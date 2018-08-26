#ifndef HSVDVBSTRICOLOR_MSORT
#define HSVDVBSTRICOLOR_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsTricolor_mSort.h"
#include "CHsvDvbsTricolor_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsTricolor_mSort_Priv::params__init(void)
{
}
CHsvDvbsTricolor_mSort_Priv::~CHsvDvbsTricolor_mSort_Priv()
{
}
//public class connections
CHsvDvbsTricolor_mSort::CHsvDvbsTricolor_mSort()
{
 m_priv = new CHsvDvbsTricolor_mSort_Priv();
itricolorsort	= m_priv->itricolorsort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsTricolor_mSort::~CHsvDvbsTricolor_mSort()
{
 delete m_priv;
}
#endif
