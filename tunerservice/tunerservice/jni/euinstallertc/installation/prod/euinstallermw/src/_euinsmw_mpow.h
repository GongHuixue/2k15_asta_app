#ifndef EUINSMW_MPOW
#define EUINSMW_MPOW

#define GENERATE__LEGACY__DEFINES

#include "../CEuInstallerMw_mpow.h"
#include "CEuInstallerMw_mpow_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CEuInstallerMw_mpow_Priv::params__init(void)
{
}
CEuInstallerMw_mpow_Priv::~CEuInstallerMw_mpow_Priv()
{
}
//public class connections
CEuInstallerMw_mpow::CEuInstallerMw_mpow()
{
 m_priv = new CEuInstallerMw_mpow_Priv();
pow	= m_priv->pow;
m_priv->hsvdvbsdm_pow	=hsvdvbsdm_pow;
m_priv->hsveuins_pow	=hsveuins_pow;
m_priv->hsvfe_pow	=hsvfe_pow;
m_priv->hsvpgdat_pow	=hsvpgdat_pow;
m_priv->txtpow = txtpow;
}
CEuInstallerMw_mpow::~CEuInstallerMw_mpow()
{
 delete m_priv;
}
#endif
