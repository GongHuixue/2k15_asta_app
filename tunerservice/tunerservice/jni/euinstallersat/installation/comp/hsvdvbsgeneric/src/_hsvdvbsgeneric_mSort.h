#ifndef HSVDVBSGENERIC_MSORT
#define HSVDVBSGENERIC_MSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsGeneric_mSort.h"
#include "CHsvDvbsGeneric_mSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsGeneric_mSort_Priv::params__init(void)
{
}
CHsvDvbsGeneric_mSort_Priv::~CHsvDvbsGeneric_mSort_Priv()
{
}
//public class connections
CHsvDvbsGeneric_mSort::CHsvDvbsGeneric_mSort()
{
 m_priv = new CHsvDvbsGeneric_mSort_Priv();
isort	= m_priv->isort;
isortpow	= m_priv->isortpow;
m_priv->idvbset	=idvbset;
m_priv->iinsN	=iinsN;
m_priv->ipackage	=ipackage;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->satfeapi	=satfeapi;
}
CHsvDvbsGeneric_mSort::~CHsvDvbsGeneric_mSort()
{
 delete m_priv;
}
#endif
