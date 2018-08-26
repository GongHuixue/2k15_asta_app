#ifndef HSVDVBNIT_M
#define HSVDVBNIT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbNIT.h"
#include "CHsvDvbNIT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbNIT_Priv::params__init(void)
{

			nitlcnmainconf_MaxElements    = 1000;     
			
			nitlcnmainconf_ElementSize    = sizeof(HsvNITLCN);   
            nitlcnmainconf_SortCriteria   = nitlcnmainconf_Primary | nitlcnmainconf_Secondary | nitlcnmainconf_Teritiary;
            
			
			nitlcnsubconf_MaxElements    = 1000;     
			
			nitlcnsubconf_ElementSize    = sizeof(HsvNITLCN);   
            nitlcnsubconf_SortCriteria   = nitlcnsubconf_Primary | nitlcnsubconf_Secondary | nitlcnsubconf_Teritiary;
            
            //nitlcnsubconf_MaxElements = (nitlcnsubconf_MaxElements * nitcablemainconf_MaxElements);

            nitlinkmainconf_MaxElements    = 50;     
            
            nitlinkmainconf_ElementSize    = sizeof(HsvNITLinkageInfo);   
            nitlinkmainconf_SortCriteria   = nitlinkmainconf_Primary | nitlinkmainconf_Secondary | nitlinkmainconf_Teritiary;
            nitlinksubconf_MaxElements    = 50;     
            
            nitlinksubconf_ElementSize    = sizeof(HsvNITLinkageInfo);   
            nitlinksubconf_SortCriteria   = nitlinksubconf_Primary | nitlinksubconf_Secondary | nitlinksubconf_Teritiary;

            

            nitcablemainconf_MaxElements    = 94;
            
            nitcablemainconf_ElementSize    = sizeof(HsvNITCableDS);   
            nitcablemainconf_SortCriteria   = nitcablemainconf_Primary | nitcablemainconf_Secondary | nitcablemainconf_Teritiary;

            nitcablesubconf_MaxElements    = 94;
            
            nitcablesubconf_ElementSize    = sizeof(HsvNITCableDS);   
            nitcablesubconf_SortCriteria   = nitcablesubconf_Primary | nitcablesubconf_Secondary | nitcablesubconf_Teritiary;
            
            //nitcablesubconf_MaxElements = (nitntwkidconf_MaxElements * nitcablemainconf_MaxElements);
            
            nitntwkidconf_MaxElements    = 200;
            
            nitntwkidconf_ElementSize    = sizeof(HsvNITOtherNetworkIdInfo);   
            nitntwkidconf_SortCriteria   = nitntwkidconf_Primary; 
			
            nitfreqlistconf_MaxElements     = 20;
            
            nitfreqlistconf_ElementSize     = sizeof(HsvNITFreqList);
            nitfreqlistconf_SortCriteria    = nitfreqlistconf_Primary | nitfreqlistconf_Secondary;
			
			nitlcn2mainconf_MaxElements    = 500 * 5;     	
            
			nitlcn2mainconf_ElementSize    = sizeof(HsvNITLCN2);   
            nitlcn2mainconf_SortCriteria   = nitlcn2mainconf_Primary | nitlcn2mainconf_Secondary | nitlcn2mainconf_Teritiary| nitlcn2mainconf_Quaternary;

			nitlcn2subconf_MaxElements    = 500 * 5;     	
            
			nitlcn2subconf_ElementSize    = sizeof(HsvNITLCN2);   
            nitlcn2subconf_SortCriteria   = nitlcn2subconf_Primary | nitlcn2subconf_Secondary | nitlcn2subconf_Teritiary| nitlcn2subconf_Quaternary;



			nitlcn2favoriteconf_MaxElements    = 500 * 5;     	
            
			nitlcn2favoriteconf_ElementSize    = sizeof(HsvNITFAVORITECHANNELLISTLCNV2);   
            nitlcn2favoriteconf_SortCriteria   = nitlcn2favoriteconf_Primary | nitlcn2favoriteconf_Secondary | nitlcn2favoriteconf_Teritiary| nitlcn2favoriteconf_Quaternary;


             //nitlcn2subconf_MaxElements = (nitlcn2mainconf_MaxElements * nitcablemainconf_MaxElements);
            nithdslcnmainconf_MaxElements    = 500;     
			
			nithdslcnmainconf_ElementSize    = sizeof(HsvNITHDSLCN);   
            nithdslcnmainconf_SortCriteria   = nithdslcnmainconf_Primary | nithdslcnmainconf_Secondary | nithdslcnmainconf_Teritiary;
            
			nithdslcnsubconf_MaxElements    = 500;     
			
			nithdslcnsubconf_ElementSize    = sizeof(HsvNITHDSLCN);   
            nithdslcnsubconf_SortCriteria   = nithdslcnsubconf_Primary | nithdslcnsubconf_Secondary | nithdslcnsubconf_Teritiary;
			

			nitsrvcatrbmainconf_MaxElements    = 1000;     
			
			nitsrvcatrbmainconf_ElementSize    = sizeof(HsvNITSRVCATRB);   
            nitsrvcatrbmainconf_SortCriteria   = nitsrvcatrbmainconf_Primary | nitsrvcatrbmainconf_Secondary | nitsrvcatrbmainconf_Teritiary;

            nitsrvclstmainconf_MaxElements    = 1000;     
			
			nitsrvclstmainconf_ElementSize    = sizeof(HsvNITServiceList);   
            nitsrvclstmainconf_SortCriteria   = nitsrvclstmainconf_Primary | nitsrvclstmainconf_Secondary | nitsrvclstmainconf_Teritiary;

            nitsrvclstsubconf_MaxElements    = 1000;     
			
			nitsrvclstsubconf_ElementSize    = sizeof(HsvNITServiceList);   
            nitsrvclstsubconf_SortCriteria   = nitsrvclstsubconf_Primary | nitsrvclstsubconf_Secondary | nitsrvclstsubconf_Teritiary;
            
			
            nittsrelocatemainconf_MaxElements    = 94;     
			
			nittsrelocatemainconf_ElementSize    = sizeof(HsvNITTSRelocated);   
            nittsrelocatemainconf_SortCriteria   = nittsrelocatemainconf_Primary | nittsrelocatemainconf_Secondary | nittsrelocatemainconf_Teritiary;

			nittargetregionconf_MaxElements           = 200;     
			
			nittargetregionconf_ElementSize           = sizeof(HsvNITTargetRegion);   
            nittargetregionconf_SortCriteria          = nittargetregionconf_Primary | nittargetregionconf_Secondary | nittargetregionconf_Teritiary;

			nittargetregionnameconf_MaxElements       = 100;
			
			nittargetregionnameconf_ElementSize       = sizeof(HsvNITTargetRegionName);   
            nittargetregionnameconf_SortCriteria      = nittargetregionnameconf_Primary | nittargetregionnameconf_Secondary | nittargetregionnameconf_Teritiary | nittargetregionnameconf_Quaternary;


			
			nitactualtsidconf_MaxElements 	  = 100;
						
			nitactualtsidconf_ElementSize 	  = sizeof(HsvActualTsId);   
			nitactualtsidconf_SortCriteria	  = nitactualtsidconf_Primary | nitactualtsidconf_Secondary; 

			
}
CHsvDvbNIT_Priv::~CHsvDvbNIT_Priv()
{
}
//public class connections
CHsvDvbNIT::CHsvDvbNIT()
{
 m_priv = new CHsvDvbNIT_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
nitcablemainconf	= m_priv->nitcablemainconf;
nitcablesubconf	= m_priv->nitcablesubconf;
nitfreqlistconf	= m_priv->nitfreqlistconf;
nithdslcnmainconf	= m_priv->nithdslcnmainconf;
nithdslcnsubconf	= m_priv->nithdslcnsubconf;
nitlcn2mainconf	= m_priv->nitlcn2mainconf;
nitlcn2favoriteconf	= m_priv->nitlcn2favoriteconf;
nitlcn2subconf	= m_priv->nitlcn2subconf;
nitlcnmainconf	= m_priv->nitlcnmainconf;
nitlcnsubconf	= m_priv->nitlcnsubconf;
nitlinkmainconf	= m_priv->nitlinkmainconf;
nitlinksubconf	= m_priv->nitlinksubconf;
nitntwkidconf	= m_priv->nitntwkidconf;
nitsrvcatrbmainconf	= m_priv->nitsrvcatrbmainconf;
nitsrvclstmainconf	= m_priv->nitsrvclstmainconf;
nitsrvclstsubconf	= m_priv->nitsrvclstsubconf;
nittargetregionconf	= m_priv->nittargetregionconf;
nittargetregionnameconf	= m_priv->nittargetregionnameconf;
nittsrelocatemainconf	= m_priv->nittsrelocatemainconf;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->cids	=cids;
m_priv->conf	=conf;
m_priv->ctrlN	=ctrlN;
m_priv->eurdiv	=eurdiv;
m_priv->ins	=ins;
m_priv->mpegserv	=mpegserv;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
m_priv->sysset	=sysset;
}
CHsvDvbNIT::~CHsvDvbNIT()
{
 delete m_priv;
}
#endif
