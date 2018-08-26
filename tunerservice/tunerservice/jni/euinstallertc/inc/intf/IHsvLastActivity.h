#ifndef IHSVLASTACTIVITY_H
#define IHSVLASTACTIVITY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvLastActivity
{
public:
	virtual ~IHsvLastActivity(){}
	virtual void PerformLastActivity(void)= 0;
};


#define IHsvLastActivityImpl(Comp,intf)    \
virtual void intf ## _PerformLastActivity(void);\
class Comp ## _ ## intf : public IHsvLastActivity \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void PerformLastActivity(void){ return m_parent->intf ## _PerformLastActivity();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
