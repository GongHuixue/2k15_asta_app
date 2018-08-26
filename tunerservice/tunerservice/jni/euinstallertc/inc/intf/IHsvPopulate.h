#ifndef IHSVPOPULATE_H
#define IHSVPOPULATE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPopulate
{
public:
	virtual ~IHsvPopulate(){}
	virtual Bool PopulateNIT(HsvDemux dmx,Address NetWkTable,int code)= 0;
	virtual Bool PopulateSDT(HsvDemux dmx,Address ServiceTable,int code,Nat32 cookie)= 0;
	virtual Bool PopulateTDT(HsvDemux dmx,Address TimeDateTable,int code)= 0;
	virtual Bool PopulateTOT(HsvDemux dmx,Address TimeOffsetTable,int code)= 0;
};


#define IHsvPopulateImpl(Comp,intf)    \
virtual Bool intf ## _PopulateNIT(HsvDemux dmx,Address NetWkTable,int code);\
virtual Bool intf ## _PopulateSDT(HsvDemux dmx,Address ServiceTable,int code,Nat32 cookie);\
virtual Bool intf ## _PopulateTDT(HsvDemux dmx,Address TimeDateTable,int code);\
virtual Bool intf ## _PopulateTOT(HsvDemux dmx,Address TimeOffsetTable,int code);\
class Comp ## _ ## intf : public IHsvPopulate \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool PopulateNIT(HsvDemux dmx,Address NetWkTable,int code){ return m_parent->intf ## _PopulateNIT(dmx,NetWkTable,code);}\
virtual Bool PopulateSDT(HsvDemux dmx,Address ServiceTable,int code,Nat32 cookie){ return m_parent->intf ## _PopulateSDT(dmx,ServiceTable,code,cookie);}\
virtual Bool PopulateTDT(HsvDemux dmx,Address TimeDateTable,int code){ return m_parent->intf ## _PopulateTDT(dmx,TimeDateTable,code);}\
virtual Bool PopulateTOT(HsvDemux dmx,Address TimeOffsetTable,int code){ return m_parent->intf ## _PopulateTOT(dmx,TimeOffsetTable,code);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
