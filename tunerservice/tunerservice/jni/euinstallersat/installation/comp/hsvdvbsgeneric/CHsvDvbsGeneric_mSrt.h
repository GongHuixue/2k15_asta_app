#ifndef  _CHSVDVBSGENERIC_MSRT_H
#define  _CHSVDVBSGENERIC_MSRT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScanData.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSorting.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvStreamNotify.h>
class CHsvDvbsGeneric_mSrt_Priv;
class CHsvDvbsGeneric_mSrt
{
public:
ProvidesInterface<IHsvSatellitePackageInstallation>	isrt;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	isrtAcqN;

ProvidesInterface<IHsvSdmControlNotifyEx>	isrtctrlN;

ProvidesInterface<IHsvDigitalScanData>	isrtdata;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	isrtplfApidvbsN;

ProvidesInterface<IHsvPower>	isrtpow;

ProvidesInterface<IHsvStreamNotify>	isrtstrapiN;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IHsvSorting>	isort;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat3;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbsGeneric_mSrt();
virtual ~CHsvDvbsGeneric_mSrt();
private:
CHsvDvbsGeneric_mSrt_Priv	*m_priv;
};

#endif

