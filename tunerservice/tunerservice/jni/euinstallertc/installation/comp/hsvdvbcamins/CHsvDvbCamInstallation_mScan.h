#ifndef  _CHSVDVBCAMINSTALLATION_MSCAN_H
#define  _CHSVDVBCAMINSTALLATION_MSCAN_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvCamScanHelper.h>
#include <IHsvDigitalScan.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSdmEnable.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <ICesOperatorProfile.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvDVBSettings.h>
class CHsvDvbCamInstallation_mScan_Priv;
class CHsvDvbCamInstallation_mScan
{
public:
ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvCamScanHelper>	icamhelper;
ProvidesInterface<IHsvDigitalScan>	iins;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvCamScanHelper>	camScanparser;
RequiresInterface<IHsvSdmEnable>	camena;
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvCamScanHelper>	camacqhelper;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvPower>	isetpow;
public:
CHsvDvbCamInstallation_mScan();
virtual ~CHsvDvbCamInstallation_mScan();
private:
CHsvDvbCamInstallation_mScan_Priv	*m_priv;
};

#endif

