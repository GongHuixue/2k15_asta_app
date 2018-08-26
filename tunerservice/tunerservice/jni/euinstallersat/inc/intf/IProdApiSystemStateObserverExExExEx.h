#ifndef IPRODAPISYSTEMSTATEOBSERVEREXEXEXEX_H
#define IPRODAPISYSTEMSTATEOBSERVEREXEXEXEX_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiSystemStateObserverExExExEx
{
public:
	virtual ~IProdApiSystemStateObserverExExExEx(){}
	virtual Bool IsRecordingOngoing(void)= 0;
	virtual void GetMultiviewState(Bool * ena)= 0;
	virtual int GetSystemDisabledEvents(void)= 0;
	virtual Bool IsTimeShiftActive(void)= 0;
	virtual Bool IsSkypeActive(void)= 0;
	virtual Bool IsTopmenubarActive(void)= 0;
	virtual Bool IsDmsPlaybackOngoing(void)= 0;
};


#define IProdApiSystemStateObserverExExExExImpl(Comp,intf)    \
virtual Bool intf ## _IsRecordingOngoing(void);\
virtual void intf ## _GetMultiviewState(Bool * ena);\
virtual int intf ## _GetSystemDisabledEvents(void);\
virtual Bool intf ## _IsTimeShiftActive(void);\
virtual Bool intf ## _IsSkypeActive(void);\
virtual Bool intf ## _IsTopmenubarActive(void);\
virtual Bool intf ## _IsDmsPlaybackOngoing(void);\
class Comp ## _ ## intf : public IProdApiSystemStateObserverExExExEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool IsRecordingOngoing(void){ return m_parent->intf ## _IsRecordingOngoing();}\
virtual void GetMultiviewState(Bool * ena){ return m_parent->intf ## _GetMultiviewState(ena);}\
virtual int GetSystemDisabledEvents(void){ return m_parent->intf ## _GetSystemDisabledEvents();}\
virtual Bool IsTimeShiftActive(void){ return m_parent->intf ## _IsTimeShiftActive();}\
virtual Bool IsSkypeActive(void){ return m_parent->intf ## _IsSkypeActive();}\
virtual Bool IsTopmenubarActive(void){ return m_parent->intf ## _IsTopmenubarActive();}\
virtual Bool IsDmsPlaybackOngoing(void){ return m_parent->intf ## _IsDmsPlaybackOngoing();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
