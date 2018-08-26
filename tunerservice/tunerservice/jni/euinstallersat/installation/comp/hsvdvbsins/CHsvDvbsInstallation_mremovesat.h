#ifndef  _CHSVDVBSINSTALLATION_MREMOVESAT_H
#define  _CHSVDVBSINSTALLATION_MREMOVESAT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
class CHsvDvbsInstallation_mremovesat_Priv;
class CHsvDvbsInstallation_mremovesat
{
public:
ProvidesInterface<IHsvSatelliteInstallation>	iaddremove;

ProvidesInterface<IHsvPower>	iremovesatpow;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IPumpExSub>	pmp;
public:
CHsvDvbsInstallation_mremovesat();
virtual ~CHsvDvbsInstallation_mremovesat();
private:
CHsvDvbsInstallation_mremovesat_Priv	*m_priv;
};

#endif

