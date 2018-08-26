/**********************************************************************
 *
 *   C Source:       hsvdvbcins_macq.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    ponraman %
 *   %date_created:  Fri Jan 18 18:27:50 2013 %
 *
 **********************************************************************/
#include "hsvdvbcins_mDataAcq.h"
//#include "hsvdvbcins_mBackground.c"


TRACESYMBOL(m, "dvb/installation/hsvdvbcins_mDataAcq")

















int CHsvDvbCInstallation_mDataAcq_Priv::s__mHsvDVBPIDList[7][7] = 
{
    /*Onid*/     { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)   },
    /*Tsid*/     { HSVSPID(ActualTsId, dvb, sdt),                 HSVSPID(OtherTsId, dvb, sdt)                },
    /*VerNo*/    { HSVSPID(ActualTsVersionNo, dvb, sdt),          HSVSPID(OtherTsVersionNo, dvb, sdt)         },
/*SpidService*/  { HSVSPID(ActualTSService, dvb, sdt),            HSVSPID(OtherSDTSection, dvb, sdt)          },
    /*LCNv1*/    { HSVSPID(ActualNetworkLCN,dvb,nit),			  HSVSPID(OtherNetworkLCN, dvb, nit)		  },
    /*LCNv2*/    { HSVSPID(ActualNetworkLCN2,dvb,nit),			  HSVSPID(OtherNetworkLCN2, dvb, nit)		  },
	/*HDSLCN*/	 { HSVSPID(ActualNetworkHDSLCN,dvb,nit),		  HSVSPID(OtherNetworkHDSLCN,dvb,nit)		  }
};


int CHsvDvbCInstallation_mDataAcq_Priv::s__mHsvDVBSortedTableList[2][2] = 
{
#if 0
    /*LCNv2*/    { srtdbids_NitLcn2TableMain,			  srtdbids_NitLcn2TableSub   },
	/*HDSLCN*/	 { srtdbids_NitHDSLcnTableMain,			  srtdbids_NitHDSLcnTableSub }	
	#endif
};


/* Static variables */
t_DVBCData CHsvDvbCInstallation_mDataAcq_Priv::s__mDVBCData;

t_LCNsData CHsvDvbCInstallation_mDataAcq_Priv::s__mLCNData;

Pump CHsvDvbCInstallation_mDataAcq_Priv::s__mAcqPump,CHsvDvbCInstallation_mDataAcq_Priv::s__mBackgroundPump;

t_CableDSDesc CHsvDvbCInstallation_mDataAcq_Priv::s__mCurrCableDS,CHsvDvbCInstallation_mDataAcq_Priv::s__mFlashCableDS;

t_ServiceList CHsvDvbCInstallation_mDataAcq_Priv::s__mSvcListData,CHsvDvbCInstallation_mDataAcq_Priv::s__mFlashSvcListData;

int CHsvDvbCInstallation_mDataAcq_Priv::s__mDigitalChannelsFound;

char CHsvDvbCInstallation_mDataAcq_Priv::s__mDirName[MAX_CHARACTERS],CHsvDvbCInstallation_mDataAcq_Priv::s__mFileName[MAX_CHARACTERS];

Bool CHsvDvbCInstallation_mDataAcq_Priv::s__mActive,CHsvDvbCInstallation_mDataAcq_Priv::s__mAcquistionInProgress,CHsvDvbCInstallation_mDataAcq_Priv::s__mSemiSbyInstallRequired,CHsvDvbCInstallation_mDataAcq_Priv::s__mVersionUpdateNeeded = TRUE;

Bool CHsvDvbCInstallation_mDataAcq_Priv::s__updateBarkerMuxDvbcins = FALSE;

int CHsvDvbCInstallation_mDataAcq_Priv::s__BackGroundCount = 0;
int CHsvDvbCInstallation_mDataAcq_Priv::s__BackGroundCountInAcq = 0;

t_SDTOtherData CHsvDvbCInstallation_mDataAcq_Priv::s__mSDTOtherVersion;

Bool CHsvDvbCInstallation_mDataAcq_Priv::s__ServiceNameUpdated = FALSE;




/* Static functions */




















































void CHsvDvbCInstallation_mDataAcq_Priv::mPumpHandler(int value, Nat32 param)
{
    TraceDebug(m,"%s: CURRENT STEP = %d",__FUNCTION__, value);

    UNUSED(param);
    switch(value)
    {
        case evStep0:
            /* Step 1: Update the service records of the current pass to SERVICE TABLE */
            mUpdateServiceTableRecords(value);
            break;
        case evStep1:
            /* Step 2: Delete Services which are not in transmission anymore */
            mDeleteServiceNotInTransmission(value);
            break;
        case evStep2:
            /* NON HONOURED PRESETS */
            mUpdatePtcTableRecords(value);
            break;
        case evStepComplete:
            /* Notification to mdig */
			mDeleteHDSimulcastSDServices();
            if(iquick_GetCurrentState() != iquick_stidle) 
            {
                iquick_SyncComplete();
            }
            else
            {
                ifull_SyncComplete();
            }
            break;
    }

}
Nat8 CHsvDvbCInstallation_mDataAcq_Priv::mGetSdtOtherVersion(int OnId,int TsId)
{
	Nat8 retval = INVALID_TS_VERSION;

	for(int i = 0; i < mSDTOtherVersion.NumOfRecords; i++)
	{
		if((OnId == mSDTOtherVersion.Version[i].Onid) && (TsId == mSDTOtherVersion.Version[i].Tsid))
		{
			retval = mSDTOtherVersion.Version[i].VersionNumber;
			break;
		}
	}

	TraceNotice(m,"mGetSdtOtherVersion TSVersion [%d] ",retval);
	
	return retval;
}
	
void CHsvDvbCInstallation_mDataAcq_Priv::mStoreSdtOtherVersion()
{
	int i = 0;
	HSVSPTYPE(OtherTSService, dvb, sdt) other_service;
	int TotalServices = strapi_GetSize (HsvMain, HSVSPID(OtherSDTSection, dvb, sdt));
	
	for(i = 0; i < TotalServices ; i++)
	{
		if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(OtherSDTSection, dvb, sdt), i, &other_service))
		{
			if(IsTSversionStored(other_service.Original_NetworkId,other_service.TsId) == FALSE)
			{
				if(mSDTOtherVersion.NumOfRecords < MAX_TS)
				{
					mSDTOtherVersion.Version[mSDTOtherVersion.NumOfRecords].VersionNumber = other_service.VersionNumber;
					mSDTOtherVersion.Version[mSDTOtherVersion.NumOfRecords].Tsid= other_service.TsId;
					mSDTOtherVersion.Version[mSDTOtherVersion.NumOfRecords].Onid= other_service.Original_NetworkId;
					mSDTOtherVersion.NumOfRecords ++;
				}
				else
				{
					TraceNotice(m,"ERROR: mSDTOtherVersion[] Overflow");
					break;
				}
			}
		}
	}
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::IsTSversionStored(int Onid,int Tsid)
{
	Bool retval = FALSE;

	for(int i = 0; i < mSDTOtherVersion.NumOfRecords; i++)
	{
		if((Onid == mSDTOtherVersion.Version[i].Onid) && (Tsid == mSDTOtherVersion.Version[i].Tsid))
		{
			retval = TRUE;
			break;
		}
	}

	return retval;
	
}




Nat8 CHsvDvbCInstallation_mDataAcq_Priv::mGetNITVersion(void)
{
    Nat8 retval = 0;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) NIDInfo;

    if(iquick_GetTargetNitType(&mDVBCData.NetworkId) == rins_NitOther)
    {
        if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), mDVBCData.NetworkId, 0, 0, (void*) (&NIDInfo)))
        {
            retval = NIDInfo.VersionNumber;
        }
    }
    else 
    {
        strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (Address)(&retval));
    }
    TraceDebug(m,"%s %d NetworkId %d VersionNumber : %d ",__FUNCTION__,__LINE__, mDVBCData.NetworkId, NIDInfo.VersionNumber);
    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mGetTSMetaData(void)
{
    Bool retval = FALSE;
    Nat16 currOnid = 0, currTsid = 0;
    int TableId = (iquick_GetSDTType() == eurdiv_SDTActual)? ACTUAL_TABLE : OTHER_TABLE;

    retval = strapi_GetByKey(HsvMain, GETHSVSPID(Onid, TableId), 0, 0, 0,&mDVBCData.Onid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(Tsid, TableId), 0, 0, 0, &mDVBCData.Tsid);
    retval = retval && strapi_GetByKey(HsvMain, GETHSVSPID(VerNo, TableId), 0, 0, 0, &mDVBCData.TsVersionNum);

    mDVBCData.NITVersion = mGetNITVersion();
    TraceDebug(m,"%s %d retval %d data : <%d, %d, %d>",__FUNCTION__, __LINE__, retval, mDVBCData.Onid, mDVBCData.Tsid, mDVBCData.TsVersionNum);

    /* Depending on installation mode and nit type correct strapi query is made */
    if( (iquick_GetCurrentState() != iquick_stidle) || BACKGROUND_INSTALL )
    {
        /* Quick Scan is in progress. So get Target NIT from quick module */
        iquick_GetTargetNitType(&mDVBCData.NetworkId);

        TraceDebug(m,"Quick Scan in progress. NID = %d",mDVBCData.NetworkId);
        if(iquick_GetCurTSValues(&currOnid, &currTsid))
        {
            if((currTsid != mDVBCData.Tsid) || (currOnid != mDVBCData.Onid))
            {
                retval = FALSE;
                /* ONID, TSID of CDSD not matching with ONID, TSID of SDT Actual in alternate freq 
                   Specifically added for Germany in case a Welho stream is played on alt freq*/
                TraceDebug(m,"From CDSD: ONID = %d, TSID = %d::From SDT: ONID = %d, TSID = %d",currOnid,currTsid, mDVBCData.Onid,mDVBCData.Tsid);
            }
        }
    }
    else
    {
        /* Full scan is in progres. So get NID value from NIT Actual */
        mDVBCData.NetworkId = 0;
        if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &(mDVBCData.NetworkId)))
        {
            TraceDebug(m,"FULL Scan in progress. NID = %d",mDVBCData.NetworkId);
        }
        else
        {
            mDVBCData.NetworkId = 1; /* just a valid value to continue installation even if NIT is not available */
        }
    }
    TraceDebug(m,"NIT Version for NID = %d is %d",mDVBCData.NetworkId,mDVBCData.NITVersion);

    if( (retval == TRUE) && (eurdiv_InstallTestStreams(CURRENT_MODE, rins_GetMedium()) == eurdiv_NotInstall) )
    {
        /* the test streams has to be installed in manual installation mode */
        retval = IS_VALID_TS | MANUAL_INSTALL;
    }

    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mInstallMux(HsvInstallationPTC *ptc)
{
    Bool retval = FALSE;
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    int TableId = (iquick_GetSDTType() == eurdiv_SDTActual)? ACTUAL_TABLE : OTHER_TABLE, i, TotalServices = 0, InstalledServices = 0;;

    TotalServices = strapi_GetSize (HsvMain, GETHSVSPID(SpidService, TableId));
    TraceDebug(m,"%s %d NoOfServices in MUX = %d",__FUNCTION__, __LINE__, TotalServices);
	memset((Address)&service, 0, sizeof(HSVSPTYPE(ActualTSService, dvb, sdt)));
    for(i = TotalServices - 1; i >= 0 ; i--)
    {
        if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId), i, (void *)(&service)) == TRUE)
        {
            if( mCheckServiceForInstall (ptc, &service) == TRUE )
            {
                InstalledServices++;
                retval = TRUE;
            }
        }
    }
    TraceNotice(m,"Installed %d services", InstalledServices);

    if(BACKGROUND_INSTALL)
    {
        mCheckPTCForBackgroundInstall(ptc, service, TotalServices);
    }

    return retval;
}
void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_UpdateBarkerMuxInfo(Nat16 onid, Nat16 tsid)
{
    HsvPgdatDigTSData   tmptsdata;
	int index, NoOfRecs = 0;
	TraceNotice(m,"idataacq_UpdateBarkerMuxInfo [%d] [%d] ",onid,tsid);
	NoOfRecs = pgdb_GetNoRecords(PTC_TABLE);
	for(index = 0; index < NoOfRecs; index++)
	{
    	if( pgdb_GetByIndex(PTC_TABLE, index, (Address )&tmptsdata)) 
    	{
			if((onid == tmptsdata.OriginalNetworkId) && (tsid == tmptsdata.Tsid))
			{
				tmptsdata.BarkerMux = TRUE;
				pgdb_Update(PTC_TABLE,&tmptsdata);
				break;
			}
		}
	}

	TraceNotice(m,"idataacq_UpdateBarkerMuxInfo [%d] [%d] ",onid,tsid);	
}
 

void CHsvDvbCInstallation_mDataAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc)
{
    HsvPgdatDigTSData   tsdata, tmptsdata;

	
	pgdb_Initialise(PTC_TABLE, (Address) &tsdata);
	pgdb_Initialise(PTC_TABLE, (Address) &tmptsdata);

    tsdata.Frequency                    = ptc->Frequency;
    tsdata.SymbolRate               = ptc->SymbolRate;
    tsdata.DecoderType              = ptc->DecoderType;     
    tsdata.OriginalNetworkId            = mDVBCData.Onid;
    tsdata.Tsid                     = mDVBCData.Tsid;
    tsdata.NetworkId                    = mDVBCData.NetworkId;
    tsdata.ModulationType           = ptc->ModulationType;
    tsdata.CodeRate                 = ptc->CodeRateHigh;
    tsdata.HierarchyMode                = ptc->HierarchyMode;
    tsdata.GuardInterval                = ptc->GuardInterval;
    tsdata.TxMode                   = ptc->TxMode;
    tsdata.IqMode                   = ptc->IqMode;
    tsdata.Bandwidth                = ptc->ChannelBandwidth;
    tsdata.StreamPriority           = ptc->StreamPriority; 
    tsdata.TimeError                    = ptc->TimeError;
    tsdata.FrequencyError           = ptc->FrequencyError;
    tsdata.FrequencyOffset          = ptc->FrequencyOffset;
    tsdata.PtcListVersion           = rins_GetInstallationVersion();
    tsdata.VSignalStrength          = ptc->VSignalStrength;
    tsdata.ASignalStrength          = ptc->ASignalStrength;
    tsdata.QSignalStrength          = ptc->QSignalStrength;
    tsdata.ChannelInformation       = ptc->ChannelInformation;
    tsdata.CDSDFrequency            = ptc->CDSDFrequency;
    tsdata.UserInstalled            = (MANUAL_INSTALL) ? TRUE : FALSE;
    tsdata.TSVersion                = mGetSdtOtherVersion(mDVBCData.Onid,mDVBCData.Tsid);/*SDT other version for UPC*/
    tsdata.SDTVersion               = mDVBCData.SDTVersion;
    tsdata.NITVersion               = (iquick_GetCurrentState() != iquick_stidle)? (ptc->NITVersion): (mDVBCData.NITVersion);

    tmptsdata.Frequency             = tsdata.Frequency;
    tmptsdata.StreamPriority        = tsdata.StreamPriority;

    if( pgdb_GetByKey((BACKGROUND_INSTALL)? PTC_TABLE: TEMP_PTC_TABLE, (Address )&tmptsdata) == FALSE ) 
    {
        if(BACKGROUND_INSTALL)
        {
            mUpdateTsBackgroundInstall();
        }
        else
        {
			TraceNotice(m,"Addition to pgdb table %s %d ", __FUNCTION__, __LINE__);
			
			pgdb_Add( TEMP_PTC_TABLE, (Address )&tsdata);
        }
    }
    else
    {
        TraceNotice(m,"Updation to pgdb table %s %d <%ld %d>", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.StreamPriority);
        pgdb_Update( (BACKGROUND_INSTALL)? PTC_TABLE: TEMP_PTC_TABLE, (Address )&tsdata);
    }
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mDuplicateEntry(HsvPgdatDigServiceData svcdat, int tableid)
{
    Bool retval = FALSE;
    int from = -1, to = -1, index = 0;
    HsvPgdatDigServiceData tempsvcdat;

    /* 2 is the number of keys */
    if(pgdb_GetRange( tableid, 2, (Address)&svcdat, &from, &to))
    {
        if((to >= 0) && (from >= 0))
        {
            for (index = from; index <= to; index++)
            {
                if(pgdb_GetByIndex( tableid, index, (Address)&tempsvcdat))
                {
                    retval = TRUE;
                    if( eurdiv_TripletKey(rins_Cable) )
                    {
                        if( ((svcdat.Tsid != tempsvcdat.Tsid) && (svcdat.Frequency != tempsvcdat.Frequency)) 
                                || (svcdat.DecoderType != tempsvcdat.DecoderType) )
                        {
                            retval = FALSE;
                        }
                    }
                }
            }
        }
    }

    TraceDebug(m,"%s service <%d %d %d %d>", retval?"Duplicate":"New", svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.Frequency);
    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCheckServiceForInstall(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    Bool retval = FALSE, channelExists = FALSE;
    HsvPgdatDigServiceData svcdat;

    if( mIsServiceInstallable(ptc, service)/*eurdiv_IsServiceInstallable(rins_Cable, service->ServiceType)*/ )
    {
        pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

        svcdat.OriginalNetworkId     = mDVBCData.Onid;
        svcdat.ServiceId             = service->ServiceId;
        svcdat.Frequency             = ptc->Frequency;
        svcdat.Tsid                  = mDVBCData.Tsid;
        svcdat.DecoderType           = feapi_ChanDecDvbC;
        svcdat.NewChannelMap         = 1;
		svcdat.StreamPriority		 = ptc->StreamPriority;
        channelExists = mDuplicateEntry(svcdat, (BACKGROUND_INSTALL)? SERVICE_TABLE : TEMP_SERVICE_TABLE);      
        if(channelExists)
        {
            //#if 0 //[HTV] duplicate channel install start
			if(sysset_GetPbsMode() == 0)
            	if(BACKGROUND_INSTALL)
            	{
					pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat);
	                mBackgroundUpdateService(&svcdat, ptc, service);
    	        }
        	    else
            	{
                	mUpdateService(&svcdat, ptc, service);
	                retval = TRUE;
    	        }
			else {
            //#else
                mAddNewService(&svcdat,ptc,service);
                mDigitalChannelsFound--;
                retval = TRUE;
            //#endif //[HTV] duplicate channel install end
			}
        }
        else
        {
            if(BACKGROUND_INSTALL)
            {
				pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat);
                mBackgroundNewService(&svcdat, ptc, service);
            }
            else
            {
                mAddNewService(&svcdat, ptc, service);
                retval = TRUE;
            }
        }
    }
    return retval;
}


void CHsvDvbCInstallation_mDataAcq_Priv::mCheckSDTOtherServiceForInstall(HsvInstallationPTC* ptc,HSVSPTYPE(ActualCableDS, dvb, nit)	*CDSD,HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    Bool retval = FALSE, channelExists = FALSE;
    HsvPgdatDigServiceData svcdat;
	

    if( mIsSDTOtherServiceInstallable(ptc, service)/*eurdiv_IsServiceInstallable(rins_Cable, service->ServiceType)*/ )
    {
        pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

        svcdat.OriginalNetworkId     = service->Original_NetworkId;
        svcdat.ServiceId             = service->ServiceId;
        svcdat.Frequency             = ptc->Frequency;
        svcdat.Tsid                  = service->TsId;
        svcdat.DecoderType           = feapi_ChanDecDvbC;
		svcdat.StreamPriority		 = ptc->StreamPriority;
        channelExists = mDuplicateEntry(svcdat, (BACKGROUND_INSTALL)? SERVICE_TABLE : TEMP_SERVICE_TABLE);      
        if(channelExists)
        {
            if(BACKGROUND_INSTALL)
            {
				pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat);
                mBackgroundUpdateService(&svcdat, ptc, service);
            }
        }
        else
        {
            if(BACKGROUND_INSTALL)
            {
                mBackgroundNewService(&svcdat, ptc, service);
            }
        }
    }
}


void CHsvDvbCInstallation_mDataAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    Bool UpdateService = TRUE;
    HsvPgdatDigServiceData svcdat;
    mAssignSvcBroadcastAttributes(psvcdat, ptc, service);

    if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC)
    {
        UpdateService = mOperatorUPCInstallRules(*psvcdat);
    }
	if((sysset_GetSystemCountry() == cids_CountryRomania) && idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_RCSRDS)
	{
		UpdateService = mOperatorRCSRDSInstallRules(*psvcdat);
	}// CR :AN-7610

	if((sysset_GetSystemCountry() == cids_CountryBulgaria) && idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_Blizoo)
	{
		UpdateService = mOperatorBlizooInstallRules(*psvcdat);
	}
	
    if(UpdateService)
    {
        mAssignSvcNonBroadcastAttributes(psvcdat);
        pgdb_Update( TEMP_SERVICE_TABLE, (Address )&psvcdat);

        TraceDebug(m,"Updated Service LCN:%d ONID:%d SVCID:%d", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
        if(BACKGROUND_INSTALL)
        {   
            sort_UpdateDigitalPreset(&svcdat);          
        }
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
    Bool InstallService = TRUE; 

    mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
    /* All Operator rules for installation of services will offcourse be based on only broadcast attributes he transmit,
       So Acquire only them before the operator speccific checks */
    if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC)
    {
        InstallService = mOperatorUPCInstallRules(*psvcdat);
    } /*CR - AN-1709*/
	
	if((sysset_GetSystemCountry() == cids_CountryRomania) && idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_RCSRDS)
	{
		InstallService = mOperatorRCSRDSInstallRules(*psvcdat);
	}// CR :AN-7610
	else if((sysset_GetSystemCountry() == cids_CountryGermany) && (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UnityMedia))
	{
		InstallService = (psvcdat->LCN == 0) ? FALSE : TRUE;
	}
	else if((sysset_GetSystemCountry() == cids_CountryBulgaria) && idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_Blizoo)
	{
		InstallService = mOperatorBlizooInstallRules(*psvcdat);
	}

    if(InstallService)
    {
        mAssignSvcNonBroadcastAttributes(psvcdat);

        if( MANUAL_INSTALL || (mDuplicateEntry(*psvcdat, SERVICE_TABLE) == FALSE) || (AUTO_INSTALL))
        {
            mDigitalChannelsFound++;
        }
        pgdb_Add( TEMP_SERVICE_TABLE, (Address )psvcdat);

        TraceDebug(m,"Added Service LCN:%d ONID:%d SVCID:%d",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
        TraceDebug(m,"SDTVersion = %ld, NITVersion = %ld",(Nat32) mDVBCData.SDTVersion,(Nat32) mDVBCData.NITVersion);

    }

    TraceDebug(m,"Added Service LCN:%d ONID:%d SVCID:%d",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbCInstallation_mDataAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
    HsvPATProgramPIDInfo val;
	HsvChannel Channelinfo;
	HsvPgdatDigServiceData  svcdat;

    psvcdat->NetworkId             =   mDVBCData.NetworkId;
    psvcdat->ModulationType        =   ptc->ModulationType;
    psvcdat->Bandwidth      =   ptc->ChannelBandwidth;
    psvcdat->StreamPriority        =   ptc->StreamPriority ;    
    psvcdat->SymbolRate            =   ptc->SymbolRate;
    psvcdat->DecoderType           =   feapi_ChanDecDvbC;
    psvcdat->ServiceType           =   mConvertToPgdatServiceType(service->ServiceType);
    psvcdat->Type                  =   GETSERVICETYPE(service->ServiceType);
    psvcdat->FreeCiMode            =   service->Free_Ci_Mode;
    psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
    psvcdat->NumBrandIds           =   service->NumBrandIds;
    psvcdat->DvbType               =   AppApiDvbTypeC;
    psvcdat->AudioPid              =   INVALID_PID;
    psvcdat->VideoPid              =   INVALID_PID;
    psvcdat->PcrPid                =   INVALID_PID;
    psvcdat->LCN                   =   INVALID_LCN;
    psvcdat->OUI                   =   HsvOUI_Last;

    if(service->Free_CA_Mode == TRUE)
    {
        psvcdat->SrcambledStatus = 1;
		psvcdat->ScramblingStatus =   1;
    }
	mAssignSvcHDSimulcastLinkageParams(psvcdat);

    mAssignLCN(psvcdat);
    psvcdat->NumericSelect     =   ( (psvcdat->LCN == ZEROLCN) && eurdiv_IsZeroLCNHidden() )? FALSE: TRUE;

    if( (eurdiv_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(psvcdat->ServiceType))) ||
            (eurdiv_InstallTestStreams(CURRENT_MODE,rins_GetMedium()) == eurdiv_Hide) )
    {
        psvcdat->SystemHidden = TRUE;
    }
    else                
    {
        psvcdat->SystemHidden = !(psvcdat->VisibleService);
    }
    if ( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) )
    {
        psvcdat->PmtPid            =   val.Pid;
    }
    mDVBCData.SDTVersion           = service->VersionNumber;
    mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds );
    if(service->ServiceName[0] == 0)
    {
        mCopyString( psvcdat->ChannelName, instutil_AsciiToUnicode("-----", 10), 10);
    }
    else
    {
        mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_ChannelNameLength - 1));
    }
	
	if(BACKGROUND_INSTALL)
	{
		ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
        
        if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
		{
			/* For Channellib notifications to be generated */
			Channelinfo.Ptc = svcdat.PresetNumber; 
			Channelinfo.Channel.OnePart = svcdat.PresetNumber;                  
			Channelinfo.Type = GETSERVICETYPE(svcdat.ServiceType);
	    
		    if (psvcdat->SrcambledStatus != svcdat.SrcambledStatus)
		    {
		        pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSrcambledStatus, (Bool)psvcdat->SrcambledStatus);
		    }
			if (psvcdat->ScramblingStatus != svcdat.ScramblingStatus)
		    {
		        pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSrcambledStatus, (Bool)psvcdat->ScramblingStatus);
		    }
		}
	}
}

void CHsvDvbCInstallation_mDataAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
    HsvPgdatDigServiceData svcdat;

    psvcdat->UserHidden             = FALSE;
    psvcdat->ChannelLock            = FALSE;
    //psvcdat->SystemHidden         = FALSE;    
    psvcdat->Favorite               = FALSE;
    psvcdat->PreferredStereo        = 1;
    psvcdat->DateStamp              = 0;
    psvcdat->PresetNumber           = INVALID_PRESET;
    psvcdat->ServiceListVersion     = rins_GetInstallationVersion();
    psvcdat->NewPreset              = !AUTO_INSTALL;
    psvcdat->HbbTvOption        = 1;

    ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
    {
        psvcdat->NewPreset = svcdat.NewPreset;
        /* Naresh: Retain the non broadcast attributes during background install */
        psvcdat->PresetNumber           = (BACKGROUND_INSTALL)? svcdat.PresetNumber : psvcdat->PresetNumber;
        psvcdat->EPGEnabled             = svcdat.EPGEnabled;
        psvcdat->ChannelLock            = svcdat.ChannelLock;;
        psvcdat->UserHidden             = svcdat.UserHidden;
        psvcdat->Favorite               = svcdat.Favorite;
        psvcdat->FavoriteNumber         = svcdat.FavoriteNumber;
        psvcdat->ServiceListVersion     = svcdat.ServiceListVersion;
        psvcdat->HbbTvOption            = svcdat.HbbTvOption;
        psvcdat->EPGShortInfo           = svcdat.EPGShortInfo;
        psvcdat->SAP                    = svcdat.SAP;
        psvcdat->DeltaVolume            = svcdat.DeltaVolume;
        psvcdat->UserModifiedName             = svcdat.UserModifiedName;
        psvcdat->PreferredStereo        = svcdat.PreferredStereo;
        psvcdat->HMBlanked              = svcdat.HMBlanked;
        psvcdat->HMProtectedChannel     = svcdat.HMProtectedChannel ;
        psvcdat->HMMapChannelNo         = svcdat.HMMapChannelNo;
        psvcdat->LogoURL                = svcdat.LogoURL;
        psvcdat->VideoPid              =  svcdat.VideoPid;              
        psvcdat->AudioPid              =  svcdat.AudioPid;
        psvcdat->PcrPid                =  svcdat.PcrPid;    
        psvcdat->VideoStreamType       =  svcdat.VideoStreamType;
        psvcdat->AudioStreamType       =  svcdat.AudioStreamType;
        psvcdat->SecAudioStreamType    =  svcdat.SecAudioStreamType;
        psvcdat->SecAudioPid           =  svcdat.SecAudioPid;
	 memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
    }

    if( Timerclk_IsClockDefined() && !MANUAL_INSTALL )
    {
        psvcdat->DateStamp = Timerclk_GetUniversalTime();
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mUpdateServiceTableRecords(int evCurrentStep)
{
    Bool ProceedUpdate = TRUE, PreviousServiceDeleted = FALSE;
    int indx = 0, noOfRecs = pgdb_GetNoRecords(TEMP_SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat, svcdat_temp;
    HsvPgdatDigTSData tsdat;
    HsvPgdatPresetData presetdat;

    svcdat.NewChannelMap = 1;
    /* Step 1: Update the service records of the current pass to SERVICE TABLE */
    for(indx = 0; indx < noOfRecs; indx++)
    {
        if( pgdb_GetByIndex(TEMP_SERVICE_TABLE, indx, (Address)&svcdat_temp) == TRUE )
        {
            ASSIGN_KEYS_OF_SVC(svcdat, svcdat_temp);
            ProceedUpdate = pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat);
            //#if 0 //[HTV] duplicate channel install start
			if(sysset_GetPbsMode() == 0)
			{
            	if(ProceedUpdate == FALSE)
	            {
    	            TraceDebug(m,"%s %d", __FUNCTION__,  __LINE__);
        	        PreviousServiceDeleted = mDeleteDuplicateRecords(&svcdat_temp);
            	}
			}
            //#endif //[HTV] duplicate channel install end
            
            if(ProceedUpdate)
            {
                tsdat.Frequency        =   svcdat.Frequency;
                tsdat.StreamPriority   =   svcdat.StreamPriority;
                if( pgdb_GetByKey( PTC_TABLE, (Address) &tsdat) == TRUE)
                {
                    TraceDebug(m,"%s %d", __FUNCTION__,  __LINE__);
                    //if( IS_NOT_USER_INSTALLED(tsdat) ) // No need to check as we have to update LCNS for Manually installed Presets also during Update installation
                    {
                        REVALIDATE(svcdat.LCN); //this is required because we would have invalidated LCN in previous pass due to conflicts if any
                        if( (VALID_LCN_RANGE(svcdat.LCN) || VALID_LCN_RANGE(svcdat_temp.LCN) || (VALID_LCN_RANGE_RCSRDS(svcdat.LCN) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS)) || (VALID_LCN_RANGE_RCSRDS(svcdat_temp.LCN) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS))) &&
                                (svcdat.LCN != svcdat_temp.LCN) )
                        {
                            if(eurdiv_UpdateLCN(rins_GetMedium()))
                            {
                                /* below done, because the LCN changes presets are sorted freshly as per design of ItaSort */
                                TraceNotice(m,"%s %d deleted preset becoz => psvcdat->LCN %d svcdat_temp.LCN %d svcdat.PresetNumber %d", __FUNCTION__, __LINE__, svcdat.LCN, svcdat_temp.LCN, svcdat.PresetNumber);
                                presetdat.PresetNumber =   svcdat.PresetNumber;
                                presetdat.Type         =   HsvOnePart;
                                pgdb_Delete(PRESET_TABLE,(Address)&presetdat);

                                svcdat.PresetNumber = INVALID_PRESET;
                            }
                            else
                            {
                                TraceNotice(m,"svcdat.LCN %d svcdat_temp.LCN %d LCN changed but could not be updated as due to user re-arranged presets", svcdat.LCN, svcdat_temp.LCN);
                            }
                        }
                        mCopySvcBroadcastAttributes(&svcdat, svcdat_temp);
                        pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
						if(MANUAL_INSTALL)
						{
							/*This is required to update FirstInstalledPreset in sort module*/
							sort_UpdateDigitalPreset(&svcdat);
						}
                    }
                }
            }
            else
            {
                /* new record Add to SERVICE TABLE */
                pgdb_Add(SERVICE_TABLE, (Address)&svcdat_temp);
                /* below is required as we have to update preset table when any of the keys of service table
                   entry is changed */
                if(PreviousServiceDeleted)
                {
                    sort_UpdateDigitalPreset(&svcdat_temp);
                }
            }
        }
    }
    pmp_PmpSend(mAcqPump, (evCurrentStep + 1), (Nat32)NULL);
}

void CHsvDvbCInstallation_mDataAcq_Priv::mDeleteServiceNotInTransmission(int evCurrentStep)
{
    int indx = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigTSData tsdat;

    for(indx = 0; indx < noOfRecs; indx++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, indx, (Address)&svcdat) == TRUE )
        {
            tsdat.Frequency        =   svcdat.Frequency;
            tsdat.StreamPriority   =   svcdat.StreamPriority;
            if( pgdb_GetByKey( TEMP_PTC_TABLE, (Address) &tsdat) == TRUE)
            {
                /* Dont remove UserInstalled presets */
                if( IS_NOT_USER_INSTALLED(tsdat) )
                {
                    /* delete record from SERVICE TABLE */
                    if( pgdb_GetByKey(TEMP_SERVICE_TABLE, (Address)&svcdat) == FALSE )
                    {
                        /* This means MUX is present but the service is removed from that MUX by broadcaster */
                        presetdat.PresetNumber =   svcdat.PresetNumber;
                        presetdat.Type         =   HsvOnePart;
                        pgdb_Delete(PRESET_TABLE,(Address)&presetdat);

                        pgdb_Delete(SERVICE_TABLE,(Address) &svcdat);
                        sortN_OnEvent(sortN_EventChannelRemoved, rins_GetInstallationMode());

                        TraceDebug(m," @ %d Ntf EventChannelRemoved sent for Preset %d, ServiceId:%d ", __LINE__, svcdat.PresetNumber, svcdat.ServiceId);
                        indx--;
                        noOfRecs--;
                    }
					else
						{
						TraceNotice(m,"Service Preset in TEMP_SERVICE_TABLE");
						}
                }
            }
        }
    }

    pmp_PmpSend(mAcqPump, (evCurrentStep + 1), (Nat32)NULL);
}

void CHsvDvbCInstallation_mDataAcq_Priv::mUpdatePtcTableRecords(int evCurrentStep)
{
    int indx = 0, noOfRecs = pgdb_GetNoRecords(TEMP_PTC_TABLE);
    HsvPgdatDigTSData tsdata;
    HsvPgdatDigTSData tsdata_temp;

    /* Step 1: Update the PTC records of the current pass to PTC TABLE */
    for(indx = 0; indx < noOfRecs; indx++)
    {
        if( pgdb_GetByIndex(TEMP_PTC_TABLE, indx, (Address)&tsdata_temp) == TRUE )
        {
            tsdata.Frequency        =   tsdata_temp.Frequency;
            tsdata.StreamPriority   =   tsdata_temp.StreamPriority;
            if( pgdb_GetByKey(PTC_TABLE, (Address)&tsdata) == TRUE )
            {
                if( IS_NOT_USER_INSTALLED(tsdata) )
                {
                    mCopyPtcBroadcastAttributes(&tsdata, tsdata_temp);
                    pgdb_Update(PTC_TABLE, (Address)&tsdata);
                }
            }
            else
            {
                /* new record Add to PTC TABLE */
                pgdb_Add(PTC_TABLE, (Address)&tsdata_temp);
            }
        }
    }

    pmp_PmpSend(mAcqPump, (evCurrentStep + 1), (Nat32)NULL);
}

void CHsvDvbCInstallation_mDataAcq_Priv::mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp)
{
    /* No need to copy Primary keys again, copy rest of them */
    psvcdat->NetworkId             =    svcdat_temp.NetworkId;
    psvcdat->ModulationType        =    svcdat_temp.ModulationType;
    psvcdat->Bandwidth			   =    svcdat_temp.Bandwidth;
    psvcdat->Tsid                  =    svcdat_temp.Tsid;
    psvcdat->LCN                   =    svcdat_temp.LCN;
    psvcdat->LowPrioLCN            =    svcdat_temp.LowPrioLCN;
    psvcdat->LowPrioVisibleService =    svcdat_temp.LowPrioVisibleService;
    psvcdat->VisibleService        =    svcdat_temp.VisibleService;
    psvcdat->NumericSelect         =    svcdat_temp.NumericSelect;
    psvcdat->ServiceType           =    svcdat_temp.ServiceType;
    psvcdat->Type                  =    svcdat_temp.Type;
    psvcdat->FreeCiMode            =    svcdat_temp.FreeCiMode;
    psvcdat->MatchBrandFlag        =    svcdat_temp.MatchBrandFlag;
    psvcdat->NumBrandIds           =    svcdat_temp.NumBrandIds;
    psvcdat->SystemHidden          =    svcdat_temp.SystemHidden;
    psvcdat->NewPreset             =    svcdat_temp.NewPreset;
    psvcdat->ServiceListVersion    =    svcdat_temp.ServiceListVersion; 
    psvcdat->VideoPid              =    svcdat_temp.VideoPid;               
    psvcdat->AudioPid              =    svcdat_temp.AudioPid;
    psvcdat->PcrPid                =    svcdat_temp.PcrPid; 
    psvcdat->VideoStreamType       =    svcdat_temp.VideoStreamType;
    psvcdat->AudioStreamType       =    svcdat_temp.AudioStreamType;
    psvcdat->SecAudioStreamType    =    svcdat_temp.SecAudioStreamType;
    psvcdat->SecAudioPid           =    svcdat_temp.SecAudioPid;
	psvcdat->SrcambledStatus	   =	svcdat_temp.SrcambledStatus;
	psvcdat->ScramblingStatus	   =	svcdat_temp.ScramblingStatus;
	psvcdat->HDSimulcastRepOnId	   =    svcdat_temp.HDSimulcastRepOnId;
	psvcdat->HDSimulcastRepTsId    =    svcdat_temp.HDSimulcastRepTsId;
	psvcdat->HDSimulcastRepSvcId   =    svcdat_temp.HDSimulcastRepSvcId;
    mCopyString( psvcdat->BrandIds, svcdat_temp.BrandIds, svcdat_temp.NumBrandIds );

    if(psvcdat->UserModifiedName == FALSE)
    {
        /* This means user has not renamed the service, so we can update the one sent by broadcaster */
        mCopyString( psvcdat->ChannelName, svcdat_temp.ChannelName, (eurdiv_PresetNameLength - 1));
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp)
{
    tsdata->Frequency            =   tsdata_temp.Frequency;
    tsdata->ModulationType       =   tsdata_temp.ModulationType;               
    tsdata->HierarchyMode        =   tsdata_temp.HierarchyMode;
    tsdata->GuardInterval        =   tsdata_temp.GuardInterval;
    tsdata->TxMode               =   tsdata_temp.TxMode;
    tsdata->IqMode               =   tsdata_temp.IqMode;
    tsdata->Bandwidth            =   tsdata_temp.Bandwidth;
    tsdata->StreamPriority       =   tsdata_temp.StreamPriority;   
    tsdata->TimeError            =   tsdata_temp.TimeError;
    tsdata->FrequencyError       =   tsdata_temp.FrequencyError;
    tsdata->FrequencyOffset      =   tsdata_temp.FrequencyOffset;
    tsdata->VSignalStrength      =   tsdata_temp.VSignalStrength;
    tsdata->ASignalStrength      =   tsdata_temp.ASignalStrength;
    tsdata->QSignalStrength      =   tsdata_temp.QSignalStrength;
    tsdata->ChannelInformation   =   tsdata_temp.ChannelInformation; 
    tsdata->DecoderType          =   tsdata_temp.DecoderType;
    tsdata->SymbolRate           =   tsdata_temp.SymbolRate; 
    tsdata->OriginalNetworkId    =   tsdata_temp.OriginalNetworkId;
    tsdata->Tsid                 =   tsdata_temp.Tsid;
    tsdata->NetworkId            =   tsdata_temp.NetworkId;
    tsdata->TSVersion            =   tsdata_temp.TSVersion;
    tsdata->PtcListVersion       =   tsdata_temp.PtcListVersion;
    tsdata->CodeRate             =   tsdata_temp.CodeRate;
    tsdata->NITVersion           =   tsdata_temp.NITVersion; 

    tsdata->UserInstalled        =   tsdata_temp.UserInstalled;
}

void CHsvDvbCInstallation_mDataAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; (i < maxchars) && (*src); i++)
    {
        *dest++ = *src++;
    }
    *dest = 0;
}

int CHsvDvbCInstallation_mDataAcq_Priv::mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId)
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

Bool CHsvDvbCInstallation_mDataAcq_Priv::mOperatorUPCInstallRules(HsvPgdatDigServiceData svcdat)
{
    Bool retval = FALSE;

    /* Rule 1. Valid LCNs */
    if( (svcdat.LCN > 0) && (svcdat.LCN != INVALID_LCN) )  //CR 174719
    {
        retval = TRUE;
    }
    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mOperatorRCSRDSInstallRules(HsvPgdatDigServiceData svcdat)
{
    Bool retval = FALSE;

    /* Rule 1. Valid LCNs */
    if( (svcdat.LCN > 0) && (svcdat.LCN != INVALID_LCN) )  //CR 7610
    {
        retval = TRUE;
    }
    return retval;
}


Bool CHsvDvbCInstallation_mDataAcq_Priv::mOperatorBlizooInstallRules(HsvPgdatDigServiceData svcdat)
{
    Bool retval = TRUE;

    /* Rules. Not Hidden and Not ZERO LCN */
     if( ((svcdat.SystemHidden == TRUE) || (svcdat.LCN == ZEROLCN)) && (rins_QuickScan == idvbset_GetAttribute(AUTO_MODE, rins_AttributeScanMode)) ) 
    {
        retval = FALSE;
    }
    return retval;
}

/* static function impl.. */
int CHsvDvbCInstallation_mDataAcq_Priv::mConvertToDVBServiceType(int servicetype)
{
    int retval = servicetype;
    switch(servicetype)
    {
        case AppApiTelevisionService:     
            retval  =   TV_SERVICE;
            break;
        case AppApiRadioService:        
            retval  =   RADIO_SERVICE;
            break;
        case AppApiTeletextService:         
            retval  =   TELETEXT_SERVICE;
            break;
        case AppApiNVODReferenceService:         
            retval  =   NVOD_REFERENCE_SERVICE;
            break;
        case AppApiNVODTimeshiftedService:         
            retval  =   NVOD_TIMESHIFTED_SERVICE;
            break;
        case AppApiMosaicService:        
            retval  =   MOSAIC_SERVICE;
            break;
        case AppApiDatabroadcastService:        
            retval  =   DATABROADCAST_SERVICE;
            break;
        case AppApiDVBMHPService:        
            retval  =   DVBMHP_SERVICE;
            break;
        case AppApiMPEG2HDService:        
            retval  =   MPEG2HDService;
            break;
        case AppApiAdvCodecSDTelevisionService:        
            retval  =   AdvCodecSDTelevisionService;
            break;
        case AppApiAdvCodecSDNVODTimeShiftedService:        
            retval  =   AdvCodecSDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecSDNVODReferenceService:        
            retval  =   AdvCodecSDNVODReferenceService;
            break;
        case AppApiAdvCodecHDTelevisionService:        
            retval  =   AdvCodecHDTelevisionService;
            break;
        case AppApiAdvCodecHDNVODTimeShiftedService:        
            retval  =   AdvCodecHDNVODTimeShiftedService;
            break;
	case AppApiAdvCodecHDNVODReferenceService:        
	    retval  =   AdvCodecHDNVODReferenceService;
	    break;
	case AppApi3DHDDigitalService:
	    retval  =   HD3DDigitalService;
	    break;
	case AdvCodecRadioService:	
	    retval  = AppApiAdvCodecRadioService;
	    break;
        default:
            break;
    }
    return retval;
}

int CHsvDvbCInstallation_mDataAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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
	    retval  = AppApiAdvCodecRadioService;
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
		case HD3DDigitalService:
			retval  =   AppApi3DHDDigitalService;
			break;
        default:
            break;
    }
    return retval;
}

/********************************
  provides IHsvPower iacqpow
 ********************************/

void CHsvDvbCInstallation_mDataAcq_Priv::iacqpow_Init()
{
    mAcqPump = pmp_PmpCreateEx(pen_PumpEngine, mPumpHandler, TRUE, "hsvdvbcins_mDataAcq_pmp");
    mBackgroundOnInit();
	mVersionUpdateNeeded = TRUE;
}

void CHsvDvbCInstallation_mDataAcq_Priv::iacqpow_TurnOn()
{
    mLoadCableDS();
    mLoadSLD();
}

void CHsvDvbCInstallation_mDataAcq_Priv::iacqpow_TurnOff()
{
}
/**********************************************
  provides IHsvDigitalAcquisition  idigacq
 **********************************************/

 
void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_Initialise()
{
    mLCNData.NumOfLCNRecords = 0;
    mDVBCData.Onid = mDVBCData.Tsid = mDVBCData.NetworkId;
	mSDTOtherVersion.NumOfRecords = 0;
    mBackgroundInitialise();
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_InitialiseTotalChannels()
{
	mDigitalChannelsFound = 0;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_AcquireData()
{
    /* Call Back once Data collection is completed by SDM */
    HsvInstallationPTC    ptc;
    HsvPgdatDigTSData     tsdata;

    Bool retval = mGetTSMetaData();

    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    if(retval == TRUE)
    {
        mGetPTCInfo(&ptc);      
        mAddToFreqMapTable(ptc);

        tsdata.Frequency      = ptc.Frequency;
        tsdata.StreamPriority = ptc.StreamPriority;

        TraceNotice(m,"%s %d svcdat.Frequency %ld", __FUNCTION__, __LINE__, ptc.Frequency);
        if(mInstallMux(&ptc) == TRUE )
        {
            /* Add entry to TS Table */
            mAddToTSTable(&ptc);
        }
        if(BACKGROUND_INSTALL)
        {
            mCheckNITForBackgroundInstall(ptc);
			if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC)
			{
				mCheckAllPTCForBackgroundInstall();
			}			
        }
		if(CURRENT_MODE == BACKGROUND_MODE )
        {
            mDeleteHDSimulcastSDServices();
        }
    }
    else
    {
        TraceDebug(m,"PTC Ignored: Invalid PTC or Incomplete Data");
    }

	mVersionUpdateNeeded = FALSE;
}

int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
    return mDigitalChannelsFound;
}
int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}
int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannels(int servicetype)
{
    UNUSED(servicetype);
    return mDigitalChannelsFound;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_AcquireONID()
{
    /* do nothing */
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_AcquireLCNData()
{
    t_LCNInfo LCNInfo;
    /* Naresh: below is overloaded function, the param is used for other purpose and not here */
    mGetLCNData(&LCNInfo, ACQUIRE_LCNS);
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_AcquireServiceListData()
{
    mAcquireServiceListData();
    mWriteSLDToFlash();
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_AcquireSDTOtherData()
{
	mStoreSdtOtherVersion();
}


void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_SyncTemporaryTableRecords(void)
{
    TraceNotice(m,"%s %d mAcqPump %d", __FUNCTION__, __LINE__, mAcqPump);
	if(AUTO_INSTALL)
	{
		pgdb_ClearTable(PTC_TABLE);
		pgdb_ClearTable(SERVICE_TABLE);
		pgdb_ClearTable(PRESET_TABLE);
		/* During installation directly FREQMAP table is populated. Dont clear it */
	}
    pmp_PmpSend(mAcqPump, evStep0, (Nat32)NULL);
}

void CHsvDvbCInstallation_mDataAcq_Priv::mAcquireServiceListData(void)
{
    Nat16 NetworkId;
    HSVSPTYPE(ActualServiceList, dvb, nit) svcList;
    int hsvspid, i = 0, numOfEntries = 0, NitType = iquick_GetTargetNitType(&NetworkId);

    TraceDebug(m,"%s %d Acquiring Svc List from NIT %s", __FUNCTION__, __LINE__, (NitType == eurdiv_NitActual)? "Actual":"Other");
    hsvspid = (NitType == eurdiv_NitActual)? HSVSPID(ActualServiceList, dvb, nit):HSVSPID(OtherServiceList, dvb, nit);

    numOfEntries = strapi_GetSize(HsvMain, hsvspid);
    TraceDebug(m,"%s %d Num of SvcList Desc = %d", __FUNCTION__, __LINE__, numOfEntries);

    mSvcListData.NumOfRecords = 0;

    for(i = 0 ; i < numOfEntries; i++)
    {
        if(strapi_GetByIndex(HsvMain, hsvspid, i, (void*)(&svcList)))
        {
            mSvcListData.mSvcListInfo[i].Onid = svcList.Original_NetworkId;
            mSvcListData.mSvcListInfo[i].Tsid = svcList.Tsid;
            mSvcListData.mSvcListInfo[i].ServiceId = svcList.ServiceId;
            mSvcListData.NumOfRecords++;

            // No real use as of now
            mSvcListData.VersionNumber = svcList.VersionNumber;
            //TraceDebug(m,"SvcList Desc ONID = %d, Tsid = %d, SvcId = %d",mSvcListData.mSvcListInfo[i].Onid,mSvcListData.mSvcListInfo[i].Tsid, mSvcListData.mSvcListInfo[i].ServiceId);
        }
        else
        {
            TraceDebug(m,"strapi fail for SvcList");
        }
    }
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mLcnVersion1Data(Nat16 NetworkId, int HsvPid, t_LCNInfo *LCNInfo, int ActionOnData)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HsvPid);
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) nwlcn;

    if( ActionOnData == ACQUIRE_LCNS )
    {
        for(i = 0; i < numOfRecords; i++)
        {
            if( (strapi_GetByIndex(HsvMain, HsvPid, i, (Address)(&nwlcn)) == TRUE) )
            {
                /* Take only those LCNs which are matching with Target NIT */
                if(nwlcn.NetworkId == NetworkId)
                {
                    retval = TRUE;
                    if(mPopulateLCN((Address)(&nwlcn), VERSION1) == FALSE)
                    {
                        break;
                    }
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

Bool CHsvDvbCInstallation_mDataAcq_Priv::mHdsLcnData(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HsvPid);
    HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) nwhdslcn;
    if(eurdiv_SupportHDSLCN(rins_GetMedium()) && (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) != rins_UPC))
    {
        if( ActionOnData == ACQUIRE_LCNS )
        {
            for(i = 0; i < numOfRecords; i++)
            {
                if(srtdb_QueryOnIndex(DBTableId, i, (Address)(&nwhdslcn)))
                {
                    /* Take only those LCNs which are matching with Target NIT */
                    if(nwhdslcn.NetworkId == NetworkId)
                    {
                        retval = TRUE;
                        if(mPopulateLCN((Address)(&nwhdslcn), HDSLCNVERSION) == FALSE)
                        {
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if( (strapi_GetByKey(HsvMain, HsvPid, LCNInfo->Onid, LCNInfo->Tsid, LCNInfo->ServiceId, &nwhdslcn) == TRUE) )
            {
                mCopyLCNInfo( LCNInfo, nwhdslcn.Original_NetworkId, nwhdslcn.Tsid, nwhdslcn.ServiceId, nwhdslcn.LogicalChannelNum, \
                        nwhdslcn.VisibleService, HDSLCNVERSION);
                retval = TRUE;
            }
        }
    }
    return retval;  
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mLcnVersion2Data(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData)
{
    Bool retval = FALSE; 
    HsvDestination dest = HsvMain;
    int NoOfRecs, i, channellistid, from, to, countrycode = 0;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    NoOfRecs = strapi_GetSize(HsvMain, HsvPid);
	TraceNotice(m,"LCNV2: No Of Records: %d", NoOfRecs);
    if( (LCN_VERSION2_PRESENT(NoOfRecs) )&&(eurdiv_SupportLCNVersion2(rins_GetMedium())) )
    {
        mGetInterestedLCNRecords(HsvPid, DBTableId, &from, &to, &countrycode);
        channellistid = mGetInterestedChanneListId(HsvPid, from, to, &countrycode);

//        if(TRUE == srtdb_SearchOnPrimaryAndSecondaryKey(DBTableId, countrycode, channellistid, &from, &to)) 
	    if(strapi_GetRangeByKey(dest,HsvPid,2 ,countrycode ,channellistid ,0 , &from, &to) == TRUE)
        {
        	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
            for(i = from; i <= to; i++)
            {
//				if( (srtdb_QueryOnIndex(DBTableId, i, (Address)&nwlcn) == TRUE) )
				if( strapi_GetByIndex(dest,HsvPid, i, (Address)&nwlcn) == TRUE )
                {
       	        	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
                    if( ActionOnData == ACQUIRE_LCNS )
                    {
                        /* Take only those LCNs which are matching with Target NIT */
                        if(nwlcn.NetworkId == NetworkId)
                        {
                            retval = TRUE;
                            if(mPopulateLCN((Address)(&nwlcn), VERSION2) == FALSE)
                            {
                                break;
                            }
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
	TraceNotice(m,"%s %d retval %d",__FUNCTION__,__LINE__,retval);
    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mPopulateLCN(Address data, int version)
{
    int cacheIndex = 0;
    Bool retval = TRUE;
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) *nwlcn;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) *nwlcn2;
    HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) *nwhdslcn;


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
                //TraceDebug(m,"Acquire LCN: SvcId = %d, LCN = %d", nwlcn->ServiceId, nwlcn->LogicalChannelNum);
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
                //TraceDebug(m,"%s:%d:Acquire LCN: SvcId = %d, LCN = %d\n", __FUNCTION__,__LINE__,nwlcn2->ServiceId, nwlcn2->LogicalChannelNum);
            }
            else
            {
                /* This case is to access the right index from the list of records*/
                mCopyLCNInfo( &(mLCNData.mLCNInfo[cacheIndex]), nwlcn2->Original_NetworkId, nwlcn2->Tsid, nwlcn2->ServiceId, \
                        nwlcn2->LogicalChannelNum, nwlcn2->VisibleService, version);

                //TraceDebug(m,"%s:%d:Acquire LCN: SvcId = %d, LCN = %d\n", __FUNCTION__,__LINE__,nwlcn2->ServiceId, nwlcn2->LogicalChannelNum);
            }
            break;
        case HDSLCNVERSION:
            nwhdslcn = (HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) *)data;
            cacheIndex = mGetLCNIndex(nwhdslcn->Original_NetworkId, nwhdslcn->Tsid, nwhdslcn->ServiceId);

            mLCNData.VersionNumber = nwhdslcn->VersionNumber;

            TraceNotice(m,"%s:%d:cacheIndex=%d:mLCNData.NumOfLCNRecords=%d",__FUNCTION__,__LINE__,cacheIndex,mLCNData.NumOfLCNRecords);
            if(cacheIndex >= mLCNData.NumOfLCNRecords)
            {
                mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwhdslcn->Original_NetworkId, nwhdslcn->Tsid, nwhdslcn->ServiceId, \
                        nwhdslcn->LogicalChannelNum, nwhdslcn->VisibleService, version);
                mLCNData.NumOfLCNRecords++;
                //TraceDebug(m,"%s:%d:Acquire LCN: SvcId = %d, LCN = %d\n", __FUNCTION__,__LINE__, nwhdslcn->ServiceId, nwhdslcn->LogicalChannelNum);
            }
            else
            {
                /* This case is to access the right index from the list of records*/
                mCopyLCNInfo( &(mLCNData.mLCNInfo[cacheIndex]), nwhdslcn->Original_NetworkId, nwhdslcn->Tsid, nwhdslcn->ServiceId, \
                        nwhdslcn->LogicalChannelNum, nwhdslcn->VisibleService, version);
                //TraceDebug(m,"%s:%d:Acquire LCN: SvcId = %d, LCN = %d\n", __FUNCTION__,__LINE__, nwhdslcn->ServiceId, nwhdslcn->LogicalChannelNum);
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

void CHsvDvbCInstallation_mDataAcq_Priv::mGetInterestedLCNRecords(int HsvPid, int DBTableId, int *from, int *to, int *countrycode)
{
    HsvDestination dest = HsvMain;
    *countrycode = sysset_GetSystemCountry();
//	if(srtdb_SearchOnPrimaryKey(DBTableId, *countrycode, from, to) == FALSE)
	if(strapi_GetRangeByKey(dest,HsvPid,1 ,*countrycode ,0 ,0 , from, to) == FALSE)
    {
        *from = 0, *to = strapi_GetSize(HsvMain, HsvPid);
    }
}

int CHsvDvbCInstallation_mDataAcq_Priv::mGetInterestedChanneListId(int HsvPid, int from, int to, int *countrycode)
{
    int i, channellistid;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    strapi_GetByIndex(HsvMain, HsvPid, from, (void*)(&nwlcn));
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
    return channellistid;
}

inline void CHsvDvbCInstallation_mDataAcq_Priv::mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version)
{
    LCNInfo->Onid              = OnId;
    LCNInfo->Tsid              = TsId;
    LCNInfo->ServiceId         = SvcId;
    LCNInfo->LogicalChannelNum = Lcn;
    LCNInfo->VisibleService    = VisibleSvc;
    LCNInfo->LCNType           = version;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mGetLCNData(t_LCNInfo *LCNInfo, int ActionOnData)
{ 
    Bool retval = FALSE;
    Nat16 NetworkId = 0;
    int NitType = (rins_FullScan == idvbset_GetAttribute(AUTO_MODE, rins_AttributeScanMode))? eurdiv_NitActual: iquick_GetTargetNitType(&NetworkId);
    int TableId = ((NitType == eurdiv_NitActual) || (MANUAL_INSTALL))? ACTUAL_TABLE : OTHER_TABLE;

    TraceDebug(m,"Target NetworkId of NIT %s = %d", (TableId == ACTUAL_TABLE)?"Actual":"Other", NetworkId);

    retval = mLcnVersion2Data(NetworkId, GETHSVSPID(LCNv2, TableId), GETDBTABLEID(0, TableId), LCNInfo, ActionOnData);
    if(retval == FALSE)
    {
        TraceDebug(m,"No LCN v2 present hence fall back to LCN v1");
        retval = mLcnVersion1Data(NetworkId, GETHSVSPID(LCNv1, TableId), LCNInfo, ActionOnData);
    }

    retval |= mHdsLcnData(NetworkId, GETHSVSPID(HDSLCN, TableId), GETDBTABLEID(1, TableId), LCNInfo, ActionOnData);

	if(AUTO_INSTALL)
	{
		idvbset_SetAttribute(AUTO_MODE, rins_AttributeLCNSorting, retval);
	}
    return retval;
}

void CHsvDvbCInstallation_mDataAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
    t_LCNInfo LCNInfo;
    int cacheIndex = 0;

    if( LCNS_REQUIRED )
    {
        if(mLCNData.NumOfLCNRecords == 0)
        {
            LCNInfo.Onid = psvcdat->OriginalNetworkId; LCNInfo.Tsid = psvcdat->Tsid; LCNInfo.ServiceId = psvcdat->ServiceId; //keys to get the LCN frm strapi records 
            if(mGetLCNData(&LCNInfo, GET_LCN) == TRUE)
            {
				if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC)
				{
					psvcdat->LCN = mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum;
				}
				else if((sysset_GetSystemCountry() == cids_CountryGermany) && (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UnityMedia))
				{
					psvcdat->LCN = (VALID_LCN_RANGE_UNITY(LCNInfo.LogicalChannelNum) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;					
				}
				else if((sysset_GetSystemCountry() == cids_CountryBulgaria) && idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_Blizoo)
				{
                	psvcdat->LCN = (VALID_LCN_RANGE_BLIZOO(LCNInfo.LogicalChannelNum) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
				}
				else
				{
                	psvcdat->LCN = ((VALID_LCN_RANGE(LCNInfo.LogicalChannelNum)||(VALID_LCN_RANGE_RCSRDS(LCNInfo.LogicalChannelNum) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS))) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
				}
                psvcdat->VisibleService = ( (psvcdat->LCN == ZEROLCN) && eurdiv_IsZeroLCNHidden() )? FALSE: LCNInfo.VisibleService;
                TraceDebug(m," %s %d LCN %d <%d, %d, %d>", __FUNCTION__, __LINE__, psvcdat->LCN, mDVBCData.Onid, mDVBCData.Tsid, psvcdat->ServiceId);
            }
        }
        else
        {
            /* Assign from Target NIT */
            cacheIndex = mGetLCNIndex(psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
            if(cacheIndex != mLCNData.NumOfLCNRecords)
            {
				if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC)
				{
					psvcdat->LCN = mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum;
				}
				else if((sysset_GetSystemCountry() == cids_CountryGermany) && (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UnityMedia))
				{
					psvcdat->LCN = (VALID_LCN_RANGE_UNITY(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;					
				}
				else if((sysset_GetSystemCountry() == cids_CountryBulgaria) && idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_Blizoo)
				{
					psvcdat->LCN = (VALID_LCN_RANGE_BLIZOO(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum)  == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;				
				}
				else
				{
                	psvcdat->LCN = ((VALID_LCN_RANGE(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) || (VALID_LCN_RANGE_RCSRDS(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS))) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;
				}
                psvcdat->VisibleService = ( (psvcdat->LCN == ZEROLCN) && eurdiv_IsZeroLCNHidden() )? FALSE: mLCNData.mLCNInfo[cacheIndex].VisibleService;
                TraceDebug(m," %s %d LCN %d <%d, %d, %d>", __FUNCTION__, __LINE__, psvcdat->LCN, mDVBCData.Onid, mDVBCData.Tsid, psvcdat->ServiceId);
            }
        }
    }   
} 

void CHsvDvbCInstallation_mDataAcq_Priv::mGetPTCInfo(HsvInstallationPTC *ptc)
{
    if(iquick_GetCurrentState() != iquick_stidle)
    {
        iquick_GetPTCInfo(ptc);
    }
    else if(igrid_GetCurrentState() != igrid_stidle)
    {
        igrid_GetPTCInfo(ptc);
    }
    else
    {
        ifull_GetPTCInfo(ptc);
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mAddToFreqMapTable(HsvInstallationPTC ptc)
{
    /* write to freqmaptable */
    HsvPgdatDigFreqMapData    freqdat;
    HsvPgdatDigFreqMapData    tmpfreqdat;
    Bool retval;

    freqdat.OriginalNetworkId   = mDVBCData.Onid;
    freqdat.Tsid                = mDVBCData.Tsid;
    freqdat.Frequency           = ptc.Frequency;
    freqdat.ModulationType      = ptc.ModulationType;
    freqdat.SymbolRate          = ptc.SymbolRate;
    freqdat.DecoderType         = ptc.DecoderType;

    tmpfreqdat.OriginalNetworkId    = freqdat.OriginalNetworkId;
    tmpfreqdat.Tsid                 = freqdat.Tsid;

    if(pgdb_GetByKey(FREQMAP_TABLE, (Address )&tmpfreqdat))
    {
        retval = pgdb_Update(FREQMAP_TABLE, (Address )&freqdat);
        TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    }
    else
    {
        retval = pgdb_Add( FREQMAP_TABLE, (Address )&freqdat);
        TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    }
}
void CHsvDvbCInstallation_mDataAcq_Priv::mAssignSvcHDSimulcastLinkageParams( HsvPgdatDigServiceData *svcdat )
{
	HsvLinkageInfo		sdtlinkage;
    HsvDestination dest = HsvMain;
    if( (svcdat->ServiceType == AppApiTelevisionService) && (TRUE == strapi_GetByKey(dest, HSVSPID(LinkageInfo, dvb, sdt), (int )svcdat->OriginalNetworkId, (int )svcdat->ServiceId, HDSimulcastNORDIG, (Address )&sdtlinkage) ) )
    {
        TraceDebug(m, "HDSimulcast: sdtlinkage.LinkageType = %02x ",sdtlinkage.LinkageType);
        TraceDebug(m, "HDSimulCast: Updating Service HDSimulcast LinkageType: [%04x|%04x|%04x] ",
                sdtlinkage.Original_NetworkId, sdtlinkage.Tsid, sdtlinkage.ServiceId);
        svcdat->HDSimulcastRepOnId  = sdtlinkage.Original_NetworkId;
        svcdat->HDSimulcastRepTsId  = sdtlinkage.Tsid;
        svcdat->HDSimulcastRepSvcId = sdtlinkage.ServiceId;
    }
}
void CHsvDvbCInstallation_mDataAcq_Priv::mDeleteHDSimulcastSDServices(void)
{
    HsvPgdatDigServiceData  svcdat_temp,svcdat,qry_svcdat;
    HsvPgdatPresetData presetdat;
    int index       = -1, srvindex    = -1, from,to,max,min;
    if ( eurdiv_IsHDSimulcastSupported() == TRUE )
    {
        max = pgdb_GetNoRecords(SERVICE_TABLE);
        min = 0;
        TraceDebug(m, "HDSimulCast: Into %s ", __FUNCTION__);
        for (index = min; index <=max; index++)
        {	
        	TraceDebug(m, "SERVICE_TABLE= %d ",SERVICE_TABLE);
            if(pgdb_GetByIndex( SERVICE_TABLE, index,(Address)&svcdat))
            { 
            	TraceDebug(m, "ServiceType= %d ",svcdat.ServiceType);
				TraceDebug(m, " HD_SIMULCAST_LINKAGE= %d ",HD_SIMULCAST_LINKAGE(svcdat));
                if( (svcdat.ServiceType == TelevisionService)  && HD_SIMULCAST_LINKAGE(svcdat) )
                {
                    TraceDebug(m, "HDSimulCast: Service [%04x|%04x|%04x|%02d] ",  svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,svcdat.ServiceType );
                    TraceDebug(m, "HDSimulCast: is Linked to [%04x|%04x|%04x] ",svcdat.HDSimulcastRepOnId,svcdat.HDSimulcastRepTsId,svcdat.HDSimulcastRepSvcId);
                    svcdat_temp.OriginalNetworkId = svcdat.HDSimulcastRepOnId;
                    svcdat_temp.ServiceId = svcdat.HDSimulcastRepSvcId;
                    if(pgdb_GetRange(SERVICE_TABLE, 2, (Address)&svcdat_temp, &from, &to))
                    {
                        ASSERT(from<=to);
                        for(srvindex=from; srvindex<=to; srvindex++)
                        {
                            if( pgdb_GetByIndex(SERVICE_TABLE, srvindex, (Address)&qry_svcdat) )
                            {
                                if(svcdat.HDSimulcastRepTsId == qry_svcdat.Tsid)
                                {
                                    TraceDebug(m,"HDSimulCast: Replacement Service Found.. Checking if its HD");
                                    if(qry_svcdat.ServiceType == AppApiAdvCodecHDTelevisionService )
                                    {
                                        TraceDebug(m, "HDSimulCast: Service to be deleted svcdat.PresetNumber %d", svcdat.PresetNumber);
                                        if(svcdat.PresetNumber != INVALID_PRESET)
                                        {
											TraceNotice(m,"HDSimulcast: Deleting Preset %d",svcdat.PresetNumber);
                                            presetdat.PresetNumber = svcdat.PresetNumber;
                                            presetdat.Type = HsvOnePart;
                                            pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
                                            if(CURRENT_MODE == UPDATE_MODE)
											{
											TraceDebug(m, "we are not decrementing mDigitalChannelsFound[%d]",mDigitalChannelsFound);
											}
											else{
                                            mDigitalChannelsFound--;
											}
                                            TraceDebug(m, "HDSimulCast: Raising Channel Removed Event");
                                            sortN_OnEvent(sortN_EventChannelRemoved, rins_GetInstallationMode());
                                        }
                                        else
                                        {
                                           	if(CURRENT_MODE == UPDATE_MODE)
											{
											TraceDebug(m, "we are not decrementing mDigitalChannelsFound[%d]",mDigitalChannelsFound);
											}
											else{
                                            mDigitalChannelsFound--;
											}
                                            TraceDebug(m, "HDSimulCast: Digital Channels Found =%d",mDigitalChannelsFound );
                                        }
										TraceNotice(m,"HDSimulcast: Deleting Service %d",svcdat.ServiceId);
                                        pgdb_Delete(SERVICE_TABLE,(Address)&svcdat);srvindex--;to--;index--;max--;
                                        break;
                                    }
                                }
                            }       
                        }               
                    }                   
                }
            }
        }
    }
} 
Bool CHsvDvbCInstallation_mDataAcq_Priv::mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat)
{
    Bool retval = FALSE;
    HsvPgdatDigServiceData svcdat2;
    int j, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);

    for(j = 0; j < noOfRecs; j++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, j, (Address)&svcdat2) == TRUE )
        {
            /* check for triplet key & decoder type */
            if( (svcdat->OriginalNetworkId == svcdat2.OriginalNetworkId)    &&
                    (svcdat->ServiceId         == svcdat2.ServiceId)            &&
                    (svcdat->Tsid              == svcdat2.Tsid)                 &&
                    (svcdat->DecoderType       == svcdat2.DecoderType)
              )
            {
                /* Retain Preset Number of the old service */
                pgdb_Delete(SERVICE_TABLE,(Address) &svcdat2);
                /* do not generate sortN notification, user need not be aware of the key changes of a service*/

                svcdat->PresetNumber        = svcdat2.PresetNumber;
                svcdat->NewPreset           = svcdat2.NewPreset;
                svcdat->PresetNumber        = svcdat2.PresetNumber;
                svcdat->EPGEnabled          = svcdat2.EPGEnabled;
                svcdat->ChannelLock         = svcdat2.ChannelLock;
                svcdat->UserHidden          = svcdat2.UserHidden;
                svcdat->Favorite            = svcdat2.Favorite;
				svcdat->FavoriteNumber		= svcdat2.FavoriteNumber;
                svcdat->ServiceListVersion  = svcdat2.ServiceListVersion;
                svcdat->HbbTvOption         = svcdat2.HbbTvOption;
                svcdat->EPGShortInfo        = svcdat2.EPGShortInfo;

                retval = TRUE;
                TraceDebug(m,"service deleted Preset %d, ServiceId:%d svcdat2.ChannelLock %d", svcdat->PresetNumber, svcdat->ServiceId, svcdat2.ChannelLock);
            }
        }
    }
    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    Bool lRetVal = TRUE;
    HsvPgdatDigServiceData lsvcdat;
    int FreeCAMode = DVBC_INVALID_FREECA_MODE;

    lsvcdat.OriginalNetworkId = mDVBCData.Onid;
    lsvcdat.ServiceId = service->ServiceId;
    lsvcdat.Frequency = ptc->Frequency;
    lsvcdat.StreamPriority = ptc->StreamPriority;
    lsvcdat.Tsid = mDVBCData.Tsid;
    lsvcdat.DecoderType = feapi_ChanDecDvbC;

    FreeCAMode = idvbset_GetAttribute(AUTO_MODE, rins_AttributeScrOrFTA);
    TraceNotice(m,"FREECAMODE=%d",FreeCAMode);
    if(FreeCAMode == FALSE)
    {
        TraceNotice(m,"Function:%s::Line %d",__FUNCTION__,__LINE__);
        if(((int)service->Free_CA_Mode != FreeCAMode))
        {
            lRetVal = FALSE;
            TraceNotice(m,"Function:%s::Line %d",__FUNCTION__,__LINE__);
            if((!AUTO_INSTALL) && (pgdb_GetByKey(SERVICE_TABLE, (Address )&lsvcdat) == TRUE))
            {
                if(PRESET_ALLOCATED(lsvcdat.PresetNumber)) //already present
                {
                    TraceNotice(m,"ALREADY Present in List Function:%s::Line %d",__FUNCTION__,__LINE__);
                    lRetVal = TRUE;
                }
            }
        }

    }
    TraceNotice(m,"FUNCTION=%s:Line=%d::FREECA MODE Of Service=%d::ServiceID=%x",__FUNCTION__,__LINE__,service->Free_CA_Mode,service->ServiceId);
    lRetVal = lRetVal && eurdiv_IsServiceInstallable( rins_Cable, service->ServiceType); 

    return lRetVal;

}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mIsSDTOtherServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(OtherTSService, dvb, sdt)* service)
{
    Bool lRetVal = TRUE;
    HsvPgdatDigServiceData lsvcdat;
    int FreeCAMode = DVBC_INVALID_FREECA_MODE;

    lsvcdat.OriginalNetworkId = service->Original_NetworkId;
    lsvcdat.ServiceId = service->ServiceId;
    lsvcdat.Frequency = ptc->Frequency;
    lsvcdat.StreamPriority = ptc->StreamPriority;
    lsvcdat.Tsid = service->TsId;
    lsvcdat.DecoderType = feapi_ChanDecDvbC;

    FreeCAMode = idvbset_GetAttribute(AUTO_MODE, rins_AttributeScrOrFTA);
    TraceNotice(m,"FREECAMODE=%d",FreeCAMode);
    if(FreeCAMode == FALSE)
    {
        TraceNotice(m,"Function:%s::Line %d",__FUNCTION__,__LINE__);
        if(((int)service->Free_CA_Mode != FreeCAMode))
        {
            lRetVal = FALSE;
            TraceNotice(m,"Function:%s::Line %d",__FUNCTION__,__LINE__);
            if((!AUTO_INSTALL) && (pgdb_GetByKey(SERVICE_TABLE, (Address )&lsvcdat) == TRUE))
            {
                if(PRESET_ALLOCATED(lsvcdat.PresetNumber)) //already present
                {
                    TraceNotice(m,"ALREADY Present in List Function:%s::Line %d",__FUNCTION__,__LINE__);
                    lRetVal = TRUE;
                }
            }
        }

    }
    TraceNotice(m,"FUNCTION=%s:Line=%d::FREECA MODE Of Service=%d::ServiceID=%x",__FUNCTION__,__LINE__,service->Free_CA_Mode,service->ServiceId);
    lRetVal = lRetVal && eurdiv_IsServiceInstallable( rins_Cable, service->ServiceType); 

    return lRetVal;

}






/*   hsvdvbcins_mBackground.c*/



void CHsvDvbCInstallation_mDataAcq_Priv::mBackgroundPumpHandler(int event, Nat32 param )
{
    UNUSED(param);
	
    if((EvStart == event) && (param == BackGroundCount))
    {
        if(BACKGROUND_INSTALL && (mAcquistionInProgress == FALSE) && mActive)
        {
            mStartBackgroundInstall();
        }
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mBackgroundOnInit(void)
{
    mBackgroundPump = pmp_PmpCreateEx(pen_PumpEngine, mBackgroundPumpHandler, TRUE, "hsvdvbcins_mbackground");
    mBackgroundInitialise();
}

void CHsvDvbCInstallation_mDataAcq_Priv::mBackgroundInitialise(void)
{
    mActive = mAcquistionInProgress = FALSE;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_Enable(void)
{
    mActive = eurdiv_IsBackgroundInstallRequired(rins_Cable);
	BackGroundCount++;

}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_Disable(void)
{
    mActive = FALSE;
	BackGroundCount++;
}

void CHsvDvbCInstallation_mDataAcq_Priv::mStartBackgroundInstall(void)
{
    if(BACKGROUND_INSTALL)
    {
        TraceDebug(m,"Background Trigger Done");
        mAcquistionInProgress = TRUE;
		/*  This is added, since on InstallationCompleted, SyncTVProvider will be done and then logo association.
			In DVBC background only channel name can be changed. Other changes will be happening via the Standby update */
		ServiceNameUpdated = FALSE;
		BackGroundCountInAcq = BackGroundCount;
        idataacq_AcquireData();
        mAcquistionInProgress = FALSE;
		if (ServiceNameUpdated == TRUE)
		{
			installN_OnEvent(installN_EventInstallationStarted, CURRENT_MODE);
			installN_OnEvent(installN_EventInstallationCompleted, CURRENT_MODE);
		}

        insN_OnEvent((mSemiSbyInstallRequired)?insN_EventNetworkUpdateDetected:insN_EventNetworkUpdateNotDetected, CURRENT_MODE);
    }
    TraceNotice(m,"Background update required = %s",(mSemiSbyInstallRequired)?"TRUE":"FALSE");
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::idataacq_IsNetworkUpdateDetected()
{
    TraceNotice(m,"NetworkUpdateDetected = %s",(mSemiSbyInstallRequired)?"TRUE":"FALSE");
    return mSemiSbyInstallRequired;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_ResetBackgroundInstall()
{
    TraceDebug(m,"%s %d",__FUNCTION__, __LINE__);

    mSemiSbyInstallRequired = FALSE;

    /* New set of CDSDs should be loaded to mFlashCableDS variable. Cant wait till TurnOn for loading this Data.
       So load it everytime installation is complete */
    mLoadCableDS();
    mLoadSLD();
}

/***************************************
  provides IHsvStreamNotify iqstrapiN
 ****************************************/
void CHsvDvbCInstallation_mDataAcq_Priv::iacqstrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    Nat16 NID = 0;
    Bool UpdateInstallReq = FALSE;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) NIDInfo;

    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);

    if(mActive)
    {
        switch(spid)
        {
            case HSVSPID(ActualCableDS, dvb, nit):
                if(iquick_GetTargetNitType(&NID) == rins_NitActual)
            {
                if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, (void*) (&NIDInfo)))
                {
                    if(NID == NIDInfo.NetworkId)
                    {
                        UpdateInstallReq = TRUE;
                    }
                }
            }
                break;
            case HSVSPID(OtherCableDS, dvb, nit):
                if(iquick_GetTargetNitType(&NID) == rins_NitOther)
            {
                if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), key3, 0, 0, (void*) (&NIDInfo)))
                {
                    if(NID == NIDInfo.NetworkId)
                    {
                        UpdateInstallReq = TRUE;
                    }
                }
            }
                break;
            case HSVSPID(ActualTSService, dvb, sdt):
				//TraceNotice(m,"strapiN-Onchanged for SDT Actual");
                UpdateInstallReq = TRUE;
                break;
			case HSVSPID(OtherTSService, dvb, sdt):
				//TraceNotice(m,"strapiN-Onchanged for SDT other");
				UpdateInstallReq = TRUE;
				break;
            default:
                break;
        }
        if(UpdateInstallReq)
        {
            if((mAcquistionInProgress == FALSE) && BACKGROUND_INSTALL && (rins_GetMedium() == rins_Cable))
            {
                pmp_PmpSendAfter(mBackgroundPump, EvStart, (Nat32)BackGroundCount, BACKGROUND_TIMEOUT);
            }
        }
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::iacqstrapiN_OnChanged( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(eventid);
    iacqstrapiN_OnAdded( dest, spid, key1, key2, key3);
}

void CHsvDvbCInstallation_mDataAcq_Priv::iacqstrapiN_OnCompleted( HsvDestination dest, int spid)
{
    iacqstrapiN_OnAdded( dest, spid, 0, 0, 0);

}

void CHsvDvbCInstallation_mDataAcq_Priv::iacqstrapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbCInstallation_mDataAcq_Priv::mGetPathName(char* dirName, char* FileName , char* PathName)
{
    if(str_strlen(dirName))
    {
        if(str_strlen(FileName))
        {
            str_strcpy(PathName, dirName);
            str_strcat(PathName,FileName);
        }
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mLoadCableDS(void)
{
    /* Read all CableDS from flash and update it in RAM */
    FILE* fp;
    int readrec = 0;

/*
    ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
    
	str_strcat(mDirName, "/channellib/");
	if(str_strlen(mDirName))
    {
		    
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
  */

	str_strcpy (mDirName, "/user_setting/rw/tvserver/databases/channellib/");
	
    mGetPathName(mDirName, CABLE_DEL_FILEPATH, mFileName);
    TraceDebug(m,"Fopen of %s\r", mFileName);

    fp = fopen(mFileName, "rb");

    if(fp)
    {
        readrec = fread((Address)(&mFlashCableDS), sizeof(mFlashCableDS), 1, fp);
        if(readrec)
        {
            TraceDebug(m,"Read Cable Del Sys from Flash\r");
        }
        else
        {
            mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
            TraceDebug(m,"Read Cable Del Sys from Flash Fail\r");
        }
        fclose(fp);
    }
    else
    {
        mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
        TraceDebug(m,"Unable to open %s\r",mFileName);

    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mLoadSLD(void)
{
    /* Read ServiceList Desc. content from flash and update it in RAM */
    FILE* fp;
    int readrec = 0;
    static char FileName[MAX_CHARACTERS];
    /*
    ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
	str_strcat(mDirName, "/channellib/");
    if(str_strlen(mDirName))
    {
        
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
	*/
    
	str_strcpy(mDirName, "/user_setting/rw/tvserver/databases/channellib/");
	
    mGetPathName(mDirName, SVC_LIST_DESC_FILEPATH, FileName);
    TraceDebug(m,"Fopen of %s\r", FileName);

    fp = fopen(FileName, "rb");

    if(fp)
    {
        readrec = fread((Address)(&mFlashSvcListData), sizeof(mFlashSvcListData), 1, fp);
        if(readrec)
        {
            TraceDebug(m,"Read SLD from Flash\r");
        }
        else
        {
            mFlashSvcListData.VersionNumber = INVALID_VERSION;
            mFlashSvcListData.NumOfRecords = 0;
            TraceDebug(m,"Read SLD from Flash Fail\r");
        }
        fclose(fp);
    }
    else
    {
        mFlashSvcListData.VersionNumber = INVALID_VERSION;
        mFlashSvcListData.NumOfRecords = 0;
        TraceDebug(m,"Unable to open %s\r",FileName);

    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mCheckPTCForBackgroundInstall(HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) Service, int TotalServices) 
{
    int i, svcIndex = 0;
    HsvPgdatDigTSData tsdat;
    Bool servicePresent = TRUE;
    HsvPgdatDigServiceData svcdat;
    HSVSPTYPE(ActualTSService, dvb, sdt) service;

    if(mSemiSbyInstallRequired == FALSE)
    {
        tsdat.Frequency = ptc->Frequency;
        tsdat.StreamPriority = ptc->StreamPriority;

        if(TRUE == pgdb_GetByKey( PTC_TABLE, (Address )&tsdat))
        {
            if(tsdat.SDTVersion != Service.VersionNumber)
            {
                TraceDebug(m,"SDT Old Version = %ld, New Version = %d ",(Nat32)tsdat.SDTVersion, Service.VersionNumber);
                /* Here check if the same service is still present in current ptc. Else service removed */
                for(svcIndex = 0; svcIndex < pgdb_GetNoRecords(SERVICE_TABLE); svcIndex++)
                {
                    if( pgdb_GetByIndex( SERVICE_TABLE, svcIndex, (Address)&svcdat) )
                    {
                        if(svcdat.Frequency == tsdat.Frequency)
                        {
                            Bool found = FALSE;
                            TraceDebug(m,"Frequency match in Service = %d\r",svcdat.Frequency);
                            for(i = TotalServices - 1; i >= 0 ; i--)
                            {
                                int TableId = (iquick_GetSDTType() == eurdiv_SDTActual)? ACTUAL_TABLE : OTHER_TABLE;
                                if(strapi_GetByIndex(HsvMain, GETHSVSPID(SpidService, TableId), i, (void *)(&service)))
                                {
                                    if((svcdat.OriginalNetworkId == service.Original_NetworkId) && \
                                            (svcdat.ServiceId == service.ServiceId))
                                    {
                                        found = TRUE;
                                        break;
                                    }
                                }
                            }
                            if(!found)
                            {
                                servicePresent = FALSE;
                                TraceDebug(m,"%s::SvcId = %d, Freq = %ld removed\r",__FUNCTION__,svcdat.ServiceId, tsdat.Frequency);
                            }
                        }
                    }
                    if(!servicePresent)
                    {
                        if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) != rins_Ziggo)
                        {
                            mSemiSbyInstallRequired = TRUE;
                            TraceDebug(m," %s %d Network update detected:: Services Removed", __FUNCTION__, __LINE__);
                            break;
                        }
                    }
                }
            }
        }
    }
}


void CHsvDvbCInstallation_mDataAcq_Priv::mCheckAllPTCForBackgroundInstall() 
{
    int NumOfTS = 0, index = 0, svcIndex = 0, from = 0, to = 0, i = 0, TotalServices = 0, db_from = 0, db_to = 0;
    HsvPgdatDigTSData tsdat;
    Bool UpdateDetected = FALSE;
    HsvPgdatDigServiceData svcdat;
    HSVSPTYPE(OtherTSService, dvb, sdt) service;


	NumOfTS = pgdb_GetNoRecords(PTC_TABLE);

	for(index = 0; index < NumOfTS; index++)
	{
		if(TRUE == pgdb_GetByIndex(PTC_TABLE,index,&tsdat))
		{
			/*get SDT other record for this TS*/
			if(strapi_GetRangeByKey(HsvMain,HSVSPID(OtherSDTSection, dvb, sdt),2,tsdat.OriginalNetworkId,tsdat.Tsid,0,&from,&to))
			{
				if(strapi_GetByIndex(HsvMain,HSVSPID(OtherSDTSection, dvb, sdt),from, &service) == TRUE)
				{
					if(tsdat.TSVersion != service.VersionNumber)
					{
						TraceNotice(m,"Version mismatch for tsid: %d, oldversion: %d, newversion: %d",tsdat.Tsid,tsdat.TSVersion,service.VersionNumber);
						/*Check for addition and update the service names*/
						mCheckSDTOtherForBackgroundInstall(tsdat.OriginalNetworkId,tsdat.Tsid);
					
						/*If there is no service addition, check for deletion*/
						if(mSemiSbyInstallRequired == FALSE)
						{
							svcdat.OriginalNetworkId = tsdat.OriginalNetworkId;
							db_from = 0; db_to = 0;
							if(pgdb_GetRange(SERVICE_TABLE,1,(Address)&svcdat,&db_from,&db_to))
							{
								for(svcIndex = db_from; svcIndex <= db_to; svcIndex++)
								{
									if( pgdb_GetByIndex( SERVICE_TABLE, svcIndex, (Address)&svcdat) )
									{
										if(svcdat.Frequency == tsdat.Frequency)
										{
											TraceDebug(m,"Frequency match in Service = %d [%d] [%d] [%d]\r",svcdat.Frequency,svcdat.OriginalNetworkId,svcdat.Tsid,svcdat.ServiceId);
											if(strapi_GetByKey(HsvMain,HSVSPID(OtherSDTSection, dvb, sdt),svcdat.OriginalNetworkId,svcdat.Tsid,svcdat.ServiceId,(void *)(&service)) == FALSE)
											{
												/* ANEESH: UPCIGNORE */
												if (mIgnoreUPCBackgroundNetworkUpdate() == FALSE)
												{
													mSemiSbyInstallRequired = TRUE;
													TraceDebug(m," %s %d Network update detected:: Services Removed", __FUNCTION__, __LINE__);
													TraceDebug(m,"%s::SvcId = %d, Freq = %ld removed\r",__FUNCTION__,svcdat.ServiceId, tsdat.Frequency);													
												}
												else
												{
													TraceDebug(m," %s %d Network update detected:: Services Removed. Ignoring as its in transition", __FUNCTION__, __LINE__);
													TraceDebug(m,"%s::SvcId = %d, Freq = %ld removed\r",__FUNCTION__,svcdat.ServiceId, tsdat.Frequency);																										
												}
												break;
											}
										}
									}
								}
							}
						}
						/*Update the TS Table with new version,Move to next TS*/
						tsdat.TSVersion = service.VersionNumber;
						pgdb_Update(PTC_TABLE,(Address)&tsdat);
					}
#if 0
					else if(tsdat.TSVersion == INVALID_TS_VERSION)
					{
						/*Update the TS Table with valid version,Move to next TS*/
						TraceNotice(m,"Invalid TS version updated with valid version: %d ",service.VersionNumber);
						tsdat.TSVersion = service.VersionNumber;
						pgdb_Update(PTC_TABLE,(Address)&tsdat);
					}
#endif

				}
			}
			else
			{
				TraceDebug(m,"%s: %d: No SDT other available for TS: onid: %d, tsid: %d",__FUNCTION__,__LINE__,tsdat.OriginalNetworkId,tsdat.Tsid);
			}
		}
	}
}


Bool CHsvDvbCInstallation_mDataAcq_Priv::mCheckForHDSimulcastLinkageUpdate(HsvPgdatDigServiceData* svcdat )
{
    Bool retval =FALSE;
	HsvLinkageInfo		sdtlinkage;
    HsvDestination dest = HsvMain;
    if( (svcdat->ServiceType == AppApiTelevisionService) && (TRUE == strapi_GetByKey(dest, HSVSPID(LinkageInfo, dvb, sdt), (int )svcdat->OriginalNetworkId, (int )svcdat->ServiceId, HDSimulcastNORDIG, (Address )&sdtlinkage) ) )
    {
        TraceDebug(m, "HDSimulcastLinkageUpdate: sdtlinkage.LinkageType = %02x ",sdtlinkage.LinkageType);
        TraceDebug(m, "HDSimulcastLinkageUpdate: Service HDSimulcast LinkageType: [%04x|%04x|%04x] ",sdtlinkage.Original_NetworkId, 
			       sdtlinkage.Tsid, sdtlinkage.ServiceId);
		
		if((sdtlinkage.Original_NetworkId, sdtlinkage.Tsid, sdtlinkage.ServiceId)||(svcdat->HDSimulcastRepOnId  != sdtlinkage.Original_NetworkId)||
		   (svcdat->HDSimulcastRepTsId  != sdtlinkage.Tsid)||(svcdat->HDSimulcastRepSvcId != sdtlinkage.ServiceId)){
			TraceDebug(m,"%s::We have HDSimulcastLinkageUpdate detected so set N/w flag true",__FUNCTION__);
			retval=TRUE;
			}
	}
	return retval;
}

void CHsvDvbCInstallation_mDataAcq_Priv::mBackgroundUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    if(BACKGROUND_INSTALL)
    {
        if(mActive)
        {
            if(mCheckForLCNUpdate(psvcdat, ptc, service) == TRUE)
            {
                TraceDebug(m,"%s::We have to update a service. Network update detected",__FUNCTION__);
                mSemiSbyInstallRequired = TRUE;
            }
			else if((mCheckForHDSimulcastLinkageUpdate(psvcdat) == TRUE) && ((sysset_GetSystemCountry() == cids_CountryFinland)||
				   (sysset_GetSystemCountry() == cids_CountrySweden)||(sysset_GetSystemCountry() == cids_CountryDenmark)||
				   (sysset_GetSystemCountry() == cids_CountryNorway))){
                TraceDebug(m,"%s::We have to detected HDSimulcastLinkageUpdate so it should be part of N/w update ->RMCR-44 ",__FUNCTION__);
                mSemiSbyInstallRequired = TRUE;
			}
            else
            {
                TraceDebug(m,"No Change in LCN");
            }
            mUpdateServiceName(psvcdat, service);
        }
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mBackgroundNewService(HsvPgdatDigServiceData* svcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    t_LCNInfo LCNInfo;
    HsvPgdatDigTSData tsdat;
	Bool RetVal = FALSE;

    UNUSED(ptc);
    if(mActive)
    {
        if((idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC) && (rins_FullScan != idvbset_GetAttribute(AUTO_MODE, rins_AttributeScanMode)) || (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_Blizoo))
        {
            svcdat->LCN = INVALID_LCN;
            tsdat.Frequency = svcdat->Frequency;
            tsdat.StreamPriority = svcdat->StreamPriority;
            if(TRUE == pgdb_GetByKey(PTC_TABLE, (Address )&tsdat)) 
            {
                if( /*mVersionUpdateNeeded || ((tsdat.NITVersion != mGetNITVersion()) && */(mGetNITVersion() != INVALID_NITVERSION) )
                {
                    TraceDebug(m,"NIT Old Version = %ld, New Version = %d ",(Nat32)tsdat.NITVersion, mGetNITVersion());

                    LCNInfo.Onid = svcdat->OriginalNetworkId; LCNInfo.Tsid = svcdat->Tsid; LCNInfo.ServiceId = svcdat->ServiceId; //keys to get the LCN frm strapi records 
                    if(mGetLCNData(&LCNInfo, GET_LCN) == TRUE)
                    {
                        svcdat->LCN     = ((VALID_LCN_RANGE(LCNInfo.LogicalChannelNum) || (VALID_LCN_RANGE_RCSRDS(LCNInfo.LogicalChannelNum) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS))) == TRUE)? LCNInfo.LogicalChannelNum: svcdat->LCN;
                        TraceDebug(m," %s %d LCN %d <%d, %d, %d>", __FUNCTION__, __LINE__, svcdat->LCN, mDVBCData.Onid, mDVBCData.Tsid, service->ServiceId);
                    }
					if(idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC)
					{
						RetVal = mOperatorUPCInstallRules(*svcdat);
					}
					else
					{
						RetVal = mOperatorBlizooInstallRules(*svcdat);
					}
					if(RetVal)
					{
						if(mDuplicateEntry(*svcdat, SERVICE_TABLE) == FALSE)
						{
							TraceDebug(m,"%s::We have to add a new service. Network update detected in ziggo/upc\r",__FUNCTION__);
							mSemiSbyInstallRequired = TRUE;
						}
						else
						{
							TraceDebug(m,"%s:: Ignore duplicate service found, ",__FUNCTION__);
						}
					}
				}
				else
				{
					TraceDebug(m,"NIT Old Version = %ld, New Version = %d ",(Nat32)tsdat.NITVersion, mGetNITVersion());
				}
			}
			else
			{
				TraceDebug(m,"TS data doesnt exist");
			}
        }
        else 
        {
            TraceDebug(m,"%s::We have to add a new service. Network update detected\r",__FUNCTION__);
            mSemiSbyInstallRequired = TRUE;
        }
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mUpdateServiceName(HsvPgdatDigServiceData* psvcdat, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    HsvPgdatDigServiceData svcdat = *psvcdat; 
    Bool updateName = TRUE;
	HsvChannel Channelinfo;

    if ((eurdiv_UpdateChannelName( rins_Cable ) == TRUE) && (CURRENT_MODE != AUTO_MODE))
    {   
        /* Channel Name Should be updated during Update Installation if diversity "UpdateChannelName" is set to true */
        if(TRUE == pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat))
        {
            Channelinfo.Ptc = svcdat.PresetNumber; 
            Channelinfo.Channel.OnePart = svcdat.PresetNumber;                  
            Channelinfo.Type = GETSERVICETYPE(svcdat.ServiceType);

            pgdat_GetChannelDataBool(Channelinfo, pgdat_BoolUpdateName, &updateName);            
        }
    } 

    TraceDebug(m,"Update NAME = %d\r",updateName);

    if(updateName == FALSE)
    {

		if (mCompareUnicodeString(svcdat.ChannelName, service->ServiceName) == FALSE)
		{
			/*Meaning user has not updated the name. So its ok we can update now. */
			mCopyString( svcdat.ChannelName, service->ServiceName, (eurdiv_ChannelNameLength - 1));
			// As pgdb_Update will update the data (including service name) and 
			// notice the java code to sync to the TV provider
			// so we don't need pgdat_StoreChannelDataString any more.
			// pgdat_StoreChannelDataString (Channelinfo, pgdat_StringExtChannelName,  svcdat.ChannelName, eurdiv_ChannelNameLength);
			TraceDebug(m, "svcdat.ChannelName != service->ServiceName");

			ServiceNameUpdated = TRUE;
		}
        

    }

    pgdb_Update( SERVICE_TABLE, (Address )&svcdat);
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCheckForLCNUpdate(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    t_LCNInfo LCNInfo;
    Bool retval = FALSE;
    HsvPgdatDigTSData tsdat;
    HsvPgdatDigServiceData svcdat = *psvcdat; 

    UNUSED(service);
    /* Always check for LCN from current NIT not from cached values. 
       Cached values are not currently being updated for NIT change */

    TraceDebug(m,"%s",__FUNCTION__);

    if(LCNS_REQUIRED)
    {
        tsdat.Frequency = ptc->Frequency;
        tsdat.StreamPriority = ptc->StreamPriority;
        if(pgdb_GetByKey( PTC_TABLE, (Address )&tsdat) == TRUE) 
        {
            REVALIDATE(svcdat.LCN);
            TraceDebug(m,"Function : %s Line : %d tsdat.NITVersion : %ld\r",__FUNCTION__,__LINE__,tsdat.NITVersion);
            if( mVersionUpdateNeeded || ((tsdat.NITVersion != mGetNITVersion()) && (mGetNITVersion() != INVALID_NITVERSION)) )
            {
                TraceDebug(m,"NIT Old Version = %ld, New Version = %d ",(Nat32)tsdat.NITVersion, mGetNITVersion());

                LCNInfo.Onid = svcdat.OriginalNetworkId; LCNInfo.Tsid = svcdat.Tsid; LCNInfo.ServiceId = svcdat.ServiceId; //keys to get the LCN frm strapi records 
                if(mGetLCNData(&LCNInfo, GET_LCN) == TRUE)
                {
                    if((svcdat.LCN != LCNInfo.LogicalChannelNum) || (svcdat.VisibleService != LCNInfo.VisibleService))
                    {
                        TraceDebug(m,"Either LCN <%d %d> or Visible Flag <%d %d> has changed", svcdat.LCN, LCNInfo.LogicalChannelNum, svcdat.VisibleService, LCNInfo.VisibleService);
                        retval = TRUE;
                    }
                }
                else
                {
                    if(VALID_LCN_RANGE(svcdat.LCN) ||(VALID_LCN_RANGE_RCSRDS(svcdat.LCN) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS)))
                    {
                        TraceDebug(m,"A valid lcn doesnt exist now LCN %d", svcdat.LCN);
                        retval = TRUE;
                    }
                }
            }
        }
    }
    else
    {
        TraceDebug(m,"No use of checking LCN when parseLCN is FALSE");
    }
    return retval;
}

void CHsvDvbCInstallation_mDataAcq_Priv::mCheckNITForBackgroundInstall(HsvInstallationPTC ptc)
{
	int NITVersion = INVALID_VERSION;
	HsvPgdatDigTSData tsdat;
    
    if(iquick_GetCurrentState() != iquick_stidle)
	{
		NITVersion = ptc.NITVersion;
	}
	else
	{
		tsdat.Frequency = ptc.Frequency;
		tsdat.StreamPriority = ptc.StreamPriority;

		if(TRUE == pgdb_GetByKey( PTC_TABLE, (Address )&tsdat))
		{
			NITVersion = tsdat.NITVersion;
		}
	}

    /* Only if quick scan, compare CDSDs */
    if((mSemiSbyInstallRequired == FALSE) && (rins_QuickScan == idvbset_GetAttribute(AUTO_MODE, rins_AttributeScanMode)))
    {
        TraceNotice(m," tsdat.NITVersion = %d and mGetNITVersion() = %d \r", NITVersion, mGetNITVersion());
        if(NITVersion != mGetNITVersion())
        {
            if(mCompareCableDS() == FALSE)
            {
                TraceNotice(m,"Network update detected due to change in CDSdesc\r");
                mSemiSbyInstallRequired = TRUE;
            }
			
            if (  (!((idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC) || ( idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_Blizoo))) && (mCompareSLD() == FALSE))
            {
                TraceNotice(m,"Network update detected due to change in SLDdesc\r");
                mSemiSbyInstallRequired = TRUE;
            }
			if((!mSemiSbyInstallRequired) && (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC) && (mCompareLCN() == FALSE))
			{
				TraceNotice(m,"Network update detected due to change in LCN Change\r");
				mSemiSbyInstallRequired = TRUE;
			}
			
        }
        else
        {
            TraceNotice(m,"NITVersion has not changed .Hence compare of SLD and CDSD is not done\r");
        }
    }
    else
    {
        TraceNotice(m,"Either Flag is TRUE or FullScan\r");
    }
}

void CHsvDvbCInstallation_mDataAcq_Priv::mCheckSDTOtherForBackgroundInstall(int Onid, int Tsid)
{
	/*Update Service Names and check for new services*/	
    Bool retval = FALSE, CDSDFound = FALSE;
	HSVSPTYPE(ActualCableDS, dvb, nit)	CableDSDesc;
	int i = 0, from = 0, to = 0, InstalledServices = 0, hsvpid = 0;
	HsvInstallationPTC ptc;
	
	HSVSPTYPE(OtherTSService, dvb, sdt) service;

	/*Fill PTC with CDSD*/
	hsvpid = (mFlashCableDS.TargetNITType == rins_NitOther) ? HSVSPID(OtherCableDS, dvb, nit) : HSVSPID(ActualCableDS, dvb, nit);
	if(strapi_GetRangeByKey(HsvMain,hsvpid,2,Onid,Tsid,0,&from,&to)== TRUE)
	{
		if(TRUE == strapi_GetByIndex(HsvMain, hsvpid, from, (void *)(&CableDSDesc)))
		{
			memset((Address)&ptc, 0, sizeof(HsvInstallationPTC));
			ptc.Frequency = (CableDSDesc.CDSD[0].Frequency * 1000)/16;
			ptc.StreamPriority = HsvStreamPriorityHigh;
			CDSDFound = TRUE;
			
		}
	}
	if(!CDSDFound)
	{
		TraceNotice(m,"CDSD not available for onid: %d tsid: %d",Onid,Tsid);
	}


	from = 0; to = 0;
	if(CDSDFound && strapi_GetRangeByKey(HsvMain,HSVSPID(OtherSDTSection, dvb, sdt),2,Onid,Tsid,0,&from,&to) == TRUE)
	{
	    TraceDebug(m,"%s %d NoOfServices in SDT Other = %d",__FUNCTION__, __LINE__, (to - from)+1);
	    for(i = from; i <= to ; i++)
	    {
	        if(strapi_GetByIndex(HsvMain, HSVSPID(OtherSDTSection, dvb, sdt), i, (void *)(&service)) == TRUE)
	        {
	            mCheckSDTOtherServiceForInstall (&ptc, &CableDSDesc, &service);
	        }
	    }
	}
	else
	{
		TraceDebug(m,"There are no services in starpi for TS: onid: %d Tsid: %d",Onid, Tsid);
	}


	
}


void CHsvDvbCInstallation_mDataAcq_Priv::mUpdateTsBackgroundInstall(void)
{
    if(mActive)
    {
        TraceDebug(m,"We got a new PTC. Network update detected\r");
        mSemiSbyInstallRequired = TRUE;
    }
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCompareCDSDFromStrapi(int hsvspid)
{
    Bool retval = TRUE, tsfound = FALSE, freqfound = FALSE, Curr = 0,mCurrCDSD = 0;
    int i = 0, j = 0;
    HSVSPTYPE(ActualCableDS, dvb, nit)  CableDSDesc;

    mCurrCableDS.NumOfTs = strapi_GetSize(HsvMain, hsvspid);

    if(mCurrCableDS.NumOfTs)
    {
        if(mCurrCableDS.NumOfTs > MAX_MUXES_PER_NTK)
        {
            TraceDebug(m,"NitAvail: numCurrCableDS is more than 10\r");
            mCurrCableDS.NumOfTs = MAX_MUXES_PER_NTK;
        }
        for(i = 0; i < mCurrCableDS.NumOfTs; i++ )
        {
            if(strapi_GetByIndex(HsvMain, hsvspid, i, (void*)(&CableDSDesc)))
            {
                mCurrCableDS.TsParam[i].ONID = CableDSDesc.Original_NetworkId;
                mCurrCableDS.TsParam[i].Tsid = CableDSDesc.Tsid;
                mCurrCableDS.TsParam[i].NumOfCDSD = CableDSDesc.NumOfCDSD;
                mCurrCableDS.TsParam[i].CurrentCDSDIndex = 0;

                for(j = 0; j < CableDSDesc.NumOfCDSD; j++)
                {
                    mCurrCableDS.TsParam[i].CableDescParam[j].Frequency = CableDSDesc.CDSD[j].Frequency;
                    mCurrCableDS.TsParam[i].CableDescParam[j].Modulation = CableDSDesc.CDSD[j].Modulation;
                    mCurrCableDS.TsParam[i].CableDescParam[j].SymbolRate = CableDSDesc.CDSD[j].SymbolRate;
                }
            }
            else
            {
                TraceDebug(m,"strapi_GetByIndex failed");
            }
        }
        mCurrCableDS.CurrentTsIndex = 0;
        TraceDebug(m,"No Of CDS records found = %d", mCurrCableDS.NumOfTs);
    }

    if(mFlashCableDS.NumOfTs != mCurrCableDS.NumOfTs)
    {
		/* ANEESH: UPCIGNORE */
		if (mIgnoreUPCBackgroundNetworkUpdate() == FALSE)
		{
			TraceDebug(m,"network update. Num of CableDS has changed. Flash = %d\r",mFlashCableDS.NumOfTs);
			retval = FALSE;			
		}
		else
		{
			TraceDebug(m,"network update. Num of CableDS has changed. Flash = %d. Ignoring it as its in transition \r",mFlashCableDS.NumOfTs);
		}
    }
    else
    {
        for(i = 0; (i < mFlashCableDS.NumOfTs) && retval; i++)
        {
            tsfound = FALSE;

            for(Curr = 0; (Curr < mFlashCableDS.NumOfTs) && retval; Curr++)
            {
                if((mFlashCableDS.TsParam[i].ONID == mCurrCableDS.TsParam[Curr].ONID) &&
                        (mFlashCableDS.TsParam[i].Tsid == mCurrCableDS.TsParam[Curr].Tsid))
                {
                    tsfound = TRUE;

                    if(mFlashCableDS.TsParam[i].NumOfCDSD != mFlashCableDS.TsParam[Curr].NumOfCDSD)
                    {
						/* ANEESH: UPCIGNORE */
						if (mIgnoreUPCBackgroundNetworkUpdate() == FALSE)
						{
							TraceDebug(m,"We have detected a network update. Num of CDSD within TS has changed\r");
							retval = FALSE;							
						}
						else
						{
							TraceDebug(m,"We have detected a network update. Num of CDSD within TS has changed. Ignoring as it happened in transition\r");
						}
                        break;
                    }
                    else
                    {
                        for(j = 0; j < mFlashCableDS.TsParam[i].NumOfCDSD; j++)
                        {
                            freqfound = FALSE;
                            for(mCurrCDSD = 0; mCurrCDSD < mFlashCableDS.TsParam[i].NumOfCDSD; mCurrCDSD++)
                            {
                                if((mFlashCableDS.TsParam[i].CableDescParam[j].Frequency == mCurrCableDS.TsParam[Curr].CableDescParam[mCurrCDSD].Frequency) &&
                                        (mFlashCableDS.TsParam[i].CableDescParam[j].SymbolRate == mCurrCableDS.TsParam[Curr].CableDescParam[mCurrCDSD].SymbolRate) &&
                                        (mFlashCableDS.TsParam[i].CableDescParam[j].Modulation == mCurrCableDS.TsParam[Curr].CableDescParam[mCurrCDSD].Modulation))
                                {
                                    freqfound = TRUE;
                                    break;
                                }
                            }
                            if(freqfound == FALSE)
                            {
                                TraceDebug(m,"network update. Freq or mod or sym within CDSD has changed in Freq = %ld\r",mFlashCableDS.TsParam[i].CableDescParam[j].Frequency);
                                retval = FALSE;
                                break;
                            }
                        }
                    }
                }
            }
            if(tsfound == FALSE)
            {
				/* ANEESH: UPCIGNORE */
				if (mIgnoreUPCBackgroundNetworkUpdate() == FALSE)
				{
					TraceDebug(m,"We have detected a network update. ONID, TSID missing = %d, %d\r",mFlashCableDS.TsParam[i].ONID,mFlashCableDS.TsParam[i].Tsid);
					retval = FALSE;					
				}
				else
				{
					TraceDebug(m,"We have detected a network update. But ignoring as it happened in transition. ONID, TSID missing = %d, %d\r",mFlashCableDS.TsParam[i].ONID,mFlashCableDS.TsParam[i].Tsid);
				}
                break;
            }
        }
    }

    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCompareCableDS(void)
{
    Nat16 NetworkID;
    Bool retval = TRUE;

    if(mFlashCableDS.TargetNITValue != INVALID_NETWORKID)
    {
        if(mFlashCableDS.TargetNITType == rins_NitActual)
        {
            if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkID))
            {
                if(NetworkID == mFlashCableDS.TargetNITValue)
                {
                    TraceDebug(m,"Found TargetNIT's during during Background\r");
                    if(mCompareCDSDFromStrapi(HSVSPID(ActualCableDS, dvb, nit)) == FALSE)
                    {
                        retval = FALSE;
                        TraceDebug(m,"Network Update: Change in CDSD\r");
                    }
                }
                else
                {
                    TraceDebug(m,"We are not interested in this NetworkID\r");
                }
            }
            else
            {
                TraceDebug(m,"ACTUAL NID not present");
            }
        }
        else if(mFlashCableDS.TargetNITType == rins_NitOther)
        {
            HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) networkinfo;

            if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), mFlashCableDS.TargetNITValue, 0, 0, &networkinfo))
            {
                TraceDebug(m,"Found TargetNIT's during during Background\r");

                if(mCompareCDSDFromStrapi(HSVSPID(OtherCableDS, dvb, nit)) == FALSE)
                {
                    retval = FALSE;
                    TraceDebug(m,"Network Update: Change in CDSD\r");
                }
            }
            else
            {
                TraceDebug(m,"Other NID not present");
            }
        }

    }

    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mIgnoreUPCBackgroundNetworkUpdate (void)
{
	Bool	RetVal = FALSE;
	
	RetVal = ((BACKGROUND_INSTALL) && (idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_UPC) && (BackGroundCount != BackGroundCountInAcq)) ? TRUE: FALSE;
	
	return RetVal;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCompareSLD(void)
{
    Bool retval = TRUE;
    int i, j;

    mAcquireServiceListData();

    if(mSvcListData.NumOfRecords != mFlashSvcListData.NumOfRecords)
    {
        TraceDebug(m,"retval %d mSvcListData.NumOfRecords %d mFlashSvcListData.NumOfRecords %d", retval, mSvcListData.NumOfRecords, mFlashSvcListData.NumOfRecords);
        retval = FALSE;
    }
    else
    {
        Bool found = FALSE;
        for(i = 0 ; i < mFlashSvcListData.NumOfRecords; i++)
        {
            found = FALSE;
            for(j = 0 ; j < mSvcListData.NumOfRecords; j++)
            {   
                if( (mFlashSvcListData.mSvcListInfo[i].Onid == mSvcListData.mSvcListInfo[j].Onid) &&
                        (mFlashSvcListData.mSvcListInfo[i].Tsid == mSvcListData.mSvcListInfo[j].Tsid) &&
                        (mFlashSvcListData.mSvcListInfo[i].ServiceId == mSvcListData.mSvcListInfo[j].ServiceId) )
                {   
                    found = TRUE;
                    break;
                }
            }

            if(found == FALSE)
            {
                TraceNotice(m,"%s %d service triplet keys r <%d, %d, %d>", __FUNCTION__, __LINE__, mSvcListData.mSvcListInfo[j].Onid, mSvcListData.mSvcListInfo[j].Tsid, mSvcListData.mSvcListInfo[j].ServiceId);
                retval = FALSE;
                break;
            }   
        }
    }       
    return retval;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCompareLCN(void)
{
    Bool retval = TRUE;
    int NumOfServices = 0,index = 0;
    HsvPgdatDigServiceData svcdat;
	t_LCNInfo LCNInfo;

	NumOfServices =	pgdb_GetNoRecords(SERVICE_TABLE);

    for (index = 0; index < NumOfServices; index++)
    {	
        if(pgdb_GetByIndex( SERVICE_TABLE, index,(Address)&svcdat))
        { 
			LCNInfo.Onid = svcdat.OriginalNetworkId; LCNInfo.Tsid = svcdat.Tsid; LCNInfo.ServiceId = svcdat.ServiceId; //keys to get the LCN frm strapi records 
			if(mGetLCNData(&LCNInfo, GET_LCN) == TRUE)
			{
				if((svcdat.LCN != LCNInfo.LogicalChannelNum) || (svcdat.VisibleService != LCNInfo.VisibleService))
				{
					TraceDebug(m,"mCompareLCN: Either LCN <%d %d> or Visible Flag <%d %d> has changed", svcdat.LCN, LCNInfo.LogicalChannelNum, svcdat.VisibleService, LCNInfo.VisibleService);
					retval = FALSE;
				}
			}
			else
			{
				if(VALID_LCN_RANGE(svcdat.LCN) ||(VALID_LCN_RANGE_RCSRDS(svcdat.LCN) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS)))
				{
					/* ANEESH: UPCIGNORE */
					if (mIgnoreUPCBackgroundNetworkUpdate() == FALSE)
					{
						TraceDebug(m,"mCompareLCN: A valid lcn doesnt exist now LCN %d", svcdat.LCN);
						retval = FALSE;						
					}
					else
					{
						TraceDebug(m,"mCompareLCN: A valid lcn doesnt exist now LCN %d. Ignoring as its in transition", svcdat.LCN);
					}
				}
			}
        }
    }



    return retval;
}


void CHsvDvbCInstallation_mDataAcq_Priv::mWriteSLDToFlash(void)
{
    FILE* fp;
    int writenrec = 0;
    char FileName[MAX_CHARACTERS];
	/*
	ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
    
	str_strcat(mDirName, "/channellib/");
	if(str_strlen(mDirName))
    {
		    
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
	*/
	
	str_strcpy(mDirName,"/user_setting/rw/tvserver/databases/channellib/");

    TraceNotice(m,"%s %d mAcqPump %d", __FUNCTION__, __LINE__, mAcqPump);
    mGetPathName(mDirName, SVC_LIST_DESC_FILEPATH, FileName);

    TraceDebug(m,"Fopen of %s\r", FileName);

    fp = fopen(FileName, "wb");

    if(fp)
    {
        writenrec = fwrite((Address)(&mSvcListData), sizeof(mSvcListData), 1, fp);
        if(writenrec)
        {
            TraceDebug(m,"Written SLD to Flash\r");
        }
        else
        {
            TraceDebug(m,"Write SLD to Flash Fail\r");
        }
        fclose(fp);
    }
    else
    {
        TraceDebug(m,"Unable to open %s\r",FileName);
        ASSERT(!"Unable to open SVC_LIST_DESC_FILEPATH");
    }
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;
    while((*src) && (*dest) )
	{
        if (*dest != *src)
		{
			break;
		}
			
		dest++; 
		src++;
	}
	
	if((*src) || (*dest))
	{
		retval = FALSE;
	}
	return retval;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_StartBackgroundInstall             (   void    ) 
{
	return;
}

int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNextSampleProgram               (   void    ) 
{
	return 0;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_DeleteServices                     (   void    ) 
{
	return;
}

int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNetworkIDList(void) 
{
	return 0;
}
void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNetworkIDName(int index, Nat16 *NetworkName) 
{
	return;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_SetFavouriteNetworkID(int mode, int attrib, int index) 
{
	return;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_ClearNetworkNameCache(void) 
{
	return;
}

Bool CHsvDvbCInstallation_mDataAcq_Priv::idataacq_IsLCNValid() 
{
	return FALSE;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_ClearCache() 
{
	return;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetRegionList(HsvNetworkRegionsData *RegionsData) 
{
	return;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType) 
{
	return;
}

int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType) 
{
	return 0;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetCachedRegionDetails(HsvTargetRegionCache * RegionCache) 
{
	return;
}
void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetChannelListIDName(int index, Nat16*ChannelistName)        
{
   return;
}
int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannelListIds()        
{
    return 0;
}

int CHsvDvbCInstallation_mDataAcq_Priv::idataacq_GetChannelListIdByIndex(int index)
{
   return 0;
}

void CHsvDvbCInstallation_mDataAcq_Priv::idataacq_SetFavouriteChannelListId(int mode, int attrib, int index)     
{
   return;
}

