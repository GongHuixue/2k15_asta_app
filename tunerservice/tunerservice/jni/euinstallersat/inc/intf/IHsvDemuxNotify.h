#ifndef IHSVDEMUXNOTIFY_H
#define IHSVDEMUXNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDemuxNotify
{
public:
	virtual ~IHsvDemuxNotify(){}
	virtual void OnStarted(HsvDemux dmx)= 0;
	virtual void OnStopped(HsvDemux dmx)= 0;
	virtual void OnDemuxSyncLock(HsvDemux dmx)= 0;
	virtual void OnDemuxSyncLost(HsvDemux dmx)= 0;
};


#define IHsvDemuxNotifyImpl(Comp,intf)    \
virtual void intf ## _OnStarted(HsvDemux dmx);\
virtual void intf ## _OnStopped(HsvDemux dmx);\
virtual void intf ## _OnDemuxSyncLock(HsvDemux dmx);\
virtual void intf ## _OnDemuxSyncLost(HsvDemux dmx);\
class Comp ## _ ## intf : public IHsvDemuxNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnStarted(HsvDemux dmx){ return m_parent->intf ## _OnStarted(dmx);}\
virtual void OnStopped(HsvDemux dmx){ return m_parent->intf ## _OnStopped(dmx);}\
virtual void OnDemuxSyncLock(HsvDemux dmx){ return m_parent->intf ## _OnDemuxSyncLock(dmx);}\
virtual void OnDemuxSyncLost(HsvDemux dmx){ return m_parent->intf ## _OnDemuxSyncLost(dmx);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
