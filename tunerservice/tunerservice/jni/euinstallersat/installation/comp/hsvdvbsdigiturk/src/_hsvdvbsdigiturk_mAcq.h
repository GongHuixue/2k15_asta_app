#ifndef HSVDVBSDIGITURK_MACQ
#define HSVDVBSDIGITURK_MACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsDigiTurk_mAcq.h"
#include "CHsvDvbsDigiTurk_mAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsDigiTurk_mAcq_Priv::params__init(void)
{
}
CHsvDvbsDigiTurk_mAcq_Priv::~CHsvDvbsDigiTurk_mAcq_Priv()
{
}
//public class connections
CHsvDvbsDigiTurk_mAcq::CHsvDvbsDigiTurk_mAcq()
{
 m_priv = new CHsvDvbsDigiTurk_mAcq_Priv();
iacqpow	= m_priv->iacqpow;
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->idataacqN	=idataacqN;
m_priv->insstate	=insstate;
m_priv->iscandata	=iscandata;
m_priv->isdsddata	=isdsddata;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->strapi	=strapi;
m_priv->util	=util;
}
CHsvDvbsDigiTurk_mAcq::~CHsvDvbsDigiTurk_mAcq()
{
 delete m_priv;
}
#endif
