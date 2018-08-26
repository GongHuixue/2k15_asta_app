#ifndef HSVDVBCINS_MDATAACQ
#define HSVDVBCINS_MDATAACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_mDataAcq.h"
#include "CHsvDvbCInstallation_mDataAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_mDataAcq_Priv::params__init(void)
{
}
CHsvDvbCInstallation_mDataAcq_Priv::~CHsvDvbCInstallation_mDataAcq_Priv()
{
}
//public class connections
CHsvDvbCInstallation_mDataAcq::CHsvDvbCInstallation_mDataAcq()
{
 m_priv = new CHsvDvbCInstallation_mDataAcq_Priv();
iacqpow	= m_priv->iacqpow;
iacqstrapiN	= m_priv->iacqstrapiN;
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
m_priv->cids	=cids;
m_priv->divsupp	=divsupp;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->idvbset	=idvbset;
m_priv->ifull	=ifull;
m_priv->igrid	=igrid;
m_priv->insN	=insN;
m_priv->installN	=installN;
m_priv->instutil	=instutil;
m_priv->iquick	=iquick;
m_priv->mpldiv	=mpldiv;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sort	=sort;
m_priv->sortN	=sortN;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->str	=str;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvDvbCInstallation_mDataAcq::~CHsvDvbCInstallation_mDataAcq()
{
 delete m_priv;
}
#endif
