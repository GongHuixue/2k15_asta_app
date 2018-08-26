#ifndef ITVPLATFORMRESOURCENOTIFY_H
#define ITVPLATFORMRESOURCENOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class ITvPlatformResourceNotify
{
public:
	virtual ~ITvPlatformResourceNotify(){}
	virtual void OnResourceLost(Nat32 resources)= 0;
	virtual void OnResourceGained(Nat32 resources)= 0;
	virtual void OnResourceStateChanged(int state)= 0;
};


#define ITvPlatformResourceNotifyImpl(Comp,intf)    \
virtual void intf ## _OnResourceLost(Nat32 resources);\
virtual void intf ## _OnResourceGained(Nat32 resources);\
virtual void intf ## _OnResourceStateChanged(int state);\
class Comp ## _ ## intf : public ITvPlatformResourceNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnResourceLost(Nat32 resources){ return m_parent->intf ## _OnResourceLost(resources);}\
virtual void OnResourceGained(Nat32 resources){ return m_parent->intf ## _OnResourceGained(resources);}\
virtual void OnResourceStateChanged(int state){ return m_parent->intf ## _OnResourceStateChanged(state);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
