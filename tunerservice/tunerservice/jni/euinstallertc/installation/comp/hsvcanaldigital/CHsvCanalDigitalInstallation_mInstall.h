#ifndef  _CHSVCANALDIGITALINSTALLATION_MINSTALL_H
#define  _CHSVCANALDIGITALINSTALLATION_MINSTALL_H 

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
class CHsvCanalDigitalInstallation_mInstall_Priv;
class CHsvCanalDigitalInstallation_mInstall
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
CHsvCanalDigitalInstallation_mInstall();
virtual ~CHsvCanalDigitalInstallation_mInstall();
private:
CHsvCanalDigitalInstallation_mInstall_Priv	*m_priv;
};

#endif

