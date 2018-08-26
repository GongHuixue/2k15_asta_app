#ifndef IAPPAPISATELEMENTARYSTREAMCONTROLNOTIFYEX_H
#define IAPPAPISATELEMENTARYSTREAMCONTROLNOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatElementaryStreamControlNotifyEx
{
public:
	virtual ~IAppApiSatElementaryStreamControlNotifyEx(){}
	virtual void OnAudioPidChanged(int Pid)= 0;
	virtual void OnAudioPidStopped(void)= 0;
	virtual void OnVideoPidChanged(int Pid)= 0;
	virtual void OnVideoPidStopped(void)= 0;
	virtual void OnPCRPidChanged(int Pid)= 0;
	virtual void OnPCRPidStopped(void)= 0;
	virtual void OnSubtitlePidChanged(int Pid)= 0;
	virtual void OnIPSubtitlePidChanged(int Pid)= 0;
	virtual void OnSubtitlePidStopped(void)= 0;
	virtual void OnIPSubtitlePidStopped(void)= 0;
	virtual void OnTeletextPidChanged(int Pid)= 0;
	virtual void OnTeletextPidStopped(void)= 0;
	virtual void OnCCPidChanged(int Pid)= 0;
	virtual void OnIPCCPidChanged(int Pid)= 0;
	virtual void OnCCPidStopped(void)= 0;
	virtual void OnIPCCPidStopped(void)= 0;
};


#define IAppApiSatElementaryStreamControlNotifyExImpl(Comp,intf)    \
virtual void intf ## _OnAudioPidChanged(int Pid);\
virtual void intf ## _OnAudioPidStopped(void);\
virtual void intf ## _OnVideoPidChanged(int Pid);\
virtual void intf ## _OnVideoPidStopped(void);\
virtual void intf ## _OnPCRPidChanged(int Pid);\
virtual void intf ## _OnPCRPidStopped(void);\
virtual void intf ## _OnSubtitlePidChanged(int Pid);\
virtual void intf ## _OnIPSubtitlePidChanged(int Pid);\
virtual void intf ## _OnSubtitlePidStopped(void);\
virtual void intf ## _OnIPSubtitlePidStopped(void);\
virtual void intf ## _OnTeletextPidChanged(int Pid);\
virtual void intf ## _OnTeletextPidStopped(void);\
virtual void intf ## _OnCCPidChanged(int Pid);\
virtual void intf ## _OnIPCCPidChanged(int Pid);\
virtual void intf ## _OnCCPidStopped(void);\
virtual void intf ## _OnIPCCPidStopped(void);\
class Comp ## _ ## intf : public IAppApiSatElementaryStreamControlNotifyEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnAudioPidChanged(int Pid){ return m_parent->intf ## _OnAudioPidChanged(Pid);}\
virtual void OnAudioPidStopped(void){ return m_parent->intf ## _OnAudioPidStopped();}\
virtual void OnVideoPidChanged(int Pid){ return m_parent->intf ## _OnVideoPidChanged(Pid);}\
virtual void OnVideoPidStopped(void){ return m_parent->intf ## _OnVideoPidStopped();}\
virtual void OnPCRPidChanged(int Pid){ return m_parent->intf ## _OnPCRPidChanged(Pid);}\
virtual void OnPCRPidStopped(void){ return m_parent->intf ## _OnPCRPidStopped();}\
virtual void OnSubtitlePidChanged(int Pid){ return m_parent->intf ## _OnSubtitlePidChanged(Pid);}\
virtual void OnIPSubtitlePidChanged(int Pid){ return m_parent->intf ## _OnIPSubtitlePidChanged(Pid);}\
virtual void OnSubtitlePidStopped(void){ return m_parent->intf ## _OnSubtitlePidStopped();}\
virtual void OnIPSubtitlePidStopped(void){ return m_parent->intf ## _OnIPSubtitlePidStopped();}\
virtual void OnTeletextPidChanged(int Pid){ return m_parent->intf ## _OnTeletextPidChanged(Pid);}\
virtual void OnTeletextPidStopped(void){ return m_parent->intf ## _OnTeletextPidStopped();}\
virtual void OnCCPidChanged(int Pid){ return m_parent->intf ## _OnCCPidChanged(Pid);}\
virtual void OnIPCCPidChanged(int Pid){ return m_parent->intf ## _OnIPCCPidChanged(Pid);}\
virtual void OnCCPidStopped(void){ return m_parent->intf ## _OnCCPidStopped();}\
virtual void OnIPCCPidStopped(void){ return m_parent->intf ## _OnIPCCPidStopped();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
