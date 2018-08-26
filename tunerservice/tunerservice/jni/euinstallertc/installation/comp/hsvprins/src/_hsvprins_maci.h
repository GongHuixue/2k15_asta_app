#ifndef HSVPRINS_MACI
#define HSVPRINS_MACI

#define GENERATE__LEGACY__DEFINES

#include "../CHsvPresetInstallation_maci.h"
#include "CHsvPresetInstallation_maci_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvPresetInstallation_maci_Priv::params__init(void)
{
}
CHsvPresetInstallation_maci_Priv::~CHsvPresetInstallation_maci_Priv()
{
}
//public class connections
CHsvPresetInstallation_maci::CHsvPresetInstallation_maci()
{
 m_priv = new CHsvPresetInstallation_maci_Priv();
acidat	= m_priv->acidat;
m_priv->cids	=cids;
m_priv->col	=col;
m_priv->div	=div;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->instutil	=instutil;
m_priv->lngids	=lngids;
m_priv->memo	=memo;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->rins	=rins;
m_priv->sort	=sort;
m_priv->sysset	=sysset;
}
CHsvPresetInstallation_maci::~CHsvPresetInstallation_maci()
{
 delete m_priv;
}
#endif
