#ifndef HSVEUINS_MCONFLICTS
#define HSVEUINS_MCONFLICTS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mconflicts.h"
#include "CHsvEuropeInstallation_mconflicts_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mconflicts_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mconflicts_Priv::~CHsvEuropeInstallation_mconflicts_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mconflicts::CHsvEuropeInstallation_mconflicts()
{
 m_priv = new CHsvEuropeInstallation_mconflicts_Priv();
iconf	= m_priv->iconf;
iconpow	= m_priv->iconpow;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->iconfN	=iconfN;
m_priv->insN	=insN;
m_priv->memo	=memo;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sysset	=sysset;
}
CHsvEuropeInstallation_mconflicts::~CHsvEuropeInstallation_mconflicts()
{
 delete m_priv;
}
#endif
