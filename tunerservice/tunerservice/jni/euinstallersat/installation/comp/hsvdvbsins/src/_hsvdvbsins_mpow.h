#ifndef HSVDVBSINS_MPOW
#define HSVDVBSINS_MPOW

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mpow.h"
#include "CHsvDvbsInstallation_mpow_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mpow_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mpow_Priv::~CHsvDvbsInstallation_mpow_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mpow::CHsvDvbsInstallation_mpow()
{
 m_priv = new CHsvDvbsInstallation_mpow_Priv();
pow	= m_priv->pow;
m_priv->idvbsetpow	=idvbsetpow;
m_priv->iminiprescanpow	=iminiprescanpow;
m_priv->impackagepow	=impackagepow;
m_priv->ipackagepow	=ipackagepow;
m_priv->ipow	=ipow;
m_priv->ipredefpow	=ipredefpow;
m_priv->iprescanpow	=iprescanpow;
m_priv->iremovesatpow	=iremovesatpow;
m_priv->isatipprescanpow	=isatipprescanpow;
}
CHsvDvbsInstallation_mpow::~CHsvDvbsInstallation_mpow()
{
 delete m_priv;
}
#endif
