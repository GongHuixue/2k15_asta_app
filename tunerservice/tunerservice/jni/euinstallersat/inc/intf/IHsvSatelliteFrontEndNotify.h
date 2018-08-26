#ifndef IHSVSATELLITEFRONTENDNOTIFY_H
#define IHSVSATELLITEFRONTENDNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteFrontEndNotify
{
public:
	virtual ~IHsvSatelliteFrontEndNotify(){}
	virtual void OnLockChanged(Bool LockState)= 0;
	virtual void OnBlindScanEnd(void)= 0;
};


#define IHsvSatelliteFrontEndNotifyImpl(Comp,intf)    \
virtual void intf ## _OnLockChanged(Bool LockState);\
virtual void intf ## _OnBlindScanEnd(void);\
class Comp ## _ ## intf : public IHsvSatelliteFrontEndNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnLockChanged(Bool LockState){ return m_parent->intf ## _OnLockChanged(LockState);}\
virtual void OnBlindScanEnd(void){ return m_parent->intf ## _OnBlindScanEnd();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
