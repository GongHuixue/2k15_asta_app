#ifndef  _CHSVEUROPEINSTALLATION_MSYSCTL_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MSYSCTL_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationUtility.h>
#include <IHsvInstallationSystemControl.h>
#include <ISvcAudioControl4ExEx.h>
#include <IHsvDestinationConfiguration.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvLog.h>
#include <ISvcVideoControl3.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_msysctl_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_msysctl_Priv::
#include "locals_msysctl.h"

class CHsvEuropeInstallation_msysctl_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_msysctl_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msysctl.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvInstallationUtilityImpl(CHsvEuropeInstallation_msysctl_Priv,instutil);
IHsvInstallationSystemControlImpl(CHsvEuropeInstallation_msysctl_Priv,sysctl);
public:
ProvidesInterface<IHsvInstallationUtility>	instutil;

ProvidesInterface<IHsvInstallationSystemControl>	sysctl;

//Required interfaces
public:
RequiresInterface<ISvcAudioControl4ExEx>	actl;
RequiresInterface<IHsvDestinationConfiguration>	destconfig;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvLog>	log;
RequiresInterface<ISvcVideoControl3>	vctl;

public:
CHsvEuropeInstallation_msysctl_Priv():i__instutil(this),i__sysctl(this)
{
instutil	=	&i__instutil;
sysctl	=	&i__sysctl;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define actl_iPresent() (actl.Present())
#define actl_Get(audioProperty)	actl->Get(audioProperty)
#define actl_Set(audioProperty,value)	actl->Set(audioProperty,value)
#define actl_Set2(audioProperty,value1,value2)	actl->Set2(audioProperty,value1,value2)
#define actl_Get2(audioproperty,value1)	actl->Get2(audioproperty,value1)
#define actl_IsAvailable(audioProperty,value)	actl->IsAvailable(audioProperty,value)
#define actl_IsControllable(audioProperty,value)	actl->IsControllable(audioProperty,value)
#define actl_IsAvailable2(audioProperty,value1,value2)	actl->IsAvailable2(audioProperty,value1,value2)
#define actl_IsControllable2(audioProperty,value1,value2)	actl->IsControllable2(audioProperty,value1,value2)
#define actl_Volume	actl->Volume()
#define actl_SmartSound	actl->SmartSound()
#define actl_VIAudioVolume	actl->VIAudioVolume()
#define actl_VIRouting	actl->VIRouting()
#define actl_VIRoutingEx	actl->VIRoutingEx()
#define actl_VINone	actl->VINone()
#define actl_VIOn	actl->VIOn()
#define actl_VISpeakerOutput	actl->VISpeakerOutput()
#define actl_VIHeadphoneOutput	actl->VIHeadphoneOutput()
#define actl_VIMonitorOutput	actl->VIMonitorOutput()
#define actl_VISpdifOutput	actl->VISpdifOutput()
#define actl_SeamlessMixing	actl->SeamlessMixing()
#define actl_SeamlessMixing_Off	actl->SeamlessMixing_Off()
#define actl_SeamlessMixing_On	actl->SeamlessMixing_On()
#define actl_SpeechPreference	actl->SpeechPreference()
#define actl_SpeechPreference_Descriptive	actl->SpeechPreference_Descriptive()
#define actl_SpeechPreference_Subtitles	actl->SpeechPreference_Subtitles()
#define actl_OriginalLanguage	actl->OriginalLanguage()
#define actl_OriginalLanguage_On	actl->OriginalLanguage_On()
#define actl_OriginalLanguage_Off	actl->OriginalLanguage_Off()
#define actl_SoundFormat	actl->SoundFormat()
#define actl_SpdifStatus	actl->SpdifStatus()
#define actl_SoundSystem	actl->SoundSystem()
#define actl_Mute	actl->Mute()
#define actl_ProgramMute	ISvcAudioControl4ExEx_ProgramMute
#define actl_PreferedStereo	actl->PreferedStereo()
#define actl_Language	actl->Language()
#define actl_LanguageChina	actl->LanguageChina()
#define actl_None	actl->None()
#define actl_SpeakerOutput	ISvcAudioControl4ExEx_SpeakerOutput
#define actl_HeadphoneOutput	actl->HeadphoneOutput()
#define actl_MonitorOutput	actl->MonitorOutput()
#define actl_SpdifOutput	actl->SpdifOutput()
#define actl_Scart1Output	actl->Scart1Output()
#define actl_Scart2Output	actl->Scart2Output()
#define actl_AllOutput	ISvcAudioControl4ExEx_AllOutput
#define actl_BoolTrue	ISvcAudioControl4ExEx_BoolTrue
#define actl_BoolFalse	ISvcAudioControl4ExEx_BoolFalse
#define actl_IgnoreValue	actl->IgnoreValue()
#define actl_VolumeMin	actl->VolumeMin()
#define actl_VolumeMax	actl->VolumeMax()
#define actl_VIVolumeMin	actl->VIVolumeMin()
#define actl_VIVolumeMax	actl->VIVolumeMax()
#define actl_SmOff	actl->SmOff()
#define actl_SmDolbyPrologic	actl->SmDolbyPrologic()
#define actl_SmFront3Stereo	actl->SmFront3Stereo()
#define actl_SmHall	actl->SmHall()
#define actl_SmIncredible3Dsurround	actl->SmIncredible3Dsurround()
#define actl_SmSpatial	actl->SmSpatial()
#define actl_SmIncredibleSurround	actl->SmIncredibleSurround()
#define actl_SmStereo4	actl->SmStereo4()
#define actl_SmDigitalDolby	actl->SmDigitalDolby()
#define actl_SmMPEGMultiChannel	actl->SmMPEGMultiChannel()
#define actl_SmIncredibleMono	actl->SmIncredibleMono()
#define actl_SmIncredibleStereo	actl->SmIncredibleStereo()
#define actl_SmVDS422	actl->SmVDS422()
#define actl_SmVDS423	actl->SmVDS423()
#define actl_SmVDS521	actl->SmVDS521()
#define actl_SmVDS522	actl->SmVDS522()
#define actl_SmMatrix	actl->SmMatrix()
#define actl_SmDolbyPrologicII	actl->SmDolbyPrologicII()
#define actl_SmDigital3D	actl->SmDigital3D()
#define actl_SmVirtualDolbyDigital	actl->SmVirtualDolbyDigital()
#define actl_SmDolbyPrologicPhantom	actl->SmDolbyPrologicPhantom()
#define actl_SndNICAMRelatedStereo	actl->SndNICAMRelatedStereo()
#define actl_SndNICAMRelatedDual	actl->SndNICAMRelatedDual()
#define actl_SndNICAMRelatedMono	actl->SndNICAMRelatedMono()
#define actl_SndNICAMUnrelatedStereo	actl->SndNICAMUnrelatedStereo()
#define actl_SndNICAMUnrelatedDual	actl->SndNICAMUnrelatedDual()
#define actl_SndNICAMUnrelatedMono	actl->SndNICAMUnrelatedMono()
#define actl_SndNICAMData	actl->SndNICAMData()
#define actl_SndFMStereo	actl->SndFMStereo()
#define actl_SndFMDual	actl->SndFMDual()
#define actl_SndFMAMMono	actl->SndFMAMMono()
#define actl_SndEIAJMono	actl->SndEIAJMono()
#define actl_SndEIAJStereo	actl->SndEIAJStereo()
#define actl_SndEIAJDual	actl->SndEIAJDual()
#define actl_SndAMMono	actl->SndAMMono()
#define actl_SndBTSCMono	actl->SndBTSCMono()
#define actl_SndBTSCStereo	actl->SndBTSCStereo()
#define actl_SndBTSCMonoSap	actl->SndBTSCMonoSap()
#define actl_SndBTSCStereoSap	actl->SndBTSCStereoSap()
#define actl_SndBasebandMono	actl->SndBasebandMono()
#define actl_SndBasebandStereo	actl->SndBasebandStereo()
#define actl_SndNoSoundSystem	actl->SndNoSoundSystem()
#define actl_McChannelOnePlusOne	actl->McChannelOnePlusOne()
#define actl_McChannelTwoPlusTwo	actl->McChannelTwoPlusTwo()
#define actl_McChannelOneByZero	actl->McChannelOneByZero()
#define actl_McChannelTwoByZero	actl->McChannelTwoByZero()
#define actl_McChannelTwoByOne	actl->McChannelTwoByOne()
#define actl_McChannelTwoByTwo	actl->McChannelTwoByTwo()
#define actl_McChannelThreeByZero	actl->McChannelThreeByZero()
#define actl_McChannelThreeByOne	actl->McChannelThreeByOne()
#define actl_McChannelThreeByTwo	actl->McChannelThreeByTwo()
#define actl_McChannelTwoByOneKaraoke	actl->McChannelTwoByOneKaraoke()
#define actl_McChannelTwoByTwoKaraoke	actl->McChannelTwoByTwoKaraoke()
#define actl_McChannelThreeByOneKaraoke	actl->McChannelThreeByOneKaraoke()
#define actl_McChannelThreeByTwoKaraoke	actl->McChannelThreeByTwoKaraoke()
#define actl_McChannelThreeByZeroKaraoke	actl->McChannelThreeByZeroKaraoke()
#define actl_McChannelPCMStereo	actl->McChannelPCMStereo()
#define actl_McChannelNotSupported	actl->McChannelNotSupported()
#define actl_SfAnalog	actl->SfAnalog()
#define actl_SfNICAM	actl->SfNICAM()
#define actl_SfMPEG	actl->SfMPEG()
#define actl_SfPCM	actl->SfPCM()
#define actl_SfDolbyDigital	actl->SfDolbyDigital()
#define actl_SfEIAJ	actl->SfEIAJ()
#define actl_Sf2CS	actl->Sf2CS()
#define actl_SfDTS	actl->SfDTS()
#define actl_SfBaseBand	actl->SfBaseBand()
#define actl_SfAAC	actl->SfAAC()
#define actl_SfUnknown	actl->SfUnknown()
#define actl_SfDolbyDigitalPlus	actl->SfDolbyDigitalPlus()
#define actl_LangEnglish	ISvcAudioControl4ExEx_LangEnglish
#define actl_LangGerman	ISvcAudioControl4ExEx_LangGerman
#define actl_LangSwedish	ISvcAudioControl4ExEx_LangSwedish
#define actl_LangItalian	ISvcAudioControl4ExEx_LangItalian
#define actl_LangFrench	ISvcAudioControl4ExEx_LangFrench
#define actl_LangSpanish	ISvcAudioControl4ExEx_LangSpanish
#define actl_LangCzechSlovak	ISvcAudioControl4ExEx_LangCzechSlovak
#define actl_LangPolish	ISvcAudioControl4ExEx_LangPolish
#define actl_LangTurkish	ISvcAudioControl4ExEx_LangTurkish
#define actl_LangRumainian	ISvcAudioControl4ExEx_LangRumainian
#define actl_LangRussian	ISvcAudioControl4ExEx_LangRussian
#define actl_LangEstonian	ISvcAudioControl4ExEx_LangEstonian
#define actl_LangUkrainian	ISvcAudioControl4ExEx_LangUkrainian
#define actl_LangGreek	ISvcAudioControl4ExEx_LangGreek
#define actl_LangArabic	ISvcAudioControl4ExEx_LangArabic
#define actl_LangHebrew	ISvcAudioControl4ExEx_LangHebrew
#define actl_LangUndefined	ISvcAudioControl4ExEx_LangUndefined
#define actl_LanguageOne	ISvcAudioControl4ExEx_LanguageOne
#define actl_LanguageTwo	ISvcAudioControl4ExEx_LanguageTwo
#define actl_LanguageDualOne	ISvcAudioControl4ExEx_LanguageDualOne
#define actl_LanguageDualTwo	ISvcAudioControl4ExEx_LanguageDualTwo
#define actl_LanguageStereo	ISvcAudioControl4ExEx_LanguageStereo
#define actl_AudioPropertyMaxValue	ISvcAudioControl4ExEx_AudioPropertyMaxValue
#define actl_SpdifUnsupported	actl->SpdifUnsupported()
#define actl_NormalAnalog	actl->NormalAnalog()
#define actl_AnalogMode	actl->AnalogMode()
#define actl_DigitalMode	actl->DigitalMode()
#define destconfig_iPresent() (destconfig.Present())
#define destconfig_iVersion	destconfig->iVersion()
#define destconfig_NoOfDestinations	destconfig->NoOfDestinations()
#define destconfig_destPropVideo	destconfig->destPropVideo()
#define destconfig_destPropAudio	destconfig->destPropAudio()
#define destconfig_destPropLockable	destconfig->destPropLockable()
#define destconfig_IsMemberDestination(memberDest,grpDest)	destconfig->IsMemberDestination(memberDest,grpDest)
#define destconfig_GetMemberDestinations(grpDest)	destconfig->GetMemberDestinations(grpDest)
#define destconfig_IsDestinationSupported(Dest)	destconfig->IsDestinationSupported(Dest)
#define destconfig_IsAudioOnlyDestination(Dest)	destconfig->IsAudioOnlyDestination(Dest)
#define destconfig_IsGroupDestination(Dest)	destconfig->IsGroupDestination(Dest)
#define destconfig_CheckProperty(dest,prop)	destconfig->CheckProperty(dest,prop)
#define div_iPresent() (div.Present())
#define div_iVersion	div->iVersion()
#define div_MaxPresets	IHsvPresetInstallationDiv_MaxPresets
#define div_PresetNameLength	IHsvPresetInstallationDiv_PresetNameLength
#define div_TxtResetTimeoutTime	div->TxtResetTimeoutTime()
#define div_SorCChannelSupported	div->SorCChannelSupported()
#define div_TxtInfoTimeoutTime	div->TxtInfoTimeoutTime()
#define div_AciOverallTimeoutTime	div->AciOverallTimeoutTime()
#define div_NITTimeoutTime	div->NITTimeoutTime()
#define div_SecondPassSearchSupported(country)	div->SecondPassSearchSupported(country)
#define div_SignalStrengthSorting	div->SignalStrengthSorting()
#define div_WeakSignalStrengthThreshold	div->WeakSignalStrengthThreshold()
#define div_AttenuatorDetectionInInstall	div->AttenuatorDetectionInInstall()
#define div_SupportNameExtractionInManIns	div->SupportNameExtractionInManIns()
#define div_GetDefaultPresetName	div->GetDefaultPresetName()
#define div_SearchForTvSystemInInstallation	div->SearchForTvSystemInInstallation()
#define div_SearchForColorSystemInInstallation	div->SearchForColorSystemInInstallation()
#define div_SortPresetsInAutoStoreModeNone	div->SortPresetsInAutoStoreModeNone()
#define div_SignalStrengthTimeoutTime	div->SignalStrengthTimeoutTime()
#define div_ManualSearchWithWrapAround	div->ManualSearchWithWrapAround()
#define div_ImmediateStoreInAutoInstall	div->ImmediateStoreInAutoInstall()
#define div_AudioMuteDuringInstall	div->AudioMuteDuringInstall()
#define div_NameExtractionDuringImplicitManInstall	div->NameExtractionDuringImplicitManInstall()
#define div_HandleSorCStationNotFoundinManInstall	div->HandleSorCStationNotFoundinManInstall()
#define div_DefaultSystemLanguage	div->DefaultSystemLanguage()
#define div_CookieDefaultValue	div->CookieDefaultValue()
#define div_MpegSectionsAcquisitionTimeout	div->MpegSectionsAcquisitionTimeout()
#define div_BlankVideo	div->BlankVideo()
#define div_SigStrengthThresholdValue	div->SigStrengthThresholdValue()
#define div_FirstInstallationPass	div->FirstInstallationPass()
#define div_PgctrlMuteColor	div->PgctrlMuteColor()
#define div_MaxPresetNo	div->MaxPresetNo()
#define div_MinPresetNo	div->MinPresetNo()
#define div_AnalogOnly	div->AnalogOnly()
#define div_InstallTestStreams(installationmode,medium)	div->InstallTestStreams(installationmode,medium)
#define div_NotInstall	div->NotInstall()
#define div_Install	div->Install()
#define div_Hide	div->Hide()
#define div_SupportMultipleOriginalNetworkId(medium)	div->SupportMultipleOriginalNetworkId(medium)
#define div_InstallDuplicateTsids(medium)	div->InstallDuplicateTsids(medium)
#define div_StreamPriorityToBeUsed(medium)	div->StreamPriorityToBeUsed(medium)
#define div_IsServiceInstallable(medium,ServiceType)	div->IsServiceInstallable(medium,ServiceType)
#define div_IsServiceSortable(medium,ServiceType)	div->IsServiceSortable(medium,ServiceType)
#define div_IsServiceHidden(medium,ServiceType)	div->IsServiceHidden(medium,ServiceType)
#define div_UpdateChannelName(medium)	div->UpdateChannelName(medium)
#define div_UpdateLCN(medium)	div->UpdateLCN(medium)
#define div_ChannelListVariant	div->ChannelListVariant()
#define div_DefaultChannelList	div->DefaultChannelList()
#define div_DualChannelList	div->DualChannelList()
#define div_TripleChannelList	div->TripleChannelList()
#define div_SkipInstallationPass	div->SkipInstallationPass()
#define div_AutoCommitOnInstallation	div->AutoCommitOnInstallation()
#define div_TripletKey(medium)	div->TripletKey(medium)
#define div_InstallDuplicateServices(medium)	div->InstallDuplicateServices(medium)
#define div_SkipAnalog	IHsvPresetInstallationDiv_SkipAnalog
#define div_SkipDigital	IHsvPresetInstallationDiv_SkipDigital
#define div_SkipNone	IHsvPresetInstallationDiv_SkipNone
#define div_ClearDataOnAutoInstallation	div->ClearDataOnAutoInstallation()
#define div_AnalogInstallationSequence	div->AnalogInstallationSequence()
#define div_PalOnly	IHsvPresetInstallationDiv_PalOnly
#define div_PalSecam	IHsvPresetInstallationDiv_PalSecam
#define div_SecamPal	IHsvPresetInstallationDiv_SecamPal
#define div_SecamOnly	IHsvPresetInstallationDiv_SecamOnly
#define div_CurrentCountryInvalidLCNSortKey1	div->CurrentCountryInvalidLCNSortKey1()
#define div_CurrentCountryInvalidLCNSortKey2	div->CurrentCountryInvalidLCNSortKey2()
#define div_CurrentCountryInvalidLCNSortKey3	div->CurrentCountryInvalidLCNSortKey3()
#define div_CurrentCountryInvalidLCNSortKey4	div->CurrentCountryInvalidLCNSortKey4()
#define div_CurrentCountryInvalidLCNSortKey5	div->CurrentCountryInvalidLCNSortKey5()
#define div_OtherCountrySortKey1	div->OtherCountrySortKey1()
#define div_OtherCountrySortKey2	div->OtherCountrySortKey2()
#define div_OtherCountrySortKey3	div->OtherCountrySortKey3()
#define div_OtherCountrySortKey4	div->OtherCountrySortKey4()
#define div_OtherCountrySortKey5	div->OtherCountrySortKey5()
#define div_KeyInvalid	IHsvPresetInstallationDiv_KeyInvalid
#define div_KeyOriginalNetworkId	IHsvPresetInstallationDiv_KeyOriginalNetworkId
#define div_KeyServiceType	IHsvPresetInstallationDiv_KeyServiceType
#define div_KeyLCN	IHsvPresetInstallationDiv_KeyLCN
#define div_KeyServiceName	IHsvPresetInstallationDiv_KeyServiceName
#define div_KeyServiceId	IHsvPresetInstallationDiv_KeyServiceId
#define div_MaxAnalogPresets	IHsvPresetInstallationDiv_MaxAnalogPresets
#define div_SupportEmptyAnalogChannels	div->SupportEmptyAnalogChannels()
#define div_StorePresetsOnStopInstallation	div->StorePresetsOnStopInstallation()
#define div_DefaultTunerPresetFrequency	div->DefaultTunerPresetFrequency()
#define div_MaxLCNValue	div->MaxLCNValue()
#define div_FreqListSortedTableId	div->FreqListSortedTableId()
#define div_GetViterbiBER()	div->GetViterbiBER()
#define div_DeltaViterbiBER()	div->DeltaViterbiBER()
#define log_iPresent() (log.Present())
#define log_Information	IHsvLog_Information
#define log_SoftErr	IHsvLog_SoftErr
#define log_FatalErr	IHsvLog_FatalErr
#define log_Error(prio,errid)	log->Error(prio,errid)
#define log_Trace(callerid,arg1,arg2)	log->Trace(callerid,arg1,arg2)
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
#define vctl_VideoMute	ISvcVideoControl3_VideoMute
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
#define vctl_VcVga	ISvcVideoControl3_VcVga
#define vctl_VcXvga	ISvcVideoControl3_VcXvga
#define vctl_VcSvga	ISvcVideoControl3_VcSvga
#define vctl_VcWxvga	ISvcVideoControl3_VcWxvga
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
#define vctl_VideoMutePogramBlack	ISvcVideoControl3_VideoMutePogramBlack
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
#include "locals_msysctl.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

