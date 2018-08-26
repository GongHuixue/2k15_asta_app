#ifndef ISVPOWER_H
#define ISVPOWER_H
#include <intfparam.h>
#include <provreq.h>
class ISvPower
{
public:
	virtual ~ISvPower(){}
	virtual void Init(void)= 0;
	virtual void TurnOn(void)= 0;
	virtual void TurnOff(void)= 0;
};


#define ISvPowerImpl(Comp,intf)    \
virtual void intf ## _Init(void);\
virtual void intf ## _TurnOn(void);\
virtual void intf ## _TurnOff(void);\
class Comp ## _ ## intf : public ISvPower \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Init(void){ return m_parent->intf ## _Init();}\
virtual void TurnOn(void){ return m_parent->intf ## _TurnOn();}\
virtual void TurnOff(void){ return m_parent->intf ## _TurnOff();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
