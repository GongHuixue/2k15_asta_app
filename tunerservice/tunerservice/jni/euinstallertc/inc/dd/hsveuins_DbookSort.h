/*
 *  Copyright(C) 2009 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *  %name: hsveuins_DbookSort.h %
 *  %version: TVG_Fusion_1 %
 *  %date_modified: Mon Apr 06 16:38:28 2010 %
 *  %derived_by: lakshminb %
 */

#include <unistd.h> 
#include <ctype.h>


/*****   GENERIC MACROS   *****/
#define     CURRENT_MODE                        ( rins_GetInstallationMode() ) 
#define     AUTO_MODE                           ( rins_InstallationModeAutomatic )
#define     UPDATE_MODE                         ( rins_InstallationModeUpdate )
#define     MANUAL_MODE                         ( rins_InstallationModeWeakSignal )
#define     BACKGROUND_MODE                     ( rins_InstallationModeBackground )
#define     INSTALL_VERSION                     (rins_GetInstallationVersion())

#define     AUTO_INSTALL                        ( (CURRENT_MODE) == (AUTO_MODE) )
#define     UPDATE_INSTALL                      ( (CURRENT_MODE) == (UPDATE_MODE) )
#define     MANUAL_INSTALL                      ( (CURRENT_MODE) == (MANUAL_MODE) )
#define     BACKGROUND_INSTALL                  ( (CURRENT_MODE) == (BACKGROUND_MODE) )

#define     CURRENT_TABLE                       ( pgdb_GetCurrentTable() )
#define     PRESET_TABLE                        ( CURRENT_TABLE | pgdbconst_Preset )
#define     ANALOG_TABLE                        ( CURRENT_TABLE | pgdbconst_Analog )
#define     PTC_TABLE                           ( CURRENT_TABLE | pgdbconst_DigitalTS )
#define     SERVICE_TABLE                       ( CURRENT_TABLE | pgdbconst_DigitalService )

#define     PRESET_NOT_ALLOCATED(svcdat)        ( (svcdat).PresetNumber == INVALID_PRESET )
#define     VALID_PRESET_RANGE(num)             ( (num > 0) && (num < 1000) )
#define     IS_VISIBLE_SERVICE(svcdat)          ( ((svcdat).VisibleService == TRUE) && ((svcdat).UserHidden == FALSE) )
#define     IS_NOT_USER_INSTALLED(tsdat)        ( (tsdat).UserInstalled == FALSE )
#define     MAX_PRESET_NUM                      ( 1000 ) 
#define     MAX_SERVICE_TYPES                   ( 8 )
#define     TV_SERVICE                          ( TelevisionService )
#define     RADIO_SERVICE                       ( RadioService )
#define     TELETEXT_SERVICE                    ( TeletextService )
#define     NVOD_REFERENCE_SERVICE              ( NVODReferenceService )
#define     NVOD_TIMESHIFTED_SERVICE            ( NVODTimeShiftedService )
#define     MOSAIC_SERVICE                      ( MosaicService )
#define     DATABROADCAST_SERVICE               ( DatabroadcastService )
#define     DVBMHP_SERVICE                      ( DVBMHPService )
#define     MIN_FREQUENCYDRIFT                  (3 * 16)            /* 6 MHz is the band*/
#define     WINDOWID                            (wnddest_GetWindowId(HsvMain))
#define     START_FREQUENCY                     ((44) * (16))
#define     END_FREQUENCY                       ((862) * (16))
#define     ADD_ENTRY                           ( 0 )
#define     UPDATE_ENTRY                        ( 1 )
#define     NON_HONOURED_START_PRESET           (eurdiv_NonRadioStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE) ))
#define     ANALOG_START_PRESET                 (eurdiv_AnalogStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE)   ))
#define     DEFAULT_START_PRESET                ( 1 )
#define     NO_PASS                             ( 0 )
#define     FIRST_PASS                          ( 1 )
#define     LAST_PASS                           ( 2 )
#define     MANUAL_INSTALL_PRESET(NewPreset,Presetnumber)     (((NewPreset)==TRUE)&&((Presetnumber)==INVALID_PRESET))

/*****   GLOBAL VARIABLES   *****/
static      Pump mdvbtsortPmp;

static Bool mConflictDetected   = FALSE;
static int  mConflictResolutionPass = NO_PASS;
static int  mCurrentPresetIndex = INVALID_PRESET, mFirstInstalledPreset = INVALID_PRESET, mInstallationVersion;
/*****   Local Structures and enums   *****/

typedef enum
{
    evStep0 = 0,
    evStep1,
    evStep2,
    evStep3,
    evStep4,
    evStepComplete,
    evNoSorting,
}SortSteps;

static int mServicePriority[MAX_SERVICE_TYPES] =
{
/* Priority is in increasing order. Refer to honouring rules sheet of vsd  */
    AppApiDatabroadcastService,
    AppApiTeletextService,
    AppApiRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiAdvCodecSDTelevisionService,
    AppApiAdvCodecHDTelevisionService   
};

/*****   static function prototypes   *****/
static void mDvbtSortHandler(int value, Nat32 param);

static int  mStrCmp(Nat16 *str1, Nat16 *str2);
static int  mGetServicePriority(int serviceType);
static int  mGetCurrentInstallationVersion(void);
static int  mGetAutomaticPlatformPresetNumber(void);
static inline Bool mIsPresetOccupied(int PresetNumber);
static void mSortAnalogServices(int evCurrentSortStep);

static void mDigitalPresetEntryforInValidLCN(int dbindex);
static void mSortNonHonouredServices(int evCurrentSortStep);
static int  mFindFirstGapInRange(int FromPreset, int ToPreset);
static void mSortHDAndSDConflictServices(int evCurrentSortStep);
static Bool mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat);
static inline void mFindPresetNumberForService(int AnalogOrDigital);
static void mSortHonouredServices(int evCurrentSortStep, Bool CheckForHDLCN);
static int  mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
static Bool mConflictDetection(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN);
static Bool mCanServiceBeHonoured(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN);
static Bool mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN);
static void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);

