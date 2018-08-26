#ifndef IHSVEITTABLE_H
#define IHSVEITTABLE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvEitTable
{
public:
	virtual ~IHsvEitTable(){}
	virtual void SubscribeEIT8days(Bool value)= 0;
};


#define IHsvEitTableImpl(Comp,intf)    \
virtual void intf ## _SubscribeEIT8days(Bool value);\
class Comp ## _ ## intf : public IHsvEitTable \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SubscribeEIT8days(Bool value){ return m_parent->intf ## _SubscribeEIT8days(value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
