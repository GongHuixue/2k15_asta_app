#ifndef  _CHSVDVBSINSTALLATION_MMINIPRESCAN_PRIV_H
#define  _CHSVDVBSINSTALLATION_MMINIPRESCAN_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvMiniPrescan.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvMiniPrescanNotify.h>
#include <IHsvPackageParser.h>
#include <IHsvPrescanParser.h>
#include <IHsvInstallationSigStrength.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvSatelliteInstallation.h>
#include <IPumpExSub.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_mminiprescan_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_mminiprescan_Priv::
#include "locals_mminiprescan.h"

class CHsvDvbsInstallation_mminiprescan_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_mminiprescan_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mminiprescan.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvMiniPrescanImpl(CHsvDvbsInstallation_mminiprescan_Priv,iminiprescan);
IHsvSdmControlNotifyExImpl(CHsvDvbsInstallation_mminiprescan_Priv,iminiprescanctrlN);
IHsvPowerImpl(CHsvDvbsInstallation_mminiprescan_Priv,iminiprescanpow);
IHsvSatelliteFrontEndNotifyImpl(CHsvDvbsInstallation_mminiprescan_Priv,iminiprescansatfrontendN);
public:
ProvidesInterface<IHsvMiniPrescan>	iminiprescan;

ProvidesInterface<IHsvSdmControlNotifyEx>	iminiprescanctrlN;

ProvidesInterface<IHsvPower>	iminiprescanpow;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	iminiprescansatfrontendN;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvMiniPrescanNotify>	iminiprescanN;
RequiresInterface<IHsvPackageParser>	ipackage;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvDvbsInstallation_mminiprescan_Priv);

public:
CHsvDvbsInstallation_mminiprescan_Priv():i__iminiprescan(this),i__iminiprescanctrlN(this),i__iminiprescanpow(this),i__iminiprescansatfrontendN(this)
{
iminiprescan	=	&i__iminiprescan;
iminiprescanctrlN	=	&i__iminiprescanctrlN;
iminiprescanpow	=	&i__iminiprescanpow;
iminiprescansatfrontendN	=	&i__iminiprescansatfrontendN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)
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
#define eurdiv_iPresent() (eurdiv.Present())
#define eurdiv_iVersion	eurdiv->iVersion()
#define eurdiv_NITTimeoutTime	eurdiv->NITTimeoutTime()
#define eurdiv_AttenuatorDetectionInInstall	eurdiv->AttenuatorDetectionInInstall()
#define eurdiv_SupportNameExtractionInManIns	eurdiv->SupportNameExtractionInManIns()
#define eurdiv_WeakSignalStrengthThreshold	eurdiv->WeakSignalStrengthThreshold()
#define eurdiv_SignalStrengthSorting	eurdiv->SignalStrengthSorting()
#define eurdiv_SearchForColorSystemInInstallation	eurdiv->SearchForColorSystemInInstallation()
#define eurdiv_SearchForTvSystemInInstallation	eurdiv->SearchForTvSystemInInstallation()
#define eurdiv_ManualSearchWithWrapAround	eurdiv->ManualSearchWithWrapAround()
#define eurdiv_SortPresetsInAutoStoreModeNone	eurdiv->SortPresetsInAutoStoreModeNone()
#define eurdiv_SignalStrengthTimeoutTime	eurdiv->SignalStrengthTimeoutTime()
#define eurdiv_DefaultTunerPresetFrequency	eurdiv->DefaultTunerPresetFrequency()
#define eurdiv_PgctrlMuteColor	eurdiv->PgctrlMuteColor()
#define eurdiv_ChannelNameLength	eurdiv->ChannelNameLength()
#define eurdiv_PresetNameLength	eurdiv->PresetNameLength()
#define eurdiv_MuteRequiredOnInstallation	eurdiv->MuteRequiredOnInstallation()
#define eurdiv_ClearDataOnAutoInstallation	eurdiv->ClearDataOnAutoInstallation()
#define eurdiv_AnalogOnly	eurdiv->AnalogOnly()
#define eurdiv_InstallTestStreams(installationmode,medium)	eurdiv->InstallTestStreams(installationmode,medium)
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_NoOfVirtualChannelsSupported(medium)	eurdiv->NoOfVirtualChannelsSupported(medium)
#define eurdiv_ForceLCNSyntax(medium)	eurdiv->ForceLCNSyntax(medium)
#define eurdiv_DefaultStreamPriority(medium)	eurdiv->DefaultStreamPriority(medium)
#define eurdiv_IsServiceInstallable(medium,ServiceType)	eurdiv->IsServiceInstallable(medium,ServiceType)
#define eurdiv_IsServiceHidden(medium,ServiceType)	eurdiv->IsServiceHidden(medium,ServiceType)
#define eurdiv_AcceptedStreamType(medium,StreamType)	eurdiv->AcceptedStreamType(medium,StreamType)
#define eurdiv_UpdateChannelName(medium)	eurdiv->UpdateChannelName(medium)
#define eurdiv_IsDbookCountry()	eurdiv->IsDbookCountry()
#define eurdiv_SkipInstallationPass	eurdiv->SkipInstallationPass()
#define eurdiv_FirstInstallationPass	eurdiv->FirstInstallationPass()
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_TxtInfoTimeout	eurdiv->TxtInfoTimeout()
#define eurdiv_VideoMuteColor	eurdiv->VideoMuteColor()
#define eurdiv_VideoMuteColorForLocks	eurdiv->VideoMuteColorForLocks()
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	eurdiv->DecoderSupported()
#define eurdiv_BreakInSupported	eurdiv->BreakInSupported()
#define eurdiv_ScartRuleSupported	eurdiv->ScartRuleSupported()
#define eurdiv_HsvAntennaDigSrvcTable	eurdiv->HsvAntennaDigSrvcTable()
#define eurdiv_HsvAntennaDigPtcTable	eurdiv->HsvAntennaDigPtcTable()
#define eurdiv_HsvAntennaFreqMapTable	eurdiv->HsvAntennaFreqMapTable()
#define eurdiv_PersistentMemUpdateTimeout	eurdiv->PersistentMemUpdateTimeout()
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	eurdiv->MaxNoOfChannelsToStoreAntennaUserTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigPtcTable()
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreAntennaFreqMapTable()
#define eurdiv_IsHDSubtitleSupported()	eurdiv->IsHDSubtitleSupported()
#define eurdiv_AvSignalDetectionTimeOut	eurdiv->AvSignalDetectionTimeOut()
#define eurdiv_HearingImpairedOn	eurdiv->HearingImpairedOn()
#define eurdiv_VisuallyImpairedOn	eurdiv->VisuallyImpairedOn()
#define eurdiv_IsQaaSupported	eurdiv->IsQaaSupported()
#define eurdiv_IsPremixedVISupported	eurdiv->IsPremixedVISupported()
#define eurdiv_EPGSecondaryDirName	eurdiv->EPGSecondaryDirName()
#define eurdiv_DefaultCharacterTable	eurdiv->DefaultCharacterTable()
#define eurdiv_ShortInfoCacheForCountry	eurdiv->ShortInfoCacheForCountry()
#define eurdiv_OUI	eurdiv->OUI()
#define eurdiv_HardwareModel	eurdiv->HardwareModel()
#define eurdiv_HardwareVersion	eurdiv->HardwareVersion()
#define eurdiv_GetNoOfBackBuffers(clientId)	eurdiv->GetNoOfBackBuffers(clientId)
#define eurdiv_SubtitleTimeOut	eurdiv->SubtitleTimeOut()
#define eurdiv_IsMpeg4STBoltOnSupported()	eurdiv->IsMpeg4STBoltOnSupported()
#define eurdiv_ForceCharacterTable	eurdiv->ForceCharacterTable()
#define eurdiv_RegionalCharacterTable	eurdiv->RegionalCharacterTable()
#define eurdiv_CurrentCountryInvalidLCNSortKey1	eurdiv->CurrentCountryInvalidLCNSortKey1()
#define eurdiv_CurrentCountryInvalidLCNSortKey2	eurdiv->CurrentCountryInvalidLCNSortKey2()
#define eurdiv_CurrentCountryInvalidLCNSortKey3	eurdiv->CurrentCountryInvalidLCNSortKey3()
#define eurdiv_CurrentCountryInvalidLCNSortKey4	eurdiv->CurrentCountryInvalidLCNSortKey4()
#define eurdiv_CurrentCountryInvalidLCNSortKey5	eurdiv->CurrentCountryInvalidLCNSortKey5()
#define eurdiv_OtherCountrySortKey1	eurdiv->OtherCountrySortKey1()
#define eurdiv_OtherCountrySortKey2	eurdiv->OtherCountrySortKey2()
#define eurdiv_OtherCountrySortKey3	eurdiv->OtherCountrySortKey3()
#define eurdiv_OtherCountrySortKey4	eurdiv->OtherCountrySortKey4()
#define eurdiv_OtherCountrySortKey5	eurdiv->OtherCountrySortKey5()
#define eurdiv_KeyInvalid	IHsvEuropeDiversity2_KeyInvalid
#define eurdiv_KeyOriginalNetworkId	IHsvEuropeDiversity2_KeyOriginalNetworkId
#define eurdiv_KeyServiceType	IHsvEuropeDiversity2_KeyServiceType
#define eurdiv_KeyLCN	IHsvEuropeDiversity2_KeyLCN
#define eurdiv_KeyServiceName	IHsvEuropeDiversity2_KeyServiceName
#define eurdiv_KeyServiceId	IHsvEuropeDiversity2_KeyServiceId
#define eurdiv_TripletKey(medium)	eurdiv->TripletKey(medium)
#define eurdiv_InstallDuplicateServices(medium)	eurdiv->InstallDuplicateServices(medium)
#define eurdiv_MeasureSignalStrengthWhilePlaying	eurdiv->MeasureSignalStrengthWhilePlaying()
#define eurdiv_Automatic	IHsvEuropeDiversity2_Automatic
#define eurdiv_PalOnly	IHsvEuropeDiversity2_PalOnly
#define eurdiv_PalSecam	IHsvEuropeDiversity2_PalSecam
#define eurdiv_SecamPal	IHsvEuropeDiversity2_SecamPal
#define eurdiv_SecamOnly	IHsvEuropeDiversity2_SecamOnly
#define eurdiv_ChannelListVariant	eurdiv->ChannelListVariant()
#define eurdiv_DefaultChannelList	IHsvEuropeDiversity2_DefaultChannelList
#define eurdiv_DualChannelList	IHsvEuropeDiversity2_DualChannelList
#define eurdiv_TripleChannelList	IHsvEuropeDiversity2_TripleChannelList
#define eurdiv_EnableCountryFallbackForLCNSyntax(medium)	eurdiv->EnableCountryFallbackForLCNSyntax(medium)
#define eurdiv_EnableONIDFallbackForLCNSyntax(medium)	eurdiv->EnableONIDFallbackForLCNSyntax(medium)
#define eurdiv_HsvCableDigSrvcTable	eurdiv->HsvCableDigSrvcTable()
#define eurdiv_HsvCableDigPtcTable	eurdiv->HsvCableDigPtcTable()
#define eurdiv_HsvCableSvcListDescTable	eurdiv->HsvCableSvcListDescTable()
#define eurdiv_HsvCableFreqMapTable	eurdiv->HsvCableFreqMapTable()
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	eurdiv->MaxNoOfChannelsToStoreCableUserTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreCableDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	eurdiv->MaxNoOfChannelsToStoreCableDigPtcTable()
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreCableFreqMapTable()
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_GetDefaultScanMode(medium)	eurdiv->GetDefaultScanMode(medium)
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_GetNextScan(medium,installationmode,ScanPreference)	eurdiv->GetNextScan(medium,installationmode,ScanPreference)
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_GetAudioPreference()	eurdiv->GetAudioPreference()
#define eurdiv_GetSubtitlePreference()	eurdiv->GetSubtitlePreference()
#define eurdiv_UserPreferredAudioFormat()	eurdiv->UserPreferredAudioFormat()
#define eurdiv_HsvDVBCSettingsFilePath	eurdiv->HsvDVBCSettingsFilePath()
#define eurdiv_HsvCableDelSysDescFilePath	eurdiv->HsvCableDelSysDescFilePath()
#define eurdiv_HsvServiceListDescFilePath	eurdiv->HsvServiceListDescFilePath()
#define eurdiv_MaxLCNValue	eurdiv->MaxLCNValue()
#define eurdiv_IsBackgroundInstallRequired(medium)	eurdiv->IsBackgroundInstallRequired(medium)
#define eurdiv_SupportLCNVersion2(medium)	eurdiv->SupportLCNVersion2(medium)
#define eurdiv_ParseLCN(medium,installationmode)	eurdiv->ParseLCN(medium,installationmode)
#define eurdiv_IsPreScanSupported(medium)	eurdiv->IsPreScanSupported(medium)
#define eurdiv_SupportHDSLCN(medium)	eurdiv->SupportHDSLCN(medium)
#define eurdiv_IsServiceAttrbDescSupported(medium)	eurdiv->IsServiceAttrbDescSupported(medium)
#define eurdiv_IsTSRelocatedDescSupported(medium)	eurdiv->IsTSRelocatedDescSupported(medium)
#define eurdiv_SDTActual	IHsvEuropeDiversity2_SDTActual
#define eurdiv_SDTOther	IHsvEuropeDiversity2_SDTOther
#define eurdiv_SDTNone	IHsvEuropeDiversity2_SDTNone
#define eurdiv_GetAltSDTType(medium)	eurdiv->GetAltSDTType(medium)
#define eurdiv_AltHomingFrequency	IHsvEuropeDiversity2_AltHomingFrequency
#define eurdiv_AltTSRelocatedDesc	IHsvEuropeDiversity2_AltTSRelocatedDesc
#define eurdiv_AltNone	IHsvEuropeDiversity2_AltNone
#define eurdiv_GetAlternateTSLocation(medium)	eurdiv->GetAlternateTSLocation(medium)
#define eurdiv_IsAc3AudioSupported()	eurdiv->IsAc3AudioSupported()
#define eurdiv_StaticTable()	eurdiv->StaticTable()
#define eurdiv_GetDefaultDigitalInstallStatus(country)	eurdiv->GetDefaultDigitalInstallStatus(country)
#define eurdiv_IsMultifeedSupported()	eurdiv->IsMultifeedSupported()
#define eurdiv_GetViterbiBER()	eurdiv->GetViterbiBER()
#define eurdiv_DeltaViterbiBER()	eurdiv->DeltaViterbiBER()
#define eurdiv_GetShortInfoCacheSize()	eurdiv->GetShortInfoCacheSize()
#define eurdiv_GetDeltaSQI()	eurdiv->GetDeltaSQI()
#define eurdiv_GetDeltaSSI()	eurdiv->GetDeltaSSI()
#define eurdiv_AutomaticDigitalPresetAllocation	eurdiv->AutomaticDigitalPresetAllocation()
#define eurdiv_NonRadioStartPreset(country,medium,numRecords)	eurdiv->NonRadioStartPreset(country,medium,numRecords)
#define eurdiv_NonRadioEndPreset(country,medium)	eurdiv->NonRadioEndPreset(country,medium)
#define eurdiv_RadioStartPreset(country,medium,numRecords)	eurdiv->RadioStartPreset(country,medium,numRecords)
#define eurdiv_RadioEndPreset(country,medium)	eurdiv->RadioEndPreset(country,medium)
#define eurdiv_IsHDSimulcastSupported()	eurdiv->IsHDSimulcastSupported()
#define eurdiv_FirstLCNOnlySupported()	eurdiv->FirstLCNOnlySupported()
#define eurdiv_IsDigiturkPackage()	eurdiv->IsDigiturkPackage()
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
#define iminiprescanN_iPresent() (iminiprescanN.Present())
#define iminiprescanN_EventPrescanFailed	IHsvMiniPrescanNotify_EventPrescanFailed
#define iminiprescanN_EventSameSatelliteDetected	IHsvMiniPrescanNotify_EventSameSatelliteDetected
#define iminiprescanN_EventDifferentSatelliteDetected	IHsvMiniPrescanNotify_EventDifferentSatelliteDetected
#define iminiprescanN_EventPreScanStopped			IHsvMiniPrescanNotify_EventPreScanStopped
#define iminiprescanN_OnEvent(EventId,Param)	iminiprescanN->OnEvent(EventId,Param)
#define ipackage_iPresent() (ipackage.Present())
#define ipackage_IdentifyPackagesAvailable()	ipackage->IdentifyPackagesAvailable()
#define ipackage_GetNumberOfPackages()	ipackage->GetNumberOfPackages()
#define ipackage_GetPackageByIndex(Index,Package)	ipackage->GetPackageByIndex(Index,Package)
#define ipackage_GetPackageByKey(Package)	ipackage->GetPackageByKey(Package)
#define ipackage_GetPackageGroupId(PackageID,PackageGroupId)	ipackage->GetPackageGroupId(PackageID,PackageGroupId)
#define ipackage_GetPackageGroupName(PackageGroupId,PackageGroupName)	ipackage->GetPackageGroupName(PackageGroupId,PackageGroupName)
#define ipackage_LoadPackageGroupInfo()	ipackage->LoadPackageGroupInfo()
#define ipackage_StartPackageParsing()	ipackage->StartPackageParsing()
#define ipackage_StopPackageParsing()	ipackage->StopPackageParsing()
#define ipackage_SetPackageParserXmlString(InputString,PackageParserXmlStringLen)	ipackage->SetPackageParserXmlString(InputString,PackageParserXmlStringLen)
#define iprescanparser_iPresent() (iprescanparser.Present())
#define iprescanparser_ExtractPreScanTableFromXml()	iprescanparser->ExtractPreScanTableFromXml()
#define iprescanparser_GetNumberOfPrescanEntries()	iprescanparser->GetNumberOfPrescanEntries()
#define iprescanparser_GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)	iprescanparser->GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)
#define iprescanparser_GetSatelliteAttributeById(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeById(SatelliteAttribute)
#define iprescanparser_GetSatelliteAttributeByPosition(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeByPosition(SatelliteAttribute)
#define iprescanparser_SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)	iprescanparser->SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)
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
#define pins_iPresent() (pins.Present())
#define pins_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define pins_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define pins_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define pins_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define pins_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define pins_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define pins_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define pins_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define pins_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define pins_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define pins_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define pins_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define pins_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define pins_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define pins_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define pins_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define pins_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define pins_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define pins_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define pins_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define pins_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define pins_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define pins_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define pins_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define pins_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define pins_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define pins_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define pins_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define pins_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define pins_GetCurrentInstallationState(mode,state)	pins->GetCurrentInstallationState(mode,state)
#define pins_StartInstallation(Source,Lnb,Mode)	pins->StartInstallation(Source,Lnb,Mode)
#define pins_StopInstallation()	pins->StopInstallation()
#define pins_ResetInstallation()	pins->ResetInstallation()
#define pins_GetNumberOfTvChannelsFound(Lnb)	pins->GetNumberOfTvChannelsFound(Lnb)
#define pins_GetNumberofRadioChannelsFound(Lnb)	pins->GetNumberofRadioChannelsFound(Lnb)
#define pins_GetNumberOfTvChannelsRemoved(Lnb)	pins->GetNumberOfTvChannelsRemoved(Lnb)
#define pins_GetNumberofRadioChannelsRemoved(Lnb)	pins->GetNumberofRadioChannelsRemoved(Lnb)
#define pins_GetSatelliteName(Lnb,SatelliteName)	pins->GetSatelliteName(Lnb,SatelliteName)
#define pins_GetNumberOfDigitalChannelsAdded()	pins->GetNumberOfDigitalChannelsAdded()
#define pins_GetNumberOfDigitalChannelsRemoved()	pins->GetNumberOfDigitalChannelsRemoved()
#define pins_GetNumberOfDigitalChannelsMoved()	pins->GetNumberOfDigitalChannelsMoved()
#define pins_IdentifyPackagesAvailable()	pins->IdentifyPackagesAvailable()
#define pins_GetTotalNumberOfPackagesFound()	pins->GetTotalNumberOfPackagesFound()
#define pins_GetPackageByIndex(Index,Package)	pins->GetPackageByIndex(Index,Package)
#define pins_SetUserPackageIndex(PackageIndex)	pins->SetUserPackageIndex(PackageIndex)
#define pins_GetUserPackageIndex(PackageIndex,IsPackage)	pins->GetUserPackageIndex(PackageIndex,IsPackage)
#define pins_GetInstalledSatellites(mode,SatelliteEntries)	pins->GetInstalledSatellites(mode,SatelliteEntries)
#define pins_InstallAddedSatellites()	pins->InstallAddedSatellites()
#define pins_ResetAddedSatellites()	pins->ResetAddedSatellites()
#define pins_RemoveSatelliteEntry(LnbNumber)	pins->RemoveSatelliteEntry(LnbNumber)
#define pins_GetSatelliteSignalStrength(LnbNumber)	pins->GetSatelliteSignalStrength(LnbNumber)
#define pins_GetSatelliteSignalQuality(LnbNumber)	pins->GetSatelliteSignalQuality(LnbNumber)
#define pins_LoadManualInstallationDefaultValues()	pins->LoadManualInstallationDefaultValues()
#define pins_StoreManualInstallationValues()	pins->StoreManualInstallationValues()
#define pins_GetAttribute(Mode,AttributeId)	pins->GetAttribute(Mode,AttributeId)
#define pins_SetAttribute(Mode,AttributeId,Value)	pins->SetAttribute(Mode,AttributeId,Value)
#define pins_GetScanProgressStatus(Mode)	pins->GetScanProgressStatus(Mode)
#define pins_GetSITableIds(NetworkID,BouquetID)	pins->GetSITableIds(NetworkID,BouquetID)
#define pins_GetPackageName(PackageId,PackageName)	pins->GetPackageName(PackageId,PackageName)
#define pins_GetSIDetails(SiValues)	pins->GetSIDetails(SiValues)
#define pins_EnableUnicable(LnbNumber,Enable)	pins->EnableUnicable(LnbNumber,Enable)
#define pins_StopSignalStrengthMeas(LnbNumber)	pins->StopSignalStrengthMeas(LnbNumber)
#define pins_GetSignalQuality(Param)	pins->GetSignalQuality(Param)
#define pins_StartSignalStrengthMeas(LnbNumber)	pins->StartSignalStrengthMeas(LnbNumber)
#define pins_GetSignalStrength(param)	pins->GetSignalStrength(param)
#define pins_StartPredefinedListCopy()	pins->StartPredefinedListCopy()
#define pins_GetFirstInstalledChannel()	pins->GetFirstInstalledChannel()
#define pins_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	pins->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsInstallation_mminiprescan_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define qssm_iPresent() (qssm.Present())
#define qssm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	qssm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define qssm_Start(winid,Avail,retval)	qssm->Start(winid,Avail,retval)
#define qssm_Stop(winid,Stopped,retval)	qssm->Stop(winid,Stopped,retval)
#define qssm_GetMeasValid(winid,Valid,retval)	qssm->GetMeasValid(winid,Valid,retval)
#define qssm_GetSigStrength(winid,Strength,retval)	qssm->GetSigStrength(winid,Strength,retval)
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
#define vssm_iPresent() (vssm.Present())
#define vssm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	vssm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define vssm_Start(winid,Avail,retval)	vssm->Start(winid,Avail,retval)
#define vssm_Stop(winid,Stopped,retval)	vssm->Stop(winid,Stopped,retval)
#define vssm_GetMeasValid(winid,Valid,retval)	vssm->GetMeasValid(winid,Valid,retval)
#define vssm_GetSigStrength(winid,Strength,retval)	vssm->GetSigStrength(winid,Strength,retval)
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
#define iminiprescanctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iminiprescanctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iminiprescanctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iminiprescanctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iminiprescanctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iminiprescanctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iminiprescanctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iminiprescanctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iminiprescanctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iminiprescanctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iminiprescanctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iminiprescanctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iminiprescanctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iminiprescanctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iminiprescanctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iminiprescanctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define iminiprescanctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define iminiprescanctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define iminiprescanctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define iminiprescanctrlN_FST	IHsvSdmControlNotifyEx_FST
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
#include "locals_mminiprescan.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

