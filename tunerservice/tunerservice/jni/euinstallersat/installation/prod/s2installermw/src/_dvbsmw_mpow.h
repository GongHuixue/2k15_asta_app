#ifndef DVBSMW_MPOW
#define DVBSMW_MPOW

#define GENERATE__LEGACY__DEFINES

#include "../CS2InstallerMw_mpow.h"
#include "CS2InstallerMw_mpow_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CS2InstallerMw_mpow_Priv::params__init(void)
{
}
CS2InstallerMw_mpow_Priv::~CS2InstallerMw_mpow_Priv()
{
}
//public class connections
CS2InstallerMw_mpow::CS2InstallerMw_mpow()
{
 m_priv = new CS2InstallerMw_mpow_Priv();
pow	= m_priv->pow;
m_priv->hsvdvbsdm_pow	=hsvdvbsdm_pow;
m_priv->hsvdvbsins_pow	=hsvdvbsins_pow;
m_priv->hsvsatfe_pow	=hsvsatfe_pow;
m_priv->sathsvpgdat_pow	=sathsvpgdat_pow;
}
CS2InstallerMw_mpow::~CS2InstallerMw_mpow()
{
 delete m_priv;
}
#endif
