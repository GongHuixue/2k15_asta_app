#ifndef HSVEUINS_MACIDS
#define HSVEUINS_MACIDS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_macids.h"
#include "CHsvEuropeInstallation_macids_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_macids_Priv::params__init(void)
{
}
CHsvEuropeInstallation_macids_Priv::~CHsvEuropeInstallation_macids_Priv()
{
}
//public class connections
CHsvEuropeInstallation_macids::CHsvEuropeInstallation_macids()
{
 m_priv = new CHsvEuropeInstallation_macids_Priv();
iacinv	= m_priv->iacinv;
svpaci_pgcni	= m_priv->svpaci_pgcni;
m_priv->dsdrv	=dsdrv;
m_priv->dsdrv3	=dsdrv3;
m_priv->gfxtxt	=gfxtxt;
m_priv->txtdspcons	=txtdspcons;
}
CHsvEuropeInstallation_macids::~CHsvEuropeInstallation_macids()
{
 delete m_priv;
}
#endif
