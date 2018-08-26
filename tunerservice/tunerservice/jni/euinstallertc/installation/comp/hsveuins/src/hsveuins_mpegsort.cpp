/**********************************************************************
 *
 *   C Source:       hsveuins_mpegsort.c
 *   Instance:       blr81mgr_1
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Tue Mar 27 14:17:12 2012 %
 *
 **********************************************************************/
#include "_hsveuins_mpegsort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mpegsort")




int CHsvEuropeInstallation_mpegsort_Priv::s__mFirstInstalledPreset;


/*****   PUMP PARAMETERS   *****/
Pump CHsvEuropeInstallation_mpegsort_Priv::s__mMpegSortPmp;



/*****   STATIC FUNCTIONS   *****/












void CHsvEuropeInstallation_mpegsort_Priv::mMpegSortHandler(int value, Nat32 param)
{
    UNUSED(param);

    if ((rins_GetLCNSortingControl() == FALSE) && (value != evSortComplete))
    {
        value = evNoSorting;
    }

    switch(value)
    {
        case evAnalogStep:
            TraceNotice (m,"%s %d\n", __FUNCTION__, __LINE__);
            AssignAnalogPresets();      
            break;
        case evDigitalStep:
            TraceNotice (m,"%s %d\n", __FUNCTION__, __LINE__);
            AssignDigitalPresets();
            break;
        case evSortComplete:
            TraceNotice (m,"%s %d\n", __FUNCTION__, __LINE__);
            sortN_OnEvent(sortN_EventSortComplete, TRUE);
            break;
        case evNoSorting:
            TraceNotice (m,"%s %d\n", __FUNCTION__, __LINE__);
            mNoSorting(value);
            break;
        default:
            TraceNotice (m,"Invalid Event : %d\n",value);
            break;
    }       
}

void CHsvEuropeInstallation_mpegsort_Priv::mNoSorting(int evCurrentSortStep)
{
    int dbindex = 0, noOfDigRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    int curPresetIndex = 0, noOfAnaRecs = pgdb_GetNoRecords(ANALOG_TABLE);
    int noOfPresetRecs = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatDigServiceData svcdat;

    TraceNotice(m,"%s: D %d A %d\r\n",__FUNCTION__, noOfDigRecs, noOfAnaRecs);

    for(dbindex = 0; dbindex < noOfPresetRecs; ++dbindex)
    {
        HsvPgdatPresetData presetdat;

        if(pgdb_GetByIndex(PRESET_TABLE, dbindex, (Address)&presetdat) == TRUE)
        {
        	if(presetdat.PresetNumber > curPresetIndex)
        		curPresetIndex = presetdat.PresetNumber;
        }
    }

    mFirstInstalledPreset = curPresetIndex;

    for(dbindex = 0; dbindex < noOfDigRecs; ++dbindex)
    {
        HsvPgdatPresetData presetdat;

        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
        {
        	if(svcdat.PresetNumber == INVALID_PRESET)
        	{
        		++curPresetIndex;
        		presetdat.PresetNumber = curPresetIndex;
        		presetdat.Type = HsvOnePart;

        		ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
        		ASSIGN_DEFAULTCOOKIES(svcdat);

        		svcdat.PresetNumber = presetdat.PresetNumber;
        		svcdat.UserHidden = FALSE;
        		svcdat.SystemHidden = FALSE;
        		if(AUTO_INSTALL)
        		{
        			svcdat.NewPreset = FALSE;
        		}
        		svcdat.EPGEnabled = FALSE;
        		svcdat.EPGShortInfo= FALSE;
        		svcdat.UserModifiedName = FALSE;
        		presetdat.UniqueNodeId  = -1;// Invalid Node id

        		pgdb_Add(PRESET_TABLE, (Address)&presetdat);
        		pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
        	}
        }
        else
        {
            TraceDebug(m,"%d Can not get data\n", __LINE__);
        }
    }

    for(dbindex = 0; dbindex < noOfAnaRecs; ++dbindex)
    {
        HsvPgdatAnalogData anadat;
        HsvPgdatPresetData presetdat;

        if(pgdb_GetByIndex(ANALOG_TABLE, dbindex, (Address)&anadat))
        {
            if( (TRUE == anadat.Tuned) &&
                    (idvbtlitesort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                ++curPresetIndex;
                presetdat.PresetNumber = curPresetIndex;
                presetdat.AnalogTablePreset = anadat.PresetNumber;
                presetdat.Type = HsvAnalog;
                presetdat.Frequency = anadat.Frequency;
                presetdat.UniqueNodeId  = -1;// Invalid Node id
                anadat.ChannelLock = FALSE;
                anadat.FavoriteNumber = 0;

                ASSIGN_DEFAULTCOOKIES(anadat);
                pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                pgdb_Update(ANALOG_TABLE,(Address) &anadat);
            }
            else
            {
                TraceDebug(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set\n", __LINE__, anadat.Frequency);
            }
        }
        else
        {
            TraceDebug(m,"%d Analog data suddenly deleted from database\n", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    if(curPresetIndex > mFirstInstalledPreset)
    	mFirstInstalledPreset++;

    pmp_PmpSend(mMpegSortPmp, evSortComplete, (Nat32)NULL);
}

inline Bool CHsvEuropeInstallation_mpegsort_Priv::IsFreqUserInstalled(Nat32 Frequency, Nat16 StreamPriority)
{
    HsvPgdatDigTSData tsdat;    
    tsdat.Frequency     =   Frequency;
    tsdat.StreamPriority   =   StreamPriority;
    if(pgdb_GetByKey( PTC_TABLE, (Address) &tsdat) )
    {
        return tsdat.UserInstalled;
    }
    return FALSE;
}

inline Bool CHsvEuropeInstallation_mpegsort_Priv::CompareIfAnalog(Address data)
{
    Bool retval = FALSE;
    HsvChannel* Channel = (HsvChannel*)data;
    if(Channel->Type == HsvAnalog)
    {
        retval = TRUE;
    }
    return retval;
}

inline Bool CHsvEuropeInstallation_mpegsort_Priv::CompareIfDigital( Address data)
{
    Bool retval = FALSE;
    HsvChannel* Channel = (HsvChannel*)data;
    if(Channel->Type == HsvOnePart)
    {
        retval = TRUE;
    }
    return retval;
}

void CHsvEuropeInstallation_mpegsort_Priv::AssignAnalogPresets(void)
{
    Int16 MinAnalogPreset = 0, MaxAnalogPreset = div_MaxAnalogPresets, presetno = START_PRESET;
    HsvPgdatAnalogData   anadat;
    int i = 0, NoOfRecords = pgdb_GetNoRecords(ANALOG_TABLE);


    TraceNotice (m,"%s %d NoOfRecords : %d \n", __FUNCTION__, __LINE__, NoOfRecords);
    if( NoOfRecords > 0 )
    {
        if(TRUE == pgdb_GetByIndex(ANALOG_TABLE, NoOfRecords - 1, (Address)&anadat))
        {
            MinAnalogPreset = anadat.PresetNumber;
            TraceNotice (m,"%s %d anadat.PresetNumber : %d\n", __FUNCTION__, __LINE__, anadat.PresetNumber);
        }
        if(TRUE == pgdb_GetByIndex(ANALOG_TABLE, 0, (Address)&anadat))
        {
            MaxAnalogPreset = anadat.PresetNumber;
            TraceNotice (m,"%s %d anadat.PresetNumber : %d\n", __FUNCTION__, __LINE__, anadat.PresetNumber);
        }
        if( (MinAnalogPreset >= 0) && (MaxAnalogPreset <= div_MaxAnalogPresets) )
        {
            /* There are valid analog presets */
            for (i = NoOfRecords - 1; i >= 0;  i--)
            {
                if( TRUE == pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
                {
                    /* Only for installed analog presets */
                    HsvPgdatPresetData presetdat;
                    presetdat.Type = HsvAnalog;

                    if( (TRUE == anadat.Tuned) && (idvbtlitesort_IsPresetInstalled(anadat.Frequency) == FALSE) )
                    {
                        /* Follow PATS */
                        if( eurdiv_AutomaticAnalogPresetAllocation() == FALSE)
                        {
                            presetdat.PresetNumber     =    presetno;
                        }
                        else
                        {
                            presetdat.PresetNumber     =    anadat.PresetNumber;
                        }
                        TraceNotice (m,"%s %d presetdat.PresetNumber : %d\n", __FUNCTION__, __LINE__, presetdat.PresetNumber);
                        if(INVALID_PRESET != presetdat.PresetNumber)
                        {
                            presetdat.Type = HsvAnalog;
                            presetdat.AnalogTablePreset = anadat.PresetNumber;
                            presetdat.Frequency = anadat.Frequency;

/*
                            if(nvmcesvc_iPresent())
                            {
                                anadat.CesvcCookie = nvmcesvc_GetDefaultCookieValue();
                            }
                            if(nvmapps_iPresent())
                            {
                                anadat.AppsCookie = nvmapps_GetDefaultCookieValue();    
                            }
                            if(nvmtxt_iPresent())
                            {
                                anadat.TxtCookie = nvmtxt_GetDefaultCookieValue();  
                            }
							*/
  //                          anadat.Favorite = 0;
//                            anadat.UserHidden = 0;
                            anadat.ChannelLock = FALSE;
							anadat.FavoriteNumber	= 0;
                            pgdb_Update(ANALOG_TABLE,(Address) &anadat);
                            presetdat.UniqueNodeId  = -1;// Invalid Node id 
                            pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                            TraceNotice (m,"%s %d Addition at Preset : %d %d\n", __FUNCTION__, __LINE__, i, presetdat.PresetNumber);
                            presetno++;
                        }
                        else
                        {
                            TraceDebug(m,"%s %d Analog table is FULL", __FUNCTION__, __LINE__);
                            ASSERT(!"Analog table is FULL");
                            break;
                        }
                    }
                    else
                    {
                        TraceNotice (m,"Ignoring Preset assignement for frequency %ld as Tuned bit is not set\n", anadat.Frequency); 
                    }
                }
                else
                {
                    TraceNotice (m,"%s %d Analog data suddenly deleted from database\n", __FUNCTION__, __LINE__);
                    ASSERT(!"Analog data suddenly deleted from database");
                }
            }
        }
    }   
    TraceNotice (m,"%s %d i : %d mMpegSortPmp : %d\n", __FUNCTION__, __LINE__,i, mMpegSortPmp);
    pmp_PmpSend(mMpegSortPmp, evDigitalStep, (Nat32)NULL);    
}

void CHsvEuropeInstallation_mpegsort_Priv::AssignDigitalPresets(void)
{
    HsvChannel  preset;
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    Nat8 CurrentFillablePreset = 0;
    int GapSize = 0, i, noRecords;

    noRecords = pgdb_GetNoRecords (SERVICE_TABLE);
    if(iadvpgitr_GetLastChannel(&preset, TRUE) == apperr_Ok)
    {
        CurrentFillablePreset = (((preset.Channel.Digit/100) + 1) * 100);
        if( (CurrentFillablePreset + noRecords) >= MAX_PRESET )
        {
            CurrentFillablePreset = mFindLargestGapInPresetList(&GapSize);
        }       
        TraceNotice (m,"%s %d preset.Channel.Digit : %d, CurrentFillablePreset : %d\n", __FUNCTION__, __LINE__,preset.Channel.Digit, CurrentFillablePreset);
    }

    TraceNotice (m,"%s %d preset.Channel.Digit : %d noRecords : %d\n", __FUNCTION__, __LINE__,preset.Channel.Digit, noRecords);
    for(i = 0;i < noRecords; i++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat))
        {
            if(PRESET_NOT_ALLOCATED(svcdat))
            {
                presetdat.PresetNumber =  CurrentFillablePreset + svcdat.LCN;
                presetdat.Type = HsvOnePart;
#if 0            
                presetdat.OriginalNetworkId = svcdat.OriginalNetworkId;
                presetdat.ServiceId = svcdat.ServiceId;
                presetdat.Tsid = svcdat.Tsid;
                presetdat.Frequency = svcdat.Frequency;
                presetdat.StreamPriority = svcdat.StreamPriority;
#endif
                ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
				/*
                if(nvmcesvc_iPresent())
                {
                    svcdat.CesvcCookie = nvmcesvc_GetDefaultCookieValue();
                }
                if(nvmapps_iPresent())
                {
                    svcdat.AppsCookie = nvmapps_GetDefaultCookieValue();    
                }
                if(nvmtxt_iPresent())
                {
                    svcdat.TxtCookie = nvmtxt_GetDefaultCookieValue(); 
                }
				*/

                svcdat.UserHidden = FALSE;
                svcdat.SystemHidden = FALSE;
                if(AUTO_INSTALL)
                {
                    svcdat.NewPreset = FALSE; 
                }
                else
                {
                    /* Background & Update */
                    svcdat.NewPreset = TRUE;
                    sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
                }
                svcdat.EPGEnabled = FALSE;  
                svcdat.EPGShortInfo= FALSE;
                svcdat.UserModifiedName = FALSE; 

                presetdat.UniqueNodeId  = -1;// Invalid Node id 
                pgdb_Add(PRESET_TABLE, (Address)&presetdat);

                svcdat.PresetNumber = presetdat.PresetNumber;  
                pgdb_Update(SERVICE_TABLE, (Address)&svcdat);

                TraceNotice (m,"Addition at Preset %d by <%d,%d>\n", presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.ServiceId);
            }
//            else
                TraceDebug(m,"VP: Would have caused a problem");    
        }
    }
    pmp_PmpSend(mMpegSortPmp, evSortComplete, (Nat32)NULL);
}

void CHsvEuropeInstallation_mpegsort_Priv::impegpow_Init(void)
{
    mMpegSortPmp = pmp_PmpCreateEx( pen_PumpEngine, mMpegSortHandler, FALSE, "hsveuins_mpegsort" );
    TraceNotice (m,"%s %d mMpegSortPmp : %d\n",__FUNCTION__, __LINE__, mMpegSortPmp);
}

void CHsvEuropeInstallation_mpegsort_Priv::impegpow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvEuropeInstallation_mpegsort_Priv::impegpow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_Initialise(void)
{
    mFirstInstalledPreset = 0xFFFF;
}

void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AddAnalogPreset(Address adata)
{

    HsvChannel preset;
    HsvPgdatPresetData presetdat;
    HsvPgdatAnalogData *panadat = (HsvPgdatAnalogData *)adata;

    if( !div_SupportEmptyAnalogChannels )
    {   
        if(UPDATE_INSTALL)
        {
            panadat->PresetNumber   =   (Nat8 )GetAutomaticPlatformPresetNumber();
        }
        else
        {
            // Automatic It is expected that the structure comes with a default preset number -> it will be used 
        }
        panadat->PreferredStereo = 1;
		panadat->UserModifiedLogo = 0;
		panadat->UserModifiedName = 0;
		panadat->LogoURL = 0;		
        pgdb_Add (ANALOG_TABLE, (Address)adata);
        presetdat.PresetNumber = INVALID_PRESET;
        TraceDebug(m,"%s %d adata.PresetNumber : %d", __FUNCTION__, __LINE__, panadat->PresetNumber);
        if(UPDATE_INSTALL)
        {
            if(div_UpdateLCN( rins_GetMedium()))
            {
                TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
                if(iadvpgitr_GetLastChannel(&preset, TRUE) == apperr_Ok)
                {
                    /* Gap Found so assign the preset with start of the gap */
                    presetdat.PresetNumber  = preset.Channel.Digit + 1;
                }
                else
                {
                    /* Just Assign Start preset */
                    presetdat.PresetNumber  = START_PRESET;
                }

                if((TRUE == pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat)))
                {
                    /* If Digital Preset then move the entire block */
                    TraceNotice (m,"An analog preset replacing digital preset at %d\n", presetdat.PresetNumber);
                    mMoveDigitalBlock(presetdat.PresetNumber);
                }
            }
            else
            {
                /* User Moved the Presets So just add at the last preset if within limit */
                presetdat.PresetNumber  = mGetLastPresetInChannelList();
                TraceDebug(m,"%s %d presetdat.PresetNumber : %d", __FUNCTION__, __LINE__, presetdat.PresetNumber);
            }
            if(INVALID_PRESET != presetdat.PresetNumber)
            {
                TraceNotice (m,"New Channel at Preset=%d, Frequency=%ld\n", presetdat.PresetNumber, panadat->Frequency); 
                presetdat.Type             =   HsvAnalog;

                presetdat.AnalogTablePreset   =   panadat->PresetNumber;

                presetdat.Frequency        =   panadat->Frequency;
				/*
                if(nvmcesvc_iPresent())
                {
                    panadat->CesvcCookie      =   nvmcesvc_GetDefaultCookieValue();
                }
                if(nvmapps_iPresent())
                {
                    panadat->AppsCookie       =   nvmapps_GetDefaultCookieValue();  
                }
                if(nvmtxt_iPresent())
                {
                    panadat->TxtCookie        =   nvmtxt_GetDefaultCookieValue();  
                }
				*/

  //              panadat->Favorite = 0;
//                panadat->UserHidden = 0;
                panadat->ChannelLock = FALSE;
                presetdat.UniqueNodeId  = -1;// Invalid Node id 
				panadat->FavoriteNumber	= 0;

                pgdb_Add(PRESET_TABLE, (Address)&presetdat);
                pgdb_Update(ANALOG_TABLE,(Address) panadat);
                TraceDebug(m,"%s %d Addition at Preset : %d presetdata.PresetNumber : %d", __FUNCTION__, __LINE__,PRESET_TABLE, presetdat.PresetNumber);
                if(UPDATE_INSTALL)
                {
                    sortN_OnEvent(sortN_EventNewPresetFound,rins_GetInstallationMode());
                }
            }
            else
            {
                if(log_iPresent())
                {
                    instutil_LogError( log_SoftErr, INS_PRESET_TABLE_FULL ); // log the error            
                }
            }
        }
    }
    else
    {        
        HsvPgdatAnalogData tempanadat;
        tempanadat.PresetNumber =  panadat->PresetNumber;

        if(TRUE == pgdb_GetByKey (ANALOG_TABLE,(Address)&tempanadat))
        {        
            pgdb_Update (ANALOG_TABLE,(Address) panadat);
            TraceNotice (m,"Updated Analog Preset %d \n",panadat->PresetNumber); 
        }
        else
        {
            TraceNotice (m,"Updating Analog Preset Failed %d \n",panadat->PresetNumber); 
        }     
    }
}

void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_RemoveDigitalPresets(void)
{
    int i = 0;
    HsvPgdatDigTSData tsdat;
    /* Remove Digital Services */
    HsvPgdatDigServiceData svcdat;
    int maxservices = pgdb_GetNoRecords(SERVICE_TABLE);

    for(i = 0 ; i < maxservices; i++)
    {
        if( pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat) )
        {
            Bool UserInstalled = IsFreqUserInstalled (svcdat.Frequency, svcdat.StreamPriority);

            if( svcdat.ServiceListVersion != INSTALL_VERSION )
            {
                tsdat.Frequency =   svcdat.Frequency;
                tsdat.StreamPriority   =   svcdat.StreamPriority;

                if( pgdb_GetByKey( PTC_TABLE, (Address)&tsdat) )
                {                   
                    if( tsdat.PtcListVersion == INSTALL_VERSION )
                    {                    
                        HsvPgdatPresetData presetdat;
                        presetdat.PresetNumber =   svcdat.PresetNumber;
                        presetdat.Type         =   HsvOnePart;
                        if( pgdb_GetByKey( PRESET_TABLE, (Address)&presetdat) )
                        {
                            TraceNotice (m,"Removing Preset %d\n", presetdat.PresetNumber);
                            if (!UserInstalled)
                            {   /* Dont remove UserInstalled preset */
                                pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
                                sortN_OnEvent(sortN_EventChannelRemoved,rins_GetInstallationMode());

                                TraceNotice (m,"Notifictn EventChannelRemoved sent for Preset %d\n",presetdat.PresetNumber);

                            }
                        }

                        if (!UserInstalled)
                        {   /* Dont remove UserInstalled preset */
                            pgdb_Delete(SERVICE_TABLE,(Address) &svcdat);
                            sortN_OnEvent(sortN_EventChannelRemoved,rins_GetInstallationMode());
                            TraceNotice (m,"Notifictn EventChannelRemoved sent for Preset %d, ServiceId:%d \n",svcdat.PresetNumber, svcdat.ServiceId);
                            i--;
                            maxservices--;  /* Reduce this preset from maxservices */
                            TraceNotice (m,"Removing Service Entry <%d,%d>\n", svcdat.OriginalNetworkId,svcdat.ServiceId);
                        }
                    }
                    else
                    {
                        svcdat.ServiceListVersion = INSTALL_VERSION;
                        pgdb_Update(SERVICE_TABLE,(Address) &svcdat);
                    }
                }
            }

        }
    }

    /* Remove Digital Transport Streams */
    int maxts = pgdb_GetNoRecords(PTC_TABLE);

    for(i = 0 ; i < maxts; i++)
    {
        if( pgdb_GetByIndex( PTC_TABLE, i, (Address)&tsdat) )
        {
            if(tsdat.PtcListVersion != INSTALL_VERSION)
            {
                if(!tsdat.UserInstalled)
                { /* Dont remove UserInstalled Preset */            

                    tsdat.PtcListVersion = INSTALL_VERSION;
                    pgdb_Update( PTC_TABLE,(Address) &tsdat );
                    TraceNotice (m,"Removing TS Entry <%d,%d>\n", tsdat.OriginalNetworkId,tsdat.Tsid);
                }   
            }
        }
    }
}

void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_SortAll(void)
{
    TraceNotice (m,"%s %d mMpegSortPmp : %d\n", __FUNCTION__, __LINE__, mMpegSortPmp);
    pmp_PmpSend(mMpegSortPmp, ((AUTO_INSTALL)? evAnalogStep : evSortComplete), (Nat32)NULL);
} 

Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
    UNUSED(CurrentOnwid);
    UNUSED(FillHoles);
    return FALSE;
}

void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AddDigitalPreset (HsvPgdatDigServiceData *psvcdat)
{
    HsvChannel preset;
    HsvPgdatPresetData presetdat;   
    int ActualSize = 1;
    if(PRESET_NOT_ALLOCATED(*psvcdat))
    {
        if(MANUAL_INSTALL || BACKGROUND_INSTALL || UPDATE_INSTALL)
        {
            if(div_UpdateLCN(rins_GetMedium()) == FALSE)
            {
                /* NB: User Moved the Presets So just add at the last preset if within limit */
                presetdat.PresetNumber = mGetLastPresetInChannelList();
            }
            else
            {   /* NB: Just add at the Last Service */
                if(iadvpgitr_GetLastChannel(&preset, FALSE) != apperr_Ok)
                {
                    if(iadvpgitr_GetLastChannel(&preset, TRUE) != apperr_Ok)
                    {
                        presetdat.PresetNumber = START_PRESET;
                    }
                    else
                    {
                        /* Digital Preset to be multiple of 100 of last Analog preset */
                        presetdat.PresetNumber = (((preset.Channel.Digit/100) + 1) * 100) + 1; 
                    }
                }
                else
                {
                    /*NB: just assign the last preset plus one to the new service*/
                    presetdat.Type = HsvAnalog;
                    presetdat.PresetNumber     =   preset.Channel.Digit + 1; 
                    if((TRUE == pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat)))
                    {
                        if(iadvpgitr_GetLastChannel(&preset, TRUE) == apperr_Ok)
                        {
                            if( (presetdat.PresetNumber = preset.Channel.Digit + 1) >= MAX_PRESET)
                            {
                                presetdat.PresetNumber = mGetLastPresetInChannelList();
                            }                      
                        }
                    }  
                }
            }
        }
        if(presetdat.PresetNumber >= MAX_PRESET)
        {
            presetdat.PresetNumber = mFindLargestGapInPresetList(&ActualSize);
            presetdat.PresetNumber++;
        }
        presetdat.Type = HsvOnePart;

        ASSIGN_PRESET_FROM_PSVC(presetdat,psvcdat);
#if 0   
        presetdat.OriginalNetworkId = psvcdat->OriginalNetworkId;
        presetdat.ServiceId = psvcdat->ServiceId;
        presetdat.Tsid = psvcdat->Tsid;
        presetdat.Frequency = psvcdat->Frequency;
        presetdat.StreamPriority = psvcdat->StreamPriority;
#endif
		/*
        if(nvmcesvc_iPresent())
        {
            psvcdat->CesvcCookie = nvmcesvc_GetDefaultCookieValue();
        }
        if(nvmapps_iPresent())
        {
            psvcdat->AppsCookie = nvmapps_GetDefaultCookieValue();  
        }
        if(nvmtxt_iPresent())
        {
            psvcdat->TxtCookie = nvmtxt_GetDefaultCookieValue(); 
        }
		*/

        psvcdat->UserHidden = FALSE;
        psvcdat->SystemHidden = FALSE;
        if(AUTO_INSTALL)
        {
            psvcdat->NewPreset = FALSE; 
        }
        else
        {
            /* Background & Update */
            psvcdat->NewPreset = TRUE;
            sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
        }

        psvcdat->EPGEnabled = FALSE;    
        psvcdat->EPGShortInfo = FALSE;  
        psvcdat->UserModifiedName = FALSE;    

        psvcdat->PresetNumber = presetdat.PresetNumber;

        mFirstInstalledPreset = ((mFirstInstalledPreset > psvcdat->PresetNumber) || (mFirstInstalledPreset ==  INVALID_PRESET) )?
            psvcdat->PresetNumber:
            mFirstInstalledPreset; 
        presetdat.UniqueNodeId  = -1;// Invalid Node id 
        pgdb_Add(PRESET_TABLE, (Address)&presetdat);


        pgdb_Update(SERVICE_TABLE, (Address)psvcdat);

        TraceNotice (m,"Addition at Preset %d by <%d,%d>\n", psvcdat->PresetNumber, psvcdat->OriginalNetworkId, psvcdat->ServiceId);


        TraceNotice (m,"ServiceType = %d\r\n",psvcdat->ServiceType);
    }
//    else
        TraceDebug(m,"VP: Would have caused a problem1");   
}

void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    if(mFirstInstalledPreset > psvcdat->PresetNumber)
    {
        mFirstInstalledPreset = psvcdat->PresetNumber; 
    }
}

Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_IsPresetInstalled(Int32 frequency)
{
    Bool retval = FALSE;
	frequency = (frequency * 16)/1000;
	
    if(UPDATE_INSTALL)
    {
        if( (freqctl_GetMinFrequency() <= frequency) && (freqctl_GetMaxFrequency() >= frequency) )
        {
            int i = 0;
            int maxrecords = pgdb_GetNoRecords(PRESET_TABLE);
            HsvPgdatPresetData presetdat;

            for(i = maxrecords - 1; i >= 0; i--)
            {
                if(TRUE == pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdat))
                {
                  	presetdat.Frequency = (presetdat.Frequency * 16)/1000;
                    if(HsvAnalog == presetdat.Type)
                    {   /* Finally we decided ABS might not be easy to debug & wrote this one ! */
                        if(presetdat.Frequency > (Nat32)frequency)
                        {
                            if(MIN_FREQUENCYDRIFT > (presetdat.Frequency - frequency))
                            {
                                retval = TRUE;
                                break;
                            }
                        }
                        else
                        {
                            if(MIN_FREQUENCYDRIFT > (frequency - presetdat.Frequency))
                            {
                                retval = TRUE;
                                break;
                            }
                        }
                    }
                }
            }
        }        
    }
	TraceNotice (m, "%s returning %d ", __FUNCTION__, retval);
    return retval;
}

int CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_GetNumberOfAnalogChannelsFound() 
{
    int retval = 0;

    if(AUTO_INSTALL)
    {
        retval = hsvprins_prins_GetNumberOfAnalogPresetsFound();
        TraceNotice (m,"%s %d retval : %d\n", __FUNCTION__, __LINE__, retval);
    }
    else if (UPDATE_INSTALL)
    {
        retval = hsvprins_prins_GetNumberOfAnalogPresetsAdded();
        TraceNotice (m,"%s %d retval : %d\n", __FUNCTION__, __LINE__, retval);
    }
    return retval;
}

Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AutoStoreManualInstallationValues ()
{
    Bool retval = FALSE;
    HsvPgdatPresetData presetdat;
    HsvPgdatAnalogData    anadat;
    HsvChannel channel, preset;
    int presetno        = 1;    
    int plfpreset = GetAutomaticPlatformPresetNumber();

    pgdb_Initialise (pgdbconst_Preset,  &presetdat);   	
	
    if(iadvpgitr_GetLastChannel(&preset, TRUE) == apperr_Ok)
    {
        /* NB: Gap Found so assign the preset with start of the gap */
        presetno  = preset.Channel.Digit + 1;
    }
    TraceNotice (m,"%s %d caller : 0x%x\n", __FUNCTION__, __LINE__, __builtin_return_address(0));
    if( (pgdb_GetNoRecords(ANALOG_TABLE ) < div_MaxAnalogPresets) && (presetno != INVALID_PRESET) && (plfpreset>0) )
    {
        retval = TRUE;
        presetdat.Type = HsvOnePart;
        presetdat.PresetNumber     =   presetno; 
        if((TRUE == pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat)))
        {
            /* If Digital Preset then move the entire block */
            TraceNotice (m,"An analog preset replacing digital preset at %d\n", presetdat.PresetNumber);
            presetdat.PresetNumber = mGetLastPresetInChannelList();
        }
        /* Create a User Table entry */
        TraceNotice (m,"presetdat.PresetNumber = %d\n", presetdat.PresetNumber);
        presetdat.Type             =   HsvAnalog;

        presetdat.AnalogTablePreset   =   (Int8 )plfpreset;

/*
        if(nvmcesvc_iPresent())
        {
            anadat.CesvcCookie      =   nvmcesvc_GetDefaultCookieValue();
        }
        if(nvmapps_iPresent())
        {
            anadat.AppsCookie       =   nvmapps_GetDefaultCookieValue();    
        }
        if(nvmtxt_iPresent())
        {
            anadat.TxtCookie        =   nvmtxt_GetDefaultCookieValue(); 
        }
*/
  //      anadat.Favorite = FALSE;
//        anadat.UserHidden = FALSE;
        anadat.ChannelLock = FALSE;
		anadat.FavoriteNumber	= 0;
        TraceNotice (m,"%s %d Addition at preset %d\n", __FUNCTION__, __LINE__, presetdat.PresetNumber);
        presetdat.UniqueNodeId  = -1;// Invalid Node id 
        pgdb_Add(PRESET_TABLE, (Address)&presetdat);

        /* Create an Analog Preset  */
        /* Prem further needs to look
           as the there is no Initialize function available */
        anadat.PresetNumber    =   (Int8 )plfpreset;
        anadat.PreferredStereo = 1;
		anadat.UserModifiedLogo = 0;
		anadat.UserModifiedName = 0;
		anadat.LogoURL = 0;		
        pgdb_Add(ANALOG_TABLE,(Address)&anadat);

        /* Store the Manual Installation Values */
        channel.Type                =   HsvAnalog;
        channel.Channel.AnalogNo    =   presetdat.PresetNumber;
        hsvprins_prins_StoreManualInstallationValues(channel);
        /* Fix me. Split this function. Move the unwanted to hsvprins */

        if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat))
        {   /* Query for frequency value and store back in Preset List */
            anadat.PresetNumber    =   (Int8 )plfpreset;
            if(TRUE == pgdb_GetByKey(ANALOG_TABLE, (Address)&anadat))
            {
                presetdat.Frequency    =   anadat.Frequency;
                pgdb_Update(PRESET_TABLE,(Address) &presetdat);
            }
        }
        else
        {
            retval = FALSE;
        }
    }
    return retval;
}

int CHsvEuropeInstallation_mpegsort_Priv::GetAutomaticPlatformPresetNumber(void)
{
    int retval = -1, CurrentPreset = -1, NextPreset = -1, i = -1;
    int NoOfRecords = pgdb_GetNoRecords(ANALOG_TABLE);

    ASSERT ( NoOfRecords <= div_MaxAnalogPresets );
    if ( NoOfRecords <= div_MaxAnalogPresets )
    {
        for (i = NoOfRecords - 1; i >= 0; i--)
        {   
            HsvPgdatAnalogData   anadat;
            CurrentPreset = NextPreset = -1;

            if( TRUE == pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
            {   /* Only for installed analog presets */
                CurrentPreset   = anadat.PresetNumber;
                if(i > 0)
                {
                    if( TRUE == pgdb_GetByIndex(ANALOG_TABLE, i - 1, (Address)&anadat))
                    {
                        NextPreset      = anadat.PresetNumber;            
                        if(NextPreset !=  (CurrentPreset + 1) )
                        {
                            break;
                        }

                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if( CurrentPreset >= 0 )
        {
            if( NextPreset > 0 )
            {
                retval = (NextPreset !=  (CurrentPreset + 1) ) ? (CurrentPreset + 1)
                    : (NextPreset + 1);    
            }
            else
            {
                retval = (CurrentPreset + 1);
            }
        }
        if(NoOfRecords == 0)
        {   
            /* Preset Table Empty */
            retval = 1;
        }
    }
    else
    {
        ASSERT ( NoOfRecords < MAX_PRESETS );
    }
    return retval;
}

void CHsvEuropeInstallation_mpegsort_Priv::mMoveDigitalBlock(Nat16 FromPreset)
{
    int i, retval;
    HsvChannel preset;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat;
    Bool BlockExceedsMaxPreset = FALSE;
    Nat16 FirstGapFreePreset = START_PRESET;

    /* Move the Digital Block => only for update Installation */
    if((retval = iadvpgitr_GetLastChannel(&preset, FALSE)) == apperr_Ok)
    {
        int NoOfDigitalPresetsInBlock = preset.Channel.Digit - FromPreset;
        for(i = 0; i <= NoOfDigitalPresetsInBlock; i++) 
        {
            /* Make use of Descending order arrangement of PRESET_Table */
            if( TRUE == pgdb_GetByIndex( PRESET_TABLE, i,(Address)&presetdat) )
            {
#if 0               
                svcdat.OriginalNetworkId = presetdat.OriginalNetworkId;
                svcdat.ServiceId = presetdat.ServiceId;
                svcdat.Frequency = presetdat.Frequency;
                svcdat.StreamPriority = presetdat.StreamPriority;
#endif
                pgdb_GetByKey (SERVICE_TABLE,(Address)&svcdat);
                pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
                if(!BlockExceedsMaxPreset)
                {
                    presetdat.PresetNumber = ((((FromPreset/100) + 1) * 100) + 1) + (NoOfDigitalPresetsInBlock - i);
                }
                else
                {
                    /* Gap was exceeded for this Digital Block, hence mNextFreePresetSegment gives
                       FirstGapPreset so just increment from this preset for rest of the services 
                       */
                    presetdat.PresetNumber = FirstGapFreePreset + i;
                }
                if( (presetdat.PresetNumber < MAX_PRESET) )
                {
                    presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    pgdb_Add(PRESET_TABLE,(Address)&presetdat);

                    svcdat.PresetNumber = presetdat.PresetNumber;
                    pgdb_Update(SERVICE_TABLE, (Address)&svcdat);

                }
                else
                {
                    /* The Digital Block cannot fit-in the gap after Analog Presets So, find the gap between
                       Analog Presets which can accomidate the Digital block 
NOTE: The Following code will be executed only once within the for loop
*/
                    BlockExceedsMaxPreset = TRUE;
                    FirstGapFreePreset = presetdat.PresetNumber = mFindLargestGapInPresetList(&NoOfDigitalPresetsInBlock);
                    presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    pgdb_Add(PRESET_TABLE,(Address)&presetdat);

                    svcdat.PresetNumber = presetdat.PresetNumber;
                    pgdb_Update(SERVICE_TABLE, (Address)&svcdat);

                }
            }
        }
    }
}

inline Nat16 CHsvEuropeInstallation_mpegsort_Priv::mGetLastPresetInChannelList(void)
{
    HsvPgdatPresetData presetdat;
    int lastPreset = presetdat.PresetNumber = 0, ActualSize = 1;

    if( pgdb_GetByIndex(PRESET_TABLE, 0, (Address)&presetdat) == TRUE)
    {
        if((presetdat.PresetNumber + 1) >= MAX_PRESET)
        {
            TraceDebug(m,"%s %d presetdat.PresetNumber : %d ", __FUNCTION__, __LINE__, presetdat.PresetNumber);
            presetdat.PresetNumber = mFindLargestGapInPresetList(&ActualSize);
        }
    }   
    return ( LARGER( (lastPreset + 1), (presetdat.PresetNumber + 1) ) );
}

Nat16 CHsvEuropeInstallation_mpegsort_Priv::mFindLargestGapInPresetList(int *GapSize)
{
    int startPreset = 1;
    int i;
    Nat16 startPresetInGap = INVALID_PRESET;
    Nat16 NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatPresetData  presetdat, nextpresetdat;

    *GapSize = 0;
    if(NoOfRecords > 1)
    {
        for(i=1; i < NoOfRecords; i++)
        {
            if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdat))
            {
                if(pgdb_GetByIndex(PRESET_TABLE, i - 1, (Address)&nextpresetdat))
                {
                    if( (*GapSize < (nextpresetdat.PresetNumber - presetdat.PresetNumber)) 
                            && (nextpresetdat.PresetNumber <= div_MaxValidLCNValue) )
                    {               
                        startPresetInGap = presetdat.PresetNumber;
                        *GapSize = (nextpresetdat.PresetNumber - presetdat.PresetNumber);
                    }           
                }
            }
        }
        /* take care of initial Gap also */
        if(*GapSize < (presetdat.PresetNumber - startPreset))
        {               
            startPresetInGap = 0;
        }
    }
    TraceDebug(m,"%s %d startPresetInGap : %d GapSize : %d", __FUNCTION__, __LINE__, startPresetInGap, *GapSize);
    return startPresetInGap;
}

HsvChannel CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_GetInstalledWeakSignalChannel(void)
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceNotice(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

/*Stub*/
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AnalogPresetEntry(void)
{
	return 0;
}
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_DeleteAllDigitalChannels()
{
	return 0;
}    
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AssignPresetsOfOtherCountries(void)
{
	return 0;
}

Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_UpdatingLCNDuringUpdateInstallation()
{
    return 0;
}
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_DeleteInvalidPTCTable()
{
	return 0;
}
int CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_GetOriginalNetworkId(int CurrentCountry)
{
	return 0;
}
void CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mpegsort_Priv::idvbtlitesort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
