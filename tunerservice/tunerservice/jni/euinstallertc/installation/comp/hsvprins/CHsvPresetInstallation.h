#ifndef  _CHSVPRESETINSTALLATION_H
#define  _CHSVPRESETINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvPresetInstallation_m.h>
#include <CHsvPresetInstallation_maci.h>
#include <CHsvPresetInstallation_msettings.h>
#include <IHsvAciData.h>
#include <IHsvAnalogSettings.h>
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
#include <IHsvLanguageIds2.h>
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

class CHsvPresetInstallation
{
public:
virtual ~CHsvPresetInstallation(){}

//Contained Modules
private:
CHsvPresetInstallation_m m;
CHsvPresetInstallation_maci maci;
CHsvPresetInstallation_msettings msettings;
public:
ProvidesInterface<IHsvAciData>	acidat;

ProvidesInterface<IHsvAnalogSettings>	anaset;

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
RequiresInterface<IHsvLanguageIds2>	lngids;
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
RequiresInterface<ITvColorDecode2>	xcol;
private:
Pumpdefines(CHsvPresetInstallation);

public:
CHsvPresetInstallation()
{
pow	=	m.pow;
prins	=	m.prins;
implins	=	m.implins;
resetN	=	m.resetN;
pgaciN	=	m.pgaciN;
pacidsN	=	m.pacidsN;
colN	=	m.colN;
feapiN	=	m.feapiN;
acidat	=	maci.acidat;
maci.pgdb	=	pgdb;
maci.pgdbconst	=	pgdbconst;
maci.cids	=	cids;
maci.col	=	col;
maci.sysset	=	sysset;
maci.sort	=	sort;
maci.memo	=	memo;
maci.div	=	div;
maci.feapi	=	feapi;
maci.instutil	=	instutil;
maci.lngids	=	lngids;
maci.rins	=	rins;
maci.eurdiv	=	eurdiv;
m.feapi	=	feapi;
m.prinsN	=	prinsN;
m.implinsN	=	implinsN;
m.pmp	=	pmp;
m.pen	=	pen;
m.div	=	div;
m.euconfig	=	euconfig;
m.pgdat	=	pgdat;
m.pgdb	=	pgdb;
m.pgdbconst	=	pgdbconst;
m.sysctl	=	sysctl;
m.vps	=	vps;
m.p830	=	p830;
m.chlname	=	chlname;
m.pgdatcni	=	pgdatcni;
m.txtpre	=	txtpre;
m.cniname	=	cniname;
m.str	=	str;
m.sysset	=	sysset;
m.cids	=	cids;
m.pgaci	=	pgaci;
m.prsort	=	prsort;
m.mem	=	mem;
m.memo	=	memo;
m.log	=	log;
m.rins	=	rins;
m.sort	=	sort;
m.col	=	col;
m.freqctl	=	freqctl;
m.instutil	=	instutil;
m.sigstr	=	sigstr;
m.wnddest	=	wnddest;
m.err	=	err;
m.eurdiv	=	eurdiv;
m.chanlibret	=	chanlibret;
msettings.wnddest	=	wnddest;
anaset	=	msettings.anaset;
msettings.feapi	=	feapi;
msettings.col	=	col;
msettings.xcol	=	xcol;
}

};

#endif

