#ifndef IHSVINSTALLATIONMODE_H
#define IHSVINSTALLATIONMODE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationMode
{
public:
	virtual ~IHsvInstallationMode(){}
	virtual int GetCurrentScanMode(void)= 0;
};


#define IHsvInstallationModeImpl(Comp,intf)    \
virtual int intf ## _GetCurrentScanMode(void);\
class Comp ## _ ## intf : public IHsvInstallationMode \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetCurrentScanMode(void){ return m_parent->intf ## _GetCurrentScanMode();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
