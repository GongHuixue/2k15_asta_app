#ifndef HSVSATFE_MSILABS
#define HSVSATFE_MSILABS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvSatelliteFrontEnd_msilabs.h"
#include "CHsvSatelliteFrontEnd_msilabs_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvSatelliteFrontEnd_msilabs_Priv::params__init(void)
{
}
CHsvSatelliteFrontEnd_msilabs_Priv::~CHsvSatelliteFrontEnd_msilabs_Priv()
{
}
//public class connections
CHsvSatelliteFrontEnd_msilabs::CHsvSatelliteFrontEnd_msilabs()
{
 m_priv = new CHsvSatelliteFrontEnd_msilabs_Priv();
plfapidvbsN	= m_priv->plfapidvbsN;
sipow	= m_priv->sipow;
sisatfrontend	= m_priv->sisatfrontend;
m_priv->err	=err;
m_priv->hsvsatsettings	=hsvsatsettings;
m_priv->pen	=pen;
m_priv->plfdvbs	=plfdvbs;
m_priv->plftune	=plftune;
m_priv->pmp	=pmp;
m_priv->satfrontendNotify	=satfrontendNotify;
m_priv->tprtk	=tprtk;
m_priv->wnddest	=wnddest;
}
CHsvSatelliteFrontEnd_msilabs::~CHsvSatelliteFrontEnd_msilabs()
{
 delete m_priv;
}
#endif
