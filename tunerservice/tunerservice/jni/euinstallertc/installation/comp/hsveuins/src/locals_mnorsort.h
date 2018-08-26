#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <unistd.h> 

#include <ctype.h>

/**************************************************************************
 * Macros and types
 **************************************************************************/

#define WINDOWID                            (wnddest_GetWindowId(HsvMain))

#define START_FREQUENCY                     ((108) * (16))

#define END_FREQUENCY                       ((863) * (16))

#define MIN_FREQUENCYDRIFT                  (3 * 16)            /* 6 MHz is the band*/

#define CURRENT_TABLE                       (pgdb_GetCurrentTable())

#define PTC_TABLE                           (CURRENT_TABLE | pgdbconst_DigitalTS)

#define SERVICE_TABLE                       (CURRENT_TABLE | pgdbconst_DigitalService)

#define ANALOG_TABLE                        (CURRENT_TABLE | pgdbconst_Analog)

#define PRESET_TABLE                        (CURRENT_TABLE | pgdbconst_Preset)      

#define AUTO_MODE                           (rins_InstallationModeAutomatic)

#define UPDATE_MODE                         (rins_InstallationModeUpdate)

#define MANUAL_MODE                         (rins_InstallationModeWeakSignal)

#define ANALOG_MANUAL                       (rins_InstallationModeManual)

#define BACKGROUND_MODE                     (rins_InstallationModeBackground)

#define CURRENT_MODE                        (rins_GetInstallationMode()) 

#define AUTO_INSTALL                        ((CURRENT_MODE) == (AUTO_MODE))

#define UPDATE_INSTALL                      ((CURRENT_MODE) == (UPDATE_MODE))

#define MANUAL_INSTALL                      ((CURRENT_MODE) == (MANUAL_MODE))

#define BACKGROUND_INSTALL                  ((CURRENT_MODE) == (BACKGROUND_MODE))

/* Start point of radio services */

#define MAX_LCN_VALUE                                               (div_MaxLCNValue)

#define IS_RADIO_SERVICE(x)                                         ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService))

#define GETCURRENTINDEX(x)                                          (IS_RADIO_SERVICE(x) ? (mCurrentRadioIndex) : (mCurrentPresetIndex))

#define MAX_SERVICE_TYPES1           (8)

#define TV_SERVICE                  (TelevisionService)

#define RADIO_SERVICE               (RadioService)

#define TELETEXT_SERVICE            (TeletextService)

#define NVOD_REFERENCE_SERVICE      (NVODReferenceService)

#define NVOD_TIMESHIFTED_SERVICE    (NVODTimeShiftedService)

#define MOSAIC_SERVICE              (MosaicService)

#define DATABROADCAST_SERVICE       (DatabroadcastService)

#define DVBMHP_SERVICE              (DVBMHPService)

#define START_PRESET                        (0)

#define MAX_NONHONOURED_PRESET              (899)

#define RADIO_START_PRESET                  (200)

#define PRESET_NOT_ALLOCATED(presetno)      (presetno == INVALID_PRESET)

#define IS_UNINSTALLED_PRESET(svcdat)       ( ((svcdat).LCN == 0) || ((svcdat).VisibleService == 0) )           

#define IS_INTERESTED_LCN_RANGE(lcn)        ( (lcn > 0) && (lcn < 899) )

#define IS_SPECIAL_SERVICE(lcn)             ( (lcn >= 900) && (lcn <= 1999) )

#define START_PRESET_FOR_SPECIAL_SERVICE    ( 900 )

#define LAST_PRESET_FOR_SPECIAL_SERVICE     ( 1999 )

#define INSTALL_VERSION                     (rins_GetInstallationVersion())

#ifndef __cplusplus

#define CLASSSCOPE

#endif

#define FNADDR(f) (& CLASSSCOPE f)


/*************************************************************************
  Local Structures and enums
 **************************************************************************/

typedef enum
{
    evStep1 = 0,
    evStep2,
    evStep3,
    evStep4,
    evStep5,
    evStep6,
    evStep7,
    evStep8,
    evStep9,
    evStep10,
    evStep11,
    evStep12,
    evStep13,
    evStepAll,
    evNoSorting,
}SortSteps;
typedef struct
{
    Bool CheckForONID;
    Bool CheckForNID;
    Bool CheckForUnInstalledPreset;
    Bool CheckForRadioService;
}HsvSortingRules;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#endif

Pump mnorsortPmp;
static Pump s__mnorsortPmp;
int mFirstInstalledPreset,mCurrentRadioIndex,mCurrentPresetIndex;
static int s__mFirstInstalledPreset,s__mCurrentRadioIndex,s__mCurrentPresetIndex;
int mServicePriority[MAX_SERVICE_TYPES1];
static int s__mServicePriority[MAX_SERVICE_TYPES1];
void mNoSorting(int evCurrentSortStep);
void mnorsortHandler(int value, Nat32 param);
void mSortAnalogPresets(int evCurrentSortStep);
void mSortDigitalHonouredPresets(Bool CheckForRadioService, int evCurrentSortStep);
void mSortDigitalNonFavHonouredPresets(Bool CheckForRadioService, int evCurrentSortStep);
void mSortDigitalNonHonouredPresets(HsvSortingRules InterestedPresets, int evCurrentSortStep);
void mSortRemainingDigitalPresets(Bool CheckForRadioService, int evCurrentSortStep);
Bool mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
void mDigitalPresetEntryforInValidLCN(int dbindex);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp( Nat16 * str1, Nat16 * str2 );
int mGetServicePriority(int serviceType);
Bool CallBackHsvAnalog(Address data);
Bool IsFreqUserInstalled(Nat32 Frequency, Nat16 StreamPriority);
int ConvertToDVBServiceType(int servicetype);
inline int mLastLCNBasedPreset(Bool CheckForRadioServices);
inline int mFirstAvailableGapInPresetList(int FromPreset, int ToPreset);
Bool mIsFavouriteNetworkID(HsvPgdatDigServiceData svcdat);
int GetAutomaticPlatformPresetNumber(void);
inline Nat16 mFindPlaceForAnalogPresets(void);
void mGetPresetRangeForService(HsvPgdatDigServiceData svcdat, int *FromPreset, int *ToPreset);
int mGetPresetNoForService(HsvPgdatDigServiceData svcdat, int FromPreset, int ToPreset);
inline int mLastLCNBasedSpecialPreset(void);
inline Bool mValidLCNRange(int LCN, int ServiceType);
void module__init(void){
#ifndef __cplusplus

#endif

	mnorsortPmp	=	s__mnorsortPmp;
	mFirstInstalledPreset	=	s__mFirstInstalledPreset;
	mCurrentRadioIndex	=	s__mCurrentRadioIndex;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	memcpy((void*)mServicePriority,(void*)s__mServicePriority,sizeof(mServicePriority));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef START_FREQUENCY
#undef START_FREQUENCY
#endif //START_FREQUENCY
#ifdef END_FREQUENCY
#undef END_FREQUENCY
#endif //END_FREQUENCY
#ifdef MIN_FREQUENCYDRIFT
#undef MIN_FREQUENCYDRIFT
#endif //MIN_FREQUENCYDRIFT
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef ANALOG_TABLE
#undef ANALOG_TABLE
#endif //ANALOG_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef ANALOG_MANUAL
#undef ANALOG_MANUAL
#endif //ANALOG_MANUAL
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef AUTO_INSTALL
#undef AUTO_INSTALL
#endif //AUTO_INSTALL
#ifdef UPDATE_INSTALL
#undef UPDATE_INSTALL
#endif //UPDATE_INSTALL
#ifdef MANUAL_INSTALL
#undef MANUAL_INSTALL
#endif //MANUAL_INSTALL
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#ifdef MAX_LCN_VALUE
#undef MAX_LCN_VALUE
#endif //MAX_LCN_VALUE
#ifdef IS_RADIO_SERVICE(x)
#undef IS_RADIO_SERVICE(x)
#endif //IS_RADIO_SERVICE(x)
#ifdef GETCURRENTINDEX(x)
#undef GETCURRENTINDEX(x)
#endif //GETCURRENTINDEX(x)
#ifdef MAX_SERVICE_TYPES1
#undef MAX_SERVICE_TYPES1
#endif //MAX_SERVICE_TYPES1
#ifdef TV_SERVICE
#undef TV_SERVICE
#endif //TV_SERVICE
#ifdef RADIO_SERVICE
#undef RADIO_SERVICE
#endif //RADIO_SERVICE
#ifdef TELETEXT_SERVICE
#undef TELETEXT_SERVICE
#endif //TELETEXT_SERVICE
#ifdef NVOD_REFERENCE_SERVICE
#undef NVOD_REFERENCE_SERVICE
#endif //NVOD_REFERENCE_SERVICE
#ifdef NVOD_TIMESHIFTED_SERVICE
#undef NVOD_TIMESHIFTED_SERVICE
#endif //NVOD_TIMESHIFTED_SERVICE
#ifdef MOSAIC_SERVICE
#undef MOSAIC_SERVICE
#endif //MOSAIC_SERVICE
#ifdef DATABROADCAST_SERVICE
#undef DATABROADCAST_SERVICE
#endif //DATABROADCAST_SERVICE
#ifdef DVBMHP_SERVICE
#undef DVBMHP_SERVICE
#endif //DVBMHP_SERVICE
#ifdef START_PRESET
#undef START_PRESET
#endif //START_PRESET
#ifdef MAX_NONHONOURED_PRESET
#undef MAX_NONHONOURED_PRESET
#endif //MAX_NONHONOURED_PRESET
#ifdef RADIO_START_PRESET
#undef RADIO_START_PRESET
#endif //RADIO_START_PRESET
#ifdef PRESET_NOT_ALLOCATED(presetno)
#undef PRESET_NOT_ALLOCATED(presetno)
#endif //PRESET_NOT_ALLOCATED(presetno)
#ifdef IS_UNINSTALLED_PRESET(svcdat)
#undef IS_UNINSTALLED_PRESET(svcdat)
#endif //IS_UNINSTALLED_PRESET(svcdat)
#ifdef IS_INTERESTED_LCN_RANGE(lcn)
#undef IS_INTERESTED_LCN_RANGE(lcn)
#endif //IS_INTERESTED_LCN_RANGE(lcn)
#ifdef IS_SPECIAL_SERVICE(lcn)
#undef IS_SPECIAL_SERVICE(lcn)
#endif //IS_SPECIAL_SERVICE(lcn)
#ifdef START_PRESET_FOR_SPECIAL_SERVICE
#undef START_PRESET_FOR_SPECIAL_SERVICE
#endif //START_PRESET_FOR_SPECIAL_SERVICE
#ifdef LAST_PRESET_FOR_SPECIAL_SERVICE
#undef LAST_PRESET_FOR_SPECIAL_SERVICE
#endif //LAST_PRESET_FOR_SPECIAL_SERVICE
#ifdef INSTALL_VERSION
#undef INSTALL_VERSION
#endif //INSTALL_VERSION
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#endif //LOCAL_UNDEFINES
