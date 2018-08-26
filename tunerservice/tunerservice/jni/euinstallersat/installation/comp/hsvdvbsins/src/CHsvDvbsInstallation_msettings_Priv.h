#ifndef  _CHSVDVBSINSTALLATION_MSETTINGS_PRIV_H
#define  _CHSVDVBSINSTALLATION_MSETTINGS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvPower.h>
#include <IHsvSatelliteInstallationRoute.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSystemSettingsNotify.h>
#include <IAppApiSystemSettingsNotify.h>
#include <IHsvSystemSettings.h>
#include <CS2MwBase.h>

class CHsvDvbsInstallation_msettings_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_msettings_Priv::
#include "locals_msettings.h"

class CHsvDvbsInstallation_msettings_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_msettings_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msettings.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSatelliteSettingsImpl(CHsvDvbsInstallation_msettings_Priv,idvbset);
IHsvPowerImpl(CHsvDvbsInstallation_msettings_Priv,idvbsetpow);
IHsvSatelliteInstallationRouteImpl(CHsvDvbsInstallation_msettings_Priv,insroute);
IHsvSystemSettingsNotifyImpl(CHsvDvbsInstallation_msettings_Priv,sysnotifyN);
public:
ProvidesInterface<IHsvSatelliteSettings>	idvbset;

ProvidesInterface<IHsvPower>	idvbsetpow;

ProvidesInterface<IHsvSatelliteInstallationRoute>	insroute;

ProvidesInterface<IHsvSystemSettingsNotify>	sysnotifyN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatSystemSettings>	sysset;

public:
CHsvDvbsInstallation_msettings_Priv():i__idvbset(this),i__idvbsetpow(this),i__insroute(this),i__sysnotifyN(this)
{
idvbset	=	&i__idvbset;
idvbsetpow	=	&i__idvbsetpow;
insroute	=	&i__insroute;
sysnotifyN	=	&i__sysnotifyN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define apsysset_iPresent() (apsysset.Present())
#define apsysset_Success	IAppApiSystemSettings5_Success
#define apsysset_NVMFailure	IAppApiSystemSettings5_NVMFailure
#define apsysset_CertificateDetectionNotDone	IAppApiSystemSettings5_CertificateDetectionNotDone
#define apsysset_InitFailure	IAppApiSystemSettings5_InitFailure
#define apsysset_AutoEpg	IAppApiSystemSettings5_AutoEpg
#define apsysset_DVBEpg	IAppApiSystemSettings5_DVBEpg
#define apsysset_IPEpg	IAppApiSystemSettings5_IPEpg
#define apsysset_Shop	IAppApiSystemSettings5_Shop
#define apsysset_Home	IAppApiSystemSettings5_Home
#define apsysset_clkSrcNone	IAppApiSystemSettings5_clkSrcNone
#define apsysset_clkSrcMainTuner	IAppApiSystemSettings5_clkSrcMainTuner
#define apsysset_clkSrcSatelliteTuner	IAppApiSystemSettings5_clkSrcSatelliteTuner
#define apsysset_clkSrcManualClock	IAppApiSystemSettings5_clkSrcManualClock
#define apsysset_avSrcNone	IAppApiSystemSettings5_avSrcNone
#define apsysset_avSrcMainTuner	IAppApiSystemSettings5_avSrcMainTuner
#define apsysset_avSrcSatellite	IAppApiSystemSettings5_avSrcSatellite
#define apsysset_avSrcAvIn0	IAppApiSystemSettings5_avSrcAvIn0
#define apsysset_avSrcAvIn1	IAppApiSystemSettings5_avSrcAvIn1
#define apsysset_avSrcAvIn2	IAppApiSystemSettings5_avSrcAvIn2
#define apsysset_avSrcAvIn3	IAppApiSystemSettings5_avSrcAvIn3
#define apsysset_avSrcAvIn4	IAppApiSystemSettings5_avSrcAvIn4
#define apsysset_avSrcAvIn5	IAppApiSystemSettings5_avSrcAvIn5
#define apsysset_avSrcAvIn6	IAppApiSystemSettings5_avSrcAvIn6
#define apsysset_avSrcAvIn7	IAppApiSystemSettings5_avSrcAvIn7
#define apsysset_avSrcAvIn8	IAppApiSystemSettings5_avSrcAvIn8
#define apsysset_avSrcAvIn9	IAppApiSystemSettings5_avSrcAvIn9
#define apsysset_avSrcAvIn10	IAppApiSystemSettings5_avSrcAvIn10
#define apsysset_svcModeNone	IAppApiSystemSettings5_svcModeNone
#define apsysset_svcModeCSM	IAppApiSystemSettings5_svcModeCSM
#define apsysset_svcModeSAM	IAppApiSystemSettings5_svcModeSAM
#define apsysset_svcModeSDM	IAppApiSystemSettings5_svcModeSDM
#define apsysset_svcModeCompair	IAppApiSystemSettings5_svcModeCompair
#define apsysset_svcModeFac	IAppApiSystemSettings5_svcModeFac
#define apsysset_svcModeDigSDM	IAppApiSystemSettings5_svcModeDigSDM
#define apsysset_svcModeBDS	IAppApiSystemSettings5_svcModeBDS
#define apsysset_svcModeRDM	IAppApiSystemSettings5_svcModeRDM
#define apsysset_svcModeBDSSys7	IAppApiSystemSettings5_svcModeBDSSys7
#define apsysset_svcModeFacExit	IAppApiSystemSettings5_svcModeFacExit
#define apsysset_BdsPowStateOn	IAppApiSystemSettings5_BdsPowStateOn
#define apsysset_BdsPowStateStandby	IAppApiSystemSettings5_BdsPowStateStandby
#define apsysset_AudioFormatStandard	IAppApiSystemSettings5_AudioFormatStandard
#define apsysset_AudioFormatAdvanced	IAppApiSystemSettings5_AudioFormatAdvanced
#define apsysset_OsdSizeInvalid	IAppApiSystemSettings5_OsdSizeInvalid
#define apsysset_OsdSizeSmall	IAppApiSystemSettings5_OsdSizeSmall
#define apsysset_OsdSizeLarge	IAppApiSystemSettings5_OsdSizeLarge
#define apsysset_SpainBaleares	IAppApiSystemSettings5_SpainBaleares
#define apsysset_SpainCanaryIsland	IAppApiSystemSettings5_SpainCanaryIsland
#define apsysset_TimeZoneContinental	IAppApiSystemSettings5_TimeZoneContinental
#define apsysset_TimeZoneAzores	IAppApiSystemSettings5_TimeZoneAzores
#define apsysset_TimeZoneKalingrad	IAppApiSystemSettings5_TimeZoneKalingrad
#define apsysset_TimeZoneMoscow	IAppApiSystemSettings5_TimeZoneMoscow
#define apsysset_TimeZoneSamara	IAppApiSystemSettings5_TimeZoneSamara
#define apsysset_TimeZoneYekaterinburg	IAppApiSystemSettings5_TimeZoneYekaterinburg
#define apsysset_TimeZoneOmsk	IAppApiSystemSettings5_TimeZoneOmsk
#define apsysset_TimeZoneKrasnoyarsk	IAppApiSystemSettings5_TimeZoneKrasnoyarsk
#define apsysset_TimeZoneIrkutsk	IAppApiSystemSettings5_TimeZoneIrkutsk
#define apsysset_TimeZoneYakutsk	IAppApiSystemSettings5_TimeZoneYakutsk
#define apsysset_TimeZoneVladivostok	IAppApiSystemSettings5_TimeZoneVladivostok
#define apsysset_TimeZoneMagadan	IAppApiSystemSettings5_TimeZoneMagadan
#define apsysset_TimeZoneKamchatka	IAppApiSystemSettings5_TimeZoneKamchatka
#define apsysset_TimeZoneLatamMinus2	IAppApiSystemSettings5_TimeZoneLatamMinus2
#define apsysset_TimeZoneLatamMinus1	IAppApiSystemSettings5_TimeZoneLatamMinus1
#define apsysset_TimeZoneLatamZero	IAppApiSystemSettings5_TimeZoneLatamZero
#define apsysset_TimeZoneLatamPlus1	IAppApiSystemSettings5_TimeZoneLatamPlus1
#define apsysset_TimeZoneLatamPlus2	IAppApiSystemSettings5_TimeZoneLatamPlus2
#define apsysset_NewSouthWales	IAppApiSystemSettings5_NewSouthWales
#define apsysset_Victoria	IAppApiSystemSettings5_Victoria
#define apsysset_Queensland	IAppApiSystemSettings5_Queensland
#define apsysset_SouthAustralia	IAppApiSystemSettings5_SouthAustralia
#define apsysset_WestAustralia	IAppApiSystemSettings5_WestAustralia
#define apsysset_Tasmania	IAppApiSystemSettings5_Tasmania
#define apsysset_NorthernTerritory	IAppApiSystemSettings5_NorthernTerritory
#define apsysset_ManualClkMode	IAppApiSystemSettings5_ManualClkMode
#define apsysset_AutoClkMode	IAppApiSystemSettings5_AutoClkMode
#define apsysset_CountryDepClkMode	IAppApiSystemSettings5_CountryDepClkMode
#define apsysset_DstOff	IAppApiSystemSettings5_DstOff
#define apsysset_DstOn	IAppApiSystemSettings5_DstOn
#define apsysset_CalStateNotStarted	IAppApiSystemSettings5_CalStateNotStarted
#define apsysset_CalStateInProgress	IAppApiSystemSettings5_CalStateInProgress
#define apsysset_CalStateSuccessfull	IAppApiSystemSettings5_CalStateSuccessfull
#define apsysset_CalStateFailed	IAppApiSystemSettings5_CalStateFailed
#define apsysset_CalStateForced	IAppApiSystemSettings5_CalStateForced
#define apsysset_AutoPowerDownModeOff	IAppApiSystemSettings5_AutoPowerDownModeOff
#define apsysset_AutoPowerDownModeOn	IAppApiSystemSettings5_AutoPowerDownModeOn
#define apsysset_ChannelListAll	IAppApiSystemSettings5_ChannelListAll
#define apsysset_ChannelListTV	IAppApiSystemSettings5_ChannelListTV
#define apsysset_ChannelListRadio	IAppApiSystemSettings5_ChannelListRadio
#define apsysset_ChannelListFavorite	IAppApiSystemSettings5_ChannelListFavorite
#define apsysset_ChannelListAnalog	IAppApiSystemSettings5_ChannelListAnalog
#define apsysset_MediumNone	IAppApiSystemSettings5_MediumNone
#define apsysset_MediumTerrestrial	IAppApiSystemSettings5_MediumTerrestrial
#define apsysset_MediumCable	IAppApiSystemSettings5_MediumCable
#define apsysset_SubtitleNone	IAppApiSystemSettings5_SubtitleNone
#define apsysset_SubtitleOff	IAppApiSystemSettings5_SubtitleOff
#define apsysset_SubtitleOn	IAppApiSystemSettings5_SubtitleOn
#define apsysset_SubtitleOnDuringMute	IAppApiSystemSettings5_SubtitleOnDuringMute
#define apsysset_InvalidPinCode	IAppApiSystemSettings5_InvalidPinCode
#define apsysset_InvalidLastViewed	IAppApiSystemSettings5_InvalidLastViewed
#define apsysset_LastViewedBroadcast	IAppApiSystemSettings5_LastViewedBroadcast
#define apsysset_LastViewedNetwork	IAppApiSystemSettings5_LastViewedNetwork
#define apsysset_GetClockMode()	apsysset->GetClockMode()
#define apsysset_SetClockMode(mode)	apsysset->SetClockMode(mode)
#define apsysset_IsDstSettingControllable()	apsysset->IsDstSettingControllable()
#define apsysset_GetDst()	apsysset->GetDst()
#define apsysset_SetDst(dst)	apsysset->SetDst(dst)
#define apsysset_IsManualClockSettingControllable()	apsysset->IsManualClockSettingControllable()
#define apsysset_GetAutoPowerDownMode()	apsysset->GetAutoPowerDownMode()
#define apsysset_SetAutoPowerDownMode(mode)	apsysset->SetAutoPowerDownMode(mode)
#define apsysset_SetMenuLanguage(language)	apsysset->SetMenuLanguage(language)
#define apsysset_GetMenuLanguage()	apsysset->GetMenuLanguage()
#define apsysset_SetInstallCountry(country)	apsysset->SetInstallCountry(country)
#define apsysset_GetInstallCountry()	apsysset->GetInstallCountry()
#define apsysset_IsDateSet()	apsysset->IsDateSet()
#define apsysset_IsClockDefined()	apsysset->IsClockDefined()
#define apsysset_IsLTOSet()	apsysset->IsLTOSet()
#define apsysset_SetRCLock(OnOff)	apsysset->SetRCLock(OnOff)
#define apsysset_GetRCLockStatus()	apsysset->GetRCLockStatus()
#define apsysset_OverrideRCLock(Override)	apsysset->OverrideRCLock(Override)
#define apsysset_SetKeyboardLock(OnOff)	apsysset->SetKeyboardLock(OnOff)
#define apsysset_GetKeyboardLock()	apsysset->GetKeyboardLock()
#define apsysset_SetBDSMode(mode)	apsysset->SetBDSMode(mode)
#define apsysset_GetBDSMode(mode)	apsysset->GetBDSMode(mode)
#define apsysset_SetSXApplicationControl(onoff)	apsysset->SetSXApplicationControl(onoff)
#define apsysset_GetSXApplicationControl()	apsysset->GetSXApplicationControl()
#define apsysset_SetBDSFeatureEnabled(onoff)	apsysset->SetBDSFeatureEnabled(onoff)
#define apsysset_GetBDSFeatureEnabled()	apsysset->GetBDSFeatureEnabled()
#define apsysset_SetBDSPowerOnState(state)	apsysset->SetBDSPowerOnState(state)
#define apsysset_GetBDSPowerOnState()	apsysset->GetBDSPowerOnState()
#define apsysset_SetOSDDisplay(on_off)	apsysset->SetOSDDisplay(on_off)
#define apsysset_GetOSDDisplay()	apsysset->GetOSDDisplay()
#define apsysset_SetBdsWakeupSource(src)	apsysset->SetBdsWakeupSource(src)
#define apsysset_GetBdsWakeupSource()	apsysset->GetBdsWakeupSource()
#define apsysset_SetHotelModeUsbBreakInAllowed(onOff)	apsysset->SetHotelModeUsbBreakInAllowed(onOff)
#define apsysset_GetHotelModeUsbBreakInAllowed()	apsysset->GetHotelModeUsbBreakInAllowed()
#define apsysset_SetMaxAllowedVolume(MaxVol)	apsysset->SetMaxAllowedVolume(MaxVol)
#define apsysset_GetMaxAllowedVolume()	apsysset->GetMaxAllowedVolume()
#define apsysset_SetEpgType(epgType)	apsysset->SetEpgType(epgType)
#define apsysset_GetEpgType()	apsysset->GetEpgType()
#define apsysset_SetFactoryMode(onoff)	apsysset->SetFactoryMode(onoff)
#define apsysset_GetFactoryMode()	apsysset->GetFactoryMode()
#define apsysset_SetShopHomeMode(mode)	apsysset->SetShopHomeMode(mode)
#define apsysset_GetShopHomeMode()	apsysset->GetShopHomeMode()
#define apsysset_SetVirginBit(virginBit)	apsysset->SetVirginBit(virginBit)
#define apsysset_GetVirginBit()	apsysset->GetVirginBit()
#define apsysset_SetClockCalibSource(src)	apsysset->SetClockCalibSource(src)
#define apsysset_GetClockCalibSource()	apsysset->GetClockCalibSource()
#define apsysset_SetCurrentAVSource(src)	apsysset->SetCurrentAVSource(src)
#define apsysset_GetCurrentAVSource()	apsysset->GetCurrentAVSource()
#define apsysset_SetPreferredAudioFormat(format)	apsysset->SetPreferredAudioFormat(format)
#define apsysset_GetPreferredAudioFormat()	apsysset->GetPreferredAudioFormat()
#define apsysset_SetServiceMode(mode)	apsysset->SetServiceMode(mode)
#define apsysset_GetServiceMode()	apsysset->GetServiceMode()
#define apsysset_SetTimeZone(timezone)	apsysset->SetTimeZone(timezone)
#define apsysset_GetTimeZone()	apsysset->GetTimeZone()
#define apsysset_IsTimeZoneSettingControllable()	apsysset->IsTimeZoneSettingControllable()
#define apsysset_IsTimeZoneAvailable(timezone)	apsysset->IsTimeZoneAvailable(timezone)
#define apsysset_GetSystemVersionNumber()	apsysset->GetSystemVersionNumber()
#define apsysset_SetOsdSize(size)	apsysset->SetOsdSize(size)
#define apsysset_GetOsdSize()	apsysset->GetOsdSize()
#define apsysset_SetClockCaliberated(state)	apsysset->SetClockCaliberated(state)
#define apsysset_SetHotelModeUsbBrowseAllowed(OnOff)	apsysset->SetHotelModeUsbBrowseAllowed(OnOff)
#define apsysset_GetHotelModeUsbBrowseAllowed()	apsysset->GetHotelModeUsbBrowseAllowed()
#define apsysset_SetFactoryReset()	apsysset->SetFactoryReset()
#define apsysset_SetPrimaryAudioLanguage(language)	apsysset->SetPrimaryAudioLanguage(language)
#define apsysset_GetPrimaryAudioLanguage()	apsysset->GetPrimaryAudioLanguage()
#define apsysset_SetSecondaryAudioLanguage(language)	apsysset->SetSecondaryAudioLanguage(language)
#define apsysset_GetSecondaryAudioLanguage()	apsysset->GetSecondaryAudioLanguage()
#define apsysset_SetPrimarySubtitleLanguage(language)	apsysset->SetPrimarySubtitleLanguage(language)
#define apsysset_GetPrimarySubtitleLanguage()	apsysset->GetPrimarySubtitleLanguage()
#define apsysset_SetSecondarySubtitleLanguage(language)	apsysset->SetSecondarySubtitleLanguage(language)
#define apsysset_GetSecondarySubtitleLanguage()	apsysset->GetSecondarySubtitleLanguage()
#define apsysset_SetPrimaryTxtLanguage(language)	apsysset->SetPrimaryTxtLanguage(language)
#define apsysset_GetPrimaryTxtLanguage()	apsysset->GetPrimaryTxtLanguage()
#define apsysset_SetSecondaryTxtLanguage(language)	apsysset->SetSecondaryTxtLanguage(language)
#define apsysset_GetSecondaryTxtLanguage()	apsysset->GetSecondaryTxtLanguage()
#define apsysset_SetHearingImpaired(OnOff)	apsysset->SetHearingImpaired(OnOff)
#define apsysset_GetHearingImpaired()	apsysset->GetHearingImpaired()
#define apsysset_ResetInternet()	apsysset->ResetInternet()
#define apsysset_SetHbbTv(OnOff)	apsysset->SetHbbTv(OnOff)
#define apsysset_GetHbbTv()	apsysset->GetHbbTv()
#define apsysset_AllowLastSourceUpdateInNVM(enable)	apsysset->AllowLastSourceUpdateInNVM(enable)
#define apsysset_SetActiveChannelList(ChannelList)	apsysset->SetActiveChannelList(ChannelList)
#define apsysset_GetActiveChannelList()	apsysset->GetActiveChannelList()
#define apsysset_SetMedium(Medium)	apsysset->SetMedium(Medium)
#define apsysset_GetMedium()	apsysset->GetMedium()
#define apsysset_SetUserPinEntryStatus(Status)	apsysset->SetUserPinEntryStatus(Status)
#define apsysset_GetUserPinEntryStatus()	apsysset->GetUserPinEntryStatus()
#define apsysset_SetVisuallyImpairedStatus(onoff)	apsysset->SetVisuallyImpairedStatus(onoff)
#define apsysset_GetVisuallyImpairedStatus()	apsysset->GetVisuallyImpairedStatus()
#define apsysset_SetSubtitlePreference(val)	apsysset->SetSubtitlePreference(val)
#define apsysset_GetSubtitlePreference()	apsysset->GetSubtitlePreference()
#define apsysset_SetPinCode(val)	apsysset->SetPinCode(val)
#define apsysset_GetPinCode()	apsysset->GetPinCode()
#define apsysset_SetDMR(val)	apsysset->SetDMR(val)
#define apsysset_GetDMR()	apsysset->GetDMR()
#define apsysset_SetWiFiSmartScreen(val)	apsysset->SetWiFiSmartScreen(val)
#define apsysset_GetWiFiSmartScreen()	apsysset->GetWiFiSmartScreen()
#define apsysset_SetChannelLogo(val)	apsysset->SetChannelLogo(val)
#define apsysset_GetChannelLogo()	apsysset->GetChannelLogo()
#define apsysset_SetTvFriendlyName(val)	apsysset->SetTvFriendlyName(val)
#define apsysset_GetTvFriendlyName()	apsysset->GetTvFriendlyName()
#define apsysset_GetMenuLangICUFormat(language)	apsysset->GetMenuLangICUFormat(language)
#define apsysset_SetTimeOfChange(changeTime,nextTimeOffset)	apsysset->SetTimeOfChange(changeTime,nextTimeOffset)
#define apsysset_GetTimeOfChange(changeTime,nextTimeOffset)	apsysset->GetTimeOfChange(changeTime,nextTimeOffset)
#define apsysset_SetLastViewedEPG(val)	apsysset->SetLastViewedEPG(val)
#define apsysset_GetLastViewedEPG()	apsysset->GetLastViewedEPG()
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
#define insN_iPresent() (insN.Present())
#define insN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define insN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define insN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
#define insN_EventInsFailed	IHsvSatelliteInstallationNotify_EventInsFailed
#define insN_EventSatelliteFound	IHsvSatelliteInstallationNotify_EventSatelliteFound
#define insN_EventSatelliteNotFound	IHsvSatelliteInstallationNotify_EventSatelliteNotFound
#define insN_EventSortingStarted	IHsvSatelliteInstallationNotify_EventSortingStarted
#define insN_EventSortStopped	IHsvSatelliteInstallationNotify_EventSortStopped
#define insN_EventSortCompleted	IHsvSatelliteInstallationNotify_EventSortCompleted
#define insN_EventSortInProgress	IHsvSatelliteInstallationNotify_EventSortInProgress
#define insN_EventChannelFound	IHsvSatelliteInstallationNotify_EventChannelFound
#define insN_EventChannelNotFound	IHsvSatelliteInstallationNotify_EventChannelNotFound
#define insN_EventInsProgress	IHsvSatelliteInstallationNotify_EventInsProgress
#define insN_EventInsCompletedForLnb	IHsvSatelliteInstallationNotify_EventInsCompletedForLnb
#define insN_EventSatLnbRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted
#define insN_EventContentLibRead	IHsvSatelliteInstallationNotify_EventContentLibRead
#define insN_EventPkgInstallStart	IHsvSatelliteInstallationNotify_EventPkgInstallStart
#define insN_EventPkgInstallEnd	IHsvSatelliteInstallationNotify_EventPkgInstallEnd
#define iinsN_EventRegionScanEnd	IHsvSatelliteInstallationNotify_EventRegionScanEnd
#define insN_EventLNBStart	IHsvSatelliteInstallationNotify_EventLNBStart
#define insN_EventLNBEnd	IHsvSatelliteInstallationNotify_EventLNBEnd
#define insN_EventSatLnbRemovalStarted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted
#define insN_EventSatRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatRemovalCompleted
#define insN_EventPackageInstallFailed	IHsvSatelliteInstallationNotify_EventPackageInstallFailed
#define insN_EventPackageId	IHsvSatelliteInstallationNotify_EventPackageId
#define insN_EventPredefinedListCopySuccesful	IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful
#define insN_EventPredefinedListCopyGenericError	IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError
#define insN_EventPredefinedListCopyOlderVersion	IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion
#define insN_EventDifferentSatelliteFound	IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound
#define insN_EventPkgParsingStarted	IHsvSatelliteInstallationNotify_EventPkgParsingStarted
#define insN_EventPkgParsingCompleted	IHsvSatelliteInstallationNotify_EventPkgParsingCompleted
#define insN_EventTriggerBckgndUpdateInstall	IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall
#define insN_EventPresetAdded	IHsvSatelliteInstallationNotify_EventPresetAdded
#define insN_EventPresetDeleted IHsvSatelliteInstallationNotify_EventPresetDeleted	
#define insN_EventUpdated	 IHsvSatelliteInstallationNotify_EventUpdated
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define s2div_iPresent() (s2div.Present())
#define s2div_iVersion	s2div->iVersion()
#define s2div_IsHomingMuxTuningRequired(SatelliteId,CountryId)	s2div->IsHomingMuxTuningRequired(SatelliteId,CountryId)
#define s2div_LoadDefaultConnectionType(CountryId,ConnectionType)	s2div->LoadDefaultConnectionType(CountryId,ConnectionType)
#define s2div_LoadDefaultLnbType(CountryId,LnbType)	s2div->LoadDefaultLnbType(CountryId,LnbType)
#define s2div_IsBackgroundInstallRequired()	s2div->IsBackgroundInstallRequired()
#define s2div_PerformReinstallInSemiStandby()	s2div->PerformReinstallInSemiStandby()
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
#define idvbset_AttributePackageId	IHsvSatelliteSettings_AttributePackageId
#define idvbset_AttributePackageOnly	IHsvSatelliteSettings_AttributePackageOnly
#define idvbset_AttributeAssetManager	IHsvSatelliteSettings_AttributeAssetManager
#define insroute_ScanPackageOnly	IHsvSatelliteInstallationRoute_ScanPackageOnly
#define insroute_ScanCompleteSatellite	IHsvSatelliteInstallationRoute_ScanCompleteSatellite


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
#include "locals_msettings.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

