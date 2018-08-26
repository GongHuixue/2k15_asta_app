#ifndef  _CHSVCANALDIGITALINSTALLATION_MROUTE_H
#define  _CHSVCANALDIGITALINSTALLATION_MROUTE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvPower.h>
#include <IHsvInstallation2.h>
class CHsvCanalDigitalInstallation_mRoute_Priv;
class CHsvCanalDigitalInstallation_mRoute
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	ins;

ProvidesInterface<IHsvDigitalScan>	istub;

ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvDigitalScan>	ibckg;
RequiresInterface<IHsvSdmControlNotifyEx>	ibckgctrlN;
RequiresInterface<IHsvPower>	ibckgpow;
RequiresInterface<IHsvDigitalScan>	idtr;
RequiresInterface<IHsvFrontEndApiNotify>	idtrfeapiN;
RequiresInterface<IHsvPower>	idtrpow;
RequiresInterface<IHsvDigitalScan>	iins;
RequiresInterface<IHsvSdmControlNotifyEx>	iinsctrlN;
RequiresInterface<IHsvFrontEndApiNotify>	iinsfeapiN;
RequiresInterface<IHsvPower>	iinspow;
RequiresInterface<IHsvDigitalScan>	ipreins;
RequiresInterface<IHsvSdmControlNotifyEx>	ipreinsctrlN;
RequiresInterface<IHsvFrontEndApiNotify>	ipreinsfeapiN;
RequiresInterface<IHsvPower>	ipreinspow;
RequiresInterface<IHsvInstallation2>	rins;
public:
CHsvCanalDigitalInstallation_mRoute();
virtual ~CHsvCanalDigitalInstallation_mRoute();
private:
CHsvCanalDigitalInstallation_mRoute_Priv	*m_priv;
};

#endif

