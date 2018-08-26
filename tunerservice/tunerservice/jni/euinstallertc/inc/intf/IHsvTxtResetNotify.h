#ifndef IHSVTXTRESETNOTIFY_H
#define IHSVTXTRESETNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtResetNotify
{
public:
	virtual ~IHsvTxtResetNotify(){}
	virtual void OnResetEnd(void)= 0;
};


#define IHsvTxtResetNotifyImpl(Comp,intf)    \
virtual void intf ## _OnResetEnd(void);\
class Comp ## _ ## intf : public IHsvTxtResetNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnResetEnd(void){ return m_parent->intf ## _OnResetEnd();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
