#ifndef  _CHSVEUROPEINSTALLATION_MPEGSORT_H
#define  _CHSVEUROPEINSTALLATION_MPEGSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvPower.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvAdvanceProgramIterator.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvCookieNvmInfo.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvSortNotify.h>
#include <IHsvAnalogInstallation.h>
class CHsvEuropeInstallation_mpegsort_Priv;
class CHsvEuropeInstallation_mpegsort
{
public:
ProvidesInterface<IHsvHybridPresetSort>	idvbtlitesort;

ProvidesInterface<IHsvPower>	impegpow;

//Required interfaces
public:
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvAdvanceProgramIterator>	iadvpgitr;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvSortNotify>	sortN;
RequiresInterface<IHsvAnalogInstallation>	hsvprins_prins;
public:
CHsvEuropeInstallation_mpegsort();
virtual ~CHsvEuropeInstallation_mpegsort();
private:
CHsvEuropeInstallation_mpegsort_Priv	*m_priv;
};

#endif

