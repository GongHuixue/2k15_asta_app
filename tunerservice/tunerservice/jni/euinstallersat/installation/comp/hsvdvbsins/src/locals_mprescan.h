#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)




/* ANEESH: TODO: Below 3 are just dummy macros. Should be replaced when the flags from 
	amdivlib is available to distinguish the product */

#define		R1HARDWARE					0

#define		R3HARDWARE					1

#define		CURRENTHARDWARE				(1)

#define		SAT_INFO_TABLE				(pgdbconst_Satellite | pgdbconst_SatInfo)

#define		WINDOWID					(wnddest_GetWindowId(HsvMain))

#define		TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define		MAX_NUM_LNBS_SUPPORTED		4

#define		IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define		SET_INS_STATE(state)		( mInstStatus.State = state )

#define		GET_INS_STATE				( mInstStatus.State )

#define		VALID_MODE(Mode)			( (Mode == pins_InstallationPreScan) ? TRUE: FALSE)

#define		SCAN_MODE_IDLE				( 0 )

#define		TABLE_BASED_SCAN_MODE		( 1 )

#define		BLIND_SCAN_MODE				( 2 )

#define		FALLBACK_BLINDSCAN_MODE		( 3 )

#define		MANUAL_FREQUENCY_MODE		( 4 )

#define		CURRENT_TABLE_INDEX			( mCurrentTableIndex )

#define		SET_SCAN_MODE(mode)			( mScanMode = mode )

#define		CURRENT_SCAN_MODE			( mScanMode )

#define		VALID_EVENT(event)			( (event >= EvStart) && (event < EvMax) )

#define		VALID_STATE(state)			( (state >= StIdle) && (state < StMax)  )

//#define		PRESCAN_MODE				( rins_InstallationModePreScan )
#define		PRESCAN_MODE				( IHsvSatelliteInstallation_InstallationPreScan )

#define		MAX_NUM_SDSD				( 500 )

#define		CURRENT_LNB_INDEX			( (mInstStatus.Lnb) )	

#define		TOTAL_NUM_OF_SATELLITES		(mCurrentSatelliteIndex)
//#define		TABLE_SCAN_DATA_TIMEOUT	((eurdiv_NITTimeoutTime + 1) * 1000)
/* Timeout is increased to 35sec, to trigger stop collection after timeout expires in SDM module. In SDM collection timeout is 30sec */

#define		TABLE_SCAN_DATA_TIMEOUT		(35 * 1000)	/* ANEESH: TODO: Revert it back to 35 after testing on SoC */

#define		MAX_FALLBACK_BLINDSSCAN_LOCKS	( 3 )

#define     INVALID_INDEX                (-1)

#define		CANAL_SAT_ID					(THOR_1W)

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
typedef	enum {
	ConstInitialized = 0,
	ConstTurnedOn,
	ConstTurnedOff
} ModuleState;
typedef enum
{
	StIdle,
	StStart,
	StTunerWait,
	StDemuxWait,
	StFallbackMode,
	StSignalStrength,
	StWaitAbort,
	StMax
}States;
typedef enum 
{
	NotRequested,
	Requested,
	MatchingBat,
	MatchingTsId
} BouquetIdTsIdFlag;
typedef enum 
{
    EvStart,
    EvStop,
    EvStationFound,
    EvStationNotFound,
    EvDataAvailable,
	EvDataNotAvailable,
	EvStartTuning,
	EvCheckLock,
	EvBlindScanEnd,
	EvCheckDataAvailability,
	EvSigStrStart,
	EvSigStrStop,
	EvMax
}Events;
typedef enum
{
	BlindScanIdle = 0,
	BlindScanStarted,
	BlindScanLocked,
	BlindScanNotLocked,
} BlindScanStatus;
typedef struct InsInstance {
	int	State;
	int	Lnb;
	int	LnbType;
	Nat8	BlindScanStarted;
	int	NumberOfLocksFound;
	int	TableCollectStatus;	/* Only used for the case in which both TSID and Bouquet ID has to be matched */
} InsInstance;
typedef struct SDSDList {
	int	Lnb;
	int NumofSDSDs;
	HsvNITSatelliteDS SDSD[MAX_NUM_SDSD];
}LNBSDSDList;
typedef struct{
	int Lnb;
	int LnbType;
	int Frequency;
	int Polarization;
}HsvSatInfoCache;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

int mCurrentSatelliteIndex;
static int s__mCurrentSatelliteIndex;
Pump mPump;
static Pump s__mPump;
InsInstance mInstStatus;
static InsInstance s__mInstStatus;
ModuleState mConstModuleLifeCycle;
static ModuleState s__mConstModuleLifeCycle;
int mCurrentTableIndex,CURRENT_SCAN_MODE;
static int s__mCurrentTableIndex,s__CURRENT_SCAN_MODE;
LNBSDSDList mLnbSdsdList;
static LNBSDSDList s__mLnbSdsdList;
int DataRequested;
static int s__DataRequested;
HsvSatInfoCache SatInfoCache[MAX_NUM_LNBS_SUPPORTED];
static HsvSatInfoCache s__SatInfoCache[MAX_NUM_LNBS_SUPPORTED];
FunctionNat32 StateEventMatrix[EvMax][StMax];
static FunctionNat32 s__StateEventMatrix[EvMax][StMax];
int MapMwLnbTypeToPlf (int LnbType);
void mAddSatInfo (HsvSatelliteMapping *MappedSatellite);
void PumpHandler(int event, Nat32 param);
void FuncProcessAbort (Nat32 Param);
void FuncStartPreScan(Nat32 Param);
void FuncStopPreScan(Nat32 Param);
void FuncStationFound(Nat32 Param);
void FuncStationNotFound(Nat32 Param);
void UpdateSatInfoCache (void);
void FuncDataAvailable(Nat32 Param);
void FuncDataNotAvailable(Nat32 Param);
void FunCheckDataAvailable(Nat32 Param);
void mSetLOValue(int SatelliteId);
Bool mMapPrescanLnbType (int SatelliteId, int *LnbType);
Bool mIsPrescanTuningAllowed (int LnbType, Bool ConversionDone);
void FuncStartTuning(Nat32 Param);
void FuncCheckLock(Nat32 Param);
void FuncCheckBlindScan(Nat32 Param);
void FuncFallbackStationFound(Nat32 Param);
void FuncFallbackStationNotFound(Nat32 Param);
void FuncFallbackDataAvailable(Nat32 Param);
void FuncFallbackDataNotAvailable(Nat32 Param);
void FuncFallbackStartTuning(Nat32 Param);
void FuncFallbackBlindScanEnd(Nat32 Param);
void StoreUnknownSatellite (void);
void mInitialise(void);
Bool mIsEndOfPrescan (void);
int mGetNextScanMode (int CurrentMode);
void mStopSdm(HsvDemux dmx);
Bool mGetSDSDFromStrapi(void);
void FuncCheckSigLock(Nat32 Param);
void FuncStartSigStrMeas(Nat32 Param);
void FuncStartSigStrTune(Nat32 LnbNumber);
void FuncStopSigStrMeas(Nat32 Param);
Nat32 QssmGetSignalStrength( );
Nat32 GetDigitalSignalStrength(void);
Nat32 vssmGetSignalStrength(void)
/*-------------------------------------------------------------------------------------------------*/;
Bool mManualFrequencyModeSupported(void);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mCurrentSatelliteIndex	=	s__mCurrentSatelliteIndex;
	mPump	=	s__mPump;
	mInstStatus	=	s__mInstStatus;
	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	mCurrentTableIndex	=	s__mCurrentTableIndex;
	CURRENT_SCAN_MODE	=	s__CURRENT_SCAN_MODE;
	mLnbSdsdList	=	s__mLnbSdsdList;
	DataRequested	=	s__DataRequested;
	memcpy((void*)SatInfoCache,(void*)s__SatInfoCache,sizeof(SatInfoCache));
	memcpy((void*)StateEventMatrix,(void*)s__StateEventMatrix,sizeof(StateEventMatrix));
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
#ifdef R1HARDWARE
#undef R1HARDWARE
#endif //R1HARDWARE
#ifdef R3HARDWARE
#undef R3HARDWARE
#endif //R3HARDWARE
#ifdef CURRENTHARDWARE
#undef CURRENTHARDWARE
#endif //CURRENTHARDWARE
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef MAX_NUM_LNBS_SUPPORTED
#undef MAX_NUM_LNBS_SUPPORTED
#endif //MAX_NUM_LNBS_SUPPORTED
#ifdef IS_VALID_LNBNUMBER(x)
#undef IS_VALID_LNBNUMBER(x)
#endif //IS_VALID_LNBNUMBER(x)
#ifdef SET_INS_STATE(state)
#undef SET_INS_STATE(state)
#endif //SET_INS_STATE(state)
#ifdef GET_INS_STATE
#undef GET_INS_STATE
#endif //GET_INS_STATE
#ifdef VALID_MODE(Mode)
#undef VALID_MODE(Mode)
#endif //VALID_MODE(Mode)
#ifdef SCAN_MODE_IDLE
#undef SCAN_MODE_IDLE
#endif //SCAN_MODE_IDLE
#ifdef TABLE_BASED_SCAN_MODE
#undef TABLE_BASED_SCAN_MODE
#endif //TABLE_BASED_SCAN_MODE
#ifdef BLIND_SCAN_MODE
#undef BLIND_SCAN_MODE
#endif //BLIND_SCAN_MODE
#ifdef FALLBACK_BLINDSCAN_MODE
#undef FALLBACK_BLINDSCAN_MODE
#endif //FALLBACK_BLINDSCAN_MODE
#ifdef MANUAL_FREQUENCY_MODE
#undef MANUAL_FREQUENCY_MODE
#endif //MANUAL_FREQUENCY_MODE
#ifdef CURRENT_TABLE_INDEX
#undef CURRENT_TABLE_INDEX
#endif //CURRENT_TABLE_INDEX
#ifdef SET_SCAN_MODE(mode)
#undef SET_SCAN_MODE(mode)
#endif //SET_SCAN_MODE(mode)
#ifdef CURRENT_SCAN_MODE
#undef CURRENT_SCAN_MODE
#endif //CURRENT_SCAN_MODE
#ifdef VALID_EVENT(event)
#undef VALID_EVENT(event)
#endif //VALID_EVENT(event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef PRESCAN_MODE
#undef PRESCAN_MODE
#endif //PRESCAN_MODE
#ifdef MAX_NUM_SDSD
#undef MAX_NUM_SDSD
#endif //MAX_NUM_SDSD
#ifdef CURRENT_LNB_INDEX
#undef CURRENT_LNB_INDEX
#endif //CURRENT_LNB_INDEX
#ifdef TOTAL_NUM_OF_SATELLITES
#undef TOTAL_NUM_OF_SATELLITES
#endif //TOTAL_NUM_OF_SATELLITES
#ifdef TABLE_SCAN_DATA_TIMEOUT
#undef TABLE_SCAN_DATA_TIMEOUT
#endif //TABLE_SCAN_DATA_TIMEOUT
#ifdef MAX_FALLBACK_BLINDSSCAN_LOCKS
#undef MAX_FALLBACK_BLINDSSCAN_LOCKS
#endif //MAX_FALLBACK_BLINDSSCAN_LOCKS
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef CANAL_SAT_ID
#undef CANAL_SAT_ID
#endif //CANAL_SAT_ID
#endif //LOCAL_UNDEFINES
