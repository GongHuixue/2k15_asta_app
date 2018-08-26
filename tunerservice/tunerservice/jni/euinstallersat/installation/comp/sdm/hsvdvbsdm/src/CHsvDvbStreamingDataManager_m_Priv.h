#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_M_PRIV_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDVBService.h>
#include <IHsvStream.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDemuxNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <IHsvCountryIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IPumpExSub.h>
#include <IHsvStreamFilterNotify.h>
#include <IHsvSatSystemSettings.h>
#include <CS2MwBase.h>

class CHsvDvbStreamingDataManager_m_Priv;
#define CLASSSCOPE CHsvDvbStreamingDataManager_m_Priv::
#include "locals_m.h"

class CHsvDvbStreamingDataManager_m_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbStreamingDataManager_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDVBSIConfigImpl(CHsvDvbStreamingDataManager_m_Priv,conf);
IHsvSdmControl2Impl(CHsvDvbStreamingDataManager_m_Priv,ctrl);
IHsvSdmControlNotifyExImpl(CHsvDvbStreamingDataManager_m_Priv,hsvdvbsi_ctrlN);
IHsvDVBServiceImpl(CHsvDvbStreamingDataManager_m_Priv,hsvdvbsi_dvbsvc);
IHsvSdmControlNotifyExImpl(CHsvDvbStreamingDataManager_m_Priv,hsvsimplempeg_ctrlN);
IHsvSdmControl2Impl(CHsvDvbStreamingDataManager_m_Priv,ictrl);
IHsvStreamImpl(CHsvDvbStreamingDataManager_m_Priv,ilclstrapi);
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbStreamingDataManager_m_Priv,pdmxsecfN);
IHsvDemuxNotifyImpl(CHsvDvbStreamingDataManager_m_Priv,phsvdmxN);
IHsvPowerImpl(CHsvDvbStreamingDataManager_m_Priv,pow);
IHsvStreamFilterImpl(CHsvDvbStreamingDataManager_m_Priv,strmfltr);
public:
ProvidesInterface<IHsvDVBSIConfig>	conf;

ProvidesInterface<IHsvSdmControl2>	ctrl;

ProvidesInterface<IHsvSdmControlNotifyEx>	hsvdvbsi_ctrlN;

ProvidesInterface<IHsvDVBService>	hsvdvbsi_dvbsvc;

ProvidesInterface<IHsvSdmControlNotifyEx>	hsvsimplempeg_ctrlN;

ProvidesInterface<IHsvSdmControl2>	ictrl;

ProvidesInterface<IHsvStream>	ilclstrapi;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	pdmxsecfN;

ProvidesInterface<IHsvDemuxNotify>	phsvdmxN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDemuxNotify>	hsvdmxN;
RequiresInterface<IHsvDemuxSectionFilterNotify>	hsvdvbsi_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	hsvdvbsi_ena;
RequiresInterface<IHsvPower>	hsvdvbsi_pow;
RequiresInterface<IHsvStreamFilter>	hsvdvbsi_strmfltr;
RequiresInterface<IHsvSdmEnable>	hsvsimplempeg_enable;
RequiresInterface<IHsvPower>	hsvsimplempeg_pow;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvStream>	istrapi;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IHsvSatSystemSettings>	sysset;
private:
Pumpdefines(CHsvDvbStreamingDataManager_m_Priv);

public:
CHsvDvbStreamingDataManager_m_Priv():i__conf(this),i__ctrl(this),i__hsvdvbsi_ctrlN(this),i__hsvdvbsi_dvbsvc(this),i__hsvsimplempeg_ctrlN(this),i__ictrl(this),i__ilclstrapi(this),i__pdmxsecfN(this),i__phsvdmxN(this),i__pow(this),i__strmfltr(this)
{
conf	=	&i__conf;
ctrl	=	&i__ctrl;
hsvdvbsi_ctrlN	=	&i__hsvdvbsi_ctrlN;
hsvdvbsi_dvbsvc	=	&i__hsvdvbsi_dvbsvc;
hsvsimplempeg_ctrlN	=	&i__hsvsimplempeg_ctrlN;
ictrl	=	&i__ictrl;
ilclstrapi	=	&i__ilclstrapi;
pdmxsecfN	=	&i__pdmxsecfN;
phsvdmxN	=	&i__phsvdmxN;
pow	=	&i__pow;
strmfltr	=	&i__strmfltr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define cids_iPresent() (cids.Present())
#define cids_CountryAustria	IHsvCountryIds_CountryAustria
#define cids_CountryBelgium	IHsvCountryIds_CountryBelgium
#define cids_CountryCroatia	IHsvCountryIds_CountryCroatia
#define cids_CountryCzechrep	IHsvCountryIds_CountryCzechrep
#define cids_CountryDenmark	IHsvCountryIds_CountryDenmark
#define cids_CountryFinland	IHsvCountryIds_CountryFinland
#define cids_CountryFrance	IHsvCountryIds_CountryFrance
#define cids_CountryGermany	IHsvCountryIds_CountryGermany
#define cids_CountryGreece	IHsvCountryIds_CountryGreece
#define cids_CountryHungary	IHsvCountryIds_CountryHungary
#define cids_CountryIreland	IHsvCountryIds_CountryIreland
#define cids_CountryItaly	IHsvCountryIds_CountryItaly
#define cids_CountryLuxembourg	IHsvCountryIds_CountryLuxembourg
#define cids_CountryNetherlands	IHsvCountryIds_CountryNetherlands
#define cids_CountryNorway	IHsvCountryIds_CountryNorway
#define cids_CountryPoland	IHsvCountryIds_CountryPoland
#define cids_CountryPortugal	IHsvCountryIds_CountryPortugal
#define cids_CountryRomania	IHsvCountryIds_CountryRomania
#define cids_CountryRussia	IHsvCountryIds_CountryRussia
#define cids_CountrySerbia	IHsvCountryIds_CountrySerbia
#define cids_CountrySlovakia	IHsvCountryIds_CountrySlovakia
#define cids_CountrySlovenia	IHsvCountryIds_CountrySlovenia
#define cids_CountrySpain	IHsvCountryIds_CountrySpain
#define cids_CountrySweden	IHsvCountryIds_CountrySweden
#define cids_CountrySwitzerland	IHsvCountryIds_CountrySwitzerland
#define cids_CountryTurkey	IHsvCountryIds_CountryTurkey
#define cids_CountryUK	IHsvCountryIds_CountryUK
#define cids_CountryOther	IHsvCountryIds_CountryOther
#define cids_CountryAustralia	IHsvCountryIds_CountryAustralia
#define cids_CountryEstonia	IHsvCountryIds_CountryEstonia
#define cids_CountryLithuania	IHsvCountryIds_CountryLithuania
#define cids_CountryLatvia	IHsvCountryIds_CountryLatvia
#define cids_CountryKazakhstan	IHsvCountryIds_CountryKazakhstan
#define cids_CountryBulgaria	IHsvCountryIds_CountryBulgaria
#define cids_CountryChina	IHsvCountryIds_CountryChina
#define cids_CountryUkraine	IHsvCountryIds_CountryUkraine
#define cids_CountryBrazil	IHsvCountryIds_CountryBrazil
#define cids_CountryArgentina	IHsvCountryIds_CountryArgentina
#define cids_CountryAlbania	IHsvCountryIds_CountryAlbania
#define cids_CountryArmenia	IHsvCountryIds_CountryArmenia
#define cids_CountryAzerbaijan	IHsvCountryIds_CountryAzerbaijan
#define cids_CountryBelarus	IHsvCountryIds_CountryBelarus
#define cids_CountryBosniaAndHerzegovina	IHsvCountryIds_CountryBosniaAndHerzegovina
#define cids_CountryGeorgia	IHsvCountryIds_CountryGeorgia
#define cids_CountryMontenegro	IHsvCountryIds_CountryMontenegro
#define cids_CountryIsrael	IHsvCountryIds_CountryIsrael
#define cids_CountryMacedoniafyrom	IHsvCountryIds_CountryMacedoniafyrom
#define cids_CountryMax	IHsvCountryIds_CountryMax
#define ctrlN_iPresent() (ctrlN.Present())
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
#define ctrlN_Postcode	IHsvSdmControlNotifyEx_Postcode
#define ctrlN_SGT	IHsvSdmControlNotifyEx_SGT
#define ctrlN_OnEvent(dmx,eventid,value)	ctrlN->OnEvent(dmx,eventid,value)
#define ctrlpen_iPresent() (ctrlpen.Present())
#define ctrlpen_PumpEngine	ctrlpen->PumpEngine()
#define div_iPresent() (div.Present())
#define div_NoOfVirtualChannels(medium)	div->NoOfVirtualChannels(medium)
#define div_NoOfDescriptors	div->NoOfDescriptors()
#define div_NoOfEvents	div->NoOfEvents()
#define div_SdmWaitTime	div->SdmWaitTime()
#define div_MaxStringLength	div->MaxStringLength()
#define div_DataCollectionTimeout	div->DataCollectionTimeout()
#define div_RRTParsingAllowed	div->RRTParsingAllowed()
#define div_SystemTime	div->SystemTime()
#define div_RatingStringLength	div->RatingStringLength()
#define div_Enable12hourEitParsing	div->Enable12hourEitParsing()
#define div_MaxPmtMonitors	div->MaxPmtMonitors()
#define div_ChannelNameLength	div->ChannelNameLength()
#define div_SystemLanguage	div->SystemLanguage()
#define div_MaxSimplePmtFilterSupported	div->MaxSimplePmtFilterSupported()
#define div_MaxSimplePmtSupported	div->MaxSimplePmtSupported()
#define div_ForceLCNSyntax(medium)	div->ForceLCNSyntax(medium)
#define div_EnableCountryFallbackForLCNSyntax(medium)	div->EnableCountryFallbackForLCNSyntax(medium)
#define div_EnableONIDFallbackForLCNSyntax(medium)	div->EnableONIDFallbackForLCNSyntax(medium)
#define div_AcceptedStreamType(medium,StreamType)	div->AcceptedStreamType(medium,StreamType)
#define div_IsMpeg4STBoltOnSupported()	div->IsMpeg4STBoltOnSupported()
#define div_IsAc3AudioSupported()	div->IsAc3AudioSupported()
#define div_ReapplyChildLockOnEventChange()	div->ReapplyChildLockOnEventChange()
#define div_IsAVCDescriptorSupported()	div->IsAVCDescriptorSupported()
#define dmxena_iPresent() (dmxena.Present())
#define dmxena_Enable(dmx)	dmxena->Enable(dmx)
#define dmxena_Disable(dmx)	dmxena->Disable(dmx)
#define dmxena_Sync(dmx)	dmxena->Sync(dmx)
#define dmxsecfN_iPresent() (dmxsecfN.Present())
#define dmxsecfN_OnRequestAllowed(dest)	dmxsecfN->OnRequestAllowed(dest)
#define dmxsecfN_OnRequestCancelled(subscrId)	dmxsecfN->OnRequestCancelled(subscrId)
#define dmxsecfN_OnRequestNotAllowed()	dmxsecfN->OnRequestNotAllowed()
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
#define hsvdmxN_iPresent() (hsvdmxN.Present())
#define hsvdmxN_OnStarted(dmx)	hsvdmxN->OnStarted(dmx)
#define hsvdmxN_OnStopped(dmx)	hsvdmxN->OnStopped(dmx)
#define hsvdmxN_OnDemuxSyncLock(dmx)	hsvdmxN->OnDemuxSyncLock(dmx)
#define hsvdmxN_OnDemuxSyncLost(dmx)	hsvdmxN->OnDemuxSyncLost(dmx)
#define hsvdvbsi_dmxsecfN_iPresent() (hsvdvbsi_dmxsecfN.Present())
#define hsvdvbsi_dmxsecfN_OnRequestAllowed(dest)	hsvdvbsi_dmxsecfN->OnRequestAllowed(dest)
#define hsvdvbsi_dmxsecfN_OnRequestCancelled(subscrId)	hsvdvbsi_dmxsecfN->OnRequestCancelled(subscrId)
#define hsvdvbsi_dmxsecfN_OnRequestNotAllowed()	hsvdvbsi_dmxsecfN->OnRequestNotAllowed()
#define hsvdvbsi_ena_iPresent() (hsvdvbsi_ena.Present())
#define hsvdvbsi_ena_Enable(dmx)	hsvdvbsi_ena->Enable(dmx)
#define hsvdvbsi_ena_Disable(dmx)	hsvdvbsi_ena->Disable(dmx)
#define hsvdvbsi_ena_Sync(dmx)	hsvdvbsi_ena->Sync(dmx)
#define hsvdvbsi_pow_iPresent() (hsvdvbsi_pow.Present())
#define hsvdvbsi_pow_Init()	hsvdvbsi_pow->Init()
#define hsvdvbsi_pow_TurnOn()	hsvdvbsi_pow->TurnOn()
#define hsvdvbsi_pow_TurnOff()	hsvdvbsi_pow->TurnOff()
#define hsvdvbsi_strmfltr_iPresent() (hsvdvbsi_strmfltr.Present())
#define hsvdvbsi_strmfltr_IsSet(dest,filterid,value)	hsvdvbsi_strmfltr->IsSet(dest,filterid,value)
#define hsvdvbsi_strmfltr_IsReady(dest,filterid)	hsvdvbsi_strmfltr->IsReady(dest,filterid)
#define hsvdvbsi_strmfltr_Set(dest,filterid,value)	hsvdvbsi_strmfltr->Set(dest,filterid,value)
#define hsvdvbsi_strmfltr_Clear(dest,filterid,value)	hsvdvbsi_strmfltr->Clear(dest,filterid,value)
#define hsvsimplempeg_enable_iPresent() (hsvsimplempeg_enable.Present())
#define hsvsimplempeg_enable_Enable(dmx)	hsvsimplempeg_enable->Enable(dmx)
#define hsvsimplempeg_enable_Disable(dmx)	hsvsimplempeg_enable->Disable(dmx)
#define hsvsimplempeg_enable_Sync(dmx)	hsvsimplempeg_enable->Sync(dmx)
#define hsvsimplempeg_pow_iPresent() (hsvsimplempeg_pow.Present())
#define hsvsimplempeg_pow_Init()	hsvsimplempeg_pow->Init()
#define hsvsimplempeg_pow_TurnOn()	hsvsimplempeg_pow->TurnOn()
#define hsvsimplempeg_pow_TurnOff()	hsvsimplempeg_pow->TurnOff()
#define ins_iPresent() (ins.Present())
#define ins_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define ins_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define ins_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define ins_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define ins_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define ins_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define ins_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define ins_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define ins_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define ins_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define ins_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
/* New mode for Tricolor Region Name based installation */
#define ins_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan

#define ins_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define ins_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan

#define ins_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define ins_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define ins_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define ins_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define ins_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define ins_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define ins_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define ins_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define ins_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define ins_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define ins_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define ins_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define ins_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define ins_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define ins_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define ins_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define ins_GetCurrentInstallationState(mode,state)	ins->GetCurrentInstallationState(mode,state)
#define ins_StartInstallation(Source,Lnb,Mode)	ins->StartInstallation(Source,Lnb,Mode)
#define ins_StopInstallation()	ins->StopInstallation()
#define ins_ResetInstallation()	ins->ResetInstallation()
#define ins_GetNumberOfTvChannelsFound(Lnb)	ins->GetNumberOfTvChannelsFound(Lnb)
#define ins_GetNumberofRadioChannelsFound(Lnb)	ins->GetNumberofRadioChannelsFound(Lnb)
#define ins_GetNumberOfTvChannelsRemoved(Lnb)	ins->GetNumberOfTvChannelsRemoved(Lnb)
#define ins_GetNumberofRadioChannelsRemoved(Lnb)	ins->GetNumberofRadioChannelsRemoved(Lnb)
#define ins_GetSatelliteName(Lnb,SatelliteName)	ins->GetSatelliteName(Lnb,SatelliteName)
#define ins_GetNumberOfDigitalChannelsAdded()	ins->GetNumberOfDigitalChannelsAdded()
#define ins_GetNumberOfDigitalChannelsRemoved()	ins->GetNumberOfDigitalChannelsRemoved()
#define ins_GetNumberOfDigitalChannelsMoved()	ins->GetNumberOfDigitalChannelsMoved()
#define ins_IdentifyPackagesAvailable()	ins->IdentifyPackagesAvailable()
#define ins_GetTotalNumberOfPackagesFound()	ins->GetTotalNumberOfPackagesFound()
#define ins_GetPackageByIndex(Index,Package)	ins->GetPackageByIndex(Index,Package)
#define ins_SetUserPackageIndex(PackageIndex)	ins->SetUserPackageIndex(PackageIndex)
#define ins_GetUserPackageIndex(PackageIndex,IsPackage)	ins->GetUserPackageIndex(PackageIndex,IsPackage)
#define ins_GetInstalledSatellites(mode,SatelliteEntries)	ins->GetInstalledSatellites(mode,SatelliteEntries)
#define ins_InstallAddedSatellites()	ins->InstallAddedSatellites()
#define ins_ResetAddedSatellites()	ins->ResetAddedSatellites()
#define ins_RemoveSatelliteEntry(LnbNumber)	ins->RemoveSatelliteEntry(LnbNumber)
#define ins_GetSatelliteSignalStrength(LnbNumber)	ins->GetSatelliteSignalStrength(LnbNumber)
#define ins_GetSatelliteSignalQuality(LnbNumber)	ins->GetSatelliteSignalQuality(LnbNumber)
#define ins_LoadManualInstallationDefaultValues()	ins->LoadManualInstallationDefaultValues()
#define ins_StoreManualInstallationValues()	ins->StoreManualInstallationValues()
#define ins_GetAttribute(Mode,AttributeId)	ins->GetAttribute(Mode,AttributeId)
#define ins_SetAttribute(Mode,AttributeId,Value)	ins->SetAttribute(Mode,AttributeId,Value)
#define ins_GetScanProgressStatus(Mode)	ins->GetScanProgressStatus(Mode)
#define ins_GetSITableIds(NetworkID,BouquetID)	ins->GetSITableIds(NetworkID,BouquetID)
#define ins_GetPackageName(PackageId,PackageName)	ins->GetPackageName(PackageId,PackageName)
#define ins_GetSIDetails(SiValues)	ins->GetSIDetails(SiValues)
#define ins_EnableUnicable(LnbNumber,Enable)	ins->EnableUnicable(LnbNumber,Enable)
#define ins_StopSignalStrengthMeas(LnbNumber)	ins->StopSignalStrengthMeas(LnbNumber)
#define ins_GetSignalQuality(Param)	ins->GetSignalQuality(Param)
#define ins_StartSignalStrengthMeas(LnbNumber)	ins->StartSignalStrengthMeas(LnbNumber)
#define ins_GetSignalStrength(param)	ins->GetSignalStrength(param)
#define ins_StartPredefinedListCopy()	ins->StartPredefinedListCopy()
#define ins_GetFirstInstalledChannel()	ins->GetFirstInstalledChannel()
#define ins_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	ins->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define istrapi_iPresent() (istrapi.Present())
#define istrapi_GetSize(dest,spid)	istrapi->GetSize(dest,spid)
#define istrapi_GetIndex(dest,spid,key1,key2,key3,index)	istrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define istrapi_GetByKey(dest,spid,key1,key2,key3,val)	istrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define istrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	istrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define istrapi_GetByIndex(dest,spid,index,val)	istrapi->GetByIndex(dest,spid,index,val)
#define pakgins_iPresent() (pakgins.Present())
#define pakgins_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define pakgins_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define pakgins_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define pakgins_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define pakgins_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define pakgins_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define pakgins_GetCurrentInstallationState(mode,state)	pakgins->GetCurrentInstallationState(mode,state)
#define pakgins_StartInstallation(Source,Lnb,Mode)	pakgins->StartInstallation(Source,Lnb,Mode)
#define pakgins_StopInstallation()	pakgins->StopInstallation()
#define pakgins_WriteBarkerMuxData()	pakgins->WriteBarkerMuxData()
#define pakgins_GetNumberOfTvChannelsFound(Mode,Lnb)	pakgins->GetNumberOfTvChannelsFound(Mode,Lnb)
#define pakgins_GetNumberofRadioChannelsFound(Mode,Lnb)	pakgins->GetNumberofRadioChannelsFound(Mode,Lnb)
#define pakgins_GetNumberOfTvChannelsRemoved(Mode,Lnb)	pakgins->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define pakgins_GetNumberofRadioChannelsRemoved(Mode,Lnb)	pakgins->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define pakgins_GetNumberOfDigitalChannelsAdded()	pakgins->GetNumberOfDigitalChannelsAdded()
#define pakgins_GetNumberOfDigitalChannelsRemoved()	pakgins->GetNumberOfDigitalChannelsRemoved()
#define pakgins_GetNumberOfDigitalChannelsMoved()	pakgins->GetNumberOfDigitalChannelsMoved()
#define pakgins_LoadManualInstallationDefaultValues()	pakgins->LoadManualInstallationDefaultValues()
#define pakgins_StoreManualInstallationValues()	pakgins->StoreManualInstallationValues()
#define pakgins_SetManualInstallationAttributes(AttributeId,Value)	pakgins->SetManualInstallationAttributes(AttributeId,Value)
#define pakgins_GetAttribute(Mode,AttributeId)	pakgins->GetAttribute(Mode,AttributeId)
#define pakgins_GetScanProgressStatus(Mode)	pakgins->GetScanProgressStatus(Mode)
#define pakgins_GetSIDetails(SiValues)	pakgins->GetSIDetails(SiValues)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbStreamingDataManager_m_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define strmfltrN_iPresent() (strmfltrN.Present())
#define strmfltrN_OnReady(dest,filterid)	strmfltrN->OnReady(dest,filterid)
#define sysset_iPresent() (sysset.Present())
#define sysset_AudioFormatStandard	IHsvSatSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvSatSystemSettings_AudioFormatAdvanced
#define sysset_SetSystemLanguage(lang)	sysset->SetSystemLanguage(lang)
#define sysset_GetSystemLanguage()	sysset->GetSystemLanguage()
#define sysset_SetPreferredPrimaryAudioLanguage(lang)	sysset->SetPreferredPrimaryAudioLanguage(lang)
#define sysset_GetPreferredPrimaryAudioLanguage()	sysset->GetPreferredPrimaryAudioLanguage()
#define sysset_GetPreferredSecondarySubtitleLanguage()	sysset->GetPreferredSecondarySubtitleLanguage()
#define sysset_SetPreferredSecondarySubtitleLanguage(lang)	sysset->SetPreferredSecondarySubtitleLanguage(lang)
#define sysset_GetPreferredSecondaryAudioLanguage()	sysset->GetPreferredSecondaryAudioLanguage()
#define sysset_SetPreferredSecondaryAudioLanguage(lang)	sysset->SetPreferredSecondaryAudioLanguage(lang)
#define sysset_SetPreferredPrimarySubtitleLanguage(lang)	sysset->SetPreferredPrimarySubtitleLanguage(lang)
#define sysset_GetPreferredPrimarySubtitleLanguage()	sysset->GetPreferredPrimarySubtitleLanguage()
#define sysset_SetPreferredAudioFormat(format)	sysset->SetPreferredAudioFormat(format)
#define sysset_GetPreferredAudioFormat()	sysset->GetPreferredAudioFormat()
#define sysset_SetPreferredPrimaryTxtLanguage(lang)	sysset->SetPreferredPrimaryTxtLanguage(lang)
#define sysset_GetPreferredPrimaryTxtLanguage()	sysset->GetPreferredPrimaryTxtLanguage()
#define sysset_SetPreferredSecondaryTxtLanguage(lang)	sysset->SetPreferredSecondaryTxtLanguage(lang)
#define sysset_GetPreferredSecondaryTxtLanguage()	sysset->GetPreferredSecondaryTxtLanguage()
#define sysset_SetSystemCountry(country)	sysset->SetSystemCountry(country)
#define sysset_GetSystemCountry()	sysset->GetSystemCountry()
#define sysset_SetInstallCountry(country)	sysset->SetInstallCountry(country)
#define sysset_GetInstallCountry()	sysset->GetInstallCountry()
#define sysset_SetInstallCity(city)	sysset->SetInstallCity(city)
#define sysset_SetSystemCity(city)	sysset->SetSystemCity(city)
#define sysset_GetInstallCity()	sysset->GetInstallCity()
#define sysset_GetSystemCity()	sysset->GetSystemCity()
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
#define conf_BatParsing	IHsvDVBSIConfig_BatParsing
#define conf_FntParsing	IHsvDVBSIConfig_FntParsing
#define conf_FstParsing	IHsvDVBSIConfig_FstParsing
#define conf_PostcodeParsing	IHsvDVBSIConfig_PostcodeParsing
#define conf_SgtParsing	IHsvDVBSIConfig_SgtParsing
#define conf_Notifications	IHsvDVBSIConfig_Notifications
#define conf_CurrentCountry	i__conf.m_CurrentCountry
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
#define ctrl_FransatCamIns  IHsvSdmControl2_FransatCamIns
#define ctrl_Invalid	IHsvSdmControl2_Invalid
#define ctrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ctrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ctrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ctrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ctrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
#define ctrl_FNTAvailable	IHsvSdmControl2_FNTAvailable
#define ctrl_FSTAvailable	IHsvSdmControl2_FSTAvailable
#define ctrl_BATAvailable	IHsvSdmControl2_BATAvailable
#define ctrl_FreesatMinimalNitAct	IHsvSdmControl2_FreesatMinimalNitAct
#define ctrl_FreesatPostcode	IHsvSdmControl2_FreesatPostcode
#define ctrl_FreesatNormal	IHsvSdmControl2_FreesatNormal
#define ctrl_FreesatMinimalNitOth IHsvSdmControl2_FreesatMinimalNitOth
#define ctrl_FreesatPSIMode IHsvSdmControl2_FreesatPSIMode
#define ctrl_TricolorNormal IHsvSdmControl2_TricolorNormal 
#define ctrl_TOTAvailable	IHsvSdmControl2_TOTAvailable
#define hsvdvbsi_ctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define hsvdvbsi_ctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define hsvdvbsi_ctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define hsvdvbsi_ctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define hsvdvbsi_ctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define hsvdvbsi_ctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define hsvdvbsi_ctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define hsvdvbsi_ctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define hsvdvbsi_ctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define hsvdvbsi_ctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define hsvdvbsi_ctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define hsvdvbsi_ctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define hsvdvbsi_ctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define hsvdvbsi_ctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define hsvdvbsi_ctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define hsvdvbsi_ctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define hsvdvbsi_ctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define hsvdvbsi_ctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define hsvdvbsi_ctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define hsvdvbsi_ctrlN_FST	IHsvSdmControlNotifyEx_FST
#define hsvdvbsi_ctrlN_Postcode	IHsvSdmControlNotifyEx_Postcode
#define hsvdvbsi_ctrlN_SGT	IHsvSdmControlNotifyEx_SGT
#define hsvsimplempeg_ctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define hsvsimplempeg_ctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define hsvsimplempeg_ctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define hsvsimplempeg_ctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define hsvsimplempeg_ctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define hsvsimplempeg_ctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define hsvsimplempeg_ctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define hsvsimplempeg_ctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define hsvsimplempeg_ctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define hsvsimplempeg_ctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define hsvsimplempeg_ctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define hsvsimplempeg_ctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define hsvsimplempeg_ctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define hsvsimplempeg_ctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define hsvsimplempeg_ctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define hsvsimplempeg_ctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define hsvsimplempeg_ctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define hsvsimplempeg_ctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define hsvsimplempeg_ctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define hsvsimplempeg_ctrlN_FST	IHsvSdmControlNotifyEx_FST
#define hsvsimplempeg_ctrlN_Postcode	IHsvSdmControlNotifyEx_Postcode
#define ictrl_Idle	IHsvSdmControl2_Idle
#define ictrl_Minimal	IHsvSdmControl2_Minimal
#define ictrl_Normal	IHsvSdmControl2_Normal
#define ictrl_External	IHsvSdmControl2_External
#define ictrl_CrossCarraige	IHsvSdmControl2_CrossCarraige
#define ictrl_NormalPlusPmt	IHsvSdmControl2_NormalPlusPmt
#define ictrl_M7Minimal	IHsvSdmControl2_M7Minimal
#define ictrl_HomingMuxData	IHsvSdmControl2_HomingMuxData
#define ictrl_PkgBuildMode	IHsvSdmControl2_PkgBuildMode
#define ictrl_FransatNormal	IHsvSdmControl2_FransatNormal
#define ictrl_MinimalPlusBat	IHsvSdmControl2_MinimalPlusBat
#define ictrl_FreesatMinimalNitAct	IHsvSdmControl2_FreesatMinimalNitAct
#define ictrl_FreesatPostcode	IHsvSdmControl2_FreesatPostcode
#define ictrl_FreesatNormal	IHsvSdmControl2_FreesatNormal
#define ictrl_FreesatMinimalNitOth IHsvSdmControl2_FreesatMinimalNitOth
#define ictrl_FreesatPSIMode IHsvSdmControl2_FreesatPSIMode
#define ictrl_Invalid	IHsvSdmControl2_Invalid
#define ictrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ictrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ictrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ictrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ictrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
#define ictrl_FNTAvailable	IHsvSdmControl2_FNTAvailable
#define ictrl_FSTAvailable	IHsvSdmControl2_FSTAvailable
#define ictrl_BATAvailable	IHsvSdmControl2_BATAvailable
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

