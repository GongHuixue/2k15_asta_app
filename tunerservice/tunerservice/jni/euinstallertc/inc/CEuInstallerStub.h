#ifndef  _CEUINSTALLERSTUB_H
#define  _CEUINSTALLERSTUB_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CEuInstallerStub_mdummy.h>
#include <CEuInstallerStub_mtxtstub.h>
#include <IProdApiClockEx.h>
#include <IHsvTxtPageAccess.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IPlfApiChanDec.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvTsvChannelName.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <IHsvTxtPageConvert.h>
#include <ITvColorDecode2.h>
#include <IPumpEngine.h>
#include <IHsvTxtDecode.h>
#include <IPlfApiChanDecSelect.h>
#include <IHsvDestinationConfiguration.h>
#include <IHsvUtilDiv.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvTxtDisplayDriver.h>
#include <ITxtDisplayDriver3.h>
#include <IEnable.h>
#include <IDateTime.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiChanDecDvbC.h>
#include <IPlfApiChanDecDvbT.h>
#include <IPlfApiTuning.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvTextDisplay.h>
#include <IHsvPool.h>
#include <IHsvDemuxNotify.h>
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
#include <IPlfApiTsDmxAbstractEx.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPlfApiSourceId.h>
#include <IPumpExSub.h>
#include <IHsvSdmPoolIds.h>
#include <ISvcPowerStateControlEx.h>
#include <IHsvTxtPageRequest.h>
#include <IRealTimeKernel.h>
#include <IHsvSdmDiv.h>
#include <IHsvSourceSetup.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IString.h>
#include <IHsvStreamFilterNotify.h>
#include <IProdApiNvmSubIdsEx.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvTcSystemSettingsEx.h>
#include <IHsvSystemSettings.h>
#include <IInfraTimerServer.h>
#include <ICeIsTpHostRtk2.h>
#include <IHsvTxtPresent.h>
#include <ISvcVideoControl3.h>
#include <ITvVideoProperties3Ex.h>
#include <IHsvTxtVpsData.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvInstallation2.h>
#include <IHsvTcGlobalSettings.h>
#include <IPlfApiVbi.h>
#include <IPlfApiVbiNotify.h>
#include <IHsvPower.h>
#include <CTvMwCore.h>
#include <IPlfApiAV.h>
class CEuInstallerStub
{
public:
virtual ~CEuInstallerStub(){}

//Contained Modules
private:
CEuInstallerStub_mdummy mdummy;
CEuInstallerStub_mtxtstub mtxtstub;
public:
ProvidesInterface<IProdApiClockEx>	Timerclk;

ProvidesInterface<IHsvTxtPageAccess>	acc;

ProvidesInterface<ISvcAudioControl4ExEx>	actl;

ProvidesInterface<IAppApiChannelLibReturnCodes>	apperr;

ProvidesInterface<IAppApiSystemSettings5>	apsysset;

ProvidesInterface<IHsvChannelLibReturnCodes>	chanlibret;

ProvidesInterface<IPlfApiChanDec>	chdec2;

ProvidesInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;

ProvidesInterface<IHsvTsvChannelName>	chlname;

ProvidesInterface<IHsvCountryIds>	cids;

ProvidesInterface<ICesCityIds>	cityids;

ProvidesInterface<IHsvTxtPageConvert>	cnv;

ProvidesInterface<ITvColorDecode2>	col;

ProvidesInterface<IPumpEngine>	ctrlpen;

ProvidesInterface<IHsvTxtDecode>	dec;

ProvidesInterface<IPlfApiChanDecSelect>	decsel;

ProvidesInterface<IHsvDestinationConfiguration>	destconfig;

ProvidesInterface<IHsvUtilDiv>	div;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvTxtDisplayDriver>	dsdrv;

ProvidesInterface<ITxtDisplayDriver3>	dsdrv3;

ProvidesInterface<IEnable>	dsenb;

ProvidesInterface<IDateTime>	dt;

ProvidesInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;

ProvidesInterface<IHsvChannelLibReturnCodes>	err;

ProvidesInterface<IHsvEuropeDiversity2>	eurdiv;

ProvidesInterface<IPlfApiSigStrengthMeas>	feassmx;

ProvidesInterface<IPlfApiChanDecDvbC>	fechandecdvbc;

ProvidesInterface<IPlfApiChanDecDvbT>	fechandecdvbtx;

ProvidesInterface<IPlfApiChanDec>	fechandecx;

ProvidesInterface<IPlfApiSigStrengthMeas>	feqssmx;

ProvidesInterface<IPlfApiTuning>	fetunx;

ProvidesInterface<IPlfApiSigStrengthMeas>	fevssmx;

ProvidesInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;

ProvidesInterface<IHsvTextDisplay>	gfxtxt;

ProvidesInterface<IHsvPool>	hpool;

ProvidesInterface<IHsvDemuxNotify>	hsvdmxN;

ProvidesInterface<IHsvInstallationNotify>	insN;

ProvidesInterface<IHsvPresetInstallationDiv>	insdiv;

ProvidesInterface<IHsvErrorCodeEx>	inserr;

ProvidesInterface<IHsvLastActivityNotify>	instlaN;

ProvidesInterface<IHsvLog>	log;

ProvidesInterface<IHsvMediaControl>	mctl;

ProvidesInterface<IHsvMemoryPool>	mem;

ProvidesInterface<IMemoryOperations>	memo;

ProvidesInterface<IHsvMpegControlNotify>	mpegN;

ProvidesInterface<IHsvMpegSectionsNotify>	mpegsecnN;

ProvidesInterface<IHsvDvbMplDiv>	mpldiv;

ProvidesInterface<IHsvCookieNvmInfo>	nvmapps;

ProvidesInterface<IHsvCookieNvmInfo>	nvmcesvc;

ProvidesInterface<IAppApiChannelLibNvmIds>	nvmids;

ProvidesInterface<IProdApiNvmProtectedAccessExEx>	nvmpa;

ProvidesInterface<IHsvCookieNvmInfo>	nvmtxt;

ProvidesInterface<IHsvTxtPacket830Data>	p830;

ProvidesInterface<IPumpEngine>	pen;

ProvidesInterface<IHsvProgramDataControl>	pgctl;

ProvidesInterface<IHsvProgramDataControl3>	pgctl3;

ProvidesInterface<IHsvProgramData3>	pgdat;

ProvidesInterface<IHsvProgramDataNotify>	pgdatN;

ProvidesInterface<IHsvProgramDataNotifyExEx>	pgdatNxx;

ProvidesInterface<IHsvProgramDataNotifyExExEx>	pgdatNxxx;

ProvidesInterface<IHsvChanlibPosixLight>	pgdatrtk;

ProvidesInterface<IHsvProgramDataDiv>	pgdiv;

ProvidesInterface<IHsvProgramIterator>	pgitr;

ProvidesInterface<IHsvProgramSelection2>	pgsel;

ProvidesInterface<IHsvTxtPacket0>	pkt0;

ProvidesInterface<IPlfApiDesignatorId>	plfdesigid;

ProvidesInterface<IPlfApiTsDmxAbstractEx>	plfdmx;

ProvidesInterface<IPlfApiErrorIds>	plferrids;

ProvidesInterface<ITvPlatformResource>	plfres;

ProvidesInterface<IPlfApiSourceId>	plfsrcid;

ProvidesInterface<IPumpExSub>	pmp;

ProvidesInterface<IHsvMemoryPool>	pool;

ProvidesInterface<IHsvSdmPoolIds>	poolids;

ProvidesInterface<ISvcPowerStateControlEx>	powctlx;

ProvidesInterface<IHsvTxtPageRequest>	req;

ProvidesInterface<IRealTimeKernel>	rtk;

ProvidesInterface<IHsvSdmDiv>	sdmdiv;

ProvidesInterface<IHsvSourceSetup>	srcstp;

ProvidesInterface<IHsvSortedTable2>	srtdb2;

ProvidesInterface<IHsvSdmSortedTableIds>	srtdbids;

ProvidesInterface<IString>	str;

ProvidesInterface<IHsvStreamFilterNotify>	strmfltrN;

ProvidesInterface<IProdApiNvmSubIdsEx>	subid;

ProvidesInterface<IHsvChannelLibSyncEvents>	sync;

ProvidesInterface<IHsvTcSystemSettings>	sysset;

ProvidesInterface<IAppApiSystemSettings5>	sysset5;

ProvidesInterface<IHsvTcSystemSettingsEx>	syssetx;

ProvidesInterface<IInfraTimerServer>	tmr;

ProvidesInterface<ICeIsTpHostRtk2>	tprtk;

ProvidesInterface<IHsvTxtPresent>	txtpre;

ProvidesInterface<ISvcVideoControl3>	vctl;

ProvidesInterface<ITvVideoProperties3Ex>	vip;

ProvidesInterface<IHsvTxtVpsData>	vps;

ProvidesInterface<IHsvWindowDestinationMap>	wnddestmap;

ProvidesInterface<IPlfApiVbiNotify>	  	    plfvbintf;
ProvidesInterface<IEnable>	dcu;
ProvidesInterface<IHsvPower>	txtpow;
//Required interfaces
void SetMwCoreInstance (CTvMwCore *Core)
{
	mtxtstub.SetMwCoreInstance(Core);
}
void SetGfxhandle( IGfxANWabs* gfxhandle)
{
	mtxtstub.SetGfxhandle(gfxhandle);
}
public:
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvSystemSettings>	tvcoresettings;
RequiresInterface<IHsvTcGlobalSettings>	globalSettings;
RequiresInterface<IPlfApiVbi>			plfvbi;
RequiresInterface<IPumpEngine>			rpen;
RequiresInterface<IPlfApiAV>			plfav;
RequiresInterface<IPlfApiTsDmxAbstractEx> plfApiTsDmx;

public:
CEuInstallerStub()
{
div	=	mdummy.div;
pgdiv	=	mdummy.pgdiv;
cids	=	mdummy.cids;
sysset	=	mdummy.sysset;
dvbsrtdbids	=	mdummy.dvbsrtdbids;
insdiv	=	mdummy.insdiv;
pmp	=	mdummy.pmp;
pen	=	mdummy.pen;
ctrlpen	=	mdummy.ctrlpen;
dt	=	mdummy.dt;
sysset5	=	mdummy.sysset5;
plfdmx	=	mdummy.plfdmx;
nvmids	=	mdummy.nvmids;
subid	=	mdummy.subid;
nvmpa	=	mdummy.nvmpa;
pool	=	mdummy.pool;
srtdb2	=	mdummy.srtdb2;
srtdbids	=	mdummy.srtdbids;
poolids	=	mdummy.poolids;
pgdat	=	mdummy.pgdat;
pgctl	=	mdummy.pgctl;
pgctl3	=	mdummy.pgctl3;
tprtk	=	mdummy.tprtk;
mpegsecnN	=	mdummy.mpegsecnN;
hsvdmxN	=	mdummy.hsvdmxN;
dmxsecfN	=	mdummy.dmxsecfN;
strmfltrN	=	mdummy.strmfltrN;
mpegN	=	mdummy.mpegN;
ffsdir	=	mdummy.ffsdir;
err	=	mdummy.err;
plferrids	=	mdummy.plferrids;
sync	=	mdummy.sync;
rtk	=	mdummy.rtk;
pgdatN	=	mdummy.pgdatN;
pgdatNxx	=	mdummy.pgdatNxx;
pgdatNxxx	=	mdummy.pgdatNxxx;
pgdatrtk	=	mdummy.pgdatrtk;
sdmdiv	=	mdummy.sdmdiv;
inserr	=	mdummy.inserr;
destconfig	=	mdummy.destconfig;
Timerclk	=	mdummy.Timerclk;
hpool	=	mdummy.hpool;
apperr	=	mdummy.apperr;
vctl	=	mdummy.vctl;
actl	=	mdummy.actl;
log	=	mdummy.log;
pgitr	=	mdummy.pgitr;
eurdiv	=	mdummy.eurdiv;
str	=	mdummy.str;
syssetx	=	mdummy.syssetx;
memo	=	mdummy.memo;
nvmapps	=	mdummy.nvmapps;
nvmcesvc	=	mdummy.nvmcesvc;
nvmtxt	=	mdummy.nvmtxt;
mctl	=	mdummy.mctl;
pgsel	=	mdummy.pgsel;
wnddestmap	=	mdummy.wnddestmap;
srcstp	=	mdummy.srcstp;
plfsrcid	=	mdummy.plfsrcid;
plfdesigid	=	mdummy.plfdesigid;
chanlibret	=	mdummy.chanlibret;
cityids	=	mdummy.cityids;
apsysset	=	mdummy.apsysset;
powctlx	=	mdummy.powctlx;
plfres	=	mdummy.plfres;
instlaN	=	mdummy.instlaN;
mpldiv	=	mdummy.mpldiv;
fetunx	=	mdummy.fetunx;
fevssmx	=	mdummy.fevssmx;
feassmx	=	mdummy.feassmx;
feqssmx	=	mdummy.feqssmx;
fechandecx	=	mdummy.fechandecx;
fechandecdvbtx	=	mdummy.fechandecdvbtx;
fechandecdvbc	=	mdummy.fechandecdvbc;
chdec2	=	mdummy.chdec2;
decsel	=	mdummy.decsel;
chdecdvbt2	=	mdummy.chdecdvbt2;
insN	=	mdummy.insN;
mem	=	mdummy.mem;
tmr	=	mdummy.tmr;
vip	=	mdummy.vip;
col	=	mdummy.col;
mdummy.ins	=	ins;
mdummy.tvcoresettings	= tvcoresettings;
mdummy.plfav	=	plfav;
mdummy.plfApiTsDmx = plfApiTsDmx;
vps	=	mtxtstub.vps;
p830	=	mtxtstub.p830;
txtpre	=	mtxtstub.txtpre;
chlname	=	mtxtstub.chlname;
cnv	=	mtxtstub.cnv;
pkt0	=	mtxtstub.pkt0;
dsdrv	=	mtxtstub.dsdrv;
dsdrv3	=	mtxtstub.dsdrv3;
req	=	mtxtstub.req;
acc	=	mtxtstub.acc;
dec	=	mtxtstub.dec;
dsenb	=	mtxtstub.dsenb;
gfxtxt	=	mtxtstub.gfxtxt;
mdummy.globalSettings = globalSettings;
mtxtstub.plfvbi = plfvbi;
plfvbintf = mtxtstub.plfvbintf;
dcu = mtxtstub.dcu;
txtpow = mtxtstub.txtpow;
mtxtstub.pen = rpen;
}

};

#endif

