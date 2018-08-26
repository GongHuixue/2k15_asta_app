#ifndef HSVDVBTINS_MCOUNTRY
#define HSVDVBTINS_MCOUNTRY

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mcountry.h"
#include "CHsvDvbTInstallation_mcountry_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mcountry_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mcountry_Priv::~CHsvDvbTInstallation_mcountry_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mcountry::CHsvDvbTInstallation_mcountry()
{
 m_priv = new CHsvDvbTInstallation_mcountry_Priv();
afitr	= m_priv->afitr;
cntryinsN	= m_priv->cntryinsN;
freqlistconf	= m_priv->freqlistconf;
icctrlN	= m_priv->icctrlN;
icntrypow	= m_priv->icntrypow;
icntrystrapiN	= m_priv->icntrystrapiN;
inscountry	= m_priv->inscountry;
langids	= m_priv->langids;
m_priv->afscanN	=afscanN;
m_priv->cdvbset	=cdvbset;
m_priv->cids	=cids;
m_priv->eurdiv	=eurdiv;
m_priv->ffsdir	=ffsdir;
m_priv->insN	=insN;
m_priv->rins	=rins;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->str	=str;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
}
CHsvDvbTInstallation_mcountry::~CHsvDvbTInstallation_mcountry()
{
 delete m_priv;
}
#endif
