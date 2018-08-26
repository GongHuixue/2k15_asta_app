#ifndef  _CHSVDVBSINSTALLATION_H
#define  _CHSVDVBSINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsInstallation_m.h>
#include <CHsvDvbsInstallation_mminiprescan.h>
#include <CHsvDvbsInstallation_mpackageparser.h>
#include <CHsvDvbsInstallation_mpow.h>
#include <CHsvDvbsInstallation_mpredefinedlistcopy.h>
#include <CHsvDvbsInstallation_mprescan.h>
#include <CHsvDvbsInstallation_mprescanparser.h>
#include <CHsvDvbsInstallation_mremovesat.h>
#include <CHsvDvbsInstallation_mroute.h>
#include <CHsvDvbsInstallation_msettings.h>
#include <CHsvDvbsInstallation_msigstr.h>
#include <CHsvDvbsInstallation_mutil.h>
#include <CHsvDvbsInstallation_msatipprescan.h>
#include <CHsvDvbsOpProfile.h>
#include <CHsvDvbsCanal.h>
#include <CHsvDvbsDigiTurk.h>
#include <CHsvDvbsFransat.h>
#include <CHsvDvbsGeneric.h>
#include <CHsvDvbsM7.h>
#include <CHsvDvbsN.h>
#include <CHsvDvbsPol.h>
#include <CHsvDvbsRussia.h>
#include <CHsvDvbsFreesat.h>
#include <CHsvDvbsAstra.h>
#include <CHsvDvbsTricolor.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteInstallationRoute.h>
#include <IHsvSatellitePackageInstallation.h>
#include <ITvPlatformResourceNotify.h>
#include <IHsvPower.h>
#include <IPlfApiStorageDeviceNotify.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvStreamNotify.h>
#include <IHsvSystemSettingsNotify.h>
#include <IProdApiSystemStateObserverNotify.h>
#include <IPlfApiPhysDeviceNotify.h>
#include <IProdApiClockEx.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMediaControl.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiStorageDevice.h>
#include <IRealTimeKernel.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvSatSystemSettings.h>
#include <ICeIsTpHostRtk2.h>
#include <IPlfApiPhysDevice.h>
#include <ISvcVideoControl3.h>
#include <IHsvWindowDestinationMap.h>
#include <ICesOperatorProfile.h>
#include <IHsvCamDataParser.h>
#include <ICesCipCAMStatusNotify.h>
#include <ICesCipCAMStatus.h>
#include <IHsvPrescanParser.h>

class CHsvDvbsInstallation
{
public:
virtual ~CHsvDvbsInstallation(){}

//Contained Modules
private:
CHsvDvbsInstallation_m m;
CHsvDvbsInstallation_mminiprescan mminiprescan;
CHsvDvbsInstallation_mpackageparser mpackageparser;
CHsvDvbsInstallation_mpow mpow;
CHsvDvbsInstallation_mpredefinedlistcopy mpredefinedlistcopy;
CHsvDvbsInstallation_mprescan mprescan;
CHsvDvbsInstallation_mprescanparser mprescanparser;
CHsvDvbsInstallation_mremovesat mremovesat;
CHsvDvbsInstallation_mroute mroute;
CHsvDvbsInstallation_msettings msettings;
CHsvDvbsInstallation_msigstr msigstr;
CHsvDvbsInstallation_mutil mutil;
CHsvDvbsInstallation_msatipprescan msatipprescan;
//Contained Components
private:
CHsvDvbsOpProfile hsvdvbsopprofile;
CHsvDvbsCanal hsvdvbscanal;
CHsvDvbsDigiTurk hsvdvbsdigiturk;
CHsvDvbsFransat hsvdvbsfransat;
CHsvDvbsGeneric hsvdvbsgeneric;
CHsvDvbsM7 hsvdvbsm7;
CHsvDvbsN hsvdvbsn;
CHsvDvbsPol hsvdvbspol;
CHsvDvbsRussia hsvdvbsrussia;
CHsvDvbsFreesat hsvdvbsfreesat;
CHsvDvbsAstra hsvdvbsastra;
CHsvDvbsTricolor hsvdvbstricolor;

public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatelliteSettings>	dvbset;

ProvidesInterface<IHsvSatelliteInstallation>	ins;

ProvidesInterface<IHsvSatelliteInstallationRoute>	insroute;

ProvidesInterface<IHsvSatellitePackageInstallation>	pakgins;

ProvidesInterface<ITvPlatformResourceNotify>	plfresN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IPlfApiStorageDeviceNotify>	recdevN;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	satfeapiN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IHsvSystemSettingsNotify>	sysnotifyN;

ProvidesInterface<IProdApiSystemStateObserverNotify>	sysstateN;

ProvidesInterface<IPlfApiPhysDeviceNotify>	usbdevexN;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<ICesCipCAMStatusNotify>	cipStatusN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<ISvcAudioControl4ExEx>	actl3;
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvLanguageIds2>	lngids;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IProdApiSystemStateObserverExExExEx>	observer;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IPlfApiStorageDevice>	recdev;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<ICeIsTpHostRtk2>	tprtk;
RequiresInterface<IPlfApiPhysDevice>	usbms;
RequiresInterface<ISvcVideoControl3>	vctl;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<IHsvCamDataParser>	camdataparser;
RequiresInterface<IHsvSdmEnable>	camnitena;
RequiresInterface<ICesCipCAMStatus>	cipStatus;
RequiresInterface<IHsvSatelliteSettings> itricolorsettings;

private:
Pumpdefines(CHsvDvbsInstallation);
TpRtkDefines(CHsvDvbsInstallation);

public:
CHsvDvbsInstallation()
{
ins	=	m.pins;
hsvdvbsgeneric.satfeapi	=	satfeapi;
hsvdvbsgeneric.ctrl	=	ctrl;
hsvdvbsgeneric.pmp	=	pmp;
hsvdvbsgeneric.pen	=	pen;
hsvdvbsgeneric.Timerclk	=	Timerclk;
hsvdvbsgeneric.rtk	=	rtk;
hsvdvbsgeneric.err	=	err;
hsvdvbsgeneric.apperr	=	apperr;
hsvdvbsgeneric.strapi	=	strapi;
hsvdvbsgeneric.strmfltr	=	strmfltr;
hsvdvbsgeneric.pgdb	=	pgdb;
hsvdvbsgeneric.pgdbconst	=	pgdbconst;
hsvdvbsgeneric.insN	=	m.iinsN;
hsvdvbsgeneric.eurdiv	=	eurdiv;
hsvdvbsgeneric.s2div	=	s2div;
hsvdvbsgeneric.cids	=	cids;
hsvdvbsgeneric.mctl	=	mctl;
hsvdvbsgeneric.wnddest	=	wnddest;
hsvdvbsgeneric.apsysset	=	apsysset;
hsvdvbsgeneric.charsetutil	=	charsetutil;
hsvdvbsgeneric.dvbset	=	msettings.idvbset;
hsvdvbsgeneric.prescandata	=	mprescan.iprescandata;
hsvdvbsgeneric.packagepar	=	mpackageparser.ipackage;
hsvdvbsgeneric.sigstr	=	msigstr.isigstr;
hsvdvbsgeneric.insstate	=	m.pins;
hsvdvbsgeneric.iprescanparser	=	mprescanparser.iprescanparser;
hsvdvbsgeneric.iutil	=	mutil.iutil;
hsvdvbsgeneric.pgsel	=	pgsel;
hsvdvbsgeneric.pgdat3	=	pgdat;
hsvdvbsgeneric.plfres	=	plfres;
hsvdvbsgeneric.dataacq	= hsvdvbscanal.dataacq;
hsvdvbsm7.satfeapi	=	satfeapi;
hsvdvbsm7.ctrl	=	ctrl;
hsvdvbsm7.pmp	=	pmp;
hsvdvbsm7.pen	=	pen;
hsvdvbsm7.Timerclk	=	Timerclk;
hsvdvbsm7.err	=	err;
hsvdvbsm7.strapi	=	strapi;
hsvdvbsm7.pgdb	=	pgdb;
hsvdvbsm7.pgdbconst	=	pgdbconst;
hsvdvbsm7.insN	=	m.iinsN;
hsvdvbsm7.eurdiv	=	eurdiv;
hsvdvbsm7.sigstr	=	msigstr.isigstr;
hsvdvbsm7.insstate	=	m.pins;
hsvdvbsm7.iutil	=	mutil.iutil;
hsvdvbsm7.idvbset	=	msettings.idvbset;
hsvdvbsm7.iprescanparser	=	mprescanparser.iprescanparser;
hsvdvbsdigiturk.satfeapi	=	satfeapi;
hsvdvbsdigiturk.ctrl	=	ctrl;
hsvdvbsdigiturk.pmp	=	pmp;
hsvdvbsdigiturk.pen	=	pen;
hsvdvbsdigiturk.err	=	err;
hsvdvbsdigiturk.strapi	=	strapi;
hsvdvbsdigiturk.pgdb	=	pgdb;
hsvdvbsdigiturk.pgdbconst	=	pgdbconst;
hsvdvbsdigiturk.insN	=	m.iinsN;
hsvdvbsdigiturk.eurdiv	=	eurdiv;
hsvdvbsdigiturk.sigstr	=	msigstr.isigstr;
hsvdvbsdigiturk.insstate	=	m.pins;
hsvdvbsdigiturk.util	=	mutil.iutil;
hsvdvbsdigiturk.Timerclk	=	Timerclk;
hsvdvbscanal.satfeapi	=	satfeapi;
hsvdvbscanal.ctrl	=	ctrl;
hsvdvbscanal.pmp	=	pmp;
hsvdvbscanal.pen	=	pen;
hsvdvbscanal.err	=	err;
hsvdvbscanal.strapi	=	strapi;
hsvdvbscanal.pgdb	=	pgdb;
hsvdvbscanal.pgdbconst	=	pgdbconst;
hsvdvbscanal.insN	=	m.iinsN;
hsvdvbscanal.eurdiv	=	eurdiv;
hsvdvbscanal.sigstr	=	msigstr.isigstr;
hsvdvbscanal.insstate	=	m.pins;
hsvdvbscanal.sysset	=	sysset;
hsvdvbscanal.iutil	=	mutil.iutil;
hsvdvbscanal.Timerclk	=	Timerclk;
hsvdvbsn.satfeapi	=	satfeapi;
hsvdvbsn.ctrl	=	ctrl;
hsvdvbsn.pmp	=	pmp;
hsvdvbsn.pen	=	pen;
hsvdvbsn.err	=	err;
hsvdvbsn.strapi	=	strapi;
hsvdvbsn.pgdb	=	pgdb;
hsvdvbsn.pgdbconst	=	pgdbconst;
hsvdvbsn.insN	=	m.iinsN;
hsvdvbsn.eurdiv	=	eurdiv;
hsvdvbsn.sigstr	=	msigstr.isigstr;
hsvdvbsn.insstate	=	m.pins;
hsvdvbsn.sysset	=	sysset;
hsvdvbsn.iutil	=	mutil.iutil;
hsvdvbspol.satfeapi	=	satfeapi;
hsvdvbspol.ctrl	=	ctrl;
hsvdvbspol.pmp	=	pmp;
hsvdvbspol.pen	=	pen;
hsvdvbspol.err	=	err;
hsvdvbspol.strapi	=	strapi;
hsvdvbspol.pgdb	=	pgdb;
hsvdvbspol.pgdbconst	=	pgdbconst;
hsvdvbspol.insN	=	m.iinsN;
hsvdvbspol.eurdiv	=	eurdiv;
hsvdvbspol.sigstr	=	msigstr.isigstr;
hsvdvbspol.insstate	=	m.pins;
hsvdvbspol.sysset	=	sysset;
hsvdvbspol.iutil	=	mutil.iutil;
hsvdvbspol.Timerclk	=	Timerclk;
hsvdvbsrussia.satfeapi	=	satfeapi;
hsvdvbsrussia.ctrl	=	ctrl;
hsvdvbsrussia.pmp	=	pmp;
hsvdvbsrussia.pen	=	pen;
hsvdvbsrussia.Timerclk	=	Timerclk;
hsvdvbsrussia.err	=	err;
hsvdvbsrussia.strapi	=	strapi;
hsvdvbsrussia.pgdb	=	pgdb;
hsvdvbsrussia.pgdbconst	=	pgdbconst;
hsvdvbsrussia.insN	=	m.iinsN;
hsvdvbsrussia.eurdiv	=	eurdiv;
hsvdvbsrussia.sigstr	=	msigstr.isigstr;
hsvdvbsrussia.insstate	=	m.pins;
hsvdvbsrussia.sysset	=	sysset;
hsvdvbsrussia.iutil	=	mutil.iutil;
hsvdvbsfransat.satfeapi	=	satfeapi;
hsvdvbsfransat.ctrl	=	ctrl;
hsvdvbsfransat.pmp	=	pmp;
hsvdvbsfransat.pen	=	pen;
hsvdvbsfransat.err	=	err;
hsvdvbsfransat.strapi	=	strapi;
hsvdvbsfransat.pgdb	=	pgdb;
hsvdvbsfransat.pgdbconst	=	pgdbconst;
hsvdvbsfransat.insN	=	m.iinsN;
hsvdvbsfransat.eurdiv	=	eurdiv;
hsvdvbsfransat.sigstr	=	msigstr.isigstr;
hsvdvbsfransat.insstate	=	m.pins;
hsvdvbsfransat.sysset	=	sysset;
hsvdvbsfransat.iutil	=	mutil.iutil;
hsvdvbsfransat.plfres	=	plfres;
hsvdvbsfransat.s2div	=	s2div;
hsvdvbsfransat.observer	=	observer;
hsvdvbsfransat.pgdat	=	pgdat;
hsvdvbsastra.satfeapi	=	satfeapi;
hsvdvbsastra.ctrl	=	ctrl;
hsvdvbsastra.pmp	=	pmp;
hsvdvbsastra.pen	=	pen;
hsvdvbsastra.Timerclk	=	Timerclk;
hsvdvbsastra.err	=	err;
hsvdvbsastra.strapi	=	strapi;
hsvdvbsastra.pgdb	=	pgdb;
hsvdvbsastra.pgdbconst	=	pgdbconst;
hsvdvbsastra.insN	=	m.iinsN;
hsvdvbsastra.eurdiv	=	eurdiv;
hsvdvbsastra.sigstr	=	msigstr.isigstr;
hsvdvbsastra.insstate	=	m.pins;
hsvdvbsastra.iutil	=	mutil.iutil;
hsvdvbsastra.pgdat	=	pgdat; 
hsvdvbsastra.pgsel	=	pgsel; 

hsvdvbstricolor.satfeapi	=	satfeapi;
hsvdvbstricolor.ctrl	=	ctrl;
hsvdvbstricolor.pmp	=	pmp;
hsvdvbstricolor.pen	=	pen;
hsvdvbstricolor.err	=	err;
hsvdvbstricolor.strapi	=	strapi;
hsvdvbstricolor.pgdb	=	pgdb;
hsvdvbstricolor.pgdbconst	=	pgdbconst;
hsvdvbstricolor.insN	=	m.iinsN;
hsvdvbstricolor.eurdiv	=	eurdiv;
hsvdvbstricolor.sigstr	=	msigstr.isigstr;
hsvdvbstricolor.insstate	=	m.pins;
hsvdvbstricolor.iutil	=	mutil.iutil;
hsvdvbstricolor.pgdat	=	pgdat;
hsvdvbstricolor.Timerclk	=	Timerclk;
hsvdvbstricolor.idvbset	=	msettings.idvbset;

hsvdvbsopprofile.satfeapi		=	satfeapi;
hsvdvbsopprofile.ctrl			=	ctrl;
hsvdvbsopprofile.pmp			=	pmp;
hsvdvbsopprofile.pen			=	pen;
hsvdvbsopprofile.strapi		=	strapi;
hsvdvbsopprofile.pgdb			=	pgdb;
hsvdvbsopprofile.pgdbconst	=	pgdbconst;
hsvdvbsopprofile.eurdiv		=	eurdiv;
hsvdvbsopprofile.sigstr		=	msigstr.isigstr;
hsvdvbsopprofile.plfres		=	plfres;
hsvdvbsopprofile.pgdat		=	pgdat;
hsvdvbsfreesat.satfeapi	=	satfeapi;
hsvdvbsfreesat.ctrl	=	ctrl;
hsvdvbsfreesat.pmp	=	pmp;
hsvdvbsfreesat.pen	=	pen;
hsvdvbsfreesat.Timerclk	=	Timerclk;
hsvdvbsfreesat.err	=	err;
hsvdvbsfreesat.strapi	=	strapi;
hsvdvbsfreesat.pgdb	=	pgdb;
hsvdvbsfreesat.pgdbconst	=	pgdbconst;
hsvdvbsfreesat.insN	=	m.iinsN;
hsvdvbsfreesat.eurdiv	=	eurdiv;
hsvdvbsfreesat.sigstr	=	msigstr.isigstr;
hsvdvbsfreesat.insstate	=	m.pins;
hsvdvbsfreesat.sysset	=	sysset;
hsvdvbsfreesat.iutil	=	mutil.iutil;
hsvdvbsfreesat.pgdat    = pgdat;
hsvdvbsopprofile.apsysset	=	apsysset;
hsvdvbsopprofile.idvbset	=	msettings.idvbset;
hsvdvbsopprofile.opins		=	opins;
hsvdvbsopprofile.insN		=	m.iinsN;
hsvdvbsopprofile.camdataparser = camdataparser;
hsvdvbsopprofile.camnitena = camnitena;
hsvdvbsopprofile.iprescanparser = mprescanparser.iprescanparser;
ctrlN	=	m.ctrlN;
satfeapiN	=	m.satfeapiN;
m.pmp	=	pmp;
m.pen	=	pen;
m.err	=	err;
m.pgdbconst	=	pgdbconst;
m.pgdb	=	pgdb;
m.insN	=	insN;
m.sysset	=	sysset;
m.mctl	=	mctl;
m.cids	=	cids;
m.wnddest	=	wnddest;
m.idvbset	=	msettings.idvbset;
m.iprescan	=	mprescan.iprescan;
m.isatipprescan	=	msatipprescan.iprescan;
m.iprescanctrlN	=	mprescan.iprescanctrlN;
m.iminiprescanctrlN	=	mminiprescan.iminiprescanctrlN;
m.ipackageparserctrlN	=	mpackageparser.ipackageparserctrlN;
m.ipackageparseropinsN =	mpackageparser.opinsN;
m.ipackageparsercipStatusN =	mpackageparser.cipStatusN;
m.iprescansatfrontendN	=	mprescan.iprescansatfrontendN;
m.iminiprescansatfrontendN	=	mminiprescan.iminiprescansatfrontendN;
m.ipackageparsersatfrontendN	=	mpackageparser.ipackageparsersatfrontendN;
m.ipackageins	=	mroute.ipackageins;
m.isigstr	=	msigstr.isigstr;
m.ipackage	=	mpackageparser.ipackage;
m.ipackagectrlN	=	mroute.ipackagectrlN;
m.ipackageplfApidvbsN	=	mroute.ipackageplfApidvbsN;
m.iaddremove	=	mremovesat.iaddremove;
m.ipackagesort	=	mroute.ipackagesort;
m.hsvdvbsgeneric_ins	=	hsvdvbsgeneric.ins;
m.hsvdvbsgeneric_plfApidvbsN	=	hsvdvbsgeneric.plfApidvbsN;
m.hsvdvbsgeneric_ctrlN	=	hsvdvbsgeneric.ctrlN;
m.ibckctrlN	=	mroute.ibckctrlN;
m.vctl	=	vctl;
m.actl3	=	actl3;
m.satfeapi	=	satfeapi;
m.iprescanparser	=	mprescanparser.iprescanparser;
m.charsetutil	=	charsetutil;
m.iutil	=	mutil.iutil;
m.ctrl	=	ctrl;
m.istrapiN	=	mroute.istrapiN;
m.ipackageopinsN	=	mroute.ipackageopinsN;
m.ibckInstall	=	mroute.ibckInstall;
m.s2div	=	s2div;
m.iminiprescan	=	mminiprescan.iminiprescan;
m.ipredefcopy	=	mpredefinedlistcopy.ipredefcopy;
m.isatipprescanctrlN = msatipprescan.iprescanctrlN;
m.isatipprescansatfrontendN = msatipprescan.iprescansatfrontendN;
pow	=	mpow.pow;
mpow.ipow	=	m.ipow;
mpow.idvbsetpow	=	msettings.idvbsetpow;
mpow.iprescanpow	=	mprescan.iprescanpow;
mpow.iminiprescanpow	=	mminiprescan.iminiprescanpow;
mpow.impackagepow	=	mpackageparser.impackagepow;
mpow.iremovesatpow	=	mremovesat.iremovesatpow;
mpow.ipackagepow	=	mroute.ipackagepow;
mpow.ipredefpow	=	mpredefinedlistcopy.ipredefpow;
mpow.isatipprescanpow	=	msatipprescan.iprescanpow;
pakgins	=	mroute.ipackageins;
mprescan.pins	=	m.pins;
mprescan.idvbset	=	msettings.idvbset;
mprescan.err	=	err;
mprescan.ctrl	=	ctrl;
mprescan.pmp	=	pmp;
mprescan.pen	=	pen;
mprescan.wnddest	=	wnddest;
mprescan.iinsN	=	m.iinsN;
mprescan.satfeapi	=	satfeapi;
mprescan.ipackage	=	mpackageparser.ipackage;
mprescan.charsetutil	=	charsetutil;
mprescan.strapi	=	strapi;
mprescan.pgdb	=	pgdb;
mprescan.pgdbconst	=	pgdbconst;
mprescan.iprescanparser	=	mprescanparser.iprescanparser;
mprescan.isigstr	=	msigstr.isigstr;
mprescan.qssm	=	qssm;
mprescan.vssm	=	vssm;
mprescan.eurdiv	=	eurdiv;
mprescan.cids	=	cids;
mprescan.sysset	=	sysset;
mminiprescan.pins	=	m.pins;
mminiprescan.idvbset	=	msettings.idvbset;
mminiprescan.err	=	err;
mminiprescan.ctrl	=	ctrl;
mminiprescan.pmp	=	pmp;
mminiprescan.pen	=	pen;
mminiprescan.wnddest	=	wnddest;
mminiprescan.iminiprescanN	=	m.iminiprescanN;
mminiprescan.satfeapi	=	satfeapi;
mminiprescan.ipackage	=	mpackageparser.ipackage;
mminiprescan.charsetutil	=	charsetutil;
mminiprescan.strapi	=	strapi;
mminiprescan.pgdb	=	pgdb;
mminiprescan.pgdbconst	=	pgdbconst;
mminiprescan.iprescanparser	=	mprescanparser.iprescanparser;
mminiprescan.isigstr	=	msigstr.isigstr;
mminiprescan.qssm	=	qssm;
mminiprescan.vssm	=	vssm;
mminiprescan.eurdiv	=	eurdiv;
msatipprescan.pins	=	m.pins;
msatipprescan.idvbset	=	msettings.idvbset;
msatipprescan.err	=	err;
msatipprescan.ctrl	=	ctrl;
msatipprescan.pmp	=	pmp;
msatipprescan.pen	=	pen;
msatipprescan.wnddest	=	wnddest;
msatipprescan.satfeapi	=	satfeapi;
msatipprescan.ipackage	=	mpackageparser.ipackage;
msatipprescan.charsetutil	=	charsetutil;
msatipprescan.strapi	=	strapi;
msatipprescan.pgdb	=	pgdb;
msatipprescan.pgdbconst	=	pgdbconst;
msatipprescan.iprescanparser	=	mprescanparser.iprescanparser;
msatipprescan.isigstr	=	msigstr.isigstr;
msatipprescan.qssm	=	qssm;
msatipprescan.vssm	=	vssm;
msatipprescan.eurdiv	=	eurdiv;
msatipprescan.sysset	=	sysset;
msatipprescan.iinsN	=	m.iinsN;
msatipprescan.cids	=	cids;
mprescanparser.satfeapi	=	satfeapi;
mprescanparser.charsetutil	=	charsetutil;
plfresN	=	hsvdvbsfransat.plfresN;
sysstateN	=	hsvdvbsfransat.sysstateN;
dvbset	=	msettings.idvbset;
insroute	=	msettings.insroute;
sysnotifyN	=	msettings.sysnotifyN;
msettings.err	=	err;
msettings.s2div	=	s2div;
msettings.sysset	=	sysset;
msettings.apsysset	=	apsysset;
msettings.insN	=	insN;
msettings.cids	=	cids;
mpackageparser.sysset	=	sysset;
mpackageparser.pgdb	=	pgdb;
mpackageparser.pgdbconst	=	pgdbconst;
mpackageparser.err	=	err;
mpackageparser.charsetutil	=	charsetutil;
mpackageparser.lngids	=	lngids;
mpackageparser.cids	=	cids;
mpackageparser.apsysset	=	apsysset;
mpackageparser.strapi	=	strapi;
mpackageparser.pmp	=	pmp;
mpackageparser.pen	=	pen;
mpackageparser.ctrl	=	ctrl;
mpackageparser.iinsN	=	m.iinsN;
mpackageparser.satfeapi	=	satfeapi;
mpackageparser.iprescanparser	=	mprescanparser.iprescanparser;
mpackageparser.opins	=	opins;
mpackageparser.cipStatus	=	cipStatus;
mpackageparser.dvbset=	msettings.idvbset;
msigstr.wnddest	=	wnddest;
msigstr.vssm	=	vssm;
msigstr.qssm	=	qssm;
mutil.pins	=	m.pins;
mutil.pgdb 	= pgdb;
mutil.pgdbconst	= pgdbconst;
mroute.hsvdvbsgeneric_pow	=	hsvdvbsgeneric.pow;
mroute.hsvdvbsgeneric_ins	=	hsvdvbsgeneric.ins;
mroute.hsvdvbsgeneric_ctrlN	=	hsvdvbsgeneric.ctrlN;
mroute.hsvdvbsgeneric_plfApidvbsN	=	hsvdvbsgeneric.plfApidvbsN;
mroute.hsvdvbsgeneric_sort	=	hsvdvbsgeneric.sort;
mroute.hsvdvbsgeneric_bckInstall	=	hsvdvbsgeneric.bckInstall;
mroute.hsvdvbsgeneric_bckctrlN	=	hsvdvbsgeneric.bckctrlN;
mroute.hsvdvbsgeneric_strapiN	=	hsvdvbsgeneric.strapiN;
mroute.hsvdvbscanal_pow	=	hsvdvbscanal.pow;
mroute.hsvdvbscanal_ins	=	hsvdvbscanal.ins;
mroute.hsvdvbscanal_ctrlN	=	hsvdvbscanal.ctrlN;
mroute.hsvdvbscanal_plfApidvbsN	=	hsvdvbscanal.plfApidvbsN;
mroute.hsvdvbscanal_sort	=	hsvdvbscanal.sort;
mroute.hsvdvbsn_pow	=	hsvdvbsn.pow;
mroute.hsvdvbsn_ins	=	hsvdvbsn.ins;
mroute.hsvdvbsn_ctrlN	=	hsvdvbsn.ctrlN;
mroute.hsvdvbsn_plfApidvbsN	=	hsvdvbsn.plfApidvbsN;
mroute.hsvdvbsn_sort	=	hsvdvbsn.sort;
mroute.hsvdvbsm7_pow	=	hsvdvbsm7.pow;
mroute.hsvdvbsm7_ins	=	hsvdvbsm7.ins;
mroute.hsvdvbsm7_ctrlN	=	hsvdvbsm7.ctrlN;
mroute.hsvdvbsm7_plfApidvbsN	=	hsvdvbsm7.plfApidvbsN;
mroute.hsvdvbsm7_sort	=	hsvdvbsm7.sort;
mroute.pins	=	m.pins;
mroute.ipackage	=	mpackageparser.ipackage;
mroute.err	=	err;
mroute.hsvdvbspol_pow	=	hsvdvbspol.pow;
mroute.hsvdvbspol_ins	=	hsvdvbspol.ins;
mroute.hsvdvbspol_ctrlN	=	hsvdvbspol.ctrlN;
mroute.hsvdvbspol_plfApidvbsN	=	hsvdvbspol.plfApidvbsN;
mroute.hsvdvbspol_sort	=	hsvdvbspol.sort;
mroute.hsvdvbsrussia_pow	=	hsvdvbsrussia.pow;
mroute.hsvdvbsrussia_ins	=	hsvdvbsrussia.ins;
mroute.hsvdvbsrussia_ctrlN	=	hsvdvbsrussia.ctrlN;
mroute.hsvdvbsrussia_plfApidvbsN	=	hsvdvbsrussia.plfApidvbsN;
mroute.hsvdvbsrussia_sort	=	hsvdvbsrussia.sort;
mroute.hsvdvbsdigiturk_pow	=	hsvdvbsdigiturk.pow;
mroute.hsvdvbsdigiturk_ins	=	hsvdvbsdigiturk.ins;
mroute.hsvdvbsdigiturk_ctrlN	=	hsvdvbsdigiturk.ctrlN;
mroute.hsvdvbsdigiturk_plfApidvbsN	=	hsvdvbsdigiturk.plfApidvbsN;
mroute.hsvdvbsdigiturk_sort	=	hsvdvbsdigiturk.sort;
mroute.hsvdvbsfransat_pow	=	hsvdvbsfransat.pow;
mroute.hsvdvbsfransat_ins	=	hsvdvbsfransat.ins;
mroute.hsvdvbsfransat_ctrlN	=	hsvdvbsfransat.ctrlN;
mroute.hsvdvbsfransat_plfApidvbsN	=	hsvdvbsfransat.plfApidvbsN;
mroute.hsvdvbsfransat_sort	=	hsvdvbsfransat.sort;
mroute.hsvdvbsfransat_bckInstall	=	hsvdvbsfransat.bckInstall;
mroute.hsvdvbsfransat_bckctrlN	=	hsvdvbsfransat.bckctrlN;
mroute.hsvdvbsopprofile_ctrlN = hsvdvbsopprofile.ctrlN;
mroute.hsvdvbsfransat_strapiN	=	hsvdvbsfransat.strapiN;
mroute.hsvdvbsopprofile_pow	=	hsvdvbsopprofile.pow;
mroute.hsvdvbsopprofile_ins	=	hsvdvbsopprofile.ins;
mroute.hsvdvbsopprofile_strapiN	=	hsvdvbsopprofile.strapiN;
mroute.hsvdvbsopprofile_sort	=	hsvdvbsopprofile.sort;
mroute.hsvdvbsopprofile_opinsN	=	hsvdvbsopprofile.opinsN;
mroute.hsvdvbsopprofile_plfApidvbsN	=	hsvdvbsopprofile.plfApidvbsN;
mroute.hsvdvbsfreesat_pow	=	hsvdvbsfreesat.pow;
mroute.hsvdvbsfreesat_ins	=	hsvdvbsfreesat.ins;
mroute.hsvdvbsfreesat_ctrlN	=	hsvdvbsfreesat.ctrlN;
mroute.hsvdvbsfreesat_plfApidvbsN	=	hsvdvbsfreesat.plfApidvbsN;
mroute.hsvdvbsfreesat_sort	=	hsvdvbsfreesat.sort;
mroute.hsvdvbsfreesat_settings	=	hsvdvbsfreesat.settings;
mroute.hsvdvbsfreesat_strapiN = hsvdvbsfreesat.strapiN;
mroute.hsvdvbsfreesat_ibckInstall = hsvdvbsfreesat.bckInstall;
mroute.hsvdvbsastra_pow	=	hsvdvbsastra.pow;
mroute.hsvdvbsastra_ins	=	hsvdvbsastra.ins;
mroute.hsvdvbsastra_ctrlN	=	hsvdvbsastra.ctrlN;
mroute.hsvdvbsastra_plfApidvbsN	=	hsvdvbsastra.plfApidvbsN;
mroute.hsvdvbsastra_sort	=	hsvdvbsastra.sort;
mroute.hsvdvbsastra_strapiN	=	hsvdvbsastra.strapiN;
mroute.hsvdvbsastra_bckInstall=	hsvdvbsastra.bckInstall;

mroute.hsvdvbstricolor_pow	=	hsvdvbstricolor.pow;
mroute.hsvdvbstricolor_ins	=	hsvdvbstricolor.ins;
mroute.hsvdvbstricolor_ctrlN	=	hsvdvbstricolor.ctrlN;
mroute.hsvdvbstricolor_plfApidvbsN	=	hsvdvbstricolor.plfApidvbsN;
mroute.hsvdvbstricolor_sort	=	hsvdvbstricolor.sort;
//mroute.hsvdvbstricolor_strapiN	=	hsvdvbstricolor.strapiN;
m.hsvdvbstricolor_plfApidvbsN = hsvdvbstricolor.plfApidvbsN;
m.hsvdvbstricolor_ctrlN = hsvdvbstricolor.ctrlN;
mremovesat.pmp	=	pmp;
mremovesat.pen	=	pen;
mremovesat.pgdb	=	pgdb;
mremovesat.pgdbconst	=	pgdbconst;
mremovesat.iinsN	=	m.iinsN;
mremovesat.err	=	err;
mremovesat.pins	=	m.pins;
mremovesat.idvbset	=	msettings.idvbset;
usbdevexN	=	mpredefinedlistcopy.usbdevexN;
recdevN	=	mpredefinedlistcopy.recdevN;
mpredefinedlistcopy.pmp	=	pmp;
mpredefinedlistcopy.pen	=	pen;
mpredefinedlistcopy.err	=	err;
mpredefinedlistcopy.usbms	=	usbms;
mpredefinedlistcopy.iinsN	=	m.iinsN;
mpredefinedlistcopy.recdev	=	recdev;
mpredefinedlistcopy.wnddest	=	wnddest;
mpredefinedlistcopy.tprtk	=	tprtk;
strapiN	=	m.strapiN;
opinsN	= 	m.opinsN;
cipStatusN	= 	m.cipStatusN;
itricolorsettings = hsvdvbstricolor.itricolorsettings;
}

};

#endif

