#ifndef HSVDVBEIT_M
#define HSVDVBEIT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbEIT.h"
#include "CHsvDvbEIT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbEIT_Priv::params__init(void)
{
}
CHsvDvbEIT_Priv::~CHsvDvbEIT_Priv()
{
}
//public class connections
CHsvDvbEIT::CHsvDvbEIT()
{
 m_priv = new CHsvDvbEIT_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->conf	=conf;
m_priv->dvbsvc	=dvbsvc;
m_priv->mpegserv	=mpegserv;
m_priv->sec	=sec;
m_priv->strapiN	=strapiN;
}
CHsvDvbEIT::~CHsvDvbEIT()
{
 delete m_priv;
}
#endif
