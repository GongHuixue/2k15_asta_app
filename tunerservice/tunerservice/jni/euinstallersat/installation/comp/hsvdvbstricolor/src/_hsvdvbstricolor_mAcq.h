#ifndef HSVDVBSTRICOLOR_MACQ
#define HSVDVBSTRICOLOR_MACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsTricolor_mAcq.h"
#include "CHsvDvbsTricolor_mAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsTricolor_mAcq_Priv::params__init(void)
{
}
CHsvDvbsTricolor_mAcq_Priv::~CHsvDvbsTricolor_mAcq_Priv()
{
}
//public class connections
CHsvDvbsTricolor_mAcq::CHsvDvbsTricolor_mAcq()
{
 m_priv = new CHsvDvbsTricolor_mAcq_Priv();
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
CHsvDvbsTricolor_mAcq::~CHsvDvbsTricolor_mAcq()
{
 delete m_priv;
}
#endif
