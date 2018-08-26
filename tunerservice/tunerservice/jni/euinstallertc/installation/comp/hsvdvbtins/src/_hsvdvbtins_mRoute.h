#ifndef HSVDVBTINS_MROUTE
#define HSVDVBTINS_MROUTE

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mRoute.h"
#include "CHsvDvbTInstallation_mRoute_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mRoute_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mRoute_Priv::~CHsvDvbTInstallation_mRoute_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mRoute::CHsvDvbTInstallation_mRoute()
{
 m_priv = new CHsvDvbTInstallation_mRoute_Priv();
ctrlN	= m_priv->ctrlN;
feapiN	= m_priv->feapiN;
idvbt	= m_priv->idvbt;
iroute	= m_priv->iroute;
istub	= m_priv->istub;
pow	= m_priv->pow;
strapiN	= m_priv->strapiN;
m_priv->eurdiv	=eurdiv;
m_priv->ibctrlN	=ibctrlN;
m_priv->ibpow	=ibpow;
m_priv->ibstrapiN	=ibstrapiN;
m_priv->icctrlN	=icctrlN;
m_priv->icntrypow	=icntrypow;
m_priv->icntrystrapiN	=icntrystrapiN;
m_priv->idatapow	=idatapow;
m_priv->idctrlN	=idctrlN;
m_priv->idtr	=idtr;
m_priv->idtrfeN	=idtrfeN;
m_priv->idtrpow	=idtrpow;
m_priv->idvbset	=idvbset;
m_priv->ifctrlN	=ifctrlN;
m_priv->ifull	=ifull;
m_priv->ifullfeN	=ifullfeN;
m_priv->ifullpow	=ifullpow;
m_priv->iqctrlN	=iqctrlN;
m_priv->iquick	=iquick;
m_priv->iquickfeN	=iquickfeN;
m_priv->iquickpow	=iquickpow;
m_priv->isetpow	=isetpow;
m_priv->rins	=rins;
m_priv->idstrapiN	=idstrapiN;
}
CHsvDvbTInstallation_mRoute::~CHsvDvbTInstallation_mRoute()
{
 delete m_priv;
}
#endif
