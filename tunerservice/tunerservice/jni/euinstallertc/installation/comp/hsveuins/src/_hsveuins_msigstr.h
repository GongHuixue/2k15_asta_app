#ifndef HSVEUINS_MSIGSTR
#define HSVEUINS_MSIGSTR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_msigstr.h"
#include "CHsvEuropeInstallation_msigstr_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_msigstr_Priv::params__init(void)
{
}
CHsvEuropeInstallation_msigstr_Priv::~CHsvEuropeInstallation_msigstr_Priv()
{
}
//public class connections
CHsvEuropeInstallation_msigstr::CHsvEuropeInstallation_msigstr()
{
 m_priv = new CHsvEuropeInstallation_msigstr_Priv();
sigstr	= m_priv->sigstr;
m_priv->err	=err;
m_priv->feapi	=feapi;
m_priv->instutil	=instutil;
m_priv->log	=log;
m_priv->rins	=rins;
m_priv->wnddest	=wnddest;
}
CHsvEuropeInstallation_msigstr::~CHsvEuropeInstallation_msigstr()
{
 delete m_priv;
}
#endif
