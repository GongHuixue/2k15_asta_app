/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *           %name: hsvdvbsfransat_mScan.c %
 *        %version:  TVG_2 %
 *     %derived_by: anuma %
 *	%date_modified:	 Wed Jan 07 15:30:25 2013 %
**********************************************************************/

/****************************************************************************
 * Local include files
 ****************************************************************************/

#include<stdio.h>

#include<string.h>

#include"_hsvdvbsfransat_mScan.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsfransat/fransat_mscan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/


#ifndef __cplusplus

#else

#endif



























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsFransat_mScan_Priv::SvcScanEventNames[EvMax+1][32] =
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



int CHsvDvbsFransat_mScan_Priv::s__mConstModuleLifeCycle = 0;

InsInstance CHsvDvbsFransat_mScan_Priv::s__mInstStatus;

Pump CHsvDvbsFransat_mScan_Priv::s__mPump;

UpdateTuneList CHsvDvbsFransat_mScan_Priv::s__UpdateInstallList[MAX_MUX_PER_SAT];

HomingMuxData CHsvDvbsFransat_mScan_Priv::s__FransatPackageDetails[NO_OF_HOMING_MUX] = {{11554, satfeapi_PolarisationVertical, FRANSAT_SAT_ID},
                                                                                                                    {11096, satfeapi_PolarisationVertical, FRANSAT_SAT_ID},
                                                                                                                    {10971, satfeapi_PolarisationVertical, FRANSAT_SAT_ID}};

int CHsvDvbsFransat_mScan_Priv::s__NumEntriesForUpdate = 0;












FunctionNat32 CHsvDvbsFransat_mScan_Priv::s__EventActionMatrix[EvMax][StMax] =
{
							/* StIdle,						StStart,					StTunerWait,				StDemuxWait,				StAcquireWait		*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL,						NULL				},
/* EvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)	},
/* EvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL				},
/* EvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL				},
/* EvDataAcquired */		{  NULL,						NULL,   					NULL,						NULL,						FNADDR(FuncDataAquired)		},
/* EvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL,						NULL				},
/* EvCheckLock */			{  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL				}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

 void CHsvDvbsFransat_mScan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m," FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsFransat_mScan_Priv::FuncStartServiceScan (Nat32 param1)
{
	/* Getting the LNB Details */
	mGetLnbDetails(FRANSAT_SAT_ID);
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

void CHsvDvbsFransat_mScan_Priv::FuncStartTuning (Nat32 param1)
{
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
	int		ModlnStd = -1, IqMode = -1, Cookie = 0;
	int		SymbolRate = 0,ModlnType = -1;
	HsvNITSatelliteDS CurrSDSD;
	int 	RollOff = -1, FEC = -1, Pilots = -1; 

	if(CURRENT_SCAN_MODE == Homing)
	{
		if(mInstStatus.HomingMuxIndex < NO_OF_HOMING_MUX)
		{
			TraceNotice  (m,"LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
				mInstStatus.LnbNumber,
				mInstStatus.LnbType,
				FransatPackageDetails[mInstStatus.HomingMuxIndex].Frequency,
				SymbolRate,
				FransatPackageDetails[mInstStatus.HomingMuxIndex].Polarization);
			SET_INS_STATE(StTunerWait);
			satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (FransatPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
								SymbolRate, FransatPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);
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
	else
	{
		if(mInstStatus.CurrSdsdIndex < mInstStatus.NumOfSDSD)
		{

			/*Get current SDSD and tune to that*/
			idataacq_GetSdsdByIndex(mInstStatus.CurrSdsdIndex,&CurrSDSD );

			TraceNotice  (m, "SvcScan: SDSD Freq %d Fransat %d ", (int)CurrSDSD.Frequency, (int)CurrSDSD.Polarization);

			SET_INS_STATE(StTunerWait);
			satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (CurrSDSD.Frequency), \
										CurrSDSD.SymbolRate, CurrSDSD.Polarization,Cookie, ModlnStd, CurrSDSD.ModulationType, IqMode, RollOff, FEC, Pilots);
		}
		else
		{
			TraceNotice (m, " Package only scan completed on Lnb %d \n",mInstStatus.LnbNumber);
			SET_INS_STATE(StIdle);
			SET_SCAN_MODE(Invalid);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
			iinsN_OnEvent(iinsN_EventPkgInstallEnd, 0);
		}
	}

	UNUSED (param1);
}

void CHsvDvbsFransat_mScan_Priv::FuncCheckLockStatus(Nat32 Cookie)
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

void CHsvDvbsFransat_mScan_Priv::mStationFound (void)
{
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
	SET_INS_STATE(StDemuxWait);
	ctrl_StartCollection(HsvDmxMain, ctrl_Minimal);

}

void CHsvDvbsFransat_mScan_Priv::mNoStationFound (void)
{
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
	if(CURRENT_SCAN_MODE == Homing)
	{
		/*Tune to next homing frequency*/
		mInstStatus.HomingMuxIndex++;
	}
	else
	{
		/*Tune to next SDSD*/
		mInstStatus.CurrSdsdIndex++;
	}
	SET_INS_STATE (StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
}

void CHsvDvbsFransat_mScan_Priv::FuncDataAvailable (Nat32 param1)
{
	int Mode;
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsFransat_mScan_Priv::FuncNoDataAvailable (Nat32 param1)
{
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsFransat_mScan_Priv::FuncDataAquired (Nat32 param1)
{
	Bool Result = (Bool)param1;
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);

	if(CURRENT_SCAN_MODE == Homing)
	{
		/*If whole data is acquired(i.e. SDTother is present), complete the installation, otherwise start SDSD based scan*/
		if(TRUE == Result)
		{
			SET_INS_STATE (StIdle);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
			iinsN_OnEvent(iinsN_EventPkgInstallEnd, 0);
			SET_SCAN_MODE(Invalid);

			if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
			{
				ctrl_StopCollection(HsvDmxMain);
			}
		}
		else
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
	}
	else
	{
		mInstStatus.CurrSdsdIndex++;

		SET_INS_STATE (StStart);

		ctrl_StopCollection(HsvDmxMain);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);

	}
}

void CHsvDvbsFransat_mScan_Priv::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice(m,"FRANSAT: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsFransat_mScan_Priv::mGetLnbDetails(int SatId)
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

void CHsvDvbsFransat_mScan_Priv::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
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

void CHsvDvbsFransat_mScan_Priv::mBuildCurrentFrequencyList (void)
{
    int     Count =0;
    int From =0;
    int To = 0;
    int NumEntry =0;
    HsvPgdatDigTSData   TempTsData;

    TempTsData.LnbNumber = mInstStatus.LnbNumber;
	
    if (pgdb_GetRange (PTC_TABLE, 1, (Address)&TempTsData, &From, &To))
    {
        for (Count = From, NumEntry = 0; ((Count <= To) && (NumEntry < MAX_MUX_PER_SAT)); Count++,NumEntry++)
        {
            if (TRUE == pgdb_GetByIndex (PTC_TABLE, Count ,(Address)&TempTsData))
            {
                UpdateInstallList[NumEntry].Frequency = TempTsData.Frequency;
                UpdateInstallList[NumEntry].Polarization = TempTsData.Polarization;
                UpdateInstallList[NumEntry].SymbolRate = TempTsData.SymbolRate;
                TraceNotice(m,"[%d][%d][%d]",UpdateInstallList[NumEntry].Frequency,TempTsData.Frequency,Count);
            }
        }
        NumEntriesForUpdate = NumEntry;
    }
}

Bool CHsvDvbsFransat_mScan_Priv::IsUpdateInstall(void)
{
    int mode, state;

    isvcscan_GetCurrentInstallationState(&mode, &state);

    return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate) || (mode == insstate_InstallationBackgroundUpdate))? TRUE: FALSE);
}


/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx	 isvcscanctrlN */

void CHsvDvbsFransat_mScan_Priv::isvcscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceNotice (m, " EventId 0x%x Value 0x%x ", EventId ,Value);
	if (VALID_DEMUX(Dmx))
	{

		switch (EventId)
		{
		case	isvcscanctrlN_DataNotAvailable:
			pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
			PrintfNotice("Data Not avilable: %d: %d\n", (!(Value & isvcscanctrlN_NIT)), (Value & isvcscanctrlN_NIT));
			break;
		case	isvcscanctrlN_StoppedCollection:
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			break;
		case	isvcscanctrlN_DataAvailable:
			if(CURRENT_SCAN_MODE == Homing)
			{
				/* in Homing mode NIT is madatory,if SDT is not present then services can be installed without name also*/
				if ((Value & isvcscanctrlN_NIT) && (Value & isvcscanctrlN_BAT))
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
				else
				{
					pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
				}
			}
			else if(CURRENT_SCAN_MODE == Fallback)
			{
				/*in Fallback mode SDT is mandatory ,on tuning to each SDSD (each frequency) SDT acual is needed to install the services.*/
				if(Value & isvcscanctrlN_SDT)
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
				else
				{
					pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
				}
			}
			break;
		case	isvcscanctrlN_SiDataAvailable:
			if(CURRENT_SCAN_MODE == Fallback)
			{
				if (Value & isvcscanctrlN_SDT)
				{
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

void CHsvDvbsFransat_mScan_Priv::plfApidvbsN_OnLockChanged( Bool LockState)
{
	/* Notifiation Handler for DVB-S platform FE */
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		isvcscandata	*/

void CHsvDvbsFransat_mScan_Priv::isvcscandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
	int	TransponderFreq;
    int count;
	HsvNITSatelliteDS CurrSDSD;

	ptc->LnbNumber = mInstStatus.LnbNumber;
	ptc->LnbType = mInstStatus.LnbType;

	mGetCurrentTunerParams (ptc);

	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);

    	if(IsUpdateInstall())
	{
		for (count = 0; count <= NumEntriesForUpdate ; count++)
		{
			if (  (UpdateInstallList[count].Polarization == ptc->Polarization) &&
				 (util_CheckFreqDuplicationwithRolFact(ptc->Frequency, UpdateInstallList[count].Frequency, ptc->SymbolRate)))
			{
				/* Frequency drift handling. SI based check will happen in Acq module */
				TraceNotice(m,"%s: Replacing TS freq %d with %d", __FUNCTION__, ptc->Frequency, UpdateInstallList[count].Frequency);
				ptc->Frequency = UpdateInstallList[count].Frequency;
				break;
			}
		}

    		if ( count == NumEntriesForUpdate &&
			 NumEntriesForUpdate  < (MAX_MUX_PER_SAT - 1) )
		{
			UpdateInstallList[NumEntriesForUpdate].Frequency = ptc->Frequency;
			UpdateInstallList[NumEntriesForUpdate].Polarization = ptc->Polarization;
			UpdateInstallList[NumEntriesForUpdate].SymbolRate = ptc->SymbolRate;
                    	NumEntriesForUpdate ++;
		}
	}

	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);

	TraceNotice  (m, " Freq %d and BW : %d \n", TransponderFreq, ptc->ChannelBandwidth);
	ptc->QSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsQsm);
	ptc->SSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsSsm);

	/* Get the SDSD from Acq*/
	idataacq_GetSdsdByIndex(mInstStatus.CurrSdsdIndex,&CurrSDSD );

	ptc->SDSDFrequency = CurrSDSD.Frequency;
	ptc->PlpId = 0;
	ptc->HierarchyMode = HsvHierarchyNone;
	ptc->StreamPriority = HsvStreamPriorityHigh;
 }

 int CHsvDvbsFransat_mScan_Priv::isvcscandata_GetInstallationVersion(void)
{
	 return 0;
}

void CHsvDvbsFransat_mScan_Priv::isvcscandata_SyncComplete(void)
{
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsFransat_mScan_Priv::isvcscanpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbfransat_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
	isortpow_Init ();
	ibckgndpow_Init ();
}

void CHsvDvbsFransat_mScan_Priv::isvcscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;

	/* Initializing the other modules.*/
	idataacq_Initialise (0);
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
	ibckgndpow_TurnOn ();
}

void CHsvDvbsFransat_mScan_Priv::isvcscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
	ibckgndpow_TurnOff ();
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetCurrentInstallationState (int *mode, int *state)
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
FResult CHsvDvbsFransat_mScan_Priv::isvcscan_StartInstallation(int Source, int Lnb, int Mode)
{
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

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	return RetVal;
}
int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfRadioChannelsFound ();

	return RetVal;
}

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsRemoved();
}
int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_WriteBarkerMuxData(void)
{
	TraceNotice(m,"DummyCall:isvcscan_WriteBarkerMuxData"); 
	return 0;
}

void CHsvDvbsFransat_mScan_Priv::isvcscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	int Package_Id = 0;

	SiValues->Pid = 0x11;
	Package_Id = insstate_GetAttribute(insstate_InstallationNone, insstate_AttributePackageId);

	if(FRANSAT_PACKAGE_ID == (Package_Id  & 0xFFFF))
	{
		SiValues->BouquetId = ((Package_Id >> 16)  & 0xFFFF);
	}
#if 0
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
        SiValues->TableId = 0x46;
	TraceNotice (m, "%s %d:table id: %d\n", __FUNCTION__, __LINE__, SiValues->TableId);

}

void CHsvDvbsFransat_mScan_Priv::idataacqN_OnDataAquired(Bool Result)
{
	pmp_PmpSend(mPump, EvDataAcquired, (Nat32)Result);
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);

}

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_GetTricolorRegionNames(Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
Bool CHsvDvbsFransat_mScan_Priv::isvcscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsFransat_mScan_Priv::isvcscan_StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsFransat_mScan_Priv::isvcscan_GetScanProgressStatus (int Mode)
{
	return 0;
}
			
void CHsvDvbsFransat_mScan_Priv::plfApidvbsN_OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsFransat_mScan_Priv::isvcscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}

void CHsvDvbsFransat_mScan_Priv::isvcscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}
