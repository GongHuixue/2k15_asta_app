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
 *          %name: hsvdvbsm7_mAcq.c %
 *       %version: TVG_FusnR3ext_22 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: shreeshav %
 */
 
/* include dependencies */
#include	"_hsvdvbsm7_mAcq.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsm7_macq")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

/* TODO: CRC has to be updated */
/* Macros */


													









/* Local Structures and enums */





/****************************************************************************
 * Static variables
 ****************************************************************************/



int CHsvDvbsM7_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsM7_mAcq_Priv::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsM7_mAcq_Priv::s__mDigitalRadioChannelsFound = 0;

Nat16 CHsvDvbsM7_mAcq_Priv::s__NumTvServicesInMux = 0,CHsvDvbsM7_mAcq_Priv::s__NumRadioServicesInMux = 0,CHsvDvbsM7_mAcq_Priv::s__NumTvServicesremoved = 0,CHsvDvbsM7_mAcq_Priv::s__NumRadioServicesRemoved = 0;

Pump CHsvDvbsM7_mAcq_Priv::s__mDataAcqPump;

HsvLnbSettings	CHsvDvbsM7_mAcq_Priv::s__mLnbSettings;

int CHsvDvbsM7_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsM7_mAcq_Priv::s__removeCurRadio =0;

HsvDataAqcInstance CHsvDvbsM7_mAcq_Priv::s__DataAcqInstance;


HsvInstallationPTC CHsvDvbsM7_mAcq_Priv::s__CurrentPTC;


HsvPgdatDigSatInfoData CHsvDvbsM7_mAcq_Priv::s__SatDetails[MAX_LNBS_SUPPORTED];


double CHsvDvbsM7_mAcq_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};



int CHsvDvbsM7_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID] =
{
/*SDSD */HSVSPID(SatelliteDS, dvb, fnt),
/*SLD*/HSVSPID(ServiceList,dvb,fnt),
/*LCD*/HSVSPID(LCN,dvb,fnt),
/*SpidService*/HSVSPID(ActualTSService, dvb, fst)
};


char CHsvDvbsM7_mAcq_Priv::s__M7LockString[10] = "(18+)";	


/****************************************************************************
 * Static functions
 ****************************************************************************/


/* Static functions */




























void CHsvDvbsM7_mAcq_Priv::mPumpHandler(int value, Nat32 param)
{
	TraceInfo (m," mPumpHandler %d value",value);
	UNUSED(param);
	switch(value)
	{
	case EvStartAcquire:
		mStartAcquisistion(value);
		break;
	case EvAcquireTSInfo:
		mAcquireTSInfo();
		break;
	case EvCompleteAcquire:
		/*Give acquire complete notification*/
		idataacqN_OnDataAquired(TRUE);
		TraceNotice (m, "EvCompleteAcquire at %s %d", __FUNCTION__, __LINE__);
		break;
	}
		
}

void CHsvDvbsM7_mAcq_Priv::mStartAcquisistion(int value)
{
	/*Get all Satellite details from SAT_INFO_TABLE */
	mGetSatelliteDetails();
	/*Collect no. of Sdsds*/
	mCollectSdsds();
	/*start acquiring TSinfo*/
	pmp_PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	
}


void CHsvDvbsM7_mAcq_Priv::mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,fnt) Sdsd, HsvInstallationPTC *ptc)
{
	int	TransponderFreq;
	ptc->LnbNumber = DataAcqInstance.LnbNumber;
	ptc->Polarization = Sdsd.Polarization;	
	ptc->Frequency = Sdsd.Frequency;
	ptc->SDSDFrequency = Sdsd.Frequency;
	ptc->SymbolRate = Sdsd.SymbolRate;
	ptc->ModulationType = Sdsd.ModulationType;
	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);
	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
	//ptc->QSignalStrength = 0;
	//ptc->SSignalStrength = 0;
	//ptc->HierarchyMode = HsvHierarchyNone;
	//ptc->StreamPriority = HsvStreamPriorityHigh;
	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);


}

void CHsvDvbsM7_mAcq_Priv::mAcquireTSInfo(void)
{
	HSVSPTYPE(SatelliteDS,dvb,fnt) CurrentSdsd;
	Bool IsKeyUpdate = FALSE;
	int TPID = 0;

	TraceInfo  (m, " DataAcqInstance.CurSdsd %d DataAcqInstance.NumSdsds %d sizeof(CurrentSdsd) %d", DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(CurrentSdsd));
	while(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
	{
		NumTvServicesInMux = NumRadioServicesInMux = NumTvServicesremoved = NumRadioServicesRemoved = 0;
		IsKeyUpdate = FALSE;
		if(strapi_GetByIndex(HsvMain, GETHSVSPID(Sdsd), DataAcqInstance.CurSdsd, (void *)(&CurrentSdsd)) == TRUE)
		{
			if(mCheckTSForInstall(CurrentSdsd) == TRUE)
			{
				DataAcqInstance.NetworkId = CurrentSdsd.NetworkId;
				DataAcqInstance.Onid	= CurrentSdsd.Original_NetworkId;
				DataAcqInstance.Tsid = CurrentSdsd.Tsid;
				mGetPTCInfo(CurrentSdsd,&CurrentPTC);

				if(IsUpdateInstall() == TRUE)
				{
					mAddToTSTable(&CurrentPTC, &IsKeyUpdate, &TPID);
					if(IsKeyUpdate == TRUE)
					{
						mInstallMux(&CurrentPTC,IsKeyUpdate, TPID);
					}
					else
					{
						/*If No keys are updated just Install the mux*/
						if(mInstallMux(&CurrentPTC, IsKeyUpdate, TPID) == FALSE )
						{
							/* If no services are added, delete entry from TS Table */
							mDeleteTSTable(&CurrentPTC);
						}
					}
					TraceNotice (m, "TpId %d Freq %d  Polarization %d TV: %d / %d Radio %d / %d  ", CurrentPTC.TPID, (int)CurrentPTC.Frequency, CurrentPTC.Polarization, NumTvServicesInMux ,\
														NumTvServicesremoved, NumRadioServicesInMux,  NumRadioServicesRemoved);
				}
				else
				{
					/*If Auto install Intsall the services and Add to TS Table*/
					if(mInstallMux(&CurrentPTC, IsKeyUpdate, TPID) == TRUE )
					{
						/* Add entry to TS Table */
						TraceNotice (m, "TpId %d Freq %d  Polarization %d TV: %d Radio %d ", CurrentPTC.TPID, (int)CurrentPTC.Frequency, CurrentPTC.Polarization, NumTvServicesInMux , NumRadioServicesInMux );
						mAddToTSTable(&CurrentPTC, &IsKeyUpdate, &TPID);
					}
				}
				/*Increment CurSdsd after installing mux*/
				DataAcqInstance.CurSdsd++;
				break;
			}
			else
			{
				/*if Sdsd is not installable move to next Sdsd */			
				DataAcqInstance.CurSdsd++;
				TraceNotice(m,"Can not install this CurrentSdsd = %d ",DataAcqInstance.CurSdsd);
			}
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
		/*Delete all Carriers(SDSDs) removed from FNT */
		if(IsUpdateInstall() == TRUE)
		{
			mDeleteMuxesFromCurrentFNT();
		}
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);	
	}
	else
	{
		pmp_PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	}
}


void CHsvDvbsM7_mAcq_Priv::mDeleteTSTable(HsvInstallationPTC *ptc)
{
	HsvPgdatDigTSData   tsdata;
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Frequency				= ptc->Frequency;
	tsdata.Polarization				= ptc->Polarization;
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tsdata) == TRUE )
	{
		TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization);
		pgdb_Delete(PTC_TABLE, (Address )&tsdata);
	}
}

void CHsvDvbsM7_mAcq_Priv::mDeleteMuxesFromCurrentFNT(void)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	HSVSPTYPE(SatelliteDS,dvb,fnt) tmpsdsd;
	int NoOfTSTables = 0 , i = 0;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

	for(i = 0; i<NoOfTSTables; i++)
	{
		pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
		if((pgdb_GetByIndex(PTC_TABLE, i, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
		{	/*Check if this TS table present in SDSD list*/
			if(strapi_GetByKey(HsvMain, GETHSVSPID(Sdsd), tmptsdata.OriginalNetworkId, tmptsdata.Tsid, tmptsdata.NetworkId, (void *)(&tmpsdsd)) == FALSE)			
			{
				mDeleteAllServicesFromCarrier(tmptsdata.Tpid);
				TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization);
				pgdb_Delete(PTC_TABLE, (Address) &tmptsdata);
			}
		}
	}

}

/*KeyUpdated indicates if any keys(i.e. Frequency/polarization) of TS Table are updated in SDSD,
If any Key/Keys are updated it will return TPID of old TStable which is deleted */
void CHsvDvbsM7_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, Bool *KeyUpdated, int *TPIDOld)
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
//	tsdata.CodeRate					= ptc->CodeRateHigh;
	//tsdata.HierarchyMode				= ptc->HierarchyMode;
//	tsdata.IqMode					= ptc->IqMode;
	tsdata.Bandwidth				= ptc->ChannelBandwidth;
	//tsdata.StreamPriority			= ptc->StreamPriority;
	//TODO: Implement GetInstallationVersion in mScan
	tsdata.PtcListVersion			= isvcscandata_GetInstallationVersion();
	//tsdata.QSignalStrength			= ptc->QSignalStrength;
	//tsdata.SSignalStrength			= ptc->SSignalStrength;
//	tsdata.ChannelInformation		= ptc->ChannelInformation;
	tsdata.SDSDFrequency			= ptc->SDSDFrequency;
	tsdata.UserInstalled			= IsManualInstall();
//    tsdata.TSVersion				= DataAcqInstance.TsVersionNum;
//	tsdata.SDTVersion				= DataAcqInstance.SDTVersion;
	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Polarization				= ptc->Polarization;
	tsdata.Tpid						= ptc->TPID;

	tmptsdata.LnbNumber				= tsdata.LnbNumber;
	tmptsdata.Frequency				= tsdata.Frequency;
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
				
				if((pgdb_GetByIndex(PTC_TABLE, i, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
				{
					if((tmptsdata.OriginalNetworkId == tsdata.OriginalNetworkId) && (tmptsdata.Tsid == tsdata.Tsid))
					{
						*KeyUpdated = TRUE;
						*TPIDOld = tmptsdata.Tpid;
						/*Delete the Old TS Table with old TPID and Keys and Add new TS Table with updated TPID and keys */
						pgdb_Delete(PTC_TABLE, (Address)&tmptsdata);
						TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization);
						pgdb_Add(PTC_TABLE, (Address )&tsdata);
						TraceNotice (m, "Addition to pgdb table %s %d <%ld %d>", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization);
						break;						
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
			pgdb_Add(PTC_TABLE, (Address )&tsdata);
		}

	}
	else
	{
		//TraceNotice (m, "Updation to pgdb table %s %d <%ld %d>", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.StreamPriority);
		pgdb_Update(PTC_TABLE, (Address )&tsdata);
	}
}



Bool CHsvDvbsM7_mAcq_Priv::mInstallMux(HsvInstallationPTC *ptc, Bool IsKeyUpdate, int OldTPID)
{
	Bool	retval = FALSE, channelExists = FALSE, IsDuplicatesvc = FALSE, IsServiceAdded = FALSE;
	int		i, InstalledServices = 0;
	HSVSPTYPE(ServiceList, dvb, fnt) servicelist;
	HSVSPTYPE(LCN, dvb, fnt) 		logicalchannel;
	HSVSPTYPE(ActualTSService, dvb, fst) service;
	HsvPgdatDigServiceData 		svcdat, tempsvcdat;
	HsvPgdatPresetData			presetData;	
	int from = 0, to = 0;
	
	strapi_GetRangeByKey(HsvMain, GETHSVSPID(SLD), 2, DataAcqInstance.Onid, DataAcqInstance.Tsid, 0, &from, &to);
	TraceNotice (m, "%s %d NoOfServices in MUX = %d ONID = %d TSID = %d ",__FUNCTION__, __LINE__, ((to - from)+1),DataAcqInstance.Onid, DataAcqInstance.Tsid);


	/* From strapi get all the services and add/update in SERVICE_TABLE */
	for(i = to; i >= from ; i--)
	{
		IsDuplicatesvc = FALSE;
		IsServiceAdded = FALSE;
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

		if(strapi_GetByIndex(HsvMain, GETHSVSPID(SLD), i, (void *)(&servicelist)) == TRUE)
		{
			/*If db key(TPID) is updated, delete the service and add it again with new TPID as TPID is the key for service table*/
			if(IsKeyUpdate == TRUE)
			{
				svcdat.Tpid = OldTPID;
				svcdat.ServiceId = servicelist.ServiceId;

				if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat) == TRUE)
				{
					IsDuplicatesvc = TRUE;
				}
			}

			svcdat.OriginalNetworkId = DataAcqInstance.Onid;
			svcdat.Tsid 			  = DataAcqInstance.Tsid;
			svcdat.LnbNumber 		  = ptc->LnbNumber;
			svcdat.Polarization 		  = ptc->Polarization;
			svcdat.Tpid	       	  = ptc->TPID;
			svcdat.Frequency		= ptc->Frequency;
			svcdat.SDSDFrequency	= ptc->SDSDFrequency;

			svcdat.ServiceId = servicelist.ServiceId;
			service.ServiceName[0] = '\0';
			
			if(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService), svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, (void *)(&service)) == TRUE)			
			{
				TraceInfo (m, " FST:SvcId %d and SvcType %d ", service.ServiceId, service.ServiceType);
				if(mIsServiceInstallable(ptc, &service))
				{
				    	 svcdat.ServiceType = service.ServiceType;
					 logicalchannel.LogicalChannelNum = INVALID_LCN;	
				    	if(strapi_GetByKey(HsvMain, GETHSVSPID(LCD), svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, (void *)(&logicalchannel)) == TRUE)
					{
						svcdat.LCN = logicalchannel.LogicalChannelNum;
						svcdat.VisibleService = logicalchannel.VisibleService;
					}
					else
					{
						TraceDebug (m, " Get LCD failed for ONID: %d TSID: %d SvcId %d ", svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId);
					}

					TraceInfo (m, " LCD: SvcId %d and SvcType %d ", service.ServiceId, service.ServiceType);
					tempsvcdat.Tpid	 = svcdat.Tpid;
					tempsvcdat.ServiceId	 = svcdat.ServiceId;

					channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
					if(channelExists)
					{
						TraceNotice (m, " Channel exists SvcId %d and SvcType %d ", service.ServiceId, service.ServiceType);
						/* If entry already present update the service data */
						mUpdateService(&svcdat, ptc, &service);
						retval = TRUE;	

					}
					else
					{
						mAddNewService(&svcdat, ptc, &service, IsDuplicatesvc);
						IsServiceAdded = TRUE;
						if(IsDuplicatesvc == FALSE)
						{
							InstalledServices++;
						}
						
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
							NumTvServicesremoved++;
							removeCurTv++;
						}
						else if (IsDigitalRadioService (&tempsvcdat))
						{
							NumRadioServicesRemoved++;
							removeCurRadio++;
						}

						presetData.PresetNumber = tempsvcdat.PresetNumber;
						pgdb_Delete(SERVICE_TABLE, (Address)&tempsvcdat);
						TraceNotice (m, " Service deleted : SvcId %d and SvcType %d ", service.ServiceId, service.ServiceType);
						
						if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
						{
							pgdb_Delete(PRESET_TABLE, (Address)&presetData);
						}				
					}

					TraceNotice (m, " Service not installable: SvcId %d and SvcType %d ", service.ServiceId, service.ServiceType);
				}
			}
		}

		if(IsDuplicatesvc )
		{
			/*Delete the duplicate service with old TPID,svcid*/
			pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
			tempsvcdat.Tpid = OldTPID;
			tempsvcdat.ServiceId = servicelist.ServiceId;
			pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
			presetData.PresetNumber = tempsvcdat.PresetNumber;
			pgdb_Delete(SERVICE_TABLE, (Address )&tempsvcdat);

			/*Delete the preset table, if the service is not added with new TPID*/
			if(IsServiceAdded == FALSE)
			{
				pgdb_Delete(PRESET_TABLE, (Address)&presetData);
			}
			
		}

	}

	if(IsUpdateInstall())
	{
		if (IsKeyUpdate == FALSE)
		{
			mDeleteServicesCurrentCarrier(ptc);
		}
		else
		{
			mDeleteAllServicesFromCarrier(OldTPID);
		}
	}

	TraceNotice (m, "Updateprint: Num TV: %d Num Radio: %d ", mDigitalTvChannelsFound, mDigitalRadioChannelsFound);
       return retval;
}

void CHsvDvbsM7_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
{
	HSVSPTYPE(ServiceList, dvb, fnt) service;
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;
	HSVSPTYPE(ActualTSService, dvb, fst) fstservice;
	
	TempSvcData.Tpid 		 = ptc->TPID;
	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{
		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			
			if ( (RetVal == TRUE) &&
				 ( (strapi_GetByKey(HsvMain, GETHSVSPID(SLD),TempSvcData.OriginalNetworkId, TempSvcData.Tsid,TempSvcData.ServiceId, (Address)(&service)) == FALSE)
				 ||(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService), TempSvcData.OriginalNetworkId, TempSvcData.Tsid, TempSvcData.ServiceId, (void *)(&fstservice)) == FALSE) )	&&
				 (TempSvcData.SDSDFrequency != 0)) /* Dont delete services installed by generic module*/
			{
				TraceNotice (m, "Delete servicess Ser-id[%d] Tsid[%d] Onid[%d]",
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

void CHsvDvbsM7_mAcq_Priv::mDeleteAllServicesFromCarrier(int TPID)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;	

	TempSvcData.Tpid 		 = TPID;

	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{

		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			if ( RetVal == TRUE)
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
				TraceNotice (m, "Delete servicess Ser-id[%d] Tsid[%d] Onid[%d]",
				TempSvcData.ServiceId,
				TempSvcData.Tsid,
				TempSvcData.OriginalNetworkId );

				pgdb_Delete(SERVICE_TABLE, (Address)&TempSvcData);
				
				if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
				{
					pgdb_Delete(PRESET_TABLE, (Address)&presetData);
				}				


			}

		}
	}

	
}

void CHsvDvbsM7_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, fst)* service)
{
	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mAssignSvcNonBroadcastAttributes(psvcdat);
	mUpdateSatelliteName (psvcdat);

	pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
		
	TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbsM7_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;

	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
	}
}

void CHsvDvbsM7_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, fst) *service, Bool IsDuplicatesvc)
{
	Nat8	ToAdd = FALSE;
	HsvPgdatPresetData			PresetData;	

	/* Filling details of service, then adding it */	
	mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mUpdateSatelliteName (psvcdat);
	
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
			NumTvServicesInMux++;
		}
	}
	else if (IsDigitalRadioService (psvcdat))
	{
		ToAdd = TRUE;
		if(IsDuplicatesvc == FALSE)
		{			
			mDigitalRadioChannelsFound++;
			mDigitalChannelsFound++;
			NumRadioServicesInMux++;
		}
	}

	/* Add to service table */
	if (ToAdd == TRUE)
	{
		/* Add only if its TV or Radio Service */
		pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
		TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d SystemHidden = %d",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId,psvcdat->SystemHidden);
		
	}
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

Bool CHsvDvbsM7_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}
/*AN-74988*/
Bool CHsvDvbsM7_mAcq_Priv::mCheckChannelLock(Nat16* src)
{
	Nat16 Unicode_Lockstring[10];
	int loop = 0;
	Bool retval = TRUE;
	Nat16* dest = Unicode_Lockstring;

	/*Convert to unicode*/
    while( loop < strlen(M7LockString))
    {
        Unicode_Lockstring[loop] = M7LockString[loop];
        ++loop;
    }
	Unicode_Lockstring[loop] = 0;

	/*Compare the strings*/
    while((*src) && (*dest) && (*dest++ == *src++));
	if(*dest)
	{
		retval = FALSE;
	}
	else
	{
		TraceNotice(m," %s: Channel Locked, RetVal: %d",__FUNCTION__, retval);
	}
	return retval;
}




void CHsvDvbsM7_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, fst) *service)
{
	psvcdat->NetworkId			   =   service->NetworkId;
	psvcdat->ModulationType        =   ptc->ModulationType;
	psvcdat->Bandwidth	   			=   ptc->ChannelBandwidth;
	//psvcdat->StreamPriority		   =   ptc->StreamPriority ;	
	psvcdat->SymbolRate            =   ptc->SymbolRate;
	psvcdat->ServiceType           =   mConvertToPgdatServiceType(service->ServiceType);
    //psvcdat->Type                  =   GETSERVICETYPE(service->ServiceType);
	psvcdat->FreeCiMode	    	   =   FALSE;
/*	psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;//Not Required
	psvcdat->NumBrandIds	       =   service->NumBrandIds;//Not Required*/
	
	psvcdat->AudioPid              =   INVALID_PID;//service->Default_audio_PID;
	psvcdat->VideoPid              =   INVALID_PID; //service->Default_video_PID;
	psvcdat->PcrPid                =   INVALID_PID; //service->Default_PCR_PID;
	psvcdat->LnbNumber			   =   ptc->LnbNumber;
	psvcdat->Polarization		   =   ptc->Polarization;
	psvcdat->Tpid				   =   ptc->TPID;
	
	//psvcdat->NumericSelect = TRUE;
	psvcdat->SystemHidden = !(psvcdat->VisibleService);


//	mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds ); //Not Required
	mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_PresetNameLength - 1) );

}

void CHsvDvbsM7_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
	int mode, state;
	Bool Proceed = FALSE;
	HsvPgdatPresetData			presetData;		
	HsvPgdatDigServiceData		svcdat;

	rins_GetCurrentInstallationState(&mode, &state);
	
	psvcdat->UserHidden             = FALSE;
	psvcdat->ChannelLock		    = FALSE;
	/*AN-74988*/
	if(mCheckChannelLock(psvcdat->ChannelName))
	{
		psvcdat->ChannelLock		    = TRUE;		
	}
	psvcdat->Favorite			    = FALSE;
	//psvcdat->PreferredStereo	    = 1;
	psvcdat->DateStamp			    = 0;
	psvcdat->PresetNumber		    = INVALID_PRESET;
	psvcdat->ServiceListVersion     = isvcscandata_GetInstallationVersion();
	psvcdat->NewPreset				= (mode == AUTO_MODE)? FALSE : TRUE;
	psvcdat->HbbTvOption 			= 1;
	psvcdat->PackageGroup			= APPAPISAT_M7;
	psvcdat->UserInstalled 			= (mLnbSettings.LnbSettings[DataAcqInstance.LnbNumber].LnbStatus == LnbM7Installed);

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
	{
		psvcdat->NewPreset				= svcdat.NewPreset;
		/* ANEESH: TODO: Check with Pavan whether need to keepthe preset number */
		//psvcdat->EPGEnabled				= svcdat.EPGEnabled;
		psvcdat->ChannelLock			= svcdat.ChannelLock;;
		psvcdat->UserHidden				= svcdat.UserHidden;
		psvcdat->Favorite				= svcdat.Favorite;
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
		psvcdat->PresetNumber		    = svcdat.PresetNumber;
		psvcdat->PackageGroup		   =  svcdat.PackageGroup;
		psvcdat->FavoriteNumber			= svcdat.FavoriteNumber;
		psvcdat->UserInstalled 			= svcdat.UserInstalled;
		
		if (mCompareUnicodeString(psvcdat->ChannelName, svcdat.ChannelName) == FALSE)
		{
			TraceNotice(m, "Service name updated");
			psvcdat->LogoURL = 0;
		}
		else
		{
			TraceNotice(m, "Service name is same");
		}
		Proceed = (!VALID_LCN_RANGE(svcdat.LCN))&&(IS_RADIO_SERVICE(psvcdat->ServiceType) != IS_RADIO_SERVICE(svcdat.ServiceType));
		REVALIDATE(svcdat.LCN);
		Proceed |= ((VALID_LCN_RANGE(psvcdat->LCN) || VALID_LCN_RANGE(svcdat.LCN)) && (psvcdat->LCN != svcdat.LCN));
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


int CHsvDvbsM7_mAcq_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
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

Bool CHsvDvbsM7_mAcq_Priv::mCheckTSForInstall(HSVSPTYPE(SatelliteDS,dvb,fnt) Sdsd)
{
	int i;
	Bool	RetVal = FALSE;
	for(i=0; i < MAX_LNBS_SUPPORTED; i++)
	{
		/*Check if satellite corresponding to this TS is installed and update the lnbnumber*/
		TraceNotice(m,"OrbitalPosition[%d]  Sdsd.OrbitalPosition[%d] ",SatDetails[i].OrbitalPosition,Sdsd.OrbitalPosition);
		if(SatDetails[i].OrbitalPosition == Sdsd.OrbitalPosition)
		{
			DataAcqInstance.LnbNumber = i;
			RetVal = TRUE;
			break;
		}
	}
	return RetVal;
}

void CHsvDvbsM7_mAcq_Priv::mGetSatelliteDetails(void)
{
	int i;
	/*Get Satellite details of all LNBs*/
	for(i=0; i < MAX_LNBS_SUPPORTED; i++)
	{
		SatDetails[i].LnbNumber = i;
		TraceNotice (m,"SatDetails[i].LnbNumber = %d ",SatDetails[i].LnbNumber);
		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails[i]) != TRUE)
		{
			TraceErr (m," ERROR: Getting Sat. details failed for LNB: %d!!! ",i);
		}
	}

	if (err_Ok != idvbset_GetLnbSettings (&mLnbSettings))
	{
		TraceErr (m,"%s: ERROR: GetLnbSettings FAILED",__FUNCTION__);
	}

}


int CHsvDvbsM7_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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
			/*
		case PALCodedSignal:
			retval  =	AppApiPALCodedSignal;
			break;
		case SECAMCodedSignal:
			retval  =	AppApiSECAMCodedSignal;
			break;
		case UserDefinedHD1:
			retval  =	AppApiUserDefinedHD1;
			break;
		case UserDefinedHD2:
			retval  =	AppApiUserDefinedHD2;
			break;
		case UserDefinedHD3:
			retval  =	AppApiUserDefinedHD3;
			break;
		case UserDefinedHD4:
			retval  =	AppApiUserDefinedHD4;
			break;
			*/
		/*case	0x80 ... 0xFF:			// ANEESH: TODO: Check this logic 
			retval  =   AppApiTelevisionService;
			break;
			*/
		case	0x1C:
			retval  =   AppApiTelevisionService;
			break;
        default:
            break;
    }
    return retval;
}

Bool CHsvDvbsM7_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
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
	case	AppApiHevcService:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsM7_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsM7_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}


Bool CHsvDvbsM7_mAcq_Priv::mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, fst)* service)
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

void CHsvDvbsM7_mAcq_Priv::mCollectSdsds (void)
{
	/* Just keeping the Number Of Sdsds alone. Getting each entry will be done seperately */
	DataAcqInstance.NumSdsds = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, fnt));
	TraceNotice (m," DataAcqInstance.NumSdsds %d ",DataAcqInstance.NumSdsds);
	DataAcqInstance.CurSdsd = 0;
}

Bool CHsvDvbsM7_mAcq_Priv::IsManualInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsM7_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate))? TRUE: FALSE);
}
/*
static Bool IsServiceScanInstall (void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insconst_InstallationServiceScan)? TRUE: FALSE);
}
*/

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsM7_mAcq_Priv::iacqpow_Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbm7_mDataAcq" );
	
	TraceNotice (m, " M7Acq Module pow Initialized ");

}

void CHsvDvbsM7_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsM7_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsM7_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
    int i;
    /* Resetting all the variables */
    mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
    removeCurTv = removeCurRadio = 0;

	for(i=0; i < MAX_LNBS_SUPPORTED; i++)
	{
		pgdb_Initialise(pgdbconst_SatInfo, (Address) &SatDetails[i]);
	}
	UNUSED(LnbNumber);
}

void CHsvDvbsM7_mAcq_Priv::idataacq_AcquireData(int Mode)
{

	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)NULL);
	UNUSED(Mode);
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);
	
	return removeCurTv;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);
	
	return removeCurRadio;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return DataAcqInstance.NumSdsds;
}

Bool CHsvDvbsM7_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;

	return RetVal;
}


int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);
	
	return RadioChannelsFound;
}

int CHsvDvbsM7_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
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

void CHsvDvbsM7_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{

}

void CHsvDvbsM7_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{

}

void CHsvDvbsM7_mAcq_Priv::idataacq_AcquireDataOnTimeout                        (   void    )
{
}

void CHsvDvbsM7_mAcq_Priv::idataacq_SyncTemporaryTableRecords			(	void	)
{
}
