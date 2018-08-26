#ifndef HSVDVBSFRANSAT_MACQ
#define HSVDVBSFRANSAT_MACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsFransat_mAcq.h"
#include "CHsvDvbsFransat_mAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsFransat_mAcq_Priv::params__init(void)
{
}
CHsvDvbsFransat_mAcq_Priv::~CHsvDvbsFransat_mAcq_Priv()
{
}
//public class connections
CHsvDvbsFransat_mAcq::CHsvDvbsFransat_mAcq()
{
 m_priv = new CHsvDvbsFransat_mAcq_Priv();
iacqpow	= m_priv->iacqpow;
idataacq	= m_priv->idataacq;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->ibckAcqN	=ibckAcqN;
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
}
CHsvDvbsFransat_mAcq::~CHsvDvbsFransat_mAcq()
{
 delete m_priv;
}
#endif
