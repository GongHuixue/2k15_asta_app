#ifndef IHSVSDTRESET_H
#define IHSVSDTRESET_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSDTReset
{
public:
	virtual ~IHsvSDTReset(){}
	virtual void SDTReset(int tableid)= 0;
};


#define IHsvSDTResetImpl(Comp,intf)    \
virtual void intf ## _SDTReset(int tableid);\
class Comp ## _ ## intf : public IHsvSDTReset \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SDTReset(int tableid){ return m_parent->intf ## _SDTReset(tableid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
