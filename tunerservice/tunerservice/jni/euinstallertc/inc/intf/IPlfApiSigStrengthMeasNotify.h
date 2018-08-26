#ifndef IPLFAPISIGSTRENGTHMEASNOTIFY_H
#define IPLFAPISIGSTRENGTHMEASNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiSigStrengthMeasNotify
{
public:
	virtual ~IPlfApiSigStrengthMeasNotify(){}
	virtual void OnMeasReady(Nat32 strength)= 0;
	virtual void OnMeasAborted(void)= 0;
};


#define IPlfApiSigStrengthMeasNotifyImpl(Comp,intf)    \
virtual void intf ## _OnMeasReady(Nat32 strength);\
virtual void intf ## _OnMeasAborted(void);\
class Comp ## _ ## intf : public IPlfApiSigStrengthMeasNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnMeasReady(Nat32 strength){ return m_parent->intf ## _OnMeasReady(strength);}\
virtual void OnMeasAborted(void){ return m_parent->intf ## _OnMeasAborted();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
