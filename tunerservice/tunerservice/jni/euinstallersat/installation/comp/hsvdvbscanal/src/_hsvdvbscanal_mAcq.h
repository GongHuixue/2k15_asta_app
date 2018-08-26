#ifndef HSVDVBSCANAL_MACQ
#define HSVDVBSCANAL_MACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsCanal_mAcq.h"
#include "CHsvDvbsCanal_mAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsCanal_mAcq_Priv::params__init(void)
{
}
CHsvDvbsCanal_mAcq_Priv::~CHsvDvbsCanal_mAcq_Priv()
{
}
//public class connections
CHsvDvbsCanal_mAcq::CHsvDvbsCanal_mAcq()
{
 m_priv = new CHsvDvbsCanal_mAcq_Priv();
iacqpow	= m_priv->iacqpow;
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
m_priv->cids	=cids;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->idataacqN	=idataacqN;
m_priv->insstate	=insstate;
m_priv->isvcscandata	=isvcscandata;
m_priv->iutil	=iutil;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
}
CHsvDvbsCanal_mAcq::~CHsvDvbsCanal_mAcq()
{
 delete m_priv;
}
#endif
