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
 *       %version: FUSION_TVG_19 %
 * %date_modified: Fri Feb 20 20:07:55 2009 %
 *    %derived_by: anuma %
 */

#include "_hsvdvbnit_m.h"


TRACESYMBOL(m, "dvb/sitables/hsvdvbnit_m")


#ifndef __cplusplus

#else

#endif















//extern Nat32	PrivateDataSpec [MAXCOUNTRY];

//#define DP(x) 	printf x


struct _DmxROMData CHsvDvbNIT_Priv::s__DmxROMData[HsvDmxLast];

Nat8 CHsvDvbNIT_Priv::s__mBuffer[16*1024];


/* Mapping to HsvGlobals using HsvConstellation */
#if 0

Nat8 CHsvDvbNIT_Priv::s__mModulation[7] = 
{
/*0x00 not defined*/					HsvUnknownConstellation,
/*0x01 16 QAM*/							HsvQam16,
/*0x02 32 QAM*/							HsvQam32,
/*0x03 64 QAM*/							HsvQam64,
/*0x04 128 QAM*/						HsvQam128,
/*0x05 256 QAM*/						HsvQam256,
/*0x06 to 0xFF reserved for future use*/HsvUnknownConstellation
};

#endif


const Nat32 CHsvDvbNIT_Priv::PrivateDataSpecifier [MAXCOUNTRY] = 
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
     /* Ukraine    */   0x0028, 
	 /* China      */   0x0028
};


int CHsvDvbNIT_Priv::s__mCurrentONID = 0;

/**********************************************************************************/

/**********************************************************************************/







		/*Poland*/





//static void InitOtherNetworkHDSLCN(HsvDemux dmx);







	/* poland*/















/***************Local Functions******************************************/





 

/**************************Initialisations*****************************************/
Nat8 CHsvDvbNIT_Priv::s__ModeArray[FILTER_DEPTH];

Nat8 CHsvDvbNIT_Priv::s__MatchArray[FILTER_DEPTH];

Nat8 CHsvDvbNIT_Priv::s__MaskArray[FILTER_DEPTH];




void CHsvDvbNIT_Priv::pow_Init(void)
{
    int dmx;
    int      i;
    
    for( dmx = (int)HsvDmxMain; dmx < (int)HsvDmxLast; dmx++ )
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
	MatchArray[0] = NIT_OTHER_TABLE_ID;
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

	Nat32 mode = IHsvSdmControl2_Idle;
    Nat32 PackageId = 0;
	int insMode, insState;
	ins_GetCurrentInstallationState(&insMode, &insState);
    DmxROMData[dmx].NITActualAvail	  = FALSE;
    DmxROMData[dmx].ActualNITVer = 0xFF;
	HsvSDMSIDataValues SiValues;

    InitActualNetworkID(dmx);
    InitNetworkName(dmx);
    InitActualNITVer(dmx);
    InitActualNetworkLCN(dmx);
    InitLinkageInfo(dmx);
	InitActualServiceListDS(dmx);
    InitActualNetworkLCN2(dmx);
    InitActualNetworkHDSLCN(dmx);
    InitActualNetworkLCN3(dmx);		/*Poland*/
    InitOtherNetworkIDInfo(dmx);
    InitOtherNetworkLCN(dmx);
    InitOtherLinkageInfo(dmx);
    InitOtherNetworkLCN2(dmx);
    InitSatelliteDS(dmx);
	InitHeadEndFrequencyList(dmx);
	InitFreesatLinkageInfo(dmx);

    DmxROMData[dmx].TablesReq = DmxROMData[dmx].TablesRecvd = 0;

    switch(sysset_GetSystemCountry())
    {  

#define COUNTRYITEM(a, b, c)    case cids_Country##b:   \
                                    mCurrentONID   =   c + 0x2000; \
                                    break;
#include "hsvcountry.h"
        default:
			mCurrentONID = 0;
			break;
	}
	SiValues.BouquetId = 0xFFFF;
    pakgins_GetSIDetails(&SiValues);
    PackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	
	/* For nit actual */
	if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[NITACTUAL_INDEX]))
	{
		TraceNotice(m,"Nit Actual Section Filter will be Set");
		#ifndef __cplusplus
		DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NIT_ACTUAL_TABLE_ID,NIT_ACTUAL_TABLE_ID, (HsvSectionCallback)Nit_Parser_Parser);
		#else
		DmxROMData[dmx].SubscrId[NITACTUAL_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)NIT_PID_VALUE, NIT_ACTUAL_TABLE_ID,NIT_ACTUAL_TABLE_ID, FNADDR(Nit_Parser_Parser));
		#endif
		DmxROMData[dmx].TablesReq |= NIT_ACTUAL_REQ;
		TraceNotice(m,"TMP_DEBUG NIT actual collection started");
	}
	
	if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[NITOTHER_INDEX]))
	{
		SiValues.TableId = NIT_OTHER_TABLE_ID;
		pakgins_GetSIDetails(&SiValues);
		//TraceNotice(m,"Nit pid : 0x%x",SiValues.Pid);
    	//TraceNotice(m,"TMP_DEBUG call get mode");
		mode = ctrl->GetMode( dmx );
		//TraceNotice(m,"TMP_DEBUG NIT Other collection - SDM mode %d",mode);
	
		if(((IHsvSdmControl2_FreesatNormal == mode) ||(IHsvSdmControl2_FreesatMinimalNitOth == mode)))
		{
			if(SiValues.Pid <= 0x1FFF)
			{
				DmxROMData[dmx].SubscrId[NITOTHER_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx),
																						SiValues.Pid,
																						NIT_OTHER_TABLE_ID,
																						NIT_OTHER_TABLE_ID,
																						FNADDR(Nit_Parser_Parser));
				DmxROMData[dmx].TablesReq |= NIT_OTHER_REQ;
				//TraceNotice(m,"NIT Other collection started PID 0x%x",SiValues.Pid);
			}
		}
		else
		{
			HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, NIT_OTHER_TABLE_ID, NIT_PID_VALUE};

			#ifndef __cplusplus
			DmxROMData[dmx].SubscrId[NITOTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, (HsvSectionFilterCallback)Nit_Parser_Parser);
			#else
			DmxROMData[dmx].SubscrId[NITOTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Nit_Parser_Parser));
			#endif
			
			PrintfNotice("DmxROMData[dmx].SubscrId[NITOTHER_INDEX] = %d ",DmxROMData[dmx].SubscrId[NITOTHER_INDEX]);
		}
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
	InitActualServiceListDS(dmx);
	InitActualNetworkLCN2(dmx);
	InitActualNetworkLCN3(dmx);  /*pOLAND*/
	InitActualNetworkHDSLCN(dmx);
	InitOtherNetworkIDInfo(dmx);
	InitOtherNetworkLCN(dmx);
	InitOtherLinkageInfo(dmx);
	InitOtherNetworkLCN2(dmx);
	InitSatelliteDS(dmx);
	InitHeadEndFrequencyList(dmx);
	InitFreesatLinkageInfo(dmx);

	DmxROMData[dmx].TablesReq = DmxROMData[dmx].TablesRecvd = 0;
}


void CHsvDvbNIT_Priv::ena_Sync(HsvDemux dmx)
{
   UNUSED( dmx );
}

/* check the keys for SDSD, are these correct enough */
HSVCOMPAREKEY(nitsatellitedsdconf, Primary,    HsvNITSatelliteDS, Original_NetworkId)

HSVCOMPAREKEY(nitsatellitedsdconf, Secondary,  HsvNITSatelliteDS, Tsid)

HSVCOMPAREKEY(nitsatellitedsdconf, Teritiary,  HsvNITSatelliteDS, NetworkId)

HSVCOMPAREKEY(nitsatellitedsdconf, Quaternary, HsvNITSatelliteDS, NetworkId)


HSVCOMPAREKEY(nitsrvclstmainconf, Primary,     HsvNITServiceList, Original_NetworkId)

HSVCOMPAREKEY(nitsrvclstmainconf, Secondary, HsvNITServiceList, Tsid)

HSVCOMPAREKEY(nitsrvclstmainconf, Teritiary,   HsvNITServiceList, ServiceId)
/*Below is not used*/

HSVCOMPAREKEY(nitsrvclstmainconf, Quaternary,   HsvNITServiceList, ServiceId)


HSVCOMPAREKEY(nitsrvclstsubconf, Primary,     HsvNITServiceList, Original_NetworkId)

HSVCOMPAREKEY(nitsrvclstsubconf, Secondary, HsvNITServiceList, Tsid)

HSVCOMPAREKEY(nitsrvclstsubconf, Teritiary,   HsvNITServiceList, ServiceId)



HSVCOMPAREKEY(nitlcnmainconf, Primary,     HsvNITLCN, Original_NetworkId)

HSVCOMPAREKEY(nitlcnmainconf, Secondary,   HsvNITLCN, Tsid)

HSVCOMPAREKEY(nitlcnmainconf, Teritiary,   HsvNITLCN, ServiceId)
/*Below is not used */

/*Nat8 nitlcnmainconf_CompareTeritiaryKey( Nat32 key, Address data )
{
	return nitlcnmainconf_Equal;
}*/


#ifndef __cplusplus

HSVCOMPAREKEY(nitlcnmainconf, QuaternaryKey, HsvNITLCN, ServiceId)

HSVCOMPAREKEY(nitlinkmainconf, QuaternaryKey, HsvNITLinkageInfo,LinkageType)

HSVCOMPAREKEY(nitntwkidconf, QuaternaryKey, HsvNITOtherNetworkIdInfo,NetworkId)

HSVCOMPAREKEY(nitlcn2mainconf, QuaternaryKey,   HsvNITLCN2,   ServiceId)

HSVCOMPAREKEY(nithdslcnmainconf, QuaternaryKey,   HsvNITHDSLCN, ServiceId)

HSVCOMPAREKEY(nitlcn3mainconf, QuaternaryKey,   HsvNITLCN3,   ServiceId)

#else


HSVCOMPAREKEY(nitfreqlistconf, Primary,    HsvNITFreqList, Original_NetworkId)

HSVCOMPAREKEY(nitfreqlistconf, Secondary,  HsvNITFreqList, Tsid)

HSVCOMPAREKEY(nitfreqlistconf, Teritiary,  HsvNITFreqList, Original_NetworkId)

HSVCOMPAREKEY(nitfreqlistconf, Quaternary, HsvNITFreqList, Original_NetworkId)


HSVCOMPAREKEY(nithdslcnsubconf, Primary,     HsvNITHDSLCN, Original_NetworkId)

HSVCOMPAREKEY(nithdslcnsubconf, Secondary,   HsvNITHDSLCN, Tsid)

HSVCOMPAREKEY(nithdslcnsubconf, Teritiary,   HsvNITHDSLCN, ServiceId)

Nat8 CHsvDvbNIT_Priv::nithdslcnsubconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}

HSVCOMPAREKEY(nitlcn2subconf, Primary,     HsvNITLCN2,  CountryCode)

HSVCOMPAREKEY(nitlcn2subconf, Secondary,   HsvNITLCN2,   ChannelListId)

HSVCOMPAREKEY(nitlcn2subconf, Teritiary,   HsvNITLCN2,   ServiceId)

Nat8 CHsvDvbNIT_Priv::nitlcn2subconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}

HSVCOMPAREKEY(nitlcnsubconf, Primary,     HsvNITLCN, Original_NetworkId)

HSVCOMPAREKEY(nitlcnsubconf, Secondary,   HsvNITLCN, Tsid)

HSVCOMPAREKEY(nitlcnsubconf, Teritiary,   HsvNITLCN, ServiceId)

Nat8 CHsvDvbNIT_Priv::nitlcnsubconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}

HSVCOMPAREKEY(nitlinksubconf, Primary,   HsvNITLinkageInfo,Original_NetworkId)

HSVCOMPAREKEY(nitlinksubconf, Secondary, HsvNITLinkageInfo,Tsid)

HSVCOMPAREKEY(nitlinksubconf, Teritiary, HsvNITLinkageInfo,LinkageType)

Nat8 CHsvDvbNIT_Priv::nitlinksubconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}


#endif


HSVCOMPAREKEY(nitlinkmainconf, Primary,   HsvNITLinkageInfo,Original_NetworkId)

HSVCOMPAREKEY(nitlinkmainconf, Secondary, HsvNITLinkageInfo,Tsid)

HSVCOMPAREKEY(nitlinkmainconf, Teritiary, HsvNITLinkageInfo,LinkageType)
/*Below is not used */


HSVCOMPAREKEY(nitntwkidconf, Primary, HsvNITOtherNetworkIdInfo,NetworkId)
/*Below is not used*/

HSVCOMPAREKEY(nitntwkidconf, Secondary, HsvNITOtherNetworkIdInfo,NetworkId)

HSVCOMPAREKEY(nitntwkidconf, Teritiary, HsvNITOtherNetworkIdInfo,NetworkId)


HSVCOMPAREKEY(nitlcn2mainconf, Primary,     HsvNITLCN2,  CountryCode)

HSVCOMPAREKEY(nitlcn2mainconf, Secondary,   HsvNITLCN2,   ChannelListId)

HSVCOMPAREKEY(nitlcn2mainconf, Teritiary,   HsvNITLCN2,   ServiceId)
/*Below is not used*/


HSVCOMPAREKEY(nithdslcnmainconf, Primary,     HsvNITHDSLCN, Original_NetworkId)

HSVCOMPAREKEY(nithdslcnmainconf, Secondary,   HsvNITHDSLCN, Tsid)

HSVCOMPAREKEY(nithdslcnmainconf, Teritiary,   HsvNITHDSLCN, ServiceId)
/*Below is not used*/



HSVCOMPAREKEY(nitlcn3mainconf, Primary,     HsvNITLCN3, Original_NetworkId)

HSVCOMPAREKEY(nitlcn3mainconf, Secondary,   HsvNITLCN3, Tsid)

HSVCOMPAREKEY(nitlcn3mainconf, Teritiary,   HsvNITLCN3, ServiceId)

/*Below is not used*/



HSVCOMPAREKEY(nitHeadEndFrequencyListconf, Primary,    HsvHeadEndFrequencyList, Original_NetworkId)

HSVCOMPAREKEY(nitHeadEndFrequencyListconf, Secondary,  HsvHeadEndFrequencyList, Tsid)

HSVCOMPAREKEY(nitHeadEndFrequencyListconf, Teritiary,  HsvHeadEndFrequencyList, NetworkId)

HSVCOMPAREKEY(nitHeadEndFrequencyListconf, Quaternary, HsvHeadEndFrequencyList, NetworkId)

HSVCOMPAREKEY(nitFreesatLinkageconf, Primary,     HsvFreesatLinkageInfo, OriginalNetworkId)

HSVCOMPAREKEY(nitFreesatLinkageconf, Secondary,   HsvFreesatLinkageInfo, Tsid)

HSVCOMPAREKEY(nitFreesatLinkageconf, Teritiary,   HsvFreesatLinkageInfo, ServiceId)

/*
Nat8 nitcablesubconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}
*/


Nat8 CHsvDvbNIT_Priv::nitsrvclstsubconf_CompareQuaternaryKey( Nat32 key, Address data )
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

Nat8 CHsvDvbNIT_Priv::nitntwkidconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}

Nat8 CHsvDvbNIT_Priv::nitlcn2mainconf_CompareQuaternaryKey( Nat32 key, Address data )
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
Nat8 CHsvDvbNIT_Priv::nitlcn3mainconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}

Nat8 CHsvDvbNIT_Priv::nitFreesatLinkageconf_CompareQuaternaryKey( Nat32 key, Address data )
{
	UNUSED (key);
	UNUSED (data);
	return FALSE;
}

Bool CHsvDvbNIT_Priv::ipop_PopulateNIT ( HsvDemux dmx , Address pNit_Parser, int code )
{
    int retval = TRUE;
	int mode = IHsvSdmControl2_Idle;
	TypeNit_Parser* NetWkTable = (TypeNit_Parser*)pNit_Parser;
	//TraceInfo(m,"ipop_PopulateNIT");

	if(NIT_ACTUAL_TABLE_ID == NetWkTable->TableId)
	{
		PopulateActualNetworkID(dmx, NetWkTable, code);
		PopulateNetworkName(dmx, NetWkTable, code);
		PopulateActualNITVer(dmx, NetWkTable, code);
		PopulateActualNetworkLCN(dmx, NetWkTable, code);
		PopulateLinkageInfo(dmx, NetWkTable, code);
		PopulateActualServiceListDS(dmx,NetWkTable, code);
		PopulateNetworkLCN2(dmx, NetWkTable, code);
		PopulateActualNetworkLCN3(dmx, NetWkTable, code);        /*Cyfrowy*/
        PopulateNetworkHDSLCN(dmx, NetWkTable, code);
		PopulateNetworkSDSD(dmx, NetWkTable, code);
		PopulateHeadEndFrequencyList(dmx, NetWkTable, code);
		PopulateFreesatLinkageInfo(dmx, NetWkTable, code);
	}
	else if(NIT_OTHER_TABLE_ID == NetWkTable->TableId)
	{
		/* PopulateOtherNetworkIDInfo(dmx, NetWkTable, code);
		PopulateOtherNetworkLCN(dmx, NetWkTable, code);
		PopulateOtherLinkageInfo(dmx, NetWkTable, code);
		PopulateOtherNetworkLCN2(dmx, NetWkTable, code);
		PopulateOtherNetworkHDSLCN(dmx, NetWkTable, code);
		*/
//		PrintfNotice("	NITT_OTHER_TABLE_ID ");
		PopulateNetworkSDSD(dmx, NetWkTable, code);
		PopulateFreesatLinkageInfo(dmx, NetWkTable, code);
	}

    if( sec_TableCompleted & code )
    {
		if(NIT_ACTUAL_TABLE_ID == NetWkTable->TableId)
		{
			DmxROMData[dmx].TablesRecvd |= NIT_ACTUAL_REQ;
		}
		if(NIT_OTHER_TABLE_ID == NetWkTable->TableId)
		{
			mode = ctrl->GetMode(dmx);
			if((IHsvSdmControl2_FreesatNormal == mode) || (IHsvSdmControl2_FreesatMinimalNitOth == mode))
			{
				DmxROMData[dmx].TablesRecvd |= NIT_OTHER_REQ;
			}
		}
		/* Only in case of NIT actual or NIT other, notify the change in information */
		if( (NIT_ACTUAL_TABLE_ID == NetWkTable->TableId) || (NIT_OTHER_TABLE_ID == NetWkTable->TableId ))
        {   
            /* generate control notifications */
            if(DmxROMData[dmx].TablesRecvd == DmxROMData[dmx].TablesReq)
            {
                DmxROMData[dmx].TablesReq = 0;
                DmxROMData[dmx].TablesRecvd = 0;
                if( ctrlN_iPresent())
                {
                    ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT);
                    //TraceNotice(m,"%s NIT collection Notification send to SDM",__FUNCTION__);
                }
            }
            else
            {
            		//TraceNotice(m,"%s Table recived 0x%x and Table Requested 0x%x not matched",__FUNCTION__,DmxROMData[dmx].TablesRecvd, DmxROMData[dmx].TablesReq);
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
void CHsvDvbNIT_Priv::InitOtherNetworkLCN2(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_NitLcn2TableSub);
}
void CHsvDvbNIT_Priv::InitActualNetworkLCN3(HsvDemux dmx)                 /*Cyfrowy*/
{
	UNUSED (dmx);
	srtdb_Init(srtdbids_NitLcn3TableMain);
}
void CHsvDvbNIT_Priv::InitSatelliteDS(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_NitSatelliteDS);
}
void CHsvDvbNIT_Priv::InitHeadEndFrequencyList(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_NitHeadEndFrequencyList);
}

void CHsvDvbNIT_Priv::InitFreesatLinkageInfo(HsvDemux dmx)
{
	UNUSED (dmx);
	srtdb_Init(srtdbids_NitFreesatLinkageInfo);
}

Bool CHsvDvbNIT_Priv::PopulateActualNetworkID( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
    UNUSED( code );
	if( sec_SctArrived & code )
    {

        DmxROMData[dmx]. NetworkId  = NetWkTable->NetworkId;
	 DmxROMData[dmx].NITActualAvail = TRUE;
        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualNetworkID, dvb, nit),  0, 0, 0, 0); 
        strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualNetworkID, dvb, nit));
    }
   return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateActualNITVer( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
	if( sec_SctArrived & code )
    {
        DmxROMData[dmx].ActualNITVer = NetWkTable->VersionNo;
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateNetworkName(HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code)
{
    int len = 0;
    int HsvEvtNull = 0;
	int stringlen = MAX_NETWORK_NAME_SIZE;

    if( sec_SctArrived & code )
    {
        if(NetWkTable->NetworkName_Descriptor.DescriptorValid)
        {  
            Nat8 *NwName = (Nat8 *) NetWkTable->NetworkName_Descriptor.NetworkName;
            
            len = NetWkTable->NetworkName_Descriptor.NetworkNameLen;
		
			charsetutil_MbToWcEx( NwName, len, DmxROMData[dmx].NetworkName, &stringlen, FALSE);
			DmxROMData[dmx].NetworkName[stringlen] = 0; 
		
            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(NetworkName, dvb, nit),  0, 0, 0, HsvEvtNull); 
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(NetworkName, dvb, nit));
        }
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkIDInfo( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    HsvNITOtherNetworkIdInfo DbaseVersion, TempVersion; 
    HsvNITOtherNetworkIdInfo OtherNtwkInfo; 
    Nat16 NetworkId = NetWkTable->NetworkId;
	int stringlen = MAX_NETWORK_NAME_SIZE;

	//printf("%s\r\n",__FUNCTION__);
	
	if( sec_SctArrived & code )
    {
		if((NetWkTable->TableId == NIT_OTHER_TABLE_ID) && (NetWkTable->NetworkName_Descriptor.DescriptorValid))
        {
            OtherNtwkInfo.VersionNumber = NetWkTable->VersionNo;
            OtherNtwkInfo.NetworkId = NetworkId;
            //{
                Nat8 *NwName = (Nat8 *) NetWkTable->NetworkName_Descriptor.NetworkName;
                int len = NetWkTable->NetworkName_Descriptor.NetworkNameLen;
                
                charsetutil_MbToWcEx( NwName, len, OtherNtwkInfo.Name, &stringlen , FALSE);
            //}
        //}
            
            if ( srtdb_QueryOnKey( srtdbids_NitOtherNetworkIdTable, NetworkId, 0 , 0,0, (Address)(&TempVersion) ) )
            {
                srtdb_Update(srtdbids_NitOtherNetworkIdTable, NetworkId, 0, 0,0, (Address)(&OtherNtwkInfo) );
                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0, 0); 
            }
            else
            {
                //printf("%s: Inserted Other NetworkID = %d\r\n",__FUNCTION__,NetworkId);
                srtdb_Insert( srtdbids_NitOtherNetworkIdTable, NetworkId, 0, 0, 0, (Address)(&OtherNtwkInfo));
                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0);
            }
        }
    }
    else if(sec_TableCompleted & code)
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
					//printf("%s: Deleted Other NetworkID = %d\r\n",__FUNCTION__,NetworkId);
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
    
    if(sec_SctArrived & code)
    {
        return  PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkLCN, dvb, nit), srtdbids_NitLcnTableMain, code);
    }
    else if( sec_TableCompleted & code )
    {
        return PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkLCN, dvb, nit), srtdbids_NitLcnTableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkLCN(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived & code)
    {
        return  PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkLCN, dvb, nit), srtdbids_NitLcnTableSub, code);
    }
    else if( sec_TableCompleted & code )
    {
		return PopulateLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkLCN, dvb, nit), srtdbids_NitLcnTableSub, code );
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
   
    HsvNITLCN DbaseVersion; 
    HsvNITLCN LogicalChannel; 
    int i = 0, tsloop = 0, j = 0;
    Nat16 vis_flag;
    int privatedataspecify = 0;	
	Nat16 TempLCNVal;

	while ( tsloop < NetWkTable->TsLoopDataNum)
	{
		if( sec_SctArrived & code )
		{
			int numlogicalchannelinfo = NetWkTable->TsLoopData[tsloop].LCNDescNum;
			
			for( i = 0; i < numlogicalchannelinfo; i++)
			{
				if(NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].DescriptorValid)
				{
					for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNLen ; j++)
					{
                        Nat16 serviceid = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId;
                        //DP(("PopulateLogicalChannel::LINE:%d serviceid:%d,tableid:%d\n\n",__LINE__,serviceid,tableid));		
                        privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].PrivateDataSpecifier;
                        
                        //TraceNotice(m,"Function : %s Line : %d privatedataspecify : %d:LCN = %d\r\n",__FUNCTION__,__LINE__,privatedataspecify,NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue);
                        TempLCNVal = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue ;
                        Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify, TempLCNVal,&vis_flag);    
                        Nat16 vflag = vis_flag;
                        //TraceNotice(m,"Function : %s Line : %d VisFlag : %d SID : %d:LCN = %d\r\n",__FUNCTION__,__LINE__,vis_flag,serviceid,lcn);
                        
                        //DP(("PopulateLogicalChannel::LINE:%d LCNValue:%d,tableid:%d\n\n",__LINE__,NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue,tableid));						
                        //DP(("PopulateLogicalChannel::LINE:%d lcn:%d,tableid:%d\n\n",__LINE__,lcn,tableid));						
                        
                        if(lcn != 0xFFFF)
                        {
                            if ( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if( ( DbaseVersion.NetworkId == NetWkTable->NetworkId ) && (   DbaseVersion.VersionNumber != NetWkTable->VersionNo )   )
                                {
                                    Bool LCNChanged = FALSE;
                                    Bool LCNAvailChanged = FALSE; /*fixme: This is not yet parsed */
                                    //int privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].PrivateDataSpecifier;
                                    //Nat16 lcn = NetWkTable->TsLoopData[i].LCN_Descriptor[i].LCNDesc[i].LCNValue;//mInterpretLCNValue(privatedataspec , NetWkTable->TsLoopData[i].LCN_Descriptor[i].LCNDesc[i].LCNValue);    
                                    //Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify , NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue, &vis_flag);    
                                    //Nat16 vflag =   vis_flag;
                                
                                    if( DbaseVersion.LogicalChannelNum != lcn)
                                    {
                                        DbaseVersion.LogicalChannelNum = lcn;
                                        LCNChanged = TRUE;
                                    }
                                    DbaseVersion.VisibleService     = vflag;  
                                
                                    DbaseVersion.VersionNumber = NetWkTable->VersionNo;
                                
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
                                //printf("%s::New LCN added = %d for svcid = %d, ntk id = %d\r\n", __FUNCTION__, LCDesc.Logical_Channel_Info[i].LogicalChannelNum, LCDesc.Logical_Channel_Info[i].ServiceId,NetWkTable->NITHEADER.Attrib);
                                LogicalChannel.NetworkId          = NetWkTable->NetworkId;
                                LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                                LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                                LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId;
                                LogicalChannel.LogicalChannelNum  = lcn;
                                //DP(("PopulateLogicalChannel ELSE LINE 779::LINE:%d lcn:%d,tableid:%d\n\n",__LINE__,lcn,tableid));			
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
		else if(sec_TableCompleted & code)
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
						if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid,0, DbaseVersion.ServiceId))
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

Bool CHsvDvbNIT_Priv::PopulateNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{

	if(sec_SctArrived & code)
    {
        return PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(ActualNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableMain, code);
    }
    else if(sec_TableCompleted & code)
    {
        return   PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(ActualNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived & code)
    {
        return  PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(OtherNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableSub, code);
    }
    else if(sec_TableCompleted & code)
    {
        return PopulateLogicalChannel2(dmx, NetWkTable, HSVSPID(OtherNetworkLCN2, dvb, nit),srtdbids_NitLcn2TableSub, code);
    }
    return TRUE;

}

Bool CHsvDvbNIT_Priv::PopulateLogicalChannel2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
    
    HsvNITLCN2 DbaseVersion; 
    HsvNITLCN2 LogicalChannel; 
    int i,j,k;
    //Nat16 vis_flag;
    int tsloop = 0;
//    int privatedataspecify = 0;	
	Nat16 TempLcnVal;
    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
        {
            int numlogicalchanne2linfo = NetWkTable->TsLoopData[tsloop].LCN2DescNum;
            for( i = 0; i < numlogicalchanne2linfo; i++)
            {
                if(NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelListLen ; j++)
                    {
                        //privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].PrivateDataSpecifier;
                       // printf("Function : %s Line : %d privatedataspecify : %d\r\n",__FUNCTION__,__LINE__,privatedataspecify);

                        Nat32  countrycode   = mInterpretCountryCode(NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Country_Code);
                        //Nat32 Country_Code = mInterpretCountryCode(TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Code); 
                        Nat8  channellistid = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_ID;
                        for( k = 0; k < NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2DescLen ; k++)
                        {
                            
                            TempLcnVal = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].LCNValue ;
							Nat16 lcn = TempLcnVal & 0x03FF;
							Nat16 vflag = (Nat16 ) ( (TempLcnVal & 0x8000) >> 15);
                            //printf("Function : %s Line : %d LCNafterinterprete : %d VisFlag : %d SID : %d, LCN = %d\r\n",__FUNCTION__,__LINE__,lcn,vis_flag,serviceid,lcn);

                            //printf("Before Query teh lcn valu is,  : %d\r\n",lcn);					  
                            //    Bool  vflag =   pLCDesc2->LogicalChannel2Wrapper[j].LCN2Info[i].VisibleServiceFlag2;
                            //Nat16 vflag =   vis_flag;		  
                            
                            if ( srtdb_QueryOnKey( tableid, countrycode, channellistid, 0, 0,(Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                Bool LCNChanged = FALSE;
                                
                                // printf("Inside the Query lcn valu is,  : %d\r\n",lcn);					  	  
                                //Nat16 lcn =     pLCDesc2->LogicalChannel2Wrapper[j].LCN2Info[i].LogicalChannelNum2;
                                //int privatedataspecify = NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].PrivateDataSpecifier;
                                //Nat16 lcn = mInterpretLCNValue(privatedataspecify , NetWkTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2Desc[k].LCNValue, &vis_flag);    			
                                //    Bool  vflag =   pLCDesc2->LogicalChannel2Wrapper[j].LCN2Info[i].VisibleServiceFlag2;
                                //Nat16 vflag =   vis_flag;   
								if( ( DbaseVersion.LogicalChannelNum != lcn ) && (  DbaseVersion.VersionNumber != NetWkTable->VersionNo ) )
                                {
                                    DbaseVersion.LogicalChannelNum = lcn;
                                    LCNChanged = TRUE;
                                }
								if (  DbaseVersion.VersionNumber != NetWkTable->VersionNo )  
								{
                                DbaseVersion.VisibleService     = vflag;  
                                
                                DbaseVersion.VersionNumber = NetWkTable->VersionNo;
                                
                                //printf("In the update part of population, Updated LCN : %d\r\n",lcn);
                                
                                srtdb_Update(tableid, countrycode, channellistid, 0,0, (Address)(&DbaseVersion) );
                                
                                if(LCNChanged)
                                {
                                    strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.CountryCode,DbaseVersion.ChannelListId, 0, 0); 
									}
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
                                LogicalChannel.LogicalChannelNum  = lcn;
                              //  printf("Else New Record: Lcn = %d, SvcId = %d, channellist = %d, country = %d \r\n",lcn, LogicalChannel.ServiceId,LogicalChannel.ChannelListId,LogicalChannel.CountryCode);					  		  
                                LogicalChannel.VisibleService     = vflag;
                                LogicalChannel.VersionNumber      = NetWkTable->VersionNo;
                                
                               // printf("%s:%d :: SID=%d LCN=%d\n", __FUNCTION__, __LINE__, LogicalChannel.ServiceId, LogicalChannel.LogicalChannelNum);
                                
                                srtdb_Insert( tableid, LogicalChannel.CountryCode, LogicalChannel.ChannelListId, 0, 0, (Address)(&LogicalChannel));
                                
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, LogicalChannel.CountryCode, LogicalChannel.ChannelListId, 0);
                            }
                        }
                    }
                }
            }
        }	  
        
        else if(sec_TableCompleted & code)
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
                            //printf("Deleted the lcn = %d\r\n",DbaseVersion.LogicalChannelNum);
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.CountryCode, DbaseVersion.ChannelListId, 0);
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
Bool CHsvDvbNIT_Priv::PopulateActualNetworkLCN3( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)						/*Cyfrowy*/
{
    
    if(sec_SctArrived & code)
    {
        return  PopulateLogicalChannel3(dmx, NetWkTable, HSVSPID(ActualNetworkLCN3, dvb, nit), srtdbids_NitLcn3TableMain, code);
    }
    else if( sec_TableCompleted & code )
    {
        return PopulateLogicalChannel3(dmx, NetWkTable, HSVSPID(ActualNetworkLCN3, dvb, nit), srtdbids_NitLcn3TableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateLogicalChannel3 ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)		/*Cyfrowy*/
{
   
    HsvNITLCN3 DbaseVersion;        /*HsvNITLCN-> HsvNITLCN3*/
    HsvNITLCN3 LogicalChannel; 
    int i = 0, tsloop = 0, j = 0;
	Nat16 vflag = TRUE;
	Nat16 lcn;

	while ( tsloop < NetWkTable->TsLoopDataNum)
	{
		if( sec_SctArrived & code )
		{
			int numlogicalchannelinfo = NetWkTable->TsLoopData[tsloop].LCN3DescNum;
			
			for( i = 0; i < numlogicalchannelinfo; i++)
			{
				if(NetWkTable->TsLoopData[tsloop].LCN3_Descriptor[i].DescriptorValid)
				{
					for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCN3_Descriptor[i].LCN3Len ; j++)
					{
                        Nat16 serviceid = NetWkTable->TsLoopData[tsloop].LCN3_Descriptor[i].LCN3Desc[j].ServiceId;
                        
						lcn = NetWkTable->TsLoopData[tsloop].LCN3_Descriptor[i].LCN3Desc[j].ChannelId ;
                        if(lcn != 0xFFFF)
                        {
                            if ( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if( ( DbaseVersion.NetworkId == NetWkTable->NetworkId ) && (  DbaseVersion.VersionNumber != NetWkTable->VersionNo )  )
                                {
                                    Bool LCNChanged = FALSE;
                                    Bool LCNAvailChanged = FALSE; /*fixme: This is not yet parsed */
                                   
                                    if( DbaseVersion.LogicalChannelNum != lcn)
                                    {
                                        DbaseVersion.LogicalChannelNum = lcn;
                                        LCNChanged = TRUE;
                                    }
                                    DbaseVersion.VisibleService     = vflag;  
                                
                                    DbaseVersion.VersionNumber = NetWkTable->VersionNo;
                                
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
                                //printf("%s::New LCN added = %d for svcid = %d, ntk id = %d\r\n", __FUNCTION__, LCDesc.Logical_Channel_Info[i].LogicalChannelNum, LCDesc.Logical_Channel_Info[i].ServiceId,NetWkTable->NITHEADER.Attrib);
                                LogicalChannel.NetworkId          = NetWkTable->NetworkId;
                                LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                                LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                                LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].LCN3_Descriptor[i].LCN3Desc[j].ServiceId;
                                LogicalChannel.LogicalChannelNum  = lcn;
                                //DP(("PopulateLogicalChannel ELSE LINE 779::LINE:%d lcn:%d,tableid:%d\n\n",__LINE__,lcn,tableid));			
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
		else if(sec_TableCompleted & code)
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
						if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid,0, DbaseVersion.ServiceId))
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


Bool CHsvDvbNIT_Priv::PopulateNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived & code)
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableMain, code);
    }
      
    else if( sec_TableCompleted & code )
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(ActualNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableMain, code);
    }
    return TRUE;
}

Bool CHsvDvbNIT_Priv::PopulateNetworkSDSD(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
	return mPopulateSatelliteDSPrivate(dmx, NetWkTable, HSVSPID(SatelliteDS, dvb, nit), srtdbids_NitSatelliteDS, code);
}

Bool CHsvDvbNIT_Priv::PopulateHeadEndFrequencyList(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
	return mPopulateHeadEndFrequencyList(dmx, NetWkTable, HSVSPID(HeadEndFrequencyList, dvb, nit), srtdbids_NitHeadEndFrequencyList, code);
}

Bool CHsvDvbNIT_Priv::PopulateOtherNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{


    if(sec_SctArrived & code)
    {
        return PopulateHDSLogicalChannel (dmx, NetWkTable, HSVSPID(OtherNetworkHDSLCN, dvb, nit),srtdbids_NitHDSLcnTableSub, code);
    }
      
    else if( sec_TableCompleted & code )
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
    
    //printf("Function : %s Line : %d\r\n",__FUNCTION__,__LINE__);
    while ( tsloop < NetWkTable->TsLoopDataNum)
    {	
        if( sec_SctArrived & code )
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
                        
						privatedataspecify = NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].PrivateDataSpecifier;
                        
						Nat16 lcn = mInterpretLCNValue(NetWkTable->TsLoopData[tsloop].ONID,privatedataspecify , NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].HDSLCNDesc[j].LCNValue, &vis_flag);              
						Nat16 vflag =   vis_flag;

                        if ( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID,NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) ) )
                        {
                            /* Record Exists - Update the information & notify if needed*/
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
                        {   /* New Record */
                            LogicalChannel.NetworkId          = NetWkTable->NetworkId;
                            LogicalChannel.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
                            LogicalChannel.Tsid               = NetWkTable->TsLoopData[tsloop].TSID;
                            LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].HDSLCN_Descriptor[i].HDSLCNDesc[j].Service_ID;
                            LogicalChannel.LogicalChannelNum  = lcn;
                            LogicalChannel.VisibleService     = vflag;
                            LogicalChannel.VersionNumber      = NetWkTable->VersionNo;
                            //printf("Function : %s Line : %d SID : %d HDSLCN : %d\r\n",__FUNCTION__,__LINE__,LogicalChannel.ServiceId,LogicalChannel.LogicalChannelNum);
                            srtdb_Insert( tableid, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId , LogicalChannel.ServiceId, (Address)(&LogicalChannel));
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId);
                        }
                    }
                }
            }
        }
        else if(sec_TableCompleted & code)
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
        tsloop++;
    }	
    return TRUE;
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
      if( sec_SctArrived & code )
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
					
					if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI) || (linkage.LinkageType == EPG_Service) || (linkage.LinkageType == SGT_Ref_Service))
					{
                
						if( srtdb_QueryOnKey( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&DbaseVersion)) )
						{
							/*Record exists. Update */
							if( srtdb_Update( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&linkage)))
							{                                            
								/* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/                  
									//printf("HYSVC : hsvdvbnit_m.c : strapiN called for LinkageInfo Onid = %d, Tsid = %d\n",linkage.Original_NetworkId, linkage.Tsid);
									strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),  HsvEvtNull );
							}
						}
						else
						{
							//printf("%s: @ %d :: OnId = %d, TsId=%d, Type=%d\n", __FUNCTION__, __LINE__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
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
									//printf("HYSVC : hsvdvbnit_m.c : strapiN called for LinkageInfo Onid = %d, Tsid = %d\n",linkage.Original_NetworkId, linkage.Tsid);
									strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),  HsvEvtNull );
							}
						}
						else
						{
							//printf("%s: @ %d :: OnId = %d, TsId=%d, Type=%d\n", __FUNCTION__, __LINE__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
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
    else if(sec_TableCompleted & code)
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


Bool CHsvDvbNIT_Priv::PopulateActualServiceListDS( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
    return PopulateServiceListDS(dmx, NetWkTable, HSVSPID(ActualServiceList, dvb, nit), srtdbids_NitSrvclstTableMain, code);
}

Bool CHsvDvbNIT_Priv::PopulateServiceListDS ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
    HsvNITServiceList DbaseVersion, TempVersion; 
    int i= 0;
    int tsloop = 0; 
    int j = 0;

    //TraceInfo(m,"Function : %s Line : %d",__FUNCTION__,__LINE__);
    while ( tsloop < NetWkTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
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

    if(sec_TableCompleted & code)
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

Bool CHsvDvbNIT_Priv::PopulateFreesatLinkageInfo( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)
{
	HsvFreesatLinkageInfo DbaseVersion, CurrentVersion;
	Nat16 LoopIndex = 0;
	Nat16 LinkageTypeIndex = 0;
	Nat16 LinkageType = 0;
	Nat16 FreesatLDIndex = 0;

	if( sec_SctArrived & code )
	{
		//TraceNotice(m,"No of Freesat LD %d",NetWkTable->FreesatLinkageDescNum);
		while(FreesatLDIndex < NetWkTable->FreesatLinkageDescNum)
		{
			//TraceNotice(m,"No Services in LD %d & PDSD %d",NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDescNum,NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].PrivateDataSpecifier);
			while((LoopIndex < NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDescNum) && (FREESAT_PDSD_VALUE == NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].PrivateDataSpecifier))
			{
				CurrentVersion.VersionNumber = NetWkTable->VersionNo;
				CurrentVersion.ServiceId = NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDesc[LoopIndex].ServiceId;
				CurrentVersion.OriginalNetworkId = NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDesc[LoopIndex].ONID;
				CurrentVersion.Tsid = NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDesc[LoopIndex].TSID;
				CurrentVersion.NetworkId = NetWkTable->NetworkId;
				CurrentVersion.FreeSatelliteLinkageTypeBitMap = 0;
				LinkageTypeIndex = 0;
				while(LinkageTypeIndex < NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDesc[LoopIndex].TunnelledTypeLoopLen)
				{
					LinkageType = NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDesc[LoopIndex].TunnelledLinkageType[LinkageTypeIndex];
					CurrentVersion.FreeSatelliteLinkageTypeBitMap |= (((LinkageType >= 0x0) && (LinkageType <= 0xB)) ? (1 << LinkageType) : 0);
					LinkageTypeIndex++;
				}

				if ( srtdb_QueryOnKey( srtdbids_NitFreesatLinkageInfo, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId , 0, (Address)(&DbaseVersion) ) )
				{
					srtdb_Update(srtdbids_NitFreesatLinkageInfo, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId,0,(Address)(&CurrentVersion) );
					strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLinkageInfo, dvb, nit), CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId, CurrentVersion.ServiceId);
					//TraceDebug(m,"Update LinkageInfo:  OIND 0x%x  TSID 0x%x SID 0x%x ", CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
				}
				else
				{
					srtdb_Insert( srtdbids_NitFreesatLinkageInfo, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId,CurrentVersion.ServiceId, (Address)(&CurrentVersion));
					strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLinkageInfo, dvb, nit), CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
					//TraceDebug(m,"Add LinkageInfo:  OIND 0x%x  TSID 0x%x SID 0x%x ", CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
				}

				LoopIndex++;
			}

			/*reset the count value to avoid duplicate population*/
			//NetWkTable->FreesatLinkage_Descriptor[FreesatLDIndex].FreesatLinkageDescNum = 0;
			FreesatLDIndex++;
		}
	}
	if(sec_TableCompleted & code)
	{
		LoopIndex = srtdb_GetNoOfRecords(srtdbids_NitFreesatLinkageInfo);

		while(LoopIndex > 0)
		{
			LoopIndex--;
			if(srtdb_QueryOnIndex(srtdbids_NitFreesatLinkageInfo,LoopIndex,(Address )(&DbaseVersion)))
			{
				if(DbaseVersion.VersionNumber != NetWkTable->VersionNo)
				{
					strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLinkageInfo, dvb, nit), DbaseVersion.OriginalNetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
				}
			}
		}
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLinkageInfo, dvb, nit));
	}
	return TRUE;
}
int CHsvDvbNIT_Priv::ConvertBcdToDecimal (int bcdvalue)
{
	Nat32 nibble;
	Nat32 decimalval = 0;
	Nat8 count = 0;

	while (count < 8)
	{
        count++;
        nibble = (bcdvalue  & 0xF0000000) >> 28;
        decimalval = (decimalval * 10) + nibble;
        bcdvalue <<= 4;
	}

	return decimalval;
}

int CHsvDvbNIT_Priv::MapModulationType (Nat8 modln)
{
	Nat8 retval = -1;

	switch (modln)
	{
	case 0:
		/* Auto */
		break;
	case 1:
		retval = 1;
		break;
	case 2:
		retval = 2;
		break;
	case 3:
		/* Auto */
		break;
	}
	return retval;
}

Nat8 CHsvDvbNIT_Priv::MapFECInner (Nat8 fec)
{
	Nat8 retval = 1;

	switch(fec)
	{
		case 1:
			 retval = IHsvSatelliteFrontEnd_FECInner12; 
			 break;
		case 2: 
			retval = IHsvSatelliteFrontEnd_FECInner23;     
			break;
		case 3: 
			retval = IHsvSatelliteFrontEnd_FECInner34;		
			break;
		case 4: 
			retval = IHsvSatelliteFrontEnd_FECInner56;		
			break;
		case 5: 
			retval = IHsvSatelliteFrontEnd_FECInner78;		
			break;
		case 6: 
			retval = IHsvSatelliteFrontEnd_FECInner89;		
			break;
		case 7: 
			retval = IHsvSatelliteFrontEnd_FECInner35;		
			break;
		case 8: 
			retval = IHsvSatelliteFrontEnd_FECInner45;		
			break;
		case 9: 
			retval = IHsvSatelliteFrontEnd_FECInner910;		
			break;
		case 10: 
			retval = 12;		
			break;
	}

	return retval;
}

Nat8 CHsvDvbNIT_Priv::MapPolarization (Nat8 pol)
{
	Nat8 retval = 1;

	//retval = (pol == 0) ? 1 : 2;

	switch(pol)
	{
		case 0:
		case 2: retval = 0;     // h/l
				break;
		case 1:
		case 3: retval = 1;		// v/r
				break;
	}

	return retval;
}

int CHsvDvbNIT_Priv::MapModulationStd (Nat8 modlnstd)
{
	return ((modlnstd == 0) ? DVBS: DVBS2);	//0. DVBS 1. DVBS2
}
Bool CHsvDvbNIT_Priv::mPopulateSatelliteDSPrivate(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
	/* The datatypes are same for both Actual and Other. So using just one instance */
    HsvNITSatelliteDS DbaseVersion, TempVersion;
    
    int i, HsvEvtNull = 0,j = 0, tsloop = 0;

	//TraceNotice(m,"code %d NetWkTable->TsLoopDataNum %d",code,NetWkTable->TsLoopDataNum);
	if( sec_SctArrived & code )
	{
		while ( tsloop < NetWkTable->TsLoopDataNum)
		{
			//TraceNotice(m,"NetWkTable->TsLoopData[tsloop].SDSDDescNum %d",NetWkTable->TsLoopData[tsloop].SDSDDescNum);
			for( i = 0; i < NetWkTable->TsLoopData[tsloop].SDSDDescNum;i++)
			{
				if (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].DescriptorValid ) 
				{
					DbaseVersion.VersionNumber		= NetWkTable->VersionNo;
					DbaseVersion.NetworkId			= NetWkTable->NetworkId;
					DbaseVersion.Tsid				= NetWkTable->TsLoopData[tsloop].TSID;
					DbaseVersion.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
					
					for( j = 0; j < NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSDLen ; j++)
					{					
						DbaseVersion.Frequency		= (ConvertBcdToDecimal (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Frequency)) * 10;
						DbaseVersion.ModulationType = MapModulationType (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationtype);
						DbaseVersion.SymbolRate		= (ConvertBcdToDecimal(NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].SymbolRate)) * 100;
						DbaseVersion.FECInner		= MapFECInner(NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].FEC_Inner);
						DbaseVersion.Polarization   = MapPolarization (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Polarization);
						DbaseVersion.RollOff		= NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].RollOff;
						DbaseVersion.ModulationSystem = MapModulationStd (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationsystem);
						DbaseVersion.OrbitalPosition = ConvertBcdToDecimal ((NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].OrbitalPostion & 0xFFFF));
						DbaseVersion.WestEastFlag = NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].WestEastFlag;
					}

					if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
					{
						if(FALSE == srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion) ))
						{
							ASSERT(FALSE);
						}
						else
						{
							strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, HsvEvtNull); 
							//TraceNotice(m,"TMP_DEBUG SDSD updated ONID %d TSID %d NID %d", DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
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
							//TraceNotice(m,"TMP_DEBUG SDSD added ONID %d TSID %d NID %d", DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
							//TraceNotice(m,"Frequency: %d Mod.System %d Mod.Type %d FECInner %d RollOff %d",DbaseVersion.Frequency,DbaseVersion.ModulationSystem,DbaseVersion.ModulationType, DbaseVersion.FECInner, DbaseVersion.RollOff);
						}
					}
				}
			}
			tsloop++;
    	}	
	}	
	else if(sec_TableCompleted & code)
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
					{  
						/* Could not delete */
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

Bool CHsvDvbNIT_Priv::mPopulateHeadEndFrequencyList(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)
{
	/* The datatypes are same for both Actual and Other. So using just one instance */
    int i, HsvEvtNull = 0,j = 0, tsloop = 0;
	HsvHeadEndFrequencyList DbaseVersion, TempVersion;    
    	
	if( sec_SctArrived & code )
	{
			for( i = 0; i < NetWkTable->HeadEndFreqDescNum; i++)
			{
				//PrintfNotice("%s %d", __FUNCTION__, NetWkTable->HeadEndFreq_Descriptor[i].DescriptorValid);
				if (NetWkTable->HeadEndFreq_Descriptor[i].DescriptorValid ) 
				{
					DbaseVersion.VersionNumber		= NetWkTable->VersionNo;
					DbaseVersion.NetworkId			= NetWkTable->NetworkId;
					//DbaseVersion.Original_NetworkId = NetWkTable->TsLoopData[tsloop].ONID;
					DbaseVersion.Original_NetworkId = 0;
					
					//PrintfNotice("%s %d", __FUNCTION__, NetWkTable->HeadEndFreq_Descriptor[i].HeadEndFreqLen);
					for( j = 0; j < NetWkTable->HeadEndFreq_Descriptor[i].HeadEndFreqLen ; j++)
					{					
						DbaseVersion.SiteHeadEndFrequency = NetWkTable->HeadEndFreq_Descriptor[i].HeadEndFreqDescriptor[j].SiteHeadEndFrequency;
						DbaseVersion.Tsid      			  = NetWkTable->HeadEndFreq_Descriptor[i].HeadEndFreqDescriptor[j].TSID;
						
						//PrintfNotice("%s %d %d %d", __FUNCTION__, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
						if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
						{
							if(FALSE == srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion) ))
							{
								//PrintfNotice("%s %d %d %d", __FUNCTION__, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
								ASSERT(FALSE);
							}
							else
							{
								//PrintfNotice("%s %d %d %d", __FUNCTION__, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
								strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, HsvEvtNull); 
							}
						}
						else
						{
							/* New Record */
							if(FALSE == srtdb_Insert(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion) ))
							{
								//PrintfNotice("%s %d %d %d", __FUNCTION__, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
								ASSERT(FALSE);
							}
							else
							{
								//PrintfNotice("%s %d %d %d", __FUNCTION__, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
								strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
							}
						}
					}
				}
		
    	}	
	}	
	else if(sec_TableCompleted & code)
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
					PrintfNotice("%s %d %d %d", __FUNCTION__, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
					if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId,0))
					{  
						 strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
					}
					else
					{  
						/* Could not delete */
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
		case 0x2114:	/* Germany */
		case 0x22D4:	/* Spain */
		case 0x212C:    /* Greece */
		case 0x2028: 	/* Austria */
        case 0x20E9:    /* Estonia */
		case 0x4080:	/* Beijing */
		case 0x4481:	/* Guangzhou */
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
        default:
            break;
        
    }
    //printf("Deduce PvtDataSpec %d\n", PrivateDataSpecifier);
    return PrivDataSpecifier;
}


/*****************************************************************************************/
Nat16 CHsvDvbNIT_Priv::mInterpretLCNValue(int NITOnid, int privatedataspecify, Nat16 lcnvalue, Nat16 *vis_flag)
{
	Nat16 lcnVal = 0xFFFF;
    Nat32 PackageId = 0;


    PackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);

	if(PackageId == POLAND_N_PACKAGE_ID)
	{
		if(privatedataspecify == 0x00B0)
		{
			lcnVal		=  (Nat16 ) (lcnvalue & 0x03FF );
			*vis_flag	=  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
			//TraceNotice(m,"POL_N: LCN = %d, visflag = %d, privatedataspecify = %d\r\n",lcnVal, *vis_flag, privatedataspecify);		
		}
		else
		{
			lcnVal		=  0xFFFF;
			*vis_flag	=  1;
			//TraceNotice(m,"POL_N: privatedataspecify doesn't match");		
		}
	}
	else if(PackageId == SMART_HDPLUS_PACKAGE_ID)
	{
		if(privatedataspecify == 0x003F)
		{
			lcnVal		=  (Nat16 ) (lcnvalue & 0x03FF );
			*vis_flag	=  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
			//TraceNotice(m,"POL_SMART_HD+: LCN = %d, visflag = %d, privatedataspecify = %d\r\n",lcnVal, *vis_flag, privatedataspecify);		
		}
		else
		{
			lcnVal		=  0xFFFF;
			*vis_flag	=  1;
			//TraceNotice(m,"POL_SMART_HD+: privatedataspecify doesn't match");		
		}
	}
	else
	{
		lcnVal		=  (Nat16 ) (lcnvalue & 0x03FF );
		*vis_flag	=  (Nat16 ) ( (lcnvalue & 0x8000) >> 15);
	    //TraceNotice(m,"LCN = %d, visflag = %d, privatedataspecify = %d\r\n",lcnVal, *vis_flag, privatedataspecify);		
	}
	return lcnVal;
}
#if 0

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
    
    for(i=0; i<7; i++)  /* 7 as per Delivery System Descriptor standards */
    {
        result += ((*symrate >> (i*4)) & 0xf) * Multiplier;
        Multiplier *= 10;
    }

    result = result*100;

    *symrate = result;

	return result;
	//DP(("mInterpretSymbolRate::LINE:%d IntereptedSymbolrate:%d,tableid:%d\n\n",__LINE__,result,tableid));
}
#endif
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
            ASSERT(("It is a scalar propert !!!"));
            break;
        case HSVSPID(ActualNetworkLCN, dvb, nit):
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcnTableMain); 
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLinkageInfoMain);
            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcn2TableMain);
            break;
	 case HSVSPID(ActualNetworkLCN3, dvb, nit):									/*Cyfrowy*/
	     retval = srtdb_GetNoOfRecords(srtdbids_NitLcn3TableMain);
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
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitLcn2TableSub);
            break;
        case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitHDSLcnTableSub);
            break;
		case HSVSPID(SatelliteDS, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitSatelliteDS);
            break;
		case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitSrvclstTableMain);
            break;
		case HSVSPID(HeadEndFrequencyList, dvb, nit): 
            retval = srtdb_GetNoOfRecords(srtdbids_NitHeadEndFrequencyList);
            break;
		case HSVSPID(FreesatLinkageInfo, dvb, nit):
			retval = srtdb_GetNoOfRecords(srtdbids_NitFreesatLinkageInfo);
		//TraceNotice(m,"TMP_DEBUG FreesatLinkageInfo GetSize - size %d", retval);
		break;
		default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}

Bool CHsvDvbNIT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{

    
	UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualNetworkID, dvb, nit): 
        case HSVSPID(NetworkName, dvb, nit): 
        case HSVSPID(ActualNITVer, dvb, nit): 
            ASSERT(("It is a scalar propert !!!"));
            return FALSE;
            break;
        case HSVSPID(ActualNetworkLCN, dvb, nit):
            srtdb_SearchOnKey(srtdbids_NitLcnTableMain, key1, key2, key3,0, (int *)&index);
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLinkageInfoMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLcn2TableMain, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(ActualNetworkLCN3, dvb, nit):											/*cyfrowy*/
	      srtdb_SearchOnKey(srtdbids_NitLcn3TableMain, key1, key2, key3, 0,(int *)&index);
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
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitLcn2TableSub, key1, key2, key3, 0,(int *)&index);
            break;
		case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitHDSLcnTableSub, key1, key2, key3, 0,(int *)&index);
            break;
		case HSVSPID(SatelliteDS, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitSatelliteDS, key1, key2, key3, 0,(int *)&index);
            break;
		case HSVSPID(ActualServiceList, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitSrvclstTableMain,key1, key2, key3, 0,(int *)&index);     
            break;
		case HSVSPID(HeadEndFrequencyList, dvb, nit): 
            srtdb_SearchOnKey(srtdbids_NitHeadEndFrequencyList, key1, key2, key3, 0,(int *)&index);
            break;
	case HSVSPID(FreesatLinkageInfo, dvb, nit):
		srtdb_SearchOnKey(srtdbids_NitFreesatLinkageInfo, key1, key2, key3, 0,(int *)&index);
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
			Nat16 *pval = (Nat16 *)val;
            *pval = DmxROMData[demux].NetworkId;
			if(DmxROMData[demux].NITActualAvail)
			{
				retval = TRUE;
			}
		    break;
        }
    case HSVSPID(NetworkName, dvb, nit):
        {
            if( DmxROMData[demux].NetworkName[0] )
            {
                /* First byte of network name was valid => We have some valid network name */
                Nat16 *pval = (Nat16 *)val;                        
                memcpy( pval, DmxROMData[demux].NetworkName, (MAX_NETWORK_NAME_SIZE * 2) + 2 );
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
                //printf("%s::%d:NITVersion = %d\r\n",__FUNCTION__,__LINE__,DmxROMData[demux].ActualNITVer);
			}
			else
			{
                //printf("%s::%d:No NIT Actual available\r\n",__FUNCTION__,__LINE__);
			}
        }

        break;

    case HSVSPID(ActualNetworkLCN, dvb, nit):
			retval = srtdb_QueryOnKey(srtdbids_NitLcnTableMain, key1, key2, key3, 0,(Address)val);
			break;
    case HSVSPID(LinkageInfo, dvb, nit): 
			retval = srtdb_QueryOnKey(srtdbids_NitLinkageInfoMain, key1, key2, key3,0, (Address)val);
			break;
    case HSVSPID(ActualNetworkLCN2, dvb, nit): 
			retval = srtdb_QueryOnKey(srtdbids_NitLcn2TableMain, key1, key2, key3, 0,(Address)val);
			break;
    case HSVSPID(ActualNetworkLCN3, dvb, nit): 													/*cyfrowy*/
			retval = srtdb_QueryOnKey(srtdbids_NitLcn3TableMain, key1, key2, key3, 0,(Address)val);
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
    case HSVSPID(OtherNetworkLCN2, dvb, nit): 
			retval = srtdb_QueryOnKey(srtdbids_NitLcn2TableSub, key1, key2, key3,0, (Address)val);
			break;
	case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
			retval = srtdb_QueryOnKey(srtdbids_NitHDSLcnTableSub, key1, key2, key3, 0,(Address)val);
			break;
	case HSVSPID(SatelliteDS, dvb, nit): 
			retval = srtdb_QueryOnKey(srtdbids_NitSatelliteDS, key1, key2, key3, 0,(Address)val);
			DP(("strapi_GetByKey, retval:%d\n",retval));			
			break;
	case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_QueryOnKey(srtdbids_NitSrvclstTableMain,key1, key2, key3, 0,(Address)val);
			break;
	case HSVSPID(HeadEndFrequencyList, dvb, nit): 
			retval = srtdb_QueryOnKey(srtdbids_NitHeadEndFrequencyList,key1, key2, key3, 0,(Address)val);
			break;
	case HSVSPID(FreesatLinkageInfo, dvb, nit):
		retval = srtdb_QueryOnKey(srtdbids_NitFreesatLinkageInfo,key1, key2, key3, 0,(Address)val);
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
            ASSERT(("It is a scalar property !!!"));
            return FALSE;
            break;
        case HSVSPID(ActualNetworkLCN, dvb, nit):
            retval = srtdb_QueryOnIndex(srtdbids_NitLcnTableMain, index, (Address)val);
            break;
        case HSVSPID(LinkageInfo, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLinkageInfoMain, index, (Address)val);
            break;
        case HSVSPID(ActualNetworkLCN2, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLcn2TableMain, index, (Address)val);
            break;
	 case HSVSPID(ActualNetworkLCN3, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLcn3TableMain, index, (Address)val);				/*cyfrowy*/
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
        case HSVSPID(OtherNetworkLCN2, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitLcn2TableSub, index, (Address)val);
            break;
		case HSVSPID(OtherNetworkHDSLCN, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitHDSLcnTableSub, index, (Address)val);
            break;
		case HSVSPID(SatelliteDS, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitSatelliteDS, index, (Address)val);
            break;
		case HSVSPID(ActualServiceList, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitSrvclstTableMain,index, (Address)val);
            break;  
		case HSVSPID(HeadEndFrequencyList, dvb, nit): 
            retval = srtdb_QueryOnIndex(srtdbids_NitHeadEndFrequencyList,index, (Address)val);
            break;
	case HSVSPID(FreesatLinkageInfo, dvb, nit):
		retval = srtdb_QueryOnIndex(srtdbids_NitFreesatLinkageInfo,index, (Address)val);
            break;
		default:
            ASSERT(FALSE);
            break;
    }
         
    return retval;
}

Bool CHsvDvbNIT_Priv::strapi_GetRangeByKey( HsvDestination dest, int prop, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	Bool retval = FALSE;
    
	UNUSED (dest);
    switch (prop)
    {
		case HSVSPID(ActualServiceList, dvb, nit):
			if(noofkeys == 2)
			{
				/*TODO: Servicelist has to be populated from NIT*/
				retval = srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitSrvclstTableMain, key1, key2, from, to );
			}
			else
			{
				ASSERT(FALSE);
			}
			break;
		case HSVSPID(ActualNetworkLCN2,dvb,nit):
			if(noofkeys == 1)
			{
				retval = srtdb_SearchOnPrimaryKey(srtdbids_NitLcn2TableMain, key1, from, to );
			}
			else if(noofkeys == 2)
			{
				retval = srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitLcn2TableMain, key1, key2, from, to );
			}
			else
			{
				ASSERT(FALSE);
			}
			break;
		default:
            ASSERT(FALSE);
            break;
	}
	
//	PrintfNotice(" noofkeys = %d prop = %d key1 = %d key2 = %d from =%d to %d retval = %d ",noofkeys,prop,key1,key2,*from,*to,retval);
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



int CHsvDvbNIT_Priv::iutil_GetLCNValue(Nat8* ptr, int num)
{
    int val = GET16(0);
	UNUSED(num);
    return val;
}


Bool CHsvDvbNIT_Priv::Nit_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
	register Nat8 *ptr = mBuffer;

    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    static TypeNit_Parser Nit_Parser;
    Bool retval = TRUE;
    int	ntfcode = sec_SctArrived;
	int installedPackageId;
	
    int dummy, loopcount = 0, descTag, descLen = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0,loop2index = 0, tableLen = 0, loop1length = 0,loop2length = 0, templen = 0; 
	Nat32 ParsedPDSD = 0;
	
	UNUSED (cookie);
	UNUSED (crc);
	memset(&Nit_Parser,0,sizeof(Nit_Parser));
	if(secondarySectionSize > 0)
    {
        memcpy(ptr,PrimarySectionStartAddress,primarySectionSize);
        memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
    }
    else if(PrimarySectionStartAddress)
	{  
        ptr = PrimarySectionStartAddress;
	}
	else
	{
		TraceNotice(m,"ERROR: %s: %d",__FUNCTION__,__LINE__);
	}
	
	//TraceNotice(m,"TMP_DEBUG Entering function %s Code 0x%x",__FUNCTION__,code);
	
    v32 = GET32(0);
    tableLen = HSV_GETSECTION_LENGTH(ptr);
	Nit_Parser.NtkNameDescNum=0;
	Nit_Parser.HeadEndFreqDescNum=0;
	Nit_Parser.LinkageDescNum=0;
	Nit_Parser.FreesatLinkageDescNum=0;
	Nit_Parser.TsLoopDataNum=0;
	Nit_Parser.TableId = GETNBITS(v32,0,8);
	dummy = GETNBITS(v32,8,1);
	dummy = GETNBITS(v32,9,1);
	dummy = GETNBITS(v32,10,2);
	Nit_Parser.SectionLen = GETNBITS(v32,12,12);
	v32 = GET32( 3);
	Nit_Parser.NetworkId = GETNBITS(v32,0,16);
	//TraceNotice(m,"Parsing the NIT with Network id: %d",Nit_Parser.NetworkId);
	dummy = GETNBITS(v32,16,2);
	Nit_Parser.VersionNo = GETNBITS(v32,18,5);
	dummy = GETNBITS(v32,23,1);
	dummy = GETNBITS(v32,24,8);
	//TraceNotice(m,"SectionNumber %d",dummy);
	v32 = GET32( 7);
	dummy = GETNBITS(v32,0,8);
	dummy = GETNBITS(v32,8,4);
	Nit_Parser.NetworkDescLen = GETNBITS(v32,12,12);
	//TraceNotice(m,"Parsing the NIT with Network id: %d Version %d",Nit_Parser.NetworkId, Nit_Parser.VersionNo);
	ptr += 10;
	tableLen = tableLen - 10;
	v32 = GET32( 0);

	installedPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	//TraceNotice(m,"installedPackageid %d",installedPackageId);
	
	while(loopcount < Nit_Parser.NetworkDescLen)
    {
        descLoopLen = 0;
        descTag = GETNBITS(v32,0, 8); 
        descLen = GETNBITS(v32,8, 8); 
		//printf("Mounesh: got 1st loop descriptor %x in mpar\n", descTag);
        switch(descTag) {
        case 0x40:
			Nit_Parser.NetworkName_Descriptor.DescriptorTag = GETNBITS(v32,0,8);
			Nit_Parser.NetworkName_Descriptor.DescriptorLen = GETNBITS(v32,8,8);
			
			Nit_Parser.NetworkName_Descriptor.NetworkNameLen = descLen;
			descLoopLen = HSV_PARSER_MIN(80,Nit_Parser.NetworkName_Descriptor.NetworkNameLen); 
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
        case 0xA1:
		if((installedPackageId != TRICOLOR_SD_PACKAGE_ID) && (installedPackageId != TRICOLOR_HD_PACKAGE_ID))
		{
			if(Nit_Parser.HeadEndFreqDescNum<10)
			{
			    ptr += 0;
				Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
				Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].DescriptorTag = GETNBITS(v32,0,8);
				Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].DescriptorLen = GETNBITS(v32,8,8);
				Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].HeadEndFreqLen = GETNBITS(v32,16,0);
				ptr += 2;
				v32 = GET32( 0 );
				loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].HeadEndFreqDescriptor)*100 ;
				while( loop1length< HSV_PARSER_MIN(Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].DescriptorLen, templen ))
				{
					int minLength = 0;
					Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].HeadEndFreqDescriptor[loop1index].TSID= GETNBITS(v32,0, 16); 
					Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].HeadEndFreqDescriptor[loop1index].SiteHeadEndFrequency= GETNBITS(v32,16, 16); 
					loop1length += 4;
					loop1index++;
					ptr += 4;
					v32 = GET32( 0);
				}
				Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].HeadEndFreqLen = loop1index;
				Nit_Parser.HeadEndFreq_Descriptor[Nit_Parser.HeadEndFreqDescNum].DescriptorValid = TRUE;
				Nit_Parser.HeadEndFreqDescNum++;
			}
			else
			{
			   	ptr += 2 + descLen;
			}
			loopcount += 2 + descLen;
			tableLen = tableLen - (2 + descLen);

			v32 = GET32( 0);
			break;
		}
		else
		{
		
			ptr += 2 + descLen;
			loopcount += 2 + descLen;
			tableLen = tableLen - (2 + descLen);
			v32 = GET32( 0);
			break;
		}
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

		case FREESAT_LINKAGE_DESCRIPTOR:	/*Free satellite linkage descriptor*/

			if(Nit_Parser.FreesatLinkageDescNum < 10)
			{
				descLoopLen = 0;
				loop1length = 0;
				loop2length = 0;
				loop1index = 0;
				Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].DescriptorTag = descTag;
				Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].DescriptorLen = descLen;
				Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].PrivateDataSpecifier = ParsedPDSD;
				Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDescNum = 0;
				ptr += 2;

				while((loop1index < FREESAT_MAX_LINKAGE_SERVICE_COUNT) && (descLoopLen < descLen))
				{
					v32 = GET32(descLoopLen);
					Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].TSID = GETNBITS(v32,0,16);
					Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].ONID = GETNBITS(v32,16,16);
					descLoopLen += 4;
					v32 = GET32(descLoopLen);
					loop1length =  GETNBITS(v32,0,8);
					/*Standard type loop is skiped as per
					**Free Satellite Requirements for Interoperability Part 3: System Management V1.6
					*/
					descLoopLen += 1 + loop1length;
					v32 = GET32(descLoopLen);
					Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].ServiceId = GETNBITS(v32,0,16);
					//TraceNotice(m,"FreesatLD: Service-ID %d",Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].ServiceId);
					loop2length =  GETNBITS(v32,16,8);
					loop2index = 0;
					templen = 0;
					Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].TunnelledTypeLoopLen = 0;
					descLoopLen += 3;
					while((loop2index < FREESAT_MAX_LINKAGE_TYPE_COUNT) && (templen < loop2length))
					{
						v32 = GET32(descLoopLen);
						Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].TunnelledLinkageType[loop2index] = GETNBITS(v32,0,8);
						//TraceNotice(m,"FreesatLD: TunnlledType 0x%x",Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].TunnelledLinkageType[loop2index]);
						descLoopLen++;
						loop2index ++;
						templen ++;
					}
					Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDesc[loop1index].TunnelledTypeLoopLen = loop2index;
					//descLoopLen += loop2length;
					loop1index ++;
				}
				Nit_Parser.FreesatLinkage_Descriptor[Nit_Parser.FreesatLinkageDescNum].FreesatLinkageDescNum = loop1index;
				ptr += descLen;
				Nit_Parser.FreesatLinkageDescNum++;
			}
			else
			{
				ptr += 2 + descLen;
			}
			v32 = GET32(0);
			loopcount += 2 + descLen;
			tableLen = tableLen - (2 + descLen);

			break;
		case 0x5F:
			ParsedPDSD = GET32( 2);
			ptr += 2 + descLen;
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
        }//endswitch
    }//endwhile
    dummy = GETNBITS(v32,0,4);
    Nit_Parser.TsLoopLen = GETNBITS(v32,4,12);
    ptr += 2;
    tableLen = tableLen - 2;
    v32 = GET32( 0);
	
    ipop_PopulateNIT(demux, (Address)&Nit_Parser,ntfcode  /*code*/);
    while( ((tableLen - 4) >  0) && (tsloopIndex < 1))
    {
        Nat32 ParsedPDSD = 0;
		Nit_Parser.TsLoopData[tsloopIndex].NtkNameDescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].LinkageDescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].HDSLCNDescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].LCNDescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum=0;
		Nit_Parser.TsLoopData[tsloopIndex].ServiceListDescNum=0;
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
            
			//printf("Mounesh: got 2nd loop descriptor %x in mpar\n", descTag);
            switch(descTag) {
            case 0x40:
				Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorTag = GETNBITS(v32, 0,8);
				Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorLen = GETNBITS(v32, 8,8);
				Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLen;
				descLoopLen = HSV_PARSER_MIN(80,Nit_Parser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen); 
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
				
            case 0x87:			
				if(Nit_Parser.TsLoopData[tsloopIndex].LCN2DescNum<100)
				{
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
            case 0x81:
            if(Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum<100)
            {
                     Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].LCN3Desc) ;
                 while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].DescriptorLen, templen))
                 {
                 int minLength = 0;
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].LCN3Desc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].LCN3Desc[loop1index].ChannelId = GETNBITS(v32,16, 16); 
                 v32 = GET32( 4);
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].LCN3Desc[loop1index].CpServiceId = GETNBITS(v32,0, 16); 
                loop1length += 6;
                loop1index++;
                ptr += 6;
                 v32 = GET32( 0);
                 }
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].LCN3Len = loop1index;
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum].DescriptorValid = TRUE;
                 Nit_Parser.TsLoopData[tsloopIndex].LCN3DescNum++;
            }
            else
            {
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);
            
            v32 = GET32( 0);
            break;
			case 0x43:
            if(Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum<10)
            {
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD);
                 while( loop1length< HSV_PARSER_MIN(Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorLen, templen))
                 {

                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Frequency = GETNBITS(v32,0, 32); 
                 v32 = GET32( 4);
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].OrbitalPostion = GETNBITS(v32,0, 16); 
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].WestEastFlag = GETNBITS(v32,16, 1); 
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Polarization = GETNBITS(v32,17, 2); 
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].RollOff = GETNBITS(v32,19, 2); 
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Modulationsystem = GETNBITS(v32,21, 1); 
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Modulationtype = GETNBITS(v32,22, 2); 
                 v32 = GET32( 7);
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].SymbolRate = GETNBITS(v32,0, 28); 
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].FEC_Inner = GETNBITS(v32,28, 4); 
                loop1length += 11;
                loop1index++;
                ptr += 11;
                 v32 = GET32( 0);
                 }
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSDLen = loop1index;
                 Nit_Parser.TsLoopData[tsloopIndex].SDSD_Descriptor[Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorValid = TRUE;
                 Nit_Parser.TsLoopData[tsloopIndex].SDSDDescNum++;
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

            
            default:
				loopcount += 2 + descLen;
				//Nat8 *x = ptr;
				ptr += 2 + descLen;
				//printf("Mounesh : default : desclen=%d, diff in ptr = %d\n", descLen, (ptr-x));
				tableLen = tableLen - (2 + descLen);
				v32 = GET32( 0);
				break;
            }//endswitch
        }//endwhile descloop
	tsloopIndex++;
	loopcount = 0;
	Nit_Parser.TsLoopDataNum = tsloopIndex;	

	retval = retval && ipop_PopulateNIT(demux, (Address)&Nit_Parser,ntfcode  /*code */);

	tsloopIndex = 0;
    }//endwhile tsloop
    //Nit_Parser.TsLoopDataNum = tsloopIndex;
    dummy = GETNBITS(v32, 0,32);
    if (code & sec_TableCompleted) {
	ntfcode = sec_TableCompleted;
	 retval = retval && ipop_PopulateNIT(demux, (Address)&Nit_Parser,ntfcode  /*code */);
    }
    //printf("CRC = 0x%x\r\n",dummy);	
	return TRUE;
    //pop_PopulateNIT( &Nit_Parser );
}//end function
