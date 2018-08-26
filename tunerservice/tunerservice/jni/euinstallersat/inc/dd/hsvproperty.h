/*  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
*  All Rights Reserved.
* This  source code and any compilation or derivative thereof is the
*  proprietary information of Koninklijke Philips Electronics N.V.
*  and is confidential in nature.
*  Under no circumstances is this software to be exposed to or placed
*  under an Open Source License of any type without the expressed
*  written permission of Koninklijke Philips Electronics N.V.
*  		%name: hsvproperty.h %
*      	%version: FUSION_TVG_9.1.1 %
* 		%date_modified: Thu Nov 13 12:24:47 2008 %
*   	     %derived_by: anuma %
*/

/** koala group HsvDVBPropertyConfiguration **/
/** koala using HsvDVBSiGlobals             **/

    /* Nit Properties */

#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                NA,                        dvb, nit)
#endif
//HSVDVBPROPERTYITEM(ActualNetworkTS,      HsvNITTS,              dvb, nit)
HSVDVBPROPERTYITEM(ActualNetworkID,      int,                       dvb, nit)
HSVDVBPROPERTYITEM(NetworkName,          char*,                     dvb, nit)
HSVDVBPROPERTYITEM(ActualNITVer,         Nat8,                      dvb, nit)
HSVDVBPROPERTYITEM(ActualNetworkLCN,     HsvNITLCN,                 dvb, nit)
HSVDVBPROPERTYITEM(LinkageInfo,          HsvNITLinkageInfo,         dvb, nit)
HSVDVBPROPERTYITEM(ActualCableDS,        HsvNITCableDS,             dvb, nit)  
HSVDVBPROPERTYITEM(ActualNetworkLCN2,    HsvNITLCN2,                dvb, nit)  
HSVDVBPROPERTYITEM(ActualNetworkHDSLCN,  HsvNITHDSLCN,              dvb, nit)  
HSVDVBPROPERTYITEM(FreqList,             HsvNITFreqList,            dvb, nit)   //rashojit
HSVDVBPROPERTYITEM(ActualSRVCATRB,       HsvNITSRVCATRB,            dvb, nit)  
HSVDVBPROPERTYITEM(ActualServiceList,    HsvNITServiceList,         dvb, nit)  
HSVDVBPROPERTYITEM(ActualTSRelocated,    HsvNITTSRelocated,         dvb, nit)  
HSVDVBPROPERTYITEM(OtherNetworkIDInfo,   HsvNITOtherNetworkIdInfo,  dvb, nit)  
HSVDVBPROPERTYITEM(OtherNetworkLCN,      HsvNITLCN,                 dvb, nit)
//HSVDVBPROPERTYITEM(OtherNetworkTS,       HsvNITTS,              dvb, nit)
HSVDVBPROPERTYITEM(OtherLinkageInfo,     HsvNITOtherLinkageInfo,    dvb, nit)
HSVDVBPROPERTYITEM(OtherCableDS,         HsvNITOtherCableDS,        dvb, nit)
HSVDVBPROPERTYITEM(OtherNetworkLCN2,     HsvNITLCN2,                dvb, nit)
HSVDVBPROPERTYITEM(OtherServiceList,     HsvNITServiceList,         dvb, nit)
HSVDVBPROPERTYITEM(OtherNetworkHDSLCN,   HsvNITHDSLCN,              dvb, nit)  
HSVDVBPROPERTYITEM(SatelliteDS,	         HsvNITSatelliteDS,         dvb, nit)
HSVDVBPROPERTYITEM(ActualNetworkLCN3,    HsvNITLCN3,                dvb, nit)
HSVDVBPROPERTYITEM(HeadEndFrequencyList, HsvHeadEndFrequencyList,   dvb, nit)
HSVDVBPROPERTYITEM(FreesatLinkageInfo,          HsvFreesatLinkageInfo,         dvb, nit)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    dvb, nit) 
#endif

    /* Sdt Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                   NA,                 dvb, sdt)
#endif
HSVDVBPROPERTYITEM(ActualTsId,              int,                dvb, sdt)  
HSVDVBPROPERTYITEM(ActualOriginalNetworkId, int,                dvb, sdt)  
HSVDVBPROPERTYITEM(ActualTsVersionNo,       int,                dvb, sdt)  
HSVDVBPROPERTYITEM(ActualTSService,         HsvSDTService,      dvb, sdt)  
HSVDVBPROPERTYITEM(OtherTSService,          HsvSDTService,      dvb, sdt)  
HSVDVBPROPERTYITEM(LinkageInfo,             HsvSDTLinkageInfo,  dvb, sdt)  
HSVDVBPROPERTYITEM(OtherTsId,               int,                dvb, sdt)  
HSVDVBPROPERTYITEM(OtherOriginalNetworkId,  int,                dvb, sdt)  
HSVDVBPROPERTYITEM(OtherTsVersionNo,        int,                dvb, sdt)  
/* This is a vector similar to ActualTSService */
HSVDVBPROPERTYITEM(OtherSDTSection,         HsvSDTService,      dvb, sdt)
HSVDVBPROPERTYITEM(TargetRegion,			HsvSDTTargetRegion, dvb, sdt)    
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                    NA,                 dvb, sdt) 
#endif


    /* Compound Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 dvb,  lcl) 
#endif
HSVDVBPROPERTYITEM(Services,            HsvDVBService,      dvb,  lcl)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 dvb,  lcl) 
#endif
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 mpeg,simplepat) 
#endif
HSVDVBPROPERTYITEM(Program,             HsvPATProgramPIDInfo, mpeg,simplepat)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 mpeg,simplepat) 
#endif

    /* Simple Pat Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 mpeg,simplepmt) 
#endif
HSVDVBPROPERTYITEM(PidInfo,             HsvSimplePMTPidInfo,mpeg,simplepmt)
HSVDVBPROPERTYITEM(FreesatTunnelledInfo,HsvFreesatTunnelledDataInfo,mpeg,simplepmt)

#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 mpeg,simplepmt) 
#endif
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                NA,                        dvb, fnt)
#endif
HSVDVBPROPERTYITEM(SatelliteDS,	         HsvNITSatelliteDS,         dvb, fnt)
HSVDVBPROPERTYITEM(NetworkName,          char*,                     dvb, fnt)
HSVDVBPROPERTYITEM(ServiceList,    		 HsvNITServiceList,         dvb, fnt)  
HSVDVBPROPERTYITEM(LCN,     			 HsvNITLCN,                 dvb, fnt)
HSVDVBPROPERTYITEM(NetworkID,     		 int,                       dvb, fnt)
HSVDVBPROPERTYITEM(FNTVer, 		         Nat8,                      dvb, fnt)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    dvb, fnt) 
#endif
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                NA,                        dvb, fst)
#endif
HSVDVBPROPERTYITEM(ActualTSService,         HsvfstSection,      dvb, fst)  
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    dvb, fst) 
#endif
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                NA,                        dvb, sgt)
#endif
HSVDVBPROPERTYITEM(ActualTSService,         HsvSGTService,      dvb, sgt)  
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    dvb, sgt) 
#endif


#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                NA,                    dvb, bat)
#endif
HSVDVBPROPERTYITEM(batLCN,			     HsvBATLCN,             dvb, bat)
HSVDVBPROPERTYITEM(batLCN2,			     HsvBATLCN2,             dvb, bat)
HSVDVBPROPERTYITEM(batLCNV2,			 HsvBATLCNV2,             dvb, bat)
HSVDVBPROPERTYITEM(batMulLCNV2,			 HsvBATMulLCNV2,             dvb, bat)
HSVDVBPROPERTYITEM(LinkageInfo,          HsvBATLinkageInfo,         dvb, bat)
HSVDVBPROPERTYITEM(ActualServiceList,    HsvBATServiceList,         dvb, bat)  
HSVDVBPROPERTYITEM(batECN,    HsvBATECN,         dvb, bat)
HSVDVBPROPERTYITEM(batDetails,    HsvBATDetails,         dvb, bat)
HSVDVBPROPERTYITEM(ActualBouquetId,      int,                       dvb, bat)
HSVDVBPROPERTYITEM(FreesatSrvGroup,    HsvFreesatServiceGroupInfo,         dvb, bat)
HSVDVBPROPERTYITEM(FreesatInfoLocation,    HsvFreesatInfoLocation,         dvb, bat)
HSVDVBPROPERTYITEM(FreesatLCN,    HsvFreesatLCN,         dvb, bat)
HSVDVBPROPERTYITEM(TricolorLRN,	  char *,		 dvb, bat)
HSVDVBPROPERTYITEM(TricolorRegionName, HsvTricolorRegionNameData, dvb,bat)

#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    dvb, bat) 
#endif

HSVDVBPROPERTYITEM(FreesatPostcodeKey,    HsvFreesatPostcodeMapping,         dvb, postcode)
HSVDVBPROPERTYITEM(FreesatRegionKey,    HsvFreesatRegionKeyMapping,         dvb, postcode)

//CAM NIT Properties
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,                NA,                    	dvb, camnit)
#endif
HSVDVBPROPERTYITEM(SatelliteDS,       	 HsvNITSatelliteDS,         dvb, camnit)
HSVDVBPROPERTYITEM(OpTuneSatelliteDS,    HsvNITSatelliteDS,         dvb, camnit)
HSVDVBPROPERTYITEM(CamNITTerrestrialDS,  HsvCamNITTerrestrialDS,    dvb, camnit)
HSVDVBPROPERTYITEM(CamNITC2DS,           HsvCamNITC2DS,             dvb, camnit)
HSVDVBPROPERTYITEM(CamNITT2DS,     		 HsvCamNITT2DS,             dvb, camnit)
HSVDVBPROPERTYITEM(CamNITLinkageInfo,    HsvCamNITLinkageInfo,      dvb, camnit)
HSVDVBPROPERTYITEM(CamNITService,	     HsvCamNITService,      	dvb, camnit)
HSVDVBPROPERTYITEM(CamNITContentLabel,	 HsvCamNITContentLabel,     dvb, camnit)
HSVDVBPROPERTYITEM(CamNIT,	 			 int, 						dvb, camnit)
HSVDVBPROPERTYITEM(CamTuneDSDesc,		 int, 						dvb, camnit)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    	dvb, camnit) 
#endif

/* Tot Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 dvb, tot)
#endif
HSVDVBPROPERTYITEM(DateTime,            HsvDateTime,           dvb, tot)
HSVDVBPROPERTYITEM(TimeOffset,          HsvTOTTimeOffsetInfo,       dvb, tot)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 dvb, tot)
#endif

