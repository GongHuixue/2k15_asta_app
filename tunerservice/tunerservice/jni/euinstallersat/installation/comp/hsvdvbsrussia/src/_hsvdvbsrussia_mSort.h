#ifndef HSVDVBSRUSSIA_MSORT
#define HSVDVBSRUSSIA_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsRussia_mSort.h"
#include "CHsvDvbsRussia_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsRussia_mSort_Priv::params__init(void)
{
}
CHsvDvbsRussia_mSort_Priv::~CHsvDvbsRussia_mSort_Priv()
{
}
//public class connections
CHsvDvbsRussia_mSort::CHsvDvbsRussia_mSort()
{
 m_priv = new CHsvDvbsRussia_mSort_Priv();
irussiasort	= m_priv->irussiasort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsRussia_mSort::~CHsvDvbsRussia_mSort()
{
 delete m_priv;
}
#endif
