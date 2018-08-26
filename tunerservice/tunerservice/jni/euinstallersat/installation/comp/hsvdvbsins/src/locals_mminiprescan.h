#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define		CURRENT_DATABASE_TABLE		(pgdbconst_Satellite)

#define		SAT_INFO_TABLE				(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	PTC_TABLE				    (pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	SERVICE_TABLE				(pgdbconst_Satellite | pgdbconst_DigitalService)

#define PRESET_TABLE				(pgdbconst_Satellite | pgdbconst_Preset)

#define		TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define		MAX_NUM_LNBS_SUPPORTED		4

#define		IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define		SET_INS_STATE(state)		( mInstStatus.State = state )

#define		GET_INS_STATE				( mInstStatus.State )

#define		SCAN_MODE_IDLE				( 0 )

#define		TABLE_BASED_SCAN_MODE		( 1 )

#define		CURRENT_TABLE_INDEX			( mCurrentTableIndex )

#define		SET_SCAN_MODE(mode)			( mScanMode = mode )

#define		CURRENT_SCAN_MODE			( mScanMode )

#define		VALID_EVENT(event)			( (event >= EvStart) && (event < EvMax) )

#define		VALID_STATE(state)			( (state >= StIdle) && (state < StMax)  )

#define		CURRENT_LNB_INDEX			( (mInstStatus.Lnb) )	

#define		TOTAL_NUM_OF_SATELLITES		(mCurrentSatelliteIndex)

//#define		TABLE_SCAN_DATA_TIMEOUT		((eurdiv_NITTimeoutTime + 1) * 1000)

#define		TABLE_SCAN_DATA_TIMEOUT		(51 * 1000)	/*  TODO: Revert it back to 35 after tvplayer issues are fixed for no sections */

#define     INVALID_INDEX                (-1)

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
	EvCheckDataAvailability,
	EvMax
}Events;
typedef struct InsInstance {
	int	State;
	int	Lnb;
	int	LnbType;
	int	NumberOfLocksFound;
	int	TableCollectStatus;	/* Only used for the case in which both TSID and Bouquet ID has to be matched */
} InsInstance;
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
int DataRequested;
static int s__DataRequested;
FunctionNat32 StateEventMatrix[EvMax][StMax];
static FunctionNat32 s__StateEventMatrix[EvMax][StMax];
void mAddSatInfo (HsvSatelliteMapping *MappedSatellite);
void PumpHandler(int event, Nat32 param);
void FuncStartMiniPreScan(Nat32 Param);
void FuncStopMiniPreScan(Nat32 Param);
void FuncMiniPrescanStationFound(Nat32 Param);
void FuncMiniPrescanStationNotFound(Nat32 Param);
void FuncMiniPrescanDataAvailable(Nat32 Param);
void FuncMiniPrescanDataNotAvailable(Nat32 Param);
void FuncCheckMiniPrescanDataAvailable(Nat32 Param);
Bool mMapPrescanLnbType (int SatelliteId, int *LnbType);
Bool mIsMiniPrescanTuningAllowed (int SatelliteId);
void UpdateIfMduType (void);
void FuncStartMiniPrescanTuning(Nat32 Param);
void FuncMiniPrescanCheckLock(Nat32 Param);
Bool mCheckChageOfSatelliteDetected (int SatelliteId);
void mInitialise(void);
Bool mIsEndOfPrescan (void);
int mGetNextScanMode (int CurrentMode);
void mStopSdm(HsvDemux dmx);
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
	DataRequested	=	s__DataRequested;
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
#ifdef CURRENT_DATABASE_TABLE
#undef CURRENT_DATABASE_TABLE
#endif //CURRENT_DATABASE_TABLE
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
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
#ifdef SCAN_MODE_IDLE
#undef SCAN_MODE_IDLE
#endif //SCAN_MODE_IDLE
#ifdef TABLE_BASED_SCAN_MODE
#undef TABLE_BASED_SCAN_MODE
#endif //TABLE_BASED_SCAN_MODE
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
#ifdef CURRENT_LNB_INDEX
#undef CURRENT_LNB_INDEX
#endif //CURRENT_LNB_INDEX
#ifdef TOTAL_NUM_OF_SATELLITES
#undef TOTAL_NUM_OF_SATELLITES
#endif //TOTAL_NUM_OF_SATELLITES
#ifdef TABLE_SCAN_DATA_TIMEOUT
#undef TABLE_SCAN_DATA_TIMEOUT
#endif //TABLE_SCAN_DATA_TIMEOUT
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#endif //LOCAL_UNDEFINES
