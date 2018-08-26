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

#define     PRESET_NOT_ALLOCATED(svcdat)        ( (svcdat).PresetNumber == INVALID_PRESET )

#define     MAX_LCN_VALUE                       ( 1000 )

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



#define     ADD_ENTRY                           (0)

#define     UPDATE_ENTRY                        (1)

#define     START_PRESET                        (1)

#define     INSTALL_VERSION                     (rins_GetInstallationVersion())

#define     ANALOG_STARTPRESET                  (eurdiv_AnalogStartPreset(sysset_GetSystemCountry(), rins_GetMedium(), pgdb_GetNoRecords(SERVICE_TABLE) ) - 1)

#define     MIN_FREQUENCYDRIFT                  (3 * 16) /* 6 MHz is the band */

#define     DELTASSI                            ( eurdiv_GetDeltaSSI() )

#define     DELTASQI                            ( eurdiv_GetDeltaSQI() )

#define     pen_PumpEngine 0

#define     VALID_LCN_RANGE_APMEA(LCN)   ((sysset_GetSystemCountry()==cids_CountryAustralia)?(350>LCN && LCN>0 ||(1000>LCN && LCN>399)):(800>LCN && LCN>0))

#define  	NON_HONOURED_END_PRESET				((sysset_GetSystemCountry()==cids_CountryAustralia)?399:div_MaxValidLCNValue)
#define  	ANALOG_END_PRESET					(div_MaxValidLCNValue)



/**************Australia spcific changes***************/

#define    	MAX_AUS_BROADCASTER (17)
#define	 	Australian_DTTB_Reference_Free_TV_Australia (0x2024)
#define		ABC_Australian_Broadcasting_Corporation	(0x1010)
#define		SBS_SBS_Australia (0x1011)
#define		Nine_Network_Australia_Nine_Network_Australia (0x1012)
#define		Seven_Network_Australia_Seven_Network_Limited (0x1013)
#define 	Network_TEN_Australia_Network_TEN_Limited (0x1014)
#define		WIN_Television_Australia_WIN_Television_Pty_Ltd (0x1015)
#define 	Prime_Television_Australia_Prime_Television_Limited (0x1016)
#define 	Southern_Cross_Broadcasting (0x1017)
#define 	Reserved_for_Australian (0x1018)
#define 	NBN_Television_Australia_NBN_Television_Limited (0x1019)
#define 	Imparja_Television_Australia_Imparja_Television_Australia (0x101A)
#define 	West_DigitalWest_Digital (0x101B)
#define 	Reserved_for_Australian_broadcasters1 (0x101C)
#define 	Reserved_for_Australian_broadcasters2 (0x101D)
#define 	Reserved_for_Australian_broadcasters3 (0x101E)
#define 	Reserved_for_Australian_broadcasters4 (0x101F)
#define 	NZ_VALID_ONID    (0x222A)
#define 	SGP_VALID_ONID   (0x22BE)
#define		MLY_VALID_ONID   (0x21CA)
#define		THAI_VALID_ONID  (0x22FC)
#define		TAIWAN_VALID_ONID (0x209E)
#define 	IDN_VALID_ONID 	(0x2168)
/*****   GLOBAL VARIABLES   *****/

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
Pump mdvbtsortPmp;
static Pump s__mdvbtsortPmp;
int mCurrentPresetIndex,mFirstInstalledPreset;
static int s__mCurrentPresetIndex,s__mFirstInstalledPreset;
int mServicePriority[MAX_SERVICE_TYPES];
int mAUSValidOnid[MAX_AUS_BROADCASTER];
static int s__mServicePriority[MAX_SERVICE_TYPES];
static int s__mAUSValidOnid[MAX_AUS_BROADCASTER];
void mNoSorting(int evCurrentSortStep);
void mDvbtSortHandler(int value, Nat32 param);
void mSortHonouredServices(int evCurrentSortStep);
Bool mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
Bool mUpdateDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
void mSortNonHonouredServices(int evCurrentSortStep, Bool CheckForCurrentOnId);
void mDigitalPresetEntryforInValidLCN(int dbindex);
void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);
void mSortAnalogServices(int evCurrentSortStep);
inline void mFindPresetNumberForService(int AnalogOrDigital);
inline int mPlaceNonHonouredOrAnalogServices(int AnalogOrDigital);
inline int mLastLCNBasedPreset(void);
int mLargestGapInForwardRange(int FromPreset, int ToPreset);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp( Nat16 * str1, Nat16 * str2 );
int mGetServicePriority(int serviceType);
Bool mIsPresetOccupied(int PresetNumber);
int mGetAutomaticPlatformPresetNumber(void);
Bool mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat);
int mConvertToDVBServiceType(int servicetype);
Bool mCompareMultiplex(HsvPgdatDigTSData oldtsdata, HsvPgdatDigTSData tsdata);
void module__init(void){
	mdvbtsortPmp	=	s__mdvbtsortPmp;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	mFirstInstalledPreset	=	s__mFirstInstalledPreset;
	memcpy((void*)mServicePriority,(void*)s__mServicePriority,sizeof(mServicePriority));
	memcpy((void*)mAUSValidOnid,(void*)s__mAUSValidOnid,sizeof(mAUSValidOnid));
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
#ifdef PRESET_NOT_ALLOCATED(svcdat)
#undef PRESET_NOT_ALLOCATED(svcdat)
#endif //PRESET_NOT_ALLOCATED(svcdat)
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
#ifdef ANALOG_STARTPRESET
#undef ANALOG_STARTPRESET
#endif //ANALOG_STARTPRESET
#ifdef MIN_FREQUENCYDRIFT
#undef MIN_FREQUENCYDRIFT
#endif //MIN_FREQUENCYDRIFT
#ifdef HD_LCN(svcdat)
#undef HD_LCN(svcdat)
#endif //HD_LCN(svcdat)
#ifdef HD_LCN1(svcdat)
#undef HD_LCN1(svcdat)
#endif //HD_LCN1(svcdat)
#ifdef DELTASSI
#undef DELTASSI
#endif //DELTASSI
#ifdef DELTASQI
#undef DELTASQI
#endif //DELTASQI
#endif //LOCAL_UNDEFINES
