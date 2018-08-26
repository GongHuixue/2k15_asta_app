#ifndef HSVEUINS_MDBOOKSORT
#define HSVEUINS_MDBOOKSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mDbookSort.h"
#include "CHsvEuropeInstallation_mDbookSort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mDbookSort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mDbookSort_Priv::~CHsvEuropeInstallation_mDbookSort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mDbookSort::CHsvEuropeInstallation_mDbookSort()
{
 m_priv = new CHsvEuropeInstallation_mDbookSort_Priv();
idbookconfN	= m_priv->idbookconfN;
idbooksort	= m_priv->idbooksort;
idbooksortpow	= m_priv->idbooksortpow;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->divsupp	=divsupp;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->freqctl	=freqctl;
m_priv->hsvdvbtins_inscountry	=hsvdvbtins_inscountry;
m_priv->iadvpgitr	=iadvpgitr;
m_priv->idbookconf	=idbookconf;
m_priv->instutil	=instutil;
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
m_priv->wnddest	=wnddest;
m_priv->hsvprins_prins = hsvprins_prins;
m_priv->hsvdvbtins_dvbset = hsvdvbtins_dvbset;;
}
CHsvEuropeInstallation_mDbookSort::~CHsvEuropeInstallation_mDbookSort()
{
 delete m_priv;
}
#endif
