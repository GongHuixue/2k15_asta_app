#ifndef HSVDVBTINS_MDATAACQ
#define HSVDVBTINS_MDATAACQ

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTInstallation_mDataAcq.h"
#include "CHsvDvbTInstallation_mDataAcq_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTInstallation_mDataAcq_Priv::params__init(void)
{
}
CHsvDvbTInstallation_mDataAcq_Priv::~CHsvDvbTInstallation_mDataAcq_Priv()
{
}
//public class connections
CHsvDvbTInstallation_mDataAcq::CHsvDvbTInstallation_mDataAcq()
{
 m_priv = new CHsvDvbTInstallation_mDataAcq_Priv();
digscanN	= m_priv->digscanN;
idataacq	= m_priv->idataacq;
idatapow	= m_priv->idatapow;
idvbtqctrlN	= m_priv->idvbtqctrlN;
m_priv->Timerclk	=Timerclk;
m_priv->chdecdvbt2	=chdecdvbt2;
m_priv->cids	=cids;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->hpool	=hpool;
m_priv->idvbset	=idvbset;
m_priv->idvbt	=idvbt;
m_priv->instutil	=instutil;
m_priv->langids	=langids;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->sort	=sort;
m_priv->sortN	=sortN;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvDvbTInstallation_mDataAcq::~CHsvDvbTInstallation_mDataAcq()
{
 delete m_priv;
}
#endif
