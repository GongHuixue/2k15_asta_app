#ifndef IHSVSATELLITEINSTALLATIONCONSTANTS_H
#define IHSVSATELLITEINSTALLATIONCONSTANTS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteInstallationConstants
{
public:
	virtual ~IHsvSatelliteInstallationConstants(){}
	#define IHsvSatelliteInstallationConstants_InstallationNone		((int)0 )
	#define IHsvSatelliteInstallationConstants_InstallationPreScan		((int)1 )
	#define IHsvSatelliteInstallationConstants_InstallationServiceScan		((int)2 )
	#define IHsvSatelliteInstallationConstants_InstallationUpdate		((int)3 )
	#define IHsvSatelliteInstallationConstants_InstallationManual		((int)4 )
	#define IHsvSatelliteInstallationConstants_InstallationAddSatellite		((int)5 )
	#define IHsvSatelliteInstallationConstants_InstallationBackground		((int)6 )
	#define IHsvSatelliteInstallationConstants_InstallationBackgroundUpdate		((int)7 )
	#define IHsvSatelliteInstallationConstants_InstallationStateIdle		((int)0 )
	#define IHsvSatelliteInstallationConstants_InstallationStateInProgress		((int)1 )
	#define IHsvSatelliteInstallationConstants_InstallationStateSorting		((int)2 )
	#define IHsvSatelliteInstallationConstants_ManualInstallLnb		((int)1 )
	#define IHsvSatelliteInstallationConstants_ManualInstallFreq		((int)2 )
	#define IHsvSatelliteInstallationConstants_ManualInstallPolaraization		((int)3 )
	#define IHsvSatelliteInstallationConstants_ManualInstallSymRate		((int)4 )
	#define IHsvSatelliteInstallationConstants_ManualInstallSymRateMode		((int)5 )
	#define IHsvSatelliteInstallationConstants_ManualInstallModulation		((int)6 )
};


#define IHsvSatelliteInstallationConstantsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvSatelliteInstallationConstants \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
