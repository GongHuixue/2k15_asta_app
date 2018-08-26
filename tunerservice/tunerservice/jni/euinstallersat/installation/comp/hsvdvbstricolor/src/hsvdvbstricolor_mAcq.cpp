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
 *          %name: hsvdvbstricolor_mAcq.c %
 *       %version: TVG_20 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: aneeshc %
 */
 
/* include dependencies */
#include	"_hsvdvbstricolor_mAcq.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbstricolor_macq")


/****************************************************************************
 * Static variables
 ****************************************************************************/

TricolorServiceList CHsvDvbsTricolor_mAcq_Priv::s__mSvcListData;

TricolorSatDSDesc CHsvDvbsTricolor_mAcq_Priv::s__mTricolorDSDesc;


int CHsvDvbsTricolor_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsTricolor_mAcq_Priv::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsTricolor_mAcq_Priv::s__mDigitalRadioChannelsFound = 0;

Pump CHsvDvbsTricolor_mAcq_Priv::s__mDataAcqPump;


int CHsvDvbsTricolor_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsTricolor_mAcq_Priv::s__removeCurRadio =0;

HsvDataAcqInstance CHsvDvbsTricolor_mAcq_Priv::s__DataAcqInstance;

HsvInstallationPTC CHsvDvbsTricolor_mAcq_Priv::s__CurrentPTC;


double CHsvDvbsTricolor_mAcq_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};



int CHsvDvbsTricolor_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID][2] = 
{
    /*Onid*/     { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)   },
    /*Tsid*/     { HSVSPID(ActualTsId, dvb, sdt),                 HSVSPID(OtherTsId, dvb, sdt)                },
    /*VerNo*/    { HSVSPID(ActualTsVersionNo, dvb, sdt),          HSVSPID(OtherTsVersionNo, dvb, sdt)         },
    /*SLD*/    	 { HSVSPID(ActualServiceList, dvb, nit),          HSVSPID(OtherServiceList, dvb, nit)         },
    /*SDSD*/     { HSVSPID(SatelliteDS, dvb, nit),          HSVSPID(SatelliteDS, dvb, nit)         },
/*SpidService*/  { HSVSPID(ActualTSService, dvb, sdt),            HSVSPID(OtherSDTSection, dvb, sdt)          },
    /*LCNv1*/    { HSVSPID(ActualNetworkLCN,dvb,nit),			  HSVSPID(OtherNetworkLCN, dvb, nit)		  },
    /*LCNv2*/    { HSVSPID(ActualNetworkLCN2,dvb,nit),			  HSVSPID(OtherNetworkLCN2, dvb, nit)		  }
};



/****************************************************************************
 * Internal functions
 ****************************************************************************/

void CHsvDvbsTricolor_mAcq_Priv::mPumpHandler(int value, Nat32 param)
{
	
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
		case EvCompleteAcquire:
			/*Give acquire complete notification*/
			idataacqN_OnDataAquired(param);
			TraceNotice (m, "Num of Channels %d, Added TV %d Radio %d. Removed TV %d Radio %d",
							mDigitalChannelsFound, mDigitalTvChannelsFound, mDigitalRadioChannelsFound,
							removeCurTv,removeCurRadio );
			break;
	}
		
}

void CHsvDvbsTricolor_mAcq_Priv::mStartHomingAcquisition(void)
{
	Bool Result = TRUE;

	
	/*Collect Sdsds from strapi*/
	mCollectSdsds();
	mGetSatelliteLnbNo(EUTELSAT_W4_36E);
	mCollectServicelistData();

	
	if(IsUpdateInstall())
	{
		if(mCheckFederalChannelListNamePresent() == FALSE)
		{
			Result = FALSE;
		}
	}

	
	pmp_PmpSend(mDataAcqPump, EvCompleteAcquire,(Nat32)Result);
	
}

void CHsvDvbsTricolor_mAcq_Priv::mStartFallbackAcquisition(void)
{
	KeyUpdateReason 	KeyUpdate = NoUpdate;
	HsvPgdatDigTSData	OldTsData;

	/* Getting ONID, TS details */
	Bool retval = mGetTSMetaData();

	
	DataAcqInstance.NetworkId = mTricolorDSDesc.SatDesc[mTricolorDSDesc.CurrentSDSDIndex].NetworkId;

	if(retval == TRUE)
	{

		TraceNotice(m,"cursdsd %d current sdt tsid %d & sdsd tsid %d",mTricolorDSDesc.CurrentSDSDIndex,DataAcqInstance.Tsid,mTricolorDSDesc.SatDesc[mTricolorDSDesc.CurrentSDSDIndex].Tsid);
		TraceNotice(m,"current sdt onid %d & sdsd onid %d",DataAcqInstance.Onid,mTricolorDSDesc.SatDesc[mTricolorDSDesc.CurrentSDSDIndex].Original_NetworkId);

		if((DataAcqInstance.Onid == mTricolorDSDesc.SatDesc[mTricolorDSDesc.CurrentSDSDIndex].Original_NetworkId)&&
		   (DataAcqInstance.Tsid == mTricolorDSDesc.SatDesc[mTricolorDSDesc.CurrentSDSDIndex].Tsid))
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
				
				if(mTricolorDSDesc.CurrentSDSDIndex == (mTricolorDSDesc.NumOfSDSD-1))
				{
					/*check if some Muxes are deleted in SDSD and delete services from those MUX*/
					mDeleteServicesFromDeletedMuxes();
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

	
			pmp_PmpSend(mDataAcqPump, EvCompleteAcquire,(Nat32)TRUE);	
				
			
		}
		else
		{
			TraceNotice(m,"current Onid and Tsid Did not match with SDT, so skipping this Mux..!");
			pmp_PmpSend(mDataAcqPump, EvCompleteAcquire,(Nat32)TRUE);
		}
	}
	
}

void CHsvDvbsTricolor_mAcq_Priv::mDeleteTSTable(HsvInstallationPTC *ptc)
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



/*Keyupdate reason indicates if any key(freq/pol) is updated in SDSD or due to Acq. mode change.  
if Acq mode changed in update install, ptc frequnecy may change as tuner will not be locked to 
exact SDSD freq, in this case old ferquency is retained. If SDSD freq\pol. is changed 
then old Tpid entry is deleted and new entry is added with new freq\pol and oldTpid is returned*/
void CHsvDvbsTricolor_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, KeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData)
{

	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0 , i = 0;
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);

	/* Filling attributes from ptc, and acqinstance */
	tsdata.Frequency				= ptc->Frequency;
	tsdata.SymbolRate				= ptc->SymbolRate;

	tsdata.OriginalNetworkId		= DataAcqInstance.Onid;
	tsdata.Tsid						= DataAcqInstance.Tsid;
	tsdata.NetworkId				= DataAcqInstance.NetworkId;
	tsdata.ModulationType			= ptc->ModulationType;

	tsdata.Bandwidth				= ptc->ChannelBandwidth;

	tsdata.PtcListVersion			= isvcscandata_GetInstallationVersion();
	tsdata.SDSDFrequency			= ptc->SDSDFrequency;
	tsdata.UserInstalled			= FALSE;
	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Polarization				= ptc->Polarization;
	tsdata.Tpid						= ptc->TPID;
	tsdata.IqMode					= ptc->ModulationStd;
	tsdata.CodeRate					= ptc->CodeRate;


	tmptsdata.LnbNumber			= tsdata.LnbNumber;
	tmptsdata.Frequency			= tsdata.Frequency;
	tmptsdata.Polarization		= tsdata.Polarization;

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
							(ABS(tmptsdata.Frequency, tsdata.Frequency) >= FREQ_DRIFT_TOLERANCE))
						{
							*KeyUpdate = SDSDChange;
				
							/*Delete the Old TS Table with old Tpid and Add new TS Table with updated Tpid and keys */
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



Bool CHsvDvbsTricolor_mAcq_Priv::mInstallFallbackMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	int		i, InstalledServices = 0;

		
	TraceNotice(m,"mSvcListData.NumOfRecords %d",mSvcListData.NumOfRecords);
	for(i = 0; i < mSvcListData.NumOfRecords ; i++)
	{
		if(mCheckServiceForInstall(&ptc, KeyUpdate,OldTsData,i))
		{
			InstalledServices++;				
			retval = TRUE;
		}

	}
	if(IsUpdateInstall())
	{
		if (KeyUpdate == SDSDChange)
		{
			/*Here OldTpid will remain with non transmitted services*/
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

Bool CHsvDvbsTricolor_mAcq_Priv::mGetTSMetaData()
{
    Bool	retval = FALSE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain,  HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &DataAcqInstance.Tsid);

	TraceNotice (m, "ONID %d and TsId %d \n",DataAcqInstance.Onid,DataAcqInstance.Tsid);

    return retval;
}
Bool CHsvDvbsTricolor_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC *ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData,int currentServiceListIndex)
{
	Bool	retval = FALSE, channelExists = FALSE, IsDuplicatesvc = FALSE, IsServiceAdded = FALSE, ToAdd = FALSE;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvPgdatDigServiceData 		svcdat, tempsvcdat;
	HsvPgdatPresetData			presetData;	
	int LoopCount = 0,sdtSize = 0;

	IsDuplicatesvc = FALSE;
	IsServiceAdded = FALSE;
	ToAdd = FALSE;
	pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		svcdat.MultipleLCN[LoopCount] = INVALID_LCN;
		svcdat.MultiplePreset[LoopCount] = INVALID_PRESET;
	}
		
	
	/*If db key(TPID) is updated, delete the service and add it again with new TPID (as TPID is the key for service table)*/
	if(KeyUpdate == SDSDChange)
	{
		svcdat.Tpid = OldTsData->Tpid;
		svcdat.ServiceId = mSvcListData.mSvcListInfo[currentServiceListIndex].ServiceId;

		if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat) == TRUE)
		{
			IsDuplicatesvc = TRUE;
		}
	}


	svcdat.Frequency		  = ptc->Frequency;
	svcdat.OriginalNetworkId  = DataAcqInstance.Onid;
	svcdat.Tsid 			  = DataAcqInstance.Tsid;
	svcdat.LnbNumber 		  = ptc->LnbNumber;
	svcdat.Polarization 	  = ptc->Polarization;
	svcdat.Tpid	       	  	= ptc->TPID;
	svcdat.ServiceId		= mSvcListData.mSvcListInfo[currentServiceListIndex].ServiceId;
	svcdat.VisibleService 	= mSvcListData.mSvcListInfo[currentServiceListIndex].MultipleVisibleServiceFlag[0];
	svcdat.NetworkId		= DataAcqInstance.NetworkId;
    svcdat.SDSDFrequency	= ptc->SDSDFrequency;

	memset(&service, 0, sizeof(HSVSPTYPE(ActualTSService, dvb, sdt)));
	sdtSize = strapi_GetSize(HsvMain,HSVSPID(ActualTSService, dvb, sdt));
	
	//TraceNotice(m,"SDT actual quering with  onid %d sid %d tsid %d sdtSize %d",svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid,sdtSize);
	if(strapi_GetByKey(HsvMain, HSVSPID(ActualTSService, dvb, sdt), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == TRUE)
	{
		if(mIsServiceInstallable(&service) == TRUE)
		{
			TraceNotice(m,"SDT ACTUAL avilable & also Installable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );	
			svcdat.ServiceType = service.ServiceType;
			ToAdd = TRUE;
		}
		else
		{
			//TraceNotice(m,"service is not installable onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );	
		}
	}
	else
	{
		//TraceNotice(m,"SDT Actual not avilable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
	}

	
	if(ToAdd == TRUE)
	{
		TraceNotice (m, " SDT:SvcId %d and SvcType %d \n", service.ServiceId, service.ServiceType);
		
		tempsvcdat.Tpid	         = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		
		if(channelExists)
		{
			TraceNotice (m, "Channel exists SvcId %d and SvcType %d \n", service.ServiceId, service.ServiceType);
			mUpdateService(&svcdat, ptc, &service,currentServiceListIndex);
			retval = TRUE;	

		}
		else
		{
			mAddNewService(&svcdat,ptc, &service,IsDuplicatesvc,currentServiceListIndex);
			IsServiceAdded = TRUE;
			retval = TRUE;
		}
		
	}
	else
	{
	
		/*if service type is not valid then delete the service from database, also
		**delete it's preset table entry
		*/
		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat))
		{
			mDeleteService(&tempsvcdat);
		}																			
	}
	if(IsDuplicatesvc )
	{
		/*Delete the duplicate service with old TPID,svcid*/
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
		tempsvcdat.Tpid = OldTsData->Tpid;
		tempsvcdat.ServiceId = mSvcListData.mSvcListInfo[currentServiceListIndex].ServiceId;;
		if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat))
		{
			mDeleteService(&tempsvcdat);
		}
	}
	return retval;
}

void CHsvDvbsTricolor_mAcq_Priv::mDeleteService(HsvPgdatDigServiceData *psvcdat)
{
	
	int LoopIndex = 0;
	int NumSrvDeleted = 0;
	HsvPgdatPresetData presetData;

	for(LoopIndex =0; LoopIndex < MAX_NUM_LCN_ENTRY; LoopIndex++)
	{
		presetData.PresetNumber = psvcdat->MultiplePreset[LoopIndex];

		if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
		{
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
			NumSrvDeleted++;
		}
	}
	
	if (IsDigitalTvChannel (psvcdat))
	{
		removeCurTv += NumSrvDeleted;
	}
	else if (IsDigitalRadioService (psvcdat))
	{
		removeCurRadio += NumSrvDeleted;
	}
	
	pgdb_Delete(SERVICE_TABLE, (Address)psvcdat);
	TraceNotice (m, "Deleted service Ser-id[%d] Tsid[%d] Onid[%d]",
				psvcdat->ServiceId,
				psvcdat->Tsid,
				psvcdat->OriginalNetworkId);
}

void CHsvDvbsTricolor_mAcq_Priv::mDeleteServicesFromDeletedMuxes(void)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

    while(NoOfTSTables > 0)
	{
	    NoOfTSTables --;
		pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
		if((pgdb_GetByIndex(PTC_TABLE, NoOfTSTables, (Address)&tmptsdata) == TRUE))
		{	
			if(FALSE == mIsTSPresentInSDSDList(&tmptsdata))
			{
				mDeleteAllServicesFromCarrier(tmptsdata.Tpid);
				TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization);
				pgdb_Delete(PTC_TABLE, (Address) &tmptsdata);
			}
		}
        else
        {
             TraceNotice(m,"Get PTC table failed Index %d SDSD Frequency %d",NoOfTSTables,tmptsdata.SDSDFrequency);
		}
	}

}

void CHsvDvbsTricolor_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	int							From = 0, To = 0, count = 0;

	TempSvcData.Tpid 		 = ptc->TPID;
	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal)
	{
		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData);
			if ((RetVal) && ((mIsSvcPresentInServiceList(&TempSvcData) == FALSE) || (mIsSvcPresentinSDTActual(&TempSvcData) == FALSE)))
			{
				mDeleteService(&TempSvcData);
			}
		}
	}
}

Bool CHsvDvbsTricolor_mAcq_Priv::mIsSvcPresentInServiceList(HsvPgdatDigServiceData *svcdata)
{
	Bool RetVal = FALSE;
	int index = 0;

	for(index = 0; index < mSvcListData.NumOfRecords ;index++)
	{
		if(svcdata->ServiceId == mSvcListData.mSvcListInfo[index].ServiceId)
		{
			RetVal = TRUE;
			break;
		}
	}

	if(index == mSvcListData.NumOfRecords)
	{
		TraceNotice(m,"%s %d Service not present in BAT LCNV2 List, hence deleting in Update Installation",__FUNCTION__,svcdata->ServiceId);
	}
	return RetVal;
	
}

Bool CHsvDvbsTricolor_mAcq_Priv::mIsSvcPresentinSDTActual(HsvPgdatDigServiceData *svcdata)
{
	Bool RetVal = FALSE;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;

	if(strapi_GetByKey(HsvMain, HSVSPID(ActualTSService, dvb, sdt), svcdata->OriginalNetworkId, svcdata->ServiceId, svcdata->Tsid, (void *)(&service)) == TRUE)
	{
		RetVal = TRUE;
	}
	else
	{
		TraceNotice(m,"%s %d Service not present in SDT Actual List, hence deleting in Update Installation",__FUNCTION__,svcdata->ServiceId);
	}
	return RetVal;	
}
Bool CHsvDvbsTricolor_mAcq_Priv::mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata)
{
	Bool RetVal = FALSE;
	int i;

	for (i = 0; i < mTricolorDSDesc.NumOfSDSD; i++)
	{
		if((tmptsdata->OriginalNetworkId == mTricolorDSDesc.SatDesc[i].Original_NetworkId) && (tmptsdata->Tsid == mTricolorDSDesc.SatDesc[i].Tsid))
		{
			RetVal = TRUE;
			break;
		}
	}

	return RetVal;
}

void CHsvDvbsTricolor_mAcq_Priv::mDeleteAllServicesFromCarrier(int Tpid)
{	
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	int							From = 0, To = 0, count = 0;

	TempSvcData.Tpid 		 = Tpid;

	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{

		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData);
			if ( RetVal == TRUE)
			{
				mDeleteService(&TempSvcData);
			}
		}
	}	
}

void CHsvDvbsTricolor_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service,int currentServiceListIndex)
{
	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
	mAssignLCN(psvcdat,currentServiceListIndex);
	mAssignSvcNonBroadcastAttributes(psvcdat);

	pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
		
	TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbsTricolor_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;
	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
	}
}

void CHsvDvbsTricolor_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool IsDuplicatesvc,int currentServiceListIndex)
{
	HsvPgdatPresetData	PresetData;	
	int LoopIndex = 0;

	mAssignLCN(psvcdat,currentServiceListIndex);
	/* Filling details of service, then adding it */	
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
	mUpdateSatelliteName (psvcdat);
	/*User attributes should be retained for duplicate service*/
	if(IsDuplicatesvc == FALSE)
	{
		mAssignSvcNonBroadcastAttributes(psvcdat);
	}

	/* Add to service table */
	
	/* Add only if its TV or Radio Service */
	if(mOperatorTricolorInstallRules(psvcdat))
	{
		pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
		TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d SystemHidden = %d\n",psvcdat->MultipleLCN[0], psvcdat->OriginalNetworkId, psvcdat->ServiceId,psvcdat->SystemHidden);
	}
		
	
	/*If it is duplicate service Update the Preset table with new parameters*/
	if(IsDuplicatesvc )
	{
		for(LoopIndex = 0; LoopIndex < MAX_NUM_LCN_ENTRY; LoopIndex++)
		{
			PresetData.PresetNumber = psvcdat->MultiplePreset[LoopIndex];
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
}

Bool CHsvDvbsTricolor_mAcq_Priv::mOperatorTricolorInstallRules(HsvPgdatDigServiceData *psvcdat)
{
    Bool retval = FALSE;
	int LoopCount = 0;

	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		if(psvcdat->MultipleLCN[LoopCount] != INVALID_LCN)
		{
			retval = TRUE;
			break;
		}
	}

	if(!retval)
	{
		TraceNotice(m,"service id %d is not valid : No LCN assigned",psvcdat->ServiceId);
	}
	
    return retval;
}

Bool CHsvDvbsTricolor_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}

void CHsvDvbsTricolor_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
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
	
	

}

void CHsvDvbsTricolor_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
	int mode, state;
	int LoopIndex = 0;
	Bool Proceed = FALSE;
	HsvPgdatPresetData			presetData;
	HsvPgdatDigServiceData		svcdat;

	rins_GetCurrentInstallationState(&mode, &state);

	psvcdat->UserHidden             = FALSE;
	psvcdat->ChannelLock		    = FALSE;
	psvcdat->Favorite			    = FALSE;

	psvcdat->DateStamp			    = 0;
	psvcdat->PresetNumber		    = INVALID_PRESET;
	psvcdat->NewPreset				= (mode == AUTO_MODE)? FALSE : TRUE;
	psvcdat->HbbTvOption 		= 1;

	psvcdat->ServiceListVersion		= mSvcListData.VersionNumber;
	psvcdat->PackageGroup 		= TRICOLOR_MATCH_SETTINGS_DB_PACKAGE_ID;
					

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	
	if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
	{
		psvcdat->NewPreset				= svcdat.NewPreset;

		psvcdat->ChannelLock			= svcdat.ChannelLock;;
		psvcdat->UserHidden				= svcdat.UserHidden;
		psvcdat->Favorite				= svcdat.Favorite;
		psvcdat->HbbTvOption			= svcdat.HbbTvOption;

		psvcdat->DeltaVolume			= svcdat.DeltaVolume;
		psvcdat->UserModifiedName				= svcdat.UserModifiedName;
		psvcdat->FavoriteNumber			= svcdat.FavoriteNumber;

		psvcdat->LogoURL				= svcdat.LogoURL;
		psvcdat->PresetNumber		  = svcdat.PresetNumber;
		psvcdat->PackageGroup		  =  svcdat.PackageGroup;

		
		if (mCompareUnicodeString(psvcdat->ChannelName, svcdat.ChannelName) == FALSE)
		{
			TraceNotice(m, "Service name updated");
			psvcdat->LogoURL = 0;
		}
		else
		{
			TraceNotice(m, "Service name is same");
		}

		/*delete the  preset table if LCN is invalid and service types are different, because non honored service
		**numbering range for radio and TV is different.
		**otherwise is LCN is in valid range but LCNs are different then delete the preset table
		*/

		
		for(LoopIndex = 0; LoopIndex < MAX_NUM_LCN_ENTRY; LoopIndex++)
		{
			if(INVALID_LCN != svcdat.MultipleLCN[LoopIndex])
			{
				Proceed = (!VALID_LCN_RANGE(svcdat.MultipleLCN[LoopIndex]))&&(IS_RADIO_SERVICE(psvcdat->ServiceType) != IS_RADIO_SERVICE(svcdat.ServiceType));
				REVALIDATE(svcdat.MultipleLCN[LoopIndex]);
				Proceed |= ((VALID_LCN_RANGE(psvcdat->MultipleLCN[LoopIndex]) || VALID_LCN_RANGE(svcdat.MultipleLCN[LoopIndex])) && (psvcdat->MultipleLCN[LoopIndex] != svcdat.MultipleLCN[LoopIndex]));
				 if(Proceed)
				 {
					TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->MultipleLCN[LoopIndex], svcdat.MultipleLCN[LoopIndex], svcdat.MultiplePreset[LoopIndex]);
					presetData.PresetNumber =   svcdat.MultiplePreset[LoopIndex];
					pgdb_Delete(PRESET_TABLE, (Address)&presetData);
					psvcdat->MultiplePreset[LoopIndex] = INVALID_PRESET;
				 }
			}
		}
        memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
	}

	if( Timerclk_IsClockDefined())
    {
        psvcdat->DateStamp = Timerclk_GetUniversalTime();
    }
}


int CHsvDvbsTricolor_mAcq_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
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

int CHsvDvbsTricolor_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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

Bool CHsvDvbsTricolor_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	switch (psvcdat->ServiceType)
	{
		case	AppApiTelevisionService:
		case	AppApiTeletextService:
		case	AppApiMPEG2HDService:
		case	AppApiAdvCodecHDTelevisionService:
		case	AppApiAdvCodecSDTelevisionService:
		case 	AppApiHevcService:
			RetVal = TRUE;
			break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsTricolor_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsTricolor_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}


Bool CHsvDvbsTricolor_mAcq_Priv::mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
	/* check service type*/
	Bool lRetVal = FALSE;
	//TraceNotice(m,"service->ServiceType %d ",service->ServiceType);
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

Bool CHsvDvbsTricolor_mAcq_Priv::mCheckFederalChannelListNamePresent(void)
{
	Bool retVal = FALSE;

	HSVSPTYPE(batMulLCNV2,dvb,bat) batservice;
	int i = 0,j = 0, numOfEntries = 0;

	numOfEntries = strapi_GetSize(HsvMain,HSVSPID(batMulLCNV2,dvb,bat));
	
	for(i = 0 ; i < numOfEntries; i++)
	{
		if(strapi_GetByIndex(HsvMain,HSVSPID(batMulLCNV2,dvb,bat), i, (void*)(&batservice)))
		{
			if(batservice.IsFederalService  == TRUE)
			{
				retVal = TRUE;
				break;
			}
		}
		else
		{
			TraceNotice (m," mCheckFederalChannelListNamePresent failed for index: %d \n",i);
		}
	}
	TraceNotice(m,"%s retVal %d",__FUNCTION__,retVal);
	return retVal;
}

void CHsvDvbsTricolor_mAcq_Priv::mCollectSdsds (void)
{
	int i =0;

	mTricolorDSDesc.NumOfSDSD = strapi_GetSize (HsvMain,HSVSPID(SatelliteDS, dvb, nit));
	TraceNotice (m," mTricolorDSDesc.NumOfSDSD %d \n",mTricolorDSDesc.NumOfSDSD);
	for(i = 0; (i < mTricolorDSDesc.NumOfSDSD) && (i < MAX_SDSD); i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&(mTricolorDSDesc.SatDesc[i]))) == FALSE)
		{
			TraceNotice (m," Collect SDSD failed for SDSD: %d \n",i);
		}
		else
		{
			TraceNotice(m,"mTricolorDSDesc.SatDesc[i] tsid %d",mTricolorDSDesc.SatDesc[i].Tsid);
		}
	}

	TraceNotice (m," mTricolorDSDesc.NumOfSDSD %d \n",mTricolorDSDesc.NumOfSDSD);
}

void CHsvDvbsTricolor_mAcq_Priv::mCollectServicelistData(void)
{
	HSVSPTYPE(batMulLCNV2,dvb,bat) batservice;
	int i = 0,j = 0, numOfEntries = 0;
	
	numOfEntries = strapi_GetSize(HsvMain,HSVSPID(batMulLCNV2,dvb,bat));
	mSvcListData.NumOfRecords = 0;

	TraceNotice(m,"debug: numOfEntries %d",numOfEntries);
	for(i = 0 ; i < numOfEntries; i++)
	{
		if(strapi_GetByIndex(HsvMain,HSVSPID(batMulLCNV2,dvb,bat), i, (void*)(&batservice)))
		{
			mSvcListData.mSvcListInfo[i].ServiceId   = batservice.ServiceId;
			for(j =0;j< MAX_NUM_LCN_ENTRY;j++)
			{
				mSvcListData.mSvcListInfo[i].LCN[j] 					    = batservice.LogicalChannelNum[j];
				mSvcListData.mSvcListInfo[i].MultipleVisibleServiceFlag[j]  = batservice.MultipleVisibleServiceFlag[j];
			}
			mSvcListData.NumOfRecords++;
			mSvcListData.VersionNumber = batservice.VersionNumber;
		}
		else
		{
			TraceNotice (m," Collect service list failed for index: %d \n",i);
		}
	}
}

void CHsvDvbsTricolor_mAcq_Priv::mGetSatelliteLnbNo(int SatId)
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
			TraceNotice(m,"debug:DataAcqInstance.LnbNumber %d",DataAcqInstance.LnbNumber);
			break;
		}
	}
}

void CHsvDvbsTricolor_mAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat,int currentServiceListIndex)
{
	int LoopCount = 0, from = 0, to = 0, index = 0, i = 0, j = 0;
	int  newLCN[MAX_NUM_LCN_ENTRY];
	Nat8 newVisiblity[MAX_NUM_LCN_ENTRY];
	
	Bool Found = FALSE, channelExists = FALSE;
	HsvPgdatDigServiceData 		tempsvcdat;
	
	tempsvcdat.Tpid  		= psvcdat->Tpid;
	tempsvcdat.ServiceId	= psvcdat->ServiceId;
	
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount++)
	{
		newLCN[LoopCount] 		= INVALID_LCN;
		newVisiblity[LoopCount] = 1;
	}
	
	channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);

	//Take Old LCNs, this is to retain the position of previous LCNs in MultipleLCN[] if service is already present
	if(channelExists)
	{
		for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
		{
			psvcdat->MultipleLCN[LoopCount] 			= tempsvcdat.MultipleLCN[LoopCount];
			psvcdat->MultipleVisibleService[LoopCount]	= tempsvcdat.MultipleVisibleService[LoopCount];
			psvcdat->MultipleNumericSelect[LoopCount]	= tempsvcdat.MultipleNumericSelect[LoopCount];
			if(psvcdat->MultipleLCN[LoopCount] != INVALID_LCN)
			{
				REVALIDATE(psvcdat->MultipleLCN[LoopCount]);
			}
		}
			
	}
	else
	{
		TraceDebug(m,"Channel does not exists");
	}


	/* Get New LCNs */
	TraceNotice(m,"currentServiceListIndex [%d]",currentServiceListIndex);
	
	for(index = 0;index < MAX_NUM_LCN_ENTRY;index++)
	{

		newLCN[index] = mSvcListData.mSvcListInfo[currentServiceListIndex].LCN[index];
		newVisiblity[index] = mSvcListData.mSvcListInfo[currentServiceListIndex].MultipleVisibleServiceFlag[index];
		
	}

	/* Remove LCNs which does not exist anymore*/
	for(i = 0; i < MAX_NUM_LCN_ENTRY; i++)
	{
		if(psvcdat->MultipleLCN[i] != INVALID_LCN)
		{
			Found = FALSE;
			for(j = 0; j < MAX_NUM_LCN_ENTRY; j++)
			{
				if(psvcdat->MultipleLCN[i] == newLCN[j])
				{
					Found  = TRUE;
					break;
				}
				
			}
			if(!Found)
			{
				TraceNotice(m,"LCN: %d removed for service: ONID[%d] TSID[%d] SVCID[%d]",psvcdat->MultipleLCN[i],DataAcqInstance.Onid, DataAcqInstance.Tsid, psvcdat->ServiceId);
				psvcdat->MultipleLCN[i] = INVALID_LCN;
				//psvcdat->MultipleVisibleService[i] = 0;
				
				/* Check service is TV or Radio */
				if (IsDigitalTvChannel (psvcdat))
				{
					removeCurTv++;
				}
				else if (IsDigitalRadioService (psvcdat))
				{
					removeCurRadio++;
				}

			}
		}
		
	}
	
	/* Add New LCNs */
	for(i = 0; i < MAX_NUM_LCN_ENTRY; i++)
	{
		if(newLCN[i] != INVALID_LCN)
		{
			Found  = FALSE;
			for(j = 0; j < MAX_NUM_LCN_ENTRY; j++)
			{
				if(psvcdat->MultipleLCN[j] == newLCN[i])
				{
					Found  = TRUE;
					break;
				}
				
			}
			
			if(!Found)
			{
				for(j = 0; j < MAX_NUM_LCN_ENTRY; j++)
				{
					if(psvcdat->MultipleLCN[j] == INVALID_LCN)
					{
						psvcdat->MultipleLCN[j] = newLCN[i];
						psvcdat->MultipleVisibleService[j] = newVisiblity[i];
						psvcdat->MultipleNumericSelect[j] = newVisiblity[i];
						TraceNotice(m,"LCN: %d visibility %d Added for service: ONID[%d] TSID[%d] SVCID[%d]",psvcdat->MultipleLCN[j],psvcdat->MultipleVisibleService[j],DataAcqInstance.Onid, DataAcqInstance.Tsid, psvcdat->ServiceId);
						break;
					}
				}
				if(j == MAX_NUM_LCN_ENTRY)
				{
					TraceErr(m,"ERROR: LCNs overflow");
				}
				
				/* Check service is TV or Radio */
				if(IsDigitalTvChannel(psvcdat))
				{
					mDigitalTvChannelsFound++;
				}
				else if(IsDigitalRadioService(psvcdat))
				{
					mDigitalRadioChannelsFound++;
				}
			}
		}
	}

	mDigitalChannelsFound = (mDigitalTvChannelsFound + mDigitalRadioChannelsFound)-(removeCurTv + removeCurRadio );
	TraceNotice (m, "Totaldigfound[%d] TvAdd[%d] RadioAdd[%d] TvRm[%d] RadioRm[%d]",
							mDigitalChannelsFound, mDigitalTvChannelsFound, mDigitalRadioChannelsFound,
							removeCurTv,removeCurRadio );

}

Bool CHsvDvbsTricolor_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}



/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsTricolor_mAcq_Priv::iacqpow_Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbtricolor_mDataAcq" );
	
	TraceNotice (m, " Tricolor Acq Module pow Initialized \n");

}

void CHsvDvbsTricolor_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsTricolor_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsTricolor_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
    /* Resetting all the variables */
    mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
    removeCurTv = removeCurRadio = 0;
	memset(&mSvcListData,0,sizeof(mSvcListData));
	
	UNUSED(LnbNumber);
}

void CHsvDvbsTricolor_mAcq_Priv::idataacq_AcquireData(int Mode)
{

	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)Mode);
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

void CHsvDvbsTricolor_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	//TraceNotice(m, "%s LCN %d VisFlag %d <%d %d %d>", __FUNCTION__, psvcdat->LCN, psvcdat->VisibleService, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
	TraceNotice(m,"No Call should be reached here\n",__FUNCTION__);
	
}
int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);
	
	return removeCurTv;
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);
	
	return removeCurRadio;
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return mTricolorDSDesc.NumOfSDSD;
}

Bool CHsvDvbsTricolor_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mTricolorDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry, &mTricolorDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));
		mTricolorDSDesc.CurrentSDSDIndex = count;
		TraceNotice(m,"mTricolorDSDesc.CurrentSDSDIndex %d",mTricolorDSDesc.CurrentSDSDIndex);
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);
	
	return RadioChannelsFound;
}

void CHsvDvbsTricolor_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{
	TraceNotice (m,"%s %d>GetTricolorRegionNames", __FUNCTION__, __LINE__);
	int listLen = strapi_GetSize (HsvMain, HSVSPID(TricolorLRN, dvb, bat));
	int i = 0, nameLen = 0;
	Nat16 name[24];
	

	*len = listLen;
	
	TraceNotice (m, "List length retrieved is [%d] names %p len %p", listLen, names,len);
	if (listLen >0)
	{
		while(i < listLen)
		{
			nameLen = strapi_GetByIndex(HsvMain, HSVSPID(TricolorLRN, dvb, bat),i,name);
			TraceNotice (m, "Region Name is [%s] ",name);

			if (nameLen)
			{
				TraceNotice(m, " New Ptr %p", names+i);
				*(names+i)  = (Nat16*)malloc(nameLen*sizeof(Nat16));
				memcpy(*(names+i), name, nameLen*sizeof(Nat16));
			}
			
			TraceNotice (m, "Region Name is [%s] names increased", *names);
			i++;
		}
	}
	return;
}

void CHsvDvbsTricolor_mAcq_Priv::idataacq_AcquireDataOnTimeout(void)
{

}

int CHsvDvbsTricolor_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{
	return 0;
}

void CHsvDvbsTricolor_mAcq_Priv::idataacq_SyncTemporaryTableRecords			(	void	)
{

}

