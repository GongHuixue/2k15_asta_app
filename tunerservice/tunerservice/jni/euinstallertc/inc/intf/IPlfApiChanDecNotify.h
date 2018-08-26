#ifndef IPLFAPICHANDECNOTIFY_H
#define IPLFAPICHANDECNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDecNotify
{
public:
	virtual ~IPlfApiChanDecNotify(){}
	virtual void OnHierarchyModeDetected(tmFe_HierarchyMode_t mode)= 0;
	virtual void OnCarrierPresentChanged(Bool carrier)= 0;
};


#define IPlfApiChanDecNotifyImpl(Comp,intf)    \
virtual void intf ## _OnHierarchyModeDetected(tmFe_HierarchyMode_t mode);\
virtual void intf ## _OnCarrierPresentChanged(Bool carrier);\
class Comp ## _ ## intf : public IPlfApiChanDecNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnHierarchyModeDetected(tmFe_HierarchyMode_t mode){ return m_parent->intf ## _OnHierarchyModeDetected(mode);}\
virtual void OnCarrierPresentChanged(Bool carrier){ return m_parent->intf ## _OnCarrierPresentChanged(carrier);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
