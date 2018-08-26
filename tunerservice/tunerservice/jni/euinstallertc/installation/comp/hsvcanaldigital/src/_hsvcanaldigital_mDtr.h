#ifndef HSVCANALDIGITAL_MDTR
#define HSVCANALDIGITAL_MDTR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvCanalDigitalInstallation_mDtr.h"
#include "CHsvCanalDigitalInstallation_mDtr_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvCanalDigitalInstallation_mDtr_Priv::params__init(void)
{
}
CHsvCanalDigitalInstallation_mDtr_Priv::~CHsvCanalDigitalInstallation_mDtr_Priv()
{
}
//public class connections
CHsvCanalDigitalInstallation_mDtr::CHsvCanalDigitalInstallation_mDtr()
{
 m_priv = new CHsvCanalDigitalInstallation_mDtr_Priv();
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
CHsvCanalDigitalInstallation_mDtr::~CHsvCanalDigitalInstallation_mDtr()
{
 delete m_priv;
}
#endif
