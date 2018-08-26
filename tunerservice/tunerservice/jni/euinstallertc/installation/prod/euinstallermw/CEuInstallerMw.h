#ifndef  _CEUINSTALLERMW_H
#define  _CEUINSTALLERMW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CEuInstallerMw_mpow.h>
#include <CHsvDvbStreamingDataManager.h>
#include <CHsvEuropeInstallation.h>
#include <CHsvFrontEnd.h>
#include <CHsvProgramData.h>
#include <CHsvUtil.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IPlfApiTuningNotify.h>
#include <IHsvDemuxNotify.h>
#include <IHsvInstallation2.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvPower.h>
#include <IProdApiClockEx.h>
#include <IHsvTxtPageAccess.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IPlfApiChanDec.h>
#include <IPlfApiChanDecDvbC.h>
#include <IPlfApiChanDecDvbT.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvTsvChannelName.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <IHsvTxtPageConvert.h>
#include <ITvColorDecode2.h>
#include <IPumpEngine.h>
#include <IHsvTxtDecode.h>
#include <IHsvDestinationConfiguration.h>
#include <IHsvUtilDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvTxtDisplayDriver.h>
#include <ITxtDisplayDriver3.h>
#include <IEnable.h>
#include <IDateTime.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IPlfApiTuning.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvTextDisplay.h>
#include <IHsvPool.h>
#include <IHsvInstallationNotify.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvLastActivityNotify.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IHsvMemoryPool.h>
#include <IMemoryOperations.h>
#include <IHsvMpegControlNotify.h>
#include <IHsvMpegSectionsNotify.h>
#include <IHsvDvbMplDiv.h>
#include <IHsvCookieNvmInfo.h>
#include <IAppApiChannelLibNvmIds.h>
#include <IProdApiNvmProtectedAccessExEx.h>
#include <ICesOperatorProfile.h>
#include <IHsvTxtPacket830Data.h>
#include <IHsvProgramDataControl.h>
#include <IHsvProgramDataControl3.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvProgramDataNotifyExEx.h>
#include <IHsvProgramDataNotifyExExEx.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvProgramDataDiv.h>
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
#include <IHsvSdmDiv.h>
#include <IHsvDemuxSectionFilter2.h>
#include <IHsvSourceSetup.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IString.h>
#include <IHsvStreamFilterNotify.h>
#include <IProdApiNvmSubIdsEx.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvSystemSettings.h>
#include <IHsvTcSystemSettingsEx.h>
#include <IInfraTimerServer.h>
#include <IHsvTxtPresent.h>
#include <ISvcVideoControl3.h>
#include <ITvVideoProperties3Ex.h>
#include <IHsvTxtVpsData.h>
#include <IHsvWindowDestinationMap.h>
#include <IPlfApiVbi.h>
#include <IPlfProxy.h>
#include <IPlfProxyNotify.h>
#include <android/log.h>
#include <IHsvAciDisplay.h>
#include <IHsvSystemSettingsNotifyEx.h>

class CEuInstallerMw
{
public:
virtual ~CEuInstallerMw(){}

//Contained Modules
private:
CEuInstallerMw_mpow mpow;
//Contained Components
private:
CHsvDvbStreamingDataManager hsvdvbsdm;
CHsvEuropeInstallation hsveuins;
CHsvFrontEnd hsvfe;
CHsvProgramData hsvpgdat;
CHsvUtil hsvutil;
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IPlfApiTuningNotify>	fetunN;

ProvidesInterface<IHsvDemuxNotify>	hsvdmxN;

ProvidesInterface<IHsvInstallation2>	ins;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;
ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSourceSetupNotify>	srcstpN;
ProvidesInterface<IPlfProxyNotify>			plfProxyN;
ProvidesInterface<IHsvAciDisplay>			acids;
ProvidesInterface<IHsvSystemSettingsNotifyEx> syssetExN;


//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvTxtPageAccess>	acc;
RequiresInterface<ISvcAudioControl4ExEx>	actl;
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IPlfApiSigStrengthMeas>	assm;
RequiresInterface<IHsvChannelLibReturnCodes>	chanlibret;
RequiresInterface<IPlfApiChanDec>	chdec;
RequiresInterface<IPlfApiChanDecDvbC>	chdecC;
RequiresInterface<IPlfApiChanDecDvbT>	chdecT;
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvTsvChannelName>	chlname;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<ICesCityIds>	cityids;
RequiresInterface<IHsvTxtPageConvert>	cnv;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvTxtDecode>	dec;
RequiresInterface<IHsvDestinationConfiguration>	destconfig;
RequiresInterface<IHsvUtilDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvPower>	dmxpow;
RequiresInterface<IHsvTxtDisplayDriver>	dsdrv;
RequiresInterface<ITxtDisplayDriver3>	dsdrv3;
RequiresInterface<IEnable>	dsenb;
RequiresInterface<IDateTime>	dt;
RequiresInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IPlfApiTuning>	fetun;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvTextDisplay>	gfxtxt;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvPresetInstallationDiv>	insdiv;
RequiresInterface<IHsvErrorCodeEx>	inserr;
RequiresInterface<IHsvLastActivityNotify>	instlaN;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IHsvMemoryPool>	mem;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvMpegControlNotify>	mpegN;
RequiresInterface<IHsvMpegSectionsNotify>	mpegsecnN;
RequiresInterface<IHsvDvbMplDiv>	mpldiv;
RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
RequiresInterface<IAppApiChannelLibNvmIds>	nvmids;
RequiresInterface<IProdApiNvmProtectedAccessExEx>	nvmpa;
RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<IHsvTxtPacket830Data>	p830;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDataControl>	pgctl;
RequiresInterface<IHsvProgramDataControl3>	pgctl3;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvProgramDataNotifyExEx>	pgdatNxx;
RequiresInterface<IHsvProgramDataNotifyExExEx>	pgdatNxxx;
RequiresInterface<IHsvChanlibPosixLight>	pgdatrtk;
RequiresInterface<IHsvProgramDataDiv>	pgdiv;
RequiresInterface<IHsvProgramIterator>	pgitr;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IHsvTxtPacket0>	pkt0;
RequiresInterface<IPlfApiDesignatorId>	plfdesigid;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPlfApiSourceId>	plfsrcid;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<ISvcPowerStateControlEx>	powctlx;
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IHsvTxtPageRequest>	req;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSdmDiv>	sdmdiv;
RequiresInterface<IHsvDemuxSectionFilter2>	secfltr;
RequiresInterface<IHsvSourceSetup>	srcstp;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IProdApiNvmSubIdsEx>	subid;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IAppApiSystemSettings5>	sysset5;
RequiresInterface<IHsvTcSystemSettingsEx>	syssetx;
RequiresInterface<IInfraTimerServer>	tmr;
RequiresInterface<IHsvTxtPresent>	txtpre;
RequiresInterface<ISvcVideoControl3>	vctl;
RequiresInterface<ITvVideoProperties3Ex>	vip;
RequiresInterface<IHsvTxtVpsData>	vps;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddestmap;
RequiresInterface<ITvColorDecode2>	xcol;
RequiresInterface<IPlfApiVbi>		plfvbi;
RequiresInterface<IEnable>			dcu;
RequiresInterface<IPlfProxy>		plfproxy;
RequiresInterface<IHsvPower>		txtpow;


private:
Pumpdefines(CEuInstallerMw);
DEMUX_DEFINES(CEuInstallerMw,secfltr);

public:
CEuInstallerMw()
{
__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerMw"," Entering constructor ");
fetunN	=	hsvfe.fetunN;
srcstpN = hsveuins.srcstpN;
acids 	= hsveuins.acids;
pow	=	mpow.pow;
mpow.txtpow = txtpow;
mpow.hsveuins_pow	=	hsveuins.pow;
mpow.hsvfe_pow	=	hsvfe.pow;
mpow.hsvpgdat_pow	=	hsvpgdat.pow;
mpow.hsvdvbsdm_pow	=	hsvdvbsdm.pow;
hsvdvbsdm.ins	=	hsveuins.ins;
hsvdvbsdm.ctrlN	=	hsveuins.ctrlN;
hsvdvbsdm.strapiN	=	hsveuins.strapiN;
hsvdvbsdm.charsetutil	=	hsvutil.charsetutil;
hsvdvbsdm.charsetutil2	=	hsvutil.charsetutil2;
hsveuins.charsetutil = hsvutil.charsetutil2;
hsvutil.div	=	div;
hsvutil.cids	=	cids;
ins	=	hsveuins.ins;
hsvutil.sysset	=	sysset;
hsvdvbsdm.pmp	=	pmp;
hsvdvbsdm.pen	=	pen;
hsvdvbsdm.ctrlpen	=	ctrlpen;
hsvdvbsdm.rtk	=	rtk;
hsvdvbsdm.dt	=	dt;
hsvdvbsdm.cids	=	cids;
hsvdvbsdm.sysset5	=	sysset5;
hsvpgdat.nvmids	=	nvmids;
hsvpgdat.subid	=	subid;
hsvpgdat.nvmpa	=	nvmpa;
hsvdvbsdm.srtdb2	=	srtdb2;
hsvdvbsdm.srtdbids	=	srtdbids;
hsvdvbsdm.dvbsrtdbids	=	dvbsrtdbids;
hsvdvbsdm.pgdat	=	hsvpgdat.pgdat3;
hsvpgdat.pgctl	=	pgctl;
hsvpgdat.pgctl3	=	pgctl3;
hsvpgdat.insN	= 	insN;
hsvpgdat.srtdb2 = 	srtdb2;
hsvpgdat.srtdbids	=	dvbsrtdbids;
hsvpgdat.sysset	=	sysset;
hsvdvbsdm.div	=	sdmdiv;
hsvdvbsdm.mpegsecnN	=	mpegsecnN;
hsvdvbsdm.strmfltrN	=	strmfltrN;
hsvdvbsdm.mpegN	=	mpegN;
hsvdmxN	=	hsvdvbsdm.hsvdmxN;
dmxsecfN	=	hsvdvbsdm.dmxsecfN;
hsvpgdat.ffsdir	=	ffsdir;
hsvpgdat.err	=	err;
hsvdvbsdm.pgsel	=	pgsel;
hsvdvbsdm.eurdiv	=	eurdiv;
hsvdvbsdm.sysset	=	sysset;
hsvpgdat.div	=	pgdiv;
hsvpgdat.sync	=	sync;
hsvpgdat.rtk	=	pgdatrtk;
hsvpgdat.corertk	=	rtk;
hsveuins.ctrl	=	hsvdvbsdm.ctrl;
hsveuins.strapi	=	hsvdvbsdm.strapi;
hsveuins.strmfltr	=	hsvdvbsdm.strmfltr;
hsvpgdat.pgdatN	=	pgdatN;
hsvpgdat.pgdatNxx	=	pgdatNxx;
hsvpgdat.pgdatNxxx	=	pgdatNxxx;
hsveuins.ling = hsvutil.ling;
hsveuins.cids	=	cids;
hsveuins.feapi	=	hsvfe.feapi;
hsveuins.destconfig	=	destconfig;
hsveuins.Timerclk	=	Timerclk;
hsveuins.hpool	=	hpool;
hsveuins.err	=	inserr;
hsveuins.apperr	=	apperr;
hsveuins.vctl	=	vctl;
hsveuins.actl	=	actl;
hsveuins.log	=	log;
hsveuins.pgdat	=	hsvpgdat.pgdat3;
hsveuins.pgdb	=	hsvpgdat.pgdb;
hsveuins.pgdbconst	=	hsvpgdat.pgdbconst;
hsveuins.pgitr	=	pgitr;
hsveuins.pgctl	=	pgctl3;
hsveuins.insN	=	insN;
hsveuins.div	=	insdiv;
hsveuins.eurdiv	=	eurdiv;
hsveuins.str	=	str;
hsveuins.sysset	=	sysset;
hsveuins.syssetx	=	syssetx;
hsveuins.memo	=	memo;
hsveuins.nvmapps	=	nvmapps;
hsveuins.nvmcesvc	=	nvmcesvc;
hsveuins.nvmtxt	=	nvmtxt;
hsveuins.mctl	=	mctl;
hsveuins.pgsel	=	pgsel;
hsveuins.wnddest	=	wnddestmap;
hsveuins.srcstp	=	srcstp;
hsveuins.plfsrcid	=	plfsrcid;
hsveuins.plfdesigid	=	plfdesigid;
hsveuins.plferrids	=	plferrids;
hsveuins.ffsdir	=	ffsdir;
hsveuins.srtdbids	=	dvbsrtdbids;
hsveuins.srtdb	=	srtdb2;
hsveuins.chanlibret	=	chanlibret;
hsveuins.cityids	=	cityids;
hsveuins.apsysset	=	apsysset;
hsveuins.powctlx	=	powctlx;
hsveuins.chdecdvbt2	=	chdecdvbt2;
hsveuins.plfres	=	plfres;
hsveuins.instlaN	=	instlaN;
hsveuins.mpldiv	=	mpldiv;
hsveuins.lngids	=	hsvdvbsdm.lngids;
hsveuins.pen	=	pen;
hsveuins.pmp	=	pmp;
hsveuins.rtk	=	rtk;
hsveuins.mem	=	mem;
hsveuins.tmr	=	tmr;
hsveuins.vip	=	vip;
hsvfe.fetun	=	fetun;
hsvfe.vssm	=	vssm;
hsvfe.qssm	=	qssm;
hsvfe.assm	=	assm;
hsvfe.chdec	=	chdec;
hsvfe.chdecT	=	chdecT;
hsvfe.chdecC	=	chdecC;
hsvfe.feapiN	=	hsveuins.feapiN;
hsvdvbsdm.dmxpow	=	dmxpow;
hsvdvbsdm.dmxena	=	dmxena;
hsvdvbsdm.secfltr	=	secfltr;
hsveuins.vps	=	vps;
hsveuins.p830	=	p830;
hsveuins.txtpre	=	txtpre;
hsveuins.chlname	=	chlname;
hsveuins.cnv	=	cnv;
hsveuins.pkt0	=	pkt0;
hsveuins.dsdrv	=	dsdrv;
hsveuins.dsdrv3	=	dsdrv3;
hsveuins.req	=	req;
hsveuins.acc	=	acc;
hsveuins.dec	=	dec;
hsveuins.dsenb	=	dsenb;
hsveuins.gfxtxt	=	gfxtxt;
hsveuins.col	=	col;
hsveuins.xcol	=	xcol;
hsveuins.camena	=	hsvdvbsdm.camena;
hsveuins.camScanparser	=	hsvdvbsdm.camScanparser;
hsveuins.opins	=	opins;
opinsN	=	hsveuins.opinsN;
__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerMw"," before plfvbi ");
hsveuins.plfvbi = plfvbi;
hsveuins.dcu 	= dcu;
__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerMw"," Before plfproxy ");
hsveuins.plfproxy = plfproxy;
plfProxyN = hsveuins.plfProxyN;
__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerMw"," Leaving constructor ");

syssetExN = hsveuins.syssetN;
}

};

#endif

