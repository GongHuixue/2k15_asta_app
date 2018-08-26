#ifndef IHSVACIDISPLAYNOTIFY_H
#define IHSVACIDISPLAYNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciDisplayNotify
{
public:
	virtual ~IHsvAciDisplayNotify(){}
	virtual void OnMultiPackageFound(void)= 0;
	virtual void OnMultiPackageToBeDisplayed(void)= 0;
	virtual void OnMultiPackageDisplayed(void)= 0;
	virtual void OnMultiPackageRemoved(void)= 0;
};


#define IHsvAciDisplayNotifyImpl(Comp,intf)    \
virtual void intf ## _OnMultiPackageFound(void);\
virtual void intf ## _OnMultiPackageToBeDisplayed(void);\
virtual void intf ## _OnMultiPackageDisplayed(void);\
virtual void intf ## _OnMultiPackageRemoved(void);\
class Comp ## _ ## intf : public IHsvAciDisplayNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnMultiPackageFound(void){ return m_parent->intf ## _OnMultiPackageFound();}\
virtual void OnMultiPackageToBeDisplayed(void){ return m_parent->intf ## _OnMultiPackageToBeDisplayed();}\
virtual void OnMultiPackageDisplayed(void){ return m_parent->intf ## _OnMultiPackageDisplayed();}\
virtual void OnMultiPackageRemoved(void){ return m_parent->intf ## _OnMultiPackageRemoved();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
