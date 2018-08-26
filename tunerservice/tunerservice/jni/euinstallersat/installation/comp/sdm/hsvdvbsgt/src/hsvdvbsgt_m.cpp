
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
 *          %name: hsvdvbsgt_m.c %
 *       %version: TVG_1 %
 * %date_modified: Thu Feb 19 17:19:20 2009 %
 *    %derived_by: shiva %
 */
 

#include "CHsvDvbSGT.h"



TRACESYMBOL(m, "s2/sdm/hsvdvbsgt")


#ifndef __cplusplus

#else

#endif








SGTDmxRomDataStruct CHsvDvbSGT::s__DmxROMData[HsvDmxLast];


Nat8 CHsvDvbSGT::s__mBuffer[16*1024];




/***************Local Functions******************************************/





#define SGT_PID_VALUE                      (0x0011)

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define HSV_INVALID_TSID                   (0xFFFF)

#define HSV_INVALID_ONID                   (0xFFFF)

#define HSV_INVALID_SERVICE                (0xFFFF)

#define INVALID_PID         			   (0x1FFF)

#define SGT_INDEX (0)

#define MAX_PROPERTIES	(2)

#define DMX_BUFFER_SIZE						(32 * 1024)

#define SGT_REQ				(0x1)

#define SGT_TABLE_ID        (0x91)

#define DP(x)

#define FNADDR(f) (& CHsvDvbSGT:: f)

#define GETINDEX(p) (p - HsvdvbsgtFirstProperty - 1)

#define CLASSSCOPE CHsvDvbSGT::



/**************************Initialisations*****************************************/

void CHsvDvbSGT::Init(void)
{
    int  dmx;
    int      i;
    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {        
        for(i = 0; i < SGT_MAX_SECTIONS; i++)
        {
            /* Clear our structures to ensure that we dont have junk values in them*/
            DmxROMData[dmx].SubscrId[i]        =   HSV_INVALID_SCT_REQUEST;
		}
		DmxROMData[dmx].SectionInfo[SGT_INDEX] = conf_SgtParsing;
		DmxROMData[dmx].SgtAvail = FALSE;
        DmxROMData[dmx].SgtVer = 0xFF;
    }

	
	for(i=0; i<FILTER_DEPTH; i++)
    {
        ModeArray[i] = 0;
        MatchArray[i] = 0;
        MaskArray[i] = 0;
    }
    MatchArray[0] = SGT_TABLE_ID;
    MaskArray[0] = 0xff;
}

void CHsvDvbSGT::TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbSGT::TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbSGT::Enable(HsvDemux dmx)
{
	HsvSDMSIDataValues SiValues;
    DmxROMData[dmx].SgtAvail = FALSE;
    DmxROMData[dmx].SgtVer = 0xFF;
	InitSgt(dmx);
	InitSgtVer(dmx);
	InitNetworkID(dmx);
	InitsgtSection(dmx);
	TraceNotice (m, "SGT: ena_Enable ");
	
	SiValues.Pid = INVALID_PID;
	pakgins_GetSIDetails(&SiValues);
	
    /* Initialise Sections */
    if((conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[SGT_INDEX]))&&((SiValues.Pid != INVALID_PID)))  
    {
		Nat16 TidExtn = 1; /*service_list_id : 1*/

		HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, SGT_TABLE_ID, SiValues.Pid};
//		DmxROMData[dmx].SubscrId[SGT_INDEX] = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Sgt_Parser_Parser));
//		DmxROMData[dmx].SubscrId[SGT_INDEX]  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)SiValues.Pid, SGT_TABLE_ID,SGT_TABLE_ID, FNADDR(Sgt_Parser_Parser));

		DmxROMData[dmx].SubscrId[SGT_INDEX]  = sec_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx), (int)SiValues.Pid, SGT_TABLE_ID , TidExtn, SGT_TABLE_ID, FNADDR(Sgt_Parser_Parser));             
		TraceNotice (m, "SGT: Requested %d with PID: %d TableID: %d",(int)DmxROMData[dmx].SubscrId[SGT_INDEX],SiValues.Pid,SGT_TABLE_ID);
    }
}

void CHsvDvbSGT::InitSgt(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_SgtTable);
}
void CHsvDvbSGT::InitSgtVer(HsvDemux dmx)
{
    DmxROMData[dmx].SgtVer = 0xff;
}

void CHsvDvbSGT::InitNetworkID(HsvDemux dmx)
{
    DmxROMData[dmx].NetworkId = HSV_INVALID_NETWORKID;
}

void CHsvDvbSGT::Disable(HsvDemux dmx)
{
	/* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[SGT_INDEX]))  
	{
		if( DmxROMData[dmx].SubscrId[SGT_INDEX] != HSV_INVALID_SCT_REQUEST )
		{
			sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxROMData[dmx].SubscrId[SGT_INDEX]);                
			DmxROMData[dmx].SubscrId[SGT_INDEX] = HSV_INVALID_SCT_REQUEST;
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
	InitSgt(dmx);
	InitSgtVer(dmx);
	InitNetworkID(dmx);
}

void CHsvDvbSGT::Sync(HsvDemux dmx)
{
    UNUSED (dmx);
    /* TODO */
}

HSVCOMPAREKEY(sgtconf, Primary,    HsvSGTService, Original_NetworkId)

HSVCOMPAREKEY(sgtconf, Secondary,  HsvSGTService, Tsid)

HSVCOMPAREKEY(sgtconf, Teritiary,  HsvSGTService, ServiceId)

// TODO: Shiva: check if it is required
HSVCOMPAREKEY(sgtconf, Quaternary,  HsvSGTService, LogicalChannelNum)


/*
Nat8 CHsvDvbSGT::sgtconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    ASSERT (! "sgt Table does not have a teritiary key" );
    return FALSE;
}*/

Bool CHsvDvbSGT::PopulateSGT ( HsvDemux dmx , Address pSgt_Parser, int code)
{
	if( sec_TableCompleted & code )
	{
		if( ctrlN_iPresent())
		{
			TraceNotice(m,"%s: %d: code =%d ctrlN_DataAvailable %d",__FUNCTION__,__LINE__,code,sec_TableCompleted);
			ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SGT);
		}
	}
	else
	{
		PopulatesgtSection(dmx, (Typesgt_parser *)pSgt_Parser, code);

	}
	return TRUE;
}

void CHsvDvbSGT::InitsgtSection(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_SgtTable);
}

Bool CHsvDvbSGT::PopulatesgtSection( HsvDemux dmx, Typesgt_parser *ServiceTable,  int code)
{
	return PopulateServiceDescriptionSection (dmx, ServiceTable, HSVSPID(ActualTSService, dvb, sgt), srtdbids_SgtTable, code);
}

Bool CHsvDvbSGT::PopulateServiceDescriptionSection(HsvDemux dmx, Typesgt_parser *ServiceTable, int Ppty, int tableid, int code)
{
    HsvSGTService       DbaseVersion;
    int                 i                   = 0;
    int					tsloop 				= 0;		
    int                 index               = 0;
    Bool                retval              = TRUE;
    


	
	while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
        {
         //   PrintfNotice("PopulatesgtSection:: ServiceDescriptionNum:%d\n\n",ServiceDescriptionNum);
    	    int ServiceDescriptionNum = ServiceTable->TsLoopData[tsloop].ServiceDescNum;
			DmxROMData[dmx].SgtVer = ServiceTable->VersionNo;
            for( i = 0; i < ServiceDescriptionNum; i++)
            {
                if(ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
                {
                    if( srtdb_QueryOnKey( tableid,ServiceTable->TsLoopData[tsloop].original_network_id,ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id, 0, (Address)(&DbaseVersion) ) )
                    {   /* Record exists => Update it */
                        /* There can be duplicate service description in the same sgt. In such cases we
                        take the last.*/
                        
                        DbaseVersion.Original_NetworkId         = ServiceTable->TsLoopData[tsloop].original_network_id;
                        DbaseVersion.Tsid        = ServiceTable->TsLoopData[tsloop].Transport_stream_id;
						DbaseVersion.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
						DbaseVersion.VersionNumber					= ServiceTable->VersionNo ;
						DbaseVersion.LogicalChannelNum		 = ServiceTable->TsLoopData[tsloop].logical_channel_number;
						DbaseVersion.VisibleService		=	ServiceTable->TsLoopData[tsloop].visible_flag;						
                        
						AssignServiceDescriptor(ServiceTable,tsloop, i, &DbaseVersion);
						//PrintfNotice("PopulatesgtSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid);
   						if( srtdb_Update(tableid, ServiceTable->TsLoopData[tsloop].original_network_id, ServiceTable->TsLoopData[tsloop].Transport_stream_id, ServiceTable->TsLoopData[tsloop].service_id, 0, (Address)(&DbaseVersion)) )
                        {                    
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceTable->TsLoopData[tsloop].original_network_id, ServiceTable->TsLoopData[tsloop].Transport_stream_id, ServiceTable->TsLoopData[tsloop].service_id, 0); /* TODO: Define events */
                        }
                    }
                    else
                    {   
                        HsvSGTService   sgtSection;
                        /* Record does not exist => Insert Fresh */
                        sgtSection.Original_NetworkId         = ServiceTable->TsLoopData[tsloop].original_network_id;
                        sgtSection.Tsid        = ServiceTable->TsLoopData[tsloop].Transport_stream_id;
						sgtSection.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
						sgtSection.LogicalChannelNum		 = ServiceTable->TsLoopData[tsloop].logical_channel_number;
						sgtSection.VisibleService		=	ServiceTable->TsLoopData[tsloop].visible_flag;						

                        AssignServiceDescriptor(ServiceTable,tsloop, i, &sgtSection);
						
                        //PrintfNotice("PopulatesgtSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid);
                        if( srtdb_Insert( tableid, ServiceTable->TsLoopData[tsloop].original_network_id,  ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id,0, (Address)(&sgtSection)) )
                        {   
                        	TraceNotice(m,"service Added to db onid: %d tsid: %d svcid: %d lcn: %d",sgtSection.Original_NetworkId,sgtSection.Tsid,sgtSection.ServiceId,sgtSection.LogicalChannelNum);
                            srtdb_SearchOnKey(tableid, ServiceTable->TsLoopData[tsloop].original_network_id, sgtSection.Tsid,sgtSection.ServiceId ,0, (int *)&index);
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, sgtSection.Original_NetworkId,sgtSection.Tsid , sgtSection.ServiceId);
                        }
                        else
                        {
                            PrintfNotice("PopulatesgtSection:: srtdb_Insert failed,ServiceTable->original_network_id:%d, ServiceTable->TsLoopDataNum[tsloop].service_id:%d\n\n", ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id);
                        }
                    }
                }
			}/*end of for loop */
			/*If there is no service descriptor still add the service with default values */
			if(ServiceDescriptionNum == 0)
			{
				if( srtdb_QueryOnKey( tableid,ServiceTable->TsLoopData[tsloop].original_network_id,ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id, 0, (Address)(&DbaseVersion) ) )
				{	/* Record exists => Update it */
					
					DbaseVersion.Original_NetworkId 		= ServiceTable->TsLoopData[tsloop].original_network_id;
					DbaseVersion.Tsid		 = ServiceTable->TsLoopData[tsloop].Transport_stream_id;
					DbaseVersion.ServiceId					= ServiceTable->TsLoopData[tsloop].service_id;
					DbaseVersion.VersionNumber					= ServiceTable->VersionNo ;
					
					if( srtdb_Update(tableid, ServiceTable->TsLoopData[tsloop].original_network_id, ServiceTable->TsLoopData[tsloop].Transport_stream_id, ServiceTable->TsLoopData[tsloop].service_id, 0, (Address)(&DbaseVersion)) )
					{					 
						strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceTable->TsLoopData[tsloop].original_network_id, ServiceTable->TsLoopData[tsloop].Transport_stream_id, ServiceTable->TsLoopData[tsloop].service_id, 0); /* TODO: Define events */
					}
				}
				else
				{	
					HsvSGTService	sgtSection;
					/* Record does not exist => Insert Fresh */
					sgtSection.Original_NetworkId		  = ServiceTable->TsLoopData[tsloop].original_network_id;
					sgtSection.Tsid 	   = ServiceTable->TsLoopData[tsloop].Transport_stream_id;
					sgtSection.ServiceId				  = ServiceTable->TsLoopData[tsloop].service_id;
					sgtSection.LogicalChannelNum		 = ServiceTable->TsLoopData[tsloop].logical_channel_number;
					sgtSection.VisibleService		=	ServiceTable->TsLoopData[tsloop].visible_flag;						
				
					AssignDefaultServiceDescriptor(&sgtSection);
					
					//PrintfNotice("PopulatesgtSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid);
					if( srtdb_Insert( tableid, ServiceTable->TsLoopData[tsloop].original_network_id,  ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id,0, (Address)(&sgtSection)) )
					{	
						TraceNotice(m,"service Added to db with default service descriptor onid: %d tsid: %d svcid: %d lcn: %d",sgtSection.Original_NetworkId,sgtSection.Tsid,sgtSection.ServiceId,sgtSection.LogicalChannelNum);
						srtdb_SearchOnKey(tableid, ServiceTable->TsLoopData[tsloop].original_network_id, sgtSection.Tsid,sgtSection.ServiceId ,0, (int *)&index);
						strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, sgtSection.Original_NetworkId,sgtSection.Tsid , sgtSection.ServiceId);
					}
					else
					{
						PrintfNotice("PopulatesgtSection:: srtdb_Insert failed,ServiceTable->original_network_id:%d, ServiceTable->TsLoopDataNum[tsloop].service_id:%d\n\n", ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id);
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
                if(srtdb_QueryOnIndex(tableid,i,(Address )(&DbaseVersion)))
                {
                    if(DbaseVersion.VersionNumber != DmxROMData[dmx].SgtVer)
                    {

                        /* delete the record */
						
                        if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId,DbaseVersion.Tsid, DbaseVersion.ServiceId, 0))
                        {  
                            DP(("Version Number Mismatch Hence Delete is Done\n\n"));
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId,DbaseVersion.Tsid, DbaseVersion.ServiceId);
                        }
                        else
                        {  /* Could not delete */
                            ASSERT(FALSE);                   
                        }
                    }
                }
                else
                {
                    DP(("PopulateSGTSection::LINE:%d\n\n",__LINE__));
                }
                /* decrement to prev index*/
                i--;
            }
        }
	 tsloop++;
    }		
    return retval;
}



void CHsvDvbSGT::AssignServiceDescriptor(Typesgt_parser *ServiceTable, int tsloop, int i, HsvSGTService *DbaseVersion)
{
    int len = 0;

    if(TRUE == ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
    {  
        Nat8 *SvcName = (Nat8 *)ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceName;

        DbaseVersion->ServiceName[0] = '\0';

        len =   ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceNameLen;

        DbaseVersion->ServiceType   = ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].ServiceType;
		SvcName[len] = '\0';
		memset(DbaseVersion->ServiceName,0x00,MAXSERVICENAMELEN * 2);
        charsetutil_MbToWc( SvcName, 
                            len, 
                            DbaseVersion->ServiceName,
                            MAXSERVICENAMELEN,
                            (len >= eurdiv_ChannelNameLength) ? TRUE : FALSE 
                            );
        len =   MAXSERVICENAMELEN;
    }
    DbaseVersion->ServiceName[len] = '\0'; /* Erase Previous Name if invalid*/
}

void CHsvDvbSGT::AssignDefaultServiceDescriptor(HsvSGTService *DbaseVersion)
{

	memset(DbaseVersion->ServiceName,0x00,MAXSERVICENAMELEN * 2);
	AsciiToUnicode("-----",DbaseVersion->ServiceName,5);
	DbaseVersion->ServiceName[5] = '\0';
    DbaseVersion->ServiceName[MAXSERVICENAMELEN] = '\0'; 

    DbaseVersion->ServiceType   = TelevisionService;
}


void CHsvDvbSGT::AsciiToUnicode( char * str, Nat16* dest, int length)
{
    int i=0;

    for(i = 0; i < eurdiv_ChannelNameLength; i++)
    {
        dest[i] = 0;
    }

    for(i = 0; i < length; i++)
    {
        dest[i] = str[i];
    }

}



/*************************IHsvStream Implementation *******************************/


int CHsvDvbSGT::GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;

	UNUSED (inst);
    switch (prop)
    {
       
        case HSVSPID(ActualTSService, dvb, sgt):
            retval = srtdb_GetNoOfRecords(srtdbids_SgtTable); 
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}


Bool CHsvDvbSGT::GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(ActualTSService, dvb, sgt):
            retval = srtdb_SearchOnKey(srtdbids_SgtTable, key1, key2, key3, 0,(int *)&index);
            break;
        
      	default:
            ASSERT(FALSE);
            break;
    }		
    return retval;
}

Bool CHsvDvbSGT::GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
	switch(prop)
	{
		
		case HSVSPID(ActualTSService, dvb, sgt):
			retval = srtdb_QueryOnKey(srtdbids_SgtTable, key1, key2, key3, 0,(Address)val);
			break;
		
		default:
			ASSERT(!"Unknown Property");
			break;
	}
    
    return retval;
}

Bool CHsvDvbSGT::GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualTSService, dvb, sgt):
            retval = srtdb_QueryOnIndex(srtdbids_SgtTable, index, (Address)val);
            break;
		default:
            ASSERT(FALSE);
            break;
    }		
	TraceNotice(m," %s: %d: retval: %d",__FUNCTION__,__LINE__,retval);
    return retval;
}

Bool CHsvDvbSGT::Set(HsvDestination dest, int filterid, int value)
{
    Bool        retval = FALSE;    


    UNUSED( value );

    switch(filterid)
    {
      
        //case HsvsgtId:
            {                
            }
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */
/*************************************************************/
void CHsvDvbSGT::OnRequestCancelled( Nat32 subscrid )
{
    int i   = 0;
    int dmx = HsvDmxMain;

    for(i = 0; i < SGT_MAX_SECTIONS; i++)
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





Bool CHsvDvbSGT::Sgt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    Typesgt_parser  sgt_parser;
    Bool retval = TRUE;
	int service_descriptor_length = 0;
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
   sgt_parser.TsLoopDataNum=0;
    sgt_parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    sgt_parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    sgt_parser.ServiceListId = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    sgt_parser.VersionNo = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    ptr += 8;
    tableLen = tableLen - 8;
    v32 = GET32( 0);
	dummy = GETNBITS(v32,0,16);
	dummy = GETNBITS(v32,16,4);
	service_descriptor_length = GETNBITS(v32,20,12);
    ptr += 4;
    tableLen = tableLen - 4;
	/*Skip service list descriptor loop*/
	ptr += service_descriptor_length;
	tableLen = tableLen - service_descriptor_length;
    v32 = GET32( 0);
	dummy = GETNBITS(v32,0,4);
	
	/*TODO:service loop length length is skipped, check if it is required to parse later*/
	dummy = GETNBITS(v32,4,12);
	ptr += 2;
    tableLen = tableLen - 2;
	
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
    {
		sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum = 0;

        v32 = GET32( 0);
		sgt_parser.TsLoopData[tsloopIndex].service_id= GETNBITS(v32, 0,16);
        sgt_parser.TsLoopData[tsloopIndex].Transport_stream_id = GETNBITS(v32, 16,16);
        v32 = GET32( 4);
        sgt_parser.TsLoopData[tsloopIndex].original_network_id = GETNBITS(v32, 0,16);
        sgt_parser.TsLoopData[tsloopIndex].logical_channel_number = GETNBITS(v32, 16,14);
        sgt_parser.TsLoopData[tsloopIndex].visible_flag = GETNBITS(v32, 30,1);
        sgt_parser.TsLoopData[tsloopIndex].new_service_flag = GETNBITS(v32, 31,1);

        v32 = GET32( 8);
		dummy = GETNBITS(v32,0,16);
		dummy = GETNBITS(v32,16,4);
        sgt_parser.TsLoopData[tsloopIndex].Descriptor_loop_length = GETNBITS(v32, 20,12);
        ptr += 12;
        tableLen = tableLen - 12;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < sgt_parser.TsLoopData[tsloopIndex].Descriptor_loop_length)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8); 
            descLen = GETNBITS(v32,8, 8); 
            switch(descTag) {
            case 0x48:
            if(sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum<100)
            {
                 sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceType = GETNBITS(v32, 16,8);
                 sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = GETNBITS(v32, 24,8);
                     descLoopLen = HSV_PARSER_MIN(80,sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen); 
                     ptr += 4;
                     memcpy(sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderName,ptr,descLoopLen);
                     ptr += sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen;
                     v32 = GET32( 0);
                     sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = descLoopLen;
                 sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = GETNBITS(v32, 0,8);
                     descLoopLen = HSV_PARSER_MIN(80,sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen); 
                     ptr += 1;
                     memcpy(sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceName,ptr,descLoopLen);
                     ptr += sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen;
                     v32 = GET32( 0);
                     sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = descLoopLen;
                 sgt_parser.TsLoopData[tsloopIndex].Service_Descriptor[sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorValid = TRUE;
                 sgt_parser.TsLoopData[tsloopIndex].ServiceDescNum++;
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
            }//endswitch
        }//endwhile descloop
    tsloopIndex++;
    loopcount = 0;
    sgt_parser.TsLoopDataNum = tsloopIndex;
	PopulateSGT(demux,(Address) &sgt_parser,sec_SctArrived );
    tsloopIndex = 0;
    }//endwhile tsloop
	if(code & sec_TableCompleted)
	{
		PopulateSGT(demux,(Address) &sgt_parser,code );
	}
    dummy = GETNBITS(v32,0,32);
    return TRUE;
}//end function

void CHsvDvbSGT::OnRequestAllowed( HsvDestination dest )
{
}

void CHsvDvbSGT::OnRequestNotAllowed ()
{
}

Bool CHsvDvbSGT::IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}

Bool CHsvDvbSGT::IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
	return FALSE;
}

Bool CHsvDvbSGT::Clear    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}

Bool CHsvDvbSGT::GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	Bool retval = FALSE;

    switch (spid)
    {
		case HSVSPID(ActualTSService, dvb, sgt):
		if(noofkeys == 2)
		{
			retval = srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_SgtTable, key1, key2, from, to );
		}
		else if(noofkeys == 3)
		{
			retval = srtdb_SearchOnPrimarySecondaryAndTeritiaryKey(srtdbids_SgtTable, key1, key2, key3, from, to );
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

	TraceNotice(m," %s: %d retval: %d",__FUNCTION__,__LINE__,retval);

	return retval;

}
