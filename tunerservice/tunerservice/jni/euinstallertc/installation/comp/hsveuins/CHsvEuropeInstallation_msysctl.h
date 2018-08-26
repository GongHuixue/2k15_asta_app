#ifndef  _CHSVEUROPEINSTALLATION_MSYSCTL_H
#define  _CHSVEUROPEINSTALLATION_MSYSCTL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationUtility.h>
#include <IHsvInstallationSystemControl.h>
#include <ISvcAudioControl4ExEx.h>
#include <IHsvDestinationConfiguration.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvLog.h>
#include <ISvcVideoControl3.h>
class CHsvEuropeInstallation_msysctl_Priv;
class CHsvEuropeInstallation_msysctl
{
public:
ProvidesInterface<IHsvInstallationUtility>	instutil;

ProvidesInterface<IHsvInstallationSystemControl>	sysctl;

//Required interfaces
public:
RequiresInterface<ISvcAudioControl4ExEx>	actl;
RequiresInterface<IHsvDestinationConfiguration>	destconfig;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvLog>	log;
RequiresInterface<ISvcVideoControl3>	vctl;
public:
CHsvEuropeInstallation_msysctl();
virtual ~CHsvEuropeInstallation_msysctl();
private:
CHsvEuropeInstallation_msysctl_Priv	*m_priv;
};

#endif

