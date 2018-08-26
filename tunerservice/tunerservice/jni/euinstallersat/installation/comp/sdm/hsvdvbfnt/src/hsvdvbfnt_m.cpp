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
 *          %name: hsvdvbfnt_m.c %
 *       %version: TVG_4 %
 * %date_modified: Fri Feb 20 20:07:55 2009 %
 *    %derived_by: shreeshav %
 */
 
#include "_hsvdvbfnt_m.h"


TRACESYMBOL(m, "s2/sdm/hsvdvbfnt")


#ifndef __cplusplus

#else

#endif








struct DmxRomDataStruct CHsvDvbFNT_Priv::s__DmxROMData[HsvDmxLast];


Nat8 CHsvDvbFNT_Priv::s__mBuffer[16*1024];
























void CHsvDvbFNT_Priv::pow_Init(void)
{
	int  dmx;
    int      i;
    
    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {        
        for(i = 0; i < MAX_SECTIONS; i++)
        {
            /* Clear our structures to ensure that we dont have junk values in them*/
            DmxROMData[dmx].SubscrId[i]  = HSV_INVALID_SCT_REQUEST;
        }
		DmxROMData[dmx].SectionInfo[FNT_INDEX] = conf_FntParsing;
		
		DmxROMData[dmx].FNTAvail = FALSE;
		DmxROMData[dmx].TablesReq = 0;
        DmxROMData[dmx].FNTVer = 0xFF;
    }  
	
}


void CHsvDvbFNT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbFNT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbFNT_Priv::ena_Enable(HsvDemux dmx)
{
	HsvSDMSIDataValues SiValues;
    DmxROMData[dmx].FNTAvail	  = FALSE;
    DmxROMData[dmx].FNTVer = 0xFF;
	
	InitSatelliteDS( dmx);
	InitNetworkName( dmx);
	InitActualNetworkID( dmx);
	InitFNTVer( dmx);
	InitLCN( dmx);
	InitServiceListDS( dmx);
	
	SiValues.Pid = INVALID_PID;
	pakgins_GetSIDetails(&SiValues);
	
	
	if((conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[FNT_INDEX]))&&((SiValues.Pid != INVALID_PID)))
	{

		#ifndef __cplusplus
		DmxROMData[dmx].SubscrId[FNT_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SiValues.Pid, FNT_TABLE_ID,FNT_TABLE_ID, (HsvSectionCallback)Fnt_Parser_Parser);
		#else
		DmxROMData[dmx].SubscrId[FNT_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SiValues.Pid, FNT_TABLE_ID,FNT_TABLE_ID, FNADDR(Fnt_Parser_Parser));
		#endif
		DmxROMData[dmx].TablesReq |= FNT_REQ;
		TraceNotice (m, "FNT: Requested %d pid = %d ",(int)DmxROMData[dmx].SubscrId[FNT_INDEX],SiValues.Pid);
	}

}

void CHsvDvbFNT_Priv::ena_Disable(HsvDemux dmx)
{
	TraceNotice (m, "FNT: disabled ");
	if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[FNT_INDEX]))  
	{
		if( DmxROMData[dmx].SubscrId[FNT_INDEX] != HSV_INVALID_SCT_REQUEST )
		{
			TraceNotice (m, "FNT: Cancelled %d ",(int)DmxROMData[dmx].SubscrId[FNT_INDEX]);
			sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxROMData[dmx].SubscrId[FNT_INDEX]);
			DmxROMData[dmx].SubscrId[FNT_INDEX] = HSV_INVALID_SCT_REQUEST ;
		}
	}
	InitSatelliteDS( dmx);
	InitNetworkName( dmx);
	InitActualNetworkID( dmx);
	InitFNTVer( dmx);
	InitLCN( dmx);
	InitServiceListDS( dmx);
}
void CHsvDvbFNT_Priv::ena_Sync(HsvDemux dmx)
{
   UNUSED( dmx );
}

HSVCOMPAREKEY(fntsatellitedsdconf, Primary,    HsvNITSatelliteDS, Original_NetworkId)

HSVCOMPAREKEY(fntsatellitedsdconf, Secondary,  HsvNITSatelliteDS, Tsid)

HSVCOMPAREKEY(fntsatellitedsdconf, Teritiary,  HsvNITSatelliteDS, NetworkId)

HSVCOMPAREKEY(fntsatellitedsdconf, Quaternary, HsvNITSatelliteDS, NetworkId)


HSVCOMPAREKEY(fntsrvclstconf, Primary,     HsvNITServiceList, Original_NetworkId)

HSVCOMPAREKEY(fntsrvclstconf, Secondary, HsvNITServiceList, Tsid)

HSVCOMPAREKEY(fntsrvclstconf, Teritiary,   HsvNITServiceList, ServiceId)



HSVCOMPAREKEY(fntlcnconf, Primary,     HsvFNTLCN, Original_NetworkId)

HSVCOMPAREKEY(fntlcnconf, Secondary,   HsvFNTLCN, Tsid)

HSVCOMPAREKEY(fntlcnconf, Teritiary,   HsvFNTLCN, ServiceId)
/*Below is not used */

#ifndef __cplusplus

HSVCOMPAREKEY(fntlcnconf, QuaternaryKey, HsvFNTLCN, ServiceId)

#endif


Nat8 CHsvDvbFNT_Priv::fntsrvclstconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}

Nat8 CHsvDvbFNT_Priv::fntlcnconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}


Bool CHsvDvbFNT_Priv::ipop_PopulateFNT( HsvDemux dmx , Address fnt_parser, int code )
{
    int retval = TRUE;
	Typefnt_parser* NetWkTable = (Typefnt_parser*)fnt_parser;
	
	PopulateNetworkName(dmx, NetWkTable, code);
	PopulateNetworkSDSD(dmx, NetWkTable, code);
	PopulateServiceListDS(dmx, NetWkTable, code);
	PopulateLogicalChannel(dmx, NetWkTable, code);
	
	if( sec_TableCompleted & code )
    {
		if( FNT_TABLE_ID == NetWkTable->TableId) 
        {  
			if( ctrlN_iPresent())
			{
				TraceNotice(m,"code =%d ctrlN_DataAvailable %d",code,sec_TableCompleted);
				ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_FNT);
			}
        }
    }
	
	return retval;
}

void CHsvDvbFNT_Priv::InitSatelliteDS(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_FntSatelliteDS);
}
void CHsvDvbFNT_Priv::InitActualNetworkID(HsvDemux dmx)
{
    DmxROMData[dmx].NetworkId = HSV_INVALID_NETWORKID;
}
void CHsvDvbFNT_Priv::InitNetworkName(HsvDemux dmx)
{
    DmxROMData[dmx].NetworkName[0] = 0;
}
void CHsvDvbFNT_Priv::InitFNTVer(HsvDemux dmx)
{
    DmxROMData[dmx].FNTVer = 0xff;
}
void CHsvDvbFNT_Priv::InitLCN(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_FntLcnTable);
}

void CHsvDvbFNT_Priv::InitServiceListDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_FntSrvclstTable);
}


Bool CHsvDvbFNT_Priv::PopulateNetworkName(HsvDemux dmx, Typefnt_parser *NetWkTable,  int code)
{
    int len = 0;
    int HsvEvtNull = 0;
	int stringlen = MAX_NETWORK_NAME_SIZE;

    if( sec_SctArrived & code )
    {
		DmxROMData[dmx].FNTVer = NetWkTable->VersionNo;
		DmxROMData[dmx].NetworkId =  NetWkTable->NetworkId;
		DmxROMData[dmx].FNTAvail = TRUE;
	
        if(NetWkTable->NetworkName_Descriptor.DescriptorValid)
        {  
            Nat8 *NwName = (Nat8 *) NetWkTable->NetworkName_Descriptor.NetworkName;
            
            len = NetWkTable->NetworkName_Descriptor.NetworkNameLen;
		
			charsetutil_MbToWcEx( NwName, len, DmxROMData[dmx].NetworkName, &stringlen, FALSE);
			DmxROMData[dmx].NetworkName[stringlen] = 0; 
		
            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(NetworkName, dvb, fnt),  0, 0, 0, HsvEvtNull); 
            strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(NetworkName, dvb, fnt));
        }
    }
    return TRUE;
}

Bool CHsvDvbFNT_Priv::PopulateNetworkSDSD(HsvDemux dmx, Typefnt_parser *NetWkTable, int code)
{
    HsvNITSatelliteDS DbaseVersion, TempVersion;
    int i, HsvEvtNull = 0,j = 0, tsloop = 0;
	int Ppty = HSVSPID(SatelliteDS, dvb, fnt);
	int tableid = srtdbids_FntSatelliteDS;

	if( sec_SctArrived & code )
	{
		while ( tsloop < NetWkTable->TsLoopDataNum)
		{
			for( i = 0; i < NetWkTable->TsLoopData[tsloop].SDSDDescNum; i++)
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
						DbaseVersion.FECInner		= NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].FEC_Inner;
						DbaseVersion.Polarization   = MapPolarization (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Polarization);
						DbaseVersion.RollOff		= NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].RollOff;
						DbaseVersion.ModulationSystem = MapModulationStd (NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].Modulationsystem);
						DbaseVersion.OrbitalPosition = ConvertBcdToDecimal ((NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].OrbitalPostion & 0xFFFF));
						DbaseVersion.WestEastFlag = NetWkTable->TsLoopData[tsloop].SDSD_Descriptor[i].SDSD[j].WestEastFlag;
					
						if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
						{
							if(FALSE == srtdb_Update(tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion) ))
							{
								ASSERT(FALSE);
							}
							else
							{
								int NoofRec = srtdb_GetNoOfRecords(srtdbids_FntSatelliteDS);
								TraceNotice(m,"SDSD Updated: ONID:%d TSID: %d NoofRec: %d",DbaseVersion.Original_NetworkId,DbaseVersion.Tsid, NoofRec);
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
								int NoofRec = srtdb_GetNoOfRecords(srtdbids_FntSatelliteDS);
								TraceNotice(m,"SDSD Addition: ONID:%d TSID: %d NoofRec: %d",DbaseVersion.Original_NetworkId,DbaseVersion.Tsid,NoofRec);
								strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.NetworkId);
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
	 					TraceNotice(m,"SDSD Removed: ONID:%d TSID: %d",DbaseVersion.Original_NetworkId,DbaseVersion.Tsid);
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

Bool CHsvDvbFNT_Priv::PopulateServiceListDS ( HsvDemux dmx, Typefnt_parser *NetWkTable,  int code)
{
    HsvNITServiceList DbaseVersion, TempVersion; 
    int i= 0;
    int tsloop = 0; 
    int j = 0;
	int Ppty = HSVSPID(ServiceList, dvb, fnt);
	int tableid = srtdbids_FntSrvclstTable;
    while ( (tsloop < NetWkTable->TsLoopDataNum) && (sec_SctArrived & code))
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
					DbaseVersion.ServiceType      	= NetWkTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListDesc[j].ServiceType; 
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
					
						if(FALSE == srtdb_Insert( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId,0, (Address)(&DbaseVersion)))
						{
							TraceInfo(m,"FAILED ONID %d TSID = %d SID = %d",DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);	
						}
						else
						{
						
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
						TraceNotice(m," Delete ONID %d TSID = %d SID = %d",DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);					
						
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

Bool CHsvDvbFNT_Priv::PopulateLogicalChannel ( HsvDemux dmx, Typefnt_parser *NetWkTable,  int code)
{
   
    HsvFNTLCN DbaseVersion; 
    HsvFNTLCN LogicalChannel; 
    int i = 0, tsloop = 0, j = 0;
    Nat16 vis_flag;
    
	Nat16 lcn;
	int Ppty = HSVSPID(LCN, dvb, fnt);
	int tableid = srtdbids_FntLcnTable;


	while ( tsloop < NetWkTable->TsLoopDataNum)
	{
		if( sec_SctArrived & code )
		{
			int numlogicalchannelinfo = NetWkTable->TsLoopData[tsloop].LCNM7DescNum;
			
			for( i = 0; i < numlogicalchannelinfo; i++)
			{
				if(NetWkTable->TsLoopData[tsloop].LCNM7_Descriptor[i].DescriptorValid)
				{
					for( j = 0; j < NetWkTable->TsLoopData[tsloop].LCNM7_Descriptor[i].LCNLen ; j++)
					{
                        Nat16 serviceid = NetWkTable->TsLoopData[tsloop].LCNM7_Descriptor[i].LCNDesc[j].ServiceId;
                        lcn = NetWkTable->TsLoopData[tsloop].LCNM7_Descriptor[i].LCNDesc[j].LCNValue ;
						vis_flag = !(NetWkTable->TsLoopData[tsloop].LCNM7_Descriptor[i].LCNDesc[j].Hidden);
                        
                        //printf("Function : %s Line : %d VisFlag : %d SID : %d:LCN = %d\r\n",__FUNCTION__,__LINE__,vis_flag,serviceid,lcn);
                        if ( srtdb_QueryOnKey( tableid, NetWkTable->TsLoopData[tsloop].ONID, NetWkTable->TsLoopData[tsloop].TSID, serviceid , 0,(Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if( ( DbaseVersion.NetworkId == NetWkTable->NetworkId ) &&  ( DbaseVersion.VersionNumber != NetWkTable->VersionNo ) )
                                {
                                    Bool LCNChanged = FALSE;
                                    Bool LCNAvailChanged = FALSE; /*fixme: This is not yet parsed */
                                                                    
                                    if( DbaseVersion.LogicalChannelNum != lcn)
                                    {
                                        DbaseVersion.LogicalChannelNum = lcn;
                                        LCNChanged = TRUE;
                                    }
                                    DbaseVersion.VisibleService     = vis_flag;  
                                
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
                                LogicalChannel.ServiceId          = NetWkTable->TsLoopData[tsloop].LCNM7_Descriptor[i].LCNDesc[j].ServiceId;
                                LogicalChannel.LogicalChannelNum  = lcn;
                                //DP(("PopulateLogicalChannel ELSE LINE 779::LINE:%d lcn:%d,tableid:%d\n\n",__LINE__,lcn,tableid));			
                                LogicalChannel.VisibleService     = vis_flag;
                                LogicalChannel.VersionNumber      = NetWkTable->VersionNo;
                                srtdb_Insert( tableid, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId , LogicalChannel.ServiceId , (Address)(&LogicalChannel));
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


int CHsvDvbFNT_Priv::ConvertBcdToDecimal (int bcdvalue)
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

int CHsvDvbFNT_Priv::MapModulationType (Nat8 modln)
{
	Nat8 retval = -1;

	switch (modln)
	{
	case MOD_TYPE_AUTO:
		/* Auto */
		break;
	case MOD_TYPE_QPSK:
		retval = MOD_TYPE_QPSK;
		break;
	case MOD_TYPE_8PSK:
		retval = MOD_TYPE_8PSK;
		break;
	case MOD_TYPE_16QAM:
		/* Auto */
		break;
	}
	return retval;
}

Nat8 CHsvDvbFNT_Priv::MapPolarization (Nat8 pol)
{
	Nat8 retval = POLARIZATION_HORIZANTAL;

	retval = (pol == 0) ? POLARIZATION_HORIZANTAL : POLARIZATION_VERTICAL;

	return retval;
}
int CHsvDvbFNT_Priv::MapModulationStd (Nat8 modlnstd)
{
	return ((modlnstd == 0) ? MODULATION_STD_DVBS: MODULATION_STD_DVBS2);	
}


/********************************************************************************/

/*************************IHsvStream Implementation *******************************/
/***********************************************************************************/

int CHsvDvbFNT_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;
    
	UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(LCN, dvb, fnt):
		retval = srtdb_GetNoOfRecords(srtdbids_FntLcnTable); 
		break;
		
		case HSVSPID(SatelliteDS, dvb, fnt): 
		retval = srtdb_GetNoOfRecords(srtdbids_FntSatelliteDS); 
		TraceNotice(m,"strapi_GetSize : SDSDs: %d", retval);
		break;
		
		case HSVSPID(ServiceList, dvb, fnt):
		retval = srtdb_GetNoOfRecords(srtdbids_FntSrvclstTable);
		break;
		
		default:
		ASSERT(FALSE);
		break;	
	}
	 return retval;
}

Bool CHsvDvbFNT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{    
	UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(LCN, dvb, fnt):
		srtdb_SearchOnKey(srtdbids_FntLcnTable, key1, key2, key3,0, (int *)&index);
		break;
		
		case HSVSPID(SatelliteDS, dvb, fnt): 
		srtdb_SearchOnKey(srtdbids_FntSatelliteDS, key1, key2, key3,0, (int *)&index);
		break;
		
		case HSVSPID(ServiceList, dvb, fnt):
		srtdb_SearchOnKey(srtdbids_FntSrvclstTable, key1, key2, key3,0, (int *)&index);
		break;
		
		default:
		ASSERT(FALSE);
		break;	

	}
	return TRUE;
}


Bool CHsvDvbFNT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    switch(prop)
    {
		case HSVSPID(NetworkID, dvb, fnt) :
			{
				Nat16 *pval = (Nat16 *)val;
				*pval = DmxROMData[demux].NetworkId;
				if(DmxROMData[demux].FNTAvail)
				{
					retval = TRUE;
				}
				break;
			}
		case HSVSPID(NetworkName, dvb, fnt):
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
		case HSVSPID(FNTVer, dvb, fnt):
			{
				Nat8 *pval = (Nat8 *)val;
				*pval = DmxROMData[demux].FNTVer;
				if(DmxROMData[demux].FNTAvail)
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
		case HSVSPID(LCN, dvb, fnt):
		retval = srtdb_QueryOnKey(srtdbids_FntLcnTable, key1, key2, key3,0, (Address)val);
		break;
		
		case HSVSPID(SatelliteDS, dvb, fnt): 
		retval = srtdb_QueryOnKey(srtdbids_FntSatelliteDS, key1, key2, key3,0, (Address)val);
		break;
		
		case HSVSPID(ServiceList, dvb, fnt):
		retval = srtdb_QueryOnKey(srtdbids_FntSrvclstTable, key1, key2, key3,0, (Address)val);
		break;
		
		default:
		ASSERT(FALSE);
		break;	
	
	    }
    
    return retval;
}

Bool CHsvDvbFNT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;
    
	UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(LCN, dvb, fnt):
		retval = srtdb_QueryOnIndex(srtdbids_FntLcnTable,  index, (Address)val);
		break;
		
		case HSVSPID(SatelliteDS, dvb, fnt): 
		retval = srtdb_QueryOnIndex(srtdbids_FntSatelliteDS,  index, (Address)val);
		break;
		
		case HSVSPID(ServiceList, dvb, fnt):
		retval = srtdb_QueryOnIndex(srtdbids_FntSrvclstTable,  index, (Address)val);
		break;
	
	default:
            ASSERT(FALSE);
            break;
    }
         
    return retval;
}

Bool CHsvDvbFNT_Priv::strapi_GetRangeByKey( HsvDestination dest, int prop, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	Bool retval = FALSE;
    
	UNUSED (dest);
    switch (prop)
    {
		case HSVSPID(ServiceList, dvb, fnt):
		if(noofkeys ==2 )
		{
		
		retval = srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_FntSrvclstTable, key1, key2, from, to );
		//PrintfNotice(" inside ");
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
	
	//PrintfNotice(" noofkeys = %d prop = %d key1 = %d key2 = %d from =%d to %d retval = %d ",noofkeys,prop,key1,key2,*from,*to,retval);
	return retval;

}

Bool CHsvDvbFNT_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
	UNUSED (dest);
	UNUSED (value);
	
    return retval;
}/* End of function strmfltr_Set() */

Bool CHsvDvbFNT_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}

Bool CHsvDvbFNT_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
	return FALSE;
}

Bool CHsvDvbFNT_Priv::strmfltr_Clear    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}


void CHsvDvbFNT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
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


int CHsvDvbFNT_Priv::M7GetLCNValue(Nat8* ptr, int num)
{
    int val = (((ptr[0]&0x3f)<<HSV_BYTE) | (ptr[1]));
    return val;
}

Bool CHsvDvbFNT_Priv::Fnt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
     Nat8 *ptr = mBuffer;
     int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    Typefnt_parser  fnt_parser;
    Bool retval = TRUE;
    int dummy, loopcount = 0, descTag, descLen = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0,loop2index = 0, tableLen = 0, loop1length = 0,loop2length = 0, templen = 0; 
    if (secondarySectionSize > 0)
     {  
          memcpy(ptr, PrimarySectionStartAddress, primarySectionSize); 
          memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
     }  
      else
      {
                  ptr = PrimarySectionStartAddress;
      }
    v32 = GET32(0);
    tableLen = HSV_GETSECTION_LENGTH(ptr);
   fnt_parser.NtkNameDescNum=0;
   fnt_parser.TsLoopDataNum=0;
    fnt_parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    fnt_parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    fnt_parser.NetworkId = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    fnt_parser.VersionNo = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,4);
    fnt_parser.NetworkDescLen = GETNBITS(v32,12,12);
    ptr += 10;
    tableLen = tableLen - 10;
    v32 = GET32( 0);
    while(loopcount < fnt_parser.NetworkDescLen)
    {
        descLoopLen = 0;
        descTag = GETNBITS(v32,0, 8); 
        descLen = GETNBITS(v32,8, 8); 
        switch(descTag) {
        case 0x40:
             fnt_parser.NetworkName_Descriptor.DescriptorTag = GETNBITS(v32,0,8);
             fnt_parser.NetworkName_Descriptor.DescriptorLen = GETNBITS(v32,8,8);
             fnt_parser.NetworkName_Descriptor.NetworkNameLen = GETNBITS(v32,16,0);
                     //fnt_parser.NetworkName_Descriptor.NetworkNameLen = descLen;
                     descLoopLen = HSV_PARSER_MIN(80,fnt_parser.NetworkName_Descriptor.NetworkNameLen); 
                     ptr += 2;
                     memcpy(fnt_parser.NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
                     ptr += fnt_parser.NetworkName_Descriptor.NetworkNameLen;
                     v32 = GET32( 0);
                     fnt_parser.NetworkName_Descriptor.NetworkNameLen = descLoopLen;
                 fnt_parser.NetworkName_Descriptor.DescriptorValid = TRUE;
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
    ipop_PopulateFNT(demux, &fnt_parser,sec_SctArrived );
    fnt_parser.TsLoopLen = GETNBITS(v32,4,12);
    ptr += 2;
    tableLen = tableLen - 2;
    v32 = GET32( 0);
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
    {
   fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum=0;
   fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum=0;
   fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum=0;
        fnt_parser.TsLoopData[tsloopIndex].TSID = GETNBITS(v32, 0,16);
        fnt_parser.TsLoopData[tsloopIndex].ONID = GETNBITS(v32, 16,16);
        v32 = GET32( 4);
        dummy = GETNBITS(v32,0,4);
        fnt_parser.TsLoopData[tsloopIndex].TsDescLoopLen = GETNBITS(v32, 4,12);
        ptr += 6;
        tableLen = tableLen - 6;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < fnt_parser.TsLoopData[tsloopIndex].TsDescLoopLen)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8); 
            descLen = GETNBITS(v32,8, 8); 
            switch(descTag) {
            case 0x43:
            if(fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum<10)
            {
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD) ;
                 while( loop1length< HSV_PARSER_MIN(fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorLen, templen))
                 {
                 int minLength = 0;
				 int freq = 0;
                 freq = fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Frequency = GETNBITS(v32,0, 32); 
				 TraceNotice(m,"SDSD for ONID: %d TSID : %d Frequency: %d",fnt_parser.TsLoopData[tsloopIndex].ONID,fnt_parser.TsLoopData[tsloopIndex].TSID,freq);
                 v32 = GET32( 4);
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].OrbitalPostion = GETNBITS(v32,0, 16); 
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].WestEastFlag = GETNBITS(v32,16, 1); 
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Polarization = GETNBITS(v32,17, 2); 
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].RollOff = GETNBITS(v32,19, 2); 
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Modulationsystem = GETNBITS(v32,21, 1); 
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].Modulationtype = GETNBITS(v32,22, 2); 
                 v32 = GET32( 7);
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].SymbolRate = GETNBITS(v32,0, 28); 
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSD[loop1index].FEC_Inner = GETNBITS(v32,28, 4); 
                loop1length += 11;
                loop1index++;
                ptr += 11;
                 v32 = GET32( 0);
                 }
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].SDSDLen = loop1index;
                 fnt_parser.TsLoopData[tsloopIndex].SDSD_Descriptor[fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum].DescriptorValid = TRUE;
                 fnt_parser.TsLoopData[tsloopIndex].SDSDDescNum++;
            }
            else
            {
				PrintfNotice("Exceeded SDSDDescNum  ");			
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);
            
            v32 = GET32( 0);
            break;
            
            case 0x41:
            if(fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum<10)
            {
                 fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc) ;
                 while( loop1length< HSV_PARSER_MIN(fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen, templen))
                 {
                 int minLength = 0;
                 fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
                 fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceType = GETNBITS(v32,16, 8); 
                loop1length += 3;
                loop1index++;
                ptr += 3;
                 v32 = GET32( 0);
                 }
                 fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListLen = loop1index;
                 fnt_parser.TsLoopData[tsloopIndex].Service_List_Descriptor[fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorValid = TRUE;
                 fnt_parser.TsLoopData[tsloopIndex].ServiceListDescNum++;
            }
            else
            {
			PrintfNotice("Exceeded ServiceListDescNum  ");			
                ptr += 2 + descLen;
            }
            loopcount += 2 + descLen;
            tableLen = tableLen - (2 + descLen);
            
            v32 = GET32( 0);
            break;
            
            case 0x83:
            if(fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum<10)
            {
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].LCNDesc) ;
                 while( loop1length< HSV_PARSER_MIN(fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].DescriptorLen, templen))
                 {
                 int minLength = 0;
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].LCNDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].LCNDesc[loop1index].Hidden = GETNBITS(v32,17, 1); 
                 loop1length += 2;
                 ptr += 2;
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].LCNDesc[loop1index].LCNValue = M7GetLCNValue( ptr, 14);
                loop1length += 2;
                loop1index++;
                ptr += 2;
                 v32 = GET32( 0);
                 }
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].LCNLen = loop1index;
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7_Descriptor[fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum].DescriptorValid = TRUE;
                 fnt_parser.TsLoopData[tsloopIndex].LCNM7DescNum++;
            }
            else
            {
						PrintfNotice("Exceeded LCNM7DescNum  ");			
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
            }//endswitch
        }//endwhile descloop
    tsloopIndex++;
    loopcount = 0;
    fnt_parser.TsLoopDataNum = tsloopIndex;
    ipop_PopulateFNT(demux, &fnt_parser,sec_SctArrived );
    tsloopIndex = 0;
    }//endwhile tsloop
	if(code & sec_TableCompleted)
	{
		ipop_PopulateFNT(demux,(Address) &fnt_parser,code );
	}
    dummy = GETNBITS(v32,0,32);
    return TRUE;
}//end function

void CHsvDvbFNT_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
{
}

void CHsvDvbFNT_Priv::dmxsecfN_OnRequestNotAllowed ()
{
}
