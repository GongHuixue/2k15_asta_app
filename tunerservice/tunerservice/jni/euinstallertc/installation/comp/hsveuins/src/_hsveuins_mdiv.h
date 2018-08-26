#ifndef HSVEUINS_MDIV
#define HSVEUINS_MDIV

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mdiv.h"
#include "CHsvEuropeInstallation_mdiv_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mdiv_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mdiv_Priv::~CHsvEuropeInstallation_mdiv_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mdiv::CHsvEuropeInstallation_mdiv()
{
 m_priv = new CHsvEuropeInstallation_mdiv_Priv();
hsvacidec_div	= m_priv->hsvacidec_div;
ieuconfig	= m_priv->ieuconfig;
svpaci_div	= m_priv->svpaci_div;
svpats_div	= m_priv->svpats_div;
m_priv->icountid	=icountid;
m_priv->pins	=pins;
m_priv->sysset	=sysset;
}
CHsvEuropeInstallation_mdiv::~CHsvEuropeInstallation_mdiv()
{
 delete m_priv;
}
#endif
