#ifndef HSVDVBCAMNIT_M
#define HSVDVBCAMNIT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCamNIT.h"
#include "CHsvDvbCamNIT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCamNIT_Priv::params__init(void)
{
	camnitlinkageinfoconf_MaxElements    = 50;     
	camnitlinkageinfoconf_ElementSize    = sizeof(HsvCamNITLinkageInfo);   
	camnitlinkageinfoconf_SortCriteria   = camnitlinkageinfoconf_Primary | camnitlinkageinfoconf_Secondary | camnitlinkageinfoconf_Teritiary;

	camnitsatellitedsconf_MaxElements    = 500;     
	camnitsatellitedsconf_ElementSize    = sizeof(HsvNITSatelliteDS);   
	camnitsatellitedsconf_SortCriteria   = camnitsatellitedsconf_Primary | camnitsatellitedsconf_Secondary;

	optunesatellitedsconf_MaxElements    = 500;     
	optunesatellitedsconf_ElementSize    = sizeof(HsvNITSatelliteDS);   
	optunesatellitedsconf_SortCriteria   = optunesatellitedsconf_Primary | optunesatellitedsconf_Secondary;

	
	camnitcontentlabelconf_MaxElements    = 10;
	camnitcontentlabelconf_ElementSize    = sizeof(HsvCamNITContentLabel);   
	camnitcontentlabelconf_SortCriteria   = camnitcontentlabelconf_Primary | camnitcontentlabelconf_Secondary | camnitcontentlabelconf_Teritiary;

	camnitserviceconf_MaxElements    = 500;
	camnitserviceconf_ElementSize    = sizeof(HsvCamNITService);   
	camnitserviceconf_SortCriteria   = camnitserviceconf_Primary | camnitserviceconf_Secondary | camnitserviceconf_Teritiary | camnitserviceconf_Quaternary;
}
CHsvDvbCamNIT_Priv::~CHsvDvbCamNIT_Priv()
{
}
//public class connections
CHsvDvbCamNIT::CHsvDvbCamNIT()
{
 m_priv = new CHsvDvbCamNIT_Priv();
camdataparser	= m_priv->camdataparser;
camnitsatellitedsconf	= m_priv->camnitsatellitedsconf;
camnitcontentlabelconf	= m_priv->camnitcontentlabelconf;
camnitlinkageinfoconf	= m_priv->camnitlinkageinfoconf;
camnitserviceconf	= m_priv->camnitserviceconf;
ena	= m_priv->ena;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
}
CHsvDvbCamNIT::~CHsvDvbCamNIT()
{
 delete m_priv;
}
#endif
