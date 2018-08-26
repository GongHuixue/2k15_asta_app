#ifndef IHSVDIGITALACQUISITIONNOTIFY_H
#define IHSVDIGITALACQUISITIONNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalAcquisitionNotify
{
public:
	virtual ~IHsvDigitalAcquisitionNotify(){}
	virtual void OnDataAquired(Bool Status)= 0;
};


#define IHsvDigitalAcquisitionNotifyImpl(Comp,intf)    \
virtual void intf ## _OnDataAquired(Bool Status);\
class Comp ## _ ## intf : public IHsvDigitalAcquisitionNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnDataAquired(Bool Status){ return m_parent->intf ## _OnDataAquired(Status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
