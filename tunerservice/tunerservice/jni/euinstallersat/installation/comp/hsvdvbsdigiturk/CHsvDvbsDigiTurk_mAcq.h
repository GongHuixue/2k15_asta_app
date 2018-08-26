#ifndef  _CHSVDVBSDIGITURK_MACQ_H
#define  _CHSVDVBSDIGITURK_MACQ_H 

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
#include <IHsvDigitalScanSdsdData.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvStream.h>
#include <IHsvSatelliteUtility.h>
class CHsvDvbsDigiTurk_mAcq_Priv;
class CHsvDvbsDigiTurk_mAcq
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
RequiresInterface<IHsvDigitalScanData>	iscandata;
RequiresInterface<IHsvDigitalScanSdsdData>	isdsddata;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatelliteUtility>	util;
public:
CHsvDvbsDigiTurk_mAcq();
virtual ~CHsvDvbsDigiTurk_mAcq();
private:
CHsvDvbsDigiTurk_mAcq_Priv	*m_priv;
};

#endif

