#ifndef  _CS2INSTALLERSTUB_H
#define  _CS2INSTALLERSTUB_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IProdApiClockEx.h>
#include <ISvcAudioControl4ExEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <IHsvComponentIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvLanguageIds2.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IMemoryOperations.h>
#include <IHsvDvbMplDiv.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvProgramSelection2.h>
#include <IPlfApiTsDmxAbstractEx.h>
#include <IPlfApiDvbsTuning.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPlfApiTuning.h>
#include <IPumpExSub.h>
#include <IHsvMemoryPool.h>
#include <IHsvSdmPoolIds.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiStorageDevice.h>
#include <IRealTimeKernel.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IString.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvSatSystemSettings.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <IPlfApiPhysDevice.h>
#include <IHsvUtilDiv.h>
#include <ISvcVideoControl3.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvSystemSettings.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatGlobalSettings.h>

class CS2InstallerStub_Priv;
class CS2InstallerStub
{
public:
ProvidesInterface<IProdApiClockEx>	Timerclk;

ProvidesInterface<ISvcAudioControl4ExEx>	actl3;

ProvidesInterface<IAppApiChannelLibReturnCodes>	apperr;

ProvidesInterface<IAppApiSystemSettings5>	apsysset;

ProvidesInterface<IHsvCountryIds>	cids;

ProvidesInterface<IHsvComponentIds>	compids;

ProvidesInterface<IPumpEngine>	ctrlpen;

ProvidesInterface<IHsvSdmDiv>	div;

ProvidesInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;

ProvidesInterface<IHsvErrorCodeEx>	err;

ProvidesInterface<IHsvEuropeDiversity2>	eurdiv;

ProvidesInterface<IHsvLanguageIds2>	lngids;

ProvidesInterface<IHsvLog>	log;

ProvidesInterface<IHsvMediaControl>	mctl;

ProvidesInterface<IMemoryOperations>	memo;

ProvidesInterface<IHsvDvbMplDiv>	mpldiv;

ProvidesInterface<IProdApiSystemStateObserverExExExEx>	observer;

ProvidesInterface<IPumpEngine>	pen;

ProvidesInterface<IHsvChannelLibReturnCodes>	pgdaterr;

ProvidesInterface<IHsvChanlibPosixLight>	pgdatrtk;

ProvidesInterface<IHsvProgramSelection2>	pgsel;

ProvidesInterface<IPlfApiTsDmxAbstractEx>	plfdmx;

ProvidesInterface<IPlfApiDvbsTuning>	plfdvbs;

ProvidesInterface<IPlfApiErrorIds>	plferrids;

ProvidesInterface<ITvPlatformResource>	plfres;

ProvidesInterface<IPlfApiTuning>	plftune;

ProvidesInterface<IPumpExSub>	pmp;

ProvidesInterface<IHsvMemoryPool>	pool;

ProvidesInterface<IHsvSdmPoolIds>	poolids;

ProvidesInterface<IPlfApiSigStrengthMeas>	qssm;

ProvidesInterface<IPlfApiStorageDevice>	recdev;

ProvidesInterface<IRealTimeKernel>	rtk;

ProvidesInterface<IHsvSatelliteDiversity>	s2div;

ProvidesInterface<IHsvSortedTable2>	srtdb2;

ProvidesInterface<IHsvSdmSortedTableIds>	srtdbids;

ProvidesInterface<IString>	str;

ProvidesInterface<IHsvChannelLibSyncEvents>	sync;

ProvidesInterface<IHsvSatSystemSettings>	sysset;

ProvidesInterface<ICeIsTpHostRtk2>	tprtk;

ProvidesInterface<IPlfApiPhysDevice>	usbms;

ProvidesInterface<IHsvUtilDiv>	utildiv;

ProvidesInterface<ISvcVideoControl3>	vctl;

ProvidesInterface<IPlfApiSigStrengthMeas>	vssm;

ProvidesInterface<IHsvWindowDestinationMap>	wnddest;

public:
RequiresInterface<IHsvSystemSettings>	tvcoresettings;

RequiresInterface<IHsvSatelliteSettings>	dvbset;

RequiresInterface<IHsvSatGlobalSettings>	globalsettings;

RequiresInterface<IPlfApiTsDmxAbstractEx> plfApiTsDmx;

public:
CS2InstallerStub();
virtual ~CS2InstallerStub();
private:
CS2InstallerStub_Priv	*m_priv;
};

#endif

