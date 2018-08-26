#ifndef IHSVTABLECONTROL_H
#define IHSVTABLECONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTableControl
{
public:
	virtual ~IHsvTableControl(){}
	virtual Bool Parse(HsvDemux demux,Nat32 cookie,int code)= 0;
};


#define IHsvTableControlImpl(Comp,intf)    \
virtual Bool intf ## _Parse(HsvDemux demux,Nat32 cookie,int code);\
class Comp ## _ ## intf : public IHsvTableControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool Parse(HsvDemux demux,Nat32 cookie,int code){ return m_parent->intf ## _Parse(demux,cookie,code);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
