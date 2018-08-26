#ifndef HSVDVBTMPEGINS_M
#define HSVDVBTMPEGINS_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbtMpegInstallation_m.h"
#include "CHsvDvbtMpegInstallation_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbtMpegInstallation_m_Priv::params__init(void)
{
}
CHsvDvbtMpegInstallation_m_Priv::~CHsvDvbtMpegInstallation_m_Priv()
{
}
//public class connections
CHsvDvbtMpegInstallation_m::CHsvDvbtMpegInstallation_m()
{
 m_priv = new CHsvDvbtMpegInstallation_m_Priv();
ctrlN	= m_priv->ctrlN;
ena	= m_priv->ena;
feapiN	= m_priv->feapiN;
idigscan	= m_priv->idigscan;
pow	= m_priv->pow;
strapiN	= m_priv->strapiN;
m_priv->ctrl	=ctrl;
m_priv->digscanN	=digscanN;
m_priv->div	=div;
m_priv->err	=err;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->freqctl	=freqctl;
m_priv->idigacq	=idigacq;
m_priv->insN	=insN;
m_priv->instutil	=instutil;
m_priv->log	=log;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->sort	=sort;
m_priv->strapi	=strapi;
m_priv->strmfltr	=strmfltr;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvDvbtMpegInstallation_m::~CHsvDvbtMpegInstallation_m()
{
 delete m_priv;
}
#endif
