#ifndef HSVDVBFNT_M
#define HSVDVBFNT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbFNT.h"
#include "CHsvDvbFNT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbFNT_Priv::params__init(void)
{
	fntlcnconf_MaxElements    = 3000;     
	fntlcnconf_ElementSize    = sizeof(HsvFNTLCN);
	fntlcnconf_SortCriteria   = fntlcnconf_Primary | fntlcnconf_Secondary | fntlcnconf_Teritiary;

	fntsatellitedsdconf_MaxElements    = 200;
	fntsatellitedsdconf_ElementSize    = sizeof(HsvNITSatelliteDS);   
	fntsatellitedsdconf_SortCriteria   = fntsatellitedsdconf_Primary | fntsatellitedsdconf_Secondary | fntsatellitedsdconf_Teritiary;

	fntsrvclstconf_MaxElements    = 3000;     
	fntsrvclstconf_ElementSize    = sizeof(HsvNITServiceList);   
	fntsrvclstconf_SortCriteria   = fntsrvclstconf_Primary | fntsrvclstconf_Secondary | fntsrvclstconf_Teritiary;

}
CHsvDvbFNT_Priv::~CHsvDvbFNT_Priv()
{
}
//public class connections
CHsvDvbFNT::CHsvDvbFNT()
{
 m_priv = new CHsvDvbFNT_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
fntlcnconf	= m_priv->fntlcnconf;
fntsatellitedsdconf	= m_priv->fntsatellitedsdconf;
fntsrvclstconf	= m_priv->fntsrvclstconf;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->conf	=conf;
m_priv->ctrlN	=ctrlN;
m_priv->pakgins	=pakgins;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
}
CHsvDvbFNT::~CHsvDvbFNT()
{
 delete m_priv;
}
#endif
