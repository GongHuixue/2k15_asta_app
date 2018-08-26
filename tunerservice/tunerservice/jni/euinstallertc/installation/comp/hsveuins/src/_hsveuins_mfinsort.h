#ifndef HSVEUINS_MFINSORT
#define HSVEUINS_MFINSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mfinsort.h"
#include "CHsvEuropeInstallation_mfinsort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mfinsort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mfinsort_Priv::~CHsvEuropeInstallation_mfinsort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mfinsort::CHsvEuropeInstallation_mfinsort()
{
 m_priv = new CHsvEuropeInstallation_mfinsort_Priv();
ifinsort	= m_priv->ifinsort;
ifinsortpow	= m_priv->ifinsortpow;
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
CHsvEuropeInstallation_mfinsort::~CHsvEuropeInstallation_mfinsort()
{
 delete m_priv;
}
#endif
