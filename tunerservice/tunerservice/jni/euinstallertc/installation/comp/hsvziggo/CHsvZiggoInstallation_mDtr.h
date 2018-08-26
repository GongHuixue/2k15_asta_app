#ifndef  _CHSVZIGGOINSTALLATION_MDTR_H
#define  _CHSVZIGGOINSTALLATION_MDTR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalScan.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSdmControl2.h>
class CHsvZiggoInstallation_mDtr_Priv;
class CHsvZiggoInstallation_mDtr
{
public:
ProvidesInterface<IHsvDigitalScan>	idtr;

ProvidesInterface<IHsvFrontEndApiNotify>	idtrfeapiN;

ProvidesInterface<IHsvPower>	idtrpow;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvSdmControl2>	ctrl;
public:
CHsvZiggoInstallation_mDtr();
virtual ~CHsvZiggoInstallation_mDtr();
private:
CHsvZiggoInstallation_mDtr_Priv	*m_priv;
};

#endif

