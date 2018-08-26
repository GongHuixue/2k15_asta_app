#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <errno.h>

#include <stdio.h>

#include <sys/types.h>

#include <unistd.h> 

#include <ctype.h>

#define CURRENT_TABLE                       ( pgdb_GetCurrentTable() )

#define SERVICE_TABLE                       ( CURRENT_TABLE | pgdbconst_DigitalService )

#define PRESET_TABLE                        ( CURRENT_TABLE | pgdbconst_Preset )

#define	INVALID_PRESET						( 0XFFFF )

#define STARTING_RECORD_INDEX				( 0 )

#define VALID_LCN_RANGE(LCN)				( (LCN > 0) && (LCN < 1000) )

#define PRESET_NOT_ALLOCATED(svcdat)        ( (svcdat).PresetNumber == INVALID_PRESET )

#define MAX_PRESETS_IN_SINGLE_STEP			( 300 )	/* Number chosen to avoid watch dog due to high presets handling in single step */

#define INVALID_LCN       					( 0xC000 )

#define IS_RADIO_SERVICE(x)                 ( (x == AppApiRadioService) || (x == AppApiUserDefinedRadioChannelWithVideoComp) )

/* start & end point of all non honored presets */

#define RADIO_START_PRESET                  ( 3001 )

#define RADIO_END_PRESET                    ( 5000 )

#define TV_START_PRESET                  	( 1001 )

#define TV_END_PRESET                  		( 3000 )

#define HYBRID_START_PRESET					( 5001 )

#define HYBRID_END_PRESET					( 9999 )

#define HYBRID_SERVICES						( 0xFFFF )

#define CURRENT_PRESET(svcType)             ( IS_RADIO_SERVICE(svcType)? mCurrentRadioPreset : mCurrentTvPreset )

/*************************************************************************
    Local Structures and enums
 **************************************************************************/

typedef enum
{
    evSortHonoredTvPresets,
	evSortHonoredRadioPresets,
    evSortNonHonoredTvPresets,
    evSortNonHonoredRadioPresets,
    evComplete
}SortSteps;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mSortPump;
static Pump s__mSortPump;
int mCurrentTvPreset,mCurrentRadioPreset,mFirstInstalledPreset;
static int s__mCurrentTvPreset,s__mCurrentRadioPreset,s__mFirstInstalledPreset;
void mSortHandler(int value, Nat32 param);
void mSortHonouredServices(Bool CheckForRadioServices, int EvCurrentSortStep, int EvCurrentRecordIndex);
void mSortNonHonouredServices(Bool CheckForRadioServices, int EvCurrentSortStep, int EvCurrentRecordIndex);
void mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
void mDigitalPresetEntryforInValidLCN(HsvPgdatDigServiceData *svcdat);
void mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNumber);
Bool mIsCurrentPresetInvalid( int PresetNo, int ServiceType, Bool FallBackToMixedRange);
void mFindPresetNumberForService(int ServiceType);
void mAssignPresetNumberForService(int ServiceType, Bool FallBackToMixedRange);
void mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset,  Bool FallBackToMixedRange);
void module__init(void){
	mSortPump	=	s__mSortPump;
	mCurrentTvPreset	=	s__mCurrentTvPreset;
	mCurrentRadioPreset	=	s__mCurrentRadioPreset;
	mFirstInstalledPreset	=	s__mFirstInstalledPreset;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef INVALID_PRESET
#undef INVALID_PRESET
#endif //INVALID_PRESET
#ifdef STARTING_RECORD_INDEX
#undef STARTING_RECORD_INDEX
#endif //STARTING_RECORD_INDEX
#ifdef VALID_LCN_RANGE(LCN)
#undef VALID_LCN_RANGE(LCN)
#endif //VALID_LCN_RANGE(LCN)
#ifdef PRESET_NOT_ALLOCATED(svcdat)
#undef PRESET_NOT_ALLOCATED(svcdat)
#endif //PRESET_NOT_ALLOCATED(svcdat)
#ifdef MAX_PRESETS_IN_SINGLE_STEP
#undef MAX_PRESETS_IN_SINGLE_STEP
#endif //MAX_PRESETS_IN_SINGLE_STEP
#ifdef INVALID_LCN
#undef INVALID_LCN
#endif //INVALID_LCN
#ifdef IS_RADIO_SERVICE(x)
#undef IS_RADIO_SERVICE(x)
#endif //IS_RADIO_SERVICE(x)
#ifdef RADIO_START_PRESET
#undef RADIO_START_PRESET
#endif //RADIO_START_PRESET
#ifdef RADIO_END_PRESET
#undef RADIO_END_PRESET
#endif //RADIO_END_PRESET
#ifdef TV_START_PRESET
#undef TV_START_PRESET
#endif //TV_START_PRESET
#ifdef TV_END_PRESET
#undef TV_END_PRESET
#endif //TV_END_PRESET
#ifdef HYBRID_START_PRESET
#undef HYBRID_START_PRESET
#endif //HYBRID_START_PRESET
#ifdef HYBRID_END_PRESET
#undef HYBRID_END_PRESET
#endif //HYBRID_END_PRESET
#ifdef HYBRID_SERVICES
#undef HYBRID_SERVICES
#endif //HYBRID_SERVICES
#ifdef CURRENT_PRESET(svcType)
#undef CURRENT_PRESET(svcType)
#endif //CURRENT_PRESET(svcType)
#endif //LOCAL_UNDEFINES
