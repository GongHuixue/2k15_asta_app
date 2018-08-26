/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvdvbnit_m.c %
 *       %version: TVG_fusion_21.1.1 %
 * %date_modified: Fri Feb 20 20:07:55 2009 %
 *    %derived_by: integration %
 */


#include "_hsvdvbnit_m.h"


TRACESYMBOL(m, "dvb/sitables/hsvdvbnit_m")



#ifndef __cplusplus

#else

#endif












struct _DmxROMData CHsvDvbNIT_Priv::s__DmxROMData[HsvDmxLast];


/* Mapping to HsvGlobals using HsvConstellation */
Nat8 CHsvDvbNIT_Priv::s__mModulation[7] = 
{
    /*0x00 not defined*/                    HsvUnknownConstellation,
    /*0x01 16 QAM*/                         HsvQam16,
    /*0x02 32 QAM*/                         HsvQam32,
    /*0x03 64 QAM*/                         HsvQam64,
    /*0x04 128 QAM*/                        HsvQam128,
    /*0x05 256 QAM*/                        HsvQam256,
    /*0x06 to 0xFF reserved for future use*/HsvUnknownConstellation
};


const Nat32 CHsvDvbNIT_Priv::PrivateDataSpecifier [] = 
{        
    /* Austria    */   0x0028,
    /* Belgium    */   0x0028,
    /* Croatia    */   0x0028,
    /* Czechrep   */   0x0028,
    /* Denmark    */   0x0029, /* Scandinavian Countries */
    /* Finland    */   0x0029, /* Scandinavian Countries */
    /* France     */   0x0028,
    /* Germany    */   0x0028,
    /* Greece     */   0x0028,
    /* Hungary    */   0x0028,
    /* Ireland    */   0x0028,
    /* Italy      */   0x0028,
    /* Luxembourg */   0x0028,
    /* Netherlands*/   0x0028,
    /* Norway     */   0x0029, /* Scandinavian Countries */
    /* Poland     */   0x0028,
    /* Portugal   */   0x0028,
    /* Romania    */   0x0028,
    /* Russia     */   0x0028,
    /* Serbia     */   0x0028,
    /* Slovakia   */   0x0028,
    /* Slovenia   */   0x0028,
    /* Spain      */   0x0028,
    /* Sweden     */   0x0029, /* Scandinavian Countries */
    /* Switzerland*/   0x0028,
    /* Turkey     */   0x0028,
    /* UK         */   0x233A,     
    /* Other      */   0x0028,
    /* Australia  */   0x0028,
    /* Estonia    */   0x0028,
    /* Lithuania  */   0x0028, 
    /* Latvia     */   0x0028,
    /* Kazakhstan */   0x0028,
    /* Bulgaria   */   0x0028,
    /* China      */   0x0028,
	/* Ukraine    */   0x0028,
	/* Brazil     */   0x0028,
	/* Argentina  */   0x0028,
	/* Albania    */   0x0028,
	/* Armenia    */   0x0028,
	/* Azerbaijan */   0x0028,
	/* Belarus    */   0x0028,
	/* BosniaAndHerzegovina   */   0x0028,
	/* Georgia    */   0x0028,
	/* Montenegro */   0x0028,
	/* Israel     */   0x0028,
	/* Macedoniafyrom  		  */   0x0028,
	/*Paraguay*/	   0x0000,
	/*Uruguay*/		   0x0000,
	/*Thailand*/	   0x22FC, 
	/*NewZealand*/	   0x0037,  
	/*Singapore*/	   0x0019,  
	/*Malaysia*/	   0x21CA,	
	/*Taiwan*/	       0X209E,
	/*Indonesia*/	   0x2168,
	/*Namibia*/		   0x0000,
	/*Peru*/		   0x0000,
	/*SouthAfrica*/	   0x22C6,
	/*UAE*/			   0x0028,
	/*Vietnam*/	       0x0028
};


int CHsvDvbNIT_Priv::s__mCurrentONID = 0;

Nat16 CHsvDvbNIT_Priv::s__ActualNetworkId = HSV_INVALID_NETWORKID;


/**********************************************************************************/


/**********************************************************************************/











































/***************Local Functions******************************************/









 





/**************************Initialisations*****************************************/
Nat8 CHsvDvbNIT_Priv::s__ModeArray[FILTER_DEPTH];

Nat8 CHsvDvbNIT_Priv::s__MatchArray[FILTER_DEPTH];

Nat8 CHsvDvbNIT_Priv::s__MaskArray[FILTER_DEPTH];




void CHsvDvbNIT_Priv::pow_Init(void)
{
    HsvDemux dmx;
    int      i;

    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {        
        for(i = 0; i < MAX_SECTIONS; i++)
        {
            /* Clear our structures to ensure that we dont have junk values in them*/
            DmxROMData[dmx].SubscrId[i]  = HSV_INVALID_SCT_REQUEST;
        }
        DmxROMData[dmx].SectionInfo[NITACTUAL_INDEX] = conf_NitActualParsing;
        DmxROMData[dmx].SectionInfo[NITOTHER_INDEX] = conf_NitOtherParsing; 
        DmxROMData[dmx].NITActualAvail = FALSE;
        DmxROMData[dmx].TablesReq = 0;
        DmxROMData[dmx].TablesRecvd = 0;
        DmxROMData[dmx].ActualNITVer = 0xFF;
    }    
    for(i=0; i<FILTER_DEPTH; i++)
    {
        ModeArray[i] = 0;
        MatchArray[i] = 0;
        MaskArray[i] = 0;
    }
    MatchArray[0] = NITT_OTHER_TABLE_ID;
    MaskArray[0] = 0xff;
}

void CHsvDvbNIT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbNIT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbNIT_Priv::ena_Enable(HsvDemux dmx)
{
	//TraceNotice(m,"NIT: ena_Enable");
    Bool Proceed = TRUE, NitActualAllocated = FALSE;  
    DmxROMData[dmx].NITActualAvail    = FALSE;
    DmxROMData[dmx].ActualNITVer = 0xFF;

    InitActualNetworkID(dmx);
    InitNetworkName(dmx);
    InitActualNITVer(dmx);
    InitActualNetworkLCN(dmx);
    InitLinkageInfo(dmx);
    InitActualCableDS(dmx);
    InitActualTSRelocateDS(dmx);
    InitActualServiceListDS(dmx);
    InitActualNetworkLCN2(dmx);
    InitActualNetworkHDSLCN(dmx);
    InitOtherNetworkIDInfo(dmx);
    InitOtherNetworkLCN(dmx);
    InitOtherLinkageInfo(dmx);
    InitOtherCableDS(dmx);
    InitOtherServiceListDS(dmx);
    InitOtherNetworkLCN2(dmx);
    InitNetworkSRVCATRB ( dmx); 
    InitNetworkFreqList (dmx);
    InitOtherNetworkHDSLCN(dmx);
    InitTargetRegionDesc(dmx);
    InitTargetRegionNameDesc(dmx);
	InitActualNetworkLCN2FavoriteList(dmx);
	InitActualTsID(dmx);

    DmxROMData[dmx].TablesReq = DmxROMData[dmx].TablesRecvd = 0;

    switch(sysset_GetSystemCountry())
    {  

#define COUNTRYITEM(a, b, c)    case cids_Country##b:   \
        mCurrentONID   =   c + 0x2000; \
        break;
#include <hsvcountry.h>
        default:
            mCurrentONID = 0;
            break;
    }

    /* For nit actual */
    if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[NITACTUAL_INDEX]))
    {
        if((ins_GetMedium() == ins_Cable)&&(ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UPC))
        {
            Proceed = FALSE; //in case of UPC cable NIT actual should not  be used, use only NIT other
        }
        if(Proceed == TRUE)
        {
            TraceNotice(m,"%s : %d :: Requesting filter for NIT Actual", __FILE__, __LINE__);
			#ifndef __cplusplus
            DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NITT_ACTUAL_TABLE_ID,NITT_ACTUAL_TABLE_ID, (HsvSectionCallback)FNADDR(Nit_Parser_Parser));
			#else
			DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NITT_ACTUAL_TABLE_ID,NITT_ACTUAL_TABLE_ID, FNADDR(Nit_Parser_Parser));
			#endif
            DmxROMData[dmx].TablesReq |= NIT_ACTUAL_REQ;
			NitActualAllocated = TRUE;
        }
    }
    /* For NIT Other */
    if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[NITOTHER_INDEX]))
    {
        if(ins_GetMedium() == ins_Cable)
        {
            if(ins_InstallationModePreScan == ins_GetInstallationMode())
            {
            	/*Do not request NIT others for Canal Digital and UnityMedia*/
			   if ((ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) != ins_CanalDigital) && 
			   	((sysset_GetSystemCountry() != cids_CountryGermany) || ((sysset_GetSystemCountry() == cids_CountryGermany) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) != ins_UnityMedia))))
				{
	                TraceDebug(m,"%s : %d :: Requesting Section Filter for all NIT others", __FILE__, __LINE__);
	                HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, NITT_OTHER_TABLE_ID, NIT_PID_VALUE};
	//                DmxROMData[dmx].SubscrId[NITOTHER_INDEX] = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, ModeArray, MatchArray, MaskArray, (HsvSectionFilterCallback)FNADDR(Nit_Parser_Parser));
				
					DmxROMData[dmx].SubscrId[NITOTHER_INDEX] = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig,8, ModeArray, MatchArray, MaskArray, FNADDR(Nit_Parser_Parser)); 
					DmxROMData[dmx].TablesReq = 0;
				 }
            }
            else
            {
                if(ins_GetAttributeMode(ins_InstallationModeAutomatic, ins_AttributeNetworkId) == ins_ManualValue)
                {
                    Nat16 TidExtn = ins_GetAttribute(ins_InstallationModeAutomatic, ins_AttributeNetworkId);
                    if(ActualNetworkId != TidExtn)
                    {
                        ActualNetworkId = HSV_INVALID_NETWORKID;
                        /* Request for NIT other section with NIT = TixExtn */
                        TraceNotice(m,"%s : %d :: Requesting filter for NID = %d", __FILE__, __LINE__, TidExtn);
						#ifndef __cplusplus
                        DmxROMData[dmx].SubscrId[NITOTHER_INDEX]  = sec_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NITT_OTHER_TABLE_ID , TidExtn, NITT_OTHER_TABLE_ID, (HsvSectionCallback) FNADDR(Nit_Parser_Parser));             
						#else
						DmxROMData[dmx].SubscrId[NITOTHER_INDEX]  = sec_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NITT_OTHER_TABLE_ID , TidExtn, NITT_OTHER_TABLE_ID, FNADDR(Nit_Parser_Parser));             
						#endif
                        DmxROMData[dmx].TablesReq |= NIT_OTHER_REQ;
                    }
                    else
                    {
                        TraceNotice(m,"%s %d requested NID by user is NIT Actual so don't request for NIT other <%d %d>", __FUNCTION__, __LINE__, DmxROMData[dmx]. NetworkId, TidExtn);
                    }
                }
                else
                {
                    TraceInfo(m,"%s : %d :: **********IMPOSSIBLE*********", __FILE__, __LINE__);
                }
            }
        }
        else
        {
			if (NitActualAllocated == FALSE)
			{
				/* Request for NIT actual section */
				TraceInfo(m,"%s : %d :: Requesting filter for NIT Actual", __FILE__, __LINE__);
				#ifndef __cplusplus
				DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NITT_ACTUAL_TABLE_ID , NITT_ACTUAL_TABLE_ID, (HsvSectionCallback)  FNADDR(Nit_Parser_Parser));
				#else
				DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NITT_ACTUAL_TABLE_ID , NITT_ACTUAL_TABLE_ID, FNADDR(Nit_Parser_Parser));
				#endif
				DmxROMData[dmx].TablesReq |= NIT_ACTUAL_REQ;
			}
        }
        ASSERT(DmxROMData[dmx].SubscrId[NITACTUAL_INDEX] != HSV_INVALID_SCT_REQUEST);     

        DmxROMData[dmx].Version    [ NITACTUAL_INDEX ]      =   (Nat8)(HSV_INVALID_VERSION);      
    }
}


void CHsvDvbNIT_Priv::ena_Disable(HsvDemux dmx)
{

    /* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[NITACTUAL_INDEX]))  
    {
        if( DmxROMData[dmx].SubscrId[NITACTUAL_INDEX] != HSV_INVALID_SCT_REQUEST )
        {
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]);
            DmxROMData[dmx].SubscrId[NITACTUAL_INDEX] = HSV_INVALID_SCT_REQUEST ;
        }
    }

    if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[NITOTHER_INDEX]))  
    {
        if( DmxROMData[dmx].SubscrId[NITOTHER_INDEX] != HSV_INVALID_SCT_REQUEST )
        {
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),DmxROMData[dmx].SubscrId[NITOTHER_INDEX]);
            DmxROMData[dmx].SubscrId[NITOTHER_INDEX] = HSV_INVALID_SCT_REQUEST ;
        }
    }

    InitActualNetworkID(dmx);
    InitNetworkName(dmx);
    InitActualNITVer(dmx);
    InitActualNetworkLCN(dmx);
    InitLinkageInfo(dmx);
    InitActualCableDS(dmx);
    InitActualTSRelocateDS(dmx);
    InitActualServiceListDS(dmx);
    InitActualNetworkLCN2(dmx);
    InitActualNetworkHDSLCN(dmx);
    InitOtherNetworkIDInfo(dmx);
    InitOtherNetworkLCN(dmx);
    InitOtherLinkageInfo(dmx);
    InitOtherCableDS(dmx);
    InitOtherServiceListDS(dmx);
    InitOtherNetworkLCN2(dmx);
    InitNetworkSRVCATRB ( dmx);  
    InitNetworkFreqList (dmx);
    InitOtherNetworkHDSLCN(dmx);
    InitTargetRegionDesc(dmx);
    InitTargetRegionNameDesc(dmx);
	InitActualNetworkLCN2FavoriteList(dmx);
	InitActualTsID(dmx);

    DmxROMData[dmx].TablesReq = DmxROMData[dmx].TablesRecvd = 0;
}


void CHsvDvbNIT_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED( dmx );
}

     HSVCOMPAREKEY(nitlcnmainconf, Primary,     HsvNITLCN, Original_NetworkId)

     HSVCOMPAREKEY(nitlcnmainconf, Secondary,   HsvNITLCN, Tsid)

  HSVCOMPAREKEY(nitlcnmainconf, Teritiary,   HsvNITLCN, ServiceId)
     /*Below is not used */


	      HSVCOMPAREKEY(nitlcnsubconf, Primary,     HsvNITLCN, Original_NetworkId)

     HSVCOMPAREKEY(nitlcnsubconf, Secondary,   HsvNITLCN, Tsid)

  HSVCOMPAREKEY(nitlcnsubconf, Teritiary,   HsvNITLCN, ServiceId)

HSVCOMPAREKEY(nitlcnsubconf, Quaternary, HsvNITLCN, ServiceId)
      /*Nat8 nitlcnmainconf_CompareTeritiaryKey( Nat32 key, Address data )
        {
        return nitlcnmainconf_Equal;
        }*/


      HSVCOMPAREKEY(nitlinkmainconf, Primary,   HsvNITLinkageInfo,Original_NetworkId)

      HSVCOMPAREKEY(nitlinkmainconf, Secondary, HsvNITLinkageInfo,Tsid)

  HSVCOMPAREKEY(nitlinkmainconf, Teritiary, HsvNITLinkageInfo,LinkageType)
      /*Below is not used */

      HSVCOMPAREKEY(nitlinksubconf, Primary,   HsvNITLinkageInfo,Original_NetworkId)

      HSVCOMPAREKEY(nitlinksubconf, Secondary, HsvNITLinkageInfo,Tsid)

  HSVCOMPAREKEY(nitlinksubconf, Teritiary, HsvNITLinkageInfo,LinkageType)

  HSVCOMPAREKEY(nitlinksubconf, Quaternary, HsvNITLinkageInfo,LinkageType)



      HSVCOMPAREKEY(nitcablemainconf, Primary,   HsvNITCableDS,Original_NetworkId)

      HSVCOMPAREKEY(nitcablemainconf, Secondary, HsvNITCableDS,Tsid)

  HSVCOMPAREKEY(nitcablemainconf, Teritiary, HsvNITCableDS,NetworkId)
      /*Below is not used */

      HSVCOMPAREKEY(nitcablesubconf, Primary,   HsvNITCableDS,Original_NetworkId)

      HSVCOMPAREKEY(nitcablesubconf, Secondary, HsvNITCableDS,Tsid)

  HSVCOMPAREKEY(nitcablesubconf, Teritiary, HsvNITCableDS,NetworkId)

  HSVCOMPAREKEY(nitcablesubconf, Quaternary, HsvNITCableDS,NetworkId)

	    

  HSVCOMPAREKEY(nitntwkidconf, Primary, HsvNITOtherNetworkIdInfo,NetworkId)
      /*Below is not used*/

      HSVCOMPAREKEY(nitntwkidconf, Secondary, HsvNITOtherNetworkIdInfo,NetworkId)

      HSVCOMPAREKEY(nitntwkidconf, Teritiary, HsvNITOtherNetworkIdInfo,NetworkId)

	  

      HSVCOMPAREKEY(nitfreqlistconf, Primary,     HsvNITFreqList,Original_NetworkId)

      HSVCOMPAREKEY(nitfreqlistconf, Secondary,   HsvNITFreqList,Tsid)

  HSVCOMPAREKEY(nitfreqlistconf, Teritiary,   HsvNITFreqList,Frequency)
      
	  /*Below is not used*/

	  

      HSVCOMPAREKEY(nitlcn2mainconf, Primary,     HsvNITLCN2,  CountryCode)

      HSVCOMPAREKEY(nitlcn2mainconf, Secondary,   HsvNITLCN2,   ChannelListId)

  HSVCOMPAREKEY(nitlcn2mainconf, Teritiary,   HsvNITLCN2,   ServiceId)
  

      HSVCOMPAREKEY(nitlcn2subconf, Primary,     HsvNITLCN2,  CountryCode)

      HSVCOMPAREKEY(nitlcn2subconf, Secondary,   HsvNITLCN2,   ChannelListId)

  HSVCOMPAREKEY(nitlcn2subconf, Teritiary,   HsvNITLCN2,   ServiceId)

  HSVCOMPAREKEY(nitlcn2subconf, Quaternary,   HsvNITLCN2,   Tsid)


  
      HSVCOMPAREKEY(nithdslcnmainconf, Primary,     HsvNITHDSLCN, Original_NetworkId)

      HSVCOMPAREKEY(nithdslcnmainconf, Secondary,   HsvNITHDSLCN, Tsid)

  HSVCOMPAREKEY(nithdslcnmainconf, Teritiary,   HsvNITHDSLCN, ServiceId)
      /*Below is not used*/

      HSVCOMPAREKEY(nithdslcnsubconf, Primary,     HsvNITHDSLCN, Original_NetworkId)

      HSVCOMPAREKEY(nithdslcnsubconf, Secondary,   HsvNITHDSLCN, Tsid)

  HSVCOMPAREKEY(nithdslcnsubconf, Teritiary,   HsvNITHDSLCN, ServiceId)

    HSVCOMPAREKEY(nithdslcnsubconf, Quaternary,   HsvNITHDSLCN, ServiceId)
	  
	        /*Below is not used*/

	HSVCOMPAREKEY(nitlcn2favoriteconf, Primary,	 HsvNITFAVORITECHANNELLISTLCNV2,  CountryCode)

	HSVCOMPAREKEY(nitlcn2favoriteconf, Secondary,	 HsvNITFAVORITECHANNELLISTLCNV2,   ChannelListId)

	HSVCOMPAREKEY(nitlcn2favoriteconf, Teritiary,	 HsvNITFAVORITECHANNELLISTLCNV2,   ServiceId)

	HSVCOMPAREKEY(nitlcn2favoriteconf, Quaternary,	 HsvNITFAVORITECHANNELLISTLCNV2,   Tsid)


      HSVCOMPAREKEY(nitsrvcatrbmainconf, Primary,     HsvNITSRVCATRB, Original_NetworkId)

      HSVCOMPAREKEY(nitsrvcatrbmainconf, Secondary,   HsvNITSRVCATRB, Tsid)

  HSVCOMPAREKEY(nitsrvcatrbmainconf, Teritiary,   HsvNITSRVCATRB, ServiceId)
      /*Below is not used*/




      HSVCOMPAREKEY(nitsrvclstmainconf, Primary,     HsvNITServiceList, Original_NetworkId)

      HSVCOMPAREKEY(nitsrvclstmainconf, Secondary, HsvNITServiceList, Tsid)

  HSVCOMPAREKEY(nitsrvclstmainconf, Teritiary,   HsvNITServiceList, ServiceId)
      /*Below is not used*/

      HSVCOMPAREKEY(nitsrvclstsubconf, Primary,     HsvNITServiceList, Original_NetworkId)

      HSVCOMPAREKEY(nitsrvclstsubconf, Secondary, HsvNITServiceList, Tsid)

  HSVCOMPAREKEY(nitsrvclstsubconf, Teritiary,   HsvNITServiceList, ServiceId)

   HSVCOMPAREKEY(nitsrvclstsubconf, Quaternary,   HsvNITServiceList, ServiceId)



      HSVCOMPAREKEY(nittsrelocatemainconf, Primary,   HsvNITTSRelocated,Original_NetworkId)

      HSVCOMPAREKEY(nittsrelocatemainconf, Secondary, HsvNITTSRelocated,Tsid)

      HSVCOMPAREKEY(nittsrelocatemainconf, Teritiary, HsvNITTSRelocated,NetworkId)

  

      HSVCOMPAREKEY(nittargetregionconf, Primary,     HsvNITTargetRegion,   OnId)

      HSVCOMPAREKEY(nittargetregionconf, Secondary,   HsvNITTargetRegion,   Tsid)

      HSVCOMPAREKEY(nittargetregionconf, Teritiary,   HsvNITTargetRegion,   NetworkId)

  

      HSVCOMPAREKEY(nittargetregionnameconf, Primary,       HsvNITTargetRegionName, Primary.RegionCode)

      HSVCOMPAREKEY(nittargetregionnameconf, Secondary,     HsvNITTargetRegionName, Primary.Secondary.RegionCode)

      HSVCOMPAREKEY(nittargetregionnameconf, Teritiary,     HsvNITTargetRegionName, Primary.Secondary.Tertiary.RegionCode)

		/* Canal Digital CR */
	  HSVCOMPAREKEY(nitactualtsidconf, Primary,     HsvActualTsId, Original_NetworkId)

      HSVCOMPAREKEY(nitactualtsidconf, Secondary, HsvActualTsId, Tsid)

	  HSVCOMPAREKEY(nitactualtsidconf, Teritiary, HsvActualTsId, Tsid)

	   HSVCOMPAREKEY(nitactualtsidconf, Quaternary, HsvActualTsId, Tsid)

	 /* Canal Digital CR */
	 
#ifdef __cplusplus

  	  HSVCOMPAREKEY(nitlcnmainconf, Quaternary, HsvNITLCN, ServiceId)

  HSVCOMPAREKEY(nitlinkmainconf, Quaternary, HsvNITLinkageInfo,LinkageType)

	  HSVCOMPAREKEY(nitcablemainconf, Quaternary, HsvNITCableDS,NetworkId)

  HSVCOMPAREKEY(nitntwkidconf, Quaternary, HsvNITOtherNetworkIdInfo,NetworkId)

  HSVCOMPAREKEY(nitfreqlistconf, Quaternary,   HsvNITFreqList,Frequency)

  HSVCOMPAREKEY(nitlcn2mainconf, Quaternary,   HsvNITLCN2,   Tsid)

  HSVCOMPAREKEY(nithdslcnmainconf, Quaternary,   HsvNITHDSLCN, ServiceId)

  HSVCOMPAREKEY(nitsrvcatrbmainconf, Quaternary,   HsvNITSRVCATRB, ServiceId)

  HSVCOMPAREKEY(nitsrvclstmainconf, Quaternary,   HsvNITServiceList, ServiceId)

	HSVCOMPAREKEY(nittsrelocatemainconf, Quaternary, HsvNITTSRelocated,NetworkId)

  HSVCOMPAREKEY(nittargetregionconf, Quaternary, HsvNITTargetRegion, CountryCode)

  HSVCOMPAREKEY(nittargetregionnameconf, Quaternary, HsvNITTargetRegionName, Langcode)

  #else

  Nat8 CHsvDvbNIT_Priv::nittargetregionconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nittargetregionnameconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nitlcnmainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nitlinkmainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nitcablemainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nitntwkidconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

 Nat8 nitlcn2mainconf_CompareQuaternaryKey( Nat32 key, Address data )
 {
    UNUSED (key);
    UNUSED (data);
    return FALSE;
 }

  Nat8 CHsvDvbNIT_Priv::nitfreqlistconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nittsrelocatemainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nitsrvclstmainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nitsrvcatrbmainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }

  Nat8 CHsvDvbNIT_Priv::nithdslcnmainconf_CompareQuaternaryKey( Nat32 key, Address data )
  {
      UNUSED (key);
      UNUSED (data);
      return FALSE;
  }
   Nat8 nitlcn2favoriteconf_CompareQuaternaryKey( Nat32 key, Address data )
 {
    UNUSED (key);
    UNUSED (data);
    return FALSE;
 }
#endif


Bool CHsvDvbNIT_Priv::ipop_PopulateNIT ( HsvDemux dmx , Address pNit_Parser, int code )
{
    int retval = TRUE;
    TypeNit_Parser* NetWkTable = (TypeNit_Parser*)pNit_Parser;

//    TraceInfo(m,"ipop_PopulateNIT");
    if(NITT_ACTUAL_TABLE_ID == NetWkTable->TableId)
    {
        PopulateActualNetworkID(dmx, NetWkTable, code);
        PopulateNetworkName(dmx, NetWkTable, code);
        PopulateActualNITVer(dmx, NetWkTable, code);
        PopulateActualNetworkLCN(dmx, NetWkTable, code);
        PopulateLinkageInfo(dmx, NetWkTable, code);
        PopulateActualCableDS(dmx, NetWkTable, code);
        PopulateActualTSRelocateDS(dmx, NetWkTable, code);
        PopulateActualServiceListDS(dmx,NetWkTable, code);
        PopulateNetworkLCN2(dmx, NetWkTable, code);
        PopulateNetworkHDSLCN(dmx, NetWkTable, code);
        PopulateNetworkSRVCATRB(dmx, NetWkTable, code);    
        PopulateFreqList(dmx, NetWkTable, code);
        PopulateTargetRegionDesc(dmx, NetWkTable, code);
        PopulateTargetRegionNameDesc(dmx, NetWkTable, code);
		PopulateChannelListId(dmx, NetWkTable, code);
		PopulateActualTsId(dmx, NetWkTable, code);
    }
    else if(NITT_OTHER_TABLE_ID == NetWkTable->TableId)
    {
        PopulateOtherNetworkIDInfo(dmx, NetWkTable, code);
        if(ins_InstallationModePreScan != ins_GetInstallationMode())
        {
            PopulateOtherNetworkLCN(dmx, NetWkTable, code);
            PopulateOtherLinkageInfo(dmx, NetWkTable, code);
            PopulateOtherCableDS(dmx, NetWkTable, code);
            PopulateOtherNetworkLCN2(dmx, NetWkTable, code);
            PopulateOtherServiceListDS(dmx, NetWkTable, code);
            PopulateOtherNetworkHDSLCN(dmx, NetWkTable, code);
        }
    }

    if( sec_TableCompleted  &  code )
    {
        if(NITT_ACTUAL_TABLE_ID == NetWkTable->TableId)
        {
            DmxROMData[dmx].TablesRecvd |= NIT_ACTUAL_REQ;
        }
        if(NITT_OTHER_TABLE_ID == NetWkTable->TableId)
        {
            DmxROMData[dmx].TablesRecvd |= NIT_OTHER_REQ;
        }
        /* Only in case of NIT actual or NIT other, notify the change in information */
        if( (NITT_ACTUAL_TABLE_ID == NetWkTable->TableId) || (NITT_OTHER_TABLE_ID == NetWkTable->TableId ))
        {   
            /* generate control notifications */
            if(DmxROMData[dmx].TablesRecvd == DmxROMData[dmx].TablesReq)
            {
                DmxROMData[dmx].TablesReq = 0;
                DmxROMData[dmx].TablesRecvd = 0;
               // if( ctrlN_iPresent())
                {
                    ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT);
                }
            }
            else
            {
				if( (ins_InstallationModePreScan == ins_GetInstallationMode()) && 
					(ins_GetAttributeMode(ins_InstallationModeAutomatic, ins_AttributeNetworkId) == ins_ManualValue) &&
					 ins_ZiggoNetworkDataSet(FALSE))
				{
					HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) networkinfo;
					Nat16 NetworkId = ins_GetAttribute(ins_InstallationModeAutomatic, ins_AttributeNetworkId);
					
					if( (DmxROMData[dmx]. NetworkId == NetworkId) || strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0, &networkinfo))
					{
						DmxROMData[dmx].TablesReq = 0;
						DmxROMData[dmx].TablesRecvd = 0;
						//if( ctrlN_iPresent())
						{
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT);
						}
					}
				}
            }
        }
    }


    return retval;
}

void CHsvDvbNIT_Priv::InitActualNetworkID(HsvDemux dmx)
{
    DmxROMData[dmx].NetworkId = HSV_INVALID_NETWORKID;
}
void CHsvDvbNIT_Priv::InitNetworkName(HsvDemux dmx)
{
    DmxROMData[dmx].NetworkName[0] = 0;
}
void CHsvDvbNIT_Priv::InitActualNITVer(HsvDemux dmx)
{
    DmxROMData[dmx].ActualNITVer = 0xff;
}
void CHsvDvbNIT_Priv::InitActualNetworkLCN(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLcnTableMain);
}
void CHsvDvbNIT_Priv::InitLinkageInfo(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLinkageInfoMain);
}
void CHsvDvbNIT_Priv::InitActualCableDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitCableDSMain);
}
void CHsvDvbNIT_Priv::InitActualTSRelocateDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitTsRelocateTableMain);
}
void CHsvDvbNIT_Priv::InitActualServiceListDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitSrvclstTableMain);
}
void CHsvDvbNIT_Priv::InitActualNetworkLCN2(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLcn2TableMain);
}
void CHsvDvbNIT_Priv::InitActualNetworkHDSLCN(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitHDSLcnTableMain);
}
void CHsvDvbNIT_Priv::InitOtherNetworkIDInfo(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitOtherNetworkIdTable);
}
void CHsvDvbNIT_Priv::InitOtherNetworkLCN(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLcnTableSub);
}
void CHsvDvbNIT_Priv::InitOtherLinkageInfo(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLinkageInfoSub);
}
void CHsvDvbNIT_Priv::InitOtherCableDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitCableDSSub);
}
void CHsvDvbNIT_Priv::InitOtherNetworkLCN2(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLcn2TableSub);
}
void CHsvDvbNIT_Priv::InitOtherServiceListDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitSrvclstTableSub);
}
void CHsvDvbNIT_Priv::InitNetworkSRVCATRB ( HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitSrvcAtrbTableMain);  
}
void CHsvDvbNIT_Priv::InitNetworkFreqList ( HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitFreqList);   
}
void CHsvDvbNIT_Priv::InitOtherNetworkHDSLCN(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitHDSLcnTableSub);
}
void CHsvDvbNIT_Priv::InitTargetRegionDesc( HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitTargetRegion);   
}
void CHsvDvbNIT_Priv::InitTargetRegionNameDesc( HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitTargetRegionName);   
}

void CHsvDvbNIT_Priv::InitActualNetworkLCN2FavoriteList(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitLCN2Favorite);
}
void CHsvDvbNIT_Priv::InitActualTsID(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_NitActualTsId);
}


Bool CHsvDvbNIT_Priv::PopulateActualNetworkID( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
    UNUSED( code );
    if( sec_SctArrived  & code )
    {

        ActualNetworkId = DmxROMData[dmx]. NetworkId  = NetWkTable->NetworkId;
        DmxROMData[dmx].NITActualAvail = TRUE;
        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualNetworkID, dvb, nit),  0, 0, 0, 0); 
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualNetworkID, dvb, nit));
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateActualNITVer( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
    if( sec_SctArrived  &  code )
    {
        DmxROMData[dmx].ActualNITVer = NetWkTable->VersionNo;
		strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualNITVer, dvb, nit),  0, 0, 0, 0); 
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualNITVer, dvb, nit));
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateNetworkName(HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
    int len = 0,i = 0;
    int HsvEvtNull = 0;
    int stringlen = MAX_NETWORK_NAME_SIZE; 

    if( sec_SctArrived  &  code )
    {
        if(NetWkTable->NetworkName_Descriptor.DescriptorValid)
        {  
            Nat8 *NwName = (Nat8 *) NetWkTable->NetworkName_Descriptor.NetworkName;

            len = NetWkTable->NetworkName_Descriptor.NetworkNameLen;
			memset(DmxROMData[dmx].NetworkName,0x00,MAX_NETWORK_NAME_SIZE);
            charsetutil_MbToWcEx( NwName, len, DmxROMData[dmx].NetworkName, &stringlen,charsetutil_ExtractShortName);
            if(stringlen > MAX_NETWORK_NAME_SIZE)
            {
                stringlen = MAX_NETWORK_NAME_SIZE;
            }
			for(i = stringlen; i < MAX_NETWORK_NAME_SIZE; i++)
			{
				DmxROMData[dmx].NetworkName[i] = 0; 
			}
            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(NetworkName, dvb, nit),  0, 0, 0, HsvEvtNull); 
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(NetworkName, dvb, nit));
        }
    }
    return TRUE;
}
Bool CHsvDvbNIT_Priv::PopulateActualTsId(HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
	return PopulateNITTsId(dmx, NetWkTable, HSVSPID(ActualTsID, dvb, nit),srtdbids_NitActualTsId, code);
}
Bool CHsvDvbNIT_Priv::PopulateNITTsId(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
	HsvActualTsId TsIdActual;
	HsvActualTsId tempActual;
	HsvActualTsId DbaseVersion; 

	int tsloop = 0;
	
	while( tsloop < NetWkTable->TsLoopDataNum)
    {
		if(sec_SctArrived  &  code )
	    { 

			   TsIdActual.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
	           TsIdActual.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
			   TsIdActual.VersionNumber      = NetWkTable->VersionNo;

			   if ( srtdb_QueryOnKey( tableid,  TsIdActual.Original_NetworkId,  TsIdActual.Tsid,  0, 0,(Address)(&tempActual) ) )
               {
                  if(FALSE == srtdb_Update(tableid, TsIdActual.Original_NetworkId, TsIdActual.Tsid, 0, 0,(Address)(&TsIdActual) ))
                  {
                  	ASSERT(FALSE);
                  }
		          else
		            {
		                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, TsIdActual.Original_NetworkId, TsIdActual.Tsid, 0, HsvEvtNull); 
		            }
               }
	            else
	            {
	                /* New Record */
	                if(FALSE == srtdb_Insert(tableid, TsIdActual.Original_NetworkId, TsIdActual.Tsid, 0, 0, (Address)(&TsIdActual) ))
	                {
	                    ASSERT(FALSE);
	                }
	                else
	                {
	                    strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, TsIdActual.Original_NetworkId, TsIdActual.Tsid, 0);
	                }
	            }
						
		} else if(sec_TableCompleted  &  code) {
	        int j = srtdb_GetNoOfRecords(tableid) - 1;
	        while( 0 <= j )
	        {
	            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
	            {
	                if((DbaseVersion.VersionNumber != NetWkTable->VersionNo))
	                {
	                    if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0,0))
	                    {  
	                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0);
	                    }
	                    else
	                    {  /* Could not delete */
	                        ASSERT(FALSE);                   
	                    }
	                }
	            }
	            j--;
	        }
        	strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
		}
		tsloop++;	
	}
	return TRUE;
}
Bool CHsvDvbNIT_Priv::PopulateActualTSRelocateDS(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    return PopulateTSRelocateDS(dmx, NetWkTable, HSVSPID(ActualTSRelocated, dvb, nit),srtdbids_NitTsRelocateTableMain, code);
}

Bool CHsvDvbNIT_Priv::PopulateTSRelocateDS(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{

    /* The datatypes are same for both Actual and Other. So using just one instance */
    HsvNITCableDS DbaseVersion; 
    HsvNITCableDS TempVersion;

    int i, HsvEvtNull = 0,j = 0, k = 0;

    if( sec_SctArrived  &  code )
    {       
        int TsRelocatenumOfCableDS = NetWkTable->TSRelocateDescNum;

        for( i = 0; i < TsRelocatenumOfCableDS; i++)
        {
            if (NetWkTable->TSRelocate_Descriptor[i].DescriptorValid ) 
            {
                DbaseVersion.VersionNumber = NetWkTable->VersionNo;
                DbaseVersion.NetworkId = NetWkTable->NetworkId;
                DbaseVersion.NumOfCDSD = 0;

                for( j = 0; j < NetWkTable->TSRelocate_Descriptor[i].TS_RelocateLen ; j++)
                {                   
                    DbaseVersion.Tsid = NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].Transport_Stream_ID;
                    DbaseVersion.Original_NetworkId = NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].Original_Network_ID; 
                    for( k = 0; k < NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].TSDescLen ; k++)
                    {                   

                        Nat32 CDSFrequency = mInterpretFrequencyValue(&(NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].TSDesc[k].Frequency));
                        Nat8 CDSModulation = mInterpretModulationValue(&(NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].TSDesc[k].Modulation));    
                        Nat32 CDSSymbolRate = mInterpretSymbolRate(&(NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].TSDesc[k].SymbolRate));    

                        //TraceInfo(m,"PopulateCDSC::symrate:%d, modln=%d, freq=%d",(int)CDSSymbolRate, CDSModulation, (int)(CDSFrequency >> 4));

                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].Frequency = CDSFrequency;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].Modulation = CDSModulation;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].SymbolRate = CDSSymbolRate;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].FEC_Inner = NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].TSDesc[k].FEC_Inner;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].FEC_Outer = NetWkTable->TSRelocate_Descriptor[i].TS_RelocateDesc[j].TSDesc[k].FEC_Outer;
                        if(mValidateCDS(&DbaseVersion, DbaseVersion.NumOfCDSD))
                        {
                            DbaseVersion.NumOfCDSD++;
                        }
                    }

                    if(DbaseVersion.NumOfCDSD > 0)
                    {
                        if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
                        {
                            if(FALSE == srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion) ))
                            {
                                ASSERT(FALSE);
                            }
                            else
                            {
                                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, HsvEvtNull); 
                            }
                        }
                        else
                        {
                            /* New Record */
                            if(FALSE == srtdb_Insert(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0, (Address)(&DbaseVersion) ))
                            {
                                ASSERT(FALSE);
                            }
                            else
                            {
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
                            }
                        }
                    }
                }
            }
        }   
    }           
    else if(sec_TableCompleted  &  code)
    {
        int j = srtdb_GetNoOfRecords(tableid) - 1;
        while( 0 <= j )
        {
            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
            {
                if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                        (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                {
                    /* delete the record */
                    if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId,0))
                    {  
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
                    }
                    else
                    {  /* Could not delete */
                        ASSERT(FALSE);                   
                    }
                }
            }
            /* decrement to prev index*/
            j--;
        }
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
    }
    else
    {
        /* Do Nothing */
    }
    return TRUE;
}



Bool CHsvDvbNIT_Priv::PopulateOtherNetworkIDInfo( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    HsvNITOtherNetworkIdInfo DbaseVersion, TempVersion; 
    HsvNITOtherNetworkIdInfo OtherNtwkInfo; 
    Nat16 NetworkId = NetWkTable->NetworkId;
    int stringlen = MAX_NETWORK_NAME_SIZE;


    if( sec_SctArrived  &  code )
    {
        if(NetWkTable->TableId == NITT_OTHER_TABLE_ID) 
        {
            OtherNtwkInfo.VersionNumber = NetWkTable->VersionNo;
            OtherNtwkInfo.NetworkId = NetworkId;
			int len = 0;
			 if( NetWkTable->NetworkName_Descriptor.DescriptorValid )
			{
	            Nat8 *NwName = (Nat8 *) NetWkTable->NetworkName_Descriptor.NetworkName;
    	        int len = NetWkTable->NetworkName_Descriptor.NetworkNameLen;
				memset(OtherNtwkInfo.Name,0x00,MAX_NETWORK_NAME_SIZE);
			    charsetutil_MbToWcEx( NwName, len, OtherNtwkInfo.Name, &stringlen , FALSE);
            }
			else 
			{
				memset(OtherNtwkInfo.Name,0x00,MAX_NETWORK_NAME_SIZE);
				 //TraceNotice(m,"[%s] [%d] NetworkId[%d] \n",__FUNCTION__,__LINE__,NetworkId);
				if ( srtdb_QueryOnKey( srtdbids_NitOtherNetworkIdTable, NetworkId, 0 , 0,0, (Address)(&TempVersion) ) )
				{
						memcpy(OtherNtwkInfo.Name, TempVersion.Name, stringlen);
				} 
				else
				{
					OtherNtwkInfo.Name[len] = '\0';
				}	
			}
            if ( srtdb_QueryOnKey( srtdbids_NitOtherNetworkIdTable, NetworkId, 0 , 0,0, (Address)(&TempVersion) ) )
            {
                srtdb_Update(srtdbids_NitOtherNetworkIdTable, NetworkId, 0, 0,0, (Address)(&OtherNtwkInfo) );
                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0, 0); 
            }
            else
            {
                srtdb_Insert( srtdbids_NitOtherNetworkIdTable, NetworkId, 0, 0, 0, (Address)(&OtherNtwkInfo));
                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0);
            }
    }
}
else if(sec_TableCompleted  &  code)
{
    /* Delete logical channels if not present */
    int j = srtdb_GetNoOfRecords(srtdbids_NitOtherNetworkIdTable) - 1;
    while( 0 <= j )
    {
        if(srtdb_QueryOnIndex(srtdbids_NitOtherNetworkIdTable,j,(Address )(&DbaseVersion)))
        {
            /* Every NIT Other could have different versions. So check corresponding Version Numbers */
            if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                    (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
            {
                /* delete the record */
                //TraceInfo(m,"%s: Deleted Other NetworkID = %d",__FUNCTION__,NetworkId);
                if (srtdb_Delete(srtdbids_NitOtherNetworkIdTable, DbaseVersion.NetworkId, 0, 0,0))
                {  
                    strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherNetworkIDInfo, dvb, nit), DbaseVersion.NetworkId, 0, 0);
                }
                else
                {  /* Could not delete */
                    ASSERT(FALSE);                   
                }
            }
        }
        /* decrement to prev index*/
        j--;
    }
    strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherNetworkIDInfo, dvb, nit));
}
return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateActualNetworkLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{

    if(sec_SctArrived  &  code)
    {
        return  PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkLCN, dvb, nit), srtdbids_NitLcnTableMain, code);
    }
    else if( sec_TableCompleted  &  code )
    {
        return PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkLCN, dvb, nit), srtdbids_NitLcnTableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkLCN(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived  &  code)
    {
        return  PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkLCN, dvb, nit), srtdbids_NitLcnTableSub, code);
    }
    else if( sec_TableCompleted  & code )
    {
        return PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkLCN, dvb, nit), srtdbids_NitLcnTableSub, code );
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{

    HsvNITLCN DbaseVersion; 
    HsvNITLCN LogicalChannel; 
    int i = 0, tsloop = 0, j = 0,k=0;
    Nat16 vis_flag;
    int privatedataspecify = 0; 
    Nat16 TempLCNVal;

    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {
            int numlogicalchannelinfo = NetWkTable->TsLoopData[tsloop].LCNDescNum;

            for( i = 0; i < numlogicalchannelinfo; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNLen ; j++)
                    {
                        Nat16 serviceid = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId;
                        if( ((sysset_GetSystemCountry() == cids_CountryUK ) && ( ins_GetMedium() == ins_Terrestrial )) || 
							((ins_GetMedium() == ins_Cable) &&  (sysset_GetSystemCountry() == cids_CountryGermany) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UnityMedia)) ||
							((ins_GetMedium() == ins_Cable) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UPC)) )
                        {
                            // for terrestrial UK we use any LCN's where the previous PDSD in the table was correct (CR brg36mgr#134435)
                            privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].prevPrivateDataSpecifier;
                        }
                        else
                        {
                            // everywhere else we only use the PDSD if it was immediately before this descriptor
                            privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].PrivateDataSpecifier;
                        }

                        TempLCNVal = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue ;
                        Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID, privatedataspecify , TempLCNVal, &vis_flag, LCN_TYPE_V1);    

                        //TraceInfo(m,"Function : %s Line : %d VisFlag : %d SID : %d:LCN = %d",__FUNCTION__,__LINE__,vis_flag,serviceid,lcn);



                        Nat16 vflag =   vis_flag;

                        if(lcn != 0xFFFF)
                        {
                            if (( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) ) )\
								&&(MULTIPLE_LCN_SUPPORTED ?(DbaseVersion.VersionNumber == NetWkTable->VersionNo):(1)))
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if( DbaseVersion.NetworkId == NetWkTable->NetworkId ) 
                                {
                                    Bool LCNChanged = FALSE;
                                    Bool LCNAvailChanged = FALSE; /*fixme: This is not yet parsed */
                                    //int privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].PrivateDataSpecifier;
                                    //Nat16 lcn = NetWkTable->TsLoopData[i].LCN_Descriptor[i].LCNDesc[i].LCNValue;//mInterpretLCNValue(privatedataspec , NetWkTable->TsLoopData[i].LCN_Descriptor[i].LCNDesc[i].LCNValue);    
                                    //Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify , NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue, &vis_flag);    
                                    //Nat16 vflag =   vis_flag;
                                
									if(MULTIPLE_LCN_SUPPORTED)
									{	
										//if LCN is not present add it to the list
										for(k=0;k<MAX_LCNS;k++)
										{
											if((DbaseVersion.LCN[k]==lcn) ||(DbaseVersion.LCN[k] == 0xFFFF))
											{
												break; //lcn is present in the list ||  end of valid LCNs
											}
										}
										
										if((k < MAX_LCNS)&&(DbaseVersion.LCN[k] == 0xFFFF))
										{
											DbaseVersion.LCN[k] = lcn;
											LCNChanged = TRUE;
										}
										
									}
									else
									{
										
										if( DbaseVersion.LogicalChannelNum != lcn)
										{
											DbaseVersion.LogicalChannelNum = lcn;
											LCNChanged = TRUE;
										}
										DbaseVersion.VisibleService     = vflag;
										DbaseVersion.VersionNumber = NetWkTable->VersionNo;
									}
                                    
                                
                                    
                                
                                    srtdb_Update(tableid,NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) );
                                
                                    if( FALSE != LCNChanged )
                                    {
                                        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid, 0); 
                                    }
                                    else
                                    {
                                        if( FALSE != LCNAvailChanged )
                                        {
                                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid, 0);  
                                        }
                                    }
                                }
                                else
                                {   /* New Record */
                                }
                            }
                            else
                            {   /* New Record */
                                //TraceNotice(m,"%s::New LCN added = %d for svcid = %d, ntk id = %d\r\n", __FUNCTION__,lcn,NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId,NetWkTable->NetworkId);
                                LogicalChannel.NetworkId          = NetWkTable->NetworkId;
                                LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                                LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                                LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId;
                                if(MULTIPLE_LCN_SUPPORTED)
								{
									for(k=0;k<MAX_LCNS;k++)
									{
										LogicalChannel.LCN[k] = 0xFFFF;
									}									
									LogicalChannel.LCN[0]  = lcn;
								}
								else
								{
									LogicalChannel.LogicalChannelNum  = lcn;
								}
                                LogicalChannel.VisibleService     = vflag;
                                LogicalChannel.VersionNumber      = NetWkTable->VersionNo;
                                srtdb_Insert( tableid, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId , LogicalChannel.ServiceId , (Address)(&LogicalChannel));
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId);
                            }
                        }
                    }
                }
            }
        }
        else if(sec_TableCompleted  &  code)
        {
            /* Delete logical channels if not present */
            int j = srtdb_GetNoOfRecords(tableid) - 1;
            while( 0 <= j )
            {
                if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
                {
                    if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                            (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                    {
                        /* delete the record */
						if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.ServiceId))
                        {  
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                        else
                        {  /* Could not delete */
                            ASSERT(FALSE);                   
                        }
                    }
                }
                /* decrement to prev index*/
                j--;
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
        }
        else
        {
            /* Do Nothing */
        }
        tsloop++;
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateActualCableDS(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    return PopulateCableDSPrivate(dmx, NetWkTable, HSVSPID(ActualCableDS, dvb, nit),srtdbids_NitCableDSMain, code);
}

Bool CHsvDvbNIT_Priv::PopulateOtherCableDS( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    return  PopulateCableDSPrivate(dmx, NetWkTable, HSVSPID(OtherCableDS, dvb, nit),srtdbids_NitCableDSSub, code);
}

Bool CHsvDvbNIT_Priv::PopulateCableDSPrivate(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{

    /* The datatypes are same for both Actual and Other. So using just one instance */
    HsvNITCableDS DbaseVersion; 
    HsvNITCableDS TempVersion;

    int i, HsvEvtNull = 0,j = 0;
    int tsloop = 0;

    if( sec_SctArrived  &  code )
    {
        while ( tsloop < NetWkTable->TsLoopDataNum)
        {
            int numOfCableDS = NetWkTable->TsLoopData[tsloop].CDSDDescNum;

            for( i = 0; i < numOfCableDS; i++)
            {
                if (NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].DescriptorValid ) 
                {
                    DbaseVersion.VersionNumber = NetWkTable->VersionNo;
                    DbaseVersion.NetworkId = NetWkTable->NetworkId;
                    DbaseVersion.Tsid = NetWkTable->TsLoopData[tsloop].TSID;
                    DbaseVersion.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                    DbaseVersion.NumOfCDSD = 0;

                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].CDSDLen ; j++)
                    {                   
                        Nat32 CDSFrequency = mInterpretFrequencyValue(&(NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].Frequency));
                        Nat8 CDSModulation = mInterpretModulationValue(&(NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].Modulation));    
                        Nat32 CDSSymbolRate = mInterpretSymbolRate(&(NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].SymbolRate));    


                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].Frequency =CDSFrequency;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].Modulation =CDSModulation;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].SymbolRate =CDSSymbolRate;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].FEC_Inner = NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].FEC_Inner;
                        DbaseVersion.CDSD[DbaseVersion.NumOfCDSD].FEC_Outer = NetWkTable->TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].FEC_Outer;
                        if(mValidateCDS(&DbaseVersion, DbaseVersion.NumOfCDSD))
                        {
                            DbaseVersion.NumOfCDSD++;
                        }
                    }

                    if(DbaseVersion.NumOfCDSD > 0)
                    {
                        if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
                        {
                            if(FALSE == srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion) ))
                            {
                                ASSERT(FALSE);
                            }
                            else
                            {
                                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, HsvEvtNull); 
                            }
                        }
                        else
                        {
                            /* New Record */
                            if(FALSE == srtdb_Insert(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion) ))
                            {
                                ASSERT(FALSE);
                            }
                            else
                            {
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
                            }
                        }
                    }
                }
            }
            tsloop++;
        }   
    }   
    else if(sec_TableCompleted  &  code)
    {
        int j = srtdb_GetNoOfRecords(tableid) - 1;
        while( 0 <= j )
        {
            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
            {
                if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                        (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                {
                    /* delete the record */
                    if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId,0))
                    {  
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
                    }
                    else
                    {  /* Could not delete */
                        ASSERT(FALSE);                   
                    }
                }
            }
            /* decrement to prev index*/
            j--;
        }
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
    }
    else
    {
        /* Do Nothing */
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived  &  code)
    {
        return PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(ActualNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableMain, code);
    }
    else if(sec_TableCompleted  &  code)
    {
        return   PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(ActualNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived  &  code)
    {
        return  PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(OtherNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableSub, code);
    }
    else if(sec_TableCompleted  &  code)
    {
        return PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(OtherNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableSub, code);
    }
    return TRUE;

}

	Bool CHsvDvbNIT_Priv::PopulateNetworkLogicalChannelV2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
	{

		HsvNITFAVORITECHANNELLISTLCNV2 DbaseVersion; 
		HsvNITFAVORITECHANNELLISTLCNV2 LogicalChannel; 
		int i,j,k,l;
		Nat16 vis_flag;
		int tsloop = 0;
		int privatedataspecify = 0; 
		Nat16 TempLcnVal;
		int stringlen = MAX_CHANNEL_LIST_NAME_SIZE; 
		//TraceNotice(m,"NetWkTable->TsLoopDataNum: %d", NetWkTable->TsLoopDataNum);
		memset(&LogicalChannel,0x00,sizeof(HsvNITFAVORITECHANNELLISTLCNV2));
		while ( tsloop < NetWkTable->TsLoopDataNum)
		{
			if( sec_SctArrived  &  code )
			{
				int numlogicalchanne2linfo = NetWkTable->TsLoopData[tsloop].LCN2DescNum;
				//TraceNotice(m,"%s:numlogicalchanne2linfo: %d",__FUNCTION__,numlogicalchanne2linfo);
				for( i = 0; i < numlogicalchanne2linfo; i++)
				{
					if(NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].DescriptorValid)
					{
						for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelListLen ; j++)
						{
							privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].PrivateDataSpecifier;
							//TraceInfo(m,"Function : %s Line : %d privatedataspecify : %d",__FUNCTION__,__LINE__,privatedataspecify);

							Nat32  countrycode   = mInterpretCountryCode(NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Country_Code);

							Nat8  channellistid = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_ID;
							Nat8 *ChannelListIdName = (Nat8 *) NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name;
							int len=NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_NameLngth;

							memset(LogicalChannel.ChannelListName,0x00,MAX_CHANNEL_LIST_NAME_SIZE);
							stringlen = MAX_CHANNEL_LIST_NAME_SIZE;
							charsetutil_MbToWcEx( ChannelListIdName, len, LogicalChannel.ChannelListName, &stringlen,FALSE);
							if(stringlen > MAX_CHANNEL_LIST_NAME_SIZE){
								stringlen = MAX_CHANNEL_LIST_NAME_SIZE;
							}
							LogicalChannel.ChannelListName[stringlen] = 0;
							for( k = 0; k < NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2DescLen ; k++)
							{

								TempLcnVal = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].LCNValue ;
								Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify , TempLcnVal, &vis_flag, LCN_TYPE_V2);           
								Nat16 vflag =   vis_flag;         
								
								if (( srtdb_QueryOnKey( tableid, countrycode, channellistid, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId, NetWkTable->TsLoopData[tsloop].TSID,(Address)(&DbaseVersion) ) ))
								{
									/* Record Exists - Update the information & notify if needed*/
									Bool LCNChanged = FALSE;
									
										if(DbaseVersion.LCN != lcn ) 
										{
											DbaseVersion.LCN = lcn;
											LCNChanged = TRUE;
										}
										DbaseVersion.VisibleService     = vflag;                                  
										DbaseVersion.VersionNumber = NetWkTable->VersionNo;
									//TraceNotice (m, " Update:CountryCode %d ChannelListID %d", countrycode, channellistid);
									
									
									if(srtdb_Update(tableid, countrycode, channellistid, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId,NetWkTable->TsLoopData[tsloop].TSID, (Address)(&DbaseVersion) ))
									{
									}
									
									if(LCNChanged)
									{
										strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, countrycode,channellistid, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId, NetWkTable->TsLoopData[tsloop].TSID); 
									}
								  
									
								}
								else
								{   /* New Record */
									//LogicalChannel.NetworkId          = NetWkTable->NetworkId;
									LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
									LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
									LogicalChannel.ChannelListId      = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_ID;
									LogicalChannel.CountryCode        = countrycode;
									LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId;
									LogicalChannel.LCN  = lcn;
									LogicalChannel.VisibleService     = vflag;
									LogicalChannel.VersionNumber      = NetWkTable->VersionNo;
									//TraceInfo(m,"%s:%d :: SID=%d LCN=%d ChannelList =%d", __FUNCTION__, __LINE__, LogicalChannel.ServiceId, LogicalChannel.LCN,LogicalChannel.ChannelListId);
									srtdb_Insert( tableid, LogicalChannel.CountryCode,LogicalChannel.ChannelListId, LogicalChannel.ServiceId,LogicalChannel.Tsid, (Address)(&LogicalChannel));
									strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, LogicalChannel.CountryCode, LogicalChannel.Original_NetworkId, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId);
								}
							}
						}
					}
				}
			}     

			else if(sec_TableCompleted  &  code)
			{
				/* Delete logical channels if not present */
				int j = srtdb_GetNoOfRecords(tableid) - 1;
				while( 0 <= j )
				{
					if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
					{
						if( (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
						{
							/* delete the record */
							if (srtdb_Delete(tableid, DbaseVersion.CountryCode, DbaseVersion.ChannelListId, 0,0))
							{  
								//TraceInfo(m,"Deleted the lcn = %d",DbaseVersion.LCN);
								strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.CountryCode, DbaseVersion.ChannelListId, DbaseVersion.ServiceId);
							}
							else
							{  /* Could not delete */
								ASSERT(FALSE);                   
							}
						}
					}
					/* decrement to prev index*/
					j--;
				}
				strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
			}
			else
			{
				/* Do Nothing */
			}

			tsloop++;
		}  

		return TRUE;

	}


Bool CHsvDvbNIT_Priv::PopulateChannelListId( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
	if(sec_SctArrived  &  code)
	{
	return  PopulateNetworkLogicalChannelV2(dmx, NetWkTable, HSVSPID(FavoriteChannelListLCNV2, dvb, nit),srtdbids_NitLCN2Favorite, code);
	}
	else if(sec_TableCompleted  &  code)
	{
	return PopulateNetworkLogicalChannelV2(dmx, NetWkTable, HSVSPID(FavoriteChannelListLCNV2, dvb, nit),srtdbids_NitLCN2Favorite, code);
	}
	return TRUE;

}

Bool CHsvDvbNIT_Priv::PopulateLogicalChannel2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{

    HsvNITLCN2 DbaseVersion; 
    HsvNITLCN2 LogicalChannel; 
    int i,j,k,l;
    Nat16 vis_flag;
    int tsloop = 0;
    int privatedataspecify = 0; 
    Nat16 TempLcnVal;
    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {
            int numlogicalchanne2linfo = NetWkTable->TsLoopData[tsloop].LCN2DescNum;
            for( i = 0; i < numlogicalchanne2linfo; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelListLen ; j++)
                    {
						if( ((ins_GetMedium() == ins_Cable) &&  (sysset_GetSystemCountry() == cids_CountryGermany) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UnityMedia)) ||
							((ins_GetMedium() == ins_Cable) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UPC)) )
						{
							privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].prevPrivateDataSpecifier;
						}
						else
						{
							privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].PrivateDataSpecifier;
						}


                        Nat32  countrycode   = mInterpretCountryCode(NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Country_Code);

                        Nat8  channellistid = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_ID;
                        for( k = 0; k < NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2DescLen ; k++)
                        {

                            TempLcnVal = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].LCNValue ;
                            Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify , TempLcnVal, &vis_flag, LCN_TYPE_V2);             

                            Nat16 vflag =   vis_flag;         
                            

                            if (( srtdb_QueryOnKey( tableid, countrycode, channellistid, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId, NetWkTable->TsLoopData[tsloop].TSID,(Address)(&DbaseVersion) ) )\
								&&(MULTIPLE_LCN_SUPPORTED ?(DbaseVersion.VersionNumber == NetWkTable->VersionNo):(1)))
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                Bool LCNChanged = FALSE;
                                
								if(MULTIPLE_LCN_SUPPORTED)
								{	
									//if LCN is not present add it to the list
									for(l=0;l<MAX_LCNS;l++)
									{
										if((DbaseVersion.LCN[l]==lcn) ||(DbaseVersion.LCN[l] == 0xFFFF))
										{
											break; //lcn is present in the list ||  end of valid LCNs
										}
									}
									
									if((l < MAX_LCNS)&&(DbaseVersion.LCN[l] == 0xFFFF))
									{
										DbaseVersion.LCN[l] = lcn;
										LCNChanged = TRUE;
									}
									
								}
								else
								{
									
									if(DbaseVersion.LogicalChannelNum != lcn ) 
									{
										DbaseVersion.LogicalChannelNum = lcn;
										LCNChanged = TRUE;
									}
									DbaseVersion.VisibleService     = vflag;                                  
									DbaseVersion.VersionNumber = NetWkTable->VersionNo;
								}
								
                                
                                
                                if(srtdb_Update(tableid, countrycode, channellistid, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId,NetWkTable->TsLoopData[tsloop].TSID, (Address)(&DbaseVersion) ))
								{
								}
                                
                                if(LCNChanged)
                                {
									strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, countrycode,channellistid, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId, NetWkTable->TsLoopData[tsloop].TSID); 
								}
                              
                                
                            }
                            else
                            {   /* New Record */
                                LogicalChannel.NetworkId          = NetWkTable->NetworkId;
                                LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                                LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                                LogicalChannel.ChannelListId      = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_ID;
                                LogicalChannel.CountryCode        = countrycode;
                                LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId;
                                if(MULTIPLE_LCN_SUPPORTED)
								{
									for(l=0;l<MAX_LCNS;l++)
									{
										LogicalChannel.LCN[l] = 0xFFFF;
									}

									LogicalChannel.LCN[0] = lcn;
									
								}
								else
								{
									LogicalChannel.LogicalChannelNum  = lcn;
								}
                                LogicalChannel.VisibleService     = vflag;
                                LogicalChannel.VersionNumber      = NetWkTable->VersionNo;

                                //TraceInfo(m,"%s:%d :: SID=%d LCN=%d", __FUNCTION__, __LINE__, LogicalChannel.ServiceId, LogicalChannel.LogicalChannelNum);

                                srtdb_Insert( tableid, LogicalChannel.CountryCode, LogicalChannel.ChannelListId, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId, NetWkTable->TsLoopData[tsloop].TSID, (Address)(&LogicalChannel));

                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, LogicalChannel.CountryCode, LogicalChannel.ChannelListId, NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].ServiceId);
                            }
                        }
                    }
                }
            }
        }     

        else if(sec_TableCompleted  &  code)
        {
            /* Delete logical channels if not present */
            int j = srtdb_GetNoOfRecords(tableid) - 1;
            while( 0 <= j )
            {
                if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
                {
                    if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                            (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                    {
                        /* delete the record */
                        if (srtdb_Delete(tableid, DbaseVersion.CountryCode, DbaseVersion.ChannelListId, 0,0))
                        {  
                            //TraceInfo(m,"Deleted the lcn = %d",DbaseVersion.LogicalChannelNum);
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.CountryCode, DbaseVersion.ChannelListId, DbaseVersion.ServiceId);
                        }
                        else
                        {  /* Could not delete */
                            ASSERT(FALSE);                   
                        }
                    }
                }
                /* decrement to prev index*/
                j--;
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
        }
        else
        {
            /* Do Nothing */
        }

        tsloop++;
    }  

    return TRUE;

}

Bool CHsvDvbNIT_Priv::PopulateNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived  &  code)
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableMain, code);
    }

    else if( sec_TableCompleted  & code )
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived  &  code)
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableSub, code);
    }

    else if( sec_TableCompleted  &  code )
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableSub, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateHDSLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
    HsvNITHDSLCN DbaseVersion; 
    HsvNITHDSLCN LogicalChannel; 
    int i;
    int j;
    Nat16 vis_flag; 
    int tsloop = 0;
	Bool ProcessValidLCN=TRUE;
    //TraceInfo(m,"Function : %s Line : %d",__FUNCTION__,__LINE__);
    while ( tsloop < NetWkTable->TsLoopDataNum)
    {   
        if( sec_SctArrived  &  code )
        {
            int NumHDSLCNInfo = NetWkTable->TsLoopData[tsloop].HDSLCNDescNum;

            for( i = 0; i < NumHDSLCNInfo; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].HDSLCNLen ; j++)
                    {
                        Nat16 serviceid = NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].HDSLCNDesc[j].Service_ID;
                        int privatedataspecify = 0;
                        if( ((sysset_GetSystemCountry() == cids_CountryUK ) && ( ins_GetMedium() == ins_Terrestrial )) || 
							((ins_GetMedium() == ins_Cable) &&  (sysset_GetSystemCountry() == cids_CountryGermany) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UnityMedia)) ||
							((ins_GetMedium() == ins_Cable) && (ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_UPC)) )
                        {
                           
                            privatedataspecify = NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].prevPrivateDataSpecifier;
                        }
                        else
                        {
                            
                            privatedataspecify = NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].PrivateDataSpecifier;
                        }
						if((sysset_GetSystemCountry() == cids_CountryUK ) && ( ins_GetMedium() == ins_Terrestrial )&&(privatedataspecify!=0x233A))
						{
						ProcessValidLCN=FALSE;
						}	
						if(ProcessValidLCN)
						{
                        Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify , NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].HDSLCNDesc[j].LCNValue, &vis_flag, LCN_TYPE_HDS);              
                        Nat16 vflag =   vis_flag;

                        if ( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID,NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) ) )
                        {
                           
                            if(DbaseVersion.NetworkId == NetWkTable->NetworkId)
                            {
                                Bool LCNChanged = FALSE;

                                if( DbaseVersion.LogicalChannelNum != lcn)
                                {
                                    DbaseVersion.LogicalChannelNum = lcn;
                                    LCNChanged = TRUE;
                                }
                                DbaseVersion.VisibleService     = vflag;  

                                DbaseVersion.VersionNumber = NetWkTable->VersionNo;

                                srtdb_Update(tableid, NetWkTable->TsLoopData[tsloop].ONID,NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) );

                                if(LCNChanged)
                                {
                                    strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, 0); 
                                }

                            }
                        }
                        else
                        {   
                            LogicalChannel.NetworkId          = NetWkTable->NetworkId;
                            LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                            LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                            LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].HDSLCNDesc[j].Service_ID;
                            LogicalChannel.LogicalChannelNum  = lcn;
                            LogicalChannel.VisibleService     = vflag;
                            LogicalChannel.VersionNumber      = NetWkTable->VersionNo;
                            //TraceInfo(m,"Function : %s Line : %d SID : %d HDSLCN : %d",__FUNCTION__,__LINE__,LogicalChannel.ServiceId,LogicalChannel.LogicalChannelNum);
                            srtdb_Insert( tableid, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId , LogicalChannel.ServiceId, (Address)(&LogicalChannel));
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId);
	                        }
                        }
                    }
                }
            }
        }
        else if(sec_TableCompleted  &  code)
        {
            /* Delete logical channels if not present */
            int j = srtdb_GetNoOfRecords(tableid) - 1;
            while( 0 <= j )
            {
                if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
                {
                    if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                            (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                    {
                        /* delete the record */
                        if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId,0))
                        {  
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                        else
                        {  /* Could not delete */
                            ASSERT(FALSE);                   
                        }
                    }
                }
                /* decrement to prev index*/
                j--;
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
        }
        tsloop++;
    }   
    return 1;
}

Bool CHsvDvbNIT_Priv::PopulateLinkageInfo ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    return PopulateLinkageInfoPrivate(dmx, NetWkTable, HSVSPID(LinkageInfo, dvb, nit), srtdbids_NitLinkageInfoMain, code);
}

Bool CHsvDvbNIT_Priv::PopulateOtherLinkageInfo ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{

    return PopulateLinkageInfoPrivate(dmx, NetWkTable, HSVSPID(OtherLinkageInfo, dvb, nit), srtdbids_NitLinkageInfoSub, code);
}

Bool CHsvDvbNIT_Priv::PopulateLinkageInfoPrivate ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{    
    Bool    retval  = TRUE;
    HSVSPTYPE(LinkageInfo, dvb, nit)  linkage;
    HSVSPTYPE(LinkageInfo, dvb, nit)  DbaseVersion;

    int i= 0;
    int tsloop = 0; 

    int HsvEvtNull = 0;
    if( sec_SctArrived  &  code )
    {
        for( i = 0; i < NetWkTable->LinkageDescNum; i++)
        {
            if(NetWkTable->Linkage_Descriptor[i].DescriptorValid)
            {
                linkage.LinkageType        = (HsvLinkageType)NetWkTable->Linkage_Descriptor[i].LinkageType;
                linkage.Original_NetworkId = NetWkTable->Linkage_Descriptor[i].ONID;
                linkage.Tsid               = NetWkTable->Linkage_Descriptor[i].TSID;
                linkage.ServiceId          = NetWkTable->Linkage_Descriptor[i].ServiceId;
                linkage.NetworkId          = NetWkTable->NetworkId;
                linkage.VersionNumber      = NetWkTable->VersionNo;
                if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI) )
                {

                    if( srtdb_QueryOnKey( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&DbaseVersion)) )
                    {
                        /*Record exists. Update */
                        if( srtdb_Update( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&linkage)))
                        {                                            
                            /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/                  
                            //TraceInfo(m,"HYSVC : hsvdvbnit_m.c : strapiN called for LinkageInfo Onid = %d, Tsid = %d",linkage.Original_NetworkId, linkage.Tsid);
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),  HsvEvtNull );
                        }
                    }
                    else
                    {
                        //TraceInfo(m,"%s: @ %d :: OnId = %d, TsId=%d, Type=%d", __FUNCTION__, __LINE__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
                        if( srtdb_Insert( tableid, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType, linkage.LinkageType,(Address)(&linkage)))
                        {        
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType));             
                        }
                    }

                }
            }        

        }

        while ( tsloop < NetWkTable->TsLoopDataNum)
        {

            for( i = 0; i < NetWkTable->TsLoopData[tsloop].LinkageDescNum; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].Linkage_Descriptor[i].DescriptorValid)
                {
                    linkage.LinkageType        = (HsvLinkageType)NetWkTable->TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType;
                    linkage.Original_NetworkId = NetWkTable->TsLoopData[tsloop].Linkage_Descriptor[i].ONID;
                    linkage.Tsid               = NetWkTable->TsLoopData[tsloop].Linkage_Descriptor[i].TSID;
                    linkage.ServiceId          = NetWkTable->TsLoopData[tsloop].Linkage_Descriptor[i].ServiceId;
                    linkage.NetworkId          = NetWkTable->NetworkId;
                    linkage.VersionNumber      = NetWkTable->VersionNo;
                    if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI) )
                    {

                        if( srtdb_QueryOnKey( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),0, (Address)(&DbaseVersion)) )
                        {
                            /*Record exists. Update */
                            if( srtdb_Update( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0, (Address)(&linkage)))
                            {                                            
                                /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/                  
                                //TraceInfo(m,"HYSVC : hsvdvbnit_m.c : strapiN called for LinkageInfo Onid = %d, Tsid = %d",linkage.Original_NetworkId, linkage.Tsid);
                                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),  HsvEvtNull );
                            }
                        }
                        else
                        {
                            //TraceInfo(m,"%s: @ %d :: OnId = %d, TsId=%d, Type=%d", __FUNCTION__, __LINE__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
                            if( srtdb_Insert( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),(linkage.LinkageType), (Address)(&linkage)))
                            {        
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType));             
                            }
                        }

                    }
                }        

            }
            tsloop++;   
        }
    }
    else if(sec_TableCompleted  &  code)
    {
        int j = srtdb_GetNoOfRecords(tableid) - 1;
        while( j >= 0 )
        {
            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
            {
                if((DbaseVersion.NetworkId == NetWkTable->NetworkId) &&  (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                {
                    /* delete the record */
                    if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0,(DbaseVersion.LinkageType)))
                    {  
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, (DbaseVersion.LinkageType));
                    }
                    else
                    {  /* Could not delete */
                        ASSERT(FALSE);                   
                    }
                }
            }
            /* decrement to prev index*/
            j--;
        }
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
    }

    return retval;
}
/***********************************************************************************/
Bool CHsvDvbNIT_Priv::PopulateNetworkSRVCATRB ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    if(sec_SctArrived  &  code)
    {
        return PopulateServiceAttribute(dmx, NetWkTable, HSVSPID(ActualSRVCATRB, dvb, nit), srtdbids_NitSrvcAtrbTableMain, code);
    }
    else if( sec_TableCompleted  &  code )
    {
        return PopulateServiceAttribute(dmx, NetWkTable, HSVSPID(ActualSRVCATRB, dvb, nit), srtdbids_NitSrvcAtrbTableMain, code);
    }

    return TRUE;
}
/*********************************************************************************/
Bool CHsvDvbNIT_Priv::PopulateServiceAttribute ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
    HsvNITSRVCATRB DbaseVersion; 
    HsvNITSRVCATRB ServiceAttrib; 
    int i= 0;
    int tsloop = 0; 
    int j = 0;

    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {

            int NumSRVCATRBInfo = NetWkTable->TsLoopData[tsloop].ServiceAttrDescNum;

            for( i = 0; i < NumSRVCATRBInfo; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeLen ; j++)
                    {

                        Nat16 serviceid = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeDesc[j].ServiceId;
                        int saprivatedataspecifier = 0;
                        if( (sysset_GetSystemCountry() == cids_CountryUK ) && ( ins_GetMedium() == ins_Terrestrial ))
                        {
                            
                            saprivatedataspecifier = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].prevPrivateDataSpecifier;
                        }
                        else
                        {
                            // everywhere else we only use the PDSD if it was immediately before this descriptor
                            saprivatedataspecifier = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].PrivateDataSpecifier;
                        }
                        if (saprivatedataspecifier == 0x233A)
                        {
                            if ( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0, (Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if(DbaseVersion.NetworkId == NetWkTable->NetworkId)
                                {
                                    DbaseVersion.NumericSelect  = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeDesc[j].Numeric_Selection_Flag;
                                    DbaseVersion.VisibleService = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeDesc[j].Visible_Service_Flag;
                                    DbaseVersion.VersionNumber  = NetWkTable->VersionNo;

                                    srtdb_Update(tableid, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID,serviceid, 0, (Address)(&DbaseVersion) );
                                    strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, 0);
                                }
                            }
                            else
                            {   /* New Record */
                                ServiceAttrib.NetworkId          = NetWkTable->NetworkId;
                                ServiceAttrib.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                                ServiceAttrib.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                                ServiceAttrib.ServiceId          = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeDesc[j].ServiceId;
                                ServiceAttrib.NumericSelect      = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeDesc[j].Numeric_Selection_Flag;
                                ServiceAttrib.VisibleService     = NetWkTable->TsLoopData[tsloop].Service_Attribute_Descriptor[i].ServiceAttributeDesc[j].Visible_Service_Flag;
                                ServiceAttrib.VersionNumber      = NetWkTable->VersionNo;

                                srtdb_Insert( tableid, ServiceAttrib.Original_NetworkId, ServiceAttrib.Tsid, ServiceAttrib.ServiceId , ServiceAttrib.ServiceId,(Address)(&ServiceAttrib));
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceAttrib.Original_NetworkId, ServiceAttrib.Tsid, ServiceAttrib.ServiceId);
                            }
                        }
                    }           
                }           

            }
        }
        tsloop++;
    }

    if(sec_TableCompleted  &  code)
    {
        /* Delete logical channels if not present */
        int j = srtdb_GetNoOfRecords(tableid) - 1;
        while( 0 <= j )
        {
            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
            {
                if( (DbaseVersion.NetworkId == NetWkTable->NetworkId) && 
                        (DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                {
                    /* delete the record */
                    if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId,0))
                    {  
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                    }
                    else
                    {  /* Could not delete */
                        ASSERT(FALSE);                   
                    }
                }
            }
            /* decrement to prev index*/
            j--;
        }
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
    }
    else
    {
        /* Do Nothing */
    }
    return TRUE;

}
/*****************************************************************************************/
Bool CHsvDvbNIT_Priv::PopulateActualServiceListDS( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    return PopulateServiceListDS(dmx, NetWkTable, HSVSPID(ActualServiceList, dvb, nit), srtdbids_NitSrvclstTableMain, code);
}

Bool CHsvDvbNIT_Priv::PopulateOtherServiceListDS(HsvDemux dmx, TypeNit_Parser * NetWkTable, int code)
{

    return PopulateServiceListDS(dmx, NetWkTable, HSVSPID(OtherServiceList, dvb, nit), srtdbids_NitSrvclstTableSub, code);
}
/**********************************************************************************************/
Bool CHsvDvbNIT_Priv::PopulateServiceListDS ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
    HsvNITServiceList DbaseVersion, TempVersion; 
    int i= 0;
    int tsloop = 0; 
    int j = 0;

    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {

            int NumSRVCLISTInfo = NetWkTable->TsLoopData[tsloop].ServiceListDescNum;

            for( i = 0; i < NumSRVCLISTInfo; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].Service_List_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListLen ; j++)
                    {

                        DbaseVersion.NetworkId          = NetWkTable->NetworkId;
                        DbaseVersion.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                        DbaseVersion.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                        DbaseVersion.ServiceId          = NetWkTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListDesc[j].ServiceId;;
                        DbaseVersion.ServiceType      = NetWkTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListDesc[j].ServiceType;          ;
                        DbaseVersion.VersionNumber      = NetWkTable->VersionNo;

                        if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId , 0, (Address)(&TempVersion) ) )
                        {
                            /* Record Exists - Update the information & notify if needed*/
                            //if(DbaseVersion.NetworkId == NITTable->NITHEADER.Attrib)

                            srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId,0,(Address)(&DbaseVersion) );
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, 0);

                        }
                        else
                        {   /* New Record */
                            srtdb_Insert( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId,DbaseVersion.ServiceId, (Address)(&DbaseVersion));
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                    }
                }           

            }
        }
        tsloop++;
    }

    if(sec_TableCompleted  &  code)
    {
        /* Delete logical channels if not present */
        int j = srtdb_GetNoOfRecords(tableid) - 1;
        while( 0 <= j )
        {
            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
            {
                if(( DbaseVersion.NetworkId == NetWkTable->NetworkId) &&
                        ( DbaseVersion.VersionNumber != NetWkTable->VersionNo))
                {
                    /* delete the record */
                    if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId,0))
                    {  
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                    }
                    else
                    {  /* Could not delete */
                        ASSERT(FALSE);                   
                    }
                }
            }
            /* decrement to prev index*/
            j--;
        }
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
    }
    else
    {
        /* Do Nothing */
    }
    return TRUE;

}

Nat32 CHsvDvbNIT_Priv::DeducePrivateDataSpecifier (int NITOnid)
{   
    Nat32 PrivDataSpecifier  =   0;
    switch (NITOnid)
    {
        case 0x2210:    /* Netherlands */
        case 0x20FA:    /* France */
        case 0x2038:    /* Belgium */
        case 0x2114:    /* Germany */
        case 0x22D4:    /* Spain */
        case 0x212C:    /* Greece */
        case 0x2028:    /* Austria */
        case 0x20E9:    /* Estonia */
        case 0x4080:    /* Beijing */
        case 0x4481:    /* Guangzhou */
		case 0x2310:	/* UAE */
            PrivDataSpecifier    =   0x0028;
            break;
        case 0x233A:    /* UK */
            PrivDataSpecifier    =   0x233A;
            break;
        case 0x20F6:    /* Finland */
        case 0x22F1:    /* Sweden */
        case 0x20D0:    /* Denmark */
            PrivDataSpecifier    =   0x0029;
            break;
		case 0x222A:	/*APMEA NewZealand*/
			PrivDataSpecifier=0x37;
			break;
		case 0X22BE:	/*APMEA Singapore*/				
			PrivDataSpecifier=0X19;
			break;
		case 0x21CA:	/*APMEA Malaysia*/
			PrivDataSpecifier=0x21CA;
			break;
		case 0x22FC:	/*APMEA Thailand*/
			PrivDataSpecifier=0x22FC;
			break;
		case 0X209E:	/*APMEA Taiwan*/
			PrivDataSpecifier=0X209E;
			break;	
		case 0x2168:	/*APMEA Indonesia*/
			PrivDataSpecifier=0x2168;
			break;	
        default:
            break;

		if(NITOnid==0X2024 ||(NITOnid>=0X1010 &&NITOnid<=0X101F))
			{
			PrivDataSpecifier=0x3201;
			//TraceInfo(m,"Australia Deduce PvtDataSpec %d", (int)PrivateDataSpecifier);
			}

    }
    //TraceInfo(m,"Deduce PvtDataSpec %d", (int)PrivateDataSpecifier);
    return PrivDataSpecifier;
}


/*****************************************************************************************/
Nat16 CHsvDvbNIT_Priv::mInterpretLCNValue(int NITOnid, int privatedataspecify, Nat16 lcnvalue, Nat16 *vis_flag, int LcnType)
{
    Nat16 lcnVal = 0xFFFF;
    Bool Proceed = TRUE;

    if( eurdiv_ForceLCNSyntax( ins_GetMedium() ) ) //diversity will be set to true by product for australia
    {        
        privatedataspecify = PrivateDataSpecifier[sysset_GetSystemCountry()];
    }
    else
    {       
        int NetworkOperator = ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator);

        if((NetworkOperator == ins_UPC) && (ins_GetMedium() == ins_Cable))
        {
            Proceed = FALSE;
            if(privatedataspecify == 0x0028)  
            {
                lcnVal      =  (Nat16 ) (lcnvalue & 0x03FF );
                *vis_flag   =  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
            }
            else
            {
                lcnVal      =  0xFFFF;
                *vis_flag   =  1;
            }
        }/*CR AN-730*/
		else if((NetworkOperator == ins_RCSRDS) && (ins_GetMedium() == ins_Cable))
        {
            Proceed = FALSE;
            if(privatedataspecify == RCS_RDS_PDSD_VALUE) 
            {
                lcnVal      =  (Nat16 ) (lcnvalue);
                *vis_flag   =  1;
            }
            else
            {
                lcnVal      =  0xFFFF;
                *vis_flag   =  1;
            }
        }/* CR AN-7610*/
		else if((sysset_GetSystemCountry() == cids_CountryGermany) && (NetworkOperator == ins_UnityMedia) && (ins_GetMedium() == ins_Cable))
        {
            Proceed = FALSE;
            if(privatedataspecify == 0x0029)
            {
                lcnVal = (LcnType == LCN_TYPE_V1) ? ((Nat16 ) (lcnvalue & 0x003FFF )) :((Nat16 ) (lcnvalue & 0x003FF ));
                *vis_flag   =  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
            }
            else
            {
                lcnVal      =  0xFFFF;
                *vis_flag   =  1;
            }
        }
        else
        {
            /*If PrivateDataSpecifier is not present then */    
            if ( privatedataspecify == 0)
            {   

                /* LCN Syntax has to be deduced from Onid when 
                   a. Private Data Specifier is absent
                   b. Product does not force the LCN Syntax to be selected for this country
                   */
                //2.2.1 
                if( eurdiv_SupportMultipleOriginalNetworkId( ins_GetMedium() ) &&  eurdiv_EnableCountryFallbackForLCNSyntax ( ins_Terrestrial ))
                {
                    privatedataspecify = PrivateDataSpecifier[sysset_GetSystemCountry()];
                }
                //2.2.2
                if ( (0 == privatedataspecify) && eurdiv_EnableONIDFallbackForLCNSyntax( ins_GetMedium() ))
                {
                    privatedataspecify = DeducePrivateDataSpecifier(NITOnid);
                }
                //3.3
                if ( (0 == privatedataspecify ) && eurdiv_EnableCountryFallbackForLCNSyntax( ins_GetMedium() ))
                {
                    privatedataspecify = PrivateDataSpecifier[sysset_GetSystemCountry()];
                }
            }   
        }



        if(Proceed) //Not for UPC
        {
            switch(privatedataspecify)
            {
                case 0x233A:    /* UK */
                case 0x0028:    /* Europe */
                case 0x22D4:    /* Spain */
				case 0x22FC:  	/*Thailand*/
				case 0x0037:	/*NewZealand*/
				case 0x0019:	/*Singapore*/
				case 0x21CA:  	/*Malaysia*/
				case 0x2168:	/*Indonesia*/
				case 0X209E:	/*Taiwan*/	
                    lcnVal =  (Nat16 ) (lcnvalue & 0x03FF );
                    break;
                case 0x0029:    /* Nordig */
					lcnVal = (LcnType == LCN_TYPE_V1) ? ((Nat16 ) (lcnvalue & 0x003FFF )) :((Nat16 ) (lcnvalue & 0x03FF ));
                    break;
                default:
                    lcnVal =  0xFFFF;
                    break;
            }

            switch(privatedataspecify)
            {
                case 0x0028:
                case 0x0029:
                case 0x233A:
				case 0x22FC:  	/*Thailand*/
				case 0x0037:	/*NewZealand*/
				case 0x0019:	/*Singapore*/
				case 0x21CA:  	/*Malaysia*/
				case 0x2168:	/*Indonesia*/
				case 0X209E:	/*Taiwan*/
                    *vis_flag =  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
                    break;

                default:
                    *vis_flag =  1;
                    break;
            }
			if(privatedataspecify>=0x3200 && privatedataspecify<=0x320F)
				{
                    lcnVal =  (Nat16 ) (lcnvalue & 0x03FF );
					*vis_flag =  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
					//TraceInfo(m,"Australia LCN = %d, visflag = %d,lcnvalue=%d, privatedataspecify = %d",lcnVal, *vis_flag,lcnvalue, privatedataspecify);
				}
        }
        //TraceInfo(m,"LCN = %d, visflag = %d, privatedataspecify = %d",lcnVal, *vis_flag, privatedataspecify);      
    }
    return lcnVal;
}
/**************************************************************************************/
/*********to parse CAble DEL sys desc *****************/
Nat32 CHsvDvbNIT_Priv::mInterpretFrequencyValue(Nat32 *freq)
{
    /* Convert BCD MHz frequency into hertz */
    int i = 0;
    Nat32 result = 0;
    Nat32 Multiplier = 1;

    for(i=0; i<8; i++)  /* 8 as per Cable Delivery System Descriptor standards */
    {
        result += ((*freq >> (i*4)) & 0xf) * Multiplier;
        Multiplier *= 10;
    }
    result = ((result/10) * 16)/ 1000;
    *freq = result;
    return result;
}

Nat8 CHsvDvbNIT_Priv::mInterpretModulationValue(Nat8 *mod)
{
    int index = *mod;
    if(index > 5)
    {
        index = 0;
    }

    *mod = mModulation[index];

    return mModulation[index];
}

Nat32 CHsvDvbNIT_Priv::mInterpretSymbolRate(Nat32 *symrate)
{
    /* Convert BCD MSymobls/sec to symbols per sec*/
    int i = 0;
    Nat32 result = 0;
    Nat32 Multiplier = 1;

    for(i=0; i<7; i++)  /* 7 as per Cable Delivery System Descriptor standards */
    {
        result += ((*symrate >> (i*4)) & 0xf) * Multiplier;
        Multiplier *= 10;
    }

    result = result*100;
    *symrate = result;
    return result;

}

/********************************************************************************/
Nat32 CHsvDvbNIT_Priv::mInterpretCountryCode( Nat32 country )
{
    /* Examine the lower 3 bytes of the country code and try to determine the corresponding country ID in cids */
    Nat32       retval = cids_CountryOther;     
    Nat8        byte1;
    Nat8        byte2;
    Nat8        byte3;

#define HSV_TO_UPPER(x) ( ( (x) >= 'a' && (x) <= 'z' ) ? ( (x) - 'a' + 'A')  : ( (x) ) )


    /* Dont assume case dependency for country codes */
    byte1 = (country & 0xFF);
    byte1 = HSV_TO_UPPER(byte1);

    byte2 = ((country & 0xFF00) >> 8);
    byte2 = HSV_TO_UPPER(byte2);

    byte3 = ((country & 0xFF0000) >> 16);
    byte3 = HSV_TO_UPPER(byte3);

    country = ((byte3 << 16) | (byte2 << 8) | (byte1)) & 0xFFFFFF;

    switch ( (country & 0x00FFFFFF) )
    {
#define COUNTRYITEM(a, b, c)    case a:   \
        retval = cids_Country##b; \
        break;
#include <hsvcountry.h>
        default:
            break;
            /* Commented to avoid a case where a stream with non supported country can cause this assert
               usually seen in test streams or DTG streams */                                     
            /* ASSERT(FALSE);*/ /* New country Id passed, assert has less impact as we return the cids_CountryOther */

    }

    return retval;

}   /* End of function MapToCountryId() */


/********************************************************************************/

/*************************IHsvStream Implementation *******************************/
/***********************************************************************************/

int CHsvDvbNIT_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualNetworkID, dvb, nit): 
        case HSVSPID(NetworkName, dvb, nit): 
        case HSVSPID(ActualNITVer, dvb, nit): 
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(ActualNetworkLCN, dvb, nit):
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcnTableMain); 
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLinkageInfoMain);
            break;
        case HSVSPID(ActualCableDS, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitCableDSMain);
            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcn2TableMain);
            break;
        case HSVSPID(ActualNetworkHDSLCN, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitHDSLcnTableMain);
            break;
        case HSVSPID(OtherNetworkIDInfo, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitOtherNetworkIdTable);
            break;
        case HSVSPID(OtherNetworkLCN, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcnTableSub);
            break;
        case HSVSPID(OtherLinkageInfo, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLinkageInfoSub);
            break;
        case HSVSPID(OtherCableDS, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitCableDSSub);
            break;
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcn2TableSub);
            break;
        case HSVSPID(ActualSRVCATRB, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitSrvcAtrbTableMain);
            break;

        case HSVSPID(ActualTSRelocated, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitTsRelocateTableMain);
            break;  

        case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitSrvclstTableMain);
            break;  

        case HSVSPID(OtherServiceList, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitSrvclstTableSub);
            break;
        case HSVSPID(FreqList, dvb, nit):
            retval = srtdb_GetNoOfRecords(srtdbids_NitFreqList);
            break;
        case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitHDSLcnTableSub);
            break;
        case HSVSPID(TargetRegionName, dvb, nit):
            retval = srtdb_GetNoOfRecords(srtdbids_NitTargetRegionName);
            break;
		case HSVSPID(FavoriteChannelListLCNV2, dvb, nit):
            retval = srtdb_GetNoOfRecords(srtdbids_NitLCN2Favorite);
            break;	
		case HSVSPID(ActualTsID, dvb, nit):
			retval = srtdb_GetNoOfRecords(srtdbids_NitActualTsId);
			//TraceDebug(m,"strapi_GetByKey, retval:%d",retval);  
	        break;		
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}

Bool CHsvDvbNIT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualNetworkID, dvb, nit): 
        case HSVSPID(NetworkName, dvb, nit): 
        case HSVSPID(ActualNITVer, dvb, nit): 
            ASSERT("It is a scalar propert !!!");
            return FALSE;
            break;
        case HSVSPID(ActualNetworkLCN, dvb, nit):
            srtdb_SearchOnKey(srtdbids_NitLcnTableMain, key1, key2, key3,0, (int *)&index);
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLinkageInfoMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(ActualCableDS, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitCableDSMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLcn2TableMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(ActualNetworkHDSLCN, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitHDSLcnTableMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(OtherNetworkIDInfo, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitOtherNetworkIdTable, key1, key2, key3,0, (int *)&index);
            break;
        case HSVSPID(OtherNetworkLCN, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLcnTableSub, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(OtherLinkageInfo, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLinkageInfoSub, key1, key2, key3,0, (int *)&index);
            break;
        case HSVSPID(OtherCableDS, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitCableDSSub, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLcn2TableSub, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(ActualSRVCATRB, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitSrvcAtrbTableMain,key1, key2, key3, 0,(int *)&index);
            break;      

        case HSVSPID(ActualTSRelocated, dvb, nit): 
            retval = srtdb_SearchOnKey(srtdbids_NitTsRelocateTableMain,key1, key2, key3,0, (int *)&index);      
            break;  

        case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_SearchOnKey(srtdbids_NitSrvclstTableMain,key1, key2, key3, 0,(int *)&index);     
            break;  

        case HSVSPID(OtherServiceList, dvb, nit): 
            retval = srtdb_SearchOnKey(srtdbids_NitSrvclstTableSub,key1, key2, key3, 0,(int *)&index);      
            break;  
        case HSVSPID(FreqList, dvb, nit):
            retval = srtdb_SearchOnKey(srtdbids_NitFreqList,key1, key2, key3, 0,(int *)&index);     
            break;
        case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitHDSLcnTableSub, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(FavoriteChannelListLCNV2, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLCN2Favorite, key1, key2, key3, 0,(int *)&index);
            break;		
		case HSVSPID(ActualTsID, dvb, nit):
			srtdb_SearchOnKey(srtdbids_NitActualTsId, key1, key2, key3, 0,(int *)&index);
			//TraceDebug(m,"strapi_GetByKey, retval:%d",retval);  
            break;			
			
        default:
            ASSERT(FALSE);
            break;
    }

    return TRUE;
}

Bool CHsvDvbNIT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    switch(prop)
    {
        case HSVSPID(ActualNetworkID, dvb, nit) :
            {
                /* 
                 * we have to accept the oxFFFF as the valid NWID 
                 * as the private_temporary_use type of streams
                 * may have the value of ONID as 0xFF01-0xFFFF 
                 * so commented this check and return the NWID whatever
                 * stored in memory TV520 FRS 3202
                 */

           
                    Nat16 *pval = (Nat16 *)val;
                    *pval = DmxROMData[demux].NetworkId;
                    if(DmxROMData[demux].NITActualAvail)
                    {
                        retval = TRUE;
                    }
                    else
                    {
                    }
                break;
            }
        case HSVSPID(NetworkName, dvb, nit):
            {
                if( DmxROMData[demux].NetworkName[0] )
                {
                    /* First byte of network name was valid => We have some valid network name */
                    Nat16 *pval = (Nat16 *)val;                        
                    memcpy( pval, DmxROMData[demux].NetworkName, (MAX_NETWORK_NAME_SIZE) + 2 );
                    retval = TRUE;
                }
                break;
            }
        case HSVSPID(ActualNITVer, dvb, nit):
            {
                Nat8 *pval = (Nat8 *)val;
                *pval = DmxROMData[demux].ActualNITVer;
                if(DmxROMData[demux].NITActualAvail)
                {
                    retval = TRUE;
                }
                else
                {
                    TraceInfo(m,"%s::%d:No NIT Actual available",__FUNCTION__,__LINE__);
                }
            }

            break;

        case HSVSPID(ActualNetworkLCN, dvb, nit):
            retval = srtdb_QueryOnKey(srtdbids_NitLcnTableMain, key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitLinkageInfoMain, key1, key2, key3,0, (Address)val);
            break;
        case HSVSPID(ActualCableDS, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitCableDSMain, key1, key2, key3, 0,(Address)val);

            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitLcn2TableMain, key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(ActualNetworkHDSLCN, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitHDSLcnTableMain, key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(OtherNetworkIDInfo, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitOtherNetworkIdTable, key1, key2, key3,0, (Address)val);
            break;
        case HSVSPID(OtherNetworkLCN, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitLcnTableSub, key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(OtherLinkageInfo, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitLinkageInfoSub, key1, key2, key3,0, (Address)val);
            break;
        case HSVSPID(OtherCableDS, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitCableDSSub, key1, key2, key3,0, (Address)val);
            break;
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitLcn2TableSub, key1, key2, key3,0, (Address)val);
            break;
        case HSVSPID(ActualSRVCATRB, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitSrvcAtrbTableMain, key1, key2, key3,0, (Address)val);
            break;              

        case HSVSPID(ActualTSRelocated, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitTsRelocateTableMain,key1, key2, key3, 0,(Address)val);
            break;  

        case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitSrvclstTableMain,key1, key2, key3, 0,(Address)val);
            break;  

        case HSVSPID(OtherServiceList, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitSrvclstTableSub,key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(FreqList, dvb, nit):
            retval = srtdb_QueryOnKey(srtdbids_NitFreqList,key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitHDSLcnTableSub, key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(TargetRegionName, dvb, nit):
            retval = srtdb_QueryOnKey(srtdbids_NitTargetRegionName, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(TargetRegion, dvb, nit):
            retval = srtdb_QueryOnKey(srtdbids_NitTargetRegion, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(FavoriteChannelListLCNV2, dvb, nit):
            retval = srtdb_QueryOnKey(srtdbids_NitLCN2Favorite, key1, key2, key3, 0, (Address)val);
			//TraceDebug(m,"strapi_GetByKey, retval:%d",retval);  
            break;			
		case HSVSPID(ActualTsID, dvb, nit):
			retval = srtdb_QueryOnKey(srtdbids_NitActualTsId, key1, key2, key3, 0,(Address)val);
			//TraceDebug(m,"strapi_GetByKey [%d]  retval:%d",__LINE__,retval);  
            break;	
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}

Bool CHsvDvbNIT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualNetworkID, dvb, nit): 
        case HSVSPID(NetworkName, dvb, nit): 
        case HSVSPID(ActualNITVer, dvb, nit): 
            ASSERT("It is a scalar property !!!");
            return FALSE;
            break;
        case HSVSPID(ActualNetworkLCN, dvb, nit):
            retval = srtdb_QueryOnIndex(srtdbids_NitLcnTableMain, index, (Address)val);
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLinkageInfoMain, index, (Address)val);
            break;
        case HSVSPID(ActualCableDS, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitCableDSMain, index, (Address)val);
            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLcn2TableMain, index, (Address)val);
            break;
        case HSVSPID(ActualNetworkHDSLCN, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitHDSLcnTableMain, index, (Address)val);
            break;
        case HSVSPID(OtherNetworkIDInfo, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitOtherNetworkIdTable, index, (Address)val);
            break;
        case HSVSPID(OtherNetworkLCN, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLcnTableSub, index, (Address)val);
            break;
        case HSVSPID(OtherLinkageInfo, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLinkageInfoSub, index, (Address)val);
            break;
        case HSVSPID(OtherCableDS, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitCableDSSub, index, (Address)val);
            break;
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLcn2TableSub, index, (Address)val);
            break;
        case HSVSPID(ActualSRVCATRB, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitSrvcAtrbTableMain, index, (Address)val);
            break;              

        case HSVSPID(ActualTSRelocated, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitTsRelocateTableMain,index, (Address)val);
            break;  

        case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitSrvclstTableMain,index, (Address)val);
            break;  

        case HSVSPID(OtherServiceList, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitSrvclstTableSub,index, (Address)val);
            break;          
        case HSVSPID(FreqList, dvb, nit):
            retval = srtdb_QueryOnIndex(srtdbids_NitFreqList,index, (Address)val);
            break;
        case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitHDSLcnTableSub, index, (Address)val);
            break;
        case HSVSPID(TargetRegionName, dvb, nit):
            retval = srtdb_QueryOnIndex(srtdbids_NitTargetRegionName, index, (Address)val);
            break;
        case HSVSPID(FavoriteChannelListLCNV2, dvb, nit):
            retval = srtdb_QueryOnIndex(srtdbids_NitLCN2Favorite, index, (Address)val);
            break;			
		case HSVSPID(ActualTsID, dvb, nit):
			retval = srtdb_QueryOnIndex(srtdbids_NitActualTsId,index, (Address)val);
			//TraceDebug(m,"strapi_GetByKey, retval:%d",retval);  
	        break;		
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}

Bool CHsvDvbNIT_Priv::strapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	Bool retval = FALSE;
	switch(spid)
	{
		case HSVSPID(ActualNetworkLCN, dvb, nit):
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitLcnTableMain, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitLcnTableMain, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;
		case HSVSPID(ActualNetworkLCN2, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitLcn2TableMain, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}

			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitLcn2TableMain, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;
		case HSVSPID(OtherNetworkLCN2, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitLcn2TableSub, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}

			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitLcn2TableSub, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;	
		case HSVSPID(ActualCableDS, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitCableDSMain, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}
		
			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitCableDSMain, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;
		case HSVSPID(FavoriteChannelListLCNV2, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitLCN2Favorite, key1, from, to) == TRUE)
				{
					//TraceNotice(m,"%s:%d: from:%d to: %d",__FUNCTION__,__LINE__,*from,*to );
					retval = TRUE;
				}

			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitLCN2Favorite, key1, key2, from, to) == TRUE)
				{
					//TraceNotice(m,"%s:%d: from: %d to: %d",__FUNCTION__,__LINE__,*from,*to );
					retval = TRUE;
				}
			}
			else if(noofkeys == 3)
			{
				if(srtdb_SearchOnPrimarySecondaryAndTeritiaryKey(srtdbids_NitLCN2Favorite, key1, key2,key3, from, to) == TRUE)
				{
					//TraceNotice(m,"%s:%d: from: %d to: %d",__FUNCTION__,__LINE__,*from,*to );
					retval = TRUE;
				}

			}
			break;	
		 case HSVSPID(OtherCableDS, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitCableDSSub, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}
		
			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitCableDSSub, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;
		 case HSVSPID(ActualTsID, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitActualTsId, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}
		
			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitActualTsId, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;
		 case HSVSPID(ActualServiceList, dvb, nit): 
		 	if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitSrvclstTableMain, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}
		
			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitSrvclstTableMain, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
		 	break;
		case HSVSPID(OtherServiceList, dvb, nit): 
			if(noofkeys == 1)
			{
				if(srtdb_SearchOnPrimaryKey(srtdbids_NitSrvclstTableSub, key1, from, to) == TRUE)
				{
					retval = TRUE;
				}
		
			}
			else if(noofkeys == 2)
			{
				if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitSrvclstTableSub, key1, key2, from, to) == TRUE)
				{
					retval = TRUE;
				}
			}
			break;
			
		default:
			break;
	}
	return retval;
}


Bool CHsvDvbNIT_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
    UNUSED (dest);
    UNUSED (value);

    switch(filterid)
    {
        /* Do nothing */
        case HsvStartMode:       
            break;
        case HsvCurrentCountry:  
            break;
        case HsvCurrentLanguage: 
            break;
        case HsvCurrentProgram:
            break;
        case HsvOtherSDTOnwidId: 
        case HsvOtherSDTServiceId:
            break;                    
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */

Bool CHsvDvbNIT_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}
Bool CHsvDvbNIT_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
return FALSE;
}
Bool CHsvDvbNIT_Priv::strmfltr_Clear    ( HsvDestination dest, int filterid, int value )
{
return FALSE;
}
Bool CHsvDvbNIT_Priv::strmfltr_ForceClear( HsvDestination dest, int filterid, int value )
{
return FALSE;
}

/*************************************************************/
void CHsvDvbNIT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    int i   = 0;
    int dmx = HsvDmxMain;

    for(i = 0; i < MAX_SECTIONS; i++)
    {
        for(  dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
        {
            if( DmxROMData[dmx].SubscrId[i] == subscrid )
            {
                /* This was a matching request. Clear our local variables */
                DmxROMData[dmx].SubscrId[i]  = HSV_INVALID_SCT_REQUEST;
            }
        }
    }
}

   void CHsvDvbNIT_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
   {
   }

	void CHsvDvbNIT_Priv::dmxsecfN_OnRequestNotAllowed ()
	{
	}



Bool CHsvDvbNIT_Priv::mValidateCDS(HsvNITCableDS *pCds, int index)
{
    Bool ret = FALSE;
    if( (pCds->CDSD[index].SymbolRate > 0) && \
            (pCds->CDSD[index].Modulation != HsvUnknownConstellation) && \
            (pCds->CDSD[index].Frequency >= START_FREQUENCY) && \
            (pCds->CDSD[index].Frequency <= END_FREQUENCY)  \
      )
    {
        ret = TRUE;
    }
    else
    {
    }
    return ret;
}

int CHsvDvbNIT_Priv::iutil_GetLCNValue(Nat8* ptr, int num)
{
    int val = GET16(0);
    UNUSED(num);
    return val;
}


Bool CHsvDvbNIT_Priv::PopulateFreqList(HsvDemux dmx, TypeNit_Parser * NetWkTable, int code)
{

    if(eurdiv_FreqListDescriptorSupported(ins_GetMedium()))
    {

        if(sec_SctArrived  &  code)
        {
            return PopulateFreqListPrivate (dmx, NetWkTable, HSVSPID(FreqList, dvb, nit),srtdbids_NitFreqList, code);
        }

        else if( sec_TableCompleted  &  code )
        {
            return PopulateFreqListPrivate (dmx, NetWkTable, HSVSPID(FreqList, dvb, nit),srtdbids_NitFreqList, code);
        }
    }
    return TRUE;
}


Bool CHsvDvbNIT_Priv::PopulateFreqListPrivate( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int Ppty, int tableid, int code)
{

    /* The datatypes are same for both Actual and Other. So using just one instance */
    HsvNITFreqList DbaseVersion,TmpDbaseVersion;

    int i=0;
    int HsvEvtNull = 0;
    int tsloop = 0;
    int j = 0;



    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {
            int numOfFreqList = NetWkTable->TsLoopData[tsloop].FrequencyListDescNum;


            for( i = 0; i < numOfFreqList; i++)
            {
                if((NetWkTable->TsLoopData[tsloop].FrequencyList_Descriptor[i].DescriptorValid) && (NetWkTable->TsLoopData[tsloop].FrequencyList_Descriptor[i].CodingType == CURRENTTERRESTRIALCODINGTYPE) && (mCurrentONID == NetWkTable->TsLoopData[tsloop].ONID) )
                {
                    DbaseVersion.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                    DbaseVersion.Tsid = NetWkTable->TsLoopData[tsloop].TSID;
                    DbaseVersion.VersionNumber = NetWkTable->VersionNo;
                    DbaseVersion.NoOfFreqs = HSV_PARSER_MIN(NetWkTable->TsLoopData[tsloop].FrequencyList_Descriptor[i].FrequencyListLen, MAX_NO_ALT_FREQ_PER_MUX);;

                    for(j = 0; j < DbaseVersion.NoOfFreqs; j++)
                    {
                        int tempFreq = NetWkTable->TsLoopData[tsloop].FrequencyList_Descriptor[i].FrequencyListDesc[j].Center_Frequency;
                        tempFreq = ( ((tempFreq/100) * 16) / 1000);

                        DbaseVersion.Frequency[j] = tempFreq;
                    }

                    if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid , 0, 0,(Address)(&TmpDbaseVersion) ) )
                    {
                        if(FALSE == srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0, 0,(Address)(&DbaseVersion)))
                        {
                            ASSERT(FALSE);
                        }
                        else
                        {
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0, HsvEvtNull);
                        }
                    }
                    else
                    {
                        if(FALSE == srtdb_Insert(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0, 0,(Address)(&DbaseVersion)))
                        {
                            ASSERT(FALSE);
                        }
                        else
                        {
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0);
                        }
                    }
                }
                else
                {
                    //TraceDebug(m,"Skipped because: CurrenONID = %d, from Stream = %d",mCurrentONID, NetWkTable->TsLoopData[tsloop].ONID);
                }
            }
        }
        else if(sec_TableCompleted  &  code)
        {
            j = srtdb_GetNoOfRecords(tableid) - 1;
            while( 0 <= j )
            {
                if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
                {
                    if(DbaseVersion.VersionNumber != NetWkTable->VersionNo)
                    {
                        /* delete the record */
                        if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0,0))
                        {
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, 0);
                        }
                        else
                        {  /* Could not delete */
                            ASSERT(FALSE);                   
                        }
                    }
                }
                /* decrement to prev index*/
                j--;
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
        }
        else
        {
            /* Do Nothing */
        }
        tsloop++;
    }
    return TRUE;
}

void CHsvDvbNIT_Priv::PopulateTargetRegionDesc( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    Bool ValidData = FALSE;
	int i, k, x = 0, tsloop = 0, HsvEvtNull = 0;
    Nat32   j;
    HsvNITTargetRegion DbaseVersion, TargetRegion;

    do
    {
        if( sec_SctArrived  &  code )
        {
            /* first check for data in 2nd TsLoop, if not present then only go 1st TsLoop */
			TargetRegion.NetworkId = NetWkTable->NetworkId;
			TargetRegion.ServiceId = 0xFFFF;
			TargetRegion.VersionNumber = NetWkTable->VersionNo;
			if(NetWkTable->TsLoopData[tsloop].ExtTargetRegionDescNum > 0)
			{
				for(i=0; i < NetWkTable->TsLoopData[tsloop].ExtTargetRegionDescNum; i++)
				{
					TargetRegion.TsLoop		 = 2;
					TargetRegion.OnId		 = NetWkTable->TsLoopData[tsloop].ONID;
					TargetRegion.Tsid		 = NetWkTable->TsLoopData[tsloop].TSID;
					TargetRegion.CountryCode = mInterpretCountryCode(NetWkTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].CountryCode);
					
					for(j=0; j < NetWkTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegionLen; j++)
					{
						TargetRegion.RegionList.RegionMap [ i ][ MULT_REGION_DEPTH_INDEX ]  =  NetWkTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[j].RegionDepth;
						TargetRegion.RegionList.RegionMap [ i ][ MULT_PRIMARY_INDEX ]		=  NetWkTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[j].PrimaryRegionCode;
						TargetRegion.RegionList.RegionMap [ i ][ MULT_SECONDARY_INDEX ]	    =  NetWkTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[j].SecondaryRegionCode;
						TargetRegion.RegionList.RegionMap [ i ][ MULT_TERTIARY_INDEX ]		=  NetWkTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[j].TertiaryRegionCode;
						if( NetWkTable->TsLoopData[ tsloop ].Ext_TargetRegion_Descriptor[ i ].TargetRegion[ j ].CountryCodeFlag == 1 )
						{
							// override the previously set country code with the one in the inner loop 
							TargetRegion.CountryCode = mInterpretCountryCode(NetWkTable->TsLoopData[ tsloop ].Ext_TargetRegion_Descriptor[ i ].TargetRegion[ j ].CountryCode);
						}
                        switch ( TargetRegion.RegionList.RegionMap [ i ][ MULT_REGION_DEPTH_INDEX ] )
                        {
                            case 0:
                            {
                                TargetRegion.RegionList.RegionMap [i][MULT_PRIMARY_INDEX]   = 0xFFFF;
                                TargetRegion.RegionList.RegionMap [i][MULT_SECONDARY_INDEX] = 0xFFFF;
                                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX]  = 0xFFFF;
                                break;
                            }
//                            
                            case 1: 
                            {
                                TargetRegion.RegionList.RegionMap [i][MULT_SECONDARY_INDEX] = 0xFFFF;
                                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX] = 0xFFFF;
                                break;
                            }
                            case 2: 
                            {
                                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX] = 0xFFFF;
                                break;
                            }
                            default:
                                break;

                        }
						ValidData = TRUE;
					}
				}
                for (x  = i; x < MAX_REGIONS_PER_SERVICE; x++)
                {
                    TargetRegion.RegionList.RegionMap [x][MULT_REGION_DEPTH_INDEX]  = INVALID_REGION_DEPTH;
                    TargetRegion.RegionList.RegionMap [x][MULT_PRIMARY_INDEX]   = 0xFFFF;
                    TargetRegion.RegionList.RegionMap [x][MULT_SECONDARY_INDEX] = 0xFFFF;
                    TargetRegion.RegionList.RegionMap [x][MULT_TERTIARY_INDEX]  = 0xFFFF;				
                }
			}
			
			if(ValidData == FALSE)
			{
				for(i=0; i < NetWkTable->ExtTargetRegionDescNum; i++)
				{
					TargetRegion.TsLoop		 = 1;
					TargetRegion.OnId		 = 0xFFFF;
					TargetRegion.Tsid		 = 0xFFFF;
					TargetRegion.CountryCode = mInterpretCountryCode(NetWkTable->Ext_TargetRegion_Descriptor[i].CountryCode);
					
					for(j=0; j < NetWkTable->Ext_TargetRegion_Descriptor[i].TargetRegionLen; j++)
					{
						TargetRegion.RegionList.RegionMap [ i ][ MULT_REGION_DEPTH_INDEX ]  =  NetWkTable->Ext_TargetRegion_Descriptor[i].TargetRegion[j].RegionDepth;
						TargetRegion.RegionList.RegionMap [ i ][ MULT_PRIMARY_INDEX ]		=  NetWkTable->Ext_TargetRegion_Descriptor[i].TargetRegion[j].PrimaryRegionCode;
						TargetRegion.RegionList.RegionMap [ i ][ MULT_SECONDARY_INDEX ]	    =  NetWkTable->Ext_TargetRegion_Descriptor[i].TargetRegion[j].SecondaryRegionCode;
						TargetRegion.RegionList.RegionMap [ i ][ MULT_TERTIARY_INDEX ]		=  NetWkTable->Ext_TargetRegion_Descriptor[i].TargetRegion[j].TertiaryRegionCode;
						
						if( NetWkTable->Ext_TargetRegion_Descriptor[ i ].TargetRegion[ j ].CountryCodeFlag == 1 )
						{
							// override the previously set country code with the one in the inner loop 
							TargetRegion.CountryCode = mInterpretCountryCode(NetWkTable->Ext_TargetRegion_Descriptor[i].TargetRegion[j].CountryCode);
						}
                        switch ( TargetRegion.RegionList.RegionMap [ i ][ MULT_REGION_DEPTH_INDEX ] )
                        {
                            case 0:
                            {
                                TargetRegion.RegionList.RegionMap [i][MULT_PRIMARY_INDEX]   = 0xFFFF;
                                TargetRegion.RegionList.RegionMap [i][MULT_SECONDARY_INDEX] = 0xFFFF;
                                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX]  = 0xFFFF;
                                break;
                            }
//                            
                            case 1: 
                            {
                                TargetRegion.RegionList.RegionMap [i][MULT_SECONDARY_INDEX] = 0xFFFF;
                                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX] = 0xFFFF;
                                break;
                            }
                            case 2: 
                            {
                                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX] = 0xFFFF;
                                break;
                            }
                            default:
                                break;
                        }
					}
				}
                for (x  = i; x < MAX_REGIONS_PER_SERVICE; x++)
                {
                    TargetRegion.RegionList.RegionMap [x][MULT_REGION_DEPTH_INDEX]  = INVALID_REGION_DEPTH;
                    TargetRegion.RegionList.RegionMap [x][MULT_PRIMARY_INDEX]   = 0xFFFF;
                    TargetRegion.RegionList.RegionMap [x][MULT_SECONDARY_INDEX] = 0xFFFF;
                    TargetRegion.RegionList.RegionMap [x][MULT_TERTIARY_INDEX]  = 0xFFFF;				
                }
			}
			/* honour the desc values only if it is UK */
			if(TargetRegion.CountryCode == cids_CountryUK)
			{
				if( srtdb_QueryOnKey(srtdbids_NitTargetRegion, TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.NetworkId, 0,(Address)(&DbaseVersion) ) )
				{
					if(srtdb_Update(srtdbids_NitTargetRegion, TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.NetworkId, 0,(Address)(&TargetRegion)))
					{
						strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, nit), TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.NetworkId, HsvEvtNull);
					}
				}
				else
				{
					if(srtdb_Insert(srtdbids_NitTargetRegion, TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.NetworkId, 0, (Address)(&TargetRegion)))
					{
						strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, nit), TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.NetworkId);
					}
				}
			}
		}	  
		
		if(sec_TableCompleted  &  code)
		{
			for(k = (srtdb_GetNoOfRecords(srtdbids_NitTargetRegion) - 1); k >= 0; k--)
			{
				if(srtdb_QueryOnIndex(srtdbids_NitTargetRegion, k, (Address)(&DbaseVersion)))
				{
					if(DbaseVersion.VersionNumber != NetWkTable->VersionNo)
					{
						if(srtdb_Delete(srtdbids_NitTargetRegion, DbaseVersion.OnId, 0, DbaseVersion.NetworkId,0))
						{  
							strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, nit), DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
						}
					}
				}
			}
			strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, nit));
		}

		tsloop++;
	}while(tsloop < NetWkTable->TsLoopDataNum);
}

void CHsvDvbNIT_Priv::PopulateTargetRegionNameDesc( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    int i = 0, j = 0, k = 0;
    HsvNITTargetRegionName DbaseVersion, TargetRegionName;

    if( sec_SctArrived & code )
    {
        TargetRegionName.NetworkId     = NetWkTable->NetworkId;
        TargetRegionName.VersionNumber = NetWkTable->VersionNo;
        for(i=0; i < NetWkTable->ExtTargetRegionNameDescNum; i++)
        {
            TargetRegionName.CountryCode = mInterpretCountryCode(NetWkTable->Ext_TargetRegionName_Descriptor[i].CountryCode);
            TargetRegionName.Langcode    = GetLanguageId(NetWkTable->Ext_TargetRegionName_Descriptor[i].LangCode);
            for(j=0; j < NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionNameLen; j++)
            {
                TargetRegionName.RegionDepth = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionDepth;

                Bool ValidData = TRUE; 
                switch(TargetRegionName.RegionDepth)
                {
                    case 3: /* Primary, Secondary & Tertiary */
                        TargetRegionName.Primary.Secondary.Tertiary.RegionCode = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].TertiaryRegionCode;
                        TargetRegionName.Primary.Secondary.RegionCode = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].SecondaryRegionCode;
                        TargetRegionName.Primary.RegionCode = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].PrimaryRegionCode;

                        memcpy(TargetRegionName.Primary.Secondary.Tertiary.RegionName, NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionName, NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen);
                        charsetutil_MbToWc( NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionName, 
                                NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen, 
                                (Nat16*)TargetRegionName.Primary.Secondary.Tertiary.RegionName,
                                MAX_REGION_NAME_SIZE,
                                (NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen >= MAX_REGION_NAME_SIZE) ? TRUE : FALSE 
                                );

                        TargetRegionName.Primary.Secondary.Tertiary.RegionName[MAX_REGION_NAME_SIZE] = 0;
                        break;
                    case 2: /* Primary & Secondary */
                        TargetRegionName.Primary.Secondary.RegionCode = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].SecondaryRegionCode;
                        TargetRegionName.Primary.RegionCode = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].PrimaryRegionCode;

                        TargetRegionName.Primary.Secondary.Tertiary.RegionCode = INVALID_REGION_CODE;
                        memcpy(TargetRegionName.Primary.Secondary.RegionName, NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionName, NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen);

                        charsetutil_MbToWc( NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionName, 
                                NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen, 
                                (Nat16*)TargetRegionName.Primary.Secondary.RegionName,
                                MAX_REGION_NAME_SIZE,
                                (NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen >= MAX_REGION_NAME_SIZE) ? TRUE : FALSE 
                                );

                        TargetRegionName.Primary.Secondary.RegionName[MAX_REGION_NAME_SIZE] = 0;
                        break;
                    case 1: /* Primary */
                        TargetRegionName.Primary.RegionCode = NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].PrimaryRegionCode;
                        TargetRegionName.Primary.Secondary.Tertiary.RegionCode = INVALID_REGION_CODE;
                        TargetRegionName.Primary.Secondary.RegionCode = INVALID_REGION_CODE;
                        memcpy(TargetRegionName.Primary.RegionName, NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionName, NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen);

                        charsetutil_MbToWc( NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionName, 
                                NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen, 
                                (Nat16*)TargetRegionName.Primary.RegionName,
                                MAX_REGION_NAME_SIZE,
                                (NetWkTable->Ext_TargetRegionName_Descriptor[i].TargetRegionName[j].RegionNameLen >= MAX_REGION_NAME_SIZE) ? TRUE : FALSE 
                                );

                        TargetRegionName.Primary.RegionName[MAX_REGION_NAME_SIZE] = 0;                  
                        break;
                    default:
                        ValidData = FALSE;
                        break;
                }

                if(ValidData)
                {
                    /* honour the desc values only if it is UK */
                    if( (TargetRegionName.CountryCode == cids_CountryUK))
                    {
                        if(srtdb_QueryOnKey(srtdbids_NitTargetRegionName, TargetRegionName.Primary.RegionCode, TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Primary.Secondary.Tertiary.RegionCode, TargetRegionName.Langcode, (Address)(&DbaseVersion))) 
                        {
                            if(srtdb_Update(srtdbids_NitTargetRegionName, TargetRegionName.Primary.RegionCode, TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Primary.Secondary.Tertiary.RegionCode, TargetRegionName.Langcode, (Address)(&TargetRegionName)))
                            {
                                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegionName, dvb, nit), TargetRegionName.Primary.RegionCode, TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Primary.Secondary.Tertiary.RegionCode, TargetRegionName.Langcode);
                            }
                        }
                        else
                        {
                            if(srtdb_Insert(srtdbids_NitTargetRegionName, TargetRegionName.Primary.RegionCode, TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Primary.Secondary.Tertiary.RegionCode, TargetRegionName.Langcode, (Address)(&TargetRegionName)))
                            {
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegionName, dvb, nit), TargetRegionName.Primary.RegionCode, TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Primary.Secondary.Tertiary.RegionCode);
                            }
                        }
                    }
                }
            }
        }
    }     
    else if(sec_TableCompleted  & code)
    {
        for(k = (srtdb_GetNoOfRecords(srtdbids_NitTargetRegionName) - 1); k >= 0; k--)
        {
            if(srtdb_QueryOnIndex(srtdbids_NitTargetRegionName, k, (Address)(&DbaseVersion)))
            {
                if(DbaseVersion.VersionNumber != NetWkTable->VersionNo)
                {
                    /* delete the record */
                    if (srtdb_Delete(srtdbids_NitTargetRegionName, DbaseVersion.NetworkId, 0, 0,0))
                    {  
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegionName, dvb, nit), DbaseVersion.Primary.RegionCode, DbaseVersion.Primary.Secondary.RegionCode, DbaseVersion.Primary.Secondary.Tertiary.RegionCode);
                    }
                }
            }
        }
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegionName, dvb, nit));
    }
}

Nat8 CHsvDvbNIT_Priv::GetLanguageId(Nat32 Language)
{
    /* Assume that the lower 3 bytes of the Nat32 contain the 3 byte code */
    char byte1 = (char)((((Nat32)(Language) & 0xFF0000)) >> 16);
    char byte2 = (char)((((Nat32)(Language) & 0xFF00))   >> 8);
    char byte3 = (char)((((Nat32)(Language) & 0xFF)));

    return (Nat8)(mpegserv_GetLanguageId( byte1, byte2, byte3 ));
} 


Nat8 CHsvDvbNIT_Priv::s__mBuffer[4*1024];

Bool CHsvDvbNIT_Priv::Nit_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = mBuffer;
    Nat8 *tempptr ;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    static TypeNit_Parser Nit_Parser;
    Bool retval = TRUE;
    int dummy, loopcount = 0, descTag, descLen = 0, descTagExtn = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0,loop2index = 0, tableLen = 0, loop1length = 0,loop2length = 0, templen = 0, tempTsTargetRegNameLen=0; 
	int	ntfcode = sec_SctArrived;
	
    UNUSED (cookie);
    UNUSED (crc);
    memset(&Nit_Parser,0,sizeof(Nit_Parser));
    if(secondarySectionSize > 0)
    {
        memcpy(ptr,PrimarySectionStartAddress,primarySectionSize);
        memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
    }
    else
    {  
        ptr = PrimarySectionStartAddress;
    }  

	

    v32 = GET32(0);
    tableLen = HSV_GETSECTION_LENGTH(ptr);
    Nit_Parser.NtkNameDescNum=0;
    Nit_Parser.TSRelocateDescNum=0;
    Nit_Parser.LinkageDescNum=0;
    Nit_Parser.ExtTargetRegionDescNum=0;
    Nit_Parser.ExtTargetRegionNameDescNum=0;
    Nit_Parser.TsLoopDataNum=0;
    Nit_Parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    Nit_Parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    Nit_Parser.NetworkId = GETNBITS(v32,0,16);
	//TraceNotice(m,"parsing NIT with NID: %d TID: %d",Nit_Parser.NetworkId,Nit_Parser.TableId);
    dummy = GETNBITS(v32,16,2);
    Nit_Parser.VersionNo = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,4);
    Nit_Parser.NetworkDescLen = GETNBITS(v32,12,12);

    ptr += 10;
    tableLen = tableLen - 10;
    v32 = GET32( 0);
    while(loopcount < Nit_Parser.NetworkDescLen)
    {
        descLoopLen = 0;
        descTag = GETNBITS(v32,0, 8); 
        descLen = GETNBITS(v32,8, 8); 
        switch(descTag) {
            case 0x40:
                Nit_Parser.NetworkName_Descriptor.DescriptorTag = GETNBITS(v32,0,8);
                Nit_Parser.NetworkName_Descriptor.DescriptorLen = GETNBITS(v32,8,8);

                Nit_Parser.NetworkName_Descriptor.NetworkNameLen = descLen;
                descLoopLen = HSV_PARSER_MIN(140,Nit_Parser.NetworkName_Descriptor.NetworkNameLen); 
                ptr += 2;
                memcpy(Nit_Parser.NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
                ptr += Nit_Parser.NetworkName_Descriptor.NetworkNameLen;
                v32 = GET32( 0);
                Nit_Parser.NetworkName_Descriptor.NetworkNameLen = descLoopLen;
                Nit_Parser.NetworkName_Descriptor.DescriptorValid = TRUE;
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);

                v32 = GET32( 0);
                break;

            case 0xAA:
                if(Nit_Parser.TSRelocateDescNum<10)
                {
                    Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].DescriptorTag = GETNBITS(v32,0,8);
                    Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].DescriptorLen = GETNBITS(v32,8,8);
                    Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateLen = 0; /*GETNBITS(v32,16,0);*/
                    ptr += 2;
                    v32 = GET32( 0 );
                    loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc);
                    while( loop1length< HSV_PARSER_MIN(Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].DescriptorLen, templen ))
                    {

                        Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].Transport_Stream_ID= GETNBITS(v32,0, 16); 
                        Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].Original_Network_ID= GETNBITS(v32,16, 16); 
                        v32 = GET32( 4);
                        Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TS_DescriptorLen= GETNBITS(v32,0, 8); 
                        Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDescLen= 0;/*GETNBITS(v32,8, 0); */
                        ptr += 5;
                        loop1length += 5;
                        v32 = GET32( 0 );
                        loop2index = 0, loop2length = 0, templen = sizeof(Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc);
                        while( (loop2length< HSV_PARSER_MIN(Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TS_DescriptorLen, templen))&& 
                                (Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TS_DescriptorLen < Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].DescriptorLen))
                        {

                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].DescriptorTag = GETNBITS(v32,0, 8); 
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].DescriptorLen = GETNBITS(v32,8, 8); 
                            v32 = GET32( 2);
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].Frequency = GETNBITS(v32,0, 32); 
                            v32 = GET32( 6);
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].reserved = GETNBITS(v32,0, 12); 
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].FEC_Outer = GETNBITS(v32,12, 4); 
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].Modulation = GETNBITS(v32,16, 8); 
                            v32 = GET32( 9);
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].SymbolRate = GETNBITS(v32,0, 28); 
                            Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDesc[loop2index].FEC_Inner = GETNBITS(v32,28, 4); 
                            loop2length += 13;
                            loop2index++;
                            ptr += 13;
                            loop1length += 13;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateDesc[loop1index].TSDescLen = loop2index;
                        loop1index++;
                        v32 = GET32( 0);
                    }
                    Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].TS_RelocateLen = loop1index;
                    Nit_Parser.TSRelocate_Descriptor[Nit_Parser.TSRelocateDescNum].DescriptorValid = TRUE;
                    Nit_Parser.TSRelocateDescNum++;
                }
                else
                {
                    ptr += 2 + descLen;
                }
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);

                v32 = GET32( 0);
                break;

            case 0x4A:
                if(Nit_Parser.LinkageDescNum<50)
                {
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].DescriptorTag = GETNBITS(v32,0,8);
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].DescriptorLen = GETNBITS(v32,8,8);
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].TSID = GETNBITS(v32,16,16);
                    v32 = GET32( 4);
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].ONID = GETNBITS(v32,0,16);
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].ServiceId = GETNBITS(v32,16,16);
                    v32 = GET32( 8);
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].LinkageType = GETNBITS(v32,0,8);

                    ptr += 2 + descLen;
                    v32 = GET32( 0);
                    Nit_Parser.Linkage_Descriptor[Nit_Parser.LinkageDescNum].DescriptorValid = TRUE;
                    Nit_Parser.LinkageDescNum++;
                }
                else
                {
                    ptr += 2 + descLen;
                }
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);

                v32 = GET32( 0);
                break;

            case 0x7F : 
                descTagExtn = GETNBITS(v32,16, 8); 
                switch(descTagExtn) {
                    case 0x09:
                        tempptr = ptr;
                        if(Nit_Parser.ExtTargetRegionDescNum<10)
                        {         


                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].DescriptorTag = GETNBITS(v32,0,8);
                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].DescriptorLen = GETNBITS(v32,8,8);
                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].DescriptorTagExtn = GETNBITS(v32,16,8);
                            v32 = GET32( 3);
                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].CountryCode = GETNBITS(v32,0,24);

                            ptr += 6;
                            v32 = GET32( 0 );
                            loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion);
                            while( loop1length< HSV_PARSER_MIN( (descLen - 4), templen) )
                            {

                                Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].reserved= GETNBITS(v32,0, 5); 
                                Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCodeFlag= GETNBITS(v32,5, 1); 
                                Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth= GETNBITS(v32,6, 2); 
                                ptr += 1;
                                loop1length++;
                                v32 = GET32( 0 );
                                if( Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCodeFlag == 1 ) {
                                    Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCode= GETNBITS(v32,0, 24); 
                                    ptr += 3;
                                    loop1length+=3;
                                    v32 = GET32( 0 );
                                }
                                if( Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 1 ) {
                                    Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].PrimaryRegionCode= GETNBITS(v32,0, 8); 
                                    ptr += 1;
                                    loop1length++;
                                    if( Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 2 ) {
                                        Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].SecondaryRegionCode= GETNBITS(v32,8, 8); 
                                        ptr += 1;
                                        loop1length++;
                                        if( Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 3 ) {
                                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].TertiaryRegionCode= GETNBITS(v32,16, 16); 
                                            ptr += 2;
                                            loop1length +=2;
                                            v32 = GET32( 0 );
                                        }
                                    }
                                }

                                loop1index++;
                                v32 = GET32( 0);
                            }
                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegionLen = loop1index;
                            Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].DescriptorValid = TRUE;
                            Nit_Parser.ExtTargetRegionDescNum++;
                        }
                        //else
                        {
                            ptr = tempptr;
                            ptr += 2 + descLen;
                        }

                        loopcount += 2 + descLen;
                        tableLen = tableLen - (2 + descLen);

                        v32 = GET32( 0);
                        break;

                    case 0x0A:
                        tempptr = ptr;
                        if(Nit_Parser.ExtTargetRegionNameDescNum<10)
                        {

                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].DescriptorTag = GETNBITS(v32,0,8);
                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].DescriptorLen = GETNBITS(v32,8,8);
                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].DescriptorTagExtn = GETNBITS(v32,16,8);
                            v32 = GET32( 3);
                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].CountryCode = GETNBITS(v32,0,24);
                            v32 = GET32( 6);
                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].LangCode = GETNBITS(v32,0,24);

                            ptr += 9;
                            v32 = GET32( 0 );
                            loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName);
                            while( loop1length< HSV_PARSER_MIN( (descLen - 7), templen) )
                            {
                                int minLength = 0;
                                Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionDepth= GETNBITS(v32,0, 2); 
                                Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionNameLen= GETNBITS(v32,2, 6); 
                                minLength = HSV_PARSER_MIN(Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionNameLen,80);
                                ptr += 1;
                                loop1length++;
                                memcpy(Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionName,ptr, minLength);
                                ptr += Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionNameLen;
                                loop1length += Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionNameLen;
                                v32 = GET32( 0);
                                Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionNameLen= minLength;
                                Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].PrimaryRegionCode= GETNBITS(v32,0, 8); 
                                ptr += 1;
                                loop1length++;
                                if( Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionDepth >= 2 ) {
                                    Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].SecondaryRegionCode= GETNBITS(v32,8, 8); 
                                    ptr += 1;
                                    loop1length++;
                                    if( Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].RegionDepth >= 3 ) {
                                        Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionName[loop1index].TertiaryRegionCode= GETNBITS(v32,16, 16); 
                                        ptr += 2;
                                        loop1length+=2;
                                        v32 = GET32( 0 );
                                    }
                                }

                                loop1index++;
                                v32 = GET32( 0);
                            }
                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].TargetRegionNameLen = loop1index;
                            Nit_Parser.Ext_TargetRegionName_Descriptor[Nit_Parser.ExtTargetRegionNameDescNum].DescriptorValid = TRUE;
                            Nit_Parser.ExtTargetRegionNameDescNum++;
                        }
                        //else
                        {
                            ptr = tempptr;
                            ptr += 2 + descLen;
                        }
                        loopcount += 2 + descLen;
                        tableLen = tableLen - (2 + descLen);

                        v32 = GET32( 0);
                        break;

                    default:
                        tableLen = tableLen - (2 + descLen);
                        loopcount += 2 + descLen;
                        ptr += 2 + descLen;
                        v32 = GET32( 0);
                        break;
                }
                break;
            default:
                tableLen = tableLen - (2 + descLen);
                loopcount += 2 + descLen;
                ptr += 2 + descLen;
                v32 = GET32( 0);
                break;
        }//endswitch
    }//endwhile
    dummy = GETNBITS(v32,0,4);
    Nit_Parser.TsLoopLen = GETNBITS(v32,4,12);
    ptr += 2;
    tableLen = tableLen - 2;
    v32 = GET32( 0);

    ipop_PopulateNIT(demux, (Address)&Nit_Parser,ntfcode /*code*/);
    while( ((tableLen - 4) >  0) && (tsloopIndex < 1))
    {
        Nat32 ParsedPDSD = 0;
        Nit_Parser.TsLoopData[tsloopIndex].NtkNameDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionNameDescNum=0;
        Nit_Parser.TsLoopData[tsloopIndex].TSID = GETNBITS(v32, 0,16);
        Nit_Parser.TsLoopData[tsloopIndex].ONID = GETNBITS(v32, 16,16);
        v32 = GET32( 4);
        dummy = GETNBITS(v32,0,4);
        Nit_Parser.TsLoopData[tsloopIndex].TsDescLoopLen = GETNBITS(v32, 4,12);
        ptr += 6;
        tableLen = tableLen - 6;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < Nit_Parser.TsLoopData[tsloopIndex].TsDescLoopLen)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8); 
            descLen = GETNBITS(v32,8, 8); 

            switch(descTag) {
                case 0x40:
                    Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorTag = GETNBITS(v32, 0,8);
                    Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorLen = GETNBITS(v32, 8,8);
                    Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLen;
                    descLoopLen = HSV_PARSER_MIN(140,Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen); 
                    ptr += 2;
                    memcpy(Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
                    ptr += Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen;
                    v32 = GET32( 0);
                    Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLoopLen;
                    Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorValid = TRUE;
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);
                    v32 = GET32( 0);
                    break;

                case 0x4A:
                    if(Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum<50)
                    {
                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].TSID = GETNBITS(v32, 16,16);
                        v32 = GET32( 4);
                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ONID = GETNBITS(v32, 0,16);
                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ServiceId = GETNBITS(v32, 16,16);
                        v32 = GET32( 8);
                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].LinkageType = GETNBITS(v32, 0,8);

                        ptr += 2 + descLen;
                        v32 = GET32( 0);

                        Nit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x44:
                    if(Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum<10)
                    {
                        Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        ptr += 2;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD);
                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorLen, templen))
                        {

                            Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].Frequency = GETNBITS(v32,0, 32); 
                            v32 = GET32( 4);
                            Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].reserved = GETNBITS(v32,0, 12); 
                            Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].FEC_Outer = GETNBITS(v32,12, 4); 
                            Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].Modulation = GETNBITS(v32,16, 8); 
                            v32 = GET32( 7);
                            Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].SymbolRate = GETNBITS(v32,0, 28); 
                            Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].FEC_Inner = GETNBITS(v32,28, 4); 
                            loop1length += 11;
                            loop1index++;
                            ptr += 11;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].CDSDLen = loop1index;
                        Nit_Parser.TsLoopData[tsloopIndex].CDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].CDSDDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);

                    break;

                case 0x5F:
                    ParsedPDSD = GET32( 2);
                    ptr += 2 + descLen;
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;
                case 0x88:
                    if(Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum<1)
                    {
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].prevPrivateDataSpecifier = ParsedPDSD;
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        ptr += 2;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].HDSLCNDesc);
                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].DescriptorLen, templen))
                        {

                            Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].HDSLCNDesc[loop1index].Service_ID = GETNBITS(v32,0, 16); 
                            Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].HDSLCNDesc[loop1index].Visible_Service_Flag = GETNBITS(v32,16, 1); 
                            Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].HDSLCNDesc[loop1index].reserved1 = GETNBITS(v32,17, 5); 
                            loop1length += 2;
                            ptr += 2;
                            Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].HDSLCNDesc[loop1index].LCNValue = iutil_GetLCNValue( ptr, 16);
                            loop1length += 2;
                            loop1index++;
                            ptr += 2;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].HDSLCNLen = loop1index;
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x83:
                case 0xE2:

                    if(Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum<100)
                    {
                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].prevPrivateDataSpecifier = ParsedPDSD;
                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        ptr += 2;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc);
                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen, templen))
                        {

                            Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
                            loop1length += 2;
                            ptr += 2;
                            Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].LCNValue = iutil_GetLCNValue( ptr, 16);
                            loop1length += 2;
                            loop1index++;
                            ptr += 2;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNLen = loop1index;
                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum++;


                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;
					
				case 0x86: 
					{
						if((ParsedPDSD == RCS_RDS_PDSD_VALUE) && (IS_SYSTEM_NETWORKOPERATOR_RCSRDS))
						{
							
		                    if(Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum<100)
		                    {
		                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].prevPrivateDataSpecifier = ParsedPDSD;
		                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
		                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorTag = GETNBITS(v32, 0,8);
		                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen = GETNBITS(v32, 8,8);
		                        ptr += 2;
		                        v32 = GET32( 0 );
		                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc);
		                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen, templen))
		                        {

		                            Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
		                            loop1length += 2;
		                            ptr += 2;
		                            Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].LCNValue = iutil_GetLCNValue( ptr, 16);
		                            loop1length += 2;
		                            loop1index++;
		                            ptr += 2;
		                            v32 = GET32( 0);
		                        }
		                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNLen = loop1index;
		                        Nit_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorValid = TRUE;
		                        Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum++;
		                    }
		                    else
		                    {
		                        ptr += 2 + descLen;
		                    }
		                    loopcount += 2 + descLen;
		                    tableLen = tableLen - (2 + descLen);

		                    v32 = GET32( 0);
						}
						else if((!(IS_SYSTEM_NETWORKOPERATOR_RCSRDS)) && (eurdiv_IsServiceAttrbDescSupported((ins_GetMedium()))))
						{
		                    if(Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum<10)
		                    {
		                        Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].prevPrivateDataSpecifier = ParsedPDSD;
		                        Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
		                        Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].DescriptorTag = GETNBITS(v32, 0,8);
		                        Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].DescriptorLen = GETNBITS(v32, 8,8);
		                        ptr += 2;
		                        v32 = GET32( 0 );
		                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].ServiceAttributeDesc);
		                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].DescriptorLen, templen))
		                        {

		                            Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].ServiceAttributeDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
		                            Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].ServiceAttributeDesc[loop1index].Reserved = GETNBITS(v32,16, 6); 
		                            Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].ServiceAttributeDesc[loop1index].Numeric_Selection_Flag = GETNBITS(v32,22, 1); 
		                            Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].ServiceAttributeDesc[loop1index].Visible_Service_Flag = GETNBITS(v32,23, 1); 
		                            loop1length += 3;
		                            loop1index++;
		                            ptr += 3;
		                            v32 = GET32( 0);
		                        }
		                        Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].ServiceAttributeLen = loop1index;
		                        Nit_Parser.TsLoopData[tsloopIndex].Service_Attribute_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum].DescriptorValid = TRUE;
		                        Nit_Parser.TsLoopData[tsloopIndex].ServiceAttrDescNum++;
		                    }
		                    else
		                    {
		                        ptr += 2 + descLen;
		                    }
		                    loopcount += 2 + descLen;
		                    tableLen = tableLen - (2 + descLen);

		                    v32 = GET32( 0);
	                	}
						else
						{
	                        ptr += 2 + descLen;
		                    loopcount += 2 + descLen;
		                    tableLen = tableLen - (2 + descLen);

		                    v32 = GET32( 0);
						}
						
	                    break;
					}

                case 0x87:          
                    if(Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum<100)
                    {
						Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].prevPrivateDataSpecifier = ParsedPDSD;
                        Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        ptr += 2;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc);
                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen, templen))
                        {
                            int minLength = 0;
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_ID = GETNBITS(v32,0, 8); 
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth = GETNBITS(v32,8, 8); 
                            minLength = HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth,40);
                            ptr += 2;
                            loop1length += 2;
                            memcpy(Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_Name,ptr, minLength);
                            ptr += Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth;
                            loop1length += Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth;
                            v32 = GET32( 0);
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth = minLength;
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].Country_Code = GETNBITS(v32,0, 24); 
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].DescriptorLen = GETNBITS(v32,24, 8); 
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].LCN2DescLen = 0; /* GETNBITS(v32,32, 0); */ 
                            ptr += 4;
                            loop1length += 4;
                            v32 = GET32( 0 );
                            loop2index = 0, loop2length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc);
                            while( (loop2length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].DescriptorLen, templen))&&
                                    (Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].DescriptorLen<Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen))
                            {

                                Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].LCN2Desc[loop2index].ServiceId = GETNBITS(v32,0, 16); 
                                loop2length += 2;
                                ptr += 2;
                                loop1length += 2;
                                Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].LCN2Desc[loop2index].LCNValue = iutil_GetLCNValue( ptr, 16);
                                loop2length += 2;
                                loop2index++;
                                ptr += 2;
                                loop1length += 2;
                                v32 = GET32( 0);
                            }
                            Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelLstDesc[loop1index].LCN2DescLen = loop2index;
                            loop1index++;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2ChannelListLen = loop1index;
                        Nit_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x62:
                    if(Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum<10)
                    {
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].Reserved = GETNBITS(v32, 16,6);
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].CodingType = GETNBITS(v32, 22,2);
                        ptr += 3;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].FrequencyListDesc);
                        while( loop1length< HSV_PARSER_MIN((descLen - 1) , templen) )
                        {

                            Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].FrequencyListDesc[loop1index].Center_Frequency = GETNBITS(v32,0, 32); 
                            loop1length += 4;
                            loop1index++;
                            ptr += 4;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].FrequencyListLen = loop1index;
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyList_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].FrequencyListDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0x41:
                    if(Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum<10)
                    {
                        Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        ptr += 2;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc);
                        while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen, templen))
                        {

                            Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
                            Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceType = GETNBITS(v32,16, 8); 
                            loop1length += 3;
                            loop1index++;
                            ptr += 3;
                            v32 = GET32( 0);
                        }
                        Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListLen = loop1index;
                        Nit_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorValid = TRUE;
                        Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;
				

                case 0x7F : 
                    descTagExtn = GETNBITS(v32,16, 8); 
                    switch(descTagExtn) {
                        case 0x09:
                            tempptr = ptr;
                            if(Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum<10)
                            {

                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorTagExtn = GETNBITS(v32, 16,8);
                                v32 = GET32( 3);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].CountryCode = GETNBITS(v32, 0,24);
                                ptr += 6;
                                v32 = GET32( 0 );
                                loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion);
                                while( loop1length< HSV_PARSER_MIN( (descLen - 4), templen) )
                                {

                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].reserved = GETNBITS(v32,0, 5); 
                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCodeFlag = GETNBITS(v32,5, 1);
                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth = GETNBITS(v32,6, 2);
                                    ptr += 1;
                                    loop1length++;
                                    v32 = GET32( 0 );
                                    if( Nit_Parser.Ext_TargetRegion_Descriptor[Nit_Parser.ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCodeFlag == 1 ) {    
                                        Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCode = GETNBITS(v32,0, 24); 
                                        ptr+=3;
                                        loop1length+=3;
                                    }
                                    v32 = GET32( 0 );
                                    if (Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 1) {
                                        Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].PrimaryRegionCode = GETNBITS(v32,0, 8);
                                        ptr++;
                                        loop1length++;
                                        if (Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 2) {
                                            Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].SecondaryRegionCode = GETNBITS(v32,8, 8); 
                                            ptr++;
                                            loop1length++;
                                            if (Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth == 3) {
                                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].TertiaryRegionCode = GETNBITS(v32,16, 16);
                                                ptr+=2;
                                                loop1length+=2;
                                            }
                                        }
                                    }

                                    loop1index++;
                                    v32 = GET32( 0);
                                }

                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegionLen = loop1index;
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorValid = TRUE;
                                Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum++;
                            }
                            //else
                            {
                                ptr = tempptr;
                                ptr += 2 + descLen;
                            }
                            loopcount += 2 + descLen;
                            tableLen = tableLen - (2 + descLen);

                            v32 = GET32( 0);
                            break;
                        case 0x0A:
                            tempptr = ptr;
                            if(Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionNameDescNum<10) {

                                tempTsTargetRegNameLen = Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionNameDescNum;

                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].DescriptorTag = GETNBITS(v32,0,8);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].DescriptorLen = GETNBITS(v32,8,8);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].DescriptorTagExtn = GETNBITS(v32,16,8);
                                v32 = GET32( 3);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].CountryCode = GETNBITS(v32,0,24);
                                v32 = GET32( 6);
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].LangCode = GETNBITS(v32,0,24);

                                ptr += 9;
                                v32 = GET32( 0 );
                                loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName);
                                while( loop1length< HSV_PARSER_MIN( (descLen - 7), templen) )
                                {
                                    int minLength = 0;
                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionDepth= GETNBITS(v32,0, 2); 
                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionNameLen= GETNBITS(v32,2, 6); 
                                    minLength = HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionNameLen,80);
                                    ptr += 1;
                                    loop1length++;
                                    memcpy(Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionName,ptr, minLength);

                                    ptr += Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionNameLen;
                                    loop1length += Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionNameLen;
                                    v32 = GET32( 0);
                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionNameLen= minLength;
                                    Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].PrimaryRegionCode= GETNBITS(v32,0, 8); 
                                    ptr += 1;
                                    loop1length++;
                                    v32 = GET32( 0 );
                                    if( Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionDepth >= 2 ) {
                                        Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].SecondaryRegionCode= GETNBITS(v32,0, 8); 
                                        ptr += 1;
                                        loop1length++;
                                        if( Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].RegionDepth >= 3 ) {
                                            Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionName[loop1index].TertiaryRegionCode= GETNBITS(v32,8, 16); 
                                            ptr += 2;
                                            loop1length+=2;
                                            v32 = GET32( 0 );
                                        }
                                    }

                                    loop1index++;
                                    v32 = GET32( 0);
                                }
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].TargetRegionNameLen = loop1index;
                                Nit_Parser.TsLoopData[tsloopIndex].Ext_TargetRegionName_Descriptor[tempTsTargetRegNameLen].DescriptorValid = TRUE;
                                Nit_Parser.TsLoopData[tsloopIndex].ExtTargetRegionNameDescNum++;
                            }
                            //else
                            {
                                ptr = tempptr ;
                                ptr += 2 + descLen;
                            }
                            loopcount += 2 + descLen;
                            tableLen = tableLen - (2 + descLen);

                            v32 = GET32( 0);

                            break; 
                        default:
                            loopcount += 2 + descLen;
                            ptr += 2 + descLen;
                            tableLen = tableLen - (2 + descLen);
                            v32 = GET32( 0);
                            break;
                    }
                    break;
                default:
                    loopcount += 2 + descLen;                   
                    ptr += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);
                    v32 = GET32( 0);
                    break;
            }//endswitch
        }//endwhile descloop
        tsloopIndex++;
        loopcount = 0;
        Nit_Parser.TsLoopDataNum = tsloopIndex; 

        retval = retval && ipop_PopulateNIT(demux, (Address)&Nit_Parser,ntfcode /*code*/);
        tsloopIndex = 0;
    }//endwhile tsloop

	if (code & sec_TableCompleted) {
		ntfcode = sec_TableCompleted;
	 	retval = retval && ipop_PopulateNIT(demux, (Address)&Nit_Parser,ntfcode  /*code */);
    }
	
    dummy = GETNBITS(v32, 0,32);
    return TRUE;

}//end function

#if 0

int CHsvDvbNIT_Priv::GetDescriptorIDOnnit( int descriptor_tag, int cookie )
{
    UNUSED (descriptor_tag);
    UNUSED (cookie);
    return 0;
}
#endif

