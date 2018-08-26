#ifndef  _CHSVDVBSPOL_MSORT_H
#define  _CHSVDVBSPOL_MSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSorting.h>
#include <IHsvPower.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
class CHsvDvbsPol_mSort_Priv;
class CHsvDvbsPol_mSort
{
public:
ProvidesInterface<IHsvSorting>	ipolsort;

ProvidesInterface<IHsvPower>	isortpow;

//Required interfaces
public:
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
public:
CHsvDvbsPol_mSort();
virtual ~CHsvDvbsPol_mSort();
private:
CHsvDvbsPol_mSort_Priv	*m_priv;
};

#endif

