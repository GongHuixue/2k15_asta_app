#ifndef  _CHSVDVBTINSTALLATION_MROUTE_H
#define  _CHSVDVBTINSTALLATION_MROUTE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvDigitalScanRoute.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDVBSettings.h>
#include <IHsvInstallation2.h>
class CHsvDvbTInstallation_mRoute_Priv;
class CHsvDvbTInstallation_mRoute
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	idvbt;

ProvidesInterface<IHsvDigitalScanRoute>	iroute;

ProvidesInterface<IHsvDigitalScan>	istub;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSdmControlNotifyEx>	ibctrlN;
RequiresInterface<IHsvPower>	ibpow;
RequiresInterface<IHsvStreamNotify>	ibstrapiN;
RequiresInterface<IHsvSdmControlNotifyEx>	icctrlN;
RequiresInterface<IHsvPower>	icntrypow;
RequiresInterface<IHsvStreamNotify>	icntrystrapiN;
RequiresInterface<IHsvPower>	idatapow;
RequiresInterface<IHsvSdmControlNotifyEx>	idctrlN;
RequiresInterface<IHsvDigitalScan>	idtr;
RequiresInterface<IHsvFrontEndApiNotify>	idtrfeN;
RequiresInterface<IHsvPower>	idtrpow;
RequiresInterface<IHsvStreamNotify>	idstrapiN;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvSdmControlNotifyEx>	ifctrlN;
RequiresInterface<IHsvDigitalScan>	ifull;
RequiresInterface<IHsvFrontEndApiNotify>	ifullfeN;
RequiresInterface<IHsvPower>	ifullpow;
RequiresInterface<IHsvSdmControlNotifyEx>	iqctrlN;
RequiresInterface<IHsvDigitalScan>	iquick;
RequiresInterface<IHsvFrontEndApiNotify>	iquickfeN;
RequiresInterface<IHsvPower>	iquickpow;
RequiresInterface<IHsvPower>	isetpow;
RequiresInterface<IHsvInstallation2>	rins;
public:
CHsvDvbTInstallation_mRoute();
virtual ~CHsvDvbTInstallation_mRoute();
private:
CHsvDvbTInstallation_mRoute_Priv	*m_priv;
};

#endif

