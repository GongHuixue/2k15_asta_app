#ifndef HSVDVBSINS_MMINIPRESCAN
#define HSVDVBSINS_MMINIPRESCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mminiprescan.h"
#include "CHsvDvbsInstallation_mminiprescan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mminiprescan_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mminiprescan_Priv::~CHsvDvbsInstallation_mminiprescan_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mminiprescan::CHsvDvbsInstallation_mminiprescan()
{
 m_priv = new CHsvDvbsInstallation_mminiprescan_Priv();
iminiprescan	= m_priv->iminiprescan;
iminiprescanctrlN	= m_priv->iminiprescanctrlN;
iminiprescanpow	= m_priv->iminiprescanpow;
iminiprescansatfrontendN	= m_priv->iminiprescansatfrontendN;
m_priv->charsetutil	=charsetutil;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->idvbset	=idvbset;
m_priv->iminiprescanN	=iminiprescanN;
m_priv->ipackage	=ipackage;
m_priv->iprescanparser	=iprescanparser;
m_priv->isigstr	=isigstr;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pins	=pins;
m_priv->pmp	=pmp;
m_priv->qssm	=qssm;
m_priv->satfeapi	=satfeapi;
m_priv->strapi	=strapi;
m_priv->vssm	=vssm;
m_priv->wnddest	=wnddest;
}
CHsvDvbsInstallation_mminiprescan::~CHsvDvbsInstallation_mminiprescan()
{
 delete m_priv;
}
#endif
