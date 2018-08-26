#ifndef  _CHSVMPEGDATAMANAGER_PRIV_H
#define  _CHSVMPEGDATAMANAGER_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmEnable.h>
#include <IInit.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMpegSections.h>
#include <IHsvMpegServices.h>
#include <IHsvStream.h>
#include <IHsvPower.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvMpegControlNotify.h>
#include <IHsvMpegSectionsNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IRealTimeKernel.h>
#include <IHsvSdmDiv.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <CTCMwBase.h>
class CHsvMpegDataManager_Priv;
#define CLASSSCOPE CHsvMpegDataManager_Priv::
#include "locals_m.h"

class CHsvMpegDataManager_Priv : public CTCMwBase
{
public:
virtual ~CHsvMpegDataManager_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,audioinfoconfaux);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,audioinfoconfmain);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,basicpidinfoconfaux);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,basicpidinfoconfmain);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,componenttaginfoaux);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,componenttaginfomain);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,databroadcastinfoaux);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,databroadcastinfomain);
IHsvSdmEnableImpl(CHsvMpegDataManager_Priv,enable);
IInitImpl(CHsvMpegDataManager_Priv,init);
IHsvLanguageIds2Impl(CHsvMpegDataManager_Priv,langids);
IHsvMpegSectionsImpl(CHsvMpegDataManager_Priv,mpegsecn);
IHsvMpegServicesImpl(CHsvMpegDataManager_Priv,mpegserv);
IHsvStreamImpl(CHsvMpegDataManager_Priv,patstrapi);
IHsvStreamImpl(CHsvMpegDataManager_Priv,pmtstrapi);
IHsvPowerImpl(CHsvMpegDataManager_Priv,pow);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,subtitleconfaux);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,subtitleconfmain);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,teletextconfaux);
IHsvSortedTableConfigurationExImpl(CHsvMpegDataManager_Priv,teletextconfmain);
public:
ProvidesInterface<IHsvSortedTableConfigurationEx>	audioinfoconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	audioinfoconfmain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	basicpidinfoconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	basicpidinfoconfmain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	componenttaginfoaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	componenttaginfomain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	databroadcastinfoaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	databroadcastinfomain;

ProvidesInterface<IHsvSdmEnable>	enable;

ProvidesInterface<IInit>	init;

ProvidesInterface<IHsvLanguageIds2>	langids;

ProvidesInterface<IHsvMpegSections>	mpegsecn;

ProvidesInterface<IHsvMpegServices>	mpegserv;

ProvidesInterface<IHsvStream>	patstrapi;

ProvidesInterface<IHsvStream>	pmtstrapi;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSortedTableConfigurationEx>	subtitleconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	subtitleconfmain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	teletextconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	teletextconfmain;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvMpegControlNotify>	mpegN;
RequiresInterface<IHsvMpegSectionsNotify>	mpegsecnN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSdmDiv>	sdmdiv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
private:
Pumpdefines(CHsvMpegDataManager_Priv);
DEMUX_DEFINES(CHsvMpegDataManager_Priv,sec);

public:
CHsvMpegDataManager_Priv():i__audioinfoconfaux(this),i__audioinfoconfmain(this),i__basicpidinfoconfaux(this),i__basicpidinfoconfmain(this),i__componenttaginfoaux(this),i__componenttaginfomain(this),i__databroadcastinfoaux(this),i__databroadcastinfomain(this),i__enable(this),i__init(this),i__langids(this),i__mpegsecn(this),i__mpegserv(this),i__patstrapi(this),i__pmtstrapi(this),i__pow(this),i__subtitleconfaux(this),i__subtitleconfmain(this),i__teletextconfaux(this),i__teletextconfmain(this)
{
audioinfoconfaux	=	&i__audioinfoconfaux;
audioinfoconfmain	=	&i__audioinfoconfmain;
basicpidinfoconfaux	=	&i__basicpidinfoconfaux;
basicpidinfoconfmain	=	&i__basicpidinfoconfmain;
componenttaginfoaux	=	&i__componenttaginfoaux;
componenttaginfomain	=	&i__componenttaginfomain;
databroadcastinfoaux	=	&i__databroadcastinfoaux;
databroadcastinfomain	=	&i__databroadcastinfomain;
enable	=	&i__enable;
init	=	&i__init;
langids	=	&i__langids;
mpegsecn	=	&i__mpegsecn;
mpegserv	=	&i__mpegserv;
patstrapi	=	&i__patstrapi;
pmtstrapi	=	&i__pmtstrapi;
pow	=	&i__pow;
subtitleconfaux	=	&i__subtitleconfaux;
subtitleconfmain	=	&i__subtitleconfmain;
teletextconfaux	=	&i__teletextconfaux;
teletextconfmain	=	&i__teletextconfmain;
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
#define mpegN_iPresent() (mpegN.Present())
#define mpegN_OnCurrentPmtPidChanged(CurrentPmtPid)	mpegN->OnCurrentPmtPidChanged(CurrentPmtPid)
#define mpegsecnN_iPresent() (mpegsecnN.Present())
#define mpegsecnN_PmtData	IHsvMpegSectionsNotify_PmtData
#define mpegsecnN_PmtAcquisitionComplete	IHsvMpegSectionsNotify_PmtAcquisitionComplete
#define mpegsecnN_OnChanged(dmx,value,eventid)	mpegsecnN->OnChanged(dmx,value,eventid)
#define mpegsecnN_OnAdded(dmx,value,eventid)	mpegsecnN->OnAdded(dmx,value,eventid)
#define mpegsecnN_OnRemoved(dmx,value,eventid)	mpegsecnN->OnRemoved(dmx,value,eventid)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgdat_iPresent() (pgdat.Present())
#define pgdat_BoolLock	IHsvProgramData3_BoolLock
#define pgdat_BoolFavorite	IHsvProgramData3_BoolFavorite
#define pgdat_BoolFavorite1	IHsvProgramData3_BoolFavorite1
#define pgdat_BoolFavorite2	IHsvProgramData3_BoolFavorite2
#define pgdat_BoolFavorite3	IHsvProgramData3_BoolFavorite3
#define pgdat_BoolPreferredFavorite	IHsvProgramData3_BoolPreferredFavorite
#define pgdat_BoolPreferredNicam	IHsvProgramData3_BoolPreferredNicam
#define pgdat_BoolPreferredStereo	IHsvProgramData3_BoolPreferredStereo
#define pgdat_BoolSAP	IHsvProgramData3_BoolSAP
#define pgdat_BoolHMProtectedChannel	IHsvProgramData3_BoolHMProtectedChannel
#define pgdat_BoolHMBlanked	IHsvProgramData3_BoolHMBlanked
#define pgdat_BoolUserHidden	IHsvProgramData3_BoolUserHidden
#define pgdat_BoolSystemHidden	IHsvProgramData3_BoolSystemHidden
#define pgdat_BoolNumericSelect	IHsvProgramData3_BoolNumericSelect
#define pgdat_BoolEpgChannel	IHsvProgramData3_BoolEpgChannel
#define pgdat_BoolEPGShortInfoEnabled	IHsvProgramData3_BoolEPGShortInfoEnabled
#define pgdat_BoolNewPreset	IHsvProgramData3_BoolNewPreset
#define pgdat_BoolFreeCiMode	IHsvProgramData3_BoolFreeCiMode
#define pgdat_BoolTuned	IHsvProgramData3_BoolTuned
#define pgdat_BoolDeTuned	IHsvProgramData3_BoolDeTuned
#define pgdat_BoolAttenuator	IHsvProgramData3_BoolAttenuator
#define pgdat_BoolAgcInstalled	IHsvProgramData3_BoolAgcInstalled
#define pgdat_BoolChannelVirgin	IHsvProgramData3_BoolChannelVirgin
#define pgdat_BoolUpdateName	IHsvProgramData3_BoolUpdateName
#define pgdat_IntDeltaVolume	IHsvProgramData3_IntDeltaVolume
#define pgdat_Nat32DateStamp	IHsvProgramData3_Nat32DateStamp
#define pgdat_Nat32AppsCookie	IHsvProgramData3_Nat32AppsCookie
#define pgdat_Nat32TxtCookie	IHsvProgramData3_Nat32TxtCookie
#define pgdat_Nat32CesvcCookie	IHsvProgramData3_Nat32CesvcCookie
#define pgdat_Nat32DvbType	IHsvProgramData3_Nat32DvbType
#define pgdat_StringChannelName	IHsvProgramData3_StringChannelName
#define pgdat_StringExtChannelName	IHsvProgramData3_StringExtChannelName
#define pgdat_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat_IntTvSystem	IHsvProgramData3_IntTvSystem
#define pgdat_IntModulation	IHsvProgramData3_IntModulation
#define pgdat_IntNewChannelMap	IHsvProgramData3_IntNewChannelMap
#define pgdat_IntSignalStrength	IHsvProgramData3_IntSignalStrength
#define pgdat_IntSignalQuality	IHsvProgramData3_IntSignalQuality
#define pgdat_IntColoursystem	IHsvProgramData3_IntColoursystem
#define pgdat_IntDecoderType	IHsvProgramData3_IntDecoderType
#define pgdat_IntFineTuneOffset	IHsvProgramData3_IntFineTuneOffset
#define pgdat_IntFineTuneFrequency	IHsvProgramData3_IntFineTuneFrequency
#define pgdat_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat_IntNetworkId	IHsvProgramData3_IntNetworkId
#define pgdat_IntOriginalNwId	IHsvProgramData3_IntOriginalNwId
#define pgdat_IntTsid	IHsvProgramData3_IntTsid
#define pgdat_IntServiceId	IHsvProgramData3_IntServiceId
#define pgdat_IntServiceType	IHsvProgramData3_IntServiceType
#define pgdat_IntPmtPid	IHsvProgramData3_IntPmtPid
#define pgdat_IntPcrPid	IHsvProgramData3_IntPcrPid
#define pgdat_IntVideoPid	IHsvProgramData3_IntVideoPid
#define pgdat_IntVideoStreamType	IHsvProgramData3_IntVideoStreamType
#define pgdat_IntAudioPid	IHsvProgramData3_IntAudioPid
#define pgdat_IntAudioStreamType	IHsvProgramData3_IntAudioStreamType
#define pgdat_IntSecAudioPid	IHsvProgramData3_IntSecAudioPid
#define pgdat_IntSecAudioStreamType	IHsvProgramData3_IntSecAudioStreamType
#define pgdat_IntInstallMode	IHsvProgramData3_IntInstallMode
#define pgdat_IntCniNi	IHsvProgramData3_IntCniNi
#define pgdat_IntDataIndicator	IHsvProgramData3_IntDataIndicator
#define pgdat_IntPresetNumber	IHsvProgramData3_IntPresetNumber
#define pgdat_IntModulationType	IHsvProgramData3_IntModulationType
#define pgdat_IntLCN	IHsvProgramData3_IntLCN
#define pgdat_IntStreamPriority	IHsvProgramData3_IntStreamPriority
#define pgdat_IntHMMapChannelNo	IHsvProgramData3_IntHMMapChannelNo
#define pgdat_IntPtc	IHsvProgramData3_IntPtc
#define pgdat_IntAssociatedDecoder	IHsvProgramData3_IntAssociatedDecoder
#define pgdat_IntChannelBandwidth	IHsvProgramData3_IntChannelBandwidth
#define pgdat_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat_Antenna	IHsvProgramData3_Antenna
#define pgdat_Cable	IHsvProgramData3_Cable
#define pgdat_IntSystemHidden	IHsvProgramData3_IntSystemHidden
#define pgdat_IntNumericSelect	IHsvProgramData3_IntNumericSelect
#define pgdat_IntNewChannel	IHsvProgramData3_IntNewChannel
#define pgdat_StringSatelliteName	IHsvProgramData3_StringSatelliteName
#define pgdat_IntSrcambledStatus	IHsvProgramData3_IntSrcambledStatus
#define pgdat_IntInstalledSatelliteNumber	IHsvProgramData3_IntInstalledSatelliteNumber
#define pgdat_IntUserHidden	IHsvProgramData3_IntUserHidden
#define pgdat_FavoriteNumber	IHsvProgramData3_FavoriteNumber
#define pgdat_FavoriteNumber1	IHsvProgramData3_FavoriteNumber1
#define pgdat_FavoriteNumber2	IHsvProgramData3_FavoriteNumber2
#define pgdat_FavoriteNumber3	IHsvProgramData3_FavoriteNumber3
#define pgdat_IntEPGEnabled	IHsvProgramData3_IntEPGEnabled
#define pgdat_IntHbbTvOption	IHsvProgramData3_IntHbbTvOption
#define pgdat_BoolChannelLock	IHsvProgramData3_BoolChannelLock
#define pgdat_StringTxtPages	IHsvProgramData3_StringTxtPages
#define pgdat_IntLogoURL	IHsvProgramData3_IntLogoURL
#define pgdat_BoolMatchBrandFlag	IHsvProgramData3_BoolMatchBrandFlag
#define pgdat_Nat32NumBrandIds	IHsvProgramData3_Nat32NumBrandIds
#define pgdat_StringBrandIds	IHsvProgramData3_StringBrandIds
#define pgdat_Nat16PrimaryRegion	IHsvProgramData3_Nat16PrimaryRegion
#define pgdat_Nat16SecondaryRegion	IHsvProgramData3_Nat16SecondaryRegion
#define pgdat_IntTertiaryRegion	IHsvProgramData3_IntTertiaryRegion
#define pgdat_Nat32CountryCode	IHsvProgramData3_Nat32CountryCode
#define pgdat_Nat64UniqueNodeId	IHsvProgramData3_Nat64UniqueNodeId
#define pgdat_BoolUserModifiedLogo	IHsvProgramData3_BoolUserModifiedLogo
#define pgdat_MultipleLCN	IHsvProgramData3_MultipleLCN
#define pgdat_MultiplePreset	IHsvProgramData3_MultiplePreset
#define pgdat_IsValidChannel(channel)	pgdat->IsValidChannel(channel)
#define pgdat_IsChannelInstalled(channel)	pgdat->IsChannelInstalled(channel)
#define pgdat_IsAttributeSupported(attribute)	pgdat->IsAttributeSupported(attribute)
#define pgdat_ClearCurrentTable()	pgdat->ClearCurrentTable()
#define pgdat_ClearAllTables()	pgdat->ClearAllTables()
#define pgdat_GetChannelDataBool(channel,dataid,value)	pgdat->GetChannelDataBool(channel,dataid,value)
#define pgdat_GetChannelDataInt(channel,dataid,value)	pgdat->GetChannelDataInt(channel,dataid,value)
#define pgdat_GetChannelDataNat32(channel,dataid,value)	pgdat->GetChannelDataNat32(channel,dataid,value)
#define pgdat_GetChannelDataString(channel,dataid,value,size)	pgdat->GetChannelDataString(channel,dataid,value,size)
#define pgdat_StoreChannelDataBool(channel,dataid,value)	pgdat->StoreChannelDataBool(channel,dataid,value)
#define pgdat_StoreChannelDataInt(channel,dataid,value)	pgdat->StoreChannelDataInt(channel,dataid,value)
#define pgdat_StoreChannelDataNat32(channel,dataid,value)	pgdat->StoreChannelDataNat32(channel,dataid,value)
#define pgdat_StoreChannelDataString(channel,dataid,value,size)	pgdat->StoreChannelDataString(channel,dataid,value,size)
#define pgdat_GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)	pgdat->GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)
#define pgdat_SwapChannels(channel1,channel2)	pgdat->SwapChannels(channel1,channel2)
#define pgdat_LoadChannelTable(dir)	pgdat->LoadChannelTable(dir)
#define pgdat_SaveChannelTable(dir)	pgdat->SaveChannelTable(dir)
#define pgdat_ReorderChannels(channel1,channel2,Swap)	pgdat->ReorderChannels(channel1,channel2,Swap)
#define pgdat_LoadChannelTableFromMedium(dir,medium)	pgdat->LoadChannelTableFromMedium(dir,medium)
#define pgdat_SaveChannelTableToMedium(dir,medium)	pgdat->SaveChannelTableToMedium(dir,medium)
#define pgdat_GetMediumFromTable(dir,medium)	pgdat->GetMediumFromTable(dir,medium)
#define pgdat_GetNoOfBarkerMultiplexes(NoOfMuxes)	pgdat->GetNoOfBarkerMultiplexes(NoOfMuxes)
#define pgdat_GetBarkerMultiplexByIndex(index,muxes)	pgdat->GetBarkerMultiplexByIndex(index,muxes)
#define pgdat_ReArrangeChannels(channel1,channel2)	pgdat->ReArrangeChannels(channel1,channel2)
#define pgdat_GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)	pgdat->GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)
#define pgdat_GetOperator(OperatorId)	pgdat->GetOperator(OperatorId)
#define pgdat_StoreChannelDataNat64(channel,dataid,value)	pgdat->StoreChannelDataNat64(channel,dataid,value)
#define pgdat_GetChannelDataNat64(channel,dataid,value)	pgdat->GetChannelDataNat64(channel,dataid,value)
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
#define pgsel_TvSystem	IHsvProgramSelection2_TvSystem
#define pgsel_AudioPid	IHsvProgramSelection2_AudioPid
#define pgsel_VideoPid	IHsvProgramSelection2_VideoPid
#define pgsel_PcrPid	IHsvProgramSelection2_PcrPid
#define pgsel_ProgramNumber	IHsvProgramSelection2_ProgramNumber
#define pgsel_SymbolRate	IHsvProgramSelection2_SymbolRate
#define pgsel_DecoderType	IHsvProgramSelection2_DecoderType
#define pgsel_InvalidAttribute	IHsvProgramSelection2_InvalidAttribute
#define pgsel_SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority)	pgsel->SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority)
#define pgsel_GetCurrentProgram(Dest,Source,ChannelNo)	pgsel->GetCurrentProgram(Dest,Source,ChannelNo)
#define pgsel_GetActualCurrentProgram(Dest,Source,ChannelNo)	pgsel->GetActualCurrentProgram(Dest,Source,ChannelNo)
#define pgsel_IsSelectionAllowed(Source,ChannelNo,Dest)	pgsel->IsSelectionAllowed(Source,ChannelNo,Dest)
#define pgsel_IsSelectionInProgress()	pgsel->IsSelectionInProgress()
#define pgsel_GetLastRequestedProgram(Dest,Source,ChannelNo)	pgsel->GetLastRequestedProgram(Dest,Source,ChannelNo)
#define pgsel_GetLastActualRequestedProgram(Dest,Source,ChannelNo)	pgsel->GetLastActualRequestedProgram(Dest,Source,ChannelNo)
#define pgsel_IsAssociationAllowed(Source,AssociationSource)	pgsel->IsAssociationAllowed(Source,AssociationSource)
#define pgsel_SetAssociation(Source,AssociationSource)	pgsel->SetAssociation(Source,AssociationSource)
#define pgsel_GetAssociation(Source)	pgsel->GetAssociation(Source)
#define pgsel_EnableAllExtensionBreakIn(enable)	pgsel->EnableAllExtensionBreakIn(enable)
#define pgsel_IsAllExtensionBreakInEnabled()	pgsel->IsAllExtensionBreakInEnabled()
#define pgsel_EnableExtensionBreakIn(ext,enable)	pgsel->EnableExtensionBreakIn(ext,enable)
#define pgsel_IsExtensionBreakInEnabled(ext)	pgsel->IsExtensionBreakInEnabled(ext)
#define pgsel_EnableBreakInHistory(enable)	pgsel->EnableBreakInHistory(enable)
#define pgsel_IsBreakInHistoryEnabled()	pgsel->IsBreakInHistoryEnabled()
#define pgsel_ClearBreakInStack()	pgsel->ClearBreakInStack()
#define pgsel_IsBreakInStackEmpty()	pgsel->IsBreakInStackEmpty()
#define pgsel_GetBreakInSourceByIndex(index,BreakInSource)	pgsel->GetBreakInSourceByIndex(index,BreakInSource)
#define pgsel_GetNumberOfBreakInSources()	pgsel->GetNumberOfBreakInSources()
#define pgsel_GetRuningStatusForService()	pgsel->GetRuningStatusForService()
#define pgsel_IsDualWindowCombinationAllowed(MainSource,MainChannel,AuxSource,AuxChannel)	pgsel->IsDualWindowCombinationAllowed(MainSource,MainChannel,AuxSource,AuxChannel)
#define pgsel_SetAttribute(attribute,value)	pgsel->SetAttribute(attribute,value)
#define pgsel_GetAttribute(attribute,value)	pgsel->GetAttribute(attribute,value)
#define pgsel_IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection)	pgsel->IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection)
#define pgsel_GetActualTypeOfSelection(Dest)	pgsel->GetActualTypeOfSelection(Dest)
#define pgsel_IsProgramSelectionRequired(Channel)	pgsel->IsProgramSelectionRequired(Channel)
#define pgsel_SetVirginBitOn()	pgsel->SetVirginBitOn()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvMpegDataManager_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
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
#define sdmdiv_iPresent() (sdmdiv.Present())
#define sdmdiv_NoOfVirtualChannels(medium)	sdmdiv->NoOfVirtualChannels(medium)
#define sdmdiv_NoOfDescriptors	sdmdiv->NoOfDescriptors()
#define sdmdiv_NoOfEvents	sdmdiv->NoOfEvents()

#define sdmdiv_MaxStringLength	sdmdiv->MaxStringLength()

#define sdmdiv_RRTParsingAllowed	sdmdiv->RRTParsingAllowed()
#define sdmdiv_SystemTime	sdmdiv->SystemTime()
#define sdmdiv_RatingStringLength	sdmdiv->RatingStringLength()
#define sdmdiv_Enable12hourEitParsing	sdmdiv->Enable12hourEitParsing()
#define sdmdiv_MaxPmtMonitors	sdmdiv->MaxPmtMonitors()
#define sdmdiv_ChannelNameLength	sdmdiv->ChannelNameLength()
#define sdmdiv_SystemLanguage	sdmdiv->SystemLanguage()
#define sdmdiv_ForceLCNSyntax(medium)	sdmdiv->ForceLCNSyntax(medium)
#define sdmdiv_EnableCountryFallbackForLCNSyntax(medium)	sdmdiv->EnableCountryFallbackForLCNSyntax(medium)
#define sdmdiv_EnableONIDFallbackForLCNSyntax(medium)	sdmdiv->EnableONIDFallbackForLCNSyntax(medium)
#define sdmdiv_SupportMultipleOriginalNetworkId(medium)	sdmdiv->SupportMultipleOriginalNetworkId(medium)
#define sdmdiv_AcceptedStreamType(medium,StreamType)	sdmdiv->AcceptedStreamType(medium,StreamType)
#define sdmdiv_IsMpeg4STBoltOnSupported()	sdmdiv->IsMpeg4STBoltOnSupported()
#define sdmdiv_IsAc3AudioSupported()	sdmdiv->IsAc3AudioSupported()
#define sdmdiv_ReapplyChildLockOnEventChange()	sdmdiv->ReapplyChildLockOnEventChange()
#define sdmdiv_IsAVCDescriptorSupported()	sdmdiv->IsAVCDescriptorSupported()
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
#define srtdb_iPresent() (srtdb.Present())
#define srtdb_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdb_GetNoOfRecords(tableid)	srtdb->GetNoOfRecords(tableid)
#define srtdb_Init(tableid)	srtdb->Init(tableid)
#define srtdb_Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)	srtdb->Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)
#define srtdb_SearchOnPrimaryKey(tableid,PrimaryKey,from,to)	srtdb->SearchOnPrimaryKey(tableid,PrimaryKey,from,to)
#define srtdb_SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)	srtdb->SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)
#define srtdb_QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_QueryOnIndex(tableid,index,data)	srtdb->QueryOnIndex(tableid,index,data)
#define srtdb_SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)	srtdb->SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)
#define srtdb_SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)	srtdb->SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)
#define srtdbids_TeletextInfoMain	 reinterpret_cast<int>(&i__teletextconfmain)
#define srtdbids_SubtitlingInfoMain	 reinterpret_cast<int>(&i__subtitleconfmain)
#define srtdbids_BasicPidInfoMain	 reinterpret_cast<int>(&i__basicpidinfoconfmain)
#define srtdbids_AudioInfoMain	 reinterpret_cast<int>(&i__audioinfoconfmain)
#define srtdbids_ComponentTagInfoMain	 reinterpret_cast<int>(&i__componenttaginfomain)
#define srtdbids_DatabroadcastInfoMain	 reinterpret_cast<int>(&i__databroadcastinfomain)
#define srtdbids_TeletextInfoAux	 reinterpret_cast<int>(&i__teletextconfaux)
#define srtdbids_SubtitlingInfoAux	 reinterpret_cast<int>(&i__subtitleconfaux)
#define srtdbids_BasicPidInfoAux	 reinterpret_cast<int>(&i__basicpidinfoconfaux)
#define srtdbids_AudioInfoAux	 reinterpret_cast<int>(&i__audioinfoconfaux)
#define srtdbids_ComponentTagInfoAux	 reinterpret_cast<int>(&i__componenttaginfoaux)
#define srtdbids_DatabroadcastInfoAux	 reinterpret_cast<int>(&i__databroadcastinfoaux)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define audioinfoconfaux_MaxElements	i__audioinfoconfaux.m_MaxElements
#define audioinfoconfaux_ElementSize	i__audioinfoconfaux.m_ElementSize
#define audioinfoconfaux_ThreadSafe	i__audioinfoconfaux.m_ThreadSafe
#define audioinfoconfaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define audioinfoconfaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define audioinfoconfaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define audioinfoconfaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define audioinfoconfaux_SortCriteria	i__audioinfoconfaux.m_SortCriteria
#define audioinfoconfaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define audioinfoconfaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define audioinfoconfaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define audioinfoconfmain_MaxElements	i__audioinfoconfmain.m_MaxElements
#define audioinfoconfmain_ElementSize	i__audioinfoconfmain.m_ElementSize
#define audioinfoconfmain_ThreadSafe	i__audioinfoconfmain.m_ThreadSafe
#define audioinfoconfmain_Primary	IHsvSortedTableConfigurationEx_Primary
#define audioinfoconfmain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define audioinfoconfmain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define audioinfoconfmain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define audioinfoconfmain_SortCriteria	i__audioinfoconfmain.m_SortCriteria
#define audioinfoconfmain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define audioinfoconfmain_Equal	IHsvSortedTableConfigurationEx_Equal
#define audioinfoconfmain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define basicpidinfoconfaux_MaxElements	i__basicpidinfoconfaux.m_MaxElements
#define basicpidinfoconfaux_ElementSize	i__basicpidinfoconfaux.m_ElementSize
#define basicpidinfoconfaux_ThreadSafe	i__basicpidinfoconfaux.m_ThreadSafe
#define basicpidinfoconfaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define basicpidinfoconfaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define basicpidinfoconfaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define basicpidinfoconfaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define basicpidinfoconfaux_SortCriteria	i__basicpidinfoconfaux.m_SortCriteria
#define basicpidinfoconfaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define basicpidinfoconfaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define basicpidinfoconfaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define basicpidinfoconfmain_MaxElements	i__basicpidinfoconfmain.m_MaxElements
#define basicpidinfoconfmain_ElementSize	i__basicpidinfoconfmain.m_ElementSize
#define basicpidinfoconfmain_ThreadSafe	i__basicpidinfoconfmain.m_ThreadSafe
#define basicpidinfoconfmain_Primary	IHsvSortedTableConfigurationEx_Primary
#define basicpidinfoconfmain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define basicpidinfoconfmain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define basicpidinfoconfmain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define basicpidinfoconfmain_SortCriteria	i__basicpidinfoconfmain.m_SortCriteria
#define basicpidinfoconfmain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define basicpidinfoconfmain_Equal	IHsvSortedTableConfigurationEx_Equal
#define basicpidinfoconfmain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define componenttaginfoaux_MaxElements	i__componenttaginfoaux.m_MaxElements
#define componenttaginfoaux_ElementSize	i__componenttaginfoaux.m_ElementSize
#define componenttaginfoaux_ThreadSafe	i__componenttaginfoaux.m_ThreadSafe
#define componenttaginfoaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define componenttaginfoaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define componenttaginfoaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define componenttaginfoaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define componenttaginfoaux_SortCriteria	i__componenttaginfoaux.m_SortCriteria
#define componenttaginfoaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define componenttaginfoaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define componenttaginfoaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define componenttaginfomain_MaxElements	i__componenttaginfomain.m_MaxElements
#define componenttaginfomain_ElementSize	i__componenttaginfomain.m_ElementSize
#define componenttaginfomain_ThreadSafe	i__componenttaginfomain.m_ThreadSafe
#define componenttaginfomain_Primary	IHsvSortedTableConfigurationEx_Primary
#define componenttaginfomain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define componenttaginfomain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define componenttaginfomain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define componenttaginfomain_SortCriteria	i__componenttaginfomain.m_SortCriteria
#define componenttaginfomain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define componenttaginfomain_Equal	IHsvSortedTableConfigurationEx_Equal
#define componenttaginfomain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define databroadcastinfoaux_MaxElements	i__databroadcastinfoaux.m_MaxElements
#define databroadcastinfoaux_ElementSize	i__databroadcastinfoaux.m_ElementSize
#define databroadcastinfoaux_ThreadSafe	i__databroadcastinfoaux.m_ThreadSafe
#define databroadcastinfoaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define databroadcastinfoaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define databroadcastinfoaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define databroadcastinfoaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define databroadcastinfoaux_SortCriteria	i__databroadcastinfoaux.m_SortCriteria
#define databroadcastinfoaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define databroadcastinfoaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define databroadcastinfoaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define databroadcastinfomain_MaxElements	i__databroadcastinfomain.m_MaxElements
#define databroadcastinfomain_ElementSize	i__databroadcastinfomain.m_ElementSize
#define databroadcastinfomain_ThreadSafe	i__databroadcastinfomain.m_ThreadSafe
#define databroadcastinfomain_Primary	IHsvSortedTableConfigurationEx_Primary
#define databroadcastinfomain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define databroadcastinfomain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define databroadcastinfomain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define databroadcastinfomain_SortCriteria	i__databroadcastinfomain.m_SortCriteria
#define databroadcastinfomain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define databroadcastinfomain_Equal	IHsvSortedTableConfigurationEx_Equal
#define databroadcastinfomain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define langids_LangEnglish	IHsvLanguageIds2_LangEnglish
#define langids_LangGerman	IHsvLanguageIds2_LangGerman
#define langids_LangSwedish	IHsvLanguageIds2_LangSwedish
#define langids_LangItalian	IHsvLanguageIds2_LangItalian
#define langids_LangFrench	IHsvLanguageIds2_LangFrench
#define langids_LangSpanish	IHsvLanguageIds2_LangSpanish
#define langids_LangCzech	IHsvLanguageIds2_LangCzech
#define langids_LangPolish	IHsvLanguageIds2_LangPolish
#define langids_LangTurkish	IHsvLanguageIds2_LangTurkish
#define langids_LangRussian	IHsvLanguageIds2_LangRussian
#define langids_LangGreek	IHsvLanguageIds2_LangGreek
#define langids_LangBasque	IHsvLanguageIds2_LangBasque
#define langids_LangCatalan	IHsvLanguageIds2_LangCatalan
#define langids_LangCroatian	IHsvLanguageIds2_LangCroatian
#define langids_LangDanish	IHsvLanguageIds2_LangDanish
#define langids_LangDutch	IHsvLanguageIds2_LangDutch
#define langids_LangFinnish	IHsvLanguageIds2_LangFinnish
#define langids_LangGaelic	IHsvLanguageIds2_LangGaelic
#define langids_LangGalligan	IHsvLanguageIds2_LangGalligan
#define langids_LangNorwegian	IHsvLanguageIds2_LangNorwegian
#define langids_LangPortuguese	IHsvLanguageIds2_LangPortuguese
#define langids_LangSerbian	IHsvLanguageIds2_LangSerbian
#define langids_LangSlovak	IHsvLanguageIds2_LangSlovak
#define langids_LangSlovenian	IHsvLanguageIds2_LangSlovenian
#define langids_LangWelsh	IHsvLanguageIds2_LangWelsh
#define langids_LangRomanian	IHsvLanguageIds2_LangRomanian
#define langids_LangEstonian	IHsvLanguageIds2_LangEstonian
#define langids_LangUkrainian	IHsvLanguageIds2_LangUkrainian
#define langids_LangArabic	IHsvLanguageIds2_LangArabic
#define langids_LangHebrew	IHsvLanguageIds2_LangHebrew
#define langids_LangHungarian	IHsvLanguageIds2_LangHungarian
#define langids_LangHungal	IHsvLanguageIds2_LangHungal
#define langids_LangMalay	IHsvLanguageIds2_LangMalay
#define langids_LangPersian	IHsvLanguageIds2_LangPersian
#define langids_LangSimplifiedchinese	IHsvLanguageIds2_LangSimplifiedchinese
#define langids_LangTaiwanese	IHsvLanguageIds2_LangTaiwanese
#define langids_LangBrazilianPortuguese	IHsvLanguageIds2_LangBrazilianPortuguese
#define langids_LangBulgarian	IHsvLanguageIds2_LangBulgarian
#define langids_LangLatinspanish	IHsvLanguageIds2_LangLatinspanish
#define langids_LangLithuanian	IHsvLanguageIds2_LangLithuanian
#define langids_LangLatvian	IHsvLanguageIds2_LangLatvian
#define langids_LangKazakh	IHsvLanguageIds2_LangKazakh
#define langids_LangThai	IHsvLanguageIds2_LangThai
#define langids_LangIrish	IHsvLanguageIds2_LangIrish
#define langids_LangUndefined	IHsvLanguageIds2_LangUndefined
#define langids_LangOriginalVersion	IHsvLanguageIds2_LangOriginalVersion
#define langids_LangAudioDescription	IHsvLanguageIds2_LangAudioDescription
#define langids_LangNone	IHsvLanguageIds2_LangNone
#define langids_MaxNumberOfLanguages	i__langids.m_MaxNumberOfLanguages
#define langids_iVersion	i__langids.m_iVersion
#define subtitleconfaux_MaxElements	i__subtitleconfaux.m_MaxElements
#define subtitleconfaux_ElementSize	i__subtitleconfaux.m_ElementSize
#define subtitleconfaux_ThreadSafe	i__subtitleconfaux.m_ThreadSafe
#define subtitleconfaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define subtitleconfaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define subtitleconfaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define subtitleconfaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define subtitleconfaux_SortCriteria	i__subtitleconfaux.m_SortCriteria
#define subtitleconfaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define subtitleconfaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define subtitleconfaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define subtitleconfmain_MaxElements	i__subtitleconfmain.m_MaxElements
#define subtitleconfmain_ElementSize	i__subtitleconfmain.m_ElementSize
#define subtitleconfmain_ThreadSafe	i__subtitleconfmain.m_ThreadSafe
#define subtitleconfmain_Primary	IHsvSortedTableConfigurationEx_Primary
#define subtitleconfmain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define subtitleconfmain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define subtitleconfmain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define subtitleconfmain_SortCriteria	i__subtitleconfmain.m_SortCriteria
#define subtitleconfmain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define subtitleconfmain_Equal	IHsvSortedTableConfigurationEx_Equal
#define subtitleconfmain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define teletextconfaux_MaxElements	i__teletextconfaux.m_MaxElements
#define teletextconfaux_ElementSize	i__teletextconfaux.m_ElementSize
#define teletextconfaux_ThreadSafe	i__teletextconfaux.m_ThreadSafe
#define teletextconfaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define teletextconfaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define teletextconfaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define teletextconfaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define teletextconfaux_SortCriteria	i__teletextconfaux.m_SortCriteria
#define teletextconfaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define teletextconfaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define teletextconfaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define teletextconfmain_MaxElements	i__teletextconfmain.m_MaxElements
#define teletextconfmain_ElementSize	i__teletextconfmain.m_ElementSize
#define teletextconfmain_ThreadSafe	i__teletextconfmain.m_ThreadSafe
#define teletextconfmain_Primary	IHsvSortedTableConfigurationEx_Primary
#define teletextconfmain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define teletextconfmain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define teletextconfmain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define teletextconfmain_SortCriteria	i__teletextconfmain.m_SortCriteria
#define teletextconfmain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define teletextconfmain_Equal	IHsvSortedTableConfigurationEx_Equal
#define teletextconfmain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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

