#ifndef HSVDVBSDIGITURK_MSORT
#define HSVDVBSDIGITURK_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsDigiTurk_mSort.h"
#include "CHsvDvbsDigiTurk_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsDigiTurk_mSort_Priv::params__init(void)
{
}
CHsvDvbsDigiTurk_mSort_Priv::~CHsvDvbsDigiTurk_mSort_Priv()
{
}
//public class connections
CHsvDvbsDigiTurk_mSort::CHsvDvbsDigiTurk_mSort()
{
 m_priv = new CHsvDvbsDigiTurk_mSort_Priv();
isort	= m_priv->isort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->iscandata	=iscandata;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsDigiTurk_mSort::~CHsvDvbsDigiTurk_mSort()
{
 delete m_priv;
}
#endif
