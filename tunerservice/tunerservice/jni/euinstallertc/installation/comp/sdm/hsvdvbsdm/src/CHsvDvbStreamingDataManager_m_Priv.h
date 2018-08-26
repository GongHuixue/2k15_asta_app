#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_M_PRIV_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDemuxNotify.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDVBService.h>
#include <IHsvMpegSectionsNotify.h>
#include <IHsvStream.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <IHsvCountryIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvMpegSections.h>
#include <IHsvInstallation2.h>
#include <IPumpExSub.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvStreamFilterNotify.h>
#include <IHsvTcSystemSettings.h>
#include <CTCMwBase.h>
class CHsvDvbStreamingDataManager_m_Priv;
#define CLASSSCOPE CHsvDvbStreamingDataManager_m_Priv::
#include "locals_m.h"

class CHsvDvbStreamingDataManager_m_Priv : public CTCMwBase
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
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbStreamingDataManager_m_Priv,dmxsecfN);
IHsvDemuxNotifyImpl(CHsvDvbStreamingDataManager_m_Priv,hsvdmxN);
IHsvSdmControlNotifyExImpl(CHsvDvbStreamingDataManager_m_Priv,hsvdvbsi_ctrlN);
IHsvDVBServiceImpl(CHsvDvbStreamingDataManager_m_Priv,hsvdvbsi_dvbsvc);
IHsvMpegSectionsNotifyImpl(CHsvDvbStreamingDataManager_m_Priv,hsvmpeg_mpegsecnN);
IHsvStreamImpl(CHsvDvbStreamingDataManager_m_Priv,ilclstrapi);
IHsvPowerImpl(CHsvDvbStreamingDataManager_m_Priv,pow);
IHsvStreamFilterImpl(CHsvDvbStreamingDataManager_m_Priv,strmfltr);
public:
ProvidesInterface<IHsvDVBSIConfig>	conf;

ProvidesInterface<IHsvSdmControl2>	ctrl;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvDemuxNotify>	hsvdmxN;

ProvidesInterface<IHsvSdmControlNotifyEx>	hsvdvbsi_ctrlN;

ProvidesInterface<IHsvDVBService>	hsvdvbsi_dvbsvc;

ProvidesInterface<IHsvMpegSectionsNotify>	hsvmpeg_mpegsecnN;

ProvidesInterface<IHsvStream>	ilclstrapi;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvPower>	dmxpow;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvPower>	hsvdvbcamsdm_pow;
RequiresInterface<IHsvStreamFilter>	hsvdvbcamsdm_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	hsvdvbsi_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	hsvdvbsi_ena;
RequiresInterface<IHsvPower>	hsvdvbsi_pow;
RequiresInterface<IHsvStreamFilter>	hsvdvbsi_strmfltr;
RequiresInterface<IHsvSdmEnable>	hsvmpeg_enable;
RequiresInterface<IHsvMpegSections>	hsvmpeg_mpegsecn;
RequiresInterface<IHsvPower>	hsvmpeg_pow;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvStream>	istrapi;
RequiresInterface<IHsvMpegSectionsNotify>	mpegsecnN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvDemuxSectionFilter2>	secfltr;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
private:
Pumpdefines(CHsvDvbStreamingDataManager_m_Priv);
DEMUX_DEFINES(CHsvDvbStreamingDataManager_m_Priv,secfltr);

public:
CHsvDvbStreamingDataManager_m_Priv():i__conf(this),i__ctrl(this),i__dmxsecfN(this),i__hsvdmxN(this),i__hsvdvbsi_ctrlN(this),i__hsvdvbsi_dvbsvc(this),i__hsvmpeg_mpegsecnN(this),i__ilclstrapi(this),i__pow(this),i__strmfltr(this)
{
conf	=	&i__conf;
ctrl	=	&i__ctrl;
dmxsecfN	=	&i__dmxsecfN;
hsvdmxN	=	&i__hsvdmxN;
hsvdvbsi_ctrlN	=	&i__hsvdvbsi_ctrlN;
hsvdvbsi_dvbsvc	=	&i__hsvdvbsi_dvbsvc;
hsvmpeg_mpegsecnN	=	&i__hsvmpeg_mpegsecnN;
ilclstrapi	=	&i__ilclstrapi;
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
#define cids_CountryParaguay	IHsvCountryIds_CountryParaguay
#define cids_CountryUruguay	IHsvCountryIds_CountryUruguay
#define cids_CountryThailand	IHsvCountryIds_CountryThailand
#define cids_CountryNewZealand	IHsvCountryIds_CountryNewZealand
#define cids_CountrySingapore	IHsvCountryIds_CountrySingapore
#define cids_CountryMalaysia	IHsvCountryIds_CountryMalaysia
#define cids_CountryTaiwan	IHsvCountryIds_CountryTaiwan
#define cids_CountryIndonesia	IHsvCountryIds_CountryIndonesia
#define cids_CountryUAE	IHsvCountryIds_CountryUAE
#define cids_CountryVietnam     IHsvCountryIds_CountryVietnam
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
#define ctrlN_OnEvent(dmx,eventid,value)	ctrlN->OnEvent(dmx,eventid,value)
#define ctrlpen_iPresent() (ctrlpen.Present())
#define ctrlpen_PumpEngine	ctrlpen->PumpEngine()
#define div_iPresent() (div.Present())
#define div_NoOfVirtualChannels(medium)	div->NoOfVirtualChannels(medium)
#define div_NoOfDescriptors	div->NoOfDescriptors()
#define div_NoOfEvents	div->NoOfEvents()

#define div_MaxStringLength	div->MaxStringLength()

#define div_RRTParsingAllowed	div->RRTParsingAllowed()
#define div_SystemTime	div->SystemTime()
#define div_RatingStringLength	div->RatingStringLength()
#define div_Enable12hourEitParsing	div->Enable12hourEitParsing()
#define div_MaxPmtMonitors	div->MaxPmtMonitors()
#define div_ChannelNameLength	div->ChannelNameLength()
#define div_SystemLanguage	div->SystemLanguage()
#define div_ForceLCNSyntax(medium)	div->ForceLCNSyntax(medium)
#define div_EnableCountryFallbackForLCNSyntax(medium)	div->EnableCountryFallbackForLCNSyntax(medium)
#define div_EnableONIDFallbackForLCNSyntax(medium)	div->EnableONIDFallbackForLCNSyntax(medium)
#define div_SupportMultipleOriginalNetworkId(medium)	div->SupportMultipleOriginalNetworkId(medium)
#define div_AcceptedStreamType(medium,StreamType)	div->AcceptedStreamType(medium,StreamType)
#define div_IsMpeg4STBoltOnSupported()	div->IsMpeg4STBoltOnSupported()
#define div_IsAc3AudioSupported()	div->IsAc3AudioSupported()
#define div_ReapplyChildLockOnEventChange()	div->ReapplyChildLockOnEventChange()
#define div_IsAVCDescriptorSupported()	div->IsAVCDescriptorSupported()
#define dmxena_iPresent() (dmxena.Present())
#define dmxena_Enable(dmx)	dmxena->Enable(dmx)
#define dmxena_Disable(dmx)	dmxena->Disable(dmx)
#define dmxena_Sync(dmx)	dmxena->Sync(dmx)
#define dmxpow_iPresent() (dmxpow.Present())
#define dmxpow_Init()	dmxpow->Init()
#define dmxpow_TurnOn()	dmxpow->TurnOn()
#define dmxpow_TurnOff()	dmxpow->TurnOff()
#define eurdiv_iPresent() (eurdiv.Present())
#define eurdiv_iVersion	eurdiv->iVersion()
#define eurdiv_sdmWaitTime() eurdiv->sdmWaitTime()
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
#define hsvdvbcamsdm_pow_iPresent() (hsvdvbcamsdm_pow.Present())
#define hsvdvbcamsdm_pow_Init()	hsvdvbcamsdm_pow->Init()
#define hsvdvbcamsdm_pow_TurnOn()	hsvdvbcamsdm_pow->TurnOn()
#define hsvdvbcamsdm_pow_TurnOff()	hsvdvbcamsdm_pow->TurnOff()
#define hsvdvbcamsdm_strmfltr_iPresent() (hsvdvbcamsdm_strmfltr.Present())
#define hsvdvbcamsdm_strmfltr_IsSet(dest,filterid,value)	hsvdvbcamsdm_strmfltr->IsSet(dest,filterid,value)
#define hsvdvbcamsdm_strmfltr_IsReady(dest,filterid)	hsvdvbcamsdm_strmfltr->IsReady(dest,filterid)
#define hsvdvbcamsdm_strmfltr_Set(dest,filterid,value)	hsvdvbcamsdm_strmfltr->Set(dest,filterid,value)
#define hsvdvbcamsdm_strmfltr_Clear(dest,filterid,value)	hsvdvbcamsdm_strmfltr->Clear(dest,filterid,value)
#define hsvdvbcamsdm_strmfltr_ForceClear(dest,filterid,value)	hsvdvbcamsdm_strmfltr->ForceClear(dest,filterid,value)
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
#define hsvdvbsi_strmfltr_ForceClear(dest,filterid,value)	hsvdvbsi_strmfltr->ForceClear(dest,filterid,value)
#define hsvmpeg_enable_iPresent() (hsvmpeg_enable.Present())
#define hsvmpeg_enable_Enable(dmx)	hsvmpeg_enable->Enable(dmx)
#define hsvmpeg_enable_Disable(dmx)	hsvmpeg_enable->Disable(dmx)
#define hsvmpeg_enable_Sync(dmx)	hsvmpeg_enable->Sync(dmx)
#define hsvmpeg_mpegsecn_iPresent() (hsvmpeg_mpegsecn.Present())
#define hsvmpeg_mpegsecn_GetNumberofPrograms(dmx)	hsvmpeg_mpegsecn->GetNumberofPrograms(dmx)
#define hsvmpeg_mpegsecn_GetProgramNumber(dmx,indx)	hsvmpeg_mpegsecn->GetProgramNumber(dmx,indx)
#define hsvmpeg_mpegsecn_GetComponentInfobyProgramNumber(dmx,prg,ci)	hsvmpeg_mpegsecn->GetComponentInfobyProgramNumber(dmx,prg,ci)
#define hsvmpeg_mpegsecn_GetComponentInfobyIndex(dmx,indx,ci)	hsvmpeg_mpegsecn->GetComponentInfobyIndex(dmx,indx,ci)
#define hsvmpeg_mpegsecn_GetCurrentTsId(dmx)	hsvmpeg_mpegsecn->GetCurrentTsId(dmx)
#define hsvmpeg_mpegsecn_GetPmtSection(dmx,prg)	hsvmpeg_mpegsecn->GetPmtSection(dmx,prg)
#define hsvmpeg_mpegsecn_MonitorProgram(dmx,prg)	hsvmpeg_mpegsecn->MonitorProgram(dmx,prg)
#define hsvmpeg_mpegsecn_MonitorProgram2(dmx,prg)	hsvmpeg_mpegsecn->MonitorProgram2(dmx,prg)
#define hsvmpeg_mpegsecn_MonitorProgramByIndex(dmx,prg,index)	hsvmpeg_mpegsecn->MonitorProgramByIndex(dmx,prg,index)
#define hsvmpeg_pow_iPresent() (hsvmpeg_pow.Present())
#define hsvmpeg_pow_Init()	hsvmpeg_pow->Init()
#define hsvmpeg_pow_TurnOn()	hsvmpeg_pow->TurnOn()
#define hsvmpeg_pow_TurnOff()	hsvmpeg_pow->TurnOff()
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
#define ins_GetNumberOfChannelListIds()	ins->GetNumberOfChannelListIds()
#define ins_GetChannelListIdByIndex(index)	ins->GetChannelListIdByIndex(index)
#define ins_SetFavouriteChannelListId(mode,attrib,index)	ins->SetFavouriteChannelListId(mode,attrib,index)
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
#define istrapi_iPresent() (istrapi.Present())
#define istrapi_GetSize(dest,spid)	istrapi->GetSize(dest,spid)
#define istrapi_GetIndex(dest,spid,key1,key2,key3,index)	istrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define istrapi_GetByKey(dest,spid,key1,key2,key3,val)	istrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define istrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	istrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define istrapi_GetByIndex(dest,spid,index,val)	istrapi->GetByIndex(dest,spid,index,val)
#define mpegsecnN_iPresent() (mpegsecnN.Present())
#define mpegsecnN_PmtData	IHsvMpegSectionsNotify_PmtData
#define mpegsecnN_PmtAcquisitionComplete	IHsvMpegSectionsNotify_PmtAcquisitionComplete
#define mpegsecnN_OnChanged(dmx,value,eventid)	mpegsecnN->OnChanged(dmx,value,eventid)
#define mpegsecnN_OnAdded(dmx,value,eventid)	mpegsecnN->OnAdded(dmx,value,eventid)
#define mpegsecnN_OnRemoved(dmx,value,eventid)	mpegsecnN->OnRemoved(dmx,value,eventid)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbStreamingDataManager_m_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define secfltr_iPresent() (secfltr.Present())
#define secfltr_SctArrived	IHsvDemuxSectionFilter2_SctArrived
#define secfltr_TableCompleted	IHsvDemuxSectionFilter2_TableCompleted
#define secfltr_SectionDepth	secfltr->SectionDepth()
#define secfltr_IsRequestAllowed(dest)	secfltr->IsRequestAllowed(dest)
#define secfltr_RequestSection(dest,pid,tableid,cookie,sctCallback)	secfltr->RequestSection(dest,pid,tableid,cookie,sctCallback)
#define secfltr_RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback)	secfltr->RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback)
#define secfltr_RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback)	secfltr->RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback)
#define secfltr_ResetRequest(dest,subscrId)	secfltr->ResetRequest(dest,subscrId)
#define secfltr_CancelSection(dest,subscrId)	secfltr->CancelSection(dest,subscrId)
#define secfltr_RequestPes(dest,pid,cookie,pesCallback)	secfltr->RequestPes(dest,pid,cookie,pesCallback)
#define secfltr_CancelPes(dest,subscrId)	secfltr->CancelPes(dest,subscrId)
#define secfltr_RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)	secfltr->RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)
#define secfltr_UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray)	secfltr->UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray)
#define secfltr_RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)	secfltr->RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)
#define secfltr_RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength)	secfltr->RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength)
#define secfltr_GetBits(sectionid,numbits)	secfltr->GetBits(sectionid,numbits)
#define secfltr_ShowBits(sectionid,numbits)	secfltr->ShowBits(sectionid,numbits)
#define secfltr_SkipBits(sectionid,numbits)	secfltr->SkipBits(sectionid,numbits)
#define secfltr_AlignToNextByte(sectionid)	secfltr->AlignToNextByte(sectionid)
#define secfltr_IsEndOfSection(sectionid)	secfltr->IsEndOfSection(sectionid)
#define secfltr_GetBitsRead(sectionid)	secfltr->GetBitsRead(sectionid)
#define secfltr_GetBitsUnread(sectionid)	secfltr->GetBitsUnread(sectionid)
#define secfltr_GetSectionBuffer(sectionid)	secfltr->GetSectionBuffer(sectionid)
#define secfltr_GetSectionLength(sectionid)	secfltr->GetSectionLength(sectionid)
#define secfltr_CheckandCancelSection(dest,PidValue)	secfltr->CheckandCancelSection(dest,PidValue)
#ifdef secfltr_RequestSectionFilter
#undef secfltr_RequestSectionFilter
#endif
#ifdef secfltr_RequestSectionFilterList
#undef secfltr_RequestSectionFilterList
#endif
#ifdef secfltr_RequestSection
#undef secfltr_RequestSection
#endif
#ifdef secfltr_RequestSection2
#undef secfltr_RequestSection2
#endif
#ifdef secfltr_RequestSection3
#undef secfltr_RequestSection3
#endif
#ifdef secfltr_RequestPes
#undef secfltr_RequestPes
#endif
#ifdef secfltr_RequestPesList
#undef secfltr_RequestPesList
#endif
#ifdef secfltr_CancelSection
#undef secfltr_CancelSection
#endif
#ifdef secfltr_CancelPes
#undef secfltr_CancelPes
#endif
#define secfltr_RequestSectionFilter dmxlocal_RequestSectionFilter
#define secfltr_RequestSectionFilterList dmxlocal_RequestSectionFilterList
#define secfltr_RequestSection dmxlocal_RequestSection
#define secfltr_RequestSection2 dmxlocal_RequestSection2
#define secfltr_RequestSection3 dmxlocal_RequestSection3
#define secfltr_RequestPes dmxlocal_RequestPes
#define secfltr_RequestPesList dmxlocal_RequestPesList
#define secfltr_CancelSection dmxlocal_CancelSection
#define secfltr_CancelPes dmxlocal_CancelPes
#define strmfltrN_iPresent() (strmfltrN.Present())
#define strmfltrN_OnReady(dest,filterid)	strmfltrN->OnReady(dest,filterid)
#define sysset_iPresent() (sysset.Present())
#define sysset_AudioFormatStandard	IHsvTcSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvTcSystemSettings_AudioFormatAdvanced
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
#define conf_Notifications	IHsvDVBSIConfig_Notifications
#define conf_CurrentCountry	i__conf.m_CurrentCountry
#define ctrl_Idle	IHsvSdmControl2_Idle
#define ctrl_Minimal	IHsvSdmControl2_Minimal
#define ctrl_Normal	IHsvSdmControl2_Normal
#define ctrl_External	IHsvSdmControl2_External
#define ctrl_CrossCarraige	IHsvSdmControl2_CrossCarraige
#define ctrl_Invalid	IHsvSdmControl2_Invalid
#define ctrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ctrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ctrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ctrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ctrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
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
#define hsvmpeg_mpegsecnN_PmtData	IHsvMpegSectionsNotify_PmtData
#define hsvmpeg_mpegsecnN_PmtAcquisitionComplete	IHsvMpegSectionsNotify_PmtAcquisitionComplete
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

