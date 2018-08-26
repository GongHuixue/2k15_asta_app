#ifndef IHSVSTREAMFILTER_H
#define IHSVSTREAMFILTER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvStreamFilter
{
public:
	virtual ~IHsvStreamFilter(){}
	virtual Bool IsSet(HsvDestination dest,int filterid,int value)= 0;
	virtual Bool IsReady(HsvDestination dest,int filterid)= 0;
	virtual Bool Set(HsvDestination dest,int filterid,int value)= 0;
	virtual Bool Clear(HsvDestination dest,int filterid,int value)= 0;
	virtual Bool ForceClear(HsvDestination dest,int filterid,int value)= 0;
};


#define IHsvStreamFilterImpl(Comp,intf)    \
virtual Bool intf ## _IsSet(HsvDestination dest,int filterid,int value);\
virtual Bool intf ## _IsReady(HsvDestination dest,int filterid);\
virtual Bool intf ## _Set(HsvDestination dest,int filterid,int value);\
virtual Bool intf ## _Clear(HsvDestination dest,int filterid,int value);\
virtual Bool intf ## _ForceClear(HsvDestination dest,int filterid,int value);\
class Comp ## _ ## intf : public IHsvStreamFilter \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool IsSet(HsvDestination dest,int filterid,int value){ return m_parent->intf ## _IsSet(dest,filterid,value);}\
virtual Bool IsReady(HsvDestination dest,int filterid){ return m_parent->intf ## _IsReady(dest,filterid);}\
virtual Bool Set(HsvDestination dest,int filterid,int value){ return m_parent->intf ## _Set(dest,filterid,value);}\
virtual Bool Clear(HsvDestination dest,int filterid,int value){ return m_parent->intf ## _Clear(dest,filterid,value);}\
virtual Bool ForceClear(HsvDestination dest,int filterid,int value){ return m_parent->intf ## _ForceClear(dest,filterid,value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
