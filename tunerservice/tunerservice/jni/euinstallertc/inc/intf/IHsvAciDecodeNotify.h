#ifndef IHSVACIDECODENOTIFY_H
#define IHSVACIDECODENOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciDecodeNotify
{
public:
	virtual ~IHsvAciDecodeNotify(){}
	virtual void OnReceivedPage(void)= 0;
	virtual void OnHeaderDecoded(void)= 0;
	virtual void OnDecodeSuccessful(void)= 0;
	virtual void OnDecodeFailure(void)= 0;
};


#define IHsvAciDecodeNotifyImpl(Comp,intf)    \
virtual void intf ## _OnReceivedPage(void);\
virtual void intf ## _OnHeaderDecoded(void);\
virtual void intf ## _OnDecodeSuccessful(void);\
virtual void intf ## _OnDecodeFailure(void);\
class Comp ## _ ## intf : public IHsvAciDecodeNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnReceivedPage(void){ return m_parent->intf ## _OnReceivedPage();}\
virtual void OnHeaderDecoded(void){ return m_parent->intf ## _OnHeaderDecoded();}\
virtual void OnDecodeSuccessful(void){ return m_parent->intf ## _OnDecodeSuccessful();}\
virtual void OnDecodeFailure(void){ return m_parent->intf ## _OnDecodeFailure();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
