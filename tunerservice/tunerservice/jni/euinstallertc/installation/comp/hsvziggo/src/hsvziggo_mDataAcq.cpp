/**********************************************************************
 *
 *   C Source:       hsvziggo_mDataAcq.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nituk %
 *   %date_created:  Tue Jun 12 21:03:57 2012 %
 *
 **********************************************************************/
#include "hsvziggo_mDataAcq.h"


TRACESYMBOL(m, "dvb/installation/hsvziggo_mDataAcq")















int CHsvZiggoInstallation_mDataAcq_Priv::s__mHsvDVBPIDList[7][7] = 
{
    /*Onid*/     { HSVSPID(ActualOriginalNetworkId, dvb, sdt),    HSVSPID(OtherOriginalNetworkId, dvb, sdt)   },
    /*Tsid*/     { HSVSPID(ActualTsId, dvb, sdt),                 HSVSPID(OtherTsId, dvb, sdt)                },
    /*VerNo*/    { HSVSPID(ActualTsVersionNo, dvb, sdt),          HSVSPID(OtherTsVersionNo, dvb, sdt)         },
/*SpidService*/  { HSVSPID(ActualTSService, dvb, sdt),            HSVSPID(OtherSDTSection, dvb, sdt)          },
    /*LCNv1*/    { HSVSPID(ActualNetworkLCN,dvb,nit),			  HSVSPID(OtherNetworkLCN, dvb, nit)		  },
    /*LCNv2*/    { HSVSPID(ActualNetworkLCN2,dvb,nit),			  HSVSPID(OtherNetworkLCN2, dvb, nit)		  },
	/*HDSLCN*/	 { HSVSPID(ActualNetworkHDSLCN,dvb,nit),		  HSVSPID(OtherNetworkHDSLCN,dvb,nit)		  }
};


int CHsvZiggoInstallation_mDataAcq_Priv::s__mHsvDVBSortedTableList[2][2] = 
{
#if 0

    /*LCNv2*/    { srtdbids_NitLcn2TableMain,			  srtdbids_NitLcn2TableSub   },
	/*HDSLCN*/	 { srtdbids_NitHDSLcnTableMain,			  srtdbids_NitHDSLcnTableSub }	
	#endif
};


/* Static variables */
t_DVBCData CHsvZiggoInstallation_mDataAcq_Priv::s__mDVBCData;

t_LCNsData CHsvZiggoInstallation_mDataAcq_Priv::s__mLCNData;

t_ZiggoServiceList CHsvZiggoInstallation_mDataAcq_Priv::s__mSvcListData;

int CHsvZiggoInstallation_mDataAcq_Priv::s__mDigitalChannelsFound;

Bool CHsvZiggoInstallation_mDataAcq_Priv::s__updateBarkerMuxZiggo = FALSE;




/* Static functions */























/* static function impl.. */





void CHsvZiggoInstallation_mDataAcq_Priv::mInstallMux(void)
{
    HsvInstallationPTC ptc;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat;
    Bool retval = FALSE, channelExists = FALSE;
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    int i, InstalledServices = 0;
    Nat16 PrevOnid = 0xFFFF, PrevTsid = 0xFFFF;
    Nat16 RequestedServiceId = 0xFFFF, RequestedOnid = 0xFFFF;
    Bool RequestSdtOtherInBackground   = FALSE;

    
    
    for(i = 0 ; i < mSvcListData.NumOfRecords; i++)
    {
        retval = FALSE; 
        pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

        svcdat.OriginalNetworkId     = mSvcListData.mSvcListInfo[i].Onid;
        svcdat.Tsid                  = mSvcListData.mSvcListInfo[i].Tsid;
        svcdat.ServiceId             = mSvcListData.mSvcListInfo[i].ServiceId;
        svcdat.ServiceType           = mSvcListData.mSvcListInfo[i].ServiceType;
        svcdat.DecoderType           = feapi_ChanDecDvbC;
        if(BACKGROUND_INSTALL)
        {
            ibckg_ZiggoGetPTCInfo(&ptc, svcdat.OriginalNetworkId, svcdat.Tsid);
        }
        else
        {
            iins_ZiggoGetPTCInfo(&ptc, svcdat.OriginalNetworkId, svcdat.Tsid);
        }

        memset((Address)&service, 0, sizeof(HSVSPTYPE(ActualTSService, dvb, sdt)));
        
        mDVBCData.NITVersion = mGetNITVersion();
        if(eurdiv_IsServiceInstallable(rins_Cable, mSvcListData.mSvcListInfo[i].ServiceType))
        {
            retval = strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE), mSvcListData.mSvcListInfo[i].Onid, mSvcListData.mSvcListInfo[i].ServiceId, mSvcListData.mSvcListInfo[i].Tsid, (void *)(&service));
            if(!BACKGROUND_INSTALL && !retval)
            {
                retval = strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, OTHER_TABLE), mSvcListData.mSvcListInfo[i].Onid, mSvcListData.mSvcListInfo[i].Tsid, mSvcListData.mSvcListInfo[i].ServiceId, (void *)(&service));
            }
            
            /* Naresh: Visible Flag is checked in mDuplicateEntry function so assign it before using below function */
            mAssignLCN(&svcdat);

            channelExists = mDuplicateEntry(svcdat, SERVICE_TABLE);
            if(channelExists)
            {
                if(!BACKGROUND_INSTALL && !retval)
                {
                    TraceNotice(m,"%s %d SDT Actual/ Other not available hence service name will be -----", __FUNCTION__, __LINE__);
                    mCopyString(service.ServiceName, instutil_AsciiToUnicode("-----", 5), 5);
                }
                retval = mUpdateService(&svcdat, &ptc, &service);
            }
            else
            {
                if(!retval)
                {
                    TraceNotice(m,"%s %d SDT Actual/ Other not available hence service name will be -----", __FUNCTION__, __LINE__);
                    mCopyString(service.ServiceName, instutil_AsciiToUnicode("-----", 5), 5);
                }
                retval = mAddNewService(&svcdat, &ptc, &service);
                if( eurdiv_SupportSDTOtherInBackgroundInstallation() && BACKGROUND_INSTALL && retval )
                {               
                    RequestSdtOtherInBackground = TRUE;
                    RequestedOnid       = svcdat.OriginalNetworkId;
                    RequestedServiceId  = svcdat.ServiceId;
                }
            }
        }
        else
        {
            svcdat.Frequency             =   ptc.Frequency;
            svcdat.StreamPriority        =   ptc.StreamPriority;

            if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
            {
                presetdat.PresetNumber =   svcdat.PresetNumber;

                pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
                pgdb_Delete(SERVICE_TABLE, (Address)&svcdat);
            }
        }

        if(retval)
        {
            InstalledServices++;

            /* This is ensure the calls are not made for each entry of service of a TS instead only once it is done */
            if(!((PrevOnid == svcdat.OriginalNetworkId) && (PrevTsid == svcdat.Tsid)))
            {
                PrevOnid = svcdat.OriginalNetworkId, PrevTsid = svcdat.Tsid;

                mAddToFreqMapTable(ptc, svcdat.OriginalNetworkId, svcdat.Tsid);
                mAddToTSTable(&ptc, svcdat.OriginalNetworkId, svcdat.Tsid);
            }
            
        }
    }
    TraceNotice(m,"Installed %d services", InstalledServices);
    
}

void CHsvZiggoInstallation_mDataAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    HsvPgdatDigTSData   tsdata, tmptsdata;

    tsdata.Frequency                = ptc->Frequency;
    tsdata.SymbolRate               = ptc->SymbolRate;
    tsdata.DecoderType              = ptc->DecoderType;     
    tsdata.OriginalNetworkId        = Onid;
    tsdata.Tsid                     = Tsid;
    tsdata.NetworkId                = mDVBCData.NetworkId;
    tsdata.ModulationType           = ptc->ModulationType;
    tsdata.CodeRate                 = ptc->CodeRateHigh;
    tsdata.HierarchyMode            = ptc->HierarchyMode;
    tsdata.GuardInterval            = ptc->GuardInterval;
    tsdata.TxMode                   = ptc->TxMode;
    tsdata.IqMode                   = ptc->IqMode;
    tsdata.Bandwidth         = ptc->ChannelBandwidth;
    tsdata.StreamPriority           = ptc->StreamPriority; 
    tsdata.TimeError                = ptc->TimeError;
    tsdata.FrequencyError           = ptc->FrequencyError;
    tsdata.FrequencyOffset          = ptc->FrequencyOffset;
    tsdata.PtcListVersion           = rins_GetInstallationVersion();
    tsdata.VSignalStrength          = ptc->VSignalStrength;
    tsdata.ASignalStrength          = ptc->ASignalStrength;
    tsdata.QSignalStrength          = ptc->QSignalStrength;
    tsdata.ChannelInformation       = ptc->ChannelInformation;
    tsdata.CDSDFrequency            = ptc->CDSDFrequency;
    tsdata.UserInstalled            = FALSE;
    tsdata.TSVersion                = mDVBCData.TsVersionNum;
    tsdata.NITVersion               = mDVBCData.NITVersion;
    tsdata.SDTVersion               = mDVBCData.SDTVersion;
	TraceNotice (m, " TSTable : Freq %d StreamPrio %d  NIT %d SDT %d ",tsdata.Frequency, tsdata.StreamPriority, tsdata.NITVersion, tsdata.SDTVersion);
    tmptsdata.Frequency             = tsdata.Frequency;
    tmptsdata.StreamPriority        = tsdata.StreamPriority;

    if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE ) 
    {
        pgdb_Add( PTC_TABLE, (Address )&tsdata);
    }
    else
    {
        pgdb_Update( PTC_TABLE, (Address )&tsdata);
    }
}
Bool CHsvZiggoInstallation_mDataAcq_Priv::mZiggoNetwork()
{
	Bool retval = FALSE;
	int NetworkOperator;
	NetworkOperator =rins_GetAttribute(AUTO_MODE,rins_AttributeNetworkOperator);
	if( (sysset_GetSystemCountry() ==IHsvCountryIds_CountryNetherlands) && (NetworkOperator == rins_Ziggo))
	{
		retval = TRUE;
	}
	return retval ;
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mDuplicateEntry(HsvPgdatDigServiceData svcdat, int tableid)
{
    Bool retval = FALSE;
    int i = 0, from = -1, to = -1;
    HsvPgdatDigServiceData svcdat2;

    /* 2 is the number of keys */
    if(pgdb_GetRange( tableid, 2, (Address)&svcdat, &from, &to))
    {
        for(i = from; i <= to; i++)
        {
            if(pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat2))
            {
                if( (!mZiggoNetwork()) || (svcdat.Tsid == svcdat2.Tsid))
			 		retval = TRUE;	
            }
        }
    }

    return retval;
}

void CHsvZiggoInstallation_mDataAcq_Priv::mCheckAndNotifyAttributeChange (HsvPgdatDigServiceData* newsvcdat, HsvPgdatDigServiceData* cursvcdat)
{
    HsvChannel Channelinfo;
    
    Channelinfo.Ptc = newsvcdat->PresetNumber; 
    Channelinfo.Channel.OnePart = newsvcdat->PresetNumber;                  
    Channelinfo.Type = AppApiOnePart;

    if (newsvcdat->SystemHidden != cursvcdat->SystemHidden)
    {
        pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSystemHidden, (Bool)newsvcdat->SystemHidden);
    }
    if (mCompareUnicodeString(newsvcdat->ChannelName, cursvcdat->ChannelName) == FALSE)
    {
        pgdat_StoreChannelDataString (Channelinfo, pgdat_StringExtChannelName,  newsvcdat->ChannelName, eurdiv_ChannelNameLength);
    }
}

void CHsvZiggoInstallation_mDataAcq_Priv::mUpdateServiceNameForTelenet(HsvPgdatDigServiceData* psvcdat)
{
	Bool retval = FALSE;
	int NetworkOperator;
	NetworkOperator =rins_GetAttribute(AUTO_MODE,rins_AttributeNetworkOperator);
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	
	/* In background update the service name for Telenet. Certification issue: AN-79957 */
	TraceNotice (m,"Country %d Operator %d ", sysset_GetSystemCountry(), NetworkOperator);
	if( (sysset_GetSystemCountry() ==IHsvCountryIds_CountryBelgium) && (NetworkOperator == rins_Telenet) && BACKGROUND_INSTALL)
	{   
		TraceNotice (m, "To check service name update for ONID %d TSID %d SID %d  ", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
		memset(&service, 0x00, sizeof(service));
		/* Only do update for SDT other. SDT actual is already done */
		retval = strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, OTHER_TABLE), psvcdat->OriginalNetworkId, psvcdat->Tsid,psvcdat->ServiceId,  (void *)(&service));		
		if (retval)
		{
			TraceNotice (m,"Telenet: UserModifiedName %d ServiceName %d ", psvcdat->UserModifiedName,service.ServiceName[0]);
			/* Service Name available. Compare and update */
			if( (psvcdat->UserModifiedName == FALSE) && (service.ServiceName[0] != 0) )
			{
				if(mCompareUnicodeString(psvcdat->ChannelName, service.ServiceName) == FALSE)
				{
					TraceNotice (m, "Telenet : Name Update happening from SDT Other during NIT update ");
					/* This means user has not renamed the service, so we can update the one sent by broadcaster */
					mCopyString( psvcdat->ChannelName, service.ServiceName, (eurdiv_ChannelNameLength - 1) );
				}
			}
		}
	}
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    Bool retval = FALSE;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData tmpsvcdat;

    mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mUpdateServiceNameForTelenet(psvcdat);
    mAssignSvcNonBroadcastAttributes(psvcdat);
    if(mOperatorZiggoInstallRules(psvcdat) == TRUE)
    {
        ASSIGN_KEYS_OF_SVC(tmpsvcdat, (*psvcdat));
        if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tmpsvcdat) == TRUE)
        {
            if (BACKGROUND_INSTALL)
            {
                mCheckAndNotifyAttributeChange (psvcdat, &tmpsvcdat);
            }
            pgdb_Update( SERVICE_TABLE, (Address)psvcdat);
        }
        else
        {
            if(mDuplicateEntry(*psvcdat, SERVICE_TABLE) == FALSE)
            {
                pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
                sort_UpdateDigitalPreset(psvcdat);

            }
            else
            {
                retval = FALSE;
            }
        }

        retval = TRUE;
    }
    else
    {

        presetdat.PresetNumber =   psvcdat->PresetNumber;
        
        pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
        pgdb_Delete(SERVICE_TABLE, (Address)psvcdat);
    }
    
    return retval;
}
void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_UpdateBarkerMuxInfo(Nat16 onid, Nat16 tsid)
{
    HsvPgdatDigTSData   tmptsdata;
	int index, NoOfRecs = 0;
	TraceNotice(m,"idataacq_UpdateBarkerMuxInfo Mahesh [%d] [%d] \n",onid,tsid);
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

	TraceNotice(m,"idataacq_UpdateBarkerMuxInfo Mahesh [%d] [%d] \n",onid,tsid);	
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_AcquireSDTOtherData()
{
	return;
}


Bool CHsvZiggoInstallation_mDataAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
    Bool retval = FALSE;
	HsvPgdatPresetData presetdat;
    mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
	mUpdateServiceNameForTelenet(psvcdat);
    mAssignSvcNonBroadcastAttributes(psvcdat);

    if(mOperatorZiggoInstallRules(psvcdat) == TRUE)
    {
        pgdb_Add(SERVICE_TABLE, (Address )psvcdat);

			if(BACKGROUND_INSTALL)
				{
				presetdat.PresetNumber = psvcdat->PresetNumber ;
				
				if (pgdb_GetByKey(PRESET_TABLE, &presetdat) == TRUE )
					if((presetdat.Tsid != psvcdat->Tsid)||(presetdat.Frequency != psvcdat->Frequency)||(presetdat.StreamPriority != psvcdat->StreamPriority))
						{

						presetdat.Tsid = psvcdat->Tsid;
						presetdat.Frequency = psvcdat->Frequency;
						presetdat.StreamPriority = psvcdat->StreamPriority;
						pgdb_Update(PRESET_TABLE,(Address) &presetdat);

						}
				}

        mDigitalChannelsFound++;
        retval = TRUE;
    }

    return retval;
}

void CHsvZiggoInstallation_mDataAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
    Bool Proceed = FALSE;
    HsvPATProgramPIDInfo val;
    HsvPgdatDigServiceData svcdat;
    HsvChannel Channelinfo;
    HSVSPTYPE(ActualTSService, dvb, sdt) TmpService;
    
    psvcdat->NetworkId             =   mDVBCData.NetworkId;
    psvcdat->Frequency             =   ptc->Frequency;
    psvcdat->ModulationType        =   ptc->ModulationType;
    psvcdat->Bandwidth      =   ptc->ChannelBandwidth;
    psvcdat->StreamPriority        =   ptc->StreamPriority ;    
    psvcdat->SymbolRate            =   ptc->SymbolRate;
    psvcdat->DecoderType           =   feapi_ChanDecDvbC;
    psvcdat->Type                  =   GETSERVICETYPE(psvcdat->ServiceType);
    psvcdat->FreeCiMode            =   service->Free_Ci_Mode;
    psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
    psvcdat->NumBrandIds           =   service->NumBrandIds;
    psvcdat->DvbType               =   AppApiDvbTypeC;
    psvcdat->AudioPid              =   INVALID_PID;
    psvcdat->VideoPid              =   INVALID_PID;
    psvcdat->PcrPid                =   INVALID_PID;
    psvcdat->LCN                   =   INVALID_LCN;
    psvcdat->OUI                   =   HsvOUI_Last;
    psvcdat->SystemHidden          =   FALSE;
    ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
    
    psvcdat->SrcambledStatus       = 0;
	psvcdat->ScramblingStatus	   = 0;

    if(service->Free_CA_Mode == TRUE)
    {
        psvcdat->SrcambledStatus = 1;
		psvcdat->ScramblingStatus =1;
    }

    mAssignLCN(psvcdat);
    // Numeric select flag is made false in case of invisible services of Ziggo. This is to ensure that the services are installed, but not selectable via Digit Entry. 
    psvcdat->NumericSelect         =   psvcdat->VisibleService;

    if ( ( eurdiv_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(psvcdat->ServiceType)) ) || (psvcdat->VisibleService == FALSE))
    {
        psvcdat->SystemHidden = TRUE;
    }

    if( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) )
    {
        psvcdat->PmtPid            =   val.Pid;
    }

    mDVBCData.SDTVersion           = service->VersionNumber;
    mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds );

    ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
    {
        Proceed = TRUE;
        psvcdat->UserModifiedName = svcdat.UserModifiedName;

        if(!strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE), psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->Tsid, (void *)(&TmpService)))
        {
            psvcdat->SrcambledStatus = svcdat.SrcambledStatus;
			psvcdat->ScramblingStatus	   =svcdat.ScramblingStatus;
        }
    }

    if( (psvcdat->UserModifiedName == FALSE) && (service->ServiceName[0] != 0) )
    {
        /* This means user has not renamed the service, so we can update the one sent by broadcaster */
        mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_ChannelNameLength - 1) );
    }
    else
    {
        if(Proceed)
        {
            mCopyString( psvcdat->ChannelName, svcdat.ChannelName, (eurdiv_ChannelNameLength - 1) );
        }
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
                //PrintfNotice("%s: :;::: SCramble status change ", __FUNCTION__);
                pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSrcambledStatus, (Bool)psvcdat->SrcambledStatus);
            }
			if (psvcdat->ScramblingStatus != svcdat.ScramblingStatus)
            {
                pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSrcambledStatus, (Bool)psvcdat->ScramblingStatus);
            }
        }
    }
}

void CHsvZiggoInstallation_mDataAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
    Bool Proceed = FALSE, retval = FALSE;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat;
    HSVSPTYPE(ActualTSService, dvb, sdt) service;

    psvcdat->UserHidden             = FALSE;
    psvcdat->ChannelLock            = FALSE;
    psvcdat->Favorite               = FALSE;
    psvcdat->PreferredStereo        = 1;
    psvcdat->PresetNumber           = INVALID_PRESET;
    psvcdat->ServiceListVersion     = rins_GetInstallationVersion();
    psvcdat->NewPreset              = !AUTO_INSTALL;
    psvcdat->HbbTvOption            = 1;
    psvcdat->NewChannelMap          = 1;

    /* Ziggo requirement for SDT other services the date time Expiry should happen */
    retval = strapi_GetByKey(HsvMain, GETHSVSPID(SpidService, ACTUAL_TABLE), psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->Tsid, (void *)(&service));

    psvcdat->DateStamp = (Timerclk_IsClockDefined() && retval)? Timerclk_GetUniversalTime() : 0;
    ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat)); 
    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
    {
    	TraceNotice(m,"%s %d lcn[%d] \n",__FUNCTION__,__LINE__,svcdat.LCN);
        mRetainNonBroadcastAttributes(psvcdat, svcdat);
        Proceed = (IS_RADIO_SERVICE(psvcdat->ServiceType) != IS_RADIO_SERVICE(svcdat.ServiceType));
        
        REVALIDATE(psvcdat->LCN); REVALIDATE(svcdat.LCN);
        Proceed |= ((VALID_LCN_RANGE(psvcdat->LCN) || VALID_LCN_RANGE(svcdat.LCN)) && (psvcdat->LCN != svcdat.LCN) && eurdiv_UpdateLCN(rins_GetMedium()));
        
        Proceed |= (psvcdat->VisibleService != svcdat.VisibleService);

        if(Proceed)
        {
            /* below done, because the LCN changes or service Type (Radio/TV vice versa) presets are sorted freshly */
            TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d newSvcType %d oldSvcType %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->LCN, svcdat.LCN, psvcdat->ServiceType, svcdat.ServiceType, svcdat.PresetNumber);
            presetdat.PresetNumber =   svcdat.PresetNumber;
            presetdat.Type         =   HsvOnePart;
            pgdb_Delete(PRESET_TABLE, (Address)&presetdat);

            psvcdat->PresetNumber = INVALID_PRESET;
        }
    }
    else
    {
        if(BACKGROUND_INSTALL)
        {
            /* Primary keys might have changed check */
            mDeleteDuplicateRecords(psvcdat);
        }
    }
}

inline void CHsvZiggoInstallation_mDataAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; (i < maxchars) && (*src); i++)
    {
        *dest++ = *src++;
    }
    *dest = 0;
}

inline int CHsvZiggoInstallation_mDataAcq_Priv::mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId)
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

Bool CHsvZiggoInstallation_mDataAcq_Priv::mInstallBasedOnHDSLcns(HsvPgdatDigServiceData svcdat1)
{
    Bool retval = TRUE;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat2;
    int i, index = -1, NoOfRecords = pgdb_GetNoRecords(SERVICE_TABLE);

    index = mGetLCNIndex(svcdat1.OriginalNetworkId, svcdat1.Tsid, svcdat1.ServiceId);
    if(index < mLCNData.NumOfLCNRecords)
    {
        if(mLCNData.mLCNInfo[index].LCNType == HDSLCNVERSION)
        {
            for(i = 0; i < NoOfRecords; i++)
            {
                if(pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat2))
                {
                    index = mGetLCNIndex(svcdat2.OriginalNetworkId, svcdat2.Tsid, svcdat2.ServiceId);
                    if(index != mLCNData.NumOfLCNRecords)
                    {
                        if( (svcdat1.LCN == svcdat2.LCN) && (mLCNData.mLCNInfo[index].LCNType != HDSLCNVERSION) )
                        {
                            TraceNotice(m,"%s %d deleted PresetNumber %d ServiceId : %d because of LCN <=> HDSLCN conflict", __FUNCTION__, __LINE__, svcdat2.PresetNumber, svcdat2.ServiceId);
                            presetdat.PresetNumber =   svcdat2.PresetNumber;

                            pgdb_Delete(SERVICE_TABLE,(Address)&svcdat2);
                            pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
                            i--; NoOfRecords--;
                        }
                    }
                }
            }
        }
        else
        {
            for(i = 0; i < NoOfRecords; i++)
            {
                if(pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat2))
                {
                    index = mGetLCNIndex(svcdat2.OriginalNetworkId, svcdat2.Tsid, svcdat2.ServiceId);
                    if(index != mLCNData.NumOfLCNRecords)
                    {
                        if( (svcdat1.LCN == svcdat2.LCN) && (mLCNData.mLCNInfo[index].LCNType == HDSLCNVERSION) )
                        {
                            retval = FALSE;
                            break;
                        }
                    }
                }
            }
        }
    }
    return retval;
}

inline Bool CHsvZiggoInstallation_mDataAcq_Priv::mOperatorZiggoInstallRules(HsvPgdatDigServiceData *svcdat)
{
    Bool retval = FALSE;

    /* Rule 1. Valid LCN */
    TraceInfo(m,"%s %d svcdat->ServiceId %d svcdat->LCN %d", __FUNCTION__, __LINE__,svcdat->ServiceId, svcdat->LCN);
    if( VALID_LCN_RANGE(svcdat->LCN) )
    {
        /* Rule 2. HD & SD LCN */
        retval = mInstallBasedOnHDSLcns(*svcdat);
    }

    return retval;
}

/**********************************************
  provides IHsvDigitalAcquisition  idataacq
 **********************************************/

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_Initialise()
{
    mLCNData.NumOfLCNRecords = 0;
    mDVBCData.Onid = mDVBCData.Tsid = mDVBCData.NetworkId = 0xFFFF;
    memset((Address)&mSvcListData, 0, sizeof(mSvcListData));
    memset((Address)&mLCNData, 0, sizeof(mLCNData));

}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_InitialiseTotalChannels()
{
    mDigitalChannelsFound = 0;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_AcquireData()
{
    /* Call Back once Data collection is completed by SDM */
    if(BACKGROUND_INSTALL)
    {
        ibckg_GetTargetNitType(&mDVBCData.NetworkId);
    }
    else
    {
        iins_GetTargetNitType(&mDVBCData.NetworkId);
    }

	/*TODO: proper mechanism need to be found for clearing and for back up of db, 
	for ziggo there will be an issue if installation is stopped aduring acquisition channel maps will not have proper data*/
	if(AUTO_INSTALL)
	{
		pgdb_ClearTable(PTC_TABLE);
		pgdb_ClearTable(SERVICE_TABLE);
		pgdb_ClearTable(PRESET_TABLE);
		pgdb_ClearTable(FREQMAP_TABLE);
	}
	

    mInstallMux();
}

/* delete those services which are not in service list descriptor */
void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_DeleteServices(void)
{
    Bool Found = FALSE;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat;
    int dbindex = 0, i = 0, NoOfRecords = pgdb_GetNoRecords(SERVICE_TABLE);

    for(dbindex = 0 ; dbindex < NoOfRecords; dbindex++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
        {
            Found = FALSE;
            for(i = 0; i < mSvcListData.NumOfRecords; i++)
            {
                if( (svcdat.OriginalNetworkId    == mSvcListData.mSvcListInfo[i].Onid) &&
                        (svcdat.Tsid                 == mSvcListData.mSvcListInfo[i].Tsid) &&
                        (svcdat.ServiceId            == mSvcListData.mSvcListInfo[i].ServiceId) )
                {
                    Found = TRUE;
                }
            }

            if(Found == FALSE)
            {
                TraceNotice(m,"%s %d preset deleted %d = <%d %d %d>", __FUNCTION__, __LINE__, svcdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId);
                presetdat.PresetNumber =   svcdat.PresetNumber;

                pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
                pgdb_Delete(SERVICE_TABLE, (Address)&svcdat);
                dbindex--; NoOfRecords--;
            }
        }
    }
}

int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
    return mDigitalChannelsFound;
}
int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}
int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannels(int servicetype)
{
    UNUSED(servicetype);
    return mDigitalChannelsFound;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_AcquireLCNData()
{
    t_LCNInfo LCNInfo;
    /* Naresh: below is overloaded function, the param is used for other purpose and not here */
    mGetLCNData(&LCNInfo, ACQUIRE_LCNS);
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_AcquireServiceListData()
{
    Nat16 NetworkId;
    HSVSPTYPE(ActualServiceList, dvb, nit) svcList;
    int hsvspid, i = 0, numOfEntries = 0, NitType = (BACKGROUND_INSTALL)? ibckg_GetTargetNitType(&NetworkId) : iins_GetTargetNitType(&NetworkId);
    hsvspid = (NitType == eurdiv_NitActual)? HSVSPID(ActualServiceList, dvb, nit):HSVSPID(OtherServiceList, dvb, nit);
    numOfEntries = strapi_GetSize(HsvMain, hsvspid);
    mSvcListData.NumOfRecords = 0;
    for(i = 0 ; i < numOfEntries; i++)
    {
        if(strapi_GetByIndex(HsvMain, hsvspid, i, (void*)(&svcList)))
        {
            mSvcListData.mSvcListInfo[i].Onid        = svcList.Original_NetworkId;
            mSvcListData.mSvcListInfo[i].Tsid        = svcList.Tsid;
            mSvcListData.mSvcListInfo[i].ServiceId   = svcList.ServiceId;
            mSvcListData.mSvcListInfo[i].ServiceType = mConvertToPgdatServiceType(svcList.ServiceType);

            mSvcListData.NumOfRecords++;
            mSvcListData.VersionNumber = svcList.VersionNumber;

        }
        else
        {

        }
    }
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mLcnVersion1Data(Nat16 NetworkId, int HsvPid, t_LCNInfo *LCNInfo, int ActionOnData)
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

Bool CHsvZiggoInstallation_mDataAcq_Priv::mHdsLcnData(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData)
{
    Bool retval = FALSE;
    int i, numOfRecords = strapi_GetSize(HsvMain, HsvPid);
    HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) nwhdslcn;

    if( ActionOnData == ACQUIRE_LCNS )
    {
        for(i = 0; i < numOfRecords; i++)
        {
            //if(srtdb_QueryOnIndex(DBTableId, i, (Address)(&nwhdslcn)))
            if(strapi_GetByIndex(HsvMain, HsvPid, i, (Address)(&nwhdslcn)))
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

    return retval;  
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mLcnVersion2Data(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData)
{
    Bool retval = FALSE; 
    HsvDestination dest = HsvMain;
    int NoOfRecs, i, channellistid, from, to, countrycode = 0;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    NoOfRecs = strapi_GetSize(HsvMain, HsvPid);

    if( LCN_VERSION2_PRESENT(NoOfRecs) )
    {
        mGetInterestedLCNRecords(HsvPid, DBTableId, &from, &to, &countrycode);
        channellistid = mGetInterestedChanneListId(HsvPid, from, to, &countrycode);

//        if(TRUE == srtdb_SearchOnPrimaryAndSecondaryKey(DBTableId, countrycode, channellistid, &from, &to)) 
	    if(strapi_GetRangeByKey(dest,HsvPid,2 ,countrycode ,channellistid ,0 , &from, &to) == TRUE)
        {
            for(i = from; i <= to; i++)
            {
//                if( (srtdb_QueryOnIndex(DBTableId, i, (Address)&nwlcn) == TRUE) )
				if( strapi_GetByIndex(dest,HsvPid, i, (Address)&nwlcn) == TRUE )
                {
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
    return retval;
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mPopulateLCN(Address data, int version)
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
        case HDSLCNVERSION:
            nwhdslcn = (HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) *)data;
            cacheIndex = mGetLCNIndex(nwhdslcn->Original_NetworkId, nwhdslcn->Tsid, nwhdslcn->ServiceId);

            mLCNData.VersionNumber = nwhdslcn->VersionNumber;

            if(cacheIndex >= mLCNData.NumOfLCNRecords)
            {
                mCopyLCNInfo( &(mLCNData.mLCNInfo[mLCNData.NumOfLCNRecords]), nwhdslcn->Original_NetworkId, nwhdslcn->Tsid, nwhdslcn->ServiceId, \
                        nwhdslcn->LogicalChannelNum, nwhdslcn->VisibleService, version);
                mLCNData.NumOfLCNRecords++;

            }
            else
            {
                /* This case is to access the right index from the list of records*/
                mCopyLCNInfo( &(mLCNData.mLCNInfo[cacheIndex]), nwhdslcn->Original_NetworkId, nwhdslcn->Tsid, nwhdslcn->ServiceId, \
                        nwhdslcn->LogicalChannelNum, nwhdslcn->VisibleService, version);

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

void CHsvZiggoInstallation_mDataAcq_Priv::mGetInterestedLCNRecords(int HsvPid, int DBTableId, int *from, int *to, int *countrycode)
{
    HsvDestination dest = HsvMain;
    *countrycode = sysset_GetSystemCountry();
//    if(srtdb_SearchOnPrimaryKey(DBTableId, *countrycode, from, to) == FALSE)
	if(strapi_GetRangeByKey(dest,HsvPid,1 ,*countrycode ,0 ,0 , from, to) == FALSE)
    {
        *from = 0, *to = strapi_GetSize(HsvMain, HsvPid);
    }
}

int CHsvZiggoInstallation_mDataAcq_Priv::mGetInterestedChanneListId(int HsvPid, int from, int to, int *countrycode)
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

inline void CHsvZiggoInstallation_mDataAcq_Priv::mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version)
{
    LCNInfo->Onid              = OnId;
    LCNInfo->Tsid              = TsId;
    LCNInfo->ServiceId         = SvcId;
    LCNInfo->LogicalChannelNum = Lcn;
    LCNInfo->VisibleService    = VisibleSvc;
    LCNInfo->LCNType           = version;
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mGetLCNData(t_LCNInfo *LCNInfo, int ActionOnData)
{ 
    Bool retval = FALSE;
    Nat16 NetworkId;
    int NitType = (BACKGROUND_INSTALL)? ibckg_GetTargetNitType(&NetworkId) : iins_GetTargetNitType(&NetworkId);
    int TableId = (NitType == eurdiv_NitActual)? ACTUAL_TABLE : OTHER_TABLE;



    retval = mLcnVersion2Data(NetworkId, GETHSVSPID(LCNv2, TableId), GETDBTABLEID(0, TableId), LCNInfo, ActionOnData);
    if(retval == FALSE)
    {
        retval = mLcnVersion1Data(NetworkId, GETHSVSPID(LCNv1, TableId), LCNInfo, ActionOnData);
    }

    retval |= mHdsLcnData(NetworkId, GETHSVSPID(HDSLCN, TableId), GETDBTABLEID(1, TableId), LCNInfo, ActionOnData);

    return retval;
}

void CHsvZiggoInstallation_mDataAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
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
                psvcdat->LCN = (VALID_LCN_RANGE(LCNInfo.LogicalChannelNum) == TRUE)? LCNInfo.LogicalChannelNum: psvcdat->LCN;
                psvcdat->VisibleService = ( (psvcdat->LCN == ZEROLCN) && eurdiv_IsZeroLCNHidden() )? FALSE: LCNInfo.VisibleService;

            }
        }
        else
        {
            /* Assign from Target NIT */
            cacheIndex = mGetLCNIndex(psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
            if(cacheIndex != mLCNData.NumOfLCNRecords)
            {
                psvcdat->LCN = (VALID_LCN_RANGE(mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum) == TRUE)? mLCNData.mLCNInfo[cacheIndex].LogicalChannelNum: psvcdat->LCN;
                psvcdat->VisibleService = ( (psvcdat->LCN == ZEROLCN) && eurdiv_IsZeroLCNHidden() )? FALSE: mLCNData.mLCNInfo[cacheIndex].VisibleService;

            }
        }
    }   
}

void CHsvZiggoInstallation_mDataAcq_Priv::mAddToFreqMapTable(HsvInstallationPTC ptc, Nat16 Onid, Nat16 Tsid)
{
    /* write to freqmaptable */
    HsvPgdatDigFreqMapData    freqdat;
    HsvPgdatDigFreqMapData    tmpfreqdat;
    Bool retval;

    freqdat.OriginalNetworkId   = Onid;
    freqdat.Tsid                = Tsid;
    freqdat.Frequency           = ptc.Frequency;
    freqdat.ModulationType      = ptc.ModulationType;
    freqdat.SymbolRate          = ptc.SymbolRate;
    freqdat.DecoderType         = ptc.DecoderType;

    tmpfreqdat.OriginalNetworkId    = freqdat.OriginalNetworkId;
    tmpfreqdat.Tsid                 = freqdat.Tsid;

    if(pgdb_GetByKey(FREQMAP_TABLE, (Address )&tmpfreqdat))
    {
        retval = pgdb_Update(FREQMAP_TABLE, (Address )&freqdat);

    }
    else
    {
        retval = pgdb_Add( FREQMAP_TABLE, (Address )&freqdat);

    }
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat)
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
                (svcdat->ServiceId         == svcdat2.ServiceId) && 
                ((!mZiggoNetwork()) || (svcdat->Tsid == svcdat2.Tsid))/*&&
                (svcdat->VisibleService == svcdat2.VisibleService) && (svcdat->VisibleService == TRUE) */)
            {
                mRetainNonBroadcastAttributes(svcdat, svcdat2);
                /* Also copy SDT values here as SDT section would not be available during background installation unless we are in tat respective mux*/
                svcdat->FreeCiMode         =   svcdat2.FreeCiMode;
                svcdat->MatchBrandFlag     =   svcdat2.MatchBrandFlag;
                svcdat->NumBrandIds        =   svcdat2.NumBrandIds;
                svcdat->SrcambledStatus    =   svcdat2.SrcambledStatus;
				svcdat->ScramblingStatus    =   svcdat2.ScramblingStatus;
                mCopyString( svcdat->BrandIds, svcdat2.BrandIds, svcdat2.NumBrandIds );
                mCopyString( svcdat->ChannelName, svcdat2.ChannelName, (eurdiv_ChannelNameLength - 1) );

                pgdb_Delete(SERVICE_TABLE,(Address) &svcdat2);
                retval = TRUE;
                break;
            }
        }
    }
    return retval;
}

void CHsvZiggoInstallation_mDataAcq_Priv::mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat)
{
    psvcdat->NewPreset = svcdat.NewPreset;
    /* Naresh: Retain the non broadcast attributes during background install */
    psvcdat->PresetNumber           = svcdat.PresetNumber;
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
    //psvcdat->UniqueIds[0]	   =  svcdat.UniqueIds[0]; 
    memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
        
}

Nat8 CHsvZiggoInstallation_mDataAcq_Priv::mGetNITVersion(void)
{
    Nat8 retval = 0;
    Nat16 NetworkId;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) NIDInfo;
    int NitType = (BACKGROUND_INSTALL)? ibckg_GetTargetNitType(&NetworkId) : iins_GetTargetNitType(&NetworkId);

    if(NitType == rins_NitOther)
    {
        if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0, (void*) (&NIDInfo)))
        {
            retval = NIDInfo.VersionNumber;
        }
    }
    else 
    {
        strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (Address)(&retval));
    }
    
    return retval;
}
Bool CHsvZiggoInstallation_mDataAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;
    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}
	return retval;
}

int CHsvZiggoInstallation_mDataAcq_Priv::mConvertToDVBServiceType(int servicetype)
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
      
        default:
            break;
    }
    return retval;
}

int CHsvZiggoInstallation_mDataAcq_Priv::mConvertToPgdatServiceType(int servicetype)
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
        default:
            break;
    }
    return retval;
}

//Stub

/* Interfaces from IHsvdigitalacquisition.id */


int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNextSampleProgram               (   void    ) 
{
	return 0;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_StartBackgroundInstall             (   void    ) 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_ResetBackgroundInstall             (   void    ) 
{
	return;
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::idataacq_IsNetworkUpdateDetected            (   void    ) 
{
	return FALSE;
}


int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNetworkIDList(void) 
{
	return 0;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNetworkIDName(int index, Nat16 *NetworkName) 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_SetFavouriteNetworkID(int mode, int attrib, int index) 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_ClearNetworkNameCache(void) 
{
	return;
}

Bool CHsvZiggoInstallation_mDataAcq_Priv::idataacq_IsLCNValid() 
{
	return FALSE;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_AcquireONID() 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_SyncTemporaryTableRecords(void) 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_ClearCache() 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetRegionList(HsvNetworkRegionsData *RegionsData) 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType) 
{
	return;
}

int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType) 
{
	return 0;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_Enable() 
{
	Nat16 RequestedServiceId = 0xFFFF, RequestedOnid = 0xFFFF;
	
	/* For Telenet we have to enable all the SDT other, not just for newly added channels */
	if( BACKGROUND_INSTALL && eurdiv_SupportSDTOtherInBackgroundInstallation())
    {
        if(!strmfltr_IsSet(HsvMain,HsvOtherSDTOnwidId, RequestedOnid)) 
        {
            strmfltr_Set( HsvMain, HsvOtherSDTOnwidId, RequestedOnid );
        }
        
        if(!strmfltr_IsSet(HsvMain,HsvOtherSDTServiceId, RequestedServiceId))
        {
            TraceNotice(m,"Telenet : ******** requesting SDT_Other filter ********** ServiceId %d", RequestedServiceId);
            strmfltr_Set( HsvMain, HsvOtherSDTServiceId, RequestedServiceId );
        }
    }

}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_Disable() 
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetCachedRegionDetails(HsvTargetRegionCache * RegionCache) 
{
	return;
}
void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetChannelListIDName(int index, Nat16*ChannelistName)        
{
   return;
}
int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannelListIds()        
{
    return 0;
}

int CHsvZiggoInstallation_mDataAcq_Priv::idataacq_GetChannelListIdByIndex(int index)
{
   return 0;
}

void CHsvZiggoInstallation_mDataAcq_Priv::idataacq_SetFavouriteChannelListId(int mode,int attrib,int index)     
{
   return;
}


void CHsvZiggoInstallation_mDataAcq_Priv::strapiN_OnChanged( HsvDestination dest, int spid, int Onid, int ServiceId, int Tsid, int eventid)
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::strapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	return;
}

void CHsvZiggoInstallation_mDataAcq_Priv::strapiN_OnCompleted         ( HsvDestination dest, int spid)
{
	return;
}
void CHsvZiggoInstallation_mDataAcq_Priv::strapiN_OnRemoved           ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	return;
}

