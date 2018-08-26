#ifndef HSVDVBSINS_MUTIL
#define HSVDVBSINS_MUTIL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mutil.h"
#include "CHsvDvbsInstallation_mutil_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mutil_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mutil_Priv::~CHsvDvbsInstallation_mutil_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mutil::CHsvDvbsInstallation_mutil()
{
 m_priv = new CHsvDvbsInstallation_mutil_Priv();
iutil	= m_priv->iutil;
m_priv->pins	=pins;
m_priv->pgdb 	=pgdb;
m_priv->pgdbconst = pgdbconst;
}
CHsvDvbsInstallation_mutil::~CHsvDvbsInstallation_mutil()
{
 delete m_priv;
}
#endif
