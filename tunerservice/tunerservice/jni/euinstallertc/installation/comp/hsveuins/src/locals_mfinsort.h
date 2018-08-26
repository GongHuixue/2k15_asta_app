#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
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

#define		RADIO_PRESET_OFFSET					(1000)

#define		PRESET_NOT_ALLOCATED(PresetNumber)		(((PresetNumber) == INVALID_PRESET) || ((PresetNumber) == 0XFFFD ))

#define     MAX_LCN_VALUE                       ( 2000 )

#define     VALID_PRESET_RANGE(num)             ( (num > 0) && (num < MAX_LCN_VALUE) )

#define     IS_VISIBLE_SERVICE(svcdat)          ( ((svcdat).VisibleService == TRUE) && ((svcdat).UserHidden == FALSE) )

#define     IS_NOT_USER_INSTALLED(tsdat)        ( (tsdat).UserInstalled == FALSE )

#define     NON_HONOURED_START_PRESET           ( eurdiv_NonRadioStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(PRESET_TABLE)) )

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

#define     ADD_ENTRY                           (0)

#define     UPDATE_ENTRY                        (1)

#define     START_PRESET                        (1)

#define     INSTALL_VERSION                     (rins_GetInstallationVersion())

#define     MIN_FREQUENCYDRIFT                  (3 * 16) /* 6 MHz is the band */

#define		DELTASSI						    ( eurdiv_GetDeltaSSI() )

#define		DELTASQI							( eurdiv_GetDeltaSQI() )

#define 	IS_RADIO_SERVICE(x)                 ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService))

#define 	ASSIGN_PRESET_NUMBER(x, y)          (IS_RADIO_SERVICE(y) ? ((x) + (RADIO_PRESET_OFFSET)):(x))

#define     SERVICE_TYPE_NONE                   (0xFFFF)

#define     CURRENT_PRESET(svcType)                     ( IS_RADIO_SERVICE(svcType)? mCurrentRadioPreset : mCurrentTvPreset )

#define     NONRADIO_ENDPRESET                  ( eurdiv_NonRadioEndPreset(sysset_GetSystemCountry(), rins_GetMedium()) )

#define DEFAULT_NONRADIOSTARTPRESET                 ( 1 )

#define DEFAULT_RADIOSTARTPRESET                    ( MAX_LCN_VALUE + 1 )

#define DEFAULT_PRESET_RANGE(FromPreset, ToPreset)  { FromPreset = IS_RADIO_SERVICE(ServiceType)? DEFAULT_RADIOSTARTPRESET : DEFAULT_NONRADIOSTARTPRESET; \
                                                      ToPreset   = IS_RADIO_SERVICE(ServiceType)? RADIO_ENDPRESET : NONRADIO_ENDPRESET; }
                                                      /* start & end point of all presets */

#define ANALOG_ENDPRESET                    ( eurdiv_AnalogEndPreset(sysset_GetSystemCountry(), rins_GetMedium())   )

#define NONRADIO_ENDPRESET                  ( eurdiv_NonRadioEndPreset(sysset_GetSystemCountry(), rins_GetMedium()) )

#define RADIO_ENDPRESET                     ( eurdiv_RadioEndPreset(sysset_GetSystemCountry(), rins_GetMedium())    )

#define IS_DIGITAL_SERVICE(svcType)                 ( svcType != SERVICE_TYPE_NONE )

#define     CURRENT_PRESET_VALID(preset, svcType)       ( !mIsCurrentPresetInvalid(preset, svcType) )

typedef enum
{
    evStep1 = 0,
    evStep2,
    evStep3,
    evStep4,
    evStepComplete,
    evNoSorting,
}SortSteps;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mfinsortPmp;
static Pump s__mfinsortPmp;
int mFirstInstalledPreset,mCurrentTvPreset,mCurrentRadioPreset;
static int s__mFirstInstalledPreset,s__mCurrentTvPreset,s__mCurrentRadioPreset;
int mServicePriority[MAX_SERVICE_TYPES];
static int s__mServicePriority[MAX_SERVICE_TYPES];
void mFinSortHandler(int value, Nat32 param);
void mNoSorting(int evCurrentSortStep);
void mSortHonouredServices(int evCurrentSortStep);
Bool mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
Bool mUpdateDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat,Nat8 i);
void mSortNonHonouredServices(int evCurrentSortStep, Bool CheckForCurrentOnId);
Bool mPresetAllocated(HsvPgdatDigServiceData *svcdat);
void mDigitalPresetEntryforInValidLCN(int dbindex);
void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate,Nat8 index);
void mSortAnalogServices(int evCurrentSortStep);
inline void mFindPresetNumberForService(int AnalogOrDigital,int ServiceType);
inline int mPlaceNonHonouredOrAnalogServices(int AnalogOrDigital,int ServiceType);
void mReInnovateFromPreset(int ServiceType, int *FromPreset);
inline int mLastLCNBasedPreset(Bool CheckForRadioServices);
int mLargestGapInForwardRange(int FromPreset, int ToPreset);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp( Nat16 * str1, Nat16 * str2 );
int mGetServicePriority(int serviceType);
Bool mIsPresetOccupied(int PresetNumber);
Bool mValidLCN(HsvPgdatDigServiceData *psvcdat);
int mGetAutomaticPlatformPresetNumber(void);
Bool mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat);
int mConvertToDVBServiceType(int servicetype);
Bool mCompareMultiplex(HsvPgdatDigTSData oldtsdata, HsvPgdatDigTSData tsdata);
Bool mIsCurrentPresetInvalid( int PresetNo, int ServiceType);
Bool mValidPresetForService(int presetnum, int svcType);
int mAnalogStartPreset(void);
int mNonRadioStartPreset(void);
int mRadioStartPreset(void);
void mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset);
void module__init(void){
	mfinsortPmp	=	s__mfinsortPmp;
	mFirstInstalledPreset	=	s__mFirstInstalledPreset;
	mCurrentTvPreset	=	s__mCurrentTvPreset;
	mCurrentRadioPreset	=	s__mCurrentRadioPreset;
	memcpy((void*)mServicePriority,(void*)s__mServicePriority,sizeof(mServicePriority));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
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
#ifdef CURRENT_INSTALL_VERSION
#undef CURRENT_INSTALL_VERSION
#endif //CURRENT_INSTALL_VERSION
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
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef ANALOG_TABLE
#undef ANALOG_TABLE
#endif //ANALOG_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef RADIO_PRESET_OFFSET
#undef RADIO_PRESET_OFFSET
#endif //RADIO_PRESET_OFFSET
#ifdef PRESET_NOT_ALLOCATED(PresetNumber)
#undef PRESET_NOT_ALLOCATED(PresetNumber)
#endif //PRESET_NOT_ALLOCATED(PresetNumber)
#ifdef MAX_LCN_VALUE
#undef MAX_LCN_VALUE
#endif //MAX_LCN_VALUE
#ifdef VALID_PRESET_RANGE(num)
#undef VALID_PRESET_RANGE(num)
#endif //VALID_PRESET_RANGE(num)
#ifdef IS_VISIBLE_SERVICE(svcdat)
#undef IS_VISIBLE_SERVICE(svcdat)
#endif //IS_VISIBLE_SERVICE(svcdat)
#ifdef IS_NOT_USER_INSTALLED(tsdat)
#undef IS_NOT_USER_INSTALLED(tsdat)
#endif //IS_NOT_USER_INSTALLED(tsdat)
#ifdef NON_HONOURED_START_PRESET
#undef NON_HONOURED_START_PRESET
#endif //NON_HONOURED_START_PRESET
#ifdef MAX_SERVICE_TYPES
#undef MAX_SERVICE_TYPES
#endif //MAX_SERVICE_TYPES
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
#ifdef MIN_FREQUENCYDRIFT
#undef MIN_FREQUENCYDRIFT
#endif //MIN_FREQUENCYDRIFT
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef START_FREQUENCY
#undef START_FREQUENCY
#endif //START_FREQUENCY
#ifdef END_FREQUENCY
#undef END_FREQUENCY
#endif //END_FREQUENCY
#ifdef ADD_ENTRY
#undef ADD_ENTRY
#endif //ADD_ENTRY
#ifdef UPDATE_ENTRY
#undef UPDATE_ENTRY
#endif //UPDATE_ENTRY
#ifdef START_PRESET
#undef START_PRESET
#endif //START_PRESET
#ifdef INSTALL_VERSION
#undef INSTALL_VERSION
#endif //INSTALL_VERSION
#ifdef MIN_FREQUENCYDRIFT
#undef MIN_FREQUENCYDRIFT
#endif //MIN_FREQUENCYDRIFT
#ifdef DELTASSI
#undef DELTASSI
#endif //DELTASSI
#ifdef DELTASQI
#undef DELTASQI
#endif //DELTASQI
#ifdef IS_RADIO_SERVICE(x)
#undef IS_RADIO_SERVICE(x)
#endif //IS_RADIO_SERVICE(x)
#ifdef ASSIGN_PRESET_NUMBER(x,
#undef ASSIGN_PRESET_NUMBER(x,
#endif //ASSIGN_PRESET_NUMBER(x,
#ifdef SERVICE_TYPE_NONE
#undef SERVICE_TYPE_NONE
#endif //SERVICE_TYPE_NONE
#ifdef CURRENT_PRESET(svcType)
#undef CURRENT_PRESET(svcType)
#endif //CURRENT_PRESET(svcType)
#ifdef NONRADIO_ENDPRESET
#undef NONRADIO_ENDPRESET
#endif //NONRADIO_ENDPRESET
#ifdef DEFAULT_NONRADIOSTARTPRESET
#undef DEFAULT_NONRADIOSTARTPRESET
#endif //DEFAULT_NONRADIOSTARTPRESET
#ifdef DEFAULT_RADIOSTARTPRESET
#undef DEFAULT_RADIOSTARTPRESET
#endif //DEFAULT_RADIOSTARTPRESET
#ifdef DEFAULT_PRESET_RANGE(FromPreset,
#undef DEFAULT_PRESET_RANGE(FromPreset,
#endif //DEFAULT_PRESET_RANGE(FromPreset,
#ifdef ANALOG_ENDPRESET
#undef ANALOG_ENDPRESET
#endif //ANALOG_ENDPRESET
#ifdef NONRADIO_ENDPRESET
#undef NONRADIO_ENDPRESET
#endif //NONRADIO_ENDPRESET
#ifdef RADIO_ENDPRESET
#undef RADIO_ENDPRESET
#endif //RADIO_ENDPRESET
#ifdef IS_DIGITAL_SERVICE(svcType)
#undef IS_DIGITAL_SERVICE(svcType)
#endif //IS_DIGITAL_SERVICE(svcType)
#ifdef CURRENT_PRESET_VALID(preset,
#undef CURRENT_PRESET_VALID(preset,
#endif //CURRENT_PRESET_VALID(preset,
#endif //LOCAL_UNDEFINES
