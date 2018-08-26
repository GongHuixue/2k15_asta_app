#ifndef  _CHSVDVBSINSTALLATION_MSETTINGS_H
#define  _CHSVDVBSINSTALLATION_MSETTINGS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvPower.h>
#include <IHsvSatelliteInstallationRoute.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSystemSettingsNotify.h>
#include <IHsvSystemSettings.h>

class CHsvDvbsInstallation_msettings_Priv;
class CHsvDvbsInstallation_msettings
{
public:
ProvidesInterface<IHsvSatelliteSettings>	idvbset;

ProvidesInterface<IHsvPower>	idvbsetpow;

ProvidesInterface<IHsvSatelliteInstallationRoute>	insroute;

ProvidesInterface<IHsvSystemSettingsNotify>	sysnotifyN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatSystemSettings>	sysset;
public:
CHsvDvbsInstallation_msettings();
virtual ~CHsvDvbsInstallation_msettings();
private:
CHsvDvbsInstallation_msettings_Priv	*m_priv;
};

#endif

