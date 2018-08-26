/**********************************************************************
 *
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
*	C Source:		hsvdvbsins_m.c
*	Instance:		
*	Description:	
*	%created_by:	  anuma %
*	%date_created:	  Fri May 10 18:12:35 2013 %
*
**********************************************************************/

#include <unistd.h>
#include "_hsvdvbsins_m.h"

#ifndef __cplusplus

#else

#endif





TRACESYMBOL(m, "s2/installation/hsvdvbsins_m")











ModuleLifeCycle CHsvDvbsInstallation_m_Priv::s__mModuleLifeCycle = TurnedOff;

CachedUniqueId	CHsvDvbsInstallation_m_Priv::s__UniqueServiceListCache[MAX_SAT_SERVICES_SUPPORTED];






/****************************************************************************
 * Static variables
 ****************************************************************************/

Pump CHsvDvbsInstallation_m_Priv::s__mPump;

TypeInstallationStatus CHsvDvbsInstallation_m_Priv::s__InsStatus;


/* Creating the new pump handler for state machine that collects and build the dynamic package list from BAT( for Fransat )
 * NOTE : PackageBuildingActionMatrix is mapped for event routing
 */






















FunctionNat32 CHsvDvbsInstallation_m_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
							/*  StIdle,							StSourceSetupWait,				StDigital,						StPackageInstal,					StGenericInstall,					StSorting,						StMiniPrescanInstallation,			StPackageParsing,					StDatabaseSync						*/
/* EvStart              */  {	FNADDR(FuncStartInstallation),	NULL,							NULL,							NULL,								NULL,								NULL,							NULL,								NULL, 								NULL  						},/* EvStart */
/* EvStop				*/  {	NULL,							FNADDR(FuncStopInstallation),	FNADDR(FuncStopInstallation),	FNADDR(FuncStopInstallation),		FNADDR(FuncStopInstallation),		FNADDR(FuncStopInstallation),	FNADDR(FuncStopSemiStandbyInstall),	FNADDR(FuncStopPackageParsing),		FNADDR(FuncStopDatabaseSync)},/* EvStop */  
/* EvSourceSetupApplied */  {	NULL,							FNADDR(FuncSourceSetupApplied),	NULL,							NULL,								NULL,								NULL,							NULL, 								NULL, 								NULL						},/* EvSourceSetupApplied */
/* EvInstallStart		*/	{	NULL,							NULL,							NULL,							FNADDR(FuncStartPackageInstall),	FNADDR(FuncStartGenericInstall),	NULL,							NULL, 								NULL,								NULL 						},/* EvInstallStart	*/
/* EvInstallComplete	*/	{	NULL,							NULL,							NULL,							FNADDR(FuncPackageInstallComplete),	FNADDR(FuncGenericInstallComplete),	NULL,							NULL,								FNADDR(FuncPackagePasingComplete),	NULL 						},/* EvInstallComplete */
/* EvSorting            */  {	NULL,							NULL,							NULL,							NULL,								NULL,								FNADDR(FuncSorting),			NULL,								NULL,								NULL 						},/* EvSorting */
/* EvSortComplete		*/  {	NULL,							NULL,							NULL,							NULL,								NULL,								FNADDR(FuncSortComplete),		NULL,								NULL,								NULL 						}, /* EvSortComplete */
/* EvInstallFailed  */      {   NULL,							NULL,							NULL,							FNADDR(FuncPackageInstallFailed),   FNADDR(FuncGenericInstallFailed),   NULL,							NULL,								NULL,								NULL 						}, /* EvInstallFailed  */
/* EvMiniPrescanResult */	{	NULL,							NULL,							NULL,							NULL,								NULL,								NULL,							FNADDR(FuncCheckSemiStandbyPrescan),NULL,								NULL 						},
/* EvPerformDatabaseSync*/	{	NULL,							NULL,							NULL,							NULL,								NULL,								NULL,							NULL,								NULL,								FNADDR(FuncPerformDatabaseSync)},
/* EvDatabaseSyncComplete*/	{	NULL,							NULL,							NULL,							NULL,								NULL,								NULL,							NULL,								NULL,								FNADDR(FuncDatabaseSyncComplete)}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/









void CHsvDvbsInstallation_m_Priv::mPumpHandler(int event, Nat32 param)
{
    if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
	{
		TraceDebug (m, "%s %d event %d param %d state %d ", __FUNCTION__, __LINE__, event, (int)param, GET_INS_STATE);
		if(EventActionMatrix[event][GET_INS_STATE] != NULL)
		{
			TraceNotice (m, "%s %d event %d param %d state %d ", __FUNCTION__, __LINE__, event, (int)param, GET_INS_STATE);
			FPCALL(EventActionMatrix[event][GET_INS_STATE])(param);
		}
	}
}

void CHsvDvbsInstallation_m_Priv::FuncStartInstallation(Nat32 param)
{
	TraceNotice (m, "%s %d InsStatus.Mode %d param %d ", __FUNCTION__, __LINE__, InsStatus.Mode, (int)param);
	
	mInitInstallationValues(param);

	mctl_Stop(HsvMain); 
	ibckInstall_DisableBackgroundInstallation ();
	pgdb_SelectTable(pgdbconst_Satellite);
	
	if( (InsStatus.Mode == AUTO_MODE) || (InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == AUTOUPDATE_MODE) || (InsStatus.Mode == BCKGNDUPDATE_MODE) || (InsStatus.Mode == PRESCAN_MODE) || (InsStatus.Mode == MINIPRESCAN_MODE) || (InsStatus.Mode == CAM_NIT_INSTALLATION_MODE))
	{
		pgdb_EnableAutoCommit(FALSE);
	}
	/* If prescan is done for the first LNB clear the database from RAM. 
		If prescan or service scan does a cancel, then Stop will be triggered.
		Inside Stop the loading from flash will be done */
	if (InsStatus.Mode == (PRESCAN_MODE | AUTO_MODE))
	{
		/* In case of prescan triggered from Reinstall menu mode will be passed as	
			PRESCAN_MODE | AUTO_MODE. So clear table. and make mode as PRESCAN only */
		if (param == 0)
		{
			pgdb_SaveChannelMapsToBackup ();
			/* Setting Database as  RAM based */
			pgdb_SelectChannelDatabase (pgdb_TempDatabase);
			pgdb_ClearTable(CURRENT_DATABASE_TABLE);
			pgdb_EnableAutoCommit(FALSE);
		}
		InsStatus.Mode = PRESCAN_MODE;
	}
	if ((InsStatus.Mode == AUTOUPDATE_MODE) || (InsStatus.Mode == MINIPRESCAN_MODE) || (InsStatus.Mode == UPDATE_MODE))
	{
		ipackage_IdentifyPackagesAvailable();
	}
	if (InsStatus.Mode == ADDSAT_MODE)
	{
		/* ANEESH: TODO: Verify this part is correct */
		pgdb_SaveChannelMapsToBackup ();
	}
	switch(InsStatus.Mode)
    {
        case AUTO_MODE:
		case CAM_NIT_INSTALLATION_MODE:
		case ADDSAT_MODE:
			//pgdb_ClearTable(pgdb_GetCurrentTable());
			TraceDebug (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
			mInitInstallationPass(TRUE);
            break;
        case UPDATE_MODE:
        case AUTOUPDATE_MODE:
		case MINIPRESCAN_MODE:
		case BCKGNDUPDATE_MODE:
		case SSBYUPDATE_MODE:
            TraceDebug (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
			mInitInstallationPass(TRUE);
            break;
        case MANUAL_MODE:
			TraceDebug (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
            mInitInstallationPass(FALSE);
            break;
        case PRESCAN_MODE:
			TraceDebug (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
			mInitInstallationPass(TRUE);
            break;
        case PACKAGE_PARSING_MODE:
//			TraceNotice(m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
            TraceNotice (m, "%s %d Gokul mFuncStartPackageParsing InsStatus.Mode %d param %d ", __FUNCTION__, __LINE__, InsStatus.Mode, (int)param);
            mFuncStartPackageParsing();
            break;
        default:
			TraceNotice (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
            break;
    }   
		TraceDebug (m, "%s %d InsStatus.Mode before If() %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
		if((InsStatus.Mode == UPDATE_MODE)||(InsStatus.Mode == BACKGROUND_MODE)||(InsStatus.Mode == MANUAL_MODE))
		{
			TraceDebug (m, "%s %d InsStatus.Mode inside if() %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
			pgdb_MasterEnableEvents(TRUE);
		}
}

void CHsvDvbsInstallation_m_Priv::FuncStopInstallation(Nat32 param)
{
	HsvLnbSettings				LnbSettings;
	TraceNotice (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
	switch(InsStatus.Mode)
    {
        case AUTO_MODE:
		case UPDATE_MODE:
        case AUTOUPDATE_MODE:
		case ADDSAT_MODE:
		case BCKGNDUPDATE_MODE:
		case CAM_NIT_INSTALLATION_MODE:
		case SSBYUPDATE_MODE:
			if (GET_INS_STATE == StGenericInstall)
			{
				hsvdvbsgeneric_ins_StopInstallation();
			}
			else
			{
				ipackageins_StopInstallation();
			}
			pgdb_LoadTable(pgdb_GetCurrentTable());	
			/* Changing the database back to SQLITE as user has stopped installation */
//			pgdb_SelectChannelDatabase (pgdb_SqliteDatabase);
			UnBlockDestination();
			if ( InsStatus.Mode == AUTO_MODE ||
				 InsStatus.Mode == ADDSAT_MODE || InsStatus.Mode == CAM_NIT_INSTALLATION_MODE)
			{
				idvbset_LoadLnbParametersFromPersistent();
                mReloadUnicableSetting ();
				pgdb_LoadChannelMapsFromBackup ();
			}
			SET_INS_STATE(StIdle);
            break;
        case MANUAL_MODE:
			ipackageins_StopInstallation();
			SET_INS_STATE(StIdle);
            break;
        case PRESCAN_MODE:
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
				if(LnbSettings.ConnectionType == LnbConnectionSatIp)
				{
					isatipprescan_StopInstallation();
				}
				else
				{
					iprescan_StopInstallation();
				}
			}

			/*pgdb_LoadTable(pgdb_GetCurrentTable());*/
			UnBlockDestination();
			SET_INS_STATE(StIdle);
			break;
        default:
			break;
    }
	
	UNUSED(param);
}

void CHsvDvbsInstallation_m_Priv::FuncSourceSetupApplied(Nat32 param)
{
	FResult	RetVal;
	int		SetValue;
	Nat16	PackageGroupId = 0;
	HsvLnbSettings				LnbSettings;
	TraceDebug (m, "%s %d TURNED_ON %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, TURNED_ON, InsStatus.Mode);
	
    SET_INS_STATE(StDigital);
	
	switch(InsStatus.Mode)
    {

        case AUTO_MODE:
		case CAM_NIT_INSTALLATION_MODE:
			/* Auto installation works directly on RAM DB. So no need to do a database sync */
					/* This is sync done from SQLITE to Temp. Which will happen during start of installation */
			SET_INS_STATE(StDigital);
			ipackage_LoadPackageGroupInfo ();
			/* Identify whether its package only or All Satellite. Based on that start the installation */
			SetValue = idvbset_GetAttribute (idvbset_AttributePackageId);
			RetVal = ipackage_GetPackageGroupId (SetValue, &PackageGroupId);
			TraceNotice (m, "PackageId %d RetVal %d PackageGroupId %d ",SetValue, RetVal, PackageGroupId);
			if ((RetVal != err_Ok) || (PackageGroupId == 0))
			{
				TraceNotice (m, "InstallStart Sent to Generic ");
				/* Predefined list only */
				SET_INS_STATE (StGenericInstall);
				pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);			
				InsStatus.Lnb = 0;
			}
			else
			{				
				/* For operator profile installation, there is no prescan done by Installer, but by CAM. Hence we need to make the DB empty */
				if (SetValue == OP_PROFILE_PACKAGE_ID)
				{
					pgdb_SelectChannelDatabase (pgdb_TempDatabase);
					pgdb_ClearTable(CURRENT_DATABASE_TABLE);
					pgdb_EnableAutoCommit(FALSE);
				}

				TraceNotice (m, "InstallStart Sent to Package ");
				/* Indicates not a homing based package */
				SET_INS_STATE (StPackageInstall);
				pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);			
			}
			break;
		case UPDATE_MODE:
		case BCKGNDUPDATE_MODE:
		case AUTOUPDATE_MODE:
		case MINIPRESCAN_MODE:
		case SSBYUPDATE_MODE:
			SET_INS_STATE(StDatabaseSync);
			InsStatus.FromDatabaseId = pgdb_SqliteDatabase;
			InsStatus.ToDatabaseId = pgdb_TempDatabase;
			InsStatus.TableInCopy = SAT_INFO_TABLE;
			InsStatus.IndexToCopy = 0;
			TraceNotice (m, " Database sync From %d to %d ", InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
			/*SyncDatabases is not required as Db sync is done from Tvprovider*/
			pmp_PmpSend(mPump, EvDatabaseSyncComplete, (Nat32)NULL);
			
			break;
		case ADDSAT_MODE:
			SET_INS_STATE (StGenericInstall);
            pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);			
            InsStatus.Lnb = INVALID_LNB;
			break;
        case MANUAL_MODE:
			ipackage_LoadPackageGroupInfo ();
			hsvdvbsgeneric_ins_StartInstallation(HsvMain, InsStatus.Lnb, InsStatus.Mode);
            break;
        case PRESCAN_MODE:
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
				if(LnbSettings.ConnectionType == LnbConnectionSatIp)
				{
					isatipprescan_StartInstallation(HsvMain, InsStatus.Lnb, InsStatus.Mode);
				}
				else
				{
					if(InsStatus.SkipInstallation == TRUE)
					{
						TraceNotice(m,"%s: %d: %d",__FUNCTION__,__LINE__,InsStatus.SkipInstallation);
						iprescan_StartInstallation(HsvNoSource, InsStatus.Lnb, InsStatus.Mode);
					}
					else
					{
						iprescan_StartInstallation(HsvMain, InsStatus.Lnb, InsStatus.Mode);
					}
				}
			}
			break;
        default:
			break;
    }   
	
	UNUSED(param);
}

void CHsvDvbsInstallation_m_Priv::FuncSorting(Nat32 param)
{
	int		PackageIndex = 0;
	
	
	switch(InsStatus.Mode)
    {
        case AUTO_MODE:
		case UPDATE_MODE:
		case ADDSAT_MODE:
        case AUTOUPDATE_MODE:
		case BCKGNDUPDATE_MODE:
		case CAM_NIT_INSTALLATION_MODE:
		case SSBYUPDATE_MODE:
			/* ServiceScan + Update should read the proper package ID */
			PackageIndex = idvbset_GetAttribute (idvbset_AttributePackageId);
            break;
        case MANUAL_MODE:
		default:
			/* Manual should add the services at the end. So treat as NO SORTING (PackageId = 0) */
			break;
	}

	TraceNotice (m, "Invoking Sort PackageId %d  ",PackageIndex); 
	ipackagesort_Sort(PackageIndex);
}

void CHsvDvbsInstallation_m_Priv::FuncSortComplete(Nat32 param)
{
	FResult	RetVal;
	int		SetValue;
	Nat16	PackageGroupId = 0;
	UNUSED(param);
	TraceNotice (m, " Sort Completed... Calling to update the flash ... ");
	pgdb_CommitTable(pgdb_GetCurrentTable());
	pgdb_SaveChannelMapsToBackup ();

	mInitInstallationValues(InsStatus.Lnb);
	switch(InsStatus.Mode)
    {
        case AUTO_MODE:
		case CAM_NIT_INSTALLATION_MODE:
			SetUpdateInstallEnabling ();
			UnBlockDestination();
			insN_OnEvent(iinsN_EventSortCompleted,InsStatus.Lnb);
			SetValue = idvbset_GetAttribute (idvbset_AttributePackageId);
			RetVal = ipackage_GetPackageGroupId (SetValue, &PackageGroupId);
			TraceNotice (m, "PackageId %d RetVal %d PackageGroupId %d ",SetValue, RetVal, PackageGroupId);
			
			pgdb_SelectChannelDatabase(pgdb_TempDatabase); 
			
            if ((RetVal != err_Ok) || (PackageGroupId == 0))
            {
                TraceNotice(m,"clearing Barker Mux Details after generic installation");
                hsvdvbsgeneric_ins_WriteBarkerMuxData();
			}
            else if (PackageGroupId != 0)
            {
                TraceNotice(m,"Write Barker Mux Details into RAM");
                ipackageins_WriteBarkerMuxData();
			}
			break;
		case UPDATE_MODE:
        case AUTOUPDATE_MODE:
		case ADDSAT_MODE:
		case BCKGNDUPDATE_MODE:
		case SSBYUPDATE_MODE:
				UnBlockDestination();
			insN_OnEvent(iinsN_EventSortCompleted,InsStatus.Lnb);
            break;
        case MANUAL_MODE:
			insN_OnEvent(iinsN_EventSortCompleted,InsStatus.Lnb);
			break;
		default:
			break;
	}
	pgdb_EnableAutoCommit (TRUE);	
}

void CHsvDvbsInstallation_m_Priv::FuncStartPackageInstall(Nat32 param)
{
	InsStatus.Lnb = 0;
	TraceNotice (m, "Starting the package install ");
    iutil_ResetData ();
	/* Start the installation of the corresponding package */
	ipackageins_StartInstallation(HsvMain, InsStatus.Lnb, InsStatus.Mode);
}

void CHsvDvbsInstallation_m_Priv::FuncPackageInstallComplete(Nat32 param)
{
	int		SetValue;

	/* Check Package only or not. If package only, start the sorting */
	SetValue = idvbset_GetAttribute (idvbset_AttributePackageOnly);
	//TraceNotice (m, "SEtValue %d ",  SetValue);
	if (SetValue || (InsStatus.Mode == BCKGNDUPDATE_MODE) || (InsStatus.Mode == SSBYUPDATE_MODE))
	{
		/* Start Sorting. Package Only */
		SET_INS_STATE(StSorting);
		insN_OnEvent(insN_EventInsProgress, 0); /*This is to update the progress bar for Pkg only installation*/
		pmp_PmpSend(mPump, EvSorting, 0);
	}
	else
	{
        if (InsStatus.Mode == AUTO_MODE || InsStatus.Mode == CAM_NIT_INSTALLATION_MODE)
        {
            mAddPackageInstalledList ();
        }
		/* Start Blind Scan. All channels */
		SET_INS_STATE(StGenericInstall);
		InsStatus.Lnb = 0;
		/*Added this delay to display number of package channels before moving to blindscan*/
		pmp_PmpSendAfter(mPump, EvInstallStart, (Nat32)NULL, 2000);
	}
}

void CHsvDvbsInstallation_m_Priv::FuncStartGenericInstall(Nat32 param)
{
	int	Count = 0;
	HsvPgdatDigSatInfoData		SatInfo;
	HsvLnbSettings				LnbSettings;
	
	if((InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == AUTOUPDATE_MODE))
    {
		/* Search through SatInfo and identify the list of satellites found in prescan.
			Then start the scanning for each of them */
		for (Count = InsStatus.Lnb; Count < MAX_NO_OF_SATELLITES; Count++)
		{
			SatInfo.LnbNumber = Count;
			PrintfNotice ( "%s %d>SAT_INFO_TABLE[%d]",__FUNCTION__,__LINE__,SatInfo.LnbNumber );
			if (pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
			{
				PrintfNotice ( "%s %d>SAT_INFO_TABLE[%d][%d][%d]",__FUNCTION__,__LINE__,SatInfo.SatelliteName[0],SatInfo.SatelliteName[1],SatInfo.SatelliteName[2] );
				/* Check Update instal needed for this Lnb */
				if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
				{
					PrintfNotice ( "%s %d>UpdateInstallEnabled[%d]",__FUNCTION__,__LINE__,LnbSettings.LnbSettings[Count].UpdateInstallEnabled );
					if ((LnbSettings.LnbSettings[Count].UpdateInstallEnabled == TRUE) && (!mIsLnbMdu(Count)))
					{
						/* Satellite update install needed for this Lnb */
						InsStatus.Lnb = Count;
						break;
					}
				}
			}
		}
	}
    else if (InsStatus.Mode == ADDSAT_MODE)
    {
        TraceNotice (m, "ADD Satellite Mode. Before determining 0x%x ", (int)InsStatus.Lnb);
        Count = InsStatus.Lnb;
        InsStatus.Lnb = GetNextLnbToRemove (Count);
        Count = (InsStatus.Lnb == INVALID_LNB) ? MAX_NO_OF_SATELLITES: InsStatus.Lnb;
        TraceNotice (m, "Starting instalaltion for %d ", Count);
    }
	else
	{
		/* Search through SatInfo and identify the list of satellites found in prescan.
			Then start the scanning for each of them */
		for (Count = InsStatus.Lnb; Count < MAX_NO_OF_SATELLITES; Count++)
		{
			SatInfo.LnbNumber = Count;
			if ((pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo)) && (!mIsLnbMdu(Count)))
			{
				TraceNotice(m, "pgdb getby key succesful for SATInfo %d ", Count);
				/* Satellite exists in this Lnb */
				InsStatus.Lnb = Count;
				break;
			}
		}
	}
	if (Count >= MAX_NO_OF_SATELLITES)
	{
		/* All Satellites covered. Start the sorting now */
		SET_INS_STATE(StSorting);
		pmp_PmpSend(mPump, EvSorting, 0);
	}
	else
	{
		/* Invoking the generic module directly */
		hsvdvbsgeneric_ins_StartInstallation(HsvMain, InsStatus.Lnb, InsStatus.Mode);
	}
}

void CHsvDvbsInstallation_m_Priv::FuncGenericInstallComplete (Nat32 param)
{
	/* Go for next Lnb */
    if (InsStatus.Mode != ADDSAT_MODE)
    {
	    InsStatus.Lnb++;
    }
	pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);
}

void CHsvDvbsInstallation_m_Priv::FuncPackageInstallFailed (Nat32 param)
{
	TraceNotice (m, "Doing Sync from Temp to SQLITE ");
	SET_INS_STATE(StDatabaseSync);
	InsStatus.FromDatabaseId = pgdb_TempDatabase;
	InsStatus.ToDatabaseId = pgdb_SqliteDatabase;
	InsStatus.TableInCopy = SAT_INFO_TABLE;
	InsStatus.IndexToCopy = 0;
	pmp_PmpSend(mPump, EvPerformDatabaseSync, (Nat32)NULL);
    insN_OnEvent(insN_EventPackageInstallFailed, param);
}

void CHsvDvbsInstallation_m_Priv::FuncGenericInstallFailed (Nat32 param)
{
    /* ANEESH: TODO: Is this event proper */
	pgdb_ClearTable(CURRENT_DATABASE_TABLE);
	//pgdb_SelectChannelDatabase(pgdb_SqliteDatabase);
	pgdb_CommitTable(pgdb_GetCurrentTable());
    insN_OnEvent(insN_EventPackageInstallFailed, param);
	mInitInstallationValues(InsStatus.Lnb);
	pgdb_EnableAutoCommit (TRUE);	
}

void CHsvDvbsInstallation_m_Priv::FuncStopPackageParsing(Nat32 param)
{
    if(err_Ok != ipackage_StopPackageParsing())
    {
        TraceNotice(m, "Stop package parshing failed");
    }
	 SET_INS_STATE(StIdle);
}
void CHsvDvbsInstallation_m_Priv::FuncPackagePasingComplete(Nat32 param)
{
	TraceNotice(m, "Package parsing completed");
    mInitInstallationValues(InsStatus.Lnb);
    SET_INS_STATE(StIdle);
}

void CHsvDvbsInstallation_m_Priv::mFuncStartPackageParsing(void)
{
    if(err_Ok == ipackage_StartPackageParsing())
    {
        insN_OnEvent(iinsN_EventPkgParsingStarted, 0);
        SET_INS_STATE(StPackageParsing);
		TraceNotice(m, "Package parsing started notification send");
    }
    else
    {
		TraceNotice(m, "Package parsing completed notification send");
        insN_OnEvent(iinsN_EventPkgParsingCompleted, 0);
    }
}

void CHsvDvbsInstallation_m_Priv::FuncStopSemiStandbyInstall (Nat32 param)
{
	//TraceNotice (m, "%s %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, InsStatus.Mode);
	switch(InsStatus.Mode)
    {
        case AUTOUPDATE_MODE:
		case MINIPRESCAN_MODE:
		case SSBYUPDATE_MODE:
		    iminiprescan_StopMiniPrescan ();
			pgdb_LoadTable(pgdb_GetCurrentTable());	
			idvbset_LoadLnbParametersFromPersistent();
			UnBlockDestination();
			SET_INS_STATE(StIdle);
            break;
        default:
			break;
    }
	
	UNUSED(param);

}

void CHsvDvbsInstallation_m_Priv::FuncCheckSemiStandbyPrescan (Nat32 param)
{
	int		SetValue;
    int     EventId, SatelliteId, index, noOfRecs;
	
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigTSData tsdat;

    EventId = UNPACK_MINISCANEVENT(param);
    SatelliteId = UNPACK_MINISCANID(param);

	if ((InsStatus.Mode == AUTOUPDATE_MODE) || InsStatus.Mode == SSBYUPDATE_MODE)
	{
		switch (EventId)
		{
		case	iminiprescanN_EventPrescanFailed:
            /* Treat this similar to PkgInstall Failed use case */
			//pgdb_SelectChannelDatabase(pgdb_SqliteDatabase);
	        pgdb_LoadTable(pgdb_GetCurrentTable());
            insN_OnEvent(insN_EventInsFailed, param);
            mInitInstallationValues(InsStatus.Lnb);
            pgdb_EnableAutoCommit (TRUE);	
			break;
		case	iminiprescanN_EventSameSatelliteDetected:
			/* No change in LNB Setting: Treat as normal update installation */
			TraceNotice (m, "Same Sat. detected in miniprescan ");
			TraceNotice (m, "InstallStart Sent to Package ");
			/* Indicates not a homing based package */
			SET_INS_STATE (StPackageInstall);
			pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);
			break;

		case	iminiprescanN_EventDifferentSatelliteDetected:
			/* Treat as reinstallation */
			/* ANEESH: 
				Clear DB
				Change Settings file 
				Change Package Selection 
				*/
				TraceNotice (m, "Different Sat. detected in miniprescan ");
				if(InsStatus.Mode == SSBYUPDATE_MODE)
				{
					noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
					/*For SSByInstallation on shutdown, update only package services*/
				    for(index = 0; index < noOfRecs; index++)
				    {
						if( pgdb_GetByIndex(SERVICE_TABLE, index, (Address)&svcdat) == TRUE )
						{
							if(svcdat.SDSDFrequency != 0)
							{
								presetdat.PresetNumber =   svcdat.PresetNumber;
								pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
								pgdb_Delete(SERVICE_TABLE,(Address) &svcdat);
								--index;
								--noOfRecs;
							}
						}
				    }

					/*Delete TStable records of Package1*/
					noOfRecs = pgdb_GetNoRecords(PTC_TABLE);
					for(index = 0; index < noOfRecs; index++)
					{
						if( pgdb_GetByIndex(PTC_TABLE, index, (Address)&tsdat) == TRUE )
						{
							if(tsdat.SDSDFrequency != 0)
							{
								pgdb_Delete(PTC_TABLE,(Address)&tsdat);
								--index;
								--noOfRecs;
							}
						}
					}
				}
				else
				{
					pgdb_ClearTable(PRESET_TABLE);
					pgdb_ClearTable(SERVICE_TABLE);
					pgdb_ClearTable(PTC_TABLE);
				}
			SetValue = mRecalculatePackageId (SatelliteId);
			idvbset_SetAttribute (idvbset_AttributePackageId, SetValue);

			TraceNotice (m, "InstallStart Sent to Package ");
			/* Indicates not a homing based package */
			InsStatus.Mode  = AUTO_MODE;
			SET_INS_STATE (StPackageInstall);
			pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);
			break;
		}	
	}
	else if (InsStatus.Mode == MINIPRESCAN_MODE)
	{
		UnBlockDestination();
		switch (EventId)
		{
		case	iminiprescanN_EventPrescanFailed:
            /* Treat this similar to PkgInstall Failed use case */
			//pgdb_SelectChannelDatabase(pgdb_SqliteDatabase);
	        pgdb_LoadTable(pgdb_GetCurrentTable());
            mInitInstallationValues(InsStatus.Lnb);
			insN_OnEvent(insN_EventSatelliteNotFound, 0);
            pgdb_EnableAutoCommit (TRUE);	
			break;

		case	iminiprescanN_EventSameSatelliteDetected:
			/* No changes. Just give SatelliteFound. Make state Idle */
			SET_INS_STATE(StIdle);
			insN_OnEvent(insN_EventSatelliteFound,SatelliteId);
			break;

		case	iminiprescanN_EventDifferentSatelliteDetected:
			/* Update the package information */
			SetValue = mRecalculatePackageId (SatelliteId);
			idvbset_SetAttribute (idvbset_AttributePackageId, SetValue);

			/* PackageUpdated. Just give SatelliteFound. Make state Idle */
			SET_INS_STATE(StIdle);
			insN_OnEvent(insN_EventDifferentSatelliteFound,SatelliteId);
			break;
		}
	}
}

void CHsvDvbsInstallation_m_Priv::FuncStopDatabaseSync(Nat32 param)
{
	TraceNotice (m, "DATABASE STOP NOT IMPLEMENTED!!!! ");
}

Bool CHsvDvbsInstallation_m_Priv::mIsPredefinedListPackage (void)
{
	Bool	IsPredefinedList = FALSE;
	int PackageId = 0, PackageGroup = 0;

	PackageId = pins_GetAttribute(UPDATE_MODE, pins_AttributePackageId);
	PackageGroup = pins_GetAttribute(UPDATE_MODE, pins_AttributePackageGroup);

	IsPredefinedList = (PackageGroup == 0) && (PackageId != 0) ? TRUE: FALSE;

	return IsPredefinedList;
}



void CHsvDvbsInstallation_m_Priv::FuncPerformDatabaseSync(Nat32 param)
{
	
	HsvPgdatDigSatInfoData		SatInfo;
	HsvPgdatDigTSData			digTs;
	HsvPgdatDigServiceData		digSrv;
	HsvPgdatHomServiceData      HomingSvcData;
	HsvPgdatPresetData			preset, temppreset;
	int		TotalNumberOfEntries, Index, Event = EvPerformDatabaseSync;
	Bool	CurrentStepComplete = TRUE;

	pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
	TotalNumberOfEntries = pgdb_GetNoRecords(InsStatus.TableInCopy);
	
	TraceNotice (m, "Perform Database sync From %d to %d ", InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
	TraceNotice (m ,"TableInCopy %d NumRecords %d ", InsStatus.TableInCopy, TotalNumberOfEntries);
	if ((InsStatus.TableInCopy == SAT_INFO_TABLE) && (InsStatus.IndexToCopy == 0))
	{
	//	TraceNotice (m, " Starting the DATABASE sync. Clearing the ToDatabase ");
		if(((InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == AUTOUPDATE_MODE)) && (InsStatus.ToDatabaseId == pgdb_SqliteDatabase))
		{
	//		TraceNotice (m, "Database clearing done during update installation except for PRESET Table ");
			/* Dont clear the PresetTable here */
			pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
			pgdb_ClearTable(SAT_INFO_TABLE);
			pgdb_ClearTable(SERVICE_TABLE);
			pgdb_ClearTable(PTC_TABLE);
			pgdb_ClearTable(HOMING_SERVICE_TABLE);
		}
		else
		{
			pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
			pgdb_ClearTable (CURRENT_DATABASE_TABLE);
		}
	}
	switch (InsStatus.TableInCopy)
	{
		case 	SAT_INFO_TABLE:
			/* While syncing back to SQLITE database, no need to update SAT_INFO_TABLE. Becauase database already have Prescan values */
			if (TotalNumberOfEntries)
			{
				for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
				{
					pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
					if (TRUE == pgdb_GetByIndex(SAT_INFO_TABLE, Index, (Address) &SatInfo))
					{
						pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
						if (TRUE != pgdb_AddInIndex (SAT_INFO_TABLE, Index, &SatInfo))
						{
						//	TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
						}
					}
					else 
					{
						TraceNotice (m, "S2 SyncDatabase failed for SAT_INFO_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
						usleep (50000);
						Index--;
					}
				}
				InsStatus.IndexToCopy = Index;
				CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
			}
		
			if (CurrentStepComplete == TRUE)
			{
				TraceNotice (m, " Database sync complete for SAT_INFO_TABLE  ");
				InsStatus.TableInCopy = PTC_TABLE;
				InsStatus.IndexToCopy = 0;
			}
			break;
		case	PTC_TABLE:
			if (TotalNumberOfEntries)
			{
				/* Do begin transaction if ToDatabase is SQLITE */
				if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
				{
					pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
					pgdb_BeginSqliteTransaction();
				}
				
				for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
				{
					pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
					if (TRUE == pgdb_GetByIndex(PTC_TABLE, Index, (Address) &digTs))
					{
						pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
						if (TRUE != pgdb_AddInIndex (PTC_TABLE, Index, &digTs))
						{
							//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
						}
					}
					else 
					{
						TraceNotice (m, "S2 SyncDatabase failed for PTC_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
						usleep (50000);
						Index--;
					}	
				}
				/* Do end transaction if ToDatabase is SQLITE */
				if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
				{
					pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
					pgdb_CommitSqliteTransaction();
				}				
				
				InsStatus.IndexToCopy = Index;
				CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
			}
			
			if (CurrentStepComplete == TRUE)
			{
				TraceNotice (m, " Database sync complete for PTC_TABLE  ");
				InsStatus.TableInCopy = SERVICE_TABLE;
				InsStatus.IndexToCopy = 0;
			}
			break;
		case	SERVICE_TABLE:
			if (TotalNumberOfEntries)
			{
				/* Do begin transaction if ToDatabase is SQLITE */
				if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
				{
					pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
					pgdb_BeginSqliteTransaction();
				}

				
				for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
				{
					pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
					if (TRUE == pgdb_GetByIndex(SERVICE_TABLE, Index, (Address) &digSrv))
					{
						pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
						if (TRUE != pgdb_AddInIndex (SERVICE_TABLE, Index, &digSrv))
						{
							//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
						}
					}
					else 
					{
						TraceNotice (m, "S2 SyncDatabase failed for SERVICE_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
						usleep (50000);
						Index--;
					}
				}
				
				/* Do end transaction if ToDatabase is SQLITE */
				if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
				{
					pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
					pgdb_CommitSqliteTransaction();
				}

				
				InsStatus.IndexToCopy = Index;
				CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
			}
			
			if (CurrentStepComplete == TRUE)
			{
				TraceNotice (m, " Database sync complete for SERVICE_TABLE  ");
				InsStatus.TableInCopy = PRESET_TABLE;
				InsStatus.IndexToCopy = 0;
				InsStatus.PresetTableSyncState = (InsStatus.ToDatabaseId == pgdb_SqliteDatabase) ? StatePresetDeleteInSqlite : StatePresetCacheToTemp;
			}
			break;
		case	PRESET_TABLE:
			if (TotalNumberOfEntries)
			{
				/* ANEESH: Handle the update installation use case. In Update installation if SatInstaller is deleting and adding
					entries then UniqueID will be lost. This is creating issues in EPG. So avoid this issue. In case of update installation
					cache the UniqueIds. And when copy back to SQLite dont add new entry. Try to update */
					/* Do begin transaction if ToDatabase is SQLITE */
				if((InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == AUTOUPDATE_MODE))
				{
					switch (InsStatus.PresetTableSyncState)
					{
						case	StatePresetCacheToTemp:
							/* Cache the values from SQLITE to Cached values. */
							for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
							{
								pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
								if (TRUE == pgdb_GetByIndex(PRESET_TABLE, Index, (Address) &preset))
								{
									if (Index < MAX_SAT_SERVICES_SUPPORTED)
									{
										UniqueServiceListCache[Index].PresetNumber = preset.PresetNumber;
										UniqueServiceListCache[Index].Tpid = preset.Tpid;
										UniqueServiceListCache[Index].ServiceId = preset.ServiceId;
									}
									pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
									if (TRUE != pgdb_AddInIndex (PRESET_TABLE, Index, &preset))
									{
										//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
									}
								}
								else 
								{
									TraceNotice (m, "S2 SyncDatabase failed for PRESET_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
									usleep (50000);
									Index--;
								}
							}
							//TraceNotice (m,"Database sync from SQLITE to Temp done till index %d TotalNumberOfEntries %d", Index,TotalNumberOfEntries);
							InsStatus.IndexToCopy = Index;
							InsStatus.NumEntriesInCache = Index;
							CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
							break;
						case	StatePresetDeleteInSqlite:
							/* Check with cache and delete the presets not in transmission OR 
								if keys are changed delete them */
							for (Index = InsStatus.IndexToCopy; Index < InsStatus.NumEntriesInCache; Index++)
							{
								preset.PresetNumber = UniqueServiceListCache[Index].PresetNumber;
								pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
								if (FALSE == pgdb_GetByKey(PRESET_TABLE,(Address)&preset))
								{
									//TraceNotice (m, "Deleting the Preset %d from Cached index %d ", UniqueServiceListCache[Index].PresetNumber, Index);
									/* This Preset is not present in the RAM database. Which means preset got deleted */
									pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
									preset.PresetNumber = UniqueServiceListCache[Index].PresetNumber;
									pgdb_Delete(PRESET_TABLE,(Address)&preset);
								}
								else
								{
									/* In case of predefined list, non-honored services can be move during update installation. Hence dont delete them	
										from preset table. Otherwise this will lead to these channels having different UniqueID, which is not desirable */
									if (mIsPredefinedListPackage())
									{
										/* Preset exists. Cross check if elements are matching. If not some other service got added 
											in the current preset. Hence delete preset from SQLITE */
										if ((preset.Tpid != UniqueServiceListCache[Index].Tpid) || (preset.ServiceId != UniqueServiceListCache[Index].ServiceId))
										{
											//TraceNotice (m, "Deleting the Preset %d from Cached index %d due to mismatch", UniqueServiceListCache[Index].PresetNumber, Index);
											pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
											preset.PresetNumber = UniqueServiceListCache[Index].PresetNumber;
											pgdb_Delete(PRESET_TABLE,(Address)&preset);
										}
									}
								}
							}
							InsStatus.IndexToCopy = Index;
							CurrentStepComplete = FALSE;
							if (Index == InsStatus.NumEntriesInCache)
							{
								//TraceNotice (m, "Deletion of non-transmission entries from SQLITE complete. Now start sync ");
								InsStatus.IndexToCopy = 0;
								InsStatus.PresetTableSyncState = StatePresetCacheToSqlite;
							}
							break;
						case	StatePresetCacheToSqlite:
							/* Add the presets which are not present */
							/*if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
							{
								pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
								pgdb_BeginSqliteTransaction();
							}*/
						
							for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
							{
								pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
								if (TRUE == pgdb_GetByIndex(PRESET_TABLE, Index, (Address) &preset))
								{
									pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
									temppreset.PresetNumber = preset.PresetNumber;
									if (FALSE == pgdb_GetByKey(PRESET_TABLE, &temppreset))
									{
										if (TRUE != pgdb_Add (PRESET_TABLE, &preset))
										{
											//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
										}
									}
									else
									{
										if (mIsPredefinedListPackage())
										{
											if (TRUE != pgdb_Update (PRESET_TABLE, &preset))
											{
												//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
											}
										}
									}
								}
								else 
								{
									TraceNotice (m, "S2 SyncDatabase failed for PRESET_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
									usleep (50000);
									Index--;
								}
							}
						
							/* Do end transaction if ToDatabase is SQLITE */
							/*
							if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
							{
								pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
								pgdb_CommitSqliteTransaction();
							}
							*/
							
							InsStatus.IndexToCopy = Index;
							CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
							break;
						default:
							break;
					}
				}
				else
				{
					if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
					{
						pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
						pgdb_BeginSqliteTransaction();
					}
				
					for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
					{
						pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
						if (TRUE == pgdb_GetByIndex(PRESET_TABLE, Index, (Address) &preset))
						{
							pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
							if (TRUE != pgdb_AddInIndex (PRESET_TABLE, Index, &preset))
							{
								//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
							}
						}
						else 
						{
							TraceNotice (m, "S2 SyncDatabase failed for PRESET_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
							usleep (50000);
							Index--;
						}
					}
					
					/* Do end transaction if ToDatabase is SQLITE */
					if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
					{
						pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
						pgdb_CommitSqliteTransaction();
					}
					
					InsStatus.IndexToCopy = Index;
					CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
				}
			}
			
			if (CurrentStepComplete == TRUE)
			{
				TraceNotice (m, " Database sync complete for PRESET_TABLE  ");
				InsStatus.TableInCopy = HOMING_SERVICE_TABLE;
				InsStatus.IndexToCopy = 0;
			}
			break;
			case	HOMING_SERVICE_TABLE:
			if (TotalNumberOfEntries)
			{
				for (Index = InsStatus.IndexToCopy; (Index < TotalNumberOfEntries) && (Index < (InsStatus.IndexToCopy + MAX_DATABASE_SYNC_IN_ONEPASS)); Index++)
				{
					pgdb_SelectChannelDatabase(InsStatus.FromDatabaseId);
					if (TRUE == pgdb_GetByIndex(HOMING_SERVICE_TABLE, Index, (Address) &HomingSvcData))
					{
						pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
						if (TRUE != pgdb_AddInIndex (HOMING_SERVICE_TABLE, Index, &HomingSvcData))
						{
							//TraceNotice (m, "S2 pgdbAddIndex failed for Index %d ", Index);
						}
					}
					else 
					{
						TraceNotice (m, "S2 SyncDatabase failed for HOMING_SERVICE_TABLE Index %d . Retrying.. From %d To %d  ", Index, InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
						usleep (50000);
						Index--;
					}
				}

				/* Do end transaction if ToDatabase is SQLITE */
				if (InsStatus.ToDatabaseId == pgdb_SqliteDatabase)
				{
					pgdb_SelectChannelDatabase(InsStatus.ToDatabaseId);
					pgdb_CommitSqliteTransaction();
				}
				
				InsStatus.IndexToCopy = Index;
				CurrentStepComplete = (Index == TotalNumberOfEntries) ? TRUE: FALSE;
			}

			if (CurrentStepComplete == TRUE)
			{
				TraceNotice (m, " Database sync complete for HOMING_SERVICE_TABLE  ");
				TraceNotice (m, " Database sync completed from %d to %d ", InsStatus.FromDatabaseId, InsStatus.ToDatabaseId);
				Event = EvDatabaseSyncComplete;
			}
			break;
		default:
			break;
	}

	pmp_PmpSend(mPump, Event, (Nat32)NULL);
}

void CHsvDvbsInstallation_m_Priv::FuncDatabaseSyncComplete(Nat32 param)
{
	FResult	RetVal;
	int		SetValue;
	Nat16	PackageGroupId = 0;
	TraceDebug (m, "%s %d TURNED_ON %d InsStatus.Mode %d ", __FUNCTION__, __LINE__, TURNED_ON, InsStatus.Mode);
	
	//TraceNotice (m, "FromDatabaseId %d Sqlitedb %d temp %d ", InsStatus.FromDatabaseId, pgdb_SqliteDatabase, pgdb_TempDatabase);
	if (InsStatus.FromDatabaseId == pgdb_SqliteDatabase)
	{
		pgdb_SelectChannelDatabase(pgdb_TempDatabase);
		if((InsStatus.Mode == MINIPRESCAN_MODE) && (s2div_PerformReinstallInSemiStandby()))
		{
			SET_INS_STATE (StMiniPrescanInstallation);
			iminiprescan_StartMiniPrescan (InsStatus.Lnb, InsStatus.Mode);
		}
		else if ((InsStatus.Mode == AUTOUPDATE_MODE) && (s2div_PerformReinstallInSemiStandby()))
		{
			SET_INS_STATE (StMiniPrescanInstallation);
			InsStatus.Lnb = mIdentifyMiniPrescanLnb();
			iminiprescan_StartMiniPrescan (InsStatus.Lnb, InsStatus.Mode);
		}/*SSBYUPDATE Mode is only used for digiturk*/
		else if ((InsStatus.Mode == SSBYUPDATE_MODE)/* && (s2div_PerformReinstallInSemiStandby())*/)
		{
			SET_INS_STATE (StMiniPrescanInstallation);
			InsStatus.Lnb = mIdentifyMiniPrescanLnb();
			iminiprescan_StartMiniPrescan (InsStatus.Lnb, InsStatus.Mode);
		}
		else if(InsStatus.Mode == MINIPRESCAN_MODE)
		{
			/* ANEESH: TODO: Give proper event to ceapps */
			TraceNotice (m, "Warning: Why did mini prescan triggered in Non-Single/Digiturk usecase!! ");
		}
		else
		{
			/* This is sync done from SQLITE to Temp. Which will happen during start of installation */
			SET_INS_STATE(StDigital);
			ipackage_LoadPackageGroupInfo ();
			/* Identify whether its package only or All Satellite. Based on that start the installation */
			SetValue = idvbset_GetAttribute (idvbset_AttributePackageId);
			RetVal = ipackage_GetPackageGroupId (SetValue, &PackageGroupId);
			TraceNotice (m, "PackageId %d RetVal %d PackageGroupId %d ",SetValue, RetVal, PackageGroupId);
			if ((RetVal != err_Ok) || (PackageGroupId == 0))
			{
				TraceNotice (m, "InstallStart Sent to Generic ");
				/* Predefined list only */
				SET_INS_STATE (StGenericInstall);
				pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);			
				InsStatus.Lnb = 0;
			}
			else
			{				
				TraceNotice (m, "InstallStart Sent to Package ");
				/* Indicates not a homing based package */
				SET_INS_STATE (StPackageInstall);
				pmp_PmpSend(mPump, EvInstallStart, (Nat32)NULL);			
			}
		}
	}
	else
	{
		/* This is after sorting phase.Temp to SQLITE sync is done */
//		pgdb_SelectChannelDatabase(pgdb_SqliteDatabase);
		SET_INS_STATE(StSorting);
		pmp_PmpSend(mPump, EvSortComplete, (Nat32)NULL);
	}

}

inline Bool CHsvDvbsInstallation_m_Priv::mValidInstallMode(int mode)
{
	FResult retval = TRUE;
	
	switch(mode)
	{
	case AUTO_MODE:
	case UPDATE_MODE:
	case MANUAL_MODE:
	case PRESCAN_MODE:
    case AUTOUPDATE_MODE:
	case ADDSAT_MODE:
	case (PRESCAN_MODE|AUTO_MODE):
	case MINIPRESCAN_MODE:
	case BCKGNDUPDATE_MODE:
    case PACKAGE_PARSING_MODE:
	case BACKGROUND_MODE:
	case CAM_NIT_INSTALLATION_MODE:
	case SSBYUPDATE_MODE:
	case (PRESCAN_MODE|ADDSAT_MODE):
		break;
	default:
	    retval = FALSE;
		break;
    }
	return retval;
}

inline void CHsvDvbsInstallation_m_Priv::mInitInstallationValues(Nat32 param)
{
	//TraceDebug (m, "%s %d param %d ", __FUNCTION__, __LINE__, (int)param);
	SET_INS_STATE(StIdle);
	InsStatus.Lnb				= param;
	InsStatus.CombinedLnbNumber	= param; 
	InsStatus.Stopped			= FALSE;
    InsStatus.LastInstalledPreset	= 0;
    //InsStatus.SkipInstallation		= 0;
}

inline void CHsvDvbsInstallation_m_Priv::mInitInstallationPass(Bool BlockDestionationFlag)
{
	Bool retval = FALSE;

	if(InsStatus.State == StIdle)
	{
		UNUSED(BlockDestionationFlag);

		if(BlockDestionationFlag)
		{
			BlockDestination();
		}
		
		insN_OnEvent(insN_EventInsStarted,0);
	}

	SET_INS_STATE(StSourceSetupWait);

	pmp_PmpSend(mPump, EvSourceSetupApplied, (Nat32)NULL);
}


int CHsvDvbsInstallation_m_Priv::mIdentifyMiniPrescanLnb (void)
{
	int	LnbPos = -1, count = 0, loopcount;
	HsvLnbSettings				LnbSettings;
	
	
	if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	{
		count =  ((LnbSettings.ConnectionType == LnbConnectionSingle) ? 1: ((LnbSettings.ConnectionType == LnbConnectionDiSeqcMini) ? 2 : 4 ));
		for (loopcount = 0; ((loopcount < count) && (LnbPos == -1)); loopcount++)
		{
			switch (LnbSettings.LnbSettings[loopcount].LnbType) 
			{
				case	LnbMdutype1:
				case	LnbMdutype2:
				case	LnbMdutype3:
				case	LnbMdutype4:
				case	LnbMdutype5:
					LnbPos = loopcount;
					break;
				default:
					break;
			}
		}
	}
	
	TraceNotice (m,"MiniPrescan Lnb %d ", LnbPos);
	return LnbPos;

}

void CHsvDvbsInstallation_m_Priv::SetUpdateInstallEnabling (void)
{
      int SetValue, Count , retVal;
      Nat16 PackageId, PackageGroup;
      HsvPgdatDigSatInfoData SatInfo;
      HsvLnbSettings LnbSettings;

      PackageId = idvbset_GetAttribute (idvbset_AttributePackageId);
	  retVal = ipackage_GetPackageGroupId ( PackageId, &PackageGroup);

      SetValue = idvbset_GetAttribute (idvbset_AttributePackageOnly);
	  TraceNotice (m, "RetVal %d Package Group %d PackageOnly flag %d ", retVal, PackageGroup, SetValue);
	  
      if ((PackageGroup == 0) || (!SetValue))
      {
		if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
		{
			/* Predefined list or All channel list. Iterate through the satellite info and update the flags */
			for (Count = 0; Count < MAX_NO_OF_SATELLITES; Count++)
			{
				SatInfo.LnbNumber = Count;
				if (pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
				{
					LnbSettings.LnbSettings[Count].UpdateInstallEnabled = TRUE;
				}
				else
				{
					LnbSettings.LnbSettings[Count].UpdateInstallEnabled = FALSE;
				}
			}
			idvbset_SetLnbSettings (&LnbSettings);
		}
	}
}

Nat32 CHsvDvbsInstallation_m_Priv::GetNextLnbToRemove (Nat32 CurrentLnb)
{
	Nat32		Lnb = 0;
	switch (CurrentLnb)
	{
	case	INVALID_LNB:
		Lnb = ((InsStatus.CombinedLnbNumber & pins_SatLnb1) ? 0 :  ((InsStatus.CombinedLnbNumber & pins_SatLnb2) ? 1: ((InsStatus.CombinedLnbNumber & pins_SatLnb3) ? 2: ((InsStatus.CombinedLnbNumber & pins_SatLnb4) ? 3 : INVALID_LNB))));
		break;
	case	0:
		Lnb = ((InsStatus.CombinedLnbNumber & pins_SatLnb2) ? 1: ((InsStatus.CombinedLnbNumber & pins_SatLnb3) ? 2: ((InsStatus.CombinedLnbNumber & pins_SatLnb4) ? 3 : INVALID_LNB)));
		break;
	case	1:
		Lnb = ((InsStatus.CombinedLnbNumber & pins_SatLnb3) ? 2: ((InsStatus.CombinedLnbNumber & pins_SatLnb4) ? 3 : INVALID_LNB));
		break;
	case	2:
		Lnb = ((InsStatus.CombinedLnbNumber & pins_SatLnb4) ? 3 : INVALID_LNB);
		break;
	case	3:
	default:
		Lnb = INVALID_LNB;
		break;
	}

	return Lnb;
}
void CHsvDvbsInstallation_m_Priv::BlockDestination(void)
{
   //TraceNotice (m,"%s %d>[%p]",__FUNCTION__,__LINE__,__builtin_return_address(0));
	
   vctl_Set2(vctl_VideoMute,TRUE, vctl_VideoMutePogramBlack);   
   if( actl3_IsAvailable2( actl3_ProgramMute, actl3_SpeakerOutput,actl3_BoolTrue ) )
    {
        if( actl3_IsControllable2( actl3_ProgramMute, actl3_SpeakerOutput,actl3_BoolTrue ) )
        {
            actl3_Set2(actl3_ProgramMute, actl3_SpeakerOutput, actl3_BoolTrue);
        }                        
    }
}

void CHsvDvbsInstallation_m_Priv::UnBlockDestination(void)
{
	//TraceNotice (m,"%s %d>[%p]",__FUNCTION__,__LINE__,__builtin_return_address(0));
	
    vctl_Set2(vctl_VideoMute,FALSE, vctl_VideoMutePogramBlack);   
    if( actl3_IsAvailable2( actl3_ProgramMute, actl3_SpeakerOutput,actl3_BoolFalse ) )
    {
        if( actl3_IsControllable2( actl3_ProgramMute, actl3_SpeakerOutput,actl3_BoolFalse ) )
        {
            actl3_Set2(actl3_ProgramMute, actl3_SpeakerOutput, actl3_BoolFalse);
        }            
    }
}

void CHsvDvbsInstallation_m_Priv::mDetermineDuplicateSatelliteName (HsvPgdatDigSatInfoData *SatInfo)
{
	Bool	RetVal = FALSE;
	char	LnbName [10];
	HsvSatelliteMapping	SatelliteMapping;

    RetVal= iprescanparser_ExtractPreScanTableFromXml();
    if (RetVal == TRUE)
    {
        SatelliteMapping.SatelliteId = SatInfo->SatelliteId;
        
        RetVal = iprescanparser_GetSatelliteAttributeById (&SatelliteMapping);
        if (RetVal == FALSE)
        {
            /* Should display Sat - <Lnb Number > */
            sprintf (LnbName, "Sat - %d", SatInfo->LnbNumber+1);
            charsetutil_MbToWc((Nat8*)LnbName, strlen(LnbName), SatInfo->SatelliteName, MAX_SATELLITE_NAME_LEN, FALSE);
        }
        else
        {
            memcpy (SatInfo->SatelliteName, SatelliteMapping.SatelliteName, (sizeof(Nat16) * MAX_SATELLITE_NAME_LEN));
        }
    }
    else
    {
        TraceNotice(m, "Error in reading XML file ");
    }
}

void CHsvDvbsInstallation_m_Priv::mAddPackageInstalledList (void)
{
    HsvPgdatDigTSData			TsData;
    int                         Count,NumRecords;
    FrequencyDataList           FreqList;

	NumRecords = pgdb_GetNoRecords(PTC_TABLE);
    for (Count = 0 ; Count < NumRecords; Count++)
    {
        if (TRUE == pgdb_GetByIndex(PTC_TABLE, Count, (Address) &TsData))
        {
            FreqList.LnbNumber = TsData.LnbNumber;
            FreqList.Frequency = TsData.Frequency;
            FreqList.Polarization = TsData.Polarization;
            FreqList.OriginalNetworkId = TsData.OriginalNetworkId;
            FreqList.TsId = TsData.Tsid;
			FreqList.SymRate = TsData.SymbolRate;

            iutil_AddEntryToList (&FreqList);
        }
    }
    TraceNotice (m, "Added %d muxes while package installation ", NumRecords);
}
void CHsvDvbsInstallation_m_Priv::mReloadUnicableSetting (void)
{
    FResult         RetVal;
    HsvLnbSettings  LnbSettings;
    int             LnbNumber = 0;/* This can be any value. Intention is just to send TRUE/FALSE to unicable config */

    RetVal = idvbset_GetLnbSettings (&LnbSettings);
	//TraceNotice (m,"%s %d>RetVal[%d][%d]",__FUNCTION__,__LINE__,RetVal,LnbSettings.ConnectionType );
    if (RetVal == err_Ok)
    {
        switch (LnbSettings.ConnectionType)
        {
            case    LnbConnectionSingle:
            case    LnbConnectionDiSeqcMini:
            case    LnbConnectionDiSeqc1_0:
                satfeapi_UnicableEnable(LnbNumber,FALSE);
                break;
            case    LnbConnectionUnicableLnb:
            case    LnbConnectionUnicableSwitch:
                satfeapi_UnicableEnable(LnbNumber,TRUE);
                break;
        }
    }
}

int CHsvDvbsInstallation_m_Priv::mRecalculatePackageId (int SatelliteId)
{
	int	PackageId = idvbset_GetAttribute (idvbset_AttributePackageId);

	switch (SatelliteId)
	{
		case	TURKSAT_42_0_E:
			PackageId = DIGITURK_TURKSAT_PACKAGE_ID;
			break;
		case	EUTELSAT_W3A_7A:
		case	EUTELSAT_W3A_7E_MDU4:
		case	EUTELSAT_W3A_7A_MDU5:
		case	EUTELSAT_W3A_7E_MDU3:
		case	EUTELSAT_W3A_7E_MDU2:
		case	EUTELSAT_W3A_7E_MDU1:
			PackageId = DIGITURK_EUTELSAT_PACKAGE_ID;
			break;
	}

	return PackageId;
}


int CHsvDvbsInstallation_m_Priv::mIsLnbMdu (int LnbNumber)
{
	int	RetVal = FALSE;
	HsvLnbSettings				LnbSettings;
	
	if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	{
		switch (LnbSettings.LnbSettings[LnbNumber].LnbType) 
		{
			case	LnbMdutype1:
			case	LnbMdutype2:
			case	LnbMdutype3:
			case	LnbMdutype4:
			case	LnbMdutype5:
				RetVal = TRUE;
				break;
			default:
				break;
		}
	}
	
	return RetVal;
}

/****************************************************************************
 * External functions
 ****************************************************************************/

/* provides IHSvPower ipow */

void CHsvDvbsInstallation_m_Priv::ipow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE, "hsvdvbsins_m_pmp" );
    
	mModuleLifeCycle = Initialised;
    //TraceDebug (m, "%s %d ", __FUNCTION__, __LINE__);
}

void CHsvDvbsInstallation_m_Priv::ipow_TurnOn(void)
{
	//TraceDebug (m, " Installation Powered On... \n");
	mModuleLifeCycle = TurnedOn;
    pgdb_EnableAutoCommit(TRUE);
	InsStatus.Mode = MODE_NONE;
	mInitInstallationValues(InsStatus.Lnb);
}

void CHsvDvbsInstallation_m_Priv::ipow_TurnOff(void)
{
	mModuleLifeCycle = TurnedOff;
    FuncStopInstallation((Nat32)NULL);
    if(InsStatus.State != StSorting)
	{
		pgdb_CommitTable(pgdb_GetCurrentTable());
	}
}

/* provides IHsvSatelliteInstallation pins */

FResult CHsvDvbsInstallation_m_Priv::pins_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult retval = 0;
	int mPackageId;

	TraceNotice (m, "TurnedOn [[%d]] ValidInstallationMode %d Lnb %d Mode %d Source %d \n", TURNED_ON, mValidInstallMode(Mode),Lnb,Mode,Source);

	if(TURNED_ON &&  mValidInstallMode(Mode) )
	{   

	 	/* First Argument: "Source" in this Function determines in Disecq 1.0 and mini usecase
	 	 * 				   if   to Skip current LNB from prescan(Source == NoSource) 
	 	 *				   else to consider for prescan and Installation
	 	 */
		if(Source != HsvNoSource)
		{
			InsStatus.SkipInstallation = FALSE;
			if (Mode == IHsvSatelliteInstallation_InstallationBackground)
			{
				ctrl_StopCollection (HsvDmxMain);

				mPackageId = pins_GetAttribute(IHsvSatelliteInstallation_InstallationBackground,IHsvSatelliteInstallation_AttributePackageId);
				TraceNotice (m, "PackageID %d ", mPackageId);
				/*masking mPackageId with 0xFFFF, since for fransat first 16bits are package id and next 16 bits are bouquet id*/
				if((mPackageId & 0xFFFF) == FRANSAT_PACKAGE_ID) // package group id
				{
					//TraceNotice (m, "Start Collection Triggered with FransatNormal");
					ctrl_StartCollection (HsvDmxMain, ctrl_FransatNormal);
	        			InsStatus.Mode = BACKGROUND_MODE;
				}
				else if(mPackageId == AUSTRIA_CHANNELLIST_PACKAGE_ID)
				{
					//TraceNotice (m, "Start Collection Triggered with Normal");
					ctrl_StartCollection (HsvDmxMain, ctrl_Normal);
					InsStatus.Mode = BACKGROUND_MODE;
					pgdb_MasterEnableEvents (TRUE);
				}
				else if(mPackageId == ASTRA_LCN_BOUQUET_ID)
				{
					//TraceNotice (m, "Start Collection Triggered for Astra LCN");
					ctrl_StartCollection (HsvDmxMain,ctrl_Normal);
					InsStatus.Mode = BACKGROUND_MODE;
				}

			}
			else if (Mode == (PRESCAN_MODE | ADDSAT_MODE))
			{
				pgdb_SaveChannelMapsToBackup ();
			}
			else
			{
		    	InsStatus.Mode  = Mode;
	        	pmp_PmpSend(mPump, EvStart, (Nat32)Lnb);
			}
		
		}
		else
		{
				
				InsStatus.Mode  = Mode;
				InsStatus.SkipInstallation = TRUE;
				TraceNotice(m,"Skip LNB %d",InsStatus.SkipInstallation);
	        	pmp_PmpSend(mPump, EvStart, (Nat32)Lnb);
		}
	}
	else
	{
		retval = err_InstallationCommandNotAllowed;
	}	
    return retval;
}

FResult CHsvDvbsInstallation_m_Priv::pins_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)0);

	if ((GET_INS_STATE == StIdle) && (InsStatus.Mode == BACKGROUND_MODE))
	{
		TraceNotice (m, "Stopping background installation ");
		if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
		{
			ctrl_StopCollection (HsvDmxMain);
		}
		pgdb_MasterEnableEvents(FALSE);
	}
		

	return RetVal;
}

int CHsvDvbsInstallation_m_Priv::pins_GetCurrentInstallationState (int *mode, int *state)
{
    /* During automatic update, if SemiStandbyInstallation mode is triggered, it means MW is doing a Mini-prescan.
     * Hence SDM would need to be informed about the same. */
	*mode  =  (((InsStatus.Mode == AUTOUPDATE_MODE) || (InsStatus.Mode == MINIPRESCAN_MODE) || (InsStatus.Mode == SSBYUPDATE_MODE))&& (GET_INS_STATE == StMiniPrescanInstallation)) ? PRESCAN_MODE : InsStatus.Mode ;
	*state =  (GET_INS_STATE == StIdle)? pins_InstallationStateIdle : pins_InstallationStateInProgress;

	return 0;
}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberOfTvChannelsFound (int Lnb)
{
	int retValue = 0;

	switch (InsStatus.Mode)
	{
	case	MANUAL_MODE:
		retValue = hsvdvbsgeneric_ins_GetNumberOfTvChannelsFound (InsStatus.Mode, Lnb);
			break;
	case	AUTO_MODE:
	case	UPDATE_MODE:
    case    AUTOUPDATE_MODE:
	case	ADDSAT_MODE:
	case	BCKGNDUPDATE_MODE:
	case 	CAM_NIT_INSTALLATION_MODE:
	case 	SSBYUPDATE_MODE:
		if (GET_INS_STATE == StGenericInstall)
		{
			//TraceNotice (m, "Generic Module query ");
			retValue = hsvdvbsgeneric_ins_GetNumberOfTvChannelsFound (InsStatus.Mode, Lnb);
		}
		else
		{
			//TraceNotice (m, "PackagEModule query ");
			retValue = ipackageins_GetNumberOfTvChannelsFound (InsStatus.Mode, Lnb);
		}		
		break;
	default:
		break;
	}

	TraceNotice (m, "%s %d retValue %d\n", __FUNCTION__, __LINE__, retValue);

	return retValue;
}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberofRadioChannelsFound (int Lnb)
{
	int retValue = 0;

	switch (InsStatus.Mode)
	{
	case	MANUAL_MODE:
		retValue = hsvdvbsgeneric_ins_GetNumberofRadioChannelsFound (InsStatus.Mode, Lnb);
			break;
	case	AUTO_MODE:
	case	UPDATE_MODE:	
	case	AUTOUPDATE_MODE:	
	case	ADDSAT_MODE:
	case	BCKGNDUPDATE_MODE:
	case 	CAM_NIT_INSTALLATION_MODE:
	case 	SSBYUPDATE_MODE:
		if (GET_INS_STATE == StGenericInstall)
		{
			retValue = hsvdvbsgeneric_ins_GetNumberofRadioChannelsFound (InsStatus.Mode, Lnb);
		}
		else
		{
			retValue = ipackageins_GetNumberofRadioChannelsFound (InsStatus.Mode, Lnb);
		}		
		break;
	default:
		break;
	}

	TraceDebug (m, "%s %d retValue %d\n", __FUNCTION__, __LINE__, retValue);

	return retValue;
}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberOfTvChannelsRemoved(int Lnb)
{
	int retValue = 0;
	
	switch (InsStatus.Mode)
	{
	case	UPDATE_MODE:
	case	BCKGNDUPDATE_MODE:
		if (GET_INS_STATE == StGenericInstall)
		{
			retValue = hsvdvbsgeneric_ins_GetNumberOfTvChannelsRemoved (InsStatus.Mode, Lnb);
		}
		else
		{
			retValue = ipackageins_GetNumberOfTvChannelsRemoved (InsStatus.Mode, Lnb);
		}
		break;
	default:
		break;
	}

	TraceDebug (m, "%s %d retValue %d\n", __FUNCTION__, __LINE__, retValue);

	return retValue;
}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberofRadioChannelsRemoved (int Lnb)
{
	int retValue = 0;

	switch (InsStatus.Mode)
	{
		case	UPDATE_MODE:
		case	BCKGNDUPDATE_MODE:
		if (GET_INS_STATE == StGenericInstall)
		{
			retValue = hsvdvbsgeneric_ins_GetNumberofRadioChannelsRemoved (InsStatus.Mode, Lnb);
		}
		else
		{			
			retValue = ipackageins_GetNumberofRadioChannelsRemoved (InsStatus.Mode, Lnb);
		}
		break;
	default:
			break;
	}

	return retValue;
}


FResult CHsvDvbsInstallation_m_Priv::pins_GetSatelliteName (int Lnb, Nat16 *SatelliteName)
{
	FResult retValue = err_ChannelNotInstalled;
	HsvPgdatDigSatInfoData		SatInfo;
    HsvLnbSettings              LnbSettings;

	SatInfo.LnbNumber = Lnb;
	if (pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (SatelliteName, SatInfo.SatelliteName, 33 * sizeof(Nat16));
		retValue = err_Ok;
	}
    else
    {
        /* No Satellite or Duplicate Satellite */
        if ((Lnb < MAX_LNB_SUPPORTED) && (err_Ok == idvbset_GetLnbSettings (&LnbSettings)) && \
                        (LnbSettings.LnbSettings[Lnb].LnbStatus == LnbDuplicate))
        {
            TraceNotice (m, "Duplicate LNB Name ");
	        SatInfo.LnbNumber = Lnb;
	        SatInfo.SatelliteId = LnbSettings.LnbSettings[Lnb].SatelliteId;
            mDetermineDuplicateSatelliteName (&SatInfo);
            memcpy (SatelliteName, SatInfo.SatelliteName, 23 * sizeof(Nat16));
            retValue = err_Ok;
        }
	}

	return retValue;
}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberOfDigitalChannelsAdded(void)
{
	/* ANEESH: TODO: Why this is taken from here. Should be routed to proper module */
	int retValue = 0;
	
	return retValue;

}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberOfDigitalChannelsRemoved(void)
{
	int retValue = 0;
	
	return retValue;
}

int CHsvDvbsInstallation_m_Priv::pins_GetNumberOfDigitalChannelsMoved (void)
{
	int retValue = 0;
	

	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_IdentifyPackagesAvailable (void)
{
	return ipackage_IdentifyPackagesAvailable ();
}

int CHsvDvbsInstallation_m_Priv::pins_GetTotalNumberOfPackagesFound (void)
{
	return ipackage_GetNumberOfPackages ();
}

FResult CHsvDvbsInstallation_m_Priv::pins_GetPackageByIndex(int Index, HsvPackageStructure *Package)
{

	return ipackage_GetPackageByIndex (Index, Package);
}

FResult CHsvDvbsInstallation_m_Priv::pins_SetUserPackageIndex(Nat32 PackageIndex)
{
	FResult retValue = 0;

	if (InsStatus.Mode == UPDATE_MODE || InsStatus.Mode == BCKGNDUPDATE_MODE)
	{
		/* This will trigger sorting */
		SET_INS_STATE(StSorting);
		pmp_PmpSend(mPump, EvSorting, 0);
	}
	else
	{
		TraceNotice (m, "Setting package index %d ", PackageIndex);
		retValue = idvbset_SetAttribute (idvbset_AttributePackageId, PackageIndex);

	}

	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_GetUserPackageIndex(Nat32* PackageIndex, Bool* IsPackage)
{
	FResult retValue = err_BadParameter;
	int		SetValue = 0;
	Nat16	PackageGroupId = 0;

	if (PackageIndex && IsPackage)
	{
		SetValue = idvbset_GetAttribute (idvbset_AttributePackageId);
		*PackageIndex = SetValue;

		retValue = ipackage_GetPackageGroupId ((Nat16)SetValue, &PackageGroupId);
		*IsPackage = ((retValue == err_Ok) && (PackageGroupId > 0)) ? TRUE : FALSE;
		retValue = err_Ok;
	}

	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_GetInstalledSatellites (int mode, HsvInstalledSatellites *SatelliteEntries)
{
	/* ANEESH: This looks pretty messy API. Make it a proper one */
	FResult retValue = err_BadParameter;
	int loopcount = 0;
	HsvPgdatDigSatInfoData		SatInfo;
	HsvLnbSettings				CurLnbSetting;

	retValue = idvbset_GetLnbSettings (&CurLnbSetting);
	if (retValue == err_Ok)
	{
		switch (CurLnbSetting.ConnectionType)
		{
		case	LnbConnectionSingle:
			SatelliteEntries->NumberOfLnbs = 1;
			break;
		case	LnbConnectionDiSeqcMini:
			SatelliteEntries->NumberOfLnbs = 2;
			break;
		case	LnbConnectionDiSeqc1_0:
			SatelliteEntries->NumberOfLnbs = 4;
			break;
		default:
			SatelliteEntries->NumberOfLnbs = 1;
			break;
		}

		for ( loopcount = 0;loopcount < SatelliteEntries->NumberOfLnbs;++loopcount)
		{
			SatelliteEntries->SatelliteDetails[loopcount].LnbNumber = loopcount;
			SatelliteEntries->SatelliteDetails[loopcount].LnbType = CurLnbSetting.LnbSettings[loopcount].LnbType;
			
			SatInfo.LnbNumber = loopcount;
			if(pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatInfo) == TRUE)
			{
				SatelliteEntries->SatelliteDetails[loopcount].IsLnbFree = FALSE;
				/* ANEESH: TODO:Update the service scan complete flag here */
				memcpy (SatelliteEntries->SatelliteDetails[loopcount].SatelliteName, SatInfo.SatelliteName, (33 * sizeof(Nat16)));
			}
			else
			{
				SatelliteEntries->SatelliteDetails[loopcount].IsLnbFree = TRUE;
				SatelliteEntries->SatelliteDetails[loopcount].SatelliteName[0] = 0x00;
				SatelliteEntries->SatelliteDetails[loopcount].IsServiceScanComplete = FALSE;
			}
		}
	}
	
	UNUSED(mode);

	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_InstallAddedSatellites (void)
{
	FResult retValue = 0;
	
	
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_ResetAddedSatellites (void)
{
	FResult retValue = 0;
	
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_RemoveSatelliteEntry (int LnbNumber)
{
	FResult retValue = err_Ok;

	InsStatus.Mode = pins_InstallationNone; 
	iaddremove_RemoveSatelliteEntry(LnbNumber);
	
	return retValue;
}

int CHsvDvbsInstallation_m_Priv::pins_GetSatelliteSignalStrength (int LnbNumber)
{
	Nat32		SignalStrength = 0;	
	
	isigstr_StartSigStrMeasAll ();

	SignalStrength  = isigstr_GetActualSignalStrength (isigstr_InsSsm, 0);
	if (SignalStrength == 0)
	{
		SignalStrength  = isigstr_GetActualSignalStrength (isigstr_InsQsm, 0);
	}

	isigstr_StopSigStrMeasAll ();

	UNUSED (LnbNumber);

	return SignalStrength;
}

int CHsvDvbsInstallation_m_Priv::pins_GetSatelliteSignalQuality (int LnbNumber)
{
	int retValue = 0;
		
	UNUSED(LnbNumber);
	/* ANEESH: TODO: Get the signal strength */
		retValue = isigstr_GetSignalStrength (isigstr_InsQsm);
	if(!retValue)
	{
		retValue = isigstr_GetSignalStrength (isigstr_InsSsm);
	}
	//TraceNotice (m, "Signal Quality got is %d ", retValue);

	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_StoreManualInstallationValues (void)
{
	//TraceDebug (m, "%s %d\n", __FUNCTION__, __LINE__);
	return hsvdvbsgeneric_ins_StoreManualInstallationValues();
}

FResult CHsvDvbsInstallation_m_Priv::pins_LoadManualInstallationDefaultValues (void)
{
	return hsvdvbsgeneric_ins_LoadManualInstallationDefaultValues ();
}

Nat32 CHsvDvbsInstallation_m_Priv::pins_GetAttribute(int Mode, int AttributeId)
{
	Nat32	retValue = 0, tempVal = 0;
	Nat16 PackageGroupId = 0; 
	switch(Mode)
    {
        case MANUAL_MODE:
			retValue = hsvdvbsgeneric_ins_GetAttribute(Mode,AttributeId);
			break;
		default:
			switch (AttributeId)
			{
			case	pins_AttributePackageId:
				retValue = idvbset_GetAttribute (idvbset_AttributePackageId);
				break;
			case	pins_AttributePackageOnly:
				retValue = idvbset_GetAttribute (idvbset_AttributePackageOnly);
				break;
			case	pins_AttributePackageGroup:
				tempVal = idvbset_GetAttribute (idvbset_AttributePackageId);
				retValue = ipackage_GetPackageGroupId ((Nat16)tempVal, &PackageGroupId);
				if (retValue == err_Ok)
				{
					retValue = PackageGroupId;
				}
				else
				{
					retValue = 0; /* Not a package. Retuning Predef */
				}
				break;
			case	IHsvSatelliteInstallation_AttributeFrequency:
				retValue = idvbset_GetAttribute (IHsvSatelliteSettings_AttributeFrequency);
				break;
			case	IHsvSatelliteInstallation_AttributePolarization:
				retValue = idvbset_GetAttribute (IHsvSatelliteSettings_AttributePolarization);
				break;
			case 	IHsvSatelliteInstallation_AttributeSymbolRate:
				retValue = idvbset_GetAttribute(IHsvSatelliteSettings_AttributeSymbolRate);
				break;
			case 	IHsvSatelliteInstallation_AttributeSymbolRateMode:
				retValue = idvbset_GetAttribute(IHsvSatelliteSettings_AttributeSymbolRateMode);
				break;
			case IHsvSatelliteInstallation_AttributeTimeOffset:
			case IHsvSatelliteInstallation_AttributeChangeDate:
			case IHsvSatelliteInstallation_AttributeNextTimeOffset:
				tempVal = idvbset_GetAttribute (idvbset_AttributePackageId);
				if (tempVal == OP_PROFILE_PACKAGE_ID) {
					 retValue = ipackageins_GetAttribute(Mode,AttributeId);
					}
				break;
			}
			break;
	}

	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_SetAttribute(int Mode, int AttributeId, Nat32 Value)
{
	//TraceNotice (m, "%s %d Mode:%d", __FUNCTION__, __LINE__,Mode);
	FResult		retValue = err_BadParameter;

	switch(Mode)
    {
        case MANUAL_MODE:
			if  (AttributeId == pins_AttributeAssetManager)
			{
				retValue = idvbset_SetAttribute (idvbset_AttributeAssetManager, Value);
			}
			else
			{
				hsvdvbsgeneric_ins_SetManualInstallationAttributes (AttributeId,Value);
				retValue = err_Ok;
			}
			break;
		default:
			switch (AttributeId)
			{
			case	pins_AttributePackageId:
				retValue = idvbset_SetAttribute (idvbset_AttributePackageId, Value);
				break;
			case	pins_AttributePackageOnly:
				retValue = idvbset_SetAttribute (idvbset_AttributePackageOnly, Value);
				break;
			case	IHsvSatelliteInstallation_AttributeFrequency:
				retValue = idvbset_SetAttribute (IHsvSatelliteSettings_AttributeFrequency, Value);
				break;
			case	IHsvSatelliteInstallation_AttributePolarization:
				retValue = idvbset_SetAttribute (IHsvSatelliteSettings_AttributePolarization, Value);
				break;
			case	IHsvSatelliteInstallation_AttributeSymbolRate:
				retValue = idvbset_SetAttribute (IHsvSatelliteSettings_AttributeSymbolRate, Value);
				break;
			case	IHsvSatelliteInstallation_AttributeSymbolRateMode:
				retValue = idvbset_SetAttribute (IHsvSatelliteSettings_AttributeSymbolRateMode, Value);
				break;
			case	pins_AttributePackageGroup:
				/* This is not allowed */
				break;
			case	pins_AttributeAssetManager:
				retValue = idvbset_SetAttribute (idvbset_AttributeAssetManager, Value);
				break;
			}
			break;
	}
	//TraceDebug (m, "%s %d AttributeId %d retValue %d\n", __FUNCTION__, __LINE__, AttributeId, retValue);

	return retValue;
}
FResult CHsvDvbsInstallation_m_Priv::pins_StartTricolorRegionParsing()
{
	//TraceNotice(m,"%s Entry ",__FUNCTION__);
	FResult retValue = err_BadParameter;
	retValue = ipackageins->StartTricolorRegionParsing();
	if(retValue == err_Ok)
	{
		//TraceNotice(m,"%s Mode set to TRICOLOR_REGION_PARSING_MODE",__FUNCTION__);
		InsStatus.Mode = TRICOLOR_REGION_PARSING_MODE;
	}
	//TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,retValue);
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_SetTricolorRegionIndex (int index)
{
	//TraceNotice(m,"%s Entry index %d",__FUNCTION__, index);
	FResult retValue = err_BadParameter;
	retValue = ipackageins->SetTricolorRegionIndex(index);
	//TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,retValue);
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_GetTricolorRegionNames (Nat16 **names, int *len)
{
	//TraceNotice(m,"%s Entry",__FUNCTION__);
	FResult retValue = err_BadParameter;
	
	retValue = ipackageins->GetTricolorRegionNames(names,len);
//	TraceNotice(m,"region names %s",&names[0][0]);
	//TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,retValue);
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	//TraceNotice(m,"%s Entry postcodelen %d postcode:%s",__FUNCTION__,PostcodeLen,Postcode);
	FResult retValue = err_BadParameter;
	retValue = ipackageins->SetPostcode(PostcodeLen, Postcode);
	//TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,retValue);
	return retValue;
}




int CHsvDvbsInstallation_m_Priv::pins_GetScanProgressStatus (int Mode)
{
	int	retValue = 0;
	int	SetValue;
	HsvLnbSettings				LnbSettings;
	switch (Mode)
	{
		case PRESCAN_MODE:
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
				if(LnbSettings.ConnectionType == LnbConnectionSatIp)
				{
					retValue = isatipprescan_GetScanProgressStatus (Mode);
				}
				else
				{
					retValue = iprescan_GetScanProgressStatus (Mode);
				}
			}
			break;
		case	AUTO_MODE:
		case	UPDATE_MODE:
		case	BCKGNDUPDATE_MODE:
		case	CAM_NIT_INSTALLATION_MODE:
			if (GET_INS_STATE == StGenericInstall)
			{
				//TraceNotice (m, "Generic Module query ");
				retValue = hsvdvbsgeneric_ins_GetScanProgressStatus (Mode);
			}
			else
			{
				/* Check Package only or not. If package only, update progress */
				SetValue = idvbset_GetAttribute (idvbset_AttributePackageOnly);
				if(SetValue)
				{
					//TraceNotice (m, "PackagEModule query ");
					if(InsStatus.State == StSorting)
					{
						retValue = 99;
					}
					else
					{
						retValue = ipackageins_GetScanProgressStatus (Mode);
						retValue = ( retValue < 100 ) ? retValue:99;
					}
				}
				else
				{
					retValue = 0;
				}
			}		
			break;
	}
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_GetSITableIds(Nat16* NetworkID, Nat16* BouquetID)
{
	FResult		RetVal = err_BadParameter;
	HsvLnbSettings				LnbSettings;

	if (NetworkID && BouquetID)
	{
		if (InsStatus.Mode == PRESCAN_MODE)
		{
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
				if(LnbSettings.ConnectionType == LnbConnectionSatIp)
				{
					RetVal = isatipprescan_GetSITableIds(NetworkID, BouquetID);
				}
				else
				{
					RetVal = iprescan_GetSITableIds(NetworkID, BouquetID);
				}
			}
		}
        else if (((InsStatus.Mode ==  AUTOUPDATE_MODE) || (InsStatus.Mode ==  MINIPRESCAN_MODE) || (InsStatus.Mode ==  SSBYUPDATE_MODE))&& (GET_INS_STATE == StMiniPrescanInstallation) )
        {
			RetVal = iminiprescan_GetSITableIds(NetworkID, BouquetID);
        }
	}

	return RetVal;
}

FResult CHsvDvbsInstallation_m_Priv::pins_GetPackageName (Nat32	PackageId, Nat16	*PackageName)
{
	FResult		RetVal = err_BadParameter;
	if (PackageName)
	{
		RetVal = ipackage_GetPackageGroupName (PackageId, PackageName);
	}

	return RetVal;
}
void CHsvDvbsInstallation_m_Priv::pins_ResetInstallation (void)
{
	//TraceNotice (m,  "%d> pins_ResetInstallation",__LINE__ );
	switch (InsStatus.Mode)
	{
	case	AUTO_MODE:
	case	PRESCAN_MODE:
	case 	CAM_NIT_INSTALLATION_MODE:
		SET_INS_STATE(StIdle);
		InsStatus.Mode = MODE_NONE;
		iprescan_ResetInstallation ();
		idvbset_LoadLnbParametersFromPersistent();
        mReloadUnicableSetting ();
		UnBlockDestination();
		if (InsStatus.Mode == PRESCAN_MODE)
		{
			InsStatus.Mode = MODE_NONE;
		}
		//pgdb_SelectChannelDatabase (pgdb_SqliteDatabase);
		pgdb_LoadChannelMapsFromBackup();
		break;
	}
	pgdb_LoadTable(pgdb_GetCurrentTable());
	pgdb_EnableAutoCommit(TRUE);
}

void CHsvDvbsInstallation_m_Priv::pins_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	ipackageins_GetSIDetails(SiValues);
}

void CHsvDvbsInstallation_m_Priv::pins_EnableUnicable (int LnbNumber, Bool Enable)
{
    satfeapi_UnicableEnable(LnbNumber,Enable);
}


int CHsvDvbsInstallation_m_Priv::pins_GetFirstInstalledChannel (void)
{
	Bool						RetVal = FALSE, IsPackage = FALSE;
	HsvPgdatPresetData			preset;
	HsvPgdatDigTSData			TsData;
	HsvPgdatDigServiceData		SvcData;
	int	From = 0, To = 0, count = 0,presetcount =0;
	int	channelno = -1;
	Nat32 PackageIndex = 0;
	int NoOfRecords = pgdb_GetNoRecords(PRESET_TABLE);


	//TraceNotice(m,"NoOfRecords: %d", NoOfRecords);
	if(NoOfRecords)
	{
		if (InsStatus.Mode == MANUAL_MODE)
		{
			/* In case of manual installation switching should be done to the installed channel only */
			TsData.LnbNumber  =	pins_GetAttribute(pins_InstallationManual,pins_ManualInstallLnb);
			TsData.Frequency  = pins_GetAttribute(pins_InstallationManual,pins_ManualInstallFreq);
			TsData.Polarization =   pins_GetAttribute(pins_InstallationManual,pins_ManualInstallPolaraization);

			RetVal = pgdb_GetByKey (PTC_TABLE, (Address) &TsData);
			//TraceNotice (m,"%s %d>MANUAL_INSTALL RetVal[%d][%d][%d][%d]",__FUNCTION__,__LINE__,TsData.LnbNumber,TsData.Frequency,TsData.Polarization,RetVal);
			if (RetVal == TRUE)
			{
				SvcData.Tpid = TsData.Tpid;
				RetVal = pgdb_GetRange (SERVICE_TABLE , 1, (Address)&SvcData , &From , &To);
				//TraceNotice (m,"%s %d>MANUAL_INSTALL RetVal[%d][%d]",__FUNCTION__,__LINE__,SvcData.Tpid,RetVal);
				if (RetVal == TRUE)
				{
					pins_GetUserPackageIndex(&PackageIndex, &IsPackage);
					for (count = To; count >= From; count--)
					{
						RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&SvcData);
						if (RetVal == TRUE)
						{							
							if(PackageIndex == ASTRA_LCN_BOUQUET_ID)
							{
								channelno = SvcData.MultiplePreset[0];
								break;
							}
							else
							{
								channelno = SvcData.PresetNumber;
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			for(presetcount=(NoOfRecords-1); presetcount >=0; presetcount--)
			{
				
				if(pgdb_GetByIndex(PRESET_TABLE,presetcount,(Address)&preset))
				{
					TraceNotice(m,"presetNumber %d presetSystemHidden %d presetServiceId %d onid %d tpid %d VisibleService %d ",preset.PresetNumber,preset.SystemHidden,preset.ServiceId,preset.OriginalNetworkId,preset.Tpid,preset.VisibleService);
					if(preset.VisibleService)
					{
						channelno = preset.PresetNumber;
						break;
					}
				}
				else
				{
					//TraceErr(m, "pgdb_GetByIndex failed");
					channelno = 1;
					break;
				}
			}
		}
	}
	TraceNotice(m, "pins_GetFirstInstalledChannel %d", channelno);
	
	return channelno;
}

void CHsvDvbsInstallation_m_Priv::pins_UpdateConfigXmlStrings (char *PrescanXmlString, int PrescanXmlStringLen, char *SatellitePackageXmlString, int SatellitePackageXmlStringLen)
{
	TraceNotice (m, "%s %d PrescanXmlStringLen [%d] SatellitePackageXmlStringLen [%d] \n", __FUNCTION__, __LINE__, PrescanXmlStringLen,SatellitePackageXmlStringLen);
	ipackage_SetPackageParserXmlString (SatellitePackageXmlString, SatellitePackageXmlStringLen);
}



/* provides IHsvSatelliteInstallationNotify  iinsN  */

void CHsvDvbsInstallation_m_Priv::iinsN_OnEvent(int eventid, int value)
{
	//TraceNotice (m, "%s %d eventid %d\n", __FUNCTION__, __LINE__, eventid);
    switch(eventid)
    {
	case iinsN_EventInsStopped:
		mInitInstallationValues(InsStatus.Lnb);
		insN_OnEvent(eventid,value);
        break;

	case  iinsN_EventPkgInstallStart:
		TraceNotice (m, "PackageInstall Started ");
		insN_OnEvent(eventid, value);
		break;

	case	iinsN_EventPkgInstallEnd:
		/* Internal Event only needed */
		TraceNotice (m, "PackageInstall Finished ");
		insN_OnEvent(eventid, value);
		pmp_PmpSend(mPump, EvInstallComplete, (Nat32)0);
		break;
		
	case	iinsN_EventRegionScanEnd:
		TraceNotice (m, "RegionScan Finished ");
		insN_OnEvent(eventid, value);
		break;

	case	iinsN_EventLNBStart:
		TraceNotice (m, "Evnt Lnb Start ");
		insN_OnEvent(eventid, value);
		break;

	case	iinsN_EventLNBEnd:
		TraceNotice (m, "Evnt Lnb Start ");
		{
			insN_OnEvent(eventid, value);
			pmp_PmpSend(mPump, EvInstallComplete, (Nat32)0);
		}
		break;

    case iinsN_EventInsCompleted:
		if (InsStatus.Mode == MANUAL_MODE)
		{
			/* TODO: Check With Pavan what to do with the manual install services.
				How the sorting should be done for them */
			SET_INS_STATE(StSorting);
			pmp_PmpSend(mPump, EvSorting, (Nat32)0);
		}
		if(InsStatus.Mode == BACKGROUND_MODE)
			{
			TraceNotice (m, "iinsN_EventInsCompleted for background ");
			insN_OnEvent(eventid, value);
			}
        break;

	case	iinsN_EventInsFailed:
		if (InsStatus.Mode == PRESCAN_MODE)
		{
			TraceNotice (m, " Prescan Complete with error \n");
			SET_INS_STATE(StIdle);
			insN_OnEvent(insN_EventSatelliteNotFound,value);			
		}
        else if ((InsStatus.Mode ==  AUTO_MODE)  || (InsStatus.Mode == CAM_NIT_INSTALLATION_MODE))
        {
			pmp_PmpSend(mPump, EvInstallFailed, (Nat32)0);
        }
		else
		{ 
			SET_INS_STATE(StIdle);
			insN_OnEvent(eventid, value);
			
			/*Select Sqlite db, if installation is failed*/
			//pgdb_SelectChannelDatabase(pgdb_SqliteDatabase);
		}
		UnBlockDestination();
		break;

	case iinsN_EventSortCompleted:
		/* ANEESH: Here check the installation mode. And start database sync */
		if ((InsStatus.Mode == AUTO_MODE) || (InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == AUTOUPDATE_MODE) || (InsStatus.Mode == BCKGNDUPDATE_MODE) || (InsStatus.Mode == CAM_NIT_INSTALLATION_MODE) || (InsStatus.Mode == SSBYUPDATE_MODE))
		{
			TraceNotice (m, "Doing Sync from Temp to SQLITE ");
	/*		SET_INS_STATE(StDatabaseSync);
			InsStatus.FromDatabaseId = pgdb_TempDatabase;
			InsStatus.ToDatabaseId = pgdb_SqliteDatabase;
			InsStatus.TableInCopy = SAT_INFO_TABLE;
			InsStatus.IndexToCopy = 0;
			pmp_PmpSend(mPump, EvPerformDatabaseSync, (Nat32)NULL); */

			SET_INS_STATE(StSorting);
			pmp_PmpSend(mPump, EvSortComplete, (Nat32)NULL);
		}
		else
		{
			pmp_PmpSend(mPump, EvSortComplete, (Nat32)NULL);
		}
        break;

	case iinsN_EventChannelFound:
	case iinsN_EventChannelNotFound:
		/* These will come for manual installation. So at this time make the mode as Idle.*/
		if (InsStatus.Mode == MANUAL_MODE)
		{
			SET_INS_STATE(StIdle);
		}
		insN_OnEvent(eventid,value);
		break;

	/* Prescan will give following notifications. SatelliteFound, SatelliteNotFound & InsFailed */
	case	iinsN_EventSatelliteFound:
	case	iinsN_EventSatelliteNotFound:
		TraceNotice (m, " Prescan Complete ...\n");
		SET_INS_STATE(StIdle);
		insN_OnEvent(eventid,value);
		UnBlockDestination();
		break;

 	case iinsN_EventPkgParsingStarted:
	{
		TraceNotice (m, "hsvdvbsins_m.c %d>Package Parsing Started\n",__LINE__);
		insN_OnEvent(eventid,value);
	}
	break;

	case iinsN_EventPkgParsingCompleted:
	{
		TraceNotice (m, "hsvdvbsins_m.c %d>Package Parsing Complete\n",__LINE__);
		insN_OnEvent(eventid,value);
        pmp_PmpSend(mPump, EvInstallComplete, (Nat32)NULL);

	}
	break;
 	case iinsN_EventTriggerBckgndUpdateInstall:
	{
		TraceNotice (m, "%d Triggering Background Update Installation\n", __LINE__);
		insN_OnEvent(eventid,value);
	}
	break;
    
	default:    
		insN_OnEvent(eventid,value);
		break;
    }
}

/* provides IHsvSdmControlNotifyEx	ctrlN	*/

void CHsvDvbsInstallation_m_Priv::ctrlN_OnEvent(HsvDemux dmx, int eventid,int value)
{
    TraceNotice (m, "ctrlN_OnEvent callback Installation mde %d [%d] %d", InsStatus.Mode, eventid,value);
	//TraceNotice (m,"state %d mode %d",GET_INS_STATE, InsStatus.Mode);
	int mPackageId;
	HsvLnbSettings				LnbSettings;
    /* ANEESH: Check the State here. If installation state is Idle, it means the notificaiton
    is caused due to program selection. So start the backcground installation */
    //TraceNotice(m,"state %d",GET_INS_STATE);
    if ((GET_INS_STATE == StIdle) && (InsStatus.Mode != PRESCAN_MODE) && (InsStatus.Mode != PACKAGE_PARSING_MODE) && (InsStatus.Mode != TRICOLOR_REGION_PARSING_MODE) && (eventid == ctrlN_StartedCollection))
    {
        TraceNotice (m, "Background Installation triggered\n");
        InsStatus.Mode = BACKGROUND_MODE;
        ibckInstall_EnableBackgroundInstallation ();
    }
	if((InsStatus.Mode == BACKGROUND_MODE) && (eventid == ctrlN_StoppedCollection) && (GET_INS_STATE == StIdle))
	{
		mPackageId = pins_GetAttribute(IHsvSatelliteInstallation_InstallationBackground,IHsvSatelliteInstallation_AttributePackageId);
		//TraceNotice (m, "PackageID %d ", mPackageId);
		if(mPackageId == FREESAT_PACKAGE_ID)
		{
			//TraceNotice (m, "Start Collection Triggered with FreesatMinimalSdtOth");
			ctrl_StartCollection (HsvDmxMain,IHsvSdmControl2_FreesatMinimalSdtOth);
			//InsStatus.Mode = BACKGROUND_MODE;
		}
	}
    switch(InsStatus.Mode)
    {
        case AUTO_MODE:
		case UPDATE_MODE:
		case AUTOUPDATE_MODE:
		case MINIPRESCAN_MODE:
		case BCKGNDUPDATE_MODE:
		case CAM_NIT_INSTALLATION_MODE:
		case SSBYUPDATE_MODE:
			if (GET_INS_STATE == StGenericInstall)
			{
				hsvdvbsgeneric_ctrlN_OnEvent(dmx, eventid, value);
			}
			else if (GET_INS_STATE == StMiniPrescanInstallation)
			{
				iminiprescanctrlN_OnEvent(dmx, eventid, value);
			}
			else
			{
				ipackagectrlN_OnEvent(dmx, eventid, value);
			}
            break;
		case	ADDSAT_MODE:
			hsvdvbsgeneric_ctrlN_OnEvent(dmx, eventid, value);
			break;
        case MANUAL_MODE:
			hsvdvbsgeneric_ctrlN_OnEvent(dmx, eventid, value);
            break;
        case PRESCAN_MODE:
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
				if(LnbSettings.ConnectionType == LnbConnectionSatIp)
				{
					isatipprescanctrlN_OnEvent(dmx, eventid, value);
				}
				else
				{
					iprescanctrlN_OnEvent(dmx, eventid, value);
				}
			}
			break;
		case BACKGROUND_MODE:
			ibckctrlN_OnEvent (dmx, eventid, value);
			break;
    	case PACKAGE_PARSING_MODE:
         	ipackageparserctrlN_OnEvent(dmx, eventid, value);
        	break;
		case TRICOLOR_REGION_PARSING_MODE:
            hsvdvbstricolor_ctrlN_OnEvent(dmx,eventid,value);
            break;
		default:
			break;
	}
}

/* provides IPlfApiDvbsNotify	plfApidvbsN */

void CHsvDvbsInstallation_m_Priv::satfeapiN_OnLockChanged(Bool LockState)
{
	HsvLnbSettings				LnbSettings;
	switch(InsStatus.Mode)
    {
        case AUTO_MODE:
		case UPDATE_MODE:
		case AUTOUPDATE_MODE:
		case MINIPRESCAN_MODE:
		case BCKGNDUPDATE_MODE:
		case CAM_NIT_INSTALLATION_MODE:
		case SSBYUPDATE_MODE:
			if (GET_INS_STATE == StGenericInstall)
			{
				hsvdvbsgeneric_plfApidvbsN_OnLockChanged(LockState);
			}
			else if (GET_INS_STATE == StMiniPrescanInstallation)
			{
				iminiprescansatfrontendN_OnLockChanged(LockState);
			}
			else
			{
				ipackageplfApidvbsN_OnLockChanged(LockState);
			}
            break;
		case ADDSAT_MODE:
        case MANUAL_MODE:
			hsvdvbsgeneric_plfApidvbsN_OnLockChanged(LockState);
            break;
        case PRESCAN_MODE:
			
			if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
			{
				//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
				if(LnbSettings.ConnectionType == LnbConnectionSatIp)
				{
					isatipprescansatfrontendN_OnLockChanged(LockState);

				}
				else
				{
					iprescansatfrontendN_OnLockChanged(LockState);
				}
			}
			iprescansatfrontendN_OnLockChanged(LockState);
			break;
        case PACKAGE_PARSING_MODE:
            ipackageparsersatfrontendN_OnLockChanged(LockState);
            break;
		 case TRICOLOR_REGION_PARSING_MODE:
            hsvdvbstricolor_plfApidvbsN_OnLockChanged(LockState);
            break;
		default:
			break;
	}
}

void CHsvDvbsInstallation_m_Priv::satfeapiN_OnBlindScanEnd (void)
{
	switch(InsStatus.Mode)
    {
		
        case AUTO_MODE:
		case UPDATE_MODE:	
		case AUTOUPDATE_MODE:	
		case MINIPRESCAN_MODE:
		case CAM_NIT_INSTALLATION_MODE:
		case SSBYUPDATE_MODE:	
			if (GET_INS_STATE == StGenericInstall)
			{
				hsvdvbsgeneric_plfApidvbsN_OnBlindScanEnd();
			}
			else if (GET_INS_STATE == StMiniPrescanInstallation)
			{
				iminiprescansatfrontendN_OnBlindScanEnd();
			}
			else
			{
				ipackageplfApidvbsN_OnBlindScanEnd();
			}
            break;
		case ADDSAT_MODE:
			hsvdvbsgeneric_plfApidvbsN_OnBlindScanEnd();
			break;
        case PRESCAN_MODE:
			iprescansatfrontendN_OnBlindScanEnd();
			break;
		default:
			break;
	}
}


void CHsvDvbsInstallation_m_Priv::pins_StopSignalStrengthMeas(int lnb)
{
	HsvLnbSettings				LnbSettings;

	if (InsStatus.Mode == PRESCAN_MODE)
	{  
		if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
		{
			//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
			if(LnbSettings.ConnectionType == LnbConnectionSatIp)
			{
			  isatipprescan_StopSignalStrengthMeas(lnb);
			}
			else
			{
			  iprescan_StopSignalStrengthMeas(lnb);
			}
		}
	}
	else  if (InsStatus.Mode == MANUAL_MODE)
	{
		isigstr_StopSigStrMeasAll ();
  }
}

void CHsvDvbsInstallation_m_Priv::pins_StartSignalStrengthMeas(int lnb)
{

  HsvLnbSettings			  LnbSettings;

	if (InsStatus.Mode == PRESCAN_MODE)
	{  
		if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
		{
			//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
			if(LnbSettings.ConnectionType == LnbConnectionSatIp)
			{
				isatipprescan_StartSignalStrengthMeas(lnb);
			}
			else
			{
				iprescan_StartSignalStrengthMeas(lnb);
			}
		}
	}
	else if (InsStatus.Mode == MANUAL_MODE)
	{
		isigstr_StartSigStrMeasAll ();
	}
}

int CHsvDvbsInstallation_m_Priv::pins_GetSignalQuality(Nat32 Param)
{

	Int32 lReturn = 0;
	HsvLnbSettings			  LnbSettings;
	if (InsStatus.Mode == PRESCAN_MODE)
	{
		if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
		{
			if(LnbSettings.ConnectionType == LnbConnectionSatIp)
			{
				lReturn = isatipprescan_GetSignalQuality(Param);
			}
			else
			{
				lReturn = iprescan_GetSignalQuality(Param);
			}
		}
	}
	else if (InsStatus.Mode == MANUAL_MODE)
	{
		lReturn = isigstr_GetActualSignalStrength (isigstr_InsQsm, 0);
	}

	return lReturn;
}

int CHsvDvbsInstallation_m_Priv::pins_GetSignalStrength(Nat32 Param)
{
	int retValue = 0;
	HsvLnbSettings			  LnbSettings;

	if (InsStatus.Mode == PRESCAN_MODE)
	{
	   if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	   {
		   if(LnbSettings.ConnectionType == LnbConnectionSatIp)
		   {
			   retValue = isatipprescan_GetSignalStrength( Param);
		   }
		   else
		   {
			   retValue = iprescan_GetSignalStrength( Param);
		   }
	   }
	}
	else if (InsStatus.Mode == MANUAL_MODE)
	{
		retValue = isigstr_GetActualSignalStrength (isigstr_InsQsm, 0);
		if(!retValue)
		{
			retValue = isigstr_GetActualSignalStrength (isigstr_InsSsm, 0);
		}
	}
	return retValue;
}

FResult CHsvDvbsInstallation_m_Priv::pins_StartPredefinedListCopy (void)
{
	return ipredefcopy_StartPredefinedListCopy ();
}

void CHsvDvbsInstallation_m_Priv::strapiN_OnCompleted(HsvDestination dest, int spid)
{
    Nat16 pkgGrpId = 0;
    Nat32 pkgId = idvbset_GetAttribute (idvbset_AttributePackageId);  
    FResult retVal = ipackage_GetPackageGroupId (pkgId, &pkgGrpId);

 
    if ((InsStatus.Mode == BACKGROUND_MODE) || (pkgGrpId == 8) || (InsStatus.Mode == MANUAL_MODE))
    {
        istrapiN_OnCompleted(dest, spid);
    }
}

void CHsvDvbsInstallation_m_Priv::strapiN_OnAdded(HsvDestination dest, int spid, int key1, int key2, int key3)
{
//    TraceNotice(m,"%s() : %d strapiN_OnAdded with spid %d and key1 %d\n", __FUNCTION__, __LINE__, spid, key1);
	if (InsStatus.Mode == BACKGROUND_MODE || InsStatus.Mode == MANUAL_MODE)
	{
	//    TraceNotice(m,"%s() : %d \n", __FUNCTION__, __LINE__);
		istrapiN_OnAdded(dest, spid, key1, key2, key3);
	}
}
 
void CHsvDvbsInstallation_m_Priv::strapiN_OnChanged(HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
	if (InsStatus.Mode == BACKGROUND_MODE || InsStatus.Mode == MANUAL_MODE)
	{
		istrapiN_OnChanged(dest, spid, key1, key2, key3, eventid);
	}
}
        
void CHsvDvbsInstallation_m_Priv::strapiN_OnRemoved(HsvDestination dest, int spid, int key1, int key2, int key3)
{
	if (InsStatus.Mode == BACKGROUND_MODE || InsStatus.Mode == MANUAL_MODE)
	{
		istrapiN_OnRemoved(dest, spid, key1, key2, key3);
	}
}

//ICesCipCAMStatusNotify
void CHsvDvbsInstallation_m_Priv::cipStatusN_OnEvent (CIPlusStatus_e status)
{
    //TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    ipackageparsercipStatusN_OnEvent (status);
}

// ICesOperatorProfileNotify
void CHsvDvbsInstallation_m_Priv::opinsN_OnOpSearchStatus (Op_ProfileSearchStatus opStatus)
{
    //TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    ipackageopinsN_OnOpSearchStatus(opStatus);
}

void CHsvDvbsInstallation_m_Priv::opinsN_OnOpStatusInfo(Op_ProfileStatusInfo StatusInfo)
{
    //TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    ipackageopinsN_OnOpStatusInfo(StatusInfo);
    TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    ipackageparseropinsN_OnOpStatusInfo(StatusInfo);
}

void CHsvDvbsInstallation_m_Priv::opinsN_OnOpNIT(Op_ProfileNitData nitData)
{
     TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    ipackageopinsN_OnOpNIT(nitData);
}

void CHsvDvbsInstallation_m_Priv::opinsN_OnOpTune(Op_ProfileTuneData tuneData)
{
     TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    ipackageopinsN_OnOpTune(tuneData);
}


void CHsvDvbsInstallation_m_Priv::iminiprescanN_OnEvent (int EventId, int Param)
{
	Nat32	MiniPrescanResult = PACK_MINISCANRESULT (EventId, Param);

		TraceNotice(m,"iminiprescanN_OnEvent :  Event: %d", EventId);

		if(EventId == iminiprescanN_EventPreScanStopped)
		{
			mInitInstallationValues(InsStatus.Lnb);
			insN_OnEvent(iinsN_EventInsStopped,Param);
		}
		else
		{
			pmp_PmpSend(mPump, EvMiniPrescanResult, (Nat32)MiniPrescanResult);
		}
}

void CHsvDvbsInstallation_m_Priv::isyssetN_Notify(int property,int value)
{
}

	/*** TVPROVIDER IMPLEMENTATION START ***/
void CHsvDvbsInstallation_m_Priv::mInitializeTvProviderData (HsvPgdatTvProviderBlobData	*TvProviderData)
{
#define NO
#define NAME
#define NONE
#define A(x)    [0]


#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      TvProviderData->item siz = def;
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     TvProviderData->item siz = def;
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)      TvProviderData->item siz = def;
#define	TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)      TvProviderData->item siz = def;
#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, sat, srv, ts)      TvProviderData->item siz = def;
#define	TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)     TvProviderData->item siz = def;
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_SATINFO_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_VECTOR_ITEM


#undef NO
#undef NAME
#undef NONE
#undef A

}


int CHsvDvbsInstallation_m_Priv::pins_GetNumberOfDatabaseRecords(int TSDataOnly)
{
	int NoOfEntries = 0;


	Bool						RetVal = FALSE, IsPackage = FALSE;
	HsvPgdatPresetData			preset;
	HsvPgdatDigTSData			TsData;
	HsvPgdatDigServiceData		SvcData;
	int	From = 0, To = 0, count = 0,presetcount =0;
	int	channelno = -1;
	Nat32 PackageIndex = 0;
	
	if((InsStatus.Mode == MANUAL_MODE) && !TSDataOnly)
	{
		/* In case of manual installation switching should be done to the installed channel only */
		TsData.LnbNumber  =	pins_GetAttribute(pins_InstallationManual,pins_ManualInstallLnb);
		TsData.Frequency  = pins_GetAttribute(pins_InstallationManual,pins_ManualInstallFreq);
		TsData.Polarization =   pins_GetAttribute(pins_InstallationManual,pins_ManualInstallPolaraization);

		RetVal = pgdb_GetByKey (PTC_TABLE, (Address) &TsData);
		//TraceNotice (m,"%s %d>MANUAL_INSTALL RetVal[%d][%d][%d][%d]",__FUNCTION__,__LINE__,TsData.LnbNumber,TsData.Frequency,TsData.Polarization,RetVal);
		if (RetVal == TRUE)
		{
			SvcData.Tpid = TsData.Tpid;
			RetVal = pgdb_GetRange (SERVICE_TABLE , 1, (Address)&SvcData , &From , &To);
			//TraceNotice (m,"%s %d>MANUAL_INSTALL RetVal[%d][%d]",__FUNCTION__,__LINE__,SvcData.Tpid,RetVal);
			if (RetVal == TRUE)
			{
				NoOfEntries = (To - From) + 1;
			} 
			//TraceNotice (m,"%s %d NoOfRecords [%d] \n",__FUNCTION__,__LINE__,NoOfEntries);
		}
	}else if(TSDataOnly) {
		NoOfEntries = pgdb_GetNoRecords(PTC_TABLE);
	} else {
		NoOfEntries = pgdb_GetNoRecords(PRESET_TABLE);
	}

	TraceNotice (m ," Number of database records: %d, TSDataOnly : %d ",  NoOfEntries, TSDataOnly);
	return NoOfEntries;

}

void CHsvDvbsInstallation_m_Priv::mCollectPresetProviderData(HsvPgdatPresetData *PresetData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	int	PackageId = idvbset_GetAttribute (idvbset_AttributePackageId);
	
	TvProviderData->PresetNumber = PresetData->PresetNumber ;
	TvProviderData->OriginalNetworkId = PresetData->OriginalNetworkId ;
	TvProviderData->Tsid = PresetData->Tsid ;
	TvProviderData->ServiceId = PresetData->ServiceId ;
	TvProviderData->Frequency = PresetData->Frequency ;
	TvProviderData->LnbNumber = PresetData->LnbNumber;
	TvProviderData->Polarization = PresetData->Polarization;
	/*Since we go for MultipleVisibleService MultipleNumericSelect for Freesat:
	we update System Hidden and NumericSelect Attributes from Preset Table for that particular Index.*/
	if((PackageId == FREESAT_PACKAGE_ID) || (PackageId == TRICOLOR_SD_PACKAGE_ID) || (PackageId == TRICOLOR_HD_PACKAGE_ID))
	{
		TvProviderData->SystemHidden = PresetData->SystemHidden;
		TvProviderData->NumericSelect = PresetData->NumericSelect;
		//TraceNotice(m,"Freesat Preset Number: %d SysHid %d NumSel %d",TvProviderData->PresetNumber,TvProviderData->SystemHidden,TvProviderData->NumericSelect);
	}
	TvProviderData->FavoriteNumber = PresetData->FavoriteNumber;
	TvProviderData->VisibleService = PresetData->VisibleService;
	
}

void CHsvDvbsInstallation_m_Priv::mCollectDigSrvProviderData (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	int	PackageId = idvbset_GetAttribute (idvbset_AttributePackageId);
	
	TvProviderData->TextSubTitlePage = DigSrvcData->TextSubTitlePage ;
	TvProviderData->LogoURL = DigSrvcData->LogoURL ;
	TvProviderData->DecoderType = DigSrvcData->DecoderType ;
	TvProviderData->ModulationType = DigSrvcData->ModulationType ;
	TvProviderData->UserModifiedLogo = DigSrvcData->UserModifiedLogo ;
	TvProviderData->SAP = DigSrvcData->SAP ;
	TvProviderData->PreferredStereo = DigSrvcData->PreferredStereo ;
	TvProviderData->Ptc = DigSrvcData->Ptc ;
	TvProviderData->SymbolRate = DigSrvcData->SymbolRate ;
//	TvProviderData->StreamPriority = DigSrvcData->StreamPriority ;
	TvProviderData->AudioPid = DigSrvcData->AudioPid ;
	TvProviderData->VideoPid = DigSrvcData->VideoPid ;
	TvProviderData->PcrPid = DigSrvcData->PcrPid ;
	TvProviderData->NetworkId = DigSrvcData->NetworkId ;
	TvProviderData->LCN = DigSrvcData->LCN ;
	TvProviderData->ServiceType = DigSrvcData->ServiceType ;
	if((PackageId != FREESAT_PACKAGE_ID) && (PackageId != TRICOLOR_SD_PACKAGE_ID) && (PackageId != TRICOLOR_HD_PACKAGE_ID))
	{
		TvProviderData->SystemHidden = DigSrvcData->SystemHidden ;
		TvProviderData->NumericSelect = TRUE; /* ANEESH: TODO: Correct this as for Freesat some changes are made   DigSrvcData->NumericSelect ;*/
	}
	TvProviderData->Bandwidth = DigSrvcData->Bandwidth ;
	TvProviderData->ScrambledStatus = DigSrvcData->ScrambledStatus ;
	TvProviderData->IntHbbTvOption = DigSrvcData->IntHbbTvOption ;
	TvProviderData->UserHidden = DigSrvcData->UserHidden ;
	TvProviderData->NewPreset = DigSrvcData->NewPreset ;
	TvProviderData->VideoStreamType = DigSrvcData->VideoStreamType ;
	TvProviderData->DpTsid = DigSrvcData->DpTsid ;
	TvProviderData->AudioStreamType = DigSrvcData->AudioStreamType ;
	TvProviderData->DpServiceId = DigSrvcData->DpServiceId ;
	TvProviderData->Tpid = DigSrvcData->Tpid ;
	TvProviderData->PackageGroup = DigSrvcData->PackageGroup ;

	/*Private Data*/
	TvProviderData->SignalStrength = DigSrvcData->SignalStrength;
	TvProviderData->SignalQuality = DigSrvcData->SignalQuality;
	TvProviderData->AppsCookie = DigSrvcData->AppsCookie;
//	TvProviderData->TxtCookie = DigSrvcData->TxtCookie;
//	TvProviderData->CesvcCookie = DigSrvcData->CesvcCookie;
	TvProviderData->SDTVersion = DigSrvcData->SDTVersion;
	TvProviderData->NITVersion = DigSrvcData->NITVersion;
	TvProviderData->DateStamp = DigSrvcData->DateStamp;
//	TvProviderData->DeltaVolume = DigSrvcData->DeltaVolume;
//	TvProviderData->RCKeyCode = DigSrvcData->RCKeyCode;
	TvProviderData->PmtPid = DigSrvcData->PmtPid;
//	TvProviderData->StreamPriority = DigSrvcData->StreamPriority;
	TvProviderData->SecAudioPid = DigSrvcData->SecAudioPid;
	TvProviderData->LowPrioLCN = DigSrvcData->LowPrioLCN;
	TvProviderData->LowPrioVisibleService = DigSrvcData->LowPrioVisibleService;
	TvProviderData->FreeCiMode = DigSrvcData->FreeCiMode;
	TvProviderData->VideoDescPresent = DigSrvcData->VideoDescPresent;
	TvProviderData->ScramblingStatus = DigSrvcData->ScramblingStatus;
	TvProviderData->DuplicateSvc = DigSrvcData->DuplicateSvc;
//	TvProviderData->OUI = DigSrvcData->OUI;
	TvProviderData->ServiceListVersion = DigSrvcData->ServiceListVersion;
	TvProviderData->UserInstalled = DigSrvcData->UserInstalled;
	TvProviderData->SecAudioStreamType = DigSrvcData->SecAudioStreamType;
//	TvProviderData->EPGEnabled = DigSrvcData->EPGEnabled;
	TvProviderData->UserModifiedName = DigSrvcData->UserModifiedName;
	TvProviderData->ChannelLock = DigSrvcData->ChannelLock;
//	TvProviderData->PreferredFavorite = DigSrvcData->PreferredFavorite;
//	TvProviderData->PreferredNicam = DigSrvcData->PreferredNicam;
//	TvProviderData->HMBlanked = DigSrvcData->HMBlanked;
//	TvProviderData->HMProtectedChannel = DigSrvcData->HMProtectedChannel;
//	TvProviderData->HMMapChannelNo = DigSrvcData->HMMapChannelNo;
	TvProviderData->DvbType = DigSrvcData->DvbType;
//	TvProviderData->EPGShortInfo = DigSrvcData->EPGShortInfo;
	TvProviderData->MatchBrandFlag = DigSrvcData->MatchBrandFlag;
	TvProviderData->NumBrandIds = DigSrvcData->NumBrandIds;
//	TvProviderData->NewChannelMap = DigSrvcData->NewChannelMap;
	TvProviderData->InstalledSatelliteNumber = DigSrvcData->InstalledSatelliteNumber;
//	TvProviderData->IntEPGEnabled = DigSrvcData->IntEPGEnabled;
//	TvProviderData->BoolChannelLock = DigSrvcData->BoolChannelLock;
//	TvProviderData->RegionDepth = DigSrvcData->RegionDepth;
	TvProviderData->NewChannel = DigSrvcData->NewChannel;
	TvProviderData->HbbTvOption = DigSrvcData->HbbTvOption;
//	TvProviderData->PrimaryRegion = DigSrvcData->PrimaryRegion;
//	TvProviderData->SecondaryRegion = DigSrvcData->SecondaryRegion;
//	TvProviderData->TertiaryRegion = DigSrvcData->TertiaryRegion;
	TvProviderData->CountryCode = DigSrvcData->CountryCode;
	TvProviderData->HDSimulcastRepOnId = DigSrvcData->HDSimulcastRepOnId;
	TvProviderData->HDSimulcastRepTsId = DigSrvcData->HDSimulcastRepTsId;
	TvProviderData->HDSimulcastRepSvcId = DigSrvcData->HDSimulcastRepSvcId;
	TvProviderData->ParentalRating = DigSrvcData->ParentalRating;
	TvProviderData->ServiceIdentifier = DigSrvcData->ServiceIdentifier;
//	TvProviderData->UniqueId = DigSrvcData->UniqueId;
	TvProviderData->AdultGenere = DigSrvcData->AdultGenere;
	TvProviderData->FreesatServiceIdentifier = DigSrvcData->FreesatServiceIdentifier;
	TvProviderData->InteractiveServiceEnabled = DigSrvcData->InteractiveServiceEnabled;
	

//	memcpy ((void*)TvProviderData->TxtPages,(void *)DigSrvcData->TxtPages, 23*sizeof(Nat16));
	memcpy ((void*)TvProviderData->ChannelName,(void *)DigSrvcData->ChannelName,(MAXSERVICENAMELEN + 1)*sizeof(Nat16));
	
	memcpy ((void*)TvProviderData->MultipleVisibleService,(void *)DigSrvcData->MultipleVisibleService,8*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultipleNumericSelect,(void *)DigSrvcData->MultipleNumericSelect,8*sizeof(Nat16));
	memcpy ((void*)TvProviderData->BrandIds,(void *)DigSrvcData->BrandIds,23*sizeof(Nat16));
//	memcpy ((void*)TvProviderData->ExtChannelName,(void *)DigSrvcData->ExtChannelName,33*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultipleLCN,(void *)DigSrvcData->MultipleLCN,8*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultiplePreset,(void *)DigSrvcData->MultiplePreset,8*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultipleFavorite,(void *)DigSrvcData->MultipleFavorite,8*sizeof(Nat8));

       // Get the UniqueId corresponding to Preset Number
       mGetUniqueIdFromPresetNumber (DigSrvcData, TvProviderData);

}


void CHsvDvbsInstallation_m_Priv::mCollectDigTsProviderData (HsvPgdatDigTSData *TsData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->DecoderType = TsData->DecoderType;

	/*Private data*/
	TvProviderData->ASignalStrength = TsData->ASignalStrength;
	TvProviderData->VSignalStrength = TsData->VSignalStrength;
	TvProviderData->QSignalStrength = TsData->QSignalStrength;
	TvProviderData->CodeRate = TsData->CodeRate;
	TvProviderData->PtcListVersion = TsData->PtcListVersion;
	TvProviderData->TSVersion = TsData->TSVersion;
	TvProviderData->PlpId = TsData->PlpId;
	TvProviderData->BarkerMux = TsData->BarkerMux;
	TvProviderData->SDSDFrequency = TsData->SDSDFrequency;
	
}

void CHsvDvbsInstallation_m_Priv::mCollectSatInfoProviderData(HsvPgdatDigSatInfoData *SatInfoData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->LnbType = SatInfoData->LnbType ;
	TvProviderData->SatelliteId = SatInfoData->SatelliteId ;
	TvProviderData->OrbitalPosition = SatInfoData->OrbitalPosition ;
	memcpy ((void*)TvProviderData->SatelliteName,(void *)SatInfoData->SatelliteName,23*sizeof(Nat16));
}

void CHsvDvbsInstallation_m_Priv::mCollectDigTsTableData (HsvPgdatDigTSData *TsData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->DecoderType = TsData->DecoderType;

	/*Private data*/
	TvProviderData->BarkerMux = TsData->BarkerMux;
	TvProviderData->SDSDFrequency = TsData->SDSDFrequency;
	TvProviderData->OriginalNetworkId = TsData->OriginalNetworkId ;
	TvProviderData->Tsid = TsData->Tsid ;
	TvProviderData->Frequency = TsData->Frequency ;
	TvProviderData->LnbNumber = TsData->LnbNumber;
	TvProviderData->Polarization = TsData->Polarization;
	TvProviderData->ModulationType = TsData->ModulationType ;
	TvProviderData->Bandwidth = TsData->Bandwidth ;
	TvProviderData->SymbolRate = TsData->SymbolRate ;
	
}


void CHsvDvbsInstallation_m_Priv::pins_GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)
{
	HsvPgdatTvProviderBlobData		*TvProviderData = NULL;
	HsvPgdatPresetData				PresetData;
	HsvPgdatDigTSData				TsData;
	HsvPgdatDigServiceData			DigSrvcData;
	HsvPgdatDigSatInfoData			SatInfoData;
	Nat32 PackageIndex = 0;
	
	Bool						RetVal = FALSE,IsPackage = FALSE;
	int	From = 0, To = 0, count = 0,presetcount =0,TempIndex=0;
	
	//TraceNotice (m, " pins_GetTvProviderBlobDataByIndex for index %d with TSDataOnly %d", Index, TSDataOnly);
	TvProviderData = (HsvPgdatTvProviderBlobData*)TvProviderBlobData;
	mInitializeTvProviderData(TvProviderData);
	
	

	if((InsStatus.Mode == MANUAL_MODE) && !TSDataOnly)
	{
		/* In case of manual installation switching should be done to the installed channel only */
		TsData.LnbNumber  =	pins_GetAttribute(pins_InstallationManual,pins_ManualInstallLnb);
		TsData.Frequency  = pins_GetAttribute(pins_InstallationManual,pins_ManualInstallFreq);
		TsData.Polarization =   pins_GetAttribute(pins_InstallationManual,pins_ManualInstallPolaraization);

		RetVal = pgdb_GetByKey (PTC_TABLE, (Address) &TsData);
		//TraceNotice (m,"%s %d>MANUAL_INSTALL RetVal[%d][%d][%d][%d]",__FUNCTION__,__LINE__,TsData.LnbNumber,TsData.Frequency,TsData.Polarization,RetVal);
		if (RetVal == TRUE)
		{
			DigSrvcData.Tpid = TsData.Tpid;
			//TraceNotice (m,"%s %d>  [%d]",__FUNCTION__,__LINE__,TsData.Tpid);
			RetVal = pgdb_GetRange (SERVICE_TABLE , 1, (Address)&DigSrvcData , &From , &To);
			//TraceNotice (m,"%s %d>  From[%d] To[%d]",__FUNCTION__,__LINE__,From,To);
			if (RetVal == TRUE)
			{
				if (pgdb_GetByIndex (SERVICE_TABLE, (From + Index), (Address)&DigSrvcData) == TRUE)
				{
					pins_GetUserPackageIndex(&PackageIndex, &IsPackage);
					if(PackageIndex == ASTRA_LCN_BOUQUET_ID)
					{
						PresetData.PresetNumber = DigSrvcData.MultiplePreset[0];			
					}
					else
					{
						PresetData.PresetNumber = DigSrvcData.PresetNumber;
					}
								
					
					
					//TraceNotice (m,"%s %d>  PresetNumber[%d] index[%d] ",__FUNCTION__,__LINE__,PresetData.PresetNumber,(From + Index));
					if (pgdb_GetIndex(PRESET_TABLE, &TempIndex, (Address)&PresetData ) == TRUE);
					{
						Index = TempIndex;
					}
				}
			} 
			//TraceNotice (m,"%s %d Index [%d] \n",__FUNCTION__,__LINE__,Index);
		}
	}

	/* Aneesh: TODO: Once completely moved to srtdb, remove the active database setting */
	pgdb_SelectChannelDatabase(pgdb_TempDatabase);
	
	if(TSDataOnly)
	{
		if (TRUE == pgdb_GetByIndex(PTC_TABLE,Index, (Address)&TsData))
		{
			mCollectDigTsTableData(&TsData,TvProviderData);
		}
		else 
		{
			//TraceNotice (m, "pgdb_GetByIndex failed for Index %d ", Index);
		}
	}
	else if (TRUE == pgdb_GetByIndex(PRESET_TABLE,Index, (Address)&PresetData))
	{
		mCollectPresetProviderData(&PresetData,TvProviderData);

		//TraceNotice (m, "Digital Preset ");
		ASSIGN_SVC_FROM_PRESET(DigSrvcData,PresetData);
		if (pgdb_GetByKey(SERVICE_TABLE,&DigSrvcData) == TRUE)
		{
			mCollectDigSrvProviderData (&DigSrvcData, TvProviderData);
			ASSIGN_TS_FROM_DIGSRV(TsData, DigSrvcData);
			if (pgdb_GetByKey(PTC_TABLE,&TsData) == TRUE)
			{
				mCollectDigTsProviderData(&TsData,TvProviderData);
			}
			SatInfoData.LnbNumber = PresetData.LnbNumber;				
			//TraceNotice (m, " lnb number %d ", SatInfoData.LnbNumber);
			if(pgdb_GetByKey(SAT_INFO_TABLE,&SatInfoData) == TRUE)
			{
				//TraceNotice (m, " getby key success %d ", SatInfoData.LnbNumber);
				mCollectSatInfoProviderData(&SatInfoData,TvProviderData);
			}
			
		}
		else
		{
			//TraceNotice (m, "pgdb_GetByKey failed for Service Table ");
		}
	}
	else 
	{
		//TraceNotice (m, "pgdb_GetByIndex failed for Index %d ", Index);
	}

}

void CHsvDvbsInstallation_m_Priv::mAddPresetData(HsvPgdatTvProviderBlobData *TvpData)
{
	HsvPgdatPresetData				PresetData, tmp_preset;

#define NON_PRESET(item, type, bit, siz, def)
#define PRESET(item, type, bit, siz, def) PresetData.item = TvpData->item;

#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, preset, ana, srv, ts)      preset(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      PresetData.item = TvpData->item;
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)    
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_SATINFO_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_VECTOR_ITEM


#undef PRESET
#undef NON_PRESET

	tmp_preset.PresetNumber = PresetData.PresetNumber;
	if (TRUE == pgdb_GetByKey(PRESET_TABLE,(Address)&tmp_preset))
	{
		pgdb_Update(PRESET_TABLE,(Address)&PresetData);
		//TraceNotice(m,"Upading the Preset Table from TVProvider data for Preset :%d",PresetData.PresetNumber);
	}
	else
	{
		pgdb_Add(PRESET_TABLE,(Address)&PresetData);
		//TraceNotice(m,"Adding the Preset Table with TVProvider data for Preset :%d",PresetData.PresetNumber);
	}
	

	

}
	
void CHsvDvbsInstallation_m_Priv::mAddSatInfoData(HsvPgdatTvProviderBlobData *TvpData)
{

	HsvPgdatDigSatInfoData		SatInfoData, tmp_satinfo;

#define NON_SATINFO(item, type, bit, siz, def)
#define SATINFO(item, type, bit, siz, def) SatInfoData.item = TvpData->item;

#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, sat, srv, ts)      sat(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)      SatInfoData.item = TvpData->item;
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)    
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_SATINFO_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_VECTOR_ITEM


#undef SATINFO
#undef NON_SATINFO


	/*Copy vector items*/

	memcpy ((void*)SatInfoData.SatelliteName,(void *)TvpData->SatelliteName,23*sizeof(Nat16));

	tmp_satinfo.LnbNumber = SatInfoData.LnbNumber;
	if (TRUE == pgdb_GetByKey(SAT_INFO_TABLE,(Address)&tmp_satinfo))
	{
		pgdb_Update(SAT_INFO_TABLE,(Address)&SatInfoData);
		//TraceNotice(m,"Updating the SatInfo Table from TVProvider data for LNBNumber :%d",SatInfoData.LnbNumber);
	}
	else
	{
		pgdb_Add(SAT_INFO_TABLE,(Address)&SatInfoData);
		//TraceNotice(m,"Adding the SatInfo Table from TVProvider data for LNBNumber :%d",SatInfoData.LnbNumber);
	}

}

void CHsvDvbsInstallation_m_Priv::mAddDigSrvData(HsvPgdatTvProviderBlobData *TvpData)
{
	HsvPgdatDigServiceData			DigSrvcData, tmp_srvcdata;
	pgdb_Initialise(SERVICE_TABLE,&DigSrvcData);
	pgdb_Initialise(SERVICE_TABLE,&tmp_srvcdata);
	
#define NON_DIGSRVC(item, type, bit, siz, def)
#define DIGSRVC(item, type, bit, siz, def) DigSrvcData.item = TvpData->item;
	
#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, sat, srv, ts)      srv(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     DigSrvcData.item = TvpData->item;
#define	TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)    
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_SATINFO_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_VECTOR_ITEM
	
	
#undef DIGSRVC
#undef NON_DIGSRVC

	/*Copy vector items*/
	memcpy ((void*)DigSrvcData.ChannelName,(void *)TvpData->ChannelName,(MAXSERVICENAMELEN + 1)*sizeof(Nat16));

	memcpy ((void*)DigSrvcData.SatelliteName,(void *)TvpData->SatelliteName,23*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultipleVisibleService,(void *)TvpData->MultipleVisibleService,8*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultipleNumericSelect,(void *)TvpData->MultipleNumericSelect,8*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.BrandIds,(void *)TvpData->BrandIds,23*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultipleLCN,(void *)TvpData->MultipleLCN,8*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultiplePreset,(void *)TvpData->MultiplePreset,8*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultipleFavorite,(void *)TvpData->MultipleFavorite,8*sizeof(Nat8));

       //Based on Preset value, copy UniqueId to corresponding position in UniqueIds array
       mUpdateUniqueIds (&DigSrvcData, TvpData);
       
	/* Assign Keys */
	tmp_srvcdata.Tpid = DigSrvcData.Tpid;
	tmp_srvcdata.ServiceId = DigSrvcData.ServiceId;

	if (TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)&tmp_srvcdata))
	{
		pgdb_Update(SERVICE_TABLE,(Address)&DigSrvcData);
	//	TraceNotice(m,"Upadating the Service Table from TVProvider data [%d] [%d] [%d] [%d] [%d]",DigSrvcData.OriginalNetworkId,DigSrvcData.ServiceId,
		//	DigSrvcData.Frequency,DigSrvcData.Polarization,DigSrvcData.UserModifiedName);
		
	}
	else
	{
		pgdb_Add(SERVICE_TABLE,(Address)&DigSrvcData);
		//TraceNotice(m,"Adding Service from TVProvider data [%d] [%d] [%d] [%d]",DigSrvcData.OriginalNetworkId,DigSrvcData.ServiceId,
		//	DigSrvcData.Frequency,DigSrvcData.Polarization);
	}
}


void CHsvDvbsInstallation_m_Priv::mAddDigTsData(HsvPgdatTvProviderBlobData *TvpData)
{

	HsvPgdatDigTSData			DigTsData, tmp_tsdata;

#define NON_DIGTS(item, type, bit, siz, def)
#define DIGTS(item, type, bit, siz, def) DigTsData.item = TvpData->item;
	
#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, sat, srv, ts)      ts(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     DigTsData.item = TvpData->item;
#define	TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)    
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_SATINFO_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_VECTOR_ITEM
	
	
#undef DIGTS
#undef NON_DIGTS

	/* Assign Keys */
	tmp_tsdata.LnbNumber = DigTsData.LnbNumber;
	tmp_tsdata.Frequency = DigTsData.Frequency;
	tmp_tsdata.Polarization = DigTsData.Polarization;

	if (TRUE == pgdb_GetByKey(PTC_TABLE,(Address)&tmp_tsdata))
	{
		pgdb_Update(PTC_TABLE,(Address)&DigTsData);
		//TraceNotice(m,"Upadating the TS Table from TVProvider data LNBNumber: [%d] Freq: [%d] Pol: [%d] ",DigTsData.LnbNumber,DigTsData.Frequency,DigTsData.Polarization);
	}
	else
	{
		pgdb_Add(PTC_TABLE,(Address)&DigTsData);
		//TraceNotice(m,"Adding the TS Table from TVProvider data LNBNumber: [%d] Freq: [%d] Pol: [%d] ",DigTsData.LnbNumber,DigTsData.Frequency,DigTsData.Polarization);
	}


}

void CHsvDvbsInstallation_m_Priv::AddSatInfo(int LnbNumber, HsvLnbSettings *LnbSettings)
{
	HsvSatelliteMapping			MappedSatellite;
	HsvSatelliteMapping			UnknownSatelliteMapping;
	HsvPgdatDigSatInfoData		SatInfo;
	char						LnbName [10];

	/* Check Unknown Satellite */
	UnknownSatelliteMapping.OrbitalPosition = 0;
	UnknownSatelliteMapping.EastWestFlag = 0;
	iprescanparser_GetSatelliteAttributeByPosition (&UnknownSatelliteMapping);
	//TraceNotice (m, "LnbNumber %d Unknown Sat %d Cur %d ", LnbNumber,UnknownSatelliteMapping.SatelliteId,LnbSettings->LnbSettings[LnbNumber].SatelliteId); 
	if (LnbSettings->LnbSettings[LnbNumber].SatelliteId != UnknownSatelliteMapping.SatelliteId)
	{
		MappedSatellite.SatelliteId = LnbSettings->LnbSettings[LnbNumber].SatelliteId;
		if(iprescanparser_GetSatelliteAttributeById (&MappedSatellite))
		{
			SatInfo.LnbNumber = LnbNumber;
			SatInfo.LnbType = LnbSettings->LnbSettings[LnbNumber].LnbType;
			SatInfo.OrbitalPosition = MappedSatellite.OrbitalPosition;
			SatInfo.SatelliteId = MappedSatellite.SatelliteId;
			memcpy (SatInfo.SatelliteName, MappedSatellite.SatelliteName, sizeof(SatInfo.SatelliteName));
			TraceNotice (m, "1: Satellie with Sat.ID %d will be added at LnbNumber %d", SatInfo.SatelliteId,SatInfo.LnbNumber); 
		}			
	}
	else
	{
		SatInfo.LnbNumber = LnbNumber;
		SatInfo.LnbType = LnbSettings->LnbSettings[LnbNumber].LnbType;
		SatInfo.OrbitalPosition = UnknownSatelliteMapping.OrbitalPosition;
		SatInfo.SatelliteId = UnknownSatelliteMapping.SatelliteId;
		/* Should display Sat - <Lnb Number > */
		sprintf (LnbName, "Sat - %d", LnbNumber);
		charsetutil_MbToWc((Nat8*)LnbName, strlen(LnbName), SatInfo.SatelliteName, MAX_SATELLITE_NAME_LEN, FALSE);
	}
	
	if (pgdb_Add (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		TraceNotice (m, "Satellie with Sat.ID %d added at LnbNumber %d", SatInfo.SatelliteId,SatInfo.LnbNumber); 
	}
	else
	{
		TraceNotice (m, "pgdb_Add failed for LnbNumber %d", LnbNumber); 
	}

}


void CHsvDvbsInstallation_m_Priv::LoadSatInfoFromSettings()
{
	HsvLnbSettings				LnbSettings;
	int i;

	//TraceNotice(m,"%s: %d",__FUNCTION__,__LINE__);
	
	if (err_Ok == idvbset_GetLnbSettings (&LnbSettings))
	{
		//TraceNotice(m,"%s: %d: Connection type: %d",__FUNCTION__,__LINE__,LnbSettings.ConnectionType);
		if(LnbSettings.ConnectionType != LnbConnectionSatIp)
		{
			if((LnbSettings.LnbSettings[0].LnbStatus == LnbInstalled) || (LnbSettings.LnbSettings[0].LnbStatus == LnbManualInstalled))
			{
				AddSatInfo(0,&LnbSettings);
			}
		}
		
		if((LnbSettings.ConnectionType == LnbConnectionDiSeqcMini) || (LnbSettings.ConnectionType == LnbConnectionUnicableSwitch) || (LnbSettings.ConnectionType == LnbConnectionDiSeqc1_0))
		{
			if((LnbSettings.LnbSettings[1].LnbStatus == LnbInstalled) || (LnbSettings.LnbSettings[1].LnbStatus == LnbManualInstalled))
			{
				AddSatInfo(1,&LnbSettings);
			}
		}
		else if(LnbSettings.ConnectionType == LnbConnectionDiSeqc1_0)
		{
			if((LnbSettings.LnbSettings[2].LnbStatus == LnbInstalled) || (LnbSettings.LnbSettings[2].LnbStatus == LnbManualInstalled))
			{
				AddSatInfo(2,&LnbSettings);
			}
			if((LnbSettings.LnbSettings[3].LnbStatus == LnbInstalled) || (LnbSettings.LnbSettings[3].LnbStatus == LnbManualInstalled))
			{
				AddSatInfo(3,&LnbSettings);
			}
		}
		else if(LnbSettings.ConnectionType == LnbConnectionSatIp)
		{
			for(i = 0; i < MAX_NO_OF_SATELLITES; i++)
			{
				if(LnbSettings.LnbSettings[i].LnbStatus == LnbInstalled)
				{
					AddSatInfo(i,&LnbSettings);
					break;
				}
				
			}
			
		}
	}
}


void CHsvDvbsInstallation_m_Priv::pins_AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear)
{
	if(Clear)
	{
		pgdb_SelectChannelDatabase (pgdb_TempDatabase);
		pgdb_ClearTable(pgdb_GetCurrentTable());
		//TraceNotice(m,"RAM copy cleared");
		iprescanparser_ExtractPreScanTableFromXml();
		LoadSatInfoFromSettings();
	}
	else
	{
		//TraceNotice(m,"pins_AddTvpData Preset: [%d] onid: [%d] service: [%d] Freq: [%d] TPID: [%d] ",TvpData->PresetNumber,TvpData->OriginalNetworkId,TvpData->ServiceId,TvpData->Frequency,TvpData->Tpid);
		mAddPresetData(TvpData);
		mAddDigSrvData(TvpData);
		mAddSatInfoData(TvpData);
		mAddDigTsData(TvpData);
	}

}


void CHsvDvbsInstallation_m_Priv::mGetUniqueIdFromPresetNumber (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData)
{
    int loopCount = 0;
    int mPackageId = pins_GetAttribute(InsStatus.Mode, IHsvSatelliteInstallation_AttributePackageId);;

    //TraceNotice (m, "%s() %d : PackageID %d ", __FUNCTION__, __LINE__, mPackageId);
    /* Masking mPackageId with 0xFFFF for Fransat PackageId, since for fransat first 16 bits are package id and next 16 bits are bouquet id */
    if (((mPackageId & 0xFFFF) == FRANSAT_PACKAGE_ID) || (mPackageId == FREESAT_PACKAGE_ID) || (mPackageId == ASTRA_LCN_BOUQUET_ID)) // package group id
    {
        for (loopCount = 0; loopCount < MAX_NUM_PRESET_ENTRY; ++loopCount)
        {
            if (TvpData->PresetNumber == TvpData->MultiplePreset[loopCount]) 
            {
                //TraceNotice(m,"[%s] [%d] Preset : %d, MultiplePreset[%d] : %d, UniqueId %d \n", __FUNCTION__, __LINE__, TvpData->PresetNumber, 
                                        //loopCount, TvpData->MultiplePreset[loopCount], DigSrvcData->UniqueIds[loopCount]);   
                TvpData->UniqueId = DigSrvcData->UniqueIds[loopCount];
                break;
            }
        }
    }
    else
    {
        TvpData->UniqueId = DigSrvcData->UniqueIds[0];
    }
    //TraceNotice(m,"[%s] [%d] : Service (OnId, SvcId, Freq, StreamPriority, PresetNo) {%d %d %d %d %d}, UniqueId %d  \n", 
//                            __FUNCTION__, __LINE__, DigSrvcData->OriginalNetworkId, DigSrvcData->ServiceId, DigSrvcData->Frequency,
  //                          DigSrvcData->StreamPriority, TvpData->PresetNumber, TvpData->UniqueId);
}


void CHsvDvbsInstallation_m_Priv::mUpdateUniqueIds (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData)
{
    int arrayIndex = 0;
    int loopCount = 0;
    HsvPgdatDigServiceData tempSvcData;
    int mPackageId = pins_GetAttribute(InsStatus.Mode, IHsvSatelliteInstallation_AttributePackageId);;

    /* Assign Keys */
    tempSvcData.Tpid = DigSrvcData->Tpid;
    tempSvcData.ServiceId = DigSrvcData->ServiceId;
    
    if (TRUE == pgdb_GetByKey (SERVICE_TABLE, (Address) &tempSvcData))
    {         
//        TraceNotice (m, "%s() %d : PackageID %d ", __FUNCTION__, __LINE__, mPackageId);
        /* Masking mPackageId with 0xFFFF for Fransat PackageId, since for fransat first 16 bits are package id and next 16 bits are bouquet id */
        if (((mPackageId & 0xFFFF) == FRANSAT_PACKAGE_ID) || (mPackageId == FREESAT_PACKAGE_ID) || (mPackageId == ASTRA_LCN_BOUQUET_ID)
			 || (mPackageId == TRICOLOR_SD_PACKAGE_ID) || (mPackageId == TRICOLOR_HD_PACKAGE_ID)) // package group id
        {   
            //For Multiple LCN supported packages, find the arrayIndex of UniqueId based on preset value
            for (loopCount = 0; loopCount < MAX_NUM_PRESET_ENTRY; ++loopCount)
            {
                if (TvpData->PresetNumber == TvpData->MultiplePreset[loopCount]) 
                {
  //                  TraceNotice(m,"[%s] [%d] Preset : %d, MultiplePreset[%d] : %d\n", __FUNCTION__, __LINE__, TvpData->PresetNumber, loopCount, TvpData->MultiplePreset[loopCount]);   
                    arrayIndex = loopCount;
                    break;
                }
            }
        }
        else
        {
            arrayIndex = 0;
        }
    }
    else
    {
        //No entry exists in SERVICE_TABLE. So update the UniqueId in the 0th index
        arrayIndex = 0;
    }    
   /* TraceNotice(m,"[%s] [%d] : Service (OnId, SvcId, Freq, StreamPriority, PresetNo) {%d %d %d %d %d}, UniqueId %d, arrayIndex %d  \n", 
                            __FUNCTION__, __LINE__, DigSrvcData->OriginalNetworkId, DigSrvcData->ServiceId, DigSrvcData->Frequency,
                            DigSrvcData->StreamPriority, TvpData->PresetNumber, TvpData->UniqueId, arrayIndex);
*/
    //Copy UniqueIds array from DB to DigSrvcData. This is required for TV Bootup case.
    for (loopCount = arrayIndex - 1; loopCount >= 0; --loopCount)
    {
        DigSrvcData->UniqueIds[loopCount] = tempSvcData.UniqueIds[loopCount];
    }

    DigSrvcData->UniqueIds[arrayIndex] = TvpData->UniqueId;
}


void CHsvDvbsInstallation_m_Priv::pins_SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *tvpData)
{	
    HsvPgdatDigServiceData DigSrvcData;
    pgdb_Initialise (SERVICE_TABLE, &DigSrvcData);

    /* Assign Keys */
    DigSrvcData.Tpid = tvpData->Tpid;
    DigSrvcData.ServiceId = tvpData->ServiceId;

    if (TRUE == pgdb_GetByKey (SERVICE_TABLE, (Address) &DigSrvcData))
    {
        //Based on Preset value, copy UniqueId to corresponding position in UniqueIds array
        mUpdateUniqueIds (&DigSrvcData, tvpData);
        
        pgdb_Update(SERVICE_TABLE, (Address)&DigSrvcData);
        //TraceNotice(m,"Upadating the Service Table from TVProvider data [%d] [%d] [%d] [%d]", DigSrvcData.OriginalNetworkId,
                                //DigSrvcData.ServiceId, DigSrvcData.Frequency,DigSrvcData.Polarization);

    }
    else
    {
        //TraceNotice (m,  "Error : Failed to find entry in SERVICE_TABLE for updating UniqueId \n");
    }
}
	

	/*** TVPROVIDER IMPLEMENTATION END ***/
