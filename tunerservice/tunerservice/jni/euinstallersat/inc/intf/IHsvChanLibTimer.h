#ifndef IHSVCHANLIBTIMER_H
#define IHSVCHANLIBTIMER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvChanLibTimer
{
public:
	virtual ~IHsvChanLibTimer(){}
	virtual void ActivateS2AliveTimer(void)= 0;
};


#define IHsvChanLibTimerImpl(Comp,intf)    \
virtual void intf ## _ActivateS2AliveTimer(void);\
class Comp ## _ ## intf : public IHsvChanLibTimer \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void ActivateS2AliveTimer(void){ return m_parent->intf ## _ActivateS2AliveTimer();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
