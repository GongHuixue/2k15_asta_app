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
 *          %name: hsvdvbsfransat_mAcq.c %
 *       %version: TVG_3 %
 * %date_modified: %
 *    %derived_by: smirajkar %
 */

/* include dependencies */
#include	"_hsvdvbsfransat_mAcq.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsfransat/fransat_macq")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

/* Macros */
















/* Local Structures and enums */













/****************************************************************************
 * Static variables
 ****************************************************************************/

FransatSatDSDesc CHsvDvbsFransat_mAcq_Priv::s__mFransatDSDesc;

FransatServiceList CHsvDvbsFransat_mAcq_Priv::s__mSvcListData;


int CHsvDvbsFransat_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsFransat_mAcq_Priv::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsFransat_mAcq_Priv::s__mDigitalRadioChannelsFound = 0;

Pump CHsvDvbsFransat_mAcq_Priv::s__mDataAcqPump;


int CHsvDvbsFransat_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsFransat_mAcq_Priv::s__removeCurRadio =0;

HsvDataAcqInstance CHsvDvbsFransat_mAcq_Priv::s__DataAcqInstance;


HsvInstallationPTC CHsvDvbsFransat_mAcq_Priv::s__CurrentPTC;

Nat16 CHsvDvbsFransat_mAcq_Priv::s__mUnicodeBuffer[11];


double CHsvDvbsFransat_mAcq_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};


/****************************************************************************
 * Static functions
 ****************************************************************************/


/* Static functions */






































#if 0


#endif




void CHsvDvbsFransat_mAcq_Priv::mPumpHandler(int value, Nat32 param)
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
		TraceNotice (m, "Num of Channels %d, Added TV %d Radio %d. Removed TV %d Radio %d",
						mDigitalChannelsFound, mDigitalTvChannelsFound, mDigitalRadioChannelsFound,
						removeCurTv,removeCurRadio );
		break;
	}

}

void CHsvDvbsFransat_mAcq_Priv::mStartHomingAcquisition(void)
{
    /* SDTOtherStatus is checked in mCollectSdsds function so get it before collectSdsds */
	mGetSDTOtherStatus();
	/*Collect Sdsds from strapi*/
	mCollectSdsds();
	mGetSatelliteLnbNo(EUTELSAT_5_W);
#if 0
	if(mCollectBarkerMuxData() == FALSE)
	{
		TraceNotice(m,"Barker mux data collection failed");
	}
#endif
	if(DataAcqInstance.SDTOtherPresent)
	{
		/*start acquiring TSinfo*/
		mAcquireTSInfo();
	}
	else
	{
		mCollectServicelistData();
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);
	}
}

#if 0

Bool CHsvDvbsFransat_mAcq_Priv::mCollectBarkerMuxData(void)
{
	int NumOfLinkageDesc = 0;
	int LinkDescLoopCount = 0;
	int DSDescLoopCount = 0;
	int index = 0;
	Bool RetVal = FALSE;
	HsvBarkerMuxData BarkerMuxData;
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;

	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));
	if(iutil_ReadBarkerMuxData(&BarkerMuxData) != TRUE)
	{
		memset(&BarkerMuxData, 0, sizeof(HsvBarkerMuxData));
		BarkerMuxData.NoOfRecords = 0;
	}

	for(LinkDescLoopCount = 0; LinkDescLoopCount < NumOfLinkageDesc ; LinkDescLoopCount++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, nit), LinkDescLoopCount, (void*)(&LinkageDesc)) == TRUE)
		{
			if(LinkageDesc.LinkageType == BARKER_MUX_LINKAGE_TYPE)
			{
				/*Get the barker mux data and write into the file*/
				/*check if data has to be appended or written as new*/
				index = BarkerMuxData.NoOfRecords;
				BarkerMuxData.NoOfRecords ++;
				BarkerMuxData.Mux[index].OnId = LinkageDesc.Original_NetworkId;
				BarkerMuxData.Mux[index].TsId = LinkageDesc.Tsid;
				BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = THOR_1W;
				for(DSDescLoopCount = 0; DSDescLoopCount < mFransatDSDesc.NumOfSDSD; DSDescLoopCount++)
				{
					if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), DSDescLoopCount, (void*)(&tmpsdsd)) == TRUE)
					{
						if((tmpsdsd.Original_NetworkId == LinkageDesc.Original_NetworkId) && (tmpsdsd.Tsid == LinkageDesc.Tsid))
						{
							BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.Frequency = tmpsdsd.Frequency;
							BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.tp_id = CREATE_TPID(DataAcqInstance.LnbNumber, tmpsdsd.Frequency, tmpsdsd.Polarization);
							if(iutil_WriteBarkerMuxData(BarkerMuxData) == TRUE)
							{
								RetVal = TRUE;
							}
							break;
						}
					}
				}
			}
		}
		else
		{
			TraceNotice (m," Collect linkage info failed for index: %d \n",LinkDescLoopCount);
		}
	}
	return RetVal;
}
#endif


void CHsvDvbsFransat_mAcq_Priv::mStartFallbackAcquisition(void)
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
			if(mFransatDSDesc.CurrentSDSDIndex == (mFransatDSDesc.NumOfSDSD-1))
			{
				/*Delete services from all deleted muxes in current version of BAT*/
				mDeleteServicesFromDeletedMuxesInCurrentBAT();
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

void CHsvDvbsFransat_mAcq_Priv::mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
{
	int	TransponderFreq = 0;

	ptc->LnbNumber = DataAcqInstance.LnbNumber;
	ptc->Polarization = Sdsd.Polarization;
	ptc->Frequency = Sdsd.Frequency;
	ptc->SDSDFrequency = Sdsd.Frequency;
	ptc->SymbolRate = Sdsd.SymbolRate;
	ptc->ModulationType = Sdsd.ModulationType;
	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);
	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
	ptc->QSignalStrength = 0;
	ptc->SSignalStrength = 0;
	ptc->HierarchyMode = HsvHierarchyNone;
	ptc->StreamPriority = HsvStreamPriorityHigh;
	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);
}

Bool CHsvDvbsFransat_mAcq_Priv::mGetTSMetaData(void)
{
    Bool	retval = FALSE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain,  HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &DataAcqInstance.Tsid);

	TraceNotice (m, "ONID %d and TsId %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);

    return retval;
}


void CHsvDvbsFransat_mAcq_Priv::mAcquireTSInfo(void)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) CurrentSdsd;
	KeyUpdateReason KeyUpdate = NoUpdate;
	HsvPgdatDigTSData OldTsData;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &OldTsData);

	TraceNotice(m, " DataAcqInstance.CurSdsd %d DataAcqInstance.NumSdsds %d sizeof(CurrentSdsd) %d", DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(CurrentSdsd));
	if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
	{
		memcpy(&CurrentSdsd,&mFransatDSDesc.SatDesc[DataAcqInstance.CurSdsd], sizeof(HsvNITSatelliteDS));

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

	if(DataAcqInstance.CurSdsd >= DataAcqInstance.NumSdsds)
	{
		/*Delete services from all deleted muxes, in current version of BAT
              delete the service atleast if one valid service (one valid mux) present in BAT,
              otherwise the retain existing service list
              */
		if((IsUpdateInstall() == TRUE) && (0 < DataAcqInstance.NumSdsds))
		{
			mDeleteServicesFromDeletedMuxesInCurrentBAT();
		}
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);
	}
	else
	{
		pmp_PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	}
}

void CHsvDvbsFransat_mAcq_Priv::mDeleteTSTable(HsvInstallationPTC *ptc)
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

void CHsvDvbsFransat_mAcq_Priv::mDeleteServicesFromDeletedMuxesInCurrentBAT(void)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

        while(NoOfTSTables > 0)
	{
	       NoOfTSTables --;
		pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
		if((pgdb_GetByIndex(PTC_TABLE, NoOfTSTables, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
		{	/*Check if any service belongs to this TS is present BAT eutelsat channel number descriptor*/
			if((FALSE == mIsTSPresentInBATTSList(&tmptsdata)) || (FALSE == mIsTSPresentInSDSDList(&tmptsdata)))
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

Bool CHsvDvbsFransat_mAcq_Priv::mIsTSPresentInBATTSList(HsvPgdatDigTSData *tmptsdata)
{
	Bool RetVal = FALSE;
	int StartCount = 0;
	int EndCount = 0;

	/*incase of Fransat BAT table transmitted across the muxes are same, so in both homing and
	**fallback mode TS considered as availabe if any service belongs to that TS is present in BAT
	*/
	if(strapi_GetRangeByKey(HsvMain, HSVSPID(batECN, dvb, bat), 2,
								tmptsdata->OriginalNetworkId,
								tmptsdata->Tsid, 0, &StartCount, &EndCount))
	{
		RetVal = TRUE;
	}

	return RetVal;
}
Bool CHsvDvbsFransat_mAcq_Priv::mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata)
{
    Bool RetVal = FALSE;
    HSVSPTYPE(SatelliteDS,dvb,nit) SatSDSD;
    if(strapi_GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, nit),
                            tmptsdata->OriginalNetworkId,
                            tmptsdata->Tsid,
                            tmptsdata->NetworkId,
                            &SatSDSD))
    {
    RetVal = TRUE;
    }
    else
    {
        TraceNotice(m,"SDSD entry removed from NIT ONID %d TSID %d NID %d",
                                                    tmptsdata->OriginalNetworkId,
                            tmptsdata->Tsid,
                            tmptsdata->NetworkId);
    }
    return RetVal;
}

/*Keyupdate reason indicates if any key(freq/pol) is updated in SDSD or due to Acq. mode change.
if Acq mode changed in update install, ptc frequnecy may change as tuner will not be locked to
exact SDSD freq, in this case old ferquency is retained. If SDSD freq\pol. is changed
then old TPID entry is deleted and new entry is added with new freq\pol and oldTPID is returned*/
void CHsvDvbsFransat_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, KeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0;
	int TSTableCount = 0;
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
	tsdata.UserInstalled			= IsManualInstall();
	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Polarization				= ptc->Polarization;
	tsdata.Tpid						= ptc->TPID;

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

			for(TSTableCount = 0; TSTableCount < NoOfTSTables; TSTableCount++)
			{
				pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
				/*Check only TS tables installed via pkg install*/
				if((pgdb_GetByIndex(PTC_TABLE, TSTableCount, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
				{
					if((tmptsdata.OriginalNetworkId == tsdata.OriginalNetworkId) && (tmptsdata.Tsid == tsdata.Tsid))
					{
						/*Return old Keys and TS table*/
						OldTsData->LnbNumber = tmptsdata.LnbNumber;
						OldTsData->Frequency = tmptsdata.Frequency;
						OldTsData->Polarization = tmptsdata.Polarization;
						/*read the current data from database using key*/
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

			/*No TSIt is a New TS, Add to TS table*/
			if(TSTableCount == NoOfTSTables)
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

Bool CHsvDvbsFransat_mAcq_Priv::mInstallHomingMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	HSVSPTYPE(batECN, dvb, bat) BatECNList;
	SvcListInfo	SeviceListInfo;
	int LoopCount = 0;
	int StartCount = 0;
	int EndCount = 0;
	int InstalledServices = 0;

	if(strapi_GetRangeByKey(HsvMain, HSVSPID(batECN, dvb, bat), 2, DataAcqInstance.Onid, DataAcqInstance.Tsid, 0, &StartCount, &EndCount) == TRUE)
	{
		TraceDebug(m, " %s %d NoOfServices in MUX = %d ONID = 0x%x TSID = 0x%x \n",__FUNCTION__, __LINE__, ((EndCount - StartCount)+1),DataAcqInstance.Onid, DataAcqInstance.Tsid);

		/* From strapi get all the services and add/update in SERVICE_TABLE */
		for(LoopCount = EndCount; LoopCount >= StartCount ; LoopCount--)
		{
			if(strapi_GetByIndex(HsvMain,  HSVSPID(batECN, dvb, bat), LoopCount, (void *)(&BatECNList)) == TRUE)
			{
				SeviceListInfo.Onid        = BatECNList.Onid;
				SeviceListInfo.Tsid        = BatECNList.Tsid;
				SeviceListInfo.ServiceId   = BatECNList.ServiceId;
				mSvcListData.VersionNumber  = BatECNList.VersionNumber; /*Gyanendra*/
				
				TraceDebug(m, "ONID 0x%x TSID 0x%x Srv ID 0x%x Key update %d",SeviceListInfo.Onid, SeviceListInfo.Tsid, SeviceListInfo.ServiceId, KeyUpdate);
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
		TraceNotice(m, "No services found in service list of ONID = 0x%x TSID = 0x%x \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);
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

Bool CHsvDvbsFransat_mAcq_Priv::mInstallFallbackMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	int LoopCount = 0;
	int InstalledServices = 0;

	for(LoopCount = 0; LoopCount <= mSvcListData.NumOfRecords ; LoopCount++)
	{
		if((mSvcListData.mSvcListInfo[LoopCount].Onid == DataAcqInstance.Onid) && (mSvcListData.mSvcListInfo[LoopCount].Tsid == DataAcqInstance.Tsid))
		{
			if(mCheckServiceForInstall(&ptc, KeyUpdate, OldTsData,&mSvcListData.mSvcListInfo[LoopCount]))
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
void CHsvDvbsFransat_mAcq_Priv::mStoreZeroMultipleLCN(HsvPgdatDigServiceData *svcdat)
{
	int LoopCount = 0;
	
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		if(svcdat->MultipleLCN[LoopCount] == 0) {
			svcdat->MultipleLCN[LoopCount] = ZERO_VALUE_LCN;
		}
		TraceNotice(m,"[%s] [%d] MultipleLCN[%d] \n",__FUNCTION__,__LINE__,svcdat->MultipleLCN[LoopCount]);
	}
}
void CHsvDvbsFransat_mAcq_Priv::mRetriveZeroMultipleLCN(HsvPgdatDigServiceData *svcdat)
{
	int LoopCount = 0;
	
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		if(svcdat->MultipleLCN[LoopCount] == ZERO_VALUE_LCN) {
			svcdat->MultipleLCN[LoopCount] = 0;
		}
		TraceNotice(m,"[%s] [%d] MultipleLCN[%d] \n",__FUNCTION__,__LINE__,svcdat->MultipleLCN[LoopCount]);
	}
}


Bool CHsvDvbsFransat_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC *ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData, SvcListInfo *ServiceList)
{
	Bool retval = FALSE;
	Bool channelExists = FALSE;
	Bool IsDuplicatesvc = FALSE;
	Bool IsServiceAdded = FALSE;
	Bool ToAdd = TRUE;
	int LoopCount = 0;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvPgdatDigServiceData 		svcdat, tempsvcdat;

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
		svcdat.ServiceId = ServiceList->ServiceId;

		if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat) == TRUE)
		{
			IsDuplicatesvc = TRUE;
		}
	}
	else
	{
		if(KeyUpdate == AcqModeChange)
		{
			ptc->Frequency = OldTsData->Frequency;
			ptc->TPID = OldTsData->Tpid;
		}
		svcdat.Tpid = ptc->TPID;
		svcdat.ServiceId = ServiceList->ServiceId;
		pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat);
	}

	svcdat.Frequency		  	= ptc->Frequency;
	svcdat.OriginalNetworkId 	= DataAcqInstance.Onid;
	svcdat.Tsid 			  	= DataAcqInstance.Tsid;
	svcdat.LnbNumber 		 	= ptc->LnbNumber;
	svcdat.Polarization 			= ptc->Polarization;
	svcdat.Tpid	       	  	= ptc->TPID;
	svcdat.ServiceId			= ServiceList->ServiceId;
	/*For fransat service visibility is always TRUE (visible)*/
	svcdat.VisibleService 	= TRUE;
	svcdat.NetworkId			= DataAcqInstance.NetworkId;
	svcdat.SDSDFrequency		= ptc->SDSDFrequency;

	/*For Fransat if service persent is BAT but it is not availabe in SDT actual/other then add
	**the services with service name should be empty and service type should be TV
	*/
	memset(&service, 0, sizeof(HSVSPTYPE(ActualTSService, dvb, sdt)));
	service.ServiceType = TelevisionService;
	/*copying is done to keep the existing name, if the service is removed from SDT*/
	mCopyString(service.ServiceName,  svcdat.ChannelName, (eurdiv_PresetNameLength - 1));

	if(strapi_GetByKey(HsvMain, HSVSPID(ActualTSService, dvb, sdt), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == FALSE)
	{
		/*If Get Entry from SDT Actual fails check in SDT other*/
		if((DataAcqInstance.Mode == Homing) &&
			(strapi_GetByKey(HsvMain, HSVSPID(OtherSDTSection, dvb, sdt), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == TRUE))
		{
			TraceDebug(m,"SDT OTHER avilable for svcid: %d, svctype: %d",service.ServiceId,service.ServiceType);
			if(mIsServiceInstallable(&service) == FALSE)
			{
				ToAdd = FALSE;
				TraceNotice(m,"service is not installable onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
			}
		}
		else
		{
			/*SDT Actual/Other not available so fill default servicename*/
			mCopyString(service.ServiceName, mAsciiToUnicode("-----", 5), 5);
		}
	}
	else
	{
		TraceDebug(m,"SDT ACTUAL avilable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
		if(mIsServiceInstallable(&service) == FALSE)
		{
			ToAdd = FALSE;
			TraceNotice(m,"service is not installable onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
		}
	}

	if(ToAdd == TRUE)
	{
		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;
		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address )&tempsvcdat);
		TraceDebug (m, "TPID 0x%x Srv ID 0x%x Channel Exist %d",tempsvcdat.Tpid, tempsvcdat.ServiceId, channelExists);
		//mAssignLCN(&svcdat, channelExists);

		if(channelExists)
		{
	        TraceDebug (m, " Channel exists SvcId 0x%x and SvcType %d \n", svcdat.ServiceId, svcdat.ServiceType);
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
		/*if service type is not valid then delete the service from database, also
		**delete it's preset table entry
		*/
		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat))
		{
			mDeleteService(&tempsvcdat, FALSE);
		}
	}


	if(IsDuplicatesvc )
	{
		/*Delete the duplicate service with old TPID,svcid*/
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
		tempsvcdat.Tpid = OldTsData->Tpid;
		tempsvcdat.ServiceId = ServiceList->ServiceId;
		if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat))
		{
			mDeleteService(&tempsvcdat, TRUE);
		}
	}
	return retval;
}

void CHsvDvbsFransat_mAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat, Bool channelExists)
{
	int NumValidLCNOld = 0;
	int NumValidLCNNew = 0;
	int LoopCount = 0;
	HSVSPTYPE(batECN,dvb,bat) batservice;

	if(strapi_GetByKey(HsvMain, HSVSPID(batECN, dvb, bat), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, (void*)(&batservice)))
	{
		for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount++)
		{
			if(INVALID_LCN != batservice.EutelsatChannelNum[LoopCount])
			{
				NumValidLCNNew++;
			}
			if(INVALID_LCN != psvcdat->MultipleLCN[LoopCount])
			{
				NumValidLCNOld++;
			}
			TraceDebug(m,"LCN old %d, LCN new %d",psvcdat->MultipleLCN[LoopCount], batservice.EutelsatChannelNum[LoopCount]);
			psvcdat->MultipleLCN[LoopCount] = batservice.EutelsatChannelNum[LoopCount];
		}

		TraceDebug(m,"Valid New LCN %d Valid Old LCN %d",NumValidLCNNew, NumValidLCNOld);

		if(NumValidLCNNew >= NumValidLCNOld)
		{
			/* Check service is TV or Radio */
			if (IsDigitalTvChannel (psvcdat))
			{
				/*if the channel already exist, then add only the new LCN entries*/
				mDigitalTvChannelsFound += ((channelExists) ? (NumValidLCNNew - NumValidLCNOld) : NumValidLCNNew);
			}
			else if (IsDigitalRadioService (psvcdat))
			{
				mDigitalRadioChannelsFound += ((channelExists) ? (NumValidLCNNew - NumValidLCNOld) : NumValidLCNNew);
			}

   			 mDigitalChannelsFound += NumValidLCNNew;
		}
		else
		{
			/* Check service is TV or Radio */
			if (IsDigitalTvChannel (psvcdat))
			{
				removeCurTv += (NumValidLCNOld - NumValidLCNNew);
			}
			else if (IsDigitalRadioService (psvcdat))
			{
				removeCurRadio +=  (NumValidLCNOld - NumValidLCNNew);
			}

			 mDigitalChannelsFound += NumValidLCNNew;
		}
	}
	else
	{
		TraceNotice(m,"Get BAT ECN failed, ONID 0x%x TSID 0x%x SID 0x%x",  psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
	}
}

void CHsvDvbsFransat_mAcq_Priv::mDeleteService(HsvPgdatDigServiceData *psvcdat, Bool Is_DuplicateService)
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

	/*if the service is a duplicate service, then removed service count will be increased while assigning LCN itself*/
	if(!Is_DuplicateService){
		if (IsDigitalTvChannel (psvcdat))
		{
			removeCurTv += NumSrvDeleted;
		}
		else if (IsDigitalRadioService (psvcdat))
		{
			removeCurRadio += NumSrvDeleted;
		}
	}

	pgdb_Delete(SERVICE_TABLE, (Address)psvcdat);
	TraceNotice (m, "Deleted service Ser-id[%d] Tsid[%d] Onid[%d]",
				psvcdat->ServiceId,
				psvcdat->Tsid,
				psvcdat->OriginalNetworkId);
}

void CHsvDvbsFransat_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
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
			if ((RetVal) && (mIsSvcPresentInServiceList(&TempSvcData) == FALSE) &&
							 (0 != TempSvcData.SDSDFrequency)) /* Dont delete services installed by generic module*/
			{
				mDeleteService(&TempSvcData, FALSE);
			}
		}
	}
}

Bool CHsvDvbsFransat_mAcq_Priv::mIsSvcPresentInServiceList(HsvPgdatDigServiceData *svcdata)
{
	Bool RetVal = FALSE;
	HSVSPTYPE(batECN,dvb,bat) batservice;

	if(strapi_GetByKey(HsvMain,  HSVSPID(batECN, dvb, bat), svcdata->OriginalNetworkId, svcdata->Tsid, svcdata->ServiceId, (void *)(&batservice)) == TRUE)
	{
		/*In case of Fransat same service can present in multiple LCN, so LCN is added as additional check to
		**identify the specify instance of a service
		*/
		RetVal = TRUE;
	}
	else
	{
		TraceNotice (m,"ECN get by Key failed");
	}

	return RetVal;
}

void CHsvDvbsFransat_mAcq_Priv::mDeleteAllServicesFromCarrier(int TPID)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
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
				mDeleteService(&TempSvcData, FALSE);
			}
		}
	}
}

void CHsvDvbsFransat_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
	mAssignLCN(psvcdat, TRUE);

	mAssignSvcNonBroadcastAttributes(psvcdat);
    	mUpdateSatelliteName (psvcdat);

	pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
	TraceDebug(m,"Updated Service ONID:%d SVCID:%d\n", psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbsFransat_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
        HsvPgdatDigSatInfoData  SatInfo;

        SatInfo.LnbNumber = psvcdat->LnbNumber;

        if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
        {
                memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
        }
}
void CHsvDvbsFransat_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool IsDuplicatesvc)
{
	HsvPgdatPresetData			PresetData;
	int LoopIndex = 0;

	/* Filling details of service, then adding it */
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
    mUpdateSatelliteName (psvcdat);

	mAssignLCN(psvcdat, FALSE);
	/*User attributes should be retained for duplicate service*/
	if(IsDuplicatesvc == FALSE)
	{
		mAssignSvcNonBroadcastAttributes(psvcdat);
	}

    /*if service entry is present only in BAT, but not availabe in SDT actual/other then service type will be empty
    **in that case also we have add service
    */
	/* Add to service table */
    pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
    TraceDebug(m,"Added Service:Name %s ONID:0x%x SVCID:0x%x SystemHidden = %d LCN 5d\n", psvcdat ->ChannelName, psvcdat->OriginalNetworkId, psvcdat->ServiceId,psvcdat->SystemHidden, psvcdat->MultipleLCN[0]);

	/*If it is duplicate service Update the Preset table with new parameters*/
	if(IsDuplicatesvc)
	{
		for(LoopIndex = 0; LoopIndex < MAX_NUM_PRESET_ENTRY; LoopIndex++){
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

Bool CHsvDvbsFransat_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}

Nat16 * CHsvDvbsFransat_mAcq_Priv::mAsciiToUnicode(char *ascii_str,int length)
{
	int loop = 0;
    while( loop < length )
    {
        mUnicodeBuffer[loop] = ascii_str[loop];
        ++loop;
    }
	return  mUnicodeBuffer;
}


void CHsvDvbsFransat_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	psvcdat->ModulationType        =   ptc->ModulationType;
	psvcdat->Bandwidth	   			=   ptc->ChannelBandwidth;

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


void CHsvDvbsFransat_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
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
	psvcdat->PackageGroup 		= APPAPISAT_Fransat;
					

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
/* ANEESH: Change this to TimerClk
	if( clk_ClockIsSet())
	{
		psvcdat->DateStamp = clk_GetUniversalTime();
	}
	*/
}

int CHsvDvbsFransat_mAcq_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
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

int CHsvDvbsFransat_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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

Bool CHsvDvbsFransat_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	switch (psvcdat->ServiceType)
	{
	case	AppApiTelevisionService:
	case	AppApiTeletextService:
	case	AppApiMPEG2HDService:
	case	AppApiAdvCodecHDTelevisionService:
	case	AppApiAdvCodecSDTelevisionService:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsFransat_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsFransat_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}

Bool CHsvDvbsFransat_mAcq_Priv::mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sdt)* service)
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

void CHsvDvbsFransat_mAcq_Priv::mCollectSdsds (void)
{
	int NumOfSDSD = 0;
	int LoopCount = 0;
	int SDSDLoopCount = 0;
	Bool AddSDSDEntry =  FALSE;
	int StartCount = 0;
	int EndCount = 0;
	HSVSPTYPE(SatelliteDS,dvb,nit) SatSDSD;

	NumOfSDSD = strapi_GetSize (HsvMain,  HSVSPID(SatelliteDS, dvb, nit));
	mFransatDSDesc.NumOfSDSD = 0;

	TraceNotice (m," Number of SDSD %d", NumOfSDSD);

	for(SDSDLoopCount = 0; SDSDLoopCount < NumOfSDSD; SDSDLoopCount ++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), SDSDLoopCount, (void*)&SatSDSD))
		{
			AddSDSDEntry =  TRUE;

			TraceDebug (m,"SDSD Entry ONID 0x%x NID 0x%x TSID 0x%x",  SatSDSD.Original_NetworkId,  SatSDSD.NetworkId, SatSDSD.Tsid);
			for(LoopCount = 0; LoopCount < mFransatDSDesc.NumOfSDSD; LoopCount++)
			{
				/*search the existing entry before adding new entry*/
				if((mFransatDSDesc.SatDesc[LoopCount].Original_NetworkId == SatSDSD.Original_NetworkId) &&
					(mFransatDSDesc.SatDesc[LoopCount].NetworkId == SatSDSD.NetworkId) &&
					(mFransatDSDesc.SatDesc[LoopCount].Tsid == SatSDSD.Tsid)){

					/*Entry already available*/
					AddSDSDEntry = FALSE;
					TraceNotice (m,"SDSD Entry already present ");
					break;
				}
			}

			if(AddSDSDEntry)
			{
				StartCount = 0;
				EndCount = 0;

				/*valid service present in BAT ECN list, so add SDSD*/
				if(strapi_GetRangeByKey(HsvMain, HSVSPID(batECN, dvb, bat), 2,
												SatSDSD.Original_NetworkId,
												SatSDSD.Tsid, 0, &StartCount, &EndCount))
				{
					memcpy(&(mFransatDSDesc.SatDesc[mFransatDSDesc.NumOfSDSD]),&SatSDSD, sizeof(HSVSPTYPE(SatelliteDS,dvb,nit)));
					mFransatDSDesc.NumOfSDSD ++;
					TraceDebug (m,"SDSD Entry Added ONID 0x%x NID 0x%x TSID 0x%x",  SatSDSD.Original_NetworkId,  SatSDSD.NetworkId, SatSDSD.Tsid);
				}
				else{
					TraceNotice (m,"Get range of service from ECN list failed");
				}
			}
		}
	}

	DataAcqInstance.CurSdsd = 0;
	DataAcqInstance.NumSdsds = 	mFransatDSDesc.NumOfSDSD;
	TraceNotice (m," DataAcqInstance.NumSdsds %d \n",DataAcqInstance.NumSdsds);
}

void CHsvDvbsFransat_mAcq_Priv::mCollectServicelistData(void)
{
	HSVSPTYPE(batECN,dvb,bat) batservice;
	int LoopCount = 0;
	int numOfEntries = 0;
	Nat32 PackageId;
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);

	numOfEntries = strapi_GetSize(HsvMain, HSVSPID(batECN, dvb, bat));
	mSvcListData.NumOfRecords = 0;
	for(LoopCount = 0 ;((LoopCount < numOfEntries) && (mSvcListData.NumOfRecords < MAX_SERVICES)); LoopCount++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(batECN, dvb, bat), LoopCount, (void*)(&batservice)))
		{
			mSvcListData.mSvcListInfo[LoopCount].Onid        = batservice.Onid;
			mSvcListData.mSvcListInfo[LoopCount].Tsid        = batservice.Tsid;
			mSvcListData.mSvcListInfo[LoopCount].ServiceId   = batservice.ServiceId;
			mSvcListData.VersionNumber = batservice.VersionNumber;
			TraceNotice (m,"%s mSvcListData.VersionNumber %d \n", __FUNCTION__, mSvcListData.VersionNumber);
			mSvcListData.NumOfRecords++;
		}
	}
}

void CHsvDvbsFransat_mAcq_Priv::mGetSDTOtherStatus(void)
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

void CHsvDvbsFransat_mAcq_Priv::mGetSatelliteLnbNo(int SatId)
{
	int LnbNumber = 0;
	HsvPgdatDigSatInfoData SatDetails;

	for(LnbNumber = 0; LnbNumber < MAX_LNBS_SUPPORTED; LnbNumber++)
	{
		pgdb_Initialise(pgdbconst_SatInfo, (Address) &SatDetails);
		SatDetails.LnbNumber = LnbNumber;

		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails) != TRUE)
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n",LnbNumber);
		}

		if(SatDetails.SatelliteId == SatId)
		{
			DataAcqInstance.LnbNumber = LnbNumber;
			break;
		}
	}
}

Bool CHsvDvbsFransat_mAcq_Priv::IsManualInstall(void)
{
	int mode, state;

	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsFransat_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;

	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate) || (mode == insstate_InstallationBackgroundUpdate))? TRUE: FALSE);
}

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsFransat_mAcq_Priv::iacqpow_Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbPol_mDataAcq" );

	TraceNotice (m, " Pol Acq Module pow Initialized \n");

}

void CHsvDvbsFransat_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsFransat_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */

void CHsvDvbsFransat_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
	/* Resetting all the variables */
	mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
	removeCurTv = removeCurRadio = 0;
	UNUSED(LnbNumber);
}

void CHsvDvbsFransat_mAcq_Priv::idataacq_AcquireData(int Mode)
{
	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)Mode);
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);

	return removeCurTv;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);

	return removeCurRadio;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return mFransatDSDesc.NumOfSDSD;
}

Bool CHsvDvbsFransat_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mFransatDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry,&mFransatDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));

		mFransatDSDesc.CurrentSDSDIndex = count;
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);

	return RadioChannelsFound;
}

void CHsvDvbsFransat_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	// Do nothing
}

void CHsvDvbsFransat_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{
	// Do nothing
}
void CHsvDvbsFransat_mAcq_Priv::idataacq_AcquireDataOnTimeout                        (   void    )
{
}

int CHsvDvbsFransat_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{
	return 0;
}

void CHsvDvbsFransat_mAcq_Priv::idataacq_SyncTemporaryTableRecords			(	void	)
{
}
