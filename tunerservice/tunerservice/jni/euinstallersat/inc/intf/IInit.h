#ifndef IINIT_H
#define IINIT_H
#include <intfparam.h>
#include <provreq.h>
class IInit
{
public:
	virtual ~IInit(){}
	virtual void Init(void)= 0;
};


#define IInitImpl(Comp,intf)    \
virtual void intf ## _Init(void);\
class Comp ## _ ## intf : public IInit \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Init(void){ return m_parent->intf ## _Init();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
