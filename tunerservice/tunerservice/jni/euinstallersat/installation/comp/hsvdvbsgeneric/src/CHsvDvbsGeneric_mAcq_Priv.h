#ifndef  _CHSVDVBSGENERIC_MACQ_PRIV_H
#define  _CHSVDVBSGENERIC_MACQ_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvDigitalAcquisition.h>
#include <IProdApiClockEx.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvPrescanParser.h>
#include <IHsvDigitalScanData.h>
#include <IHsvSatelliteUtility.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IRealTimeKernel.h>
#include <IHsvStream.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvPackageParser.h>
#include <CS2MwBase.h>

class CHsvDvbsGeneric_mAcq_Priv;
#define CLASSSCOPE CHsvDvbsGeneric_mAcq_Priv::
#include "locals_mAcq.h"

class CHsvDvbsGeneric_mAcq_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsGeneric_mAcq_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mAcq.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvDvbsGeneric_mAcq_Priv,iacqpow);
IHsvDigitalAcquisitionImpl(CHsvDvbsGeneric_mAcq_Priv,idataacq);
public:
ProvidesInterface<IHsvPower>	iacqpow;

ProvidesInterface<IHsvDigitalAcquisition>	idataacq;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDigitalAcquisitionNotify>	iacqN;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvDigitalScanData>	isrtdata;
RequiresInterface<IHsvDigitalScanData>	isvcscandata;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat3;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvDigitalAcquisition>	dataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvPackageParser>	ipackage;

private:
Pumpdefines(CHsvDvbsGeneric_mAcq_Priv);

public:
CHsvDvbsGeneric_mAcq_Priv():i__iacqpow(this),i__idataacq(this)
{
iacqpow	=	&i__iacqpow;
idataacq	=	&i__idataacq;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define Timerclk_iPresent() (Timerclk.Present())
#define Timerclk_ClocksourceManual	IProdApiClockEx_ClocksourceManual
#define Timerclk_ClocksourceTOT	IProdApiClockEx_ClocksourceTOT
#define Timerclk_ClocksourceECD	IProdApiClockEx_ClocksourceECD
#define Timerclk_ClocksourceTXT	IProdApiClockEx_ClocksourceTXT
#define Timerclk_ClocksourceTDT	IProdApiClockEx_ClocksourceTDT
#define Timerclk_ClocksourceTOTDVBS	IProdApiClockEx_ClocksourceTOTDVBS
#define Timerclk_ClocksourceTDTDVBS	IProdApiClockEx_ClocksourceTDTDVBS
#define Timerclk_InvalidClock	IProdApiClockEx_InvalidClock
#define Timerclk_SetTime(utc,lto,source)	Timerclk->SetTime(utc,lto,source)
#define Timerclk_SetUniversalTime(utc,source)	Timerclk->SetUniversalTime(utc,source)
#define Timerclk_SetLocalTime(time,source)	Timerclk->SetLocalTime(time,source)
#define Timerclk_GetUniversalTime()	Timerclk->GetUniversalTime()
#define Timerclk_GetLocalTimeOffset()	Timerclk->GetLocalTimeOffset()
#define Timerclk_GetLocalTime()	Timerclk->GetLocalTime()
#define Timerclk_SetNextLTOChange(timeOfChange,nextLTO,source)	Timerclk->SetNextLTOChange(timeOfChange,nextLTO,source)
#define Timerclk_GetAbsoluteLocalTime(Utc,localTime)	Timerclk->GetAbsoluteLocalTime(Utc,localTime)
#define Timerclk_GetAbsoluteUTC(localTime,Utc)	Timerclk->GetAbsoluteUTC(localTime,Utc)
#define Timerclk_TimeZoneNone	IProdApiClockEx_TimeZoneNone
#define Timerclk_TimeZoneBaleares	IProdApiClockEx_TimeZoneBaleares
#define Timerclk_TimeZoneCanaryIsland	IProdApiClockEx_TimeZoneCanaryIsland
#define Timerclk_TimeZoneContinental	IProdApiClockEx_TimeZoneContinental
#define Timerclk_TimeZoneAzores	IProdApiClockEx_TimeZoneAzores
#define Timerclk_TimeZoneKalingrad	IProdApiClockEx_TimeZoneKalingrad
#define Timerclk_TimeZoneMoscow	IProdApiClockEx_TimeZoneMoscow
#define Timerclk_TimeZoneSamara	IProdApiClockEx_TimeZoneSamara
#define Timerclk_TimeZoneYekaterinburg	IProdApiClockEx_TimeZoneYekaterinburg
#define Timerclk_TimeZoneOmsk	IProdApiClockEx_TimeZoneOmsk
#define Timerclk_TimeZoneKrasnoyarsk	IProdApiClockEx_TimeZoneKrasnoyarsk
#define Timerclk_TimeZoneIrkutsk	IProdApiClockEx_TimeZoneIrkutsk
#define Timerclk_TimeZoneYakutsk	IProdApiClockEx_TimeZoneYakutsk
#define Timerclk_TimeZoneVladivostok	IProdApiClockEx_TimeZoneVladivostok
#define Timerclk_TimeZoneMagadan	IProdApiClockEx_TimeZoneMagadan
#define Timerclk_TimeZoneKamchatka	IProdApiClockEx_TimeZoneKamchatka
#define Timerclk_SetUserTimeZone(timezone)	Timerclk->SetUserTimeZone(timezone)
#define Timerclk_GetUserTimeZone()	Timerclk->GetUserTimeZone()
#define Timerclk_GetTimeZone()	Timerclk->GetTimeZone()
#define Timerclk_DstAuto	IProdApiClockEx_DstAuto
#define Timerclk_DstOn	IProdApiClockEx_DstOn
#define Timerclk_DstOff	IProdApiClockEx_DstOff
#define Timerclk_IsDstActive()	Timerclk->IsDstActive()
#define Timerclk_SetUserDst(dst)	Timerclk->SetUserDst(dst)
#define Timerclk_GetUserDst()	Timerclk->GetUserDst()
#define Timerclk_LtoModeAutomatic	IProdApiClockEx_LtoModeAutomatic
#define Timerclk_LtoModeCountryDependent	IProdApiClockEx_LtoModeCountryDependent
#define Timerclk_SetLtoMode(ltomode)	Timerclk->SetLtoMode(ltomode)
#define Timerclk_GetLtoMode()	Timerclk->GetLtoMode()
#define Timerclk_IsClockManual()	Timerclk->IsClockManual()
#define Timerclk_IsClockDefined()	Timerclk->IsClockDefined()
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)
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
#define iacqN_iPresent() (iacqN.Present())
#define iacqN_OnDataAquired(Status)	iacqN->OnDataAquired(Status)
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
#define iprescanparser_iPresent() (iprescanparser.Present())
#define iprescanparser_ExtractPreScanTableFromXml()	iprescanparser->ExtractPreScanTableFromXml()
#define iprescanparser_GetNumberOfPrescanEntries()	iprescanparser->GetNumberOfPrescanEntries()
#define iprescanparser_GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)	iprescanparser->GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)
#define iprescanparser_GetSatelliteAttributeById(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeById(SatelliteAttribute)
#define iprescanparser_GetSatelliteAttributeByPosition(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeByPosition(SatelliteAttribute)
#define iprescanparser_SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)	iprescanparser->SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)
#define isrtdata_iPresent() (isrtdata.Present())
#define isrtdata_GetPtcInfo(ptc)	isrtdata->GetPtcInfo(ptc)
#define isrtdata_GetInstallationVersion()	isrtdata->GetInstallationVersion()
#define isrtdata_GetPtcInfoForSdSd(ptc)	isrtdata->GetPtcInfoForSdSd(ptc)
#define isrtdata_SyncComplete()	isrtdata->SyncComplete()
#define isvcscandata_iPresent() (isvcscandata.Present())
#define isvcscandata_GetPtcInfo(ptc)	isvcscandata->GetPtcInfo(ptc)
#define isvcscandata_GetInstallationVersion()	isvcscandata->GetInstallationVersion()
#define isvcscandata_GetPtcInfoForSdSd(ptc)	isvcscandata->GetPtcInfoForSdSd(ptc)
#define isvcscandata_SyncComplete()	isvcscandata->SyncComplete()
#define iutil_iPresent() (iutil.Present())
#define iutil_ResetData()	iutil->ResetData()
#define iutil_CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)	iutil->CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)
#define iutil_AddEntryToList(Entry)	iutil->AddEntryToList(Entry)
#define iutil_IsDuplicate(Entry)	iutil->IsDuplicate(Entry)
#define iutil_ReadBarkerMuxData(Data)	iutil->ReadBarkerMuxData(Data)
#define iutil_WriteBarkerMuxData(Data)	iutil->WriteBarkerMuxData(Data)
#define iutil_ResetBarkerMuxData()	iutil->ResetBarkerMuxData()
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsGeneric_mAcq_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define rins_iPresent() (rins.Present())
#define rins_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define rins_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define rins_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define rins_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define rins_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define rins_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define rins_GetCurrentInstallationState(mode,state)	rins->GetCurrentInstallationState(mode,state)
#define rins_StartInstallation(Source,Lnb,Mode)	rins->StartInstallation(Source,Lnb,Mode)
#define rins_StopInstallation()	rins->StopInstallation()
#define rins_WriteBarkerMuxData()	rins->WriteBarkerMuxData()
#define rins_GetNumberOfTvChannelsFound(Mode,Lnb)	rins->GetNumberOfTvChannelsFound(Mode,Lnb)
#define rins_GetNumberofRadioChannelsFound(Mode,Lnb)	rins->GetNumberofRadioChannelsFound(Mode,Lnb)
#define rins_GetNumberOfTvChannelsRemoved(Mode,Lnb)	rins->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define rins_GetNumberofRadioChannelsRemoved(Mode,Lnb)	rins->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define rins_GetNumberOfDigitalChannelsAdded()	rins->GetNumberOfDigitalChannelsAdded()
#define rins_GetNumberOfDigitalChannelsRemoved()	rins->GetNumberOfDigitalChannelsRemoved()
#define rins_GetNumberOfDigitalChannelsMoved()	rins->GetNumberOfDigitalChannelsMoved()
#define rins_LoadManualInstallationDefaultValues()	rins->LoadManualInstallationDefaultValues()
#define rins_StoreManualInstallationValues()	rins->StoreManualInstallationValues()
#define rins_SetManualInstallationAttributes(AttributeId,Value)	rins->SetManualInstallationAttributes(AttributeId,Value)
#define rins_GetAttribute(Mode,AttributeId)	rins->GetAttribute(Mode,AttributeId)
#define rins_GetScanProgressStatus(Mode)	rins->GetScanProgressStatus(Mode)
#define rins_GetSIDetails(SiValues)	rins->GetSIDetails(SiValues)
#define rtk_iPresent() (rtk.Present())
#define rtk_PrioHighest	rtk->PrioHighest()
#define rtk_PrioHigh	rtk->PrioHigh()
#define rtk_PrioAboveNormal	rtk->PrioAboveNormal()
#define rtk_PrioNormal	rtk->PrioNormal()
#define rtk_PrioBelowNormal	rtk->PrioBelowNormal()
#define rtk_PrioLow	rtk->PrioLow()
#define rtk_PrioLowest	rtk->PrioLowest()
#define rtk_TskCreate(func,priority,stacksize)	rtk->TskCreate(func,priority,stacksize)
#define rtk_TskCreateNoWatchdog(func,priority,stacksize)	rtk->TskCreateNoWatchdog(func,priority,stacksize)
#define rtk_TskDelete(tsk)	rtk->TskDelete(tsk)
#define rtk_TskCurrent()	rtk->TskCurrent()
#define rtk_TskSetPriority(tsk,priority)	rtk->TskSetPriority(tsk,priority)
#define rtk_TskSuspend(msecs)	rtk->TskSuspend(msecs)
#define rtk_TskResume(tsk)	rtk->TskResume(tsk)
#define rtk_TskBeginCriticalSection()	rtk->TskBeginCriticalSection()
#define rtk_TskEndCriticalSection()	rtk->TskEndCriticalSection()
#define rtk_TskFeedWatchdog()	rtk->TskFeedWatchdog()
#define rtk_TskBoostWatchdog(seconds)	rtk->TskBoostWatchdog(seconds)
#define rtk_TskWatchdogPeriod()	rtk->TskWatchdogPeriod()
#define rtk_IsrBegin()	rtk->IsrBegin()
#define rtk_IsrEnd()	rtk->IsrEnd()
#define rtk_IsrEvtSend(tsk,evt)	rtk->IsrEvtSend(tsk,evt)
#define rtk_IsrMbxSend(mbx,msg,param1,param2)	rtk->IsrMbxSend(mbx,msg,param1,param2)
#define rtk_SemCreate()	rtk->SemCreate()
#define rtk_SemCreateWithCeiling(ceiling)	rtk->SemCreateWithCeiling(ceiling)
#define rtk_SemDelete(sem)	rtk->SemDelete(sem)
#define rtk_SemAcquire(sem)	rtk->SemAcquire(sem)
#define rtk_SemAcquireNoWait(sem)	rtk->SemAcquireNoWait(sem)
#define rtk_SemRelease(sem)	rtk->SemRelease(sem)
#define rtk_EvtCreate(tsk)	rtk->EvtCreate(tsk)
#define rtk_EvtDelete(tsk,evt)	rtk->EvtDelete(tsk,evt)
#define rtk_EvtSend(tsk,evt)	rtk->EvtSend(tsk,evt)
#define rtk_EvtReceive(mask)	rtk->EvtReceive(mask)
#define rtk_EvtReceiveNoWait(mask)	rtk->EvtReceiveNoWait(mask)
#define rtk_EvtReceiveWait(mask,msecs)	rtk->EvtReceiveWait(mask,msecs)
#define rtk_EvtGetReserved(tsk)	rtk->EvtGetReserved(tsk)
#define rtk_TmrCreate(tsk,evt)	rtk->TmrCreate(tsk,evt)
#define rtk_TmrDelete(tmr)	rtk->TmrDelete(tmr)
#define rtk_TmrEvery(tmr,msecs)	rtk->TmrEvery(tmr,msecs)
#define rtk_TmrOnce(tmr,msecs)	rtk->TmrOnce(tmr,msecs)
#define rtk_TmrCancel(tmr)	rtk->TmrCancel(tmr)
#define rtk_TmrTime()	rtk->TmrTime()
#define rtk_TmrResolution()	rtk->TmrResolution()
#define rtk_MbxCreate()	rtk->MbxCreate()
#define rtk_MbxDelete(mbx)	rtk->MbxDelete(mbx)
#define rtk_MbxSend(mbx,msg,param1,param2)	rtk->MbxSend(mbx,msg,param1,param2)
#define rtk_MbxReceive(mbx,msg)	rtk->MbxReceive(mbx,msg)
#define rtk_MbxReceiveNoWait(mbx,msg)	rtk->MbxReceiveNoWait(mbx,msg)
#define rtk_TlsCreate(size)	rtk->TlsCreate(size)
#define rtk_TlsAccess(tls)	rtk->TlsAccess(tls)
#define strapi_iPresent() (strapi.Present())
#define strapi_GetSize(dest,spid)	strapi->GetSize(dest,spid)
#define strapi_GetIndex(dest,spid,key1,key2,key3,index)	strapi->GetIndex(dest,spid,key1,key2,key3,index)
#define strapi_GetByKey(dest,spid,key1,key2,key3,val)	strapi->GetByKey(dest,spid,key1,key2,key3,val)
#define strapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	strapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define strapi_GetByIndex(dest,spid,index,val)	strapi->GetByIndex(dest,spid,index,val)
#define idataacq_Homing	IHsvDigitalAcquisition_Homing
#define idataacq_Fallback	IHsvDigitalAcquisition_Fallback
#define idataacq_Normal	IHsvDigitalAcquisition_Normal
#define idataacq_Background	IHsvDigitalAcquisition_Background
#define idataacq_AcquireSDSDs	IHsvDigitalAcquisition_AcquireSDSDs
#define dataacq_AssignLCN(psvcdat) dataacq->AssignLCN(psvcdat)
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define dataacq_GetTricolorRegionNames(names, len) dataacq->GetTricolorRegionNames(names, len)
#define insN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define insN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define insN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
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
#include "locals_mAcq.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

