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
 *
 *
 *	C Source:		hsvdvbsins_mprescan.c
 *	Instance:		
 *	Description:	
 *	%created_by:	 anuma %
 *	%date_created:	 Fri May 24 15:34:40 2013 %
 *
**********************************************************************/

#include "_hsvdvbsins_msatipprescan.h"

/****************************************************************************
 * Macros and types
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsins_msatipprescan")


#ifndef __cplusplus

#else

#endif




/****************************************************************************
 * Static variables
 ****************************************************************************/


int CHsvDvbsInstallation_msatipprescan_Priv::s__mCurrentSatelliteIndex;
 
Pump CHsvDvbsInstallation_msatipprescan_Priv::s__mPump;

InsInstance CHsvDvbsInstallation_msatipprescan_Priv::s__mInstStatus;

ModuleState CHsvDvbsInstallation_msatipprescan_Priv::s__mConstModuleLifeCycle = ConstTurnedOff;

int CHsvDvbsInstallation_msatipprescan_Priv::s__mCurrentTableIndex,CHsvDvbsInstallation_msatipprescan_Priv::s__CURRENT_SCAN_MODE;

int CHsvDvbsInstallation_msatipprescan_Priv::s__DataRequested = 0;







FunctionNat32 CHsvDvbsInstallation_msatipprescan_Priv::s__StateEventMatrix[EvMax][StMax] =
{
							  /*	StIdle					StStart					StTunerWait					StDemuxWait						*/
	/* EvStart */             {		FNADDR(FuncStartPreScan),NULL,					NULL,						NULL						},
	/* EvStop */			  {		NULL,					FNADDR(FuncStopPreScan),FNADDR(FuncStopPreScan),	FNADDR(FuncStopPreScan)		},
	/* EvStationFound */	  {		NULL,					NULL,					FNADDR(FuncStationFound),	NULL						},
	/* EvStationNotFound */   {		NULL,					NULL,            		FNADDR(FuncStationNotFound),NULL						},
	/* EvDataAvailable */     {		NULL,					NULL,            		NULL,						FNADDR(FuncDataAvailable)	},
	/* EvDataNotAvailable */  {		NULL,					NULL,            		NULL,						FNADDR(FuncDataNotAvailable)},
	/* EvStartTuning */       {		NULL,					FNADDR(FuncStartTuning),NULL,						NULL						},
	/* EvCheckLock	*/		  {		NULL,					NULL,					FNADDR(FuncCheckLock),		NULL						},
	/* EvCheckDataAvailability */{	NULL,					NULL,					NULL,						FNADDR(FunCheckDataAvailable)}

};



/****************************************************************************
 * Static functions
 ****************************************************************************/











/***** Static Functions *****/



void CHsvDvbsInstallation_msatipprescan_Priv::mAddSatInfo (HsvSatelliteMapping *MappedSatellite)
{
	Bool						RetVal = FALSE, UnknownSat = FALSE;
	int							Count = 0;
	HsvPgdatDigSatInfoData		SatInfo;
	HsvLnbSettings				LnbSettings;
	char						LnbName [10];
	HsvSatelliteMapping			UnknownSatelliteMapping;

	/* If no satellites are present, add the sat info at first */
	SatInfo.LnbNumber = CURRENT_LNB_INDEX;
	if (!pgdb_GetByKey(SAT_INFO_TABLE, (Address)&SatInfo))
	{
		SatInfo.LnbNumber = CURRENT_LNB_INDEX;
		SatInfo.LnbType = IPlfApiDvbsTuning_TUNING_DVBS_UNIVERSAL;
		SatInfo.OrbitalPosition = MappedSatellite->OrbitalPosition;
        SatInfo.SatelliteId = MappedSatellite->SatelliteId;
		memcpy (SatInfo.SatelliteName, MappedSatellite->SatelliteName, sizeof(SatInfo.SatelliteName));

		if (pgdb_Add (SAT_INFO_TABLE, (Address)&SatInfo))
		{
			TraceNotice(m,"LNB NUM: %d, TYPE: %d, orb.pos.: %d",SatInfo.LnbNumber, SatInfo.LnbType,SatInfo.OrbitalPosition);		

			TraceNotice(m," Added the SatelliteInfo Succesfully \n");
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				LnbSettings.LnbSettings[mInstStatus.Lnb].LnbStatus = LnbInstalled;
				LnbSettings.LnbSettings[mInstStatus.Lnb].SatelliteId = SatInfo.SatelliteId;
				LnbSettings.LnbSettings[mInstStatus.Lnb].UpdateInstallEnabled = TRUE;
				idvbset_SetLnbSettings (&LnbSettings);
			}
		}
		else
		{
			TraceNotice(m," Add SatInfo Failed... \n");
		}
	}
}

void CHsvDvbsInstallation_msatipprescan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceDebug(m,"%s %d event %d GET_INS_STATE %d\n", __FUNCTION__, __LINE__, event, GET_INS_STATE);
	if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
	{
		TraceDebug(m,"%s %d event %s\n", __FUNCTION__, __LINE__, StateEventMatrix[event][GET_INS_STATE]? "Handled" : "Ignored");
		if(StateEventMatrix[event][GET_INS_STATE] != NULL)
		{
			FPCALL(StateEventMatrix[event][GET_INS_STATE])(param);
		}
	}
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncStartPreScan(Nat32 Param)
{
	HsvLnbSettings	LnbSettings;
	
	mInitialise();
	SET_SCAN_MODE(TABLE_BASED_SCAN_MODE);

	TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
	/* Save the current LNB Settings to local data */
	idvbset_GetLnbSettings (&LnbSettings);
	mInstStatus.Lnb = Param;
	mInstStatus.LnbType = LnbSettings.LnbSettings[Param].LnbType;
	/*populate country dependant prescan table*/
	TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
	iprescanparser_PopulateCountryDependantTable(sysset_GetSystemCountry());
	GetSatIPPrescanEntry(FirstEntry);
	/*All LNBTypes are considered as Universal as SATIP server takes care of all other LNB types*/
	mInstStatus.LnbType = LnbUniversal;
	
	TraceNotice(m,"%s %d Param %d <Lnb, LnbType> <%d %d> Mode %d \n", __FUNCTION__, __LINE__, (int) Param, mInstStatus.Lnb, mInstStatus.LnbType, CURRENT_SCAN_MODE);

	SET_INS_STATE(StStart);
	mStopSdm(HsvDmxMain);
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncStopPreScan(Nat32 Param)
{
	TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);
	if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	mInitialise();
	iinsN_OnEvent(iinsN_EventInsStopped,mInstStatus.Lnb);
	UNUSED(Param);
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncStationFound(Nat32 Param)
{
	/* start sdm collection with appropriate mode */

	TraceDebug (m, "Station Found ");
	iinsN_OnEvent(iinsN_EventInsProgress,mInstStatus.Lnb);
	SET_INS_STATE(StDemuxWait);	
	
	DataRequested++;
	pmp_PmpSendAfter(mPump, EvCheckDataAvailability, (Nat32)DataRequested, TABLE_SCAN_DATA_TIMEOUT);
	ctrl_StartCollection(HsvDmxMain, ctrl_Normal);

	UNUSED(Param);

}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncStationNotFound(Nat32 Param)
{
	iinsN_OnEvent(iinsN_EventInsProgress,mInstStatus.Lnb);
	
	TraceNotice (m, "Station Not Found");

	GetSatIPPrescanEntry(NextEntry);
	
	TraceNotice (m, "EvStartTuning with SCAN_MODE %d", CURRENT_SCAN_MODE);
	SET_INS_STATE(StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	UNUSED(Param);
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncDataAvailable(Nat32 Param)
{
	int i = 0;
	Bool SatelliteFound = FALSE;
	HsvSatelliteList	PreScanTableSatellite;
	HsvSatelliteMapping	SatelliteMapping;

	TraceDebug (m, "Data AVailable ");
	memset (&SatelliteMapping, 0x00, sizeof(HsvSatelliteMapping));
	memset((Address)(&PreScanTableSatellite), 0, sizeof(PreScanTableSatellite));

	TraceNotice(m," SAT FOUND WITH INDEX %d \n", CURRENT_TABLE_INDEX);
	SatelliteFound = TRUE;
	iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
	SatelliteMapping.SatelliteId = PreScanTableSatellite.SatelliteId;
	TraceNotice (m, " Found Satellite ID %d ", PreScanTableSatellite.SatelliteId);
	iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);

	mAddSatInfo (&SatelliteMapping);
	/*Cache the tuning parameters*/
	mInitialise();
	ctrl_StopCollection(HsvDmxMain);
	TraceNotice(m," PRE-SCAN ENDED \n");
	iinsN_OnEvent(iinsN_EventSatelliteFound,mInstStatus.Lnb);

	UNUSED(Param);
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncDataNotAvailable(Nat32 Param)
{

	TraceDebug (m, "Data Not avaialable");
	
	GetSatIPPrescanEntry(NextEntry);
	SET_INS_STATE(StStart);
	mStopSdm(HsvDmxMain);
	UNUSED(Param);
}

void CHsvDvbsInstallation_msatipprescan_Priv::GetSatIPPrescanEntry(EntryIndex Entry)
{
	HsvSatelliteList	PreScanTableSatellite;
	HsvSatelliteMapping	SatelliteMapping;

	if(FirstEntry == Entry)
	{
		CURRENT_TABLE_INDEX = 0;
	}
	else
	{
		CURRENT_TABLE_INDEX++;
	}

	while (CURRENT_TABLE_INDEX <= TOTAL_NUM_OF_SATELLITES)
	{
		iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
		SatelliteMapping.SatelliteId = PreScanTableSatellite.SatelliteId;
		iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);
		
		if(SatelliteMapping.SatIP)
		{
			break;
		}
		CURRENT_TABLE_INDEX ++;
	}

	if(CURRENT_TABLE_INDEX >= TOTAL_NUM_OF_SATELLITES)
	{
		SET_SCAN_MODE(SCAN_MODE_IDLE);
	}
}



void CHsvDvbsInstallation_msatipprescan_Priv::FunCheckDataAvailable(Nat32 Param)
{
	/* Did not get no data available ntf for this request. So sending from here */
	if (Param == DataRequested)
	{
		pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
	}
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncStartTuning(Nat32 Param)
{
	
	FResult				RetVal = err_Ok;
	int					Frequency, Polarization = 0,SymbolRate,SymbolRateMode;
	HsvSatelliteList	PreScanTableSatellite;
	HsvLnbSettings		LnbSettings;
	int					LnbType, SatelliteId;
	int					ModulationSystem, ModulationType, FECInner, RollOffFactor, Pilots = satfeapi_PilotsON;

	TraceNotice (m, "%s %d CURRENT_TABLE_INDEX %d TOTAL_NUM_OF_SATELLITES %d\n", __FUNCTION__, __LINE__, CURRENT_TABLE_INDEX, TOTAL_NUM_OF_SATELLITES);
	TraceNotice (m , "EndOfSacn %d  CurrentScanMode %d ", mIsEndOfPrescan(), CURRENT_SCAN_MODE);
	if (!mIsEndOfPrescan ())
	{
		/* Get data and tune */
		iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
		
		Frequency = PreScanTableSatellite.PrescanFrequency;
		Polarization = PreScanTableSatellite.Polarization;
		SymbolRate = PreScanTableSatellite.SymbolRate;
		SatelliteId = PreScanTableSatellite.SatelliteId;
		ModulationSystem = PreScanTableSatellite.ModulationSystem;
		ModulationType = PreScanTableSatellite.ModulationType;
		FECInner = PreScanTableSatellite.FECInner;
		RollOffFactor = PreScanTableSatellite.RollOffFactor;
		LnbType = mInstStatus.LnbType;
		TraceNotice (m, " Prescan: %s Freq %d Pol %d BouqtId %d NwId %d NwId1 %d TsId %d SymRate %d\n", __FUNCTION__, Frequency, Polarization,PreScanTableSatellite.BouquetId, PreScanTableSatellite.NetworkId,\
										PreScanTableSatellite.NetworkId1, PreScanTableSatellite.TsId, 0);
		mInstStatus.TableCollectStatus = ((PreScanTableSatellite.BouquetId != 0xFFFF) && (PreScanTableSatellite.TsId != 0xFFFF)) ? Requested : NotRequested;
		SET_INS_STATE(StTunerWait);
		
		TraceNotice (m, "%s SatelliteId %d SatelliteFrontEndTune Lnb %d LnbType %d Frequency %d Polarization %d ModulationSystem: %d ModulationType: %d FECInner: %d RollOff: %d Pilots: %d\n", __FUNCTION__, SatelliteId, mInstStatus.Lnb, LnbType, Frequency, Polarization,ModulationSystem, ModulationType, FECInner, RollOffFactor, Pilots);
		RetVal = satfeapi_SatelliteFrontEndTune (mInstStatus.Lnb, LnbType, Frequency,SymbolRate,Polarization, 0, ModulationSystem, ModulationType, -1, RollOffFactor, FECInner, Pilots);
		
		if (RetVal != err_Ok)
		{
			TraceNotice (m, " Error in SatelliteFrontendTune ");
			mInitialise();
			/* Notify Error to apps */
			iinsN_OnEvent(iinsN_EventInsFailed,mInstStatus.Lnb);
		}
	}
	else
	{
		TraceNotice (m, "Nothing found. Setting LNB as free ");
		/* Marking the LNB as free */
		if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
		{
			LnbSettings.LnbSettings[mInstStatus.Lnb].LnbStatus = LnbFree;
			LnbSettings.LnbSettings[mInstStatus.Lnb].UpdateInstallEnabled = FALSE;
			idvbset_SetLnbSettings (&LnbSettings);
		}

		/* Satellite Not Found */
		mInitialise();
		iinsN_OnEvent(iinsN_EventSatelliteNotFound,mInstStatus.Lnb);

	}

	UNUSED(Param);
}

void CHsvDvbsInstallation_msatipprescan_Priv::FuncCheckLock(Nat32 Param)
{
	int RetVal, LnbNumber, LnbType, LockStatus, LockedFreq, Polarization, SymbolRate, IqMode, Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus,	&LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth );
	if ((RetVal == err_Ok) && (LockStatus != FALSE))
	{
		TraceNotice (m, "Prescan: Lock: LnbNumber %d LockedFreq %d Pol %d SymRate %d IqMode %d ", LnbNumber, LockedFreq, Polarization, SymbolRate, IqMode);
		pmp_PmpSend(mPump, EvStationFound, (Nat32)NULL);
	}
	else
	{
		TraceNotice (m, "No Station found ");
		pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
	}

}



void CHsvDvbsInstallation_msatipprescan_Priv::mInitialise(void)
{
	SET_INS_STATE(StIdle);
	SET_SCAN_MODE(SCAN_MODE_IDLE);
	CURRENT_TABLE_INDEX = 0;
	TraceNotice(m,"%s %d  TOTAL_NUM_OF_SATELLITES %d\n", __FUNCTION__, __LINE__, TOTAL_NUM_OF_SATELLITES);

}

Bool CHsvDvbsInstallation_msatipprescan_Priv::mIsEndOfPrescan (void)
{
	Bool	RetVal = FALSE;

	RetVal = (CURRENT_SCAN_MODE == SCAN_MODE_IDLE) ? TRUE: FALSE;

	return RetVal;
}


void CHsvDvbsInstallation_msatipprescan_Priv::mStopSdm(HsvDemux dmx)
{
	if(ctrl_GetMode(dmx) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		ctrl_StopCollection(dmx);
	}
}


/****************************************************************************
 * External functions
 ****************************************************************************/

/* provides IHsvPower		iprescanpow */

void CHsvDvbsInstallation_msatipprescan_Priv::iprescanpow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbsins_mSatipPreScan" );
	mConstModuleLifeCycle = ConstInitialized;
	TraceDebug(m, "%s %d mPump %d\n", __FUNCTION__, __LINE__, mPump);
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescanpow_TurnOn(void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
	mInitialise();

}
void CHsvDvbsInstallation_msatipprescan_Priv::iprescanpow_TurnOff(void)
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

/* provides IHsvSatelliteInstallation		iprescan	*/

/* Function to get the installation mode and status */
int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetCurrentInstallationState (int *mode, int *state)
{
	UNUSED(mode);
	UNUSED(state);
	return 0;
}

/* Functions for automatic installation + update installation */
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult			RetVal = err_BadParameter;
	iprescanparser_ExtractPreScanTableFromXml();
	TOTAL_NUM_OF_SATELLITES = iprescanparser_GetNumberOfPrescanEntries ();
	TraceNotice(m,"[ Total Number Of Satellites to search = %d ]",TOTAL_NUM_OF_SATELLITES);

	TraceNotice(m,"TURNED_ON %d <%d %d %d>\n",  TURNED_ON, Source, Lnb, Mode);
	if (TURNED_ON)
	{
		/* Currently supporting only service scan. Have to update VALID_MODE as features added */
		if (IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			SET_INS_STATE(StIdle);
			
			pmp_PmpSend(mPump, EvStart, Lnb);
			
			RetVal = err_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberOfTvChannelsFound (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}
int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberofRadioChannelsFound (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}
int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberOfTvChannelsRemoved    (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberofRadioChannelsRemoved (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}


/* Display the satellite Name per LNB. This should be used during pre-scan and service scan */
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSatelliteName (int Lnb, Nat16 *SatelliteName)
{
	/* GetSatellite Name will not be routed. So ignore */
	FResult		RetVal = err_NotSupported;
	
	return RetVal;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	return Retval;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	return Retval;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	return Retval;
}
	
/* Package information after the installation (service scan). But to be filled up by the Package Module */
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_IdentifyPackagesAvailable (void)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d \n", __FUNCTION__, __LINE__);
	return RetVal;
}
int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetTotalNumberOfPackagesFound (void)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d \n", __FUNCTION__, __LINE__);
	return RetVal;
}
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetPackageByIndex(int Index, HsvPackageStructure *Package)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d \n", __FUNCTION__, __LINE__);
	UNUSED (Index);
	UNUSED (Package);
	return RetVal;
}
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_SetUserPackageIndex(Nat32 PackageIndex)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d \n", __FUNCTION__, __LINE__);
	UNUSED (PackageIndex);
	return RetVal;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetUserPackageIndex(Nat32* PackageIndex, Bool* IsPackage)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d \n", __FUNCTION__, __LINE__);
	UNUSED (PackageIndex);
	return RetVal;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetInstalledSatellites (int mode, HsvInstalledSatellites *SatelliteEntries)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d \n", __FUNCTION__, __LINE__);
	UNUSED (mode);
	UNUSED (SatelliteEntries);
	return RetVal;
}

/* Interfaces towards the Add Satellite */
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_InstallAddedSatellites (void)
{
	FResult		RetVal = err_NotSupported;
	return RetVal;
}
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_ResetAddedSatellites (void)
{
	FResult		RetVal = err_NotSupported;
	return RetVal;
}

/* Interfaces towards the Remove Satellite */
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_RemoveSatelliteEntry (int LnbNumber)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (LnbNumber);
	return RetVal;
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_ResetInstallation (void)
{
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSatelliteSignalStrength (int LnbNumber)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (LnbNumber);
	return RetVal;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSatelliteSignalQuality  (int LnbNumber)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (LnbNumber);
	return RetVal;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSITableIds(Nat16* NetworkID, Nat16* BouquetID)
{
	FResult		RetVal = err_NotSupported;
	HsvSatelliteList	PreScanTableSatellite;

	if (CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
	{
		iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);

		*NetworkID = PreScanTableSatellite.NetworkId;
		*BouquetID = PreScanTableSatellite.BouquetId;
		RetVal = err_Ok;
	}
	TraceDebug(m,"%s %d CURRENT_TABLE_INDEX %d NetworkId %d BouquetId %d\n", __FUNCTION__, __LINE__, CURRENT_TABLE_INDEX, *NetworkID, *BouquetID);

	return RetVal;
}

Nat32 CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetAttribute(int Mode, int AttributeId)
{
	UNUSED (Mode);
	UNUSED (AttributeId);
	return 0;
}
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_SetAttribute(int Mode, int AttributeId, Nat32 Value)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (Mode);
	UNUSED (AttributeId);
	UNUSED (Value);
	return RetVal;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetScanProgressStatus (int Mode)
{
	int	ProgressBarStatus = 0;

	if (CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
	{
		if(TOTAL_NUM_OF_SATELLITES)
		{
			ProgressBarStatus = ((CURRENT_TABLE_INDEX < TOTAL_NUM_OF_SATELLITES) ? (CURRENT_TABLE_INDEX*100 /TOTAL_NUM_OF_SATELLITES)  : 0);
		}
	}
	else
	{
		ProgressBarStatus = 0;
	}
	
	if(ProgressBarStatus == 100)
	{
		ProgressBarStatus = 99;
	}
	
	return ProgressBarStatus;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetPackageName (Nat32 PackageId, Nat16	*PackageName)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (PackageId);
	UNUSED (PackageName);
	return RetVal;
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetFirstInstalledChannel(void)
{
	return 0;
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_UpdateConfigXmlStrings(char * PrescanXmlString,int PrescanXmlStringLen,char * SatellitePackageXmlString,int SatellitePackageXmlStringLen)
{
	return;
}

/* provides IPlfApiDvbsNotify		iprescanplfApidvbsN	*/

void CHsvDvbsInstallation_msatipprescan_Priv::iprescansatfrontendN_OnLockChanged(Bool LockState)
{
	/* Notifiation Handler for DVB-S platform FE. Thread seperating here */
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescansatfrontendN_OnBlindScanEnd(void)
{
}


/* provides IHsvDigitalScanData		iprescandata	*/

int CHsvDvbsInstallation_msatipprescan_Priv::iprescandata_GetInstallationVersion(void)
{
	return 0;
}

/* provides IHsvSdmControlNotifyEx		iprescanctrlN */

void CHsvDvbsInstallation_msatipprescan_Priv::iprescanctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
	HsvSatelliteList	PreScanTableSatellite;
	Nat16				NetworkId, TsId;

	TraceDebug (m, "%s %d eventid %d TURNED_ON %d\n", __FUNCTION__, __LINE__, eventid, TURNED_ON);
    if(TURNED_ON && (GET_INS_STATE != StIdle) )
    {
		switch(eventid)
        {
        case iprescanctrlN_DataAvailable:
			/* Chk the mode. If in table based mode, get the NIDs /BouquetID to compare */
			/* Waiting till NIT, SDT & BAT Available */
			if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
			{
				TraceNotice (m, "Table based scan ");
				/* Table Based Scan Mode. Get data from parser */
				iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
				TraceNotice (m, "BouquetId 0x%x NetworkId 0x%x NetworkID1 0x%d ", PreScanTableSatellite.BouquetId, PreScanTableSatellite.NetworkId, PreScanTableSatellite.NetworkId1);
				if ((PreScanTableSatellite.NetworkId != 0xFFFF) && ((value & iprescanctrlN_NIT) == iprescanctrlN_NIT))
				{
					TraceNotice (m, "NIT Came ");
					if (TRUE == strapi_GetByKey  (HsvMain,HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, (void *)(&NetworkId)))
					{
						TraceNotice (m, "NetworkId from stream %d networkId %d networkid1 %d", NetworkId, PreScanTableSatellite.NetworkId,PreScanTableSatellite.NetworkId1);
						if ((NetworkId == PreScanTableSatellite.NetworkId) || ((PreScanTableSatellite.NetworkId1 != 0xFFFF) && (NetworkId == PreScanTableSatellite.NetworkId1)))
						{
							DataRequested++;
							pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
						}
						else
						{
							DataRequested++;
							pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
						}
					}
					else
					{
						DataRequested++;
						TraceNotice (m, "Nit Callback came.. But strapi failed !!! ");
						pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
					}
				}
			}
			break;
        case iprescanctrlN_DataNotAvailable:
			DataRequested++;
			pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
			break;
        case iprescanctrlN_StoppedCollection:
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
            break;
		default:
	        break;
        }
    }
	UNUSED(dmx);
	UNUSED(value);
}


int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSignalStrength(Nat32 Param)
{
	int retValue = 0;

	return retValue;
}


void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StopSignalStrengthMeas(int Param)
{

}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StartSignalStrengthMeas(int Param)
{

}


int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSignalQuality(Nat32 Param)
{

    Nat32 lReturn = 0;
    return lReturn;

}


FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StoreManualInstallationValues (void)
{
	return 0;
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_EnableUnicable (int LnbNumber, Bool Enable)
{
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StartPredefinedListCopy (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}
FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetTricolorRegionNames(Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}


void CHsvDvbsInstallation_msatipprescan_Priv::iprescandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescandata_SyncComplete(void)
{
}

int CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetNumberOfDatabaseRecords(int TSDataOnly)
{
	return 0;
}

void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)
{
}


void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear)
{
	return;
}


void CHsvDvbsInstallation_msatipprescan_Priv::iprescan_SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData)
{
	return;
}


