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
 *          %name: hsvdvbsfransat_mSort.c %
 *       %version: TVG_1 %
 * %date_modified: %
 *    %derived_by: anuma %
 */

#include "_hsvdvbsfransat_mSort.h"

#include "fransatsort.h"

TRACESYMBOL(m, "s2/installation/hsvdvbsfransat/fransat_msort")
/****************************************************************************
 * Macros and types
 ****************************************************************************/

//todo delete this


int CHsvDvbsFransat_mSort_Priv::s__mCurrentRadioIndex = 0,CHsvDvbsFransat_mSort_Priv::s__mCurrentPresetIndex = 0;

Pump CHsvDvbsFransat_mSort_Priv::s__Sortingpmp;














/******************************************************/

/* provides IHsvPower isortpow */
void CHsvDvbsFransat_mSort_Priv::isortpow_Init()
{
	PrintfNotice ("Sort Pow Init being called \n");
	Sortingpmp = pmp_PmpCreateEx(pen_PumpEngine, SortingHandler, TRUE, "hsvdvbinsm7_msort");
}

void CHsvDvbsFransat_mSort_Priv::isortpow_TurnOn (void)
{

}

void CHsvDvbsFransat_mSort_Priv::isortpow_TurnOff (void)
{

}

/* provides IHsvSorting		isort */

void CHsvDvbsFransat_mSort_Priv::ifransatsort_Sort (Nat32 PackageIndex)
{
	int mode,state,retval;
	retval = rins_GetCurrentInstallationState (&mode, &state);
	TraceNotice(m,"Fransat Sorting started");

	if(mode == AUTO_MODE)
	{
		mCurrentRadioIndex = 0;
		mCurrentPresetIndex = 0;
	}

	iinsN_OnEvent(iinsN_EventSortingStarted, 0);
	pmp_PmpSend(Sortingpmp, SORT_HONOURED_SERVICES, 0);
}

void CHsvDvbsFransat_mSort_Priv::SortingHandler( int event, Nat32 startindex )
{
	TraceNotice(m,"event= %d startindex = %d ", event,(int) startindex);

	switch (event)
	{
		case SORT_HONOURED_SERVICES:
		{
			mSortHonouredServices(FALSE, startindex);
		}
		break;
		case SORT_HONOURED_RADIO_SERVICES:
		{
			mSortHonouredServices(TRUE, startindex);
		}
		break;
		case SORT_NONHONOURED_SERVICES:
			mSortNonHonouredServices(FALSE, startindex);
		break;
		case SORT_NONHONOURED_RADIO_SERVICES:
			mSortNonHonouredServices(TRUE, startindex);
		break;
		case SORT_COMPLETE:
			iinsN_OnEvent(iinsN_EventSortCompleted, 0);
		break;

		default:
			break;
	}
}

void CHsvDvbsFransat_mSort_Priv::mSortHonouredServices(Bool CheckForRadioServices, int startindex)
{
	HsvPgdatDigServiceData svcdat;
	int RecordIndex = 0;
	int NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	int NextIndex = 0;
	int LCNIndex = 0;
	int CurrentSortStep = ((CheckForRadioServices) ? SORT_HONOURED_RADIO_SERVICES:SORT_HONOURED_SERVICES);

	TraceNotice(m,"Number of service records %d Start index %d Sort Step %d ",NoOfRecs, startindex, CurrentSortStep);
	RecordIndex = startindex;
	for(; ((RecordIndex < startindex+STEP_SIZE) &&(RecordIndex < NoOfRecs)); RecordIndex++)
	{
		if(TRUE == pgdb_GetByIndex(SERVICE_TABLE, RecordIndex, (Address)&svcdat))
		{
			mRetriveZeroMultipleLCN(&svcdat);
			for(LCNIndex = 0; LCNIndex < MAX_NUM_LCN_ENTRY; LCNIndex++)
			{
				if((INVALID_LCN != svcdat.MultipleLCN[LCNIndex])
						&& (VALID_LCN_RANGE(svcdat.MultipleLCN[LCNIndex]))
						&& (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices))
				{
					if(PRESET_NOT_ALLOCATED(svcdat.MultiplePreset[LCNIndex]))
					{
						mDigitalPresetEntryforValidLCN(RecordIndex, LCNIndex);
					}
				}
			}
		}
		else
		{
			TraceErr(m,"Error: This should not be printed!!");
		}
	}

	TraceDebug(m,"Number of service records %d Rec index %d",NoOfRecs, RecordIndex);
	if(RecordIndex < NoOfRecs)
	{
		NextIndex = startindex+STEP_SIZE;
	}
	else
	{
		NextIndex =0;
		CurrentSortStep++;
	}
	TraceNotice(m,"Pmp send done with event = %d NextIndex = %d \n", CurrentSortStep,NextIndex);
	pmp_PmpSend(Sortingpmp, CurrentSortStep,NextIndex);
}


void CHsvDvbsFransat_mSort_Priv::mSortNonHonouredServices(Bool CheckForRadioServices, int startindex)
{
	HsvPgdatDigServiceData svcdat;
	int RecordIndex = 0, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	int NextIndex =0;
	int LCNIndex = 0;
	int CurrentSortStep = ((CheckForRadioServices) ? SORT_NONHONOURED_RADIO_SERVICES:SORT_NONHONOURED_SERVICES);
	RecordIndex = startindex;


	TraceDebug(m,"Number of service records %d Start index %d Sort step %d",NoOfRecs, startindex, CurrentSortStep);
	for(; (RecordIndex < startindex+STEP_SIZE) &&(RecordIndex < NoOfRecs); RecordIndex++)
	{
		if( pgdb_GetByIndex(SERVICE_TABLE, RecordIndex, (Address)&svcdat) == TRUE )
		{
			mRetriveZeroMultipleLCN(&svcdat);
			for(LCNIndex = 0; LCNIndex < MAX_NUM_LCN_ENTRY; LCNIndex++)
			{
				if((INVALID_LCN != svcdat.MultipleLCN[LCNIndex])
					&& (PRESET_NOT_ALLOCATED(svcdat.MultiplePreset[LCNIndex]))
					&& (!VALID_LCN_RANGE(svcdat.MultipleLCN[LCNIndex]))
					&& (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices) )
				{
					mDigitalPresetEntryforInValidLCN(RecordIndex, LCNIndex);
				}
			}
		}
	}

	TraceDebug(m," Number of service records %d Rec index %d",NoOfRecs, RecordIndex);
	if(RecordIndex < NoOfRecs)
	{
		NextIndex = startindex+STEP_SIZE;
	}
	else
	{
		NextIndex =0;
		CurrentSortStep++;
	}
	TraceNotice(m,"Pmp send done with event = %d NextIndex = %d \n", CurrentSortStep,NextIndex);
	pmp_PmpSend(Sortingpmp, CurrentSortStep,NextIndex);

}

void CHsvDvbsFransat_mSort_Priv::mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, int LCNIndex)
{
	HsvPgdatPresetData      presetdat;

	pgdb_Initialise (pgdbconst_Preset, (Address)&presetdat);

	svcdat->MultiplePreset[LCNIndex] = PresetNo;
	presetdat.PresetNumber = svcdat->MultiplePreset[LCNIndex];
    svcdat->PresetNumber = svcdat->MultiplePreset[0];

	presetdat.OriginalNetworkId = svcdat->OriginalNetworkId;
	presetdat.ServiceId = svcdat->ServiceId;
	presetdat.Tsid = svcdat->Tsid;
	presetdat.Tpid = svcdat->Tpid;
	presetdat.Frequency = svcdat->Frequency;
	presetdat.Polarization = svcdat->Polarization;
	presetdat.LnbNumber = svcdat->LnbNumber;
	presetdat.VisibleService = svcdat->VisibleService;
	//presetdat.SystemHidden = !svcdat->VisibleService[0];
	presetdat.NumericSelect = svcdat->NumericSelect;
	
	TraceDebug(m,"SID = %d PresetNo = %d ",presetdat.ServiceId,PresetNo);
	if(TRUE != pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
	{
		pgdb_Add(PRESET_TABLE, (Address)&presetdat);

		mStoreZeroMultipleLCN(svcdat);
		pgdb_Update(SERVICE_TABLE,(Address)svcdat);
		mRetriveZeroMultipleLCN(svcdat);
	}
	else
	{
		TraceErr(m,"!!Preset is already present in PRESET_TABLE\n");

	}
}

void CHsvDvbsFransat_mSort_Priv::mDigitalPresetEntryforValidLCN(int dbindex, int LCNIndex)
{
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;

    if( pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
    	mRetriveZeroMultipleLCN(&svcdat);
        REVALIDATE( svcdat.MultipleLCN[LCNIndex]);

        /* Check if LCN preset is occupied */
        presetdat.PresetNumber = svcdat.MultipleLCN[LCNIndex];
        if( pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) )
        {
		//preset is occupied   , service will get the preset number in non hon
		TraceNotice(m,"INVALIDATE SID = %d svcdat.LCN = %d ",svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
		INVALIDATE( svcdat.MultipleLCN[LCNIndex]);
		mStoreZeroMultipleLCN(&svcdat);
		pgdb_Update(SERVICE_TABLE,(Address)&svcdat);
		mRetriveZeroMultipleLCN(&svcdat);
        }
        else
        {
		     TraceDebug(m,"Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x",presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
            /* That preset is free. So just grab it */
            mAddEntryToPresetTable(&svcdat,  svcdat.MultipleLCN[LCNIndex], LCNIndex);
        }
    }
}

void CHsvDvbsFransat_mSort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex,  int LCNIndex)
{
    int FromPreset = 0, ToPreset = 0;
    int CurrentPresetIndex = 0;
    HsvPgdatDigServiceData svcdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
    	mRetriveZeroMultipleLCN(&svcdat);
	ToPreset =  (IS_RADIO_SERVICE(svcdat.ServiceType))?MAX_RADIO_PRESET:RADIO_PRESET_OFFSET;
	FromPreset  = (IS_RADIO_SERVICE(svcdat.ServiceType))?RADIO_PRESET_OFFSET:TV_PRESET_OFFSET;;

	CurrentPresetIndex = mGetPresetNoForService(svcdat, FromPreset, ToPreset);

        if(CurrentPresetIndex > 0)
        {
		mAddEntryToPresetTable(&svcdat, CurrentPresetIndex, LCNIndex);
		CurrentPresetIndex = CurrentPresetIndex + 1;
        }
    }
    else
    {
        TraceNotice(m,"%d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}

int CHsvDvbsFransat_mSort_Priv::mGetPresetNoForService(HsvPgdatDigServiceData svcdat, int FromPreset, int ToPreset)
{
    int CurrentPresetIndex = 0;
    HsvPgdatPresetData presetdat;

	CurrentPresetIndex  = GETCURRENTINDEX(svcdat.ServiceType);

	presetdat.PresetNumber = CurrentPresetIndex;

	if( (CurrentPresetIndex == 0) || pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat)
			|| (CurrentPresetIndex < FromPreset) || (CurrentPresetIndex > ToPreset) )
	{
		if( (CurrentPresetIndex = mFirstAvailableGapInPresetList(FromPreset, ToPreset)) == INVALID_PRESET)
		{
			//If we dont get any then start placing the service from MIXED_PRESET_OFFSET
			CurrentPresetIndex = mFirstAvailableGapInPresetList(MIXED_PRESET_OFFSET, MAX_PRESET_NUMBER);
		}
		TraceNotice(m,"%s:: %d CurrentPresetIndex = %d",__FUNCTION__, __LINE__, CurrentPresetIndex);
	}
    if(IS_RADIO_SERVICE(svcdat.ServiceType))
	{
		mCurrentRadioIndex = CurrentPresetIndex;
	}
	else
	{
		mCurrentPresetIndex = CurrentPresetIndex;
	}
	return CurrentPresetIndex;
}

int CHsvDvbsFransat_mSort_Priv::mFirstAvailableGapInPresetList(int FromPreset, int ToPreset)
{
	int RecordIndex = 0, PreviousPreset = FromPreset, Retval = INVALID_PRESET, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);

	HsvPgdatPresetData presetdat;

	if(NoOfRecs == 0)
	{
		Retval = FromPreset + 1;
	}

	else if(NoOfRecs == 1)
	{
		if(pgdb_GetByIndex( PRESET_TABLE, 0, (Address)&presetdat ) == TRUE)
		{
			Retval = ((presetdat.PresetNumber > FromPreset))? (presetdat.PresetNumber + 1) : (FromPreset + 1);
		}
		else
		{
			/* error condition should not occur */
			Retval = FromPreset + 1;
		}

	}
	else
	{
		presetdat.PresetNumber = (FromPreset + 1);
		if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE)
		{
			Retval = FromPreset + 1;
		}
		else
		{
			for(RecordIndex = (NoOfRecs - 1); RecordIndex >= 0; RecordIndex--)
			{
				pgdb_GetByIndex( PRESET_TABLE, RecordIndex, (Address)&presetdat );

				if(presetdat.PresetNumber <= FromPreset)
				{
					PreviousPreset = presetdat.PresetNumber;
					if(0 == RecordIndex)
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
					if(0 == RecordIndex)
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
		}
	}
	return Retval;
}
void CHsvDvbsFransat_mSort_Priv::mStoreZeroMultipleLCN(HsvPgdatDigServiceData *svcdat)
{
	int LoopCount = 0;
	
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		if(svcdat->MultipleLCN[LoopCount] == 0) {
			svcdat->MultipleLCN[LoopCount] = ZERO_VALUE_LCN;
		}
		TraceNotice(m,"[%s] [%d] MultipleLCN[%d] \n",__FUNCTION__,__LINE__,svcdat->MultipleLCN[LoopCount]);
	}
}
void CHsvDvbsFransat_mSort_Priv::mRetriveZeroMultipleLCN(HsvPgdatDigServiceData *svcdat)
{
	int LoopCount = 0;
	
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		if(svcdat->MultipleLCN[LoopCount] == ZERO_VALUE_LCN) {
			svcdat->MultipleLCN[LoopCount] = 0;
		}
		TraceNotice(m,"[%s] [%d] MultipleLCN[%d] \n",__FUNCTION__,__LINE__,svcdat->MultipleLCN[LoopCount]);
	}
}

