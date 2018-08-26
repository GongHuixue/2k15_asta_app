#ifndef HSVEUINS_MPOW
#define HSVEUINS_MPOW

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mpow.h"
#include "CHsvEuropeInstallation_mpow_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mpow_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mpow_Priv::~CHsvEuropeInstallation_mpow_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mpow::CHsvEuropeInstallation_mpow()
{
 m_priv = new CHsvEuropeInstallation_mpow_Priv();
pow	= m_priv->pow;
m_priv->hsvacidec_pow	=hsvacidec_pow;
m_priv->hsvdvbcamins_pow	=hsvdvbcamins_pow;
m_priv->hsvdvbcins_pow	=hsvdvbcins_pow;
m_priv->hsvdvbtins_pow	=hsvdvbtins_pow;
m_priv->hsvdvbtmpegins_pow	=hsvdvbtmpegins_pow;
m_priv->hsvprins_pow	=hsvprins_pow;
m_priv->hsvziggoins_pow	=hsvziggoins_pow;
m_priv->icabpow	=icabpow;
m_priv->iblizoopow	=iblizoopow;
m_priv->icamsortpow	=icamsortpow;
m_priv->iconpow	=iconpow;
m_priv->idbookconpow	=idbookconpow;
m_priv->idbooksortpow	=idbooksortpow;
m_priv->idvbtsortpow	=idvbtsortpow;
m_priv->ifinsortpow	=ifinsortpow;
m_priv->iitapow	=iitapow;
m_priv->ilitepow	=ilitepow;
m_priv->imfreqctlpow	=imfreqctlpow;
m_priv->impegpow	=impegpow;
m_priv->impow	=impow;
m_priv->inorpow	=inorpow;
m_priv->svpaci_pow	=svpaci_pow;
m_priv->idvbtapmeasortpow	=idvbtapmeasortpow;
m_priv->idvbthungarysortpow	=idvbthungarysortpow;
m_priv->hsvcanaldigitalins_pow	=hsvcanaldigitalins_pow;
}
CHsvEuropeInstallation_mpow::~CHsvEuropeInstallation_mpow()
{
 delete m_priv;
}
#endif
