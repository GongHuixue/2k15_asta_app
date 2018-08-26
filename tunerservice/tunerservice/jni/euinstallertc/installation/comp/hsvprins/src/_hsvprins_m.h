#ifndef HSVPRINS_M
#define HSVPRINS_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvPresetInstallation_m.h"
#include "CHsvPresetInstallation_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvPresetInstallation_m_Priv::params__init(void)
{
}
CHsvPresetInstallation_m_Priv::~CHsvPresetInstallation_m_Priv()
{
}
//public class connections
CHsvPresetInstallation_m::CHsvPresetInstallation_m()
{
 m_priv = new CHsvPresetInstallation_m_Priv();
colN	= m_priv->colN;
feapiN	= m_priv->feapiN;
implins	= m_priv->implins;
pacidsN	= m_priv->pacidsN;
pgaciN	= m_priv->pgaciN;
pow	= m_priv->pow;
prins	= m_priv->prins;
resetN	= m_priv->resetN;
m_priv->chanlibret	=chanlibret;
m_priv->chlname	=chlname;
m_priv->cids	=cids;
m_priv->cniname	=cniname;
m_priv->col	=col;
m_priv->div	=div;
m_priv->err	=err;
m_priv->euconfig	=euconfig;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->freqctl	=freqctl;
m_priv->implinsN	=implinsN;
m_priv->instutil	=instutil;
m_priv->log	=log;
m_priv->mem	=mem;
m_priv->memo	=memo;
m_priv->p830	=p830;
m_priv->pen	=pen;
m_priv->pgaci	=pgaci;
m_priv->pgdat	=pgdat;
m_priv->pgdatcni	=pgdatcni;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->prinsN	=prinsN;
m_priv->prsort	=prsort;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->sort	=sort;
m_priv->str	=str;
m_priv->sysctl	=sysctl;
m_priv->sysset	=sysset;
m_priv->txtpre	=txtpre;
m_priv->vps	=vps;
m_priv->wnddest	=wnddest;
}
CHsvPresetInstallation_m::~CHsvPresetInstallation_m()
{
 delete m_priv;
}
#endif
