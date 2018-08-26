#ifndef HSVDVBTMPEGINS_MDIGACQ
#define HSVDVBTMPEGINS_MDIGACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbtMpegInstallation_mdigacq.h"
#include "CHsvDvbtMpegInstallation_mdigacq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbtMpegInstallation_mdigacq_Priv::params__init(void)
{
}
CHsvDvbtMpegInstallation_mdigacq_Priv::~CHsvDvbtMpegInstallation_mdigacq_Priv()
{
}
//public class connections
CHsvDvbtMpegInstallation_mdigacq::CHsvDvbtMpegInstallation_mdigacq()
{
 m_priv = new CHsvDvbtMpegInstallation_mdigacq_Priv();
idigacq	= m_priv->idigacq;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->divsupp	=divsupp;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->idigscan	=idigscan;
m_priv->instutil	=instutil;
m_priv->log	=log;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->sort	=sort;
m_priv->srtdb	=srtdb;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
}
CHsvDvbtMpegInstallation_mdigacq::~CHsvDvbtMpegInstallation_mdigacq()
{
 delete m_priv;
}
#endif
