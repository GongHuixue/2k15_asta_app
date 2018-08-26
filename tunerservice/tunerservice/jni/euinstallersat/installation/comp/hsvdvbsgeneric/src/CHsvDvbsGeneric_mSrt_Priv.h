#ifndef  _CHSVDVBSGENERIC_MSRT_PRIV_H
#define  _CHSVDVBSGENERIC_MSRT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScanData.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSorting.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvStreamNotify.h>
#include <CS2MwBase.h>
class CHsvDvbsGeneric_mSrt_Priv;
#define CLASSSCOPE CHsvDvbsGeneric_mSrt_Priv::
#include "locals_mSrt.h"

class CHsvDvbsGeneric_mSrt_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsGeneric_mSrt_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mSrt.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSatellitePackageInstallationImpl(CHsvDvbsGeneric_mSrt_Priv,isrt);
IHsvDigitalAcquisitionNotifyImpl(CHsvDvbsGeneric_mSrt_Priv,isrtAcqN);
IHsvSdmControlNotifyExImpl(CHsvDvbsGeneric_mSrt_Priv,isrtctrlN);
IHsvDigitalScanDataImpl(CHsvDvbsGeneric_mSrt_Priv,isrtdata);
IHsvSatelliteFrontEndNotifyImpl(CHsvDvbsGeneric_mSrt_Priv,isrtplfApidvbsN);
IHsvPowerImpl(CHsvDvbsGeneric_mSrt_Priv,isrtpow);
IHsvStreamNotifyImpl(CHsvDvbsGeneric_mSrt_Priv, isrtstrapiN);
public:
ProvidesInterface<IHsvSatellitePackageInstallation>	isrt;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	isrtAcqN;

ProvidesInterface<IHsvSdmControlNotifyEx>	isrtctrlN;

ProvidesInterface<IHsvDigitalScanData>	isrtdata;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	isrtplfApidvbsN;

ProvidesInterface<IHsvPower>	isrtpow;

ProvidesInterface<IHsvStreamNotify>	isrtstrapiN;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IHsvSorting>	isort;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat3;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvDvbsGeneric_mSrt_Priv);

public:
CHsvDvbsGeneric_mSrt_Priv():i__isrt(this),i__isrtAcqN(this),i__isrtctrlN(this),i__isrtdata(this),i__isrtplfApidvbsN(this),i__isrtpow(this), i__isrtstrapiN(this)
{
isrt	=	&i__isrt;
isrtAcqN	=	&i__isrtAcqN;
isrtctrlN	=	&i__isrtctrlN;
isrtdata	=	&i__isrtdata;
isrtplfApidvbsN	=	&i__isrtplfApidvbsN;
isrtpow	=	&i__isrtpow;
isrtstrapiN	=	&i__isrtstrapiN;
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
#define idvbset_iPresent() (idvbset.Present())
#define idvbset_AttributePackageId	IHsvSatelliteSettings_AttributePackageId
#define idvbset_AttributePackageOnly	IHsvSatelliteSettings_AttributePackageOnly
#define idvbset_AttributeAssetManager	IHsvSatelliteSettings_AttributeAssetManager
#define idvbset_LoadLnbParametersFromPersistent()	idvbset->LoadLnbParametersFromPersistent()
#define idvbset_GetLnbSettings(LnbSettings)	idvbset->GetLnbSettings(LnbSettings)
#define idvbset_SetLnbSettings(LnbSettings)	idvbset->SetLnbSettings(LnbSettings)
#define idvbset_ResetLnbSettings()	idvbset->ResetLnbSettings()
#define idvbset_GetDefaultValues(LnbSettingsEntry)	idvbset->GetDefaultValues(LnbSettingsEntry)
#define idvbset_ResetToDefaultLnbSettings()	idvbset->ResetToDefaultLnbSettings()
#define idvbset_GetAttribute(AttributeId)	idvbset->GetAttribute(AttributeId)
#define idvbset_SetAttribute(AttributeId,Value)	idvbset->SetAttribute(AttributeId,Value)
#define idvbset_SaveSatelliteSettingsToPersistent()	idvbset->SaveSatelliteSettingsToPersistent()
#define idvbset_CommitSatelliteSettingsToPersistent()	idvbset->CommitSatelliteSettingsToPersistent()
#define idvbset_ReLoadLnbParametersFromPersistent()	idvbset->ReLoadLnbParametersFromPersistent()
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
#define isort_iPresent() (isort.Present())
#define isort_Sort(PackageIndex)	isort->Sort(PackageIndex)
#define iutil_iPresent() (iutil.Present())
#define iutil_ResetData()	iutil->ResetData()
#define iutil_CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)	iutil->CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)
#define iutil_AddEntryToList(Entry)	iutil->AddEntryToList(Entry)
#define iutil_IsDuplicate(Entry)	iutil->IsDuplicate(Entry)
#define iutil_ReadBarkerMuxData(Data)	iutil->ReadBarkerMuxData(Data)
#define iutil_WriteBarkerMuxData(Data)	iutil->WriteBarkerMuxData(Data)
#define iutil_ResetBarkerMuxData()	iutil->ResetBarkerMuxData()
#define mctl_iPresent() (mctl.Present())
#define mctl_InvalidMedia	IHsvMediaControl_InvalidMedia
#define mctl_Video	IHsvMediaControl_Video
#define mctl_Audio	IHsvMediaControl_Audio
#define mctl_Pcr	IHsvMediaControl_Pcr
#define mctl_Subtitle	IHsvMediaControl_Subtitle
#define mctl_ClosedCaption	IHsvMediaControl_ClosedCaption
#define mctl_Teletext	IHsvMediaControl_Teletext
#define mctl_IPSubtitle	IHsvMediaControl_IPSubtitle
#define mctl_IPClosedCaption	IHsvMediaControl_IPClosedCaption
#define mctl_InvalidSelector	IHsvMediaControl_InvalidSelector
#define mctl_Language	IHsvMediaControl_Language
#define mctl_Type	IHsvMediaControl_Type
#define mctl_Pid	IHsvMediaControl_Pid
#define mctl_VIAssociation	IHsvMediaControl_VIAssociation
#define mctl_VIPrimaryAssociation	IHsvMediaControl_VIPrimaryAssociation
#define mctl_StreamType	IHsvMediaControl_StreamType
#define mctl_GetMediaSize(dest,media)	mctl->GetMediaSize(dest,media)
#define mctl_GetMediaByKey(dest,media,selector1,selector2,value)	mctl->GetMediaByKey(dest,media,selector1,selector2,value)
#define mctl_GetMediaIndex(dest,media,selector1,selecto2,index)	mctl->GetMediaIndex(dest,media,selector1,selecto2,index)
#define mctl_GetMediaByIndex(dest,media,index,value)	mctl->GetMediaByIndex(dest,media,index,value)
#define mctl_SetMedia(dest,media,selector,value)	mctl->SetMedia(dest,media,selector,value)
#define mctl_SetMediaWithProgram(dest,program,media,selector,value)	mctl->SetMediaWithProgram(dest,program,media,selector,value)
#define mctl_Play(dest)	mctl->Play(dest)
#define mctl_PlayMedia(dest,media)	mctl->PlayMedia(dest,media)
#define mctl_Stop(dest)	mctl->Stop(dest)
#define mctl_StopMedia(dest,media)	mctl->StopMedia(dest,media)
#define mctl_Flush(dest)	mctl->Flush(dest)
#define mctl_EnableMedia(dest,media)	mctl->EnableMedia(dest,media)
#define mctl_DisableMedia(dest,media)	mctl->DisableMedia(dest,media)
#define mctl_GetCurrentSelection(dest,media,selector)	mctl->GetCurrentSelection(dest,media,selector)
#define mctl_IsMediaPlaying(dest,media)	mctl->IsMediaPlaying(dest,media)
#define mctl_IsMediaEnabled(dest,media)	mctl->IsMediaEnabled(dest,media)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgdat3_iPresent() (pgdat3.Present())
#define pgdat3_BoolLock	pgdat3->BoolLock()
#define pgdat3_BoolFavorite	pgdat3->BoolFavorite()
#define pgdat3_BoolUserHidden	pgdat3->BoolUserHidden()
#define pgdat3_BoolSystemHidden	pgdat3->BoolSystemHidden()
#define pgdat3_BoolNewPreset	pgdat3->BoolNewPreset()
#define pgdat3_BoolFreeCiMode	pgdat3->BoolFreeCiMode()
#define pgdat3_BoolUpdateName	pgdat3->BoolUpdateName()
#define pgdat3_IntDeltaVolume	pgdat3->IntDeltaVolume()
#define pgdat3_Nat32DateStamp	pgdat3->Nat32DateStamp()
#define pgdat3_Nat32AppsCookie	pgdat3->Nat32AppsCookie()
#define pgdat3_Nat32TxtCookie	pgdat3->Nat32TxtCookie()
#define pgdat3_StringChannelName	pgdat3->StringChannelName()
#define pgdat3_StringExtChannelName	pgdat3->StringExtChannelName()
#define pgdat3_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat3_IntModulation	pgdat3->IntModulation()
#define pgdat3_IntSignalStrength	pgdat3->IntSignalStrength()
#define pgdat3_IntSignalQuality	pgdat3->IntSignalQuality()
#define pgdat3_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat3_IntNetworkId	pgdat3->IntNetworkId()
#define pgdat3_IntOriginalNwId	pgdat3->IntOriginalNwId()
#define pgdat3_IntTsid	pgdat3->IntTsid()
#define pgdat3_IntServiceId	pgdat3->IntServiceId()
#define pgdat3_IntServiceType	pgdat3->IntServiceType()
#define pgdat3_IntPmtPid	pgdat3->IntPmtPid()
#define pgdat3_IntPcrPid	pgdat3->IntPcrPid()
#define pgdat3_IntVideoPid	pgdat3->IntVideoPid()
#define pgdat3_IntVideoStreamType	pgdat3->IntVideoStreamType()
#define pgdat3_IntAudioPid	pgdat3->IntAudioPid()
#define pgdat3_IntAudioStreamType	pgdat3->IntAudioStreamType()
#define pgdat3_IntSecAudioPid	pgdat3->IntSecAudioPid()
#define pgdat3_IntSecAudioStreamType	pgdat3->IntSecAudioStreamType()
#define pgdat3_IntPresetNumber	pgdat3->IntPresetNumber()
#define pgdat3_IntModulationType	pgdat3->IntModulationType()
#define pgdat3_IntLCN	pgdat3->IntLCN()
#define pgdat3_IntPtc	pgdat3->IntPtc()
#define pgdat3_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat3_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat3_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat3_Antenna	IHsvProgramData3_Antenna
#define pgdat3_Cable	IHsvProgramData3_Cable
#define pgdat3_IntSystemHidden	pgdat3->IntSystemHidden()
#define pgdat3_IntNumericSelect	pgdat3->IntNumericSelect()
#define pgdat3_IntNewChannel	pgdat3->IntNewChannel()
#define pgdat3_StringSatelliteName	pgdat3->StringSatelliteName()
#define pgdat3_IntSrcambledStatus	pgdat3->IntSrcambledStatus()
#define pgdat3_IntInstalledSatelliteNumber	pgdat3->IntInstalledSatelliteNumber()
#define pgdat3_IntUserHidden	pgdat3->IntUserHidden()
#define pgdat3_FavoriteNumber	pgdat3->FavoriteNumber()
#define pgdat3_IntHbbTvOption	pgdat3->IntHbbTvOption()
#define pgdat3_BoolChannelLock	pgdat3->BoolChannelLock()
#define pgdat3_StringTxtPages	pgdat3->StringTxtPages()
#define pgdat3_IntLogoURL	pgdat3->IntLogoURL()
#define pgdat3_BoolMatchBrandFlag	pgdat3->BoolMatchBrandFlag()
#define pgdat3_Nat32NumBrandIds	pgdat3->Nat32NumBrandIds()
#define pgdat3_StringBrandIds	pgdat3->StringBrandIds()
#define pgdat3_Nat64UniqueNodeId	pgdat3->Nat64UniqueNodeId()
#define pgdat3_BoolUserModifiedLogo	pgdat3->BoolUserModifiedLogo()
#define pgdat3_Nat32TPID	pgdat3->Nat32TPID()
#define pgdat3_IntLnbNumber	IHsvProgramData3_IntLnbNumber
#define pgdat3_IntPolarization	IHsvProgramData3_IntPolarization
#define pgdat3_IntSatelliteId	pgdat3->IntSatelliteId()
#define pgdat3_IntInstalledSatelliteId	pgdat3->IntInstalledSatelliteId()
#define pgdat3_IntPackageGroup	pgdat3->IntPackageGroup()
#define pgdat3_IntDpTsid	pgdat3->IntDpTsid()
#define pgdat3_IntDpServiceId	pgdat3->IntDpServiceId()
#define pgdat3_MultipleLCN	pgdat3->MultipleLCN()
#define pgdat3_MultiplePreset	pgdat3->MultiplePreset()
#define pgdat3_IsValidChannel(channel)	pgdat3->IsValidChannel(channel)
#define pgdat3_IsChannelInstalled(channel)	pgdat3->IsChannelInstalled(channel)
#define pgdat3_IsAttributeSupported(attribute)	pgdat3->IsAttributeSupported(attribute)
#define pgdat3_ClearCurrentTable()	pgdat3->ClearCurrentTable()
#define pgdat3_ClearAllTables()	pgdat3->ClearAllTables()
#define pgdat3_GetChannelDataBool(channel,dataid,value)	pgdat3->GetChannelDataBool(channel,dataid,value)
#define pgdat3_GetChannelDataInt(channel,dataid,value)	pgdat3->GetChannelDataInt(channel,dataid,value)
#define pgdat3_GetChannelDataNat32(channel,dataid,value)	pgdat3->GetChannelDataNat32(channel,dataid,value)
#define pgdat3_GetChannelDataString(channel,dataid,value,size)	pgdat3->GetChannelDataString(channel,dataid,value,size)
#define pgdat3_StoreChannelDataBool(channel,dataid,value)	pgdat3->StoreChannelDataBool(channel,dataid,value)
#define pgdat3_StoreChannelDataInt(channel,dataid,value)	pgdat3->StoreChannelDataInt(channel,dataid,value)
#define pgdat3_StoreChannelDataNat32(channel,dataid,value)	pgdat3->StoreChannelDataNat32(channel,dataid,value)
#define pgdat3_StoreChannelDataString(channel,dataid,value,size)	pgdat3->StoreChannelDataString(channel,dataid,value,size)
#define pgdat3_GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)	pgdat3->GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)
#define pgdat3_SwapChannels(channel1,channel2)	pgdat3->SwapChannels(channel1,channel2)
#define pgdat3_LoadChannelTable(dir)	pgdat3->LoadChannelTable(dir)
#define pgdat3_SaveChannelTable(dir)	pgdat3->SaveChannelTable(dir)
#define pgdat3_ReorderChannels(channel1,channel2,Swap)	pgdat3->ReorderChannels(channel1,channel2,Swap)
#define pgdat3_LoadChannelTableFromMedium(dir,medium)	pgdat3->LoadChannelTableFromMedium(dir,medium)
#define pgdat3_SaveChannelTableToMedium(dir,medium)	pgdat3->SaveChannelTableToMedium(dir,medium)
#define pgdat3_GetMediumFromTable(dir,medium)	pgdat3->GetMediumFromTable(dir,medium)
#define pgdat3_GetNoOfBarkerMultiplexes(NoOfMuxes)	pgdat3->GetNoOfBarkerMultiplexes(NoOfMuxes)
#define pgdat3_GetBarkerMultiplexByIndex(index,muxes)	pgdat3->GetBarkerMultiplexByIndex(index,muxes)
#define pgdat3_ReArrangeChannels(channel1,channel2)	pgdat3->ReArrangeChannels(channel1,channel2)
#define pgdat3_GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)	pgdat3->GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)
#define pgdat3_GetOperator(OperatorId)	pgdat3->GetOperator(OperatorId)
#define pgdat3_StoreChannelDataNat64(channel,dataid,value)	pgdat3->StoreChannelDataNat64(channel,dataid,value)
#define pgdat3_GetChannelDataNat64(channel,dataid,value)	pgdat3->GetChannelDataNat64(channel,dataid,value)
#define pgdat3_GetSatelliteName(LnbNumber,SatelliteName)	pgdat3->GetSatelliteName(LnbNumber,SatelliteName)
#define pgdat3_GetSatellitePackage(PackageId,PackageIGroupId)	pgdat3->GetSatellitePackage(PackageId,PackageIGroupId)
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
#define pgsel_iPresent() (pgsel.Present())
#define pgsel_DefaultSelection	IHsvProgramSelection2_DefaultSelection
#define pgsel_SilentSelection	IHsvProgramSelection2_SilentSelection
#define pgsel_ControlledSelection	IHsvProgramSelection2_ControlledSelection
#define pgsel_ReplacementSelection	IHsvProgramSelection2_ReplacementSelection
#define pgsel_BreakIn	IHsvProgramSelection2_BreakIn
#define pgsel_DecoderBreakIn	IHsvProgramSelection2_DecoderBreakIn
#define pgsel_MultifeedSelection	IHsvProgramSelection2_MultifeedSelection
#define pgsel_NDTSelection	IHsvProgramSelection2_NDTSelection
#define pgsel_PriorityHigh	IHsvProgramSelection2_PriorityHigh
#define pgsel_PriorityMed	IHsvProgramSelection2_PriorityMed
#define pgsel_PriorityLow	IHsvProgramSelection2_PriorityLow
#define pgsel_Frequency	IHsvProgramSelection2_Frequency
#define pgsel_ModulationType	IHsvProgramSelection2_ModulationType
#define pgsel_Polarization	IHsvProgramSelection2_Polarization
#define pgsel_SymbolRate	IHsvProgramSelection2_SymbolRate
#define pgsel_LnbNumber	IHsvProgramSelection2_LnbNumber
#define pgsel_AudioPid	IHsvProgramSelection2_AudioPid
#define pgsel_VideoPid	IHsvProgramSelection2_VideoPid
#define pgsel_PcrPid	IHsvProgramSelection2_PcrPid
#define pgsel_ProgramNumber	IHsvProgramSelection2_ProgramNumber
#define pgsel_ModulationStd	IHsvProgramSelection2_ModulationStd
#define pgsel_CodeRate	IHsvProgramSelection2_CodeRate
#define pgsel_InvalidAttribute	IHsvProgramSelection2_InvalidAttribute
#define pgsel_SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority)	pgsel->SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority)
#define pgsel_GetCurrentProgram(Dest,Source,ChannelNo)	pgsel->GetCurrentProgram(Dest,Source,ChannelNo)
#define pgsel_GetActualCurrentProgram(Dest,Source,ChannelNo)	pgsel->GetActualCurrentProgram(Dest,Source,ChannelNo)
#define pgsel_IsSelectionAllowed(Source,ChannelNo,Dest)	pgsel->IsSelectionAllowed(Source,ChannelNo,Dest)
#define pgsel_IsSelectionInProgress()	pgsel->IsSelectionInProgress()
#define pgsel_GetLastRequestedProgram(Dest,Source,ChannelNo)	pgsel->GetLastRequestedProgram(Dest,Source,ChannelNo)
#define pgsel_GetLastActualRequestedProgram(Dest,Source,ChannelNo)	pgsel->GetLastActualRequestedProgram(Dest,Source,ChannelNo)
#define pgsel_SetAttribute(attribute,value)	pgsel->SetAttribute(attribute,value)
#define pgsel_GetAttribute(attribute,value)	pgsel->GetAttribute(attribute,value)
#define pgsel_IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection)	pgsel->IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection)
#define pgsel_GetActualTypeOfSelection(Dest)	pgsel->GetActualTypeOfSelection(Dest)
#define pgsel_IsProgramSelectionRequired(channelno)	pgsel->IsProgramSelectionRequired(channelno)
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsGeneric_mSrt_Priv::func,replace,(char *)name,this)
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
#define strmfltr_iPresent() (strmfltr.Present())
#define strmfltr_IsSet(dest,filterid,value)	strmfltr->IsSet(dest,filterid,value)
#define strmfltr_IsReady(dest,filterid)	strmfltr->IsReady(dest,filterid)
#define strmfltr_Set(dest,filterid,value)	strmfltr->Set(dest,filterid,value)
#define strmfltr_Clear(dest,filterid,value)	strmfltr->Clear(dest,filterid,value)
#define wnddest_iPresent() (wnddest.Present())
#define wnddest_InvalidWindowId	wnddest->InvalidWindowId()
#define wnddest_GetWindowId(dest)	wnddest->GetWindowId(dest)
#define wnddest_GetAudioNodeId(dest)	wnddest->GetAudioNodeId(dest)
#define wnddest_GetMonitorWindow()	wnddest->GetMonitorWindow()
#define wnddest_WndTypeInvalid	IHsvWindowDestinationMap_WndTypeInvalid
#define wnddest_WndTypeMainVideo	IHsvWindowDestinationMap_WndTypeMainVideo
#define wnddest_WndTypeMainAudio	IHsvWindowDestinationMap_WndTypeMainAudio
#define wnddest_WndTypeMonitor	IHsvWindowDestinationMap_WndTypeMonitor
#define wnddest_WndTypeAuxVideo	IHsvWindowDestinationMap_WndTypeAuxVideo
#define wnddest_GetWindowType(winid)	wnddest->GetWindowType(winid)
#define wnddest_GetDestinationForWindow(windowid)	wnddest->GetDestinationForWindow(windowid)
#define isrt_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define isrt_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define isrt_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define isrt_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define isrt_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define isrt_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define isrtctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define isrtctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define isrtctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define isrtctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define isrtctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define isrtctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define isrtctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define isrtctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define isrtctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define isrtctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define isrtctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define isrtctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define isrtctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define isrtctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define isrtctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define isrtctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define isrtctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define isrtctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define isrtctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define isrtctrlN_FST	IHsvSdmControlNotifyEx_FST
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
#include "locals_mSrt.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

