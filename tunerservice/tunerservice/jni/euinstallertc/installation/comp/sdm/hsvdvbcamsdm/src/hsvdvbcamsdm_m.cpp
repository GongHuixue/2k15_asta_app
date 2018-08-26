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


#include "_hsvdvbcamsdm_m.h"

TRACESYMBOL(m, "dvb/sitables/hsvdvbcamsdm_m")


#ifndef __cplusplus

#else

#endif


Nat8 CHsvDvbCamSdm_Priv::s__mModulation[7] = 
{
    /*0x00 not defined*/                    HsvUnknownConstellation,
    /*0x01 16 QAM*/                         HsvQam16,
    /*0x02 32 QAM*/                         HsvQam32,
    /*0x03 64 QAM*/                         HsvQam64,
    /*0x04 128 QAM*/                        HsvQam128,
    /*0x05 256 QAM*/                        HsvQam256,
    /*0x06 to 0xFF reserved for future use*/HsvUnknownConstellation
};


Bool CHsvDvbCamSdm_Priv::s__mActive = FALSE;

Nat8 CHsvDvbCamSdm_Priv::s__mcamCharCode = 0;

Bool CHsvDvbCamSdm_Priv::s__mPrevPrivateDataSpecifierPresent = FALSE;

Nat8 CHsvDvbCamSdm_Priv::s__mBuffer[4*1024];
Nat32 mCookie = 0;
TypeCamNitParser CHsvDvbCamSdm_Priv::s__CamNitParser;




/***** STATIC FUNCTIONS   *****/

/* Init Functions */








/* Interpret Data Functions */





/* Populate Data Functions */










/* Keys definition for the sorted table data */

HSVCOMPAREKEY(camnitcabledsconf, Primary,     HsvCamNITCableDS, OriginalNetworkId)

HSVCOMPAREKEY(camnitcabledsconf, Secondary,   HsvCamNITCableDS, TsId)

HSVCOMPAREKEY(camnitcabledsconf, Teritiary,   HsvCamNITCableDS, TsId)

HSVCOMPAREKEY(camnitcabledsconf, Quaternary,  HsvCamNITCableDS, TsId)


HSVCOMPAREKEY(camnitterrestrialdsconf, Primary,     HsvCamNITTerrestrialDS, OriginalNetworkId)

HSVCOMPAREKEY(camnitterrestrialdsconf, Secondary,   HsvCamNITTerrestrialDS, TsId)

HSVCOMPAREKEY(camnitterrestrialdsconf, Teritiary,   HsvCamNITTerrestrialDS, NetworkId)

HSVCOMPAREKEY(camnitterrestrialdsconf, Quaternary,  HsvCamNITTerrestrialDS, TsId)


HSVCOMPAREKEY(camnitc2dsconf, Primary,     HsvCamNITC2DS, OriginalNetworkId)

HSVCOMPAREKEY(camnitc2dsconf, Secondary,   HsvCamNITC2DS, TsId)

HSVCOMPAREKEY(camnitc2dsconf, Teritiary,   HsvCamNITC2DS, TsId)

HSVCOMPAREKEY(camnitc2dsconf, Quaternary,  HsvCamNITC2DS, TsId)


HSVCOMPAREKEY(camnitt2dsconf, Primary,    HsvCamNITT2DS, OriginalNetworkId)

HSVCOMPAREKEY(camnitt2dsconf, Secondary,  HsvCamNITT2DS, TsId)

HSVCOMPAREKEY(camnitt2dsconf, Teritiary,  HsvCamNITT2DS, TsId)

HSVCOMPAREKEY(camnitt2dsconf, Quaternary, HsvCamNITT2DS, TsId)


HSVCOMPAREKEY(camnitcontentlabelconf, Primary,    HsvCamNITContentLabel, ContentByteMin)

HSVCOMPAREKEY(camnitcontentlabelconf, Secondary,  HsvCamNITContentLabel, ContentByteMax)

HSVCOMPAREKEY(camnitcontentlabelconf, Teritiary,  HsvCamNITContentLabel, ISO_639_Language_Code)

HSVCOMPAREKEY(camnitcontentlabelconf, Quaternary, HsvCamNITContentLabel, ContentByteMax)


HSVCOMPAREKEY(camnitserviceconf, Primary,    HsvCamNITService, OriginalNetworkId)

HSVCOMPAREKEY(camnitserviceconf, Secondary,  HsvCamNITService, TsId)

HSVCOMPAREKEY(camnitserviceconf, Teritiary,  HsvCamNITService, ServiceId)

HSVCOMPAREKEY(camnitserviceconf, Quaternary, HsvCamNITService, LogicalChannelNumber)


HSVCOMPAREKEY(camnitlinkageinfoconf, Primary,    HsvCamNITLinkageInfo,  Original_NetworkId)

HSVCOMPAREKEY(camnitlinkageinfoconf, Secondary,  HsvCamNITLinkageInfo,  Tsid)

HSVCOMPAREKEY(camnitlinkageinfoconf, Teritiary,  HsvCamNITLinkageInfo,  LinkageType)

HSVCOMPAREKEY(camnitlinkageinfoconf, Quaternary, HsvCamNITLinkageInfo,  LinkageType)


void CHsvDvbCamSdm_Priv::mInitCamNitCableDS(void)
{
	srtdb_Init(srtdbids_CamNitCableDS);
}

void CHsvDvbCamSdm_Priv::mInitCamNitTerrestrialDS(void)
{
	srtdb_Init(srtdbids_CamNitTerrestrialDS);
}

void CHsvDvbCamSdm_Priv::mInitCamNitC2DS(void)
{
	srtdb_Init(srtdbids_CamNitC2DS);
}

void CHsvDvbCamSdm_Priv::mInitCamNitT2DS(void)
{
	srtdb_Init(srtdbids_CamNitT2DS);
}

void CHsvDvbCamSdm_Priv::mInitCamNitContentLabel(void)
{
	srtdb_Init(srtdbids_CamNitContentLabel);
}

void CHsvDvbCamSdm_Priv::mInitCamNitService(void)
{
	srtdb_Init(srtdbids_CamNitService);
}

void CHsvDvbCamSdm_Priv::mInitCamNitLinkageInfo(void)
{
	srtdb_Init(srtdbids_CamNitLinkageInfo);
}

/* Interpret Data Functions */

Nat8 CHsvDvbCamSdm_Priv::mInterpretModulationValue(Nat8 *mod)
{
    int index = *mod;
	
    if(index > 5)
    {
        index = 0;
    }
	
    *mod = mModulation[index];

    return mModulation[index];
}

Nat32 CHsvDvbCamSdm_Priv::mInterpretSymbolRate(Nat32 *symrate)
{
    /* Convert BCD MSymobls/sec to symbols per sec*/
    int i = 0;
    Nat32 result = 0;
    Nat32 Multiplier = 1;

    for(i=0; i < 7; i++)  /* 7 as per Cable Delivery System Descriptor standards */
    {
        result += ((*symrate >> (i*4)) & 0xf) * Multiplier;
        Multiplier *= 10;
    }

    result = result*100;
    *symrate = result;
    return result;

}

Nat32 CHsvDvbCamSdm_Priv::mInterpretFrequencyValue(Nat32 *freq)
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

Nat8 CHsvDvbCamSdm_Priv::mMapDVBTBandwidth(int bw)
{
	Nat8 bandwidth = 0;				//TUNING_DVBT_BW_AUTO  = 0; /**< use this for auto detection */
	switch(bw){
		case 0:
			bandwidth = 4;			//Change in 2k15(Please refer ITuningDvbT.java) : TUNING_DVBT_BW_MHZ_8 = 4; /**< 8 MHz Channel */
			break;
		case 1:
			bandwidth = 2;			//TUNING_DVBT_BW_MHZ_7 = 2; /**< 7 MHz Channel */
			break;
		case 2:
			bandwidth = 1;			//TUNING_DVBT_BW_MHZ_6 = 1; /**< 6 MHz Channel */
			break;
		case 3:
			bandwidth = 5;
			break;
		case 4:
			bandwidth = 10;				//DVB-T2 specific
			break;
		case 5:
			bandwidth = 1712;			//DVB-T2 specific...check the value...is it 1.712? how to send this val to playtv?
			break;
	}

	return bandwidth;
}

/* Populate Data Functions */

void CHsvDvbCamSdm_Priv::mPopulateCamNitCableDS(void)
{
	HsvCamNITCableDS DbaseVersion, TempVersion;
    int tsloop = 0, i = 0, HsvEvtNull = 0, j = 0, NumOfT2DS = 0;
	Nat32 CDSFrequency = 0, CDSSymbolRate = 0;
	Nat8 CDSModulation = 0;
	
	while ( tsloop < CamNitParser.TsLoopDataNum)
	{
		NumOfT2DS = CamNitParser.TsLoopData[tsloop].CDSDDescNum;
		for( i = 0; i < NumOfT2DS; i++)
		{
			if (CamNitParser.TsLoopData[tsloop].CDSD_Descriptor[i].DescriptorValid ) 
			{
				DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
				DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				DbaseVersion.NumOfDSD = 0;

				for( j = 0; j < CamNitParser.TsLoopData[tsloop].CDSD_Descriptor[i].CDSDLen ; j++)
				{                   
					CDSFrequency = mInterpretFrequencyValue(&(CamNitParser.TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].Frequency));
					CDSModulation = mInterpretModulationValue(&(CamNitParser.TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].Modulation));    
					CDSSymbolRate = mInterpretSymbolRate(&(CamNitParser.TsLoopData[tsloop].CDSD_Descriptor[i].CDSD[j].SymbolRate));    

					TraceNotice(m,"PopulateCDSC::symrate:%d, modln=%d, freq=%d",(int)CDSSymbolRate, CDSModulation, (int)(CDSFrequency >> 4));

					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Frequency  = CDSFrequency;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Modulation = CDSModulation;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].SymbolRate = CDSSymbolRate;
					DbaseVersion.NumOfDSD++;
					TraceNotice(m,"%s:: ValidateCDS Success ",__FUNCTION__);
				}

				if(mCookie == EnmTypeCamNITData)
				{
					DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
					DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				}
				else
				{
					DbaseVersion.TsId = CDSFrequency;
					DbaseVersion.OriginalNetworkId = CDSModulation;
					TraceNotice(m,"@ 352 TsId %d OriginalNetworkId %d", DbaseVersion.TsId, DbaseVersion.OriginalNetworkId);
				}
				
				TraceNotice(m,"NoOf CDSD's %d", DbaseVersion.NumOfDSD);
				if(DbaseVersion.NumOfDSD > 0)
				{
					if ( srtdb_QueryOnKey( srtdbids_CamNitCableDS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
					{
						Bool ret = srtdb_Update(srtdbids_CamNitCableDS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion));
						TraceNotice(m,"%d %d %d ret %d",DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, ret);
					}
					else
					{
						/* New Record */
						Bool ret = srtdb_Insert(srtdbids_CamNitCableDS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion));
						TraceNotice(m,"%d %d %d ret %d",DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, ret);
					}
				}
			}
		}
		tsloop++;
	}   
}

void CHsvDvbCamSdm_Priv::mPopulateCamNitTerrestrialDS(void)
{
	HsvCamNITTerrestrialDS DbaseVersion, TempVersion;
    int tsloop = 0, i = 0, HsvEvtNull = 0, j = 0, NumOfT2DS = 0;
	Nat32 Frequency = 0;
	Nat8  Priority = 0; 
	Nat32 Bandwidth;
	Nat8 CodeRateLPSTream = 0, GuardInterval = 0, TransmissionMode = 0, OtherFrequencyFlag = 0;
	
	TraceNotice(m, "%s %d %d", __FUNCTION__, tsloop, CamNitParser.TsLoopDataNum);
	while ( tsloop < CamNitParser.TsLoopDataNum)
	{
		NumOfT2DS = CamNitParser.TsLoopData[tsloop].TDSDDescNum;
		TraceNotice(m, "%s %d %d", __FUNCTION__, tsloop, NumOfT2DS);
		for( i = 0; i < NumOfT2DS; i++)
		{
			TraceNotice(m, "%s %d %d", __FUNCTION__, tsloop, CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].DescriptorValid);
			if (CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].DescriptorValid ) 
			{
				DbaseVersion.NumOfDSD = 0;

				TraceNotice(m, "%s %d %d", __FUNCTION__, tsloop, CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSDLen);
				for( j = 0; j < CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSDLen ; j++)
				{                   
					Frequency  = (((CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].Frequency)/100000) * 16);
					Priority   = CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].Priority;
					Priority   ^= 1;
					Bandwidth  = mMapDVBTBandwidth(CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].Bandwidth);

					CodeRateLPSTream 	= CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].CodeRateLPSTream;
					GuardInterval 		= CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].GuardInterval;
					TransmissionMode 	= CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].TransmissionMode;
					OtherFrequencyFlag 	= CamNitParser.TsLoopData[tsloop].TDSD_Descriptor[i].TDSD[j].OtherFrequencyFlag;

					TraceNotice(m,"Bandwidth %d, Priority %d Frequency %d", (int)Bandwidth, Priority, (int)(Frequency));

					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Frequency  = Frequency;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Priority = Priority;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Bandwidth = Bandwidth;
					DbaseVersion.NumOfDSD++;
				}
				
				if(mCookie == EnmTypeCamNITData)
				{
					DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
					DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				}
				else
				{
					DbaseVersion.OriginalNetworkId = i;
					DbaseVersion.TsId = Frequency;
					DbaseVersion.NetworkId = ((CodeRateLPSTream << 5) | (GuardInterval << 3) | (TransmissionMode << 1) | OtherFrequencyFlag); //Workaround for DTVL 7.2.8.5
					TraceNotice(m,"@ 352 TsId %d OriginalNetworkId %d NetworkId %d", DbaseVersion.TsId, DbaseVersion.OriginalNetworkId, DbaseVersion.NetworkId);
				}
				
				TraceNotice(m,"NoOf TDSD's %d", DbaseVersion.NumOfDSD);
				if(DbaseVersion.NumOfDSD > 0)
				{
					if ( srtdb_QueryOnKey( srtdbids_CamNitTerrestrialDS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
					{
						Bool ret = srtdb_Update(srtdbids_CamNitTerrestrialDS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion));
						TraceNotice(m,"%d %d %d ret %d",DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, ret);
					}
					else
					{
						/* New Record */
						Bool ret = srtdb_Insert(srtdbids_CamNitTerrestrialDS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion));
						TraceNotice(m,"%d %d %d ret %d",DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, ret);
					}
				}
			}
		}
		tsloop++;
	}
}

void CHsvDvbCamSdm_Priv::mPopulateCamNitC2DS(void)
{
	HsvCamNITC2DS DbaseVersion, TempVersion;
    int tsloop = 0, i = 0, HsvEvtNull = 0, j = 0, NumOfC2DS = 0;
	Nat32 Frequency = 0;

	while ( tsloop < CamNitParser.TsLoopDataNum)
	{
		NumOfC2DS = CamNitParser.TsLoopData[tsloop].C2DSDDescNum;
		for( i = 0; i < NumOfC2DS; i++)
		{
			if (CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].DescriptorValid ) 
			{
				DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
				DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				DbaseVersion.NumOfDSD = 0;

				for( j = 0; j < CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].C2DSDLen ; j++)
				{                   
					Frequency  = mInterpretFrequencyValue(&(CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].C2DSD[j].Frequency));
					
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Frequency  = Frequency;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].PLP_Id     = CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].C2DSD[j].PLP_Id;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].SystemId   = CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].C2DSD[j].SystemId;
					
					TraceNotice(m,"PLP_Id %d Frequency %d SystemId %d", CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].C2DSD[j].PLP_Id, (int)(Frequency >> 4), CamNitParser.TsLoopData[tsloop].C2DSD_Descriptor[i].C2DSD[j].SystemId);
					
					DbaseVersion.NumOfDSD++;
				}

				if(mCookie == EnmTypeCamNITData)
				{
					DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
					DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				}
				else
				{
					DbaseVersion.TsId = Frequency;
					DbaseVersion.OriginalNetworkId = DbaseVersion.DSD[DbaseVersion.NumOfDSD - 1].PLP_Id;
					TraceNotice(m,"@ 426 TsId %d OriginalNetworkId %d", DbaseVersion.TsId, DbaseVersion.OriginalNetworkId);
				}
				
				TraceNotice(m,"NoOf C2DSD's %d", DbaseVersion.NumOfDSD);
				if(DbaseVersion.NumOfDSD > 0)
				{
					if ( srtdb_QueryOnKey( srtdbids_CamNitC2DS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
					{
						srtdb_Update(srtdbids_CamNitC2DS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion));
					}
					else
					{
						/* New Record */
						srtdb_Insert(srtdbids_CamNitC2DS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion));
					}
				}
			}
		}
		tsloop++;
	}
}

void CHsvDvbCamSdm_Priv::mPopulateCamNitT2DS(void)
{
	HsvCamNITT2DS DbaseVersion, TempVersion;
    int tsloop = 0, i = 0, HsvEvtNull = 0, j = 0, NumOfT2DS = 0;
	Nat32 Frequency = 0, Bandwidth;
	
	while ( tsloop < CamNitParser.TsLoopDataNum)
	{
		NumOfT2DS = CamNitParser.TsLoopData[tsloop].T2DSDDescNum;
		for( i = 0; i < NumOfT2DS; i++)
		{
			if (CamNitParser.TsLoopData[tsloop].T2DSD_Descriptor[i].DescriptorValid ) 
			{
				DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
				DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				DbaseVersion.NumOfDSD = 0;

				for( j = 0; j < CamNitParser.TsLoopData[tsloop].T2DSD_Descriptor[i].T2DSDLen ; j++)
				{                   
					Frequency  = mInterpretFrequencyValue(&(CamNitParser.TsLoopData[tsloop].T2DSD_Descriptor[i].T2DSD[j].Frequency));
					Bandwidth  = mMapDVBTBandwidth(CamNitParser.TsLoopData[tsloop].T2DSD_Descriptor[i].T2DSD[j].Bandwidth);

					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Frequency  = Frequency;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].Bandwidth  = Bandwidth;
					DbaseVersion.DSD[DbaseVersion.NumOfDSD].PLP_Id     = CamNitParser.TsLoopData[tsloop].T2DSD_Descriptor[i].T2DSD[j].PLP_Id;
					
					TraceNotice(m,"Bandwidth %d, PLP_Id %d Frequency %d", (int)Bandwidth, CamNitParser.TsLoopData[tsloop].T2DSD_Descriptor[i].T2DSD[j].PLP_Id, (int)(Frequency >> 4));
					
					DbaseVersion.NumOfDSD++;
				}

				if(mCookie == EnmTypeCamNITData)
				{
					DbaseVersion.TsId = CamNitParser.TsLoopData[tsloop].TSID;
					DbaseVersion.OriginalNetworkId = CamNitParser.TsLoopData[tsloop].ONID;
				}
				else
				{
					DbaseVersion.TsId = Frequency;
					DbaseVersion.OriginalNetworkId = DbaseVersion.DSD[DbaseVersion.NumOfDSD - 1].PLP_Id;
					TraceNotice(m,"@ 475 TsId %d OriginalNetworkId %d", DbaseVersion.TsId, DbaseVersion.OriginalNetworkId);
				}
				
				TraceNotice(m,"NoOf T2DSD's %d", DbaseVersion.NumOfDSD);
				if(DbaseVersion.NumOfDSD > 0)
				{
					if ( srtdb_QueryOnKey( srtdbids_CamNitT2DS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&TempVersion) ) )
					{
						srtdb_Update(srtdbids_CamNitT2DS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, 0,(Address)(&DbaseVersion));
					}
					else
					{
						/* New Record */
						srtdb_Insert(srtdbids_CamNitT2DS, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.NetworkId, DbaseVersion.NetworkId, (Address)(&DbaseVersion));
					}
				}
			}
		}
		tsloop++;
	}
}

void CHsvDvbCamSdm_Priv::mPopulateCamNitContentLabel(void)
{
	HsvCamNITContentLabel DbaseVersion, TempVersion;
    int i = 0, len = 0, stringlen = MAXCONTENTLABLENAMELEN + 1;

	for( i = 0; i < 10; i++)//CamNitParser.CIPlus_Content_Label_Descriptor
	{
		if(CamNitParser.CIPlus_Content_Label_Descriptor[i].DescriptorValid)
		{
			DbaseVersion.ContentByteMin  		= CamNitParser.CIPlus_Content_Label_Descriptor[i].Content_Byte_Min;
			DbaseVersion.ContentByteMax  		= CamNitParser.CIPlus_Content_Label_Descriptor[i].Content_Byte_Min;;
			DbaseVersion.ISO_639_Language_Code  = CamNitParser.CIPlus_Content_Label_Descriptor[i].ISO_639_Language_Code;
			
			Nat8 *LabelName = (Nat8 *) CamNitParser.CIPlus_Content_Label_Descriptor[i].LabelChar;
            len = CamNitParser.CIPlus_Content_Label_Descriptor[i].LabelCharLen;

            charsetutil_MbToWcEx( LabelName, len, (Nat16*)&DbaseVersion.LabelChar, &stringlen, charsetutil_ExtractShortName);
            if(stringlen > MAXCONTENTLABLENAMELEN)
            {
                stringlen = MAXCONTENTLABLENAMELEN;
            }
            DbaseVersion.LabelChar[stringlen] = 0; 
			if ( srtdb_QueryOnKey( srtdbids_CamNitContentLabel, DbaseVersion.ContentByteMin, DbaseVersion.ContentByteMax, DbaseVersion.ISO_639_Language_Code, 0,(Address)(&TempVersion) ) )
			{
				srtdb_Update(srtdbids_CamNitContentLabel, DbaseVersion.ContentByteMin, DbaseVersion.ContentByteMax, DbaseVersion.ISO_639_Language_Code, 0,(Address)(&DbaseVersion));
			}
			else
			{
				/* New Record */
				srtdb_Insert(srtdbids_CamNitContentLabel, DbaseVersion.ContentByteMin, DbaseVersion.ContentByteMax, DbaseVersion.ISO_639_Language_Code, 0, (Address)(&DbaseVersion));
			}
		}
	}	
}

void CHsvDvbCamSdm_Priv::mPopulateCamNitService(void)
{
	HsvCamNITService DbaseVersion, TempVersion;
    int tsloop = 0, i = 0, len = 0, NumOfServiceDescNum = 0;
	Nat8 *ServiceName = NULL;

	while ( tsloop < CamNitParser.TsLoopDataNum)
	{
		NumOfServiceDescNum = CamNitParser.TsLoopData[tsloop].CIPlusServiceDescNum;
		for( i = 0; i < NumOfServiceDescNum; i++)
		{
			if (CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].DescriptorValid ) 
			{
				DbaseVersion.TsId 					= CamNitParser.TsLoopData[tsloop].TSID;
				DbaseVersion.OriginalNetworkId 		= CamNitParser.TsLoopData[tsloop].ONID;
				DbaseVersion.ServiceId              = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceId;
				DbaseVersion.ServiceType			= CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceType;
				DbaseVersion.VisibleServiceFlag		= CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].VisibleServiceFlag;
				DbaseVersion.SelectableServiceFlag	= CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].SelectableServiceFlag;
				DbaseVersion.LogicalChannelNumber	= CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].LogicalChannelNumber;
				DbaseVersion.ServiceName[0] 		= '\0';
				
				//Nat8 *ServiceName = (Nat8 *)CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceName;			
				len =   CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceNameLen;
				ServiceName = (Nat8 *)malloc(len+1);
				ServiceName[0] = mcamCharCode;
				TraceNotice(m,"before concat in CAM SDM is %d %d\n",ServiceName[0], mcamCharCode);
				//strncat((char *)ServiceName, CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceName, len);
				for(int loop=0; loop<len; loop++){
					ServiceName[loop+1] = CamNitParser.TsLoopData[tsloop].CIPlus_Service_Descriptor[i].ServiceName[loop];
				}
				TraceNotice(m,"char code used in CAM SDM is %d\n",ServiceName[0]);
				charsetutil_MbToWc( ServiceName, len+1, DbaseVersion.ServiceName, MAXSERVICENAMELEN, (len >= div_ChannelNameLength) ? TRUE : FALSE);
				len =   MAXSERVICENAMELEN;
				DbaseVersion.ServiceName[len] = '\0';
				ServiceName = NULL;
				free(ServiceName);
				if ( srtdb_QueryOnKey( srtdbids_CamNitService, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, (Address)(&TempVersion) ) )
				{
					Bool ret = srtdb_Update(srtdbids_CamNitService, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, (Address)(&DbaseVersion));
					TraceNotice(m,"%d %d %d %d ret %d",DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, ret);
				}
				else
				{
					/* New Record */
					Bool ret = srtdb_Insert(srtdbids_CamNitService, DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, (Address)(&DbaseVersion));
					TraceNotice(m,"%d %d %d %d ret %d",DbaseVersion.OriginalNetworkId, DbaseVersion.TsId, DbaseVersion.ServiceId, DbaseVersion.LogicalChannelNumber, ret);
				}
			}
		}
		tsloop++;
	}
}

void CHsvDvbCamSdm_Priv::mPopulateCamNitLinkageInfo(void)
{
	Bool retval  = TRUE;	
	int i= 0, tsloop = 0;
	HSVSPTYPE(CamNITLinkageInfo, dvb, camnit)  		linkage;
    HSVSPTYPE(CamNITLinkageInfo, dvb, camnit)  		DbaseVersion;

	for( i = 0; i < CamNitParser.LinkageDescNum; i++)
	{
		if(CamNitParser.Linkage_Descriptor[i].DescriptorValid)
		{
			linkage.LinkageType        = (HsvLinkageType)CamNitParser.Linkage_Descriptor[i].LinkageType;
			linkage.Original_NetworkId  = CamNitParser.Linkage_Descriptor[i].ONID;
			linkage.Tsid               = CamNitParser.Linkage_Descriptor[i].TSID;
			linkage.ServiceId          = CamNitParser.Linkage_Descriptor[i].ServiceId;
			linkage.NetworkId          = CamNitParser.NetworkId;
			linkage.VersionNumber      = CamNitParser.VersionNo;
			TraceNotice(m,"%s %d Linkage type delivered is %d for %d %d %d",__FUNCTION__,__LINE__,linkage.LinkageType,linkage.Original_NetworkId,linkage.Tsid,linkage.ServiceId);
			if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI)||(linkage.LinkageType == EPG_Service) )
			{

				if( srtdb_QueryOnKey( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&DbaseVersion)) )
				{
					/*Record exists. Update */
					
					TraceNotice(m,"%s Onid = %d, TsId = %d", __FUNCTION__, linkage.Original_NetworkId, linkage.Tsid);
					srtdb_Update( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0,(Address)(&linkage));
				}
				else
				{
					TraceNotice(m,"%s OnId = %d, TsId=%d, Type=%d", __FUNCTION__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
					srtdb_Insert( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType, linkage.LinkageType,(Address)(&linkage));
				}
				strapiN_OnCompleted(1, HSVSPID(CamNITLinkageInfo, dvb, camnit));

			}
		}        

        while ( tsloop < CamNitParser.TsLoopDataNum)
        {

            for( i = 0; i < CamNitParser.TsLoopData[tsloop].LinkageDescNum; i++)
            {
                if(CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].DescriptorValid)
                {
                    linkage.LinkageType        = (HsvLinkageType)CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].LinkageType;
                    linkage.Original_NetworkId  = CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].ONID;
                    linkage.Tsid               = CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].TSID;
                    linkage.ServiceId          = CamNitParser.TsLoopData[tsloop].Linkage_Descriptor[i].ServiceId;
                    linkage.NetworkId          = CamNitParser.NetworkId;
                    linkage.VersionNumber      = CamNitParser.VersionNo;
                    if((linkage.LinkageType == SystemSoftwareUpdate) || (linkage.LinkageType == TS_Containing_Complete_Network_Bouquet_SI)||(linkage.LinkageType == EPG_Service) )
                    {

                        if( srtdb_QueryOnKey( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),0, (Address)(&DbaseVersion)) )
                        {
                            /*Record exists. Update */
                            srtdb_Update( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType), 0, (Address)(&linkage));
                            TraceNotice(m,"HYSVC : hsvdvbnit_m.c : strapiN called for LinkageInfo Onid = %d, TsId = %d",linkage.Original_NetworkId, linkage.Tsid);
                        }
                        else
                        {
                            TraceNotice(m,"%s: @ %d :: OnId = %d, TsId=%d, Type=%d", __FUNCTION__, __LINE__, linkage.Original_NetworkId, linkage.Tsid, linkage.LinkageType);
                            srtdb_Insert( srtdbids_CamNitLinkageInfo, linkage.Original_NetworkId, linkage.Tsid, (linkage.LinkageType),(linkage.LinkageType), (Address)(&linkage));
                        }
                    }
                }        

            }
            tsloop++;   
        }
    }
}

Bool CHsvDvbCamSdm_Priv::mPopulateNIT(void)
{
    int retval = TRUE;
    
	TraceNotice(m, "%s mActive %d", __FUNCTION__, mActive);
	
	if(mActive)
	{
		mPopulateCamNitCableDS();
		mPopulateCamNitTerrestrialDS();
		mPopulateCamNitC2DS();
		mPopulateCamNitT2DS();
		mPopulateCamNitService();
		mPopulateCamNitContentLabel();
		mPopulateCamNitLinkageInfo();
		
		TraceErr(m, "%s @ 901 mCookie %d", __FUNCTION__, mCookie);
		if(mCookie == EnmTypeTuneDSDescData)
		{
			strapiN_OnCompleted(0, mCookie);
		}
		mPrevPrivateDataSpecifierPresent = FALSE;
	}
    return retval;
}

Nat8 CHsvDvbCamSdm_Priv::mGetLanguageId(Nat32 Language)
{
	/* Assume that the lower 3 bytes of the Nat32 contain the 3 byte code */
    char byte1 = (char)((((Nat32)(Language) & 0xFF0000)) >> 16);
    char byte2 = (char)((((Nat32)(Language) & 0xFF00))   >> 8);
    char byte3 = (char)((((Nat32)(Language) & 0xFF)));

    return (Nat8)(mpegserv_GetLanguageId( byte1, byte2, byte3 ));
}

void CHsvDvbCamSdm_Priv::pow_Init(void)
{
	mActive = FALSE;
}

void CHsvDvbCamSdm_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbCamSdm_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbCamSdm_Priv::ena_Enable(HsvDemux dmx)
{
	mActive		= TRUE;
	
	TraceNotice(m, "mActive %d Reset CAM NIT strapi database", mActive);
	
	mInitCamNitLinkageInfo();
    mInitCamNitCableDS();
    mInitCamNitTerrestrialDS();
    mInitCamNitC2DS();			
    mInitCamNitT2DS();
    mInitCamNitContentLabel();
    mInitCamNitService();	
}

void CHsvDvbCamSdm_Priv::ena_Disable(HsvDemux dmx)
{
	mActive		= FALSE;
	
	TraceNotice(m, "mActive %d Reset CAM NIT strapi database", mActive);
	
	mInitCamNitLinkageInfo();
    mInitCamNitCableDS();
    mInitCamNitTerrestrialDS();
    mInitCamNitC2DS();			
    mInitCamNitT2DS();
    mInitCamNitContentLabel();
    mInitCamNitService();
}

void CHsvDvbCamSdm_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED( dmx );
}

/*****   IHsvStream Implementation   *****/

int CHsvDvbCamSdm_Priv::strapi_GetSize   (HsvDestination dest, int prop)
{
    int retval = 0;

    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(CamNITCableDS, dvb, camnit):
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitCableDS);
            break;
        case HSVSPID(CamNITTerrestrialDS, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitTerrestrialDS);

            break;
        case HSVSPID(CamNITC2DS, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitC2DS);
	    	   
            break;
        case HSVSPID(CamNITT2DS, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitT2DS);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitLinkageInfo);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitService);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit): 
            retval = srtdb_GetNoOfRecords(srtdbids_CamNitContentLabel);
            break;
        default:
            ASSERT(FALSE);
            break;
    }

	    TraceNotice(m, "%s %d %d", __FUNCTION__, prop, retval);

    return retval;
}

Bool CHsvDvbCamSdm_Priv::strapi_GetIndex  (HsvDestination dest, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(CamNITCableDS, dvb, camnit):
            srtdb_SearchOnKey(srtdbids_CamNitCableDS, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(CamNITTerrestrialDS, dvb, camnit): 
			srtdb_SearchOnKey(srtdbids_CamNitTerrestrialDS, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(CamNITC2DS, dvb, camnit): 
			srtdb_SearchOnKey(srtdbids_CamNitC2DS, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(CamNITT2DS, dvb, camnit): 
			srtdb_SearchOnKey(srtdbids_CamNitT2DS, key1, key2, key3, 0,(int *)&index);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
			srtdb_SearchOnKey(srtdbids_CamNitLinkageInfo, key1, key2, key3, 0,(int *)&index);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
			srtdb_SearchOnKey(srtdbids_CamNitService, key1, key2, key3, 0,(int *)&index);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit): 
            srtdb_SearchOnKey(srtdbids_CamNitContentLabel, key1, key2, key3, 0,(int *)&index);
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    return TRUE;
}

Bool CHsvDvbCamSdm_Priv::strapi_GetByKey  (HsvDestination dest, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    
	UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(CamNITCableDS, dvb, camnit):
            retval = srtdb_QueryOnKey(srtdbids_CamNitCableDS, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(CamNITTerrestrialDS, dvb, camnit): 
			retval = srtdb_QueryOnKey(srtdbids_CamNitTerrestrialDS, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(CamNITC2DS, dvb, camnit): 
			retval = srtdb_QueryOnKey(srtdbids_CamNitC2DS, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(CamNITT2DS, dvb, camnit): 
			retval = srtdb_QueryOnKey(srtdbids_CamNitT2DS, key1, key2, key3, 0, (Address)val);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
			retval = srtdb_QueryOnKey(srtdbids_CamNitLinkageInfo, key1, key2, key3, 0, (Address)val);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
			retval = srtdb_QueryOnKey(srtdbids_CamNitService, key1, key2, key3, 0, (Address)val);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit):
            retval = srtdb_QueryOnKey(srtdbids_CamNitContentLabel, key1, key2, key3, 0, (Address)val);
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    
    return retval;
}

Bool CHsvDvbCamSdm_Priv::strapi_GetByIndex(HsvDestination dest, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (dest);
    switch (prop)
    {
        case HSVSPID(CamNITCableDS, dvb, camnit):
            retval = srtdb_QueryOnIndex(srtdbids_CamNitCableDS, index, (Address)val);
            break;
        case HSVSPID(CamNITTerrestrialDS, dvb, camnit): 
			retval = srtdb_QueryOnIndex(srtdbids_CamNitTerrestrialDS, index, (Address)val);
            break;
        case HSVSPID(CamNITC2DS, dvb, camnit): 
			retval = srtdb_QueryOnIndex(srtdbids_CamNitC2DS, index, (Address)val);
            break;
        case HSVSPID(CamNITT2DS, dvb, camnit): 
			retval = srtdb_QueryOnIndex(srtdbids_CamNitT2DS, index, (Address)val);
            break;
        case HSVSPID(CamNITLinkageInfo, dvb, camnit): 
			retval = srtdb_QueryOnIndex(srtdbids_CamNitLinkageInfo, index, (Address)val);
            break;  
        case HSVSPID(CamNITService, dvb, camnit): 
			retval = srtdb_QueryOnIndex(srtdbids_CamNitService, index, (Address)val);
            break;  
        case HSVSPID(CamNITContentLabel, dvb, camnit):
            retval = srtdb_QueryOnIndex(srtdbids_CamNitContentLabel, index, (Address)val);
            break;
        default:
            ASSERT(FALSE);
            break;
    }

		    TraceNotice(m, "%s %d %d %d", __FUNCTION__, prop, index, retval);
    return retval;
}

Bool CHsvDvbCamSdm_Priv::strapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	UNUSED(dest);
	UNUSED(spid);
	UNUSED(noofkeys);
	UNUSED(key1);
	UNUSED(key2);
	UNUSED(key3);
	UNUSED(from);
	UNUSED(to);
	
	return FALSE;
}


Bool CHsvDvbCamSdm_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
    
	UNUSED (dest);
    UNUSED (value);

    return retval;
	
}/* End of function strmfltr_Set() */

Bool CHsvDvbCamSdm_Priv::strmfltr_IsSet    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}
Bool CHsvDvbCamSdm_Priv::strmfltr_IsReady  ( HsvDestination dest, int filterid ) /* Ready for Strapi */
{
	return FALSE;
}
Bool CHsvDvbCamSdm_Priv::strmfltr_Clear    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}
Bool CHsvDvbCamSdm_Priv::strmfltr_ForceClear    ( HsvDestination dest, int filterid, int value )
{
	return FALSE;
}


/*****	NIT PARSER CODE   *****/

Bool CHsvDvbCamSdm_Priv::camScanparser_CamNitParser_Parser( HsvDestination   dest,  Nat32 cookie, int DataSize, Nat8 * DataPtr)
{
	Nat8 *TempPtr;
    Bool retval = TRUE;
	register int v32=0;
	register Nat8 *ptr = mBuffer;
	HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
	int dummy, loopcount = 0, descTag = 0, descTagExtn = 0, descLen = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0,loop2index = 0, tableLen = 0, loop1length = 0,loop2length = 0, templen = 0, unused = 0;; 
	int nitLoopLen = 0;
	int privateDataSpecifierId = 0;
	
	ptr = DataPtr;	
	v32 = GET32(0);
	mPrevPrivateDataSpecifierPresent = FALSE;
	nitLoopLen = DataSize;
	mCookie = cookie;
	TraceErr(m, "%s @ 901 mCookie %d", __FUNCTION__, mCookie);

	while(nitLoopLen > 0){
	if(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
	{
		tableLen = HSV_GETSECTION_LENGTH(ptr);
		TraceNotice(m,"%s %d",__FUNCTION__,tableLen);
		nitLoopLen = nitLoopLen - tableLen;
		
		CamNitParser.NtkNameDescNum=0;
		CamNitParser.LinkageDescNum=0;
		CamNitParser.CIPlusContentLabelDescNum=0;
		CamNitParser.TsLoopDataNum=0;
		CamNitParser.TableId = GETNBITS(v32,0,8);
		dummy = GETNBITS(v32,8,1);
		dummy = GETNBITS(v32,9,1);
		dummy = GETNBITS(v32,10,2);
		CamNitParser.SectionLen = GETNBITS(v32,12,12);
		v32 = GET32( 3);
		CamNitParser.NetworkId = GETNBITS(v32,0,16);
		dummy = GETNBITS(v32,16,2);
		CamNitParser.VersionNo = GETNBITS(v32,18,5);
		dummy = GETNBITS(v32,23,1);
		dummy = GETNBITS(v32,24,8);
		v32 = GET32( 7);
		dummy = GETNBITS(v32,0,8);
		dummy = GETNBITS(v32,8,4);
		CamNitParser.NetworkDescLen = GETNBITS(v32,12,12);
		ptr += 10;
		tableLen = tableLen - 10;
		v32 = GET32( 0);
		
		TraceNotice(m,"%s %d",__FUNCTION__, CamNitParser.NetworkDescLen);
		
		while(loopcount < CamNitParser.NetworkDescLen)
		{
			descLoopLen = 0;
			descTag = GETNBITS(v32,0, 8); 
			descLen = GETNBITS(v32,8, 8); 
			switch(descTag) {
			case 0x40:
				 CamNitParser.NetworkName_Descriptor.DescriptorTag = GETNBITS(v32,0,8);
				 CamNitParser.NetworkName_Descriptor.DescriptorLen = GETNBITS(v32,8,8);
				 CamNitParser.NetworkName_Descriptor.NetworkNameLen = GETNBITS(v32,16,0);
				 CamNitParser.NetworkName_Descriptor.NetworkNameLen = descLen;
				 descLoopLen = HSV_PARSER_MIN(80,CamNitParser.NetworkName_Descriptor.NetworkNameLen); 
				 ptr += 2;
				 memcpy(CamNitParser.NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
				 ptr += CamNitParser.NetworkName_Descriptor.NetworkNameLen;
				 v32 = GET32( 0);
				 CamNitParser.NetworkName_Descriptor.NetworkNameLen = descLoopLen;
				 CamNitParser.NetworkName_Descriptor.DescriptorValid = TRUE;
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
			
				v32 = GET32( 0);
			break;
		
			case 0x4A:
				if(CamNitParser.LinkageDescNum<10)
				{
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].DescriptorTag = GETNBITS(v32,0,8);
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].DescriptorLen = GETNBITS(v32,8,8);
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].TSID = GETNBITS(v32,16,16);
					 v32 = GET32( 4);
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].ONID = GETNBITS(v32,0,16);
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].ServiceId = GETNBITS(v32,16,16);
					 v32 = GET32( 8);
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].LinkageType = GETNBITS(v32,0,8);
					 CamNitParser.Linkage_Descriptor[CamNitParser.LinkageDescNum].DescriptorValid = TRUE;
					 CamNitParser.LinkageDescNum++;

					 //To handle DTVL test case 7.2.7.5
					 //ptr += 9;
					 ptr += 2 + descLen;
					 v32 = GET32( 0);
				}
				else
				{
					ptr += 2 + descLen;
				}
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
				
				v32 = GET32( 0);
			break;
		
			case 0x54:
				if(CamNitParser.CIPlusContentLabelDescNum<10)
				{
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].DescriptorTag = GETNBITS(v32,0,8);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].DescriptorLen = GETNBITS(v32,8,8);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].Content_Byte_Min = GETNBITS(v32,16,8);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].Content_Byte_Max = GETNBITS(v32,24,8);
					 v32 = GET32( 4);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].ISO_639_Language_Code = GETNBITS(v32,0,24);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen = GETNBITS(v32,24,0);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen = (descLen - 5);
					 descLoopLen = HSV_PARSER_MIN(80,CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen); 
					 ptr += 7;
					 memcpy(CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelChar,ptr,descLoopLen);
					 ptr += CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen;
					 v32 = GET32( 0);
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].LabelCharLen = descLoopLen;
					 CamNitParser.CIPlus_Content_Label_Descriptor[CamNitParser.CIPlusContentLabelDescNum].DescriptorValid = TRUE;
					 CamNitParser.CIPlusContentLabelDescNum++;
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
				tableLen = tableLen - (2 + descLen);
				loopcount += 2 + descLen;
				ptr += 2 + descLen;
				v32 = GET32( 0);
				break;
			}//endswitch
		}//endwhile
		dummy = GETNBITS(v32,0,4);
		mPopulateNIT();
		CamNitParser.TsLoopLen = GETNBITS(v32,4,12);
		ptr += 2;
		tableLen = tableLen - 2;
		v32 = GET32( 0);
	}
	else
	{
		tableLen = DataSize;
		nitLoopLen = nitLoopLen - tableLen;
		TraceErr(m, "%s @ 1033 tableLen %d *ptr %d *(ptr+1) %d", __FUNCTION__, tableLen, *ptr, *(ptr+1));
	}
	
	TraceErr(m, "%s @ 901 %d GET_PARSE_TABLE_LEN(cookie) %d tsloopIndex %d", __FUNCTION__, cookie, GET_PARSE_TABLE_LEN(cookie), tsloopIndex);
	while( (GET_PARSE_TABLE_LEN(cookie) >  0)  &&  ( tsloopIndex < 1 ))
	{
		CamNitParser.TsLoopData[tsloopIndex].NtkNameDescNum=0;
		CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum=0;
		CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum=0;
		CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum=0;
		CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum=0;
		CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum=0;
		CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum=0;
		loopcount = 0;
		
		if(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
		{
			CamNitParser.TsLoopData[tsloopIndex].TSID = GETNBITS(v32, 0,16);
			CamNitParser.TsLoopData[tsloopIndex].ONID = GETNBITS(v32, 16,16);
			v32 = GET32( 4);
			dummy = GETNBITS(v32,0,4);
			CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen = GETNBITS(v32, 4,12);
			ptr += 6;
			tableLen = tableLen - 6;
			v32 = GET32( 0);
			
			TraceNotice(m,"%s @ 1058 CamNitParser.TsLoopData[%d].TsDescLoopLen %d",__FUNCTION__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen);
		}
		else
		{
			CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen = tableLen;
			TraceNotice(m,"%s @ 1063 CamNitParser.TsLoopData[%d].TsDescLoopLen %d",__FUNCTION__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen);
		}
		
		while(loopcount < CamNitParser.TsLoopData[tsloopIndex].TsDescLoopLen)
		{
			descLoopLen = 0, loop1length = 0;
			descTag = GETNBITS(v32,0, 8); 
			descLen = GETNBITS(v32,8, 8);
			
			TraceNotice(m,"%s @ 1073 descTag %d descLen %d",__FUNCTION__, descTag, descLen);
			
			switch(descTag) {
			case 0x40:
				 CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorTag = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorLen = GETNBITS(v32, 8,8);
					 CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLen;
					 descLoopLen = HSV_PARSER_MIN(80,CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen); 
					 ptr += 2;
					 memcpy(CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkName,ptr,descLoopLen);
					 ptr += CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen;
					 v32 = GET32( 0);
					 CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.NetworkNameLen = descLoopLen;
				 CamNitParser.TsLoopData[tsloopIndex].NetworkName_Descriptor.DescriptorValid = TRUE;
			loopcount += 2 + descLen;
			tableLen = tableLen - (2 + descLen);
			
			v32 = GET32( 0);
			break;
			
			case 0x4A:
			if(CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum<80)
			{
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorTag = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorLen = GETNBITS(v32, 8,8);
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].TSID = GETNBITS(v32, 16,16);
				 v32 = GET32( 4);
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].ONID = GETNBITS(v32, 0,16);
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].ServiceId = GETNBITS(v32, 16,16);
				 v32 = GET32( 8);
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].LinkageType = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].Linkage_Descriptor[CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorValid = TRUE;
				 CamNitParser.TsLoopData[tsloopIndex].LinkageDescNum++;
		   ptr += 9;
			v32 = GET32( 0);
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
			if(CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum<30)
			{
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
				 ptr += 2;
				 v32 = GET32( 0 );
				 loop1index = 0, loop1length = 0, templen = sizeof(CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD)*20 ;
				 while( loop1length< HSV_PARSER_MIN(CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorLen, templen))
				 {
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].Frequency = GETNBITS(v32,0, 32); 
				 v32 = GET32( 4);
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].reserved = GETNBITS(v32,0, 12); 
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].FEC_Outer = GETNBITS(v32,12, 4); 
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].Modulation = GETNBITS(v32,16, 8); 
				 v32 = GET32( 7);
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].SymbolRate = GETNBITS(v32,0, 28); 
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSD[loop1index].FEC_Inner = GETNBITS(v32,28, 4); 
				 loop1length += 11;
				 loop1index++;
				 ptr += 11;
				 v32 = GET32( 0);
				 }
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].CDSDLen = loop1index;
				 CamNitParser.TsLoopData[tsloopIndex].CDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum].DescriptorValid = TRUE;
				 CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum++;
				 
				 TraceNotice(m,"%s CamNitParser.TsLoopData[%d].CDSDDescNum %d",__FUNCTION__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].CDSDDescNum);
			}
			else
			{
				ptr += 2 + descLen;
			}
			loopcount += 2 + descLen;
			tableLen = tableLen - (2 + descLen);
			
			v32 = GET32( 0);
			break;
			
			case 0x5A:
			TraceNotice(m,"%s @ %d CamNitParser.TsLoopData[%d].TDSDDescNum %d",__FUNCTION__, __LINE__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum);
			if(CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum<160)
			{
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
				 
				 ptr += 2;
				 v32 = GET32( 0 );
				 loop1index = 0, loop1length = 0, templen = sizeof(CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD)*20 ;
				 TraceNotice(m,"%s @ %d templen %d",__FUNCTION__, __LINE__, templen);
				 while( loop1length< HSV_PARSER_MIN(CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].DescriptorLen, templen))
				 {
				 TraceNotice(m,"%s @ %d loop1length %d",__FUNCTION__, __LINE__, loop1length);	
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].Frequency = GETNBITS(v32,0, 32); 
				 v32 = GET32( 4);
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].Bandwidth = GETNBITS(v32,0, 3); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].Priority = GETNBITS(v32,3, 1); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].TimeSlicingIndicator = GETNBITS(v32,4, 1); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].MPE_FECIndicator = GETNBITS(v32,5, 1); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].Reserved = GETNBITS(v32,6, 2); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].Constellation = GETNBITS(v32,8, 2); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].HierarchyInformation = GETNBITS(v32,10, 3); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].CodeRateHPSTream = GETNBITS(v32,13, 3); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].CodeRateLPSTream = GETNBITS(v32,16, 3); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].GuardInterval = GETNBITS(v32,19, 2); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].TransmissionMode = GETNBITS(v32,21, 2); 
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].OtherFrequencyFlag = GETNBITS(v32,23, 1); 
				 v32 = GET32( 7);
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSD[loop1index].Reserved = GETNBITS(v32,0, 32); 
				 loop1length += 11;
				 loop1index++;
				 ptr += 11;
				 v32 = GET32( 0);
				 }
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].TDSDLen = loop1index;
				 CamNitParser.TsLoopData[tsloopIndex].TDSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum].DescriptorValid = TRUE;
				 CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum++;
				 
				 TraceNotice(m,"%s CamNitParser.TsLoopData[%d].TDSDDescNum %d loop1index %d",__FUNCTION__, tsloopIndex, CamNitParser.TsLoopData[tsloopIndex].TDSDDescNum, loop1index);
			}
			else
			{
				ptr += 2 + descLen;
			}
			loopcount += 2 + descLen;
			tableLen = tableLen - (2 + descLen);
			
			v32 = GET32( 0);
			break;
			
			case 0x7F:
				descTagExtn = GETNBITS(v32, 0, 8);
				switch(descTagExtn)
				{
					case 0x0D:
						TempPtr = ptr;
						if(CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum<30)
						{
							TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
							CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
							CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
							CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].DescriptorTagExtn = GETNBITS(v32, 16,8);
							ptr += 3;
							v32 = GET32(0);
							loop1index = 0, loop1length = 0, templen = sizeof(CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].C2DSD)*20 ;
							while( loop1length< HSV_PARSER_MIN(CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].DescriptorLen, templen))
							{
								CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].C2DSD[loop1index].PLP_Id = GETNBITS(v32, 0, 8);
								CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].C2DSD[loop1index].SystemId = GETNBITS(v32,8, 16);
								ptr += 3;
								v32 = GET32(0);
								if((descLen - 4) > 0)
								{
									CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].C2DSD[loop1index].Frequency = GETNBITS(v32, 0, 32);
									ptr += 4;
									v32 = GET32( 0 );
								}
								loop1length += 7;
								loop1index++;
							}
							CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].C2DSDLen = loop1index;
							CamNitParser.TsLoopData[tsloopIndex].C2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum].DescriptorValid = TRUE;
							CamNitParser.TsLoopData[tsloopIndex].C2DSDDescNum++;
							ptr = TempPtr;
							ptr += 2 + descLen;
						}
						else
						{
							ptr += 2 + descLen;
						}
						loopcount += 2 + descLen;
						tableLen = tableLen - (2 + descLen);
			
						v32 = GET32( 0);
						break;
					case 0x04:
						TempPtr = ptr;
						if(CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum<30)
						{
							int TfsFlag;
							
							CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].DescriptorTag = GETNBITS(v32, 0,8);
							CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].DescriptorLen = GETNBITS(v32, 8,8);
							CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].DescriptorTagExtn = GETNBITS(v32, 16,8);
							
							ptr += 3;
							v32 = GET32(0);
							loop1index = 0, loop1length = 0, templen = sizeof(CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].T2DSD)*20 ;
							while( loop1length< HSV_PARSER_MIN(CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].DescriptorLen, templen))
							{
								CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].T2DSD[loop1index].PLP_Id = GETNBITS(v32, 24, 8);
								CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].T2DSD[loop1index].SystemId = GETNBITS(v32,0, 16);
								ptr += 3;
								v32 = GET32(0);
								if((descLen - 4) > 0)
								{
									unused = GETNBITS(v32, 0, 2);
									CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].T2DSD[loop1index].Bandwidth = GETNBITS(v32, 2, 4);
									unused = GETNBITS(v32, 6, 9);
									TfsFlag = GETNBITS(v32, 15, 1);
									unused = GETNBITS(v32, 16, 16);
									ptr += 4;
									v32 = GET32(0);
									if(TfsFlag == 1)
									{
										/* T2DSD:	Time-Freq Slicing is not supported */
										loop1length += 7;
									}
									else
									{
										CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].T2DSD[loop1index].Frequency = GETNBITS(v32, 0, 32);									
										ptr += 4;
										v32 = GET32(0);
										loop1length += 11;
									}
								}
								loop1index++;
							}
							CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].T2DSDLen = loop1index;
							CamNitParser.TsLoopData[tsloopIndex].T2DSD_Descriptor[CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum].DescriptorValid = TRUE;
							CamNitParser.TsLoopData[tsloopIndex].T2DSDDescNum++;
							ptr = TempPtr;
							ptr += 2 + descLen;
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
					
						ptr += 2 + descLen;
						loopcount += 2 + descLen;
						tableLen = tableLen - (2 + descLen);			
						v32 = GET32( 0);
						break;
				}
			case 0xCC:
			if(CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum<300)
			{
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].PrivateDataSpecifier = GET_PRIVATE_DATA_SPECIFIER( ptr );
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorTag = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorLen = GETNBITS(v32, 8,8);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceId = GETNBITS(v32, 16,16);
				 v32 = GET32( 4);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceType = GETNBITS(v32, 0,8);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].VisibleServiceFlag = GETNBITS(v32, 8,1);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].SelectableServiceFlag = GETNBITS(v32, 9,1);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].LogicalChannelNumber = GETNBITS(v32, 10,14);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen = GETNBITS(v32, 24,8);
				 descLoopLen = HSV_PARSER_MIN(80,CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen); 
				 ptr += 8;
				 memcpy(CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderName,ptr,descLoopLen);
				 ptr += CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen;
				 v32 = GET32( 0);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ProviderNameLen = descLoopLen;
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen = GETNBITS(v32, 0,8);
				 descLoopLen = HSV_PARSER_MIN(80,CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen); 
				 ptr += 1;
				 memcpy(CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceName,ptr,descLoopLen);
				 ptr += CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen;
				 v32 = GET32( 0);
				 CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen = descLoopLen;
				 /*if((CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].PrivateDataSpecifier == 0x00000040) || (mPrevPrivateDataSpecifierPresent))
				 {
				       if((mPrevPrivateDataSpecifierPresent) && ((CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].PrivateDataSpecifier != 0x00000040) ))
				       {
					   	mPrevPrivateDataSpecifierPresent = FALSE;
				       }
					else
					{
						mPrevPrivateDataSpecifierPresent = TRUE;
					}
				 	CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorValid = TRUE;
				 }
				 else
				 {
				 	CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorValid = FALSE;
				 }*/
				 
				 if(mPrevPrivateDataSpecifierPresent == TRUE)
				 	CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorValid = TRUE;
				 else
				 	CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].DescriptorValid = FALSE;
				 
				 TraceNotice(m,"%s %d %d %d %d",__FUNCTION__, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceId, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].LogicalChannelNumber, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceType, CamNitParser.TsLoopData[tsloopIndex].CIPlus_Service_Descriptor[CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum].ServiceNameLen);
				 
				 CamNitParser.TsLoopData[tsloopIndex].CIPlusServiceDescNum++;
				 
				 
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
				unused = GETNBITS(v32, 0,8);
				unused = GETNBITS(v32, 8,8);
				ptr += 2;
				v32 = GET32( 0);
				privateDataSpecifierId = GETNBITS(v32, 0,32);
				TraceNotice(m, "privateDataSpecifierId = %d", privateDataSpecifierId);
				if(privateDataSpecifierId == 0x40){
					mPrevPrivateDataSpecifierPresent = TRUE;
				}
				else{
					mPrevPrivateDataSpecifierPresent = FALSE;
				}
				TraceNotice(m, "mPrevPrivateDataSpecifierPresent = %d", mPrevPrivateDataSpecifierPresent);
				ptr += 4;
				loopcount += 2 + descLen;
				tableLen = tableLen - (2 + descLen);
			
				v32 = GET32( 0);
				break;
			
			default:
			loopcount += 2 + descLen;
			ptr += 2 + descLen;
			tableLen = tableLen - (2 + descLen);
			TraceNotice(m,"%s %d %d %d",__FUNCTION__, loopcount, descLen, tableLen);
			v32 = GET32( 0);
			break;
			}//endswitch
		}//endwhile descloop
	tsloopIndex++;
	loopcount = 0;
	CamNitParser.TsLoopDataNum = tsloopIndex;
	TraceNotice(m, "%s CamNitParser.TsLoopDataNum %d", __FUNCTION__, CamNitParser.TsLoopDataNum);
	retval = retval && mPopulateNIT();
	tsloopIndex = 0;
	}//endwhile tsloop
	if(HEADER_PLUS_FIRST_LOOP_PRESENT(cookie))
	{
		dummy = GETNBITS(v32,0,32);
		ptr += 4;
		TraceNotice(m, "%s dummy %d", __FUNCTION__, dummy);
	}
	}
	if(mCookie == EnmTypeCamNITData)
	{
		TraceNotice(m, "NIT strapi on completed!! ");
		strapiN_OnCompleted(0, mCookie);
	}
	return TRUE;
}//end function
int CHsvDvbCamSdm_Priv::camScanparser_GetCamInstallationMode(void){
	return 0;
}
void CHsvDvbCamSdm_Priv::camScanparser_SetCharacterCode(char* charCode){
	TraceNotice(m,"Character code from CAM is %d %d %d\n",charCode[0],charCode[1],charCode[2]);
	mcamCharCode = (Nat8)charCode[0];//mFindTableCode((Nat8 *)charCode);
	TraceNotice(m,"Character code after conversion is %d",mcamCharCode);
	return ;
}

/*  
    From ETSI EN 300 468, table A3 (single byte character table codes):
    0x01 = ISO 8859-5
    0x02 = ISO 8859-6
    0x03 = ISO 8859-7
    0x04 = ISO 8859-8
    0x05 = ISO 8859-9
    0x06 = ISO 8859-10
    0x07 = ISO 8859-11
    0x09 = ISO 8859-13
    0x0a = ISO 8859-14
    0x0b = ISO 8859-15
    0x10 = (3 byte encoding, see table A4)
    0x11 = ISO 10646 (Basic Multilingual Plane)
    0x12 = KSX1001-2004 (Korean)
    0x13 = GB-2312-1980 (Simplified Chinese)
    0x14 = Big5 subset of ISO 10646
    0x15 = UTF8 encoding of ISO 10646 

    From ETSI EN 300 468, table A4 (three byte character table codes):
    0x10 0x00 0x01 = ISO 8859-1
    0x10 0x00 0x02 = ISO 8859-2
    0x10 0x00 0x03 = ISO 8859-3
    0x10 0x00 0x04 = ISO 8859-4
    0x10 0x00 0x05 = ISO 8859-5
    0x10 0x00 0x06 = ISO 8859-6
    0x10 0x00 0x07 = ISO 8859-7
    0x10 0x00 0x08 = ISO 8859-8
    0x10 0x00 0x09 = ISO 8859-9
    0x10 0x00 0x0a = ISO 8859-10
    0x10 0x00 0x0b = ISO 8859-11
    0x10 0x00 0x0d = ISO 8859-13
    0x10 0x00 0x0e = ISO 8859-14
    0x10 0x00 0x0f = ISO 8859-15

    From cesgpi_mwchar.c (tvApp), resulting table codes (that we are converting to) are:
    0x00 = ISO 6937
    0x01 = ISO 8859-5 
    0x02 = ISO 8859-6 
    0x03 = ISO 8859-7 
    0x04 = ISO 8859-8 
    0x05 = ISO 8859-9
    0x06 = ISO 8859-2
    0x07 = ISO 8859-15
    0x08 = ISO 8859-4
    0x09 = ISO 8859-13
    0x11 = ISO/IEC 10646-1 
    0x13 = Chinese charater set GB2312 mixed up with english
    0x15 = UTF8 encoding of ISO 10646 
    */
Nat8 CHsvDvbCamSdm_Priv::mFindTableCode(Nat8* str)
{
    Nat8 charCode = DEFAULT_CHAR_SET;

    switch (*str)
    {
        case 0x00:
        case 0x01: 
        case 0x02: 
        case 0x03: 
        case 0x04: 
        case 0x05:
        case 0x09:
        case 0x11:
        case 0x13:
        case 0x15:
            /* these single byte table IDs map directly */
            charCode = *str;
            break;
        case 0x0b:
            charCode = 0x07;
            break;
        case 0x10:
            {
                int nextCode = ((str[1] << 8) | (str[2]));
                switch (nextCode)
                {
                    case 0x0002: 
                        charCode = 0x06;
                        break;            
                    case 0x0004: 
                        charCode = 0x08;
                        break;            
                    case 0x0005: 
                        charCode = 0x01;
                        break;            
                    case 0x0006: 
                        charCode = 0x02;
                        break;            
                    case 0x0007: 
                        charCode = 0x03;
                        break;            
                    case 0x0008:
                        charCode = 0x04;
                        break;            
                    case 0x0009: 
                        charCode = 0x05;
                        break;            
                    case 0x000d: 
                        charCode = 0x09;
                        break;            
                    case 0x000f: 
                        charCode = 0x07;
                        break;            
                    default:
                        break;            
                }
            }
            break;
        default:
			/* brg36mgr#158094: When the predefined character code is not present, 
				fallback to DEFAULT_CHAR_SET */
			if(!(*str >= 0x20))
			{
				ASSERT(!"Unsupported Character set in the stream");
			}
            break;            
    }


    return charCode;
}



