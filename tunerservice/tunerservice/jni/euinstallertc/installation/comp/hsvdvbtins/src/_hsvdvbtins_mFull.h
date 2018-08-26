#ifndef HSVDVBTINS_MFULL
#define HSVDVBTINS_MFULL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mFull.h"
#include "CHsvDvbTInstallation_mFull_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mFull_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mFull_Priv::~CHsvDvbTInstallation_mFull_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mFull::CHsvDvbTInstallation_mFull()
{
 m_priv = new CHsvDvbTInstallation_mFull_Priv();
ifctrlN	= m_priv->ifctrlN;
ifull	= m_priv->ifull;
ifullfeN	= m_priv->ifullfeN;
ifullpow	= m_priv->ifullpow;
m_priv->chdecdvbt2	=chdecdvbt2;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->digscanN	=digscanN;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->idvbtqctrlN	=idvbtqctrlN;
m_priv->insN	=insN;
m_priv->istub	=istub;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
m_priv->strapi	=strapi;
}
CHsvDvbTInstallation_mFull::~CHsvDvbTInstallation_mFull()
{
 delete m_priv;
}
#endif
