#ifndef  _CHSVDVBCINSTALLATION_M_PRIV_H
#define  _CHSVDVBCINSTALLATION_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvInstallation2.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvDigitalScan.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
#include <CTCMwBase.h>
class CHsvDvbCInstallation_m_Priv;
#define CLASSSCOPE CHsvDvbCInstallation_m_Priv::
#include "locals_m.h"

class CHsvDvbCInstallation_m_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbCInstallation_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmControlNotifyExImpl(CHsvDvbCInstallation_m_Priv,ctrlN);
IEnableImpl(CHsvDvbCInstallation_m_Priv,ena);
IHsvFrontEndApiNotifyImpl(CHsvDvbCInstallation_m_Priv,feapiN);
IHsvDigitalScanNotifyImpl(CHsvDvbCInstallation_m_Priv,ifullN);
IHsvDigitalScanNotifyImpl(CHsvDvbCInstallation_m_Priv,igridN);
IHsvInstallation2Impl(CHsvDvbCInstallation_m_Priv,ins);
IHsvDigitalScanNotifyImpl(CHsvDvbCInstallation_m_Priv,iprescanN);
IHsvDigitalScanNotifyImpl(CHsvDvbCInstallation_m_Priv,iquickN);
IHsvPowerImpl(CHsvDvbCInstallation_m_Priv,pow);
IHsvStreamNotifyImpl(CHsvDvbCInstallation_m_Priv,strapiN);
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScanNotify>	ifullN;

ProvidesInterface<IHsvDigitalScanNotify>	igridN;

ProvidesInterface<IHsvInstallation2>	ins;

ProvidesInterface<IHsvDigitalScanNotify>	iprescanN;

ProvidesInterface<IHsvDigitalScanNotify>	iquickN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvStreamNotify>	iacqstrapiN;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvSdmControlNotifyEx>	ifctrlN;
RequiresInterface<IEnable>	ifena;
RequiresInterface<IHsvStreamNotify>	ifstrapiN;
RequiresInterface<IHsvDigitalScan>	ifull;
RequiresInterface<IHsvFrontEndApiNotify>	ifullfeN;
RequiresInterface<IHsvPower>	ifullpow;
RequiresInterface<IHsvSdmControlNotifyEx>	igctrlN;
RequiresInterface<IEnable>	igena;
RequiresInterface<IHsvDigitalScan>	igrid;
RequiresInterface<IHsvFrontEndApiNotify>	igridfeN;
RequiresInterface<IHsvPower>	igridpow;
RequiresInterface<IHsvStreamNotify>	igstrapiN;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvSdmControlNotifyEx>	ipctrlN;
RequiresInterface<IEnable>	ipena;
RequiresInterface<IHsvDigitalScan>	iprescan;
RequiresInterface<IHsvFrontEndApiNotify>	iprescanfeN;
RequiresInterface<IHsvPower>	iprescanpow;
RequiresInterface<IHsvSdmControlNotifyEx>	iqctrlN;
RequiresInterface<IEnable>	iqena;
RequiresInterface<IHsvStreamNotify>	iqstrapiN;
RequiresInterface<IHsvDigitalScan>	iquick;
RequiresInterface<IHsvFrontEndApiNotify>	iquickfeN;
RequiresInterface<IHsvPower>	iquickpow;
RequiresInterface<IHsvPower>	isetpow;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
private:
Pumpdefines(CHsvDvbCInstallation_m_Priv);

public:
CHsvDvbCInstallation_m_Priv():i__ctrlN(this),i__ena(this),i__feapiN(this),i__ifullN(this),i__igridN(this),i__ins(this),i__iprescanN(this),i__iquickN(this),i__pow(this),i__strapiN(this)
{
ctrlN	=	&i__ctrlN;
ena	=	&i__ena;
feapiN	=	&i__feapiN;
ifullN	=	&i__ifullN;
igridN	=	&i__igridN;
ins	=	&i__ins;
iprescanN	=	&i__iprescanN;
iquickN	=	&i__iquickN;
pow	=	&i__pow;
strapiN	=	&i__strapiN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#define eurdiv_AnalogOnly()	eurdiv->AnalogOnly()
#define eurdiv_InstallTestStreams(installationmode,medium)	eurdiv->InstallTestStreams(installationmode,medium)
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_NoOfVirtualChannelsSupported(medium)	eurdiv->NoOfVirtualChannelsSupported(medium)
#define eurdiv_SupportMultipleOriginalNetworkId(medium)	eurdiv->SupportMultipleOriginalNetworkId(medium)
#define eurdiv_ForceLCNSyntax(medium)	eurdiv->ForceLCNSyntax(medium)
#define eurdiv_InstallDuplicateTsids(medium)	eurdiv->InstallDuplicateTsids(medium)
#define eurdiv_DefaultStreamPriority(medium)	eurdiv->DefaultStreamPriority(medium)
#define eurdiv_IsServiceInstallable(medium,ServiceType)	eurdiv->IsServiceInstallable(medium,ServiceType)
#define eurdiv_IsServiceSortable(medium,ServiceType)	eurdiv->IsServiceSortable(medium,ServiceType)
#define eurdiv_IsServiceHidden(medium,ServiceType)	eurdiv->IsServiceHidden(medium,ServiceType)
#define eurdiv_AcceptedStreamType(medium,StreamType)	eurdiv->AcceptedStreamType(medium,StreamType)
#define eurdiv_UpdateChannelName(medium)	eurdiv->UpdateChannelName(medium)
#define eurdiv_IsApmeaChannelListCountry()	eurdiv->IsApmeaChannelListCountry()
#define eurdiv_IsApmeaNetworkUpdateCountry()	eurdiv->IsApmeaNetworkUpdateCountry()
#define eurdiv_IsDbookCountry()	eurdiv->IsDbookCountry()
#define eurdiv_SkipInstallationPass	eurdiv->SkipInstallationPass()
#define eurdiv_FirstInstallationPass	eurdiv->FirstInstallationPass()
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_UpdateLCN(medium)	eurdiv->UpdateLCN(medium)
#define eurdiv_TxtInfoTimeout	eurdiv->TxtInfoTimeout()
#define eurdiv_VideoMuteColor	eurdiv->VideoMuteColor()
#define eurdiv_VideoMuteColorForLocks	eurdiv->VideoMuteColorForLocks()
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	eurdiv->DecoderSupported()
#define eurdiv_BreakInSupported	eurdiv->BreakInSupported()
#define eurdiv_ScartRuleSupported	eurdiv->ScartRuleSupported()
#define eurdiv_HsvAntennaAnalogTable	eurdiv->HsvAntennaAnalogTable()
#define eurdiv_HsvAntennaDigSrvcTable	eurdiv->HsvAntennaDigSrvcTable()
#define eurdiv_HsvAntennaDigPtcTable	eurdiv->HsvAntennaDigPtcTable()
#define eurdiv_HsvAntennaFreqMapTable	eurdiv->HsvAntennaFreqMapTable()
#define eurdiv_PersistentMemUpdateTimeout	eurdiv->PersistentMemUpdateTimeout()
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	eurdiv->MaxNoOfChannelsToStoreAntennaUserTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigPtcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaAnalogTable	eurdiv->MaxNoOfChannelsToStoreAntennaAnalogTable()
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreAntennaFreqMapTable()
#define eurdiv_IsHDSubtitleSupported()	eurdiv->IsHDSubtitleSupported()
#define eurdiv_AvSignalDetectionTimeOut	eurdiv->AvSignalDetectionTimeOut()
#define eurdiv_HearingImpairedOn	eurdiv->HearingImpairedOn()
#define eurdiv_VisuallyImpairedOn()	eurdiv->VisuallyImpairedOn()
#define eurdiv_IsQaaSupported()	eurdiv->IsQaaSupported()
#define eurdiv_IsPremixedVISupported()	eurdiv->IsPremixedVISupported()
#define eurdiv_EPGSecondaryDirName	eurdiv->EPGSecondaryDirName()
#define eurdiv_DefaultCharacterTable	eurdiv->DefaultCharacterTable()
#define eurdiv_ShortInfoCacheForCountry	eurdiv->ShortInfoCacheForCountry()
#define eurdiv_OUI	eurdiv->OUI()
#define eurdiv_HardwareModel	eurdiv->HardwareModel()
#define eurdiv_HardwareVersion	eurdiv->HardwareVersion()
#define eurdiv_GetNoOfBackBuffers(clientId)	eurdiv->GetNoOfBackBuffers(clientId)
#define eurdiv_SubtitleTimeOut	eurdiv->SubtitleTimeOut()
#define eurdiv_IsMpeg4STBoltOnSupported()	eurdiv->IsMpeg4STBoltOnSupported()
#define eurdiv_IsAVCDescriptorSupported()	eurdiv->IsAVCDescriptorSupported()
#define eurdiv_ForceCharacterTable()	eurdiv->ForceCharacterTable()
#define eurdiv_RegionalCharacterTable()	eurdiv->RegionalCharacterTable()
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
#define eurdiv_AnalogInstallationSequence	eurdiv->AnalogInstallationSequence()
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
#define eurdiv_HsvCableAnalogTable	eurdiv->HsvCableAnalogTable()
#define eurdiv_HsvCableDigSrvcTable	eurdiv->HsvCableDigSrvcTable()
#define eurdiv_HsvCableDigPtcTable	eurdiv->HsvCableDigPtcTable()
#define eurdiv_HsvCableSvcListDescTable	eurdiv->HsvCableSvcListDescTable()
#define eurdiv_HsvCableFreqMapTable	eurdiv->HsvCableFreqMapTable()
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	eurdiv->MaxNoOfChannelsToStoreCableUserTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreCableDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	eurdiv->MaxNoOfChannelsToStoreCableDigPtcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableAnalogTable	eurdiv->MaxNoOfChannelsToStoreCableAnalogTable()
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreCableFreqMapTable()
#define eurdiv_IsDVBCSupported()	eurdiv->IsDVBCSupported()
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_GetDefaultScanMode(medium)	eurdiv->GetDefaultScanMode(medium)
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanAnalog	IHsvEuropeDiversity2_ScanAnalog
#define eurdiv_ScanDVBT	IHsvEuropeDiversity2_ScanDVBT
#define eurdiv_ScanDVBC	IHsvEuropeDiversity2_ScanDVBC
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_ScanDVBTMpegOnly	IHsvEuropeDiversity2_ScanDVBTMpegOnly
#define eurdiv_ScanDVBCLite	IHsvEuropeDiversity2_ScanDVBCLite
#define eurdiv_GetScanPreference(medium,installationmode)	eurdiv->GetScanPreference(medium,installationmode)
#define eurdiv_GetNextScan(medium,installationmode,ScanPreference)	eurdiv->GetNextScan(medium,installationmode,ScanPreference)
#define eurdiv_GetDVBTMode()	eurdiv->GetDVBTMode()
#define eurdiv_GetDVBCMode()	eurdiv->GetDVBCMode()
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_GetNitPriority(medium)	eurdiv->GetNitPriority(medium)
#define eurdiv_IsServiceListDescriptorMandatory(medium)	eurdiv->IsServiceListDescriptorMandatory(medium)
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_GetAudioPreference()	eurdiv->GetAudioPreference()
#define eurdiv_GetSubtitlePreference()	eurdiv->GetSubtitlePreference()
#define eurdiv_UserPreferredAudioFormat()	eurdiv->UserPreferredAudioFormat()
#define eurdiv_IsFrequencyListStorageRequired()	eurdiv->IsFrequencyListStorageRequired()
#define eurdiv_GetDefaultAttributeValues(attrib,country,mode,length,values)	eurdiv->GetDefaultAttributeValues(attrib,country,mode,length,values)
#define eurdiv_HsvDVBCSettingsFilePath	eurdiv->HsvDVBCSettingsFilePath()
#define eurdiv_HsvCableDelSysDescFilePath	eurdiv->HsvCableDelSysDescFilePath()
#define eurdiv_HsvServiceListDescFilePath	eurdiv->HsvServiceListDescFilePath()
#define eurdiv_MaxLCNValue	eurdiv->MaxLCNValue()
#define eurdiv_IsBackgroundInstallRequired(medium)	eurdiv->IsBackgroundInstallRequired(medium)
#define eurdiv_SupportLCNVersion2(medium)	eurdiv->SupportLCNVersion2(medium)
#define eurdiv_ParseLCN(medium,installationmode)	eurdiv->ParseLCN(medium,installationmode)
#define eurdiv_IsPreScanSupported(medium)	eurdiv->IsPreScanSupported(medium)
#define eurdiv_SortNonLCNs(medium)	eurdiv->SortNonLCNs(medium)
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
#define eurdiv_GetAltFreqScanSupported(country)	eurdiv->GetAltFreqScanSupported(country)
#define eurdiv_FreqListDescriptorSupported(medium)	eurdiv->FreqListDescriptorSupported(medium)
#define eurdiv_IsAc3AudioSupported()	eurdiv->IsAc3AudioSupported()
#define eurdiv_GetDefaultAnalogInstallStatus(country)	eurdiv->GetDefaultAnalogInstallStatus(country)
#define eurdiv_StaticTable()	eurdiv->StaticTable()
#define eurdiv_GetDefaultDigitalInstallStatus(country)	eurdiv->GetDefaultDigitalInstallStatus(country)
#define eurdiv_IsMultifeedSupported()	eurdiv->IsMultifeedSupported()
#define eurdiv_IsZeroLCNHidden()	eurdiv->IsZeroLCNHidden()
#define eurdiv_GetViterbiBER()	eurdiv->GetViterbiBER()
#define eurdiv_DeltaViterbiBER()	eurdiv->DeltaViterbiBER()
#define eurdiv_GetShortInfoCacheSize()	eurdiv->GetShortInfoCacheSize()
#define eurdiv_GetDeltaSQI()	eurdiv->GetDeltaSQI()
#define eurdiv_GetDeltaSSI()	eurdiv->GetDeltaSSI()
#define eurdiv_AutomaticAnalogPresetAllocation()	eurdiv->AutomaticAnalogPresetAllocation()
#define eurdiv_AutomaticDigitalPresetAllocation()	eurdiv->AutomaticDigitalPresetAllocation()
#define eurdiv_AnalogStartPreset(country,medium,numRecords)	eurdiv->AnalogStartPreset(country,medium,numRecords)
#define eurdiv_AnalogEndPreset(country,medium)	eurdiv->AnalogEndPreset(country,medium)
#define eurdiv_NonRadioStartPreset(country,medium,numRecords)	eurdiv->NonRadioStartPreset(country,medium,numRecords)
#define eurdiv_NonRadioEndPreset(country,medium)	eurdiv->NonRadioEndPreset(country,medium)
#define eurdiv_RadioStartPreset(country,medium,numRecords)	eurdiv->RadioStartPreset(country,medium,numRecords)
#define eurdiv_RadioEndPreset(country,medium)	eurdiv->RadioEndPreset(country,medium)
#define eurdiv_IsHDSimulcastSupported()	eurdiv->IsHDSimulcastSupported()
#define eurdiv_IsDVBT2Supported()	eurdiv->IsDVBT2Supported()
#define eurdiv_MultipleLCNSupported()	eurdiv->MultipleLCNSupported()
#define eurdiv_SubtitlePidFallbackFirstPMT()	eurdiv->SubtitlePidFallbackFirstPMT()
#define eurdiv_DeleteTSNotIntransmission()	eurdiv->DeleteTSNotIntransmission()
#define eurdiv_ReapplyChildLockOnEventChange()	eurdiv->ReapplyChildLockOnEventChange()
#define eurdiv_DeleteServiceOnFly()	eurdiv->DeleteServiceOnFly()
#define hsverr_iPresent() (hsverr.Present())
#define hsverr_Ok	IHsvErrorCodeEx_Ok
#define hsverr_BadParameter	IHsvErrorCodeEx_BadParameter
#define hsverr_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define hsverr_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define hsverr_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define hsverr_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define hsverr_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define hsverr_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define hsverr_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define hsverr_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define hsverr_FileError	IHsvErrorCodeEx_FileError
#define hsverr_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define hsverr_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define hsverr_NotSupported	IHsvErrorCodeEx_NotSupported
#define hsverr_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define hsverr_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define hsverr_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define hsverr_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define hsverr_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define hsverr_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define hsverr_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define hsverr_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define hsverr_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define hsverr_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define hsverr_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define hsverr_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define hsverr_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define hsverr_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define hsverr_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define hsverr_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define hsverr_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define hsverr_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define hsverr_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define hsverr_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define iacqpow_iPresent() (iacqpow.Present())
#define iacqpow_Init()	iacqpow->Init()
#define iacqpow_TurnOn()	iacqpow->TurnOn()
#define iacqpow_TurnOff()	iacqpow->TurnOff()
#define iacqstrapiN_iPresent() (iacqstrapiN.Present())
#define iacqstrapiN_OnCompleted(dest,spid)	iacqstrapiN->OnCompleted(dest,spid)
#define iacqstrapiN_OnAdded(dest,spid,key1,key2,key3)	iacqstrapiN->OnAdded(dest,spid,key1,key2,key3)
#define iacqstrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	iacqstrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define iacqstrapiN_OnRemoved(dest,spid,key1,key2,key3)	iacqstrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define idataacq_iPresent() (idataacq.Present())
#define idataacq_Initialise()	idataacq->Initialise()
#define idataacq_InitialiseTotalChannels()	idataacq->InitialiseTotalChannels()
#define idataacq_AcquireData()	idataacq->AcquireData()
#define idataacq_GetNumberOfDigitalChannelsFound()	idataacq->GetNumberOfDigitalChannelsFound()
#define idataacq_GetNumberOfDigitalChannelsRemoved()	idataacq->GetNumberOfDigitalChannelsRemoved()
#define idataacq_GetNumberOfChannels(servicetype)	idataacq->GetNumberOfChannels(servicetype)
#define idataacq_GetNextSampleProgram()	idataacq->GetNextSampleProgram()
#define idataacq_AcquireLCNData()	idataacq->AcquireLCNData()
#define idataacq_AcquireServiceListData()	idataacq->AcquireServiceListData()
#define idataacq_StartBackgroundInstall()	idataacq->StartBackgroundInstall()
#define idataacq_ResetBackgroundInstall()	idataacq->ResetBackgroundInstall()
#define idataacq_IsNetworkUpdateDetected()	idataacq->IsNetworkUpdateDetected()
#define idataacq_DeleteServices()	idataacq->DeleteServices()
#define idataacq_GetNetworkIDList()	idataacq->GetNetworkIDList()
#define idataacq_GetNetworkIDName(index,NetworkName)	idataacq->GetNetworkIDName(index,NetworkName)
#define idataacq_SetFavouriteNetworkID(mode,attrib,index)	idataacq->SetFavouriteNetworkID(mode,attrib,index)
#define idataacq_ClearNetworkNameCache()	idataacq->ClearNetworkNameCache()
#define idataacq_IsLCNValid()	idataacq->IsLCNValid()
#define idataacq_AcquireONID()	idataacq->AcquireONID()
#define idataacq_SyncTemporaryTableRecords()	idataacq->SyncTemporaryTableRecords()
#define idataacq_ClearCache()	idataacq->ClearCache()
#define idataacq_GetRegionList(RegionsData)	idataacq->GetRegionList(RegionsData)
#define idataacq_SetFavouriteRegion(mode,index,RegionType)	idataacq->SetFavouriteRegion(mode,index,RegionType)
#define idataacq_GetFavouriteRegion(mode,RegionType)	idataacq->GetFavouriteRegion(mode,RegionType)
#define idataacq_Enable()	idataacq->Enable()
#define idataacq_Disable()	idataacq->Disable()
#define idataacq_GetCachedRegionDetails(RegionCache)	idataacq->GetCachedRegionDetails(RegionCache)
#define idataacq_UpdateBarkerMuxInfo(IsBarkerMux)	idataacq->UpdateBarkerMuxInfo(IsBarkerMux)
#define idvbset_iPresent() (idvbset.Present())
#define idvbset_SetAttribute(installationmode,attribute,value)	idvbset->SetAttribute(installationmode,attribute,value)
#define idvbset_GetAttribute(installationmode,attribute)	idvbset->GetAttribute(installationmode,attribute)
#define idvbset_ResetAttributeToDefault(installationmode,attribute)	idvbset->ResetAttributeToDefault(installationmode,attribute)
#define idvbset_ResetAttributeToPersistent(installationmode,attribute)	idvbset->ResetAttributeToPersistent(installationmode,attribute)
#define idvbset_ResetAllToDefault()	idvbset->ResetAllToDefault()
#define idvbset_ResetAllToPersistent()	idvbset->ResetAllToPersistent()
#define idvbset_GetAttributeLength(installationmode,attribute)	idvbset->GetAttributeLength(installationmode,attribute)
#define idvbset_GetNextAttributeValue(installationmode,attribute,value)	idvbset->GetNextAttributeValue(installationmode,attribute,value)
#define idvbset_SetPreferred(attribute,value,preferred)	idvbset->SetPreferred(attribute,value,preferred)
#define idvbset_GetAttributeRange(installationmode,attribute,minValue,maxValue)	idvbset->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define idvbset_GetAttributeMode(installationmode,attribute)	idvbset->GetAttributeMode(installationmode,attribute)
#define idvbset_SetAttributeMode(installationmode,attribute,attributeMode)	idvbset->SetAttributeMode(installationmode,attribute,attributeMode)
#define idvbset_CopyTemporaryToPersistent()	idvbset->CopyTemporaryToPersistent()
#define idvbset_ClearPersistent()	idvbset->ClearPersistent()
#define idvbset_CommitPreferred()	idvbset->CommitPreferred()
#define idvbset_IsAvailable(installationmode,attribute)	idvbset->IsAvailable(installationmode,attribute)
#define idvbset_SetUserSymbolRates(installationmode,values,len)	idvbset->SetUserSymbolRates(installationmode,values,len)
#define idvbset_GetUserSymbolRates(installationmode,values,len)	idvbset->GetUserSymbolRates(installationmode,values,len)
#define idvbset_GetPredefinedSymbolRates(installationmode,values,len)	idvbset->GetPredefinedSymbolRates(installationmode,values,len)
#define idvbset_ClearUserSymbolRates()	idvbset->ClearUserSymbolRates()
#define idvbset_GetONIDNetworkOperator(ONID)	idvbset->GetONIDNetworkOperator(ONID)
#define ifctrlN_iPresent() (ifctrlN.Present())
#define ifctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ifctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ifctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ifctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ifctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ifctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ifctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ifctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ifctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ifctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ifctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ifctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ifctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ifctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ifctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ifctrlN_OnEvent(dmx,eventid,value)	ifctrlN->OnEvent(dmx,eventid,value)
#define ifena_iPresent() (ifena.Present())
#define ifena_Enable()	ifena->Enable()
#define ifena_Disable()	ifena->Disable()
#define ifstrapiN_iPresent() (ifstrapiN.Present())
#define ifstrapiN_OnCompleted(dest,spid)	ifstrapiN->OnCompleted(dest,spid)
#define ifstrapiN_OnAdded(dest,spid,key1,key2,key3)	ifstrapiN->OnAdded(dest,spid,key1,key2,key3)
#define ifstrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	ifstrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define ifstrapiN_OnRemoved(dest,spid,key1,key2,key3)	ifstrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define ifull_iPresent() (ifull.Present())
#define ifull_stidle	IHsvDigitalScan_stidle
#define ifull_stfewait	IHsvDigitalScan_stfewait
#define ifull_stdmxwait	IHsvDigitalScan_stdmxwait
#define ifull_stdecision	IHsvDigitalScan_stdecision
#define ifull_Initialise()	ifull->Initialise()
#define ifull_StartInstallation(source,ptc,mode)	ifull->StartInstallation(source,ptc,mode)
#define ifull_StopInstallation()	ifull->StopInstallation()
#define ifull_StartDigitalScan()	ifull->StartDigitalScan()
#define ifull_StartDigitalTuning(frequency)	ifull->StartDigitalTuning(frequency)
#define ifull_StopDigitalScan()	ifull->StopDigitalScan()
#define ifull_GetNoOfPass()	ifull->GetNoOfPass()
#define ifull_GetCurrentPass()	ifull->GetCurrentPass()
#define ifull_GetPTCInfo(ptc)	ifull->GetPTCInfo(ptc)
#define ifull_StoreWeakSignalInstallationChannel()	ifull->StoreWeakSignalInstallationChannel()
#define ifull_GetNumberOfDigitalChannelsFound()	ifull->GetNumberOfDigitalChannelsFound()
#define ifull_GetNumberOfDigitalChannelsRemoved()	ifull->GetNumberOfDigitalChannelsRemoved()
#define ifull_GetTargetNitType(NetworkId)	ifull->GetTargetNitType(NetworkId)
#define ifull_GetCurrentState()	ifull->GetCurrentState()
#define ifull_GetSDTType()	ifull->GetSDTType()
#define ifull_GetAltTSValues(ONID,TSID)	ifull->GetAltTSValues(ONID,TSID)
#define ifull_GetCurTSValues(ONID,TSID)	ifull->GetCurTSValues(ONID,TSID)
#define ifull_GetStreamPriority()	ifull->GetStreamPriority()
#define ifull_SetStreamPriority(prio)	ifull->SetStreamPriority(prio)
#define ifull_SyncComplete()	ifull->SyncComplete()
#define ifull_ClearCache()	ifull->ClearCache()
#define ifull_GetPLPIds(PLPIds)	ifull->GetPLPIds(PLPIds)
#define ifull_GetHierarchyMode()	ifull->GetHierarchyMode()
#define ifull_ZiggoGetPTCInfo(ptc,Onid,Tsid)	ifull->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define ifull_ZiggoGetSDTType(Frequency)	ifull->ZiggoGetSDTType(Frequency)
#define ifull_GetEpgBarkerMux(ONID,TSID)	ifull->GetEpgBarkerMux(ONID,TSID)
#define ifull_ZiggoNetworkDataSet(ActionValue)	ifull->ZiggoNetworkDataSet(ActionValue)
#define ifull_ClearPersistent()	ifull->ClearPersistent()
#define ifullfeN_iPresent() (ifullfeN.Present())
#define ifullfeN_OnSearchStateChanged(state)	ifullfeN->OnSearchStateChanged(state)
#define ifullfeN_OnSearchInProgress(state)	ifullfeN->OnSearchInProgress(state)
#define ifullfeN_OnStationFound()	ifullfeN->OnStationFound()
#define ifullfeN_OnStationNotFound()	ifullfeN->OnStationNotFound()
#define ifullfeN_OnTvSystemDetected(tvSystem)	ifullfeN->OnTvSystemDetected(tvSystem)
#define ifullfeN_OnAfcFreqChanged(freq)	ifullfeN->OnAfcFreqChanged(freq)
#define ifullfeN_OnAfcLimitReached(freq)	ifullfeN->OnAfcLimitReached(freq)
#define ifullfeN_OnAfcModeChanged()	ifullfeN->OnAfcModeChanged()
#define ifullfeN_OnMeasReady(ssm,strength)	ifullfeN->OnMeasReady(ssm,strength)
#define ifullfeN_OnMeasAborted(ssm)	ifullfeN->OnMeasAborted(ssm)
#define ifullfeN_OnConstellationDetected(constellation)	ifullfeN->OnConstellationDetected(constellation)
#define ifullfeN_OnIqModeDetected(mode)	ifullfeN->OnIqModeDetected(mode)
#define ifullfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	ifullfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define ifullfeN_OnHierarchyModeDetected(mode)	ifullfeN->OnHierarchyModeDetected(mode)
#define ifullfeN_OnGuardIntervalDetected(interval)	ifullfeN->OnGuardIntervalDetected(interval)
#define ifullfeN_OnTxModeDetected(mode)	ifullfeN->OnTxModeDetected(mode)
#define ifullfeN_OnChanBandwidthDetected(bandwith)	ifullfeN->OnChanBandwidthDetected(bandwith)
#define ifullfeN_OnCarrierPresentChanged(carrier)	ifullfeN->OnCarrierPresentChanged(carrier)
#define ifullfeN_OnBerThresholdCrossed(ber,berThreshold)	ifullfeN->OnBerThresholdCrossed(ber,berThreshold)
#define ifullpow_iPresent() (ifullpow.Present())
#define ifullpow_Init()	ifullpow->Init()
#define ifullpow_TurnOn()	ifullpow->TurnOn()
#define ifullpow_TurnOff()	ifullpow->TurnOff()
#define igctrlN_iPresent() (igctrlN.Present())
#define igctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define igctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define igctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define igctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define igctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define igctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define igctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define igctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define igctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define igctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define igctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define igctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define igctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define igctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define igctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define igctrlN_OnEvent(dmx,eventid,value)	igctrlN->OnEvent(dmx,eventid,value)
#define igena_iPresent() (igena.Present())
#define igena_Enable()	igena->Enable()
#define igena_Disable()	igena->Disable()
#define igrid_iPresent() (igrid.Present())
#define igrid_stidle	IHsvDigitalScan_stidle
#define igrid_stfewait	IHsvDigitalScan_stfewait
#define igrid_stdmxwait	IHsvDigitalScan_stdmxwait
#define igrid_stdecision	IHsvDigitalScan_stdecision
#define igrid_Initialise()	igrid->Initialise()
#define igrid_StartInstallation(source,ptc,mode)	igrid->StartInstallation(source,ptc,mode)
#define igrid_StopInstallation()	igrid->StopInstallation()
#define igrid_StartDigitalScan()	igrid->StartDigitalScan()
#define igrid_StartDigitalTuning(frequency)	igrid->StartDigitalTuning(frequency)
#define igrid_StopDigitalScan()	igrid->StopDigitalScan()
#define igrid_GetNoOfPass()	igrid->GetNoOfPass()
#define igrid_GetCurrentPass()	igrid->GetCurrentPass()
#define igrid_GetPTCInfo(ptc)	igrid->GetPTCInfo(ptc)
#define igrid_StoreWeakSignalInstallationChannel()	igrid->StoreWeakSignalInstallationChannel()
#define igrid_GetNumberOfDigitalChannelsFound()	igrid->GetNumberOfDigitalChannelsFound()
#define igrid_GetNumberOfDigitalChannelsRemoved()	igrid->GetNumberOfDigitalChannelsRemoved()
#define igrid_GetTargetNitType(NetworkId)	igrid->GetTargetNitType(NetworkId)
#define igrid_GetCurrentState()	igrid->GetCurrentState()
#define igrid_GetSDTType()	igrid->GetSDTType()
#define igrid_GetAltTSValues(ONID,TSID)	igrid->GetAltTSValues(ONID,TSID)
#define igrid_GetCurTSValues(ONID,TSID)	igrid->GetCurTSValues(ONID,TSID)
#define igrid_GetStreamPriority()	igrid->GetStreamPriority()
#define igrid_SetStreamPriority(prio)	igrid->SetStreamPriority(prio)
#define igrid_SyncComplete()	igrid->SyncComplete()
#define igrid_ClearCache()	igrid->ClearCache()
#define igrid_GetPLPIds(PLPIds)	igrid->GetPLPIds(PLPIds)
#define igrid_GetHierarchyMode()	igrid->GetHierarchyMode()
#define igrid_ZiggoGetPTCInfo(ptc,Onid,Tsid)	igrid->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define igrid_ZiggoGetSDTType(Frequency)	igrid->ZiggoGetSDTType(Frequency)
#define igrid_GetEpgBarkerMux(ONID,TSID)	igrid->GetEpgBarkerMux(ONID,TSID)
#define igrid_ZiggoNetworkDataSet(ActionValue)	igrid->ZiggoNetworkDataSet(ActionValue)
#define igrid_ClearPersistent()	igrid->ClearPersistent()
#define igridfeN_iPresent() (igridfeN.Present())
#define igridfeN_OnSearchStateChanged(state)	igridfeN->OnSearchStateChanged(state)
#define igridfeN_OnSearchInProgress(state)	igridfeN->OnSearchInProgress(state)
#define igridfeN_OnStationFound()	igridfeN->OnStationFound()
#define igridfeN_OnStationNotFound()	igridfeN->OnStationNotFound()
#define igridfeN_OnTvSystemDetected(tvSystem)	igridfeN->OnTvSystemDetected(tvSystem)
#define igridfeN_OnAfcFreqChanged(freq)	igridfeN->OnAfcFreqChanged(freq)
#define igridfeN_OnAfcLimitReached(freq)	igridfeN->OnAfcLimitReached(freq)
#define igridfeN_OnAfcModeChanged()	igridfeN->OnAfcModeChanged()
#define igridfeN_OnMeasReady(ssm,strength)	igridfeN->OnMeasReady(ssm,strength)
#define igridfeN_OnMeasAborted(ssm)	igridfeN->OnMeasAborted(ssm)
#define igridfeN_OnConstellationDetected(constellation)	igridfeN->OnConstellationDetected(constellation)
#define igridfeN_OnIqModeDetected(mode)	igridfeN->OnIqModeDetected(mode)
#define igridfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	igridfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define igridfeN_OnHierarchyModeDetected(mode)	igridfeN->OnHierarchyModeDetected(mode)
#define igridfeN_OnGuardIntervalDetected(interval)	igridfeN->OnGuardIntervalDetected(interval)
#define igridfeN_OnTxModeDetected(mode)	igridfeN->OnTxModeDetected(mode)
#define igridfeN_OnChanBandwidthDetected(bandwith)	igridfeN->OnChanBandwidthDetected(bandwith)
#define igridfeN_OnCarrierPresentChanged(carrier)	igridfeN->OnCarrierPresentChanged(carrier)
#define igridfeN_OnBerThresholdCrossed(ber,berThreshold)	igridfeN->OnBerThresholdCrossed(ber,berThreshold)
#define igridpow_iPresent() (igridpow.Present())
#define igridpow_Init()	igridpow->Init()
#define igridpow_TurnOn()	igridpow->TurnOn()
#define igridpow_TurnOff()	igridpow->TurnOff()
#define igstrapiN_iPresent() (igstrapiN.Present())
#define igstrapiN_OnCompleted(dest,spid)	igstrapiN->OnCompleted(dest,spid)
#define igstrapiN_OnAdded(dest,spid,key1,key2,key3)	igstrapiN->OnAdded(dest,spid,key1,key2,key3)
#define igstrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	igstrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define igstrapiN_OnRemoved(dest,spid,key1,key2,key3)	igstrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define insN_iPresent() (insN.Present())
#define insN_EventInstallationCompleted	IHsvInstallationNotify_EventInstallationCompleted
#define insN_EventInstallationStarted	IHsvInstallationNotify_EventInstallationStarted
#define insN_EventInstallationStopped	IHsvInstallationNotify_EventInstallationStopped
#define insN_EventInstallationPaused	IHsvInstallationNotify_EventInstallationPaused
#define insN_EventInstallationContinued	IHsvInstallationNotify_EventInstallationContinued
#define insN_EventChannelFound	IHsvInstallationNotify_EventChannelFound
#define insN_EventChannelNotFound	IHsvInstallationNotify_EventChannelNotFound
#define insN_EventSearchInProgress	IHsvInstallationNotify_EventSearchInProgress
#define insN_EventTuningStarted	IHsvInstallationNotify_EventTuningStarted
#define insN_EventTuningStationFound	IHsvInstallationNotify_EventTuningStationFound
#define insN_EventTuningStationNotFound	IHsvInstallationNotify_EventTuningStationNotFound
#define insN_EventManualInstallationCniExtractionStarted	IHsvInstallationNotify_EventManualInstallationCniExtractionStarted
#define insN_EventManualInstallationCniExtractionEnded	IHsvInstallationNotify_EventManualInstallationCniExtractionEnded
#define insN_EventATSSortingStarted	IHsvInstallationNotify_EventATSSortingStarted
#define insN_EventAciStoreStarted	IHsvInstallationNotify_EventAciStoreStarted
#define insN_EventTvSystemChanged	IHsvInstallationNotify_EventTvSystemChanged
#define insN_EventMediumChanged	IHsvInstallationNotify_EventMediumChanged
#define insN_EventSignalStrengthChanged	IHsvInstallationNotify_EventSignalStrengthChanged
#define insN_EventBackGroundCNIUpdated	IHsvInstallationNotify_EventBackGroundCNIUpdated
#define insN_EventPresetStored	IHsvInstallationNotify_EventPresetStored
#define insN_EventPhaseStarted	IHsvInstallationNotify_EventPhaseStarted
#define insN_EventPhaseCompleted	IHsvInstallationNotify_EventPhaseCompleted
#define insN_EventChannelIterationStarted	IHsvInstallationNotify_EventChannelIterationStarted
#define insN_EventHeirarchyModeDetected	IHsvInstallationNotify_EventHeirarchyModeDetected
#define insN_EventChannelAdded	IHsvInstallationNotify_EventChannelAdded
#define insN_EventChannelRemoved	IHsvInstallationNotify_EventChannelRemoved
#define insN_EventNetworkUpdateDetected	IHsvInstallationNotify_EventNetworkUpdateDetected
#define insN_EventDisplayNetworkNames	IHsvInstallationNotify_EventDisplayNetworkNames
#define insN_EventNIDInvalid	IHsvInstallationNotify_EventNIDInvalid
#define insN_EventNetworkUpdateNotDetected	IHsvInstallationNotify_EventNetworkUpdateNotDetected
#define insN_EventOnConflictsDetected	IHsvInstallationNotify_EventOnConflictsDetected
#define insN_EventDisplayRegionNames	IHsvInstallationNotify_EventDisplayRegionNames
#define insN_EventPLPsDetected	IHsvInstallationNotify_EventPLPsDetected
#define insN_NetworkOperator	IHsvInstallationNotify_NetworkOperator
#define insN_EventPresetAdded	IHsvInstallationNotify_EventPresetAdded
#define insN_EventPresetDeleted IHsvInstallationNotify_EventPresetDeleted	
#define insN_EventUpdated	 IHsvInstallationNotify_EventUpdated
#define insN_EventMultiPackageFound 	IHsvInstallationNotify_EventMultiPackageFound
#define	insN_EventMultiPackageToBeDisplayed 	IHsvInstallationNotify_EventMultiPackageToBeDisplayed
#define	insN_EventMultiPackageRemoved	 IHsvInstallationNotify_EventMultiPackageRemoved
#define insN_EventNewPresetNumber		IHsvInstallationNotify_EventNewPresetNumber
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define ipctrlN_iPresent() (ipctrlN.Present())
#define ipctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ipctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ipctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ipctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ipctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ipctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ipctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ipctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ipctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ipctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ipctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ipctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ipctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ipctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ipctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ipctrlN_OnEvent(dmx,eventid,value)	ipctrlN->OnEvent(dmx,eventid,value)
#define ipena_iPresent() (ipena.Present())
#define ipena_Enable()	ipena->Enable()
#define ipena_Disable()	ipena->Disable()
#define iprescan_iPresent() (iprescan.Present())
#define iprescan_stidle	IHsvDigitalScan_stidle
#define iprescan_stfewait	IHsvDigitalScan_stfewait
#define iprescan_stdmxwait	IHsvDigitalScan_stdmxwait
#define iprescan_stdecision	IHsvDigitalScan_stdecision
#define iprescan_Initialise()	iprescan->Initialise()
#define iprescan_StartInstallation(source,ptc,mode)	iprescan->StartInstallation(source,ptc,mode)
#define iprescan_StopInstallation()	iprescan->StopInstallation()
#define iprescan_StartDigitalScan()	iprescan->StartDigitalScan()
#define iprescan_StartDigitalTuning(frequency)	iprescan->StartDigitalTuning(frequency)
#define iprescan_StopDigitalScan()	iprescan->StopDigitalScan()
#define iprescan_GetNoOfPass()	iprescan->GetNoOfPass()
#define iprescan_GetCurrentPass()	iprescan->GetCurrentPass()
#define iprescan_GetPTCInfo(ptc)	iprescan->GetPTCInfo(ptc)
#define iprescan_StoreWeakSignalInstallationChannel()	iprescan->StoreWeakSignalInstallationChannel()
#define iprescan_GetNumberOfDigitalChannelsFound()	iprescan->GetNumberOfDigitalChannelsFound()
#define iprescan_GetNumberOfDigitalChannelsRemoved()	iprescan->GetNumberOfDigitalChannelsRemoved()
#define iprescan_GetTargetNitType(NetworkId)	iprescan->GetTargetNitType(NetworkId)
#define iprescan_GetCurrentState()	iprescan->GetCurrentState()
#define iprescan_GetSDTType()	iprescan->GetSDTType()
#define iprescan_GetAltTSValues(ONID,TSID)	iprescan->GetAltTSValues(ONID,TSID)
#define iprescan_GetCurTSValues(ONID,TSID)	iprescan->GetCurTSValues(ONID,TSID)
#define iprescan_GetStreamPriority()	iprescan->GetStreamPriority()
#define iprescan_SetStreamPriority(prio)	iprescan->SetStreamPriority(prio)
#define iprescan_SyncComplete()	iprescan->SyncComplete()
#define iprescan_ClearCache()	iprescan->ClearCache()
#define iprescan_GetPLPIds(PLPIds)	iprescan->GetPLPIds(PLPIds)
#define iprescan_GetHierarchyMode()	iprescan->GetHierarchyMode()
#define iprescan_ZiggoGetPTCInfo(ptc,Onid,Tsid)	iprescan->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define iprescan_ZiggoGetSDTType(Frequency)	iprescan->ZiggoGetSDTType(Frequency)
#define iprescan_GetEpgBarkerMux(ONID,TSID)	iprescan->GetEpgBarkerMux(ONID,TSID)
#define iprescan_ZiggoNetworkDataSet(ActionValue)	iprescan->ZiggoNetworkDataSet(ActionValue)
#define iprescan_ClearPersistent()	iprescan->ClearPersistent()
#define iprescanfeN_iPresent() (iprescanfeN.Present())
#define iprescanfeN_OnSearchStateChanged(state)	iprescanfeN->OnSearchStateChanged(state)
#define iprescanfeN_OnSearchInProgress(state)	iprescanfeN->OnSearchInProgress(state)
#define iprescanfeN_OnStationFound()	iprescanfeN->OnStationFound()
#define iprescanfeN_OnStationNotFound()	iprescanfeN->OnStationNotFound()
#define iprescanfeN_OnTvSystemDetected(tvSystem)	iprescanfeN->OnTvSystemDetected(tvSystem)
#define iprescanfeN_OnAfcFreqChanged(freq)	iprescanfeN->OnAfcFreqChanged(freq)
#define iprescanfeN_OnAfcLimitReached(freq)	iprescanfeN->OnAfcLimitReached(freq)
#define iprescanfeN_OnAfcModeChanged()	iprescanfeN->OnAfcModeChanged()
#define iprescanfeN_OnMeasReady(ssm,strength)	iprescanfeN->OnMeasReady(ssm,strength)
#define iprescanfeN_OnMeasAborted(ssm)	iprescanfeN->OnMeasAborted(ssm)
#define iprescanfeN_OnConstellationDetected(constellation)	iprescanfeN->OnConstellationDetected(constellation)
#define iprescanfeN_OnIqModeDetected(mode)	iprescanfeN->OnIqModeDetected(mode)
#define iprescanfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	iprescanfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define iprescanfeN_OnHierarchyModeDetected(mode)	iprescanfeN->OnHierarchyModeDetected(mode)
#define iprescanfeN_OnGuardIntervalDetected(interval)	iprescanfeN->OnGuardIntervalDetected(interval)
#define iprescanfeN_OnTxModeDetected(mode)	iprescanfeN->OnTxModeDetected(mode)
#define iprescanfeN_OnChanBandwidthDetected(bandwith)	iprescanfeN->OnChanBandwidthDetected(bandwith)
#define iprescanfeN_OnCarrierPresentChanged(carrier)	iprescanfeN->OnCarrierPresentChanged(carrier)
#define iprescanfeN_OnBerThresholdCrossed(ber,berThreshold)	iprescanfeN->OnBerThresholdCrossed(ber,berThreshold)
#define iprescanpow_iPresent() (iprescanpow.Present())
#define iprescanpow_Init()	iprescanpow->Init()
#define iprescanpow_TurnOn()	iprescanpow->TurnOn()
#define iprescanpow_TurnOff()	iprescanpow->TurnOff()
#define iqctrlN_iPresent() (iqctrlN.Present())
#define iqctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iqctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iqctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iqctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iqctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iqctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iqctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iqctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iqctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iqctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iqctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iqctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iqctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iqctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iqctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iqctrlN_OnEvent(dmx,eventid,value)	iqctrlN->OnEvent(dmx,eventid,value)
#define iqena_iPresent() (iqena.Present())
#define iqena_Enable()	iqena->Enable()
#define iqena_Disable()	iqena->Disable()
#define iqstrapiN_iPresent() (iqstrapiN.Present())
#define iqstrapiN_OnCompleted(dest,spid)	iqstrapiN->OnCompleted(dest,spid)
#define iqstrapiN_OnAdded(dest,spid,key1,key2,key3)	iqstrapiN->OnAdded(dest,spid,key1,key2,key3)
#define iqstrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	iqstrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define iqstrapiN_OnRemoved(dest,spid,key1,key2,key3)	iqstrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define iquick_iPresent() (iquick.Present())
#define iquick_stidle	IHsvDigitalScan_stidle
#define iquick_stfewait	IHsvDigitalScan_stfewait
#define iquick_stdmxwait	IHsvDigitalScan_stdmxwait
#define iquick_stdecision	IHsvDigitalScan_stdecision
#define iquick_Initialise()	iquick->Initialise()
#define iquick_StartInstallation(source,ptc,mode)	iquick->StartInstallation(source,ptc,mode)
#define iquick_StopInstallation()	iquick->StopInstallation()
#define iquick_StartDigitalScan()	iquick->StartDigitalScan()
#define iquick_StartDigitalTuning(frequency)	iquick->StartDigitalTuning(frequency)
#define iquick_StopDigitalScan()	iquick->StopDigitalScan()
#define iquick_GetNoOfPass()	iquick->GetNoOfPass()
#define iquick_GetCurrentPass()	iquick->GetCurrentPass()
#define iquick_GetPTCInfo(ptc)	iquick->GetPTCInfo(ptc)
#define iquick_StoreWeakSignalInstallationChannel()	iquick->StoreWeakSignalInstallationChannel()
#define iquick_GetNumberOfDigitalChannelsFound()	iquick->GetNumberOfDigitalChannelsFound()
#define iquick_GetNumberOfDigitalChannelsRemoved()	iquick->GetNumberOfDigitalChannelsRemoved()
#define iquick_GetTargetNitType(NetworkId)	iquick->GetTargetNitType(NetworkId)
#define iquick_GetCurrentState()	iquick->GetCurrentState()
#define iquick_GetSDTType()	iquick->GetSDTType()
#define iquick_GetAltTSValues(ONID,TSID)	iquick->GetAltTSValues(ONID,TSID)
#define iquick_GetCurTSValues(ONID,TSID)	iquick->GetCurTSValues(ONID,TSID)
#define iquick_GetStreamPriority()	iquick->GetStreamPriority()
#define iquick_SetStreamPriority(prio)	iquick->SetStreamPriority(prio)
#define iquick_SyncComplete()	iquick->SyncComplete()
#define iquick_ClearCache()	iquick->ClearCache()
#define iquick_GetPLPIds(PLPIds)	iquick->GetPLPIds(PLPIds)
#define iquick_GetHierarchyMode()	iquick->GetHierarchyMode()
#define iquick_ZiggoGetPTCInfo(ptc,Onid,Tsid)	iquick->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define iquick_ZiggoGetSDTType(Frequency)	iquick->ZiggoGetSDTType(Frequency)
#define iquick_GetEpgBarkerMux(ONID,TSID)	iquick->GetEpgBarkerMux(ONID,TSID)
#define iquick_ZiggoNetworkDataSet(ActionValue)	iquick->ZiggoNetworkDataSet(ActionValue)
#define iquick_ClearPersistent()	iquick->ClearPersistent()
#define iquick_GetSIDetails(sivalues)	iquick->GetSIDetails(sivalues)
#define iquickfeN_iPresent() (iquickfeN.Present())
#define iquickfeN_OnSearchStateChanged(state)	iquickfeN->OnSearchStateChanged(state)
#define iquickfeN_OnSearchInProgress(state)	iquickfeN->OnSearchInProgress(state)
#define iquickfeN_OnStationFound()	iquickfeN->OnStationFound()
#define iquickfeN_OnStationNotFound()	iquickfeN->OnStationNotFound()
#define iquickfeN_OnTvSystemDetected(tvSystem)	iquickfeN->OnTvSystemDetected(tvSystem)
#define iquickfeN_OnAfcFreqChanged(freq)	iquickfeN->OnAfcFreqChanged(freq)
#define iquickfeN_OnAfcLimitReached(freq)	iquickfeN->OnAfcLimitReached(freq)
#define iquickfeN_OnAfcModeChanged()	iquickfeN->OnAfcModeChanged()
#define iquickfeN_OnMeasReady(ssm,strength)	iquickfeN->OnMeasReady(ssm,strength)
#define iquickfeN_OnMeasAborted(ssm)	iquickfeN->OnMeasAborted(ssm)
#define iquickfeN_OnConstellationDetected(constellation)	iquickfeN->OnConstellationDetected(constellation)
#define iquickfeN_OnIqModeDetected(mode)	iquickfeN->OnIqModeDetected(mode)
#define iquickfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	iquickfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define iquickfeN_OnHierarchyModeDetected(mode)	iquickfeN->OnHierarchyModeDetected(mode)
#define iquickfeN_OnGuardIntervalDetected(interval)	iquickfeN->OnGuardIntervalDetected(interval)
#define iquickfeN_OnTxModeDetected(mode)	iquickfeN->OnTxModeDetected(mode)
#define iquickfeN_OnChanBandwidthDetected(bandwith)	iquickfeN->OnChanBandwidthDetected(bandwith)
#define iquickfeN_OnCarrierPresentChanged(carrier)	iquickfeN->OnCarrierPresentChanged(carrier)
#define iquickfeN_OnBerThresholdCrossed(ber,berThreshold)	iquickfeN->OnBerThresholdCrossed(ber,berThreshold)
#define iquickpow_iPresent() (iquickpow.Present())
#define iquickpow_Init()	iquickpow->Init()
#define iquickpow_TurnOn()	iquickpow->TurnOn()
#define iquickpow_TurnOff()	iquickpow->TurnOff()
#define isetpow_iPresent() (isetpow.Present())
#define isetpow_Init()	isetpow->Init()
#define isetpow_TurnOn()	isetpow->TurnOn()
#define isetpow_TurnOff()	isetpow->TurnOff()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbCInstallation_m_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define rins_iPresent() (rins.Present())
#define rins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define rins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define rins_StIdle	IHsvInstallation2_StIdle
#define rins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define rins_StDigital	IHsvInstallation2_StDigital
#define rins_StAnalog	IHsvInstallation2_StAnalog
#define rins_StPreSorting	IHsvInstallation2_StPreSorting
#define rins_StSorting	IHsvInstallation2_StSorting
#define rins_Terrestrial	IHsvInstallation2_Terrestrial
#define rins_Cable	IHsvInstallation2_Cable
#define rins_Satellite	IHsvInstallation2_Satellite
#define rins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define rins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define rins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define rins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define rins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define rins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define rins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define rins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define rins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define rins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define rins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define rins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define rins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define rins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define rins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define rins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define rins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define rins_MaxChannel	IHsvInstallation2_MaxChannel
#define rins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define rins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define rins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define rins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define rins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define rins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define rins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define rins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define rins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define rins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define rins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define rins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define rins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define rins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define rins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define rins_InsAssm	IHsvInstallation2_InsAssm
#define rins_InsVssm	IHsvInstallation2_InsVssm
#define rins_InsQssm	IHsvInstallation2_InsQssm
#define rins_InsSssm	IHsvInstallation2_InsSssm
#define rins_StartInstallation(source,ptc,mode)	rins->StartInstallation(source,ptc,mode)
#define rins_StopInstallation()	rins->StopInstallation()
#define rins_GetNumberOfAnalogChannelsFound()	rins->GetNumberOfAnalogChannelsFound()
#define rins_GetNumberOfDigitalChannelsFound()	rins->GetNumberOfDigitalChannelsFound()
#define rins_GetNumberOfDigitalChannelsRemoved()	rins->GetNumberOfDigitalChannelsRemoved()
#define rins_GetInstallationProgress()	rins->GetInstallationProgress()
#define rins_GetInstallationStatus()	rins->GetInstallationStatus()
#define rins_GetInstallationMode()	rins->GetInstallationMode()
#define rins_IsUpdateInstallationSupported()	rins->IsUpdateInstallationSupported()
#define rins_SetLCNSortingControl(mode)	rins->SetLCNSortingControl(mode)
#define rins_GetLCNSortingControl()	rins->GetLCNSortingControl()
#define rins_SetInstallCountry(country)	rins->SetInstallCountry(country)
#define rins_SetSystemCountry(country)	rins->SetSystemCountry(country)
#define rins_GetFirstIntalledDigitalChannel(channelno)	rins->GetFirstIntalledDigitalChannel(channelno)
#define rins_GetFirstIntalledAnalogueChannel(channelno)	rins->GetFirstIntalledAnalogueChannel(channelno)
#define rins_GetFirstIntalledRadioChannel(channelno)	rins->GetFirstIntalledRadioChannel(channelno)
#define rins_GetFirstInstalledChannel(channelno)	rins->GetFirstInstalledChannel(channelno)
#define rins_GetNetworkNameForNetworkID(networkID,NetworkName)	rins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define rins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	rins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define rins_IsValidNetworkId(networkID)	rins->IsValidNetworkId(networkID)
#define rins_SetLowestNetworkId(networkID)	rins->SetLowestNetworkId(networkID)
#define rins_SetManualFrequency(frequency,offset,finetune)	rins->SetManualFrequency(frequency,offset,finetune)
#define rins_GetManualFrequency(frequency,offset,finetune)	rins->GetManualFrequency(frequency,offset,finetune)
#define rins_SetManualChannel(channel,finetune)	rins->SetManualChannel(channel,finetune)
#define rins_GetManualChannel(channel,finetune)	rins->GetManualChannel(channel,finetune)
#define rins_IsManualInstallationModeSupported(mode)	rins->IsManualInstallationModeSupported(mode)
#define rins_SetManualInstallationMode(mode)	rins->SetManualInstallationMode(mode)
#define rins_GetManualInstallationMode()	rins->GetManualInstallationMode()
#define rins_StoreManualInstallationValues(channel)	rins->StoreManualInstallationValues(channel)
#define rins_AutoStoreManualInstallationValues()	rins->AutoStoreManualInstallationValues()
#define rins_StartFrequencySearch()	rins->StartFrequencySearch()
#define rins_GetSigStrengthRange(measmode,min,max)	rins->GetSigStrengthRange(measmode,min,max)
#define rins_GetSignalstrength(measmode)	rins->GetSignalstrength(measmode)
#define rins_StoreWeakSignalInstallationChannel()	rins->StoreWeakSignalInstallationChannel()
#define rins_GetInstalledWeakSignalChannel()	rins->GetInstalledWeakSignalChannel()
#define rins_GetSignalQualityBer()	rins->GetSignalQualityBer()
#define rins_IsFrequencySearchDirectionSupported(searchup)	rins->IsFrequencySearchDirectionSupported(searchup)
#define rins_SetFrequencySearchDirection(searchup)	rins->SetFrequencySearchDirection(searchup)
#define rins_GetFrequencySearchDirection()	rins->GetFrequencySearchDirection()
#define rins_GetMinFrequency()	rins->GetMinFrequency()
#define rins_GetMaxFrequency()	rins->GetMaxFrequency()
#define rins_GetTunerFrequency()	rins->GetTunerFrequency()
#define rins_SetTunerFrequency(freq,fineTune)	rins->SetTunerFrequency(freq,fineTune)
#define rins_GetFrequency2Channel(chantbl,frequency)	rins->GetFrequency2Channel(chantbl,frequency)
#define rins_GetChannel2CarrierFrequency(chantbl,channel)	rins->GetChannel2CarrierFrequency(chantbl,channel)
#define rins_GetChannel2CentreFrequency(chantbl,channel)	rins->GetChannel2CentreFrequency(chantbl,channel)
#define rins_GetCurrentPass()	rins->GetCurrentPass()
#define rins_GetNoOfPass()	rins->GetNoOfPass()
#define rins_GetCurrentPassType()	rins->GetCurrentPassType()
#define rins_IsMediumSupported(medium)	rins->IsMediumSupported(medium)
#define rins_GetMedium()	rins->GetMedium()
#define rins_SetMedium(medium)	rins->SetMedium(medium)
#define rins_GetInstalledMedium()	rins->GetInstalledMedium()
#define rins_SetInstalledMedium(medium)	rins->SetInstalledMedium(medium)
#define rins_IsTvSystemSupported(tvsystem)	rins->IsTvSystemSupported(tvsystem)
#define rins_SetTvSystem(tvsystem)	rins->SetTvSystem(tvsystem)
#define rins_GetTvSystem()	rins->GetTvSystem()
#define rins_IsColorSystemSupported(colorsystem)	rins->IsColorSystemSupported(colorsystem)
#define rins_SetColorSystem(colorsystem)	rins->SetColorSystem(colorsystem)
#define rins_GetColorSystem()	rins->GetColorSystem()
#define rins_IsValidPTC(medium,PTC)	rins->IsValidPTC(medium,PTC)
#define rins_GetMinPTC(medium)	rins->GetMinPTC(medium)
#define rins_GetMaxPTC(medium)	rins->GetMaxPTC(medium)
#define rins_GetLastPTCFound()	rins->GetLastPTCFound()
#define rins_GetNumberOfPTCsFound()	rins->GetNumberOfPTCsFound()
#define rins_StartSigStrMeas(measmode)	rins->StartSigStrMeas(measmode)
#define rins_StopSigStrMeas(measmode)	rins->StopSigStrMeas(measmode)
#define rins_IsSignalStrengthMeasurementValid(measmode)	rins->IsSignalStrengthMeasurementValid(measmode)
#define rins_ScanNone	IHsvInstallation2_ScanNone
#define rins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define rins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define rins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define rins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define rins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define rins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define rins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define rins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define rins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define rins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define rins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define rins_AttributeCity	IHsvInstallation2_AttributeCity
#define rins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define rins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define rins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define rins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define rins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define rins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define rins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define rins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define rins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define rins_AttributeFavoriteChannelId	IHsvInstallation2_AttributeFavoriteChannelId
#define rins_QuickScan	IHsvInstallation2_QuickScan
#define rins_FullScan	IHsvInstallation2_FullScan
#define rins_GridScan	IHsvInstallation2_GridScan
#define rins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define rins_ManualValue	IHsvInstallation2_ManualValue
#define rins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	rins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define rins_SetAttributeMode(installationmode,attribute,attributeMode)	rins->SetAttributeMode(installationmode,attribute,attributeMode)
#define rins_SetAttribute(installationmode,attribute,value)	rins->SetAttribute(installationmode,attribute,value)
#define rins_GetAttributeMode(installationmode,attribute)	rins->GetAttributeMode(installationmode,attribute)
#define rins_GetAttribute(installationmode,attribute)	rins->GetAttribute(installationmode,attribute)
#define rins_IsAvailable(installationmode,attribute)	rins->IsAvailable(installationmode,attribute)
#define rins_ResetAttributeToDefault(installationmode,attribute)	rins->ResetAttributeToDefault(installationmode,attribute)
#define rins_ResetAttributeToPersistent(installationmode,attribute)	rins->ResetAttributeToPersistent(installationmode,attribute)
#define rins_NitNone	IHsvInstallation2_NitNone
#define rins_NitActual	IHsvInstallation2_NitActual
#define rins_NitOther	IHsvInstallation2_NitOther
#define rins_GetTargetNitType(NetworkId)	rins->GetTargetNitType(NetworkId)
#define rins_IsNetworkUpdateDetected()	rins->IsNetworkUpdateDetected()
#define rins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define rins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define rins_Initialise()	rins->Initialise()
#define rins_SkipInstallationScans(ScanTypes)	rins->SkipInstallationScans(ScanTypes)
#define rins_GetAltTSValues(ONID,TSID)	rins->GetAltTSValues(ONID,TSID)
#define rins_SetUserSymbolRates(installationmode,values,len)	rins->SetUserSymbolRates(installationmode,values,len)
#define rins_GetUserSymbolRates(installationmode,values,len)	rins->GetUserSymbolRates(installationmode,values,len)
#define rins_GetPredefinedSymbolRates(installationmode,values,len)	rins->GetPredefinedSymbolRates(installationmode,values,len)
#define rins_GetNetworkIDList()	rins->GetNetworkIDList()
#define rins_GetNetworkIDName(index,NetworkName)	rins->GetNetworkIDName(index,NetworkName)
#define rins_SetFavouriteNetworkID(mode,attrib,index)	rins->SetFavouriteNetworkID(mode,attrib,index)
#define rins_SetFavouriteRegion(mode,index,RegionType)	rins->SetFavouriteRegion(mode,index,RegionType)
#define rins_None	IHsvInstallation2_None
#define rins_Ziggo	IHsvInstallation2_Ziggo
#define rins_UPC	IHsvInstallation2_UPC
#define rins_UnityMedia	IHsvInstallation2_UnityMedia
#define rins_Kdg	IHsvInstallation2_Kdg
#define rins_Telenet	IHsvInstallation2_Telenet
#define rins_RCSRDS	IHsvInstallation2_RCSRDS
#define rins_SetUserSelectConflictService(LcnIndex,SvcIndex)	rins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define rins_ConflictsSelectionDone(UserSelection)	rins->ConflictsSelectionDone(UserSelection)
#define rins_GetConflictServices(ConflictList,NumRecords)	rins->GetConflictServices(ConflictList,NumRecords)
#define rins_GetInstallationVersion()	rins->GetInstallationVersion()
#define rins_GetInstallationState()	rins->GetInstallationState()
#define rins_GetPLPIds(PLPIds)	rins->GetPLPIds(PLPIds)
#define rins_GetRegionList(RegionsData)	rins->GetRegionList(RegionsData)
#define rins_UserSelectionDone(UserSelection)	rins->UserSelectionDone(UserSelection)
#define rins_GetFavouriteRegion(mode,RegionType)	rins->GetFavouriteRegion(mode,RegionType)
#define rins_GetStreamPriority()	rins->GetStreamPriority()
#define rins_SetStreamPriority(prio)	rins->SetStreamPriority(prio)
#define rins_GetConstellation()	rins->GetConstellation()
#define rins_GetSymbolRate()	rins->GetSymbolRate()
#define rins_GetHierarchyMode()	rins->GetHierarchyMode()
#define rins_GetEpgBarkerMux(OnId,TsId)	rins->GetEpgBarkerMux(OnId,TsId)
#define rins_ZiggoNetworkDataSet(ActionValue)	rins->ZiggoNetworkDataSet(ActionValue)
#define rins_ClearPersistent()	rins->ClearPersistent()
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
#define ifullN_EventScanStopped	IHsvDigitalScanNotify_EventScanStopped
#define ifullN_EventScanCompleted	IHsvDigitalScanNotify_EventScanCompleted
#define ifullN_EventScanFailed	IHsvDigitalScanNotify_EventScanFailed
#define ifullN_EventTargetNITFound	IHsvDigitalScanNotify_EventTargetNITFound
#define igridN_EventScanStopped	IHsvDigitalScanNotify_EventScanStopped
#define igridN_EventScanCompleted	IHsvDigitalScanNotify_EventScanCompleted
#define igridN_EventScanFailed	IHsvDigitalScanNotify_EventScanFailed
#define igridN_EventTargetNITFound	IHsvDigitalScanNotify_EventTargetNITFound
#define ins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define ins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define ins_StIdle	IHsvInstallation2_StIdle
#define ins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define ins_StDigital	IHsvInstallation2_StDigital
#define ins_StAnalog	IHsvInstallation2_StAnalog
#define ins_StPreSorting	IHsvInstallation2_StPreSorting
#define ins_StSorting	IHsvInstallation2_StSorting
#define ins_Terrestrial	IHsvInstallation2_Terrestrial
#define ins_Cable	IHsvInstallation2_Cable
#define ins_Satellite	IHsvInstallation2_Satellite
#define ins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define ins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define ins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define ins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define ins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define ins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define ins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define ins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define ins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define ins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define ins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define ins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define ins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define ins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define ins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define ins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define ins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define ins_MaxChannel	IHsvInstallation2_MaxChannel
#define ins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define ins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define ins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define ins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define ins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define ins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define ins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define ins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define ins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define ins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define ins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define ins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define ins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define ins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define ins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define ins_InsAssm	IHsvInstallation2_InsAssm
#define ins_InsVssm	IHsvInstallation2_InsVssm
#define ins_InsQssm	IHsvInstallation2_InsQssm
#define ins_InsSssm	IHsvInstallation2_InsSssm
#define ins_ScanNone	IHsvInstallation2_ScanNone
#define ins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define ins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define ins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define ins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define ins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define ins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define ins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define ins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define ins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define ins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define ins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define ins_AttributeCity	IHsvInstallation2_AttributeCity
#define ins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define ins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define ins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define ins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define ins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define ins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define ins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define ins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define ins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define ins_QuickScan	IHsvInstallation2_QuickScan
#define ins_FullScan	IHsvInstallation2_FullScan
#define ins_GridScan	IHsvInstallation2_GridScan
#define ins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define ins_ManualValue	IHsvInstallation2_ManualValue
#define ins_NitNone	IHsvInstallation2_NitNone
#define ins_NitActual	IHsvInstallation2_NitActual
#define ins_NitOther	IHsvInstallation2_NitOther
#define ins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define ins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define ins_None	IHsvInstallation2_None
#define ins_Ziggo	IHsvInstallation2_Ziggo
#define ins_UPC	IHsvInstallation2_UPC
#define ins_UnityMedia	IHsvInstallation2_UnityMedia
#define ins_Kdg	IHsvInstallation2_Kdg
#define ins_Telenet	IHsvInstallation2_Telenet
#define ins_RCSRDS	IHsvInstallation2_RCSRDS
#define rins_GetChannelListIDName(index,ChannelistName)	rins->GetChannelListIDName(index,ChannelistName)
#define rins_GetNumberOfChannelListIds()	rins->GetNumberOfChannelListIds()
#define rins_GetChannelListIdByIndex(index)	rins->GetChannelListIdByIndex(index)
#define rins_SetFavouriteChannelListId(mode,attrib,index)	rins->SetFavouriteChannelListId(mode,attrib,index)
#define iprescanN_EventScanStopped	IHsvDigitalScanNotify_EventScanStopped
#define iprescanN_EventScanCompleted	IHsvDigitalScanNotify_EventScanCompleted
#define iprescanN_EventScanFailed	IHsvDigitalScanNotify_EventScanFailed
#define iprescanN_EventTargetNITFound	IHsvDigitalScanNotify_EventTargetNITFound
#define iquickN_EventScanStopped	IHsvDigitalScanNotify_EventScanStopped
#define iquickN_EventScanCompleted	IHsvDigitalScanNotify_EventScanCompleted
#define iquickN_EventScanFailed	IHsvDigitalScanNotify_EventScanFailed
#define iquickN_EventTargetNITFound	IHsvDigitalScanNotify_EventTargetNITFound
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

