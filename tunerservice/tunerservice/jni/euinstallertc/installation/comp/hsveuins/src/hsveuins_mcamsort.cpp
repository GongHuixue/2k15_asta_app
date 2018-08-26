/**********************************************************************
 *
 *   C Source:       hsveuins_mcamsort.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Tue Mar 27 14:17:26 2012 %
 *
 **********************************************************************/
#include "_hsveuins_mcamsort.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mcamsort")

/*****   MACROS   *****/

/* ChannelLib Database Tables */



#ifndef __cplusplus

#endif





/*****   static functions   *****/




/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvEuropeInstallation_mcamsort_Priv::s__mCamSortPmp;

char CHsvEuropeInstallation_mcamsort_Priv::s__TempString[50];

/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

void CHsvEuropeInstallation_mcamsort_Priv::mCamSortPumpHandler(int Event, Nat32 Param)
{
    
	TraceNotice(m,"%s CurrentStep %d Index %d", __FUNCTION__, Event, Param);

    switch(Event)
    {
		case EvSortStart:
        case EvSortContinue:
            mSortPresets((int)Param);
            break;  
			
        case EvSortComplete:
			sortN_OnEvent(sortN_EventSortComplete, Param);
            break;
			
        default:
            ASSERT(!"Unknown Step in sorting");
            break;
    }
}

void CHsvEuropeInstallation_mcamsort_Priv::mSortPresets(int RunningRecordIndex)
{
	int i = 0, j = 0;
	HsvPgdatDigServiceData SvcData;
	
	TraceNotice(m,"%s RunningRecordIndex %d", __FUNCTION__, RunningRecordIndex);
	
	/* Sorting Algorithm is simple as the InvalidLCN or conflicts are resolved in DataAcq module & strapi modules respectively , so life is easy here :).. */
	for(i = 0, j = 0; (RunningRecordIndex >= 0) && (j < MAX_PRESETS_SORT_PER_STEP); RunningRecordIndex--, j++)
	{
		if(pgdb_GetByIndex(SERVICE_TABLE, RunningRecordIndex, (Address)&SvcData))
		{
			if(PRESET_NOT_ALLOCATED(SvcData.PresetNumber))
			{
				mAddEntryToPresetTable(&SvcData);
			}
		}
		else
		{
			TraceErr(m, "GetByIndex failed for index in table", RunningRecordIndex, SERVICE_TABLE);
		}
	}
	
	if(RunningRecordIndex >= 0)
	{
		pmp_PmpSend(mCamSortPmp, EvSortContinue, RunningRecordIndex);
	}
	else
	{
		pmp_PmpSend(mCamSortPmp, EvSortComplete, TRUE);
	}
}

void CHsvEuropeInstallation_mcamsort_Priv::mAddEntryToPresetTable(HsvPgdatDigServiceData *SvcData)
{
	HsvPgdatPresetData PresetData;
	
	PresetData.PresetNumber = SvcData->LCN;
	PresetData.Type = HsvOnePart;

	ASSIGN_PRESET_FROM_SVC(PresetData,(*SvcData));
	ASSIGN_DEFAULTCOOKIES(*SvcData);

	TraceNotice(m,"Addition of Preset %d by <%d %d %s>", PresetData.PresetNumber, SvcData->OriginalNetworkId, SvcData->ServiceId, (mGetServiceName(SvcData) == TRUE)? TempString: "\0");
	
	PresetData.UniqueNodeId  = -1;// Invalid Node id 
	pgdb_Add(PRESET_TABLE, (Address)&PresetData);
	
	SvcData->PresetNumber = PresetData.PresetNumber;
	pgdb_Update(SERVICE_TABLE, (Address)SvcData);
}

void CHsvEuropeInstallation_mcamsort_Priv::icamsortpow_Init()
{
    mCamSortPmp = pmp_PmpCreateEx( pen_PumpEngine, mCamSortPumpHandler, FALSE, "hsvdvbcamins_mSort" );
}

void CHsvEuropeInstallation_mcamsort_Priv::icamsortpow_TurnOn()
{

}

void CHsvEuropeInstallation_mcamsort_Priv::icamsortpow_TurnOff()
{

}

/*****   Sort interface   *****/

void CHsvEuropeInstallation_mcamsort_Priv::icamsort_Initialise()
{
	/* For Future use if required */
}

void CHsvEuropeInstallation_mcamsort_Priv::icamsort_Sort(void)
{
	int NoOfRecords = pgdb_GetNoRecords(SERVICE_TABLE);
	 
    TraceNotice(m, "%s NoOfRecords %d", __FUNCTION__, NoOfRecords);
	
	if(NoOfRecords > 0)
	{
		/* starting indexing with last record */
		pmp_PmpSend(mCamSortPmp, EvSortStart, (NoOfRecords - 1));
	}
	else
	{
		/* indicate failure with third param, so as the client module can use it */
		pmp_PmpSend(mCamSortPmp, EvSortComplete, (Nat32)FALSE);
	}
}

void CHsvEuropeInstallation_mcamsort_Priv::icamsort_UpdateDigitalPreset(HsvPgdatDigServiceData *psvcdat)
{
    HsvPgdatPresetData presetdat;

    if(TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)psvcdat))
    {
        presetdat.PresetNumber = psvcdat->PresetNumber;
        if(TRUE == pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
        {
            ASSIGN_PRESET_FROM_PSVC(presetdat,psvcdat);     

            pgdb_Update (PRESET_TABLE, (Address)&presetdat);
			
            TraceNotice(m,"Updated Preset %d with new information from <%d,%d,%d,%d>\n", presetdat.PresetNumber,psvcdat->OriginalNetworkId, psvcdat->ServiceId, psvcdat->StreamPriority, psvcdat->Frequency);
        }
    }
}


/*****    Used for logs purpose for debuggign services installed/ sorted   *****/
Bool CHsvEuropeInstallation_mcamsort_Priv::mGetServiceName(HsvPgdatDigServiceData *SvcData)
{
	int i = 0;
	
	for(i = 0; SvcData->ChannelName[i] !=0; i++)
	{
		TempString[i] = (char) SvcData->ChannelName[i];
	}	
	TempString[i] = 0;
	
	return ((i>0)? TRUE: FALSE);
}
