#ifndef HSVDVBSTRICOLOR_MSCAN
#define HSVDVBSTRICOLOR_MSCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsTricolor_mScan.h"
#include "CHsvDvbsTricolor_mScan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsTricolor_mScan_Priv::params__init(void)
{
}
CHsvDvbsTricolor_mScan_Priv::~CHsvDvbsTricolor_mScan_Priv()
{
}
//public class connections
CHsvDvbsTricolor_mScan::CHsvDvbsTricolor_mScan()
{
	m_priv = new CHsvDvbsTricolor_mScan_Priv();
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
	m_priv->util	=util;
	m_priv->idvbset = idvbset;
	m_priv->strapi = strapi;
	m_priv->itricolorsettings = itricolorsettings;
}
CHsvDvbsTricolor_mScan::~CHsvDvbsTricolor_mScan()
{
 delete m_priv;
}
#endif
