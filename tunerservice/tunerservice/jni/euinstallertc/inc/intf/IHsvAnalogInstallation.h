#ifndef IHSVANALOGINSTALLATION_H
#define IHSVANALOGINSTALLATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAnalogInstallation
{
public:
	virtual ~IHsvAnalogInstallation(){}
	#define IHsvAnalogInstallation_InvalidCni		((Nat16)0 )
	virtual int InvalidChannel(void)= 0;
	virtual int InvalidFrequency(void)= 0;
	#define IHsvAnalogInstallation_InstallationStateIdle		((int)0 )
	#define IHsvAnalogInstallation_InstallationStateInProgress		((int)1 )
	#define IHsvAnalogInstallation_InstallationModeNone		((int)0 )
	#define IHsvAnalogInstallation_InstallationModeManual		((int)1 )
	#define IHsvAnalogInstallation_InstallationModeAutomatic		((int)2 )
	#define IHsvAnalogInstallation_InstallationModeBackground		((int)3 )
	#define IHsvAnalogInstallation_InstallationModeImplicit		((int)4 )
	#define IHsvAnalogInstallation_SChannel		((int)0 )
	#define IHsvAnalogInstallation_CChannel		((int)1 )
	#define IHsvAnalogInstallation_ManualInstallationModeFrequency		((int)0 )
	#define IHsvAnalogInstallation_ManualInstallationModeSChannel		((int)1 )
	#define IHsvAnalogInstallation_ManualInstallationModeCChannel		((int)2 )
	#define IHsvAnalogInstallation_InsTvSystemBg		((int)0 )
	#define IHsvAnalogInstallation_InsTvSystemDk		((int)1 )
	#define IHsvAnalogInstallation_InsTvSystemI		((int)2 )
	#define IHsvAnalogInstallation_InsTvSystemL		((int)3 )
	#define IHsvAnalogInstallation_InsTvSystemM		((int)5 )
	#define IHsvAnalogInstallation_InsTvSystemAuto		((int)6 )
	#define IHsvAnalogInstallation_InsColourSystemPal		((int)0 )
	#define IHsvAnalogInstallation_InsColourSystemSecam		((int)1 )
	#define IHsvAnalogInstallation_InsColourSystemNtsc358		((int)2 )
	#define IHsvAnalogInstallation_InsColourSystemNtsc443		((int)3 )
	#define IHsvAnalogInstallation_InsColourSystemAuto		((int)4 )
	#define IHsvAnalogInstallation_InsColourSystemInvalid		((int)5 )
	virtual void Initialise(void)= 0;
	virtual void StartAutomaticInstallation(void)= 0;
	virtual void StopAutomaticInstallation(void)= 0;
	virtual void SkipInstallation(void)= 0;
	virtual Bool IsManualInstallationModeSupported(int mode)= 0;
	virtual void SetManualInstallationMode(int mode)= 0;
	virtual int GetManualInstallationMode(void)= 0;
	virtual void SetManualFrequency(int frequency,int offset,Bool finetune)= 0;
	virtual void GetManualFrequency(int * frequency,int * offset,Bool * finetune)= 0;
	virtual void SetManualChannel(int channel,Bool finetune)= 0;
	virtual void GetManualChannel(int * channel,Bool * finetune)= 0;
	virtual void StartManualInstallation(void)= 0;
	virtual void StopManualInstallation(void)= 0;
	virtual void StoreManualInstallationValues(HsvChannel channel)= 0;
	virtual Bool StartFrequencySearch(void)= 0;
	virtual HsvChannel GetPresetSearchingFor(void)= 0;
	virtual HsvChannel GetLastFoundPreset(void)= 0;
	virtual char* GetLastFoundPresetName(void)= 0;
	virtual int GetLastFoundPresetFrequency(void)= 0;
	virtual int GetNumberOfAnalogPresetsFound(void)= 0;
	virtual int GetNumberOfAnalogPresetsAdded(void)= 0;
	virtual void InitialiseTotalChannels(void)= 0;
	virtual Bool StartBackgroundCniUpdation(HsvChannel channel)= 0;
	virtual Bool IsTvSystemSupported(int instvsystem)= 0;
	virtual void SetTvSystem(int instvsystem)= 0;
	virtual int GetTvSystem(void)= 0;
	virtual Bool IsColorSystemSupported(int colorsystem)= 0;
	virtual void SetColorSystem(int colorsystem)= 0;
	virtual int GetColorSystem(void)= 0;
	virtual void SetTunerFrequency(int freq,Bool fineTune)= 0;
	virtual void SetHandleTunerFreqNotify(Bool val)= 0;
	virtual int GetInstallationPass(void)= 0;
	virtual int GetInstallationState(void)= 0;
	virtual int GetNoOfPass(void)= 0;
};


#define IHsvAnalogInstallationImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual void intf ## _Initialise(void);\
virtual void intf ## _StartAutomaticInstallation(void);\
virtual void intf ## _StopAutomaticInstallation(void);\
virtual void intf ## _SkipInstallation(void);\
virtual Bool intf ## _IsManualInstallationModeSupported(int mode);\
virtual void intf ## _SetManualInstallationMode(int mode);\
virtual int intf ## _GetManualInstallationMode(void);\
virtual void intf ## _SetManualFrequency(int frequency,int offset,Bool finetune);\
virtual void intf ## _GetManualFrequency(int * frequency,int * offset,Bool * finetune);\
virtual void intf ## _SetManualChannel(int channel,Bool finetune);\
virtual void intf ## _GetManualChannel(int * channel,Bool * finetune);\
virtual void intf ## _StartManualInstallation(void);\
virtual void intf ## _StopManualInstallation(void);\
virtual void intf ## _StoreManualInstallationValues(HsvChannel channel);\
virtual Bool intf ## _StartFrequencySearch(void);\
virtual HsvChannel intf ## _GetPresetSearchingFor(void);\
virtual HsvChannel intf ## _GetLastFoundPreset(void);\
virtual char* intf ## _GetLastFoundPresetName(void);\
virtual int intf ## _GetLastFoundPresetFrequency(void);\
virtual int intf ## _GetNumberOfAnalogPresetsFound(void);\
virtual int intf ## _GetNumberOfAnalogPresetsAdded(void);\
virtual void intf ## _InitialiseTotalChannels(void);\
virtual Bool intf ## _StartBackgroundCniUpdation(HsvChannel channel);\
virtual Bool intf ## _IsTvSystemSupported(int instvsystem);\
virtual void intf ## _SetTvSystem(int instvsystem);\
virtual int intf ## _GetTvSystem(void);\
virtual Bool intf ## _IsColorSystemSupported(int colorsystem);\
virtual void intf ## _SetColorSystem(int colorsystem);\
virtual int intf ## _GetColorSystem(void);\
virtual void intf ## _SetTunerFrequency(int freq,Bool fineTune);\
virtual void intf ## _SetHandleTunerFreqNotify(Bool val);\
virtual int intf ## _GetInstallationPass(void);\
virtual int intf ## _GetInstallationState(void);\
virtual int intf ## _GetNoOfPass(void);\
class Comp ## _ ## intf : public IHsvAnalogInstallation \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_InvalidChannel; \
    InterfaceParam<Comp,int> m_InvalidFrequency; \
    Comp ## _ ## intf( Comp *parent):m_InvalidChannel(parent),m_InvalidFrequency(parent) \
    {\
        m_parent = parent;\
    }\
virtual int InvalidChannel(void){ return m_InvalidChannel.Call();}\
virtual int InvalidFrequency(void){ return m_InvalidFrequency.Call();}\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual void StartAutomaticInstallation(void){ return m_parent->intf ## _StartAutomaticInstallation();}\
virtual void StopAutomaticInstallation(void){ return m_parent->intf ## _StopAutomaticInstallation();}\
virtual void SkipInstallation(void){ return m_parent->intf ## _SkipInstallation();}\
virtual Bool IsManualInstallationModeSupported(int mode){ return m_parent->intf ## _IsManualInstallationModeSupported(mode);}\
virtual void SetManualInstallationMode(int mode){ return m_parent->intf ## _SetManualInstallationMode(mode);}\
virtual int GetManualInstallationMode(void){ return m_parent->intf ## _GetManualInstallationMode();}\
virtual void SetManualFrequency(int frequency,int offset,Bool finetune){ return m_parent->intf ## _SetManualFrequency(frequency,offset,finetune);}\
virtual void GetManualFrequency(int * frequency,int * offset,Bool * finetune){ return m_parent->intf ## _GetManualFrequency(frequency,offset,finetune);}\
virtual void SetManualChannel(int channel,Bool finetune){ return m_parent->intf ## _SetManualChannel(channel,finetune);}\
virtual void GetManualChannel(int * channel,Bool * finetune){ return m_parent->intf ## _GetManualChannel(channel,finetune);}\
virtual void StartManualInstallation(void){ return m_parent->intf ## _StartManualInstallation();}\
virtual void StopManualInstallation(void){ return m_parent->intf ## _StopManualInstallation();}\
virtual void StoreManualInstallationValues(HsvChannel channel){ return m_parent->intf ## _StoreManualInstallationValues(channel);}\
virtual Bool StartFrequencySearch(void){ return m_parent->intf ## _StartFrequencySearch();}\
virtual HsvChannel GetPresetSearchingFor(void){ return m_parent->intf ## _GetPresetSearchingFor();}\
virtual HsvChannel GetLastFoundPreset(void){ return m_parent->intf ## _GetLastFoundPreset();}\
virtual char* GetLastFoundPresetName(void){ return m_parent->intf ## _GetLastFoundPresetName();}\
virtual int GetLastFoundPresetFrequency(void){ return m_parent->intf ## _GetLastFoundPresetFrequency();}\
virtual int GetNumberOfAnalogPresetsFound(void){ return m_parent->intf ## _GetNumberOfAnalogPresetsFound();}\
virtual int GetNumberOfAnalogPresetsAdded(void){ return m_parent->intf ## _GetNumberOfAnalogPresetsAdded();}\
virtual void InitialiseTotalChannels(void){ return m_parent->intf ## _InitialiseTotalChannels();}\
virtual Bool StartBackgroundCniUpdation(HsvChannel channel){ return m_parent->intf ## _StartBackgroundCniUpdation(channel);}\
virtual Bool IsTvSystemSupported(int instvsystem){ return m_parent->intf ## _IsTvSystemSupported(instvsystem);}\
virtual void SetTvSystem(int instvsystem){ return m_parent->intf ## _SetTvSystem(instvsystem);}\
virtual int GetTvSystem(void){ return m_parent->intf ## _GetTvSystem();}\
virtual Bool IsColorSystemSupported(int colorsystem){ return m_parent->intf ## _IsColorSystemSupported(colorsystem);}\
virtual void SetColorSystem(int colorsystem){ return m_parent->intf ## _SetColorSystem(colorsystem);}\
virtual int GetColorSystem(void){ return m_parent->intf ## _GetColorSystem();}\
virtual void SetTunerFrequency(int freq,Bool fineTune){ return m_parent->intf ## _SetTunerFrequency(freq,fineTune);}\
virtual void SetHandleTunerFreqNotify(Bool val){ return m_parent->intf ## _SetHandleTunerFreqNotify(val);}\
virtual int GetInstallationPass(void){ return m_parent->intf ## _GetInstallationPass();}\
virtual int GetInstallationState(void){ return m_parent->intf ## _GetInstallationState();}\
virtual int GetNoOfPass(void){ return m_parent->intf ## _GetNoOfPass();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
