#ifndef  _CHSVDVBSFREESAT_MSCAN_H
#define  _CHSVDVBSFREESAT_MSCAN_H

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScanData.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvInstallationSigStrength.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvDigitalScanSdsdData.h>
#include <CS2MwBase.h>

class CHsvDvbsFreesat_mScan: public IHsvDigitalAcquisitionNotify, public IHsvSatellitePackageInstallation, public IHsvSdmControlNotifyEx, public IHsvDigitalScanData, public IHsvPower, public IHsvSatelliteFrontEndNotify, public IHsvDigitalScanSdsdData, public CS2MwBase
{
public:
	ProvidesInterface<IHsvDigitalAcquisitionNotify>	idataacqN;

	ProvidesInterface<IHsvSatellitePackageInstallation>	isvcscan;

	ProvidesInterface<IHsvSdmControlNotifyEx>	isvcscanctrlN;

	ProvidesInterface<IHsvDigitalScanData>	isvcscandata;

	ProvidesInterface<IHsvPower>	isvcscanpow;

	ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

	ProvidesInterface<IHsvDigitalScanSdsdData> iscansdsd;

	//Required interfaces
public:
	RequiresInterface<IHsvSdmControl2>	ctrl;
	RequiresInterface<IHsvPower>	iacqpow;
	RequiresInterface<IHsvDigitalAcquisition>	idataacq;
	RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
	RequiresInterface<IHsvSatelliteInstallation>	insstate;
	RequiresInterface<IHsvInstallationSigStrength>	isigstr;
	RequiresInterface<IHsvPower>	isortpow;
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IHsvProgramDatabase>	pgdb;
	RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
	RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
	RequiresInterface<IHsvStream>	strapi;
	RequiresInterface<IHsvErrorCodeEx>	err;
	RequiresInterface<IHsvPower>	isettingspow;
	RequiresInterface<IHsvSatelliteSettings>	isettings;
	RequiresInterface<IHsvPower> ibckgndpow;

public:

	void OnDataAquired(Bool Status);

	int GetCurrentInstallationState(int * mode,int * state);
	FResult StartInstallation(int Source,int Lnb,int Mode);
	FResult StopInstallation(void);
	FResult WriteBarkerMuxData(void);
	int GetNumberOfTvChannelsFound(int Mode,int Lnb);
	int GetNumberofRadioChannelsFound(int Mode,int Lnb);
	int GetNumberOfTvChannelsRemoved(int Mode,int Lnb);
	int GetNumberofRadioChannelsRemoved(int Mode,int Lnb);
	int GetNumberOfDigitalChannelsAdded(void);
	int GetNumberOfDigitalChannelsRemoved(void);
	int GetNumberOfDigitalChannelsMoved(void);
	FResult LoadManualInstallationDefaultValues(void);
	FResult StoreManualInstallationValues(void);
	Bool SetManualInstallationAttributes(int AttributeId,int Value);
	int GetAttribute(int Mode,int AttributeId);
	FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);
	FResult GetTricolorRegionNames(Nat16 **names, int *len);
	FResult SetTricolorRegionIndex(int index);
	FResult StartTricolorRegionParsing ();
	int GetScanProgressStatus(int Mode);
	void GetSIDetails(HsvSDMSIDataValues * SiValues);

	void OnEvent(HsvDemux dmx,int eventid,int value);

	void GetPtcInfo(HsvInstallationPTC * ptc);
	int GetInstallationVersion(void);
	void GetPtcInfoForSdSd(HsvInstallationPTC * ptc);
	void SyncComplete(void);

	void Init(void);
	void TurnOn(void);
	void TurnOff(void);

	void OnLockChanged(Bool LockState);
	void OnBlindScanEnd(void);

	Bool GetHomingData(void* data);
	int GetSDSDData(void *data);

private:
	Pumpdefines(CHsvDvbsFreesat_mScan);

	#define CURRENT_MODE		(mInstStatus.InstallationMode)
	#define	SET_INS_MODE(Mode)	(mInstStatus.InstallationMode=Mode)
	#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))
	#define TURNED_ON			(s__mConstModuleLifeCycle == ConstTurnedOn)
	#define VALID_SOURCE(source)		(source == HsvMainTuner)
	#define	MAX_NUM_LNBS_SUPPORTED		(4)
	#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)
	#define VALID_MODE(Mode)    ((Mode == IHsvSatelliteInstallation_InstallationServiceScan || Mode == IHsvSatelliteInstallation_InstallationUpdate || Mode == IHsvSatelliteInstallation_InstallationAutomaticUpdate ||  Mode == IHsvSatelliteInstallation_InstallationBackground) ? TRUE: FALSE)
	#define	SCAN_NOT_INPROGESS	(mInstStatus.State == StIdle)
	#define NO_OF_HOMING_MUX		(1)
	#define MAX_LINKAGE_SERVICE	(25)
	#define	SET_SCAN_MODE(Mode)	(mInstStatus.ScanMode=Mode)
	#define	CURRENT_SCAN_MODE	(mInstStatus.ScanMode)
	#define	SET_SCAN_SUB_MODE(Mode)	(mInstStatus.ScanSubMode=Mode)
	#define	CURRENT_SCAN_SUB_MODE	(mInstStatus.ScanSubMode)
	#define	SET_INS_STATE(state)		(mInstStatus.State = state)
	#define	CURRENT_INS_STATE		(mInstStatus.State)
	#define	VALID_DEMUX(Dmx)			(HsvDmxMain == Dmx)

	#define DEFAULT_FREESAT_HD_BID			(272)
	#define DEFAULT_FREESAT_HD_RID			(50)

	#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsFreesat_mScan::func,replace,(char *)name,this)
	#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
	#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)

	#define CLASSSCOPE CHsvDvbsFreesat_mScan::
	#define FNADDR(f) (& CLASSSCOPE f)
	#define FPCALL(f) (this->* f)

	#define POSTCODE_TREE_TABLE		(0)
	#define REGION_KEY_MAP_TABLE	(1)

	typedef void (CLASSSCOPE *FunctionNat32)(Nat32);

	typedef enum __State
	{
		ConstInitialized,
		ConstTurnedOn,
		ConstTurnedOff
	} State;

	typedef	enum
	{
		InvalidScanMode = 0,
		FactoryMuxMode,
		StoredLDSearchMode,
		StoredILDSearchMode,
		BlindScanMode,
		LDSearchMode,
		HomingServiceMode,
		MaxScanMode
	} ScanningMode;

	typedef enum
	{
		InvalidScanSubMode = 0,
		AcquireSIPSITables,
		TableAcquireWait,
		AcquireNITOther,
		NITOtherAcquireWait,
		MaxScanSubMode
	}ScanningSubMode;

	typedef	enum
	{
		StIdle = 0,
		StStart,
		StTunerWait,
		StHomingServiceDetection,
		StAcquirePostcodekey,
		StPostcodekeyAcquireWait,
		StAcquireRegionkey,
		StRegionkeyAcquireWait,
		StAcquireSI,
		StSIAcquireWait,
		StServiceInstallWait,
		StServiceInstallComplete,
		StMax
	}SvcScanState;

	typedef	enum
	{
		EvStart = 0,
		EvStop,
		EvStartTuning,
		EvCheckLock,
		EvIdentifyHomingService,
		EvStartTableCollection,
		EvDataAvailable,
		EvDataNotAvailable,
		EvIdentifyBouquet,
		EvInstallComplete,
		EvMax
	}SvcScanEvents;

	typedef struct HomingMuxData
	{
		Nat32	Frequency;
		Nat8	Polarization;
		Nat16	SatelliteId;
	} HomingMuxData;

	typedef struct HomingServiceInfo
	{
		int Frequency;
		int Polarization;
		Bool IsDataValid;
		Bool BarkerValid;
		Nat16 ServiceId;
		Nat16 PID[FREESAT_MAX_TUNNELED_PID_PER_SERVICE];
		Nat32 TunnelledDataTypeBitMap;
	}HomingServiceInfo;

	typedef struct LinkageServiceInfo
	{
		int Frequency;
		int Polarization;
		Nat16 Onid;
		Nat16 Tsid;
		Nat16 ServiceId;
		Nat32 LinkageTypeBitMap;
	}LinkageServiceInfo;

	typedef struct InsInstance
	{
		int State;
		int LnbNumber;
		int LnbType;
		int InstallationMode;
		int IntallationState;
		Nat16 BouquetId;
		Nat16 RegionId;
		Nat32 FactoryMuxIndex;
		Nat32 StoredLDServiceIndex;
		Nat32 MaxStoredLDServiceIndex;
		Nat32 StoredILDServiceIndex;
		Nat32 MaxStoredILDServiceIndex;
		Nat32 LinkageServiceIndex;
		Nat32 NumOfLinkageService;
		Bool BlindScanInProgress;
		ScanningMode ScanMode;
		ScanningSubMode ScanSubMode;
		HomingServiceInfo mHomingServiceInfo;
		LinkageServiceInfo mLinkageServiceInfo[MAX_LINKAGE_SERVICE];
	} InsInstance;

	static Pump mPump;
	static InsInstance mInstStatus;
	static int s__mConstModuleLifeCycle;
	static HomingMuxData s__FreesatPackageDetails[NO_OF_HOMING_MUX];
	static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
	static FunctionNat32 s__FreesatHomingSrvDetectionActionMatrix[MaxScanMode][MaxScanSubMode];
	static Bool mInNITActualMode;
	

	void PumpHandler(int event, Nat32 param);

	/*State machine function*/
	void FuncStartServiceScan (Nat32 param);
	void FuncStartTuning (Nat32 param);
	void FuncCheckLockStatus(Nat32 param);
	void FuncIdentifyHomingService(Nat32 param);
	void FuncStartTableCollection(Nat32 param);
	void FuncIdentifyBouquet(Nat32 param);
	void FuncDataAvailable(Nat32 value);
	void FuncDataNotAvailable(Nat32 value);
	void FuncStopServiceScan(Nat32 value);
	void FuncInstallComplete(Nat32 param);

	void mAcquireSIPSITables(Nat32 param);
	void mCheckDataAvailable(Nat32 param);
	void mAcquireNitOther(Nat32 param);
	void mIdentifyHomingServiceFromPMT(Nat32 param);
	void mStoreLinkageServiceList(Nat32 param);
	void mCheckBATAvailability(Nat32 param);

	void mStationFound(void);
	void mNoStationFound(void);
	void mOnSdmStoppedCollection(void);
	void mGetLnbDetails(int SatId);
	void mGetCurrentTunerParams (HsvInstallationPTC *ptc);
	void mSwitchScanMode(void);
public:

	CHsvDvbsFreesat_mScan()
	{
		idataacqN = this;
		isvcscan = this;
		isvcscanctrlN = this;
		isvcscandata = this;
		isvcscanpow = this;
		iscansdsd = this;
		plfApidvbsN = this;
	}
	virtual ~CHsvDvbsFreesat_mScan();
};

#endif

