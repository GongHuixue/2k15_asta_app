#ifndef  _CHSVDVBSGENERIC_MBCKGND_H
#define  _CHSVDVBSGENERIC_MBCKGND_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallation.h>
#include <IPumpEngine.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
class CHsvDvbsGeneric_mBckgnd_Priv;
class CHsvDvbsGeneric_mBckgnd
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;

ProvidesInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;

ProvidesInterface<IHsvPower>	ibckgndpow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
public:
CHsvDvbsGeneric_mBckgnd();
virtual ~CHsvDvbsGeneric_mBckgnd();
private:
CHsvDvbsGeneric_mBckgnd_Priv	*m_priv;
};

#endif

