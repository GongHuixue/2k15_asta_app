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
 *          %name: hsvdvbsm7_mScan.c %
 *       %version: TVG_R3EXT_16 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: shreeshav %
 */

#include "_hsvdvbsm7_mScan.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsm7_mscan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#else

#endif



































/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsM7_mScan_Priv::SvcScanEventNames[EvMax+1][32] = 
{
	"EvStart",
	"EvStop",
	"EvStationFound",
	"EvStationNotFound",
	"EvDataAvailable",
	"EvDataNotAvailable",
	"EvDataAcquired",
	"EvStartTuning",
	"EvCheckLock",
	"EvMax"
};


const HomingMuxData CHsvDvbsM7_mScan_Priv::Astra1HomingFrequencyDetails = { 12515, satfeapi_PolarisationHorizontal,ASTRA_19_2_E };


const HomingMuxData CHsvDvbsM7_mScan_Priv::Astra3HomingFrequencyDetails = { 12070, satfeapi_PolarisationHorizontal,ASTRA_23_5_E };

const HomingMuxData CHsvDvbsM7_mScan_Priv::EutelSatHomingFrequencyDetails = { 12073, satfeapi_PolarisationVertical,EUTELSAT_9_A};

const SatData CHsvDvbsM7_mScan_Priv::M7SatOrder1[MAX_NUM_LNBS_SUPPORTED] = {{ASTRA_19_2_E,FALSE},{ASTRA_23_5_E,FALSE},{ASTRA_28_2_E,FALSE},{HOTBIRD_13_0_E,FALSE}};

const SatData CHsvDvbsM7_mScan_Priv::M7SatOrder2[MAX_NUM_LNBS_SUPPORTED] = {{ASTRA_19_2_E,FALSE},{ASTRA_23_5_E,FALSE},{EUTELSAT_9_A,FALSE},{HOTBIRD_13_0_E,FALSE}};

const SatData CHsvDvbsM7_mScan_Priv::M7SatOrder3[MAX_NUM_LNBS_SUPPORTED] = {{HOTBIRD_13_0_E,FALSE},{ASTRA_19_2_E,FALSE},{ASTRA_23_5_E,FALSE},{ASTRA_28_2_E,FALSE}};

const SatData CHsvDvbsM7_mScan_Priv::M7SatOrder4[MAX_NUM_LNBS_SUPPORTED] = {{EUTELSAT_9_A,FALSE},{HOTBIRD_13_0_E,FALSE},{ASTRA_19_2_E,FALSE},{ASTRA_23_5_E,FALSE}};


int CHsvDvbsM7_mScan_Priv::s__mConstModuleLifeCycle = 0;

InsInstance CHsvDvbsM7_mScan_Priv::s__mInstStatus;

Pump CHsvDvbsM7_mScan_Priv::s__mPump;

PackageDetails CHsvDvbsM7_mScan_Priv::s__M7PackageDetails[NO_OF_PACKAGES_SUPPORTED] = {
	{CANALDIGITAAL_SD_BOUQUET_ID, CANALDIGITAAL_SD_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder1},
	{CANALDIGITAAL_HD_BOUQUET_ID, CANALDIGITAAL_HD_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder1},
	{TVVLAANDEREN_SD_BOUQUET_ID, TVVLAANDEREN_SD_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder1},
	{TVVLAANDEREN_HD_BOUQUET_ID, TVVLAANDEREN_HD_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder1},
	{TELESAT_BEL_BOUQUET_ID, TELESAT_BEL_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder3},
	{TELESAT_LUX_BOUQUET_ID, TELESAT_LUX_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder3},
	{AUSRTIA_BOUQUET_ID, AUSTRIA_PID, 2, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,NULL}, M7SatOrder1},
	{CZECH_REPUBLIC_BOUQUET_ID, CZECH_REPUBLIC_PID, 1, {&Astra3HomingFrequencyDetails,NULL,NULL}, M7SatOrder2},
	{SLOVAK_REPUBLIC_BOUQUET_ID, SLOVAK_REPUBLIC_PID, 1, {&Astra3HomingFrequencyDetails,NULL,NULL}, M7SatOrder2},
	{AUSTRIASAT_MAGYA_PACKAGE_ID, AUSTRIASAT_MAGYA_PID, 3, {&Astra3HomingFrequencyDetails,&Astra1HomingFrequencyDetails,&EutelSatHomingFrequencyDetails}, M7SatOrder4}};

/*Frequencies to locate Astra Ref NIT*/
HomingMuxData CHsvDvbsM7_mScan_Priv::s__AstraRefFrequencyDetails[NO_OF_ASTRA_REF_FREQ] = {
	{ 12168, satfeapi_PolarisationVertical,ASTRA_23_5_E},
	{ 12070, satfeapi_PolarisationHorizontal,ASTRA_23_5_E},
	{ 11739, satfeapi_PolarisationVertical,ASTRA_23_5_E},
	{ 12109, satfeapi_PolarisationHorizontal,ASTRA_23_5_E},
	{ 12525, satfeapi_PolarisationVertical,ASTRA_23_5_E},
	{ 12603, satfeapi_PolarisationHorizontal,ASTRA_19_2_E},
	{ 12551, satfeapi_PolarisationVertical,ASTRA_19_2_E},
	{ 11302, satfeapi_PolarisationHorizontal,ASTRA_19_2_E},
	{ 12515, satfeapi_PolarisationHorizontal,ASTRA_19_2_E },
	{ 11856, satfeapi_PolarisationVertical,ASTRA_19_2_E }};


UsrPackageDetails CHsvDvbsM7_mScan_Priv::s__UserPackagedetails;











//static void SetChannelDecoder (void);


FunctionNat32 CHsvDvbsM7_mScan_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
							   /* StIdle,					StStart,					StTunerWait,				StDemuxWait,				StAcquireWait,					StDemuxWaitforM7Data*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL,						NULL,							NULL},
/* EvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),	FNADDR(FuncStopServiceScan)},
/* EvStationFound */		{  NULL,						NULL,						FNADDR(FuncStationFound),	NULL,						NULL,							NULL},
/* EvStationNotFound */		{  NULL,						NULL,               		FNADDR(FuncNoStationFound),	NULL,						NULL,							NULL},
/* EvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL,							FNADDR(FuncM7DataAvailable)},
/* EvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL,							FNADDR(FuncNoM7DataAvailable)},
/* EvDataAcquired */		{  NULL,						NULL,   					NULL,						NULL,						FNADDR(FuncDataAquired),		NULL},
/* EvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL,						NULL,							NULL},
/* EvCheckLock */			{  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL,							NULL}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsM7_mScan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	TraceNotice (m, "SvcScan: %s %d event %d [%s] State %d ", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
	if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
	{
		if(EventActionMatrix[event][mInstStatus.State] != NULL)
		{
			TraceNotice (m, "SvcScan: %s %d event %d [%s] State %d ", __FUNCTION__, __LINE__, event,SvcScanEventNames[event],  mInstStatus.State);
			FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
		}
	}
}

void CHsvDvbsM7_mScan_Priv::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	SET_INS_STATE(StIdle);

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



void CHsvDvbsM7_mScan_Priv::FuncStationFound (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);

	if((mInstStatus.ScanMode == Fallback) && (mInstStatus.RefM7HomingDetailsAvaialble == FALSE))
	{
		SET_INS_STATE(StDemuxWait);
		ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
	}
	else if((mInstStatus.ScanMode != Invalid))
	{
		SET_INS_STATE(StDemuxWaitforM7Data);
		ctrl_StartCollection(HsvDmxMain, ctrl_M7Minimal);
	}
	UNUSED (param1);
}

void CHsvDvbsM7_mScan_Priv::FuncNoStationFound (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	/*Tune to next Homing frequency*/
	if((mInstStatus.RefNITDetailsAvailable == FALSE) && (SetNextHomingMuxDetails(FALSE) == TRUE))
	{
		SET_INS_STATE (StStart);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL); 	
	}/*This is the case when tuning is failed with one of the Linkgedescriptor SDSDs, tune to next Linkagedescriptor SDSD*/
	else if((mInstStatus.ScanMode == Fallback) &&
		((mInstStatus.RefNITDetailsAvailable == TRUE) && (mInstStatus.RefM7HomingDetailsAvaialble == FALSE) && (SetNextNITRefDetails() == TRUE)))
	{
		SET_INS_STATE (StStart);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL); 			
	}/*TODO: if tuning to RefM7Homingmux is failed then tune to next mux on next satellite*/
/*	else if((mInstStatus.ScanMode == Fallback) && (mInstStatus.RefM7HomingDetailsAvaialble == TRUE))
	{
	}*/
	else
	{
		TraceErr  (m, "%d: Installation Failed [%d]",__LINE__,mInstStatus.RefNITDetailsAvailable);
		SET_INS_STATE (StIdle);
		iinsN_OnEvent(iinsN_EventInsFailed, 0);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
		SET_SCAN_MODE(Invalid);
	}

	UNUSED (param1);
}


void CHsvDvbsM7_mScan_Priv::FuncDataAvailable (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	
	if(mInstStatus.RefNITDetailsAvailable == FALSE)
	{
		if(mStoreRefNITDetails() == TRUE)
		{
			mInstStatus.RefNITDetailsAvailable = TRUE;

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
			TraceNotice(m,"%s: %d: mStoreRefNITDetails FAILED",__FUNCTION__,__LINE__);
			SET_INS_STATE (StIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}
	}
	else if(mInstStatus.RefM7HomingDetailsAvaialble == FALSE)
	{
		if(mStoreRefM7HomingDetails() == TRUE)
		{
			mInstStatus.RefM7HomingDetailsAvaialble = TRUE;
		
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
			TraceNotice(m,"%s: %d: mStoreRefM7HomingDetails FAILED",__FUNCTION__,__LINE__);
			SET_INS_STATE (StIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}
	}
	else
	{
		TraceNotice(m,"%s: %d",__FUNCTION__,__LINE__);
	}
	UNUSED (param1);
}

void CHsvDvbsM7_mScan_Priv::FuncM7DataAvailable (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);

	/*CR: TF515PHIALLMTK02-77*/
	if(IS_SERVICE_SCAN)
	{
		mSetLNBConfiguration();
	}
	
	idataacq_Initialise (0);
	/*Lnb number is ignored in mAcq*/
	idataacq_AcquireData(0);
	SET_INS_STATE(StAcquireWait);

	UNUSED (param1);
}


void CHsvDvbsM7_mScan_Priv::FuncNoDataAvailable (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);

	/*If RefNIT not available, go to next Homing mux*/
	if((mInstStatus.RefNITDetailsAvailable == FALSE) && (SetNextHomingMuxDetails(FALSE) == TRUE))
	{
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
		TraceErr  (m, "%d:  Installation Failed [%d]",__LINE__,mInstStatus.RefNITDetailsAvailable);
		SET_INS_STATE (StIdle);
		iinsN_OnEvent(iinsN_EventInsFailed,0);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
		
		if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
		{
			ctrl_StopCollection(HsvDmxMain);
		}
	}

	UNUSED (param1);
}

void CHsvDvbsM7_mScan_Priv::FuncNoM7DataAvailable (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);

	/*If FST/FNT are not available in fallbackmode go to next homing frequency from next satellite*/
	Bool NextSatellite = (mInstStatus.ScanMode == Homing) ? FALSE : TRUE;
	mInstStatus.RefNITDetailsAvailable = FALSE;
	mInstStatus.RefM7HomingDetailsAvaialble = FALSE;
	if(SetNextHomingMuxDetails(NextSatellite) == TRUE)
	{
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
		TraceErr  (m, "%d:  Installation Failed [%d]",__LINE__,mInstStatus.RefNITDetailsAvailable);
		SET_INS_STATE (StIdle);
		iinsN_OnEvent(iinsN_EventInsFailed,0);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
		
		if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
		{
			ctrl_StopCollection(HsvDmxMain);
		}
	}

	UNUSED (param1);
}


void CHsvDvbsM7_mScan_Priv::FuncDataAquired (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	SET_INS_STATE (StIdle);

	TraceNotice (m, " Package only scan completed on Lnb %d ",mInstStatus.Lnb);
	
	SET_INS_MODE(insstate_InstallationNone);
	iinsN_OnEvent(iinsN_EventPkgInstallEnd, 0);
	if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}

	/*Reset M7Installed LNBs to LNBInstalled*/
	if(IS_SERVICE_SCAN){
		ResetM7installedLNBs();
	}
	
	UNUSED (param1);
}

void CHsvDvbsM7_mScan_Priv::FuncCheckLockStatus(Nat32 Cookie)
{
	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);
	
	TraceNotice (m, "Freq %d Sym %d  ",LockedFreq, SymbolRate);
	if (RetVal == err_Ok)
	{
		if (LockStatus != 0)
		{
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

void CHsvDvbsM7_mScan_Priv::FuncStartTuning (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	int		SymbolRate = 0, ModlnStd = -1, ModlnType = -1, IqMode = -1;
	int 	RollOff = -1, FEC = -1, Pilots = -1; 

	TraceNotice  (m, "FuncStartTuning: Freq %d Pol %d ", (int)mInstStatus.Frequency, \
	(int)mInstStatus.Polarization);

	/* Have to do a direct tuning here */
	SET_INS_STATE(StTunerWait);
	satfeapi_SatelliteFrontEndTune(mInstStatus.Lnb, mInstStatus.LnbType, (mInstStatus.Frequency), \
								SymbolRate, mInstStatus.Polarization,mInstStatus.Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);
	UNUSED (param1);
}

void CHsvDvbsM7_mScan_Priv::FuncStartServiceScan (Nat32 param1)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	HsvPgdatDigSatInfoData	SatInfo;
	int i = MAX_NUM_LNBS_SUPPORTED;
	FResult		RetVal = err_NotSupported;

	/* Set the User selected package details */
	RetVal = mSetUserPackageDetails();

	if((RetVal == err_Ok) && (SetNextHomingMuxDetails(FALSE) == TRUE))
	{
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
	}
	else
	{
		TraceErr (m, "No Valid Homing mux found");
		SET_INS_STATE (StIdle);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
		iinsN_OnEvent(iinsN_EventInsFailed,0);
		/*Notify instllation failed/completed*/
	}
	UNUSED (param1);
}

/* M7 CR Changes*/

Bool CHsvDvbsM7_mScan_Priv::SetNextNITRefDetails()
{
	mInstStatus.CurrentRefNITDataIndex ++;
	TraceNotice(m,"CurrentRefNITDataIndex: %d",mInstStatus.CurrentRefNITDataIndex);
	Bool RetVal = FALSE;
	if(mInstStatus.CurrentRefNITDataIndex < mInstStatus.NoOfLinkageDescFound)
	{
		mInstStatus.Frequency = mInstStatus.RefNITData[mInstStatus.CurrentRefNITDataIndex].Frequency;
		mInstStatus.Polarization = mInstStatus.RefNITData[mInstStatus.CurrentRefNITDataIndex].Polarization;
		RetVal = TRUE;
	}
	else
	{
		TraceNotice(m,"CurrentRefNITDataIndex: %d, tuned to all linkage descriptors so switching to next satellite",mInstStatus.CurrentRefNITDataIndex);
		mInstStatus.CurrentRefNITDataIndex = 0;
		mInstStatus.RefNITDetailsAvailable = FALSE;
		mInstStatus.RefM7HomingDetailsAvaialble = FALSE;
		RetVal = SetNextHomingMuxDetails(TRUE);
	}

	return RetVal;
	
}


/* SwitchSatellite is TRUE if next Homing mux to be taken from next Satellite*/

Bool CHsvDvbsM7_mScan_Priv::SetNextHomingMuxDetails(Bool SwitchSatellite)
{
	Bool RetVal = FALSE;
	HsvPgdatDigSatInfoData SatInfo;

	CURRENT_INDEX = (CURRENT_INDEX == -1) ? 0 : (CURRENT_INDEX + 1);

	TraceNotice(m,"%d: CURRENT_INDEX: %d",__LINE__,CURRENT_INDEX);

	if(mInstStatus.ScanMode == Homing)
	{
		while((CURRENT_INDEX < UserPackagedetails.NoOfHomingMux) && (IsSatelliteDetected(UserPackagedetails.HomingMuxList[CURRENT_INDEX]->SatelliteId, &SatInfo) == FALSE))
		{
			CURRENT_INDEX++;
			TraceNotice(m,"%d: CURRENT_INDEX: %d",__LINE__,CURRENT_INDEX);
		}


		if((CURRENT_INDEX < UserPackagedetails.NoOfHomingMux))
		{
			RetVal = TRUE;
		}
		else
		{
			TraceDebug(m,"CurrentHomingIndex[%d] has exceeded NoOfHomingMux[%d], set Mode to Fallback",CURRENT_INDEX,UserPackagedetails.NoOfHomingMux);
			RetVal = FALSE;
			SET_SCAN_MODE(Fallback);
			CURRENT_INDEX = 0;
		}

	}
	
	if(mInstStatus.ScanMode == Fallback)
	{
		int CurrentSatID = AstraRefFrequencyDetails[CURRENT_INDEX - 1].SatelliteId;
			
		while((CURRENT_INDEX < NO_OF_ASTRA_REF_FREQ) && 
			(((SwitchSatellite) && (CurrentSatID == AstraRefFrequencyDetails[CURRENT_INDEX].SatelliteId)) || (IsSatelliteDetected(AstraRefFrequencyDetails[CURRENT_INDEX].SatelliteId, &SatInfo) == FALSE)))
		{
			CURRENT_INDEX++;
			TraceNotice(m,"%d: CURRENT_INDEX: %d",__LINE__,CURRENT_INDEX);
		}
		
		if((CURRENT_INDEX < NO_OF_ASTRA_REF_FREQ))
		{
			RetVal = TRUE;
		}
		else
		{
			TraceDebug(m,"CurrentFallbackMuxIndex[%d] has exceeded NoOfFallbackmuxes [%d]",CURRENT_INDEX,NO_OF_ASTRA_REF_FREQ);
		}
		
	}

	
	/*Set Tuning details to mInstStatus*/
	if(RetVal == TRUE)
	{
		mInstStatus.Lnb = SatInfo.LnbNumber;
		mInstStatus.LnbType = SatInfo.LnbType; 
		if(mInstStatus.ScanMode == Homing)
		{
			mInstStatus.Polarization = UserPackagedetails.HomingMuxList[CURRENT_INDEX]->Polarization;
			mInstStatus.Frequency = (UserPackagedetails.HomingMuxList[CURRENT_INDEX]->Frequency) * 1000;
		}
		else
		{
			mInstStatus.Polarization = AstraRefFrequencyDetails[CURRENT_INDEX].Polarization;
			mInstStatus.Frequency = (AstraRefFrequencyDetails[CURRENT_INDEX].Frequency) * 1000;
		}
		
		TraceNotice(m, "ScanMode: %d : Setting LNB as %d and Type %d ",mInstStatus.ScanMode,mInstStatus.Lnb,mInstStatus.LnbType);
	}

	return RetVal;

}

Bool CHsvDvbsM7_mScan_Priv::IsSatelliteDetected(int SatID, HsvPgdatDigSatInfoData* SatDetails)
{
	int i = 0, RetVal = FALSE;;
	HsvPgdatDigSatInfoData	SatInfo;
	
	for(i=0; i < MAX_NUM_LNBS_SUPPORTED; i++)
	{
		SatInfo.LnbNumber = i;
		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatInfo) == TRUE)
		{
			if(SatInfo.SatelliteId == SatID)
			{
				memcpy(SatDetails,&SatInfo,sizeof(SatInfo));
				RetVal = TRUE;
				break;
			
			}
		
		}
	}
	TraceNotice(m,"%s: SatID:%d RetVal: %d",__FUNCTION__,SatID,RetVal);
	return RetVal;
}

Bool CHsvDvbsM7_mScan_Priv::mStoreRefNITDetails()
{

	int i = 0, NumOfLinkageDesc = 0, NumOfSDSD = 0, LDIndex = 0;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;
	HSVSPTYPE(SatelliteDS, dvb, nit)	SatDSDesc;
	Bool Found = FALSE, RetVal = FALSE;

	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));

	for(i = 0; ((i < NumOfLinkageDesc) && (LDIndex < MAX_LINKAGE_DESC)) ; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, nit), i, (void*)(&LinkageDesc)) == TRUE)
		{
			if(LinkageDesc.LinkageType == NIT_REF_LINKAGE_TYPE)
			{
				mInstStatus.RefNITData[LDIndex].ONID = LinkageDesc.Original_NetworkId;
				mInstStatus.RefNITData[LDIndex].TSID = LinkageDesc.Tsid;
				mInstStatus.RefNITData[LDIndex].SvcId = LinkageDesc.ServiceId;
				LDIndex ++;
				Found = TRUE;
			}
		}
	}

	mInstStatus.NoOfLinkageDescFound = LDIndex;
	if(Found == TRUE)
	{
		NumOfSDSD = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
		for(LDIndex = 0; LDIndex < mInstStatus.NoOfLinkageDescFound; LDIndex++)
		{
			for(i = 0; i < NumOfSDSD; i++)
			{
				if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&SatDSDesc)) == TRUE)
				{
					if((SatDSDesc.Original_NetworkId == mInstStatus.RefNITData[LDIndex].ONID) && (SatDSDesc.Tsid == mInstStatus.RefNITData[LDIndex].TSID))
					{
						mInstStatus.RefNITData[LDIndex].Frequency = SatDSDesc.Frequency;
						mInstStatus.RefNITData[LDIndex].Polarization = SatDSDesc.Polarization;
						mInstStatus.RefNITData[LDIndex].ModulationSystem= SatDSDesc.ModulationSystem; 
						mInstStatus.RefNITData[LDIndex].ModulationType= SatDSDesc.ModulationType; 
						mInstStatus.RefNITData[LDIndex].FECInner= SatDSDesc.FECInner; 
						mInstStatus.RefNITData[LDIndex].RollOff= SatDSDesc.RollOff;
						RetVal = TRUE;
						break;
					}
				}
			}
		}

		if(RetVal == TRUE)
		{
			mInstStatus.Frequency = mInstStatus.RefNITData[0].Frequency;
			mInstStatus.Polarization = mInstStatus.RefNITData[0].Polarization;
			mInstStatus.CurrentRefNITDataIndex = 0;
		}
		
	}
	else
	{
		TraceNotice(m,"%s: %d Linkage Descriptor is not found",__FUNCTION__,__LINE__);
	}

	TraceNotice(m,"%s: %d NoOfLinkageDescFound : %d RetVal: %d",__FUNCTION__,__LINE__, mInstStatus.NoOfLinkageDescFound, RetVal);


	return RetVal;
}


Bool CHsvDvbsM7_mScan_Priv::mStoreRefM7HomingDetails()
{

	int i = 0, NumOfLinkageDesc = 0, NumOfSDSD;
	HSVSPTYPE(SatelliteDS, dvb, nit)	SatDSDesc;
	Bool Found = FALSE, RetVal = FALSE;

	HsvPgdatDigSatInfoData	SatInfo;
	SatInfo.LnbNumber = mInstStatus.Lnb;
	
	if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatInfo) == FALSE)
	{
		TraceErr (m,"%s: %d : Satinfo query is FAILED",__FUNCTION__,__LINE__);
	}

	int TSID = (SatInfo.SatelliteId == ASTRA_23_5_E) ? ASTRA_23_TSID : ASTRA_19_TSID;

	NumOfSDSD = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
	
	for(i = 0; i < NumOfSDSD; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&SatDSDesc)) == TRUE)
		{
			if((SatDSDesc.Tsid == TSID))
			{
				mInstStatus.RefM7HomingData.Frequency = SatDSDesc.Frequency;
				mInstStatus.RefM7HomingData.Polarization = SatDSDesc.Polarization;
				mInstStatus.RefM7HomingData.ModulationSystem= SatDSDesc.ModulationSystem; 
				mInstStatus.RefM7HomingData.ModulationType= SatDSDesc.ModulationType; 
				mInstStatus.RefM7HomingData.FECInner= SatDSDesc.FECInner; 
				mInstStatus.RefM7HomingData.RollOff= SatDSDesc.RollOff;
				mInstStatus.Frequency = SatDSDesc.Frequency;
				mInstStatus.Polarization = SatDSDesc.Polarization;
				TraceNotice(m,"Matching TSID[%d] found at freq: %d, pol:%d",TSID,mInstStatus.Frequency,mInstStatus.Polarization);
				RetVal = TRUE;
				break;
			}
		}
	}
		

	TraceNotice(m,"%s: %d RetVal: %d",__FUNCTION__,__LINE__, RetVal);


	return RetVal;
}



/*M7 CR Changes*/

/*M7 change*/
FResult CHsvDvbsM7_mScan_Priv::mSetUserPackageDetails(void)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	FResult		RetVal = err_NotSupported;
	Nat32 BouquetIndex;
	BouquetIndex = insstate_GetAttribute(mInstStatus.InstallationMode, insstate_AttributePackageId);
	int i;
	for(i=0; i < NO_OF_PACKAGES_SUPPORTED; i++)
	{
		if(M7PackageDetails[i].BouquetIndex == BouquetIndex)
		{
			UserPackagedetails.BouquetIndex= BouquetIndex;
			UserPackagedetails.PID = M7PackageDetails[i].PID;
			UserPackagedetails.NoOfHomingMux= M7PackageDetails[i].NoOfHomingMux;
			memcpy (UserPackagedetails.HomingMuxList, M7PackageDetails[i].HomingMuxList, sizeof(UserPackagedetails.HomingMuxList));
			memcpy (UserPackagedetails.SatelliteOrder, M7PackageDetails[i].SatelliteOrder, sizeof(UserPackagedetails.SatelliteOrder));
			CURRENT_INDEX = -1;
			RetVal = err_Ok;
			break;
		}
	}
	if(i == NO_OF_PACKAGES_SUPPORTED)
	{
		TraceErr(m,"Invalid Bouquet index:%d",(int)BouquetIndex);
	}
	return RetVal;
}

void CHsvDvbsM7_mScan_Priv::ResetM7installedLNBs()
{
	HsvLnbSettings		LnbSettings;
	int					LnbNumner;
	if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	{
		for (LnbNumner = 0; LnbNumner < MAX_NUM_LNBS_SUPPORTED; LnbNumner++)
		{
			if(LnbSettings.LnbSettings[LnbNumner].LnbStatus == LnbM7Installed)
			{
				LnbSettings.LnbSettings[LnbNumner].LnbStatus = LnbInstalled;
			}
			
		}
		idvbset_SetLnbSettings (&LnbSettings);
	}

}


void CHsvDvbsM7_mScan_Priv::mSetLNBConfiguration(void)
{
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);
	HsvLnbSettings				LnbSettings;
	HsvPgdatDigSatInfoData		SatInfo, TempSatInfo;
	HsvSatelliteMapping			MappedSatellite;

	int SatID = -1, LnbNumner = 0;

	if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	{
		TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
		if((LnbSettings.ConnectionType == LnbConnectionSingle)||(LnbSettings.ConnectionType == 	LnbConnectionDiSeqcMini)||(LnbSettings.ConnectionType == LnbConnectionDiSeqc1_0))
		{
		
			/*Reset LNBStatus of free LNBs based on connection type*/
			if(LnbSettings.ConnectionType != LnbConnectionDiSeqc1_0)
			{
				LnbSettings.LnbSettings[2].LnbStatus = LnbFree;
				LnbSettings.LnbSettings[3].LnbStatus = LnbFree;
				if(LnbSettings.ConnectionType == LnbConnectionSingle)
				{
					LnbSettings.LnbSettings[1].LnbStatus = LnbFree;
				}
			}

			if(!mNonM7SatelliteDetected(&LnbSettings))
			{
				//Set Connectiontype as Diseqc1.0
				if(LnbSettings.ConnectionType != LnbConnectionDiSeqc1_0)
				{
					LnbSettings.ConnectionType = (HsvLnbConnectionType)LnbConnectionDiSeqc1_0;
					LnbSettings.LnbSettings[0].LnbType = LnbUniversal;
					LnbSettings.LnbSettings[1].LnbType = LnbUniversal;
					LnbSettings.LnbSettings[2].LnbType = LnbUniversal;
					LnbSettings.LnbSettings[3].LnbType = LnbUniversal;
					idvbset_SetLnbSettings (&LnbSettings);
	
				}
			
				for(LnbNumner = 0; LnbNumner < MAX_NUM_LNBS_SUPPORTED; LnbNumner++)
				{
					if(LnbSettings.LnbSettings[LnbNumner].LnbStatus != LnbInstalled)
					{
						int index = -1;
						if(GetSatelliteIndexForAddition(&index))
						{
							//Add Satellite to SatInfo table
							memset (&MappedSatellite, 0x00, sizeof(HsvSatelliteMapping));
							MappedSatellite.SatelliteId = UserPackagedetails.SatelliteOrder[index].SatelliteId;
							iprescanparser_GetSatelliteAttributeById (&MappedSatellite);

							SatInfo.LnbNumber = LnbNumner;
							SatInfo.LnbType = LnbUniversal;
							SatInfo.OrbitalPosition = MappedSatellite.OrbitalPosition;
							SatInfo.SatelliteId = MappedSatellite.SatelliteId;
							memcpy (SatInfo.SatelliteName, MappedSatellite.SatelliteName, sizeof(SatInfo.SatelliteName));

							TempSatInfo.LnbNumber = LnbNumner;
							if (pgdb_GetByKey (SAT_INFO_TABLE, (Address)&TempSatInfo))
							{
								pgdb_Update (SAT_INFO_TABLE, (Address)&SatInfo);
							}
							else
							{
								pgdb_Add (SAT_INFO_TABLE, (Address)&SatInfo);
								TraceNotice(m,"Added Satellite with SatID: %d at LNB Number %d",SatInfo.SatelliteId,LnbNumner);
							}
							
							//Update UserPackagedetails
							UserPackagedetails.SatelliteOrder[index].Found = TRUE;


							//Update LNB Settings
							LnbSettings.LnbSettings[LnbNumner].LnbStatus = LnbM7Installed;
							LnbSettings.LnbSettings[LnbNumner].SatelliteId = SatInfo.SatelliteId;
							LnbSettings.LnbSettings[LnbNumner].UpdateInstallEnabled = TRUE;
							idvbset_SetLnbSettings (&LnbSettings);
						}
						else
						{
							TraceNotice(m,"No Satellite found for addition at LNB Number : %d",LnbNumner);
						}
					}
					else
					{
						TraceNotice(m,"Satellite with SatID: %d Added in prescan at LNB Number : %d",LnbSettings.LnbSettings[LnbNumner].SatelliteId,LnbNumner);
					}
				}
			}
			else
			{
				TraceNotice(m,"%s: %d: Non M7 satellite detected, Nothing to do here",__FUNCTION__,__LINE__);
			}
			
		}
		else
		{
			TraceNotice(m,"%s: %d: Connection type: %d, Nothing to do here",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
		}
	}
}

Bool CHsvDvbsM7_mScan_Priv::GetSatelliteIndexForAddition(int* index)
{
	Bool Retval = FALSE;
	for(int i = 0; i < MAX_NUM_LNBS_SUPPORTED; i++)
	{
		if(!(UserPackagedetails.SatelliteOrder[i].Found))
		{
			*index = i;
			Retval = TRUE;
			break;
		}
	}

	return Retval;
	
}

/*	This function checks if any other satellite(which is not there in SatelliteOrder) detected
	and also updates what are the satellites detected in SatelliteOrder if only M7 satellites are detected*/
Bool CHsvDvbsM7_mScan_Priv::mNonM7SatelliteDetected(HsvLnbSettings *LnbSettings)
{
	Bool RetVal = FALSE;
	int i = 0, j = 0;
	TraceNotice(m,"%s:%d",__FUNCTION__, __LINE__);

	for(i=0; i < MAX_NUM_LNBS_SUPPORTED; i++)
	{
		if (LnbInstalled == LnbSettings->LnbSettings[i].LnbStatus)
		{
			Bool M7Sat = FALSE;
			for(j = 0; j < MAX_NUM_LNBS_SUPPORTED; j++)
			{
				if(LnbSettings->LnbSettings[i].SatelliteId == UserPackagedetails.SatelliteOrder[j].SatelliteId)
				{
					UserPackagedetails.SatelliteOrder[j].Found = TRUE;
					M7Sat = TRUE;
					TraceNotice(m,"%s:%d: index: %d Sat.ID: %d j= %d",__FUNCTION__, __LINE__,i, LnbSettings->LnbSettings[i].SatelliteId,j);
					break;
				}
			}
			if(!M7Sat)
			{
				RetVal = TRUE;
				break;
			}
		}
	}
	
	TraceNotice(m,"%s: retval: %d",__FUNCTION__, RetVal);
	return RetVal;
}



/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx		isvcscanctrlN */

void CHsvDvbsM7_mScan_Priv::isvcscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
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
			if(mInstStatus.State == StDemuxWaitforM7Data)
			{
				if ((Value & isvcscanctrlN_FNT) && (Value & isvcscanctrlN_FST))
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
			}
			else
			{
				pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
			}
			break;
		case	isvcscanctrlN_SiDataAvailable:
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

void CHsvDvbsM7_mScan_Priv::plfApidvbsN_OnLockChanged( Bool LockState)
{
	/* TODO: Verify Cookie check is needed here or not */
	/* Notifiation Handler for DVB-S platform FE */	
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		isvcscandata	*/


int CHsvDvbsM7_mScan_Priv::isvcscandata_GetInstallationVersion(void)
{
	/* ANEESH: TODO: Have to implement this function when update installation comes */
	return 0;
}



void CHsvDvbsM7_mScan_Priv::isvcscandata_SyncComplete(void)
{
	TraceNotice (m, "%s %d", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
	/*TODO: check if this function is required and isigstr_StopSigStrMeasAll need to be called*/
//	isigstr_StopSigStrMeasAll();
	iinsN_OnEvent(iinsN_EventPkgInstallEnd,0);
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsM7_mScan_Priv::isvcscanpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbm7_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized ");
	/* Initialize acquisition module also */
	iacqpow_Init();
	isortpow_Init ();
}

void CHsvDvbsM7_mScan_Priv::isvcscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;
	
	mInstStatus.Cookie = 0;
	/* Initializing the other modules. TODO: Confirm :this is not to be called during StartInstallation */
	idataacq_Initialise (0);
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
}

void CHsvDvbsM7_mScan_Priv::isvcscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsM7_mScan_Priv::isvcscan_GetCurrentInstallationState (int *mode, int *state)
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
FResult CHsvDvbsM7_mScan_Priv::isvcscan_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult			RetVal = err_BadParameter;
	if (TURNED_ON)
	{
		TraceDebug (m, "SERVICE Scan Already Turned On ");
		/* Currently supporting only service scan. Have to update VALID_MODE as features added */
		if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			if (SCAN_NOT_INPROGESS)
			{
				TraceDebug (m, " No Service Scan in progress.. Initiating ");
				SET_INS_MODE(Mode);
				mInstStatus.IntallationState = insstate_InstallationStateInProgress;
				SET_SCAN_MODE(Homing);
				CURRENT_INDEX = -1;
				mInstStatus.RefNITDetailsAvailable = FALSE;
				mInstStatus.RefM7HomingDetailsAvaialble = FALSE;
				mInstStatus.CurrentRefNITDataIndex = -1;
				/* Now initialize the freq finder module to load the SDSDs obtained from pre-scan */
				pmp_PmpSend(mPump, EvStart, (Nat32)NULL);
			}
			RetVal = err_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsM7_mScan_Priv::isvcscan_WriteBarkerMuxData(void)
{
	idataacq_StoreBarkerMuxDetails();
	return TRUE;
}
FResult CHsvDvbsM7_mScan_Priv::isvcscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	return RetVal;
}
int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;
	
	RetVal = idataacq_GetNumberOfRadioChannelsFound ();
	
	return RetVal;
}

int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsRemoved();		
}
int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsM7_mScan_Priv::isvcscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

void CHsvDvbsM7_mScan_Priv::isvcscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	SiValues->Pid = UserPackagedetails.PID;
	SiValues->TableId = 0;
	SiValues->BouquetId = INVALID_BOUQUET_ID;
}

void CHsvDvbsM7_mScan_Priv::idataacqN_OnDataAquired(Bool Status)
{
	pmp_PmpSend(mPump, EvDataAcquired, (Nat32)NULL);
	TraceNotice (m, "%s %d", __FUNCTION__, __LINE__);
	UNUSED(Status);

}

int CHsvDvbsM7_mScan_Priv::isvcscan_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

FResult CHsvDvbsM7_mScan_Priv::isvcscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsM7_mScan_Priv::isvcscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsM7_mScan_Priv::isvcscan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsM7_mScan_Priv::isvcscan_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}


Bool CHsvDvbsM7_mScan_Priv::isvcscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsM7_mScan_Priv::isvcscan_StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsM7_mScan_Priv::isvcscan_GetScanProgressStatus (int Mode)
{
	return 0;
}
			
void CHsvDvbsM7_mScan_Priv::plfApidvbsN_OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsM7_mScan_Priv::isvcscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}
			

void CHsvDvbsM7_mScan_Priv::isvcscandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
}

void CHsvDvbsM7_mScan_Priv::isvcscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}
