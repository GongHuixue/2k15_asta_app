#ifndef HSVDVBSGENERIC_MSCAN
#define HSVDVBSGENERIC_MSCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsGeneric_mScan.h"
#include "CHsvDvbsGeneric_mScan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsGeneric_mScan_Priv::params__init(void)
{
}
CHsvDvbsGeneric_mScan_Priv::~CHsvDvbsGeneric_mScan_Priv()
{
}
//public class connections
CHsvDvbsGeneric_mScan::CHsvDvbsGeneric_mScan()
{
 m_priv = new CHsvDvbsGeneric_mScan_Priv();
iscanAcqN	= m_priv->iscanAcqN;
isvcscan	= m_priv->isvcscan;
isvcscanctrlN	= m_priv->isvcscanctrlN;
isvcscandata	= m_priv->isvcscandata;
isvcscanplfApidvbsN	= m_priv->isvcscanplfApidvbsN;
isvcscanpow	= m_priv->isvcscanpow;
m_priv->apsysset	=apsysset;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->iacqpow	=iacqpow;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->isigstr	=isigstr;
m_priv->iutil	=iutil;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->s2div	=s2div;
m_priv->satfeapi	=satfeapi;
m_priv->strapi	=strapi;
m_priv->wnddest	=wnddest;
}
CHsvDvbsGeneric_mScan::~CHsvDvbsGeneric_mScan()
{
 delete m_priv;
}
#endif
