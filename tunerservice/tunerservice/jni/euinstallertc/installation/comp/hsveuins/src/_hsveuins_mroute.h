#ifndef HSVEUINS_MROUTE
#define HSVEUINS_MROUTE

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mroute.h"
#include "CHsvEuropeInstallation_mroute_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mroute_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mroute_Priv::~CHsvEuropeInstallation_mroute_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mroute::CHsvEuropeInstallation_mroute()
{
 m_priv = new CHsvEuropeInstallation_mroute_Priv();
isort	= m_priv->isort;
m_priv->idbooksort	=idbooksort;
m_priv->idvbclitesort	=idvbclitesort;
m_priv->idvbcsort	=idvbcsort;
m_priv->idvbtlitesort	=idvbtlitesort;
m_priv->idvbtsort	=idvbtsort;
m_priv->ifinsort	=ifinsort;
m_priv->inorsort	=inorsort;
m_priv->isortroute	=isortroute;
m_priv->istubsort	=istubsort;
m_priv->itasort	=itasort;
m_priv->idvbtapmeasort	=idvbtapmeasort;
m_priv->idvbthungarysort	=idvbthungarysort;
m_priv->iblizoosort	=iblizoosort;
}
CHsvEuropeInstallation_mroute::~CHsvEuropeInstallation_mroute()
{
 delete m_priv;
}
#endif
