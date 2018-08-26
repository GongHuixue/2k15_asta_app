#ifndef IHSVCHANNELLIBSYNCEVENTS_H
#define IHSVCHANNELLIBSYNCEVENTS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvChannelLibSyncEvents
{
public:
	virtual ~IHsvChannelLibSyncEvents(){}
	virtual void EnableEvents(Bool Status)= 0;
	virtual void MasterEnableEvents(Bool Status)= 0;
	virtual void OnInsert(int tableid,Address data)= 0;
	virtual void OnUpdate(int tableid,Address data)= 0;
	virtual void OnDelete(int tableid,Address data)= 0;
};


#define IHsvChannelLibSyncEventsImpl(Comp,intf)    \
virtual void intf ## _EnableEvents(Bool Status);\
virtual void intf ## _MasterEnableEvents(Bool Status);\
virtual void intf ## _OnInsert(int tableid,Address data);\
virtual void intf ## _OnUpdate(int tableid,Address data);\
virtual void intf ## _OnDelete(int tableid,Address data);\
class Comp ## _ ## intf : public IHsvChannelLibSyncEvents \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void EnableEvents(Bool Status){ return m_parent->intf ## _EnableEvents(Status);}\
virtual void MasterEnableEvents(Bool Status){ return m_parent->intf ## _MasterEnableEvents(Status);}\
virtual void OnInsert(int tableid,Address data){ return m_parent->intf ## _OnInsert(tableid,data);}\
virtual void OnUpdate(int tableid,Address data){ return m_parent->intf ## _OnUpdate(tableid,data);}\
virtual void OnDelete(int tableid,Address data){ return m_parent->intf ## _OnDelete(tableid,data);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
