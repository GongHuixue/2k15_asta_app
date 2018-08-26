#ifndef IHSVSYSTEMSETTINGSNOTIFY_H
#define IHSVSYSTEMSETTINGSNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSystemSettingsNotify
{
public:
	virtual ~IHsvSystemSettingsNotify(){}
	virtual void Notify(int property,int value)= 0;
};


#define IHsvSystemSettingsNotifyImpl(Comp,intf)    \
virtual void intf ## _Notify(int property,int value);\
class Comp ## _ ## intf : public IHsvSystemSettingsNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Notify(int property,int value){ return m_parent->intf ## _Notify(property,value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
