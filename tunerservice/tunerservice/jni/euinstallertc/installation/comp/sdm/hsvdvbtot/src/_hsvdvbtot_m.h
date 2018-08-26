#ifndef HSVDVBTOT_M
#define HSVDVBTOT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbTOT.h"
#include "CHsvDvbTOT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbTOT_Priv::params__init(void)
{

totmainconf_MaxElements    = 10;  
	totmainconf_ElementSize    = sizeof(HsvTimeOffsetDescription);   
	totmainconf_SortCriteria   = totmainconf_Primary | totmainconf_Secondary ;
}
CHsvDvbTOT_Priv::~CHsvDvbTOT_Priv()
{
}
//public class connections
CHsvDvbTOT::CHsvDvbTOT()
{
 m_priv = new CHsvDvbTOT_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
totmainconf	= m_priv->totmainconf;
m_priv->cids	=cids;
m_priv->conf	=conf;
m_priv->dt	=dt;
m_priv->dtconv	=dtconv;
m_priv->eurdiv	=eurdiv;
m_priv->ins	=ins;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
m_priv->sysset5	=sysset5;
}
CHsvDvbTOT::~CHsvDvbTOT()
{
 delete m_priv;
}
#endif
