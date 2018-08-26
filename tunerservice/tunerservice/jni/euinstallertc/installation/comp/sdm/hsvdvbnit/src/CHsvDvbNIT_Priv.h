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
#include <IHsvInstallation2.h>
#include <IHsvMpegServices.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvTcSystemSettings.h>
#include <CTCMwBase.h>
class CHsvDvbNIT_Priv;
#define CLASSSCOPE CHsvDvbNIT_Priv::
#include "locals_m.h"

class CHsvDvbNIT_Priv : public CTCMwBase
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
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitcablemainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitcablesubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitfreqlistconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nithdslcnmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nithdslcnsubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcn2mainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcn2subconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcnmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcnsubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlinkmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlinksubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitntwkidconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitsrvcatrbmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitsrvclstmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitsrvclstsubconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nittargetregionconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nittargetregionnameconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nittsrelocatemainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitlcn2favoriteconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbNIT_Priv,nitactualtsidconf);

IHsvPowerImpl(CHsvDvbNIT_Priv,pow);
IHsvStreamImpl(CHsvDvbNIT_Priv,strapi);
IHsvStreamFilterImpl(CHsvDvbNIT_Priv,strmfltr);
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitcablemainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitcablesubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitfreqlistconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2mainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2subconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinkmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinksubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitntwkidconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvcatrbmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nittargetregionconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nittargetregionnameconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nittsrelocatemainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2favoriteconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitactualtsidconf;

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
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
private:
DEMUX_DEFINES(CHsvDvbNIT_Priv,sec);

public:
CHsvDvbNIT_Priv():i__dmxsecfN(this),i__ena(this),i__nitcablemainconf(this),i__nitcablesubconf(this),i__nitfreqlistconf(this),i__nithdslcnmainconf(this),i__nithdslcnsubconf(this),i__nitlcn2mainconf(this),i__nitlcn2subconf(this),i__nitlcnmainconf(this),i__nitlcnsubconf(this),i__nitlinkmainconf(this),i__nitlinksubconf(this),i__nitntwkidconf(this),i__nitsrvcatrbmainconf(this),i__nitsrvclstmainconf(this),i__nitsrvclstsubconf(this),i__nitlcn2favoriteconf(this),i__nittargetregionconf(this),i__nittargetregionnameconf(this),i__nittsrelocatemainconf(this),i__pow(this),i__strapi(this),i__strmfltr(this),i__nitactualtsidconf(this)
{
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
nitcablemainconf	=	&i__nitcablemainconf;
nitcablesubconf	=	&i__nitcablesubconf;
nitfreqlistconf	=	&i__nitfreqlistconf;
nithdslcnmainconf	=	&i__nithdslcnmainconf;
nithdslcnsubconf	=	&i__nithdslcnsubconf;
nitlcn2mainconf	=	&i__nitlcn2mainconf;
nitlcn2subconf	=	&i__nitlcn2subconf;
nitlcnmainconf	=	&i__nitlcnmainconf;
nitlcnsubconf	=	&i__nitlcnsubconf;
nitlinkmainconf	=	&i__nitlinkmainconf;
nitlinksubconf	=	&i__nitlinksubconf;
nitntwkidconf	=	&i__nitntwkidconf;
nitsrvcatrbmainconf	=	&i__nitsrvcatrbmainconf;
nitsrvclstmainconf	=	&i__nitsrvclstmainconf;
nitsrvclstsubconf	=	&i__nitsrvclstsubconf;
nittargetregionconf	=	&i__nittargetregionconf;
nittargetregionnameconf	=	&i__nittargetregionnameconf;
nittsrelocatemainconf	=	&i__nittsrelocatemainconf;
nitlcn2favoriteconf	=	&i__nitlcn2favoriteconf;
nitactualtsidconf	=	&i__nitactualtsidconf;

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
#define cids_CountryParaguay	IHsvCountryIds_CountryParaguay
#define cids_CountryUruguay	IHsvCountryIds_CountryUruguay
#define cids_CountryThailand	IHsvCountryIds_CountryThailand
#define cids_CountryNewZealand	IHsvCountryIds_CountryNewZealand
#define cids_CountrySingapore	IHsvCountryIds_CountrySingapore
#define cids_CountryMalaysia	IHsvCountryIds_CountryMalaysia
#define cids_CountryTaiwan	IHsvCountryIds_CountryTaiwan
#define cids_CountryIndonesia	IHsvCountryIds_CountryIndonesia
#define cids_CountryUAE	IHsvCountryIds_CountryUAE
#define cids_CountryVietnam	IHsvCountryIds_CountryVietnam
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
#define ins_CanalDigital	IHsvInstallation2_CanalDigital
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
#define mpegserv_iPresent() (mpegserv.Present())
#define mpegserv_GetLanguageId(byte1,byte2,byte3)	mpegserv->GetLanguageId(byte1,byte2,byte3)
#define mpegserv_IsProgramPresent(dmx,prg)	mpegserv->IsProgramPresent(dmx,prg)
#define mpegserv_ReadTsPacketFields(subscr_id,sec)	mpegserv->ReadTsPacketFields(subscr_id,sec)
#define mpegserv_GetCcDescriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetCcDescriptor(dmx,prg,IsDescriptorParsed)
#define mpegserv_GetCaDescriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetCaDescriptor(dmx,prg,IsDescriptorParsed)
#define mpegserv_GetAc3Descriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetAc3Descriptor(dmx,prg,IsDescriptorParsed)
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
#define srtdb_SearchOnPrimarySecondaryAndTeritiaryKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,from,to)	srtdb->SearchOnPrimarySecondaryAndTeritiaryKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,from,to)
#define srtdb_QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_QueryOnIndex(tableid,index,data)	srtdb->QueryOnIndex(tableid,index,data)
#define srtdb_SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)	srtdb->SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)
#define srtdb_SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)	srtdb->SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)
#define srtdbids_NitLcnTableMain	 reinterpret_cast<int>(&i__nitlcnmainconf)
#define srtdbids_NitLinkageInfoMain	 reinterpret_cast<int>(&i__nitlinkmainconf)
#define srtdbids_NitCableDSMain	 reinterpret_cast<int>(&i__nitcablemainconf)
#define srtdbids_NitTsRelocateTableMain	 reinterpret_cast<int>(&i__nittsrelocatemainconf)
#define srtdbids_NitSrvclstTableMain	 reinterpret_cast<int>(&i__nitsrvclstmainconf)
#define srtdbids_NitLCN2Favorite	 reinterpret_cast<int>(&i__nitlcn2favoriteconf)
#define srtdbids_NitLcn2TableMain	 reinterpret_cast<int>(&i__nitlcn2mainconf)
#define srtdbids_NitHDSLcnTableMain	 reinterpret_cast<int>(&i__nithdslcnmainconf)
#define srtdbids_NitOtherNetworkIdTable	 reinterpret_cast<int>(&i__nitntwkidconf)
#define srtdbids_NitLcnTableSub	 reinterpret_cast<int>(&i__nitlcnsubconf)
#define srtdbids_NitLinkageInfoSub	 reinterpret_cast<int>(&i__nitlinksubconf)
#define srtdbids_NitCableDSSub	 reinterpret_cast<int>(&i__nitcablesubconf)
#define srtdbids_NitLcn2TableSub	 reinterpret_cast<int>(&i__nitlcn2subconf)
#define srtdbids_NitSrvclstTableSub	 reinterpret_cast<int>(&i__nitsrvclstsubconf)
#define srtdbids_NitSrvcAtrbTableMain	 reinterpret_cast<int>(&i__nitsrvcatrbmainconf)
#define srtdbids_NitFreqList	 reinterpret_cast<int>(&i__nitfreqlistconf)
#define srtdbids_NitHDSLcnTableSub	 reinterpret_cast<int>(&i__nithdslcnsubconf)
#define srtdbids_NitTargetRegion	 reinterpret_cast<int>(&i__nittargetregionconf)
#define srtdbids_NitTargetRegionName	 reinterpret_cast<int>(&i__nittargetregionnameconf)
#define srtdbids_NitActualTsId	 reinterpret_cast<int>(&i__nitactualtsidconf)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
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
#define nitcablemainconf_MaxElements	i__nitcablemainconf.m_MaxElements
#define nitcablemainconf_ElementSize	i__nitcablemainconf.m_ElementSize
#define nitcablemainconf_ThreadSafe	i__nitcablemainconf.m_ThreadSafe
#define nitcablemainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitcablemainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitcablemainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitcablemainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitcablemainconf_SortCriteria	i__nitcablemainconf.m_SortCriteria
#define nitcablemainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitcablemainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitcablemainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitcablesubconf_MaxElements	i__nitcablesubconf.m_MaxElements
#define nitcablesubconf_ElementSize	i__nitcablesubconf.m_ElementSize
#define nitcablesubconf_ThreadSafe	i__nitcablesubconf.m_ThreadSafe
#define nitcablesubconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitcablesubconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitcablesubconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitcablesubconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitcablesubconf_SortCriteria	i__nitcablesubconf.m_SortCriteria
#define nitcablesubconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitcablesubconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitcablesubconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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
#define nitsrvcatrbmainconf_MaxElements	i__nitsrvcatrbmainconf.m_MaxElements
#define nitsrvcatrbmainconf_ElementSize	i__nitsrvcatrbmainconf.m_ElementSize
#define nitsrvcatrbmainconf_ThreadSafe	i__nitsrvcatrbmainconf.m_ThreadSafe
#define nitsrvcatrbmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitsrvcatrbmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitsrvcatrbmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitsrvcatrbmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitsrvcatrbmainconf_SortCriteria	i__nitsrvcatrbmainconf.m_SortCriteria
#define nitsrvcatrbmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitsrvcatrbmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitsrvcatrbmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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
#define nittargetregionconf_MaxElements	i__nittargetregionconf.m_MaxElements
#define nittargetregionconf_ElementSize	i__nittargetregionconf.m_ElementSize
#define nittargetregionconf_ThreadSafe	i__nittargetregionconf.m_ThreadSafe
#define nittargetregionconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nittargetregionconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nittargetregionconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nittargetregionconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nittargetregionconf_SortCriteria	i__nittargetregionconf.m_SortCriteria
#define nittargetregionconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nittargetregionconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nittargetregionconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nittargetregionnameconf_MaxElements	i__nittargetregionnameconf.m_MaxElements
#define nittargetregionnameconf_ElementSize	i__nittargetregionnameconf.m_ElementSize
#define nittargetregionnameconf_ThreadSafe	i__nittargetregionnameconf.m_ThreadSafe
#define nittargetregionnameconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nittargetregionnameconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nittargetregionnameconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nittargetregionnameconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nittargetregionnameconf_SortCriteria	i__nittargetregionnameconf.m_SortCriteria
#define nittargetregionnameconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nittargetregionnameconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nittargetregionnameconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nittsrelocatemainconf_MaxElements	i__nittsrelocatemainconf.m_MaxElements
#define nittsrelocatemainconf_ElementSize	i__nittsrelocatemainconf.m_ElementSize
#define nittsrelocatemainconf_ThreadSafe	i__nittsrelocatemainconf.m_ThreadSafe
#define nittsrelocatemainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nittsrelocatemainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nittsrelocatemainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nittsrelocatemainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nittsrelocatemainconf_SortCriteria	i__nittsrelocatemainconf.m_SortCriteria
#define nittsrelocatemainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nittsrelocatemainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nittsrelocatemainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitlcn2favoriteconf_MaxElements	i__nitlcn2favoriteconf.m_MaxElements
#define nitlcn2favoriteconf_ElementSize	i__nitlcn2favoriteconf.m_ElementSize
#define nitlcn2favoriteconf_ThreadSafe	i__nitlcn2favoriteconf.m_ThreadSafe
#define nitlcn2favoriteconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitlcn2favoriteconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitlcn2favoriteconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define nitlcn2favoriteconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define nitlcn2favoriteconf_SortCriteria	i__nitlcn2favoriteconf.m_SortCriteria
#define nitlcn2favoriteconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitlcn2favoriteconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitlcn2favoriteconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define nitactualtsidconf_MaxElements	i__nitactualtsidconf.m_MaxElements
#define nitactualtsidconf_ElementSize	i__nitactualtsidconf.m_ElementSize
#define nitactualtsidconf_ThreadSafe	i__nitactualtsidconf.m_ThreadSafe
#define nitactualtsidconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define nitactualtsidconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define nitactualtsidconf_SortCriteria	i__nitactualtsidconf.m_SortCriteria
#define nitactualtsidconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define nitactualtsidconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define nitactualtsidconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey


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

