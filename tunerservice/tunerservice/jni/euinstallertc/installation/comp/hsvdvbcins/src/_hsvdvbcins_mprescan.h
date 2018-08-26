#ifndef HSVDVBCINS_MPRESCAN
#define HSVDVBCINS_MPRESCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_mprescan.h"
#include "CHsvDvbCInstallation_mprescan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_mprescan_Priv::params__init(void)
{
}
CHsvDvbCInstallation_mprescan_Priv::~CHsvDvbCInstallation_mprescan_Priv()
{
}
//public class connections
CHsvDvbCInstallation_mprescan::CHsvDvbCInstallation_mprescan()
{
 m_priv = new CHsvDvbCInstallation_mprescan_Priv();
ipctrlN	= m_priv->ipctrlN;
ipena	= m_priv->ipena;
iprescan	= m_priv->iprescan;
iprescanfeN	= m_priv->iprescanfeN;
iprescanpow	= m_priv->iprescanpow;
m_priv->ctrl	=ctrl;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->hsverr	=hsverr;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->insN	=insN;
m_priv->iprescanN	=iprescanN;
m_priv->pen	=pen;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->strapi	=strapi;
m_priv->wnddest	=wnddest;
}
CHsvDvbCInstallation_mprescan::~CHsvDvbCInstallation_mprescan()
{
 delete m_priv;
}
#endif
