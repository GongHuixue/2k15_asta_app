#ifndef  _CHSVEUROPEINSTALLATION_MFREQCTL_H
#define  _CHSVEUROPEINSTALLATION_MFREQCTL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvPower.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
class CHsvEuropeInstallation_mfreqctl_Priv;
class CHsvEuropeInstallation_mfreqctl
{
public:
ProvidesInterface<IHsvInstallationFrequencyControl>	freqctl;

ProvidesInterface<IHsvPower>	imfreqctlpow;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvEuropeInstallation_mfreqctl();
virtual ~CHsvEuropeInstallation_mfreqctl();
private:
CHsvEuropeInstallation_mfreqctl_Priv	*m_priv;
};

#endif

