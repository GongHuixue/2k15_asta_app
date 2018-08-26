
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
 *       %version: FUSION_TVG_14.1.2 %
 * %date_modified: Thu Feb 19 17:19:20 2009 %
 *    %derived_by: anuma %
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

Nat8 CHsvDvbSDT_Priv::s__mBuffer[16*1024];


/***************Local Functions******************************************/



















#if 0





#endif







//static Bool mCacheSDT ();
/**************************Initialisations*****************************************/

void CHsvDvbSDT_Priv::pow_Init(void)
{
    int  dmx;
    int      i;
    
    for( dmx = (int)HsvDmxMain; dmx < (int)HsvDmxLast; dmx++ )
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



Bool CHsvDvbSDT_Priv::mIsSDTClearNeeded ()
{
	int insMode, insState;
    int  mInstalledPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
    Bool clearSdt = TRUE;
     
    ins_GetCurrentInstallationState(&insMode, &insState);
	    
    if (insMode == ins_InstallationBackground && GET_FRANSAT_PACKAGE(mInstalledPackageId) == 31)
    {
      	clearSdt = FALSE;
    }
	if (insMode == ins_InstallationBackground && mInstalledPackageId == FREESAT_PACKAGE_ID)
	{
		clearSdt = FALSE;
	}
    return clearSdt;
}
void CHsvDvbSDT_Priv::ena_Enable(HsvDemux dmx)
{
	HsvSDMSIDataValues SiValues;      
	int mode = IHsvSdmControl2_Idle;
	int insMode, insState;
	ins_GetCurrentInstallationState(&insMode, &insState);

	if (mIsSDTClearNeeded())
	{
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
		DmxData[dmx].OtherSectionValid  =   FALSE;
	}
	TraceNotice(m,"TMP_DEBUG call get mode");
	mode =  ctrl->GetMode(dmx);
	SiValues.TableId = ((IHsvSdmControl2_FreesatNormal == mode) ? SDT_ACTUAL_TABLE_ID : INVALID_TABLEID);
	pakgins_GetSIDetails(&SiValues);
	TraceNotice(m, "TMP_DEBUG Enable SDT mode 0x%x insmode 0x%x",mode,insMode);
	DmxData[dmx].TablesReq = DmxData[dmx].TablesRecvd = 0;
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
		TraceNotice(m, "TMP_DEBUG SDT actual collection started mode 0x%x",mode);
	}
	SiValues.TableId = ((IHsvSdmControl2_FreesatNormal == mode) ? SDT_OTHER_TABLE_ID : INVALID_TABLEID);
	pakgins_GetSIDetails(&SiValues);
	TraceNotice(m, "SDTOTHER enable status: %d", (conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX])));
	if((conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX])) && (SiValues.TableId == SDT_OTHER_TABLE_ID))  
	{
		if(((IHsvSdmControl2_FreesatNormal == mode) && (mode != IHsvSdmControl2_FreesatMinimalSdtOth)) && (SiValues.Pid <= 0x1FFF) )
		{
			/*DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx),
																				(int)SiValues.Pid,
																				SDT_OTHER_TABLE_ID,
																				SDT_OTHER_TABLE_ID, FNADDR(Sdt_Parser_Parser));*/
			HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID,SiValues.Pid};
			DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));																
			DmxData[dmx].TablesReq = 0;
			TraceNotice(m, "TMP_DEBUG SDT other collection started mode 0x%x PID 0x%x",mode, SiValues.Pid);
		}
		else
		{
			HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID, SDT_PID_VALUE};
			#ifndef __cplusplus
			DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, (HsvSectionFilterCallback)Sdt_Parser_Parser);
			#else
			DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));
			#endif
			//DmxData[dmx].TablesReq |= SDT_OTHER_REQ;
			DmxData[dmx].TablesReq = 0;
			TraceNotice(m, "SDT OTHER ena_Enable");
			ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
		}
	} 

	DmxData[dmx].TsId               =   HSV_INVALID_TSID;         
	DmxData[dmx].OriginalNetworkId  =   HSV_INVALID_NETWORKID;         
	DmxData[dmx].ActualOnId         =   0;
	DmxData[dmx].ActualSvcId        =   0;
        
}


/*This func was provided to enable sdt in backgroundmode only after collection of freesat tunnelled sdt pid from pmt*/
void CHsvDvbSDT_Priv::Freesatena_Enable(HsvDemux dmx)
{
	TraceNotice(m,"Entering Function %s",__FUNCTION__);
	int mode = IHsvSdmControl2_Idle;
	int insMode, insState ,mInstalledPackageId;
	TraceNotice(m,"TMP_DEBUG call get mode");
	mode =  ctrl->GetMode(dmx);
	ins_GetCurrentInstallationState(&insMode, &insState);
	mInstalledPackageId = ins_GetAttribute(ins_InstallationBackground, ins_AttributePackageId);
	int tunnelled_sdt_pid = FREESAT_TUNNELLED_PID_INVALID;
	HSVSPTYPE(FreesatTunnelledInfo, mpeg, simplepmt) FreesatTunneldData;

	TraceNotice(m, "TMP_DEBUG Enable SDT mode 0x%x insmode 0x%x",mode,insMode);

	if (mIsSDTClearNeeded())
	{
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
		DmxData[dmx].OtherSectionValid  =   FALSE;
	}

	if(mInstalledPackageId == FREESAT_PACKAGE_ID)
	{
		if(ipmtstrapi->GetByKey(HsvMain,HSVSPID(FreesatTunnelledInfo, mpeg,simplepmt),0,0,0,&FreesatTunneldData))
		{
			tunnelled_sdt_pid = ((FreesatTunneldData.TunnelledDataTypeBitMap & (1 << 0x03)) ? FreesatTunneldData.PID[0x03] : FREESAT_TUNNELLED_PID_INVALID);
			TraceNotice(m,"tunnelled_sdt_pid %d DmxData[dmx].enabled = %d",tunnelled_sdt_pid,DmxData[dmx].enabled);
			if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]) && (!DmxData[dmx].enabled))  
			{
				if((IHsvSdmControl2_FreesatMinimalSdtOth == mode) && (tunnelled_sdt_pid <= FREESAT_TUNNELLED_PID_INVALID) )
				{
					HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SDT_OTHER_TABLE_ID,tunnelled_sdt_pid};
					DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Sdt_Parser_Parser));																
					DmxData[dmx].TablesReq = 0;
					TraceNotice(m, "TMP_DEBUG SDT other collection started mode 0x%x PID 0x%x",mode, tunnelled_sdt_pid);
					
					DmxData[dmx].enabled = true;
					TraceNotice(m, "TMP_DEBUG SDT other collection started mode 0x%x PID 0x%x",mode,tunnelled_sdt_pid);
				}else{TraceNotice(m,"Sdt other section Not requested line %d",__LINE__);}
			}
			else
			{ TraceNotice(m,"Sdt other section Not requested %d",__LINE__);}
		}
		else
		{
			TraceNotice(m,"Strapi for freesat tunnelled info failed !!!");
		}
	}

	DmxData[dmx].TsId               =   HSV_INVALID_TSID;         
	DmxData[dmx].OriginalNetworkId  =   HSV_INVALID_NETWORKID;         
	DmxData[dmx].ActualOnId         =   0;
	DmxData[dmx].ActualSvcId        =   0;
}

void CHsvDvbSDT_Priv::Freesatena_Disable(HsvDemux dmx)
{
}
void CHsvDvbSDT_Priv::Freesatena_Sync(HsvDemux dmx)
{
}

void CHsvDvbSDT_Priv::ena_Disable(HsvDemux dmx)
{
         
    
	if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_ACTUAL_INDEX]))  
	{
		if( DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX] != HSV_INVALID_SCT_REQUEST )
		{
			sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]);                
			DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]           =    HSV_INVALID_SCT_REQUEST;
		}
		else
		{
			/* We had not started subscription before*/
			DP(("We had not started subscription before\n\n"));
		}
	}
	if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))  
	{
		if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST )
		{
			sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId[SDT_OTHER_INDEX]);                
			DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;
			DmxData[dmx].enabled = false;
		}
		else
		{
			/* We had not started subscription before*/
			DP(("We had not started subscription before\n\n"));
		}
	}
	else
	{
		DP(("else part of conf_IsActionAllowed, dmx:%d\n",dmx));
	}

    DmxData[dmx].ActualOnId         =   0;
    DmxData[dmx].ActualSvcId        =   0;
    if (mIsSDTClearNeeded())
	{
		DmxData[dmx].OtherSectionValid             =    FALSE; 
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
	}
	DmxData[dmx].TablesReq = DmxData[dmx].TablesRecvd = 0;
    
}

void CHsvDvbSDT_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED (dmx);
    /* TODO */
}

HSVCOMPAREKEY(sdtmainconf,Primary,  HsvSDTSection,Original_NetworkId)

HSVCOMPAREKEY(sdtmainconf,Secondary,HsvSDTSection,ServiceId)

HSVCOMPAREKEY(sdtmainconf, Teritiary, HsvSDTSection,Tsid)
/* Not used */

#ifndef __cplusplus

HSVCOMPAREKEY(sdtmainconf,QuaternaryKey,HsvSDTSection,ServiceId)

HSVCOMPAREKEY(linkmainconf, QuaternaryKey, HsvLinkageInfo,Tsid)

HSVCOMPAREKEY(sdtsubconf,QuaternaryKey,HsvSDTSection,ServiceId)

#endif


HSVCOMPAREKEY(linkmainconf, Primary, HsvLinkageInfo,ActualOnId)

HSVCOMPAREKEY(linkmainconf, Secondary, HsvLinkageInfo,ActualSvcId)

HSVCOMPAREKEY(linkmainconf, Teritiary, HsvLinkageInfo,LinkageType)
/* Not used */



HSVCOMPAREKEY(sdtsubconf,Primary,  HsvSDTSection,Original_NetworkId)

HSVCOMPAREKEY(sdtsubconf,Secondary,HsvSDTSection,ServiceId)

HSVCOMPAREKEY(sdtsubconf, Teritiary, HsvSDTSection,Tsid)
/* Not used */



/*Nat8 sdtmainconf_CompareTeritiaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    ASSERT (! "SDT Table does not have a teritiary key" );
    return sdtmainconf_Equal;
}

Nat8 sdtsubconf_CompareTeritiaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    ASSERT (! "SDT Other Table does not have a teritiary key" );
    return sdtmainconf_Equal;
}*/


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

Bool CHsvDvbSDT_Priv::ipop_PopulateSDT ( HsvDemux dmx , Address pSdt_Parser, int code, Nat32 cookie )
{
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
       
    }
    else if(SDT_OTHER_TABLE_ID == ServiceTable->TableId)
    {
		/* no strapi ntfs.. sent here used for installation which is based on SDT other, currently used for Ziggo */
        mQuickPopulateOtherSDTSectionServices(dmx, ServiceTable, code);
        PopulateTSVersionNumber(dmx, ServiceTable, code);
        PopulateLinkageInfo(dmx, ServiceTable, code);
	}
    if( sec_TableCompleted & code )
    {
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
				DmxData[dmx].TablesReq = 0;
                DmxData[dmx].TablesRecvd = 0;
				/* generate control notifications */
				if( ctrlN_iPresent())
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
Bool CHsvDvbSDT_Priv::PopulateTSID(HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if( sec_SctArrived & code )
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
    if( sec_SctArrived & code )
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
    if( sec_SctArrived & code )
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
    if(sec_SctArrived & code)
    {
        return  PopulateServiceDescriptionSection (dmx, ServiceTable, HSVSPID(ActualTSService, dvb, sdt), srtdbids_SdtTableActual, code);
    }
    
    else if( sec_TableCompleted & code )
    {
        return PopulateServiceDescriptionSection (dmx, ServiceTable, HSVSPID(ActualTSService, dvb, sdt), srtdbids_SdtTableActual, code);
    }
    return TRUE;
}

Bool CHsvDvbSDT_Priv::PopulateOtherSDTSection( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    if(sec_SctArrived & code)
    {
        return  PopulateOtherServiceDescriptionSection (dmx, ServiceTable, HSVSPID(OtherTSService, dvb, sdt),0, 0);
    }
    
    else if( sec_TableCompleted & code )
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
    int		   tsloop 	   = 0;		
    int                 index               = 0;
    Bool                retval              = TRUE;
    int                 svcid               = 0;
    int                 onwid               = 0;    
    Bool                changed             = FALSE;

	
    while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
        {
            // DP(("PopulateSDTSection:: PopulateSDTFunctionid:%d\n\n",funcID));
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
                        DbaseVersion.Free_Ci_Mode			    = FALSE;
                        DbaseVersion.Match_Brand_Flag			= FALSE;
                        DbaseVersion.NumBrandIds			    = 0;

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
						SDTSection.Tsid			   			  = ServiceTable->transport_stream_id;
                        SDTSection.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                        SDTSection.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                        SDTSection.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                        SDTSection.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                        SDTSection.VersionNumber              = ServiceTable->version_number ;
                        SDTSection.Free_Ci_Mode	    		  = FALSE;
						SDTSection.Match_Brand_Flag			  = FALSE;
						SDTSection.NumBrandIds			      = 0;

                        AssignServiceDescriptor(ServiceTable,tsloop, i, &SDTSection);
                        AssignCipDesc(ServiceTable,tsloop, i, &SDTSection);
                        //DP(("PopulateSDTSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid));
                        if( srtdb_Insert( tableid, ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id,0, (Address)(&SDTSection)) )
                        {                    
                            srtdb_SearchOnKey(tableid, ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, ServiceTable->transport_stream_id,0, (int *)&index);
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
        else if(sec_TableCompleted & code)
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
                        DP(("PopulateSDTSection::LINE:%d DbaseVersion.VersionNumber:%d\n\n",__LINE__,DbaseVersion.VersionNumber));	
                        /* delete the record */
                        if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, ServiceTable->transport_stream_id,0))
                        {  
                            DP(("Version Number Mismatch Hence Delete is Done\n\n"));
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
                    DP(("PopulateSDTSection::LINE:%d\n\n",__LINE__));
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
    int 		tsloop	= 0;
   // UNUSED( secindex );
	UNUSED (tableid);
    DP(("%s \n", __FUNCTION__));
while ( tsloop < ServiceTable->TsLoopDataNum)
{

    if( sec_SctArrived & code )
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

            
                    AssignServiceDescriptor(ServiceTable, tsloop,i, &DmxData[dmx].SDTOtherSection);            
                    strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id, 0, 0); /* TODO: Define events */
                }
            }
        }
    }
    else if(sec_TableCompleted & code)
    /* Delete services if not present */
    {
        if(ServiceTable->version_number != DmxData[dmx].SDTOtherSection.VersionNumber)
        {
            DmxData[dmx].OtherSectionValid     =   FALSE;
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
	Bool ShortNameReqd = FALSE;
	Bool IsDigiturkPkg = FALSE;

    if(TRUE == ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
    {  
        Nat8 *SvcName = (Nat8 *)ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceName;

        DbaseVersion->ServiceName[0] = '\0';
		
        len =   ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceNameLen;

		IsDigiturkPkg = eurdiv_IsDigiturkPackage();
		ShortNameReqd = ((IsDigiturkPkg == TRUE) && (len > MAX_DIGITURK_SERVICE_LEN)) ? TRUE: ((len >= div_ChannelNameLength) ? TRUE : FALSE);

        DbaseVersion->ServiceType   = ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceType;
		memset(DbaseVersion->ServiceName,0x00,MAXSERVICENAMELEN * 2);
        charsetutil_MbToWc( SvcName, 
                            len, 
                            DbaseVersion->ServiceName,
                            MAXSERVICENAMELEN,
                            ShortNameReqd
                            );
        len =   (IsDigiturkPkg == TRUE) ? MAX_DIGITURK_SERVICE_LEN : MAXSERVICENAMELEN;
		
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
		}
	}	
}
Bool CHsvDvbSDT_Priv::PopulateLinkageInfo ( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code)
{
    return PopulateLinkageInfoPrivate (dmx, ServiceTable, HSVSPID(LinkageInfo, dvb, sdt), srtdbids_LinkageInfoMain, code);
}

void CHsvDvbSDT_Priv::mQuickPopulateOtherSDTSectionServices(HsvDemux dmx, TypeSdt_Parser* ServiceTable,  int code)
{
    HsvSDTSection       TmpDbaseVersion, DbaseVersion;
    int i= 0, tsloop = 0, len = 0;
    int tableid = srtdbids_SdtTableOther;
    
	TraceNotice(m,"TMP_DEBUG %s %d Table ID %d",__FUNCTION__,__LINE__,tableid);
	while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
        {
            int ServiceDescriptionNum = ServiceTable->TsLoopData[tsloop].ServiceDescNum;
            
            for( i = 0; i < ServiceDescriptionNum; i++)
            {
                if(ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
                {
					DmxData[dmx].OtherSectionValid          = TRUE;

                    DbaseVersion.Original_NetworkId         = ServiceTable->original_network_id;
 		    // Added for Poland N 
		    DbaseVersion.Tsid			    = ServiceTable->transport_stream_id;
                    DbaseVersion.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
                    DbaseVersion.ServiceType                = ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceType;
                    DbaseVersion.EIT_Schedule_Flag          = ServiceTable->TsLoopData[tsloop].Eit_Schedule_Flag;
                    DbaseVersion.EIT_Present_Following_Flag = ServiceTable->TsLoopData[tsloop].Eit_Present_Following_Flag;
                    DbaseVersion.Running_Status             = ServiceTable->TsLoopData[tsloop].running_status;
                    DbaseVersion.Free_CA_Mode               = ServiceTable->TsLoopData[tsloop].free_CA_mode;
                    DbaseVersion.VersionNumber              = ServiceTable->version_number;
                    DbaseVersion.Free_Ci_Mode			    = FALSE;
					DbaseVersion.Match_Brand_Flag			= FALSE;
					DbaseVersion.NumBrandIds			    = 0;
					
				
					memset(DbaseVersion.ServiceName,0x00,MAXSERVICENAMELEN * 2);	
					/* ServiceName */
                    len =   ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceNameLen;
					TraceNotice(m,"Service Name Lenght %d ",len);
					charsetutil_MbToWc( (Nat8 *)ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceName, 
										len, DbaseVersion.ServiceName, MAXSERVICENAMELEN, (len >= div_ChannelNameLength) ? TRUE : FALSE );
					len =   MAXSERVICENAMELEN;
					DbaseVersion.ServiceName[len] = '\0';
					
                    if( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, DbaseVersion.Tsid, 0,(Address)(&TmpDbaseVersion) ) )
                    {
                    	TraceNotice(m,"srtdb_QueryOnKey");
                        if(srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, DbaseVersion.Tsid, 0,(Address)(&DbaseVersion)))
						{
							strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherTSService, dvb, sdt), DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, DbaseVersion.Tsid, 0); 
						}
                    }
                    else
                    {   
                    	TraceNotice(m,"Service Inserted %d and Service Name %s\n",DbaseVersion.ServiceId,DbaseVersion.ServiceName);
						if(!srtdb_Insert( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, DbaseVersion.Tsid, 0,(Address)(&DbaseVersion)) )
                        {                    
                            DP(("PopulateSDTOther vector:: srtdb_Insert failed: ServiceTable->original_network_id:%d, ServiceTable->TsLoopDataNum[tsloop].service_id:%d\n\n",DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId));
                        }
						else
						{
                           strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(OtherTSService, dvb, sdt), DbaseVersion.Original_NetworkId, DbaseVersion.ServiceId, DbaseVersion.Tsid );
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
    //int     tableid = DmxROMData[dmx].PropertyInfo[pptyindex].dbtable;    
    int i= 0;
    int tsloop = 0;
    
	//UNUSED( secindex );
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
				//int j = 0;
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
				//int j = 0;
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
							printf("HDSimulCast: Update [%04x|%04x|%04x]   -->   [%04x|%04x|%04x] \n",
							ServiceTable->original_network_id,
							ServiceTable->transport_stream_id,
							ServiceTable->TsLoopData[tsloop].service_id,
							DmxData[dmx].LinkageInfo.Original_NetworkId,
							DmxData[dmx].LinkageInfo.Tsid,
							DmxData[dmx].LinkageInfo.ServiceId);
							break;	
						}                
					}
					else
					{
						if( srtdb_Insert( tableid,ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType, 0, (Address)(&DmxData[dmx].LinkageInfo) ) )    /*pr49805 */
						{                    						
							strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(LinkageInfo, dvb, sdt), ServiceTable->original_network_id, DmxData[dmx].LinkageInfo.ActualSvcId, DmxData[dmx].LinkageInfo.LinkageType );    /*pr49805 */         
							printf("HDSimulCast: Insert [%04x|%04x|%04x]   -->   [%04x|%04x|%04x] \n",
							ServiceTable->original_network_id,
							ServiceTable->transport_stream_id,
							ServiceTable->TsLoopData[tsloop].service_id,
							DmxData[dmx].LinkageInfo.Original_NetworkId,
							DmxData[dmx].LinkageInfo.Tsid,
							DmxData[dmx].LinkageInfo.ServiceId);
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
            ASSERT(("It is a scalar property !!!"));
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
            ASSERT(("It is a scalar propert !!!"));
            break;
        case HSVSPID(OtherSDTSection, dvb, sdt):
            retval = srtdb_GetNoOfRecords(srtdbids_SdtTableOther); 
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
            ASSERT(("It is a scalar propert !!!"));
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
            ASSERT(("It is a scalar propert !!!"));
            break;
        case HSVSPID(OtherSDTSection, dvb, sdt):
            retval = srtdb_SearchOnKey(srtdbids_SdtTableOther, key1, key2, key3, 0,(int *)&index);
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
						 
					  //if(HSV_INVALID_NETWORKID != DmxData[demux].OriginalNetworkId)
                {
                    Nat16 *pval = (Nat16 *)val;
                    *pval = DmxData[demux].OriginalNetworkId;
                    retval = TRUE;
                }
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

                {                    
                    Nat16 *pval = (Nat16 *)val;
                    *pval = DmxData[demux].TsId;
                    retval = TRUE;
                }
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
            ASSERT(("It is a scalar propert !!!"));
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

    	default:
            ASSERT(FALSE);
            break;
    }		
    return retval;

}

Bool CHsvDvbSDT_Priv::strapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	return FALSE;
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


                if( !(DmxData[dmx].OtherSectionValid) )
                {
                    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))  
                    {
                        if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST )
                        {
                            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),  DmxData[dmx].SubscrId[SDT_OTHER_INDEX] );
                            DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;
                        }
#ifndef __cplusplus
                        DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SDT_PID_VALUE,SDT_OTHER_TABLE_ID, SDT_OTHER_INDEX, (HsvSectionCallback)Sdt_Parser_Parser);
#else
						DmxData[dmx].SubscrId[SDT_OTHER_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SDT_PID_VALUE,SDT_OTHER_TABLE_ID, SDT_OTHER_INDEX, FNADDR(Sdt_Parser_Parser));
#endif
                        ASSERT(DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST);
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
	HsvDemux dmx = HsvDmxMain;

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

			sec_ResetRequest( HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId[SDT_ACTUAL_INDEX]);
		}
		else
		{
			PrintfNotice("SDTReset Failure. not in proper state\r\n");
		}
	}
	else
	{
		if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[SDT_OTHER_INDEX]))  
        {
            if( DmxData[dmx].SubscrId[SDT_OTHER_INDEX] != HSV_INVALID_SCT_REQUEST )
            {
                sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId[SDT_OTHER_INDEX]);                
                DmxData[dmx].SubscrId[SDT_OTHER_INDEX] = HSV_INVALID_SCT_REQUEST;
				InitOtherSDTSection(dmx);
				InitOtherTSID(dmx);
				InitOtherONID(dmx);
				InitOtherTSVersionNumber(dmx);
				InitOtherSDTSectionServices(dmx);
            }
        }
		else
		{ 
			PrintfNotice("%s %d SDT Other request not possible\n", __FUNCTION__, __LINE__);
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
#ifndef __cplusplus
#include "../type/hsvcountry.h"
#else
#include "hsvcountry.h"
#endif
                                default:
                                		break;
    }
    return retval;

}



Bool CHsvDvbSDT_Priv::Sdt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{

   //printf("from Sdt_Parser_Parser = %d\n",funcID);
   	TraceNotice(m,"Entering Sdt_pareser");
   
    register Nat8*ptr = mBuffer;
    register int v32=0;
	int			DescriptorPtrMovement = 0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);	
    static TypeSdt_Parser Sdt_Parser;
	Bool retval = TRUE;
	int	ntfcode = sec_SctArrived;
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
    TraceNotice(m,"TMP_DEBUG %s %d SDT Section received, TableID 0x%x tsid %d", __FUNCTION__,__LINE__,Sdt_Parser.TableId,Sdt_Parser.transport_stream_id);
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
    {
   Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum=0;
   Sdt_Parser.TsLoopData[tsloopIndex].LinkageDescNum=0;
   Sdt_Parser.TsLoopData[tsloopIndex].CIPlusDescNum=0;
   Sdt_Parser.TsLoopData[tsloopIndex].ExtTargetRegionDescNum=0;
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
				DescriptorPtrMovement = 0;
				Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorTag = GETNBITS(v32, 0,8);
				Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorLen = GETNBITS(v32, 8,8);
				Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceType = GETNBITS(v32, 16,8);
				Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = GETNBITS(v32, 24,8);
				if ((Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen + 2) <= descLen)//+2 because desclen + 2 is full
				{
					/* Parsing provider name length */
					descLoopLen = HSV_PARSER_MIN(80,Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen); 
					ptr += 4;
					memcpy(Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderName,ptr,descLoopLen);
					ptr += Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen;
					v32 = GET32( 0);
					DescriptorPtrMovement = 4 + Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen;//ANEESH: Offset saved

					Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = descLoopLen;
					/* Parsing the service name length */

					Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = GETNBITS(v32, 0,8);
					if ((DescriptorPtrMovement + Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen) < (descLen + 2))
					{
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
						PrintfNotice ("S2App:Invalid service name length: %d %d %d ",DescriptorPtrMovement,  Sdt_Parser.TsLoopData[tsloopIndex].Service_Descriptor[Sdt_Parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen, \
										descLen);
						ptr += (2 + descLen - DescriptorPtrMovement);
					}
				}
				else
				{
					ptr += 2 + descLen;
				}
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
            default:
            loopcount += 2 + descLen;
            ptr += 2 + descLen;
            tableLen = tableLen - (2 + descLen);
            v32 = GET32( 0);
            break;
            }
        }
    tsloopIndex++;
    loopcount = 0;
    Sdt_Parser.TsLoopDataNum = tsloopIndex;
		
	 retval = retval && ipop_PopulateSDT(demux, (Address)&Sdt_Parser,ntfcode /*code*/, cookie);
	tsloopIndex = 0;
	
    }
    if (code & sec_TableCompleted)
    {
	    ntfcode = sec_TableCompleted;
	    retval = retval && ipop_PopulateSDT(demux, (Address)&Sdt_Parser,ntfcode /*code*/, cookie);
    }


    dummy = GETNBITS(v32,0,32);
    return retval;		
    
}//end function

