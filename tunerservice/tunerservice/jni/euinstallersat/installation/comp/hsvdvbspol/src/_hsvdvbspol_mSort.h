#ifndef HSVDVBSPOL_MSORT
#define HSVDVBSPOL_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsPol_mSort.h"
#include "CHsvDvbsPol_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsPol_mSort_Priv::params__init(void)
{
}
CHsvDvbsPol_mSort_Priv::~CHsvDvbsPol_mSort_Priv()
{
}
//public class connections
CHsvDvbsPol_mSort::CHsvDvbsPol_mSort()
{
 m_priv = new CHsvDvbsPol_mSort_Priv();
ipolsort	= m_priv->ipolsort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsPol_mSort::~CHsvDvbsPol_mSort()
{
 delete m_priv;
}
#endif
