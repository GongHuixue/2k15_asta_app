#ifndef HSVEUINS_MSYSSET
#define HSVEUINS_MSYSSET

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_msysset.h"
#include "CHsvEuropeInstallation_msysset_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_msysset_Priv::params__init(void)
{
}
CHsvEuropeInstallation_msysset_Priv::~CHsvEuropeInstallation_msysset_Priv()
{
}
//public class connections
CHsvEuropeInstallation_msysset::CHsvEuropeInstallation_msysset()
{
 m_priv = new CHsvEuropeInstallation_msysset_Priv();
icountid	= m_priv->icountid;
ilangid	= m_priv->ilangid;
}
CHsvEuropeInstallation_msysset::~CHsvEuropeInstallation_msysset()
{
 delete m_priv;
}
#endif
