#ifndef IHSVDVBSERVICE_H
#define IHSVDVBSERVICE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDVBService
{
public:
	virtual ~IHsvDVBService(){}
	virtual Bool GetCurrentService(HsvDemux dmx,int * onwid,int * svcid)= 0;
	virtual Bool GetCurrentService2(HsvDemux dmx,int * onwid,int * tsid,int * svcid)= 0;
	virtual Bool GetOtherService(HsvDemux dmx,int * onwid,int * svcid)= 0;
	virtual Bool GetActualEitSchedService(HsvDemux dmx,int * svcid)= 0;
	virtual Bool GetOtherEitSchedService(HsvDemux dmx,int * svcid)= 0;
	virtual Bool GetExtendedInfoEventId(HsvDemux dmx,int * evtid)= 0;
};


#define IHsvDVBServiceImpl(Comp,intf)    \
virtual Bool intf ## _GetCurrentService(HsvDemux dmx,int * onwid,int * svcid);\
virtual Bool intf ## _GetCurrentService2(HsvDemux dmx,int * onwid,int * tsid,int * svcid);\
virtual Bool intf ## _GetOtherService(HsvDemux dmx,int * onwid,int * svcid);\
virtual Bool intf ## _GetActualEitSchedService(HsvDemux dmx,int * svcid);\
virtual Bool intf ## _GetOtherEitSchedService(HsvDemux dmx,int * svcid);\
virtual Bool intf ## _GetExtendedInfoEventId(HsvDemux dmx,int * evtid);\
class Comp ## _ ## intf : public IHsvDVBService \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool GetCurrentService(HsvDemux dmx,int * onwid,int * svcid){ return m_parent->intf ## _GetCurrentService(dmx,onwid,svcid);}\
virtual Bool GetCurrentService2(HsvDemux dmx,int * onwid,int * tsid,int * svcid){ return m_parent->intf ## _GetCurrentService2(dmx,onwid,tsid,svcid);}\
virtual Bool GetOtherService(HsvDemux dmx,int * onwid,int * svcid){ return m_parent->intf ## _GetOtherService(dmx,onwid,svcid);}\
virtual Bool GetActualEitSchedService(HsvDemux dmx,int * svcid){ return m_parent->intf ## _GetActualEitSchedService(dmx,svcid);}\
virtual Bool GetOtherEitSchedService(HsvDemux dmx,int * svcid){ return m_parent->intf ## _GetOtherEitSchedService(dmx,svcid);}\
virtual Bool GetExtendedInfoEventId(HsvDemux dmx,int * evtid){ return m_parent->intf ## _GetExtendedInfoEventId(dmx,evtid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
