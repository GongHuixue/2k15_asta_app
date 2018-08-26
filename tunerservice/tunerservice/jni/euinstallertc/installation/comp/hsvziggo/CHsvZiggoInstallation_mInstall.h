#ifndef  _CHSVZIGGOINSTALLATION_MINSTALL_H
#define  _CHSVZIGGOINSTALLATION_MINSTALL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalScan.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvSdmControl2.h>
#include <IHsvDVBSettings.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
class CHsvZiggoInstallation_mInstall_Priv;
class CHsvZiggoInstallation_mInstall
{
public:
ProvidesInterface<IHsvDigitalScan>	iins;

ProvidesInterface<IHsvSdmControlNotifyEx>	iinsctrlN;

ProvidesInterface<IHsvFrontEndApiNotify>	iinsfeapiN;

ProvidesInterface<IHsvPower>	iinspow;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvDVBSettings>	dvbset;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalScan>	ibckg;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvZiggoInstallation_mInstall();
virtual ~CHsvZiggoInstallation_mInstall();
private:
CHsvZiggoInstallation_mInstall_Priv	*m_priv;
};

#endif

