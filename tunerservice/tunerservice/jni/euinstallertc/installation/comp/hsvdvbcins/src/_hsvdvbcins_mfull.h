#ifndef HSVDVBCINS_MFULL
#define HSVDVBCINS_MFULL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_mfull.h"
#include "CHsvDvbCInstallation_mfull_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_mfull_Priv::params__init(void)
{
}
CHsvDvbCInstallation_mfull_Priv::~CHsvDvbCInstallation_mfull_Priv()
{
}
//public class connections
CHsvDvbCInstallation_mfull::CHsvDvbCInstallation_mfull()
{
 m_priv = new CHsvDvbCInstallation_mfull_Priv();
ifctrlN	= m_priv->ifctrlN;
ifena	= m_priv->ifena;
ifstrapiN	= m_priv->ifstrapiN;
ifull	= m_priv->ifull;
ifullfeN	= m_priv->ifullfeN;
ifullpow	= m_priv->ifullpow;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->hsverr	=hsverr;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->ifullN	=ifullN;
m_priv->insN	=insN;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst=pgdbconst;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->str	=str;
m_priv->strapi	=strapi;
m_priv->strmfltr	=strmfltr;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvDvbCInstallation_mfull::~CHsvDvbCInstallation_mfull()
{
 delete m_priv;
}
#endif
