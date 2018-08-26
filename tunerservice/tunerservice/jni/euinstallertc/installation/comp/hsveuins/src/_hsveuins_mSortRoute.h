#ifndef HSVEUINS_MSORTROUTE
#define HSVEUINS_MSORTROUTE

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mSortRoute.h"
#include "CHsvEuropeInstallation_mSortRoute_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mSortRoute_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mSortRoute_Priv::~CHsvEuropeInstallation_mSortRoute_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mSortRoute::CHsvEuropeInstallation_mSortRoute()
{
 m_priv = new CHsvEuropeInstallation_mSortRoute_Priv();
isortroute	= m_priv->isortroute;
istubsort	= m_priv->istubsort;
m_priv->cids	=cids;
m_priv->eurdiv	=eurdiv;
m_priv->idbooksort	=idbooksort;
m_priv->idvbclitesort	=idvbclitesort;
m_priv->idvbcsort	=idvbcsort;
m_priv->idvbtlitesort	=idvbtlitesort;
m_priv->idvbtsort	=idvbtsort;
m_priv->ifinsort	=ifinsort;
m_priv->inorsort	=inorsort;
m_priv->itasort	=itasort;
m_priv->rins	=rins;
m_priv->sysset	=sysset;
m_priv->idvbtapmeasort	=idvbtapmeasort;
m_priv->idvbthungarysort	=idvbthungarysort;
m_priv->iblizoosort = iblizoosort;
}
CHsvEuropeInstallation_mSortRoute::~CHsvEuropeInstallation_mSortRoute()
{
 delete m_priv;
}
#endif
