#ifndef  _CHSVEUROPEINSTALLATION_MSYSSET_H
#define  _CHSVEUROPEINSTALLATION_MSYSSET_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ICesCountryIds.h>
#include <IHsvLanguageIds2.h>
class CHsvEuropeInstallation_msysset_Priv;
class CHsvEuropeInstallation_msysset
{
public:
ProvidesInterface<ICesCountryIds>	icountid;

ProvidesInterface<IHsvLanguageIds2>	ilangid;

public:
CHsvEuropeInstallation_msysset();
virtual ~CHsvEuropeInstallation_msysset();
private:
CHsvEuropeInstallation_msysset_Priv	*m_priv;
};

#endif

