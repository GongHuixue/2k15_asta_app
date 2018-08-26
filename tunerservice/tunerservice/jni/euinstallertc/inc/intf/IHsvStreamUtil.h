#ifndef IHSVSTREAMUTIL_H
#define IHSVSTREAMUTIL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvStreamUtil
{
public:
	virtual ~IHsvStreamUtil(){}
	virtual int GetLCNValue(Nat8 * ptr,int num)= 0;
};


#define IHsvStreamUtilImpl(Comp,intf)    \
virtual int intf ## _GetLCNValue(Nat8 * ptr,int num);\
class Comp ## _ ## intf : public IHsvStreamUtil \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetLCNValue(Nat8 * ptr,int num){ return m_parent->intf ## _GetLCNValue(ptr,num);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
