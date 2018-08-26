#ifndef  _CHSVEUROPEINSTALLATION_MSIGSTR_H
#define  _CHSVEUROPEINSTALLATION_MSIGSTR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvInstallation2.h>
#include <IHsvWindowDestinationMap.h>
class CHsvEuropeInstallation_msigstr_Priv;
class CHsvEuropeInstallation_msigstr
{
public:
ProvidesInterface<IHsvInstallationSigStrength>	sigstr;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvEuropeInstallation_msigstr();
virtual ~CHsvEuropeInstallation_msigstr();
private:
CHsvEuropeInstallation_msigstr_Priv	*m_priv;
};

#endif

