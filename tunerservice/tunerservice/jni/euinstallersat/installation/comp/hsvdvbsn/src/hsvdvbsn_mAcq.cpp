/*
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary information of Koninklijke
  *  Philips Electronics N.V. and is confidential in nature.  Under no circumstances is this software to beexposed  
  *  to or placed under an Open Source License of any type without the expressed written permission of 
  *  Koninklijke Philips Electronics N.V.
  *
  *  %name: hsvdvbsn_mAcq.c %
  *  %version:  TVG_5 %
  *  %date_modified:  %
  *  %derived_by:  aneeshc % 
  */
  
/*****************************************************************************************
 *  Include dependencies
 *****************************************************************************************/
#include	"_hsvdvbsn_mAcq.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsn_macq")

/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/


















/* Local Structures and enums */


















/*****************************************************************************************
 * Static variables
 *****************************************************************************************/

NLCNData CHsvDvbsN_mAcq_Priv::s__mLCNData;

NSatDSDesc CHsvDvbsN_mAcq_Priv::s__mNDSDesc;


int CHsvDvbsN_mAcq_Priv::s__mDigitalChannelsFound = 0,CHsvDvbsN_mAcq_Priv::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsN_mAcq_Priv::s__mDigitalRadioChannelsFound = 0;

Pump CHsvDvbsN_mAcq_Priv::s__mDataAcqPump;


int CHsvDvbsN_mAcq_Priv::s__removeCurTv = 0,CHsvDvbsN_mAcq_Priv::s__removeCurRadio = 0;

HsvDataAcqInstance CHsvDvbsN_mAcq_Priv::s__DataAcqInstance;


HsvInstallationPTC CHsvDvbsN_mAcq_Priv::s__CurrentPTC;

HsvBarkerMuxData CHsvDvbsN_mAcq_Priv::s__BarkerMuxData;

AcqSDT CHsvDvbsN_mAcq_Priv::s__sdt_mode;


double CHsvDvbsN_mAcq_Priv::s__RollOffTable[4]  =
{
    0.35, /* "00" */
    0.25, /* "01" */
    0.20, /* "10" */
    0.00  /* "11" -- Reserved */
};


int CHsvDvbsN_mAcq_Priv::s__mHsvDVBPIDList[MAX_PROPERTY_ID][2] = 
{
    /*Onid*/        { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)},
    /*Tsid*/        { HSVSPID(ActualTsId, dvb, sdt),         HSVSPID(OtherTsId, dvb, sdt)       },
    /*VerNo*/      { HSVSPID(ActualTsVersionNo, dvb, sdt),  HSVSPID(OtherTsVersionNo, dvb, sdt) },
    /*SDSD*/      { HSVSPID(SatelliteDS, dvb, nit),        HSVSPID(SatelliteDS, dvb, nit)      },
    /*SpidService*/ { HSVSPID(ActualTSService, dvb, sdt),    HSVSPID(OtherSDTSection, dvb, sdt)  },
    /*LCN*/        { HSVSPID(ActualNetworkLCN,dvb,nit),     HSVSPID(OtherNetworkLCN, dvb, nit) }
};


/*****************************************************************************************
 * Static functions
 *****************************************************************************************/











































void CHsvDvbsN_mAcq_Priv::mPumpHandler(int value, Nat32 param)
{
    Bool Status = FALSE;
    TraceNotice (m," N ACQ mPumpHandler %d value",value);
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
            sdt_mode = Sdt_actual;
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
	case EvDeleteNonTransmittedTs:
		mDeleteMuxesFromCurrentNIT ();	
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);
		break;
    }
}

void CHsvDvbsN_mAcq_Priv::mStartHomingAcquisition(void)
{
    /* SDTOtherStatus is checked in mCollectSdsds function so get it before collectSdsds */
    mGetSDTOtherStatus();
    /* Collect Sdsds from strapi */
    mCollectSdsds();
    mGetSatelliteLnbNo(HOTBIRD_13_0_E);
    if(mCollectBarkerMuxData() == FALSE)
    {
        TraceNotice(m,"N ACQ Barker mux data collection failed");
    }
    if(DataAcqInstance.SDTOtherPresent)
    {
        /* start acquiring TSinfo */
        mAcquireTSInfo();
    } else {
        mAcquireLCNData();
        pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);
    }
}


int CHsvDvbsN_mAcq_Priv::idataacq_StoreBarkerMuxDetails(void)
{

	int RetVal = FALSE;
	if(iutil_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		RetVal = TRUE;
	}
	
	return RetVal;
}
Bool CHsvDvbsN_mAcq_Priv::mCollectBarkerMuxData(void)
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
                /* Get the barker mux data and write into the file */
                /* check if data has to be appended or written as new */
                BarkerMuxData.Mux[index].OnId = LinkageDesc.Original_NetworkId;
                BarkerMuxData.Mux[index].TsId = LinkageDesc.Tsid;
				BarkerMuxData.Mux[index].Params.Type = AppApiDVBSType;
				BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = DataAcqInstance.LnbNumber;
//                BarkerMuxData.Mux[index].Params.TuningParams.DVBSParam.sat_id = HOTBIRD_13_0_E;
                
                for(j = 0; j < mNDSDesc.NumOfSDSD; j++)
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


void CHsvDvbsN_mAcq_Priv::mStartFallbackAcquisition(void)
{
    TraceNotice(m," %s %d \n",__func__,__LINE__);
    KeyUpdateReason 				KeyUpdate = NoUpdate;
    HsvPgdatDigTSData			OldTsData;

    /* Getting ONID, TS details */
    Bool retval = mGetTSMetaData();

    if(retval == TRUE)
    {
        isvcscandata_GetPtcInfo(&CurrentPTC);
        TraceNotice(m," %s %d  Current PTC Frequecny [%d] \n",__func__,__LINE__,CurrentPTC.Frequency); 
        if(IsUpdateInstall() == TRUE)
        {
            /*If TS is already present with different Keys then add services with new keys returned*/
            mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
            TraceNotice(m," Update %s %d \n",__func__,__LINE__);
            if(mInstallFallbackMux(CurrentPTC, KeyUpdate, &OldTsData) == FALSE )
            {
                /* If no services are added\updated, delete entry from TS Table */
                mDeleteTSTable(&CurrentPTC);
            }
            /* Delete the muxes from NIT if current mux is last*/
            if(mNDSDesc.CurrentSDSDIndex == (mNDSDesc.NumOfSDSD-1))
            {
                /*Update this fn to delete muxes in fallback mode also*/
                mDeleteMuxesFromCurrentNIT();
            }
        }
        else
        {
            TraceNotice(m," Add %s %d \n",__func__,__LINE__);
            /*Intsall the services and Add to TS Table*/
            if(mInstallFallbackMux(CurrentPTC, KeyUpdate, &OldTsData) == TRUE )
            {
                /* Add entry to TS Table */
                TraceNotice(m," mAddToTSTable %s %d \n",__func__,__LINE__);
                mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
            }
        }
        pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)TRUE);
    }

}


void CHsvDvbsN_mAcq_Priv::mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
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
	ptc->QSignalStrength = 0;
	ptc->SSignalStrength = 0;
	ptc->HierarchyMode = HsvHierarchyNone;
	ptc->StreamPriority = HsvStreamPriorityHigh;
    ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);
	isvcscandata_GetPtcInfoForSdSd (ptc);
}

Bool CHsvDvbsN_mAcq_Priv::mGetTSMetaData(void)
{
    Bool	retval = FALSE;

	/* Get ONID, TSID deta	ils */
    retval = strapi_GetByKey(HsvMain, GETHSVSPID(Onid, ACTUAL_TABLE), 0, 0, 0,&DataAcqInstance.Onid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(Tsid, ACTUAL_TABLE), 0, 0, 0, &DataAcqInstance.Tsid);
    strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &DataAcqInstance.NetworkId);
  //  DataAcqInstance.NetworkId = DataAcqInstance.Onid;

	TraceNotice (m, "ONID %d and TsId %d NwId[%d] \n", DataAcqInstance.Onid, DataAcqInstance.Tsid,DataAcqInstance.NetworkId);

    return retval;
}

void CHsvDvbsN_mAcq_Priv::updateSdtMode(HSVSPTYPE(SatelliteDS,dvb,nit) CurrentSdsd)
{
    HsvInstallationPTC tunedPTC;

    isvcscandata_GetPtcInfo(&tunedPTC);

    
    if(ABS(tunedPTC.Frequency,CurrentSdsd.Frequency) < FREQ_DRIFT_TOLERANCE) {
        TraceNotice(m,"updateSdtMode Actual \n");
        sdt_mode = Sdt_actual;
    } else {
        TraceNotice(m,"updateSdtMode Other \n");    
        sdt_mode = Sdt_other;
    }   
}

void CHsvDvbsN_mAcq_Priv::mAcquireTSInfo(void)
{
    HSVSPTYPE(SatelliteDS,dvb,nit) CurrentSdsd;
    KeyUpdateReason KeyUpdate = NoUpdate;
    HsvPgdatDigTSData OldTsData;

    pgdb_Initialise(pgdbconst_DigitalTS, (Address) &OldTsData);

    TraceNotice(m," DataAcqInstance.CurSdsd %d DataAcqInstance.NumSdsds %d sizeof(CurrentSdsd) %d \n", DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(CurrentSdsd));
    if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
    {
        if(strapi_GetByIndex(HsvMain, GETHSVSPID(SDSD,ACTUAL_TABLE), DataAcqInstance.CurSdsd, (void *)(&CurrentSdsd)) == TRUE)
        {
            DataAcqInstance.NetworkId = CurrentSdsd.NetworkId;
            DataAcqInstance.Onid = CurrentSdsd.Original_NetworkId;
            DataAcqInstance.Tsid = CurrentSdsd.Tsid;
            /* In Homing mode PTC info is built with in Acq. module as no tuning to SDSD is required */
            mGetPTCInfo(CurrentSdsd,&CurrentPTC);

            updateSdtMode(CurrentSdsd);

            if(IsUpdateInstall() == TRUE)
            {
            /*If TS is already present with different Keys then add services with new keys returned*/
            mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
            TraceNotice(m," UPDATE SDSD LOOP NetworkId[%d] Onid[%d] Tsid[%d] \n",DataAcqInstance.NetworkId,DataAcqInstance.Onid,DataAcqInstance.Tsid);
            if(mInstallHomingMux(CurrentPTC, KeyUpdate, &OldTsData) == FALSE )
            {
            /* If no services are added\updated, delete entry from TS Table */
            mDeleteTSTable(&CurrentPTC);
            }
            }
            else
            {
            /*Intsall the services and Add to TS Table*/
            TraceNotice(m,"SDSD LOOP NetworkId[%d] Onid[%d] Tsid[%d] \n",DataAcqInstance.NetworkId,DataAcqInstance.Onid,DataAcqInstance.Tsid);
            if(mInstallHomingMux(CurrentPTC, KeyUpdate, &OldTsData) == TRUE )
            {
            /* Add entry to TS Table */
            TraceNotice(m," mAddToTSTable Ln[%d] \n",__LINE__);
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
		TraceNotice(m,"EvCompleteAcquire SDSD COUNT[%d] \n",DataAcqInstance.CurSdsd);
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);	
    }
    else
    {
		TraceNotice(m,"SDSD COUNT[%d] \n",DataAcqInstance.CurSdsd);
		pmp_PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
    }
}


void CHsvDvbsN_mAcq_Priv::mDeleteTSTable(HsvInstallationPTC *ptc)
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

void CHsvDvbsN_mAcq_Priv::mDeleteMuxesFromCurrentNIT(void)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0 , i = 0;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

	for(i = NoOfTSTables - 1; i >= 0; i--)
	{
		pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
		if((pgdb_GetByIndex(PTC_TABLE, i, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
		{	
			/*Check if this TS table present in SDSD list*/
			if(mIsTSPresentInSDSDList(&tmptsdata) == FALSE)			
			{
				mDeleteAllServicesFromCarrier(tmptsdata.Tpid);
				TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization);
				pgdb_Delete(PTC_TABLE, (Address) &tmptsdata);
				//break;
				
			}
		}
    }

}

Bool CHsvDvbsN_mAcq_Priv::mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata)
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
		for (i = 0; i < mNDSDesc.NumOfSDSD; i++)
		{
			if((tmptsdata->OriginalNetworkId == mNDSDesc.SatDesc[i].Original_NetworkId) && (tmptsdata->Tsid == mNDSDesc.SatDesc[i].Tsid))
			{
				RetVal = TRUE;
				break;
			}
		}
	}
	return RetVal;
}

/* Keyupdate reason indicates if any key(freq/pol) is updated in SDSD or due to Acq. mode change.  
    if Acq mode changed in update install, ptc frequnecy may change as tuner will not be locked to 
    exact SDSD freq, in this case old ferquency is retained. If SDSD freq\pol. is changed 
    then old TPID entry is deleted and new entry is added with new freq\pol and old TPID is returned */
void CHsvDvbsN_mAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, KeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData)
{
    HsvPgdatDigTSData tsdata, tmptsdata;
    int NoOfTSTables = 0;
    int i = 0;

    pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);
    pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);

    /* Filling attributes from ptc and acqinstance */
    tsdata.Frequency            = ptc->Frequency;
    tsdata.SymbolRate           = ptc->SymbolRate;
    tsdata.OriginalNetworkId    = DataAcqInstance.Onid;
    tsdata.Tsid                 = DataAcqInstance.Tsid;
    tsdata.NetworkId            = DataAcqInstance.NetworkId;
    tsdata.ModulationType       = ptc->ModulationType;
    tsdata.Bandwidth     		= ptc->ChannelBandwidth;
    tsdata.PtcListVersion       = isvcscandata_GetInstallationVersion();
    tsdata.SDSDFrequency        = ptc->SDSDFrequency;
    tsdata.UserInstalled        = IsManualInstall();
    tsdata.LnbNumber            = ptc->LnbNumber;
    tsdata.Polarization         = ptc->Polarization;
    tsdata.Tpid                 = ptc->TPID;

    tmptsdata.LnbNumber = tsdata.LnbNumber;
    tmptsdata.Frequency = tsdata.Frequency;
    tmptsdata.Polarization = tsdata.Polarization;

    /* check entry already present. If yes update else add */
    if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE )
    {
    	/*If GetByKey is failed, check if any Keys(Frequency/polarization) are updated */
    	if(IsUpdateInstall() == TRUE)
    	{
    		NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

    		TraceNotice (m, "NoOfTSTables [%d] \n",NoOfTSTables);

    		for(i = 0; i<NoOfTSTables; i++)
    		{
    			pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
    			/*Check only TS tables installed via pkg install*/
    			if((pgdb_GetByIndex(PTC_TABLE, i, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
    			{
    				TraceNotice(m," tmptsdata.OriginalNetworkId[%d]  tsdata.OriginalNetworkId [%d]  tmptsdata.Tsid[%d]  tsdata.Tsid[%d] \n",
    					tmptsdata.OriginalNetworkId,tsdata.OriginalNetworkId,tmptsdata.Tsid,tsdata.Tsid);
    				if((tmptsdata.OriginalNetworkId == tsdata.OriginalNetworkId) && (tmptsdata.Tsid == tsdata.Tsid))
    				{
    					/*Return old Keys and TS table*/
    					OldTsData->LnbNumber = tmptsdata.LnbNumber;
    					OldTsData->Frequency = tmptsdata.Frequency;
    					OldTsData->Polarization = tmptsdata.Polarization;
    					TraceNotice (m, "Addition to pgdb table %s %d <%ld %d %ld>\n", __FUNCTION__, __LINE__, OldTsData->Frequency, OldTsData->Polarization,tmptsdata.Tpid);
    					pgdb_GetByKey(PTC_TABLE, (Address )OldTsData);
    					/*Check if pol&lnb are same and frequency is different and difference is with in the tolerance*/
    					if( ((tmptsdata.LnbNumber == tsdata.LnbNumber) && (tmptsdata.Polarization == tsdata.Polarization)) && 
    						(ABS(tmptsdata.Frequency, tsdata.Frequency) < FREQ_DRIFT_TOLERANCE))
    					{
    						*KeyUpdate = AcqModeChange;
    						tsdata.Frequency	= tmptsdata.Frequency;
    						tsdata.Tpid		= tmptsdata.Tpid;
    						TraceNotice (m, "Addition to pgdb table %s %d <%ld %d %ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization,tsdata.Tpid);
    						pgdb_Update(PTC_TABLE, (Address )&tsdata);
    						
    						break;
    						
    					}
    					else
    					{
    						*KeyUpdate = SDSDChange;
    			
    						/*Delete the Old TS Table with old Tpid and Add new TS Table with updated Tpid and keys */
    						pgdb_Delete(PTC_TABLE, (Address)&tmptsdata);
    						TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d %ld>\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization,tmptsdata.Tpid);
    						pgdb_Add(PTC_TABLE, (Address )&tsdata);
    						TraceNotice (m, "Addition to pgdb table %s %d <%ld %d %ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization,tsdata.Tpid);
    						break;
    					}
    					
    				}
    			}
    		}
    		/*It is a New TS, Add to TS table*/
    		if(i == NoOfTSTables)
    		{
    			TraceNotice (m, "Addition to pgdb table %s %d <%ld %d %ld>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization,tsdata.Tpid);
    			pgdb_Add(PTC_TABLE, (Address )&tsdata);
    		}
    	}
    	else
    	{
    		/*In Auto install, Add to TS table*/	
    		TraceNotice (m, " Auto install Addition to pgdb table %s %d \n", __FUNCTION__, __LINE__);
    		pgdb_Add(PTC_TABLE, (Address )&tsdata);
    	}

    }
    else
    {
    	TraceNotice (m, "Updation to pgdb table %s %d \n", __FUNCTION__, __LINE__);
    	pgdb_Update(PTC_TABLE, (Address )&tsdata);
    }
}



Bool CHsvDvbsN_mAcq_Priv::mAcquireSDTServices(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	HSVSPTYPE(ActualTSService, dvb, sdt) service_actual;
	HSVSPTYPE(OtherSDTSection, dvb, sdt) service_other;
	int		TableId_Actual 	= ACTUAL_TABLE;
	int		TableId_Other 	= OTHER_TABLE;
	SvcListInfo	SeviceListInfo;;
	int		i, InstalledServices = 0;
	int		TotalServices_Actual = 0;
	int		TotalServices_Other  = 0;
	Bool retval = FALSE;
	

	if(sdt_mode == 	Sdt_actual) {
		TotalServices_Actual = strapi_GetSize (HsvMain, GETHSVSPID(SpidService, TableId_Actual));
		
		TraceNotice (m, "SDT ACTUAL %s %d NoOfServices in MUX = %d ONID = %d TSID = %d \n",__FUNCTION__, __LINE__, TotalServices_Actual,DataAcqInstance.Onid, DataAcqInstance.Tsid);

		/* From strapi get all the services and add/update in SERVICE_TABLE */
		for(i = (TotalServices_Actual - 1); i >= 0 ; i--)
		{
				if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId_Actual), i, (void *)(&service_actual)) == TRUE)
				{
					
					SeviceListInfo.Onid        = DataAcqInstance.Onid;
					SeviceListInfo.Tsid        = DataAcqInstance.Tsid;
					SeviceListInfo.ServiceId   = service_actual.ServiceId;
					SeviceListInfo.ServiceType = mConvertToPgdatServiceType(service_actual.ServiceType);
					SeviceListInfo.NetworkId	= DataAcqInstance.NetworkId;
					if(mCheckServiceForInstall(&ptc, KeyUpdate, OldTsData,&SeviceListInfo))
					{
						InstalledServices++;
						retval = TRUE;
					}
				}
		}

		
	}
	else {	
			TotalServices_Other = strapi_GetSize (HsvMain, GETHSVSPID(SpidService, TableId_Other));
			TraceNotice (m, "%s %d NoOfServices in MUX = %d ONID = %d TSID = %d \n",__FUNCTION__, __LINE__, TotalServices_Other,DataAcqInstance.Onid, DataAcqInstance.Tsid);

			/* From strapi get all the services and add/update in SERVICE_TABLE */
			for(i = (TotalServices_Other - 1); i >= 0 ; i--)
			{
					if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId_Other), i, (void *)(&service_other)) == TRUE)
					{
						//TraceNotice (m, " SDT OTHER Service Count [%d] OnId[%d] TsId[%d] SvcId[%d] \n",i,service_other.Original_NetworkId,service_other.Tsid,service_other.ServiceId);
						//strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NwId);
						if((service_other.Original_NetworkId == DataAcqInstance.Onid) && (service_other.Tsid == DataAcqInstance.Tsid)) {
						//	TraceNotice (m, " CONTINUE [%d] \n",i);
							//continue;
						//}
						SeviceListInfo.Onid        = DataAcqInstance.Onid;
						SeviceListInfo.Tsid        = DataAcqInstance.Tsid;
						SeviceListInfo.ServiceId   = service_other.ServiceId;
						SeviceListInfo.ServiceType = mConvertToPgdatServiceType(service_other.ServiceType);
						SeviceListInfo.NetworkId	= DataAcqInstance.NetworkId;
						
						if(mCheckServiceForInstall(&ptc, KeyUpdate, OldTsData,&SeviceListInfo))
						{
							InstalledServices++;
							retval = TRUE;
						}
					}
						}
			}


	}

	return retval; 
		
}
Bool CHsvDvbsN_mAcq_Priv::mInstallHomingMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;




	retval = mAcquireSDTServices(ptc,KeyUpdate,OldTsData);
	
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
//	TraceNotice(m, "Installed %d services\n", InstalledServices);

       return retval;
}


Bool CHsvDvbsN_mAcq_Priv::mInstallFallbackMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
    Bool retval = FALSE;
    TraceNotice(m," %s %d \n",__func__,__LINE__);

    retval = mAcquireSDTServices(ptc,KeyUpdate,OldTsData);

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

    TraceNotice(m," %s %d retval[%d]  \n",__func__,__LINE__,retval);
    return retval;
	   
}


Bool CHsvDvbsN_mAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC *ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData, SvcListInfo *ServiceList)
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
	}
	/*TODO: check if it can be moved to installmux*/
	if(KeyUpdate == AcqModeChange)
	{
		ptc->Frequency = OldTsData->Frequency;
		ptc->TPID = OldTsData->Tpid;
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
	TraceNotice(m,"DataAcqInstance avilable for onid: %d, tsid: %d \n",DataAcqInstance.Onid,DataAcqInstance.Tsid  );
	if(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE), svcdat.OriginalNetworkId, svcdat.ServiceId, DataAcqInstance.Tsid, (void *)(&service)) == FALSE)
	{
		if((DataAcqInstance.Mode == Homing) && 
			(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, OTHER_TABLE), svcdat.OriginalNetworkId,svcdat.ServiceId, DataAcqInstance.Tsid, (void *)(&service)) == TRUE))
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
		TraceNotice(m,"SDT ACTUAL avilable for onid: %d, tsid: %d, svcid: %d svctype: %d \n",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId, service.ServiceType );
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
		/*Delete the duplicate service with old TPID,svcid*/
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
		tempsvcdat.Tpid = OldTsData->Tpid;
		tempsvcdat.ServiceId = ServiceList->ServiceId;
		pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		presetData.PresetNumber = tempsvcdat.PresetNumber;
		pgdb_Delete(SERVICE_TABLE, (Address )&tempsvcdat);

		/*Delete the preset table, if the service is not added with new TPID*/
		if(IsServiceAdded == FALSE)
		{
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
		}
		
	}
	return retval;
}



void CHsvDvbsN_mAcq_Priv::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
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

Bool CHsvDvbsN_mAcq_Priv::mIsSvcPresentInServiceList(HsvPgdatDigServiceData *svcdata)
{
	Bool retval = TRUE;
	
	HSVSPTYPE(ActualTSService, dvb, sdt) service_actual;
	HSVSPTYPE(OtherSDTSection, dvb, sdt) service_other;
	
	
	if (strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE),svcdata->OriginalNetworkId, svcdata->ServiceId,svcdata->Tsid, (Address)(&service_actual)) == FALSE)
	{
		if(strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, OTHER_TABLE),svcdata->OriginalNetworkId, svcdata->ServiceId,svcdata->Tsid, (Address)(&service_other)) == FALSE)
		{
		    retval = FALSE;		
		}
	}
	
	return retval;
}


void CHsvDvbsN_mAcq_Priv::mDeleteAllServicesFromCarrier(int TPID)
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
		}
	}
}

void CHsvDvbsN_mAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	if(VALID_LCN_RANGE(psvcdat->LCN))
	{		
		/* Filling update details and updating */
		mAssignSvcBroadcastAttributes(psvcdat, ptc,service);
		mAssignSvcNonBroadcastAttributes(psvcdat);
		mUpdateSatelliteName (psvcdat);

		pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
			
		TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
	}
	else
	{
		/* Need to delete this service. As LCN has changed from honored to non - honored */
		mDeleteNonhonoredServices (psvcdat);
	}
}


void CHsvDvbsN_mAcq_Priv::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
        HsvPgdatDigSatInfoData  SatInfo;

        SatInfo.LnbNumber = psvcdat->LnbNumber;

        if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
        {
                memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
        }
}


void CHsvDvbsN_mAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool IsDuplicatesvc)
{
	Nat8	ToAdd = FALSE;
	HsvPgdatPresetData			PresetData;	

	if(VALID_LCN_RANGE(psvcdat->LCN))
	{	
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
	else
	{
		TraceNotice (m, "NHD: Service Not installed dye to invalid LCN ONID %d TSID %d ServiceID %d ", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
	}
}

Bool CHsvDvbsN_mAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}

void CHsvDvbsN_mAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
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

void CHsvDvbsN_mAcq_Priv::mDeleteNonhonoredServices (HsvPgdatDigServiceData* psvcdat)
{
	HsvPgdatPresetData			presetData;		
	HsvPgdatDigServiceData		svcdat;

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	if((pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE) && IsUpdateInstall() && (svcdat.SDSDFrequency != 0))
	{
		TraceNotice (m, "NHD: UpdateInstall deleting service with preset %d ONID %d TsId %d  ServiceId %d. This moved to nonhonored ", \
								svcdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid ,svcdat.ServiceId);
		
		if (IsDigitalTvChannel (&svcdat))
		{
			removeCurTv++;
		}
		else if (IsDigitalRadioService (&svcdat))
		{
			removeCurRadio++;
		}

		/* We are in upate install. And we found some servies for which LCN have moved from honored to non-honored. 
			Delete these entries from both SERVICE TABLE and PRESET TABLE */
		presetData.PresetNumber =   svcdat.PresetNumber;						
		if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
		{
			pgdb_Delete(PRESET_TABLE, (Address)&presetData);
		}
		pgdb_Delete (SERVICE_TABLE, (Address)&svcdat);
	}
}


void CHsvDvbsN_mAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
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
	psvcdat->PackageGroup 		= POLAND_N_MATCH_SETTINGS_DB_PACKAGE_ID;
	

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
/* ANEESH: Its wrong implementation: It should be TimerClk interface
	if( clk_ClockIsSet())
	{
		psvcdat->DateStamp = clk_GetUniversalTime();
	}
	*/
}


int CHsvDvbsN_mAcq_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
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

int CHsvDvbsN_mAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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

Bool CHsvDvbsN_mAcq_Priv::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
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

Bool CHsvDvbsN_mAcq_Priv::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsN_mAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}


Bool CHsvDvbsN_mAcq_Priv::mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sdt)* service)
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

void CHsvDvbsN_mAcq_Priv::mCollectSdsds (void)
{
    int i = 0;

    mNDSDesc.NumOfSDSD = strapi_GetSize (HsvMain, GETHSVSPID(SDSD,ACTUAL_TABLE));
    for(i = 0; i < mNDSDesc.NumOfSDSD; i++)
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&(mNDSDesc.SatDesc[i]))) == FALSE)
        {
            TraceNotice (m," Collect SDSD failed for SDSD: %d \n",i);
        }
    }

    DataAcqInstance.CurSdsd = 0;
    DataAcqInstance.NumSdsds = mNDSDesc.NumOfSDSD;

    TraceNotice(m,"mCollectSdsds No of SDSD's [%d] \n",DataAcqInstance.NumSdsds);
}



Bool CHsvDvbsN_mAcq_Priv::mGetLCN(t_LCNInfo *LCNInfo)
{
	Bool retval = FALSE;
    int TableId =  ACTUAL_TABLE;

	
	retval = mLcnVersion1Data(GETHSVSPID(LCN, TableId), LCNInfo, FALSE);
 	return retval;
}


Bool CHsvDvbsN_mAcq_Priv::mAcquireLCNData(void)
{
    Bool retval = FALSE;
    int TableId =  ACTUAL_TABLE;
    t_LCNInfo LCNInfo;
	
   
   retval = mLcnVersion1Data(GETHSVSPID(LCN, TableId), &LCNInfo, TRUE);
    
    return retval;

}

Bool CHsvDvbsN_mAcq_Priv::mLcnVersion1Data(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll)
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
				
                if(mPopulateLCN((Address)(&nwlcn), VERSION) == FALSE)
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
                    nwlcn.VisibleService, VERSION);
            retval = TRUE;
        } else {
			TraceNotice(m,"strapi_GetByKey Failed for LCN \n");
        }
		
    }
	
    return retval;
}

Bool CHsvDvbsN_mAcq_Priv::mPopulateLCN(Address data, int version)
{
	int  cacheIndex = 0;
    Bool retval 	= TRUE;
	
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) *nwlcn;

  	nwlcn = (HSVSPTYPE(ActualNetworkLCN, dvb, nit) *)data;
    cacheIndex = mGetLCNIndex(nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId);

	mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwlcn->Original_NetworkId, nwlcn->Tsid, nwlcn->ServiceId, \
                    nwlcn->LogicalChannelNum, nwlcn->VisibleService, version);
    mLCNData.VersionNumber = nwlcn->VersionNumber;

	if(cacheIndex >= mLCNData.NumOfLCNRecords)
    {
   		mLCNData.NumOfLCNRecords++;
   	}
	if(mLCNData.NumOfLCNRecords == MAX_LCN_NUMBERS)
    {
        ASSERT(!"Increase the number of LCN records");
        retval = FALSE;
    }

    return retval;
}

inline void CHsvDvbsN_mAcq_Priv::mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version)
{
    LCNInfo->Onid              = OnId;
    LCNInfo->Tsid              = TsId;
    LCNInfo->ServiceId         = SvcId;
    LCNInfo->LogicalChannelNum = Lcn;
    LCNInfo->VisibleService    = VisibleSvc;
    LCNInfo->LCNType           = version;
}

void CHsvDvbsN_mAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
    t_LCNInfo LCNInfo;
    int cacheIndex = 0;

	TraceNotice(m,"mAssignLCN mLCNData.NumOfLCNRecords[%d]  \n",mLCNData.NumOfLCNRecords); 

    if(mLCNData.NumOfLCNRecords == 0)
    {
		//TraceNotice(m,"OriginalNetworkId[%d] Tsid[%d] ServiceId[%d] \n",psvcdat->OriginalNetworkId,psvcdat->Tsid,psvcdat->ServiceId);
		LCNInfo.Onid = psvcdat->OriginalNetworkId; LCNInfo.Tsid = psvcdat->Tsid; LCNInfo.ServiceId = psvcdat->ServiceId; //keys to get the LCN frm strapi records 
        if(mGetLCN(&LCNInfo) == TRUE)
        {
            psvcdat->LCN = (VALID_LCN_RANGE(LCNInfo.LogicalChannelNum) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
			/* brg36mgr&nr=243091: As per DCRS 6445:
				Visibility_flag: This flag within the NIT actual -> LCN_descriptor shall be ignored. By default all services are visible */
            psvcdat->VisibleService = TRUE; /*LCNInfo.VisibleService;*/
        }
		
    }
    else
    {
    	//TraceNotice(m,"OriginalNetworkId[%d] Tsid[%d] ServiceId[%d] \n",psvcdat->OriginalNetworkId,psvcdat->Tsid,psvcdat->ServiceId);
        cacheIndex = mGetLCNIndex(psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
        if(cacheIndex != mLCNData.NumOfLCNRecords)
        {
            psvcdat->LCN = (VALID_LCN_RANGE(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;
			/* brg36mgr&nr=243091: As per DCRS 6445:
				Visibility_flag: This flag within the NIT actual -> LCN_descriptor shall be ignored. By default all services are visible */
            psvcdat->VisibleService = TRUE; 
        }
    }
}

inline int CHsvDvbsN_mAcq_Priv::mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId)
{
    int i = 0;

	
    for( i = 0; i < mLCNData.NumOfLCNRecords; i++)
    {
        if((mLCNData.mLCNInfo[i].Onid == Onid) && (mLCNData.mLCNInfo[i].Tsid == Tsid) && (mLCNData.mLCNInfo[i].ServiceId == ServiceId))
        {
            break;
        }
    }
	//TraceNotice(m,"OriginalNetworkId[%d] Tsid[%d] ServiceId[%d] index[%d] \n",Onid,Tsid,ServiceId,i);
    return i;
}


void CHsvDvbsN_mAcq_Priv::mGetSDTOtherStatus(void)
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

void CHsvDvbsN_mAcq_Priv::mGetSatelliteLnbNo(int SatId)
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

Bool CHsvDvbsN_mAcq_Priv::IsManualInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsN_mAcq_Priv::IsUpdateInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsN_mAcq_Priv::iacqpow_Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbn_mDataAcq" );
	
	TraceNotice (m, " N Acq New N Acq Module pow Initialized \n");

}

void CHsvDvbsN_mAcq_Priv::iacqpow_TurnOn(void)
{

}

void CHsvDvbsN_mAcq_Priv::iacqpow_TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsN_mAcq_Priv::idataacq_Initialise(int LnbNumber)
{
    /* Resetting all the variables */
    mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
    removeCurTv = removeCurRadio = 0;
	memset(&mLCNData,0,sizeof(mLCNData));
	UNUSED(LnbNumber);
}

void CHsvDvbsN_mAcq_Priv::idataacq_AcquireData(int Mode)
{

	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)Mode);
}

void CHsvDvbsN_mAcq_Priv::idataacq_AcquireDataOnTimeout (void)
{
	pmp_PmpSend(mDataAcqPump, EvDeleteNonTransmittedTs, (Nat32)NULL);
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);
	
	return removeCurTv;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);
	
	return removeCurRadio;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfSdsds ()
{
	return mNDSDesc.NumOfSDSD;
}

Bool CHsvDvbsN_mAcq_Priv::idataacq_GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mNDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry, &mNDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));
		mNDSDesc.CurrentSDSDIndex = count;
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsN_mAcq_Priv::idataacq_GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);
	
	return RadioChannelsFound;
}

void CHsvDvbsN_mAcq_Priv::idataacq_SyncTemporaryTableRecords			(	void	)
{
}

void CHsvDvbsN_mAcq_Priv::idataacq_AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	//Do Nothing
}

void CHsvDvbsN_mAcq_Priv::idataacq_GetTricolorRegionNames (Nat16 **names, int *len)
{
	//Do Nothing
}

