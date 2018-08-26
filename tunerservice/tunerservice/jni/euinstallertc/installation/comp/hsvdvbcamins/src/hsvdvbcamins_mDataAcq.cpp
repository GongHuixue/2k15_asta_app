/**********************************************************************
 *
 *   C Source:       hsvdvbcamins_mDataAcq.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nituk %
 *   %date_created:  Tue Jun 12 21:03:57 2012 %
 *
 **********************************************************************/
#include "_hsvdvbcamins_mDataAcq.h"


TRACESYMBOL(m, "dvb/installation/hsvdvbcamins_mDataAcq")






/*****   Static variables   *****/
t_CamServiceList CHsvDvbCamInstallation_mDataAcq_Priv::s__mCamServiceList;

Nat8 CHsvDvbCamInstallation_mDataAcq_Priv::s__mCamNITVersion = 0;

int CHsvDvbCamInstallation_mDataAcq_Priv::s__mDigitalChannelsFound = 0;

Bool CHsvDvbCamInstallation_mDataAcq_Priv::s__updateBarkerMuxDvbCamins = FALSE;


char FirstByte ;
char SecondByte;
char ThirdByte ;



/*****   Static Functions   *****/

















void CHsvDvbCamInstallation_mDataAcq_Priv::mInstallMuxs(void)
{
    HsvInstallationPTC ptc;
    HsvPgdatDigServiceData svcdat;
    Bool retval = FALSE, channelExists = FALSE;
    int i, InstalledServices = 0;
    Nat16 PrevOriginalNetworkId = 0xFFFF, PrevTsId = 0xFFFF;

	TraceNotice(m,"%s %d", __FUNCTION__, mCamServiceList.NumOfRecords);
    for(i = 0 ; i < mCamServiceList.NumOfRecords; i++)
    {
        retval = FALSE;         
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

		mAssignServiceMetaDataAttributes(&svcdat, &(mCamServiceList.ServiceInfo[i]));
		
        iins_ZiggoGetPTCInfo(&ptc, svcdat.OriginalNetworkId, svcdat.Tsid);
        
		channelExists = mDuplicateEntry(svcdat, SERVICE_TABLE);
		TraceNotice(m,"%s %d", __FUNCTION__, channelExists);
		if(channelExists)
		{
			retval = mUpdateService(&svcdat, &ptc);
		}
		else
		{
			retval = mAddNewService(&svcdat, &ptc);
		}
        
		if(retval)
        {
            InstalledServices++;
            /* This is ensure the calls are not made for each entry of service of a TS instead only once it is done */
            if(!((PrevOriginalNetworkId == svcdat.OriginalNetworkId) && (PrevTsId == svcdat.Tsid)))
            {
                PrevOriginalNetworkId = svcdat.OriginalNetworkId, PrevTsId = svcdat.Tsid;
                mAddToTSTable(&ptc, svcdat.OriginalNetworkId, svcdat.Tsid,FALSE);
            }
        }
		mAddToFreqMapTable(ptc, svcdat.OriginalNetworkId, svcdat.Tsid);
        TraceNotice(m,"Installed %d services", InstalledServices);
    }
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mAssignServiceMetaDataAttributes(HsvPgdatDigServiceData *svcdat, HsvCamNITService *Service)
{
	svcdat->Tsid				=	Service->TsId;
	svcdat->OriginalNetworkId   =	Service->OriginalNetworkId;
    svcdat->ServiceId			=	Service->ServiceId;
	svcdat->ServiceType			=	Service->ServiceType;
	svcdat->VisibleService   	=	Service->VisibleServiceFlag;
	svcdat->NumericSelect		= 	Service->SelectableServiceFlag;
	svcdat->LCN					=	Service->LogicalChannelNumber;
	
	mCopyString( svcdat->ChannelName, Service->ServiceName, (eurdiv_PresetNameLength - 1) );
	
}

Nat8 CHsvDvbCamInstallation_mDataAcq_Priv::mGetDvbType(int DecoderType)
{
	Nat8 Retval = 0;
	
	if(DecoderType == feapi_ChanDecDvbC)
	{
		Retval = AppApiDvbTypeC;
	}
	else if( (DecoderType == feapi_ChanDecDvbT) || (DecoderType == feapi_ChanDecDvbT2) )
	{
		Retval = AppApiDvbTypeT;
	}	
	
	return Retval;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mAddToTSTable(HsvInstallationPTC *ptc, Nat16 OriginalNetworkId, Nat16 TsId,Bool isBarker)
{
    HsvPgdatDigTSData   tsdata, tmptsdata;
	HSVSPTYPE(CamNITLinkageInfo, dvb, camnit) NitLinkageData;

//        if(strapi_GetByIndex(HsvMain, , i, (void*)(&ServiceList)))
	
    tsdata.Frequency                = ptc->Frequency;
    tsdata.SymbolRate               = ptc->SymbolRate;
    tsdata.DecoderType              = ptc->DecoderType;     
    tsdata.OriginalNetworkId        = OriginalNetworkId;
    tsdata.Tsid                     = TsId;
    tsdata.NetworkId                = 0;
    tsdata.ModulationType           = ptc->ModulationType;
    tsdata.CodeRate                 = ptc->CodeRateHigh;
    tsdata.HierarchyMode            = ptc->HierarchyMode;
    tsdata.GuardInterval            = ptc->GuardInterval;
    tsdata.TxMode                   = ptc->TxMode;
    tsdata.IqMode                   = ptc->IqMode;
    tsdata.Bandwidth         		= ptc->ChannelBandwidth;
    tsdata.StreamPriority           = ptc->StreamPriority; 
    tsdata.TimeError                = ptc->TimeError;
    tsdata.FrequencyError           = ptc->FrequencyError;
    tsdata.FrequencyOffset          = ptc->FrequencyOffset;
    tsdata.PtcListVersion           = 0;
    tsdata.VSignalStrength          = ptc->VSignalStrength;
    tsdata.ASignalStrength          = ptc->ASignalStrength;
    tsdata.QSignalStrength          = ptc->QSignalStrength;
    tsdata.ChannelInformation       = ptc->ChannelInformation;
    tsdata.CDSDFrequency            = ptc->CDSDFrequency;
    tsdata.UserInstalled            = FALSE;
    tsdata.TSVersion                = 0;
    tsdata.NITVersion               = 0;
    tsdata.SDTVersion               = 0;
    tmptsdata.Frequency             = tsdata.Frequency;
    tmptsdata.StreamPriority        = tsdata.StreamPriority;
	tsdata.BarkerMux 			= isBarker;
    if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE ) 
    {
        pgdb_Add( PTC_TABLE, (Address )&tsdata);
    }
    else
    {
        pgdb_Update( PTC_TABLE, (Address )&tsdata);
    }
}

Bool CHsvDvbCamInstallation_mDataAcq_Priv::mDuplicateEntry(HsvPgdatDigServiceData svcdat, int tableid)
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
                if(svcdat.LCN == svcdat2.LCN)
                {
                    retval = TRUE;
                }
            }
        }
    }

    return retval;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mCheckAndNotifyAttributeChange (HsvPgdatDigServiceData* newsvcdat, HsvPgdatDigServiceData* cursvcdat)
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
Bool CHsvDvbCamInstallation_mDataAcq_Priv::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc)
{
    Bool retval = FALSE;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData tmpsvcdat;

    mAssignServiceBroadcastAttributes(psvcdat, ptc);
    mAssignServiceNonBroadcastAttributes(psvcdat);
	
    if(mOperatorProfileInstallRules(psvcdat) == TRUE)
    {
        //ASSIGN_KEYS_OF_SVC(tmpsvcdat, (*psvcdat));
		ASSIGN_KEYS_OF_CAM_SVC(tmpsvcdat, (*psvcdat));
		TraceNotice(m,"psvcdat %d %d %d %d %d %d", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, psvcdat->LCN, psvcdat->Frequency, psvcdat->StreamPriority);
        if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tmpsvcdat) == TRUE)
        {
            if(BACKGROUND_CAM_INSTALL)
            {
                mCheckAndNotifyAttributeChange (psvcdat, &tmpsvcdat);
            }
            pgdb_Update( SERVICE_TABLE, (Address)psvcdat);
			
			TraceNotice(m,"Updated Service %d %d %d %d ", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, psvcdat->LCN);
        }
        else
        {
			TraceNotice(m,"@ 233 psvcdat %d %d %d %d %d %d", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, psvcdat->LCN, psvcdat->Frequency, psvcdat->StreamPriority);
            if(mDuplicateEntry(*psvcdat, SERVICE_TABLE) == FALSE)
            {			
                pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
				
				TraceNotice(m,"Added Service %d %d %d %d ", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, psvcdat->LCN);
                sort_UpdateDigitalPreset(psvcdat);
            }
        }

        retval = TRUE;
    }
    else
    {
        presetdat.PresetNumber =   psvcdat->PresetNumber;       
        pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
        pgdb_Delete(SERVICE_TABLE, (Address)psvcdat);
		
		TraceNotice(m,"Deleted Service PresetNumber %d %d %d %d %d ", psvcdat->PresetNumber, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, psvcdat->LCN);
    }
    
    return retval;
}

Bool CHsvDvbCamInstallation_mDataAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc)
{
    Bool retval = FALSE;

    mAssignServiceBroadcastAttributes(psvcdat, ptc);
    mAssignServiceNonBroadcastAttributes(psvcdat);

    if(mOperatorProfileInstallRules(psvcdat) == TRUE)
    {
        Bool ret = pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
		
		TraceNotice(m,"Added Service %d %d %d %d ret %d", psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, psvcdat->LCN, ret);
        mDigitalChannelsFound++;
        retval = TRUE;
    }

    return retval;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mAssignServiceBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc)
{
    HsvPATProgramPIDInfo val;
    
	psvcdat->Frequency             =   ptc->Frequency;
    psvcdat->ModulationType        =   ptc->ModulationType;
    psvcdat->Bandwidth      	   =   ptc->ChannelBandwidth;
    psvcdat->StreamPriority        =   ptc->StreamPriority;
    psvcdat->SymbolRate            =   ptc->SymbolRate;
    psvcdat->DecoderType           =   ptc->DecoderType;
    psvcdat->Type                  =   GETSERVICETYPE(psvcdat->ServiceType);
    psvcdat->FreeCiMode            =   psvcdat->MatchBrandFlag = psvcdat->NumBrandIds = psvcdat->NetworkId = 0;
	psvcdat->AudioPid 			   =   psvcdat->VideoPid = psvcdat->PcrPid = INVALID_PID;
    psvcdat->DvbType               =   mGetDvbType(ptc->DecoderType);;    
    psvcdat->OUI                   =   0;
    psvcdat->SystemHidden          =   (!(psvcdat->VisibleService));
	psvcdat->SrcambledStatus       =   1;
	psvcdat->ScramblingStatus      =   1;
	
	if( strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)) )
    {
        psvcdat->PmtPid            =   val.Pid;
    }
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mAssignServiceNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat;
    
    psvcdat->UserHidden             = FALSE;
    psvcdat->ChannelLock            = FALSE;
    psvcdat->Favorite               = FALSE;
    psvcdat->PreferredStereo        = 1;
    psvcdat->ServiceListVersion     = 0;
    psvcdat->HbbTvOption            = 1;
    psvcdat->NewChannelMap          = 1;
	psvcdat->PresetNumber           = INVALID_PRESET;
	psvcdat->NewPreset              = BACKGROUND_CAM_INSTALL;
	
    psvcdat->DateStamp = (Timerclk_IsClockDefined())? Timerclk_GetUniversalTime() : 0;
    
	ASSIGN_KEYS_OF_CAM_SVC(svcdat, (*psvcdat)); 
    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
    {
        mRetainNonBroadcastAttributes(psvcdat, svcdat);
        
		psvcdat->UserModifiedName = svcdat.UserModifiedName;
		if(psvcdat->UserModifiedName == TRUE)
		{
			/* This means user has renamed the service, so retain it */
			mCopyString( psvcdat->ChannelName, svcdat.ChannelName, (eurdiv_PresetNameLength - 1) );
		}
		
        if(psvcdat->LCN != svcdat.LCN)
        {
            /* Below done, because the LCN changes or service Type (Radio/TV vice versa) presets are sorted freshly */            
			TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->LCN, svcdat.LCN, svcdat.PresetNumber);
            presetdat.PresetNumber =   svcdat.PresetNumber;
            presetdat.Type         =   HsvOnePart;
			
            pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
            psvcdat->PresetNumber = INVALID_PRESET;
        }
    }
    else
    {
        if(BACKGROUND_CAM_INSTALL)
        {
            /* Primary keys might have changed check */
            mDeleteDuplicateRecords(psvcdat);
        }
    }
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; (i < maxchars) && (*src); i++)
    {
        *dest++ = *src++;
    }
    *dest = 0;
}

Bool CHsvDvbCamInstallation_mDataAcq_Priv::mOperatorProfileInstallRules(HsvPgdatDigServiceData *svcdat)
{
    Bool retval = FALSE;

    TraceInfo(m,"%s ServiceId %d LCN %d", __FUNCTION__, svcdat->ServiceId, svcdat->LCN);
    
	/* Rule 1: Valid LCN */
	if( VALID_CAM_LCN_RANGE(svcdat->LCN) )
    {
        retval = TRUE;
    }

	/* Rule 2: of conflicting LCNs are handled implicitly in strapi database of sdm data population as is LCN as a key for CamNITService */
	
    return retval;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mAddToFreqMapTable(HsvInstallationPTC ptc, Nat16 OriginalNetworkId, Nat16 TsId)
{
    /* write to freqmaptable */
    HsvPgdatDigFreqMapData    freqdat;
    HsvPgdatDigFreqMapData    tmpfreqdat;
    Bool retval;

    freqdat.OriginalNetworkId   = OriginalNetworkId;
    freqdat.Tsid                = TsId;
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

Bool CHsvDvbCamInstallation_mDataAcq_Priv::mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat)
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
                (svcdat->ServiceId         == svcdat2.ServiceId) )
            {
                mRetainNonBroadcastAttributes(svcdat, svcdat2);                
				mCopyString( svcdat->ChannelName, svcdat2.ChannelName, (eurdiv_PresetNameLength - 1) );
                pgdb_Delete(SERVICE_TABLE,(Address) &svcdat2);
				
                retval = TRUE;
                break;
            }
        }
    }
    return retval;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat)
{
    /* Retain the non broadcast attributes during background install */
	
	psvcdat->NewPreset 				=  svcdat.NewPreset;
   	psvcdat->PresetNumber           =  svcdat.PresetNumber;
    psvcdat->EPGEnabled             =  svcdat.EPGEnabled;
    psvcdat->ChannelLock            =  svcdat.ChannelLock;;
    psvcdat->UserHidden             =  svcdat.UserHidden;
    psvcdat->Favorite               =  svcdat.Favorite;
    psvcdat->FavoriteNumber         =  svcdat.FavoriteNumber;
    psvcdat->ServiceListVersion     =  svcdat.ServiceListVersion;
    psvcdat->HbbTvOption            =  svcdat.HbbTvOption;
    psvcdat->EPGShortInfo           =  svcdat.EPGShortInfo;
    psvcdat->SAP                    =  svcdat.SAP;
    psvcdat->DeltaVolume            =  svcdat.DeltaVolume;
    psvcdat->UserModifiedName       =  svcdat.UserModifiedName;
    psvcdat->PreferredStereo        =  svcdat.PreferredStereo;
    psvcdat->HMBlanked              =  svcdat.HMBlanked;
    psvcdat->HMProtectedChannel     =  svcdat.HMProtectedChannel ;
    psvcdat->HMMapChannelNo         =  svcdat.HMMapChannelNo;
    psvcdat->LogoURL                =  svcdat.LogoURL;
    psvcdat->VideoPid               =  svcdat.VideoPid;              
    psvcdat->AudioPid               =  svcdat.AudioPid;
    psvcdat->PcrPid                 =  svcdat.PcrPid;    
    psvcdat->VideoStreamType        =  svcdat.VideoStreamType;
    psvcdat->AudioStreamType        =  svcdat.AudioStreamType;
    psvcdat->SecAudioStreamType     =  svcdat.SecAudioStreamType;
    psvcdat->SecAudioPid            =  svcdat.SecAudioPid;
	
}

Bool CHsvDvbCamInstallation_mDataAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;
    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}
	return retval;
}

/**********************************************
  provides IHsvDigitalAcquisition  idataacq
 **********************************************/

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_Initialise()
{
    mCamNITVersion = 0;

    memset((Address)&mCamServiceList, 0, sizeof(mCamServiceList));
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_InitialiseTotalChannels()
{
    mDigitalChannelsFound = 0;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_AcquireData()
{
	TraceNotice(m,"%s", __FUNCTION__);
    mInstallMuxs();
}

/* delete those services which are not in CAM NIT service descriptor */
void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_DeleteServices(void)
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
            for(i = 0; i < mCamServiceList.NumOfRecords; i++)
            {
                if( (svcdat.OriginalNetworkId  == mCamServiceList.ServiceInfo[i].OriginalNetworkId) &&
                    (svcdat.Tsid               == mCamServiceList.ServiceInfo[i].TsId) &&
                    (svcdat.ServiceId          == mCamServiceList.ServiceInfo[i].ServiceId) )
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

int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound()
{
	TraceNotice(m, "%s %d", __FUNCTION__, mDigitalChannelsFound);
    return mDigitalChannelsFound;
}
int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}
int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannels(int servicetype)
{
    UNUSED(servicetype);
	TraceNotice(m, "%s %d", __FUNCTION__, mDigitalChannelsFound);
    return mDigitalChannelsFound;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_AcquireServiceListData()
{
    HSVSPTYPE(CamNITService, dvb, camnit) ServiceList;
    int i = 0, NoOfRecords = strapi_GetSize(HsvMain, HSVSPID(CamNITService, dvb, camnit));
	
    mCamServiceList.NumOfRecords = 0;
    for(i = 0 ; i < NoOfRecords; i++)
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(CamNITService, dvb, camnit), i, (void*)(&ServiceList)))
        {
            mCamServiceList.ServiceInfo[i] = ServiceList;
			mCamServiceList.VersionNumber  = mCamNITVersion;
			mCamServiceList.NumOfRecords++;
			
			TraceNotice(m,"%d %d %d %d mCamServiceList.NumOfRecords %d", mCamServiceList.ServiceInfo[i].OriginalNetworkId, mCamServiceList.ServiceInfo[i].TsId, mCamServiceList.ServiceInfo[i].ServiceId, mCamServiceList.ServiceInfo[i].LogicalChannelNumber, mCamServiceList.NumOfRecords);
        }
    }
	
	
}


/*****   Stub Interfaces  *****/
int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNextSampleProgram               (   void    ) 
{
	return 0;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_StartBackgroundInstall             (   void    ) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_ResetBackgroundInstall             (   void    ) 
{
	return;
}

Bool CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_IsNetworkUpdateDetected            (   void    ) 
{
	return FALSE;
}


int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNetworkIDList(void) 
{
	return 0;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNetworkIDName(int index, Nat16 *NetworkName) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_SetFavouriteNetworkID(int mode, int attrib, int index) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_ClearNetworkNameCache(void) 
{
	return;
}

Bool CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_IsLCNValid() 
{
	return FALSE;
}

/*void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_AcquireOriginalNetworkId() 
{
	return;
}*/

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_SyncTemporaryTableRecords(void) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_ClearCache(void) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetRegionList(HsvNetworkRegionsData *RegionsData) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType) 
{
	return;
}

int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType) 
{
	return 0;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_Enable() 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_Disable() 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetCachedRegionDetails(HsvTargetRegionCache * RegionCache) 
{
	return;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_AcquireLCNData(void){
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_AcquireONID(void){
}


void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_UpdateBarkerMuxInfo(Nat16 onid, Nat16 tsid){
    HsvPgdatDigTSData   tmptsdata;
	int index, NoOfRecs = 0;
	HsvInstallationPTC ptc;
	TraceNotice(m,"idataacq_UpdateBarkerMuxInfo [%d] [%d] \n",onid,tsid);
	NoOfRecs = pgdb_GetNoRecords(PTC_TABLE);
	for(index = 0; index < NoOfRecs; index++)
	{
    	if( pgdb_GetByIndex(PTC_TABLE, index, (Address )&tmptsdata)) 
    	{
    		TraceNotice(m,"PGDB query is success");
			if((onid == tmptsdata.OriginalNetworkId) && (tsid == tmptsdata.Tsid))
			{
				TraceNotice(m,"Onid & tsid matches!! ");
				updateBarkerMuxDvbCamins = TRUE;
				tmptsdata.BarkerMux             = true;
				pgdb_Update(PTC_TABLE,&tmptsdata);
				break;
			}
		}
	}

	if(updateBarkerMuxDvbCamins == FALSE)
	{
		NoOfRecs = pgdb_GetNoRecords(FREQMAP_TABLE);
		HsvPgdatDigFreqMapData    tmpfreqdat;
		for(index = 0; index < NoOfRecs; index++)
		{
			if( pgdb_GetByIndex(FREQMAP_TABLE, index, (Address )&tmpfreqdat)) {
				TraceNotice(m,"PGDB query is success in freq map table");
				if((onid == tmpfreqdat.OriginalNetworkId) && (tsid == tmpfreqdat.Tsid))
				{		
					ptc.Frequency          	= tmpfreqdat.Frequency;
					ptc.SymbolRate		   	= tmpfreqdat.SymbolRate;
					ptc.ModulationType		= tmpfreqdat.ModulationType;
					ptc.DecoderType		   	= tmpfreqdat.DecoderType;
					ptc.DecoderType		   	= tmpfreqdat.DecoderType;
					ptc.HierarchyMode		=	HsvHierarchyNone;
					ptc.GuardInterval		=	HsvGuardIntervalAuto;
					ptc.TxMode 				=	HsvTxModeAuto;			 
					ptc.IqMode 				=	HsvIqModeNormal;
					ptc.CodeRateHigh		=	ptc.CodeRateLow = HsvCodeRateAuto;
					ptc.ChannelInformation 	=   ptc.TimeError   = ptc.FrequencyError = ptc.FrequencyOffset = 0;
					ptc.StreamPriority 		= 0;
					Bool isBarker = TRUE;
					TraceNotice(m,"adding ts table with barker data as TRUE");
					mAddToTSTable(&ptc, onid, tsid,TRUE);
					updateBarkerMuxDvbCamins = TRUE;
					TraceNotice(m,"Added new TS entry into TS table");
				}
			}
		}
	}

	TraceNotice(m,"idataacq_UpdateBarkerMuxInfo [%d] [%d] \n",onid,tsid);
}

int CHsvDvbCamInstallation_mDataAcq_Priv::pcamhelper_GetCamInstallationMode(void)
{
	return 0;
}
void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetChannelListIDName(int index, Nat16*ChannelistName)        
{
   return;
}
int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannelListIds()        
{
    return 0;
}

int CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_GetChannelListIdByIndex(int index)
{
   return 0;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_SetFavouriteChannelListId(int mode, int attrib, int index)     
{
   return;
}
void CHsvDvbCamInstallation_mDataAcq_Priv::idataacq_AcquireSDTOtherData()
{
	return;
}
void CHsvDvbCamInstallation_mDataAcq_Priv::pcamhelper_SetCharacterCode(char* charCode)
{
	Nat8 charCodeFromCam = 0, prestoredCharCode = 0;
	/*if((idvbset_GetAttribute(AUTO_MODE,rins_AttributeNetworkOperator)  == rins_DvbCCAM) || (idvbset_GetAttribute(AUTO_MODE,rins_AttributeNetworkOperator)  == rins_DvbTCAM))
	{

		charCodeFromCam = mFindTableCode((Nat8 *)charCode);
		FirstByte = charCodeFromCam;
		TraceNotice(m,"Character code from Cam after conversion is %d before conversion is %d %d %d",charCodeFromCam,charCode[0],charCode[1],charCode[2]);
		prestoredCharCode = (Nat8)idvbset_GetAttribute(AUTO_MODE, rins_Attributecamcharset);
		if((charCodeFromCam != prestoredCharCode) || ((charCodeFromCam == 0x00) && (prestoredCharCode == 0)))
		{
              	msetCharacterCode(charCodeFromCam,prestoredCharCode);
			idvbset_SetAttribute(AUTO_MODE, rins_Attributecamcharset, charCodeFromCam);
			TraceNotice(m,"New character code set stored \n");
		}
	}
	else
	{
		TraceNotice(m,"Not a cam profile.. so don't do anything \n");
	}*/
	return ;
}

void CHsvDvbCamInstallation_mDataAcq_Priv::msetCharacterCode(Nat8 charCodeFromCam,Nat8 prestoredCharCode)
{
    Bool retval = FALSE;
    HsvPgdatDigServiceData svcdat2;
    HsvPgdatDigServiceData svcdatTemp;
    int j, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    Nat8 stringName[MAX_TEXT_LENGTH +1];
    int stringLength = eurdiv_PresetNameLength - 1;
 /*   for(j = 0; j < noOfRecs; j++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, j, (Address)&svcdat2) == TRUE )
        {*/
            /* check for triplet key & decoder type */
		/*  if(ling_WcToMb(prestoredCharCode, svcdat2.ChannelName, (eurdiv_PresetNameLength - 1), stringName, &stringLength) != 0)
		  {
		         TraceNotice(m,"Error in conversion from Unicode to Iso code\n");
		         break;
		  }
		  else
		  {
		       Nat8 tempStringName[MAXSERVICENAMELEN];
			tempStringName[0] = charCodeFromCam;
			for(int i=1;i<eurdiv_PresetNameLength;i++)
				tempStringName[i] = stringName[i-1];
			//strncpy(tempStringName[3],stringName,stringLength);
		       int tempLen = (eurdiv_PresetNameLength - 1);
		       TraceNotice(m,"Conversion success \n");
			//charsetutil_MbToWc( tempStringName, stringLength, svcdatTemp.ChannelName, (eurdiv_PresetNameLength - 1), FALSE);
			//charsetutil_MbToWcEx(charCodeFromCam, stringName, stringLength, svcdatTemp.ChannelName, &tempLen,FALSE);
			ling_MbToWcEx(charCodeFromCam, stringName,stringLength, svcdat2.ChannelName, &stringLength, TRUE);
		  	mCopyString( svcdatTemp.ChannelName, svcdat2.ChannelName, (eurdiv_PresetNameLength - 1) );
                	pgdb_Update(SERVICE_TABLE,(Address) &svcdat2);
		  }
            }
        }*/
}
Bool CHsvDvbCamInstallation_mDataAcq_Priv::pcamhelper_CamNitParser_Parser( HsvDestination   dest,  Nat32 cookie, int DataSize, Nat8 * DataPtr)
{
return TRUE;
}

/*  
    From ETSI EN 300 468, table A3 (single byte character table codes):
    0x01 = ISO 8859-5
    0x02 = ISO 8859-6
    0x03 = ISO 8859-7
    0x04 = ISO 8859-8
    0x05 = ISO 8859-9
    0x06 = ISO 8859-10
    0x07 = ISO 8859-11
    0x09 = ISO 8859-13
    0x0a = ISO 8859-14
    0x0b = ISO 8859-15
    0x10 = (3 byte encoding, see table A4)
    0x11 = ISO 10646 (Basic Multilingual Plane)
    0x12 = KSX1001-2004 (Korean)
    0x13 = GB-2312-1980 (Simplified Chinese)
    0x14 = Big5 subset of ISO 10646
    0x15 = UTF8 encoding of ISO 10646 

    From ETSI EN 300 468, table A4 (three byte character table codes):
    0x10 0x00 0x01 = ISO 8859-1
    0x10 0x00 0x02 = ISO 8859-2
    0x10 0x00 0x03 = ISO 8859-3
    0x10 0x00 0x04 = ISO 8859-4
    0x10 0x00 0x05 = ISO 8859-5
    0x10 0x00 0x06 = ISO 8859-6
    0x10 0x00 0x07 = ISO 8859-7
    0x10 0x00 0x08 = ISO 8859-8
    0x10 0x00 0x09 = ISO 8859-9
    0x10 0x00 0x0a = ISO 8859-10
    0x10 0x00 0x0b = ISO 8859-11
    0x10 0x00 0x0d = ISO 8859-13
    0x10 0x00 0x0e = ISO 8859-14
    0x10 0x00 0x0f = ISO 8859-15

    From cesgpi_mwchar.c (tvApp), resulting table codes (that we are converting to) are:
    0x00 = ISO 6937
    0x01 = ISO 8859-5 
    0x02 = ISO 8859-6 
    0x03 = ISO 8859-7 
    0x04 = ISO 8859-8 
    0x05 = ISO 8859-9
    0x06 = ISO 8859-2
    0x07 = ISO 8859-15
    0x08 = ISO 8859-4
    0x09 = ISO 8859-13
    0x11 = ISO/IEC 10646-1 
    0x13 = Chinese charater set GB2312 mixed up with english
    0x15 = UTF8 encoding of ISO 10646 
    */
Nat8 CHsvDvbCamInstallation_mDataAcq_Priv::mFindTableCode(Nat8* str)
{
    Nat8 charCode = DEFAULT_CHAR_SET;

    switch (*str)
    {
        case 0x00:
        case 0x01: 
        case 0x02: 
        case 0x03: 
        case 0x04: 
        case 0x05:
        case 0x09:
        case 0x11:
        case 0x13:
        case 0x15:
            /* these single byte table IDs map directly */
            charCode = *str;
            break;
        case 0x0b:
            charCode = 0x07;
            break;
        case 0x10:
            {
                int nextCode = ((str[1] << 8) | (str[2]));
                switch (nextCode)
                {
                    case 0x0002: 
                        charCode = 0x06;
                        break;            
                    case 0x0004: 
                        charCode = 0x08;
                        break;            
                    case 0x0005: 
                        charCode = 0x01;
                        break;            
                    case 0x0006: 
                        charCode = 0x02;
                        break;            
                    case 0x0007: 
                        charCode = 0x03;
                        break;            
                    case 0x0008:
                        charCode = 0x04;
                        break;            
                    case 0x0009: 
                        charCode = 0x05;
                        break;            
                    case 0x000d: 
                        charCode = 0x09;
                        break;            
                    case 0x000f: 
                        charCode = 0x07;
                        break;            
                    default:
                        break;            
                }
            }
            break;
        default:
			/* brg36mgr#158094: When the predefined character code is not present, 
				fallback to DEFAULT_CHAR_SET */
			if(!(*str >= 0x20))
			{
				ASSERT(!"Unsupported Character set in the stream");
			}
            break;            
    }


    return charCode;
}

