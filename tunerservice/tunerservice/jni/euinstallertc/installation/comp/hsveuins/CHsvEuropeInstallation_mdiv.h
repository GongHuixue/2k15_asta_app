#ifndef  _CHSVEUROPEINSTALLATION_MDIV_H
#define  _CHSVEUROPEINSTALLATION_MDIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciDecodeDiv.h>
#include <IHsvEuropeConfiguration.h>
#include <ICesPaciDiv.h>
#include <ICesPatsDiv.h>
#include <ICesCountryIds.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
class CHsvEuropeInstallation_mdiv_Priv;
class CHsvEuropeInstallation_mdiv
{
public:
ProvidesInterface<IHsvAciDecodeDiv>	hsvacidec_div;

ProvidesInterface<IHsvEuropeConfiguration>	ieuconfig;

ProvidesInterface<ICesPaciDiv>	svpaci_div;

ProvidesInterface<ICesPatsDiv>	svpats_div;

//Required interfaces
public:
RequiresInterface<ICesCountryIds>	icountid;
RequiresInterface<IHsvInstallation2>	pins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvEuropeInstallation_mdiv();
virtual ~CHsvEuropeInstallation_mdiv();
private:
CHsvEuropeInstallation_mdiv_Priv	*m_priv;
};

#endif

