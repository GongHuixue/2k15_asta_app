#ifndef HSVEUINS_MITASORT
#define HSVEUINS_MITASORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mitasort.h"
#include "CHsvEuropeInstallation_mitasort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mitasort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mitasort_Priv::~CHsvEuropeInstallation_mitasort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mitasort::CHsvEuropeInstallation_mitasort()
{
 m_priv = new CHsvEuropeInstallation_mitasort_Priv();
iconfN	= m_priv->iconfN;
iitapow	= m_priv->iitapow;
itasort	= m_priv->itasort;
m_priv->apperr	=apperr;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->freqctl	=freqctl;
m_priv->hsvdvbtins_dvbset	=hsvdvbtins_dvbset;
m_priv->iadvpgitr	=iadvpgitr;
m_priv->iconf	=iconf;
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
CHsvEuropeInstallation_mitasort::~CHsvEuropeInstallation_mitasort()
{
 delete m_priv;
}
#endif
