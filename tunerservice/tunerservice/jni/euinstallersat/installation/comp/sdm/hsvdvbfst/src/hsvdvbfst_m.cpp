
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
 *          %name: hsvdvbfst_m.c %
 *       %version: TVG_4 %
 * %date_modified: Thu Feb 19 17:19:20 2009 %
 *    %derived_by: shreeshav %
 */
 

#include "_hsvdvbfst_m.h"



TRACESYMBOL(m, "s2/sdm/hsvdvbfst")


#ifndef __cplusplus

#else

#endif








struct DmxRomDataStruct CHsvDvbFST_Priv::s__DmxROMData[HsvDmxLast];


Nat8 CHsvDvbFST_Priv::s__mBuffer[16*1024];

Nat8 CHsvDvbFST_Priv::s__ModeArray[FILTER_DEPTH];

Nat8 CHsvDvbFST_Priv::s__MatchArray[FILTER_DEPTH];

Nat8 CHsvDvbFST_Priv::s__MaskArray[FILTER_DEPTH];





/***************Local Functions******************************************/










/**************************Initialisations*****************************************/

void CHsvDvbFST_Priv::pow_Init(void)
{
    int  dmx;
    int      i;
    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {        
        for(i = 0; i < MAX_SECTIONS; i++)
        {
            /* Clear our structures to ensure that we dont have junk values in them*/
            DmxROMData[dmx].SubscrId[i]        =   HSV_INVALID_SCT_REQUEST;
		}
		DmxROMData[dmx].SectionInfo[FST_INDEX] = conf_FstParsing;
		DmxROMData[dmx].FstAvail = FALSE;
        DmxROMData[dmx].FstVer = 0xFF;
    }
	
	for(i=0; i<FILTER_DEPTH; i++)
    {
        ModeArray[i] = 0;
        MatchArray[i] = 0;
        MaskArray[i] = 0;
    }
    MatchArray[0] = FST_TABLE_ID;
    MaskArray[0] = 0xff;
}

void CHsvDvbFST_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbFST_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbFST_Priv::ena_Enable(HsvDemux dmx)
{
	HsvSDMSIDataValues SiValues;
    DmxROMData[dmx].FstAvail = FALSE;
    DmxROMData[dmx].FstVer = 0xFF;
	InitFst(dmx);
	InitFstVer(dmx);
	InitNetworkID(dmx);
	InitfstSection(dmx);
	TraceNotice (m, "FST: ena_Enable ");
	
	SiValues.Pid = INVALID_PID;
	pakgins_GetSIDetails(&SiValues);
	
    /* Initialise Sections */
    if((conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[FST_INDEX]))&&((SiValues.Pid != INVALID_PID)))  
    {
		
		HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, FST_TABLE_ID, SiValues.Pid};
#ifndef __cplusplus
		DmxROMData[dmx].SubscrId[FST_INDEX]	= sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, (HsvSectionFilterCallback)Fst_Parser_Parser);
#else
		DmxROMData[dmx].SubscrId[FST_INDEX]	= sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Fst_Parser_Parser));
#endif

		TraceNotice (m, "FST: Requested with subscr id: %d, buf size : %d",(int)DmxROMData[dmx].SubscrId[FST_INDEX], DMX_BUFFER_SIZE);
    }
}

void CHsvDvbFST_Priv::InitFst(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_FstTable);
}
void CHsvDvbFST_Priv::InitFstVer(HsvDemux dmx)
{
    DmxROMData[dmx].FstVer = 0xff;
}

void CHsvDvbFST_Priv::InitNetworkID(HsvDemux dmx)
{
    DmxROMData[dmx].NetworkId = HSV_INVALID_NETWORKID;
}

void CHsvDvbFST_Priv::ena_Disable(HsvDemux dmx)
{
	/* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo[FST_INDEX]))  
	{
		if( DmxROMData[dmx].SubscrId[FST_INDEX] != HSV_INVALID_SCT_REQUEST )
		{
			sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxROMData[dmx].SubscrId[FST_INDEX]);                
			DmxROMData[dmx].SubscrId[FST_INDEX] = HSV_INVALID_SCT_REQUEST;
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
	InitFst(dmx);
	InitFstVer(dmx);
	InitNetworkID(dmx);
}

void CHsvDvbFST_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED (dmx);
    /* TODO */
}

HSVCOMPAREKEY(fstconf, Primary,    HsvfstSection, Original_NetworkId)

HSVCOMPAREKEY(fstconf, Secondary,  HsvfstSection, Transport_stream_id)

HSVCOMPAREKEY(fstconf, Teritiary,  HsvfstSection, ServiceId)


Nat8 CHsvDvbFST_Priv::fstconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED ( key );
    UNUSED ( data);
    ASSERT (! "fst Table does not have a teritiary key" );
    return FALSE;
}

Bool CHsvDvbFST_Priv::ipop_PopulateFST ( HsvDemux dmx , Address pFst_Parser, int code)
{
	if( sec_TableCompleted & code )
	{
		if( ctrlN_iPresent())
		{
			TraceNotice(m,"code =%d ctrlN_DataAvailable %d",code,sec_TableCompleted);
			ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_FST);
		}
	}
	else
	{
		PopulatefstSection(dmx, (Typefst_parser *)pFst_Parser, code);
	}
	return TRUE;
}

void CHsvDvbFST_Priv::InitfstSection(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_FstTable);
}

Bool CHsvDvbFST_Priv::PopulatefstSection( HsvDemux dmx, Typefst_parser *ServiceTable,  int code)
{
  
    return  PopulateServiceDescriptionSection (dmx, ServiceTable, HSVSPID(ActualTSService, dvb, fst), srtdbids_FstTable, code);
}

Bool CHsvDvbFST_Priv::PopulateServiceDescriptionSection(HsvDemux dmx, Typefst_parser *ServiceTable, int Ppty, int tableid, int code)
{
    HsvfstSection       DbaseVersion;
    int                 i                   = 0;
    int					tsloop 				= 0;		
    int                 index               = 0;
    Bool                retval              = TRUE;
    


	
	while ( tsloop < ServiceTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
        {
         //   PrintfNotice("PopulatefstSection:: ServiceDescriptionNum:%d\n\n",ServiceDescriptionNum);
    	    int ServiceDescriptionNum = ServiceTable->TsLoopData[tsloop].ServiceDescNum;
			DmxROMData[dmx].FstVer = ServiceTable->VersionNo;
            for( i = 0; i < ServiceDescriptionNum; i++)
            {
                if(ServiceTable->TsLoopData[tsloop].Service_Descriptor[i].DescriptorValid)
                {
                    if( srtdb_QueryOnKey( tableid,ServiceTable->TsLoopData[tsloop].original_network_id,ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id, 0, (Address)(&DbaseVersion) ) )
                    {   /* Record exists => Update it */
                        /* There can be duplicate service description in the same fst. In such cases we
                        take the last.*/
                        
                        DbaseVersion.Original_NetworkId         = ServiceTable->TsLoopData[tsloop].original_network_id;
                        DbaseVersion.Transport_stream_id        = ServiceTable->TsLoopData[tsloop].Transport_stream_id;
						DbaseVersion.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
                        DbaseVersion.Default_video_PID          = ServiceTable->TsLoopData[tsloop].Default_video_PID;
                        DbaseVersion.Default_audio_PID			= ServiceTable->TsLoopData[tsloop].Default_audio_PID;
                        DbaseVersion.Default_video_ECM_PID      = ServiceTable->TsLoopData[tsloop].Default_video_ECM_PID;
                        DbaseVersion.Default_audio_ECM_PID      = ServiceTable->TsLoopData[tsloop].Default_audio_ECM_PID;
                        DbaseVersion.Default_PCR_PID            = ServiceTable->TsLoopData[tsloop].Default_PCR_PID ;
						DbaseVersion.VersionNo					= ServiceTable->VersionNo ;
                        
						AssignServiceDescriptor(ServiceTable,tsloop, i, &DbaseVersion);
						//PrintfNotice("PopulatefstSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid);
   						if( srtdb_Update(tableid, ServiceTable->TsLoopData[tsloop].original_network_id, ServiceTable->TsLoopData[tsloop].Transport_stream_id, ServiceTable->TsLoopData[tsloop].service_id, 0, (Address)(&DbaseVersion)) )
                        {                    
                            strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), Ppty, ServiceTable->TsLoopData[tsloop].original_network_id, ServiceTable->TsLoopData[tsloop].Transport_stream_id, ServiceTable->TsLoopData[tsloop].service_id, 0); /* TODO: Define events */
                        }
                    }
                    else
                    {   
                        HsvfstSection   fstSection;
                        /* Record does not exist => Insert Fresh */
                        fstSection.Original_NetworkId         = ServiceTable->TsLoopData[tsloop].original_network_id;
                        fstSection.Transport_stream_id        = ServiceTable->TsLoopData[tsloop].Transport_stream_id;
						fstSection.ServiceId                  = ServiceTable->TsLoopData[tsloop].service_id;
                        fstSection.Default_video_PID          = ServiceTable->TsLoopData[tsloop].Default_video_PID;
                        fstSection.Default_audio_PID		  = ServiceTable->TsLoopData[tsloop].Default_audio_PID;
                        fstSection.Default_video_ECM_PID      = ServiceTable->TsLoopData[tsloop].Default_video_ECM_PID;
                        fstSection.Default_audio_ECM_PID      = ServiceTable->TsLoopData[tsloop].Default_audio_ECM_PID;
                        fstSection.Default_PCR_PID            = ServiceTable->TsLoopData[tsloop].Default_PCR_PID ;
                        

                        AssignServiceDescriptor(ServiceTable,tsloop, i, &fstSection);
						
					
                        
                        //PrintfNotice("PopulatefstSection::LINE:%d ServiceTable->original_network_id:%d, ServiceTable->TsLoopData[tsloop].service_id:%d,tableid:%d\n\n",__LINE__,ServiceTable->original_network_id, ServiceTable->TsLoopData[tsloop].service_id,tableid);
                        if( srtdb_Insert( tableid, ServiceTable->TsLoopData[tsloop].original_network_id,  ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id,0, (Address)(&fstSection)) )
                        {                    
                            srtdb_SearchOnKey(tableid, ServiceTable->TsLoopData[tsloop].original_network_id, fstSection.Transport_stream_id,fstSection.ServiceId ,0, (int *)&index);
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), Ppty, fstSection.Original_NetworkId,fstSection.Transport_stream_id , fstSection.ServiceId);
                        }
                        else
                        {
                            PrintfNotice("PopulatefstSection:: srtdb_Insert failed,ServiceTable->original_network_id:%d, ServiceTable->TsLoopDataNum[tsloop].service_id:%d\n\n", ServiceTable->TsLoopData[tsloop].Transport_stream_id,ServiceTable->TsLoopData[tsloop].service_id);
                        }
                    }
                }
			}/*end of for loop */
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
                    if(DbaseVersion.VersionNo != DmxROMData[dmx].FstVer)
                    {

                        /* delete the record */
						
                        if (srtdb_Delete(tableid, DbaseVersion.Original_NetworkId,DbaseVersion.Transport_stream_id, DbaseVersion.ServiceId, 0))
                        {  
                            DP(("Version Number Mismatch Hence Delete is Done\n\n"));
                            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), Ppty, DbaseVersion.Original_NetworkId,DbaseVersion.Transport_stream_id, DbaseVersion.ServiceId);
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
        }
	 tsloop++;
    }		
    return retval;
}



void CHsvDvbFST_Priv::AssignServiceDescriptor(Typefst_parser *ServiceTable, int tsloop, int i, HsvfstSection *DbaseVersion)
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




/*************************IHsvStream Implementation *******************************/


int CHsvDvbFST_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;

	UNUSED (inst);
    switch (prop)
    {
       
        case HSVSPID(ActualTSService, dvb, fst):
            retval = srtdb_GetNoOfRecords(srtdbids_FstTable); 
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}


Bool CHsvDvbFST_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(ActualTSService, dvb, fst):
            retval = srtdb_SearchOnKey(srtdbids_FstTable, key1, key2, key3, 0,(int *)&index);
            break;
        
      	default:
            ASSERT(FALSE);
            break;
    }		
    return retval;
}

Bool CHsvDvbFST_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
	switch(prop)
	{
		
		case HSVSPID(ActualTSService, dvb, fst):
			retval = srtdb_QueryOnKey(srtdbids_FstTable, key1, key2, key3, 0,(Address)val);
			break;
		
		default:
			ASSERT(!"Unknown Property");
			break;
	}
    
    return retval;
}

Bool CHsvDvbFST_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(ActualTSService, dvb, fst):
            retval = srtdb_QueryOnIndex(srtdbids_FstTable, index, (Address)val);
            break;
		default:
            ASSERT(FALSE);
            break;
    }		
    return retval;
}

Bool CHsvDvbFST_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool        retval = FALSE;    


    UNUSED( value );

    switch(filterid)
    {
      
        //case HsvfstId:
            {                
            }
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */
/*************************************************************/
void CHsvDvbFST_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
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





Bool CHsvDvbFST_Priv::Fst_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    Typefst_parser  fst_parser;
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
   fst_parser.TsLoopDataNum=0;
    fst_parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    fst_parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    fst_parser.NetworkId = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    fst_parser.VersionNo = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    ptr += 8;
    tableLen = tableLen - 8;
    v32 = GET32( 0);
    while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
    {
		fst_parser.TsLoopData[tsloopIndex].ServiceDescNum=0;
        fst_parser.TsLoopData[tsloopIndex].original_network_id = GETNBITS(v32, 0,16);
        fst_parser.TsLoopData[tsloopIndex].Transport_stream_id = GETNBITS(v32, 16,16);
        v32 = GET32( 4);
        fst_parser.TsLoopData[tsloopIndex].service_id = GETNBITS(v32, 0,16);
        fst_parser.TsLoopData[tsloopIndex].Default_video_PID = GETNBITS(v32, 16,16);
        v32 = GET32( 8);
        fst_parser.TsLoopData[tsloopIndex].Default_audio_PID = GETNBITS(v32, 0,16);
        fst_parser.TsLoopData[tsloopIndex].Default_video_ECM_PID = GETNBITS(v32, 16,16);
        v32 = GET32( 12);
        fst_parser.TsLoopData[tsloopIndex].Default_audio_ECM_PID = GETNBITS(v32, 0,16);
        fst_parser.TsLoopData[tsloopIndex].Default_PCR_PID = GETNBITS(v32, 16,16);
        v32 = GET32( 16);
        fst_parser.TsLoopData[tsloopIndex].reserved4 = GETNBITS(v32, 0,4);
        fst_parser.TsLoopData[tsloopIndex].Descriptor_loop_length = GETNBITS(v32, 4,12);
        ptr += 18;
        tableLen = tableLen - 18;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < fst_parser.TsLoopData[tsloopIndex].Descriptor_loop_length)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8); 
            descLen = GETNBITS(v32,8, 8); 
            switch(descTag) {
            case 0x48:
            if(fst_parser.TsLoopData[tsloopIndex].ServiceDescNum<100)
            {
                 fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceType = GETNBITS(v32, 16,8);
                 fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = GETNBITS(v32, 24,8);
                     descLoopLen = HSV_PARSER_MIN(80,fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen); 
                     ptr += 4;
                     memcpy(fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderName,ptr,descLoopLen);
                     ptr += fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen;
                     v32 = GET32( 0);
                     fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ProviderNameLen = descLoopLen;
                 fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = GETNBITS(v32, 0,8);
                     descLoopLen = HSV_PARSER_MIN(80,fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen); 
                     ptr += 1;
                     memcpy(fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceName,ptr,descLoopLen);
                     ptr += fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen;
                     v32 = GET32( 0);
                     fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].ServiceNameLen = descLoopLen;
                 fst_parser.TsLoopData[tsloopIndex].Service_Descriptor[fst_parser.TsLoopData[tsloopIndex].ServiceDescNum].DescriptorValid = TRUE;
                 fst_parser.TsLoopData[tsloopIndex].ServiceDescNum++;
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
    fst_parser.TsLoopDataNum = tsloopIndex;
	ipop_PopulateFST(demux,(Address) &fst_parser,sec_SctArrived );
    tsloopIndex = 0;
    }//endwhile tsloop
	if(code & sec_TableCompleted)
	{
		ipop_PopulateFST(demux,(Address) &fst_parser,code );
	}
    dummy = GETNBITS(v32,0,32);
    return TRUE;
}//end function

void CHsvDvbFST_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
{
}

void CHsvDvbFST_Priv::dmxsecfN_OnRequestNotAllowed ()
{
}

Bool CHsvDvbFST_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}

Bool CHsvDvbFST_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
	return FALSE;
}

Bool CHsvDvbFST_Priv::strmfltr_Clear    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}

Bool CHsvDvbFST_Priv::strapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	return FALSE;
}