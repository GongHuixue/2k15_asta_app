#ifndef SVPACI_M
#define SVPACI_M

#define GENERATE__LEGACY__DEFINES

#include "../CSvcPaci_m.h"
#include "CSvcPaci_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CSvcPaci_m_Priv::params__init(void)
{
}
CSvcPaci_m_Priv::~CSvcPaci_m_Priv()
{
}
//public class connections
CSvcPaci_m::CSvcPaci_m()
{
 m_priv = new CSvcPaci_m_Priv();
acidecN	= m_priv->acidecN;
acids	= m_priv->acids;
pgaci	= m_priv->pgaci;
pginsN	= m_priv->pginsN;
pow	= m_priv->pow;
txrstN	= m_priv->txrstN;
m_priv->acidat	=acidat;
m_priv->acidec	=acidec;
m_priv->acidsN	=acidsN;
m_priv->adiv	=adiv;
m_priv->langid	=langid;
m_priv->pen	=pen;
m_priv->pgaciN	=pgaciN;
m_priv->pgcni	=pgcni;
m_priv->pkt0	=pkt0;
m_priv->pmp	=pmp;
m_priv->prins	=prins;
m_priv->sysset	=sysset;
m_priv->tmr	=tmr;
m_priv->txtpre	=txtpre;
m_priv->vip	=vip;
}
CSvcPaci_m::~CSvcPaci_m()
{
 delete m_priv;
}
#endif
