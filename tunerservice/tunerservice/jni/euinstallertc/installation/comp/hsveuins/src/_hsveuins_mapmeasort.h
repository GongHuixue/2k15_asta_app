#ifndef HSVEUINS_MAPMEASORT
#define HSVEUINS_MAPMEASORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mapmeasort.h"
#include "CHsvEuropeInstallation_mapmeasort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mapmeasort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mapmeasort_Priv::~CHsvEuropeInstallation_mapmeasort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mapmeasort::CHsvEuropeInstallation_mapmeasort()
{
 m_priv = new CHsvEuropeInstallation_mapmeasort_Priv();
idvbtapmeasort	= m_priv->idvbtapmeasort;
idvbtapmeasortpow	= m_priv->idvbtapmeasortpow;
m_priv->apperr	=apperr;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->divsupp	=divsupp;
m_priv->eurdiv	=eurdiv;
m_priv->freqctl	=freqctl;
m_priv->hsvdvbtins_inscountry	=hsvdvbtins_inscountry;
m_priv->iadvpgitr	=iadvpgitr;
m_priv->memo	=memo;
m_priv->nvmapps	=nvmapps;
m_priv->nvmcesvc	=nvmcesvc;
m_priv->nvmtxt	=nvmtxt;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sortN	=sortN;
m_priv->sysset	=sysset;
m_priv->hsvprins_prins = hsvprins_prins;
}
CHsvEuropeInstallation_mapmeasort::~CHsvEuropeInstallation_mapmeasort()
{
 delete m_priv;
}
#endif
