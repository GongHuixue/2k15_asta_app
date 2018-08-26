#ifndef HSVPRINS_MSETTINGS
#define HSVPRINS_MSETTINGS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvPresetInstallation_msettings.h"
#include "CHsvPresetInstallation_msettings_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvPresetInstallation_msettings_Priv::params__init(void)
{
}
CHsvPresetInstallation_msettings_Priv::~CHsvPresetInstallation_msettings_Priv()
{
}
//public class connections
CHsvPresetInstallation_msettings::CHsvPresetInstallation_msettings()
{
 m_priv = new CHsvPresetInstallation_msettings_Priv();
anaset	= m_priv->anaset;
m_priv->col	=col;
m_priv->feapi	=feapi;
m_priv->wnddest	=wnddest;
m_priv->xcol	=xcol;
}
CHsvPresetInstallation_msettings::~CHsvPresetInstallation_msettings()
{
 delete m_priv;
}
#endif
