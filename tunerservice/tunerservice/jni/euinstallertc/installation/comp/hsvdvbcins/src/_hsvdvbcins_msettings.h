#ifndef HSVDVBCINS_MSETTINGS
#define HSVDVBCINS_MSETTINGS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_msettings.h"
#include "CHsvDvbCInstallation_msettings_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_msettings_Priv::params__init(void)
{
}
CHsvDvbCInstallation_msettings_Priv::~CHsvDvbCInstallation_msettings_Priv()
{
}
//public class connections
CHsvDvbCInstallation_msettings::CHsvDvbCInstallation_msettings()
{
 m_priv = new CHsvDvbCInstallation_msettings_Priv();
idvbset	= m_priv->idvbset;
isetpow	= m_priv->isetpow;
syssetN	= m_priv->syssetN;
m_priv->apsysset	=apsysset;
m_priv->cids	=cids;
m_priv->cityids	=cityids;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->insN	=insN;
m_priv->pen	=pen;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sortroute	=sortroute;
m_priv->str	=str;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvDvbCInstallation_msettings::~CHsvDvbCInstallation_msettings()
{
 delete m_priv;
}
#endif
