/*****************************************************************************************
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary information of Koninklijke
  *  Philips Electronics N.V. and is confidential in nature.  Under no circumstances is this software to be exposed  
  *  to or placed under an Open Source License of any type without the expressed written permission of 
  *  Koninklijke Philips Electronics N.V.
  *
  *  %name: hsvdvbsopprofile_mSort.cpp %
  *  %version:  TVG_Android_1 %
  *  %date_modified:  %
  *  %derived_by:  anuma %
  *
  ****************************************************************************************/

/*****************************************************************************************
 * Include files
 *****************************************************************************************/
#include "CHsvDvbsOpProfile_mSort.h"


/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/
TRACESYMBOL(m, "dvb/installation/hsvdvbsopprofile_mSort")


/*****************************************************************************************
 * Static variables
 *****************************************************************************************/
Pump CHsvDvbsOpProfile_mSort::mCamSortPmp;
int CHsvDvbsOpProfile_mSort::mCurrentRadioIndex = 0;
int CHsvDvbsOpProfile_mSort::mCurrentPresetIndex = 0;


/*****************************************************************************************
 * Private methods
 *****************************************************************************************/
void CHsvDvbsOpProfile_mSort::mPumpHandler (int event, Nat32 param)
{    
    int startIndex = param;
    TraceNotice(m,"event= %d startindex = %d ", event,(int) startIndex);

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
        insN->OnEvent (IHsvSatelliteInstallationNotify_EventSortCompleted, 0);
        break;

    default:
    break;
    }
}

void CHsvDvbsOpProfile_mSort::mSortHonouredServices(Bool checkForRadioServices, int startIndex)
{
    HsvPgdatDigServiceData svcData;
    int recordIndex = 0;
    int numOfRecs = pgdb->GetNoRecords(SERVICE_TABLE);
    int nextIndex = 0;
    int lcnIndex = 0;
    int currentSortStep = ((checkForRadioServices) ? SORT_HONOURED_RADIO_SERVICES : SORT_HONOURED_SERVICES);

    TraceNotice(m,"Number of service records %d Start index %d Sort Step %d ",numOfRecs, startIndex, currentSortStep);
    
    recordIndex = startIndex;
    
    for (; ((recordIndex < startIndex + STEP_SIZE)  && (recordIndex < numOfRecs)); ++recordIndex)
    {
        if (TRUE == pgdb->GetByIndex (SERVICE_TABLE, recordIndex, (Address) &svcData))
        {
            for (lcnIndex = 0; lcnIndex < MAX_NUM_LCN_ENTRY; lcnIndex++)
            {
				TraceNotice (m, "RecrdIndex %d LcnIndex %d MultipleLCN %d ", recordIndex, lcnIndex, svcData.MultipleLCN[lcnIndex]);
                if ((INVALID_LCN != svcData.MultipleLCN[lcnIndex]) && 
                     (VALID_LCN_RANGE (svcData.MultipleLCN[lcnIndex])) &&
                     (IS_RADIO_SERVICE (svcData.ServiceType) == checkForRadioServices))
                {
					
                    if(PRESET_NOT_ALLOCATED (svcData.MultiplePreset[lcnIndex]))
                    {
						TraceNotice (m, "PresetNot allocated for Recordindex %d LcnIndex %d ", recordIndex, lcnIndex);
                        mDigitalPresetEntryforValidLCN (recordIndex, lcnIndex);
                    }
                }
            }
        }
        else
        {
            TraceErr(m,"Error: This should not be printed!!");
        }
    }

    TraceDebug(m,"Number of service records %d Rec index %d", numOfRecs, recordIndex);
    
    if (recordIndex < numOfRecs)
    {
        nextIndex = startIndex + STEP_SIZE;
    }
    else
    {
        nextIndex =0;
        ++currentSortStep;
    }
    TraceNotice(m,"Pmp send done with event = %d NextIndex = %d \n", currentSortStep, nextIndex);
    m_pfac.PmpSend (mCamSortPmp, currentSortStep, nextIndex);
}


void CHsvDvbsOpProfile_mSort::mSortNonHonouredServices(Bool checkForRadioServices, int startIndex)
{
    HsvPgdatDigServiceData svcData;
    int recordIndex = 0;
    int numOfRecs = pgdb->GetNoRecords (SERVICE_TABLE);
    int nextIndex =0;
    int lcnIndex = 0;
    int currentSortStep = ((checkForRadioServices) ? SORT_NONHONOURED_RADIO_SERVICES : SORT_NONHONOURED_SERVICES);

    recordIndex = startIndex;

    TraceNotice (m,"Number of service records %d Start index %d Sort step %d\n", numOfRecs, startIndex, currentSortStep);
    
    for ( ;  (recordIndex < startIndex + STEP_SIZE)  && (recordIndex < numOfRecs); ++recordIndex)
    {
        if (TRUE == pgdb->GetByIndex (SERVICE_TABLE, recordIndex, (Address) &svcData))
        {
            for (lcnIndex = 0; lcnIndex < MAX_NUM_LCN_ENTRY; ++lcnIndex)
            {
                if ((INVALID_LCN != svcData.MultipleLCN[lcnIndex]) &&
                     (PRESET_NOT_ALLOCATED (svcData.MultiplePreset[lcnIndex])) &&
                     (!VALID_LCN_RANGE (svcData.MultipleLCN[lcnIndex])) &&
                     (checkForRadioServices == IS_RADIO_SERVICE (svcData.ServiceType)))
                {
                    mDigitalPresetEntryforInValidLCN (recordIndex, lcnIndex);
                }
            }
        }
    }

    TraceNotice (m," Number of service records %d Rec index %d\n",numOfRecs, recordIndex);
    
    if(recordIndex < numOfRecs)
    {
        nextIndex = startIndex + STEP_SIZE;
    }
    else
    {
        nextIndex =0;
        ++currentSortStep;
    }
    TraceNotice(m,"Pmp send done with event = %d NextIndex = %d \n", currentSortStep, nextIndex);
    m_pfac.PmpSend(mCamSortPmp, currentSortStep, nextIndex);

}

void CHsvDvbsOpProfile_mSort::mAddEntryToPresetTable(HsvPgdatDigServiceData *svcData, int presetNo, int lcnIndex)
{
    HsvPgdatPresetData presetData;

    pgdb->Initialise (IHsvProgramDatabaseConstants_Preset, (Address) &presetData);

    svcData->MultiplePreset[lcnIndex] = presetNo;
    svcData->PresetNumber = svcData->MultiplePreset[0];
    presetData.PresetNumber = svcData->MultiplePreset[lcnIndex];

    presetData.OriginalNetworkId = svcData->OriginalNetworkId;
    presetData.ServiceId = svcData->ServiceId;
    presetData.Tsid = svcData->Tsid;
    presetData.Tpid = svcData->Tpid;
    presetData.Frequency = svcData->Frequency;
    presetData.Polarization = svcData->Polarization;
    presetData.LnbNumber = svcData->LnbNumber;
    
    TraceNotice (m,"SID = %d PresetNo = %d \n", presetData.ServiceId, presetNo);
    
    if (TRUE != pgdb->GetByKey (PRESET_TABLE, (Address) &presetData))
    {
        pgdb->Add(PRESET_TABLE, (Address) &presetData);
        pgdb->Update(SERVICE_TABLE, (Address) svcData);
    }
    else
    {
        TraceErr(m,"!!Preset is already present in PRESET_TABLE\n");
    }
}

void CHsvDvbsOpProfile_mSort::mDigitalPresetEntryforValidLCN(int dbIndex, int lcnIndex)
{
    HsvPgdatDigServiceData svcData;
    HsvPgdatPresetData presetData;

    if (TRUE == pgdb->GetByIndex (SERVICE_TABLE, dbIndex, (Address) &svcData))
    {
        REVALIDATE ( svcData.MultipleLCN[lcnIndex]);

        /* Check if LCN preset is occupied */
        presetData.PresetNumber = svcData.MultipleLCN[lcnIndex];
        
        if( pgdb->GetByKey (PRESET_TABLE, (Address) &presetData) )
        {
            //preset is occupied   , service will get the preset number in non hon
            TraceNotice(m,"INVALIDATE SID = %d svcdat.LCN = %d ", svcData.ServiceId, svcData.MultipleLCN[lcnIndex]);
            INVALIDATE ( svcData.MultipleLCN[lcnIndex]);
            pgdb->Update(SERVICE_TABLE,(Address) &svcData);
        }
        else
        {
            TraceNotice (m, "Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x", presetData.PresetNumber, \
                                     svcData.OriginalNetworkId, svcData.Tsid, svcData.ServiceId, svcData.MultipleLCN[lcnIndex]);
            /* That preset is free. So just grab it */
            mAddEntryToPresetTable (&svcData,  svcData.MultipleLCN[lcnIndex], lcnIndex);
        }
    }
}

void CHsvDvbsOpProfile_mSort::mDigitalPresetEntryforInValidLCN(int dbIndex,  int lcnIndex)
{
    int fromPreset = 0;
    int toPreset = 0;
    int currentPresetIndex = 0;
    HsvPgdatDigServiceData svcData;

    if (TRUE == pgdb->GetByIndex (SERVICE_TABLE, dbIndex, (Address) &svcData))
    {
        toPreset =  (IS_RADIO_SERVICE (svcData.ServiceType)) ? MAX_RADIO_PRESET : RADIO_PRESET_OFFSET;
        fromPreset  = (IS_RADIO_SERVICE (svcData.ServiceType)) ? RADIO_PRESET_OFFSET : TV_PRESET_OFFSET;;

        currentPresetIndex = mGetPresetNoForService(svcData, fromPreset, toPreset);

        if (currentPresetIndex > 0)
        {
            mAddEntryToPresetTable (&svcData, currentPresetIndex, lcnIndex);
            currentPresetIndex = currentPresetIndex + 1;
        }
    }
    else
    {
        TraceNotice(m,"%d Suddenly the svcdat is removed. How ?!!", __LINE__);
        ASSERT(!"Suddenly the svcdat is removed. How ?!!");
    }
}

int CHsvDvbsOpProfile_mSort::mGetPresetNoForService(HsvPgdatDigServiceData svcData, int fromPreset, int toPreset)
{
    int currentPresetIndex = 0;
    HsvPgdatPresetData presetData;

    currentPresetIndex  = GETCURRENTINDEX (svcData.ServiceType);

    presetData.PresetNumber = currentPresetIndex;

    if ((currentPresetIndex == 0) || 
         pgdb->GetByKey (PRESET_TABLE, (Address) &presetData) ||
         (currentPresetIndex < fromPreset) || (currentPresetIndex > toPreset))
    {
        if(INVALID_PRESET == (currentPresetIndex = mFirstAvailableGapInPresetList(fromPreset, toPreset)))
        {
            //If we dont get any then start placing the service from MIXED_PRESET_OFFSET
            currentPresetIndex = mFirstAvailableGapInPresetList (MIXED_PRESET_OFFSET, MAX_PRESET_NUMBER);
        }
        TraceNotice (m,"%s:: %d CurrentPresetIndex = %d",__FUNCTION__, __LINE__, currentPresetIndex);
    }
    if (IS_RADIO_SERVICE (svcData.ServiceType))
    {
        mCurrentRadioIndex = currentPresetIndex;
    }
    else
    {
        mCurrentPresetIndex = currentPresetIndex;
    }
    return currentPresetIndex;
}

int CHsvDvbsOpProfile_mSort::mFirstAvailableGapInPresetList (int fromPreset, int toPreset)
{
    int recordIndex = 0;
    int prevPreset = fromPreset;
    int retval = INVALID_PRESET;
    HsvPgdatPresetData presetData;
    int numOfRecs = pgdb->GetNoRecords (PRESET_TABLE);

    if (0 == numOfRecs)
    {
        retval = fromPreset + 1;
    }
    else if (1 == numOfRecs)
    {
        if (pgdb->GetByIndex (TRUE == PRESET_TABLE, 0, (Address) &presetData))
        {
            retval = ((presetData.PresetNumber > fromPreset)) ? (presetData.PresetNumber + 1) : (fromPreset + 1);
        }
        else
        {
            /* error condition should not occur */
            retval = fromPreset + 1;
        }

    }
    else
    {
        presetData.PresetNumber = (fromPreset + 1);
        if (FALSE == pgdb->GetByKey (PRESET_TABLE, (Address) &presetData))
        {
            retval = fromPreset + 1;
        }
        else
        {
            for (recordIndex = (numOfRecs - 1); recordIndex >= 0; --recordIndex)
            {
                pgdb->GetByIndex (PRESET_TABLE, recordIndex, (Address) &presetData);

                if (presetData.PresetNumber <= fromPreset)
                {
                    prevPreset = presetData.PresetNumber;
                    if (0 == recordIndex)
                    {
                        retval = fromPreset + 1;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                if ((prevPreset >= fromPreset) && (presetData.PresetNumber - prevPreset) > 1)
                {
                    /* Found the first gap in needed range */
                    retval = prevPreset + 1;
                    break;
                }
                else
                {
                    if (0 == recordIndex)
                    {
                        retval = (presetData.PresetNumber < toPreset)?(presetData.PresetNumber + 1):INVALID_PRESET;
                        break;
                    }
                    else
                    {
                        prevPreset = presetData.PresetNumber;
                    }
                }
            }

            retval = (retval <= toPreset)? retval : INVALID_PRESET;
        }
    }
    return retval;
}


// Overridden IHsvPower methods
void CHsvDvbsOpProfile_mSort::Init()
{
    mCamSortPmp = m_pfac.PmpCreate (pen->PumpEngine(), &CHsvDvbsOpProfile_mSort::mPumpHandler, \
                                                            FALSE, (char *)"hsvdvbsopprofile_mSort", this);
}

void CHsvDvbsOpProfile_mSort::TurnOn()
{

}

void CHsvDvbsOpProfile_mSort::TurnOff()
{

}

// Overridden IHsvSorting methods
void CHsvDvbsOpProfile_mSort::Sort(Nat32 param)
{

    int mode, state, retVal;

    TraceNotice(m, "%s() @ %d \n", __FUNCTION__, __LINE__);
    
    retVal = rins->GetCurrentInstallationState (&mode, &state);
    
    if ((mode == AUTO_MODE) || (mode == CAM_NIT_UPDATE_MODE))
    {
        mCurrentRadioIndex = 0;
        mCurrentPresetIndex = 0;
    }

    insN->OnEvent (IHsvSatelliteInstallationNotify_EventSortingStarted, 0);
    m_pfac.PmpSend (mCamSortPmp, SORT_HONOURED_SERVICES, 0);
}
