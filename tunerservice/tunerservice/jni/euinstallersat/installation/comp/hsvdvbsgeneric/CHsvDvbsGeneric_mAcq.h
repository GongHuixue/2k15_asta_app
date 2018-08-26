#ifndef  _CHSVDVBSGENERIC_MACQ_H
#define  _CHSVDVBSGENERIC_MACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvDigitalAcquisition.h>
#include <IProdApiClockEx.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvPrescanParser.h>
#include <IHsvDigitalScanData.h>
#include <IHsvSatelliteUtility.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IRealTimeKernel.h>
#include <IHsvStream.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvPackageParser.h>
class CHsvDvbsGeneric_mAcq_Priv;
class CHsvDvbsGeneric_mAcq
{
public:
ProvidesInterface<IHsvPower>	iacqpow;

ProvidesInterface<IHsvDigitalAcquisition>	idataacq;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDigitalAcquisitionNotify>	iacqN;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvDigitalScanData>	isrtdata;
RequiresInterface<IHsvDigitalScanData>	isvcscandata;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat3;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvDigitalAcquisition>	dataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvPackageParser>	ipackage;
public:
CHsvDvbsGeneric_mAcq();
virtual ~CHsvDvbsGeneric_mAcq();
private:
CHsvDvbsGeneric_mAcq_Priv	*m_priv;
};

#endif

