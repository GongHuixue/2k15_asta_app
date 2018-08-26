#ifndef HSVEUINS_MPEGSORT
#define HSVEUINS_MPEGSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mpegsort.h"
#include "CHsvEuropeInstallation_mpegsort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mpegsort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mpegsort_Priv::~CHsvEuropeInstallation_mpegsort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mpegsort::CHsvEuropeInstallation_mpegsort()
{
 m_priv = new CHsvEuropeInstallation_mpegsort_Priv();
idvbtlitesort	= m_priv->idvbtlitesort;
impegpow	= m_priv->impegpow;
m_priv->apperr	=apperr;
m_priv->div	=div;
m_priv->eurdiv	=eurdiv;
m_priv->freqctl	=freqctl;
m_priv->iadvpgitr	=iadvpgitr;
m_priv->instutil	=instutil;
m_priv->log	=log;
m_priv->nvmapps	=nvmapps;
m_priv->nvmcesvc	=nvmcesvc;
m_priv->nvmtxt	=nvmtxt;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sortN	=sortN;
m_priv->hsvprins_prins = hsvprins_prins;
}
CHsvEuropeInstallation_mpegsort::~CHsvEuropeInstallation_mpegsort()
{
 delete m_priv;
}
#endif
