#ifndef IHSVLASTACTIVITYNOTIFY_H
#define IHSVLASTACTIVITYNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvLastActivityNotify
{
public:
	virtual ~IHsvLastActivityNotify(){}
	virtual void LastActivityPerformed(void)= 0;
};


#define IHsvLastActivityNotifyImpl(Comp,intf)    \
virtual void intf ## _LastActivityPerformed(void);\
class Comp ## _ ## intf : public IHsvLastActivityNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void LastActivityPerformed(void){ return m_parent->intf ## _LastActivityPerformed();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
