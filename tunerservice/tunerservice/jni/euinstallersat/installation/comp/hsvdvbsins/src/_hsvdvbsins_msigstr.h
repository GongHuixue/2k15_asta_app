#ifndef HSVDVBSINS_MSIGSTR
#define HSVDVBSINS_MSIGSTR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_msigstr.h"
#include "CHsvDvbsInstallation_msigstr_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_msigstr_Priv::params__init(void)
{
}
CHsvDvbsInstallation_msigstr_Priv::~CHsvDvbsInstallation_msigstr_Priv()
{
}
//public class connections
CHsvDvbsInstallation_msigstr::CHsvDvbsInstallation_msigstr()
{
 m_priv = new CHsvDvbsInstallation_msigstr_Priv();
isigstr	= m_priv->isigstr;
m_priv->qssm	=qssm;
m_priv->vssm	=vssm;
m_priv->wnddest	=wnddest;
}
CHsvDvbsInstallation_msigstr::~CHsvDvbsInstallation_msigstr()
{
 delete m_priv;
}
#endif
