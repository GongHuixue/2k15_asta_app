#ifndef  _CHSVDVBSRUSSIA_MACQ_H
#define  _CHSVDVBSRUSSIA_MACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvDigitalAcquisition.h>
#include <IProdApiClockEx.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvDigitalScanData.h>
#include <IHsvSatelliteUtility.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvStream.h>
#include <IHsvSatSystemSettings.h>
class CHsvDvbsRussia_mAcq_Priv;
class CHsvDvbsRussia_mAcq
{
public:
ProvidesInterface<IHsvPower>	iacqpow;

ProvidesInterface<IHsvDigitalAcquisition>	idataacq;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDigitalAcquisitionNotify>	idataacqN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvDigitalScanData>	isvcscandata;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
public:
CHsvDvbsRussia_mAcq();
virtual ~CHsvDvbsRussia_mAcq();
private:
CHsvDvbsRussia_mAcq_Priv	*m_priv;
};

#endif

