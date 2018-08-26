#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

/*****   GENERIC MACROS   *****/

#define     DP(str)                 //printf str

#define     START_PRESET            (1)  

#define     MAX_PRESET              (1000)

#define     LARGER(a,b)             ((a>b)?a:b)

#define     AUTO_INSTALL            (CURRENT_MODE == AUTO_MODE)

#define     UPDATE_INSTALL          (CURRENT_MODE == UPDATE_MODE)

#define     MANUAL_INSTALL          (CURRENT_MODE == MANUAL_MODE)

#define     ANALOG_MANUAL_INSTALL   (CURRENT_MODE == ANALOG_MANUAL) 

#define     BACKGROUND_INSTALL      (CURRENT_MODE == BACKGROUND_MODE)

#define     AUTO_MODE               (rins_InstallationModeAutomatic)

#define     UPDATE_MODE             (rins_InstallationModeUpdate)

#define     MANUAL_MODE             (rins_InstallationModeWeakSignal)

#define     CURRENT_MODE            (rins_GetInstallationMode())

#define     BACKGROUND_MODE         (rins_InstallationModeBackground) 

#define     ANALOG_MANUAL           (rins_InstallationModeManual)

#define     PTC_TABLE               (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)

#define     PRESET_TABLE            (pgdb_GetCurrentTable() | pgdbconst_Preset)

#define     SERVICE_TABLE           (pgdb_GetCurrentTable() | pgdbconst_DigitalService)

#define     ANALOG_TABLE            (pgdb_GetCurrentTable() | pgdbconst_Analog)

#define     MIN_FREQUENCYDRIFT      (3 * 16) /* 6 MHz is the band*/

#define     INSTALL_VERSION         (rins_GetInstallationVersion())

#define     PRESET_NOT_ALLOCATED(svcdat)        ( (svcdat).PresetNumber == INVALID_PRESET )

typedef enum 
{
    evAnalogStep,
    evDigitalStep,
    evSortComplete,
    evNoSorting,
}mpegEvents;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mFirstInstalledPreset;
static int s__mFirstInstalledPreset;
Pump mMpegSortPmp;
static Pump s__mMpegSortPmp;
void mNoSorting(int evCurrentSortStep);
void mMpegSortHandler(int value, Nat32 param);
inline Bool IsFreqUserInstalled(Nat32 Frequency, Nat16 StreamPriority);
inline Bool CompareIfAnalog(Address data);
inline Bool CompareIfDigital( Address data);
void AssignAnalogPresets(void);
void AssignDigitalPresets(void);
int GetAutomaticPlatformPresetNumber(void);
void mMoveDigitalBlock(Nat16 FromPreset);
inline Nat16 mGetLastPresetInChannelList(void);
Nat16 mFindLargestGapInPresetList(int *GapSize);
void module__init(void){
	mFirstInstalledPreset	=	s__mFirstInstalledPreset;
	mMpegSortPmp	=	s__mMpegSortPmp;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef DP(str)
#undef DP(str)
#endif //DP(str)
#ifdef START_PRESET
#undef START_PRESET
#endif //START_PRESET
#ifdef MAX_PRESET
#undef MAX_PRESET
#endif //MAX_PRESET
#ifdef LARGER(a,b)
#undef LARGER(a,b)
#endif //LARGER(a,b)
#ifdef AUTO_INSTALL
#undef AUTO_INSTALL
#endif //AUTO_INSTALL
#ifdef UPDATE_INSTALL
#undef UPDATE_INSTALL
#endif //UPDATE_INSTALL
#ifdef MANUAL_INSTALL
#undef MANUAL_INSTALL
#endif //MANUAL_INSTALL
#ifdef ANALOG_MANUAL_INSTALL
#undef ANALOG_MANUAL_INSTALL
#endif //ANALOG_MANUAL_INSTALL
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef ANALOG_MANUAL
#undef ANALOG_MANUAL
#endif //ANALOG_MANUAL
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef ANALOG_TABLE
#undef ANALOG_TABLE
#endif //ANALOG_TABLE
#ifdef MIN_FREQUENCYDRIFT
#undef MIN_FREQUENCYDRIFT
#endif //MIN_FREQUENCYDRIFT
#ifdef INSTALL_VERSION
#undef INSTALL_VERSION
#endif //INSTALL_VERSION
#ifdef PRESET_NOT_ALLOCATED(svcdat)
#undef PRESET_NOT_ALLOCATED(svcdat)
#endif //PRESET_NOT_ALLOCATED(svcdat)
#endif //LOCAL_UNDEFINES
