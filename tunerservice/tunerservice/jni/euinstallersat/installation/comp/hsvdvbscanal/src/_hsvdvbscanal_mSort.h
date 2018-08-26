#ifndef HSVDVBSCANAL_MSORT
#define HSVDVBSCANAL_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsCanal_mSort.h"
#include "CHsvDvbsCanal_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsCanal_mSort_Priv::params__init(void)
{
}
CHsvDvbsCanal_mSort_Priv::~CHsvDvbsCanal_mSort_Priv()
{
}
//public class connections
CHsvDvbsCanal_mSort::CHsvDvbsCanal_mSort()
{
 m_priv = new CHsvDvbsCanal_mSort_Priv();
icanalsort	= m_priv->icanalsort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsCanal_mSort::~CHsvDvbsCanal_mSort()
{
 delete m_priv;
}
#endif
