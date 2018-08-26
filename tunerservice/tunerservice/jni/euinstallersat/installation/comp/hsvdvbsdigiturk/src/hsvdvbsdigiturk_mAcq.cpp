/**********************************************************************
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *	C Source:		hsvdvbsdigiturk_mAcq.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	dnilanjan %
 *	%date_created:	Tue Apr 23 14:21:12 2013 %
 *
**********************************************************************/
#include	"_hsvdvbsdigiturk_mAcq.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsdigiturk_mAcq")

/****************************************************************************
 * Local include files
 ****************************************************************************/


/****************************************************************************
 * Macros and types
 ****************************************************************************/


/* Macros */
























/****************************************************************************
 * Static variables
 ****************************************************************************/

Pump CHsvDvbsDigiTurk_mAcq_Priv::s__mDataAcqPump;

int CHsvDvbsDigiTurk_mAcq_Priv::s__mDigitalTvChannelsFoundInLnb[MAX_LNBS_SUPPORTED],CHsvDvbsDigiTurk_mAcq_Priv::s__mDigitalRadioChannelsFoundInLnb[MAX_LNBS_SUPPORTED];

int CHsvDvbsDigiTurk_mAcq_Priv::s__mDigitalTranspondersFound = 0;

int CHsvDvbsDigiTurk_mAcq_Priv::s__mCurrentLnb = 0,CHsvDvbsDigiTurk_mAcq_Priv::s__mDigitalChannelsFound = 0;

int CHsvDvbsDigiTurk_mAcq_Priv::s__mDigitalTVChannelsRemoved,CHsvDvbsDigiTurk_mAcq_Priv::s__mDigitalRadioChannelsRemoved;

HsvDataAcqInstance CHsvDvbsDigiTurk_mAcq_Priv::s__DataAcqInstance;

t_LCNsData CHsvDvbsDigiTurk_mAcq_Priv::s__mLCNData;

HsvBarkerMuxData CHsvDvbsDigiTurk_mAcq_Priv::s__BarkerMuxData;


Nat16 CHsvDvbsDigiTurk_mAcq_Priv::s__mUnicodeBuffer[11];


int CHsvDvbsDigiTurk_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID][2] = 
{
    /*Onid*/     { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)   },
    /*Tsid*/     { HSVSPID(ActualTsId, dvb, sdt),                 HSVSPID(OtherTsId, dvb, sdt)                },
    /*VerNo*/    { HSVSPID(ActualTsVersionNo, dvb, sdt),          HSVSPID(OtherTsVersionNo, dvb, sdt)         },
/*SpidService*/  { HSVSPID(ActualTSService, dvb, sdt),            HSVSPID(OtherSDTSection, dvb, sdt)          },
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

/* Static functions */


































Nat16 CHsvDvbsDigiTurk_mAcq_Priv::mMapBouquetIdtoPackageId(Nat32 PackageId)
{
	Nat16 retval = 0xFFFF;
	HsvInstallationPTC    ptc;
	HsvPgdatDigSatInfoData	SatInfo;

	switch (PackageId)
	{
		case DIGITURK_TURKSAT_PACKAGE_ID:
			retval = DIGITURK_TURKSAT_42E_BOUQUET_ID;
			break;
		case DIGITURK_EUTELSAT_PACKAGE_ID:
			iscandata_GetPtcInfo(&ptc);
			SatInfo.LnbNumber = ptc.LnbNumber;
			if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatInfo) == TRUE)
			{
				retval = ((SatInfo.LnbType == LnbMdutype1) ? DIGITURK_EUTELSAT_W3_SD_BOUQUET_ID : DIGITURK_EUTELSAT_W3_BOUQUET_ID);
				TraceNotice(m, "%s: LNB_Type: %d, Bouquet id: %d",__FUNCTION__,SatInfo.LnbType,retval);
			}
			break;
	}
	return retval;
}


void CHsvDvbsDigiTurk_mAcq_Priv::mPumpHandler(int value, Nat32 param)
{
	TraceNotice(m, "%s value  %d", __FUNCTION__, value);
	if(value == EvStartAcquistion)
	{
		if(param == idataacq_Homing)
		{
			t_LCNInfo LCNInfo;
			
			Nat32 PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
			Nat16 BouquetId = mMapBouquetIdtoPackageId(PackageId);

			/* Naresh: below is overloaded function, the param is used for other purpose and not here */
			mGetLCNData(BouquetId, &LCNInfo, ACQUIRE_LCNS);
			if (PackageId == DIGITURK_TURKSAT_PACKAGE_ID)
			{
				Bool retval = mCollectTurkSatBarkerMuxData();
				TraceNotice(m,"Barker mux data collection for TrukSat %s", (retval == TRUE)?"Success" : "Failed");
			}
			else
			{
				
				Bool retval = mCollectEutelSatBarkerMuxData();
				TraceNotice(m,"Setting number of barker mux to 0 for EutelSat %s", (retval == TRUE)?"Success" : "Failed");
			}
			
			//TraceNotice(m,"Barker mux data collection %s", (retval == TRUE)?"Success" : "Failed");
		}
		else
		{
			mAcquireData();
		}
		idataacqN_OnDataAquired(TRUE);
	}
	else if(value == EvSyncRecords)
	{
		mSyncServiceRecords(param);
	}
	UNUSED(param);
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mIsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	
	switch (psvcdat->ServiceType)
	{
		case AppApiTelevisionService:
		case AppApiMPEG2HDService:
		case AppApi3DHDDigitalService:
		case AppApiAdvCodecHDTelevisionService:
		case	AppApiHevcService:
			RetVal = TRUE;
			break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mIsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	
	switch (psvcdat->ServiceType)
	{
		case AppApiRadioService:
		case AppApiUserDefinedRadioChannelWithVideoComp:
			RetVal = TRUE;
			break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mGetTSMetaData(void)
{
    Bool	retval = FALSE;
    int		TableId = ACTUAL_TABLE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, GETHSVSPID(Onid, TableId), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(Tsid, TableId), 0, 0, 0, &DataAcqInstance.Tsid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(VerNo, TableId), 0, 0, 0, &DataAcqInstance.TsVersionNum);

	TraceNotice (m, "ONID %d and TsId %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);

    return retval;
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mInstallMux(HsvInstallationPTC *ptc)
{
    Bool	retval = FALSE;
	int		TableId = ACTUAL_TABLE;
	int		i, TotalServices = 0, InstalledServices = 0;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	
	TotalServices = strapi_GetSize (HsvMain, GETHSVSPID(SpidService, TableId));
	TraceNotice (m, "%s %d NoOfServices in MUX = %d\n",__FUNCTION__, __LINE__, TotalServices);
	
	/* From strapi get all the services and add/update them in TEMP_SVC_TABLE */
    for(i = (TotalServices - 1); i >= 0 ; i--)
    {
		if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId), i, (void *)(&service)) == TRUE)
        {
            if( mCheckServiceForInstall (ptc, &service) == TRUE )
            {
				/* TODO: mSatDetailsTo correct this and increment only when succesful addition happens */
                InstalledServices++;
                retval = TRUE;
            }
        }
    }
	
	TraceNotice (m, "mSatDetailsUpdateprint: Num TV: %d Num Radio: %d\n", mDigitalTvChannelsFoundInLnb[mCurrentLnb], mDigitalRadioChannelsFoundInLnb[mCurrentLnb]);
    TraceNotice (m, "Installed %d services\n", InstalledServices);

    return retval;
}

void CHsvDvbsDigiTurk_mAcq_Priv::mAcquireData(void)
{
	/* Call Back once Data collection is completed by SDM */
    HsvInstallationPTC    ptc;

	memset (&DataAcqInstance, 0x00, sizeof(DataAcqInstance));

	/* Getting ONID, TS details */
	Bool retval = mGetTSMetaData();

	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
    if(retval == TRUE)
    {
		/* Get Current PTC details from scan module */
        iscandata_GetPtcInfo(&ptc);
		TraceNotice (m, "%s %d svcdat.Frequency %ld\n", __FUNCTION__, __LINE__, ptc.Frequency);

		if(mInstallMux(&ptc) == TRUE )
		{
			/* Add entry to TS Table */
			mAddToTSTable(&ptc);
			
			TraceNotice (m, " TranspondeNum: %d , Freq %d Pol %d SymRate %d Tv: %d Rad: %d\n", mDigitalTranspondersFound, (int)ptc.Frequency ,\
								ptc.Polarization, (int)ptc.SymbolRate, mDigitalTVChannelsRemoved, mDigitalRadioChannelsRemoved);
		}
		mDigitalTranspondersFound++;
		TraceNotice (m, " Tranponder Count is %d \n", mDigitalTranspondersFound);
    }
	else
	{
		TraceNotice (m, "PTC Ignored: Invalid PTC or Incomplete Data\n");
	}
}

void CHsvDvbsDigiTurk_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc)
{
	SDSDList SDSDListData;
	int CurrentSDSDIndex;
	HsvPgdatDigTSData   tsdata, tmptsdata;

	
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
	
	CurrentSDSDIndex = isdsddata_GetSDSDData((void*)&SDSDListData);
	
	if(CurrentSDSDIndex < SDSDListData.NumofSDSDs)
	{
		/* Filling attributes from ptc, and acqinstance */
		tsdata.Frequency				= ptc->Frequency;
		tsdata.SymbolRate				= ptc->SymbolRate;

		tsdata.OriginalNetworkId		= SDSDListData.SDSD[CurrentSDSDIndex].Original_NetworkId;
		tsdata.Tsid						= SDSDListData.SDSD[CurrentSDSDIndex].Tsid;
		tsdata.NetworkId				= DataAcqInstance.NetworkId;
		tsdata.ModulationType			= ptc->ModulationType;
	//tsdata.CodeRate				= ptc->CodeRateHigh;
	tsdata.IqMode					= ptc->ModulationStd;
	tsdata.CodeRate					= ptc->CodeRate;
	//tsdata.IqMode					= ptc->IqMode;
		tsdata.Bandwidth			= ptc->ChannelBandwidth;
		tsdata.PtcListVersion			= iscandata_GetInstallationVersion();
		tsdata.SDSDFrequency			= ptc->SDSDFrequency;
		tsdata.UserInstalled			= mIsManualInstall();
		tsdata.TSVersion				= DataAcqInstance.TsVersionNum;
		tsdata.LnbNumber				= ptc->LnbNumber;
		tsdata.Polarization				= ptc->Polarization;
		tsdata.Tpid						= ptc->TPID;

		tmptsdata.LnbNumber				= tsdata.LnbNumber;
		tmptsdata.Frequency				= tsdata.Frequency;
		tmptsdata.Polarization			= tsdata.Polarization;

	/* check entry already present. If yes update else add */
	/* TODO: Manual + servic scan uses PTC Table directly */
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE )
	{
		TraceNotice (m, "Addition to pgdb table %s %d <%ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency);
		TraceDebug(m, "Nilanjan tsdata: ModulationType = %d, ModulationStd = %d, CodeRate = %d", tsdata.ModulationType, tsdata.IqMode,tsdata.CodeRate);
		pgdb_Add(PTC_TABLE, (Address )&tsdata);

		}
		else
		{
			TraceNotice (m, "Updation to pgdb table %s %d <%ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency);
			pgdb_Update(PTC_TABLE, (Address )&tsdata);
		}
	}
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	SDSDList SDSDListData;
	int DuplicateIndex = -1, CurrentSDSDIndex;
	Bool		retval = FALSE, channelExists = FALSE;
	HsvPgdatDigServiceData svcdat, tempsvcdat;

	TraceNotice (m, " SvcId %d and SvcType %d \n", service->ServiceId, service->ServiceType);

	/* Checking whether service is having installable service type. TODO: Define the Service type  */
    if( mIsServiceInstallable(ptc, service))
    {
		/* Get Default values */
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));
		CurrentSDSDIndex = isdsddata_GetSDSDData((void*)&SDSDListData);
		if(CurrentSDSDIndex < SDSDListData.NumofSDSDs)
		{
			svcdat.OriginalNetworkId	 = SDSDListData.SDSD[CurrentSDSDIndex].Original_NetworkId;
			svcdat.ServiceId			 = service->ServiceId;
			svcdat.Frequency	         = ptc->Frequency;
			svcdat.Tsid                  = SDSDListData.SDSD[CurrentSDSDIndex].Tsid;
			svcdat.LnbNumber			 = ptc->LnbNumber;
			svcdat.Polarization			 = ptc->Polarization;
			svcdat.Tpid					 = ptc->TPID;
			svcdat.SDSDFrequency		 = ptc->SDSDFrequency;
			svcdat.SymbolRate            = ptc->SymbolRate;
			TraceNotice (m, "In CheckServiceForInstall LNB %d Pol %d TpId %d TSID %d ONID %d\n", ptc->LnbNumber, ptc->Polarization, (int) ptc->TPID, svcdat.Tsid, svcdat.OriginalNetworkId);

			tempsvcdat.Tpid				 = svcdat.Tpid;
			tempsvcdat.ServiceId		 = svcdat.ServiceId;

			/* There is no concept of duplicate services. Even if the services are repeated,
				they are added. But the TPID & service ID combination cannot be duplicate */
			channelExists = mDuplicateEntry(svcdat, &DuplicateIndex);
			/*TraceNotice ( m,"Channel Exist[%d]",	channelExists);*/
			if (channelExists)
			{
				/* If entry already present update the service data */
				TraceNotice(m,"%s : Duplicate Service Found...", __FUNCTION__); 
				mUpdateService(&svcdat, ptc, service, DuplicateIndex);
				retval = TRUE;	
			}
			else
			{	
				TraceNotice(m,"%s : New service found...", __FUNCTION__);
				mAddNewService(&svcdat, ptc, service);
				retval = TRUE;
			}
		}
	}
	return retval;
}

void CHsvDvbsDigiTurk_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service, int DuplicateIndex)
{
	/* Filling update details and updating */
	HsvPgdatPresetData		presetdata;	
	HsvPgdatDigServiceData 	tmpsvcdata;
	
	mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mUpdateSatelliteName (psvcdat);
	
	if(VALID_LCN_RANGE(psvcdat->LCN))
	{
		ASSIGN_KEYS_OF_SVC(tmpsvcdata, (*psvcdat));
		if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tmpsvcdata) == TRUE)
		{
			mRetainNonBroadcastAttributes(psvcdat, tmpsvcdata);
			TraceNotice(m,"Old LCN: %d, New LCN: %d", tmpsvcdata.PresetNumber, psvcdat->LCN);
			if((VALID_LCN_RANGE(psvcdat->LCN) || VALID_LCN_RANGE(tmpsvcdata.LCN)) && (psvcdat->LCN != tmpsvcdata.LCN))
			{
				TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->LCN, tmpsvcdata.LCN, tmpsvcdata.PresetNumber);
				presetdata.PresetNumber =   tmpsvcdata.PresetNumber;
				pgdb_Delete(PRESET_TABLE, (Address)&presetdata);
				psvcdat->PresetNumber = INVALID_PRESET;		 
			}
			pgdb_Update(SERVICE_TABLE, (Address)psvcdat);			
		}
		else
		{
			if((DuplicateIndex != -1) && (pgdb_GetByIndex( SERVICE_TABLE, DuplicateIndex, (Address)&tmpsvcdata)))
			{
				mRetainNonBroadcastAttributes(psvcdat, tmpsvcdata);
				
				presetdata.PresetNumber =   tmpsvcdata.PresetNumber;
				pgdb_Delete(SERVICE_TABLE, (Address)&tmpsvcdata);

				if((VALID_LCN_RANGE(psvcdat->LCN) || VALID_LCN_RANGE(tmpsvcdata.LCN)) && (psvcdat->LCN != tmpsvcdata.LCN))
				{
					TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->LCN, tmpsvcdata.LCN, tmpsvcdata.PresetNumber);
					presetdata.PresetNumber =   tmpsvcdata.PresetNumber;
					pgdb_Delete(PRESET_TABLE, (Address)&presetdata);
					psvcdat->PresetNumber = INVALID_PRESET;		 
				}
				else
				{
					if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetdata))
					{
						TraceNotice(m, "Updating the preset entry %d of Preset table", (int)presetdata.PresetNumber);
						presetdata.OriginalNetworkId = psvcdat->OriginalNetworkId;
						presetdata.ServiceId = psvcdat->ServiceId;
						presetdata.Tsid = psvcdat->Tsid;
						presetdata.Tpid = psvcdat->Tpid;
						presetdata.Frequency = psvcdat->Frequency;
						presetdata.Polarization = psvcdat->Polarization;
						presetdata.LnbNumber = psvcdat->LnbNumber;
						pgdb_Update(PRESET_TABLE, (Address)&presetdata);
					}				
				}

				pgdb_Add(SERVICE_TABLE, (Address)psvcdat);
				
			}
			
		}
		TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
	}
	else
    {
    	ASSIGN_KEYS_OF_SVC(tmpsvcdata, (*psvcdat));
    	if((pgdb_GetByKey(SERVICE_TABLE, (Address)&tmpsvcdata) == TRUE) && (tmpsvcdata.SDSDFrequency != 0))
    	{
        	presetdata.PresetNumber =   tmpsvcdata.PresetNumber;
        
			if (mIsDigitalTvChannel (psvcdat))
			{
				mDigitalTVChannelsRemoved++;
			}
			else if (mIsDigitalRadioService (psvcdat))
			{
				mDigitalRadioChannelsRemoved++;
			}
			TraceNotice(m,"Deleted Service PresetNo %d LCN:%d ONID:%d SVCID:%d\n", (int)presetdata.PresetNumber,(int) psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
        	pgdb_Delete(PRESET_TABLE, (Address)&presetdata);
        	pgdb_Delete(SERVICE_TABLE, (Address)psvcdat);

		}
	}
}

void CHsvDvbsDigiTurk_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;

	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
	}
}

void CHsvDvbsDigiTurk_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	/* Filling details of service, then adding it */	
	mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mUpdateSatelliteName (psvcdat);
	
	if(VALID_LCN_RANGE(psvcdat->LCN))
	{
		mAssignSvcNonBroadcastAttributes(psvcdat);
		/* Check service is TV or Radio */
		if (mIsDigitalTvChannel (psvcdat))
		{
			mDigitalTvChannelsFoundInLnb[mCurrentLnb]++;
		}
		else if (mIsDigitalRadioService (psvcdat))
		{
			mDigitalRadioChannelsFoundInLnb[mCurrentLnb]++;
		}
		
		/* Add to Service table */
		
		pgdb_Add(SERVICE_TABLE, (Address )psvcdat);

		mDigitalChannelsFound++;		
		TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d\n",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
		TraceNotice(m,"SDTVersion = %ld\r\n",(Nat32) DataAcqInstance.SDTVersion);
	}
	else
	{
		TraceNotice(m,"Service Not installed LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
	}
}

/*--------------------------------------------------------------------------------------------------------------------------*/
Nat16 * CHsvDvbsDigiTurk_mAcq_Priv::mAsciiToUnicode(char *ascii_str,int length)
/*--------------------------------------------------------------------------------------------------------------------------*/
{
	int loop = 0;
    while( loop < length )
    {
        mUnicodeBuffer[loop] = ascii_str[loop];
        ++loop;
    }
	return  mUnicodeBuffer;
}

void CHsvDvbsDigiTurk_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	int mode, state;
	HsvPATProgramPIDInfo		val;

	insstate_GetCurrentInstallationState(&mode, &state);

	psvcdat->NetworkId			   =   DataAcqInstance.NetworkId;
	psvcdat->ModulationType        =   ptc->ModulationType;
	psvcdat->Bandwidth	   			=   ptc->ChannelBandwidth;
	psvcdat->SymbolRate            =   ptc->SymbolRate;
	psvcdat->ServiceType           =   service->ServiceType;
    psvcdat->FreeCiMode	    	   =   service->Free_Ci_Mode;
	psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
	psvcdat->NumBrandIds	       =   service->NumBrandIds;
	psvcdat->AudioPid              =   INVALID_PID;
	psvcdat->VideoPid              =   INVALID_PID;
	psvcdat->PcrPid                =   INVALID_PID;
	psvcdat->LCN				   =   INVALID_LCN;
	psvcdat->LnbNumber			   =   ptc->LnbNumber;
	psvcdat->Polarization		   =   ptc->Polarization;
	psvcdat->Tpid				   =   ptc->TPID;
	
	psvcdat->NumericSelect = TRUE;

	if(service->Free_CA_Mode == TRUE)
    {
        psvcdat->ScramblingStatus = 1;
    }
	mAssignLCN(psvcdat);
	/* ANEESH: TODO: Change this 
	if ( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) 
	{
		psvcdat->PmtPid			   =   val.Pid;
	}
	*/
	
	psvcdat->SystemHidden = !(psvcdat->VisibleService);

	DataAcqInstance.SDTVersion		   = service->VersionNumber;
	mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds );

	if(service->ServiceName[0] == 0)
    {
        mCopyString( psvcdat->ChannelName, mAsciiToUnicode("-----", 5), 5);
    }
    else
    {
		mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_PresetNameLength - 1) );
    }

}

void CHsvDvbsDigiTurk_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
	int mode, state;
	


	insstate_GetCurrentInstallationState(&mode, &state);

	psvcdat->UserHidden             = FALSE;
	psvcdat->ChannelLock		    = FALSE;
	psvcdat->Favorite			    = FALSE;
	psvcdat->DateStamp			    = 0;
	psvcdat->PresetNumber		    = INVALID_PRESET;
	psvcdat->ServiceListVersion     = iscandata_GetInstallationVersion();
	psvcdat->NewPreset				= (mode == AUTO_MODE)? FALSE : TRUE;
	psvcdat->HbbTvOption 		    = 1;
	if(DIGITURK_TURKSAT_PACKAGE_ID == insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId)) {
		psvcdat->PackageGroup           = DIGITURK_TURKSAT_MATCH_SETTINGS_DB_PACKAGE_ID;
	} else {
		psvcdat->PackageGroup			= DIGITURK_EUTELSAT_MATCH_SETTINGS_DB_PACKAGE_ID;
	}
	
	if( Timerclk_IsClockDefined())
    {
        psvcdat->DateStamp = Timerclk_GetUniversalTime();
    }
}

void CHsvDvbsDigiTurk_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	Bool lRetVal = FALSE;

	switch(service->ServiceType)
	{
		case AppApiTelevisionService:
		case AppApiRadioService:
		case AppApiMPEG2HDService:
		case AppApi3DHDDigitalService:
		case AppApiAdvCodecHDTelevisionService:
		case AppApiUserDefinedRadioChannelWithVideoComp:
		case AppApiHevcService:
			lRetVal = TRUE;
			break;
		default:
			break;
	}
	return lRetVal;	    
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mIsManualInstall(void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mIsUpdateInstall(void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mIsServiceScanInstall (void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationServiceScan)? TRUE: FALSE);
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mGetLCNData(Nat16 BouquetId, t_LCNInfo *LCNInfo, int ActionOnData)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HSVSPID(batLCN,dvb,bat));
    HSVSPTYPE(batLCN, dvb, bat) batlcn;

	TraceNotice(m, "%s %d", __FUNCTION__, ActionOnData);
    if( ActionOnData == ACQUIRE_LCNS )
    {
        for(i = 0; i < numOfRecords; i++)
        {
            if( (strapi_GetByIndex(HsvMain, HSVSPID(batLCN,dvb,bat), i, (Address)(&batlcn)) == TRUE) )
            {
                /* Take only those LCNs which are matching with Target NIT */
                if(batlcn.BouquetId == BouquetId)
                {
                    retval = TRUE;
                    if(mPopulateLCN((Address)(&batlcn)) == FALSE)
                    {
                        break;
                    }
                }
            }
        }
		TraceNotice(m, "%s mLCNData.NumOfLCNRecords %d", __FUNCTION__, mLCNData.NumOfLCNRecords);
    }
    else
    {
        if( (strapi_GetByKey(HsvMain, HSVSPID(batLCN,dvb,bat), LCNInfo->Original_NetworkId, LCNInfo->Tsid, LCNInfo->ServiceId, &batlcn) == TRUE) )
        {
            mCopyLCNInfo( LCNInfo, batlcn.Original_NetworkId, batlcn.Tsid, batlcn.ServiceId, batlcn.LogicalChannelNum, batlcn.DpServiceId, batlcn.DpTsid);
            retval = TRUE;
        }
    }
    return retval;
}

inline void CHsvDvbsDigiTurk_mAcq_Priv::mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int DpServiceId, int DpTsid)
{
    LCNInfo->Original_NetworkId = OnId;
    LCNInfo->Tsid               = TsId;
    LCNInfo->ServiceId          = SvcId;
    LCNInfo->LogicalChannelNum  = Lcn;
	LCNInfo->DpServiceId        = DpServiceId;
	LCNInfo->DpTsid				= DpTsid;
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mPopulateLCN(Address data)
{
    int cacheIndex = 0;
    Bool retval = TRUE;
    HSVSPTYPE(batLCN, dvb, bat) *nwlcn;
    

    nwlcn = (HSVSPTYPE(batLCN, dvb, bat) *)data;
    cacheIndex = mGetLCNIndex(nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId);

    mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId, \
            nwlcn->LogicalChannelNum, nwlcn->DpServiceId, nwlcn->DpTsid);
    mLCNData.VersionNumber = nwlcn->VersionNumber;

    if(cacheIndex >= mLCNData.NumOfLCNRecords)
    {
        mLCNData.NumOfLCNRecords++;
        TraceErr(m,"Acquire service <%d %d %d> LCN = %d", nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId, nwlcn->LogicalChannelNum);
    }
    
    if(mLCNData.NumOfLCNRecords == MAX_LCN_NUMBERS)
    {
        TraceErr(m, "ASSERT: Increase the number of LCN records");
        retval = FALSE;
    }

    return retval;
}

int CHsvDvbsDigiTurk_mAcq_Priv::mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId)
{
    int i = 0;

    for( i = 0; i < mLCNData.NumOfLCNRecords; i++)
    {
        if((mLCNData.mLCNInfo[i].Original_NetworkId == Onid) && (mLCNData.mLCNInfo[i].Tsid == Tsid) && (mLCNData.mLCNInfo[i].ServiceId == ServiceId))
        {
            break;
        }
    }
    return i;
}

void CHsvDvbsDigiTurk_mAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	Nat32 PackageId;
	t_LCNInfo LCNInfo;
	int cacheIndex = 0, DummyBouquetId = 0;
	
	if(mLCNData.NumOfLCNRecords == 0)
    {
        LCNInfo.Original_NetworkId = psvcdat->OriginalNetworkId; LCNInfo.Tsid = psvcdat->Tsid; LCNInfo.ServiceId = psvcdat->ServiceId; //keys to get the LCN frm strapi records 
        if(mGetLCNData(DummyBouquetId, &LCNInfo, GET_LCN) == TRUE)
        {
			psvcdat->LCN            = (VALID_LCN_RANGE(LCNInfo.LogicalChannelNum) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
			psvcdat->VisibleService = TRUE;
			
			PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
			if(PackageId == DIGITURK_TURKSAT_PACKAGE_ID)
			{
				psvcdat->DpServiceId    = LCNInfo.DpServiceId;
				psvcdat->DpTsid         = LCNInfo.DpTsid;
			}
            TraceErr(m," %s %d LCN %d <%d, %d, %d>\n", __FUNCTION__, __LINE__, psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
        }
    }
    else
    {
        /* Assign from Target BAT */
		cacheIndex = mGetLCNIndex(psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
		if(cacheIndex != mLCNData.NumOfLCNRecords)
		{
			psvcdat->LCN = (VALID_LCN_RANGE(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;
			psvcdat->VisibleService = TRUE;
			
			PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
			if(PackageId == DIGITURK_TURKSAT_PACKAGE_ID)
			{
				psvcdat->DpServiceId    = mLCNData.mLCNInfo[cacheIndex].DpServiceId;
				psvcdat->DpTsid         = mLCNData.mLCNInfo[cacheIndex].DpTsid;
			}
			TraceErr(m," %s %d LCN %d <%d, %d, %d>\n", __FUNCTION__, __LINE__, psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
		}
    }
}

void CHsvDvbsDigiTurk_mAcq_Priv::mSyncServiceRecords(int EvCurrentRecordIndex)
{
	TraceNotice(m, "%s", __FUNCTION__);	
	HsvPgdatDigTSData   	tsdata;
	HsvPgdatDigServiceData  svcdata;
	HsvPgdatPresetData		presetdata;
	int LCNIndex;
    int i, j, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE), InstallationVersion = iscandata_GetInstallationVersion();
    
	for( i = EvCurrentRecordIndex, j = 0; (i < NoOfRecs) && (j < MAX_SERVICES_IN_SINGLE_STEP); i++, j++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdata) == TRUE )
        {
			EvCurrentRecordIndex = i;

            if(svcdata.ServiceListVersion < InstallationVersion)
            {
				TraceDebug(m, "Old Service LCN %d ServiceId %d\n", svcdata.LCN, svcdata.ServiceId);
				
				//Assign keys  of PTC table
				tsdata.LnbNumber	= 	svcdata.LnbNumber;
				tsdata.Frequency	=	svcdata.Frequency;
				tsdata.Polarization =	svcdata.Polarization;

				LCNIndex = 0;
				LCNIndex = mGetLCNIndex(svcdata.OriginalNetworkId, svcdata.Tsid, svcdata.ServiceId);

				//TraceNotice(m,"Nilanjan LCNIndex = %d, NumOfLCNRecords = %d", LCNIndex, mLCNData.NumOfLCNRecords);
				
				
				if(((pgdb_GetByKey(PTC_TABLE, (Address)&tsdata) == TRUE) && (tsdata.PtcListVersion == InstallationVersion)&& (svcdata.SDSDFrequency != 0))
				    || ((mPresentInSDSD(&tsdata) == FALSE) && (svcdata.SDSDFrequency != 0))
				    || ((LCNIndex == mLCNData.NumOfLCNRecords) && (svcdata.SDSDFrequency != 0)))
				{
					presetdata.PresetNumber = svcdata.PresetNumber;
					
					if (mIsDigitalTvChannel (&svcdata))
					{
						mDigitalTVChannelsRemoved++;
					}
					else if (mIsDigitalRadioService (&svcdata))
					{
						mDigitalRadioChannelsRemoved++;
					}
					TraceDebug(m, "%s Preset %d deleted", __FUNCTION__, svcdata.PresetNumber);
					pgdb_Delete(SERVICE_TABLE, (Address)&svcdata);				
					pgdb_Delete(PRESET_TABLE, (Address)&presetdata);
					i--;
				}
			}
		}
	}
	
	if(i < NoOfRecs)
	{
		pmp_PmpSend(mDataAcqPump, EvSyncRecords, (EvCurrentRecordIndex + 1));
	}
	else
	{
		mSyncPtcRecords();
	}
}

void CHsvDvbsDigiTurk_mAcq_Priv::mSyncPtcRecords(void)
{
	Bool Found = FALSE;
	HsvPgdatDigTSData   	tsdata;
	HsvPgdatDigServiceData 	svcdata;
	int i, from = -1, to = -1, NoOfRecs = pgdb_GetNoRecords(PTC_TABLE), InstallationVersion = iscandata_GetInstallationVersion();
    
	for(i = NoOfRecs; (i >= 0); i--)
    {
		Found = FALSE;
        if( pgdb_GetByIndex(PTC_TABLE, i, (Address)&tsdata) == TRUE )
        {
			if(tsdata.PtcListVersion < InstallationVersion)
            {
				svcdata.Tpid = tsdata.Tpid;
				if( pgdb_GetRange(SERVICE_TABLE, 1, (Address)&svcdata, &from, &to) )
				{
					if((from >= 0) && (to >= 0))
					{
						Found = TRUE;
					}
				}
				
				if(Found == FALSE)
				{
					/* no service is installed from this PTC  so delete it from TS table */
					TraceNotice(m, "Old TS Entry Frequency %d deleted\n", (int)tsdata.Frequency);				
					pgdb_Delete(PTC_TABLE, (Address)&tsdata);
				}
			}
		}
	}
	
	TraceErr(m, "%s SyncComplete done", __FUNCTION__);
	iscandata_SyncComplete();
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mDuplicateEntry(HsvPgdatDigServiceData svcdat, int *DuplicateIndex)
{
    Bool retval = FALSE;
    int i = 0, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat2;

	for(i = 0; i <= NoOfRecs; i++)
	{
		if(pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat2))
		{
			if(svcdat.ServiceId == svcdat2.ServiceId)
			{
				TraceDebug(m, "Nilanjan: CurrentSrvcFreq, Pol = <%d, %d>, OldSrvcFreq, Pol = <%d, %d>, CurrentSrvcSymRate = %d", svcdat.Frequency,svcdat.Polarization,svcdat2.Frequency,svcdat2.Polarization,svcdat.SymbolRate);
				if ( (util_CheckFreqDuplicationwithRolFact(svcdat.Frequency, svcdat2.Frequency, svcdat.SymbolRate)) && (svcdat.Polarization == svcdat2.Polarization)
				     || ((svcdat.Tsid == svcdat2.Tsid) && (svcdat.OriginalNetworkId == svcdat2.OriginalNetworkId) && (svcdat2.SDSDFrequency != 0)) )
				{
					retval = TRUE;
					*DuplicateIndex = i;
					break;
				}
			}
		}
	}

    return retval;
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mPresentInSDSD(HsvPgdatDigTSData *tsdata)
{
	int i = 0;
	Bool retval = FALSE;
	SDSDList SDSDListData;
	
	isdsddata_GetSDSDData((void*)&SDSDListData);
	
	for(i = 0; i < SDSDListData.NumofSDSDs; i++ )
	{
		if( (abs((int)SDSDListData.SDSD[i].Frequency - (int)tsdata->Frequency) <= FREQ_DRIFT_TOLERANCE) 
			&& (SDSDListData.SDSD[i].Polarization == tsdata->Polarization) )
		{
			retval = TRUE;
			break;
		}				
	}
	
	return retval;
}

void CHsvDvbsDigiTurk_mAcq_Priv::mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat)
{
    psvcdat->NewPreset 				= svcdat.NewPreset;
    psvcdat->PresetNumber           = svcdat.PresetNumber;
    psvcdat->ChannelLock            = svcdat.ChannelLock;;
    psvcdat->UserHidden             = svcdat.UserHidden;
    psvcdat->Favorite               = svcdat.Favorite;
    psvcdat->FavoriteNumber         = svcdat.FavoriteNumber;
    psvcdat->ServiceListVersion     = iscandata_GetInstallationVersion();
    psvcdat->HbbTvOption            = svcdat.HbbTvOption;
    psvcdat->DeltaVolume            = svcdat.DeltaVolume;
    psvcdat->UserModifiedName             = svcdat.UserModifiedName;
    psvcdat->LogoURL                = svcdat.LogoURL;
    
    psvcdat->VideoPid              =  svcdat.VideoPid;              
    psvcdat->AudioPid              =  svcdat.AudioPid;
    psvcdat->PcrPid                =  svcdat.PcrPid;    
    psvcdat->VideoStreamType       =  svcdat.VideoStreamType;
    psvcdat->AudioStreamType       =  svcdat.AudioStreamType;
    psvcdat->SecAudioStreamType    =  svcdat.SecAudioStreamType;
    psvcdat->SecAudioPid           =  svcdat.SecAudioPid;
    psvcdat->PackageGroup		   =  svcdat.PackageGroup;	
    memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::mCollectEutelSatBarkerMuxData(void)
{
	int NumOfLinkageDesc = 0, i = 0, j = 0, index = 0;
	Bool RetVal = FALSE;
	HsvBarkerMuxData BarkerMuxData;
#if 0
	SDSDList SDSDListData;
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;
	
	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));
	TraceNotice(m, "NumOfLinkageDesc = %d", NumOfLinkageDesc);
	
	for(i = 0; i < NumOfLinkageDesc ; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, nit), i, (void*)(&LinkageDesc)) == TRUE)
		{
			if(LinkageDesc.LinkageType == BARKER_MUX_LINKAGE_TYPE)
			{
				/*Get the barker mux data and write into the file*/
				/*check if data has to be appended or written as new*/
				
				if(util_ReadBarkerMuxData(&BarkerMuxData) == FALSE)
				{
					BarkerMuxData.NoOfRecords = 0;
				}
				
				index = BarkerMuxData.NoOfRecords;
				BarkerMuxData.NoOfRecords ++;
				BarkerMuxData.Mux[index].OnId = LinkageDesc.Original_NetworkId;
				BarkerMuxData.Mux[index].TsId = LinkageDesc.Tsid;
				BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = THOR_1W;
				
				isdsddata_GetSDSDData((void*)&SDSDListData);
				for(j = 0; j < SDSDListData.NumofSDSDs; j++)
				{
					if((SDSDListData.SDSD[j].Original_NetworkId == LinkageDesc.Original_NetworkId) && (SDSDListData.SDSD[j].Tsid == LinkageDesc.Tsid))
					{
						BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.Frequency = SDSDListData.SDSD[j].Frequency;
						BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.tp_id = CREATE_TPID(mCurrentLnb, SDSDListData.SDSD[j].Frequency, SDSDListData.SDSD[j].Polarization);
						if(util_WriteBarkerMuxData(BarkerMuxData) == TRUE)
						{
							RetVal = TRUE;
						}
						break;
					}
				}
				break;
			}
		}
		else
		{
			TraceNotice (m," Collect linkage info failed for index: %d \n",i);
		}
	}

	if(i >= NumOfLinkageDesc)
	{
			TraceNotice (m," No Barker mux found\n");
	}
	return RetVal;
#endif


	BarkerMuxData.NoOfRecords = 0;
	if(util_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		RetVal = TRUE;
	}
	return RetVal;

}

int CHsvDvbsDigiTurk_mAcq_Priv::mGetSatelliteLnbNo(int SatId)
{
	int i;
	HsvPgdatDigSatInfoData SatDetails;
	int LnbNumber = 0;
	for(i=0; i < MAX_LNBS_SUPPORTED; i++)
	{
		pgdb_Initialise(pgdbconst_SatInfo, (Address) &SatDetails);
		SatDetails.LnbNumber = i;
		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails) != TRUE)
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n",i);
		}

		if(SatDetails.SatelliteId == SatId)
		{
			LnbNumber = i;
			break;
		}
	}
	return LnbNumber;
}


Bool CHsvDvbsDigiTurk_mAcq_Priv::mCollectTurkSatBarkerMuxData(void)
{
	int NumOfLinkageDesc = 0, i = 0, j = 0, index = 0, HomingIndex = 0;
	Bool RetVal = FALSE;
	SDSDList SDSDListData;
	PackageDetails HomingData;
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;
	int LnbNumber = 0;;
	
	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));
	
	if(util_ReadBarkerMuxData(&BarkerMuxData) == FALSE)
	{
		BarkerMuxData.NoOfRecords = 0;
	}
	
	index = BarkerMuxData.NoOfRecords;
	BarkerMuxData.NoOfRecords ++; 
	TraceNotice(m, "Nilanjan %d : BarkerMuxData.NoOfRecords = %d", __LINE__, BarkerMuxData.NoOfRecords);
	/*BarkerMuxData.Mux[index].OnId = LinkageDesc.Original_NetworkId;
	BarkerMuxData.Mux[index].TsId = LinkageDesc.Tsid;
	BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = THOR_1W;*/
	
	isdsddata_GetSDSDData((void*)&SDSDListData);
	HomingIndex = isdsddata_GetHomingData((void*)&HomingData);
	LnbNumber = mGetSatelliteLnbNo(TURKSAT_42_0_E);
				
	for(j = 0; j < SDSDListData.NumofSDSDs; j++)
	{
		//if((SDSDListData.SDSD[i].Original_NetworkId == LinkageDesc.Original_NetworkId) && (SDSDListData.SDSD[i].Tsid == LinkageDesc.Tsid))
		if (HomingData.HomingMuxDetails[HomingIndex].Frequency == SDSDListData.SDSD[j].Frequency)
		{
			BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.Frequency = SDSDListData.SDSD[j].Frequency;
			BarkerMuxData.Mux[index].OnId = SDSDListData.SDSD[j].Original_NetworkId;
			BarkerMuxData.Mux[index].TsId = SDSDListData.SDSD[j].Tsid;
			BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = LnbNumber;
			BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.tp_id = CREATE_TPID(LnbNumber, SDSDListData.SDSD[j].Frequency, SDSDListData.SDSD[j].Polarization);
			TraceNotice(m, "Nilanjan: BarkerMux Freq = %d, BarkerMux Pol = %d lnb num %d", SDSDListData.SDSD[j].Frequency, SDSDListData.SDSD[j].Polarization,LnbNumber);
			RetVal = TRUE;
			break;
		}
	}

	return RetVal;
}


/****************************************************************************
 * External functions
 ****************************************************************************/
/* provides IHsvPower iacqpow */

void CHsvDvbsDigiTurk_mAcq_Priv::iacqpow_Init(void)
{

	mDataAcqPump = pmp_PmpCreateEx(pen_PumpEngine, mPumpHandler, TRUE, "hsvdvbsdigiturk_mAcq_pmp");
}

void CHsvDvbsDigiTurk_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsDigiTurk_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsDigiTurk_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
	/* Resetting all the variables */
	TraceNotice (m ,"mSatDetailsCurrentLnb number in acq %d ", LnbNumber);
	mCurrentLnb = LnbNumber;
	mDigitalTvChannelsFoundInLnb[mCurrentLnb] = mDigitalRadioChannelsFoundInLnb[mCurrentLnb] = 0;

    mDigitalChannelsFound = 0;
	mDigitalTranspondersFound = mDigitalTVChannelsRemoved = mDigitalRadioChannelsRemoved = 0;
	mLCNData.NumOfLCNRecords = 0;
}

void CHsvDvbsDigiTurk_mAcq_Priv::idataacq_AcquireData(int Mode)
{
	pmp_PmpSend(mDataAcqPump, EvStartAcquistion, (Nat32)Mode);
	UNUSED(Mode);
}

void CHsvDvbsDigiTurk_mAcq_Priv::idataacq_AcquireDataOnTimeout(void)
{
	/* Do Nothing */
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}
int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	return (mDigitalTvChannelsFoundInLnb[mCurrentLnb]);
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	return mDigitalRadioChannelsFoundInLnb[mCurrentLnb];
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{	
	return mDigitalTVChannelsRemoved;
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	return mDigitalRadioChannelsRemoved;
}

void CHsvDvbsDigiTurk_mAcq_Priv::idataacq_SyncTemporaryTableRecords(void)
{
	/* 3rd param in the  call is for the RecordIndex */
	pmp_PmpSend(mDataAcqPump, EvSyncRecords, 0);
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return 0;
}

Bool CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;

	return RetVal;
}


int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	if(Lnb < MAX_LNBS_SUPPORTED)
	{
		TvChannelsFound = mDigitalTvChannelsFoundInLnb[Lnb];
	}

	return TvChannelsFound;
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	if(Lnb < MAX_LNBS_SUPPORTED)
	{
		RadioChannelsFound = mDigitalRadioChannelsFoundInLnb[Lnb];
	}

	return RadioChannelsFound;
}

int CHsvDvbsDigiTurk_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{
	int RetVal = FALSE;
	if(util_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		RetVal = TRUE;
	}
	return RetVal;	

}
void CHsvDvbsDigiTurk_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	// Do nothing
}

void CHsvDvbsDigiTurk_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{
	// Do nothing
}

