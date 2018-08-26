#ifndef HSVEUINS_MSTUB
#define HSVEUINS_MSTUB

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mstub.h"
#include "CHsvEuropeInstallation_mstub_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mstub_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mstub_Priv::~CHsvEuropeInstallation_mstub_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mstub::CHsvEuropeInstallation_mstub()
{
 m_priv = new CHsvEuropeInstallation_mstub_Priv();
hsvprins_pgdatcni	= m_priv->hsvprins_pgdatcni;
}
CHsvEuropeInstallation_mstub::~CHsvEuropeInstallation_mstub()
{
 delete m_priv;
}
#endif
