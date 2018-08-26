#ifndef IHSVSTREAMNOTIFY_H
#define IHSVSTREAMNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvStreamNotify
{
public:
	virtual ~IHsvStreamNotify(){}
	virtual void OnCompleted(HsvDestination dest,int spid)= 0;
	virtual void OnAdded(HsvDestination dest,int spid,int key1,int key2,int key3)= 0;
	virtual void OnChanged(HsvDestination dest,int spid,int key1,int key2,int key3,int eventid)= 0;
	virtual void OnRemoved(HsvDestination dest,int spid,int key1,int key2,int key3)= 0;
};


#define IHsvStreamNotifyImpl(Comp,intf)    \
virtual void intf ## _OnCompleted(HsvDestination dest,int spid);\
virtual void intf ## _OnAdded(HsvDestination dest,int spid,int key1,int key2,int key3);\
virtual void intf ## _OnChanged(HsvDestination dest,int spid,int key1,int key2,int key3,int eventid);\
virtual void intf ## _OnRemoved(HsvDestination dest,int spid,int key1,int key2,int key3);\
class Comp ## _ ## intf : public IHsvStreamNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnCompleted(HsvDestination dest,int spid){ return m_parent->intf ## _OnCompleted(dest,spid);}\
virtual void OnAdded(HsvDestination dest,int spid,int key1,int key2,int key3){ return m_parent->intf ## _OnAdded(dest,spid,key1,key2,key3);}\
virtual void OnChanged(HsvDestination dest,int spid,int key1,int key2,int key3,int eventid){ return m_parent->intf ## _OnChanged(dest,spid,key1,key2,key3,eventid);}\
virtual void OnRemoved(HsvDestination dest,int spid,int key1,int key2,int key3){ return m_parent->intf ## _OnRemoved(dest,spid,key1,key2,key3);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
