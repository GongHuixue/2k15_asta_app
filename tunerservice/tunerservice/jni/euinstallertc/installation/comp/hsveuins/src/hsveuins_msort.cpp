/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsveuins_msort.c %
 *       %version: TVG_Fusion_7 %
 * %date_modified: Mon Apr 06 17:44:09 2009 %
 *    %derived_by: aneeshc % 
 */




/****************************************************************************
 * Local include files
 ****************************************************************************/

#include "_hsveuins_msort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_msort")





Pump CHsvEuropeInstallation_msort_Priv::s__mdvbtsortPmp;

int CHsvEuropeInstallation_msort_Priv::s__mCurrentPresetIndex = INVALID_PRESET,CHsvEuropeInstallation_msort_Priv::s__mFirstInstalledPreset = 0xFFFF;


/*****   Local Structures and enums   *****/


int CHsvEuropeInstallation_msort_Priv::s__mServicePriority[MAX_SERVICE_TYPES] =
{
    AppApiDatabroadcastService,
    AppApiTeletextService,
    AppApiRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiAdvCodecSDTelevisionService,
    AppApiAdvCodecHDTelevisionService       
};



/*****   static function prototypes   *****/
























/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvEuropeInstallation_msort_Priv::mDvbtSortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s: CURRENT STEP = %d",__FUNCTION__, value);

    if((rins_GetLCNSortingControl() == FALSE) && (value != evStepComplete))
    {
        value = evNoSorting;
    }

    switch(value)
    {

        case evStep1:
            /* HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of honoured presets", __FUNCTION__, __LINE__);
            mSortHonouredServices(value);
            break;
        case evStep2:
            /* NON HONOURED PRESETS */
            TraceDebug(m,"%s %d swap of HD & SD presets", __FUNCTION__, __LINE__);
            mSwapSDAndHDPresets(value);
            break;
        case evStep3:
            /* NON HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of non honoured presets from static table", __FUNCTION__, __LINE__);
            mSortPresetsOfStaticTable(value);
            break;
        case evStep4:
            /* NON HONOURED PRESETS */
            TraceDebug(m,"%s %d Sorting of non honoured presets", __FUNCTION__, __LINE__);
            mSortNonHonouredServices(value, TRUE);
            break;
        case evStep5:
            /* NON HONOURED OTHER COUNTRY PRESETS */
            TraceDebug(m,"%s %d Sorting of non honoured other country presets", __FUNCTION__, __LINE__);
            mSortNonHonouredServices(value, FALSE);
            break;
        case evStep6:
            /* ANAvsdvsdfsLOG PRESETS */
            TraceDebug(m,"%s %d Sorting of analog presets ", __FUNCTION__, __LINE__);
            mSortAnalogServices(value);
            break;
        case evStepComplete:
            TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
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

void CHsvEuropeInstallation_msort_Priv::mNoSorting(int evCurrentSortStep)
{
    int dbindex = 0, noOfDigRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    int noOfAnaRecs = pgdb_GetNoRecords(ANALOG_TABLE);
    int noOfPresetRecs = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatDigServiceData svcdat;

    TraceNotice(m,"%s: D %d A %d\r\n",__FUNCTION__, noOfDigRecs, noOfAnaRecs);


    if(AUTO_INSTALL || noOfPresetRecs == 0)
    {
    	mCurrentPresetIndex = 0;
    }
    else
    {
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
    }

    TraceNotice(m,"%s:Current Preset: %d\r\n",__FUNCTION__, mCurrentPresetIndex);


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
        			svcdat.NewPreset = FALSE;

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
                    (idvbtsort_IsPresetInstalled(anadat.Frequency) == FALSE) )
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
                TraceDebug(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set", __LINE__, anadat.Frequency);
            }
        }
        else
        {
            TraceDebug(m,"%d Analog data suddenly deleted from database", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    pmp_PmpSend(mdvbtsortPmp, evStepComplete, (Nat32)NULL);
}

void CHsvEuropeInstallation_msort_Priv::mSortHonouredServices(int evCurrentSortStep)
{
    int dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    int from = 0, to = 0;
    Bool retval = TRUE;

    TraceDebug(m,"%s %d Sorting of Honoured services", __FUNCTION__, __LINE__);

    to = noOfRecs - 1;
    /* brg36mgr #141364: In case of single ONID, at first honor the services from 
     * current country only. Then sort based on the HDSLCN and static table. Followed
     * by non-honored services of same country. Then do the sorting of all remaining services
     * which are from different country */
    if(div_SupportMultipleOriginalNetworkId(rins_GetMedium()) == FALSE)
    {
        svcdat.OriginalNetworkId =   idvbtsort_GetOriginalNetworkId(sysset_GetSystemCountry());
        TraceDebug(m,"%s %d country: %d ONID: %d", __FUNCTION__, __LINE__,sysset_GetSystemCountry(),svcdat.OriginalNetworkId);
        retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
    }

	for(dbindex = from; retval && (dbindex <= to); dbindex++)
	{
		if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
		{
			if( (PRESET_NOT_ALLOCATED(svcdat)||( mIsPresetOccupied(svcdat.LCN) == FALSE )))
			{
				/* For UAE Country the Valid LCN Range is: 1 - 799 for others its from 0-999*/
				if((sysset_GetSystemCountry() == cids_CountryUAE) && (VALID_LCN_RANGE_UAE(svcdat.LCN)))
				{
					TraceDebug(m,"%s %d Country UAE :Sorting of Honoured services :: dbindex %d svcdat.LCN %d", __FUNCTION__, __LINE__, dbindex, svcdat.LCN);
					mDigitalPresetEntryforValidLCN(&svcdat);
				}
				else if ((sysset_GetSystemCountry() != cids_CountryUAE) && (VALID_LCN_RANGE(svcdat.LCN)))
				{
					TraceDebug(m,"%s %d Sorting of Honoured services :: dbindex %d svcdat.LCN %d", __FUNCTION__, __LINE__, dbindex, svcdat.LCN);
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
				/* Non Honoured LCN or RADIO Service or DVBT preset.
				   So lets come back later */
			}
		}
		else
		{
			ASSERT(!" Who deleted the service here ");
		}
	}
    
	TraceDebug(m,"Pmp send done with event = %d", (evCurrentSortStep + 1));
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

void CHsvEuropeInstallation_msort_Priv::mSwapSDAndHDPresets(int evCurrentSortStep)
{
    int i, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    HsvChannel SwapChannel01, SwapChannel02;

    if(eurdiv_SupportHDSLCN(rins_GetMedium()))
    {
        for( i = 0; i <= NoOfRecs; i++)     
        {
            if( TRUE == pgdb_GetByIndex( SERVICE_TABLE, i, (Address)&svcdat) )
            {
                if( (VALID_LCN_RANGE(svcdat.LCN)) && (VALID_LCN_RANGE(svcdat.LowPrioLCN)) )
                {
                    TraceInfo(m,"%s %d svcdat.ServiceType : %d svcdat.LowPrioLCN : %d svcdat.LCN : %d, SvcId = %d", __FUNCTION__, __LINE__, svcdat.ServiceType, svcdat.LowPrioLCN, svcdat.LCN,svcdat.ServiceId);
                    if( (svcdat.LowPrioLCN < svcdat.LCN) && (svcdat.PresetNumber != svcdat.LowPrioLCN) )
                    {
                        TraceInfo(m,"%s %d svcdat.ServiceType : %d svcdat.LowPrioLCN : %d svcdat.LCN : %d, SvcId = %d", __FUNCTION__, __LINE__, svcdat.ServiceType, svcdat.LowPrioLCN, svcdat.LCN,svcdat.ServiceId);
                        SwapChannel01.Type              = (AppApiChannelType)svcdat.Type;
                        SwapChannel01.Channel.OnePart   = svcdat.LCN;

                        SwapChannel02.Type              = (AppApiChannelType)svcdat.Type;
                        SwapChannel02.Channel.OnePart   = svcdat.LowPrioLCN;

                        presetdat.Type = svcdat.Type;
                        presetdat.PresetNumber = svcdat.LowPrioLCN;

                        /* IF LowPrioLCN is not occupied, only then do swapping */
                        if(FALSE == pgdb_GetByKey( PRESET_TABLE, (Address)&presetdat))
                        {
                            pgdat_SwapChannels( SwapChannel01, SwapChannel02);
                            TraceDebug(m,"%s:%d : Swapping", __FUNCTION__,__LINE__);
                        }
                    }
                }
            }
        }
    }    
    TraceDebug(m,"Pmp send done with event = %d", (evCurrentSortStep + 1));
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

Bool CHsvEuropeInstallation_msort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
	Bool retval = FALSE;
	HsvPgdatPresetData presetdat;
    if( mIsPresetOccupied(svcdat->LCN) == FALSE )
    {
		if(svcdat->PresetNumber != INVALID_PRESET)
		{
			presetdat.PresetNumber =   svcdat->PresetNumber;
			presetdat.Type         =   HsvOnePart;
			pgdb_Delete(PRESET_TABLE,(Address)&presetdat);                                
			svcdat->PresetNumber = INVALID_PRESET;
		}

		mAddOrUpdateEntryToPresetTable(svcdat, svcdat->LCN, ADD_ENTRY);
		retval = TRUE;
	}
	else
	{
		retval = mUpdateDigitalPresetEntryforValidLCN(svcdat);
	}
    return retval;
}

Bool CHsvEuropeInstallation_msort_Priv::mUpdateDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
    Bool retval = FALSE, CanBeReplaced = (div_UpdateLCN(rins_GetMedium()) || (MANUAL_INSTALL))?TRUE:FALSE;
    HsvPgdatPresetData presetdat,presetdattemp;
    int dbindex =0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData tempsvcdat;
    HsvPgdatDigTSData oldtsdat, tsdata;

    presetdat.PresetNumber = svcdat->LCN;
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
    {
        if( mServiceIsOfPreviousPass(presetdat) == TRUE)
        {
            // if current preset is SD service & conflicting with HD, then HD will gets the Preset

            if(CanBeReplaced && HD_LCN(svcdat))
            {
                //HD simulcast LCN is present ,replace 
                for( dbindex = 0; dbindex < noOfRecs; dbindex++)
                {
                    if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&tempsvcdat) == TRUE)
                    {
                        if((svcdat->LCN == tempsvcdat.LowPrioLCN )&&(tempsvcdat.LowPrioLCN == tempsvcdat.PresetNumber))
                        {
                            /*if(current installed prest != HD || !user moved)*/
                            if(!HD_LCN1(tempsvcdat))
                            {
                                svcdat->PresetNumber = tempsvcdat.PresetNumber;
                                presetdattemp.PresetNumber = tempsvcdat.PresetNumber;
                                ASSIGN_PRESET_FROM_SVC(presetdattemp,tempsvcdat);

                                //delete tempsvcdat.PresetNumber from preset table
                                pgdb_Delete(PRESET_TABLE, (Address)&presetdattemp);


                                if( mIsPresetOccupied(tempsvcdat.LCN) == FALSE )
                                {                                    
                                    tempsvcdat.PresetNumber = tempsvcdat.LCN;
                                    mAddOrUpdateEntryToPresetTable(&tempsvcdat, tempsvcdat.PresetNumber, ADD_ENTRY);

                                }
                                else
                                {                                    
                                    tempsvcdat.LCN = INVALID_LCN; 
                                    tempsvcdat.PresetNumber = INVALID_PRESET;
                                    pgdb_Update(SERVICE_TABLE, (Address)&tempsvcdat);                                    
                                }                                

                                mAddOrUpdateEntryToPresetTable(svcdat, svcdat->PresetNumber, ADD_ENTRY);
                            }
                            else
                            {
                                svcdat->LCN = INVALID_LCN; 
                                pgdb_Update(SERVICE_TABLE, (Address)svcdat);

                            }

                            break;
                        }


                    }
                }

                retval = TRUE;                
                CanBeReplaced = FALSE;
            }
            else if (!MANUAL_INSTALL)
            {
                svcdat->LCN = INVALID_LCN; 
                pgdb_Update(SERVICE_TABLE, (Address)svcdat);
                CanBeReplaced = FALSE;
            }   

        }        

    }   
    if(CanBeReplaced)
    {
        Bool PresetRequireRefilling = FALSE;
        Bool Proceed = TRUE;
        HsvPgdatDigServiceData oldsvcdat;

        if(presetdat.Type == HsvAnalog)
        {
            Proceed = FALSE;
            svcdat->LCN = INVALID_LCN; 
            pgdb_Update(SERVICE_TABLE, (Address)svcdat);
            retval = TRUE;
        }

        if(Proceed)
        {
            ASSIGN_SVC_FROM_PRESET(oldsvcdat,presetdat);
            if(pgdb_GetByKey (SERVICE_TABLE,(Address)&oldsvcdat) == TRUE)
            {
                /* Autonomous Sorting Rule 1. Service Priority */
                int OldSvcPriority = mGetServicePriority(oldsvcdat.ServiceType);
                int SvcPriority    = mGetServicePriority(svcdat->ServiceType);
                if(MANUAL_INSTALL)
                {
                    PresetRequireRefilling = TRUE;
                }
                else
                {
                    if (OldSvcPriority < SvcPriority) 
                    {   
                        PresetRequireRefilling = TRUE;
                    }
                    else if(OldSvcPriority == SvcPriority)
                    {
                        /* Autonomous Sorting Rule 2. Signal Strength */
                        oldtsdat.Frequency          =   oldsvcdat.Frequency;
                        oldtsdat.StreamPriority     =   oldsvcdat.StreamPriority;

                        tsdata.Frequency            =   svcdat->Frequency;
                        tsdata.StreamPriority       =   svcdat->StreamPriority;

                        if( (pgdb_GetByKey(PTC_TABLE, (Address)&oldtsdat) == TRUE) && 
                                (pgdb_GetByKey(PTC_TABLE, (Address)&tsdata) == TRUE) )
                        {
                            if(mCompareMultiplex(oldtsdat, tsdata))
                            {
                                PresetRequireRefilling = TRUE;
                            }
                        }
                    }
                    else
                    {
                        /* Existing Service is of higher ranking than the current one */
                    }
                }
                if(PresetRequireRefilling)
                {
                    if(presetdat.Type != HsvAnalog)
                    {
                        oldsvcdat.LCN = INVALID_LCN;
                        oldsvcdat.PresetNumber = INVALID_PRESET;
                        pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);
                    }

                    mAddOrUpdateEntryToPresetTable(svcdat, svcdat->LCN, UPDATE_ENTRY);
                    retval = TRUE;
                }
                else 
                {
                    //invalidate the LCN of the service which lost the battle
                    svcdat->LCN = INVALID_LCN; 
                    pgdb_Update(SERVICE_TABLE, (Address)svcdat);
                }
            }
        }
    }

    return retval;
}

void CHsvEuropeInstallation_msort_Priv::mSortNonHonouredServices(int evCurrentSortStep, Bool CheckForCurrentOnId)
{
    int i = 0, from = 0, to, pref_dbindex = -1, dbindex = 0;
    HsvPgdatDigServiceData svcdat;
    Bool retval = TRUE, pref_index_found = TRUE;

    to = pgdb_GetNoRecords(SERVICE_TABLE) - 1;
    if( CheckForCurrentOnId && (div_SupportMultipleOriginalNetworkId(rins_GetMedium()) == FALSE) )
    {
        svcdat.OriginalNetworkId =   idvbtsort_GetOriginalNetworkId(sysset_GetSystemCountry());
        retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
    }

    for( i = from; retval && (i <= to) && (pref_index_found == TRUE); i++)
    {
        pref_index_found = FALSE;
        for(dbindex = from; dbindex <= to; dbindex++)
        {
            if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
            {
                /* This function will act as a generic function especially for the other countries. 
                 * Here rather than going for only non-honored services, sort the honored one also
                 * For the installed country this wont create an issue as these services will already
                 * be sorted before this is executed */
                if( PRESET_NOT_ALLOCATED(svcdat) /* && (!VALID_LCN_RANGE(svcdat.LCN)) */)
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
            }
        }
        if(pref_index_found == TRUE)
        {
            mDigitalPresetEntryforInValidLCN(pref_dbindex);
        }
    }

    TraceDebug(m,"Pmp send done with event = %d", evCurrentSortStep + 1);
    pmp_PmpSend(mdvbtsortPmp, evCurrentSortStep + 1, (Nat32)NULL);
}

void CHsvEuropeInstallation_msort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    HsvPgdatDigServiceData svcdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        mFindPresetNumberForService(HsvOnePart);

        if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
        {
            mAddOrUpdateEntryToPresetTable(&svcdat, mCurrentPresetIndex, ADD_ENTRY);
            mCurrentPresetIndex++;
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

void CHsvEuropeInstallation_msort_Priv::mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate)
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

    TraceDebug(m,"@ %d %s at Preset %d by <%d,%d>", __LINE__, (AddOrUpdate == ADD_ENTRY)?"Addition":"Updation", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId);
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
            presetdat.UniqueNodeId  = tmppresetdat.UniqueNodeId;
        }
        pgdb_Update(PRESET_TABLE, (Address)&presetdat);
    }

    svcdat->PresetNumber = presetdat.PresetNumber;
    pgdb_Update(SERVICE_TABLE, (Address)svcdat);

    mFirstInstalledPreset  = ((mFirstInstalledPreset > presetdat.PresetNumber) && (svcdat->VisibleService == TRUE)&&(svcdat->SystemHidden == FALSE)) ? presetdat.PresetNumber: mFirstInstalledPreset;

    if(svcdat->NewPreset)
    {
        sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
    }
}

void CHsvEuropeInstallation_msort_Priv::mSortAnalogServices(int evCurrentSortStep)
{
    int i, noOfRecs = pgdb_GetNoRecords(ANALOG_TABLE), digservices = pgdb_GetNoRecords(SERVICE_TABLE);

    HsvPgdatAnalogData anadat;
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d noOfRecs: %d", __FUNCTION__, __LINE__, noOfRecs);

//    for(i = 0 ; i < (noOfRecs); i++) //the order should be ascending order of frequencies from the ANALOG TABLE
    for(i = (noOfRecs - 1); i >= 0; i--)
    {   
        if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
        {
            /* Only for installed analog presets, 2nd check is to check if this a new service are previously installed one */
            if( (TRUE == anadat.Tuned) && 
                    (idvbtsort_IsPresetInstalled(anadat.Frequency) == FALSE) )
            {
                /* Allocate the current number */
                if( (TRUE == div_AnalogOnly) || (digservices == 0) )
                {   
                    /* Analog only installation or installation which yeilded no digital service - Follow PATS */
                    if( eurdiv_AutomaticAnalogPresetAllocation() == TRUE)
                    {
                        presetdat.PresetNumber = anadat.PresetNumber;
                    }
                }
                else
                {
                    mFindPresetNumberForService(HsvAnalog);
                    presetdat.PresetNumber = mCurrentPresetIndex;
                }
                presetdat.AnalogTablePreset = anadat.PresetNumber;

                if( VALID_PRESET_RANGE(presetdat.PresetNumber) )
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
                    TraceDebug(m,"%d Cannot Add Analog Preset as there is no place in the PRESET LIST", __LINE__);
                    ASSERT(!"Preset table is FULL");
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

    TraceDebug(m,"Pmp send done with event = %d", evCurrentSortStep + 1);
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

inline void CHsvEuropeInstallation_msort_Priv::mFindPresetNumberForService(int AnalogOrDigital)
{
    HsvPgdatPresetData presetdat;
    int SortingNewPresetTypes = FALSE, NoOfRecs = pgdb_GetNoRecords((AnalogOrDigital == HsvOnePart)? PRESET_TABLE: SERVICE_TABLE);


    presetdat.PresetNumber = (mCurrentPresetIndex - 1);
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
    {
    	
        if(AnalogOrDigital != presetdat.Type)
        {
            /* this is done not to mix up Digital & Analog services */
            SortingNewPresetTypes = TRUE;
        }
    }

    if( (mCurrentPresetIndex == INVALID_PRESET) || mIsPresetOccupied(mCurrentPresetIndex) || (VALID_PRESET_RANGE(mCurrentPresetIndex) == FALSE)
            || (SortingNewPresetTypes == TRUE) )
    {
        if(NoOfRecs == 0)
        {
        	NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);
        	if(NoOfRecs == 0)
        	{
            	mCurrentPresetIndex = START_PRESET;
        	}
			else
			{
				if(pgdb_GetByIndex(PRESET_TABLE,0, (Address)&presetdat) == TRUE)
				{
					mCurrentPresetIndex = presetdat.PresetNumber + 1;
				}
			}
        }
        else
        {
            mCurrentPresetIndex = mPlaceNonHonouredOrAnalogServices(AnalogOrDigital);
        }   
    }
	
    TraceDebug(m,"%s %d mCurrentPresetIndex %d",__FUNCTION__, __LINE__, mCurrentPresetIndex);
}

inline int CHsvEuropeInstallation_msort_Priv::mPlaceNonHonouredOrAnalogServices(int AnalogOrDigital)
{
    int Retval = INVALID_PRESET, FromPreset = NON_HONOURED_START_PRESET;
    int ToPreset = NON_HONOURED_END_PRESET;
    HsvPgdatPresetData presetdat;

    if(AnalogOrDigital == HsvOnePart)
    {
        FromPreset = eurdiv_AutomaticDigitalPresetAllocation()? mLastLCNBasedPreset(): NON_HONOURED_START_PRESET;
    }
    else
    {
        if(eurdiv_AutomaticAnalogPresetAllocation())
        {
            if(pgdb_GetByIndex(PRESET_TABLE, 0, (Address)&presetdat) == TRUE)
            {
                if(presetdat.Type == HsvOnePart)
                {
                    FromPreset = presetdat.PresetNumber;
                }
            }

            if( (FromPreset%100) != 0)
            {
                FromPreset = (FromPreset + (100 - FromPreset%100)) + 1;
            }
        }
        else
        {
            FromPreset = ANALOG_STARTPRESET;
        }
    }

    Retval = mLargestGapInForwardRange(FromPreset, ToPreset);
    if(Retval == INVALID_PRESET)
    {
        TraceDebug(m,"%s %d mCurrentPresetIndex %d", __FUNCTION__, __LINE__, mCurrentPresetIndex);
        Retval = mLargestGapInForwardRange(START_PRESET, ToPreset);
    }

    return Retval;
}

inline int CHsvEuropeInstallation_msort_Priv::mLastLCNBasedPreset(void)
{
    int i = 0, retval = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatPresetData presetdata;
    HsvPgdatDigServiceData svcdat;

    for(i = 0; i < NoOfRecords; i++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdata))
        {
            if(presetdata.Type == HsvOnePart)
            {
                ASSIGN_SVC_FROM_PRESET(svcdat, presetdata);
                if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat))
                {
                    if( (VALID_LCN_RANGE(svcdat.LCN)) && (svcdat.LCN == svcdat.PresetNumber) )
                    {
                        retval = svcdat.PresetNumber;
                        break;
                    }
                }
            }
        }
    }

    return retval;
}

int CHsvEuropeInstallation_msort_Priv::mLargestGapInForwardRange(int FromPreset, int ToPreset)
{
    int i = 0, LargestPresetGap = 0, PreviousPreset = ToPreset, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);    
    HsvPgdatPresetData presetdat;
    int passval = 0;

    /* Below is the heart of the sorting module, beware of PRs before modifying it :) */
    if(NoOfRecs == 0)
    {
        TraceDebug(m,"%s:%d:FromPreset=%d",__FUNCTION__,__LINE__,FromPreset);
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
                    Retval = (Retval <= ToPreset)?Retval : INVALID_PRESET;
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



    TraceInfo(m,"%s %d Retval %d PreviousPreset %d presetdat.PresetNumber %d NoOfRecs %d LargestPresetGap %d", __FUNCTION__, __LINE__, Retval, PreviousPreset, presetdat.PresetNumber, NoOfRecs, LargestPresetGap);
    return Retval;
}

int CHsvEuropeInstallation_msort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
{
    int retval = 0;
    HsvPgdatDigServiceData pref_svcdata;

	REVALIDATE(svcdata->LCN);

    if(pgdb_GetByIndex(SERVICE_TABLE, pref_index, (Address)&pref_svcdata))
    {
		/* AN-29199. Had alignment with Pavan/Paul Meuleman. For Multiple ONID countries no need to sort based on 
			ascendig order of ONID. Order should be (1) ServiceType (2) LCN (3) Service name in alphabetical order
			(4) ServiceID */

		REVALIDATE(pref_svcdata.LCN);
		
        retval = (mGetServicePriority(pref_svcdata.ServiceType) - mGetServicePriority(svcdata->ServiceType));

        retval = (retval == 0)? (svcdata->LCN - pref_svcdata.LCN):retval;   

        retval = (retval == 0)? mStrCmp(svcdata->ChannelName, pref_svcdata.ChannelName):retval;

        retval = (retval == 0)? (svcdata->ServiceId - pref_svcdata.ServiceId):retval;
    }
    return retval;
}

int CHsvEuropeInstallation_msort_Priv::mStrCmp( Nat16 * str1, Nat16 * str2 )
{
   
    /*Above code is commented so as to keep same behaviour as euapp*/

    int ret;

    ASSERT( NULL != str1 ); /* Must not be the NULL pointer */
    ASSERT( NULL != str2 ); /* Must not be the NULL pointer */

    ret = *(Nat16 *)str1 - *(Nat16 *)str2;
    while( !ret && *str1 )
    {
        str1++;
        str2++;
        ret = *(Nat16 *)str1 - *(Nat16 *)str2;
    }
    return ret;
}   /* mStrCmp   */

int CHsvEuropeInstallation_msort_Priv::mGetServicePriority(int serviceType)
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

Bool CHsvEuropeInstallation_msort_Priv::mIsPresetOccupied(int PresetNumber)
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

void CHsvEuropeInstallation_msort_Priv::idvbtsortpow_Init()
{
    mdvbtsortPmp = pmp_PmpCreateEx( pen_PumpEngine, mDvbtSortHandler, FALSE, "hsveuins_mdvbtsort" );

    mFirstInstalledPreset = 0xFFFF;
    mCurrentPresetIndex = INVALID_PRESET;
}

void CHsvEuropeInstallation_msort_Priv::idvbtsortpow_TurnOn()
{

}

void CHsvEuropeInstallation_msort_Priv::idvbtsortpow_TurnOff()
{

}
void CHsvEuropeInstallation_msort_Priv::idvbtsort_Initialise(void)
{

    mCurrentPresetIndex = INVALID_PRESET;
	mFirstInstalledPreset = 0xFFFF;
}

void CHsvEuropeInstallation_msort_Priv::mSortPresetsOfStaticTable(int evCurrentSortStep)
{
    Nat16 *svclist = hsvdvbtins_inscountry_GetRankingList(sysset_GetSystemCountry());
    int to = -1, from = -1, i;
    int dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;

    if( (svclist != NULL) && (divsupp_StaticTable()) )
    {
        while( (*svclist != 0) )
        {
            HsvPgdatDigServiceData svcdat;

            svcdat.OriginalNetworkId   =   idvbtsort_GetOriginalNetworkId(sysset_GetSystemCountry());
            svcdat.ServiceId           =   *svclist;

            if(pgdb_GetRange( SERVICE_TABLE, 2, (Address) &svcdat, &from, &to))
            {
                for(i = from; i <= to; i++)
                {
                    if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat) == TRUE)
                    {
                        if(PRESET_NOT_ALLOCATED(svcdat))
                        {
                            mDigitalPresetEntryforInValidLCN(i);
                        }
                    }
                }
            }
            svclist++;
        }

        /* For Germany , the honored services from other country are not treated upto this point.
         * So to avoid the mixing of honored and non-honored services, first sort the remaining
         * honoured services, followed by non-honoured services for same country and then other countires */
        TraceDebug(m,"%s %d Sorting of Remaining services", __FUNCTION__, __LINE__);
        for( dbindex = 0; dbindex < noOfRecs; dbindex++)
        {
            if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
            {
                if( PRESET_NOT_ALLOCATED(svcdat) && VALID_LCN_RANGE(svcdat.LCN) )
                {
                    mDigitalPresetEntryforInValidLCN(dbindex);
                }
            }
            else
            {
                ASSERT(!" Who deleted the service here ");
            }
        }
    }

    TraceDebug(m,"Pmp send done with event = %d", (evCurrentSortStep + 1));
    pmp_PmpSend(mdvbtsortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

void CHsvEuropeInstallation_msort_Priv::idvbtsort_AddDigitalPreset (HsvPgdatDigServiceData *psvcdat)
{
    int dbindex = -1;
    Bool retval = FALSE;

    if(BACKGROUND_INSTALL)
    {
        TraceDebug(m,"%s %d LCN %d", __FUNCTION__, __LINE__, psvcdat->LCN);
        if(pgdb_GetIndex(SERVICE_TABLE, &dbindex, (Address)psvcdat))
        {
            if(VALID_LCN_RANGE(psvcdat->LCN))
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
        TraceNotice(m," @ %d This function call should not be made in installation mode other than manual mode", __LINE__);
        ASSERT(FALSE);
    }

}

void CHsvEuropeInstallation_msort_Priv::idvbtsort_AddAnalogPreset(Address adata)
{
    HsvPgdatAnalogData *panadat = (HsvPgdatAnalogData *)adata;

    if(UPDATE_INSTALL)
    {
        panadat->PresetNumber = mGetAutomaticPlatformPresetNumber();
        TraceDebug(m,"%s %d panadat->PresetNumber %d", __FUNCTION__, __LINE__, panadat->PresetNumber);
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

Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AutoStoreManualInstallationValues ()
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
    	TraceDebug(m,"Hsvprins %s %d mCurrentPresetIndex %d", __FUNCTION__, __LINE__,mCurrentPresetIndex);

        if( VALID_PRESET_RANGE(mCurrentPresetIndex) )
        {   
			pgdb_Initialise (pgdbconst_Analog, (Address) (&anadat));                
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
//          anadat.UserHidden = FALSE;
            anadat.ChannelLock = FALSE;
            anadat.PreferredStereo = 1;
			anadat.FavoriteNumber	= 0;
			anadat.UserModifiedLogo = 0;
			anadat.UserModifiedName = 0;
			anadat.LogoURL = 0;		
            pgdb_Add(ANALOG_TABLE,(Address)&anadat);
			TraceDebug(m,"Hsvprins %s %d ", __FUNCTION__, __LINE__);

            /* Store the Manual Installation Values */
            channel.Type = HsvAnalog;
            channel.Channel.AnalogNo = mCurrentPresetIndex;
	    	TraceDebug(m,"Hsvprins %s %d hsvprins_prins_StoreManualInstallationValues entered", __FUNCTION__, __LINE__);
		
            hsvprins_prins_StoreManualInstallationValues(channel);
    		TraceDebug(m,"Hsvprins %s %d ", __FUNCTION__, __LINE__);

            /* Fix me. Split this function. Move the unwanted to hsvprins */
            if(TRUE == pgdb_GetByKey(PRESET_TABLE, (Address)&newpresetdat))
            {
			    TraceDebug(m,"Hsvprins %s %d hsvprins_prins_StoreManualInstallationValues exited", __FUNCTION__, __LINE__);

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

int CHsvEuropeInstallation_msort_Priv::idvbtsort_GetNumberOfAnalogChannelsFound()      
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

void CHsvEuropeInstallation_msort_Priv::idvbtsort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;

    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);

    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)psvcdat))
    {
        presetdat.PresetNumber = psvcdat->PresetNumber;
        presetdat.Type = HsvOnePart;

        if(TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
        { 
            ASSIGN_PRESET_FROM_PSVC(presetdat,psvcdat);     
            pgdb_Update (PRESET_TABLE, (Address)&presetdat);

			
            mFirstInstalledPreset = ((mFirstInstalledPreset > presetdat.PresetNumber) && (psvcdat->VisibleService == TRUE)&&(psvcdat->SystemHidden == FALSE)) ? presetdat.PresetNumber: mFirstInstalledPreset;

            TraceDebug(m,"Updated Preset %d with new information from <%d,%d,%d,%d>", presetdat.PresetNumber,psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->StreamPriority, psvcdat->Frequency); 
        }
        else
        {
            TraceDebug(m,"%s %d",__FUNCTION__, __LINE__);
        }
    }      
}

int CHsvEuropeInstallation_msort_Priv::idvbtsort_GetOriginalNetworkId(int CurrentCountry)
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
            	TraceNotice(m,"it is Other Country");
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
                        ONWID   = 0xFFFF;
                    }
                }
                else
                {
                    /* No Transport Stream */
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
//  TraceDebug(m,"%s %d CurrentONID = %d", __FUNCTION__, __LINE__, ONWID);
    return (int )ONWID;
}

Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_IsPresetInstalled(Int32 frequency)
{
    Bool retval = FALSE;
	frequency = (frequency * 16)/1000;
	
    if((rins_InstallationModeUpdate == rins_GetInstallationMode())||(MANUAL_INSTALL))
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
                        if( presetdat.Frequency > (Nat32)frequency)
                        {
                            if(MIN_FREQUENCYDRIFT > (presetdat.Frequency - frequency))
                            {
                               	TraceNotice(m,"%s: %d index: %d presetdat.Frequency : %d frequency: %d",__FUNCTION__,__LINE__,i,presetdat.Frequency,frequency);
                                retval = TRUE;
                                break;
                            }
                        }
                        else
                        {
                            if(MIN_FREQUENCYDRIFT > (frequency - presetdat.Frequency))
                            {
                               	TraceNotice(m,"%s: %d index: %d presetdat.Frequency : %d frequency: %d",__FUNCTION__,__LINE__,i,presetdat.Frequency,frequency);
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

void CHsvEuropeInstallation_msort_Priv::idvbtsort_SortAll()
{
    TraceDebug(m,"%s %d mdvbtsortPmp %d", __FUNCTION__, __LINE__, mdvbtsortPmp);
    /* brg36mgr&nr=141377: For Germany the static table based sorting should be given 
     * first preference. So at first not checking for the honored services. So in case of
     * divsypp_StaticTable */
    if (!divsupp_StaticTable()) 
    {
        pmp_PmpSend(mdvbtsortPmp, evStep1, (Nat32)NULL);
    }
    else 
    {
        pmp_PmpSend(mdvbtsortPmp, evStep3, (Nat32)NULL);
    }
}

HsvChannel CHsvEuropeInstallation_msort_Priv::idvbtsort_GetInstalledWeakSignalChannel()
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceDebug(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

int CHsvEuropeInstallation_msort_Priv::mGetAutomaticPlatformPresetNumber(void)
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

Bool CHsvEuropeInstallation_msort_Priv::mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat)
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

    TraceDebug(m,"%s %d presetnum %d retval %d", __FUNCTION__, __LINE__, presetdat.PresetNumber, retval);
    return retval;
}

int CHsvEuropeInstallation_msort_Priv::mConvertToDVBServiceType(int servicetype)
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
/******** retval = FALSE: indicates retaining a multiplex - equivalent to selecting channel 1 *********/
/******** retval = TRUE : indicates replacing a multiplex - equivalent to selecting channel 2 *********/

Bool CHsvEuropeInstallation_msort_Priv::mCompareMultiplex(HsvPgdatDigTSData oldtsdata, HsvPgdatDigTSData tsdata)
{
    Bool retval     =   TRUE;    

    /* If the Two TSs are from the same Hierarchical Mux */
    if((oldtsdata.Frequency == tsdata.Frequency) && (oldtsdata.StreamPriority != tsdata.StreamPriority))
    {
        retval = TRUE;
        if((oldtsdata.QSignalStrength > 40) && (tsdata.QSignalStrength > 40))
        {
            /* Low Priority Stream is Selected */
            retval = FALSE;
        }
    }      
    else 
    {
        if(oldtsdata.QSignalStrength == tsdata.QSignalStrength)
        {
            retval = (tsdata.VSignalStrength > oldtsdata.VSignalStrength)? TRUE: FALSE;
        }
        else
        {       
            if(oldtsdata.QSignalStrength > tsdata.QSignalStrength)
            {
                if ( oldtsdata.VSignalStrength < tsdata.VSignalStrength )
                {
                    if((oldtsdata.QSignalStrength - tsdata.QSignalStrength) < DELTASQI )
                    {
                        retval = ((tsdata.VSignalStrength - oldtsdata.VSignalStrength ) > DELTASSI)? TRUE: FALSE;
                    }
                    else
                    {
                        retval = FALSE;
                    }
                }
                else
                {
                    retval = FALSE; //select A
                }
            } 
            else if( oldtsdata.VSignalStrength > tsdata.VSignalStrength )
            {
                if(( tsdata.QSignalStrength - oldtsdata.QSignalStrength ) < DELTASQI ) 
                {
                    retval = ((oldtsdata.VSignalStrength - tsdata.VSignalStrength) > DELTASSI )? FALSE: TRUE;
                }
                else
                {
                    retval = TRUE;
                }
            }
            else
            {
                retval = TRUE;
            }
        }
    } 
    return retval;
}

/*Stub */
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_msort_Priv::idvbtsort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_DeleteAllDigitalChannels()
{
	return 0;
}    
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_DeleteInvalidPTCTable()
{
	return 0;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_UpdatingLCNDuringUpdateInstallation()
{
	return 0;
}
Bool CHsvEuropeInstallation_msort_Priv::idvbtsort_AssignPresetsOfOtherCountries   (void)
{
	return 0;
}
void CHsvEuropeInstallation_msort_Priv::idvbtsort_RemoveDigitalPresets(void)
{
	return;
}
