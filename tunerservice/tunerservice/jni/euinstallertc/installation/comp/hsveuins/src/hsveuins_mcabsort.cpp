/**********************************************************************
 *
 *   C Source:       hsveuins_mcabsort.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    ponraman %
 *   %date_created:  Fri Jan 18 18:20:47 2013 %
 *
 **********************************************************************/
#include "_hsveuins_mcabsort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mcabsort")

#include "hsveuins_cabsort.h"

/*****************************************
  provides IHsvHybridPresetSort cabsort
 ******************************************/


void CHsvEuropeInstallation_mcabsort_Priv::icabpow_Init()
{
    mCabsortPump = pmp_PmpCreateEx( pen_PumpEngine, mCabsortHandler, FALSE, "hsveuins_mcabsort" );
}

void CHsvEuropeInstallation_mcabsort_Priv::icabpow_TurnOn()
{
}

void CHsvEuropeInstallation_mcabsort_Priv::icabpow_TurnOff()
{
}

void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_Initialise()
{
    if(AUTO_INSTALL)
    {
        mCurrentTvPreset = mCurrentRadioPreset  = INVALID_PRESET;
    }
    mFirstInstalledPreset = 0xFFFF; 
}

void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AddAnalogPreset(Address adata)
{
    HsvPgdatAnalogData *panadat = (HsvPgdatAnalogData *)adata;

    /* obtain the PresetNumber for Analog table only for Update Install, for Auto Install it ll come from hsvprins */
    if(UPDATE_INSTALL)
    {
        panadat->PresetNumber = mGetAutomaticPlatformPresetNumber();
    }

    INITIALIZE_ANALOG_ITEMS(*panadat)
        pgdb_Add (ANALOG_TABLE, (Address)adata);

}

Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AutoStoreManualInstallationValues()
{
    Bool retval = FALSE;
    int CurrentPreset;
    HsvPgdatAnalogData    anadat;

    if( pgdb_GetNoRecords(ANALOG_TABLE) < div_MaxAnalogPresets )
    {
        mFindPresetNumberForService(SERVICE_TYPE_NONE);
        TraceNotice(m,"%s:%d:mCurrentTvPreset=%d",__FUNCTION__,__LINE__,mCurrentTvPreset);

        if(IS_RADIO_SERVICE(SERVICE_TYPE_NONE))
        {
            CurrentPreset = mCurrentRadioPreset;
        }
        else
        {
            CurrentPreset = mCurrentTvPreset;
        }
        if(mValidPresetForService(CurrentPreset,SERVICE_TYPE_NONE))
        {   
            retval = mAddPresetEntryForNewAnalog( &anadat, CURRENT_PRESET(SERVICE_TYPE_NONE));
            if(retval)
            {
                mCurrentTvPreset++;
            }       
        }
        else
        {
            TraceNotice(m,"%s %d Could not allocate the preset entry to the Analog service", __FUNCTION__, __LINE__);
            ASSERT(!"Could not allocate the preset entry to the service");
        }
    }
    else
    {
        TraceNotice(m,"%s %d Installed Analog services exceeds Max Limit : %d", __FUNCTION__, __LINE__, div_MaxAnalogPresets);
        ASSERT(FALSE);
    }
    return retval;
}

void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_RemoveDigitalPresets()
{
    /* Remove services that are no longer pointed by CDSDs */
    Bool tsfound = FALSE; 
    HsvPgdatDigTSData tsdat;
    int i = 0, j = 0, k = 0, maxts = pgdb_GetNoRecords(PTC_TABLE);

    tsfound = mTSInTransmission();
    if(tsfound)
    {
        for(i = 0 ; i < maxts; i++)
        {
            if( pgdb_GetByIndex( PTC_TABLE, i, (Address)&tsdat) )
            {
                tsfound = FALSE;
                if(IS_NOT_USER_INSTALLED(tsdat))
                {
                    for(j = 0; j < mFlashCableDS.NumOfTs; j++)
                    {
                        /* As alt frequencies are coming into picture only onid, tsid comparison is made */
                        if((tsdat.OriginalNetworkId == mFlashCableDS.TsParam[j].ONID) &&
                                (tsdat.Tsid == mFlashCableDS.TsParam[j].Tsid) &&
                                (eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltTSRelocatedDesc) )
                        {
                            tsfound = TRUE;
                            TraceDebug(m,"Ts found for %d onid and %d Tsid \r\n",tsdat.OriginalNetworkId, tsdat.Tsid);
                            break;
                        }
                        else
                        {
                            for(k = 0; k < mFlashCableDS.TsParam[j].NumOfCDSD; k++)
                            {
                                if(tsdat.Frequency == ((mFlashCableDS.TsParam[j].CableDescParam[k].Frequency * 1000) / 16))
                                {
                                    tsfound = TRUE;
                                    TraceDebug(m,"Ts found for Frequency = %ld \r\n",tsdat.Frequency);
                                    break;
                                }
                            }
                        }
                    }
                    if(tsfound == FALSE)
                    {
                        /* All services of that TS will be deleted */

                        TraceDebug(m,"Deleting entries of TS freq = %ld\r\n",tsdat.Frequency);
                        mDeleteTSByIndex(i);i--;maxts--;
                    }
                }
            }
        }
    }
    else
    {
        TraceDebug(m,"Probably somebody has removed the cable so dont delete anything\n");
    }
}

int CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_GetNumberOfAnalogChannelsFound()
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

void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d\n",__FUNCTION__, __LINE__);

    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)psvcdat))
    {
        presetdat.PresetNumber = psvcdat->PresetNumber;
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

Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_DeleteInvalidPTCTable()
{
    HsvPgdatDigServiceData svcdat;
    HsvPgdatDigTSData tsdat;
    Bool retval = TRUE, InvalidPTCTable = TRUE;
    int index = -1, srvindex = -1, from, to, noofptcrecords = pgdb_GetNoRecords(PTC_TABLE);

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
                retval |= pgdb_Delete( PTC_TABLE, (Address) &tsdat );
            }
        }

    }
    return retval;
}

void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_SortAll()
{
    int   event     = evDynamicSortingStep1;
    Nat16 NetworkId = hsvdvbcins_dvbset_GetAttribute(CURRENT_MODE, rins_AttributeNetworkId);

    if(mStaticSortingAvailable(NetworkId))
    {
        /* Sort from StaticTable for Only KDG and KDB Network of Germany */
        event = evStaticSortingStep1;       
    }
    pmp_PmpSend(mCabsortPump, event, (Nat32)NULL);
}

Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_IsPresetInstalled(Int32 frequency)
{
    Bool retval = FALSE;
    Nat32 minfreq = START_FREQUENCY, maxfreq = END_FREQUENCY, result = 0;
	frequency = (frequency * 16)/1000;

    if(rins_InstallationModeUpdate == rins_GetInstallationMode() ||(MANUAL_INSTALL))
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
                   	presetdat.Frequency = (presetdat.Frequency * 16) / 1000;
                    if(HsvAnalog == presetdat.Type)
                    {   /* Finally we decided ABS might not be easy to debug & wrote this one ! */
                        if( presetdat.Frequency > (Nat32)frequency)
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

    return retval;

}

HsvChannel CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_GetInstalledWeakSignalChannel()
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceNotice(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

/****************************************************************************
  Static functions Implementation
 *****************************************************************************/

void CHsvEuropeInstallation_mcabsort_Priv::mCabsortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s %d value %d\n", __FUNCTION__, __LINE__, value);

    if((rins_GetLCNSortingControl() == FALSE) && (value != evComplete))
    {
        value = evNoSorting;
    }

    switch(value)
    {
        case evStaticSortingStep1:
            mAssignPresetsFromStaticTable(FALSE, value);
            break;
        case evStaticSortingStep2:
            mAssignPresetsFromStaticTable(TRUE, value);
            break;
        case evDynamicSortingStep1:     // [Hotel TV] Sorting DVB-C honoured TV services
            mSortHonouredServices(FALSE, value, DECODER_TYPE_CABLE);
            break;
        case evDynamicSortingStep2:     // [Hotel TV] Sorting DVB-C honoured Radio services
            mSortHonouredServices(TRUE, value, DECODER_TYPE_CABLE);
            break;
        case evDynamicSortingStep3:     // [Hotel TV] Sorting DVB-T honoured TV services
            mSortHonouredServices(FALSE, value, DECODER_TYPE_TERRESTRIAL);
            break;
        case evDynamicSortingStep4:     // [Hotel TV] Sorting DVB-T honoured Radio services
            mSortHonouredServices(TRUE, value, DECODER_TYPE_TERRESTRIAL);
            break;
        case evCommonStep1:
            mSortNonHonouredServices(FALSE, value, DECODER_TYPE_CABLE);
            break;
        case evCommonStep2:
            mSortNonHonouredServices(TRUE, value, DECODER_TYPE_CABLE);
            break;
        case evCommonStep3:
            mSortNonHonouredServices(FALSE, value, DECODER_TYPE_TERRESTRIAL);
            break;
        case evCommonStep4:
            mSortNonHonouredServices(TRUE, value, DECODER_TYPE_TERRESTRIAL);
            break;
        case evCommonStep5:
            TraceDebug(m,"Calling AnalogPresetEntry\n");
            mSortAnalogServices(value);
            break;
		case evNonHonouredSortingRCSRDS:
			 TraceNotice(m,"Non Honoured  Sorting for RCS RDS");
			 mSortNonHonouredServicesRCSRDS(value);
			 break;
        case evNonHonouredSortingBlizoo:
			TraceNotice(m,"Non Honoured  Sorting for Blizoo");
			mSortNonHonouredServicesBlizoo(value);
            break;
        case evComplete:
            idvbcsort_DeleteInvalidPTCTable();
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

void CHsvEuropeInstallation_mcabsort_Priv::mNoSorting(int evCurrentSortStep)
{
    int dbindex = 0, noOfDigRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    int noOfAnaRecs = pgdb_GetNoRecords(ANALOG_TABLE);
    int noOfPresetRecs = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatDigServiceData svcdat;

    TraceDebug(m,"%s: D %d A %d\r\n",__FUNCTION__, noOfDigRecs, noOfAnaRecs);

    mCurrentTvPreset = 0;

    for(dbindex = 0; dbindex < noOfPresetRecs; ++dbindex)
    {
        HsvPgdatPresetData presetdat;

        if(pgdb_GetByIndex(PRESET_TABLE, dbindex, (Address)&presetdat) == TRUE)
        {
        	if(presetdat.PresetNumber > mCurrentTvPreset)
        		mCurrentTvPreset = presetdat.PresetNumber;
        }
    }

    mFirstInstalledPreset = mCurrentTvPreset;

    for(dbindex = 0; dbindex < noOfDigRecs; ++dbindex)
    {
        HsvPgdatPresetData presetdat;

        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
        {
        	if(svcdat.PresetNumber == INVALID_PRESET)
        	{
        		++mCurrentTvPreset;
        		presetdat.PresetNumber = mCurrentTvPreset;
        		presetdat.Type = HsvOnePart;

        		ASSIGN_PRESET_FROM_SVC(presetdat,svcdat);
        		ASSIGN_DEFAULTCOOKIES(svcdat);

        		svcdat.PresetNumber = presetdat.PresetNumber;
        		if(AUTO_INSTALL)
        			svcdat.NewPreset = FALSE;

        		if( (div_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(svcdat.ServiceType)))
                    || (div_InstallTestStreams(CURRENT_MODE, rins_GetMedium()) == div_Hide) )
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
            if( (anadat.Tuned == TRUE) &&
                    (idvbcsort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                ++mCurrentTvPreset;
                presetdat.PresetNumber = mCurrentTvPreset;
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
                TraceErr(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set\n", __LINE__, anadat.Frequency);
            }
        }
        else
        {
            TraceErr(m,"%d Analog data suddenly deleted from database\n", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    if(mCurrentTvPreset > mFirstInstalledPreset)
    	mFirstInstalledPreset++;

    pmp_PmpSend(mCabsortPump, (evComplete), (Nat32)NULL);
}

void CHsvEuropeInstallation_mcabsort_Priv::mSortAnalogServices(int evCurrentSortStep)
{
    HsvPgdatAnalogData anadat;
    int i, status, noOfRecs = pgdb_GetNoRecords(ANALOG_TABLE), numdigservice = pgdb_GetNoRecords(SERVICE_TABLE);
    Bool FollowPATS = (numdigservice == 0) && (eurdiv_AutomaticAnalogPresetAllocation() == FALSE);

	if(rins_InstallationModeBackground != rins_GetInstallationMode())
	{
		if( (FollowPATS == FALSE) && (noOfRecs > 0) )
		{
			mFindPresetNumberForService(SERVICE_TYPE_NONE);
		}
		TraceDebug(m,"%s %d noOfRecs: %d FollowPATS %d\n", __FUNCTION__, __LINE__, noOfRecs, FollowPATS);
		for(i = (noOfRecs - 1); i >= 0; i--)
		{   
			if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
			{
				/* Only Installed & New presets */
				if( (anadat.Tuned == TRUE) && (idvbcsort_IsPresetInstalled(anadat.Frequency) == FALSE) )
				{
					status = mAddPresetEntryForInstalledAnalog(anadat, (FollowPATS)? anadat.PresetNumber : CURRENT_PRESET(SERVICE_TYPE_NONE));
					
					if(status == NO_MORE_GAPFOUND)
					{
						break;
					}
					else if(status == RETRY)
					{
						i++;
					}
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
	}
	if(IS_SYSTEM_NETWORKOPERATOR_RCSRDS)
	{
    	TraceDebug(m,"RCS_RDS Diversity:After Analog Sorting Pmp send done with event = %d\r\n", evCurrentSortStep + 1);
   	 	pmp_PmpSend(mCabsortPump, (evCurrentSortStep + 1), (Nat32)NULL);
	}
	else
	{
    	TraceDebug(m,"Pmp send done with event = %d\r\n", evCurrentSortStep + 2);
    	pmp_PmpSend(mCabsortPump, (evComplete), (Nat32)NULL);
	}
}


void CHsvEuropeInstallation_mcabsort_Priv::mSortHonouredServices(Bool CheckForRadioServices, int evCurrentSortStep, Nat32 decoderType)
{
	Bool Proceed = TRUE;
    HsvPgdatDigServiceData svcdat;
    int i = 0, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE); 
	int NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
    Bool isDecTypeDvbC = ((decoderType & IHsvFrontEndApi_ChanDecDvbC) ? TRUE : FALSE);
    
    TraceNotice (m, "%s : NoOfRecs %d\n", __FUNCTION__, NoOfRecs);
	for( i = 0; i < NoOfRecs; i++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat) == TRUE )
        {
            TraceNotice (m, "%s : ServiceId %d, DecoderType %d\n", __FUNCTION__, svcdat.ServiceId, svcdat.DecoderType);
            if ((VALID_LCN_RANGE(svcdat.LCN) || (VALID_LCN_RANGE_RCSRDS(svcdat.LCN) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS))) && 
                (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices) && (mConvertDecoderType(svcdat.DecoderType) & decoderType))
            {
                // check to see if the present we want to be in is empty, if so delete our preset so we'll be put there
                HsvPgdatPresetData presetdat;
                presetdat.PresetNumber = (isDecTypeDvbC ? ASSIGN_PRESET_NUMBER(svcdat.LCN) : ASSIGN_PRESET_NUMBER_FOR_DVBT(svcdat.LCN));
                if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE )
                {
                    presetdat.PresetNumber =   svcdat.PresetNumber;
                    presetdat.Type         =   HsvOnePart;
                    TraceDebug(m,"deleting preset %d so it can be mapped to LCN service = %d\n", svcdat.PresetNumber, svcdat.LCN);
                    pgdb_Delete(PRESET_TABLE,(Address)&presetdat);                                
                    svcdat.PresetNumber = INVALID_PRESET;
                }

                if( PRESET_NOT_ALLOCATED(svcdat) )
                {
                    TraceDebug(m,"try to allocate preset entry for LCN service = %d\n", svcdat.LCN);
                    if (isDecTypeDvbC && ((((sysset_GetSystemCountry() == cids_CountryNetherlands) && 
						 ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None))) || 
						 ((sysset_GetSystemCountry() == cids_CountryBelgium) && (NetworkOperator == rins_Telenet))) &&
						  (svcdat.VisibleService == FALSE))) 
                    {
                        /* for Ziggo or other networks in netherlands Invisible services shall not be honored with the LCN position */
                        Proceed = FALSE;
                        svcdat.LCN = INVALID_LCN;
                        pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
                    }
                    else
                    {
                        Proceed = TRUE;
                    }

                    if(Proceed)
                    {
                        mDigitalPresetEntryforValidLCN(i);
                    }
                }
			}
		}
	}
	if(IS_SYSTEM_NETWORKOPERATOR_RCSRDS && (CheckForRadioServices == TRUE))
	{
    	TraceDebug(m,"RCS_RDS Diversity:After Honored sorting-Radio Pmp send done with event = %d\r\n", evCurrentSortStep + 3);
   	 	pmp_PmpSend(mCabsortPump, (evCurrentSortStep + 3), (Nat32)NULL);
	}
	else if (IS_SYSTEM_NETWORKOPERATOR_Blizoo && (CheckForRadioServices == TRUE))
	{
		TraceDebug(m,"Pmp send done with event(evNonHonouredSortingBlizoo) = %d\r\n", evNonHonouredSortingBlizoo);
   	 	pmp_PmpSend(mCabsortPump, (evNonHonouredSortingBlizoo), (Nat32)NULL);
	}
	else
	{
		TraceDebug(m,"Pmp send done with event = %d %s %d\r\n", evCurrentSortStep + 1,__FUNCTION__,__LINE__);
   	 	pmp_PmpSend(mCabsortPump, (evCurrentSortStep + 1), (Nat32)NULL);
	}
}

void CHsvEuropeInstallation_mcabsort_Priv::mSortNonHonouredServices(Bool CheckForRadioServices, int evCurrentSortStep, Nat32 decoderType)
{
    int i = 0, pref_dbindex = -1, dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    Bool pref_index_found = TRUE;

    for( i = 0; (i < noOfRecs) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = 0; dbindex < noOfRecs; dbindex++)
        {
            if (pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
            {
                if (PRESET_NOT_ALLOCATED(svcdat) && (!VALID_LCN_RANGE(svcdat.LCN)) &&
                   (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices) &&
                   (mConvertDecoderType(svcdat.DecoderType) & decoderType))
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
        }

        if(pref_index_found == TRUE)
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }

    TraceDebug(m,"Pmp send done with event = %d\r\n", evCurrentSortStep + 1);
    pmp_PmpSend(mCabsortPump, (evCurrentSortStep + 1), (Nat32)NULL);
}

//Diversity added : CR AN 7160
void CHsvEuropeInstallation_mcabsort_Priv::mSortNonHonouredServicesRCSRDS(int evCurrentSortStep)
{

	// add the the logic here :)
	int noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	int dbIndex  = 0;
	HsvPgdatDigServiceData svcdat;
	
	for(dbIndex = 0;dbIndex < noOfRecs;dbIndex++)
	{
		 if(pgdb_GetByIndex(SERVICE_TABLE, dbIndex, (Address)&svcdat) == TRUE)
         {
            if( PRESET_NOT_ALLOCATED(svcdat) && (!VALID_LCN_RANGE_RCSRDS(svcdat.LCN)))       
            {
            	mDigitalPresetEntryforInValidLCN_RCSRDS(dbIndex);
            }

		}
	
	}
	TraceDebug(m,"%s Pmp send done with event = %d\r\n",__FUNCTION__,evCurrentSortStep + 1);
    pmp_PmpSend(mCabsortPump, (evCurrentSortStep + 2), (Nat32)NULL);

}
void CHsvEuropeInstallation_mcabsort_Priv::mDigitalPresetEntryforInValidLCN_RCSRDS(int dbindex)
{
	HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
	if( pgdb_GetByIndex( SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
        REVALIDATE(svcdat.LCN);
		mAddOrUpdateEntryToPresetTable(&svcdat,mCurrentPreset_InValidLCN_RCSRDS, ADD_ENTRY);
		mCurrentPreset_InValidLCN_RCSRDS++;
	}
}

void CHsvEuropeInstallation_mcabsort_Priv::mSortNonHonouredServicesBlizoo(int evCurrentSortStep)
{

	// add the the logic here :)
	int noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	int dbIndex  = 0;
	HsvPgdatDigServiceData svcdat;
	mCurrentPreset_InValidLCN_Blizoo = 800;
	
	for(dbIndex = 0;dbIndex < noOfRecs;dbIndex++)
	{
	    if(pgdb_GetByIndex(SERVICE_TABLE, dbIndex, (Address)&svcdat) == TRUE)
         {
            if( PRESET_NOT_ALLOCATED(svcdat) && (!VALID_LCN_RANGE(svcdat.LCN)))       
            {
            	mDigitalPresetEntryforInValidLCN_Blizoo(dbIndex);
            }
	}
	
	}
	TraceDebug(m,"%s Pmp send done with event = %d\r\n",__FUNCTION__,evCurrentSortStep + 1);
    pmp_PmpSend(mCabsortPump, (evCommonStep3), (Nat32)NULL);

}
void CHsvEuropeInstallation_mcabsort_Priv::mDigitalPresetEntryforInValidLCN_Blizoo(int dbindex)
{
	HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
	if( pgdb_GetByIndex( SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
        REVALIDATE(svcdat.LCN);
		mAddOrUpdateEntryToPresetTable(&svcdat,mCurrentPreset_InValidLCN_Blizoo, ADD_ENTRY);
		mCurrentPreset_InValidLCN_Blizoo++;
	}
}

void CHsvEuropeInstallation_mcabsort_Priv::mDigitalPresetEntryforValidLCN(int dbindex)
{
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;

    if( pgdb_GetByIndex( SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
        REVALIDATE(svcdat.LCN);

        /* Check if LCN preset is occupied */
        presetdat.PresetNumber = ASSIGN_PRESET_NUMBER(svcdat.LCN);
        if( pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) )
        {
            if( mIsPresetReplacable(presetdat, svcdat) )
            {
                mAddOrUpdateEntryToPresetTable(&svcdat, ASSIGN_PRESET_NUMBER(svcdat.LCN), UPDATE_ENTRY);
            }
        }
        else
        {
            /* That preset is free. So just grab it */
            mAddOrUpdateEntryToPresetTable(&svcdat, ASSIGN_PRESET_NUMBER(svcdat.LCN), ADD_ENTRY);
        }
    }
}

void CHsvEuropeInstallation_mcabsort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    int CurrentPreset;
    HsvPgdatDigServiceData svcdat;
	Bool retVal = 0;
	
    if(pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        mFindPresetNumberForService(svcdat.ServiceType);

        if(IS_RADIO_SERVICE(svcdat.ServiceType))
        {
            CurrentPreset = mCurrentRadioPreset;
        }
        else
        {
            CurrentPreset = mCurrentTvPreset;
        }
		
		Nat16 NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

		if(NetworkOperator == rins_Ziggo || NetworkOperator == rins_Telenet) {
			retVal = mGetValidRangeofPreset(CurrentPreset,svcdat.ServiceType);
		} else {
			retVal = CURRENT_PRESET_VALID(CurrentPreset, svcdat.ServiceType);
		}
		
		
        if(retVal)
        {
            mAddOrUpdateEntryToPresetTable(&svcdat, CURRENT_PRESET(svcdat.ServiceType), ADD_ENTRY);
            if(IS_RADIO_SERVICE(svcdat.ServiceType))
            {
                mCurrentRadioPreset++;
            }
            else
            {
                mCurrentTvPreset++;
            }
        }
        else
        {
            TraceNotice(m,"%s %d Could not allocate the preset entry to the service <%d %d>", __FUNCTION__, __LINE__, svcdat.OriginalNetworkId, svcdat.ServiceId);
            ASSERT(!"Could not allocate the preset entry to the service");
        }
    }
}

int CHsvEuropeInstallation_mcabsort_Priv::mAddPresetEntryForInstalledAnalog(HsvPgdatAnalogData anadat, int PresetNumber)
{
    HsvPgdatPresetData presetdat, tmppresetdat;
    int numdigservice = pgdb_GetNoRecords(SERVICE_TABLE), retval = SUCCESS, CurrentPreset;
    Bool FollowPATS   = (numdigservice == 0) && (eurdiv_AutomaticAnalogPresetAllocation() == FALSE);

    presetdat.PresetNumber = PresetNumber;
	tmppresetdat.PresetNumber = PresetNumber;

    if( ((presetdat.PresetNumber >= DEFAULT_ANALOG_STARTPRESET) && (presetdat.PresetNumber <= ANALOG_ENDPRESET) 
		&& (pgdb_GetByKey(PRESET_TABLE, (Address)&tmppresetdat) == FALSE)) || (FollowPATS == TRUE) )
    {
        presetdat.AnalogTablePreset = anadat.PresetNumber;
        presetdat.Type = HsvAnalog;
        presetdat.Frequency = anadat.Frequency;

        ASSIGN_DEFAULTCOOKIES(anadat);

        TraceDebug(m,"%s %d Addition at Preset  @ %d\n", __FUNCTION__, __LINE__, presetdat.PresetNumber);
        presetdat.UniqueNodeId  = -1;// Invalid Node id 
        pgdb_Add(PRESET_TABLE,(Address) &presetdat);
        pgdb_Update(ANALOG_TABLE,(Address) &anadat);

        if(FollowPATS == FALSE)
        {
            if(IS_RADIO_SERVICE(SERVICE_TYPE_NONE))
            {
                mCurrentRadioPreset++;
            }
            else
            {
                mCurrentTvPreset++;
            }
        }
    }
    else
    {
        /* The current PresetGap is completed, but still few Analog presets remaining, So find new PresetGap for this */
        TraceErr(m,"The current PresetGap is completed, but still few Analog presets remaining, So find new PresetGap for this\n");

        mFindPresetNumberForService(SERVICE_TYPE_NONE);
        
		if( (mCurrentTvPreset >= DEFAULT_ANALOG_STARTPRESET) && (mCurrentTvPreset <= ANALOG_ENDPRESET) )
        {
            TraceErr(m,"Num of Analog presets allocated till now out of available Analog services\n");
            TraceErr(m,"There is new Gap found @ %d for rest of the services\n", CURRENT_PRESET(SERVICE_TYPE_NONE));
            retval = RETRY;
        }
        else
        {
            TraceErr(m,"Num of Analog presets allocated out of available Analog services\n");
            TraceErr(m,"There is no more Gap to allocate the Analog Presets\n");
            retval = NO_MORE_GAPFOUND;
        }
    }
    return retval;
}

Bool CHsvEuropeInstallation_mcabsort_Priv::mAddPresetEntryForNewAnalog(HsvPgdatAnalogData *anadat, int PresetNumber)
{
    Bool retval = TRUE;
    HsvChannel channel;
    HsvPgdatPresetData newpresetdat;
    int plfpreset = mGetAutomaticPlatformPresetNumber();

    /* Create a User Table entry */
    TraceDebug(m,"Preset = %d, PlfPreset = %d\n", PresetNumber, plfpreset);
    newpresetdat.PresetNumber = PresetNumber;           
    newpresetdat.Type = HsvAnalog;
    newpresetdat.AnalogTablePreset = plfpreset;
 //   anadat->Favorite = FALSE;
//    anadat->UserHidden = FALSE;
    anadat->ChannelLock = FALSE;
    newpresetdat.UniqueNodeId   = -1;// Invalid Node id 
	anadat->FavoriteNumber	= 0;
    pgdb_Add(PRESET_TABLE, (Address)&newpresetdat);      

    ASSIGN_DEFAULTCOOKIES(*anadat);
    INITIALIZE_ANALOG_ITEMS(*anadat)

        /* Create an Analog Preset */
        anadat->PresetNumber = plfpreset;
    pgdb_Add(ANALOG_TABLE,(Address)anadat);

    /* Store the Manual Installation Values */
    channel.Type = HsvAnalog;
    channel.Channel.AnalogNo = PresetNumber;
    hsvprins_prins_StoreManualInstallationValues(channel);

    /* Below is to update the frequency value in the Preset table entry */
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&newpresetdat))
    {
        anadat->PresetNumber = plfpreset;
        if(pgdb_GetByKey(ANALOG_TABLE, (Address)anadat))
        {
            newpresetdat.Frequency = anadat->Frequency;
            pgdb_Update(PRESET_TABLE, (Address) &newpresetdat);
        }
    }
    else
    {
        retval = FALSE;
    }

    TraceDebug(m,"%s %d retval %d\n", __FUNCTION__, __LINE__, retval);
    return retval;
}

int CHsvEuropeInstallation_mcabsort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
{
    int i = 0, retval = 0;
    int sortkey[6] = {div_CurrentCountryInvalidLCNSortKey1, 
                      div_CurrentCountryInvalidLCNSortKey2, 
                      div_CurrentCountryInvalidLCNSortKey3,
                      div_CurrentCountryInvalidLCNSortKey4, 
                      div_CurrentCountryInvalidLCNSortKey5, 
                      div_KeyInvalid };

    HsvPgdatDigServiceData pref_svcdata;

    if(pgdb_GetByIndex(SERVICE_TABLE, pref_index, (Address)&pref_svcdata))
    {
        while(sortkey[i] != div_KeyInvalid)
        {
            switch(sortkey[i])
            {
                case div_KeyOriginalNetworkId:
                    retval = (retval == 0)? (svcdata->OriginalNetworkId - pref_svcdata.OriginalNetworkId): retval;
                    break;
                case div_KeyServiceType:
                    retval = (retval == 0)? (mGetServicePriority(pref_svcdata.ServiceType) - mGetServicePriority(svcdata->ServiceType)):retval;
                    break;
                case div_KeyLCN:
                    retval = (retval == 0)? (svcdata->LCN - pref_svcdata.LCN):retval;    
                    break;
                case div_KeyServiceName:
                    retval = (retval == 0)? mStrCmp(svcdata->ChannelName, pref_svcdata.ChannelName):retval;
                    break;
                case div_KeyServiceId:
                    retval = (retval == 0)? (svcdata->ServiceId - pref_svcdata.ServiceId):retval;
                    break;
                default:
                    break;
            }
            i++;
        }
    }
    return retval;
}

int CHsvEuropeInstallation_mcabsort_Priv::mStrCmp(Nat16 *str1, Nat16 *str2)
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

int CHsvEuropeInstallation_mcabsort_Priv::mGetServicePriority(int serviceType)
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

void CHsvEuropeInstallation_mcabsort_Priv::mReadCableDS(void)
{
    /* Read cable DS from flash and update */
    FILE* fp;
    int readrec = 0;
    char FileName[MAX_CHARACTERS];

    mGetFileName(FileName, CABLE_DEL_FILEPATH);
    TraceDebug(m,"Fopen of %s\r\n", FileName);

    fp = fopen(FileName, "rb");

    if(fp)
    {
        readrec = fread((Address)(&mFlashCableDS), sizeof(mFlashCableDS), 1, fp);
        if(readrec)
        {
            TraceDebug(m,"Read Cable Del Sys from Flash\r\n");
        }
        else
        {
            mFlashCableDS.NumOfTs = 0;
            TraceDebug(m,"Read Cable Del Sys from Flash Fail\r\n");
        }
        fclose(fp);
    }
    else
    {
        mFlashCableDS.NumOfTs = 0;
        TraceDebug(m,"Unable to open %s\r\n",FileName);
        ASSERT(!"Unable to open CABLE_DEL_FILEPATH");
    }
}

void CHsvEuropeInstallation_mcabsort_Priv::mGetFileName(char *FileName, char *FilePath)
{
	char DirName[MAX_CHARACTERS];
	/*
	ffsdir_GetDirPath( DirName, ffsdir_Boot, ffsdir_Broadcast );
    
	str_strcat(DirName, "/channellib/");
*/
	str_strcpy (DirName, "/user_setting/rw/tvserver/databases/channellib/");
	if(str_strlen(DirName))
    {
        str_strcpy(FileName, DirName);
		str_strcat(FileName, FilePath);
		//PrintfNotice("%s %d file name %s\n", __FUNCTION__, __LINE__, FileName);
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
	
}

void CHsvEuropeInstallation_mcabsort_Priv::mDeleteTSByIndex(int index)
{
    HsvPgdatDigTSData tsdat;
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    int i = 0, maxservices = pgdb_GetNoRecords(SERVICE_TABLE);

    if( pgdb_GetByIndex( PTC_TABLE, index, (Address)&tsdat) )
    {
        for(i = 0; i < maxservices; i++)
        {
            if( pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat) )
            {
                if(svcdat.Frequency == tsdat.Frequency)
                {
                    TraceDebug(m,"Frequency match in Service = %d\r\n",svcdat.Frequency);
                    presetdat.PresetNumber = svcdat.PresetNumber;
                    presetdat.Type = HsvOnePart;

                    if(pgdb_GetByKey( PRESET_TABLE, (Address)&presetdat))
                    {
                        TraceDebug(m,"Removing Preset = %d, Service = %d\n", presetdat.PresetNumber, svcdat.ServiceId);
                        pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
                        /* Reduce this preset from maxservices */
                        pgdb_Delete(SERVICE_TABLE,(Address)&svcdat);i--;maxservices--;

                        sortN_OnEvent(sortN_EventChannelRemoved, CURRENT_MODE);
                        TraceDebug(m,"EventChannelRemoved sent for Preset %d\n",presetdat.PresetNumber);
                    }
                }
            }
        }
    }

    /* Delete the TS Entry as well */
    TraceDebug(m,"Removing tsdat of Freq = %ld\r\n",tsdat.Frequency);

    pgdb_Delete(PTC_TABLE, (Address)&tsdat);
}

void CHsvEuropeInstallation_mcabsort_Priv::mAssignPresetsFromStaticTable(Bool CheckForRadioServices, int evCurrentSortStep)
{
    HsvPgdatDigServiceData svcdat;
    int i, dbindex, NoOfRankingSvcs, to = pgdb_GetNoRecords(SERVICE_TABLE);
    int NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
    Nat16 *RankingListOrder = NULL, NetworkId = hsvdvbcins_dvbset_GetAttribute(CURRENT_MODE, rins_AttributeNetworkId);

    if (KDG_NETWORK(NetworkId)) /* brg36mgr# CR 95138 */
    {
        if(NetworkOperator == IHsvInstallation2_Kdg_HD)
        {
            TraceNotice(m," KDG HD Ranking List Sorting Done");
            NoOfRankingSvcs = sizeof(mGermanyKDGHDRankingList) / sizeof(mGermanyKDGHDRankingList[0]);
            RankingListOrder = mGermanyKDGHDRankingList;
        }
        else if(NetworkOperator == IHsvInstallation2_Kdg_SD)
        {
            TraceNotice(m," KDG SD Ranking List Sorting Done");
            NoOfRankingSvcs = sizeof(mGermanyKDGSDRankingList) / sizeof(mGermanyKDGSDRankingList[0]);
            RankingListOrder = mGermanyKDGSDRankingList;
        }
    }
    else
    {
        NoOfRankingSvcs = sizeof(mGermanyKDBRankingList)/sizeof(mGermanyKDBRankingList[0]);
        RankingListOrder = mGermanyKDBRankingList;
    }

    TraceDebug(m,"%s %d NoOfRankingSvcs : %d\n", __FUNCTION__, __LINE__, NoOfRankingSvcs);

    for(i=0; i < NoOfRankingSvcs; i++)
    {       
        for(dbindex = 0; dbindex <= to; dbindex++)
        {
            if( (TRUE == pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat)) 
                    && (CheckForRadioServices == IS_RADIO_SERVICE(svcdat.ServiceType)) )
            {
                if( PRESET_NOT_ALLOCATED(svcdat) &&
                        (svcdat.ServiceId == RankingListOrder[i]) )
                {
                    mDigitalPresetEntryforInValidLCN(dbindex);
                    break;
                }
            }
        }
    }

    int event = (evCurrentSortStep == evStaticSortingStep2)? (evCommonStep1): (evCurrentSortStep + 1);
    TraceDebug(m,"Pmp send done with event = %d\r\n", event);
    pmp_PmpSend(mCabsortPump, event, (Nat32)NULL);
}

void CHsvEuropeInstallation_mcabsort_Priv::mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate)
{
    HsvPgdatPresetData presetdat, tmppresetdat;

    presetdat.PresetNumber = PresetNo;
    presetdat.Type = HsvOnePart;

    ASSIGN_PRESET_FROM_SVC(presetdat,(*svcdat));
    ASSIGN_DEFAULTCOOKIES(*svcdat);

    if( (div_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(svcdat->ServiceType))) 
            || (div_InstallTestStreams(CURRENT_MODE, rins_GetMedium()) == div_Hide) )
    {
        svcdat->SystemHidden = TRUE;
    }
    else                
    {
        svcdat->SystemHidden = !(svcdat->VisibleService);
    }

    INITIALIZE_DIGITAL_ITEMS(*svcdat)

        TraceDebug(m,"@ %d %s at Preset %d by <%d,%d>\n", __LINE__, (AddOrUpdate == ADD_ENTRY)?"Addition":"Updation", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);

    if(AddOrUpdate == ADD_ENTRY)
    {
        presetdat.UniqueNodeId  = -1;// Invalid Node id 
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

    mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;

    if(svcdat->NewPreset)
    {
        sortN_OnEvent(sortN_EventNewPresetFound, CURRENT_MODE);
    }
}

Bool CHsvEuropeInstallation_mcabsort_Priv::mIsPresetReplacable(HsvPgdatPresetData presetdat, HsvPgdatDigServiceData svcdat)
{
	Bool retval = FALSE;
	int OldSvcPriority, CurrSvcPriority;
	HsvPgdatDigServiceData oldsvcdat;
	int NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	
	/* Preset Replacement not possible for 1. user rearranged matrix, 2. Manual install case */
	if( (div_UpdateLCN(rins_Cable) == TRUE) && !MANUAL_INSTALL )
	{
		ASSIGN_SVC_FROM_PRESET(oldsvcdat, presetdat);
		if( pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat) == TRUE)
		{    
            if (oldsvcdat.DecoderType == svcdat.DecoderType)
            {
                /* Rule 1: Service priority */
                OldSvcPriority = mGetServicePriority(oldsvcdat.ServiceType);
                CurrSvcPriority = mGetServicePriority(svcdat.ServiceType);
                if(CurrSvcPriority > OldSvcPriority)
                {
                    /* Current contestant has higher priority than existing Service Type. So strip him of his preset position.*/
                    retval = TRUE;
                }
                else if ( CurrSvcPriority == OldSvcPriority )
                {
                    //Rule 2: If service priorities are the same, the lower serviceId gets priority in this battle for preset no.
                    if(svcdat.ServiceId < oldsvcdat.ServiceId)
                    {
                        retval = TRUE;
                    }
                }
                
                /* Rule 3: Based on LCNs */
                if( (!VALID_LCN_RANGE(oldsvcdat.LCN)) || ((!VALID_LCN_RANGE_RCSRDS(oldsvcdat.LCN)) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS) ))
                {
                    retval = TRUE;
                }
            }
            else if ((IHsvFrontEndApi_ChanDecDvbT == oldsvcdat.DecoderType) && (IHsvFrontEndApi_ChanDecDvbC == svcdat.DecoderType))
            {
                // For Hotel TV, DVB-C channels should get the priority
				retval = TRUE;
            }
		}
	}
	if(retval == TRUE)
	{
		/* Ya - we found a better candidate for using this preset */
		INVALIDATE(oldsvcdat.LCN);
		oldsvcdat.PresetNumber = INVALID_PRESET;
		pgdb_Update(SERVICE_TABLE,(Address)&oldsvcdat); 
	}
	else
	{
		/* Need to move requested one to non honoured list */
		INVALIDATE(svcdat.LCN);
		svcdat.PresetNumber = INVALID_PRESET;
		pgdb_Update(SERVICE_TABLE,(Address)&svcdat); 
	}
	
	TraceDebug(m,"%s %d retval %d for LCN %d\n", __FUNCTION__, __LINE__, retval, svcdat.LCN);
	return retval;
}

Bool CHsvEuropeInstallation_mcabsort_Priv::mIsCurrentPresetInvalid( int PresetNo, int ServiceType)
{
    HsvPgdatPresetData presetdata;

    presetdata.PresetNumber = PresetNo;
    return ( (PresetNo == INVALID_PRESET) || pgdb_GetByKey(PRESET_TABLE, (Address)&presetdata)
            || (!mValidPresetForService(PresetNo, ServiceType)) );
}

/* Based on service type updates the static variable maintained for CURRENT_PRESET */
inline void CHsvEuropeInstallation_mcabsort_Priv::mFindPresetNumberForService(int ServiceType)
{
    int CurrentPreset = INVALID_PRESET;
    HsvPgdatPresetData presetdat;
	int NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	
    if( IS_DIGITAL_SERVICE(ServiceType) )
    {
        if(IS_RADIO_SERVICE(ServiceType))
        {
            CurrentPreset = mCurrentRadioPreset;
        }
        else
        {
            CurrentPreset = mCurrentTvPreset;
        }
    }
    else
    {
        TraceDebug(m,"%s %d mCurrentTvPreset %d\n", __FUNCTION__, __LINE__, mCurrentTvPreset);
        presetdat.PresetNumber = (mCurrentTvPreset - 1);
        if( (TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat) ))
        {
            if(presetdat.Type == HsvAnalog )
            {
                CurrentPreset = mCurrentTvPreset;
            }
        }
    }
    TraceDebug(m,"%s %d  mCurrentTvPreset = %d\n", __FUNCTION__, __LINE__, mCurrentTvPreset/*mIsCurrentPresetInvalid(CurrentPreset, ServiceType)*/);
    if( mIsCurrentPresetInvalid(CurrentPreset, ServiceType) )
    {
        if(IS_RADIO_SERVICE(ServiceType))
        {
            mAssignPresetNumberForService(ServiceType);
        }
        else
        {
            mAssignPresetNumberForService(ServiceType);
        }
    }
    TraceDebug(m,"%s %d CurrentAvailablePreset %d\n", __FUNCTION__, __LINE__, CURRENT_PRESET(ServiceType));
}

void CHsvEuropeInstallation_mcabsort_Priv::mAssignPresetNumberForService(int ServiceType)
{
    int FromPreset = 0, ToPreset = 0;
	int NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
    HsvPgdatPresetData temp;
    int index = 0;
    pgdb_GetByIndex(PRESET_TABLE, index, (Address)&temp);

    mGetPresetRangeForService(ServiceType, &FromPreset, &ToPreset);
    TraceNotice(m,"%s:%d:FromPreset=%d:ToPreset=%d",__FUNCTION__,__LINE__,FromPreset,ToPreset);

    mReInnovateFromPreset(ServiceType, &FromPreset);

    if(IS_RADIO_SERVICE(ServiceType))
    {
        mCurrentRadioPreset = mLargestGapInForwardRange(FromPreset, ToPreset);
    }
    else
    {
		mCurrentTvPreset = (NetworkOperator == rins_Blizoo ) ? ((temp.PresetNumber > 1001 && HsvAnalog != temp.Type)?temp.PresetNumber + 1 : 1001 ): mLargestGapInForwardRange(FromPreset, ToPreset);
		    TraceNotice(m,"%s:%d:mCurrentTvPreset=%d: NetworkOperator = %d",__FUNCTION__,__LINE__,mCurrentTvPreset,NetworkOperator);
    }

    if( mIsCurrentPresetInvalid(CURRENT_PRESET(ServiceType), ServiceType) )
    {
        /* Preset not free in interested gap, So try finding from default presetrange */
        DEFAULT_PRESET_RANGE(FromPreset, ToPreset);

        if(IS_RADIO_SERVICE(ServiceType))
        {
            mCurrentRadioPreset = mLargestGapInForwardRange(FromPreset, ToPreset);
        }
        else
        {
            mCurrentTvPreset = mLargestGapInForwardRange(FromPreset, ToPreset);
        }

    }
}

inline int CHsvEuropeInstallation_mcabsort_Priv::mLastLCNBasedPreset(Bool CheckForRadioServices)
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
                        if( (VALID_LCN_RANGE(svcdat.LCN)) && (ASSIGN_PRESET_NUMBER(svcdat.LCN) == presetdata.PresetNumber) )
                        {
                            retval = svcdat.PresetNumber;
                            break;
                        }
                    }
                }
            }
        }
    }

    TraceDebug(m," %s %d retval %d\n", __FUNCTION__, __LINE__, retval);
    return retval;
}

int CHsvEuropeInstallation_mcabsort_Priv::mLargestGapInForwardRange(int FromPreset, int ToPreset)
{
    int i = 0, LargestPresetGap = 1, PreviousPreset = (FromPreset - 1), Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);    
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
                    PreviousPreset = presetdat.PresetNumber;
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
				if((PreviousPreset + 1) < FromPreset)
				{
					Retval = FromPreset;
				}
                else if ( ((PreviousPreset + 1) <= ToPreset) && ((ToPreset - PreviousPreset) >= LargestPresetGap) )
				{
					Retval = (PreviousPreset + 1);
				}
            }
            break;
        }
    }



    TraceDebug(m,"%s %d Retval %d PreviousPreset %d presetdat.PresetNumber %d NoOfRecs %d LargestPresetGap %d\n", __FUNCTION__, __LINE__, Retval, PreviousPreset, presetdat.PresetNumber, NoOfRecs, LargestPresetGap);
    return Retval;
}

Bool CHsvEuropeInstallation_mcabsort_Priv::mValidPresetForService(int presetnum, int svcType)
{
    int startpreset = 0, endpreset = 0;
    Bool RetVal = FALSE;

    /* Validity of given preset range, if it is in required range based on its sevrice group(RADIO, TV, ANALOG) */
    mGetPresetRangeForService(svcType, &startpreset, &endpreset);

    if((presetnum >= startpreset) && (presetnum <= endpreset))
    {   
        RetVal = TRUE;
    }
    return (RetVal);
}

void CHsvEuropeInstallation_mcabsort_Priv::mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset)
{
    *startpreset  = NONRADIO_STARTPRESET();
    *endpreset    = NONRADIO_ENDPRESET;

    if( IS_DIGITAL_SERVICE(svcType) )
    {
        if( IS_RADIO_SERVICE(svcType) )
        {
            *startpreset = RADIO_STARTPRESET();
            *endpreset   = RADIO_ENDPRESET;
        }
    }
    else
    {
        *startpreset = ANALOG_STARTPRESET();
        *endpreset   = ANALOG_ENDPRESET;
    }

    TraceDebug(m,"%s %d PRESET RANGE <=> (%d - %d) for ServiceType %d\n", __FUNCTION__, __LINE__, *startpreset, *endpreset, svcType);
}

void CHsvEuropeInstallation_mcabsort_Priv::mReInnovateFromPreset(int ServiceType, int *FromPreset)
{
    int numdigservice;

    /* Currently this is needed only for Analog service */
    if(ServiceType == SERVICE_TYPE_NONE)
    {
        numdigservice = pgdb_GetNoRecords(SERVICE_TABLE);
        /* The spec. for Analog is the firstPreset is next 100th multiple + 1 of LastLCNBasedService */
        if( (numdigservice != 0) && (eurdiv_AutomaticAnalogPresetAllocation() == TRUE) )
        {
            if( ((*FromPreset) % 100) != 0 )
            {
                *FromPreset = *FromPreset + (100 - (*FromPreset % 100)) + 1;
            }
        }
    }
}

Bool CHsvEuropeInstallation_mcabsort_Priv::mTSInTransmission(void)
{
    Bool retval = FALSE;
    HsvPgdatDigTSData tsdat;
    int i = 0, j = 0, maxts = pgdb_GetNoRecords(PTC_TABLE);

    TraceDebug(m,"MaxTS = %d\r\n",maxts);
    mReadCableDS();

    TraceDebug(m,"Num of CDSD = %d\r\n",mFlashCableDS.NumOfTs);

    for(i = 0 ; i < maxts; i++)
    {
        if( pgdb_GetByIndex( PTC_TABLE, i, (Address)&tsdat) )
        {
            retval = FALSE;
            for(j = 0; j < mFlashCableDS.NumOfTs; j++)
            {
                /* As alt frequencies are coming into picture only onid, tsid comparison is made */
                if((tsdat.OriginalNetworkId == mFlashCableDS.TsParam[j].ONID) &&
                        (tsdat.Tsid == mFlashCableDS.TsParam[j].Tsid))
                {
                    retval = TRUE;
                    TraceDebug(m,"Ts found for %d onid and %d Tsid \r\n",tsdat.OriginalNetworkId, tsdat.Tsid);
                    break;
                }
            }
        }
        if(retval)
        {
            break;
        }
    }
    return retval;
}

/* inline functions to get Start presets based on presetgroups (ANALOG, TV, RADIO) */
inline int CHsvEuropeInstallation_mcabsort_Priv::ANALOG_STARTPRESET(void)
{
    int retval, LastLCNPreset = mLastLCNBasedPreset(FALSE);
	int NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	
    retval = ((LastLCNPreset != INVALID_PRESET) && (LastLCNPreset < NONRADIO_ENDPRESET))? (LastLCNPreset + 1) : INVALID_PRESET;
	
    /* In case of No LCN services or FixedPresetRange is enabled based on country & medium */
    if( (eurdiv_AutomaticAnalogPresetAllocation() == FALSE) || (retval == INVALID_PRESET) || ((NetworkOperator == rins_Blizoo) && (retval < 1000)) )
    {
        retval = eurdiv_AnalogStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE) );
    }

    return retval;
}

inline int CHsvEuropeInstallation_mcabsort_Priv::NONRADIO_STARTPRESET(void)
{
    int retval, LastLCNPreset = mLastLCNBasedPreset(FALSE);

    retval = ((LastLCNPreset != INVALID_PRESET) && (LastLCNPreset < NONRADIO_ENDPRESET))? (LastLCNPreset + 1) : INVALID_PRESET;


    /* In case of No LCN services or FixedPresetRange is enabled based on country & medium */
    if( (eurdiv_AutomaticDigitalPresetAllocation() == FALSE) || (retval == INVALID_PRESET) )
    {
        retval = eurdiv_NonRadioStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(PRESET_TABLE));
    }

    return retval;
}

inline int CHsvEuropeInstallation_mcabsort_Priv::RADIO_STARTPRESET(void)
{
    int retval, LastLCNPreset = mLastLCNBasedPreset(TRUE);

    retval = ((LastLCNPreset != INVALID_PRESET) && (LastLCNPreset < RADIO_ENDPRESET)) ? (LastLCNPreset + 1) : INVALID_PRESET;

    /* In case of No LCN services or FixedPresetRange is enabled based on country & medium */
    if( (eurdiv_AutomaticDigitalPresetAllocation() == FALSE) || (retval == INVALID_PRESET) )
    {
        retval = eurdiv_RadioStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(PRESET_TABLE));
    }

    return retval;
}

int CHsvEuropeInstallation_mcabsort_Priv::mGetAutomaticPlatformPresetNumber(void)
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

Bool CHsvEuropeInstallation_mcabsort_Priv::mStaticSortingAvailable(Nat16 NetworkId)
{
	Bool retval = FALSE;
	Nat16 NetworkOperator = rins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	if( (NetworkOperator == IHsvInstallation2_Kdg_HD) || (NetworkOperator == IHsvInstallation2_Kdg_SD) )
	{
		retval = !(rins_GetAttribute(AUTO_MODE, rins_AttributeLCNSorting));
	}
	else 
	{
		/* CR: AN-52846: For KBW no longer need predefined list based sorting. Follow the LCN rules */
		retval = FALSE;
	}
	TraceErr(m, "%s %d NetworkOperator %d", __FUNCTION__, retval, NetworkOperator);
	return retval;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::mGetValidRangeofPreset(int presetnum, int svcType)
{
	Bool retVal = FALSE;
	
	if( IS_DIGITAL_SERVICE(svcType) ) {
		if( IS_RADIO_SERVICE(svcType) ) {
			if((presetnum >= DEFAULT_RADIOSTARTPRESET) || (presetnum <= RADIO_ENDPRESET)) {
				retVal = TRUE;
			}
		} else {
			if((presetnum >= DEFAULT_NONRADIOSTARTPRESET) || (presetnum <= NONRADIO_ENDPRESET)) {
				retVal = TRUE;
			}
		}
	
	} else {
		if((presetnum >= DEFAULT_ANALOG_STARTPRESET) || (presetnum <= ANALOG_ENDPRESET)) {
			retVal = TRUE;
		}
	}

	return retVal;
}

/*Stub */
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_DeleteAllDigitalChannels()
{
	return 0;
}    
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_UpdatingLCNDuringUpdateInstallation()
{
	return 0;
}
Bool CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AssignPresetsOfOtherCountries   (void)
{
	return 0;
}
int CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_GetOriginalNetworkId(int CurrentCountry)
{
	return 0;
}
void CHsvEuropeInstallation_mcabsort_Priv::idvbcsort_AddDigitalPreset(HsvPgdatDigServiceData *svcdat)
{
	return;
}

