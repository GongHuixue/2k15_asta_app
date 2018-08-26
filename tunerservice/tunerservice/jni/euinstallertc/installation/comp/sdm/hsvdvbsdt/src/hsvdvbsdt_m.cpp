
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
 *          %name: hsvdvbsdt_m.c %
 *       %version: TVG_FusionPPV2_13 %
 * %date_modified: Thu Feb 19 17:19:20 2009 %
 *    %derived_by: adarshlr %
 */


#include "_hsvdvbsdt_m.h"

TRACESYMBOL(m, "dvb/sitables/hsvdvbsdt_m")


#ifndef __cplusplus




#else



#endif








DemuxData CHsvDvbSDT_Priv::s__DmxData[HsvDmxLast];




Nat8 CHsvDvbSDT_Priv::s__ModeArray[FILTER_DEPTH];

Nat8 CHsvDvbSDT_Priv::s__MatchArray[FILTER_DEPTH];

Nat8 CHsvDvbSDT_Priv::s__MaskArray[FILTER_DEPTH];


#define BACKGROUND_INSTALLATION (ins_InstallationModeBackground)
#define CURRENT_INST_MODE       (ins_GetInstallationMode()) 


/***************Local Functions******************************************/



























/**************************Initialisations*****************************************/

void CHsvDvbSDT_Priv::pow_Init(void)
{
    HsvDemux dmx;
    int      i;

    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {
        for(i = 0; i < MAX_SECTIONS; i++)
        {
            /* Clear our structures to ensure that we dont have junk values in them*/
            DmxData[dmx].SubscrId[i]        =   HSV_INVALID_SCT_REQUEST;
            DmxData[dmx].SectionInfo[SDT_ACTUAL_INDEX] = conf_SdtActualParsing;
            DmxData[dmx].SectionInfo[SDT_OTHER_INDEX] = conf_SdtOtherParsing;
            DmxData[dmx].OtherSectionValid  =   FALSE;
            DmxData[dmx].ActualOnId         =   0;
            DmxData[dmx].ActualSvcId        =   0;
            DmxData[dmx].TablesReq = 0;
            DmxData[dmx].TablesRecvd = 0;
        }
    }
    for(i=0; i<FILTER_DEPTH; i++)
    {
        ModeArray[i] = 0;
        MatchArray[i] = 0;
        MaskArray[i] = 0;
    }
    MatchArray[0] = SDT_OTHER_TABLE_ID;
    MaskArray[0] = 0xff;
}

void CHsvDvbSDT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbSDT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbSDT_Priv::ena_Enable(HsvDemux dmx)
{

    Nat16 Onid = 0, Tsid = 0;
	HsvSDMSIDataValues sivalues;

    InitTSID(dmx);
    InitONID(dmx);
    InitTSVersionNumber(dmx);
    InitSDTSection(dmx);
    InitOtherSDTSection(dmx);
    InitLinkageInfo(dmx);
    InitOtherTSID(dmx);
    InitOtherONID(dmx);
    InitOtherTSVersionNumber(dmx);
    InitOtherSDTSectionServices(dmx);
    InitTargetRegionDesc(dmx);
	InitServiceAvailablityDesc(dmx);
	InitMultiLingSvcNameDesc(dmx);

    DmxData[dmx].TablesReq = DmxData[dmx].TablesRecvd = 0;
    /* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_ACTUAL_INDEX]))
    {
	#ifndef __cplusplus
		DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SDT_PID_VALUE, SDT_ACTUAL_TABLE_ID, SDT_ACTUAL_TABLE_ID, (HsvSectionCallback)Sdt_Parser_Parser);
	#else
        DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SDT_PID_VALUE, SDT_ACTUAL_TABLE_ID, SDT_ACTUAL_TABLE_ID, FNADDR(Sdt_Parser_Parser));
	#endif
        DmxData[dmx].Version[ SDT_ACTUAL_INDEX ] =   (Nat8)(HSV_INVALID_VERSION);
        DmxData[dmx].TablesReq |= SDT_ACTUAL_REQ;
        ASSERT(DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX] != HSV_INVALID_SCT_REQUEST);
    }
	sivalues.TableId = -1;
	ins_GetSIDetails(&sivalues);
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))
    {
        if(ins_GetAltTSValues( &Onid, &Tsid ))
        {
            TraceNotice(m,"Requesting for SDT_Other%s %d", __FUNCTION__, __LINE__);
            /* Registering for All SDT Others during installation */
            HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID, SDT_PID_VALUE};

            DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig,8, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));

            ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
        } else if(sivalues.TableId == SDT_OTHER_TABLE_ID) {
			TraceNotice(m,"Requesting UPC  SDT_Other%s %d", __FUNCTION__, __LINE__);
            /* Registering for All SDT Others during installation */
            HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID, SDT_PID_VALUE};

            DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig,8, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));

            ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
        }
    }

    DmxData[dmx].TsId               =   HSV_INVALID_TSID;
    DmxData[dmx].OriginalNetworkId  =   HSV_INVALID_NETWORKID;
    DmxData[dmx].OtherSectionValid  =   FALSE;
    DmxData[dmx].ActualOnId         =   0;
    DmxData[dmx].ActualSvcId        =   0;

}

void CHsvDvbSDT_Priv::ena_Disable(HsvDemux dmx)
{

    /* Initialise Sections */

    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_ACTUAL_INDEX]))
    {
        if( DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX] != HSV_INVALID_SCT_REQUEST )
        {
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]);
            DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]           =    HSV_INVALID_SCT_REQUEST;
        }
        else
        {
            /* We had not started subscription before*/
            TraceDebug(m,"We had not started subscription before");
        }
    }
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))
    {
        if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST )
        {
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[SDT_OTHER_INDEX]);
            DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;
        }
        else
        {
            /* We had not started subscription before*/
            TraceDebug(m,"We had not started subscription before");
        }
    }
    else
    {
        TraceDebug(m,"else part of conf_IsActionAllowed, dmx:%d\n",dmx);
    }


    DmxData[dmx].OtherSectionValid             =    FALSE;
    DmxData[dmx].ActualOnId         =   0;
    DmxData[dmx].ActualSvcId        =   0;

    InitTSID(dmx);
    InitONID(dmx);
    InitTSVersionNumber(dmx);
    InitSDTSection(dmx);
    InitOtherSDTSection(dmx);
    InitLinkageInfo(dmx);
    InitOtherTSID(dmx);
    InitOtherONID(dmx);
    InitOtherTSVersionNumber(dmx);
    InitOtherSDTSectionServices(dmx);
    InitTargetRegionDesc(dmx);
	InitServiceAvailablityDesc(dmx);
	InitMultiLingSvcNameDesc(dmx);
    DmxData[dmx].TablesReq = DmxData[dmx].TablesRecvd = 0;

}

void CHsvDvbSDT_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED (dmx);
    /* TODO */
}

      HSVCOMPAREKEY(sdtmainconf,Primary,  HsvSDTSection,Original_NetworkId)

  HSVCOMPAREKEY(sdtmainconf,Secondary,HsvSDTSection,ServiceId)

  HSVCOMPAREKEY(sdtmainconf,Teritiary,HsvSDTSection,TsId)
      /* Not used */

	  
  

      HSVCOMPAREKEY(linkmainconf, Primary, HsvLinkageInfo,ActualOnId)

      HSVCOMPAREKEY(linkmainconf, Secondary, HsvLinkageInfo,ActualSvcId)

  HSVCOMPAREKEY(linkmainconf, Teritiary, HsvLinkageInfo,LinkageType)
      /* Not used */



      HSVCOMPAREKEY(sdtsubconf,Primary,  HsvSDTSection,Original_NetworkId)

  HSVCOMPAREKEY(sdtsubconf,Secondary,HsvSDTSection,TsId)

  HSVCOMPAREKEY(sdtsubconf,Teritiary,HsvSDTSection,ServiceId)

  

      HSVCOMPAREKEY(sdttargetregionconf, Primary,     HsvSDTTargetRegion,   OnId)

      HSVCOMPAREKEY(sdttargetregionconf, Secondary,   HsvSDTTargetRegion,   Tsid)

      HSVCOMPAREKEY(sdttargetregionconf, Teritiary,   HsvSDTTargetRegion,   ServiceId)
      
   	  HSVCOMPAREKEY(sdtsvcavailabilityconf,Primary,HsvSDTCellID,Original_NetworkId)
   	  HSVCOMPAREKEY(sdtsvcavailabilityconf,Secondary,HsvSDTCellID,Tsid)
   	  HSVCOMPAREKEY(sdtsvcavailabilityconf,Teritiary,HsvSDTCellID,ServiceId)

	  
   	  HSVCOMPAREKEY(sdtmultilingsvcnameconf,Primary,HsvSDTMultiLingSvcName,OnId)
   	  HSVCOMPAREKEY(sdtmultilingsvcnameconf,Secondary,HsvSDTMultiLingSvcName,Tsid)
   	  HSVCOMPAREKEY(sdtmultilingsvcnameconf,Teritiary,HsvSDTMultiLingSvcName,ServiceId)
  	  HSVCOMPAREKEY(sdtmultilingsvcnameconf,Quaternary,HsvSDTMultiLingSvcName,LangCode)
   	 

  
#ifdef __cplusplus

HSVCOMPAREKEY(sdtmainconf,Quaternary,HsvSDTSection,ServiceId)

  HSVCOMPAREKEY(linkmainconf, Quaternary, HsvLinkageInfo,Tsid)

  HSVCOMPAREKEY(sdtsubconf,Quaternary,HsvSDTSection,ServiceId)

  HSVCOMPAREKEY(sdttargetregionconf, Quaternary, HsvSDTTargetRegion, CountryCode)

  HSVCOMPAREKEY(sdtsvcavailabilityconf,Quaternary,HsvSDTCellID,ServiceId)


  
  #else

  
Nat8 CHsvDvbSDT_Priv::sdttargetregionconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    ASSERT (! "SDT Table does not have a teritiary key" );
    return FALSE;
}


Nat8 CHsvDvbSDT_Priv::sdtmainconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    return FALSE;
}

Nat8 CHsvDvbSDT_Priv::sdtsubconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    return FALSE;
}

Nat8 CHsvDvbSDT_Priv::linkmainconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    return FALSE;
}
#endif


Bool CHsvDvbSDT_Priv::ipop_PopulateSDT ( HsvDemux dmx , Address pSdt_Parser, int code, Nat32 cookie )
{
	//TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    int retval = TRUE;
    TypeSdt_Parser* ServiceTable = (TypeSdt_Parser*)pSdt_Parser;

    /*  Find which section is recieved */
    if(SDT_ACTUAL_TABLE_ID == ServiceTable->TableId)
    {
        DmxData[dmx].Version[SDT_ACTUAL_INDEX] = ServiceTable->version_number;
        PopulateTSID(dmx, ServiceTable, code);
        PopulateONID(dmx, ServiceTable, code);
        PopulateTSVersionNumber(dmx, ServiceTable, code);
        PopulateSDTSection(dmx, ServiceTable, code);
        PopulateLinkageInfo(dmx, ServiceTable, code);
        PopulateTargetRegionDesc(dmx, ServiceTable, code);
		PopulateServiceAvailabilityDesc(dmx, ServiceTable, code);
		PopulateMultiLingSvcNameDesc(dmx, ServiceTable, code);

    }
    else if(SDT_OTHER_TABLE_ID == ServiceTable->TableId)
    {
        int NetworkOperator = ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator);
        if( ((sysset_GetSystemCountry() == cids_CountryNetherlands)                && 
                ((NetworkOperator == ins_Ziggo) || (NetworkOperator == ins_None))) ||  
                ( eurdiv_SupportSDTOtherInBackgroundInstallation() )
          )
        {
            /* no strapi ntfs.. sent here used for installation which is based on SDT other, currently used for Ziggo */
            mQuickPopulateOtherSDTSectionServices(dmx, ServiceTable, code);
            PopulateTSVersionNumber(dmx, ServiceTable, code);
        } else if(NetworkOperator == ins_UPC) {
			 /* no strapi ntfs.. sent here used for installation which is based on SDT other, currently used for UPC */
		//	TraceNotice(m,"%s:%d UPC SDT Other",__FUNCTION__,__LINE__); 
            mQuickPopulateOtherSDTSectionServices(dmx, ServiceTable, code);
            PopulateTSVersionNumber(dmx, ServiceTable, code);
        }
        else
        {
            DmxData[dmx].Version[SDT_OTHER_INDEX] = ServiceTable->version_number;
            /* This is populating a scalar quantity */
            PopulateOtherSDTSection(dmx, ServiceTable, code);
        }
    }
	//TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    if( sec_TableCompleted  &  code )
    {
	//TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
        if(SDT_ACTUAL_TABLE_ID == ServiceTable->TableId)
        {
            DmxData[dmx].TablesRecvd |= SDT_ACTUAL_REQ;
        }
        if(SDT_OTHER_TABLE_ID == ServiceTable->TableId)
        {
            DmxData[dmx].TablesRecvd |= SDT_OTHER_REQ;
        }
        if( (SDT_ACTUAL_TABLE_ID == ServiceTable->TableId) || (SDT_OTHER_TABLE_ID == ServiceTable->TableId) )
        {
            if(DmxData[dmx].TablesRecvd == DmxData[dmx].TablesReq)
            {
				TraceNotice(m,"%s:%d: sent DataAvilable from SDT",__FUNCTION__,__LINE__);
                DmxData[dmx].TablesReq = 0;
                DmxData[dmx].TablesRecvd = 0;
                /* generate control notifications */
                //if( ctrlN_iPresent())
                {
                    ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT);
                }
            }
        }
    }
    UNUSED(cookie);
    return retval;
}

void CHsvDvbSDT_Priv::InitTSID(HsvDemux dmx)
{
    DmxData[dmx].TsId = HSV_INVALID_TSID;
}

void CHsvDvbSDT_Priv::InitONID(HsvDemux dmx)
{
    DmxData[dmx].OriginalNetworkId = HSV_INVALID_ONID;
}

void CHsvDvbSDT_Priv::InitTSVersionNumber(HsvDemux dmx)
{
    DmxData[dmx].TsVersionNo = 0xff;
}

void CHsvDvbSDT_Priv::InitSDTSection(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_SdtTableActual);
}

void CHsvDvbSDT_Priv::InitOtherSDTSection(HsvDemux dmx)
{
    DmxData[dmx].OtherSectionValid = FALSE;
}

void CHsvDvbSDT_Priv::InitLinkageInfo(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_LinkageInfoMain);
}

void CHsvDvbSDT_Priv::InitOtherTSID(HsvDemux dmx)
{
    DmxData[dmx].TsId = HSV_INVALID_TSID;
}
void CHsvDvbSDT_Priv::InitOtherONID(HsvDemux dmx)
{
    DmxData[dmx].OriginalNetworkId = HSV_INVALID_ONID;
}
void CHsvDvbSDT_Priv::InitOtherTSVersionNumber(HsvDemux dmx)
{
    DmxData[dmx].TsVersionNo = 0xff;
}
void CHsvDvbSDT_Priv::InitOtherSDTSectionServices(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_SdtTableOther);
}

void CHsvDvbSDT_Priv::InitServiceAvailablityDesc(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_SdtSvcAvailability);
}
void CHsvDvbSDT_Priv::InitTargetRegionDesc( HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_SdtTargetRegion);
}
void CHsvDvbSDT_Priv::InitMultiLingSvcNameDesc( HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_SdtMultiLingSvcName);
}


Bool CHsvDvbSDT_Priv::PopulateTSID(HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if( sec_SctArrived  &  code )
    {
        DmxData[dmx].TsId = ServiceTable->transport_stream_id;

        /*  A different ts is getting transmitted at this frequency */
        DmxData[dmx].ActualSectionValid     =   TRUE;
        DmxData[dmx].TsId            = ServiceTable->transport_stream_id;
        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx),HSVSPID(ActualTsId, dvb, sdt),  0, 0, 0, 0);
        /* Delete all entries in the table. This has to be done on notification */

    }
    return TRUE;
}

Bool CHsvDvbSDT_Priv::PopulateONID( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if( sec_SctArrived  &  code )
    {
        DmxData[dmx].OriginalNetworkId = ServiceTable->original_network_id;
        /*  A different ts is getting transmitted at this frequency */
        DmxData[dmx].ActualSectionValid     =   TRUE;
        DmxData[dmx].OriginalNetworkId      = ServiceTable->original_network_id;
        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx),HSVSPID(ActualOriginalNetworkId, dvb, sdt),  0, 0, 0, 0);
        /* Delete all entries in the table. This has to be done on notification */

    }
    return TRUE;
}

Bool CHsvDvbSDT_Priv::PopulateTSVersionNumber( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if( sec_SctArrived  &  code )
    {
        DmxData[dmx].TsVersionNo = ServiceTable->version_number;
        /*  A different ts is getting transmitted at this frequency */
        DmxData[dmx].ActualSectionValid     =   TRUE;
        DmxData[dmx].TsVersionNo            = ServiceTable->version_number;
        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx),HSVSPID(ActualTsVersionNo, dvb, sdt),  0, 0, 0, 0);
        /* Delete all entries in the table. This has to be done on notification */

    }
    return TRUE;
}

Bool CHsvDvbSDT_Priv::PopulateSDTSection( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if(sec_SctArrived  &  code)
    {
        return  PopulateServiceDescriptionSection (dmx, ServiceTable, HSVSPID(ActualTSService, dvb, sdt), srtdbids_SdtTableActual, code);
    }

    else if( sec_TableCompleted  & code )
    {
        return PopulateServiceDescriptionSection (dmx, ServiceTable, HSVSPID(ActualTSService, dvb, sdt), srtdbids_SdtTableActual, code);
    }
    return TRUE;
}

Bool CHsvDvbSDT_Priv::PopulateOtherSDTSection( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if(sec_SctArrived  &  code)
    {
        return  PopulateOtherServiceDescriptionSection (dmx, ServiceTable, HSVSPID(OtherTSService, dvb, sdt),0, 0);
    }

    else if( sec_TableCompleted  &  code )
    {
        return PopulateOtherServiceDescriptionSection(dmx, ServiceTable, HSVSPID(OtherTSService, dvb, sdt),0,0);
    }
    return TRUE;
}

Bool CHsvDvbSDT_Priv::PopulateServiceDescriptionSection(HsvDemux dmx, TypeSdt_Parser *ServiceTable, int Ppty, int tableid, int code)
{
    HsvSDTSection       DbaseVersion;
    int                 i                   = 0;
    int                 j                   = 0;
    int        tsloop      = 0;
    int                 index               = 0;
    Bool                retval              = TRUE;
    int                 svcid               = 0;
    int                 onwid               = 0;
    Bool                changed             = FALSE;

    while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {
            int ServiceDescriptionNum = ServiceTable->TsLoopData[tsloop].ServiceDescNum;

            for( i = 0; i < ServiceDescriptionNum; i++)
            {
                if(ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
                {
                    if( srtdb_QueryOnKey( tableid,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id, 0, (Address)(&DbaseVersion) ) )
                    {   /* Record exists => Update it */
                        /* There can be duplicate service description in the same SDT. In such cases we
                           take the last. Refer corridor discussion with HKK 6/4/05:5:17PM */
                        DbaseVersion.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                        DbaseVersion.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                        DbaseVersion.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                        DbaseVersion.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                        DbaseVersion.VersionNumber              = ServiceTable->version_number ;
                        DbaseVersion.Free_Ci_Mode               = FALSE;
                        DbaseVersion.Match_Brand_Flag           = FALSE;
                        DbaseVersion.NumBrandIds                = 0;

                        AssignServiceDescriptor(ServiceTable,tsloop, i, &DbaseVersion);
                        AssignCipDesc(ServiceTable,tsloop, i, &DbaseVersion);

                        if( srtdb_Update(tableid, ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id,0, (Address)(&DbaseVersion)) )
                        {
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id, 0); /* TODO: Define events */
                        }
                    }
                    else
                    {
                        HsvSDTSection   SDTSection;
                        /* Record does not exist => Insert Fresh */
                        SDTSection.Original_NetworkId         = ServiceTable->original_network_id;
                        SDTSection.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
                        SDTSection.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                        SDTSection.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                        SDTSection.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                        SDTSection.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                        SDTSection.VersionNumber              = ServiceTable->version_number ;
                        SDTSection.Free_Ci_Mode               = FALSE;
                        SDTSection.Match_Brand_Flag           = FALSE;
						SDTSection.NumBrandIds			      = 0;
						SDTSection.TsId         			  = ServiceTable->transport_stream_id;

                        AssignServiceDescriptor(ServiceTable,tsloop, i, &SDTSection);
                        AssignCipDesc(ServiceTable,tsloop, i, &SDTSection);
                        //DP(("PopulateSDTSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid));
                        if( srtdb_Insert( tableid, SDTSection.Original_NetworkId, SDTSection.ServiceId, SDTSection.TsId, 0, (Address)(&SDTSection)) )
                        {
                            srtdb_SearchOnKey(tableid, SDTSection.Original_NetworkId, SDTSection.ServiceId, SDTSection.TsId, 0, (int *)&index);
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, SDTSection.Original_NetworkId, SDTSection.ServiceId, ServiceTable->transport_stream_id);
                        }
                        else
                        {
                            //DP(("PopulateSDTSection:: srtdb_Insert failed,ServiceTable->original_network_id:%d, ServiceTable->TsLoopDataNum[tsloop].service_id:%d\n\n",ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id));
                        }
                    }

                    /* Check for the other SDT service also in the same SDT section */
                    if( TRUE == dvbsvc_GetOtherService  (dmx, &onwid, &svcid) )
                    {
                        for( j = 0; j < ServiceDescriptionNum; j++)
                        {
                            if ((svcid == ServiceTable->TsLoopData[tsloop].service_id) &&
                                    (onwid == ServiceTable->original_network_id) )
                            {
                                /* Record exists => Update it */
                                /* There can be duplicate service description in the same SDT. In such cases we
                                   take the last. Refer corridor discussion with HKK 6/4/05:5:17PM */
                                changed                                                 = DmxData[dmx].OtherSectionValid;
                                DmxData[dmx].OtherSectionValid                          = TRUE;
                                DmxData[dmx].SDTOtherSection.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                                DmxData[dmx].SDTOtherSection.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                                DmxData[dmx].SDTOtherSection.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                                DmxData[dmx].SDTOtherSection.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                                DmxData[dmx].SDTOtherSection.VersionNumber              = ServiceTable->version_number ;
                                DmxData[dmx].SDTOtherSection.Original_NetworkId         = ((Nat16)(onwid));
                                DmxData[dmx].SDTOtherSection.ServiceId                  = ((Nat16)(svcid));

                                AssignServiceDescriptor(ServiceTable, tsloop,j, &DmxData[dmx].SDTOtherSection);

                                if( changed )
                                {
                                    strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherTSService, dvb, sdt), ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id, 0);
                                }
                                else
                                {
                                    strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherTSService, dvb, sdt), ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id );
                                }
                            }
                            else
                            {
                                /* Some service other than the one we were interested in. Continue iterating */
                            }
                        }
                    }
                    else
                    {
                        /* Other service filter was not set ?. Do nothing */
                    }
                }
            }
        }
        else if(sec_TableCompleted  &  code)
        {
            /* Delete services if not present */
            i = srtdb_GetNoOfRecords(tableid) - 1;
            while( 0 <= i )
            {
                /* Only services from SDT actual are inserted into database. */
                /* Version number information from both SDT actual and SDT other is filled into our static structure*/
                /* Ensure that we compare the version number of elements in database against version number of SDT actual */
                if(srtdb_QueryOnIndex(tableid,i,(Address )(&DbaseVersion)))
                {
                    if(DbaseVersion.VersionNumber != DmxData[dmx].Version[ SDT_ACTUAL_INDEX ])
                    {
                        //TraceDebug(m,"PopulateSDTSection::LINE:%d DbaseVersion.VersionNumber:%d",__LINE__,DbaseVersion.VersionNumber);
                        /* delete the record */
                        if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, DbaseVersion.TsId, 0))
                        {
                          //  TraceDebug(m,"Version Number Mismatch Hence Delete is Done");
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, 0);
                        }
                        else
                        {  /* Could not delete */
                            ASSERT(FALSE);
                        }
                    }
                }
                else
                {
                    //TraceDebug(m,"PopulateSDTSection::LINE:%d",__LINE__);
                }
                /* decrement to prev index*/
                i--;
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
        }
        else
        {
            /* Do Nothing */
        }
        tsloop++;
    }
    return retval;
}

Bool CHsvDvbSDT_Priv::PopulateOtherServiceDescriptionSection(HsvDemux dmx, TypeSdt_Parser *ServiceTable, int Ppty, int tableid, int code)
{

    int                 i           = 0;
    Bool                retval      = TRUE;
    int                 svcid       = 0;
    int                 onwid       = 0;
    int         tsloop  = 0;
    // UNUSED( secindex );
    UNUSED (tableid);
    //TraceDebug(m,"%s \n", __FUNCTION__);
    while ( tsloop < ServiceTable->TsLoopDataNum)
    {

        if( sec_SctArrived  &  code )
        {
            if( TRUE == dvbsvc_GetOtherService  (dmx, &onwid, &svcid) )
            {
                int OtherServiceDescriptionNum = ServiceTable->TsLoopData[tsloop].ServiceDescNum;
                for( i = 0; i < OtherServiceDescriptionNum; i++)
                {
                    if ((svcid == ServiceTable->TsLoopData[tsloop].service_id) &&
                            (onwid == ServiceTable->original_network_id) )
                    {   /* Record exists => Update it */
                        /* There can be duplicate service description in the same SDT. In such cases we
                           take the last. Refer corridor discussion with HKK 6/4/05:5:17PM */
                        DmxData[dmx].OtherSectionValid     =   TRUE;

                        DmxData[dmx].SDTOtherSection.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                        DmxData[dmx].SDTOtherSection.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                        DmxData[dmx].SDTOtherSection.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                        DmxData[dmx].SDTOtherSection.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                        DmxData[dmx].SDTOtherSection.VersionNumber              = ServiceTable->version_number ;
                        DmxData[dmx].SDTOtherSection.Original_NetworkId         = ((Nat16)(onwid));
                        DmxData[dmx].SDTOtherSection.ServiceId                  = ((Nat16)(svcid));
					DmxData[dmx].SDTOtherSection.TsId						= 0;

                        AssignServiceDescriptor(ServiceTable, tsloop,i, &DmxData[dmx].SDTOtherSection);
                        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, 0, 0); /* TODO: Define events */
                    }
                }
            }
        }
        else if(sec_TableCompleted  &  code)
            /* Delete services if not present */
        {
            if(ServiceTable->version_number != DmxData[dmx].SDTOtherSection.VersionNumber)
            {
                DmxData[dmx].OtherSectionValid     =   FALSE;
                //strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), ppty, SDTTable->SDTHEADER.Original_NWId, SDTTable->SDTDATA.SvcId, 0, 0); /* TODO: Define events */
                strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), Ppty);
            }
        }
        else
        {
            /* Do Nothing */
        }
        tsloop++;
    }
    return retval;
}



void CHsvDvbSDT_Priv::AssignServiceDescriptor(TypeSdt_Parser *ServiceTable, int tsloop, int i, HsvSDTSection *DbaseVersion)
{
    int len = 0;

    if(TRUE == ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
    {
        Nat8 *SvcName = (Nat8 *)ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceName;

        DbaseVersion->ServiceName[0] = '\0';

        len =   ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceNameLen;

        DbaseVersion->ServiceType   = ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceType;
		memset(DbaseVersion->ServiceName,0x00,MAXSERVICENAMELEN * 2);
		
		charsetutil_MbToWc( SvcName,
                len,
                DbaseVersion->ServiceName,
                MAXSERVICENAMELEN,
                (len >= div_ServiceNameLength) ? TRUE : FALSE
                );
        len =   MAXSERVICENAMELEN;
    }
    DbaseVersion->ServiceName[len] = '\0'; /* Erase Previous Name if invalid*/
}

inline void CHsvDvbSDT_Priv::AssignCipDesc(TypeSdt_Parser* ServiceTable,int tsloop, int i, HsvSDTSection *DbaseVersion)
{
    Nat32 j = 0;
    if( (ServiceTable->TsLoopData[tsloop].CIPlusDescNum > 0) &&
            (ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].DescriptorValid == TRUE) )
    {
        int privatedataspecify = ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].PrivateDataSpecifier;
        if(privatedataspecify != CIP_PRIVATE_DATA_SPEC)
        {
            DbaseVersion->Free_Ci_Mode = 0;
            DbaseVersion->Match_Brand_Flag = 0;
            DbaseVersion->NumBrandIds = 0;
            for(j=0; j < (sizeof(ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].CicamBrandDesc))/sizeof(ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].CicamBrandDesc[0]); j++)
            {
                DbaseVersion->Brand_Ids[j] = 0;
            }
        }
        else
        {
            DbaseVersion->Free_Ci_Mode = ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].Free_Ci_Mode;
            DbaseVersion->Match_Brand_Flag = ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].Match_Brand_Flag;
            for(j=0; j < ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].Cicam_BrandDesc_Len; j++)
            {
                DbaseVersion->Brand_Ids[j] = ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].CicamBrandDesc[j].Cicam_Brand_Identifier;
            }
            DbaseVersion->NumBrandIds = ServiceTable->TsLoopData[tsloop].CI_Plus_Descriptor[i].Cicam_BrandDesc_Len;
			DbaseVersion->Brand_Ids[DbaseVersion->NumBrandIds] = 0;
        }
    }
}
Bool CHsvDvbSDT_Priv::PopulateLinkageInfo ( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    return PopulateLinkageInfoPrivate (dmx, ServiceTable, HSVSPID(LinkageInfo, dvb, sdt), srtdbids_LinkageInfoMain, code);
}


void CHsvDvbSDT_Priv::DeleteServicesOldVersion(HsvSDTSection *DbaseVersion, int tableid)
{
	int from = 0, to = 0, i = 0;
	HsvSDTSection TempDbaseVersion;
	/* Delete services if not present */
	if(srtdb_SearchOnPrimaryAndSecondaryKey(tableid,DbaseVersion->Original_NetworkId,DbaseVersion->TsId,&from,&to) == TRUE)
	{
		for(i = to; i >= from ; i--)
		{
			if(srtdb_QueryOnIndex(tableid,i,(Address )(&TempDbaseVersion)))
			{
				if(DbaseVersion->VersionNumber != TempDbaseVersion.VersionNumber)
				{
					TraceDebug(m,"DeleteServicesOldVersion::LINE:%d DbaseVersion.VersionNumber:%d",__LINE__,DbaseVersion->VersionNumber);
					/* delete the record */
					if (srtdb_Delete(tableid, TempDbaseVersion.Original_NetworkId, TempDbaseVersion.TsId, TempDbaseVersion.ServiceId, 0))
					{
						TraceDebug(m,"Version Number Mismatch Hence Delete is Done");
					}
					else
					{  /* Could not delete */
						ASSERT(FALSE);
					}
				}
				else
				{
					TraceDebug(m,"No Serives with different version");
					break;
				}
			}
		}
	}
}

void CHsvDvbSDT_Priv::mQuickPopulateOtherSDTSectionServices(HsvDemux dmx, TypeSdt_Parser* ServiceTable,  int code)
{
    HsvSDTSection       TmpDbaseVersion, DbaseVersion;
    int i= 0, tsloop = 0, len = 0;
    int tableid = srtdbids_SdtTableOther;

    int NetworkOperator = ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator);	

    while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        if( sec_SctArrived  &  code )
        {
            int ServiceDescriptionNum = ServiceTable->TsLoopData[tsloop].ServiceDescNum;

            for( i = 0; i < ServiceDescriptionNum; i++)
            {
                if(ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
                {
                    DmxData[dmx].OtherSectionValid          = TRUE;

                    DbaseVersion.Original_NetworkId         = ServiceTable->original_network_id;
                    DbaseVersion.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
                    DbaseVersion.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                    DbaseVersion.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                    DbaseVersion.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                    DbaseVersion.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                    DbaseVersion.VersionNumber              = ServiceTable->version_number;
					//TraceNotice(m,"[%s] [%d] VersionNumber[%d] \n",__FUNCTION__,__LINE__,DbaseVersion.VersionNumber);
                    DbaseVersion.Free_Ci_Mode               = FALSE;
                    DbaseVersion.Match_Brand_Flag           = FALSE;
                    DbaseVersion.NumBrandIds                = 0;
					DbaseVersion.TsId						= ServiceTable->transport_stream_id;

					memset(DbaseVersion.ServiceName,0x00,MAXSERVICENAMELEN * 2);
                    /* ServiceName */
/*                    len =   ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceNameLen;
                    charsetutil_MbToWc( (Nat8 *)ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceName,
                            len, DbaseVersion.ServiceName, MAXSERVICENAMELEN, (len >= div_ChannelNameLength) ? TRUE : FALSE );
                    len =   MAXSERVICENAMELEN;
                    DbaseVersion.ServiceName[len] = '\0';*/

					AssignServiceDescriptor(ServiceTable,tsloop, i, &DbaseVersion);
					/*Delete services with old version*/
					if(NetworkOperator == ins_UPC)
					{
						DeleteServicesOldVersion(&DbaseVersion,tableid);
					}

                    if( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, 0,(Address)(&TmpDbaseVersion) ) )
                    {
						if(NetworkOperator == ins_UPC) 
						{
							TraceNotice (m, " UPC: Updating ONID %d, TSID %d, SID %d", DbaseVersion.Original_NetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId);
						}
                        srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, 0,(Address)(&DbaseVersion));
                        if( (CURRENT_INST_MODE == BACKGROUND_INSTALLATION) && (eurdiv_SupportSDTOtherInBackgroundInstallation()))  
                        {
                            //generate a strapiN onchanged here, and we update the svc names
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherTSService, dvb, sdt), ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id, 0); /* TODO: Define events */
                        }
                        else
                        {
                            //TraceDebug(m, "No strapiN generated here for ziggo/telenet which is based on sdt_other");
                        }
                    }
                    else
                    {
						if(NetworkOperator == ins_UPC) 
						{
							TraceNotice (m, " UPC: Inserting ONID %d, TSID %d, SID %d", DbaseVersion.Original_NetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId);
						}
                    	//TraceNotice(m,"[%s] [%d] \n",__FUNCTION__,__LINE__);
						if(srtdb_Insert( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, 0,(Address)(&DbaseVersion)) )
                        {
                        //	 TraceNotice(m,"CURRENT_INST_MODE[%d] BACKGROUND_INSTALLATION[%d] \n",CURRENT_INST_MODE,BACKGROUND_INSTALLATION);
                            if( (CURRENT_INST_MODE == BACKGROUND_INSTALLATION) && (eurdiv_SupportSDTOtherInBackgroundInstallation() || (NetworkOperator == ins_UPC)))  
                            {
                                //generate a strapiN onchanged here, and we update the svc names
                                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherTSService, dvb, sdt), ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id, 0); /* TODO: Define events */
                            }
                            else
                            {
                                //TraceInfo(m, "No strapiN generated here for ziggo/telenet which is based on sdt_other");
                            }
                        }
                        else
                        {
                            //TraceDebug(m,"PopulateSDTOther vector:: srtdb_Insert failed: ServiceTable->original_network_id:%d, ServiceTable->TsLoopDataNum[tsloop].service_id:%d",DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId);
                        }
                    }
                }
            }
        }
        tsloop++;
    }
}

Bool CHsvDvbSDT_Priv::PopulateLinkageInfoPrivate (HsvDemux dmx, TypeSdt_Parser *ServiceTable, int Ppty, int tableid, int code)
{

    Bool    retval  = TRUE;
    int i= 0;
    int tsloop = 0;
    UNUSED (Ppty);
    UNUSED( code );
    while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        int linkagedescnumber = ServiceTable->TsLoopData[tsloop].LinkageDescNum;
        for( i = 0; i < linkagedescnumber; i++)
        {
            if(ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].DescriptorValid )
            {
                /* Copy into our static structure before populating */
                int index = 0;
                /* To populate mulitply Linkage Descriptor */
                if( (ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType == Service_Replacement_Service) )
                {
                    DmxData[dmx].LinkageInfo.LinkageType        = (HsvLinkageType)ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType;
                    DmxData[dmx].LinkageInfo.Original_NetworkId = ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].ONID;
                    DmxData[dmx].LinkageInfo.Tsid               = ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].TSID;
                    DmxData[dmx].LinkageInfo.ServiceId          = ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].ServiceId;
                    DmxData[dmx].LinkageInfo.ActualOnId         = ServiceTable->original_network_id;     /*pr49805 */
                    DmxData[dmx].LinkageInfo.ActualSvcId        = ServiceTable->TsLoopData[tsloop].service_id; /*pr49805 */

                    if( srtdb_SearchOnKey( tableid, ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType,0,(&index) ) )   /*pr49805 */
                    {
                        /*Record exists. Update */
                        if( srtdb_Update( tableid, ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType,0, (Address)(&DmxData[dmx].LinkageInfo) ) )   /*pr49805 */
                        {
                            /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                            strapiN_OnChanged( HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(LinkageInfo, dvb, sdt),ServiceTable->original_network_id,DmxData[dmx].LinkageInfo.ActualSvcId,DmxData[dmx].LinkageInfo.LinkageType ,0 );    /*pr49805 */
                            break;
                        }
                    }
                    else
                    {
                        if( srtdb_Insert( tableid,ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType, 0, (Address)(&DmxData[dmx].LinkageInfo) ) )    /*pr49805 */
                        {
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(LinkageInfo, dvb, sdt), ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType );    /*pr49805 */
                            break;
                        }
                    }
                }
            }
        }
        tsloop++;
    }

    tsloop=0;

    while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        int linkagedescnumber = ServiceTable->TsLoopData[tsloop].LinkageDescNum;
        for( i = 0; i < linkagedescnumber; i++)
        {
            if(ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].DescriptorValid )
            {
                /* Copy into our static structure before populating */
                int index = 0;
                /* To populate mulitply Linkage Descriptor */
                if( (ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType == HDSimulcastNORDIG) )
                {
                    DmxData[dmx].LinkageInfo.LinkageType        = (HsvLinkageType)ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType;
                    DmxData[dmx].LinkageInfo.Original_NetworkId = ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].ONID;
                    DmxData[dmx].LinkageInfo.Tsid               = ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].TSID;
                    DmxData[dmx].LinkageInfo.ServiceId          = ServiceTable->TsLoopData[tsloop].Linkage_Descriptor[i].ServiceId;
                    DmxData[dmx].LinkageInfo.ActualOnId         = ServiceTable->original_network_id;     /*pr49805 */
                    DmxData[dmx].LinkageInfo.ActualSvcId        = ServiceTable->TsLoopData[tsloop].service_id; /*pr49805 */

                    if( srtdb_SearchOnKey( tableid, ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType,0,(&index) ) )   /*pr49805 */
                    {
                        /*Record exists. Update */
                        if( srtdb_Update( tableid, ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType,0, (Address)(&DmxData[dmx].LinkageInfo) ) )   /*pr49805 */
                        {
                            /* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/
                            strapiN_OnChanged( HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(LinkageInfo, dvb, sdt),ServiceTable->original_network_id,DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType,0 );    /*pr49805 */
                            /*TraceDebug(m,"HDSimulCast: Update [%04x|%04x|%04x]   -->   [%04x|%04x|%04x] ",
                                    ServiceTable->original_network_id,
                                    ServiceTable->transport_stream_id,
                                    ServiceTable->TsLoopData[tsloop].service_id,
                                    DmxData[dmx].LinkageInfo.Original_NetworkId,
                                    DmxData[dmx].LinkageInfo.Tsid,
                                    DmxData[dmx].LinkageInfo.ServiceId);*/
                            break;
                        }
                    }
                    else
                    {
                        if( srtdb_Insert( tableid,ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType, 0, (Address)(&DmxData[dmx].LinkageInfo) ) )    /*pr49805 */
                        {
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(LinkageInfo, dvb, sdt), ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType );    /*pr49805 */
                            /*TraceDebug(m,"HDSimulCast: Insert [%04x|%04x|%04x]   -->   [%04x|%04x|%04x] ",
                                    ServiceTable->original_network_id,
                                    ServiceTable->transport_stream_id,
                                    ServiceTable->TsLoopData[tsloop].service_id,
                                    DmxData[dmx].LinkageInfo.Original_NetworkId,
                                    DmxData[dmx].LinkageInfo.Tsid,
                                    DmxData[dmx].LinkageInfo.ServiceId);
									*/
                            break;
                        }
                    }
                }
            }
        }
        tsloop++;
    }
    return retval;
}


/*************************IHsvStream Implementation *******************************/

#define GETINDEX(p) (p - HsvdvbsdtFirstProperty - 1)

int CHsvDvbSDT_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualTsId, dvb, sdt):
        case HSVSPID(ActualOriginalNetworkId, dvb, sdt):
        case HSVSPID(ActualTsVersionNo, dvb, sdt):
        case HSVSPID(OtherTSService, dvb, sdt):
            ASSERT("It is a scalar property !!!");
            break;
        case HSVSPID(ActualTSService, dvb, sdt):
            retval = srtdb_GetNoOfRecords(srtdbids_SdtTableActual);
            break;
        case HSVSPID(LinkageInfo, dvb, sdt):
            retval = srtdb_GetNoOfRecords(srtdbids_LinkageInfoMain);
            break;
        case HSVSPID(OtherTsId, dvb, sdt):
        case HSVSPID(OtherOriginalNetworkId, dvb, sdt):
        case HSVSPID(OtherTsVersionNo, dvb, sdt):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(OtherSDTSection, dvb, sdt):
            retval = srtdb_GetNoOfRecords(srtdbids_SdtTableOther);
            break;
		case HSVSPID(SvcAvailabilty,dvb, sdt):
			retval = srtdb_GetNoOfRecords(srtdbids_SdtSvcAvailability);
			break;
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}


Bool CHsvDvbSDT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualTsId, dvb, sdt):
        case HSVSPID(ActualOriginalNetworkId, dvb, sdt):
        case HSVSPID(ActualTsVersionNo, dvb, sdt):
        case HSVSPID(OtherTSService, dvb, sdt):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(ActualTSService, dvb, sdt):
            retval = srtdb_SearchOnKey(srtdbids_SdtTableActual, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(LinkageInfo, dvb, sdt):
            retval = srtdb_SearchOnKey(srtdbids_LinkageInfoMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(OtherTsId, dvb, sdt):
        case HSVSPID(OtherOriginalNetworkId, dvb, sdt):
        case HSVSPID(OtherTsVersionNo, dvb, sdt):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(OtherSDTSection, dvb, sdt):
            retval = srtdb_SearchOnKey(srtdbids_SdtTableOther, key1, key2, key3, 0,(int *)&index);
            break;
		case HSVSPID(SvcAvailabilty,dvb, sdt):
			retval = srtdb_SearchOnKey(srtdbids_SdtSvcAvailability, key1, key2, key3, 0,(int *)&index);
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

Bool CHsvDvbSDT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);
    switch(prop)
    {
        case HSVSPID(LinkageInfo, dvb, sdt):
            {
                retval = srtdb_QueryOnKey(srtdbids_LinkageInfoMain, key1, key2, key3, 0,(Address)val);

                break;
            }
        case HSVSPID(ActualOriginalNetworkId, dvb, sdt):
            {
                /*
                 * we have to accept the oxFFFF as the valid ONID
                 * as the private_temporary_use type of streams
                 * may have the value of ONID as 0xFF00-0xFFFF
                 * so commented this check and return the ONID whatever
                 * stored in memory TV520 FRS 3201
                 */
                int *pval = (int *)val;
                *pval = DmxData[demux].OriginalNetworkId;
                retval = TRUE;
                break;
            }
        case HSVSPID(ActualTsVersionNo, dvb, sdt):
            {
                if(HSV_INVALID_VERSION != DmxData[demux].TsVersionNo)
                {
                    Nat8 *pval = (Nat8 *)val;
                    *pval = ((Nat8)(DmxData[demux].TsVersionNo));
                    retval = TRUE;
                }
                break;
            }
        case HSVSPID(ActualTsId, dvb, sdt):
            {
                /*
                 * we have to accept the oxFFFF as the valid TSID
                 * otherwise the tuning will fail for the mux having TSID 0xFFFF.
                 * so commented this check and return the TSID whatever
                 * stored in memory
                 */
                 Nat16 *pval = (Nat16 *)val;
                 *pval = DmxData[demux].TsId;
                 retval = TRUE;
                break;
            }
        case HSVSPID(ActualTSService, dvb, sdt):
            retval = srtdb_QueryOnKey(srtdbids_SdtTableActual, key1, key2, key3, 0,(Address)val);
            break;
        case HSVSPID(OtherTSService, dvb, sdt):
            {
                int onwid = 0;
                int svcid = 0;

                if( dvbsvc_GetOtherService  (demux, &onwid, &svcid) )
                {
                    if( onwid == DmxData[demux].SDTOtherSection.Original_NetworkId
                            &&
                            svcid == DmxData[demux].SDTOtherSection.ServiceId)
                    {
                        if(DmxData[demux].OtherSectionValid)
                        {
                            HsvSDTSection *pval = (HsvSDTSection *)val;
                            memcpy(pval, (Address )&DmxData[demux].SDTOtherSection, sizeof(HsvSDTSection));
                            retval = TRUE;
                        }
                    }
                }
                break;
            }
        case HSVSPID(OtherTsId, dvb, sdt):
            /*
             * we have to accept the oxFFFF as the valid TSID
             * otherwise the tuning will fail for the mux having TSID 0xFFFF.
             * so commented this check and return the TSID whatever
             * stored in memory
             */

            if(DmxData[demux].OtherSectionValid)
            {
                Nat16 *pval = (Nat16 *)val;
                *pval = DmxData[demux].OtherTsId;
                retval = TRUE;
            }
            break;

        case HSVSPID(OtherOriginalNetworkId, dvb, sdt):
            /*
             * we have to accept the oxFFFF as the valid ONID
             * as the private_temporary_use type of streams
             * may have the value of ONID as 0xFF00-0xFFFF
             * so commented this check and return the ONID whatever
             * stored in memory TV520 FRS 3201
             */

            if(DmxData[demux].OtherSectionValid)
            {
                int *pval = (int *)val;
                *pval = DmxData[demux].OtherONID;
                retval = TRUE;
            }

            break;

        case HSVSPID(OtherTsVersionNo, dvb, sdt):

            if((HSV_INVALID_VERSION != DmxData[demux].OtherTsVersionNo) &&
                    (DmxData[demux].OtherSectionValid))
            {
                Nat8 *pval = (Nat8 *)val;
                *pval = ((Nat8)(DmxData[demux].OtherTsVersionNo));
                retval = TRUE;
            }
            break;

        case HSVSPID(OtherSDTSection, dvb, sdt):

            if(DmxData[demux].OtherSectionValid)
            {
                retval = srtdb_QueryOnKey(srtdbids_SdtTableOther, key1, key2, key3,0, (Address)val);
            }

            break;
        case HSVSPID(TargetRegion, dvb, sdt):
            retval = srtdb_QueryOnKey(srtdbids_SdtTargetRegion, key1, key2, key3, 0, (Address)val);
            break;
		case HSVSPID(SvcAvailabilty,dvb, sdt):
			retval = srtdb_QueryOnKey(srtdbids_SdtSvcAvailability, key1, key2, key3,0, (Address)val);
			break;
        default:
            ASSERT(!"Unknown Property");
            break;
    }

    return retval;
}

Bool CHsvDvbSDT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualTsId, dvb, sdt):
        case HSVSPID(ActualOriginalNetworkId, dvb, sdt):
        case HSVSPID(ActualTsVersionNo, dvb, sdt):
        case HSVSPID(OtherTSService, dvb, sdt):
        case HSVSPID(OtherTsId, dvb, sdt):
        case HSVSPID(OtherOriginalNetworkId, dvb, sdt):
        case HSVSPID(OtherTsVersionNo, dvb, sdt):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(ActualTSService, dvb, sdt):
            retval = srtdb_QueryOnIndex(srtdbids_SdtTableActual, index, (Address)val);
            break;
        case HSVSPID(LinkageInfo, dvb, sdt):
            retval = srtdb_QueryOnIndex(srtdbids_LinkageInfoMain, index, (Address)val);
            break;
        case HSVSPID(OtherSDTSection, dvb, sdt):
            retval = srtdb_QueryOnIndex(srtdbids_SdtTableOther, index, (Address)val);
            break;
		case HSVSPID(SvcAvailabilty,dvb, sdt):
			retval = srtdb_QueryOnIndex(srtdbids_SdtSvcAvailability, index, (Address)val);
			TraceDebug(m,"SvcAvailabilty return =[%d]",retval);
			break;
		case HSVSPID(MultiLingSvcName, dvb, sdt):
			retval = srtdb_QueryOnIndex(srtdbids_SdtMultiLingSvcName, index, (Address)val);
			break;
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;

}

Bool CHsvDvbSDT_Priv::strapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
    Bool retval = FALSE;

    switch (spid)
    {
	case HSVSPID(OtherSDTSection, dvb, sdt):
		
		if(noofkeys == 1)
		{
			if(srtdb_SearchOnPrimaryKey(srtdbids_SdtTableOther, key1, from, to) == TRUE)
			{
				TraceNotice(m,"%s:%d: from:%d to: %d",__FUNCTION__,__LINE__,*from,*to );
				retval = TRUE;
			}
		
		}
		else if(noofkeys == 2)
		{
			if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_SdtTableOther, key1, key2, from, to) == TRUE)
			{
				TraceNotice(m,"%s:%d: from: %d to: %d",__FUNCTION__,__LINE__,*from,*to );
				retval = TRUE;
			}
		}
		break;
	case HSVSPID(SvcAvailabilty, dvb, sdt):	
		if(noofkeys == 1)
		{
			if(srtdb_SearchOnPrimaryKey(srtdbids_SdtSvcAvailability, key1, from, to) == TRUE)
			{
				TraceNotice(m,"%s:%d: from:%d to: %d",__FUNCTION__,__LINE__,*from,*to );
				retval = TRUE;
			}
		
		}
		else if(noofkeys == 2)
		{
			if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_SdtSvcAvailability, key1, key2, from, to) == TRUE)
			{
				TraceNotice(m,"%s:%d: from: %d to: %d",__FUNCTION__,__LINE__,*from,*to );
				retval = TRUE;
			}
		}
		break;
	case HSVSPID(MultiLingSvcName, dvb, sdt): 
		if(noofkeys == 3)
		{
			if(srtdb_SearchOnPrimarySecondaryAndTeritiaryKey(srtdbids_SdtMultiLingSvcName, key1, key2, key3, from, to) == TRUE)
			{
				TraceNotice(m,"%s:%d: from: %d to: %d",__FUNCTION__,__LINE__,*from,*to );
				retval = TRUE;
			}
		}
		break;
	default:
		break;
    
    }

return retval;
}

Bool CHsvDvbSDT_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool        retval = FALSE;
    HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(dest);

    UNUSED( value );

    switch(filterid)
    {
        case HsvStartMode:
            break;
        case HsvCurrentCountry:
            break;
        case HsvCurrentLanguage:
            break;
        case HsvCurrentProgram:
            break;
        case HsvOtherSDTOnwidId:
            /* Do not react. Let client set the other Svc ID filter also */
            break;
            break;
        case HsvOtherSDTServiceId:
            {
                int             onwid       = 0;
                int             svcid       = 0;
                HsvSDTSection   sdtsection;

				#if 0
				DmxData[dmx].OtherSectionValid      =   FALSE;
                if( dvbsvc_GetOtherService  (dmx, &onwid, &svcid) )
                {
                    /* Other TS service is a filter controlled scalar */
                    if( strapi_GetByKey(dest,HSVSPID(ActualTSService, dvb, sdt), onwid, svcid, 0, (void *)(&sdtsection)) )
                    {
                        /* We already have a service which we are required to monitor */
                        /* Cache it in our static structure so that we can satisfy all requests*/
                        DmxData[dmx].SDTOtherSection        =   sdtsection;
                        DmxData[dmx].OtherSectionValid      =   TRUE;
                    }
                    else
                    {
                        /* We dont have the service cached from SDT actual */
                        /* Invalidate our SDT other cache. It will be repopulated anyways when we get SDT other */

                    }
                }
                else
                {
                    /* GetOtherService failed. Bail out */
                }
				
				if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))
			    {
			        if(ins_GetAltTSValues( &Onid, &Tsid ))
			        {
			            TraceNotice(m,"Requesting for SDT_Other%s %d", __FUNCTION__, __LINE__);
			            /* Registering for All SDT Others during installation */
			            HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID, SDT_PID_VALUE};

			            DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig,8, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));

			            ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
			        } else if(sivalues.TableId == SDT_OTHER_TABLE_ID) {
						TraceNotice(m,"Requesting UPC  SDT_Other%s %d", __FUNCTION__, __LINE__);
			            /* Registering for All SDT Others during installation */
			            HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID, SDT_PID_VALUE};

			            DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig,8, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));

			            ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
			        }
			    }
				#endif

				//TraceNotice (m, "Telenet: OtherSectionValid %d and SDT Other subscriber ID %d INVALID SubID %d  ", DmxData[dmx].OtherSectionValid, \
												DmxData[dmx].SubscrId[SDT_OTHER_INDEX], HSV_INVALID_SCT_REQUEST);
                if( !(DmxData[dmx].OtherSectionValid) )
                {
                    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))
                    {
                        if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] == HSV_INVALID_SCT_REQUEST )
                        {
							TraceNotice (m, "Telenet: SDT Other enabled 1");
                            //sec_CancelSection( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] );
                            DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;

							/* Registering for All SDT Others during installation */
			            	HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID, SDT_PID_VALUE};

			            	DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig,8, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));
							ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
                        }
						
						else
						{
					//		TraceNotice (m, "Telenet: SDT Other already enabled ");
						}
                    }
                    else
                    {
                        /* QAC */
                    }
                }

                retval = TRUE;
                break;
            }
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */
Bool CHsvDvbSDT_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
return FALSE;
}
Bool CHsvDvbSDT_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
return FALSE;
}
Bool CHsvDvbSDT_Priv::strmfltr_Clear    ( HsvDestination dest, int filterid, int value )
{
return FALSE;
}

Bool CHsvDvbSDT_Priv::strmfltr_ForceClear(HsvDestination dest, int filterid, int value)
{
    Bool ret = FALSE;
    
     HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(dest);
    
    // currently only used for belgium/telenet
    if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST ) 
    {
       // TraceNotice(m,"Hsvdvbsdt : strmfltr_ForceClear called: cancelling SDT_Other tableid subscriber %d \n", DmxData[dmx].SubscrId[SDT_OTHER_INDEX]);
       // sec_CancelSection( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] );
        DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;
        ret = TRUE;
    }
    return ret;
}


/*************************************************************/
void CHsvDvbSDT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    int i   = 0;
    int dmx = HsvDmxMain;

    for(i = 0; i < MAX_SECTIONS; i++)
    {
        for(  dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
        {
            if( DmxData[dmx].SubscrId[i] == subscrid )
            {
                /* This was a matching request. Clear our local variables */
                DmxData[dmx].SubscrId[i]  = HSV_INVALID_SCT_REQUEST;
            }
        }
    }
}


   void CHsvDvbSDT_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
   {
   }

	void CHsvDvbSDT_Priv::dmxsecfN_OnRequestNotAllowed ()
	{
	}
void CHsvDvbSDT_Priv::sdtena_SDTReset(int tableid)
{
    int dmx = HsvDmxMain;
    Nat16 Onid, Tsid;

    if(tableid == SDT_ACTUAL_TABLE_ID)
    {
        if(DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX] != HSV_INVALID_SCT_REQUEST)
        {
            //DmxData[dmx].OtherSectionValid  =    FALSE;
            DmxData[dmx].ActualOnId         =   0;
            DmxData[dmx].ActualSvcId        =   0;

            InitTSID(dmx);
            InitONID(dmx);
            InitTSVersionNumber(dmx);
            InitSDTSection(dmx);
            InitLinkageInfo(dmx);			
			InitServiceAvailablityDesc(dmx);

//            sec_ResetRequest( DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]);
        }
        else
        {
            TraceNotice(m,"SDTReset Failure. not in proper state");
        }
    }
    else
    {
        if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))
        {
            if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST )
            {
                //sec_CancelSection(DmxData[dmx].SubscrId[SDT_OTHER_INDEX]);
                DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;
                InitOtherSDTSection(dmx);
                InitOtherTSID(dmx);
                InitOtherONID(dmx);
                InitOtherTSVersionNumber(dmx);
                InitOtherSDTSectionServices(dmx);
            }

            if(ins_GetAltTSValues( &Onid, &Tsid ))
            {
                /* Registering for SDT Other during dynaic case */
				#ifndef __cplusplus
                DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSection3(HSV_MAP_DMX_TO_DEST(dmx), (int)SDT_PID_VALUE, SDT_OTHER_TABLE_ID, Tsid, Onid, SDT_OTHER_COOKIE, (HsvSectionCallback)Sdt_Parser_Parser);
				#else
				DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSection3(HSV_MAP_DMX_TO_DEST(dmx), (int)SDT_PID_VALUE, SDT_OTHER_TABLE_ID, Tsid, Onid, SDT_OTHER_COOKIE, FNADDR(Sdt_Parser_Parser));
				#endif
                DmxData[dmx].Version[ SDT_OTHER_INDEX ] =   (Nat8)(HSV_INVALID_VERSION);

                ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
            }
        }
        else
        {
            TraceNotice(m,"%s %d SDT Other request not possible", __FUNCTION__, __LINE__);
        }
    }
}
void CHsvDvbSDT_Priv::PopulateServiceAvailabilityDesc( HsvDemux dmx, TypeSdt_Parser  *ServiceTable, int code)
{	
	HsvDestination dest = HsvMain;
	int i,tsloop=0;
	int TotalServices=0;
	HsvSDTCellID  CellIDData,CellIDData_temp;
	for(tsloop = 0; tsloop < ServiceTable->TsLoopDataNum; tsloop++)
	{
		if( sec_SctArrived  &  code )
		{
			memset((Address)&CellIDData_temp, 0, sizeof(CellIDData_temp));
			CellIDData.Original_NetworkId        = ServiceTable->original_network_id;
			CellIDData.Tsid        = ServiceTable->transport_stream_id;
			CellIDData.ServiceId=ServiceTable->TsLoopData[tsloop].service_id;
			TraceNotice(m,"ServiceId[%d]",CellIDData.ServiceId);
		    for (i=0;(i<ServiceTable->TsLoopData[tsloop].ServiceAvaiDescNum);i++)
			{
				TraceNotice(m,"Value of i=[%d]:serviceId=[%d]:cell_id_length[%d],",i,CellIDData.ServiceId,
				ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].CellIdLen);
				for(int loop = 0; loop<ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].CellIdLen; loop++)
				{
					TraceNotice(m,"CellIDData.NumGlobalCellIDs=[%d]",CellIDData.NumGlobalCellIDs);
					CellIDData.Availability_flag=ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].availability_flag;
					CellIDData.GlobalCellID[CellIDData.NumGlobalCellIDs] = ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].cellId[loop];
					CellIDData.NumGlobalCellIDs++;					
				}
				if((ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].CellIdLen == 0) && (ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].availability_flag == FALSE))
				{
					CellIDData.Availability_flag=ServiceTable->TsLoopData[tsloop].Service_Availability_Descriptor[i].availability_flag;
				}
				if (srtdb_QueryOnKey( srtdbids_SdtSvcAvailability,CellIDData.Original_NetworkId,CellIDData.Tsid,CellIDData.ServiceId,0,(Address)(&CellIDData_temp))==FALSE)
				{
					int retval =srtdb_Insert(srtdbids_SdtSvcAvailability,CellIDData.Original_NetworkId,CellIDData.Tsid ,CellIDData.ServiceId,0,(Address)(&CellIDData));
					TraceNotice(m,"retval=[%d]",retval);
				}
				else
				{
					int retval1=srtdb_Update(srtdbids_SdtSvcAvailability,CellIDData.Original_NetworkId,CellIDData.Tsid ,CellIDData.ServiceId,0,(Address)(&CellIDData));
					TraceNotice(m,"retval1=[%d]",retval1);
				}		
			}
		}
	}
}

Nat8 CHsvDvbSDT_Priv::GetLanguageId(Nat32 Language)
{
    /* Assume that the lower 3 bytes of the Nat32 contain the 3 byte code */
    char byte1 = (char)((((Nat32)(Language) & 0xFF0000)) >> 16);
    char byte2 = (char)((((Nat32)(Language) & 0xFF00))   >> 8);
    char byte3 = (char)((((Nat32)(Language) & 0xFF)));

    return (Nat8)(mpegserv_GetLanguageId( byte1, byte2, byte3 ));
} 



void CHsvDvbSDT_Priv::PopulateMultiLingSvcNameDesc( HsvDemux dmx, TypeSdt_Parser  *ServiceTable, int code)
{
    int i, j, k, tsloop, len;
    int x = 0;
    HsvSDTMultiLingSvcName DbaseVersion, MultiLingSvcName, TempVersion;
    for(tsloop = 0; tsloop < ServiceTable->TsLoopDataNum; tsloop++)
    {
        if( sec_SctArrived  &  code )
        {
			int NumMultiLingSvcNameDesc = ServiceTable->TsLoopData[tsloop].MultiLingSvcNameDescNum;

            for( i = 0; i < NumMultiLingSvcNameDesc; i++)
            {
                if(ServiceTable->TsLoopData[tsloop].MultiLing_SvcName_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < ServiceTable->TsLoopData[tsloop].MultiLing_SvcName_Descriptor[i].MultiLingSvcNameLen ; j++)
                    {
                        DbaseVersion.OnId				= ServiceTable->original_network_id;
                        DbaseVersion.Tsid				= ServiceTable->transport_stream_id;
                        DbaseVersion.ServiceId          = ServiceTable->TsLoopData[tsloop].service_id;
                        DbaseVersion.LangCode			= GetLanguageId(ServiceTable->TsLoopData[tsloop].MultiLing_SvcName_Descriptor[i].MultiLingSvcNameDesc[j].LangCode);          
                        DbaseVersion.VersionNumber      = ServiceTable->version_number;

						
						Nat8 *SvcName = (Nat8 *)ServiceTable->TsLoopData[tsloop].MultiLing_SvcName_Descriptor[i].MultiLingSvcNameDesc[j].ServiceName;
					
						DbaseVersion.ServiceName[0] = '\0';
					
						len =	ServiceTable->TsLoopData[tsloop].MultiLing_SvcName_Descriptor[i].MultiLingSvcNameDesc[j].ServiceNameLen;
					
						memset(DbaseVersion.ServiceName,0x00,MAXSERVICENAMELEN * 2);
						
						charsetutil_MbToWc( SvcName,
								len,
								DbaseVersion.ServiceName,
								MAXSERVICENAMELEN,
								(len >= div_ServiceNameLength) ? TRUE : FALSE
								);
						len =	MAXSERVICENAMELEN;
						
						DbaseVersion.ServiceName[len] = '\0'; /* Erase Previous Name if invalid*/

						TraceNotice(m,"Adding MultiLingSvcNameDesc with onid: %d tsid: %d, svcid: %d LangCode: %d",DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId,DbaseVersion.LangCode);

                        if ( srtdb_QueryOnKey( srtdbids_SdtMultiLingSvcName, DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId , DbaseVersion.LangCode, (Address)(&TempVersion) ) )
                        {
                            srtdb_Update(srtdbids_SdtMultiLingSvcName, DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId,DbaseVersion.LangCode,(Address)(&DbaseVersion) );
//                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(MultiLingSvcName, dvb, sdt), DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.LangCode);

                        }
                        else
                        {   /* New Record */
                            srtdb_Insert( srtdbids_SdtMultiLingSvcName, DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId,DbaseVersion.ServiceId, (Address)(&DbaseVersion));
//                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(MultiLingSvcName, dvb, sdt), DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                    }
                }           

            }
        }
        else if(sec_TableCompleted  &  code)
        {
            for(k = (srtdb_GetNoOfRecords(srtdbids_SdtMultiLingSvcName) - 1); k >= 0; k--)
            {
                if(srtdb_QueryOnIndex(srtdbids_SdtMultiLingSvcName, k, (Address)(&DbaseVersion)))
                {
                    if(DbaseVersion.VersionNumber != ServiceTable->version_number)
                    {
                        if(srtdb_Delete(srtdbids_SdtMultiLingSvcName, DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId, 0))
                        {
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(MultiLingSvcName, dvb, sdt), DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                    }
                }
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(MultiLingSvcName, dvb, sdt));
        }
    }
}


void CHsvDvbSDT_Priv::PopulateTargetRegionDesc( HsvDemux dmx, TypeSdt_Parser  *ServiceTable, int code)
{
    int i, k, tsloop,HsvEvtNull = 0;
    int x = 0;
    HsvSDTTargetRegion DbaseVersion, TargetRegion;
    for(tsloop = 0; tsloop < ServiceTable->TsLoopDataNum; tsloop++)
    {
        if( sec_SctArrived  &  code )
        {
            /* first check for data in 2nd TsLoop, if not present then only go 1st TsLoop */
            TargetRegion.NetworkId     = 0xFFFF;
            TargetRegion.VersionNumber = ServiceTable->version_number;
            for(i=0; ((i < ServiceTable->TsLoopData[tsloop].ExtTargetRegionDescNum) && (mInterpretCountryCode(ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].CountryCode) == cids_CountryUK)); i++)
            {
                TargetRegion.TsLoop      = 0;
                TargetRegion.OnId        = ServiceTable->original_network_id;
                TargetRegion.Tsid        = ServiceTable->transport_stream_id;
                TargetRegion.CountryCode = mInterpretCountryCode(ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].CountryCode);
                TargetRegion.ServiceId   = ServiceTable->TsLoopData[tsloop].service_id;

                TargetRegion.RegionList.RegionMap [i][MULT_REGION_DEPTH_INDEX]      = ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[0].RegionDepth;
                TargetRegion.RegionList.RegionMap [i][MULT_PRIMARY_INDEX]           = ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[0].PrimaryRegionCode;
                TargetRegion.RegionList.RegionMap [i][MULT_SECONDARY_INDEX]         = ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[0].SecondaryRegionCode;
                TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX]          = ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[0].TertiaryRegionCode;

                switch (ServiceTable->TsLoopData[tsloop].Ext_TargetRegion_Descriptor[i].TargetRegion[0].RegionDepth)
                {
                    case 0:
                    {
                        TargetRegion.RegionList.RegionMap [i][MULT_PRIMARY_INDEX]   = 0xFFFF;
                        TargetRegion.RegionList.RegionMap [i][MULT_SECONDARY_INDEX] = 0xFFFF;
                        TargetRegion.RegionList.RegionMap [i][MULT_TERTIARY_INDEX]  = 0xFFFF;
                        break;
                    }

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
            for (x  = i; x < MAX_REGIONS_PER_SERVICE; x++)
            {
                TargetRegion.RegionList.RegionMap [x][MULT_REGION_DEPTH_INDEX]  = INVALID_REGION_DEPTH;
                TargetRegion.RegionList.RegionMap [x][MULT_PRIMARY_INDEX]   = 0xFFFF;
                TargetRegion.RegionList.RegionMap [x][MULT_SECONDARY_INDEX] = 0xFFFF;
                TargetRegion.RegionList.RegionMap [x][MULT_TERTIARY_INDEX]  = 0xFFFF;
            }

            /* honour the desc values only if it is UK */
            if(TargetRegion.CountryCode == cids_CountryUK)
            {
                if( srtdb_QueryOnKey(srtdbids_SdtTargetRegion, TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.ServiceId, 0,(Address)(&DbaseVersion) ) )
                {
                    if(srtdb_Update(srtdbids_SdtTargetRegion, TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.ServiceId, 0,(Address)(&TargetRegion)))
                    {
                        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, sdt), TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.ServiceId, HsvEvtNull);
                    }
                }
                else
                {
                    if(srtdb_Insert(srtdbids_SdtTargetRegion, TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.ServiceId, 0, (Address)(&TargetRegion)))
                    {
                        strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, sdt), TargetRegion.OnId, TargetRegion.Tsid, TargetRegion.ServiceId);
                    }
                }
            }
        }
        else if(sec_TableCompleted  &  code)
        {
            for(k = (srtdb_GetNoOfRecords(srtdbids_SdtTargetRegion) - 1); k >= 0; k--)
            {
                if(srtdb_QueryOnIndex(srtdbids_SdtTargetRegion, k, (Address)(&DbaseVersion)))
                {
                    if(DbaseVersion.VersionNumber != ServiceTable->version_number)
                    {
                        if(srtdb_Delete(srtdbids_SdtTargetRegion, DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId, 0))
                        {
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, sdt), DbaseVersion.OnId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                    }
                }
            }
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(TargetRegion, dvb, sdt));
        }
    }
}

Nat32 CHsvDvbSDT_Priv::mInterpretCountryCode( Nat32 country )
{
    /* Examine the lower 3 bytes of the country code and try to determine the corresponding country ID in cids */
    Nat32       retval = cids_CountryOther;
    Nat8        byte1, byte2, byte3;

#define HSV_TO_UPPER(x) ( ( (x) >= 'a' && (x) <= 'z' ) ? ( (x) - 'a' + 'A')  : ( (x) ) )

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
#include "hsvcountry.h"
        default:
            break;
    }
    return retval;

}


Nat8 CHsvDvbSDT_Priv::s__mBuffer[4*1024];

Bool CHsvDvbSDT_Priv::Sdt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
	
    register Nat8*ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest); 
    static TypeSdt_Parser Sdt_Parser;
	int	ntfcode = sec_SctArrived;
    Bool retval = TRUE;
    int dummy, loopcount = 0, descTag, descLen = 0, descTagExtn = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0,tableLen = 0, loop1length = 0, templen = 0; 
    UNUSED (crc);
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
    Sdt_Parser.TableId = GETNBITS(v32,0,8);
	//TraceNotice(m, "Parsing SDT table id: %d",Sdt_Parser.TableId);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    Sdt_Parser.section_length = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    Sdt_Parser.transport_stream_id = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    Sdt_Parser.version_number = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    Sdt_Parser.original_network_id = GETNBITS(v32,8,16);
    dummy = GETNBITS(v32,24,8);
    ptr += 11;
    tableLen = tableLen - 11;
    v32 = GET32( 0);
    Sdt_Parser.TsLoopDataNum = 0;   
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
    {
        Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum=0;
        Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum=0;
        Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum=0;
        Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum=0;
		Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum=0;
        //   Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor=0;
        Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum=0;
        // Sdt_Parser.TsLoopData[tsloopIndex].TsLoopData=0;
        Sdt_Parser.TsLoopData[tsloopIndex].service_id = GETNBITS(v32, 0,16);
        dummy = GETNBITS(v32,16,6);
        Sdt_Parser.TsLoopData[tsloopIndex].Eit_Schedule_Flag = GETNBITS(v32, 22,1);
        Sdt_Parser.TsLoopData[tsloopIndex].Eit_Present_Following_Flag = GETNBITS(v32, 23,1);
        Sdt_Parser.TsLoopData[tsloopIndex].running_status = GETNBITS(v32, 24,3);
        Sdt_Parser.TsLoopData[tsloopIndex].free_CA_mode = GETNBITS(v32, 27,1);
        v32 = GET32( 3);
        Sdt_Parser.TsLoopData[tsloopIndex].descriptors_loop_length = GETNBITS(v32, 4,12);
        ptr += 5;
        tableLen = tableLen - 5;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < Sdt_Parser.TsLoopData[tsloopIndex].descriptors_loop_length)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8); 
            descLen = GETNBITS(v32,8, 8); 
            switch(descTag) {
                case 0x48:
                    if(Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum<100)
                    {
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceType = GETNBITS(v32, 16,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = GETNBITS(v32, 24,8);
                        descLoopLen = HSV_PARSER_MIN(80,Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen); 
                        ptr += 4;
                        memcpy(Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderName,ptr,descLoopLen);
                        ptr += Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen;
                        v32 = GET32( 0);
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = descLoopLen;
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = GETNBITS(v32, 0,8);
                        descLoopLen = HSV_PARSER_MIN(80,Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen); 
                        ptr += 1;
                        memcpy(Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceName,ptr,descLoopLen);
                        ptr += Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen;
                        v32 = GET32( 0);
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = descLoopLen;
                        Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorValid = TRUE;
                        Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;
					
				case 0x5d:
					if(Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum<50)
					{
						Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].DescriptorTag = GETNBITS(v32, 0,8);
						Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].DescriptorLen = GETNBITS(v32, 8,8);
						ptr += 2;
						v32 = GET32( 0 );
						loop1index = 0, loop1length = 0, templen = sizeof(Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc);
						while( loop1length< HSV_PARSER_MIN(Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].DescriptorLen, templen))
						{
							Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].LangCode = GETNBITS(v32,0, 24); 
	                        Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ProviderNameLen = GETNBITS(v32, 24,8);
							loop1length += 4;
							ptr += 4;
							v32 = GET32( 0 );
							descLoopLen = HSV_PARSER_MIN(80,Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ProviderNameLen); 
							memcpy(Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ProviderName,ptr,descLoopLen);
							ptr += Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ProviderNameLen;
							loop1length += Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ProviderNameLen;
							v32 = GET32( 0);
							Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ProviderNameLen = descLoopLen;
							
							Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ServiceNameLen = GETNBITS(v32, 0,8);
							descLoopLen = HSV_PARSER_MIN(80,Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ServiceNameLen); 
							ptr += 1;
							loop1length += 1;
							memcpy(Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ServiceName,ptr,descLoopLen);
							ptr += Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ServiceNameLen;
							loop1length += Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ServiceNameLen;
							v32 = GET32( 0);
							Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameDesc[loop1index].ServiceNameLen = descLoopLen;

							loop1index++;
						}
                        Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].MultiLingSvcNameLen = loop1index;
                        Sdt_Parser.TsLoopData[tsloopIndex].MultiLing_SvcName_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum].DescriptorValid = TRUE;
						Sdt_Parser.TsLoopData[tsloopIndex].MultiLingSvcNameDescNum++;
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
                    if(Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum<50)
                    {
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].TSID = GETNBITS(v32, 16,16);
                        v32 = GET32( 4);
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ONID = GETNBITS(v32, 0,16);
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ServiceId = GETNBITS(v32, 16,16);
                        v32 = GET32( 8);
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].LinkageType = GETNBITS(v32, 0,8);
                        ptr += 2 + descLen;
                        v32 = GET32( 0);
                        Sdt_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorValid = TRUE;
                        Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum++;
                    }
                    else
                    {
                        ptr += 2 + descLen;
                    }
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);

                    v32 = GET32( 0);
                    break;

                case 0xCE:
                    if(Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum<5)
                    {
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Free_Ci_Mode = GETNBITS(v32, 16,1);
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Match_Brand_Flag = GETNBITS(v32, 17,1);
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Reserved_Future_Use = GETNBITS(v32, 18,6);

                        ptr += 3;
                        v32 = GET32( 0 );
                        loop1index = 0, loop1length = 0;

                        if(Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Match_Brand_Flag == 1)
                        {
                            Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Number_Of_Entries = GETNBITS(v32, 0,8);
                            ptr += 1;
                            v32 = GET32( 0 );
                            templen = sizeof(Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].CicamBrandDesc)/sizeof(Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].CicamBrandDesc[0]) ;
                            while( loop1length < HSV_PARSER_MIN((Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Number_Of_Entries * 2), (templen * 2)) )
                            {
                                Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].CicamBrandDesc[loop1index].Cicam_Brand_Identifier = GETNBITS(v32,0, 16); 
                                loop1length += 2;
                                loop1index++;
                                ptr += 2;
                                v32 = GET32(0);
                            }

                            if(loop1length < Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Number_Of_Entries * 2)
                            {
                                loop1length = Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Number_Of_Entries * 2;
                            }
                            ptr += descLen - (2 + loop1length);
                        }
                        else
                        {
                            ptr += descLen - (1 + loop1length);
                        }

                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].Cicam_BrandDesc_Len = loop1index;
                        Sdt_Parser.TsLoopData[tsloopIndex].CI_Plus_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum].DescriptorValid = TRUE;
                        Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum++;
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
                            if(Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum<10)
                            {
                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorTagExtn = GETNBITS(v32, 16,8);
                                v32 = GET32( 3);
                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].CountryCode = GETNBITS(v32, 0,24);

                                ptr += 6;
                                v32 = GET32( 0 );
                                loop1index = 0, loop1length = 0, templen = sizeof(Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion);
                                while( loop1length< HSV_PARSER_MIN( (descLen - 4), templen) )
                                {

                                    Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].reserved = GETNBITS(v32,0, 5); 
                                    Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCodeFlag = GETNBITS(v32,5, 1); 
                                    Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth = GETNBITS(v32,6, 2); 
                                    ptr += 1;
                                    loop1length++;
                                    v32 = GET32( 0 );
                                    if(Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCodeFlag == 1)
                                    {
                                        Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].CountryCode = GETNBITS(v32,0, 24);   
                                        ptr += 3;
                                        loop1length+=3;
                                        v32 = GET32( 0 );
                                    }

                                    if( Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 1 ) {
                                        Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].PrimaryRegionCode = GETNBITS(v32,0, 8); 
                                        ptr += 1;
                                        loop1length++;
                                        if( Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 2 ) {
                                            Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].SecondaryRegionCode = GETNBITS(v32,8, 8); 
                                            ptr += 1;
                                            loop1length++;
                                            if( Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].RegionDepth >= 3 ) {
                                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegion[loop1index].TertiaryRegionCode = GETNBITS(v32,16, 16);
                                                ptr += 2;
                                                loop1length +=2;
                                                v32 = GET32( 0 );
                                            }
                                        }
                                    }

                                    loop1index++;
                                    v32 = GET32( 0);
                                }
                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].TargetRegionLen = loop1index;
                                Sdt_Parser.TsLoopData[tsloopIndex].Ext_TargetRegion_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum].DescriptorValid = TRUE;
                                Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum++;
                            }
                            else
                            {
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
					case 0x72:   /*Service availablity descriptor*/
						{
							TraceNotice(m, "Parsing Service availablity descriptor[%x]",0x72);
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].CellIdLen=0;
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].DescriptorLen=0;
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].DescriptorTag=0;
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].availability_flag=0;
							if(Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum < 10)
							{
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].DescriptorTag=GETNBITS(v32, 0,8);
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].DescriptorLen=GETNBITS(v32, 8,8);
							Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].availability_flag=GETNBITS(v32, 16,1);
							ptr+=3;
							v32=GET32(0);
							loop1index = 0, loop1length = 0, templen = sizeof(Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].cellId);
								while( loop1length< HSV_PARSER_MIN(( (Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].DescriptorLen)-1),templen))
								{
								Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].cellId[loop1index]=GETNBITS(v32, 0,16);
								loop1length += 2;
								loop1index++;
								Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].CellIdLen++;
								ptr += 2;
								v32 = GET32(0);
								}
								Sdt_Parser.TsLoopData[tsloopIndex].Service_Availability_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum].DescriptorValid = TRUE;
								Sdt_Parser.TsLoopData[tsloopIndex].ServiceAvaiDescNum++;
							}
						}
                    loopcount += 2 + descLen;
                    tableLen = tableLen - (2 + descLen);
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
        Sdt_Parser.TsLoopDataNum = tsloopIndex;

        retval = retval && ipop_PopulateSDT(demux, (Address)&Sdt_Parser,ntfcode /*code*/, cookie);
        tsloopIndex = 0;

    }//endwhile tsloop

	if (code & sec_TableCompleted)
    {
	    ntfcode = sec_TableCompleted;
	    retval = retval && ipop_PopulateSDT(demux, (Address)&Sdt_Parser,ntfcode /*code*/, cookie);
    }
	
    //TraceInfo(m,"CRC = 0x%x",dummy);   
    dummy = GETNBITS(v32,0,32);
    return retval;      

}//end function



