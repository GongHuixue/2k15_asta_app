#ifndef  _CHSVDVBTDT_PRIV_H
#define  _CHSVDVBTDT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvComponentIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvDateTimeConversion.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallation2.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <CTCMwBase.h>
class CHsvDvbTDT_Priv;
#define CLASSSCOPE CHsvDvbTDT_Priv::
#include "locals_m.h"

class CHsvDvbTDT_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbTDT_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbTDT_Priv,dmxsecfN);
IHsvSdmEnableImpl(CHsvDvbTDT_Priv,ena);
IHsvPowerImpl(CHsvDvbTDT_Priv,pow);
IHsvStreamImpl(CHsvDvbTDT_Priv,strapi);
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

//Required interfaces
public:
RequiresInterface<IHsvComponentIds>	compids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvDateTimeConversion>	dtconv;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
private:
DEMUX_DEFINES(CHsvDvbTDT_Priv,sec);

public:
CHsvDvbTDT_Priv():i__dmxsecfN(this),i__ena(this),i__pow(this),i__strapi(this)
{
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
pow	=	&i__pow;
strapi	=	&i__strapi;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define compids_iPresent() (compids.Present())
#define compids_hsvcc708dec	IHsvComponentIds_hsvcc708dec
#define compids_hsvatscsdm	IHsvComponentIds_hsvatscsdm
#define compids_hsvcc	IHsvComponentIds_hsvcc
#define compids_hsvccdisp	IHsvComponentIds_hsvccdisp
#define compids_hsvcm	IHsvComponentIds_hsvcm
#define compids_hsvdbase	IHsvComponentIds_hsvdbase
#define compids_hsvdmx	IHsvComponentIds_hsvdmx
#define compids_hsvins	IHsvComponentIds_hsvins
#define compids_hsvlocks	IHsvComponentIds_hsvlocks
#define compids_hsvlog	IHsvComponentIds_hsvlog
#define compids_hsvmempool	IHsvComponentIds_hsvmempool
#define compids_hsvmpeg	IHsvComponentIds_hsvmpeg
#define compids_hsvmpl	IHsvComponentIds_hsvmpl
#define compids_hsvpgview	IHsvComponentIds_hsvpgview
#define compids_hsvpsip	IHsvComponentIds_hsvpsip
#define compids_hsvsel	IHsvComponentIds_hsvsel
#define compids_hsvsrttable	IHsvComponentIds_hsvsrttable
#define compids_hsvunsrttable	IHsvComponentIds_hsvunsrttable
#define compids_hsvl21dc	IHsvComponentIds_hsvl21dc
#define compids_hsveuins	IHsvComponentIds_hsveuins
#define compids_hsveursel	IHsvComponentIds_hsveursel
#define compids_hsvdvbsdm	IHsvComponentIds_hsvdvbsdm
#define compids_hsvprins	IHsvComponentIds_hsvprins
#define compids_NumComponents	IHsvComponentIds_NumComponents
#define conf_iPresent() (conf.Present())
#define conf_NitActualParsing	IHsvDVBSIConfig_NitActualParsing
#define conf_NitOtherParsing	IHsvDVBSIConfig_NitOtherParsing
#define conf_SdtActualParsing	IHsvDVBSIConfig_SdtActualParsing
#define conf_SdtOtherParsing	IHsvDVBSIConfig_SdtOtherParsing
#define conf_EitNowNextActualParsing	IHsvDVBSIConfig_EitNowNextActualParsing
#define conf_EitNowNextOtherParsing	IHsvDVBSIConfig_EitNowNextOtherParsing
#define conf_EitSchedActualParsing	IHsvDVBSIConfig_EitSchedActualParsing
#define conf_EitSchedOtherParsing	IHsvDVBSIConfig_EitSchedOtherParsing
#define conf_TdtParsing	IHsvDVBSIConfig_TdtParsing
#define conf_TotParsing	IHsvDVBSIConfig_TotParsing
#define conf_Notifications	IHsvDVBSIConfig_Notifications
#define conf_CurrentCountry	conf->CurrentCountry()
#define conf_IsActionAllowed(dmx,table)	conf->IsActionAllowed(dmx,table)
#define dtconv_iPresent() (dtconv.Present())
#define dtconv_DecodeMJD(date,year,month,day)	dtconv->DecodeMJD(date,year,month,day)
#define dtconv_EncodeDataTime(Date,Time,dt)	dtconv->EncodeDataTime(Date,Time,dt)
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
#define ins_iPresent() (ins.Present())
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
#define ins_StartInstallation(source,ptc,mode)	ins->StartInstallation(source,ptc,mode)
#define ins_StopInstallation()	ins->StopInstallation()
#define ins_GetNumberOfAnalogChannelsFound()	ins->GetNumberOfAnalogChannelsFound()
#define ins_GetNumberOfDigitalChannelsFound()	ins->GetNumberOfDigitalChannelsFound()
#define ins_GetNumberOfDigitalChannelsRemoved()	ins->GetNumberOfDigitalChannelsRemoved()
#define ins_GetInstallationProgress()	ins->GetInstallationProgress()
#define ins_GetInstallationStatus()	ins->GetInstallationStatus()
#define ins_GetInstallationMode()	ins->GetInstallationMode()
#define ins_IsUpdateInstallationSupported()	ins->IsUpdateInstallationSupported()
#define ins_SetInstallCountry(country)	ins->SetInstallCountry(country)
#define ins_SetSystemCountry(country)	ins->SetSystemCountry(country)
#define ins_GetFirstIntalledDigitalChannel(channelno)	ins->GetFirstIntalledDigitalChannel(channelno)
#define ins_GetFirstIntalledAnalogueChannel(channelno)	ins->GetFirstIntalledAnalogueChannel(channelno)
#define ins_GetFirstIntalledRadioChannel(channelno)	ins->GetFirstIntalledRadioChannel(channelno)
#define ins_GetFirstInstalledChannel(channelno)	ins->GetFirstInstalledChannel(channelno)
#define ins_GetNetworkNameForNetworkID(networkID,NetworkName)	ins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define ins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	ins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define ins_IsValidNetworkId(networkID)	ins->IsValidNetworkId(networkID)
#define ins_SetLowestNetworkId(networkID)	ins->SetLowestNetworkId(networkID)
#define ins_SetManualFrequency(frequency,offset,finetune)	ins->SetManualFrequency(frequency,offset,finetune)
#define ins_GetManualFrequency(frequency,offset,finetune)	ins->GetManualFrequency(frequency,offset,finetune)
#define ins_SetManualChannel(channel,finetune)	ins->SetManualChannel(channel,finetune)
#define ins_GetManualChannel(channel,finetune)	ins->GetManualChannel(channel,finetune)
#define ins_IsManualInstallationModeSupported(mode)	ins->IsManualInstallationModeSupported(mode)
#define ins_SetManualInstallationMode(mode)	ins->SetManualInstallationMode(mode)
#define ins_GetManualInstallationMode()	ins->GetManualInstallationMode()
#define ins_StoreManualInstallationValues(channel)	ins->StoreManualInstallationValues(channel)
#define ins_AutoStoreManualInstallationValues()	ins->AutoStoreManualInstallationValues()
#define ins_StartFrequencySearch()	ins->StartFrequencySearch()
#define ins_GetSigStrengthRange(measmode,min,max)	ins->GetSigStrengthRange(measmode,min,max)
#define ins_GetSignalstrength(measmode)	ins->GetSignalstrength(measmode)
#define ins_StoreWeakSignalInstallationChannel()	ins->StoreWeakSignalInstallationChannel()
#define ins_GetInstalledWeakSignalChannel()	ins->GetInstalledWeakSignalChannel()
#define ins_GetSignalQualityBer()	ins->GetSignalQualityBer()
#define ins_IsFrequencySearchDirectionSupported(searchup)	ins->IsFrequencySearchDirectionSupported(searchup)
#define ins_SetFrequencySearchDirection(searchup)	ins->SetFrequencySearchDirection(searchup)
#define ins_GetFrequencySearchDirection()	ins->GetFrequencySearchDirection()
#define ins_GetMinFrequency()	ins->GetMinFrequency()
#define ins_GetMaxFrequency()	ins->GetMaxFrequency()
#define ins_GetTunerFrequency()	ins->GetTunerFrequency()
#define ins_SetTunerFrequency(freq,fineTune)	ins->SetTunerFrequency(freq,fineTune)
#define ins_GetFrequency2Channel(chantbl,frequency)	ins->GetFrequency2Channel(chantbl,frequency)
#define ins_GetChannel2CarrierFrequency(chantbl,channel)	ins->GetChannel2CarrierFrequency(chantbl,channel)
#define ins_GetChannel2CentreFrequency(chantbl,channel)	ins->GetChannel2CentreFrequency(chantbl,channel)
#define ins_GetCurrentPass()	ins->GetCurrentPass()
#define ins_GetNoOfPass()	ins->GetNoOfPass()
#define ins_GetCurrentPassType()	ins->GetCurrentPassType()
#define ins_IsMediumSupported(medium)	ins->IsMediumSupported(medium)
#define ins_GetMedium()	ins->GetMedium()
#define ins_SetMedium(medium)	ins->SetMedium(medium)
#define ins_GetInstalledMedium()	ins->GetInstalledMedium()
#define ins_SetInstalledMedium(medium)	ins->SetInstalledMedium(medium)
#define ins_IsTvSystemSupported(tvsystem)	ins->IsTvSystemSupported(tvsystem)
#define ins_SetTvSystem(tvsystem)	ins->SetTvSystem(tvsystem)
#define ins_GetTvSystem()	ins->GetTvSystem()
#define ins_IsColorSystemSupported(colorsystem)	ins->IsColorSystemSupported(colorsystem)
#define ins_SetColorSystem(colorsystem)	ins->SetColorSystem(colorsystem)
#define ins_GetColorSystem()	ins->GetColorSystem()
#define ins_IsValidPTC(medium,PTC)	ins->IsValidPTC(medium,PTC)
#define ins_GetMinPTC(medium)	ins->GetMinPTC(medium)
#define ins_GetMaxPTC(medium)	ins->GetMaxPTC(medium)
#define ins_GetLastPTCFound()	ins->GetLastPTCFound()
#define ins_GetNumberOfPTCsFound()	ins->GetNumberOfPTCsFound()
#define ins_StartSigStrMeas(measmode)	ins->StartSigStrMeas(measmode)
#define ins_StopSigStrMeas(measmode)	ins->StopSigStrMeas(measmode)
#define ins_IsSignalStrengthMeasurementValid(measmode)	ins->IsSignalStrengthMeasurementValid(measmode)
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
#define ins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	ins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define ins_SetAttributeMode(installationmode,attribute,attributeMode)	ins->SetAttributeMode(installationmode,attribute,attributeMode)
#define ins_SetAttribute(installationmode,attribute,value)	ins->SetAttribute(installationmode,attribute,value)
#define ins_GetAttributeMode(installationmode,attribute)	ins->GetAttributeMode(installationmode,attribute)
#define ins_GetAttribute(installationmode,attribute)	ins->GetAttribute(installationmode,attribute)
#define ins_IsAvailable(installationmode,attribute)	ins->IsAvailable(installationmode,attribute)
#define ins_ResetAttributeToDefault(installationmode,attribute)	ins->ResetAttributeToDefault(installationmode,attribute)
#define ins_ResetAttributeToPersistent(installationmode,attribute)	ins->ResetAttributeToPersistent(installationmode,attribute)
#define ins_NitNone	IHsvInstallation2_NitNone
#define ins_NitActual	IHsvInstallation2_NitActual
#define ins_NitOther	IHsvInstallation2_NitOther
#define ins_GetTargetNitType(NetworkId)	ins->GetTargetNitType(NetworkId)
#define ins_IsNetworkUpdateDetected()	ins->IsNetworkUpdateDetected()
#define ins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define ins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define ins_Initialise()	ins->Initialise()
#define ins_SkipInstallationScans(ScanTypes)	ins->SkipInstallationScans(ScanTypes)
#define ins_GetAltTSValues(ONID,TSID)	ins->GetAltTSValues(ONID,TSID)
#define ins_SetUserSymbolRates(installationmode,values,len)	ins->SetUserSymbolRates(installationmode,values,len)
#define ins_GetUserSymbolRates(installationmode,values,len)	ins->GetUserSymbolRates(installationmode,values,len)
#define ins_GetPredefinedSymbolRates(installationmode,values,len)	ins->GetPredefinedSymbolRates(installationmode,values,len)
#define ins_GetNetworkIDList()	ins->GetNetworkIDList()
#define ins_GetNetworkIDName(index,NetworkName)	ins->GetNetworkIDName(index,NetworkName)
#define ins_GetChannelListIDName(index,ChannelistName)	ins->GetChannelListIDName(index,ChannelistName)
#define ins_SetFavouriteNetworkID(mode,attrib,index)	ins->SetFavouriteNetworkID(mode,attrib,index)
#define ins_SetFavouriteRegion(mode,index,RegionType)	ins->SetFavouriteRegion(mode,index,RegionType)
#define ins_None	IHsvInstallation2_None
#define ins_Ziggo	IHsvInstallation2_Ziggo
#define ins_UPC	IHsvInstallation2_UPC
#define ins_UnityMedia	IHsvInstallation2_UnityMedia
#define ins_Kdg	IHsvInstallation2_Kdg
#define ins_Telenet	IHsvInstallation2_Telenet
#define ins_RCSRDS	IHsvInstallation2_RCSRDS
#define ins_SetUserSelectConflictService(LcnIndex,SvcIndex)	ins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define ins_ConflictsSelectionDone(UserSelection)	ins->ConflictsSelectionDone(UserSelection)
#define ins_GetConflictServices(ConflictList,NumRecords)	ins->GetConflictServices(ConflictList,NumRecords)
#define ins_GetInstallationVersion()	ins->GetInstallationVersion()
#define ins_GetInstallationState()	ins->GetInstallationState()
#define ins_GetPLPIds(PLPIds)	ins->GetPLPIds(PLPIds)
#define ins_GetRegionList(RegionsData)	ins->GetRegionList(RegionsData)
#define ins_UserSelectionDone(UserSelection)	ins->UserSelectionDone(UserSelection)
#define ins_GetFavouriteRegion(mode,RegionType)	ins->GetFavouriteRegion(mode,RegionType)
#define ins_GetStreamPriority()	ins->GetStreamPriority()
#define ins_SetStreamPriority(prio)	ins->SetStreamPriority(prio)
#define ins_GetConstellation()	ins->GetConstellation()
#define ins_GetSymbolRate()	ins->GetSymbolRate()
#define ins_GetHierarchyMode()	ins->GetHierarchyMode()
#define ins_GetEpgBarkerMux(OnId,TsId)	ins->GetEpgBarkerMux(OnId,TsId)
#define ins_ZiggoNetworkDataSet(ActionValue)	ins->ZiggoNetworkDataSet(ActionValue)
#define ins_ClearPersistent()	ins->ClearPersistent()
#define sec_iPresent() (sec.Present())
#define sec_SctArrived	IHsvDemuxSectionFilter2_SctArrived
#define sec_TableCompleted	IHsvDemuxSectionFilter2_TableCompleted
#define sec_SectionDepth	sec->SectionDepth()
#define sec_IsRequestAllowed(dest)	sec->IsRequestAllowed(dest)
#define sec_RequestSection(dest,pid,tableid,cookie,sctCallback)	sec->RequestSection(dest,pid,tableid,cookie,sctCallback)
#define sec_RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback)	sec->RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback)
#define sec_RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback)	sec->RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback)
#define sec_ResetRequest(dest,subscrId)	sec->ResetRequest(dest,subscrId)
#define sec_CancelSection(dest,subscrId)	sec->CancelSection(dest,subscrId)
#define sec_RequestPes(dest,pid,cookie,pesCallback)	sec->RequestPes(dest,pid,cookie,pesCallback)
#define sec_CancelPes(dest,subscrId)	sec->CancelPes(dest,subscrId)
#define sec_RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)	sec->RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)
#define sec_UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray)	sec->UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray)
#define sec_RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)	sec->RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)
#define sec_RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength)	sec->RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength)
#define sec_GetBits(sectionid,numbits)	sec->GetBits(sectionid,numbits)
#define sec_ShowBits(sectionid,numbits)	sec->ShowBits(sectionid,numbits)
#define sec_SkipBits(sectionid,numbits)	sec->SkipBits(sectionid,numbits)
#define sec_AlignToNextByte(sectionid)	sec->AlignToNextByte(sectionid)
#define sec_IsEndOfSection(sectionid)	sec->IsEndOfSection(sectionid)
#define sec_GetBitsRead(sectionid)	sec->GetBitsRead(sectionid)
#define sec_GetBitsUnread(sectionid)	sec->GetBitsUnread(sectionid)
#define sec_GetSectionBuffer(sectionid)	sec->GetSectionBuffer(sectionid)
#define sec_GetSectionLength(sectionid)	sec->GetSectionLength(sectionid)
#define sec_CheckandCancelSection(dest,PidValue)	sec->CheckandCancelSection(dest,PidValue)
#ifdef sec_RequestSectionFilter
#undef sec_RequestSectionFilter
#endif
#ifdef sec_RequestSectionFilterList
#undef sec_RequestSectionFilterList
#endif
#ifdef sec_RequestSection
#undef sec_RequestSection
#endif
#ifdef sec_RequestSection2
#undef sec_RequestSection2
#endif
#ifdef sec_RequestSection3
#undef sec_RequestSection3
#endif
#ifdef sec_RequestPes
#undef sec_RequestPes
#endif
#ifdef sec_RequestPesList
#undef sec_RequestPesList
#endif
#ifdef sec_CancelSection
#undef sec_CancelSection
#endif
#ifdef sec_CancelPes
#undef sec_CancelPes
#endif
#define sec_RequestSectionFilter dmxlocal_RequestSectionFilter
#define sec_RequestSectionFilterList dmxlocal_RequestSectionFilterList
#define sec_RequestSection dmxlocal_RequestSection
#define sec_RequestSection2 dmxlocal_RequestSection2
#define sec_RequestSection3 dmxlocal_RequestSection3
#define sec_RequestPes dmxlocal_RequestPes
#define sec_RequestPesList dmxlocal_RequestPesList
#define sec_CancelSection dmxlocal_CancelSection
#define sec_CancelPes dmxlocal_CancelPes
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

