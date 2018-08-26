#ifndef IHSVPROGRAMDATANOTIFY2_H
#define IHSVPROGRAMDATANOTIFY2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataNotify2
{
public:
	virtual ~IHsvProgramDataNotify2(){}
	#define IHsvProgramDataNotify2_MajorChannel		((int)0 )
	#define IHsvProgramDataNotify2_MinorChannel		((int)1 )
	#define IHsvProgramDataNotify2_PIDs		((int)2 )
	virtual void OnUpdated(int tableid,HsvChannel channel,int item)= 0;
	virtual void OnAdded(int tableid,HsvChannel channel,int item)= 0;
	virtual void OnRemoved(int tableid,HsvChannel channel,int item)= 0;
	virtual void OnChannelsSwapped(int tableid,HsvChannel channel1,HsvChannel channel2)= 0;
};


#define IHsvProgramDataNotify2Impl(Comp,intf)    \
virtual void intf ## _OnUpdated(int tableid,HsvChannel channel,int item);\
virtual void intf ## _OnAdded(int tableid,HsvChannel channel,int item);\
virtual void intf ## _OnRemoved(int tableid,HsvChannel channel,int item);\
virtual void intf ## _OnChannelsSwapped(int tableid,HsvChannel channel1,HsvChannel channel2);\
class Comp ## _ ## intf : public IHsvProgramDataNotify2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnUpdated(int tableid,HsvChannel channel,int item){ return m_parent->intf ## _OnUpdated(tableid,channel,item);}\
virtual void OnAdded(int tableid,HsvChannel channel,int item){ return m_parent->intf ## _OnAdded(tableid,channel,item);}\
virtual void OnRemoved(int tableid,HsvChannel channel,int item){ return m_parent->intf ## _OnRemoved(tableid,channel,item);}\
virtual void OnChannelsSwapped(int tableid,HsvChannel channel1,HsvChannel channel2){ return m_parent->intf ## _OnChannelsSwapped(tableid,channel1,channel2);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
