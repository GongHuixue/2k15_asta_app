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
 *	C Source:		hsvdvbsins_mminiprescan.c
 *	Instance:		
 *	Description:	
 *	%created_by:	  aneeshc %
 *	%date_created:	  Thu Apr 18 18:52:01 2013 %
 *
**********************************************************************/

#include "_hsvdvbsins_mminiprescan.h"

/****************************************************************************
 * Macros and types
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsins_mminiprescan")


#ifndef __cplusplus

#else

#endif




















/****************************************************************************
 * Static variables
 ****************************************************************************/


int CHsvDvbsInstallation_mminiprescan_Priv::s__mCurrentSatelliteIndex;
 
Pump CHsvDvbsInstallation_mminiprescan_Priv::s__mPump;

InsInstance CHsvDvbsInstallation_mminiprescan_Priv::s__mInstStatus;

ModuleState CHsvDvbsInstallation_mminiprescan_Priv::s__mConstModuleLifeCycle = ConstTurnedOff;

int CHsvDvbsInstallation_mminiprescan_Priv::s__mCurrentTableIndex,CHsvDvbsInstallation_mminiprescan_Priv::s__CURRENT_SCAN_MODE;

int CHsvDvbsInstallation_mminiprescan_Priv::s__DataRequested = 0;












FunctionNat32 CHsvDvbsInstallation_mminiprescan_Priv::s__StateEventMatrix[EvMax][StMax] =
{
									/* StIdle						StStart								StTunerWait								StDemuxWait		    */
/* EvStart */					{	FNADDR(FuncStartMiniPreScan),	NULL,								NULL,									NULL								},
/* EvStop */					{	NULL,							FNADDR(FuncStopMiniPreScan), 		FNADDR(FuncStopMiniPreScan),			FNADDR(FuncStopMiniPreScan)					},
/* EvStationFound */			{	NULL,							NULL,								FNADDR(FuncMiniPrescanStationFound),    NULL								},
/* EvStationNotFound */			{	NULL,							NULL,            					FNADDR(FuncMiniPrescanStationNotFound), NULL								},
/* EvDataAvailable */			{	NULL,							NULL,            					NULL,									FNADDR(FuncMiniPrescanDataAvailable)		},
/* EvDataNotAvailable */		{	NULL,							NULL,            					NULL,									FNADDR(FuncMiniPrescanDataNotAvailable)		},
/* EvStartTuning */				{	NULL,							FNADDR(FuncStartMiniPrescanTuning),	NULL,									NULL								},
/* EvCheckLock	*/				{	NULL,							NULL,								FNADDR(FuncMiniPrescanCheckLock),		NULL								},
/* EvCheckDataAvailability */	{	NULL,							NULL,								NULL,									FNADDR(FuncCheckMiniPrescanDataAvailable)	}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/










/***** Static Functions *****/

void CHsvDvbsInstallation_mminiprescan_Priv::mAddSatInfo (HsvSatelliteMapping *MappedSatellite)
{
	HsvPgdatDigSatInfoData		SatInfo;
	HsvLnbSettings				LnbSettings;

	/* If no satellites are present, add the sat info at first */
	SatInfo.LnbNumber = CURRENT_LNB_INDEX;
	if (pgdb_GetByKey(SAT_INFO_TABLE, (Address)&SatInfo))
	{
		SatInfo.LnbNumber = CURRENT_LNB_INDEX;
		SatInfo.LnbType = mInstStatus.LnbType;
		SatInfo.SatelliteId = MappedSatellite->SatelliteId;
		SatInfo.OrbitalPosition = MappedSatellite->OrbitalPosition;
		memcpy (SatInfo.SatelliteName, MappedSatellite->SatelliteName, sizeof(SatInfo.SatelliteName));

		if (pgdb_Update (SAT_INFO_TABLE, (Address)&SatInfo))
		{
			TraceNotice(m," Updated the SatelliteInfo Succesfully \n");
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				if (LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType != mInstStatus.LnbType)
				{
					TraceNotice (m, "Setting Type To MDU ");
					LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType = (HsvLnbType) mInstStatus.LnbType;
				}
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
	else
	{
		TraceNotice (m, "ERROR: In MiniPrescan no satellite info found for update ");
	}
}

void CHsvDvbsInstallation_mminiprescan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice(m,"%s %d event %d GET_INS_STATE %d\n", __FUNCTION__, __LINE__, event, GET_INS_STATE);
	if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
	{
		TraceNotice(m,"%s %d event %s\n", __FUNCTION__, __LINE__, StateEventMatrix[event][GET_INS_STATE]? "Handled" : "Ignored");
		if(StateEventMatrix[event][GET_INS_STATE] != NULL)
		{
			FPCALL(StateEventMatrix[event][GET_INS_STATE])(param);
		}
	}
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncStartMiniPreScan(Nat32 Param)
{
	HsvLnbSettings	LnbSettings;
	
	mInitialise();
	SET_SCAN_MODE((mGetNextScanMode(-1)));
    
	/* Save the current LNB Settings to local data */
	idvbset_GetLnbSettings (&LnbSettings);
	mInstStatus.Lnb = Param;
	mInstStatus.LnbType = LnbSettings.LnbSettings[Param].LnbType;
	/* Check Whether currently detected LNB is MDU. If yes, it has to be considered as 
		universal LNB for prescan phase */
	switch(mInstStatus.LnbType)
	{
	case	LnbMdutype1:
	case	LnbMdutype2:
	case	LnbMdutype3:
	case	LnbMdutype4:
	case	LnbMdutype5:
		mInstStatus.LnbType = LnbUniversal;
		LnbSettings.LnbSettings[Param].LnbType = LnbUniversal;
		idvbset_SetLnbSettings (&LnbSettings);
		break;
	default:
		break;
	}
	
	TraceNotice(m,"%s %d Param %d <Lnb, LnbType> <%d %d> Mode %d \n", __FUNCTION__, __LINE__, (int) Param, mInstStatus.Lnb, mInstStatus.LnbType, CURRENT_SCAN_MODE);

	SET_INS_STATE(StStart);
	mStopSdm(HsvDmxMain);
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncStopMiniPreScan(Nat32 Param)
{
	TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);
	if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	mInitialise();
	iminiprescanN_OnEvent(iminiprescanN_EventPreScanStopped,mInstStatus.Lnb);
	UNUSED(Param);
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncMiniPrescanStationFound(Nat32 Param)
{
	/* start sdm collection with appropriate mode */
	TraceNotice (m, "Station Found ");
	SET_INS_STATE(StDemuxWait);	
	if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
	{
		DataRequested++;
		pmp_PmpSendAfter(mPump, EvCheckDataAvailability, (Nat32)DataRequested, TABLE_SCAN_DATA_TIMEOUT);
	}
	ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
	UNUSED(Param);

}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncMiniPrescanStationNotFound(Nat32 Param)
{	
	SET_SCAN_MODE((mGetNextScanMode(0)));
	TraceNotice (m, "Station Not Found ");
	SET_INS_STATE(StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);

	UNUSED(Param);
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncMiniPrescanDataAvailable(Nat32 Param)
{
	Bool SameSatelliteFound = TRUE;
	HsvSatelliteList	PreScanTableSatellite;
	HsvSatelliteMapping	SatelliteMapping;

	TraceNotice (m, "Data Available ");
	memset (&SatelliteMapping, 0x00, sizeof(HsvSatelliteMapping));
	memset((Address)(&PreScanTableSatellite), 0, sizeof(PreScanTableSatellite));
	
	if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
	{
		TraceNotice(m," SAT FOUND WITH INDEX %d \n", CURRENT_TABLE_INDEX);
		iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
		SatelliteMapping.SatelliteId = PreScanTableSatellite.SatelliteId;
		mMapPrescanLnbType (SatelliteMapping.SatelliteId, &(mInstStatus.LnbType));
		TraceNotice (m, " Found Satellite ID %d ", PreScanTableSatellite.SatelliteId);
		iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);
	}

	/* Check Satellite Change. If yes, clear the complete pgdb. Start adding the satellite info table.
		Pacakge change will not be handled here. hsvdvbsins will trigger the re-installation and package selection */
	if (mCheckChageOfSatelliteDetected (PreScanTableSatellite.SatelliteId))
	{
		SameSatelliteFound = FALSE;
		//pgdb_ClearTable(CURRENT_DATABASE_TABLE);

		mAddSatInfo (&SatelliteMapping);
	}

	mInitialise();
	ctrl_StopCollection(HsvDmxMain);	
	/* ANEESH: TODO: StopCollection notification will come now. Need to see how to handle this 
		as control goes back to installation */
	TraceNotice(m," Mini PRE-SCAN ENDED \n");

	/* Inform hsvdvbsin about the satellite detection */
	if (SameSatelliteFound)
	{
        UpdateIfMduType ();
        TraceNotice (m, "MiniPrescan: Same satellite found ");
		iminiprescanN_OnEvent (iminiprescanN_EventSameSatelliteDetected, PreScanTableSatellite.SatelliteId);
	}
	else
	{
        TraceNotice (m, "MiniPrescan: Different satellite found ");
		iminiprescanN_OnEvent (iminiprescanN_EventDifferentSatelliteDetected, PreScanTableSatellite.SatelliteId);
	}

	UNUSED(Param);
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncMiniPrescanDataNotAvailable(Nat32 Param)
{

	TraceNotice (m, "Data Not avaialable");
	SET_SCAN_MODE((mGetNextScanMode(0)));
	
	SET_INS_STATE(StStart);
	mStopSdm(HsvDmxMain);
	UNUSED(Param);
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncCheckMiniPrescanDataAvailable(Nat32 Param)
{
	/* Did not get no data available ntf for this request. So sending from here */
	if (Param == DataRequested)
	{
		pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
	}
}

Bool CHsvDvbsInstallation_mminiprescan_Priv::mMapPrescanLnbType (int SatelliteId, int *LnbType)
{
    Bool                    ConversionDone = TRUE;
	HsvSatelliteMapping		SatelliteAttribute;
	SatelliteAttribute.SatelliteId = SatelliteId;

	if (TRUE == iprescanparser_GetSatelliteAttributeById (&SatelliteAttribute))
	{
		switch (SatelliteAttribute.MduType)
		{
		case	1:
			*LnbType = LnbMdutype1;
			break;
		case	2:
			*LnbType = LnbMdutype2;
			break;
		case	3:
			*LnbType = LnbMdutype3;
			break;
		case	4:
			*LnbType = LnbMdutype4;
			break;
		case	5:
			*LnbType = LnbMdutype5;
			break;
		default:
            ConversionDone = FALSE;
			break;
		}
	}
    return ConversionDone;
}


Bool CHsvDvbsInstallation_mminiprescan_Priv::mIsMiniPrescanTuningAllowed (int SatelliteId)
{
	Bool	RetVal = FALSE;
	/* Mini Prescan is intended only for Digiturk specifil Satellites - TurkSat / EutelSat  (MDUs) */
	switch (SatelliteId)
	{
		/* ANEESH: Miniprescan is supported only for MDUs in 2k14 */
//		case	TURKSAT_42_0_E:
//		case	EUTELSAT_W3A_7A:
		case	EUTELSAT_W3A_7A_MDU5:
		case	EUTELSAT_W3A_7E_MDU4:
		case	EUTELSAT_W3A_7E_MDU3:
		case	EUTELSAT_W3A_7E_MDU2:
		case	EUTELSAT_W3A_7E_MDU1:
			RetVal = TRUE;
			break;
		default:
			break;
	}

	return RetVal;
}


void CHsvDvbsInstallation_mminiprescan_Priv::UpdateIfMduType (void)
{
    HsvLnbSettings				LnbSettings;
	
    if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
    {
        if (LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType != mInstStatus.LnbType)
        {
            TraceNotice (m, "Setting Type To MDU %d ", mInstStatus.LnbType);
            LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType = (HsvLnbType)mInstStatus.LnbType;
        }
        idvbset_SetLnbSettings (&LnbSettings);
    }
}

void CHsvDvbsInstallation_mminiprescan_Priv::FuncStartMiniPrescanTuning(Nat32 Param)
{
	FResult				RetVal = err_Ok;
	int					Frequency, Polarization = 0;
	HsvSatelliteList	PreScanTableSatellite;
	int					LnbType;

	TraceNotice (m, "%s %d CURRENT_TABLE_INDEX %d TOTAL_NUM_OF_SATELLITES %d\n", __FUNCTION__, __LINE__, CURRENT_TABLE_INDEX, TOTAL_NUM_OF_SATELLITES);
	TraceNotice (m , "EndOfSacn %d  CurrentScanMode %d ", mIsEndOfPrescan(), CURRENT_SCAN_MODE);
	if (!mIsEndOfPrescan ())
	{
		if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
		{
			/* Table Based Scan Mode. Get Each data and tune */
			iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
			
			Frequency = PreScanTableSatellite.PrescanFrequency;
			Polarization = PreScanTableSatellite.Polarization;
			LnbType = mInstStatus.LnbType;
			mMapPrescanLnbType (PreScanTableSatellite.SatelliteId, &LnbType);
			if (mIsMiniPrescanTuningAllowed (PreScanTableSatellite.SatelliteId))
			{
				TraceNotice (m, " Prescan: %s Freq %d Pol %d BouqtId %d NwId %d NwId1 %d TsId %d SymRate %d\n", __FUNCTION__, Frequency, Polarization,PreScanTableSatellite.BouquetId, PreScanTableSatellite.NetworkId,\
												PreScanTableSatellite.NetworkId1, PreScanTableSatellite.TsId, 0);
				mInstStatus.TableCollectStatus = ((PreScanTableSatellite.BouquetId != 0xFFFF) && (PreScanTableSatellite.TsId != 0xFFFF)) ? Requested : NotRequested;
				SET_INS_STATE(StTunerWait);
				RetVal = satfeapi_SatelliteFrontEndTune (mInstStatus.Lnb, LnbType, Frequency, 0,Polarization, 0, -1, -1, -1, -1, -1, -1);
				
				if (RetVal != err_Ok)
				{
					TraceNotice (m, " Error in SatelliteFrontendTune ");
					mInitialise();
					/* Error reprt to hsvdvbsins */
					iminiprescanN_OnEvent (iminiprescanN_EventPrescanFailed, 0);
				}
			}
			else
			{
				SET_SCAN_MODE((mGetNextScanMode(0)));
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
		}
	}
	else
	{
		/* Mini-Prescan ended without finding anything */
		iminiprescanN_OnEvent (iminiprescanN_EventPrescanFailed, 0);
	}

	UNUSED(Param);
}


void CHsvDvbsInstallation_mminiprescan_Priv::FuncMiniPrescanCheckLock(Nat32 Param)
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

Bool CHsvDvbsInstallation_mminiprescan_Priv::mCheckChageOfSatelliteDetected (int SatelliteId)
{
	Bool	RetVal = TRUE;
	HsvPgdatDigSatInfoData		SatInfo;

	SatInfo.LnbNumber = CURRENT_LNB_INDEX;
	if (pgdb_GetByKey(SAT_INFO_TABLE, (Address)&SatInfo))
	{
		RetVal = (SatInfo.SatelliteId != SatelliteId) ? TRUE : FALSE;
	}

	return RetVal;
}


void CHsvDvbsInstallation_mminiprescan_Priv::mInitialise(void)
{
	SET_INS_STATE(StIdle);
	
	mInstStatus.NumberOfLocksFound = 0;
	SET_SCAN_MODE(SCAN_MODE_IDLE);
	CURRENT_TABLE_INDEX = 0;

	TraceNotice(m,"%s %d  TOTAL_NUM_OF_SATELLITES %d\n", __FUNCTION__, __LINE__, TOTAL_NUM_OF_SATELLITES);

}

Bool CHsvDvbsInstallation_mminiprescan_Priv::mIsEndOfPrescan (void)
{
	Bool	RetVal = FALSE;

	RetVal = (CURRENT_SCAN_MODE == SCAN_MODE_IDLE) ? TRUE: FALSE;

	return RetVal;
}

int CHsvDvbsInstallation_mminiprescan_Priv::mGetNextScanMode (int CurrentMode)
{
	int		ScanMode = CURRENT_SCAN_MODE;

	if (CurrentMode == -1)
	{
		ScanMode = TABLE_BASED_SCAN_MODE;
	}
	else
	{
		if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
		{
			CURRENT_TABLE_INDEX++;
			if (CURRENT_TABLE_INDEX >= TOTAL_NUM_OF_SATELLITES)
			{
				/* No matching entries found in scan. Give completed */
				ScanMode = SCAN_MODE_IDLE;
			}
		}
	}

	return ScanMode;
}

void CHsvDvbsInstallation_mminiprescan_Priv::mStopSdm(HsvDemux dmx)
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

void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescanpow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbsins_mMiniPreScan" );
	mConstModuleLifeCycle = ConstInitialized;
	TraceNotice(m, "%s %d mPump %d\n", __FUNCTION__, __LINE__, mPump);
}

void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescanpow_TurnOn(void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
	mInitialise();
	/* TBD: make use of return value of the below function based on this we can skip TABLE 18 scan in error conditions
	        of xml file not there */


}
void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescanpow_TurnOff(void)
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

/* provides IHsvSatelliteInstallation		iprescan	*/


/* Functions for automatic installation + update installation */
FResult CHsvDvbsInstallation_mminiprescan_Priv::iminiprescan_StartMiniPrescan(int Lnb, int Param)
{
	FResult			RetVal = err_BadParameter;
	iprescanparser_ExtractPreScanTableFromXml();
	TOTAL_NUM_OF_SATELLITES = iprescanparser_GetNumberOfPrescanEntries ();
	TraceNotice(m,"[ Total Number Of Satellites to search = %d ]",TOTAL_NUM_OF_SATELLITES);

	TraceNotice(m,"TURNED_ON %d <%d %d>\n",  TURNED_ON, Lnb, Param);
	if (TURNED_ON)
	{
		/* Currently supporting only service scan. Have to update VALID_MODE as features added */
		if (IS_VALID_LNBNUMBER(Lnb))
		{
			SET_INS_STATE(StIdle);
			
			pmp_PmpSend(mPump, EvStart, Lnb);
			
			RetVal = err_Ok;
		}
	}

	UNUSED(Param);
	return RetVal;
}

void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescan_StopMiniPrescan (void)
{
	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);
}



FResult CHsvDvbsInstallation_mminiprescan_Priv::iminiprescan_GetSITableIds(Nat16* NetworkID, Nat16* BouquetID)
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

	TraceNotice(m,"%s %d CURRENT_TABLE_INDEX %d NetworkId %d BouquetId %d\n", __FUNCTION__, __LINE__, CURRENT_TABLE_INDEX, *NetworkID, *BouquetID);

	return RetVal;
}

/* provides IPlfApiDvbsNotify		iminiprescanplfApidvbsN	*/

void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescansatfrontendN_OnLockChanged(Bool LockState)
{
	/* Notifiation Handler for DVB-S platform FE. Thread seperating here */
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescansatfrontendN_OnBlindScanEnd(void)
{
	/* Not Expected here */
}

/* provides IHsvSdmControlNotifyEx		iprescanctrlN */

void CHsvDvbsInstallation_mminiprescan_Priv::iminiprescanctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
	HsvSatelliteList	PreScanTableSatellite;
	Nat16				NetworkId, TsId;

	TraceNotice (m, "%s %d eventid %d TURNED_ON %d\n", __FUNCTION__, __LINE__, eventid, TURNED_ON);
    if(TURNED_ON && (GET_INS_STATE != StIdle) )
    {
		switch(eventid)
        {
        case iminiprescanctrlN_DataAvailable:
			/* Chk the mode. If in table based mode, get the NIDs /BouquetID to compare */
			/* Waiting till NIT, SDT & BAT Available */
			if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
			{
				TraceNotice (m, "Table based scan ");
				/* Table Based Scan Mode. Get data from parser */
				iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
				TraceNotice (m, "BouquetId 0x%x NetworkId 0x%x NetworkID1 0x%d ", PreScanTableSatellite.BouquetId, PreScanTableSatellite.NetworkId, PreScanTableSatellite.NetworkId1);
				if ((PreScanTableSatellite.BouquetId != 0xFFFF) && ((value & iminiprescanctrlN_BAT) == iminiprescanctrlN_BAT))
				{
					if ((mInstStatus.TableCollectStatus == NotRequested) || (mInstStatus.TableCollectStatus == MatchingTsId))
					{
						/*	1. Only bouquetId needs to be validated. (No TSID) GiveData Available
							2. Matching TSID already found. So both TSID and bouquet ID matching. Give Data Available */
						DataRequested++;
						pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
					}
					else if (mInstStatus.TableCollectStatus == Requested)
					{
						/* TSID is yet to arrive. Only update the flag */
						mInstStatus.TableCollectStatus = MatchingBat;
					}
				}
				else if ((PreScanTableSatellite.NetworkId != 0xFFFF) && ((value & iminiprescanctrlN_NIT) == iminiprescanctrlN_NIT))
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
				else if ((PreScanTableSatellite.TsId != 0xFFFF) && ((value & iminiprescanctrlN_SDT) == iminiprescanctrlN_SDT))
				{
					TraceNotice (m, "SDT Available ");
					if (TRUE == strapi_GetByKey  (HsvMain,HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, (void *)(&TsId)))
					{
						TraceNotice (m, "TsId from stream %d TsId %d", TsId, PreScanTableSatellite.TsId);
						if (TsId == PreScanTableSatellite.TsId)
						{
							if (mInstStatus.TableCollectStatus == Requested)
							{
								mInstStatus.TableCollectStatus = MatchingTsId;
							}
							else if (mInstStatus.TableCollectStatus == MatchingBat)
							{
								DataRequested++;
								pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
							}
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
						TraceNotice (m, "Sdt Callback came.. But strapi failed !!! ");
						pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
					}
				}
			}
			break;
        case iminiprescanctrlN_DataNotAvailable:
			DataRequested++;
			pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
			break;
        case iminiprescanctrlN_StoppedCollection:
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
            break;
		default:
	        break;
        }
    }
	UNUSED(dmx);
	UNUSED(value);
}











