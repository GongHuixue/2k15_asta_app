#ifndef  _CHSVEUROPEINSTALLATION_MCAMSORT_H
#define  _CHSVEUROPEINSTALLATION_MCAMSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCamPresetSort.h>
#include <IHsvPower.h>
#include <IHsvCookieNvmInfo.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSortNotify.h>
class CHsvEuropeInstallation_mcamsort_Priv;
class CHsvEuropeInstallation_mcamsort
{
public:
ProvidesInterface<IHsvCamPresetSort>	icamsort;

ProvidesInterface<IHsvPower>	icamsortpow;

//Required interfaces
public:
RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSortNotify>	sortN;
public:
CHsvEuropeInstallation_mcamsort();
virtual ~CHsvEuropeInstallation_mcamsort();
private:
CHsvEuropeInstallation_mcamsort_Priv	*m_priv;
};

#endif

