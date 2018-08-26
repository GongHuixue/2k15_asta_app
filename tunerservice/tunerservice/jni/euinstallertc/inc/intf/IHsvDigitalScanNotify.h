#ifndef IHSVDIGITALSCANNOTIFY_H
#define IHSVDIGITALSCANNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalScanNotify
{
public:
	virtual ~IHsvDigitalScanNotify(){}
	#define IHsvDigitalScanNotify_EventScanStopped		((int)0 )
	#define IHsvDigitalScanNotify_EventScanCompleted		((int)1 )
	#define IHsvDigitalScanNotify_EventScanFailed		((int)2 )
	#define IHsvDigitalScanNotify_EventTargetNITFound		((int)3 )
	virtual void OnEvent(int event)= 0;
};


#define IHsvDigitalScanNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int event);\
class Comp ## _ ## intf : public IHsvDigitalScanNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int event){ return m_parent->intf ## _OnEvent(event);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
