#ifndef IAPPAPISATPROGRAMDATANOTIFY_H
#define IAPPAPISATPROGRAMDATANOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataNotify
{
public:
	virtual ~IAppApiSatProgramDataNotify(){}
	virtual void OnChannelAdded(AppApiChannel channel)= 0;
	virtual void OnChannelRemoved(AppApiChannel channel)= 0;
	virtual void OnChannelUpdated(AppApiChannel channel,int attribute)= 0;
	virtual void OnChannelTableReset(void)= 0;
	virtual void OnChannelTableChanged(void)= 0;
};


#define IAppApiSatProgramDataNotifyImpl(Comp,intf)    \
virtual void intf ## _OnChannelAdded(AppApiChannel channel);\
virtual void intf ## _OnChannelRemoved(AppApiChannel channel);\
virtual void intf ## _OnChannelUpdated(AppApiChannel channel,int attribute);\
virtual void intf ## _OnChannelTableReset(void);\
virtual void intf ## _OnChannelTableChanged(void);\
class Comp ## _ ## intf : public IAppApiSatProgramDataNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnChannelAdded(AppApiChannel channel){ return m_parent->intf ## _OnChannelAdded(channel);}\
virtual void OnChannelRemoved(AppApiChannel channel){ return m_parent->intf ## _OnChannelRemoved(channel);}\
virtual void OnChannelUpdated(AppApiChannel channel,int attribute){ return m_parent->intf ## _OnChannelUpdated(channel,attribute);}\
virtual void OnChannelTableReset(void){ return m_parent->intf ## _OnChannelTableReset();}\
virtual void OnChannelTableChanged(void){ return m_parent->intf ## _OnChannelTableChanged();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
