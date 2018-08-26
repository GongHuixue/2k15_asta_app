/**********************************************************************
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *	C Source:		hsvdvbsins_mservicescan.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	 aneeshc %
 *	%date_created:	 Fri May  3 19:10:53 2013 %
 *
**********************************************************************/

#include "_hsvdvbsgeneric_mScan.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsgeneric_mScan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#else

#endif

























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsGeneric_mScan_Priv::SvcScanEventNames[EvMax+1][32] = 
{
	"EvStart",
	"EvStop",
	"EvStationFound",
	"EvStationNotFound",
	"EvDataAvailable",
	"EvDataNotAvailable",
	"EvStartTuning",
	"EvCheckLock",
	"EvBlindScanEnd",
	"EvMax"
};


int CHsvDvbsGeneric_mScan_Priv::s__mConstModuleLifeCycle = 0,CHsvDvbsGeneric_mScan_Priv::s__NumEntriesForUpdate = 0,CHsvDvbsGeneric_mScan_Priv::s__CurrentEntryForUpdate = 0,CHsvDvbsGeneric_mScan_Priv::s__NumEntriesInOverlappingRange = 0;

InsInstance CHsvDvbsGeneric_mScan_Priv::s__mInstStatus;

AstraScanInstance CHsvDvbsGeneric_mScan_Priv::s__mAstraScanStatus;


Pump CHsvDvbsGeneric_mScan_Priv::s__mPump;

UpdateTuneList CHsvDvbsGeneric_mScan_Priv::s__UpdateInstallList[MAX_SERVICES_PER_SAT];

UpdateTuneList CHsvDvbsGeneric_mScan_Priv::s__SwitchFreqList[MAX_TP_IN_OVERLAPPING_REG];


/* Used to cache the FE params, in cases where lock is lost in between data collection */
UpdateTuneList CHsvDvbsGeneric_mScan_Priv::s__mCachedFEParams;











HomingMuxData CHsvDvbsGeneric_mScan_Priv::s__AstraHomingDetails[NO_OF_HOMING_MUX] = {{12603 , satfeapi_PolarisationHorizontal, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner56,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{12551, satfeapi_PolarisationVertical, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner56,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{11302 , satfeapi_PolarisationHorizontal, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner23,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{12515 , satfeapi_PolarisationHorizontal, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner56,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{11856 , satfeapi_PolarisationVertical, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner34,satfeapi_RollOffOP35,satfeapi_PilotsON}};






FunctionNat32 CHsvDvbsGeneric_mScan_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
							   /* StIdle,					StStart,					StTunerWait,				StDemuxWait			*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL},
/* EvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)	},
/* EvStationFound */		{  NULL,						NULL,						FNADDR(FuncStationFound),	NULL				},
/* EvStationNotFound */		{  NULL,						NULL,						FNADDR(FuncNoStationFound),	NULL				},
/* EvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable)	},
/* EvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable)	},
/* EvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL				},
/* EvCheckLock */			{  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL				},
/* EvBlindScanEnd */		{  NULL,						NULL,						FNADDR(FuncBlindScanEnd),	NULL				},
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsGeneric_mScan_Priv::PumpHandler(int event, Nat32 param)
{	
	if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
	{
		if(EventActionMatrix[event][mInstStatus.State] != NULL)
		{
			TraceNotice (m, "SvcScan: %s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
			FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
		}
	}
}

void CHsvDvbsGeneric_mScan_Priv::SetChannelDecoder (void)
{
}

void CHsvDvbsGeneric_mScan_Priv::mBuildCurrentFrequencyList (void)
{
	int		Count, From, To, NumEntry =0;
	HsvPgdatDigTSData	TempTsData;

	TempTsData.LnbNumber = mInstStatus.Lnb; 
	if (pgdb_GetRange (PTC_TABLE, 1, (Address)&TempTsData, &From, &To))
	{
		for (Count = From, NumEntry = 0; ((Count <= To) && (NumEntry < MAX_SERVICES_PER_SAT)); Count++,NumEntry++)
		{
			if (TRUE == pgdb_GetByIndex (PTC_TABLE, Count ,(Address)&TempTsData))
			{
				UpdateInstallList[NumEntry].Frequency = TempTsData.Frequency;
				UpdateInstallList[NumEntry].Polarization = TempTsData.Polarization;
				UpdateInstallList[NumEntry].SymbolRate = TempTsData.SymbolRate;
				TraceNotice(m,"[%d][%d][%d]",UpdateInstallList[NumEntry].Frequency,(int)TempTsData.Frequency,Count);
			}
		}
	}
	NumEntriesForUpdate = NumEntry;
	CurrentEntryForUpdate = 0;
}
Bool CHsvDvbsGeneric_mScan_Priv::IsMduLnb (int LnbType)
{
	Bool	RetVal = FALSE;
	switch (LnbType)
	{
	case	LnbMdutype1:
	case	LnbMdutype2:
	case	LnbMdutype3:
	case	LnbMdutype4:
	case	LnbMdutype5:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}

void CHsvDvbsGeneric_mScan_Priv::FuncStartServiceScan (Nat32 param1)
{
	HsvLnbSettings	LnbSettings;

	idataacq_Initialise (param1);

	/* Save the current LNB Settings to local data */
	idvbset_GetLnbSettings (&LnbSettings);
	mInstStatus.Lnb = param1;
	mInstStatus.LnbType = LnbSettings.LnbSettings[param1].LnbType;
	mInstStatus.BlindScanInProgress = FALSE;
	mInstStatus.ProgressBar = 0;

    NumEntriesInOverlappingRange = 0;
    memset (SwitchFreqList, 0x00, sizeof(SwitchFreqList));
	/* Pass LNB number */
	iinsN_OnEvent(iinsN_EventLNBStart, mInstStatus.Lnb);

	if((CURRENT_MODE == insstate_InstallationUpdate) || (CURRENT_MODE == insstate_InstallationAutomaticUpdate))
	{
		mBuildCurrentFrequencyList ();
	}

	SET_INS_STATE (StStart);
	SetChannelDecoder ();	//ANEESH: TODO: Verify this is correct 
	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);		
	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	UNUSED(param1);
}

void CHsvDvbsGeneric_mScan_Priv::FuncStopServiceScan (Nat32 param1)
{
	SET_INS_STATE(StIdle);

	/* Stop currentSearch and stop the SDM */
	//ANEESH: StopSatelliteFrontEndSearch ();
	//isigstr_StopSigStrMeasAll();
	if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	satfeapi_AbortSatelliteBlindScan (mInstStatus.Lnb);
	iinsN_OnEvent(iinsN_EventInsStopped, mInstStatus.Lnb);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	SET_INS_MODE(insstate_InstallationNone);
	UNUSED (param1);
}

void CHsvDvbsGeneric_mScan_Priv::FuncStartTuning (Nat32 param1)
{
	FResult	RetVal = err_Ok;
	HsvNITSatelliteDS CurrSDSD;
	int		ModlnStd = -1, IqMode = -1, Cookie = 0;
	int		SymbolRate = 0,ModlnType = -1;
	int 	RollOff = -1, FEC = -1, Pilots = satfeapi_PilotsON; 

	
	if(!mAstraScanStatus.Enable)
	{
		if (mInstStatus.BlindScanInProgress == FALSE)
		{
			SET_INS_STATE(StTunerWait);
			RetVal = satfeapi_StartSatelliteBlindScan (mInstStatus.Lnb, satfeapi_BlindScanModeNormal);
			if (RetVal != err_Ok)
			{
				SET_INS_STATE(StIdle);
				iinsN_OnEvent(iinsN_EventInsFailed, mInstStatus.Lnb);
			}
			else
			{
				mInstStatus.BlindScanInProgress = TRUE;
			}
		}
		else
		{
			SET_INS_STATE(StTunerWait);
			RetVal = satfeapi_ContinueSatelliteBlindScan ();
			if (RetVal != err_Ok)
			{
				SET_INS_STATE(StIdle);
				//iinsN_OnEvent(iinsN_EventInsFailed, mInstStatus.Lnb);
			}
		}
	}
	else
	{
		if(mAstraScanStatus.Mode == Homing)
		{
			if(mAstraScanStatus.RefNITDetailsAvailable == FALSE)
			{
				if(mAstraScanStatus.HomingMuxIndex < NO_OF_HOMING_MUX)
				{
					SET_INS_STATE(StTunerWait);
					satfeapi_SatelliteFrontEndTune(mInstStatus.Lnb, mInstStatus.LnbType, (AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].Frequency*1000), \
											SymbolRate, AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].Polarization,Cookie, AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].ModulationSystem, \
											AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].ModulationType, IqMode, AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].RollOffFactor, \
											AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].FECInner, AstraHomingDetails[mAstraScanStatus.HomingMuxIndex].Pilots);
				}
				else
				{
					TraceNotice (m, " Astra Referance NIT not found on Lnb %d \n",mInstStatus.Lnb);				
					SET_INS_STATE(StIdle);
					iinsN_OnEvent(iinsN_EventInsFailed, mInstStatus.Lnb);
					mAstraScanStatus.Mode = Idle;
				}
			}
			else
			{
				SET_INS_STATE(StTunerWait);
				satfeapi_SatelliteFrontEndTune(mInstStatus.Lnb, mInstStatus.LnbType, mAstraScanStatus.RefNITData.Frequency, \
								SymbolRate, mAstraScanStatus.RefNITData.Polarization,Cookie, mAstraScanStatus.RefNITData.ModulationSystem, mAstraScanStatus.RefNITData.ModulationType, IqMode, \
								MapRollOffFactor(mAstraScanStatus.RefNITData.RollOff), mAstraScanStatus.RefNITData.FECInner, Pilots);
			}
		}
		else if(mAstraScanStatus.Mode == SDSDScan)
		{
			if(mAstraScanStatus.CurrSdsdIndex < mAstraScanStatus.NumOfSDSD)
			{
		
				/*Get current SDSD and tune to that*/
				idataacq_GetSdsdByIndex(mAstraScanStatus.CurrSdsdIndex,&CurrSDSD );	
		
				TraceNotice  (m, "SvcScan: SDSD Freq %d Pol %d ", (int)CurrSDSD.Frequency, (int)CurrSDSD.Polarization);
		
				SET_INS_STATE(StTunerWait);
				satfeapi_SatelliteFrontEndTune(mInstStatus.Lnb, mInstStatus.LnbType, (CurrSDSD.Frequency), \
											CurrSDSD.SymbolRate, CurrSDSD.Polarization,Cookie, CurrSDSD.ModulationSystem, CurrSDSD.ModulationType, CurrSDSD.FECInner, MapRollOffFactor(CurrSDSD.RollOff), CurrSDSD.FECInner, Pilots);
			}
			else
			{
				TraceNotice (m, " NIT based scanning completed on Lnb %d. Doing sync \n",mInstStatus.Lnb);
				/* 
				SET_INS_STATE(StIdle);
				iinsN_OnEvent(iinsN_EventLNBEnd,mInstStatus.Lnb);
				mAstraScanStatus.Mode = Idle;
				mAstraScanStatus.Enable = FALSE;
				*/
				idataacq_SyncTemporaryTableRecords();
			}
		}
		else
		{
			TraceNotice(m,"Not Possible");
		}
		
	}

	UNUSED (param1);
}

void CHsvDvbsGeneric_mScan_Priv::FuncStationFound (Nat32 param1)
{
	TraceNotice  (m, " In Function %s and line %d \n", __FUNCTION__, __LINE__);
	/* start signal strength measurement */
	//isigstr_StartSigStrMeasAll();
	mInstStatus.ProgressBar++;
	iinsN_OnEvent(iinsN_EventInsProgress, mInstStatus.Lnb);
	SET_INS_STATE(StDemuxWait);
	if(mAstraScanStatus.Enable && (mAstraScanStatus.Mode == Homing))
	{
		ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
	}
	else
	{
		ctrl_StartCollection(HsvDmxMain, ctrl_NormalPlusPmt);
	}
	
	UNUSED (param1);
}

void CHsvDvbsGeneric_mScan_Priv::FuncNoStationFound (Nat32 param1)
{

	/* Call scan step module to update station not found freq. This will take care
		of updating the frequencies internaly */
	TraceNotice (m, " NO Station Found...\n");
	iinsN_OnEvent(iinsN_EventInsProgress, mInstStatus.Lnb);

	mInstStatus.ProgressBar++;
	if( ((CURRENT_MODE == insstate_InstallationUpdate)|| (CURRENT_MODE == insstate_InstallationAutomaticUpdate)) && (CurrentEntryForUpdate < NumEntriesForUpdate))
	{
		CurrentEntryForUpdate++;
	}

	if(mAstraScanStatus.Enable)
	{
		/* Increment SDSD index or Homing mux index*/
		if (mAstraScanStatus.Mode == Homing)
		{
			if(mAstraScanStatus.RefNITDetailsAvailable == TRUE)
			{
				/*Stop scanning*/
				TraceNotice (m, " Tuning to Referance NIT failed on Lnb %d \n",mInstStatus.Lnb);				
				SET_INS_STATE(StIdle);
				iinsN_OnEvent(iinsN_EventInsFailed, mInstStatus.Lnb);
				mAstraScanStatus.Mode = Idle;
				return;
			}
			else
			{
				mAstraScanStatus.HomingMuxIndex++;
			}
		}
		else
		{
			mAstraScanStatus.CurrSdsdIndex++;
		}
	}

	
	SET_INS_STATE (StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	UNUSED (param1);
}

void CHsvDvbsGeneric_mScan_Priv::FuncDataAvailable (Nat32 param1)
{
	/* Update the data from Data Acq Module */
	if(mAstraScanStatus.Enable && (mAstraScanStatus.Mode == Homing))
	{
		if(mAstraScanStatus.RefNITDetailsAvailable)
		{
			idataacq_AcquireData (idataacq_AcquireSDSDs);
		}
		else
		{
			if(mStoreRefNITDetails() == TRUE)
			{
				mAstraScanStatus.RefNITDetailsAvailable = TRUE;
				
				SET_INS_STATE (StStart);
				if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
				{
					TraceNotice (m, "%s: %d:StartTuning Sent \n",__FUNCTION__,__LINE__);
					pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
				}
				else
				{
					ctrl_StopCollection(HsvDmxMain);
				}
			}
			else
			{
				TraceNotice (m, "mStoreRefNITDetails failed ");
				SET_INS_STATE(StIdle);
				iinsN_OnEvent(iinsN_EventLNBEnd,mInstStatus.Lnb);
				mAstraScanStatus.Mode = Idle;
				mAstraScanStatus.Enable = FALSE;
			}
		}
	}
	else
	{
		idataacq_AcquireData (0);
	}
	UNUSED (param1);
}

void CHsvDvbsGeneric_mScan_Priv::FuncNoDataAvailable (Nat32 param1)
{

	/* Update the data from Data Acq Module */
	if(!mAstraScanStatus.Enable)
	{
		idataacq_AcquireDataOnTimeout ();
	}
	else
	{
		/*Move to Next SDSD or next Homing mux*/
		if((mAstraScanStatus.Mode == Homing) &&(mAstraScanStatus.RefNITDetailsAvailable == TRUE))
		{
			/*Ref NIT is not received, Send Installation Failed/LNB End Notification*/
			
			TraceNotice (m, "Ref NIT is not received");
			SET_INS_STATE(StIdle);
			iinsN_OnEvent(iinsN_EventLNBEnd,mInstStatus.Lnb);
			mAstraScanStatus.Mode = Idle;
			mAstraScanStatus.Enable = FALSE;
		}
		else
		{
			(mAstraScanStatus.Mode == Homing)? (mAstraScanStatus.HomingMuxIndex++) : (mAstraScanStatus.CurrSdsdIndex++);
			
			SET_INS_STATE (StStart);
			if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
			{
				TraceNotice (m, "%s: %d:StartTuning Sent \n",__FUNCTION__,__LINE__);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
			else
			{
				ctrl_StopCollection(HsvDmxMain);
			}
		}

	}

	UNUSED (param1);
}


void CHsvDvbsGeneric_mScan_Priv::FuncCheckLockStatus(Nat32 param1)
{
	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);
	if (RetVal == err_Ok)
	{
		if (LockStatus != 0)
		{
            if ((LockedFreq == 0) && (IsMduLnb(LnbType)))
            {
			    pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
            }
            else
            {
			    // Station Found, so cache parameters for use, in case lock is lost during data aquisition
				mCachedFEParams.Frequency = LockedFreq;
				mCachedFEParams.Polarization = Polarization;
				mCachedFEParams.SymbolRate = SymbolRate;
				
			    pmp_PmpSend(mPump, EvStationFound, (Nat32)NULL);
            }
		}
		else
		{

			pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
		}
	}
	else
	{
		pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
	}
}

void CHsvDvbsGeneric_mScan_Priv::FuncBlindScanEnd(Nat32 Param)
{
	/* ANEESH: TODO: Check this part for completion. In case of SDSD scan how to handle this */
	/* BlindScan Finished. Give notification to appln */
	/* 
	mInstStatus.BlindScanInProgress = FALSE;
	SET_INS_STATE(StIdle);

	iinsN_OnEvent(iinsN_EventLNBEnd,mInstStatus.Lnb);
	*/
	TraceNotice (m, "%s idataacq_SyncTemporaryTableRecords called\n", __FUNCTION__);
	idataacq_SyncTemporaryTableRecords();	
	
}

void CHsvDvbsGeneric_mScan_Priv::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
{

	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);
	
	if (RetVal == err_Ok)
	{
		if (LockStatus != 0)
		{
			ptc->Frequency = LockedFreq;		
			ptc->SymbolRate = SymbolRate;
			ptc->ModulationType = 0;
			ptc->CodeRateHigh = 0;
			ptc->CodeRateLow = 0;	/* Testing shows that Puncture Rate is similar to FEC value */
			ptc->IqMode = IqMode;
			ptc->ChannelBandwidth = Bandwidth;
			ptc->Polarization = Polarization;
		}
		else // Lock lost
		{
			ptc->Frequency = mCachedFEParams.Frequency;		
			ptc->SymbolRate = mCachedFEParams.SymbolRate;
			ptc->ModulationType = 0;
			ptc->CodeRateHigh = 0;
			ptc->CodeRateLow = 0;	/* Testing shows that Puncture Rate is similar to FEC value */
			ptc->IqMode = 0;
			ptc->ChannelBandwidth = 0;
			ptc->Polarization = mCachedFEParams.Polarization;
		}
	}
}

void CHsvDvbsGeneric_mScan_Priv::mHandleOverlappingRegion (HsvInstallationPTC *ptc)
{
    int count = 0;

    if ((IN_SWITCHING_REGION(ptc->Frequency)) && (NumEntriesInOverlappingRange < MAX_TP_IN_OVERLAPPING_REG))
    {
        for (count = 0; count < NumEntriesInOverlappingRange; count++)
        {
            if ((SwitchFreqList[count].Polarization == ptc->Polarization) &&
				 iutil_CheckFreqDuplicationwithRolFact(ptc->Frequency, SwitchFreqList[count].Frequency, ptc->SymbolRate))
            {
                TraceNotice (m, "Duplicate frequency entry found. Skipping ");
                ptc->Frequency = SwitchFreqList[count].Frequency;		
            }
        }
        if (count == NumEntriesInOverlappingRange)
        {
            /* No matching entries */
            SwitchFreqList[count].Frequency = ptc->Frequency;
            SwitchFreqList[count].Polarization = ptc->Polarization;
			SwitchFreqList[count].SymbolRate  = ptc->SymbolRate;
            NumEntriesInOverlappingRange++;
        }
    }
}

int CHsvDvbsGeneric_mScan_Priv::MapRollOffFactor(int RollOff)
{	
	int RetVal = IHsvSatelliteFrontEnd_RollOffOP35;

	switch(RollOff)
	{
		case 0:
			RetVal = IHsvSatelliteFrontEnd_RollOffOP35;
			break;
		case 1:
			RetVal = IHsvSatelliteFrontEnd_RollOffOP25;
			break;
		case 2:
			RetVal = IHsvSatelliteFrontEnd_RollOffOP20;
			break;
		default:
			break;
	}

	TraceNotice(m, "%s: RetVal : %d", __FUNCTION__, RetVal);
	return RetVal;
}


/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx		isvcscanctrlN */

void CHsvDvbsGeneric_mScan_Priv::isvcscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceNotice (m, "EventId 0x%x Value 0x%x ", EventId ,Value);
	if (VALID_DEMUX(Dmx))
	{
		switch (EventId)
		{
		case	isvcscanctrlN_DataNotAvailable:
				pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
			break;
		case	isvcscanctrlN_StoppedCollection:
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			break;
		case	isvcscanctrlN_DataAvailable:
		case	isvcscanctrlN_OnlyPsiDataAvailable:
			if(mAstraScanStatus.Enable && (mAstraScanStatus.Mode == Homing))
			{
				/*In Homing Mode NIT is enough*/
				if (Value & isvcscanctrlN_NIT)
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
				else
				{
					pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
				}
			}
			else if (Value & isvcscanctrlN_SDT)
			{
				pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
			}
			break;
		case	isvcscanctrlN_SiDataAvailable:
			if(mAstraScanStatus.Enable && (mAstraScanStatus.Mode == Homing))
			{
				/*Do Nothing, as we need NIT in Astra Homing scan*/
			}
			else if (Value & isvcscanctrlN_SDT)
			{
				pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
			}
			break;
		case	isvcscanctrlN_StartedCollection:
			break;
		default:
			break;
		}
	}
	UNUSED (Value);	/* ANEESH: TODO: Make sure this is not needed */
}

/* provides IPlfApiDvbsNotify	isvcscanplfApidvbsN */

void CHsvDvbsGeneric_mScan_Priv::isvcscanplfApidvbsN_OnLockChanged(Bool LockState)
{
	/* Notifiation Handler for DVB-S platform FE */	
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

void CHsvDvbsGeneric_mScan_Priv::isvcscanplfApidvbsN_OnBlindScanEnd ()
{
	if (mInstStatus.BlindScanInProgress == TRUE)
	{
		pmp_PmpSend(mPump, EvBlindScanEnd, (Nat32)NULL);
	}
}

/* provides IHsvDigitalScanData		isvcscandata	*/

void CHsvDvbsGeneric_mScan_Priv::isvcscandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
	int	TransponderFreq, count;
	HsvNITSatelliteDS CurrSDSD;

	ptc->LnbNumber = mInstStatus.Lnb;
	ptc->LnbType = mInstStatus.LnbType;

	mGetCurrentTunerParams (ptc);

	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);
#if 0
	if( ((CURRENT_MODE == insstate_InstallationUpdate) || (CURRENT_MODE == insstate_InstallationAutomaticUpdate)) && (CurrentEntryForUpdate < NumEntriesForUpdate))
	{
		/* Check for duplication here */
		if (  (UpdateInstallList[CurrentEntryForUpdate].Polarization == ptc->Polarization) && 
			( ((UpdateInstallList[CurrentEntryForUpdate].Frequency >= ptc->Frequency) && ((UpdateInstallList[CurrentEntryForUpdate].Frequency - ptc->Frequency) < FREQ_DRIFT_TOLERANCE) ) ||
			 ( (ptc->Frequency > UpdateInstallList[CurrentEntryForUpdate].Frequency) && ((ptc->Frequency - UpdateInstallList[CurrentEntryForUpdate].Frequency) < FREQ_DRIFT_TOLERANCE) ) ))
		{
			/* Frequency drift handling. SI based check will happen in Acq module */
			ptc->Frequency = UpdateInstallList[CurrentEntryForUpdate].Frequency;
		}
	}
#endif
	if((CURRENT_MODE == insstate_InstallationUpdate) || (CURRENT_MODE == insstate_InstallationAutomaticUpdate))
	{
		for (count = 0; count <= NumEntriesForUpdate ; count++)
		{
			if (  (UpdateInstallList[count].Polarization == ptc->Polarization) && 
				 (iutil_CheckFreqDuplicationwithRolFact(ptc->Frequency, UpdateInstallList[count].Frequency, ptc->SymbolRate)))
			{
				/* Frequency drift handling. SI based check will happen in Acq module */
				TraceNotice(m,"Duplicate Transponder found at freq: %d, prev. freq: %d",ptc->Frequency,UpdateInstallList[count].Frequency);
				ptc->Frequency = UpdateInstallList[count].Frequency;
				break;
			}
			if ( count == NumEntriesForUpdate &&
				 NumEntriesForUpdate  < (MAX_SERVICES_PER_SAT - 1) )
			{				
				++NumEntriesForUpdate;
				UpdateInstallList[NumEntriesForUpdate].Frequency = ptc->Frequency;
				UpdateInstallList[NumEntriesForUpdate].Polarization = ptc->Polarization;
				UpdateInstallList[NumEntriesForUpdate].SymbolRate = ptc->SymbolRate;
			}
		}
	}
    else if ((CURRENT_MODE == insstate_InstallationServiceScan) || (CURRENT_MODE == insstate_InstallationAddSatellite))
    {
        mHandleOverlappingRegion (ptc);
    }


	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);

	TraceNotice  (m, " Freq %d and BW : %d \n", TransponderFreq, ptc->ChannelBandwidth);
	ptc->QSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsQsm);
	ptc->SSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsSsm);

	/* Get the SDSD from strapi if needed */
	ptc->SDSDFrequency = 0;
	ptc->PlpId = 0;
    //ptc->ChannelInformation;	//Not needed
	ptc->HierarchyMode = HsvHierarchyNone;
    ptc->StreamPriority = HsvStreamPriorityHigh;
	if(mAstraScanStatus.Enable)
	{
		/* Get the SDSD from Acq*/
		idataacq_GetSdsdByIndex(mAstraScanStatus.CurrSdsdIndex,&CurrSDSD );	
		ptc->ModulationType   = CurrSDSD.ModulationType;
		ptc->ModulationStd    = CurrSDSD.ModulationSystem;
		ptc->CodeRate   	  = CurrSDSD.FECInner;
	}
 
}

int CHsvDvbsGeneric_mScan_Priv::isvcscandata_GetInstallationVersion(void)
{
	/* ANEESH: TODO: Have to implement this function when update installation comes */
	return 0;
}



void CHsvDvbsGeneric_mScan_Priv::isvcscandata_SyncComplete(void)
{
/*	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
	
	isigstr_StopSigStrMeasAll();
	iinsN_OnEvent(iinsN_EventInsCompleted, mInstStatus.Lnb);
*/
	TraceNotice (m, "%s mInstStatus.BlindScanInProgress %d AstraLCN Enabled %d AstraScanMode %d \n", __FUNCTION__, mInstStatus.BlindScanInProgress, mAstraScanStatus.Enable, mAstraScanStatus.Mode);
	
	if(mInstStatus.BlindScanInProgress == TRUE)
	{
		mInstStatus.BlindScanInProgress = FALSE;
		SET_INS_STATE(StIdle);

		iinsN_OnEvent(iinsN_EventLNBEnd,mInstStatus.Lnb);
	}
	if ((mAstraScanStatus.Enable) && (mAstraScanStatus.Mode == SDSDScan)) 
	{
		SET_INS_STATE(StIdle);
		iinsN_OnEvent(iinsN_EventLNBEnd,mInstStatus.Lnb);
		mAstraScanStatus.Mode = Idle;
		mAstraScanStatus.Enable = FALSE;		
	}
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsGeneric_mScan_Priv::isvcscanpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbsins_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
}

void CHsvDvbsGeneric_mScan_Priv::isvcscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;

	/* Initializing the other modules. TODO: Confirm :this is not to be called during StartInstallation */
	idataacq_Initialise (0);
}

void CHsvDvbsGeneric_mScan_Priv::isvcscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

/* provides IHsvDigitalAcquisitionNotify iacqN */
void CHsvDvbsGeneric_mScan_Priv::iscanAcqN_OnDataAquired  (Bool Status)
{

	if( ((CURRENT_MODE == insstate_InstallationUpdate) || (insstate_InstallationAutomaticUpdate)) && (CurrentEntryForUpdate < NumEntriesForUpdate))
	{
		CurrentEntryForUpdate++;
	}

	/* Giving channel found notification to ceapps so that 
	they can update the number of channels found */
	iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.Lnb);

	if( mAstraScanStatus.Enable )
	{
		if(mAstraScanStatus.Mode == Homing)
		{
			if(Status)
			{
				mAstraScanStatus.Mode = SDSDScan;
				mAstraScanStatus.NumOfSDSD = idataacq_GetNumberOfSdsds();
			}
			else
			{
				TraceNotice(m,"%s: %d: SDSD acquisition Failed",__FUNCTION__,__LINE__);
			}
		}
		else
		{
			mAstraScanStatus.CurrSdsdIndex++;
		}
	}

	SET_INS_STATE (StStart);
	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		TraceNotice (m, " StartTuning Sent \n");
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	UNUSED(Status);
}


/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetCurrentInstallationState (int *mode, int *state)
{
	/* Function to get the installation mode and status */
	int		RetVal = err_Ok;
	if (mode && state)
	{
		*mode = CURRENT_MODE;
		*state = mInstStatus.IntallationState;
	}
	return RetVal;
}

int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetAttribute(int Mode, int AttributeId)
{
	int			RetVal = 0;

	return RetVal;
}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

int CHsvDvbsGeneric_mScan_Priv::mGetSatID(int LnbNumber)
{
	HsvPgdatDigSatInfoData SatDetails;
	pgdb_Initialise(pgdbconst_SatInfo, (Address) &SatDetails);
	SatDetails.LnbNumber = LnbNumber;
	
	if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails) != TRUE)
	{
		TraceNotice (m," ERROR: mGetSatID failed for LNB: %d!!! \n",LnbNumber);
	}

	return SatDetails.SatelliteId;
}

Bool CHsvDvbsGeneric_mScan_Priv::mStoreRefNITDetails()
{

	int i = 0, NumOfLinkageDesc = 0, NumOfSDSD;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;
	HSVSPTYPE(SatelliteDS, dvb, nit)	SatDSDesc;
	Bool Found = FALSE, RetVal = FALSE;

	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));

	for(i = 0; i < NumOfLinkageDesc ; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, nit), i, (void*)(&LinkageDesc)) == TRUE)
		{
			if(LinkageDesc.LinkageType == NIT_REF_LINKAGE_TYPE)
			{
				mAstraScanStatus.RefNITData.ONID = LinkageDesc.Original_NetworkId;
				mAstraScanStatus.RefNITData.TSID = LinkageDesc.Tsid;
				mAstraScanStatus.RefNITData.SvcId = LinkageDesc.ServiceId;
				Found = TRUE;
				break;
			}
		}
	}

	if(Found == TRUE)
	{
		NumOfSDSD = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
		
		for(i = 0; i < NumOfSDSD; i++)
		{
			if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&SatDSDesc)) == TRUE)
			{
				if((SatDSDesc.Original_NetworkId == mAstraScanStatus.RefNITData.ONID) && (SatDSDesc.Tsid == mAstraScanStatus.RefNITData.TSID))
				{
					mAstraScanStatus.RefNITData.Frequency = SatDSDesc.Frequency;
					mAstraScanStatus.RefNITData.Polarization = SatDSDesc.Polarization;
					mAstraScanStatus.RefNITData.ModulationSystem= SatDSDesc.ModulationSystem; 
					mAstraScanStatus.RefNITData.ModulationType= SatDSDesc.ModulationType; 
					mAstraScanStatus.RefNITData.FECInner= SatDSDesc.FECInner; 
					mAstraScanStatus.RefNITData.RollOff= SatDSDesc.RollOff; 
					RetVal = TRUE;
					break;
				}
			}
		}
		
	}
	else
	{
		TraceNotice(m,"%s: %d Linkage Descriptor is not found",__FUNCTION__,__LINE__);
	}

	TraceNotice(m,"%s: %d RetVal: %d",__FUNCTION__,__LINE__, RetVal);


	return RetVal;
}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}


/* Functions for automatic installation + update installation */
FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_StartInstallation(int Source, int Lnb, int Mode)
{
    FResult RetVal = err_BadParameter;
    HsvPgdatDigSatInfoData SatDetails;
    Nat32 PackageIndex = 0;
	Bool IsPackage = FALSE;
    insstate_GetUserPackageIndex(&PackageIndex, &IsPackage);

    if (TURNED_ON)
    {
        TraceNotice (m, "SERVICE Scan Already Turned On \n");
        /* Currently supporting only service scan. Have to update VALID_MODE as features added */
        if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
        {
            if (SCAN_NOT_INPROGESS)
            {
                TraceNotice (m, " No Service Scan in progress.. Initiating \n");
                SET_INS_MODE(Mode);
                TraceNotice (m, " PackageIndex %d IsPackage %d\n",PackageIndex,IsPackage);
                /*SDSD Scan need to be done only for Predefined ranking list on Astra Satellite*/
                if((!IsPackage) && (mGetSatID(Lnb) == ASTRA_19_2_E) && (PackageIndex != NO_SORTING_PACKAGE_ID))
                {
                    mAstraScanStatus.Enable = TRUE;
                    mAstraScanStatus.Mode = Homing;
                    mAstraScanStatus.HomingMuxIndex = 0;
                    mAstraScanStatus.CurrSdsdIndex = 0;
                    mAstraScanStatus.RefNITDetailsAvailable = FALSE;
                    mAstraScanStatus.NumOfSDSD = 0;
                }
                else
                {
                    mAstraScanStatus.Enable = FALSE;
                }
                mInstStatus.IntallationState = insstate_InstallationStateInProgress;
                /* Now initialize the freq finder module to load the SDSDs obtained from pre-scan */
                
                SET_INS_STATE (StIdle);
                pmp_PmpSend(mPump, EvStart, Lnb);
            }
            RetVal = err_Ok;
        }
    }
    return RetVal;
}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsInLnb(Lnb);

	return RetVal;
}
int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;
	
	RetVal = idataacq_GetNumberOfRadioChannelsInLnb (Lnb);

	return RetVal;
}

int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	return idataacq_GetNumberOfTvChannelsRemoved();
}
int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}
	
int CHsvDvbsGeneric_mScan_Priv::isvcscan_GetScanProgressStatus (int Mode)
{
	return ((mInstStatus.ProgressBar < 100) ? mInstStatus.ProgressBar : 99);
}
FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_WriteBarkerMuxData(void)
{
	idataacq_StoreBarkerMuxDetails();
	return TRUE;

}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}

FResult CHsvDvbsGeneric_mScan_Priv::isvcscan_StoreManualInstallationValues (void)
{
	return 0;
}

Bool CHsvDvbsGeneric_mScan_Priv::isvcscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return 0;
}

void CHsvDvbsGeneric_mScan_Priv::isvcscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
}

void CHsvDvbsGeneric_mScan_Priv::isvcscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}
