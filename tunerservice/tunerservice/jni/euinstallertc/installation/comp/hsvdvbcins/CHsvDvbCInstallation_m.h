#ifndef  _CHSVDVBCINSTALLATION_M_H
#define  _CHSVDVBCINSTALLATION_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvInstallation2.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvDigitalScan.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
class CHsvDvbCInstallation_m_Priv;
class CHsvDvbCInstallation_m
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScanNotify>	ifullN;

ProvidesInterface<IHsvDigitalScanNotify>	igridN;

ProvidesInterface<IHsvInstallation2>	ins;

ProvidesInterface<IHsvDigitalScanNotify>	iprescanN;

ProvidesInterface<IHsvDigitalScanNotify>	iquickN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvStreamNotify>	iacqstrapiN;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvSdmControlNotifyEx>	ifctrlN;
RequiresInterface<IEnable>	ifena;
RequiresInterface<IHsvStreamNotify>	ifstrapiN;
RequiresInterface<IHsvDigitalScan>	ifull;
RequiresInterface<IHsvFrontEndApiNotify>	ifullfeN;
RequiresInterface<IHsvPower>	ifullpow;
RequiresInterface<IHsvSdmControlNotifyEx>	igctrlN;
RequiresInterface<IEnable>	igena;
RequiresInterface<IHsvDigitalScan>	igrid;
RequiresInterface<IHsvFrontEndApiNotify>	igridfeN;
RequiresInterface<IHsvPower>	igridpow;
RequiresInterface<IHsvStreamNotify>	igstrapiN;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvSdmControlNotifyEx>	ipctrlN;
RequiresInterface<IEnable>	ipena;
RequiresInterface<IHsvDigitalScan>	iprescan;
RequiresInterface<IHsvFrontEndApiNotify>	iprescanfeN;
RequiresInterface<IHsvPower>	iprescanpow;
RequiresInterface<IHsvSdmControlNotifyEx>	iqctrlN;
RequiresInterface<IEnable>	iqena;
RequiresInterface<IHsvStreamNotify>	iqstrapiN;
RequiresInterface<IHsvDigitalScan>	iquick;
RequiresInterface<IHsvFrontEndApiNotify>	iquickfeN;
RequiresInterface<IHsvPower>	iquickpow;
RequiresInterface<IHsvPower>	isetpow;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
public:
CHsvDvbCInstallation_m();
virtual ~CHsvDvbCInstallation_m();
private:
CHsvDvbCInstallation_m_Priv	*m_priv;
};

#endif

