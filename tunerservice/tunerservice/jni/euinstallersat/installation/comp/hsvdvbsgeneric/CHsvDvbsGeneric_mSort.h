#ifndef  _CHSVDVBSGENERIC_MSORT_H
#define  _CHSVDVBSGENERIC_MSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSorting.h>
#include <IHsvPower.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvPackageParser.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
class CHsvDvbsGeneric_mSort_Priv;
class CHsvDvbsGeneric_mSort
{
public:
ProvidesInterface<IHsvSorting>	isort;

ProvidesInterface<IHsvPower>	isortpow;

//Required interfaces
public:
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvPackageParser>	ipackage;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
public:
CHsvDvbsGeneric_mSort();
virtual ~CHsvDvbsGeneric_mSort();
private:
CHsvDvbsGeneric_mSort_Priv	*m_priv;
};

#endif

