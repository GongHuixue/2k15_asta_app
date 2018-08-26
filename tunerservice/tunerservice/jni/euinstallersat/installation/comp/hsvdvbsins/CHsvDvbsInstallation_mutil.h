#ifndef  _CHSVDVBSINSTALLATION_MUTIL_H
#define  _CHSVDVBSINSTALLATION_MUTIL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
class CHsvDvbsInstallation_mutil_Priv;
class CHsvDvbsInstallation_mutil
{
public:
ProvidesInterface<IHsvSatelliteUtility>	iutil;

//Required interfaces
public:
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
public:
CHsvDvbsInstallation_mutil();
virtual ~CHsvDvbsInstallation_mutil();
private:
CHsvDvbsInstallation_mutil_Priv	*m_priv;
};

#endif

