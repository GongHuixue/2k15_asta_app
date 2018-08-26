#ifndef  _CHSVPRESETINSTALLATION_M_H
#define  _CHSVPRESETINSTALLATION_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ITvColorDecode2NotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPresetImplicitInstall.h>
#include <IHsvAciDisplayNotify.h>
#include <IHsvAciInstallationSubNotify.h>
#include <IHsvPower.h>
#include <IHsvAnalogInstallation.h>
#include <IHsvTxtResetNotify.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvTsvChannelName.h>
#include <IHsvCountryIds.h>
#include <IHsvCniPresetName.h>
#include <ITvColorDecode2.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeConfiguration.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvPresetImplicitInstallNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvMemoryPool.h>
#include <IMemoryOperations.h>
#include <IHsvTxtPacket830Data.h>
#include <IPumpEngine.h>
#include <ISvcAciInstallation.h>
#include <IHsvProgramData3.h>
#include <ISvcCniData.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvAnalogInstallationNotify.h>
#include <IHsvPresetSort.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IString.h>
#include <IHsvInstallationSystemControl.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvTxtPresent.h>
#include <IHsvTxtVpsData.h>
#include <IHsvWindowDestinationMap.h>
class CHsvPresetInstallation_m_Priv;
class CHsvPresetInstallation_m
{
public:
ProvidesInterface<ITvColorDecode2NotifyEx>	colN;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvPresetImplicitInstall>	implins;

ProvidesInterface<IHsvAciDisplayNotify>	pacidsN;

ProvidesInterface<IHsvAciInstallationSubNotify>	pgaciN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvAnalogInstallation>	prins;

ProvidesInterface<IHsvTxtResetNotify>	resetN;

//Required interfaces
public:
RequiresInterface<IHsvChannelLibReturnCodes>	chanlibret;
RequiresInterface<IHsvTsvChannelName>	chlname;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvCniPresetName>	cniname;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeConfiguration>	euconfig;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvPresetImplicitInstallNotify>	implinsN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMemoryPool>	mem;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvTxtPacket830Data>	p830;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<ISvcAciInstallation>	pgaci;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<ISvcCniData>	pgdatcni;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvAnalogInstallationNotify>	prinsN;
RequiresInterface<IHsvPresetSort>	prsort;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IString>	str;
RequiresInterface<IHsvInstallationSystemControl>	sysctl;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvTxtPresent>	txtpre;
RequiresInterface<IHsvTxtVpsData>	vps;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvPresetInstallation_m();
virtual ~CHsvPresetInstallation_m();
private:
CHsvPresetInstallation_m_Priv	*m_priv;
};

#endif

