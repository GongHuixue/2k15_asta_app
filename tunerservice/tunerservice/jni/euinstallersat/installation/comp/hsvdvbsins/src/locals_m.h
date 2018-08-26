#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#include <stdio.h>

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define TURNED_ON					(mModuleLifeCycle == TurnedOn)

#define MODE_NONE					(pins_InstallationNone)

#define AUTO_MODE					(pins_InstallationServiceScan)

#define UPDATE_MODE					(pins_InstallationUpdate)

#define AUTOUPDATE_MODE				(pins_InstallationAutomaticUpdate)

#define MANUAL_MODE					(pins_InstallationManual)

#define TRICOLOR_REGION_PARSING_MODE (pins_InstallationStateRegionScan)

#define PRESCAN_MODE				(pins_InstallationPreScan)

#define	ADDSAT_MODE					(pins_InstallationAddSatellite)

#define	BACKGROUND_MODE				(pins_InstallationBackground)

#define	BCKGNDUPDATE_MODE				(pins_InstallationBackgroundUpdate)

#define SSBYUPDATE_MODE			(pins_InstallationSSbyUpdate)

#define PACKAGE_PARSING_MODE                  (pins_InstallationPackageParsing)

#define CAM_NIT_INSTALLATION_MODE              (pins_InstallationCamNit)

#define MINIPRESCAN_MODE			(pins_InstallationMiniPrecan)

#define VALID_EVENT(event)			((event >= EvStart) && (event < EvMax))

#define VALID_STATE(state)			((state >= StIdle) && (state < StMax))

#define	SET_INS_STATE(state)		(InsStatus.State = state)

#define	GET_INS_STATE				(InsStatus.State)

#define	CURRENT_DATABASE_TABLE		(pgdbconst_Satellite)

#define	PTC_TABLE				    (pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	SAT_INFO_TABLE				(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	SERVICE_TABLE				(pgdbconst_Satellite | pgdbconst_DigitalService)

#define PRESET_TABLE				(pgdbconst_Satellite | pgdbconst_Preset)

#define	INTERACTIVE_SERVICE_TABLE				(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_InteractiveService)
#define	HOMING_SERVICE_TABLE					(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_HomingService)

#define INVALID_LNB                 (0xFFFF)

#define MAIN_VIDEO_WINDOW_TYPE      0

#define MAIN_AUDIO_WINDOW_TYPE      1

#define MONITOR_WINDOW_TYPE         2

#define MAX_NO_OF_SOURCE_SETUPS		3

#define	MAX_NO_OF_SATELLITES		4

#define	PACK_MINISCANRESULT(Ev,Id)	(((Ev<<16) & 0xFFFF0000) | (Id & 0xFFFF))

#define	UNPACK_MINISCANEVENT(Res)	((Res >> 16) & 0xFFFF)

#define	UNPACK_MINISCANID(Res)		(Res & 0xFFFF)

#define	MAX_DATABASE_SYNC_IN_ONEPASS	(20)

#define	MAX_SAT_SERVICES_SUPPORTED			(5000)

#define MAX_NUM_LCN_ENTRY			8

#define MAX_NUM_PRESET_ENTRY		MAX_NUM_LCN_ENTRY

typedef enum
{
	StIdle,
	StSourceSetupWait,
	StDigital,
	StPackageInstall,
	StGenericInstall,
	StSorting,
	StMiniPrescanInstallation,	/* This state is added explicitly for CR brg36mgr#249802 for treating LNB change in Digiturk */
	StPackageParsing,
	StDatabaseSync,
	StMax
}States;
typedef enum 
{
    EvStart,
    EvStop,
    EvSourceSetupApplied,
	EvInstallStart,
	EvInstallComplete,
    EvSorting,
    EvSortComplete,			
    EvInstallFailed,
	EvMiniPrescanResult,
	EvPerformDatabaseSync,
	EvDatabaseSyncComplete,
	EvMax
}Events;
typedef enum
{
    Initialised = 0,
    TurnedOn,
    TurnedOff
}ModuleLifeCycle;
typedef struct InstallationStatus
{
    int		State;
    Nat32    Mode;
    Nat32   Lnb;
    Bool    Stopped;
    Nat16	LastInstalledPreset;
    int		SkipInstallation;
    Nat32   CombinedLnbNumber;
	int		TableInCopy;
	int		FromDatabaseId;
	int		ToDatabaseId;
	int		IndexToCopy;
	int		PresetTableSyncState;
	int		NumEntriesInCache;
}TypeInstallationStatus;

typedef enum __PresetTableCopyStates {
	StatePresetCacheToTemp,
	StatePresetDeleteInSqlite,
	StatePresetCacheToSqlite,
	StatePresetCacheToSqliteComplete
} PresetTableCopyStates;

typedef struct _CachedUniqueId {
	Nat32	PresetNumber;
	Nat32	Tpid;
	Nat16	ServiceId;
} CachedUniqueId;

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

CachedUniqueId	UniqueServiceListCache[MAX_SAT_SERVICES_SUPPORTED];
static CachedUniqueId	s__UniqueServiceListCache[MAX_SAT_SERVICES_SUPPORTED];
ModuleLifeCycle mModuleLifeCycle;
static ModuleLifeCycle s__mModuleLifeCycle;
Pump mPump;
static Pump s__mPump;
TypeInstallationStatus InsStatus;
static TypeInstallationStatus s__InsStatus;
FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
void mPumpHandler(int event, Nat32 param);
void FuncStartInstallation(Nat32 param);
void FuncStopInstallation(Nat32 param);
void FuncSourceSetupApplied(Nat32 param);
void FuncSorting(Nat32 param);
void FuncSortComplete(Nat32 param);
void FuncStartPackageInstall(Nat32 param);
void FuncPackageInstallComplete(Nat32 param);
void FuncStartGenericInstall(Nat32 param);
void FuncGenericInstallComplete (Nat32 param);
void FuncPackageInstallFailed (Nat32 param);
void FuncGenericInstallFailed (Nat32 param);
void FuncStopPackageParsing(Nat32 param);
void FuncPackagePasingComplete(Nat32 param);
void mFuncStartPackageParsing(void);
void FuncStopSemiStandbyInstall (Nat32 param);
void FuncCheckSemiStandbyPrescan (Nat32 param);
void FuncStopDatabaseSync(Nat32 param);
void FuncPerformDatabaseSync(Nat32 param);
void FuncDatabaseSyncComplete(Nat32 param);
inline Bool mValidInstallMode(int mode);
inline void mInitInstallationValues(Nat32 param);
inline void mInitInstallationPass(Bool BlockDestionationFlag);
void SetUpdateInstallEnabling (void);
Nat32 GetNextLnbToRemove (Nat32 CurrentLnb);
void BlockDestination(void);
void UnBlockDestination(void);
void mDetermineDuplicateSatelliteName (HsvPgdatDigSatInfoData *SatInfo);
void mAddPackageInstalledList (void);
void mReloadUnicableSetting (void);
int mRecalculatePackageId (int SatelliteId);
int mIsLnbMdu (int LnbNumber);
int mIdentifyMiniPrescanLnb (void);
void mInitializeTvProviderData (HsvPgdatTvProviderBlobData	*TvProviderData);
void mCollectDigSrvProviderData (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectDigTsProviderData (HsvPgdatDigTSData  *AnalogData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectPresetProviderData(HsvPgdatPresetData *PresetData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectSatInfoProviderData(HsvPgdatDigSatInfoData *SatInfoData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectDigTsTableData (HsvPgdatDigTSData *TsData, HsvPgdatTvProviderBlobData *TvProviderData);
void mAddPresetData(HsvPgdatTvProviderBlobData *TvpData);
void mAddSatInfoData(HsvPgdatTvProviderBlobData *TvpData);
void mAddDigSrvData(HsvPgdatTvProviderBlobData *TvpData);
void mAddDigTsData(HsvPgdatTvProviderBlobData *TvpData);
void LoadSatInfoFromSettings();
void AddSatInfo(int LnbNumber, HsvLnbSettings *LnbSettings);
void mGetUniqueIdFromPresetNumber (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData);
void mUpdateUniqueIds (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData);
Bool mIsPredefinedListPackage (void);



void module__init(void){
#ifndef __cplusplus

#else

#endif

	mModuleLifeCycle	=	s__mModuleLifeCycle;
	mPump	=	s__mPump;
	InsStatus	=	s__InsStatus;
	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
	memcpy(UniqueServiceListCache, s__UniqueServiceListCache, sizeof(UniqueServiceListCache));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef MODE_NONE
#undef MODE_NONE
#endif //MODE_NONE
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef AUTOUPDATE_MODE
#undef AUTOUPDATE_MODE
#endif //AUTOUPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef PRESCAN_MODE
#undef PRESCAN_MODE
#endif //PRESCAN_MODE
#ifdef ADDSAT_MODE
#undef ADDSAT_MODE
#endif //ADDSAT_MODE
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef BCKGNDUPDATE_MODE
#undef BCKGNDUPDATE_MODE
#endif //BCKGNDUPDATE_MODE
#ifdef PACKAGE_PARSING_MODE
#undef PACKAGE_PARSING_MODE
#endif //PACKAGE_PARSING_MODE
#ifdef MINIPRESCAN_MODE
#undef MINIPRESCAN_MODE
#endif //MINIPRESCAN_MODE
#ifdef VALID_EVENT(event)
#undef VALID_EVENT(event)
#endif //VALID_EVENT(event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef SET_INS_STATE(state)
#undef SET_INS_STATE(state)
#endif //SET_INS_STATE(state)
#ifdef GET_INS_STATE
#undef GET_INS_STATE
#endif //GET_INS_STATE
#ifdef CURRENT_DATABASE_TABLE
#undef CURRENT_DATABASE_TABLE
#endif //CURRENT_DATABASE_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef INVALID_LNB
#undef INVALID_LNB
#endif //INVALID_LNB
#ifdef MAIN_VIDEO_WINDOW_TYPE
#undef MAIN_VIDEO_WINDOW_TYPE
#endif //MAIN_VIDEO_WINDOW_TYPE
#ifdef MAIN_AUDIO_WINDOW_TYPE
#undef MAIN_AUDIO_WINDOW_TYPE
#endif //MAIN_AUDIO_WINDOW_TYPE
#ifdef MONITOR_WINDOW_TYPE
#undef MONITOR_WINDOW_TYPE
#endif //MONITOR_WINDOW_TYPE
#ifdef MAX_NO_OF_SOURCE_SETUPS
#undef MAX_NO_OF_SOURCE_SETUPS
#endif //MAX_NO_OF_SOURCE_SETUPS
#ifdef MAX_NO_OF_SATELLITES
#undef MAX_NO_OF_SATELLITES
#endif //MAX_NO_OF_SATELLITES
#ifdef PACK_MINISCANRESULT(Ev,Id)
#undef PACK_MINISCANRESULT(Ev,Id)
#endif //PACK_MINISCANRESULT(Ev,Id)
#ifdef UNPACK_MINISCANEVENT(Res)
#undef UNPACK_MINISCANEVENT(Res)
#endif //UNPACK_MINISCANEVENT(Res)
#ifdef UNPACK_MINISCANID(Res)
#undef UNPACK_MINISCANID(Res)
#endif //UNPACK_MINISCANID(Res)
#endif //LOCAL_UNDEFINES
