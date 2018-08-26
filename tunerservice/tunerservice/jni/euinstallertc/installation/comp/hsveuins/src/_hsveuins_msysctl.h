#ifndef HSVEUINS_MSYSCTL
#define HSVEUINS_MSYSCTL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_msysctl.h"
#include "CHsvEuropeInstallation_msysctl_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_msysctl_Priv::params__init(void)
{
}
CHsvEuropeInstallation_msysctl_Priv::~CHsvEuropeInstallation_msysctl_Priv()
{
}
//public class connections
CHsvEuropeInstallation_msysctl::CHsvEuropeInstallation_msysctl()
{
 m_priv = new CHsvEuropeInstallation_msysctl_Priv();
instutil	= m_priv->instutil;
sysctl	= m_priv->sysctl;
m_priv->actl	=actl;
m_priv->destconfig	=destconfig;
m_priv->div	=div;
m_priv->log	=log;
m_priv->vctl	=vctl;
}
CHsvEuropeInstallation_msysctl::~CHsvEuropeInstallation_msysctl()
{
 delete m_priv;
}
#endif
