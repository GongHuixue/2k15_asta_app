#ifndef HSVDVBCAMINS_MDATAACQ
#define HSVDVBCAMINS_MDATAACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCamInstallation_mDataAcq.h"
#include "CHsvDvbCamInstallation_mDataAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCamInstallation_mDataAcq_Priv::params__init(void)
{
}
CHsvDvbCamInstallation_mDataAcq_Priv::~CHsvDvbCamInstallation_mDataAcq_Priv()
{
}
//public class connections
CHsvDvbCamInstallation_mDataAcq::CHsvDvbCamInstallation_mDataAcq()
{
 m_priv = new CHsvDvbCamInstallation_mDataAcq_Priv();
idataacq	= m_priv->idataacq;
m_priv->Timerclk	=Timerclk;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->icamhelper	=icamhelper;
m_priv->iins	=iins;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->rins	=rins;
m_priv->sort	=sort;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
m_priv->ling	=ling;
m_priv->idvbset = idvbset;
m_priv->charsetutil = charsetutil;
pcamhelper = m_priv->pcamhelper;
}
CHsvDvbCamInstallation_mDataAcq::~CHsvDvbCamInstallation_mDataAcq()
{
 delete m_priv;
}
#endif
