#ifndef IENABLE_H
#define IENABLE_H
#include <intfparam.h>
#include <provreq.h>
class IEnable
{
public:
	virtual ~IEnable(){}
	virtual void Enable(void)= 0;
	virtual void Disable(void)= 0;
};


#define IEnableImpl(Comp,intf)    \
virtual void intf ## _Enable(void);\
virtual void intf ## _Disable(void);\
class Comp ## _ ## intf : public IEnable \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Enable(void){ return m_parent->intf ## _Enable();}\
virtual void Disable(void){ return m_parent->intf ## _Disable();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
