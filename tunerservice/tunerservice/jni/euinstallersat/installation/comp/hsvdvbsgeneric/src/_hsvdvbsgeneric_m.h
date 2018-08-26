#ifndef HSVDVBSGENERIC_M
#define HSVDVBSGENERIC_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsGeneric_m.h"
#include "CHsvDvbsGeneric_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsGeneric_m_Priv::params__init(void)
{
}
CHsvDvbsGeneric_m_Priv::~CHsvDvbsGeneric_m_Priv()
{
}
//public class connections
CHsvDvbsGeneric_m::CHsvDvbsGeneric_m()
{
 m_priv = new CHsvDvbsGeneric_m_Priv();
bckInstall	= m_priv->bckInstall;
ctrlN	= m_priv->ctrlN;
iacqN	= m_priv->iacqN;
insN	=m_priv->insN;
ins	= m_priv->ins;
plfApidvbsN	= m_priv->plfApidvbsN;
pow	= m_priv->pow;
strapiN = m_priv->strapiN;
m_priv->err	=err;
m_priv->iacqpow	=iacqpow;
m_priv->ibckAcqN	=ibckAcqN;
m_priv->ibckInstall	=ibckInstall;
m_priv->ibckgndpow	=ibckgndpow;
m_priv->insstate	=insstate;
m_priv->iscanAcqN	=iscanAcqN;
m_priv->isortpow	=isortpow;
m_priv->isrt	=isrt;
m_priv->isrtAcqN	=isrtAcqN;
m_priv->isrtctrlN	=isrtctrlN;
m_priv->isrtplfApidvbsN	=isrtplfApidvbsN;
m_priv->isrtpow	=isrtpow;
m_priv->isvcscan	=isvcscan;
m_priv->isvcscanctrlN	=isvcscanctrlN;
m_priv->isvcscanplfApidvbsN	=isvcscanplfApidvbsN;
m_priv->isvcscanpow	=isvcscanpow;
m_priv->isrtstrapiN = isrtstrapiN;
m_priv->ibckgndstrapiN = ibckgndstrapiN;
}
CHsvDvbsGeneric_m::~CHsvDvbsGeneric_m()
{
 delete m_priv;
}
#endif
