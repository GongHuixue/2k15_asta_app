#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <ctype.h>

#define START_FREQUENCY                     (108 * 16)
#define END_FREQUENCY                       (863 * 16)
#define WINDOWID                            (wnddest_GetWindowId(HsvMain))

#define CURRENT_TABLE                       (pgdb_GetCurrentTable() )
#define PTC_TABLE                           (CURRENT_TABLE | pgdbconst_DigitalTS)
#define SERVICE_TABLE                       (CURRENT_TABLE | pgdbconst_DigitalService)
#define ANALOG_TABLE                        (CURRENT_TABLE | pgdbconst_Analog)
#define PRESET_TABLE                        (CURRENT_TABLE | pgdbconst_Preset)

#define AUTO_MODE                           (rins_InstallationModeAutomatic)
#define UPDATE_MODE                         (rins_InstallationModeUpdate)
#define MANUAL_MODE                         (rins_InstallationModeWeakSignal)
#define ANALOG_MANUAL                       (rins_InstallationModeManual)

#define CURRENT_MODE                        (rins_GetInstallationMode()) 

#define AUTO_INSTALL                        ((CURRENT_MODE) == (AUTO_MODE))
#define UPDATE_INSTALL                      ((CURRENT_MODE) == (UPDATE_MODE))
#define MANUAL_INSTALL                      ((CURRENT_MODE) == (MANUAL_MODE))
#define ANALOG_MANUAL_INSTALL               ((CURRENT_MODE) == (ANALOG_MANUAL))

/* start & end point of all presets */
#define ANALOG_ENDPRESET                    ( eurdiv_AnalogEndPreset(sysset_GetSystemCountry(), rins_GetMedium())   )
#define NONRADIO_ENDPRESET                  ( eurdiv_NonRadioEndPreset(sysset_GetSystemCountry(), rins_GetMedium()) )
#define RADIO_ENDPRESET                     ( eurdiv_RadioEndPreset(sysset_GetSystemCountry(), rins_GetMedium())    )
#define DEFAULT_ANALOG_STARTPRESET			( eurdiv_AnalogStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE) ))

/* values harcoded as these are used only if preset allocation with previous presetrange(using above macros) is not possible */
#define DEFAULT_NONRADIOSTARTPRESET                 ( 1 )
#define DEFAULT_RADIOSTARTPRESET                    ( MAX_LCN_VALUE + 1 )
#define DEFAULT_PRESET_RANGE(FromPreset, ToPreset)  { FromPreset = IS_RADIO_SERVICE(ServiceType)? DEFAULT_RADIOSTARTPRESET : DEFAULT_NONRADIOSTARTPRESET; \
                                                      ToPreset   = IS_RADIO_SERVICE(ServiceType)? RADIO_ENDPRESET : NONRADIO_ENDPRESET; }
#define IS_NOT_USER_INSTALLED(tsdat)                ( (tsdat).UserInstalled == FALSE )
#define MAX_LCN_VALUE                                               (div_MaxLCNValue)
#define IS_RADIO_SERVICE(x)                                         ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )
#define MAX_SERVICE_TYPES                                           (9)
#define GETCURRENTINDEX(x)                                        	(IS_RADIO_SERVICE(x) ? (InsStatus.CurrentRadioIndex) : (InsStatus.CurrentPresetIndex))
#define ASSIGN_PRESET_NUMBER(x)                                     (((IS_SYSTEM_NETWORKOPERATOR_RCSRDS)||(IS_SYSTEM_NETWORKOPERATOR_Blizoo))?(x):(IS_RADIO_SERVICE(svcdat.ServiceType) ? ((x) + (MAX_LCN_VALUE)):(x)))
#define AUTOMATICPRESETALLOCATION(div,StartPreset,LastLCNPreset)    ((!div)? StartPreset : LastLCNPreset)
#define SERVICE_TYPE_NONE                                           (0xFFFF)
#define IS_SYSTEM_NETWORKOPERATOR_RCSRDS							((sysset_GetSystemCountry() == cids_CountryRomania)&&(rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkOperator) == rins_RCSRDS)? true : false)
#define IS_SYSTEM_NETWORKOPERATOR_Blizoo							(((sysset_GetSystemCountry() == cids_CountryBulgaria) )&&(rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkOperator) == rins_Blizoo))

#define RCSRDS_MinValidLCNValue    									(1)
#define RCSRDS_MaxValidLCNValue    									(1999)
#define VALID_LCN_RANGE_RCSRDS(x)									(((x) <= RCSRDS_MaxValidLCNValue) && ( RCSRDS_MinValidLCNValue <= (x)))

#define TV_SERVICE                  (TelevisionService)
#define RADIO_SERVICE               (RadioService)
#define TELETEXT_SERVICE            (TeletextService)
#define NVOD_REFERENCE_SERVICE      (NVODReferenceService)
#define NVOD_TIMESHIFTED_SERVICE    (NVODTimeShiftedService)
#define MOSAIC_SERVICE              (MosaicService)
#define DATABROADCAST_SERVICE       (DatabroadcastService)
#define DVBMHP_SERVICE              (DVBMHPService)
#define ADVANCE_RADIOCODEC_SERVICE 		(AdvCodecRadioService)

#define	CABLE_DEL_FILEPATH							"HsvCableDelSysDescFile"
#define MAX_CHARACTERS								(128)
#define KDG_NETWORK(NetworkId)                      ((NetworkId >= 0xF001) && (NetworkId <= 0xF01F))
#define KDB_NETWORK(NetworkId)                      (NetworkId == 0xA018) 
#define PRESET_NOT_ALLOCATED(svcdat)                ( (svcdat).PresetNumber == INVALID_PRESET )

#define CURRENT_PRESET(svcType)                     ( IS_RADIO_SERVICE(svcType)? mCurrentRadioPreset : mCurrentTvPreset )
#define IS_DIGITAL_SERVICE(svcType)                 ( svcType != SERVICE_TYPE_NONE )
#define IS_DIGITAL_PRESET(presetType)               ( presetType == HsvOnePart)
#define CURRENT_PRESET_VALID(preset, svcType)       ( !mIsCurrentPresetInvalid(preset, svcType) )   
#define INITIALIZE_ANALOG_ITEMS(anadat)             (anadat).ChannelLock = FALSE; (anadat).PreferredStereo  = 1;
#define INITIALIZE_DIGITAL_ITEMS(svcdat)            (svcdat).EPGEnabled = (svcdat).UserModifiedName = (svcdat).EPGShortInfo = (svcdat).UserHidden = FALSE; (svcdat).NewPreset = !AUTO_INSTALL;
#define SUCCESS                                     1
#define RETRY                                       2
#define NO_MORE_GAPFOUND                            3           
#define MIN_FREQUENCYDRIFT                          (3 * 16) /* 6 MHz is the band*/
#define ADD_ENTRY                                   ( 0 )
#define UPDATE_ENTRY                                ( 1 )
#define DECODER_TYPE_TERRESTRIAL                    (IHsvFrontEndApi_ChanDecDvbT)
#define DECODER_TYPE_CABLE                          (IHsvFrontEndApi_ChanDecDvbC)
#define ASSIGN_PRESET_NUMBER_FOR_DVBT(x)            ((IS_RADIO_SERVICE(svcdat.ServiceType) ? ((x) + (MAX_LCN_VALUE)):(x)))

/*************************************************************************
    Local Structures and enums
 **************************************************************************/

typedef enum
{
    evStaticSortingStep1 = 0,
    evStaticSortingStep2,
    evDynamicSortingStep1,
    evDynamicSortingStep2,
    evDynamicSortingStep3,
    evDynamicSortingStep4,
    evCommonStep1,
    evCommonStep2,
    evCommonStep3,
    evCommonStep4,
    evCommonStep5,
    evNonHonouredSortingRCSRDS,
    evNonHonouredSortingBlizoo,
    evComplete,
    evNoSorting,
}SortSteps;

static Nat16 mGermanyKDGHDRankingList[] =
{
#define SVC_ITEM(SVC_Name, SVC_Id)  SVC_Id
#include "GermanyKDGHDRankingList.h"
#undef  SVC_ITEM
};

static Nat16 mGermanyKDGSDRankingList[] =
{
#define SVC_ITEM(SVC_Name, SVC_Id)  SVC_Id
#include "GermanyKDGSDRankingList.h"
#undef  SVC_ITEM
};

static Nat16 mGermanyKDBRankingList[] = 
{
#define SVC_ITEM(SVC_Name, SVC_Id)  SVC_Id
#include "GermanyKDBRankingList.h"
#undef  SVC_ITEM
        
};

static int  mCurrentTvPreset = INVALID_PRESET, mCurrentRadioPreset = INVALID_PRESET, mFirstInstalledPreset = INVALID_PRESET,mCurrentPreset_InValidLCN_RCSRDS = 3000,mCurrentPreset_InValidLCN_Blizoo = 800;

/* module functions */
static void mCabsortHandler(int value, Nat32 param);
static void mSortAnalogServices(int evCurrentSortStep);
static void mSortHonouredServices(Bool CheckForRadioServices, int evCurrentSortStep, Nat32 decoderType);
static void mSortNonHonouredServices(Bool CheckForRadioServices, int evCurrentSortStep, Nat32 decoderType);
static void mSortNonHonouredServicesRCSRDS(int evCurrentSortStep);
static void mSortNonHonouredServicesBlizoo(int evCurrentSortStep);
static void mDigitalPresetEntryforInValidLCN_Blizoo(int dbindex);
static void mDigitalPresetEntryforValidLCN(int dbindex);
static void mDigitalPresetEntryforInValidLCN_RCSRDS(int dbindex);
static void mDigitalPresetEntryforInValidLCN(int dbindex);
static int mAddPresetEntryForInstalledAnalog(HsvPgdatAnalogData anadat, int PresetNumber);
static Bool mAddPresetEntryForNewAnalog(HsvPgdatAnalogData *anadat, int PresetNumber);
static int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
static int mStrCmp(Nat16 *str1, Nat16 *str2);
static int mGetServicePriority(int serviceType);
static void mReadCableDS(void);
static void mGetFileName(char *FileName, char *FilePath);
static void mDeleteTSByIndex(int index);
static void mAssignPresetsFromStaticTable(Bool CheckForRadioServices, int evCurrentSortStep);
static void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);
static Bool mIsPresetReplacable(HsvPgdatPresetData presetdat, HsvPgdatDigServiceData svcdat);
static inline void mFindPresetNumberForService(int ServiceType);
static void mAssignPresetNumberForService(int ServiceType);
static inline int mLastLCNBasedPreset(Bool CheckForRadioServices);
static int mLargestGapInForwardRange(int FromPreset, int ToPreset);
static Bool mValidPresetForService(int presetnum, int svcType);
static void mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset);
static void mReInnovateFromPreset(int ServiceType, int *FromPreset);
static Bool mTSInTransmission(void);
static inline int ANALOG_STARTPRESET(void);
static inline int NONRADIO_STARTPRESET(void);
static inline int RADIO_STARTPRESET(void);
static int mGetAutomaticPlatformPresetNumber(void);
static Bool mIsCurrentPresetInvalid( int PresetNo, int ServiceType);
static Bool mStaticSortingAvailable(Nat16 NetworkId);

/* module variables */
static Pump mCabsortPump;
static t_CableDSDesc mFlashCableDS;

/* Priority is in increasing order. Refer to honouring rules sheet of vsd  */
static int mServicePriority[MAX_SERVICE_TYPES] =
{
    AppApiDatabroadcastService,
    AppApiTeletextService,
    AppApiRadioService,
    AppApiAdvCodecRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiAdvCodecSDTelevisionService,
    AppApiAdvCodecHDTelevisionService   
};

/* static function impl.. */
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
		case AppApiAdvCodecRadioService:
			retval = ADVANCE_RADIOCODEC_SERVICE;
			break;
        default:
            break;
    }
    return retval;
}

static Nat32 mConvertDecoderType(Nat8 decoderType)
{
    Nat32 retVal = decoderType;

    switch(decoderType)
    {
        case IHsvFrontEndApi_ChanDecDvbT:
        case IHsvFrontEndApi_ChanDecDvbT2:
            retVal = DECODER_TYPE_TERRESTRIAL;
            break;
        case IHsvFrontEndApi_ChanDecDvbC:
            retVal = DECODER_TYPE_CABLE;
            break;
        default:
            break;
    }
    return retVal;
}


