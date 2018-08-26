#ifndef IINFRATIMERSERVER_H
#define IINFRATIMERSERVER_H
#include <intfparam.h>
#include <provreq.h>
class IInfraTimerServer
{
public:
	virtual ~IInfraTimerServer(){}
	virtual STimer Create(Function ntf)= 0;
	virtual void FireOnce(STimer tmr,Int32 seconds)= 0;
	virtual void FireEvery(STimer tmr,Int32 seconds)= 0;
	virtual void Cancel(STimer tmr)= 0;
	virtual void Delete(STimer tmr)= 0;
	virtual Bool State(STimer tmr,Int32 * remaining,Int32 * reload)= 0;
};


#define IInfraTimerServerImpl(Comp,intf)    \
virtual STimer intf ## _Create(Function ntf);\
virtual void intf ## _FireOnce(STimer tmr,Int32 seconds);\
virtual void intf ## _FireEvery(STimer tmr,Int32 seconds);\
virtual void intf ## _Cancel(STimer tmr);\
virtual void intf ## _Delete(STimer tmr);\
virtual Bool intf ## _State(STimer tmr,Int32 * remaining,Int32 * reload);\
class Comp ## _ ## intf : public IInfraTimerServer \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual STimer Create(Function ntf){ return m_parent->intf ## _Create(ntf);}\
virtual void FireOnce(STimer tmr,Int32 seconds){ return m_parent->intf ## _FireOnce(tmr,seconds);}\
virtual void FireEvery(STimer tmr,Int32 seconds){ return m_parent->intf ## _FireEvery(tmr,seconds);}\
virtual void Cancel(STimer tmr){ return m_parent->intf ## _Cancel(tmr);}\
virtual void Delete(STimer tmr){ return m_parent->intf ## _Delete(tmr);}\
virtual Bool State(STimer tmr,Int32 * remaining,Int32 * reload){ return m_parent->intf ## _State(tmr,remaining,reload);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
