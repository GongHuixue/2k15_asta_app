#ifndef IHSVINSTALLATIONFREQUENCYCONTROL_H
#define IHSVINSTALLATIONFREQUENCYCONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationFrequencyControl
{
public:
	virtual ~IHsvInstallationFrequencyControl(){}
	virtual int GetMinFrequency(void)= 0;
	virtual int GetMaxFrequency(void)= 0;
	virtual int GetTunerFrequency(void)= 0;
	virtual void SetTunerFrequency(int freq,Bool fineTune)= 0;
	virtual int GetFrequency2Channel(int chantbl,int frequency)= 0;
	virtual int GetChannel2CarrierFrequency(int chantbl,int channel)= 0;
	virtual int GetChannel2CentreFrequency(int chantbl,int channel)= 0;
};


#define IHsvInstallationFrequencyControlImpl(Comp,intf)    \
virtual int intf ## _GetMinFrequency(void);\
virtual int intf ## _GetMaxFrequency(void);\
virtual int intf ## _GetTunerFrequency(void);\
virtual void intf ## _SetTunerFrequency(int freq,Bool fineTune);\
virtual int intf ## _GetFrequency2Channel(int chantbl,int frequency);\
virtual int intf ## _GetChannel2CarrierFrequency(int chantbl,int channel);\
virtual int intf ## _GetChannel2CentreFrequency(int chantbl,int channel);\
class Comp ## _ ## intf : public IHsvInstallationFrequencyControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetMinFrequency(void){ return m_parent->intf ## _GetMinFrequency();}\
virtual int GetMaxFrequency(void){ return m_parent->intf ## _GetMaxFrequency();}\
virtual int GetTunerFrequency(void){ return m_parent->intf ## _GetTunerFrequency();}\
virtual void SetTunerFrequency(int freq,Bool fineTune){ return m_parent->intf ## _SetTunerFrequency(freq,fineTune);}\
virtual int GetFrequency2Channel(int chantbl,int frequency){ return m_parent->intf ## _GetFrequency2Channel(chantbl,frequency);}\
virtual int GetChannel2CarrierFrequency(int chantbl,int channel){ return m_parent->intf ## _GetChannel2CarrierFrequency(chantbl,channel);}\
virtual int GetChannel2CentreFrequency(int chantbl,int channel){ return m_parent->intf ## _GetChannel2CentreFrequency(chantbl,channel);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
