#ifndef ICESCIPCAMSTATUSNOTIFY_H
#define ICESCIPCAMSTATUSNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class ICesCipCAMStatusNotify
{
public:
	virtual ~ICesCipCAMStatusNotify(){}
	virtual void OnEvent(CIPlusStatus_e status)= 0;
};


#define ICesCipCAMStatusNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(CIPlusStatus_e status);\
class Comp ## _ ## intf : public ICesCipCAMStatusNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(CIPlusStatus_e status){ return m_parent->intf ## _OnEvent(status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
