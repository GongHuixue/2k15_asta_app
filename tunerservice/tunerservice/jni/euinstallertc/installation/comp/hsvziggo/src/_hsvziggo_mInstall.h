#ifndef HSVZIGGO_MINSTALL
#define HSVZIGGO_MINSTALL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvZiggoInstallation_mInstall.h"
#include "CHsvZiggoInstallation_mInstall_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvZiggoInstallation_mInstall_Priv::params__init(void)
{
}
CHsvZiggoInstallation_mInstall_Priv::~CHsvZiggoInstallation_mInstall_Priv()
{
}
//public class connections
CHsvZiggoInstallation_mInstall::CHsvZiggoInstallation_mInstall()
{
 m_priv = new CHsvZiggoInstallation_mInstall_Priv();
iins	= m_priv->iins;
iinsctrlN	= m_priv->iinsctrlN;
iinsfeapiN	= m_priv->iinsfeapiN;
iinspow	= m_priv->iinspow;
m_priv->ctrl	=ctrl;
m_priv->dvbset	=dvbset;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->hsverr	=hsverr;
m_priv->ibckg	=ibckg;
m_priv->idataacq	=idataacq;
m_priv->insN	=insN;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->strapi	=strapi;
m_priv->wnddest	=wnddest;
}
CHsvZiggoInstallation_mInstall::~CHsvZiggoInstallation_mInstall()
{
 delete m_priv;
}
#endif
