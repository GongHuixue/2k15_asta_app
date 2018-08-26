#ifndef IMULTINOTIFY_H
#define IMULTINOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IMultiNotify
{
public:
	virtual ~IMultiNotify(){}
	virtual void OnEvent(int id)= 0;
};


#define IMultiNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int id);\
class Comp ## _ ## intf : public IMultiNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int id){ return m_parent->intf ## _OnEvent(id);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
