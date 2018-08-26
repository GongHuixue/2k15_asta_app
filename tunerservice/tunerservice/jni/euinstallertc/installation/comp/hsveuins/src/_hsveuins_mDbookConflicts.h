#ifndef HSVEUINS_MDBOOKCONFLICTS
#define HSVEUINS_MDBOOKCONFLICTS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mDbookConflicts.h"
#include "CHsvEuropeInstallation_mDbookConflicts_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mDbookConflicts_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mDbookConflicts_Priv::~CHsvEuropeInstallation_mDbookConflicts_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mDbookConflicts::CHsvEuropeInstallation_mDbookConflicts()
{
 m_priv = new CHsvEuropeInstallation_mDbookConflicts_Priv();
idbookconf	= m_priv->idbookconf;
idbookconpow	= m_priv->idbookconpow;
m_priv->cids	=cids;
m_priv->hpool	=hpool;
m_priv->hsvdvbtins_digacq	=hsvdvbtins_digacq;
m_priv->hsvdvbtins_dvbset	=hsvdvbtins_dvbset;
m_priv->idbookconfN	=idbookconfN;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sysset	=sysset;
}
CHsvEuropeInstallation_mDbookConflicts::~CHsvEuropeInstallation_mDbookConflicts()
{
 delete m_priv;
}
#endif
