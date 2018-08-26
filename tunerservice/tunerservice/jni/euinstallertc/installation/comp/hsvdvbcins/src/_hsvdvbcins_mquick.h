#ifndef HSVDVBCINS_MQUICK
#define HSVDVBCINS_MQUICK

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_mquick.h"
#include "CHsvDvbCInstallation_mquick_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_mquick_Priv::params__init(void)
{
}
CHsvDvbCInstallation_mquick_Priv::~CHsvDvbCInstallation_mquick_Priv()
{
}
//public class connections
CHsvDvbCInstallation_mquick::CHsvDvbCInstallation_mquick()
{
 m_priv = new CHsvDvbCInstallation_mquick_Priv();
iqctrlN	= m_priv->iqctrlN;
iqena	= m_priv->iqena;
iqstrapiN	= m_priv->iqstrapiN;
iquick	= m_priv->iquick;
iquickfeN	= m_priv->iquickfeN;
iquickpow	= m_priv->iquickpow;
m_priv->apsysset	=apsysset;
m_priv->ctrl	=ctrl;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->hsverr	=hsverr;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->insN	=insN;
m_priv->iquickN	=iquickN;
m_priv->mctl	=mctl;
m_priv->memo	=memo;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->str	=str;
m_priv->strapi	=strapi;
m_priv->strmfltr	=strmfltr;
m_priv->wnddest	=wnddest;
}
CHsvDvbCInstallation_mquick::~CHsvDvbCInstallation_mquick()
{
 delete m_priv;
}
#endif
