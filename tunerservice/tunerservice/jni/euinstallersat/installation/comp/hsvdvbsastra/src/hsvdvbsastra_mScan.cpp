/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *          %name: hsvdvbsastra_mScan.c %
 *       %version: TVG_6 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: shreeshav %
 */

#include <CHsvDvbsAstra_mScan.h>


/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsastra_mscan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/


#define FNADDR(f) (& CHsvDvbsAstra_mScan:: f)

#define FPCALL(f) (this->* f)

#define	VALID_EVENT(Ev)	(Ev < AstraEvMax) ? TRUE : FALSE

#define	VALID_STATE(St)		(St < AstraStMax) ? TRUE	: FALSE

#define	SET_INS_STATE(St)	(mInstStatus.State=St)

#define	SET_INS_MODE(Mode)	(mInstStatus.InstallationMode=Mode)

#define	SET_SCAN_MODE(Mode)	(mInstStatus.ScanMode=Mode)

#define	CURRENT_SCAN_MODE	(mInstStatus.ScanMode)

#define 	TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)

#define 	VALID_SOURCE(source)		(source == HsvMainTuner)

#define	VALID_DEMUX(Dmx)			(Dmx == HsvDmxMain)

#define	MAX_NUM_LNBS_SUPPORTED		(4)

#define	IS_VALID_LNBNUMBER(x)		(x < MAX_NUM_LNBS_SUPPORTED)

#define	VALID_MODE(Mode)	((Mode == insstate_InstallationServiceScan) || (Mode == insstate_InstallationUpdate) ||  (Mode == insstate_InstallationAutomaticUpdate) ) ? TRUE: FALSE

#define	SCAN_NOT_INPROGESS	(mInstStatus.State == AstraStIdle)

#define	IS_SERVICE_SCAN		(mInstStatus.InstallationMode == insstate_InstallationServiceScan)

#define	CURRENT_MODE		(mInstStatus.InstallationMode)

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

//#define	CREATE_TPID(LnbNumber,Frequency,Polarization)	(((LnbNumber&0x0F) << 28)|((Polarization & 0x01) << 24) | ((Frequency)&0xFFFFFF))

#define	SAT_INFO_TABLE									(pgdbconst_Satellite | pgdbconst_SatInfo)


#define	ASTRA_SAT_ID			(ASTRA_19_2_E)

#define	INVALID_BOUQUET_ID								(0xFFFF)

#define SGT_TABLE_ID                (0x91) 

#define NIT_REF_LINKAGE_TYPE		(0x04)

#define SGT_REF_LINKAGE_TYPE		(0x93)




typedef	enum 
{
	ConstInitialized = 0,
	ConstTurnedOn,
	ConstTurnedOff
} ModuleState;




/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsAstra_mScan::SvcScanEventNames[AstraEvMax+1][32] = 
{
	"AstraEvStart",
	"AstraEvStop",
	"AstraEvDataAvailable",
	"AstraEvDataNotAvailable",
	"AstraEvDataAcquired",
	"AstraEvStartTuning",
	"AstraEvCheckLock",
	"AstraEvSdmStopped",
	"AstraEvMax"
};



int CHsvDvbsAstra_mScan::s__mConstModuleLifeCycle = 0;

AstraInsInstance CHsvDvbsAstra_mScan::s__mInstStatus;

Pump CHsvDvbsAstra_mScan::s__mPump;


AstraHomingMuxData CHsvDvbsAstra_mScan::s__AstraDigitalPackageDetails[ASTRA_NO_OF_HOMING_MUX] = {{12603 , satfeapi_PolarisationHorizontal, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner56,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{12551, satfeapi_PolarisationVertical, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner56,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{11302 , satfeapi_PolarisationHorizontal, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner23,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{12515 , satfeapi_PolarisationHorizontal, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner56,satfeapi_RollOffOP35,satfeapi_PilotsON},
																	{11856 , satfeapi_PolarisationVertical, ASTRA_SAT_ID,satfeapi_ModSysDVBS,satfeapi_DVBSQPSK,satfeapi_FECInner34,satfeapi_RollOffOP35,satfeapi_PilotsON}};




AstraFunctionNat32 CHsvDvbsAstra_mScan::s__EventActionMatrix[AstraEvMax][AstraStMax] = 
{
							/* AstraStIdle,						AstraStAstraStart,					AstraStTunerWait,				AstraStDemuxWait,				AstraStAcquireWait			*/
/* AstraEvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL,						NULL				},
/* AstraEvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)},
/* AstraEvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL				},
/* AstraEvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL				},
/* AstraEvDataAcquired */		{  NULL,						NULL,   					NULL,						NULL,						FNADDR(FuncDataAcquired)	},
/* AstraEvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL,						NULL				},
/* AstraEvCheckLock */			{  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL				},
/* AstraEvSdmStopped */			{  NULL,						FNADDR(FuncSdmStopped),		NULL,					NULL,						NULL				}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsAstra_mScan::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);
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

void CHsvDvbsAstra_mScan::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);
	SET_INS_STATE(AstraStIdle);
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



void CHsvDvbsAstra_mScan::mStationFound (void)
{
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);

	SET_INS_STATE(AstraStDemuxWait);
	if((CURRENT_SCAN_MODE == Homing) || (CURRENT_SCAN_MODE == AcquireNIT))
	{
		ctrl_StartCollection(HsvDmxMain, ctrl_Normal);

	}
	else if(CURRENT_SCAN_MODE == AcquireSGT)
	{
		ctrl_StartCollection(HsvDmxMain, ctrl_NormalPlusPmt);
	}
}

void CHsvDvbsAstra_mScan::mNoStationFound (void)
{
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);
	if(CURRENT_SCAN_MODE == Homing)
	{
		/*Tune to next homing frequency*/		
		mInstStatus.HomingMuxIndex++;
		SET_INS_STATE (AstraStStart);		
		pmp_PmpSend(mPump, AstraEvStartTuning, (Nat32)NULL); 	
	}
	else
	{
		TraceNotice(m,"Station not found in mode : %d",CURRENT_SCAN_MODE);
		SET_INS_STATE (AstraStIdle);
		SET_SCAN_MODE(Invalid);
		iinsN_OnEvent(iinsN_EventInsFailed, 0);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
	}

}


void CHsvDvbsAstra_mScan::FuncDataAvailable (Nat32 param1)
{
	int Mode;
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);
	if(CURRENT_SCAN_MODE == Homing)
	{
		if(mStoreRefNITDetails() == TRUE)
		{
			idataacq_Initialise (0);
			SET_SCAN_MODE( AcquireNIT);
			SET_INS_STATE (AstraStStart);		
			if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
			{
				pmp_PmpSend(mPump, AstraEvStartTuning, (Nat32)NULL); 	
			}
			else
			{
				ctrl_StopCollection(HsvDmxMain);
			}
		}
		else
		{
			TraceNotice(m,"%s: %d: mStoreRefNITDetails FAILED",__FUNCTION__,__LINE__);
			SET_INS_STATE (AstraStIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}
	}
	else if(CURRENT_SCAN_MODE == AcquireNIT)
	{
		if(mStoreRefSGTDetails() == TRUE)
		{
			/*Collect SDSDs*/
			Mode = idataacq_Homing;
			idataacq_AcquireData(Mode);
			SET_INS_STATE(AstraStAcquireWait);
		}
		else
		{
			TraceNotice(m,"%s: %d: mStoreRefSGTDetails FAILED",__FUNCTION__,__LINE__);
			SET_INS_STATE (AstraStIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}
	}
	else if(CURRENT_SCAN_MODE == AcquireSGT)
	{
		if(mStoreSGTPID() == TRUE)
		{
			SET_SCAN_MODE(AcquireServices);	
			SET_INS_STATE (AstraStStart);		
			ctrl_StopCollection(HsvDmxMain);
		}
		else
		{
			TraceNotice(m,"%s: %d: mStoreSGTPID FAILED",__FUNCTION__,__LINE__);
			SET_INS_STATE (AstraStIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
		}
		
	}
	else if(CURRENT_SCAN_MODE == AcquireServices)
	{
		Mode = idataacq_Fallback;
		idataacq_AcquireData(Mode);
		SET_INS_STATE(AstraStAcquireWait);
	}

	UNUSED (param1);
}

void CHsvDvbsAstra_mScan::FuncNoDataAvailable (Nat32 param1)
{
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);

	if(CURRENT_SCAN_MODE == AcquireServices)
	{		
		TraceNotice(m,"AstraLCN: Installation Failed",__FUNCTION__,__LINE__);
		SET_INS_STATE (AstraStIdle);
		SET_SCAN_MODE(Invalid);
		iinsN_OnEvent(iinsN_EventInsFailed, 0);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
	}
	else
	{

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
		
		SET_INS_STATE (AstraStStart);			
		if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
		{
			pmp_PmpSend(mPump, AstraEvStartTuning, (Nat32)NULL);		
		}
		else
		{
			ctrl_StopCollection(HsvDmxMain);
		}
	}

	UNUSED (param1);
}

void CHsvDvbsAstra_mScan::FuncSdmStopped(Nat32  param)
{
	if(CURRENT_SCAN_MODE == AcquireServices)
	{
		SET_INS_STATE(AstraStDemuxWait);
		ctrl_StartCollection(HsvDmxMain, ctrl_AstraSGT);
	}
}


void CHsvDvbsAstra_mScan::FuncDataAcquired (Nat32 param1)
{
	Bool Result = (Bool)param1;
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);

	if(CURRENT_SCAN_MODE == AcquireNIT)
	{
		mInstStatus.NumOfSDSD = idataacq_GetNumberOfSdsds();
		mInstStatus.CurrSdsdIndex= 0;
		SET_SCAN_MODE(AcquireSGT);
		SET_INS_STATE (AstraStStart);		
		if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
		{
			pmp_PmpSend(mPump, AstraEvStartTuning, (Nat32)NULL); 	
		}
		else
		{
			ctrl_StopCollection(HsvDmxMain);
		}
	}
	else
	{
		SET_INS_STATE (AstraStIdle);
		mInstStatus.IntallationState = insstate_InstallationStateIdle;
		SET_INS_MODE(insstate_InstallationNone);
		iinsN_OnEvent(iinsN_EventPkgInstallEnd, 0);
		SET_SCAN_MODE(Invalid);
		
		if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
		{
			ctrl_StopCollection(HsvDmxMain);
		}
	}
}

void CHsvDvbsAstra_mScan::FuncCheckLockStatus(Nat32 Cookie)
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

void CHsvDvbsAstra_mScan::FuncStartTuning (Nat32 param1)
{
	TraceNotice(m,"ASTRA LCN %s:%d\n",__FUNCTION__, __LINE__);
	int		ModlnStd = -1, IqMode = -1, Cookie = 0;
	int		SymbolRate = 0,ModlnType = -1;
	int 	RollOff = -1, FEC = -1, Pilots = satfeapi_PilotsON; 
	HsvNITSatelliteDS CurrSDSD;

	if(CURRENT_SCAN_MODE == Homing)
	{
		if(mInstStatus.HomingMuxIndex < ASTRA_NO_OF_HOMING_MUX)
		{
		SET_INS_STATE(AstraStTunerWait);
		
		TraceNotice(m,"Homing: lnbNumber %d LnbType %d Frequency %d SymbolRate %d Polarization %d Cookie %d ModlnStd %d ModlnType %d IqMode %d RollOff %d FEC %d Pilots %d",mInstStatus.LnbNumber, mInstStatus.LnbType, (AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
								SymbolRate, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].ModulationSystem, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].ModulationType, IqMode, \
								AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].RollOffFactor,AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].FECInner,AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].Pilots);
								
		satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, (AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].Frequency*1000), \
								SymbolRate, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].Polarization,Cookie, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].ModulationSystem, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].ModulationType, \
								IqMode, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].RollOffFactor, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].FECInner, AstraDigitalPackageDetails[mInstStatus.HomingMuxIndex].Pilots);
		}
		else
		{
			SET_INS_STATE (AstraStIdle);
			SET_SCAN_MODE(Invalid);
			iinsN_OnEvent(iinsN_EventInsFailed, 0);
			mInstStatus.IntallationState = insstate_InstallationStateIdle;
			SET_INS_MODE(insstate_InstallationNone);
			TraceNotice(m,"Homing frequency list exhausted, No lock found for Homing frequencies");
		}

	}
	else if(CURRENT_SCAN_MODE == AcquireNIT)
	{
		
		SET_INS_STATE(AstraStTunerWait);
		
		TraceNotice(m,"AcquireNIT: lnbNumber %d LnbType %d Frequency %d SymbolRate %d Polarization %d Cookie %d ModlnStd %d ModlnType %d IqMode %d",mInstStatus.LnbNumber, mInstStatus.LnbType, mInstStatus.RefNITData.Frequency, \
								SymbolRate, mInstStatus.RefNITData.Polarization,Cookie, ModlnStd, ModlnType, IqMode);
								
		satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, mInstStatus.RefNITData.Frequency, \
								SymbolRate, mInstStatus.RefNITData.Polarization,Cookie, mInstStatus.RefNITData.ModulationSystem, mInstStatus.RefNITData.ModulationType, IqMode, \
								MapRollOffFactor(mInstStatus.RefNITData.RollOff), mInstStatus.RefNITData.FECInner, Pilots);
	}
	else if(CURRENT_SCAN_MODE == AcquireSGT)
	{
		
		SET_INS_STATE(AstraStTunerWait);
		
		TraceNotice(m," AcquireSGT: lnbNumber %d LnbType %d Frequency %d SymbolRate %d Polarization %d Cookie %d ModlnStd %d ModlnType %d IqMode %d",mInstStatus.LnbNumber, mInstStatus.LnbType, mInstStatus.RefSGTData.Frequency, \
								SymbolRate, mInstStatus.RefSGTData.Polarization,Cookie, ModlnStd, ModlnType, IqMode);
								
		satfeapi_SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, mInstStatus.RefSGTData.Frequency, \
								SymbolRate, mInstStatus.RefSGTData.Polarization,Cookie, mInstStatus.RefSGTData.ModulationSystem, mInstStatus.RefSGTData.ModulationType, IqMode, \
								MapRollOffFactor(mInstStatus.RefSGTData.RollOff), mInstStatus.RefSGTData.FECInner, Pilots);
	}
	UNUSED (param1);
}

void CHsvDvbsAstra_mScan::FuncStartServiceScan (Nat32 param1)
{
	/* Getting the LNB Details */
	mGetLnbDetails(ASTRA_SAT_ID);
	mInstStatus.HomingMuxIndex = 0;
	mInstStatus.NumOfSDSD = 0;
	mInstStatus.CurrSdsdIndex = 0;
	SET_SCAN_MODE(Homing);
	SET_INS_STATE (AstraStStart);
	
	iinsN_OnEvent(iinsN_EventPkgInstallStart,0);
	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, AstraEvStartTuning, (Nat32)NULL);		
	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}

	
	UNUSED (param1);
}


void CHsvDvbsAstra_mScan::mGetLnbDetails(int SatId)
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


void CHsvDvbsAstra_mScan::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
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


Bool CHsvDvbsAstra_mScan::mStoreRefNITDetails()
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
				mInstStatus.RefNITData.ONID = LinkageDesc.Original_NetworkId;
				mInstStatus.RefNITData.TSID = LinkageDesc.Tsid;
				mInstStatus.RefNITData.SvcId = LinkageDesc.ServiceId;
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
				if((SatDSDesc.Original_NetworkId == mInstStatus.RefNITData.ONID) && (SatDSDesc.Tsid == mInstStatus.RefNITData.TSID))
				{
					mInstStatus.RefNITData.Frequency = SatDSDesc.Frequency;
					mInstStatus.RefNITData.Polarization = SatDSDesc.Polarization; 
					mInstStatus.RefNITData.ModulationSystem= SatDSDesc.ModulationSystem; 
					mInstStatus.RefNITData.ModulationType= SatDSDesc.ModulationType; 
					mInstStatus.RefNITData.FECInner= SatDSDesc.FECInner; 
					mInstStatus.RefNITData.RollOff= SatDSDesc.RollOff; 
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

	return RetVal;
}

Bool CHsvDvbsAstra_mScan::mStoreRefSGTDetails()
{
	int i = 0, NumOfLinkageDesc = 0, NumOfSDSD;
	HSVSPTYPE(LinkageInfo, dvb, nit) LinkageDesc;
	HSVSPTYPE(SatelliteDS, dvb, nit)	SatDSDesc;
	Bool Found = FALSE, RetVal = FALSE;

	NumOfLinkageDesc = strapi_GetSize (HsvMain, HSVSPID(LinkageInfo, dvb, nit));

	TraceNotice(m,"%s: %d: NumOfLinkageDesc: %d",__FUNCTION__,__LINE__,NumOfLinkageDesc);

	for(i = 0; i < NumOfLinkageDesc ; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(LinkageInfo, dvb, nit), i, (void*)(&LinkageDesc)) == TRUE)
		{
			TraceNotice(m,"index: %d, linkage type: %d",i, LinkageDesc.LinkageType);
			if(LinkageDesc.LinkageType == SGT_REF_LINKAGE_TYPE)
			{
				mInstStatus.RefSGTData.ONID = LinkageDesc.Original_NetworkId;
				mInstStatus.RefSGTData.TSID = LinkageDesc.Tsid;
				mInstStatus.RefSGTData.SvcId = LinkageDesc.ServiceId;
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
				if((SatDSDesc.Original_NetworkId == mInstStatus.RefSGTData.ONID) && (SatDSDesc.Tsid == mInstStatus.RefSGTData.TSID))
				{
					mInstStatus.RefSGTData.Frequency = SatDSDesc.Frequency;
					mInstStatus.RefSGTData.Polarization = SatDSDesc.Polarization;
					mInstStatus.RefSGTData.ModulationSystem= SatDSDesc.ModulationSystem; 
					mInstStatus.RefSGTData.ModulationType= SatDSDesc.ModulationType; 
					mInstStatus.RefSGTData.FECInner= SatDSDesc.FECInner; 
					mInstStatus.RefSGTData.RollOff= SatDSDesc.RollOff; 
					RetVal = TRUE;
					break;
				}
			}
		}
		
	}
	else
	{
		TraceNotice(m,"%s: %d Linkage Descriptor not found",__FUNCTION__,__LINE__);
	}

	return RetVal;

}

Bool CHsvDvbsAstra_mScan::mStoreSGTPID()
{
	HSVSPTYPE(PidInfo, mpeg,simplepmt) PidInfo;
	Bool RetVal = FALSE;

	if ( strapi_GetByKey(HsvMain, HSVSPID(PidInfo, mpeg,simplepmt), mInstStatus.RefSGTData.SvcId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&PidInfo)) == TRUE )
	{
		mInstStatus.RefSGTData.SGTPid = PidInfo.SgtPid;

		RetVal = TRUE;
	}

	TraceNotice (m, "SGT PID stored : %d ", mInstStatus.RefSGTData.SGTPid);

	return RetVal;
}

int CHsvDvbsAstra_mScan::MapRollOffFactor(int RollOff)
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

void CHsvDvbsAstra_mScan::OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceNotice (m, "EventId 0x%x Value 0x%x ", EventId ,Value);
	if (VALID_DEMUX(Dmx))
	{
	
		switch (EventId)
		{
		case	isvcscanctrlN_DataNotAvailable:
			pmp_PmpSend(mPump, AstraEvDataNotAvailable, (Nat32)NULL);
			PrintfNotice("Data Not avilable: %d: %d\n", (!(Value & isvcscanctrlN_NIT)), (Value & isvcscanctrlN_NIT));
			break;
		case	isvcscanctrlN_StoppedCollection:
			if(CURRENT_SCAN_MODE != AcquireServices)
			{
				pmp_PmpSend(mPump, AstraEvStartTuning, (Nat32)NULL);
			}
			else
			{
				pmp_PmpSend(mPump, AstraEvSdmStopped, (Nat32)NULL);
			}
			break;
		case	isvcscanctrlN_DataAvailable:
				if(CURRENT_SCAN_MODE == AcquireSGT)
				{
					/*TODO: if there are no PMTs installation may stuck so handle only SDT available case also*/
					if(Value & isvcscanctrlN_SIMPLEPMT)
					pmp_PmpSend(mPump, AstraEvDataAvailable, (Nat32)NULL);
				}
				else
				{
					pmp_PmpSend(mPump, AstraEvDataAvailable, (Nat32)NULL);
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
}

/* provides IPlfApiDvbsNotify	isvcscanplfApidvbsN */

void CHsvDvbsAstra_mScan::OnLockChanged( Bool LockState)
{
	/* TODO: Verify Cookie check is needed here or not */
	/* Notifiation Handler for DVB-S platform FE */	
	pmp_PmpSend(mPump, AstraEvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		isvcscandata	*/


void CHsvDvbsAstra_mScan::GetPtcInfo (HsvInstallationPTC *ptc)
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


int CHsvDvbsAstra_mScan::GetInstallationVersion(void)
{
	/* ANEESH: TODO: Have to implement this function when update installation comes */
	return 0;
}



void CHsvDvbsAstra_mScan::SyncComplete(void)
{
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);
	pgdb_CommitTable(pgdb_GetCurrentTable());
}

/* provides IHsvPower	isvcscanpow */

void CHsvDvbsAstra_mScan::Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbastra_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
	isortpow_Init ();
	ibckgndpow_Init ();
}

void CHsvDvbsAstra_mScan::TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;
	
	/* Initializing the other modules. TODO: Confirm :this is not to be called during StartInstallation */
	idataacq_Initialise (0);
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
	ibckgndpow_TurnOn ();
}

void CHsvDvbsAstra_mScan::TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
	ibckgndpow_TurnOff ();
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsAstra_mScan::GetCurrentInstallationState (int *mode, int *state)
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
FResult CHsvDvbsAstra_mScan::StartInstallation(int Source, int Lnb, int Mode)
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
				pmp_PmpSend(mPump, AstraEvStart, (Nat32)NULL);
			}
			RetVal = err_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsAstra_mScan::WriteBarkerMuxData(void)
{
	idataacq_StoreBarkerMuxDetails();
	return TRUE;

}
FResult CHsvDvbsAstra_mScan::StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, AstraEvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsAstra_mScan::GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	return RetVal;
}
int CHsvDvbsAstra_mScan::GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;
	
	RetVal = idataacq_GetNumberOfRadioChannelsFound ();
	
	return RetVal;
}

int CHsvDvbsAstra_mScan::GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return idataacq_GetNumberOfTvChannelsRemoved();		
}
int CHsvDvbsAstra_mScan::GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	UNUSED(Lnb);
	return	idataacq_GetNumberofRadioChannelsRemoved();
}

int CHsvDvbsAstra_mScan::GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsAstra_mScan::GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsAstra_mScan::GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

void CHsvDvbsAstra_mScan::GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	if(AcquireServices == CURRENT_SCAN_MODE)
	{
		SiValues->Pid = mInstStatus.RefSGTData.SGTPid;
		/*SGT TableId*/
		SiValues->TableId = SGT_TABLE_ID;
		SiValues->BouquetId = INVALID_BOUQUET_ID;

	}
	else
	{
		SiValues->Pid = INVALID_PID;
		SiValues->TableId = 0;
		SiValues->BouquetId = INVALID_BOUQUET_ID;
	
	}
}

FResult CHsvDvbsAstra_mScan::SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	return 0;
}

FResult CHsvDvbsAstra_mScan::StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsAstra_mScan::SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsAstra_mScan::GetTricolorRegionNames(Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
void CHsvDvbsAstra_mScan::OnDataAquired(Bool Result)
{
	pmp_PmpSend(mPump, AstraEvDataAcquired, (Nat32)Result);
	TraceNotice (m, "%s %d\n", __FUNCTION__, __LINE__);

}


int CHsvDvbsAstra_mScan::GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

Bool CHsvDvbsAstra_mScan::SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsAstra_mScan::StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsAstra_mScan::GetScanProgressStatus (int Mode)
{
	return 0;
}
			
void CHsvDvbsAstra_mScan::OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsAstra_mScan::LoadManualInstallationDefaultValues (void)
{
	return 0;
}
			

void CHsvDvbsAstra_mScan::GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}

