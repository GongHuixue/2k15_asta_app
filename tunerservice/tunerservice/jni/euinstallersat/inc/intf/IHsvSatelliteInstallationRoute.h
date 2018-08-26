#ifndef IHSVSATELLITEINSTALLATIONROUTE_H
#define IHSVSATELLITEINSTALLATIONROUTE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteInstallationRoute
{
public:
	virtual ~IHsvSatelliteInstallationRoute(){}
	#define IHsvSatelliteInstallationRoute_ScanPackageOnly		((int)0x01 )
	#define IHsvSatelliteInstallationRoute_ScanCompleteSatellite		((int)0x02 )
	virtual int GetActiveScanInterface(void)= 0;
	virtual Bool SetActiveScanInterface(int ScanMode)= 0;
};


#define IHsvSatelliteInstallationRouteImpl(Comp,intf)    \
virtual int intf ## _GetActiveScanInterface(void);\
virtual Bool intf ## _SetActiveScanInterface(int ScanMode);\
class Comp ## _ ## intf : public IHsvSatelliteInstallationRoute \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetActiveScanInterface(void){ return m_parent->intf ## _GetActiveScanInterface();}\
virtual Bool SetActiveScanInterface(int ScanMode){ return m_parent->intf ## _SetActiveScanInterface(ScanMode);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
