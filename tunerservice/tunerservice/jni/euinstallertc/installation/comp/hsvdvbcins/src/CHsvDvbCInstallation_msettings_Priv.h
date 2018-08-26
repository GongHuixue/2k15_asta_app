#ifndef  _CHSVDVBCINSTALLATION_MSETTINGS_PRIV_H
#define  _CHSVDVBCINSTALLATION_MSETTINGS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSettings.h>
#include <IHsvPower.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvSortRoute.h>
#include <IString.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <CTCMwBase.h>
class CHsvDvbCInstallation_msettings_Priv;
#define CLASSSCOPE CHsvDvbCInstallation_msettings_Priv::
#include "locals_msettings.h"

class CHsvDvbCInstallation_msettings_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbCInstallation_msettings_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msettings.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDVBSettingsImpl(CHsvDvbCInstallation_msettings_Priv,idvbset);
IHsvPowerImpl(CHsvDvbCInstallation_msettings_Priv,isetpow);
IHsvSystemSettingsNotifyExImpl(CHsvDvbCInstallation_msettings_Priv,syssetN);
public:
ProvidesInterface<IHsvDVBSettings>	idvbset;

ProvidesInterface<IHsvPower>	isetpow;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<ICesCityIds>	cityids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvSortRoute>	sortroute;
RequiresInterface<IString>	str;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvDvbCInstallation_msettings_Priv);

public:
CHsvDvbCInstallation_msettings_Priv():i__idvbset(this),i__isetpow(this),i__syssetN(this)
{
idvbset	=	&i__idvbset;
isetpow	=	&i__isetpow;
syssetN	=	&i__syssetN;
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
#define cids_CountryParaguay	IHsvCountryIds_CountryParaguay
#define cids_CountryUruguay	IHsvCountryIds_CountryUruguay
#define cids_CountryThailand	IHsvCountryIds_CountryThailand
#define cids_CountryNewZealand	IHsvCountryIds_CountryNewZealand
#define cids_CountrySingapore	IHsvCountryIds_CountrySingapore
#define cids_CountryMalaysia	IHsvCountryIds_CountryMalaysia
#define cids_CountryTaiwan	IHsvCountryIds_CountryTaiwan
#define cids_CountryIndonesia	IHsvCountryIds_CountryIndonesia
#define cids_CountryUAE	IHsvCountryIds_CountryUAE
#define cids_CountryMax	IHsvCountryIds_CountryMax
#define cityids_iPresent() (cityids.Present())
#define cityids_CityBeijing	ICesCityIds_CityBeijing
#define cityids_CityGuangdong	ICesCityIds_CityGuangdong
#define cityids_CityGuangzhou	ICesCityIds_CityGuangzhou
#define cityids_CityOthers	ICesCityIds_CityOthers
#define cityids_CityInvalid	ICesCityIds_CityInvalid
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
#define feapi_iPresent() (feapi.Present())
#define feapi_GetFreqRange(winid,MinFreq,MaxFreq,retval)	feapi->GetFreqRange(winid,MinFreq,MaxFreq,retval)
#define feapi_GetFreq(winid,Freq,retval)	feapi->GetFreq(winid,Freq,retval)
#define feapi_SetFreq(winid,freq,finetune,retval)	feapi->SetFreq(winid,freq,finetune,retval)
#define feapi_GetTvSystemSupp(winid,tvSystem,Supp,retval)	feapi->GetTvSystemSupp(winid,tvSystem,Supp,retval)
#define feapi_GetTvSystem(winid,TvSystem,retval)	feapi->GetTvSystem(winid,TvSystem,retval)
#define feapi_SetTvSystem(winid,TvSystem,retval)	feapi->SetTvSystem(winid,TvSystem,retval)
#define feapi_StartSearch(winid,startFreq,mode,endFreq,retval)	feapi->StartSearch(winid,startFreq,mode,endFreq,retval)
#define feapi_StopSearch(winid,retval)	feapi->StopSearch(winid,retval)
#define feapi_Freq2Chan(winid,freq,table,Chan,retval)	feapi->Freq2Chan(winid,freq,table,Chan,retval)
#define feapi_GetCarrierFreq(winid,chan,table,Freq,retval)	feapi->GetCarrierFreq(winid,chan,table,Freq,retval)
#define feapi_SigAssm	IHsvFrontEndApi_SigAssm
#define feapi_SigVssm	IHsvFrontEndApi_SigVssm
#define feapi_SigQssm	IHsvFrontEndApi_SigQssm
#define feapi_SigSssm	IHsvFrontEndApi_SigSssm
#define feapi_GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval)	feapi->GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval)
#define feapi_Start(winid,ssm,Avail,retval)	feapi->Start(winid,ssm,Avail,retval)
#define feapi_Stop(winid,ssm,Stopped,retval)	feapi->Stop(winid,ssm,Stopped,retval)
#define feapi_GetMeasValid(winid,ssm,Valid,retval)	feapi->GetMeasValid(winid,ssm,Valid,retval)
#define feapi_GetSigStrength(winid,ssm,Strength,retval)	feapi->GetSigStrength(winid,ssm,Strength,retval)
#define feapi_GetActualConstellation(winid,decoder,pConstellation,retval)	feapi->GetActualConstellation(winid,decoder,pConstellation,retval)
#define feapi_SetConstellation(winid,decoder,constellation,retval)	feapi->SetConstellation(winid,decoder,constellation,retval)
#define feapi_GetBer(winid,decoder,Ber,retval)	feapi->GetBer(winid,decoder,Ber,retval)
#define feapi_GetCarrierPresent(winid,Present,retval)	feapi->GetCarrierPresent(winid,Present,retval)
#define feapi_SetChanBandwidth(winid,bandwidth,retval)	feapi->SetChanBandwidth(winid,bandwidth,retval)
#define feapi_GetActualChanBandwidth(winid,Bandwidth,retval)	feapi->GetActualChanBandwidth(winid,Bandwidth,retval)
#define feapi_SetStreamPriority(winid,streamPriority,retval)	feapi->SetStreamPriority(winid,streamPriority,retval)
#define feapi_GetStreamPriority(winid,streamPriority,retval)	feapi->GetStreamPriority(winid,streamPriority,retval)
#define feapi_GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)	feapi->GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)
#define feapi_SetSymbolRate(winid,rate,retval)	feapi->SetSymbolRate(winid,rate,retval)
#define feapi_GetSymbolRate(winid,rate,retval)	feapi->GetSymbolRate(winid,rate,retval)
#define feapi_SetSearchRates(winid,SearchRate,size,retval)	feapi->SetSearchRates(winid,SearchRate,size,retval)
#define feapi_GetActualCodeRate(winid,rate,retval)	feapi->GetActualCodeRate(winid,rate,retval)
#define feapi_SetFreqStep(winid,step,retval)	feapi->SetFreqStep(winid,step,retval)
#define feapi_GetFreqStep(winid,step,retval)	feapi->GetFreqStep(winid,step,retval)
#define feapi_GetTPSId(winid,TPSId,retval)	feapi->GetTPSId(winid,TPSId,retval)
#define feapi_ChanDecDvbT	IHsvFrontEndApi_ChanDecDvbT
#define feapi_ChanDecDvbC	IHsvFrontEndApi_ChanDecDvbC
#define feapi_ChanDecDvbS	IHsvFrontEndApi_ChanDecDvbS
#define feapi_ChanDecISDBT	IHsvFrontEndApi_ChanDecISDBT
#define feapi_ChanDecDvbT2	IHsvFrontEndApi_ChanDecDvbT2
#define ffsdir_iPresent() (ffsdir.Present())
#define ffsdir_AvPlf	IProdApiFlashFileSystemDirectoryExEx_AvPlf
#define ffsdir_CeApps	IProdApiFlashFileSystemDirectoryExEx_CeApps
#define ffsdir_CeDcp	IProdApiFlashFileSystemDirectoryExEx_CeDcp
#define ffsdir_CeDvp	IProdApiFlashFileSystemDirectoryExEx_CeDvp
#define ffsdir_CeGs	IProdApiFlashFileSystemDirectoryExEx_CeGs
#define ffsdir_CeInfra	IProdApiFlashFileSystemDirectoryExEx_CeInfra
#define ffsdir_CeSvc	IProdApiFlashFileSystemDirectoryExEx_CeSvc
#define ffsdir_CeTlpod	IProdApiFlashFileSystemDirectoryExEx_CeTlpod
#define ffsdir_CeTv	IProdApiFlashFileSystemDirectoryExEx_CeTv
#define ffsdir_CeVlfw	IProdApiFlashFileSystemDirectoryExEx_CeVlfw
#define ffsdir_Fac	IProdApiFlashFileSystemDirectoryExEx_Fac
#define ffsdir_GfxMgr	IProdApiFlashFileSystemDirectoryExEx_GfxMgr
#define ffsdir_HySvc	IProdApiFlashFileSystemDirectoryExEx_HySvc
#define ffsdir_Infra	IProdApiFlashFileSystemDirectoryExEx_Infra
#define ffsdir_JagDvp	IProdApiFlashFileSystemDirectoryExEx_JagDvp
#define ffsdir_Juice	IProdApiFlashFileSystemDirectoryExEx_Juice
#define ffsdir_NhApi	IProdApiFlashFileSystemDirectoryExEx_NhApi
#define ffsdir_TvSvc	IProdApiFlashFileSystemDirectoryExEx_TvSvc
#define ffsdir_TxPlf	IProdApiFlashFileSystemDirectoryExEx_TxPlf
#define ffsdir_TxSvc	IProdApiFlashFileSystemDirectoryExEx_TxSvc
#define ffsdir_CeHtv	IProdApiFlashFileSystemDirectoryExEx_CeHtv
#define ffsdir_Tv520Avi	IProdApiFlashFileSystemDirectoryExEx_Tv520Avi
#define ffsdir_CbMhg	IProdApiFlashFileSystemDirectoryExEx_CbMhg
#define ffsdir_Tv	IProdApiFlashFileSystemDirectoryExEx_Tv
#define ffsdir_TvPlf	IProdApiFlashFileSystemDirectoryExEx_TvPlf
#define ffsdir_NumCustomers	IProdApiFlashFileSystemDirectoryExEx_NumCustomers
#define ffsdir_SharedRes	IProdApiFlashFileSystemDirectoryExEx_SharedRes
#define ffsdir_Ols	IProdApiFlashFileSystemDirectoryExEx_Ols
#define ffsdir_Demo	IProdApiFlashFileSystemDirectoryExEx_Demo
#define ffsdir_Home	IProdApiFlashFileSystemDirectoryExEx_Home
#define ffsdir_Dfu	IProdApiFlashFileSystemDirectoryExEx_Dfu
#define ffsdir_Upg	IProdApiFlashFileSystemDirectoryExEx_Upg
#define ffsdir_Broadcast	IProdApiFlashFileSystemDirectoryExEx_Broadcast
#define ffsdir_ReadOnce	IProdApiFlashFileSystemDirectoryExEx_ReadOnce
#define ffsdir_ReadUpgrade	IProdApiFlashFileSystemDirectoryExEx_ReadUpgrade
#define ffsdir_ReadWrite	IProdApiFlashFileSystemDirectoryExEx_ReadWrite
#define ffsdir_ReadRFS	IProdApiFlashFileSystemDirectoryExEx_ReadRFS
#define ffsdir_Boot	IProdApiFlashFileSystemDirectoryExEx_Boot
#define ffsdir_Data	IProdApiFlashFileSystemDirectoryExEx_Data
#define ffsdir_NumPaths	IProdApiFlashFileSystemDirectoryExEx_NumPaths
#define ffsdir_MaxStringLength	IProdApiFlashFileSystemDirectoryExEx_MaxStringLength
#define ffsdir_GetDirPath(direc,pathtype,subsystem)	ffsdir->GetDirPath(direc,pathtype,subsystem)
#define ffsdir_GetDirPathLength(pathtype,subsystem)	ffsdir->GetDirPathLength(pathtype,subsystem)
#define ffsdir_GetDirPathStr(direc,pathtype,subsystem)	ffsdir->GetDirPathStr(direc,pathtype,subsystem)
#define ffsdir_GetDirPathLengthStr(pathtype,subsystem)	ffsdir->GetDirPathLengthStr(pathtype,subsystem)
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
#define insN_EventNewPresetNumber	IHsvInstallationNotify_EventNewPresetNumber
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define plferrids_iPresent() (plferrids.Present())
#define plferrids_Ok	IPlfApiErrorIds_Ok
#define plferrids_ResourceNotOwned	IPlfApiErrorIds_ResourceNotOwned
#define plferrids_InterfaceNotAvailable	IPlfApiErrorIds_InterfaceNotAvailable
#define plferrids_InterfaceNotImplemented	IPlfApiErrorIds_InterfaceNotImplemented
#define plferrids_Other	IPlfApiErrorIds_Other
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbCInstallation_msettings_Priv::func,replace,(char *)name,this)
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
#define rins_AttributeDualAnalogPass  IHsvInstallation2_AttributeDualAnalogPass
#define rins_AttributeDTTScanOnAnalog  IHsvInstallation2_AttributeDTTScanOnAnalog
#define rins_AttributeLCNOption  IHsvInstallation2_AttributeLCNOption
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
#define rins_Blizoo	IHsvInstallation2_Blizoo
#define rins_CanalDigital IHsvInstallation2_CanalDigital
#define rins_YouSee	IHsvInstallation2_YouSee
#define rins_Telemach	IHsvInstallation2_Telemach
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
#define sortroute_iPresent() (sortroute.Present())
#define sortroute_stubsort	IHsvSortRoute_stubsort
#define sortroute_dvbtsort	IHsvSortRoute_dvbtsort
#define sortroute_dvbcsort	IHsvSortRoute_dvbcsort
#define sortroute_norsort	IHsvSortRoute_norsort
#define sortroute_dvbclitesort	IHsvSortRoute_dvbclitesort
#define sortroute_dvbtlitesort	IHsvSortRoute_dvbtlitesort
#define sortroute_italysort	IHsvSortRoute_italysort
#define sortroute_dvbt2sort	IHsvSortRoute_dvbt2sort
#define sortroute_finsort	IHsvSortRoute_finsort
#define sortroute_Enable()	sortroute->Enable()
#define sortroute_GetCurrentActiveSortInterface()	sortroute->GetCurrentActiveSortInterface()
#define str_iPresent() (str.Present())
#define str_strcmp(str1,str2)	str->strcmp(str1,str2)
#define str_strcmpRom(str1,str2)	str->strcmpRom(str1,str2)
#define str_strncmp(str1,str2,num)	str->strncmp(str1,str2,num)
#define str_strncmpRom(str1,str2,num)	str->strncmpRom(str1,str2,num)
#define str_strlen(str1)	str->strlen(str1)
#define str_strlenRom(str1)	str->strlenRom(str1)
#define str_strcpy(dest,source)	str->strcpy(dest,source)
#define str_strcpyRom(dest,source)	str->strcpyRom(dest,source)
#define str_strncpy(dest,source,num)	str->strncpy(dest,source,num)
#define str_strncpyRom(dest,source,num)	str->strncpyRom(dest,source,num)
#define str_strcat(dest,source)	str->strcat(dest,source)
#define str_strcatRom(dest,source)	str->strcatRom(dest,source)
#define str_strncat(dest,source,num)	str->strncat(dest,source,num)
#define str_strstr(book,word)	str->strstr(book,word)
#define str_strchr(book,letter)	str->strchr(book,letter)
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

