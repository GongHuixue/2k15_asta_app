#ifndef HSVDVBSFRANSAT_MBCKGND
#define HSVDVBSFRANSAT_MBCKGND

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsFransat_mBckgnd.h"
#include "CHsvDvbsFransat_mBckgnd_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsFransat_mBckgnd_Priv::params__init(void)
{
}
CHsvDvbsFransat_mBckgnd_Priv::~CHsvDvbsFransat_mBckgnd_Priv()
{
}
//public class connections
CHsvDvbsFransat_mBckgnd::CHsvDvbsFransat_mBckgnd()
{
 m_priv = new CHsvDvbsFransat_mBckgnd_Priv();
bckctrlN	= m_priv->bckctrlN;
ibckAcqN	= m_priv->ibckAcqN;
ibckInstall	= m_priv->ibckInstall;
ibckgndpow	= m_priv->ibckgndpow;
plfresN	= m_priv->plfresN;
strapiN	= m_priv->strapiN;
sysstateN	= m_priv->sysstateN;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->idataacq	=idataacq;
m_priv->iinsN	=iinsN;
m_priv->insstate	=insstate;
m_priv->observer	=observer;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->plfres	=plfres;
m_priv->pmp	=pmp;
m_priv->s2div	=s2div;
m_priv->strapi	=strapi;
}
CHsvDvbsFransat_mBckgnd::~CHsvDvbsFransat_mBckgnd()
{
 delete m_priv;
}
#endif
