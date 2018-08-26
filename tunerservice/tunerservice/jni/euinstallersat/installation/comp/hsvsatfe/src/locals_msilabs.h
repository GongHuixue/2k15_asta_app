#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#define WINDOWID					(wnddest_GetWindowId(HsvMain))

#define SEM_CREATE      tprtk_MutexCreate()

#define SEM_TAKE(sem)   tprtk_MutexLock(sem)

#define SEM_GIVE(sem)   tprtk_MutexUnlock(sem)

/* General macros for validation */

#define VALID_EVENT(Event)  ((Event < EvSatfeMax) ? TRUE : FALSE)

#define VALID_STATE(State)  ((State < StSatfeMax) ? TRUE : FALSE)

#define	SET_STATE(State)	(mSatFeIns.CurrentState = (State));

#define	CHK_VALID_LNB(Lnb)				(((Lnb) < MAX_LNB_SUPPORTED) ? err_Ok : err_BadParameter)

#define	CHK_VALID_LNBTYPE(LnbType)		(((LnbType >= LnbUniversal) && (LnbType < LnbInvalid)) ? err_Ok : err_BadParameter)

#define	CHK_VALID_FREQ(Freq)			((((Freq) >= (KUBAND_LOWBAND_START_FREQ - FREQ_RANGE_TOLERANCE)) && ((Freq) <= (KUBAND_HIGHBAND_END_FREQ + FREQ_RANGE_TOLERANCE))) ?  err_Ok : err_BadParameter)

/* Frequency values in KHz */

#define		KUBAND_LOWBAND_START_FREQ		(10700000) 

#define		KUBAND_LOWBAND_END_FREQ			(11700000)

#define		KUBAND_HIGHBAND_START_FREQ		(11700000)

#define		KUBAND_HIGHBAND_END_FREQ		(12750000)

//#define 	KUBAND_HIGHBAND_END_FREQ		(12598000)

#define		FREQ_RANGE_TOLERANCE			(2000)

#define		IF_RANGE_FREQ_START				(950000)

#define		IF_RANGE_FREQ_END				(2150000)

/* Frequency conversion macros */

#define	MAP_SATFE_POLARIZATION_TO_PLFVAL(Pol)	((Pol == sisatfrontend_PolarisationHorizontal) ? plfdvbs_TUNING_DVBS_HORIZONTAL : plfdvbs_TUNING_DVBS_VERTICAL)

#define	MAP_PLFVAL_TO_SATFE_POLARIZATION(Pol)	((Pol == plfdvbs_TUNING_DVBS_HORIZONTAL) ? sisatfrontend_PolarisationHorizontal : sisatfrontend_PolarisationVertical)

#define	MAP_UNIVERSAL_FREQ_TO_BAND(Freq)					(((Freq) >= KUBAND_HIGHBAND_START_FREQ) ? plfdvbs_TUNING_DVBS_BANDHIGH : plfdvbs_TUNING_DVBS_BANDLOW)

/* MDU */

#define		IS_MDU(MduType)				(((MduType == LnbMdutype1) || (MduType == LnbMdutype2) || (MduType == LnbMdutype3) || (MduType == LnbMdutype4) || (MduType == LnbMdutype5)) ? TRUE : FALSE)


/* BlindScanRelated */

#define		MAX_BLIND_SCAN_RANGE			(4)

/* Data Type */

typedef enum SatFeStates    /* States used */
{
	StIdle,
	StTuningIdle,
	StTuningAwaiting,
	StBlindScanIdle,
	StBlindScanProgress,
	StBlindScanEnd,
	StSatfeMax
} SatFeStates;
typedef enum SatFeEvents    /* List of events */
{
	EvNewFeRequest,
	EvStartTune,
	EvTuneResult,
	EvStartBlindScan,
	EvContinueBlindScan,
	EvAbortBlindScan,
	EvBlindScanNtf,
	EvBlindScanEnd,
	EvSatfeMax
} SatFeEvents;
typedef enum    /* SatFE Tuning Mode */
{
	SatFeModeNone,
	SatFeModeTune,
	SatFeModeBlindScan
} SatFeModes;
typedef struct	FineTuneParameters  /* Frequency parameters used for fine tuning */
{
	int		SymbolRate;
	int		ModulationStandard;
	int		Constellation;
	int		CodeRate;
	int		IqMode;
} FineTuneParameters;
typedef struct	SatIpParameters  /* parameters used for satip tuning */
{
	int		ModulationSystem;
	int		ModulationType;
	int		RollOffFactor;
	int		FECInner;
	int		Pilots;
} SatIpParameters;
typedef struct TuningParameters /* Tuning request Parameters */
{
	int		LnbNumber;
	int		Frequency;
	int		Polarization;
	HsvLnbType	LnbType;
	FineTuneParameters	TuningParams;
	SatIpParameters	SatIpParams;
	Nat8	Valid;
} TuningParameters;
typedef struct SatFeInstance    /* Keeping the state machine of SatFE module */
{
	int			CurrentState;
	SatFeModes	CurrentMode;
	int			BlindScanMode;
    Bool        UnicableEnabed;
} SatFeInstance;
typedef struct BlindScanStatus  /* Variables keeping status of blind scan */
{
	int		LnbNumber;
	int		CurrentTableIndex;
	int		CurrentBandInTable;
} BlindScanStatus;
typedef struct BlindScanRangeTable  /* Blind Scan Ranges */
{
	Nat32	StartFreq;
	Nat32	EndFreq;
	int		Polarization;
} BlindScanRangeTable;
typedef struct BlindScanTable   /* Common Blind Scan table for all LNBs */
{
	HsvLnbType	LnbType;
	int			BlindScanMode;
	Nat8		TotalNumOfBands;
	BlindScanRangeTable		Ranges[MAX_BLIND_SCAN_RANGE];	
} BlindScanTable;
#define	NUM_BLINSCAN_LNB_ENTRIES	9

/* Blind Scan Frequency ranges. It contains the ranges of each LNB which needs to be covered in blind scan */

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

BlindScanTable mBlindScanFrequency[NUM_BLINSCAN_LNB_ENTRIES];
static BlindScanTable s__mBlindScanFrequency[NUM_BLINSCAN_LNB_ENTRIES];
char StateNames[StSatfeMax][32];
static char s__StateNames[StSatfeMax][32];
char EventNames[EvSatfeMax][32];
static char s__EventNames[EvSatfeMax][32];
Bool tuneresult;
static Bool s__tuneresult;
TuningParameters mNewFeRequestParams,mCurrentFeParams;
static TuningParameters s__mNewFeRequestParams,s__mCurrentFeParams;
SatFeInstance mSatFeIns;
static SatFeInstance s__mSatFeIns;
BlindScanStatus mBlindScanStatus;
static BlindScanStatus s__mBlindScanStatus;
int SatFeSem;
static int s__SatFeSem;
Pump mPump;
static Pump s__mPump;
FunctionNat32 SatFeEventActionMatrix[EvSatfeMax][StSatfeMax];
static FunctionNat32 s__SatFeEventActionMatrix[EvSatfeMax][StSatfeMax];
void mPumpHandler(int event, Nat32 param);
void mProcessFeRequest (Nat32 Param);
void mNewFeRequest (Nat32 Param);
void mSendTuneRequest (Nat32 Param);
void mNewTuneRequest (Nat32 Param);
void mNotifyTuneResult (Nat32 Param);
void mGotoNewFeRequest (Nat32 Param);
void mProcessBlindScan (Nat32 Param);
void mStartBlindScan (Nat32 Param);
void mTriggerBlindScan (Nat32 Param);
void mNotifyBlindScanResult (Nat32 Param);
void mContinueBlindScan (Nat32 Param);
void mAbortBlindSCan (Nat32 Param);
void mProcessBlindScanEnd (Nat32 Param);
void mNotifyBlindScanEnd (Nat32 Param);
void mInitialize (void);
Bool mValidTuningCombination(int LnbNumber, HsvLnbType LnbType);
void mCopyTuningRequest (void);
FResult mSendUniversalLnbTuningRequest (void);
FResult mSendMduTuningRequest (void);
FResult mEnableUnicableDevice (int LnbNumber, Bool Flag, Bool ForceSet);
FResult mSendUnicableTuningRequest (void);
int MapMwLnbTypeToPlf (int LnbType);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)mBlindScanFrequency,(void*)s__mBlindScanFrequency,sizeof(mBlindScanFrequency));
	memcpy((void*)StateNames,(void*)s__StateNames,sizeof(StateNames));
	memcpy((void*)EventNames,(void*)s__EventNames,sizeof(EventNames));
	tuneresult	=	s__tuneresult;
	mNewFeRequestParams	=	s__mNewFeRequestParams;
	mCurrentFeParams	=	s__mCurrentFeParams;
	mSatFeIns	=	s__mSatFeIns;
	mBlindScanStatus	=	s__mBlindScanStatus;
	SatFeSem	=	s__SatFeSem;
	mPump	=	s__mPump;
	memcpy((void*)SatFeEventActionMatrix,(void*)s__SatFeEventActionMatrix,sizeof(SatFeEventActionMatrix));
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
#ifdef SEM_CREATE
#undef SEM_CREATE
#endif //SEM_CREATE
#ifdef SEM_TAKE(sem)
#undef SEM_TAKE(sem)
#endif //SEM_TAKE(sem)
#ifdef SEM_GIVE(sem)
#undef SEM_GIVE(sem)
#endif //SEM_GIVE(sem)
#ifdef VALID_EVENT(Event)
#undef VALID_EVENT(Event)
#endif //VALID_EVENT(Event)
#ifdef VALID_STATE(State)
#undef VALID_STATE(State)
#endif //VALID_STATE(State)
#ifdef SET_STATE(State)
#undef SET_STATE(State)
#endif //SET_STATE(State)
#ifdef CHK_VALID_LNB(Lnb)
#undef CHK_VALID_LNB(Lnb)
#endif //CHK_VALID_LNB(Lnb)
#ifdef CHK_VALID_LNBTYPE(LnbType)
#undef CHK_VALID_LNBTYPE(LnbType)
#endif //CHK_VALID_LNBTYPE(LnbType)
#ifdef CHK_VALID_FREQ(Freq)
#undef CHK_VALID_FREQ(Freq)
#endif //CHK_VALID_FREQ(Freq)
#ifdef KUBAND_LOWBAND_START_FREQ
#undef KUBAND_LOWBAND_START_FREQ
#endif //KUBAND_LOWBAND_START_FREQ
#ifdef KUBAND_LOWBAND_END_FREQ
#undef KUBAND_LOWBAND_END_FREQ
#endif //KUBAND_LOWBAND_END_FREQ
#ifdef KUBAND_HIGHBAND_START_FREQ
#undef KUBAND_HIGHBAND_START_FREQ
#endif //KUBAND_HIGHBAND_START_FREQ
#ifdef KUBAND_HIGHBAND_END_FREQ
#undef KUBAND_HIGHBAND_END_FREQ
#endif //KUBAND_HIGHBAND_END_FREQ
#ifdef FREQ_RANGE_TOLERANCE
#undef FREQ_RANGE_TOLERANCE
#endif //FREQ_RANGE_TOLERANCE
#ifdef IF_RANGE_FREQ_START
#undef IF_RANGE_FREQ_START
#endif //IF_RANGE_FREQ_START
#ifdef IF_RANGE_FREQ_END
#undef IF_RANGE_FREQ_END
#endif //IF_RANGE_FREQ_END
#ifdef MAP_SATFE_POLARIZATION_TO_PLFVAL(Pol)
#undef MAP_SATFE_POLARIZATION_TO_PLFVAL(Pol)
#endif //MAP_SATFE_POLARIZATION_TO_PLFVAL(Pol)
#ifdef MAP_PLFVAL_TO_SATFE_POLARIZATION(Pol)
#undef MAP_PLFVAL_TO_SATFE_POLARIZATION(Pol)
#endif //MAP_PLFVAL_TO_SATFE_POLARIZATION(Pol)
#ifdef MAP_UNIVERSAL_FREQ_TO_BAND(Freq)
#undef MAP_UNIVERSAL_FREQ_TO_BAND(Freq)
#endif //MAP_UNIVERSAL_FREQ_TO_BAND(Freq)
#ifdef IS_MDU(MduType)
#undef IS_MDU(MduType)
#endif //IS_MDU(MduType)
#ifdef MAX_BLIND_SCAN_RANGE
#undef MAX_BLIND_SCAN_RANGE
#endif //MAX_BLIND_SCAN_RANGE
#ifdef NUM_BLINSCAN_LNB_ENTRIES
#undef NUM_BLINSCAN_LNB_ENTRIES
#endif //NUM_BLINSCAN_LNB_ENTRIES
#endif //LOCAL_UNDEFINES
