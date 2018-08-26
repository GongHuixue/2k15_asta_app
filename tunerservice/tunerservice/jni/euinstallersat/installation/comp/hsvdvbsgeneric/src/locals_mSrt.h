#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdio.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define WINDOWID					(wnddest_GetWindowId(HsvMain))

#define TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define VALID_SOURCE(source)		(source == HsvMainTuner)
#define		UPDATE_MODE								(insstate_InstallationUpdate)
#define	VALID_DEMUX(Dms)			(Dmx == HsvDmxMain)

#define	MAX_NUM_LNBS_SUPPORTED		4

#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

#define	VALID_EVENT(Ev)	(Ev < EvMax) ? TRUE : FALSE

#define	VALID_STATE(St)	(St < StMax) ? TRUE	: FALSE

#define	SET_INS_STATE(St)	mInstStatus.State=St

#define	SET_INS_MODE(Mode)	mInstStatus.InstallationMode=Mode

#define	VALID_MODE(Mode)	(Mode == insstate_InstallationManual) ? TRUE: FALSE

#define	SCAN_NOT_INPROGESS	((mInstStatus.State == StIdle) || (mInstStatus.State == StPMTWait))

#define	CURRENT_MODE		(mInstStatus.InstallationMode)

#define	MANUAL_SCAN_STEP_SIZE	10000

#define	MANUAL_SCAN_RANGE		1000

#define	PTC_TABLE				(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	TEMP_CHANNEL_TABLE		(pgdbconst_Satellite)

#define IS_TV_SERVICE(x)        ((x == AppApiTelevisionService) || (x == AppApiTeletextService) || \
								 (x == AppApiMPEG2HDService)  || (x == AppApiAdvCodecHDTelevisionService) || \
								 (x == AppApiAdvCodecSDTelevisionService) || (x == AppApiSkyHD))

#define EvNoPMT					1

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
typedef	enum {
	ConstInitialized = 0,
	ConstTurnedOn,
	ConstTurnedOff
} ModuleState;
typedef	enum {
	StIdle = 0,
	StStart,
	StTunerWait,
	StDemuxWait,
	StPMTWait,
	StMax
} SvaScanState;
typedef	enum {
	EvStart = 0,
	EvStop,
	EvStationFound,
	EvStationNotFound,
	EvDataAvailable,
	EvDataNotAvailable,
	EvStartTuning,
	EvCheckLock,
	EvPMTCollected,
	EvMax
} SrtEvents;
typedef struct InsInstance {
	int	State;
	int	LnbType;
	int	Cookie;
	int	InstallationMode;
	int	IntallationState;
	HsvDemux	CurrentDemux;
	Nat32	UserInstallLnb;
	Nat32	UserInstallFreq;
	Nat32	UserInstallPolaraization;
	Nat32	UserInstallSymRate;
	Nat32	UserInstallsymRateMode;
} InsInstance;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

static const char SrtEventNames[EvMax+1][32];
int mConstModuleLifeCycle;
static int s__mConstModuleLifeCycle;
InsInstance mInstStatus;
static InsInstance s__mInstStatus;
Pump mPump;
static Pump s__mPump;
Pump NoDataPump;
static Pump s__NoDataPump;
Bool mPlayStarted;
static Bool s__mPlayStarted;
HsvSDTService mSvcForPlayBack;
static HsvSDTService s__mSvcForPlayBack;
int mCurrentSessionCookie;
static int s__mCurrentSessionCookie;
FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
void PumpHandler(int event, Nat32 param);
void SetChannelDecoder (void);
void FuncStartManualScan (Nat32 param1);
void FuncStopManualScan (Nat32 param1);
void FuncStartTuning (Nat32 param1);
void FuncStationFound (Nat32 param1);
void FuncNoStationFound (Nat32 param1);
void FuncDataAvailable (Nat32 param1);
void FuncNoDataAvailable (Nat32 param1);
void FuncCheckLock (Nat32 param1);
void FuncPMTCollected (Nat32 param1);
Bool mPlayService(int serviceid);
void mGetCurrentTunerParams (HsvInstallationPTC *ptc);
void mCheckDuplicateTransponder (HsvInstallationPTC *ptc);
Bool mIsLCNAcquistionSupported(void);
void NoPMTHandler(int event, Nat32 param);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	mInstStatus	=	s__mInstStatus;
	mPump	=	s__mPump;
	NoDataPump	=	s__NoDataPump;
	mPlayStarted	=	s__mPlayStarted;
	mSvcForPlayBack = s__mSvcForPlayBack;
	mCurrentSessionCookie = s__mCurrentSessionCookie;
	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
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
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef VALID_SOURCE(source)
#undef VALID_SOURCE(source)
#endif //VALID_SOURCE(source)
#ifdef VALID_DEMUX(Dms)
#undef VALID_DEMUX(Dms)
#endif //VALID_DEMUX(Dms)
#ifdef MAX_NUM_LNBS_SUPPORTED
#undef MAX_NUM_LNBS_SUPPORTED
#endif //MAX_NUM_LNBS_SUPPORTED
#ifdef IS_VALID_LNBNUMBER(x)
#undef IS_VALID_LNBNUMBER(x)
#endif //IS_VALID_LNBNUMBER(x)
#ifdef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#undef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#endif //ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#ifdef VALID_EVENT(Ev)
#undef VALID_EVENT(Ev)
#endif //VALID_EVENT(Ev)
#ifdef VALID_STATE(St)
#undef VALID_STATE(St)
#endif //VALID_STATE(St)
#ifdef SET_INS_STATE(St)
#undef SET_INS_STATE(St)
#endif //SET_INS_STATE(St)
#ifdef SET_INS_MODE(Mode)
#undef SET_INS_MODE(Mode)
#endif //SET_INS_MODE(Mode)
#ifdef VALID_MODE(Mode)
#undef VALID_MODE(Mode)
#endif //VALID_MODE(Mode)
#ifdef SCAN_NOT_INPROGESS
#undef SCAN_NOT_INPROGESS
#endif //SCAN_NOT_INPROGESS
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef MANUAL_SCAN_STEP_SIZE
#undef MANUAL_SCAN_STEP_SIZE
#endif //MANUAL_SCAN_STEP_SIZE
#ifdef MANUAL_SCAN_RANGE
#undef MANUAL_SCAN_RANGE
#endif //MANUAL_SCAN_RANGE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef TEMP_CHANNEL_TABLE
#undef TEMP_CHANNEL_TABLE
#endif //TEMP_CHANNEL_TABLE
#endif //LOCAL_UNDEFINES
