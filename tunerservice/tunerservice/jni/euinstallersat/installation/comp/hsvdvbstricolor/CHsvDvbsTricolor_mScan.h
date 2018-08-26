#ifndef  _CHSVDVBSTRICOLOR_MSCAN_H
#define  _CHSVDVBSTRICOLOR_MSCAN_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScanData.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvInstallationSigStrength.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvStream.h>
#include <IHsvSatelliteSettings.h>

class CHsvDvbsTricolor_mScan_Priv;
class CHsvDvbsTricolor_mScan
{
public:
ProvidesInterface<IHsvDigitalAcquisitionNotify>	idataacqN;
ProvidesInterface<IHsvSatellitePackageInstallation>	isvcscan;
ProvidesInterface<IHsvSdmControlNotifyEx>	isvcscanctrlN;
ProvidesInterface<IHsvDigitalScanData>	isvcscandata;
ProvidesInterface<IHsvPower>	isvcscanpow;
ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvPower>	ibckgndpow;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IHsvPower>	isortpow;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvSatelliteUtility>	util;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatelliteSettings> itricolorsettings;

public:
CHsvDvbsTricolor_mScan();
virtual ~CHsvDvbsTricolor_mScan();
private:
CHsvDvbsTricolor_mScan_Priv	*m_priv;
};

#endif

