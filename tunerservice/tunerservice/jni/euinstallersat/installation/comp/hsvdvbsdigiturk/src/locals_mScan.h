#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdio.h>

#include <string.h>

#define	VALID_EVENT(event)			((event < EvMax) ? TRUE : FALSE)

#define	VALID_STATE(state)			((state < StMax) ? TRUE	: FALSE)

#define	SET_INS_STATE(state)		(mInstStatus.State = state)

#define	SET_INS_MODE(Mode)			(mInstStatus.InstallationMode = Mode)

#define	CURRENT_MODE				(mInstStatus.InstallationMode)

#define	CURRENT_STATE				(mInstStatus.State)

#define WINDOWID					(wnddest_GetWindowId(HsvMain))

#define TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define VALID_SOURCE(source)		(source == HsvMainTuner)

#define	VALID_DEMUX(Dms)			(Dmx == HsvDmxMain)

#define	MAX_NUM_LNBS_SUPPORTED		4

#define MAX_DIGITURK_PKG			6

#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define	FREQ_DRIFT_TOLERANCE		(4000)

#define	VALID_MODE(Mode)	((Mode == insstate_InstallationServiceScan || Mode == insstate_InstallationUpdate || Mode == insstate_InstallationAutomaticUpdate ||  Mode == insstate_InstallationAddSatellite || Mode == insstate_InstallationSSbyUpdate) ? TRUE: FALSE)

#define	SCAN_NOT_INPROGESS			(mInstStatus.State == StIdle)

#define	MAX_SERVICES_PER_SAT		( 2000 )

#define	MAX_NUM_SDSD				( 500 )

#define	MAX_NUM_HEADEND_FREQUENCY	( 50 )

#define	CURRENT_HOMING_MUX_INDEX	( mCurrentHomingMuxIndex )

#define	CURRENT_SDSD_MUX_INDEX		( mCurrentSDSDMuxIndex )

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

#define	SAT_INFO_TABLE									(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	PTC_TABLE										(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	INVALID_BOUQUET_ID								(0xFFFF)

#define	IS_VALID_ROLLOFF(x)								(x<(sizeof(RollOffTable)/sizeof(RollOffTable[0])))

#define	HOMING_DATA_ACQUIRED							(mSdsdList.NumofSDSDs)

#define SERVICE_TABLE									(pgdbconst_Satellite | pgdbconst_DigitalService)

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
	StHomingScan,
	StDemuxWait,
	StAcquireWait,
	StSDSDScan,
	StMax
} SvaScanState;
typedef	enum 
{
	EvStart = 0,
	EvStop,
	EvStartTuning,
	EvCheckLock,
	EvStationFound,
	EvStationNotFound,
	EvDataAvailable,
	EvDataNotAvailable,
	EvDataAcquired,
	EvComplete,
	EvMax
} SvcScanEvents;
typedef struct InsInstance 
{
	int	State;
	int	Lnb;
	int	LnbType;
	int	Cookie;
	int	InstallationMode;
	int	IntallationState;
	Nat8 Polarization;
} InsInstance;
typedef struct HomingMuxData 
{
	Nat32	Frequency;
	Nat8	Polarization;
	Nat16	SatelliteId;
} HomingMuxData;
typedef struct PackageDetails
{
	Nat32 BouquetIndex;
	const HomingMuxData* HomingMuxDetails;
} PackageDetails;
typedef struct SDSDList
{
	int	Lnb;
	int NumofSDSDs;
	HSVSPTYPE(SatelliteDS, dvb, nit) SDSD[MAX_NUM_SDSD];
} SDSDList;
typedef struct HeadEndFrequencyList
{
	int	Lnb;
	int NumofFreqs;
	HSVSPTYPE(HeadEndFrequencyList, dvb, nit) HeadEndFrequency[MAX_NUM_HEADEND_FREQUENCY];
} HeadEndFrequencyList;
typedef struct 
{
	int	Frequency;
	int	Polarization;
	int	SymbolRate;
} UpdateTuneList;
#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
static const char SvcScanEventNames[EvMax+1][32];
Pump mPump;
static Pump s__mPump;
InsInstance mInstStatus;
static InsInstance s__mInstStatus;
SDSDList mSdsdList;
static SDSDList s__mSdsdList;
HeadEndFrequencyList mHeadEndFrequencyList;
static HeadEndFrequencyList s__mHeadEndFrequencyList;
UpdateTuneList UpdateInstallList[MAX_SERVICES_PER_SAT];
static UpdateTuneList s__UpdateInstallList[MAX_SERVICES_PER_SAT];
int mConstModuleLifeCycle,mCurrentHomingMuxIndex,mCurrentSDSDMuxIndex,mInstallationVersion;
static int s__mConstModuleLifeCycle,s__mCurrentHomingMuxIndex,s__mCurrentSDSDMuxIndex,s__mInstallationVersion;
int NumEntriesForUpdate;
static int s__NumEntriesForUpdate;
static const HomingMuxData EutelSatHomingFrequency[7];
static const HomingMuxData TurkSatHomingFrequency[3];
PackageDetails DigiTurkPackages[3];
static PackageDetails s__DigiTurkPackages[3];
PackageDetails mUserSelectedPackage;
static PackageDetails s__mUserSelectedPackage;
double RollOffTable[4];
static double s__RollOffTable[4];
#ifndef __cplusplus

#else

#endif

FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
void PumpHandler(int event, Nat32 param);
void mStopSdm (void);
void FuncStopServiceScan (Nat32 Param);
void FuncStationFound (Nat32 Param);
void FuncNoStationFound (Nat32 Param);
void FuncDataAvailable (Nat32 Param);
void FuncNoDataAvailable (Nat32 Param);
void FuncDataAcquired (Nat32 Param);
void FuncCheckLockStatus(Nat32 Cookie);
void FuncStartTuning (Nat32 Param);
void FuncStartServiceScan (Nat32 Param);
void FuncComplete(Nat32 Param);
FResult mGetUserPackageDetails(void);
void mInitInstallationValues(int EventId);
Bool mGetSDSDFromStrapi(void);
Bool mGetHeadEndFrequencyFromStrapi(void);
FResult mGetNextTunerParameters(int *Frequency, int *Polarization, int *SymbolRate, int *ModlnStd, int *ModlnType, int *CodeRate);
int CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner);
Nat16 mMapBouquetIdtoPackageId(Nat32 PackageId);
Bool mIsUpdateInstall(void);
int mMapFrequency(int index);
void mBuildCurrentFrequencyList (void);
void module__init(void){
	mPump	=	s__mPump;
	mInstStatus	=	s__mInstStatus;
	mSdsdList	=	s__mSdsdList;
	mHeadEndFrequencyList	=	s__mHeadEndFrequencyList;
	memcpy((void*)UpdateInstallList,(void*)s__UpdateInstallList,sizeof(UpdateInstallList));
	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	mCurrentHomingMuxIndex	=	s__mCurrentHomingMuxIndex;
	mCurrentSDSDMuxIndex	=	s__mCurrentSDSDMuxIndex;
	mInstallationVersion	=	s__mInstallationVersion;
	NumEntriesForUpdate	=	s__NumEntriesForUpdate;
	memcpy((void*)DigiTurkPackages,(void*)s__DigiTurkPackages,sizeof(DigiTurkPackages));
	mUserSelectedPackage	=	s__mUserSelectedPackage;
	memcpy((void*)RollOffTable,(void*)s__RollOffTable,sizeof(RollOffTable));
#ifndef __cplusplus

#else

#endif

	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef VALID_EVENT(event)
#undef VALID_EVENT(event)
#endif //VALID_EVENT(event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef SET_INS_STATE(state)
#undef SET_INS_STATE(state)
#endif //SET_INS_STATE(state)
#ifdef SET_INS_MODE(Mode)
#undef SET_INS_MODE(Mode)
#endif //SET_INS_MODE(Mode)
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef CURRENT_STATE
#undef CURRENT_STATE
#endif //CURRENT_STATE
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
#ifdef MAX_DIGITURK_PKG
#undef MAX_DIGITURK_PKG
#endif //MAX_DIGITURK_PKG
#ifdef IS_VALID_LNBNUMBER(x)
#undef IS_VALID_LNBNUMBER(x)
#endif //IS_VALID_LNBNUMBER(x)
#ifdef FREQ_DRIFT_TOLERANCE
#undef FREQ_DRIFT_TOLERANCE
#endif //FREQ_DRIFT_TOLERANCE
#ifdef VALID_MODE(Mode)
#undef VALID_MODE(Mode)
#endif //VALID_MODE(Mode)
#ifdef SCAN_NOT_INPROGESS
#undef SCAN_NOT_INPROGESS
#endif //SCAN_NOT_INPROGESS
#ifdef MAX_SERVICES_PER_SAT
#undef MAX_SERVICES_PER_SAT
#endif //MAX_SERVICES_PER_SAT
#ifdef MAX_NUM_SDSD
#undef MAX_NUM_SDSD
#endif //MAX_NUM_SDSD
#ifdef MAX_NUM_HEADEND_FREQUENCY
#undef MAX_NUM_HEADEND_FREQUENCY
#endif //MAX_NUM_HEADEND_FREQUENCY
#ifdef CURRENT_HOMING_MUX_INDEX
#undef CURRENT_HOMING_MUX_INDEX
#endif //CURRENT_HOMING_MUX_INDEX
#ifdef CURRENT_SDSD_MUX_INDEX
#undef CURRENT_SDSD_MUX_INDEX
#endif //CURRENT_SDSD_MUX_INDEX
#ifdef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#undef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#endif //ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef INVALID_BOUQUET_ID
#undef INVALID_BOUQUET_ID
#endif //INVALID_BOUQUET_ID
#ifdef IS_VALID_ROLLOFF(x)
#undef IS_VALID_ROLLOFF(x)
#endif //IS_VALID_ROLLOFF(x)
#ifdef HOMING_DATA_ACQUIRED
#undef HOMING_DATA_ACQUIRED
#endif //HOMING_DATA_ACQUIRED
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
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
#endif //LOCAL_UNDEFINES
