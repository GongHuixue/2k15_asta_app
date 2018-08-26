#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <errno.h>

#include <sys/types.h>

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

#define BACKGROUND_MODE                     ( rins_InstallationModeBackground )

#define ANALOG_MANUAL                       (rins_InstallationModeManual)

#define CURRENT_MODE                        (rins_GetInstallationMode()) 

#define AUTO_INSTALL                        ((CURRENT_MODE) == (AUTO_MODE))

#define UPDATE_INSTALL                      ((CURRENT_MODE) == (UPDATE_MODE))

#define MANUAL_INSTALL                      ((CURRENT_MODE) == (MANUAL_MODE))

#define BACKGROUND_INSTALL                  ( (CURRENT_MODE) == (BACKGROUND_MODE) )

/* Start point of radio services */

#define MAX_LCN_VALUE                                               (div_MaxLCNValue)

#define IS_RADIO_SERVICE(x)                                         ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService))

#define GETCURRENTINDEX(x)                                          (IS_RADIO_SERVICE(x) ? (mCurrentRadioIndex) : (mCurrentPresetIndex))

#define ASSIGN_PRESET_NUMBER(x, y)                                  (IS_RADIO_SERVICE(y) ? ((x) + (MAX_LCN_VALUE)):(x))

#define MAX_SERVICE_TYPES1           (8)

#define MAX_CHINA_SERVICE_TYPES     (12)

#define TV_SERVICE                  (TelevisionService)

#define RADIO_SERVICE               (RadioService)

#define TELETEXT_SERVICE            (TeletextService)

#define NVOD_REFERENCE_SERVICE      (NVODReferenceService)

#define NVOD_TIMESHIFTED_SERVICE    (NVODTimeShiftedService)

#define MOSAIC_SERVICE              (MosaicService)

#define DATABROADCAST_SERVICE       (DatabroadcastService)

#define DVBMHP_SERVICE              (DVBMHPService)

#define START_PRESET                        (1)

#define PRESET_NOT_ALLOCATED(presetno)      (presetno == INVALID_PRESET)

#define DVBC_DECODER_PRESETS                (feapi_ChanDecDvbC)

#define DVBT_DECODER_PRESETS                (feapi_ChanDecDvbT)

#define	CABLE_DEL_FILEPATH					"HsvCableDelSysDescFile"

#define MAX_CHARACTERS						(128)

#define IS_DIGITAL_PRESET(presetType)       ( presetType == HsvOnePart)

#define INSTALL_VERSION                     (rins_GetInstallationVersion())
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
    evStepAll,
    evNoSorting,
}SortSteps;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mLiteSortPmp;
static Pump s__mLiteSortPmp;
int mFirstInstalledPreset,mCurrentPresetIndex,mCurrentRadioIndex;
static int s__mFirstInstalledPreset,s__mCurrentPresetIndex,s__mCurrentRadioIndex;
int mServicePriority[MAX_SERVICE_TYPES1];
static int s__mServicePriority[MAX_SERVICE_TYPES1];
int mChinaServicePriority[MAX_CHINA_SERVICE_TYPES];
static int s__mChinaServicePriority[MAX_CHINA_SERVICE_TYPES];
void mNoSorting(int evCurrentSortStep);
void mLiteSortHandler(int value, Nat32 param);
void mSortAnalogPresets(int evCurrentSortStep);
void mSortDigitalHonouredPresets(Bool CheckForRadioServices, Nat32 DecoderType, int evCurrentSortStep);
void mSortDigitalNonHonouredPresets(Bool CheckForRadioServices, int evCurrentSortStep);
Bool mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
void mDigitalPresetEntryforInValidLCN(int dbindex);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp( Nat16 * str1, Nat16 * str2 );
int mGetServicePriority(int serviceType);
Bool CallBackHsvAnalog(Address data);
Bool IsFreqUserInstalled(Nat32 Frequency, Nat16 StreamPriority);
int ConvertToDVBServiceType(int servicetype);
inline int mLastNonRadioDigitalPreset(void);
inline int mLastLCNBasedPreset(Bool CheckForRadioServices);
inline int mFindPlaceForAnalogPresets(void);
int mLargestGapInForwardRange(int FromPreset, int ToPreset);
int GetAutomaticPlatformPresetNumber(void);
Bool mValidPresetRange(int SvcType, int presetno);
void module__init(void){
	mLiteSortPmp	=	s__mLiteSortPmp;
	mFirstInstalledPreset	=	s__mFirstInstalledPreset;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	mCurrentRadioIndex	=	s__mCurrentRadioIndex;
	memcpy((void*)mServicePriority,(void*)s__mServicePriority,sizeof(mServicePriority));
	memcpy((void*)mChinaServicePriority,(void*)s__mChinaServicePriority,sizeof(mChinaServicePriority));
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
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef ANALOG_MANUAL
#undef ANALOG_MANUAL
#endif //ANALOG_MANUAL
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
#ifdef ASSIGN_PRESET_NUMBER(x,
#undef ASSIGN_PRESET_NUMBER(x,
#endif //ASSIGN_PRESET_NUMBER(x,
#ifdef MAX_SERVICE_TYPES1
#undef MAX_SERVICE_TYPES1
#endif //MAX_SERVICE_TYPES1
#ifdef MAX_CHINA_SERVICE_TYPES
#undef MAX_CHINA_SERVICE_TYPES
#endif //MAX_CHINA_SERVICE_TYPES
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
#ifdef PRESET_NOT_ALLOCATED(presetno)
#undef PRESET_NOT_ALLOCATED(presetno)
#endif //PRESET_NOT_ALLOCATED(presetno)
#ifdef DVBC_DECODER_PRESETS
#undef DVBC_DECODER_PRESETS
#endif //DVBC_DECODER_PRESETS
#ifdef DVBT_DECODER_PRESETS
#undef DVBT_DECODER_PRESETS
#endif //DVBT_DECODER_PRESETS
#ifdef CABLE_DEL_FILEPATH
#undef CABLE_DEL_FILEPATH
#endif //CABLE_DEL_FILEPATH
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef IS_DIGITAL_PRESET(presetType)
#undef IS_DIGITAL_PRESET(presetType)
#endif //IS_DIGITAL_PRESET(presetType)
#ifdef INSTALL_VERSION
#undef INSTALL_VERSION
#endif //INSTALL_VERSION
#endif //LOCAL_UNDEFINES
