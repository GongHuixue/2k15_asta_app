#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include<stdio.h>

#include<string.h>

#include"_hsvdvbstricolor_mScan.h"

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define	VALID_EVENT(Ev)		(Ev < EvMax) ? TRUE : FALSE

#define	VALID_STATE(St)		(St < StMax) ? TRUE	: FALSE

//#define	SET_INS_STATE(St)	((mInstStatus.State != StRegionScanWait)?(mInstStatus.State=St):( mInstStatus.State = StRegionScanWait))
#define SET_INS_STATE(St)        (mInstStatus.State = St)	

#define	SET_INS_MODE(Mode)	(mInstStatus.InstallationMode=Mode)

#define	SET_SCAN_MODE(Mode)	(mInstStatus.ScanMode=Mode)

#define	CURRENT_SCAN_MODE	(mInstStatus.ScanMode)

#define TURNED_ON			(mConstModuleLifeCycle == ConstTurnedOn)

#define VALID_SOURCE(source)		(source == HsvMainTuner)

#define	VALID_DEMUX(Dmx)			(Dmx == HsvDmxMain)

#define	MAX_NUM_LNBS_SUPPORTED		(4)

#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define VALID_MODE(Mode)    ((Mode == insstate_InstallationServiceScan || Mode == insstate_InstallationUpdate || Mode == insstate_InstallationAutomaticUpdate ||  Mode == insstate_InstallationBackgroundUpdate) ? TRUE: FALSE)

#define	SCAN_NOT_INPROGESS	(mInstStatus.State == StIdle)

#define	IS_SERVICE_SCAN		(mInstStatus.InstallationMode == insstate_InstallationServiceScan)

#define	CURRENT_MODE		(mInstStatus.InstallationMode)

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)			(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

#define	SAT_INFO_TABLE		(pgdbconst_Satellite | pgdbconst_SatInfo)

#define NO_OF_HOMING_MUX	(1)

#define	TRICOLOR_SAT_ID		(EUTELSAT_W4_36E)

#define	TRICOLOR_BOUQUET_ID_1	(0x01)

#define	TRICOLOR_BOUQUET_ID_2	(0x02)

#define BAT_TABLE_ID		(0x4A)

#define	INVALID_BOUQUET_ID	(0xFFFF)

#define	SERVICE_TABLE		(pgdb_GetCurrentTable() | pgdbconst_DigitalService)

#define	PTC_TABLE							    	(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define MAX_MUX_PER_SAT		(200)

#define	AUTO_MODE				(insstate_InstallationServiceScan)

#define	IS_VALID_ROLLOFF(x)								(x<(sizeof(RollOffTable)/sizeof(RollOffTable[0])))


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
	StAcquireWait,
	StRegionScanWait,
	StMax
} SvaScanState;
typedef	enum
{
	EvStart = 0,
	EvStop,
	EvDataAvailable,
	EvDataNotAvailable,
	EvDataAcquired,
	EvStartTuning,
	EvCheckLock,
	EvMax
} SvcScanEvents;
typedef	enum
{
    Invalid = 0,
	Homing = 1,
	Fallback
} ScanningMode;
typedef struct InsInstance
{
	int	State;
	int	LnbNumber;
	int	LnbType;
	int	InstallationMode;
	int	IntallationState;
	int	CurrSdsdIndex;
	int	NumOfSDSD;
	int	HomingMuxIndex;
	ScanningMode ScanMode;
} InsInstance;

typedef struct _HomingMuxData
{
	Nat32	Frequency;
	Nat8	Polarization;
	Nat16	SatelliteId;
} HomingMuxData;

typedef struct 
{
	int	Frequency;
	int	Polarization;
	int	SymbolRate;
} UpdateTuneList;


#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#include<stdio.h>

#include<string.h>

#include"_hsvdvbstricolor_mScan.h"

#ifndef __cplusplus

#else

#endif

static const char SvcScanEventNames[EvMax+1][32];
int mConstModuleLifeCycle;
static int s__mConstModuleLifeCycle;
InsInstance mInstStatus;
static InsInstance s__mInstStatus;
Pump mPump;
static Pump s__mPump;
HomingMuxData TricolorPackageDetails[NO_OF_HOMING_MUX];
static HomingMuxData s__TricolorPackageDetails[NO_OF_HOMING_MUX];
FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
UpdateTuneList UpdateInstallList[MAX_MUX_PER_SAT];
static UpdateTuneList s__UpdateInstallList[MAX_MUX_PER_SAT];
int NumEntriesForUpdate;
static int s__NumEntriesForUpdate;
double RollOffTable[4];
static double s__RollOffTable[4];

void PumpHandler(int event, Nat32 param);
void FuncStartServiceScan (Nat32 param1);
void FuncStartTuning (Nat32 param1);
void FuncCheckLockStatus(Nat32 Cookie);
void FuncRegionDataAcquired (Nat32 param1);
void FuncNoRegionDataAvailable (Nat32 param1);


void mStationFound (void);
void mNoStationFound (void);
void FuncDataAvailable (Nat32 param1);
void FuncNoDataAvailable (Nat32 param1);
void FuncDataAquired (Nat32 param1);
void FuncStopServiceScan (Nat32 param1);
void mGetLnbDetails(int SatId);
void mGetCurrentTunerParams (HsvInstallationPTC *ptc);
void mBuildCurrentFrequencyList (void);
Bool IsUpdateInstall(void);
void FuncStartRegionScan (Nat32 param1);
FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);
int CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner);

void module__init(void){
#include<stdio.h>

#include<string.h>

#include"_hsvdvbstricolor_mScan.h"

#ifndef __cplusplus

#else

#endif

	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	mInstStatus	=	s__mInstStatus;
	mPump	=	s__mPump;
	NumEntriesForUpdate = s__NumEntriesForUpdate;
	memcpy((void*)TricolorPackageDetails,(void*)s__TricolorPackageDetails,sizeof(TricolorPackageDetails));
	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
	memcpy((void*)UpdateInstallList,(void*)s__UpdateInstallList,sizeof(UpdateInstallList));
	memcpy((void*)RollOffTable,(void*)s__RollOffTable,sizeof(RollOffTable));
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
#ifdef SET_SCAN_MODE(Mode)
#undef SET_SCAN_MODE(Mode)
#endif //SET_SCAN_MODE(Mode)
#ifdef CURRENT_SCAN_MODE
#undef CURRENT_SCAN_MODE
#endif //CURRENT_SCAN_MODE
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef VALID_SOURCE(source)
#undef VALID_SOURCE(source)
#endif //VALID_SOURCE(source)
#ifdef VALID_DEMUX(Dmx)
#undef VALID_DEMUX(Dmx)
#endif //VALID_DEMUX(Dmx)
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
#ifdef IS_SERVICE_SCAN
#undef IS_SERVICE_SCAN
#endif //IS_SERVICE_SCAN
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#undef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#endif //ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef NO_OF_HOMING_MUX
#undef NO_OF_HOMING_MUX
#endif //NO_OF_HOMING_MUX
#ifdef TRICOLOR_SAT_ID
#undef TRICOLOR_SAT_ID
#endif //TRICOLOR_SAT_ID
#ifdef INVALID_BOUQUET_ID
#undef INVALID_BOUQUET_ID
#endif //INVALID_BOUQUET_ID
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#endif //LOCAL_UNDEFINES
