#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <sys/stat.h>

typedef enum
{
	SORT_HONOURED_SERVICES = 0,
	SORT_HONOURED_RADIO_SERVICES,
	SORT_NONHONOURED_SERVICES,
	SORT_NONHONOURED_RADIO_SERVICES,
	SORT_COMPLETE
}SORTING_HANDLER_ENUM;
#define NUM_OF_PRIORITY	5

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mCurrentRadioIndex,mCurrentPresetIndex;
static int s__mCurrentRadioIndex,s__mCurrentPresetIndex;
Pump Sortingpmp;
static Pump s__Sortingpmp;
int SvcPriority[NUM_OF_PRIORITY];
static int s__SvcPriority[NUM_OF_PRIORITY];
void SortingHandler( int event, Nat32 startindex );
void mSortHonouredServices(Bool CheckForRadioServices, int startindex);
void mSortNonHonouredServices(Bool CheckForRadioServices, int startindex);
void mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo);
void mDigitalPresetEntryforValidLCN(int dbindex);
Bool mPriorityCheck(Nat8 OldServiceType, Nat8 NewServiceType);
void mDigitalPresetEntryforInValidLCN(int dbindex);
int mGetPresetNoForService(HsvPgdatDigServiceData svcdat, int FromPreset, int ToPreset);
int mFirstAvailableGapInPresetList(int FromPreset, int ToPreset);
void module__init(void){
	mCurrentRadioIndex	=	s__mCurrentRadioIndex;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	Sortingpmp	=	s__Sortingpmp;
	memcpy((void*)SvcPriority,(void*)s__SvcPriority,sizeof(SvcPriority));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef NUM_OF_PRIORITY
#undef NUM_OF_PRIORITY
#endif //NUM_OF_PRIORITY
#endif //LOCAL_UNDEFINES
