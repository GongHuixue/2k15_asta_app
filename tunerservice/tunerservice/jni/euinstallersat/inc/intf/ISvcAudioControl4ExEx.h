#ifndef ISVCAUDIOCONTROL4EXEX_H
#define ISVCAUDIOCONTROL4EXEX_H
#include <intfparam.h>
#include <provreq.h>
class ISvcAudioControl4ExEx
{
public:
	virtual ~ISvcAudioControl4ExEx(){}
	virtual int Get(int audioProperty)= 0;
	virtual void Set(int audioProperty,int value)= 0;
	virtual void Set2(int audioProperty,int value1,int value2)= 0;
	virtual int Get2(int audioproperty,int value1)= 0;
	virtual Bool IsAvailable(int audioProperty,int value)= 0;
	virtual Bool IsControllable(int audioProperty,int value)= 0;
	virtual Bool IsAvailable2(int audioProperty,int value1,int value2)= 0;
	virtual Bool IsControllable2(int audioProperty,int value1,int value2)= 0;
	virtual int Volume(void)= 0;
	virtual int SmartSound(void)= 0;
	virtual int VIAudioVolume(void)= 0;
	virtual int VIRouting(void)= 0;
	virtual int VIRoutingEx(void)= 0;
	virtual int VINone(void)= 0;
	virtual int VIOn(void)= 0;
	virtual int VISpeakerOutput(void)= 0;
	virtual int VIHeadphoneOutput(void)= 0;
	virtual int VIMonitorOutput(void)= 0;
	virtual int VISpdifOutput(void)= 0;
	virtual Bool SeamlessMixing(void)= 0;
	virtual int SeamlessMixing_Off(void)= 0;
	virtual int SeamlessMixing_On(void)= 0;
	virtual int SpeechPreference(void)= 0;
	virtual int SpeechPreference_Descriptive(void)= 0;
	virtual int SpeechPreference_Subtitles(void)= 0;
	virtual int OriginalLanguage(void)= 0;
	virtual int OriginalLanguage_On(void)= 0;
	virtual int OriginalLanguage_Off(void)= 0;
	virtual int SoundFormat(void)= 0;
	virtual int SpdifStatus(void)= 0;
	virtual int SoundSystem(void)= 0;
	virtual int Mute(void)= 0;
	virtual int ProgramMute(void)= 0;
	virtual int PreferedStereo(void)= 0;
	virtual int Language(void)= 0;
	virtual int LanguageChina(void)= 0;
	virtual int None(void)= 0;
	virtual int SpeakerOutput(void)= 0;
	virtual int HeadphoneOutput(void)= 0;
	virtual int MonitorOutput(void)= 0;
	virtual int SpdifOutput(void)= 0;
	virtual int Scart1Output(void)= 0;
	virtual int Scart2Output(void)= 0;
	virtual int AllOutput(void)= 0;
	virtual int BoolTrue(void)= 0;
	virtual int BoolFalse(void)= 0;
	virtual int IgnoreValue(void)= 0;
	virtual int VolumeMin(void)= 0;
	virtual int VolumeMax(void)= 0;
	virtual int VIVolumeMin(void)= 0;
	virtual int VIVolumeMax(void)= 0;
	virtual int SmOff(void)= 0;
	virtual int SmDolbyPrologic(void)= 0;
	virtual int SmFront3Stereo(void)= 0;
	virtual int SmHall(void)= 0;
	virtual int SmIncredible3Dsurround(void)= 0;
	virtual int SmSpatial(void)= 0;
	virtual int SmIncredibleSurround(void)= 0;
	virtual int SmStereo4(void)= 0;
	virtual int SmDigitalDolby(void)= 0;
	virtual int SmMPEGMultiChannel(void)= 0;
	virtual int SmIncredibleMono(void)= 0;
	virtual int SmIncredibleStereo(void)= 0;
	virtual int SmVDS422(void)= 0;
	virtual int SmVDS423(void)= 0;
	virtual int SmVDS521(void)= 0;
	virtual int SmVDS522(void)= 0;
	virtual int SmMatrix(void)= 0;
	virtual int SmDolbyPrologicII(void)= 0;
	virtual int SmDigital3D(void)= 0;
	virtual int SmVirtualDolbyDigital(void)= 0;
	virtual int SmDolbyPrologicPhantom(void)= 0;
	virtual int SndNICAMRelatedStereo(void)= 0;
	virtual int SndNICAMRelatedDual(void)= 0;
	virtual int SndNICAMRelatedMono(void)= 0;
	virtual int SndNICAMUnrelatedStereo(void)= 0;
	virtual int SndNICAMUnrelatedDual(void)= 0;
	virtual int SndNICAMUnrelatedMono(void)= 0;
	virtual int SndNICAMData(void)= 0;
	virtual int SndFMStereo(void)= 0;
	virtual int SndFMDual(void)= 0;
	virtual int SndFMAMMono(void)= 0;
	virtual int SndEIAJMono(void)= 0;
	virtual int SndEIAJStereo(void)= 0;
	virtual int SndEIAJDual(void)= 0;
	virtual int SndAMMono(void)= 0;
	virtual int SndBTSCMono(void)= 0;
	virtual int SndBTSCStereo(void)= 0;
	virtual int SndBTSCMonoSap(void)= 0;
	virtual int SndBTSCStereoSap(void)= 0;
	virtual int SndBasebandMono(void)= 0;
	virtual int SndBasebandStereo(void)= 0;
	virtual int SndNoSoundSystem(void)= 0;
	virtual int McChannelOnePlusOne(void)= 0;
	virtual int McChannelTwoPlusTwo(void)= 0;
	virtual int McChannelOneByZero(void)= 0;
	virtual int McChannelTwoByZero(void)= 0;
	virtual int McChannelTwoByOne(void)= 0;
	virtual int McChannelTwoByTwo(void)= 0;
	virtual int McChannelThreeByZero(void)= 0;
	virtual int McChannelThreeByOne(void)= 0;
	virtual int McChannelThreeByTwo(void)= 0;
	virtual int McChannelTwoByOneKaraoke(void)= 0;
	virtual int McChannelTwoByTwoKaraoke(void)= 0;
	virtual int McChannelThreeByOneKaraoke(void)= 0;
	virtual int McChannelThreeByTwoKaraoke(void)= 0;
	virtual int McChannelThreeByZeroKaraoke(void)= 0;
	virtual int McChannelPCMStereo(void)= 0;
	virtual int McChannelNotSupported(void)= 0;
	virtual int SfAnalog(void)= 0;
	virtual int SfNICAM(void)= 0;
	virtual int SfMPEG(void)= 0;
	virtual int SfPCM(void)= 0;
	virtual int SfDolbyDigital(void)= 0;
	virtual int SfEIAJ(void)= 0;
	virtual int Sf2CS(void)= 0;
	virtual int SfDTS(void)= 0;
	virtual int SfBaseBand(void)= 0;
	virtual int SfAAC(void)= 0;
	virtual int SfUnknown(void)= 0;
	virtual int SfDolbyDigitalPlus(void)= 0;
	#define ISvcAudioControl4ExEx_LangEnglish		((int)0 )
	#define ISvcAudioControl4ExEx_LangGerman		((int)1 )
	#define ISvcAudioControl4ExEx_LangSwedish		((int)2 )
	#define ISvcAudioControl4ExEx_LangItalian		((int)3 )
	#define ISvcAudioControl4ExEx_LangFrench		((int)4 )
	#define ISvcAudioControl4ExEx_LangSpanish		((int)5 )
	#define ISvcAudioControl4ExEx_LangCzechSlovak		((int)6 )
	#define ISvcAudioControl4ExEx_LangPolish		((int)7 )
	#define ISvcAudioControl4ExEx_LangTurkish		((int)8 )
	#define ISvcAudioControl4ExEx_LangRumainian		((int)9 )
	#define ISvcAudioControl4ExEx_LangRussian		((int)10 )
	#define ISvcAudioControl4ExEx_LangEstonian		((int)11 )
	#define ISvcAudioControl4ExEx_LangUkrainian		((int)12 )
	#define ISvcAudioControl4ExEx_LangGreek		((int)13 )
	#define ISvcAudioControl4ExEx_LangArabic		((int)14 )
	#define ISvcAudioControl4ExEx_LangHebrew		((int)15 )
	#define ISvcAudioControl4ExEx_LangUndefined		((int)16 )
	#define ISvcAudioControl4ExEx_LanguageOne		((int)17 )
	#define ISvcAudioControl4ExEx_LanguageTwo		((int)18 )
	#define ISvcAudioControl4ExEx_LanguageDualOne		((int)19 )
	#define ISvcAudioControl4ExEx_LanguageDualTwo		((int)20 )
	#define ISvcAudioControl4ExEx_LanguageStereo		((int)21 )
	#define ISvcAudioControl4ExEx_AudioPropertyMaxValue		((int)100 )
	virtual int SpdifUnsupported(void)= 0;
	virtual int NormalAnalog(void)= 0;
	virtual int AnalogMode(void)= 0;
	virtual int DigitalMode(void)= 0;
};


#define ISvcAudioControl4ExExImpl(Comp,intf)    \
virtual int intf ## _Get(int audioProperty);\
virtual void intf ## _Set(int audioProperty,int value);\
virtual void intf ## _Set2(int audioProperty,int value1,int value2);\
virtual int intf ## _Get2(int audioproperty,int value1);\
virtual Bool intf ## _IsAvailable(int audioProperty,int value);\
virtual Bool intf ## _IsControllable(int audioProperty,int value);\
virtual Bool intf ## _IsAvailable2(int audioProperty,int value1,int value2);\
virtual Bool intf ## _IsControllable2(int audioProperty,int value1,int value2);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public ISvcAudioControl4ExEx \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_Volume; \
    InterfaceParam<Comp,int> m_SmartSound; \
    InterfaceParam<Comp,int> m_VIAudioVolume; \
    InterfaceParam<Comp,int> m_VIRouting; \
    InterfaceParam<Comp,int> m_VIRoutingEx; \
    InterfaceParam<Comp,int> m_VINone; \
    InterfaceParam<Comp,int> m_VIOn; \
    InterfaceParam<Comp,int> m_VISpeakerOutput; \
    InterfaceParam<Comp,int> m_VIHeadphoneOutput; \
    InterfaceParam<Comp,int> m_VIMonitorOutput; \
    InterfaceParam<Comp,int> m_VISpdifOutput; \
    InterfaceParam<Comp,Bool> m_SeamlessMixing; \
    InterfaceParam<Comp,int> m_SeamlessMixing_Off; \
    InterfaceParam<Comp,int> m_SeamlessMixing_On; \
    InterfaceParam<Comp,int> m_SpeechPreference; \
    InterfaceParam<Comp,int> m_SpeechPreference_Descriptive; \
    InterfaceParam<Comp,int> m_SpeechPreference_Subtitles; \
    InterfaceParam<Comp,int> m_OriginalLanguage; \
    InterfaceParam<Comp,int> m_OriginalLanguage_On; \
    InterfaceParam<Comp,int> m_OriginalLanguage_Off; \
    InterfaceParam<Comp,int> m_SoundFormat; \
    InterfaceParam<Comp,int> m_SpdifStatus; \
    InterfaceParam<Comp,int> m_SoundSystem; \
    InterfaceParam<Comp,int> m_Mute; \
    InterfaceParam<Comp,int> m_ProgramMute; \
    InterfaceParam<Comp,int> m_PreferedStereo; \
    InterfaceParam<Comp,int> m_Language; \
    InterfaceParam<Comp,int> m_LanguageChina; \
    InterfaceParam<Comp,int> m_None; \
    InterfaceParam<Comp,int> m_SpeakerOutput; \
    InterfaceParam<Comp,int> m_HeadphoneOutput; \
    InterfaceParam<Comp,int> m_MonitorOutput; \
    InterfaceParam<Comp,int> m_SpdifOutput; \
    InterfaceParam<Comp,int> m_Scart1Output; \
    InterfaceParam<Comp,int> m_Scart2Output; \
    InterfaceParam<Comp,int> m_AllOutput; \
    InterfaceParam<Comp,int> m_BoolTrue; \
    InterfaceParam<Comp,int> m_BoolFalse; \
    InterfaceParam<Comp,int> m_IgnoreValue; \
    InterfaceParam<Comp,int> m_VolumeMin; \
    InterfaceParam<Comp,int> m_VolumeMax; \
    InterfaceParam<Comp,int> m_VIVolumeMin; \
    InterfaceParam<Comp,int> m_VIVolumeMax; \
    InterfaceParam<Comp,int> m_SmOff; \
    InterfaceParam<Comp,int> m_SmDolbyPrologic; \
    InterfaceParam<Comp,int> m_SmFront3Stereo; \
    InterfaceParam<Comp,int> m_SmHall; \
    InterfaceParam<Comp,int> m_SmIncredible3Dsurround; \
    InterfaceParam<Comp,int> m_SmSpatial; \
    InterfaceParam<Comp,int> m_SmIncredibleSurround; \
    InterfaceParam<Comp,int> m_SmStereo4; \
    InterfaceParam<Comp,int> m_SmDigitalDolby; \
    InterfaceParam<Comp,int> m_SmMPEGMultiChannel; \
    InterfaceParam<Comp,int> m_SmIncredibleMono; \
    InterfaceParam<Comp,int> m_SmIncredibleStereo; \
    InterfaceParam<Comp,int> m_SmVDS422; \
    InterfaceParam<Comp,int> m_SmVDS423; \
    InterfaceParam<Comp,int> m_SmVDS521; \
    InterfaceParam<Comp,int> m_SmVDS522; \
    InterfaceParam<Comp,int> m_SmMatrix; \
    InterfaceParam<Comp,int> m_SmDolbyPrologicII; \
    InterfaceParam<Comp,int> m_SmDigital3D; \
    InterfaceParam<Comp,int> m_SmVirtualDolbyDigital; \
    InterfaceParam<Comp,int> m_SmDolbyPrologicPhantom; \
    InterfaceParam<Comp,int> m_SndNICAMRelatedStereo; \
    InterfaceParam<Comp,int> m_SndNICAMRelatedDual; \
    InterfaceParam<Comp,int> m_SndNICAMRelatedMono; \
    InterfaceParam<Comp,int> m_SndNICAMUnrelatedStereo; \
    InterfaceParam<Comp,int> m_SndNICAMUnrelatedDual; \
    InterfaceParam<Comp,int> m_SndNICAMUnrelatedMono; \
    InterfaceParam<Comp,int> m_SndNICAMData; \
    InterfaceParam<Comp,int> m_SndFMStereo; \
    InterfaceParam<Comp,int> m_SndFMDual; \
    InterfaceParam<Comp,int> m_SndFMAMMono; \
    InterfaceParam<Comp,int> m_SndEIAJMono; \
    InterfaceParam<Comp,int> m_SndEIAJStereo; \
    InterfaceParam<Comp,int> m_SndEIAJDual; \
    InterfaceParam<Comp,int> m_SndAMMono; \
    InterfaceParam<Comp,int> m_SndBTSCMono; \
    InterfaceParam<Comp,int> m_SndBTSCStereo; \
    InterfaceParam<Comp,int> m_SndBTSCMonoSap; \
    InterfaceParam<Comp,int> m_SndBTSCStereoSap; \
    InterfaceParam<Comp,int> m_SndBasebandMono; \
    InterfaceParam<Comp,int> m_SndBasebandStereo; \
    InterfaceParam<Comp,int> m_SndNoSoundSystem; \
    InterfaceParam<Comp,int> m_McChannelOnePlusOne; \
    InterfaceParam<Comp,int> m_McChannelTwoPlusTwo; \
    InterfaceParam<Comp,int> m_McChannelOneByZero; \
    InterfaceParam<Comp,int> m_McChannelTwoByZero; \
    InterfaceParam<Comp,int> m_McChannelTwoByOne; \
    InterfaceParam<Comp,int> m_McChannelTwoByTwo; \
    InterfaceParam<Comp,int> m_McChannelThreeByZero; \
    InterfaceParam<Comp,int> m_McChannelThreeByOne; \
    InterfaceParam<Comp,int> m_McChannelThreeByTwo; \
    InterfaceParam<Comp,int> m_McChannelTwoByOneKaraoke; \
    InterfaceParam<Comp,int> m_McChannelTwoByTwoKaraoke; \
    InterfaceParam<Comp,int> m_McChannelThreeByOneKaraoke; \
    InterfaceParam<Comp,int> m_McChannelThreeByTwoKaraoke; \
    InterfaceParam<Comp,int> m_McChannelThreeByZeroKaraoke; \
    InterfaceParam<Comp,int> m_McChannelPCMStereo; \
    InterfaceParam<Comp,int> m_McChannelNotSupported; \
    InterfaceParam<Comp,int> m_SfAnalog; \
    InterfaceParam<Comp,int> m_SfNICAM; \
    InterfaceParam<Comp,int> m_SfMPEG; \
    InterfaceParam<Comp,int> m_SfPCM; \
    InterfaceParam<Comp,int> m_SfDolbyDigital; \
    InterfaceParam<Comp,int> m_SfEIAJ; \
    InterfaceParam<Comp,int> m_Sf2CS; \
    InterfaceParam<Comp,int> m_SfDTS; \
    InterfaceParam<Comp,int> m_SfBaseBand; \
    InterfaceParam<Comp,int> m_SfAAC; \
    InterfaceParam<Comp,int> m_SfUnknown; \
    InterfaceParam<Comp,int> m_SfDolbyDigitalPlus; \
    InterfaceParam<Comp,int> m_SpdifUnsupported; \
    InterfaceParam<Comp,int> m_NormalAnalog; \
    InterfaceParam<Comp,int> m_AnalogMode; \
    InterfaceParam<Comp,int> m_DigitalMode; \
    Comp ## _ ## intf( Comp *parent):m_Volume(parent),m_SmartSound(parent),m_VIAudioVolume(parent),m_VIRouting(parent),m_VIRoutingEx(parent),m_VINone(parent),m_VIOn(parent),m_VISpeakerOutput(parent),m_VIHeadphoneOutput(parent),m_VIMonitorOutput(parent),m_VISpdifOutput(parent),m_SeamlessMixing(parent),m_SeamlessMixing_Off(parent),m_SeamlessMixing_On(parent),m_SpeechPreference(parent),m_SpeechPreference_Descriptive(parent),m_SpeechPreference_Subtitles(parent),m_OriginalLanguage(parent),m_OriginalLanguage_On(parent),m_OriginalLanguage_Off(parent),m_SoundFormat(parent),m_SpdifStatus(parent),m_SoundSystem(parent),m_Mute(parent),m_ProgramMute(parent),m_PreferedStereo(parent),m_Language(parent),m_LanguageChina(parent),m_None(parent),m_SpeakerOutput(parent),m_HeadphoneOutput(parent),m_MonitorOutput(parent),m_SpdifOutput(parent),m_Scart1Output(parent),m_Scart2Output(parent),m_AllOutput(parent),m_BoolTrue(parent),m_BoolFalse(parent),m_IgnoreValue(parent),m_VolumeMin(parent),m_VolumeMax(parent),m_VIVolumeMin(parent),m_VIVolumeMax(parent),m_SmOff(parent),m_SmDolbyPrologic(parent),m_SmFront3Stereo(parent),m_SmHall(parent),m_SmIncredible3Dsurround(parent),m_SmSpatial(parent),m_SmIncredibleSurround(parent),m_SmStereo4(parent),m_SmDigitalDolby(parent),m_SmMPEGMultiChannel(parent),m_SmIncredibleMono(parent),m_SmIncredibleStereo(parent),m_SmVDS422(parent),m_SmVDS423(parent),m_SmVDS521(parent),m_SmVDS522(parent),m_SmMatrix(parent),m_SmDolbyPrologicII(parent),m_SmDigital3D(parent),m_SmVirtualDolbyDigital(parent),m_SmDolbyPrologicPhantom(parent),m_SndNICAMRelatedStereo(parent),m_SndNICAMRelatedDual(parent),m_SndNICAMRelatedMono(parent),m_SndNICAMUnrelatedStereo(parent),m_SndNICAMUnrelatedDual(parent),m_SndNICAMUnrelatedMono(parent),m_SndNICAMData(parent),m_SndFMStereo(parent),m_SndFMDual(parent),m_SndFMAMMono(parent),m_SndEIAJMono(parent),m_SndEIAJStereo(parent),m_SndEIAJDual(parent),m_SndAMMono(parent),m_SndBTSCMono(parent),m_SndBTSCStereo(parent),m_SndBTSCMonoSap(parent),m_SndBTSCStereoSap(parent),m_SndBasebandMono(parent),m_SndBasebandStereo(parent),m_SndNoSoundSystem(parent),m_McChannelOnePlusOne(parent),m_McChannelTwoPlusTwo(parent),m_McChannelOneByZero(parent),m_McChannelTwoByZero(parent),m_McChannelTwoByOne(parent),m_McChannelTwoByTwo(parent),m_McChannelThreeByZero(parent),m_McChannelThreeByOne(parent),m_McChannelThreeByTwo(parent),m_McChannelTwoByOneKaraoke(parent),m_McChannelTwoByTwoKaraoke(parent),m_McChannelThreeByOneKaraoke(parent),m_McChannelThreeByTwoKaraoke(parent),m_McChannelThreeByZeroKaraoke(parent),m_McChannelPCMStereo(parent),m_McChannelNotSupported(parent),m_SfAnalog(parent),m_SfNICAM(parent),m_SfMPEG(parent),m_SfPCM(parent),m_SfDolbyDigital(parent),m_SfEIAJ(parent),m_Sf2CS(parent),m_SfDTS(parent),m_SfBaseBand(parent),m_SfAAC(parent),m_SfUnknown(parent),m_SfDolbyDigitalPlus(parent),m_SpdifUnsupported(parent),m_NormalAnalog(parent),m_AnalogMode(parent),m_DigitalMode(parent) \
    {\
        m_parent = parent;\
    }\
virtual int Get(int audioProperty){ return m_parent->intf ## _Get(audioProperty);}\
virtual void Set(int audioProperty,int value){ return m_parent->intf ## _Set(audioProperty,value);}\
virtual void Set2(int audioProperty,int value1,int value2){ return m_parent->intf ## _Set2(audioProperty,value1,value2);}\
virtual int Get2(int audioproperty,int value1){ return m_parent->intf ## _Get2(audioproperty,value1);}\
virtual Bool IsAvailable(int audioProperty,int value){ return m_parent->intf ## _IsAvailable(audioProperty,value);}\
virtual Bool IsControllable(int audioProperty,int value){ return m_parent->intf ## _IsControllable(audioProperty,value);}\
virtual Bool IsAvailable2(int audioProperty,int value1,int value2){ return m_parent->intf ## _IsAvailable2(audioProperty,value1,value2);}\
virtual Bool IsControllable2(int audioProperty,int value1,int value2){ return m_parent->intf ## _IsControllable2(audioProperty,value1,value2);}\
virtual int Volume(void){ return m_Volume.Call();}\
virtual int SmartSound(void){ return m_SmartSound.Call();}\
virtual int VIAudioVolume(void){ return m_VIAudioVolume.Call();}\
virtual int VIRouting(void){ return m_VIRouting.Call();}\
virtual int VIRoutingEx(void){ return m_VIRoutingEx.Call();}\
virtual int VINone(void){ return m_VINone.Call();}\
virtual int VIOn(void){ return m_VIOn.Call();}\
virtual int VISpeakerOutput(void){ return m_VISpeakerOutput.Call();}\
virtual int VIHeadphoneOutput(void){ return m_VIHeadphoneOutput.Call();}\
virtual int VIMonitorOutput(void){ return m_VIMonitorOutput.Call();}\
virtual int VISpdifOutput(void){ return m_VISpdifOutput.Call();}\
virtual Bool SeamlessMixing(void){ return m_SeamlessMixing.Call();}\
virtual int SeamlessMixing_Off(void){ return m_SeamlessMixing_Off.Call();}\
virtual int SeamlessMixing_On(void){ return m_SeamlessMixing_On.Call();}\
virtual int SpeechPreference(void){ return m_SpeechPreference.Call();}\
virtual int SpeechPreference_Descriptive(void){ return m_SpeechPreference_Descriptive.Call();}\
virtual int SpeechPreference_Subtitles(void){ return m_SpeechPreference_Subtitles.Call();}\
virtual int OriginalLanguage(void){ return m_OriginalLanguage.Call();}\
virtual int OriginalLanguage_On(void){ return m_OriginalLanguage_On.Call();}\
virtual int OriginalLanguage_Off(void){ return m_OriginalLanguage_Off.Call();}\
virtual int SoundFormat(void){ return m_SoundFormat.Call();}\
virtual int SpdifStatus(void){ return m_SpdifStatus.Call();}\
virtual int SoundSystem(void){ return m_SoundSystem.Call();}\
virtual int Mute(void){ return m_Mute.Call();}\
virtual int ProgramMute(void){ return m_ProgramMute.Call();}\
virtual int PreferedStereo(void){ return m_PreferedStereo.Call();}\
virtual int Language(void){ return m_Language.Call();}\
virtual int LanguageChina(void){ return m_LanguageChina.Call();}\
virtual int None(void){ return m_None.Call();}\
virtual int SpeakerOutput(void){ return m_SpeakerOutput.Call();}\
virtual int HeadphoneOutput(void){ return m_HeadphoneOutput.Call();}\
virtual int MonitorOutput(void){ return m_MonitorOutput.Call();}\
virtual int SpdifOutput(void){ return m_SpdifOutput.Call();}\
virtual int Scart1Output(void){ return m_Scart1Output.Call();}\
virtual int Scart2Output(void){ return m_Scart2Output.Call();}\
virtual int AllOutput(void){ return m_AllOutput.Call();}\
virtual int BoolTrue(void){ return m_BoolTrue.Call();}\
virtual int BoolFalse(void){ return m_BoolFalse.Call();}\
virtual int IgnoreValue(void){ return m_IgnoreValue.Call();}\
virtual int VolumeMin(void){ return m_VolumeMin.Call();}\
virtual int VolumeMax(void){ return m_VolumeMax.Call();}\
virtual int VIVolumeMin(void){ return m_VIVolumeMin.Call();}\
virtual int VIVolumeMax(void){ return m_VIVolumeMax.Call();}\
virtual int SmOff(void){ return m_SmOff.Call();}\
virtual int SmDolbyPrologic(void){ return m_SmDolbyPrologic.Call();}\
virtual int SmFront3Stereo(void){ return m_SmFront3Stereo.Call();}\
virtual int SmHall(void){ return m_SmHall.Call();}\
virtual int SmIncredible3Dsurround(void){ return m_SmIncredible3Dsurround.Call();}\
virtual int SmSpatial(void){ return m_SmSpatial.Call();}\
virtual int SmIncredibleSurround(void){ return m_SmIncredibleSurround.Call();}\
virtual int SmStereo4(void){ return m_SmStereo4.Call();}\
virtual int SmDigitalDolby(void){ return m_SmDigitalDolby.Call();}\
virtual int SmMPEGMultiChannel(void){ return m_SmMPEGMultiChannel.Call();}\
virtual int SmIncredibleMono(void){ return m_SmIncredibleMono.Call();}\
virtual int SmIncredibleStereo(void){ return m_SmIncredibleStereo.Call();}\
virtual int SmVDS422(void){ return m_SmVDS422.Call();}\
virtual int SmVDS423(void){ return m_SmVDS423.Call();}\
virtual int SmVDS521(void){ return m_SmVDS521.Call();}\
virtual int SmVDS522(void){ return m_SmVDS522.Call();}\
virtual int SmMatrix(void){ return m_SmMatrix.Call();}\
virtual int SmDolbyPrologicII(void){ return m_SmDolbyPrologicII.Call();}\
virtual int SmDigital3D(void){ return m_SmDigital3D.Call();}\
virtual int SmVirtualDolbyDigital(void){ return m_SmVirtualDolbyDigital.Call();}\
virtual int SmDolbyPrologicPhantom(void){ return m_SmDolbyPrologicPhantom.Call();}\
virtual int SndNICAMRelatedStereo(void){ return m_SndNICAMRelatedStereo.Call();}\
virtual int SndNICAMRelatedDual(void){ return m_SndNICAMRelatedDual.Call();}\
virtual int SndNICAMRelatedMono(void){ return m_SndNICAMRelatedMono.Call();}\
virtual int SndNICAMUnrelatedStereo(void){ return m_SndNICAMUnrelatedStereo.Call();}\
virtual int SndNICAMUnrelatedDual(void){ return m_SndNICAMUnrelatedDual.Call();}\
virtual int SndNICAMUnrelatedMono(void){ return m_SndNICAMUnrelatedMono.Call();}\
virtual int SndNICAMData(void){ return m_SndNICAMData.Call();}\
virtual int SndFMStereo(void){ return m_SndFMStereo.Call();}\
virtual int SndFMDual(void){ return m_SndFMDual.Call();}\
virtual int SndFMAMMono(void){ return m_SndFMAMMono.Call();}\
virtual int SndEIAJMono(void){ return m_SndEIAJMono.Call();}\
virtual int SndEIAJStereo(void){ return m_SndEIAJStereo.Call();}\
virtual int SndEIAJDual(void){ return m_SndEIAJDual.Call();}\
virtual int SndAMMono(void){ return m_SndAMMono.Call();}\
virtual int SndBTSCMono(void){ return m_SndBTSCMono.Call();}\
virtual int SndBTSCStereo(void){ return m_SndBTSCStereo.Call();}\
virtual int SndBTSCMonoSap(void){ return m_SndBTSCMonoSap.Call();}\
virtual int SndBTSCStereoSap(void){ return m_SndBTSCStereoSap.Call();}\
virtual int SndBasebandMono(void){ return m_SndBasebandMono.Call();}\
virtual int SndBasebandStereo(void){ return m_SndBasebandStereo.Call();}\
virtual int SndNoSoundSystem(void){ return m_SndNoSoundSystem.Call();}\
virtual int McChannelOnePlusOne(void){ return m_McChannelOnePlusOne.Call();}\
virtual int McChannelTwoPlusTwo(void){ return m_McChannelTwoPlusTwo.Call();}\
virtual int McChannelOneByZero(void){ return m_McChannelOneByZero.Call();}\
virtual int McChannelTwoByZero(void){ return m_McChannelTwoByZero.Call();}\
virtual int McChannelTwoByOne(void){ return m_McChannelTwoByOne.Call();}\
virtual int McChannelTwoByTwo(void){ return m_McChannelTwoByTwo.Call();}\
virtual int McChannelThreeByZero(void){ return m_McChannelThreeByZero.Call();}\
virtual int McChannelThreeByOne(void){ return m_McChannelThreeByOne.Call();}\
virtual int McChannelThreeByTwo(void){ return m_McChannelThreeByTwo.Call();}\
virtual int McChannelTwoByOneKaraoke(void){ return m_McChannelTwoByOneKaraoke.Call();}\
virtual int McChannelTwoByTwoKaraoke(void){ return m_McChannelTwoByTwoKaraoke.Call();}\
virtual int McChannelThreeByOneKaraoke(void){ return m_McChannelThreeByOneKaraoke.Call();}\
virtual int McChannelThreeByTwoKaraoke(void){ return m_McChannelThreeByTwoKaraoke.Call();}\
virtual int McChannelThreeByZeroKaraoke(void){ return m_McChannelThreeByZeroKaraoke.Call();}\
virtual int McChannelPCMStereo(void){ return m_McChannelPCMStereo.Call();}\
virtual int McChannelNotSupported(void){ return m_McChannelNotSupported.Call();}\
virtual int SfAnalog(void){ return m_SfAnalog.Call();}\
virtual int SfNICAM(void){ return m_SfNICAM.Call();}\
virtual int SfMPEG(void){ return m_SfMPEG.Call();}\
virtual int SfPCM(void){ return m_SfPCM.Call();}\
virtual int SfDolbyDigital(void){ return m_SfDolbyDigital.Call();}\
virtual int SfEIAJ(void){ return m_SfEIAJ.Call();}\
virtual int Sf2CS(void){ return m_Sf2CS.Call();}\
virtual int SfDTS(void){ return m_SfDTS.Call();}\
virtual int SfBaseBand(void){ return m_SfBaseBand.Call();}\
virtual int SfAAC(void){ return m_SfAAC.Call();}\
virtual int SfUnknown(void){ return m_SfUnknown.Call();}\
virtual int SfDolbyDigitalPlus(void){ return m_SfDolbyDigitalPlus.Call();}\
virtual int SpdifUnsupported(void){ return m_SpdifUnsupported.Call();}\
virtual int NormalAnalog(void){ return m_NormalAnalog.Call();}\
virtual int AnalogMode(void){ return m_AnalogMode.Call();}\
virtual int DigitalMode(void){ return m_DigitalMode.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
