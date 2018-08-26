#ifndef  _CEUINSTALLERSTUB_MDUMMY_PRIV_H
#define  _CEUINSTALLERSTUB_MDUMMY_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IProdApiClockEx.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IPlfApiChanDec.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <ITvColorDecode2.h>
#include <IPumpEngine.h>
#include <IPlfApiChanDecSelect.h>
#include <IHsvDestinationConfiguration.h>
#include <IHsvUtilDiv.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IDateTime.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiChanDecDvbC.h>
#include <IPlfApiChanDecDvbT.h>
#include <IPlfApiTuning.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
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
#include <IPlfApiDesignatorId.h>
#include <IPlfApiTsDmxAbstractEx.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPlfApiSourceId.h>
#include <IPumpExSub.h>
#include <IHsvSdmPoolIds.h>
#include <ISvcPowerStateControlEx.h>
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
#include <IInfraTimerServer.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <ISvcVideoControl3.h>
#include <ITvVideoProperties3Ex.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvInstallation2.h>
#include <IHsvTcGlobalSettings.h>
#include <IPlfApiAV.h>
#include <CTCMwBase.h>
class CEuInstallerStub_mdummy_Priv;
#define CLASSSCOPE CEuInstallerStub_mdummy_Priv::
#include "locals_mdummy.h"

class CEuInstallerStub_mdummy_Priv : public CTCMwBase
{
public:
virtual ~CEuInstallerStub_mdummy_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mdummy.h"
#undef MEMBERVARS
//Provided interfaces
private:
IProdApiClockExImpl(CEuInstallerStub_mdummy_Priv,Timerclk);
ISvcAudioControl4ExExImpl(CEuInstallerStub_mdummy_Priv,actl);
IAppApiChannelLibReturnCodesImpl(CEuInstallerStub_mdummy_Priv,apperr);
IAppApiSystemSettings5Impl(CEuInstallerStub_mdummy_Priv,apsysset);
IHsvChannelLibReturnCodesImpl(CEuInstallerStub_mdummy_Priv,chanlibret);
IPlfApiChanDecImpl(CEuInstallerStub_mdummy_Priv,chdec2);
IPlfApiChanDecDvbT2Impl(CEuInstallerStub_mdummy_Priv,chdecdvbt2);
IHsvCountryIdsImpl(CEuInstallerStub_mdummy_Priv,cids);
ICesCityIdsImpl(CEuInstallerStub_mdummy_Priv,cityids);
ITvColorDecode2Impl(CEuInstallerStub_mdummy_Priv,col);
IPumpEngineImpl(CEuInstallerStub_mdummy_Priv,ctrlpen);
IPlfApiChanDecSelectImpl(CEuInstallerStub_mdummy_Priv,decsel);
IHsvDestinationConfigurationImpl(CEuInstallerStub_mdummy_Priv,destconfig);
IHsvUtilDivImpl(CEuInstallerStub_mdummy_Priv,div);
IHsvDemuxSectionFilterNotifyImpl(CEuInstallerStub_mdummy_Priv,dmxsecfN);
IDateTimeImpl(CEuInstallerStub_mdummy_Priv,dt);
IHsvDvbSiSortedTableIdsImpl(CEuInstallerStub_mdummy_Priv,dvbsrtdbids);
IHsvChannelLibReturnCodesImpl(CEuInstallerStub_mdummy_Priv,err);
IHsvEuropeDiversity2Impl(CEuInstallerStub_mdummy_Priv,eurdiv);
IPlfApiSigStrengthMeasImpl(CEuInstallerStub_mdummy_Priv,feassmx);
IPlfApiChanDecDvbCImpl(CEuInstallerStub_mdummy_Priv,fechandecdvbc);
IPlfApiChanDecDvbTImpl(CEuInstallerStub_mdummy_Priv,fechandecdvbtx);
IPlfApiChanDecImpl(CEuInstallerStub_mdummy_Priv,fechandecx);
IPlfApiSigStrengthMeasImpl(CEuInstallerStub_mdummy_Priv,feqssmx);
IPlfApiTuningImpl(CEuInstallerStub_mdummy_Priv,fetunx);
IPlfApiSigStrengthMeasImpl(CEuInstallerStub_mdummy_Priv,fevssmx);
IProdApiFlashFileSystemDirectoryExExImpl(CEuInstallerStub_mdummy_Priv,ffsdir);
IHsvPoolImpl(CEuInstallerStub_mdummy_Priv,hpool);
IHsvDemuxNotifyImpl(CEuInstallerStub_mdummy_Priv,hsvdmxN);
IHsvInstallationNotifyImpl(CEuInstallerStub_mdummy_Priv,insN);
IHsvPresetInstallationDivImpl(CEuInstallerStub_mdummy_Priv,insdiv);
IHsvErrorCodeExImpl(CEuInstallerStub_mdummy_Priv,inserr);
IHsvLastActivityNotifyImpl(CEuInstallerStub_mdummy_Priv,instlaN);
IHsvLogImpl(CEuInstallerStub_mdummy_Priv,log);
IHsvMediaControlImpl(CEuInstallerStub_mdummy_Priv,mctl);
IHsvMemoryPoolImpl(CEuInstallerStub_mdummy_Priv,mem);
IMemoryOperationsImpl(CEuInstallerStub_mdummy_Priv,memo);
IHsvMpegControlNotifyImpl(CEuInstallerStub_mdummy_Priv,mpegN);
IHsvMpegSectionsNotifyImpl(CEuInstallerStub_mdummy_Priv,mpegsecnN);
IHsvDvbMplDivImpl(CEuInstallerStub_mdummy_Priv,mpldiv);
IHsvCookieNvmInfoImpl(CEuInstallerStub_mdummy_Priv,nvmapps);
IHsvCookieNvmInfoImpl(CEuInstallerStub_mdummy_Priv,nvmcesvc);
IAppApiChannelLibNvmIdsImpl(CEuInstallerStub_mdummy_Priv,nvmids);
IProdApiNvmProtectedAccessExExImpl(CEuInstallerStub_mdummy_Priv,nvmpa);
IHsvCookieNvmInfoImpl(CEuInstallerStub_mdummy_Priv,nvmtxt);
IPumpEngineImpl(CEuInstallerStub_mdummy_Priv,pen);
IHsvProgramDataControlImpl(CEuInstallerStub_mdummy_Priv,pgctl);
IHsvProgramDataControl3Impl(CEuInstallerStub_mdummy_Priv,pgctl3);
IHsvProgramData3Impl(CEuInstallerStub_mdummy_Priv,pgdat);
IHsvProgramDataNotifyImpl(CEuInstallerStub_mdummy_Priv,pgdatN);
IHsvProgramDataNotifyExExImpl(CEuInstallerStub_mdummy_Priv,pgdatNxx);
IHsvProgramDataNotifyExExExImpl(CEuInstallerStub_mdummy_Priv,pgdatNxxx);
IHsvChanlibPosixLightImpl(CEuInstallerStub_mdummy_Priv,pgdatrtk);
IHsvProgramDataDivImpl(CEuInstallerStub_mdummy_Priv,pgdiv);
IHsvProgramIteratorImpl(CEuInstallerStub_mdummy_Priv,pgitr);
IHsvProgramSelection2Impl(CEuInstallerStub_mdummy_Priv,pgsel);
IPlfApiDesignatorIdImpl(CEuInstallerStub_mdummy_Priv,plfdesigid);
IPlfApiTsDmxAbstractExImpl(CEuInstallerStub_mdummy_Priv,plfdmx);
IPlfApiErrorIdsImpl(CEuInstallerStub_mdummy_Priv,plferrids);
ITvPlatformResourceImpl(CEuInstallerStub_mdummy_Priv,plfres);
IPlfApiSourceIdImpl(CEuInstallerStub_mdummy_Priv,plfsrcid);
IPumpExSubImpl(CEuInstallerStub_mdummy_Priv,pmp);
IHsvMemoryPoolImpl(CEuInstallerStub_mdummy_Priv,pool);
IHsvSdmPoolIdsImpl(CEuInstallerStub_mdummy_Priv,poolids);
ISvcPowerStateControlExImpl(CEuInstallerStub_mdummy_Priv,powctlx);
IRealTimeKernelImpl(CEuInstallerStub_mdummy_Priv,rtk);
IHsvSdmDivImpl(CEuInstallerStub_mdummy_Priv,sdmdiv);
IHsvSourceSetupImpl(CEuInstallerStub_mdummy_Priv,srcstp);
IHsvSortedTable2Impl(CEuInstallerStub_mdummy_Priv,srtdb2);
IHsvSdmSortedTableIdsImpl(CEuInstallerStub_mdummy_Priv,srtdbids);
IStringImpl(CEuInstallerStub_mdummy_Priv,str);
IHsvStreamFilterNotifyImpl(CEuInstallerStub_mdummy_Priv,strmfltrN);
IProdApiNvmSubIdsExImpl(CEuInstallerStub_mdummy_Priv,subid);
IHsvChannelLibSyncEventsImpl(CEuInstallerStub_mdummy_Priv,sync);
IHsvTcSystemSettingsImpl(CEuInstallerStub_mdummy_Priv,sysset);
IAppApiSystemSettings5Impl(CEuInstallerStub_mdummy_Priv,sysset5);
IHsvTcSystemSettingsExImpl(CEuInstallerStub_mdummy_Priv,syssetx);
IInfraTimerServerImpl(CEuInstallerStub_mdummy_Priv,tmr);
ICeIsTpHostRtk2Impl(CEuInstallerStub_mdummy_Priv,tprtk);
ISvcVideoControl3Impl(CEuInstallerStub_mdummy_Priv,vctl);
ITvVideoProperties3ExImpl(CEuInstallerStub_mdummy_Priv,vip);
IHsvWindowDestinationMapImpl(CEuInstallerStub_mdummy_Priv,wnddestmap);
public:
ProvidesInterface<IProdApiClockEx>	Timerclk;

ProvidesInterface<ISvcAudioControl4ExEx>	actl;

ProvidesInterface<IAppApiChannelLibReturnCodes>	apperr;

ProvidesInterface<IAppApiSystemSettings5>	apsysset;

ProvidesInterface<IHsvChannelLibReturnCodes>	chanlibret;

ProvidesInterface<IPlfApiChanDec>	chdec2;

ProvidesInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;

ProvidesInterface<IHsvCountryIds>	cids;

ProvidesInterface<ICesCityIds>	cityids;

ProvidesInterface<ITvColorDecode2>	col;

ProvidesInterface<IPumpEngine>	ctrlpen;

ProvidesInterface<IPlfApiChanDecSelect>	decsel;

ProvidesInterface<IHsvDestinationConfiguration>	destconfig;

ProvidesInterface<IHsvUtilDiv>	div;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

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

ProvidesInterface<IPlfApiDesignatorId>	plfdesigid;

ProvidesInterface<IPlfApiTsDmxAbstractEx>	plfdmx;

ProvidesInterface<IPlfApiErrorIds>	plferrids;

ProvidesInterface<ITvPlatformResource>	plfres;

ProvidesInterface<IPlfApiSourceId>	plfsrcid;

ProvidesInterface<IPumpExSub>	pmp;

ProvidesInterface<IHsvMemoryPool>	pool;

ProvidesInterface<IHsvSdmPoolIds>	poolids;

ProvidesInterface<ISvcPowerStateControlEx>	powctlx;

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

ProvidesInterface<ISvcVideoControl3>	vctl;

ProvidesInterface<ITvVideoProperties3Ex>	vip;

ProvidesInterface<IHsvWindowDestinationMap>	wnddestmap;

//Required interfaces
public:
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvSystemSettings>	tvcoresettings;
RequiresInterface<IHsvTcGlobalSettings>	globalSettings;
RequiresInterface<IPlfApiAV>			plfav;
RequiresInterface<IPlfApiTsDmxAbstractEx> plfApiTsDmx;

public:
CEuInstallerStub_mdummy_Priv():i__Timerclk(this),i__actl(this),i__apperr(this),i__apsysset(this),i__chanlibret(this),i__chdec2(this),i__chdecdvbt2(this),i__cids(this),i__cityids(this),i__col(this),i__ctrlpen(this),i__decsel(this),i__destconfig(this),i__div(this),i__dmxsecfN(this),i__dt(this),i__dvbsrtdbids(this),i__err(this),i__eurdiv(this),i__feassmx(this),i__fechandecdvbc(this),i__fechandecdvbtx(this),i__fechandecx(this),i__feqssmx(this),i__fetunx(this),i__fevssmx(this),i__ffsdir(this),i__hpool(this),i__hsvdmxN(this),i__insN(this),i__insdiv(this),i__inserr(this),i__instlaN(this),i__log(this),i__mctl(this),i__mem(this),i__memo(this),i__mpegN(this),i__mpegsecnN(this),i__mpldiv(this),i__nvmapps(this),i__nvmcesvc(this),i__nvmids(this),i__nvmpa(this),i__nvmtxt(this),i__pen(this),i__pgctl(this),i__pgctl3(this),i__pgdat(this),i__pgdatN(this),i__pgdatNxx(this),i__pgdatNxxx(this),i__pgdatrtk(this),i__pgdiv(this),i__pgitr(this),i__pgsel(this),i__plfdesigid(this),i__plfdmx(this),i__plferrids(this),i__plfres(this),i__plfsrcid(this),i__pmp(this),i__pool(this),i__poolids(this),i__powctlx(this),i__rtk(this),i__sdmdiv(this),i__srcstp(this),i__srtdb2(this),i__srtdbids(this),i__str(this),i__strmfltrN(this),i__subid(this),i__sync(this),i__sysset(this),i__sysset5(this),i__syssetx(this),i__tmr(this),i__tprtk(this),i__vctl(this),i__vip(this),i__wnddestmap(this)
{
Timerclk	=	&i__Timerclk;
actl	=	&i__actl;
apperr	=	&i__apperr;
apsysset	=	&i__apsysset;
chanlibret	=	&i__chanlibret;
chdec2	=	&i__chdec2;
chdecdvbt2	=	&i__chdecdvbt2;
cids	=	&i__cids;
cityids	=	&i__cityids;
col	=	&i__col;
ctrlpen	=	&i__ctrlpen;
decsel	=	&i__decsel;
destconfig	=	&i__destconfig;
div	=	&i__div;
dmxsecfN	=	&i__dmxsecfN;
dt	=	&i__dt;
dvbsrtdbids	=	&i__dvbsrtdbids;
err	=	&i__err;
eurdiv	=	&i__eurdiv;
feassmx	=	&i__feassmx;
fechandecdvbc	=	&i__fechandecdvbc;
fechandecdvbtx	=	&i__fechandecdvbtx;
fechandecx	=	&i__fechandecx;
feqssmx	=	&i__feqssmx;
fetunx	=	&i__fetunx;
fevssmx	=	&i__fevssmx;
ffsdir	=	&i__ffsdir;
hpool	=	&i__hpool;
hsvdmxN	=	&i__hsvdmxN;
insN	=	&i__insN;
insdiv	=	&i__insdiv;
inserr	=	&i__inserr;
instlaN	=	&i__instlaN;
log	=	&i__log;
mctl	=	&i__mctl;
mem	=	&i__mem;
memo	=	&i__memo;
mpegN	=	&i__mpegN;
mpegsecnN	=	&i__mpegsecnN;
mpldiv	=	&i__mpldiv;
nvmapps	=	&i__nvmapps;
nvmcesvc	=	&i__nvmcesvc;
nvmids	=	&i__nvmids;
nvmpa	=	&i__nvmpa;
nvmtxt	=	&i__nvmtxt;
pen	=	&i__pen;
pgctl	=	&i__pgctl;
pgctl3	=	&i__pgctl3;
pgdat	=	&i__pgdat;
pgdatN	=	&i__pgdatN;
pgdatNxx	=	&i__pgdatNxx;
pgdatNxxx	=	&i__pgdatNxxx;
pgdatrtk	=	&i__pgdatrtk;
pgdiv	=	&i__pgdiv;
pgitr	=	&i__pgitr;
pgsel	=	&i__pgsel;
plfdesigid	=	&i__plfdesigid;
plfdmx	=	&i__plfdmx;
plferrids	=	&i__plferrids;
plfres	=	&i__plfres;
plfsrcid	=	&i__plfsrcid;
pmp	=	&i__pmp;
pool	=	&i__pool;
poolids	=	&i__poolids;
powctlx	=	&i__powctlx;
rtk	=	&i__rtk;
sdmdiv	=	&i__sdmdiv;
srcstp	=	&i__srcstp;
srtdb2	=	&i__srtdb2;
srtdbids	=	&i__srtdbids;
str	=	&i__str;
strmfltrN	=	&i__strmfltrN;
subid	=	&i__subid;
sync	=	&i__sync;
sysset	=	&i__sysset;
sysset5	=	&i__sysset5;
syssetx	=	&i__syssetx;
tmr	=	&i__tmr;
tprtk	=	&i__tprtk;
vctl	=	&i__vctl;
vip	=	&i__vip;
wnddestmap	=	&i__wnddestmap;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define ins_iPresent() (ins.Present())
#define ins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define ins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define ins_StIdle	IHsvInstallation2_StIdle
#define ins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define ins_StDigital	IHsvInstallation2_StDigital
#define ins_StAnalog	IHsvInstallation2_StAnalog
#define ins_StPreSorting	IHsvInstallation2_StPreSorting
#define ins_StSorting	IHsvInstallation2_StSorting
#define ins_Terrestrial	IHsvInstallation2_Terrestrial
#define ins_Cable	IHsvInstallation2_Cable
#define ins_Satellite	IHsvInstallation2_Satellite
#define ins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define ins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define ins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define ins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define ins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define ins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define ins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define ins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define ins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define ins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define ins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define ins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define ins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define ins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define ins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define ins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define ins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define ins_MaxChannel	IHsvInstallation2_MaxChannel
#define ins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define ins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define ins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define ins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define ins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define ins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define ins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define ins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define ins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define ins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define ins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define ins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define ins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define ins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define ins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define ins_InsAssm	IHsvInstallation2_InsAssm
#define ins_InsVssm	IHsvInstallation2_InsVssm
#define ins_InsQssm	IHsvInstallation2_InsQssm
#define ins_InsSssm	IHsvInstallation2_InsSssm
#define ins_StartInstallation(source,ptc,mode)	ins->StartInstallation(source,ptc,mode)
#define ins_StopInstallation()	ins->StopInstallation()
#define ins_GetNumberOfAnalogChannelsFound()	ins->GetNumberOfAnalogChannelsFound()
#define ins_GetNumberOfDigitalChannelsFound()	ins->GetNumberOfDigitalChannelsFound()
#define ins_GetNumberOfDigitalChannelsRemoved()	ins->GetNumberOfDigitalChannelsRemoved()
#define ins_GetInstallationProgress()	ins->GetInstallationProgress()
#define ins_GetInstallationStatus()	ins->GetInstallationStatus()
#define ins_GetInstallationMode()	ins->GetInstallationMode()
#define ins_IsUpdateInstallationSupported()	ins->IsUpdateInstallationSupported()
#define ins_SetInstallCountry(country)	ins->SetInstallCountry(country)
#define ins_SetSystemCountry(country)	ins->SetSystemCountry(country)
#define ins_GetFirstIntalledDigitalChannel(channelno)	ins->GetFirstIntalledDigitalChannel(channelno)
#define ins_GetFirstIntalledAnalogueChannel(channelno)	ins->GetFirstIntalledAnalogueChannel(channelno)
#define ins_GetFirstIntalledRadioChannel(channelno)	ins->GetFirstIntalledRadioChannel(channelno)
#define ins_GetFirstInstalledChannel(channelno)	ins->GetFirstInstalledChannel(channelno)
#define ins_GetNetworkNameForNetworkID(networkID,NetworkName)	ins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define ins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	ins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define ins_IsValidNetworkId(networkID)	ins->IsValidNetworkId(networkID)
#define ins_SetLowestNetworkId(networkID)	ins->SetLowestNetworkId(networkID)
#define ins_SetManualFrequency(frequency,offset,finetune)	ins->SetManualFrequency(frequency,offset,finetune)
#define ins_GetManualFrequency(frequency,offset,finetune)	ins->GetManualFrequency(frequency,offset,finetune)
#define ins_SetManualChannel(channel,finetune)	ins->SetManualChannel(channel,finetune)
#define ins_GetManualChannel(channel,finetune)	ins->GetManualChannel(channel,finetune)
#define ins_IsManualInstallationModeSupported(mode)	ins->IsManualInstallationModeSupported(mode)
#define ins_SetManualInstallationMode(mode)	ins->SetManualInstallationMode(mode)
#define ins_GetManualInstallationMode()	ins->GetManualInstallationMode()
#define ins_StoreManualInstallationValues(channel)	ins->StoreManualInstallationValues(channel)
#define ins_AutoStoreManualInstallationValues()	ins->AutoStoreManualInstallationValues()
#define ins_StartFrequencySearch()	ins->StartFrequencySearch()
#define ins_GetSigStrengthRange(measmode,min,max)	ins->GetSigStrengthRange(measmode,min,max)
#define ins_GetSignalstrength(measmode)	ins->GetSignalstrength(measmode)
#define ins_StoreWeakSignalInstallationChannel()	ins->StoreWeakSignalInstallationChannel()
#define ins_GetInstalledWeakSignalChannel()	ins->GetInstalledWeakSignalChannel()
#define ins_GetSignalQualityBer()	ins->GetSignalQualityBer()
#define ins_IsFrequencySearchDirectionSupported(searchup)	ins->IsFrequencySearchDirectionSupported(searchup)
#define ins_SetFrequencySearchDirection(searchup)	ins->SetFrequencySearchDirection(searchup)
#define ins_GetFrequencySearchDirection()	ins->GetFrequencySearchDirection()
#define ins_GetMinFrequency()	ins->GetMinFrequency()
#define ins_GetMaxFrequency()	ins->GetMaxFrequency()
#define ins_GetTunerFrequency()	ins->GetTunerFrequency()
#define ins_SetTunerFrequency(freq,fineTune)	ins->SetTunerFrequency(freq,fineTune)
#define ins_GetFrequency2Channel(chantbl,frequency)	ins->GetFrequency2Channel(chantbl,frequency)
#define ins_GetChannel2CarrierFrequency(chantbl,channel)	ins->GetChannel2CarrierFrequency(chantbl,channel)
#define ins_GetChannel2CentreFrequency(chantbl,channel)	ins->GetChannel2CentreFrequency(chantbl,channel)
#define ins_GetCurrentPass()	ins->GetCurrentPass()
#define ins_GetNoOfPass()	ins->GetNoOfPass()
#define ins_GetCurrentPassType()	ins->GetCurrentPassType()
#define ins_IsMediumSupported(medium)	ins->IsMediumSupported(medium)
#define ins_GetMedium()	ins->GetMedium()
#define ins_SetMedium(medium)	ins->SetMedium(medium)
#define ins_GetInstalledMedium()	ins->GetInstalledMedium()
#define ins_SetInstalledMedium(medium)	ins->SetInstalledMedium(medium)
#define ins_IsTvSystemSupported(tvsystem)	ins->IsTvSystemSupported(tvsystem)
#define ins_SetTvSystem(tvsystem)	ins->SetTvSystem(tvsystem)
#define ins_GetTvSystem()	ins->GetTvSystem()
#define ins_IsColorSystemSupported(colorsystem)	ins->IsColorSystemSupported(colorsystem)
#define ins_SetColorSystem(colorsystem)	ins->SetColorSystem(colorsystem)
#define ins_GetColorSystem()	ins->GetColorSystem()
#define ins_IsValidPTC(medium,PTC)	ins->IsValidPTC(medium,PTC)
#define ins_GetMinPTC(medium)	ins->GetMinPTC(medium)
#define ins_GetMaxPTC(medium)	ins->GetMaxPTC(medium)
#define ins_GetLastPTCFound()	ins->GetLastPTCFound()
#define ins_GetNumberOfPTCsFound()	ins->GetNumberOfPTCsFound()
#define ins_StartSigStrMeas(measmode)	ins->StartSigStrMeas(measmode)
#define ins_StopSigStrMeas(measmode)	ins->StopSigStrMeas(measmode)
#define ins_IsSignalStrengthMeasurementValid(measmode)	ins->IsSignalStrengthMeasurementValid(measmode)
#define ins_ScanNone	IHsvInstallation2_ScanNone
#define ins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define ins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define ins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define ins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define ins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define ins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define ins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define ins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define ins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define ins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define ins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define ins_AttributeCity	IHsvInstallation2_AttributeCity
#define ins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define ins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define ins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define ins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define ins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define ins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define ins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define ins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define ins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define ins_AttributeDualAnalogPass  IHsvInstallation2_AttributeDualAnalogPass
#define ins_AttributeDTTScanOnAnalog  IHsvInstallation2_AttributeDTTScanOnAnalog
#define ins_AttributeLCNOption  IHsvInstallation2_AttributeLCNOption
#define ins_QuickScan	IHsvInstallation2_QuickScan
#define ins_FullScan	IHsvInstallation2_FullScan
#define ins_GridScan	IHsvInstallation2_GridScan
#define ins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define ins_ManualValue	IHsvInstallation2_ManualValue
#define ins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	ins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define ins_SetAttributeMode(installationmode,attribute,attributeMode)	ins->SetAttributeMode(installationmode,attribute,attributeMode)
#define ins_SetAttribute(installationmode,attribute,value)	ins->SetAttribute(installationmode,attribute,value)
#define ins_GetAttributeMode(installationmode,attribute)	ins->GetAttributeMode(installationmode,attribute)
#define ins_GetAttribute(installationmode,attribute)	ins->GetAttribute(installationmode,attribute)
#define ins_IsAvailable(installationmode,attribute)	ins->IsAvailable(installationmode,attribute)
#define ins_ResetAttributeToDefault(installationmode,attribute)	ins->ResetAttributeToDefault(installationmode,attribute)
#define ins_ResetAttributeToPersistent(installationmode,attribute)	ins->ResetAttributeToPersistent(installationmode,attribute)
#define ins_NitNone	IHsvInstallation2_NitNone
#define ins_NitActual	IHsvInstallation2_NitActual
#define ins_NitOther	IHsvInstallation2_NitOther
#define ins_GetTargetNitType(NetworkId)	ins->GetTargetNitType(NetworkId)
#define ins_IsNetworkUpdateDetected()	ins->IsNetworkUpdateDetected()
#define ins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define ins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define ins_Initialise()	ins->Initialise()
#define ins_SkipInstallationScans(ScanTypes)	ins->SkipInstallationScans(ScanTypes)
#define ins_GetAltTSValues(ONID,TSID)	ins->GetAltTSValues(ONID,TSID)
#define ins_SetUserSymbolRates(installationmode,values,len)	ins->SetUserSymbolRates(installationmode,values,len)
#define ins_GetUserSymbolRates(installationmode,values,len)	ins->GetUserSymbolRates(installationmode,values,len)
#define ins_GetPredefinedSymbolRates(installationmode,values,len)	ins->GetPredefinedSymbolRates(installationmode,values,len)
#define ins_GetNetworkIDList()	ins->GetNetworkIDList()
#define ins_GetNetworkIDName(index,NetworkName)	ins->GetNetworkIDName(index,NetworkName)
#define ins_GetChannelListIDName(index,ChannelistName)	ins->GetChannelListIDName(index,ChannelistName)
#define ins_SetFavouriteNetworkID(mode,attrib,index)	ins->SetFavouriteNetworkID(mode,attrib,index)
#define ins_SetFavouriteRegion(mode,index,RegionType)	ins->SetFavouriteRegion(mode,index,RegionType)
#define ins_None	IHsvInstallation2_None
#define ins_Ziggo	IHsvInstallation2_Ziggo
#define ins_UPC	IHsvInstallation2_UPC
#define ins_UnityMedia	IHsvInstallation2_UnityMedia
#define ins_Kdg	IHsvInstallation2_Kdg
#define ins_Telenet	IHsvInstallation2_Telenet
#define ins_RCSRDS	IHsvInstallation2_RCSRDS
#define ins_Blizoo	IHsvInstallation2_Blizoo
#define ins_CanalDigital IHsvInstallation2_CanalDigital
#define ins_YouSee	IHsvInstallation2_YouSee
#define ins_Telemach IHsvInstallation2_Telemach
#define ins_SetUserSelectConflictService(LcnIndex,SvcIndex)	ins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define ins_ConflictsSelectionDone(UserSelection)	ins->ConflictsSelectionDone(UserSelection)
#define ins_GetConflictServices(ConflictList,NumRecords)	ins->GetConflictServices(ConflictList,NumRecords)
#define ins_GetInstallationVersion()	ins->GetInstallationVersion()
#define ins_GetInstallationState()	ins->GetInstallationState()
#define ins_GetPLPIds(PLPIds)	ins->GetPLPIds(PLPIds)
#define ins_GetRegionList(RegionsData)	ins->GetRegionList(RegionsData)
#define ins_UserSelectionDone(UserSelection)	ins->UserSelectionDone(UserSelection)
#define ins_GetFavouriteRegion(mode,RegionType)	ins->GetFavouriteRegion(mode,RegionType)
#define ins_GetStreamPriority()	ins->GetStreamPriority()
#define ins_SetStreamPriority(prio)	ins->SetStreamPriority(prio)
#define ins_GetConstellation()	ins->GetConstellation()
#define ins_GetSymbolRate()	ins->GetSymbolRate()
#define ins_GetHierarchyMode()	ins->GetHierarchyMode()
#define ins_GetEpgBarkerMux(OnId,TsId)	ins->GetEpgBarkerMux(OnId,TsId)
#define ins_ZiggoNetworkDataSet(ActionValue)	ins->ZiggoNetworkDataSet(ActionValue)
#define ins_ClearPersistent()	ins->ClearPersistent()
#define ins_GetNumberOfChannelListIds()	ins->GetNumberOfChannelListIds()
#define ins_GetChannelListIdByIndex(index)	ins->GetChannelListIdByIndex(index)
#define ins_SetFavouriteChannelListId(mode,attrib,index)	ins->SetFavouriteChannelListId(mode,attrib,index)
#define tvcoresettings_AudioFormatStandard IHsvSystemSettings_AudioFormatStandard
#define tvcoresettings_AudioFormatAdvanced IHsvSystemSettings_AudioFormatAdvanced
#define tvcoresettings_MenuLanguage IHsvSystemSettings_MenuLanguage
#define tvcoresettings_Medium IHsvSystemSettings_Medium
#define tvcoresettings_InstalledCountry IHsvSystemSettings_InstalledCountry
#define tvcoresettings_HearingImpairedType IHsvSystemSettings_HearingImpairedType
#define tvcoresettings_PreferredAudioFormat IHsvSystemSettings_PreferredAudioFormat
#define tvcoresettings_PreferredPrimaryAudioLanguage IHsvSystemSettings_PreferredPrimaryAudioLanguage
#define tvcoresettings_PreferredSecondaryAudioLanguage IHsvSystemSettings_PreferredSecondaryAudioLanguage
#define tvcoresettings_PreferredPrimarySubtitleLanguage IHsvSystemSettings_PreferredPrimarySubtitleLanguage
#define tvcoresettings_PreferredSecondarySubtitleLanguage IHsvSystemSettings_PreferredSecondarySubtitleLanguage
#define tvcoresettings_PreferredPrimaryTxtLanguage IHsvSystemSettings_PreferredPrimaryTxtLanguage
#define tvcoresettings_PreferredSecondaryTxtLanguage IHsvSystemSettings_PreferredSecondaryTxtLanguage
#define tvcoresettings_clockmode IHsvSystemSettings_clockmode
#define tvcoresettings_City IHsvSystemSettings_City
#define tvcoresettings_TimeZoneCanary IHsvSystemSettings_TimeZoneCanar
#define tvcoresettings_TimeZoneRussia IHsvSystemSettings_TimeZoneRussi
#define tvcoresettings_TimeZoneBrazil IHsvSystemSettings_TimeZoneBrazi
#define tvcoresettings_TimeZoneSpain IHsvSystemSettings_TimeZoneSpain
#define tvcoresettings_TimeZonePortugal IHsvSystemSettings_TimeZonePortugal
#define tvcoresettings_TimeZoneKazakhstan IHsvSystemSettings_TimeZoneKazakhstan
#define tvcoresettings_ParentalRatingNotify IHsvSystemSettings_ParentalRatingNotify
#define tvcoresettings_SpeechPreference IHsvSystemSettings_SpeechPreference
#define tvcoresettings_VIRouting IHsvSystemSettings_VIRouting
#define tvcoresettings_VIAudioVolume IHsvSystemSettings_VIAudioVolume
#define tvcoresettings_OriginalLanguage IHsvSystemSettings_OriginalLanguage
#define tvcoresettings_SubtitleStatus IHsvSystemSettings_SubtitleStatus
#define tvcoresettings_SoundSystem IHsvSystemSettings_SoundSystem
#define tvcoresettings_VirginBitStatus IHsvSystemSettings_VirginBitStatus
#define tvcoresettings_DVBTLiteCountry IHsvSystemSettings_DVBTLiteCountry
#define tvcoresettings_HearingImpairedOn IHsvSystemSettings_HearingImpairedOn
#define tvcoresettings_SubtitleOn IHsvSystemSettings_SubtitleOn
#define tvcoresettings_MultifeedSupported IHsvSystemSettings_MultifeedSupported
#define tvcoresettings_VisuallyImpairedOn IHsvSystemSettings_VisuallyImpairedOn
#define tvcoresettings_OADSupported IHsvSystemSettings_OADSupported
#define tvcoresettings_QADSupported IHsvSystemSettings_QADSupported
#define tvcoresettings_SubtitlePIDFallBackFirstPMT IHsvSystemSettings_SubtitlePIDFallBackFirstPMT
#define tvcoresettings_IsPreMixedVISupported IHsvSystemSettings_IsPreMixedVISupported
#define tvcoresettings_IsQASUPPORTED IHsvSystemSettings_IsQASUPPORTED
#define tvcoresettings_IsAVCDescriptorSupported IHsvSystemSettings_IsAVCDescriptorSupported
#define tvcoresettings_IsAc3AudioSupported IHsvSystemSettings_IsAc3AudioSupported
#define tvcoresettings_DefaultCharacterTable IHsvSystemSettings_DefaultCharacterTable
#define tvcoresettings_CAM1_MEDIUM IHsvSystemSettings_CAM1_MEDIUM
#define tvcoresettings_CAM2_MEDIUM IHsvSystemSettings_CAM2_MEDIUM
#define tvcoresettings_OVV_ENABLE IHsvSystemSettings_OVV_ENABLE
#define tvcoresettings_SAD_ENABLE IHsvSystemSettings_SAD_ENABLE
#define tvcoresettings_Dual_Status IHsvSystemSettings_Dual_Status
#define tvcoresettings_setValue(Property,value) 	tvcoresettings->setValue(Property,value)
#define tvcoresettings_getValue(Property)		tvcoresettings->getValue(Property)
#define tvcoresettings_GetPrimaryAudioLanguage()		tvcoresettings->GetPrimaryAudioLanguage()
#define tvcoresettings_GetSecondarySubtitleLanguage()		tvcoresettings->GetSecondarySubtitleLanguage()
#define tvcoresettings_GetSecondaryAudioLanguage()		tvcoresettings->GetSecondaryAudioLanguage()
#define tvcoresettings_GetPrimarySubtitleLanguage()		tvcoresettings->GetPrimarySubtitleLanguage()
#define tvcoresettings_GetAudioFormat()		tvcoresettings->GetAudioFormat()
#define tvcoresettings_GetPrimaryTxtLanguage()		tvcoresettings->GetPrimaryTxtLanguage()
#define tvcoresettings_GetSecondaryTxtLanguage()	tvcoresettings->GetSecondaryTxtLanguage()
#define tvcoresettings_GetInstallCountry()		tvcoresettings->GetInstallCountry()
#define tvcoresettings_GetMenuLanguage()		tvcoresettings->GetMenuLanguage()
#define tvcoresettings_GetVisuallyImpairedStatus()		tvcoresettings->GetVisuallyImpairedStatus()
#define tvcoresettings_GetHearingImpaired()		tvcoresettings->GetHearingImpaired()
#define tvcoresettings_GetSubtitleOn()		tvcoresettings->GetSubtitleOn()
#define tvcoresettings_GetOperatorCable()		tvcoresettings->GetOperatorCable()
#define tvcoresettings_GetOperatorSatellite()		tvcoresettings->GetOperatorSatellite()
#define tvcoresettings_GetParentalRating()		tvcoresettings->GetParentalRating()
#define tvcoresettings_InitDbJni()		tvcoresettings->InitDbJni()
#define tvcoresettings_InitDbNative()		tvcoresettings->InitDbNative()
#define tvcoresettings_sync()		tvcoresettings->sync()
#define globalSettings_GetValuesFromGlobalSettings(ID,Value)  globalSettings->GetValuesFromGlobalSettings(ID,Value)
#define Timerclk_ClocksourceManual	IProdApiClockEx_ClocksourceManual
#define Timerclk_ClocksourceTOT	IProdApiClockEx_ClocksourceTOT
#define Timerclk_ClocksourceECD	IProdApiClockEx_ClocksourceECD
#define Timerclk_ClocksourceTXT	IProdApiClockEx_ClocksourceTXT
#define Timerclk_ClocksourceTDT	IProdApiClockEx_ClocksourceTDT
#define Timerclk_ClocksourceTOTDVBS	IProdApiClockEx_ClocksourceTOTDVBS
#define Timerclk_ClocksourceTDTDVBS	IProdApiClockEx_ClocksourceTDTDVBS
#define Timerclk_InvalidClock	IProdApiClockEx_InvalidClock
#define Timerclk_TimeZoneNone	IProdApiClockEx_TimeZoneNone
#define Timerclk_TimeZoneBaleares	IProdApiClockEx_TimeZoneBaleares
#define Timerclk_TimeZoneCanaryIsland	IProdApiClockEx_TimeZoneCanaryIsland
#define Timerclk_TimeZoneContinental	IProdApiClockEx_TimeZoneContinental
#define Timerclk_TimeZoneAzores	IProdApiClockEx_TimeZoneAzores
#define Timerclk_TimeZoneKalingrad	IProdApiClockEx_TimeZoneKalingrad
#define Timerclk_TimeZoneMoscow	IProdApiClockEx_TimeZoneMoscow
#define Timerclk_TimeZoneSamara	IProdApiClockEx_TimeZoneSamara
#define Timerclk_TimeZoneYekaterinburg	IProdApiClockEx_TimeZoneYekaterinburg
#define Timerclk_TimeZoneOmsk	IProdApiClockEx_TimeZoneOmsk
#define Timerclk_TimeZoneKrasnoyarsk	IProdApiClockEx_TimeZoneKrasnoyarsk
#define Timerclk_TimeZoneIrkutsk	IProdApiClockEx_TimeZoneIrkutsk
#define Timerclk_TimeZoneYakutsk	IProdApiClockEx_TimeZoneYakutsk
#define Timerclk_TimeZoneVladivostok	IProdApiClockEx_TimeZoneVladivostok
#define Timerclk_TimeZoneMagadan	IProdApiClockEx_TimeZoneMagadan
#define Timerclk_TimeZoneKamchatka	IProdApiClockEx_TimeZoneKamchatka
#define Timerclk_DstAuto	IProdApiClockEx_DstAuto
#define Timerclk_DstOn	IProdApiClockEx_DstOn
#define Timerclk_DstOff	IProdApiClockEx_DstOff
#define Timerclk_LtoModeAutomatic	IProdApiClockEx_LtoModeAutomatic
#define Timerclk_LtoModeCountryDependent	IProdApiClockEx_LtoModeCountryDependent
#define actl_Volume	i__actl.m_Volume
#define actl_SmartSound	i__actl.m_SmartSound
#define actl_VIAudioVolume	i__actl.m_VIAudioVolume
#define actl_VIRouting	i__actl.m_VIRouting
#define actl_VIRoutingEx	i__actl.m_VIRoutingEx
#define actl_VINone	i__actl.m_VINone
#define actl_VIOn	i__actl.m_VIOn
#define actl_VISpeakerOutput	i__actl.m_VISpeakerOutput
#define actl_VIHeadphoneOutput	i__actl.m_VIHeadphoneOutput
#define actl_VIMonitorOutput	i__actl.m_VIMonitorOutput
#define actl_VISpdifOutput	i__actl.m_VISpdifOutput
#define actl_SeamlessMixing	i__actl.m_SeamlessMixing
#define actl_SeamlessMixing_Off	i__actl.m_SeamlessMixing_Off
#define actl_SeamlessMixing_On	i__actl.m_SeamlessMixing_On
#define actl_SpeechPreference	i__actl.m_SpeechPreference
#define actl_SpeechPreference_Descriptive	i__actl.m_SpeechPreference_Descriptive
#define actl_SpeechPreference_Subtitles	i__actl.m_SpeechPreference_Subtitles
#define actl_OriginalLanguage	i__actl.m_OriginalLanguage
#define actl_OriginalLanguage_On	i__actl.m_OriginalLanguage_On
#define actl_OriginalLanguage_Off	i__actl.m_OriginalLanguage_Off
#define actl_SoundFormat	i__actl.m_SoundFormat
#define actl_SpdifStatus	i__actl.m_SpdifStatus
#define actl_SoundSystem	i__actl.m_SoundSystem
#define actl_Mute	i__actl.m_Mute
#define actl_ProgramMute	ISvcAudioControl4ExEx_ProgramMute
#define actl_PreferedStereo	i__actl.m_PreferedStereo
#define actl_Language	i__actl.m_Language
#define actl_LanguageChina	i__actl.m_LanguageChina
#define actl_None	i__actl.m_None
#define actl_SpeakerOutput	ISvcAudioControl4ExEx_SpeakerOutput
#define actl_HeadphoneOutput	i__actl.m_HeadphoneOutput
#define actl_MonitorOutput	i__actl.m_MonitorOutput
#define actl_SpdifOutput	i__actl.m_SpdifOutput
#define actl_Scart1Output	i__actl.m_Scart1Output
#define actl_Scart2Output	i__actl.m_Scart2Output
#define actl_AllOutput	ISvcAudioControl4ExEx_AllOutput
#define actl_BoolTrue	ISvcAudioControl4ExEx_BoolTrue
#define actl_BoolFalse	ISvcAudioControl4ExEx_BoolFalse
#define actl_IgnoreValue	i__actl.m_IgnoreValue
#define actl_VolumeMin	i__actl.m_VolumeMin
#define actl_VolumeMax	i__actl.m_VolumeMax
#define actl_VIVolumeMin	i__actl.m_VIVolumeMin
#define actl_VIVolumeMax	i__actl.m_VIVolumeMax
#define actl_SmOff	i__actl.m_SmOff
#define actl_SmDolbyPrologic	i__actl.m_SmDolbyPrologic
#define actl_SmFront3Stereo	i__actl.m_SmFront3Stereo
#define actl_SmHall	i__actl.m_SmHall
#define actl_SmIncredible3Dsurround	i__actl.m_SmIncredible3Dsurround
#define actl_SmSpatial	i__actl.m_SmSpatial
#define actl_SmIncredibleSurround	i__actl.m_SmIncredibleSurround
#define actl_SmStereo4	i__actl.m_SmStereo4
#define actl_SmDigitalDolby	i__actl.m_SmDigitalDolby
#define actl_SmMPEGMultiChannel	i__actl.m_SmMPEGMultiChannel
#define actl_SmIncredibleMono	i__actl.m_SmIncredibleMono
#define actl_SmIncredibleStereo	i__actl.m_SmIncredibleStereo
#define actl_SmVDS422	i__actl.m_SmVDS422
#define actl_SmVDS423	i__actl.m_SmVDS423
#define actl_SmVDS521	i__actl.m_SmVDS521
#define actl_SmVDS522	i__actl.m_SmVDS522
#define actl_SmMatrix	i__actl.m_SmMatrix
#define actl_SmDolbyPrologicII	i__actl.m_SmDolbyPrologicII
#define actl_SmDigital3D	i__actl.m_SmDigital3D
#define actl_SmVirtualDolbyDigital	i__actl.m_SmVirtualDolbyDigital
#define actl_SmDolbyPrologicPhantom	i__actl.m_SmDolbyPrologicPhantom
#define actl_SndNICAMRelatedStereo	i__actl.m_SndNICAMRelatedStereo
#define actl_SndNICAMRelatedDual	i__actl.m_SndNICAMRelatedDual
#define actl_SndNICAMRelatedMono	i__actl.m_SndNICAMRelatedMono
#define actl_SndNICAMUnrelatedStereo	i__actl.m_SndNICAMUnrelatedStereo
#define actl_SndNICAMUnrelatedDual	i__actl.m_SndNICAMUnrelatedDual
#define actl_SndNICAMUnrelatedMono	i__actl.m_SndNICAMUnrelatedMono
#define actl_SndNICAMData	i__actl.m_SndNICAMData
#define actl_SndFMStereo	i__actl.m_SndFMStereo
#define actl_SndFMDual	i__actl.m_SndFMDual
#define actl_SndFMAMMono	i__actl.m_SndFMAMMono
#define actl_SndEIAJMono	i__actl.m_SndEIAJMono
#define actl_SndEIAJStereo	i__actl.m_SndEIAJStereo
#define actl_SndEIAJDual	i__actl.m_SndEIAJDual
#define actl_SndAMMono	i__actl.m_SndAMMono
#define actl_SndBTSCMono	i__actl.m_SndBTSCMono
#define actl_SndBTSCStereo	i__actl.m_SndBTSCStereo
#define actl_SndBTSCMonoSap	i__actl.m_SndBTSCMonoSap
#define actl_SndBTSCStereoSap	i__actl.m_SndBTSCStereoSap
#define actl_SndBasebandMono	i__actl.m_SndBasebandMono
#define actl_SndBasebandStereo	i__actl.m_SndBasebandStereo
#define actl_SndNoSoundSystem	i__actl.m_SndNoSoundSystem
#define actl_McChannelOnePlusOne	i__actl.m_McChannelOnePlusOne
#define actl_McChannelTwoPlusTwo	i__actl.m_McChannelTwoPlusTwo
#define actl_McChannelOneByZero	i__actl.m_McChannelOneByZero
#define actl_McChannelTwoByZero	i__actl.m_McChannelTwoByZero
#define actl_McChannelTwoByOne	i__actl.m_McChannelTwoByOne
#define actl_McChannelTwoByTwo	i__actl.m_McChannelTwoByTwo
#define actl_McChannelThreeByZero	i__actl.m_McChannelThreeByZero
#define actl_McChannelThreeByOne	i__actl.m_McChannelThreeByOne
#define actl_McChannelThreeByTwo	i__actl.m_McChannelThreeByTwo
#define actl_McChannelTwoByOneKaraoke	i__actl.m_McChannelTwoByOneKaraoke
#define actl_McChannelTwoByTwoKaraoke	i__actl.m_McChannelTwoByTwoKaraoke
#define actl_McChannelThreeByOneKaraoke	i__actl.m_McChannelThreeByOneKaraoke
#define actl_McChannelThreeByTwoKaraoke	i__actl.m_McChannelThreeByTwoKaraoke
#define actl_McChannelThreeByZeroKaraoke	i__actl.m_McChannelThreeByZeroKaraoke
#define actl_McChannelPCMStereo	i__actl.m_McChannelPCMStereo
#define actl_McChannelNotSupported	i__actl.m_McChannelNotSupported
#define actl_SfAnalog	i__actl.m_SfAnalog
#define actl_SfNICAM	i__actl.m_SfNICAM
#define actl_SfMPEG	i__actl.m_SfMPEG
#define actl_SfPCM	i__actl.m_SfPCM
#define actl_SfDolbyDigital	i__actl.m_SfDolbyDigital
#define actl_SfEIAJ	i__actl.m_SfEIAJ
#define actl_Sf2CS	i__actl.m_Sf2CS
#define actl_SfDTS	i__actl.m_SfDTS
#define actl_SfBaseBand	i__actl.m_SfBaseBand
#define actl_SfAAC	i__actl.m_SfAAC
#define actl_SfUnknown	i__actl.m_SfUnknown
#define actl_SfDolbyDigitalPlus	i__actl.m_SfDolbyDigitalPlus
#define actl_LangEnglish	ISvcAudioControl4ExEx_LangEnglish
#define actl_LangGerman	ISvcAudioControl4ExEx_LangGerman
#define actl_LangSwedish	ISvcAudioControl4ExEx_LangSwedish
#define actl_LangItalian	ISvcAudioControl4ExEx_LangItalian
#define actl_LangFrench	ISvcAudioControl4ExEx_LangFrench
#define actl_LangSpanish	ISvcAudioControl4ExEx_LangSpanish
#define actl_LangCzechSlovak	ISvcAudioControl4ExEx_LangCzechSlovak
#define actl_LangPolish	ISvcAudioControl4ExEx_LangPolish
#define actl_LangTurkish	ISvcAudioControl4ExEx_LangTurkish
#define actl_LangRumainian	ISvcAudioControl4ExEx_LangRumainian
#define actl_LangRussian	ISvcAudioControl4ExEx_LangRussian
#define actl_LangEstonian	ISvcAudioControl4ExEx_LangEstonian
#define actl_LangUkrainian	ISvcAudioControl4ExEx_LangUkrainian
#define actl_LangGreek	ISvcAudioControl4ExEx_LangGreek
#define actl_LangArabic	ISvcAudioControl4ExEx_LangArabic
#define actl_LangHebrew	ISvcAudioControl4ExEx_LangHebrew
#define actl_LangUndefined	ISvcAudioControl4ExEx_LangUndefined
#define actl_LanguageOne	ISvcAudioControl4ExEx_LanguageOne
#define actl_LanguageTwo	ISvcAudioControl4ExEx_LanguageTwo
#define actl_LanguageDualOne	ISvcAudioControl4ExEx_LanguageDualOne
#define actl_LanguageDualTwo	ISvcAudioControl4ExEx_LanguageDualTwo
#define actl_LanguageStereo	ISvcAudioControl4ExEx_LanguageStereo
#define actl_AudioPropertyMaxValue	ISvcAudioControl4ExEx_AudioPropertyMaxValue
#define actl_SpdifUnsupported	i__actl.m_SpdifUnsupported
#define actl_NormalAnalog	i__actl.m_NormalAnalog
#define actl_AnalogMode	i__actl.m_AnalogMode
#define actl_DigitalMode	i__actl.m_DigitalMode
#define apperr_Ok	IAppApiChannelLibReturnCodes_Ok
#define apperr_BadParameter	IAppApiChannelLibReturnCodes_BadParameter
#define apperr_ChannelTableEmpty	IAppApiChannelLibReturnCodes_ChannelTableEmpty
#define apperr_ChannelTableExhausted	IAppApiChannelLibReturnCodes_ChannelTableExhausted
#define apperr_MinorNumbersExhausted	IAppApiChannelLibReturnCodes_MinorNumbersExhausted
#define apperr_NotSupported	IAppApiChannelLibReturnCodes_NotSupported
#define apsysset_Success	IAppApiSystemSettings5_Success
#define apsysset_NVMFailure	IAppApiSystemSettings5_NVMFailure
#define apsysset_CertificateDetectionNotDone	IAppApiSystemSettings5_CertificateDetectionNotDone
#define apsysset_InitFailure	IAppApiSystemSettings5_InitFailure
#define apsysset_AutoEpg	IAppApiSystemSettings5_AutoEpg
#define apsysset_DVBEpg	IAppApiSystemSettings5_DVBEpg
#define apsysset_IPEpg	IAppApiSystemSettings5_IPEpg
#define apsysset_Shop	IAppApiSystemSettings5_Shop
#define apsysset_Home	IAppApiSystemSettings5_Home
#define apsysset_clkSrcNone	IAppApiSystemSettings5_clkSrcNone
#define apsysset_clkSrcMainTuner	IAppApiSystemSettings5_clkSrcMainTuner
#define apsysset_clkSrcSatelliteTuner	IAppApiSystemSettings5_clkSrcSatelliteTuner
#define apsysset_clkSrcManualClock	IAppApiSystemSettings5_clkSrcManualClock
#define apsysset_avSrcNone	IAppApiSystemSettings5_avSrcNone
#define apsysset_avSrcMainTuner	IAppApiSystemSettings5_avSrcMainTuner
#define apsysset_avSrcSatellite	IAppApiSystemSettings5_avSrcSatellite
#define apsysset_avSrcAvIn0	IAppApiSystemSettings5_avSrcAvIn0
#define apsysset_avSrcAvIn1	IAppApiSystemSettings5_avSrcAvIn1
#define apsysset_avSrcAvIn2	IAppApiSystemSettings5_avSrcAvIn2
#define apsysset_avSrcAvIn3	IAppApiSystemSettings5_avSrcAvIn3
#define apsysset_avSrcAvIn4	IAppApiSystemSettings5_avSrcAvIn4
#define apsysset_avSrcAvIn5	IAppApiSystemSettings5_avSrcAvIn5
#define apsysset_avSrcAvIn6	IAppApiSystemSettings5_avSrcAvIn6
#define apsysset_avSrcAvIn7	IAppApiSystemSettings5_avSrcAvIn7
#define apsysset_avSrcAvIn8	IAppApiSystemSettings5_avSrcAvIn8
#define apsysset_avSrcAvIn9	IAppApiSystemSettings5_avSrcAvIn9
#define apsysset_avSrcAvIn10	IAppApiSystemSettings5_avSrcAvIn10
#define apsysset_svcModeNone	IAppApiSystemSettings5_svcModeNone
#define apsysset_svcModeCSM	IAppApiSystemSettings5_svcModeCSM
#define apsysset_svcModeSAM	IAppApiSystemSettings5_svcModeSAM
#define apsysset_svcModeSDM	IAppApiSystemSettings5_svcModeSDM
#define apsysset_svcModeCompair	IAppApiSystemSettings5_svcModeCompair
#define apsysset_svcModeFac	IAppApiSystemSettings5_svcModeFac
#define apsysset_svcModeDigSDM	IAppApiSystemSettings5_svcModeDigSDM
#define apsysset_svcModeBDS	IAppApiSystemSettings5_svcModeBDS
#define apsysset_svcModeRDM	IAppApiSystemSettings5_svcModeRDM
#define apsysset_svcModeBDSSys7	IAppApiSystemSettings5_svcModeBDSSys7
#define apsysset_svcModeFacExit	IAppApiSystemSettings5_svcModeFacExit
#define apsysset_BdsPowStateOn	IAppApiSystemSettings5_BdsPowStateOn
#define apsysset_BdsPowStateStandby	IAppApiSystemSettings5_BdsPowStateStandby
#define apsysset_AudioFormatStandard	IAppApiSystemSettings5_AudioFormatStandard
#define apsysset_AudioFormatAdvanced	IAppApiSystemSettings5_AudioFormatAdvanced
#define apsysset_OsdSizeInvalid	IAppApiSystemSettings5_OsdSizeInvalid
#define apsysset_OsdSizeSmall	IAppApiSystemSettings5_OsdSizeSmall
#define apsysset_OsdSizeLarge	IAppApiSystemSettings5_OsdSizeLarge
#define apsysset_SpainBaleares	IAppApiSystemSettings5_SpainBaleares
#define apsysset_SpainCanaryIsland	IAppApiSystemSettings5_SpainCanaryIsland
#define apsysset_TimeZoneContinental	IAppApiSystemSettings5_TimeZoneContinental
#define apsysset_TimeZoneAzores	IAppApiSystemSettings5_TimeZoneAzores
#define apsysset_TimeZoneKalingrad	IAppApiSystemSettings5_TimeZoneKalingrad
#define apsysset_TimeZoneMoscow	IAppApiSystemSettings5_TimeZoneMoscow
#define apsysset_TimeZoneSamara	IAppApiSystemSettings5_TimeZoneSamara
#define apsysset_TimeZoneYekaterinburg	IAppApiSystemSettings5_TimeZoneYekaterinburg
#define apsysset_TimeZoneOmsk	IAppApiSystemSettings5_TimeZoneOmsk
#define apsysset_TimeZoneKrasnoyarsk	IAppApiSystemSettings5_TimeZoneKrasnoyarsk
#define apsysset_TimeZoneIrkutsk	IAppApiSystemSettings5_TimeZoneIrkutsk
#define apsysset_TimeZoneYakutsk	IAppApiSystemSettings5_TimeZoneYakutsk
#define apsysset_TimeZoneVladivostok	IAppApiSystemSettings5_TimeZoneVladivostok
#define apsysset_TimeZoneMagadan	IAppApiSystemSettings5_TimeZoneMagadan
#define apsysset_TimeZoneKamchatka	IAppApiSystemSettings5_TimeZoneKamchatka
#define apsysset_TimeZoneLatamMinus2	IAppApiSystemSettings5_TimeZoneLatamMinus2
#define apsysset_TimeZoneLatamMinus1	IAppApiSystemSettings5_TimeZoneLatamMinus1
#define apsysset_TimeZoneLatamZero	IAppApiSystemSettings5_TimeZoneLatamZero
#define apsysset_TimeZoneLatamPlus1	IAppApiSystemSettings5_TimeZoneLatamPlus1
#define apsysset_TimeZoneLatamPlus2	IAppApiSystemSettings5_TimeZoneLatamPlus2
#define apsysset_NewSouthWales	IAppApiSystemSettings5_NewSouthWales
#define apsysset_Victoria	IAppApiSystemSettings5_Victoria
#define apsysset_Queensland	IAppApiSystemSettings5_Queensland
#define apsysset_SouthAustralia	IAppApiSystemSettings5_SouthAustralia
#define apsysset_WestAustralia	IAppApiSystemSettings5_WestAustralia
#define apsysset_Tasmania	IAppApiSystemSettings5_Tasmania
#define apsysset_NorthernTerritory	IAppApiSystemSettings5_NorthernTerritory
#define apsysset_ManualClkMode	IAppApiSystemSettings5_ManualClkMode
#define apsysset_AutoClkMode	IAppApiSystemSettings5_AutoClkMode
#define apsysset_CountryDepClkMode	IAppApiSystemSettings5_CountryDepClkMode
#define apsysset_DstOff	IAppApiSystemSettings5_DstOff
#define apsysset_DstOn	IAppApiSystemSettings5_DstOn
#define apsysset_CalStateNotStarted	IAppApiSystemSettings5_CalStateNotStarted
#define apsysset_CalStateInProgress	IAppApiSystemSettings5_CalStateInProgress
#define apsysset_CalStateSuccessfull	IAppApiSystemSettings5_CalStateSuccessfull
#define apsysset_CalStateFailed	IAppApiSystemSettings5_CalStateFailed
#define apsysset_CalStateForced	IAppApiSystemSettings5_CalStateForced
#define apsysset_AutoPowerDownModeOff	IAppApiSystemSettings5_AutoPowerDownModeOff
#define apsysset_AutoPowerDownModeOn	IAppApiSystemSettings5_AutoPowerDownModeOn
#define apsysset_ChannelListAll	IAppApiSystemSettings5_ChannelListAll
#define apsysset_ChannelListTV	IAppApiSystemSettings5_ChannelListTV
#define apsysset_ChannelListRadio	IAppApiSystemSettings5_ChannelListRadio
#define apsysset_ChannelListFavorite	IAppApiSystemSettings5_ChannelListFavorite
#define apsysset_ChannelListAnalog	IAppApiSystemSettings5_ChannelListAnalog
#define apsysset_MediumNone	IAppApiSystemSettings5_MediumNone
#define apsysset_MediumTerrestrial	IAppApiSystemSettings5_MediumTerrestrial
#define apsysset_MediumCable	IAppApiSystemSettings5_MediumCable
#define apsysset_SubtitleNone	IAppApiSystemSettings5_SubtitleNone
#define apsysset_SubtitleOff	IAppApiSystemSettings5_SubtitleOff
#define apsysset_SubtitleOn	IAppApiSystemSettings5_SubtitleOn
#define apsysset_SubtitleOnDuringMute	IAppApiSystemSettings5_SubtitleOnDuringMute
#define apsysset_InvalidPinCode	IAppApiSystemSettings5_InvalidPinCode
#define apsysset_InvalidLastViewed	IAppApiSystemSettings5_InvalidLastViewed
#define apsysset_LastViewedBroadcast	IAppApiSystemSettings5_LastViewedBroadcast
#define apsysset_LastViewedNetwork	IAppApiSystemSettings5_LastViewedNetwork
#define chanlibret_Ok	IHsvChannelLibReturnCodes_Ok
#define chanlibret_BadParameter	IHsvChannelLibReturnCodes_BadParameter
#define chanlibret_ChannelTableEmpty	IHsvChannelLibReturnCodes_ChannelTableEmpty
#define chanlibret_ChannelTableExhausted	IHsvChannelLibReturnCodes_ChannelTableExhausted
#define chanlibret_MinorNumbersExhausted	IHsvChannelLibReturnCodes_MinorNumbersExhausted
#define chanlibret_NotSupported	IHsvChannelLibReturnCodes_NotSupported
#define chanlibret_FileError	IHsvChannelLibReturnCodes_FileError
#define chanlibret_ChannelTableVersionError	IHsvChannelLibReturnCodes_ChannelTableVersionError
#define chanlibret_ChannelTableCrcError	IHsvChannelLibReturnCodes_ChannelTableCrcError
#define chanlibret_ChannelNotInstalled	IHsvChannelLibReturnCodes_ChannelNotInstalled
#define chanlibret_NVMError	IHsvChannelLibReturnCodes_NVMError
#define chdecdvbt2_PlpIdAuto	IPlfApiChanDecDvbT2_PlpIdAuto
#define chdecdvbt2_AdvSigTFS	IPlfApiChanDecDvbT2_AdvSigTFS
#define chdecdvbt2_AdvSigFEF	IPlfApiChanDecDvbT2_AdvSigFEF
#define chdecdvbt2_AdvSigAuxStream	IPlfApiChanDecDvbT2_AdvSigAuxStream
#define chdecdvbt2_AdvSigGSE	IPlfApiChanDecDvbT2_AdvSigGSE
#define chdecdvbt2_AdvSigGCS	IPlfApiChanDecDvbT2_AdvSigGCS
#define chdecdvbt2_AdvSigGFPS	IPlfApiChanDecDvbT2_AdvSigGFPS
#define chdecdvbt2_AdvSigFuturePayloadType	IPlfApiChanDecDvbT2_AdvSigFuturePayloadType
#define chdecdvbt2_AdvSigMISO	IPlfApiChanDecDvbT2_AdvSigMISO
#define chdecdvbt2_AdvSigS1Future	IPlfApiChanDecDvbT2_AdvSigS1Future
#define chdecdvbt2_AdvSigT2FutureVersion	IPlfApiChanDecDvbT2_AdvSigT2FutureVersion
#define chdecdvbt2_AdvSigFuturePlpType	IPlfApiChanDecDvbT2_AdvSigFuturePlpType
#define chdecdvbt2_AdvSigL1Change	IPlfApiChanDecDvbT2_AdvSigL1Change
#define chdecdvbt2_SigPropSinglePlp	IPlfApiChanDecDvbT2_SigPropSinglePlp
#define chdecdvbt2_SigPropIQ	IPlfApiChanDecDvbT2_SigPropIQ
#define chdecdvbt2_MaxPlp	IPlfApiChanDecDvbT2_MaxPlp
#define cids_CountryAustria	IHsvCountryIds_CountryAustria
#define cids_CountryBelgium	IHsvCountryIds_CountryBelgium
#define cids_CountryCroatia	IHsvCountryIds_CountryCroatia
#define cids_CountryCzechrep	IHsvCountryIds_CountryCzechrep
#define cids_CountryDenmark	IHsvCountryIds_CountryDenmark
#define cids_CountryFinland	IHsvCountryIds_CountryFinland
#define cids_CountryFrance	IHsvCountryIds_CountryFrance
#define cids_CountryGermany	IHsvCountryIds_CountryGermany
#define cids_CountryGreece	IHsvCountryIds_CountryGreece
#define cids_CountryHungary	IHsvCountryIds_CountryHungary
#define cids_CountryIreland	IHsvCountryIds_CountryIreland
#define cids_CountryItaly	IHsvCountryIds_CountryItaly
#define cids_CountryLuxembourg	IHsvCountryIds_CountryLuxembourg
#define cids_CountryNetherlands	IHsvCountryIds_CountryNetherlands
#define cids_CountryNorway	IHsvCountryIds_CountryNorway
#define cids_CountryPoland	IHsvCountryIds_CountryPoland
#define cids_CountryPortugal	IHsvCountryIds_CountryPortugal
#define cids_CountryRomania	IHsvCountryIds_CountryRomania
#define cids_CountryRussia	IHsvCountryIds_CountryRussia
#define cids_CountrySerbia	IHsvCountryIds_CountrySerbia
#define cids_CountrySlovakia	IHsvCountryIds_CountrySlovakia
#define cids_CountrySlovenia	IHsvCountryIds_CountrySlovenia
#define cids_CountrySpain	IHsvCountryIds_CountrySpain
#define cids_CountrySweden	IHsvCountryIds_CountrySweden
#define cids_CountrySwitzerland	IHsvCountryIds_CountrySwitzerland
#define cids_CountryTurkey	IHsvCountryIds_CountryTurkey
#define cids_CountryUK	IHsvCountryIds_CountryUK
#define cids_CountryOther	IHsvCountryIds_CountryOther
#define cids_CountryAustralia	IHsvCountryIds_CountryAustralia
#define cids_CountryEstonia	IHsvCountryIds_CountryEstonia
#define cids_CountryLithuania	IHsvCountryIds_CountryLithuania
#define cids_CountryLatvia	IHsvCountryIds_CountryLatvia
#define cids_CountryKazakhstan	IHsvCountryIds_CountryKazakhstan
#define cids_CountryBulgaria	IHsvCountryIds_CountryBulgaria
#define cids_CountryChina	IHsvCountryIds_CountryChina
#define cids_CountryUkraine	IHsvCountryIds_CountryUkraine
#define cids_CountryBrazil	IHsvCountryIds_CountryBrazil
#define cids_CountryArgentina	IHsvCountryIds_CountryArgentina
#define cids_CountryAlbania	IHsvCountryIds_CountryAlbania
#define cids_CountryArmenia	IHsvCountryIds_CountryArmenia
#define cids_CountryAzerbaijan	IHsvCountryIds_CountryAzerbaijan
#define cids_CountryBelarus	IHsvCountryIds_CountryBelarus
#define cids_CountryBosniaAndHerzegovina	IHsvCountryIds_CountryBosniaAndHerzegovina
#define cids_CountryGeorgia	IHsvCountryIds_CountryGeorgia
#define cids_CountryMontenegro	IHsvCountryIds_CountryMontenegro
#define cids_CountryIsrael	IHsvCountryIds_CountryIsrael
#define cids_CountryMacedoniafyrom	IHsvCountryIds_CountryMacedoniafyrom
#define cids_CountryParaguay	IHsvCountryIds_CountryParaguay
#define cids_CountryUruguay	IHsvCountryIds_CountryUruguay
#define cids_CountryThailand	IHsvCountryIds_CountryThailand
#define cids_CountryNewZealand	IHsvCountryIds_CountryNewZealand
#define cids_CountrySingapore	IHsvCountryIds_CountrySingapore
#define cids_CountryMalaysia	IHsvCountryIds_CountryMalaysia
#define cids_CountryTaiwan	IHsvCountryIds_CountryTaiwan
#define cids_CountryIndonesia	IHsvCountryIds_CountryIndonesia
#define cids_CountryUAE	IHsvCountryIds_CountryUAE
#define cids_CountryVietnam     IHsvCountryIds_CountryVietnam
#define cids_CountryMax	IHsvCountryIds_CountryMax
#define cityids_CityBeijing	ICesCityIds_CityBeijing
#define cityids_CityGuangdong	ICesCityIds_CityGuangdong
#define cityids_CityGuangzhou	ICesCityIds_CityGuangzhou
#define cityids_CityOthers	ICesCityIds_CityOthers
#define cityids_CityInvalid	ICesCityIds_CityInvalid
#define col_UnknownColorSystem	i__col.m_UnknownColorSystem
#define col_InvalidColorSystem	i__col.m_InvalidColorSystem
#define col_Pal	i__col.m_Pal
#define col_Secam	i__col.m_Secam
#define col_Ntsc	i__col.m_Ntsc
#define col_FreqUnknown	i__col.m_FreqUnknown
#define col_FreqInvalid	i__col.m_FreqInvalid
#define col_Freq4pt433619	i__col.m_Freq4pt433619
#define col_Freq3pt582056	i__col.m_Freq3pt582056
#define col_Freq3pt575611	i__col.m_Freq3pt575611
#define col_Freq3pt579545	i__col.m_Freq3pt579545
#define ctrlpen_PumpEngine	i__ctrlpen.m_PumpEngine
#define decsel_ChanDecDvbT	IPlfApiChanDecSelect_ChanDecDvbT
#define decsel_ChanDecDvbC	IPlfApiChanDecSelect_ChanDecDvbC
#define decsel_ChanDecDvbS	IPlfApiChanDecSelect_ChanDecDvbS
#define decsel_ChanDecISDBT	IPlfApiChanDecSelect_ChanDecISDBT
#define decsel_ChanDecDvbT2	IPlfApiChanDecSelect_ChanDecDvbT2
#define decsel_ChanDecDvbC2	IPlfApiChanDecSelect_ChanDecDvbC2
#define destconfig_iVersion	i__destconfig.m_iVersion
#define destconfig_NoOfDestinations	i__destconfig.m_NoOfDestinations
#define destconfig_destPropVideo	i__destconfig.m_destPropVideo
#define destconfig_destPropAudio	i__destconfig.m_destPropAudio
#define destconfig_destPropLockable	i__destconfig.m_destPropLockable
#define dt_Monday	IDateTime_Monday
#define dt_Tuesday	IDateTime_Tuesday
#define dt_Wednesday	IDateTime_Wednesday
#define dt_Thursday	IDateTime_Thursday
#define dt_Friday	IDateTime_Friday
#define dt_Saturday	IDateTime_Saturday
#define dt_Sunday	IDateTime_Sunday
#define dt_Hour	IDateTime_Hour
#define dt_Day	IDateTime_Day
#define dt_DateTimeMin	IDateTime_DateTimeMin
#define dt_DateTimeMax	IDateTime_DateTimeMax
#define dt_OffsetModifiedJulianDate	IDateTime_OffsetModifiedJulianDate
#define dvbsrtdbids_NitLcnTableMain	i__dvbsrtdbids.m_NitLcnTableMain
#define dvbsrtdbids_SdtTableActual	i__dvbsrtdbids.m_SdtTableActual
#define dvbsrtdbids_SdtTableOther	i__dvbsrtdbids.m_SdtTableOther
#define dvbsrtdbids_EitPresentActual	i__dvbsrtdbids.m_EitPresentActual
#define dvbsrtdbids_EitFollowActual	i__dvbsrtdbids.m_EitFollowActual
#define dvbsrtdbids_EitPresentOther	i__dvbsrtdbids.m_EitPresentOther
#define dvbsrtdbids_EitFollowOther	i__dvbsrtdbids.m_EitFollowOther
#define dvbsrtdbids_EitScheduleActual	i__dvbsrtdbids.m_EitScheduleActual
#define dvbsrtdbids_EitScheduleOther	i__dvbsrtdbids.m_EitScheduleOther
#define dvbsrtdbids_EitLinkageInfo	i__dvbsrtdbids.m_EitLinkageInfo
#define dvbsrtdbids_TotTableMain	i__dvbsrtdbids.m_TotTableMain
#define dvbsrtdbids_LinkageInfoMain	i__dvbsrtdbids.m_LinkageInfoMain
#define dvbsrtdbids_NitLinkageInfoMain	i__dvbsrtdbids.m_NitLinkageInfoMain
#define dvbsrtdbids_NitLcnTableSub	i__dvbsrtdbids.m_NitLcnTableSub
#define dvbsrtdbids_NitCableDSMain	i__dvbsrtdbids.m_NitCableDSMain
#define dvbsrtdbids_NitCableDSSub	i__dvbsrtdbids.m_NitCableDSSub
#define dvbsrtdbids_NitLinkageInfoSub	i__dvbsrtdbids.m_NitLinkageInfoSub
#define dvbsrtdbids_NitOtherNetworkIdTable	i__dvbsrtdbids.m_NitOtherNetworkIdTable
#define dvbsrtdbids_NitFreqList	i__dvbsrtdbids.m_NitFreqList
#define dvbsrtdbids_NitLcn2TableMain	i__dvbsrtdbids.m_NitLcn2TableMain
#define dvbsrtdbids_NitLcn2TableSub	i__dvbsrtdbids.m_NitLcn2TableSub
#define dvbsrtdbids_NitHDSLcnTableMain	i__dvbsrtdbids.m_NitHDSLcnTableMain
#define dvbsrtdbids_NitSrvcAtrbTableMain	i__dvbsrtdbids.m_NitSrvcAtrbTableMain
#define dvbsrtdbids_NitSrvclstTableMain	i__dvbsrtdbids.m_NitSrvclstTableMain
#define dvbsrtdbids_NitSrvclstTableSub	i__dvbsrtdbids.m_NitSrvclstTableSub
#define dvbsrtdbids_NitTsRelocateTableMain	i__dvbsrtdbids.m_NitTsRelocateTableMain
#define dvbsrtdbids_NitHDSLcnTableSub	i__dvbsrtdbids.m_NitHDSLcnTableSub
#define dvbsrtdbids_SdtTargetRegion	i__dvbsrtdbids.m_SdtTargetRegion
#define dvbsrtdbids_NitTargetRegion	i__dvbsrtdbids.m_NitTargetRegion
#define dvbsrtdbids_NitTargetRegionName	i__dvbsrtdbids.m_NitTargetRegionName
#define err_Ok	IHsvChannelLibReturnCodes_Ok
#define err_BadParameter	IHsvChannelLibReturnCodes_BadParameter
#define err_ChannelTableEmpty	IHsvChannelLibReturnCodes_ChannelTableEmpty
#define err_ChannelTableExhausted	IHsvChannelLibReturnCodes_ChannelTableExhausted
#define err_MinorNumbersExhausted	IHsvChannelLibReturnCodes_MinorNumbersExhausted
#define err_NotSupported	IHsvChannelLibReturnCodes_NotSupported
#define err_FileError	IHsvChannelLibReturnCodes_FileError
#define err_ChannelTableVersionError	IHsvChannelLibReturnCodes_ChannelTableVersionError
#define err_ChannelTableCrcError	IHsvChannelLibReturnCodes_ChannelTableCrcError
#define err_ChannelNotInstalled	IHsvChannelLibReturnCodes_ChannelNotInstalled
#define err_NVMError	IHsvChannelLibReturnCodes_NVMError
#define eurdiv_iVersion	i__eurdiv.m_iVersion
#define eurdiv_NITTimeoutTime	i__eurdiv.m_NITTimeoutTime
#define eurdiv_AttenuatorDetectionInInstall	i__eurdiv.m_AttenuatorDetectionInInstall
#define eurdiv_SupportNameExtractionInManIns	i__eurdiv.m_SupportNameExtractionInManIns
#define eurdiv_WeakSignalStrengthThreshold	i__eurdiv.m_WeakSignalStrengthThreshold
#define eurdiv_SignalStrengthSorting	i__eurdiv.m_SignalStrengthSorting
#define eurdiv_SearchForColorSystemInInstallation	i__eurdiv.m_SearchForColorSystemInInstallation
#define eurdiv_SearchForTvSystemInInstallation	i__eurdiv.m_SearchForTvSystemInInstallation
#define eurdiv_ManualSearchWithWrapAround	i__eurdiv.m_ManualSearchWithWrapAround
#define eurdiv_SortPresetsInAutoStoreModeNone	i__eurdiv.m_SortPresetsInAutoStoreModeNone
#define eurdiv_SignalStrengthTimeoutTime	i__eurdiv.m_SignalStrengthTimeoutTime
#define eurdiv_DefaultTunerPresetFrequency	i__eurdiv.m_DefaultTunerPresetFrequency
#define eurdiv_PgctrlMuteColor	i__eurdiv.m_PgctrlMuteColor
#define eurdiv_ChannelNameLength	i__eurdiv.m_ChannelNameLength
#define eurdiv_PresetNameLength	i__eurdiv.m_PresetNameLength
#define eurdiv_MuteRequiredOnInstallation	i__eurdiv.m_MuteRequiredOnInstallation
#define eurdiv_ClearDataOnAutoInstallation	i__eurdiv.m_ClearDataOnAutoInstallation
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_SkipInstallationPass	i__eurdiv.m_SkipInstallationPass
#define eurdiv_FirstInstallationPass	i__eurdiv.m_FirstInstallationPass
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_TxtInfoTimeout	i__eurdiv.m_TxtInfoTimeout
#define eurdiv_VideoMuteColor	i__eurdiv.m_VideoMuteColor
#define eurdiv_VideoMuteColorForLocks	i__eurdiv.m_VideoMuteColorForLocks
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	i__eurdiv.m_DecoderSupported
#define eurdiv_BreakInSupported	i__eurdiv.m_BreakInSupported
#define eurdiv_ScartRuleSupported	i__eurdiv.m_ScartRuleSupported
#define eurdiv_HsvAntennaAnalogTable	i__eurdiv.m_HsvAntennaAnalogTable
#define eurdiv_HsvAntennaDigSrvcTable	i__eurdiv.m_HsvAntennaDigSrvcTable
#define eurdiv_HsvAntennaDigPtcTable	i__eurdiv.m_HsvAntennaDigPtcTable
#define eurdiv_HsvAntennaFreqMapTable	i__eurdiv.m_HsvAntennaFreqMapTable
#define eurdiv_PersistentMemUpdateTimeout	i__eurdiv.m_PersistentMemUpdateTimeout
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaUserTable
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaDigSrvcTable
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaDigPtcTable
#define eurdiv_MaxNoOfChannelsToStoreAntennaAnalogTable	i__eurdiv.m_MaxNoOfChannelsToStoreAntennaAnalogTable
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	i__eurdiv.m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable
#define eurdiv_AvSignalDetectionTimeOut	i__eurdiv.m_AvSignalDetectionTimeOut
#define eurdiv_HearingImpairedOn	i__eurdiv.m_HearingImpairedOn
#define eurdiv_EPGSecondaryDirName	i__eurdiv.m_EPGSecondaryDirName
#define eurdiv_DefaultCharacterTable	i__eurdiv.m_DefaultCharacterTable
#define eurdiv_ShortInfoCacheForCountry	i__eurdiv.m_ShortInfoCacheForCountry
#define eurdiv_OUI	i__eurdiv.m_OUI
#define eurdiv_HardwareModel	i__eurdiv.m_HardwareModel
#define eurdiv_HardwareVersion	i__eurdiv.m_HardwareVersion
#define eurdiv_SubtitleTimeOut	i__eurdiv.m_SubtitleTimeOut
#define eurdiv_CurrentCountryInvalidLCNSortKey1	i__eurdiv.m_CurrentCountryInvalidLCNSortKey1
#define eurdiv_CurrentCountryInvalidLCNSortKey2	i__eurdiv.m_CurrentCountryInvalidLCNSortKey2
#define eurdiv_CurrentCountryInvalidLCNSortKey3	i__eurdiv.m_CurrentCountryInvalidLCNSortKey3
#define eurdiv_CurrentCountryInvalidLCNSortKey4	i__eurdiv.m_CurrentCountryInvalidLCNSortKey4
#define eurdiv_CurrentCountryInvalidLCNSortKey5	i__eurdiv.m_CurrentCountryInvalidLCNSortKey5
#define eurdiv_OtherCountrySortKey1	i__eurdiv.m_OtherCountrySortKey1
#define eurdiv_OtherCountrySortKey2	i__eurdiv.m_OtherCountrySortKey2
#define eurdiv_OtherCountrySortKey3	i__eurdiv.m_OtherCountrySortKey3
#define eurdiv_OtherCountrySortKey4	i__eurdiv.m_OtherCountrySortKey4
#define eurdiv_OtherCountrySortKey5	i__eurdiv.m_OtherCountrySortKey5
#define eurdiv_KeyInvalid	IHsvEuropeDiversity2_KeyInvalid
#define eurdiv_KeyOriginalNetworkId	IHsvEuropeDiversity2_KeyOriginalNetworkId
#define eurdiv_KeyServiceType	IHsvEuropeDiversity2_KeyServiceType
#define eurdiv_KeyLCN	IHsvEuropeDiversity2_KeyLCN
#define eurdiv_KeyServiceName	IHsvEuropeDiversity2_KeyServiceName
#define eurdiv_KeyServiceId	IHsvEuropeDiversity2_KeyServiceId
#define eurdiv_MeasureSignalStrengthWhilePlaying	i__eurdiv.m_MeasureSignalStrengthWhilePlaying
#define eurdiv_AnalogInstallationSequence	i__eurdiv.m_AnalogInstallationSequence
#define eurdiv_Automatic	IHsvEuropeDiversity2_Automatic
#define eurdiv_PalOnly	IHsvEuropeDiversity2_PalOnly
#define eurdiv_PalSecam	IHsvEuropeDiversity2_PalSecam
#define eurdiv_SecamPal	IHsvEuropeDiversity2_SecamPal
#define eurdiv_SecamOnly	IHsvEuropeDiversity2_SecamOnly
#define eurdiv_ChannelListVariant	i__eurdiv.m_ChannelListVariant
#define eurdiv_DefaultChannelList	IHsvEuropeDiversity2_DefaultChannelList
#define eurdiv_DualChannelList	IHsvEuropeDiversity2_DualChannelList
#define eurdiv_TripleChannelList	IHsvEuropeDiversity2_TripleChannelList
#define eurdiv_HsvCableAnalogTable	i__eurdiv.m_HsvCableAnalogTable
#define eurdiv_HsvCableDigSrvcTable	i__eurdiv.m_HsvCableDigSrvcTable
#define eurdiv_HsvCableDigPtcTable	i__eurdiv.m_HsvCableDigPtcTable
#define eurdiv_HsvCableSvcListDescTable	i__eurdiv.m_HsvCableSvcListDescTable
#define eurdiv_HsvCableFreqMapTable	i__eurdiv.m_HsvCableFreqMapTable
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableUserTable
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableDigSrvcTable
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableDigPtcTable
#define eurdiv_MaxNoOfChannelsToStoreCableAnalogTable	i__eurdiv.m_MaxNoOfChannelsToStoreCableAnalogTable
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	i__eurdiv.m_MaxNoOfMultiplexsToStoreCableFreqMapTable
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanAnalog	IHsvEuropeDiversity2_ScanAnalog
#define eurdiv_ScanDVBT	IHsvEuropeDiversity2_ScanDVBT
#define eurdiv_ScanDVBC	IHsvEuropeDiversity2_ScanDVBC
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_ScanDVBTMpegOnly	IHsvEuropeDiversity2_ScanDVBTMpegOnly
#define eurdiv_ScanDVBCLite	IHsvEuropeDiversity2_ScanDVBCLite
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_HsvDVBCSettingsFilePath	i__eurdiv.m_HsvDVBCSettingsFilePath
#define eurdiv_HsvCableDelSysDescFilePath	i__eurdiv.m_HsvCableDelSysDescFilePath
#define eurdiv_HsvServiceListDescFilePath	i__eurdiv.m_HsvServiceListDescFilePath
#define eurdiv_MaxLCNValue	i__eurdiv.m_MaxLCNValue
#define eurdiv_SDTActual	IHsvEuropeDiversity2_SDTActual
#define eurdiv_SDTOther	IHsvEuropeDiversity2_SDTOther
#define eurdiv_SDTNone	IHsvEuropeDiversity2_SDTNone
#define eurdiv_AltHomingFrequency	IHsvEuropeDiversity2_AltHomingFrequency
#define eurdiv_AltTSRelocatedDesc	IHsvEuropeDiversity2_AltTSRelocatedDesc
#define eurdiv_AltNone	IHsvEuropeDiversity2_AltNone
#define ffsdir_AvPlf	IProdApiFlashFileSystemDirectoryExEx_AvPlf
#define ffsdir_CeApps	IProdApiFlashFileSystemDirectoryExEx_CeApps
#define ffsdir_CeDcp	IProdApiFlashFileSystemDirectoryExEx_CeDcp
#define ffsdir_CeDvp	IProdApiFlashFileSystemDirectoryExEx_CeDvp
#define ffsdir_CeGs	IProdApiFlashFileSystemDirectoryExEx_CeGs
#define ffsdir_CeInfra	IProdApiFlashFileSystemDirectoryExEx_CeInfra
#define ffsdir_CeSvc	IProdApiFlashFileSystemDirectoryExEx_CeSvc
#define ffsdir_CeTlpod	IProdApiFlashFileSystemDirectoryExEx_CeTlpod
#define ffsdir_CeTv	IProdApiFlashFileSystemDirectoryExEx_CeTv
#define ffsdir_CeVlfw	IProdApiFlashFileSystemDirectoryExEx_CeVlfw
#define ffsdir_Fac	IProdApiFlashFileSystemDirectoryExEx_Fac
#define ffsdir_GfxMgr	IProdApiFlashFileSystemDirectoryExEx_GfxMgr
#define ffsdir_HySvc	IProdApiFlashFileSystemDirectoryExEx_HySvc
#define ffsdir_Infra	IProdApiFlashFileSystemDirectoryExEx_Infra
#define ffsdir_JagDvp	IProdApiFlashFileSystemDirectoryExEx_JagDvp
#define ffsdir_Juice	IProdApiFlashFileSystemDirectoryExEx_Juice
#define ffsdir_NhApi	IProdApiFlashFileSystemDirectoryExEx_NhApi
#define ffsdir_TvSvc	IProdApiFlashFileSystemDirectoryExEx_TvSvc
#define ffsdir_TxPlf	IProdApiFlashFileSystemDirectoryExEx_TxPlf
#define ffsdir_TxSvc	IProdApiFlashFileSystemDirectoryExEx_TxSvc
#define ffsdir_CeHtv	IProdApiFlashFileSystemDirectoryExEx_CeHtv
#define ffsdir_Tv520Avi	IProdApiFlashFileSystemDirectoryExEx_Tv520Avi
#define ffsdir_CbMhg	IProdApiFlashFileSystemDirectoryExEx_CbMhg
#define ffsdir_Tv	IProdApiFlashFileSystemDirectoryExEx_Tv
#define ffsdir_TvPlf	IProdApiFlashFileSystemDirectoryExEx_TvPlf
#define ffsdir_NumCustomers	IProdApiFlashFileSystemDirectoryExEx_NumCustomers
#define ffsdir_SharedRes	IProdApiFlashFileSystemDirectoryExEx_SharedRes
#define ffsdir_Ols	IProdApiFlashFileSystemDirectoryExEx_Ols
#define ffsdir_Demo	IProdApiFlashFileSystemDirectoryExEx_Demo
#define ffsdir_Home	IProdApiFlashFileSystemDirectoryExEx_Home
#define ffsdir_Dfu	IProdApiFlashFileSystemDirectoryExEx_Dfu
#define ffsdir_Upg	IProdApiFlashFileSystemDirectoryExEx_Upg
#define ffsdir_Broadcast	IProdApiFlashFileSystemDirectoryExEx_Broadcast
#define ffsdir_ReadOnce	IProdApiFlashFileSystemDirectoryExEx_ReadOnce
#define ffsdir_ReadUpgrade	IProdApiFlashFileSystemDirectoryExEx_ReadUpgrade
#define ffsdir_ReadWrite	IProdApiFlashFileSystemDirectoryExEx_ReadWrite
#define ffsdir_ReadRFS	IProdApiFlashFileSystemDirectoryExEx_ReadRFS
#define ffsdir_Boot	IProdApiFlashFileSystemDirectoryExEx_Boot
#define ffsdir_Data	IProdApiFlashFileSystemDirectoryExEx_Data
#define ffsdir_NumPaths	IProdApiFlashFileSystemDirectoryExEx_NumPaths
#define ffsdir_MaxStringLength	IProdApiFlashFileSystemDirectoryExEx_MaxStringLength
#define hpool_MemLocalDma	IHsvPool_MemLocalDma
#define hpool_MemLocal	IHsvPool_MemLocal
#define hpool_MemShared	IHsvPool_MemShared
#define hpool_MemLocalNoFatal	IHsvPool_MemLocalNoFatal
#define insN_EventInstallationCompleted	IHsvInstallationNotify_EventInstallationCompleted
#define insN_EventInstallationStarted	IHsvInstallationNotify_EventInstallationStarted
#define insN_EventInstallationStopped	IHsvInstallationNotify_EventInstallationStopped
#define insN_EventInstallationPaused	IHsvInstallationNotify_EventInstallationPaused
#define insN_EventInstallationContinued	IHsvInstallationNotify_EventInstallationContinued
#define insN_EventChannelFound	IHsvInstallationNotify_EventChannelFound
#define insN_EventChannelNotFound	IHsvInstallationNotify_EventChannelNotFound
#define insN_EventSearchInProgress	IHsvInstallationNotify_EventSearchInProgress
#define insN_EventTuningStarted	IHsvInstallationNotify_EventTuningStarted
#define insN_EventTuningStationFound	IHsvInstallationNotify_EventTuningStationFound
#define insN_EventTuningStationNotFound	IHsvInstallationNotify_EventTuningStationNotFound
#define insN_EventManualInstallationCniExtractionStarted	IHsvInstallationNotify_EventManualInstallationCniExtractionStarted
#define insN_EventManualInstallationCniExtractionEnded	IHsvInstallationNotify_EventManualInstallationCniExtractionEnded
#define insN_EventATSSortingStarted	IHsvInstallationNotify_EventATSSortingStarted
#define insN_EventAciStoreStarted	IHsvInstallationNotify_EventAciStoreStarted
#define insN_EventTvSystemChanged	IHsvInstallationNotify_EventTvSystemChanged
#define insN_EventMediumChanged	IHsvInstallationNotify_EventMediumChanged
#define insN_EventSignalStrengthChanged	IHsvInstallationNotify_EventSignalStrengthChanged
#define insN_EventBackGroundCNIUpdated	IHsvInstallationNotify_EventBackGroundCNIUpdated
#define insN_EventPresetStored	IHsvInstallationNotify_EventPresetStored
#define insN_EventPhaseStarted	IHsvInstallationNotify_EventPhaseStarted
#define insN_EventPhaseCompleted	IHsvInstallationNotify_EventPhaseCompleted
#define insN_EventChannelIterationStarted	IHsvInstallationNotify_EventChannelIterationStarted
#define insN_EventHeirarchyModeDetected	IHsvInstallationNotify_EventHeirarchyModeDetected
#define insN_EventChannelAdded	IHsvInstallationNotify_EventChannelAdded
#define insN_EventChannelRemoved	IHsvInstallationNotify_EventChannelRemoved
#define insN_EventNetworkUpdateDetected	IHsvInstallationNotify_EventNetworkUpdateDetected
#define insN_EventDisplayNetworkNames	IHsvInstallationNotify_EventDisplayNetworkNames
#define insN_EventNIDInvalid	IHsvInstallationNotify_EventNIDInvalid
#define insN_EventNetworkUpdateNotDetected	IHsvInstallationNotify_EventNetworkUpdateNotDetected
#define insN_EventOnConflictsDetected	IHsvInstallationNotify_EventOnConflictsDetected
#define insN_EventDisplayRegionNames	IHsvInstallationNotify_EventDisplayRegionNames
#define insN_EventPLPsDetected	IHsvInstallationNotify_EventPLPsDetected
#define insN_NetworkOperator	IHsvInstallationNotify_NetworkOperator
#define insN_EventMultiPackageFound 	IHsvInstallationNotify_EventMultiPackageFound
#define	insN_EventMultiPackageToBeDisplayed 	IHsvInstallationNotify_EventMultiPackageToBeDisplayed
#define	insN_EventMultiPackageRemoved	 IHsvInstallationNotify_EventMultiPackageRemoved
#define insN_EventNewPresetNumber IHsvInstallationNotify_EventNewPresetNumber
#define insdiv_iVersion	i__insdiv.m_iVersion
#define insdiv_MaxPresets	IHsvPresetInstallationDiv_MaxPresets
#define insdiv_PresetNameLength	IHsvPresetInstallationDiv_PresetNameLength
#define insdiv_TxtResetTimeoutTime	i__insdiv.m_TxtResetTimeoutTime
#define insdiv_SorCChannelSupported	i__insdiv.m_SorCChannelSupported
#define insdiv_TxtInfoTimeoutTime	i__insdiv.m_TxtInfoTimeoutTime
#define insdiv_AciOverallTimeoutTime	i__insdiv.m_AciOverallTimeoutTime
#define insdiv_NITTimeoutTime	i__insdiv.m_NITTimeoutTime
#define insdiv_SignalStrengthSorting	i__insdiv.m_SignalStrengthSorting
#define insdiv_WeakSignalStrengthThreshold	i__insdiv.m_WeakSignalStrengthThreshold
#define insdiv_AttenuatorDetectionInInstall	i__insdiv.m_AttenuatorDetectionInInstall
#define insdiv_SupportNameExtractionInManIns	i__insdiv.m_SupportNameExtractionInManIns
#define insdiv_SearchForTvSystemInInstallation	i__insdiv.m_SearchForTvSystemInInstallation
#define insdiv_SearchForColorSystemInInstallation	i__insdiv.m_SearchForColorSystemInInstallation
#define insdiv_SortPresetsInAutoStoreModeNone	i__insdiv.m_SortPresetsInAutoStoreModeNone
#define insdiv_SignalStrengthTimeoutTime	i__insdiv.m_SignalStrengthTimeoutTime
#define insdiv_ManualSearchWithWrapAround	i__insdiv.m_ManualSearchWithWrapAround
#define insdiv_ImmediateStoreInAutoInstall	i__insdiv.m_ImmediateStoreInAutoInstall
#define insdiv_AudioMuteDuringInstall	i__insdiv.m_AudioMuteDuringInstall
#define insdiv_NameExtractionDuringImplicitManInstall	i__insdiv.m_NameExtractionDuringImplicitManInstall
#define insdiv_HandleSorCStationNotFoundinManInstall	i__insdiv.m_HandleSorCStationNotFoundinManInstall
#define insdiv_DefaultSystemLanguage	i__insdiv.m_DefaultSystemLanguage
#define insdiv_CookieDefaultValue	i__insdiv.m_CookieDefaultValue
#define insdiv_MpegSectionsAcquisitionTimeout	i__insdiv.m_MpegSectionsAcquisitionTimeout
#define insdiv_BlankVideo	i__insdiv.m_BlankVideo
#define insdiv_SigStrengthThresholdValue	i__insdiv.m_SigStrengthThresholdValue
#define insdiv_FirstInstallationPass	i__insdiv.m_FirstInstallationPass
#define insdiv_PgctrlMuteColor	i__insdiv.m_PgctrlMuteColor
#define insdiv_MaxPresetNo	i__insdiv.m_MaxPresetNo
#define insdiv_MinPresetNo	i__insdiv.m_MinPresetNo
#define insdiv_AnalogOnly	i__insdiv.m_AnalogOnly
#define insdiv_NotInstall	i__insdiv.m_NotInstall
#define insdiv_Install	i__insdiv.m_Install
#define insdiv_Hide	i__insdiv.m_Hide
#define insdiv_ChannelListVariant	i__insdiv.m_ChannelListVariant
#define insdiv_DefaultChannelList	i__insdiv.m_DefaultChannelList
#define insdiv_DualChannelList	i__insdiv.m_DualChannelList
#define insdiv_TripleChannelList	i__insdiv.m_TripleChannelList
#define insdiv_SkipInstallationPass	i__insdiv.m_SkipInstallationPass
#define insdiv_AutoCommitOnInstallation	i__insdiv.m_AutoCommitOnInstallation
#define insdiv_SkipAnalog	IHsvPresetInstallationDiv_SkipAnalog
#define insdiv_SkipDigital	IHsvPresetInstallationDiv_SkipDigital
#define insdiv_SkipNone	IHsvPresetInstallationDiv_SkipNone
#define insdiv_ClearDataOnAutoInstallation	i__insdiv.m_ClearDataOnAutoInstallation
#define insdiv_AnalogInstallationSequence	i__insdiv.m_AnalogInstallationSequence
#define insdiv_PalOnly	IHsvPresetInstallationDiv_PalOnly
#define insdiv_PalSecam	IHsvPresetInstallationDiv_PalSecam
#define insdiv_SecamPal	IHsvPresetInstallationDiv_SecamPal
#define insdiv_SecamOnly	IHsvPresetInstallationDiv_SecamOnly
#define insdiv_CurrentCountryInvalidLCNSortKey1	i__insdiv.m_CurrentCountryInvalidLCNSortKey1
#define insdiv_CurrentCountryInvalidLCNSortKey2	i__insdiv.m_CurrentCountryInvalidLCNSortKey2
#define insdiv_CurrentCountryInvalidLCNSortKey3	i__insdiv.m_CurrentCountryInvalidLCNSortKey3
#define insdiv_CurrentCountryInvalidLCNSortKey4	i__insdiv.m_CurrentCountryInvalidLCNSortKey4
#define insdiv_CurrentCountryInvalidLCNSortKey5	i__insdiv.m_CurrentCountryInvalidLCNSortKey5
#define insdiv_OtherCountrySortKey1	i__insdiv.m_OtherCountrySortKey1
#define insdiv_OtherCountrySortKey2	i__insdiv.m_OtherCountrySortKey2
#define insdiv_OtherCountrySortKey3	i__insdiv.m_OtherCountrySortKey3
#define insdiv_OtherCountrySortKey4	i__insdiv.m_OtherCountrySortKey4
#define insdiv_OtherCountrySortKey5	i__insdiv.m_OtherCountrySortKey5
#define insdiv_KeyInvalid	IHsvPresetInstallationDiv_KeyInvalid
#define insdiv_KeyOriginalNetworkId	IHsvPresetInstallationDiv_KeyOriginalNetworkId
#define insdiv_KeyServiceType	IHsvPresetInstallationDiv_KeyServiceType
#define insdiv_KeyLCN	IHsvPresetInstallationDiv_KeyLCN
#define insdiv_KeyServiceName	IHsvPresetInstallationDiv_KeyServiceName
#define insdiv_KeyServiceId	IHsvPresetInstallationDiv_KeyServiceId
#define insdiv_MaxAnalogPresets	IHsvPresetInstallationDiv_MaxAnalogPresets
#define insdiv_SupportEmptyAnalogChannels	i__insdiv.m_SupportEmptyAnalogChannels
#define insdiv_StorePresetsOnStopInstallation	i__insdiv.m_StorePresetsOnStopInstallation
#define insdiv_DefaultTunerPresetFrequency	i__insdiv.m_DefaultTunerPresetFrequency
#define insdiv_MaxLCNValue	i__insdiv.m_MaxLCNValue
#define insdiv_FreqListSortedTableId	i__insdiv.m_FreqListSortedTableId
#define inserr_Ok	IHsvErrorCodeEx_Ok
#define inserr_BadParameter	IHsvErrorCodeEx_BadParameter
#define inserr_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define inserr_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define inserr_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define inserr_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define inserr_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define inserr_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define inserr_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define inserr_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define inserr_FileError	IHsvErrorCodeEx_FileError
#define inserr_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define inserr_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define inserr_NotSupported	IHsvErrorCodeEx_NotSupported
#define inserr_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define inserr_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define inserr_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define inserr_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define inserr_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define inserr_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define inserr_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define inserr_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define inserr_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define inserr_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define inserr_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define inserr_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define inserr_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define inserr_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define inserr_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define inserr_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define inserr_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define inserr_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define inserr_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define inserr_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define log_Information	IHsvLog_Information
#define log_SoftErr	IHsvLog_SoftErr
#define log_FatalErr	IHsvLog_FatalErr
#define mctl_InvalidMedia	IHsvMediaControl_InvalidMedia
#define mctl_Video	IHsvMediaControl_Video
#define mctl_Audio	IHsvMediaControl_Audio
#define mctl_Pcr	IHsvMediaControl_Pcr
#define mctl_Subtitle	IHsvMediaControl_Subtitle
#define mctl_ClosedCaption	IHsvMediaControl_ClosedCaption
#define mctl_Teletext	IHsvMediaControl_Teletext
#define mctl_IPSubtitle	IHsvMediaControl_IPSubtitle
#define mctl_IPClosedCaption	IHsvMediaControl_IPClosedCaption
#define mctl_InvalidSelector	IHsvMediaControl_InvalidSelector
#define mctl_Language	IHsvMediaControl_Language
#define mctl_Type	IHsvMediaControl_Type
#define mctl_Pid	IHsvMediaControl_Pid
#define mctl_VIAssociation	IHsvMediaControl_VIAssociation
#define mctl_VIPrimaryAssociation	IHsvMediaControl_VIPrimaryAssociation
#define mctl_StreamType	IHsvMediaControl_StreamType
#define mpegsecnN_PmtData	IHsvMpegSectionsNotify_PmtData
#define mpegsecnN_PmtAcquisitionComplete	IHsvMpegSectionsNotify_PmtAcquisitionComplete
#define mpldiv_AvSignalDetectionTimeOut	i__mpldiv.m_AvSignalDetectionTimeOut
#define mpldiv_HearingImpairedOn	i__mpldiv.m_HearingImpairedOn
#define mpldiv_VisuallyImpairedOn	i__mpldiv.m_VisuallyImpairedOn
#define mpldiv_SubtitleOn	i__mpldiv.m_SubtitleOn
#define mpldiv_PidCachingEnabled	i__mpldiv.m_PidCachingEnabled
#define nvmapps_CookieNvmInfo	i__nvmapps.m_CookieNvmInfo
#define nvmapps_NumberOfEntries	IHsvCookieNvmInfo_NumberOfEntries
#define nvmapps_InvalidNvmID	IHsvCookieNvmInfo_InvalidNvmID
#define nvmcesvc_CookieNvmInfo	i__nvmcesvc.m_CookieNvmInfo
#define nvmcesvc_NumberOfEntries	IHsvCookieNvmInfo_NumberOfEntries
#define nvmcesvc_InvalidNvmID	IHsvCookieNvmInfo_InvalidNvmID
#define nvmids_InstSettingsInstallMode	i__nvmids.m_InstSettingsInstallMode
#define nvmids_LastPresetType	i__nvmids.m_LastPresetType
#define nvmids_LastPresetlPtc	i__nvmids.m_LastPresetlPtc
#define nvmids_LastPresetOnePartNo	i__nvmids.m_LastPresetOnePartNo
#define nvmids_LastPresetAnalogNo	i__nvmids.m_LastPresetAnalogNo
#define nvmids_LastPresetDigit	i__nvmids.m_LastPresetDigit
#define nvmids_LastPresetTwoPartMajorNo	i__nvmids.m_LastPresetTwoPartMajorNo
#define nvmids_LastPresetTwoPartMinorNo	i__nvmids.m_LastPresetTwoPartMinorNo
#define nvmids_LastSource	i__nvmids.m_LastSource
#define nvmids_LstStatParentalRatingAge	i__nvmids.m_LstStatParentalRatingAge
#define nvmids_LstStatParentalRatingDrugs	i__nvmids.m_LstStatParentalRatingDrugs
#define nvmids_LstStatParentalRatingViolence	i__nvmids.m_LstStatParentalRatingViolence
#define nvmids_LstStatParentalRatingSex	i__nvmids.m_LstStatParentalRatingSex
#define nvmids_InstSettingsClosedCaptions	i__nvmids.m_InstSettingsClosedCaptions
#define nvmids_InstSettingsSubtitle	i__nvmids.m_InstSettingsSubtitle
#define nvmids_LstStatDVBParentalRating	i__nvmids.m_LstStatDVBParentalRating
#define nvmpa_optTrue	IProdApiNvmProtectedAccessExEx_optTrue
#define nvmpa_optFalse	IProdApiNvmProtectedAccessExEx_optFalse
#define nvmpa_optInvalid	IProdApiNvmProtectedAccessExEx_optInvalid
#define nvmtxt_CookieNvmInfo	i__nvmtxt.m_CookieNvmInfo
#define nvmtxt_NumberOfEntries	IHsvCookieNvmInfo_NumberOfEntries
#define nvmtxt_InvalidNvmID	IHsvCookieNvmInfo_InvalidNvmID
#define pen_PumpEngine	i__pen.m_PumpEngine
#define pgctl_Terrestrial	IHsvProgramDataControl_Terrestrial
#define pgctl_Cable	IHsvProgramDataControl_Cable
#define pgctl_Satellite	IHsvProgramDataControl_Satellite
#define pgctl3_Terrestrial	IHsvProgramDataControl3_Terrestrial
#define pgctl3_Cable	IHsvProgramDataControl3_Cable
#define pgctl3_Satellite	IHsvProgramDataControl3_Satellite
#define pgctl3_CcOn	IHsvProgramDataControl3_CcOn
#define pgctl3_CcOff	IHsvProgramDataControl3_CcOff
#define pgctl3_CcOnDuringMute	IHsvProgramDataControl3_CcOnDuringMute
#define pgctl3_SubtitleOff	IHsvProgramDataControl3_SubtitleOff
#define pgctl3_SubtitleOn	IHsvProgramDataControl3_SubtitleOn
#define pgctl3_SubtitleOnDuringMute	IHsvProgramDataControl3_SubtitleOnDuringMute
#define pgctl3_SelectionTypeNormal	IHsvProgramDataControl3_SelectionTypeNormal
#define pgctl3_SelectionTypeQuite	IHsvProgramDataControl3_SelectionTypeQuite
#define pgctl3_SelectionTypeNonDestructive	IHsvProgramDataControl3_SelectionTypeNonDestructive
#define pgctl3_SelectionTypeQuiteNonDestructive	IHsvProgramDataControl3_SelectionTypeQuiteNonDestructive
#define pgdat_BoolLock	IHsvProgramData3_BoolLock
#define pgdat_BoolFavorite	IHsvProgramData3_BoolFavorite
#define pgdat_BoolFavorite1	IHsvProgramData3_BoolFavorite1
#define pgdat_BoolFavorite2	IHsvProgramData3_BoolFavorite2
#define pgdat_BoolFavorite3	IHsvProgramData3_BoolFavorite3
#define pgdat_BoolPreferredFavorite	IHsvProgramData3_BoolPreferredFavorite
#define pgdat_BoolPreferredNicam	IHsvProgramData3_BoolPreferredNicam
#define pgdat_BoolPreferredStereo	IHsvProgramData3_BoolPreferredStereo
#define pgdat_BoolSAP	IHsvProgramData3_BoolSAP
#define pgdat_BoolHMProtectedChannel	IHsvProgramData3_BoolHMProtectedChannel
#define pgdat_BoolHMBlanked	IHsvProgramData3_BoolHMBlanked
#define pgdat_BoolUserHidden	IHsvProgramData3_BoolUserHidden
#define pgdat_BoolSystemHidden	IHsvProgramData3_BoolSystemHidden
#define pgdat_BoolNumericSelect	IHsvProgramData3_BoolNumericSelect
#define pgdat_BoolEpgChannel	IHsvProgramData3_BoolEpgChannel
#define pgdat_BoolEPGShortInfoEnabled	IHsvProgramData3_BoolEPGShortInfoEnabled
#define pgdat_BoolNewPreset	IHsvProgramData3_BoolNewPreset
#define pgdat_BoolFreeCiMode	IHsvProgramData3_BoolFreeCiMode
#define pgdat_BoolTuned	IHsvProgramData3_BoolTuned
#define pgdat_BoolDeTuned	IHsvProgramData3_BoolDeTuned
#define pgdat_BoolAttenuator	IHsvProgramData3_BoolAttenuator
#define pgdat_BoolAgcInstalled	IHsvProgramData3_BoolAgcInstalled
#define pgdat_BoolChannelVirgin	IHsvProgramData3_BoolChannelVirgin
#define pgdat_BoolUpdateName	IHsvProgramData3_BoolUpdateName
#define pgdat_IntDeltaVolume	IHsvProgramData3_IntDeltaVolume
#define pgdat_Nat32DateStamp	IHsvProgramData3_Nat32DateStamp
#define pgdat_Nat32AppsCookie	IHsvProgramData3_Nat32AppsCookie
#define pgdat_Nat32TxtCookie	IHsvProgramData3_Nat32TxtCookie
#define pgdat_Nat32CesvcCookie	IHsvProgramData3_Nat32CesvcCookie
#define pgdat_Nat32DvbType	IHsvProgramData3_Nat32DvbType
#define pgdat_StringChannelName	IHsvProgramData3_StringChannelName
#define pgdat_StringExtChannelName	IHsvProgramData3_StringExtChannelName
#define pgdat_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat_IntTvSystem	IHsvProgramData3_IntTvSystem
#define pgdat_IntModulation	IHsvProgramData3_IntModulation
#define pgdat_IntNewChannelMap	IHsvProgramData3_IntNewChannelMap
#define pgdat_IntSignalStrength	IHsvProgramData3_IntSignalStrength
#define pgdat_IntSignalQuality	IHsvProgramData3_IntSignalQuality
#define pgdat_IntColoursystem	IHsvProgramData3_IntColoursystem
#define pgdat_IntDecoderType	IHsvProgramData3_IntDecoderType
#define pgdat_IntFineTuneOffset	IHsvProgramData3_IntFineTuneOffset
#define pgdat_IntFineTuneFrequency	IHsvProgramData3_IntFineTuneFrequency
#define pgdat_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat_IntNetworkId	IHsvProgramData3_IntNetworkId
#define pgdat_IntOriginalNwId	IHsvProgramData3_IntOriginalNwId
#define pgdat_IntTsid	IHsvProgramData3_IntTsid
#define pgdat_IntServiceId	IHsvProgramData3_IntServiceId
#define pgdat_IntServiceType	IHsvProgramData3_IntServiceType
#define pgdat_IntPmtPid	IHsvProgramData3_IntPmtPid
#define pgdat_IntPcrPid	IHsvProgramData3_IntPcrPid
#define pgdat_IntVideoPid	IHsvProgramData3_IntVideoPid
#define pgdat_IntVideoStreamType	IHsvProgramData3_IntVideoStreamType
#define pgdat_IntAudioPid	IHsvProgramData3_IntAudioPid
#define pgdat_IntAudioStreamType	IHsvProgramData3_IntAudioStreamType
#define pgdat_IntSecAudioPid	IHsvProgramData3_IntSecAudioPid
#define pgdat_IntSecAudioStreamType	IHsvProgramData3_IntSecAudioStreamType
#define pgdat_IntInstallMode	IHsvProgramData3_IntInstallMode
#define pgdat_IntCniNi	IHsvProgramData3_IntCniNi
#define pgdat_IntDataIndicator	IHsvProgramData3_IntDataIndicator
#define pgdat_IntPresetNumber	IHsvProgramData3_IntPresetNumber
#define pgdat_IntModulationType	IHsvProgramData3_IntModulationType
#define pgdat_IntLCN	IHsvProgramData3_IntLCN
#define pgdat_IntStreamPriority	IHsvProgramData3_IntStreamPriority
#define pgdat_IntHMMapChannelNo	IHsvProgramData3_IntHMMapChannelNo
#define pgdat_IntPtc	IHsvProgramData3_IntPtc
#define pgdat_IntAssociatedDecoder	IHsvProgramData3_IntAssociatedDecoder
#define pgdat_IntChannelBandwidth	IHsvProgramData3_IntChannelBandwidth
#define pgdat_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat_Antenna	IHsvProgramData3_Antenna
#define pgdat_Cable	IHsvProgramData3_Cable
#define pgdat_IntSystemHidden	IHsvProgramData3_IntSystemHidden
#define pgdat_IntNumericSelect	IHsvProgramData3_IntNumericSelect
#define pgdat_IntNewChannel	IHsvProgramData3_IntNewChannel
#define pgdat_StringSatelliteName	IHsvProgramData3_StringSatelliteName
#define pgdat_IntSrcambledStatus	IHsvProgramData3_IntSrcambledStatus
#define pgdat_IntInstalledSatelliteNumber	IHsvProgramData3_IntInstalledSatelliteNumber
#define pgdat_IntUserHidden	IHsvProgramData3_IntUserHidden
#define pgdat_FavoriteNumber	IHsvProgramData3_FavoriteNumber
#define pgdat_FavoriteNumber1	IHsvProgramData3_FavoriteNumber1
#define pgdat_FavoriteNumber2	IHsvProgramData3_FavoriteNumber2
#define pgdat_FavoriteNumber3	IHsvProgramData3_FavoriteNumber3
#define pgdat_IntEPGEnabled	IHsvProgramData3_IntEPGEnabled
#define pgdat_IntHbbTvOption	IHsvProgramData3_IntHbbTvOption
#define pgdat_BoolChannelLock	IHsvProgramData3_BoolChannelLock
#define pgdat_StringTxtPages	IHsvProgramData3_StringTxtPages
#define pgdat_IntLogoURL	IHsvProgramData3_IntLogoURL
#define pgdat_BoolMatchBrandFlag	IHsvProgramData3_BoolMatchBrandFlag
#define pgdat_Nat32NumBrandIds	IHsvProgramData3_Nat32NumBrandIds
#define pgdat_StringBrandIds	IHsvProgramData3_StringBrandIds
#define pgdat_Nat16PrimaryRegion	IHsvProgramData3_Nat16PrimaryRegion
#define pgdat_Nat16SecondaryRegion	IHsvProgramData3_Nat16SecondaryRegion
#define pgdat_IntTertiaryRegion	IHsvProgramData3_IntTertiaryRegion
#define pgdat_Nat32CountryCode	IHsvProgramData3_Nat32CountryCode
#define pgdat_Nat64UniqueNodeId	IHsvProgramData3_Nat64UniqueNodeId
#define pgdat_BoolUserModifiedLogo	IHsvProgramData3_BoolUserModifiedLogo
#define pgdat_MultipleLCN	IHsvProgramData3_MultipleLCN
#define pgdat_MultiplePreset	IHsvProgramData3_MultiplePreset
#define pgdatNxx_MajorChannel	IHsvProgramDataNotifyExEx_MajorChannel
#define pgdatNxx_MinorChannel	IHsvProgramDataNotifyExEx_MinorChannel
#define pgdatNxx_PIDs	IHsvProgramDataNotifyExEx_PIDs
#define pgdiv_DefaultSystemLanguage	i__pgdiv.m_DefaultSystemLanguage
#define pgdiv_OobSupported	i__pgdiv.m_OobSupported
#define pgdiv_NoOfMinorChannelsToStoreAntenna	i__pgdiv.m_NoOfMinorChannelsToStoreAntenna
#define pgdiv_NoOfMinorChannelsToStoreCable	i__pgdiv.m_NoOfMinorChannelsToStoreCable
#define pgdiv_MaxNoOfChannelsToStoreAntenna	i__pgdiv.m_MaxNoOfChannelsToStoreAntenna
#define pgdiv_MaxNoOfChannelsToStoreCable	i__pgdiv.m_MaxNoOfChannelsToStoreCable
#define pgdiv_MaxNoOfPrograms	i__pgdiv.m_MaxNoOfPrograms
#define pgdiv_PersistentMemoryFileVersion	i__pgdiv.m_PersistentMemoryFileVersion
#define pgdiv_DefaultTunerPresetFrequency	i__pgdiv.m_DefaultTunerPresetFrequency
#define pgdiv_HsvAntennaMajorTable	i__pgdiv.m_HsvAntennaMajorTable
#define pgdiv_HsvAntennaPtcTable	i__pgdiv.m_HsvAntennaPtcTable
#define pgdiv_HsvCableMajorTable	i__pgdiv.m_HsvCableMajorTable
#define pgdiv_HsvCablePtcTable	i__pgdiv.m_HsvCablePtcTable
#define pgdiv_HsvOobMajorTable	i__pgdiv.m_HsvOobMajorTable
#define pgdiv_HsvOobPtcTable	i__pgdiv.m_HsvOobPtcTable
#define pgdiv_PersistentMemUpdateTimeout	i__pgdiv.m_PersistentMemUpdateTimeout
#define pgdiv_CookieDefaultValue	i__pgdiv.m_CookieDefaultValue
#define pgdiv_EpgCookieDefaultValue	i__pgdiv.m_EpgCookieDefaultValue
#define pgdiv_TxtCookieDefaultValue	i__pgdiv.m_TxtCookieDefaultValue
#define pgdiv_AppsCookieDefaultValue	i__pgdiv.m_AppsCookieDefaultValue
#define pgdiv_ProgramViewForUS	i__pgdiv.m_ProgramViewForUS
#define pgdiv_ChannelNameLength	i__pgdiv.m_ChannelNameLength
#define pgdiv_HsvAntennaAnalogTable	i__pgdiv.m_HsvAntennaAnalogTable
#define pgdiv_HsvAntennaDigSrvcTable	i__pgdiv.m_HsvAntennaDigSrvcTable
#define pgdiv_HsvAntennaDigPtcTable	i__pgdiv.m_HsvAntennaDigPtcTable
#define pgdiv_HsvAntennaFreqMapTable	i__pgdiv.m_HsvAntennaFreqMapTable
#define pgdiv_HsvCableAnalogTable	i__pgdiv.m_HsvCableAnalogTable
#define pgdiv_HsvCableDigSrvcTable	i__pgdiv.m_HsvCableDigSrvcTable
#define pgdiv_HsvCableDigPtcTable	i__pgdiv.m_HsvCableDigPtcTable
#define pgdiv_HsvCableFreqMapTable	i__pgdiv.m_HsvCableFreqMapTable
#define pgdiv_MaxNoOfChannelsToStoreAntennaUserTable	i__pgdiv.m_MaxNoOfChannelsToStoreAntennaUserTable
#define pgdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	i__pgdiv.m_MaxNoOfChannelsToStoreAntennaDigSrvcTable
#define pgdiv_MaxNoOfChannelsToStoreAntennaDigTSTable	i__pgdiv.m_MaxNoOfChannelsToStoreAntennaDigTSTable
#define pgdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	i__pgdiv.m_MaxNoOfChannelsToStoreAntennaDigPtcTable
#define pgdiv_MaxNoOfChannelsToStoreAntennaAnalogTable	i__pgdiv.m_MaxNoOfChannelsToStoreAntennaAnalogTable
#define pgdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	i__pgdiv.m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable
#define pgdiv_MaxNoOfChannelsToStoreCableUserTable	i__pgdiv.m_MaxNoOfChannelsToStoreCableUserTable
#define pgdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	i__pgdiv.m_MaxNoOfChannelsToStoreCableDigSrvcTable
#define pgdiv_MaxNoOfChannelsToStoreCableDigTSTable	i__pgdiv.m_MaxNoOfChannelsToStoreCableDigTSTable
#define pgdiv_MaxNoOfChannelsToStoreCableDigPtcTable	i__pgdiv.m_MaxNoOfChannelsToStoreCableDigPtcTable
#define pgdiv_MaxNoOfChannelsToStoreCableAnalogTable	i__pgdiv.m_MaxNoOfChannelsToStoreCableAnalogTable
#define pgdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	i__pgdiv.m_MaxNoOfMultiplexsToStoreCableFreqMapTable
#define pgdiv_AnalogOnly	i__pgdiv.m_AnalogOnly
#define pgdiv_PrimaryFileVersion	i__pgdiv.m_PrimaryFileVersion
#define pgdiv_SecondaryFileVersion	i__pgdiv.m_SecondaryFileVersion
#define pgdiv_ChannelListVariant	i__pgdiv.m_ChannelListVariant
#define pgdiv_DefaultChannelList	IHsvProgramDataDiv_DefaultChannelList
#define pgdiv_DualChannelList	IHsvProgramDataDiv_DualChannelList
#define pgdiv_TripleChannelList	IHsvProgramDataDiv_TripleChannelList
#define pgdiv_ChannelNameSource	i__pgdiv.m_ChannelNameSource
#define pgdiv_ExtendedName	IHsvProgramDataDiv_ExtendedName
#define pgdiv_ShortName	IHsvProgramDataDiv_ShortName
#define pgdiv_Default	IHsvProgramDataDiv_Default
#define pgitr_All	IHsvProgramIterator_All
#define pgitr_Digital	IHsvProgramIterator_Digital
#define pgitr_Analog	IHsvProgramIterator_Analog
#define pgitr_Mux	IHsvProgramIterator_Mux
#define pgitr_ChannelsInMux	IHsvProgramIterator_ChannelsInMux
#define pgitr_None	IHsvProgramIterator_None
#define pgitr_Favorite	IHsvProgramIterator_Favorite
#define pgitr_Favorite1	IHsvProgramIterator_Favorite1
#define pgitr_Favorite2	IHsvProgramIterator_Favorite2
#define pgitr_Favorite3	IHsvProgramIterator_Favorite3
#define pgitr_Locked	IHsvProgramIterator_Locked
#define pgitr_UnLocked	IHsvProgramIterator_UnLocked
#define pgitr_EpgChannel	IHsvProgramIterator_EpgChannel
#define pgitr_NonEpgChannel	IHsvProgramIterator_NonEpgChannel
#define pgitr_SystemHidden	IHsvProgramIterator_SystemHidden
#define pgitr_NonSystemHidden	IHsvProgramIterator_NonSystemHidden
#define pgitr_UserHidden	IHsvProgramIterator_UserHidden
#define pgitr_NonUserHidden	IHsvProgramIterator_NonUserHidden
#define pgitr_AudioOnly	IHsvProgramIterator_AudioOnly
#define pgitr_NonAudioOnly	IHsvProgramIterator_NonAudioOnly
#define pgitr_DvbT	IHsvProgramIterator_DvbT
#define pgitr_DvbC	IHsvProgramIterator_DvbC
#define pgitr_DvbTLite	IHsvProgramIterator_DvbTLite
#define pgitr_DvbCLite	IHsvProgramIterator_DvbCLite
#define pgitr_DvbS2	IHsvProgramIterator_DvbS2
#define pgitr_PreferredFavorite	IHsvProgramIterator_PreferredFavorite
#define pgsel_DefaultSelection	IHsvProgramSelection2_DefaultSelection
#define pgsel_SilentSelection	IHsvProgramSelection2_SilentSelection
#define pgsel_ControlledSelection	IHsvProgramSelection2_ControlledSelection
#define pgsel_ReplacementSelection	IHsvProgramSelection2_ReplacementSelection
#define pgsel_BreakIn	IHsvProgramSelection2_BreakIn
#define pgsel_DecoderBreakIn	IHsvProgramSelection2_DecoderBreakIn
#define pgsel_MultifeedSelection	IHsvProgramSelection2_MultifeedSelection
#define pgsel_NDTSelection	IHsvProgramSelection2_NDTSelection
#define pgsel_PriorityHigh	IHsvProgramSelection2_PriorityHigh
#define pgsel_PriorityMed	IHsvProgramSelection2_PriorityMed
#define pgsel_PriorityLow	IHsvProgramSelection2_PriorityLow
#define pgsel_Frequency	IHsvProgramSelection2_Frequency
#define pgsel_ModulationType	IHsvProgramSelection2_ModulationType
#define pgsel_TvSystem	IHsvProgramSelection2_TvSystem
#define pgsel_AudioPid	IHsvProgramSelection2_AudioPid
#define pgsel_VideoPid	IHsvProgramSelection2_VideoPid
#define pgsel_PcrPid	IHsvProgramSelection2_PcrPid
#define pgsel_ProgramNumber	IHsvProgramSelection2_ProgramNumber
#define pgsel_SymbolRate	IHsvProgramSelection2_SymbolRate
#define pgsel_DecoderType	IHsvProgramSelection2_DecoderType
#define pgsel_InvalidAttribute	IHsvProgramSelection2_InvalidAttribute
#define plfdesigid_DesignatorNone	IPlfApiDesignatorId_DesignatorNone
#define plfdesigid_DesignatorAll	IPlfApiDesignatorId_DesignatorAll
#define plfdesigid_DesignatorAnalog	IPlfApiDesignatorId_DesignatorAnalog
#define plfdesigid_DesignatorDigital	IPlfApiDesignatorId_DesignatorDigital
#define plfdesigid_DesignatorMpeg2	IPlfApiDesignatorId_DesignatorMpeg2
#define plfdesigid_DesignatorMpeg4	IPlfApiDesignatorId_DesignatorMpeg4
#define plfdesigid_DesignatorJpg	IPlfApiDesignatorId_DesignatorJpg
#define plfdesigid_DesignatorMp3	IPlfApiDesignatorId_DesignatorMp3
#define plfdesigid_DesignatorWm	IPlfApiDesignatorId_DesignatorWm
#define plfdesigid_DesignatorDivX	IPlfApiDesignatorId_DesignatorDivX
#define plfdesigid_DesignatorMpegTs	IPlfApiDesignatorId_DesignatorMpegTs
#define plfdesigid_DesignatorRm	IPlfApiDesignatorId_DesignatorRm
#define plfdesigid_DesignatorMkv	IPlfApiDesignatorId_DesignatorMkv
#define plfdesigid_DesignatorMpegTsDmx	IPlfApiDesignatorId_DesignatorMpegTsDmx
#define plfdesigid_DesignatorData	IPlfApiDesignatorId_DesignatorData
#define plfdesigid_DesignatorHls	IPlfApiDesignatorId_DesignatorHls
#define plfdesigid_DesignatorWidevine	IPlfApiDesignatorId_DesignatorWidevine
#define plfdesigid_DesignatorMss	IPlfApiDesignatorId_DesignatorMss
#define plfdesigid_DesignatorMhegTsDmx	IPlfApiDesignatorId_DesignatorMhegTsDmx
#define plfdesigid_DesignatorMpegDash_Fmp4	IPlfApiDesignatorId_DesignatorMpegDash_Fmp4
#define plfdesigid_DesignatorMpegDash_TS	IPlfApiDesignatorId_DesignatorMpegDash_TS
#define plfdesigid_DesignatorYtlb_Fmp4	IPlfApiDesignatorId_DesignatorYtlb_Fmp4
#define plfdesigid_DesignatorNetFlix	IPlfApiDesignatorId_DesignatorNetFlix
#define plfdmx_CrcModeSkipBadSections	IPlfApiTsDmxAbstractEx_CrcModeSkipBadSections
#define plfdmx_CrcModeAcceptAllSections	IPlfApiTsDmxAbstractEx_CrcModeAcceptAllSections
#define plfdmx_CrcModeDontCheckCrc	IPlfApiTsDmxAbstractEx_CrcModeDontCheckCrc
#define plfdmx_FilterDepth	IPlfApiTsDmxAbstractEx_FilterDepth
#define plfdmx_StreamTypeInvalid	IPlfApiTsDmxAbstractEx_StreamTypeInvalid
#define plfdmx_StreamTypemp1v	IPlfApiTsDmxAbstractEx_StreamTypemp1v
#define plfdmx_StreamTypemp2v	IPlfApiTsDmxAbstractEx_StreamTypemp2v
#define plfdmx_StreamTypemp4v	IPlfApiTsDmxAbstractEx_StreamTypemp4v
#define plfdmx_StreamTypemp1a	IPlfApiTsDmxAbstractEx_StreamTypemp1a
#define plfdmx_StreamTypemp2a	IPlfApiTsDmxAbstractEx_StreamTypemp2a
#define plfdmx_StreamTypemp4a	IPlfApiTsDmxAbstractEx_StreamTypemp4a
#define plfdmx_StreamTypettxt	IPlfApiTsDmxAbstractEx_StreamTypettxt
#define plfdmx_StreamTypesubt	IPlfApiTsDmxAbstractEx_StreamTypesubt
#define plfdmx_StreamTypepcr	IPlfApiTsDmxAbstractEx_StreamTypepcr
#define plfdmx_StreamTypeac3	IPlfApiTsDmxAbstractEx_StreamTypeac3
#define plfdmx_StreamTypeh264	IPlfApiTsDmxAbstractEx_StreamTypeh264
#define plfdmx_StreamTypedivx	IPlfApiTsDmxAbstractEx_StreamTypedivx
#define plfdmx_StreamTypevc1	IPlfApiTsDmxAbstractEx_StreamTypevc1
#define plfdmx_StreamTypeaac	IPlfApiTsDmxAbstractEx_StreamTypeaac
#define plfdmx_StreamTypeheaac	IPlfApiTsDmxAbstractEx_StreamTypeheaac
#define plfdmx_StreamTypewma	IPlfApiTsDmxAbstractEx_StreamTypewma
#define plfdmx_StreamTypeddplus	IPlfApiTsDmxAbstractEx_StreamTypeddplus
#define plfdmx_StreamTypedts	IPlfApiTsDmxAbstractEx_StreamTypedts
#define plfdmx_StreamTypemmw	IPlfApiTsDmxAbstractEx_StreamTypemmw
#define plfdmx_StreamTypemma	IPlfApiTsDmxAbstractEx_StreamTypemma
#define plfdmx_StreamTypeOther	IPlfApiTsDmxAbstractEx_StreamTypeOther
#define plfdmx_StreamTypeLpcm	IPlfApiTsDmxAbstractEx_StreamTypeLpcm
#define plfdmx_InvalidSubscrId	IPlfApiTsDmxAbstractEx_InvalidSubscrId
#define plfdmx_ScramblingUnknown	IPlfApiTsDmxAbstractEx_ScramblingUnknown
#define plfdmx_NotScrambled	IPlfApiTsDmxAbstractEx_NotScrambled
#define plfdmx_Scrambled	IPlfApiTsDmxAbstractEx_Scrambled
#define plfdmx_MediaTypeAudio	IPlfApiTsDmxAbstractEx_MediaTypeAudio
#define plfdmx_MediaTypeVideo	IPlfApiTsDmxAbstractEx_MediaTypeVideo
#define plfdmx_MediaTypeAudioDesc	IPlfApiTsDmxAbstractEx_MediaTypeAudioDesc
#define plferrids_Ok	IPlfApiErrorIds_Ok
#define plferrids_ResourceNotOwned	IPlfApiErrorIds_ResourceNotOwned
#define plferrids_InterfaceNotAvailable	IPlfApiErrorIds_InterfaceNotAvailable
#define plferrids_InterfaceNotImplemented	IPlfApiErrorIds_InterfaceNotImplemented
#define plferrids_Other	IPlfApiErrorIds_Other
#define plfres_AudioFeaturing	ITvPlatformResource_AudioFeaturing
#define plfres_Connectivity	ITvPlatformResource_Connectivity
#define plfres_Frontend	ITvPlatformResource_Frontend
#define plfres_General	ITvPlatformResource_General
#define plfres_Infrastructure	ITvPlatformResource_Infrastructure
#define plfres_Source	ITvPlatformResource_Source
#define plfres_VideoFeaturing	ITvPlatformResource_VideoFeaturing
#define plfres_Xray	ITvPlatformResource_Xray
#define plfres_Scale	ITvPlatformResource_Scale
#define plfres_Gfx	ITvPlatformResource_Gfx
#define plfres_Mute	ITvPlatformResource_Mute
#define plfres_FullState	ITvPlatformResource_FullState
#define plfres_SubState	ITvPlatformResource_SubState
#define plfres_IdleState	ITvPlatformResource_IdleState
#define plfres_FullStateWithVideoScale	ITvPlatformResource_FullStateWithVideoScale
#define plfres_Invalid	ITvPlatformResource_Invalid
#define plfres_FullWithScaleState	ITvPlatformResource_FullWithScaleState
#define plfres_IdleWithMuteState	ITvPlatformResource_IdleWithMuteState
#define plfres_FullStateWithOutMute	ITvPlatformResource_FullStateWithOutMute
#define plfres_FrontEndState	ITvPlatformResource_FrontEndState
#define plfres_ScaleState	ITvPlatformResource_ScaleState
#define plfsrcid_SrcInvalid	IPlfApiSourceId_SrcInvalid
#define plfsrcid_SrcNone	IPlfApiSourceId_SrcNone
#define plfsrcid_SrcTuner	IPlfApiSourceId_SrcTuner
#define plfsrcid_SrcFront	IPlfApiSourceId_SrcFront
#define plfsrcid_SrcAv1	IPlfApiSourceId_SrcAv1
#define plfsrcid_SrcAv2	IPlfApiSourceId_SrcAv2
#define plfsrcid_SrcAv3	IPlfApiSourceId_SrcAv3
#define plfsrcid_SrcAv4	IPlfApiSourceId_SrcAv4
#define plfsrcid_SrcAv5	IPlfApiSourceId_SrcAv5
#define plfsrcid_SrcAv6	IPlfApiSourceId_SrcAv6
#define plfsrcid_SrcAv7	IPlfApiSourceId_SrcAv7
#define plfsrcid_SrcAv8	IPlfApiSourceId_SrcAv8
#define plfsrcid_SrcAv9	IPlfApiSourceId_SrcAv9
#define plfsrcid_SrcAv10	IPlfApiSourceId_SrcAv10
#define plfsrcid_SrcHdmi1	IPlfApiSourceId_SrcHdmi1
#define plfsrcid_SrcHdmi2	IPlfApiSourceId_SrcHdmi2
#define plfsrcid_SrcHdmi3	IPlfApiSourceId_SrcHdmi3
#define plfsrcid_SrcHdmi4	IPlfApiSourceId_SrcHdmi4
#define plfsrcid_SrcHdmi5	IPlfApiSourceId_SrcHdmi5
#define plfsrcid_SrcUrl	IPlfApiSourceId_SrcUrl
#define plfsrcid_SrcBolton	IPlfApiSourceId_SrcBolton
#define plfsrcid_SrcVga	IPlfApiSourceId_SrcVga
#define plfsrcid_SrcFrontHdmi	IPlfApiSourceId_SrcFrontHdmi
#define plfsrcid_SrcSkype	IPlfApiSourceId_SrcSkype
#define plfsrcid_SrcWifiDisplay	IPlfApiSourceId_SrcWifiDisplay
#define plfsrcid_SrcData	IPlfApiSourceId_SrcData
#define plfsrcid_SrcAudioIn	IPlfApiSourceId_SrcAudioIn
#define poolids_StringPool	i__poolids.m_StringPool
#define poolids_DescPool	i__poolids.m_DescPool
#define poolids_PmtSectionPool	i__poolids.m_PmtSectionPool
#define poolids_BufferPool	i__poolids.m_BufferPool
#define poolids_StringPoolVc	i__poolids.m_StringPoolVc
#define poolids_SectionBufferPool	i__poolids.m_SectionBufferPool
#define poolids_PesBufferPool	i__poolids.m_PesBufferPool
#define poolids_MsgPoolId	i__poolids.m_MsgPoolId
#define powctlx_SemiSbyAcquisition	ISvcPowerStateControlEx_SemiSbyAcquisition
#define powctlx_SemiSbyClkCalib	ISvcPowerStateControlEx_SemiSbyClkCalib
#define powctlx_SemiSbyTvtvAcq	ISvcPowerStateControlEx_SemiSbyTvtvAcq
#define powctlx_SemiSbyInstall	ISvcPowerStateControlEx_SemiSbyInstall
#define powctlx_SemiSbyRecording	ISvcPowerStateControlEx_SemiSbyRecording
#define powctlx_SemiSbyHoming	ISvcPowerStateControlEx_SemiSbyHoming
#define rtk_PrioHighest	i__rtk.m_PrioHighest
#define rtk_PrioHigh	i__rtk.m_PrioHigh
#define rtk_PrioAboveNormal	i__rtk.m_PrioAboveNormal
#define rtk_PrioNormal	i__rtk.m_PrioNormal
#define rtk_PrioBelowNormal	i__rtk.m_PrioBelowNormal
#define rtk_PrioLow	i__rtk.m_PrioLow
#define rtk_PrioLowest	i__rtk.m_PrioLowest
#define sdmdiv_NoOfDescriptors	i__sdmdiv.m_NoOfDescriptors
#define sdmdiv_NoOfEvents	i__sdmdiv.m_NoOfEvents

#define sdmdiv_MaxStringLength	i__sdmdiv.m_MaxStringLength

#define sdmdiv_RRTParsingAllowed	i__sdmdiv.m_RRTParsingAllowed
#define sdmdiv_SystemTime	i__sdmdiv.m_SystemTime
#define sdmdiv_RatingStringLength	i__sdmdiv.m_RatingStringLength
#define sdmdiv_Enable12hourEitParsing	i__sdmdiv.m_Enable12hourEitParsing
#define sdmdiv_MaxPmtMonitors	i__sdmdiv.m_MaxPmtMonitors
#define sdmdiv_ChannelNameLength	i__sdmdiv.m_ChannelNameLength
#define sdmdiv_SystemLanguage	i__sdmdiv.m_SystemLanguage
#define srcstp_Success	IHsvSourceSetup_Success
#define srcstp_SourceSetupNotAllowed	IHsvSourceSetup_SourceSetupNotAllowed
#define srcstp_SourceSetupNotApplied	IHsvSourceSetup_SourceSetupNotApplied
#define srcstp_WaitForSourceSetupApplyNotify	IHsvSourceSetup_WaitForSourceSetupApplyNotify
#define srcstp_ResourceNotAvailable	IHsvSourceSetup_ResourceNotAvailable
#define srcstp_WndDesignatorNone	IHsvSourceSetup_WndDesignatorNone
#define srcstp_WndDesignatorProcessed	IHsvSourceSetup_WndDesignatorProcessed
#define srcstp_WndDesignatorUnProcessed	IHsvSourceSetup_WndDesignatorUnProcessed
#define srtdb2_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb2_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb2_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdbids_VcTableMain	i__srtdbids.m_VcTableMain
#define srtdbids_VcTableAux	i__srtdbids.m_VcTableAux
#define srtdbids_MgtTableMain	i__srtdbids.m_MgtTableMain
#define srtdbids_MgtTableAux	i__srtdbids.m_MgtTableAux
#define srtdbids_PmtTableMain	i__srtdbids.m_PmtTableMain
#define srtdbids_PmtTableAux	i__srtdbids.m_PmtTableAux
#define srtdbids_BasicPidInfoMain	i__srtdbids.m_BasicPidInfoMain
#define srtdbids_BasicPidInfoAux	i__srtdbids.m_BasicPidInfoAux
#define srtdbids_AudioInfoMain	i__srtdbids.m_AudioInfoMain
#define srtdbids_AudioInfoAux	i__srtdbids.m_AudioInfoAux
#define srtdbids_SubtitlingInfoMain	i__srtdbids.m_SubtitlingInfoMain
#define srtdbids_SubtitlingInfoAux	i__srtdbids.m_SubtitlingInfoAux
#define srtdbids_TeletextInfoMain	i__srtdbids.m_TeletextInfoMain
#define srtdbids_TeletextInfoAux	i__srtdbids.m_TeletextInfoAux
#define srtdbids_ComponentTagInfoMain	i__srtdbids.m_ComponentTagInfoMain
#define srtdbids_ComponentTagInfoAux	i__srtdbids.m_ComponentTagInfoAux
#define srtdbids_DatabroadcastInfoMain	i__srtdbids.m_DatabroadcastInfoMain
#define srtdbids_DatabroadcastInfoAux	i__srtdbids.m_DatabroadcastInfoAux
#define srtdbids_ReqTableMain	i__srtdbids.m_ReqTableMain
#define srtdbids_ReqTableAux	i__srtdbids.m_ReqTableAux
#define srtdbids_EitTableMain	i__srtdbids.m_EitTableMain
#define srtdbids_EitTableAux	i__srtdbids.m_EitTableAux
#define subid_Apps	IProdApiNvmSubIdsEx_Apps
#define subid_Txt	IProdApiNvmSubIdsEx_Txt
#define subid_Epg	IProdApiNvmSubIdsEx_Epg
#define subid_Zap	IProdApiNvmSubIdsEx_Zap
#define subid_Dlna	IProdApiNvmSubIdsEx_Dlna
#define subid_Ecd	IProdApiNvmSubIdsEx_Ecd
#define subid_Skype	IProdApiNvmSubIdsEx_Skype
#define subid_Cetv	IProdApiNvmSubIdsEx_Cetv
#define subid_Prod	IProdApiNvmSubIdsEx_Prod
#define subid_Cbmhg	IProdApiNvmSubIdsEx_Cbmhg
#define subid_NetTv	IProdApiNvmSubIdsEx_NetTv
#define subid_Play	IProdApiNvmSubIdsEx_Play
#define subid_Dvbs2	IProdApiNvmSubIdsEx_Dvbs2
#define subid_Eu	IProdApiNvmSubIdsEx_Eu
#define subid_Bra	IProdApiNvmSubIdsEx_Bra
#define subid_Home	IProdApiNvmSubIdsEx_Home
#define subid_Demo	IProdApiNvmSubIdsEx_Demo
#define subid_Upg	IProdApiNvmSubIdsEx_Upg
#define subid_Tv	IProdApiNvmSubIdsEx_Tv
#define subid_Deasvc	IProdApiNvmSubIdsEx_Deasvc
#define subid_Txsvc	IProdApiNvmSubIdsEx_Txsvc
#define subid_Fac	IProdApiNvmSubIdsEx_Fac
#define subid_Tvsvc	IProdApiNvmSubIdsEx_Tvsvc
#define subid_Svpsc	IProdApiNvmSubIdsEx_Svpsc
#define subid_Ceinfra	IProdApiNvmSubIdsEx_Ceinfra
#define subid_Tvint	IProdApiNvmSubIdsEx_Tvint
#define subid_Ols	IProdApiNvmSubIdsEx_Ols
#define subid_Media	IProdApiNvmSubIdsEx_Media
#define subid_NotAllowed	IProdApiNvmSubIdsEx_NotAllowed
#define sysset_AudioFormatStandard	IHsvTcSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvTcSystemSettings_AudioFormatAdvanced
#define sysset5_Success	IAppApiSystemSettings5_Success
#define sysset5_NVMFailure	IAppApiSystemSettings5_NVMFailure
#define sysset5_CertificateDetectionNotDone	IAppApiSystemSettings5_CertificateDetectionNotDone
#define sysset5_InitFailure	IAppApiSystemSettings5_InitFailure
#define sysset5_AutoEpg	IAppApiSystemSettings5_AutoEpg
#define sysset5_DVBEpg	IAppApiSystemSettings5_DVBEpg
#define sysset5_IPEpg	IAppApiSystemSettings5_IPEpg
#define sysset5_Shop	IAppApiSystemSettings5_Shop
#define sysset5_Home	IAppApiSystemSettings5_Home
#define sysset5_clkSrcNone	IAppApiSystemSettings5_clkSrcNone
#define sysset5_clkSrcMainTuner	IAppApiSystemSettings5_clkSrcMainTuner
#define sysset5_clkSrcSatelliteTuner	IAppApiSystemSettings5_clkSrcSatelliteTuner
#define sysset5_clkSrcManualClock	IAppApiSystemSettings5_clkSrcManualClock
#define sysset5_avSrcNone	IAppApiSystemSettings5_avSrcNone
#define sysset5_avSrcMainTuner	IAppApiSystemSettings5_avSrcMainTuner
#define sysset5_avSrcSatellite	IAppApiSystemSettings5_avSrcSatellite
#define sysset5_avSrcAvIn0	IAppApiSystemSettings5_avSrcAvIn0
#define sysset5_avSrcAvIn1	IAppApiSystemSettings5_avSrcAvIn1
#define sysset5_avSrcAvIn2	IAppApiSystemSettings5_avSrcAvIn2
#define sysset5_avSrcAvIn3	IAppApiSystemSettings5_avSrcAvIn3
#define sysset5_avSrcAvIn4	IAppApiSystemSettings5_avSrcAvIn4
#define sysset5_avSrcAvIn5	IAppApiSystemSettings5_avSrcAvIn5
#define sysset5_avSrcAvIn6	IAppApiSystemSettings5_avSrcAvIn6
#define sysset5_avSrcAvIn7	IAppApiSystemSettings5_avSrcAvIn7
#define sysset5_avSrcAvIn8	IAppApiSystemSettings5_avSrcAvIn8
#define sysset5_avSrcAvIn9	IAppApiSystemSettings5_avSrcAvIn9
#define sysset5_avSrcAvIn10	IAppApiSystemSettings5_avSrcAvIn10
#define sysset5_svcModeNone	IAppApiSystemSettings5_svcModeNone
#define sysset5_svcModeCSM	IAppApiSystemSettings5_svcModeCSM
#define sysset5_svcModeSAM	IAppApiSystemSettings5_svcModeSAM
#define sysset5_svcModeSDM	IAppApiSystemSettings5_svcModeSDM
#define sysset5_svcModeCompair	IAppApiSystemSettings5_svcModeCompair
#define sysset5_svcModeFac	IAppApiSystemSettings5_svcModeFac
#define sysset5_svcModeDigSDM	IAppApiSystemSettings5_svcModeDigSDM
#define sysset5_svcModeBDS	IAppApiSystemSettings5_svcModeBDS
#define sysset5_svcModeRDM	IAppApiSystemSettings5_svcModeRDM
#define sysset5_svcModeBDSSys7	IAppApiSystemSettings5_svcModeBDSSys7
#define sysset5_svcModeFacExit	IAppApiSystemSettings5_svcModeFacExit
#define sysset5_BdsPowStateOn	IAppApiSystemSettings5_BdsPowStateOn
#define sysset5_BdsPowStateStandby	IAppApiSystemSettings5_BdsPowStateStandby
#define sysset5_AudioFormatStandard	IAppApiSystemSettings5_AudioFormatStandard
#define sysset5_AudioFormatAdvanced	IAppApiSystemSettings5_AudioFormatAdvanced
#define sysset5_OsdSizeInvalid	IAppApiSystemSettings5_OsdSizeInvalid
#define sysset5_OsdSizeSmall	IAppApiSystemSettings5_OsdSizeSmall
#define sysset5_OsdSizeLarge	IAppApiSystemSettings5_OsdSizeLarge
#define sysset5_SpainBaleares	IAppApiSystemSettings5_SpainBaleares
#define sysset5_SpainCanaryIsland	IAppApiSystemSettings5_SpainCanaryIsland
#define sysset5_TimeZoneContinental	IAppApiSystemSettings5_TimeZoneContinental
#define sysset5_TimeZoneAzores	IAppApiSystemSettings5_TimeZoneAzores
#define sysset5_TimeZoneKalingrad	IAppApiSystemSettings5_TimeZoneKalingrad
#define sysset5_TimeZoneMoscow	IAppApiSystemSettings5_TimeZoneMoscow
#define sysset5_TimeZoneSamara	IAppApiSystemSettings5_TimeZoneSamara
#define sysset5_TimeZoneYekaterinburg	IAppApiSystemSettings5_TimeZoneYekaterinburg
#define sysset5_TimeZoneOmsk	IAppApiSystemSettings5_TimeZoneOmsk
#define sysset5_TimeZoneKrasnoyarsk	IAppApiSystemSettings5_TimeZoneKrasnoyarsk
#define sysset5_TimeZoneIrkutsk	IAppApiSystemSettings5_TimeZoneIrkutsk
#define sysset5_TimeZoneYakutsk	IAppApiSystemSettings5_TimeZoneYakutsk
#define sysset5_TimeZoneVladivostok	IAppApiSystemSettings5_TimeZoneVladivostok
#define sysset5_TimeZoneMagadan	IAppApiSystemSettings5_TimeZoneMagadan
#define sysset5_TimeZoneKamchatka	IAppApiSystemSettings5_TimeZoneKamchatka
#define sysset5_TimeZoneLatamMinus2	IAppApiSystemSettings5_TimeZoneLatamMinus2
#define sysset5_TimeZoneLatamMinus1	IAppApiSystemSettings5_TimeZoneLatamMinus1
#define sysset5_TimeZoneLatamZero	IAppApiSystemSettings5_TimeZoneLatamZero
#define sysset5_TimeZoneLatamPlus1	IAppApiSystemSettings5_TimeZoneLatamPlus1
#define sysset5_TimeZoneLatamPlus2	IAppApiSystemSettings5_TimeZoneLatamPlus2
#define sysset5_NewSouthWales	IAppApiSystemSettings5_NewSouthWales
#define sysset5_Victoria	IAppApiSystemSettings5_Victoria
#define sysset5_Queensland	IAppApiSystemSettings5_Queensland
#define sysset5_SouthAustralia	IAppApiSystemSettings5_SouthAustralia
#define sysset5_WestAustralia	IAppApiSystemSettings5_WestAustralia
#define sysset5_Tasmania	IAppApiSystemSettings5_Tasmania
#define sysset5_NorthernTerritory	IAppApiSystemSettings5_NorthernTerritory
#define sysset5_ManualClkMode	IAppApiSystemSettings5_ManualClkMode
#define sysset5_AutoClkMode	IAppApiSystemSettings5_AutoClkMode
#define sysset5_CountryDepClkMode	IAppApiSystemSettings5_CountryDepClkMode
#define sysset5_DstOff	IAppApiSystemSettings5_DstOff
#define sysset5_DstOn	IAppApiSystemSettings5_DstOn
#define sysset5_CalStateNotStarted	IAppApiSystemSettings5_CalStateNotStarted
#define sysset5_CalStateInProgress	IAppApiSystemSettings5_CalStateInProgress
#define sysset5_CalStateSuccessfull	IAppApiSystemSettings5_CalStateSuccessfull
#define sysset5_CalStateFailed	IAppApiSystemSettings5_CalStateFailed
#define sysset5_CalStateForced	IAppApiSystemSettings5_CalStateForced
#define sysset5_AutoPowerDownModeOff	IAppApiSystemSettings5_AutoPowerDownModeOff
#define sysset5_AutoPowerDownModeOn	IAppApiSystemSettings5_AutoPowerDownModeOn
#define sysset5_ChannelListAll	IAppApiSystemSettings5_ChannelListAll
#define sysset5_ChannelListTV	IAppApiSystemSettings5_ChannelListTV
#define sysset5_ChannelListRadio	IAppApiSystemSettings5_ChannelListRadio
#define sysset5_ChannelListFavorite	IAppApiSystemSettings5_ChannelListFavorite
#define sysset5_ChannelListAnalog	IAppApiSystemSettings5_ChannelListAnalog
#define sysset5_MediumNone	IAppApiSystemSettings5_MediumNone
#define sysset5_MediumTerrestrial	IAppApiSystemSettings5_MediumTerrestrial
#define sysset5_MediumCable	IAppApiSystemSettings5_MediumCable
#define sysset5_SubtitleNone	IAppApiSystemSettings5_SubtitleNone
#define sysset5_SubtitleOff	IAppApiSystemSettings5_SubtitleOff
#define sysset5_SubtitleOn	IAppApiSystemSettings5_SubtitleOn
#define sysset5_SubtitleOnDuringMute	IAppApiSystemSettings5_SubtitleOnDuringMute
#define sysset5_InvalidPinCode	IAppApiSystemSettings5_InvalidPinCode
#define sysset5_InvalidLastViewed	IAppApiSystemSettings5_InvalidLastViewed
#define sysset5_LastViewedBroadcast	IAppApiSystemSettings5_LastViewedBroadcast
#define sysset5_LastViewedNetwork	IAppApiSystemSettings5_LastViewedNetwork
#define syssetx_AudioFormatStandard	IHsvTcSystemSettingsEx_AudioFormatStandard
#define syssetx_AudioFormatAdvanced	IHsvTcSystemSettingsEx_AudioFormatAdvanced
#define tprtk_TaskPrioHighest	i__tprtk.m_TaskPrioHighest
#define tprtk_TaskPrioHigh	i__tprtk.m_TaskPrioHigh
#define tprtk_TaskPrioAboveNormal	i__tprtk.m_TaskPrioAboveNormal
#define tprtk_TaskPrioNormal	i__tprtk.m_TaskPrioNormal
#define tprtk_TaskPrioBelowNormal	i__tprtk.m_TaskPrioBelowNormal
#define tprtk_TaskPrioLow	i__tprtk.m_TaskPrioLow
#define tprtk_TaskPrioLowest	i__tprtk.m_TaskPrioLowest
#define tprtk_SemSignaled	i__tprtk.m_SemSignaled
#define tprtk_SemUnsignaled	i__tprtk.m_SemUnsignaled
#define tprtk_TimeoutInfinite	i__tprtk.m_TimeoutInfinite
#define tprtk_TimeoutZero	i__tprtk.m_TimeoutZero
#define vctl_Freeze	i__vctl.m_Freeze
#define vctl_Pan	i__vctl.m_Pan
#define vctl_ViewMode	i__vctl.m_ViewMode
#define vctl_SeamlessViewMode	i__vctl.m_SeamlessViewMode
#define vctl_PicturePos	i__vctl.m_PicturePos
#define vctl_PicturePosHoriz	i__vctl.m_PicturePosHoriz
#define vctl_VideoCoding	i__vctl.m_VideoCoding
#define vctl_VideoCodingAux	i__vctl.m_VideoCodingAux
#define vctl_ImageFormat	i__vctl.m_ImageFormat
#define vctl_AutoFormat	i__vctl.m_AutoFormat
#define vctl_VideoMute	ISvcVideoControl3_VideoMute
#define vctl_VideoMuteAux	i__vctl.m_VideoMuteAux
#define vctl_VideoMuteScart2Out	i__vctl.m_VideoMuteScart2Out
#define vctl_VideoPresenceMain	i__vctl.m_VideoPresenceMain
#define vctl_VideoPresenceAux	i__vctl.m_VideoPresenceAux
#define vctl_IncomingFrameLinesMain	i__vctl.m_IncomingFrameLinesMain
#define vctl_IncomingVisibleFieldLinesMain	i__vctl.m_IncomingVisibleFieldLinesMain
#define vctl_IncomingSignalInterlaceMain	i__vctl.m_IncomingSignalInterlaceMain
#define vctl_IncomingFieldFrequencyMain	i__vctl.m_IncomingFieldFrequencyMain
#define vctl_IncomingVisiblePixels	i__vctl.m_IncomingVisiblePixels
#define vctl_IncomingVisiblePixelsAux	i__vctl.m_IncomingVisiblePixelsAux
#define vctl_IncomingFrameLinesAux	i__vctl.m_IncomingFrameLinesAux
#define vctl_IncomingVisibleFieldLinesAux	i__vctl.m_IncomingVisibleFieldLinesAux
#define vctl_IncomingSignalInterlaceAux	i__vctl.m_IncomingSignalInterlaceAux
#define vctl_IncomingFieldFrequencyAux	i__vctl.m_IncomingFieldFrequencyAux
#define vctl_AutoVideoMute	i__vctl.m_AutoVideoMute
#define vctl_AbsPicPosVertical	i__vctl.m_AbsPicPosVertical
#define vctl_AbsPicPosHoriz	i__vctl.m_AbsPicPosHoriz
#define vctl_VideoProtection	i__vctl.m_VideoProtection
#define vctl_LastItem	i__vctl.m_LastItem
#define vctl_FreezeOn	i__vctl.m_FreezeOn
#define vctl_FreezeOff	i__vctl.m_FreezeOff
#define vctl_PanUp	i__vctl.m_PanUp
#define vctl_PanDown	i__vctl.m_PanDown
#define vctl_PanLeft	i__vctl.m_PanLeft
#define vctl_PanRight	i__vctl.m_PanRight
#define vctl_VmNormalScreen4by3	i__vctl.m_VmNormalScreen4by3
#define vctl_VmMovieExpand14by9	i__vctl.m_VmMovieExpand14by9
#define vctl_VmMovieExpand16by9	i__vctl.m_VmMovieExpand16by9
#define vctl_VmSubtitleZoom	i__vctl.m_VmSubtitleZoom
#define vctl_VmSuperZoomMode	i__vctl.m_VmSuperZoomMode
#define vctl_VmWideScreen	i__vctl.m_VmWideScreen
#define vctl_VmMovieExpand21by9	i__vctl.m_VmMovieExpand21by9
#define vctl_VmNormalScreen	i__vctl.m_VmNormalScreen
#define vctl_VmVerticalSqueeze	i__vctl.m_VmVerticalSqueeze
#define vctl_VmExpand4by3	i__vctl.m_VmExpand4by3
#define vctl_VmPanorama	i__vctl.m_VmPanorama
#define vctl_VmHalfWindow	i__vctl.m_VmHalfWindow
#define vctl_VmHalfWindowSqueezed	i__vctl.m_VmHalfWindowSqueezed
#define vctl_VmHorizontalSqueeze	i__vctl.m_VmHorizontalSqueeze
#define vctl_VmOtherViewMode	i__vctl.m_VmOtherViewMode
#define vctl_VmAmoranap	i__vctl.m_VmAmoranap
#define vctl_VmZoomMode	i__vctl.m_VmZoomMode
#define vctl_VmHorizontalExpand	i__vctl.m_VmHorizontalExpand
#define vctl_VmPseudoPipWindow	i__vctl.m_VmPseudoPipWindow
#define vctl_VmPreviewWindow	i__vctl.m_VmPreviewWindow
#define vctl_VmNativeMode	i__vctl.m_VmNativeMode
#define vctl_VmHighRes	i__vctl.m_VmHighRes
#define vctl_VmUltraWide	i__vctl.m_VmUltraWide
#define vctl_VmUltraWideSubtitle	i__vctl.m_VmUltraWideSubtitle
#define vctl_VmUltraWide16by9	i__vctl.m_VmUltraWide16by9
#define vctl_VmVideoWindow	i__vctl.m_VmVideoWindow
#define vctl_VmUltraWideSuperZoomME16by9	i__vctl.m_VmUltraWideSuperZoomME16by9
#define vctl_VmAutofill	i__vctl.m_VmAutofill
#define vctl_VmAutozoom	i__vctl.m_VmAutozoom
#define vctl_AutoFormatMode	i__vctl.m_AutoFormatMode
#define vctl_PicturePosMin	i__vctl.m_PicturePosMin
#define vctl_PicturePosMax	i__vctl.m_PicturePosMax
#define vctl_PicturePosHorizMin	i__vctl.m_PicturePosHorizMin
#define vctl_PicturePosHorizMax	i__vctl.m_PicturePosHorizMax
#define vctl_VcCvbs	i__vctl.m_VcCvbs
#define vctl_VcYc	i__vctl.m_VcYc
#define vctl_VcYuv	i__vctl.m_VcYuv
#define vctl_VcRgb	i__vctl.m_VcRgb
#define vctl_VcYPbPr	i__vctl.m_VcYPbPr
#define vctl_VcYcOrCvbs	i__vctl.m_VcYcOrCvbs
#define vctl_VcRgb2Fh	i__vctl.m_VcRgb2Fh
#define vctl_VcYPbPr2Fh	i__vctl.m_VcYPbPr2Fh
#define vctl_VcYuv2Fh	i__vctl.m_VcYuv2Fh
#define vctl_VcRgb3Fh	i__vctl.m_VcRgb3Fh
#define vctl_VcYPbPr3Fh	i__vctl.m_VcYPbPr3Fh
#define vctl_VcYuv3Fh	i__vctl.m_VcYuv3Fh
#define vctl_VcVga	ISvcVideoControl3_VcVga
#define vctl_VcXvga	ISvcVideoControl3_VcXvga
#define vctl_VcSvga	ISvcVideoControl3_VcSvga
#define vctl_VcWxvga	ISvcVideoControl3_VcWxvga
#define vctl_ImageFormatInvalid	i__vctl.m_ImageFormatInvalid
#define vctl_ImageFormatUnknown	i__vctl.m_ImageFormatUnknown
#define vctl_ImageFormatNoImage	i__vctl.m_ImageFormatNoImage
#define vctl_ImageFormat4by3FF	i__vctl.m_ImageFormat4by3FF
#define vctl_ImageFormat14by9Top	i__vctl.m_ImageFormat14by9Top
#define vctl_ImageFormat14by9Center	i__vctl.m_ImageFormat14by9Center
#define vctl_ImageFormat16by9Top	i__vctl.m_ImageFormat16by9Top
#define vctl_ImageFormat16by9Center	i__vctl.m_ImageFormat16by9Center
#define vctl_ImageFormat4by3Use14by9	i__vctl.m_ImageFormat4by3Use14by9
#define vctl_ImageFormat16by9FF	i__vctl.m_ImageFormat16by9FF
#define vctl_ImageFormatMoreThan16by9Center	i__vctl.m_ImageFormatMoreThan16by9Center
#define vctl_ImageFormat16by9Use14by9	i__vctl.m_ImageFormat16by9Use14by9
#define vctl_ImageFormat16by9Use4by3	i__vctl.m_ImageFormat16by9Use4by3
#define vctl_VideoPresentInvalid	i__vctl.m_VideoPresentInvalid
#define vctl_VideoPresentUnknown	i__vctl.m_VideoPresentUnknown
#define vctl_VideoPresent	i__vctl.m_VideoPresent
#define vctl_VideoLost	i__vctl.m_VideoLost
#define vctl_VideoMuteBlack	i__vctl.m_VideoMuteBlack
#define vctl_VideoMuteBlue	i__vctl.m_VideoMuteBlue
#define vctl_VideoMuteGrey	i__vctl.m_VideoMuteGrey
#define vctl_VideoMuteWhite	i__vctl.m_VideoMuteWhite
#define vctl_VideoMutePogramBlack	ISvcVideoControl3_VideoMutePogramBlack
#define vctl_VideoMutePogramGrey	i__vctl.m_VideoMutePogramGrey
#define vctl_VideoMuteColourMin	i__vctl.m_VideoMuteColourMin
#define vctl_VideoMuteColourMax	i__vctl.m_VideoMuteColourMax
#define vctl_SigInterlace	i__vctl.m_SigInterlace
#define vctl_SigProgressive	i__vctl.m_SigProgressive
#define vctl_SigInterlaceInvalid	i__vctl.m_SigInterlaceInvalid
#define vctl_SigInterlaceUnknown	i__vctl.m_SigInterlaceUnknown
#define vctl_SigInterlaceOneOne	i__vctl.m_SigInterlaceOneOne
#define vctl_SigInterlaceTwoOne	i__vctl.m_SigInterlaceTwoOne
#define vctl_SigInterlaceFourTwo	i__vctl.m_SigInterlaceFourTwo
#define vctl_AbsPicPosVerticalMin	i__vctl.m_AbsPicPosVerticalMin
#define vctl_AbsPicPosVerticalMax	i__vctl.m_AbsPicPosVerticalMax
#define vctl_AbsPicPosHorizMin	i__vctl.m_AbsPicPosHorizMin
#define vctl_AbsPicPosHorizMax	i__vctl.m_AbsPicPosHorizMax
#define vctl_UnKnown	i__vctl.m_UnKnown
#define vctl_IgnoreValue	i__vctl.m_IgnoreValue
#define vctl_ResetValue	i__vctl.m_ResetValue
#define vctl_VideoPropertyMaxValue	ISvcVideoControl3_VideoPropertyMaxValue
#define vip_VideoPresenceInvalid	i__vip.m_VideoPresenceInvalid
#define vip_VideoPresenceUnknown	i__vip.m_VideoPresenceUnknown
#define vip_VideoPresenceDetected	i__vip.m_VideoPresenceDetected
#define vip_VideoPresenceNotDetected	i__vip.m_VideoPresenceNotDetected
#define vip_FieldFrequencyInvalid	i__vip.m_FieldFrequencyInvalid
#define vip_FieldFrequencyUnknown	i__vip.m_FieldFrequencyUnknown
#define vip_NumberOfLinesInvalid	i__vip.m_NumberOfLinesInvalid
#define vip_NumberOfLinesUnknown	i__vip.m_NumberOfLinesUnknown
#define vip_InterlaceInvalid	i__vip.m_InterlaceInvalid
#define vip_InterlaceUnknown	i__vip.m_InterlaceUnknown
#define vip_InterlaceOneOne	i__vip.m_InterlaceOneOne
#define vip_InterlaceTwoOne	i__vip.m_InterlaceTwoOne
#define vip_InterlaceFourTwo	i__vip.m_InterlaceFourTwo
#define vip_ImageFormatInvalid	i__vip.m_ImageFormatInvalid
#define vip_ImageFormatUnknown	i__vip.m_ImageFormatUnknown
#define vip_ImageFormat4by3FullFormat	i__vip.m_ImageFormat4by3FullFormat
#define vip_ImageFormat14by9Top	i__vip.m_ImageFormat14by9Top
#define vip_ImageFormat14by9Center	i__vip.m_ImageFormat14by9Center
#define vip_ImageFormat16by9Top	i__vip.m_ImageFormat16by9Top
#define vip_ImageFormat16by9Center	i__vip.m_ImageFormat16by9Center
#define vip_ImageFormat4by3Use14by9	i__vip.m_ImageFormat4by3Use14by9
#define vip_ImageFormat16by9Use14by9	i__vip.m_ImageFormat16by9Use14by9
#define vip_ImageFormat16by9Use4by3	i__vip.m_ImageFormat16by9Use4by3
#define vip_ImageFormat16by9FullFormat	i__vip.m_ImageFormat16by9FullFormat
#define vip_ImageFormatMoreThan16by9Center	i__vip.m_ImageFormatMoreThan16by9Center
#define vip_VideoCodingInvalid	i__vip.m_VideoCodingInvalid
#define vip_VideoCodingUnknown	i__vip.m_VideoCodingUnknown
#define vip_VideoCodingCvbs	i__vip.m_VideoCodingCvbs
#define vip_VideoCodingYc	i__vip.m_VideoCodingYc
#define vip_VideoCodingYuv	i__vip.m_VideoCodingYuv
#define vip_VideoCodingYuv2FH	i__vip.m_VideoCodingYuv2FH
#define vip_VideoCodingYuv3FH	i__vip.m_VideoCodingYuv3FH
#define vip_VideoCodingRgb	i__vip.m_VideoCodingRgb
#define vip_VideoCodingRgb2FH	i__vip.m_VideoCodingRgb2FH
#define vip_VideoCodingRgb3FH	i__vip.m_VideoCodingRgb3FH
#define vip_VideoCodingYPbPr	i__vip.m_VideoCodingYPbPr
#define vip_VideoCodingYPbPr2FH	i__vip.m_VideoCodingYPbPr2FH
#define vip_VideoCodingYPbPr3FH	i__vip.m_VideoCodingYPbPr3FH
#define wnddestmap_InvalidWindowId	i__wnddestmap.m_InvalidWindowId
#define wnddestmap_WndTypeInvalid	IHsvWindowDestinationMap_WndTypeInvalid
#define wnddestmap_WndTypeMainVideo	IHsvWindowDestinationMap_WndTypeMainVideo
#define wnddestmap_WndTypeMainAudio	IHsvWindowDestinationMap_WndTypeMainAudio
#define wnddestmap_WndTypeMonitor	IHsvWindowDestinationMap_WndTypeMonitor
#define wnddestmap_WndTypeAuxVideo	IHsvWindowDestinationMap_WndTypeAuxVideo
#define	plfav_VideoPresenceInvalid	IPlfApiAV_VideoPresenceInvalid
#define	plfav_VideoPresenceUnknown	IPlfApiAV_VideoPresenceUnknown
#define	plfav_VideoPresenceDetected	IPlfApiAV_VideoPresenceDetected
#define	plfav_VideoPresenceNotDetected	IPlfApiAV_VideoPresenceNotDetected
#define	plfav_GetVideoPresent		plfav->GetVideoPresent
#define	plfav_NoADRouting				IPlfApiAV_NoADRouting
#define	plfav_MainSpeakers		IPlfApiAV_MainSpeakers
#define	plfav_HeadPhones		IPlfApiAV_HeadPhones
#define	plfav_MonitorOut		IPlfApiAV_MonitorOut
#define	plfav_SpdifOut		IPlfApiAV_SpdifOut
#define	plfav_NoADSubStream	IPlfApiAV_NoADSubStream
#define	plfav_ADSubStream1	IPlfApiAV_ADSubStream1
#define	plfav_ADSubStream2	IPlfApiAV_ADSubStream2
#define	plfav_ADSubStream3	IPlfApiAV_ADSubStream3	
#define	plfav_setSeamlessMixing		plfav->setSeamlessMixing
#define	plfav_getSeamlessMixing		plfav->getSeamlessMixing
#define	plfav_setRouting				plfav->setRouting
#define	plfav_getRouting				plfav->getRouting
#define	plfav_setVolume				plfav->setVolume
#define	plfav_getVolume				plfav->getVolume
#define	plfav_getVolumeRange			plfav->getVolumeRange
#define	plfav_setAudioMute			plfav->setAudioMute
#define	plfav_getAudioMute			plfav->getAudioMute
#define	plfav_setAudioMuteLock		plfav->setAudioMuteLock
#define	plfav_getAudioMuteLockStatus		plfav->getAudioMuteLockStatus
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mdummy.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

