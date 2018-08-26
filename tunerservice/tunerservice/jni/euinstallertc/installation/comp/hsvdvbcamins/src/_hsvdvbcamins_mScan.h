#ifndef HSVDVBCAMINS_MSCAN
#define HSVDVBCAMINS_MSCAN

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCamInstallation_mScan.h"
#include "CHsvDvbCamInstallation_mScan_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCamInstallation_mScan_Priv::params__init(void)
{
}
CHsvDvbCamInstallation_mScan_Priv::~CHsvDvbCamInstallation_mScan_Priv()
{
}
//public class connections
CHsvDvbCamInstallation_mScan::CHsvDvbCamInstallation_mScan()
{
 m_priv = new CHsvDvbCamInstallation_mScan_Priv();
ena	= m_priv->ena;
feapiN	= m_priv->feapiN;
icamhelper	= m_priv->icamhelper;
iins	= m_priv->iins;
opinsN	= m_priv->opinsN;
pow	= m_priv->pow;
strapiN	= m_priv->strapiN;
m_priv->camScanparser	=camScanparser;
m_priv->camacqhelper	=camacqhelper;
m_priv->camena	=camena;
m_priv->chdecdvbt2	=chdecdvbt2;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->hsverr	=hsverr;
m_priv->idataacq	=idataacq;
m_priv->insN	=insN;
m_priv->mctl	=mctl;
m_priv->opins	=opins;
m_priv->pen	=pen;
m_priv->plferrids	=plferrids;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sigstr	=sigstr;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
m_priv->idvbset = idvbset;
m_priv->isetpow = isetpow;
}
CHsvDvbCamInstallation_mScan::~CHsvDvbCamInstallation_mScan()
{
 delete m_priv;
}
#endif
