#ifndef HSVCANALDIGITAL_MPREINSTALL
#define HSVCANALDIGITAL_MPREINSTALL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvCanalDigitalInstallation_mPreInstall.h"
#include "CHsvCanalDigitalInstallation_mPreInstall_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvCanalDigitalInstallation_mPreInstall_Priv::params__init(void)
{
}
CHsvCanalDigitalInstallation_mPreInstall_Priv::~CHsvCanalDigitalInstallation_mPreInstall_Priv()
{
}
//public class connections
CHsvCanalDigitalInstallation_mPreInstall::CHsvCanalDigitalInstallation_mPreInstall()
{
 m_priv = new CHsvCanalDigitalInstallation_mPreInstall_Priv();
ipreins	= m_priv->ipreins;
ipreinsctrlN	= m_priv->ipreinsctrlN;
ipreinsfeapiN	= m_priv->ipreinsfeapiN;
ipreinspow	= m_priv->ipreinspow;
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
m_priv->iprescanN	=iprescanN;
}
CHsvCanalDigitalInstallation_mPreInstall::~CHsvCanalDigitalInstallation_mPreInstall()
{
 delete m_priv;
}
#endif
