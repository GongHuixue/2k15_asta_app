#ifndef IAPPAPISATSENDCHANNELEVENTS_H
#define IAPPAPISATSENDCHANNELEVENTS_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatSendChannelEvents
{
public:
	virtual ~IAppApiSatSendChannelEvents(){}
	#define IAppApiSatSendChannelEvents_SelectChannel		((int)0 )
	#define IAppApiSatSendChannelEvents_SetTvSystem		((int)1 )
	#define IAppApiSatSendChannelEvents_SetFrequency		((int)2 )
	#define IAppApiSatSendChannelEvents_MaxEvents		((int)3 )
	virtual void SendEvent(int EventId,Address data,Nat32 size)= 0;
};


#define IAppApiSatSendChannelEventsImpl(Comp,intf)    \
virtual void intf ## _SendEvent(int EventId,Address data,Nat32 size);\
class Comp ## _ ## intf : public IAppApiSatSendChannelEvents \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SendEvent(int EventId,Address data,Nat32 size){ return m_parent->intf ## _SendEvent(EventId,data,size);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
