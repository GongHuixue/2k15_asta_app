#ifndef  _CHSVDVBSGENERIC_M_H
#define  _CHSVDVBSGENERIC_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvStreamNotify.h>
class CHsvDvbsGeneric_m_Priv;
class CHsvDvbsGeneric_m
{
public:
ProvidesInterface<IHsvSatelliteBackgroundInstallation>	bckInstall;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	iacqN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;
RequiresInterface<IHsvPower>	ibckgndpow;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvDigitalAcquisitionNotify>	iscanAcqN;
RequiresInterface<IHsvPower>	isortpow;
RequiresInterface<IHsvSatellitePackageInstallation>	isrt;
RequiresInterface<IHsvDigitalAcquisitionNotify>	isrtAcqN;
RequiresInterface<IHsvSdmControlNotifyEx>	isrtctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	isrtplfApidvbsN;
RequiresInterface<IHsvPower>	isrtpow;
RequiresInterface<IHsvSatellitePackageInstallation>	isvcscan;
RequiresInterface<IHsvSdmControlNotifyEx>	isvcscanctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	isvcscanplfApidvbsN;
RequiresInterface<IHsvPower>	isvcscanpow;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvStreamNotify>	isrtstrapiN;
RequiresInterface<IHsvStreamNotify>	ibckgndstrapiN;
public:
CHsvDvbsGeneric_m();
virtual ~CHsvDvbsGeneric_m();
private:
CHsvDvbsGeneric_m_Priv	*m_priv;
};

#endif

