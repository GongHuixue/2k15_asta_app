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
 *          %name: hsveuins_mhungarysort.cpp %
 *       %version: TVG_MTK_15 %
 * %date_modified: Thur Jan 29 13:13:09 2015 %
 *    %derived_by: Bharat Singh Tanwar % 
 */


/****************************************************************************
 * Local include files
 ****************************************************************************/

#include "_hsveuins_mhungarysort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mhungarysort")






                                                      





/*****   GLOBAL VARIABLES   *****/
Pump CHsvEuropeInstallation_mhungarysort_Priv::s__mhungarysortPmp;

int CHsvEuropeInstallation_mhungarysort_Priv::s__mFirstInstalledPreset = 0xFFFF,CHsvEuropeInstallation_mhungarysort_Priv::s__mCurrentTvPreset = INVALID_PRESET,CHsvEuropeInstallation_mhungarysort_Priv::s__mCurrentRadioPreset = INVALID_PRESET;


/*****   Local Structures and enums   *****/


int CHsvEuropeInstallation_mhungarysort_Priv::s__mServicePriority[MAX_SERVICE_TYPES] =
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

void CHsvEuropeInstallation_mhungarysort_Priv::mHungarySortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s: CURRENT STEP = %d\r",__FUNCTION__, value);

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
        /* HD-SD SWAP */
        TraceDebug(m,"%s %d swap of HD & SD presets", __FUNCTION__, __LINE__);
        /* NON HONOURED PRESETS */
        TraceDebug(m,"%s %d Sorting of non honoured presets", __FUNCTION__, __LINE__);
        mSortNonHonouredServices(value, TRUE);
        break;
	case evStep3:
        /* NON HONOURED PRESETS */
        TraceDebug(m,"%s %d Sorting of non honoured other country presets", __FUNCTION__, __LINE__);
        mSortNonHonouredServices(value, FALSE);
        break;
	case evStep4:
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

void CHsvEuropeInstallation_mhungarysort_Priv::mNoSorting(int evCurrentSortStep)
{
    int dbindex = 0, noOfDigRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    int noOfAnaRecs = pgdb_GetNoRecords(ANALOG_TABLE);
    int noOfPresetRecs = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatDigServiceData svcdat;

    TraceNotice(m,"%s: D %d A %d\r\n",__FUNCTION__, noOfDigRecs, noOfAnaRecs);

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
                (idvbthungarysort_IsPresetInstalled(anadat.Frequency) == FALSE) )
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
                TraceDebug(m,"%d Ignoring Preset assignment for frequency %ld as Tuned bit is not set\n", __LINE__, anadat.Frequency);
            }
        }
        else
        {
            TraceDebug(m,"%d Analog data suddenly deleted from database\n", __LINE__);
            ASSERT(!"Analog data suddenly deleted from database");
        }
    }

    if(mCurrentTvPreset > mFirstInstalledPreset)
    	mFirstInstalledPreset++;

    pmp_PmpSend(mhungarysortPmp, evStepComplete, (Nat32)NULL);
}

void CHsvEuropeInstallation_mhungarysort_Priv::mSortHonouredServices(int evCurrentSortStep)
{
    int dbindex = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    int from = 0, to = 0;
    Bool retval = TRUE;
    
    TraceDebug(m,"%s %d Sorting of Honoured services", __FUNCTION__, __LINE__);
    
    to = noOfRecs - 1;
    
    /*div_SupportMultipleOriginalNetworkId --> Not supported*/
    svcdat.OriginalNetworkId =   idvbthungarysort_GetOriginalNetworkId(sysset_GetSystemCountry());
    retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);    
        
	TraceNotice (m, "Sorting Honored Services. From %d To %d ", from, to);
    for(dbindex = from; (dbindex <= to) && retval; dbindex++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE)
        {
			
                TraceDebug(m,"%s %d Sorting of Honoured services :: dbindex %d svcdat.LCN %d", __FUNCTION__, __LINE__, dbindex, svcdat.LCN);
			mDigitalPresetEntryforValidLCN(&svcdat);			
			
		}
        else
        {
            ASSERT(!" Who deleted the service here ");
        }
    }

    TraceDebug(m,"Pmp send done with event = %d\r", (evCurrentSortStep + 1));
    pmp_PmpSend(mhungarysortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}


Bool CHsvEuropeInstallation_mhungarysort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
	Bool retval = FALSE;
	int  presetnum = -1;
	Nat8 i=0;
	if( PRESET_NOT_ALLOCATED(svcdat->PresetNumber) && VALID_LCN_RANGE(svcdat->LCN))
		{
			
			presetnum = ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType);
			TraceNotice (m, "PresetNumber allocated %d LCN %d", presetnum, svcdat->LCN);
			if( mIsPresetOccupied(presetnum) == FALSE )
			{
				mAddOrUpdateEntryToPresetTable(svcdat, presetnum, ADD_ENTRY);
				retval = TRUE;
			}
			else
			{
				retval = mUpdateDigitalPresetEntryforValidLCN(svcdat);
			}
		}
	return retval;
}

Bool CHsvEuropeInstallation_mhungarysort_Priv::mUpdateDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
	Bool retval = FALSE, CanBeReplaced = (div_UpdateLCN(rins_GetMedium()) || (MANUAL_INSTALL))?TRUE:FALSE;
	HsvPgdatPresetData presetdat;
       
	HsvPgdatDigTSData oldtsdat, tsdata;
	Nat8 k =0;
	
    presetdat.PresetNumber = ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType);
    if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
	{
		if( mServiceIsOfPreviousPass(presetdat) == TRUE)
		{                        
            if(CanBeReplaced )
            {                
                retval = TRUE;            
			}
            else if (!MANUAL_INSTALL)
            {
                INVALIDATE(svcdat->LCN); 
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
			INVALIDATE(svcdat->LCN);
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
						oldtsdat.Frequency			=	oldsvcdat.Frequency;
						oldtsdat.StreamPriority		=   oldsvcdat.StreamPriority;

						tsdata.Frequency	        =	svcdat->Frequency;
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
					if(presetdat.PresetNumber == oldsvcdat.PresetNumber)
					{
						INVALIDATE(oldsvcdat.LCN);
						oldsvcdat.PresetNumber = INVALID_PRESET;
					}
					pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);
                }
				
				mAddOrUpdateEntryToPresetTable(svcdat, ASSIGN_PRESET_NUMBER(svcdat->LCN, svcdat->ServiceType), UPDATE_ENTRY);
				retval = TRUE;
			}
			else 
			{
				//invalidate the LCN of the service which lost the battle
				INVALIDATE(svcdat->LCN); 
				pgdb_Update(SERVICE_TABLE, (Address)svcdat);
			}
			}
		}
	}
	
	return retval;
}

void CHsvEuropeInstallation_mhungarysort_Priv::mSortNonHonouredServices(int evCurrentSortStep, Bool CheckForCurrentOnId)
{
    int i = 0, from = 0, to, pref_dbindex = -1, dbindex = 0;
    HsvPgdatDigServiceData svcdat;
    Bool retval = TRUE, pref_index_found = TRUE;
    
    to = pgdb_GetNoRecords(SERVICE_TABLE) - 1;
	TraceNotice (m, " sortNon honored From %d To %d ", from , to);
    if( CheckForCurrentOnId )
    {
        svcdat.OriginalNetworkId =   idvbthungarysort_GetOriginalNetworkId(sysset_GetSystemCountry());
        retval = pgdb_GetRange (SERVICE_TABLE, 1, (Address)&svcdat, &from, &to);
		TraceNotice (m, "sortNon honored ONID From %d To %d ", from , to);
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
			     if( mPresetAllocated(&svcdat)==FALSE) /* && (!VALID_LCN_RANGE(svcdat.LCN)) */
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
			TraceNotice (m, "ANEESH: Preferred DBIndex is %d ", pref_dbindex);
			mDigitalPresetEntryforInValidLCN(pref_dbindex);
		}
	}
	
    TraceDebug(m,"Pmp send done with event = %d\r", evCurrentSortStep + 1);
	pmp_PmpSend(mhungarysortPmp, evCurrentSortStep + 1, (Nat32)NULL);
}

Bool CHsvEuropeInstallation_mhungarysort_Priv::mPresetAllocated(HsvPgdatDigServiceData *svcdat) 
{
	Bool retval = FALSE;
	Nat8 i =0;
	if ( (svcdat->PresetNumber != INVALID_PRESET) && (svcdat->PresetNumber != 0xFFFD) )
	{
		retval = TRUE;
	}

	return retval;
}
void CHsvEuropeInstallation_mhungarysort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex)
{
    int CurrentPreset;
    HsvPgdatDigServiceData svcdat;
   
    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
        mFindPresetNumberForService(HsvOnePart,svcdat.ServiceType);
        
        if(IS_RADIO_SERVICE(svcdat.ServiceType))
        {
            CurrentPreset = mCurrentRadioPreset;
        }
        else
        {
            CurrentPreset = mCurrentTvPreset;
        }
        
        if(VALID_PRESET_RANGE(CurrentPreset))
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
    else
    {
        TraceNotice(m,"@ %d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}

void CHsvEuropeInstallation_mhungarysort_Priv::mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate)
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

    mFirstInstalledPreset  = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;
    
    if(svcdat->NewPreset)
    {
        sortN_OnEvent(sortN_EventNewPresetFound, rins_GetInstallationMode());
    }
}

void CHsvEuropeInstallation_mhungarysort_Priv::mSortAnalogServices(int evCurrentSortStep)
{
    int i, noOfRecs = pgdb_GetNoRecords(ANALOG_TABLE), digservices = pgdb_GetNoRecords(SERVICE_TABLE);
    
    HsvPgdatAnalogData anadat;
    HsvPgdatPresetData presetdat;
    
    TraceDebug(m,"%s %d noOfRecs: %d", __FUNCTION__, __LINE__, noOfRecs);

    for(i = (noOfRecs - 1); i >= 0; i--)
    {   
        if(pgdb_GetByIndex(ANALOG_TABLE, i, (Address)&anadat))
        {
            /* Only for installed analog presets, 2nd check is to check if this a new service are previously installed one */
            if( (TRUE == anadat.Tuned) && 
                (idvbthungarysort_IsPresetInstalled(anadat.Frequency) == FALSE) )
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
                    mFindPresetNumberForService(HsvAnalog,SERVICE_TYPE_NONE);
                    presetdat.PresetNumber = mCurrentTvPreset;
                }
                presetdat.AnalogTablePreset = anadat.PresetNumber;

                if( VALID_PRESET_RANGE(presetdat.PresetNumber) )
                {
                    presetdat.Type = HsvAnalog;
                    presetdat.Frequency = anadat.Frequency;
                    
                    ASSIGN_DEFAULTCOOKIES(anadat);
					presetdat.UniqueNodeId  = -1;// Invalid Node id 
                    pgdb_Add(PRESET_TABLE,(Address) &presetdat);
                    pgdb_Update(ANALOG_TABLE,(Address) &anadat);
                    
                    mCurrentTvPreset++;
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

    TraceDebug(m,"Pmp send done with event = %d\r", evCurrentSortStep + 1);
    pmp_PmpSend(mhungarysortPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

/* Based on service type updates the static variable maintained for CURRENT_PRESET */
inline void CHsvEuropeInstallation_mhungarysort_Priv::mFindPresetNumberForService(int AnalogOrDigital,int ServiceType)
{
    int CurrentPreset = INVALID_PRESET;
    HsvPgdatPresetData presetdat;
    
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
        presetdat.PresetNumber = (mCurrentTvPreset - 1);
        if( (TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat) ))
        {
            if(presetdat.Type == HsvAnalog)
            {
                CurrentPreset = mCurrentTvPreset;
            }
        }
    }
    if( mIsCurrentPresetInvalid(CurrentPreset, ServiceType) )
    {       
        mPlaceNonHonouredOrAnalogServices(AnalogOrDigital,ServiceType);     
    }
	TraceNotice(m,"%s,%d,%d",__FUNCTION__,__LINE__,mCurrentRadioPreset);
}

inline int CHsvEuropeInstallation_mhungarysort_Priv::mPlaceNonHonouredOrAnalogServices(int AnalogOrDigital,int ServiceType)
{
    int Retval = INVALID_PRESET, FromPreset = NON_HONOURED_START_PRESET;
    int ToPreset = div_MaxValidLCNValue;
    UNUSED(AnalogOrDigital);
    
    mGetPresetRangeForService(ServiceType, &FromPreset, &ToPreset);
    mReInnovateFromPreset(ServiceType, &FromPreset);
    if(IS_RADIO_SERVICE(ServiceType))
    {
        mCurrentRadioPreset = mLargestGapInForwardRange(FromPreset, ToPreset);
    }
    else
    {
        mCurrentTvPreset = mLargestGapInForwardRange(FromPreset, ToPreset);
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

    return Retval;
}
void CHsvEuropeInstallation_mhungarysort_Priv::mReInnovateFromPreset(int ServiceType, int *FromPreset)
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

inline int CHsvEuropeInstallation_mhungarysort_Priv::mLastLCNBasedPreset(Bool CheckForRadioServices)
{
    int i = 0, j = 0, retval = INVALID_PRESET, NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);
    HsvPgdatPresetData presetdata;
    HsvPgdatDigServiceData svcdat;
	Bool	proceed = TRUE;

    for(i = 0; i < NoOfRecords; i++)
    {
        if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdata))
        {
            if(presetdata.Type == HsvOnePart)
            {
				TraceNotice(m, "i %d presetdata.PresetNumber %d", i, presetdata.PresetNumber);
                ASSIGN_SVC_FROM_PRESET(svcdat, presetdata);
                if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat))
                {
                    if(IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices)
                    {
						if( (VALID_LCN_RANGE(svcdat.PresetNumber)) && 
							(ASSIGN_PRESET_NUMBER(svcdat.PresetNumber, svcdat.ServiceType) == svcdat.PresetNumber) && 
							(presetdata.PresetNumber == svcdat.PresetNumber) )
						{
							retval = svcdat.PresetNumber;
							proceed = FALSE;
							break;
						}
						if((proceed == FALSE))
						{
							TraceNotice(m, "svcdat.MultiplePreset[%d] %d svcdat.MultipleLCN[%d] %d", j, svcdat.MultiplePreset[j], j, svcdat.MultipleLCN[j]);
							break;
						}
                    }
                }
            }
        }
    }
	TraceNotice(m, "%s %d retval %d\n", __FUNCTION__, __LINE__, retval);

    return retval;
}

int CHsvEuropeInstallation_mhungarysort_Priv::mLargestGapInForwardRange(int FromPreset, int ToPreset)
{
    int i = 0, LargestPresetGap = 1, PreviousPreset = ToPreset, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);    
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
                Retval = ((PreviousPreset + 1) < FromPreset)? FromPreset : (PreviousPreset + 1);
            }
            break;
        }
    }
    TraceDebug(m,"%s %d Retval %d PreviousPreset %d presetdat.PresetNumber %d NoOfRecs %d LargestPresetGap %d", __FUNCTION__, __LINE__, Retval, PreviousPreset, presetdat.PresetNumber, NoOfRecs, LargestPresetGap);
    return Retval;
}

int CHsvEuropeInstallation_mhungarysort_Priv::mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index)
{
    int retval = 0;
    HsvPgdatDigServiceData pref_svcdata;

    if(pgdb_GetByIndex(SERVICE_TABLE, pref_index, (Address)&pref_svcdata))
    {
        retval = (svcdata->OriginalNetworkId - pref_svcdata.OriginalNetworkId);
        retval = (retval == 0)? (mGetServicePriority(pref_svcdata.ServiceType) - mGetServicePriority(svcdata->ServiceType)) : retval;
    
		retval = (retval == 0)? (svcdata->LCN - pref_svcdata.LCN):retval;   
        
        retval = (retval == 0)? mStrCmp(svcdata->ChannelName, pref_svcdata.ChannelName):retval;
        
        retval = (retval == 0)? (svcdata->ServiceId - pref_svcdata.ServiceId):retval;
    }
    return retval;

}

int CHsvEuropeInstallation_mhungarysort_Priv::mStrCmp( Nat16 * str1, Nat16 * str2 )
{
    /*int ret = 0;
    
    ASSERT( NULL != str1 ); 
    ASSERT( NULL != str2 ); 

    while( !ret && (*str1 || *str2) )
    {
        ret = toupper(*str1) - toupper(*str2);
        str1++, str2++;
    }

    return ret;*/

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

int CHsvEuropeInstallation_mhungarysort_Priv::mGetServicePriority(int serviceType)
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

Bool CHsvEuropeInstallation_mhungarysort_Priv::mIsPresetOccupied(int PresetNumber)
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

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysortpow_Init()
{
    mhungarysortPmp = pmp_PmpCreateEx( pen_PumpEngine, mHungarySortHandler, FALSE, "hsveuins_mhungarysort" );
    
    mFirstInstalledPreset = 0xFFFF;
    
}

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysortpow_TurnOn()
{

}

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysortpow_TurnOff()
{

}
void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_Initialise(void)
{
    if(AUTO_INSTALL)
    {
        mCurrentTvPreset = mCurrentRadioPreset  = INVALID_PRESET;
    }
    mFirstInstalledPreset = 0xFFFF;
}

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AddDigitalPreset (HsvPgdatDigServiceData *psvcdat)
{
    int dbindex = -1;
    Bool retval = FALSE;

    if(BACKGROUND_INSTALL)
    {
        TraceDebug(m,"%s %d LCN %d", __FUNCTION__, __LINE__, psvcdat->LCN);
        if(pgdb_GetIndex(SERVICE_TABLE, &dbindex, (Address)psvcdat))
        {
			if(mValidLCN(psvcdat))
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
Bool CHsvEuropeInstallation_mhungarysort_Priv::mValidLCN(HsvPgdatDigServiceData *psvcdat)
{
	Bool retval = FALSE;
	if(VALID_LCN_RANGE(psvcdat->LCN))
	{
		retval = TRUE;
	}
	return retval;
}

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AddAnalogPreset(Address adata)
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
 //   panadat->Favorite = 0;
//    panadat->UserHidden = 0;
    panadat->PreferredStereo = 1;
    panadat->FavoriteNumber	= 0;
	panadat->UserModifiedLogo = 0;
	panadat->UserModifiedName = 0;
	panadat->LogoURL = 0;

    pgdb_Add (ANALOG_TABLE, (Address)adata);
}

Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AutoStoreManualInstallationValues ()
{   
    Bool retval = FALSE;
    HsvPgdatPresetData newpresetdat;
    HsvPgdatAnalogData    anadat;
    HsvChannel channel;
    int plfpreset = mGetAutomaticPlatformPresetNumber();
    int CurrentPreset = INVALID_PRESET;
    
	pgdb_Initialise (pgdbconst_Preset,  &newpresetdat);   
	
    if(pgdb_GetNoRecords(ANALOG_TABLE) < div_MaxAnalogPresets )
    {
        mFindPresetNumberForService(HsvAnalog,SERVICE_TYPE_NONE);
        if(IS_RADIO_SERVICE(SERVICE_TYPE_NONE))
        {
            CurrentPreset = mCurrentRadioPreset;
        }
        else
        {
            CurrentPreset = mCurrentTvPreset;
        }
        
        if( mValidPresetForService(CurrentPreset,SERVICE_TYPE_NONE))
        {   
            /* Create a User Table entry */
            newpresetdat.PresetNumber = CURRENT_PRESET(SERVICE_TYPE_NONE);
            newpresetdat.AnalogTablePreset = plfpreset;
            newpresetdat.Type = HsvAnalog;
                  
            ASSIGN_DEFAULTCOOKIES(anadat);
            
			newpresetdat.UniqueNodeId  = -1;// Invalid Node id 
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
            channel.Channel.AnalogNo = CURRENT_PRESET(SERVICE_TYPE_NONE);
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

            mCurrentTvPreset++;
            retval = TRUE;
        }
    }
    return retval;
    

}

int CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_GetNumberOfAnalogChannelsFound()      
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

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;
	Nat8 i=0;

    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    
    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)psvcdat))
    {
		presetdat.PresetNumber = psvcdat->PresetNumber;
		presetdat.Type = HsvOnePart;
		
		if(TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
		{ 
			ASSIGN_PRESET_FROM_PSVC(presetdat,psvcdat); 	
			pgdb_Update (PRESET_TABLE, (Address)&presetdat);
			
			mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;
			
        TraceDebug(m,"Updated Preset %d with new information from <%d,%d,%d,%d>", presetdat.PresetNumber,psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->StreamPriority, psvcdat->Frequency); 
		}
		else
		{
        TraceDebug(m,"%s %d",__FUNCTION__, __LINE__);
		}
    }      
}

int CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_GetOriginalNetworkId(int CurrentCountry)
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
    TraceDebug(m,"%s %d CurrentONID = %d", __FUNCTION__, __LINE__, ONWID);
    return (int )ONWID;
}

Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_IsPresetInstalled(Int32 frequency)
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

void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_SortAll()
{
    TraceDebug(m,"%s %d mhungarysortPmp %d", __FUNCTION__, __LINE__, mhungarysortPmp);  
    pmp_PmpSend(mhungarysortPmp, evStep1, (Nat32)NULL); 
}

HsvChannel CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_GetInstalledWeakSignalChannel()
{
    HsvChannel channel;

    channel.Type = HsvOnePart;
    channel.Channel.OnePart = mFirstInstalledPreset;
    TraceDebug(m,"%s %d FirstInstalledPreset %d", __FUNCTION__, __LINE__, mFirstInstalledPreset);
    return channel;
}

int CHsvEuropeInstallation_mhungarysort_Priv::mGetAutomaticPlatformPresetNumber(void)
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

Bool CHsvEuropeInstallation_mhungarysort_Priv::mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat)
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

int CHsvEuropeInstallation_mhungarysort_Priv::mConvertToDVBServiceType(int servicetype)
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
/******** retval = FALSE: indicates retaining a multiplex - equivalent to selecting channel 1 *********/
/******** retval = TRUE : indicates replacing a multiplex - equivalent to selecting channel 2 *********/

Bool CHsvEuropeInstallation_mhungarysort_Priv::mCompareMultiplex(HsvPgdatDigTSData oldtsdata, HsvPgdatDigTSData tsdata)
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

Bool CHsvEuropeInstallation_mhungarysort_Priv::mIsCurrentPresetInvalid( int PresetNo, int ServiceType)
{
    HsvPgdatPresetData presetdata;

    presetdata.PresetNumber = PresetNo;
    return ( (PresetNo == INVALID_PRESET) || pgdb_GetByKey(PRESET_TABLE, (Address)&presetdata)
             || (!mValidPresetForService(PresetNo, ServiceType)) );
}


Bool CHsvEuropeInstallation_mhungarysort_Priv::mValidPresetForService(int presetnum, int svcType)
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
/* inline functions to get Start presets based on presetgroups (ANALOG, TV, RADIO) */

int CHsvEuropeInstallation_mhungarysort_Priv::mAnalogStartPreset(void)
{
    int retval, LastLCNPreset = mLastLCNBasedPreset(FALSE);

    retval = ((LastLCNPreset != INVALID_PRESET) && (LastLCNPreset < NONRADIO_ENDPRESET))? (LastLCNPreset + 1) : INVALID_PRESET;


    /* In case of No LCN services or FixedPresetRange is enabled based on country & medium */
    if( (eurdiv_AutomaticAnalogPresetAllocation() == FALSE) || (retval == INVALID_PRESET) )
    {
        retval = eurdiv_AnalogStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE) );
    }

    return retval;
}

int CHsvEuropeInstallation_mhungarysort_Priv::mNonRadioStartPreset(void)
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

int CHsvEuropeInstallation_mhungarysort_Priv::mRadioStartPreset(void)
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

void CHsvEuropeInstallation_mhungarysort_Priv::mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset)
{
    *startpreset  = mNonRadioStartPreset();
    *endpreset    = NONRADIO_ENDPRESET;
    
    if( IS_DIGITAL_SERVICE(svcType) )
    {
        if( IS_RADIO_SERVICE(svcType) )
        {
            *startpreset = mRadioStartPreset();
            *endpreset   = RADIO_ENDPRESET;
        }
    }
    else
    {
        *startpreset = mAnalogStartPreset();
        *endpreset   = ANALOG_ENDPRESET;
    }
    
    TraceDebug(m,"%s %d PRESET RANGE <=> (%d - %d) for ServiceType %d", __FUNCTION__, __LINE__, *startpreset, *endpreset, svcType);
}


/*Stub */
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid, int *FillHoles)
{
	return 0;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AnalogPresetEntry(void)
{
	return 0;
}
void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AssignPresetsForCountry(int ONID)
{
	return;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_DeleteAllDigitalChannels()
{
	return 0;
}    
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_DeleteInvalidPTCTable()
{
	return 0;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AssignPresetsForCurrentCountry  (int CurrentOnwid, Bool CheckLCN)
{
	return 0;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)
{
	return 0;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AssignPresetsWithStaticTable ( int CurrentOnwid, int Country )
{
	return 0;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_UpdatingLCNDuringUpdateInstallation()
{
	return 0;
}
Bool CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_AssignPresetsOfOtherCountries   (void)
{
	return 0;
}
void CHsvEuropeInstallation_mhungarysort_Priv::idvbthungarysort_RemoveDigitalPresets(void)
{
	return;
}
