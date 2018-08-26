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
 *          %name: hsvdvbstricolor_mSort.c %
 *       %version: TVG_1 %
 * %date_modified: %
 *    %derived_by: anuma %
 */

#include "_hsvdvbstricolor_mSort.h"

#include "tricolorsort.h"

TRACESYMBOL(m, "s2/installation/hsvdvbstricolor/tricolor_msort")
/****************************************************************************
 * Macros and types
 ****************************************************************************/

//todo delete this


int CHsvDvbsTricolor_mSort_Priv::s__mCurrentNonHonrdRadioIndex = RADIO_START_NONHONRD_OFFSET,CHsvDvbsTricolor_mSort_Priv::s__mCurrentNonHonrdTVIndex = TV_START_NONHONRD_OFFSET;

Pump CHsvDvbsTricolor_mSort_Priv::s__Sortingpmp;














/******************************************************/

/* provides IHsvPower isortpow */
void CHsvDvbsTricolor_mSort_Priv::isortpow_Init()
{
	PrintfNotice ("Sort Pow Init being called \n");
	Sortingpmp = pmp_PmpCreateEx(pen_PumpEngine, SortingHandler, TRUE, "hsvdvbinstricolor_msort");
}

void CHsvDvbsTricolor_mSort_Priv::isortpow_TurnOn (void)
{

}

void CHsvDvbsTricolor_mSort_Priv::isortpow_TurnOff (void)
{

}

/* provides IHsvSorting		isort */

void CHsvDvbsTricolor_mSort_Priv::itricolorsort_Sort (Nat32 PackageIndex)
{
	int mode,state,retval;
	retval = rins_GetCurrentInstallationState (&mode, &state);
	TraceNotice(m,"Tricolor Sorting started");

	if(mode == AUTO_MODE)
	{
		mCurrentNonHonrdRadioIndex = RADIO_START_NONHONRD_OFFSET;
		mCurrentNonHonrdTVIndex = TV_START_NONHONRD_OFFSET;
	}

	iinsN_OnEvent(iinsN_EventSortingStarted, 0);
	pmp_PmpSend(Sortingpmp, SORT_HONOURED_SERVICES, 0);
}

void CHsvDvbsTricolor_mSort_Priv::SortingHandler( int event, Nat32 startindex )
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

void CHsvDvbsTricolor_mSort_Priv::mSortHonouredServices(Bool CheckForRadioServices, int startindex)
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


void CHsvDvbsTricolor_mSort_Priv::mSortNonHonouredServices(Bool CheckForRadioServices, int startindex)
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

void CHsvDvbsTricolor_mSort_Priv::mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, int LCNIndex)
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
	presetdat.VisibleService = svcdat->MultipleVisibleService[LCNIndex];
	presetdat.SystemHidden = !(svcdat->MultipleVisibleService[LCNIndex]);
	presetdat.NumericSelect = svcdat->MultipleNumericSelect[LCNIndex];
	
	
	TraceDebug(m,"SID = %d PresetNo = %d Visibility %d NumericSel %d",presetdat.ServiceId,PresetNo,presetdat.VisibleService,presetdat.NumericSelect);
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

void CHsvDvbsTricolor_mSort_Priv::mDigitalPresetEntryforValidLCN(int dbindex, int LCNIndex)
{
	Bool isHonoured = TRUE;
    HsvPgdatDigServiceData svcdat,tempsvcdat;
    HsvPgdatPresetData presetdat;
	int CurrentPresetIndex = 0;

	
    if( pgdb_GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
    	TraceNotice(m,"debug:%s Service id %d",__FUNCTION__,svcdat.ServiceId);
        REVALIDATE( svcdat.MultipleLCN[LCNIndex]);

        /* Check if LCN preset is occupied */
		CurrentPresetIndex = mGetPresetNoForService(&svcdat,isHonoured,LCNIndex);		
        presetdat.PresetNumber = CurrentPresetIndex;

		TraceNotice(m,"%s CurrentPresetIndex %d",__FUNCTION__,CurrentPresetIndex);
			
        if( pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) )
        {
        	TraceNotice(m,"debug:LCN Conflict:previous sid %d curr sid %d ",presetdat.ServiceId,svcdat.ServiceId);
			/* LCN conflict : Service with Lower Sid retained and Higher sent to NonHonoured List*/        
        	if(presetdat.ServiceId > svcdat.ServiceId)
        	{
        		tempsvcdat.Tpid = presetdat.Tpid;
				tempsvcdat.ServiceId = presetdat.ServiceId;

				if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat) == TRUE)
				{
					INVALIDATE( tempsvcdat.MultipleLCN[LCNIndex]);
					tempsvcdat.MultiplePreset[LCNIndex] = INVALID_PRESET;
					pgdb_Update(SERVICE_TABLE,(Address)&tempsvcdat);
				}
				pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
				TraceDebug(m," %d Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x",__LINE__,presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
				mAddEntryToPresetTable(&svcdat,  CurrentPresetIndex, LCNIndex);
				
        	}
			else
			{
				//preset is occupied ,service will get the preset number in non hon
				TraceNotice(m,"INVALIDATE SID = %d svcdat.LCN = %d ",svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
				INVALIDATE( svcdat.MultipleLCN[LCNIndex]);
				pgdb_Update(SERVICE_TABLE,(Address)&svcdat);
			}
			
        }
        else
        {
		     TraceDebug(m," %d Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x",__LINE__,presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
            /* That preset is free. So just grab it */
            mAddEntryToPresetTable(&svcdat,  CurrentPresetIndex, LCNIndex);
        }
    }
}

void CHsvDvbsTricolor_mSort_Priv::mDigitalPresetEntryforInValidLCN(int dbindex,  int LCNIndex)
{
	Bool isHonoured = FALSE;
    int CurrentPresetIndex = 0;
    HsvPgdatDigServiceData svcdat;
	HsvPgdatPresetData presetdat;

    if(TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbindex, (Address)&svcdat))
    {
    	TraceNotice(m,"debug:%s Service id %d",__FUNCTION__,svcdat.ServiceId);
		CurrentPresetIndex = mGetPresetNoForService(&svcdat,isHonoured,LCNIndex);
		presetdat.PresetNumber = CurrentPresetIndex;

		TraceNotice(m,"%s CurrentPresetIndex %d",__FUNCTION__,CurrentPresetIndex);

		if(IS_RADIO_SERVICE(svcdat.ServiceType))
        {
        	if((CurrentPresetIndex >= RADIO_START_NONHONRD_OFFSET) && (CurrentPresetIndex <= RADIO_MAX_NONHONRD_OFFSET))
        	{
        		TraceDebug(m,"debug: %d Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x",__LINE__,presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
				mAddEntryToPresetTable(&svcdat, CurrentPresetIndex, LCNIndex);
        	}
			else
			{
				TraceNotice(m,"%s CurrentPresetIndex-Not-Correct preset Not Added for Invalid Radio !!",__FUNCTION__);				
			}
        }
		else
		{
			if((CurrentPresetIndex >= TV_START_NONHONRD_OFFSET) && (CurrentPresetIndex <= TV_MAX_NONHONRD_OFFSET))
        	{
        		TraceDebug(m,"debug: %d Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x",__LINE__,presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
				mAddEntryToPresetTable(&svcdat, CurrentPresetIndex, LCNIndex);
        	}
			else
			{
				TraceNotice(m,"%s CurrentPresetIndex-Not-Correct preset Not Added for Invalid TV !!",__FUNCTION__);								
			}	
		}
    }
    else
    {
        TraceNotice(m,"%d %s FAILURE in Svcdat.", __LINE__,__FUNCTION__);
        ASSERT(!"FAILURE in Svcdat");
    }
}

int CHsvDvbsTricolor_mSort_Priv::mGetPresetNoForService(HsvPgdatDigServiceData *svcdat,Bool isHonoured,int LCNIndex)
{
  	int CurrentPresetIndex = 0;
    HsvPgdatPresetData presetdat;	

	
	if(isHonoured == TRUE)
	{
		if(IS_RADIO_SERVICE(svcdat->ServiceType))
		{
			CurrentPresetIndex = RADIO_START_HONRD_OFFSET + svcdat->MultipleLCN[LCNIndex];
		}
		else
		{
			CurrentPresetIndex = TV_START_HONRD_OFFSET + svcdat->MultipleLCN[LCNIndex];
		}
		
	}
	else
	{
		TraceNotice(m,"debug:curRadIndex %d curTVIndex %d",mCurrentNonHonrdRadioIndex,mCurrentNonHonrdTVIndex);
		if(IS_RADIO_SERVICE(svcdat->ServiceType))
		{
			CurrentPresetIndex = mCurrentNonHonrdRadioIndex;
			mCurrentNonHonrdRadioIndex++;
		}
		else
		{
			CurrentPresetIndex = mCurrentNonHonrdTVIndex;
			mCurrentNonHonrdTVIndex++;
		}
	}

	TraceNotice(m,"%s:: %d CurrentPresetIndex = %d",__FUNCTION__, __LINE__,CurrentPresetIndex);
	return CurrentPresetIndex;

}

int CHsvDvbsTricolor_mSort_Priv::mFirstAvailableGapInPresetList(int FromPreset, int ToPreset)
{

	HsvPgdatPresetData presetdat;
	int presetIndex = FromPreset;

	for(presetIndex = FromPreset;presetIndex<=ToPreset;presetIndex++)
	{
		if(pgdb_GetByIndex( PRESET_TABLE, presetIndex, (Address)&presetdat ))
		{
			if(presetdat.PresetNumber == INVALID_PRESET)
			{
				return presetIndex;
			}
		}
		else
		{
			TraceNotice(m,"%s Failure in GetByIndex of Preset Table presetIndex",__FUNCTION__,presetIndex);
		}
		
	}
	
	return presetIndex;
}

