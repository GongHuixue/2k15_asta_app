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
 *	C Source:		hsvdvbsins_mdataacq.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	anuma %
 *	%date_created:	Fri May 10 18:13:22 2013 %
 *
**********************************************************************/
/* include dependencies */
#include	"_hsvdvbsgeneric_mAcq.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsgeneric_mAcq")

/****************************************************************************
 * Macros and types
 ****************************************************************************/


/* Macros */












/****************************************************************************
 * Static variables
 ****************************************************************************/

int CHsvDvbsGeneric_mAcq_Priv::s__mDigitalTvChannelsFoundInLnb[MAX_LNBS_SUPPORTED],CHsvDvbsGeneric_mAcq_Priv::s__mDigitalRadioChannelsFoundInLnb[MAX_LNBS_SUPPORTED];

int CHsvDvbsGeneric_mAcq_Priv::s__mDigitalTranspondersFound = 0;

int CHsvDvbsGeneric_mAcq_Priv::s__mCurrentLnb = 0,CHsvDvbsGeneric_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsGeneric_mAcq_Priv::s__mDigitalUserDefinedChannelsFound = 0;

Pump CHsvDvbsGeneric_mAcq_Priv::s__mDataAcqPump;

int CHsvDvbsGeneric_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsGeneric_mAcq_Priv::s__removeCurRadio =0;

HsvDataAcqInstance CHsvDvbsGeneric_mAcq_Priv::s__DataAcqInstance;

Nat16 CHsvDvbsGeneric_mAcq_Priv::s__NumTvServicesInMux = 0,CHsvDvbsGeneric_mAcq_Priv::s__NumRadioServicesInMux = 0,CHsvDvbsGeneric_mAcq_Priv::s__NumTvServicesremoved = 0,CHsvDvbsGeneric_mAcq_Priv::s__NumRadioServicesRemoved = 0;


Nat16 CHsvDvbsGeneric_mAcq_Priv::s__mUnicodeBuffer[11];


int CHsvDvbsGeneric_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID][2] = 
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










/*static void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp);
static void mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp);*/




















void CHsvDvbsGeneric_mAcq_Priv::mPumpHandler(int value, Nat32 param)
{
	UNUSED(param);
	switch(value)
	{
	case	StartDataAcq:
		mAcquireData();
		iacqN_OnDataAquired (TRUE);
		break;

	case	StartDataAcqOnTimeout:
		mAcquireDataOnTimeout ();
		iacqN_OnDataAquired (TRUE);
		break;

	case	StartBackgroundDataAcq:
		mUpdateBackgroundService ();
		iacqN_OnDataAquired (TRUE);
		break;
	
	case	StartSDSDDataAcq:
		mCollectSdsds ();
		iacqN_OnDataAquired (mSatDSDesc.NumOfSDSD != 0);
		break;
	case StartSyncRecordsForPreDefinedList:
		mSyncRecordsForPreDefinedList();
		break;
	}		
}


void CHsvDvbsGeneric_mAcq_Priv::mCollectSdsds (void)
{
	int i =0;

	mSatDSDesc.NumOfSDSD = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
	if(mSatDSDesc.NumOfSDSD > MAX_SDSD)
	{
		TraceNotice(m,"ERROR: Number of SDSDs : %d exceeds MAX_SDSD",mSatDSDesc.NumOfSDSD);
		mSatDSDesc.NumOfSDSD = MAX_SDSD; 
	}
	for(i = 0; i < mSatDSDesc.NumOfSDSD; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&(mSatDSDesc.SatDesc[i]))) == FALSE)
		{
			TraceNotice (m," Collect SDSD failed for SDSD: %d \n",i);
		}
	}

	mSatDSDesc.CurrentSDSDIndex= 0;
	TraceNotice (m," DataAcqInstance.NumSdsds %d \n",mSatDSDesc.NumOfSDSD);
}


Bool CHsvDvbsGeneric_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}


Bool CHsvDvbsGeneric_mAcq_Priv::UpdateServiceTable (Nat32 TpId)
{
	Bool	RetVal = TRUE;
	HsvPgdatDigServiceData svcdat;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	int i, TotalServices = 0;
	HsvChannel Channelinfo;
	int		TableId = ACTUAL_TABLE;

	TotalServices = strapi_GetSize (HsvMain, GETHSVSPID(SpidService, TableId));
	TraceNotice (m, "Total services %d ", TotalServices);
	for(i = TotalServices - 1; i >= 0 ; i--)
    {
        if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId), i, (void *)(&service)) == TRUE)
        {
			svcdat.Tpid = TpId;
			svcdat.ServiceId = service.ServiceId;

			if (TRUE == pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat))
			{
				TraceNotice (m, "pgdbGetByKey succesful  for serviceId %d preset %d ", svcdat.ServiceId, svcdat.PresetNumber);
				if (mCompareUnicodeString(svcdat.ChannelName, service.ServiceName) == FALSE)
				{
					Channelinfo.Type = AppApiOnePart;
					Channelinfo.Channel.OnePart = svcdat.PresetNumber;
					
					TraceNotice (m, "ChannelName update for Preset %d ", Channelinfo.Channel.OnePart);
					memcpy (svcdat.ChannelName,service.ServiceName, eurdiv_ChannelNameLength * sizeof(Nat16));
					pgdb_Update(SERVICE_TABLE,(Address)&svcdat);
					
					insN_OnEvent(IHsvSatelliteInstallationNotify_EventUpdated, 1);
					
					//pgdat3_StoreChannelDataString (Channelinfo, pgdat3_StringChannelName,  service.ServiceName, eurdiv_ChannelNameLength);
				}
				else
				{
					TraceDebug (m, " ChannelName same  for Preset %d ", Channelinfo.Channel.OnePart);
				}
			}
		}
	}

	return RetVal;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mCheckAndUpdateSdtVersion (Nat32 *TpId)
{
	Bool	VersionUpdate = FALSE;
	FResult	RetVal;
    int LnbNumber, Frequency = 0, Polarization = 0;
	HsvSource  Source;
	HsvChannel ChannelNo ;
	HsvPgdatDigTSData			TsData;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	int		TableId = ACTUAL_TABLE, i = 0;

	pgsel_GetCurrentProgram(HsvMain,&Source,&ChannelNo);
	
	TraceNotice (m, "ChannelNumber in background %d ", ChannelNo.Channel.Digit);
    RetVal = pgdat3_GetChannelDataInt(ChannelNo, pgdat3_IntLnbNumber, &LnbNumber);
    RetVal = (RetVal == err_Ok) ? pgdat3_GetChannelDataInt(ChannelNo, pgdat3_IntPolarization, &Polarization) : RetVal;
    RetVal = (RetVal == err_Ok) ? pgdat3_GetChannelDataInt(ChannelNo, pgdat3_IntFrequency, &Frequency) : RetVal;
	TraceNotice (m, " Lnb %d Pol %d Freq %d ", LnbNumber, Polarization, Frequency);
	if (RetVal == err_Ok)
	{
		TsData.LnbNumber	= LnbNumber;
		TsData.Frequency	= Frequency;
		TsData.Polarization = Polarization;

		RetVal = pgdb_GetByKey (PTC_TABLE, (Address) &TsData);
		if ((RetVal == TRUE) && (strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId), i, (void *)(&service)) == TRUE))
		{
			TraceNotice (m, "ServiceVersion %d InChannelMaps %d ", service.VersionNumber, TsData.SDTVersion);
			VersionUpdate = (service.VersionNumber != TsData.SDTVersion) ? TRUE: FALSE;
			*TpId = TsData.Tpid;
		}

		if (VersionUpdate == TRUE)
		{
			TsData.SDTVersion = service.VersionNumber;
			TsData.TSVersion = service.VersionNumber;
			pgdb_Update (PTC_TABLE, (Address) &TsData);
		}
	}

	return VersionUpdate;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mUpdateBackgroundService (void)
{
	Bool	RetVal = FALSE;
	Nat32	TpId;
	int mode, state;
	if (TRUE == mCheckAndUpdateSdtVersion (&TpId))
	{
	  	insstate_GetCurrentInstallationState(&mode, &state);
		TraceNotice (m, "Mode=[%d][%d]",mode,BACKGROUND_MODE);
		if(mode==BACKGROUND_MODE)
			{
		insN_OnEvent(insN_EventInsStarted, BACKGROUND_MODE);
		RetVal = UpdateServiceTable (TpId);
		insN_OnEvent(insN_EventInsCompleted, BACKGROUND_MODE);
			}
	}

	return RetVal;
}

/* static function impl.. */
int CHsvDvbsGeneric_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
{
	int retval = servicetype;
    switch(servicetype)
    {
        case TelevisionService:     
            retval  =   AppApiTelevisionService;
            break;
        case RadioService:
        case AdvCodecRadioService:    
            retval  =   AppApiRadioService;
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

Bool CHsvDvbsGeneric_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	/* REQUIREMENT: DVB-S2-INS-025 */
	switch (psvcdat->ServiceType)
	{
	case	AppApiTelevisionService:
	case	AppApiTeletextService:
	case	AppApiMPEG2HDService:
	case	AppApiAdvCodecHDTelevisionService:
	case	AppApiAdvCodecSDTelevisionService:
	case	AppApiSkyHD:
	case 	AppApiHevcService:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsGeneric_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = (psvcdat->ServiceType == AppApiRadioService) ? TRUE: FALSE;
	return RetVal;
}

Bool CHsvDvbsGeneric_mAcq_Priv::IsUserDefinedService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = (psvcdat->ServiceType == AppApiRadioService) ? TRUE: FALSE;
	return RetVal;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mGetTSMetaData(void)
{
    Bool	retval = FALSE;
    int		TableId = ACTUAL_TABLE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, GETHSVSPID(Onid, TableId), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(Tsid, TableId), 0, 0, 0, &DataAcqInstance.Tsid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(VerNo, TableId), 0, 0, 0, &DataAcqInstance.TsVersionNum);

	//TraceNotice (m, "ONID %d and TsId %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);

    return retval;
}

void CHsvDvbsGeneric_mAcq_Priv::FillDummySdtData (HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	service->ServiceType = TelevisionService;
	service->Free_Ci_Mode = TRUE;
	service->Match_Brand_Flag = 0;
	service->NumBrandIds = 0;	
	service->VersionNumber = 0;
	memset (service->Brand_Ids , 0x00, sizeof(service->Brand_Ids));
	//memcpy (service->ServiceName, "------",7); 
	service->ServiceName[0] = 0;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mInstallMuxOnPat (HsvInstallationPTC *ptc, int TotalServices)
{
	Bool	retval = FALSE;
	int		i, InstalledServices = 0;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvPATProgramPIDInfo					val;

	TraceNotice (m, "%s %d NoOfServices in MUX = %d\n",__FUNCTION__, __LINE__, TotalServices);
	
	if (IsManualInstall())
	{
		/* When doing SRT, SatInfo may not be present. So add the same here */
		mAddSatInfo (ptc);
		DeleteCurrentChannelEntry (ptc);
	}
	
	/* From strapi get all the services and add/update them in TEMP_SVC_TABLE */
	for(i = TotalServices - 1; i >= 0 ; i--)
	{
		if ( strapi_GetByIndex(HsvMain, HSVSPID(Program, mpeg, simplepat), i, (Address)(&val)) )
		{
			/* val.ProgramNumber gives the service ID */
			TraceNotice (m, "No SDT Data for SvcId %d .. So filling dummy data \n", val.ProgramNumber);
			service.ServiceId = val.ProgramNumber;
			FillDummySdtData (&service);

			if( mCheckServiceForInstall (ptc, &service) == TRUE )
			{
				InstalledServices++;
				retval = TRUE;
			}
		}
	}
	/*Work around to not delete the services when demux instance is NULL during 4AM update*/
	if ((IsUpdateInstall()) && (TotalServices != 0))
	{
		mDeleteServicesCurrentCarrier(ptc);
	}		
	TraceNotice (m, "Updateprint: Num TV: %d Num Radio: %d UserDef: %d \n", mDigitalTvChannelsFoundInLnb[mCurrentLnb], mDigitalRadioChannelsFoundInLnb[mCurrentLnb], mDigitalUserDefinedChannelsFound);
	TraceNotice(m, "Installed %d services\n", InstalledServices);

    return retval;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mInstallMuxOnTimeout(HsvInstallationPTC *ptc)
{
    Bool	retval = FALSE;
	int		TotalServicesInPat = 0;

	TotalServicesInPat = strapi_GetSize (HsvMain, HSVSPID(Program, mpeg, simplepat));

	TraceNotice (m, " TotalSvcInPat : %d \n", TotalServicesInPat);
	retval = mInstallMuxOnPat (ptc, TotalServicesInPat);

    return retval;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mInstallMux(HsvInstallationPTC *ptc)
{
    Bool	retval = FALSE;
	int		TableId = ACTUAL_TABLE;
	int		i, TotalServices = 0, InstalledServices = 0;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	
	TotalServices = strapi_GetSize (HsvMain, GETHSVSPID(SpidService, TableId));
	TraceNotice (m, "%s %d NoOfServices in MUX = %d\n",__FUNCTION__, __LINE__, TotalServices);
	if (IsManualInstall())
	{
		/* When doing SRT, SatInfo may not be present. So add the same here */
		mAddSatInfo (ptc);
		DeleteCurrentChannelEntry (ptc);
	}

	/* From strapi get all the services and add/update them in TEMP_SVC_TABLE */
    for(i = TotalServices - 1; i >= 0 ; i--)
    {
		if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId), i, (void *)(&service)) == TRUE)
        {
            if( mCheckServiceForInstall (ptc, &service) == TRUE )
            {
				/* TODO: ANEESH: To correct this and increment only when succesful addition happens */
                InstalledServices++;
                retval = TRUE;
            }
        }
    }
	if (IsUpdateInstall())
	{
		mDeleteServicesCurrentCarrier(ptc);
	}			

	TraceNotice (m, "Updateprint: Num TV: %d Num Radio: %d UserDef: %d \n", mDigitalTvChannelsFoundInLnb[mCurrentLnb], mDigitalRadioChannelsFoundInLnb[mCurrentLnb], mDigitalUserDefinedChannelsFound);
    TraceNotice (m, "Installed %d services\n", InstalledServices);

    return retval;
}

void CHsvDvbsGeneric_mAcq_Priv::GetUserPackageIndex(Nat32* PackageIndex, Bool* IsPackage)
{
	FResult retValue = err_BadParameter;
	int		SetValue = 0;
	Nat16	PackageGroupId = 0;

	if (PackageIndex && IsPackage)
	{
		SetValue = idvbset_GetAttribute (idvbset_AttributePackageId);
		*PackageIndex = SetValue;

		retValue = ipackage_GetPackageGroupId ((Nat16)SetValue, &PackageGroupId);
		*IsPackage = ((retValue == err_Ok) && (PackageGroupId > 0)) ? TRUE : FALSE;
		retValue = err_Ok;
	}
}


void CHsvDvbsGeneric_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
{
	HSVSPTYPE(ActualTSService, dvb, sdt) service;	
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;
	HsvPATProgramPIDInfo		val;
	
	TempSvcData.Tpid 		 = ptc->TPID;
	
	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{
		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			
			if ( RetVal == TRUE &&
				 (strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE),TempSvcData.OriginalNetworkId, TempSvcData.ServiceId,TempSvcData.Tsid , (Address)(&service)) == FALSE) &&
				 ( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, simplepat), TempSvcData.ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) == FALSE) && 
                 (TempSvcData.SDSDFrequency == 0)/* Delete only services installed by generic */)
			{
				TraceNotice (m, "%s %d>Delete servicess Ser-id[%d] Tsid[%d] Onid[%d]",
							__FUNCTION__,
							__LINE__,
							TempSvcData.ServiceId,
							TempSvcData.Tsid,
							TempSvcData.OriginalNetworkId );

				if (IsDigitalTvChannel (&TempSvcData))
				{
					removeCurTv++;
					NumTvServicesremoved++;
				}
				else if (IsDigitalRadioService (&TempSvcData))
				{
					removeCurRadio++;
					NumRadioServicesRemoved++;
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

void CHsvDvbsGeneric_mAcq_Priv::DeleteCurrentChannelEntry (HsvInstallationPTC *ptc)
{
	/* This function will check whether newly found MUX was already present in same 
		frequcney/pol. If yes, it will be deleted from database. Otherwise just ignore */
	Bool						RetVal = FALSE;
	HsvPgdatDigTSData			deleteTsData;
	HsvPgdatDigServiceData		deleteSvcData;
	HsvPgdatPresetData			presetData;
	int							From = 0, To = 0, count = 0;
	Nat32 PackageIndex = 0;
	Bool IsPackage = FALSE;
	
	deleteTsData.LnbNumber	=	ptc->LnbNumber;
	deleteTsData.Frequency	=	ptc->Frequency;
	deleteTsData.Polarization = ptc->Polarization;

	RetVal = pgdb_GetByKey (PTC_TABLE, (Address) &deleteTsData);
	if (RetVal == TRUE)
	{
		deleteSvcData.Tpid = deleteTsData.Tpid;
		pgdb_Delete (PTC_TABLE, (Address) &deleteTsData);

		RetVal = pgdb_GetRange (SERVICE_TABLE , 1, (Address)&deleteSvcData , &From , &To);
		if (RetVal == TRUE)
		{
			for (count = To; count >= From; count--)
			{
				RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&deleteSvcData); 
				if (RetVal == TRUE)
				{

					GetUserPackageIndex(&PackageIndex, &IsPackage);
					
					if(PackageIndex == ASTRA_LCN_BOUQUET_ID)
					{
						presetData.PresetNumber = deleteSvcData.MultiplePreset[0];			
					} else  {
						presetData.PresetNumber = deleteSvcData.PresetNumber;
					}
					TraceNotice (m, "%s %d>Delete servicess Ser-id[%d] Tsid[%d] Onid[%d]",
							__FUNCTION__,
							__LINE__,
							deleteSvcData.ServiceId,
							deleteSvcData.Tsid,
							deleteSvcData.OriginalNetworkId );
					
					pgdb_Delete(SERVICE_TABLE, (Address)&deleteSvcData);

					if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
					{
						pgdb_Delete(PRESET_TABLE, (Address)&presetData);
					}
				}
			}
		}
	}
}

void CHsvDvbsGeneric_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);

	/* Filling attributes from ptc, and acqinstance */
	tsdata.Frequency					= ptc->Frequency;
	tsdata.SymbolRate				= ptc->SymbolRate;

	tsdata.OriginalNetworkId			= DataAcqInstance.Onid;
	tsdata.Tsid						= DataAcqInstance.Tsid;
	tsdata.NetworkId					= DataAcqInstance.NetworkId;
	tsdata.ModulationType			= ptc->ModulationType;
	tsdata.CodeRate					= ptc->CodeRateHigh;
	//tsdata.HierarchyMode				= ptc->HierarchyMode;
	tsdata.IqMode					= ptc->IqMode;
	tsdata.Bandwidth				= ptc->ChannelBandwidth;
	//tsdata.StreamPriority			= ptc->StreamPriority; 
	tsdata.PtcListVersion			= isvcscandata_GetInstallationVersion();
	//tsdata.QSignalStrength			= ptc->QSignalStrength;
	//tsdata.SSignalStrength			= ptc->SSignalStrength;
	//tsdata.ChannelInformation		= ptc->ChannelInformation;
	tsdata.SDSDFrequency			= ptc->SDSDFrequency;
	tsdata.UserInstalled			= IsManualInstall();
    tsdata.TSVersion				= DataAcqInstance.TsVersionNum;
	tsdata.SDTVersion				= DataAcqInstance.SDTVersion;
	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Polarization				= ptc->Polarization;
	tsdata.Tpid						= ptc->TPID;
	tsdata.DecoderType				= ptc->ModulationStd;

	tmptsdata.LnbNumber				= tsdata.LnbNumber;
	tmptsdata.Frequency				= tsdata.Frequency;
	tmptsdata.Polarization			= tsdata.Polarization;

	/* check entry already present. If yes update else add */
	/* TODO: Manual + servic scan uses PTC Table directly */
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE )
	{
		TraceNotice (m, "Addition to pgdb table %s %d <%ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency);
		pgdb_Add(PTC_TABLE, (Address )&tsdata);

	}
	else 
	{
		if((!IsManualInstall()) && (tmptsdata.SDSDFrequency != 0))
		{
			tsdata.SDSDFrequency			= tmptsdata.SDSDFrequency;
		
		}
		TraceNotice (m, "Updation to pgdb table %s %d <%ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency);
		pgdb_Update(PTC_TABLE, (Address )&tsdata);
	}
}

Bool CHsvDvbsGeneric_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	Bool		retval = FALSE, channelExists = FALSE;
	HsvPgdatDigServiceData svcdat, tempsvcdat;

	TraceDebug (m, " SvcId %d and SvcType %d \n", service->ServiceId, service->ServiceType);

	/* Checking whether service is having installable service type. TODO: Define the Service type  */
    if( mIsServiceInstallable(ptc, service))
    {
		/* Get Default values */
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

        svcdat.OriginalNetworkId	 = DataAcqInstance.Onid;
        svcdat.ServiceId			 = service->ServiceId;
		svcdat.Frequency	         = ptc->Frequency;
		svcdat.Tsid                  = DataAcqInstance.Tsid;

		//svcdat.NewChannelMap		 = 1;
		svcdat.LnbNumber			 = ptc->LnbNumber;
		svcdat.Polarization			 = ptc->Polarization;
		svcdat.Tpid					 = ptc->TPID;
        svcdat.SDSDFrequency		 = ptc->SDSDFrequency;
		svcdat.DecoderType			 = ptc->ModulationStd;
		/*TODO: uncomment after adding these items in db*/
//		svcdat.FECInner = ptc->FECInner;
//		svcdat.RollOff	= ptc->RollOff;
		TraceDebug (m, "In CheckServiceForInstall LNB %d Pol %d TpId %d ONid[%d]\n", ptc->LnbNumber, ptc->Polarization, (int) ptc->TPID,svcdat.OriginalNetworkId);

		tempsvcdat.Tpid				 = svcdat.Tpid;
		tempsvcdat.ServiceId		 = svcdat.ServiceId;

		/* There is no concept of duplicate services. Even if the services are repeated,
			they are added. But the TPID & service ID combination cannot be duplicate */
		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		/*TraceNotice ( m,"Channel Exist[%d]",	channelExists);*/
		if (channelExists)
		{
			/*services installed by package should not be updated*/
			if (IsServiceScanInstall () || (tempsvcdat.SDSDFrequency != 0))
			{
				TraceNotice (m, "service id :%d LCN: %d Preset: %d installed via pkg will not be updated ", tempsvcdat.ServiceId, tempsvcdat.LCN, tempsvcdat.PresetNumber);
				TraceDebug (m, " ERROR..if seen during SDSD scan.. \n");
				/* No update is needed when doing service scan. So ignore this service */
				retval = FALSE;
			}
			else
			{
				/* If entry already present update the service data */
				mUpdateService(&svcdat, ptc, service);
				retval = TRUE;	
			}
		}
		else
		{
			
			mAddNewService(&svcdat, ptc, service);
			retval = TRUE;
		}
	}
	return retval;
}

void CHsvDvbsGeneric_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	

	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mAssignSvcNonBroadcastAttributes(psvcdat);
	mUpdateSatelliteName (psvcdat);

	/* Check service is TV or Radio */
	if (IsDigitalTvChannel (psvcdat) || IsDigitalRadioService (psvcdat))
	{
		pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
		TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
	}
	else
	{
		TraceNotice (m, "%s %d>Delete servicess Ser-id[%d] Tsid[%d] Onid[%d]",
							__FUNCTION__,
							__LINE__,
							psvcdat->ServiceId,
							psvcdat->Tsid,
							psvcdat->OriginalNetworkId );
		
		TempSvcData.Tpid				 = psvcdat->Tpid;
		TempSvcData.ServiceId		 = psvcdat->ServiceId;

		pgdb_GetByKey(SERVICE_TABLE,(Address)&TempSvcData);
		if (IsDigitalTvChannel (&TempSvcData))
		{
			removeCurTv++;
			NumTvServicesremoved++;
		}
		else if (IsDigitalRadioService (&TempSvcData))
		{
			removeCurRadio++;
			NumRadioServicesRemoved++;
		}
	
		presetData.PresetNumber = TempSvcData.PresetNumber;
		pgdb_Delete(SERVICE_TABLE, (Address)&TempSvcData);
		
		if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
		{
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
		}				
	}
}

void CHsvDvbsGeneric_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;

	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
            	memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, MAX_SATELLITE_NAME_LEN * sizeof(Nat16));
	}
}

void CHsvDvbsGeneric_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	Nat8	ToAdd = FALSE;

	/* Filling details of service, then adding it */	
	mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mAssignSvcNonBroadcastAttributes(psvcdat);
	mUpdateSatelliteName (psvcdat);

	mDigitalChannelsFound++;
	/* Check service is TV or Radio */
	if (IsDigitalTvChannel (psvcdat))
	{
		ToAdd = TRUE;
		mDigitalTvChannelsFoundInLnb[mCurrentLnb]++;
		NumTvServicesInMux++;
	}
	else if (IsDigitalRadioService (psvcdat))
	{
		ToAdd = TRUE;
		mDigitalRadioChannelsFoundInLnb[mCurrentLnb]++;
		NumRadioServicesInMux++;
	}
	else if (IsUserDefinedService (psvcdat))
	{
		ToAdd = TRUE;
		mDigitalUserDefinedChannelsFound++;
	}

	/* Add to TEMP service table */
	if (ToAdd == TRUE)
	{
		/* Add only if its TV or Radio Service */
		pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
		
		//TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d\n",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
		//TraceNotice(m,"SDTVersion = %ld\r\n",(Nat32) DataAcqInstance.SDTVersion);  
		TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d\n",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
	}
}

void CHsvDvbsGeneric_mAcq_Priv::UpdateServiceTypeFromPat (HsvPgdatDigServiceData *psvcdat)
{
	HsvSimplePMTPidInfo		PidInfo;

	/*TraceNotice(m,"Service-Tyep[%d]",psvcdat->ServiceType);*/

	switch (psvcdat->ServiceType)
	{
	case	AppApiTelevisionService:
	case	AppApiTeletextService:
	case	AppApiMPEG2HDService:
	case	AppApiAdvCodecHDTelevisionService:
	case	AppApiAdvCodecSDTelevisionService:
	case	AppApiRadioService:
	case 	AppApiSkyHD:
			break;
	default:
		/* ANEESH:: TODO: Need to check only for 0x80 - 0xFF (verify ) */
		/*TraceNotice(m,"Default Service-Type");*/

		if ( (psvcdat->ServiceType == 0xFF ) ||
			 ( psvcdat->ServiceType >= 0x80 &&
			   psvcdat->ServiceType <= 0xFE ))
		{
			if ( strapi_GetByKey(HsvMain, HSVSPID(PidInfo, mpeg,simplepmt), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&PidInfo)) )	
			{
				psvcdat->ServiceType = ((PidInfo.VideoPid != INVALID_PID)) ? AppApiTelevisionService : \
										((PidInfo.AudioPid != INVALID_PID) ?  AppApiRadioService :  psvcdat->ServiceType);
				TraceNotice(m,"Service-Type vp[%d]ap[%d]",PidInfo.VideoPid,PidInfo.AudioPid);
			}
		}	
		break;
	}
	/*TraceNotice(m,"UpdateServiceTypeFromPat");*/
}

/*--------------------------------------------------------------------------------------------------------------------------*/
Nat16 * CHsvDvbsGeneric_mAcq_Priv::mAsciiToUnicode(char *ascii_str,int length)
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


void CHsvDvbsGeneric_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	int mode, state;
	HsvPATProgramPIDInfo		val;

	insstate_GetCurrentInstallationState(&mode, &state);

	psvcdat->NetworkId			   =   DataAcqInstance.NetworkId;
	psvcdat->ModulationType        =   ptc->ModulationType;
	psvcdat->Bandwidth	   			=   ptc->ChannelBandwidth;
	//psvcdat->StreamPriority		   =   ptc->StreamPriority ;	
	psvcdat->SymbolRate            =   ptc->SymbolRate;
	psvcdat->ServiceType           =   mConvertToPgdatServiceType(service->ServiceType);
    //psvcdat->Type                  =   GETSERVICETYPE(service->ServiceType);
	psvcdat->FreeCiMode	    	   =   service->Free_Ci_Mode;
	psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
	psvcdat->NumBrandIds	       =   service->NumBrandIds;
	psvcdat->AudioPid              =   INVALID_PID;
	psvcdat->VideoPid              =   INVALID_PID;
	psvcdat->PcrPid                =   INVALID_PID;
	psvcdat->LCN				   =   INVALID_LCN;
	//psvcdat->OUI                   =   HsvOUI_Last;
	psvcdat->LnbNumber			   =   ptc->LnbNumber;
	psvcdat->Polarization		   =   ptc->Polarization;
	psvcdat->Tpid				   =   ptc->TPID;
	
	psvcdat->NumericSelect = TRUE;

	if(service->Free_CA_Mode == TRUE)
    {
        psvcdat->ScramblingStatus = 1;
    }
	/* Updating the service type from SimplePat/Pmt in case of service/update installation */
	if ((mode == AUTO_MODE) || (mode == UPDATE_MODE) || (mode == AUTOUPDATE_MODE)|| (mode == ADDSAT_MODE))
	{
		UpdateServiceTypeFromPat (psvcdat);
	}

	if(mIsLCNAcquistionSupported())
	{
		dataacq_AssignLCN(psvcdat);
		TraceNotice(m, "%s LCN %d VisibleService %d for service Triplet <%d %d %d>", __FUNCTION__, psvcdat->LCN, psvcdat->VisibleService, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
	}
	

	/* ANEESH: TODO: UPDATE PMT PID From SimplePat */
	/* if ( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) )
	{
		psvcdat->PmtPid			   =   val.Pid;
	}
	else */
	if ( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, simplepat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) )
	{
		psvcdat->PmtPid			   =   val.Pid;
	}

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

void CHsvDvbsGeneric_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
	int mode, state;
  	int LoopCount = 0;
	HsvPgdatPresetData presetData;
	HsvPgdatDigServiceData		svcdat;

	insstate_GetCurrentInstallationState(&mode, &state);

	psvcdat->UserHidden             = FALSE;
	psvcdat->ChannelLock		    = FALSE;
	psvcdat->Favorite			    = FALSE;
	//psvcdat->PreferredStereo	    = 1;
	psvcdat->DateStamp			    = 0;
	psvcdat->PresetNumber		    = INVALID_PRESET;
	psvcdat->ServiceListVersion     = isvcscandata_GetInstallationVersion();
	psvcdat->NewPreset				= (mode == AUTO_MODE)? FALSE : TRUE;
	psvcdat->HbbTvOption 		= 1;
	psvcdat->PackageGroup           = APPAPISAT_None;
	psvcdat->UserInstalled           = IsManualInstall();
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		psvcdat->MultipleLCN[LoopCount] = INVALID_LCN;
		psvcdat->MultiplePreset[LoopCount] = INVALID_PRESET;
	}
	/*FRANSAT - To place the service in non honoured range, value is assigned to 0xFFFF*/
	psvcdat->MultipleLCN[0]	= 0xFFFF;

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
	{
		psvcdat->NewPreset				= svcdat.NewPreset;
		/* ANEESH: TODO: Check with Pavan whether need to keepthe preset number */
		//psvcdat->EPGEnabled				= svcdat.EPGEnabled;
		psvcdat->ChannelLock			= svcdat.ChannelLock;;
		psvcdat->UserHidden				= svcdat.UserHidden;
		psvcdat->Favorite				= svcdat.Favorite;
        psvcdat->FavoriteNumber         = svcdat.FavoriteNumber;
		psvcdat->ServiceListVersion     = svcdat.ServiceListVersion;
		psvcdat->HbbTvOption			= svcdat.HbbTvOption;
		//psvcdat->EPGShortInfo           = svcdat.EPGShortInfo;
		//psvcdat->SAP                    = svcdat.SAP;
		psvcdat->DeltaVolume			= svcdat.DeltaVolume;
		psvcdat->UserModifiedName				= svcdat.UserModifiedName;
		//psvcdat->PreferredStereo		= svcdat.PreferredStereo;
		//psvcdat->HMBlanked				= svcdat.HMBlanked;
		//psvcdat->HMProtectedChannel		= svcdat.HMProtectedChannel ;
		//psvcdat->HMMapChannelNo			= svcdat.HMMapChannelNo;
		psvcdat->LogoURL				= svcdat.LogoURL;
		if (mCompareUnicodeString(psvcdat->ChannelName, svcdat.ChannelName) == FALSE)
		{
			TraceNotice(m, "Service name updated");
			psvcdat->LogoURL = 0;
		}
		else
		{
			TraceNotice(m, "Service name is same");
		}
		/*If the service installed via manual installation earlier then invalidate the preset*/
		if((!IsManualInstall()) && (svcdat.UserInstalled == TRUE))
		{
			TraceNotice(m,"ONID: %d TSID: %d SVCID: %d deleted PresetNumber %d", svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,svcdat.PresetNumber);
			presetData.PresetNumber =   svcdat.PresetNumber;						
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
		}
		else if ((IsUpdateInstall()) && (mIsPredefinedListPackage () ))
		{
			TraceNotice(m,"PredefListUpdate: ONID: %d TSID: %d SVCID: %d deleted PresetNumber %d", svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,svcdat.PresetNumber);
			presetData.PresetNumber =   svcdat.PresetNumber;						
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
		}
		else
		{
		        psvcdat->PresetNumber		    = svcdat.PresetNumber;        
		}
		psvcdat->MultipleLCN[0]     = svcdat.MultipleLCN[0];
              psvcdat->MultiplePreset[0]     = svcdat.MultiplePreset[0];
	       memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
		TraceNotice(m,"Preset: %d", psvcdat->PresetNumber);
	}

    if( Timerclk_IsClockDefined() && !IsManualInstall() )
    {
        psvcdat->DateStamp = Timerclk_GetUniversalTime();
    }

}

#if 0

void CHsvDvbsGeneric_mAcq_Priv::mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp)
{
	/* No need to copy Primary keys again, copy rest of them */
	psvcdat->NetworkId			   =	svcdat_temp.NetworkId;
	psvcdat->ModulationType        =	svcdat_temp.ModulationType;
	psvcdat->Bandwidth	   			=	svcdat_temp.ChannelBandwidth;
	psvcdat->Tsid				   =	svcdat_temp.Tsid;
    psvcdat->LCN				   =	svcdat_temp.LCN;
	//psvcdat->LowPrioLCN			   =	svcdat_temp.LowPrioLCN;
    //psvcdat->LowPrioVisibleService =	svcdat_temp.LowPrioVisibleService;
    psvcdat->VisibleService[0]		   =	svcdat_temp.VisibleService[0];
	//psvcdat->NumericSelect		   =	svcdat_temp.NumericSelect;
    psvcdat->ServiceType           =    svcdat_temp.ServiceType;
    //psvcdat->Type                  =	svcdat_temp.Type;
	psvcdat->FreeCiMode	    	   =    svcdat_temp.FreeCiMode;
	psvcdat->MatchBrandFlag        =    svcdat_temp.MatchBrandFlag;
	psvcdat->NumBrandIds	       =    svcdat_temp.NumBrandIds;
	psvcdat->SystemHidden		   =	svcdat_temp.SystemHidden;
	psvcdat->NewPreset			   =	svcdat_temp.NewPreset;
	psvcdat->ServiceListVersion	   =	svcdat_temp.ServiceListVersion; 
	mCopyString( psvcdat->BrandIds, svcdat_temp.BrandIds, svcdat_temp.NumBrandIds );

	if(psvcdat->UserModifiedName == FALSE)
	{
		/* This means user has not renamed the service, so we can update the one sent by broadcaster */
		mCopyString( psvcdat->ChannelName, svcdat_temp.ChannelName, (eurdiv_PresetNameLength - 1));
	}
}
#endif

/*
static void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp)
{
	tsdata->Frequency            =   tsdata_temp.Frequency;
    tsdata->ModulationType       =   tsdata_temp.ModulationType;               
    //tsdata->HierarchyMode        =   tsdata_temp.HierarchyMode;
    tsdata->IqMode               =   tsdata_temp.IqMode;
    tsdata->Bandwidth     		=   tsdata_temp.ChannelBandwidth;
    //tsdata->StreamPriority       =   tsdata_temp.StreamPriority;
    //tsdata->QSignalStrength      =   tsdata_temp.QSignalStrength;
	//tsdata->SSignalStrength      =   tsdata_temp.SSignalStrength;
    //tsdata->ChannelInformation   =   tsdata_temp.ChannelInformation; 

    tsdata->SymbolRate           =   tsdata_temp.SymbolRate; 
    tsdata->OriginalNetworkId    =   tsdata_temp.OriginalNetworkId;
    tsdata->Tsid                 =   tsdata_temp.Tsid;
    tsdata->NetworkId            =   tsdata_temp.NetworkId;
	tsdata->TSVersion            =   tsdata_temp.TSVersion;
	tsdata->PtcListVersion       =   tsdata_temp.PtcListVersion;
	tsdata->CodeRate             =   tsdata_temp.CodeRate;
	
	tsdata->UserInstalled		 =	 tsdata_temp.UserInstalled;
}
*/


void CHsvDvbsGeneric_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}

void CHsvDvbsGeneric_mAcq_Priv::mDetermineSatelliteDetails (HsvPgdatDigSatInfoData *SatInfo)
{
	int		NumSdsds;
	Bool	RetVal = FALSE;
	char	LnbName [10];
	HsvSatelliteMapping	SatelliteMapping;
	HSVSPTYPE(SatelliteDS, dvb, nit)    SatelliteDSDesc;

	NumSdsds = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
	if (NumSdsds)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), 0, (void*)(&SatelliteDSDesc)))
		{
			RetVal= iprescanparser_ExtractPreScanTableFromXml();
			if (RetVal == TRUE)
			{
				SatelliteMapping.OrbitalPosition = SatelliteDSDesc.OrbitalPosition;
				SatelliteMapping.EastWestFlag = SatelliteDSDesc.WestEastFlag;
				RetVal = iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping);
			}
		}
	}
	else
	{
		iprescanparser_ExtractPreScanTableFromXml();
	}

	if (RetVal == FALSE)
	{
		/* Unknown Satellite */
		SatelliteMapping.OrbitalPosition = 0;
		SatelliteMapping.EastWestFlag = 0;
		iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping);
	}

	SatInfo->SatelliteId = SatelliteMapping.SatelliteId;
	SatInfo->OrbitalPosition = SatelliteMapping.OrbitalPosition;

	if (RetVal == FALSE)
	{
		/* Should display Sat - <Lnb Number > */
		sprintf (LnbName, "Sat - %d", SatInfo->LnbNumber + 1);
		charsetutil_MbToWc((Nat8*)LnbName, strlen(LnbName), SatInfo->SatelliteName, MAX_SATELLITE_NAME_LEN, FALSE);
	}
	else
	{
            	memcpy (SatInfo->SatelliteName, SatelliteMapping.SatelliteName, MAX_SATELLITE_NAME_LEN * sizeof(Nat16));
	}
}

void CHsvDvbsGeneric_mAcq_Priv::mDetermineDuplicateSatelliteName (HsvPgdatDigSatInfoData *SatInfo)
{
	Bool	RetVal = FALSE;
	char	LnbName [10];
	HsvSatelliteMapping	SatelliteMapping;

    RetVal= iprescanparser_ExtractPreScanTableFromXml();
    if (RetVal == TRUE)
    {
        SatelliteMapping.SatelliteId = SatInfo->SatelliteId;
        
        RetVal = iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);
        if (RetVal == FALSE)
        {
            /* Should display Sat - <Lnb Number > */
	        SatInfo->OrbitalPosition = 0;
            sprintf (LnbName, "Sat - %d", SatInfo->LnbNumber+1);
            charsetutil_MbToWc((Nat8*)LnbName, strlen(LnbName), SatInfo->SatelliteName, MAX_SATELLITE_NAME_LEN, FALSE);
        }
        else
        {
	        SatInfo->OrbitalPosition = SatelliteMapping.OrbitalPosition;
            memcpy (SatInfo->SatelliteName, SatelliteMapping.SatelliteName, MAX_SATELLITE_NAME_LEN * sizeof(Nat16));
        }
    }
}

Bool CHsvDvbsGeneric_mAcq_Priv::mUpdateSatelliteDetails (HsvPgdatDigSatInfoData *SatInfo)
{
	int		NumSdsds;
	Bool	RetVal = FALSE;
	HsvSatelliteMapping	SatelliteMapping;
	HSVSPTYPE(SatelliteDS, dvb, nit)    SatelliteDSDesc;

	/* Check existing satellite info is unknown or not */
	iprescanparser_ExtractPreScanTableFromXml();
	
	/* Getting Unknown SatelliteID */
	SatelliteMapping.OrbitalPosition = 0;
	SatelliteMapping.EastWestFlag = 0;
	iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping);

	if (SatelliteMapping.SatelliteId == SatInfo->SatelliteId)
	{
		NumSdsds = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
		if (NumSdsds)
		{
			if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), 0, (void*)(&SatelliteDSDesc)))
			{
				SatelliteMapping.OrbitalPosition = SatelliteDSDesc.OrbitalPosition;
				SatelliteMapping.EastWestFlag = SatelliteDSDesc.WestEastFlag;
				RetVal = iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping);
				if (RetVal == TRUE)
				{
					TraceNotice (m, "Stored Satellite Unknown -- Updating with Known Sat Details obtained from SDSD in manual install");
					/* Finally found one known satellite */
					SatInfo->SatelliteId = SatelliteMapping.SatelliteId;
					SatInfo->OrbitalPosition = SatelliteMapping.OrbitalPosition;
            				memcpy (SatInfo->SatelliteName, SatelliteMapping.SatelliteName, MAX_SATELLITE_NAME_LEN * sizeof(Nat16));
				}
			}
		}
	}

	return RetVal;
}


void CHsvDvbsGeneric_mAcq_Priv::mAddSatInfo (HsvInstallationPTC	*ptc)
{
	HsvPgdatDigSatInfoData		SatInfo;
	HsvLnbSettings				LnbSettings;

	/* If no satellites are present, add the sat info at first */
	SatInfo.LnbNumber = ptc->LnbNumber;
	if (!pgdb_GetByKey(SAT_INFO_TABLE, (Address)&SatInfo))
	{
        if (err_Ok == idvbset_GetLnbSettings (&LnbSettings)) 
        {
            TraceNotice (m, "Handling of SRT. No Sat Info Found.. So adding the new entry \n");
            SatInfo.LnbType = ptc->LnbType;
            SatInfo.LnbNumber = ptc->LnbNumber;

            if (LnbSettings.LnbSettings[ptc->LnbNumber].LnbStatus == LnbDuplicate)
            {
                SatInfo.SatelliteId = LnbSettings.LnbSettings[ptc->LnbNumber].SatelliteId;
                mDetermineDuplicateSatelliteName (&SatInfo);
            }
            else
            {
                mDetermineSatelliteDetails (&SatInfo);
            }

            if (pgdb_Add (SAT_INFO_TABLE, (Address)&SatInfo))
            {
                TraceNotice (m, " Added the SatelliteInfo Succesfully \n");
                if (LnbSettings.LnbSettings[ptc->LnbNumber].LnbStatus != LnbDuplicate)
                {
                    LnbSettings.LnbSettings[ptc->LnbNumber].SatelliteId = SatInfo.SatelliteId;
                    LnbSettings.LnbSettings[ptc->LnbNumber].LnbStatus = LnbManualInstalled;
					LnbSettings.LnbSettings[ptc->LnbNumber].UpdateInstallEnabled = FALSE;
                }
                idvbset_SetLnbSettings (&LnbSettings);
				idvbset_SaveSatelliteSettingsToPersistent();
				idvbset_CommitSatelliteSettingsToPersistent (); 
            }
            else
            {
                TraceNotice (m, " Add SatInfo Failed... \n");
            }
        }
	}
	else
	{
		/* Already data existing. Check if this is unknown satellite. Update info only in case of unknown sat */
		if (TRUE == mUpdateSatelliteDetails (&SatInfo))
		{
			if (pgdb_Add (SAT_INFO_TABLE, (Address)&SatInfo))
			{
				TraceNotice (m, " Updated the SatelliteInfo Succesfully \n");
			}
			else
			{
				TraceNotice (m, " Add SatInfo Failed... \n");
			}
		}
	}
}

void CHsvDvbsGeneric_mAcq_Priv::mGetPTCInfo(HsvInstallationPTC *ptc)
{
	if (IsManualInstall ())
	{
		isrtdata_GetPtcInfo (ptc);
	}
	else
	{
		isvcscandata_GetPtcInfo (ptc);
	}
}

Bool CHsvDvbsGeneric_mAcq_Priv::mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	/* Currently no elimination condition for Installable check. Update this function
		if such requirement comes in future */
	Bool					lRetVal = TRUE;
	return lRetVal;	    
}


Bool CHsvDvbsGeneric_mAcq_Priv::IsManualInstall(void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsGeneric_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}
Bool CHsvDvbsGeneric_mAcq_Priv::IsServiceScanInstall (void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationServiceScan)? TRUE: FALSE);
}


/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsGeneric_mAcq_Priv::iacqpow_Init(void)
{

	mDataAcqPump = pmp_PmpCreateEx(pen_PumpEngine, mPumpHandler, TRUE, "hsvdvbsins_mDataAcq_pmp");
}

void CHsvDvbsGeneric_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsGeneric_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsGeneric_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
	/* Resetting all the variables */
	TraceNotice (m ,"CurrentLnb number in acq %d ", LnbNumber);
	mCurrentLnb = LnbNumber;
	mDigitalTvChannelsFoundInLnb[mCurrentLnb] = mDigitalRadioChannelsFoundInLnb[mCurrentLnb] = 0;

    mDigitalChannelsFound = mDigitalUserDefinedChannelsFound = 0;
	mDigitalTranspondersFound = removeCurTv = removeCurRadio = 0;
	mSatDSDesc.NumOfSDSD = 0;
}

void CHsvDvbsGeneric_mAcq_Priv::idataacq_AcquireData(int Mode)
{
	if (Mode == idataacq_Background)
	{
		pmp_PmpSend(mDataAcqPump, StartBackgroundDataAcq, (Nat32)NULL);
	}
	else if(Mode == idataacq_AcquireSDSDs)
	{
		pmp_PmpSend(mDataAcqPump, StartSDSDDataAcq, (Nat32)NULL);
	}
	else 
	{
		pmp_PmpSend(mDataAcqPump, StartDataAcq, (Nat32)NULL);
	}
	UNUSED(Mode);
}
void CHsvDvbsGeneric_mAcq_Priv::mCheckAndAdjustDuplicateEntry (HsvInstallationPTC *Ptc)
{
	int mode, state;
    FrequencyDataList   Data;
    Bool        IsDuplicate = FALSE;

	insstate_GetCurrentInstallationState(&mode, &state);

    if (mode == AUTO_MODE)
    {
        Data.LnbNumber = Ptc->LnbNumber;
        Data.Frequency = Ptc->Frequency;
        Data.Polarization = Ptc->Polarization;
        Data.OriginalNetworkId = DataAcqInstance.Onid;
        Data.TsId = DataAcqInstance.Tsid;
		Data.SymRate = Ptc->SymbolRate;	

        IsDuplicate = iutil_IsDuplicate (&Data);
        if (IsDuplicate == TRUE)
        {
            /* Finding a duplicate entry. Update Frequency and TPID */
            TraceNotice (m, "Found Duplicate of Package Installation in Generic install ");
            Ptc->Frequency = Data.Frequency;
	        Ptc->TPID = CREATE_TPID(Ptc->LnbNumber, Ptc->Frequency, Ptc->Polarization);
        }
    }
}
void CHsvDvbsGeneric_mAcq_Priv::mAcquireData(void)
{
	/* Call Back once Data collection is completed by SDM */
    HsvInstallationPTC    ptc;

	memset (&DataAcqInstance, 0x00, sizeof(DataAcqInstance));
	NumTvServicesInMux = NumRadioServicesInMux = NumTvServicesremoved = NumRadioServicesRemoved = 0;

	/* Getting ONID, TS details */
	Bool retval = mGetTSMetaData();

	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
    if(retval == TRUE)
    {
		/* Get Current PTC details from scan module */
        mGetPTCInfo(&ptc);
		TraceNotice (m, "%s %d svcdat.Frequency %ld\n", __FUNCTION__, __LINE__, ptc.Frequency);
        mCheckAndAdjustDuplicateEntry (&ptc);

		if(mInstallMux(&ptc) == TRUE )
		{
			/* Add entry to TS Table */
			mAddToTSTable(&ptc);
			
			if (IsUpdateInstall())
			{
				TraceNotice (m, "TpId %d Freq %d  Polarization %d TV: %d / %d Radio %d / %d  ", (int)ptc.TPID, (int)ptc.Frequency, ptc.Polarization, NumTvServicesInMux ,\
														NumTvServicesremoved, NumRadioServicesInMux,  NumRadioServicesRemoved);
			}
			else
			{
				TraceNotice (m, "TpId %d Freq %d  Polarization %d TV: %d Radio %d ", (int)ptc.TPID, (int)ptc.Frequency, ptc.Polarization, NumTvServicesInMux , NumRadioServicesInMux );
			}
		}
		mDigitalTranspondersFound++;
		TraceNotice (m, " Tranponder Count is %d \n", mDigitalTranspondersFound);
    }
	else
	{
		TraceNotice (m, "PTC Ignored: Invalid PTC or Incomplete Data\n");
	}
}

Bool CHsvDvbsGeneric_mAcq_Priv::mIsPredefinedListPackage (void)
{
	Bool	IsPredefinedList = FALSE;
	int PackageId = 0, PackageGroup = 0;

	PackageId = insstate_GetAttribute(UPDATE_MODE, insstate_AttributePackageId);
	PackageGroup = insstate_GetAttribute(UPDATE_MODE, insstate_AttributePackageGroup);

	IsPredefinedList = (PackageGroup == 0) && (PackageId != 0) ? TRUE: FALSE;

	return IsPredefinedList;
}

void CHsvDvbsGeneric_mAcq_Priv::idataacq_AcquireDataOnTimeout(void)
{
	pmp_PmpSend(mDataAcqPump, StartDataAcqOnTimeout, (Nat32)NULL);
}

void CHsvDvbsGeneric_mAcq_Priv::mAcquireDataOnTimeout(void)
{
	/* Call Back once Data collection is completed by SDM */
    HsvInstallationPTC    ptc;

	memset (&DataAcqInstance, 0x00, sizeof(DataAcqInstance));
	NumTvServicesInMux = NumRadioServicesInMux = NumTvServicesremoved = NumRadioServicesRemoved = 0;
    
	/* Getting ONID, TS details */
	Bool retval = mGetTSMetaData();

	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
    if(retval == TRUE)
    {
		/* Get Current PTC details from scan module */
        mGetPTCInfo(&ptc);

		TraceNotice (m, "%s %d svcdat.Frequency %ld\n", __FUNCTION__, __LINE__, ptc.Frequency);

		if(mInstallMuxOnTimeout(&ptc) == TRUE )
		{
			/* Add entry to TS Table */
			mAddToTSTable(&ptc);

			if (IsUpdateInstall())
			{
				TraceNotice (m, " TpId %d Freq %d  Polarization %d TV: %d / %d Radio %d / %d  ", (int)ptc.TPID, (int)ptc.Frequency, ptc.Polarization, NumTvServicesInMux ,\
														NumTvServicesremoved, NumRadioServicesInMux,  NumRadioServicesRemoved);
			}
			else
			{
				TraceNotice (m, "TpId %d Freq %d  Polarization %d TV: %d Radio %d ", (int)ptc.TPID, (int)ptc.Frequency, ptc.Polarization, NumTvServicesInMux , NumRadioServicesInMux );
			}
		}
		mDigitalTranspondersFound++;
		TraceNotice (m, " Tranponder Count is %d \n", mDigitalTranspondersFound);
    }
	else
	{
		TraceNotice (m, "PTC Ignored: Invalid PTC or Incomplete Data\n");
	}
}

Bool CHsvDvbsGeneric_mAcq_Priv::mIsLCNAcquistionSupported(void)
{
	Bool retval = FALSE;
	int PackageId = 0;
	
	if(IsManualInstall())
	{
		PackageId = insstate_GetAttribute(UPDATE_MODE, insstate_AttributePackageId);
		TraceNotice (m, "%s PackageId %d\n", __FUNCTION__, PackageId);
		switch(PackageId)
		{
			case CANALDIGITAL_NORWAY_PACKAGE_ID:
			case CANALDIGITAL_SWEDEN_PACKAGE_ID:
			case CANALDIGITAL_FINLAND_PACKAGE_ID:
			case CANALDIGITAL_DENMARK_PACKAGE_ID:
				retval = TRUE;
				break;
			default:
				break;
		}
	}
	
	TraceNotice (m, "%s retval %d\n", __FUNCTION__, retval);
	return retval;
}

Bool CHsvDvbsGeneric_mAcq_Priv::mSyncRecordsForPreDefinedList(void)
{
	Bool	retVal = TRUE;	
	int i, NoOfRecords;
	
	HsvPgdatPresetData			presetData;		
	HsvPgdatDigServiceData		svcdat;
	NoOfRecords = pgdb_GetNoRecords(SERVICE_TABLE);
	
	TraceNotice (m, "%s NoOfRecords %d\n", __FUNCTION__, NoOfRecords);
	
	/* Not many services we find here with creteria to delete here so don't have to do it in incremental steps */
	/* TODO: Check how do we handle the LNB Specific Service Data here */
	
	for(i = 0; (i < NoOfRecords); i++)
	{
		if (TRUE == pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat));
		{
			if(svcdat.PresetNumber != INVALID_PRESET)
			{
				//TraceNotice(m,"PredefListUpdate: ONID: %d TSID: %d SVCID: %d deleted PresetNumber %d", svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,svcdat.PresetNumber);
				presetData.PresetNumber =   svcdat.PresetNumber;						
				pgdb_Delete(PRESET_TABLE, (Address)&presetData);
				
				svcdat.PresetNumber = INVALID_PRESET;
				pgdb_Update(SERVICE_TABLE, (Address)&svcdat);								
			}
		}		
	}
	
	//TraceNotice (m, "%s isvcscandata_SyncComplete sent\n", __FUNCTION__);
	isvcscandata_SyncComplete();

	return retVal;
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}
int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	return (mDigitalTvChannelsFoundInLnb[mCurrentLnb] + mDigitalUserDefinedChannelsFound);
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	return mDigitalRadioChannelsFoundInLnb[mCurrentLnb];
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{	
	return removeCurTv;
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	return removeCurRadio;
}

void CHsvDvbsGeneric_mAcq_Priv::idataacq_SyncTemporaryTableRecords(void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	TraceNotice (m, "UpdateInstall %d IsPredefinedList %d ",  IsUpdateInstall(), mIsPredefinedListPackage());
	if( (IsUpdateInstall()) && (mIsPredefinedListPackage()) )
	{
		pmp_PmpSend(mDataAcqPump, StartSyncRecordsForPreDefinedList, (Nat32)NULL);
	}
	else
	{
		TraceNotice (m, "%s isvcscandata_SyncComplete sent\n", __FUNCTION__);
		isvcscandata_SyncComplete();
	}	
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return mSatDSDesc.NumOfSDSD;
}

Bool CHsvDvbsGeneric_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mSatDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry, &mSatDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	if(Lnb < MAX_LNBS_SUPPORTED)
	{
		TvChannelsFound = mDigitalTvChannelsFoundInLnb[Lnb];
	}

	return TvChannelsFound;
}

int CHsvDvbsGeneric_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	if(Lnb < MAX_LNBS_SUPPORTED)
	{
		RadioChannelsFound = mDigitalRadioChannelsFoundInLnb[Lnb];
	}

	return RadioChannelsFound;
}
int CHsvDvbsGeneric_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{
	int RetVal = FALSE;
	HsvBarkerMuxData BarkerMuxData;
	BarkerMuxData.NoOfRecords = 0;
	if(iutil_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		TraceNotice(m,"Cleared Previous BarkerMux details ");
		RetVal = TRUE;
	}
	
	return RetVal;
}

void CHsvDvbsGeneric_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	//Do Nothing
}

void CHsvDvbsGeneric_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{
	//Do Nothing
}

