#ifndef  _CHSVDVBNIT_PRIV_H
#define  _CHSVDVBNIT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSdmControl2.h>
#include <IHsvSatelliteFrontEnd.h>
#include <CS2MwBase.h>
class CHsvDvbNIT_Priv;
#define CLASSSCOPE CHsvDvbNIT_Priv::
#include "locals_m.h"

class CHsvDvbNIT_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbNIT_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbNIT_Priv,dmxsecfN);
IHsvSdmEnableImpl(CHsvDvbNIT_Priv,ena);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitHeadEndFrequencyListconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitfreqlistconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nithdslcnmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nithdslcnsubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcn2mainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcn2subconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcn3mainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcnmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcnsubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlinkmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlinksubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitntwkidconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitsatellitedsdconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitsrvclstmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitsrvclstsubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitFreesatLinkageconf);
IHsvPowerImpl(CHsvDvbNIT_Priv,pow);
IHsvStreamImpl(CHsvDvbNIT_Priv,strapi);
IHsvStreamFilterImpl(CHsvDvbNIT_Priv,strmfltr);
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitHeadEndFrequencyListconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitfreqlistconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2mainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2subconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn3mainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinkmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinksubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitntwkidconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsatellitedsdconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitFreesatLinkageconf;
ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IHsvSdmControl2>	ctrl;
private:
DEMUX_DEFINES(CHsvDvbNIT_Priv,sec);

public:
CHsvDvbNIT_Priv():i__dmxsecfN(this),i__ena(this),i__nitHeadEndFrequencyListconf(this),i__nitfreqlistconf(this),i__nithdslcnmainconf(this),i__nithdslcnsubconf(this),i__nitlcn2mainconf(this),i__nitlcn2subconf(this),i__nitlcn3mainconf(this),i__nitlcnmainconf(this),i__nitlcnsubconf(this),i__nitlinkmainconf(this),i__nitlinksubconf(this),i__nitntwkidconf(this),i__nitsatellitedsdconf(this),i__nitsrvclstmainconf(this),i__nitsrvclstsubconf(this),i__nitFreesatLinkageconf(this),i__pow(this),i__strapi(this),i__strmfltr(this)
{
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
nitHeadEndFrequencyListconf	=	&i__nitHeadEndFrequencyListconf;
nitfreqlistconf	=	&i__nitfreqlistconf;
nithdslcnmainconf	=	&i__nithdslcnmainconf;
nithdslcnsubconf	=	&i__nithdslcnsubconf;
nitlcn2mainconf	=	&i__nitlcn2mainconf;
nitlcn2subconf	=	&i__nitlcn2subconf;
nitlcn3mainconf	=	&i__nitlcn3mainconf;
nitlcnmainconf	=	&i__nitlcnmainconf;
nitlcnsubconf	=	&i__nitlcnsubconf;
nitlinkmainconf	=	&i__nitlinkmainconf;
nitlinksubconf	=	&i__nitlinksubconf;
nitntwkidconf	=	&i__nitntwkidconf;
nitsatellitedsdconf	=	&i__nitsatellitedsdconf;
nitsrvclstmainconf	=	&i__nitsrvclstmainconf;
nitsrvclstsubconf	=	&i__nitsrvclstsubconf;
nitFreesatLinkageconf	=	&i__nitFreesatLinkageconf;
pow	=	&i__pow;
strapi	=	&i__strapi;
strmfltr	=	&i__strmfltr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_ExtractNone	IHsvCharSetUtility2_ExtractNone
#define charsetutil_ExtractShortName	IHsvCharSetUtility2_ExtractShortName
#define charsetutil_ExtractEITShortEvent	IHsvCharSetUtility2_ExtractEITShortEvent
#define charsetutil_ExtractEITExtendedEvent	IHsvCharSetUtility2_ExtractEITExtendedEvent
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,exinfo)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,exinfo)
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
#define conf_BatParsing	IHsvDVBSIConfig_BatParsing
#define conf_FntParsing	IHsvDVBSIConfig_FntParsing
#define conf_FstParsing	IHsvDVBSIConfig_FstParsing
#define conf_Notifications	IHsvDVBSIConfig_Notifications
#define conf_CurrentCountry	conf->CurrentCountry()
#define conf_IsActionAllowed(dmx,table)	conf->IsActionAllowed(dmx,table)
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
#define ctrlN_OnEvent(dmx,eventid,value)	ctrlN->OnEvent(dmx,eventid,value)
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
#define srtdbids_NitLcnTableMain	 reinterpret_cast<int>(&i__nitlcnmainconf)
#define srtdbids_NitLcnTableSub	 reinterpret_cast<int>(&i__nitlcnsubconf)
#define srtdbids_NitLinkageInfoMain	 reinterpret_cast<int>(&i__nitlinkmainconf)
#define srtdbids_NitLinkageInfoSub	 reinterpret_cast<int>(&i__nitlinksubconf)
#define srtdbids_NitSatelliteDS	 reinterpret_cast<int>(&i__nitsatellitedsdconf)
#define srtdbids_NitOtherNetworkIdTable	 reinterpret_cast<int>(&i__nitntwkidconf)
#define srtdbids_NitFreqList	 reinterpret_cast<int>(&i__nitfreqlistconf)
#define srtdbids_NitLcn2TableMain	 reinterpret_cast<int>(&i__nitlcn2mainconf)
#define srtdbids_NitLcn2TableSub	 reinterpret_cast<int>(&i__nitlcn2subconf)
#define srtdbids_NitHDSLcnTableMain	 reinterpret_cast<int>(&i__nithdslcnmainconf)
#define srtdbids_NitHDSLcnTableSub	 reinterpret_cast<int>(&i__nithdslcnsubconf)
#define srtdbids_NitSrvclstTableMain	 reinterpret_cast<int>(&i__nitsrvclstmainconf)
#define srtdbids_NitSrvclstTableSub	 reinterpret_cast<int>(&i__nitsrvclstsubconf)
#define srtdbids_NitLcn3TableMain	 reinterpret_cast<int>(&i__nitlcn3mainconf)
#define srtdbids_NitHeadEndFrequencyList	 reinterpret_cast<int>(&i__nitHeadEndFrequencyListconf)
#define srtdbids_NitFreesatLinkageInfo	 reinterpret_cast<int>(&i__nitFreesatLinkageconf)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
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
#define nitHeadEndFrequencyListconf_MaxElements	i__nitHeadEndFrequencyListconf.m_MaxElements
#define nitHeadEndFrequencyListconf_ElementSize	i__nitHeadEndFrequencyListconf.m_ElementSize
#define nitHeadEndFrequencyListconf_ThreadSafe	i__nitHeadEndFrequencyListconf.m_ThreadSafe
#define nitHeadEndFrequencyListconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitHeadEndFrequencyListconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitHeadEndFrequencyListconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitHeadEndFrequencyListconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitHeadEndFrequencyListconf_SortCriteria	i__nitHeadEndFrequencyListconf.m_SortCriteria
#define nitHeadEndFrequencyListconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitHeadEndFrequencyListconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitHeadEndFrequencyListconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitfreqlistconf_MaxElements	i__nitfreqlistconf.m_MaxElements
#define nitfreqlistconf_ElementSize	i__nitfreqlistconf.m_ElementSize
#define nitfreqlistconf_ThreadSafe	i__nitfreqlistconf.m_ThreadSafe
#define nitfreqlistconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitfreqlistconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitfreqlistconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitfreqlistconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitfreqlistconf_SortCriteria	i__nitfreqlistconf.m_SortCriteria
#define nitfreqlistconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitfreqlistconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitfreqlistconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nithdslcnmainconf_MaxElements	i__nithdslcnmainconf.m_MaxElements
#define nithdslcnmainconf_ElementSize	i__nithdslcnmainconf.m_ElementSize
#define nithdslcnmainconf_ThreadSafe	i__nithdslcnmainconf.m_ThreadSafe
#define nithdslcnmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nithdslcnmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nithdslcnmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nithdslcnmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nithdslcnmainconf_SortCriteria	i__nithdslcnmainconf.m_SortCriteria
#define nithdslcnmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nithdslcnmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nithdslcnmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nithdslcnsubconf_MaxElements	i__nithdslcnsubconf.m_MaxElements
#define nithdslcnsubconf_ElementSize	i__nithdslcnsubconf.m_ElementSize
#define nithdslcnsubconf_ThreadSafe	i__nithdslcnsubconf.m_ThreadSafe
#define nithdslcnsubconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nithdslcnsubconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nithdslcnsubconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nithdslcnsubconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nithdslcnsubconf_SortCriteria	i__nithdslcnsubconf.m_SortCriteria
#define nithdslcnsubconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nithdslcnsubconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nithdslcnsubconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlcn2mainconf_MaxElements	i__nitlcn2mainconf.m_MaxElements
#define nitlcn2mainconf_ElementSize	i__nitlcn2mainconf.m_ElementSize
#define nitlcn2mainconf_ThreadSafe	i__nitlcn2mainconf.m_ThreadSafe
#define nitlcn2mainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlcn2mainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlcn2mainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlcn2mainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlcn2mainconf_SortCriteria	i__nitlcn2mainconf.m_SortCriteria
#define nitlcn2mainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlcn2mainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlcn2mainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlcn2subconf_MaxElements	i__nitlcn2subconf.m_MaxElements
#define nitlcn2subconf_ElementSize	i__nitlcn2subconf.m_ElementSize
#define nitlcn2subconf_ThreadSafe	i__nitlcn2subconf.m_ThreadSafe
#define nitlcn2subconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlcn2subconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlcn2subconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlcn2subconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlcn2subconf_SortCriteria	i__nitlcn2subconf.m_SortCriteria
#define nitlcn2subconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlcn2subconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlcn2subconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlcn3mainconf_MaxElements	i__nitlcn3mainconf.m_MaxElements
#define nitlcn3mainconf_ElementSize	i__nitlcn3mainconf.m_ElementSize
#define nitlcn3mainconf_ThreadSafe	i__nitlcn3mainconf.m_ThreadSafe
#define nitlcn3mainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlcn3mainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlcn3mainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlcn3mainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlcn3mainconf_SortCriteria	i__nitlcn3mainconf.m_SortCriteria
#define nitlcn3mainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlcn3mainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlcn3mainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlcnmainconf_MaxElements	i__nitlcnmainconf.m_MaxElements
#define nitlcnmainconf_ElementSize	i__nitlcnmainconf.m_ElementSize
#define nitlcnmainconf_ThreadSafe	i__nitlcnmainconf.m_ThreadSafe
#define nitlcnmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlcnmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlcnmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlcnmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlcnmainconf_SortCriteria	i__nitlcnmainconf.m_SortCriteria
#define nitlcnmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlcnmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlcnmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlcnsubconf_MaxElements	i__nitlcnsubconf.m_MaxElements
#define nitlcnsubconf_ElementSize	i__nitlcnsubconf.m_ElementSize
#define nitlcnsubconf_ThreadSafe	i__nitlcnsubconf.m_ThreadSafe
#define nitlcnsubconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlcnsubconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlcnsubconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlcnsubconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlcnsubconf_SortCriteria	i__nitlcnsubconf.m_SortCriteria
#define nitlcnsubconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlcnsubconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlcnsubconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlinkmainconf_MaxElements	i__nitlinkmainconf.m_MaxElements
#define nitlinkmainconf_ElementSize	i__nitlinkmainconf.m_ElementSize
#define nitlinkmainconf_ThreadSafe	i__nitlinkmainconf.m_ThreadSafe
#define nitlinkmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlinkmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlinkmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlinkmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlinkmainconf_SortCriteria	i__nitlinkmainconf.m_SortCriteria
#define nitlinkmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlinkmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlinkmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlinksubconf_MaxElements	i__nitlinksubconf.m_MaxElements
#define nitlinksubconf_ElementSize	i__nitlinksubconf.m_ElementSize
#define nitlinksubconf_ThreadSafe	i__nitlinksubconf.m_ThreadSafe
#define nitlinksubconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlinksubconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlinksubconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlinksubconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlinksubconf_SortCriteria	i__nitlinksubconf.m_SortCriteria
#define nitlinksubconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlinksubconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlinksubconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitntwkidconf_MaxElements	i__nitntwkidconf.m_MaxElements
#define nitntwkidconf_ElementSize	i__nitntwkidconf.m_ElementSize
#define nitntwkidconf_ThreadSafe	i__nitntwkidconf.m_ThreadSafe
#define nitntwkidconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitntwkidconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitntwkidconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitntwkidconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitntwkidconf_SortCriteria	i__nitntwkidconf.m_SortCriteria
#define nitntwkidconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitntwkidconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitntwkidconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitsatellitedsdconf_MaxElements	i__nitsatellitedsdconf.m_MaxElements
#define nitsatellitedsdconf_ElementSize	i__nitsatellitedsdconf.m_ElementSize
#define nitsatellitedsdconf_ThreadSafe	i__nitsatellitedsdconf.m_ThreadSafe
#define nitsatellitedsdconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitsatellitedsdconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitsatellitedsdconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitsatellitedsdconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitsatellitedsdconf_SortCriteria	i__nitsatellitedsdconf.m_SortCriteria
#define nitsatellitedsdconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitsatellitedsdconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitsatellitedsdconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitsrvclstmainconf_MaxElements	i__nitsrvclstmainconf.m_MaxElements
#define nitsrvclstmainconf_ElementSize	i__nitsrvclstmainconf.m_ElementSize
#define nitsrvclstmainconf_ThreadSafe	i__nitsrvclstmainconf.m_ThreadSafe
#define nitsrvclstmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitsrvclstmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitsrvclstmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitsrvclstmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitsrvclstmainconf_SortCriteria	i__nitsrvclstmainconf.m_SortCriteria
#define nitsrvclstmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitsrvclstmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitsrvclstmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitsrvclstsubconf_MaxElements	i__nitsrvclstsubconf.m_MaxElements
#define nitsrvclstsubconf_ElementSize	i__nitsrvclstsubconf.m_ElementSize
#define nitsrvclstsubconf_ThreadSafe	i__nitsrvclstsubconf.m_ThreadSafe
#define nitsrvclstsubconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitsrvclstsubconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitsrvclstsubconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitsrvclstsubconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitsrvclstsubconf_SortCriteria	i__nitsrvclstsubconf.m_SortCriteria
#define nitsrvclstsubconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitsrvclstsubconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitsrvclstsubconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitFreesatLinkageconf_MaxElements	i__nitFreesatLinkageconf.m_MaxElements
#define nitFreesatLinkageconf_ElementSize	i__nitFreesatLinkageconf.m_ElementSize
#define nitFreesatLinkageconf_ThreadSafe		i__nitFreesatLinkageconf.m_ThreadSafe
#define nitFreesatLinkageconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitFreesatLinkageconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitFreesatLinkageconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitFreesatLinkageconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitFreesatLinkageconf_SortCriteria	i__nitFreesatLinkageconf.m_SortCriteria
#define nitFreesatLinkageconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitFreesatLinkageconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitFreesatLinkageconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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

