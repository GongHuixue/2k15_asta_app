#ifndef  _CHSVDVBSDIGITURK_MSORT_H
#define  _CHSVDVBSDIGITURK_MSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSorting.h>
#include <IHsvPower.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvDigitalScanData.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
class CHsvDvbsDigiTurk_mSort_Priv;
class CHsvDvbsDigiTurk_mSort
{
public:
ProvidesInterface<IHsvSorting>	isort;

ProvidesInterface<IHsvPower>	isortpow;

//Required interfaces
public:
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvDigitalScanData>	iscandata;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
public:
CHsvDvbsDigiTurk_mSort();
virtual ~CHsvDvbsDigiTurk_mSort();
private:
CHsvDvbsDigiTurk_mSort_Priv	*m_priv;
};

#endif

