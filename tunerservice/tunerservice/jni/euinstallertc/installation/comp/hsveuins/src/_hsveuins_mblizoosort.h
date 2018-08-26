#ifndef HSVEUINS_MBLIZOOSORT
#define HSVEUINS_MBLIZOOSORT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mblizoosort.h"
#include "CHsvEuropeInstallation_mblizoosort_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mblizoosort_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mblizoosort_Priv::~CHsvEuropeInstallation_mblizoosort_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mblizoosort::CHsvEuropeInstallation_mblizoosort()
{
 m_priv = new CHsvEuropeInstallation_mblizoosort_Priv();
iblizoopow	= m_priv->iblizoopow;
iblizoosort	= m_priv->iblizoosort;
//m_priv->apperr	=apperr;
m_priv->cids	=cids;
m_priv->div	=div;
//m_priv->divsupp	=divsupp;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
//m_priv->ffsdir	=ffsdir;
//m_priv->hsvdvbcins_digacq	=hsvdvbcins_digacq;
m_priv->hsvdvbcins_dvbset	=hsvdvbcins_dvbset;
//m_priv->iadvpgitr	=iadvpgitr;
//m_priv->memo	=memo;
//m_priv->nvmapps	=nvmapps;
//m_priv->nvmcesvc	=nvmcesvc;
//m_priv->nvmtxt	=nvmtxt;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->rtk	=rtk;
m_priv->sortN	=sortN;
m_priv->str	=str;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
m_priv->hsvprins_prins = hsvprins_prins;
}
CHsvEuropeInstallation_mblizoosort::~CHsvEuropeInstallation_mblizoosort()
{
 delete m_priv;
}
#endif
