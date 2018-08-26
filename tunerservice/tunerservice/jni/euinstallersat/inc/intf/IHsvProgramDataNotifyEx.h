#ifndef IHSVPROGRAMDATANOTIFYEX_H
#define IHSVPROGRAMDATANOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataNotifyEx
{
public:
	virtual ~IHsvProgramDataNotifyEx(){}
	#define IHsvProgramDataNotifyEx_MajorChannel		((int)0 )
	#define IHsvProgramDataNotifyEx_MinorChannel		((int)1 )
	#define IHsvProgramDataNotifyEx_PIDs		((int)2 )
	virtual void OnUpdated(HsvChannel channel,int item)= 0;
	virtual void OnAdded(HsvChannel channel,int item)= 0;
	virtual void OnRemoved(HsvChannel channel,int item)= 0;
	virtual void OnChannelsSwapped(HsvChannel channel1,HsvChannel channel2)= 0;
	virtual void OnChannelsRearranged(HsvChannel src,HsvChannel dst)= 0;
};


#define IHsvProgramDataNotifyExImpl(Comp,intf)    \
virtual void intf ## _OnUpdated(HsvChannel channel,int item);\
virtual void intf ## _OnAdded(HsvChannel channel,int item);\
virtual void intf ## _OnRemoved(HsvChannel channel,int item);\
virtual void intf ## _OnChannelsSwapped(HsvChannel channel1,HsvChannel channel2);\
virtual void intf ## _OnChannelsRearranged(HsvChannel src,HsvChannel dst);\
class Comp ## _ ## intf : public IHsvProgramDataNotifyEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnUpdated(HsvChannel channel,int item){ return m_parent->intf ## _OnUpdated(channel,item);}\
virtual void OnAdded(HsvChannel channel,int item){ return m_parent->intf ## _OnAdded(channel,item);}\
virtual void OnRemoved(HsvChannel channel,int item){ return m_parent->intf ## _OnRemoved(channel,item);}\
virtual void OnChannelsSwapped(HsvChannel channel1,HsvChannel channel2){ return m_parent->intf ## _OnChannelsSwapped(channel1,channel2);}\
virtual void OnChannelsRearranged(HsvChannel src,HsvChannel dst){ return m_parent->intf ## _OnChannelsRearranged(src,dst);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
