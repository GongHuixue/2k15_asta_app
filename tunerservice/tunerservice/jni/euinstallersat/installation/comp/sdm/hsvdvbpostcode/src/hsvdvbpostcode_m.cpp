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
#include "CHsvDvbPostcode.h"
#include <unistd.h>

TRACESYMBOL(m, "app/installer/euinstallersat/jni/installation/comp/sdm/hsvdvbpostcode")

#ifndef __cplusplus

#else

#endif

//HSVCOMPAREKEY(postcodekeyconf, Primary,    HsvFreesatPostcodeMapping, SectionNum)
/*
Nat8 CHsvDvbPostcode::postcodekeyconf_ComparePrimaryKey( Nat32 key, Address data )                      
{                                                                               
    HsvFreesatPostcodeMapping * Section   = (HsvFreesatPostcodeMapping *)data;                                    
    Nat8            RetValue     = postcodekeyconf_SmallerKey;                            
                                                                                
    if( NULL == data )                                                          
    {                                                                           
        ASSERT( "NULL pointer passed to extract and compare key ");             
    }                                                                           
    else                                                                        
    {                                                                           
        if ( key < (Nat32) Section->SectionNum )                                           
        {                                                                       
            RetValue = postcodekeyconf_BiggerKey;                                       
        }                                                                       
        else                                                                    
        {                                                                       
            if (key == (Nat32) Section->SectionNum )                                       
            {                                                                   
                RetValue = postcodekeyconf_Equal;                                        
            }                                                                   
        }                                                                       
    }                                                                           
    return RetValue;                                                            
}   
*/
//HSVCOMPAREKEY(postcodekeyconf, Secondary,  HsvFreesatPostcodeMapping, NodeIndex)

Nat8 CHsvDvbPostcode::postcodekeyconf_ComparePrimaryKey( Nat32 key, Address data )                      
{                                                                               
    HsvFreesatPostcodeMapping * Section   = (HsvFreesatPostcodeMapping *)data;                                    
    Nat8            RetValue     = postcodekeyconf_SmallerKey;                            
                                                                                
    if( NULL == data )                                                          
    {                                                                           
        ASSERT( "NULL pointer passed to extract and compare key ");             
    }                                                                           
    else                                                                        
    {                                                                           
        if ( key < (Nat32) Section->NodeIndex )                                           
        {                                                                       
            RetValue = postcodekeyconf_BiggerKey;                                       
        }                                                                       
        else                                                                    
        {                                                                       
            if (key == (Nat32) Section->NodeIndex )                                       
            {                                                                   
                RetValue = postcodekeyconf_Equal;                                        
            }                                                                   
        }                                                                       
    }                                                                           
    return RetValue;                                                            
}
/*Not used*/
HSVCOMPAREKEY(postcodekeyconf, Secondary,  HsvFreesatPostcodeMapping, NodeIndex)
HSVCOMPAREKEY(postcodekeyconf, Teritiary,  HsvFreesatPostcodeMapping, NodeIndex)
HSVCOMPAREKEY(postcodekeyconf, Quaternary, HsvFreesatPostcodeMapping, NodeIndex)


HSVCOMPAREKEY(postcoderegionkeyconf, Primary,    HsvFreesatRegionKeyMapping, RegionKey)

/*Not used*/
HSVCOMPAREKEY(postcoderegionkeyconf, Secondary,  HsvFreesatRegionKeyMapping, RegionKey)
HSVCOMPAREKEY(postcoderegionkeyconf, Teritiary,  HsvFreesatRegionKeyMapping, RegionKey)
HSVCOMPAREKEY(postcoderegionkeyconf, Quaternary, HsvFreesatRegionKeyMapping, RegionKey)

#define POSTCODE_TREE_TABLE		(0)
#define REGION_KEY_MAP_TABLE	(1)
#define FREESAT_PARSEDPOSTCODE_FILE_PATH  "/data/data/org.droidtv.euinstallersat/freesatpostcode.txt"
#define FREESAT_HEXADUMP_PATH "/data/data/org.droidtv.euinstallersat/freesat_1.txt"

Bool CHsvDvbPostcode::bothSubTablesCollected = FALSE;
Nat32 CHsvDvbPostcode::NodeIndex = 0;
Nat32 CHsvDvbPostcode::K = 0;
PostCodeTree_Dump CHsvDvbPostcode::postCodeDump[FREESAT_MAX_POSTCODE_TREE_SECTIONS];  
RegionKeyMap_Dump CHsvDvbPostcode::regionKeyDump[FREESAT_MAX_REGION_KEY_SECTIONS];
Nat16 CHsvDvbPostcode::CurrentLookupTableType = INVALID_LOOKUP_TABLETYPE;

void CHsvDvbPostcode::Init(void)
{

	TraceNotice(m,"Chsvdvbpostcode Init called");
	int dmx = HsvDmxMain;
	int postcodeSectionLoop = 0;
	int regionkeymapSectionLoop = 0;

	for( dmx = (int)HsvDmxMain; dmx < (int)HsvDmxLast; dmx++ )
	{
		/* Clear our structures to ensure that we dont have junk values in them*/
		DmxRomData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST;
		DmxRomData[dmx].SectionInfo = IHsvDVBSIConfig_PostcodeParsing;
		DmxRomData[dmx].TablesReq = 0;
		DmxRomData[dmx].TablesRecvd = 0;
		DmxRomData[dmx].Version = 0;
	}

	for(postcodeSectionLoop = 0;postcodeSectionLoop < FREESAT_MAX_POSTCODE_TREE_SECTIONS;postcodeSectionLoop++)
	{
		memset(&postCodeDump[postcodeSectionLoop],0x00,sizeof(postCodeDump));
	}

	for(regionkeymapSectionLoop = 0;regionkeymapSectionLoop < FREESAT_MAX_REGION_KEY_SECTIONS;regionkeymapSectionLoop++)
	{
		memset(&regionKeyDump[regionkeymapSectionLoop],0x00,sizeof(regionKeyDump));
	}

	bothSubTablesCollected = FALSE;
	NodeIndex = 0;
	CurrentLookupTableType = INVALID_LOOKUP_TABLETYPE;
	K = 0;

	
}

void CHsvDvbPostcode::TurnOn(void)
{
	/* Do Nothing */
}

void CHsvDvbPostcode::TurnOff(void)
{
	/* Do Nothing */
}

void CHsvDvbPostcode::Enable(HsvDemux dmx)
{
	HsvSDMSIDataValues SiValues;

	int postcodeSectionLoop =0;
	int regionkeymapSectionLoop =0;

	TraceNotice (m," Entering function  - %s",__FUNCTION__);
	memset(&SiValues, 0, sizeof(HsvSDMSIDataValues));
	SiValues.TableId = FREESAT_POSTCODE_TABLE_ID;

	/*get the PID details*/
	ins->GetSIDetails(&SiValues);

	/*initialize the database*/
	if(SiValues.FreesatPostCodeTableType == POSTCODE_TREE_TABLE)
	{
		InitFreesatPostcodeKeyMap(dmx);
		for(postcodeSectionLoop = 0;postcodeSectionLoop < FREESAT_MAX_POSTCODE_TREE_SECTIONS;postcodeSectionLoop++)
		{
			memset(&postCodeDump[postcodeSectionLoop],0x00,sizeof(postCodeDump));
		}
	}
	else if(SiValues.FreesatPostCodeTableType == REGION_KEY_MAP_TABLE)
	{
		InitFreesatRegionKeyMap(dmx);
		for(regionkeymapSectionLoop = 0;regionkeymapSectionLoop < FREESAT_MAX_REGION_KEY_SECTIONS;regionkeymapSectionLoop++)
		{
			memset(&regionKeyDump[regionkeymapSectionLoop],0x00,sizeof(regionKeyDump));
		}
	}
	else
	{
		InitFreesatPostcodeKeyMap(dmx);
		InitFreesatRegionKeyMap(dmx);
	}

	if (conf->IsActionAllowed(dmx, DmxRomData[dmx].SectionInfo))
	{
		#if 1
		/*request separate filter to collect poscode key map section and postcode region key map section*/
		DmxRomData[dmx].SubscrId = dmxlocal_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx),
																				SiValues.Pid,
																				FREESAT_POSTCODE_TABLE_ID,
																				SiValues.FreesatPostCodeTableType,
																				(int)SiValues.FreesatPostCodeTableType,
																				FNADDR(Postcode_Parser));
		TraceNotice (m,"Postcode Requested for postcode key table, PID  %d subscriber id %d",SiValues.Pid,DmxRomData[dmx].SubscrId);
		DmxRomData[dmx].TablesReq |= (1 << SiValues.FreesatPostCodeTableType);
		#endif
	}

}


void CHsvDvbPostcode::Disable(HsvDemux dmx)
{
	TraceNotice (m," Entering function  - %s bothSubTablesCollected %d",__FUNCTION__,bothSubTablesCollected);
	/*initialize the database*/
	if(bothSubTablesCollected)
	{
		InitFreesatPostcodeKeyMap(dmx);
		InitFreesatRegionKeyMap(dmx);
		CurrentLookupTableType = INVALID_LOOKUP_TABLETYPE;
		bothSubTablesCollected = FALSE;
	}

    /* Initialise Sections */
	if(conf->IsActionAllowed(dmx, DmxRomData[dmx].SectionInfo))
	{
		if(HSV_INVALID_SCT_REQUEST != DmxRomData[dmx].SubscrId)
		{
			dmxlocal_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxRomData[dmx].SubscrId);
			DmxRomData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST ;
		}
	}
}

void CHsvDvbPostcode::Sync(HsvDemux dmx)
{
	UNUSED( dmx );
}

void CHsvDvbPostcode::InitFreesatPostcodeKeyMap(HsvDemux dmx)
{
	TraceNotice (m," Entering function  - %s",__FUNCTION__);
	srtdb->Init(srtdbids_PostcodeFreesatPostcodeKeyMap);
}

void CHsvDvbPostcode::InitFreesatRegionKeyMap(HsvDemux dmx)
{
	TraceNotice (m," Entering function  - %s",__FUNCTION__);
	srtdb->Init(srtdbids_PostcodeFreesatRegionKeyMap);
}

Bool CHsvDvbPostcode::ipop_PopulatePostcode ( HsvDemux dmx ,int code )
{
	Bool retval = TRUE;
	

	TraceNotice (m," Entering function  - %s",__FUNCTION__);
	if(POSTCODE_TREE_TABLE == CurrentLookupTableType)
	{
		mPopulatePostcodeTreeTable(dmx,code);
	}
	else if(REGION_KEY_MAP_TABLE == CurrentLookupTableType)
	{
		mPopulateRegionKeyTable(dmx,code);
	}

	if((IHsvDemuxSectionFilter2_TableCompleted & code) && (DmxRomData[dmx].TablesRecvd  == DmxRomData[dmx].TablesReq))
	{
		DmxRomData[dmx].TablesReq = 0;
		DmxRomData[dmx].TablesRecvd = 0;
		ctrlN->OnEvent( dmx,IHsvSdmControlNotifyEx_DataAvailable,IHsvSdmControlNotifyEx_Postcode);

		/* The below check has to be changed to by adding a static variable for tablerecvied == 3*/
		if(REGION_KEY_MAP_TABLE == CurrentLookupTableType)
		{
			TraceNotice(m,"Both tables collected");
			bothSubTablesCollected = TRUE;
		}
		
	}
	return retval;
}

void CHsvDvbPostcode::mPopulatePostcodeTreeTable( HsvDemux dmx ,int code)
{	
	Nat32 LoopCount = 0;
	Nat32 LoopIndex = 0;
	Nat32 Loop1Index = 0;
	
	register Nat8 *ptr = mConcatPostCode.mConcatPostCodeDump;
	register int v32=0;
	int tableLen = mConcatPostCode.totalPostCodeLen;
	int childcount = 0;

	NodeIndex = 0;
	int i=0,j=0;
	HsvFreesatPostcodeMapping DatabaseVersion;
	HsvFreesatPostcodeMapping CurrentVersion;
	FILE*	fp = NULL;
	fp = fopen(FREESAT_PARSEDPOSTCODE_FILE_PATH, "w");

	TraceNotice (m," Entering function  - %s code %d tablen %d NodeIndex",__FUNCTION__,code,tableLen);
	if(IHsvDemuxSectionFilter2_SctArrived & code)
	{
 
		v32 = GET32(0);
		while(LoopCount < tableLen)
		{
			v32 = GET32(0);
			
			/*First loop provides information about child count so initialize all second loop variables to zero*/
			
			CurrentVersion.ChildCount = GETNBITS(v32,0,8);
			childcount = CurrentVersion.ChildCount;
			CurrentVersion.NodeIndex = NodeIndex;
			CurrentVersion.RegionKey = 0;
			CurrentVersion.NextWordOffset = 0;
			CurrentVersion.PostcodeChar = 0;
			CurrentVersion.IsLeafNode = 0;
			NodeIndex ++;
			
			if(srtdb->QueryOnKey( srtdbids_PostcodeFreesatPostcodeKeyMap,CurrentVersion.NodeIndex, 0,0,0, (Address)(&DatabaseVersion)))
			{
				TraceNotice(m,"%d Node Index:%d childcount %d",__LINE__,CurrentVersion.NodeIndex,CurrentVersion.ChildCount);
				srtdb->Update(srtdbids_PostcodeFreesatPostcodeKeyMap,CurrentVersion.NodeIndex,0,0,0, (Address)(&CurrentVersion) );
				strapiN->OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatPostcodeKey, dvb, postcode),CurrentVersion.NodeIndex,0, 0,0);
			}
			else
			{
				TraceNotice(m,"%d Node Index:%d childcount %d",__LINE__,CurrentVersion.NodeIndex,CurrentVersion.ChildCount);
				srtdb->Insert( srtdbids_PostcodeFreesatPostcodeKeyMap,CurrentVersion.NodeIndex, 0, 0,0, (Address)(&CurrentVersion));
				strapiN->OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatPostcodeKey, dvb, postcode),CurrentVersion.NodeIndex,0, 0);
			}
			ptr += 3;
			LoopCount += 3;
			Loop1Index = 0;
		
			 
			while((Loop1Index < FREESAT_MAX_CHILD_PER_NODE) && (Loop1Index < childcount))
			{
				v32 = GET32(0);
				/*Second loop provides information about region key or next word offset, so set child count to zero*/
				 				
				CurrentVersion.IsLeafNode = GETNBITS(v32,0,1);
				CurrentVersion.PostcodeChar = GETNBITS(v32,1,7);
				if(CurrentVersion.IsLeafNode)
				{
					CurrentVersion.RegionKey = GETNBITS(v32,8,16);
					CurrentVersion.NextWordOffset = 0;
				}
				else
				{
					CurrentVersion.RegionKey = 0;
					CurrentVersion.NextWordOffset = GETNBITS(v32,8,16);
				}
				
				CurrentVersion.ChildCount = 0;
				CurrentVersion.NodeIndex = NodeIndex;
				NodeIndex ++;

				
				if(srtdb->QueryOnKey( srtdbids_PostcodeFreesatPostcodeKeyMap,CurrentVersion.NodeIndex,0,0,0, (Address)(&DatabaseVersion)))
				{
					TraceNotice(m,"%d Node Index:%d ",__LINE__,CurrentVersion.NodeIndex);
					srtdb->Update(srtdbids_PostcodeFreesatPostcodeKeyMap,CurrentVersion.NodeIndex, 0, 0, 0, (Address)(&CurrentVersion) );
					strapiN->OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatPostcodeKey, dvb, postcode),CurrentVersion.NodeIndex, 0,0,0);
				}
				else
				{
					TraceNotice(m,"%d Node Index:%d ",__LINE__,CurrentVersion.NodeIndex);
					srtdb->Insert( srtdbids_PostcodeFreesatPostcodeKeyMap,CurrentVersion.NodeIndex,0,0,0, (Address)(&CurrentVersion));
					strapiN->OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatPostcodeKey, dvb, postcode), CurrentVersion.NodeIndex,0,0);
				}

			
				ptr += 3;
				LoopCount += 3;
				Loop1Index ++;
			}
			 
		}
	}

#if 0
	if(fp != NULL)
	{
		fprintf(fp,"NodeIndex ChildCount IsleafNode PostCodeChar RegionKey OffsetWord\n");
		while((i < PostcodeTable->PostcodeMapping_num))
		{
			fprintf(fp,"[%-7d] [%-8d] [0       ] [0         ] [0      ] [0       ]\n",K,PostcodeTable->PostcodeMapping[i].ChildCount);
			K++;
			j=0;
			while((j < PostcodeTable->PostcodeMapping_num) && (j < FREESAT_MAX_CHILD_PER_NODE) 
				&& (j < PostcodeTable->PostcodeMapping[i].ChildCount))
			{
				fprintf(fp,"[%-7d] [0       ] [%-8d] [%-10c] [%-7d] [%-8d]\n",K,PostcodeTable->PostcodeMapping[i].PostcodeKey[j].IsLeafNode,PostcodeTable->PostcodeMapping[i].PostcodeKey[j].PostcodeChar,
					PostcodeTable->PostcodeMapping[i].PostcodeKey[j].RegionKey,PostcodeTable->PostcodeMapping[i].PostcodeKey[j].NextWordOffset);
				K++;
				j++;
			}
			i++;
			
		}
		fclose (fp);
	}
	else
	{
		TraceNotice(m,"%s Error in File opening",__FUNCTION__);
	}
#endif
	
	if(IHsvDemuxSectionFilter2_TableCompleted & code)
	{
		
		DmxRomData[dmx].TablesRecvd |= (1 << FREESAT_POSTCODE_KEY_MAP_TABLE);
		strapiN->OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatPostcodeKey, dvb, postcode));
		TraceNotice(m,"Table Completed For FREESAT_POSTCODE_KEY_MAP_TABLE table recvd %d",DmxRomData[dmx].TablesRecvd);
		
	}


}
void CHsvDvbPostcode::mPopulateRegionKeyTable( HsvDemux dmx ,int code)
{

	
	Nat32 LoopCount = 0;

	register Nat8 *ptr = mConcatRegionKeyMap.mConcatRegionKeyMapDump;
	register int v32=0;
	int tableLen = mConcatRegionKeyMap.totalRegionKeyMapLen;
	

	v32 = GET32(0);

	TraceNotice (m," Entering function  - %s tableLen %d Code %d",__FUNCTION__,tableLen,code);

	HsvFreesatRegionKeyMapping DatabaseVersion;
	HsvFreesatRegionKeyMapping CurrentVersion;
	
	if(IHsvDemuxSectionFilter2_SctArrived & code)
	{
		while(LoopCount < tableLen)
		{
			
			v32 = GET32(0);
			
			CurrentVersion.RegionKey = GETNBITS(v32,0,16);
			CurrentVersion.SDBouquetId = GETNBITS(v32,16,16);

			LoopCount += 4;
			ptr += 4;
			v32 = GET32(0);

			CurrentVersion.SDRegionId = GETNBITS(v32,0,16);
			CurrentVersion.HDBouquetId = GETNBITS(v32,16,16);

			LoopCount += 4;
			ptr += 4;
			v32 = GET32(0);

			CurrentVersion.HDRegionId = GETNBITS(v32,0,16);

			LoopCount += 2;
			ptr += 2;

			
			if(srtdb->QueryOnKey( srtdbids_PostcodeFreesatRegionKeyMap, CurrentVersion.RegionKey, 0, 0,0, (Address)(&DatabaseVersion)))
			{
				TraceNotice(m,"Updating Region Key : %d HDBid %d HDRid %d",CurrentVersion.RegionKey,CurrentVersion.HDBouquetId,CurrentVersion.HDRegionId);
				srtdb->Update(srtdbids_PostcodeFreesatRegionKeyMap, CurrentVersion.RegionKey, 0, 0, 0, (Address)(&CurrentVersion) );
				strapiN->OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatRegionKey, dvb, postcode), CurrentVersion.RegionKey, 0, 0,0);
			}
			else
			{
				TraceNotice(m,"Inserting Region Key : %d HDBid %d HDRid %d",CurrentVersion.RegionKey,CurrentVersion.HDBouquetId,CurrentVersion.HDRegionId);
				srtdb->Insert( srtdbids_PostcodeFreesatRegionKeyMap, CurrentVersion.RegionKey, 0, 0, 0, (Address)(&CurrentVersion));
				strapiN->OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatRegionKey, dvb, postcode), CurrentVersion.RegionKey, 0, 0);
			}
		
		}
	}
	if(IHsvDemuxSectionFilter2_TableCompleted & code)
	{
		
		DmxRomData[dmx].TablesRecvd |= (1 << FREESAT_REGION_KEY_MAP_TABLE);
		TraceNotice(m,"Table Completed For FREESAT_REGION_KEY_MAP_TABLE table recvd %d",DmxRomData[dmx].TablesRecvd);
		//mDispatchPostCodeTableCompleted(dmx);
		strapiN->OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatRegionKey, dvb, postcode));
	}
}

Bool CHsvDvbPostcode::Postcode_Parser( HsvDestination dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
	register Nat8 *ptr = mBuffer;
	register int v32=0;
	HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
	Bool retval = TRUE;
	int tableLen = 0;
	int dummy = 0;
	int TableId,LookupTableType,VersionNo,SectionNumber,SectionLen,LastSectionNumber;
	Nat32 LoopCount = 0;
	Nat32 LoopIndex = 0;
	Nat32 Loop1Index = 0;
	Nat8 dumpByte;
	TraceNotice (m," Entering function  - %s code 0x%x",__FUNCTION__, code);
	createDump(PrimarySectionStartAddress);
	if (secondarySectionSize > 0)
	{
		memcpy(ptr, PrimarySectionStartAddress, primarySectionSize);
		memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
	}
	else
	{
	      ptr = PrimarySectionStartAddress;
	}

	tableLen = HSV_GETSECTION_LENGTH(ptr);

	v32 = GET32(0);

	TableId = GETNBITS(v32,0,8);
	dummy = GETNBITS(v32,8,1);
	dummy = GETNBITS(v32,9,1);
	dummy = GETNBITS(v32,10,2);
	SectionLen = GETNBITS(v32,12,12);
	v32 = GET32( 3);
	LookupTableType = GETNBITS(v32,0,16);
	dummy = GETNBITS(v32,16,2);
	VersionNo = GETNBITS(v32,18,5);
	dummy = GETNBITS(v32,23,1);
	SectionNumber = GETNBITS(v32,24,8);
	v32 = GET32( 7);
	LastSectionNumber = GETNBITS(v32,0,8);
	TraceNotice (m," Postcode table version number %d Lockuptable type %d SectionNumber %d",VersionNo,LookupTableType,SectionNumber);
	ptr += 8;
	tableLen = tableLen - 8;
	v32 = GET32( 0);

	//Postcode_Parser.PostcodeMapping_num = 0;
	//Postcode_Parser.RegionKeyMapping_num = 0;

	
		if((FREESAT_POSTCODE_KEY_MAP_TABLE == LookupTableType) && (SectionNumber < FREESAT_MAX_POSTCODE_TREE_SECTIONS))
		{
			postCodeDump[SectionNumber].TableId = TableId;
			postCodeDump[SectionNumber].SectionLen = SectionLen;
			postCodeDump[SectionNumber].VersionNo = VersionNo;
			postCodeDump[SectionNumber].SectionNumberIndex = SectionNumber;
			postCodeDump[SectionNumber].LastSectionNumber = LastSectionNumber;
			postCodeDump[SectionNumber].PostCodeTreeLen = (tableLen - 4);
			while(LoopCount < (postCodeDump[SectionNumber].PostCodeTreeLen))
			{
				v32 = GET32(0);
				dumpByte = GETNBITS(v32,0,8);
				//TraceNotice(m,"0x%x  ",dumpByte);
				postCodeDump[SectionNumber].PostCodeTreeDump[LoopCount] = dumpByte;
				ptr = ptr + 1;
				LoopCount = LoopCount + 1;
			}
		}
		else if((FREESAT_REGION_KEY_MAP_TABLE == LookupTableType) && (SectionNumber < FREESAT_MAX_REGION_KEY_SECTIONS))
		{
			regionKeyDump[SectionNumber].TableId = TableId;
			regionKeyDump[SectionNumber].SectionLen = SectionLen;
			regionKeyDump[SectionNumber].VersionNo = VersionNo;
			regionKeyDump[SectionNumber].SectionNumberIndex = SectionNumber;
			regionKeyDump[SectionNumber].LastSectionNumber = LastSectionNumber;
			regionKeyDump[SectionNumber].RegionKeyMapLen = (tableLen - 4);
			while(LoopCount < (regionKeyDump[SectionNumber].RegionKeyMapLen))
			{
				v32 = GET32(0);
				dumpByte = GETNBITS(v32,0,8);
				//TraceNotice(m,"0x%x  ",dumpByte);
				regionKeyDump[SectionNumber].regionKeyMapDump[LoopCount] = dumpByte;
				ptr = ptr + 1;
				LoopCount = LoopCount + 1;
			}
		}


	//TraceNotice(m,"subscrib id %d",DmxRomData[demux].SubscrId);
	//startRequestForRegionKeyTable(code,demux);
	
	if(IHsvDemuxSectionFilter2_TableCompleted & code)
	{
		if(LookupTableType == 0)
		{
			concatPostCodeTree();
			CurrentLookupTableType = 0;
		}
		else if(LookupTableType == 1)
		{
			concatRegionKeyMapTree();
			CurrentLookupTableType = 1;
		}
		ipop_PopulatePostcode(demux,code);
		TraceNotice(m,"%s Code %d ",__FUNCTION__,code);
		
	}	
	TraceNotice (m," Exiting function Freesat - %s",__FUNCTION__);
	return retval;
}

void CHsvDvbPostcode::concatPostCodeTree()
{
	Nat32 SectionCount = 0;
	Nat32 OuterLoopIndex = 0;
	Nat32 InnerLoopIndex = 0;
	mConcatPostCode.totalPostCodeLen = 0;
	
	while(SectionCount <= postCodeDump[SectionCount].LastSectionNumber)
	{
		
		InnerLoopIndex = 0;
		mConcatPostCode.totalPostCodeLen += postCodeDump[SectionCount].PostCodeTreeLen;

		TraceNotice(m,"%s currentsection %d LastSectionNumber %d currentpostcodelen %d OuterLoopIndex %d totalpostcodeLen %d",__FUNCTION__,SectionCount,postCodeDump[SectionCount].LastSectionNumber,postCodeDump[SectionCount].PostCodeTreeLen,OuterLoopIndex,mConcatPostCode.totalPostCodeLen);
		while(OuterLoopIndex < mConcatPostCode.totalPostCodeLen)
		{
			mConcatPostCode.mConcatPostCodeDump[OuterLoopIndex] = postCodeDump[SectionCount].PostCodeTreeDump[InnerLoopIndex];
			
			InnerLoopIndex++;
			OuterLoopIndex++;
		}
		SectionCount++;
	}
}

void CHsvDvbPostcode::concatRegionKeyMapTree()
{
	Nat32 SectionCount = 0;
	Nat32 OuterLoopIndex = 0;
	Nat32 InnerLoopIndex = 0;
	mConcatRegionKeyMap.totalRegionKeyMapLen = 0;
	
	while(SectionCount <= regionKeyDump[SectionCount].LastSectionNumber)
	{
		TraceNotice(m,"%s currentsection %d LastSectionNumber %d currentregionKeyMaplen %d",__FUNCTION__,SectionCount,regionKeyDump[SectionCount].LastSectionNumber,regionKeyDump[SectionCount].RegionKeyMapLen);
		InnerLoopIndex = 0;
		mConcatRegionKeyMap.totalRegionKeyMapLen += regionKeyDump[SectionCount].RegionKeyMapLen;
		while(OuterLoopIndex < mConcatRegionKeyMap.totalRegionKeyMapLen)
		{
			mConcatRegionKeyMap.mConcatRegionKeyMapDump[OuterLoopIndex] = regionKeyDump[SectionCount].regionKeyMapDump[InnerLoopIndex];
			InnerLoopIndex++;
			OuterLoopIndex++;
		}
		SectionCount++;
		
	}
}


void CHsvDvbPostcode::createDump(Nat8 * PrimarySectionStartAddress)
{
	register Nat8 *ptr = mBuffer;
	register int v32=0;
	Nat8 dumpByte;
	int loop1,loop2;
	int LookupTableType,dummy,VersionNo,SectionNumber;
	int tableLen = 0;
	FILE*	fp = NULL;
	
	ptr = PrimarySectionStartAddress;
	tableLen = HSV_GETSECTION_LENGTH(ptr);

	ptr += 3;

	v32 = GET32(0);
	LookupTableType = GETNBITS(v32,0,16);
	dummy = GETNBITS(v32,16,2);
	VersionNo = GETNBITS(v32,18,5);
	dummy = GETNBITS(v32,23,1);
	SectionNumber = GETNBITS(v32,24,8);

	TraceNotice(m,"LookupTableType %d Version %d SectionNum %d",LookupTableType,VersionNo,SectionNumber);
	
	ptr += 5;

	tableLen = tableLen - 8;

	if(LookupTableType == 0)
	{
		if(SectionNumber == 0)
		{
			TraceNotice(m,"writing to file\n");
			fp = fopen(FREESAT_HEXADUMP_PATH,"w");
		}
		else
		{
			
			TraceNotice(m,"Appending to file\n");
			fp = fopen(FREESAT_HEXADUMP_PATH,"a");
		}

	
		
		TraceNotice(m,"%s %d",__FUNCTION__,__LINE__);
		if(fp != NULL)
		{
			loop2 = 0;
			loop1 = 1;
			TraceNotice(m,"%s %d tablelen %d",__FUNCTION__,__LINE__,tableLen);
			while(loop2 < (tableLen - 4))
			{
					v32 = GET32(0);
					dumpByte = GETNBITS(v32,0,8);
					//TraceNotice(m,"0x%x  ",dumpByte);
					fprintf(fp,"0x%x  ",dumpByte);
					ptr = ptr + 1;
					loop2 = loop2 + 1;
					if(loop1 == 10)
					{
						fprintf(fp,"\n");
						loop1 = 0;
					}
					loop1++;
					
			}
			/*int fd = fileno(fp);
			TraceNotice(m,"file size %d ",ftell(fp));
			fsync(fd);*/
			fclose(fp);
			
		}
		else
		{
			TraceNotice(m,"%s Error in File opening",__FUNCTION__);
		}
	}
}

#if 0
void CHsvDvbPostcode::parsePostCodeDump(HsvDemux dmx,int code)
{
	register Nat8 *ptr;
	register int v32=0;
	//HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
	TypePostcode_Parser  Postcode_Parser;
	Nat32 LoopCount = 0;
	Nat32 LoopIndex = 0;
	Nat32 Loop1Index = 0;
	int tableLen = mConcatPostCode.totalPostCodeLen;

	ptr = mConcatPostCode.mConcatPostCodeDump;

	v32 = GET32(0);

	TraceNotice(m,"%s tableLen %d",__FUNCTION__,tableLen);


	Postcode_Parser.LookupTableType = 0;
	
/*	while(LoopCount < (tableLen))
	{
			
			v32 = GET32(0);
			TraceNotice(m,"LoopCount %d LoopIndex %d",LoopCount,LoopIndex);
			Postcode_Parser.PostcodeMapping[LoopIndex].ChildCount = GETNBITS(v32,0,8);
			TraceNotice(m,"ChildCount %d",Postcode_Parser.PostcodeMapping[LoopIndex].ChildCount);
			
			ptr += 3;
			LoopCount += 3;
			Loop1Index = 0;
			while((LoopCount < tableLen) && (Loop1Index < FREESAT_MAX_CHILD_PER_NODE)
								&& (Loop1Index < Postcode_Parser.PostcodeMapping[LoopIndex].ChildCount))
			{
				v32 = GET32( 0);
				Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].IsLeafNode = GETNBITS(v32,0,1);
				Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].PostcodeChar = GETNBITS(v32,1,7);
				if(Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].IsLeafNode)
				{
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].RegionKey = GETNBITS(v32,8,16);
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].NextWordOffset = 0;
				}
				else
				{
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].RegionKey = 0;
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].NextWordOffset = GETNBITS(v32,8,16);
				}

				ptr += 3;
				LoopCount += 3;
				Loop1Index++;
			}

			LoopIndex++;
	}
	Postcode_Parser.PostcodeMapping_num = LoopIndex;*/

	ipop_PopulatePostcode(dmx, (Address)&Postcode_Parser, code);
	
}

void CHsvDvbPostcode::parseRegionKeyDump(HsvDemux dmx,int code)
{
	register Nat8 *ptr;
	register int v32=0;
	//HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
	TypePostcode_Parser  Postcode_Parser;
	Nat32 LoopCount = 0;
	Nat32 LoopIndex = 0;
	Nat32 Loop1Index = 0;
	int tableLen = mConcatRegionKeyMap.totalRegionKeyMapLen;
	
	ptr = mConcatRegionKeyMap.mConcatRegionKeyMapDump;

	v32 = GET32(0);

	TraceNotice(m,"%s tableLen %d",__FUNCTION__,tableLen);


	Postcode_Parser.LookupTableType = 1;
	while((LoopCount < (tableLen))  && (LoopIndex < FREESAT_MAX_REGION_KEY_PER_SECTION))
	{
			v32 = GET32(0);
			Postcode_Parser.RegionKeyMapping[LoopIndex].RegionKey = GETNBITS(v32,0,16);
			Postcode_Parser.RegionKeyMapping[LoopIndex].SDBouquetId = GETNBITS(v32,16,16);
			LoopCount += 4;
			ptr += 4;
			v32 = GET32(0);
			Postcode_Parser.RegionKeyMapping[LoopIndex].SDRegionId = GETNBITS(v32,0,16);
			Postcode_Parser.RegionKeyMapping[LoopIndex].HDBouquetId = GETNBITS(v32,16,16);
			LoopCount += 4;
			ptr += 4;
			v32 = GET32(0);
			Postcode_Parser.RegionKeyMapping[LoopIndex].HDRegionId = GETNBITS(v32,0,16);
			LoopCount += 2;
			ptr += 2;
			TraceNotice(m,"Region Key %d HD RegionId : %d HD Bqid: %d",Postcode_Parser.RegionKeyMapping[LoopIndex].RegionKey,Postcode_Parser.RegionKeyMapping[LoopIndex].HDRegionId,Postcode_Parser.RegionKeyMapping[LoopIndex].HDBouquetId);
			LoopIndex ++;
			
	}

	Postcode_Parser.RegionKeyMapping_num = LoopIndex;

	ipop_PopulatePostcode(dmx, (Address)&Postcode_Parser, code);
}


{
/*post code tree table logice:
	while((LoopCount < (tableLen - 4))  && (LoopIndex < FREESAT_MAX_CHILD_LOOP_PER_SECTION))
	{
			
			v32 = GET32( 0);
			Postcode_Parser.PostcodeMapping[LoopIndex].ChildCount = GETNBITS(v32,0,8);
			TraceNotice(m,"0x%x",Postcode_Parser.PostcodeMapping[LoopIndex].ChildCount);
			dummy = GETNBITS(v32,8,8);
			TraceNotice(m,"0x%x",dummy);
			dummy = GETNBITS(v32,16,8);
			ptr += 3;
			LoopCount += 3;
			Loop1Index = 0;
			while((LoopCount < (tableLen - 4)) && (Loop1Index < FREESAT_MAX_CHILD_PER_NODE)
								&& (Loop1Index < Postcode_Parser.PostcodeMapping[LoopIndex].ChildCount))
			{
				v32 = GET32( 0);
				Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].IsLeafNode = GETNBITS(v32,0,1);
				Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].PostcodeChar = GETNBITS(v32,1,7);
				if(Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].IsLeafNode)
				{
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].RegionKey = GETNBITS(v32,8,16);
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].NextWordOffset = 0;
				}
				else
				{
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].RegionKey = 0;
					Postcode_Parser.PostcodeMapping[LoopIndex].PostcodeKey[Loop1Index].NextWordOffset = GETNBITS(v32,8,16);
				}

				ptr += 3;
				LoopCount += 3;
				Loop1Index++;
			}

			LoopIndex++;
	}

		Postcode_Parser.PostcodeMapping_num = LoopIndex;
}

/*region key map table logic */

while((LoopCount < (tableLen - 4))  && (LoopIndex < FREESAT_MAX_REGION_KEY_PER_SECTION))
		{
			v32 = GET32(LoopCount);
			Postcode_Parser.RegionKeyMapping[LoopIndex].RegionKey = GETNBITS(v32,0,16);
			Postcode_Parser.RegionKeyMapping[LoopIndex].SDBouquetId = GETNBITS(v32,16,16);
			LoopCount += 4;
			v32 = GET32(LoopCount);
			Postcode_Parser.RegionKeyMapping[LoopIndex].SDRegionId = GETNBITS(v32,0,16);
			Postcode_Parser.RegionKeyMapping[LoopIndex].HDBouquetId = GETNBITS(v32,16,16);
			LoopCount += 4;
			v32 = GET32(LoopCount);
			Postcode_Parser.RegionKeyMapping[LoopIndex].HDRegionId = GETNBITS(v32,0,16);
			LoopCount += 2;
			TraceNotice(m,"Region Key %d HD RegionId : %d HD Bqid: %d",Postcode_Parser.RegionKeyMapping[LoopIndex].RegionKey,Postcode_Parser.RegionKeyMapping[LoopIndex].HDRegionId,Postcode_Parser.RegionKeyMapping[LoopIndex].HDBouquetId);
			LoopIndex ++;
			
		}
		ptr += LoopCount;
		Postcode_Parser.RegionKeyMapping_num = LoopIndex;

void CHsvDvbPostcode::startRequestForRegionKeyTable(int code,HsvDemux dmx)
{
	HsvSDMSIDataValues SiValues;

	TraceNotice (m," Entering function  - %s code %d",__FUNCTION__,code);
	memset(&SiValues, 0, sizeof(HsvSDMSIDataValues));
	SiValues.TableId = FREESAT_POSTCODE_TABLE_ID;

	/*get the PID details*/
	ins->GetSIDetails(&SiValues);
	if(IHsvDemuxSectionFilter2_TableCompleted & code)
	{
		InitFreesatRegionKeyMap(dmx);
		TraceNotice(m,"subscrib id state %d line %d",DmxRomData[dmx].SubscrId,__LINE__);
		if(HSV_INVALID_SCT_REQUEST != DmxRomData[dmx].SubscrId)
		{

			TraceNotice(m,"Cancelled Section\n");
			dmxlocal_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxRomData[dmx].SubscrId);
			DmxRomData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST ;
			
		}
		TraceNotice(m,"SiValues.Pid %d subscrib id state %d line %d",SiValues.Pid,DmxRomData[dmx].SubscrId,__LINE__);
		if(HSV_INVALID_SCT_REQUEST == DmxRomData[dmx].SubscrId)
		{
			DmxRomData[dmx].SubscrId = dmxlocal_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx),
																				SiValues.Pid,
																				FREESAT_POSTCODE_TABLE_ID,
																				(Nat16)FREESAT_REGION_KEY_MAP_TABLE,
																				0,
																				FNADDR(Postcode_Parser));
			TraceNotice (m,"Postcode Requested for region key table, PID %d",SiValues.Pid);
			DmxRomData[dmx].TablesReq |= (1 << FREESAT_REGION_KEY_MAP_TABLE);
		}
		
	}	
}
#endif
int CHsvDvbPostcode::GetSize   (HsvDestination inst, int prop)
{
	int retval = 0;

	UNUSED (inst);
	switch (prop)
	{
	case HSVSPID(FreesatPostcodeKey, dvb, postcode):
		retval = srtdb->GetNoOfRecords(srtdbids_PostcodeFreesatPostcodeKeyMap);
		break;
	case HSVSPID(FreesatRegionKey, dvb, postcode):
		retval = srtdb->GetNoOfRecords(srtdbids_PostcodeFreesatRegionKeyMap);
		break;
	default:
		break;
	}
	return retval;
}

Bool CHsvDvbPostcode::GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
	Bool retval = FALSE;
	UNUSED (inst);
	switch (prop)
	{
	case HSVSPID(FreesatPostcodeKey, dvb, postcode):
		retval = srtdb->SearchOnKey(srtdbids_PostcodeFreesatPostcodeKeyMap, key1, key2, key3,0, (int *)&index);
		break;
	case HSVSPID(FreesatRegionKey, dvb, postcode):
		retval = srtdb->SearchOnKey(srtdbids_PostcodeFreesatRegionKeyMap, key1, key2, key3,0, (int *)&index);
		break;
	default:
		break;
	}
	return retval;
}

Bool CHsvDvbPostcode::GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
	Bool retval = FALSE;
	UNUSED (inst);
	switch (prop)
	{
	case HSVSPID(FreesatPostcodeKey, dvb, postcode):
		retval = srtdb->QueryOnKey(srtdbids_PostcodeFreesatPostcodeKeyMap, key1, key2, key3, 0,(Address)val);
		break;
	case HSVSPID(FreesatRegionKey, dvb, postcode):
		retval = srtdb->QueryOnKey(srtdbids_PostcodeFreesatRegionKeyMap, key1, key2, key3, 0,(Address)val);
		break;
	default:
		break;
	}
	return retval;
}

Bool CHsvDvbPostcode::GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
	TraceNotice(m,"Entering %s",__FUNCTION__);
	Bool retval = FALSE;
	UNUSED (inst);
	switch (prop)
	{
	case HSVSPID(FreesatPostcodeKey, dvb, postcode):
		TraceNotice(m,"INDEX %d %s",index,__FUNCTION__);
		retval = srtdb->QueryOnIndex(srtdbids_PostcodeFreesatPostcodeKeyMap, index, (Address)val);
		break;
	case HSVSPID(FreesatRegionKey, dvb, postcode):
		TraceNotice(m,"INDEX %d %s",index,__FUNCTION__);
		retval = srtdb->QueryOnIndex(srtdbids_PostcodeFreesatRegionKeyMap, index, (Address)val);
		break;
	default:
		break;
	}
	return retval;
}

 Bool CHsvDvbPostcode::GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to)
{
	Bool retval = FALSE;
	return retval;
}


Bool CHsvDvbPostcode::Set(HsvDestination dest, int filterid, int value)
{
	Bool retval = FALSE;
	UNUSED (dest);
	UNUSED (value);

	return retval;
}/* End of function strmfltr_Set() */

/*void CHsvDvbPostcode::mDispatchPostCodeTableCompleted(int dmx)
{
	if(DmxRomData[dmx].TablesRecvd == 0x03)
	{
		strapiN->OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatPostcodeKey, dvb, postcode));
		strapiN->OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatRegionKey, dvb, postcode));
	}
}*/
	
Bool CHsvDvbPostcode::IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}
Bool CHsvDvbPostcode::IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
	return FALSE;
}
Bool CHsvDvbPostcode::Clear    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}
/*************************************************************/
void CHsvDvbPostcode::OnRequestCancelled( Nat32 subscrid )
{
}

void CHsvDvbPostcode::OnRequestAllowed( HsvDestination dest )
{
}

void CHsvDvbPostcode::OnRequestNotAllowed ()
{
}

CHsvDvbPostcode::~CHsvDvbPostcode()
{
}

void CHsvDvbPostcode::params__init(void)
{
	postcodekeyconf_MaxElements    = 20000;
	postcodekeyconf_ElementSize    = sizeof(HsvFreesatPostcodeMapping);
	postcodekeyconf_SortCriteria   = postcodekeyconf_Primary;

	postcoderegionkeyconf_MaxElements    = 1500;
	postcoderegionkeyconf_ElementSize    = sizeof(HsvFreesatRegionKeyMapping);
	postcoderegionkeyconf_SortCriteria   = postcoderegionkeyconf_Primary;
}

void CHsvDvbPostcode::module__init(void)
{

}

