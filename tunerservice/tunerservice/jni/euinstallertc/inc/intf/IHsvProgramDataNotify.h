#ifndef IHSVPROGRAMDATANOTIFY_H
#define IHSVPROGRAMDATANOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataNotify
{
public:
	virtual ~IHsvProgramDataNotify(){}
	virtual void OnChannelAdded(AppApiChannel channel)= 0;
	virtual void OnChannelRemoved(AppApiChannel channel)= 0;
	virtual void OnChannelUpdated(AppApiChannel channel,int attribute)= 0;
	virtual void OnChannelTableReset(void)= 0;
	virtual void OnChannelTableChanged(void)= 0;
	virtual void OnChannelsRearranged(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual void OnChannelTableUpdateStart(void)= 0;
	virtual void OnChannelTableUpdateEnd(int Reset)= 0;
	virtual void OnChannelsSwapped(AppApiChannel channel1,AppApiChannel channel2)= 0;
};


#define IHsvProgramDataNotifyImpl(Comp,intf)    \
virtual void intf ## _OnChannelAdded(AppApiChannel channel);\
virtual void intf ## _OnChannelRemoved(AppApiChannel channel);\
virtual void intf ## _OnChannelUpdated(AppApiChannel channel,int attribute);\
virtual void intf ## _OnChannelTableReset(void);\
virtual void intf ## _OnChannelTableChanged(void);\
virtual void intf ## _OnChannelsRearranged(AppApiChannel channel1,AppApiChannel channel2);\
virtual void intf ## _OnChannelTableUpdateStart(void);\
virtual void intf ## _OnChannelTableUpdateEnd(int Reset);\
virtual void intf ## _OnChannelsSwapped(AppApiChannel channel1,AppApiChannel channel2);\
class Comp ## _ ## intf : public IHsvProgramDataNotify \
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
virtual void OnChannelsRearranged(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _OnChannelsRearranged(channel1,channel2);}\
virtual void OnChannelTableUpdateStart(void){ return m_parent->intf ## _OnChannelTableUpdateStart();}\
virtual void OnChannelTableUpdateEnd(int Reset){ return m_parent->intf ## _OnChannelTableUpdateEnd(Reset);}\
virtual void OnChannelsSwapped(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _OnChannelsSwapped(channel1,channel2);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
