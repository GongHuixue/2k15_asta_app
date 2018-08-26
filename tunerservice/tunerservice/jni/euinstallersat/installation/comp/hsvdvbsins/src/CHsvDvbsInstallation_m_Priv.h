#ifndef  _CHSVDVBSINSTALLATION_M_PRIV_H
#define  _CHSVDVBSINSTALLATION_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvMiniPrescanNotify.h>
#include <IHsvSatelliteInstallationConstants.h>
#include <IHsvPower.h>
#include <IHsvSystemSettingsNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvStreamNotify.h>
#include <ISvcAudioControl4ExEx.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvMiniPrescan.h>
#include <IHsvPackageParser.h>
#include <IHsvSorting.h>
#include <IHsvPredefinedListCopy.h>
#include <IHsvPrescanParser.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvSatSystemSettings.h>
#include <ISvcVideoControl3.h>
#include <IHsvWindowDestinationMap.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_m_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_m_Priv::
#include "locals_m.h"

class CHsvDvbsInstallation_m_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmControlNotifyExImpl(CHsvDvbsInstallation_m_Priv,ctrlN);
IHsvSatelliteInstallationNotifyImpl(CHsvDvbsInstallation_m_Priv,iinsN);
IHsvMiniPrescanNotifyImpl(CHsvDvbsInstallation_m_Priv,iminiprescanN);
IHsvSatelliteInstallationConstantsImpl(CHsvDvbsInstallation_m_Priv,insconst);
IHsvPowerImpl(CHsvDvbsInstallation_m_Priv,ipow);
IHsvSystemSettingsNotifyImpl(CHsvDvbsInstallation_m_Priv,isyssetN);
IHsvSatelliteInstallationImpl(CHsvDvbsInstallation_m_Priv,pins);
IHsvSatelliteFrontEndNotifyImpl(CHsvDvbsInstallation_m_Priv,satfeapiN);
IHsvStreamNotifyImpl(CHsvDvbsInstallation_m_Priv,strapiN);
ICesOperatorProfileNotifyImpl(CHsvDvbsInstallation_m_Priv,opinsN);
ICesCipCAMStatusNotifyImpl(CHsvDvbsInstallation_m_Priv,cipStatusN);
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatelliteInstallationNotify>	iinsN;

ProvidesInterface<IHsvMiniPrescanNotify>	iminiprescanN;

ProvidesInterface<IHsvSatelliteInstallationConstants>	insconst;

ProvidesInterface<IHsvPower>	ipow;

ProvidesInterface<IHsvSystemSettingsNotify>	isyssetN;

ProvidesInterface<IHsvSatelliteInstallation>	pins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	satfeapiN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<ICesCipCAMStatusNotify>	cipStatusN;

//Required interfaces
public:
RequiresInterface<ISvcAudioControl4ExEx>	actl3;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsgeneric_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsgeneric_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsgeneric_plfApidvbsN;
RequiresInterface<IHsvSatelliteInstallation>	iaddremove;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;
RequiresInterface<IHsvSdmControlNotifyEx>	ibckctrlN;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvMiniPrescan>	iminiprescan;
RequiresInterface<IHsvSdmControlNotifyEx>	iminiprescanctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	iminiprescansatfrontendN;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvPackageParser>	ipackage;
RequiresInterface<IHsvSdmControlNotifyEx>	ipackagectrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	ipackageins;
RequiresInterface<IHsvSdmControlNotifyEx>	ipackageparserctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	ipackageparsersatfrontendN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	ipackageplfApidvbsN;
RequiresInterface<IHsvSorting>	ipackagesort;
RequiresInterface<IHsvPredefinedListCopy>	ipredefcopy;
RequiresInterface<IHsvSatelliteInstallation>	iprescan;
RequiresInterface<IHsvSdmControlNotifyEx>	iprescanctrlN;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvSatelliteFrontEndNotify>	iprescansatfrontendN;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IHsvStreamNotify>	istrapiN;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<ISvcVideoControl3>	vctl;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ICesOperatorProfileNotify>	ipackageopinsN;
RequiresInterface<ICesOperatorProfileNotify>	ipackageparseropinsN;
RequiresInterface<ICesCipCAMStatusNotify>	ipackageparsercipStatusN;
RequiresInterface<IHsvSatelliteInstallation>	isatipprescan;
RequiresInterface<IHsvSatelliteFrontEndNotify>	isatipprescansatfrontendN;
RequiresInterface<IHsvSdmControlNotifyEx>	isatipprescanctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbstricolor_plfApidvbsN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbstricolor_ctrlN;
private:
Pumpdefines(CHsvDvbsInstallation_m_Priv);

public:
CHsvDvbsInstallation_m_Priv():i__ctrlN(this),i__iinsN(this),i__iminiprescanN(this),i__insconst(this),i__ipow(this),i__isyssetN(this),i__pins(this),i__satfeapiN(this),i__strapiN(this),i__opinsN(this),i__cipStatusN(this)
{
ctrlN	=	&i__ctrlN;
iinsN	=	&i__iinsN;
iminiprescanN	=	&i__iminiprescanN;
insconst	=	&i__insconst;
ipow	=	&i__ipow;
isyssetN	=	&i__isyssetN;
pins	=	&i__pins;
satfeapiN	=	&i__satfeapiN;
strapiN	=	&i__strapiN;
opinsN	=	&i__opinsN;
cipStatusN	=	&i__cipStatusN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define actl3_iPresent() (actl3.Present())
#define actl3_Get(audioProperty)	actl3->Get(audioProperty)
#define actl3_Set(audioProperty,value)	actl3->Set(audioProperty,value)
#define actl3_Set2(audioProperty,value1,value2)	actl3->Set2(audioProperty,value1,value2)
#define actl3_Get2(audioproperty,value1)	actl3->Get2(audioproperty,value1)
#define actl3_IsAvailable(audioProperty,value)	actl3->IsAvailable(audioProperty,value)
#define actl3_IsControllable(audioProperty,value)	actl3->IsControllable(audioProperty,value)
#define actl3_IsAvailable2(audioProperty,value1,value2)	actl3->IsAvailable2(audioProperty,value1,value2)
#define actl3_IsControllable2(audioProperty,value1,value2)	actl3->IsControllable2(audioProperty,value1,value2)
#define actl3_Volume	actl3->Volume()
#define actl3_SmartSound	actl3->SmartSound()
#define actl3_VIAudioVolume	actl3->VIAudioVolume()
#define actl3_VIRouting	actl3->VIRouting()
#define actl3_VIRoutingEx	actl3->VIRoutingEx()
#define actl3_VINone	actl3->VINone()
#define actl3_VIOn	actl3->VIOn()
#define actl3_VISpeakerOutput	actl3->VISpeakerOutput()
#define actl3_VIHeadphoneOutput	actl3->VIHeadphoneOutput()
#define actl3_VIMonitorOutput	actl3->VIMonitorOutput()
#define actl3_VISpdifOutput	actl3->VISpdifOutput()
#define actl3_SeamlessMixing	actl3->SeamlessMixing()
#define actl3_SeamlessMixing_Off	actl3->SeamlessMixing_Off()
#define actl3_SeamlessMixing_On	actl3->SeamlessMixing_On()
#define actl3_SpeechPreference	actl3->SpeechPreference()
#define actl3_SpeechPreference_Descriptive	actl3->SpeechPreference_Descriptive()
#define actl3_SpeechPreference_Subtitles	actl3->SpeechPreference_Subtitles()
#define actl3_OriginalLanguage	actl3->OriginalLanguage()
#define actl3_OriginalLanguage_On	actl3->OriginalLanguage_On()
#define actl3_OriginalLanguage_Off	actl3->OriginalLanguage_Off()
#define actl3_SoundFormat	actl3->SoundFormat()
#define actl3_SpdifStatus	actl3->SpdifStatus()
#define actl3_SoundSystem	actl3->SoundSystem()
#define actl3_Mute	actl3->Mute()
#define actl3_ProgramMute	actl3->ProgramMute()
#define actl3_PreferedStereo	actl3->PreferedStereo()
#define actl3_Language	actl3->Language()
#define actl3_LanguageChina	actl3->LanguageChina()
#define actl3_None	actl3->None()
#define actl3_SpeakerOutput	actl3->SpeakerOutput()
#define actl3_HeadphoneOutput	actl3->HeadphoneOutput()
#define actl3_MonitorOutput	actl3->MonitorOutput()
#define actl3_SpdifOutput	actl3->SpdifOutput()
#define actl3_Scart1Output	actl3->Scart1Output()
#define actl3_Scart2Output	actl3->Scart2Output()
#define actl3_AllOutput	actl3->AllOutput()
#define actl3_BoolTrue	actl3->BoolTrue()
#define actl3_BoolFalse	actl3->BoolFalse()
#define actl3_IgnoreValue	actl3->IgnoreValue()
#define actl3_VolumeMin	actl3->VolumeMin()
#define actl3_VolumeMax	actl3->VolumeMax()
#define actl3_VIVolumeMin	actl3->VIVolumeMin()
#define actl3_VIVolumeMax	actl3->VIVolumeMax()
#define actl3_SmOff	actl3->SmOff()
#define actl3_SmDolbyPrologic	actl3->SmDolbyPrologic()
#define actl3_SmFront3Stereo	actl3->SmFront3Stereo()
#define actl3_SmHall	actl3->SmHall()
#define actl3_SmIncredible3Dsurround	actl3->SmIncredible3Dsurround()
#define actl3_SmSpatial	actl3->SmSpatial()
#define actl3_SmIncredibleSurround	actl3->SmIncredibleSurround()
#define actl3_SmStereo4	actl3->SmStereo4()
#define actl3_SmDigitalDolby	actl3->SmDigitalDolby()
#define actl3_SmMPEGMultiChannel	actl3->SmMPEGMultiChannel()
#define actl3_SmIncredibleMono	actl3->SmIncredibleMono()
#define actl3_SmIncredibleStereo	actl3->SmIncredibleStereo()
#define actl3_SmVDS422	actl3->SmVDS422()
#define actl3_SmVDS423	actl3->SmVDS423()
#define actl3_SmVDS521	actl3->SmVDS521()
#define actl3_SmVDS522	actl3->SmVDS522()
#define actl3_SmMatrix	actl3->SmMatrix()
#define actl3_SmDolbyPrologicII	actl3->SmDolbyPrologicII()
#define actl3_SmDigital3D	actl3->SmDigital3D()
#define actl3_SmVirtualDolbyDigital	actl3->SmVirtualDolbyDigital()
#define actl3_SmDolbyPrologicPhantom	actl3->SmDolbyPrologicPhantom()
#define actl3_SndNICAMRelatedStereo	actl3->SndNICAMRelatedStereo()
#define actl3_SndNICAMRelatedDual	actl3->SndNICAMRelatedDual()
#define actl3_SndNICAMRelatedMono	actl3->SndNICAMRelatedMono()
#define actl3_SndNICAMUnrelatedStereo	actl3->SndNICAMUnrelatedStereo()
#define actl3_SndNICAMUnrelatedDual	actl3->SndNICAMUnrelatedDual()
#define actl3_SndNICAMUnrelatedMono	actl3->SndNICAMUnrelatedMono()
#define actl3_SndNICAMData	actl3->SndNICAMData()
#define actl3_SndFMStereo	actl3->SndFMStereo()
#define actl3_SndFMDual	actl3->SndFMDual()
#define actl3_SndFMAMMono	actl3->SndFMAMMono()
#define actl3_SndEIAJMono	actl3->SndEIAJMono()
#define actl3_SndEIAJStereo	actl3->SndEIAJStereo()
#define actl3_SndEIAJDual	actl3->SndEIAJDual()
#define actl3_SndAMMono	actl3->SndAMMono()
#define actl3_SndBTSCMono	actl3->SndBTSCMono()
#define actl3_SndBTSCStereo	actl3->SndBTSCStereo()
#define actl3_SndBTSCMonoSap	actl3->SndBTSCMonoSap()
#define actl3_SndBTSCStereoSap	actl3->SndBTSCStereoSap()
#define actl3_SndBasebandMono	actl3->SndBasebandMono()
#define actl3_SndBasebandStereo	actl3->SndBasebandStereo()
#define actl3_SndNoSoundSystem	actl3->SndNoSoundSystem()
#define actl3_McChannelOnePlusOne	actl3->McChannelOnePlusOne()
#define actl3_McChannelTwoPlusTwo	actl3->McChannelTwoPlusTwo()
#define actl3_McChannelOneByZero	actl3->McChannelOneByZero()
#define actl3_McChannelTwoByZero	actl3->McChannelTwoByZero()
#define actl3_McChannelTwoByOne	actl3->McChannelTwoByOne()
#define actl3_McChannelTwoByTwo	actl3->McChannelTwoByTwo()
#define actl3_McChannelThreeByZero	actl3->McChannelThreeByZero()
#define actl3_McChannelThreeByOne	actl3->McChannelThreeByOne()
#define actl3_McChannelThreeByTwo	actl3->McChannelThreeByTwo()
#define actl3_McChannelTwoByOneKaraoke	actl3->McChannelTwoByOneKaraoke()
#define actl3_McChannelTwoByTwoKaraoke	actl3->McChannelTwoByTwoKaraoke()
#define actl3_McChannelThreeByOneKaraoke	actl3->McChannelThreeByOneKaraoke()
#define actl3_McChannelThreeByTwoKaraoke	actl3->McChannelThreeByTwoKaraoke()
#define actl3_McChannelThreeByZeroKaraoke	actl3->McChannelThreeByZeroKaraoke()
#define actl3_McChannelPCMStereo	actl3->McChannelPCMStereo()
#define actl3_McChannelNotSupported	actl3->McChannelNotSupported()
#define actl3_SfAnalog	actl3->SfAnalog()
#define actl3_SfNICAM	actl3->SfNICAM()
#define actl3_SfMPEG	actl3->SfMPEG()
#define actl3_SfPCM	actl3->SfPCM()
#define actl3_SfDolbyDigital	actl3->SfDolbyDigital()
#define actl3_SfEIAJ	actl3->SfEIAJ()
#define actl3_Sf2CS	actl3->Sf2CS()
#define actl3_SfDTS	actl3->SfDTS()
#define actl3_SfBaseBand	actl3->SfBaseBand()
#define actl3_SfAAC	actl3->SfAAC()
#define actl3_SfUnknown	actl3->SfUnknown()
#define actl3_SfDolbyDigitalPlus	actl3->SfDolbyDigitalPlus()
#define actl3_LangEnglish	ISvcAudioControl4ExEx_LangEnglish
#define actl3_LangGerman	ISvcAudioControl4ExEx_LangGerman
#define actl3_LangSwedish	ISvcAudioControl4ExEx_LangSwedish
#define actl3_LangItalian	ISvcAudioControl4ExEx_LangItalian
#define actl3_LangFrench	ISvcAudioControl4ExEx_LangFrench
#define actl3_LangSpanish	ISvcAudioControl4ExEx_LangSpanish
#define actl3_LangCzechSlovak	ISvcAudioControl4ExEx_LangCzechSlovak
#define actl3_LangPolish	ISvcAudioControl4ExEx_LangPolish
#define actl3_LangTurkish	ISvcAudioControl4ExEx_LangTurkish
#define actl3_LangRumainian	ISvcAudioControl4ExEx_LangRumainian
#define actl3_LangRussian	ISvcAudioControl4ExEx_LangRussian
#define actl3_LangEstonian	ISvcAudioControl4ExEx_LangEstonian
#define actl3_LangUkrainian	ISvcAudioControl4ExEx_LangUkrainian
#define actl3_LangGreek	ISvcAudioControl4ExEx_LangGreek
#define actl3_LangArabic	ISvcAudioControl4ExEx_LangArabic
#define actl3_LangHebrew	ISvcAudioControl4ExEx_LangHebrew
#define actl3_LangUndefined	ISvcAudioControl4ExEx_LangUndefined
#define actl3_LanguageOne	ISvcAudioControl4ExEx_LanguageOne
#define actl3_LanguageTwo	ISvcAudioControl4ExEx_LanguageTwo
#define actl3_LanguageDualOne	ISvcAudioControl4ExEx_LanguageDualOne
#define actl3_LanguageDualTwo	ISvcAudioControl4ExEx_LanguageDualTwo
#define actl3_LanguageStereo	ISvcAudioControl4ExEx_LanguageStereo
#define actl3_AudioPropertyMaxValue	ISvcAudioControl4ExEx_AudioPropertyMaxValue
#define actl3_SpdifUnsupported	actl3->SpdifUnsupported()
#define actl3_NormalAnalog	actl3->NormalAnalog()
#define actl3_AnalogMode	actl3->AnalogMode()
#define actl3_DigitalMode	actl3->DigitalMode()
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
#define hsvdvbsgeneric_ctrlN_iPresent() (hsvdvbsgeneric_ctrlN.Present())
#define hsvdvbsgeneric_ctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define hsvdvbsgeneric_ctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define hsvdvbsgeneric_ctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define hsvdvbsgeneric_ctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define hsvdvbsgeneric_ctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define hsvdvbsgeneric_ctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define hsvdvbsgeneric_ctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define hsvdvbsgeneric_ctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define hsvdvbsgeneric_ctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define hsvdvbsgeneric_ctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define hsvdvbsgeneric_ctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define hsvdvbsgeneric_ctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define hsvdvbsgeneric_ctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define hsvdvbsgeneric_ctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define hsvdvbsgeneric_ctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define hsvdvbsgeneric_ctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define hsvdvbsgeneric_ctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define hsvdvbsgeneric_ctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define hsvdvbsgeneric_ctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define hsvdvbsgeneric_ctrlN_FST	IHsvSdmControlNotifyEx_FST
#define hsvdvbsgeneric_ctrlN_OnEvent(dmx,eventid,value)	hsvdvbsgeneric_ctrlN->OnEvent(dmx,eventid,value)
#define hsvdvbsgeneric_ins_iPresent() (hsvdvbsgeneric_ins.Present())
#define hsvdvbsgeneric_ins_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define hsvdvbsgeneric_ins_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define hsvdvbsgeneric_ins_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define hsvdvbsgeneric_ins_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define hsvdvbsgeneric_ins_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define hsvdvbsgeneric_ins_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define hsvdvbsgeneric_ins_GetCurrentInstallationState(mode,state)	hsvdvbsgeneric_ins->GetCurrentInstallationState(mode,state)
#define hsvdvbsgeneric_ins_StartInstallation(Source,Lnb,Mode)	hsvdvbsgeneric_ins->StartInstallation(Source,Lnb,Mode)
#define hsvdvbsgeneric_ins_StopInstallation()	hsvdvbsgeneric_ins->StopInstallation()
#define hsvdvbsgeneric_ins_WriteBarkerMuxData()	hsvdvbsgeneric_ins->WriteBarkerMuxData()
#define hsvdvbsgeneric_ins_GetNumberOfTvChannelsFound(Mode,Lnb)	hsvdvbsgeneric_ins->GetNumberOfTvChannelsFound(Mode,Lnb)
#define hsvdvbsgeneric_ins_GetNumberofRadioChannelsFound(Mode,Lnb)	hsvdvbsgeneric_ins->GetNumberofRadioChannelsFound(Mode,Lnb)
#define hsvdvbsgeneric_ins_GetNumberOfTvChannelsRemoved(Mode,Lnb)	hsvdvbsgeneric_ins->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define hsvdvbsgeneric_ins_GetNumberofRadioChannelsRemoved(Mode,Lnb)	hsvdvbsgeneric_ins->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsAdded()	hsvdvbsgeneric_ins->GetNumberOfDigitalChannelsAdded()
#define hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsRemoved()	hsvdvbsgeneric_ins->GetNumberOfDigitalChannelsRemoved()
#define hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsMoved()	hsvdvbsgeneric_ins->GetNumberOfDigitalChannelsMoved()
#define hsvdvbsgeneric_ins_LoadManualInstallationDefaultValues()	hsvdvbsgeneric_ins->LoadManualInstallationDefaultValues()
#define hsvdvbsgeneric_ins_StoreManualInstallationValues()	hsvdvbsgeneric_ins->StoreManualInstallationValues()
#define hsvdvbsgeneric_ins_SetManualInstallationAttributes(AttributeId,Value)	hsvdvbsgeneric_ins->SetManualInstallationAttributes(AttributeId,Value)
#define hsvdvbsgeneric_ins_GetAttribute(Mode,AttributeId)	hsvdvbsgeneric_ins->GetAttribute(Mode,AttributeId)
#define hsvdvbsgeneric_ins_GetScanProgressStatus(Mode)	hsvdvbsgeneric_ins->GetScanProgressStatus(Mode)
#define hsvdvbsgeneric_ins_GetSIDetails(SiValues)	hsvdvbsgeneric_ins->GetSIDetails(SiValues)
#define hsvdvbsgeneric_plfApidvbsN_iPresent() (hsvdvbsgeneric_plfApidvbsN.Present())
#define hsvdvbsgeneric_plfApidvbsN_OnLockChanged(LockState)	hsvdvbsgeneric_plfApidvbsN->OnLockChanged(LockState)
#define hsvdvbsgeneric_plfApidvbsN_OnBlindScanEnd()	hsvdvbsgeneric_plfApidvbsN->OnBlindScanEnd()
#define iaddremove_iPresent() (iaddremove.Present())
#define iaddremove_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define iaddremove_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define iaddremove_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define iaddremove_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define iaddremove_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define iaddremove_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define iaddremove_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define iaddremove_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define iaddremove_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define iaddremove_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define iaddremove_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define iaddremove_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define iaddremove_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define iaddremove_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define iaddremove_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define iaddremove_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define iaddremove_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define iaddremove_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define iaddremove_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define iaddremove_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define iaddremove_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define iaddremove_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define iaddremove_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define iaddremove_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define iaddremove_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define iaddremove_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define iaddremove_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define iaddremove_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define iaddremove_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define iaddremove_GetCurrentInstallationState(mode,state)	iaddremove->GetCurrentInstallationState(mode,state)
#define iaddremove_StartInstallation(Source,Lnb,Mode)	iaddremove->StartInstallation(Source,Lnb,Mode)
#define iaddremove_StopInstallation()	iaddremove->StopInstallation()
#define iaddremove_ResetInstallation()	iaddremove->ResetInstallation()
#define iaddremove_GetNumberOfTvChannelsFound(Lnb)	iaddremove->GetNumberOfTvChannelsFound(Lnb)
#define iaddremove_GetNumberofRadioChannelsFound(Lnb)	iaddremove->GetNumberofRadioChannelsFound(Lnb)
#define iaddremove_GetNumberOfTvChannelsRemoved(Lnb)	iaddremove->GetNumberOfTvChannelsRemoved(Lnb)
#define iaddremove_GetNumberofRadioChannelsRemoved(Lnb)	iaddremove->GetNumberofRadioChannelsRemoved(Lnb)
#define iaddremove_GetSatelliteName(Lnb,SatelliteName)	iaddremove->GetSatelliteName(Lnb,SatelliteName)
#define iaddremove_GetNumberOfDigitalChannelsAdded()	iaddremove->GetNumberOfDigitalChannelsAdded()
#define iaddremove_GetNumberOfDigitalChannelsRemoved()	iaddremove->GetNumberOfDigitalChannelsRemoved()
#define iaddremove_GetNumberOfDigitalChannelsMoved()	iaddremove->GetNumberOfDigitalChannelsMoved()
#define iaddremove_IdentifyPackagesAvailable()	iaddremove->IdentifyPackagesAvailable()
#define iaddremove_GetTotalNumberOfPackagesFound()	iaddremove->GetTotalNumberOfPackagesFound()
#define iaddremove_GetPackageByIndex(Index,Package)	iaddremove->GetPackageByIndex(Index,Package)
#define iaddremove_SetUserPackageIndex(PackageIndex)	iaddremove->SetUserPackageIndex(PackageIndex)
#define iaddremove_GetUserPackageIndex(PackageIndex,IsPackage)	iaddremove->GetUserPackageIndex(PackageIndex,IsPackage)
#define iaddremove_GetInstalledSatellites(mode,SatelliteEntries)	iaddremove->GetInstalledSatellites(mode,SatelliteEntries)
#define iaddremove_InstallAddedSatellites()	iaddremove->InstallAddedSatellites()
#define iaddremove_ResetAddedSatellites()	iaddremove->ResetAddedSatellites()
#define iaddremove_RemoveSatelliteEntry(LnbNumber)	iaddremove->RemoveSatelliteEntry(LnbNumber)
#define iaddremove_GetSatelliteSignalStrength(LnbNumber)	iaddremove->GetSatelliteSignalStrength(LnbNumber)
#define iaddremove_GetSatelliteSignalQuality(LnbNumber)	iaddremove->GetSatelliteSignalQuality(LnbNumber)
#define iaddremove_LoadManualInstallationDefaultValues()	iaddremove->LoadManualInstallationDefaultValues()
#define iaddremove_StoreManualInstallationValues()	iaddremove->StoreManualInstallationValues()
#define iaddremove_GetAttribute(Mode,AttributeId)	iaddremove->GetAttribute(Mode,AttributeId)
#define iaddremove_SetAttribute(Mode,AttributeId,Value)	iaddremove->SetAttribute(Mode,AttributeId,Value)
#define iaddremove_GetScanProgressStatus(Mode)	iaddremove->GetScanProgressStatus(Mode)
#define iaddremove_GetSITableIds(NetworkID,BouquetID)	iaddremove->GetSITableIds(NetworkID,BouquetID)
#define iaddremove_GetPackageName(PackageId,PackageName)	iaddremove->GetPackageName(PackageId,PackageName)
#define iaddremove_GetSIDetails(SiValues)	iaddremove->GetSIDetails(SiValues)
#define iaddremove_EnableUnicable(LnbNumber,Enable)	iaddremove->EnableUnicable(LnbNumber,Enable)
#define iaddremove_StopSignalStrengthMeas(LnbNumber)	iaddremove->StopSignalStrengthMeas(LnbNumber)
#define iaddremove_GetSignalQuality(Param)	iaddremove->GetSignalQuality(Param)
#define iaddremove_StartSignalStrengthMeas(LnbNumber)	iaddremove->StartSignalStrengthMeas(LnbNumber)
#define iaddremove_GetSignalStrength(param)	iaddremove->GetSignalStrength(param)
#define iaddremove_StartPredefinedListCopy()	iaddremove->StartPredefinedListCopy()
#define iaddremove_GetFirstInstalledChannel()	iaddremove->GetFirstInstalledChannel()
#define iaddremove_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	iaddremove->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define ibckInstall_iPresent() (ibckInstall.Present())
#define ibckInstall_EnableBackgroundInstallation()	ibckInstall->EnableBackgroundInstallation()
#define ibckInstall_DisableBackgroundInstallation()	ibckInstall->DisableBackgroundInstallation()
#define ibckctrlN_iPresent() (ibckctrlN.Present())
#define ibckctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ibckctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ibckctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ibckctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ibckctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ibckctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ibckctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ibckctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ibckctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ibckctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ibckctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ibckctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ibckctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ibckctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ibckctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ibckctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define ibckctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define ibckctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define ibckctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define ibckctrlN_FST	IHsvSdmControlNotifyEx_FST
#define ibckctrlN_OnEvent(dmx,eventid,value)	ibckctrlN->OnEvent(dmx,eventid,value)
#define idvbset_iPresent() (idvbset.Present())
#define idvbset_AttributePackageId	IHsvSatelliteSettings_AttributePackageId
#define idvbset_AttributePackageOnly	IHsvSatelliteSettings_AttributePackageOnly
#define idvbset_AttributeAssetManager	IHsvSatelliteSettings_AttributeAssetManager
#define idvbset_LoadLnbParametersFromPersistent()	idvbset->LoadLnbParametersFromPersistent()
#define idvbset_GetLnbSettings(LnbSettings)	idvbset->GetLnbSettings(LnbSettings)
#define idvbset_SetLnbSettings(LnbSettings)	idvbset->SetLnbSettings(LnbSettings)
#define idvbset_ResetLnbSettings()	idvbset->ResetLnbSettings()
#define idvbset_GetDefaultValues(LnbSettingsEntry)	idvbset->GetDefaultValues(LnbSettingsEntry)
#define idvbset_ResetToDefaultLnbSettings()	idvbset->ResetToDefaultLnbSettings()
#define idvbset_GetAttribute(AttributeId)	idvbset->GetAttribute(AttributeId)
#define idvbset_SetAttribute(AttributeId,Value)	idvbset->SetAttribute(AttributeId,Value)
#define idvbset_SaveSatelliteSettingsToPersistent()	idvbset->SaveSatelliteSettingsToPersistent()
#define idvbset_CommitSatelliteSettingsToPersistent()	idvbset->CommitSatelliteSettingsToPersistent()
#define idvbset_ReLoadLnbParametersFromPersistent()	idvbset->ReLoadLnbParametersFromPersistent()
#define iminiprescan_iPresent() (iminiprescan.Present())
#define iminiprescan_StartMiniPrescan(LnbNumber,Param)	iminiprescan->StartMiniPrescan(LnbNumber,Param)
#define iminiprescan_StopMiniPrescan()	iminiprescan->StopMiniPrescan()
#define iminiprescan_GetSITableIds(NetworkID,BouquetID)	iminiprescan->GetSITableIds(NetworkID,BouquetID)
#define iminiprescanctrlN_iPresent() (iminiprescanctrlN.Present())
#define iminiprescanctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iminiprescanctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iminiprescanctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iminiprescanctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iminiprescanctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iminiprescanctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iminiprescanctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iminiprescanctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iminiprescanctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iminiprescanctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iminiprescanctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iminiprescanctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iminiprescanctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iminiprescanctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iminiprescanctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iminiprescanctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define iminiprescanctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define iminiprescanctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define iminiprescanctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define iminiprescanctrlN_FST	IHsvSdmControlNotifyEx_FST
#define iminiprescanctrlN_OnEvent(dmx,eventid,value)	iminiprescanctrlN->OnEvent(dmx,eventid,value)
#define iminiprescansatfrontendN_iPresent() (iminiprescansatfrontendN.Present())
#define iminiprescansatfrontendN_OnLockChanged(LockState)	iminiprescansatfrontendN->OnLockChanged(LockState)
#define iminiprescansatfrontendN_OnBlindScanEnd()	iminiprescansatfrontendN->OnBlindScanEnd()
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
#define ipackage_iPresent() (ipackage.Present())
#define ipackage_IdentifyPackagesAvailable()	ipackage->IdentifyPackagesAvailable()
#define ipackage_GetNumberOfPackages()	ipackage->GetNumberOfPackages()
#define ipackage_GetPackageByIndex(Index,Package)	ipackage->GetPackageByIndex(Index,Package)
#define ipackage_GetPackageByKey(Package)	ipackage->GetPackageByKey(Package)
#define ipackage_GetPackageGroupId(PackageID,PackageGroupId)	ipackage->GetPackageGroupId(PackageID,PackageGroupId)
#define ipackage_GetPackageGroupName(PackageGroupId,PackageGroupName)	ipackage->GetPackageGroupName(PackageGroupId,PackageGroupName)
#define ipackage_LoadPackageGroupInfo()	ipackage->LoadPackageGroupInfo()
#define ipackage_StartPackageParsing()	ipackage->StartPackageParsing()
#define ipackage_StopPackageParsing()	ipackage->StopPackageParsing()
#define ipackage_SetPackageParserXmlString(InputString,PackageParserXmlStringLen)	ipackage->SetPackageParserXmlString(InputString,PackageParserXmlStringLen)
#define ipackagectrlN_iPresent() (ipackagectrlN.Present())
#define ipackagectrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ipackagectrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ipackagectrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ipackagectrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ipackagectrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ipackagectrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ipackagectrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ipackagectrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ipackagectrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ipackagectrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ipackagectrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ipackagectrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ipackagectrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ipackagectrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ipackagectrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ipackagectrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define ipackagectrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define ipackagectrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define ipackagectrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define ipackagectrlN_FST	IHsvSdmControlNotifyEx_FST
#define ipackagectrlN_OnEvent(dmx,eventid,value)	ipackagectrlN->OnEvent(dmx,eventid,value)
#define ipackageins_iPresent() (ipackageins.Present())
#define ipackageins_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define ipackageins_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define ipackageins_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define ipackageins_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define ipackageins_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define ipackageins_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define ipackageins_GetCurrentInstallationState(mode,state)	ipackageins->GetCurrentInstallationState(mode,state)
#define ipackageins_StartInstallation(Source,Lnb,Mode)	ipackageins->StartInstallation(Source,Lnb,Mode)
#define ipackageins_StopInstallation()	ipackageins->StopInstallation()
#define ipackageins_WriteBarkerMuxData()	ipackageins->WriteBarkerMuxData()
#define ipackageins_GetNumberOfTvChannelsFound(Mode,Lnb)	ipackageins->GetNumberOfTvChannelsFound(Mode,Lnb)
#define ipackageins_GetNumberofRadioChannelsFound(Mode,Lnb)	ipackageins->GetNumberofRadioChannelsFound(Mode,Lnb)
#define ipackageins_GetNumberOfTvChannelsRemoved(Mode,Lnb)	ipackageins->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define ipackageins_GetNumberofRadioChannelsRemoved(Mode,Lnb)	ipackageins->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define ipackageins_GetNumberOfDigitalChannelsAdded()	ipackageins->GetNumberOfDigitalChannelsAdded()
#define ipackageins_GetNumberOfDigitalChannelsRemoved()	ipackageins->GetNumberOfDigitalChannelsRemoved()
#define ipackageins_GetNumberOfDigitalChannelsMoved()	ipackageins->GetNumberOfDigitalChannelsMoved()
#define ipackageins_LoadManualInstallationDefaultValues()	ipackageins->LoadManualInstallationDefaultValues()
#define ipackageins_StoreManualInstallationValues()	ipackageins->StoreManualInstallationValues()
#define ipackageins_SetManualInstallationAttributes(AttributeId,Value)	ipackageins->SetManualInstallationAttributes(AttributeId,Value)
#define ipackageins_GetAttribute(Mode,AttributeId)	ipackageins->GetAttribute(Mode,AttributeId)
#define ipackageins_GetScanProgressStatus(Mode)	ipackageins->GetScanProgressStatus(Mode)
#define ipackageins_GetSIDetails(SiValues)	ipackageins->GetSIDetails(SiValues)
#define ipackageparserctrlN_iPresent() (ipackageparserctrlN.Present())
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
#define ipackageparserctrlN_OnEvent(dmx,eventid,value)	ipackageparserctrlN->OnEvent(dmx,eventid,value)
#define ipackageparsersatfrontendN_iPresent() (ipackageparsersatfrontendN.Present())
#define ipackageparsersatfrontendN_OnLockChanged(LockState)	ipackageparsersatfrontendN->OnLockChanged(LockState)
#define hsvdvbstricolor_plfApidvbsN_OnLockChanged(LockState) hsvdvbstricolor_plfApidvbsN->OnLockChanged(LockState)
#define hsvdvbstricolor_ctrlN_OnEvent(dmx,eventid,value)	hsvdvbstricolor_ctrlN->OnEvent(dmx,eventid,value)
#define ipackageparsersatfrontendN_OnBlindScanEnd()	ipackageparsersatfrontendN->OnBlindScanEnd()
#define ipackageplfApidvbsN_iPresent() (ipackageplfApidvbsN.Present())
#define ipackageplfApidvbsN_OnLockChanged(LockState)	ipackageplfApidvbsN->OnLockChanged(LockState)
#define ipackageplfApidvbsN_OnBlindScanEnd()	ipackageplfApidvbsN->OnBlindScanEnd()
#define ipackagesort_iPresent() (ipackagesort.Present())
#define ipackagesort_Sort(PackageIndex)	ipackagesort->Sort(PackageIndex)
#define ipredefcopy_iPresent() (ipredefcopy.Present())
#define ipredefcopy_StartPredefinedListCopy()	ipredefcopy->StartPredefinedListCopy()
#define iprescan_iPresent() (iprescan.Present())
#define iprescan_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define iprescan_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define iprescan_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define iprescan_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define iprescan_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define iprescan_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define iprescan_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define iprescan_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define iprescan_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define iprescan_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define iprescan_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define iprescan_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define iprescan_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define iprescan_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define iprescan_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define iprescan_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define iprescan_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define iprescan_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define iprescan_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define iprescan_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define iprescan_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define iprescan_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define iprescan_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define iprescan_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define iprescan_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define iprescan_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define iprescan_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define iprescan_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define iprescan_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define iprescan_GetCurrentInstallationState(mode,state)	iprescan->GetCurrentInstallationState(mode,state)
#define iprescan_StartInstallation(Source,Lnb,Mode)	iprescan->StartInstallation(Source,Lnb,Mode)
#define iprescan_StopInstallation()	iprescan->StopInstallation()
#define iprescan_ResetInstallation()	iprescan->ResetInstallation()
#define iprescan_GetNumberOfTvChannelsFound(Lnb)	iprescan->GetNumberOfTvChannelsFound(Lnb)
#define iprescan_GetNumberofRadioChannelsFound(Lnb)	iprescan->GetNumberofRadioChannelsFound(Lnb)
#define iprescan_GetNumberOfTvChannelsRemoved(Lnb)	iprescan->GetNumberOfTvChannelsRemoved(Lnb)
#define iprescan_GetNumberofRadioChannelsRemoved(Lnb)	iprescan->GetNumberofRadioChannelsRemoved(Lnb)
#define iprescan_GetSatelliteName(Lnb,SatelliteName)	iprescan->GetSatelliteName(Lnb,SatelliteName)
#define iprescan_GetNumberOfDigitalChannelsAdded()	iprescan->GetNumberOfDigitalChannelsAdded()
#define iprescan_GetNumberOfDigitalChannelsRemoved()	iprescan->GetNumberOfDigitalChannelsRemoved()
#define iprescan_GetNumberOfDigitalChannelsMoved()	iprescan->GetNumberOfDigitalChannelsMoved()
#define iprescan_IdentifyPackagesAvailable()	iprescan->IdentifyPackagesAvailable()
#define iprescan_GetTotalNumberOfPackagesFound()	iprescan->GetTotalNumberOfPackagesFound()
#define iprescan_GetPackageByIndex(Index,Package)	iprescan->GetPackageByIndex(Index,Package)
#define iprescan_SetUserPackageIndex(PackageIndex)	iprescan->SetUserPackageIndex(PackageIndex)
#define iprescan_GetUserPackageIndex(PackageIndex,IsPackage)	iprescan->GetUserPackageIndex(PackageIndex,IsPackage)
#define iprescan_GetInstalledSatellites(mode,SatelliteEntries)	iprescan->GetInstalledSatellites(mode,SatelliteEntries)
#define iprescan_InstallAddedSatellites()	iprescan->InstallAddedSatellites()
#define iprescan_ResetAddedSatellites()	iprescan->ResetAddedSatellites()
#define iprescan_RemoveSatelliteEntry(LnbNumber)	iprescan->RemoveSatelliteEntry(LnbNumber)
#define iprescan_GetSatelliteSignalStrength(LnbNumber)	iprescan->GetSatelliteSignalStrength(LnbNumber)
#define iprescan_GetSatelliteSignalQuality(LnbNumber)	iprescan->GetSatelliteSignalQuality(LnbNumber)
#define iprescan_LoadManualInstallationDefaultValues()	iprescan->LoadManualInstallationDefaultValues()
#define iprescan_StoreManualInstallationValues()	iprescan->StoreManualInstallationValues()
#define iprescan_GetAttribute(Mode,AttributeId)	iprescan->GetAttribute(Mode,AttributeId)
#define iprescan_SetAttribute(Mode,AttributeId,Value)	iprescan->SetAttribute(Mode,AttributeId,Value)
#define iprescan_GetScanProgressStatus(Mode)	iprescan->GetScanProgressStatus(Mode)
#define iprescan_GetSITableIds(NetworkID,BouquetID)	iprescan->GetSITableIds(NetworkID,BouquetID)
#define iprescan_GetPackageName(PackageId,PackageName)	iprescan->GetPackageName(PackageId,PackageName)
#define iprescan_GetSIDetails(SiValues)	iprescan->GetSIDetails(SiValues)
#define iprescan_EnableUnicable(LnbNumber,Enable)	iprescan->EnableUnicable(LnbNumber,Enable)
#define iprescan_StopSignalStrengthMeas(LnbNumber)	iprescan->StopSignalStrengthMeas(LnbNumber)
#define iprescan_GetSignalQuality(Param)	iprescan->GetSignalQuality(Param)
#define iprescan_StartSignalStrengthMeas(LnbNumber)	iprescan->StartSignalStrengthMeas(LnbNumber)
#define iprescan_GetSignalStrength(param)	iprescan->GetSignalStrength(param)
#define iprescan_StartPredefinedListCopy()	iprescan->StartPredefinedListCopy()
#define iprescan_GetFirstInstalledChannel()	iprescan->GetFirstInstalledChannel()
#define iprescan_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	iprescan->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define isatipprescan_iPresent() (isatipprescan.Present())
#define isatipprescan_GetCurrentInstallationState(mode,state)	isatipprescan->GetCurrentInstallationState(mode,state)
#define isatipprescan_StartInstallation(Source,Lnb,Mode)	isatipprescan->StartInstallation(Source,Lnb,Mode)
#define isatipprescan_StopInstallation()	isatipprescan->StopInstallation()
#define isatipprescan_ResetInstallation()	isatipprescan->ResetInstallation()
#define isatipprescan_GetNumberOfTvChannelsFound(Lnb)	isatipprescan->GetNumberOfTvChannelsFound(Lnb)
#define isatipprescan_GetNumberofRadioChannelsFound(Lnb)	isatipprescan->GetNumberofRadioChannelsFound(Lnb)
#define isatipprescan_GetNumberOfTvChannelsRemoved(Lnb)	isatipprescan->GetNumberOfTvChannelsRemoved(Lnb)
#define isatipprescan_GetNumberofRadioChannelsRemoved(Lnb)	isatipprescan->GetNumberofRadioChannelsRemoved(Lnb)
#define isatipprescan_GetSatelliteName(Lnb,SatelliteName)	isatipprescan->GetSatelliteName(Lnb,SatelliteName)
#define isatipprescan_GetNumberOfDigitalChannelsAdded()	isatipprescan->GetNumberOfDigitalChannelsAdded()
#define isatipprescan_GetNumberOfDigitalChannelsRemoved()	isatipprescan->GetNumberOfDigitalChannelsRemoved()
#define isatipprescan_GetNumberOfDigitalChannelsMoved()	isatipprescan->GetNumberOfDigitalChannelsMoved()
#define isatipprescan_IdentifyPackagesAvailable()	isatipprescan->IdentifyPackagesAvailable()
#define isatipprescan_GetTotalNumberOfPackagesFound()	isatipprescan->GetTotalNumberOfPackagesFound()
#define isatipprescan_GetPackageByIndex(Index,Package)	isatipprescan->GetPackageByIndex(Index,Package)
#define isatipprescan_SetUserPackageIndex(PackageIndex)	isatipprescan->SetUserPackageIndex(PackageIndex)
#define isatipprescan_GetUserPackageIndex(PackageIndex,IsPackage)	isatipprescan->GetUserPackageIndex(PackageIndex,IsPackage)
#define isatipprescan_GetInstalledSatellites(mode,SatelliteEntries)	isatipprescan->GetInstalledSatellites(mode,SatelliteEntries)
#define isatipprescan_InstallAddedSatellites()	isatipprescan->InstallAddedSatellites()
#define isatipprescan_ResetAddedSatellites()	isatipprescan->ResetAddedSatellites()
#define isatipprescan_RemoveSatelliteEntry(LnbNumber)	isatipprescan->RemoveSatelliteEntry(LnbNumber)
#define isatipprescan_GetSatelliteSignalStrength(LnbNumber)	isatipprescan->GetSatelliteSignalStrength(LnbNumber)
#define isatipprescan_GetSatelliteSignalQuality(LnbNumber)	isatipprescan->GetSatelliteSignalQuality(LnbNumber)
#define isatipprescan_LoadManualInstallationDefaultValues()	isatipprescan->LoadManualInstallationDefaultValues()
#define isatipprescan_StoreManualInstallationValues()	isatipprescan->StoreManualInstallationValues()
#define isatipprescan_GetAttribute(Mode,AttributeId)	isatipprescan->GetAttribute(Mode,AttributeId)
#define isatipprescan_SetAttribute(Mode,AttributeId,Value)	isatipprescan->SetAttribute(Mode,AttributeId,Value)
#define isatipprescan_GetScanProgressStatus(Mode)	isatipprescan->GetScanProgressStatus(Mode)
#define isatipprescan_GetSITableIds(NetworkID,BouquetID)	isatipprescan->GetSITableIds(NetworkID,BouquetID)
#define isatipprescan_GetPackageName(PackageId,PackageName)	isatipprescan->GetPackageName(PackageId,PackageName)
#define isatipprescan_GetSIDetails(SiValues)	isatipprescan->GetSIDetails(SiValues)
#define isatipprescan_EnableUnicable(LnbNumber,Enable)	isatipprescan->EnableUnicable(LnbNumber,Enable)
#define isatipprescan_StopSignalStrengthMeas(LnbNumber)	isatipprescan->StopSignalStrengthMeas(LnbNumber)
#define isatipprescan_GetSignalQuality(Param)	isatipprescan->GetSignalQuality(Param)
#define isatipprescan_StartSignalStrengthMeas(LnbNumber)	isatipprescan->StartSignalStrengthMeas(LnbNumber)
#define isatipprescan_GetSignalStrength(param)	isatipprescan->GetSignalStrength(param)
#define isatipprescan_StartPredefinedListCopy()	isatipprescan->StartPredefinedListCopy()
#define isatipprescan_GetFirstInstalledChannel()	isatipprescan->GetFirstInstalledChannel()
#define isatipprescan_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	isatipprescan->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define iprescanctrlN_iPresent() (iprescanctrlN.Present())
#define iprescanctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iprescanctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iprescanctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iprescanctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iprescanctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iprescanctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iprescanctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iprescanctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iprescanctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iprescanctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iprescanctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iprescanctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iprescanctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iprescanctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iprescanctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iprescanctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define iprescanctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define iprescanctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define iprescanctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define iprescanctrlN_FST	IHsvSdmControlNotifyEx_FST
#define iprescanctrlN_OnEvent(dmx,eventid,value)	iprescanctrlN->OnEvent(dmx,eventid,value)
#define isatipprescanctrlN_OnEvent(dmx,eventid,value)	isatipprescanctrlN->OnEvent(dmx,eventid,value)
#define iprescanparser_iPresent() (iprescanparser.Present())
#define iprescanparser_ExtractPreScanTableFromXml()	iprescanparser->ExtractPreScanTableFromXml()
#define iprescanparser_GetNumberOfPrescanEntries()	iprescanparser->GetNumberOfPrescanEntries()
#define iprescanparser_GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)	iprescanparser->GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite)
#define iprescanparser_GetSatelliteAttributeById(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeById(SatelliteAttribute)
#define iprescanparser_GetSatelliteAttributeByPosition(SatelliteAttribute)	iprescanparser->GetSatelliteAttributeByPosition(SatelliteAttribute)
#define iprescanparser_SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)	iprescanparser->SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen)
#define iprescansatfrontendN_iPresent() (iprescansatfrontendN.Present())
#define iprescansatfrontendN_OnLockChanged(LockState)	iprescansatfrontendN->OnLockChanged(LockState)
#define isatipprescansatfrontendN_OnLockChanged(LockState)	isatipprescansatfrontendN->OnLockChanged(LockState)
#define iprescansatfrontendN_OnBlindScanEnd()	iprescansatfrontendN->OnBlindScanEnd()
#define isigstr_iPresent() (isigstr.Present())
#define isigstr_InsQsm	IHsvInstallationSigStrength_InsQsm
#define isigstr_InsSsm	IHsvInstallationSigStrength_InsSsm
#define isigstr_Initialise()	isigstr->Initialise()
#define isigstr_GetSigStrengthRange(mode,min,max)	isigstr->GetSigStrengthRange(mode,min,max)
#define isigstr_GetSignalStrength(mode)	isigstr->GetSignalStrength(mode)
#define isigstr_GetMinSignalStrength(mode)	isigstr->GetMinSignalStrength(mode)
#define isigstr_GetMaxSignalStrength(mode)	isigstr->GetMaxSignalStrength(mode)
#define isigstr_GetActualSignalStrength(mode,cookie)	isigstr->GetActualSignalStrength(mode,cookie)
#define isigstr_StartSigStrMeasAll()	isigstr->StartSigStrMeasAll()
#define isigstr_StopSigStrMeasAll()	isigstr->StopSigStrMeasAll()
#define isigstr_UpdateSigStrRange()	isigstr->UpdateSigStrRange()
#define isigstr_GetSigStrengthMeasured()	isigstr->GetSigStrengthMeasured()
#define isigstr_SetSigStrengthMeasured(flag)	isigstr->SetSigStrengthMeasured(flag)
#define isigstr_StartSigStrMeas(measmode)	isigstr->StartSigStrMeas(measmode)
#define isigstr_StopSigStrMeas(measmode)	isigstr->StopSigStrMeas(measmode)
#define isigstr_IsSignalStrengthMeasurementValid(measmode)	isigstr->IsSignalStrengthMeasurementValid(measmode)
#define istrapiN_iPresent() (istrapiN.Present())
#define istrapiN_OnCompleted(dest,spid)	istrapiN->OnCompleted(dest,spid)
#define istrapiN_OnAdded(dest,spid,key1,key2,key3)	istrapiN->OnAdded(dest,spid,key1,key2,key3)
#define istrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	istrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define istrapiN_OnRemoved(dest,spid,key1,key2,key3)	istrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define ipackageopinsN_OnOpSearchStatus(opStatus)		ipackageopinsN->OnOpSearchStatus(opStatus)
#define ipackageopinsN_OnOpStatusInfo(statusInfo)		ipackageopinsN->OnOpStatusInfo(statusInfo)
#define ipackageopinsN_OnOpNIT(nitData)					ipackageopinsN->OnOpNIT(nitData)	
#define ipackageopinsN_OnOpTune(tuneData)				ipackageopinsN->OnOpTune(tuneData)
#define ipackageparseropinsN_OnOpSearchStatus(opStatus)		ipackageparseropinsN->OnOpSearchStatus(opStatus)
#define ipackageparseropinsN_OnOpStatusInfo(statusInfo)		ipackageparseropinsN->OnOpStatusInfo(statusInfo)
#define ipackageparseropinsN_OnOpNIT(nitData)				ipackageparseropinsN->OnOpNIT(nitData)	
#define ipackageparseropinsN_OnOpTune(tuneData)			ipackageparseropinsN->OnOpTune(tuneData)
#define ipackageparsercipStatusN_OnEvent(status)				ipackageparsercipStatusN->OnEvent(status)
#define iutil_iPresent() (iutil.Present())
#define iutil_ResetData()	iutil->ResetData()
#define iutil_CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)	iutil->CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate)
#define iutil_AddEntryToList(Entry)	iutil->AddEntryToList(Entry)
#define iutil_IsDuplicate(Entry)	iutil->IsDuplicate(Entry)
#define iutil_ReadBarkerMuxData(Data)	iutil->ReadBarkerMuxData(Data)
#define iutil_WriteBarkerMuxData(Data)	iutil->WriteBarkerMuxData(Data)
#define iutil_ResetBarkerMuxData()	iutil->ResetBarkerMuxData()
#define mctl_iPresent() (mctl.Present())
#define mctl_InvalidMedia	IHsvMediaControl_InvalidMedia
#define mctl_Video	IHsvMediaControl_Video
#define mctl_Audio	IHsvMediaControl_Audio
#define mctl_Pcr	IHsvMediaControl_Pcr
#define mctl_Subtitle	IHsvMediaControl_Subtitle
#define mctl_ClosedCaption	IHsvMediaControl_ClosedCaption
#define mctl_Teletext	IHsvMediaControl_Teletext
#define mctl_IPSubtitle	IHsvMediaControl_IPSubtitle
#define mctl_IPClosedCaption	IHsvMediaControl_IPClosedCaption
#define mctl_InvalidSelector	IHsvMediaControl_InvalidSelector
#define mctl_Language	IHsvMediaControl_Language
#define mctl_Type	IHsvMediaControl_Type
#define mctl_Pid	IHsvMediaControl_Pid
#define mctl_VIAssociation	IHsvMediaControl_VIAssociation
#define mctl_VIPrimaryAssociation	IHsvMediaControl_VIPrimaryAssociation
#define mctl_StreamType	IHsvMediaControl_StreamType
#define mctl_GetMediaSize(dest,media)	mctl->GetMediaSize(dest,media)
#define mctl_GetMediaByKey(dest,media,selector1,selector2,value)	mctl->GetMediaByKey(dest,media,selector1,selector2,value)
#define mctl_GetMediaIndex(dest,media,selector1,selecto2,index)	mctl->GetMediaIndex(dest,media,selector1,selecto2,index)
#define mctl_GetMediaByIndex(dest,media,index,value)	mctl->GetMediaByIndex(dest,media,index,value)
#define mctl_SetMedia(dest,media,selector,value)	mctl->SetMedia(dest,media,selector,value)
#define mctl_SetMediaWithProgram(dest,program,media,selector,value)	mctl->SetMediaWithProgram(dest,program,media,selector,value)
#define mctl_Play(dest)	mctl->Play(dest)
#define mctl_PlayMedia(dest,media)	mctl->PlayMedia(dest,media)
#define mctl_Stop(dest)	mctl->Stop(dest)
#define mctl_StopMedia(dest,media)	mctl->StopMedia(dest,media)
#define mctl_Flush(dest)	mctl->Flush(dest)
#define mctl_EnableMedia(dest,media)	mctl->EnableMedia(dest,media)
#define mctl_DisableMedia(dest,media)	mctl->DisableMedia(dest,media)
#define mctl_GetCurrentSelection(dest,media,selector)	mctl->GetCurrentSelection(dest,media,selector)
#define mctl_IsMediaPlaying(dest,media)	mctl->IsMediaPlaying(dest,media)
#define mctl_IsMediaEnabled(dest,media)	mctl->IsMediaEnabled(dest,media)
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
#define pgdb_LoadChannelMapsFromBackup() pgdb->LoadChannelMapsFromBackup()
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsInstallation_m_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define s2div_iPresent() (s2div.Present())
#define s2div_iVersion	s2div->iVersion()
#define s2div_IsHomingMuxTuningRequired(SatelliteId,CountryId)	s2div->IsHomingMuxTuningRequired(SatelliteId,CountryId)
#define s2div_LoadDefaultConnectionType(CountryId,ConnectionType)	s2div->LoadDefaultConnectionType(CountryId,ConnectionType)
#define s2div_LoadDefaultLnbType(CountryId,LnbType)	s2div->LoadDefaultLnbType(CountryId,LnbType)
#define s2div_IsBackgroundInstallRequired()	s2div->IsBackgroundInstallRequired()
#define s2div_PerformReinstallInSemiStandby()	s2div->PerformReinstallInSemiStandby()
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
#define vctl_iPresent() (vctl.Present())
#define vctl_Set(property,value)	vctl->Set(property,value)
#define vctl_Get(property)	vctl->Get(property)
#define vctl_Set2(property,value1,value2)	vctl->Set2(property,value1,value2)
#define vctl_Set3(property,value1,value2)	vctl->Set3(property,value1,value2)
#define vctl_IsAvailable(property,value)	vctl->IsAvailable(property,value)
#define vctl_IsControllable(property,value)	vctl->IsControllable(property,value)
#define vctl_Freeze	vctl->Freeze()
#define vctl_Pan	vctl->Pan()
#define vctl_ViewMode	vctl->ViewMode()
#define vctl_SeamlessViewMode	vctl->SeamlessViewMode()
#define vctl_PicturePos	vctl->PicturePos()
#define vctl_PicturePosHoriz	vctl->PicturePosHoriz()
#define vctl_VideoCoding	vctl->VideoCoding()
#define vctl_VideoCodingAux	vctl->VideoCodingAux()
#define vctl_ImageFormat	vctl->ImageFormat()
#define vctl_AutoFormat	vctl->AutoFormat()
#define vctl_VideoMute	vctl->VideoMute()
#define vctl_VideoMuteAux	vctl->VideoMuteAux()
#define vctl_VideoMuteScart2Out	vctl->VideoMuteScart2Out()
#define vctl_VideoPresenceMain	vctl->VideoPresenceMain()
#define vctl_VideoPresenceAux	vctl->VideoPresenceAux()
#define vctl_IncomingFrameLinesMain	vctl->IncomingFrameLinesMain()
#define vctl_IncomingVisibleFieldLinesMain	vctl->IncomingVisibleFieldLinesMain()
#define vctl_IncomingSignalInterlaceMain	vctl->IncomingSignalInterlaceMain()
#define vctl_IncomingFieldFrequencyMain	vctl->IncomingFieldFrequencyMain()
#define vctl_IncomingVisiblePixels	vctl->IncomingVisiblePixels()
#define vctl_IncomingVisiblePixelsAux	vctl->IncomingVisiblePixelsAux()
#define vctl_IncomingFrameLinesAux	vctl->IncomingFrameLinesAux()
#define vctl_IncomingVisibleFieldLinesAux	vctl->IncomingVisibleFieldLinesAux()
#define vctl_IncomingSignalInterlaceAux	vctl->IncomingSignalInterlaceAux()
#define vctl_IncomingFieldFrequencyAux	vctl->IncomingFieldFrequencyAux()
#define vctl_AutoVideoMute	vctl->AutoVideoMute()
#define vctl_AbsPicPosVertical	vctl->AbsPicPosVertical()
#define vctl_AbsPicPosHoriz	vctl->AbsPicPosHoriz()
#define vctl_VideoProtection	vctl->VideoProtection()
#define vctl_LastItem	vctl->LastItem()
#define vctl_FreezeOn	vctl->FreezeOn()
#define vctl_FreezeOff	vctl->FreezeOff()
#define vctl_PanUp	vctl->PanUp()
#define vctl_PanDown	vctl->PanDown()
#define vctl_PanLeft	vctl->PanLeft()
#define vctl_PanRight	vctl->PanRight()
#define vctl_VmNormalScreen4by3	vctl->VmNormalScreen4by3()
#define vctl_VmMovieExpand14by9	vctl->VmMovieExpand14by9()
#define vctl_VmMovieExpand16by9	vctl->VmMovieExpand16by9()
#define vctl_VmSubtitleZoom	vctl->VmSubtitleZoom()
#define vctl_VmSuperZoomMode	vctl->VmSuperZoomMode()
#define vctl_VmWideScreen	vctl->VmWideScreen()
#define vctl_VmMovieExpand21by9	vctl->VmMovieExpand21by9()
#define vctl_VmNormalScreen	vctl->VmNormalScreen()
#define vctl_VmVerticalSqueeze	vctl->VmVerticalSqueeze()
#define vctl_VmExpand4by3	vctl->VmExpand4by3()
#define vctl_VmPanorama	vctl->VmPanorama()
#define vctl_VmHalfWindow	vctl->VmHalfWindow()
#define vctl_VmHalfWindowSqueezed	vctl->VmHalfWindowSqueezed()
#define vctl_VmHorizontalSqueeze	vctl->VmHorizontalSqueeze()
#define vctl_VmOtherViewMode	vctl->VmOtherViewMode()
#define vctl_VmAmoranap	vctl->VmAmoranap()
#define vctl_VmZoomMode	vctl->VmZoomMode()
#define vctl_VmHorizontalExpand	vctl->VmHorizontalExpand()
#define vctl_VmPseudoPipWindow	vctl->VmPseudoPipWindow()
#define vctl_VmPreviewWindow	vctl->VmPreviewWindow()
#define vctl_VmNativeMode	vctl->VmNativeMode()
#define vctl_VmHighRes	vctl->VmHighRes()
#define vctl_VmUltraWide	vctl->VmUltraWide()
#define vctl_VmUltraWideSubtitle	vctl->VmUltraWideSubtitle()
#define vctl_VmUltraWide16by9	vctl->VmUltraWide16by9()
#define vctl_VmVideoWindow	vctl->VmVideoWindow()
#define vctl_VmUltraWideSuperZoomME16by9	vctl->VmUltraWideSuperZoomME16by9()
#define vctl_VmAutofill	vctl->VmAutofill()
#define vctl_VmAutozoom	vctl->VmAutozoom()
#define vctl_AutoFormatMode	vctl->AutoFormatMode()
#define vctl_PicturePosMin	vctl->PicturePosMin()
#define vctl_PicturePosMax	vctl->PicturePosMax()
#define vctl_PicturePosHorizMin	vctl->PicturePosHorizMin()
#define vctl_PicturePosHorizMax	vctl->PicturePosHorizMax()
#define vctl_VcCvbs	vctl->VcCvbs()
#define vctl_VcYc	vctl->VcYc()
#define vctl_VcYuv	vctl->VcYuv()
#define vctl_VcRgb	vctl->VcRgb()
#define vctl_VcYPbPr	vctl->VcYPbPr()
#define vctl_VcYcOrCvbs	vctl->VcYcOrCvbs()
#define vctl_VcRgb2Fh	vctl->VcRgb2Fh()
#define vctl_VcYPbPr2Fh	vctl->VcYPbPr2Fh()
#define vctl_VcYuv2Fh	vctl->VcYuv2Fh()
#define vctl_VcRgb3Fh	vctl->VcRgb3Fh()
#define vctl_VcYPbPr3Fh	vctl->VcYPbPr3Fh()
#define vctl_VcYuv3Fh	vctl->VcYuv3Fh()
#define vctl_VcVga	vctl->VcVga()
#define vctl_VcXvga	vctl->VcXvga()
#define vctl_VcSvga	vctl->VcSvga()
#define vctl_VcWxvga	vctl->VcWxvga()
#define vctl_ImageFormatInvalid	vctl->ImageFormatInvalid()
#define vctl_ImageFormatUnknown	vctl->ImageFormatUnknown()
#define vctl_ImageFormatNoImage	vctl->ImageFormatNoImage()
#define vctl_ImageFormat4by3FF	vctl->ImageFormat4by3FF()
#define vctl_ImageFormat14by9Top	vctl->ImageFormat14by9Top()
#define vctl_ImageFormat14by9Center	vctl->ImageFormat14by9Center()
#define vctl_ImageFormat16by9Top	vctl->ImageFormat16by9Top()
#define vctl_ImageFormat16by9Center	vctl->ImageFormat16by9Center()
#define vctl_ImageFormat4by3Use14by9	vctl->ImageFormat4by3Use14by9()
#define vctl_ImageFormat16by9FF	vctl->ImageFormat16by9FF()
#define vctl_ImageFormatMoreThan16by9Center	vctl->ImageFormatMoreThan16by9Center()
#define vctl_ImageFormat16by9Use14by9	vctl->ImageFormat16by9Use14by9()
#define vctl_ImageFormat16by9Use4by3	vctl->ImageFormat16by9Use4by3()
#define vctl_VideoPresentInvalid	vctl->VideoPresentInvalid()
#define vctl_VideoPresentUnknown	vctl->VideoPresentUnknown()
#define vctl_VideoPresent	vctl->VideoPresent()
#define vctl_VideoLost	vctl->VideoLost()
#define vctl_VideoMuteBlack	vctl->VideoMuteBlack()
#define vctl_VideoMuteBlue	vctl->VideoMuteBlue()
#define vctl_VideoMuteGrey	vctl->VideoMuteGrey()
#define vctl_VideoMuteWhite	vctl->VideoMuteWhite()
#define vctl_VideoMutePogramBlack	vctl->VideoMutePogramBlack()
#define vctl_VideoMutePogramGrey	vctl->VideoMutePogramGrey()
#define vctl_VideoMuteColourMin	vctl->VideoMuteColourMin()
#define vctl_VideoMuteColourMax	vctl->VideoMuteColourMax()
#define vctl_SigInterlace	vctl->SigInterlace()
#define vctl_SigProgressive	vctl->SigProgressive()
#define vctl_SigInterlaceInvalid	vctl->SigInterlaceInvalid()
#define vctl_SigInterlaceUnknown	vctl->SigInterlaceUnknown()
#define vctl_SigInterlaceOneOne	vctl->SigInterlaceOneOne()
#define vctl_SigInterlaceTwoOne	vctl->SigInterlaceTwoOne()
#define vctl_SigInterlaceFourTwo	vctl->SigInterlaceFourTwo()
#define vctl_AbsPicPosVerticalMin	vctl->AbsPicPosVerticalMin()
#define vctl_AbsPicPosVerticalMax	vctl->AbsPicPosVerticalMax()
#define vctl_AbsPicPosHorizMin	vctl->AbsPicPosHorizMin()
#define vctl_AbsPicPosHorizMax	vctl->AbsPicPosHorizMax()
#define vctl_UnKnown	vctl->UnKnown()
#define vctl_IgnoreValue	vctl->IgnoreValue()
#define vctl_ResetValue	vctl->ResetValue()
#define vctl_VideoPropertyMaxValue	ISvcVideoControl3_VideoPropertyMaxValue
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
#define iminiprescanN_EventPrescanFailed	IHsvMiniPrescanNotify_EventPrescanFailed
#define iminiprescanN_EventSameSatelliteDetected	IHsvMiniPrescanNotify_EventSameSatelliteDetected
#define iminiprescanN_EventDifferentSatelliteDetected	IHsvMiniPrescanNotify_EventDifferentSatelliteDetected
#define iminiprescanN_EventPreScanStopped	IHsvMiniPrescanNotify_EventPreScanStopped
#define insconst_InstallationNone	IHsvSatelliteInstallationConstants_InstallationNone
#define insconst_InstallationPreScan	IHsvSatelliteInstallationConstants_InstallationPreScan
#define insconst_InstallationServiceScan	IHsvSatelliteInstallationConstants_InstallationServiceScan
#define insconst_InstallationUpdate	IHsvSatelliteInstallationConstants_InstallationUpdate
#define insconst_InstallationManual	IHsvSatelliteInstallationConstants_InstallationManual
#define insconst_InstallationAddSatellite	IHsvSatelliteInstallationConstants_InstallationAddSatellite
#define insconst_InstallationBackground	IHsvSatelliteInstallationConstants_InstallationBackground
#define insconst_InstallationBackgroundUpdate	IHsvSatelliteInstallationConstants_InstallationBackgroundUpdate
#define insconst_InstallationStateIdle	IHsvSatelliteInstallationConstants_InstallationStateIdle
#define insconst_InstallationStateInProgress	IHsvSatelliteInstallationConstants_InstallationStateInProgress
#define insconst_InstallationStateSorting	IHsvSatelliteInstallationConstants_InstallationStateSorting
#define insconst_ManualInstallLnb	IHsvSatelliteInstallationConstants_ManualInstallLnb
#define insconst_ManualInstallFreq	IHsvSatelliteInstallationConstants_ManualInstallFreq
#define insconst_ManualInstallPolaraization	IHsvSatelliteInstallationConstants_ManualInstallPolaraization
#define insconst_ManualInstallSymRate	IHsvSatelliteInstallationConstants_ManualInstallSymRate
#define insconst_ManualInstallSymRateMode	IHsvSatelliteInstallationConstants_ManualInstallSymRateMode
#define insconst_ManualInstallModulation	IHsvSatelliteInstallationConstants_ManualInstallModulation
#define pins_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define pins_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define pins_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define pins_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define pins_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define pins_InstallationStateRegionScan IHsvSatelliteInstallation_InstallationStateRegionScan
#define pins_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define pins_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define pins_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define pins_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define pins_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define pins_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define pins_InstallationCamNit          IHsvSatelliteInstallation_InstallationCamNit
#define pins_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define pins_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define pins_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define pins_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define pins_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define pins_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define pins_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define pins_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define pins_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define pins_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define pins_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define pins_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define pins_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define pins_InstallationSSbyUpdate		IHsvSatelliteInstallation_InstallationSSbyUpdate
#define pins_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define pins_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define pins_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define pins_SatLnb4	IHsvSatelliteInstallation_SatLnb4
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

