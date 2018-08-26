#ifndef IHSVSTREAMFILTERNOTIFY_H
#define IHSVSTREAMFILTERNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvStreamFilterNotify
{
public:
	virtual ~IHsvStreamFilterNotify(){}
	virtual void OnReady(HsvDestination dest,int filterid)= 0;
};


#define IHsvStreamFilterNotifyImpl(Comp,intf)    \
virtual void intf ## _OnReady(HsvDestination dest,int filterid);\
class Comp ## _ ## intf : public IHsvStreamFilterNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnReady(HsvDestination dest,int filterid){ return m_parent->intf ## _OnReady(dest,filterid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
