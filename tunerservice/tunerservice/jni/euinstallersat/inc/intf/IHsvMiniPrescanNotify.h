#ifndef IHSVMINIPRESCANNOTIFY_H
#define IHSVMINIPRESCANNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMiniPrescanNotify
{
public:
	virtual ~IHsvMiniPrescanNotify(){}
	#define IHsvMiniPrescanNotify_EventPrescanFailed		((int)1 )
	#define IHsvMiniPrescanNotify_EventSameSatelliteDetected		((int)2 )
	#define IHsvMiniPrescanNotify_EventDifferentSatelliteDetected		((int)3 )
	#define IHsvMiniPrescanNotify_EventPreScanStopped		((int)4 )
	virtual void OnEvent(int EventId,int Param)= 0;
};


#define IHsvMiniPrescanNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int EventId,int Param);\
class Comp ## _ ## intf : public IHsvMiniPrescanNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int EventId,int Param){ return m_parent->intf ## _OnEvent(EventId,Param);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
