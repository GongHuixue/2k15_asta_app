/*  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
*  All Rights Reserved.
* This  source code and any compilation or derivative thereof is the
*  proprietary information of Koninklijke Philips Electronics N.V.
*  and is confidential in nature.
*  Under no circumstances is this software to be exposed to or placed
*  under an Open Source License of any type without the expressed
*  written permission of Koninklijke Philips Electronics N.V.
*  		%name: hsvproperty.h %
*      	%version: TVG_tv550r4dev %
* 		%date_modified: Thu Nov 13 12:24:47 2008 %
*   	     %derived_by: lakshminb %
*/

/** koala group HsvDVBPropertyConfiguration **/
/** koala using HsvDVBSiGlobals             **/


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
HSVDVBPROPERTYITEM(TargetRegion,		 HsvNITTargetRegion,        dvb, nit)  
HSVDVBPROPERTYITEM(TargetRegionName,     HsvNITTargetRegionName,    dvb, nit)  
HSVDVBPROPERTYITEM(FavoriteChannelListLCNV2,HsvNITFAVORITECHANNELLISTLCNV2, dvb, nit)  
HSVDVBPROPERTYITEM(ActualTsID,			 HsvActualTsId, dvb, nit)  
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
HSVDVBPROPERTYITEM(SvcAvailabilty,          HsvSDTCellID,       dvb, sdt) 
/* This is a vector similar to ActualTSService */
HSVDVBPROPERTYITEM(OtherSDTSection,         HsvSDTService,      dvb, sdt)
HSVDVBPROPERTYITEM(TargetRegion,			HsvSDTTargetRegion, dvb, sdt)    
HSVDVBPROPERTYITEM(MultiLingSvcName,		HsvSDTMultiLingSvcName, dvb, sdt)    
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                    NA,                 dvb, sdt) 
#endif

    /* Eit Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 dvb, eit)
#endif
HSVDVBPROPERTYITEM(ActualEITPresent,    HsvEITEvent,        dvb, eit)
HSVDVBPROPERTYITEM(ActualEITFollow,     HsvEITEvent,        dvb, eit)
HSVDVBPROPERTYITEM(OtherEITPresent,     HsvEITEvent,        dvb, eit)
HSVDVBPROPERTYITEM(OtherEITFollow,      HsvEITEvent,        dvb, eit)
HSVDVBPROPERTYITEM(ActualEITSched,      HsvEITEvent,        dvb, eit)
HSVDVBPROPERTYITEM(OtherEITSched,       HsvEITEvent,        dvb, eit)
HSVDVBPROPERTYITEM(ActualPresentRating, HsvParentalRatingDescription,   dvb, eit)
HSVDVBPROPERTYITEM(ExtendedInfo,        HsvExtendedEventInfo,   dvb, eit)
HSVDVBPROPERTYITEM(ShortDesc,           HsvEITShortDesc,   dvb, eit)
HSVDVBPROPERTYITEM(ExtendedInfoForNow,  HsvExtendedEventInfo,   dvb, eit)
HSVDVBPROPERTYITEM(ExtendedInfoForNext, HsvExtendedEventInfo,   dvb, eit)
HSVDVBPROPERTYITEM(LinkageDesc,			HsvLinkageDescription,   dvb, eit)

#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 dvb, eit) 
#endif


    /* Tdt Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 dvb, tdt) 
#endif
HSVDVBPROPERTYITEM(DateTime,            HsvDateTime,           dvb, tdt)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 dvb, tdt) 
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

    /* Pat Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 mpeg,pat) 
#endif
HSVDVBPROPERTYITEM(CurrentTsId,         int,                mpeg,pat)
HSVDVBPROPERTYITEM(Program,             HsvPATProgramPIDInfo,       mpeg,pat)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 mpeg,pat) 
#endif

    /* Pmt Properties */
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(First,               NA,                 mpeg,pmt) 
#endif
HSVDVBPROPERTYITEM(ProgramNumber,       int,                mpeg,pmt)
HSVDVBPROPERTYITEM(AudioInfo,           HsvPMTAudioInfo,    mpeg, pmt)
HSVDVBPROPERTYITEM(CurrentAudioInfo,    HsvPMTAudioInfo,    mpeg, pmt)
HSVDVBPROPERTYITEM(SubtitlingInfo,      HsvPMTSubtitlingInfo,dvb, pmt)
HSVDVBPROPERTYITEM(CurrentSubtitlingInfo,HsvPMTSubtitlingInfo,dvb, pmt)
HSVDVBPROPERTYITEM(TeletextInfo,        HsvPMTTeletextInfo, dvb, pmt)
HSVDVBPROPERTYITEM(CurrentTeletextInfo, HsvPMTTeletextInfo, dvb, pmt)
HSVDVBPROPERTYITEM(BasicPidInfo,        HsvPMTBasicPidInfo,    mpeg, pmt)
HSVDVBPROPERTYITEM(CurrentBasicPidInfo, HsvPMTBasicPidInfo,    mpeg, pmt)
HSVDVBPROPERTYITEM(CurrentProgram,      int,    mpeg, pmt)
HSVDVBPROPERTYITEM(PmtSection,          void *, mpeg, pmt)
HSVDVBPROPERTYITEM(ComponentTagInfo,    HsvPMTComponentTagInfo, dvb, pmt)
HSVDVBPROPERTYITEM(DatabroadcastInfo,   HsvPMTDatabroadcastInfo, dvb, pmt)


#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                NA,                 mpeg, pmt) 
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
HSVDVBPROPERTYITEM(First,                NA,                        dvb, camnit)
#endif
HSVDVBPROPERTYITEM(CamNITCableDS,        HsvCamNITCableDS,          dvb, camnit)
HSVDVBPROPERTYITEM(CamNITTerrestrialDS,  HsvCamNITTerrestrialDS,    dvb, camnit)
HSVDVBPROPERTYITEM(CamNITC2DS,           HsvCamNITC2DS,             dvb, camnit)
HSVDVBPROPERTYITEM(CamNITT2DS,     		 HsvCamNITT2DS,             dvb, camnit)
HSVDVBPROPERTYITEM(CamNITLinkageInfo,    HsvCamNITLinkageInfo,      dvb, camnit)
HSVDVBPROPERTYITEM(CamNITService,	     HsvCamNITService,      	dvb, camnit)
HSVDVBPROPERTYITEM(CamNITContentLabel,	 HsvCamNITContentLabel,     dvb, camnit)
#ifdef _HSVDVBCONFINTERNAL
HSVDVBPROPERTYITEM(Last,                 NA,                    	dvb, camnit) 
#endif