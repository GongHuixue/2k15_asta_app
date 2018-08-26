#ifndef IAPPAPISATPROGRAMDATANOTIFYEX_H
#define IAPPAPISATPROGRAMDATANOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataNotifyEx
{
public:
	virtual ~IAppApiSatProgramDataNotifyEx(){}
	virtual void OnChannelAdded(AppApiChannel channel)= 0;
	virtual void OnChannelRemoved(AppApiChannel channel)= 0;
	virtual void OnChannelUpdated(AppApiChannel channel,int attribute)= 0;
	virtual void OnChannelTableReset(void)= 0;
	virtual void OnChannelTableChanged(void)= 0;
	virtual void OnChannelTableUpdateStart(void)= 0;
	virtual void OnChannelTableUpdateEnd(int Reset)= 0;
};


#define IAppApiSatProgramDataNotifyExImpl(Comp,intf)    \
virtual void intf ## _OnChannelAdded(AppApiChannel channel);\
virtual void intf ## _OnChannelRemoved(AppApiChannel channel);\
virtual void intf ## _OnChannelUpdated(AppApiChannel channel,int attribute);\
virtual void intf ## _OnChannelTableReset(void);\
virtual void intf ## _OnChannelTableChanged(void);\
virtual void intf ## _OnChannelTableUpdateStart(void);\
virtual void intf ## _OnChannelTableUpdateEnd(int Reset);\
class Comp ## _ ## intf : public IAppApiSatProgramDataNotifyEx \
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
virtual void OnChannelTableUpdateStart(void){ return m_parent->intf ## _OnChannelTableUpdateStart();}\
virtual void OnChannelTableUpdateEnd(int Reset){ return m_parent->intf ## _OnChannelTableUpdateEnd(Reset);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
