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

#define	VALID_EVENT(Ev)	(Ev < EvMax) ? TRUE : FALSE

#define	VALID_STATE(St)	(St < StMax) ? TRUE	: FALSE

#define	SET_INS_STATE(St)	mInstStatus.State=St

#define	SET_INS_MODE(Mode)	mInstStatus.InstallationMode=Mode

#define	SET_SCAN_MODE(Mode)	(mInstStatus.ScanMode=Mode)

#define TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define VALID_SOURCE(source)		(source == HsvMainTuner)

#define	VALID_DEMUX(Dmx)			(Dmx == HsvDmxMain)

#define	MAX_NUM_LNBS_SUPPORTED		4

#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define	VALID_MODE(Mode)	((Mode == insstate_InstallationServiceScan) || (Mode == insstate_InstallationUpdate))|| (Mode == insstate_InstallationAutomaticUpdate) ? TRUE: FALSE

#define	SCAN_NOT_INPROGESS	(mInstStatus.State == StIdle)

#define	IS_SERVICE_SCAN		(mInstStatus.InstallationMode == insstate_InstallationServiceScan)

#define	CURRENT_MODE		(mInstStatus.InstallationMode)

#define CURRENT_INDEX		(mInstStatus.CurrentHomingIndex)

#define NO_OF_ASTRA_REF_FREQ	10

#define NIT_REF_LINKAGE_TYPE		(0x04)

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

#define	SAT_INFO_TABLE									(pgdbconst_Satellite | pgdbconst_SatInfo)



/* PID values of M7 packages*/ 

#define CANALDIGITAAL_SD_PID	900

#define CANALDIGITAAL_HD_PID	901

#define TVVLAANDEREN_SD_PID	910

#define TVVLAANDEREN_HD_PID	911

#define TELESAT_BEL_PID			920

#define TELESAT_LUX_PID			921

#define AUSTRIA_PID				950

#define CZECH_REPUBLIC_PID		30

#define SLOVAK_REPUBLIC_PID	31

#define AUSTRIASAT_MAGYA_PID	951


#define INVALID_BOUQUET_ID 	-1

#define MAX_HOMING_ENTRIES 3

/*TSID details of Astra Barkermux*/

#define ASTRA_19_TSID	1105

#define ASTRA_23_TSID	3219

#define MAX_LINKAGE_DESC	3


//#define INVALID_PID 	-1

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
	StDemuxWaitforM7Data,
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
	EvDataAcquired,
	EvStartTuning,
	EvCheckLock,
	EvMax
} SvcScanEvents;
typedef	enum 
{
	Invalid = 0,
	Homing,
	Fallback
} ScanningMode;
typedef struct _TuningData 
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
} TuningData;
typedef struct InsInstance 
{
	int	State;
	int	Lnb;
	int	LnbType;
	int	Cookie;
	int	InstallationMode;
	int	IntallationState;
	Nat8 Polarization;
	Nat32 Frequency;
	Nat16 CurrentHomingIndex;
	ScanningMode ScanMode;
	Bool	RefNITDetailsAvailable;
	TuningData RefNITData[MAX_LINKAGE_DESC];
	Nat16 CurrentRefNITDataIndex;
	Nat16 NoOfLinkageDescFound;
	Bool	RefM7HomingDetailsAvaialble;
	TuningData RefM7HomingData;
} InsInstance;
typedef struct _HomingMuxData 
{
	Nat32	Frequency;
	Nat8		Polarization;
	Nat16	SatelliteId;
} HomingMuxData;
typedef struct _SatData 
{
	Nat16	SatelliteId;
	Bool	Found;
} SatData;
typedef struct _PackageDetails
{
	Nat32 BouquetIndex;
	Nat32 PID;
	Nat16 NoOfHomingMux;
	const HomingMuxData *HomingMuxList[MAX_HOMING_ENTRIES];
	const SatData *SatelliteOrder;
} PackageDetails;

typedef struct _UsrPackageDetails
{
	Nat32 BouquetIndex;
	Nat32 PID;
	Nat16 NoOfHomingMux;
	HomingMuxData *HomingMuxList[MAX_HOMING_ENTRIES];
	SatData SatelliteOrder[MAX_NUM_LNBS_SUPPORTED];
} UsrPackageDetails;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

static const char SvcScanEventNames[EvMax+1][32];
static const HomingMuxData Astra1HomingFrequencyDetails;
static const HomingMuxData Astra3HomingFrequencyDetails;
static const HomingMuxData EutelSatHomingFrequencyDetails;
const static SatData M7SatOrder1[MAX_NUM_LNBS_SUPPORTED];
const static SatData M7SatOrder2[MAX_NUM_LNBS_SUPPORTED];
const static SatData M7SatOrder3[MAX_NUM_LNBS_SUPPORTED];
const static SatData M7SatOrder4[MAX_NUM_LNBS_SUPPORTED];
int mConstModuleLifeCycle;
static int s__mConstModuleLifeCycle;
InsInstance mInstStatus;
static InsInstance s__mInstStatus;
Pump mPump;
static Pump s__mPump;
PackageDetails M7PackageDetails[NO_OF_PACKAGES_SUPPORTED];
static PackageDetails s__M7PackageDetails[NO_OF_PACKAGES_SUPPORTED];
UsrPackageDetails UserPackagedetails;
static UsrPackageDetails s__UserPackagedetails;
HomingMuxData AstraRefFrequencyDetails[NO_OF_ASTRA_REF_FREQ];
static HomingMuxData s__AstraRefFrequencyDetails[NO_OF_ASTRA_REF_FREQ];
FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
void PumpHandler(int event, Nat32 param);
void FuncStopServiceScan (Nat32 param1);
void FuncStationFound (Nat32 param1);
void FuncNoStationFound (Nat32 param1);
void FuncDataAvailable (Nat32 param1);
void FuncM7DataAvailable (Nat32 param1);
void FuncNoDataAvailable (Nat32 param1);
void FuncNoM7DataAvailable (Nat32 param1);
void FuncDataAquired (Nat32 param1);
void FuncCheckLockStatus(Nat32 Cookie);
void FuncStartTuning (Nat32 param1);
void FuncStartServiceScan (Nat32 param1);
FResult mSetUserPackageDetails(void);
void mSetLNBConfiguration(void);
void ResetM7installedLNBs();
Bool mNonM7SatelliteDetected(HsvLnbSettings *LnbSettings);
Bool GetSatelliteIndexForAddition(int* index);
Bool SetNextNITRefDetails();
Bool SetNextHomingMuxDetails(Bool SwitchSat);
Bool IsSatelliteDetected(int SatID, HsvPgdatDigSatInfoData* SatDetails);
Bool mStoreRefNITDetails();
Bool mStoreRefM7HomingDetails();
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	mInstStatus	=	s__mInstStatus;
	mPump	=	s__mPump;
	memcpy((void*)M7PackageDetails,(void*)s__M7PackageDetails,sizeof(M7PackageDetails));
	UserPackagedetails	=	s__UserPackagedetails;
	memcpy((void*)AstraRefFrequencyDetails,(void*)s__AstraRefFrequencyDetails,sizeof(AstraRefFrequencyDetails));
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
#ifdef CANALDIGITAAL_SD_PID
#undef CANALDIGITAAL_SD_PID
#endif //CANALDIGITAAL_SD_PID
#ifdef CANALDIGITAAL_HD_PID
#undef CANALDIGITAAL_HD_PID
#endif //CANALDIGITAAL_HD_PID
#ifdef TVVLAANDEREN_SD_PID
#undef TVVLAANDEREN_SD_PID
#endif //TVVLAANDEREN_SD_PID
#ifdef TVVLAANDEREN_HD_PID
#undef TVVLAANDEREN_HD_PID
#endif //TVVLAANDEREN_HD_PID
#ifdef TELESAT_BEL_PID
#undef TELESAT_BEL_PID
#endif //TELESAT_BEL_PID
#ifdef TELESAT_LUX_PID
#undef TELESAT_LUX_PID
#endif //TELESAT_LUX_PID
#ifdef AUSTRIA_PID
#undef AUSTRIA_PID
#endif //AUSTRIA_PID
#ifdef CZECH_REPUBLIC_PID
#undef CZECH_REPUBLIC_PID
#endif //CZECH_REPUBLIC_PID
#ifdef SLOVAK_REPUBLIC_PID
#undef SLOVAK_REPUBLIC_PID
#endif //SLOVAK_REPUBLIC_PID
#ifdef INVALID_BOUQUET_ID
#undef INVALID_BOUQUET_ID
#endif //INVALID_BOUQUET_ID
#endif //LOCAL_UNDEFINES
