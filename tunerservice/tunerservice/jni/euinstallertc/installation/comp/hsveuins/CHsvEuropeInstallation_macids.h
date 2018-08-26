#ifndef  _CHSVEUROPEINSTALLATION_MACIDS_H
#define  _CHSVEUROPEINSTALLATION_MACIDS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciNavigation.h>
#include <ISvcCniData.h>
#include <IHsvTxtDisplayDriver.h>
#include <ITxtDisplayDriver3.h>
#include <IHsvTextDisplay.h>
#include <IAppApiTextDisplayConstants.h>
class CHsvEuropeInstallation_macids_Priv;
class CHsvEuropeInstallation_macids
{
public:
ProvidesInterface<IHsvAciNavigation>	iacinv;

ProvidesInterface<ISvcCniData>	svpaci_pgcni;

//Required interfaces
public:
RequiresInterface<IHsvTxtDisplayDriver>	dsdrv;
RequiresInterface<ITxtDisplayDriver3>	dsdrv3;
RequiresInterface<IHsvTextDisplay>	gfxtxt;
RequiresInterface<IAppApiTextDisplayConstants>	txtdspcons;
public:
CHsvEuropeInstallation_macids();
virtual ~CHsvEuropeInstallation_macids();
private:
CHsvEuropeInstallation_macids_Priv	*m_priv;
};

#endif

