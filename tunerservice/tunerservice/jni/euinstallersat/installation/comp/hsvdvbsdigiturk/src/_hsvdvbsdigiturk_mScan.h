#ifndef HSVDVBSDIGITURK_MSCAN
#define HSVDVBSDIGITURK_MSCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsDigiTurk_mScan.h"
#include "CHsvDvbsDigiTurk_mScan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsDigiTurk_mScan_Priv::params__init(void)
{
}
CHsvDvbsDigiTurk_mScan_Priv::~CHsvDvbsDigiTurk_mScan_Priv()
{
}
//public class connections
CHsvDvbsDigiTurk_mScan::CHsvDvbsDigiTurk_mScan()
{
 m_priv = new CHsvDvbsDigiTurk_mScan_Priv();
idataacqN	= m_priv->idataacqN;
iscan	= m_priv->iscan;
iscanctrlN	= m_priv->iscanctrlN;
iscandata	= m_priv->iscandata;
iscanpow	= m_priv->iscanpow;
isdsddata	= m_priv->isdsddata;
plfApidvbsN	= m_priv->plfApidvbsN;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->iacqpow	=iacqpow;
m_priv->idataacq	=idataacq;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->isigstr	=isigstr;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->satfeapi	=satfeapi;
m_priv->strapi	=strapi;
m_priv->util	=util;
}
CHsvDvbsDigiTurk_mScan::~CHsvDvbsDigiTurk_mScan()
{
 delete m_priv;
}
#endif
