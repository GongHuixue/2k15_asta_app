#ifndef HSVEUINS_MADVPGITR
#define HSVEUINS_MADVPGITR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_madvpgitr.h"
#include "CHsvEuropeInstallation_madvpgitr_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_madvpgitr_Priv::params__init(void)
{
}
CHsvEuropeInstallation_madvpgitr_Priv::~CHsvEuropeInstallation_madvpgitr_Priv()
{
}
//public class connections
CHsvEuropeInstallation_madvpgitr::CHsvEuropeInstallation_madvpgitr()
{
 m_priv = new CHsvEuropeInstallation_madvpgitr_Priv();
iadvpgitr	= m_priv->iadvpgitr;
m_priv->apperr	=apperr;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pgitr	=pgitr;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
}
CHsvEuropeInstallation_madvpgitr::~CHsvEuropeInstallation_madvpgitr()
{
 delete m_priv;
}
#endif
