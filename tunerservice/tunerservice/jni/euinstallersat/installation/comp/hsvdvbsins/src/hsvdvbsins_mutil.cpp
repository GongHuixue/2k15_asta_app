/**********************************************************************
 *
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *
 *
 *	C Source:		hsvdvbsins_mutil.c
 *	Instance:		
 *	Description:	
 *	%created_by:	   aneeshc %
 *	%date_created:	   Thu Apr 25 11:59:56 2013 %
 *
**********************************************************************/
#include "_hsvdvbsins_mutil.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsins_m")

/****************************************************************************
 * Macros and types
 ****************************************************************************/
#define		PTC_TABLE							    (pgdbconst_Satellite | pgdbconst_DigitalTS)

FrequencyDataList CHsvDvbsInstallation_mutil_Priv::s__FrequencyData[MAX_TP_PER_SATELLITE];

int CHsvDvbsInstallation_mutil_Priv::s__NumOfEntries;


HsvBarkerMuxFlashData CHsvDvbsInstallation_mutil_Priv::s__mBarkerMuxFlashData =
{
	BARKER_MUX_FILE_PATH, {{BARKER_MUX_FILE_CURRENT_PRIMARYVERSION, BARKER_MUX_FILE_CURRENT_SECONDARYVERSION, sizeof(AppApiMultiplex)}, 0, 0}
};





/****************************************************************************
 * Static functions
 ****************************************************************************/

Nat32 CHsvDvbsInstallation_mutil_Priv::CalculateCrc32( void* buffer, int size )
{
    /* http://www.cl.cam.ac.uk/Research/SRG/bluebook/21/crc/crc.html */
    Nat32 Result = 0xFFFFFFFF;
    int   i = 0;
    int   j = 0;
    Nat8  Octet = 0;
    Nat8 *Buf   = (Nat8*)buffer;
    
    for ( i = 0; i < size; i++ )
    {
        Octet = *Buf++;
        for ( j = 0; j < 8; j++ )
        {
            Result = ( Result << 1 );
            if ( ( Octet >> 7 ) ^ ( Result >> 31 ) )
            {
                Result ^= 0x04C11DB7;
            }
            Octet <<= 1;
        }
    }
    
    return ~Result;             /* The complement of the remainder */
}

HsvBarkerMuxHeaderCompatibility CHsvDvbsInstallation_mutil_Priv::mCheckVersions(HsvBarkerMuxFlashHeader* Header)
{
    HsvBarkerMuxHeaderCompatibility    ret = HsvVersionsDontMatch;
    Nat32 HeaderCRC = 0;

    HeaderCRC = CalculateCrc32((Address)Header, sizeof(mBarkerMuxFlashData.Header.Header));
	         
	if(mBarkerMuxFlashData.Header.Header.PrimaryVersion == Header->Header.PrimaryVersion)
    {
		ret = HsvPrimaryVersionMatch;		
	    if(mBarkerMuxFlashData.Header.Header.SecondaryVersion == Header->Header.SecondaryVersion)
        {
			if(HeaderCRC == Header->HeaderCRC)
			{							
				ret = HsvVersionsMatch;
			}
			else
			{				
				ret = HsvCrcError;
			}
        }
		else if (mBarkerMuxFlashData.Header.Header.SecondaryVersion < Header->Header.SecondaryVersion)
		{
			ret = HsvSecondaryVersionHigh;
		}
    }	
    return ret;
}

 
Bool CHsvDvbsInstallation_mutil_Priv::iutil_CheckFreqDuplicationwithRolFact(Nat32 Newfreq,Nat32 Oldfreq,Nat32 SymbolRate)
{
	int FreqDiff = 0;	
	Nat32 Tempsym = 0;        
	Bool retVal = FALSE;

	FreqDiff = Oldfreq - Newfreq;  
	Tempsym = SymbolRate/1000;
	
	if( abs(FreqDiff) < ( 135*Tempsym/200 ))
	{
		retVal = TRUE;
	}
	TraceDebug(m, "Ret[%d][%d][%d][%d]",retVal,abs(FreqDiff),( 135*Tempsym/200 ),Tempsym);
	return retVal;
}

/* Provides iutil */

void CHsvDvbsInstallation_mutil_Priv::iutil_ResetData (void)
{
    memset (FrequencyData, 0x00, sizeof(FrequencyData));
    NumOfEntries = 0;
}

void CHsvDvbsInstallation_mutil_Priv::iutil_AddEntryToList (FrequencyDataList  *Entry)
{
    if ((Entry) && (NumOfEntries < MAX_TP_PER_SATELLITE))
    {
        FrequencyData[NumOfEntries].LnbNumber = Entry->LnbNumber;
        FrequencyData[NumOfEntries].Frequency = Entry->Frequency;
        FrequencyData[NumOfEntries].Polarization = Entry->Polarization;
        FrequencyData[NumOfEntries].OriginalNetworkId = Entry->OriginalNetworkId;
        FrequencyData[NumOfEntries].TsId = Entry->TsId;
		FrequencyData[NumOfEntries].SymRate = Entry->SymRate;
        NumOfEntries++;
    }
    else
    {
        TraceNotice (m, "Warning: Trying add more entries than array limit");
    }
}

Bool CHsvDvbsInstallation_mutil_Priv::iutil_IsDuplicate (FrequencyDataList  *Entry)
{
    int     Count;
    Bool    Duplicate = FALSE;
	Nat32	PackageId = pins_GetAttribute(pins_InstallationServiceScan, pins_AttributePackageId);

    for (Count = 0; Count < NumOfEntries; Count++)
    {
        if ( (COMPARE_ABS_VALUES(FrequencyData[Count].LnbNumber, Entry->LnbNumber)) &&
             (COMPARE_ABS_VALUES(FrequencyData[Count].Polarization,Entry->Polarization)) &&
             (iutil_CheckFreqDuplicationwithRolFact(Entry->Frequency,FrequencyData[Count].Frequency, Entry->SymRate)) 
			)
        {
			if( (ISDIGITURK_PACKAGEID(PackageId)) || ((COMPARE_ABS_VALUES(FrequencyData[Count].OriginalNetworkId,Entry->OriginalNetworkId)) &&
             (COMPARE_ABS_VALUES(FrequencyData[Count].TsId, Entry->TsId)) ))
			{
				Duplicate = TRUE;
				Entry ->Frequency = FrequencyData[Count].Frequency;
			}
        }
    }

    return Duplicate;
}

Bool CHsvDvbsInstallation_mutil_Priv::iutil_WriteBarkerMuxData(HsvBarkerMuxData Data)
{
	int i = 0, retval = FALSE;
	HsvPgdatDigTSData			TsData;
	
	TraceNotice (m, "BARKER Mux Addition Number of entries: %d ", Data.NoOfRecords);
	for (i = 0; i < Data.NoOfRecords; i++)
	{
		TsData.LnbNumber = Data.Mux[i].Params.TuningParams.DVBSParam.sat_id;
		TsData.Frequency = Data.Mux[i].Params.TuningParams.DVBSParam.Frequency;
		TsData.Polarization = Data.Mux[i].Params.TuningParams.DVBSParam.tp_id & 0x01;
		
		if( pgdb_GetByKey(PTC_TABLE, (Address )&TsData) == TRUE )
		{
			TsData.BarkerMux = TRUE;
			pgdb_Update (PTC_TABLE, &TsData);
			retval = TRUE;
			TraceNotice (m, "BARKER Mux Addition Succesful: Lnb %d Freq %d Pol %d ", TsData.LnbNumber, TsData.Frequency, TsData.Polarization);
		}
		else
		{
			/*Initialize with default values*/
			pgdb_Initialise(pgdbconst_DigitalTS, (Address) &TsData);
			TsData.LnbNumber = Data.Mux[i].Params.TuningParams.DVBSParam.sat_id;
			TsData.Frequency = Data.Mux[i].Params.TuningParams.DVBSParam.Frequency;
			TsData.Polarization = Data.Mux[i].Params.TuningParams.DVBSParam.tp_id & 0x01;
			TsData.BarkerMux = TRUE;
			pgdb_Add(PTC_TABLE, (Address )&TsData);
			TraceNotice (m, "BARKER Mux Addition as new Mux Succesful: Lnb %d Freq %d Pol %d ", TsData.LnbNumber, TsData.Frequency, TsData.Polarization);
		}
	}

	return retval;
}

Bool CHsvDvbsInstallation_mutil_Priv::iutil_ReadBarkerMuxData(HsvBarkerMuxData *Data)
{
	int i = 0, retval = FALSE;
	HsvPgdatDigTSData			TsData;
	int NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);
	
	TraceNotice (m, "BARKER Mux Reading Number of entries: %d ", NoOfTSTables);
	if (Data)
	{
		Data->NoOfRecords = 0;
		for (i = 0; i < NoOfTSTables; i++)
		{
			if ((pgdb_GetByIndex (PTC_TABLE, i, &TsData) == TRUE) && (TsData.BarkerMux == TRUE))
			{
				if (Data->NoOfRecords <= MAX_NUM_BARKER_MUX)
				{
					Data->Mux[Data->NoOfRecords].OnId = TsData.OriginalNetworkId;
					Data->Mux[Data->NoOfRecords].TsId = TsData.Tsid;
					Data->Mux[Data->NoOfRecords].Params.TuningParams.DVBSParam.sat_id = TsData.LnbNumber;
					Data->Mux[Data->NoOfRecords].Params.TuningParams.DVBSParam.tp_id = TsData.Tpid;
					Data->Mux[Data->NoOfRecords].Params.TuningParams.DVBSParam.Frequency = TsData.Frequency;
					Data->Mux[Data->NoOfRecords].Params.TuningParams.DVBSParam.SymbolRate = TsData.SymbolRate;
					Data->NoOfRecords++;
					retval = TRUE;
				}
			}
		}

			TraceNotice (m, "Barker Mux Reading No of Entries %d ", Data->NoOfRecords);
	}
	

	
/*	
	
	HsvBarkerMuxFlashHeader    Header;
    HsvBarkerMuxHeaderCompatibility    Compatibility = HsvVersionsDontMatch;
	
	TraceNotice(m, "%s", __FUNCTION__);
	fp = fopen(mBarkerMuxFlashData.BarkerMuxFileName, "rb" );
	
	if( (fp != NULL) && Data)
	{
		fread((Address)&(Header), sizeof(HsvBarkerMuxFlashHeader), 1, fp);
    
		Compatibility = mCheckVersions(&(Header));
		switch(Compatibility)
		{
			case HsvVersionsMatch:
			case HsvPrimaryVersionMatch:
					Data->NoOfRecords = mBarkerMuxFlashData.Header.NoOfRecords;
					for(i = 0; i < mBarkerMuxFlashData.Header.NoOfRecords; i++)
					{
						fread(&(Data->Mux[i]), mBarkerMuxFlashData.Header.Header.RecordSize, 1, fp);
					}
					retval = TRUE;
					fclose(fp);
				break;
			case HsvSecondaryVersionHigh:
				break;
			case HsvVersionsDontMatch:
				TraceNotice(m,"%s File Version mismatch",__FUNCTION__);
				break;
			case HsvCrcError:
				TraceNotice(m,"%s : Channel table CRC check failed for file %s ",__FUNCTION__, mBarkerMuxFlashData.BarkerMuxFileName);
				break;				
			default:
				ASSERT(FALSE);
				break;	
		}
	}
	*/
	return retval;
}

void CHsvDvbsInstallation_mutil_Priv::iutil_ResetBarkerMuxData()
{	
	TraceNotice(m, "%s", __FUNCTION__);
	unlink(mBarkerMuxFlashData.BarkerMuxFileName);
}





