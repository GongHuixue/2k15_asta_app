#ifndef HSVEUINS_MCAMSORT
#define HSVEUINS_MCAMSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mcamsort.h"
#include "CHsvEuropeInstallation_mcamsort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mcamsort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mcamsort_Priv::~CHsvEuropeInstallation_mcamsort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mcamsort::CHsvEuropeInstallation_mcamsort()
{
 m_priv = new CHsvEuropeInstallation_mcamsort_Priv();
icamsort	= m_priv->icamsort;
icamsortpow	= m_priv->icamsortpow;
m_priv->nvmapps	=nvmapps;
m_priv->nvmcesvc	=nvmcesvc;
m_priv->nvmtxt	=nvmtxt;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->sortN	=sortN;
}
CHsvEuropeInstallation_mcamsort::~CHsvEuropeInstallation_mcamsort()
{
 delete m_priv;
}
#endif
