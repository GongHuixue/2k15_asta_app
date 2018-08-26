#ifndef IHSVSOURCESETUPNOTIFY_H
#define IHSVSOURCESETUPNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSourceSetupNotify
{
public:
	virtual ~IHsvSourceSetupNotify(){}
	virtual void OnSourceSetupApplied(int Status)= 0;
};


#define IHsvSourceSetupNotifyImpl(Comp,intf)    \
virtual void intf ## _OnSourceSetupApplied(int Status);\
class Comp ## _ ## intf : public IHsvSourceSetupNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnSourceSetupApplied(int Status){ return m_parent->intf ## _OnSourceSetupApplied(Status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
