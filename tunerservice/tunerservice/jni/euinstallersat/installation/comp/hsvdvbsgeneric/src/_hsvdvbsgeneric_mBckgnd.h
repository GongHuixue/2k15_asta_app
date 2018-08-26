#ifndef HSVDVBSGENERIC_MBCKGND
#define HSVDVBSGENERIC_MBCKGND

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsGeneric_mBckgnd.h"
#include "CHsvDvbsGeneric_mBckgnd_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsGeneric_mBckgnd_Priv::params__init(void)
{
}
CHsvDvbsGeneric_mBckgnd_Priv::~CHsvDvbsGeneric_mBckgnd_Priv()
{
}
//public class connections
CHsvDvbsGeneric_mBckgnd::CHsvDvbsGeneric_mBckgnd()
{
 m_priv = new CHsvDvbsGeneric_mBckgnd_Priv();
bckctrlN	= m_priv->bckctrlN;
ibckAcqN	= m_priv->ibckAcqN;
ibckInstall	= m_priv->ibckInstall;
ibckgndpow	= m_priv->ibckgndpow;
strapiN	= m_priv->strapiN;
m_priv->idataacq	=idataacq;
m_priv->insstate	=insstate;
m_priv->pen	=pen;
m_priv->plfres	=plfres;
m_priv->pmp	=pmp;
m_priv->s2div	=s2div;
}
CHsvDvbsGeneric_mBckgnd::~CHsvDvbsGeneric_mBckgnd()
{
 delete m_priv;
}
#endif
