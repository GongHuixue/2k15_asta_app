#ifndef HSVDVBCINS_MGRID
#define HSVDVBCINS_MGRID

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_mgrid.h"
#include "CHsvDvbCInstallation_mgrid_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_mgrid_Priv::params__init(void)
{
}
CHsvDvbCInstallation_mgrid_Priv::~CHsvDvbCInstallation_mgrid_Priv()
{
}
//public class connections
CHsvDvbCInstallation_mgrid::CHsvDvbCInstallation_mgrid()
{
 m_priv = new CHsvDvbCInstallation_mgrid_Priv();
igctrlN	= m_priv->igctrlN;
igena	= m_priv->igena;
igrid	= m_priv->igrid;
igridfeN	= m_priv->igridfeN;
igridpow	= m_priv->igridpow;
igstrapiN	= m_priv->igstrapiN;
m_priv->ctrl	=ctrl;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->hsverr	=hsverr;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->igridN	=igridN;
m_priv->insN	=insN;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->str	=str;
m_priv->strapi	=strapi;
m_priv->strmfltr	=strmfltr;
m_priv->wnddest	=wnddest;
}
CHsvDvbCInstallation_mgrid::~CHsvDvbCInstallation_mgrid()
{
 delete m_priv;
}
#endif
