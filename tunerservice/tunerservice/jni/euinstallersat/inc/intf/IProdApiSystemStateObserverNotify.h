#ifndef IPRODAPISYSTEMSTATEOBSERVERNOTIFY_H
#define IPRODAPISYSTEMSTATEOBSERVERNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiSystemStateObserverNotify
{
public:
	virtual ~IProdApiSystemStateObserverNotify(){}
	#define IProdApiSystemStateObserverNotify_RecordingStateChanged		((int)0 )
	#define IProdApiSystemStateObserverNotify_MultiviewStateChanged		((int)1 )
	#define IProdApiSystemStateObserverNotify_DisabledEventsStateChanged		((int)2 )
	#define IProdApiSystemStateObserverNotify_TimeshiftStateChanged		((int)3 )
	#define IProdApiSystemStateObserverNotify_SkypeStateChanged		((int)4 )
	#define IProdApiSystemStateObserverNotify_TopmenubarStateChanged		((int)5 )
	virtual void OnSystemStateChanged(int State)= 0;
};


#define IProdApiSystemStateObserverNotifyImpl(Comp,intf)    \
virtual void intf ## _OnSystemStateChanged(int State);\
class Comp ## _ ## intf : public IProdApiSystemStateObserverNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnSystemStateChanged(int State){ return m_parent->intf ## _OnSystemStateChanged(State);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
