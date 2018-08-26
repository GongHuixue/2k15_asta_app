#ifndef IHSVPROGRAMITERATORNOTIFY_H
#define IHSVPROGRAMITERATORNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramIteratorNotify
{
public:
	virtual ~IHsvProgramIteratorNotify(){}
	virtual void OnChannelAdded(HsvChannel channelno)= 0;
	virtual void OnChannelRemoved(HsvChannel channelno)= 0;
};


#define IHsvProgramIteratorNotifyImpl(Comp,intf)    \
virtual void intf ## _OnChannelAdded(HsvChannel channelno);\
virtual void intf ## _OnChannelRemoved(HsvChannel channelno);\
class Comp ## _ ## intf : public IHsvProgramIteratorNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnChannelAdded(HsvChannel channelno){ return m_parent->intf ## _OnChannelAdded(channelno);}\
virtual void OnChannelRemoved(HsvChannel channelno){ return m_parent->intf ## _OnChannelRemoved(channelno);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
