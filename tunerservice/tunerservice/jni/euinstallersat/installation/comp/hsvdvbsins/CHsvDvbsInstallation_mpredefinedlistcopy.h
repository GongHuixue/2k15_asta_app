#ifndef  _CHSVDVBSINSTALLATION_MPREDEFINEDLISTCOPY_H
#define  _CHSVDVBSINSTALLATION_MPREDEFINEDLISTCOPY_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPredefinedListCopy.h>
#include <IHsvPower.h>
#include <IPlfApiStorageDeviceNotify.h>
#include <IPlfApiPhysDeviceNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
#include <IPlfApiStorageDevice.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <IPlfApiPhysDevice.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbsInstallation_mpredefinedlistcopy_Priv;
class CHsvDvbsInstallation_mpredefinedlistcopy
{
public:
ProvidesInterface<IHsvPredefinedListCopy>	ipredefcopy;

ProvidesInterface<IHsvPower>	ipredefpow;

ProvidesInterface<IPlfApiStorageDeviceNotify>	recdevN;

ProvidesInterface<IPlfApiPhysDeviceNotify>	usbdevexN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPlfApiStorageDevice>	recdev;
RequiresInterface<ICeIsTpHostRtk2>	tprtk;
RequiresInterface<IPlfApiPhysDevice>	usbms;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbsInstallation_mpredefinedlistcopy();
virtual ~CHsvDvbsInstallation_mpredefinedlistcopy();
private:
CHsvDvbsInstallation_mpredefinedlistcopy_Priv	*m_priv;
};

#endif

