#ifndef HSVZIGGO_MDATAACQ
#define HSVZIGGO_MDATAACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvZiggoInstallation_mDataAcq.h"
#include "CHsvZiggoInstallation_mDataAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvZiggoInstallation_mDataAcq_Priv::params__init(void)
{
}
CHsvZiggoInstallation_mDataAcq_Priv::~CHsvZiggoInstallation_mDataAcq_Priv()
{
}
//public class connections
CHsvZiggoInstallation_mDataAcq::CHsvZiggoInstallation_mDataAcq()
{
 m_priv = new CHsvZiggoInstallation_mDataAcq_Priv();
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
m_priv->dvbset	=dvbset;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ibckg	=ibckg;
m_priv->iins	=iins;
m_priv->insN	=insN;
m_priv->instutil	=instutil;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->rins	=rins;
m_priv->sort	=sort;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
m_priv->strmfltr =strmfltr;
strapiN = m_priv->strapiN;
}
CHsvZiggoInstallation_mDataAcq::~CHsvZiggoInstallation_mDataAcq()
{
 delete m_priv;
}
#endif
