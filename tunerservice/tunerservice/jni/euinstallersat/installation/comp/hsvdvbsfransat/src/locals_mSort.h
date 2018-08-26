#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <sys/stat.h>

#define ZERO_VALUE_LCN		(0xC001)

typedef enum
{
	SORT_HONOURED_SERVICES = 0,
	SORT_HONOURED_RADIO_SERVICES,
	SORT_NONHONOURED_SERVICES,
	SORT_NONHONOURED_RADIO_SERVICES,
	SORT_COMPLETE
}SORTING_HANDLER_ENUM;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mCurrentRadioIndex,mCurrentPresetIndex;
static int s__mCurrentRadioIndex,s__mCurrentPresetIndex;
Pump Sortingpmp;
static Pump s__Sortingpmp;
void SortingHandler( int event, Nat32 startindex );
void mSortHonouredServices(Bool CheckForRadioServices, int startindex);
void mSortNonHonouredServices(Bool CheckForRadioServices, int startindex);
void mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, int LCNIndex);
void mDigitalPresetEntryforValidLCN(int dbindex, int LCNIndex);
void mDigitalPresetEntryforInValidLCN(int dbindex,  int LCNIndex);
int mGetPresetNoForService(HsvPgdatDigServiceData svcdat, int FromPreset, int ToPreset);
int mFirstAvailableGapInPresetList(int FromPreset, int ToPreset);
void mStoreZeroMultipleLCN(HsvPgdatDigServiceData* psvcdat);
void mRetriveZeroMultipleLCN(HsvPgdatDigServiceData* psvcdat);
void module__init(void){
	mCurrentRadioIndex	=	s__mCurrentRadioIndex;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	Sortingpmp	=	s__Sortingpmp;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#endif //LOCAL_UNDEFINES
