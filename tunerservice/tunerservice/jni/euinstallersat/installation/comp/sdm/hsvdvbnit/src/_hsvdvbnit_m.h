#ifndef HSVDVBNIT_M
#define HSVDVBNIT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbNIT.h"
#include "CHsvDvbNIT_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbNIT_Priv::params__init(void)
{






			nitlcnmainconf_MaxElements    = 500;     
			nitlcnmainconf_ElementSize    = sizeof(HsvNITLCN);   
            nitlcnmainconf_SortCriteria   = nitlcnmainconf_Primary | nitlcnmainconf_Secondary | nitlcnmainconf_Teritiary;

			nitlcnsubconf_MaxElements    = 500;     
			nitlcnsubconf_ElementSize    = sizeof(HsvNITLCN);   
            nitlcnsubconf_SortCriteria   = nitlcnsubconf_Primary | nitlcnsubconf_Secondary | nitlcnsubconf_Teritiary;

            nitlinkmainconf_MaxElements    = 50;     
            nitlinkmainconf_ElementSize    = sizeof(HsvNITLinkageInfo);   
            nitlinkmainconf_SortCriteria   = nitlinkmainconf_Primary | nitlinkmainconf_Secondary | nitlinkmainconf_Teritiary;

			nitlinksubconf_MaxElements    = 50;     
            nitlinksubconf_ElementSize    = sizeof(HsvNITLinkageInfo);   
            nitlinksubconf_SortCriteria   = nitlinksubconf_Primary | nitlinksubconf_Secondary | nitlinksubconf_Teritiary;

			nitsatellitedsdconf_MaxElements    = 500;
            nitsatellitedsdconf_ElementSize    = sizeof(HsvNITSatelliteDS);   
            nitsatellitedsdconf_SortCriteria   = nitsatellitedsdconf_Primary | nitsatellitedsdconf_Secondary | nitsatellitedsdconf_Teritiary;
            
            nitntwkidconf_MaxElements    = 200;
            nitntwkidconf_ElementSize    = sizeof(HsvNITOtherNetworkIdInfo);   
            nitntwkidconf_SortCriteria   = nitntwkidconf_Primary; 
			
            nitfreqlistconf_MaxElements     = 20;
            nitfreqlistconf_ElementSize     = sizeof(HsvNITFreqList);
            nitfreqlistconf_SortCriteria    = nitfreqlistconf_Primary | nitfreqlistconf_Secondary;


            nitlcn2mainconf_MaxElements    = 500 * 5;     
			nitlcn2mainconf_ElementSize    = sizeof(HsvNITLCN2);   
            nitlcn2mainconf_SortCriteria   = nitlcn2mainconf_Primary | nitlcn2mainconf_Secondary | nitlcn2mainconf_Teritiary;


			nitlcn2subconf_MaxElements    = 500 * 5;     
			nitlcn2subconf_ElementSize    = sizeof(HsvNITLCN2);   
            nitlcn2subconf_SortCriteria   = nitlcn2subconf_Primary | nitlcn2subconf_Secondary | nitlcn2subconf_Teritiary;


            //nitlcn2subconf.MaxElements = (nitlcn2mainconf.MaxElements * nitsatellitedsdconf.MaxElements);
            nithdslcnmainconf_MaxElements    = 500;     
			nithdslcnmainconf_ElementSize    = sizeof(HsvNITHDSLCN);   
            nithdslcnmainconf_SortCriteria   = nithdslcnmainconf_Primary | nithdslcnmainconf_Secondary | nithdslcnmainconf_Teritiary;

            nithdslcnsubconf_MaxElements    = 500;     
			nithdslcnsubconf_ElementSize    = sizeof(HsvNITHDSLCN);   
            nithdslcnsubconf_SortCriteria   = nithdslcnsubconf_Primary | nithdslcnsubconf_Secondary | nithdslcnsubconf_Teritiary;

			
			nitsrvclstmainconf_MaxElements    = 500;     
			nitsrvclstmainconf_ElementSize    = sizeof(HsvNITServiceList);   
            nitsrvclstmainconf_SortCriteria   = nitsrvclstmainconf_Primary | nitsrvclstmainconf_Secondary | nitsrvclstmainconf_Teritiary;

            nitsrvclstsubconf_MaxElements    = 500;     
			nitsrvclstsubconf_ElementSize    = sizeof(HsvNITServiceList);   
            nitsrvclstsubconf_SortCriteria   = nitsrvclstsubconf_Primary | nitsrvclstsubconf_Secondary | nitsrvclstsubconf_Teritiary;

			
			nitlcn3mainconf_MaxElements    = 2000;     // check
			nitlcn3mainconf_ElementSize    = sizeof(HsvNITLCN3);   
            nitlcn3mainconf_SortCriteria   = nitlcn3mainconf_Primary | nitlcn3mainconf_Secondary | nitlcn3mainconf_Teritiary;

			nitHeadEndFrequencyListconf_MaxElements    = 50;
            nitHeadEndFrequencyListconf_ElementSize    = sizeof(HsvHeadEndFrequencyList);   
            nitHeadEndFrequencyListconf_SortCriteria   = nitHeadEndFrequencyListconf_Primary | nitHeadEndFrequencyListconf_Secondary | nitHeadEndFrequencyListconf_Teritiary;

			nitFreesatLinkageconf_MaxElements    = 25;
            nitFreesatLinkageconf_ElementSize    = sizeof(HsvFreesatLinkageInfo);
            nitFreesatLinkageconf_SortCriteria   = nitFreesatLinkageconf_Primary | nitFreesatLinkageconf_Secondary | nitFreesatLinkageconf_Teritiary;


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
nitHeadEndFrequencyListconf	= m_priv->nitHeadEndFrequencyListconf;
nitfreqlistconf	= m_priv->nitfreqlistconf;
nithdslcnmainconf	= m_priv->nithdslcnmainconf;
nithdslcnsubconf	= m_priv->nithdslcnsubconf;
nitlcn2mainconf	= m_priv->nitlcn2mainconf;
nitlcn2subconf	= m_priv->nitlcn2subconf;
nitlcn3mainconf	= m_priv->nitlcn3mainconf;
nitlcnmainconf	= m_priv->nitlcnmainconf;
nitlcnsubconf	= m_priv->nitlcnsubconf;
nitlinkmainconf	= m_priv->nitlinkmainconf;
nitlinksubconf	= m_priv->nitlinksubconf;
nitntwkidconf	= m_priv->nitntwkidconf;
nitsatellitedsdconf	= m_priv->nitsatellitedsdconf;
nitsrvclstmainconf	= m_priv->nitsrvclstmainconf;
nitsrvclstsubconf	= m_priv->nitsrvclstsubconf;
nitFreesatLinkageconf	= m_priv->nitFreesatLinkageconf;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->cids	=cids;
m_priv->conf	=conf;
m_priv->ctrlN	=ctrlN;
m_priv->eurdiv	=eurdiv;
m_priv->ins	=ins;
m_priv->pakgins	=pakgins;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
m_priv->sysset	=sysset;
m_priv->ctrl	=ctrl;
}
CHsvDvbNIT::~CHsvDvbNIT()
{
 delete m_priv;
}
#endif
