#ifndef HSVDVBCAMINS_MSETTINGS
#define HSVDVBCAMINS_MSETTINGS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCamInstallation_mSettings.h"
#include "CHsvDvbCamInstallation_mSettings_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCamInstallation_mSettings_Priv::params__init(void)
{
}
CHsvDvbCamInstallation_mSettings_Priv::~CHsvDvbCamInstallation_mSettings_Priv()
{
}
//public class connections
CHsvDvbCamInstallation_mSettings::CHsvDvbCamInstallation_mSettings()
{
 m_priv = new CHsvDvbCamInstallation_mSettings_Priv();
 idvbset	= m_priv->idvbset;
isetpow	= m_priv->isetpow;
syssetN	= m_priv->syssetN;
m_priv->str	=str;
m_priv->rins	=rins;
}
CHsvDvbCamInstallation_mSettings::~CHsvDvbCamInstallation_mSettings()
{
 delete m_priv;
}
#endif
