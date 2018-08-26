#ifndef HSVDVBSGENERIC_MSRT
#define HSVDVBSGENERIC_MSRT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsGeneric_mSrt.h"
#include "CHsvDvbsGeneric_mSrt_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsGeneric_mSrt_Priv::params__init(void)
{
}
CHsvDvbsGeneric_mSrt_Priv::~CHsvDvbsGeneric_mSrt_Priv()
{
}
//public class connections
CHsvDvbsGeneric_mSrt::CHsvDvbsGeneric_mSrt()
{
 m_priv = new CHsvDvbsGeneric_mSrt_Priv();
isrt	= m_priv->isrt;
isrtAcqN	= m_priv->isrtAcqN;
isrtctrlN	= m_priv->isrtctrlN;
isrtdata	= m_priv->isrtdata;
isrtplfApidvbsN	= m_priv->isrtplfApidvbsN;
isrtpow	= m_priv->isrtpow;
isrtstrapiN = m_priv->isrtstrapiN;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->iacqpow	=iacqpow;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->isigstr	=isigstr;
m_priv->isort	=isort;
m_priv->iutil	=iutil;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->pgdat3	=pgdat3;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pgsel	=pgsel;
m_priv->pmp	=pmp;
m_priv->satfeapi	=satfeapi;
m_priv->strapi	=strapi;
m_priv->strmfltr	=strmfltr;
m_priv->wnddest	=wnddest;
}
CHsvDvbsGeneric_mSrt::~CHsvDvbsGeneric_mSrt()
{
 delete m_priv;
}
#endif
