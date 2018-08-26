#ifndef IPUMPENGINE_H
#define IPUMPENGINE_H
#include <intfparam.h>
#include <provreq.h>
class IPumpEngine
{
public:
	virtual ~IPumpEngine(){}
	virtual IThread* PumpEngine(void)= 0;
};


#define IPumpEngineImpl(Comp,intf)    \
friend class InterfaceParam<Comp,IThread*>;\
class Comp ## _ ## intf : public IPumpEngine \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,IThread*> m_PumpEngine; \
    Comp ## _ ## intf( Comp *parent):m_PumpEngine(parent) \
    {\
        m_parent = parent;\
    }\
virtual IThread* PumpEngine(void){ return m_PumpEngine.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
