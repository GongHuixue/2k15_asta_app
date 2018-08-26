#ifndef IHSVTXTPRESENT_H
#define IHSVTXTPRESENT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPresent
{
public:
	virtual ~IHsvTxtPresent(){}
	virtual Bool WstPresent(void)= 0;
	virtual Bool VpsPresent(void)= 0;
};


#define IHsvTxtPresentImpl(Comp,intf)    \
virtual Bool intf ## _WstPresent(void);\
virtual Bool intf ## _VpsPresent(void);\
class Comp ## _ ## intf : public IHsvTxtPresent \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool WstPresent(void){ return m_parent->intf ## _WstPresent();}\
virtual Bool VpsPresent(void){ return m_parent->intf ## _VpsPresent();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
