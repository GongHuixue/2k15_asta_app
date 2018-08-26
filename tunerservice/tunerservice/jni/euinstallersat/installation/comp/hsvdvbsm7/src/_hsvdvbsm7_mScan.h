#ifndef HSVDVBSM7_MSCAN
#define HSVDVBSM7_MSCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsM7_mScan.h"
#include "CHsvDvbsM7_mScan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsM7_mScan_Priv::params__init(void)
{
}
CHsvDvbsM7_mScan_Priv::~CHsvDvbsM7_mScan_Priv()
{
}
//public class connections
CHsvDvbsM7_mScan::CHsvDvbsM7_mScan()
{
 m_priv = new CHsvDvbsM7_mScan_Priv();
idataacqN	= m_priv->idataacqN;
isvcscan	= m_priv->isvcscan;
isvcscanctrlN	= m_priv->isvcscanctrlN;
isvcscandata	= m_priv->isvcscandata;
isvcscanpow	= m_priv->isvcscanpow;
plfApidvbsN	= m_priv->plfApidvbsN;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->iacqpow	=iacqpow;
m_priv->idataacq	=idataacq;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->isigstr	=isigstr;
m_priv->isortpow	=isortpow;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->satfeapi	=satfeapi;
m_priv->idvbset	=idvbset;
m_priv->iprescanparser	=iprescanparser;
m_priv->strapi = strapi;
}
CHsvDvbsM7_mScan::~CHsvDvbsM7_mScan()
{
 delete m_priv;
}
#endif
