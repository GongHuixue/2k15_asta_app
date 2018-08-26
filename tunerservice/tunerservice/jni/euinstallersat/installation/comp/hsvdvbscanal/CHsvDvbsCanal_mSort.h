#ifndef  _CHSVDVBSCANAL_MSORT_H
#define  _CHSVDVBSCANAL_MSORT_H 

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
class CHsvDvbsCanal_mSort_Priv;
class CHsvDvbsCanal_mSort
{
public:
ProvidesInterface<IHsvSorting>	icanalsort;

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
CHsvDvbsCanal_mSort();
virtual ~CHsvDvbsCanal_mSort();
private:
CHsvDvbsCanal_mSort_Priv	*m_priv;
};

#endif

