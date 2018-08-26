#ifndef  _CHSVDVBSDIGITURK_MSCAN_PRIV_H
#define  _CHSVDVBSDIGITURK_MSCAN_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScanData.h>
#include <IHsvPower.h>
#include <IHsvDigitalScanSdsdData.h>
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
#include <IHsvSatelliteUtility.h>
#include <CS2MwBase.h>
class CHsvDvbsDigiTurk_mScan_Priv;
#define CLASSSCOPE CHsvDvbsDigiTurk_mScan_Priv::
#include "locals_mScan.h"

class CHsvDvbsDigiTurk_mScan_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsDigiTurk_mScan_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mScan.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDigitalAcquisitionNotifyImpl(CHsvDvbsDigiTurk_mScan_Priv,idataacqN);
IHsvSatellitePackageInstallationImpl(CHsvDvbsDigiTurk_mScan_Priv,iscan);
IHsvSdmControlNotifyExImpl(CHsvDvbsDigiTurk_mScan_Priv,iscanctrlN);
IHsvDigitalScanDataImpl(CHsvDvbsDigiTurk_mScan_Priv,iscandata);
IHsvPowerImpl(CHsvDvbsDigiTurk_mScan_Priv,iscanpow);
IHsvDigitalScanSdsdDataImpl(CHsvDvbsDigiTurk_mScan_Priv,isdsddata);
IHsvSatelliteFrontEndNotifyImpl(CHsvDvbsDigiTurk_mScan_Priv,plfApidvbsN);
public:
ProvidesInterface<IHsvDigitalAcquisitionNotify>	idataacqN;

ProvidesInterface<IHsvSatellitePackageInstallation>	iscan;

ProvidesInterface<IHsvSdmControlNotifyEx>	iscanctrlN;

ProvidesInterface<IHsvDigitalScanData>	iscandata;

ProvidesInterface<IHsvPower>	iscanpow;

ProvidesInterface<IHsvDigitalScanSdsdData>	isdsddata;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatelliteUtility>	util;
private:
Pumpdefines(CHsvDvbsDigiTurk_mScan_Priv);

public:
CHsvDvbsDigiTurk_mScan_Priv():i__idataacqN(this),i__iscan(this),i__iscanctrlN(this),i__iscandata(this),i__iscanpow(this),i__isdsddata(this),i__plfApidvbsN(this)
{
idataacqN	=	&i__idataacqN;
iscan	=	&i__iscan;
iscanctrlN	=	&i__iscanctrlN;
iscandata	=	&i__iscandata;
iscanpow	=	&i__iscanpow;
isdsddata	=	&i__isdsddata;
plfApidvbsN	=	&i__plfApidvbsN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#define iinsN_EventRegionScanEnd	IHsvSatelliteInstallationNotify_EventRegionScanEnd
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
#define insstate_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
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
#define insstate_InstallationSSbyUpdate	IHsvSatelliteInstallation_InstallationSSbyUpdate
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
#define insstate_StartTricolorRegionParsing()	insstate->StartTricolorRegionParsing()
#define insstate_SetTricolorRegionIndex(indx)	insstate->SetTricolorRegionIndex(indx)
#define insstate_GetTricolorRegionNames(names)	insstate->GetTricolorRegionNames(names)
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsDigiTurk_mScan_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define satfeapi_iPresent() (satfeapi.Present())
#define satfeapi_PolarisationHorizontal	IHsvSatelliteFrontEnd_PolarisationHorizontal
#define satfeapi_PolarisationVertical	IHsvSatelliteFrontEnd_PolarisationVertical
#define satfeapi_BlindScanModeNormal	IHsvSatelliteFrontEnd_BlindScanModeNormal
#define satfeapi_BlindScanModeMinimal	IHsvSatelliteFrontEnd_BlindScanModeMinimal
#define satfeapi_SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots)	satfeapi->SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots)
#define satfeapi_StartSatelliteBlindScan(LnbNumber,Mode)	satfeapi->StartSatelliteBlindScan(LnbNumber,Mode)
#define satfeapi_ContinueSatelliteBlindScan()	satfeapi->ContinueSatelliteBlindScan()
#define satfeapi_AbortSatelliteBlindScan(LnbNumber)	satfeapi->AbortSatelliteBlindScan(LnbNumber)
#define satfeapi_GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth)	satfeapi->GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth)
#define satfeapi_UnicableEnable(LnbNumber,Enable)	satfeapi->UnicableEnable(LnbNumber,Enable)
#define satfeapi_IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization)	satfeapi->IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization)
#define strapi_iPresent() (strapi.Present())
#define strapi_GetSize(dest,spid)	strapi->GetSize(dest,spid)
#define strapi_GetIndex(dest,spid,key1,key2,key3,index)	strapi->GetIndex(dest,spid,key1,key2,key3,index)
#define strapi_GetByKey(dest,spid,key1,key2,key3,val)	strapi->GetByKey(dest,spid,key1,key2,key3,val)
#define strapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	strapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define strapi_GetByIndex(dest,spid,index,val)	strapi->GetByIndex(dest,spid,index,val)
#define util_iPresent() (util.Present())
#define util_ResetData()	util->ResetData()
#define util_CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)	util->CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)
#define util_AddEntryToList(Entry)	util->AddEntryToList(Entry)
#define util_IsDuplicate(Entry)	util->IsDuplicate(Entry)
#define util_ReadBarkerMuxData(Data)	util->ReadBarkerMuxData(Data)
#define util_WriteBarkerMuxData(Data)	util->WriteBarkerMuxData(Data)
#define util_ResetBarkerMuxData()	util->ResetBarkerMuxData()
#define iscan_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define iscan_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define iscan_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define iscan_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define iscan_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define iscan_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define iscanctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iscanctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iscanctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iscanctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iscanctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iscanctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iscanctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iscanctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iscanctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iscanctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iscanctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iscanctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iscanctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iscanctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iscanctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iscanctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define iscanctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define iscanctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define iscanctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define iscanctrlN_FST	IHsvSdmControlNotifyEx_FST
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mScan.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

