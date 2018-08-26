#ifndef HSVDVBBAT_M
#define HSVDVBBAT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbBAT.h"
#include "CHsvDvbBAT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbBAT_Priv::params__init(void)
{
	batlcnconf_MaxElements    = 1500;
	batlcnconf_ElementSize    = sizeof(HsvBATLCN);   
	batlcnconf_SortCriteria   = batlcnconf_Primary | batlcnconf_Secondary | batlcnconf_Teritiary;

	batlcn2conf_MaxElements    = 1500;
	batlcn2conf_ElementSize    = sizeof(HsvBATLCN2);   
	batlcn2conf_SortCriteria   = batlcn2conf_Primary | batlcn2conf_Secondary | batlcn2conf_Teritiary;

	batlinkmainconf_MaxElements    = 50;
	batlinkmainconf_ElementSize    = sizeof(HsvBATLinkageInfo);   
	batlinkmainconf_SortCriteria   = batlinkmainconf_Primary | batlinkmainconf_Secondary | batlinkmainconf_Teritiary;

	batsrvclstmainconf_MaxElements    = 1500;
	batsrvclstmainconf_ElementSize    = sizeof(HsvBATServiceList);
	batsrvclstmainconf_SortCriteria   = batsrvclstmainconf_Primary | batsrvclstmainconf_Secondary | batsrvclstmainconf_Teritiary;

	batDetailsconf_MaxElements    = 60;
	batDetailsconf_ElementSize    = sizeof(HsvBATDetails);
	batDetailsconf_SortCriteria   = batDetailsconf_Primary;

	batECNconf_MaxElements    = 1500;
	batECNconf_ElementSize    = sizeof(HsvBATECN);
	batECNconf_SortCriteria   = batECNconf_Primary | batECNconf_Secondary | batECNconf_Teritiary;

	batFreesatSrvGroupconf_MaxElements    = 500;
	batFreesatSrvGroupconf_ElementSize    = sizeof(HsvFreesatServiceGroupInfo);
	batFreesatSrvGroupconf_SortCriteria   = batFreesatSrvGroupconf_Primary | batFreesatSrvGroupconf_Secondary;
	batFreesatInfoLocationconf_MaxElements    = 170;
	batFreesatInfoLocationconf_ElementSize    = sizeof(HsvFreesatInfoLocation);
	batFreesatInfoLocationconf_SortCriteria   = batFreesatInfoLocationconf_Primary | batFreesatInfoLocationconf_Secondary | batFreesatInfoLocationconf_Teritiary;

	batFreesatLCNconf_MaxElements    = 5000;
	batFreesatLCNconf_ElementSize    = sizeof(HsvFreesatLCN);
	batFreesatLCNconf_SortCriteria   = batFreesatLCNconf_Primary | batFreesatLCNconf_Secondary | batFreesatLCNconf_Teritiary;

	batLCNV2conf_MaxElements    = 1500;
	batLCNV2conf_ElementSize    = sizeof(HsvBATLCNV2);   
	batLCNV2conf_SortCriteria   = batLCNV2conf_Primary;

	batMulLCNV2conf_MaxElements    = 1500;
	batMulLCNV2conf_ElementSize    = sizeof(HsvBATMulLCNV2);   
	batMulLCNV2conf_SortCriteria   = batMulLCNV2conf_Primary;


}
CHsvDvbBAT_Priv::~CHsvDvbBAT_Priv()
{
}
//public class connections
CHsvDvbBAT::CHsvDvbBAT()
{
 m_priv = new CHsvDvbBAT_Priv();
batDetailsconf	= m_priv->batDetailsconf;
batECNconf	= m_priv->batECNconf;
batlcn2conf	= m_priv->batlcn2conf;
batlcnconf	= m_priv->batlcnconf;
batlinkmainconf	= m_priv->batlinkmainconf;
batsrvclstmainconf	= m_priv->batsrvclstmainconf;
batFreesatSrvGroupconf	= m_priv->batFreesatSrvGroupconf;
batFreesatInfoLocationconf	= m_priv->batFreesatInfoLocationconf;
batFreesatLCNconf	= m_priv->batFreesatLCNconf;

dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
m_priv->charsetutil	=charsetutil;
m_priv->conf	=conf;
m_priv->ctrl	=ctrl;
m_priv->ctrlN	=ctrlN;
m_priv->ins	=ins;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
m_priv->sysset	=sysset;
m_priv->itricolorsettings = itricolorsettings;
}
CHsvDvbBAT::~CHsvDvbBAT()
{
 delete m_priv;
}
#endif
