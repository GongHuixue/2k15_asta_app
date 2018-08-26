#ifndef  _CHSVDVBCINSTALLATION_MPRESCAN_H
#define  _CHSVDVBCINSTALLATION_MPRESCAN_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IEnable.h>
#include <IHsvDigitalScan.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvInstallationNotify.h>
#include <IHsvDigitalScanNotify.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbCInstallation_mprescan_Priv;
class CHsvDvbCInstallation_mprescan
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ipctrlN;

ProvidesInterface<IEnable>	ipena;

ProvidesInterface<IHsvDigitalScan>	iprescan;

ProvidesInterface<IHsvFrontEndApiNotify>	iprescanfeN;

ProvidesInterface<IHsvPower>	iprescanpow;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvDigitalScanNotify>	iprescanN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbCInstallation_mprescan();
virtual ~CHsvDvbCInstallation_mprescan();
private:
CHsvDvbCInstallation_mprescan_Priv	*m_priv;
};

#endif

