/**********************************************************************
 *
 *   C Source:       hsveuins_mlitesort.c
 *   Instance:       blr81mgr_1
 *   Description:    
 *   %created_by:    nituk %
 *   %date_created:  Wed Mar 28 18:10:05 2012 %
 *
 **********************************************************************/
#include "_hsveuins_mlitesort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mlitesort")









/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/



















/* static void mReadCableDS(void);
   static void mDeleteTSByIndex(int index); */


/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvEuropeInstallation_mlitesort_Priv::s__mLiteSortPmp;

//static t_CableDSDesc mFlashCableDS;
int CHsvEuropeInstallation_mlitesort_Priv::s__mFirstInstalledPreset = 0xFFFF,CHsvEuropeInstallation_mlitesort_Priv::s__mCurrentPresetIndex,CHsvEuropeInstallation_mlitesort_Priv::s__mCurrentRadioIndex;

/* Priority is in increasing order. Refer to honouring rules sheet of vsd  */
int CHsvEuropeInstallation_mlitesort_Priv::s__mServicePriority[MAX_SERVICE_TYPES1] =
{
    AppApiDatabroadcastService,
    AppApiTeletextService,
    AppApiAdvCodecRadioService,
    AppApiRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiAdvCodecSDTelevisionService,
    AppApiAdvCodecHDTelevisionService
};


/* Priority is in increasing order. Refer to honouring rules sheet of vsd  */
int CHsvEuropeInstallation_mlitesort_Priv::s__mChinaServicePriority[MAX_CHINA_SERVICE_TYPES] = 
{
    AppApiAdvCodecRadioService,
    AppApiSECAMCodedSignal,
    AppApiPALCodedSignal,
    AppApiRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiUserDefinedHD4,
    AppApiUserDefinedHD3,
    AppApiUserDefinedHD2,
    AppApiUserDefinedHD1,
    AppApiAdvCodecHDTelevisionService,
    AppApiAdvCodecSDTelevisionService
};


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvEuropeInstallation_mlitesort_Priv::mLiteSortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s: CURRENT STEP = %d",__FUNCTION__, value);

    if((rins_GetLCNSortingControl() == FALSE) && (value != evStepAll))
    {
        value = evNoSorting;
    }

    switch(value)
    {
        case evStep1:
            /* NONRADIO LCN BASED DVBC PRESETS */
            TraceInfo(m,"%s %d NONRADIO LCN BASED DVBC PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalHonouredPresets(FALSE, DVBC_DECODER_PRESETS, value);
            break;
        case evStep2:
            /* NONRADIO LCN BASED DVBT PRESETS */
            TraceInfo(m,"%s %d NONRADIO LCN BASED DVBT PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalHonouredPresets(FALSE, DVBT_DECODER_PRESETS, value);
            break;
        case evStep3:
            /* NONRADIO NON LCN BASED DVBC & DVBT PRESETS */
            TraceInfo(m,"%s %d NONRADIO NON LCN BASED DVBC & DVBT PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalNonHonouredPresets(FALSE, value);
            break;
        case evStep4:
            /* ANALOG PRESETS */
            TraceInfo(m,"%s %d ANALOG PRESETS ", __FUNCTION__, __LINE__);
            mSortAnalogPresets(value);
            break;
        case evStep5:
            /* RADIO LCN BASED DVBC PRESETS */
            TraceInfo(m,"%s %d RADIO LCN BASED DVBC PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalHonouredPresets(TRUE, DVBC_DECODER_PRESETS, value);
            break;
        case evStep6:
            /* RADIO LCN BASED DVBT PRESETS */
            TraceInfo(m,"%s %d RADIO LCN BASED DVBT PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalHonouredPresets(TRUE, DVBT_DECODER_PRESETS, value);
            break;
        case evStep7:
            /* RADIO NON LCN BASED DVBC & DVBT PRESETS */
            TraceInfo(m,"%s %d RADIO NON LCN BASED DVBC & DVBT PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalNonHonouredPresets(TRUE, value);
            break;
        case evStepAll:
            TraceInfo(m,"%s %d", __FUNCTION__, __LINE__);
            idvbclitesort_DeleteInvalidPTCTable();
            sortN_OnEvent(sortN_EventSortComplete, TRUE);
            break;
        case evNoSorting:
            TraceNotice(m,"%s %d No Sorting\n", __FUNCTION__, __LINE__);
            mNoSorting(value);
            break;
        default:
            ASSERT(!"Unknown Step in sorting");
            break;
    }
}

void CHsvEuropeInstallation_mlitesort_Priv::mNoSorting(int evCurrentSortStep)
{
    int dbindex = 0, noOfDigRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    int noOfAnaRecs = pgdb_GetNoRecords(ANALOG_TABLE);
    int noOfPresetRecs = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatDigServiceData svcdat;

    TraceNotice(m,"%s: D %d A %d\r\n",__FUNCTION__, noOfDigRecs, noOfAnaRecs);

    mCurrentPresetIndex = 0;

    for(dbindex = 0; dbindex < noOfPresetRecs; ++dbindex)
    {
       	HsvPgdatPresetData presetdat;

       	if(pgdb_GetByIndex(PRESET_TABLE, dbindex, (Address)&presetdat) == TRUE)
      	{
       		if(presetdat.PresetNumber > mCurrentPresetIndex)
       			mCurrentPresetIndex = presetdat.PresetNumber;
       	}
    }

    for(dbindex = 0; dbindex < noOfDigRecs; ++dbindex)
    {
        HsvPgdatPresetData presetdat;

        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
        {
        	if(svcdat.PresetNumber == INVALID_PRESET)
        	{
        		++mCurrentPresetIndex;
        		presetdat.PresetNumber = mCurrentPresetIndex;
        		presetdat.Type = HsvOnePart;

        		ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
        		ASSIGN_DEFAULTCOOKIES(svcdat);

        		svcdat.PresetNumber = presetdat.PresetNumber;
        		if(AUTO_INSTALL)
        		{
        			svcdat.NewPreset = FALSE;
        		}
        		svcdat.SystemHidden = FALSE;
        		svcdat.EPGEnabled = FALSE;
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
                    (idvbclitesort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                ++mCurrentPresetIndex;
                presetdat.PresetNumber = mCurrentPresetIndex;
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
                TraceDebug(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set", __LINE__, anadat.Frequency);
            }
        }
        else
        {
            TraceDebug(m,"%d Analog data suddenly deleted from database", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    pmp_PmpSend(mLiteSortPmp, evStepAll, (Nat32)NULL);
}

/*****************************************
  provides IHsvHybridPresetSort litesort
 ******************************************/

void CHsvEuropeInstallation_mlitesort_Priv::ilitepow_Init()
{
    mLiteSortPmp = pmp_PmpCreateEx( pen_PumpEngine, mLiteSortHandler, FALSE, "hsveuins_mlitesort" );
}

void CHsvEuropeInstallation_mlitesort_Priv::ilitepow_TurnOn()
{
}

void CHsvEuropeInstallation_mlitesort_Priv::ilitepow_TurnOff()
{
}

void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_Initialise()
{
    mFirstInstalledPreset = 0xFFFF;

    if(AUTO_INSTALL)
    {
        mCurrentPresetIndex = 0;
        mCurrentRadioIndex = 0;
    }    
}

void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AddAnalogPreset(Address adata)
{

    HsvPgdatAnalogData *panadat = (HsvPgdatAnalogData *)adata;


    if(UPDATE_INSTALL)
    {
        panadat->PresetNumber = (Nat8 )GetAutomaticPlatformPresetNumber();
    }
    else
    {   /* Automatic */
        /* It is expected that the structure comes with a default preset number -> it will be used */
    }

  //  panadat->Favorite = FALSE;
//    panadat->UserHidden = FALSE;
    panadat->ChannelLock = FALSE;
    panadat->PreferredStereo = 1;
	panadat->FavoriteNumber	= 0;
	panadat->UserModifiedLogo = 0;
	panadat->UserModifiedName = 0;
	panadat->LogoURL = 0;

    pgdb_Add (ANALOG_TABLE, (Address)adata);
}

HsvChannel CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_GetInstalledWeakSignalChannel()
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceNotice(m,"%s %d channel %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

void CHsvEuropeInstallation_mlitesort_Priv::mSortAnalogPresets(int evCurrentSortStep)
{
    /* Note: Analog entries at locations of 100+ */
    HsvPgdatAnalogData anadat;
    HsvPgdatPresetData presetdat;
    int i, presetno = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(ANALOG_TABLE);

    presetno = mFindPlaceForAnalogPresets();

    TraceInfo(m,"%s %d presetno %d NoOfRecords: %d", __FUNCTION__, __LINE__, presetno, NoOfRecords);
    for(i = NoOfRecords -1 ; i >= 0; i--)
    {   
        if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
        {
            /* Only for installed analog presets */
            if( (TRUE == anadat.Tuned) && 
                    (idvbclitesort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                /* Allocate the current number */
                presetdat.PresetNumber = presetno;
                TraceDebug(m,"%s %d presetdat.PresetNumber : %d\n", __FUNCTION__, __LINE__, presetdat.PresetNumber);
                presetdat.AnalogTablePreset = anadat.PresetNumber;

                if(presetdat.PresetNumber >= MAX_LCN_VALUE )
                {
                    presetdat.PresetNumber = presetno = mFindPlaceForAnalogPresets();

                }
                if(INVALID_PRESET != presetdat.PresetNumber)
                {
                    presetdat.Type = HsvAnalog;
                    presetdat.Frequency = anadat.Frequency;

                    ASSIGN_DEFAULTCOOKIES(anadat);
                    presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                    pgdb_Update(ANALOG_TABLE,(Address) &anadat);

                    presetno++;
                }
                else
                {
                    TraceInfo(m,"%d Cannot Add Analog Preset as there is no place in the PRESET LIST", __LINE__);
                    ASSERT(!"Analog table is FULL");
                    break;
                }
            }
            else
            {
                TraceInfo(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set", __LINE__, anadat.Frequency); 
            }
        }
        else
        {
            TraceInfo(m,"%d Analog data suddenly deleted from database", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    int evNextSortStep = evCurrentSortStep + 1;
    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mLiteSortPmp, evNextSortStep, (Nat32)NULL);
}

void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AddDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    if( BACKGROUND_INSTALL )
    {
        int dbindex;
        Bool retval = FALSE;

        TraceDebug(m,"%d: LCN = %d",__LINE__,psvcdat->LCN);

        if(TRUE == pgdb_GetIndex(SERVICE_TABLE, &dbindex, (Address)psvcdat))
        {
            /* Try to obtain a Preset using InvalidLCN algorithm */
            if (VALID_LCN_RANGE(REVALIDATE(psvcdat->LCN)))
            {
                retval = mDigitalPresetEntryforValidLCN(psvcdat);
            }

            if(retval == FALSE)
            {
                mDigitalPresetEntryforInValidLCN(dbindex);
            }
        }
    }
    else
    {
        TraceNotice(m,"%s %d This function call should not be made in installation mode other than manual mode", __FUNCTION__, __LINE__);
        ASSERT(FALSE);
    }
}

Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AutoStoreManualInstallationValues()
{
    Bool retval = FALSE;
    HsvPgdatPresetData newpresetdat;
    HsvPgdatAnalogData    anadat;
    HsvChannel channel;
    int presetno = INVALID_PRESET;
    int plfpreset = GetAutomaticPlatformPresetNumber();

    pgdb_Initialise (pgdbconst_Preset,  &newpresetdat);   	
    if(pgdb_GetNoRecords(ANALOG_TABLE) < div_MaxAnalogPresets )
    {
        presetno = mFindPlaceForAnalogPresets();


        if( (plfpreset > 0 ) && (presetno != INVALID_PRESET))
        {   
            /* Create a User Table entry */
            TraceDebug(m,"%d Preset = %d,plfPreset=%d\n", __LINE__, presetno,plfpreset);
            newpresetdat.PresetNumber = presetno;
            newpresetdat.Type = HsvAnalog;
            newpresetdat.AnalogTablePreset = (Int8 )plfpreset;

            ASSIGN_DEFAULTCOOKIES(anadat);
            newpresetdat.UniqueNodeId   = -1;// Invalid Node id 
            pgdb_Add(PRESET_TABLE, (Address)&newpresetdat);

            /* Create an Analog Preset */
            anadat.PresetNumber = (Int8)plfpreset;
  //          anadat.Favorite = FALSE;
//            anadat.UserHidden = FALSE;
            anadat.ChannelLock = FALSE;
            anadat.PreferredStereo = 1;
			anadat.FavoriteNumber	= 0;
			anadat.UserModifiedLogo = 0;
			anadat.UserModifiedName = 0;
			anadat.LogoURL = 0;
            pgdb_Add(ANALOG_TABLE,(Address)&anadat);

            /* Store the Manual Installation Values */
            channel.Type = HsvAnalog;
            channel.Channel.AnalogNo = presetno;
            hsvprins_prins_StoreManualInstallationValues(channel);

            /* Fix me. Split this function. Move the unwanted to hsvprins */
            if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&newpresetdat))
            {
                /* Query for frequency value and store back in Preset List */
                anadat.PresetNumber = (Int8)plfpreset;
                if(TRUE == pgdb_GetByKey(ANALOG_TABLE, (Address)&anadat))
                {
                    newpresetdat.Frequency = anadat.Frequency;
                    pgdb_Update(PRESET_TABLE, (Address) &newpresetdat);
                }
            }
            retval = TRUE;
        }
    }
    return retval;
}

int CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_GetNumberOfAnalogChannelsFound()
{
    int retval = 0;

    if(AUTO_INSTALL)
    {
        retval = hsvprins_prins_GetNumberOfAnalogPresetsFound();
    }
    else if(UPDATE_INSTALL)
    {
        retval = hsvprins_prins_GetNumberOfAnalogPresetsAdded();
    }
    return retval;
}

void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d",__FUNCTION__, __LINE__);

    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)psvcdat))
    {
        presetdat.PresetNumber = psvcdat->PresetNumber;
        presetdat.Type = HsvOnePart;

        if(TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
        {

            ASSIGN_PRESET_FROM_PSVC(presetdat,psvcdat);     
            pgdb_Update (PRESET_TABLE, (Address)&presetdat);

            if (MANUAL_INSTALL) 
            {
                mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;
            }
            TraceDebug(m,"Updated Preset %d with new information from <%d,%d,%d,%d>\n", presetdat.PresetNumber,psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->StreamPriority, psvcdat->Frequency); 
        }
        else
        {
            TraceDebug(m,"%s %d\n",__FUNCTION__, __LINE__);
        }
    }          
}
/*****************************************************************************
  This is actually for Best Mux only. But since we can install DVBT also on
  cable, this function still exists
 *****************************************************************************/
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_DeleteInvalidPTCTable()
{
    HsvPgdatDigServiceData svcdat;
    HsvPgdatDigTSData tsdat;
    Bool retval = TRUE;
    Bool InvalidPTCTable = TRUE;
    int noofptcrecords = pgdb_GetNoRecords(PTC_TABLE);
    int index = -1;
    int srvindex = -1;
    int from,to;

    for (index = noofptcrecords -1; index >= 0; index--)
    {
        if(pgdb_GetByIndex( PTC_TABLE, index,(Address)&tsdat))
        {
            svcdat.OriginalNetworkId = tsdat.OriginalNetworkId; 
            InvalidPTCTable = TRUE;   

            if(pgdb_GetRange(SERVICE_TABLE, 1, (Address)&svcdat, &from, &to))
            {
                ASSERT(from<=to);
                /* Iterate over all multiplexes with the same onid */
                for(srvindex=from; (srvindex<=to) &&(InvalidPTCTable); srvindex++)
                {
                    pgdb_GetByIndex(SERVICE_TABLE, srvindex, (Address)&svcdat);

                    /* Check if this service is from the mux we are interested in */
                    if((svcdat.Frequency == tsdat.Frequency) && (svcdat.StreamPriority == tsdat.StreamPriority))
                    {
                        InvalidPTCTable = FALSE;
                    }
                }
            }

            if(InvalidPTCTable)
            {
                /* Delete the Invalid PTC table */
                retval = pgdb_Delete( PTC_TABLE, (Address) &tsdat );
            }
        }

    }
    return (retval);
}

void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_SortAll()
{
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    pmp_PmpSend(mLiteSortPmp, evStep1, (Nat32)NULL);
}

Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_IsPresetInstalled(Int32 frequency)
{
    Bool retval = FALSE;
    Nat32 minfreq = START_FREQUENCY, maxfreq = END_FREQUENCY, result = 0;
	frequency = (frequency * 16)/1000;

    if((UPDATE_INSTALL) || (MANUAL_INSTALL))
    {
        feapi_GetFreqRange(WINDOWID, &minfreq, &maxfreq, &result);

        if( (minfreq <= (Nat32)frequency) && (maxfreq >= (Nat32)frequency) )
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
                    {   
                        /* Finally we decided ABS might not be easy to debug & wrote this one ! */
                        if( presetdat.Frequency > (Nat32)frequency)
                        {
                            if( (presetdat.Frequency - frequency) < MIN_FREQUENCYDRIFT )
                            {
                                retval = TRUE;
                                break;
                            }
                        }
                        else
                        {
                            if( (frequency - presetdat.Frequency) < MIN_FREQUENCYDRIFT )
                            {
                                retval = TRUE;
                                break;
                            }
                        }
                        TraceInfo(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
                    }
                }
            }
        }        
    }

    TraceInfo(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}
/***********************************/

void CHsvEuropeInstallation_mlitesort_Priv::mSortDigitalHonouredPresets(Bool CheckForRadioServices, Nat32 DecoderType, int evCurrentSortStep)
{
    int dbindex;
    HsvPgdatDigServiceData svcdat;

    TraceDebug(m,"%s %d SORTING OF %s %s\n", __FUNCTION__, __LINE__, (DecoderType & feapi_ChanDecDvbC)?"DVBC":"DVBT", CheckForRadioServices?"RADIO SERVICES":"NON RADIO SERVICES");
    for( dbindex = 0; dbindex < pgdb_GetNoRecords(SERVICE_TABLE); dbindex++)
    {
        if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
        {
            if( (svcdat.DecoderType & DecoderType) && (INVALID_PRESET == svcdat.PresetNumber)
                    && VALID_LCN_RANGE(REVALIDATE(svcdat.LCN)) && (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices) )
            {
                mDigitalPresetEntryforValidLCN(&svcdat);
            }
            else
            {
                /* Non Honoured LCN or RADIO Service or DVBT preset.
                   So lets come back later */
            }
        }
        else
        {
            ASSERT(!" Who deleted the service here ");
        }
    }

    int evNextSortStep = evCurrentSortStep + 1;
    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mLiteSortPmp, evNextSortStep, (Nat32)NULL);
}

void CHsvEuropeInstallation_mlitesort_Priv::mSortDigitalNonHonouredPresets(Bool CheckForRadioServices, int evCurrentSortStep)
{
    int i = 0, pref_dbindex = -1, dbindex = 0, to = pgdb_GetNoRecords(SERVICE_TABLE);
    Bool pref_index_found = TRUE; 
    HsvPgdatDigServiceData svcdat;
    int evNextSortStep;

    for(; (i < to) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = 0; dbindex < to; dbindex++)
        {
            if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
            {
                if( PRESET_NOT_ALLOCATED(svcdat.PresetNumber) && (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices))
                {
                    if(pref_index_found == FALSE)
                    {
                        /* First time in the loop */
                        pref_dbindex = dbindex;
                        pref_index_found = TRUE;
                    }
                    else
                    {
                        if(mCompareServices(&svcdat, pref_dbindex) < 0)
                        {
                            pref_dbindex = dbindex;
                        }
                    }
                }
                else
                {
                    /* Non Honoured LCN or RADIO Service or DVBT preset.
                       So lets come back later */
                }
            }
            else
            {
                ASSERT(!" Who deleted the service here ");
            }
        }

        if( (pref_dbindex >= 0) && (pref_index_found == TRUE))
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }           

    evNextSortStep = evCurrentSortStep + 1;

    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mLiteSortPmp, evNextSortStep, (Nat32)NULL);
}

Bool CHsvEuropeInstallation_mlitesort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
    HsvPgdatDigServiceData oldsvcdat;
    HsvPgdatPresetData presetdat, tmppresetdat;
    Bool PresetRequireRefilling = FALSE;
    Bool retval = FALSE;

    REVALIDATE(svcdat->LCN);

    presetdat.PresetNumber = ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType);
    presetdat.Type = HsvOnePart;

    if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat))
    {
        /* Someone has already occupied that preset. Lets start a fight now !!*/
        ASSIGN_SVC_FROM_PRESET(oldsvcdat, presetdat);
        if(TRUE == pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat))
        {
            if(div_UpdateLCN(rins_Cable))
            {
                if((oldsvcdat.ServiceListVersion == INSTALL_VERSION) &&
                        (!VALID_LCN_RANGE(oldsvcdat.LCN)))
                {
                    /* Existing service has a LCN where as already installed one in current installation 
                       doesnt have LCN. So lets refill */
                    PresetRequireRefilling = TRUE;
                }
                else if( (svcdat->DecoderType & feapi_ChanDecDvbC) && (oldsvcdat.DecoderType & feapi_ChanDecDvbT) )
                {
                    /* Exisitng service is DVBT preset, whereas new one is a DVBC Preset */
                    PresetRequireRefilling = TRUE;
                }
                else
                {
                    if(svcdat->DecoderType == oldsvcdat.DecoderType)
                    {
                        int svcdatPriority = mGetServicePriority(svcdat->ServiceType);
                        int oldsvcdatPriority = mGetServicePriority(oldsvcdat.ServiceType);

                        if( (svcdatPriority > oldsvcdatPriority) || 
                                ((svcdatPriority == oldsvcdatPriority) && (!VALID_LCN_RANGE(oldsvcdat.LCN))) )
                        {
                            /* Current contestant has higher priority than existing Service Type.
                               So strip him of his preset position.*/
                            PresetRequireRefilling = TRUE;
                        }
                    }
                }
            }
            if( PresetRequireRefilling )
            {
                /* Ya - we found a better candidate for using this preset */
                INVALIDATE(oldsvcdat.LCN);
                oldsvcdat.PresetNumber = INVALID_PRESET;
                pgdb_Update(SERVICE_TABLE,(Address)&oldsvcdat); 

                presetdat.PresetNumber = ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType);
                presetdat.Type = HsvOnePart;

                ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
                ASSIGN_DEFAULTCOOKIES(*svcdat);

                svcdat->UserHidden = FALSE;

                svcdat->SystemHidden = FALSE;

                svcdat->NewPreset = !AUTO_INSTALL;
                svcdat->EPGEnabled = FALSE; 
                svcdat->EPGShortInfo = FALSE;
                tmppresetdat.PresetNumber = presetdat.PresetNumber;
                if(pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat) == TRUE)
                {
                    presetdat.UniqueNodeId = tmppresetdat.UniqueNodeId;
                }
                pgdb_Update (PRESET_TABLE, (Address)&presetdat);

                svcdat->PresetNumber = presetdat.PresetNumber;
                pgdb_Update (SERVICE_TABLE, (Address)svcdat);
                retval = TRUE;

                TraceDebug(m,"Replacement at Preset %d by <%d,%d>\n", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId); 
            }
            else
            {
                /* Current preset is not replaced. Its LCN will be made Invalid.
                   So that it comes in the next round */
                if(!UPDATE_INSTALL)
                {
                    svcdat->LCN = INVALID_LCN;
                    pgdb_Update (SERVICE_TABLE, (Address)svcdat);
                    retval = TRUE;
                }
            }
        }
        else
        {
            ASSERT(!" How did the service get deleted ");
        }
    }
    else
    {
        /* That preset is free. So just grab it */
        TraceDebug(m,"@ %d ServiceType = %d",__LINE__, svcdat->ServiceType);
        presetdat.PresetNumber = ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType);
        presetdat.Type = HsvOnePart;

        ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
        ASSIGN_DEFAULTCOOKIES(*svcdat);

        svcdat->NewPreset = !AUTO_INSTALL;
        svcdat->UserHidden = FALSE;
        svcdat->SystemHidden = FALSE;
        svcdat->EPGEnabled = FALSE; 
        svcdat->EPGShortInfo = FALSE;
        svcdat->UserModifiedName = FALSE;                 
        presetdat.UniqueNodeId  = -1;// Invalid Node id 
        pgdb_Add(PRESET_TABLE, (Address)&presetdat);

        svcdat->PresetNumber = ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType);
        pgdb_Update(SERVICE_TABLE, (Address)svcdat);

        TraceDebug(m,"Addition at Preset %d by <%d,%d>\n", svcdat->PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);

        retval = TRUE;

        if(!IS_RADIO_SERVICE(svcdat->ServiceType))
        {
            mFirstInstalledPreset  = ( mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;
        }       

        if(svcdat->NewPreset)
        {
            sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
        }
    }
    return retval;
}

void CHsvEuropeInstallation_mlitesort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    int CurrentPresetIndex = 0, FromPreset, ToPreset;
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat, temppresetdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        temppresetdat.PresetNumber = CurrentPresetIndex = GETCURRENTINDEX(svcdat.ServiceType);
        temppresetdat.Type = HsvOnePart;

        TraceDebug(m,"%s::CurrentPresetIndex = %d",__FUNCTION__,CurrentPresetIndex);
        if( (mValidPresetRange(svcdat.ServiceType, CurrentPresetIndex) == FALSE) || pgdb_GetByKey(PRESET_TABLE, (Address)(&temppresetdat)) )
        {
            FromPreset = mLastLCNBasedPreset(IS_RADIO_SERVICE(svcdat.ServiceType)?TRUE:FALSE);
            /* Naresh: the 2nd check has to be changed based on inputs from RM team for a CR to indicate smae behaviour to be followed for Radio & Non-Radio preset allocation */
            if( (FromPreset == INVALID_PRESET) || (FromPreset >= div_MaxValidLCNValue) )
            {
                FromPreset = (IS_RADIO_SERVICE(svcdat.ServiceType))?(MAX_LCN_VALUE + 1):START_PRESET;
            }
            else
            {
                FromPreset++;
            }
            ToPreset = (IS_RADIO_SERVICE(svcdat.ServiceType))?(MAX_LCN_VALUE + div_MaxValidLCNValue):(MAX_LCN_VALUE);

            CurrentPresetIndex = mLargestGapInForwardRange(FromPreset, ToPreset);
        }

        if((CurrentPresetIndex > 0))
        {
            TraceDebug(m,"%s::CurrentPresetIndex = %d",__FUNCTION__,CurrentPresetIndex);
            presetdat.PresetNumber = CurrentPresetIndex;
            presetdat.Type = HsvOnePart;

            ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
            ASSIGN_DEFAULTCOOKIES(svcdat);

            svcdat.UserHidden = FALSE;            
            svcdat.SystemHidden = FALSE;
            svcdat.EPGEnabled = FALSE;
            svcdat.EPGShortInfo = FALSE;
            svcdat.UserModifiedName = FALSE;
            presetdat.UniqueNodeId  = -1;// Invalid Node id 
            pgdb_Add(PRESET_TABLE, (Address )&presetdat);

            /* Pavan */
            if(AUTO_INSTALL)
            {
                svcdat.NewPreset = FALSE; 
            }
            else
            {   /* Background & Update */
                svcdat.NewPreset = TRUE;
                sortN_OnEvent(sortN_EventNewPresetFound,rins_GetInstallationMode());
            }

            svcdat.PresetNumber = presetdat.PresetNumber;  
            pgdb_Update(SERVICE_TABLE, (Address)&svcdat);

            TraceDebug(m,"Addition at Preset %d by <%d,%d>\n", presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.ServiceId);


            mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;;

            CurrentPresetIndex = presetdat.PresetNumber + 1;            
        }
        if(IS_RADIO_SERVICE(svcdat.ServiceType))
        {
            TraceInfo(m,"%s %d mCurrentRadioIndex: %d CurrentPresetIndex%d", __FUNCTION__, __LINE__, mCurrentRadioIndex, CurrentPresetIndex);
            mCurrentRadioIndex = CurrentPresetIndex;
        }
        else
        {
            TraceInfo(m,"%s %d mCurrentPresetIndex: %d CurrentPresetIndex%d", __FUNCTION__, __LINE__, mCurrentPresetIndex, CurrentPresetIndex);
            mCurrentPresetIndex = CurrentPresetIndex;
        }
    }
    else
    {
        TraceInfo(m,"%d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}

int CHsvEuropeInstallation_mlitesort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
{
    int retval = 0;
    HsvPgdatDigServiceData pref_svcdata;

    if( pgdb_GetByIndex(SERVICE_TABLE, pref_index, (Address) (&pref_svcdata)) )
    {
        retval = mGetServicePriority(pref_svcdata.ServiceType) - mGetServicePriority(svcdata->ServiceType);

        retval = (retval == 0)? (svcdata->LCN - pref_svcdata.LCN):retval;    

        retval = (retval == 0)? mStrCmp(svcdata->ChannelName, pref_svcdata.ChannelName):retval;

        retval = (retval == 0)? (svcdata->ServiceId - pref_svcdata.ServiceId):retval;
    }
    return retval;
}

int CHsvEuropeInstallation_mlitesort_Priv::mStrCmp( Nat16 * str1, Nat16 * str2 )
{
    int ret = 0;

    ASSERT( NULL != str1 ); /* Must not be the NULL pointer */
    ASSERT( NULL != str2 ); /* Must not be the NULL pointer */

    while( !ret && (*str1 || *str2) )
    {
        ret = toupper(*str1) - toupper(*str2);
        str1++, str2++;
    }

    return ret;
}   /* mStrCmp   */

int CHsvEuropeInstallation_mlitesort_Priv::mGetServicePriority(int serviceType)
{
    int i = 0, retval = 1;
    Bool found = FALSE;

    if(cids_CountryChina != sysset_GetInstallCountry())
    {
        for(i = 0; i < MAX_SERVICE_TYPES1; i++)
        {
            if(serviceType == mServicePriority[i])
            {
                found = TRUE;
                break;
            }
        }
    }
    else
    {
        for(i = 0; i < MAX_CHINA_SERVICE_TYPES; i++)
        {
            if(serviceType == mChinaServicePriority[i])
            {
                found = TRUE;
                break;
            }
        }
    }

    /* In case we dont find anything, just fallback to previous case */
    retval = (TRUE == found) ? i: ConvertToDVBServiceType(serviceType);

    return retval;
}

Bool CHsvEuropeInstallation_mlitesort_Priv::CallBackHsvAnalog(Address data)
{
    Bool retval = FALSE;
    HsvChannel* Channel = (HsvChannel*)data;
    if(Channel->Type == HsvAnalog)
    {
        retval = TRUE;
    }
    return retval;
}

Bool CHsvEuropeInstallation_mlitesort_Priv::IsFreqUserInstalled(Nat32 Frequency, Nat16 StreamPriority)
{
    Bool retval = FALSE;
    HsvPgdatDigTSData tsdat;    

    tsdat.Frequency     =   Frequency;
    tsdat.StreamPriority   =   StreamPriority;

    if(TRUE == pgdb_GetByKey( PTC_TABLE, (Address) &tsdat) )
    {
        retval = tsdat.UserInstalled;
    }
    return retval;
}

int CHsvEuropeInstallation_mlitesort_Priv::ConvertToDVBServiceType(int servicetype)
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
        case AppApiPALCodedSignal:
            retval  =   PALCodedSignal;
            break;
        case AppApiSECAMCodedSignal:
            retval  =   SECAMCodedSignal;
            break;
        case AppApiUserDefinedHD1:
            retval  =   UserDefinedHD1;
            break;
        case AppApiUserDefinedHD2:
            retval  =   UserDefinedHD2;
            break;
        case AppApiUserDefinedHD3:
            retval  =   UserDefinedHD3;
            break;
        case AppApiUserDefinedHD4:
            retval  =   UserDefinedHD4;
            break;
		case AppApi3DHDDigitalService:
			retval =    HD3DDigitalService;
			break;

        default:
            break;
    }
    return retval;
}

inline int CHsvEuropeInstallation_mlitesort_Priv::mLastNonRadioDigitalPreset(void)
{
    HsvPgdatPresetData presetdata;
    int i = 0, retval = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE), numdigservice = pgdb_GetNoRecords(SERVICE_TABLE);

    for(i = 0; (numdigservice) && (i < NoOfRecords); i++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdata))
        {
            if(presetdata.PresetNumber < MAX_LCN_VALUE)
            {
                retval = presetdata.PresetNumber;
                break;
            }
        }
    }

    return retval;
}

inline int CHsvEuropeInstallation_mlitesort_Priv::mLastLCNBasedPreset(Bool CheckForRadioServices)
{
    int i = 0, retval = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatPresetData presetdata;
    HsvPgdatDigServiceData svcdat;

    for(i = 0; i < NoOfRecords; i++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdata))
        {
            if(IS_DIGITAL_PRESET(presetdata.Type))
            {
                ASSIGN_SVC_FROM_PRESET(svcdat, presetdata);
                if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat))
                {
                    if(IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices)
                    {   
                        if( (VALID_LCN_RANGE(svcdat.LCN)) && (ASSIGN_PRESET_NUMBER(svcdat.LCN, svcdat.ServiceType) == presetdata.PresetNumber) )
                        {
                            retval = svcdat.PresetNumber;
                            break;
                        }
                    }
                }
            }
        }
    }

    return retval;
}

inline int CHsvEuropeInstallation_mlitesort_Priv::mFindPlaceForAnalogPresets(void)
{
    int retval = INVALID_PRESET, FromPreset = 1;
    HsvPgdatPresetData presetdata;
    HsvChannel preset;

    if(apperr_Ok == iadvpgitr_GetLastChannel(&preset, TRUE))
    {
        presetdata.PresetNumber = preset.Channel.Digit + 1;
        presetdata.Type = HsvOnePart;

        if( pgdb_GetByKey(PRESET_TABLE, (Address) (&presetdata)) )
        {
            /* RESET the retval, so as to find the largest Gap in following code */
            retval = INVALID_PRESET;
        }
        else
        {
            retval = preset.Channel.Digit + 1;
        }
    }

    if(retval == INVALID_PRESET)
    {
        FromPreset = mLastNonRadioDigitalPreset();

        if(FromPreset == INVALID_PRESET)
        {
            FromPreset = START_PRESET;
        }

        retval = mLargestGapInForwardRange(FromPreset, MAX_LCN_VALUE);
    }

    return retval;
}


int CHsvEuropeInstallation_mlitesort_Priv::mLargestGapInForwardRange(int FromPreset, int ToPreset)
{
    int i = 0, LargestPresetGap = 1, PreviousPreset = ToPreset, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);    
    HsvPgdatPresetData presetdat;
    int passval = 0;

    /* Below is the heart of the sorting module, beware of PRs before modifying it :) */
    if(NoOfRecs == 0)
    {
        TraceNotice(m,"%s:%d:FromPreset=%d",__FUNCTION__,__LINE__,FromPreset);
        return FromPreset;
    }

    if(NoOfRecs == 1)
    {
        pgdb_GetByIndex( PRESET_TABLE, 0, (Address)&presetdat );

        /* Boundary condition */
        Retval = (presetdat.PresetNumber == FromPreset)? (presetdat.PresetNumber + 1):FromPreset;
        return Retval;
    }

    for(i = (NoOfRecs - 1); i >= 0; i--)
    {
        pgdb_GetByIndex( PRESET_TABLE, i, (Address)&presetdat );

        if(presetdat.PresetNumber <= ToPreset)
        {
            passval = 1;
            if(presetdat.PresetNumber <= FromPreset) 
            {
                PreviousPreset = presetdat.PresetNumber;
                if(i == 0)
                {
                    /* Boundary termination condition 1 */
                    Retval = (presetdat.PresetNumber == FromPreset)? (presetdat.PresetNumber + 1):FromPreset;
                    break;
                }   
                else
                {
                    passval = 0;
                }
            }

            if (passval) 
            {
                if( (PreviousPreset >= FromPreset) && ((presetdat.PresetNumber - PreviousPreset) > LargestPresetGap) )
                {
                    Retval = PreviousPreset + 1; 
                    LargestPresetGap = (presetdat.PresetNumber - PreviousPreset);
                    if(i == 0)
                    {
                        /* Boundary termination condition 2 */
                        if( LargestPresetGap < ((int)(ToPreset - presetdat.PresetNumber)) )
                        {
                            Retval = (presetdat.PresetNumber < ToPreset)?(presetdat.PresetNumber + 1):INVALID_PRESET; 
                        }
                        break;
                    }
                }
                else
                {
                    if(i == 0)
                    {
                        /* Boundary termination condition 3 */
                        if( LargestPresetGap < ((int)(ToPreset - presetdat.PresetNumber)) )
                        {
                            Retval = (presetdat.PresetNumber < ToPreset)?(presetdat.PresetNumber + 1):INVALID_PRESET; 
                        }
                        break;
                    }               
                    else
                    {
                        PreviousPreset = presetdat.PresetNumber;
                    }
                }
            }
        }
        else
        {
            /* entering into other boundaries, out of the interested range */
            int LastGap = (presetdat.PresetNumber - PreviousPreset);
            if( (LastGap != 1) && (LastGap > LargestPresetGap) )
            {
                Retval = PreviousPreset + 1;
            }
            break;
        }
    }



    TraceDebug(m,"%s %d Retval %d PreviousPreset %d presetdat.PresetNumber %d NoOfRecs %d LargestPresetGap %d\n", __FUNCTION__, __LINE__, Retval, PreviousPreset, presetdat.PresetNumber, NoOfRecs, LargestPresetGap);
    return Retval;
}

int CHsvEuropeInstallation_mlitesort_Priv::GetAutomaticPlatformPresetNumber(void)
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
Bool CHsvEuropeInstallation_mlitesort_Priv::mValidPresetRange(int SvcType, int presetno)
{
    Bool retval = FALSE;

    if( IS_RADIO_SERVICE(SvcType) )
    {
        retval = (presetno <= (MAX_LCN_VALUE + div_MaxValidLCNValue)) && (presetno >= (MAX_LCN_VALUE + div_MinValidLCNValue));
    }
    else
    {
        retval = (presetno <= div_MaxValidLCNValue) && (presetno >= div_MinValidLCNValue);
    }
    TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}


/*Stub */
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_DeleteAllDigitalChannels()
{
	return 0;
}    

Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_UpdatingLCNDuringUpdateInstallation()
{
	return 0;
}
Bool CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_AssignPresetsOfOtherCountries   (void)
{
	return 0;
}
int CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_GetOriginalNetworkId(int CurrentCountry)
{
	return 0;
}
void CHsvEuropeInstallation_mlitesort_Priv::idvbclitesort_RemoveDigitalPresets(void)
{
	return;
}
