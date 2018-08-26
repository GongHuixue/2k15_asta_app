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
 *          %name: hsvdvbbat_m.c %
 *       %version: blr81mgr#TVG_4.1.7.1.1 %
 * %date_modified: Fri Feb 20 20:07:55 2009 %
 *    %derived_by: anuma %
 */
 
#include "_hsvdvbbat_m.h"


TRACESYMBOL(m, "s2/sdm/hsvdvbbat")


#ifndef __cplusplus

#else

#endif

HsvTricolorLRNListDetails gBatTricolorLrnData;
HsvRegionNameList gRegionNameList;

Nat8 CHsvDvbBAT_Priv::s__mBuffer[16*1024*8];

Nat8 CHsvDvbBAT_Priv::s__ModeArray[FILTER_DEPTH];

Nat8 CHsvDvbBAT_Priv::s__MatchArray[FILTER_DEPTH];

Nat8 CHsvDvbBAT_Priv::s__MaskArray[FILTER_DEPTH];


struct DmxRomDataStruct CHsvDvbBAT_Priv::s__DmxROMData[HsvDmxLast];

/*CYFRA*/
/*FRANSAT-ECD-> Eutelsat Channel Descriptor*/
/*FRANSAT-BatDetails - Contains overall Bouquet Information*/
/*FRANSAT To populate bouquet Details*/
/*FRANSAT-ECD-> Eutelsat Channel Descriptor*/
/*CYFRA*/

/**********************************************************************************/

HSVCOMPAREKEY(batlcnconf, Primary,     HsvBATLCN, Original_NetworkId)

HSVCOMPAREKEY(batlcnconf, Secondary,   HsvBATLCN, Tsid)

HSVCOMPAREKEY(batlcnconf, Teritiary,   HsvBATLCN, ServiceId)
/*Below is not used */

HSVCOMPAREKEY(batlcnconf, Quaternary, HsvBATLCN, ServiceId)



HSVCOMPAREKEY(batsrvclstmainconf, Primary,     HsvBATServiceList, Original_NetworkId)

HSVCOMPAREKEY(batsrvclstmainconf, Secondary, HsvBATServiceList, Tsid)

HSVCOMPAREKEY(batsrvclstmainconf, Teritiary,   HsvBATServiceList, ServiceId)
/*Below is not used*/

HSVCOMPAREKEY(batsrvclstmainconf, Quaternary,   HsvBATServiceList, ServiceId)

/* BOUQUET INFO */

HSVCOMPAREKEY(batDetailsconf, Primary,     HsvBATDetails, BouquetId)

/* NOT USED */

HSVCOMPAREKEY(batDetailsconf, Secondary, HsvBATDetails, BouquetId )

HSVCOMPAREKEY(batDetailsconf, Teritiary,   HsvBATDetails, BouquetId )

HSVCOMPAREKEY(batDetailsconf, Quaternary, HsvBATDetails, BouquetId)

/* FRANSAT */

HSVCOMPAREKEY(batECNconf, Primary,     HsvBATECN,Onid )

HSVCOMPAREKEY(batECNconf, Secondary, HsvBATECN,Tsid )

HSVCOMPAREKEY(batECNconf, Teritiary,   HsvBATECN, ServiceId )

/* NOT USED */

HSVCOMPAREKEY(batECNconf, Quaternary, HsvBATECN,EutelsatChannelNum)


HSVCOMPAREKEY(batlcn2conf, Primary,     HsvBATLCN2, Original_NetworkId)

HSVCOMPAREKEY(batlcn2conf, Secondary,   HsvBATLCN2, Tsid)

HSVCOMPAREKEY(batlcn2conf, Teritiary,   HsvBATLCN2, ServiceId)
/*Below is not used */

HSVCOMPAREKEY(batlcn2conf, Quaternary, HsvBATLCN2, ServiceId)


HSVCOMPAREKEY(batFreesatSrvGroupconf, Primary,     HsvFreesatServiceGroupInfo, FreeSatelliteServiceIdentifier)
HSVCOMPAREKEY(batFreesatSrvGroupconf, Secondary,   HsvFreesatServiceGroupInfo, FreeSatelliteServicegroupId)
/*Below is not used */
HSVCOMPAREKEY(batFreesatSrvGroupconf, Teritiary,   HsvFreesatServiceGroupInfo, FreeSatelliteServicegroupId)
HSVCOMPAREKEY(batFreesatSrvGroupconf, Quaternary, HsvFreesatServiceGroupInfo, FreeSatelliteServicegroupId)
HSVCOMPAREKEY(batFreesatInfoLocationconf, Primary,     HsvFreesatInfoLocation, OriginalNetworkId)
HSVCOMPAREKEY(batFreesatInfoLocationconf, Secondary,   HsvFreesatInfoLocation, Tsid)
HSVCOMPAREKEY(batFreesatInfoLocationconf, Teritiary,   HsvFreesatInfoLocation, ServiceId)
/*Below is not used */
HSVCOMPAREKEY(batFreesatInfoLocationconf, Quaternary, HsvFreesatInfoLocation, ServiceId)

HSVCOMPAREKEY(batFreesatLCNconf, Primary,     HsvFreesatLCN, OriginalNetworkId)
HSVCOMPAREKEY(batFreesatLCNconf, Secondary,   HsvFreesatLCN, Tsid)
HSVCOMPAREKEY(batFreesatLCNconf, Teritiary,   HsvFreesatLCN, ServiceId)
/*Below is not used */
HSVCOMPAREKEY(batFreesatLCNconf, Quaternary, HsvFreesatLCN, ServiceId)
HSVCOMPAREKEY(batlinkmainconf, Primary,   HsvBATLinkageInfo,Original_NetworkId)

HSVCOMPAREKEY(batlinkmainconf, Secondary, HsvBATLinkageInfo,Tsid)

HSVCOMPAREKEY(batlinkmainconf, Teritiary, HsvBATLinkageInfo,LinkageType)
/*Below is not used */

#ifndef __cplusplus

HSVCOMPAREKEY(batlinkmainconf, QuaternaryKey, HsvBATLinkageInfo,LinkageType)

#endif

HSVCOMPAREKEY(batLCNV2conf, Primary,     HsvBATLCNV2, ServiceId)

/*Below is not used */
HSVCOMPAREKEY(batLCNV2conf, Secondary,   HsvBATLCNV2, ServiceId)

HSVCOMPAREKEY(batLCNV2conf, Teritiary,   HsvBATLCNV2, ServiceId)

HSVCOMPAREKEY(batLCNV2conf, Quaternary, HsvBATLCNV2, ServiceId)


HSVCOMPAREKEY(batMulLCNV2conf, Primary,     HsvBATMulLCNV2, ServiceId)

/*Below is not used */
HSVCOMPAREKEY(batMulLCNV2conf, Secondary,   HsvBATMulLCNV2, ServiceId)

HSVCOMPAREKEY(batMulLCNV2conf, Teritiary,   HsvBATMulLCNV2, ServiceId)

HSVCOMPAREKEY(batMulLCNV2conf, Quaternary, HsvBATMulLCNV2, ServiceId)


/*****   Module functions   *****/



Nat8 CHsvDvbBAT_Priv::batlinkmainconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED (key);
    UNUSED (data);
    return FALSE;
}
void CHsvDvbBAT_Priv::mInitBatLCN(HsvDemux dmx)
{
	srtdb_Init(srtdbids_BatLcnTable);
	UNUSED (dmx);
}

void CHsvDvbBAT_Priv::InitActualServiceListDS(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_BatSrvclstTableMain);
}

void CHsvDvbBAT_Priv::InitLinkageInfo(HsvDemux dmx)
{
	UNUSED (dmx);
    srtdb_Init(srtdbids_BatLinkageInfoMain);
}

void CHsvDvbBAT_Priv::InitActualBouquetId(HsvDemux dmx)
{
    DmxROMData[dmx].BouquetId = 0xFFFF;
}

Bool CHsvDvbBAT_Priv::PopulateActualBouquetId( HsvDemux dmx, TypeBat_Parser *BatTable,  int code)
{
    UNUSED( code );
	if( sec_SctArrived & code )
    {
        DmxROMData[dmx]. BouquetId  = BatTable->BouquetId;	        
    }
   return TRUE;
}


void CHsvDvbBAT_Priv::mPopulateNetworkLCN( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{
	Bool LCNChanged = FALSE;
	HsvBATLCN DbaseVersion, LogicalChannel;
	int i = 0, tsloop = 0, j = 0, TempLCNValue = 0xFFFF;
	
	while ( tsloop < BatTable->TsLoopDataNum)
	{
		TraceNotice(m,"BatTable->TsLoopData[tsloop].LCNDescNum %d",BatTable->TsLoopData[tsloop].LCNDescNum);
		if( sec_SctArrived & code )
		{
			for( i = 0; i < BatTable->TsLoopData[tsloop].LCNDescNum; i++)
			{
				if(BatTable->TsLoopData[tsloop].LCN_Descriptor[i].DescriptorValid)
				{
					for( j = 0; j < BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNLen ; j++)
					{
						TempLCNValue = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].LCNValue;
                        if(TempLCNValue != 0xFFFF)
                        {
                            if ( srtdb_QueryOnKey( srtdbids_BatLcnTable, BatTable->TsLoopData[tsloop].ONID, BatTable->TsLoopData[tsloop].TSID, BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId , 0, (Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if( (DbaseVersion.BouquetId == BatTable->BouquetId) && (DbaseVersion.VersionNumber != BatTable->VersionNo) )
                                {
                                    DbaseVersion.VersionNumber = BatTable->VersionNo;
									DbaseVersion.Frequency     = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].Frequency;
									DbaseVersion.Polarization  = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].Polarization;
									DbaseVersion.DpServiceId   = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].DpServiceId;
									DbaseVersion.DpTsid        = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].DpTSId;
									
									if( DbaseVersion.LogicalChannelNum != TempLCNValue )
                                    {
                                        DbaseVersion.LogicalChannelNum = TempLCNValue;
                                        LCNChanged = TRUE;
                                    }

									//PrintfNotice("LCN: <%d %d %d> <%d %d>", DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNum, DbaseVersion.VisibleService);
                                    srtdb_Update(srtdbids_BatLcnTable,BatTable->TsLoopData[tsloop].ONID, BatTable->TsLoopData[tsloop].TSID, BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId , 0,(Address)(&DbaseVersion) );
                                
                                    if(LCNChanged == TRUE)
                                    {
                                        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN, dvb, bat), BatTable->TsLoopData[tsloop].ONID, BatTable->TsLoopData[tsloop].TSID, BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId, 0); 
                                    }
								}
                            }
                            else
                            {   
                                LogicalChannel.BouquetId          = BatTable->BouquetId;
                                LogicalChannel.Original_NetworkId = BatTable->TsLoopData[tsloop].ONID;
                                LogicalChannel.Tsid               = BatTable->TsLoopData[tsloop].TSID;
								LogicalChannel.Frequency          = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].Frequency;
								LogicalChannel.Polarization       = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].Polarization;
								LogicalChannel.ServiceId          = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].ServiceId;
								LogicalChannel.DpServiceId        = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].DpServiceId;
								LogicalChannel.DpTsid             = BatTable->TsLoopData[tsloop].LCN_Descriptor[i].LCNDesc[j].DpTSId;
                                LogicalChannel.LogicalChannelNum  = TempLCNValue;
                                LogicalChannel.VisibleService     = TRUE;
                                LogicalChannel.VersionNumber      = BatTable->VersionNo;

								//PrintfNotice("LCN: <%d %d %d> <%d %d>", LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId, LogicalChannel.LogicalChannelNum, LogicalChannel.VisibleService);
                                srtdb_Insert( srtdbids_BatLcnTable, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId , LogicalChannel.ServiceId , (Address)(&LogicalChannel));
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN, dvb, bat), LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId);
                            }
                        }
                    }
				}
			}
		}
		else if(sec_TableCompleted & code)
		{
			/* Delete logical channels if not present */
			int j = srtdb_GetNoOfRecords(srtdbids_BatLcnTable) - 1;
			while( j >= 0 )
			{
				if(srtdb_QueryOnIndex(srtdbids_BatLcnTable,j,(Address )(&DbaseVersion)))
				{
					if( (DbaseVersion.BouquetId == BatTable->BouquetId) && 
						(DbaseVersion.VersionNumber != BatTable->VersionNo))
					{
						/* delete the record */
						if (srtdb_Delete(srtdbids_BatLcnTable, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.ServiceId))
						{  
							strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN, dvb, bat), DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
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
			strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN, dvb, bat));
		}
		tsloop++;
	}
}

void CHsvDvbBAT_Priv::mInitBatLCN2(HsvDemux dmx)						/*cyfra*/
{
	srtdb_Init(srtdbids_BatLcn2Table);
	UNUSED (dmx);
}

void CHsvDvbBAT_Priv::mInitBatLCNV2(HsvDemux dmx)						/*NTV+*/
{
	srtdb_Init(srtdbids_BatLCNV2Table);
	UNUSED (dmx);
}

void CHsvDvbBAT_Priv::mInitBatMulLCNV2(HsvDemux dmx)						/*Tricolor*/
{
	srtdb_Init(srtdbids_BatMulLCNV2Table);
	UNUSED (dmx);
}



void CHsvDvbBAT_Priv::mInitBatECN(HsvDemux dmx)					/*FRANSAT-ECD-> Eutelsat Channel Descriptor*/
{
	srtdb_Init(srtdbids_BatECNTable);
	UNUSED (dmx);
}

void CHsvDvbBAT_Priv::mInitBatDetails(HsvDemux dmx)					/*FRANSAT-BatInfo - Contains overall Bouquet Information*/
{
	srtdb_Init(srtdbids_BatDetailsTable);
	UNUSED (dmx);
}

void	CHsvDvbBAT_Priv::mInitBatTricolorLRNDetails(HsvDemux dmx)
{
	UNUSED (dmx);
	memset ((void *)&gBatTricolorLrnData,0, sizeof (HsvTricolorLRNListDetails));
	memset ((void *)&gRegionNameList,0, sizeof (HsvRegionNameList));
}

void	CHsvDvbBAT_Priv::mInitBatFreesatSrvGroupTable(HsvDemux dmx)
{
	srtdb_Init(srtdbids_BatFreesatSrvGroupTable);
	UNUSED (dmx);
}
void	CHsvDvbBAT_Priv::mInitBatFreesatInfoLocationTable(HsvDemux dmx)
{
	srtdb_Init(srtdbids_BatFreesatInfoLocationTable);
	UNUSED (dmx);
}

void	CHsvDvbBAT_Priv::mInitBatFreesatLCNTable(HsvDemux dmx)
{
	srtdb_Init(srtdbids_BatFreesatLCNTable);
	UNUSED (dmx);
}
void CHsvDvbBAT_Priv::mPopulateNetworkLCN2( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{
	Bool LCN2Changed = FALSE;
	HsvBATLCN2 DbaseVersion, LogicalChannel;
	int i = 0, tsloop = 0, j = 0, TempLCNValue = 0xFFFF;
	Bool v_flag =0;
	
	while ( tsloop < BatTable->TsLoopDataNum)
	{
		if( sec_SctArrived & code )
		{
			for( i = 0; i < BatTable->TsLoopData[tsloop].LCN2DescNum; i++)
			{
				if(BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].DescriptorValid)
				{
					for( j = 0; j < BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Len ; j++)
					{
						TempLCNValue = (BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Desc[j].LCNValue&0x03FF);
						v_flag	= (Bool )( (BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Desc[j].LCNValue & 0x8000) >> 15);
                        if(TempLCNValue != 0xFFFF)
                        {
                            if ( srtdb_QueryOnKey( srtdbids_BatLcn2Table, BatTable->TsLoopData[tsloop].ONID, BatTable->TsLoopData[tsloop].TSID, BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Desc[j].ServiceId , 0, (Address)(&DbaseVersion) ) )
                            {
                                /* Record Exists - Update the information & notify if needed*/
                                if( (DbaseVersion.BouquetId == BatTable->BouquetId) && (DbaseVersion.VersionNumber != BatTable->VersionNo) )
                                {
                                    DbaseVersion.VersionNumber = BatTable->VersionNo;								
													
									if( DbaseVersion.LogicalChannelNum != TempLCNValue )
                                    {
                                        DbaseVersion.LogicalChannelNum = TempLCNValue;
                                        LCN2Changed = TRUE;
                                    }
									DbaseVersion.VisibleService =  v_flag; 
									//PrintfNotice("LCN: <%d %d %d> <%d %d>", DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNum, DbaseVersion.VisibleService);
                                    srtdb_Update(srtdbids_BatLcn2Table,BatTable->TsLoopData[tsloop].ONID, BatTable->TsLoopData[tsloop].TSID, BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Desc[j].ServiceId , 0,(Address)(&DbaseVersion) );
                                
                                    if(LCN2Changed == TRUE)
                                    {
                                        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN2, dvb, bat), BatTable->TsLoopData[tsloop].ONID, BatTable->TsLoopData[tsloop].TSID, BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Desc[j].ServiceId, 0); 
                                    }
								}
                            }
                            else
                            {   
                                LogicalChannel.BouquetId          = BatTable->BouquetId;
                                LogicalChannel.Original_NetworkId = BatTable->TsLoopData[tsloop].ONID;
                                LogicalChannel.Tsid               = BatTable->TsLoopData[tsloop].TSID;
					
								LogicalChannel.ServiceId          = BatTable->TsLoopData[tsloop].LCN2_Descriptor[i].LCN2Desc[j].ServiceId;
								
                                LogicalChannel.LogicalChannelNum  = TempLCNValue;                                
                                LogicalChannel.VersionNumber      = BatTable->VersionNo;
								LogicalChannel.VisibleService     =  v_flag;  
								PrintfNotice("LCN: <%d %d %d> <%d %d>", LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId, LogicalChannel.LogicalChannelNum, LogicalChannel.VisibleService);
                                srtdb_Insert( srtdbids_BatLcn2Table, LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId , LogicalChannel.ServiceId , (Address)(&LogicalChannel));
                                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN2, dvb, bat), LogicalChannel.Original_NetworkId, LogicalChannel.Tsid, LogicalChannel.ServiceId);
                            }
                        }
                    }
				}
			}
		}
		else if(sec_TableCompleted & code)
		{
			/* Delete logical channels if not present */
			int j = srtdb_GetNoOfRecords(srtdbids_BatLcn2Table) - 1;
			while( j >= 0 )
			{
				if(srtdb_QueryOnIndex(srtdbids_BatLcn2Table,j,(Address )(&DbaseVersion)))
				{
					if( (DbaseVersion.BouquetId == BatTable->BouquetId) && 
						(DbaseVersion.VersionNumber != BatTable->VersionNo))
					{
						/* delete the record */
						if (srtdb_Delete(srtdbids_BatLcn2Table, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.ServiceId))
						{  
							strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN2, dvb, bat), DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
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
			strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCN2, dvb, bat));
		}
		tsloop++;
	}
}

void CHsvDvbBAT_Priv::mPopulateNetworkLCNV2( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{
	Bool LCNV2Changed = FALSE;
	HsvBATLCNV2 DbaseVersion, LogicalChannel;
	int i = 0, j = 0, TempLCNValue = 0xFFFF;
	Bool v_flag =0;
	if( sec_SctArrived & code )
	{
		for( i = 0; i < BatTable->LCNV2DescNum; i++)
		{
			if(BatTable->LCNV2_Descriptor[i].DescriptorValid)
			{
				for( j = 0; j < BatTable->LCNV2_Descriptor[i].LCN2Len ; j++)
				{
					TempLCNValue = (BatTable->LCNV2_Descriptor[i].LCN2Desc[j].LCNValue&0x03FF);
					v_flag	= (Bool )( (BatTable->LCNV2_Descriptor[i].LCN2Desc[j].LCNValue & 0x8000) >> 15);
					if(TempLCNValue != 0xFFFF)
					{
						if ( srtdb_QueryOnKey( srtdbids_BatLCNV2Table, BatTable->LCNV2_Descriptor[i].LCN2Desc[j].ServiceId , 0, 0, 0, (Address)(&DbaseVersion) ) )
						{
							/* Record Exists - Update the information & notify if needed*/
							if( (DbaseVersion.BouquetId == BatTable->BouquetId) && (DbaseVersion.VersionNumber != BatTable->VersionNo) )
							{
								DbaseVersion.VersionNumber = BatTable->VersionNo;								
												
								if( DbaseVersion.LogicalChannelNum != TempLCNValue )
								{
									DbaseVersion.LogicalChannelNum = TempLCNValue;
									LCNV2Changed = TRUE;
								}
								DbaseVersion.VisibleService =  v_flag; 
								//PrintfNotice("LCN: <%d %d %d> <%d %d>", DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNum, DbaseVersion.VisibleService);
								srtdb_Update(srtdbids_BatLCNV2Table, BatTable->LCNV2_Descriptor[i].LCN2Desc[j].ServiceId , 0, 0, 0,(Address)(&DbaseVersion) );
							
								if(LCNV2Changed == TRUE)
								{
									strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCNV2, dvb, bat), BatTable->LCNV2_Descriptor[i].LCN2Desc[j].ServiceId, 0, 0, 0); 
								}
							}
						}
						else
						{   
							LogicalChannel.BouquetId          = BatTable->BouquetId;	
							LogicalChannel.ServiceId          = BatTable->LCNV2_Descriptor[i].LCN2Desc[j].ServiceId;
							
							LogicalChannel.LogicalChannelNum  = TempLCNValue;                                
							LogicalChannel.VersionNumber      = BatTable->VersionNo;
							LogicalChannel.VisibleService     =  v_flag;  
							PrintfNotice("mPopulateNetworkLCNV2: LCN: <%d> <%d %d>", LogicalChannel.ServiceId, LogicalChannel.LogicalChannelNum, LogicalChannel.VisibleService);
							srtdb_Insert( srtdbids_BatLCNV2Table,LogicalChannel.ServiceId , 0, 0, 0, (Address)(&LogicalChannel));
							strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCNV2, dvb, bat), LogicalChannel.ServiceId, 0, 0);
						}
					}
				}
			}
		}
	}
	else if(sec_TableCompleted & code)
	{
		/* Delete logical channels if not present */
		int j = srtdb_GetNoOfRecords(srtdbids_BatLCNV2Table) - 1;
		while( j >= 0 )
		{
			if(srtdb_QueryOnIndex(srtdbids_BatLCNV2Table,j,(Address )(&DbaseVersion)))
			{
				if( (DbaseVersion.BouquetId == BatTable->BouquetId) && 
					(DbaseVersion.VersionNumber != BatTable->VersionNo))
				{
					/* delete the record */
					if (srtdb_Delete(srtdbids_BatLCNV2Table, DbaseVersion.ServiceId, 0, 0, 0))
					{  
						strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCNV2, dvb, bat), DbaseVersion.ServiceId, 0, 0);
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
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batLCNV2, dvb, bat));
	}
}

void CHsvDvbBAT_Priv::mPopulateTricolorLCNV2( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{
	//TraceNotice(m,"%s code %d",__FUNCTION__,code);
	Bool LCNV2Changed = FALSE;
	HsvBATMulLCNV2 DbaseVersion, LogicalChannel;
	int i = 0, j = 0, k =0 ,LoopIndex = 0,TempLCNValue = 0xFFFF;
	Bool v_flag =0;
	char regionName[24] = "FEDERAL";
	int length = 0;
	char *hdsdPostfix = NULL;
	int preferedlangid = 0;
	Nat32 Data = 0;
	HsvTricolorRegionNameData *tricolorRegionName;
	Bool validChannellistname = TRUE;

	int packageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	if (packageId == TRICOLOR_SD_PACKAGE_ID) 
	{
		hdsdPostfix = "_SD";
	}
	else if (packageId == TRICOLOR_HD_PACKAGE_ID)
	{
		
		hdsdPostfix = "_HD";
	}

	
	Data = itricolorsettings_GetAttribute(idvbset_AttributeTricolorRegionNameData);
	tricolorRegionName = (HsvTricolorRegionNameData*)Data;
	
	TraceNotice(m," Region Name selcted is %s %p %d",tricolorRegionName->regionName,tricolorRegionName,packageId);
	if (tricolorRegionName->regionName != NULL)
	{
		strncpy(regionName,tricolorRegionName->regionName,tricolorRegionName->regionNameLength);
		regionName[tricolorRegionName->regionNameLength] = '\0';
		TraceNotice(m," Region Name selcted is %s",regionName);
	}
	else
	{
		TraceNotice(m," Region Name List is Empty!!!!! or Somehow we could not Retreive selected Region\n");
		
	}

	/*This memory was dynamically allocated in hsvdvbstricolor_msetting.cpp GetAttribute Function*/
	//TraceNotice(m,"freeing memory after this");
	free(tricolorRegionName);
	
	if( sec_SctArrived & code )
	{
		//TraceNotice(m,"debug: BatTable->LCNV2DescNum %d",BatTable->LCNV2DescNum);
		for( i = 0; i < BatTable->LCNV2DescNum; i++)
		{
			if(BatTable->LCNV2_Descriptor[i].DescriptorValid)
			{
				//TraceNotice(m,"debug: BatTable->LCNV2_Descriptor[%d].LCN2ChannelListLen %d %s",i,BatTable->LCNV2_Descriptor[i].LCN2ChannelListLen,hdsdPostfix);
				for( j = 0; j < BatTable->LCNV2_Descriptor[i].LCN2ChannelListLen ; j++)
				{
					
					if(NULL != strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name,regionName))
					{
						
						if(NULL == strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name,"_AL"))
						{
							if(NULL == strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name, hdsdPostfix))
							{
								validChannellistname = FALSE;
							}	
						}
					}
					else
					{
						
						if(strcmp(regionName,"FEDERAL") == 0)
						{
							validChannellistname = FALSE;
						}
						else
						{
							
							if(NULL != strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name,"FEDERAL"))
							{	
								
								if(NULL == strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name, "_AL"))
								{
									
									if(NULL == strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name, hdsdPostfix))
									{
										validChannellistname = FALSE;
									}
								}
							}
							else
							{
								validChannellistname = FALSE;
							}
						}		
					}

					if(validChannellistname == FALSE)
					{
						//TraceNotice(m,"Not a valid channellist name [%s]",BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name);
						continue;
					}
					else
					{
						//TraceNotice(m,"%s",BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name);
					}

					LogicalChannel.IsFederalService = (NULL != strstr(BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].Channel_List_Name,"FEDERAL_"))?TRUE:FALSE;
					
					//TraceNotice(m,"debug: BatTable->LCNV2_Descriptor[%d].LCN2ChannelLstDesc[%d].LCN2SvcDescLen %d",i,j,BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDescLen);
					for(k = 0;k < BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDescLen;k++)
					{

						TempLCNValue = BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDesc[k].LCNValue;
						v_flag   	 = BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDesc[k].Visibility;

						LogicalChannel.BouquetId          = BatTable->BouquetId;	
						LogicalChannel.ServiceId          = BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDesc[k].ServiceId;                            
						LogicalChannel.VersionNumber      = BatTable->VersionNo;

						//TraceNotice(m,"considering:TempLCNValue %d v_flag %d sid %d bid %d",TempLCNValue,v_flag,LogicalChannel.ServiceId,LogicalChannel.BouquetId);

						/*Invalidate all ECN entries*/
						LogicalChannel.LogicalChannelNum[0]	 			= TempLCNValue;
						LogicalChannel.LogicalChannelNum[1]  			= INVALID_BAT_LCN;
						LogicalChannel.LogicalChannelNum[2]  			= INVALID_BAT_LCN;
						LogicalChannel.LogicalChannelNum[3]  			= INVALID_BAT_LCN;
						LogicalChannel.LogicalChannelNum[4]  			= INVALID_BAT_LCN;
						LogicalChannel.LogicalChannelNum[5]  			= INVALID_BAT_LCN;
						LogicalChannel.LogicalChannelNum[6]  			= INVALID_BAT_LCN;
						LogicalChannel.LogicalChannelNum[7]  			= INVALID_BAT_LCN;

						/*Initialize MultipleVisibleServiceFlag*/
						LogicalChannel.MultipleVisibleServiceFlag[0]    = v_flag;					
						LogicalChannel.MultipleVisibleServiceFlag[1]    = 0;
						LogicalChannel.MultipleVisibleServiceFlag[2]    = 0;
						LogicalChannel.MultipleVisibleServiceFlag[3]    = 0;
						LogicalChannel.MultipleVisibleServiceFlag[4]    = 0;
						LogicalChannel.MultipleVisibleServiceFlag[5]    = 0;
						LogicalChannel.MultipleVisibleServiceFlag[6]    = 0;
						LogicalChannel.MultipleVisibleServiceFlag[7]    = 0;


					
						if(TempLCNValue != 0xFFFF)
						{
							if ( srtdb_QueryOnKey( srtdbids_BatMulLCNV2Table, BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDesc[k].ServiceId, 0, 0, 0, (Address)(&DbaseVersion) ) )
							{
								/* Record Exists - Update the information & notify if needed*/
								if( (DbaseVersion.BouquetId == LogicalChannel.BouquetId ))  
								{
									LCNV2Changed = TRUE;

									//TraceNotice(m,"DbaseVersion.VersionNumber %d LogicalChannel.VersionNumber %d",DbaseVersion.VersionNumber,LogicalChannel.VersionNumber);
									if(DbaseVersion.VersionNumber == LogicalChannel.VersionNumber)
									{
										LCNV2Changed = FALSE;
										/*version matches so this entry is for same service at different ECN (multiple ECN for same service)*/
										for(LoopIndex = 0; LoopIndex < MAX_LCN_PER_SERVICE; LoopIndex++)
				                        {
				                            if(TempLCNValue == DbaseVersion.LogicalChannelNum[LoopIndex])
				                            {
				                                /*existing entry so skip the LCN value*/
				                                break;
				                            }
				                            else if(INVALID_BAT_LCN == DbaseVersion.LogicalChannelNum[LoopIndex])
				                            {
				                                LogicalChannel.LogicalChannelNum[LoopIndex] 		 = TempLCNValue;
												LogicalChannel.MultipleVisibleServiceFlag[LoopIndex] = v_flag;
				                                LCNV2Changed = TRUE;
				                                //TraceNotice(m,"%d Multiple LCN for Service, SID %d LCN %d",LoopIndex, DbaseVersion.ServiceId, TempLCNValue);
				                                break;
				                            }
				                            else
				                            {
				                                LogicalChannel.LogicalChannelNum[LoopIndex] 		 =   DbaseVersion.LogicalChannelNum[LoopIndex];
												LogicalChannel.MultipleVisibleServiceFlag[LoopIndex] =   DbaseVersion.MultipleVisibleServiceFlag[LoopIndex];
				                            }
				                        }
									}
									
								}
								
								if(LCNV2Changed == TRUE)
								{
									
									//TraceNotice(m,"Updated LCN: <%d> <%d %d>",DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNum[0], DbaseVersion.VisibleService);
									srtdb_Update(srtdbids_BatMulLCNV2Table, BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDesc[k].ServiceId , 0, 0, 0,(Address)(&LogicalChannel) );
									strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batMulLCNV2, dvb, bat), BatTable->LCNV2_Descriptor[i].LCN2ChannelLstDesc[j].LCN2SvcDesc[k].ServiceId, 0, 0, 0); 
								}
							}
							else
							{   

								//TraceNotice(m,"Added mPopulateNetworkLCNV2: LCN: <%d> <%d %d>", LogicalChannel.ServiceId, LogicalChannel.LogicalChannelNum[0], LogicalChannel.VisibleService);
								srtdb_Insert( srtdbids_BatMulLCNV2Table,LogicalChannel.ServiceId , 0, 0, 0, (Address)(&LogicalChannel));
								strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batMulLCNV2, dvb, bat), LogicalChannel.ServiceId, 0, 0);
							}
						
						}
					}
				
					}
				}
			}
	

		
		
	}
	else if(sec_TableCompleted & code)
	{
		/* Delete logical channels if not present */
		int j = srtdb_GetNoOfRecords(srtdbids_BatMulLCNV2Table) - 1;
		while( j >= 0 )
		{
			if(srtdb_QueryOnIndex(srtdbids_BatMulLCNV2Table,j,(Address )(&DbaseVersion)))
			{
				//TraceNotice(m,"debug: db.bid %d db.vno %d cur.bid %d cur.vno %d ",DbaseVersion.BouquetId,DbaseVersion.VersionNumber,BatTable->BouquetId,BatTable->VersionNo);
				if( (DbaseVersion.BouquetId == BatTable->BouquetId) && 
					(DbaseVersion.VersionNumber != BatTable->VersionNo))
				{
					
					/* delete the record */
					if (srtdb_Delete(srtdbids_BatMulLCNV2Table, DbaseVersion.ServiceId, 0, 0, 0))
					{  
						strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batMulLCNV2, dvb, bat), DbaseVersion.ServiceId, 0, 0);
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
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batMulLCNV2, dvb, bat));
		
	}

	
}



/* Tricolor Region Name population. This should happen according the language setting */
void CHsvDvbBAT_Priv::mPopulateTricolorLRNDetails( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{

	int channelListIndex;
	int packageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	
	/* During package Build mode extract the list of regions to be shown for Tricolor Region Name Selection 
 	*  for Bouquet ID 0x01
 	*/

	if ((ctrl_PkgBuildMode == ctrl_GetMode(dmx)) && (BatTable->BouquetId == 0x01) && (BatTable->TricolorLRN_DescNum > 0))
	{
		
		int sysLanguageId = sysset_GetSystemLanguage();
		//TraceNotice(m,"SysLang id %d TricolorLRN_DescNum %d",sysLanguageId,BatTable->TricolorLRN_DescNum);
		//TricolorLRN_Descriptor.channelListDetailNum;
		
		int descCount = BatTable->TricolorLRN_DescNum; 
		int length;
		int preferedLangId;
		int curLangId = -1;
		char *listPostfix;
		int loop = 0,channellistloop = 0,totalChannellistcount =0,langListIndex = 0,channelListIndex = 0;
		Bool channelListNameExists = false;
		
		/* Third preference given to first available language: So keep it default */
		preferedLangId = mGetLanguageId(BatTable->TricolorLRN_Descriptor[0].langCode[0], \
									 	BatTable->TricolorLRN_Descriptor[0].langCode[1], \
									 	BatTable->TricolorLRN_Descriptor[0].langCode[2]);

		
		/*
		Here we are indentifying the Prefered Language:with below priority
			1.User selected menu language
			2.Russian Language.
			3.First Available Language.
		*/
		while(loop < descCount)
		{
			curLangId = mGetLanguageId(BatTable->TricolorLRN_Descriptor[loop].langCode[0], \
									   BatTable->TricolorLRN_Descriptor[loop].langCode[1], \
									   BatTable->TricolorLRN_Descriptor[loop].langCode[2]);

			
			if((curLangId == sysLanguageId))
			{
				preferedLangId = curLangId;
				break;
			}
			else if((IHsvLanguageIds2_LangRussian == curLangId))
			{
				preferedLangId = curLangId;
			}

			loop++;
		}

	
		TraceNotice(m,"prefered Languageid %d",preferedLangId);

		/*Adding Previous Section's Language List Count*/
		descCount += gBatTricolorLrnData.LanguageListCount;
		
		loop = gBatTricolorLrnData.LanguageListCount;
		totalChannellistcount = gRegionNameList.TotalChannelListCount;

		TraceNotice(m,"New section: loop [%d] totalChannellistcount [%d] descCount [%d]",loop,totalChannellistcount,descCount);

		channellistloop = 0;
		curLangId = -1;
		
		while((loop < descCount) && (loop < 10))
		{
			gBatTricolorLrnData.LanguageListDetails[loop].langCode[0] = BatTable->TricolorLRN_Descriptor[loop].langCode[0];
			gBatTricolorLrnData.LanguageListDetails[loop].langCode[1] = BatTable->TricolorLRN_Descriptor[loop].langCode[1];
			gBatTricolorLrnData.LanguageListDetails[loop].langCode[2] = BatTable->TricolorLRN_Descriptor[loop].langCode[2];

			curLangId = mGetLanguageId(gBatTricolorLrnData.LanguageListDetails[loop].langCode[0], 
									   gBatTricolorLrnData.LanguageListDetails[loop].langCode[1],
									   gBatTricolorLrnData.LanguageListDetails[loop].langCode[2]);

			
			if(curLangId == preferedLangId)
			{
				gBatTricolorLrnData.LanguageListDetails[loop].ChannelListCount = BatTable->TricolorLRN_Descriptor[loop].channelListDetailNum;
			
				channellistloop = 0;
				while((channellistloop < gBatTricolorLrnData.LanguageListDetails[loop].ChannelListCount) && 
					  (totalChannellistcount < 10))
				{
					
					
					length = BatTable->TricolorLRN_Descriptor[loop].Tricolor_ChannelListDetails[channellistloop].channelListNameLength;
					length = length > TRICOLOR_MAX_REGION_NAME_LENGTH ? TRICOLOR_MAX_REGION_NAME_LENGTH : length;

					
					strncpy(gBatTricolorLrnData.LanguageListDetails[loop].ChannelListDetails[channellistloop].regionName,BatTable->TricolorLRN_Descriptor[loop].Tricolor_ChannelListDetails[channellistloop].channelListName,\
					length);
					gBatTricolorLrnData.LanguageListDetails[loop].ChannelListDetails[channellistloop].regionNameLength = length;
					gBatTricolorLrnData.LanguageListDetails[loop].ChannelListDetails[channellistloop].regionName[length] = '\0';

					strncpy(gRegionNameList.ChannelListData[totalChannellistcount].regionName,BatTable->TricolorLRN_Descriptor[loop].Tricolor_ChannelListDetails[channellistloop].channelListName,\
					length);
					gRegionNameList.ChannelListData[totalChannellistcount].regionNameLength = length;
					gRegionNameList.ChannelListData[totalChannellistcount].regionName[length] = '\0';

					length = BatTable->TricolorLRN_Descriptor[loop].Tricolor_ChannelListDetails[channellistloop].channelListNameTranslationLength;
					length = length > TRICOLOR_MAX_REGION_NAME_LENGTH ? TRICOLOR_MAX_REGION_NAME_LENGTH : length;
					
					charsetutil_MbToWc
					( (Nat8 *) BatTable->TricolorLRN_Descriptor[loop].Tricolor_ChannelListDetails[channellistloop].channelListNameTranslation, 
					    length, 
					    (Nat16 *) gRegionNameList.ChannelListData[totalChannellistcount].regionNameTranslation,
					    length,
					    FALSE
					 );

					gBatTricolorLrnData.LanguageListDetails[loop].ChannelListDetails[channellistloop].regionNameTranslationLength = length;
					gBatTricolorLrnData.LanguageListDetails[loop].ChannelListDetails[channellistloop].regionNameTranslation[length] = '\0';

					charsetutil_MbToWc
					(  (Nat8 *) BatTable->TricolorLRN_Descriptor[loop].Tricolor_ChannelListDetails[channellistloop].channelListNameTranslation, 
					   length, 
					   (Nat16 *) gRegionNameList.ChannelListData[totalChannellistcount].regionNameTranslation,
					   length,
					   FALSE
					 );

					gRegionNameList.ChannelListData[totalChannellistcount].regionNameTranslationLength = length;
					gRegionNameList.ChannelListData[totalChannellistcount].regionNameTranslation[length] = '\0';


					channellistloop++;
					totalChannellistcount++;

					TraceNotice(m,"channellistloop %d totalchannellistcount %d",channellistloop,totalChannellistcount);
				}
				
			}

			loop++;
		}
		gRegionNameList.TotalChannelListCount = totalChannellistcount;
		gBatTricolorLrnData.LanguageListCount = loop;

		TraceNotice(m,"Current Section: LRN details:LanguageListCount  %d totalchannellistcount %d",loop,totalChannellistcount);
	}
}

void CHsvDvbBAT_Priv::mPopulateBouquetDetails( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{
    HsvBATDetails	DbaseVersion;
    HsvBATDetails	CurrentVersion;

    if(BatTable->BouquetName_Descriptor.DescriptorValid)
    {
        memset(&DbaseVersion, 0, sizeof(HsvBATDetails));
        memset(&CurrentVersion, 0, sizeof(HsvBATDetails));

        CurrentVersion.BouquetId = BatTable->BouquetId;
        CurrentVersion.VersionNumber = BatTable->VersionNo;
        charsetutil_MbToWc((Nat8 *)BatTable->BouquetName_Descriptor.BouquetName,
                                           BatTable->BouquetName_Descriptor.BouquetNameLen,
                                           CurrentVersion.BouquetName,
                                            MAX_BOUQUET_NAME_LEN,
                                            (BatTable->BouquetName_Descriptor.BouquetNameLen >= MAX_BOUQUET_NAME_LEN) ? TRUE : FALSE);

        if ( srtdb_QueryOnKey( srtdbids_BatDetailsTable, CurrentVersion.BouquetId,0,0,0, (Address)(&DbaseVersion) ) )
        {
            /* Record Exists - Update the information & notify if needed*/
            if( (DbaseVersion.BouquetId == CurrentVersion.BouquetId) && (DbaseVersion.VersionNumber != CurrentVersion.VersionNumber) )
            {
                /* Above if condition have to be verified for version checking in case of version changed */
                TraceDebug(m,"BAT details update: <0x%x %d %s\n", CurrentVersion.BouquetId, CurrentVersion.VersionNumber,CurrentVersion.BouquetName);
                srtdb_Update( srtdbids_BatDetailsTable, CurrentVersion.BouquetId,0,0,0, (Address)(&CurrentVersion) );
                strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batDetails, dvb, bat), CurrentVersion.BouquetId, 0, 0, 0);
            }
        }
        else
        {
            TraceDebug(m,"BAT details added: <0x%x %d %s\n", CurrentVersion.BouquetId, CurrentVersion.VersionNumber,CurrentVersion.BouquetName);
            srtdb_Insert( srtdbids_BatDetailsTable, CurrentVersion.BouquetId,0,0,0, (Address)(&CurrentVersion));
            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batDetails, dvb, bat), CurrentVersion.BouquetId, 0,0);
        }

        /*Reset the descriptor valid flag to avoid adding/updating same descriptor again, due to muliple population for same section*/
        BatTable->BouquetName_Descriptor.DescriptorValid = FALSE;
    }
}

void CHsvDvbBAT_Priv::mPopulateEutelsatChannelList( HsvDemux dmx , TypeBat_Parser *BatTable, int code)
{
    HsvBATECN DbaseVersion;
    HsvBATECN CurrentVersion;
    int DescIndex = 0;
    int TempLCNValue = 0xFFFF;
    int LoopIndex = 0;
    Bool UpdateECN = FALSE;
    while ( DescIndex < BatTable->TotalNoOfEutelsatDesc)
    {

        if(FRANSAT_PDSD_VALUE == BatTable->EutelsatChannelDescriptor[DescIndex].PrivateDataSpecifierValue)
        {
            TempLCNValue = BatTable->EutelsatChannelDescriptor[DescIndex].EutelsatChannelNum;

            CurrentVersion.BouquetId      = BatTable->BouquetId;
            CurrentVersion.Onid         = BatTable->EutelsatChannelDescriptor[DescIndex].Onid;
            CurrentVersion.Tsid               = BatTable->EutelsatChannelDescriptor[DescIndex].Tsid;
            CurrentVersion.ServiceId          = BatTable->EutelsatChannelDescriptor[DescIndex].ServiceId;
            CurrentVersion.VersionNumber      = BatTable->VersionNo;

            /*Invalidate all ECN entries*/
            CurrentVersion.EutelsatChannelNum[0]  = TempLCNValue;
            CurrentVersion.EutelsatChannelNum[1]  = INVALID_BAT_ECN;
            CurrentVersion.EutelsatChannelNum[2]  = INVALID_BAT_ECN;
            CurrentVersion.EutelsatChannelNum[3]  = INVALID_BAT_ECN;
            CurrentVersion.EutelsatChannelNum[4]  = INVALID_BAT_ECN;
            CurrentVersion.EutelsatChannelNum[5]  = INVALID_BAT_ECN;
            CurrentVersion.EutelsatChannelNum[6]  = INVALID_BAT_ECN;
            CurrentVersion.EutelsatChannelNum[7]  = INVALID_BAT_ECN;


            if ( srtdb_QueryOnKey( srtdbids_BatECNTable,
                                   CurrentVersion.Onid,
                                    CurrentVersion.Tsid,
                                   CurrentVersion.ServiceId ,  0, (Address)(&DbaseVersion)))
            {
                if(DbaseVersion.BouquetId == CurrentVersion.BouquetId)
                {
                    UpdateECN = TRUE;
                    if(DbaseVersion.VersionNumber == CurrentVersion.VersionNumber)
                    {
                        UpdateECN = FALSE;
                        /*version matches so this entry is for same service at different ECN (multiple ECN for same service)*/
                        for(LoopIndex = 0; LoopIndex < MAX_ECN_PER_SERVICE; LoopIndex++)
                        {
                            if(TempLCNValue == DbaseVersion.EutelsatChannelNum[LoopIndex])
                            {
                                /*existing entry so skip the ECN value*/
                                break;
                            }
                            else if(INVALID_BAT_ECN == DbaseVersion.EutelsatChannelNum[LoopIndex])
                            {
                                CurrentVersion.EutelsatChannelNum[LoopIndex]  = TempLCNValue;
                                UpdateECN = TRUE;
                                TraceNotice(m,"%d ECN for Service, SID %d ECN %d",LoopIndex, DbaseVersion.ServiceId, TempLCNValue);
                                break;
                            }
                            else
                            {
                                CurrentVersion.EutelsatChannelNum[LoopIndex] =   DbaseVersion.EutelsatChannelNum[LoopIndex];
                            }
                        }
                    }

                    if(UpdateECN)
                    {
                        srtdb_Update( srtdbids_BatECNTable, CurrentVersion.Onid,
                                                                        CurrentVersion.Tsid,
                                                                        CurrentVersion.ServiceId ,
                                                                        0, (Address)(&CurrentVersion));

                        strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batECN, dvb, bat),
                                                                   CurrentVersion.Onid,
                                                                   CurrentVersion.Tsid,
                                                                   CurrentVersion.ServiceId, (int)0);

                        TraceDebug(m,"Update ECN: BID 0x%x OIND 0x%x  TSID 0x%x SID 0x%x  ECN %d Ver %d", CurrentVersion.BouquetId, CurrentVersion.Onid, CurrentVersion.Tsid, CurrentVersion.ServiceId, TempLCNValue, CurrentVersion.VersionNumber);

                    }
                    else
                    {
                        TraceNotice(m, "More than 8 ECN entries/ dulicate, so skiping ECN %d For service - OIND 0x%x  TSID 0x%x SID 0x%x ",TempLCNValue, CurrentVersion.Onid, CurrentVersion.Tsid, CurrentVersion.ServiceId);
                    }
                }
            }
            else
            {

                srtdb_Insert( srtdbids_BatECNTable, CurrentVersion.Onid,
                                                        CurrentVersion.Tsid, CurrentVersion.ServiceId,
                                                        0 , (Address)(&CurrentVersion));

                strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batECN, dvb, bat),
                                                                    CurrentVersion.Onid, CurrentVersion.Tsid, CurrentVersion.ServiceId);

                TraceDebug(m,"Add ECN: BID 0x%x OIND 0x%x  TSID 0x%x SID 0x%x  ECN %d Ver %d", CurrentVersion.BouquetId, CurrentVersion.Onid , CurrentVersion.Tsid , CurrentVersion.ServiceId, TempLCNValue, CurrentVersion.VersionNumber);

            }
        }
        else
        {
            TraceNotice(m, "Invalid PDSD <0x%x>  For service - OIND 0x%x  TSID 0x%x SID 0x%x ",
                        BatTable->EutelsatChannelDescriptor[DescIndex].PrivateDataSpecifierValue,
                        BatTable->EutelsatChannelDescriptor[DescIndex].Onid,
                        BatTable->EutelsatChannelDescriptor[DescIndex].Tsid,
                        BatTable->EutelsatChannelDescriptor[DescIndex].ServiceId);
        }

		DescIndex++;
	}

	if(sec_TableCompleted & code)
	{
		/* Delete logical channels if not present */
		int TotalRecords = srtdb_GetNoOfRecords(srtdbids_BatECNTable) - 1;

		while( TotalRecords >= 0 )
		{
			if(srtdb_QueryOnIndex(srtdbids_BatECNTable,TotalRecords,(Address )(&DbaseVersion)))
			{
				if( (DbaseVersion.BouquetId == BatTable->BouquetId) &&
						(DbaseVersion.VersionNumber != BatTable->VersionNo))
				{
					/* delete the record */
					if (srtdb_Delete(srtdbids_BatECNTable, DbaseVersion.Onid, DbaseVersion.Tsid, DbaseVersion.ServiceId, DbaseVersion.ServiceId))
					{
						strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batECN, dvb, bat), DbaseVersion.Onid, DbaseVersion.Tsid, DbaseVersion.ServiceId);
					}
					else
					{  /* Could not delete */
						ASSERT(FALSE);
					}
				}
			}
			/* decrement to prev index*/
			TotalRecords--;
		}
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(batECN, dvb, bat));
	}
}
Bool CHsvDvbBAT_Priv::PopulateLinkageInfo ( HsvDemux dmx, TypeBat_Parser *BatTable, int code)
{
    return PopulateLinkageInfoPrivate(dmx, BatTable, HSVSPID(LinkageInfo, dvb, bat), srtdbids_BatLinkageInfoMain, code);
}

Bool CHsvDvbBAT_Priv::PopulateLinkageInfoPrivate ( HsvDemux dmx, TypeBat_Parser *BatTable, int Ppty, int tableid, int code)
{    
    Bool    retval  = TRUE;
    HSVSPTYPE(LinkageInfo, dvb, bat)  linkage;
    HSVSPTYPE(LinkageInfo, dvb, bat)  DbaseVersion;
    
    int i= 0;
    int tsloop = 0;	

    int HsvEvtNull = 0;
      if( sec_SctArrived & code )
    {
        for( i = 0; i < BatTable->LinkageDescNum; i++)
        {
            if(BatTable->Linkage_Descriptor[i].DescriptorValid)
            {
                    linkage.LinkageType        = (HsvLinkageType)BatTable->Linkage_Descriptor[i].LinkageType;
                    linkage.Original_NetworkId = BatTable->Linkage_Descriptor[i].ONID;
                    linkage.Tsid               = BatTable->Linkage_Descriptor[i].TSID;
                    linkage.ServiceId          = BatTable->Linkage_Descriptor[i].ServiceId;
                    //linkage.NetworkId          = BatTable->NetworkId;
                    linkage.VersionNumber      = BatTable->VersionNo;
					if(linkage.LinkageType == EPG_Service)
					{                
						if( srtdb_QueryOnKey( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&DbaseVersion)) )
						{
							/*Record exists. Update */
							if( srtdb_Update( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&linkage)))
							{                                            
								/* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/                  
									//printf("HYSVC : hsvdvbbat_m.c : strapiN called for LinkageInfo Onid = %d, Tsid = %d\n",linkage.Original_NetworkId, linkage.Tsid);
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
    
	while ( tsloop < BatTable->TsLoopDataNum)
	{
    
        for( i = 0; i < BatTable->TsLoopData[tsloop].LinkageDescNum; i++)
        {
            if(BatTable->TsLoopData[tsloop].Linkage_Descriptor[i].DescriptorValid)
            {
                    linkage.LinkageType        = (HsvLinkageType)BatTable->TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType;
                    linkage.Original_NetworkId = BatTable->TsLoopData[tsloop].Linkage_Descriptor[i].ONID;
                    linkage.Tsid               = BatTable->TsLoopData[tsloop].Linkage_Descriptor[i].TSID;
                    linkage.ServiceId          = BatTable->TsLoopData[tsloop].Linkage_Descriptor[i].ServiceId;
                    //linkage.NetworkId          = BatTable->NetworkId;
                    linkage.VersionNumber      = BatTable->VersionNo;
					if(linkage.LinkageType == EPG_Service)
					{
                                   
						if( srtdb_QueryOnKey( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),0, (Address)(&DbaseVersion)) )
						{
							/*Record exists. Update */
							if( srtdb_Update( tableid, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0, (Address)(&linkage)))
							{                                            
								/* "Changed" events require us to notify which field of a property has changed. For the moment, send out HsvEvtNull as the property*/                  
									//printf("HYSVC : hsvdvbbat_m.c : strapiN called for LinkageInfo Onid = %d, Tsid = %d\n",linkage.Original_NetworkId, linkage.Tsid);
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
                if(DbaseVersion.VersionNumber != BatTable->VersionNo)
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

Bool CHsvDvbBAT_Priv::mPopulateFreesatServiceGroupInfo( HsvDemux dmx, TypeBat_Parser *BatTable,  int code)
{
	HsvFreesatServiceGroupInfo DbaseVersion, CurrentVersion;
	Nat16 LoopIndex = 0;

	if(sec_SctArrived & code)
	{
		while(LoopIndex < BatTable->FreesatServiceGroupDescNum)
		{
			if(FREESAT_PDSD_VALUE == BatTable->FreesatServiceGroup_Descriptor[LoopIndex].PrivateDataSpecifier)
			{
				CurrentVersion.VersionNumber = BatTable->VersionNo;
				CurrentVersion.FreeSatelliteServiceIdentifier = BatTable->FreesatServiceGroup_Descriptor[LoopIndex].FreeSatelliteServiceIdentifier;
				CurrentVersion.FreeSatelliteServicegroupId = BatTable->FreesatServiceGroup_Descriptor[LoopIndex].FreeSatelliteServicegroupId;
				CurrentVersion.NonDestructiveTuneFlag = BatTable->FreesatServiceGroup_Descriptor[LoopIndex].NonDestructiveTuneFlag;
				CurrentVersion.ReturnChannelAccessFlag = BatTable->FreesatServiceGroup_Descriptor[LoopIndex].ReturnChannelAccessFlag;

				if (srtdb_QueryOnKey( srtdbids_BatFreesatSrvGroupTable, CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId, 0 , 0, (Address)(&DbaseVersion)))
				{
					//TraceNotice(m,"TMP_DEBUG Freesat service group updated Service Identifier %d Group ID %d", CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId);
					srtdb_Update(srtdbids_BatFreesatSrvGroupTable, CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId, 0 , 0, (Address)(&CurrentVersion) );
					strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatSrvGroup, dvb, bat), CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId, 0, CurrentVersion.FreeSatelliteServiceIdentifier);
				}
				else
				{
					//TraceNotice(m,"TMP_DEBUG Freesat service group added Service Identifier %d Group ID %d", CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId);
					srtdb_Insert( srtdbids_BatFreesatSrvGroupTable, CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId, 0 , 0, (Address)(&CurrentVersion));
					strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatSrvGroup, dvb, bat), CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId, 0);
				}
			}

			LoopIndex++;
		}
		/*reset descriptor count to avoid duplicate population*/
		BatTable->FreesatServiceGroupDescNum = 0;
	}
	if(sec_TableCompleted & code)
	{
		LoopIndex = srtdb_GetNoOfRecords(srtdbids_BatFreesatSrvGroupTable);
		while(LoopIndex > 0)
		{
			LoopIndex--;
			if(srtdb_QueryOnIndex(srtdbids_BatFreesatSrvGroupTable,LoopIndex,(Address )(&DbaseVersion)))
			{
				if(DbaseVersion.VersionNumber != BatTable->VersionNo)
				{
					strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatSrvGroup, dvb, bat), CurrentVersion.FreeSatelliteServiceIdentifier, CurrentVersion.FreeSatelliteServicegroupId, 0);
				}
			}
		}
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatSrvGroup, dvb, bat));
	}

	return TRUE;
}
Bool CHsvDvbBAT_Priv::mPopulateFreesatInfoLocationInfo( HsvDemux dmx, TypeBat_Parser *BatTable,  int code)
{
	HsvFreesatInfoLocation DbaseVersion, CurrentVersion;
	Nat16 LoopIndex = 0;

	
	if(sec_SctArrived & code)
	{

		/*TraceNotice(m,"mPopulateFreesatInfoLocationInfo %d code %d",BatTable->FreesatInfoLocationDescNum,\
																			code
																			);*/
		while(LoopIndex < BatTable->FreesatInfoLocationDescNum)
		{
			//TraceNotice(m,"pdsd %d",BatTable->FreesatInfoLocation_Descriptor[LoopIndex].PrivateDataSpecifier);
			if(FREESAT_PDSD_VALUE == BatTable->FreesatInfoLocation_Descriptor[LoopIndex].PrivateDataSpecifier)
			{
				CurrentVersion.VersionNumber = BatTable->VersionNo;
				CurrentVersion.OriginalNetworkId = BatTable->FreesatInfoLocation_Descriptor[LoopIndex].ONID;
				CurrentVersion.Tsid = BatTable->FreesatInfoLocation_Descriptor[LoopIndex].TSID;
				CurrentVersion.ServiceId = BatTable->FreesatInfoLocation_Descriptor[LoopIndex].ServiceId;

				if ( srtdb_QueryOnKey( srtdbids_BatFreesatInfoLocationTable, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId , 0, (Address)(&DbaseVersion) ) )
				{
					TraceNotice(m,"TMP_DEBUG Freesat Info location updated ONID 0x%x TSID 0x%x SID 0x%x",CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
					srtdb_Update(srtdbids_BatFreesatInfoLocationTable, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId,0,(Address)(&CurrentVersion) );
					strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatInfoLocation, dvb, bat), CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId, CurrentVersion.ServiceId);
				}
				else
				{
					TraceNotice(m,"TMP_DEBUG Freesat Info location added ONID 0x%x TSID 0x%x SID 0x%x",CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
					srtdb_Insert( srtdbids_BatFreesatInfoLocationTable, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId,CurrentVersion.ServiceId, (Address)(&CurrentVersion));
					strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatInfoLocation, dvb, bat), CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
				}
			}

			LoopIndex++;
		}
	}
	if(sec_TableCompleted & code)
	{
		LoopIndex = srtdb_GetNoOfRecords(srtdbids_BatFreesatInfoLocationTable);
		while(LoopIndex > 0)
		{
			LoopIndex--;
			if(srtdb_QueryOnIndex(srtdbids_BatFreesatInfoLocationTable,LoopIndex,(Address )(&DbaseVersion)))
			{
				if(DbaseVersion.VersionNumber != BatTable->VersionNo)
				{
					strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatInfoLocation, dvb, bat), DbaseVersion.OriginalNetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
				}
			}
		}
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatInfoLocation, dvb, bat));
	}
	return TRUE;
}

Bool CHsvDvbBAT_Priv::mPopulateFreesatLCN( HsvDemux dmx, TypeBat_Parser *BatTable,  int code)
{
	HsvFreesatLCN DbaseVersion, CurrentVersion;
	Nat16 LoopIndex = 0;
	Nat16 Loop1Index = 0;
	Nat16 Loop2Index = 0;
	Bool UpdateLCN = FALSE;

	if(sec_SctArrived & code)
	{
		while(LoopIndex < BatTable->TsLoopDataNum)
		{
			Loop1Index = 0;
			//TraceNotice(m,"TMP_DEBUG ONID 0x%x TSID 0x%x Total Number of service %d",BatTable->TsLoopData[LoopIndex].ONID, BatTable->TsLoopData[LoopIndex].TSID, BatTable->TsLoopData[LoopIndex].FreesatLCNDescNum);
			while(Loop1Index < BatTable->TsLoopData[LoopIndex].FreesatLCNDescNum)
			{
				/*global region ID 0x0000 (user customised) is not supported so ignore from populating*/
				if((FREESAT_PDSD_VALUE == BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].PrevPrivateDataSpecifier)
					&& (0x0000 != BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].RegionId))
				{
					Loop2Index = 0;
					CurrentVersion.VersionNumber = BatTable->VersionNo;
					CurrentVersion.FreeSatelliteServiceIdentifier =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].FreeSatelliteServiceIdentifier;
					CurrentVersion.OriginalNetworkId =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].ONID;
					CurrentVersion.Tsid =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].TSID;
					CurrentVersion.ServiceId =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].ServiceId;
					CurrentVersion.RegionId[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].RegionId;
					CurrentVersion.NumericSelectionFlag[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].NumericSelectionFlag;
					CurrentVersion.VisibleServiceFlag[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].VisibleServiceFlag;
					CurrentVersion.LogicalChannelNumber[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].LogicalChannelNumber;
					Loop2Index++;
					/*TraceNotice(m,"TMP_DEBUG Line %d SID 0x%x Freesat LCN %d RID %d ",__LINE__,
																	BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].ServiceId,
																	BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].LogicalChannelNumber,
																	BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].RegionId);*/

					while(Loop2Index < FREESAT_MAX_LCN_PER_SERVICE)
					{
						CurrentVersion.RegionId[Loop2Index] =  0;
						CurrentVersion.NumericSelectionFlag[Loop2Index] =  0;
						CurrentVersion.VisibleServiceFlag[Loop2Index] =  0;
						CurrentVersion.LogicalChannelNumber[Loop2Index] =  FREESAT_INVALID_LCN;
						Loop2Index++;
					}

					if ( srtdb_QueryOnKey( srtdbids_BatFreesatLCNTable, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId , 0, (Address)(&DbaseVersion) ) )
					{
						/*in Freesat service shall have multiple LCN
						**same service have muliple LCN in global region
						**Service may have different LCN in different region ID
						** if verison number are same then new entry shall be multiple LCN is global region
						**or different LCN in different region, so insert the new entry
						**
						*/
						UpdateLCN = TRUE;
						if(CurrentVersion.VersionNumber == DbaseVersion.VersionNumber)
						{
							UpdateLCN = FALSE;
							for(Loop2Index = 0; Loop2Index < FREESAT_MAX_LCN_PER_SERVICE; Loop2Index++)
							{
								if((BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].LogicalChannelNumber == DbaseVersion.LogicalChannelNumber[Loop2Index])
									&& (BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].RegionId == DbaseVersion.RegionId[Loop2Index]))
								{
									/*LCN already exist, so ignore*/
									break;
								}
								else if(FREESAT_INVALID_LCN == DbaseVersion.LogicalChannelNumber[Loop2Index])
								{
									CurrentVersion.RegionId[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].RegionId;
									CurrentVersion.NumericSelectionFlag[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].NumericSelectionFlag;
									CurrentVersion.VisibleServiceFlag[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].VisibleServiceFlag;
									CurrentVersion.LogicalChannelNumber[Loop2Index] =  BatTable->TsLoopData[LoopIndex].FreesatLCN_Descriptor[Loop1Index].LogicalChannelNumber;
									UpdateLCN = TRUE;
									break;
								}
								else
								{
									CurrentVersion.RegionId[Loop2Index] =  DbaseVersion.RegionId[Loop2Index];
									CurrentVersion.NumericSelectionFlag[Loop2Index] =  DbaseVersion.NumericSelectionFlag[Loop2Index];
									CurrentVersion.VisibleServiceFlag[Loop2Index] =  DbaseVersion.VisibleServiceFlag[Loop2Index];
									CurrentVersion.LogicalChannelNumber[Loop2Index] =  DbaseVersion.LogicalChannelNumber[Loop2Index];
								}
							}
						}

						if(UpdateLCN)
						{
							//TraceNotice(m,"TMP_DEBUG Line %d Freesat LCN updated for service 0x%x",__LINE__,CurrentVersion.ServiceId);
							srtdb_Update(srtdbids_BatFreesatLCNTable, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId,0,(Address)(&CurrentVersion) );
							strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLCN, dvb, bat), CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId, CurrentVersion.ServiceId);
						}
					}
					else
					{
						//TraceNotice(m,"TMP_DEBUG Line %d Freesat LCN added for service 0x%x",__LINE__,CurrentVersion.ServiceId);
						srtdb_Insert( srtdbids_BatFreesatLCNTable, CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId,CurrentVersion.ServiceId, (Address)(&CurrentVersion));
						strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLCN, dvb, bat), CurrentVersion.OriginalNetworkId, CurrentVersion.Tsid, CurrentVersion.ServiceId);
					}
				}
				Loop1Index++;
			}

			LoopIndex++;
		}
	}
	if(sec_TableCompleted & code)
	{
		LoopIndex = srtdb_GetNoOfRecords(srtdbids_BatFreesatLCNTable) ;
		while(LoopIndex > 0)
		{
			LoopIndex--;
			if(srtdb_QueryOnIndex(srtdbids_BatFreesatLCNTable,LoopIndex,(Address )(&DbaseVersion)))
			{
				if(DbaseVersion.VersionNumber != BatTable->VersionNo)
				{
					strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLCN, dvb, bat), DbaseVersion.OriginalNetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId);
				}
			}
		}
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatLCN, dvb, bat));
	}
	return TRUE;
}

/*****   External functions   *****/
void CHsvDvbBAT_Priv::pow_Init(void)
{
	int dmx;
	int      i;

	for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
	{
		DmxROMData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST;
		DmxROMData[dmx].SectionInfo = conf_BatParsing;
	}

	for(i=0; i<FILTER_DEPTH; i++)
	{
		ModeArray[i] = 0;
		MatchArray[i] = 0;
		MaskArray[i] = 0;
	}
	MatchArray[0] = BAT_TABLE_ID;
	MaskArray[0] = 0xff;
}

void CHsvDvbBAT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbBAT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbBAT_Priv::ena_Enable(HsvDemux dmx)
{
	int mode = 0,insMode = 0, state = 0;
	HsvSDMSIDataValues SiValues;
	Nat16	requestedBouquetId = INVALID_BOUQUET_ID, RequestedNid = 0;
	int mInstalledPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	
	InitLinkageInfo(dmx);
	TraceNotice (m, "BAT Requested ");
	ins_GetCurrentInstallationState (&insMode, &state);
	if (insMode == ins_InstallationPreScan)
	{
		ins_GetSITableIds(&RequestedNid, &requestedBouquetId);
	}
	else
	{
		TraceNotice(m,"Requested for Get Si Details");
		SiValues.TableId = BAT_TABLE_ID;
		ins_GetSIDetails(&SiValues);
		requestedBouquetId = SiValues.BouquetId;
	}

	mInitBatLCN(dmx);
	InitActualServiceListDS(dmx);
	InitActualBouquetId(dmx);

	mInitBatLCN2(dmx);						/*CYFRA*/
	mInitBatLCNV2(dmx);						/*NTV+*/
	mInitBatECN(dmx);						/*FRANSAT-ECD-> Eutelsat Channel Descriptor*/
	mInitBatDetails(dmx)	;				/*FRANSAT-BatInfo - Contains overall Bouquet Information*/
	mInitBatFreesatSrvGroupTable(dmx);
	mInitBatFreesatInfoLocationTable(dmx);
	mInitBatFreesatLCNTable(dmx);
	mInitBatMulLCNV2(dmx);					/*TRICOLOR USES MULIPLE LCN V2*/
	mInitBatTricolorLRNDetails(dmx); 		/*TRICOLOR USES BAT LOGICAL_REGION_NAME_DESCRIPTOR */	
	
	
	
	TraceNotice (m, "Requested Bouquet Id 0x%x INVALID 0x%x mode %d", requestedBouquetId, INVALID_BOUQUET_ID,mode);

	/* For bat requested case, in case of package build mode all available BAT in homing mux needs to be collected
	** so bouquet ID passed is invalid */
	if (conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo))
	{	
		TraceNotice(m,"TMP_DEBUG call get mode");
		mode = ctrl_GetMode( dmx );
		TraceNotice (m, "TMP_DEBUG SDM mode recived %d",mode);

		/*for NTV+ Collect all tables */
		/*Incase fransat is added back - Requesting in pkgbuildmode will fail, 
		  because pkgbuild mode will go for only particular BID, this change needed for TRICOLOR pkg.
		  So add a new collection mode when Fransat is added back*/
		  
		if(
			(mInstalledPackageId == NTVPLUS_PACKAGE_ID) ||
			( ((mInstalledPackageId == TRICOLOR_HD_PACKAGE_ID) || (mInstalledPackageId == TRICOLOR_SD_PACKAGE_ID)) && 
			   (ctrl_GetMode( dmx ) == ctrl_TricolorNormal)
			 )
		   )
		 {
			TraceDebug (m, "BAT Collection Triggered in Pkg build mode - Bouquet Id 0x%x ", requestedBouquetId);
			//DmxROMData[dmx].SubscrId = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)BAT_PID_VALUE, BAT_TABLE_ID, (int)requestedBouquetId, (HsvSectionCallback)Bat_Parser_Parser);
			HsvSectionFilterConfig SctConfig = {DMX_BUFFER_SIZE, HsvCrcModeSkipBadSections, TRUE, BAT_TABLE_ID, BAT_PID_VALUE};
			#ifndef __cplusplus
			DmxROMData[dmx].SubscrId  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, (HsvSectionFilterCallback)Bat_Parser_Parser);
			#else
			DmxROMData[dmx].SubscrId  = sec_RequestSectionFilter(HSV_MAP_DMX_TO_DEST(dmx), &SctConfig, 12, ModeArray, MatchArray, MaskArray, FNADDR(Bat_Parser_Parser));
			#endif

		}
		else if((ctrl_FreesatNormal == mode) && (SiValues.Pid <= 0x1FFF))
		{
			DmxROMData[dmx].SubscrId = sec_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx),
																(int)SiValues.Pid,
																BAT_TABLE_ID,
																requestedBouquetId,
																(int)requestedBouquetId, FNADDR(Bat_Parser_Parser));
			TraceNotice (m, "BAT collection started for Freesat Normal mode, PID 0x%x Bouquet ID %d",SiValues.Pid,requestedBouquetId);
		}
		else{
			if(requestedBouquetId != INVALID_BOUQUET_ID){
				TraceNotice (m, "BAT Collection Triggered for Bouquet Id 0x%x ", requestedBouquetId);
				#ifndef __cplusplus
				DmxROMData[dmx].SubscrId = sec_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx), (int)BAT_PID_VALUE, BAT_TABLE_ID, requestedBouquetId, (int)requestedBouquetId, (HsvSectionCallback)Bat_Parser_Parser);
				#else
				DmxROMData[dmx].SubscrId = sec_RequestSection2(HSV_MAP_DMX_TO_DEST(dmx), (int)BAT_PID_VALUE, BAT_TABLE_ID, requestedBouquetId, (int)requestedBouquetId, FNADDR(Bat_Parser_Parser));
				#endif
			}
		}
	}
}


void CHsvDvbBAT_Priv::ena_Disable(HsvDemux dmx)
{
	mInitBatLCN(dmx);
	InitActualServiceListDS(dmx);
	InitLinkageInfo(dmx);
	InitActualBouquetId(dmx);
	
    /* Initialise Sections */
	if(conf_IsActionAllowed(dmx, DmxROMData[dmx].SectionInfo))  
	{
		if( DmxROMData[dmx].SubscrId != HSV_INVALID_SCT_REQUEST )
		{
			sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxROMData[dmx].SubscrId);
			DmxROMData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST ;
		}
	}
}

Bool CHsvDvbBAT_Priv::PopulateActualServiceListDS( HsvDemux dmx, TypeBat_Parser *BatTable, int code)
{
    return PopulateServiceListDS(dmx, BatTable, HSVSPID(ActualServiceList, dvb, bat), srtdbids_BatSrvclstTableMain, code);
}

Bool CHsvDvbBAT_Priv::PopulateServiceListDS ( HsvDemux dmx, TypeBat_Parser *BatTable, int Ppty, int tableid, int code)
{
    HsvBATServiceList DbaseVersion, TempVersion; 
    int i= 0;
    int tsloop = 0; 
    int j = 0;
int from = 0; int to = 0;
    //TraceInfo(m,"Function : %s Line : %d",__FUNCTION__,__LINE__);
    while ( tsloop < BatTable->TsLoopDataNum)
    {
        if( sec_SctArrived & code )
        {

            int NumSRVCLISTInfo = BatTable->TsLoopData[tsloop].ServiceListDescNum;
			TraceNotice(m,"NumSRVCLISTInfo %d",NumSRVCLISTInfo);

            for( i = 0; i < NumSRVCLISTInfo; i++)
            {
            	TraceNotice(m,"BatTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListLen %d",BatTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListLen);
                if(BatTable->TsLoopData[tsloop].Service_List_Descriptor[i].DescriptorValid)
                {
                    for( j = 0; j < BatTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListLen ; j++)
                    {

                        DbaseVersion.BouquetId          = BatTable->BouquetId;
                        DbaseVersion.Original_NetworkId = BatTable->TsLoopData[tsloop].ONID;
                        DbaseVersion.Tsid               = BatTable->TsLoopData[tsloop].TSID;
                        DbaseVersion.ServiceId          = BatTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListDesc[j].ServiceId;;
                        DbaseVersion.ServiceType      = BatTable->TsLoopData[tsloop].Service_List_Descriptor[i].ServiceListDesc[j].ServiceType;          ;
                        DbaseVersion.VersionNumber      = BatTable->VersionNo;
				
						TraceInfo(m,"type %d id %d onid %d tsid %d",DbaseVersion.ServiceType,DbaseVersion.ServiceId,DbaseVersion.Original_NetworkId,DbaseVersion.Tsid );
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
							 if ( srtdb_QueryOnKey( tableid, DbaseVersion.Original_NetworkId, DbaseVersion.Tsid, DbaseVersion.ServiceId , 0, (Address)(&TempVersion) ) )
                        {
                            /* Record Exists - Update the information & notify if needed*/
                            //if(DbaseVersion.NetworkId == NITTable->NITHEADER.Attrib)

                            
                        }
						else
						{
							
						}
                        }
						
						
						 strapi_GetRangeByKey( HSV_MAP_DMX_TO_DEST(dmx), Ppty,2, DbaseVersion.Original_NetworkId,  DbaseVersion.Tsid, 0, &from, &to);
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
		
		TraceNotice(m,"Number of records in Bat %d",srtdb_GetNoOfRecords(tableid));
        while( 0 <= j )
        {
            if(srtdb_QueryOnIndex(tableid,j,(Address )(&DbaseVersion)))
            {
                if(( DbaseVersion.BouquetId == BatTable->BouquetId) &&
                        ( DbaseVersion.VersionNumber != BatTable->VersionNo))
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


void CHsvDvbBAT_Priv::ena_Sync(HsvDemux dmx)
{
   UNUSED( dmx );
}


Bool CHsvDvbBAT_Priv::ipop_PopulateBAT ( HsvDemux dmx , Address pBat_Parser, int code )
{
    int retval = TRUE, mode, state, mInstalledPackageId;
    TypeBat_Parser* BatTable = (TypeBat_Parser*)pBat_Parser;

	ins_GetCurrentInstallationState (&mode, &state);
	mInstalledPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	
	
	/*during package build mode installation mode will be idle*/
	if (ctrl_PkgBuildMode == ctrl_GetMode( dmx )) 
	{
		if((TRICOLOR_HD_PACKAGE_ID == mInstalledPackageId) || (TRICOLOR_SD_PACKAGE_ID == mInstalledPackageId))
		{
			TraceNotice(m, "Tricolor Region Scan mode Bouquet ID %d", BatTable->BouquetId);	
			mPopulateBouquetDetails( dmx, BatTable, code);	
			/* Added for Russia Tricolor Region name parsing */
			mPopulateTricolorLRNDetails (dmx, BatTable, code);

		}
		else
		{
			/* In pakage build mode, no need to populate other details, since
			* for package list no other details required
			*/
			mPopulateBouquetDetails( dmx, BatTable, code);
		}
			
	}
	else if ((ctrl_TricolorNormal == ctrl_GetMode(dmx))&& (mInstalledPackageId == TRICOLOR_SD_PACKAGE_ID) || (mInstalledPackageId == TRICOLOR_HD_PACKAGE_ID))
	{
		mPopulateBouquetDetails( dmx, BatTable, code);
		mPopulateTricolorLCNV2( dmx, BatTable, code);
		PopulateActualBouquetId(dmx, BatTable, code);
		PopulateLinkageInfo(dmx, BatTable, code);
		PopulateActualServiceListDS(dmx, BatTable, code);
	}
	else if ((mInstalledPackageId != NTVPLUS_PACKAGE_ID) || (IS_NTVPLUS_BAT(BatTable->BouquetId))) /*RMCR - 768*/
	{
		TraceNotice(m, "Populating BAT with BouquetId : %d", BatTable->BouquetId);
		//if((mode == ins_InstallationServiceScan) || (mode == ins_InstallationUpdate)  || (mode == ins_InstallationBackgroundUpdate))
		{
			mPopulateBouquetDetails( dmx, BatTable, code);

			mPopulateNetworkLCN( dmx, BatTable, code);
			mPopulateNetworkLCN2( dmx, BatTable, code);							/*cyfra*/
			mPopulateNetworkLCNV2( dmx, BatTable, code);							/*NTV+*/
			PopulateLinkageInfo(dmx, BatTable, code);
			PopulateActualServiceListDS(dmx, BatTable, code);
            PopulateActualBouquetId(dmx, BatTable, code);

			/* If Eutelsat channel descriptor presents then only we have to populate */
			if( BatTable->TotalNoOfEutelsatDesc )
			{
				mPopulateEutelsatChannelList( dmx,BatTable,code);
			}

			mPopulateFreesatServiceGroupInfo(dmx, BatTable, code);
			mPopulateFreesatInfoLocationInfo(dmx, BatTable, code);
			mPopulateFreesatLCN(dmx, BatTable,  code);
		}
	}
	else
	{
		TraceNotice(m, "Ignored BAT with BouquetId : %d", BatTable->BouquetId);
	}

	if( sec_TableCompleted & code )
    {		
    	
		if( ctrlN_iPresent())
		{
		
			TraceNotice(m,"debug: DataAvailable triggerd for BAT");
			ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_BAT);
		}
    }

	return retval;
}


/*************************************************************/
void CHsvDvbBAT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    int dmx = HsvDmxMain;

    for(  dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {
        if( DmxROMData[dmx].SubscrId == subscrid )
        {
            /* This was a matching request. Clear our local variables */
            DmxROMData[dmx].SubscrId  = HSV_INVALID_SCT_REQUEST;
        }
    }

}

int CHsvDvbBAT_Priv::strapi_GetSize(HsvDestination inst, int prop)
{
    int retval = 0;
    
	UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(batLCN,dvb,bat):
			retval = srtdb_GetNoOfRecords(srtdbids_BatLcnTable); 
			break;
		case HSVSPID(ActualServiceList, dvb, bat): 
            retval = srtdb_GetNoOfRecords(srtdbids_BatSrvclstTableMain); 
			break;
		case HSVSPID(batLCN2,dvb,bat):
			retval = srtdb_GetNoOfRecords(srtdbids_BatLcn2Table); 
			break;
		case HSVSPID(batLCNV2,dvb,bat):
			retval = srtdb_GetNoOfRecords(srtdbids_BatLCNV2Table); 
			break;
		case HSVSPID(batMulLCNV2,dvb,bat):
			retval = srtdb_GetNoOfRecords(srtdbids_BatMulLCNV2Table); 
			break;
		case HSVSPID(LinkageInfo, dvb, bat): 
            retval = srtdb_GetNoOfRecords(srtdbids_BatLinkageInfoMain);
            break;
	case HSVSPID(batECN, dvb, bat):
		retval = srtdb_GetNoOfRecords(srtdbids_BatECNTable);
		break;

	case HSVSPID(batDetails, dvb, bat):
		retval = srtdb_GetNoOfRecords(srtdbids_BatDetailsTable);
		break;
	case HSVSPID(FreesatSrvGroup, dvb, bat):
		retval = srtdb_GetNoOfRecords(srtdbids_BatFreesatSrvGroupTable);
		break;
	case HSVSPID(FreesatInfoLocation, dvb, bat):
		retval = srtdb_GetNoOfRecords(srtdbids_BatFreesatInfoLocationTable);
		break;
	case HSVSPID(FreesatLCN, dvb, bat):
		retval = srtdb_GetNoOfRecords(srtdbids_BatFreesatLCNTable);
		break;
	case HSVSPID(TricolorLRN, dvb, bat):
	case HSVSPID(TricolorRegionName,dvb,bat):
		retval = gRegionNameList.TotalChannelListCount;
		break;
		default:
			break;
	}
	return retval;
}

Bool CHsvDvbBAT_Priv::strapi_GetIndex(HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(batLCN,dvb,bat):
			srtdb_SearchOnKey(srtdbids_BatLcnTable, key1, key2, key3,0, (int *)&index);
			break;
		case HSVSPID(ActualServiceList, dvb, bat): 
            srtdb_SearchOnKey(srtdbids_BatSrvclstTableMain,key1, key2, key3, 0,(int *)&index);

			break;
		case HSVSPID(batLCN2,dvb,bat):
			srtdb_SearchOnKey(srtdbids_BatLcn2Table, key1, key2, key3,0, (int *)&index);
			break;
		case HSVSPID(batLCNV2,dvb,bat):
			srtdb_SearchOnKey(srtdbids_BatLCNV2Table, key1, 0, 0 ,0, (int *)&index);
			break;
		case HSVSPID(batMulLCNV2,dvb,bat):
			srtdb_SearchOnKey(srtdbids_BatMulLCNV2Table, key1, 0, 0 ,0, (int *)&index);
			break;
		case HSVSPID(LinkageInfo, dvb, bat): 
            srtdb_SearchOnKey(srtdbids_BatLinkageInfoMain, key1, key2, key3, 0,(int *)&index);
            break;
	case HSVSPID(batECN, dvb, bat):
		srtdb_SearchOnKey(srtdbids_BatECNTable, key1, key2, key3, 0,(int *)&index);
		break;

	case HSVSPID(batDetails, dvb, bat):
		srtdb_SearchOnKey(srtdbids_BatDetailsTable, key1, 0, 0, 0,(int *)&index);
		break;
	case HSVSPID(FreesatSrvGroup, dvb, bat):
		srtdb_SearchOnKey(srtdbids_BatFreesatSrvGroupTable, key1, key2, 0, 0,(int *)&index);
		break;
	case HSVSPID(FreesatInfoLocation, dvb, bat):
		srtdb_SearchOnKey(srtdbids_BatFreesatInfoLocationTable, key1, key2, key3, 0,(int *)&index);
		break;
	case HSVSPID(FreesatLCN, dvb, bat):
		srtdb_SearchOnKey(srtdbids_BatFreesatLCNTable, key1, key2, key3, 0,(int *)&index);
		break;
		default:
			break;
	}
	return TRUE;
}

Bool CHsvDvbBAT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    int retval = 0;
	HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);
    
	UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(ActualBouquetId, dvb, bat) :
		{
			Nat16 *pval = (Nat16 *)val;
            *pval = DmxROMData[demux].BouquetId;
			retval = TRUE;
		}		
		break;
	
		case HSVSPID(batLCN,dvb,bat):
			retval = srtdb_QueryOnKey(srtdbids_BatLcnTable, key1, key2, key3, 0,(Address)val);
			break;
		case HSVSPID(ActualServiceList, dvb, bat): 
            retval = srtdb_QueryOnKey(srtdbids_BatSrvclstTableMain,key1, key2, key3, 0,(Address)val);

			break;
		case HSVSPID(batLCN2,dvb,bat):
			retval = srtdb_QueryOnKey(srtdbids_BatLcn2Table, key1, key2, key3, 0,(Address)val);
			break;
			
		case HSVSPID(batLCNV2,dvb,bat):
			retval = srtdb_QueryOnKey(srtdbids_BatLCNV2Table, key1, 0, 0, 0,(Address)val);
			break;
		case HSVSPID(batMulLCNV2,dvb,bat):
			retval = srtdb_QueryOnKey(srtdbids_BatMulLCNV2Table, key1, 0, 0, 0,(Address)val);
			break;
		case HSVSPID(LinkageInfo, dvb, bat): 
			retval = srtdb_QueryOnKey(srtdbids_BatLinkageInfoMain, key1, key2, key3,0, (Address)val);
			break;
	case HSVSPID(batECN, dvb, bat):
		retval = srtdb_QueryOnKey(srtdbids_BatECNTable, key1, key2, key3,0, (Address)val);
		break;

	case HSVSPID(batDetails, dvb, bat):
		/* Bouquet id is primary key and it is only the key mapped so all other keys given as 0 */
		retval = srtdb_QueryOnKey(srtdbids_BatDetailsTable, key1, 0, 0, 0, (Address)val);
		break;
	case HSVSPID(FreesatSrvGroup, dvb, bat):
		retval = srtdb_QueryOnKey(srtdbids_BatFreesatSrvGroupTable, key1, key2, 0,0, (Address)val);
		break;
	case HSVSPID(FreesatInfoLocation, dvb, bat):
		retval = srtdb_QueryOnKey(srtdbids_BatFreesatInfoLocationTable, key1, key2, key3,0, (Address)val);
		break;
	case HSVSPID(FreesatLCN, dvb, bat):
		retval = srtdb_QueryOnKey(srtdbids_BatFreesatLCNTable, key1, key2, key3,0, (Address)val);
		break;
		default:
			break;
	}
	return retval;
}

Bool CHsvDvbBAT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    int retval = 0;
    
	UNUSED (inst);
    switch (prop)
    {
		case HSVSPID(batLCN,dvb,bat):
			retval = srtdb_QueryOnIndex(srtdbids_BatLcnTable, index, (Address)val);
			break;
		case HSVSPID(ActualServiceList, dvb, bat):
			retval = srtdb_QueryOnIndex(srtdbids_BatSrvclstTableMain, index, (Address)val);
			break;
		case HSVSPID(batLCN2,dvb,bat):
			retval = srtdb_QueryOnIndex(srtdbids_BatLcn2Table, index, (Address)val);
			break;
		case HSVSPID(batLCNV2,dvb,bat):
			retval = srtdb_QueryOnIndex(srtdbids_BatLCNV2Table, index, (Address)val);
			break;
		case HSVSPID(batMulLCNV2,dvb,bat):
			retval = srtdb_QueryOnIndex(srtdbids_BatMulLCNV2Table, index, (Address)val);
			break;
		case HSVSPID(LinkageInfo, dvb, bat): 
            retval = srtdb_QueryOnIndex(srtdbids_BatLinkageInfoMain, index, (Address)val);
            break;
	case HSVSPID(batECN, dvb, bat):
		retval = srtdb_QueryOnIndex(srtdbids_BatECNTable, index, (Address)val);
		break;

	case HSVSPID(batDetails, dvb, bat):
		retval = srtdb_QueryOnIndex(srtdbids_BatDetailsTable, index,(Address)val);
		break;
	case HSVSPID(FreesatSrvGroup, dvb, bat):
		retval = srtdb_QueryOnIndex(srtdbids_BatFreesatSrvGroupTable, index,(Address)val);
		break;
	case HSVSPID(FreesatInfoLocation, dvb, bat):
		retval = srtdb_QueryOnIndex(srtdbids_BatFreesatInfoLocationTable, index,(Address)val);
		break;
	case HSVSPID(FreesatLCN, dvb, bat):
		retval = srtdb_QueryOnIndex(srtdbids_BatFreesatLCNTable, index,(Address)val);
		break;
	case HSVSPID(TricolorLRN, dvb, bat):
		//TraceNotice(m,"gRegionNameList.TotalChannelListCount %d",gRegionNameList.TotalChannelListCount);
		if (index < gRegionNameList.TotalChannelListCount)
		{
			Nat16 *pval = (Nat16*)val;  
			//TraceNotice(m,"region name %s namelength %d",gRegionNameList.ChannelListData[index].regionNameTranslation,(gRegionNameList.ChannelListData[index].regionNameTranslationLength));
			memcpy(pval,gRegionNameList.ChannelListData[index].regionNameTranslation,(gRegionNameList.ChannelListData[index].regionNameTranslationLength * sizeof(Nat16)));
			
			retval =  gRegionNameList.ChannelListData[index].regionNameTranslationLength;
		}
		break;
	case HSVSPID(TricolorRegionName,dvb,bat):
		TraceNotice(m,"gRegionNameList.TotalChannelListCount %d",gRegionNameList.TotalChannelListCount);
		if(index < gRegionNameList.TotalChannelListCount)
		{
			HsvTricolorRegionNameData *pval = (HsvTricolorRegionNameData*) val;
			TraceNotice(m,"region name %s namelength %d",gRegionNameList.ChannelListData[index].regionName,\
				                                         gRegionNameList.ChannelListData[index].regionNameLength);
														
			memcpy(pval->regionName,gRegionNameList.ChannelListData[index].regionName,(gRegionNameList.ChannelListData[index].regionNameLength * sizeof(char)));
			pval->regionNameLength = gRegionNameList.ChannelListData[index].regionNameLength;

			retval = TRUE;
		}
		break;
		default:
			break;
	}
	return retval;
}
Bool CHsvDvbBAT_Priv::strapi_GetRangeByKey( HsvDestination dest, int prop, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	Bool retval = FALSE;
    
	UNUSED (dest);
    switch (prop)
    {
		case HSVSPID(ActualServiceList, dvb, bat):
			if(noofkeys == 2)
			{
				TraceInfo(m,"Number of records in Bat %d",srtdb_GetNoOfRecords(srtdbids_BatSrvclstTableMain));
				/*TODO: Servicelist has to be populated from BAT*/
				
				retval = srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_BatSrvclstTableMain, key1, key2, from, to );
				
				TraceInfo(m,"Bat from %d to %d",*from,*to);
		}
		else
		{
			ASSERT(FALSE);
		}
		break;
	case HSVSPID(batECN, dvb, bat):
		if(noofkeys == 2)
		{
			TraceDebug(m,"Number of records in Bat %d",srtdb_GetNoOfRecords(srtdbids_BatECNTable));
			/*TODO: Servicelist has to be populated from BAT*/

			retval = srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_BatECNTable, key1, key2, from, to );
			}
			else
			{
				ASSERT(FALSE);
			}
			break;
		/*case HSVSPID(ActualNetworkLCN2,dvb,nit):
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
			break;*/
		default:
            ASSERT(FALSE);
            break;
	}
	
//	PrintfNotice(" noofkeys = %d prop = %d key1 = %d key2 = %d from =%d to %d retval = %d ",noofkeys,prop,key1,key2,*from,*to,retval);
	return retval;

}

Bool CHsvDvbBAT_Priv::Bat_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{	
	TraceNotice(m,"Bat Parser Triggered");
    register Nat8 *ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    TypeBat_Parser  Bat_Parser;
    Bool retval = TRUE;
    int installedPackageId,state,insMode;
    int dummy, loopcount = 0, descTag, descLen = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0,loop2index = 0, tableLen = 0, loop1length = 0,loop2length = 0, templen = 0; 
	Nat16 ServiceId = 0xFFFF;
	Nat16 FreesatServiceIdentifier = 0xFFFF;
	Nat16 ServiceGroupId = 0xFFFF;
	Nat8 NonDestructiveTuneFlag = 0;
	Nat8 ReturnChannelAccessFlag = 0;
	Nat8 AllocationUnit = 0;
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
   	Bat_Parser.LinkageDescNum=0;
	Bat_Parser.TotalNoOfEutelsatDesc = 0; /* Fransat - Init */
	Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue = 0;/* Fransat - Init */
	Bat_Parser.LCNV2DescNum = 0;
	Bat_Parser.TricolorLRN_DescNum = 0;
	Bat_Parser.FreesatInfoLocationDescNum = 0;
	Bat_Parser.FreesatServiceGroupDescNum = 0;
	Bat_Parser.FreesatInteractiveStorageDescNum = 0;
   	Bat_Parser.TsLoopDataNum=0;
    Bat_Parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    Bat_Parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    Bat_Parser.BouquetId = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    Bat_Parser.VersionNo = GETNBITS(v32,18,5);
    dummy = GETNBITS(v32,23,1);
    dummy = GETNBITS(v32,24,8);
    v32 = GET32( 7);
    dummy = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,4);
    Bat_Parser.BouquetDescLen = GETNBITS(v32,12,12);
    ptr += 10;
    tableLen = tableLen - 10;
    
    installedPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
	ins_GetCurrentInstallationState (&insMode, &state);
	
	
	TraceNotice(m,"%d Bid %d",__LINE__,Bat_Parser.BouquetId);

	if(((installedPackageId == TRICOLOR_SD_PACKAGE_ID) || (installedPackageId == TRICOLOR_HD_PACKAGE_ID)) && \ 
		((ctrl_GetMode(demux) == ctrl_TricolorNormal) || (ctrl_GetMode(demux) == ctrl_PkgBuildMode))) 
	{
		if(!(IS_TRICOLOR_VALID_BID(Bat_Parser.BouquetId)))
		{
			return TRUE;
		}
				
    }
    v32 = GET32( 0);
	TraceNotice(m,"Section Len %d Bid %d BoquetDescLen %d Bat_Parser.VersionNo %d",Bat_Parser.SectionLen,Bat_Parser.BouquetId,Bat_Parser.BouquetDescLen,Bat_Parser.VersionNo);
    while(loopcount < Bat_Parser.BouquetDescLen)
    {
        descLoopLen = 0;
        descTag = GETNBITS(v32,0, 8); 
        descLen = GETNBITS(v32,8, 8);
		TraceNotice(m,"DescTag 0x%x DescLen %d",descTag,descLen);
        switch(descTag) 
		{
	        case 0x47:
	             Bat_Parser.BouquetName_Descriptor.DescriptorTag = GETNBITS(v32,0,8);
	             Bat_Parser.BouquetName_Descriptor.DescriptorLen = GETNBITS(v32,8,8);
	             //Bat_Parser.BouquetName_Descriptor.BouquetNameLen = GETNBITS(v32,16,0);
	             Bat_Parser.BouquetName_Descriptor.BouquetNameLen = descLen;
	             descLoopLen = HSV_PARSER_MIN(MAX_BOUQUET_NAME_LEN,Bat_Parser.BouquetName_Descriptor.BouquetNameLen); 
	             ptr += 2;
	             memcpy(Bat_Parser.BouquetName_Descriptor.BouquetName,ptr,descLoopLen);
				 Bat_Parser.BouquetName_Descriptor.BouquetName[ MAX_BOUQUET_NAME_LEN - 1 ] = '\0';
	             ptr += Bat_Parser.BouquetName_Descriptor.BouquetNameLen;
	             v32 = GET32( 0);
	             Bat_Parser.BouquetName_Descriptor.BouquetNameLen = descLoopLen;
	             Bat_Parser.BouquetName_Descriptor.DescriptorValid = TRUE;
	        	 loopcount += 2 + descLen;
	        	 tableLen = tableLen - (2 + descLen);
	        	 v32 = GET32( 0);
	        break;
	    
	        case 0x4A:
	        	if(Bat_Parser.LinkageDescNum<10)
	        	{
		             Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].DescriptorTag = GETNBITS(v32,0,8);
		             Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].DescriptorLen = GETNBITS(v32,8,8);
		             Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].TSID = GETNBITS(v32,16,16);
		             v32 = GET32( 4);
		             Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].ONID = GETNBITS(v32,0,16);
		             Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].ServiceId = GETNBITS(v32,16,16);
		             v32 = GET32( 8);
		             Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].LinkageType = GETNBITS(v32,0,8);
		             ptr += 2 + descLen;
					 v32 = GET32( 0);
		    		 Bat_Parser.Linkage_Descriptor[Bat_Parser.LinkageDescNum].DescriptorValid = TRUE;
		     		 Bat_Parser.LinkageDescNum++;
	    		}
	    		else
	     		{
	         		 ptr += 2 + descLen;
	     		}
	        	loopcount += 2 + descLen;
	        	tableLen = tableLen - (2 + descLen);
	        	v32 = GET32( 0);
	        break;
    
			case PRIVATE_DATA_SPECIFIER_DESCRIPTOR:
				Bat_Parser.PrivateDataSpecifierDescriptor.DescriptorTag = descTag;
				Bat_Parser.PrivateDataSpecifierDescriptor.DescriptorLen = descLen;
				v32 = GET32( 2);
				Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue = GETNBITS(v32,0,32);

				ptr += 2 + descLen;
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);

				v32 = GET32( 0);
			
			break;

			case 0x87: /* For Tricolor LCN v2 from BAT */
			{

				
				TraceNotice(m, "installedPackageId: %d , NTVPLUS_PACKAGE_ID: %d", installedPackageId, NTVPLUS_PACKAGE_ID);
				
				TraceNotice(m,"Installation Mode %d",insMode);
				 if (((installedPackageId == TRICOLOR_SD_PACKAGE_ID) || (installedPackageId == TRICOLOR_HD_PACKAGE_ID)) && (insMode != ins_InstallationStateRegionScan))
				 {
					 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
					 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorTag = GETNBITS(v32, 0,8);
					 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorLen = GETNBITS(v32, 8,8);
					 ptr += 2;
					 v32 = GET32( 0 );
					 loop1index = 0, loop1length = 0, templen = sizeof(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc);
					 
					 while( loop1length < HSV_PARSER_MIN(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorLen, templen))
					 {
						 int minLength = 0;
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_ID = GETNBITS(v32,0, 8); 
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth = GETNBITS(v32,8, 8); 
						 minLength = HSV_PARSER_MIN(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth,24);
						 TraceNotice(m,"debug :minlength used %d",minLength);
						 ptr += 2;
						 loop1length += 2;
						 memcpy(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_Name,ptr, minLength);
						 ptr += Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth;
						 loop1length += Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth;
						 //TraceNotice(m,"channel_list_id %d channel_list_name %s",Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_ID ,Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_Name);
						 v32 = GET32( 0);
						 // put logs and second thing check how federal check is added. and things installed 3 points
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Channel_List_NameLngth = minLength;
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].Country_Code = GETNBITS(v32,0, 24); 
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].DescriptorLen = GETNBITS(v32,24, 8); 
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].LCN2SvcDescLen = 0; /* GETNBITS(v32,32, 0); */ 
						 ptr += 4;
						 loop1length += 4;
						 v32 = GET32( 0 );
						 loop2index = 0, loop2length = 0, templen = sizeof(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc);
						 while( (loop2length < HSV_PARSER_MIN(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].DescriptorLen, templen))\
							     && \ 
							     (Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].DescriptorLen < Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorLen))
						 {
							 
							 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].LCN2SvcDesc[loop2index].ServiceId = GETNBITS(v32,0, 16);
							// TraceNotice(m,"service id: %d",Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].LCN2SvcDesc[loop2index].ServiceId);
							 loop2length += 2;
							 ptr += 2;
							 loop1length += 2;
							 v32 = GET32( 0);
							 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].LCN2SvcDesc[loop2index].Visibility = GETNBITS(v32,0,1);
							 dummy = GETNBITS(v32,1,5);
							 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].LCN2SvcDesc[loop2index].LCNValue = GETNBITS(v32,6,10);
							 loop2length += 2;
							 loop2index++;
							 ptr += 2;
							 loop1length += 2;
							 v32 = GET32( 0);
						 }
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelLstDesc[loop1index].LCN2SvcDescLen = loop2index;
						 loop1index++;
						 v32 = GET32( 0);
					 }
					 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2ChannelListLen = loop1index;
					 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorValid = TRUE;
					 Bat_Parser.LCNV2DescNum++;
				 }
				 else
				 {
					 ptr += 2 + descLen;
				 }
				 loopcount += 2 + descLen;
				 tableLen = tableLen - (2 + descLen);
				 v32 = GET32( 0);
			}	 
			break;
			
			case 0x83:
			{
				TraceNotice(m, "mInstalledPackageId: %d , NTVPLUS_PACKAGE_ID: %d", installedPackageId, NTVPLUS_PACKAGE_ID);
				 if(installedPackageId == NTVPLUS_PACKAGE_ID)
				 {
				 	 if(Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum<100)
					{
						 //Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorTag = GETNBITS(v32, 0,8);
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorLen = GETNBITS(v32, 8,8);
						 ptr += 2;
						 v32 = GET32( 0 );
						 loop1index = 0, loop1length = 0, templen = sizeof(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2Desc) ;
						 while( loop1length< HSV_PARSER_MIN(Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorLen, templen))
						 {
							int minLength = 0; int svcid, LCN;
							svcid = Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2Desc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
							LCN = Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2Desc[loop1index].LCNValue = GETNBITS(v32,16, 16);
							TraceNotice(m," Svcid: %d LCN : %d",svcid,LCN);
							loop1length += 4;
							loop1index++;
							ptr += 4;
							v32 = GET32( 0);
						 }
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].LCN2Len = loop1index;
						 Bat_Parser.LCNV2_Descriptor[Bat_Parser.LCNV2DescNum].DescriptorValid=TRUE ;
					  
						//Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrevPrivateDataSpecifier=GET_PREV_PRIVATE_DATA_SPECIFIER(ptr);

						Bat_Parser.LCNV2DescNum++;
					}
					else
					{
						ptr += 2 + descLen;
					}
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
				
					v32 = GET32( 0);
				}
				else if ((installedPackageId != TRICOLOR_SD_PACKAGE_ID) || \
	  					 (installedPackageId != TRICOLOR_HD_PACKAGE_ID)) /* Added for explicitly for Tricolor */
				{
		        /*check whether descriptor length is valid*/
	            if(!(descLen % 8))
				{

		                /*skip descriptor tag and descriptor length*/
		                ptr = ptr +2;
		                loop1index = 0;
		                while((loop1index  < descLen) && (Bat_Parser.TotalNoOfEutelsatDesc < MAX_ECN_SERVICES))
						{
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].PrivateDataSpecifierValue = Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue;
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].DescriptorTag = descTag;
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].DescriptorLen = descLen;

		                    v32 = GET32( 0);
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].Onid = GETNBITS(v32,0,16);
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].Tsid = GETNBITS(v32,16,16);

		                    v32 = GET32( 4);
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].ServiceId = GETNBITS(v32,0,16);
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].EutelsatChannelNum = GETNBITS(v32,16,12);

		                    Bat_Parser.TotalNoOfEutelsatDesc++;
		                    /*move to next service loop*/
		                    ptr += 8;
		                    loop1index += 8;

		                    TraceDebug(m,"ECN - Index %d Len %d Onid 0x%x TSID 0x%x Tsid 0x%x ECN %d Data 0x%x 0x%x",
		                    Bat_Parser.TotalNoOfEutelsatDesc,
		                    descLen,
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].Onid,
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].Tsid,
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].ServiceId,
		                    Bat_Parser.EutelsatChannelDescriptor[Bat_Parser.TotalNoOfEutelsatDesc].EutelsatChannelNum,
		                    GET32( 0),
		                    GET32( 4));

		                }
	            	}
	            	else
					{
	                	TraceNotice(m,"Invalid ECN descriptor, descriptor length %d",descLen);
						ptr += 2+ descLen;
					}
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
					loop1index = 0;
					v32 = GET32( 0);
				}
				else
				{
					ptr += 2+ descLen;
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
					v32 = GET32( 0);
				}
			}
			break;

		case FREESAT_INFO_LOCATION_DESCRIPTOR: /*free satellite info location descriptor*/
			 if(installedPackageId == FREESAT_PACKAGE_ID) 
			 {
			 	 TraceNotice(m,"FREESAT_INFO_LOCATION_DESCRIPTOR Entry");
				 v32 = GET32( 0);
				 loop1length = GETNBITS(v32,16,8);
				 /*Home loop length is skiped as per
				 **Free Satellite Requirements for Interoperability Part 3: System Management V1.6
				 */
				 ptr += 3 + loop1length;
				 v32 = GET32( 0);

				 loop2length = GETNBITS(v32,0,8);
				 ptr++;

				 loop2index = 0;

				while((Bat_Parser.FreesatInfoLocationDescNum < FREESAT_MAX_INFO_LOCATION_DESC_COUNT) && (loop2index < loop2length))
				{
					v32 = GET32( loop2index);
					Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].PrivateDataSpecifier = Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue;
					//TraceNotice(m,"%x %d",Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].PrivateDataSpecifier,Bat_Parser.FreesatInfoLocationDescNum);
					Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].DescriptorTag = descTag;
					Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].DescriptorLen = descLen;
					Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].TSID = GETNBITS(v32,0,16);
					Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].ONID = GETNBITS(v32,16,16);
					loop2index += 4;
					v32 = GET32( loop2index);
					Bat_Parser.FreesatInfoLocation_Descriptor[Bat_Parser.FreesatInfoLocationDescNum].ServiceId = GETNBITS(v32,0,16);
					loop2index += 2;
					Bat_Parser.FreesatInfoLocationDescNum++;
				}
				ptr += loop2length;
				v32 = GET32( 0);
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
			 }
			 else 
			 {
					ptr += 2+ descLen;
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
					v32 = GET32( 0);
			 }
			
			break;
			
		case FREESAT_SERVICEGROUP_DESCRIPTOR: /*free satellite servicegroup descriptor*/
			//TraceNotice(m,"FREESAT_SERVICEGROUP_DESCRIPTOR Entry");

			if(installedPackageId == FREESAT_PACKAGE_ID) 
			{
				descLoopLen = 0;
				ptr += 2;

				while(descLoopLen < descLen)
				{
					v32 = GET32( 0);
					NonDestructiveTuneFlag =  GETNBITS(v32,0,1);
					ReturnChannelAccessFlag =  GETNBITS(v32,1,1);
					ServiceGroupId = GETNBITS(v32,5,11);

					loop1length = GETNBITS(v32,16,8);
					loop1index = 0;
					ptr += 3;
					while((Bat_Parser.FreesatServiceGroupDescNum < FREESAT_SERVICEGROUP_DESC_COUNT) && (loop1index < loop1length))
					{
						v32 = GET32( loop1index);
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].PrivateDataSpecifier = Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue;
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].DescriptorTag = descTag;
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].DescriptorLen = descLen;
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].NonDestructiveTuneFlag = NonDestructiveTuneFlag;
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].ReturnChannelAccessFlag = ReturnChannelAccessFlag;
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].FreeSatelliteServicegroupId = ServiceGroupId;
						Bat_Parser.FreesatServiceGroup_Descriptor[Bat_Parser.FreesatServiceGroupDescNum].FreeSatelliteServiceIdentifier = GETNBITS(v32,1,15);
						Bat_Parser.FreesatServiceGroupDescNum ++;
						loop1index += 2;
					}

					descLoopLen += 3 + loop1length;
					ptr += loop1length;
				}

				v32 = GET32( 0);
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
			} else {
				ptr += 2+ descLen;
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
				v32 = GET32( 0);
			}
			//TraceNotice(m,"FREESAT_SERVICEGROUP_DESCRIPTOR Exit");
			break;

			case TRICOLOR_LOGICAL_REGION_NAME_DESCRIPTOR_TAG:
			
				TraceNotice(m,"Tricolor Region Name Descriptor Entry Bouquet ID - %d", Bat_Parser.BouquetId);

				if ((installedPackageId == TRICOLOR_SD_PACKAGE_ID) || (installedPackageId == TRICOLOR_HD_PACKAGE_ID))
				{
					int listCount = 0;
					int nameLength = 0;
					loop1length = 0;
					v32 = GET32(0);
					loop1index = 0;
					descLoopLen = 0;
					loop1length = descLen;
					loop2length = 0;
					ptr += 2;
					
					
					//TraceNotice(m,"loop1length %d\n",loop1length);
					/* Outer Loop for each ISO-639-2 language codes */
					while ((Bat_Parser.TricolorLRN_DescNum < TRICOLOR_MAX_ISO639_2_LANGUAGE_CODES) && (loop1index< loop1length)) 
					{
						Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].langCode[0] = *ptr; ptr++;
						Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].langCode[1] = *ptr; ptr++;
						Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].langCode[2] = *ptr; ptr++;
						//TraceNotice(m,"langCode %s Bat_Parser.TricolorLRN_DescNum %d \n",Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].langCode,Bat_Parser.TricolorLRN_DescNum);
						loop2length = *ptr; ptr++;
						loop2index = 0;
						
						//TraceNotice(m,"loop2length %d\n",loop2length);
						Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].channelListDetailNum = 0;
						/* Inner loop for getting all the channel list names and channel list name translations */
						while ((Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].channelListDetailNum < TRICOLOR_MAX_REGION_NAMES) && \
									(loop2index < loop2length))
						{
							nameLength = 0;
							//TraceNotice(m,"listCount %d\n",listCount);
							/* Setting with '\0' character to handle region name '\0' termination */
							memset (&Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount], '\0', \
								sizeof (Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[0]));
							
							Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameLength = *(ptr + loop2index);
						
							nameLength = Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameLength;
							nameLength = nameLength > TRICOLOR_MAX_REGION_NAME_LENGTH ? TRICOLOR_MAX_REGION_NAME_LENGTH : nameLength;

							//TraceNotice(m,"channelListNameLength %d\n",Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameLength);
							loop2index++;
							memcpy (Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListName,(ptr + loop2index),nameLength);
							//for(int i=0;i < Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameLength;i++)
							//{
								//TraceNotice(m,"channelListName 0x%x\n",Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListName[i]);
							//}
							loop2index += Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameLength;

							Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslationLength = *(ptr + loop2index);

							nameLength = Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslationLength;
							nameLength = nameLength > TRICOLOR_MAX_REGION_NAME_LENGTH ? TRICOLOR_MAX_REGION_NAME_LENGTH : nameLength;
							
							//TraceNotice(m,"channelListNameTransLength %d\n",Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslationLength);
							loop2index++;
							memcpy (Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslation,(ptr + loop2index),nameLength);
							//for(int i=0;i < Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslationLength;i++)
							//{
								//TraceNotice(m,"channelListNameTrans 0x%x\n",Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslation[i]);
							//}
							loop2index += Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].Tricolor_ChannelListDetails[listCount].channelListNameTranslationLength;

							Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].channelListDetailNum++;
							listCount = Bat_Parser.TricolorLRN_Descriptor[Bat_Parser.TricolorLRN_DescNum].channelListDetailNum;

							
						} 
						loop1index += 4;
						loop1index += loop2length;
						ptr += loop2length;
						Bat_Parser.TricolorLRN_DescNum++;
						
					} 
					tableLen = tableLen - (descLen + 2);
					loopcount += 2 + descLen;
					v32 = GET32( 0);
				}else {
					ptr += 2+ descLen;
					loopcount += 2 + descLen;
					tableLen = tableLen - (descLen + 2);
					v32 = GET32( 0);
				}
				
			break;

			default:
				tableLen = tableLen - (2 + descLen);
				loopcount += 2 + descLen;
				ptr += 2 + descLen;
				v32 = GET32( 0);
			break;
		}//endswitch
	} //endwhile

	/* We should not use the pds of first loop further in second loop */
	Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue = 0;

	dummy = GETNBITS(v32,0,4);
	//ipop_PopulateBAT(demux, &Bat_Parser, code);
	Bat_Parser.TsLoopLen = GETNBITS(v32,4,12);

	ptr += 2;
	tableLen = tableLen - 2;
	v32 = GET32( 0);

	TraceDebug(m,"Hsvdvbbat_mpar.c: %s:%d %d tablelen %d tsloopIndex %d\n",__FUNCTION__, __LINE__,code,tableLen,tsloopIndex);

	while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
	{
		Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum=0;
   		Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum=0;
		Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum=0;
		Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum=0;
		Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum = 0;
		Bat_Parser.TsLoopData[tsloopIndex].FreesatInteractiveRestrictionDescNum = 0;
        Bat_Parser.TsLoopData[tsloopIndex].TSID = GETNBITS(v32, 0,16);
        Bat_Parser.TsLoopData[tsloopIndex].ONID = GETNBITS(v32, 16,16);
        v32 = GET32( 4);
        dummy = GETNBITS(v32,0,4);
        Bat_Parser.TsLoopData[tsloopIndex].TsDescLoopLen = GETNBITS(v32, 4,12);
        ptr += 6;
        tableLen = tableLen - 6;
        v32 = GET32( 0);
        loopcount = 0;
        while(loopcount < Bat_Parser.TsLoopData[tsloopIndex].TsDescLoopLen)
        {
            descLoopLen = 0, loop1length = 0;
            descTag = GETNBITS(v32,0, 8); 
            descLen = GETNBITS(v32,8, 8); 
			
            switch(descTag) {
			case 0x82:
			{
						/*Ignore this descriptor for NTV+*/				
						if((Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum<100) && (installedPackageId != NTVPLUS_PACKAGE_ID))
						{
							//Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
							Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorTag = GETNBITS(v32, 0,8);
							Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen = GETNBITS(v32, 8,8);
							ptr += 2;
							v32 = GET32( 0 );
							loop1index = 0, loop1length = 0, templen = sizeof(Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Desc) ;
							while( loop1length< HSV_PARSER_MIN(Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen, templen))
							{
								int minLength = 0;
								Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Desc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
								Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Desc[loop1index].LCNValue = GETNBITS(v32,16, 16); 
								loop1length += 4;
								loop1index++;
								ptr += 4;
								v32 = GET32( 0);
							}
							Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Len = loop1index;
							Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorValid=TRUE ;

							//Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrevPrivateDataSpecifier=GET_PREV_PRIVATE_DATA_SPECIFIER(ptr);

							Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum++;
						}
						else
						{
							TraceNotice(m,"Ignoring 0x82 descriptor for NTV+");
							ptr += 2 + descLen;
						}
						loopcount += 2 + descLen;
						tableLen = tableLen - (2 + descLen);
						
					v32 = GET32( 0);
			}
			break;
            case 0x83:
			{
				if(installedPackageId == CYFRAPLUS_POLSAT_PACKAGE_ID)
				{
					 if(Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum<100)
					{
						//Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
						Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorTag = GETNBITS(v32, 0,8);
						Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen = GETNBITS(v32, 8,8);
						ptr += 2;
						v32 = GET32( 0 );
						loop1index = 0, loop1length = 0, templen = sizeof(Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Desc) ;
						while( loop1length< HSV_PARSER_MIN(Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorLen, templen))
						{
							int minLength = 0;
							Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Desc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
							Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Desc[loop1index].LCNValue = GETNBITS(v32,16, 16); 
							loop1length += 4;
							loop1index++;
							ptr += 4;
							v32 = GET32( 0);
						}
						Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].LCN2Len = loop1index;
						Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].DescriptorValid=TRUE ;

						//Bat_Parser.TsLoopData[tsloopIndex].LCN2_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum].PrevPrivateDataSpecifier=GET_PREV_PRIVATE_DATA_SPECIFIER(ptr);

						Bat_Parser.TsLoopData[tsloopIndex].LCN2DescNum++;
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
					if(Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum<100)
					{
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorTag = GETNBITS(v32, 0,8);
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen = GETNBITS(v32, 8,8);
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].Frequency = GETNBITS(v32, 16,16);
						 v32 = GET32( 4);
						 dummy = GETNBITS(v32, 0,7);
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].Polarization = GETNBITS(v32, 7,1);
						 ptr += 5;
						 v32 = GET32( 0 );
					 	 loop1index = 0, loop1length = 3, templen = sizeof(Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc) ;
						 while( loop1length< HSV_PARSER_MIN(Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen, templen))
						 {
						 int minLength = 0;
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
						 //Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].LCNValue = GetLCNValue( ptr, 16);
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].LCNValue = GETNBITS(v32,16, 16);
						 ptr += 4;
						 v32 = GET32(0);
						 loop1length += 4;
						 
						 if(loop1length < HSV_PARSER_MIN(Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen, templen))
						 {
						 	Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].DpServiceId = GETNBITS(v32,0, 16); 
						 	Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].DpTSId = GETNBITS(v32,16, 16);
						 	
							loop1length += 4;
							ptr += 4;
							v32 = GET32( 0);
						 }
						 //PrintfNotice("Nilanjan: ServiceId = %d LCNValue = %d", Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].ServiceId, Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].LCNValue);
						loop1index++;
						 
						 }
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNLen = loop1index;
						 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorValid = TRUE;
						 Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum++;
					}
					else
					{
						ptr += 2 + descLen;
					}
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
	
					v32 = GET32( 0);
				}
			}
            break;

			case 0x81:
            if(Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum<10)
            {
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].Frequency = 0xFFFF;
				 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].Polarization = 0xFFFF;
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc)*100 ;
                 while( loop1length< HSV_PARSER_MIN(Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorLen, templen))
                 {
                 int minLength = 0;
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].ServiceId = GETNBITS(v32,0, 16);  
				 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].LCNValue = GETNBITS(v32,16, 16);
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].DpServiceId = 0xFFFF;
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNDesc[loop1index].DpTSId = 0xFFFF;
                 loop1length += 4;
                 loop1index++;
                 ptr += 4;
                 v32 = GET32( 0);
                 }
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].LCNLen = loop1index;
                 Bat_Parser.TsLoopData[tsloopIndex].LCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum].DescriptorValid = TRUE;
                 Bat_Parser.TsLoopData[tsloopIndex].LCNDescNum++;
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
            if(Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum<100)
            {
                 Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                 Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen = GETNBITS(v32, 8,8);
				 //TraceNotice(m,"desc len %d",Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen);
                 ptr += 2;
                 v32 = GET32( 0 );
                 loop1index = 0, loop1length = 0, templen = sizeof(Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc);
                 while( loop1length< HSV_PARSER_MIN(Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorLen, templen))
                 {
					Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceId = GETNBITS(v32,0, 16); 
					Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceType = GETNBITS(v32,16, 8); 
					//TraceNotice(m,"sid 0x%x",Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListDesc[loop1index].ServiceId);
					loop1length += 3;
					loop1index++;
					ptr += 3;
					v32 = GET32( 0);
                 }
                 Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].ServiceListLen = loop1index;
                 Bat_Parser.TsLoopData[tsloopIndex].Service_List_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum].DescriptorValid = TRUE;
                 Bat_Parser.TsLoopData[tsloopIndex].ServiceListDescNum++;
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
				if(Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum<50)
				{
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorTag = GETNBITS(v32, 0,8);
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorLen = GETNBITS(v32, 8,8);
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].TSID = GETNBITS(v32, 16,16);
					v32 = GET32( 4);
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ONID = GETNBITS(v32, 0,16);
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ServiceId = GETNBITS(v32, 16,16);
					v32 = GET32( 8);
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].LinkageType = GETNBITS(v32, 0,8);
					
					ptr += 2 + descLen;
					v32 = GET32( 0);
					
					Bat_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorValid = TRUE;
					Bat_Parser.TsLoopData[tsloopIndex].LinkageDescNum++;
				}
				else
				{
					ptr += 2 + descLen;
				}
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
				
				v32 = GET32( 0);
				break;
				
			case FREESAT_REGIONALISED_LCN_DESCRIPTOR:	/*Free Satellite Regionalised logical channel descriptor*/
				//TraceNotice(m,"FREESAT_REGIONALISED_LCN_DESCRIPTOR Entry");

				if(installedPackageId == FREESAT_PACKAGE_ID) 
				{
					descLoopLen = 0;
					ptr +=2;
					//TraceNotice(m,"TMP_DEBUG %d  descLen %d",__LINE__,descLen);
					while(descLoopLen < descLen)
					{
						loop1length = 0;
						loop1index = 0;
						v32 = GET32( 0);
						ServiceId = GETNBITS(v32, 0,16);
						FreesatServiceIdentifier = GETNBITS(v32, 17,15);
						v32 = GET32( 4);
						loop1length = GETNBITS(v32, 0,8);

						ptr += 5;
						//TraceNotice(m,"TMP_DEBUG %d  loop1length %d",__LINE__,loop1length);
						while((Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum < FREESAT_REGIONALISED_LCN_DESC_COUNT) && (loop1index <  loop1length))
						{
							v32 = GET32( loop1index);
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].DescriptorTag = descTag;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].DescriptorLen = descLen;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].PrevPrivateDataSpecifier = Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].ONID = Bat_Parser.TsLoopData[tsloopIndex].ONID;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].TSID = Bat_Parser.TsLoopData[tsloopIndex].TSID;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].ServiceId = ServiceId;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].FreeSatelliteServiceIdentifier = FreesatServiceIdentifier;
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].NumericSelectionFlag = GETNBITS(v32, 0,1);
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].VisibleServiceFlag = GETNBITS(v32, 1,1);
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].UserCustomisableFlag = GETNBITS(v32, 2,1);
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].LogicalChannelNumber = GETNBITS(v32, 4,12);
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].RegionId = GETNBITS(v32, 16,16);
							#if 0
							TraceNotice(m,"V32 0x%x ONID %d TSID %d SID %d FID %d NSF %d VSF %d UCF %d LCN %d RID %d",v32,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].ONID ,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].TSID,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].ServiceId,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].FreeSatelliteServiceIdentifier,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].NumericSelectionFlag,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].VisibleServiceFlag,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].UserCustomisableFlag,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].LogicalChannelNumber,
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCN_Descriptor[Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum].RegionId);
							#endif
							Bat_Parser.TsLoopData[tsloopIndex].FreesatLCNDescNum ++;
							loop1index +=4;
						}

						ptr += loop1length;
						descLoopLen += 5 + loop1length;
					}
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
					v32 = GET32( 0);
				}else {
					ptr += 2 + descLen;
					loopcount += 2 + descLen;
					tableLen = tableLen - (2 + descLen);
					v32 = GET32( 0);
				}
				TraceNotice(m,"FREESAT_REGIONALISED_LCN_DESCRIPTOR Exit");
				break;
				
			case PRIVATE_DATA_SPECIFIER_DESCRIPTOR:

				Bat_Parser.PrivateDataSpecifierDescriptor.DescriptorTag = descTag;
				Bat_Parser.PrivateDataSpecifierDescriptor.DescriptorLen = descLen;
				v32 = GET32( 2);
				Bat_Parser.PrivateDataSpecifierDescriptor.PrivateDataSpecifierValue = GETNBITS(v32,0,32);

				ptr += 2 + descLen;
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
    	Bat_Parser.TsLoopDataNum = tsloopIndex;
    	//retval = retval && pop_PopulateBAT( &Bat_Parser );
		ipop_PopulateBAT(demux, &Bat_Parser, sec_SctArrived);
   		tsloopIndex = 0;
    }//endwhile tsloop
    dummy = GETNBITS(v32,0,32);
	/*Condition is removed to update the BAT name (BAT details) even if TS loop
	**length is zero, change is made during FRANSAT package implementation
	*/
		if((Bat_Parser.TsLoopLen == 0) && (code & sec_SctArrived))
		{
			/*This is required for Tricolor*/
			ipop_PopulateBAT(demux, &Bat_Parser, code);		
		}
		else if( code & sec_TableCompleted )
		{
			/* Passed code as 3rd parameter */
			ipop_PopulateBAT(demux, &Bat_Parser, sec_TableCompleted);
		}
	#if 0
		if( code & sec_TableCompleted )
		{
			/* Passed code as 3rd parameter */
			ipop_PopulateBAT(demux, &Bat_Parser, sec_TableCompleted);
		}
	#endif
	TraceNotice(m,"Code : %d",code);



	return TRUE;
} //end function

void CHsvDvbBAT_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
{
}

void CHsvDvbBAT_Priv::dmxsecfN_OnRequestNotAllowed ()
{
}


/* For the Tricolor ISO 639-2 Language code to Language ID mapping */
int CHsvDvbBAT_Priv::mGetLanguageId(char byte1, char byte2, char byte3)
{
    /* Return the language ID of the language corresponding to the three character code */
    /* The 3 character code conforms to the ISO 639-2 B naming convention and the language ID
     that is returned conforms to the integer identifiers defined in IHsvLanguageIds interface */
    int lngid = langid_LangUndefined;

    Nat8 ubyte1 = HSV_TO_LOWER(byte1);
    Nat8 ubyte2 = HSV_TO_LOWER(byte2);
    Nat8 ubyte3 = HSV_TO_LOWER(byte3);

    switch (HSV_MAKE_CHAR_MASK(ubyte1, ubyte2, ubyte3)) {
    case HSV_MAKE_CHAR_MASK('e','n','g'):
        lngid = langid_LangEnglish;
        break;
    case HSV_MAKE_CHAR_MASK('g','e','r'):
    case HSV_MAKE_CHAR_MASK('d','e','u'):
        lngid = langid_LangGerman;
        break;
    case HSV_MAKE_CHAR_MASK('s','w','e'):
        lngid = langid_LangSwedish;
        break;
    case HSV_MAKE_CHAR_MASK('i','t','a'):
        lngid = langid_LangItalian;
        break;
    case HSV_MAKE_CHAR_MASK('f','r','e'):
    case HSV_MAKE_CHAR_MASK('f','r','a'):
        lngid = langid_LangFrench;
        break;
    case HSV_MAKE_CHAR_MASK('s','p','a'):
    case HSV_MAKE_CHAR_MASK('e','s','l'):
    case HSV_MAKE_CHAR_MASK('e','s','p'):
        lngid = langid_LangSpanish;
        break;
    case HSV_MAKE_CHAR_MASK('c','z','e'):
    case HSV_MAKE_CHAR_MASK('c','e','s'):
        lngid = langid_LangCzech;
        break;
    case HSV_MAKE_CHAR_MASK('p','o','l'):
        lngid = langid_LangPolish;
        break;
    case HSV_MAKE_CHAR_MASK('t','u','r'):
        lngid = langid_LangTurkish;
        break;
    case HSV_MAKE_CHAR_MASK('r','u','s'):
        lngid = langid_LangRussian;
        break;
    case HSV_MAKE_CHAR_MASK('g','r','e'):
    case HSV_MAKE_CHAR_MASK('e','l','l'):
        lngid = langid_LangGreek;
        break;
    case HSV_MAKE_CHAR_MASK('b','a','q'):
    case HSV_MAKE_CHAR_MASK('e','u','s'):
        lngid = langid_LangBasque;
        break;
    case HSV_MAKE_CHAR_MASK('c','a','t'):
        lngid = langid_LangCatalan;
        break;
    case HSV_MAKE_CHAR_MASK('s','c','r'):
    case HSV_MAKE_CHAR_MASK('h','r','v'):
        lngid = langid_LangCroatian;
        break;
    case HSV_MAKE_CHAR_MASK('d','a','n'):
        lngid = langid_LangDanish;
        break;
    case HSV_MAKE_CHAR_MASK('d','u','t'):
    case HSV_MAKE_CHAR_MASK('n','l','d'):
        lngid = langid_LangDutch;
        break;
    case HSV_MAKE_CHAR_MASK('f','i','n'):
        lngid = langid_LangFinnish;
        break;
    case HSV_MAKE_CHAR_MASK('g','l','a'):
    case HSV_MAKE_CHAR_MASK('g','a','e'):
        lngid = langid_LangGaelic;
        break;
    case HSV_MAKE_CHAR_MASK('g','l','e'):
    case HSV_MAKE_CHAR_MASK('i','r','i'):
        lngid = langid_LangIrish;
        break;
    case HSV_MAKE_CHAR_MASK('g','l','g'):
        lngid = langid_LangGalligan;
        break;
    case HSV_MAKE_CHAR_MASK('n','o','r'):
        lngid = langid_LangNorwegian;
        break;
    case HSV_MAKE_CHAR_MASK('p','o','r'):
        lngid = langid_LangPortuguese;
        break;
    case HSV_MAKE_CHAR_MASK('s','c','c'):
    case HSV_MAKE_CHAR_MASK('s','r','p'):
        lngid = langid_LangSerbian;
        break;
    case HSV_MAKE_CHAR_MASK('s','l','o'):
    case HSV_MAKE_CHAR_MASK('s','l','k'):
        lngid = langid_LangSlovak;
        break;
    case HSV_MAKE_CHAR_MASK('s','l','v'):
        lngid = langid_LangSlovenian;
        break;
    case HSV_MAKE_CHAR_MASK('w','e','l'):
    case HSV_MAKE_CHAR_MASK('c','y','m'):
        lngid = langid_LangWelsh;
        break;
    case HSV_MAKE_CHAR_MASK('r','u','m'):
    case HSV_MAKE_CHAR_MASK('r','o','n'):
        lngid = langid_LangRomanian;
        break;
    case HSV_MAKE_CHAR_MASK('e','s','t'):
        lngid = langid_LangEstonian;
        break;
    case HSV_MAKE_CHAR_MASK('u','k','r'):
        lngid = langid_LangUkrainian;
        break;
    case HSV_MAKE_CHAR_MASK('a','r','a'):
        lngid = langid_LangArabic;
        break;
    case HSV_MAKE_CHAR_MASK('h','e','b'):
        lngid = langid_LangHebrew;
        break;
    case HSV_MAKE_CHAR_MASK('h','u','n'):
        lngid = langid_LangHungarian;
        break;
    case HSV_MAKE_CHAR_MASK('l','a','v'):
        lngid = langid_LangLatvian;
        break;
    case HSV_MAKE_CHAR_MASK('k','a','z'):
        lngid = langid_LangKazakh;
        break;
    case HSV_MAKE_CHAR_MASK('b','u','l'):
        lngid = langid_LangBulgarian;
        break;
    case HSV_MAKE_CHAR_MASK('c','h','n'):
        lngid = langid_LangSimplifiedchinese;
        break;
    case HSV_MAKE_CHAR_MASK('l','i','t'):
        lngid = langid_LangLithuanian;
        break;
    case HSV_MAKE_CHAR_MASK('q','a','a'):
    case HSV_MAKE_CHAR_MASK('Q','A','A'):
        lngid = langid_LangOriginalVersion;
        break;
    case HSV_MAKE_CHAR_MASK('u','n','d'):
    case HSV_MAKE_CHAR_MASK('U','N','D'):
        if (1) {
            lngid = langid_LangOriginalVersion;
        }
        break;
    case HSV_MAKE_CHAR_MASK('a','d',' '):
    case HSV_MAKE_CHAR_MASK('A','D',' '):
    case HSV_MAKE_CHAR_MASK('a','d','1'):
    case HSV_MAKE_CHAR_MASK('A','D','1'):
    case HSV_MAKE_CHAR_MASK('a','d','2'):
    case HSV_MAKE_CHAR_MASK('A','D','2'):
    case HSV_MAKE_CHAR_MASK('a','d','3'):
    case HSV_MAKE_CHAR_MASK('A','D','3'):
    case HSV_MAKE_CHAR_MASK('a','d','4'):
    case HSV_MAKE_CHAR_MASK('A','D','4'):
    case HSV_MAKE_CHAR_MASK('a','d','5'):
    case HSV_MAKE_CHAR_MASK('A','D','5'):
    case HSV_MAKE_CHAR_MASK('a','d','6'):
    case HSV_MAKE_CHAR_MASK('A','D','6'):
    case HSV_MAKE_CHAR_MASK('a','d','7'):
    case HSV_MAKE_CHAR_MASK('A','D','7'):
    case HSV_MAKE_CHAR_MASK('a','d','8'):
    case HSV_MAKE_CHAR_MASK('A','D','8'):
    case HSV_MAKE_CHAR_MASK('a','d','9'):
    case HSV_MAKE_CHAR_MASK('A','D','9'):
    case HSV_MAKE_CHAR_MASK('Q','A','D'):
    case HSV_MAKE_CHAR_MASK('q','a','d'):
    case HSV_MAKE_CHAR_MASK('N','A','R'):
    case HSV_MAKE_CHAR_MASK('n','a','r'):

        if (1) {
            TraceInfo(m, "euApp: adn is assigned to LangAudioDescription");
            lngid = langid_LangAudioDescription;
        }
        break;
    default:
        break;
    }
	TraceNotice(m,"%s return langid %d",__FUNCTION__,lngid);
    return lngid;
}

int CHsvDvbBAT_Priv::iutil_GetLCNValue(Nat8* ptr, int num)
{
    int val = GET16(0);
	UNUSED(num);
    return val;
}



