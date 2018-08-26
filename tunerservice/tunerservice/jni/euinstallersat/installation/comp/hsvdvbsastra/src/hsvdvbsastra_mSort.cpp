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
 *          %name: hsvdvbsastra_mSort.c %
 *       %version:  TVG_4 %
 * %date_modified:  %
 *    %derived_by:  shreeshav % 
 */

#include "astrasort.h"
#include "CHsvDvbsAstra_mSort.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbsastra_msort")
/****************************************************************************
 * Macros and types
 ****************************************************************************/

typedef enum
{
	SORT_HONOURED_SERVICES = 0,
	SORT_HONOURED_RADIO_SERVICES,
	SORT_NONHONOURED_SERVICES,
	SORT_NONHONOURED_RADIO_SERVICES,
	SORT_COMPLETE
}SORTING_HANDLER_ENUM;




int CHsvDvbsAstra_mSort::s__mCurrentRadioIndex = 0,CHsvDvbsAstra_mSort::s__mCurrentPresetIndex = 0;

Pump CHsvDvbsAstra_mSort::s__Sortingpmp;

int CHsvDvbsAstra_mSort::s__SvcPriority[ASTRA_NUM_OF_PRIORITY] = {AppApiAdvCodecHDTelevisionService,\
											AppApiAdvCodecSDTelevisionService,\
											AppApiTelevisionService};



/******************************************************/

/* provides IHsvPower isortpow */
void CHsvDvbsAstra_mSort::Init()
{
	PrintfNotice ("Sort Pow Init being called \n");
	Sortingpmp = pmp_PmpCreateEx(pen_PumpEngine, SortingHandler, TRUE, "hsvdvbinsastra_msort");   
}

void CHsvDvbsAstra_mSort::TurnOn (void)
{

}

void CHsvDvbsAstra_mSort::TurnOff (void)
{

}

/* provides IHsvSorting		isort */

void CHsvDvbsAstra_mSort::Sort (Nat32 PackageIndex)
{
	int mode,state,retval;
	retval = rins_GetCurrentInstallationState (&mode, &state); 
	TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);
	
	if(mode == AUTO_MODE)
	{
		mCurrentRadioIndex = 0;
		mCurrentPresetIndex = 0;
	}
	
	iinsN_OnEvent(iinsN_EventSortingStarted, 0);
	pmp_PmpSend(Sortingpmp, SORT_HONOURED_SERVICES, 0);
}

void CHsvDvbsAstra_mSort::SortingHandler( int event, Nat32 startindex )
{
	TraceNotice(m,"  event= %d startindex = %d ", event,(int) startindex);

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

void CHsvDvbsAstra_mSort::mSortHonouredServices(Bool CheckForRadioServices, int startindex)
{
    HsvPgdatDigServiceData svcdat;
    int i = 0, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	int nextindex =0;
	int LCNIndex = 0;
	int CurrentSortStep = (CheckForRadioServices?SORT_HONOURED_RADIO_SERVICES:SORT_HONOURED_SERVICES);
    i = startindex;
	for(; (i< startindex+STEP_SIZE) &&(i < NoOfRecs); i++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat) == TRUE )
        {
        
		for(LCNIndex = 0; LCNIndex < MAX_NUM_LCN_ENTRY; LCNIndex++)
		{
            if( (INVALID_LCN != svcdat.MultipleLCN[LCNIndex]) && VALID_LCN_RANGE(svcdat.MultipleLCN[LCNIndex]) && (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices) )
            {               
                if(PRESET_NOT_ALLOCATED(svcdat.MultiplePreset[LCNIndex]))
                {
                    mDigitalPresetEntryforValidLCN(i,LCNIndex);                   
                }
				else
				{
				}
			}
			else
			{
			}
		}
		}
		else
		{
				TraceErr(m,"Error: This should not be printed!!");
		}
	}
	if(i<NoOfRecs)
	{
		nextindex = startindex+STEP_SIZE;
	}
	else
	{	
		nextindex =0;	
		CurrentSortStep++;
	}
	TraceNotice(m,"Pmp send done with event = %d nextindex = %d \n", CurrentSortStep,nextindex);
	pmp_PmpSend(Sortingpmp, CurrentSortStep,nextindex);
	
}


void CHsvDvbsAstra_mSort::mSortNonHonouredServices(Bool CheckForRadioServices, int startindex)
{
    HsvPgdatDigServiceData svcdat;
    int i = 0, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	int nextindex =0;
	int LCNIndex = 0;
	int CurrentSortStep = (CheckForRadioServices?SORT_NONHONOURED_RADIO_SERVICES:SORT_NONHONOURED_SERVICES);
    i = startindex;
	for(; (i< startindex+STEP_SIZE) &&(i < NoOfRecs); i++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat) == TRUE )
        {
			for(LCNIndex = 0; LCNIndex < MAX_NUM_LCN_ENTRY; LCNIndex++)
			{
				if((INVALID_LCN != svcdat.MultipleLCN[LCNIndex])
					&& (PRESET_NOT_ALLOCATED(svcdat.MultiplePreset[LCNIndex]))
					&& (!VALID_LCN_RANGE(svcdat.MultipleLCN[LCNIndex]))
					&& (IS_RADIO_SERVICE(svcdat.ServiceType) == CheckForRadioServices) )
				{
					mDigitalPresetEntryforInValidLCN(i, LCNIndex);
				}
			}
		}
	}
	if(i<NoOfRecs)
	{
		nextindex = startindex+STEP_SIZE;
	}
	else
	{	
		nextindex =0;	
		CurrentSortStep++;
	}
	TraceNotice(m,"Pmp send done with event = %d\r\n", CurrentSortStep);
	pmp_PmpSend(Sortingpmp, CurrentSortStep,nextindex);
	
}

void CHsvDvbsAstra_mSort::mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, int LCNIndex)
{
	HsvPgdatPresetData      presetdat;

	pgdb_Initialise (pgdbconst_Preset, (Address)&presetdat);
	
	svcdat->MultiplePreset[LCNIndex] = PresetNo;
	presetdat.PresetNumber = 	svcdat->MultiplePreset[LCNIndex];

	presetdat.OriginalNetworkId = svcdat->OriginalNetworkId;
    presetdat.ServiceId = svcdat->ServiceId;
    presetdat.Tsid = svcdat->Tsid;
    presetdat.Tpid = svcdat->Tpid;
    presetdat.Frequency = svcdat->Frequency;
	presetdat.Polarization = svcdat->Polarization;
	presetdat.LnbNumber = svcdat->LnbNumber;
	TraceNotice(m,"SID = %d PresetNo = %d ",presetdat.ServiceId,PresetNo);
	if(TRUE != pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
	{
		pgdb_Add(PRESET_TABLE, (Address)&presetdat);

		pgdb_Update(SERVICE_TABLE,(Address)svcdat);
	}
	else
	{
		TraceErr(m,"!!Preset is already present in PRESET_TABLE\n");

	}
}


void CHsvDvbsAstra_mSort::mDigitalPresetEntryforValidLCN(int dbindex,int LCNIndex)
{
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;

    if( pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
        REVALIDATE(svcdat.MultipleLCN[LCNIndex]);

        /* Check if LCN preset is occupied */
        presetdat.PresetNumber = svcdat.MultipleLCN[LCNIndex];
        if( pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) )
        {           
			
			HsvPgdatDigServiceData OldSvcdat;	
			OldSvcdat.Tpid 		= presetdat.Tpid;
			OldSvcdat.ServiceId 	= presetdat.ServiceId;

			 pgdb_GetByKey(SERVICE_TABLE, (Address)&OldSvcdat);


			if(mPriorityCheck(OldSvcdat.ServiceType, svcdat.ServiceType))
			{
				//Invalidate old service LCN and update the old service entry in service table
				TraceNotice(m,"Invalidating the LCN %d, OldSvcId: %d",OldSvcdat.MultipleLCN[LCNIndex],OldSvcdat.ServiceId);
				INVALIDATE( OldSvcdat.MultipleLCN[LCNIndex]);

//				OldSvcdat.MultipleLCN[LCNIndex] = INVALID_LCN;
				OldSvcdat.MultiplePreset[LCNIndex] = INVALID_PRESET;


				pgdb_Update(SERVICE_TABLE,(Address)&OldSvcdat);


				pgdb_Delete(PRESET_TABLE, (Address)&presetdat);
				mAddEntryToPresetTable(&svcdat, svcdat.MultipleLCN[LCNIndex],LCNIndex);
			}
			else
			{
		
				//preset is occupied, invalidate the LCN, it will be placed in non honored  range  
				TraceNotice(m,"Invalidating the LCN %d, SvcId: %d",svcdat.MultipleLCN[LCNIndex],svcdat.ServiceId);
				INVALIDATE( svcdat.MultipleLCN[LCNIndex]);
//				svcdat.MultipleLCN[LCNIndex] = INVALID_LCN;
				pgdb_Update(SERVICE_TABLE,(Address)&svcdat);
			}
        }
        else
        {
            /* That preset is free. So just grab it */
            mAddEntryToPresetTable(&svcdat, svcdat.MultipleLCN[LCNIndex],LCNIndex);
        }
    }
}


void CHsvDvbsAstra_mSort::mDigitalPresetEntryforInValidLCN(int dbindex,  int LCNIndex)
{
    int FromPreset = 0, ToPreset = 0;
    int CurrentPresetIndex = 0;
    HsvPgdatDigServiceData svcdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
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

int CHsvDvbsAstra_mSort::mGetPresetNoForService(HsvPgdatDigServiceData svcdat, int FromPreset, int ToPreset)
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

int CHsvDvbsAstra_mSort::mFirstAvailableGapInPresetList(int FromPreset, int ToPreset)
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



Bool CHsvDvbsAstra_mSort::mPriorityCheck(Nat8 OldServiceType, Nat8 NewServiceType)
{
	Bool retval = FALSE;
	int OldSvcPrio = 0,NewSvcPrio = 0;
	
	for(OldSvcPrio = 0; OldSvcPrio < ASTRA_NUM_OF_PRIORITY ; OldSvcPrio++)
	{
		if(SvcPriority[OldSvcPrio] == OldServiceType)
		{
			break;
		}
	}

	for(NewSvcPrio = 0; NewSvcPrio < ASTRA_NUM_OF_PRIORITY ; NewSvcPrio++)
	{
		if(SvcPriority[NewSvcPrio] == NewServiceType)
		{
			break;
		}
	}

	if(NewSvcPrio < OldSvcPrio)
	{
		retval = TRUE;
	}


	return retval;

}



