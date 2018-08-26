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
 *	C Source:		hsvdvbsins_msrt.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	 aneeshc %
 *	%date_created:	 Fri Apr 19 16:07:08 2013 %
 *
**********************************************************************/

/****************************************************************************
 * Local include files
 ****************************************************************************/


#include "_hsvdvbsgeneric_mSrt.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsgeneric_mSrt")
/****************************************************************************
 * Macros and types
 ****************************************************************************/


#ifndef __cplusplus

#else

#endif






















/****************************************************************************
 * Static variables
 ****************************************************************************/


const char CHsvDvbsGeneric_mSrt_Priv::SrtEventNames[EvMax+1][32] = 
{
	"EvStart",
	"EvStop",
	"EvStationFound",
	"EvStationNotFound",
	"EvDataAvailable",
	"EvDataNotAvailable",
	"EvStartTuning",
	"EvCheckLock",
	"EvPMTCollected",
	"EvMax"
};


int CHsvDvbsGeneric_mSrt_Priv::s__mConstModuleLifeCycle = 0;

InsInstance CHsvDvbsGeneric_mSrt_Priv::s__mInstStatus;

Pump CHsvDvbsGeneric_mSrt_Priv::s__mPump;

Bool CHsvDvbsGeneric_mSrt_Priv::s__mPlayStarted = FALSE;

HsvSDTService CHsvDvbsGeneric_mSrt_Priv::s__mSvcForPlayBack;

Pump CHsvDvbsGeneric_mSrt_Priv::s__NoDataPump;

int CHsvDvbsGeneric_mSrt_Priv::s__mCurrentSessionCookie = 0;













FunctionNat32 CHsvDvbsGeneric_mSrt_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
/*							 StIdle,					    StStart,					StTunerWait,				StDemuxWait		            StPMTWait                   */
/* EvStart */				{FNADDR(FuncStartManualScan),	NULL,						NULL,						NULL,				        NULL                        },
/* EvStop */				{NULL,						    FNADDR(FuncStopManualScan),	FNADDR(FuncStopManualScan),	FNADDR(FuncStopManualScan),	FNADDR(FuncStopManualScan)  },
/* EvStationFound */		{NULL,						    NULL,						FNADDR(FuncStationFound),	NULL,				        NULL                        },
/* EvStationNotFound */		{NULL,						    NULL,						FNADDR(FuncNoStationFound),	NULL,				        NULL                        },
/* EvDataAvailable */		{NULL,						    NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL                        },
/* EvDataNotAvailable */	{NULL,						    NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL	                    },
/* EvStartTuning */			{NULL,						    FNADDR(FuncStartTuning),	NULL,						NULL,				        NULL                        },
/* EvCheckLock */			{NULL,						    NULL,						FNADDR(FuncCheckLock),		NULL,				        NULL                        },
/* EvPMTCollected */		{NULL,						    NULL,						NULL,		                NULL,				        FNADDR(FuncPMTCollected)    }
};


/****************************************************************************
 * Static functions
 ****************************************************************************/


void CHsvDvbsGeneric_mSrt_Priv::PumpHandler(int event, Nat32 param)
{	
	TraceNotice (m,"%s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SrtEventNames[event],  mInstStatus.State);
	if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
	{
		TraceNotice (m,"%s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SrtEventNames[event],  mInstStatus.State);
		if(EventActionMatrix[event][mInstStatus.State] != NULL)
		{
			TraceNotice (m,"%s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,SrtEventNames[event],  mInstStatus.State);
			FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
		}
	}
}

void CHsvDvbsGeneric_mSrt_Priv::NoPMTHandler(int event, Nat32 param)
{	
	if((StPMTWait == mInstStatus.State) && (mCurrentSessionCookie == param) && (EvNoPMT == event))
	{
		TraceNotice(m,"NoPMTHandler: Set to Idle");
		SET_INS_STATE(StIdle);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
	}

}


void CHsvDvbsGeneric_mSrt_Priv::SetChannelDecoder (void)
{
}

void CHsvDvbsGeneric_mSrt_Priv::FuncStartManualScan (Nat32 param1)
{
	HsvLnbSettings	LnbSettings;

	/* Stop if playback is already in going on */
	mctl_Stop(HsvMain);

	idataacq_Initialise (mInstStatus.UserInstallLnb);

	/* Save the current LNB Settings to local data */
	idvbset_GetLnbSettings (&LnbSettings);
	mInstStatus.LnbType = LnbSettings.LnbSettings[mInstStatus.UserInstallLnb].LnbType;
	TraceNotice (m,"%s %d mInstStatus.LnbType %d\n", __FUNCTION__, __LINE__, mInstStatus.LnbType);

	SET_INS_STATE (StStart);

	/* Stop the SDM if already in collection state */
	if (ctrl_GetMode(mInstStatus.CurrentDemux) != ctrl_Idle)
	{
		TraceNotice (m,"%s %d mInstStatus.LnbType %d\n", __FUNCTION__, __LINE__, mInstStatus.LnbType);
		ctrl_StopCollection(mInstStatus.CurrentDemux);
	}
	else
	{
		TraceNotice (m,"%s %d mInstStatus.LnbType %d\n", __FUNCTION__, __LINE__, mInstStatus.LnbType);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncStopManualScan (Nat32 param1)
{
	SET_INS_STATE(StIdle);

	/* Stop currentSearch and stop the SDM */
	if (ctrl_GetMode(mInstStatus.CurrentDemux) != ctrl_Idle)
	{
		ctrl_StopCollection(mInstStatus.CurrentDemux);
	}
    if (mPlayStarted)
    {
        mctl_Stop(HsvMain);
        mPlayStarted = FALSE;
        memset((Address)(&mSvcForPlayBack), 0, sizeof(mSvcForPlayBack));
    }
	iinsN_OnEvent(iinsN_EventInsStopped,mInstStatus.UserInstallLnb);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	SET_INS_MODE(insstate_InstallationNone);
	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncStartTuning (Nat32 param1)
{
	FResult		RetVal = err_Ok;
	/* Start the tuning for the requested Frequency, polarization and symbol rate */
	SetChannelDecoder ();
	TraceNotice (m,"%s %d %d %d\n", __FUNCTION__, __LINE__, mInstStatus.LnbType, (int)mInstStatus.UserInstallLnb);

	RetVal = satfeapi_SatelliteFrontEndTune (mInstStatus.UserInstallLnb, mInstStatus.LnbType, mInstStatus.UserInstallFreq, mInstStatus.UserInstallSymRate,\
											mInstStatus.UserInstallPolaraization, 0, -1, -1, -1, -1, -1, -1);
	if (RetVal == err_Ok)
	{
		TraceNotice(m ,"%s %d %d %d %d \n", __FUNCTION__, __LINE__, mInstStatus.LnbType, (int)mInstStatus.UserInstallLnb, (int)mInstStatus.UserInstallFreq);
		SET_INS_STATE(StTunerWait);
	}
	else
	{
		/* Inform InsFailed to ceapps */
		iinsN_OnEvent(iinsN_EventChannelNotFound,mInstStatus.UserInstallLnb);
	}

	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncStationFound (Nat32 param1)
{
	/* start signal strength measurement */
	TraceNotice (m,"%s %d %d %d\n", __FUNCTION__, __LINE__, mInstStatus.LnbType, (int)mInstStatus.UserInstallLnb);

	/* Start the SDM module. TODO: Check with Pavan: whether the mode should be Minimal */
	ctrl_StartCollection(mInstStatus.CurrentDemux, ctrl_NormalPlusPmt);
	SET_INS_STATE(StDemuxWait);
	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncNoStationFound (Nat32 param1)
{
	SET_INS_STATE(StIdle);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	iinsN_OnEvent(iinsN_EventChannelNotFound,mInstStatus.UserInstallLnb);
	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncDataAvailable (Nat32 param1)
{
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
    int index = 0;
    int loopCount = 0;
    int numSvcs = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));

    TraceNotice (m,"%s() : numSvcs %d\n", __FUNCTION__, numSvcs);                        
            
    for (loopCount = 0; loopCount < numSvcs; ++loopCount)
    {
        if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), loopCount, &service))
        {
            TraceNotice (m,"%s() : loopCount %d, Svc <%d %d %d>, ServiceType 0x%x, Free_CA_Mode %d\n", __FUNCTION__, loopCount, service.Original_NetworkId, service.Tsid, service.ServiceId, service.ServiceType, service.Free_CA_Mode);                        
            if ((IS_TV_SERVICE(service.ServiceType) && (FALSE == service.Free_CA_Mode)))
            {                                
                break;
            }
        }
    }
    // If loopCount == numSvcs, no TV service found in Actual TS list; set the first Radio service
    // as current pgm; else first TV service will be available at index = loopCount
    index = ((numSvcs == loopCount) ? 0 : loopCount);

    TraceNotice (m,"%s() : Index %d\n", __FUNCTION__, index);                        
    
    if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), index, &mSvcForPlayBack))
    {
        TraceNotice (m,"%s() : %d\n", __FUNCTION__, __LINE__);
        if (mPlayService (mSvcForPlayBack.ServiceId))
        {
            TraceNotice (m,"%s() : %d\n", __FUNCTION__, __LINE__);
			
			SET_INS_STATE(StIdle);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			
            /* ntf to apps, to show "store" button */
	        iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.UserInstallLnb);
        }
        else
        {
            SET_INS_STATE(StPMTWait);
			pmp_PmpSendAfter(NoDataPump,EvNoPMT,mCurrentSessionCookie,10000);
			iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.UserInstallLnb);
    	    TraceNotice (m,"%s() : Wait for PMT - Pgm %d\n", __FUNCTION__, mSvcForPlayBack.ServiceId);
        }
    }    

	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncPMTCollected (Nat32 param1)
{
	SET_INS_STATE(StIdle);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;

	// Starting the playback of the first service found				
	if(!mPlayStarted)
	{
		TraceNotice (m,"Starting the playback \n");
		mPlayService(param1);
	}
	
	/* ntf to apps, to show "store" button */
	iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.UserInstallLnb);

    UNUSED(param1);
}


void CHsvDvbsGeneric_mSrt_Priv::FuncNoDataAvailable (Nat32 param1)
{
	
	//idataacq_AcquireDataOnTimeout ();
	SET_INS_STATE(StIdle);
	mInstStatus.IntallationState = insstate_InstallationStateIdle;
	iinsN_OnEvent(iinsN_EventChannelNotFound,mInstStatus.UserInstallLnb);

	if(ctrl_GetMode(mInstStatus.CurrentDemux) != ctrl_Idle)
	{
		ctrl_StopCollection(mInstStatus.CurrentDemux);
	}
	UNUSED (param1);
}

void CHsvDvbsGeneric_mSrt_Priv::FuncCheckLock (Nat32 param1)
{
	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);
	if (RetVal == err_Ok)
	{
		if (LockStatus != 0)
		{
			//ROUNDOFF_TPFREQ(mInstStatus.UserInstallFreq,LockedFreq);			
			pmp_PmpSend(mPump, EvStationFound, (Nat32)NULL);
		}
		else
		{
			pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
		}
	}
	else
	{
		pmp_PmpSend(mPump, EvStationFound, (Nat32)NULL);
	}
}

Bool CHsvDvbsGeneric_mSrt_Priv::mPlayService(int serviceid)
{
    HsvSimplePMTPidInfo pidInfo;  
    HsvDestination dest = HsvMain;

    if(mPlayStarted == FALSE)
    {
        if (TRUE == strapi_GetByKey(dest, HSVSPID(PidInfo, mpeg, simplepmt), serviceid, HSVINVALIDKEY, HSVINVALIDKEY, (Address)(&pidInfo))) 
        { 
            TraceDebug(m,"Play Started on Service = %d\r\n", serviceid);
            mctl_Flush(dest);
            mctl_SetMedia(dest, mctl_Audio, pidInfo.AudioStreamType, pidInfo.AudioPid);  
            mctl_SetMedia(dest, mctl_Video, pidInfo.VideoStreamType, pidInfo.VideoPid);
            mctl_SetMedia(dest, mctl_Pcr, mctl_InvalidSelector, pidInfo.PcrPid);
            mctl_Play(dest);            
            mPlayStarted = TRUE;
        }
        else
        {
            TraceDebug(m,"%s(): Error... Failed to get AV pids for Service = 0x%x\n", __FUNCTION__, serviceid);
        }        
    }
    return mPlayStarted;
}

void CHsvDvbsGeneric_mSrt_Priv::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
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

void CHsvDvbsGeneric_mSrt_Priv::mCheckDuplicateTransponder (HsvInstallationPTC *ptc)
{
	int		Count, From, To;
	HsvPgdatDigTSData	TempTsData;
	
	TempTsData.LnbNumber = ptc->LnbNumber;
	if (pgdb_GetRange (PTC_TABLE, 1, (Address)&TempTsData, &From, &To))
	{
		for (Count = From; Count <= To; Count++)
		{
			if (TRUE == pgdb_GetByIndex (PTC_TABLE, Count ,(Address)&TempTsData))
			{
				if ((TempTsData.Polarization == ptc->Polarization) &&
					 (iutil_CheckFreqDuplicationwithRolFact(ptc->Frequency, TempTsData.Frequency, ptc->SymbolRate)))
				{
					/* Got duplicate transponder. now give this frequency to ptc and break */
					ptc->Frequency = TempTsData.Frequency;
					break;
				}
			}
		}
	}
}

Bool CHsvDvbsGeneric_mSrt_Priv::mIsLCNAcquistionSupported(void)
{
	Bool retval = FALSE;
	int PackageId = 0;
	
	PackageId = insstate_GetAttribute(UPDATE_MODE, insstate_AttributePackageId);
	TraceNotice (m, "%s PackageId %d\n", __FUNCTION__, PackageId);
	switch(PackageId)
	{
		case CANALDIGITAL_NORWAY_PACKAGE_ID:
		case CANALDIGITAL_SWEDEN_PACKAGE_ID:
		case CANALDIGITAL_FINLAND_PACKAGE_ID:
		case CANALDIGITAL_DENMARK_PACKAGE_ID:
			retval = TRUE;
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

/* provides IHsvSdmControlNotifyEx	isrtctrlN	*/

void CHsvDvbsGeneric_mSrt_Priv::isrtctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceNotice (m,"%s %d <%d %d %d>\n", __FUNCTION__, __LINE__, Dmx, EventId, Value);
	if (VALID_DEMUX(Dmx))
	{
		switch (EventId)
		{
		case	isrtctrlN_DataNotAvailable:
				if (strapi_GetSize (HsvMain, HSVSPID(Program, mpeg, simplepat)))
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
				else
				{
				pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
				}
			break;
		case	isrtctrlN_StoppedCollection:
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			break;
		
		case	isrtctrlN_OnlyPsiDataAvailable:
		case	isrtctrlN_SiDataAvailable:
			break;
		case	isrtctrlN_DataAvailable:
			//if(isigstr_GetSigStrengthMeasured() == TRUE)
			if (Value & isrtctrlN_SDT)			
			{
				if ((mIsLCNAcquistionSupported() == TRUE))
				{
					if (Value & isrtctrlN_NIT)
					{
						pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
					}
				}
				else
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
			}
			break;
		
			break;
		case	isrtctrlN_StartedCollection:
			break;
		default:
			break;
		}
	}
	UNUSED (Value);
}

/* provides IPlfApiDvbsNotify	isrtplfApidvbsN */

void CHsvDvbsGeneric_mSrt_Priv::isrtplfApidvbsN_OnLockChanged(Bool LockState)
{
	/* Thread seperation done */
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData	isrtdata	*/

void CHsvDvbsGeneric_mSrt_Priv::isrtdata_GetPtcInfo (HsvInstallationPTC *ptc)
{
	int	TransponderFreq;

	TraceNotice (m," Inside SRT..Lnb is %d \n", (int)mInstStatus.UserInstallLnb);
	ptc->LnbNumber = mInstStatus.UserInstallLnb;
	ptc->LnbType = mInstStatus.LnbType;			
	ptc->Polarization = mInstStatus.UserInstallPolaraization;	/* Frequency will be calculated directly from plfapi */

	mGetCurrentTunerParams (ptc);
	
	TransponderFreq = ptc->Frequency;
	/*ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);*/
	
	/* ANEESH: TODO:  Check for the frequency check here. */
	mCheckDuplicateTransponder (ptc);

	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
	mInstStatus.UserInstallFreq = ptc->Frequency;

	TraceNotice  (m, " Freq %d and BW : %d \n", TransponderFreq, ptc->ChannelBandwidth);

	ptc->QSignalStrength    =   isigstr_GetSignalStrength(isigstr_InsQsm);
	ptc->SSignalStrength    =   isigstr_GetSignalStrength(isigstr_InsSsm);

	/* TODO: Get SDSD from strapi if already collected */
	ptc->SDSDFrequency = 0;
	ptc->PlpId = 0;
    //ptc->ChannelInformation;	//Not needed
	ptc->HierarchyMode = HsvHierarchyNone;
    ptc->StreamPriority = HsvStreamPriorityHigh;
 
}

void CHsvDvbsGeneric_mSrt_Priv::isrtdata_SyncComplete(void)
{
	TraceNotice (m,"%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdbconst_Satellite);
	
	iinsN_OnEvent(iinsN_EventInsCompleted,mInstStatus.UserInstallLnb);
}

int CHsvDvbsGeneric_mSrt_Priv::isrtdata_GetInstallationVersion(void)
{
	return 0;
}



/* provides IHsvPower isrtpow */

void CHsvDvbsGeneric_mSrt_Priv::isrtpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbsins_srt" );
	NoDataPump = pmp_PmpCreateEx( pen_PumpEngine, NoPMTHandler, TRUE,"hsvdvbsins_srt_NoData");
	mConstModuleLifeCycle = ConstInitialized;
	SET_INS_STATE(StIdle);
	mPlayStarted = FALSE;
    memset((Address)(&mSvcForPlayBack), 0, sizeof(mSvcForPlayBack));
	TraceNotice (m," SRT Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
}

void CHsvDvbsGeneric_mSrt_Priv::isrtpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;
	mInstStatus.CurrentDemux = HsvDmxMain;
	mCurrentSessionCookie = 0;

	mInstStatus.UserInstallLnb = 0;
	mInstStatus.UserInstallFreq = 10700000;
	mInstStatus.UserInstallPolaraization = PolarisationVertical;
	mInstStatus.UserInstallsymRateMode = SymbolRateModeAuto;
	mInstStatus.UserInstallSymRate = 0;	

	/* Initializing the other modules. TODO: Confirm :this is not to be called during StartInstallation */
	idataacq_Initialise (0);
}

void CHsvDvbsGeneric_mSrt_Priv::isrtpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

/* provides IHsvSatelliteInstallation isrt */

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetCurrentInstallationState (int *mode, int *state)
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
FResult CHsvDvbsGeneric_mSrt_Priv::isrt_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult			RetVal = err_BadParameter;

	TraceNotice (m,"%s %d TURNED_ON %d <%d %d %d>\n", __FUNCTION__, __LINE__, TURNED_ON, Source, Lnb, Mode);
	if (TURNED_ON)
	{
		/* Currently supporting only service scan. Have to update VALID_MODE as features added */
		if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			if (SCAN_NOT_INPROGESS)
			{
				SET_INS_MODE(Mode);
				mPlayStarted = FALSE;
				mCurrentSessionCookie ++;
				SET_INS_STATE(StIdle);
				mInstStatus.IntallationState = insstate_InstallationStateInProgress;

				/* Clearing the temp tables */
				//pgdb_ClearTable (TEMP_CHANNEL_TABLE);
				/* Now copy the data from actual table to temp table */
				//pgdb_CopyChannelMapToTemp ();

				/* Now initialize the freq finder module to load the SDSDs obtained from pre-scan */
				pmp_PmpSend(mPump, EvStart, Lnb);
			}
			RetVal = err_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsGeneric_mSrt_Priv::isrt_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsFound();
}
int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberOfRadioChannelsFound ();
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}
	

FResult CHsvDvbsGeneric_mSrt_Priv::isrt_LoadManualInstallationDefaultValues (void)
{
	FResult	RetVal;
    int LnbNumber, Frequency, Polarization;
    Nat32 SymbolRate;
	HsvSource  Source;
	HsvChannel ChannelNo ;
	    
	pgsel_GetCurrentProgram(HsvMain,&Source,&ChannelNo);
	
    pgdat3_GetChannelDataInt(ChannelNo, pgdat3_IntLnbNumber, &LnbNumber);
    pgdat3_GetChannelDataInt(ChannelNo, pgdat3_IntPolarization, &Polarization);
    pgdat3_GetChannelDataNat32(ChannelNo, pgdat3_Nat32SymbolRate, &SymbolRate);
    RetVal = pgdat3_GetChannelDataInt(ChannelNo, pgdat3_IntFrequency, &Frequency);
                                                    
	if ((RetVal == err_Ok) )
	{
               
        
		mInstStatus.UserInstallLnb = LnbNumber;
		mInstStatus.UserInstallFreq = Frequency;
		mInstStatus.UserInstallSymRate = (mInstStatus.UserInstallsymRateMode == SymbolRateModeAuto)? 0: SymbolRate;
		mInstStatus.UserInstallPolaraization = Polarization;
	}

	return RetVal;
}
FResult CHsvDvbsGeneric_mSrt_Priv::isrt_StoreManualInstallationValues (void)
{
	FResult		RetVal = err_Ok;
	int 		TotalServices = 0;	
	
	
	/* User has opted to Store the services. So acquire the service data. Then call sort interface
		for creation of preset numbers */
	TotalServices = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));

	TraceNotice (m,"%s %d>TotalServices[%d]\n", __FUNCTION__, __LINE__,TotalServices);

	if (TotalServices)
	{
		idataacq_AcquireData (0);
		
	}	
	else
	{
		idataacq_AcquireDataOnTimeout ();
	}

	return RetVal;
}

void CHsvDvbsGeneric_mSrt_Priv::isrtAcqN_OnDataAquired  (Bool Result)
{
	
	ctrl_StopCollection(mInstStatus.CurrentDemux);
	iinsN_OnEvent(iinsN_EventInsCompleted,mInstStatus.UserInstallLnb);
	UNUSED(Result);
}

Bool CHsvDvbsGeneric_mSrt_Priv::isrt_SetManualInstallationAttributes (int AttributeId, int Value)
{
	Bool	RetVal = TRUE;
	switch (AttributeId)
	{
	case	insstate_ManualInstallLnb:
		mInstStatus.UserInstallLnb = Value;
		break;
	case	insstate_ManualInstallFreq:
		mInstStatus.UserInstallFreq = Value;
		break;
	case	insstate_ManualInstallPolaraization:
		mInstStatus.UserInstallPolaraization = Value;
		break;
	case	insstate_ManualInstallSymRate:
		mInstStatus.UserInstallSymRate = Value;
		break;
	case	insstate_ManualInstallSymRateMode:
		mInstStatus.UserInstallsymRateMode = Value;
        if (Value == SymbolRateModeAuto)
		{
			mInstStatus.UserInstallSymRate = 0;
		}

		break;
	default:
		RetVal = FALSE;
	}

	return RetVal;
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetAttribute(int Mode, int AttributeId)
{
	int			RetVal = 0, Frequency, SymbolRate, ModlnStd, ModlnType;
	int			CodeRate, PunctureRate, IQMode, LockState,CmdResult;

	switch (AttributeId)
	{
	case	insstate_ManualInstallLnb:
		RetVal = mInstStatus.UserInstallLnb;
		break;
	case	insstate_ManualInstallFreq:
		RetVal = mInstStatus.UserInstallFreq;
		break;
	case	insstate_ManualInstallPolaraization:
		RetVal = mInstStatus.UserInstallPolaraization;
		break;
	case	insstate_ManualInstallSymRate:
		RetVal = mInstStatus.UserInstallSymRate;
		break;
	case	insstate_ManualInstallSymRateMode:
		RetVal = mInstStatus.UserInstallsymRateMode;
		break;
	case	insstate_ManualInstallModulation:
		/* ANEESH: TODO: Export Modulation Type also in satfe interface */
		/*
			RetVal = plfapidvbs_GetParams ( WINDOWID, &Frequency, &SymbolRate, &ModlnStd, &ModlnType, 
									&CodeRate, &PunctureRate, &IQMode, &LockState, &CmdResult);
			if ((RetVal == err_Ok) && (CmdResult == plfapidvbs_CmdResultOK))
			{
				RetVal =  (LockState == plfapidvbs_LockStateNOLock) ? (-1) : ModlnType;
			}
			else
			{
				RetVal = -1;
			}
		*/
		break;
	default:
		RetVal = FALSE;
	}

	UNUSED (Mode);
	return RetVal;
}

FResult CHsvDvbsGeneric_mSrt_Priv::isrt_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsGeneric_mSrt_Priv::isrt_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsGeneric_mSrt_Priv::isrt_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
FResult CHsvDvbsGeneric_mSrt_Priv::isrt_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	TraceNotice(m,"Error!!! SetPostcode- call should not land here");
	return 0;
}

FResult CHsvDvbsGeneric_mSrt_Priv::isrt_WriteBarkerMuxData(void)
{
	return 0;
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberOfTvChannelsRemoved    (int Mode, int Lnb)
{
	return 0;
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetNumberofRadioChannelsRemoved (int Mode, int Lnb)
{
	return 0;
}

int CHsvDvbsGeneric_mSrt_Priv::isrt_GetScanProgressStatus (int Mode)	/* This will return the scan progress value */
{
	return 0;
}

void CHsvDvbsGeneric_mSrt_Priv::isrt_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
}

void CHsvDvbsGeneric_mSrt_Priv::isrtdata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}

void CHsvDvbsGeneric_mSrt_Priv::isrtplfApidvbsN_OnBlindScanEnd ()
{
}

void CHsvDvbsGeneric_mSrt_Priv::isrtstrapiN_OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3)
{
//    TraceNotice (m,"%s %d : %d %d\n", __FUNCTION__, __LINE__, spid, key1);
    switch(spid)
    {
        case HSVSPID(PidInfo, mpeg, simplepmt):
            {
                if (key1 == mSvcForPlayBack.ServiceId)
                {
                    pmp_PmpSendAfter(mPump, EvPMTCollected, key1, 100);
                }
            }
            break;

        default:
            break;
    }
    
    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbsGeneric_mSrt_Priv::isrtstrapiN_OnChanged (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED(eventid);
}

void CHsvDvbsGeneric_mSrt_Priv::isrtstrapiN_OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbsGeneric_mSrt_Priv::isrtstrapiN_OnCompleted (HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}

