/**********************************************************************
 *
 *   C Source:       hsvdvbtmpegins_mdigacq.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    aneeshc %
 *   %date_created:  Sat Apr 07 13:25:14 2012 %
 *
 **********************************************************************/
#include "_hsvdvbtmpegins_mdigacq.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtmpegins_mdigacq")

#include<string.h>





int CHsvDvbtMpegInstallation_mdigacq_Priv::s__mInsMedium;

Nat16 CHsvDvbtMpegInstallation_mdigacq_Priv::s__mCurrentPresetIndex;

Bool CHsvDvbtMpegInstallation_mdigacq_Priv::s__mIsChannelListUpdated = FALSE;





TypeInstallationStatus CHsvDvbtMpegInstallation_mdigacq_Priv::s__InsStatus;


void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_Initialise (void)
{
    mCurrentPresetIndex             =   1;
	/* This is removed because intialisetotalchannels will be done from hsveuins_m
		at the start of installation */
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_InitialiseTotalChannels( void )
{
    InsStatus.DigitalChannelsFound  =   0;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_AcquireData ( void )
{   
    /* Call Back once a TS is acquired by SDM */
    HsvInstallationPTC    ptc;
    HsvPgdatDigTSData   tsdat;

	mIsChannelListUpdated = FALSE;
    idigscan_GetPTCInfo(&ptc);
    mInsMedium = rins_GetMedium();
    tsdat.Frequency     =   ptc.Frequency;
    tsdat.StreamPriority   =   ptc.StreamPriority;

    TraceNotice (m," TS  (%d)\n", ptc.Frequency);
    if ( FALSE == pgdb_GetByKey(ANTENNA_PTC, (Address )&tsdat))
    {   /* New TS. Insert a Transport Stream */
        TraceNotice (m,"New TS  (%d)\n", ptc.Frequency);
        if(TRUE == AddServices(&ptc))
        {
            tsdat.Frequency            =   ptc.Frequency;            
            tsdat.OriginalNetworkId    =   0xFFFF;
            tsdat.Tsid                 =   0xFFFF;
            tsdat.NetworkId            =   0xFFFF;
            tsdat.ModulationType       =   ptc.ModulationType;            
            tsdat.HierarchyMode        =   ptc.HierarchyMode;
            tsdat.GuardInterval        =   ptc.GuardInterval;
            tsdat.TxMode               =   ptc.TxMode;
            tsdat.IqMode               =   ptc.IqMode;
            tsdat.Bandwidth     =   ptc.ChannelBandwidth;
            tsdat.StreamPriority       =   ptc.StreamPriority;
            tsdat.TimeError            =   ptc.TimeError;
            tsdat.FrequencyError       =   ptc.FrequencyError;
            tsdat.FrequencyOffset      =   ptc.FrequencyOffset;
            tsdat.PtcListVersion       =   rins_GetInstallationVersion();
            tsdat.VSignalStrength      =   ptc.VSignalStrength;
            tsdat.ASignalStrength      =   ptc.ASignalStrength;
            tsdat.QSignalStrength      =   ptc.QSignalStrength;
            tsdat.ChannelInformation   =   ptc.ChannelInformation;
            tsdat.TSVersion            =   INVALID_VALUE;
            tsdat.UserInstalled     =   (MANUAL_INSTALL) ? TRUE : FALSE;
            tsdat.CodeRate             =   (tsdat.StreamPriority  == HsvStreamPriorityHigh ) ? ptc.CodeRateHigh: ptc.CodeRateLow;
            tsdat.DecoderType          =   ptc.DecoderType;
            tsdat.SymbolRate           =   ptc.SymbolRate;

            pgdb_Add( ANTENNA_PTC, (Address )&tsdat);
        }
    }
    else
    {   
        /* TS Exists in DB */
        Bool UpdateTransportStream = (MANUAL_INSTALL) ? TRUE : FALSE;

        TraceNotice (m,"TS Exists in DB (%d)\n", ptc.Frequency);
        if(!UpdateTransportStream)
        {
            switch (rins_GetInstallationMode())
            {
                case rins_InstallationModeBackground:
                    //if ( tsdat.TSVersion != DigInsStatus.TsVersionNumber ) 
                    {
                        UpdateTransportStream = TRUE;
                    }
                    break;
                case rins_InstallationModeAutomatic:
                    {
                        /* Do Nothing, With the new definition of unique entires in PTC is based on
                           <frequency,streampriority>,you will never encounter two such entries
                           during Automatic Installation */
                        /* ASSERT(!"Duplicate entries of PTCs during Automatic installation is not possible"); */
                    }
                    break;
                case rins_InstallationModeUpdate:
                    if ( rins_GetInstallationVersion() != tsdat.PtcListVersion  )
                    {   /* Different Pass..indeed we need to update */
                        if(! tsdat.UserInstalled)
                        {   /* Dont touch manually installed channels */
                            UpdateTransportStream = TRUE;
                        }
                    }
                    break;
                default:
                    instutil_LogError( log_SoftErr, INS_INVALID_SWITCH_CASE ); /*log the error */
                    break;
            }
        }

        /* Update Transport Stream data */
        if(UpdateTransportStream && (TRUE == AddServices(&ptc)))
        {
            /* Dont copy primary keys during updation */

            tsdat.OriginalNetworkId    =   0xFFFF;
            tsdat.Tsid                 =   0xFFFF;
            tsdat.ModulationType       =   ptc.ModulationType;
            tsdat.CodeRate             =   ptc.CodeRateHigh;
            tsdat.HierarchyMode        =   ptc.HierarchyMode;
            tsdat.GuardInterval        =   ptc.GuardInterval;
            tsdat.TxMode               =   ptc.TxMode;
            tsdat.IqMode               =   ptc.IqMode;
            tsdat.Bandwidth     =   ptc.ChannelBandwidth;
            tsdat.StreamPriority       =   ptc.StreamPriority;
            tsdat.TimeError            =   ptc.TimeError;
            tsdat.FrequencyError       =   ptc.FrequencyError;
            tsdat.FrequencyOffset      =   ptc.FrequencyOffset;
            tsdat.VSignalStrength      =   ptc.VSignalStrength;
            tsdat.ASignalStrength      =   ptc.ASignalStrength;
            tsdat.QSignalStrength      =   ptc.QSignalStrength;
            tsdat.ChannelInformation   =   ptc.ChannelInformation;
            tsdat.PtcListVersion       =   rins_GetInstallationVersion();
            tsdat.TSVersion            =   INVALID_VALUE;
            tsdat.NetworkId            =   0xFFFF;
            tsdat.UserInstalled        =   (rins_InstallationModeWeakSignal == rins_GetInstallationMode()) ? TRUE : FALSE;
            tsdat.CodeRate             =   (tsdat.StreamPriority  == HsvStreamPriorityHigh ) ? ptc.CodeRateHigh: ptc.CodeRateLow;

            TraceNotice (m,"Updated TS Information for (%d)\n", ptc.Frequency);

            pgdb_Update( ANTENNA_PTC, (Address )&tsdat);
        }
        else
        {
            TraceNotice (m,"Better Freq. for TS (%d) exists\n", ptc.Frequency);
            /* Do Nothing */
        }
    }

}


Bool CHsvDvbtMpegInstallation_mdigacq_Priv::AddServices ( HsvInstallationPTC *ptc )
{
    HsvDestination dest = HsvMain;
    Bool retval = FALSE;
    int i;
    int noofservices = strapi_GetSize (dest, HSVSPID(Program, mpeg, pat));
    int noofservicesinstalled = 0;

    for(i = noofservices - 1; i >= 0 ; i--)
    {
        HSVSPTYPE(Program, mpeg, pat) service;
        if(TRUE == strapi_GetByIndex(dest, HSVSPID(Program, mpeg, pat), i, (void *)(&service)))
        {
            if(TRUE == AddService (ptc, &service))
            {
                noofservicesinstalled++;
                retval = TRUE;
            }
        }
    }

    TraceNotice (m,"Installed %d services\n", noofservicesinstalled);

    return retval;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNumberOfDigitalChannelsFound(void)
{
    int retval = 0;
    if(AUTO_INSTALL || MANUAL_INSTALL || UPDATE_INSTALL)
    {
        retval = InsStatus.DigitalChannelsFound;
        TraceNotice (m,"%s %d DigitalChannelsFound : %d\n", __FUNCTION__, __LINE__, InsStatus.DigitalChannelsFound);
    }
    return retval;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNumberOfChannels( int servicetype )
{
    UNUSED(servicetype);
    return 0;
}

/****ITaly redesign changes ********/
Bool CHsvDvbtMpegInstallation_mdigacq_Priv::AddService (HsvInstallationPTC *ptc, HSVSPTYPE(Program, mpeg, pat) *service)
{
    int indx, from = -1, to = -1;
    Bool retval = FALSE, ChannelExists = FALSE;
    HsvPgdatDigServiceData svcdat;
    HsvPgdatDigServiceData svcdat_temp;

    pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));

    svcdat.OriginalNetworkId     =  0xFFFF;
    svcdat.ServiceId             =  service->ProgramNumber;
    svcdat.Frequency             =  ptc->Frequency;
    svcdat.ModulationType        =  ptc->ModulationType;
    svcdat.Bandwidth      =  ptc->ChannelBandwidth;
    svcdat.StreamPriority        =  ptc->StreamPriority;
    svcdat.Tsid                  =  0xFFFF;
    svcdat.DuplicateSvc          =  0;

    if(pgdb_GetRange( DIGITAL_SERVICE, 2,(Address)&svcdat, &from, &to))
    {
        for (indx = from; indx <= to ; indx++)
        {
            if(pgdb_GetByIndex( DIGITAL_SERVICE, indx, (Address)&svcdat_temp ))
            {
                if(DuplicateEntry(&svcdat,&svcdat_temp))
                {
                    ChannelExists = TRUE;
                    break;
                }
            }
        }
    }
    if(!ChannelExists)
    {
    	mIsChannelListUpdated = TRUE;
        AddNewService(&svcdat,ptc,service);
        retval = TRUE;
    }
    else
    {
        if(MANUAL_INSTALL)
        {
            InsStatus.DigitalChannelsFound++;
            sort_UpdateDigitalPreset(&svcdat_temp);
        }
    }
    return retval;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::AddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(Program, mpeg, pat) *service)
{
    HsvPATProgramPIDInfo    val;

    psvcdat->AudioPid              =   INVALID_PID;
    psvcdat->VideoPid              =   INVALID_PID;
    psvcdat->PcrPid                =   INVALID_PID;
    psvcdat->PresetNumber          =   INVALID_PRESET;
    psvcdat->ServiceId             =   service->ProgramNumber;
    psvcdat->OriginalNetworkId     =   0xFFFF;
    psvcdat->Frequency             =   ptc->Frequency ;
    psvcdat->OUI                   =   HsvOUI_Last;
    psvcdat->VisibleService        =   TRUE;
    psvcdat->ServiceListVersion    =   rins_GetInstallationVersion();
    psvcdat->ServiceType           =   AppApiTelevisionService;
    psvcdat->Type                  =   HsvOnePart;
    psvcdat->DecoderType           =   feapi_ChanDecDvbT;
    psvcdat->SymbolRate            =   DEFAULT_SYM_RATE;
    psvcdat->DvbType                =   AppApiDvbTypeTLite;
    psvcdat->ChannelLock            = 0;
    psvcdat->SystemHidden           = 0;
    psvcdat->UserHidden             = 0;
    psvcdat->Favorite               = 0;
    psvcdat->PreferredStereo        = 1;

    psvcdat->LCN                   =   mCurrentPresetIndex++;

    if(strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)))
    {
        psvcdat->PmtPid = val.Pid;

    }
    memset(psvcdat->ChannelName, 0, sizeof(psvcdat->ChannelName));
	mCopyString(psvcdat->ChannelName, instutil_AsciiToUnicode("-----", 5), 5);
    pgdb_Add( DIGITAL_SERVICE, (Address )psvcdat);

    InsStatus.DigitalChannelsFound++;

    TraceNotice (m,"Added Service LCN:%d ONID:%d SVCID:%d psvcdat->Frequency : %d\n",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->Frequency);

    if( BACKGROUND_INSTALL || UPDATE_INSTALL || MANUAL_INSTALL )
    {
        sort_AddDigitalPreset (psvcdat);
    }
}

inline void CHsvDvbtMpegInstallation_mdigacq_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; (i < maxchars) && (*src); i++)
    {
        *dest++ = *src++;
    }
    *dest = 0;
}

Bool CHsvDvbtMpegInstallation_mdigacq_Priv::DuplicateEntry(HsvPgdatDigServiceData *psvcdat1, HsvPgdatDigServiceData *psvcdat2)
{
    Bool retval = FALSE;

    TraceNotice (m,"%s %d psvcdat1->Tsid : %d psvcdat1->Frequency  : %d psvcdat1->StreamPriority : %d\n", __FUNCTION__, __LINE__, psvcdat1->Tsid, psvcdat1->Frequency, psvcdat1->StreamPriority);
    TraceNotice (m,"%s %d psvcdat2->Tsid : %d psvcdat2->Frequency  : %d psvcdat2->StreamPriority : %d\n", __FUNCTION__, __LINE__, psvcdat2->Tsid, psvcdat2->Frequency, psvcdat2->StreamPriority);
    if( (psvcdat1->OriginalNetworkId == psvcdat2->OriginalNetworkId) && 
            (psvcdat1->ServiceId == psvcdat2->ServiceId) &&
            (psvcdat1->Frequency == psvcdat2->Frequency) ) 
    {
        retval = TRUE;
    }
    return retval;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNumberOfDigitalChannelsRemoved() 
{
	return 0;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNextSampleProgram               (   void    ) 
{
	return 0;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_AcquireLCNData                     (   void    ) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_AcquireServiceListData             (   void    ) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_StartBackgroundInstall             (   void    ) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_ResetBackgroundInstall             (   void    ) 
{
	return;
}

Bool CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_IsNetworkUpdateDetected            (   void    ) 
{
	return mIsChannelListUpdated;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_DeleteServices                     (   void    ) 
{
	return;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNetworkIDList(void) 
{
	return 0;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNetworkIDName(int index, Nat16 *NetworkName) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_SetFavouriteNetworkID(int mode, int attrib, int index) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_ClearNetworkNameCache(void) 
{
	return;
}

Bool CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_IsLCNValid() 
{
	return FALSE;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_AcquireONID() 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_SyncTemporaryTableRecords(void) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_ClearCache() 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetRegionList(HsvNetworkRegionsData *RegionsData) 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType) 
{
	return;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType) 
{
	return 0;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_Enable() 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_Disable() 
{
	return;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetCachedRegionDetails(HsvTargetRegionCache * RegionCache) 
{
	return;
}
void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_UpdateBarkerMuxInfo(Nat16 onid, Nat16 tsid)
{
	return;
}
void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetChannelListIDName(int index, Nat16*ChannelistName)        
{
   return;
}
int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetNumberOfChannelListIds()        
{
    return 0;
}

int CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_GetChannelListIdByIndex(int index)
{
   return 0;
}

void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_SetFavouriteChannelListId(int mode, int attrib, int index)     
{
   return;
}
void CHsvDvbtMpegInstallation_mdigacq_Priv::idigacq_AcquireSDTOtherData()
{
	return;
}


