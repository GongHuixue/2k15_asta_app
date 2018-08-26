/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvdvbspol_mAcq.c %
 *       %version: TVG_23 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by:  shivam %
 */
 
/* include dependencies */
#include	"_hsvdvbspol_mAcq.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbspol_macq")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

/* Macros */

													



									











/* Local Structures and enums */





















/****************************************************************************
 * Static variables
 ****************************************************************************/

PolLCNData CHsvDvbsPol_mAcq_Priv::s__mLCNData;

PolServiceList CHsvDvbsPol_mAcq_Priv::s__mSvcListData;

PolSatDSDesc CHsvDvbsPol_mAcq_Priv::s__mPolDSDesc;


int CHsvDvbsPol_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsPol_mAcq_Priv::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsPol_mAcq_Priv::s__mDigitalRadioChannelsFound = 0;

Pump CHsvDvbsPol_mAcq_Priv::s__mDataAcqPump;


int CHsvDvbsPol_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsPol_mAcq_Priv::s__removeCurRadio =0;

HsvDataAcqInstance CHsvDvbsPol_mAcq_Priv::s__DataAcqInstance;


HsvInstallationPTC CHsvDvbsPol_mAcq_Priv::s__CurrentPTC;

HsvBarkerMuxData CHsvDvbsPol_mAcq_Priv::s__BarkerMuxData;

double CHsvDvbsPol_mAcq_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};



int CHsvDvbsPol_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID][2] = 
{
    /*Onid*/     { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)   },
    /*Tsid*/     { HSVSPID(ActualTsId, dvb, sdt),                 HSVSPID(OtherTsId, dvb, sdt)                },
    /*VerNo*/    { HSVSPID(ActualTsVersionNo, dvb, sdt),          HSVSPID(OtherTsVersionNo, dvb, sdt)         },
    /*SLD*/    { HSVSPID(ActualServiceList, dvb, nit),          HSVSPID(OtherServiceList, dvb, nit)         },
    /*SDSD*/    { HSVSPID(SatelliteDS, dvb, nit),          HSVSPID(SatelliteDS, dvb, nit)         },
/*SpidService*/  { HSVSPID(ActualTSService, dvb, sdt),            HSVSPID(OtherSDTSection, dvb, sdt)          }    
};



/****************************************************************************
 * Static functions
 ****************************************************************************/


/* Static functions */
















































void CHsvDvbsPol_mAcq_Priv::mPumpHandler(int value, Nat32 param)
{
	Bool Status = FALSE;
	TraceInfo (m," mPumpHandler %d value",value);
	switch(value)
	{
	case EvStartAcquire:
		if(param  == idataacq_Homing)
		{
			DataAcqInstance.Mode = Homing;
			mStartHomingAcquisition();
		}
		else
		{
			DataAcqInstance.Mode = Fallback;
			mStartFallbackAcquisition();			
		}
		break;
	case EvAcquireTSInfo:
		mAcquireTSInfo();
		break;
	case EvCompleteAcquire:
		Status = DataAcqInstance.SDTOtherPresent;
		/*Give acquire complete notification*/
		if(DataAcqInstance.Mode == Homing)
		{
			idataacqN_OnDataAquired(Status);
		}
		else
		{
			idataacqN_OnDataAquired(param);
		}
		TraceNotice (m, "EvCompleteAcquire at with status: %d\n", Status);
		break;
	}
		
}


void CHsvDvbsPol_mAcq_Priv::mStartHomingAcquisition(void)
{
       /* SDTOtherStatus is checked in mCollectSdsds function so get it before collectSdsds */
	mGetSDTOtherStatus();
	/*Collect Sdsds from strapi*/
	mCollectSdsds();
	mGetSatelliteLnbNo(HOTBIRD_13_0_E);
	if(mCollectBarkerMuxData() == FALSE)
	{
		TraceNotice(m,"Barker mux data collection failed");
	}
	if(DataAcqInstance.SDTOtherPresent)
	{
		/*start acquiring TSinfo*/
		mAcquireTSInfo();
	}
	else
	{
		mCollectServicelistData();
		mAcquireLCNData();
		/*TODO:Install the mux from SDTActual*/
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);			
	}
}


int CHsvDvbsPol_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{

	int RetVal = FALSE;
	if(iutil_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		RetVal = TRUE;
	}

	return RetVal;
	
}
Bool CHsvDvbsPol_mAcq_Priv::mCollectBarkerMuxData(void)
{
	int NumOfLinkageDesc = 0, i = 0, j = 0, index = 0;
	Bool RetVal = FALSE;
	
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	HSVSPTYPE(LinkageInfo, dvb, bat) LinkageDesc;
	Nat32 PackageId;
	HsvInstallationPTC tempCurrentPTC;
	Nat16 Original_NetworkId =0xFFFF,Tsid = 0xFFFF;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	
	

	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, bat));
		memset(&BarkerMuxData, 0, sizeof(HsvBarkerMuxData));
		BarkerMuxData.NoOfRecords = 0;
		index = 0;

	 if(PackageId == CYFRAPLUS_POLSAT_PACKAGE_ID)
	{
	
		for(i = 0; i < NumOfLinkageDesc ; i++)
		{
			if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, bat), i, (void*)(&LinkageDesc)) == TRUE)
			{
				if(LinkageDesc.LinkageType == EPG_Service)
				{
					/*Get the barker mux data and write into the file*/
					/*check if data has to be appended or written as new*/
					
					BarkerMuxData.Mux[index].OnId = LinkageDesc.Original_NetworkId;
					BarkerMuxData.Mux[index].TsId = LinkageDesc.Tsid;
					BarkerMuxData.Mux[index].Params.Type = AppApiDVBSType;
					BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = DataAcqInstance.LnbNumber;
					for(j = 0; j < mPolDSDesc.NumOfSDSD; j++)
					{
						if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), j, (void*)(&tmpsdsd)) == TRUE)
						{
							if((tmpsdsd.Original_NetworkId == LinkageDesc.Original_NetworkId) && (tmpsdsd.Tsid == LinkageDesc.Tsid))
							{
								BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.Frequency = tmpsdsd.Frequency;
								BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.tp_id = CREATE_TPID(DataAcqInstance.LnbNumber, tmpsdsd.Frequency, tmpsdsd.Polarization);
								index++;
								BarkerMuxData.NoOfRecords ++;
								RetVal = TRUE;
							}
						}
					}
				}
			}
					
		}
			
	}
	else if(PackageId == CYFROWY_POLSAT_PACKAGE_ID)
	{
			isvcscandata_GetPtcInfo(&tempCurrentPTC);
			index = 0;
			BarkerMuxData.NoOfRecords = 1;
			strapi_GetByKey(HsvMain, GETHSVSPID(Onid, ACTUAL_TABLE), 0, 0, 0,&Original_NetworkId);
			strapi_GetByKey(HsvMain, GETHSVSPID(Tsid, ACTUAL_TABLE), 0, 0, 0, &Tsid);
			BarkerMuxData.Mux[index].Params.Type = AppApiDVBSType;
			BarkerMuxData.Mux[index].OnId = Original_NetworkId;
			BarkerMuxData.Mux[index].TsId = Tsid;
			BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id =  DataAcqInstance.LnbNumber;;
			BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.Frequency = tempCurrentPTC.Frequency;
			BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.tp_id = tempCurrentPTC.TPID;
			RetVal = TRUE;
	}
	return RetVal;
}


void CHsvDvbsPol_mAcq_Priv::mStartFallbackAcquisition(void)
{
	KeyUpdateReason 				KeyUpdate = NoUpdate;
	HsvPgdatDigTSData			OldTsData;

	/* Getting ONID, TS details */
	Bool retval = mGetTSMetaData();

	if(retval == TRUE)
	{
		isvcscandata_GetPtcInfo(&CurrentPTC);
		if(IsUpdateInstall() == TRUE)
		{
			/*If TS is already present with different Keys then add services with new keys returned*/
			mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
			if(mInstallFallbackMux(CurrentPTC, KeyUpdate, &OldTsData) == FALSE )
			{
				/* If no services are added\updated, delete entry from TS Table */
				mDeleteTSTable(&CurrentPTC);
			}
			/* Delete the muxes from NIT if current mux is last*/
			if(mPolDSDesc.CurrentSDSDIndex == (mPolDSDesc.NumOfSDSD-1))
			{
				/*Update this fn to delete muxes in fallback mode also*/
				mDeleteMuxesFromCurrentNIT();
			}
		}
		else
		{
			/*Intsall the services and Add to TS Table*/
			if(mInstallFallbackMux(CurrentPTC, KeyUpdate, &OldTsData) == TRUE )
			{
				/* Add entry to TS Table */
				mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
			}
		}
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)TRUE);	
	}

}


void CHsvDvbsPol_mAcq_Priv::mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
{
int	TransponderFreq;
	ptc->LnbNumber = DataAcqInstance.LnbNumber;
	ptc->Polarization = Sdsd.Polarization;	
	ptc->Frequency = Sdsd.Frequency;
	ptc->SDSDFrequency = Sdsd.Frequency;
	ptc->SymbolRate = Sdsd.SymbolRate;
	ptc->ModulationType = Sdsd.ModulationType;
	ptc->ModulationStd    = Sdsd.ModulationSystem;
	ptc->CodeRate   	  = Sdsd.FECInner;
	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);
	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
	ptc->QSignalStrength = 0;
	ptc->SSignalStrength = 0;
	ptc->HierarchyMode = HsvHierarchyNone;
	ptc->StreamPriority = HsvStreamPriorityHigh;
	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);


}

Bool CHsvDvbsPol_mAcq_Priv::mGetTSMetaData(void)
{
    Bool	retval = FALSE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain, HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &DataAcqInstance.Tsid);

	TraceNotice (m, "ONID %d and TsId %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);

    return retval;
}


void CHsvDvbsPol_mAcq_Priv::mAcquireTSInfo(void)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) CurrentSdsd;
	KeyUpdateReason KeyUpdate = NoUpdate;
	HsvPgdatDigTSData OldTsData;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &OldTsData);
	
	TraceInfo  (m, " DataAcqInstance.CurSdsd %d DataAcqInstance.NumSdsds %d sizeof(CurrentSdsd) %d", DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(CurrentSdsd));
	if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), DataAcqInstance.CurSdsd, (void *)(&CurrentSdsd)) == TRUE)
		{
			DataAcqInstance.NetworkId = CurrentSdsd.NetworkId;
			DataAcqInstance.Onid	= CurrentSdsd.Original_NetworkId;
			DataAcqInstance.Tsid = CurrentSdsd.Tsid;
			/*In Homing mode PTC info is built with in Acq. module as no tuning to SDSD is required*/
			mGetPTCInfo(CurrentSdsd,&CurrentPTC);

			if(IsUpdateInstall() == TRUE)
			{
				/*If TS is already present with different Keys then add services with new keys returned*/
				mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
				if(mInstallHomingMux(CurrentPTC, KeyUpdate, &OldTsData) == FALSE )
				{
					/* If no services are added\updated, delete entry from TS Table */
					mDeleteTSTable(&CurrentPTC);
				}
			}
			else
			{
				/*Intsall the services and Add to TS Table*/
				if(mInstallHomingMux(CurrentPTC, KeyUpdate, &OldTsData) == TRUE )
				{
					/* Add entry to TS Table */
					mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
				}
			}
			/*Increment CurSdsd after installing mux*/
			DataAcqInstance.CurSdsd++;
		}
		else
		{
			/*Should not come here*/
			TraceNotice(m,"Error in getting SDSD from strapi SDSD index: %d", DataAcqInstance.CurSdsd);
			DataAcqInstance.CurSdsd++;
		}
	}
	
	if(DataAcqInstance.CurSdsd >= DataAcqInstance.NumSdsds)
	{
		/*Delete all Carriers(SDSDs) removed from NIT */
		if(IsUpdateInstall() == TRUE)
		{
			mDeleteMuxesFromCurrentNIT();
		}
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);	
	}
	else
	{
		pmp_PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	}
}


void CHsvDvbsPol_mAcq_Priv::mDeleteTSTable(HsvInstallationPTC *ptc)
{
	HsvPgdatDigTSData   tsdata;
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Frequency				= ptc->Frequency;
	tsdata.Polarization				= ptc->Polarization;
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tsdata) == TRUE )
	{
		TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization);
		pgdb_Delete(PTC_TABLE, (Address )&tsdata);
	}
}

void CHsvDvbsPol_mAcq_Priv::mDeleteMuxesFromCurrentNIT(void)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0 , i = 0;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

	for(i = NoOfTSTables; i > 0; i--)
	{
		pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
		if((pgdb_GetByIndex(PTC_TABLE, (i-1), (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
		{	/*Check if this TS table present in SDSD list*/
			if(mIsTSPresentInSDSDList(&tmptsdata) == FALSE)			
			{
				if(mDeleteAllServicesFromCarrier(tmptsdata.Tpid) == TRUE)
				{
					TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d> tsid: %d\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization, tmptsdata.Tsid);
					pgdb_Delete(PTC_TABLE, (Address) &tmptsdata);
				}
				else
				{
					tmptsdata.SDSDFrequency = 0;
					pgdb_Update(PTC_TABLE, (Address) &tmptsdata);
					
				}
			}
		}
	}

}

Bool CHsvDvbsPol_mAcq_Priv::mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	Bool RetVal = FALSE;
	int i;

	/*In Homing mode, check by using strapi and in Fallback mode, check in saved list*/
	if(DataAcqInstance.Mode == Homing)
	{
		if(strapi_GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, nit), tmptsdata->OriginalNetworkId, tmptsdata->Tsid, tmptsdata->NetworkId, (void *)(&tmpsdsd)) == TRUE)
		{
			RetVal = TRUE;
		}
	}
	else
	{
		for (i = 0; i < mPolDSDesc.NumOfSDSD; i++)
		{
			if((tmptsdata->OriginalNetworkId == mPolDSDesc.SatDesc[i].Original_NetworkId) && (tmptsdata->Tsid == mPolDSDesc.SatDesc[i].Tsid))
			{
				RetVal = TRUE;
				break;
			}
		}
	}
	return RetVal;
}

/*Keyupdate reason indicates if any key(freq/pol) is updated in SDSD or due to Acq. mode change.  
if Acq mode changed in update install, ptc frequnecy may change as tuner will not be locked to 
exact SDSD freq, in this case old ferquency is retained. If SDSD freq\pol. is changed 
then old TPID entry is deleted and new entry is added with new freq\pol and oldTPID is returned*/
void CHsvDvbsPol_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, KeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData)
{

	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0 , i = 0;
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);

	/* Filling attributes from ptc, and acqinstance */
	tsdata.Frequency					= ptc->Frequency;
	tsdata.SymbolRate				= ptc->SymbolRate;

	tsdata.OriginalNetworkId			= DataAcqInstance.Onid;
	tsdata.Tsid						= DataAcqInstance.Tsid;
	tsdata.NetworkId					= DataAcqInstance.NetworkId;
	tsdata.ModulationType			= ptc->ModulationType;
	
	tsdata.Bandwidth			= ptc->ChannelBandwidth;
	
	tsdata.PtcListVersion			= isvcscandata_GetInstallationVersion();
	tsdata.SDSDFrequency			= ptc->SDSDFrequency;
	tsdata.UserInstalled			= IsManualInstall();
	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Polarization				= ptc->Polarization;
	tsdata.Tpid						= ptc->TPID;
	tsdata.IqMode					= ptc->ModulationStd;
	tsdata.CodeRate					= ptc->CodeRate;

	tmptsdata.LnbNumber			= tsdata.LnbNumber;
	tmptsdata.Frequency			= tsdata.Frequency;
	tmptsdata.Polarization			= tsdata.Polarization;

	/* check entry already present. If yes update else add */
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE )
	{
		/*If GetByKey is failed, check if any Keys(Frequency/polarization) are updated */
		if(IsUpdateInstall() == TRUE)
		{
			NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

			for(i = 0; i<NoOfTSTables; i++)
			{
				pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
				
				if(pgdb_GetByIndex(PTC_TABLE, i, (Address)&tmptsdata) == TRUE)
				{
					if((tmptsdata.OriginalNetworkId == tsdata.OriginalNetworkId) && (tmptsdata.Tsid == tsdata.Tsid))
					{
						/*Return old Keys and TS table*/
						OldTsData->LnbNumber = tmptsdata.LnbNumber;
						OldTsData->Frequency = tmptsdata.Frequency;
						OldTsData->Polarization = tmptsdata.Polarization;
						pgdb_GetByKey(PTC_TABLE, (Address )OldTsData);
						/*Check if pol&lnb are same and frequency is different and difference is with in the tolerance*/
						if( ((tmptsdata.LnbNumber == tsdata.LnbNumber) && (tmptsdata.Polarization == tsdata.Polarization)) && 
							(ABS(tmptsdata.Frequency, tsdata.Frequency) < FREQ_DRIFT_TOLERANCE))
						{
							*KeyUpdate = AcqModeChange;
							tsdata.Frequency	= tmptsdata.Frequency;
							tsdata.Tpid		= tmptsdata.Tpid;
							pgdb_Update(PTC_TABLE, (Address )&tsdata);
							break;
							
						}
						else
						{
							*KeyUpdate = SDSDChange;
				
							/*Delete the Old TS Table with old TPID and Add new TS Table with updated TPID and keys */
							pgdb_Delete(PTC_TABLE, (Address)&tmptsdata);
							TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization);
							pgdb_Add(PTC_TABLE, (Address )&tsdata);
							TraceNotice (m, "Addition to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization);
							break;
						}
						
					}
				}
			}
			/*It is a New TS, Add to TS table*/
			if(i == NoOfTSTables)
			{
				pgdb_Add(PTC_TABLE, (Address )&tsdata);
			}
		}
		else
		{
			/*In Auto install, Add to TS table*/		
			pgdb_Add(PTC_TABLE, (Address )&tsdata);
		}

	}
	else
	{
		//TraceNotice (m, "Updation to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.StreamPriority);
		pgdb_Update(PTC_TABLE, (Address )&tsdata);
	}
}

Bool CHsvDvbsPol_mAcq_Priv::mInstallHomingMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	HSVSPTYPE(ActualServiceList, dvb, nit) servicelist;
	SvcListInfo	SeviceListInfo;;
	int		i, from = 0, to = 0,InstalledServices = 0;	
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);

	if(strapi_GetRangeByKey(HsvMain, GETPID_SLD(PackageId), 2, DataAcqInstance.Onid, DataAcqInstance.Tsid, 0, &from, &to) == TRUE)
	{
		TraceNotice (m, "%s %d NoOfServices in MUX = %d ONID = %d TSID = %d \n",__FUNCTION__, __LINE__, ((to - from)+1),DataAcqInstance.Onid, DataAcqInstance.Tsid);

		/* From strapi get all the services and add/update in SERVICE_TABLE */
		for(i = to; i >= from ; i--)
		{
				if(strapi_GetByIndex(HsvMain, GETPID_SLD(PackageId), i, (void *)(&servicelist)) == TRUE)
				{
					SeviceListInfo.Onid        = servicelist.Original_NetworkId;
					SeviceListInfo.Tsid        = servicelist.Tsid;
					SeviceListInfo.ServiceId   = servicelist.ServiceId;
					SeviceListInfo.ServiceType = mConvertToPgdatServiceType(servicelist.ServiceType);
					SeviceListInfo.NetworkId	= servicelist.NetworkId;
					if(mCheckServiceForInstall(&ptc, KeyUpdate, OldTsData,&SeviceListInfo))
					{
						InstalledServices++;
						retval = TRUE;
					}
				}
		}

	}
	else
	{
		TraceNotice(m, "No services found in service list of ONID = %d TSID = %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);
	}
	
	if(IsUpdateInstall())
	{
		if (KeyUpdate == SDSDChange)
		{
			/*Here OldTPID will remain with non transmitted services*/
			mDeleteAllServicesFromCarrier(OldTsData->Tpid);
		}
		else
		{
			mDeleteServicesCurrentCarrier(&ptc);
		}
	}

	TraceNotice (m, "Homing Mode: Updateprint: Num TV: %d Num Radio: %d \n", mDigitalTvChannelsFound, mDigitalRadioChannelsFound);

       return retval;
}


Bool CHsvDvbsPol_mAcq_Priv::mInstallFallbackMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	int		i, InstalledServices = 0;

	for(i = 0; i <= mSvcListData.NumOfRecords ; i++)
	{
		if((mSvcListData.mSvcListInfo[i].Onid == DataAcqInstance.Onid) && (mSvcListData.mSvcListInfo[i].Tsid == DataAcqInstance.Tsid))
		{
			if(mCheckServiceForInstall(&ptc, KeyUpdate, OldTsData,&mSvcListData.mSvcListInfo[i]))
			{
				InstalledServices++;				
				retval = TRUE;
			}
		}
	}

	if(IsUpdateInstall())
	{
		if (KeyUpdate == SDSDChange)
		{
			/*Here OldTPID will remain with non transmitted services*/
			mDeleteAllServicesFromCarrier(OldTsData->Tpid);
		}
		else
		{
			mDeleteServicesCurrentCarrier(&ptc);
		}
	}

	TraceNotice (m, "Fallback Mode: Updateprint: Num TV: %d Num Radio: %d \n", mDigitalTvChannelsFound, mDigitalRadioChannelsFound);
	TraceNotice(m, "Installed %d services\n", InstalledServices);

       return retval;
}


Bool CHsvDvbsPol_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC *ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData, SvcListInfo *ServiceList)
{
	Bool	retval = FALSE, channelExists = FALSE, IsDuplicatesvc = FALSE, IsServiceAdded = FALSE, ToAdd = FALSE;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvPgdatDigServiceData 		svcdat, tempsvcdat;
	HsvPgdatPresetData			presetData;	

	IsDuplicatesvc = FALSE;
	IsServiceAdded = FALSE;
	ToAdd = FALSE;
	pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

	/*If db key(TPID) is updated, delete the service and add it again with new TPID (as TPID is the key for service table)*/
	if(KeyUpdate == SDSDChange)
	{
		svcdat.Tpid = OldTsData->Tpid;
		svcdat.ServiceId = ServiceList->ServiceId;

		if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat) == TRUE)
		{
			IsDuplicatesvc = TRUE;
		}
        PrintfNotice("SDSD Change");
	}
	/*TODO: check if it can be moved to installmux*/
	if(KeyUpdate == AcqModeChange)
	{
		ptc->Frequency = OldTsData->Frequency;
		ptc->TPID = OldTsData->Tpid;
        PrintfNotice("Acq Mode changed");
	}

	svcdat.Frequency		  = ptc->Frequency;
	svcdat.OriginalNetworkId = DataAcqInstance.Onid;
	svcdat.Tsid 			  = DataAcqInstance.Tsid;
	svcdat.LnbNumber 		  = ptc->LnbNumber;
	svcdat.Polarization 		  = ptc->Polarization;
	svcdat.Tpid	       	  = ptc->TPID;
	svcdat.ServiceId		= ServiceList->ServiceId;
	svcdat.NetworkId		=   ServiceList->NetworkId;
	svcdat.SDSDFrequency	= ptc->SDSDFrequency;


	/*If Get Entry from SDT Actual fails check in SDT other*/
	if(strapi_GetByKey(HsvMain, HSVSPID(ActualTSService, dvb, sdt), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == FALSE)
	{
		if((DataAcqInstance.Mode == Homing) && 
			(strapi_GetByKey(HsvMain, HSVSPID(OtherSDTSection, dvb, sdt), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == TRUE))
		{
			ToAdd = TRUE;
//			PrintfNotice("SDT OTHER avilable for svcid: %d, svctype: %d",service.ServiceId,service.ServiceType);
		}
		else
			{
				PrintfNotice("SDT Actual and OTHER not avilable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
			}
	}
	else
	{
		ToAdd = TRUE;
		PrintfNotice("SDT ACTUAL avilable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
	}

	if(mIsServiceInstallable(&service) == FALSE)
	{
		ToAdd = FALSE;
		PrintfNotice("service is not installable onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
	}


	if(ToAdd == TRUE)
	{
//		TraceNotice (m, " SDT:SvcId %d and SvcType %d \n", service.ServiceId, service.ServiceType);
		mAssignLCN(&svcdat);
		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		if(channelExists)
		{
			TraceNotice (m, " Channel exists SvcId %d and SvcType %d \n", service.ServiceId, service.ServiceType);
			/* If entry already present update the service data */
			mUpdateService(&svcdat, ptc, &service);
			retval = TRUE;	

		}
		else
		{
			mAddNewService(&svcdat, ptc, &service,IsDuplicatesvc);
			IsServiceAdded = TRUE;
			retval = TRUE;
		}
		
	}
	else
	{
		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		if(channelExists)
		{
			if (IsDigitalTvChannel (&tempsvcdat))
			{
				removeCurTv++;
			}
			else if (IsDigitalRadioService (&tempsvcdat))
			{
				removeCurRadio++;
			}

			presetData.PresetNumber = tempsvcdat.PresetNumber;
			pgdb_Delete(SERVICE_TABLE, (Address)&tempsvcdat);
			TraceNotice (m, " Service deleted : SvcId %d and SvcType %d \n", service.ServiceId, service.ServiceType);
			
			if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
			{
				pgdb_Delete(PRESET_TABLE, (Address)&presetData);
			}				
		}
	}
	if(IsDuplicatesvc )
	{
        Bool Proceed = FALSE;
		Nat32 PackageId;
		PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
		/*Delete the duplicate service with old TPID,svcid*/
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
		tempsvcdat.Tpid = OldTsData->Tpid;
		tempsvcdat.ServiceId = ServiceList->ServiceId;
		pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		Proceed = (!VALID_LCN_RANGE(tempsvcdat.LCN,PackageId))&&(IS_RADIO_SERVICE(tempsvcdat.ServiceType) != IS_RADIO_SERVICE(svcdat.ServiceType));
        REVALIDATE(tempsvcdat.LCN);
		Proceed |= ((VALID_LCN_RANGE(tempsvcdat.LCN,PackageId) || VALID_LCN_RANGE(svcdat.LCN,PackageId)) && (tempsvcdat.LCN != svcdat.LCN));
		 if(Proceed)
		 {
			TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, tempsvcdat.LCN, svcdat.LCN, svcdat.PresetNumber);
			presetData.PresetNumber =   svcdat.PresetNumber;						
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
			svcdat.PresetNumber = INVALID_PRESET;
            pgdb_Update(SERVICE_TABLE, (Address )&svcdat);            
		 }
		/*Delete duplicate service if it is added with new parameters*/
		if(IsServiceAdded == TRUE)
		{
			TraceNotice(m,"%s %d deleted service =>  svcid %d PresetNumber %d", __FUNCTION__, __LINE__,  tempsvcdat.ServiceId, tempsvcdat.PresetNumber);
			pgdb_Delete(SERVICE_TABLE, (Address )&tempsvcdat);
		}
	}
	return retval;
}



void CHsvDvbsPol_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;
	
	TempSvcData.Tpid 		 = ptc->TPID;
	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{
		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			if ( RetVal == TRUE && (mIsSvcPresentInServiceList(&TempSvcData) == FALSE) &&
							 (TempSvcData.SDSDFrequency != 0)) /* Dont delete services installed by generic module*/
			{
				TraceNotice (m, "Delete services Ser-id[%d] Tsid[%d] Onid[%d]",
							TempSvcData.ServiceId,
							TempSvcData.Tsid,
							TempSvcData.OriginalNetworkId );

				if (IsDigitalTvChannel (&TempSvcData))
				{
					removeCurTv++;
				}
				else if (IsDigitalRadioService (&TempSvcData))
				{
					removeCurRadio++;
				}
				presetData.PresetNumber = TempSvcData.PresetNumber;
				pgdb_Delete(SERVICE_TABLE, (Address)&TempSvcData);
				
				if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
				{
					pgdb_Delete(PRESET_TABLE, (Address)&presetData);
				}				
			}
		}
	}
}

Bool CHsvDvbsPol_mAcq_Priv::mIsSvcPresentInServiceList(HsvPgdatDigServiceData *svcdata)
{
	Bool retval = FALSE;
	HSVSPTYPE(ActualServiceList, dvb, nit) service;
	int i;
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	/*In Homing mode, check from strapi. In Fallback mode, check in stored list*/
	if(DataAcqInstance.Mode == Homing)
	{
		if(strapi_GetByKey(HsvMain, GETPID_SLD(PackageId),svcdata->OriginalNetworkId, svcdata->Tsid,svcdata->ServiceId, (Address)(&service)) == TRUE)
		{
			retval = TRUE; 	
		}
	}
	else
	{
		for (i = 0; i < mSvcListData.NumOfRecords; i++)
		{
			if((svcdata->OriginalNetworkId == mSvcListData.mSvcListInfo[i].Onid) && (svcdata->Tsid == mSvcListData.mSvcListInfo[i].Tsid) && (svcdata->ServiceId == mSvcListData.mSvcListInfo[i].ServiceId))
			{
				retval = TRUE;
				break;
			}
		}
	}
	return retval;
}

int CHsvDvbsPol_mAcq_Priv::mDeleteAllServicesFromCarrier(int TPID)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;
	int 							ret = TRUE;

	TempSvcData.Tpid 		 = TPID;

	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{
		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			if ( RetVal == TRUE)
			{
				if(TempSvcData.SDSDFrequency != 0)
				{
					if (IsDigitalTvChannel (&TempSvcData))
					{
						removeCurTv++;
					}
					else if (IsDigitalRadioService (&TempSvcData))
					{
						removeCurRadio++;
					}

					presetData.PresetNumber = TempSvcData.PresetNumber;
					TraceNotice (m, "Deleted service Ser-id[%d] Tsid[%d] Onid[%d]",
					TempSvcData.ServiceId,
					TempSvcData.Tsid,
					TempSvcData.OriginalNetworkId );

					pgdb_Delete(SERVICE_TABLE, (Address)&TempSvcData);
					
					if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
					{
						pgdb_Delete(PRESET_TABLE, (Address)&presetData);
					}
				}
				else
				{
					ret = FALSE;
				}
			}
		}
	}

	return ret;
}

void CHsvDvbsPol_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
	mAssignSvcNonBroadcastAttributes(psvcdat);
	mUpdateSatelliteName (psvcdat);

	pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
		
	TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbsPol_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;

	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
	}
}

void CHsvDvbsPol_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool IsDuplicatesvc)
{
	Nat8	ToAdd = FALSE;
	HsvPgdatPresetData			PresetData;	

	/* Filling details of service, then adding it */	
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
	mUpdateSatelliteName (psvcdat);
	
	/*User attributes should be retained for duplicate service*/
	if(IsDuplicatesvc == FALSE)
	{
		mAssignSvcNonBroadcastAttributes(psvcdat);
	}

	/* Check service is TV or Radio */
	if (IsDigitalTvChannel (psvcdat))
	{
		ToAdd = TRUE;
		/*If the service is duplicate service (i.e. if any keys are updated in svc table)*/
		if(IsDuplicatesvc == FALSE)
		{			
			mDigitalTvChannelsFound++;
			mDigitalChannelsFound++;

		}
	}
	else if (IsDigitalRadioService (psvcdat))
	{
		ToAdd = TRUE;
		if(IsDuplicatesvc == FALSE)
		{			
			mDigitalRadioChannelsFound++;
			mDigitalChannelsFound++;
		}
	}

	/* Add to service table */
	if (ToAdd == TRUE)
	{
		/* Add only if its TV or Radio Service */
		pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
		TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d SystemHidden = %d\n",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId,psvcdat->SystemHidden);
		
	}

	/*If it is duplicate service Update the Preset table with new parameters*/
	if(IsDuplicatesvc && ToAdd)
	{
		PresetData.PresetNumber = psvcdat->PresetNumber;
		if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&PresetData))
		{
			PresetData.OriginalNetworkId = psvcdat->OriginalNetworkId;
			PresetData.ServiceId = psvcdat->ServiceId;
			PresetData.Tsid = psvcdat->Tsid;
			PresetData.Tpid = psvcdat->Tpid;
			PresetData.Frequency = psvcdat->Frequency;
			PresetData.Polarization = psvcdat->Polarization;
			PresetData.LnbNumber = psvcdat->LnbNumber;
			pgdb_Update(PRESET_TABLE, (Address)&PresetData);
		}				
	}
}

Bool CHsvDvbsPol_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}


void CHsvDvbsPol_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	psvcdat->ModulationType        =   ptc->ModulationType;
	psvcdat->Bandwidth	   =   ptc->ChannelBandwidth;
	
	psvcdat->SymbolRate            =   ptc->SymbolRate;
	psvcdat->LnbNumber			   =   ptc->LnbNumber;
	psvcdat->Polarization		   =   ptc->Polarization;
	psvcdat->Tpid				   =   ptc->TPID;
	psvcdat->AudioPid              =   INVALID_PID;
	psvcdat->VideoPid              =   INVALID_PID;
	psvcdat->PcrPid                =   INVALID_PID;
	psvcdat->ServiceType           =   mConvertToPgdatServiceType(service->ServiceType);
	
	psvcdat->FreeCiMode	    	   =   service->Free_Ci_Mode;
	psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
	psvcdat->NumBrandIds           =   service->NumBrandIds;
	mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds );

	psvcdat->ScramblingStatus		= 0; 
	if(service->Free_CA_Mode == TRUE)
	{
		psvcdat->ScramblingStatus = 1;
	}

	mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_PresetNameLength - 1) );

	psvcdat->NumericSelect = TRUE;
	psvcdat->SystemHidden = !(psvcdat->VisibleService);


}

void CHsvDvbsPol_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
	int mode, state;
	Bool Proceed = FALSE;
	HsvPgdatPresetData			presetData;		
	HsvPgdatDigServiceData		svcdat;

	rins_GetCurrentInstallationState(&mode, &state);
	
	psvcdat->UserHidden             = FALSE;
	psvcdat->ChannelLock		    = FALSE;
	psvcdat->Favorite			    = FALSE;
	
	psvcdat->DateStamp			    = 0;
	psvcdat->PresetNumber		    = INVALID_PRESET;
	psvcdat->ServiceListVersion     = isvcscandata_GetInstallationVersion();
	psvcdat->NewPreset				= (mode == AUTO_MODE)? FALSE : TRUE;
	psvcdat->HbbTvOption 		= 1;
	if( CYFRAPLUS_POLSAT_PACKAGE_ID == insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId))
	{
		psvcdat->PackageGroup     		= CYFRAPLUS_POLSAT_MATCH_SETTINGS_DB_PACKAGE_ID;
	} else {
		psvcdat->PackageGroup			=	CYFROWY_POLSAT_MATCH_SETTINGS_DB_PACKAGE_ID;
	}
	

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
	{
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	
		psvcdat->NewPreset				= svcdat.NewPreset;
		
		psvcdat->ChannelLock			= svcdat.ChannelLock;;
		psvcdat->UserHidden				= svcdat.UserHidden;
		psvcdat->Favorite				= svcdat.Favorite;
		psvcdat->ServiceListVersion     = svcdat.ServiceListVersion;
		psvcdat->HbbTvOption			= svcdat.HbbTvOption;
		
		psvcdat->DeltaVolume			= svcdat.DeltaVolume;
		psvcdat->UserModifiedName				= svcdat.UserModifiedName;
		psvcdat->FavoriteNumber			= svcdat.FavoriteNumber;
		
		psvcdat->LogoURL				= svcdat.LogoURL;
		psvcdat->PresetNumber		    = svcdat.PresetNumber;
		psvcdat->PackageGroup		   =  svcdat.PackageGroup;
		if (mCompareUnicodeString(psvcdat->ChannelName, svcdat.ChannelName) == FALSE)
		{
			TraceNotice(m, "Service name updated");
			psvcdat->LogoURL = 0;
		}
		else
		{
			TraceNotice(m, "Service name is same");
		}

		Proceed = (!VALID_LCN_RANGE(svcdat.LCN,PackageId))&&(IS_RADIO_SERVICE(psvcdat->ServiceType) != IS_RADIO_SERVICE(svcdat.ServiceType));
		REVALIDATE(svcdat.LCN);
		Proceed |= ((VALID_LCN_RANGE(psvcdat->LCN,PackageId) || VALID_LCN_RANGE(svcdat.LCN,PackageId)) && (psvcdat->LCN != svcdat.LCN));
		 if(Proceed)
		 {
			TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->LCN, svcdat.LCN, svcdat.PresetNumber);
			presetData.PresetNumber =   svcdat.PresetNumber;						
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
			psvcdat->PresetNumber = INVALID_PRESET;		 
		 }
               memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
	}

	    if( Timerclk_IsClockDefined())
		{
			psvcdat->DateStamp = Timerclk_GetUniversalTime();
		}

}


int CHsvDvbsPol_mAcq_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
{
	double	Bandwidth = 0;

	if (IS_VALID_ROLLOFF(RollOff))
	{
		/* SB = SR(1+Ro) */
		Bandwidth = SymbolRate * (1+RollOffTable[RollOff]);
	}
	Bandwidth /= 1000;	/* To make it in KHz */
	UNUSED (FECInner);

	return (Nat8)Bandwidth;
}

int CHsvDvbsPol_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
{
	int retval = servicetype;
    switch(servicetype)
    {
        case TelevisionService:     
            retval  =   AppApiTelevisionService;
            break;
        case RadioService:
            retval  =   AppApiRadioService;
            break;
        case AdvCodecRadioService:    
            retval  =   AppApiAdvCodecRadioService;
            break;
        case TeletextService:         
            retval  =   AppApiTeletextService;
            break;
        case NVODTimeShiftedService:         
            retval  =   AppApiNVODTimeshiftedService;
            break;
        case NVODReferenceService:         
            retval  =   AppApiNVODReferenceService;
            break;
        case MosaicService:        
            retval  =   AppApiMosaicService;
            break;
        case DatabroadcastService:        
            retval  =   AppApiDatabroadcastService;
            break;
        case DVBMHPService:        
            retval  =   AppApiDVBMHPService;
            break;
        case MPEG2HDService:        
            retval  =   AppApiMPEG2HDService;
            break;
        case AdvCodecSDTelevisionService:        
            retval  =   AppApiAdvCodecSDTelevisionService;
            break;
        case AdvCodecSDNVODTimeShiftedService:        
            retval  =   AppApiAdvCodecSDNVODTimeShiftedService;
            break;
        case AdvCodecSDNVODReferenceService:        
            retval  =   AppApiAdvCodecSDNVODReferenceService;
            break;
        case AdvCodecHDTelevisionService:        
            retval  =   AppApiAdvCodecHDTelevisionService;
            break;
        case AdvCodecHDNVODTimeShiftedService:        
            retval  =   AppApiAdvCodecHDNVODTimeShiftedService;
            break;
        case AdvCodecHDNVODReferenceService:        
            retval  =   AppApiAdvCodecHDNVODReferenceService;
            break;
	case	0x1C:
			retval  =   AppApiTelevisionService;
			break;
        default:
            break;
    }
    return retval;
}

Bool CHsvDvbsPol_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	switch (psvcdat->ServiceType)
	{
	case	AppApiTelevisionService:
	case	AppApiTeletextService:
	case	AppApiMPEG2HDService:
	case	AppApiAdvCodecHDTelevisionService:
	case	AppApiAdvCodecSDTelevisionService:
	case	AppApiHevcService:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsPol_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsPol_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}


Bool CHsvDvbsPol_mAcq_Priv::mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	/* check service type*/
	Bool					lRetVal = FALSE;
	switch(service->ServiceType)
	{
	case TelevisionService:
	case RadioService:
	case TeletextService:
	case AdvCodecRadioService:
	case MPEG2HDService:
	case AdvCodecSDTelevisionService:
	case AdvCodecHDTelevisionService:
	case 0x1C:
	case AppApiHevcService:
		lRetVal = TRUE;
		break;
	default:
		break;
	}
	return lRetVal;	    
}

void CHsvDvbsPol_mAcq_Priv::mCollectSdsds (void)
{
	int i =0;

	mPolDSDesc.NumOfSDSD = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
	for(i = 0; i < mPolDSDesc.NumOfSDSD; i++)
	{
		strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&(mPolDSDesc.SatDesc[i])));
	}

	DataAcqInstance.CurSdsd = 0;
	DataAcqInstance.NumSdsds = 	mPolDSDesc.NumOfSDSD;
	TraceNotice (m," DataAcqInstance.NumSdsds %d \n",DataAcqInstance.NumSdsds);
}

void CHsvDvbsPol_mAcq_Priv::mCollectServicelistData(void)
{
	HSVSPTYPE(ActualServiceList, dvb, nit) svcList;
	int i = 0, numOfEntries = 0;
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	
	numOfEntries = strapi_GetSize(HsvMain, GETPID_SLD(PackageId));
	mSvcListData.NumOfRecords = 0;
	for(i = 0 ; i < numOfEntries; i++)
	{
		if(strapi_GetByIndex(HsvMain, GETPID_SLD(PackageId), i, (void*)(&svcList)))
		{
			mSvcListData.mSvcListInfo[i].Onid        = svcList.Original_NetworkId;
			mSvcListData.mSvcListInfo[i].Tsid        = svcList.Tsid;
			mSvcListData.mSvcListInfo[i].ServiceId   = svcList.ServiceId;
			mSvcListData.mSvcListInfo[i].ServiceType = mConvertToPgdatServiceType(svcList.ServiceType);
			mSvcListData.mSvcListInfo[i].NetworkId	= svcList.NetworkId;

			mSvcListData.NumOfRecords++;
			mSvcListData.VersionNumber = svcList.VersionNumber;
		}
		else
		{

		}
	}
}

Bool CHsvDvbsPol_mAcq_Priv::mGetLCN(t_LCNInfo *LCNInfo)
{
    Bool retval = FALSE;
    
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	
	if(PackageId == CYFROWY_POLSAT_PACKAGE_ID)
	{
		retval = mLcnCyfrowyData(HSVSPID(ActualNetworkLCN3,dvb,nit), LCNInfo, FALSE);
	}
    else if(PackageId == CYFRAPLUS_POLSAT_PACKAGE_ID)
    {
        retval = mLcnCyfraplusData(HSVSPID(batLCN2, dvb, bat), LCNInfo, FALSE);
    }

    return retval;

}
Bool CHsvDvbsPol_mAcq_Priv::mAcquireLCNData(void)
{
    Bool retval = FALSE;
    int TableId =  ACTUAL_TABLE;
    t_LCNInfo LCNInfo;
	
    Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	
	if(PackageId == CYFROWY_POLSAT_PACKAGE_ID)
	{
		retval = mLcnCyfrowyData(HSVSPID(ActualNetworkLCN3,dvb,nit), &LCNInfo, TRUE);
	}
    else if(PackageId == CYFRAPLUS_POLSAT_PACKAGE_ID)
    {
        retval = mLcnCyfraplusData(HSVSPID(batLCN2, dvb, bat), &LCNInfo, TRUE);
    }

    return retval;

}

Bool CHsvDvbsPol_mAcq_Priv::mLcnCyfraplusData(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HsvPid);
    HSVSPTYPE(batLCN2, dvb, bat) nwlcn;

    if( AcquireAll == TRUE )
    {
        for(i = 0; i < numOfRecords; i++)
        {
            if( (strapi_GetByIndex(HsvMain, HsvPid, i, (Address)(&nwlcn)) == TRUE) )
            {
                retval = TRUE;
                if(mPopulateLCN((Address)(&nwlcn), VERSION_CYFRAPLUS) == FALSE)
                {
                    break;
                }
            }
        }
    }
    else
    {
        if( (strapi_GetByKey(HsvMain, HsvPid, LCNInfo->Onid, LCNInfo->Tsid, LCNInfo->ServiceId, &nwlcn) == TRUE) )
        {
            mCopyLCNInfo( LCNInfo, nwlcn.Original_NetworkId, nwlcn.Tsid, nwlcn.ServiceId, nwlcn.LogicalChannelNum, \
                    nwlcn.VisibleService, VERSION_CYFRAPLUS);
            retval = TRUE;
        }
    }
    return retval;
}

Bool CHsvDvbsPol_mAcq_Priv::mLcnCyfrowyData(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HsvPid);
    HsvNITLCN3 nwlcn;

    if( AcquireAll == TRUE )
    {
        for(i = 0; i < numOfRecords; i++)
        {
            if( (strapi_GetByIndex(HsvMain, HsvPid, i, (Address)(&nwlcn)) == TRUE) )
            {
                retval = TRUE;
                if(mPopulateLCN((Address)(&nwlcn), VERSION_CYFROWY) == FALSE)
                {
                    break;
                }
            }
        }
    }
    else
    {
        if( (strapi_GetByKey(HsvMain, HsvPid, LCNInfo->Onid, LCNInfo->Tsid, LCNInfo->ServiceId, &nwlcn) == TRUE) )
        {
            mCopyLCNInfo( LCNInfo, nwlcn.Original_NetworkId, nwlcn.Tsid, nwlcn.ServiceId, nwlcn.LogicalChannelNum, \
                    nwlcn.VisibleService, VERSION_CYFROWY);
            retval = TRUE;
        }
    }
    return retval;
}

Bool CHsvDvbsPol_mAcq_Priv::mPopulateLCN(Address data, int version)
{
    int cacheIndex = 0;
    Bool retval = TRUE;
    HSVSPTYPE(batLCN2, dvb, bat) *nwlcn;
    HsvNITLCN3 *nwlcn3;

    switch(version)
    {
        case VERSION_CYFRAPLUS:
            nwlcn = (HSVSPTYPE(batLCN2, dvb, bat) *)data;
            cacheIndex = mGetLCNIndex(nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId);
			if((cacheIndex >= mLCNData.NumOfLCNRecords)&&(mLCNData.NumOfLCNRecords < MAX_LCN_NUMBERS))
			{
				mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId, \
						nwlcn->LogicalChannelNum, nwlcn->VisibleService, version);
				mLCNData.VersionNumber = nwlcn->VersionNumber; 
                mLCNData.NumOfLCNRecords++;
            }
            break;
        case VERSION_CYFROWY:
            nwlcn3 = (HsvNITLCN3 *)data;
            cacheIndex = mGetLCNIndex(nwlcn3->Original_NetworkId, nwlcn3->Tsid, nwlcn3->ServiceId);
			if((cacheIndex >= mLCNData.NumOfLCNRecords)&&(mLCNData.NumOfLCNRecords < MAX_LCN_NUMBERS))
			{
				mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwlcn3->Original_NetworkId, nwlcn3->Tsid, nwlcn3->ServiceId, \
						nwlcn3->LogicalChannelNum, nwlcn3->VisibleService, version);
				mLCNData.VersionNumber = nwlcn3->VersionNumber; 
                mLCNData.NumOfLCNRecords++;
            }
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    if(mLCNData.NumOfLCNRecords == MAX_LCN_NUMBERS)
    {
        ASSERT(!"Increase the number of LCN records");
        retval = FALSE;
    }

    return retval;
}



inline void CHsvDvbsPol_mAcq_Priv::mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version)
{
    LCNInfo->Onid              = OnId;
    LCNInfo->Tsid              = TsId;
    LCNInfo->ServiceId         = SvcId;
    LCNInfo->LogicalChannelNum = Lcn;
    LCNInfo->VisibleService    = VisibleSvc;
    LCNInfo->LCNType           = version;
}

void CHsvDvbsPol_mAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
    t_LCNInfo LCNInfo;
    int cacheIndex = 0;
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);

    if(mLCNData.NumOfLCNRecords == 0)
    {
        LCNInfo.Onid = psvcdat->OriginalNetworkId; LCNInfo.Tsid = psvcdat->Tsid; LCNInfo.ServiceId = psvcdat->ServiceId; //keys to get the LCN frm strapi records 
        if(mGetLCN(&LCNInfo) == TRUE)
        {
            psvcdat->LCN = (VALID_LCN_RANGE(LCNInfo.LogicalChannelNum,PackageId) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
            psvcdat->VisibleService = LCNInfo.VisibleService;

        }
    }
    else
    {
        cacheIndex = mGetLCNIndex(psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
        if(cacheIndex != mLCNData.NumOfLCNRecords)
        {
            psvcdat->LCN = (VALID_LCN_RANGE(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum,PackageId) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;
            psvcdat->VisibleService = mLCNData.mLCNInfo[cacheIndex].VisibleService;

        }
    }
}

inline int CHsvDvbsPol_mAcq_Priv::mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId)
{
    int i = 0;

    for( i = 0; i < mLCNData.NumOfLCNRecords; i++)
    {
        if((mLCNData.mLCNInfo[i].Onid == Onid) && (mLCNData.mLCNInfo[i].Tsid == Tsid) && (mLCNData.mLCNInfo[i].ServiceId == ServiceId))
        {
            break;
        }
    }
    return i;
}


void CHsvDvbsPol_mAcq_Priv::mGetSDTOtherStatus(void)
{
	int Size = 0;
	DataAcqInstance.SDTOtherPresent = FALSE;
	
	Size = strapi_GetSize (HsvMain, HSVSPID(OtherSDTSection, dvb, sdt));
	if(Size != 0)
	{
		DataAcqInstance.SDTOtherPresent = TRUE;
	}

	TraceNotice (m, " SDT OTHER present status: %d \n",DataAcqInstance.SDTOtherPresent);
}

void CHsvDvbsPol_mAcq_Priv::mGetSatelliteLnbNo(int SatId)
{
	int i;
	HsvPgdatDigSatInfoData SatDetails;
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
			DataAcqInstance.LnbNumber = i;
			break;
		}
	}
}

Bool CHsvDvbsPol_mAcq_Priv::IsManualInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsPol_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsPol_mAcq_Priv::iacqpow_Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbPol_mDataAcq" );
	
	TraceNotice (m, " Pol Acq Module pow Initialized \n");

}

void CHsvDvbsPol_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsPol_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsPol_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
    /* Resetting all the variables */
    mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
    removeCurTv = removeCurRadio = 0;
	memset(&mLCNData,0,sizeof(mLCNData));
	UNUSED(LnbNumber);
}

void CHsvDvbsPol_mAcq_Priv::idataacq_AcquireData(int Mode)
{

	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)Mode);
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);
	
	return removeCurTv;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);
	
	return removeCurRadio;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return mPolDSDesc.NumOfSDSD;
}

Bool CHsvDvbsPol_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mPolDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry,&mPolDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));
		
		mPolDSDesc.CurrentSDSDIndex = count;
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsPol_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);
	
	return RadioChannelsFound;
}

void CHsvDvbsPol_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{

}

void CHsvDvbsPol_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{

}
void CHsvDvbsPol_mAcq_Priv::idataacq_AcquireDataOnTimeout                        (   void    )
{

}

void CHsvDvbsPol_mAcq_Priv::idataacq_SyncTemporaryTableRecords			(	void	)
{

}

