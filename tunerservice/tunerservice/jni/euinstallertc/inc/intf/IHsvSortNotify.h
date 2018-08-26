#ifndef IHSVSORTNOTIFY_H
#define IHSVSORTNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSortNotify
{
public:
	virtual ~IHsvSortNotify(){}
	#define IHsvSortNotify_EventNewPresetFound		((int)26 )
	#define IHsvSortNotify_EventChannelRemoved		((int)27 )
	#define IHsvSortNotify_EventSortComplete		((int)28 )
	virtual void OnEvent(int eventid,int value)= 0;
};


#define IHsvSortNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int eventid,int value);\
class Comp ## _ ## intf : public IHsvSortNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int eventid,int value){ return m_parent->intf ## _OnEvent(eventid,value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
