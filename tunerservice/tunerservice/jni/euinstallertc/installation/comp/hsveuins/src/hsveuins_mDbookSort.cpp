/*
 *  Copyright(C) 2009 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *  %name: hsveuins_mDbookSort.c %
 *  %version: TVG_Fusion_3 %
 *  %date_modified: Mon Apr 06 16:38:28 2010 %
 *  %derived_by: nareshj %
 */



#include "_hsveuins_mDbookSort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mDbookSort")

#include "hsveuins_DbookSort.h"


void CHsvEuropeInstallation_mDbookSort_Priv::idbooksortpow_Init()
{
    mdvbtsortPmp = pmp_PmpCreateEx(pen_PumpEngine, mDvbtSortHandler, FALSE, "hsveuins_mdvbtsort");
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksortpow_TurnOn()
{

}

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksortpow_TurnOff()
{

}


/*****************************************
  provides IHsvHybridPresetSort itasort
 ******************************************/

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_Initialise()
{
    mInstallationVersion  = (Nat8)mGetCurrentInstallationVersion();
    mFirstInstalledPreset = 0xFFFF;
    mConflictDetected     = FALSE;
    mConflictResolutionPass   = FIRST_PASS;

    if(AUTO_INSTALL)
    {
        mCurrentPresetIndex   = INVALID_PRESET;
    }
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_SortAll()
{
    TraceNotice(m,"%s %d mdvbtsortPmp %d", __FUNCTION__, __LINE__, mdvbtsortPmp);
        mConflictResolutionPass = FIRST_PASS;   //i.e., first SD rather normal LCNs
        pmp_PmpSend(mdvbtsortPmp, evStep1, (Nat32)NULL);
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AddAnalogPreset(Address adata)
{
    HsvPgdatAnalogData *panadat = (HsvPgdatAnalogData *)adata;

    if(UPDATE_INSTALL)
    {
        panadat->PresetNumber = mGetAutomaticPlatformPresetNumber();
    }
    else
    {   /* Automatic */
        /* It is expected that the structure comes with a default preset number -> it will be used */
    }
 //   panadat->Favorite = 0;
//    panadat->UserHidden = 0;
    panadat->PreferredStereo = 1;
	panadat->FavoriteNumber	= 0;
	panadat->UserModifiedLogo = 0;
	panadat->UserModifiedName = 0;
	panadat->LogoURL = 0;
    pgdb_Add (ANALOG_TABLE, (Address)adata);
}

Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AutoStoreManualInstallationValues()
{
    Bool retval = FALSE;
    HsvPgdatPresetData newpresetdat;
    HsvPgdatAnalogData    anadat;
    HsvChannel channel;
    int plfpreset = mGetAutomaticPlatformPresetNumber();
    pgdb_Initialise (pgdbconst_Preset,  &newpresetdat);   
    if(pgdb_GetNoRecords(ANALOG_TABLE) < div_MaxAnalogPresets )
    {
        mFindPresetNumberForService(HsvAnalog);

        if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
        {   
            /* Create a User Table entry */
            newpresetdat.PresetNumber = mCurrentPresetIndex;
            newpresetdat.AnalogTablePreset = plfpreset;
            newpresetdat.Type = HsvAnalog;

            ASSIGN_DEFAULTCOOKIES(anadat);
            newpresetdat.UniqueNodeId   = -1;// Invalid Node id 
            pgdb_Add(PRESET_TABLE, (Address)&newpresetdat);

            /* Create an Analog Preset */
            anadat.PresetNumber = plfpreset;
//            anadat.Favorite = FALSE;
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
            channel.Channel.AnalogNo = mCurrentPresetIndex;
            hsvprins_prins_StoreManualInstallationValues(channel);

            /* Fix me. Split this function. Move the unwanted to hsvprins */
            if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&newpresetdat))
            {
                /* Query for frequency value and store back in Preset List */
                anadat.PresetNumber = plfpreset;
                if(TRUE == pgdb_GetByKey(ANALOG_TABLE, (Address)&anadat))
                {
                    newpresetdat.Frequency = anadat.Frequency;
                    pgdb_Update(PRESET_TABLE, (Address) &newpresetdat);
                }
            }

            mCurrentPresetIndex++;
            retval = TRUE;
        }
    }
    return retval;
}

int CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_GetNumberOfAnalogChannelsFound()
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

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AddDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    int dbindex;
    Bool retval = FALSE;

    if(BACKGROUND_INSTALL)
    {
        TraceDebug(m,"%s %d LowPrioLCN %d LCN %d\n", __FUNCTION__, __LINE__, psvcdat->LowPrioLCN, psvcdat->LCN);
        if(pgdb_GetIndex(SERVICE_TABLE, &dbindex, (Address)psvcdat))
        {
            /* 1st HDS LCN */
            if(VALID_LCN_RANGE(psvcdat->LowPrioLCN))
            {
                retval = mDigitalPresetEntryforValidLCN(psvcdat, TRUE);
            }
            if(retval == FALSE)
            {
                /* 2nd SD LCN */
                if(VALID_LCN_RANGE(psvcdat->LCN))
                {
                    retval = mDigitalPresetEntryforValidLCN(psvcdat, FALSE);
                }
            }
            if(retval == FALSE)
            {
                mDigitalPresetEntryforInValidLCN(dbindex);
            }
        }
    }
    else
    {
        TraceNotice(m," @ %d This function call should not be made in installation mode other than manual mode", __LINE__);
        ASSERT(FALSE);
    }
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d\n",__FUNCTION__, __LINE__);

    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)psvcdat))
    {
        presetdat.PresetNumber = psvcdat->PresetNumber;
        presetdat.Type = HsvOnePart;

        if(TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
        { 
            ASSIGN_PRESET_FROM_PSVC(presetdat,psvcdat);     
            pgdb_Update (PRESET_TABLE, (Address)&presetdat);

            mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;

            TraceDebug(m,"Updated Preset %d with new information from <%d,%d,%d,%d>\n", presetdat.PresetNumber,psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->StreamPriority, psvcdat->Frequency); 
        }
        else
        {
            TraceDebug(m,"%s %d\n",__FUNCTION__, __LINE__);
        }
    }          
}

int CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_GetOriginalNetworkId(int CurrentCountry)
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

    TraceDebug(m,"CurrentONID = %d", ONWID);
    return (int )ONWID;
}

Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_IsPresetInstalled(Int32 frequency)
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

HsvChannel CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_GetInstalledWeakSignalChannel(void)
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceNotice(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbookconfN_OnEvent(int eventId)
{
    UNUSED(eventId);
    if(mConflictResolutionPass != LAST_PASS)
    {
        mConflictResolutionPass++;
    }
    else
    {
        /* Reset, so as to perform the regular sorting as all the conflicts are resolved */
        mConflictResolutionPass = NO_PASS;
    }
    mConflictDetected = FALSE;
    /* All the conflicts resolved now, So start assigning the presets for these, 
       the sorting steps of Honoured & Non - Honoured would continue */     
    TraceNotice(m,"%s %d Conflicts resolved", __FUNCTION__, __LINE__);
    pmp_PmpSend(mdvbtsortPmp, ((mConflictResolutionPass == NO_PASS)? evStep0: evStep1), (Nat32)NULL);
}


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvEuropeInstallation_mDbookSort_Priv::mDvbtSortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s: CURRENT STEP = %d\r\n",__FUNCTION__, value);

    if((rins_GetLCNSortingControl() == FALSE) && (value != evStepComplete))
    {
        value = evNoSorting;
    }

    switch(value)
    {
        /* the below step will be executed after resolving SD LCN & HD LCN conflicts individually in separate pass 
           evStep0 is the final step in conflict resolution after this all the resolved conflicts will be sent for sorting :) */
        case evStep0:
            TraceDebug(m,"%s %d Sorting of HD & SD presets \n", __FUNCTION__, __LINE__);
            mSortHDAndSDConflictServices(value);
            break;
        case evStep1:
            /* HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of honoured presets\n", __FUNCTION__, __LINE__);
            mSortHonouredServices(value, (mConflictResolutionPass == LAST_PASS)?TRUE: FALSE);
            break;
        case evStep2:
            /* CONFLICT PRESETS */
            TraceDebug(m,"%s %d Conflict resolution start :mConflictResolutionPass=%d\n",__FUNCTION__, __LINE__,mConflictResolutionPass);
            /* call conflicts module and wait for notification from it, as user UI conflict resolution screen 
               is not TimeOut based */
            idbookconf_ResolveConflicts(mConflictResolutionPass);
            break;
            /* The below step shall be skipped if no conflicts are found */     ;
        case evStep3:
            /* NON HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of non honoured presets\n", __FUNCTION__, __LINE__);
            mSortNonHonouredServices(value);

            break;
        case evStep4:
            /* ANALOG PRESETS */
            TraceDebug(m,"%s %d Sorting of analog presets \n", __FUNCTION__, __LINE__);
            mSortAnalogServices(value);
            break;
        case evStepComplete:
            TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
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

void CHsvEuropeInstallation_mDbookSort_Priv::mNoSorting(int evCurrentSortStep)
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

    mFirstInstalledPreset = mCurrentPresetIndex;

    TraceNotice(m,"%s:Current Preset: %d\r\n",__FUNCTION__, mCurrentPresetIndex);

	for(dbindex = 0; dbindex < noOfDigRecs; ++dbindex)
	{
        HsvPgdatPresetData presetdat;

		if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
		{
			TraceNotice(m,"%s:Found Service-> Preset:%d  Serv:%d\r\n",__FUNCTION__, svcdat.PresetNumber, svcdat.ServiceId);

			if(svcdat.PresetNumber == INVALID_PRESET)
			{
				TraceNotice(m,"%s:Add Preset-> Serv:%d\r\n",__FUNCTION__, svcdat.ServiceId);

				++mCurrentPresetIndex;
				presetdat.PresetNumber = mCurrentPresetIndex;
				presetdat.Type = HsvOnePart;

				ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
				ASSIGN_DEFAULTCOOKIES(svcdat);

				svcdat.PresetNumber = presetdat.PresetNumber;
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
                    (idbooksort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                ++mCurrentPresetIndex;
                presetdat.PresetNumber = mCurrentPresetIndex;
                presetdat.AnalogTablePreset = anadat.PresetNumber;
                presetdat.Type = HsvAnalog;
                presetdat.Frequency = anadat.Frequency;
                presetdat.UniqueNodeId  = -1;// Invalid Node id

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

    if(mCurrentPresetIndex > mFirstInstalledPreset)
    	mFirstInstalledPreset++;

    pmp_PmpSend(mdvbtsortPmp, evStepComplete, (Nat32)NULL);
}

void CHsvEuropeInstallation_mDbookSort_Priv::mSortHonouredServices(int evCurrentSortStep, Bool CheckForHDLCN)
{
    int LCN, dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    Bool CanBeReplaced = (div_UpdateLCN(rins_GetMedium()))?TRUE:FALSE;

    TraceDebug(m,"%s %d Sorting of Honoured services CheckForHDLCN = %d  noOfRecs = %d \n", __FUNCTION__, __LINE__,CheckForHDLCN,noOfRecs);

    for( dbindex = 0; dbindex < noOfRecs; dbindex++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
        {
            LCN = (CheckForHDLCN)? svcdat.LowPrioLCN : svcdat.LCN;
                
            
			if(MANUAL_INSTALL && !MANUAL_INSTALL_PRESET(svcdat.NewPreset,svcdat.PresetNumber))
			{
				CanBeReplaced = FALSE;
			}
			
            if((CanBeReplaced ||(MANUAL_INSTALL && MANUAL_INSTALL_PRESET(svcdat.NewPreset,svcdat.PresetNumber)))
                    && (VALID_LCN_RANGE(svcdat.LowPrioLCN)||VALID_LCN_RANGE(svcdat.LCN))&&
                    ((svcdat.LowPrioLCN != svcdat.PresetNumber)&&(svcdat.LCN != svcdat.PresetNumber)))
            {
                //delete preset  ,LCN has changed for this service 
                presetdat.PresetNumber = svcdat.PresetNumber;
                if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
                {
                    pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
                }

                svcdat.PresetNumber = INVALID_PRESET;
                pgdb_Update(SERVICE_TABLE, (Address)&svcdat);                            
            }

            TraceDebug(m,"%s %d dbindex %d LCN %d\n", __FUNCTION__, __LINE__, dbindex, LCN);

            if( (PRESET_NOT_ALLOCATED(svcdat)||(CheckForHDLCN)) && VALID_LCN_RANGE(LCN) )
            {
                TraceDebug(m,"%s %d dbindex %d LCN %d\n", __FUNCTION__, __LINE__, dbindex, LCN);
                mDigitalPresetEntryforValidLCN(&svcdat, CheckForHDLCN);
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

    TraceDebug(m,"Pmp send done with event = %d\r\n", (evCurrentSortStep + 1));

    if(mConflictResolutionPass != NO_PASS)
    {   
        if(mConflictDetected == TRUE)
        {   
            TraceDebug(m,"Pmp send done with event = %d\r\n", evCurrentSortStep + 1);
            pmp_PmpSend(mdvbtsortPmp, evCurrentSortStep + 1, (Nat32)NULL);
        }    
        else 
        {
            /*if no conflict in first pass /second pass send the notification , to increment to the next pass*/
            idbookconfN_OnEvent(TRUE);
        }
    }
    else
    {

        TraceDebug(m,"Pmp send done with event = %d\r\n", evCurrentSortStep + 1);
        pmp_PmpSend(mdvbtsortPmp, evCurrentSortStep + 2, (Nat32)NULL);
    }

}

Bool CHsvEuropeInstallation_mDbookSort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN)
{
    Bool retval = FALSE,CanBeReplaced = (div_UpdateLCN(rins_GetMedium()))?TRUE:FALSE;
    int LCN = (CheckForHDLCN)? svcdat->LowPrioLCN : svcdat->LCN;
    Bool Proceed = TRUE;
    if( mIsPresetOccupied(LCN) == FALSE )
    {
        /* LCN position free, So just grab the entry in preset table for this service */
        if(mCanServiceBeHonoured(svcdat, CheckForHDLCN) == TRUE)
        {
            if(CheckForHDLCN)
            {
                HsvPgdatPresetData presetdat;
                presetdat.PresetNumber = svcdat->LCN;
                if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
                {
                    if((svcdat->OriginalNetworkId == presetdat.OriginalNetworkId)&&(svcdat->ServiceId == presetdat.ServiceId)&&
                            (svcdat->Frequency == presetdat.Frequency))
                    {
                        pgdb_Delete(PRESET_TABLE,(Address)&presetdat);

                        INVALIDATE(svcdat->LCN);                            
                        pgdb_Update(SERVICE_TABLE, (Address)svcdat);                            
                    }
                }
            }

            if(MANUAL_INSTALL && MANUAL_INSTALL_PRESET(svcdat->NewPreset,svcdat->PresetNumber))// if this service is from manual installtion
            {
                Proceed = FALSE;
                if((CheckForHDLCN == FALSE) && VALID_LCN_RANGE(svcdat->LowPrioLCN))
                {
                    Proceed = FALSE;//Valid HD lcn is present ,so ignore normal LCN 
                    INVALIDATE(svcdat->LCN);                            
                    pgdb_Update(SERVICE_TABLE, (Address)svcdat);                            
                }
                else
                {
                    Proceed = TRUE;
                }

            }
            if(Proceed)
            {
                mAddOrUpdateEntryToPresetTable(svcdat, LCN, ADD_ENTRY);
            }
            retval = TRUE;
        }
    }
    else
    {   
        if(CanBeReplaced||MANUAL_INSTALL)  
        {                
            if((MANUAL_INSTALL) && MANUAL_INSTALL_PRESET(svcdat->NewPreset,svcdat->PresetNumber)) // if this service is from manual installtion
            {   
                Proceed = FALSE;

                if((CheckForHDLCN == FALSE) && VALID_LCN_RANGE(svcdat->LowPrioLCN))
                {
                    Proceed = FALSE;//Valid HD lcn is present ,so ignore normal LCN      
                    INVALIDATE(svcdat->LCN);                            
                    pgdb_Update(SERVICE_TABLE, (Address)svcdat);                            
                }
                else
                {
                    Proceed = TRUE;
                }
            }

            if(Proceed)
            {                
                /* It can be the same service in next installation pass, so don't treat it as conflict */
                if( (svcdat->PresetNumber != LCN) && (!BACKGROUND_INSTALL) )
                {
                    /* Same LCNs encountered check if this can be treated as Conflicts based installation mode */
                    TraceNotice(m,"Same LCNs encountered, check if this can be treated as Conflicts based on rules considering installation mode. LCN %d svcdat->PresetNumber %d", svcdat->LCN, svcdat->PresetNumber);

                    //If the Preset occupied is from previous pass and it is Update installaiton then invalidate the new Preset.
                    HsvPgdatPresetData presetdat;
                    presetdat.PresetNumber = LCN;
                    if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
                    {
						if(mServiceIsOfPreviousPass(presetdat) && !MANUAL_INSTALL_PRESET(svcdat->NewPreset,svcdat->PresetNumber))
						{
                            if(CheckForHDLCN)
                            {
                                INVALIDATE(svcdat->LowPrioLCN);
                            }
                            else
                            {
                                INVALIDATE(svcdat->LCN);
                            }
                            TraceNotice(m,"Updation to pgdb table @ %s %d", __FUNCTION__, __LINE__);
                            pgdb_Update(SERVICE_TABLE, (Address)svcdat);
                            retval = TRUE;
                        }
                        else
                        {
                            retval = mConflictDetection(svcdat, CheckForHDLCN);
                        }
                    }


                }
            }            

        }        
        else
        {
            //in update install , user reorder is true ,so invalidate lcn 
            if(CheckForHDLCN)
            {
                INVALIDATE(svcdat->LowPrioLCN);
            }
            else
            {
                INVALIDATE(svcdat->LCN);
            }  
            pgdb_Update(SERVICE_TABLE, (Address)svcdat);

        }
    }



    return retval;
}

void CHsvEuropeInstallation_mDbookSort_Priv::mSortNonHonouredServices(int evCurrentSortStep)
{
    int i = 0, pref_dbindex = -1, dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool pref_index_found = TRUE;

    for( i = 0; (i < noOfRecs) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = 0; dbindex < noOfRecs; dbindex++)
        {
            if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
            {
                /* 2nd & 3rd check is required because we should touch LCN conflict records which were not allocated in previous pass
                   and are waiting for conflict resolution within this step (ex: Invisible service LCN records during auto install) */
                if( PRESET_NOT_ALLOCATED(svcdat) && (!VALID_LCN_RANGE(svcdat.LCN))
                        && (!VALID_LCN_RANGE(svcdat.LowPrioLCN)) )
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

        if(pref_index_found == TRUE)
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);

    /* This probably is confusing looks like but "Conflict Resolution" step should be skipped if there is no conflicts found 
       And that is what is done below :) */



}

void CHsvEuropeInstallation_mDbookSort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    HsvPgdatDigServiceData svcdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        mFindPresetNumberForService(HsvOnePart);

        if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
        {
            mAddOrUpdateEntryToPresetTable(&svcdat, mCurrentPresetIndex, ADD_ENTRY);
        }
        else
        {
            TraceNotice(m,"%s %d Could not allocate the preset entry to the service <%d %d>", __FUNCTION__, __LINE__, svcdat.OriginalNetworkId, svcdat.ServiceId);
            ASSERT(!"Could not allocate the preset entry to the service");
        }
    }
    else
    {
        TraceNotice(m,"@ %d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}

/* Added from query interface */
int CHsvEuropeInstallation_mDbookSort_Priv::mGetCurrentInstallationVersion(void)
{
    int retval = 0;
    int maxrecords = pgdb_GetNoRecords(PTC_TABLE);

    if(maxrecords > 0)
    {
        HsvPgdatDigTSData tsdat;
        if(TRUE == pgdb_GetByIndex(PTC_TABLE, 0, (Address)&tsdat))
        {
            retval = tsdat.PtcListVersion;
        }
    }
    return retval;
}

int CHsvEuropeInstallation_mDbookSort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
{
    int retval = 0;
    HsvPgdatDigServiceData pref_svcdata;

    if(pgdb_GetByIndex(SERVICE_TABLE, pref_index, (Address)&pref_svcdata))
    {
        retval = mGetServicePriority(pref_svcdata.ServiceType) - mGetServicePriority(svcdata->ServiceType);

        retval = (retval == 0)? (svcdata->LCN - pref_svcdata.LCN):retval;    

        retval = (retval == 0)? mStrCmp(svcdata->ChannelName, pref_svcdata.ChannelName):retval;

        retval = (retval == 0)? (svcdata->ServiceId - pref_svcdata.ServiceId):retval;
    }
    return retval;
}

int CHsvEuropeInstallation_mDbookSort_Priv::mStrCmp( Nat16 * str1, Nat16 * str2 )
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

int CHsvEuropeInstallation_mDbookSort_Priv::mGetServicePriority(int serviceType)
{
    int i = 0, retval = 1;
    Bool found = FALSE;

    for(i = 0; i < MAX_SERVICE_TYPES; i++)
    {
        if(serviceType == mServicePriority[i])
        {
            found = TRUE;
            break;
        }
    }

    /* In case we dont find anything, just fallback to previous case */
    retval = (TRUE == found) ? i:0;

    return retval;
}

void CHsvEuropeInstallation_mDbookSort_Priv::mSortAnalogServices(int evCurrentSortStep)
{
    HsvPgdatAnalogData anadat;
    HsvPgdatPresetData presetdat;
    int i, noOfRecs = pgdb_GetNoRecords(ANALOG_TABLE);

    TraceDebug(m,"%s %d noOfRecs: %d\n", __FUNCTION__, __LINE__, noOfRecs);
    for(i = (noOfRecs - 1); i >= 0; i--)
    {   
        if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
        {
            /* Only for installed analog presets, 2nd check is to check if this a new service are previously installed one */
            if( (TRUE == anadat.Tuned) && 
                    (idbooksort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                /* Allocate the current number */
                mFindPresetNumberForService(HsvAnalog);

                presetdat.PresetNumber = mCurrentPresetIndex;
                presetdat.AnalogTablePreset = anadat.PresetNumber;

                if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
                {
                    presetdat.Type = HsvAnalog;
                    presetdat.Frequency = anadat.Frequency;

                    ASSIGN_DEFAULTCOOKIES(anadat);
                    presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                    pgdb_Update(ANALOG_TABLE,(Address) &anadat);

                    mCurrentPresetIndex++;
                }
                else
                {
                    TraceDebug(m,"%d Cannot Add Analog Preset as there is no place in the PRESET LIST\n", __LINE__);
                    ASSERT(!"Preset table is FULL");
                    break;
                }
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

    TraceDebug(m,"Pmp send done with event = %d\r\n", evCurrentSortStep + 1);
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

Bool CHsvEuropeInstallation_mDbookSort_Priv::mIsHdSdFromUserSelectedRegion(HsvPgdatDigServiceData *HdService, HsvPgdatDigServiceData *SdService)
{
	Bool RetVal = TRUE;
    int PrimaryRegion   = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributePrimaryRegion);
    int SecondaryRegion = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributeSecondaryRegion);
    int TertiaryRegion  = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributeTertiaryRegion);
	
	if (VALID_PRIMARY_REGION(PrimaryRegion) && VALID_PRIMARY_REGION(HdService->PrimaryRegion))
	{
		if ((HdService->PrimaryRegion != PrimaryRegion) /*|| (SdService->PrimaryRegion != PrimaryRegion)*/)
		{
			TraceNotice (m, "Primary Regions different  ");
			RetVal = FALSE;
		}
		else if (VALID_SECONDARY_REGION(SecondaryRegion) && (VALID_SECONDARY_REGION(HdService->SecondaryRegion)))
		{
			if ((HdService->SecondaryRegion != SecondaryRegion) /* || (SdService->SecondaryRegion != SecondaryRegion)*/)
			{
				TraceNotice (m, "Secondary Regions different  ");
				RetVal = FALSE;
			}
			else if (VALID_TERTIARY_REGION(TertiaryRegion) && VALID_TERTIARY_REGION(HdService->TertiaryRegion))
			{
				if ((HdService->TertiaryRegion != TertiaryRegion)/* || (SdService->TertiaryRegion != TertiaryRegion)*/)
				{
					TraceNotice (m, "Tertiary Regions different  ");
					RetVal = FALSE;
				}
			}
		}
	}
	return RetVal;
}
void CHsvEuropeInstallation_mDbookSort_Priv::mSortHDAndSDConflictServices(int evCurrentSortStep)
{
    int i, j, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE), count;
    HsvPgdatDigServiceData currsvcdat, svcdat;
    Bool Proceed = TRUE;
    HsvPgdatPresetData presetdat, tmppresetdat;
    HsvPgdatDigTSData  tmptsdat;
    Nat8 mAddUpdate = ADD_ENTRY;
	int 	LcnToBeSwapped = 0;

    /* Goal of this function is to convert the HD LCNs are priority LCNs
       to the LCN attribute of service table as since it would be the value which would be honoured */
    for(i = 0; i < noOfRecs; i++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&currsvcdat))
        {
            if(VALID_LCN_RANGE(currsvcdat.LowPrioLCN) )
            {
                presetdat.PresetNumber = currsvcdat.LowPrioLCN;
                if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE)
                {
                    //This HD preset position is free
                    presetdat.PresetNumber = currsvcdat.LCN;   
                    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
                    {
                        if((currsvcdat.OriginalNetworkId == presetdat.OriginalNetworkId)&&(currsvcdat.ServiceId == presetdat.ServiceId)&&
                                (currsvcdat.Frequency == presetdat.Frequency))
                        {
                            pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
                        }
                    }
					
					/* Check if any service have an LCN matching to this. If yes and its preset not allocated, then it will be the case
						in which FIRST_PASS conflict resuoution winner has conflict with HDLCN.
						Need to swap the LCNs in DigSrvTable. Do not add to preset, next SortHonored step will take care of this */
					if (VALID_LCN_RANGE(currsvcdat.LCN))
					{
						for (count = 0; count < noOfRecs; count++)
						{
							if (pgdb_GetByIndex(SERVICE_TABLE, count, &svcdat))
							{
								/* Conflicting service should not have HDLCN. Should have same Normal LCN and Preset not allocated. (this can happen in first pass resolution case) */
								if ((currsvcdat.LowPrioLCN == svcdat.LCN) && (PRESET_NOT_ALLOCATED(svcdat)) && (!VALID_LCN_RANGE(svcdat.LowPrioLCN)) )
								{
									svcdat.LCN = currsvcdat.LCN;
									TraceNotice (m, "Swapping LCN of ServiceID %d to Value %d (NormalLCN) ", svcdat.ServiceId, svcdat.LCN);
									pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
									/* There can be only 1 winner for LCN confictt in FIRST_PASS. So its not really needed to check further */
									break;
								}
							}
						}
					}

                    mAddOrUpdateEntryToPresetTable(&currsvcdat,currsvcdat.LowPrioLCN,ADD_ENTRY);
                }
                else
                {
                    Proceed = TRUE;
                    presetdat.PresetNumber = currsvcdat.LowPrioLCN;
                    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
                    {
                        if((currsvcdat.OriginalNetworkId == presetdat.OriginalNetworkId)&&(currsvcdat.ServiceId == presetdat.ServiceId)&&
                                (currsvcdat.Frequency == presetdat.Frequency))
                        {
                            // this LCN has already got HD preset
                            Proceed = FALSE;
                        }

                    }

                    if(Proceed == TRUE)
                    {   

                        for(j = 0; j < noOfRecs; j++)
                        {
                            if(pgdb_GetByIndex(SERVICE_TABLE, j, (Address)&svcdat) == TRUE)
                            {
                                /* At HDSLCN number some other preset is placed. So swap them */
                                if((i != j)&&(currsvcdat.LowPrioLCN == svcdat.PresetNumber) && mIsHdSdFromUserSelectedRegion(&currsvcdat, &svcdat))
                                {
                                    /* swap the SD LCN of HD service with LCN of SD service */
                                    presetdat.PresetNumber = currsvcdat.LCN;

                                    if(VALID_LCN_RANGE(currsvcdat.LCN)) 
                                    {
                                        if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE)
                                        {
                                            /* old service LCN will take normal LCN value of HD service */
                                            svcdat.LCN = currsvcdat.LCN;
                                            svcdat.PresetNumber = svcdat.LCN;
                                            presetdat.PresetNumber = svcdat.PresetNumber;
                                            mAddOrUpdateEntryToPresetTable(&svcdat,svcdat.PresetNumber,ADD_ENTRY);
                                        }
                                        else
                                        {
                                            if(MANUAL_INSTALL)
                                            {
                                                tmppresetdat.PresetNumber = currsvcdat.LCN;
                                                if( pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat) == TRUE)
                                                {
                                                    tmptsdat.Frequency          =   tmppresetdat.Frequency;
                                                    tmptsdat.StreamPriority =   tmppresetdat.StreamPriority;
                                                    if(pgdb_GetByKey(PTC_TABLE, (Address)&tmptsdat) == TRUE)
                                                    {
                                                        if(tmptsdat.UserInstalled)
                                                        {
                                                            Proceed = FALSE;
                                                        }
                                                    }
                                                }
                                            }

                                            if( (Proceed) && ((currsvcdat.OriginalNetworkId == presetdat.OriginalNetworkId)&&(currsvcdat.ServiceId == presetdat.ServiceId)&&
                                                        (currsvcdat.Frequency == presetdat.Frequency)) )
                                            {
                                                svcdat.LCN = currsvcdat.LCN;
                                                svcdat.PresetNumber = svcdat.LCN;                                            
                                                presetdat.PresetNumber = svcdat.PresetNumber;                                            
                                                mAddOrUpdateEntryToPresetTable(&svcdat,svcdat.PresetNumber,UPDATE_ENTRY);                                                
                                            }
                                            else
                                            {
                                                INVALIDATE(svcdat.LCN);
                                                svcdat.PresetNumber = INVALID_PRESET;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        /* HD service doesnt have a normal LCN value or someone has already occupied
                                           So the SD service LCN gets invalidated and is non honoured */
                                        INVALIDATE(svcdat.LCN);
                                        svcdat.PresetNumber = INVALID_PRESET;
                                    }

                                    Proceed = TRUE;
                                    if(MANUAL_INSTALL)
                                    {
                                        tmppresetdat.PresetNumber = currsvcdat.LowPrioLCN;
                                        if( pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat) == TRUE)
                                        {
                                            tmptsdat.Frequency          =   tmppresetdat.Frequency;
                                            tmptsdat.StreamPriority     =   tmppresetdat.StreamPriority;
                                            if(pgdb_GetByKey(PTC_TABLE, (Address)&tmptsdat) == TRUE)
                                            {
                                                if(tmptsdat.UserInstalled)
                                                {
                                                    Proceed = FALSE;
                                                }
                                            }
                                        }
                                    }

                                    if(Proceed)
                                    {
                                        pgdb_Update(SERVICE_TABLE, (Address)&svcdat);

                                        /* Here the HD service assignment starts.*/
                                        //currsvcdat.LCN = currsvcdat.LowPrioLCN;
                                        currsvcdat.PresetNumber = currsvcdat.LowPrioLCN;
                                        pgdb_Update(SERVICE_TABLE, (Address)&currsvcdat);

                                        presetdat.PresetNumber = currsvcdat.PresetNumber;
                                        if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
                                        {
                                            mAddUpdate = UPDATE_ENTRY;
                                        }
                                        else
                                        {
                                            mAddUpdate = ADD_ENTRY;
                                        }

                                        mAddOrUpdateEntryToPresetTable(&currsvcdat,currsvcdat.PresetNumber,mAddUpdate);
                                        break;
                                    }
                                }
                            }
                        }
                    }
					else
					{
						/* Isnt this needed here also?? There can be cases in which FIRST_PASS services have conflict with HDLCN	
							HDLCN as such does not have conflict and hence given the position. Now the Winner of FIRST_PASS should
							get the Normal LCN of the HD Service.  */
						LcnToBeSwapped = currsvcdat.LCN;
						if (!VALID_LCN_RANGE(currsvcdat.LCN)) /* Very less chance that this will be TRUE, as most of the time we will invalidate normal LCN when HDLCN gets PresetNumber */
						{
							REVALIDATE(LcnToBeSwapped);	/* Temporarily revalidating. This is needed because if HDLCN gets assigned to PresetNumber normal LCN is invalidated */
							TraceNotice (m, "Revalidation needed. After that LCN %d ", LcnToBeSwapped);
						}
						
						if (VALID_LCN_RANGE(LcnToBeSwapped))
						{
							for (count = 0; count < noOfRecs; count++)
							{
								if (pgdb_GetByIndex(SERVICE_TABLE, count, &svcdat))
								{
									/* Handling case in which service which have 
										1) Won in the Conflict resolution in FIRST. But has conflict with HDLCN of current service
										2) Preset number is not yet allocated for the Normal LCN
										3) Doesnt have a valid HDLCN, means this one never came for HD LCN conflict */
									if ((currsvcdat.LowPrioLCN == svcdat.LCN) && (PRESET_NOT_ALLOCATED(svcdat)) && (!VALID_LCN_RANGE(svcdat.LowPrioLCN)) )
									{
										svcdat.LCN = LcnToBeSwapped;
										TraceNotice (m, "Swapping LCN of ServiceID %d to Value %d (NormalLCN) Revalidated %d ", svcdat.ServiceId, svcdat.LCN);
										pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
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
	#if 0
	for(i = 0; i < noOfRecs; i++)
	{
		if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&currsvcdat))
		{
			if((PRESET_NOT_ALLOCATED(currsvcdat)) &&  VALID_LCN_RANGE(currsvcdat.LCN) && ( currsvcdat.ServiceListVersion == INSTALL_VERSION ))
			{
				/* Invalidating the LCN of services which got low priority in Conflict resolution.
				   Here service has a valid LCN (won in the FIRST_PASS) but no valid HDLCN. So in the LAST_PASS
				   if there is conflict with HDLCN this is given low priority. This service never gets assigned. */
				INVALIDATE(currsvcdat.LCN);
				pgdb_Update(SERVICE_TABLE, (Address)&currsvcdat);
				TraceNotice(m, "Invalidating the LCN of ServiceID %d ", currsvcdat.ServiceId);
			}
		}
	}
	#endif
    TraceDebug(m,"Pmp send done with event = %d\r\n", evCurrentSortStep + 1);
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}


void CHsvEuropeInstallation_mDbookSort_Priv::mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate)
{
    HsvPgdatPresetData presetdat, tmppresetdat;

    presetdat.PresetNumber = PresetNo;
    presetdat.Type = HsvOnePart;

    ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
    ASSIGN_DEFAULTCOOKIES(*svcdat);

    /*if( (div_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(svcdat->ServiceType))) 
      || (div_InstallTestStreams(rins_GetInstallationMode(), rins_GetMedium()) == div_Hide) )
      {
      svcdat->SystemHidden = TRUE;
      }
      else                
      {
      svcdat->SystemHidden = !(svcdat->VisibleService);
      }*/


   
    TraceDebug(m,"@ %d %s at Preset %d by <%d,%d>\n", __LINE__, (AddOrUpdate == ADD_ENTRY)?"Addition":"Updation", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);
    if(AddOrUpdate == ADD_ENTRY)
    {
		presetdat.UniqueNodeId	= -1;// Invalid Node id 
        pgdb_Add(PRESET_TABLE, (Address)&presetdat);
    }
    else
    {
        tmppresetdat.PresetNumber = presetdat.PresetNumber;
        if(pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat) == TRUE)
        {
            presetdat.UniqueNodeId = tmppresetdat.UniqueNodeId;
        }
        pgdb_Update(PRESET_TABLE, (Address)&presetdat);
    }

    svcdat->PresetNumber = presetdat.PresetNumber;
    pgdb_Update(SERVICE_TABLE, (Address)svcdat);

    mFirstInstalledPreset  = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;  

    if(svcdat->NewPreset)
    {
        sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
    }
}

inline Bool CHsvEuropeInstallation_mDbookSort_Priv::mIsPresetOccupied(int PresetNumber)
{
    Bool retval = FALSE;
    HsvPgdatPresetData presetdat;

    presetdat.PresetNumber = PresetNumber;
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
    {
        retval = TRUE;
    }

    return retval;
}

inline void CHsvEuropeInstallation_mDbookSort_Priv::mFindPresetNumberForService(int AnalogOrDigital)
{
    int FromPreset = (AnalogOrDigital == HsvOnePart)? NON_HONOURED_START_PRESET : ANALOG_START_PRESET, ToPreset = div_MaxValidLCNValue; 
    int NoOfRecs = pgdb_GetNoRecords((AnalogOrDigital == HsvOnePart)? PRESET_TABLE: SERVICE_TABLE);

    if( (mCurrentPresetIndex == INVALID_PRESET) || mIsPresetOccupied(mCurrentPresetIndex) 
            || (VALID_PRESET_RANGE(mCurrentPresetIndex) == FALSE))
    {
        mCurrentPresetIndex = (NoOfRecs == 0)? FromPreset : mFindFirstGapInRange(FromPreset, ToPreset);
        if(mCurrentPresetIndex == INVALID_PRESET)
        {
            FromPreset = DEFAULT_START_PRESET;
            mCurrentPresetIndex = mFindFirstGapInRange(FromPreset, ToPreset);
        }
    }
    TraceDebug(m,"%s %d mCurrentPresetIndex %d\n", __FUNCTION__, __LINE__, mCurrentPresetIndex);
}

int CHsvEuropeInstallation_mDbookSort_Priv::mGetAutomaticPlatformPresetNumber(void)
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

Bool CHsvEuropeInstallation_mDbookSort_Priv::mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat)
{
    Bool retval = FALSE;
    HsvPgdatDigServiceData svcdat;

    ASSIGN_SVC_FROM_PRESET(svcdat,presetdat);
    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)&svcdat))
    {
        if( svcdat.ServiceListVersion != INSTALL_VERSION )
        {
            /* This means the service is installed in previous installations */
            retval = TRUE;
        }
    }

    TraceNotice(m,"%s %d presetnum %d retval %d", __FUNCTION__, __LINE__, presetdat.PresetNumber, retval);
    return retval;
}

Bool CHsvEuropeInstallation_mDbookSort_Priv::mCanServiceBeHonoured(HsvPgdatDigServiceData *currsvcdat, Bool CheckForHDLCN)
{
    Bool retval = TRUE, VisibleFlag;
    int currdbindex = -1, LCN1, LCN2;

    if(IS_VISIBLE_SERVICE(*currsvcdat) == FALSE)
    {
        int dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
        HsvPgdatDigServiceData svcdat;

        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);

        /* This is a invisible services, honour it only if there is no conflicts for its LCN */
            for( dbindex = 0; dbindex < noOfRecs; dbindex++)
            {
                if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
            {
                if(pgdb_GetIndex(SERVICE_TABLE, &currdbindex, (Address)currsvcdat))
                {
                    if(CheckForHDLCN)
                    {
                        LCN1 = currsvcdat->LowPrioLCN;
                        LCN2 = svcdat.LowPrioLCN;
                        VisibleFlag = svcdat.LowPrioVisibleService;
                    }
                    else
                    {
                        LCN1 = currsvcdat->LCN;
                        LCN2 = svcdat.LCN;
                        VisibleFlag = svcdat.VisibleService;
                    }

                    if( (currdbindex != dbindex) && (LCN1 == LCN2) 
                            && (VisibleFlag == TRUE) )
                    {
                        retval = FALSE;
                        TraceNotice(m," Invisible service in conflict race for LCN %d", currsvcdat->LCN);
                        break;
                    }
                }
            }
        }
    }

    if(retval == FALSE)
    {
        /* Invisible services which has LCN conflicts should not be used for "User Conflict Resolution"
           So, Invalidate it and handle in next step itself => sorting of Non-honoured services */
        if(CheckForHDLCN)
        {
            INVALIDATE(currsvcdat->LowPrioLCN);
        }
        else
        {
            INVALIDATE(currsvcdat->LCN);
        }
        TraceNotice(m,"Updation to pgdb table @ %s %d", __FUNCTION__, __LINE__);
        pgdb_Update(SERVICE_TABLE, (Address)currsvcdat);
    }
    return retval;
}

Bool CHsvEuropeInstallation_mDbookSort_Priv::mConflictDetection(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN)
{
    int LCN;
    Bool retval = FALSE, VisibleFlag, IsItConflict = TRUE, SvcHonoured;
    //HsvPgdatDigTSData  tsdat;
    HsvPgdatPresetData presetdat;   
    /* We know preset is occupied, Now check for few rules to detect it as conflict or not depending on installation mode */
    if(AUTO_INSTALL)
    {
        if(mCanServiceBeHonoured(svcdat, CheckForHDLCN) == TRUE)
        {   
            TraceNotice(m,"Conflicts detected for LCN %d", svcdat->LCN);
            mConflictDetected = TRUE;
        }
    }
    else
    {
        LCN = (CheckForHDLCN)? svcdat->LowPrioLCN : svcdat->LCN;
        SvcHonoured = mCanServiceBeHonoured(svcdat, CheckForHDLCN);
        IsItConflict = SvcHonoured?IsItConflict: FALSE;



        if((SvcHonoured == TRUE) || (MANUAL_INSTALL && MANUAL_INSTALL_PRESET(svcdat->NewPreset, svcdat->PresetNumber))) 
        {
            presetdat.PresetNumber = LCN;
            if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
            {
                HsvPgdatDigServiceData oldsvcdat;
                Bool Proceed = TRUE;

                if(presetdat.Type == HsvAnalog)
                {
                    Proceed = FALSE;
                    if(CheckForHDLCN)
                    {
                        INVALIDATE(svcdat->LowPrioLCN);
                    }
                    else
                    {
                        INVALIDATE(svcdat->LCN);
                    }
                    pgdb_Update(SERVICE_TABLE, (Address)svcdat);
                    retval = TRUE;
                    IsItConflict = FALSE;
                }

                if(Proceed)
                {                    
                    ASSIGN_SVC_FROM_PRESET(oldsvcdat,presetdat);
                    if(pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat))
                    {
                        VisibleFlag = (CheckForHDLCN)? oldsvcdat.LowPrioVisibleService : oldsvcdat.VisibleService;
                        if( (VisibleFlag == FALSE) || MANUAL_INSTALL )
                        {
                            if(CheckForHDLCN)
                            {
                                INVALIDATE(oldsvcdat.LowPrioLCN);

                                /*if HD LCN conflict with normal LCN then invalidate noraml LCN */
                                if((MANUAL_INSTALL) && (oldsvcdat.LCN == LCN))
                                {
                                    INVALIDATE(oldsvcdat.LCN);
                                }
                            }
                            else
                            {
								/* reverse of above conditions */
								INVALIDATE(oldsvcdat.LCN);
								if(MANUAL_INSTALL && (oldsvcdat.LowPrioLCN == LCN) )
								{
									INVALIDATE(oldsvcdat.LowPrioLCN);
								}
							}

							/* This means old service is installed in manual installed and so, should not be overwritten again */
							Bool Proceed = TRUE;
							
							if(MANUAL_INSTALL)
							{
								Proceed = FALSE;
								if(svcdat->NewPreset == TRUE)
								{
									Proceed = TRUE;
								}
							}
							
							if(Proceed)
							{
								oldsvcdat.PresetNumber = INVALID_PRESET;
								pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);
                            
								mAddOrUpdateEntryToPresetTable(svcdat, LCN, UPDATE_ENTRY);
                            }
                            /* No conflicts detected as the old service is invisible one, its LCN is dis-honoured */
                            IsItConflict = FALSE;
                            retval = TRUE;
                        }
                    }
                }
            }
        }

        mConflictDetected = (mConflictDetected == FALSE)?IsItConflict:mConflictDetected;
        if(IsItConflict == TRUE)
        {
            TraceNotice(m,"Conflicts detected for LCN %d", LCN);
        }
    }
    return retval;
}

int CHsvEuropeInstallation_mDbookSort_Priv::mFindFirstGapInRange(int FromPreset, int ToPreset)
{
    int i = 0, PreviousPreset = MAX_PRESET_NUM, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);
    int passval = 0;

    HsvPgdatPresetData presetdat;

    /* Below is the heart of the sorting module, beware of PRs before modifying it :) */
    if(NoOfRecs == 0)
    {
        return FromPreset;
    }

    if(NoOfRecs == 1)
    {
        pgdb_GetByIndex( PRESET_TABLE, 0, (Address)&presetdat );

        /* Boundary condition, need not wait untill PR comes for this, handle first itself :) */
        Retval = (presetdat.PresetNumber == FromPreset)? (presetdat.PresetNumber + 1):FromPreset;
        return Retval;
    }

    presetdat.PresetNumber = FromPreset;
    if(FALSE == pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat))
    {       
        return FromPreset;
    }
    for(i = (NoOfRecs - 1); i >= 0; i--)
    {
        pgdb_GetByIndex( PRESET_TABLE, i, (Address)&presetdat );
        passval = 1;
        if(presetdat.PresetNumber <= FromPreset) 
        {
            PreviousPreset = presetdat.PresetNumber;
            if(i == 0)
            {
                /* Boundary condition, need not wait untill PR comes for this, handle first itself :) */
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
    }
    return Retval;
}

/*Stub */
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_DeleteAllDigitalChannels()
{
	return 0;
}    
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_DeleteInvalidPTCTable()
{
	return 0;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_UpdatingLCNDuringUpdateInstallation()
{
	return 0;
}
Bool CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_AssignPresetsOfOtherCountries   (void)
{
	return 0;
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbooksort_RemoveDigitalPresets(void)
{
	return;
}

void CHsvEuropeInstallation_mDbookSort_Priv::idbookconfN_OnConflictsDetected(void)
{
	return;
}

