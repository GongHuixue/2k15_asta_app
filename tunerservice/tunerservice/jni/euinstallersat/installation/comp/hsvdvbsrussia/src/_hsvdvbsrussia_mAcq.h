#ifndef HSVDVBSRUSSIA_MACQ
#define HSVDVBSRUSSIA_MACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsRussia_mAcq.h"
#include "CHsvDvbsRussia_mAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsRussia_mAcq_Priv::params__init(void)
{
}
CHsvDvbsRussia_mAcq_Priv::~CHsvDvbsRussia_mAcq_Priv()
{
}
//public class connections
CHsvDvbsRussia_mAcq::CHsvDvbsRussia_mAcq()
{
 m_priv = new CHsvDvbsRussia_mAcq_Priv();
iacqpow	= m_priv->iacqpow;
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
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
CHsvDvbsRussia_mAcq::~CHsvDvbsRussia_mAcq()
{
 delete m_priv;
}
#endif
