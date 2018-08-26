#ifndef IAPPAPISATELEMENTARYSTREAMCONTROL_H
#define IAPPAPISATELEMENTARYSTREAMCONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatElementaryStreamControl
{
public:
	virtual ~IAppApiSatElementaryStreamControl(){}
	#define IAppApiSatElementaryStreamControl_DefaultPID		((int)0x1fff )
	virtual AppApiReturnCode PlayAudioPid(int PIDValue)= 0;
	virtual AppApiReturnCode StopAudioPid(void)= 0;
	virtual AppApiReturnCode PlayVideoPid(int PIDValue)= 0;
	virtual AppApiReturnCode StopVideoPid(void)= 0;
	virtual AppApiReturnCode PlayPCRPid(int PIDValue)= 0;
	virtual AppApiReturnCode StopPCRPid(void)= 0;
	virtual AppApiReturnCode PlaySubtitlePid(int PIDValue)= 0;
	virtual AppApiReturnCode StopSubtitlePid(void)= 0;
	virtual AppApiReturnCode PlayTeletextPid(int PIDValue)= 0;
	virtual AppApiReturnCode StopTeletextPid(void)= 0;
	virtual AppApiReturnCode PlayCCPid(int PIDValue)= 0;
	virtual AppApiReturnCode StopCCPid(void)= 0;
	virtual int GetAudioPid(void)= 0;
	virtual int GetVideoPid(void)= 0;
	virtual int GetPCRPid(void)= 0;
	virtual int GetTeletextPid(void)= 0;
	virtual int GetSubtitlePid(void)= 0;
	virtual int GetCCPid(void)= 0;
};


#define IAppApiSatElementaryStreamControlImpl(Comp,intf)    \
virtual AppApiReturnCode intf ## _PlayAudioPid(int PIDValue);\
virtual AppApiReturnCode intf ## _StopAudioPid(void);\
virtual AppApiReturnCode intf ## _PlayVideoPid(int PIDValue);\
virtual AppApiReturnCode intf ## _StopVideoPid(void);\
virtual AppApiReturnCode intf ## _PlayPCRPid(int PIDValue);\
virtual AppApiReturnCode intf ## _StopPCRPid(void);\
virtual AppApiReturnCode intf ## _PlaySubtitlePid(int PIDValue);\
virtual AppApiReturnCode intf ## _StopSubtitlePid(void);\
virtual AppApiReturnCode intf ## _PlayTeletextPid(int PIDValue);\
virtual AppApiReturnCode intf ## _StopTeletextPid(void);\
virtual AppApiReturnCode intf ## _PlayCCPid(int PIDValue);\
virtual AppApiReturnCode intf ## _StopCCPid(void);\
virtual int intf ## _GetAudioPid(void);\
virtual int intf ## _GetVideoPid(void);\
virtual int intf ## _GetPCRPid(void);\
virtual int intf ## _GetTeletextPid(void);\
virtual int intf ## _GetSubtitlePid(void);\
virtual int intf ## _GetCCPid(void);\
class Comp ## _ ## intf : public IAppApiSatElementaryStreamControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual AppApiReturnCode PlayAudioPid(int PIDValue){ return m_parent->intf ## _PlayAudioPid(PIDValue);}\
virtual AppApiReturnCode StopAudioPid(void){ return m_parent->intf ## _StopAudioPid();}\
virtual AppApiReturnCode PlayVideoPid(int PIDValue){ return m_parent->intf ## _PlayVideoPid(PIDValue);}\
virtual AppApiReturnCode StopVideoPid(void){ return m_parent->intf ## _StopVideoPid();}\
virtual AppApiReturnCode PlayPCRPid(int PIDValue){ return m_parent->intf ## _PlayPCRPid(PIDValue);}\
virtual AppApiReturnCode StopPCRPid(void){ return m_parent->intf ## _StopPCRPid();}\
virtual AppApiReturnCode PlaySubtitlePid(int PIDValue){ return m_parent->intf ## _PlaySubtitlePid(PIDValue);}\
virtual AppApiReturnCode StopSubtitlePid(void){ return m_parent->intf ## _StopSubtitlePid();}\
virtual AppApiReturnCode PlayTeletextPid(int PIDValue){ return m_parent->intf ## _PlayTeletextPid(PIDValue);}\
virtual AppApiReturnCode StopTeletextPid(void){ return m_parent->intf ## _StopTeletextPid();}\
virtual AppApiReturnCode PlayCCPid(int PIDValue){ return m_parent->intf ## _PlayCCPid(PIDValue);}\
virtual AppApiReturnCode StopCCPid(void){ return m_parent->intf ## _StopCCPid();}\
virtual int GetAudioPid(void){ return m_parent->intf ## _GetAudioPid();}\
virtual int GetVideoPid(void){ return m_parent->intf ## _GetVideoPid();}\
virtual int GetPCRPid(void){ return m_parent->intf ## _GetPCRPid();}\
virtual int GetTeletextPid(void){ return m_parent->intf ## _GetTeletextPid();}\
virtual int GetSubtitlePid(void){ return m_parent->intf ## _GetSubtitlePid();}\
virtual int GetCCPid(void){ return m_parent->intf ## _GetCCPid();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
