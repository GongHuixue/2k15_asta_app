#ifndef  _CS2INSTALLERMW_H
#define  _CS2INSTALLERMW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CS2InstallerMw_mpow.h>
#include <CHsvDvbStreamingDataManager.h>
#include <CHsvDvbsInstallation.h>
#include <CHsvSatelliteFrontEnd.h>
#include <CHsvUtil.h>
#include <CHsvSatProgramData.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDemuxNotify.h>
#include <IPlfApiTuningNotify.h>
#include <IHsvPower.h>
#include <IProdApiClockEx.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMediaControl.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvProgramSelection2.h>
#include <IPlfApiDvbsTuning.h>
#include <ITvPlatformResource.h>
#include <IPlfApiTuning.h>
#include <IPumpExSub.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiStorageDevice.h>
#include <IRealTimeKernel.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvDemuxSectionFilter2.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvSatSystemSettings.h>
#include <ICeIsTpHostRtk2.h>
#include <IPlfApiPhysDevice.h>
#include <IHsvUtilDiv.h>
#include <ISvcVideoControl3.h>
#include <IHsvWindowDestinationMap.h>
#include <ICesOperatorProfile.h>
#include <IHsvSystemSettingsNotify.h>

class CS2InstallerMw
{
public:
virtual ~CS2InstallerMw(){}

//Contained Modules
private:
CS2InstallerMw_mpow mpow;
//Contained Components
private:
CHsvDvbStreamingDataManager hsvdvbsdm;
CHsvDvbsInstallation hsvdvbsins;
CHsvSatelliteFrontEnd hsvsatfe;
CHsvUtil hsvutil;
CHsvSatProgramData sathsvpgdat;
public:
ProvidesInterface<IHsvSatelliteSettings>	dvbset;

ProvidesInterface<IHsvSatelliteInstallation>	ins;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	pdmxsecfN;

ProvidesInterface<IHsvDemuxNotify>	phsvdmxN;

ProvidesInterface<IPlfApiTuningNotify>	plfapidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<ICesCipCAMStatusNotify>	cipStatusN;

ProvidesInterface<IHsvSystemSettingsNotify> sysnotifyN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<ISvcAudioControl4ExEx>	actl3;
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvLanguageIds2>	lngids;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IProdApiSystemStateObserverExExExEx>	observer;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvChannelLibReturnCodes>	pgdaterr;
RequiresInterface<IHsvChanlibPosixLight>	pgdatrtk;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPlfApiDvbsTuning>	plfdvbs;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPlfApiTuning>	plftune;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IPlfApiStorageDevice>	recdev;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvDemuxSectionFilter2>	secf;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<ICeIsTpHostRtk2>	tprtk;
RequiresInterface<IPlfApiPhysDevice>	usbms;
RequiresInterface<IHsvUtilDiv>	utildiv;
RequiresInterface<ISvcVideoControl3>	vctl;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<ICesCipCAMStatus>	cipStatus;
private:
Pumpdefines(CS2InstallerMw);
DEMUX_DEFINES(CS2InstallerMw,secf);
TpRtkDefines(CS2InstallerMw);

public:
CS2InstallerMw()
{
pow	=	mpow.pow;
mpow.hsvdvbsins_pow	=	hsvdvbsins.pow;
mpow.hsvsatfe_pow	=	hsvsatfe.pow;
mpow.hsvdvbsdm_pow	=	hsvdvbsdm.pow;
mpow.sathsvpgdat_pow	=	sathsvpgdat.pow;
ins	=	hsvdvbsins.ins;
hsvdvbsins.satfeapi	=	hsvsatfe.satfrontend;
plfapidvbsN	=	hsvsatfe.plfapidvbsN;
hsvdvbsins.ctrl	=	hsvdvbsdm.ctrl;
hsvdvbsins.strapi	=	hsvdvbsdm.strapi;
hsvdvbsins.strmfltr	=	hsvdvbsdm.strmfltr;
hsvdvbsins.pgdat	=	sathsvpgdat.pgdat3;
hsvdvbsins.pgdb	=	sathsvpgdat.pgdb;
hsvdvbsins.pgdbconst	=	sathsvpgdat.pgdbconst;
hsvdvbsins.pmp	=	pmp;
hsvdvbsins.pen	=	pen;
hsvdvbsins.Timerclk	=	Timerclk;
hsvdvbsins.rtk	=	rtk;
hsvdvbsins.err	=	err;
hsvdvbsins.apperr	=	apperr;
hsvdvbsins.insN	=	insN;
hsvdvbsins.eurdiv	=	eurdiv;
hsvdvbsins.s2div	=	s2div;
hsvdvbsins.sysset	=	sysset;
hsvdvbsins.cids	=	cids;
hsvdvbsins.mctl	=	mctl;
hsvdvbsins.lngids	=	lngids;
hsvdvbsins.wnddest	=	wnddest;
hsvdvbsins.apsysset	=	apsysset;
hsvdvbsins.plfres	=	plfres;
hsvdvbsins.vssm	=	vssm;
hsvdvbsins.qssm	=	qssm;
hsvdvbsins.charsetutil	=	hsvutil.charsetutil;
hsvdvbsins.vctl	=	vctl;
hsvdvbsins.actl3	=	actl3;
hsvdvbsins.pgsel	=	pgsel;
hsvdvbsins.observer	=	observer;
hsvdvbsins.recdev	=	recdev;
hsvdvbsins.usbms	=	usbms;
hsvdvbsins.tprtk	=	tprtk;
hsvdvbsins.opins	= 	opins;
hsvdvbsins.cipStatus = 	cipStatus;
hsvdvbsdm.ctrlN	=	hsvdvbsins.ctrlN;
hsvdvbsdm.strapiN	=	hsvdvbsins.strapiN;
hsvdvbsdm.pakgins	=	hsvdvbsins.pakgins;
hsvdvbsdm.ins	=	hsvdvbsins.ins;
hsvdvbsdm.pmp	=	pmp;
hsvdvbsdm.pen	=	pen;
hsvdvbsdm.rtk	=	rtk;
hsvdvbsdm.cids	=	cids;
hsvdvbsdm.sysset	=	sysset;
hsvdvbsdm.charsetutil	=	hsvutil.charsetutil;
hsvdvbsdm.eurdiv	=	eurdiv;
hsvdvbsdm.ctrlpen	=	ctrlpen;
hsvdvbsdm.srtdb2	=	srtdb2;
hsvdvbsdm.srtdbids	=	srtdbids;
hsvdvbsdm.dvbsrtdbids	=	dvbsrtdbids;
hsvdvbsdm.div	=	div;
hsvdvbsdm.charsetutil2	=	hsvutil.charsetutil2;
hsvdvbsdm.secf	=	secf;
hsvdvbsdm.dmxena	=	dmxena;
phsvdmxN	=	hsvdvbsdm.phsvdmxN;
pdmxsecfN	=	hsvdvbsdm.pdmxsecfN;
hsvsatfe.plfdvbs	=	plfdvbs;
hsvsatfe.plftune	=	plftune;
hsvsatfe.err	=	err;
hsvsatfe.wnddest	=	wnddest;
hsvsatfe.pmp	=	pmp;
hsvsatfe.pen	=	pen;
hsvsatfe.tprtk	=	tprtk;
hsvsatfe.hsvsatsettings	=	hsvdvbsins.dvbset;
dvbset	=	hsvdvbsins.dvbset;
hsvsatfe.satfrontendNotify	=	hsvdvbsins.satfeapiN;
sathsvpgdat.rtk	=	pgdatrtk;
sathsvpgdat.err	=	pgdaterr;
sathsvpgdat.sync	=	sync;
sathsvpgdat.insN=insN;
hsvutil.div	=	utildiv;
hsvutil.cids	=	cids;
hsvutil.sysset	=	sysset;
sathsvpgdat.srtdb2 = srtdb2;
sathsvpgdat.srtdbids = dvbsrtdbids;
opinsN	=  hsvdvbsins.opinsN;
cipStatusN	=  hsvdvbsins.cipStatusN;
hsvdvbsins.camdataparser = hsvdvbsdm.camdataparser;
hsvdvbsins.camnitena = hsvdvbsdm.camnitena;
sysnotifyN = hsvdvbsins.sysnotifyN;
hsvdvbsdm.itricolorsettings = hsvdvbsins.itricolorsettings;
}

};

#endif

