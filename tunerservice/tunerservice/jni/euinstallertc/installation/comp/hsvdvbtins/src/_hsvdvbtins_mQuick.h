#ifndef HSVDVBTINS_MQUICK
#define HSVDVBTINS_MQUICK

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mQuick.h"
#include "CHsvDvbTInstallation_mQuick_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mQuick_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mQuick_Priv::~CHsvDvbTInstallation_mQuick_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mQuick::CHsvDvbTInstallation_mQuick()
{
 m_priv = new CHsvDvbTInstallation_mQuick_Priv();
iqctrlN	= m_priv->iqctrlN;
iquick	= m_priv->iquick;
iquickfeN	= m_priv->iquickfeN;
iquickpow	= m_priv->iquickpow;
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
CHsvDvbTInstallation_mQuick::~CHsvDvbTInstallation_mQuick()
{
 delete m_priv;
}
#endif
