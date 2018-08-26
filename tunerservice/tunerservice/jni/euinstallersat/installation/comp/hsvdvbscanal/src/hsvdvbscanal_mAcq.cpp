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
 *          %name: hsvdvbscanal_mAcq.c %
 *       %version: TVG_20 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: aneeshc %
 */
 
/* include dependencies */
#include	"_hsvdvbscanal_mAcq.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbscanal_macq")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

/* Macros */

													















/* Local Structures and enums */























/****************************************************************************
 * Static variables
 ****************************************************************************/

CanalLCNData CHsvDvbsCanal_mAcq_Priv::s__mLCNData;

CanalServiceList CHsvDvbsCanal_mAcq_Priv::s__mSvcListData;

CanalSatDSDesc CHsvDvbsCanal_mAcq_Priv::s__mCanalDSDesc;


int CHsvDvbsCanal_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsCanal_mAcq_Priv::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsCanal_mAcq_Priv::s__mDigitalRadioChannelsFound = 0;

Pump CHsvDvbsCanal_mAcq_Priv::s__mDataAcqPump;


int CHsvDvbsCanal_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsCanal_mAcq_Priv::s__removeCurRadio =0;

HsvDataAcqInstance CHsvDvbsCanal_mAcq_Priv::s__DataAcqInstance;


HsvInstallationPTC CHsvDvbsCanal_mAcq_Priv::s__CurrentPTC;

HsvBarkerMuxData CHsvDvbsCanal_mAcq_Priv::s__BarkerMuxData;

double CHsvDvbsCanal_mAcq_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};



int CHsvDvbsCanal_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID][2] = 
{
    /*Onid*/     { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)   },
    /*Tsid*/     { HSVSPID(ActualTsId, dvb, sdt),                 HSVSPID(OtherTsId, dvb, sdt)                },
    /*VerNo*/    { HSVSPID(ActualTsVersionNo, dvb, sdt),          HSVSPID(OtherTsVersionNo, dvb, sdt)         },
    /*SLD*/    { HSVSPID(ActualServiceList, dvb, nit),          HSVSPID(OtherServiceList, dvb, nit)         },
    /*SDSD*/    { HSVSPID(SatelliteDS, dvb, nit),          HSVSPID(SatelliteDS, dvb, nit)         },
/*SpidService*/  { HSVSPID(ActualTSService, dvb, sdt),            HSVSPID(OtherSDTSection, dvb, sdt)          },
    /*LCNv1*/    { HSVSPID(ActualNetworkLCN,dvb,nit),			  HSVSPID(OtherNetworkLCN, dvb, nit)		  },
    /*LCNv2*/    { HSVSPID(ActualNetworkLCN2,dvb,nit),			  HSVSPID(OtherNetworkLCN2, dvb, nit)		  }
};



/****************************************************************************
 * Static functions
 ****************************************************************************/


/* Static functions */
















































void CHsvDvbsCanal_mAcq_Priv::mPumpHandler(int value, Nat32 param)
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

void CHsvDvbsCanal_mAcq_Priv::mStartHomingAcquisition(void)
{
       /* SDTOtherStatus is checked in mCollectSdsds function so get it before collectSdsds */
	mGetSDTOtherStatus();
	/*Collect Sdsds from strapi*/
	mCollectSdsds();
	mGetSatelliteLnbNo(THOR_1W);
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


int CHsvDvbsCanal_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{

	int RetVal = FALSE;
	if(iutil_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		RetVal = TRUE;
	}
	return RetVal;	
}
Bool CHsvDvbsCanal_mAcq_Priv::mCollectBarkerMuxData(void)
{
	int NumOfLinkageDesc = 0, i = 0, j = 0, index = 0;
	Bool RetVal = FALSE;
	
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;

	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));
	memset(&BarkerMuxData, 0, sizeof(HsvBarkerMuxData));
	BarkerMuxData.NoOfRecords = 0;
				index = 0;
	

	for(i = 0; i < NumOfLinkageDesc ; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, nit), i, (void*)(&LinkageDesc)) == TRUE)
		{
			if(LinkageDesc.LinkageType == BARKER_MUX_LINKAGE_TYPE)
			{
				/*Get the barker mux data and write into the file*/
				/*check if data has to be appended or written as new*/
				BarkerMuxData.Mux[index].OnId = LinkageDesc.Original_NetworkId;
				BarkerMuxData.Mux[index].TsId = LinkageDesc.Tsid;
				BarkerMuxData.Mux[index].Params.Type = AppApiDVBSType;
				BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = DataAcqInstance.LnbNumber;
				for(j = 0; j < mCanalDSDesc.NumOfSDSD; j++)
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
		else
		{
			TraceNotice (m," Collect linkage info failed for index: %d \n",i);
		}
	}
	
TraceNotice (m," Number of  Barker Mux index: %d \n",index);
	return RetVal;
}


void CHsvDvbsCanal_mAcq_Priv::mStartFallbackAcquisition(void)
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
			if(mCanalDSDesc.CurrentSDSDIndex == (mCanalDSDesc.NumOfSDSD-1))
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


void CHsvDvbsCanal_mAcq_Priv::mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
{
	ptc->LnbNumber = DataAcqInstance.LnbNumber;
	ptc->Polarization = Sdsd.Polarization;	
	ptc->Frequency = Sdsd.Frequency;
	ptc->SDSDFrequency = Sdsd.Frequency;
	ptc->SymbolRate = Sdsd.SymbolRate;
	ptc->ModulationType = Sdsd.ModulationType;
	ptc->ModulationStd    = Sdsd.ModulationSystem;
	ptc->CodeRate   	  = Sdsd.FECInner;
	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);


}

Bool CHsvDvbsCanal_mAcq_Priv::mGetTSMetaData(void)
{
    Bool	retval = FALSE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, GETHSVSPID(Onid, ACTUAL_TABLE), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(Tsid, ACTUAL_TABLE), 0, 0, 0, &DataAcqInstance.Tsid);

	TraceNotice (m, "ONID %d and TsId %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);

    return retval;
}


void CHsvDvbsCanal_mAcq_Priv::mAcquireTSInfo(void)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) CurrentSdsd;
	KeyUpdateReason KeyUpdate = NoUpdate;
	HsvPgdatDigTSData OldTsData;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &OldTsData);
	
	TraceInfo  (m, " DataAcqInstance.CurSdsd %d DataAcqInstance.NumSdsds %d sizeof(CurrentSdsd) %d", DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(CurrentSdsd));
	if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
	{
		if(strapi_GetByIndex(HsvMain, GETHSVSPID(SDSD,ACTUAL_TABLE), DataAcqInstance.CurSdsd, (void *)(&CurrentSdsd)) == TRUE)
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


void CHsvDvbsCanal_mAcq_Priv::mDeleteTSTable(HsvInstallationPTC *ptc)
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

void CHsvDvbsCanal_mAcq_Priv::mDeleteMuxesFromCurrentNIT(void)
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

Bool CHsvDvbsCanal_mAcq_Priv::mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	Bool RetVal = FALSE;
	int i;

	/*In Homing mode, check by using strapi and in Fallback mode, check in saved list*/
	if(DataAcqInstance.Mode == Homing)
	{
		if(strapi_GetByKey(HsvMain, GETHSVSPID(SDSD, ACTUAL_TABLE), tmptsdata->OriginalNetworkId, tmptsdata->Tsid, tmptsdata->NetworkId, (void *)(&tmpsdsd)) == TRUE)
		{
			RetVal = TRUE;
		}
	}
	else
	{
		for (i = 0; i < mCanalDSDesc.NumOfSDSD; i++)
		{
			if((tmptsdata->OriginalNetworkId == mCanalDSDesc.SatDesc[i].Original_NetworkId) && (tmptsdata->Tsid == mCanalDSDesc.SatDesc[i].Tsid))
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
then old Tpid entry is deleted and new entry is added with new freq\pol and oldTpid is returned*/
void CHsvDvbsCanal_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, KeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData)
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

Bool CHsvDvbsCanal_mAcq_Priv::mInstallHomingMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	HSVSPTYPE(ActualServiceList, dvb, nit) servicelist;
	SvcListInfo	SeviceListInfo;;
	int		i, from = 0, to = 0,InstalledServices = 0;

	if(strapi_GetRangeByKey(HsvMain, GETHSVSPID(SLD, ACTUAL_TABLE), 2, DataAcqInstance.Onid, DataAcqInstance.Tsid, 0, &from, &to) == TRUE)
	{
		TraceNotice (m, "%s %d NoOfServices in MUX = %d ONID = %d TSID = %d \n",__FUNCTION__, __LINE__, ((to - from)+1),DataAcqInstance.Onid, DataAcqInstance.Tsid);

		/* From strapi get all the services and add/update in SERVICE_TABLE */
		for(i = to; i >= from ; i--)
		{
				if(strapi_GetByIndex(HsvMain, GETHSVSPID(SLD, ACTUAL_TABLE), i, (void *)(&servicelist)) == TRUE)
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
			/*Here OldTpid will remain with non transmitted services*/
			mDeleteAllServicesFromCarrier(OldTsData->Tpid);
		}
		else
		{
			mDeleteServicesCurrentCarrier(&ptc);
		}
	}


	TraceNotice (m, "Homing Mode: Updateprint: Num TV: %d Num Radio: %d \n", mDigitalTvChannelsFound, mDigitalRadioChannelsFound);
//	TraceNotice(m, "Installed %d services\n", InstalledServices);

       return retval;
}


Bool CHsvDvbsCanal_mAcq_Priv::mInstallFallbackMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
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


Bool CHsvDvbsCanal_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC *ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData, SvcListInfo *ServiceList)
{
	Bool	retval = FALSE, channelExists = FALSE, IsDuplicatesvc = FALSE, IsServiceAdded = FALSE, ToAdd = FALSE;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvPgdatDigServiceData 		svcdat, tempsvcdat;
	HsvPgdatPresetData			presetData;	

	IsDuplicatesvc = FALSE;
	IsServiceAdded = FALSE;
	ToAdd = FALSE;
	pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

	/*If db key(Tpid) is updated, delete the service and add it again with new Tpid (as Tpid is the key for service table)*/
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
	if(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == FALSE)
	{
		if((DataAcqInstance.Mode == Homing) && 
			(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, OTHER_TABLE), svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Tsid, (void *)(&service)) == TRUE))
		{
			ToAdd = TRUE;
			TraceNotice(m, "SDT OTHER avilable for svcid: %d, svctype: %d",service.ServiceId,service.ServiceType);
		}
		else
		{
			TraceNotice(m,"SDT OTHER not avilable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
		}
	}
	else
	{
		ToAdd = TRUE;
		TraceNotice(m,"SDT ACTUAL avilable for onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
	}

	if(mIsServiceInstallable(&service) == FALSE)
	{
		ToAdd = FALSE;
		TraceNotice(m,"service is not installable onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
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
		/*Delete the duplicate service with old Tpid,svcid*/
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
		tempsvcdat.Tpid = OldTsData->Tpid;
		tempsvcdat.ServiceId = ServiceList->ServiceId;
		pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		Proceed = (!VALID_LCN_RANGE(tempsvcdat.LCN))&&(IS_RADIO_SERVICE(tempsvcdat.ServiceType) != IS_RADIO_SERVICE(svcdat.ServiceType));
        REVALIDATE(tempsvcdat.LCN);
		Proceed |= ((VALID_LCN_RANGE(tempsvcdat.LCN) || VALID_LCN_RANGE(svcdat.LCN)) && (tempsvcdat.LCN != svcdat.LCN));
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



void CHsvDvbsCanal_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
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
			if ( RetVal == TRUE && (mIsSvcPresentInServiceList(&TempSvcData) == FALSE) && (TempSvcData.SDSDFrequency != 0)) /* Dont delete services installed by generic module*/
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
	else
	{
		TraceNotice(m,"Get Range failed in %s\n", __FUNCTION__);
	}
}

Bool CHsvDvbsCanal_mAcq_Priv::mIsSvcPresentInServiceList(HsvPgdatDigServiceData *svcdata)
{
	Bool retval = FALSE;
	HSVSPTYPE(ActualServiceList, dvb, nit) service;
	int i;

	
	/*In Homing mode, check from strapi. In Fallback mode, check in stored list*/
	if(DataAcqInstance.Mode == Homing)
	{
		if(strapi_GetByKey(HsvMain, GETHSVSPID(SLD, ACTUAL_TABLE),svcdata->OriginalNetworkId, svcdata->Tsid,svcdata->ServiceId, (Address)(&service)) == TRUE)
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

int CHsvDvbsCanal_mAcq_Priv::mDeleteAllServicesFromCarrier(int Tpid)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;
	int 							ret = TRUE;

	TempSvcData.Tpid 		 = Tpid;

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

void CHsvDvbsCanal_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
	mAssignSvcNonBroadcastAttributes(psvcdat);
	mUpdateSatelliteName (psvcdat);

	pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
		
	TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbsCanal_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;

	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
	}
}

void CHsvDvbsCanal_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool IsDuplicatesvc)
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

Bool CHsvDvbsCanal_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}

void CHsvDvbsCanal_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
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
	//psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
	//psvcdat->NumBrandIds           =   service->NumBrandIds;
	mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds );

	psvcdat->ScramblingStatus		= 0; 
	if(service->Free_CA_Mode == TRUE)
	{
		psvcdat->ScramblingStatus = 1;
	}

	mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_PresetNameLength - 1) );

	//psvcdat->NumericSelect = TRUE;
	psvcdat->SystemHidden = !(psvcdat->VisibleService);

}

void CHsvDvbsCanal_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
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
	psvcdat->PackageGroup 		= APPAPISAT_CanalDigital;
	

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
	{
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


int CHsvDvbsCanal_mAcq_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
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

int CHsvDvbsCanal_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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

Bool CHsvDvbsCanal_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
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

Bool CHsvDvbsCanal_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsCanal_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}


Bool CHsvDvbsCanal_mAcq_Priv::mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sdt)* service)
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

void CHsvDvbsCanal_mAcq_Priv::mCollectSdsds (void)
{
	int i =0;

	mCanalDSDesc.NumOfSDSD = strapi_GetSize (HsvMain, GETHSVSPID(SDSD,ACTUAL_TABLE));
	if(mCanalDSDesc.NumOfSDSD > MAX_SDSD)
	{
		TraceNotice(m,"Number of SDSDs : %d exceeds MAX_SDSDs",mCanalDSDesc.NumOfSDSD);
		mCanalDSDesc.NumOfSDSD = MAX_SDSD; 
	}
	for(i = 0; i < mCanalDSDesc.NumOfSDSD; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&(mCanalDSDesc.SatDesc[i]))) == FALSE)
		{
			TraceNotice (m," Collect SDSD failed for SDSD: %d \n",i);
		}
	}

	DataAcqInstance.CurSdsd = 0;
	DataAcqInstance.NumSdsds = 	mCanalDSDesc.NumOfSDSD;
	TraceNotice (m," DataAcqInstance.NumSdsds %d \n",DataAcqInstance.NumSdsds);
}

void CHsvDvbsCanal_mAcq_Priv::mCollectServicelistData(void)
{
	HSVSPTYPE(ActualServiceList, dvb, nit) svcList;
	int i = 0, numOfEntries = 0;
	numOfEntries = strapi_GetSize(HsvMain, GETHSVSPID(SLD,ACTUAL_TABLE));
	mSvcListData.NumOfRecords = 0;
	for(i = 0 ; i < numOfEntries; i++)
	{
		if(strapi_GetByIndex(HsvMain, GETHSVSPID(SLD,ACTUAL_TABLE), i, (void*)(&svcList)))
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
			TraceNotice (m," Collect service list failed for index: %d \n",i);
		}
	}
}

Bool CHsvDvbsCanal_mAcq_Priv::mGetLCN(t_LCNInfo *LCNInfo)
{
    Bool retval = FALSE;
    int TableId =  ACTUAL_TABLE;

    retval = mLcnVersion2Data(GETHSVSPID(LCNv2, TableId), LCNInfo, FALSE);
    if(retval == FALSE)
    {
        retval = mLcnVersion1Data(GETHSVSPID(LCNv1, TableId), LCNInfo, FALSE);
    }

    return retval;

}

Bool CHsvDvbsCanal_mAcq_Priv::mAcquireLCNData(void)
{
    Bool retval = FALSE;
    int TableId =  ACTUAL_TABLE;
    t_LCNInfo LCNInfo;
	
    retval = mLcnVersion2Data(GETHSVSPID(LCNv2, TableId), &LCNInfo, TRUE);
    if(retval == FALSE)
    {
        retval = mLcnVersion1Data(GETHSVSPID(LCNv1, TableId), &LCNInfo, TRUE);
    }

    return retval;

}

Bool CHsvDvbsCanal_mAcq_Priv::mLcnVersion1Data(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HsvPid);
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) nwlcn;

    if( AcquireAll == TRUE )
    {
        for(i = 0; i < numOfRecords; i++)
        {
            if( (strapi_GetByIndex(HsvMain, HsvPid, i, (Address)(&nwlcn)) == TRUE) )
            {
                retval = TRUE;
                if(mPopulateLCN((Address)(&nwlcn), VERSION1) == FALSE)
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
                    nwlcn.VisibleService, VERSION1);
            retval = TRUE;
        }
    }
    return retval;
}

Bool CHsvDvbsCanal_mAcq_Priv::mLcnVersion2Data(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll)
{
    Bool retval = FALSE; 
    int NoOfRecs, i, channellistid, from = 0, to = 0, countrycode = 0;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    NoOfRecs = strapi_GetSize(HsvMain, HsvPid);

    if( LCN_VERSION2_PRESENT(NoOfRecs) )
    {
    	/*Get first channel list with user selected country */
        mGetInterestedLCNRecords(HsvPid, &from, &to, &countrycode);
        channellistid = mGetInterestedChanneListId(HsvPid, from, to, &countrycode);
		TraceDebug(m,"%s country code:%d",__FUNCTION__,countrycode);
        if(TRUE == strapi_GetRangeByKey(HsvMain,HsvPid, 2, countrycode, channellistid, 0, &from, &to))
        {
            for(i = from; i <= to; i++)
            {
                if(strapi_GetByIndex(HsvMain, HsvPid, i, (Address)(&nwlcn)) == TRUE) 
                {
                    if( AcquireAll == TRUE )
                    {
                        retval = TRUE;
                        if(mPopulateLCN((Address)(&nwlcn), VERSION2) == FALSE)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if( (LCNInfo->Onid == nwlcn.Original_NetworkId) && (LCNInfo->Tsid == nwlcn.Tsid) && (LCNInfo->ServiceId == nwlcn.ServiceId) )
                        {
                            mCopyLCNInfo( LCNInfo, nwlcn.Original_NetworkId, nwlcn.Tsid, \
                                    nwlcn.ServiceId, nwlcn.LogicalChannelNum, nwlcn.VisibleService, VERSION2);
                            retval = TRUE;
                            break;
                        }
                    }   
                }
            }
        }
    }
    return retval;
}

Bool CHsvDvbsCanal_mAcq_Priv::mPopulateLCN(Address data, int version)
{
    int cacheIndex = 0;
    Bool retval = TRUE;
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) *nwlcn;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) *nwlcn2;

    switch(version)
    {
        case VERSION1:
            nwlcn = (HSVSPTYPE(ActualNetworkLCN, dvb, nit) *)data;
            cacheIndex = mGetLCNIndex(nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId);

            mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId, \
                    nwlcn->LogicalChannelNum, nwlcn->VisibleService, version);
            mLCNData.VersionNumber = nwlcn->VersionNumber;

            if(cacheIndex >= mLCNData.NumOfLCNRecords)
            {
                mLCNData.NumOfLCNRecords++;
            }
            break;
        case VERSION2:
            nwlcn2 = (HSVSPTYPE(ActualNetworkLCN2, dvb, nit) *)data;
            cacheIndex = mGetLCNIndex(nwlcn2->Original_NetworkId, nwlcn2->Tsid, nwlcn2->ServiceId);

            mLCNData.VersionNumber = nwlcn2->VersionNumber;

            if(cacheIndex >= mLCNData.NumOfLCNRecords)
            {
                mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwlcn2->Original_NetworkId, nwlcn2->Tsid, nwlcn2->ServiceId, \
                        nwlcn2->LogicalChannelNum, nwlcn2->VisibleService, version);
                mLCNData.NumOfLCNRecords++;  
            }
            else
            {
                /* This case is to access the right index from the list of records*/
                mCopyLCNInfo( &(mLCNData.mLCNInfo[cacheIndex]), nwlcn2->Original_NetworkId, nwlcn2->Tsid, nwlcn2->ServiceId, \
                        nwlcn2->LogicalChannelNum, nwlcn2->VisibleService, version);


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

void CHsvDvbsCanal_mAcq_Priv::mGetInterestedLCNRecords(int HsvPid, int *from, int *to, int *countrycode)
{
	/* Getting the current country */
	//*countrycode = sysset_GetSystemCountry();
	int packageid=insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	*countrycode = mGetCorrespondingCountryForPackage(packageid);
	TraceDebug(m," Packageid = %d and Country code=%d",packageid,*countrycode);
	if(strapi_GetRangeByKey(HsvMain,HsvPid, 1, *countrycode, 0, 0, from, to) == FALSE)
	{
		*from = 0, *to = strapi_GetSize(HsvMain, HsvPid);
		TraceNotice(m," from= %d and to= %d",*from,*to);
	}
	TraceDebug(m," from= %d and to= %d",*from,*to);
}

int CHsvDvbsCanal_mAcq_Priv::mGetInterestedChanneListId(int HsvPid, int from, int to, int *countrycode)
{
    int i, channellistid = 0;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    if(strapi_GetByIndex(HsvMain, HsvPid, from, (void*)(&nwlcn)) == TRUE)
    {
        channellistid = nwlcn.ChannelListId;
        *countrycode = nwlcn.CountryCode;
		for(i = (from + 1); i <= to; i++)
        {
            if(TRUE == strapi_GetByIndex(HsvMain, HsvPid, i, (void*)(&nwlcn)))
            {
                if(nwlcn.ChannelListId < channellistid)
                {
                    *countrycode = nwlcn.CountryCode;
                    channellistid = nwlcn.ChannelListId;
                }
            }
        }
    }
    return channellistid;
}
int CHsvDvbsCanal_mAcq_Priv::mGetCorrespondingCountryForPackage(int packageid)
{
	int country = 0;
	switch(packageid)
	{
		case CANALDIGITAL_DENMARK_PACKAGE_ID:country = cids_CountryDenmark;break;
		case CANALDIGITAL_SWEDEN_PACKAGE_ID:country =  cids_CountrySweden;break;
		case CANALDIGITAL_FINLAND_PACKAGE_ID:country = cids_CountryFinland;break;
		case CANALDIGITAL_NORWAY_PACKAGE_ID:country =  cids_CountryNorway;break;
	}
	return country;
}

inline void CHsvDvbsCanal_mAcq_Priv::mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version)
{
    LCNInfo->Onid              = OnId;
    LCNInfo->Tsid              = TsId;
    LCNInfo->ServiceId         = SvcId;
    LCNInfo->LogicalChannelNum = Lcn;
    LCNInfo->VisibleService    = VisibleSvc;
    LCNInfo->LCNType           = version;
}

void CHsvDvbsCanal_mAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
    t_LCNInfo LCNInfo;
    int cacheIndex = 0;

    if(mLCNData.NumOfLCNRecords == 0)
    {
        LCNInfo.Onid = psvcdat->OriginalNetworkId; LCNInfo.Tsid = psvcdat->Tsid; LCNInfo.ServiceId = psvcdat->ServiceId; //keys to get the LCN frm strapi records 
        if(mGetLCN(&LCNInfo) == TRUE)
        {
            psvcdat->LCN = (VALID_LCN_RANGE(LCNInfo.LogicalChannelNum) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
            psvcdat->VisibleService = LCNInfo.VisibleService;

        }
    }
    else
    {
        cacheIndex = mGetLCNIndex(psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
        if(cacheIndex != mLCNData.NumOfLCNRecords)
        {
            psvcdat->LCN = (VALID_LCN_RANGE(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;
            psvcdat->VisibleService = mLCNData.mLCNInfo[cacheIndex].VisibleService;

        }
    }
}

inline int CHsvDvbsCanal_mAcq_Priv::mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId)
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


void CHsvDvbsCanal_mAcq_Priv::mGetSDTOtherStatus(void)
{
	int Size = 0;
	DataAcqInstance.SDTOtherPresent = FALSE;
	
	Size = strapi_GetSize (HsvMain, GETHSVSPID(SpidService,OTHER_TABLE));
	if(Size != 0)
	{
		DataAcqInstance.SDTOtherPresent = TRUE;
	}

	TraceNotice (m, " SDT OTHER present status: %d \n",DataAcqInstance.SDTOtherPresent);
}

void CHsvDvbsCanal_mAcq_Priv::mGetSatelliteLnbNo(int SatId)
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

Bool CHsvDvbsCanal_mAcq_Priv::IsManualInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsCanal_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsCanal_mAcq_Priv::iacqpow_Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbcanal_mDataAcq" );
	
	TraceNotice (m, " Canal Acq Module pow Initialized \n");

}

void CHsvDvbsCanal_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsCanal_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsCanal_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
    /* Resetting all the variables */
    mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
    removeCurTv = removeCurRadio = 0;
	memset(&mLCNData,0,sizeof(mLCNData));
	UNUSED(LnbNumber);
}

void CHsvDvbsCanal_mAcq_Priv::idataacq_AcquireData(int Mode)
{

	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)Mode);
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);
	
	return removeCurTv;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);
	
	return removeCurRadio;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return mCanalDSDesc.NumOfSDSD;
}

Bool CHsvDvbsCanal_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mCanalDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry, &mCanalDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));
		mCanalDSDesc.CurrentSDSDIndex = count;
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsCanal_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);
	
	return RadioChannelsFound;
}

void CHsvDvbsCanal_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	TraceNotice(m, "%s LCN %d VisFlag %d <%d %d %d>", __FUNCTION__, psvcdat->LCN, psvcdat->VisibleService, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
	mAssignLCN(psvcdat);
}

void CHsvDvbsCanal_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{
	TraceNotice(m, "%s :Error should not land here", __FUNCTION__);
}

void CHsvDvbsCanal_mAcq_Priv::idataacq_AcquireDataOnTimeout                        (   void    )
{

}


void CHsvDvbsCanal_mAcq_Priv::idataacq_SyncTemporaryTableRecords			(	void	)
{

}
