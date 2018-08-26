#ifndef  _CHSVDVBTINSTALLATION_MFULL_H
#define  _CHSVDVBTINSTALLATION_MFULL_H 

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
#include <IHsvDVBSettings.h>
#include <IHsvSdmControlNotify.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvStream.h>
class CHsvDvbTInstallation_mFull_Priv;
class CHsvDvbTInstallation_mFull
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ifctrlN;

ProvidesInterface<IHsvDigitalScan>	ifull;

ProvidesInterface<IHsvFrontEndApiNotify>	ifullfeN;

ProvidesInterface<IHsvPower>	ifullpow;

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
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvSdmControlNotify>	idvbtqctrlN;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvDigitalScan>	istub;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvStream>	strapi;
public:
CHsvDvbTInstallation_mFull();
virtual ~CHsvDvbTInstallation_mFull();
private:
CHsvDvbTInstallation_mFull_Priv	*m_priv;
};

#endif

