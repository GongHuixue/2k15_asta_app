#ifndef  _CHSVEUROPEINSTALLATION_H
#define  _CHSVEUROPEINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvEuropeInstallation_m.h>
#include <CHsvEuropeInstallation_mDbookConflicts.h>
#include <CHsvEuropeInstallation_mDbookSort.h>
#include <CHsvEuropeInstallation_mSortRoute.h>
#include <CHsvEuropeInstallation_macids.h>
#include <CHsvEuropeInstallation_madvpgitr.h>
#include <CHsvEuropeInstallation_mcabsort.h>
#include <CHsvEuropeInstallation_mcamsort.h>
#include <CHsvEuropeInstallation_mconflicts.h>
#include <CHsvEuropeInstallation_mdiv.h>
#include <CHsvEuropeInstallation_mfinsort.h>
#include <CHsvEuropeInstallation_mfreqctl.h>
#include <CHsvEuropeInstallation_mitasort.h>
#include <CHsvEuropeInstallation_mlitesort.h>
#include <CHsvEuropeInstallation_mnorsort.h>
#include <CHsvEuropeInstallation_mpegsort.h>
#include <CHsvEuropeInstallation_mpow.h>
#include <CHsvEuropeInstallation_mroute.h>
#include <CHsvEuropeInstallation_msigstr.h>
#include <CHsvEuropeInstallation_msort.h>
#include <CHsvEuropeInstallation_mstub.h>
#include <CHsvEuropeInstallation_msysctl.h>
#include <CHsvEuropeInstallation_msysset.h>
#include <CHsvEuropeInstallation_mapmeasort.h>
#include <CHsvEuropeInstallation_mhungarysort.h>
#include <CHsvEuropeInstallation_mblizoosort.h>
#include <CHsvAciDecode.h>
#include <CHsvDvbCamInstallation.h>
#include <CHsvDvbCInstallation.h>
#include <CHsvDvbTInstallation.h>
#include <CHsvDvbtMpegInstallation.h>
#include <CHsvPresetInstallation.h>
#include <CHsvZiggoInstallation.h>
#include <CHsvCanalDigitalInstallation.h>
#include <CSvcPaci.h>
#include <CSvcPats.h>
#include <IHsvAciData.h>
#include <IHsvAltFrequencyIterator.h>
#include <IHsvAltFrequencyScannerNotify.h>
#include <ITvColorDecode2NotifyEx.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDVBSettings.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPresetImplicitInstall.h>
#include <IHsvInstallation2.h>
#include <IHsvLastActivity.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvAciDisplayNotify.h>
#include <IHsvAciInstallationSubNotify.h>
#include <IHsvPower.h>
#include <IHsvTxtResetNotify.h>
#include <IHsvSourceSetupNotify.h>
#include <IHsvStreamNotify.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IProdApiClockEx.h>
#include <IHsvTxtPageAccess.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvSdmEnable.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvTsvChannelName.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <IHsvTxtPageConvert.h>
#include <ITvColorDecode2.h>
#include <IHsvSdmControl2.h>
#include <IHsvTxtDecode.h>
#include <IHsvDestinationConfiguration.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvTxtDisplayDriver.h>
#include <ITxtDisplayDriver3.h>
#include <IEnable.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvTextDisplay.h>
#include <IHsvPool.h>
#include <IHsvInstallationNotify.h>
#include <IHsvLastActivityNotify.h>
#include <IHsvLanguageIds2.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IHsvMemoryPool.h>
#include <IMemoryOperations.h>
#include <IHsvDvbMplDiv.h>
#include <IHsvCookieNvmInfo.h>
#include <ICesOperatorProfile.h>
#include <IHsvTxtPacket830Data.h>
#include <IPumpEngine.h>
#include <IHsvProgramDataControl3.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramIterator.h>
#include <IHsvProgramSelection2.h>
#include <IHsvTxtPacket0.h>
#include <IPlfApiDesignatorId.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPlfApiSourceId.h>
#include <IPumpExSub.h>
#include <ISvcPowerStateControlEx.h>
#include <IHsvTxtPageRequest.h>
#include <IRealTimeKernel.h>
#include <IHsvSourceSetup.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvTcSystemSettingsEx.h>
#include <IInfraTimerServer.h>
#include <IAppApiTextDisplayConstants.h>
#include <IHsvTxtPresent.h>
#include <ISvcVideoControl3.h>
#include <ITvVideoProperties3Ex.h>
#include <IHsvTxtVpsData.h>
#include <IHsvWindowDestinationMap.h>
#include <IPlfApiVbi.h>
#include <IPlfProxy.h>
#include <IHsvAciDisplay.h>
#include <IPlfProxyNotify.h>
#include<IMultiLingualStringConversion.h>
#include <IHsvCharSetUtility2.h>
class CHsvEuropeInstallation
{
public:
virtual ~CHsvEuropeInstallation(){}

//Contained Modules
private:
CHsvEuropeInstallation_m m;
CHsvEuropeInstallation_mDbookConflicts mDbookConflicts;
CHsvEuropeInstallation_mDbookSort mDbookSort;
CHsvEuropeInstallation_mSortRoute mSortRoute;
CHsvEuropeInstallation_macids macids;
CHsvEuropeInstallation_madvpgitr madvpgitr;
CHsvEuropeInstallation_mblizoosort mblizoosort;
CHsvEuropeInstallation_mcabsort mcabsort;
CHsvEuropeInstallation_mcamsort mcamsort;
CHsvEuropeInstallation_mconflicts mconflicts;
CHsvEuropeInstallation_mdiv mdiv;
CHsvEuropeInstallation_mfinsort mfinsort;
CHsvEuropeInstallation_mfreqctl mfreqctl;
CHsvEuropeInstallation_mitasort mitasort;
CHsvEuropeInstallation_mlitesort mlitesort;
CHsvEuropeInstallation_mnorsort mnorsort;
CHsvEuropeInstallation_mpegsort mpegsort;
CHsvEuropeInstallation_mapmeasort mapmeasort;
CHsvEuropeInstallation_mpow mpow;
CHsvEuropeInstallation_mroute mroute;
CHsvEuropeInstallation_msigstr msigstr;
CHsvEuropeInstallation_msort msort;
CHsvEuropeInstallation_mstub mstub;
CHsvEuropeInstallation_msysctl msysctl;
CHsvEuropeInstallation_msysset msysset;
CHsvEuropeInstallation_mhungarysort mhungarysort;
//Contained Components
private:
CHsvAciDecode hsvacidec;
CHsvDvbCamInstallation hsvdvbcamins;
CHsvDvbCInstallation hsvdvbcins;
CHsvDvbTInstallation hsvdvbtins;
CHsvDvbtMpegInstallation hsvdvbtmpegins;
CHsvPresetInstallation hsvprins;
CHsvZiggoInstallation hsvziggoins;
CHsvCanalDigitalInstallation hsvcanaldigitalins;
CSvcPaci svpaci;
CSvcPats svpats;
public:
ProvidesInterface<IHsvAciData>	acidat;

ProvidesInterface<IHsvAltFrequencyIterator>	afitr;

ProvidesInterface<IHsvAltFrequencyScannerNotify>	afscanN;

ProvidesInterface<ITvColorDecode2NotifyEx>	colN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvDVBSettings>	dvbset;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvSortedTableConfigurationEx>	freqlistconf;

ProvidesInterface<IHsvPresetImplicitInstall>	implins;

ProvidesInterface<IHsvInstallation2>	ins;

ProvidesInterface<IHsvLastActivity>	instla;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;
ProvidesInterface<IHsvAciDisplayNotify>	pacidsN;

ProvidesInterface<IHsvAciInstallationSubNotify>	pgaciN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvTxtResetNotify>	resetN;

ProvidesInterface<IHsvSourceSetupNotify>	srcstpN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;
ProvidesInterface<IHsvAciDisplay>	acids;
ProvidesInterface<IPlfProxyNotify>			plfProxyN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvTxtPageAccess>	acc;
RequiresInterface<ISvcAudioControl4ExEx>	actl;
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvSdmEnable>	camena;
RequiresInterface<IHsvChannelLibReturnCodes>	chanlibret;
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvTsvChannelName>	chlname;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<ICesCityIds>	cityids;
RequiresInterface<IHsvTxtPageConvert>	cnv;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvTxtDecode>	dec;
RequiresInterface<IHsvDestinationConfiguration>	destconfig;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvTxtDisplayDriver>	dsdrv;
RequiresInterface<ITxtDisplayDriver3>	dsdrv3;
RequiresInterface<IEnable>	dsenb;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvTextDisplay>	gfxtxt;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvLastActivityNotify>	instlaN;
RequiresInterface<IHsvLanguageIds2>	lngids;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IHsvMemoryPool>	mem;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvDvbMplDiv>	mpldiv;
RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<IHsvTxtPacket830Data>	p830;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDataControl3>	pgctl;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramIterator>	pgitr;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IHsvTxtPacket0>	pkt0;
RequiresInterface<IPlfApiDesignatorId>	plfdesigid;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPlfApiSourceId>	plfsrcid;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<ISvcPowerStateControlEx>	powctlx;
RequiresInterface<IHsvTxtPageRequest>	req;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSourceSetup>	srcstp;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvTcSystemSettingsEx>	syssetx;
RequiresInterface<IInfraTimerServer>	tmr;
RequiresInterface<IAppApiTextDisplayConstants>	txtdspcons;
RequiresInterface<IHsvTxtPresent>	txtpre;
RequiresInterface<ISvcVideoControl3>	vctl;
RequiresInterface<ITvVideoProperties3Ex>	vip;
RequiresInterface<IHsvTxtVpsData>	vps;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ITvColorDecode2>	xcol;
RequiresInterface<IHsvCamScanHelper>	camScanparser;
RequiresInterface<IPlfApiVbi>		plfvbi;
RequiresInterface<IEnable>			dcu;
RequiresInterface<IPlfProxy>		plfproxy;
RequiresInterface<IMultiLingualStringConversion>	ling;
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
private:
Pumpdefines(CHsvEuropeInstallation);

public:
CHsvEuropeInstallation()
{
pow	=	mpow.pow;
mpow.impow	=	m.impow;
mpow.imfreqctlpow	=	mfreqctl.imfreqctlpow;
mpow.icabpow	=	mcabsort.icabpow;
mpow.iblizoopow	=	mblizoosort.iblizoopow;
mpow.ilitepow	=	mlitesort.ilitepow;
mpow.inorpow	=	mnorsort.inorpow;
mpow.iitapow	=	mitasort.iitapow;
mpow.iconpow	=	mconflicts.iconpow;
mpow.idbookconpow	=	mDbookConflicts.idbookconpow;
mpow.idbooksortpow	=	mDbookSort.idbooksortpow;
mpow.idvbtsortpow	=	msort.idvbtsortpow;
mpow.ifinsortpow	=	mfinsort.ifinsortpow;
mpow.icamsortpow	=	mcamsort.icamsortpow;
mpow.idvbtapmeasortpow	=	mapmeasort.idvbtapmeasortpow;
mpow.impegpow	=	mpegsort.impegpow;
mpow.hsvdvbtins_pow	=	hsvdvbtins.pow;
mpow.hsvdvbcins_pow	=	hsvdvbcins.pow;
mpow.hsvdvbtmpegins_pow	=	hsvdvbtmpegins.pow;
mpow.hsvziggoins_pow	=	hsvziggoins.pow;
mpow.hsvcanaldigitalins_pow	=	hsvcanaldigitalins.pow;
mpow.hsvprins_pow	=	hsvprins.pow;
mpow.svpaci_pow	=	svpaci.pow;
mpow.hsvacidec_pow	=	hsvacidec.pow;
mpow.hsvdvbcamins_pow	=	hsvdvbcamins.pow;
mpow.idvbthungarysortpow	=	mhungarysort.idvbthungarysortpow;
plfProxyN = m.plfProxyN;
feapiN	=	m.feapiN;
implins	=	m.implins;
acidat	=	m.acidat;
resetN	=	m.resetN;
pgaciN	=	m.ipgaciN;
pacidsN	=	m.pacidsN;
colN	=	m.colN;
srcstpN	=	m.srcstpN;
m.pmp	=	pmp;
m.pen	=	pen;
m.rtk	=	rtk;
m.div	=	div;
m.eurdiv	=	eurdiv;
m.err	=	err;
m.log	=	log;
m.instutil	=	msysctl.instutil;
m.isortroute	=	mSortRoute.isortroute;
m.isort	=	mroute.isort;
m.icamsort = mcamsort.icamsort;
m.sigstr	=	msigstr.sigstr;
m.freqctl	=	mfreqctl.freqctl;
m.hsvdvbtins_digacq	=	hsvdvbtins.digacq;
m.hsvdvbcins_digacq	=	hsvdvbcins.digacq;
m.hsvdvbtins_dvbt	=	hsvdvbtins.dvbt;
m.hsvdvbtmpegins_digacq	=	hsvdvbtmpegins.digacq;
m.hsvziggoins_dataacq	=	hsvziggoins.dataacq;
m.hsvcanaldigitalins_dataacq	=	hsvcanaldigitalins.dataacq;
m.hsvdvbcamins_dataacq	=	hsvdvbcamins.dataacq;
m.hsvdvbtmpegins_digscan	=	hsvdvbtmpegins.digscan;
m.hsvprins_prins	=	hsvprins.prins;
m.dcu	= dcu;
m.plfproxy = plfproxy;
msort.hsvprins_prins	= hsvprins.prins;
mcabsort.hsvprins_prins	= hsvprins.prins;
mlitesort.hsvprins_prins	= hsvprins.prins;
mpegsort.hsvprins_prins	= hsvprins.prins;
mfinsort.hsvprins_prins = hsvprins.prins;
mitasort.hsvprins_prins = hsvprins.prins;
mnorsort.hsvprins_prins = hsvprins.prins;
mapmeasort.hsvprins_prins = hsvprins.prins;
mhungarysort.hsvprins_prins = hsvprins.prins;
m.pgdbconst	=	pgdbconst;
m.pgdb	=	pgdb;
m.insN	=	insN;
m.sysset	=	sysset;
m.syssetx	=	syssetx;
m.apsysset	=	apsysset;
m.sysctl	=	msysctl.sysctl;
m.pgctl	=	pgctl;
m.mctl	=	mctl;
m.cids	=	cids;
m.srcstp	=	srcstp;
m.plfsrcid	=	plfsrcid;
m.plfdesigid	=	plfdesigid;
m.plferrids	=	plferrids;
m.wnddest	=	wnddest;
m.hsvdvbtins_feapiN	=	hsvdvbtins.feapiN;
m.hsvdvbcins_feapiN	=	hsvdvbcins.feapiN;
m.hsvziggoins_feapiN	=	hsvziggoins.feapiN;
m.hsvcanaldigitalins_feapiN	=	hsvcanaldigitalins.feapiN;
m.hsvdvbtmpegins_feapiN	=	hsvdvbtmpegins.feapiN;
m.hsvprins_feapiN	=	hsvprins.feapiN;
m.hsvdvbcamins_feapiN	=	hsvdvbcamins.feapiN;
m.hsvziggoins_ins	=	hsvziggoins.ins;
m.hsvcanaldigitalins_ins	=	hsvcanaldigitalins.ins;
m.hsvdvbcamins_ins	=	hsvdvbcamins.ins;
m.hsvdvbcins_dvbset	=	hsvdvbcins.dvbset;
m.hsvdvbtins_dvbset	=	hsvdvbtins.dvbset;
m.hsvdvbcamins_dvbset	=	hsvdvbcamins.dvbset;
m.feapi	=	feapi;
m.rins	=	m.pins;
m.hsvdvbtins_cntryinsN	=	hsvdvbtins.cntryinsN;
m.plfvbi	= plfvbi;
syssetN	=	m.isyssetN;
m.hsvdvbcins_syssetN	=	hsvdvbcins.syssetN;
m.hsvdvbtins_syssetN	=	hsvdvbtins.syssetN;
m.hsvdvbtins_bcksyssetN	=	hsvdvbtins.bcksyssetN;
m.iconf	=	mconflicts.iconf;
m.powctlx	=	powctlx;
m.hsvziggoins_sortN	=	hsvziggoins.sortN;
m.hsvziggoins_ena	=	hsvziggoins.ena;
m.hsvcanaldigitalins_sortN	=	hsvcanaldigitalins.sortN;
m.hsvcanaldigitalins_ena	=	hsvcanaldigitalins.ena;
m.hsvdvbcamins_ena	=	hsvdvbcamins.ena;
instla	=	m.instla;
m.instlaN	=	instlaN;
m.hsvprins_pow	=	hsvprins.pow;
m.hsvprins_acidat	=	hsvprins.acidat;
m.hsvprins_anaset	=	hsvprins.anaset;
m.hsvprins_implins	=	hsvprins.implins;
m.hsvprins_resetN	=	hsvprins.resetN;
m.hsvprins_pgaciN	=	hsvprins.pgaciN;
m.hsvprins_pacidsN	=	hsvprins.pacidsN;
m.hsvprins_colN	=	hsvprins.colN;
m.ctrl 	= ctrl;
hsvprins.rins	=	m.pins;
hsvprins.instutil	=	msysctl.instutil;
hsvprins.sysctl	=	msysctl.sysctl;
hsvprins.feapi	=	feapi;
hsvprins.wnddest	=	wnddest;
hsvprins.prinsN	=	m.hsvprins_prinsN;
hsvprins.pmp	=	pmp;
hsvprins.pen	=	pen;
hsvprins.div	=	div;
hsvprins.euconfig	=	mdiv.ieuconfig;
hsvprins.pgdb	=	pgdb;
hsvprins.pgdat	=	pgdat;
hsvprins.log	=	log;
hsvprins.vps	=	vps;
hsvprins.p830	=	p830;
hsvprins.txtpre	=	txtpre;
hsvprins.chlname	=	chlname;
hsvprins.pgdatcni	=	mstub.hsvprins_pgdatcni;
hsvprins.cniname	=	svpats.cniname;
hsvprins.str	=	str;
hsvprins.col	=	col;
hsvprins.xcol	=	xcol;
hsvprins.sysset	=	sysset;
hsvprins.cids	=	cids;
hsvprins.lngids	=	lngids;
acids			= 	svpaci.acids;
hsvprins.pgaci	=	svpaci.pgaci;
hsvprins.prsort	=	svpats.prsort;
hsvprins.mem	=	mem;
hsvprins.memo	=	memo;
hsvprins.pgdbconst	=	pgdbconst;
hsvprins.freqctl	=	mfreqctl.freqctl;
hsvprins.sigstr	=	msigstr.sigstr;
hsvprins.sort	=	mroute.isort;
hsvprins.err	=	err;
hsvprins.eurdiv	=	eurdiv;
hsvprins.chanlibret	=	chanlibret;
hsvacidec.acidecN	=	svpaci.acidecN;
hsvacidec.acinv	=	macids.iacinv;
hsvacidec.cnv	=	cnv;
hsvacidec.pkt0	=	pkt0;
hsvacidec.dsdrv	=	dsdrv;
hsvacidec.req	=	req;
hsvacidec.acc	=	acc;
hsvacidec.dec	=	dec;
hsvacidec.dsenb	=	dsenb;
hsvacidec.div	=	mdiv.hsvacidec_div;
hsvacidec.str	=	str;
hsvacidec.pen	=	pen;
hsvacidec.pmp	=	pmp;
hsvacidec.col	=	col;
hsvacidec.euconfig	=	mdiv.ieuconfig;
svpaci.pen	=	pen;
svpaci.pmp	=	pmp;
svpaci.prins	=	m.pins;
svpaci.tmr	=	tmr;
svpaci.div	=	mdiv.svpaci_div;
svpaci.sysset	=	sysset;
svpaci.langid	=	msysset.ilangid;
svpaci.vip	=	vip;
svpaci.txtpre	=	txtpre;
svpaci.pkt0	=	pkt0;
svpaci.acidat	=	hsvprins.acidat;
svpaci.pgcni	=	macids.svpaci_pgcni;
svpaci.acidec	=	hsvacidec.acidec;
svpaci.pgaciN	=	m.ipgaciN;
svpaci.acidsN	=	hsvprins.pacidsN;
macids.txtdspcons	=	txtdspcons;
macids.gfxtxt	=	gfxtxt;
macids.dsdrv	=	dsdrv;
macids.dsdrv3	=	dsdrv3;
svpats.div	=	mdiv.svpats_div;
svpats.str	=	str;
svpats.sysset	=	sysset;
svpats.langid	=	msysset.ilangid;
svpats.countid	=	msysset.icountid;
svpats.mem	=	mem;
svpats.memo	=	memo;
mdiv.icountid	=	msysset.icountid;
mdiv.sysset	=	sysset;
mdiv.pins	=	m.pins;
hsvdvbtins.feapi	=	feapi;
hsvdvbtins.rins	=	m.pins;
hsvdvbtins.sigstr	=	msigstr.sigstr;
hsvdvbtins.pen	=	pen;
hsvdvbtins.pmp	=	pmp;
hsvdvbtins.Timerclk	=	Timerclk;
hsvdvbtins.ctrl	=	ctrl;
hsvdvbtins.strapi	=	strapi;
hsvdvbtins.mctl	=	mctl;
hsvdvbtins.strmfltr	=	strmfltr;
hsvdvbtins.insN	=	m.hsvdvbtins_insN;
hsvdvbtins.installN	=	insN;
hsvdvbtins.pgdb	=	pgdb;
hsvdvbtins.wnddest	=	wnddest;
hsvdvbtins.plferrids	=	plferrids;
hsvdvbtins.ffsdir	=	ffsdir;
hsvdvbtins.str	=	str;
hsvdvbtins.cdvbset	=	hsvdvbcins.dvbset;
hsvdvbtins.sortroute	=	mSortRoute.isortroute;
hsvdvbtins.sortN	=	m.sortN;
hsvdvbtins.err	=	err;
hsvdvbtins.instutil	=	msysctl.instutil;
hsvdvbtins.pgdbconst	=	pgdbconst;
hsvdvbtins.pgdat	=	pgdat;
hsvdvbtins.sort	=	mroute.isort;
hsvdvbtins.sysset	=	sysset;
hsvdvbtins.cids	=	cids;
hsvdvbtins.eurdiv	=	eurdiv;
hsvdvbtins.srtdbids	=	srtdbids;
hsvdvbtins.srtdb	=	srtdb;
hsvdvbtins.chdecdvbt2	=	chdecdvbt2;
hsvdvbtins.plfres	=	plfres;
hsvdvbtins.hpool	=	hpool;
hsvdvbtins.pgsel	=	pgsel;
hsvdvbtmpegins.feapi	=	feapi;
hsvdvbtmpegins.instutil	=	msysctl.instutil;
hsvdvbtmpegins.rins	=	m.pins;
hsvdvbtmpegins.sigstr	=	msigstr.sigstr;
hsvdvbtmpegins.log	=	log;
hsvdvbtmpegins.div	=	div;
hsvdvbtmpegins.pen	=	pen;
hsvdvbtmpegins.pmp	=	pmp;
hsvdvbtmpegins.ctrl	=	ctrl;
hsvdvbtmpegins.strapi	=	strapi;
hsvdvbtmpegins.err	=	err;
hsvdvbtmpegins.mctl	=	mctl;
hsvdvbtmpegins.strmfltr	=	strmfltr;
hsvdvbtmpegins.insN	=	m.hsvdvbtmpegins_insN;
hsvdvbtmpegins.digscanN	=	m.hsvdvbtmpegins_digscanN;
hsvdvbtmpegins.pgdb	=	pgdb;
hsvdvbtmpegins.wnddest	=	wnddest;
hsvdvbtmpegins.plferrids	=	plferrids;
hsvdvbtmpegins.pgdbconst	=	pgdbconst;
hsvdvbtmpegins.pgdat	=	pgdat;
hsvdvbtmpegins.divsupp	=	m.divsupp;
hsvdvbtmpegins.sort	=	mroute.isort;
hsvdvbtmpegins.sysset	=	sysset;
hsvdvbtmpegins.cids	=	cids;
hsvdvbtmpegins.freqctl	=	mfreqctl.freqctl;
hsvdvbtmpegins.eurdiv	=	eurdiv;
hsvdvbtmpegins.srtdb	=	srtdb;
hsvdvbcins.rins	=	m.pins;
hsvdvbcins.pgdat	=	pgdat;
hsvdvbcins.pen	=	pen;
hsvdvbcins.pmp	=	pmp;
hsvdvbcins.Timerclk	=	Timerclk;
hsvdvbcins.ctrl	=	ctrl;
hsvdvbcins.strapi	=	strapi;
hsvdvbcins.sysset	=	sysset;
hsvdvbcins.pgdb	=	pgdb;
hsvdvbcins.sigstr	=	msigstr.sigstr;
hsvdvbcins.divsupp	=	m.divsupp;
hsvdvbcins.insN	=	m.hsvdvbcins_insN;
hsvdvbcins.installN	=	insN;
hsvdvbcins.sort	=	mroute.isort;
hsvdvbcins.pgdbconst	=	pgdbconst;
hsvdvbcins.hsverr	=	err;
hsvdvbcins.eurdiv	=	eurdiv;
hsvdvbcins.mpldiv	=	mpldiv;
hsvdvbcins.strmfltr	=	strmfltr;
hsvdvbcins.mctl	=	mctl;
hsvdvbcins.feapi	=	feapi;
hsvdvbcins.wnddest	=	wnddest;
hsvdvbcins.plferrids	=	plferrids;
hsvdvbcins.ffsdir	=	ffsdir;
hsvdvbcins.str	=	str;
hsvdvbcins.srtdbids	=	srtdbids;
hsvdvbcins.srtdb	=	srtdb;
hsvdvbcins.memo	=	memo;
hsvdvbcins.cids	=	cids;
hsvdvbcins.cityids	=	cityids;
hsvdvbcins.apsysset	=	apsysset;
hsvdvbcins.sortroute	=	mSortRoute.isortroute;
hsvdvbcins.sortN	=	m.sortN;
hsvdvbcins.instutil	=	msysctl.instutil;
m.hsvdvbcins_ins	=	hsvdvbcins.ins;
hsvziggoins.rins	=	m.pins;
hsvziggoins.pgdat	=	pgdat;
hsvziggoins.pen	=	pen;
hsvziggoins.pmp	=	pmp;
hsvziggoins.Timerclk	=	Timerclk;
hsvziggoins.ctrl	=	ctrl;
hsvziggoins.strapi	=	strapi;
hsvziggoins.pgdb	=	pgdb;
hsvziggoins.insN	=	m.hsvziggoins_insN;
hsvziggoins.sort	=	mroute.isort;
hsvziggoins.pgdbconst	=	pgdbconst;
hsvziggoins.eurdiv	=	eurdiv;
hsvziggoins.feapi	=	feapi;
hsvziggoins.wnddest	=	wnddest;
hsvziggoins.srtdbids	=	srtdbids;
hsvziggoins.srtdb	=	srtdb;
hsvziggoins.plfres	=	plfres;
hsvziggoins.plferrids	=	plferrids;
hsvziggoins.hsverr	=	err;
hsvziggoins.sysset	=	sysset;
hsvziggoins.dvbset	=	hsvdvbcins.dvbset;
hsvziggoins.sigstr	=	msigstr.sigstr;
hsvziggoins.mctl	=	mctl;
hsvziggoins.instutil	=	msysctl.instutil;
hsvziggoins.pgsel	=	pgsel;
hsvziggoins.rtk	=	rtk;
hsvziggoins.chanret	=	chanlibret;
hsvziggoins.strmfltr = strmfltr;
hsvcanaldigitalins.rins	=	m.pins;
hsvcanaldigitalins.pgdat	=	pgdat;
hsvcanaldigitalins.pen	=	pen;
hsvcanaldigitalins.pmp	=	pmp;
hsvcanaldigitalins.Timerclk	=	Timerclk;
hsvcanaldigitalins.ctrl	=	ctrl;
hsvcanaldigitalins.strapi	=	strapi;
hsvcanaldigitalins.pgdb	=	pgdb;
hsvcanaldigitalins.insN	=	m.hsvcanaldigitalins_insN;
hsvcanaldigitalins.sort	=	mroute.isort;
hsvcanaldigitalins.pgdbconst	=	pgdbconst;
hsvcanaldigitalins.eurdiv	=	eurdiv;
hsvcanaldigitalins.feapi	=	feapi;
hsvcanaldigitalins.wnddest	=	wnddest;
hsvcanaldigitalins.srtdbids	=	srtdbids;
hsvcanaldigitalins.srtdb	=	srtdb;
hsvcanaldigitalins.plfres	=	plfres;
hsvcanaldigitalins.plferrids	=	plferrids;
hsvcanaldigitalins.hsverr	=	err;
hsvcanaldigitalins.sysset	=	sysset;
hsvcanaldigitalins.dvbset	=	hsvdvbcins.dvbset;
hsvcanaldigitalins.sigstr	=	msigstr.sigstr;
hsvcanaldigitalins.mctl	=	mctl;
hsvcanaldigitalins.instutil	=	msysctl.instutil;
hsvcanaldigitalins.pgsel	=	pgsel;
hsvcanaldigitalins.rtk	=	rtk;
hsvcanaldigitalins.chanret	=	chanlibret;
hsvcanaldigitalins.strmfltr = strmfltr;
hsvdvbcamins.str	=	str;
hsvdvbcamins.ling = ling;
hsvdvbcamins.rins = m.pins;
hsvdvbcamins.pgdat	=	pgdat;
hsvdvbcamins.pen	=	pen;
hsvdvbcamins.pmp	=	pmp;
hsvdvbcamins.Timerclk	=	Timerclk;
hsvdvbcamins.ctrl	=	ctrl;
hsvdvbcamins.strapi	=	strapi;
hsvdvbcamins.pgdb	=	pgdb;
hsvdvbcamins.insN	=	m.hsvdvbcamins_insN;
hsvdvbcamins.sort	=	mcamsort.icamsort;
hsvdvbcamins.pgdbconst	=	pgdbconst;
hsvdvbcamins.eurdiv	=	eurdiv;
hsvdvbcamins.feapi	=	feapi;
hsvdvbcamins.wnddest	=	wnddest;
hsvdvbcamins.srtdbids	=	srtdbids;
hsvdvbcamins.srtdb	=	srtdb;
hsvdvbcamins.plfres	=	plfres;
hsvdvbcamins.plferrids	=	plferrids;
hsvdvbcamins.hsverr	=	err;
hsvdvbcamins.sysset	=	sysset;
hsvdvbcamins.sigstr	=	msigstr.sigstr;
hsvdvbcamins.mctl	=	mctl;
hsvdvbcamins.camena	=	camena;
hsvdvbcamins.chdecdvbt2	=	chdecdvbt2;
hsvdvbcamins.cids	=	cids;
hsvdvbcamins.charsetutil = charsetutil;
opinsN	=	hsvdvbcamins.opinsN;
hsvdvbcamins.opins	=	opins;
hsvdvbcamins.camScanparser = camScanparser;
msort.pen	=	pen;
msort.pmp	=	pmp;
msort.rins	=	m.pins;
msort.sortN	=	m.sortN;
msort.hsvdvbtins_inscountry	=	hsvdvbtins.inscountry;
msort.pgdb	=	pgdb;
msort.pgdbconst	=	pgdbconst;
msort.pgdat	=	pgdat;
msort.div	=	div;
msort.sysset	=	sysset;
msort.cids	=	cids;
msort.nvmapps	=	nvmapps;
msort.nvmcesvc	=	nvmcesvc;
msort.nvmtxt	=	nvmtxt;
msort.apperr	=	apperr;
msort.iadvpgitr	=	madvpgitr.iadvpgitr;
msort.memo	=	memo;
msort.freqctl	=	mfreqctl.freqctl;
msort.divsupp	=	m.divsupp;
msort.eurdiv	=	eurdiv;
mDbookSort.pen	=	pen;
mDbookSort.pmp	=	pmp;
mDbookSort.rins	=	m.pins;
mDbookSort.sortN	=	m.sortN;
mDbookSort.hsvdvbtins_inscountry	=	hsvdvbtins.inscountry;
mDbookSort.instutil	=	msysctl.instutil;
mDbookSort.pgdb	=	pgdb;
mDbookSort.pgdbconst	=	pgdbconst;
mDbookSort.pgdat	=	pgdat;
mDbookSort.div	=	div;
mDbookSort.sysset	=	sysset;
mDbookSort.cids	=	cids;
mDbookSort.nvmapps	=	nvmapps;
mDbookSort.nvmcesvc	=	nvmcesvc;
mDbookSort.nvmtxt	=	nvmtxt;
mDbookSort.iadvpgitr	=	madvpgitr.iadvpgitr;
mDbookSort.memo	=	memo;
mDbookSort.freqctl	=	mfreqctl.freqctl;
mDbookSort.divsupp	=	m.divsupp;
mDbookSort.eurdiv	=	eurdiv;
mDbookSort.idbookconf	=	mDbookConflicts.idbookconf;
mDbookSort.wnddest	=	wnddest;
mDbookSort.feapi	=	feapi;
mDbookSort.hsvprins_prins = hsvprins.prins;
mDbookSort.hsvdvbtins_dvbset	=	hsvdvbtins.dvbset;
m.idbookconf	=	mDbookConflicts.idbookconf;
mpegsort.pmp	=	pmp;
mpegsort.pen	=	pen;
mpegsort.rins	=	m.pins;
mpegsort.sortN	=	m.sortN;
mpegsort.log	=	log;
mpegsort.instutil	=	msysctl.instutil;
mpegsort.pgdb	=	pgdb;
mpegsort.pgdbconst	=	pgdbconst;
mpegsort.div	=	div;
mpegsort.nvmapps	=	nvmapps;
mpegsort.nvmcesvc	=	nvmcesvc;
mpegsort.nvmtxt	=	nvmtxt;
mpegsort.apperr	=	apperr;
mpegsort.iadvpgitr	=	madvpgitr.iadvpgitr;
mpegsort.eurdiv	=	eurdiv;
mpegsort.freqctl	=	mfreqctl.freqctl;
msigstr.instutil	=	msysctl.instutil;
msigstr.feapi	=	feapi;
msigstr.err	=	err;
msigstr.log	=	log;
msigstr.rins	=	m.pins;
msigstr.wnddest	=	wnddest;
mfreqctl.feapi	=	feapi;
mfreqctl.rins	=	m.pins;
mfreqctl.insN	=	insN;
mfreqctl.wnddest	=	wnddest;
mfreqctl.eurdiv	=	eurdiv;
mfreqctl.sysset	=	sysset;
msysctl.actl	=	actl;
msysctl.vctl	=	vctl;
msysctl.destconfig	=	destconfig;
msysctl.div	=	div;
msysctl.log	=	log;
mcabsort.pgdb	=	pgdb;
mcabsort.pgdbconst	=	pgdbconst;
mcabsort.sortN	=	m.sortN;
mcabsort.rins	=	m.pins;
mcabsort.div	=	div;
mcabsort.pgdat	=	pgdat;
mcabsort.nvmapps	=	nvmapps;
mcabsort.nvmcesvc	=	nvmcesvc;
mcabsort.nvmtxt	=	nvmtxt;
mcabsort.cids	=	cids;
mcabsort.apperr	=	apperr;
mcabsort.iadvpgitr	=	madvpgitr.iadvpgitr;
mcabsort.memo	=	memo;
mcabsort.feapi	=	feapi;
mcabsort.pmp	=	pmp;
mcabsort.pen	=	pen;
mcabsort.rtk	=	rtk;
mcabsort.wnddest	=	wnddest;
mcabsort.ffsdir	=	ffsdir;
mcabsort.str	=	str;
mcabsort.eurdiv	=	eurdiv;
mcabsort.hsvdvbcins_digacq	=	hsvdvbcins.digacq;
mcabsort.sysset	=	sysset;

mblizoosort.cids	=	cids;
mblizoosort.div	=	div;
mblizoosort.eurdiv	=	eurdiv;
mblizoosort.feapi	=	feapi;
mblizoosort.pen	=	pen;
mblizoosort.pgdat	=	pgdat;
mblizoosort.pgdb	=	pgdb;
mblizoosort.pgdbconst	=	pgdbconst;
mblizoosort.pmp	=	pmp;
mblizoosort.rins	=	m.pins;
mblizoosort.rtk	=	rtk;
mblizoosort.sortN	=	m.sortN;
mblizoosort.str	=	str;
mblizoosort.sysset	=	sysset;
mblizoosort.wnddest	=	wnddest;
mblizoosort.hsvprins_prins	= hsvprins.prins;
mblizoosort.hsvdvbcins_dvbset	=	hsvdvbcins.dvbset;

mlitesort.pmp	=	pmp;
mlitesort.pen	=	pen;
mlitesort.rins	=	m.pins;
mlitesort.pgitr	=	pgitr;
mlitesort.pgdb	=	pgdb;
mlitesort.pgdat	=	pgdat;
mlitesort.pgdbconst	=	pgdbconst;
mlitesort.sortN	=	m.sortN;
mlitesort.div	=	div;
mlitesort.freqctl	=	mfreqctl.freqctl;
mlitesort.eurdiv	=	eurdiv;
mlitesort.nvmapps	=	nvmapps;
mlitesort.nvmcesvc	=	nvmcesvc;
mlitesort.nvmtxt	=	nvmtxt;
mlitesort.err	=	err;
mlitesort.log	=	log;
mlitesort.instutil	=	msysctl.instutil;
mlitesort.apperr	=	apperr;
mlitesort.feapi	=	feapi;
mlitesort.wnddest	=	wnddest;
mlitesort.iadvpgitr	=	madvpgitr.iadvpgitr;
mcabsort.hsvdvbcins_dvbset	=	hsvdvbcins.dvbset;
mcabsort.divsupp	=	m.divsupp;
mlitesort.ffsdir	=	ffsdir;
mlitesort.str	=	str;
mlitesort.cids	=	cids;
mlitesort.sysset	=	sysset;
mnorsort.pmp	=	pmp;
mnorsort.pen	=	pen;
mnorsort.rins	=	m.pins;
mnorsort.pgitr	=	pgitr;
mnorsort.pgdb	=	pgdb;
mnorsort.pgdat	=	pgdat;
mnorsort.pgdbconst	=	pgdbconst;
mnorsort.sortN	=	m.sortN;
mnorsort.div	=	div;
mnorsort.cids	=	cids;
mnorsort.feapi	=	feapi;
mnorsort.freqctl	=	mfreqctl.freqctl;
mnorsort.eurdiv	=	eurdiv;
mnorsort.nvmapps	=	nvmapps;
mnorsort.nvmcesvc	=	nvmcesvc;
mnorsort.nvmtxt	=	nvmtxt;
mnorsort.err	=	err;
mnorsort.log	=	log;
mnorsort.instutil	=	msysctl.instutil;
mnorsort.wnddest	=	wnddest;
mnorsort.hsvdvbtins_dvbset	=	hsvdvbtins.dvbset;
mnorsort.iadvpgitr	=	madvpgitr.iadvpgitr;
mnorsort.apperr	=	apperr;
mnorsort.sysset	=	sysset;
mitasort.pmp	=	pmp;
mitasort.pen	=	pen;
mitasort.rins	=	m.pins;
mitasort.pgitr	=	pgitr;
mitasort.pgdb	=	pgdb;
mitasort.pgdat	=	pgdat;
mitasort.pgdbconst	=	pgdbconst;
mitasort.sortN	=	m.sortN;
mitasort.div	=	div;
mitasort.cids	=	cids;
mitasort.feapi	=	feapi;
mitasort.freqctl	=	mfreqctl.freqctl;
mitasort.eurdiv	=	eurdiv;
mitasort.nvmapps	=	nvmapps;
mitasort.nvmcesvc	=	nvmcesvc;
mitasort.nvmtxt	=	nvmtxt;
mitasort.err	=	err;
mitasort.wnddest	=	wnddest;
mitasort.hsvdvbtins_dvbset	=	hsvdvbtins.dvbset;
mitasort.iadvpgitr	=	madvpgitr.iadvpgitr;
mitasort.apperr	=	apperr;
mitasort.iconf	=	mconflicts.iconf;
mitasort.sysset	=	sysset;
mconflicts.iconfN	=	mitasort.iconfN;
mconflicts.rins	=	m.pins;
mconflicts.pgdb	=	pgdb;
mconflicts.pmp	=	pmp;
mconflicts.pen	=	pen;
mconflicts.pgdbconst	=	pgdbconst;
mconflicts.div	=	div;
mconflicts.memo	=	memo;
mconflicts.insN	=	insN;
mconflicts.cids	=	cids;
mconflicts.sysset	=	sysset;
mDbookConflicts.idbookconfN	=	mDbookSort.idbookconfN;
mDbookConflicts.rins	=	m.pins;
mDbookConflicts.pgdb	=	pgdb;
mDbookConflicts.pmp	=	pmp;
mDbookConflicts.pen	=	pen;
mDbookConflicts.pgdbconst	=	pgdbconst;
mDbookConflicts.cids	=	cids;
mDbookConflicts.sysset	=	sysset;
mDbookConflicts.hsvdvbtins_dvbset	=	hsvdvbtins.dvbset;
mDbookConflicts.hsvdvbtins_digacq	=	hsvdvbtins.digacq;
mDbookConflicts.hpool	=	hpool;
mfinsort.pen	=	pen;
mfinsort.pmp	=	pmp;
mfinsort.rins	=	m.pins;
mfinsort.sortN	=	m.sortN;
mfinsort.hsvdvbtins_inscountry	=	hsvdvbtins.inscountry;
mfinsort.pgdb	=	pgdb;
mfinsort.pgdbconst	=	pgdbconst;
mfinsort.pgdat	=	pgdat;
mfinsort.div	=	div;
mfinsort.sysset	=	sysset;
mfinsort.cids	=	cids;
mfinsort.nvmapps	=	nvmapps;
mfinsort.nvmcesvc	=	nvmcesvc;
mfinsort.nvmtxt	=	nvmtxt;
mfinsort.apperr	=	apperr;
mfinsort.iadvpgitr	=	madvpgitr.iadvpgitr;
mfinsort.memo	=	memo;
mfinsort.freqctl	=	mfreqctl.freqctl;
mfinsort.divsupp	=	m.divsupp;
mfinsort.eurdiv	=	eurdiv;
mcamsort.nvmapps	=	nvmapps;
mcamsort.nvmcesvc	=	nvmcesvc;
mcamsort.nvmtxt	=	nvmtxt;
mcamsort.pgdb	=	pgdb;
mcamsort.pgdbconst	=	pgdbconst;
mcamsort.pgdat	=	pgdat;
mcamsort.pen	=	pen;
mcamsort.pmp	=	pmp;
mcamsort.sortN	=	m.sortN;
mapmeasort.pmp	=	pmp;
mapmeasort.pen	=	pen;
mapmeasort.rins	=	m.pins;
mapmeasort.pgitr	=	pgitr;
mapmeasort.pgdb	=	pgdb;
mapmeasort.pgdat	=	pgdat;
mapmeasort.pgdbconst	=	pgdbconst;
mapmeasort.sortN	=	m.sortN;
mapmeasort.div	=	div;
mapmeasort.freqctl	=	mfreqctl.freqctl;
mapmeasort.eurdiv	=	eurdiv;
mapmeasort.nvmapps	=	nvmapps;
mapmeasort.nvmcesvc	=	nvmcesvc;
mapmeasort.nvmtxt	=	nvmtxt;
mapmeasort.err	=	err;
mapmeasort.log	=	log;
mapmeasort.instutil	=	msysctl.instutil;
mapmeasort.apperr	=	apperr;
mapmeasort.feapi	=	feapi;
mapmeasort.wnddest	=	wnddest;
mapmeasort.iadvpgitr	=	madvpgitr.iadvpgitr;
mapmeasort.sysset	=sysset;
mapmeasort.divsupp	=	m.divsupp;
mapmeasort.hsvdvbtins_inscountry	=	hsvdvbtins.inscountry;
mapmeasort.hsvprins_prins	= hsvprins.prins;
mhungarysort.pmp	=	pmp;
mhungarysort.pen	=	pen;
mhungarysort.rins	=	m.pins;
mhungarysort.pgitr	=	pgitr;
mhungarysort.pgdb	=	pgdb;
mhungarysort.pgdat	=	pgdat;
mhungarysort.pgdbconst	=	pgdbconst;
mhungarysort.sortN	=	m.sortN;
mhungarysort.div	=	div;
mhungarysort.freqctl	=	mfreqctl.freqctl;
mhungarysort.eurdiv	=	eurdiv;
mhungarysort.nvmapps	=	nvmapps;
mhungarysort.nvmcesvc	=	nvmcesvc;
mhungarysort.nvmtxt	=	nvmtxt;
mhungarysort.err	=	err;
mhungarysort.log	=	log;
mhungarysort.instutil	=	msysctl.instutil;
mhungarysort.apperr	=	apperr;
mhungarysort.feapi	=	feapi;
mhungarysort.wnddest	=	wnddest;
mhungarysort.iadvpgitr	=	madvpgitr.iadvpgitr;
mhungarysort.sysset	=sysset;
mhungarysort.divsupp	=	m.divsupp;
mhungarysort.hsvdvbtins_inscountry	=	hsvdvbtins.inscountry;
mhungarysort.hsvprins_prins	= hsvprins.prins;


ins	=	m.pins;
strapiN	=	m.strapiN;
m.tstrapiN	=	hsvdvbtins.strapiN;
m.cstrapiN	=	hsvdvbcins.strapiN;
m.mpegstrapiN	=	hsvdvbtmpegins.strapiN;
m.hsvziggoins_strapiN	=	hsvziggoins.strapiN;
m.hsvcanaldigitalins_strapiN	=	hsvcanaldigitalins.strapiN;
m.strapi	=	strapi;
m.hsvdvbcamins_strapiN	=	hsvdvbcamins.strapiN;
freqlistconf	=	hsvdvbtins.freqlistconf;
ctrlN	=	m.ctrlN;
m.tctrlN	=	hsvdvbtins.ctrlN;
m.cctrlN	=	hsvdvbcins.ctrlN;
m.hsvziggoins_ctrlN	=	hsvziggoins.ctrlN;
m.hsvcanaldigitalins_ctrlN	=	hsvcanaldigitalins.ctrlN;
m.hsvdvbtmpegins_ena	=	hsvdvbtmpegins.ena;
m.hsvdvbtins_ena	=	hsvdvbtins.ena;
m.hsvdvbcins_ena	=	hsvdvbcins.ena;
m.hsvdvbtins_afitr	=	hsvdvbtins.afitr;
afitr	=	hsvdvbtins.afitr;
afscanN	=	m.iafscanN;
hsvdvbtins.afscanN	=	m.iafscanN;
madvpgitr.apperr	=	apperr;
madvpgitr.pgdb	=	pgdb;
madvpgitr.pgitr	=	pgitr;
madvpgitr.srtdb	=	srtdb;
dvbset	=	hsvdvbcins.dvbset;
madvpgitr.srtdbids	=	srtdbids;
madvpgitr.pgdbconst	=	pgdbconst;
mSortRoute.idvbtsort	=	msort.idvbtsort;
mSortRoute.idvbtapmeasort	=	mapmeasort.idvbtapmeasort;
mSortRoute.idvbthungarysort	=	mhungarysort.idvbthungarysort;
mSortRoute.iblizoosort	=	mblizoosort.iblizoosort;
mSortRoute.idbooksort	=	mDbookSort.idbooksort;
mSortRoute.idvbtlitesort	=	mpegsort.idvbtlitesort;
mSortRoute.idvbcsort	=	mcabsort.idvbcsort;
mSortRoute.idvbclitesort	=	mlitesort.idvbclitesort;
mSortRoute.inorsort	=	mnorsort.inorsort;
mSortRoute.itasort	=	mitasort.itasort;
mSortRoute.ifinsort	=	mfinsort.ifinsort;
mSortRoute.rins	=	m.pins;
mSortRoute.cids	=	cids;
mSortRoute.eurdiv	=	eurdiv;
mSortRoute.sysset	=	sysset;
mroute.isortroute	=	mSortRoute.isortroute;
mroute.idvbtsort	=	msort.idvbtsort;
mroute.idvbcsort	=	mcabsort.idvbcsort;
mroute.inorsort	=	mnorsort.inorsort;
mroute.idvbclitesort	=	mlitesort.idvbclitesort;
mroute.idvbtlitesort	=	mpegsort.idvbtlitesort;
mroute.itasort	=	mitasort.itasort;
mroute.idbooksort	=	mDbookSort.idbooksort;
mroute.ifinsort	=	mfinsort.ifinsort;
mroute.istubsort	=	mSortRoute.istubsort;
mroute.idvbtapmeasort	=	mapmeasort.idvbtapmeasort;
mroute.idvbthungarysort	=	mhungarysort.idvbthungarysort;
mroute.iblizoosort	=	mblizoosort.iblizoosort;
m.pginsN = svpaci.pginsN;
}

};

#endif

