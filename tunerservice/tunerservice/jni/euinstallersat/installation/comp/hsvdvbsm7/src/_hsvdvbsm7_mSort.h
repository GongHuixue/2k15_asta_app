#ifndef HSVDVBSM7_MSORT
#define HSVDVBSM7_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsM7_mSort.h"
#include "CHsvDvbsM7_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsM7_mSort_Priv::params__init(void)
{
}
CHsvDvbsM7_mSort_Priv::~CHsvDvbsM7_mSort_Priv()
{
}
//public class connections
CHsvDvbsM7_mSort::CHsvDvbsM7_mSort()
{
 m_priv = new CHsvDvbsM7_mSort_Priv();
im7sort	= m_priv->im7sort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsM7_mSort::~CHsvDvbsM7_mSort()
{
 delete m_priv;
}
#endif
