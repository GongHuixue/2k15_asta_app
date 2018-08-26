#ifndef HSVDVBSGENERIC_MACQ
#define HSVDVBSGENERIC_MACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsGeneric_mAcq.h"
#include "CHsvDvbsGeneric_mAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsGeneric_mAcq_Priv::params__init(void)
{
}
CHsvDvbsGeneric_mAcq_Priv::~CHsvDvbsGeneric_mAcq_Priv()
{
}
//public class connections
CHsvDvbsGeneric_mAcq::CHsvDvbsGeneric_mAcq()
{
 m_priv = new CHsvDvbsGeneric_mAcq_Priv();
iacqpow	= m_priv->iacqpow;
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
m_priv->charsetutil	=charsetutil;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->iacqN	=iacqN;
m_priv->idvbset	=idvbset;
m_priv->insstate	=insstate;
m_priv->iprescanparser	=iprescanparser;
m_priv->isrtdata	=isrtdata;
m_priv->isvcscandata	=isvcscandata;
m_priv->iutil	=iutil;
m_priv->pen	=pen;
m_priv->pgdat3	=pgdat3;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pgsel	=pgsel;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->rtk	=rtk;
m_priv->strapi	=strapi;
m_priv->dataacq =dataacq;
m_priv->insN	=insN;
m_priv->ipackage =ipackage;
}
CHsvDvbsGeneric_mAcq::~CHsvDvbsGeneric_mAcq()
{
 delete m_priv;
}
#endif
