/**********************************************************************
 *
 *   C Source:       hsveuins_mnorsort.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Tue Mar 27 14:17:26 2012 %
 *
 **********************************************************************/
#include "_hsveuins_mnorsort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mnorsort")










#ifndef __cplusplus

#endif








/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/

























/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvEuropeInstallation_mnorsort_Priv::s__mnorsortPmp;

int CHsvEuropeInstallation_mnorsort_Priv::s__mFirstInstalledPreset = 0xFFFF,CHsvEuropeInstallation_mnorsort_Priv::s__mCurrentRadioIndex,CHsvEuropeInstallation_mnorsort_Priv::s__mCurrentPresetIndex;

/* Priority is in increasing order. Refer to honouring rules sheet of vsd  */
int CHsvEuropeInstallation_mnorsort_Priv::s__mServicePriority[MAX_SERVICE_TYPES1] =
{
    AppApiDatabroadcastService,
    AppApiTeletextService,
    AppApiRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiAdvCodecSDTelevisionService,
    AppApiAdvCodecHDTelevisionService   
};


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvEuropeInstallation_mnorsort_Priv::mnorsortHandler(int value, Nat32 param)
{
    UNUSED(param);
    HsvSortingRules InterestedPresets;
    TraceDebug(m,"%s: CURRENT STEP = %d",__FUNCTION__, value);

    if((rins_GetLCNSortingControl() == FALSE) && (value != evStepAll))
    {
        value = evNoSorting;
    }

    switch(value)
    {
        case evStep1:
            /* NONRADIO CURRENT ONID, FAVOURITE NID HONOURED PRESETS */
            TraceDebug(m,"%s %d NONRADIO CURRENT ONID, FAVOURITE NID HONOURED PRESETS", __FUNCTION__, __LINE__);
            mSortDigitalHonouredPresets(FALSE, value);
            mSortDigitalHonouredPresets(TRUE, value);
            mSortDigitalNonFavHonouredPresets(FALSE, value);
            break;
        case evStep2:
            /* NONRADIO CURRENT ONID, FAVOURITE NID NON HONOURED PRESETS */
            TraceDebug(m,"%s %d NONRADIO CURRENT ONID, FAVOURITE NID NON HONOURED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForNID = TRUE;
            InterestedPresets.CheckForUnInstalledPreset = InterestedPresets.CheckForRadioService = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;
        case evStep3:
            /* NONRADIO CURRENT ONID, NON FAVOURITE NID NON HONOURED PRESETS */
            TraceDebug(m,"%s %d NONRADIO CURRENT ONID, NON FAVOURITE NID NON HONOURED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = TRUE;
            InterestedPresets.CheckForNID = InterestedPresets.CheckForUnInstalledPreset = InterestedPresets.CheckForRadioService = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;
        case evStep4:
            /* NONRADIO CURRENT ONID, FAVOURITE NID UNINSTALLED PRESETS */
            TraceDebug(m,"%s %d NONRADIO CURRENT ONID, FAVOURITE NID UNINSTALLED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForNID = InterestedPresets.CheckForUnInstalledPreset = TRUE;
            InterestedPresets.CheckForRadioService = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;
        case evStep5:
            /* NONRADIO CURRENT ONID, NON FAVOURITE NID UNINSTALLED PRESETS */
            TraceDebug(m,"%s %d NONRADIO CURRENT ONID, NON FAVOURITE NID UNINSTALLED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForUnInstalledPreset = TRUE;
            InterestedPresets.CheckForNID = InterestedPresets.CheckForRadioService = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;
        case evStep6:
            /* NONRADIO REMAINING PRESETS */
            TraceDebug(m,"%s %d NONRADIO REMAINING PRESETS ", __FUNCTION__, __LINE__);
            mSortRemainingDigitalPresets(FALSE, value);
            break;
        case evStep7:   
            /* ANALOG PRESETS */
            TraceDebug(m,"%s %d ANALOG PRESETS ", __FUNCTION__, __LINE__);
            mSortAnalogPresets(value);
            break;
        case evStep8:       
            /* RADIO CURRENT ONID, FAVOURITE NID HONOURED PRESETS */
            TraceDebug(m,"%s %d RADIO CURRENT ONID, FAVOURITE NID HONOURED PRESETS ", __FUNCTION__, __LINE__);
            mSortDigitalNonFavHonouredPresets(TRUE, value);
            break;
        case evStep9:
            /* RADIO CURRENT ONID, FAVOURITE NID NON HONOURED PRESETS */
            TraceDebug(m,"%s %d RADIO CURRENT ONID, NON FAVOURITE NID HONOURED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForNID = InterestedPresets.CheckForRadioService = TRUE;
            InterestedPresets.CheckForUnInstalledPreset = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;  
        case evStep10:
            /* RADIO CURRENT ONID, NON FAVOURITE NID NON HONOURED PRESETS */
            TraceDebug(m,"%s %d RADIO CURRENT ONID, NON FAVOURITE NID NON HONOURED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForRadioService = TRUE;
            InterestedPresets.CheckForNID = InterestedPresets.CheckForUnInstalledPreset = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;
        case evStep11:
            /* RADIO CURRENT ONID, FAVOURITE NID UNINSTALLED PRESETS */
            TraceDebug(m,"%s %d RADIO CURRENT ONID, FAVOURITE NID UNINSTALLED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForRadioService = InterestedPresets.CheckForNID = TRUE;
            InterestedPresets.CheckForUnInstalledPreset = TRUE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;
        case evStep12:
            /* RADIO CURRENT ONID, NON FAVOURITE NID UNINSTALLED PRESETS */
            TraceDebug(m,"%s %d RADIO CURRENT ONID, NON FAVOURITE NID UNINSTALLED PRESETS ", __FUNCTION__, __LINE__);
            InterestedPresets.CheckForONID = InterestedPresets.CheckForRadioService = InterestedPresets.CheckForUnInstalledPreset = TRUE;
            InterestedPresets.CheckForNID = FALSE;
            mSortDigitalNonHonouredPresets(InterestedPresets, value);
            break;

        case evStep13:
            /* RADIO REMAINING PRESETS */
            TraceDebug(m,"%s %d RADIO REMAINING PRESETS ", __FUNCTION__, __LINE__);
            mSortRemainingDigitalPresets(TRUE, value);
            break;  

        case evStepAll:
            TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
            inorsort_DeleteInvalidPTCTable();
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

void CHsvEuropeInstallation_mnorsort_Priv::mNoSorting(int evCurrentSortStep)
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
        		if((div_IsServiceHidden(rins_GetMedium(),ConvertToDVBServiceType(svcdat.ServiceType)))
                    ||(div_InstallTestStreams(rins_GetInstallationMode(),rins_GetMedium()) == div_Hide))
        		{
        			svcdat.SystemHidden = TRUE;
        		}
        		else
        		{
        			svcdat.SystemHidden = !(svcdat.VisibleService);
        		}
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
                    (inorsort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                ++mCurrentPresetIndex;
                presetdat.PresetNumber = mCurrentPresetIndex;
                presetdat.AnalogTablePreset = anadat.PresetNumber;
                presetdat.Type = HsvAnalog;
                presetdat.Frequency = anadat.Frequency;
                presetdat.UniqueNodeId = -1;// Invalid Node id

                ASSIGN_DEFAULTCOOKIES(anadat);
                pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                pgdb_Update(ANALOG_TABLE,(Address) &anadat);
            }
            else
            {
                TraceErr(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set\n", __LINE__, anadat.Frequency);
            }
        }
        else
        {
            TraceErr(m,"%d Analog data suddenly deleted from database\n", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    pmp_PmpSend(mnorsortPmp, evStepAll, (Nat32)NULL);
}

/*****************************************
  provides IHsvHybridPresetSort cabsort
 ******************************************/

void CHsvEuropeInstallation_mnorsort_Priv::inorpow_Init()
{
    mnorsortPmp = pmp_PmpCreateEx( pen_PumpEngine, mnorsortHandler, FALSE, "hsveuins_mnorsort" );
}

void CHsvEuropeInstallation_mnorsort_Priv::inorsort_Initialise()
{
    mFirstInstalledPreset = 0xFFFF;

	// This is the Fix for PR AN-70206
  	mCurrentPresetIndex = 0;
    mCurrentRadioIndex = 0;
        
}

void CHsvEuropeInstallation_mnorsort_Priv::inorsort_AddAnalogPreset(Address adata)
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
  //  panadat->Favorite = 0;
//    panadat->UserHidden = 0;
    panadat->PreferredStereo = 1;
	panadat->FavoriteNumber	= 0;
	panadat->UserModifiedLogo = 0;
	panadat->UserModifiedName = 0;
	panadat->LogoURL = 0;
    pgdb_Add (ANALOG_TABLE, (Address)adata);

}

void CHsvEuropeInstallation_mnorsort_Priv::mSortAnalogPresets(int evCurrentSortStep)
{
    HsvPgdatAnalogData anadat;
    HsvPgdatPresetData presetdat;
    int i, NoOfRecords = pgdb_GetNoRecords(ANALOG_TABLE), presetno = INVALID_PRESET;

    TraceDebug(m,"%s %d NoOfRecords: %d", __FUNCTION__, __LINE__, NoOfRecords);

    presetno = mFindPlaceForAnalogPresets();
    for(i = (NoOfRecords - 1); i >= 0; i--)
    {   
        if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
        {
            /* Only for installed analog presets */
            if( (TRUE == anadat.Tuned) && 
                    (inorsort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                /* Allocate the current number */
                presetdat.PresetNumber = presetno;
                TraceDebug(m,"%s %d presetdat.PresetNumber : %d", __FUNCTION__, __LINE__, presetdat.PresetNumber);
                presetdat.AnalogTablePreset = anadat.PresetNumber;

                if(presetdat.PresetNumber >= MAX_LCN_VALUE )
                {
                    presetdat.PresetNumber = presetno = mFindPlaceForAnalogPresets();

                }

                if(INVALID_PRESET != presetdat.PresetNumber)
                {
                    presetdat.Type = HsvAnalog;
                    presetdat.Frequency = anadat.Frequency;
                    presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    ASSIGN_DEFAULTCOOKIES(anadat);

                    pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                    pgdb_Update(ANALOG_TABLE,(Address) &anadat);

                    presetno++;
                }
                else
                {
                    TraceDebug(m,"%d Cannot Add Analog Preset as there is no place in the PRESET LIST", __LINE__);
                    ASSERT(!"Analog table is FULL");
                    break;
                }
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

    int evNextSortStep = evCurrentSortStep + 1;
    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mnorsortPmp, evNextSortStep, (Nat32)NULL);
}

void CHsvEuropeInstallation_mnorsort_Priv::inorsort_AddDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    if( MANUAL_INSTALL || BACKGROUND_INSTALL )
    {
        int dbindex;
        Bool retval = FALSE;

        TraceDebug(m,"%s %d: LCN = %d",__FUNCTION__,__LINE__,psvcdat->LCN);

        if(TRUE == pgdb_GetIndex(SERVICE_TABLE, &dbindex, (Address)psvcdat))
        {
            /* Try to obtain a Preset using InvalidLCN algorithm */
            if (mValidLCNRange(psvcdat->LCN,psvcdat->ServiceType))
            {
                retval = mDigitalPresetEntryforValidLCN(psvcdat);
            }

            if( retval == FALSE)
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

Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AutoStoreManualInstallationValues()
{
    Bool retval = FALSE;
    HsvPgdatPresetData newpresetdat;
    HsvPgdatAnalogData    anadat;
    HsvChannel channel;
    int presetno = INVALID_PRESET;
    pgdb_Initialise (pgdbconst_Preset,  &newpresetdat);   	
    if(pgdb_GetNoRecords(ANALOG_TABLE) < div_MaxAnalogPresets )
    {
        presetno = mFindPlaceForAnalogPresets();

        if(presetno != INVALID_PRESET)
        {   
            /* Create a User Table entry */
            TraceDebug(m,"%d Preset = %d", __LINE__, presetno);
            newpresetdat.PresetNumber = presetno;
            newpresetdat.AnalogTablePreset = newpresetdat.PresetNumber;
            newpresetdat.Type = HsvAnalog;

            ASSIGN_DEFAULTCOOKIES(anadat);
            newpresetdat.UniqueNodeId   = -1;// Invalid Node id 
            pgdb_Add(PRESET_TABLE, (Address)&newpresetdat);

            /* Create an Analog Preset */
            anadat.PresetNumber = presetno;
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
                anadat.PresetNumber = presetno;
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

int CHsvEuropeInstallation_mnorsort_Priv::inorsort_GetNumberOfAnalogChannelsFound()
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

void CHsvEuropeInstallation_mnorsort_Priv::inorsort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
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
            TraceDebug(m,"Updated Preset %d with new information from <%d,%d,%d,%d>", presetdat.PresetNumber,psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->StreamPriority, psvcdat->Frequency); 
        }
        else
        {
            TraceDebug(m,"%s %d",__FUNCTION__, __LINE__);
        }
    }          
}

Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_UpdatingLCNDuringUpdateInstallation()
{
    /* To be implemented */
    return FALSE;
}

/*****************************************************************************
  This is actually for Best Mux only. But since we can install DVBT also on
  cable, this function still exists
 *****************************************************************************/
Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_DeleteInvalidPTCTable()
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

void CHsvEuropeInstallation_mnorsort_Priv::inorsort_SortAll()
{
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    pmp_PmpSend(mnorsortPmp, evStep1, (Nat32)NULL);
}

int CHsvEuropeInstallation_mnorsort_Priv::inorsort_GetOriginalNetworkId(int CurrentCountry)
{
    Nat16 ONWID   = 0xFFFF;

    switch(CurrentCountry)
    {  
#define COUNTRYITEM(a, b, c)    case cids_Country##b:   \
        ONWID   =   c + 0x2000; \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvcountry.h"
#else
#include "hsvcountry.h"
#endif

        default:
            {   /* For Other Country */
                HsvPgdatDigTSData tsdat;
                int i = 0;      
                int TSesWithKnownONWID = TRUE;
                int CurrentSignalStrength = 0;
                int MaxTransportStreams = pgdb_GetNoRecords(PTC_TABLE);

                if(MaxTransportStreams > 0 )
                {
                    FResult res = pgdb_GetByIndex(PTC_TABLE, 0, (Address)&tsdat);
                    if(res != FALSE)
                    {
                        ONWID                   = tsdat.OriginalNetworkId;
                        CurrentSignalStrength   = tsdat.ASignalStrength;
                    }
                    else
                    {
                        ASSERT(!"Service suddenly deleted.");
                        ONWID   = 0xFFFF;
                    }
                }
                else
                {
                    /* No Transport Stream */
                    ASSERT(!"Transport stream is not present");
                    ONWID = 0xFFFF;
                }


                for(i = 0; (i < MaxTransportStreams); i++)
                {
                    if(TRUE == pgdb_GetByIndex(PTC_TABLE, i, (Address)&tsdat))
                    {
                        switch(tsdat.OriginalNetworkId - 0x2000)
                        {
#define COUNTRYITEM(a, b, c)    case cids_Country##b:   
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvcountry.h"
#else
#include "hsvcountry.h"
#endif

                            {
                                if( (TRUE == TSesWithKnownONWID ) && 
                                        (tsdat.ASignalStrength > (Nat32)CurrentSignalStrength ) )
                                {   /* Streams with all known ONWID, get the best reception quality */                                     
                                    ONWID                   = tsdat.OriginalNetworkId;
                                    CurrentSignalStrength   = tsdat.ASignalStrength;
                                }
                                break;
                            }
                            default:
                            {   
                                if( TRUE == TSesWithKnownONWID)
                                {   /* Oh! we encountered a TS with an unknown ONWID */
                                    TSesWithKnownONWID = FALSE;
                                    ONWID                   = tsdat.OriginalNetworkId;
                                    CurrentSignalStrength   = tsdat.ASignalStrength;
                                }
                                else
                                {
                                    if (tsdat.ASignalStrength > (Nat32)CurrentSignalStrength) 
                                    {   /* Streams with all unknown ONWID, get the best reception quality */                                       
                                        ONWID                   = tsdat.OriginalNetworkId;
                                        CurrentSignalStrength   = tsdat.ASignalStrength;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        ONWID = 0xFFFF;
                        break;
                    }
                }
                break;  /* end of default */
            }
    }
    TraceInfo(m,"CurrentONID = %d", ONWID);
    return (int )ONWID;
}

Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_IsPresetInstalled(Int32 frequency)
{
    Bool retval = FALSE;
    Nat32 minfreq = START_FREQUENCY, maxfreq = END_FREQUENCY, result = 0;
	frequency = (frequency * 16)/1000;

    if(UPDATE_INSTALL || MANUAL_INSTALL)
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
                    {   /* Finally we decided ABS might not be easy to debug & wrote this one ! */
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
                    }
                }
            }
        }        
    }

    return retval;
}
/***********************************/

void CHsvEuropeInstallation_mnorsort_Priv::mSortDigitalHonouredPresets(Bool CheckForRadioService, int evCurrentSortStep)
{
    UNUSED(evCurrentSortStep);
    int dbindex, from = 0, to = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool retval = TRUE;

    TraceDebug(m,"%s %d SORTING OF %s", __FUNCTION__, __LINE__, CheckForRadioService?"RADIO SERVICES":"NON RADIO SERVICES");

    svcdat.OriginalNetworkId =   (Nat16 ) inorsort_GetOriginalNetworkId(sysset_GetSystemCountry());
    retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
    TraceDebug(m,"%s %d from %d to %d retval %d", __FUNCTION__, __LINE__, from, to, retval);

    if(retval)
    {

        for( dbindex = from; dbindex <= to; dbindex++)
        {
            if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
            {
                /* below is a bit tricky :) */
                if(MANUAL_INSTALL)
                {
                    /* if in manual mode, then honor the frequnecy of this only, and overrule everything, favorite network also */
                    retval = IsFreqUserInstalled(svcdat.Frequency, svcdat.StreamPriority);
                }
                else
                {
                    retval = mIsFavouriteNetworkID(svcdat);
                }

                if(retval)
                {

                    if( PRESET_NOT_ALLOCATED(svcdat.PresetNumber) && mValidLCNRange(REVALIDATE(svcdat.LCN),svcdat.ServiceType) 
                            && (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioService) )
                    {
                        mDigitalPresetEntryforValidLCN(&svcdat);
                    }
                    else
                    {
                        /* Non Honoured LCN or RADIO Service or DVBT preset.
                           So lets come back later */
                    }
                }
            }
            else
            {
                ASSERT(!" Who deleted the service here ");
            }
        }
    }
}

void CHsvEuropeInstallation_mnorsort_Priv::mSortDigitalNonFavHonouredPresets(Bool CheckForRadioService, int evCurrentSortStep)
{
    int dbindex, from = 0, to = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    Bool retval = TRUE;

    TraceDebug(m,"%s %d SORTING OF %s", __FUNCTION__, __LINE__, CheckForRadioService?"RADIO SERVICES":"NON RADIO SERVICES");

    svcdat.OriginalNetworkId =   (Nat16 ) inorsort_GetOriginalNetworkId(sysset_GetSystemCountry());
    retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
    TraceDebug(m,"%s %d from %d to %d retval %d", __FUNCTION__, __LINE__, from, to, retval);

    if(retval)
    {
        for( dbindex = from; dbindex <= to; dbindex++)
        {
            if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
            {
                presetdat.PresetNumber = REVALIDATE(svcdat.LCN);
                presetdat.Type = HsvOnePart;
                if( PRESET_NOT_ALLOCATED(svcdat.PresetNumber) && 
                        mValidLCNRange(svcdat.LCN,svcdat.ServiceType) && 
                        (FALSE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat)) &&
                        (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioService) )
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
    }
    int evNextSortStep = evCurrentSortStep + 1;
    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mnorsortPmp, evNextSortStep, (Nat32)NULL);
}


void CHsvEuropeInstallation_mnorsort_Priv::mSortDigitalNonHonouredPresets(HsvSortingRules InterestedPresets, int evCurrentSortStep)
{
    int i = 0, retval = TRUE, pref_dbindex = -1, dbindex = 0, from = 0, to = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool pref_index_found = TRUE;

    int SmallLCNOfSpecialService = LAST_PRESET_FOR_SPECIAL_SERVICE;

    if(InterestedPresets.CheckForONID)
    {
        svcdat.OriginalNetworkId =   (Nat16 ) inorsort_GetOriginalNetworkId(sysset_GetSystemCountry());
        retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
        TraceDebug(m,"%s %d from %d to %d retval %d", __FUNCTION__, __LINE__, from, to, retval);
    }

    for( i = from; retval && (i < to) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = from; dbindex < to; dbindex++)
        {
            if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
            {
                if( PRESET_NOT_ALLOCATED(svcdat.PresetNumber) && 
                        (InterestedPresets.CheckForNID == mIsFavouriteNetworkID(svcdat)) &&
                        (InterestedPresets.CheckForRadioService == IS_RADIO_SERVICE(svcdat.ServiceType)) &&
                        (InterestedPresets.CheckForUnInstalledPreset == IS_UNINSTALLED_PRESET(svcdat)) )
                {
                    if(pref_index_found == FALSE)
                    {
                        /* First time in the loop */
                        pref_dbindex = dbindex;
                        pref_index_found = TRUE;
                    }
                    else
                    {
                        int lcn = svcdat.LCN;

                        if( IS_SPECIAL_SERVICE(REVALIDATE(lcn)) )
                        {
                            /* The Sorting order for Special services is based on LCN order as per the new CR */
                            if(SmallLCNOfSpecialService > lcn)
                            {
                                pref_dbindex = dbindex;
                                SmallLCNOfSpecialService = lcn;
                            }
                        }
                        else if(mCompareServices(&svcdat, pref_dbindex) < 0)
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

        if( (pref_dbindex >= from) && (pref_index_found == TRUE))
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }           

    int evNextSortStep = evCurrentSortStep + 1;
    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mnorsortPmp, evNextSortStep, (Nat32)NULL);
}

void CHsvEuropeInstallation_mnorsort_Priv::mSortRemainingDigitalPresets(Bool CheckForRadioService, int evCurrentSortStep)
{
    int i = 0, pref_dbindex = -1, dbindex = 0, to = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool pref_index_found = TRUE;

    int SmallLCNOfSpecialService = LAST_PRESET_FOR_SPECIAL_SERVICE;

    for(; (i < to) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = 0; dbindex < to; dbindex++)
        {
            if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
            {

                if( PRESET_NOT_ALLOCATED(svcdat.PresetNumber) &&
                        (CheckForRadioService == IS_RADIO_SERVICE(svcdat.ServiceType)) )
                {

                    if(pref_index_found == FALSE)
                    {
                        /* First time in the loop */
                        pref_dbindex = dbindex;
                        pref_index_found = TRUE;
                    }
                    else
                    {
                        int lcn = svcdat.LCN;

                        if( IS_SPECIAL_SERVICE(REVALIDATE(lcn)) )
                        {
                            /* The Sorting order for Special services is based on LCN order as per the new CR */
                            if(SmallLCNOfSpecialService > lcn)
                            {
                                pref_dbindex = dbindex;
                                SmallLCNOfSpecialService = lcn;
                            }
                        }
                        else if(mCompareServices(&svcdat, pref_dbindex) < 0)
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
        TraceDebug(m,"%s %d pref_dbindex %d, pref_index_found %d ", __FUNCTION__, __LINE__, pref_dbindex,pref_index_found);

        if( (pref_dbindex >= 0) && (pref_index_found == TRUE))
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }           

    int evNextSortStep = evCurrentSortStep + 1;
    TraceDebug(m,"Pmp send done with event = %d", evNextSortStep);
    pmp_PmpSend(mnorsortPmp, evNextSortStep, (Nat32)NULL);
}

Bool CHsvEuropeInstallation_mnorsort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
    HsvPgdatDigServiceData oldsvcdat;
    HsvPgdatPresetData presetdat, tmppresetdat;


    Bool PresetRequireRefilling = FALSE, retval = FALSE;

    REVALIDATE(svcdat->LCN);

    presetdat.PresetNumber = svcdat->LCN;
    presetdat.Type = HsvOnePart;

    if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat))
    {

        if(AUTO_INSTALL || MANUAL_INSTALL)
        {   
            ASSIGN_SVC_FROM_PRESET(oldsvcdat, presetdat);
            if (pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat))
            {
                if((oldsvcdat.ServiceListVersion == INSTALL_VERSION) &&
                        ((!mValidLCNRange(oldsvcdat.LCN,oldsvcdat.ServiceType)) || (oldsvcdat.VisibleService == FALSE) ) )
                {
                    /* Existing service has a LCN where as already installed one in current installation 
                       doesnt have LCN. So lets refill */
                    PresetRequireRefilling = TRUE;
                    TraceDebug(m,"%s %d PresetRequireRefilling %d ", __FUNCTION__, __LINE__, PresetRequireRefilling);
                }
                else
                {
                    int svcdatPriority = mGetServicePriority(svcdat->ServiceType);
                    int oldsvcdatPriority = mGetServicePriority(oldsvcdat.ServiceType);

                    if( (svcdatPriority > oldsvcdatPriority) || 
                            ((svcdatPriority == oldsvcdatPriority) && (oldsvcdat.LCN == INVALID_LCN)) )
                    {
                        /* Current contestant has higher priority than existing Service Type.
                           So strip him of his preset position.*/
                        PresetRequireRefilling = TRUE;
                        TraceDebug(m,"%s %d PresetRequireRefilling %d ", __FUNCTION__, __LINE__, PresetRequireRefilling);
                    }
                    else
                    {
                        HsvPgdatDigTSData oldtsdat, tsdata;
                        oldtsdat.Frequency  =   oldsvcdat.Frequency;
                        oldtsdat.StreamPriority   =   oldsvcdat.StreamPriority;

                        tsdata.Frequency    =   svcdat->Frequency;
                        tsdata.StreamPriority   =   svcdat->StreamPriority;

                        if( pgdb_GetByKey (PTC_TABLE,(Address) &oldtsdat) && pgdb_GetByKey (PTC_TABLE, (Address)&tsdata) )
                        {
                            /* Also check for the similar service types => Radio/TV Service */
                            if( (oldtsdat.ASignalStrength  < tsdata.ASignalStrength) &&
                                    (IS_RADIO_SERVICE(svcdat->ServiceType) == IS_RADIO_SERVICE(oldsvcdat.ServiceType)) )
                            {
                                PresetRequireRefilling = TRUE;
                                TraceDebug(m,"%s %d PresetRequireRefilling %d oldtsdat.ASignalStrength %d tsdata.ASignalStrength %d", __FUNCTION__, __LINE__, PresetRequireRefilling, (int)oldtsdat.ASignalStrength, (int) tsdata.ASignalStrength);
                            }
                        }
                    }
                }

                if (rins_InstallationModeWeakSignal == rins_GetInstallationMode())
                {
                    PresetRequireRefilling = TRUE;                  
                }

            }
        }
        if(PresetRequireRefilling)
        {
            /* Ya - we found a better candidate for using this preset */
            INVALIDATE(oldsvcdat.LCN);
            oldsvcdat.PresetNumber = INVALID_PRESET;
            pgdb_Update(SERVICE_TABLE,(Address)&oldsvcdat); 

            TraceDebug(m,"ServiceType = %d",svcdat->ServiceType);
            presetdat.PresetNumber = svcdat->LCN;
            presetdat.Type = HsvOnePart;

            ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
            ASSIGN_DEFAULTCOOKIES(*svcdat);

            svcdat->UserHidden = FALSE;

            /* Change Made to Implement CR ehv02mgr#16143 */
            if( (div_IsServiceHidden(rins_GetMedium(),ConvertToDVBServiceType(svcdat->ServiceType)))
                    || (div_InstallTestStreams(rins_GetInstallationMode(),rins_GetMedium()) == div_Hide) )
            {
                svcdat->SystemHidden = TRUE;
            }
            else
            {
                svcdat->SystemHidden = !(svcdat->VisibleService);
            }
            svcdat->NewPreset = !(AUTO_INSTALL);
            svcdat->EPGEnabled = FALSE;                         
            tmppresetdat.PresetNumber = presetdat.PresetNumber;
            if(pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat) == TRUE)
            {
                presetdat.UniqueNodeId = tmppresetdat.UniqueNodeId;
            }
            pgdb_Update (PRESET_TABLE, (Address)&presetdat);

            svcdat->PresetNumber = presetdat.PresetNumber;
            pgdb_Update (SERVICE_TABLE, (Address)svcdat);

            retval = TRUE;
            TraceDebug(m,"Replacement at Preset %d by <%d,%d>", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);
        }
    }
    else
    {
        /* That preset is free. So just grab it */      
        presetdat.PresetNumber = svcdat->LCN;
        presetdat.Type = HsvOnePart;

        ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
        ASSIGN_DEFAULTCOOKIES(*svcdat);

        svcdat->NewPreset = !AUTO_INSTALL;
        svcdat->UserHidden = FALSE;
        /* Change Made to Implement CR ehv02mgr#16143 */
        if( (div_IsServiceHidden(rins_GetMedium(),ConvertToDVBServiceType(svcdat->ServiceType))) 
                || (div_InstallTestStreams(rins_GetInstallationMode(),rins_GetMedium()) == div_Hide) )
        {
            svcdat->SystemHidden = TRUE;
        }
        else                
        {
            svcdat->SystemHidden = !(svcdat->VisibleService);
        }
        svcdat->EPGEnabled = FALSE; 
        svcdat->UserModifiedName = FALSE;                 
        presetdat.UniqueNodeId  = -1;// Invalid Node id 
        pgdb_Add(PRESET_TABLE, (Address)&presetdat);

        svcdat->PresetNumber = svcdat->LCN;
        pgdb_Update(SERVICE_TABLE, (Address)svcdat);

        TraceDebug(m,"@ %d Addition at Preset %d by <%d,%d>", __LINE__, svcdat->PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);
        TraceDebug(m,"svcdat->SystemHidden %d", svcdat->SystemHidden);

        if(!IS_RADIO_SERVICE(svcdat->ServiceType))
        {
            mFirstInstalledPreset  = ( mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;
        }

        if(svcdat->NewPreset)
        {
            sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
        }
        retval = TRUE;
    }
    return retval;
}

void CHsvEuropeInstallation_mnorsort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    int FromPreset = 0, ToPreset = 0;
    int CurrentPresetIndex = 0;
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        mGetPresetRangeForService(svcdat, &FromPreset, &ToPreset); 

        CurrentPresetIndex = mGetPresetNoForService(svcdat, FromPreset, ToPreset);

        TraceDebug(m,"%s::%d CurrentPresetIndex = %d",__FUNCTION__, __LINE__, CurrentPresetIndex);
        if(CurrentPresetIndex > 0)
        {
            presetdat.PresetNumber = CurrentPresetIndex;
            presetdat.Type = HsvOnePart;

            ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
            ASSIGN_DEFAULTCOOKIES(svcdat);

            svcdat.UserHidden = FALSE;            

            if((div_IsServiceHidden(rins_GetMedium(),ConvertToDVBServiceType(svcdat.ServiceType)))||(div_InstallTestStreams(rins_GetInstallationMode(),rins_GetMedium()) == div_Hide))
            {
                svcdat.SystemHidden = TRUE;
            }
            else
            {
                /* If LCN is zero do not check for Visble flag */

                svcdat.SystemHidden = svcdat.VisibleService ? FALSE : TRUE;
            }
            TraceDebug(m,"%s::svcdat.SystemHidden = %d",__FUNCTION__,svcdat.SystemHidden);

            svcdat.EPGEnabled = FALSE;
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

            TraceDebug(m,"Addition at Preset %d by <%d,%d>", presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.ServiceId);


            mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;;

            CurrentPresetIndex = presetdat.PresetNumber + 1;            
        }
        if(IS_RADIO_SERVICE(svcdat.ServiceType))
        {
            mCurrentRadioIndex = CurrentPresetIndex;
        }
        else
        {
            mCurrentPresetIndex = CurrentPresetIndex;
        }
    }
    else
    {
        TraceDebug(m,"%d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}

int CHsvEuropeInstallation_mnorsort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
{
    int retval = 0;
    HsvPgdatDigServiceData pref_svcdata;

    if(pgdb_GetByIndex(SERVICE_TABLE, pref_index, (Address)(&pref_svcdata)))
    {
        retval = mGetServicePriority(pref_svcdata.ServiceType) - mGetServicePriority(svcdata->ServiceType);

        retval = (retval == 0)? (svcdata->LCN - pref_svcdata.LCN):retval;    

        retval = (retval == 0)? mStrCmp(svcdata->ChannelName, pref_svcdata.ChannelName):retval;

        retval = (retval == 0)? (svcdata->ServiceId - pref_svcdata.ServiceId):retval;
    }
    return retval;
}

int CHsvEuropeInstallation_mnorsort_Priv::mStrCmp( Nat16 * str1, Nat16 * str2 )
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

int CHsvEuropeInstallation_mnorsort_Priv::mGetServicePriority(int serviceType)
{
    int i = 0, retval = 1;
    Bool found = FALSE;

    for(i = 0; i < MAX_SERVICE_TYPES1; i++)
    {
        if(serviceType == mServicePriority[i])
        {
            found = TRUE;
            break;
        }
    }

    /* In case we dont find anything, just fallback to previous case */
    retval = (TRUE == found) ? i: ConvertToDVBServiceType(serviceType);

    return retval;
}

Bool CHsvEuropeInstallation_mnorsort_Priv::CallBackHsvAnalog(Address data)
{
    Bool retval = FALSE;
    HsvChannel* Channel = (HsvChannel*)data;
    if(Channel->Type == HsvAnalog)
    {
        retval = TRUE;
    }
    return retval;
}

Bool CHsvEuropeInstallation_mnorsort_Priv::IsFreqUserInstalled(Nat32 Frequency, Nat16 StreamPriority)
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

int CHsvEuropeInstallation_mnorsort_Priv::ConvertToDVBServiceType(int servicetype)
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
			retval =    HD3DDigitalService;
			break;
        default:
            break;
    }
    return retval;
}

inline int CHsvEuropeInstallation_mnorsort_Priv::mLastLCNBasedPreset(Bool CheckForRadioServices)
{
    int i, retval = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatPresetData presetdata;
    HsvPgdatDigServiceData svcdata;

    TraceDebug(m,"%s %d NoOfRecords: %d", __FUNCTION__, __LINE__, NoOfRecords);
    for(i = 0; i < NoOfRecords; i++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdata))
        {
            ASSIGN_SVC_FROM_PRESET(svcdata, presetdata);
            if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdata))
            {
                if(IS_RADIO_SERVICE(svcdata.ServiceType) == CheckForRadioServices)
                {
                    if(
                            (svcdata.PresetNumber == svcdata.LCN) && 
                            (ISVALID(svcdata.LCN)) && (IS_INTERESTED_LCN_RANGE(svcdata.LCN))
                      ) 
                    {
                        retval = svcdata.PresetNumber;
                        TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
                        break;
                    }
                    else
                    {
                        TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, svcdata.LCN);
                    }
                }
            }
        }
    }

    TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

inline int CHsvEuropeInstallation_mnorsort_Priv::mFirstAvailableGapInPresetList(int FromPreset, int ToPreset)
{
    int i = 0, PreviousPreset = FromPreset, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);

    HsvPgdatPresetData presetdat;

    if(NoOfRecs == 0)
    {
        return FromPreset + 1;
    }

    if(NoOfRecs == 1)
    {
        if(pgdb_GetByIndex( PRESET_TABLE, 0, (Address)&presetdat ) == TRUE)
        {
            Retval = ((presetdat.PresetNumber == 1) && (presetdat.PresetNumber >= FromPreset))? (presetdat.PresetNumber + 1) : (FromPreset + 1);
        }
        else
        {
            /* error condition should not occur */
            Retval = FromPreset + 1;
        }
        return Retval;
    }

    presetdat.PresetNumber = (FromPreset + 1);
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE)
    {
        return FromPreset + 1;
    }

    for(i = (NoOfRecs - 1); i >= 0; i--)
    {
        pgdb_GetByIndex( PRESET_TABLE, i, (Address)&presetdat );

        if(presetdat.PresetNumber <= FromPreset) 
        {
            PreviousPreset = presetdat.PresetNumber;
            if(i == 0)
            {
                Retval = FromPreset + 1;
                break;
            }   
            else
            {
                continue;
            }
        }

        if( (PreviousPreset >= FromPreset) && (presetdat.PresetNumber - PreviousPreset) > 1 )
        {
            /* Found the first gap in needed range */
            Retval = PreviousPreset + 1; 
            break;
        }
        else
        {
            if(i == 0)
            {
                Retval = (presetdat.PresetNumber < ToPreset)?(presetdat.PresetNumber + 1):INVALID_PRESET; 
                break;
            }               
            else
            {
                PreviousPreset = presetdat.PresetNumber;
            }
        }
    }

    //  TraceNotice(m,"%s %d Retval %d PreviousPreset %d presetdat.PresetNumber %d NoOfRecs %d", __FUNCTION__, __LINE__, Retval, PreviousPreset, presetdat.PresetNumber, NoOfRecs);
    Retval = (Retval <= ToPreset)? Retval : INVALID_PRESET;
    return Retval;
}


Bool CHsvEuropeInstallation_mnorsort_Priv::mIsFavouriteNetworkID(HsvPgdatDigServiceData svcdat)
{
    Nat16 NetworkId = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkId);
    HsvPgdatDigTSData   tsdata;
    Bool retval = FALSE;

    tsdata.Frequency = svcdat.Frequency;
    tsdata.StreamPriority = svcdat.StreamPriority;
    if (pgdb_GetByKey(PTC_TABLE, (Address )&tsdata))
    {
        if (tsdata.NetworkId == NetworkId)
        {
            retval = TRUE;      
        }
    }
    else
    {
        TraceDebug(m,"%s %d retval %d tsdata.Frequency %d tsdata.StreamPriority %d", __FUNCTION__, __LINE__, retval, (int )tsdata.Frequency, tsdata.StreamPriority);
    }
    TraceDebug(m,"%s %d retval%d", __FUNCTION__, __LINE__, retval);
    return retval;
}

int CHsvEuropeInstallation_mnorsort_Priv::GetAutomaticPlatformPresetNumber(void)
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


inline Nat16 CHsvEuropeInstallation_mnorsort_Priv::mFindPlaceForAnalogPresets(void)
{

    int retval = INVALID_PRESET, FromPreset = START_PRESET, ToPreset = MAX_NONHONOURED_PRESET;
    Bool  CheckForRadioServices = FALSE;
    HsvPgdatPresetData presetdata;
    HsvChannel preset;

    if(apperr_Ok == iadvpgitr_GetLastChannel(&preset, TRUE))
    {
        presetdata.PresetNumber = preset.Channel.Digit + 1;
        presetdata.Type = HsvOnePart;

        //TraceNotice(m,"%s %d presetdata.PresetNumber %d", __FUNCTION__, __LINE__, presetdata.PresetNumber);
        if(pgdb_GetByKey(PRESET_TABLE, (Address)(&presetdata)))
        {
            //TraceNotice(m,"%s %d presetdata.PresetNumber %d", __FUNCTION__, __LINE__, presetdata.PresetNumber);  
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
        FromPreset  = mLastLCNBasedPreset(CheckForRadioServices);       


        if( (FromPreset == INVALID_PRESET) || (FromPreset >= MAX_NONHONOURED_PRESET))
        {
            FromPreset = 0;
        }

        retval = mFirstAvailableGapInPresetList(FromPreset, ToPreset);
		/* ANEESH: Adding from Latest R3Ext */
		if( (retval == INVALID_PRESET) && (FromPreset > 0) )
		{
			FromPreset = 0;
			retval = mFirstAvailableGapInPresetList(FromPreset, ToPreset);
		}
    }

    TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);  
    return retval;
}

Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AssignPresetsOfOtherCountries(void)
    /* Assigning presets to channels from other countries */
{
    int i = 0, retval = TRUE, pref_dbindex = -1, dbindex = 0, from = 0, to = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool pref_index_found = TRUE;


    for( i = from; retval && (i < to) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;

        for(dbindex = from; dbindex < to; dbindex++)
        {
            if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat))
            {
                if( PRESET_NOT_ALLOCATED(svcdat.PresetNumber) )
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

        if( (pref_dbindex >= from) && (pref_index_found == TRUE))
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }           
    return TRUE;
}

HsvChannel CHsvEuropeInstallation_mnorsort_Priv::inorsort_GetInstalledWeakSignalChannel()
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceNotice(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}


void CHsvEuropeInstallation_mnorsort_Priv::mGetPresetRangeForService(HsvPgdatDigServiceData svcdat, int *FromPreset, int *ToPreset)
{
    HsvPgdatPresetData presetdata;

    REVALIDATE(svcdat.LCN);
    if( IS_SPECIAL_SERVICE(svcdat.LCN) )
    {
        *ToPreset = LAST_PRESET_FOR_SPECIAL_SERVICE;
        if( AUTO_INSTALL )
        {
            *FromPreset  = mLastLCNBasedSpecialPreset();

            *FromPreset  = (*FromPreset  ==  INVALID_PRESET)?START_PRESET_FOR_SPECIAL_SERVICE:(*FromPreset);

            TraceNotice(m,"%s %d *FromPreset %d svcdat.LCN %d", __FUNCTION__, __LINE__, *FromPreset, svcdat.LCN);
        }
        else
        {
            /* For UPDATE & MANUAL INSTALL - just get the Last special preset and add + 1 nothing else required */
            if(pgdb_GetByIndex(PRESET_TABLE, 0, (Address)&presetdata))
            {
                if( IS_SPECIAL_SERVICE(presetdata.PresetNumber) )
                {
                    *FromPreset = presetdata.PresetNumber;
                    TraceNotice(m,"%s %d *FromPreset %d svcdat.LCN %d", __FUNCTION__, __LINE__, *FromPreset, svcdat.LCN);
                }
                else
                {
                    *FromPreset = START_PRESET_FOR_SPECIAL_SERVICE;
                    TraceNotice(m,"%s %d *FromPreset %d svcdat.LCN %d", __FUNCTION__, __LINE__, *FromPreset, svcdat.LCN);
                }
            }
        }
        TraceNotice(m,"%s %d *FromPreset %d svcdat.LCN %d", __FUNCTION__, __LINE__, *FromPreset, svcdat.LCN);
    }
    else
    {
        *ToPreset = MAX_NONHONOURED_PRESET;
        *FromPreset  = mLastLCNBasedPreset(IS_RADIO_SERVICE(svcdat.ServiceType)?TRUE:FALSE);

        if ( (*FromPreset == INVALID_PRESET) || (*FromPreset >= MAX_NONHONOURED_PRESET))
        {
            *FromPreset = (IS_RADIO_SERVICE(svcdat.ServiceType))?RADIO_START_PRESET:0;
        }   
        else if ( (*FromPreset < RADIO_START_PRESET) && (IS_RADIO_SERVICE(svcdat.ServiceType)) )
        {
            *FromPreset = RADIO_START_PRESET;
        }
    }
}

int CHsvEuropeInstallation_mnorsort_Priv::mGetPresetNoForService(HsvPgdatDigServiceData svcdat, int FromPreset, int ToPreset)
{
    int CurrentPresetIndex = 0;

    HsvPgdatPresetData presetdat;

    REVALIDATE(svcdat.LCN);
    if( IS_SPECIAL_SERVICE(svcdat.LCN) )
    {
        /* The new CR does talk about distinguisition of Radio & TV services for Special servivces */
        CurrentPresetIndex = mFirstAvailableGapInPresetList(FromPreset, ToPreset);

        /* Just to find the Gap in the given Preset Range is sufficient nothing more is required, 
           as we have the luxury of the largest range it is impossible to fill in the entire Gap :) <=> (901 - 1999) */
        TraceNotice(m,"%s %d CurrentPresetIndex %d svcdat.LCN %d", __FUNCTION__, __LINE__, CurrentPresetIndex, svcdat.LCN);
    }
    else
    {
        CurrentPresetIndex  = GETCURRENTINDEX(svcdat.ServiceType);

        presetdat.PresetNumber = CurrentPresetIndex; 
        presetdat.Type = HsvOnePart;

        TraceDebug(m,"%s:: %d CurrentPresetIndex = %d FromPreset %d",__FUNCTION__, __LINE__, CurrentPresetIndex, FromPreset);
        if( (CurrentPresetIndex == 0) || pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat)
                || (CurrentPresetIndex < FromPreset) || (CurrentPresetIndex > ToPreset) )
        {
            if( (CurrentPresetIndex = mFirstAvailableGapInPresetList(FromPreset, ToPreset)) == INVALID_PRESET)
            {
                FromPreset = (IS_RADIO_SERVICE(svcdat.ServiceType))?RADIO_START_PRESET:START_PRESET;
                CurrentPresetIndex = mFirstAvailableGapInPresetList(FromPreset, ToPreset);
            }
            TraceDebug(m,"%s:: %d CurrentPresetIndex = %d",__FUNCTION__, __LINE__, CurrentPresetIndex);
        }
    }
    return CurrentPresetIndex;
}

inline int CHsvEuropeInstallation_mnorsort_Priv::mLastLCNBasedSpecialPreset(void)
{
    int i, retval = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatPresetData presetdata;
    HsvPgdatDigServiceData svcdata;

    TraceDebug(m,"%s %d NoOfRecords: %d", __FUNCTION__, __LINE__, NoOfRecords);
    for(i = 0; i < NoOfRecords; i++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdata))
        {
            ASSIGN_SVC_FROM_PRESET(svcdata, presetdata);
            if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdata))
            {
                if( (svcdata.PresetNumber == svcdata.LCN) && IS_SPECIAL_SERVICE(svcdata.LCN) )  
                {
                    retval = svcdata.PresetNumber;
                    TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
                    break;
                }
                else
                {
                    TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, svcdata.LCN);
                }
            }
        }
    }

    TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

inline Bool CHsvEuropeInstallation_mnorsort_Priv::mValidLCNRange(int LCN, int ServiceType)
{
    Bool  retval;
    if(IS_RADIO_SERVICE(ServiceType))
    {
        retval = (LCN >= RADIO_START_PRESET) && (LCN <= div_MaxValidLCNValue);
    }
    else
    {
        retval = (LCN >= div_MinValidLCNValue) && (LCN <= div_MaxValidLCNValue);
    }

    return retval;
}

/*Stub */
Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_mnorsort_Priv::inorsort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_DeleteAllDigitalChannels()
{
	return 0;
}    

Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mnorsort_Priv::inorsort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}

void CHsvEuropeInstallation_mnorsort_Priv::inorsort_RemoveDigitalPresets(void)
{
	return;
}


void CHsvEuropeInstallation_mnorsort_Priv::inorpow_TurnOn  ( void )
{
	return;
}

void CHsvEuropeInstallation_mnorsort_Priv::inorpow_TurnOff ( void )
{
	return;
}
