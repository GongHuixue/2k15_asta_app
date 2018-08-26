/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *          %name: hsvdvbsrussia_mScan.c %
 *       %version: TVG_6 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: shreeshav %
 */

#include "_hsvdvbsrussia_mScan.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsrussia_mscan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#else

#endif






























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsRussia_mScan_Priv::SvcScanEventNames[EvMax+1][32] = 
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



int CHsvDvbsRussia_mScan_Priv::s__mConstModuleLifeCycle = 0;

InsInstance CHsvDvbsRussia_mScan_Priv::s__mInstStatus;

Pump CHsvDvbsRussia_mScan_Priv::s__mPump;


HomingMuxData CHsvDvbsRussia_mScan_Priv::s__RussiaDigitalPackageDetails[NO_OF_HOMING_MUX] = {{12073 , satfeapi_PolarisationHorizontal, RUSSIA_SAT_ID},
																	{12341, satfeapi_PolarisationHorizontal, RUSSIA_SAT_ID}};
















FunctionNat32 CHsvDvbsRussia_mScan_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
							/* StIdle,						StStart,					StTunerWait,				StDemuxWait,				StAcquireWait			*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL,						NULL				},
/* EvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)},
/* EvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL				},
/* EvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL				},
/* EvDataAcquired */		{  NULL,						NULL,   					NULL,						NULL,						FNADDR(FuncDataAcquired)	},
/* EvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL,						NULL				},
/* EvCheckLock */			{  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL				}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsRussia_mScan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);
	TraceNotice (m, "SvcScan: %s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
	if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
	{
		if(EventActionMatrix[event][mInstStatus.State] != NULL)
		{
			TraceNotice (m, "SvcScan: %s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
			FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
		}
	}
}

void CHsvDvbsRussia_mScan_Priv::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);
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



void CHsvDvbsRussia_mScan_Priv::mStationFound (void)
{
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);

	SET_INS_STATE(StDemuxWait);
	ctrl_StartCollection(HsvDmxMain, ctrl_Minimal);
}

void CHsvDvbsRussia_mScan_Priv::mNoStationFound (void)
{
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);
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


void CHsvDvbsRussia_mScan_Priv::FuncDataAvailable (Nat32 param1)
{
	int Mode;
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsRussia_mScan_Priv::FuncNoDataAvailable (Nat32 param1)
{
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsRussia_mScan_Priv::FuncDataAcquired (Nat32 param1)
{
	Bool Result = (Bool)param1;
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);

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

void CHsvDvbsRussia_mScan_Priv::FuncCheckLockStatus(Nat32 Cookie)
{
	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);
	
	TraceNotice (m, "Freq %d Sym %d  \n",LockedFreq, SymbolRate);
	if ((RetVal == err_Ok) && (LockStatus == 0))
	{
		mNoStationFound();
	}
	else
	{
		mStationFound();
	}
}

void CHsvDvbsRussia_mScan_Priv::FuncStartTuning (Nat32 param1)
{
	TraceNotice(m,"RUSSIA: %s:%d\n",__FUNCTION__, __LINE__);
	int		ModlnStd = -1, IqMode = -1, Cookie = 0;
	int		SymbolRate = 0,ModlnType = -1;
	HsvNITSatelliteDS CurrSDSD;
	int 	RollOff = -1, FEC = -1, Pilots = -1; 

	if(CURRENT_SCAN_MODE == Homing)
	{
		if(mInstStatus.HomingMuxIndex < NO_OF_HOMING_MUX)
		{
		SET_INS_STATE(StTunerWait);
		
		TraceNotice(m,"lnbNumber %d LnbType %d Frequency %d SymbolRate %d Polarization %d Cookie %d ModlnStd %d ModlnType %d IqMode %d",mInstStatus.LnbNumber, mInstStatus.LnbType, (RussiaDigitalPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
								SymbolRate, RussiaDigitalPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, ModlnStd, ModlnType, IqMode);
								
		satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (RussiaDigitalPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
								SymbolRate, RussiaDigitalPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);
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

			TraceNotice  (m, "SvcScan: SDSD Freq %d Pol %d ", (int)CurrSDSD.Frequency, (int)CurrSDSD.Polarization);

			SET_INS_STATE(StTunerWait);
			satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (CurrSDSD.Frequency), \
										CurrSDSD.SymbolRate, CurrSDSD.Polarization,Cookie, ModlnStd, CurrSDSD.ModulationType, IqMode, RollOff, FEC, Pilots);
		}
		else
		{
			TraceNotice (m, " Package only scan completed on Lnb %d \n",mInstStatus.LnbNumber);
			SET_INS_STATE (StIdle);
			SET_SCAN_MODE(Invalid);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
			iinsN_OnEvent(iinsN_EventPkgInstallEnd, 0);
		}
	}
									
	UNUSED (param1);
}

void CHsvDvbsRussia_mScan_Priv::FuncStartServiceScan (Nat32 param1)
{
	/* Getting the LNB Details */
	mGetLnbDetails(RUSSIA_SAT_ID);
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


void CHsvDvbsRussia_mScan_Priv::mGetLnbDetails(int SatId)
{
	int i;
	HsvPgdatDigSatInfoData SatDetails;
	for(i=0; i < MAX_NUM_LNBS_SUPPORTED; i++)
	{
		pgdb_Initialise(SAT_INFO_TABLE, (Address) &SatDetails);
		SatDetails.LnbNumber = i;
		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails) != TRUE)
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n",i);
		}

		if(SatDetails.SatelliteId == SatId)
		{
			mInstStatus.LnbNumber = i;
			mInstStatus.LnbType = SatDetails.LnbType;
			break;
		}
	}
}


void CHsvDvbsRussia_mScan_Priv::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
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
		ptc->CodeRateLow = 0;	/* Testing shows that Puncture Rate is similar to FEC value */
		ptc->IqMode = IqMode;
		ptc->ChannelBandwidth = Bandwidth;
		ptc->Polarization = Polarization;
	}
}



/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx		isvcscanctrlN */

void CHsvDvbsRussia_mScan_Priv::isvcscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceNotice (m, "EventId 0x%x Value 0x%x ", EventId ,Value);
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
		TraceNotice(m,"ctrlN_NIT available");	
			if(CURRENT_SCAN_MODE == Homing)
			{
				pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
			}
			else if(CURRENT_SCAN_MODE == Fallback)
			{
				if ((Value & isvcscanctrlN_SDT))
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

/* provides IPlfApiDvbsNotify	isvcscanplfApidvbsN */

void CHsvDvbsRussia_mScan_Priv::plfApidvbsN_OnLockChanged( Bool LockState)
{
	/* TODO: Verify Cookie check is needed here or not */
	/* Notifiation Handler for DVB-S platform FE */	
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		isvcscandata	*/


void CHsvDvbsRussia_mScan_Priv::isvcscandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
	int	TransponderFreq;
	HsvNITSatelliteDS CurrSDSD;

	ptc->LnbNumber = mInstStatus.LnbNumber;
	ptc->LnbType = mInstStatus.LnbType;

	mGetCurrentTunerParams (ptc);

	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);

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


int CHsvDvbsRussia_mScan_Priv::isvcscandata_GetInstallationVersion(void)
{
	/* ANEESH: TODO: Have to implement this function when update installation comes */
	return 0;
}



void CHsvDvbsRussia_mScan_Priv::isvcscandata_SyncComplete(void)
{
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsRussia_mScan_Priv::isvcscanpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbrussia_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
	isortpow_Init ();
}

void CHsvDvbsRussia_mScan_Priv::isvcscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;
	
	/* Initializing the other modules. TODO: Confirm :this is not to be called during StartInstallation */
	idataacq_Initialise (0);
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
}

void CHsvDvbsRussia_mScan_Priv::isvcscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsRussia_mScan_Priv::isvcscan_GetCurrentInstallationState (int *mode, int *state)
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
FResult CHsvDvbsRussia_mScan_Priv::isvcscan_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult			RetVal = err_BadParameter;
	if (TURNED_ON)
	{
		TraceDebug (m, "SERVICE Scan Already Turned On \n");
		if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			if (SCAN_NOT_INPROGESS)
			{
				TraceDebug (m, " No Service Scan in progress.. Initiating \n");
				SET_INS_MODE(Mode);
				mInstStatus.IntallationState = insstate_InstallationStateInProgress;
				pmp_PmpSend(mPump, EvStart, (Nat32)NULL);
			}
			RetVal = err_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsRussia_mScan_Priv::isvcscan_WriteBarkerMuxData(void)
{
	idataacq_StoreBarkerMuxDetails();
	return TRUE;

}
FResult CHsvDvbsRussia_mScan_Priv::isvcscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	return RetVal;
}
int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;
	
	RetVal = idataacq_GetNumberOfRadioChannelsFound ();
	
	return RetVal;
}

int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsRemoved();		
}
int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsRussia_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

void CHsvDvbsRussia_mScan_Priv::isvcscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	SiValues->Pid = INVALID_PID;

	if(Homing == CURRENT_SCAN_MODE)
	{
		SiValues->TableId = SDT_OTHER_TABLE_ID;
		SiValues->BouquetId = RUSSIA_BOUQUET_ID;

	}
	else
	{
		SiValues->TableId = 0;
		SiValues->BouquetId = INVALID_BOUQUET_ID;
	
	}
}

void CHsvDvbsRussia_mScan_Priv::idataacqN_OnDataAquired(Bool Result)
{
	pmp_PmpSend(mPump, EvDataAcquired, (Nat32)Result);
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);

}


int CHsvDvbsRussia_mScan_Priv::isvcscan_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

FResult CHsvDvbsRussia_mScan_Priv::isvcscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsRussia_mScan_Priv::isvcscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsRussia_mScan_Priv::isvcscan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsRussia_mScan_Priv::isvcscan_GetTricolorRegionNames (Nat16 **regionNames, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}


Bool CHsvDvbsRussia_mScan_Priv::isvcscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsRussia_mScan_Priv::isvcscan_StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsRussia_mScan_Priv::isvcscan_GetScanProgressStatus (int Mode)
{
	return 0;
}
			
void CHsvDvbsRussia_mScan_Priv::plfApidvbsN_OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsRussia_mScan_Priv::isvcscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}
			

void CHsvDvbsRussia_mScan_Priv::isvcscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}

