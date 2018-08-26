#ifndef HSVDVBSINS_MREMOVESAT
#define HSVDVBSINS_MREMOVESAT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mremovesat.h"
#include "CHsvDvbsInstallation_mremovesat_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mremovesat_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mremovesat_Priv::~CHsvDvbsInstallation_mremovesat_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mremovesat::CHsvDvbsInstallation_mremovesat()
{
 m_priv = new CHsvDvbsInstallation_mremovesat_Priv();
iaddremove	= m_priv->iaddremove;
iremovesatpow	= m_priv->iremovesatpow;
m_priv->err	=err;
m_priv->idvbset	=idvbset;
m_priv->iinsN	=iinsN;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pins	=pins;
m_priv->pmp	=pmp;
}
CHsvDvbsInstallation_mremovesat::~CHsvDvbsInstallation_mremovesat()
{
 delete m_priv;
}
#endif
