#ifndef  _CHSVDVBTINSTALLATION_MDTR_H
#define  _CHSVDVBTINSTALLATION_MDTR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScan.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSdmControlNotify.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvStreamNotify.h>
class CHsvDvbTInstallation_mDtr_Priv;
class CHsvDvbTInstallation_mDtr
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	idctrlN;

ProvidesInterface<IHsvDigitalScan>	idtr;

ProvidesInterface<IHsvFrontEndApiNotify>	idtrfeN;

ProvidesInterface<IHsvPower>	idtrpow;

ProvidesInterface<IHsvStreamNotify> idstrapiN;

//Required interfaces
public:
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvDigitalScanNotify>	digscanN;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSdmControlNotify>	idvbtqctrlN;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvDigitalScan>	istub;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbTInstallation_mDtr();
virtual ~CHsvDvbTInstallation_mDtr();
private:
CHsvDvbTInstallation_mDtr_Priv	*m_priv;
};

#endif

