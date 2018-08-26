#ifndef HSVCANALDIGITAL_MBACKGROUND
#define HSVCANALDIGITAL_MBACKGROUND

#define GENERATE__LEGACY__DEFINES

#include "../CHsvCanalDigitalInstallation_mBackground.h"
#include "CHsvCanalDigitalInstallation_mBackground_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvCanalDigitalInstallation_mBackground_Priv::params__init(void)
{
}
CHsvCanalDigitalInstallation_mBackground_Priv::~CHsvCanalDigitalInstallation_mBackground_Priv()
{
}
//public class connections
CHsvCanalDigitalInstallation_mBackground::CHsvCanalDigitalInstallation_mBackground()
{
 m_priv = new CHsvCanalDigitalInstallation_mBackground_Priv();
ena	= m_priv->ena;
ibckg	= m_priv->ibckg;
ibckgctrlN	= m_priv->ibckgctrlN;
ibckgpow	= m_priv->ibckgpow;
sortN	= m_priv->sortN;
strapiN	= m_priv->strapiN;
m_priv->chanret	=chanret;
m_priv->dvbset	=dvbset;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->idataacq	=idataacq;
m_priv->insN	=insN;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pgsel	=pgsel;
m_priv->plfres	=plfres;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
m_priv->rtk	=rtk;
m_priv->sigstr	=sigstr;
m_priv->sort	=sort;
m_priv->strapi	=strapi;
m_priv->wnddest	=wnddest;
m_priv->idatastrapiN = idatastrapiN;
}
CHsvCanalDigitalInstallation_mBackground::~CHsvCanalDigitalInstallation_mBackground()
{
 delete m_priv;
}
#endif
