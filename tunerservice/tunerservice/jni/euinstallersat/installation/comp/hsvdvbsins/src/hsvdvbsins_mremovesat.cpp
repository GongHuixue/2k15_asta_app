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
 *	C Source:		hsvdvbsins_mremovesat.c
 *	Instance:		
 *	Description:	
 *	%created_by:	  aneeshc %
 *	%date_created:	  Fri Apr 19 16:08:31 2013 %
 *
**********************************************************************/

#include "_hsvdvbsins_mremovesat.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsins_mremovesat")

/****************************************************************************
 * Macros and types
 ****************************************************************************/










/****************************************************************************
 * Static variables
 ****************************************************************************/

Pump CHsvDvbsInstallation_mremovesat_Priv::s__mPump;

int CHsvDvbsInstallation_mremovesat_Priv::s__mConstModuleLifeCycle;


int CHsvDvbsInstallation_mremovesat_Priv::s__ts_from_index  = 0;
 /* static variable which will be pointing to current TS index in the DB while the removal process is ON*/
int CHsvDvbsInstallation_mremovesat_Priv::s__ts_to_index  = 0;
  /* static variable which will be pointing to last TS index in the DB while the removal process is ON*/
int CHsvDvbsInstallation_mremovesat_Priv::s__LnbsToRemove = 0;


/****************************************************************************
 * Static functions
 ****************************************************************************/








/*********************************************************************************
  * @brief Pump Handler function
  * @param[in] Events
  * @param[in] Parameters passed to the handler functions
  * @returns void
  **********************************************************************************/
void CHsvDvbsInstallation_mremovesat_Priv::mPumpHandler(int value, Nat32 param)
{
	Nat32	LnbNum;
    HsvLnbSettings  LnbSettings;

	switch(value)
	{
	case EvStart:
        TraceNotice (m, "Cur Lnb 0x%x ", (int)param);
		LnbNum = GetNextLnbToRemove (param);
        TraceNotice (m, "LnbToRemove %d ", (int)LnbNum);
		if (LnbNum == INVALID_LNB)
		{
            TraceNotice (m, "All Completed. Sending Rmeoval completed ntf");
			pgdb_CommitTable(pgdbconst_Satellite);
			pgdb_EnableAutoCommit(TRUE);
			idvbset_SaveSatelliteSettingsToPersistent();
			idvbset_CommitSatelliteSettingsToPersistent ();	
			iinsN_OnEvent (iinsN_EventSatLnbRemovalCompleted,param);
			FuncParamReset(LnbNum);		
		}
		else
		{
            TraceNotice (m, "Triggering Removal ");
			FuncParamReset(LnbNum);
			FuncInitialise(LnbNum);
		}
		break;
	case EvSatInfoDelStart:
		FuncRemoveSatInfo(param);
		break;
	case EvTSInfoDelStart:
	case EvPumpLimitReached:
		FuncRemoveTSSatInfo(param);
		break;
    case EvLnbRemoved:
        /* Mark Lnb as Free */
        /* ANEESH: TODO: How to mark the duplicates as free */
        if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
        {
            TraceNotice (m, "Setting LNB As free ");
            LnbSettings.LnbSettings[param].LnbStatus = LnbFree;
			LnbSettings.LnbSettings[param].UpdateInstallEnabled = FALSE;
            idvbset_SetLnbSettings (&LnbSettings);
        }
	    pmp_PmpSend(mPump, EvStart, (Nat32)param);
		break;
	}
}

/*********************************************************************************
  * @brief Initialises the TS Info indexes as the func pgdb_GetRange shall be called only once.
  * @param[in] LNB Number
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::FuncInitialise(Nat32 Param)
{
	HsvPgdatDigTSData		TSInfoData;
	Bool					status = FALSE;
	Nat32					ts_from=0,ts_to=0;

	TSInfoData.LnbNumber = Param;
	if((status = pgdb_GetRange (PTC_TABLE , 1, (Address)&TSInfoData , (int*)&ts_from , (int*)&ts_to)) != TRUE)
	{
		TraceNotice(m,"%s: %u-pgdb_GetRange returned %u. No channels installed for LNB %d   \n", __FUNCTION__, __LINE__, status, (int)Param);
		ts_from_index = 0;
		ts_to_index = 0;
	}
	else
	{
		ts_from_index = ts_from;
		ts_to_index      = ts_to;
	}

	pmp_PmpSend(mPump, EvSatInfoDelStart, (Nat32)Param);
}

/*********************************************************************************
  * @brief This function removes the TS and its corresponding service INFO in a loop taking care of the
  * PUMP Limit in order to avoid conflict with the Watch Dog
  * @param[in] LNB Number
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::FuncRemoveTSSatInfo(Nat32 Param)
 {

	HsvPgdatDigTSData		TSInfoData;
	HsvPgdatDigServiceData	ServiceInfoData;
	HsvPgdatPresetData		PresetInfoData;
	Bool					status = FALSE, flag = TRUE;
	int						service_from=0,service_to=0,ts_count=0,service_count=0;
	static int				service_index = 0;

	for (ts_count = ts_to_index; (ts_count >= ts_from_index); ts_count--)
	{
		flag = TRUE;
		status = pgdb_GetByIndex (PTC_TABLE, ts_count   ,(Address)&TSInfoData);
		if (status != TRUE)
		{
			TraceNotice(m,"%s: %u-pgdb_GetByIndex returned %u \n", __FUNCTION__, __LINE__, status);
			flag = FALSE;
		}
		else
		{

			ServiceInfoData.Tpid = TSInfoData.Tpid;
			status = pgdb_GetRange (SERVICE_TABLE , 1, (Address)&ServiceInfoData , (int*)&service_from , (int*)&service_to);

			if (status == TRUE)
			{
				for (service_count = service_to; (service_count >= service_from); service_count--)
				{
					if((status = pgdb_GetByIndex (SERVICE_TABLE, service_count ,(Address)&ServiceInfoData)) != TRUE)
					{
						TraceNotice(m,"%s: %u-pgdb_GetByIndex returned %u \n", __FUNCTION__, __LINE__, status);
						flag = FALSE;
						break;
					}

					PresetInfoData.PresetNumber = ServiceInfoData.PresetNumber;

					if((status = pgdb_GetByKey( PRESET_TABLE,(Address) &PresetInfoData)) != TRUE)
					{
						TraceNotice(m,"%s: %u-pgdb_GetByKey returned %u \n", __FUNCTION__, __LINE__, status);
					}
					else if(( status = pgdb_Delete(PRESET_TABLE, (Address)&PresetInfoData)) != TRUE)
					{
						TraceNotice(m,"%s: %u-pgdb_Delete returned %u \n", __FUNCTION__, __LINE__, status);
					}
					else if(( status = pgdb_Delete(SERVICE_TABLE, (Address)&ServiceInfoData)) != TRUE)
					{
						TraceNotice(m,"%s: %u-pgdb_Delete returned %u \n", __FUNCTION__, __LINE__, status);
					}
					else
					{
						service_index ++;
						if((service_index % PUMP_LIMIT) == 0)
						{
							pmp_PmpSend(mPump, EvPumpLimitReached, (Nat32)Param);
							flag = FALSE;
							break;
						}
					}
				}
			}

			if (((flag == TRUE) && (status = pgdb_Delete(PTC_TABLE, (Address)&TSInfoData)) == TRUE) )
			{
				ts_to_index--;
				service_index = 0;
				if(ts_from_index > ts_to_index)
				{
					pmp_PmpSend(mPump, EvLnbRemoved, (Nat32)Param);
					break;
				}
			}
			else
			{
				TraceNotice(m,"%s: %u-pgdb_Delete returned %u \n", __FUNCTION__, __LINE__, status);
				break;
			}
		}
	}

}

/*********************************************************************************
  * @brief :This function removes the Satellite Info from the DB
  * @param[in] LNB Number
  * @returns void
  **********************************************************************************/
void CHsvDvbsInstallation_mremovesat_Priv::FuncRemoveSatInfo(Nat32 Param )
{
	HsvPgdatDigSatInfoData	SatInfo;
	Bool status = FALSE;

	SatInfo.LnbNumber = Param;

	pgdb_EnableAutoCommit(FALSE);
	if ((status = pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatInfo)  )!= TRUE)
	{
		TraceNotice(m,"%s: %u-pgdb_GetByKey returned %u \n", __FUNCTION__, __LINE__, status);
		pmp_PmpSend(mPump, EvLnbRemoved, (Nat32)Param);
	}
	else if (( status = pgdb_Delete(SAT_INFO_TABLE, (Address)&SatInfo) )!= TRUE)
	{
		TraceNotice(m,"%s: %u-pgdb_Delete returned %u \n", __FUNCTION__, __LINE__, status);
	}
	else
	{
		if ((ts_from_index == 0) && (ts_to_index == 0))
        {
    		pmp_PmpSend(mPump, EvLnbRemoved, (Nat32)Param);
        }
        else
        {
    		pmp_PmpSend(mPump, EvTSInfoDelStart, (Nat32)Param);
        }
	}
}

/*********************************************************************************
  * @brief :This function resets the static variables holding the TS info Indexes in the DB after removing
  * the complete Satellite info
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::FuncParamReset(Nat32 num)
{

	ts_from_index = 0;
	ts_to_index = 0;

	UNUSED(num);
}

Nat32 CHsvDvbsInstallation_mremovesat_Priv::GetNextLnbToRemove (Nat32 CurrentLnb)
{
	Nat32		Lnb = 0;
	switch (CurrentLnb)
	{
	case	INVALID_LNB:
		Lnb = ((LnbsToRemove & pins_SatLnb1) ? 0 :  ((LnbsToRemove & pins_SatLnb2) ? 1: ((LnbsToRemove & pins_SatLnb3) ? 2: ((LnbsToRemove & pins_SatLnb4) ? 3 : INVALID_LNB))));
		break;
	case	0:
		Lnb = ((LnbsToRemove & pins_SatLnb2) ? 1: ((LnbsToRemove & pins_SatLnb3) ? 2: ((LnbsToRemove & pins_SatLnb4) ? 3 : INVALID_LNB)));
		break;
	case	1:
		Lnb = ((LnbsToRemove & pins_SatLnb3) ? 2: ((LnbsToRemove & pins_SatLnb4) ? 3 : INVALID_LNB));
		break;
	case	2:
		Lnb = ((LnbsToRemove & pins_SatLnb4) ? 3 : INVALID_LNB);
		break;
	case	3:
	default:
		Lnb = INVALID_LNB;
		break;
	}

	return Lnb;
}
/*********************************************************************************
  * @brief :This function starts the PUMP Engine
  * @param[in] LNB Number
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::RemoveSatInfo(Nat32 Param)
{
	Nat32	Lnb;

	LnbsToRemove = Param;
	
	Lnb = INVALID_LNB;
	iinsN_OnEvent (iinsN_EventSatLnbRemovalStarted,Param);
	pmp_PmpSend(mPump, EvStart, (Nat32)Lnb);
}


/****************************************************************************
 * External functions
 ****************************************************************************/



/*********************************************************************************
  * @brief :API provided to remove Satellite info
  * @param[in] LNB Number
  * @returns void
  **********************************************************************************/

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_RemoveSatelliteEntry(int LnbNumber)
{
	FResult	RetVal = err_Ok;

	RemoveSatInfo(LnbNumber);

	return RetVal;
}


/*********************************************************************************
  * @brief :This function initialises PUMP Engine
  * @param[in] void
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::iremovesatpow_Init (void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbsins_mRemoveSat" );
    mConstModuleLifeCycle = ConstInitialized;
	TraceNotice(m, "%s %d mPump %d\n", __FUNCTION__, __LINE__, mPump);
}


/*********************************************************************************
  * @brief :
  * @param[in] void
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::iremovesatpow_TurnOn (void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
}


/*********************************************************************************
  * @brief :
  * @param[in] void
  * @returns void
  **********************************************************************************/

void CHsvDvbsInstallation_mremovesat_Priv::iremovesatpow_TurnOff (void)
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetCurrentInstallationState (int *mode, int *state)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StartInstallation(int Source, int Lnb, int Mode)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StopInstallation(void)
{
	return 0;
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_ResetInstallation (void)
{
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberOfTvChannelsFound      (int Lnb)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberofRadioChannelsFound   (int Lnb)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberOfTvChannelsRemoved    (int Lnb)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberofRadioChannelsRemoved (int Lnb)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSatelliteName (int Lnb, Nat16 *SatelliteName)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberOfDigitalChannelsAdded(void)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberOfDigitalChannelsRemoved(void)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberOfDigitalChannelsMoved (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_IdentifyPackagesAvailable (void)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetTotalNumberOfPackagesFound (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetPackageByIndex(int Index, HsvPackageStructure *Package)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_SetUserPackageIndex(Nat32 PackageIndex)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetUserPackageIndex(Nat32* PackageIndex, Bool* IsPackage)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetInstalledSatellites (int mode, HsvInstalledSatellites *SatelliteEntries)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_InstallAddedSatellites (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_ResetAddedSatellites (void)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSatelliteSignalStrength (int LnbNumber)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSatelliteSignalQuality  (int LnbNumber)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_LoadManualInstallationDefaultValues (void)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StoreManualInstallationValues (void)
{
	return 0;
}

Nat32 CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}
FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_SetAttribute(int Mode, int AttributeId, Nat32 Value)
{
	return 0;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetScanProgressStatus (int Mode)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSITableIds(Nat16* NetworkID, Nat16* BouquetID)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetPackageName (Nat32	PackageId, Nat16	*PackageName)
{
	return 0;
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_EnableUnicable (int LnbNumber, Bool Enable)
{
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StopSignalStrengthMeas(int LnbNumber)
{
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSignalQuality(Nat32 Param)
{
	return 0;
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StartSignalStrengthMeas(int LnbNumber)
{
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetSignalStrength(Nat32 param)
{
	return 0;
}

FResult CHsvDvbsInstallation_mremovesat_Priv::iaddremove_StartPredefinedListCopy (void)
{
	return 0;
}


int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetFirstInstalledChannel(void)
{
	return 0;
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_UpdateConfigXmlStrings(char * PrescanXmlString,int PrescanXmlStringLen,char * SatellitePackageXmlString,int SatellitePackageXmlStringLen)
{
	return;
}

int CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetNumberOfDatabaseRecords(int TSdataOnly)
{
	return 0;
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSdataOnly)
{
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear)
{
	return;
}

void CHsvDvbsInstallation_mremovesat_Priv::iaddremove_SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData)
{
	return;
}

