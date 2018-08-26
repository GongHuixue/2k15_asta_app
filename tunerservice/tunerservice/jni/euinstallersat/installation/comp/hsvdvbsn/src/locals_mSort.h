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
} SORTING_HANDLER_ENUM;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mCurrentRadioIndex;
static int s__mCurrentRadioIndex;
int mCurrentPresetIndex;
static int s__mCurrentPresetIndex;
Pump mSortingPmp;
static Pump s__mSortingPmp;
void SortingHandler (int event, Nat32 startIndex);
void mSortHonouredServices (Bool checkForRadioServices, int startIndex);
void mSortNonHonouredServices(Bool checkForRadioServices, int startIndex);
void mAddEntryToPresetTable (HsvPgdatDigServiceData *svcData, int presetNo);
void mDigitalPresetEntryforValidLCN (int dbIndex);
void mDigitalPresetEntryforInValidLCN (int dbIndex);
int mGetPresetNoForService (HsvPgdatDigServiceData svcData, int fromPreset, int toPreset);
int mFirstAvailableGapInPresetList(int fromPreset, int toPreset);
void module__init(void){
	mCurrentRadioIndex	=	s__mCurrentRadioIndex;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	mSortingPmp	=	s__mSortingPmp;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#endif //LOCAL_UNDEFINES
