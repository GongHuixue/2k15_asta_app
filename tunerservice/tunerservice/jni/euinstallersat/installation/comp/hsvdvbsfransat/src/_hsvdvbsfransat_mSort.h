#ifndef HSVDVBSFRANSAT_MSORT
#define HSVDVBSFRANSAT_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsFransat_mSort.h"
#include "CHsvDvbsFransat_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsFransat_mSort_Priv::params__init(void)
{
}
CHsvDvbsFransat_mSort_Priv::~CHsvDvbsFransat_mSort_Priv()
{
}
//public class connections
CHsvDvbsFransat_mSort::CHsvDvbsFransat_mSort()
{
 m_priv = new CHsvDvbsFransat_mSort_Priv();
ifransatsort	= m_priv->ifransatsort;
isortpow	= m_priv->isortpow;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbsFransat_mSort::~CHsvDvbsFransat_mSort()
{
 delete m_priv;
}
#endif
