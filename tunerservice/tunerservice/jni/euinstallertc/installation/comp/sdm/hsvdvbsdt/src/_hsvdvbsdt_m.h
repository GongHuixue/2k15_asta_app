#ifndef HSVDVBSDT_M
#define HSVDVBSDT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbSDT.h"
#include "CHsvDvbSDT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbSDT_Priv::params__init(void)
{
sdtmainconf_MaxElements    = 1000;     /* Number of Services per tsid */ 
        
        sdtmainconf_ElementSize    = sizeof(HsvSDTSection);   
        sdtmainconf_SortCriteria   = sdtmainconf_Primary | sdtmainconf_Secondary | sdtmainconf_Teritiary;

        sdtsubconf_MaxElements    = 1000;     /* Number of Services per tsid */ 
        
        sdtsubconf_ElementSize    = sizeof(HsvSDTSection);   
        sdtsubconf_SortCriteria   = sdtsubconf_Primary | sdtsubconf_Secondary | sdtsubconf_Teritiary;

        linkmainconf_MaxElements    = 1000;     /* Copy from SDT*/     
        linkmainconf_ElementSize    = sizeof(HsvLinkageInfo);   
        linkmainconf_SortCriteria   = linkmainconf_Primary | linkmainconf_Secondary | linkmainconf_Teritiary;
    
		sdttargetregionconf_MaxElements    = 100;   
        sdttargetregionconf_ElementSize    = sizeof(HsvSDTTargetRegion);
        sdttargetregionconf_SortCriteria   = sdttargetregionconf_Primary | sdttargetregionconf_Secondary | sdttargetregionconf_Teritiary;

		sdtsvcavailabilityconf_MaxElements    = 1000;     /* Number of Services per Tsid */ 
        sdtsvcavailabilityconf_ElementSize    = sizeof(HsvSDTCellID);   
        sdtsvcavailabilityconf_SortCriteria   = sdtsubconf_Primary | sdtsubconf_Secondary | sdtsubconf_Teritiary;

		
		sdtmultilingsvcnameconf_MaxElements    = 3000;     /* Number of Services per Tsid */ 
        sdtmultilingsvcnameconf_ElementSize    = sizeof(HsvSDTMultiLingSvcName);   
        sdtmultilingsvcnameconf_SortCriteria   = sdtsubconf_Primary | sdtsubconf_Secondary | sdtsubconf_Teritiary | sdtsubconf_Quaternary;

}
CHsvDvbSDT_Priv::~CHsvDvbSDT_Priv()
{
}
//public class connections
CHsvDvbSDT::CHsvDvbSDT()
{
 m_priv = new CHsvDvbSDT_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
linkmainconf	= m_priv->linkmainconf;
pow	= m_priv->pow;
sdtena	= m_priv->sdtena;
sdtmainconf	= m_priv->sdtmainconf;
sdtsubconf	= m_priv->sdtsubconf;
sdttargetregionconf	= m_priv->sdttargetregionconf;
sdtsvcavailabilityconf=m_priv->sdtsvcavailabilityconf;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->cids	=cids;
m_priv->conf	=conf;
m_priv->ctrlN	=ctrlN;
m_priv->dvbsvc	=dvbsvc;
m_priv->ins	=ins;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
m_priv->sysset	=sysset;
m_priv->eurdiv = eurdiv;
m_priv->mpegserv	= mpegserv;
}
CHsvDvbSDT::~CHsvDvbSDT()
{
 delete m_priv;
}
#endif
