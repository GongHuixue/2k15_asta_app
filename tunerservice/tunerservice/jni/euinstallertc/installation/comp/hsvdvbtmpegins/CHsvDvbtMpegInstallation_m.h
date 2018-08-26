#ifndef  _CHSVDVBTMPEGINSTALLATION_M_H
#define  _CHSVDVBTMPEGINSTALLATION_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotify.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSdmControl2.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbtMpegInstallation_m_Priv;
class CHsvDvbtMpegInstallation_m
{
public:
ProvidesInterface<IHsvSdmControlNotify>	ctrlN;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	idigscan;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvDigitalScanNotify>	digscanN;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvDigitalAcquisition>	idigacq;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbtMpegInstallation_m();
virtual ~CHsvDvbtMpegInstallation_m();
private:
CHsvDvbtMpegInstallation_m_Priv	*m_priv;
};

#endif

