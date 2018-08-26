#ifndef HSVZIGGO_MDTR
#define HSVZIGGO_MDTR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvZiggoInstallation_mDtr.h"
#include "CHsvZiggoInstallation_mDtr_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvZiggoInstallation_mDtr_Priv::params__init(void)
{
}
CHsvZiggoInstallation_mDtr_Priv::~CHsvZiggoInstallation_mDtr_Priv()
{
}
//public class connections
CHsvZiggoInstallation_mDtr::CHsvZiggoInstallation_mDtr()
{
 m_priv = new CHsvZiggoInstallation_mDtr_Priv();
idtr	= m_priv->idtr;
idtrfeapiN	= m_priv->idtrfeapiN;
idtrpow	= m_priv->idtrpow;
m_priv->hsverr	=hsverr;
m_priv->insN	=insN;
m_priv->pen	=pen;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->ctrl	=ctrl;
}
CHsvZiggoInstallation_mDtr::~CHsvZiggoInstallation_mDtr()
{
 delete m_priv;
}
#endif
