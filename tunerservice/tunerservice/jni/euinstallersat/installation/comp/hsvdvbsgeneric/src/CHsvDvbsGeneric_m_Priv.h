#ifndef  _CHSVDVBSGENERIC_M_PRIV_H
#define  _CHSVDVBSGENERIC_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvStreamNotify.h>
#include <CS2MwBase.h>
class CHsvDvbsGeneric_m_Priv;
#define CLASSSCOPE CHsvDvbsGeneric_m_Priv::
#include "locals_m.h"

class CHsvDvbsGeneric_m_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsGeneric_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSatelliteBackgroundInstallationImpl(CHsvDvbsGeneric_m_Priv,bckInstall);
IHsvSdmControlNotifyExImpl(CHsvDvbsGeneric_m_Priv,ctrlN);
IHsvDigitalAcquisitionNotifyImpl(CHsvDvbsGeneric_m_Priv,iacqN);
IHsvSatellitePackageInstallationImpl(CHsvDvbsGeneric_m_Priv,ins);
IHsvSatelliteFrontEndNotifyImpl(CHsvDvbsGeneric_m_Priv,plfApidvbsN);
IHsvPowerImpl(CHsvDvbsGeneric_m_Priv,pow);
IHsvStreamNotifyImpl(CHsvDvbsGeneric_m_Priv, strapiN);
public:
ProvidesInterface<IHsvSatelliteBackgroundInstallation>	bckInstall;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	iacqN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;
RequiresInterface<IHsvPower>	ibckgndpow;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvDigitalAcquisitionNotify>	iscanAcqN;
RequiresInterface<IHsvPower>	isortpow;
RequiresInterface<IHsvSatellitePackageInstallation>	isrt;
RequiresInterface<IHsvDigitalAcquisitionNotify>	isrtAcqN;
RequiresInterface<IHsvSdmControlNotifyEx>	isrtctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	isrtplfApidvbsN;
RequiresInterface<IHsvPower>	isrtpow;
RequiresInterface<IHsvSatellitePackageInstallation>	isvcscan;
RequiresInterface<IHsvSdmControlNotifyEx>	isvcscanctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	isvcscanplfApidvbsN;
RequiresInterface<IHsvPower>	isvcscanpow;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvStreamNotify>	isrtstrapiN;
RequiresInterface<IHsvStreamNotify>	ibckgndstrapiN;

public:
CHsvDvbsGeneric_m_Priv():i__bckInstall(this),i__ctrlN(this),i__iacqN(this),i__ins(this),i__plfApidvbsN(this),i__pow(this), i__strapiN(this)
{
bckInstall	=	&i__bckInstall;
ctrlN	=	&i__ctrlN;
iacqN	=	&i__iacqN;
ins	=	&i__ins;
plfApidvbsN	=	&i__plfApidvbsN;
pow	=	&i__pow;
strapiN = &i__strapiN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#define ibckAcqN_iPresent() (ibckAcqN.Present())
#define ibckAcqN_OnDataAquired(Status)	ibckAcqN->OnDataAquired(Status)
#define ibckInstall_iPresent() (ibckInstall.Present())
#define ibckInstall_EnableBackgroundInstallation()	ibckInstall->EnableBackgroundInstallation()
#define ibckInstall_DisableBackgroundInstallation()	ibckInstall->DisableBackgroundInstallation()
#define ibckgndpow_iPresent() (ibckgndpow.Present())
#define ibckgndpow_Init()	ibckgndpow->Init()
#define ibckgndpow_TurnOn()	ibckgndpow->TurnOn()
#define ibckgndpow_TurnOff()	ibckgndpow->TurnOff()
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
#define iscanAcqN_iPresent() (iscanAcqN.Present())
#define iscanAcqN_OnDataAquired(Status)	iscanAcqN->OnDataAquired(Status)
#define isortpow_iPresent() (isortpow.Present())
#define isortpow_Init()	isortpow->Init()
#define isortpow_TurnOn()	isortpow->TurnOn()
#define isortpow_TurnOff()	isortpow->TurnOff()
#define isrt_iPresent() (isrt.Present())
#define isrt_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define isrt_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define isrt_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define isrt_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define isrt_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define isrt_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define isrt_GetCurrentInstallationState(mode,state)	isrt->GetCurrentInstallationState(mode,state)
#define isrt_StartInstallation(Source,Lnb,Mode)	isrt->StartInstallation(Source,Lnb,Mode)
#define isrt_StopInstallation()	isrt->StopInstallation()
#define isrt_WriteBarkerMuxData()	isrt->WriteBarkerMuxData()
#define isrt_GetNumberOfTvChannelsFound(Mode,Lnb)	isrt->GetNumberOfTvChannelsFound(Mode,Lnb)
#define isrt_GetNumberofRadioChannelsFound(Mode,Lnb)	isrt->GetNumberofRadioChannelsFound(Mode,Lnb)
#define isrt_GetNumberOfTvChannelsRemoved(Mode,Lnb)	isrt->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define isrt_GetNumberofRadioChannelsRemoved(Mode,Lnb)	isrt->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define isrt_GetNumberOfDigitalChannelsAdded()	isrt->GetNumberOfDigitalChannelsAdded()
#define isrt_GetNumberOfDigitalChannelsRemoved()	isrt->GetNumberOfDigitalChannelsRemoved()
#define isrt_GetNumberOfDigitalChannelsMoved()	isrt->GetNumberOfDigitalChannelsMoved()
#define isrt_LoadManualInstallationDefaultValues()	isrt->LoadManualInstallationDefaultValues()
#define isrt_StoreManualInstallationValues()	isrt->StoreManualInstallationValues()
#define isrt_SetManualInstallationAttributes(AttributeId,Value)	isrt->SetManualInstallationAttributes(AttributeId,Value)
#define isrt_GetAttribute(Mode,AttributeId)	isrt->GetAttribute(Mode,AttributeId)
#define isrt_GetScanProgressStatus(Mode)	isrt->GetScanProgressStatus(Mode)
#define isrt_GetSIDetails(SiValues)	isrt->GetSIDetails(SiValues)
#define isrtAcqN_iPresent() (isrtAcqN.Present())
#define isrtAcqN_OnDataAquired(Status)	isrtAcqN->OnDataAquired(Status)
#define isrtctrlN_iPresent() (isrtctrlN.Present())
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
#define isrtctrlN_OnEvent(dmx,eventid,value)	isrtctrlN->OnEvent(dmx,eventid,value)
#define isrtplfApidvbsN_iPresent() (isrtplfApidvbsN.Present())
#define isrtplfApidvbsN_OnLockChanged(LockState)	isrtplfApidvbsN->OnLockChanged(LockState)
#define isrtplfApidvbsN_OnBlindScanEnd()	isrtplfApidvbsN->OnBlindScanEnd()
#define isrtpow_iPresent() (isrtpow.Present())
#define isrtpow_Init()	isrtpow->Init()
#define isrtpow_TurnOn()	isrtpow->TurnOn()
#define isrtpow_TurnOff()	isrtpow->TurnOff()
#define isvcscan_iPresent() (isvcscan.Present())
#define isvcscan_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define isvcscan_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define isvcscan_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define isvcscan_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define isvcscan_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define isvcscan_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define isvcscan_GetCurrentInstallationState(mode,state)	isvcscan->GetCurrentInstallationState(mode,state)
#define isvcscan_StartInstallation(Source,Lnb,Mode)	isvcscan->StartInstallation(Source,Lnb,Mode)
#define isvcscan_StopInstallation()	isvcscan->StopInstallation()
#define isvcscan_WriteBarkerMuxData()	isvcscan->WriteBarkerMuxData()
#define isvcscan_GetNumberOfTvChannelsFound(Mode,Lnb)	isvcscan->GetNumberOfTvChannelsFound(Mode,Lnb)
#define isvcscan_GetNumberofRadioChannelsFound(Mode,Lnb)	isvcscan->GetNumberofRadioChannelsFound(Mode,Lnb)
#define isvcscan_GetNumberOfTvChannelsRemoved(Mode,Lnb)	isvcscan->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define isvcscan_GetNumberofRadioChannelsRemoved(Mode,Lnb)	isvcscan->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define isvcscan_GetNumberOfDigitalChannelsAdded()	isvcscan->GetNumberOfDigitalChannelsAdded()
#define isvcscan_GetNumberOfDigitalChannelsRemoved()	isvcscan->GetNumberOfDigitalChannelsRemoved()
#define isvcscan_GetNumberOfDigitalChannelsMoved()	isvcscan->GetNumberOfDigitalChannelsMoved()
#define isvcscan_LoadManualInstallationDefaultValues()	isvcscan->LoadManualInstallationDefaultValues()
#define isvcscan_StoreManualInstallationValues()	isvcscan->StoreManualInstallationValues()
#define isvcscan_SetManualInstallationAttributes(AttributeId,Value)	isvcscan->SetManualInstallationAttributes(AttributeId,Value)
#define isvcscan_GetAttribute(Mode,AttributeId)	isvcscan->GetAttribute(Mode,AttributeId)
#define isvcscan_GetScanProgressStatus(Mode)	isvcscan->GetScanProgressStatus(Mode)
#define isvcscan_GetSIDetails(SiValues)	isvcscan->GetSIDetails(SiValues)
#define isvcscanctrlN_iPresent() (isvcscanctrlN.Present())
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
#define isvcscanctrlN_OnEvent(dmx,eventid,value)	isvcscanctrlN->OnEvent(dmx,eventid,value)
#define isvcscanplfApidvbsN_iPresent() (isvcscanplfApidvbsN.Present())
#define isvcscanplfApidvbsN_OnLockChanged(LockState)	isvcscanplfApidvbsN->OnLockChanged(LockState)
#define isvcscanplfApidvbsN_OnBlindScanEnd()	isvcscanplfApidvbsN->OnBlindScanEnd()
#define isvcscanpow_iPresent() (isvcscanpow.Present())
#define isvcscanpow_Init()	isvcscanpow->Init()
#define isvcscanpow_TurnOn()	isvcscanpow->TurnOn()
#define isvcscanpow_TurnOff()	isvcscanpow->TurnOff()
#define ctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define ctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define ctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define ctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define ctrlN_FST	IHsvSdmControlNotifyEx_FST
#define ins_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define ins_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define ins_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define ins_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define ins_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define ins_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define insN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define insN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define insN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
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
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

