#ifndef HSVDVBTINS_MDTR
#define HSVDVBTINS_MDTR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mDtr.h"
#include "CHsvDvbTInstallation_mDtr_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mDtr_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mDtr_Priv::~CHsvDvbTInstallation_mDtr_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mDtr::CHsvDvbTInstallation_mDtr()
{
 m_priv = new CHsvDvbTInstallation_mDtr_Priv();
idctrlN	= m_priv->idctrlN;
idtr	= m_priv->idtr;
idtrfeN	= m_priv->idtrfeN;
idtrpow	= m_priv->idtrpow;
idstrapiN	= m_priv->idstrapiN;
m_priv->chdecdvbt2	=chdecdvbt2;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->digscanN	=digscanN;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->idataacq	=idataacq;
m_priv->idvbtqctrlN	=idvbtqctrlN;
m_priv->insN	=insN;
m_priv->istub	=istub;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->strapi	=strapi;
m_priv->strmfltr	=strmfltr;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvDvbTInstallation_mDtr::~CHsvDvbTInstallation_mDtr()
{
 delete m_priv;
}
#endif
