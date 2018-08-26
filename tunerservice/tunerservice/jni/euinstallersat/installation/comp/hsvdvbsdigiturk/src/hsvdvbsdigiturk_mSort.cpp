/**********************************************************************
 *
 *   C Source:       hsvdvbsdigiturk_msort.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    aneeshc %
 *   %date_created:  Sat May  4 13:19:02 2013 %
 *
 **********************************************************************/
#include "_hsvdvbsdigiturk_mSort.h"







/* module functions */











/* module variables */
Pump CHsvDvbsDigiTurk_mSort_Priv::s__mSortPump;

int CHsvDvbsDigiTurk_mSort_Priv::s__mCurrentTvPreset = INVALID_PRESET,CHsvDvbsDigiTurk_mSort_Priv::s__mCurrentRadioPreset = INVALID_PRESET,CHsvDvbsDigiTurk_mSort_Priv::s__mFirstInstalledPreset = INVALID_PRESET;

TRACESYMBOL(m, "dvb/installation/hsvdvbsdigiturk_msort")


void CHsvDvbsDigiTurk_mSort_Priv::isortpow_Init()
{
    mSortPump = pmp_PmpCreateEx( pen_PumpEngine, mSortHandler, FALSE, "hsvdvbsdigiturk_msort" );
	TraceNotice(m, "%s mSortPump %d", __FUNCTION__, mSortPump);
}

void CHsvDvbsDigiTurk_mSort_Priv::isortpow_TurnOn()
{
}

void CHsvDvbsDigiTurk_mSort_Priv::isortpow_TurnOff()
{
}

/* provides IHsvSorting		isort */
void CHsvDvbsDigiTurk_mSort_Priv::isort_Sort(Nat32 PackageIndex)
{
	mFirstInstalledPreset = mCurrentRadioPreset = mCurrentTvPreset = 0xFFFF; 
	
	TraceNotice(m, "%s", __FUNCTION__);
	
	HsvPgdatDigServiceData svcdat;

	if(pgdb_GetByIndex(SERVICE_TABLE, 0, (Address)&svcdat) == TRUE)
	{
		svcdat.ServiceListVersion = iscandata_GetInstallationVersion();
		
		TraceNotice(m, "%s Last ServiceListVersion %d", __FUNCTION__, svcdat.ServiceListVersion);
		pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
	}
	
	/* Naresh: is this required */
	iinsN_OnEvent(iinsN_EventSortingStarted, 0);
	
    pmp_PmpSend(mSortPump, evSortHonoredTvPresets, (Nat32)STARTING_RECORD_INDEX);
}

/****************************************************************************
  Static functions Implementation
 *****************************************************************************/

void CHsvDvbsDigiTurk_mSort_Priv::mSortHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceNotice(m,"%s value %d\n", __FUNCTION__, value);
    switch(value)
    {
		case evSortHonoredTvPresets:
            mSortHonouredServices(FALSE, value, param);
            break;
		case evSortHonoredRadioPresets:
            mSortHonouredServices(TRUE, value, param);
            break;
        case evSortNonHonoredTvPresets:
            mSortNonHonouredServices(FALSE, value, param);
            break;
        case evSortNonHonoredRadioPresets:
            mSortNonHonouredServices(TRUE, value, param);
            break;
        case evComplete:
            iinsN_OnEvent(iinsN_EventSortCompleted, 0);
            break;
        default:
            ASSERT(!"Unknown Step in sorting");
            break;
    }
}

void CHsvDvbsDigiTurk_mSort_Priv::mSortHonouredServices(Bool CheckForRadioServices, int EvCurrentSortStep, int EvCurrentRecordIndex)
{
	Bool ProceedToNextStep = TRUE;
    HsvPgdatDigServiceData svcdat;
    int i, j, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE), EvNextStep = EvCurrentSortStep;
    
	for( i = EvCurrentRecordIndex, j = 0; (i < NoOfRecs) && (j < MAX_PRESETS_IN_SINGLE_STEP); i++, j++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat) == TRUE )
        {
			EvCurrentRecordIndex = i;
            if( VALID_LCN_RANGE(svcdat.LCN) && PRESET_NOT_ALLOCATED(svcdat)  && (CheckForRadioServices == IS_RADIO_SERVICE(svcdat.ServiceType)))
            {
				ProceedToNextStep = FALSE;
				TraceNotice(m, "try to allocate preset entry for LCN service = %d\n", svcdat.LCN);
				mDigitalPresetEntryforValidLCN(&svcdat);
			}
		}
	}
	
	/* if proceed is TRUE then one atleast one interested preset is found int this pass so contiue next time within same step,
       else continue with next sorting step */
	   if((ProceedToNextStep == TRUE) && (i >= NoOfRecs))
	   {
			EvNextStep = (EvCurrentSortStep + 1);
			EvCurrentRecordIndex = -1;
	   }	   
	   TraceNotice(m, "Pmp send done with event %d with record index %d\n", EvNextStep, (EvCurrentRecordIndex + 1));

    pmp_PmpSend(mSortPump, EvNextStep, (Nat32) (EvCurrentRecordIndex + 1));
}

void CHsvDvbsDigiTurk_mSort_Priv::mSortNonHonouredServices(Bool CheckForRadioServices, int EvCurrentSortStep, int EvCurrentRecordIndex)
{
    Bool ProceedToNextStep = TRUE;
    HsvPgdatDigServiceData svcdat;
    int i, j, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE), EvNextStep = EvCurrentSortStep;
    
	for( i = EvCurrentRecordIndex, j = 0; (i < NoOfRecs) && (j < MAX_PRESETS_IN_SINGLE_STEP); i++, j++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat) == TRUE )
        {
			EvCurrentRecordIndex = i;
            if( !VALID_LCN_RANGE(svcdat.LCN) && PRESET_NOT_ALLOCATED(svcdat) 
				&& (CheckForRadioServices == IS_RADIO_SERVICE(svcdat.ServiceType)))
            {
				ProceedToNextStep = FALSE;
				TraceNotice(m, "try to allocate preset entry for NON LCN ServiceId %d\n", svcdat.ServiceId);
				mDigitalPresetEntryforInValidLCN(&svcdat);
			}
		}
	}
	
	/* if proceed is TRUE then one atleast one interested preset is found int this pass so contiue next time within same step,
       else continue with next sorting step */
	   if(ProceedToNextStep == TRUE)
	   {
			EvNextStep = (EvCurrentSortStep + 1);
			EvCurrentRecordIndex = -1;
	   }	   
	   TraceNotice(m, "Pmp send done with event %d with record index %d\n", EvNextStep, (EvCurrentRecordIndex + 1));

    pmp_PmpSend(mSortPump, EvNextStep, (Nat32) (EvCurrentRecordIndex + 1));
}

void CHsvDvbsDigiTurk_mSort_Priv::mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat)
{
    HsvPgdatPresetData presetdat;

	/* Check if LCN preset is occupied */
	presetdat.PresetNumber = svcdat->LCN;
	if( (pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == FALSE) )
	{
		/* That preset is free. So just grab it */
		mAddEntryToPresetTable(svcdat, svcdat->LCN);
	}
	else
	{
		/* LCN conflict so sort it in non honored preset range as it is FCFS based for LCN conflict rules */
		svcdat-> LCN = INVALID_LCN;
		pgdb_Update(SERVICE_TABLE, (Address)svcdat);
	}
}

void CHsvDvbsDigiTurk_mSort_Priv::mDigitalPresetEntryforInValidLCN(HsvPgdatDigServiceData *svcdat)
{
    mFindPresetNumberForService(svcdat->ServiceType);

	if( (CURRENT_PRESET(svcdat->ServiceType) >= TV_START_PRESET) && (CURRENT_PRESET(svcdat->ServiceType) <= HYBRID_END_PRESET) )
	{
		mAddEntryToPresetTable(svcdat, CURRENT_PRESET(svcdat->ServiceType));
		if(IS_RADIO_SERVICE(svcdat->ServiceType))
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
		TraceNotice(m,"%s Could not allocate the preset entry to the service <%d %d>", __FUNCTION__, svcdat->OriginalNetworkId, svcdat->ServiceId);
		ASSERT(!"Could not allocate the preset entry to the service");
	}
}

void CHsvDvbsDigiTurk_mSort_Priv::mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNumber)
{
    HsvPgdatPresetData      presetdat;

	pgdb_Initialise (pgdbconst_Preset, (Address)&presetdat);
	
	svcdat->PresetNumber		= PresetNumber;
	
	presetdat.PresetNumber 		= PresetNumber;
	presetdat.OriginalNetworkId = svcdat->OriginalNetworkId;
    presetdat.ServiceId 		= svcdat->ServiceId;
    presetdat.Tsid 				= svcdat->Tsid;
    presetdat.Tpid 				= svcdat->Tpid;
    presetdat.Frequency 		= svcdat->Frequency;
	presetdat.Polarization 		= svcdat->Polarization;
	presetdat.LnbNumber 		= svcdat->LnbNumber;
	presetdat.VisibleService	 	= svcdat->VisibleService;
	//presetdat.SystemHidden	 	= !svcdat->VisibleService[0];
	presetdat.NumericSelect 	= svcdat->NumericSelect;

	pgdb_Add(PRESET_TABLE, (Address)&presetdat);
	
	pgdb_Update(SERVICE_TABLE,(Address)svcdat);
	
	TraceNotice(m,"Addition at Preset %ld by <%d %d %ld>\n", presetdat.PresetNumber, svcdat->OriginalNetworkId, svcdat->ServiceId, svcdat->Frequency);

    mFirstInstalledPreset = (mFirstInstalledPreset > presetdat.PresetNumber) ? presetdat.PresetNumber: mFirstInstalledPreset;    
}

Bool CHsvDvbsDigiTurk_mSort_Priv::mIsCurrentPresetInvalid( int PresetNo, int ServiceType, Bool FallBackToMixedRange)
{
	HsvPgdatPresetData presetdata;
	int startpreset = 0, endpreset = 0;
	
    mGetPresetRangeForService(ServiceType, &startpreset, &endpreset, FallBackToMixedRange);
	
	presetdata.PresetNumber = PresetNo;
	
    return ( (PresetNo == INVALID_PRESET) || (PresetNo < startpreset) || (PresetNo > endpreset)
	         || pgdb_GetByKey(PRESET_TABLE, (Address)&presetdata) );
}

/* Based on service type updates the static variable maintained for CURRENT_PRESET */
void CHsvDvbsDigiTurk_mSort_Priv::mFindPresetNumberForService(int ServiceType)
{
    TraceNotice(m,"%s CurrentRunningPreset %d mCurrentRadioPreset %d mCurrentTvPreset %d\n", __FUNCTION__, CURRENT_PRESET(ServiceType), mCurrentRadioPreset, mCurrentTvPreset);
    if( mIsCurrentPresetInvalid(CURRENT_PRESET(ServiceType), ServiceType, FALSE) )
    {
		mAssignPresetNumberForService(ServiceType, FALSE);
		
		if( mIsCurrentPresetInvalid(CURRENT_PRESET(ServiceType), ServiceType, FALSE) )
		{
			/* Fall back to Mixed  Range */
			mAssignPresetNumberForService(ServiceType, TRUE);
		}
	}
    TraceDebug(m,"%s %d CurrentAvailablePreset %d\n", __FUNCTION__, __LINE__, CURRENT_PRESET(ServiceType));
}

/* This function finds last non honored preset installed or start preset range if none are there */
void CHsvDvbsDigiTurk_mSort_Priv::mAssignPresetNumberForService(int ServiceType, Bool FallBackToMixedRange)
{
	HsvPgdatPresetData presetdat;
    int i, StartPreset = 0, EndPreset = 0, NoOfRecs = pgdb_GetNoRecords(PRESET_TABLE);

    mGetPresetRangeForService(ServiceType, &StartPreset, &EndPreset, FallBackToMixedRange);	
    TraceNotice(m,"%s StartPreset %d EndPreset %d", __FUNCTION__, StartPreset, EndPreset);
	if(IS_RADIO_SERVICE(ServiceType))
	{
		mCurrentRadioPreset = StartPreset;
	}
	else
	{
		mCurrentTvPreset = StartPreset;
	}				
	for(i = 0; i < NoOfRecs; i++)
	{
		if(pgdb_GetByIndex(PRESET_TABLE, i, (Address)&presetdat) == TRUE)
		{
			/* sorted in descending oreder so the first to get is the last non hhonored preset number in interested range */
			if( (presetdat.PresetNumber >= StartPreset) && (presetdat.PresetNumber <= EndPreset) )
			{
				if(IS_RADIO_SERVICE(ServiceType))
				{
					mCurrentRadioPreset = (presetdat.PresetNumber + 1);
				}
				else
				{
					mCurrentTvPreset = (presetdat.PresetNumber + 1);
				}
				break;
			}
			
		}
	}
}

void CHsvDvbsDigiTurk_mSort_Priv::mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset,  Bool FallBackToMixedRange)
{
    *startpreset  = TV_START_PRESET, *endpreset = TV_END_PRESET;
    
    /* Validity based on its service group(RADIO, TV) */
    if( IS_RADIO_SERVICE(svcType) )
	{
		*startpreset = RADIO_START_PRESET;
		*endpreset   = RADIO_END_PRESET;
	}
	
	if(FallBackToMixedRange == TRUE)
	{
		*startpreset = HYBRID_START_PRESET;
		*endpreset   = HYBRID_END_PRESET;
	}
}
