#ifndef HSVCANALDIGITAL_MINSTALL
#define HSVCANALDIGITAL_MINSTALL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvCanalDigitalInstallation_mInstall.h"
#include "CHsvCanalDigitalInstallation_mInstall_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvCanalDigitalInstallation_mInstall_Priv::params__init(void)
{
}
CHsvCanalDigitalInstallation_mInstall_Priv::~CHsvCanalDigitalInstallation_mInstall_Priv()
{
}
//public class connections
CHsvCanalDigitalInstallation_mInstall::CHsvCanalDigitalInstallation_mInstall()
{
 m_priv = new CHsvCanalDigitalInstallation_mInstall_Priv();
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
CHsvCanalDigitalInstallation_mInstall::~CHsvCanalDigitalInstallation_mInstall()
{
 delete m_priv;
}
#endif
