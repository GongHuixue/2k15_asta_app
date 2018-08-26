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
 *  %name: hsveuins_Italy.h %
 *  %version: TVG_Fusion_3 %
 *  %date_modified: Mon Apr 06 16:38:28 2010 %
 *  %derived_by: nareshj %
 */
 
#include <unistd.h> 
#include <ctype.h>

/*****   GENERIC MACROS   *****/
#define     CURRENT_MODE                        ( rins_GetInstallationMode() ) 
#define     AUTO_MODE                           ( rins_InstallationModeAutomatic )
#define     UPDATE_MODE                         ( rins_InstallationModeUpdate )
#define     MANUAL_MODE                         ( rins_InstallationModeWeakSignal )
#define     BACKGROUND_MODE                     ( rins_InstallationModeBackground )
#define     CURRENT_INSTALL_VERSION             ( rins_GetInstallationVersion() )

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
#define     VALIDLCNRANGE(svcdat)               ( ((svcdat).LCN > 0) && ((svcdat).LCN < 1000) )
#define     IS_VISIBLE_SERVICE(svcdat)          ( ((svcdat).VisibleService == TRUE)/* && ((svcdat).UserHidden == FALSE)*/ )
#define     IS_NOT_USER_INSTALLED(tsdat)        ( (tsdat).UserInstalled == FALSE )
#define     NON_HONOURED_START_PRESET           ( eurdiv_NonRadioStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(PRESET_TABLE)) )
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
#define     REVERSE_DIRECTION                   (-1)
#define     FORWARD_DIRECTION                   (1)
#define     START_PRESET                        (1)
#define     INSTALL_VERSION                     (rins_GetInstallationVersion())

/*****   GLOBAL VARIABLES   *****/
static Pump mitasortPmp;
static Bool mConflictDetected                    = FALSE;
static int  mCurrentPresetIndex = INVALID_PRESET, mFirstInstalledPreset = 0xFFFF;

/*****   Local Structures and enums   *****/

typedef enum
{
    evAutonomousSortHonoured = 0,
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
static void mItaSortHandler(int value, Nat32 param);

static int  mStrCmp(Nat16 *str1, Nat16 *str2);
static Bool mIsPresetOccupied(int PresetNumber);
static int  mGetServicePriority(int serviceType);
static int mGetAutomaticPlatformPresetNumber(void);
static int  mPlaceNonHonouredOrAnalogServices(void);
static void mAutonomousSortingHonouredServices(void);
static void mSortAnalogServices(int evCurrentSortStep);
static void mSortHonouredServices(int evCurrentSortStep);
static void mDigitalPresetEntryforInValidLCN(int dbindex);
static void mSortNonHonouredServices(int evCurrentSortStep);
static void mConflictDetection(HsvPgdatDigServiceData *svcdat);
static Bool mCanServiceBeHonoured(HsvPgdatDigServiceData *svcdat);
static int  mFirstGapInForwardRange(int FromPreset, int ToPreset);
static int  mFirstGapInReverseRange(int FromPreset, int ToPreset);
static Bool mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat);
static inline void mFindPresetNumberForService(int AnalogOrDigital);
static void mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
static int  mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
static void mAutonomousDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
static void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);
static int mNonHounouredDirection = FORWARD_DIRECTION;

/*****   Static functions   *****/

static int mConvertToDVBServiceType(int servicetype)
{
    int retval = servicetype;
    switch(servicetype)
    {
        case AppApiTelevisionService:     
            retval  =   TV_SERVICE;
            break;
        case AppApiRadioService:        
            retval  =   RADIO_SERVICE;
            break;
        case AppApiTeletextService:         
            retval  =   TELETEXT_SERVICE;
            break;
        case AppApiNVODReferenceService:         
            retval  =   NVOD_REFERENCE_SERVICE;
            break;
        case AppApiNVODTimeshiftedService:         
            retval  =   NVOD_TIMESHIFTED_SERVICE;
            break;
        case AppApiMosaicService:        
            retval  =   MOSAIC_SERVICE;
            break;
        case AppApiDatabroadcastService:        
            retval  =   DATABROADCAST_SERVICE;
            break;
        case AppApiDVBMHPService:        
            retval  =   DVBMHP_SERVICE;
            break;
        case AppApiMPEG2HDService:        
            retval  =   MPEG2HDService;
            break;
        case AppApiAdvCodecSDTelevisionService:        
            retval  =   AdvCodecSDTelevisionService;
            break;
        case AppApiAdvCodecSDNVODTimeShiftedService:        
            retval  =   AdvCodecSDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecSDNVODReferenceService:        
            retval  =   AdvCodecSDNVODReferenceService;
            break;
        case AppApiAdvCodecHDTelevisionService:        
            retval  =   AdvCodecHDTelevisionService;
            break;
        case AppApiAdvCodecHDNVODTimeShiftedService:        
            retval  =   AdvCodecHDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecHDNVODReferenceService:        
            retval  =   AdvCodecHDNVODReferenceService;
            break;      
		case AppApi3DHDDigitalService:
			retval =    HD3DDigitalService;
			break;
        default:
            break;        
    }
    return retval;
}
