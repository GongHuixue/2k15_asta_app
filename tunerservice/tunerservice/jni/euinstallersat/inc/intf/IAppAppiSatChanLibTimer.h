#ifndef IAPPAPPISATCHANLIBTIMER_H
#define IAPPAPPISATCHANLIBTIMER_H
#include <intfparam.h>
#include <provreq.h>
class IAppAppiSatChanLibTimer
{
public:
	virtual ~IAppAppiSatChanLibTimer(){}
	virtual void ActivateS2AliveTimer(void)= 0;
};


#define IAppAppiSatChanLibTimerImpl(Comp,intf)    \
virtual void intf ## _ActivateS2AliveTimer(void);\
class Comp ## _ ## intf : public IAppAppiSatChanLibTimer \
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
