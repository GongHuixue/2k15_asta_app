/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *           %name: hsvdvbstricolor_mScan.c %
 *        %version:  TVG_2 %
 *     %derived_by: anuma %
 *	%date_modified:	 Wed Jan 07 15:30:25 2013 %
**********************************************************************/

/****************************************************************************
 * Local include files
 ****************************************************************************/

#include<stdio.h>

#include<string.h>

#include"_hsvdvbstricolor_mScan.h"


TRACESYMBOL(m, "s2/installation/hsvdvbstricolor/tricolor_mscan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/


#ifndef __cplusplus

#else

#endif



























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsTricolor_mScan_Priv::SvcScanEventNames[EvMax+1][32] =
{
	"EvStart",
	"EvStop",
	"EvDataAvailable",
	"EvDataNotAvailable",
	"EvDataAcquired",
	"EvStartTuning",
	"EvCheckLock",
	"EvMax"
};



int CHsvDvbsTricolor_mScan_Priv::s__mConstModuleLifeCycle = 0;

InsInstance CHsvDvbsTricolor_mScan_Priv::s__mInstStatus;

Pump CHsvDvbsTricolor_mScan_Priv::s__mPump;

UpdateTuneList CHsvDvbsTricolor_mScan_Priv::s__UpdateInstallList[MAX_MUX_PER_SAT];

HomingMuxData CHsvDvbsTricolor_mScan_Priv::s__TricolorPackageDetails[NO_OF_HOMING_MUX] = {{12226, satfeapi_PolarisationHorizontal, TRICOLOR_SAT_ID}};

int CHsvDvbsTricolor_mScan_Priv::s__NumEntriesForUpdate = 0;

double CHsvDvbsTricolor_mScan_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};


FunctionNat32 CHsvDvbsTricolor_mScan_Priv::s__EventActionMatrix[EvMax][StMax] =
{
							/* StIdle,						StStart,					StTunerWait,				StDemuxWait,				StAcquireWait					StRegionScanWait				*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL,						NULL,							FNADDR(FuncStartRegionScan)		},
/* EvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),	FNADDR(FuncStopServiceScan)		},
/* EvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL,							FNADDR(FuncRegionDataAcquired)		},
/* EvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL,							FNADDR(FuncNoRegionDataAvailable)		},
/* EvDataAcquired */		{  NULL,						NULL,   					NULL,						NULL,						FNADDR(FuncDataAquired),		FNADDR(FuncDataAquired)			},
/* EvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL,						NULL,							FNADDR(FuncStartTuning)			},
/* EvCheckLock */			{  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL,							FNADDR(FuncCheckLockStatus)		}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

 void CHsvDvbsTricolor_mScan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m," TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);
	TraceNotice(m, "SvcScan: %s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
	if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
	{
		if(EventActionMatrix[event][mInstStatus.State] != NULL)
		{
			TraceNotice (m, "SvcScan: %s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
			FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
		}
	}
}

void CHsvDvbsTricolor_mScan_Priv::FuncStartRegionScan (Nat32 param)
{

	TraceNotice(m," TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);
	/* Getting the LNB Details */
	mGetLnbDetails(TRICOLOR_SAT_ID);
	mInstStatus.IntallationState = insstate_InstallationStateRegionScan;
	mInstStatus.HomingMuxIndex = 0;
	mInstStatus.NumOfSDSD = 0;
	mInstStatus.CurrSdsdIndex = 0;
	SET_SCAN_MODE(Homing);
	SET_INS_STATE(StRegionScanWait);
	
	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);

	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}

}

void CHsvDvbsTricolor_mScan_Priv::FuncRegionDataAcquired (Nat32 param)
{

	
	SET_INS_STATE(StIdle);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	SET_INS_MODE(insstate_InstallationNone);
	iinsN_OnEvent(iinsN_EventRegionScanEnd, 0);
	SET_SCAN_MODE(Invalid);
	
	if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	TraceNotice(m,"%s Exit state: %d",__FUNCTION__,mInstStatus.State);

	
}

void CHsvDvbsTricolor_mScan_Priv::FuncNoRegionDataAvailable (Nat32 param)
{

	SET_INS_STATE (StIdle);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	SET_INS_MODE(insstate_InstallationNone);
	iinsN_OnEvent(iinsN_EventRegionScanEnd, 0);
	SET_SCAN_MODE(Invalid);	
	if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}

}



void CHsvDvbsTricolor_mScan_Priv::FuncStartServiceScan (Nat32 param1)
{
	/* Getting the LNB Details */
	TraceNotice(m,"%s MODE %d",__FUNCTION__,ctrl_GetMode(HsvDmxMain));
	
	mGetLnbDetails(TRICOLOR_SAT_ID);
	mInstStatus.HomingMuxIndex = 0;
	mInstStatus.NumOfSDSD = 0;
	mInstStatus.CurrSdsdIndex = 0;
	SET_SCAN_MODE(Homing);
	SET_INS_STATE (StStart);

	iinsN_OnEvent(iinsN_EventPkgInstallStart,0);

	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}

	UNUSED (param1);
}

void CHsvDvbsTricolor_mScan_Priv::FuncStartTuning (Nat32 param1)
{
	TraceNotice(m,"TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);
	int		ModlnStd = -1, IqMode = -1, Cookie = 0;
	int 	RollOff = -1, FEC = -1, Pilots = -1;
	int		SymbolRate = 0,ModlnType = -1;
	Bool    LockState = TRUE;
	int 	state,mode;
	isvcscan_GetCurrentInstallationState(&mode, &state);
	HsvNITSatelliteDS CurrSDSD;

	

	TraceNotice(m,"current scan mode %d and Installation mode %d",CURRENT_SCAN_MODE,mode);
	if(CURRENT_SCAN_MODE == Homing)
	{
		if(mInstStatus.HomingMuxIndex < NO_OF_HOMING_MUX)
		{
				if((mInstStatus.State != StRegionScanWait) && (mode == insstate_InstallationServiceScan) && (!IsUpdateInstall()))
				{
					//By this time we are finished with TricolorRegionScan mode and we are in Tricolor Normal mode.
					TraceNotice(m,"During Auto Installation:Already tuned to Homing Mux:Just Change the state & trigger event to checklockstatus");
					SET_INS_STATE(StTunerWait);
					pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
				}
				else
				{
					TraceNotice  (m,"LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
					mInstStatus.LnbNumber,
					mInstStatus.LnbType,
					TricolorPackageDetails[mInstStatus.HomingMuxIndex].Frequency,
					SymbolRate,
					TricolorPackageDetails[mInstStatus.HomingMuxIndex].Polarization);
					if(IsUpdateInstall())
					{
						SET_INS_STATE(StTunerWait);
					}
					satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (TricolorPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
								SymbolRate, TricolorPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, ModlnStd, ModlnType, IqMode,RollOff, FEC, Pilots);
				}
		}		
		else
		{
			SET_INS_STATE (StIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}

	}
	else if(CURRENT_SCAN_MODE == Fallback)
	{
		if(mInstStatus.CurrSdsdIndex < mInstStatus.NumOfSDSD)
		{

			/*Get current SDSD and tune to that*/
			idataacq_GetSdsdByIndex(mInstStatus.CurrSdsdIndex,&CurrSDSD);

			TraceNotice  (m, "SvcScan: SDSD Freq %d Tricolor pol %d SymbolRate %d", (int)CurrSDSD.Frequency, (int)CurrSDSD.Polarization,(int)CurrSDSD.SymbolRate);
			SET_INS_STATE(StTunerWait);
			satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (CurrSDSD.Frequency), \
										CurrSDSD.SymbolRate, CurrSDSD.Polarization,Cookie, ModlnStd, CurrSDSD.ModulationType, IqMode,RollOff, FEC, Pilots);
		}
		else
		{
			TraceNotice (m, " Package only scan completed on Lnb %d \n",mInstStatus.LnbNumber);

			itricolorsettings->SaveSatelliteSettingsToPersistent();
			itricolorsettings->CommitSatelliteSettingsToPersistent();
			SET_INS_STATE(StIdle);
			SET_SCAN_MODE(Invalid);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
			iinsN_OnEvent(iinsN_EventPkgInstallEnd, 0);
		}
	}
	else
	{
		TraceNotice(m,"ERROR !!! should not reach here Current Scan mode is Invalid\n");	
	}

	UNUSED (param1);
}

void CHsvDvbsTricolor_mScan_Priv::FuncCheckLockStatus(Nat32 Cookie)
{
	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams(&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);

	TraceNotice(m, "Freq %d Sym %d  \n",LockedFreq, SymbolRate);
	if ((RetVal == err_Ok) && (LockStatus == 0))
	{
		mNoStationFound();
	}
	else
	{
		mStationFound();
	}
}

void CHsvDvbsTricolor_mScan_Priv::mStationFound (void)
{
	TraceNotice(m,"TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);

	if(CURRENT_SCAN_MODE == Homing)
	{
		if (mInstStatus.State != StRegionScanWait)
		{
			SET_INS_STATE(StDemuxWait);
			ctrl_StartCollection(HsvDmxMain, ctrl_TricolorNormal);
		}
		else 
		{
			ctrl_StartCollection(HsvDmxMain,ctrl_PkgBuildMode);
		}
	}
	else if(CURRENT_SCAN_MODE == Fallback)
	{
		SET_INS_STATE(StDemuxWait);
		TraceNotice(m,"Station Found:Fallback mode:Started collection in ctrl_Normal Mode");
		ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
	}
	
}

void CHsvDvbsTricolor_mScan_Priv::mNoStationFound (void)
{
	TraceNotice(m,"TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);
	if(CURRENT_SCAN_MODE == Homing)
	{
		/*Tune to next homing frequency*/
		mInstStatus.HomingMuxIndex++;
	}
	else
	{
		/*Tune to next SDSD*/
		mInstStatus.CurrSdsdIndex++;
		SET_INS_STATE (StStart);
	}

	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
}

void CHsvDvbsTricolor_mScan_Priv::FuncDataAvailable (Nat32 param1)
{
	int Mode;
	TraceNotice(m,"TRICOLOR: %s:%d mode %d\n",__FUNCTION__, __LINE__,CURRENT_SCAN_MODE);
	if(CURRENT_SCAN_MODE == Homing)
	{
		Mode = idataacq_Homing;
		idataacq_Initialise (0);
	}
	else
	{
		Mode = idataacq_Fallback;
	}
	idataacq_AcquireData(Mode);
	SET_INS_STATE(StAcquireWait);

	UNUSED (param1);
}

void CHsvDvbsTricolor_mScan_Priv::FuncNoDataAvailable (Nat32 param1)
{
	TraceNotice(m,"TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);
	if(CURRENT_SCAN_MODE == Homing)
	{
		/*Tune to next homing frequency*/
		mInstStatus.HomingMuxIndex++;
	}
	else
	{
		/*Tune to next SDSD frequency*/
		mInstStatus.CurrSdsdIndex++;
	}

	SET_INS_STATE (StStart);
	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}

	UNUSED (param1);
}

void CHsvDvbsTricolor_mScan_Priv::FuncDataAquired (Nat32 param1)
{
	Bool Result = (Bool)param1;
	TraceNotice(m,"TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);

	if (CURRENT_SCAN_MODE == Homing)
	{
		if(TRUE == Result)
		{
			mInstStatus.NumOfSDSD = idataacq_GetNumberOfSdsds();
			mInstStatus.CurrSdsdIndex= 0;
			SET_SCAN_MODE( Fallback);
			SET_INS_STATE (StStart);
			if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
			{
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
			else
			{
				ctrl_StopCollection(HsvDmxMain);
			}
		}
		else
		{
			//Update Installation Failure due to absence of Valid Channel List Name.
			SET_INS_STATE (StIdle);
			SET_SCAN_MODE(Invalid);
			if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
			{
				ctrl_StopCollection(HsvDmxMain);
			}
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}
	}
	else if(CURRENT_SCAN_MODE == Fallback)
	{
		//Tune to Next SDSD.
	    if(TRUE == Result)
		{
			mInstStatus.CurrSdsdIndex++;
			SET_INS_STATE (StStart);
			if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
			{
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
			else
			{
				ctrl_StopCollection(HsvDmxMain);
			}
		}
	}

	/* To Update Channel count*/
	iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.LnbNumber);
}

void CHsvDvbsTricolor_mScan_Priv::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice(m,"TRICOLOR: %s:%d\n",__FUNCTION__, __LINE__);
	SET_INS_STATE(StIdle);
	SET_SCAN_MODE(Invalid);

	/* Stop the SDM */
	isigstr_StopSigStrMeasAll();
	if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	iinsN_OnEvent(iinsN_EventInsStopped,0);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	SET_INS_MODE(insstate_InstallationNone);
	UNUSED (param1);
}

void CHsvDvbsTricolor_mScan_Priv::mGetLnbDetails(int SatId)
{
	int LnbIndex;
	HsvPgdatDigSatInfoData SatDetails;
	for(LnbIndex=0; LnbIndex < MAX_NUM_LNBS_SUPPORTED; LnbIndex++)
	{
		pgdb_Initialise(SAT_INFO_TABLE, (Address) &SatDetails);
		SatDetails.LnbNumber = LnbIndex;
		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails) != TRUE)
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n",LnbIndex);
		}

		if(SatDetails.SatelliteId == SatId)
		{
			mInstStatus.LnbNumber = LnbIndex;
			mInstStatus.LnbType = SatDetails.LnbType;
			break;
		}
	}
}

void CHsvDvbsTricolor_mScan_Priv::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
{

	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);

	if (RetVal == err_Ok)
	{
		ptc->Frequency = LockedFreq;
		ptc->SymbolRate = SymbolRate;
		ptc->ModulationType = 0;
		ptc->CodeRateHigh = 0;
		ptc->CodeRateLow = 0;
		ptc->IqMode = IqMode;
		ptc->ChannelBandwidth = Bandwidth;
		ptc->Polarization = Polarization;
	}
}

Bool CHsvDvbsTricolor_mScan_Priv::IsUpdateInstall(void)
{
    int mode, state;

    isvcscan_GetCurrentInstallationState(&mode, &state);

    return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate) || (mode == insstate_InstallationBackgroundUpdate))? TRUE: FALSE);
}


/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx	 isvcscanctrlN */

void CHsvDvbsTricolor_mScan_Priv::isvcscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceNotice (m, " EventId 0x%x Value 0x%x  state %d ", EventId ,Value,mInstStatus.State);
	if (VALID_DEMUX(Dmx))
	{

		switch (EventId)
		{
		case	isvcscanctrlN_DataNotAvailable:
			pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
			PrintfNotice("Data Not avilable: %d: %d\n", (!(Value & isvcscanctrlN_NIT)), (Value & isvcscanctrlN_NIT));
			break;
		case	isvcscanctrlN_StoppedCollection:
				if(mInstStatus.State != StIdle)
				{
					pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
				}	
				break;
		case	isvcscanctrlN_DataAvailable:
			TraceNotice(m," debug:Data Available !");
			if(CURRENT_SCAN_MODE == Homing)
			{
				if(mInstStatus.State == StRegionScanWait)
				{
					if ((Value & isvcscanctrlN_BAT))
					{
						pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
					}
					
				}
				else 
				{	
					if ((Value & isvcscanctrlN_NIT) && (Value & isvcscanctrlN_BAT))
					{
						TraceNotice(m," debug:NIT & BAT  Available !");
						pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
					}
				}
			}
			else if(CURRENT_SCAN_MODE == Fallback)
			{
				if (Value & isvcscanctrlN_SDT)
				{
					TraceNotice(m,"%s %d SDT data available in Fallback Mode\n",__FUNCTION__,__LINE__);
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
				else if(Value & isvcscanctrlN_NIT)
				{
					TraceNotice(m,"%s %d Only NIT data available,But SDT not Present in Fallback Mode\n",__FUNCTION__,__LINE__);
					pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
				}
					
			}
			break;
		case	isvcscanctrlN_SiDataAvailable:
			if(CURRENT_SCAN_MODE == Fallback)
			{
				if (Value & isvcscanctrlN_SDT)
				{
					TraceNotice(m,"%s %d SDT data available in Fallback Mode\n",__FUNCTION__,__LINE__);
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
			}
			break;
		case	isvcscanctrlN_StartedCollection:
			break;
		default:
			break;
		}
	}
}

void CHsvDvbsTricolor_mScan_Priv::plfApidvbsN_OnLockChanged( Bool LockState)
{
	/* Notifiation Handler for DVB-S platform FE */
	TraceNotice(m,"%s Notification came",__FUNCTION__);
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		isvcscandata	*/

void CHsvDvbsTricolor_mScan_Priv::isvcscandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
	int	TransponderFreq;
    int count;
	HsvNITSatelliteDS CurrSDSD;

	ptc->LnbNumber = mInstStatus.LnbNumber;
	ptc->LnbType = mInstStatus.LnbType;

	/* Get the SDSD from Acq*/
	idataacq_GetSdsdByIndex(mInstStatus.CurrSdsdIndex,&CurrSDSD);
	
	//mGetCurrentTunerParams (ptc);

	ptc->Frequency 		  = CurrSDSD.Frequency;
	ptc->SymbolRate 	  = CurrSDSD.SymbolRate;
	ptc->ModulationType   = CurrSDSD.ModulationType;
	ptc->ModulationStd    = CurrSDSD.ModulationSystem;
	ptc->CodeRate   	  = CurrSDSD.FECInner;
	ptc->Polarization 	  = CurrSDSD.Polarization;

	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);

	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);

	TraceNotice  (m, " Freq %d and BW : %d \n", TransponderFreq, ptc->ChannelBandwidth);
	ptc->QSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsQsm);
	ptc->SSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsSsm);

	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd(CurrSDSD.RollOff, CurrSDSD.SymbolRate,CurrSDSD.FECInner);

	ptc->SDSDFrequency = CurrSDSD.Frequency;
	ptc->PlpId = 0;
	ptc->HierarchyMode = HsvHierarchyNone;
	ptc->StreamPriority = HsvStreamPriorityHigh;
 }

int CHsvDvbsTricolor_mScan_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
{
	double	Bandwidth = 0;

	if (IS_VALID_ROLLOFF(RollOff))
	{
		/* SB = SR(1+Ro) */
		Bandwidth = SymbolRate * (1+RollOffTable[RollOff]);
	}
	Bandwidth /= 1000;	/* To make it in KHz */
	UNUSED (FECInner);

	return (Nat8)Bandwidth;
}

 int CHsvDvbsTricolor_mScan_Priv::isvcscandata_GetInstallationVersion(void)
{
	 return 0;
}

void CHsvDvbsTricolor_mScan_Priv::isvcscandata_SyncComplete(void)
{
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsTricolor_mScan_Priv::isvcscanpow_Init(void)
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbtricolor_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
	isortpow_Init ();
	
}

void CHsvDvbsTricolor_mScan_Priv::isvcscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;

	/* Initializing the other modules.*/
	idataacq_Initialise (0);
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
	
}

void CHsvDvbsTricolor_mScan_Priv::isvcscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
	
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetCurrentInstallationState (int *mode, int *state)
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

/* Functions for automatic installation + update installation */
FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_StartInstallation(int Source, int Lnb, int Mode)
{
	TraceNotice(m,"%s source %d lnb %d  mode %d state %d",__FUNCTION__,Source,Lnb,Mode,mInstStatus.State);
	FResult			RetVal = err_BadParameter;
	if (TURNED_ON)
	{
		if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			if (SCAN_NOT_INPROGESS)
			{
				SET_INS_MODE(Mode);
				mInstStatus.IntallationState = insstate_InstallationStateInProgress;
				pmp_PmpSend(mPump, EvStart, (Nat32)NULL);
			}
			RetVal = err_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	return RetVal;
}
int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfRadioChannelsFound ();

	return RetVal;
}

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsRemoved();
}
int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_WriteBarkerMuxData(void)
{
	TraceNotice(m,"DummyCall:isvcscan_WriteBarkerMuxData"); 
	return 0;
}

void CHsvDvbsTricolor_mScan_Priv::isvcscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	int Package_Id = 0;

	SiValues->Pid = 0x1FFF;
	SiValues->BouquetId = 0xFFFF;
	Package_Id = insstate_GetAttribute(insstate_InstallationNone, insstate_AttributePackageId);

	if((TRICOLOR_SD_PACKAGE_ID == (Package_Id  & 0xFFFF)) || (TRICOLOR_HD_PACKAGE_ID == (Package_Id  & 0xFFFF)))
	{
		switch(SiValues->TableId)
		{
			
			case 0x4A: /*BAT*/
			   if(mInstStatus.State == StRegionScanWait)
			   {
			   		SiValues->BouquetId = TRICOLOR_BOUQUET_ID_1;
			   }
			   break;
					   
		    case 0x40: /*NIT Actual*/
						break;
		    case 0x42: /*SDT Actual*/
						break;
		    case 0x46: /*SDT Other*/
						break;
		    default:    break;
		}
	}
    #if 0
	SiValues->TableId = BAT_TABLE_ID;
	SiValues->BouquetId = TRICOLOR_BOUQUET_ID_1;
	if(Homing == CURRENT_SCAN_MODE)
	{
		/*table ID is passed as 0x46 to trigger SDT other collection*/
		SiValues->TableId = 0x46;
	}
	else
	{
		SiValues->TableId = 0;
	}
#endif
    
	TraceNotice (m, "%s %d:table id: %d\n", __FUNCTION__, __LINE__, SiValues->TableId);

}

void CHsvDvbsTricolor_mScan_Priv::idataacqN_OnDataAquired(Bool Result)
{
	pmp_PmpSend(mPump, EvDataAcquired, (Nat32)Result);
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);

}

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

 

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "StartTricolorRegionParsing");
	  SET_INS_STATE(StRegionScanWait);
	  pmp_PmpSend(mPump, EvStart, (Nat32)0);

	  /*SetAttribute is needed here to initialize Current Region Name to Null as this New AutoInstallation*/
	  HSVSPTYPE(TricolorRegionName, dvb, bat) tricolorLRN;
	  memset(&tricolorLRN,0x00,sizeof(HsvTricolorRegionNameData));
	  itricolorsettings_SetAttribute(idvbset_AttributeTricolorRegionNameData,(Nat32)&tricolorLRN);
	  
	  TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	  return err_Ok;
}

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "GetTricolorRegionNames");
	  idataacq_GetTricolorRegionNames (names, len);
	  return err_Ok;
}

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_SetTricolorRegionIndex(int index)
{
	  char general[24] = "FEDERAL";
	  
	  TraceNotice(m, "SetTricolorRegionIndex - %d", index);
	  HSVSPTYPE(TricolorRegionName, dvb, bat) tricolorLRN;

		
	  memset(&tricolorLRN,0x00,sizeof(HsvTricolorRegionNameData));
	  
	  int no_Regions_found = strapi_GetSize(HsvMain,HSVSPID(TricolorRegionName, dvb, bat));
	  
    	if(no_Regions_found > 0)
    	{
    		  if(index == 0) // This will point to GENERAL Region
    		  {
    		  	strncpy(tricolorLRN.regionName,general,sizeof(general));
    			tricolorLRN.regionNameLength = strlen(general);
				
    
    			/*TraceNotice(m,"Region Name selected is: %s %d %p %p %p\n",tricolorLRN.regionName,tricolorLRN.regionNameLength,\
																			&tricolorLRN.regionName,&tricolorLRN.regionNameLength,\ 
																			&tricolorLRN);*/
																			
    		  	itricolorsettings_SetAttribute(idvbset_AttributeTricolorRegionNameData,(Nat32)&tricolorLRN);
    		  }
    		  else
    		  {
    		  	if(strapi_GetByIndex(HsvMain,HSVSPID(TricolorRegionName, dvb, bat),index - 1,&tricolorLRN))
    		  	{
    		  		itricolorsettings_SetAttribute(idvbset_AttributeTricolorRegionNameData,(Nat32)&tricolorLRN);
    		  	}
    		  }
    	}
        else
		{
		  	TraceNotice(m,"Region Name List is empty assigning FEDERAL\n");
			strncpy(tricolorLRN.regionName,general,sizeof(general));
			tricolorLRN.regionNameLength = sizeof(general);
			tricolorLRN.regionName[tricolorLRN.regionNameLength] = '\0';
		  	itricolorsettings_SetAttribute(idvbset_AttributeTricolorRegionNameData,(Nat32)&tricolorLRN);
		}
		
	  TraceNotice(m,"Region Name selected is: %s\n",tricolorLRN.regionName);
	  return err_Ok;
}

Bool CHsvDvbsTricolor_mScan_Priv::isvcscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsTricolor_mScan_Priv::isvcscan_GetScanProgressStatus (int Mode)
{
	return 0;
}
			
void CHsvDvbsTricolor_mScan_Priv::plfApidvbsN_OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}

void CHsvDvbsTricolor_mScan_Priv::isvcscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}

FResult CHsvDvbsTricolor_mScan_Priv::isvcscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}