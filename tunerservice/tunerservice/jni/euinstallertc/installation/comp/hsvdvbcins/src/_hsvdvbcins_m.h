#ifndef HSVDVBCINS_M
#define HSVDVBCINS_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCInstallation_m.h"
#include "CHsvDvbCInstallation_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCInstallation_m_Priv::params__init(void)
{
}
CHsvDvbCInstallation_m_Priv::~CHsvDvbCInstallation_m_Priv()
{
}
//public class connections
CHsvDvbCInstallation_m::CHsvDvbCInstallation_m()
{
 m_priv = new CHsvDvbCInstallation_m_Priv();
ctrlN	= m_priv->ctrlN;
ena	= m_priv->ena;
feapiN	= m_priv->feapiN;
ifullN	= m_priv->ifullN;
igridN	= m_priv->igridN;
ins	= m_priv->ins;
iprescanN	= m_priv->iprescanN;
iquickN	= m_priv->iquickN;
pow	= m_priv->pow;
strapiN	= m_priv->strapiN;
m_priv->eurdiv	=eurdiv;
m_priv->hsverr	=hsverr;
m_priv->iacqpow	=iacqpow;
m_priv->iacqstrapiN	=iacqstrapiN;
m_priv->idataacq	=idataacq;
m_priv->idvbset	=idvbset;
m_priv->ifctrlN	=ifctrlN;
m_priv->ifena	=ifena;
m_priv->ifstrapiN	=ifstrapiN;
m_priv->ifull	=ifull;
m_priv->ifullfeN	=ifullfeN;
m_priv->ifullpow	=ifullpow;
m_priv->igctrlN	=igctrlN;
m_priv->igena	=igena;
m_priv->igrid	=igrid;
m_priv->igridfeN	=igridfeN;
m_priv->igridpow	=igridpow;
m_priv->igstrapiN	=igstrapiN;
m_priv->insN	=insN;
m_priv->ipctrlN	=ipctrlN;
m_priv->ipena	=ipena;
m_priv->iprescan	=iprescan;
m_priv->iprescanfeN	=iprescanfeN;
m_priv->iprescanpow	=iprescanpow;
m_priv->iqctrlN	=iqctrlN;
m_priv->iqena	=iqena;
m_priv->iqstrapiN	=iqstrapiN;
m_priv->iquick	=iquick;
m_priv->iquickfeN	=iquickfeN;
m_priv->iquickpow	=iquickpow;
m_priv->isetpow	=isetpow;
m_priv->pen	=pen;
m_priv->pmp	=pmp;
m_priv->rins	=rins;
}
CHsvDvbCInstallation_m::~CHsvDvbCInstallation_m()
{
 delete m_priv;
}
#endif
