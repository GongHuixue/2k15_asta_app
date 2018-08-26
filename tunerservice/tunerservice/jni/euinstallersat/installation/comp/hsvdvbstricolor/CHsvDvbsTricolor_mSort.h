#ifndef  _CHSVDVBSTRICOLOR_MSORT_H
#define  _CHSVDVBSTRICOLOR_MSORT_H 

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
class CHsvDvbsTricolor_mSort_Priv;
class CHsvDvbsTricolor_mSort
{
public:
ProvidesInterface<IHsvSorting>	itricolorsort;
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
CHsvDvbsTricolor_mSort();
virtual ~CHsvDvbsTricolor_mSort();
private:
CHsvDvbsTricolor_mSort_Priv	*m_priv;
};

#endif

