#ifndef  _CHSVEUROPEINSTALLATION_M_H
#define  _CHSVEUROPEINSTALLATION_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciData.h>
#include <ITvColorDecode2NotifyEx.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvInstallationNotify.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvAnalogInstallationNotify.h>
#include <IHsvAltFrequencyScannerNotify.h>
#include <IHsvPresetImplicitInstall.h>
#include <IHsvPower.h>
#include <IHsvLastActivity.h>
#include <IHsvAciInstallationSubNotify.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IHsvAciDisplayNotify.h>
#include <IHsvInstallation2.h>
#include <IHsvTxtResetNotify.h>
#include <IHsvSortNotify.h>
#include <IHsvSourceSetupNotify.h>
#include <IHsvStreamNotify.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IEnable.h>
#include <IHsvAltFrequencyIterator.h>
#include <IHsvDigitalScan.h>
#include <IHsvAnalogSettings.h>
#include <IHsvAnalogInstallation.h>
#include <IHsvCamPresetSort.h>
#include <IHsvConflicts.h>
#include <IHsvLastActivityNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortRoute.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramDataControl3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiDesignatorId.h>
#include <IPlfApiErrorIds.h>
#include <IPlfApiSourceId.h>
#include <IPumpExSub.h>
#include <ISvcPowerStateControlEx.h>
#include <IRealTimeKernel.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSourceSetup.h>
#include <IHsvStream.h>
#include <IHsvInstallationSystemControl.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvTcSystemSettingsEx.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvSdmControl2.h>
#include <IPlfApiVbi.h>
#include <IPlfProxy.h>
#include <IPlfProxyNotify.h>

class CHsvEuropeInstallation_m_Priv;
class CHsvEuropeInstallation_m
{
public:
ProvidesInterface<IHsvAciData>	acidat;

ProvidesInterface<ITvColorDecode2NotifyEx>	colN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvInstallationDivSupport>	divsupp;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;
ProvidesInterface<IHsvInstallationNotify>	hsvdvbcamins_insN;

ProvidesInterface<IHsvInstallationNotify>	hsvdvbcins_insN;

ProvidesInterface<IHsvInstallationNotify>	hsvdvbtins_insN;

ProvidesInterface<IHsvDigitalScanNotify>	hsvdvbtmpegins_digscanN;

ProvidesInterface<IHsvInstallationNotify>	hsvdvbtmpegins_insN;

ProvidesInterface<IHsvAnalogInstallationNotify>	hsvprins_prinsN;

ProvidesInterface<IHsvInstallationNotify>	hsvziggoins_insN;

ProvidesInterface<IHsvInstallationNotify>	hsvcanaldigitalins_insN;

ProvidesInterface<IHsvAltFrequencyScannerNotify>	iafscanN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ictrlN;

ProvidesInterface<IHsvPresetImplicitInstall>	implins;

ProvidesInterface<IHsvPower>	impow;

ProvidesInterface<IHsvLastActivity>	instla;

ProvidesInterface<IHsvAciInstallationSubNotify>	ipgaciN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	isyssetN;

ProvidesInterface<IHsvAciDisplayNotify>	pacidsN;

ProvidesInterface<IHsvInstallation2>	pins;

ProvidesInterface<IHsvTxtResetNotify>	resetN;

ProvidesInterface<IHsvSortNotify>	sortN;

ProvidesInterface<IHsvSourceSetupNotify>	srcstpN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IPlfProxyNotify>	plfProxyN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvSdmControlNotifyEx>	cctrlN;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvStreamNotify>	cstrapiN;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbcamins_dataacq;
RequiresInterface<IHsvDVBSettings>hsvdvbcamins_dvbset;
RequiresInterface<IEnable>	hsvdvbcamins_ena;
RequiresInterface<IHsvFrontEndApiNotify>	hsvdvbcamins_feapiN;
RequiresInterface<IHsvDigitalScan>	hsvdvbcamins_ins;
RequiresInterface<IHsvStreamNotify>	hsvdvbcamins_strapiN;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbcins_digacq;
RequiresInterface<IHsvDVBSettings>	hsvdvbcins_dvbset;
RequiresInterface<IEnable>	hsvdvbcins_ena;
RequiresInterface<IHsvFrontEndApiNotify>	hsvdvbcins_feapiN;
RequiresInterface<IHsvInstallation2>	hsvdvbcins_ins;
RequiresInterface<IHsvSystemSettingsNotifyEx>	hsvdvbcins_syssetN;
RequiresInterface<IHsvAltFrequencyIterator>	hsvdvbtins_afitr;
RequiresInterface<IHsvInstallationNotify>	hsvdvbtins_cntryinsN;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbtins_digacq;
RequiresInterface<IHsvDVBSettings>	hsvdvbtins_dvbset;
RequiresInterface<IHsvDigitalScan>	hsvdvbtins_dvbt;
RequiresInterface<IEnable>	hsvdvbtins_ena;
RequiresInterface<IHsvFrontEndApiNotify>	hsvdvbtins_feapiN;
RequiresInterface<IHsvSystemSettingsNotifyEx>	hsvdvbtins_syssetN;
RequiresInterface<IHsvSystemSettingsNotifyEx>	hsvdvbtins_bcksyssetN;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbtmpegins_digacq;
RequiresInterface<IHsvDigitalScan>	hsvdvbtmpegins_digscan;
RequiresInterface<IEnable>	hsvdvbtmpegins_ena;
RequiresInterface<IHsvFrontEndApiNotify>	hsvdvbtmpegins_feapiN;
RequiresInterface<IHsvAciData>	hsvprins_acidat;
RequiresInterface<IHsvAnalogSettings>	hsvprins_anaset;
RequiresInterface<ITvColorDecode2NotifyEx>	hsvprins_colN;
RequiresInterface<IHsvFrontEndApiNotify>	hsvprins_feapiN;
RequiresInterface<IHsvPresetImplicitInstall>	hsvprins_implins;
RequiresInterface<IHsvAciDisplayNotify>	hsvprins_pacidsN;
RequiresInterface<IHsvAciInstallationSubNotify>	hsvprins_pgaciN;
RequiresInterface<IHsvPower>	hsvprins_pow;
RequiresInterface<IHsvAnalogInstallation>	hsvprins_prins;
RequiresInterface<IHsvTxtResetNotify>	hsvprins_resetN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvziggoins_ctrlN;
RequiresInterface<IHsvDigitalAcquisition>	hsvziggoins_dataacq;
RequiresInterface<IEnable>	hsvziggoins_ena;
RequiresInterface<IHsvFrontEndApiNotify>	hsvziggoins_feapiN;
RequiresInterface<IHsvDigitalScan>	hsvziggoins_ins;
RequiresInterface<IHsvSortNotify>	hsvziggoins_sortN;
RequiresInterface<IHsvStreamNotify>	hsvziggoins_strapiN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvcanaldigitalins_ctrlN;
RequiresInterface<IHsvDigitalAcquisition>	hsvcanaldigitalins_dataacq;
RequiresInterface<IEnable>	hsvcanaldigitalins_ena;
RequiresInterface<IHsvFrontEndApiNotify>	hsvcanaldigitalins_feapiN;
RequiresInterface<IHsvDigitalScan>	hsvcanaldigitalins_ins;
RequiresInterface<IHsvSortNotify>	hsvcanaldigitalins_sortN;
RequiresInterface<IHsvStreamNotify>	hsvcanaldigitalins_strapiN;
RequiresInterface<IHsvCamPresetSort>	icamsort;
RequiresInterface<IHsvConflicts>	iconf;
RequiresInterface<IHsvConflicts>	idbookconf;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationNotify>	pginsN;
RequiresInterface<IHsvLastActivityNotify>	instlaN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvHybridPresetSort>	isort;
RequiresInterface<IHsvSortRoute>	isortroute;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IHsvStreamNotify>	mpegstrapiN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDataControl3>	pgctl;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiDesignatorId>	plfdesigid;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPlfApiSourceId>	plfsrcid;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<ISvcPowerStateControlEx>	powctlx;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvSourceSetup>	srcstp;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvInstallationSystemControl>	sysctl;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvTcSystemSettingsEx>	syssetx;
RequiresInterface<IHsvSdmControlNotifyEx>	tctrlN;
RequiresInterface<IHsvStreamNotify>	tstrapiN;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IPlfApiVbi>		plfvbi;
RequiresInterface<IEnable>			dcu;
RequiresInterface<IPlfProxy>		plfproxy;
public:
CHsvEuropeInstallation_m();
virtual ~CHsvEuropeInstallation_m();
private:
CHsvEuropeInstallation_m_Priv	*m_priv;
};

#endif

