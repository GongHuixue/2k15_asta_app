#ifndef IHSVSATELLITEBACKGROUNDINSTALLATION_H
#define IHSVSATELLITEBACKGROUNDINSTALLATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteBackgroundInstallation
{
public:
	virtual ~IHsvSatelliteBackgroundInstallation(){}
	virtual void EnableBackgroundInstallation(void)= 0;
	virtual void DisableBackgroundInstallation(void)= 0;
};


#define IHsvSatelliteBackgroundInstallationImpl(Comp,intf)    \
virtual void intf ## _EnableBackgroundInstallation(void);\
virtual void intf ## _DisableBackgroundInstallation(void);\
class Comp ## _ ## intf : public IHsvSatelliteBackgroundInstallation \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void EnableBackgroundInstallation(void){ return m_parent->intf ## _EnableBackgroundInstallation();}\
virtual void DisableBackgroundInstallation(void){ return m_parent->intf ## _DisableBackgroundInstallation();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
