#ifndef HSVEUINS_MNORSORT
#define HSVEUINS_MNORSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mnorsort.h"
#include "CHsvEuropeInstallation_mnorsort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mnorsort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mnorsort_Priv::~CHsvEuropeInstallation_mnorsort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mnorsort::CHsvEuropeInstallation_mnorsort()
{
 m_priv = new CHsvEuropeInstallation_mnorsort_Priv();
inorpow	= m_priv->inorpow;
inorsort	= m_priv->inorsort;
m_priv->apperr	=apperr;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->freqctl	=freqctl;
m_priv->hsvdvbtins_dvbset	=hsvdvbtins_dvbset;
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
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
m_priv->hsvprins_prins = hsvprins_prins;
}
CHsvEuropeInstallation_mnorsort::~CHsvEuropeInstallation_mnorsort()
{
 delete m_priv;
}
#endif
