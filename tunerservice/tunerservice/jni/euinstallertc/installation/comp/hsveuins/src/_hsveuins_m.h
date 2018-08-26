#ifndef HSVEUINS_M
#define HSVEUINS_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_m.h"
#include "CHsvEuropeInstallation_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_m_Priv::params__init(void)
{
}
CHsvEuropeInstallation_m_Priv::~CHsvEuropeInstallation_m_Priv()
{
}
//public class connections
CHsvEuropeInstallation_m::CHsvEuropeInstallation_m()
{
 m_priv = new CHsvEuropeInstallation_m_Priv();
acidat	= m_priv->acidat;
colN	= m_priv->colN;
ctrlN	= m_priv->ctrlN;
divsupp	= m_priv->divsupp;
feapiN	= m_priv->feapiN;
hsvdvbcamins_insN	= m_priv->hsvdvbcamins_insN;
hsvdvbcins_insN	= m_priv->hsvdvbcins_insN;
hsvdvbtins_insN	= m_priv->hsvdvbtins_insN;
hsvdvbtmpegins_digscanN	= m_priv->hsvdvbtmpegins_digscanN;
hsvdvbtmpegins_insN	= m_priv->hsvdvbtmpegins_insN;
hsvprins_prinsN	= m_priv->hsvprins_prinsN;
hsvziggoins_insN	= m_priv->hsvziggoins_insN;
hsvcanaldigitalins_insN	= m_priv->hsvcanaldigitalins_insN;
iafscanN	= m_priv->iafscanN;
ictrlN	= m_priv->ictrlN;
implins	= m_priv->implins;
impow	= m_priv->impow;
instla	= m_priv->instla;
ipgaciN	= m_priv->ipgaciN;
isyssetN	= m_priv->isyssetN;
pacidsN	= m_priv->pacidsN;
pins	= m_priv->pins;
resetN	= m_priv->resetN;
sortN	= m_priv->sortN;
srcstpN	= m_priv->srcstpN;
strapiN	= m_priv->strapiN;
m_priv->apsysset	=apsysset;
m_priv->cctrlN	=cctrlN;
m_priv->cids	=cids;
m_priv->cstrapiN	=cstrapiN;
m_priv->div	=div;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->freqctl	=freqctl;
m_priv->hsvdvbcamins_dataacq	=hsvdvbcamins_dataacq;
m_priv->hsvdvbcamins_dvbset	=hsvdvbcamins_dvbset;
m_priv->hsvdvbcamins_ena	=hsvdvbcamins_ena;
m_priv->hsvdvbcamins_feapiN	=hsvdvbcamins_feapiN;
m_priv->hsvdvbcamins_ins	=hsvdvbcamins_ins;
m_priv->hsvdvbcamins_strapiN	=hsvdvbcamins_strapiN;
m_priv->hsvdvbcins_digacq	=hsvdvbcins_digacq;
m_priv->hsvdvbcins_dvbset	=hsvdvbcins_dvbset;
m_priv->hsvdvbcins_ena	=hsvdvbcins_ena;
m_priv->hsvdvbcins_feapiN	=hsvdvbcins_feapiN;
m_priv->hsvdvbcins_ins	=hsvdvbcins_ins;
m_priv->hsvdvbcins_syssetN	=hsvdvbcins_syssetN;
m_priv->hsvdvbtins_afitr	=hsvdvbtins_afitr;
m_priv->hsvdvbtins_cntryinsN	=hsvdvbtins_cntryinsN;
m_priv->hsvdvbtins_digacq	=hsvdvbtins_digacq;
m_priv->hsvdvbtins_dvbset	=hsvdvbtins_dvbset;
m_priv->hsvdvbtins_dvbt	=hsvdvbtins_dvbt;
m_priv->hsvdvbtins_ena	=hsvdvbtins_ena;
m_priv->hsvdvbtins_feapiN	=hsvdvbtins_feapiN;
m_priv->hsvdvbtins_syssetN	=hsvdvbtins_syssetN;
m_priv->hsvdvbtins_bcksyssetN	=hsvdvbtins_bcksyssetN;
m_priv->hsvdvbtmpegins_digacq	=hsvdvbtmpegins_digacq;
m_priv->hsvdvbtmpegins_digscan	=hsvdvbtmpegins_digscan;
m_priv->hsvdvbtmpegins_ena	=hsvdvbtmpegins_ena;
m_priv->hsvdvbtmpegins_feapiN	=hsvdvbtmpegins_feapiN;
m_priv->hsvprins_acidat	=hsvprins_acidat;
m_priv->hsvprins_anaset	=hsvprins_anaset;
m_priv->hsvprins_colN	=hsvprins_colN;
m_priv->hsvprins_feapiN	=hsvprins_feapiN;
m_priv->hsvprins_implins	=hsvprins_implins;
m_priv->hsvprins_pacidsN	=hsvprins_pacidsN;
m_priv->hsvprins_pgaciN	=hsvprins_pgaciN;
m_priv->hsvprins_pow	=hsvprins_pow;
m_priv->hsvprins_prins	=hsvprins_prins;
m_priv->hsvprins_resetN	=hsvprins_resetN;
m_priv->hsvziggoins_ctrlN	=hsvziggoins_ctrlN;
m_priv->hsvziggoins_dataacq	=hsvziggoins_dataacq;
m_priv->hsvziggoins_ena	=hsvziggoins_ena;
m_priv->hsvziggoins_feapiN	=hsvziggoins_feapiN;
m_priv->hsvziggoins_ins	=hsvziggoins_ins;
m_priv->hsvziggoins_sortN	=hsvziggoins_sortN;
m_priv->hsvziggoins_strapiN	=hsvziggoins_strapiN;
m_priv->hsvcanaldigitalins_ctrlN	=hsvcanaldigitalins_ctrlN;
m_priv->hsvcanaldigitalins_dataacq	=hsvcanaldigitalins_dataacq;
m_priv->hsvcanaldigitalins_ena	=hsvcanaldigitalins_ena;
m_priv->hsvcanaldigitalins_feapiN	=hsvcanaldigitalins_feapiN;
m_priv->hsvcanaldigitalins_ins	=hsvcanaldigitalins_ins;
m_priv->hsvcanaldigitalins_sortN	=hsvcanaldigitalins_sortN;
m_priv->hsvcanaldigitalins_strapiN	=hsvcanaldigitalins_strapiN;
m_priv->icamsort	=icamsort;
m_priv->iconf	=iconf;
m_priv->idbookconf	=idbookconf;
m_priv->insN	=insN;
m_priv->pginsN	=pginsN;
m_priv->instlaN	=instlaN;
m_priv->instutil	=instutil;
m_priv->isort	=isort;
m_priv->isortroute	=isortroute;
m_priv->log	=log;
m_priv->mctl	=mctl;
m_priv->mpegstrapiN	=mpegstrapiN;
m_priv->pen	=pen;
m_priv->pgctl	=pgctl;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->plfdesigid	=plfdesigid;
m_priv->plferrids	=plferrids;
m_priv->plfsrcid	=plfsrcid;
m_priv->pmp	=pmp;
m_priv->powctlx	=powctlx;
m_priv->rins	=rins;
m_priv->rtk	=rtk;
m_priv->sigstr	=sigstr;
m_priv->srcstp	=srcstp;
m_priv->strapi	=strapi;
m_priv->sysctl	=sysctl;
m_priv->sysset	=sysset;
m_priv->syssetx	=syssetx;
m_priv->tctrlN	=tctrlN;
m_priv->tstrapiN	=tstrapiN;
m_priv->wnddest	=wnddest;
m_priv->ctrl = ctrl;
m_priv->plfvbi = plfvbi;
m_priv->dcu = dcu;
m_priv->plfproxy = plfproxy;
plfProxyN = m_priv->plfProxyN;
}
CHsvEuropeInstallation_m::~CHsvEuropeInstallation_m()
{
 delete m_priv;
}
#endif
