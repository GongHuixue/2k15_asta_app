#ifndef HSVDVBSINS_MSATIPPRESCAN
#define HSVDVBSINS_MSATIPPRESCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_msatipprescan.h"
#include "CHsvDvbsInstallation_msatipprescan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_msatipprescan_Priv::params__init(void)
{
}
CHsvDvbsInstallation_msatipprescan_Priv::~CHsvDvbsInstallation_msatipprescan_Priv()
{
}
//public class connections
CHsvDvbsInstallation_msatipprescan::CHsvDvbsInstallation_msatipprescan()
{
 m_priv = new CHsvDvbsInstallation_msatipprescan_Priv();
iprescan	= m_priv->iprescan;
iprescanctrlN	= m_priv->iprescanctrlN;
iprescandata	= m_priv->iprescandata;
iprescanpow	= m_priv->iprescanpow;
iprescansatfrontendN	= m_priv->iprescansatfrontendN;
m_priv->charsetutil	=charsetutil;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->idvbset	=idvbset;
m_priv->iinsN	=iinsN;
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
m_priv->sysset	=sysset;
m_priv->vssm	=vssm;
m_priv->wnddest	=wnddest;
}
CHsvDvbsInstallation_msatipprescan::~CHsvDvbsInstallation_msatipprescan()
{
 delete m_priv;
}
#endif
