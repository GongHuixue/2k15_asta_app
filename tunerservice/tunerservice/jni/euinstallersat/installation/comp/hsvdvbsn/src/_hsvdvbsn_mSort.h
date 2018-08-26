#ifndef HSVDVBSN_MSORT
#define HSVDVBSN_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsN_mSort.h"
#include "CHsvDvbsN_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsN_mSort_Priv::params__init(void)
{
}
CHsvDvbsN_mSort_Priv::~CHsvDvbsN_mSort_Priv()
{
}
//public class connections
CHsvDvbsN_mSort::CHsvDvbsN_mSort()
{
 m_priv = new CHsvDvbsN_mSort_Priv();
insort	= m_priv->insort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsN_mSort::~CHsvDvbsN_mSort()
{
 delete m_priv;
}
#endif
