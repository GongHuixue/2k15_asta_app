#ifndef IHSVPROGRAMDATANOTIFYEXEXEX_H
#define IHSVPROGRAMDATANOTIFYEXEXEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataNotifyExExEx
{
public:
	virtual ~IHsvProgramDataNotifyExExEx(){}
	virtual void OnChannelAdded(AppApiChannel channel)= 0;
	virtual void OnChannelRemoved(AppApiChannel channel)= 0;
	virtual void OnChannelUpdated(AppApiChannel channel,int attribute)= 0;
	virtual void OnChannelTableReset(void)= 0;
	virtual void OnChannelTableChanged(void)= 0;
	virtual void OnChannelsRearranged(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual void OnChannelTableUpdateStart(void)= 0;
	virtual void OnChannelTableUpdateEnd(int Reset)= 0;
	virtual void OnChannelsSwapped(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual void OnChannelMapLoadComplete(Bool Status)= 0;
	virtual void OnChannelMapSaveComplete(Bool Status)= 0;
};


#define IHsvProgramDataNotifyExExExImpl(Comp,intf)    \
virtual void intf ## _OnChannelAdded(AppApiChannel channel);\
virtual void intf ## _OnChannelRemoved(AppApiChannel channel);\
virtual void intf ## _OnChannelUpdated(AppApiChannel channel,int attribute);\
virtual void intf ## _OnChannelTableReset(void);\
virtual void intf ## _OnChannelTableChanged(void);\
virtual void intf ## _OnChannelsRearranged(AppApiChannel channel1,AppApiChannel channel2);\
virtual void intf ## _OnChannelTableUpdateStart(void);\
virtual void intf ## _OnChannelTableUpdateEnd(int Reset);\
virtual void intf ## _OnChannelsSwapped(AppApiChannel channel1,AppApiChannel channel2);\
virtual void intf ## _OnChannelMapLoadComplete(Bool Status);\
virtual void intf ## _OnChannelMapSaveComplete(Bool Status);\
class Comp ## _ ## intf : public IHsvProgramDataNotifyExExEx \
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
virtual void OnChannelMapLoadComplete(Bool Status){ return m_parent->intf ## _OnChannelMapLoadComplete(Status);}\
virtual void OnChannelMapSaveComplete(Bool Status){ return m_parent->intf ## _OnChannelMapSaveComplete(Status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
