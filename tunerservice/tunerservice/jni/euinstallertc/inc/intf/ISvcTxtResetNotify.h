#ifndef ISVCTXTRESETNOTIFY_H
#define ISVCTXTRESETNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class ISvcTxtResetNotify
{
public:
	virtual ~ISvcTxtResetNotify(){}
	virtual void OnResetBegin(void)= 0;
	virtual void OnResetEnd(void)= 0;
};


#define ISvcTxtResetNotifyImpl(Comp,intf)    \
virtual void intf ## _OnResetBegin(void);\
virtual void intf ## _OnResetEnd(void);\
class Comp ## _ ## intf : public ISvcTxtResetNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnResetBegin(void){ return m_parent->intf ## _OnResetBegin();}\
virtual void OnResetEnd(void){ return m_parent->intf ## _OnResetEnd();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
