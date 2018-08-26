/*
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary information of Koninklijke
  *  Philips Electronics N.V. and is confidential in nature.  Under no circumstances is this software to beexposed  
  *  to or placed under an Open Source License of any type without the expressed written permission of 
  *  Koninklijke Philips Electronics N.V.
  *
  *  %name: hsvdvbsn_mSort.c %
  *  %version:  TVG_1 %
  *  %date_modified:  %
  *  %derived_by:  shibus % 
  */

#include "_hsvdvbsn_mSort.h"

#include "nsort.h"


TRACESYMBOL (m, "dvb/installation/hsvdvbsn/sort")

/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/

//todo delete this


int CHsvDvbsN_mSort_Priv::s__mCurrentRadioIndex = 0;

int CHsvDvbsN_mSort_Priv::s__mCurrentPresetIndex = 0;

Pump CHsvDvbsN_mSort_Priv::s__mSortingPmp;













/*****************************************************************************************/

/* provides IHsvPower isortpow */
void CHsvDvbsN_mSort_Priv::isortpow_Init ()
{  
    TraceNotice (m, "%s() %d\n", __FUNCTION__, __LINE__);
    PrintfNotice ("Sort Pow Init being called \n");
    mSortingPmp = pmp_PmpCreateEx (pen_PumpEngine, SortingHandler, TRUE, "hsvdvbsinsN_msort");   
}

void CHsvDvbsN_mSort_Priv::isortpow_TurnOn (void)
{  
    TraceNotice (m, "%s() %d\n", __FUNCTION__, __LINE__);
    // Do Nothing
}

void CHsvDvbsN_mSort_Priv::isortpow_TurnOff (void)
{  
    TraceNotice (m, "%s() %d\n", __FUNCTION__, __LINE__);
    // Do Nothing
}

/* provides IHsvSorting isort */
void CHsvDvbsN_mSort_Priv::insort_Sort (Nat32 packageIndex)
{
    int mode;
    int state;
    int retval;
    
    TraceNotice (m, "%s() %d\n", __FUNCTION__, __LINE__);
    
    retval = rins_GetCurrentInstallationState (&mode, &state); 

    if (mode == AUTO_MODE)
    {
        mCurrentRadioIndex = 0;
        mCurrentPresetIndex = 0;
    }
    iinsN_OnEvent (iinsN_EventSortingStarted, 0);
    pmp_PmpSend (mSortingPmp, SORT_HONOURED_SERVICES, 0);
}

void CHsvDvbsN_mSort_Priv::SortingHandler (int event, Nat32 startIndex)
{
    TraceNotice (m, "event = %d, startIndex = %d", event, (int) startIndex);

    switch (event)
    {
        case SORT_HONOURED_SERVICES:
            mSortHonouredServices (FALSE, startIndex);
            break;
        case SORT_HONOURED_RADIO_SERVICES:
            mSortHonouredServices (TRUE, startIndex);
            break;
        case SORT_NONHONOURED_SERVICES:
            mSortNonHonouredServices (FALSE, startIndex);
            break;
        case SORT_NONHONOURED_RADIO_SERVICES:
            mSortNonHonouredServices (TRUE, startIndex);
            break;
        case SORT_COMPLETE:
            iinsN_OnEvent (iinsN_EventSortCompleted, 0);
            break;
        default:
            break;
        }
}

void CHsvDvbsN_mSort_Priv::mSortHonouredServices (Bool checkForRadioServices, int startIndex)
{
    int i = 0;
    int nextIndex = 0;
    HsvPgdatDigServiceData svcData;
    int numOfRecs = pgdb_GetNoRecords (SERVICE_TABLE);
    int currentSortStep = (checkForRadioServices ? SORT_HONOURED_RADIO_SERVICES : SORT_HONOURED_SERVICES);
           
    for (i = startIndex; (i < startIndex + STEP_SIZE) && (i < numOfRecs); i++)
    {
        if (TRUE == pgdb_GetByIndex (SERVICE_TABLE, i, (Address) &svcData))
        {
            if (VALID_LCN_RANGE(svcData.LCN) && (checkForRadioServices == IS_RADIO_SERVICE(svcData.ServiceType)))
            {               
                if (PRESET_NOT_ALLOCATED(svcData))
                {
                    mDigitalPresetEntryforValidLCN (i);                   
                }
            }
        }
        else
        {
            TraceErr (m, "Error : This should not be printed!!");
        }
    }
    
    if(i < numOfRecs)
    {
        nextIndex = startIndex + STEP_SIZE;
    }
    else
    {
        nextIndex = 0;
        currentSortStep++;
    }
    TraceNotice (m, "Pmp send done with event = %d nextIndex = %d \n", currentSortStep, nextIndex);
    pmp_PmpSend (mSortingPmp, currentSortStep, nextIndex);
}


void CHsvDvbsN_mSort_Priv::mSortNonHonouredServices(Bool checkForRadioServices, int startIndex)
{
    int i = 0;    
    int nextIndex = 0;
    HsvPgdatDigServiceData svcData;
    int numOfRecs = pgdb_GetNoRecords (SERVICE_TABLE);
    int currentSortStep = (checkForRadioServices ? SORT_NONHONOURED_RADIO_SERVICES : SORT_NONHONOURED_SERVICES);
    
    for(i = startIndex; (i < startIndex + STEP_SIZE) && (i < numOfRecs); i++)
    {
        if (TRUE == pgdb_GetByIndex (SERVICE_TABLE, i, (Address) &svcData))
        {
            if (PRESET_NOT_ALLOCATED(svcData) && (!VALID_LCN_RANGE(svcData.LCN)) && 
                 (checkForRadioServices == IS_RADIO_SERVICE(svcData.ServiceType)))
            {
                mDigitalPresetEntryforInValidLCN (i);
            }
        }
    }
    
    if (i < numOfRecs)
    {
        nextIndex = startIndex + STEP_SIZE;
    }
    else
    {
        nextIndex =0;
        currentSortStep++;
    }
    
    TraceNotice (m,"Pmp send done with event = %d\r\n", currentSortStep);
    pmp_PmpSend (mSortingPmp, currentSortStep,nextIndex);
}

void CHsvDvbsN_mSort_Priv::mAddEntryToPresetTable (HsvPgdatDigServiceData *svcData, int presetNo)
{
    HsvPgdatPresetData presetData;

    pgdb_Initialise (pgdbconst_Preset, (Address) &presetData);
    svcData->PresetNumber = presetNo;
    
    presetData.PresetNumber = svcData->PresetNumber;
    presetData.OriginalNetworkId = svcData->OriginalNetworkId;
    presetData.ServiceId = svcData->ServiceId;
    presetData.Tsid = svcData->Tsid;
    presetData.Tpid = svcData->Tpid;
    presetData.Frequency = svcData->Frequency;
    presetData.Polarization = svcData->Polarization;
    presetData.LnbNumber = svcData->LnbNumber;
	presetData.VisibleService = svcData->VisibleService;
	presetData.NumericSelect = svcData->NumericSelect;
    
    TraceNotice(m, "SID = %d, PresetNo = %d", presetData.ServiceId, presetNo);
    
    if (TRUE != pgdb_GetByKey (PRESET_TABLE, (Address) &presetData))
    {
        pgdb_Add (PRESET_TABLE, (Address) &presetData);
        pgdb_Update (SERVICE_TABLE, (Address) svcData);
    }
    else
    {
        TraceErr(m, "!!Preset is already present in PRESET_TABLE\n");
    }
}


void CHsvDvbsN_mSort_Priv::mDigitalPresetEntryforValidLCN (int dbIndex)
{
    HsvPgdatDigServiceData svcData;
    HsvPgdatPresetData presetData;

    if (TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbIndex, (Address) &svcData))
    {
        REVALIDATE(svcData.LCN);

        /* Check if LCN preset is occupied */
        presetData.PresetNumber = svcData.LCN;
        if (pgdb_GetByKey (PRESET_TABLE, (Address) &presetData))
        {  
            //preset is occupied, service will get the preset number in non hon
            INVALIDATE(svcData.LCN);
            pgdb_Update (SERVICE_TABLE,(Address) &svcData);
        }
        else
        {
            /* That preset is free. So just grab it */
            mAddEntryToPresetTable (&svcData, svcData.LCN);
        }
    }
}

void CHsvDvbsN_mSort_Priv::mDigitalPresetEntryforInValidLCN (int dbIndex)
{
    int fromPreset = 0;
    int toPreset = 0;
    int currentPresetIndex = 0;
    HsvPgdatDigServiceData svcData;

    if (TRUE == pgdb_GetByIndex (SERVICE_TABLE, dbIndex, (Address) &svcData))
    {      
        toPreset =  (IS_RADIO_SERVICE(svcData.ServiceType)) ? MAX_RADIO_PRESET : RADIO_PRESET_OFFSET;
        fromPreset  = (IS_RADIO_SERVICE(svcData.ServiceType)) ? RADIO_PRESET_OFFSET : TV_PRESET_OFFSET;
        
        currentPresetIndex = mGetPresetNoForService (svcData, fromPreset, toPreset);

        if(currentPresetIndex > 0)
        {
            mAddEntryToPresetTable (&svcData, currentPresetIndex);            
            currentPresetIndex = currentPresetIndex + 1;
        }
    }
    else
    {
        TraceNotice(m,"%d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}


int CHsvDvbsN_mSort_Priv::mGetPresetNoForService (HsvPgdatDigServiceData svcData, int fromPreset, int toPreset)
{
    int currentPresetIndex = 0;
    HsvPgdatPresetData presetData;

    currentPresetIndex  = GETCURRENTINDEX(svcData.ServiceType);

    presetData.PresetNumber = currentPresetIndex; 
    //presetdat.Type = HsvOnePart;

    if ((currentPresetIndex == 0) || pgdb_GetByKey (PRESET_TABLE, (Address) &presetData) ||
         (currentPresetIndex < fromPreset) || (currentPresetIndex > toPreset))
    {
        if ((currentPresetIndex = mFirstAvailableGapInPresetList (fromPreset, toPreset)) == INVALID_PRESET)
        {
            //If we dont get any then start placing the service from MIXED_PRESET_OFFSET
            currentPresetIndex = mFirstAvailableGapInPresetList (MIXED_PRESET_OFFSET, MAX_PRESET_NUMBER);
        }
        TraceNotice(m,"%s:: %d CurrentPresetIndex = %d", __FUNCTION__, __LINE__, currentPresetIndex);
    }
    if(IS_RADIO_SERVICE(svcData.ServiceType))
    {
        mCurrentRadioIndex = currentPresetIndex;
    }
    else
    {
        mCurrentPresetIndex = currentPresetIndex;
    }
    return currentPresetIndex;
}



int CHsvDvbsN_mSort_Priv::mFirstAvailableGapInPresetList(int fromPreset, int toPreset)
{
    int i = 0;
    int previousPreset = fromPreset;
    int Retval = INVALID_PRESET;
    int numOfRecs = pgdb_GetNoRecords (PRESET_TABLE);
    HsvPgdatPresetData presetData;

    if (numOfRecs == 0)
    {
        Retval = fromPreset + 1;
    }
    else if (numOfRecs == 1)
    {
        if (TRUE == pgdb_GetByIndex (PRESET_TABLE, 0, (Address) &presetData))
        {
            Retval = ((presetData.PresetNumber == 1) && (presetData.PresetNumber >= fromPreset)) ? (presetData.PresetNumber + 1) : (fromPreset + 1);
        }
        else
        {
            /* error condition should not occur */
            Retval = fromPreset + 1;
        }
    }
    else
    {
        presetData.PresetNumber = (fromPreset + 1);
        if (FALSE == pgdb_GetByKey (PRESET_TABLE, (Address) &presetData))
        {
            Retval = fromPreset + 1;
        }
        else
        {
            for (i = (numOfRecs - 1) ; i >= 0; i--)
            {
                pgdb_GetByIndex (PRESET_TABLE, i, (Address) &presetData);

                if (presetData.PresetNumber <= fromPreset) 
                {
                    previousPreset = presetData.PresetNumber;
                    if (i == 0)
                    {
                        Retval = fromPreset + 1;
                        break;
                    }   
                    else
                    {
                        continue;
                    }
                }

                if ((previousPreset >= fromPreset) && (presetData.PresetNumber - previousPreset) > 1)
                {
                    /* Found the first gap in needed range */
                    Retval = previousPreset + 1; 
                    break;
                }
                else
                {
                    if (i == 0)
                    {
                        Retval = (presetData.PresetNumber < toPreset) ? (presetData.PresetNumber + 1) : INVALID_PRESET; 
                        break;
                    }               
                    else
                    {
                        previousPreset = presetData.PresetNumber;
                    }
                }
            }
            //  TraceNotice(m,"%s %d Retval %d PreviousPreset %d presetdat.PresetNumber %d NoOfRecs %d", __FUNCTION__, __LINE__, Retval, PreviousPreset, presetdat.PresetNumber, NoOfRecs);
            Retval = (Retval <= toPreset)? Retval : INVALID_PRESET;
        }
    }
    return Retval;
}
