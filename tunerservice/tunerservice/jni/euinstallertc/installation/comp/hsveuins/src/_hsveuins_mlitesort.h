#ifndef HSVEUINS_MLITESORT
#define HSVEUINS_MLITESORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mlitesort.h"
#include "CHsvEuropeInstallation_mlitesort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mlitesort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mlitesort_Priv::~CHsvEuropeInstallation_mlitesort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mlitesort::CHsvEuropeInstallation_mlitesort()
{
 m_priv = new CHsvEuropeInstallation_mlitesort_Priv();
idvbclitesort	= m_priv->idvbclitesort;
ilitepow	= m_priv->ilitepow;
m_priv->apperr	=apperr;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->ffsdir	=ffsdir;
m_priv->freqctl	=freqctl;
m_priv->iadvpgitr	=iadvpgitr;
m_priv->instutil	=instutil;
m_priv->log	=log;
m_priv->nvmapps	=nvmapps;
m_priv->nvmcesvc	=nvmcesvc;
m_priv->nvmtxt	=nvmtxt;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pgitr	=pgitr;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sortN	=sortN;
m_priv->str	=str;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
m_priv->hsvprins_prins = hsvprins_prins;
}
CHsvEuropeInstallation_mlitesort::~CHsvEuropeInstallation_mlitesort()
{
 delete m_priv;
}
#endif
