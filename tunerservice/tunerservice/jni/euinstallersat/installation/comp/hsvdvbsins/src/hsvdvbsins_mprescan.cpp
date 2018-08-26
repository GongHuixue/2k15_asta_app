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

#include <unistd.h>

#include "_hsvdvbsins_mprescan.h"

/****************************************************************************
 * Macros and types
 ****************************************************************************/


TRACESYMBOL(m, "s2/installation/hsvdvbsins_mprescan")


#ifndef __cplusplus

#else

#endif






















/****************************************************************************
 * Static variables
 ****************************************************************************/


int CHsvDvbsInstallation_mprescan_Priv::s__mCurrentSatelliteIndex;
 
Pump CHsvDvbsInstallation_mprescan_Priv::s__mPump;

InsInstance CHsvDvbsInstallation_mprescan_Priv::s__mInstStatus;

ModuleState CHsvDvbsInstallation_mprescan_Priv::s__mConstModuleLifeCycle = ConstTurnedOff;

int CHsvDvbsInstallation_mprescan_Priv::s__mCurrentTableIndex,CHsvDvbsInstallation_mprescan_Priv::s__CURRENT_SCAN_MODE;

LNBSDSDList CHsvDvbsInstallation_mprescan_Priv::s__mLnbSdsdList;

int CHsvDvbsInstallation_mprescan_Priv::s__DataRequested = 0;

HsvSatInfoCache CHsvDvbsInstallation_mprescan_Priv::s__SatInfoCache[MAX_NUM_LNBS_SUPPORTED];



























FunctionNat32 CHsvDvbsInstallation_mprescan_Priv::s__StateEventMatrix[EvMax][StMax] =
{
							  /*	StIdle					StStart					StTunerWait					StDemuxWait						StFallbackMode						StSignalStrength			StWaitAbort			 */
	/* EvStart */             {		FNADDR(FuncStartPreScan),NULL,					NULL,						NULL,							NULL,								NULL,						NULL	             },
	/* EvStop */			  {		NULL,					FNADDR(FuncStopPreScan),FNADDR(FuncStopPreScan),	FNADDR(FuncStopPreScan),		FNADDR(FuncStopPreScan),			NULL,						FNADDR(FuncStopPreScan)},
	/* EvStationFound */	  {		NULL,					NULL,					FNADDR(FuncStationFound),	NULL,							FNADDR(FuncFallbackStationFound),	NULL,						NULL	             },
	/* EvStationNotFound */   {		NULL,					NULL,            		FNADDR(FuncStationNotFound),NULL,							FNADDR(FuncFallbackStationNotFound),NULL,						NULL	             },
	/* EvDataAvailable */     {		NULL,					NULL,            		NULL,						FNADDR(FuncDataAvailable),		FNADDR(FuncFallbackDataAvailable),	NULL,						NULL	             },
	/* EvDataNotAvailable */  {		NULL,					NULL,            		NULL,						FNADDR(FuncDataNotAvailable),	FNADDR(FuncFallbackDataNotAvailable),NULL,						NULL	             },
	/* EvStartTuning */       {		NULL,					FNADDR(FuncStartTuning),NULL,						NULL,							FNADDR(FuncFallbackStartTuning),	NULL,						NULL	 },
	/* EvCheckLock	*/		  {		NULL,					NULL,					FNADDR(FuncCheckLock),		NULL,							FNADDR(FuncCheckLock),				FNADDR(FuncCheckSigLock),	NULL	 },
	/* EvBlindScanEnd */	  {		NULL,					NULL,					FNADDR(FuncCheckBlindScan),	NULL,							FNADDR(FuncFallbackBlindScanEnd),	NULL,						FNADDR(FuncProcessAbort)},
	/* EvCheckDataAvailability */{	NULL,					NULL,					NULL,						FNADDR(FunCheckDataAvailable),	NULL,								NULL,						NULL	             				 },
	/* EvSigStrStart */       {		NULL,					FNADDR(FuncStartSigStrTune),NULL,					NULL,							NULL,								FNADDR(FuncStartSigStrMeas),NULL },
	/* EvSigStrStop */        {		NULL,					NULL,	                NULL,						NULL,							NULL,								FNADDR(FuncStopSigStrMeas), NULL  }

};



/****************************************************************************
 * Static functions
 ****************************************************************************/











/***** Static Functions *****/



int CHsvDvbsInstallation_mprescan_Priv::MapMwLnbTypeToPlf (int LnbType)
{
	int PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_UNIVERSAL;
	switch (LnbType)
	{
		case	LnbUniversal:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_UNIVERSAL;
			break;
		case	LnbMdutype1:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_MDU1;
			break;
		case	LnbMdutype2:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_MDU2;
			break;
		case	LnbMdutype3:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_MDU3;
			break;
		case	LnbMdutype4:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_MDU4;
			break;
		case	LnbMdutype5:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_MDU5;
			break;
		case	LnbUnicable:
			PlfLnbType = IPlfApiDvbsTuning_TUNING_DVBS_UNICABLE; /* Aneesh: TODO: Add this type in the interface file */
			break;
		default:
			break;
	}
	return PlfLnbType;
}


void CHsvDvbsInstallation_mprescan_Priv::mAddSatInfo (HsvSatelliteMapping *MappedSatellite)
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
		/* Check Unknown Satellite */
		UnknownSatelliteMapping.OrbitalPosition = 0;
		UnknownSatelliteMapping.EastWestFlag = 0;
		iprescanparser_GetSatelliteAttributeByPosition (&UnknownSatelliteMapping);
		TraceNotice (m, "Unknown Sat %d Cur %d ", UnknownSatelliteMapping.SatelliteId,MappedSatellite->SatelliteId); 
		if (MappedSatellite->SatelliteId != UnknownSatelliteMapping.SatelliteId)
		{
			for (Count = 0; Count  < MAX_NUM_LNBS_SUPPORTED; Count++)
			{	
				/* Check for duplicate satellite Id. Ignore if unknown satellite */
				SatInfo.LnbNumber = Count;
				if (pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
				{
					if (SatInfo.SatelliteId == MappedSatellite->SatelliteId)
					{
						TraceNotice (m, "Duplicate ");
						RetVal = TRUE;
						break;
					}
				}
			}
		}
		else
		{
			TraceNotice (m, "Unknown Sat ");
			UnknownSat = TRUE;
		}

		if (RetVal == FALSE)
		{
			SatInfo.LnbNumber = CURRENT_LNB_INDEX;
			SatInfo.LnbType = MapMwLnbTypeToPlf(mInstStatus.LnbType);
			SatInfo.OrbitalPosition = MappedSatellite->OrbitalPosition;

                    if((FALLBACK_BLINDSCAN_MODE == CURRENT_SCAN_MODE) &&
						(EUTELSAT_5_W == MappedSatellite->SatelliteId) &&
						(cids_CountryFrance == sysset_GetSystemCountry()))
                    {
                            /*if the Eutelsat 5 W satellite is detected using extended prescan (blind scan) and  country is france
                            **then packages should not be displayed to user (Fransat requirement), so making satellite ID as
                            **unknown to avoild showing unsorted (only) package to user
                            **This condition should be removed if someother package is added for france in SatellitePackageList.xml
                            */
                            SatInfo.SatelliteId = UnknownSatelliteMapping.SatelliteId;
                            TraceNotice (m, "Eutelsat satellite ID is changed to unknown  satellite ID");
                    }
                    else
                    {
                            SatInfo.SatelliteId = MappedSatellite->SatelliteId;
                    }

			if (UnknownSat)
			{
				/* Should display Sat - <Lnb Number > */
				sprintf (LnbName, "Sat - %d", CURRENT_LNB_INDEX);
				charsetutil_MbToWc((Nat8*)LnbName, strlen(LnbName), SatInfo.SatelliteName, MAX_SATELLITE_NAME_LEN, FALSE);
			}
			else
			{
				memcpy (SatInfo.SatelliteName, MappedSatellite->SatelliteName, sizeof(SatInfo.SatelliteName));
			}

			if (pgdb_Add (SAT_INFO_TABLE, (Address)&SatInfo))
			{
				TraceNotice(m,"LNB NUM: %d, TYPE: %d, orb.pos.: %d",SatInfo.LnbNumber, SatInfo.LnbType,SatInfo.OrbitalPosition);		

				TraceNotice(m," Added the SatelliteInfo Succesfully  ");
				if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
				{
					if (LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType != mInstStatus.LnbType)
					{
						TraceNotice (m, "Setting Type To MDU ");
						LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType = (HsvLnbType)mInstStatus.LnbType;
					}
					LnbSettings.LnbSettings[mInstStatus.Lnb].LnbStatus = LnbInstalled;
					LnbSettings.LnbSettings[mInstStatus.Lnb].SatelliteId = SatInfo.SatelliteId;
					LnbSettings.LnbSettings[mInstStatus.Lnb].UpdateInstallEnabled = TRUE;
					idvbset_SetLnbSettings (&LnbSettings);
				}
			}
			else
			{
				TraceNotice(m," Add SatInfo Failed...  ");
			}
		}
		else
		{
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				LnbSettings.LnbSettings[mInstStatus.Lnb].SatelliteId = SatInfo.SatelliteId;
				LnbSettings.LnbSettings[mInstStatus.Lnb].LnbStatus = LnbDuplicate;
				LnbSettings.LnbSettings[mInstStatus.Lnb].UpdateInstallEnabled = FALSE;
				idvbset_SetLnbSettings (&LnbSettings);
			}
		}
	}
}

void CHsvDvbsInstallation_mprescan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceDebug(m,"%s %d event %d GET_INS_STATE %d ", __FUNCTION__, __LINE__, event, GET_INS_STATE);
	if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
	{
		TraceDebug(m,"%s %d event %s ", __FUNCTION__, __LINE__, StateEventMatrix[event][GET_INS_STATE]? "Handled" : "Ignored");
		if(StateEventMatrix[event][GET_INS_STATE] != NULL)
		{
			FPCALL(StateEventMatrix[event][GET_INS_STATE])(param);
		}
	}
}

void CHsvDvbsInstallation_mprescan_Priv::FuncProcessAbort (Nat32 Param)
{
	if(CURRENT_SCAN_MODE == FALLBACK_BLINDSCAN_MODE)
	{
		TraceDebug (m, " Func[%s] Line[%d]  ",__FUNCTION__,__LINE__);
		SET_INS_STATE(StFallbackMode);
	}
	else
	{
		TraceDebug (m, " Func[%s] Line[%d]  ",__FUNCTION__,__LINE__);
		SET_INS_STATE(StTunerWait);
	}
	pmp_PmpSend(mPump, EvStationFound, (Nat32)NULL);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStartPreScan(Nat32 Param)
{
	HsvLnbSettings	LnbSettings;
	
	mInitialise();
	SET_SCAN_MODE((mGetNextScanMode(-1)));
    
	/* Save the current LNB Settings to local data */
	idvbset_GetLnbSettings (&LnbSettings);
	mInstStatus.Lnb = Param;
	mInstStatus.LnbType = LnbSettings.LnbSettings[Param].LnbType;
	/*populate country dependant prescan table*/
	iprescanparser_PopulateCountryDependantTable(sysset_GetSystemCountry());
	/* ANEESH: Check Whether currently detected LNB is MDU. If yes, it has to be considered as 
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
	
	TraceNotice(m,"%s %d Param %d <Lnb, LnbType> <%d %d> Mode %d  ", __FUNCTION__, __LINE__, (int) Param, mInstStatus.Lnb, mInstStatus.LnbType, CURRENT_SCAN_MODE);

	SET_INS_STATE(StStart);
	mStopSdm(HsvDmxMain);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStopPreScan(Nat32 Param)
{
	TraceNotice(m,"%s %d ", __FUNCTION__, __LINE__);
	if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	if (mInstStatus.BlindScanStarted != BlindScanIdle)
	{
		satfeapi_AbortSatelliteBlindScan(mInstStatus.Lnb);
	}
	mInitialise();
	iinsN_OnEvent(iinsN_EventInsStopped,mInstStatus.Lnb);
	UNUSED(Param);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStationFound(Nat32 Param)
{
	/* start sdm collection with appropriate mode */

	if (CURRENT_SCAN_MODE == BLIND_SCAN_MODE)
	{
		UpdateSatInfoCache ();
		/* Start the Table based scan */
		SET_SCAN_MODE((mGetNextScanMode(0)));
		SET_INS_STATE(StStart);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		TraceDebug (m, "Station Found ");
		iinsN_OnEvent(iinsN_EventInsProgress,mInstStatus.Lnb);
		SET_INS_STATE(StDemuxWait);	
		
		if( (CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE) || (CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE) )
		{
			DataRequested++;
			pmp_PmpSendAfter(mPump, EvCheckDataAvailability, (Nat32)DataRequested, TABLE_SCAN_DATA_TIMEOUT);
		}
		ctrl_StartCollection(HsvDmxMain, ctrl_Normal);

		UNUSED(Param);
	}
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStationNotFound(Nat32 Param)
{
	iinsN_OnEvent(iinsN_EventInsProgress,mInstStatus.Lnb);
	
	if (CURRENT_SCAN_MODE != BLIND_SCAN_MODE)
	{
		TraceNotice (m, "Station Not Found CURRENT_SCAN_MODE %d", CURRENT_SCAN_MODE);
		
		SET_SCAN_MODE((mGetNextScanMode(CURRENT_SCAN_MODE)));
		
		TraceNotice (m, "EvStartTuning with SCAN_MODE %d", CURRENT_SCAN_MODE);
		SET_INS_STATE(StStart);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
    else if (CURRENT_SCAN_MODE == BLIND_SCAN_MODE)
    {
		TraceDebug (m, "Station Not Found ");
		SET_INS_STATE(StStart);
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
    }
	UNUSED(Param);
}
void CHsvDvbsInstallation_mprescan_Priv::UpdateSatInfoCache (void)
{
	int RetVal, LnbNumber, LnbType, LockStatus, LockedFreq, Polarization, SymbolRate, IqMode, Bandwidth;
	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus,	&LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth );
	SatInfoCache[CURRENT_LNB_INDEX].Lnb          = CURRENT_LNB_INDEX;
	SatInfoCache[CURRENT_LNB_INDEX].LnbType      = mInstStatus.LnbType;
    SatInfoCache[CURRENT_LNB_INDEX].Frequency    = LockedFreq;
	SatInfoCache[CURRENT_LNB_INDEX].Polarization = Polarization;
	TraceNotice (m, " Freq %d Pol %d ", LockedFreq, Polarization );
}

void CHsvDvbsInstallation_mprescan_Priv::FuncDataAvailable(Nat32 Param)
{
	int i = 0;
	Bool SatelliteFound = FALSE;
	HsvSatelliteList	PreScanTableSatellite;
	HsvSatelliteMapping	SatelliteMapping;

	TraceDebug (m, "Data AVailable ");
	memset (&SatelliteMapping, 0x00, sizeof(HsvSatelliteMapping));
	memset((Address)(&PreScanTableSatellite), 0, sizeof(PreScanTableSatellite));

	/* get SDSD values for service scan which is next step of installation */
	mGetSDSDFromStrapi();
	
	if(CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE)
	{
		SatelliteFound = TRUE;
		SatelliteMapping.SatelliteId = CANAL_SAT_ID;
		mMapPrescanLnbType (SatelliteMapping.SatelliteId, &(mInstStatus.LnbType));
		TraceNotice (m, " Found Satellite ID %d ", SatelliteMapping.SatelliteId);
		iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);
	}
	else if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
	{
		TraceNotice(m," SAT FOUND WITH INDEX %d  ", CURRENT_TABLE_INDEX);
		SatelliteFound = TRUE;
		iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
		SatelliteMapping.SatelliteId = PreScanTableSatellite.SatelliteId;
		mMapPrescanLnbType (SatelliteMapping.SatelliteId, &(mInstStatus.LnbType));
		TraceNotice (m, " Found Satellite ID %d ", PreScanTableSatellite.SatelliteId);
		iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);
	}
	else
	{
		for (i = 0; i < mLnbSdsdList.NumofSDSDs; i++ )
		{
			SatelliteMapping.OrbitalPosition = mLnbSdsdList.SDSD[i].OrbitalPosition;
			SatelliteMapping.EastWestFlag = mLnbSdsdList.SDSD[i].WestEastFlag;
			if (iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping))
			{
				SatelliteFound = TRUE;
				break;
			}
		}
	}

	if (!SatelliteFound)
	{
		/* Unknown Satellite */
		SatelliteMapping.OrbitalPosition = 0;
		SatelliteMapping.EastWestFlag = 0;
		iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping);
	}

	mAddSatInfo (&SatelliteMapping);
	/*Cache the tuning parameters*/
   	UpdateSatInfoCache ();
	mInitialise();
	ctrl_StopCollection(HsvDmxMain);
	TraceNotice(m," PRE-SCAN ENDED  ");
	iinsN_OnEvent(iinsN_EventSatelliteFound,mInstStatus.Lnb);

	UNUSED(Param);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncDataNotAvailable(Nat32 Param)
{

	TraceDebug (m, "Data Not avaialable");
	SET_SCAN_MODE((mGetNextScanMode(0)));
	
	SET_INS_STATE(StStart);
	mStopSdm(HsvDmxMain);
	UNUSED(Param);
}

void CHsvDvbsInstallation_mprescan_Priv::FunCheckDataAvailable(Nat32 Param)
{
	/* Did not get no data available ntf for this request. So sending from here */
	if (Param == DataRequested)
	{
		pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
	}
}

void CHsvDvbsInstallation_mprescan_Priv::mSetLOValue(int SatelliteId)
{
	HsvLnbSettings	LnbSettings;
	
	if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	{
		if ((LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType == LnbUniversal) || (LnbSettings.LnbSettings[mInstStatus.Lnb].LnbType == LnbCircular))
		{
			if(SatelliteId == EUTELSAT_W4_36E)
			{
				LnbSettings.LnbSettings[mInstStatus.Lnb].HighLoFreq = CIRCULAR_HIGH_LO_FREQ;
				TraceNotice(m,"EUTELSAT_W4_36E CIRCULAR_HIGH_LO_FREQ %d",CIRCULAR_HIGH_LO_FREQ);
			}
			else
			{
				LnbSettings.LnbSettings[mInstStatus.Lnb].HighLoFreq = UNIVERSAL_HIGH_LO_FREQ;
				TraceNotice(m,"mSetLOValue UNIVERSAL_HIGH_LO_FREQ %d",UNIVERSAL_HIGH_LO_FREQ);
			}
		}
		
		idvbset_SetLnbSettings (&LnbSettings);
	}
	
}
Bool CHsvDvbsInstallation_mprescan_Priv::mMapPrescanLnbType (int SatelliteId, int *LnbType)
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

Bool CHsvDvbsInstallation_mprescan_Priv::mIsPrescanTuningAllowed (int LnbType, Bool ConversionDone)
{
	Bool	RetVal = TRUE;
	HsvLnbSettings	LnbSettings;

	switch (LnbType)
	{
	case	LnbMdutype1:
	case	LnbMdutype2:
	case	LnbMdutype3:
	case	LnbMdutype4:
	case	LnbMdutype5:
		if ((err_Ok == idvbset_GetLnbSettings (&LnbSettings)) && ((LnbSettings.ConnectionType == LnbConnectionUnicableSwitch) || (LnbSettings.ConnectionType == LnbConnectionUnicableLnb) ))
		{
            /* MDU Tuning not allowed for Unicable LNB & Switch */
			/* Disecq mini and 1.0 was removed to Support MDU behind DISEQC switch accdg to CR AN2767*/
			
			RetVal = FALSE;
		}
		break;
    default:
		if ((ConversionDone == TRUE) && (err_Ok == idvbset_GetLnbSettings (&LnbSettings)) && ((LnbSettings.ConnectionType == LnbConnectionUnicableSwitch) || (LnbSettings.ConnectionType == LnbConnectionUnicableLnb) ))
		{
            TraceNotice (m, "MDU Mapped as Universal. Dont install in case of Unicable LNB/Switch ");
            /* Conversion is done for MDU to Universal. This is not allowed if connection type is Unicable Switch/LNB */
			RetVal = FALSE;
		}
        break;
	}
	
	return RetVal;
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStartTuning(Nat32 Param)
{
	
	FResult				RetVal = err_Ok;
	int					Frequency, Polarization = 0,SymbolRate,SymbolRateMode;
	HsvSatelliteList	PreScanTableSatellite;
	HsvLnbSettings		LnbSettings;
	int					LnbType, SatelliteId;
    Bool                ConversionDone = FALSE;

	TraceNotice (m, "%s %d CURRENT_TABLE_INDEX %d TOTAL_NUM_OF_SATELLITES %d ", __FUNCTION__, __LINE__, CURRENT_TABLE_INDEX, TOTAL_NUM_OF_SATELLITES);
	TraceNotice (m , "EndOfSacn %d  CurrentScanMode %d ", mIsEndOfPrescan(), CURRENT_SCAN_MODE);
	if (!mIsEndOfPrescan ())
	{
		if( (CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE) || (CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE) )
		{
			if(CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE)
			{
			
				Frequency = pins_GetAttribute(PRESCAN_MODE, IHsvSatelliteInstallation_AttributeFrequency);
				Polarization = pins_GetAttribute(PRESCAN_MODE, IHsvSatelliteInstallation_AttributePolarization);
				SymbolRate = pins_GetAttribute(PRESCAN_MODE, IHsvSatelliteInstallation_AttributeSymbolRate);
				mInstStatus.TableCollectStatus = Requested;			
				SatelliteId = CANAL_SAT_ID;
				
				TraceNotice (m, "%s user entered Frequency %d Polarization %d ", __FUNCTION__, Frequency, Polarization);
			}
			else
			{				
				/* Table Based Scan Mode. Get Each data and tune */
				iprescanparser_GetSatelliteEntryFromPreScanTable(CURRENT_TABLE_INDEX, &PreScanTableSatellite);
				
				Frequency = PreScanTableSatellite.PrescanFrequency;
				Polarization = PreScanTableSatellite.Polarization;
				SymbolRate = 0;
				SatelliteId = PreScanTableSatellite.SatelliteId;
			}
			LnbType = mInstStatus.LnbType;
			ConversionDone = mMapPrescanLnbType (SatelliteId, &LnbType);
			mSetLOValue(SatelliteId);
			if (mIsPrescanTuningAllowed (LnbType, ConversionDone))
			{
				TraceNotice (m, " Prescan: %s Freq %d Pol %d BouqtId %d NwId %d NwId1 %d TsId %d SymRate %d ", __FUNCTION__, Frequency, Polarization,PreScanTableSatellite.BouquetId, PreScanTableSatellite.NetworkId,\
												PreScanTableSatellite.NetworkId1, PreScanTableSatellite.TsId, 0);
				mInstStatus.TableCollectStatus = ((PreScanTableSatellite.BouquetId != 0xFFFF) && (PreScanTableSatellite.TsId != 0xFFFF)) ? Requested : NotRequested;
				SET_INS_STATE(StTunerWait);
				
				TraceNotice (m, "%s SatelliteId %d SatelliteFrontEndTune Lnb %d LnbType %d Frequency %d Polarization %d ", __FUNCTION__, SatelliteId, mInstStatus.Lnb, LnbType, Frequency, Polarization);
				RetVal = satfeapi_SatelliteFrontEndTune (mInstStatus.Lnb, LnbType, Frequency,SymbolRate,Polarization, 0, -1, -1, -1, -1, -1, -1);
				
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
				iinsN_OnEvent(iinsN_EventInsProgress,mInstStatus.Lnb);
				SET_SCAN_MODE((mGetNextScanMode(0)));
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
		}
		else
		{
			if (mInstStatus.BlindScanStarted == BlindScanIdle)
			{
				TraceNotice (m, "Prescan: Starting Blind Scan ");
				/* Blind Scan Mode */
				SET_INS_STATE(StTunerWait);
				RetVal = satfeapi_StartSatelliteBlindScan (mInstStatus.Lnb, satfeapi_BlindScanModeNormal);
				if (RetVal != err_Ok)
				{
					TraceNotice (m, "BlindScan start failed ");
					mInitialise();
					/* Notify Error to apps */
					iinsN_OnEvent(iinsN_EventInsFailed,mInstStatus.Lnb);
				}
				else
				{
					/* Blind Scan started */
					mInstStatus.BlindScanStarted = BlindScanStarted;
				}
			}
			else
			{
				/* Blind Scan Mode */
				SET_INS_STATE(StTunerWait);
				RetVal = satfeapi_ContinueSatelliteBlindScan();
				if (RetVal != err_Ok)
				{
					TraceNotice (m, "BlindScan start failed ");
					mInitialise();
					/* Notify Error to apps */
					iinsN_OnEvent(iinsN_EventInsFailed,mInstStatus.Lnb);
				}
			}
		}
	}
	else
	{
		if (mInstStatus.BlindScanStarted == BlindScanLocked)
		{
			/* Unknown Satellite */

			TraceNotice (m, "Table-18 Scan not found valid satellite but still not going to do fallback blind scan ");
			StoreUnknownSatellite ();
			mInitialise();
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
	}

	UNUSED(Param);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncCheckLock(Nat32 Param)
{
	int RetVal, LnbNumber, LnbType, LockStatus, LockedFreq, Polarization, SymbolRate, IqMode, Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus,	&LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth );
	if ((RetVal == err_Ok) && (LockStatus != FALSE))
	{
		TraceNotice (m, "Prescan: Lock: LnbNumber %d LockedFreq %d Pol %d SymRate %d IqMode %d ", LnbNumber, LockedFreq, Polarization, SymbolRate, IqMode);
		if (mInstStatus.BlindScanStarted == BlindScanStarted) 
		{
			TraceNotice (m, "BlindScan Locked");
			mInstStatus.BlindScanStarted = BlindScanLocked;
			UpdateSatInfoCache ();
			if(CURRENT_SCAN_MODE != FALLBACK_BLINDSCAN_MODE) {
				SET_INS_STATE(StWaitAbort);
				satfeapi_AbortSatelliteBlindScan (0); /* ANEESH: FIXIT: TODO: Correctthe Lnbnumber here */
			}

		}
		pmp_PmpSend(mPump, EvStationFound, (Nat32)NULL);
	}
	else
	{
		TraceNotice (m, "No Station found ");
		pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
	}

}

void CHsvDvbsInstallation_mprescan_Priv::FuncCheckBlindScan(Nat32 Param)
{
	/* Indicates there is nothing found in this LNB */
	if (mInstStatus.BlindScanStarted == BlindScanStarted) 
	{
		TraceNotice (m, " BlindScan not locked ");
		mInstStatus.BlindScanStarted = BlindScanNotLocked;
	}

	SET_SCAN_MODE((mGetNextScanMode(0)));
	SET_INS_STATE(StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
}


void CHsvDvbsInstallation_mprescan_Priv::FuncFallbackStationFound(Nat32 Param)
{

	TraceDebug (m, "Station Found ");
	iinsN_OnEvent(iinsN_EventInsProgress,mInstStatus.Lnb);
	
	ctrl_StartCollection(HsvDmxMain, ctrl_Normal);

}

void CHsvDvbsInstallation_mprescan_Priv::FuncFallbackStationNotFound(Nat32 Param)
{
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncFallbackDataAvailable(Nat32 Param)
{
	int i = 0;
	Bool SatelliteFound = FALSE;
	HsvSatelliteList	PreScanTableSatellite;
	HsvSatelliteMapping	SatelliteMapping;

	TraceDebug (m, "Data AVailable ");
	memset (&SatelliteMapping, 0x00, sizeof(HsvSatelliteMapping));
	memset((Address)(&PreScanTableSatellite), 0, sizeof(PreScanTableSatellite));

	mInstStatus.NumberOfLocksFound++;

	/* get SDSD values for identifying as valid satellite */
	mGetSDSDFromStrapi();
	
	for (i = 0; i < mLnbSdsdList.NumofSDSDs; i++ )
	{
		SatelliteMapping.OrbitalPosition = mLnbSdsdList.SDSD[i].OrbitalPosition;
		SatelliteMapping.EastWestFlag = mLnbSdsdList.SDSD[i].WestEastFlag;
		if (iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping))
		{
			/*When the fallback detection finds a satellite, only Astra 19.2 shall be kept, all other satellites detected shall be changed to Unkown satellite.*/
			if (SatelliteMapping.SatelliteId == ASTRA_19_2_E)
			{
				SatelliteFound = TRUE;
				break;
			}
		}
	}

	if (SatelliteFound)
	{
		UpdateSatInfoCache ();
		mAddSatInfo (&SatelliteMapping);
		mInitialise();
		ctrl_StopCollection(HsvDmxMain);
		TraceNotice(m," PRE-SCAN ENDED  ");
		satfeapi_AbortSatelliteBlindScan (0);
		iinsN_OnEvent(iinsN_EventSatelliteFound,mInstStatus.Lnb);
	}
	else
	{
		/* Check how many tries are over. If this exceeds the max trials.
			Save satellite as unknown */
		if (mInstStatus.NumberOfLocksFound == MAX_FALLBACK_BLINDSSCAN_LOCKS)
		{
			UpdateSatInfoCache ();
			TraceNotice (m, " Obtained %d locks in fallback blind scan mode. But no valid SDSD. Marking as unknown satellite ", MAX_FALLBACK_BLINDSSCAN_LOCKS);
			StoreUnknownSatellite ();
			satfeapi_AbortSatelliteBlindScan (0);
			SET_SCAN_MODE((mGetNextScanMode(0)));
		}
		else
		{
			mStopSdm(HsvDmxMain);
		}
	}

	UNUSED(Param);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncFallbackDataNotAvailable(Nat32 Param)
{

	mInstStatus.NumberOfLocksFound++;
	if (mInstStatus.NumberOfLocksFound == MAX_FALLBACK_BLINDSSCAN_LOCKS)
	{
		TraceNotice (m, " Obtained %d locks in fallback blind scan mode. But no valid SDSD. Marking as unknown satellite ", MAX_FALLBACK_BLINDSSCAN_LOCKS);
		UpdateSatInfoCache ();
		StoreUnknownSatellite ();
		satfeapi_AbortSatelliteBlindScan (0);
		SET_SCAN_MODE((mGetNextScanMode(0)));
	}
	else
	{
		mStopSdm(HsvDmxMain);
	}

	UNUSED(Param);
}


void CHsvDvbsInstallation_mprescan_Priv::FuncFallbackStartTuning(Nat32 Param)
{
	FResult		RetVal = err_Ok;

	if (mInstStatus.BlindScanStarted == BlindScanIdle)
	{
		TraceNotice (m, "Prescan: Starting Blind Scan ");

		/* ANEESH: TODO: Check with Pavan, whether minimal mode in satfe has to be reverted back. */
		RetVal = satfeapi_StartSatelliteBlindScan (mInstStatus.Lnb, satfeapi_BlindScanModeMinimal);
		if (RetVal != err_Ok)
		{
			/* Give as unknown satellite */
			StoreUnknownSatellite ();
			SET_SCAN_MODE((mGetNextScanMode(0)));
		}
		else
		{
			/* Blind Scan started */
			mInstStatus.BlindScanStarted = BlindScanStarted;
		}
	}
	else
	{
		/* Blind Scan Mode */
		RetVal = satfeapi_ContinueSatelliteBlindScan();
		if (RetVal != err_Ok)
		{
			/* Give as unknown satellite */
			StoreUnknownSatellite ();
			SET_SCAN_MODE((mGetNextScanMode(0)));
		}
	}

}

void CHsvDvbsInstallation_mprescan_Priv::FuncFallbackBlindScanEnd(Nat32 Param)
{
	TraceNotice (m, "Fallback blind scan also finished. No valid satellites found. Mark as unknown satellite ");
	StoreUnknownSatellite ();
	SET_SCAN_MODE((mGetNextScanMode(0)));
}


void CHsvDvbsInstallation_mprescan_Priv::StoreUnknownSatellite (void)
{
	HsvSatelliteMapping	SatelliteMapping;

	SatelliteMapping.OrbitalPosition = 0;
	SatelliteMapping.EastWestFlag = 0;
	iprescanparser_GetSatelliteAttributeByPosition (&SatelliteMapping);

	mAddSatInfo (&SatelliteMapping);
	mInitialise();
	ctrl_StopCollection(HsvDmxMain);
	TraceNotice(m," PRE-SCAN ENDED  ");
	iinsN_OnEvent(iinsN_EventSatelliteFound,mInstStatus.Lnb);

}

void CHsvDvbsInstallation_mprescan_Priv::mInitialise(void)
{
	SET_INS_STATE(StIdle);
	
	mInstStatus.BlindScanStarted = BlindScanIdle;
	mInstStatus.NumberOfLocksFound = 0;
	SET_SCAN_MODE(SCAN_MODE_IDLE);
	CURRENT_TABLE_INDEX = 0;
	memset (&mLnbSdsdList, 0x00, sizeof(mLnbSdsdList));

	TraceNotice(m,"%s %d  TOTAL_NUM_OF_SATELLITES %d ", __FUNCTION__, __LINE__, TOTAL_NUM_OF_SATELLITES);

}

Bool CHsvDvbsInstallation_mprescan_Priv::mIsEndOfPrescan (void)
{
	Bool	RetVal = FALSE;

	RetVal = (CURRENT_SCAN_MODE == SCAN_MODE_IDLE) ? TRUE: FALSE;

	return RetVal;
}

int CHsvDvbsInstallation_mprescan_Priv::mGetNextScanMode (int CurrentMode)
{
	int		ScanMode = CURRENT_SCAN_MODE;

	if (CurrentMode == -1)
	{
		ScanMode = BLIND_SCAN_MODE;
	}
	else
	{
		if(CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE)
		{
			ScanMode = TABLE_BASED_SCAN_MODE;
		}
		else if(CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
		{
			CURRENT_TABLE_INDEX++;
			if (CURRENT_TABLE_INDEX >= TOTAL_NUM_OF_SATELLITES)
			{
        					ScanMode = SCAN_MODE_IDLE;
			}

		}
		else if (CURRENT_SCAN_MODE == BLIND_SCAN_MODE)
		{
			if (mInstStatus.BlindScanStarted == BlindScanLocked)
			{
				/* LNB Not Vacant. Start the Table based scan */
				ScanMode = ((mManualFrequencyModeSupported())? MANUAL_FREQUENCY_MODE: TABLE_BASED_SCAN_MODE);
			}
			else if (mInstStatus.BlindScanStarted == BlindScanNotLocked)
			{
				ScanMode = SCAN_MODE_IDLE;
				/* Lnb Vacant. End of Scan */
			}
		}
	}

	return ScanMode;
}

void CHsvDvbsInstallation_mprescan_Priv::mStopSdm(HsvDemux dmx)
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

Bool CHsvDvbsInstallation_mprescan_Priv::mGetSDSDFromStrapi(void)
{
	int i;
	int NumSdsds = 0;
	HSVSPTYPE(SatelliteDS, dvb, nit)    SatelliteDSDesc;
    
    mLnbSdsdList.NumofSDSDs = strapi_GetSize(HsvMain, HSVSPID(SatelliteDS, dvb, nit));
    
	for(i = 0; i < mLnbSdsdList.NumofSDSDs; i++ )
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&SatelliteDSDesc)))
        {
            mLnbSdsdList.SDSD[i] = SatelliteDSDesc;
			NumSdsds++;
		}
    }
	mLnbSdsdList.NumofSDSDs = NumSdsds;
    
	TraceNotice (m, "Num Of SDSD records mLnbSdsdList[%d] %d ", CURRENT_LNB_INDEX, mLnbSdsdList.NumofSDSDs);
    
	return 0;
}

/****************************************************************************
 * External functions
 ****************************************************************************/

/* provides IHsvPower		iprescanpow */

void CHsvDvbsInstallation_mprescan_Priv::iprescanpow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbsins_mPreScan" );
	mConstModuleLifeCycle = ConstInitialized;
	TraceDebug(m, "%s %d mPump %d ", __FUNCTION__, __LINE__, mPump);
}

void CHsvDvbsInstallation_mprescan_Priv::iprescanpow_TurnOn(void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
	mInitialise();
	/* TBD: make use of return value of the below function based on this we can skip TABLE 18 scan in error conditions
	        of xml file not there */


}
void CHsvDvbsInstallation_mprescan_Priv::iprescanpow_TurnOff(void)
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

/* provides IHsvSatelliteInstallation		iprescan	*/

/* Function to get the installation mode and status */
int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetCurrentInstallationState (int *mode, int *state)
{
	UNUSED(mode);
	UNUSED(state);
	return 0;
}

/* Functions for automatic installation + update installation */
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult			RetVal = err_BadParameter;
	iprescanparser_ExtractPreScanTableFromXml();
	TOTAL_NUM_OF_SATELLITES = iprescanparser_GetNumberOfPrescanEntries ();
	TraceNotice(m,"[ Total Number Of Satellites to search = %d ]",TOTAL_NUM_OF_SATELLITES);
	HsvLnbSettings		LnbSettings;

	TraceNotice(m,"TURNED_ON %d <%d %d %d> ",  TURNED_ON, Source, Lnb, Mode);
	if (TURNED_ON)
	{
		if(Source != HsvNoSource)
		{
			/* Currently supporting only service scan. Have to update VALID_MODE as features added */
			if (IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
			{
				SET_INS_STATE(StIdle);
				
				pmp_PmpSend(mPump, EvStart, Lnb);
				
				RetVal = err_Ok;
			}
		}
		else
		{
			TraceNotice (m, "Skip LNB as User has not selected this LNB for Installation ");
			/* Marking the LNB as free */
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				LnbSettings.LnbSettings[Lnb].LnbStatus = LnbFree;
				LnbSettings.LnbSettings[Lnb].UpdateInstallEnabled = FALSE;
				idvbset_SetLnbSettings (&LnbSettings);
			}

			/* Satellite Not Found */
			mInitialise();
			usleep(100000);
			iinsN_OnEvent(iinsN_EventSatelliteNotFound,Lnb);
		}
	}
	return RetVal;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberOfTvChannelsFound (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}
int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberofRadioChannelsFound (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}
int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberOfTvChannelsRemoved    (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberofRadioChannelsRemoved (int Lnb)
{
	UNUSED(Lnb);
	return 0;
}


/* Display the satellite Name per LNB. This should be used during pre-scan and service scan */
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSatelliteName (int Lnb, Nat16 *SatelliteName)
{
	/* GetSatellite Name will not be routed. So ignore */
	FResult		RetVal = err_NotSupported;
	
	return RetVal;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	return Retval;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	return Retval;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	return Retval;
}
	
/* Package information after the installation (service scan). But to be filled up by the Package Module */
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_IdentifyPackagesAvailable (void)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d  ", __FUNCTION__, __LINE__);
	return RetVal;
}
int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetTotalNumberOfPackagesFound (void)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d  ", __FUNCTION__, __LINE__);
	return RetVal;
}
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetPackageByIndex(int Index, HsvPackageStructure *Package)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d  ", __FUNCTION__, __LINE__);
	UNUSED (Index);
	UNUSED (Package);
	return RetVal;
}
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_SetUserPackageIndex(Nat32 PackageIndex)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d  ", __FUNCTION__, __LINE__);
	UNUSED (PackageIndex);
	return RetVal;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetUserPackageIndex(Nat32* PackageIndex, Bool* IsPackage)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d  ", __FUNCTION__, __LINE__);
	UNUSED (PackageIndex);
	return RetVal;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetInstalledSatellites (int mode, HsvInstalledSatellites *SatelliteEntries)
{
	FResult		RetVal = err_NotSupported;
	TraceErr(m," Wrong Routing !!! %s %d  ", __FUNCTION__, __LINE__);
	UNUSED (mode);
	UNUSED (SatelliteEntries);
	return RetVal;
}

/* Interfaces towards the Add Satellite */
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_InstallAddedSatellites (void)
{
	FResult		RetVal = err_NotSupported;
	return RetVal;
}
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_ResetAddedSatellites (void)
{
	FResult		RetVal = err_NotSupported;
	return RetVal;
}

/* Interfaces towards the Remove Satellite */
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_RemoveSatelliteEntry (int LnbNumber)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (LnbNumber);
	return RetVal;
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_ResetInstallation (void)
{
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSatelliteSignalStrength (int LnbNumber)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (LnbNumber);
	return RetVal;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSatelliteSignalQuality  (int LnbNumber)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (LnbNumber);
	return RetVal;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSITableIds(Nat16* NetworkID, Nat16* BouquetID)
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
	else if(CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE)
	{
		/* Canal Digital */
		*NetworkID = 0x0046;
		*BouquetID = 0xFFFF;
		RetVal = err_Ok;
	}

	TraceDebug(m,"%s %d CURRENT_TABLE_INDEX %d NetworkId %d BouquetId %d ", __FUNCTION__, __LINE__, CURRENT_TABLE_INDEX, *NetworkID, *BouquetID);

	return RetVal;
}

Nat32 CHsvDvbsInstallation_mprescan_Priv::iprescan_GetAttribute(int Mode, int AttributeId)
{
	UNUSED (Mode);
	UNUSED (AttributeId);
	return 0;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_SetAttribute(int Mode, int AttributeId, Nat32 Value)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (Mode);
	UNUSED (AttributeId);
	UNUSED (Value);
	return RetVal;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetScanProgressStatus (int Mode)
{
	int	ProgressBarStatus = 0;
	/* For Pre-Scan the logic of Progress Status bar is 
		25% -> For Table Based Scan		Remaining 75% -> BlindScan */

	if (CURRENT_SCAN_MODE == TABLE_BASED_SCAN_MODE)
	{
		ProgressBarStatus = 25 + ((CURRENT_TABLE_INDEX < TOTAL_NUM_OF_SATELLITES) ? (((CURRENT_TABLE_INDEX*100 /TOTAL_NUM_OF_SATELLITES) * 75) /100) : 75);
	}
	else if(CURRENT_SCAN_MODE == FALLBACK_BLINDSCAN_MODE)
	{
		ProgressBarStatus = 99;
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

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_GetPackageName (Nat32 PackageId, Nat16	*PackageName)
{
	FResult		RetVal = err_NotSupported;
	UNUSED (PackageId);
	UNUSED (PackageName);
	return RetVal;
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetFirstInstalledChannel(void)
{
	return 0;
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_UpdateConfigXmlStrings(char * PrescanXmlString,int PrescanXmlStringLen,char * SatellitePackageXmlString,int SatellitePackageXmlStringLen)
{
	return;
}

/* provides IPlfApiDvbsNotify		iprescanplfApidvbsN	*/

void CHsvDvbsInstallation_mprescan_Priv::iprescansatfrontendN_OnLockChanged(Bool LockState)
{
	/* Notifiation Handler for DVB-S platform FE. Thread seperating here */
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

void CHsvDvbsInstallation_mprescan_Priv::iprescansatfrontendN_OnBlindScanEnd(void)
{
	/* Notifiation Handler for DVB-S platform FE. Thread seperating here */
	pmp_PmpSend(mPump, EvBlindScanEnd, (Nat32)NULL);
}


/* provides IHsvDigitalScanData		iprescandata	*/

int CHsvDvbsInstallation_mprescan_Priv::iprescandata_GetInstallationVersion(void)
{
	return 0;
}

/* provides IHsvSdmControlNotifyEx		iprescanctrlN */

void CHsvDvbsInstallation_mprescan_Priv::iprescanctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
	HsvSatelliteList	PreScanTableSatellite;
	Nat16				NetworkId, TsId;

	TraceDebug (m, "%s %d eventid %d TURNED_ON %d scan mode %d value %d ", __FUNCTION__, __LINE__, eventid, TURNED_ON,CURRENT_SCAN_MODE,value);
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
				if ((PreScanTableSatellite.BouquetId != 0xFFFF) && ((value & iprescanctrlN_BAT) == iprescanctrlN_BAT))
				{
					if ((mInstStatus.TableCollectStatus == NotRequested) || (mInstStatus.TableCollectStatus == MatchingTsId))
					{
						DataRequested++;
						/*	1. Only bouquetId needs to be validated. (No TSID) GiveData Available
							2. Matching TSID already found. So both TSID and bouquet ID matching. Give Data Available */
						pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
					}
					else if (mInstStatus.TableCollectStatus == Requested)
					{
						/* TSID is yet to arrive. Only update the flag */
						mInstStatus.TableCollectStatus = MatchingBat;
					}
				}
				else if ((PreScanTableSatellite.NetworkId != 0xFFFF) && ((value & iprescanctrlN_NIT) == iprescanctrlN_NIT))
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
				else if ((PreScanTableSatellite.TsId != 0xFFFF) && ((value & iprescanctrlN_SDT) == iprescanctrlN_SDT))
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
			else
			{
				if(CURRENT_SCAN_MODE == MANUAL_FREQUENCY_MODE)
				{
					TraceNotice(m, "%s DataRequested %d", __FUNCTION__, DataRequested);
					DataRequested++;
				}
				pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
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

void CHsvDvbsInstallation_mprescan_Priv::FuncCheckSigLock(Nat32 Param)
{
	int RetVal, LnbNumber, LnbType, LockStatus, LockedFreq, Polarization, SymbolRate, IqMode, Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus,	&LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth );
	if ((RetVal == err_Ok) && (LockStatus != FALSE))
	{
  	    SET_INS_STATE(StSignalStrength);
	    pmp_PmpSend(mPump, EvSigStrStart, (Nat32)Param);
	}
	else
	{
		TraceNotice (m, "Tuning Failed ");
	}

}



int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSignalStrength(Nat32 Param)
{
	int retValue = 0;

	UNUSED(Param);
	retValue =GetDigitalSignalStrength();
	TraceNotice (m, " Rahul: %s %d SignalStrength=%d ",__FUNCTION__,__LINE__,retValue);

	return retValue;
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStartSigStrMeas(Nat32 Param)
{
    Bool RetVal = FALSE;

    RetVal = isigstr_StartSigStrMeasAll();

 	if (RetVal != err_Ok)
 	{
 	   TraceNotice (m, " Error in isigstr_StartSigStrMeasAll ");
 	}
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStartSigStrTune(Nat32 LnbNumber)
{
	    Bool	RetVal       = FALSE;
		int     LnbType      = SatInfoCache[LnbNumber ].LnbType;
		int     Frequency    = SatInfoCache[LnbNumber ].Frequency;
	    int     Polarization = SatInfoCache[LnbNumber ].Polarization;

		RetVal = satfeapi_SatelliteFrontEndTune (LnbNumber, LnbType, Frequency, 0,Polarization, 0, -1, -1, -1, -1, -1, -1);

        if (RetVal != err_Ok)
		{
			TraceNotice (m, " Error in SatelliteFrontendTune ");
			
		}
		else
		{
		    SET_INS_STATE(StSignalStrength);
		}
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_StopSignalStrengthMeas(int Param)
{

  	SET_INS_STATE(StSignalStrength);
	pmp_PmpSend(mPump, EvSigStrStop, (Nat32)Param);
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_StartSignalStrengthMeas(int Param)
{

  	SET_INS_STATE(StStart);
	pmp_PmpSend(mPump, EvSigStrStart, (Nat32)Param);
}

void CHsvDvbsInstallation_mprescan_Priv::FuncStopSigStrMeas(Nat32 Param)
{

  SET_INS_STATE(StIdle);
  isigstr_StopSigStrMeasAll();
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSignalQuality(Nat32 Param)
{

    Nat32 lReturn = 0;


    lReturn = QssmGetSignalStrength( );
    return lReturn;

}


Nat32 CHsvDvbsInstallation_mprescan_Priv::QssmGetSignalStrength( )
{
    Bool  valid = FALSE;
    Nat32 retval = 0;
    Nat32  strength = 0;
    
    qssm_GetMeasValid(WINDOWID, &valid, &retval);

    if ( valid )
    {
        qssm_GetSigStrength(WINDOWID, &strength, &retval);
    }
    return strength;
}

Nat32 CHsvDvbsInstallation_mprescan_Priv::GetDigitalSignalStrength(void)
{
    Nat32 SignalStrength = 0;
    Nat32 retval = 0;
    Nat32 MinStrength = 0;
    Nat32 MaxStrength = 1;

    vssm_GetSigStrengthRange(WINDOWID, &MinStrength, &MaxStrength, &retval);
    
    if( retval == err_Ok)
    {
        SignalStrength = (((vssmGetSignalStrength()- MinStrength) * 100) / ((MaxStrength - MinStrength) ? (MaxStrength - MinStrength) : 1));        
    }
    
    return SignalStrength;
}

/*-------------------------------------------------------------------------------------------------*/
Nat32 CHsvDvbsInstallation_mprescan_Priv::vssmGetSignalStrength(void)
/*-------------------------------------------------------------------------------------------------*/
{
    Bool  valid = FALSE;
    Nat32 retval = 0;
    Nat32  strength = 0;
    
    vssm_GetMeasValid(WINDOWID, &valid, &retval);

    if ( valid )
    {
        vssm_GetSigStrength(WINDOWID, &strength, &retval);
    }

    return strength;    
}


Bool CHsvDvbsInstallation_mprescan_Priv::mManualFrequencyModeSupported(void)
{
	Bool retval = FALSE;
	int Country = 0;
	Nat32 Frequency;
	
	Country = sysset_GetSystemCountry();
	
	TraceNotice (m, "%s Country %d ", __FUNCTION__, Country);
	switch(Country)
	{
		case cids_CountryNorway:
		case cids_CountrySweden:
		case cids_CountryFinland:
		case cids_CountryDenmark:
			Frequency = pins_GetAttribute(PRESCAN_MODE, IHsvSatelliteInstallation_AttributeFrequency);
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
	
	TraceNotice (m, "%s retval %d ", __FUNCTION__, retval);
	return retval;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_StoreManualInstallationValues (void)
{
	return 0;
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_EnableUnicable (int LnbNumber, Bool Enable)
{
}

FResult CHsvDvbsInstallation_mprescan_Priv::iprescan_StartPredefinedListCopy (void)
{
	return 0;
}

void CHsvDvbsInstallation_mprescan_Priv::iprescandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
}

void CHsvDvbsInstallation_mprescan_Priv::iprescandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}

void CHsvDvbsInstallation_mprescan_Priv::iprescandata_SyncComplete(void)
{
}

int CHsvDvbsInstallation_mprescan_Priv::iprescan_GetNumberOfDatabaseRecords(int TSDataOnly)
{
	return 0;
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)
{
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear)
{
}

void CHsvDvbsInstallation_mprescan_Priv::iprescan_SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData)
{
}

