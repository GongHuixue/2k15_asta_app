#ifndef HSVDVBSINS_MSETTINGS
#define HSVDVBSINS_MSETTINGS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_msettings.h"
#include "CHsvDvbsInstallation_msettings_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_msettings_Priv::params__init(void)
{
}
CHsvDvbsInstallation_msettings_Priv::~CHsvDvbsInstallation_msettings_Priv()
{
}
//public class connections
CHsvDvbsInstallation_msettings::CHsvDvbsInstallation_msettings()
{
 m_priv = new CHsvDvbsInstallation_msettings_Priv();
idvbset	= m_priv->idvbset;
idvbsetpow	= m_priv->idvbsetpow;
insroute	= m_priv->insroute;
sysnotifyN	= m_priv->sysnotifyN;
m_priv->apsysset	=apsysset;
m_priv->cids	=cids;
m_priv->err	=err;
m_priv->insN	=insN;
m_priv->s2div	=s2div;
m_priv->sysset	=sysset;
}
CHsvDvbsInstallation_msettings::~CHsvDvbsInstallation_msettings()
{
 delete m_priv;
}
#endif
