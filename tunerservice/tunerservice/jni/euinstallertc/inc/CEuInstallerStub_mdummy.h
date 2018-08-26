#ifndef  _CEUINSTALLERSTUB_MDUMMY_H
#define  _CEUINSTALLERSTUB_MDUMMY_H 

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
#include <IHsvSystemSettings.h>
#include <IInfraTimerServer.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <ISvcVideoControl3.h>
#include <ITvVideoProperties3Ex.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvInstallation2.h>
#include <IHsvTcGlobalSettings.h>
#include <IPlfApiAV.h>
class CEuInstallerStub_mdummy_Priv;
class CEuInstallerStub_mdummy
{
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
CEuInstallerStub_mdummy();
virtual ~CEuInstallerStub_mdummy();
private:
CEuInstallerStub_mdummy_Priv	*m_priv;
};

#endif

