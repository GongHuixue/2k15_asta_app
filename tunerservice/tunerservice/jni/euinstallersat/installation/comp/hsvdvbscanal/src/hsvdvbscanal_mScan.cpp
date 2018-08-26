/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *          %name: hsvdvbscanal_mScan.c %
 *       %version: TVG_11 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: shivam %
 */

#include "_hsvdvbscanal_mScan.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbscanal_mscan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/


#ifndef __cplusplus

#else

#endif





























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsCanal_mScan_Priv::SvcScanEventNames[EvMax+1][32] = 
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



int CHsvDvbsCanal_mScan_Priv::s__mConstModuleLifeCycle = 0;

InsInstance CHsvDvbsCanal_mScan_Priv::s__mInstStatus;

Pump CHsvDvbsCanal_mScan_Priv::s__mPump;


HomingMuxData CHsvDvbsCanal_mScan_Priv::s__CanalDigitalPackageDetails[NO_OF_HOMING_MUX] = {{11247, satfeapi_PolarisationVertical, CANAL_SAT_ID},
																	{10872, satfeapi_PolarisationVertical, CANAL_SAT_ID}};


















FunctionNat32 CHsvDvbsCanal_mScan_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
							/* StIdle,							StStart,					StTunerWait,				StDemuxWait,				StAcquireWait			*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),	NULL,						NULL,						NULL,						NULL				},
/* EvStop */				{  NULL,							FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)},
/* EvDataAvailable */		{  NULL,							NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL				},
/* EvDataNotAvailable */	{  NULL,							NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL				},
/* EvDataAcquired */		{  NULL,							NULL,   					NULL,						NULL,						FNADDR(FuncDataAquired)	},
/* EvStartTuning */			{  NULL,							FNADDR(FuncStartTuning),	NULL,						NULL,						NULL				},
/* EvCheckLock */			{  NULL,							NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL				}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsCanal_mScan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m,"CANAL DIGITAL: %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsCanal_mScan_Priv::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice(m,"CANAL DIGITAL: %s:%d\n",__FUNCTION__, __LINE__);
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



void CHsvDvbsCanal_mScan_Priv::mStationFound (void)
{
	TraceNotice(m,"CANAL DIGITAL: %s:%d\n",__FUNCTION__, __LINE__);

	SET_INS_STATE(StDemuxWait);
	ctrl_StartCollection(HsvDmxMain, ctrl_Minimal);
}

void CHsvDvbsCanal_mScan_Priv::mNoStationFound (void)
{
	TraceNotice(m,"CANAL DIGITAL: %s CURRENT_SCAN_MODE %d\n",__FUNCTION__, CURRENT_SCAN_MODE);
	if(CURRENT_SCAN_MODE == Homing)
	{
		/*Tune to next homing frequency*/		
		mInstStatus.HomingMuxIndex++;
	}
	else if(CURRENT_SCAN_MODE == Fallback)
	{
		/*Tune to next SDSD*/
		mInstStatus.CurrSdsdIndex++;
	}
	SET_INS_STATE (StStart);		
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);		
}


void CHsvDvbsCanal_mScan_Priv::FuncDataAvailable (Nat32 param1)
{
	int Mode;
	TraceNotice(m,"CANAL DIGITAL: %s CURRENT_SCAN_MODE %d\n",__FUNCTION__, CURRENT_SCAN_MODE);
	
	if( (CURRENT_SCAN_MODE == ManualFrequency) || (CURRENT_SCAN_MODE == Homing) )
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

void CHsvDvbsCanal_mScan_Priv::FuncNoDataAvailable (Nat32 param1)
{
	TraceNotice(m,"CANAL DIGITAL: %s CURRENT_SCAN_MODE %d\n",__FUNCTION__, CURRENT_SCAN_MODE);
	
	if(CURRENT_SCAN_MODE == Homing)
	{
		/*Tune to next homing frequency*/
		mInstStatus.HomingMuxIndex++;
	}
	else if(CURRENT_SCAN_MODE == Fallback)
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

void CHsvDvbsCanal_mScan_Priv::FuncDataAquired (Nat32 param1)
{
	Bool Result = (Bool)param1;
	TraceNotice(m,"CANAL DIGITAL: %s CURRENT_SCAN_MODE %d\n",__FUNCTION__, CURRENT_SCAN_MODE);

	if( (CURRENT_SCAN_MODE == Homing) || (CURRENT_SCAN_MODE == ManualFrequency) )
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
	
	/* To Update Channel count*/
	iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.LnbNumber);
	/*To Update the progress*/
	iinsN_OnEvent(iinsN_EventInsProgress, mInstStatus.LnbNumber);
}

void CHsvDvbsCanal_mScan_Priv::FuncCheckLockStatus(Nat32 Cookie)
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

void CHsvDvbsCanal_mScan_Priv::FuncStartTuning (Nat32 param1)
{
	TraceNotice(m,"CANAL DIGITAL: %s:%d\n",__FUNCTION__, __LINE__);
	int		ModlnStd = -1, IqMode = -1, Cookie = 0;
	int		SymbolRate = 0,ModlnType = -1, Frequency, Polarization;
	int 	RollOff = -1, FEC = -1, Pilots = -1; 	/*Params Used for Only SAT-IP*/
	HsvNITSatelliteDS CurrSDSD;

	if(CURRENT_SCAN_MODE == Homing)
	{
		if(mInstStatus.HomingMuxIndex < NO_OF_HOMING_MUX)
		{
			SET_INS_STATE(StTunerWait);
			satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (CanalDigitalPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
									SymbolRate, CanalDigitalPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);
		}
		else if(mManualFrequencyModeSupported())
		{
			TraceNotice(m, "%s SCAN_MODE ManualFrequency", __FUNCTION__);
			SET_SCAN_MODE(ManualFrequency);
			
			Frequency = insstate_GetAttribute(AUTO_MODE, IHsvSatelliteInstallation_AttributeFrequency); 	
			Polarization = insstate_GetAttribute(AUTO_MODE, IHsvSatelliteInstallation_AttributePolarization);
			SymbolRate = insstate_GetAttribute(AUTO_MODE, IHsvSatelliteInstallation_AttributeSymbolRate);
			
			TraceNotice(m, "%s with user entered attributes Frequency %d Polarization %d Lnb %d LnbType %d", __FUNCTION__, Frequency, Polarization, mInstStatus.LnbNumber, mInstStatus.LnbType);
			
			SET_INS_STATE(StTunerWait);
			
			satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, Frequency, \
										   SymbolRate, Polarization, Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);
		}
		else
		{
			SET_INS_STATE (StIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}

	}/*If manual frequency tuning also failed, then stop the installation*/
	else if(CURRENT_SCAN_MODE == ManualFrequency)
	{
		SET_INS_STATE (StIdle);
		SET_SCAN_MODE(Invalid);
		iinsN_OnEvent(iinsN_EventInsFailed, 0);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
		
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
										CurrSDSD.SymbolRate, CurrSDSD.Polarization,Cookie, CurrSDSD.ModulationSystem, CurrSDSD.ModulationType, CurrSDSD.FECInner, RollOff, FEC, Pilots);
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

void CHsvDvbsCanal_mScan_Priv::FuncStartServiceScan (Nat32 param1)
{
	/* Getting the LNB Details */
	mGetLnbDetails(CANAL_SAT_ID);
	mInstStatus.HomingMuxIndex = 0;
	mInstStatus.NumOfSDSD = 0;
	mInstStatus.CurrSdsdIndex = 0;

	TraceNotice(m, "%s SCAN_MODE Homing", __FUNCTION__);
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


void CHsvDvbsCanal_mScan_Priv::mGetLnbDetails(int SatId)
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


void CHsvDvbsCanal_mScan_Priv::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
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

Bool CHsvDvbsCanal_mScan_Priv::mManualFrequencyModeSupported(void)
{
	Bool retval = FALSE;
	int PackageId = 0;
	Nat32 Frequency;
	
	PackageId = insstate_GetAttribute(AUTO_MODE, insstate_AttributePackageId);
	TraceNotice (m, "%s PackageId %d\n", __FUNCTION__, PackageId);
	switch(PackageId)
	{
		case CANALDIGITAL_NORWAY_PACKAGE_ID:
		case CANALDIGITAL_SWEDEN_PACKAGE_ID:
		case CANALDIGITAL_FINLAND_PACKAGE_ID:
		case CANALDIGITAL_DENMARK_PACKAGE_ID:
			Frequency = insstate_GetAttribute(AUTO_MODE, IHsvSatelliteInstallation_AttributeFrequency);
			if(Frequency != 0)
			{
				TraceNotice(m , "%s user entered Frequency %ld", __FUNCTION__, Frequency);
				retval = TRUE;
			}
			else
			{
				TraceNotice(m , "%s user entered Frequency is 0 so continue with table scan", __FUNCTION__);
			}
			break;
		default:
			break;
	}
	
	TraceNotice (m, "%s retval %d\n", __FUNCTION__, retval);
	return retval;
}

/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx		isvcscanctrlN */

void CHsvDvbsCanal_mScan_Priv::isvcscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	Nat16				NetworkId;
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
			if( (CURRENT_SCAN_MODE == Homing) || (CURRENT_SCAN_MODE == ManualFrequency) )
			{
				if ((Value & isvcscanctrlN_NIT))
				{
					if (TRUE == strapi_GetByKey(HsvMain,HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, (void *)(&NetworkId)))
					{
						TraceNotice (m, "NetworkId from stream 0x%x Canal Digital networkid 0x%x", NetworkId, CANAL_NETWORK_ID);
						if ((NetworkId == CANAL_NETWORK_ID))
						{
							pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
						}
						else
						{
							pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
						}
					}
				}				
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

void CHsvDvbsCanal_mScan_Priv::plfApidvbsN_OnLockChanged( Bool LockState)
{
	/* TODO: Verify Cookie check is needed here or not */
	/* Notifiation Handler for DVB-S platform FE */	
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		isvcscandata	*/


void CHsvDvbsCanal_mScan_Priv::isvcscandata_GetPtcInfo (HsvInstallationPTC *ptc)
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
	ptc->ModulationType   = CurrSDSD.ModulationType;
	ptc->ModulationStd    = CurrSDSD.ModulationSystem;
	ptc->CodeRate   	  = CurrSDSD.FECInner;

 }


int CHsvDvbsCanal_mScan_Priv::isvcscandata_GetInstallationVersion(void)
{
	/* ANEESH: TODO: Have to implement this function when update installation comes */
	return 0;
}



void CHsvDvbsCanal_mScan_Priv::isvcscandata_SyncComplete(void)
{
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsCanal_mScan_Priv::isvcscanpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbcanal_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
	isortpow_Init ();
}

void CHsvDvbsCanal_mScan_Priv::isvcscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;
	
	/* Initializing the other modules. TODO: Confirm :this is not to be called during StartInstallation */
	idataacq_Initialise (0);
	iacqpow_TurnOn();
	isortpow_TurnOn ();
}

void CHsvDvbsCanal_mScan_Priv::isvcscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow_TurnOff();
	isortpow_TurnOff ();
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsCanal_mScan_Priv::isvcscan_GetCurrentInstallationState (int *mode, int *state)
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
FResult CHsvDvbsCanal_mScan_Priv::isvcscan_StartInstallation(int Source, int Lnb, int Mode)
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

FResult CHsvDvbsCanal_mScan_Priv::isvcscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	return RetVal;
}
int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;
	
	RetVal = idataacq_GetNumberOfRadioChannelsFound ();
	
	return RetVal;
}

int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsRemoved();		
}
int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsCanal_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}
FResult CHsvDvbsCanal_mScan_Priv::isvcscan_WriteBarkerMuxData(void)
{
	TraceNotice(m,"SHREESHA:isvcscan_WriteBarkerMuxData"); 
	idataacq_StoreBarkerMuxDetails();
	return 0;
}

void CHsvDvbsCanal_mScan_Priv::isvcscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	SiValues->Pid = INVALID_PID;
	SiValues->BouquetId = INVALID_BOUQUET_ID;
	/*Request for SDT other in Homing mode*/
	if( (CURRENT_SCAN_MODE == Homing) || (CURRENT_SCAN_MODE == ManualFrequency) )
	{
		SiValues->TableId = 0x46;
	}
	else
	{
		SiValues->TableId = 0;		
	}

	TraceNotice (m, "%s %d:table id: %d\n", __FUNCTION__, __LINE__, SiValues->TableId);

}

void CHsvDvbsCanal_mScan_Priv::idataacqN_OnDataAquired(Bool Result)
{
	pmp_PmpSend(mPump, EvDataAcquired, (Nat32)Result);
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);

}


int CHsvDvbsCanal_mScan_Priv::isvcscan_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

FResult CHsvDvbsCanal_mScan_Priv::isvcscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsCanal_mScan_Priv::isvcscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsCanal_mScan_Priv::isvcscan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsCanal_mScan_Priv::isvcscan_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
Bool CHsvDvbsCanal_mScan_Priv::isvcscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsCanal_mScan_Priv::isvcscan_StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsCanal_mScan_Priv::isvcscan_GetScanProgressStatus (int Mode)
{
	int RetVal = 0;
	if(mInstStatus.NumOfSDSD != 0)
	{
		RetVal = (int)(mInstStatus.CurrSdsdIndex * 100 )/ mInstStatus.NumOfSDSD;
	}
	return RetVal;
}
			
void CHsvDvbsCanal_mScan_Priv::plfApidvbsN_OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsCanal_mScan_Priv::isvcscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}
			
void CHsvDvbsCanal_mScan_Priv::isvcscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}
