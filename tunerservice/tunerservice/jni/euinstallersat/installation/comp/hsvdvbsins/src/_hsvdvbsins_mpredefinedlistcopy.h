#ifndef HSVDVBSINS_MPREDEFINEDLISTCOPY
#define HSVDVBSINS_MPREDEFINEDLISTCOPY

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mpredefinedlistcopy.h"
#include "CHsvDvbsInstallation_mpredefinedlistcopy_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mpredefinedlistcopy_Priv::~CHsvDvbsInstallation_mpredefinedlistcopy_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mpredefinedlistcopy::CHsvDvbsInstallation_mpredefinedlistcopy()
{
 m_priv = new CHsvDvbsInstallation_mpredefinedlistcopy_Priv();
ipredefcopy	= m_priv->ipredefcopy;
ipredefpow	= m_priv->ipredefpow;
recdevN	= m_priv->recdevN;
usbdevexN	= m_priv->usbdevexN;
m_priv->err	=err;
m_priv->iinsN	=iinsN;
m_priv->pen	=pen;
m_priv->pmp	=pmp;
m_priv->recdev	=recdev;
m_priv->tprtk	=tprtk;
m_priv->usbms	=usbms;
m_priv->wnddest	=wnddest;
}
CHsvDvbsInstallation_mpredefinedlistcopy::~CHsvDvbsInstallation_mpredefinedlistcopy()
{
 delete m_priv;
}
#endif
