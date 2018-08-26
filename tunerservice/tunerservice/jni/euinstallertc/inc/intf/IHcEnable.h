#ifndef IHCENABLE_H
#define IHCENABLE_H
#include <intfparam.h>
#include <provreq.h>
class IHcEnable
{
public:
	virtual ~IHcEnable(){}
	virtual void Enable(int reason)= 0;
	virtual void Disable(int reason)= 0;
};


#define IHcEnableImpl(Comp,intf)    \
virtual void intf ## _Enable(int reason);\
virtual void intf ## _Disable(int reason);\
class Comp ## _ ## intf : public IHcEnable \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Enable(int reason){ return m_parent->intf ## _Enable(reason);}\
virtual void Disable(int reason){ return m_parent->intf ## _Disable(reason);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
