#ifndef HSVDVBTDT_M
#define HSVDVBTDT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTDT.h"
#include "CHsvDvbTDT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTDT_Priv::params__init(void)
{
}
CHsvDvbTDT_Priv::~CHsvDvbTDT_Priv()
{
}
//public class connections
CHsvDvbTDT::CHsvDvbTDT()
{
 m_priv = new CHsvDvbTDT_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
m_priv->compids	=compids;
m_priv->conf	=conf;
m_priv->dtconv	=dtconv;
m_priv->eurdiv	=eurdiv;
m_priv->ins	=ins;
m_priv->sec	=sec;
}
CHsvDvbTDT::~CHsvDvbTDT()
{
 delete m_priv;
}
#endif
