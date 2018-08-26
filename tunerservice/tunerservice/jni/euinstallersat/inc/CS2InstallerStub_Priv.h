#ifndef  _CS2INSTALLERSTUB_PRIV_H
#define  _CS2INSTALLERSTUB_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IProdApiClockEx.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <IHsvComponentIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvLanguageIds2.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IMemoryOperations.h>
#include <IHsvDvbMplDiv.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvProgramSelection2.h>
#include <IPlfApiTsDmxAbstractEx.h>
#include <IPlfApiDvbsTuning.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPlfApiTuning.h>
#include <IPumpExSub.h>
#include <IHsvMemoryPool.h>
#include <IHsvSdmPoolIds.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiStorageDevice.h>
#include <IRealTimeKernel.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IString.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvSatSystemSettings.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <IPlfApiPhysDevice.h>
#include <IHsvUtilDiv.h>
#include <ISvcVideoControl3.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvSystemSettings.h>
#include <IHsvSatelliteSettings.h>
#include <IAppApiMultiLingualStringConversion.h>
#include <IHsvSatGlobalSettings.h>
#include <CS2MwBase.h>
class CS2InstallerStub_Priv;
#define CLASSSCOPE CS2InstallerStub_Priv::
#include "locals_mdummy.h"

class CS2InstallerStub_Priv : public CS2MwBase
{
public:
virtual ~CS2InstallerStub_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mdummy.h"
#undef MEMBERVARS
//Provided interfaces
private:
IProdApiClockExImpl(CS2InstallerStub_Priv,Timerclk);
ISvcAudioControl4ExExImpl(CS2InstallerStub_Priv,actl3);
IAppApiChannelLibReturnCodesImpl(CS2InstallerStub_Priv,apperr);
IAppApiSystemSettings5Impl(CS2InstallerStub_Priv,apsysset);
IHsvCountryIdsImpl(CS2InstallerStub_Priv,cids);
IHsvComponentIdsImpl(CS2InstallerStub_Priv,compids);
IPumpEngineImpl(CS2InstallerStub_Priv,ctrlpen);
IHsvSdmDivImpl(CS2InstallerStub_Priv,div);
IHsvDvbSiSortedTableIdsImpl(CS2InstallerStub_Priv,dvbsrtdbids);
IHsvErrorCodeExImpl(CS2InstallerStub_Priv,err);
IHsvEuropeDiversity2Impl(CS2InstallerStub_Priv,eurdiv);
IHsvLanguageIds2Impl(CS2InstallerStub_Priv,lngids);
IHsvLogImpl(CS2InstallerStub_Priv,log);
IHsvMediaControlImpl(CS2InstallerStub_Priv,mctl);
IMemoryOperationsImpl(CS2InstallerStub_Priv,memo);
IHsvDvbMplDivImpl(CS2InstallerStub_Priv,mpldiv);
IProdApiSystemStateObserverExExExExImpl(CS2InstallerStub_Priv,observer);
IPumpEngineImpl(CS2InstallerStub_Priv,pen);
IHsvChannelLibReturnCodesImpl(CS2InstallerStub_Priv,pgdaterr);
IHsvChanlibPosixLightImpl(CS2InstallerStub_Priv,pgdatrtk);
IHsvProgramSelection2Impl(CS2InstallerStub_Priv,pgsel);
IPlfApiTsDmxAbstractExImpl(CS2InstallerStub_Priv,plfdmx);
IPlfApiDvbsTuningImpl(CS2InstallerStub_Priv,plfdvbs);
IPlfApiErrorIdsImpl(CS2InstallerStub_Priv,plferrids);
ITvPlatformResourceImpl(CS2InstallerStub_Priv,plfres);
IPlfApiTuningImpl(CS2InstallerStub_Priv,plftune);
IPumpExSubImpl(CS2InstallerStub_Priv,pmp);
IHsvMemoryPoolImpl(CS2InstallerStub_Priv,pool);
IHsvSdmPoolIdsImpl(CS2InstallerStub_Priv,poolids);
IPlfApiSigStrengthMeasImpl(CS2InstallerStub_Priv,qssm);
IPlfApiStorageDeviceImpl(CS2InstallerStub_Priv,recdev);
IRealTimeKernelImpl(CS2InstallerStub_Priv,rtk);
IHsvSatelliteDiversityImpl(CS2InstallerStub_Priv,s2div);
IHsvSortedTable2Impl(CS2InstallerStub_Priv,srtdb2);
IHsvSdmSortedTableIdsImpl(CS2InstallerStub_Priv,srtdbids);
IStringImpl(CS2InstallerStub_Priv,str);
IHsvChannelLibSyncEventsImpl(CS2InstallerStub_Priv,sync);
IHsvSatSystemSettingsImpl(CS2InstallerStub_Priv,sysset);
ICeIsTpHostRtk2Impl(CS2InstallerStub_Priv,tprtk);
IPlfApiPhysDeviceImpl(CS2InstallerStub_Priv,usbms);
IHsvUtilDivImpl(CS2InstallerStub_Priv,utildiv);
ISvcVideoControl3Impl(CS2InstallerStub_Priv,vctl);
IPlfApiSigStrengthMeasImpl(CS2InstallerStub_Priv,vssm);
IHsvWindowDestinationMapImpl(CS2InstallerStub_Priv,wnddest);
public:
ProvidesInterface<IProdApiClockEx>	Timerclk;

ProvidesInterface<ISvcAudioControl4ExEx>	actl3;

ProvidesInterface<IAppApiChannelLibReturnCodes>	apperr;

ProvidesInterface<IAppApiSystemSettings5>	apsysset;

ProvidesInterface<IHsvCountryIds>	cids;

ProvidesInterface<IHsvComponentIds>	compids;

ProvidesInterface<IPumpEngine>	ctrlpen;

ProvidesInterface<IHsvSdmDiv>	div;

ProvidesInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;

ProvidesInterface<IHsvErrorCodeEx>	err;

ProvidesInterface<IHsvEuropeDiversity2>	eurdiv;

ProvidesInterface<IHsvLanguageIds2>	lngids;

ProvidesInterface<IHsvLog>	log;

ProvidesInterface<IHsvMediaControl>	mctl;

ProvidesInterface<IMemoryOperations>	memo;

ProvidesInterface<IHsvDvbMplDiv>	mpldiv;

ProvidesInterface<IProdApiSystemStateObserverExExExEx>	observer;

ProvidesInterface<IPumpEngine>	pen;

ProvidesInterface<IHsvChannelLibReturnCodes>	pgdaterr;

ProvidesInterface<IHsvChanlibPosixLight>	pgdatrtk;

ProvidesInterface<IHsvProgramSelection2>	pgsel;

ProvidesInterface<IPlfApiTsDmxAbstractEx>	plfdmx;

ProvidesInterface<IPlfApiDvbsTuning>	plfdvbs;

ProvidesInterface<IPlfApiErrorIds>	plferrids;

ProvidesInterface<ITvPlatformResource>	plfres;

ProvidesInterface<IPlfApiTuning>	plftune;

ProvidesInterface<IPumpExSub>	pmp;

ProvidesInterface<IHsvMemoryPool>	pool;

ProvidesInterface<IHsvSdmPoolIds>	poolids;

ProvidesInterface<IPlfApiSigStrengthMeas>	qssm;

ProvidesInterface<IPlfApiStorageDevice>	recdev;

ProvidesInterface<IRealTimeKernel>	rtk;

ProvidesInterface<IHsvSatelliteDiversity>	s2div;

ProvidesInterface<IHsvSortedTable2>	srtdb2;

ProvidesInterface<IHsvSdmSortedTableIds>	srtdbids;

ProvidesInterface<IString>	str;

ProvidesInterface<IHsvChannelLibSyncEvents>	sync;

ProvidesInterface<IHsvSatSystemSettings>	sysset;

ProvidesInterface<ICeIsTpHostRtk2>	tprtk;

ProvidesInterface<IPlfApiPhysDevice>	usbms;

ProvidesInterface<IHsvUtilDiv>	utildiv;

ProvidesInterface<ISvcVideoControl3>	vctl;

ProvidesInterface<IPlfApiSigStrengthMeas>	vssm;

ProvidesInterface<IHsvWindowDestinationMap>	wnddest;

public:
RequiresInterface<IHsvSystemSettings>	tvcoresettings;
RequiresInterface<IHsvSatelliteSettings>	dvbset;
RequiresInterface<IHsvSatGlobalSettings>	globalsettings;
RequiresInterface<IPlfApiTsDmxAbstractEx> plfApiTsDmx;

public:
CS2InstallerStub_Priv():i__Timerclk(this),i__actl3(this),i__apperr(this),i__apsysset(this),i__cids(this),i__compids(this),i__ctrlpen(this),i__div(this),i__dvbsrtdbids(this),i__err(this),i__eurdiv(this),i__lngids(this),i__log(this),i__mctl(this),i__memo(this),i__mpldiv(this),i__observer(this),i__pen(this),i__pgdaterr(this),i__pgdatrtk(this),i__pgsel(this),i__plfdmx(this),i__plfdvbs(this),i__plferrids(this),i__plfres(this),i__plftune(this),i__pmp(this),i__pool(this),i__poolids(this),i__qssm(this),i__recdev(this),i__rtk(this),i__s2div(this),i__srtdb2(this),i__srtdbids(this),i__str(this),i__sync(this),i__sysset(this),i__tprtk(this),i__usbms(this),i__utildiv(this),i__vctl(this),i__vssm(this),i__wnddest(this)
{
Timerclk	=	&i__Timerclk;
actl3	=	&i__actl3;
apperr	=	&i__apperr;
apsysset	=	&i__apsysset;
cids	=	&i__cids;
compids	=	&i__compids;
ctrlpen	=	&i__ctrlpen;
div	=	&i__div;
dvbsrtdbids	=	&i__dvbsrtdbids;
err	=	&i__err;
eurdiv	=	&i__eurdiv;
lngids	=	&i__lngids;
log	=	&i__log;
mctl	=	&i__mctl;
memo	=	&i__memo;
mpldiv	=	&i__mpldiv;
observer	=	&i__observer;
pen	=	&i__pen;
pgdaterr	=	&i__pgdaterr;
pgdatrtk	=	&i__pgdatrtk;
pgsel	=	&i__pgsel;
plfdmx	=	&i__plfdmx;
plfdvbs	=	&i__plfdvbs;
plferrids	=	&i__plferrids;
plfres	=	&i__plfres;
plftune	=	&i__plftune;
pmp	=	&i__pmp;
pool	=	&i__pool;
poolids	=	&i__poolids;
qssm	=	&i__qssm;
recdev	=	&i__recdev;
rtk	=	&i__rtk;
s2div	=	&i__s2div;
srtdb2	=	&i__srtdb2;
srtdbids	=	&i__srtdbids;
str	=	&i__str;
sync	=	&i__sync;
sysset	=	&i__sysset;
tprtk	=	&i__tprtk;
usbms	=	&i__usbms;
utildiv	=	&i__utildiv;
vctl	=	&i__vctl;
vssm	=	&i__vssm;
wnddest	=	&i__wnddest;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define Timerclk_ClocksourceManual	IProdApiClockEx_ClocksourceManual
#define Timerclk_ClocksourceTOT	IProdApiClockEx_ClocksourceTOT
#define Timerclk_ClocksourceECD	IProdApiClockEx_ClocksourceECD
#define Timerclk_ClocksourceTXT	IProdApiClockEx_ClocksourceTXT
#define Timerclk_ClocksourceTDT	IProdApiClockEx_ClocksourceTDT
#define Timerclk_ClocksourceTOTDVBS	IProdApiClockEx_ClocksourceTOTDVBS
#define Timerclk_ClocksourceTDTDVBS	IProdApiClockEx_ClocksourceTDTDVBS
#define Timerclk_InvalidClock	IProdApiClockEx_InvalidClock
#define Timerclk_TimeZoneNone	IProdApiClockEx_TimeZoneNone
#define Timerclk_TimeZoneBaleares	IProdApiClockEx_TimeZoneBaleares
#define Timerclk_TimeZoneCanaryIsland	IProdApiClockEx_TimeZoneCanaryIsland
#define Timerclk_TimeZoneContinental	IProdApiClockEx_TimeZoneContinental
#define Timerclk_TimeZoneAzores	IProdApiClockEx_TimeZoneAzores
#define Timerclk_TimeZoneKalingrad	IProdApiClockEx_TimeZoneKalingrad
#define Timerclk_TimeZoneMoscow	IProdApiClockEx_TimeZoneMoscow
#define Timerclk_TimeZoneSamara	IProdApiClockEx_TimeZoneSamara
#define Timerclk_TimeZoneYekaterinburg	IProdApiClockEx_TimeZoneYekaterinburg
#define Timerclk_TimeZoneOmsk	IProdApiClockEx_TimeZoneOmsk
#define Timerclk_TimeZoneKrasnoyarsk	IProdApiClockEx_TimeZoneKrasnoyarsk
#define Timerclk_TimeZoneIrkutsk	IProdApiClockEx_TimeZoneIrkutsk
#define Timerclk_TimeZoneYakutsk	IProdApiClockEx_TimeZoneYakutsk
#define Timerclk_TimeZoneVladivostok	IProdApiClockEx_TimeZoneVladivostok
#define Timerclk_TimeZoneMagadan	IProdApiClockEx_TimeZoneMagadan
#define Timerclk_TimeZoneKamchatka	IProdApiClockEx_TimeZoneKamchatka
#define Timerclk_DstAuto	IProdApiClockEx_DstAuto
#define Timerclk_DstOn	IProdApiClockEx_DstOn
#define Timerclk_DstOff	IProdApiClockEx_DstOff
#define Timerclk_LtoModeAutomatic	IProdApiClockEx_LtoModeAutomatic
#define Timerclk_LtoModeCountryDependent	IProdApiClockEx_LtoModeCountryDependent
#define actl3_Volume	i__actl3.m_Volume
#define actl3_SmartSound	i__actl3.m_SmartSound
#define actl3_VIAudioVolume	i__actl3.m_VIAudioVolume
#define actl3_VIRouting	i__actl3.m_VIRouting
#define actl3_VIRoutingEx	i__actl3.m_VIRoutingEx
#define actl3_VINone	i__actl3.m_VINone
#define actl3_VIOn	i__actl3.m_VIOn
#define actl3_VISpeakerOutput	i__actl3.m_VISpeakerOutput
#define actl3_VIHeadphoneOutput	i__actl3.m_VIHeadphoneOutput
#define actl3_VIMonitorOutput	i__actl3.m_VIMonitorOutput
#define actl3_VISpdifOutput	i__actl3.m_VISpdifOutput
#define actl3_SeamlessMixing	i__actl3.m_SeamlessMixing
#define actl3_SeamlessMixing_Off	i__actl3.m_SeamlessMixing_Off
#define actl3_SeamlessMixing_On	i__actl3.m_SeamlessMixing_On
#define actl3_SpeechPreference	i__actl3.m_SpeechPreference
#define actl3_SpeechPreference_Descriptive	i__actl3.m_SpeechPreference_Descriptive
#define actl3_SpeechPreference_Subtitles	i__actl3.m_SpeechPreference_Subtitles
#define actl3_OriginalLanguage	i__actl3.m_OriginalLanguage
#define actl3_OriginalLanguage_On	i__actl3.m_OriginalLanguage_On
#define actl3_OriginalLanguage_Off	i__actl3.m_OriginalLanguage_Off
#define actl3_SoundFormat	i__actl3.m_SoundFormat
#define actl3_SpdifStatus	i__actl3.m_SpdifStatus
#define actl3_SoundSystem	i__actl3.m_SoundSystem
#define actl3_Mute	i__actl3.m_Mute
#define actl3_ProgramMute	i__actl3.m_ProgramMute
#define actl3_PreferedStereo	i__actl3.m_PreferedStereo
#define actl3_Language	i__actl3.m_Language
#define actl3_LanguageChina	i__actl3.m_LanguageChina
#define actl3_None	i__actl3.m_None
#define actl3_SpeakerOutput	i__actl3.m_SpeakerOutput
#define actl3_HeadphoneOutput	i__actl3.m_HeadphoneOutput
#define actl3_MonitorOutput	i__actl3.m_MonitorOutput
#define actl3_SpdifOutput	i__actl3.m_SpdifOutput
#define actl3_Scart1Output	i__actl3.m_Scart1Output
#define actl3_Scart2Output	i__actl3.m_Scart2Output
#define actl3_AllOutput	i__actl3.m_AllOutput
#define actl3_BoolTrue	i__actl3.m_BoolTrue
#define actl3_BoolFalse	i__actl3.m_BoolFalse
#define actl3_IgnoreValue	i__actl3.m_IgnoreValue
#define actl3_VolumeMin	i__actl3.m_VolumeMin
#define actl3_VolumeMax	i__actl3.m_VolumeMax
#define actl3_VIVolumeMin	i__actl3.m_VIVolumeMin
#define actl3_VIVolumeMax	i__actl3.m_VIVolumeMax
#define actl3_SmOff	i__actl3.m_SmOff
#define actl3_SmDolbyPrologic	i__actl3.m_SmDolbyPrologic
#define actl3_SmFront3Stereo	i__actl3.m_SmFront3Stereo
#define actl3_SmHall	i__actl3.m_SmHall
#define actl3_SmIncredible3Dsurround	i__actl3.m_SmIncredible3Dsurround
#define actl3_SmSpatial	i__actl3.m_SmSpatial
#define actl3_SmIncredibleSurround	i__actl3.m_SmIncredibleSurround
#define actl3_SmStereo4	i__actl3.m_SmStereo4
#define actl3_SmDigitalDolby	i__actl3.m_SmDigitalDolby
#define actl3_SmMPEGMultiChannel	i__actl3.m_SmMPEGMultiChannel
#define actl3_SmIncredibleMono	i__actl3.m_SmIncredibleMono
#define actl3_SmIncredibleStereo	i__actl3.m_SmIncredibleStereo
#define actl3_SmVDS422	i__actl3.m_SmVDS422
#define actl3_SmVDS423	i__actl3.m_SmVDS423
#define actl3_SmVDS521	i__actl3.m_SmVDS521
#define actl3_SmVDS522	i__actl3.m_SmVDS522
#define actl3_SmMatrix	i__actl3.m_SmMatrix
#define actl3_SmDolbyPrologicII	i__actl3.m_SmDolbyPrologicII
#define actl3_SmDigital3D	i__actl3.m_SmDigital3D
#define actl3_SmVirtualDolbyDigital	i__actl3.m_SmVirtualDolbyDigital
#define actl3_SmDolbyPrologicPhantom	i__actl3.m_SmDolbyPrologicPhantom
#define actl3_SndNICAMRelatedStereo	i__actl3.m_SndNICAMRelatedStereo
#define actl3_SndNICAMRelatedDual	i__actl3.m_SndNICAMRelatedDual
#define actl3_SndNICAMRelatedMono	i__actl3.m_SndNICAMRelatedMono
#define actl3_SndNICAMUnrelatedStereo	i__actl3.m_SndNICAMUnrelatedStereo
#define actl3_SndNICAMUnrelatedDual	i__actl3.m_SndNICAMUnrelatedDual
#define actl3_SndNICAMUnrelatedMono	i__actl3.m_SndNICAMUnrelatedMono
#define actl3_SndNICAMData	i__actl3.m_SndNICAMData
#define actl3_SndFMStereo	i__actl3.m_SndFMStereo
#define actl3_SndFMDual	i__actl3.m_SndFMDual
#define actl3_SndFMAMMono	i__actl3.m_SndFMAMMono
#define actl3_SndEIAJMono	i__actl3.m_SndEIAJMono
#define actl3_SndEIAJStereo	i__actl3.m_SndEIAJStereo
#define actl3_SndEIAJDual	i__actl3.m_SndEIAJDual
#define actl3_SndAMMono	i__actl3.m_SndAMMono
#define actl3_SndBTSCMono	i__actl3.m_SndBTSCMono
#define actl3_SndBTSCStereo	i__actl3.m_SndBTSCStereo
#define actl3_SndBTSCMonoSap	i__actl3.m_SndBTSCMonoSap
#define actl3_SndBTSCStereoSap	i__actl3.m_SndBTSCStereoSap
#define actl3_SndBasebandMono	i__actl3.m_SndBasebandMono
#define actl3_SndBasebandStereo	i__actl3.m_SndBasebandStereo
#define actl3_SndNoSoundSystem	i__actl3.m_SndNoSoundSystem
#define actl3_McChannelOnePlusOne	i__actl3.m_McChannelOnePlusOne
#define actl3_McChannelTwoPlusTwo	i__actl3.m_McChannelTwoPlusTwo
#define actl3_McChannelOneByZero	i__actl3.m_McChannelOneByZero
#define actl3_McChannelTwoByZero	i__actl3.m_McChannelTwoByZero
#define actl3_McChannelTwoByOne	i__actl3.m_McChannelTwoByOne
#define actl3_McChannelTwoByTwo	i__actl3.m_McChannelTwoByTwo
#define actl3_McChannelThreeByZero	i__actl3.m_McChannelThreeByZero
#define actl3_McChannelThreeByOne	i__actl3.m_McChannelThreeByOne
#define actl3_McChannelThreeByTwo	i__actl3.m_McChannelThreeByTwo
#define actl3_McChannelTwoByOneKaraoke	i__actl3.m_McChannelTwoByOneKaraoke
#define actl3_McChannelTwoByTwoKaraoke	i__actl3.m_McChannelTwoByTwoKaraoke
#define actl3_McChannelThreeByOneKaraoke	i__actl3.m_McChannelThreeByOneKaraoke
#define actl3_McChannelThreeByTwoKaraoke	i__actl3.m_McChannelThreeByTwoKaraoke
#define actl3_McChannelThreeByZeroKaraoke	i__actl3.m_McChannelThreeByZeroKaraoke
#define actl3_McChannelPCMStereo	i__actl3.m_McChannelPCMStereo
#define actl3_McChannelNotSupported	i__actl3.m_McChannelNotSupported
#define actl3_SfAnalog	i__actl3.m_SfAnalog
#define actl3_SfNICAM	i__actl3.m_SfNICAM
#define actl3_SfMPEG	i__actl3.m_SfMPEG
#define actl3_SfPCM	i__actl3.m_SfPCM
#define actl3_SfDolbyDigital	i__actl3.m_SfDolbyDigital
#define actl3_SfEIAJ	i__actl3.m_SfEIAJ
#define actl3_Sf2CS	i__actl3.m_Sf2CS
#define actl3_SfDTS	i__actl3.m_SfDTS
#define actl3_SfBaseBand	i__actl3.m_SfBaseBand
#define actl3_SfAAC	i__actl3.m_SfAAC
#define actl3_SfUnknown	i__actl3.m_SfUnknown
#define actl3_SfDolbyDigitalPlus	i__actl3.m_SfDolbyDigitalPlus
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
#define actl3_SpdifUnsupported	i__actl3.m_SpdifUnsupported
#define actl3_NormalAnalog	i__actl3.m_NormalAnalog
#define actl3_AnalogMode	i__actl3.m_AnalogMode
#define actl3_DigitalMode	i__actl3.m_DigitalMode
#define apperr_Ok	IAppApiChannelLibReturnCodes_Ok
#define apperr_BadParameter	IAppApiChannelLibReturnCodes_BadParameter
#define apperr_ChannelTableEmpty	IAppApiChannelLibReturnCodes_ChannelTableEmpty
#define apperr_ChannelTableExhausted	IAppApiChannelLibReturnCodes_ChannelTableExhausted
#define apperr_MinorNumbersExhausted	IAppApiChannelLibReturnCodes_MinorNumbersExhausted
#define apperr_NotSupported	IAppApiChannelLibReturnCodes_NotSupported
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
#define tvcoresettings_AudioFormatStandard IHsvSystemSettings_AudioFormatStandard
#define tvcoresettings_AudioFormatAdvanced IHsvSystemSettings_AudioFormatAdvanced
#define tvcoresettings_MenuLanguage IHsvSystemSettings_MenuLanguage
#define tvcoresettings_Medium IHsvSystemSettings_Medium
#define tvcoresettings_InstalledCountry IHsvSystemSettings_InstalledCountry
#define tvcoresettings_HearingImpairedType IHsvSystemSettings_HearingImpairedType
#define tvcoresettings_PreferredAudioFormat IHsvSystemSettings_PreferredAudioFormat
#define tvcoresettings_PreferredPrimaryAudioLanguage IHsvSystemSettings_PreferredPrimaryAudioLanguage
#define tvcoresettings_PreferredSecondaryAudioLanguage IHsvSystemSettings_PreferredSecondaryAudioLanguage
#define tvcoresettings_PreferredPrimarySubtitleLanguage IHsvSystemSettings_PreferredPrimarySubtitleLanguage
#define tvcoresettings_PreferredSecondarySubtitleLanguage IHsvSystemSettings_PreferredSecondarySubtitleLanguage
#define tvcoresettings_PreferredPrimaryTxtLanguage IHsvSystemSettings_PreferredPrimaryTxtLanguage
#define tvcoresettings_PreferredSecondaryTxtLanguage IHsvSystemSettings_PreferredSecondaryTxtLanguage
#define tvcoresettings_clockmode IHsvSystemSettings_clockmode
#define tvcoresettings_City IHsvSystemSettings_City
#define tvcoresettings_TimeZoneCanary IHsvSystemSettings_TimeZoneCanar
#define tvcoresettings_TimeZoneRussia IHsvSystemSettings_TimeZoneRussi
#define tvcoresettings_TimeZoneBrazil IHsvSystemSettings_TimeZoneBrazi
#define tvcoresettings_TimeZoneSpain IHsvSystemSettings_TimeZoneSpain
#define tvcoresettings_TimeZonePortugal IHsvSystemSettings_TimeZonePortugal
#define tvcoresettings_TimeZoneKazakhstan IHsvSystemSettings_TimeZoneKazakhstan
#define tvcoresettings_ParentalRatingNotify IHsvSystemSettings_ParentalRatingNotify
#define tvcoresettings_SpeechPreference IHsvSystemSettings_SpeechPreference
#define tvcoresettings_VIRouting IHsvSystemSettings_VIRouting
#define tvcoresettings_VIAudioVolume IHsvSystemSettings_VIAudioVolume
#define tvcoresettings_OriginalLanguage IHsvSystemSettings_OriginalLanguage
#define tvcoresettings_SubtitleStatus IHsvSystemSettings_SubtitleStatus
#define tvcoresettings_SoundSystem IHsvSystemSettings_SoundSystem
#define tvcoresettings_VirginBitStatus IHsvSystemSettings_VirginBitStatus
#define tvcoresettings_DVBTLiteCountry IHsvSystemSettings_DVBTLiteCountry
#define tvcoresettings_HearingImpairedOn IHsvSystemSettings_HearingImpairedOn
#define tvcoresettings_SubtitleOn IHsvSystemSettings_SubtitleOn
#define tvcoresettings_MultifeedSupported IHsvSystemSettings_MultifeedSupported
#define tvcoresettings_VisuallyImpairedOn IHsvSystemSettings_VisuallyImpairedOn
#define tvcoresettings_OADSupported IHsvSystemSettings_OADSupported
#define tvcoresettings_QADSupported IHsvSystemSettings_QADSupported
#define tvcoresettings_SubtitlePIDFallBackFirstPMT IHsvSystemSettings_SubtitlePIDFallBackFirstPMT
#define tvcoresettings_IsPreMixedVISupported IHsvSystemSettings_IsPreMixedVISupported
#define tvcoresettings_IsQASUPPORTED IHsvSystemSettings_IsQASUPPORTED
#define tvcoresettings_IsAVCDescriptorSupported IHsvSystemSettings_IsAVCDescriptorSupported
#define tvcoresettings_IsAc3AudioSupported IHsvSystemSettings_IsAc3AudioSupported
#define tvcoresettings_DefaultCharacterTable IHsvSystemSettings_DefaultCharacterTable
#define tvcoresettings_CAM1_MEDIUM IHsvSystemSettings_CAM1_MEDIUM
#define tvcoresettings_CAM2_MEDIUM IHsvSystemSettings_CAM2_MEDIUM
#define tvcoresettings_OVV_ENABLE IHsvSystemSettings_OVV_ENABLE
#define tvcoresettings_SAD_ENABLE IHsvSystemSettings_SAD_ENABLE
#define tvcoresettings_Dual_Status IHsvSystemSettings_Dual_Status
#define tvcoresettings_setValue(Property,value) 	tvcoresettings->setValue(Property,value)
#define tvcoresettings_getValue(Property)		tvcoresettings->getValue(Property)
#define tvcoresettings_GetPrimaryAudioLanguage()		tvcoresettings->GetPrimaryAudioLanguage()
#define tvcoresettings_GetSecondarySubtitleLanguage()		tvcoresettings->GetSecondarySubtitleLanguage()
#define tvcoresettings_GetSecondaryAudioLanguage()		tvcoresettings->GetSecondaryAudioLanguage()
#define tvcoresettings_GetPrimarySubtitleLanguage()		tvcoresettings->GetPrimarySubtitleLanguage()
#define tvcoresettings_GetAudioFormat()		tvcoresettings->GetAudioFormat()
#define tvcoresettings_GetPrimaryTxtLanguage()		tvcoresettings->GetPrimaryTxtLanguage()
#define tvcoresettings_GetSecondaryTxtLanguage()	tvcoresettings->GetSecondaryTxtLanguage()
#define tvcoresettings_GetInstallCountry()		tvcoresettings->GetInstallCountry()
#define tvcoresettings_GetMenuLanguage()		tvcoresettings->GetMenuLanguage()
#define tvcoresettings_GetVisuallyImpairedStatus()		tvcoresettings->GetVisuallyImpairedStatus()
#define tvcoresettings_GetHearingImpaired()		tvcoresettings->GetHearingImpaired()
#define tvcoresettings_GetSubtitleOn()		tvcoresettings->GetSubtitleOn()
#define tvcoresettings_GetOperatorCable()		tvcoresettings->GetOperatorCable()
#define tvcoresettings_GetOperatorSatellite()		tvcoresettings->GetOperatorSatellite()
#define tvcoresettings_GetParentalRating()		tvcoresettings->GetParentalRating()
#define tvcoresettings_InitDbJni()		tvcoresettings->InitDbJni()
#define tvcoresettings_InitDbNative()		tvcoresettings->InitDbNative()
#define compids_hsvcc708dec	IHsvComponentIds_hsvcc708dec
#define compids_hsvatscsdm	IHsvComponentIds_hsvatscsdm
#define compids_hsvcc	IHsvComponentIds_hsvcc
#define compids_hsvccdisp	IHsvComponentIds_hsvccdisp
#define compids_hsvcm	IHsvComponentIds_hsvcm
#define compids_hsvdbase	IHsvComponentIds_hsvdbase
#define compids_hsvdmx	IHsvComponentIds_hsvdmx
#define compids_hsvdvbsins	IHsvComponentIds_hsvdvbsins
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
#define ctrlpen_PumpEngine	i__ctrlpen.m_PumpEngine
#define div_NoOfDescriptors	i__div.m_NoOfDescriptors
#define div_NoOfEvents	i__div.m_NoOfEvents
#define div_SdmWaitTime	i__div.m_SdmWaitTime
#define div_MaxStringLength	i__div.m_MaxStringLength
#define div_DataCollectionTimeout	i__div.m_DataCollectionTimeout
#define div_RRTParsingAllowed	i__div.m_RRTParsingAllowed
#define div_SystemTime	i__div.m_SystemTime
#define div_RatingStringLength	i__div.m_RatingStringLength
#define div_Enable12hourEitParsing	i__div.m_Enable12hourEitParsing
#define div_MaxPmtMonitors	i__div.m_MaxPmtMonitors
#define div_ChannelNameLength	i__div.m_ChannelNameLength
#define div_SystemLanguage	i__div.m_SystemLanguage
#define div_MaxSimplePmtFilterSupported	i__div.m_MaxSimplePmtFilterSupported
#define div_MaxSimplePmtSupported	i__div.m_MaxSimplePmtSupported
#define dvbsrtdbids_NitLcnTableMain	i__dvbsrtdbids.m_NitLcnTableMain
#define dvbsrtdbids_SdtTableActual	i__dvbsrtdbids.m_SdtTableActual
#define dvbsrtdbids_SdtTableOther	i__dvbsrtdbids.m_SdtTableOther
#define dvbsrtdbids_EitPresentActual	i__dvbsrtdbids.m_EitPresentActual
#define dvbsrtdbids_EitFollowActual	i__dvbsrtdbids.m_EitFollowActual
#define dvbsrtdbids_EitPresentOther	i__dvbsrtdbids.m_EitPresentOther
#define dvbsrtdbids_EitFollowOther	i__dvbsrtdbids.m_EitFollowOther
#define dvbsrtdbids_EitScheduleActual	i__dvbsrtdbids.m_EitScheduleActual
#define dvbsrtdbids_EitScheduleOther	i__dvbsrtdbids.m_EitScheduleOther
#define dvbsrtdbids_EitLinkageInfo	i__dvbsrtdbids.m_EitLinkageInfo
#define dvbsrtdbids_TotTableMain	i__dvbsrtdbids.m_TotTableMain
#define dvbsrtdbids_LinkageInfoMain	i__dvbsrtdbids.m_LinkageInfoMain
#define dvbsrtdbids_NitLinkageInfoMain	i__dvbsrtdbids.m_NitLinkageInfoMain
#define dvbsrtdbids_NitLcnTableSub	i__dvbsrtdbids.m_NitLcnTableSub
#define dvbsrtdbids_NitSatelliteDS	i__dvbsrtdbids.m_NitSatelliteDS
#define dvbsrtdbids_NitLinkageInfoSub	i__dvbsrtdbids.m_NitLinkageInfoSub
#define dvbsrtdbids_NitOtherNetworkIdTable	i__dvbsrtdbids.m_NitOtherNetworkIdTable
#define dvbsrtdbids_NitFreqList	i__dvbsrtdbids.m_NitFreqList
#define dvbsrtdbids_NitLcn2TableMain	i__dvbsrtdbids.m_NitLcn2TableMain
#define dvbsrtdbids_NitLcn2TableSub	i__dvbsrtdbids.m_NitLcn2TableSub
#define dvbsrtdbids_NitLcn3TableMain	i__dvbsrtdbids.m_NitLcn3TableMain
#define dvbsrtdbids_NitHDSLcnTableMain	i__dvbsrtdbids.m_NitHDSLcnTableMain
#define dvbsrtdbids_NitSrvcAtrbTableMain	i__dvbsrtdbids.m_NitSrvcAtrbTableMain
#define dvbsrtdbids_NitSrvclstTableMain	i__dvbsrtdbids.m_NitSrvclstTableMain
#define dvbsrtdbids_NitSrvclstTableSub	i__dvbsrtdbids.m_NitSrvclstTableSub
#define dvbsrtdbids_NitTsRelocateTableMain	i__dvbsrtdbids.m_NitTsRelocateTableMain
#define dvbsrtdbids_NitHDSLcnTableSub	i__dvbsrtdbids.m_NitHDSLcnTableSub
#define dvbsrtdbids_SdtTargetRegion	i__dvbsrtdbids.m_SdtTargetRegion
#define dvbsrtdbids_BatSrvclstTableMain	i__dvbsrtdbids.m_BatSrvclstTableMain
#define dvbsrtdbids_FntSatelliteDS	i__dvbsrtdbids.m_FntSatelliteDS
#define dvbsrtdbids_FntSrvclstTable	i__dvbsrtdbids.m_FntSrvclstTable
#define dvbsrtdbids_FntLcnTable	i__dvbsrtdbids.m_FntLcnTable
#define dvbsrtdbids_FntTable	i__dvbsrtdbids.m_FntTable
#define dvbsrtdbids_FstTable	i__dvbsrtdbids.m_FstTable
#define dvbsrtdbids_BatLcnTable	i__dvbsrtdbids.m_BatLcnTable
#define dvbsrtdbids_BatLcn2Table	i__dvbsrtdbids.m_BatLcn2Table
#define dvbsrtdbids_BatLinkageInfoMain	i__dvbsrtdbids.m_BatLinkageInfoMain
#define dvbsrtdbids_NitHeadEndFrequencyList	i__dvbsrtdbids.m_NitHeadEndFrequencyList
#define dvbsrtdbids_BatECNTable	i__dvbsrtdbids.m_BatECNTable
#define dvbsrtdbids_BatDetailsTable	i__dvbsrtdbids.m_BatDetailsTable
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
#define eurdiv_iVersion	i__eurdiv.m_iVersion
#define eurdiv_NITTimeoutTime	i__eurdiv.m_NITTimeoutTime
#define eurdiv_AttenuatorDetectionInInstall	i__eurdiv.m_AttenuatorDetectionInInstall
#define eurdiv_SupportNameExtractionInManIns	i__eurdiv.m_SupportNameExtractionInManIns
#define eurdiv_WeakSignalStrengthThreshold	i__eurdiv.m_WeakSignalStrengthThreshold
#define eurdiv_SignalStrengthSorting	i__eurdiv.m_SignalStrengthSorting
#define eurdiv_SearchForColorSystemInInstallation	i__eurdiv.m_SearchForColorSystemInInstallation
#define eurdiv_SearchForTvSystemInInstallation	i__eurdiv.m_SearchForTvSystemInInstallation
#define eurdiv_ManualSearchWithWrapAround	i__eurdiv.m_ManualSearchWithWrapAround
#define eurdiv_SortPresetsInAutoStoreModeNone	i__eurdiv.m_SortPresetsInAutoStoreModeNone
#define eurdiv_SignalStrengthTimeoutTime	i__eurdiv.m_SignalStrengthTimeoutTime
#define eurdiv_DefaultTunerPresetFrequency	i__eurdiv.m_DefaultTunerPresetFrequency
#define eurdiv_PgctrlMuteColor	i__eurdiv.m_PgctrlMuteColor
#define eurdiv_ChannelNameLength	i__eurdiv.m_ChannelNameLength
#define eurdiv_PresetNameLength	i__eurdiv.m_PresetNameLength
#define eurdiv_MuteRequiredOnInstallation	i__eurdiv.m_MuteRequiredOnInstallation
#define eurdiv_ClearDataOnAutoInstallation	i__eurdiv.m_ClearDataOnAutoInstallation
#define eurdiv_AnalogOnly	i__eurdiv.m_AnalogOnly
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_SkipInstallationPass	i__eurdiv.m_SkipInstallationPass
#define eurdiv_FirstInstallationPass	i__eurdiv.m_FirstInstallationPass
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_TxtInfoTimeout	i__eurdiv.m_TxtInfoTimeout
#define eurdiv_VideoMuteColor	i__eurdiv.m_VideoMuteColor
#define eurdiv_VideoMuteColorForLocks	i__eurdiv.m_VideoMuteColorForLocks
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	i__eurdiv.m_DecoderSupported
#define eurdiv_BreakInSupported	i__eurdiv.m_BreakInSupported
#define eurdiv_ScartRuleSupported	i__eurdiv.m_ScartRuleSupported
#define eurdiv_HsvAntennaDigSrvcTable	i__eurdiv.m_HsvAntennaDigSrvcTable
#define eurdiv_HsvAntennaDigPtcTable	i__eurdiv.m_HsvAntennaDigPtcTable
#define eurdiv_HsvAntennaFreqMapTable	i__eurdiv.m_HsvAntennaFreqMapTable
#define eurdiv_PersistentMemUpdateTimeout	i__eurdiv.m_PersistentMemUpdateTimeout
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaUserTable
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaDigSrvcTable
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaDigPtcTable
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	i__eurdiv.m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable
#define eurdiv_AvSignalDetectionTimeOut	i__eurdiv.m_AvSignalDetectionTimeOut
#define eurdiv_HearingImpairedOn	i__eurdiv.m_HearingImpairedOn
#define eurdiv_VisuallyImpairedOn	i__eurdiv.m_VisuallyImpairedOn
#define eurdiv_IsQaaSupported	i__eurdiv.m_IsQaaSupported
#define eurdiv_IsPremixedVISupported	i__eurdiv.m_IsPremixedVISupported
#define eurdiv_EPGSecondaryDirName	i__eurdiv.m_EPGSecondaryDirName
#define eurdiv_DefaultCharacterTable	i__eurdiv.m_DefaultCharacterTable
#define eurdiv_ShortInfoCacheForCountry	i__eurdiv.m_ShortInfoCacheForCountry
#define eurdiv_OUI	i__eurdiv.m_OUI
#define eurdiv_HardwareModel	i__eurdiv.m_HardwareModel
#define eurdiv_HardwareVersion	i__eurdiv.m_HardwareVersion
#define eurdiv_SubtitleTimeOut	i__eurdiv.m_SubtitleTimeOut
#define eurdiv_ForceCharacterTable	i__eurdiv.m_ForceCharacterTable
#define eurdiv_RegionalCharacterTable	i__eurdiv.m_RegionalCharacterTable
#define eurdiv_CurrentCountryInvalidLCNSortKey1	i__eurdiv.m_CurrentCountryInvalidLCNSortKey1
#define eurdiv_CurrentCountryInvalidLCNSortKey2	i__eurdiv.m_CurrentCountryInvalidLCNSortKey2
#define eurdiv_CurrentCountryInvalidLCNSortKey3	i__eurdiv.m_CurrentCountryInvalidLCNSortKey3
#define eurdiv_CurrentCountryInvalidLCNSortKey4	i__eurdiv.m_CurrentCountryInvalidLCNSortKey4
#define eurdiv_CurrentCountryInvalidLCNSortKey5	i__eurdiv.m_CurrentCountryInvalidLCNSortKey5
#define eurdiv_OtherCountrySortKey1	i__eurdiv.m_OtherCountrySortKey1
#define eurdiv_OtherCountrySortKey2	i__eurdiv.m_OtherCountrySortKey2
#define eurdiv_OtherCountrySortKey3	i__eurdiv.m_OtherCountrySortKey3
#define eurdiv_OtherCountrySortKey4	i__eurdiv.m_OtherCountrySortKey4
#define eurdiv_OtherCountrySortKey5	i__eurdiv.m_OtherCountrySortKey5
#define eurdiv_KeyInvalid	IHsvEuropeDiversity2_KeyInvalid
#define eurdiv_KeyOriginalNetworkId	IHsvEuropeDiversity2_KeyOriginalNetworkId
#define eurdiv_KeyServiceType	IHsvEuropeDiversity2_KeyServiceType
#define eurdiv_KeyLCN	IHsvEuropeDiversity2_KeyLCN
#define eurdiv_KeyServiceName	IHsvEuropeDiversity2_KeyServiceName
#define eurdiv_KeyServiceId	IHsvEuropeDiversity2_KeyServiceId
#define eurdiv_MeasureSignalStrengthWhilePlaying	i__eurdiv.m_MeasureSignalStrengthWhilePlaying
#define eurdiv_Automatic	IHsvEuropeDiversity2_Automatic
#define eurdiv_PalOnly	IHsvEuropeDiversity2_PalOnly
#define eurdiv_PalSecam	IHsvEuropeDiversity2_PalSecam
#define eurdiv_SecamPal	IHsvEuropeDiversity2_SecamPal
#define eurdiv_SecamOnly	IHsvEuropeDiversity2_SecamOnly
#define eurdiv_ChannelListVariant	i__eurdiv.m_ChannelListVariant
#define eurdiv_DefaultChannelList	IHsvEuropeDiversity2_DefaultChannelList
#define eurdiv_DualChannelList	IHsvEuropeDiversity2_DualChannelList
#define eurdiv_TripleChannelList	IHsvEuropeDiversity2_TripleChannelList
#define eurdiv_HsvCableDigSrvcTable	i__eurdiv.m_HsvCableDigSrvcTable
#define eurdiv_HsvCableDigPtcTable	i__eurdiv.m_HsvCableDigPtcTable
#define eurdiv_HsvCableSvcListDescTable	i__eurdiv.m_HsvCableSvcListDescTable
#define eurdiv_HsvCableFreqMapTable	i__eurdiv.m_HsvCableFreqMapTable
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableUserTable
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableDigSrvcTable
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableDigPtcTable
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	i__eurdiv.m_MaxNoOfMultiplexsToStoreCableFreqMapTable
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_HsvDVBCSettingsFilePath	i__eurdiv.m_HsvDVBCSettingsFilePath
#define eurdiv_HsvCableDelSysDescFilePath	i__eurdiv.m_HsvCableDelSysDescFilePath
#define eurdiv_HsvServiceListDescFilePath	i__eurdiv.m_HsvServiceListDescFilePath
#define eurdiv_MaxLCNValue	i__eurdiv.m_MaxLCNValue
#define eurdiv_SDTActual	IHsvEuropeDiversity2_SDTActual
#define eurdiv_SDTOther	IHsvEuropeDiversity2_SDTOther
#define eurdiv_SDTNone	IHsvEuropeDiversity2_SDTNone
#define eurdiv_AltHomingFrequency	IHsvEuropeDiversity2_AltHomingFrequency
#define eurdiv_AltTSRelocatedDesc	IHsvEuropeDiversity2_AltTSRelocatedDesc
#define eurdiv_AltNone	IHsvEuropeDiversity2_AltNone
#define eurdiv_AutomaticDigitalPresetAllocation	i__eurdiv.m_AutomaticDigitalPresetAllocation
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
#define lngids_iVersion	i__lngids.m_iVersion
#define log_Information	IHsvLog_Information
#define log_SoftErr	IHsvLog_SoftErr
#define log_FatalErr	IHsvLog_FatalErr
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
#define mpldiv_AvSignalDetectionTimeOut	i__mpldiv.m_AvSignalDetectionTimeOut
#define mpldiv_HearingImpairedOn	i__mpldiv.m_HearingImpairedOn
#define mpldiv_VisuallyImpairedOn	i__mpldiv.m_VisuallyImpairedOn
#define mpldiv_SubtitleOn	i__mpldiv.m_SubtitleOn
#define mpldiv_PidCachingEnabled	i__mpldiv.m_PidCachingEnabled
#define pen_PumpEngine	i__pen.m_PumpEngine
#define pgdaterr_Ok	IHsvChannelLibReturnCodes_Ok
#define pgdaterr_BadParameter	IHsvChannelLibReturnCodes_BadParameter
#define pgdaterr_ChannelTableEmpty	IHsvChannelLibReturnCodes_ChannelTableEmpty
#define pgdaterr_ChannelTableExhausted	IHsvChannelLibReturnCodes_ChannelTableExhausted
#define pgdaterr_MinorNumbersExhausted	IHsvChannelLibReturnCodes_MinorNumbersExhausted
#define pgdaterr_NotSupported	IHsvChannelLibReturnCodes_NotSupported
#define pgdaterr_FileError	IHsvChannelLibReturnCodes_FileError
#define pgdaterr_ChannelTableVersionError	IHsvChannelLibReturnCodes_ChannelTableVersionError
#define pgdaterr_ChannelTableCrcError	IHsvChannelLibReturnCodes_ChannelTableCrcError
#define pgdaterr_ChannelNotInstalled	IHsvChannelLibReturnCodes_ChannelNotInstalled
#define pgdaterr_NVMError	IHsvChannelLibReturnCodes_NVMError
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
#define pgsel_Polarization	IHsvProgramSelection2_Polarization
#define pgsel_SymbolRate	IHsvProgramSelection2_SymbolRate
#define pgsel_LnbNumber	IHsvProgramSelection2_LnbNumber
#define pgsel_AudioPid	IHsvProgramSelection2_AudioPid
#define pgsel_VideoPid	IHsvProgramSelection2_VideoPid
#define pgsel_PcrPid	IHsvProgramSelection2_PcrPid
#define pgsel_ProgramNumber	IHsvProgramSelection2_ProgramNumber
#define pgsel_ModulationStd	IHsvProgramSelection2_ModulationStd
#define pgsel_CodeRate	IHsvProgramSelection2_CodeRate
#define pgsel_InvalidAttribute	IHsvProgramSelection2_InvalidAttribute
#define plfdmx_CrcModeSkipBadSections	IPlfApiTsDmxAbstractEx_CrcModeSkipBadSections
#define plfdmx_CrcModeAcceptAllSections	IPlfApiTsDmxAbstractEx_CrcModeAcceptAllSections
#define plfdmx_CrcModeDontCheckCrc	IPlfApiTsDmxAbstractEx_CrcModeDontCheckCrc
#define plfdmx_FilterDepth	IPlfApiTsDmxAbstractEx_FilterDepth
#define plfdmx_StreamTypeInvalid	IPlfApiTsDmxAbstractEx_StreamTypeInvalid
#define plfdmx_StreamTypemp1v	IPlfApiTsDmxAbstractEx_StreamTypemp1v
#define plfdmx_StreamTypemp2v	IPlfApiTsDmxAbstractEx_StreamTypemp2v
#define plfdmx_StreamTypemp4v	IPlfApiTsDmxAbstractEx_StreamTypemp4v
#define plfdmx_StreamTypemp1a	IPlfApiTsDmxAbstractEx_StreamTypemp1a
#define plfdmx_StreamTypemp2a	IPlfApiTsDmxAbstractEx_StreamTypemp2a
#define plfdmx_StreamTypemp4a	IPlfApiTsDmxAbstractEx_StreamTypemp4a
#define plfdmx_StreamTypettxt	IPlfApiTsDmxAbstractEx_StreamTypettxt
#define plfdmx_StreamTypesubt	IPlfApiTsDmxAbstractEx_StreamTypesubt
#define plfdmx_StreamTypepcr	IPlfApiTsDmxAbstractEx_StreamTypepcr
#define plfdmx_StreamTypeac3	IPlfApiTsDmxAbstractEx_StreamTypeac3
#define plfdmx_StreamTypeh264	IPlfApiTsDmxAbstractEx_StreamTypeh264
#define plfdmx_StreamTypedivx	IPlfApiTsDmxAbstractEx_StreamTypedivx
#define plfdmx_StreamTypevc1	IPlfApiTsDmxAbstractEx_StreamTypevc1
#define plfdmx_StreamTypeaac	IPlfApiTsDmxAbstractEx_StreamTypeaac
#define plfdmx_StreamTypeheaac	IPlfApiTsDmxAbstractEx_StreamTypeheaac
#define plfdmx_StreamTypewma	IPlfApiTsDmxAbstractEx_StreamTypewma
#define plfdmx_StreamTypeddplus	IPlfApiTsDmxAbstractEx_StreamTypeddplus
#define plfdmx_StreamTypedts	IPlfApiTsDmxAbstractEx_StreamTypedts
#define plfdmx_StreamTypemmw	IPlfApiTsDmxAbstractEx_StreamTypemmw
#define plfdmx_StreamTypemma	IPlfApiTsDmxAbstractEx_StreamTypemma
#define plfdmx_StreamTypeOther	IPlfApiTsDmxAbstractEx_StreamTypeOther
#define plfdmx_StreamTypeLpcm	IPlfApiTsDmxAbstractEx_StreamTypeLpcm
#define plfdmx_InvalidSubscrId	IPlfApiTsDmxAbstractEx_InvalidSubscrId
#define plfdmx_ScramblingUnknown	IPlfApiTsDmxAbstractEx_ScramblingUnknown
#define plfdmx_NotScrambled	IPlfApiTsDmxAbstractEx_NotScrambled
#define plfdmx_Scrambled	IPlfApiTsDmxAbstractEx_Scrambled
#define plfdmx_MediaTypeAudio	IPlfApiTsDmxAbstractEx_MediaTypeAudio
#define plfdmx_MediaTypeVideo	IPlfApiTsDmxAbstractEx_MediaTypeVideo
#define plfdmx_MediaTypeAudioDesc	IPlfApiTsDmxAbstractEx_MediaTypeAudioDesc
#define plfdvbs_TUNING_DVBS_ERR_NONE	IPlfApiDvbsTuning_TUNING_DVBS_ERR_NONE
#define plfdvbs_TUNING_DVBS_ERR_BAD_PARAMETER	IPlfApiDvbsTuning_TUNING_DVBS_ERR_BAD_PARAMETER
#define plfdvbs_TUNING_DVBS_ERR_NOT_IMPLEMENTED	IPlfApiDvbsTuning_TUNING_DVBS_ERR_NOT_IMPLEMENTED
#define plfdvbs_TUNING_DVBS_ERR_EXEC_FAILURE	IPlfApiDvbsTuning_TUNING_DVBS_ERR_EXEC_FAILURE
#define plfdvbs_TUNING_DVBS_START_FREQUENCY	IPlfApiDvbsTuning_TUNING_DVBS_START_FREQUENCY
#define plfdvbs_TUNING_DVBS_END_FREQUENCY	IPlfApiDvbsTuning_TUNING_DVBS_END_FREQUENCY
#define plfdvbs_TUNING_DVBS_UNKNOWN	IPlfApiDvbsTuning_TUNING_DVBS_UNKNOWN
#define plfdvbs_TUNING_DVBS_QPSK	IPlfApiDvbsTuning_TUNING_DVBS_QPSK
#define plfdvbs_TUNING_DVBS_APSK16	IPlfApiDvbsTuning_TUNING_DVBS_APSK16
#define plfdvbs_TUNING_DVBS_APSK32	IPlfApiDvbsTuning_TUNING_DVBS_APSK32
#define plfdvbs_TUNING_DVBs_PSK8	IPlfApiDvbsTuning_TUNING_DVBs_PSK8
#define plfdvbs_TUNING_DVBS_SYMBOLRATE_MIN	IPlfApiDvbsTuning_TUNING_DVBS_SYMBOLRATE_MIN
#define plfdvbs_TUNING_DVBS_SYMBOLRATE_MAX	IPlfApiDvbsTuning_TUNING_DVBS_SYMBOLRATE_MAX
#define plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO	IPlfApiDvbsTuning_TUNING_DVBS_SR_DETECTMODE_AUTO
#define plfdvbs_TUNING_DVBS_SR_DETECTMODE_MANUAL	IPlfApiDvbsTuning_TUNING_DVBS_SR_DETECTMODE_MANUAL
#define plfdvbs_TUNING_DVBS_HORIZONTAL	IPlfApiDvbsTuning_TUNING_DVBS_HORIZONTAL
#define plfdvbs_TUNING_DVBS_VERTICAL	IPlfApiDvbsTuning_TUNING_DVBS_VERTICAL
#define plfdvbs_TUNING_DVBS_UNIVERSAL	IPlfApiDvbsTuning_TUNING_DVBS_UNIVERSAL
#define plfdvbs_TUNING_DVBS_CIRCULAR	IPlfApiDvbsTuning_TUNING_DVBS_CIRCULAR
#define plfdvbs_TUNING_DVBS_MDU1	IPlfApiDvbsTuning_TUNING_DVBS_MDU1
#define plfdvbs_TUNING_DVBS_MDU2	IPlfApiDvbsTuning_TUNING_DVBS_MDU2
#define plfdvbs_TUNING_DVBS_MDU3	IPlfApiDvbsTuning_TUNING_DVBS_MDU3
#define plfdvbs_TUNING_DVBS_MDU4	IPlfApiDvbsTuning_TUNING_DVBS_MDU4
#define plfdvbs_TUNING_DVBS_MDU5	IPlfApiDvbsTuning_TUNING_DVBS_MDU5
#define plfdvbs_TUNING_DVBS_UNICABLE	IPlfApiDvbsTuning_TUNING_DVBS_UNICABLE
#define plferrids_Ok	IPlfApiErrorIds_Ok
#define plferrids_ResourceNotOwned	IPlfApiErrorIds_ResourceNotOwned
#define plferrids_InterfaceNotAvailable	IPlfApiErrorIds_InterfaceNotAvailable
#define plferrids_InterfaceNotImplemented	IPlfApiErrorIds_InterfaceNotImplemented
#define plferrids_Other	IPlfApiErrorIds_Other
#define plfres_AudioFeaturing	ITvPlatformResource_AudioFeaturing
#define plfres_Connectivity	ITvPlatformResource_Connectivity
#define plfres_Frontend	ITvPlatformResource_Frontend
#define plfres_General	ITvPlatformResource_General
#define plfres_Infrastructure	ITvPlatformResource_Infrastructure
#define plfres_Source	ITvPlatformResource_Source
#define plfres_VideoFeaturing	ITvPlatformResource_VideoFeaturing
#define plfres_Xray	ITvPlatformResource_Xray
#define plfres_Scale	ITvPlatformResource_Scale
#define plfres_Gfx	ITvPlatformResource_Gfx
#define plfres_Mute	ITvPlatformResource_Mute
#define plfres_FullState	ITvPlatformResource_FullState
#define plfres_SubState	ITvPlatformResource_SubState
#define plfres_IdleState	ITvPlatformResource_IdleState
#define plfres_FullStateWithVideoScale	ITvPlatformResource_FullStateWithVideoScale
#define plfres_Invalid	ITvPlatformResource_Invalid
#define plfres_FullWithScaleState	ITvPlatformResource_FullWithScaleState
#define plfres_IdleWithMuteState	ITvPlatformResource_IdleWithMuteState
#define plfres_FullStateWithOutMute	ITvPlatformResource_FullStateWithOutMute
#define plfres_FrontEndState	ITvPlatformResource_FrontEndState
#define plfres_ScaleState	ITvPlatformResource_ScaleState
#define plftune_TUNING_ERR_NONE	IPlfApiTuning_TUNING_ERR_NONE
#define plftune_TUNING_ERR_BAD_PARAMETER	IPlfApiTuning_TUNING_ERR_BAD_PARAMETER
#define plftune_TUNING_ERR_NOT_IMPLEMENTED	IPlfApiTuning_TUNING_ERR_NOT_IMPLEMENTED
#define plftune_TUNING_ERR_EXEC_FAILURE	IPlfApiTuning_TUNING_ERR_EXEC_FAILURE
#define plftune_TUNING_STANDARD_DVBT	IPlfApiTuning_TUNING_STANDARD_DVBT
#define plftune_TUNING_STANDARD_DVBT2	IPlfApiTuning_TUNING_STANDARD_DVBT2
#define plftune_TUNING_STANDARD_DVBC	IPlfApiTuning_TUNING_STANDARD_DVBC
#define plftune_TUNING_STANDARD_DVBC2	IPlfApiTuning_TUNING_STANDARD_DVBC2
#define plftune_TUNING_STANDARD_DVBS2	IPlfApiTuning_TUNING_STANDARD_DVBS2
#define plftune_TUNING_STANDARD_ANALOG	IPlfApiTuning_TUNING_STANDARD_ANALOG
#define plftune_TUNING_RESULT_LOCK	IPlfApiTuning_TUNING_RESULT_LOCK
#define plftune_TUNING_RESULT_NOLOCK	IPlfApiTuning_TUNING_RESULT_NOLOCK
#define poolids_StringPool	i__poolids.m_StringPool
#define poolids_DescPool	i__poolids.m_DescPool
#define poolids_PmtSectionPool	i__poolids.m_PmtSectionPool
#define poolids_BufferPool	i__poolids.m_BufferPool
#define poolids_StringPoolVc	i__poolids.m_StringPoolVc
#define poolids_SectionBufferPool	i__poolids.m_SectionBufferPool
#define poolids_PesBufferPool	i__poolids.m_PesBufferPool
#define poolids_MsgPoolId	i__poolids.m_MsgPoolId
#define recdev_ErrorOk	IPlfApiStorageDevice_ErrorOk
#define recdev_ErrorInvalidArgument	IPlfApiStorageDevice_ErrorInvalidArgument
#define recdev_ErrorContainerListTooBig	IPlfApiStorageDevice_ErrorContainerListTooBig
#define recdev_ErrorMountPathTooBig	IPlfApiStorageDevice_ErrorMountPathTooBig
#define recdev_ErrorStorageNameTooBig	IPlfApiStorageDevice_ErrorStorageNameTooBig
#define recdev_ContTypeUnknown	IPlfApiStorageDevice_ContTypeUnknown
#define recdev_ContTypeMedia	IPlfApiStorageDevice_ContTypeMedia
#define recdev_ContTypeRecording	IPlfApiStorageDevice_ContTypeRecording
#define recdev_ContTypeTimeshift	IPlfApiStorageDevice_ContTypeTimeshift
#define recdev_ContTypeVideostore	IPlfApiStorageDevice_ContTypeVideostore
#define recdev_ContTypeAll	IPlfApiStorageDevice_ContTypeAll
#define recdev_PhysIdsAll	IPlfApiStorageDevice_PhysIdsAll
#define recdev_MaxContainerListSize	IPlfApiStorageDevice_MaxContainerListSize
#define recdev_MaxMountPathSize	IPlfApiStorageDevice_MaxMountPathSize
#define recdev_MaxStorageNameSize	IPlfApiStorageDevice_MaxStorageNameSize
#define rtk_PrioHighest	i__rtk.m_PrioHighest
#define rtk_PrioHigh	i__rtk.m_PrioHigh
#define rtk_PrioAboveNormal	i__rtk.m_PrioAboveNormal
#define rtk_PrioNormal	i__rtk.m_PrioNormal
#define rtk_PrioBelowNormal	i__rtk.m_PrioBelowNormal
#define rtk_PrioLow	i__rtk.m_PrioLow
#define rtk_PrioLowest	i__rtk.m_PrioLowest
#define s2div_iVersion	i__s2div.m_iVersion
#define srtdb2_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb2_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb2_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdbids_VcTableMain	i__srtdbids.m_VcTableMain
#define srtdbids_VcTableAux	i__srtdbids.m_VcTableAux
#define srtdbids_MgtTableMain	i__srtdbids.m_MgtTableMain
#define srtdbids_MgtTableAux	i__srtdbids.m_MgtTableAux
#define srtdbids_PmtTableMain	i__srtdbids.m_PmtTableMain
#define srtdbids_PmtTableAux	i__srtdbids.m_PmtTableAux
#define srtdbids_BasicPidInfoMain	i__srtdbids.m_BasicPidInfoMain
#define srtdbids_BasicPidInfoAux	i__srtdbids.m_BasicPidInfoAux
#define srtdbids_AudioInfoMain	i__srtdbids.m_AudioInfoMain
#define srtdbids_AudioInfoAux	i__srtdbids.m_AudioInfoAux
#define srtdbids_SubtitlingInfoMain	i__srtdbids.m_SubtitlingInfoMain
#define srtdbids_SubtitlingInfoAux	i__srtdbids.m_SubtitlingInfoAux
#define srtdbids_TeletextInfoMain	i__srtdbids.m_TeletextInfoMain
#define srtdbids_TeletextInfoAux	i__srtdbids.m_TeletextInfoAux
#define srtdbids_ComponentTagInfoMain	i__srtdbids.m_ComponentTagInfoMain
#define srtdbids_ComponentTagInfoAux	i__srtdbids.m_ComponentTagInfoAux
#define srtdbids_ReqTableMain	i__srtdbids.m_ReqTableMain
#define srtdbids_ReqTableAux	i__srtdbids.m_ReqTableAux
#define srtdbids_EitTableMain	i__srtdbids.m_EitTableMain
#define srtdbids_EitTableAux	i__srtdbids.m_EitTableAux
#define srtdbids_SimplePmtMain	i__srtdbids.m_SimplePmtMain
#define srtdbids_SimplePmtAux	i__srtdbids.m_SimplePmtAux
#define sysset_AudioFormatStandard	IHsvSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvSystemSettings_AudioFormatAdvanced
#define tprtk_TaskPrioHighest	i__tprtk.m_TaskPrioHighest
#define tprtk_TaskPrioHigh	i__tprtk.m_TaskPrioHigh
#define tprtk_TaskPrioAboveNormal	i__tprtk.m_TaskPrioAboveNormal
#define tprtk_TaskPrioNormal	i__tprtk.m_TaskPrioNormal
#define tprtk_TaskPrioBelowNormal	i__tprtk.m_TaskPrioBelowNormal
#define tprtk_TaskPrioLow	i__tprtk.m_TaskPrioLow
#define tprtk_TaskPrioLowest	i__tprtk.m_TaskPrioLowest
#define tprtk_SemSignaled	i__tprtk.m_SemSignaled
#define tprtk_SemUnsignaled	i__tprtk.m_SemUnsignaled
#define tprtk_TimeoutInfinite	i__tprtk.m_TimeoutInfinite
#define tprtk_TimeoutZero	i__tprtk.m_TimeoutZero
#define usbms_ErrorOk	IPlfApiPhysDevice_ErrorOk
#define usbms_ErrorDeviceListTooBig	IPlfApiPhysDevice_ErrorDeviceListTooBig
#define usbms_ErrorDeviceNameTooBig	IPlfApiPhysDevice_ErrorDeviceNameTooBig
#define usbms_PhysTypeUnknown	IPlfApiPhysDevice_PhysTypeUnknown
#define usbms_PhysTypeUsbMs	IPlfApiPhysDevice_PhysTypeUsbMs
#define usbms_PhysTypeUsbImage	IPlfApiPhysDevice_PhysTypeUsbImage
#define usbms_PhysTypeUsbHid	IPlfApiPhysDevice_PhysTypeUsbHid
#define usbms_PhysTypeUsbNet	IPlfApiPhysDevice_PhysTypeUsbNet
#define usbms_PhysTypeSD	IPlfApiPhysDevice_PhysTypeSD
#define usbms_PhysTypeEmmc	IPlfApiPhysDevice_PhysTypeEmmc
#define usbms_PhysTypeNetSmb	IPlfApiPhysDevice_PhysTypeNetSmb
#define usbms_PhysTypeNetNfs	IPlfApiPhysDevice_PhysTypeNetNfs
#define usbms_PhysTypeSkypeCam	IPlfApiPhysDevice_PhysTypeSkypeCam
#define usbms_PhysTypeUsbWifi	IPlfApiPhysDevice_PhysTypeUsbWifi
#define usbms_PhysTypeAll	IPlfApiPhysDevice_PhysTypeAll
#define usbms_MaxDeviceListSize	IPlfApiPhysDevice_MaxDeviceListSize
#define usbms_MaxDeviceNameSize	IPlfApiPhysDevice_MaxDeviceNameSize
#define vctl_Freeze	i__vctl.m_Freeze
#define vctl_Pan	i__vctl.m_Pan
#define vctl_ViewMode	i__vctl.m_ViewMode
#define vctl_SeamlessViewMode	i__vctl.m_SeamlessViewMode
#define vctl_PicturePos	i__vctl.m_PicturePos
#define vctl_PicturePosHoriz	i__vctl.m_PicturePosHoriz
#define vctl_VideoCoding	i__vctl.m_VideoCoding
#define vctl_VideoCodingAux	i__vctl.m_VideoCodingAux
#define vctl_ImageFormat	i__vctl.m_ImageFormat
#define vctl_AutoFormat	i__vctl.m_AutoFormat
#define vctl_VideoMute	i__vctl.m_VideoMute
#define vctl_VideoMuteAux	i__vctl.m_VideoMuteAux
#define vctl_VideoMuteScart2Out	i__vctl.m_VideoMuteScart2Out
#define vctl_VideoPresenceMain	i__vctl.m_VideoPresenceMain
#define vctl_VideoPresenceAux	i__vctl.m_VideoPresenceAux
#define vctl_IncomingFrameLinesMain	i__vctl.m_IncomingFrameLinesMain
#define vctl_IncomingVisibleFieldLinesMain	i__vctl.m_IncomingVisibleFieldLinesMain
#define vctl_IncomingSignalInterlaceMain	i__vctl.m_IncomingSignalInterlaceMain
#define vctl_IncomingFieldFrequencyMain	i__vctl.m_IncomingFieldFrequencyMain
#define vctl_IncomingVisiblePixels	i__vctl.m_IncomingVisiblePixels
#define vctl_IncomingVisiblePixelsAux	i__vctl.m_IncomingVisiblePixelsAux
#define vctl_IncomingFrameLinesAux	i__vctl.m_IncomingFrameLinesAux
#define vctl_IncomingVisibleFieldLinesAux	i__vctl.m_IncomingVisibleFieldLinesAux
#define vctl_IncomingSignalInterlaceAux	i__vctl.m_IncomingSignalInterlaceAux
#define vctl_IncomingFieldFrequencyAux	i__vctl.m_IncomingFieldFrequencyAux
#define vctl_AutoVideoMute	i__vctl.m_AutoVideoMute
#define vctl_AbsPicPosVertical	i__vctl.m_AbsPicPosVertical
#define vctl_AbsPicPosHoriz	i__vctl.m_AbsPicPosHoriz
#define vctl_VideoProtection	i__vctl.m_VideoProtection
#define vctl_LastItem	i__vctl.m_LastItem
#define vctl_FreezeOn	i__vctl.m_FreezeOn
#define vctl_FreezeOff	i__vctl.m_FreezeOff
#define vctl_PanUp	i__vctl.m_PanUp
#define vctl_PanDown	i__vctl.m_PanDown
#define vctl_PanLeft	i__vctl.m_PanLeft
#define vctl_PanRight	i__vctl.m_PanRight
#define vctl_VmNormalScreen4by3	i__vctl.m_VmNormalScreen4by3
#define vctl_VmMovieExpand14by9	i__vctl.m_VmMovieExpand14by9
#define vctl_VmMovieExpand16by9	i__vctl.m_VmMovieExpand16by9
#define vctl_VmSubtitleZoom	i__vctl.m_VmSubtitleZoom
#define vctl_VmSuperZoomMode	i__vctl.m_VmSuperZoomMode
#define vctl_VmWideScreen	i__vctl.m_VmWideScreen
#define vctl_VmMovieExpand21by9	i__vctl.m_VmMovieExpand21by9
#define vctl_VmNormalScreen	i__vctl.m_VmNormalScreen
#define vctl_VmVerticalSqueeze	i__vctl.m_VmVerticalSqueeze
#define vctl_VmExpand4by3	i__vctl.m_VmExpand4by3
#define vctl_VmPanorama	i__vctl.m_VmPanorama
#define vctl_VmHalfWindow	i__vctl.m_VmHalfWindow
#define vctl_VmHalfWindowSqueezed	i__vctl.m_VmHalfWindowSqueezed
#define vctl_VmHorizontalSqueeze	i__vctl.m_VmHorizontalSqueeze
#define vctl_VmOtherViewMode	i__vctl.m_VmOtherViewMode
#define vctl_VmAmoranap	i__vctl.m_VmAmoranap
#define vctl_VmZoomMode	i__vctl.m_VmZoomMode
#define vctl_VmHorizontalExpand	i__vctl.m_VmHorizontalExpand
#define vctl_VmPseudoPipWindow	i__vctl.m_VmPseudoPipWindow
#define vctl_VmPreviewWindow	i__vctl.m_VmPreviewWindow
#define vctl_VmNativeMode	i__vctl.m_VmNativeMode
#define vctl_VmHighRes	i__vctl.m_VmHighRes
#define vctl_VmUltraWide	i__vctl.m_VmUltraWide
#define vctl_VmUltraWideSubtitle	i__vctl.m_VmUltraWideSubtitle
#define vctl_VmUltraWide16by9	i__vctl.m_VmUltraWide16by9
#define vctl_VmVideoWindow	i__vctl.m_VmVideoWindow
#define vctl_VmUltraWideSuperZoomME16by9	i__vctl.m_VmUltraWideSuperZoomME16by9
#define vctl_VmAutofill	i__vctl.m_VmAutofill
#define vctl_VmAutozoom	i__vctl.m_VmAutozoom
#define vctl_AutoFormatMode	i__vctl.m_AutoFormatMode
#define vctl_PicturePosMin	i__vctl.m_PicturePosMin
#define vctl_PicturePosMax	i__vctl.m_PicturePosMax
#define vctl_PicturePosHorizMin	i__vctl.m_PicturePosHorizMin
#define vctl_PicturePosHorizMax	i__vctl.m_PicturePosHorizMax
#define vctl_VcCvbs	i__vctl.m_VcCvbs
#define vctl_VcYc	i__vctl.m_VcYc
#define vctl_VcYuv	i__vctl.m_VcYuv
#define vctl_VcRgb	i__vctl.m_VcRgb
#define vctl_VcYPbPr	i__vctl.m_VcYPbPr
#define vctl_VcYcOrCvbs	i__vctl.m_VcYcOrCvbs
#define vctl_VcRgb2Fh	i__vctl.m_VcRgb2Fh
#define vctl_VcYPbPr2Fh	i__vctl.m_VcYPbPr2Fh
#define vctl_VcYuv2Fh	i__vctl.m_VcYuv2Fh
#define vctl_VcRgb3Fh	i__vctl.m_VcRgb3Fh
#define vctl_VcYPbPr3Fh	i__vctl.m_VcYPbPr3Fh
#define vctl_VcYuv3Fh	i__vctl.m_VcYuv3Fh
#define vctl_VcVga	i__vctl.m_VcVga
#define vctl_VcXvga	i__vctl.m_VcXvga
#define vctl_VcSvga	i__vctl.m_VcSvga
#define vctl_VcWxvga	i__vctl.m_VcWxvga
#define vctl_ImageFormatInvalid	i__vctl.m_ImageFormatInvalid
#define vctl_ImageFormatUnknown	i__vctl.m_ImageFormatUnknown
#define vctl_ImageFormatNoImage	i__vctl.m_ImageFormatNoImage
#define vctl_ImageFormat4by3FF	i__vctl.m_ImageFormat4by3FF
#define vctl_ImageFormat14by9Top	i__vctl.m_ImageFormat14by9Top
#define vctl_ImageFormat14by9Center	i__vctl.m_ImageFormat14by9Center
#define vctl_ImageFormat16by9Top	i__vctl.m_ImageFormat16by9Top
#define vctl_ImageFormat16by9Center	i__vctl.m_ImageFormat16by9Center
#define vctl_ImageFormat4by3Use14by9	i__vctl.m_ImageFormat4by3Use14by9
#define vctl_ImageFormat16by9FF	i__vctl.m_ImageFormat16by9FF
#define vctl_ImageFormatMoreThan16by9Center	i__vctl.m_ImageFormatMoreThan16by9Center
#define vctl_ImageFormat16by9Use14by9	i__vctl.m_ImageFormat16by9Use14by9
#define vctl_ImageFormat16by9Use4by3	i__vctl.m_ImageFormat16by9Use4by3
#define vctl_VideoPresentInvalid	i__vctl.m_VideoPresentInvalid
#define vctl_VideoPresentUnknown	i__vctl.m_VideoPresentUnknown
#define vctl_VideoPresent	i__vctl.m_VideoPresent
#define vctl_VideoLost	i__vctl.m_VideoLost
#define vctl_VideoMuteBlack	i__vctl.m_VideoMuteBlack
#define vctl_VideoMuteBlue	i__vctl.m_VideoMuteBlue
#define vctl_VideoMuteGrey	i__vctl.m_VideoMuteGrey
#define vctl_VideoMuteWhite	i__vctl.m_VideoMuteWhite
#define vctl_VideoMutePogramBlack	i__vctl.m_VideoMutePogramBlack
#define vctl_VideoMutePogramGrey	i__vctl.m_VideoMutePogramGrey
#define vctl_VideoMuteColourMin	i__vctl.m_VideoMuteColourMin
#define vctl_VideoMuteColourMax	i__vctl.m_VideoMuteColourMax
#define vctl_SigInterlace	i__vctl.m_SigInterlace
#define vctl_SigProgressive	i__vctl.m_SigProgressive
#define vctl_SigInterlaceInvalid	i__vctl.m_SigInterlaceInvalid
#define vctl_SigInterlaceUnknown	i__vctl.m_SigInterlaceUnknown
#define vctl_SigInterlaceOneOne	i__vctl.m_SigInterlaceOneOne
#define vctl_SigInterlaceTwoOne	i__vctl.m_SigInterlaceTwoOne
#define vctl_SigInterlaceFourTwo	i__vctl.m_SigInterlaceFourTwo
#define vctl_AbsPicPosVerticalMin	i__vctl.m_AbsPicPosVerticalMin
#define vctl_AbsPicPosVerticalMax	i__vctl.m_AbsPicPosVerticalMax
#define vctl_AbsPicPosHorizMin	i__vctl.m_AbsPicPosHorizMin
#define vctl_AbsPicPosHorizMax	i__vctl.m_AbsPicPosHorizMax
#define vctl_UnKnown	i__vctl.m_UnKnown
#define vctl_IgnoreValue	i__vctl.m_IgnoreValue
#define vctl_ResetValue	i__vctl.m_ResetValue
#define vctl_VideoPropertyMaxValue	ISvcVideoControl3_VideoPropertyMaxValue
#define wnddest_InvalidWindowId	i__wnddest.m_InvalidWindowId
#define wnddest_WndTypeInvalid	IHsvWindowDestinationMap_WndTypeInvalid
#define wnddest_WndTypeMainVideo	IHsvWindowDestinationMap_WndTypeMainVideo
#define wnddest_WndTypeMainAudio	IHsvWindowDestinationMap_WndTypeMainAudio
#define wnddest_WndTypeMonitor	IHsvWindowDestinationMap_WndTypeMonitor
#define wnddest_WndTypeAuxVideo	IHsvWindowDestinationMap_WndTypeAuxVideo
#define dvbset_GetAttribute(attribute) dvbset->GetAttribute(attribute)
#define dvbset_GetLnbSettings(LnbSettings)	dvbset->GetLnbSettings(LnbSettings)
#define dvbset_AttributePackageId IHsvSatelliteSettings_AttributePackageId
#define globalsettings_GetValuesFromGlobalSettings(ID,Value)  globalsettings->GetValuesFromGlobalSettings(ID,Value)
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
#include "locals_mdummy.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

