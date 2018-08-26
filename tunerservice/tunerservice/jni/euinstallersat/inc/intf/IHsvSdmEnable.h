#ifndef IHSVSDMENABLE_H
#define IHSVSDMENABLE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmEnable
{
public:
	virtual ~IHsvSdmEnable(){}
	virtual void Enable(HsvDemux dmx)= 0;
	virtual void Disable(HsvDemux dmx)= 0;
	virtual void Sync(HsvDemux dmx)= 0;
};


#define IHsvSdmEnableImpl(Comp,intf)    \
virtual void intf ## _Enable(HsvDemux dmx);\
virtual void intf ## _Disable(HsvDemux dmx);\
virtual void intf ## _Sync(HsvDemux dmx);\
class Comp ## _ ## intf : public IHsvSdmEnable \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Enable(HsvDemux dmx){ return m_parent->intf ## _Enable(dmx);}\
virtual void Disable(HsvDemux dmx){ return m_parent->intf ## _Disable(dmx);}\
virtual void Sync(HsvDemux dmx){ return m_parent->intf ## _Sync(dmx);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
