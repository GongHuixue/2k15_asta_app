#ifndef HSVEUINS_MFREQCTL
#define HSVEUINS_MFREQCTL

#define GENERATE__LEGACY__DEFINES

#include "../CHsvEuropeInstallation_mfreqctl.h"
#include "CHsvEuropeInstallation_mfreqctl_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvEuropeInstallation_mfreqctl_Priv::params__init(void)
{
}
CHsvEuropeInstallation_mfreqctl_Priv::~CHsvEuropeInstallation_mfreqctl_Priv()
{
}
//public class connections
CHsvEuropeInstallation_mfreqctl::CHsvEuropeInstallation_mfreqctl()
{
 m_priv = new CHsvEuropeInstallation_mfreqctl_Priv();
freqctl	= m_priv->freqctl;
imfreqctlpow	= m_priv->imfreqctlpow;
m_priv->eurdiv	=eurdiv;
m_priv->feapi	=feapi;
m_priv->insN	=insN;
m_priv->rins	=rins;
m_priv->sysset	=sysset;
m_priv->wnddest	=wnddest;
}
CHsvEuropeInstallation_mfreqctl::~CHsvEuropeInstallation_mfreqctl()
{
 delete m_priv;
}
#endif
