#ifndef HSVDVBCAMSDM_M
#define HSVDVBCAMSDM_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbCamSdm.h"
#include "CHsvDvbCamSdm_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbCamSdm_Priv::params__init(void)
{
	camnitlinkageinfoconf_MaxElements    = 50;     
	camnitlinkageinfoconf_ElementSize    = sizeof(HsvCamNITLinkageInfo);   
	camnitlinkageinfoconf_SortCriteria   = camnitlinkageinfoconf_Primary | camnitlinkageinfoconf_Secondary | camnitlinkageinfoconf_Teritiary;
	
	camnitcabledsconf_MaxElements    = 94;     
	camnitcabledsconf_ElementSize    = sizeof(HsvCamNITCableDS);   
	camnitcabledsconf_SortCriteria   = camnitcabledsconf_Primary | camnitcabledsconf_Secondary;
	
	camnitterrestrialdsconf_MaxElements    = 160;     
	camnitterrestrialdsconf_ElementSize    = sizeof(HsvCamNITTerrestrialDS);   
	camnitterrestrialdsconf_SortCriteria   = camnitterrestrialdsconf_Primary | camnitterrestrialdsconf_Secondary | camnitterrestrialdsconf_Teritiary;

	camnitc2dsconf_MaxElements    = 94;     
	camnitc2dsconf_ElementSize    = sizeof(HsvCamNITC2DS);   
	camnitc2dsconf_SortCriteria   = camnitc2dsconf_Primary | camnitc2dsconf_Secondary;

	camnitt2dsconf_MaxElements    = 94;
	camnitt2dsconf_ElementSize    = sizeof(HsvCamNITT2DS);   
	camnitt2dsconf_SortCriteria   = camnitt2dsconf_Primary | camnitt2dsconf_Secondary;

	camnitcontentlabelconf_MaxElements    = 10;
	camnitcontentlabelconf_ElementSize    = sizeof(HsvCamNITContentLabel);   
	camnitcontentlabelconf_SortCriteria   = camnitcontentlabelconf_Primary | camnitcontentlabelconf_Secondary | camnitcontentlabelconf_Teritiary;
	
	camnitserviceconf_MaxElements    = 500;
	camnitserviceconf_ElementSize    = sizeof(HsvCamNITService);   
	camnitserviceconf_SortCriteria   = camnitserviceconf_Primary | camnitserviceconf_Secondary | camnitserviceconf_Teritiary | camnitserviceconf_Quaternary;

}
CHsvDvbCamSdm_Priv::~CHsvDvbCamSdm_Priv()
{
}
//public class connections
CHsvDvbCamSdm::CHsvDvbCamSdm()
{
 m_priv = new CHsvDvbCamSdm_Priv();
camScanparser	= m_priv->camScanparser;
camnitc2dsconf	= m_priv->camnitc2dsconf;
camnitcabledsconf	= m_priv->camnitcabledsconf;
camnitcontentlabelconf	= m_priv->camnitcontentlabelconf;
camnitlinkageinfoconf	= m_priv->camnitlinkageinfoconf;
camnitserviceconf	= m_priv->camnitserviceconf;
camnitt2dsconf	= m_priv->camnitt2dsconf;
camnitterrestrialdsconf	= m_priv->camnitterrestrialdsconf;
ena	= m_priv->ena;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->mpegserv	=mpegserv;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
}
CHsvDvbCamSdm::~CHsvDvbCamSdm()
{
 delete m_priv;
}
#endif
