#ifndef  _CHSVDVBSASTRA_MSCAN_H
#define  _CHSVDVBSASTRA_MSCAN_H 

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
#include <CS2MwBase.h>

class CHsvDvbsAstra_mScan;

typedef void (CHsvDvbsAstra_mScan:: *AstraFunctionNat32)(Nat32);

#define	ASTRA_NO_OF_HOMING_MUX		(5)

typedef	enum 
{
	AstraStIdle = 0,
	AstraStStart,
	AstraStTunerWait,
	AstraStDemuxWait,
	AstraStAcquireWait,
	AstraStMax
} AstraSvaScanState;
typedef	enum 
{
	AstraEvStart = 0,
	AstraEvStop,
	AstraEvDataAvailable,
	AstraEvDataNotAvailable,
	AstraEvDataAcquired,
	AstraEvStartTuning,
	AstraEvCheckLock,
	AstraEvSdmStopped,
	AstraEvMax
} AstraSvcScanEvents;

typedef	enum 
{
	Invalid = 0,
	Homing = 1,
	AcquireNIT,
	AcquireSGT,
	AcquireServices
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
typedef struct _SGTReferanceData 
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
	int 	SGTPid;
} ReferanceSGTData;

typedef struct AstraInsInstance 
{
	int	State;
	int	LnbNumber;
	int	LnbType;
	int	InstallationMode;
	int	IntallationState;
	int	CurrSdsdIndex;
	int	NumOfSDSD;
	int	HomingMuxIndex;
	ReferanceNITData RefNITData;
	ReferanceSGTData RefSGTData;
	ScanningMode ScanMode;
} AstraInsInstance;


typedef struct _AstraHomingMuxData 
{
	Nat32	Frequency;
	Nat8	Polarization;
	Nat16	SatelliteId;
	Nat8	ModulationSystem;
	Nat8	ModulationType;
	Nat8	FECInner;
	Nat8	RollOffFactor;
	Nat8	Pilots;
} AstraHomingMuxData;



class CHsvDvbsAstra_mScan: private IHsvDigitalAcquisitionNotify,IHsvSatellitePackageInstallation,IHsvSdmControlNotifyEx,IHsvDigitalScanData,IHsvPower,IHsvSatelliteFrontEndNotify,public CS2MwBase
{
public:
ProvidesInterface<IHsvDigitalAcquisitionNotify>	idataacqN;

ProvidesInterface<IHsvSatellitePackageInstallation>	isvcscan;

ProvidesInterface<IHsvSdmControlNotifyEx>	isvcscanctrlN;

ProvidesInterface<IHsvDigitalScanData>	isvcscandata;

ProvidesInterface<IHsvPower>	isvcscanpow;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

//Required interfaces

RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IHsvPower>	isortpow;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvPower>	ibckgndpow;


private:
Pumpdefines(CHsvDvbsAstra_mScan);


private:
static const char SvcScanEventNames[AstraEvMax+1][32];
int mConstModuleLifeCycle;
static int s__mConstModuleLifeCycle;
AstraInsInstance mInstStatus;
static AstraInsInstance s__mInstStatus;
Pump mPump;
static Pump s__mPump;
AstraHomingMuxData AstraDigitalPackageDetails[ASTRA_NO_OF_HOMING_MUX];
static AstraHomingMuxData s__AstraDigitalPackageDetails[ASTRA_NO_OF_HOMING_MUX];
AstraFunctionNat32 EventActionMatrix[AstraEvMax][AstraStMax];
static AstraFunctionNat32 s__EventActionMatrix[AstraEvMax][AstraStMax];

public:
CHsvDvbsAstra_mScan()
{
	idataacqN	=	this;
	isvcscan	=	this;
	isvcscanctrlN	=	this;
	isvcscandata	=	this;
	isvcscanpow	=	this;
	plfApidvbsN	=	this;

	
	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	mInstStatus	=	s__mInstStatus;
	mPump	=	s__mPump;
	memcpy((void*)AstraDigitalPackageDetails,(void*)s__AstraDigitalPackageDetails,sizeof(AstraDigitalPackageDetails));
	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
}
virtual ~CHsvDvbsAstra_mScan()
{
}
/*IHsvDigitalAcquisitionNotify*/
virtual void OnDataAquired(Bool Status);
/*IHsvSatellitePackageInstallation*/
virtual int GetCurrentInstallationState(int * mode,int * state);
virtual FResult StartInstallation(int Source,int Lnb,int Mode);
virtual FResult StopInstallation();
virtual FResult WriteBarkerMuxData();
virtual int GetNumberOfTvChannelsFound(int Mode,int Lnb);
virtual int GetNumberofRadioChannelsFound(int Mode,int Lnb);
virtual int GetNumberOfTvChannelsRemoved(int Mode,int Lnb);
virtual int GetNumberofRadioChannelsRemoved(int Mode,int Lnb);
virtual int GetNumberOfDigitalChannelsAdded();
virtual int GetNumberOfDigitalChannelsRemoved();
virtual int GetNumberOfDigitalChannelsMoved();
virtual FResult LoadManualInstallationDefaultValues();
virtual FResult StoreManualInstallationValues();
virtual Bool SetManualInstallationAttributes(int AttributeId,int Value);
virtual int GetAttribute(int Mode,int AttributeId);
virtual int GetScanProgressStatus(int Mode);
virtual void GetSIDetails(HsvSDMSIDataValues * SiValues);
virtual FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);

virtual FResult GetTricolorRegionNames(Nat16 **names, int *len);
virtual FResult SetTricolorRegionIndex(int index);
virtual FResult StartTricolorRegionParsing ();

/*IHsvSdmControlNotifyEx*/
virtual void OnEvent(HsvDemux dmx,int eventid,int value);
/*IHsvDigitalScanData*/
virtual void GetPtcInfo(HsvInstallationPTC * ptc);
virtual int GetInstallationVersion();
virtual void GetPtcInfoForSdSd(HsvInstallationPTC * ptc);
virtual void SyncComplete();
/*IHsvPower*/
virtual void Init();
virtual void TurnOn();
virtual void TurnOff();
/*IHsvSatelliteFrontEndNotify*/
virtual void OnLockChanged(Bool LockState);
virtual void OnBlindScanEnd();


/*Local functions*/

void PumpHandler(int event, Nat32 param);
void FuncStopServiceScan (Nat32 param1);
void mStationFound ();
void mNoStationFound ();
void FuncDataAvailable (Nat32 param1);
void FuncNoDataAvailable (Nat32 param1);
void FuncSdmStopped(Nat32  param);
void FuncDataAcquired (Nat32 param1);
void FuncCheckLockStatus(Nat32 Cookie);
void FuncStartTuning (Nat32 param1);
void FuncStartServiceScan (Nat32 param1);
void mGetLnbDetails(int SatId);
void mGetCurrentTunerParams (HsvInstallationPTC *ptc);
Bool mStoreRefNITDetails();
Bool mStoreRefSGTDetails();
Bool mStoreSGTPID();
int  MapRollOffFactor(int RollOff);



};

#define ctrl_iPresent() (ctrl.Present())
#define ctrl_Idle	IHsvSdmControl2_Idle
#define ctrl_Minimal	IHsvSdmControl2_Minimal
#define ctrl_Normal	IHsvSdmControl2_Normal
#define ctrl_External	IHsvSdmControl2_External
#define ctrl_CrossCarraige	IHsvSdmControl2_CrossCarraige
#define ctrl_NormalPlusPmt	IHsvSdmControl2_NormalPlusPmt
#define ctrl_M7Minimal	IHsvSdmControl2_M7Minimal
#define ctrl_HomingMuxData	IHsvSdmControl2_HomingMuxData
#define ctrl_PkgBuildMode	IHsvSdmControl2_PkgBuildMode
#define ctrl_FransatNormal	IHsvSdmControl2_FransatNormal
#define ctrl_MinimalPlusBat	IHsvSdmControl2_MinimalPlusBat
#define ctrl_AstraSGT	IHsvSdmControl2_AstraSGT
#define ctrl_Invalid	IHsvSdmControl2_Invalid
#define ctrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ctrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ctrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ctrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ctrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
#define ctrl_FNTAvailable	IHsvSdmControl2_FNTAvailable
#define ctrl_FSTAvailable	IHsvSdmControl2_FSTAvailable
#define ctrl_BATAvailable	IHsvSdmControl2_BATAvailable
#define ctrl_GetMode(dmx)	ctrl->GetMode(dmx)
#define ctrl_GetStatus(dmx)	ctrl->GetStatus(dmx)
#define ctrl_StartCollection(dmx,mode)	ctrl->StartCollection(dmx,mode)
#define ctrl_StopCollection(dmx)	ctrl->StopCollection(dmx)
#define err_iPresent() (err.Present())
#define err_Ok	IHsvErrorCodeEx_Ok
#define err_BadParameter	IHsvErrorCodeEx_BadParameter
#define err_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define err_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define err_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define err_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define err_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define err_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define err_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define err_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define err_FileError	IHsvErrorCodeEx_FileError
#define err_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define err_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define err_NotSupported	IHsvErrorCodeEx_NotSupported
#define err_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define err_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define err_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define err_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define err_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define err_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define err_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define err_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define err_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define err_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define err_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define err_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define err_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define err_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define err_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define err_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define err_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define err_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define err_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define err_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define err_DiseqcError	IHsvErrorCodeEx_DiseqcError
#define err_TunerError	IHsvErrorCodeEx_TunerError
#define err_UsbPathNotFound	IHsvErrorCodeEx_UsbPathNotFound
#define iacqpow_iPresent() (iacqpow.Present())
#define iacqpow_Init()	iacqpow->Init()
#define iacqpow_TurnOn()	iacqpow->TurnOn()
#define iacqpow_TurnOff()	iacqpow->TurnOff()
#define idataacq_iPresent() (idataacq.Present())
#define idataacq_Homing	IHsvDigitalAcquisition_Homing
#define idataacq_Fallback	IHsvDigitalAcquisition_Fallback
#define idataacq_Normal	IHsvDigitalAcquisition_Normal
#define idataacq_Background	IHsvDigitalAcquisition_Background
#define idataacq_Initialise(LnbNumber)	idataacq->Initialise(LnbNumber)
#define idataacq_AcquireData(Mode)	idataacq->AcquireData(Mode)
#define idataacq_AcquireDataOnTimeout()	idataacq->AcquireDataOnTimeout()
#define idataacq_GetNumberOfDigitalChannelsFound()	idataacq->GetNumberOfDigitalChannelsFound()
#define idataacq_GetNumberOfDigitalChannelsRemoved()	idataacq->GetNumberOfDigitalChannelsRemoved()
#define idataacq_GetNumberOfTvChannelsFound()	idataacq->GetNumberOfTvChannelsFound()
#define idataacq_GetNumberOfRadioChannelsFound()	idataacq->GetNumberOfRadioChannelsFound()
#define idataacq_GetNumberOfTvChannelsRemoved()	idataacq->GetNumberOfTvChannelsRemoved()
#define idataacq_GetNumberofRadioChannelsRemoved()	idataacq->GetNumberofRadioChannelsRemoved()
#define idataacq_StoreBarkerMuxDetails()	idataacq->StoreBarkerMuxDetails()
#define idataacq_SyncTemporaryTableRecords()	idataacq->SyncTemporaryTableRecords()
#define idataacq_GetNumberOfSdsds()	idataacq->GetNumberOfSdsds()
#define idataacq_GetSdsdByIndex(count,SdSdEntry)	idataacq->GetSdsdByIndex(count,SdSdEntry)
#define idataacq_GetNumberOfTvChannelsInLnb(Lnb)	idataacq->GetNumberOfTvChannelsInLnb(Lnb)
#define idataacq_GetNumberOfRadioChannelsInLnb(Lnb)	idataacq->GetNumberOfRadioChannelsInLnb(Lnb)
#define iinsN_iPresent() (iinsN.Present())
#define iinsN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define iinsN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define iinsN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
#define iinsN_EventInsFailed	IHsvSatelliteInstallationNotify_EventInsFailed
#define iinsN_EventSatelliteFound	IHsvSatelliteInstallationNotify_EventSatelliteFound
#define iinsN_EventSatelliteNotFound	IHsvSatelliteInstallationNotify_EventSatelliteNotFound
#define iinsN_EventSortingStarted	IHsvSatelliteInstallationNotify_EventSortingStarted
#define iinsN_EventSortStopped	IHsvSatelliteInstallationNotify_EventSortStopped
#define iinsN_EventSortCompleted	IHsvSatelliteInstallationNotify_EventSortCompleted
#define iinsN_EventSortInProgress	IHsvSatelliteInstallationNotify_EventSortInProgress
#define iinsN_EventChannelFound	IHsvSatelliteInstallationNotify_EventChannelFound
#define iinsN_EventChannelNotFound	IHsvSatelliteInstallationNotify_EventChannelNotFound
#define iinsN_EventInsProgress	IHsvSatelliteInstallationNotify_EventInsProgress
#define iinsN_EventInsCompletedForLnb	IHsvSatelliteInstallationNotify_EventInsCompletedForLnb
#define iinsN_EventSatLnbRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted
#define iinsN_EventContentLibRead	IHsvSatelliteInstallationNotify_EventContentLibRead
#define iinsN_EventPkgInstallStart	IHsvSatelliteInstallationNotify_EventPkgInstallStart
#define iinsN_EventPkgInstallEnd	IHsvSatelliteInstallationNotify_EventPkgInstallEnd
#define iinsN_EventLNBStart	IHsvSatelliteInstallationNotify_EventLNBStart
#define iinsN_EventLNBEnd	IHsvSatelliteInstallationNotify_EventLNBEnd
#define iinsN_EventSatLnbRemovalStarted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted
#define iinsN_EventSatRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatRemovalCompleted
#define iinsN_EventPackageInstallFailed	IHsvSatelliteInstallationNotify_EventPackageInstallFailed
#define iinsN_EventPackageId	IHsvSatelliteInstallationNotify_EventPackageId
#define iinsN_EventPredefinedListCopySuccesful	IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful
#define iinsN_EventPredefinedListCopyGenericError	IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError
#define iinsN_EventPredefinedListCopyOlderVersion	IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion
#define iinsN_EventDifferentSatelliteFound	IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound
#define iinsN_EventPkgParsingStarted	IHsvSatelliteInstallationNotify_EventPkgParsingStarted
#define iinsN_EventPkgParsingCompleted	IHsvSatelliteInstallationNotify_EventPkgParsingCompleted
#define iinsN_EventTriggerBckgndUpdateInstall	IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall
#define iinsN_OnEvent(eventid,value)	iinsN->OnEvent(eventid,value)
#define insstate_iPresent() (insstate.Present())
#define insstate_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define insstate_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define insstate_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define insstate_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define insstate_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define insstate_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define insstate_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define insstate_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define insstate_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define insstate_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define insstate_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define insstate_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define insstate_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define insstate_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define insstate_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define insstate_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define insstate_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define insstate_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define insstate_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define insstate_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define insstate_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define insstate_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define insstate_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define insstate_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define insstate_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define insstate_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define insstate_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define insstate_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define insstate_GetCurrentInstallationState(mode,state)	insstate->GetCurrentInstallationState(mode,state)
#define insstate_StartInstallation(Source,Lnb,Mode)	insstate->StartInstallation(Source,Lnb,Mode)
#define insstate_StopInstallation()	insstate->StopInstallation()
#define insstate_ResetInstallation()	insstate->ResetInstallation()
#define insstate_GetNumberOfTvChannelsFound(Lnb)	insstate->GetNumberOfTvChannelsFound(Lnb)
#define insstate_GetNumberofRadioChannelsFound(Lnb)	insstate->GetNumberofRadioChannelsFound(Lnb)
#define insstate_GetNumberOfTvChannelsRemoved(Lnb)	insstate->GetNumberOfTvChannelsRemoved(Lnb)
#define insstate_GetNumberofRadioChannelsRemoved(Lnb)	insstate->GetNumberofRadioChannelsRemoved(Lnb)
#define insstate_GetSatelliteName(Lnb,SatelliteName)	insstate->GetSatelliteName(Lnb,SatelliteName)
#define insstate_GetNumberOfDigitalChannelsAdded()	insstate->GetNumberOfDigitalChannelsAdded()
#define insstate_GetNumberOfDigitalChannelsRemoved()	insstate->GetNumberOfDigitalChannelsRemoved()
#define insstate_GetNumberOfDigitalChannelsMoved()	insstate->GetNumberOfDigitalChannelsMoved()
#define insstate_IdentifyPackagesAvailable()	insstate->IdentifyPackagesAvailable()
#define insstate_GetTotalNumberOfPackagesFound()	insstate->GetTotalNumberOfPackagesFound()
#define insstate_GetPackageByIndex(Index,Package)	insstate->GetPackageByIndex(Index,Package)
#define insstate_SetUserPackageIndex(PackageIndex)	insstate->SetUserPackageIndex(PackageIndex)
#define insstate_GetUserPackageIndex(PackageIndex,IsPackage)	insstate->GetUserPackageIndex(PackageIndex,IsPackage)
#define insstate_GetInstalledSatellites(mode,SatelliteEntries)	insstate->GetInstalledSatellites(mode,SatelliteEntries)
#define insstate_InstallAddedSatellites()	insstate->InstallAddedSatellites()
#define insstate_ResetAddedSatellites()	insstate->ResetAddedSatellites()
#define insstate_RemoveSatelliteEntry(LnbNumber)	insstate->RemoveSatelliteEntry(LnbNumber)
#define insstate_GetSatelliteSignalStrength(LnbNumber)	insstate->GetSatelliteSignalStrength(LnbNumber)
#define insstate_GetSatelliteSignalQuality(LnbNumber)	insstate->GetSatelliteSignalQuality(LnbNumber)
#define insstate_LoadManualInstallationDefaultValues()	insstate->LoadManualInstallationDefaultValues()
#define insstate_StoreManualInstallationValues()	insstate->StoreManualInstallationValues()
#define insstate_GetAttribute(Mode,AttributeId)	insstate->GetAttribute(Mode,AttributeId)
#define insstate_SetAttribute(Mode,AttributeId,Value)	insstate->SetAttribute(Mode,AttributeId,Value)
#define insstate_GetScanProgressStatus(Mode)	insstate->GetScanProgressStatus(Mode)
#define insstate_GetSITableIds(NetworkID,BouquetID)	insstate->GetSITableIds(NetworkID,BouquetID)
#define insstate_GetPackageName(PackageId,PackageName)	insstate->GetPackageName(PackageId,PackageName)
#define insstate_GetSIDetails(SiValues)	insstate->GetSIDetails(SiValues)
#define insstate_EnableUnicable(LnbNumber,Enable)	insstate->EnableUnicable(LnbNumber,Enable)
#define insstate_StopSignalStrengthMeas(LnbNumber)	insstate->StopSignalStrengthMeas(LnbNumber)
#define insstate_GetSignalQuality(Param)	insstate->GetSignalQuality(Param)
#define insstate_StartSignalStrengthMeas(LnbNumber)	insstate->StartSignalStrengthMeas(LnbNumber)
#define insstate_GetSignalStrength(param)	insstate->GetSignalStrength(param)
#define insstate_StartPredefinedListCopy()	insstate->StartPredefinedListCopy()
#define insstate_GetFirstInstalledChannel()	insstate->GetFirstInstalledChannel()
#define insstate_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	insstate->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define isigstr_iPresent() (isigstr.Present())
#define isigstr_InsQsm	IHsvInstallationSigStrength_InsQsm
#define isigstr_InsSsm	IHsvInstallationSigStrength_InsSsm
#define isigstr_Initialise()	isigstr->Initialise()
#define isigstr_GetSigStrengthRange(mode,min,max)	isigstr->GetSigStrengthRange(mode,min,max)
#define isigstr_GetSignalStrength(mode)	isigstr->GetSignalStrength(mode)
#define isigstr_GetMinSignalStrength(mode)	isigstr->GetMinSignalStrength(mode)
#define isigstr_GetMaxSignalStrength(mode)	isigstr->GetMaxSignalStrength(mode)
#define isigstr_GetActualSignalStrength(mode,cookie)	isigstr->GetActualSignalStrength(mode,cookie)
#define isigstr_StartSigStrMeasAll()	isigstr->StartSigStrMeasAll()
#define isigstr_StopSigStrMeasAll()	isigstr->StopSigStrMeasAll()
#define isigstr_UpdateSigStrRange()	isigstr->UpdateSigStrRange()
#define isigstr_GetSigStrengthMeasured()	isigstr->GetSigStrengthMeasured()
#define isigstr_SetSigStrengthMeasured(flag)	isigstr->SetSigStrengthMeasured(flag)
#define isigstr_StartSigStrMeas(measmode)	isigstr->StartSigStrMeas(measmode)
#define isigstr_StopSigStrMeas(measmode)	isigstr->StopSigStrMeas(measmode)
#define isigstr_IsSignalStrengthMeasurementValid(measmode)	isigstr->IsSignalStrengthMeasurementValid(measmode)
#define isortpow_iPresent() (isortpow.Present())
#define isortpow_Init()	isortpow->Init()
#define isortpow_TurnOn()	isortpow->TurnOn()
#define isortpow_TurnOff()	isortpow->TurnOff()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgdb_iPresent() (pgdb.Present())
#define pgdb_GetCurrentTable()	pgdb->GetCurrentTable()
#define pgdb_SelectTable(tableid)	pgdb->SelectTable(tableid)
#define pgdb_ClearTable(tableid)	pgdb->ClearTable(tableid)
#define pgdb_IsSupported(tableid)	pgdb->IsSupported(tableid)
#define pgdb_CommitTable(tableid)	pgdb->CommitTable(tableid)
#define pgdb_LoadTable(tableid)	pgdb->LoadTable(tableid)
#define pgdb_GetNoRecords(tableid)	pgdb->GetNoRecords(tableid)
#define pgdb_GetByKey(tableid,channeldata)	pgdb->GetByKey(tableid,channeldata)
#define pgdb_GetIndex(tableid,index,channeldata)	pgdb->GetIndex(tableid,index,channeldata)
#define pgdb_GetByIndex(tableid,index,channeldata)	pgdb->GetByIndex(tableid,index,channeldata)
#define pgdb_GetRange(tableid,noofkeys,channeldata,from,to)	pgdb->GetRange(tableid,noofkeys,channeldata,from,to)
#define pgdb_Add(tableid,channeldata)	pgdb->Add(tableid,channeldata)
#define pgdb_Update(tableid,channeldata)	pgdb->Update(tableid,channeldata)
#define pgdb_Delete(tableid,channeldata)	pgdb->Delete(tableid,channeldata)
#define pgdb_EnableAutoCommit(enable)	pgdb->EnableAutoCommit(enable)
#define pgdb_ChannelTableChanged()	pgdb->ChannelTableChanged()
#define pgdb_Initialise(tableid,channeldata)	pgdb->Initialise(tableid,channeldata)
#define pgdb_MasterEnableEvents(Status)	pgdb->MasterEnableEvents(Status)
#define pgdb_SaveChannelMapsToBackup()  pgdb->SaveChannelMapsToBackup()
#define pgdb_LoadChannelMapsFromBackup pgdb->LoadChannelMapsFromBackup()
#define pgdb_SqliteDatabase		IHsvProgramDatabase_SqliteDatabase
#define pgdb_TempDatabase		IHsvProgramDatabase_TempDatabase
#define pgdb_SelectChannelDatabase(databaseId)		pgdb->SelectChannelDatabase(databaseId)
#define pgdb_SyncDatabase(fromDatabaseId,toDatabaseId)		pgdb->SyncDatabase(fromDatabaseId,toDatabaseId)
#define pgdb_AddInIndex(tableid,index,channeldata)	pgdb->AddInIndex(tableid,index,channeldata)
#define pgdb_BeginSqliteTransaction()		pgdb->BeginSqliteTransaction()
#define pgdb_CommitSqliteTransaction()		pgdb->CommitSqliteTransaction()
#define pgdbconst_iPresent() (pgdbconst.Present())
#define pgdbconst_Antenna	IHsvProgramDatabaseConstants_Antenna
#define pgdbconst_Cable	IHsvProgramDatabaseConstants_Cable
#define pgdbconst_TempAntenna	IHsvProgramDatabaseConstants_TempAntenna
#define pgdbconst_TempCable	IHsvProgramDatabaseConstants_TempCable
#define pgdbconst_Satellite	IHsvProgramDatabaseConstants_Satellite
#define pgdbconst_TempSatellite	IHsvProgramDatabaseConstants_TempSatellite
#define pgdbconst_Analog	IHsvProgramDatabaseConstants_Analog
#define pgdbconst_DigitalTS	IHsvProgramDatabaseConstants_DigitalTS
#define pgdbconst_DigitalService	IHsvProgramDatabaseConstants_DigitalService
#define pgdbconst_Preset	IHsvProgramDatabaseConstants_Preset
#define pgdbconst_FrequencyMapTable	IHsvProgramDatabaseConstants_FrequencyMapTable
#define pgdbconst_CurrentDigitalService	IHsvProgramDatabaseConstants_CurrentDigitalService
#define pgdbconst_CurrentDigitalTS	IHsvProgramDatabaseConstants_CurrentDigitalTS
#define pgdbconst_CurrentAnalog	IHsvProgramDatabaseConstants_CurrentAnalog
#define pgdbconst_CurrentPreset	IHsvProgramDatabaseConstants_CurrentPreset
#define pgdbconst_CurrentFrequencyMapTable	IHsvProgramDatabaseConstants_CurrentFrequencyMapTable
#define pgdbconst_SatInfo	IHsvProgramDatabaseConstants_SatInfo
#define pgdbconst_CurrentSatInfo	IHsvProgramDatabaseConstants_CurrentSatInfo
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsAstra_mScan::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define satfeapi_iPresent() (satfeapi.Present())
#define satfeapi_PolarisationHorizontal	IHsvSatelliteFrontEnd_PolarisationHorizontal
#define satfeapi_PolarisationVertical	IHsvSatelliteFrontEnd_PolarisationVertical
#define satfeapi_BlindScanModeNormal	IHsvSatelliteFrontEnd_BlindScanModeNormal
#define satfeapi_BlindScanModeMinimal	IHsvSatelliteFrontEnd_BlindScanModeMinimal
#define satfeapi_PilotsOFF	IHsvSatelliteFrontEnd_PilotsOFF
#define satfeapi_PilotsON	IHsvSatelliteFrontEnd_PilotsON
#define satfeapi_RollOffUnknown	IHsvSatelliteFrontEnd_RollOffUnknown
#define satfeapi_RollOffOP35	IHsvSatelliteFrontEnd_RollOffOP35
#define satfeapi_RollOffOP25	IHsvSatelliteFrontEnd_RollOffOP25
#define satfeapi_RollOffOP20	IHsvSatelliteFrontEnd_RollOffOP20
#define satfeapi_FECInnerUnknown	IHsvSatelliteFrontEnd_FECInnerUnknown
#define satfeapi_FECInner12			IHsvSatelliteFrontEnd_FECInner12
#define satfeapi_FECInner23			IHsvSatelliteFrontEnd_FECInner23
#define satfeapi_FECInner34			IHsvSatelliteFrontEnd_FECInner34
#define satfeapi_FECInner35			IHsvSatelliteFrontEnd_FECInner35
#define satfeapi_FECInner45			IHsvSatelliteFrontEnd_FECInner45
#define satfeapi_FECInner56			IHsvSatelliteFrontEnd_FECInner56
#define satfeapi_FECInner78			IHsvSatelliteFrontEnd_FECInner78
#define satfeapi_FECInner89			IHsvSatelliteFrontEnd_FECInner89
#define satfeapi_FECInner910			IHsvSatelliteFrontEnd_FECInner910
#define satfeapi_DVBSQPSK	IHsvSatelliteFrontEnd_DVBSQPSK
#define satfeapi_DVBSPSK8	IHsvSatelliteFrontEnd_DVBSPSK8
#define satfeapi_ModSysDVBS		IHsvSatelliteFrontEnd_ModSysDVBS
#define satfeapi_ModSysDVBS2		IHsvSatelliteFrontEnd_ModSysDVBS2
#define satfeapi_SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots)	satfeapi->SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots)
#define satfeapi_StartSatelliteBlindScan(LnbNumber,Mode)	satfeapi->StartSatelliteBlindScan(LnbNumber,Mode)
#define satfeapi_ContinueSatelliteBlindScan()	satfeapi->ContinueSatelliteBlindScan()
#define satfeapi_AbortSatelliteBlindScan(LnbNumber)	satfeapi->AbortSatelliteBlindScan(LnbNumber)
#define satfeapi_GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth)	satfeapi->GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth)
#define satfeapi_UnicableEnable(LnbNumber,Enable)	satfeapi->UnicableEnable(LnbNumber,Enable)
#define satfeapi_IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization)	satfeapi->IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization)
#define isvcscan_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define isvcscan_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define isvcscan_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define isvcscan_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define isvcscan_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define isvcscan_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define isvcscanctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define isvcscanctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define isvcscanctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define isvcscanctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define isvcscanctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define isvcscanctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define isvcscanctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define isvcscanctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define isvcscanctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define isvcscanctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define isvcscanctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define isvcscanctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define isvcscanctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define isvcscanctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define isvcscanctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define isvcscanctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define isvcscanctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define isvcscanctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define isvcscanctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define isvcscanctrlN_FST	IHsvSdmControlNotifyEx_FST
#define strapi_iPresent() (strapi.Present())
#define strapi_GetSize(dest,spid)	strapi->GetSize(dest,spid)
#define strapi_GetIndex(dest,spid,key1,key2,key3,index)	strapi->GetIndex(dest,spid,key1,key2,key3,index)
#define strapi_GetByKey(dest,spid,key1,key2,key3,val)	strapi->GetByKey(dest,spid,key1,key2,key3,val)
#define strapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	strapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define strapi_GetByIndex(dest,spid,index,val)	strapi->GetByIndex(dest,spid,index,val)
#define ibckgndpow_iPresent() (ibckgndpow.Present())
#define ibckgndpow_Init()	ibckgndpow->Init()
#define ibckgndpow_TurnOn()	ibckgndpow->TurnOn()
#define ibckgndpow_TurnOff()	ibckgndpow->TurnOff()

#endif

