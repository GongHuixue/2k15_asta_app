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
 *  %name: hsveuins_mitasort.c %
 *  %version: TVG_FusionR3Ext_7 %
 *  %date_modified: Mon Apr 06 16:38:28 2010 %
 *  %derived_by: ponraman %
 */



#include "_hsveuins_mitasort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mitasort")

#include "hsveuins_Italy.h"


void CHsvEuropeInstallation_mitasort_Priv::iitapow_Init()
{
    mitasortPmp = pmp_PmpCreateEx( pen_PumpEngine, mItaSortHandler, FALSE, "hsveuins_mitasort" );
}

void CHsvEuropeInstallation_mitasort_Priv::iitapow_TurnOn()
{

}

void CHsvEuropeInstallation_mitasort_Priv::iitapow_TurnOff()
{

}


/*****************************************
  provides IHsvHybridPresetSort itasort
 ******************************************/

void CHsvEuropeInstallation_mitasort_Priv::itasort_Initialise()
{
    mFirstInstalledPreset = 0xFFFF;
    mCurrentPresetIndex = INVALID_PRESET;
    mConflictDetected = FALSE;
    mNonHounouredDirection = FORWARD_DIRECTION;
}

void CHsvEuropeInstallation_mitasort_Priv::itasort_SortAll()
{
    TraceNotice(m,"%s %d mitasortPmp %d", __FUNCTION__, __LINE__, mitasortPmp);
    pmp_PmpSend(mitasortPmp, evStep1, (Nat32)NULL);
}

void CHsvEuropeInstallation_mitasort_Priv::itasort_AddAnalogPreset(Address adata)
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
  //  panadat->Favorite = 0;
//    panadat->UserHidden = 0;
    panadat->PreferredStereo = 1;
	panadat->FavoriteNumber	= 0;
	panadat->UserModifiedLogo = 0;
	panadat->UserModifiedName = 0;
	panadat->LogoURL = 0;	
    pgdb_Add (ANALOG_TABLE, (Address)adata);
}

Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AutoStoreManualInstallationValues()
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

int CHsvEuropeInstallation_mitasort_Priv::itasort_GetNumberOfAnalogChannelsFound()
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

void CHsvEuropeInstallation_mitasort_Priv::itasort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d\r\n",__FUNCTION__, __LINE__);

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

int CHsvEuropeInstallation_mitasort_Priv::itasort_GetOriginalNetworkId(int CurrentCountry)
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

Bool CHsvEuropeInstallation_mitasort_Priv::itasort_IsPresetInstalled(Int32 frequency)
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

HsvChannel CHsvEuropeInstallation_mitasort_Priv::itasort_GetInstalledWeakSignalChannel(void)
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceNotice(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvEuropeInstallation_mitasort_Priv::mItaSortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s: CURRENT STEP = %d\r\n",__FUNCTION__, value);

    if((rins_GetLCNSortingControl() == FALSE) && (value != evStepComplete))
    {
        value = evNoSorting;
    }

    switch(value)
    {

        case evAutonomousSortHonoured:
            /* User has cancelled conflict menu, So sort using existing rules after that go to Step2 to sort NonHonoured services */
            TraceNotice(m,"User has cancelled conflict menu, So sort using existing rules after that go to Step2 to sort NonHonoured services");
            mAutonomousSortingHonouredServices();
            break;
        case evStep1:
            /* HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of honoured presets\n", __FUNCTION__, __LINE__);
            mSortHonouredServices(value);
            break;
        case evStep2:
            /* NON HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of non honoured presets\n", __FUNCTION__, __LINE__);
            mSortNonHonouredServices(value);
            break;

            /* The below step shall be skipped if no conflicts are found */     ;
        case evStep3:
            /* CONFLICT PRESETS */
            TraceDebug(m,"%s %d Conflict resolution start \n", __FUNCTION__, __LINE__);
            /* call conflicts module and wait for notification from it, as user UI conflict resolution screen 
               is not TimeOut based */
            iconf_ResolveConflicts(TRUE);
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

void CHsvEuropeInstallation_mitasort_Priv::mNoSorting(int evCurrentSortStep)
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
        		if( (div_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(svcdat.ServiceType)))
                    || (div_InstallTestStreams(rins_GetInstallationMode(), rins_GetMedium()) == div_Hide) )
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
                    (itasort_IsPresetInstalled(anadat.Frequency) == FALSE) )
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

    pmp_PmpSend(mitasortPmp, evStepComplete, (Nat32)NULL);
}

void CHsvEuropeInstallation_mitasort_Priv::mSortHonouredServices(int evCurrentSortStep)
{
    Bool retval = TRUE;
	HsvPgdatDigServiceData 	svcdat;
	HsvPgdatPresetData 		presetdat;
    int dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE), from = 0, to = -1;

    TraceDebug(m,"%s %d Sorting of Honoured services", __FUNCTION__, __LINE__);

    to = noOfRecs - 1;
    /* brg36mgr #141364: In case of single ONID, at first honor the services from 
     * current country only. Then sort based on the HDSLCN and static table. Followed
     * by non-honored services of same country. Then do the sorting of all remaining services
     * which are from different country */
    if(div_SupportMultipleOriginalNetworkId(rins_GetMedium()) == FALSE)
    {
        svcdat.OriginalNetworkId =   itasort_GetOriginalNetworkId(sysset_GetSystemCountry());
        retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
    }

    for(dbindex = from; (retval == TRUE) && (dbindex <= to); dbindex++)
	{
		if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
		{
			if(VALIDLCNRANGE(svcdat))
			{
				// check to see if the present we want to be in is empty, if so delete our preset so we'll be put there
                presetdat.PresetNumber = svcdat.LCN;
                if( (svcdat.LCN != svcdat.PresetNumber) && pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE )
                {
                    presetdat.PresetNumber =   svcdat.PresetNumber;
                    presetdat.Type         =   HsvOnePart;
                    TraceDebug(m,"deleting preset %d so it can be mapped to LCN service = %d\n", svcdat.PresetNumber, svcdat.LCN);
                    pgdb_Delete(PRESET_TABLE,(Address)&presetdat);                                
                    svcdat.PresetNumber = INVALID_PRESET;
                }
				if(PRESET_NOT_ALLOCATED(svcdat))
				{
					TraceNotice(m,"%s %d Sorting of Honoured services :: dbindex %d svcdat.LCN %d\n", __FUNCTION__, __LINE__, dbindex, svcdat.LCN);
					mDigitalPresetEntryforValidLCN(&svcdat);
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
	
    TraceDebug(m,"Pmp send done with event = %d\r\n", (evCurrentSortStep + 1));
    pmp_PmpSend(mitasortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

void CHsvEuropeInstallation_mitasort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
    if( mIsPresetOccupied(svcdat->LCN) == FALSE )
    {
        /* LCN position free, So just grab the entry in preset table for this service */
        if(mCanServiceBeHonoured(svcdat) == TRUE)
        {   
            mAddOrUpdateEntryToPresetTable(svcdat, svcdat->LCN, ADD_ENTRY);
        }
    }
    else
    {
        /* It can be the same service in next installation pass, so don't treat it as conflict */
        if(svcdat->PresetNumber != svcdat->LCN)
        {
            /* Same LCNs encountered check if this can be treated as Conflicts based installation mode */
            TraceNotice(m,"Same LCNs encountered, check if this can be treated as Conflicts based on rules considering installation mode. LCN %d svcdat->PresetNumber %d", svcdat->LCN, svcdat->PresetNumber);
            mConflictDetection(svcdat);
        }
    }
}

void CHsvEuropeInstallation_mitasort_Priv::mSortNonHonouredServices(int evCurrentSortStep)
{
    int i = 0, evNextStep = 0, pref_dbindex = -1, dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool pref_index_found = TRUE;

    for( i = 0; (i < noOfRecs) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = 0; dbindex < noOfRecs; dbindex++)
        {
            if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
            {
                /* 2nd check is required because we should touch LCN conflict records which were not allocated in previous pass
                   and are waiting for conflict resolution within this step (ex: Invisible service LCN records during auto install) */
				
                if( PRESET_NOT_ALLOCATED(svcdat) && ((!VALIDLCNRANGE(svcdat)) || (mConflictDetected == FALSE)) )
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

    /* This probably is confusing looks like but "Conflict Resolution" step should be skipped if there is no conflicts found 
       And that is what is done below :) */

    if(mConflictDetected == TRUE)
    {
        evNextStep = evCurrentSortStep + 1;
    }
    else
    {
        evNextStep = evCurrentSortStep + 2;
    }

    TraceDebug(m,"Pmp send done with event = %d\r\n", evNextStep);
    pmp_PmpSend(mitasortPmp, evNextStep, (Nat32)NULL);
}

void CHsvEuropeInstallation_mitasort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    HsvPgdatDigServiceData svcdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        mFindPresetNumberForService(HsvOnePart);

        if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
        {
            mAddOrUpdateEntryToPresetTable(&svcdat, mCurrentPresetIndex, ADD_ENTRY);
            mCurrentPresetIndex += mNonHounouredDirection;
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

int CHsvEuropeInstallation_mitasort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
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

int CHsvEuropeInstallation_mitasort_Priv::mStrCmp( Nat16 * str1, Nat16 * str2 )
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

int CHsvEuropeInstallation_mitasort_Priv::mGetServicePriority(int serviceType)
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
    retval = (TRUE == found) ? i: mConvertToDVBServiceType(serviceType);

    return retval;
}

void CHsvEuropeInstallation_mitasort_Priv::mSortAnalogServices(int evCurrentSortStep)
{
    int i, noOfRecs = pgdb_GetNoRecords(ANALOG_TABLE);

    HsvPgdatAnalogData anadat;
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d noOfRecs: %d\n", __FUNCTION__, __LINE__, noOfRecs);

    for(i = (noOfRecs - 1); i >= 0; i--)
    {   
        if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
        {
            /* Only for installed analog presets, 2nd check is to check if this a new service are previously installed one */
            if( (TRUE == anadat.Tuned) && 
                    (itasort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                /* Allocate the current number */
                mFindPresetNumberForService(HsvAnalog);

                presetdat.PresetNumber = mCurrentPresetIndex;
                presetdat.AnalogTablePreset = anadat.PresetNumber;

                if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
                {
                    presetdat.Type = HsvAnalog;
                    presetdat.Frequency = anadat.Frequency;
                    presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    ASSIGN_DEFAULTCOOKIES(anadat);
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
    pmp_PmpSend(mitasortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

void CHsvEuropeInstallation_mitasort_Priv::mAutonomousSortingHonouredServices(void)
{
    int dbindex = 0, from = 0, to, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
	Bool retval = TRUE;

    TraceDebug(m,"%s %d Sorting of Honoured services Autonomously\n", __FUNCTION__, __LINE__);

    to = noOfRecs - 1;
    /* brg36mgr #141364: In case of single ONID, at first honor the services from 
     * current country only. Then sort based on the HDSLCN and static table. Followed
     * by non-honored services of same country. Then do the sorting of all remaining services
     * which are from different country */
    if(div_SupportMultipleOriginalNetworkId(rins_GetMedium()) == FALSE)
    {
        svcdat.OriginalNetworkId =   itasort_GetOriginalNetworkId(sysset_GetSystemCountry());
        retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
    }

    for(dbindex = from; (retval == TRUE) && (dbindex <= to); dbindex++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
        {
            /* Revalidate now again, remember we invalidate all the LCNs in Conflict based on assumption
               that user would select one & revalidate only that, For Autonomous sorting revalidate all of these again */

            REVALIDATE(svcdat.LCN);

            if( PRESET_NOT_ALLOCATED(svcdat) && VALIDLCNRANGE(svcdat) )
            {
                mAutonomousDigitalPresetEntryforValidLCN(&svcdat);
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

    /* Done sorting with Autonomous sorting of Honoured services, Continue with sorting of nonhonoured services */
    TraceDebug(m,"Pmp send done with event = %d\r\n", evStep2);
    pmp_PmpSend(mitasortPmp, evStep2, (Nat32)NULL);
}

void CHsvEuropeInstallation_mitasort_Priv::mAutonomousDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
    Bool AutonomousSortRequired = (div_UpdateLCN(rins_GetMedium()))?TRUE:FALSE;
    HsvPgdatPresetData presetdat;

    presetdat.PresetNumber = svcdat->LCN;
    presetdat.Type = HsvOnePart;

    /* The below check cannot go FALSE, as per the design of ItalySort, as we would have a preset entry invariably for a conflict service */
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
    {
        if( mServiceIsOfPreviousPass(presetdat) == TRUE)
        {
            /* INVALIDATE(LCN) cannot be used here, Because in AutonomousSort function, REVALIDATE(LCN) is done invariably for every service,
               as all the conflict services LCN would have been invalidated and now user has skipped conflict resoultion, so REVALIDATE for those is not done */
            svcdat->LCN = INVALID_LCN; 
            TraceNotice(m,"Updation to pgdb table @ %s %d", __FUNCTION__, __LINE__);
            pgdb_Update(SERVICE_TABLE, (Address)svcdat);

            AutonomousSortRequired = FALSE;
        }   
    }

    if(AutonomousSortRequired)
    {
        Bool PresetRequireRefilling = FALSE;
        HsvPgdatDigServiceData oldsvcdat;

        ASSIGN_SVC_FROM_PRESET(oldsvcdat,presetdat);
        if(pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat) == TRUE)
        {
            /* Autonomous Sorting Rule 1. Service Priority */
            int OldSvcPriority = mGetServicePriority(oldsvcdat.ServiceType);
            int SvcPriority    = mGetServicePriority(svcdat->ServiceType);

            if (OldSvcPriority < SvcPriority) 
            {   
                PresetRequireRefilling = TRUE;
            }
            else if(OldSvcPriority == SvcPriority)
            {
                /* Autonomous Sorting Rule 2. Signal Strength */
                HsvPgdatDigTSData oldtsdat, tsdata;

                oldtsdat.Frequency          =   oldsvcdat.Frequency,      tsdata.Frequency      =   svcdat->Frequency;
                oldtsdat.StreamPriority     =   oldsvcdat.StreamPriority, tsdata.StreamPriority =   svcdat->StreamPriority;

                if( (pgdb_GetByKey (PTC_TABLE,(Address) &oldtsdat) == TRUE) && 
                        (pgdb_GetByKey (PTC_TABLE, (Address)&tsdata) == TRUE) )
                {
                    if( oldtsdat.ASignalStrength  < tsdata.ASignalStrength )
                    {
                        PresetRequireRefilling = TRUE;
                    }
                }
            }
            else
            {
                /* Existing Service is of higher ranking than the current one */
            }

            if(PresetRequireRefilling)
            {
                oldsvcdat.LCN = INVALID_LCN;
                oldsvcdat.PresetNumber = INVALID_PRESET;
                pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);

                mAddOrUpdateEntryToPresetTable(svcdat, svcdat->LCN, UPDATE_ENTRY);
            }
        }
    }
}


void CHsvEuropeInstallation_mitasort_Priv::mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate)
{
    HsvPgdatPresetData presetdat, tmppresetdat;

    presetdat.PresetNumber = PresetNo;
    presetdat.Type = HsvOnePart;

    ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
    ASSIGN_DEFAULTCOOKIES(*svcdat);

    if( (div_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(svcdat->ServiceType))) 
            || (div_InstallTestStreams(rins_GetInstallationMode(), rins_GetMedium()) == div_Hide) )
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
    TraceDebug(m,"@ %d %s at Preset %d by <%d,%d>\n", __LINE__, (AddOrUpdate == ADD_ENTRY)?"Addition":"Updation", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);
    if(AddOrUpdate == ADD_ENTRY)
    {
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

Bool CHsvEuropeInstallation_mitasort_Priv::mIsPresetOccupied(int PresetNumber)
{
    Bool retval = FALSE;
    HsvPgdatPresetData presetdat;

    presetdat.PresetNumber = PresetNumber;
    presetdat.Type = HsvOnePart;

    /* Check for Digital Channel */
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
    {
        retval = TRUE;
    }

    if(retval == FALSE)
    {
        /* No Digital Channel found so now for Analog Channel */
        presetdat.Type = HsvAnalog;

        if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
        {
            retval = TRUE;
        }   
    }

    return retval;
}

int CHsvEuropeInstallation_mitasort_Priv::mPlaceNonHonouredOrAnalogServices(void)
{
    int Retval = INVALID_PRESET, FromPreset = NON_HONOURED_START_PRESET, ToPreset = div_MaxValidLCNValue;       

    Retval = mFirstGapInForwardRange(FromPreset, ToPreset);

    if(Retval == INVALID_PRESET)
    {
        /* Could not find the gap in the range => (FromPreset - ToPreset), So try to find the Gap in Range FromPreset = 849 <-> ToPreset = 1 */
        TraceNotice(m,"Could not find the gap in the range => (850-999), Now try (849 - 1)");

        FromPreset = NON_HONOURED_START_PRESET - 1, ToPreset = div_MinValidLCNValue;
        mNonHounouredDirection = REVERSE_DIRECTION;
        Retval = mFirstGapInReverseRange(FromPreset, ToPreset);
    }
    return Retval;
}

int CHsvEuropeInstallation_mitasort_Priv::mFirstGapInForwardRange(int FromPreset, int ToPreset)
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

int CHsvEuropeInstallation_mitasort_Priv::mFirstGapInReverseRange(int FromPreset, int ToPreset)
{
    int i = 0, NextPreset = 0, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);
    int passval = 0;

    HsvPgdatPresetData presetdat;

    /* Below is the heart of the sorting module, beware of PRs before modifying it :) */

    /* No need of boundary conditions for "NoOfRecs", here as it cannot occur in this case */
    for(i = 0; i < NoOfRecs; i++)
    {
        if( pgdb_GetByIndex( PRESET_TABLE, i, (Address)&presetdat ) == TRUE)
        {
            passval = 1;
            if(presetdat.PresetNumber > FromPreset)
            {
                NextPreset = presetdat.PresetNumber;
                if(i == (NoOfRecs - 1))
                {
                    Retval = FromPreset;
                    break;
                }
                else
                {
                    passval = 0;
                }
            }

            if (passval) 
            {
                if( (NextPreset - presetdat.PresetNumber) > 1 )
                {
                    /* Found the first gap in needed range */
                    Retval = NextPreset - 1; 
                    break;
                }   
                else
                {
                    if(i == (NoOfRecs - 1))
                    {
                        Retval = (presetdat.PresetNumber > ToPreset)?(presetdat.PresetNumber - 1):INVALID_PRESET;
                        break;
                    }       
                    else
                    {   
                        NextPreset = presetdat.PresetNumber;
                    }
                }
            }
        }
    }

    return Retval;
} 

void CHsvEuropeInstallation_mitasort_Priv::mConflictDetection(HsvPgdatDigServiceData *svcdat)
{
    HsvPgdatPresetData presetdat;

    /* We know preset is occupied, Now check for few rules to detect it as conflict or not depending on installation mode */
    if(AUTO_INSTALL)
    {
        if(mCanServiceBeHonoured(svcdat) == TRUE)
        {   
            TraceNotice(m,"Conflicts detected for LCN %d", svcdat->LCN);
            mConflictDetected = TRUE;

        }
    }
    else
    {
        /* Update or manual install */
        Bool IsItConflict = TRUE;
        Bool SvcHonoured = mCanServiceBeHonoured(svcdat);

        IsItConflict = SvcHonoured?IsItConflict: FALSE;
        if(SvcHonoured == TRUE)
        {
            presetdat.PresetNumber = svcdat->LCN;
            presetdat.Type = HsvOnePart;    ;

            if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
            {
                HsvPgdatDigServiceData oldsvcdat;

                ASSIGN_SVC_FROM_PRESET(oldsvcdat,presetdat);
                if( (pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat) == TRUE) && 
                        (IS_VISIBLE_SERVICE(oldsvcdat) == FALSE) )
                {
                    /* Naresh: known bug here Can user move a Invisible service???, if so it is not handled here */
                    INVALIDATE(oldsvcdat.LCN);
                    oldsvcdat.PresetNumber = INVALID_PRESET;
                    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
                    pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);

                    mAddOrUpdateEntryToPresetTable(svcdat, svcdat->LCN, UPDATE_ENTRY);

                    /* No conflicts detected as the old service is invisible one, its LCN is dis-honoured */
                    IsItConflict = FALSE;
                }
            }
        }

        mConflictDetected = (mConflictDetected == FALSE)?IsItConflict:mConflictDetected;
        if(IsItConflict == TRUE)
        {
            TraceNotice(m,"Conflicts detected for LCN %d", svcdat->LCN);
        }

    }
}

inline void CHsvEuropeInstallation_mitasort_Priv::mFindPresetNumberForService(int AnalogOrDigital)
{
    int NoOfRecs = pgdb_GetNoRecords((AnalogOrDigital == HsvOnePart)? PRESET_TABLE: SERVICE_TABLE);
    if( (mCurrentPresetIndex == INVALID_PRESET) || mIsPresetOccupied(mCurrentPresetIndex) || (VALID_PRESET_RANGE(mCurrentPresetIndex) == FALSE))
    {
        if(NoOfRecs == 0)
        {
            mCurrentPresetIndex = START_PRESET;
        }
        else
        {
            mCurrentPresetIndex = mPlaceNonHonouredOrAnalogServices();
        }   
    }
    //TraceNotice(m,"%s %d mCurrentPresetIndex %d", __FUNCTION__, __LINE__, mCurrentPresetIndex);
}

int CHsvEuropeInstallation_mitasort_Priv::mGetAutomaticPlatformPresetNumber(void)
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

Bool CHsvEuropeInstallation_mitasort_Priv::mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat)
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

void CHsvEuropeInstallation_mitasort_Priv::iconfN_OnEvent(int eventId)
{
    mConflictDetected = FALSE;
    if(eventId == iconfN_ConflictsResolved)
    {
        /* All the conflicts resolved now, So start assigning the presets for these, the sorting steps of Honoured & Non - Honoured would continue */

        TraceNotice(m,"%s %d Conflicts resolved", __FUNCTION__, __LINE__);
        pmp_PmpSend(mitasortPmp, evStep1, (Nat32)NULL);
    }
    else if(eventId == iconfN_ConflictsNotResolved)
    {
        /* Conflicts Not reolved by neither "Automatic Resolution" nor user has helped in resolving it :) */

        /* 
           Now its a different story LCNs have to be sorted based on exisiting rules 
           1. ServicePriority
           2. Signal Strength of the MUX
           */

        TraceNotice(m,"%s %d Conflicts not resolved by user", __FUNCTION__, __LINE__);
        pmp_PmpSend(mitasortPmp, evAutonomousSortHonoured, (Nat32)NULL);
    }
    else
    {
        /* Unknown event from mConflicts - Do Nothing */
        TraceNotice(m,"%s %d Unknown event from mConflicts - Do Nothing", __FUNCTION__, __LINE__);
        ASSERT(FALSE);
    }
}

Bool CHsvEuropeInstallation_mitasort_Priv::mCanServiceBeHonoured(HsvPgdatDigServiceData *currsvcdat)
{
    Bool retval = TRUE;
    int currdbindex = -1;

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
                    if( (currdbindex != dbindex) && (currsvcdat->LCN == svcdat.LCN) )
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
        INVALIDATE(currsvcdat->LCN);
        TraceNotice(m,"Updation to pgdb table @ %s %d", __FUNCTION__, __LINE__);
        pgdb_Update(SERVICE_TABLE, (Address)currsvcdat);
    }
    return retval;
}

/*Stub */
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_mitasort_Priv::itasort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_DeleteAllDigitalChannels()
{
	return 0;
}    
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_DeleteInvalidPTCTable()
{
	return 0;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_UpdatingLCNDuringUpdateInstallation()
{
	return 0;
}
Bool CHsvEuropeInstallation_mitasort_Priv::itasort_AssignPresetsOfOtherCountries   (void)
{
	return 0;
}
void CHsvEuropeInstallation_mitasort_Priv::itasort_RemoveDigitalPresets(void)
{
	return;
}
void CHsvEuropeInstallation_mitasort_Priv::itasort_AddDigitalPreset(HsvPgdatDigServiceData *svcdat)
{
	return;
}

void CHsvEuropeInstallation_mitasort_Priv::iconfN_OnConflictsDetected()
{
	return;
}
