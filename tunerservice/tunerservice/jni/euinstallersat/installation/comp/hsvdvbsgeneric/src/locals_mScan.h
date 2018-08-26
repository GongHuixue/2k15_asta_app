#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdio.h>

#include <string.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define	VALID_EVENT(Ev)				((Ev < EvMax) ? TRUE : FALSE)

#define	VALID_STATE(St)				((St < StMax) ? TRUE	: FALSE)

#define	SET_INS_STATE(St)			(mInstStatus.State=St)

#define	SET_INS_MODE(Mode)			(mInstStatus.InstallationMode=Mode)

#define WINDOWID					(wnddest_GetWindowId(HsvMain))

#define TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define VALID_SOURCE(source)		(source == HsvMainTuner)

#define	VALID_DEMUX(Dms)			(Dmx == HsvDmxMain)

#define	MAX_NUM_LNBS_SUPPORTED		4

#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define	VALID_MODE(Mode)	((Mode == insstate_InstallationServiceScan || Mode == insstate_InstallationUpdate || Mode == insstate_InstallationAutomaticUpdate ||  Mode == insstate_InstallationAddSatellite) ? TRUE: FALSE)

#define	SCAN_NOT_INPROGESS	(mInstStatus.State == StIdle)

#define	CURRENT_MODE		(mInstStatus.InstallationMode)

#define	MAX_SERVICES_PER_SAT	(2000)

#define MAX_TP_IN_OVERLAPPING_REG   (100)

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

#define	SAT_INFO_TABLE									(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	PTC_TABLE										(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define SWITCHING_FREQUENCY         (11700000)  /*KHz*/

#define IN_SWITCHING_REGION(Freq)      (((Freq >= (SWITCHING_FREQUENCY - 60000)) && (Freq <= (SWITCHING_FREQUENCY + 60000))) ? TRUE : FALSE)

#define	NO_OF_HOMING_MUX		(5)

#define NIT_REF_LINKAGE_TYPE		(0x04)

#define	ASTRA_SAT_ID			(ASTRA_19_2_E)





typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
typedef	enum 
{
	ConstInitialized = 0,
	ConstTurnedOn,
	ConstTurnedOff
} ModuleState;
typedef	enum 
{
	StIdle = 0,
	StStart,
	StTunerWait,
	StDemuxWait,
	StMax
} SvaScanState;
typedef	enum 
{
	EvStart = 0,
	EvStop,
	EvStationFound,
	EvStationNotFound,
	EvDataAvailable,
	EvDataNotAvailable,
	EvStartTuning,
	EvCheckLock,
	EvBlindScanEnd,
	EvMax
} SvcScanEvents;
typedef struct InsInstance 
{
	int	State;
	int	Lnb;
	int	LnbType;
	int	InstallationMode;
	int	IntallationState;
	Bool BlindScanInProgress;
	int	ProgressBar;
} InsInstance;

typedef struct HomingMuxData 
{
	Nat32	Frequency;
	Nat8	Polarization;
	Nat16	SatelliteId;
	Nat8	ModulationSystem;
	Nat8	ModulationType;
	Nat8	FECInner;
	Nat8	RollOffFactor;
	Nat8	Pilots;
} HomingMuxData;


typedef	enum 
{
	Idle = 0,
	Homing = 1,
	SDSDScan
} ScanningMode;

typedef struct _ReferanceNITData 
{
	int 	ONID;
	int		TSID;
	int		SvcId;
	Nat32	Frequency;
	Nat8	Polarization;
	Nat8	RollOff;
	int		ModulationSystem;
	int		ModulationType;
	Nat8	FECInner;
} ReferanceNITData;


typedef struct AstraScanInstance
{
	Bool	Enable;
	ScanningMode Mode;
	int		HomingMuxIndex;
	int		CurrSdsdIndex;
	int		NumOfSDSD;
	Bool	RefNITDetailsAvailable;
	ReferanceNITData RefNITData;
} AstraScanInstance;

typedef struct 
{
	int	Frequency;
	int	Polarization;
	int	SymbolRate;
} UpdateTuneList;
;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

static const char SvcScanEventNames[EvMax+1][32];
int mConstModuleLifeCycle,NumEntriesForUpdate,CurrentEntryForUpdate,NumEntriesInOverlappingRange;
static int s__mConstModuleLifeCycle,s__NumEntriesForUpdate,s__CurrentEntryForUpdate,s__NumEntriesInOverlappingRange;
InsInstance mInstStatus;
static InsInstance s__mInstStatus;
AstraScanInstance mAstraScanStatus;
static AstraScanInstance s__mAstraScanStatus;
Pump mPump;
static Pump s__mPump;
UpdateTuneList UpdateInstallList[MAX_SERVICES_PER_SAT];
static UpdateTuneList s__UpdateInstallList[MAX_SERVICES_PER_SAT];
UpdateTuneList SwitchFreqList[MAX_TP_IN_OVERLAPPING_REG];
static UpdateTuneList s__SwitchFreqList[MAX_TP_IN_OVERLAPPING_REG];
HomingMuxData AstraHomingDetails[NO_OF_HOMING_MUX];
static HomingMuxData s__AstraHomingDetails[NO_OF_HOMING_MUX];
UpdateTuneList mCachedFEParams;
static UpdateTuneList s__mCachedFEParams;
FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
void PumpHandler(int event, Nat32 param);
void SetChannelDecoder (void);
void mBuildCurrentFrequencyList (void);
Bool IsMduLnb (int LnbType);
void FuncStartServiceScan (Nat32 param1);
void FuncStopServiceScan (Nat32 param1);
void FuncStartTuning (Nat32 param1);
void FuncStationFound (Nat32 param1);
void FuncNoStationFound (Nat32 param1);
void FuncDataAvailable (Nat32 param1);
void FuncNoDataAvailable (Nat32 param1);
void FuncCheckLockStatus(Nat32 param1);
void FuncBlindScanEnd(Nat32 Param);
void mGetCurrentTunerParams (HsvInstallationPTC *ptc);
void mHandleOverlappingRegion (HsvInstallationPTC *ptc);
int	mGetSatID(int LnbNumber);
Bool mStoreRefNITDetails();
int MapRollOffFactor(int RollOff);


void module__init(void){
#ifndef __cplusplus

#else

#endif

	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	NumEntriesForUpdate	=	s__NumEntriesForUpdate;
	CurrentEntryForUpdate	=	s__CurrentEntryForUpdate;
	NumEntriesInOverlappingRange	=	s__NumEntriesInOverlappingRange;
	mInstStatus	=	s__mInstStatus;
	mAstraScanStatus = s__mAstraScanStatus;
	mPump	=	s__mPump;
	memcpy((void*)UpdateInstallList,(void*)s__UpdateInstallList,sizeof(UpdateInstallList));
	memcpy((void*)SwitchFreqList,(void*)s__SwitchFreqList,sizeof(SwitchFreqList));
	mCachedFEParams	=	s__mCachedFEParams;
	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
	memcpy((void*)AstraHomingDetails,(void*)s__AstraHomingDetails,sizeof(AstraHomingDetails));
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
#ifdef VALID_MODE(Mode)
#undef VALID_MODE(Mode)
#endif //VALID_MODE(Mode)
#ifdef SCAN_NOT_INPROGESS
#undef SCAN_NOT_INPROGESS
#endif //SCAN_NOT_INPROGESS
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef MAX_SERVICES_PER_SAT
#undef MAX_SERVICES_PER_SAT
#endif //MAX_SERVICES_PER_SAT
#ifdef MAX_TP_IN_OVERLAPPING_REG
#undef MAX_TP_IN_OVERLAPPING_REG
#endif //MAX_TP_IN_OVERLAPPING_REG
#ifdef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#undef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#endif //ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SWITCHING_FREQUENCY
#undef SWITCHING_FREQUENCY
#endif //SWITCHING_FREQUENCY
#ifdef IN_SWITCHING_REGION(Freq)
#undef IN_SWITCHING_REGION(Freq)
#endif //IN_SWITCHING_REGION(Freq)
#endif //LOCAL_UNDEFINES
