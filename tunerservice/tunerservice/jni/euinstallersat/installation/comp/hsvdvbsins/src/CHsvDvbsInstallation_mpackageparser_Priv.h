#ifndef  _CHSVDVBSINSTALLATION_MPACKAGEPARSER_PRIV_H
#define  _CHSVDVBSINSTALLATION_MPACKAGEPARSER_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvPackageParser.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvPrescanParser.h>
#include <IHsvLanguageIds2.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvSatSystemSettings.h>
#include <ICesOperatorProfile.h>
#include <ICesOperatorProfileNotify.h>
#include <ICesCipCAMStatusNotify.h>
#include <ICesCipCAMStatus.h>
#include <CS2MwBase.h>

class CHsvDvbsInstallation_mpackageparser_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_mpackageparser_Priv::
#include "locals_mpackageparser.h"

class CHsvDvbsInstallation_mpackageparser_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_mpackageparser_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpackageparser.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvDvbsInstallation_mpackageparser_Priv,impackagepow);
IHsvPackageParserImpl(CHsvDvbsInstallation_mpackageparser_Priv,ipackage);
IHsvSdmControlNotifyExImpl(CHsvDvbsInstallation_mpackageparser_Priv,ipackageparserctrlN);
IHsvSatelliteFrontEndNotifyImpl(CHsvDvbsInstallation_mpackageparser_Priv,ipackageparsersatfrontendN);
ICesOperatorProfileNotifyImpl(CHsvDvbsInstallation_mpackageparser_Priv,opinsN);
ICesCipCAMStatusNotifyImpl(CHsvDvbsInstallation_mpackageparser_Priv,cipStatusN);
public:
ProvidesInterface<IHsvPower>	impackagepow;

ProvidesInterface<IHsvPackageParser>	ipackage;

ProvidesInterface<IHsvSdmControlNotifyEx>	ipackageparserctrlN;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	ipackageparsersatfrontendN;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<ICesCipCAMStatusNotify>	cipStatusN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvLanguageIds2>	lngids;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<ICesCipCAMStatus>	cipStatus;
RequiresInterface<IHsvSatelliteSettings>	dvbset;
private:
Pumpdefines(CHsvDvbsInstallation_mpackageparser_Priv);

public:
CHsvDvbsInstallation_mpackageparser_Priv():i__impackagepow(this),i__ipackage(this),i__ipackageparserctrlN(this),i__ipackageparsersatfrontendN(this),i__opinsN(this),i__cipStatusN(this)
{
impackagepow	=	&i__impackagepow;
ipackage	=	&i__ipackage;
ipackageparserctrlN	=	&i__ipackageparserctrlN;
ipackageparsersatfrontendN	=	&i__ipackageparsersatfrontendN;
opinsN	=	&i__opinsN;
cipStatusN=	&i__cipStatusN;
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
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)
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
#define ctrl_iPresent() (ctrl.Present())
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
#define ctrl_Invalid	IHsvSdmControl2_Invalid
#define ctrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ctrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ctrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ctrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ctrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
#define ctrl_FNTAvailable	IHsvSdmControl2_FNTAvailable
#define ctrl_FSTAvailable	IHsvSdmControl2_FSTAvailable
#define ctrl_BATAvailable	IHsvSdmControl2_BATAvailable
#define ctrl_GetMode(dmx)	ctrl->GetMode(dmx)
#define ctrl_GetStatus(dmx)	ctrl->GetStatus(dmx)
#define ctrl_StartCollection(dmx,mode)	ctrl->StartCollection(dmx,mode)
#define ctrl_StopCollection(dmx)	ctrl->StopCollection(dmx)
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
#define iinsN_iPresent() (iinsN.Present())
#define iinsN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define iinsN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define iinsN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
#define iinsN_EventInsFailed	IHsvSatelliteInstallationNotify_EventInsFailed
#define iinsN_EventSatelliteFound	IHsvSatelliteInstallationNotify_EventSatelliteFound
#define iinsN_EventSatelliteNotFound	IHsvSatelliteInstallationNotify_EventSatelliteNotFound
#define iinsN_EventSortingStarted	IHsvSatelliteInstallationNotify_EventSortingStarted
#define iinsN_EventSortStopped	IHsvSatelliteInstallationNotify_EventSortStopped
#define iinsN_EventSortCompleted	IHsvSatelliteInstallationNotify_EventSortCompleted
#define iinsN_EventSortInProgress	IHsvSatelliteInstallationNotify_EventSortInProgress
#define iinsN_EventChannelFound	IHsvSatelliteInstallationNotify_EventChannelFound
#define iinsN_EventChannelNotFound	IHsvSatelliteInstallationNotify_EventChannelNotFound
#define iinsN_EventInsProgress	IHsvSatelliteInstallationNotify_EventInsProgress
#define iinsN_EventInsCompletedForLnb	IHsvSatelliteInstallationNotify_EventInsCompletedForLnb
#define iinsN_EventSatLnbRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted
#define iinsN_EventContentLibRead	IHsvSatelliteInstallationNotify_EventContentLibRead
#define iinsN_EventPkgInstallStart	IHsvSatelliteInstallationNotify_EventPkgInstallStart
#define iinsN_EventPkgInstallEnd	IHsvSatelliteInstallationNotify_EventPkgInstallEnd
#define iinsN_EventRegionScanEnd	IHsvSatelliteInstallationNotify_EventRegionScanEnd
#define iinsN_EventLNBStart	IHsvSatelliteInstallationNotify_EventLNBStart
#define iinsN_EventLNBEnd	IHsvSatelliteInstallationNotify_EventLNBEnd
#define iinsN_EventSatLnbRemovalStarted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted
#define iinsN_EventSatRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatRemovalCompleted
#define iinsN_EventPackageInstallFailed	IHsvSatelliteInstallationNotify_EventPackageInstallFailed
#define iinsN_EventPackageId	IHsvSatelliteInstallationNotify_EventPackageId
#define iinsN_EventPredefinedListCopySuccesful	IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful
#define iinsN_EventPredefinedListCopyGenericError	IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError
#define iinsN_EventPredefinedListCopyOlderVersion	IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion
#define iinsN_EventDifferentSatelliteFound	IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound
#define iinsN_EventPkgParsingStarted	IHsvSatelliteInstallationNotify_EventPkgParsingStarted
#define iinsN_EventPkgParsingCompleted	IHsvSatelliteInstallationNotify_EventPkgParsingCompleted
#define iinsN_EventTriggerBckgndUpdateInstall	IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall
#define iinsN_OnEvent(eventid,value)	iinsN->OnEvent(eventid,value)
#define iprescanparser_iPresent() (iprescanparser.Present())
#define iprescanparser_ExtractPreScanTableFromXml()	iprescanparser->ExtractPreScanTableFromXml()
#define iprescanparser_GetNumberOfPrescanEntries()	iprescanparser->GetNumberOfPrescanEntries()
#define iprescanparser_GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)	iprescanparser->GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)
#define iprescanparser_GetSatelliteAttributeById(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeById(SatelliteAttribute)
#define iprescanparser_GetSatelliteAttributeByPosition(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeByPosition(SatelliteAttribute)
#define iprescanparser_SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)	iprescanparser->SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)
#define lngids_iPresent() (lngids.Present())
#define lngids_LangEnglish	IHsvLanguageIds2_LangEnglish
#define lngids_LangGerman	IHsvLanguageIds2_LangGerman
#define lngids_LangSwedish	IHsvLanguageIds2_LangSwedish
#define lngids_LangItalian	IHsvLanguageIds2_LangItalian
#define lngids_LangFrench	IHsvLanguageIds2_LangFrench
#define lngids_LangSpanish	IHsvLanguageIds2_LangSpanish
#define lngids_LangCzech	IHsvLanguageIds2_LangCzech
#define lngids_LangPolish	IHsvLanguageIds2_LangPolish
#define lngids_LangTurkish	IHsvLanguageIds2_LangTurkish
#define lngids_LangRussian	IHsvLanguageIds2_LangRussian
#define lngids_LangGreek	IHsvLanguageIds2_LangGreek
#define lngids_LangBasque	IHsvLanguageIds2_LangBasque
#define lngids_LangCatalan	IHsvLanguageIds2_LangCatalan
#define lngids_LangCroatian	IHsvLanguageIds2_LangCroatian
#define lngids_LangDanish	IHsvLanguageIds2_LangDanish
#define lngids_LangDutch	IHsvLanguageIds2_LangDutch
#define lngids_LangFinnish	IHsvLanguageIds2_LangFinnish
#define lngids_LangGaelic	IHsvLanguageIds2_LangGaelic
#define lngids_LangGalligan	IHsvLanguageIds2_LangGalligan
#define lngids_LangNorwegian	IHsvLanguageIds2_LangNorwegian
#define lngids_LangPortuguese	IHsvLanguageIds2_LangPortuguese
#define lngids_LangSerbian	IHsvLanguageIds2_LangSerbian
#define lngids_LangSlovak	IHsvLanguageIds2_LangSlovak
#define lngids_LangSlovenian	IHsvLanguageIds2_LangSlovenian
#define lngids_LangWelsh	IHsvLanguageIds2_LangWelsh
#define lngids_LangRomanian	IHsvLanguageIds2_LangRomanian
#define lngids_LangEstonian	IHsvLanguageIds2_LangEstonian
#define lngids_LangUkrainian	IHsvLanguageIds2_LangUkrainian
#define lngids_LangArabic	IHsvLanguageIds2_LangArabic
#define lngids_LangHebrew	IHsvLanguageIds2_LangHebrew
#define lngids_LangHungarian	IHsvLanguageIds2_LangHungarian
#define lngids_LangHungal	IHsvLanguageIds2_LangHungal
#define lngids_LangMalay	IHsvLanguageIds2_LangMalay
#define lngids_LangPersian	IHsvLanguageIds2_LangPersian
#define lngids_LangSimplifiedchinese	IHsvLanguageIds2_LangSimplifiedchinese
#define lngids_LangTaiwanese	IHsvLanguageIds2_LangTaiwanese
#define lngids_LangBrazilianPortuguese	IHsvLanguageIds2_LangBrazilianPortuguese
#define lngids_LangBulgarian	IHsvLanguageIds2_LangBulgarian
#define lngids_LangLatinspanish	IHsvLanguageIds2_LangLatinspanish
#define lngids_LangLithuanian	IHsvLanguageIds2_LangLithuanian
#define lngids_LangLatvian	IHsvLanguageIds2_LangLatvian
#define lngids_LangKazakh	IHsvLanguageIds2_LangKazakh
#define lngids_LangThai	IHsvLanguageIds2_LangThai
#define lngids_LangIrish	IHsvLanguageIds2_LangIrish
#define lngids_LangUndefined	IHsvLanguageIds2_LangUndefined
#define lngids_LangOriginalVersion	IHsvLanguageIds2_LangOriginalVersion
#define lngids_LangAudioDescription	IHsvLanguageIds2_LangAudioDescription
#define lngids_LangORG	IHsvLanguageIds2_LangORG
#define lngids_LangORJ	IHsvLanguageIds2_LangORJ
#define lngids_LangNone	IHsvLanguageIds2_LangNone
#define lngids_MaxNumberOfLanguages	IHsvLanguageIds2_MaxNumberOfLanguages
#define lngids_iVersion	lngids->iVersion()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsInstallation_mpackageparser_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define satfeapi_iPresent() (satfeapi.Present())
#define satfeapi_PolarisationHorizontal	IHsvSatelliteFrontEnd_PolarisationHorizontal
#define satfeapi_PolarisationVertical	IHsvSatelliteFrontEnd_PolarisationVertical
#define satfeapi_BlindScanModeNormal	IHsvSatelliteFrontEnd_BlindScanModeNormal
#define satfeapi_BlindScanModeMinimal	IHsvSatelliteFrontEnd_BlindScanModeMinimal
#define satfeapi_SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots)	satfeapi->SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots)
#define satfeapi_StartSatelliteBlindScan(LnbNumber,Mode)	satfeapi->StartSatelliteBlindScan(LnbNumber,Mode)
#define satfeapi_ContinueSatelliteBlindScan()	satfeapi->ContinueSatelliteBlindScan()
#define satfeapi_AbortSatelliteBlindScan(LnbNumber)	satfeapi->AbortSatelliteBlindScan(LnbNumber)
#define satfeapi_GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth)	satfeapi->GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth)
#define satfeapi_UnicableEnable(LnbNumber,Enable)	satfeapi->UnicableEnable(LnbNumber,Enable)
#define satfeapi_IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization)	satfeapi->IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization)
#define strapi_iPresent() (strapi.Present())
#define strapi_GetSize(dest,spid)	strapi->GetSize(dest,spid)
#define strapi_GetIndex(dest,spid,key1,key2,key3,index)	strapi->GetIndex(dest,spid,key1,key2,key3,index)
#define strapi_GetByKey(dest,spid,key1,key2,key3,val)	strapi->GetByKey(dest,spid,key1,key2,key3,val)
#define strapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	strapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define strapi_GetByIndex(dest,spid,index,val)	strapi->GetByIndex(dest,spid,index,val)
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
#define ipackageparserctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ipackageparserctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ipackageparserctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ipackageparserctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ipackageparserctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ipackageparserctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ipackageparserctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ipackageparserctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ipackageparserctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ipackageparserctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ipackageparserctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ipackageparserctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ipackageparserctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ipackageparserctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ipackageparserctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ipackageparserctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define ipackageparserctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define ipackageparserctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define ipackageparserctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define ipackageparserctrlN_FST	IHsvSdmControlNotifyEx_FST
#define dvbset_GetLnbSettings(LnbSettings)	dvbset->GetLnbSettings(LnbSettings)
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
#include "locals_mpackageparser.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

