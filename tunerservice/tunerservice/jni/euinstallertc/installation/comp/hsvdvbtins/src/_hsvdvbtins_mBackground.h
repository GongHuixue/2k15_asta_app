#ifndef HSVDVBTINS_MBACKGROUND
#define HSVDVBTINS_MBACKGROUND

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mBackground.h"
#include "CHsvDvbTInstallation_mBackground_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mBackground_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mBackground_Priv::~CHsvDvbTInstallation_mBackground_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mBackground::CHsvDvbTInstallation_mBackground()
{
 m_priv = new CHsvDvbTInstallation_mBackground_Priv();
ena	= m_priv->ena;
ibctrlN	= m_priv->ibctrlN;
ibpow	= m_priv->ibpow;
ibstrapiN	= m_priv->ibstrapiN;
syssetN	= m_priv->isyssetN;
m_priv->eurdiv	=eurdiv;
m_priv->idataacq	=idataacq;
m_priv->pen	=pen;
m_priv->plfres	=plfres;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->pgsel = pgsel;
m_priv->pgdb = pgdb;
m_priv->pgdbconst = pgdbconst;
m_priv->strapi = strapi;
m_priv->installN	=installN;
m_priv->cids	=cids;
m_priv->sysset=sysset;
m_priv->sort=sort;
m_priv->instutil = instutil;
m_priv->pgdat = pgdat;
}
CHsvDvbTInstallation_mBackground::~CHsvDvbTInstallation_mBackground()
{
 delete m_priv;
}
#endif
