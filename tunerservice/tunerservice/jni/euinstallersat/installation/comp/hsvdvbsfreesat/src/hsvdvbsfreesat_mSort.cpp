
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
*          %name: hsvdvbsfreesat_mSort.c %
*       %version: TVG_1 %
* %date_modified: %
*    %derived_by: anuma %
*/


#include "CHsvDvbsFreesat_mSort.h"
#include "freesatsort.h"


/********************************************************************************
* local Globals
*********************************************************************************/
TRACESYMBOL(m, "installation/hsvdvbsfreesat/hsvdvbsfreesat_mSort")
typedef enum
{
	SORT_HONOURED_SERVICES = 0,
	SORT_COMPLETE
}SORTING_HANDLER_ENUM;





/* provides IHsvPower isortpow */
void CHsvDvbsFreesat_mSort::Init()
{
	TraceNotice (m,"Sort Pow Init being called \n");
	Sortingpmp = pmp_PmpCreateEx(pen->PumpEngine(), SortingHandler, TRUE, "hsvdvbinsfreesat_msort");
}

void CHsvDvbsFreesat_mSort::TurnOn (void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
}

void CHsvDvbsFreesat_mSort::TurnOff (void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
}



/* provides IHsvSorting	isort */
void CHsvDvbsFreesat_mSort::Sort (Nat32 PackageIndex)
{
	int mode,state,retval;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	retval = rins->GetCurrentInstallationState (&mode, &state);
	TraceNotice(m,"freesat Sorting started");

	if(mode == AUTO_MODE)
	{
		//mCurrentRadioIndex  = 0;
		  mCurrentPresetIndex = 0;
	}

	iinsN->OnEvent(IHsvSatelliteInstallationNotify_EventSortingStarted, 0);
	pmp_PmpSend(Sortingpmp, SORT_HONOURED_SERVICES, 0);
}

void CHsvDvbsFreesat_mSort::SortingHandler( int event, Nat32 startindex )
{
	TraceNotice (m," Entering function Freesat - %s event= %d startindex = %d ",__FUNCTION__, event,(int) startindex);
	switch (event)
	{
		case SORT_HONOURED_SERVICES:
		{
			mSortServices(startindex);
		}
		break;
		case SORT_COMPLETE:
		{
			mUpdateServiceTable(startindex);
		}
		break;
		default:
			break;
	}
}

void CHsvDvbsFreesat_mSort::mSortServices(int startindex)
{
	HsvPgdatDigServiceData svcdat;
	HsvPgdatPresetData presetdat;
	int RecordIndex = 0;
	int NoOfRecs = pgdb->GetNoRecords(SERVICE_TABLE);
	int NextIndex = 0;
	int LCNIndex = 0;
	int CurrentSortStep = SORT_HONOURED_SERVICES;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	TraceNotice(m,"Number of service records %d Start index %d Sort Step %d ",NoOfRecs, startindex, CurrentSortStep);
	RecordIndex = startindex;
	for(; ((RecordIndex < startindex+STEP_SIZE) && (RecordIndex < NoOfRecs)); RecordIndex++)
	{
		if(TRUE == pgdb->GetByIndex(SERVICE_TABLE, RecordIndex, (Address)&svcdat))
		{
			for(LCNIndex = 0; LCNIndex < MAX_NUM_LCN_ENTRY; LCNIndex++)
			{
				TraceNotice(m,"TMP_DEBUG LINE %d SID %d LCN %d Preset %d",__LINE__,svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex], svcdat.MultiplePreset[LCNIndex]);
				if(VALID_LCN_RANGE(svcdat.MultipleLCN[LCNIndex]))
				{
					TraceNotice(m,"TMP_DEBUG LINE %d SID %d LCN %d Preset %d",__LINE__,svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex], svcdat.MultiplePreset[LCNIndex]);
					if(PRESET_NOT_ALLOCATED(svcdat.MultiplePreset[LCNIndex]))
					{
						TraceNotice(m,"TMP_DEBUG LINE %d SID %d LCN %d Preset %d",__LINE__,svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex], svcdat.MultiplePreset[LCNIndex]);
						mDigitalPresetEntryforValidLCN(RecordIndex, LCNIndex);
					}
					else
					{
						/*preset is already available, then update visible service and numeric select flag*/
						  presetdat.PresetNumber = svcdat.MultipleLCN[LCNIndex];
					        if( pgdb->GetByKey(PRESET_TABLE, (Address)&presetdat) )
					        {
					        	presetdat.VisibleService = (svcdat.MultipleVisibleService[LCNIndex]);
					        	presetdat.SystemHidden = (!(svcdat.MultipleVisibleService[LCNIndex]));
					        	presetdat.NumericSelect = svcdat.MultipleNumericSelect[LCNIndex];
					        	pgdb->Update(PRESET_TABLE, (Address )&presetdat);
					        }
					}
				}
			}
		}
		else
		{
			TraceNotice(m,"Error: This should not be printed!!");
		}
	}

	TraceNotice(m,"Number of service records %d Rec index %d",NoOfRecs, RecordIndex);
	if(RecordIndex < NoOfRecs)
	{
		NextIndex = startindex+STEP_SIZE;
	}
	else
	{
		NextIndex =0;
		CurrentSortStep++;
	}
	TraceNotice(m,"Pmp send done with event = %d NextIndex = %d \n", CurrentSortStep,NextIndex);
	pmp_PmpSend(Sortingpmp, CurrentSortStep,NextIndex);
}

void CHsvDvbsFreesat_mSort::mDigitalPresetEntryforValidLCN(int dbindex, int LCNIndex)
{
    HsvPgdatDigServiceData svcdat;
    HsvPgdatDigServiceData tempSvcdat;
    HsvPgdatPresetData presetdat;
    Nat8 preExisting_LCNIndex = 0;
    /*The LCNType in the below variable refers to Regional Variant or Global one*/
    Nat8 preExisting_LCNType = 0;
    Nat8 current_LCNType = 0;
    Nat8 LCNType_Order = 0;
    TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);

    if( pgdb->GetByIndex(SERVICE_TABLE, dbindex, (Address)&svcdat) == TRUE )
    {
        REVALIDATE(svcdat.MultipleLCN[LCNIndex]);
        /* Check for Duplicate LCN*/
        presetdat.PresetNumber = svcdat.MultipleLCN[LCNIndex];
        if( pgdb->GetByKey(PRESET_TABLE, (Address)&presetdat) )
        {
        	TraceNotice(m,"Duplicate lcn sid %d PresetNumber %d ",presetdat.ServiceId,presetdat.PresetNumber);
			//Check for a Duplicate Service
        	if((presetdat.ServiceId != svcdat.ServiceId) || (presetdat.Tpid != svcdat.Tpid))
        	{
        		TraceNotice(m,"Not a Duplicate Service\n");
				
        		tempSvcdat.Tpid = presetdat.Tpid;
        		tempSvcdat.ServiceId = presetdat.ServiceId;
	        	/*preset is already available , check whether it is global or regional*/

				if(pgdb->GetByKey(SERVICE_TABLE, (Address)&tempSvcdat))
	        	{
	        		//Trying to get the pre-existing LCN Index, 
	        		//on Basis of this Index, LCN type is decided Global(if Index is other Zero) or Regional(if Index is Zero)
	        		for(preExisting_LCNIndex = 0; preExisting_LCNIndex < MAX_NUM_LCN_ENTRY; preExisting_LCNIndex++)
					{
						if((tempSvcdat.MultipleLCN[preExisting_LCNIndex]) == presetdat.PresetNumber)
						{
							break;
						}
					}

					if(preExisting_LCNIndex < MAX_NUM_LCN_ENTRY)
					{
						preExisting_LCNType = (preExisting_LCNIndex == 0)? REGIONAL : GLOBAL;
						current_LCNType 	= (LCNIndex == 0)? REGIONAL : GLOBAL;
						LCNType_Order = GET_ORDER(preExisting_LCNType,current_LCNType);

						TraceNotice(m,"Order %d",LCNType_Order);
						
						switch(LCNType_Order)
						{
							case PRE_REG__CURR_REG:
							case PRE_REG__CURR_GBL:
							case PRE_GBL__CURR_GBL:
								/*Ignore the LCN*/
								svcdat.MultiplePreset[LCNIndex] = INVALID_PRESET;
								svcdat.MultipleLCN[LCNIndex] = INVALID_LCN;
								pgdb->Update(SERVICE_TABLE, (Address )&svcdat);
								break;

							case PRE_GBL__CURR_REG:
								/*delete the previous LCN and preset, add it for new service*/
								pgdb->Delete(PRESET_TABLE, (Address)&presetdat);
								tempSvcdat.MultiplePreset[preExisting_LCNIndex] = INVALID_PRESET;
								tempSvcdat.MultipleLCN[preExisting_LCNIndex] = INVALID_LCN;
								pgdb->Update(SERVICE_TABLE, (Address )&tempSvcdat);
								mAddEntryToPresetTable(&svcdat,svcdat.MultipleLCN[LCNIndex],LCNIndex);
								break;

							default:
								break;
						}
					}
					else
					{
						TraceNotice(m,"Error!!! Preset is not found in duplicate service");
						/*LCN is not available in duplicate service, so delete the existing preset and add it newly*/
						mAddEntryToPresetTable(&svcdat,  svcdat.MultipleLCN[LCNIndex], LCNIndex);
					}
				}
				else
				{
					TraceNotice(m,"Error!!! Service table get by key failed, TPID 0x%x SID 0x%x",tempSvcdat.Tpid,tempSvcdat.ServiceId);
				}
			}
			else
			{
				TraceNotice(m,"Error!!! Preset from same service is shown as duplicate, should not enter here");
			}
	     }
	     else
	     {
	        TraceNotice(m,"Adding Preset @ %d for service ONID 0x%x TSID 0x%x SID 0x%x",presetdat.PresetNumber, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.MultipleLCN[LCNIndex]);
	        mAddEntryToPresetTable(&svcdat,  svcdat.MultipleLCN[LCNIndex], LCNIndex);
	     }
   	}
}


void CHsvDvbsFreesat_mSort::mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, int LCNIndex)
{
	HsvPgdatPresetData      presetdat;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	pgdb->Initialise (IHsvProgramDatabaseConstants_Preset, (Address)&presetdat);

	svcdat->MultiplePreset[LCNIndex] = PresetNo;
	presetdat.PresetNumber = svcdat->MultiplePreset[LCNIndex];
	
	presetdat.OriginalNetworkId = svcdat->OriginalNetworkId;
	presetdat.ServiceId = svcdat->ServiceId;
	presetdat.Tsid = svcdat->Tsid;
	presetdat.Tpid = svcdat->Tpid;
	presetdat.Frequency = svcdat->Frequency;
	presetdat.Polarization = svcdat->Polarization;
	presetdat.LnbNumber = svcdat->LnbNumber;
	presetdat.VisibleService = svcdat->MultipleVisibleService[LCNIndex];
	presetdat.SystemHidden = !(svcdat->MultipleVisibleService[LCNIndex]);
	presetdat.NumericSelect = svcdat->MultipleNumericSelect[LCNIndex];

	TraceNotice(m,"SID = %d PresetNo = %d ",presetdat.ServiceId,PresetNo);
	/*TraceDebug(m,"Before Service Update:Name %s ONID:0x%x TSID 0x%x SVCID:0x%x SystemHidden = %d LCN %d %d %d %d %d %d %d %d Preset %d %d %d %d %d %d %d %d\n", svcdat ->ChannelName, \
	svcdat->OriginalNetworkId, svcdat->Tsid, svcdat->ServiceId,svcdat->SystemHidden, svcdat->MultipleLCN[0], svcdat->MultipleLCN[1], svcdat->MultipleLCN[2],svcdat->MultipleLCN[3], svcdat->MultipleLCN[4],
	svcdat->MultipleLCN[5], svcdat->MultipleLCN[6], svcdat->MultipleLCN[7], svcdat->MultiplePreset[0], svcdat->MultiplePreset[1], svcdat->MultiplePreset[2],svcdat->MultiplePreset[3], svcdat->MultiplePreset[4],
	svcdat->MultiplePreset[5], svcdat->MultiplePreset[6], svcdat->MultiplePreset[7]);*/
	
	if(TRUE != pgdb->GetByKey (PRESET_TABLE,(Address)&presetdat))
	{
		pgdb->Add(PRESET_TABLE, (Address)&presetdat);

		pgdb->Update(SERVICE_TABLE,(Address)svcdat);
	}
	else
	{
		TraceErr(m,"Error!!!Preset is already present in PRESET_TABLE - should not enter here\n");

	}
	/*TraceDebug(m,"After Service Update:Name %s ONID:0x%x TSID 0x%x SVCID:0x%x SystemHidden = %d LCN %d %d %d %d %d %d %d %d Preset %d %d %d %d %d %d %d %d\n", svcdat ->ChannelName, \
	svcdat->OriginalNetworkId, svcdat->Tsid, svcdat->ServiceId,svcdat->SystemHidden, svcdat->MultipleLCN[0], svcdat->MultipleLCN[1], svcdat->MultipleLCN[2],svcdat->MultipleLCN[3], svcdat->MultipleLCN[4],
	svcdat->MultipleLCN[5], svcdat->MultipleLCN[6], svcdat->MultipleLCN[7], svcdat->MultiplePreset[0], svcdat->MultiplePreset[1], svcdat->MultiplePreset[2],svcdat->MultiplePreset[3], svcdat->MultiplePreset[4],
	svcdat->MultiplePreset[5], svcdat->MultiplePreset[6], svcdat->MultiplePreset[7]);*/
}

/*
This function Removes the Service Entry of those services(from service_table)
which have Invalid LCN through out MultiplePreset[] Array
*/
void CHsvDvbsFreesat_mSort::mUpdateServiceTable(int startindex)
{
	HsvPgdatDigServiceData svcdat;
	int RecordIndex = 0;
	int NextIndex = 0;
	int LCNIndex = 0;
	int NoOfRecs =  pgdb->GetNoRecords(SERVICE_TABLE);
	RecordIndex = startindex;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	for(; ((RecordIndex < startindex+STEP_SIZE) &&(RecordIndex < NoOfRecs)); RecordIndex++)
	{
		if(TRUE == pgdb->GetByIndex(SERVICE_TABLE, RecordIndex, (Address)&svcdat))
		{

			for(LCNIndex = 0; LCNIndex < MAX_NUM_LCN_ENTRY; LCNIndex++)
			{
				if(svcdat.MultiplePreset[LCNIndex] != INVALID_PRESET)
				{
					break;
				}
			}
		}
		if(MAX_NUM_LCN_ENTRY == LCNIndex)
		{
			pgdb->Delete(SERVICE_TABLE,&svcdat);
		}
	}

	TraceDebug(m,"Number of service records %d Rec index %d",NoOfRecs,RecordIndex);
	if(RecordIndex < NoOfRecs)
	{
		NextIndex = startindex+STEP_SIZE;
		TraceNotice(m,"Pmp send done with event = %d NextIndex = %d \n", SORT_COMPLETE,NextIndex);
		pmp_PmpSend(Sortingpmp,SORT_COMPLETE,NextIndex);
	}
	else
	{
		iinsN->OnEvent(IHsvSatelliteInstallationNotify_EventSortCompleted, 0);
	}
}

