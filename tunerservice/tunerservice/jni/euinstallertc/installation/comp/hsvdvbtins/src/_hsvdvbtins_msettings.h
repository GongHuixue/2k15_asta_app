#ifndef HSVDVBTINS_MSETTINGS
#define HSVDVBTINS_MSETTINGS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_msettings.h"
#include "CHsvDvbTInstallation_msettings_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_msettings_Priv::params__init(void)
{
}
CHsvDvbTInstallation_msettings_Priv::~CHsvDvbTInstallation_msettings_Priv()
{
}
//public class connections
CHsvDvbTInstallation_msettings::CHsvDvbTInstallation_msettings()
{
 m_priv = new CHsvDvbTInstallation_msettings_Priv();
idvbset	= m_priv->idvbset;
isetpow	= m_priv->isetpow;
syssetN	= m_priv->syssetN;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->plferrids	=plferrids;
m_priv->rins	=rins;
m_priv->sortroute	=sortroute;
m_priv->str	=str;
m_priv->wnddest	=wnddest;
}
CHsvDvbTInstallation_msettings::~CHsvDvbTInstallation_msettings()
{
 delete m_priv;
}
#endif
