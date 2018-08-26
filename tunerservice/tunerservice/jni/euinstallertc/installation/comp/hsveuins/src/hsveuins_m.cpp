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
 *          %name: hsveuins_m.c %
 *       %version: TVG_FusionR3_23 %
 * %date_modified: Tue Apr 07 11:24:33 2009 %
 *    %derived_by: nareshj % 
 */

/****************************************************************************
  1.pvn: handle installation states correctly with dvbc coming into picture
  2.
 ****************************************************************************/

/****************************************************************************
 * Local include files
 ****************************************************************************/

#include "_hsveuins_m.h"
#include "stub.h"
#include <utils/Log.h>
#include <android/log.h>
#include <utils/String8.h>
TRACESYMBOL(m, "dvb/installation/hsveuins_m")

#include "hsveuins_m.h"
#include "HtvDebug.h"
//#include "hsveuins_mSourceSetup.c"



#ifndef __cplusplus

#else

#endif









ModuleLifeCycle CHsvEuropeInstallation_m_Priv::s__mModuleLifeCycle = TurnedOff;

Nat16 CHsvEuropeInstallation_m_Priv::s__mBarkerMuxONID = 0xFFFF,CHsvEuropeInstallation_m_Priv::s__mBarkerMuxTSID = 0xFFFF;




Pump CHsvEuropeInstallation_m_Priv::s__mPump;

TypeInstallationStatus CHsvEuropeInstallation_m_Priv::s__InsStatus;

Bool CHsvEuropeInstallation_m_Priv::s__InsCompleted = FALSE;
   
int CHsvEuropeInstallation_m_Priv::s__CurrentFrequency = 0;

int CHsvEuropeInstallation_m_Priv::s__LastProgressStatus = 0;

int CHsvEuropeInstallation_m_Priv::AnalogEnabledStatus = 0; 
int CHsvEuropeInstallation_m_Priv::s__InstallationPassSwitchOver = 0;                            

Bool CHsvEuropeInstallation_m_Priv::s__mCamProfile0Installation = FALSE;

int CHsvEuropeInstallation_m_Priv::s__CurLCNControlMode = 1;

//extern int divsupp_PresetNameLength;
//divsupp_PresetNameLength = div_PresetNameLength;










const FunctionNat32 CHsvEuropeInstallation_m_Priv::EventActionMatrix[][10] =
{
						/*  StIdle,              StSourceSetupWait,      StDigital,            StAnalog,             StPreSorting,         StSorting            */
    /* EvStart              */  { FNADDR(FuncStartInstallation), NULL,                   NULL,                 NULL,                 NULL,                 NULL                 }, /* EvStart */
    /* EvStop               */  { NULL,                  FNADDR(FuncStopInstallation),   FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation) }, /* EvStop */  
    /* EvSourceSetupApplied */  { NULL,                  FNADDR(FuncSourceSetupApplied), NULL,                 NULL,                 NULL,                 NULL,                }, /* EvSourceSetupApplied */
    /* EvMakeDecision       */  { NULL,                  NULL,                   FNADDR(FuncMakeDecision),     FNADDR(FuncMakeDecision),     NULL,                 NULL,                }, /* EvMakeDecision */
    /* EvPreSorting         */  { NULL,                  NULL,                   NULL,                 NULL,                 FNADDR(FuncPreSorting),       NULL,                }, /* EvPreSorting */
    /* EvSorting            */  { NULL,                  NULL,                   NULL,                 NULL,                 NULL,                 FNADDR(FuncSorting)          }, /* EvSorting */
    /* EvDummy              */  { NULL,                  NULL,                   NULL,                 NULL,                 NULL,                 NULL                 },  /* EvSortComplete */
    /* EvSortComplete       */  { NULL,                  NULL,                   NULL,                 NULL,                 NULL,                 FNADDR(FuncSortComplete)     },  /* EvSortComplete */
	/* EvSearchInProgress   */  { NULL,                  NULL,                   FNADDR(FuncSearchInProgress), FNADDR(FuncSearchInProgress), FNADDR(FuncSearchInProgress), FNADDR(FuncSearchInProgress) }  /* EvSearchInProgress */
};


inline void CHsvEuropeInstallation_m_Priv::mPumpHandler(int event, Nat32 param)
{
    TraceDebug(m,"%s %d event %d param %d state %d", __FUNCTION__, __LINE__, event, (int)param, GET_INS_STATE);
    if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
    {
        //TraceDebug(m,"%s %d event %d param %d state %d", __FUNCTION__, __LINE__, event, (int)param, GET_INS_STATE);
        if(EventActionMatrix[event][GET_INS_STATE] != NULL)
        {
            //TraceDebug(m,"%s %d event %d param %d state %d", __FUNCTION__, __LINE__, event, (int)param, GET_INS_STATE);
            FPCALL(EventActionMatrix[event][GET_INS_STATE])(param);
        }
    }
}

inline void CHsvEuropeInstallation_m_Priv::FuncStartInstallation(Nat32 param)
{
    Bool Proceed = TRUE;
    int NetworkOperator;
	InsCompleted = FALSE;
	LastProgressStatus = 0;
	CurrentFrequency = pins_GetMinFrequency();
	mBarkerMuxONID= 0xFFFF;            
	mBarkerMuxTSID= 0xFFFF;

	TraceNotice(m,"%s %d InsStatus.Mode %d InsStatus.Pass %d", __FUNCTION__, __LINE__, InsStatus.Mode, InsStatus.Pass);
    NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

    if( (InsStatus.Mode == MANUAL_MODE) && (InsStatus.Country == cids_CountryNetherlands) && 
            ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)) )
    {
        Proceed = FALSE;
    }
    else if( (InsStatus.Mode == MANUAL_MODE) && ((InsStatus.Country == cids_CountryBelgium) && (NetworkOperator == rins_Telenet)) )
    {   
        // Telenet also does not allow non NIT/NID based installations.
        Proceed = FALSE;
    }
	else if((InsStatus.Mode == MANUAL_MODE) && mIsCanalDigitalorYouSeeOperatorSupported())
    {
    	// This case for Canal Digital and YouSee operator
        Proceed = FALSE;
    }
	
	hsvdvbtins_digacq_InitialiseTotalChannels();
	hsvdvbcins_digacq_InitialiseTotalChannels();
	hsvdvbtmpegins_digacq_InitialiseTotalChannels();
	hsvziggoins_dataacq_InitialiseTotalChannels();
	hsvcanaldigitalins_dataacq_InitialiseTotalChannels();
	hsvprins_prins_InitialiseTotalChannels ();
	hsvdvbcamins_dataacq_InitialiseTotalChannels();

	InsStatus.DigitalChannelsRemoved = 0;
	if (sysset_GetPbsMode() && sysset_GetDvbtSetting() && sysset_GetDvbcSetting()) // [HTV]
	{
		int orgMedium = pgctl_GetSelectedMedium();
			
		if (orgMedium == pins_Cable)
		{
			pgctl_SetSelectedMedium(pins_Terrestrial);
		}
		else 
		{
			pgctl_SetSelectedMedium(pins_Cable);
		}

		mInitInstallationValues(param, TRUE);
		pgctl_SetSelectedMedium(orgMedium);
	}
    mInitInstallationValues(param, TRUE);

    if(Proceed)
    {
        mctl_Stop(HsvMain); 
    }

    pgdb_ClearTable(TEMP_PTC_TABLE);
    pgdb_ClearTable(TEMP_SERVICE_TABLE);

    if((InsStatus.Mode == AUTO_MODE) || (InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == CAM_MODE))
    {
        pgdb_EnableAutoCommit(FALSE);
		if(InsStatus.Mode == UPDATE_MODE)
		{
			pgdb_MasterEnableEvents(TRUE);
		}
		/*  Need to make EnableEvents as FALSE during auto installation. Because now during background installation	
			EnableEvents are made TRUE. So for safety adding it */
		if (InsStatus.Mode == AUTO_MODE)
		{
			pgdb_MasterEnableEvents(FALSE);
		}
    }
	
    switch(InsStatus.Mode)
    {
        case AUTO_MODE:
			//TraceNotice (m,"Save Channel maps to backup triggered");
			pgdb_SaveChannelMapsToBackup ();
           // pgdb_ClearTable(pgdb_GetCurrentTable());
			/* ANEESH: DATABASEOPTIMIZATION */
			pgdb_SelectActiveChannelDatabase (pgdb_TempDatabase);
			pgdb_ClearTable(pgdb_GetCurrentTable());
			/* ANEESH: TODO: Right now we are clearing the analog database before next installation.
			This will have impact if user stops the instalaltion in between. So this will need the
			implementation of database inmemory */
//			pgdb_ClearTable(ANALOG_TABLE);
			InstallationPassSwitchOver = 0;
            InsStatus.Pass = (HsvInstallationPass)mCalculateInstallationPass();
            
            mInitInstallationPass(TRUE);
            break;
        case UPDATE_MODE:
			pgdb_SaveChannelMapsToBackup ();
            InsStatus.InstallationVersion++;
			InstallationPassSwitchOver = 0;
            InsStatus.Pass = (HsvInstallationPass)mCalculateInstallationPass();

            mInitInstallationPass(TRUE);
            break;
        case ANALOG_MANUAL_MODE:
            InsStatus.Pass = (HsvInstallationPass)SCAN_ANALOG;

            mInitInstallationPass(FALSE);
            break;
        case MANUAL_MODE:
            InsStatus.InstallationVersion++;
            InsStatus.Pass = (HsvInstallationPass)mCalculateInstallationPass();

            mInitInstallationPass(FALSE);
            break;
        case PRESCAN_MODE:
			pgdb_SaveChannelMapsToBackup ();
		//	pgdb_ClearTable(pgdb_GetCurrentTable());
            InsStatus.Pass = (HsvInstallationPass)SCAN_DVBC;
			InstallationPassSwitchOver = 0;

            mInitInstallationPass(TRUE);
            break;
		case CAM_MODE:
			pgdb_SaveChannelMapsToBackup ();
			pgdb_ClearTable(pgdb_GetCurrentTable());
			InsStatus.Pass = (ANTENNA_MEDIUM)?((HsvInstallationPass)SCAN_DVBT): ((HsvInstallationPass)SCAN_DVBC);
            mInitInstallationPass(TRUE);
		        eurdiv_setForceCharacterTable(TRUE);
			break;
        default:

            break;
    }   
	if((InsStatus.Mode == UPDATE_MODE)||(InsStatus.Mode == BACKGROUND_MODE)||(InsStatus.Mode == MANUAL_MODE))
	{
		pgdb_MasterEnableEvents(TRUE);
	}
}

inline void CHsvEuropeInstallation_m_Priv::FuncSourceSetupApplied(Nat32 param)
{
	int medium = 0, mode = 0, token = 0;/* token is always ROOT(0) */
	//String8	*dummy = new String8();
	String8 dummy;
	
    dummy = String8("");
    UNUSED(param);
	if (InsStatus.Pass != SCAN_NONE)
	{
		DetermineMedium(&medium, InsStatus.Pass);
		switch(medium)
		{
			case srcstp_Analog:
				mode = 1;
				break;
			case srcstp_DVBC:
				mode = 8;
				break;
			case srcstp_DVBT:
				mode = 6;
				break;
			default:
				break;
		}
		if (mode != 0)
		{
			//memset (&dummy, 0x00, sizeof(dummy));
			plfproxy_setDataSource(token,dummy,mode);
		}
	}
	
    switch (InsStatus.Mode)
    {
        case ANALOG_MANUAL_MODE:
			pgdb_SetDatabaseOperationMode(pgdb_DatabaseModeNormal);
            SET_INS_STATE(StAnalog);


			if(!InsStatus.vbi_enabled)
			{
				plfvbi_Enable();
				InsStatus.vbi_enabled = TRUE;
			}

            hsvprins_prins_StartManualInstallation();
            break;
        case AUTO_MODE:
        case UPDATE_MODE:
			pgdb_SetDatabaseOperationMode (pgdb_DatabaseModeNormal);
            if(DIGITAL_PASS)
            {
                mStartDigitalInstall();
            }
            else
            {
                if (InsStatus.Pass == SCAN_NONE) 
                {
                    /* brg36mgr=139681: For sweden, when analog channels are disabled, and skip is done during
                     * DVB-C installation, the code in else is executed and set goes to fake installation. 
                     * so in this case forcefully doing the installation completed procedure. */

                    /* All Scans complete */
					insN_OnEvent(insN_EventChannelIterationStarted, InsStatus.Mode);
                    SET_INS_STATE(StSorting);
                    pmp_PmpSend(mPump, EvSorting, (Nat32)NULL);
                }
                else 
                {
                    SET_INS_STATE(StAnalog);
					/* Enable VBI here */

					if(!InsStatus.vbi_enabled)
					{
						plfvbi_Enable();
						InsStatus.vbi_enabled = TRUE;
					}
					//dcu_Enable ();
                    hsvprins_prins_StartAutomaticInstallation();
                    insN_OnEvent(insN_EventPhaseStarted, pins_InstallationInPassAnalog); 
                }
            }
            break;
        case MANUAL_MODE:
        case PRESCAN_MODE:

			pgdb_SetDatabaseOperationMode (pgdb_DatabaseModeNormal);
            mStartDigitalInstall();
            break;
		case CAM_MODE:

			hsvdvbcins_ena_Disable();
			hsvdvbtins_ena_Disable();
			hsvziggoins_ena_Disable();
			hsvcanaldigitalins_ena_Disable();
			hsvdvbtmpegins_ena_Disable();
			SET_INS_STATE(StDigital);
			pgdb_SetDatabaseOperationMode (pgdb_DatabaseModeCam);
			hsvdvbcamins_ins_StartInstallation(HsvMain, 0, InsStatus.Mode);
			insN_OnEvent(insN_EventPhaseStarted, pins_InstallationInDigitalPass); 
        default:
            break;
    }
}

inline void CHsvEuropeInstallation_m_Priv::FuncStopInstallation(Nat32 param)
{
    UNUSED(param);
    int NetworkOperator;
    Bool StopPending = FALSE;
    InsStatus.Stopped = TRUE;
    switch (InsStatus.State)
    {
        case StDigital:
			//pgdb_SelectActiveChannelDatabase(pgdb_SqliteDatabase);
			if(CAM_INSTALL)
			{
				if(hsvdvbcamins_ins_StopInstallation() != err_InstallationNotInProgress)
				{
					StopPending = TRUE;
				}
			}
			else
			{
            if(InsStatus.Pass == SCAN_DVBC)
            {
                NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

                if( ((InsStatus.Country == cids_CountryNetherlands) && 
                    ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)))   ||
                    (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) )
                {
                    if(hsvziggoins_ins_StopInstallation() != err_InstallationNotInProgress)
                    {
                        StopPending = TRUE;
                    }
                }else if(mIsCanalDigitalorYouSeeOperatorSupported())
                {
                    if(hsvcanaldigitalins_ins_StopInstallation() != err_InstallationNotInProgress)
                    {
                        StopPending = TRUE;
                    }
                }
                else
                {
                    if(hsvdvbcins_ins_StopInstallation() != err_InstallationNotInProgress)
                    {
                        StopPending = TRUE;
                    }
                }
            }
            else if(InsStatus.Pass == SCAN_MPEG_ONLY )
            {
                
                if(hsvdvbtmpegins_digscan_StopDigitalScan() != err_InstallationNotInProgress)
                {
                    StopPending = TRUE;
                }
            }
            else
            {

                if(hsvdvbtins_dvbt_StopInstallation() != err_InstallationNotInProgress)
                {
                    StopPending = TRUE;
					}
                }
            }
            break;
        case StAnalog:        
			//pgdb_SelectActiveChannelDatabase(pgdb_SqliteDatabase);           
            if(InsStatus.Mode == ANALOG_MANUAL_MODE)
            {

            	if(InsStatus.vbi_enabled)
				{
					plfvbi_Disable ();
					InsStatus.vbi_enabled = FALSE;
				}	
                hsvprins_prins_StopManualInstallation();
            }
            else
            {
                hsvprins_prins_StopAutomaticInstallation();
            }
            break;
        default:
            break;
    }
    if(StopPending == FALSE)
    {
        mInstallationDone();
    }
	/* In case of Stop Installation making the Mode to Normal. Because user can do a normal installation.
		Start CAM installation and stop it. There is no background installation done for CAM. So whenever any 
		other CAM based installation is needed, StartInstallation will be explicitly triggered, thereby putting 
		database Mode as CAM mode */
	pgdb_SetDatabaseOperationMode (pgdb_DatabaseModeNormal);

}

void CHsvEuropeInstallation_m_Priv::FuncMakeDecision(Nat32 param)
{
    UNUSED(param);
    int event = 0;
    Bool l_ret;
    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            InsStatus.Pass = (HsvInstallationPass)mCalculateInstallationPass();
            if(InsStatus.Pass == SCAN_NONE)
            {
                /* All Scans complete */
                insN_OnEvent(insN_EventPhaseCompleted,  pins_InstallationInPassAnalog);

                event = mWaitForUserSelection();
                if(event)
                {
                    TraceDebug(m,"%s %d Display UI content requiring user intervention", __FUNCTION__, __LINE__);
                    SET_INS_STATE(StPreSorting);
                    insN_OnEvent(event, pins_InstallationInDigitalPass);
                }
                else
                {   
                    insN_OnEvent(insN_EventChannelIterationStarted, InsStatus.Mode);
                    SET_INS_STATE(StSorting);
                    pmp_PmpSend(mPump, EvSorting, (Nat32)NULL);
                }
            }
            else
            {
				InstallationPassSwitchOver = 0;
                /* start new pass */
                mInitInstallationPass(TRUE);
            }
            break;
        case MANUAL_MODE:
            l_ret = mIsNextPassRequired();


            InsStatus.Pass = (HsvInstallationPass) ((l_ret)? mCalculateInstallationPass() : SCAN_NONE);

            if(InsStatus.Pass == SCAN_NONE)
            {
				insN_OnEvent(insN_EventChannelIterationStarted, InsStatus.Mode);
                SET_INS_STATE(StSorting);
                pmp_PmpSend(mPump, EvSorting, (Nat32)NULL);
            }
            else
            {
                mInitInstallationPass(FALSE);
            }
            break;
        case PRESCAN_MODE:
            mInstallationDone();
            break;
        default:
            break;
    }
}

inline void CHsvEuropeInstallation_m_Priv::FuncPreSorting(Nat32 param)
{
    if(param == USER_SELECTION_DONE)
    {

        if(InsStatus.Country == cids_CountryUK)
        {

		    idbookconf_AssignRegionAttributesForService ();
			hsvdvbtins_digacq_DeleteServices();
        }
		insN_OnEvent(insN_EventChannelIterationStarted, InsStatus.Mode);
        SET_INS_STATE(StSorting);
        pmp_PmpSend(mPump, EvSorting, (Nat32)NULL);
    }
    else
    {

        if(InsStatus.Country == cids_CountryNorway)
        {
            hsvdvbtins_digacq_SetFavouriteNetworkID(AUTO_MODE, rins_AttributeNetworkId, param);
        }
        else
        {
            hsvdvbtins_digacq_SetFavouriteRegion(AUTO_MODE, ((param & 0xFFFF0000) >> 16), (HsvEnmRegionType)(param & 0xFFFF));
        }   
    }
}

inline void CHsvEuropeInstallation_m_Priv::FuncSorting(Nat32 param)
{
    UNUSED(param);
    /* below statement originally required for cabsort(but now applied to all)
       to avoid watchdog in field scenarios of sorting >=500 services */
    rtk_TskBoostWatchdog(60);

	if(InsStatus.Mode == UPDATE_MODE)
    {
        isort_RemoveDigitalPresets();

    }
    if (CAM_INSTALL)
	{
		icamsort_Sort();
	}
	else
    {
        isort_SortAll();
    }
}

void CHsvEuropeInstallation_m_Priv::FuncSearchInProgress(Nat32 param)
{
	Nat32 Frequency = 0, errorcode;
	if(InsStatus.State != StIdle)
	{

	    feapi_GetFreq(WINDOWID, &Frequency, &errorcode);
	    ASSERT(TM_OK  ==  errorcode );

		CurrentFrequency = Frequency;
	    insN_OnEvent(insN_EventSearchInProgress, Frequency);
		pmp_PmpSendAfter(mPump, EvSearchInProgress, 0,4000);
	}
}

void CHsvEuropeInstallation_m_Priv::mStoreBarkerMuxData(void)
{

	/*Store Barker Mux Data*/
	int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

	if( (InsStatus.Country == cids_CountryNetherlands) && 
			((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)) )
	{
		hsvziggoins_dataacq_UpdateBarkerMuxInfo(mBarkerMuxONID,mBarkerMuxTSID);
	} else if(mIsCanalDigitalorYouSeeOperatorSupported())
    {
    		hsvcanaldigitalins_dataacq_UpdateBarkerMuxInfo(mBarkerMuxONID,mBarkerMuxTSID);
	}
	else
	{
		hsvdvbcins_digacq_UpdateBarkerMuxInfo(mBarkerMuxONID,mBarkerMuxTSID);
	}
	/* CR: TF515PHIALLMVL02-109. Norway Riks TV also support Barker Mux */
	if(DVBC_LIGHT_COUNTRY || (InsStatus.Country == cids_CountryNorway))
	{
		hsvdvbtins_digacq_UpdateBarkerMuxInfo(mBarkerMuxONID,mBarkerMuxTSID);
	}
	if(CAM_INSTALL)
	{

		hsvdvbcamins_dataacq_UpdateBarkerMuxInfo(mBarkerMuxONID,mBarkerMuxTSID);
	}
}

void CHsvEuropeInstallation_m_Priv::mPerformDatabaseSync (int FromDatabaseId, int ToDatabaseId)
{
	int DatabaseToBeSynced [MAX_DATABASE_SYNC] = {PTC_TABLE,SERVICE_TABLE, PRESET_TABLE,FREQMAP_TABLE, ANALOG_TABLE};
	int TotalNumberOfEntries =0, count = 0, Index = 0;
	HsvPgdatDigTSData		digTsData;
	HsvPgdatDigServiceData	digSrvData;
	HsvPgdatPresetData		presetData;
	HsvPgdatDigFreqMapData	freqMapData;
	HsvPgdatAnalogData		analogData;

	if(ToDatabaseId == pgdb_SqliteDatabase) {
		pgdb_SelectActiveChannelDatabase(pgdb_SqliteDatabase);
		pgdb_ClearTable(pgdb_GetCurrentTable());
		pgdb_SelectActiveChannelDatabase(pgdb_TempDatabase);
	
	}
	pgdb_BeginSqliteTransaction();
	
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[0]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,digTsData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[1]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,digSrvData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[2]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,presetData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[3]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,freqMapData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[4]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,analogData)

	pgdb_CommitSqliteTransaction();
}

void CHsvEuropeInstallation_m_Priv::FuncSortComplete(Nat32 param)
{
    UNUSED(param);
	int	curMedium, otherMedium = 0;
	if(VALID_BARKERMUX_FOUND == TRUE)
	{
		mStoreBarkerMuxData();
	}
	
	if (AUTO_INSTALL)
	{
		/* Perform the database sync here */

		mPerformDatabaseSync (pgdb_TempDatabase, pgdb_SqliteDatabase);
		pgdb_SelectActiveChannelDatabase(pgdb_TempDatabase);
	}
	
    pgdb_CommitTable(pgdb_GetCurrentTable());
	pgdb_SaveChannelMapsToBackup ();
    TraceDebug(m,"SORT COMPLETE"); 
    if(AUTO_INSTALL)
    {
        
    
		/* Deleting the other medium database (CR: AN-8610)*/
		curMedium = (InsStatus.Medium == rins_Cable) ? (pgdbconst_Cable) : (pgdbconst_Antenna);
		otherMedium = (InsStatus.Medium == rins_Cable) ? (pgdbconst_Antenna): (pgdbconst_Cable);
		pgdb_SelectTable(otherMedium);
//		pgdb_ClearTable (otherMedium);
		pgdb_CommitTable (otherMedium);
		pgdb_SaveChannelMapsToBackup ();
		pgdb_SelectTable(curMedium);
		
		/* Store everything in flash */

        int DigitalChannelsFound = pins_GetNumberOfDigitalChannelsFound();

        if( (DigitalChannelsFound == 0) && (InsStatus.SkipInstallation & rins_ScanDVBC) )
        {

            hsvdvbcins_dvbset_ClearPersistent();
        }
        else
        {
            if(InsStatus.Country == cids_CountryChina)
            {

                hsvdvbcins_dvbset_SetAttribute(AUTO_MODE, rins_AttributeCity, sysset_GetSystemCity());
            }

            if(sysset_GetPbsMode()) {
            	if(sysset_GetDvbcSetting()) {
            		TraceDebug(m,"CommitPreferred for DVB-C");
            		hsvdvbcins_dvbset_CopyTemporaryToPersistent();
            		hsvdvbcins_dvbset_CommitPreferred();
            	}

            	if(sysset_GetDvbtSetting()) {
            		TraceDebug(m,"CommitPreferred for DVB-T");
            		hsvdvbtins_dvbset_CopyTemporaryToPersistent();
            		hsvdvbtins_dvbset_CommitPreferred();
            	}
            }
            else
            {
            	if(CABLE_MEDIUM)
            	{
                

                    hsvdvbcins_dvbset_CopyTemporaryToPersistent();
                    hsvdvbcins_dvbset_CommitPreferred();
                
            	}
            	else
            	{

            		hsvdvbtins_dvbset_CopyTemporaryToPersistent();
            		hsvdvbtins_dvbset_CommitPreferred();
            	}
            }
        }
        

        pgctl_SetInstalledMedium(pgctl_GetSelectedMedium());
        apsysset_SetMedium(pgctl_GetSelectedMedium());
    }
	else if(CAM_INSTALL)
	{
	       int DigitalChannelsFound = pins_GetNumberOfDigitalChannelsFound();
        	if(DigitalChannelsFound == 0) 
        	{

            		hsvdvbcamins_dvbset_ClearPersistent();
		       eurdiv_setForceCharacterTable(FALSE);
        	}
		else
		{
		pgctl_SetInstalledMedium(pgctl_GetSelectedMedium());
        apsysset_SetMedium(pgctl_GetSelectedMedium());
			hsvdvbcamins_dvbset_CopyTemporaryToPersistent();
			hsvdvbcamins_dvbset_CommitPreferred();
		}
	}


    hsvdvbtins_digacq_ClearCache();
    sysctl_BlockDestinations(HsvMain, FALSE);
    mInstallationDone();
}

inline void CHsvEuropeInstallation_m_Priv::mInitInstallationValues(Nat32 param, Bool InstallStart)
{
    SET_INS_STATE(StIdle);
    InsStatus.Pass              = (HsvInstallationPass)SCAN_NONE;
    InsStatus.Medium            = pins_GetMedium();
    InsStatus.Country           = sysset_GetSystemCountry();
    InsStatus.Stopped           = FALSE;
    InsStatus.Frequency         = param;

    hsvprins_prins_Initialise();
    hsvdvbcins_ins_Initialise();
    hsvdvbtins_dvbt_Initialise();
    hsvdvbtmpegins_digscan_Initialise();
    hsvziggoins_dataacq_Initialise();
	hsvcanaldigitalins_dataacq_Initialise();
    if(InstallStart == TRUE)
    {
        isort_Initialise();
    }
    hsvdvbtins_ena_Disable();
    hsvdvbcins_ena_Disable();
    hsvdvbtmpegins_ena_Disable();
	hsvziggoins_ena_Disable();
	hsvcanaldigitalins_ena_Disable();
}

inline Bool CHsvEuropeInstallation_m_Priv::mValidInstallMode(int mode)
{
    FResult retval = TRUE;

    switch(mode)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
        case MANUAL_MODE:
        case PRESCAN_MODE:
        case ANALOG_MANUAL_MODE:
		case BACKGROUND_MODE:
		case CAM_MODE:
            break;
        default:
            retval = FALSE;
            break;
    }
    return retval;
}

inline void CHsvEuropeInstallation_m_Priv::mUnicodeCopy(Nat16* dest, Nat16* source)
{
	ASSERT(NULL != dest);
	ASSERT(NULL != source);

	while(*source != '\0')
	{
		*dest++ = *source++;
	}
	*dest = *source;
}


inline void CHsvEuropeInstallation_m_Priv::mInstallationDone(void)
{

    if(!MANUAL_INSTALL)
    {
        //mctl_Stop(HsvMain); /* Naresh: is this correct */
        sysctl_BlockDestinations(HsvMain, FALSE);
    }

    if( (InsStatus.Mode == AUTO_MODE) || (InsStatus.Mode == UPDATE_MODE) || (InsStatus.Mode == CAM_MODE))
    {
        pgdb_LoadTable(pgdb_GetCurrentTable());
        pgdb_EnableAutoCommit(TRUE);
		if(InsStatus.Mode == UPDATE_MODE)
		{
			pgdb_MasterEnableEvents(FALSE);
		}
		if (InsStatus.Stopped)
		{

			pgdb_LoadChannelMapsFromBackup();
		}
    }
	else if ((InsStatus.Mode == PRESCAN_MODE) && (InsStatus.Stopped))
	{

		pgdb_LoadChannelMapsFromBackup();	
	}

    insN_OnEvent( (InsStatus.Stopped)?insN_EventInstallationStopped: insN_EventInstallationCompleted,InsStatus.Mode); 
    hsvdvbtins_cntryinsN_OnEvent( (InsStatus.Stopped)?insN_EventInstallationStopped: insN_EventInstallationCompleted,InsStatus.Mode);

	if(!InsStatus.Stopped)
	{
		InsCompleted = TRUE;
		insN_OnEvent(insN_NetworkOperator,hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator));
	}
    SET_INS_STATE(StIdle);

    /* Init skipInstllation separately not in below function, as it would also be called during start installation
       which would reset the value of this quite early before this is used */
    InsStatus.SkipInstallation = SCAN_NONE;     
    mInitInstallationValues(InsStatus.Frequency, FALSE);
}

int CHsvEuropeInstallation_m_Priv::mWaitForUserSelection(void)
{
    int retval = 0;
    /* retval = TRUE => we have to wait for user selection 
       on the post Installation screens given to user, retval = FALSE - no need UI screens shown, hence no wait */

    if((InsStatus.Country == cids_CountryNorway) && (ANTENNA_MEDIUM))
    {   
        if(pins_GetNetworkIDList() > 0)
        {
            retval = insN_EventDisplayNetworkNames;
        }

    }
    else if(eurdiv_IsDbookCountry() == TRUE)
    {
        static HsvNetworkRegionsData RegionsData ;


        memset((Address)(&RegionsData), 0, sizeof(RegionsData));
        pins_GetRegionList(&RegionsData);
        if( (RegionsData.NoOfRegions > 0) && (AUTO_INSTALL) )
        {
            retval = insN_EventDisplayRegionNames;
        }
		/* If Region count is 0 in auto installation, then no need to handle the DeleteServices of UK-DVBT.
			During selection itself Best MUX will come into picture and only one service of same Duplet will be present.
			TODO: Do we have a case in which Target Region Name descriptor is absent but TRD is present. Less likely */
		/* TODO: Check Do we have to set invalid region selection to Settings or it will be handled from UI itself */
    }
	else if(eurdiv_IsApmeaChannelListCountry()==TRUE)
		{

			if(AUTO_INSTALL)//Show ChannelList UI only in case of AUTO installation and channellist >1
			{
			if(pins_GetNumberOfChannelListIds() > 1)
			  {
				  retval = insN_EventDisplayChannelListId;
			  }
			}
		}
	

    return retval;
}

inline void CHsvEuropeInstallation_m_Priv::mInitInstallationPass(Bool BlockDestionationFlag)
{
    Bool retval, Proceed = TRUE;
    int NetworkOperator;

    if(InsStatus.State == StIdle)
    {
        sysctl_BlockDestinations(HsvMain, BlockDestionationFlag);
		pginsN_OnEvent(insN_EventInstallationStarted,InsStatus.Mode);
        insN_OnEvent(insN_EventInstallationStarted,InsStatus.Mode);
		/* ANEESH: ADD_PRINS_EVENT */
        hsvdvbtins_cntryinsN_OnEvent(insN_EventInstallationStarted, InsStatus.Mode);
    }

    NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

    if( (InsStatus.Mode == MANUAL_MODE) && (((InsStatus.Country == cids_CountryNetherlands) && 
            ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)))            || 
            (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) )
       )
    {
        Proceed = FALSE;
    } else if((InsStatus.Mode == MANUAL_MODE) && mIsCanalDigitalorYouSeeOperatorSupported())
    {
        Proceed = FALSE;
    }

    SET_INS_STATE(StSourceSetupWait);
    if(Proceed)
    {
        retval = mSourceSetupAndApply(InsStatus.Pass);
        if ( (retval != srcstp_WaitForSourceSetupApplyNotify) && (retval != srcstp_Success) )
        {

            pmp_PmpSend(mPump, EvStop, InsStatus.Frequency);
        }
        else
        {

        }
    }
    else
    {

        pmp_PmpSend(mPump, EvSourceSetupApplied, (Nat32)NULL);
    }
}

void CHsvEuropeInstallation_m_Priv::mStartDigitalInstall(void)
{
    SET_INS_STATE(StDigital);


    if(InsStatus.Pass == SCAN_DVBT)
    {
        hsvdvbcins_ena_Disable();
        hsvdvbtins_ena_Enable();
        hsvziggoins_ena_Disable();
		hsvcanaldigitalins_ena_Disable();
        hsvdvbtins_dvbt_StartInstallation(HsvMain, InsStatus.Frequency, InsStatus.Mode);
    }
    else if(InsStatus.Pass == SCAN_MPEG_ONLY)
    {
        hsvdvbtmpegins_ena_Enable();
        hsvdvbtmpegins_digscan_StartInstallation(HsvMain, InsStatus.Frequency, InsStatus.Mode);
    }
    else
    {
        int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

		//TraceDebug(m,"%s %d NetworkOperator[%d]  Country[%d] ", __FUNCTION__, __LINE__, NetworkOperator, InsStatus.Country);
        if( ( (InsStatus.Country == cids_CountryNetherlands) && 
                ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)) ) || 
                (InsStatus.Country == cids_CountryBelgium &&  NetworkOperator == rins_Telenet)
          )
        {
        	//TraceDebug(m,"%s %d NetworkOperator[%d]  Country[%d] ", __FUNCTION__, __LINE__, NetworkOperator, InsStatus.Country);
            hsvziggoins_ins_StartInstallation(HsvMain, InsStatus.Frequency, InsStatus.Mode);
        } else if(mIsCanalDigitalorYouSeeOperatorSupported())
        {
			//TraceDebug(m,"%s %d NetworkOperator[%d]  Country[%d] ", __FUNCTION__, __LINE__, NetworkOperator, InsStatus.Country);
			// This Initialise need to check
			hsvcanaldigitalins_ins_Initialise();
			hsvcanaldigitalins_ins_StartInstallation(HsvMain, InsStatus.Frequency, InsStatus.Mode);
    	}
        else
        {
        	//TraceDebug(m,"%s %d NetworkOperator[%d]  Country[%d] ", __FUNCTION__, __LINE__, NetworkOperator, InsStatus.Country);
            hsvdvbcins_ena_Enable();
            hsvdvbcins_ins_StartInstallation(HsvMain, InsStatus.Frequency, InsStatus.Mode);
        }

    }
    insN_OnEvent(insN_EventPhaseStarted, pins_InstallationInDigitalPass); 
}


Bool CHsvEuropeInstallation_m_Priv::mIsDVBCSpecificAttribute(int attribute)  
{
	Bool retval = false;

	switch(attribute)
	{
	
		case rins_AttributeNetworkFreq:
		case rins_AttributeNetworkId:
		case rins_AttributeNetworkOperator:
			retval = true;
			break;
		default:retval = false;
			break;
	}

	//TraceNotice(m,"%s attrib %d retval %d",__FUNCTION__,attribute,retval);

	return retval;	
}



FResult CHsvEuropeInstallation_m_Priv::pins_StartInstallation(int source, int ptc, int mode)    
{
    FResult retval = err_Ok;
	int 	Medium = pins_GetMedium();

    TraceNotice(m,"%s %d source %d mode [[%d]] TURNED_ON %d", __FUNCTION__, __LINE__, source, mode, TURNED_ON);
    if(TURNED_ON && VALID_SOURCE(source) && mValidInstallMode(mode) )
    {
		if (mode == BACKGROUND_MODE)
		{
			hsvdvbtins_digacq_InitialiseTotalChannels();
			hsvdvbcins_digacq_InitialiseTotalChannels();
			hsvdvbtmpegins_digacq_InitialiseTotalChannels();
			hsvziggoins_dataacq_InitialiseTotalChannels();
			hsvcanaldigitalins_dataacq_InitialiseTotalChannels();
			hsvprins_prins_InitialiseTotalChannels ();
			hsvdvbcamins_dataacq_InitialiseTotalChannels();
			InsStatus.DigitalChannelsRemoved = 0;


			/* Stop Collection */
			/* ANEESH: Start collection here */
			InsStatus.Mode  = mode;
			//ctrl_StopCollection (HsvDmxMain);
			if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
			{
				ctrl_StopCollection (HsvDmxMain);
			}
			//TraceNotice (m, "BCKGROUND Installation Triggered. ");
			/*Acquire demux interface this is required if channel zap is done done from Analog <-> Digital*/
			//plfproxy_acquirePlfInstance(TVPLAYERSERVICE_IID_TSDEMUX);
			if (eurdiv_IsBackgroundInstallRequired(Medium))
			{
				ctrl_StartCollection (HsvDmxMain, ctrl_Normal);
			}
			
		}
		else
		{
			//TraceDebug(m,"%s %d source %d mode %d TURNED_ON %d", __FUNCTION__, __LINE__, source, mode, TURNED_ON);
			InsStatus.Mode  = mode;
			pmp_PmpSend(mPump, EvStart, (Nat32)ptc);
			pmp_PmpSendAfter(mPump, EvSearchInProgress, 0,4000);
		}
    }
    else
    {
        retval = err_InstallationCommandNotAllowed;
    }   
    return retval;
}

FResult CHsvEuropeInstallation_m_Priv::pins_StopInstallation(void)
{
    FResult retval = err_Ok;
    TraceDebug(m,"%s %d TURNED_ON %d", __FUNCTION__, __LINE__, TURNED_ON);

    if(TURNED_ON)
    {
        pmp_PmpSend(mPump, EvStop, (Nat32)NULL);
		//TraceNotice (m, " State %d Mode %d ", InsStatus.State, InsStatus.Mode);
		if ((InsStatus.State == StIdle) && (InsStatus.Mode == BACKGROUND_MODE))
		{
		//	TraceNotice (m, "Stopping background installation ");
			/* Disabling the background installation and reset all variables. Then stopping the filters */
			hsvdvbtins_ena_Disable();
			hsvdvbcins_ena_Disable();
			hsvdvbtmpegins_ena_Disable();
			hsvziggoins_ena_Disable();
			hsvcanaldigitalins_ena_Disable();

			if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
			{
				ctrl_StopCollection (HsvDmxMain);
			}
		}
    }
	pgdb_MasterEnableEvents(FALSE);
    return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetNumberOfDigitalChannelsRemoved()    
{
    int retval = 0;
    if(InsStatus.Mode == pins_InstallationModeUpdate)
    {
        retval = InsStatus.DigitalChannelsRemoved;
    }
    return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetInstallationStatus()                 
{  
    int retval = pins_InstallationStateIdle;
    switch(InsStatus.State)
    {
        case StSourceSetupWait:
        case StDigital:              
        case StAnalog:
        case StPreSorting:
        case StSorting:             
            retval = pins_InstallationStateInProgress;
            break;
        default:
            break;
    }
    return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetCurrentPass( void )
{   
    int retval = 1, pass = SCAN_NONE;

    if(GET_INS_STATE != StIdle)
    {
        do
        {
            pass = eurdiv_GetNextScan(InsStatus.Medium, InsStatus.Mode, pass);
            if(pass == (int)InsStatus.Pass)
            {
                break;
            }
            retval++;
        }while(pass != SCAN_NONE);
    }
    return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetNoOfPass (void)
{
    int retval = 0, pass = SCAN_NONE;
    do
    {
        pass = eurdiv_GetNextScan(InsStatus.Medium, InsStatus.Mode, pass);
		if(pass != SCAN_NONE)
		{
    		retval++;
		}
    }while(pass != SCAN_NONE);

    return retval;


}

int CHsvEuropeInstallation_m_Priv::pins_GetInstallationMode()                  
{   
    return InsStatus.Mode;
}

int CHsvEuropeInstallation_m_Priv::pins_GetInstallationVersion()
{   
    return InsStatus.InstallationVersion;
}

int CHsvEuropeInstallation_m_Priv::pins_GetInstallationState()
{   
    return InsStatus.State;
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsMediumSupported( int medium)               
{
    Bool retval = FALSE;
    switch(medium)
    {
        case pins_Terrestrial:
            retval = TRUE;
            break;
        case pins_Cable:
            if(eurdiv_IsDVBCSupported() || (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite))
            {
                retval = TRUE;
            }
            break;
        default:
            break;
    }
    return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetMedium()
{
    return pgctl_GetSelectedMedium();
}

void CHsvEuropeInstallation_m_Priv::pins_SetMedium( int medium)                       
{
    switch(medium)
    {
        case pins_Cable:
        case pins_Terrestrial:
            InsStatus.Medium = medium;
            pgdb_EnableAutoCommit(FALSE);
            pgctl_SetSelectedMedium(medium);
            pgdb_SelectTable(((InsStatus.Medium == rins_Cable) ? (pgdbconst_Cable) : (pgdbconst_Antenna)));
            pgdb_LoadTable(pgdb_GetCurrentTable());

            if(insN_iPresent())
            {
                insN_OnEvent(insN_EventMediumChanged, medium);
            }
            pgdb_EnableAutoCommit(TRUE);
            break;
        default:
            ASSERT(FALSE);
            break;
    }   
}

int CHsvEuropeInstallation_m_Priv::pins_GetInstalledMedium(void)
{
    return pgctl_GetInstalledMedium();
}

void CHsvEuropeInstallation_m_Priv::pins_SetInstalledMedium(int medium) 
{
    pins_SetMedium(medium);
    pgctl_SetInstalledMedium(medium);
    syssetx_SetSelectedMedium(medium);
    switch(medium)
    {
        case pins_Terrestrial:
            apsysset_SetMedium(apsysset_MediumTerrestrial);
            break;
        case  pins_Cable:
            apsysset_SetMedium(apsysset_MediumCable);
            break;
        default:
            break;
    }
}

HsvChannel CHsvEuropeInstallation_m_Priv::pins_GetInstalledWeakSignalChannel(void)
{
    HsvChannel retval;

    retval= isort_GetInstalledWeakSignalChannel();
    //TraceDebug(m,"%d Channel %lu", retval.Channel.OnePart);
    return retval;
}

FResult CHsvEuropeInstallation_m_Priv::pins_StoreWeakSignalInstallationChannel (void)
{
    FResult retval = 0;

    if(InsStatus.Pass == SCAN_DVBT)
    {
        retval = hsvdvbtins_dvbt_StoreWeakSignalInstallationChannel();
    }
    else if(InsStatus.Pass == SCAN_DVBC)
    {
        retval = hsvdvbcins_ins_StoreWeakSignalInstallationChannel();
    }
    else if(InsStatus.Pass == SCAN_MPEG_ONLY)
    {
        retval = hsvdvbtmpegins_digscan_StoreWeakSignalInstallationChannel();
    }

    return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetActiveMedium (void)
{
    int activeMedium = pgctl_GetSelectedMedium();
    int numDvbTChannels = 0;
	int numDvbCChannels = 0;
    
    if(sysset_GetPbsMode()) // [Hotel TV]
    {
        if (!CAM_INSTALL) // CAM Installation is not applicable for Hotel TV
        {
            // Get number of DVB-T channels installed
            if(eurdiv_GetDVBTMode() == SCAN_MPEG_ONLY)
    	    {
        	    numDvbTChannels = hsvdvbtmpegins_digacq_GetNumberOfDigitalChannelsFound();
        	}
        	else
        	{
            	numDvbTChannels = hsvdvbtins_digacq_GetNumberOfDigitalChannelsFound();
        	}
            
            // Get number of DVB-C channels installed
            int networkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

        	if (((InsStatus.Country == cids_CountryNetherlands) && 
                ((networkOperator == rins_Ziggo) || (networkOperator == rins_None))) || 
                (InsStatus.Country == cids_CountryBelgium && networkOperator == rins_Telenet))
        	{
            	numDvbCChannels = hsvziggoins_dataacq_GetNumberOfDigitalChannelsFound();
	        } 
            else if (mIsCanalDigitalorYouSeeOperatorSupported())
    	    {
				numDvbCChannels = hsvcanaldigitalins_dataacq_GetNumberOfDigitalChannelsFound();
        	}	
        	else
        	{
            	numDvbCChannels = hsvdvbcins_digacq_GetNumberOfDigitalChannelsFound();
	        }
        }
        else
        {
            TraceErr(m, "%s: Error : Invalid case for Hotel TV", __FUNCTION__, __LINE__);
        }

        // Find the active medium base on the DVB-T/DVB-C ON/OFF setting and the 
        // number of channels installed for each medium.
        //  
        //      1. DVB-T -> ON,     DVB-C -> OFF    => Active Medium DVB-T
        //      2. DVB-T -> OFF,    DVB-C -> ON     => Active Medium DVB-C
        //      3. DVB-T -> ON,     DVB-C -> ON    
        //              a.  numDvbCChannels > 0     => Active Medium DVB-C
        //              b.  numDvbCChannels = 0     => Active Medium DVB-T
        if (sysset_GetDvbtSetting() && sysset_GetDvbcSetting())
        {
            activeMedium = ((numDvbCChannels > 0) ? pins_Cable : pins_Terrestrial);
        }        
    }
    else
    {
        // Do nothing; Return selected medium
    }    
    return activeMedium;
}

int CHsvEuropeInstallation_m_Priv::pins_GetNumberOfDigitalChannelsFound(void)
{
    int retval = 0;
	int DvbTChCount = 0;
	int DvbCChCount = 0;

	if(sysset_GetPbsMode() == 1) // [HTV]
	{
		if(CAM_INSTALL)
		{
			retval = hsvdvbcamins_dataacq_GetNumberOfDigitalChannelsFound();
		}
    	else
		{
	    	if(eurdiv_GetDVBTMode() == SCAN_MPEG_ONLY)
    	    {
        	    retval = hsvdvbtmpegins_digacq_GetNumberOfDigitalChannelsFound();
        	}
        	else
        	{
            	retval = hsvdvbtins_digacq_GetNumberOfDigitalChannelsFound();
        	}

			DvbTChCount = retval;

    	    int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

        	if( ( (InsStatus.Country == cids_CountryNetherlands) && 
                ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)) ) || 
                (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet)
          		)
        	{
            	retval = hsvziggoins_dataacq_GetNumberOfDigitalChannelsFound();
	        } else if(mIsCanalDigitalorYouSeeOperatorSupported())
    	    {
				retval = hsvcanaldigitalins_dataacq_GetNumberOfDigitalChannelsFound();
        	}	
        	else
        	{
            	retval = hsvdvbcins_digacq_GetNumberOfDigitalChannelsFound();
	        }
				DvbCChCount = retval;
        	if(DVBC_LIGHT_COUNTRY)
        	{
            	retval += hsvdvbtins_digacq_GetNumberOfDigitalChannelsFound();
			}


			retval = DvbTChCount + DvbCChCount;
	    	TraceDebug(m,"%s %d DvbTChCount=%d DvbCChCount=%d",__FUNCTION__, __LINE__, DvbTChCount, DvbCChCount);
    	}
    	TraceDebug(m,"%s %d retval %d",__FUNCTION__, __LINE__, retval);
    	return retval;
	}

	
	if(CAM_INSTALL)
	{
		retval = hsvdvbcamins_dataacq_GetNumberOfDigitalChannelsFound();
	}
    else
	{
    if(ANTENNA_MEDIUM)
    {
        if(eurdiv_GetDVBTMode() == SCAN_MPEG_ONLY)
        {
            retval = hsvdvbtmpegins_digacq_GetNumberOfDigitalChannelsFound();
        }
        else
        {
            retval = hsvdvbtins_digacq_GetNumberOfDigitalChannelsFound();
        }
    }
    else
    {
        int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

        if( ( (InsStatus.Country == cids_CountryNetherlands) && 
                ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)) ) || 
                (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet)
          )
        {
            retval = hsvziggoins_dataacq_GetNumberOfDigitalChannelsFound();
        } else if(mIsCanalDigitalorYouSeeOperatorSupported())
        {
			retval = hsvcanaldigitalins_dataacq_GetNumberOfDigitalChannelsFound();
        }	
        else
        {
            retval = hsvdvbcins_digacq_GetNumberOfDigitalChannelsFound();
        }
        if(DVBC_LIGHT_COUNTRY)
        {
            retval += hsvdvbtins_digacq_GetNumberOfDigitalChannelsFound();
		}
	}
    }
    TraceDebug(m,"%s %d retval %d",__FUNCTION__, __LINE__, retval);
    return retval;
}

Bool CHsvEuropeInstallation_m_Priv::pins_AutoStoreManualInstallationValues()
{
    //TraceDebug(m,"%s %d",__FUNCTION__, __LINE__);
		pgdb_MasterEnableEvents(TRUE);
    isort_AutoStoreManualInstallationValues();

    return TRUE;
}

int CHsvEuropeInstallation_m_Priv::pins_GetNumberOfAnalogChannelsFound()
{
    int retval = isort_GetNumberOfAnalogChannelsFound();

    return retval;
}

Bool CHsvEuropeInstallation_m_Priv::pins_SetAttribute(int installationmode, int attribute, int value )
{
    Bool retval = TRUE;
    int NetworkOperator;

	if (attribute == pins_AttributeAnalogEnabled)
	{
		AnalogEnabledStatus = value;
	}
    if (pins_Terrestrial == pins_GetMedium())
    {
        retval = hsvdvbtins_dvbset_SetAttribute(installationmode, attribute, value);
    }
    else
    {
        retval = hsvdvbcins_ins_SetAttribute(installationmode, attribute, value);

        NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
        
        if( (InsStatus.Country == cids_CountryNetherlands) && ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)) &&
            (attribute == hsvdvbcins_ins_AttributeNetworkId))
        {
            hsvziggoins_ins_ZiggoNetworkDataSet(TRUE);
           // TraceNotice(m,"%s %d ZiggoNetworkDataSet called", __FUNCTION__, __LINE__);
        }
        else if ( (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) &&
            (attribute == hsvdvbcins_ins_AttributeNetworkId) )
        {
            hsvziggoins_ins_ZiggoNetworkDataSet(TRUE);
        }

        /* set both DVBT & DVBC attributes, as both scans are done in DVBC Light country */
        if ( DVBC_LIGHT_COUNTRY && (attribute == pins_AttributeScanMode) )
        {
            retval = hsvdvbtins_dvbset_SetAttribute(installationmode, attribute, value);
        }
    }

    return retval;
}           

void CHsvEuropeInstallation_m_Priv::hsvprins_prinsN_OnEvent(int eventid, int value)
{
    int evtid = -1, val = value;

    switch (eventid)
    {
        case hsvprins_prinsN_EventAutomaticInstallationCompleted:
			//TraceNotice (m, "VBI Disabling current VBI state %d",InsStatus.vbi_enabled);
			if(InsStatus.vbi_enabled)
			{
				plfvbi_Disable ();
				InsStatus.vbi_enabled = FALSE;
			}
			
			dcu_Disable ();
            pmp_PmpSend(mPump, EvMakeDecision, (Nat32)NULL);
            break;
            /* Analog Only Notifications */
        case hsvprins_prinsN_EventManualInstallationCniExtractionStarted:  
            evtid   =  insN_EventManualInstallationCniExtractionStarted;
            break;
        case hsvprins_prinsN_EventManualInstallationCniExtractionEnded:  
            evtid   =  insN_EventManualInstallationCniExtractionEnded;
            break;
        case hsvprins_prinsN_EventChannelFound:  
            evtid   =  insN_EventChannelFound;
            break;
        case hsvprins_prinsN_EventATSSortingStarted:  
            evtid   =  insN_EventATSSortingStarted;
            break;
        case hsvprins_prinsN_EventAciStoreStarted:  
            evtid   =  insN_EventAciStoreStarted;
            break;
        case hsvprins_prinsN_EventTvSystemChanged:  
            evtid   =  insN_EventTvSystemChanged;
            break;
        case hsvprins_prinsN_EventManualInstallationChannelNotFound:  
            evtid   =  insN_EventChannelNotFound;
            val     =  pins_InstallationModeManual;
            break;
        case hsvprins_prinsN_EventSearchInProgress:  
            evtid   =  insN_EventSearchInProgress;
            break;
        case hsvprins_prinsN_EventTuningStarted:  
            evtid   =  insN_EventTuningStarted;
            break;
        case hsvprins_prinsN_EventTuningStationFound:  
            evtid   =  insN_EventTuningStationFound;
            break;
        case hsvprins_prinsN_EventTuningStationNotFound:  
            evtid   =  insN_EventTuningStationNotFound;
            break;
        case hsvprins_prinsN_EventPhaseStarted:
            evtid   =   insN_EventPhaseStarted;
            val     =   pins_InstallationInPassAnalog;
            break;
        case hsvprins_prinsN_EventPhaseCompleted:            
            evtid   =   insN_EventPhaseCompleted;
            val     =   pins_InstallationInPassAnalog;
            break;
		case hsvprins_prinsN_EventMultiPackageFound:
			
			evtid 	=	insN_EventMultiPackageFound;
			val		=	0;
			break;
		case hsvprins_prinsN_EventMultiPackageToBeDisplayed:
			
			evtid 	=	insN_EventMultiPackageToBeDisplayed;
			val		=	0;
			break;
		case hsvprins_prinsN_EventMultiPackageRemoved:
			
			evtid 	=	insN_EventMultiPackageRemoved;
			val		=	0;
			break;
        default:
            break;
    }

    if(evtid != -1)
    {
		
		pginsN_OnEvent(evtid, val);
        insN_OnEvent(evtid, val);
    }
}

void CHsvEuropeInstallation_m_Priv::hsvprins_prinsN_OnManualInstallationStored( HsvChannel chan )
{
    SET_INS_STATE(StIdle);
	int chanvalue = chan.Channel.Digit; 
    if(insN_iPresent())
    {
        insN_OnEvent(insN_EventPresetStored, chanvalue);
    }
}

void CHsvEuropeInstallation_m_Priv::hsvprins_prinsN_OnBackgroundCniUpdated(Nat16 Cni,HsvChannel channel)
{

}

void CHsvEuropeInstallation_m_Priv::hsvdvbtins_insN_OnEvent(int eventid, int value)
{
   // TraceDebug(m,"%s %d eventid %d value %d", __FUNCTION__, __LINE__, eventid, value);
    switch(eventid)
    {
        case hsvdvbtins_insN_EventInstallationStopped:
            mInstallationDone();
            break;
        case hsvdvbtins_insN_EventInstallationCompleted:
            pmp_PmpSend(mPump, EvMakeDecision, (Nat32)value);
            break;
        case hsvdvbtins_insN_EventOnConflictsDetected:
            if(powctlx_GetPowerMode() != PscPowOn)
            {
                
                InsStatus.Stopped = TRUE;
                mInstallationDone();
            }
            insN_OnEvent(eventid, value);
            break;
        default:    
		/* ANEESH: ADD_PRINS_EVENT */
			pginsN_OnEvent(eventid, value);
            insN_OnEvent(eventid, value);
            break;
    }
}

void CHsvEuropeInstallation_m_Priv::hsvdvbcins_insN_OnEvent(int eventid, int value)
{
    //TraceDebug(m,"%s %d eventid %d value %d", __FUNCTION__, __LINE__, eventid, value);
    switch(eventid)
    {
        case hsvdvbcins_insN_EventInstallationStopped:
            mInstallationDone();
            break;
        case hsvdvbcins_insN_EventChannelNotFound: //for DVBC Lite as to do 2nd pass i.e., DVBT
            if(eurdiv_GetDVBCMode() != eurdiv_ScanDVBCLite)
            {
                insN_OnEvent(eventid, value);
                mInstallationDone();
            }
            else
            {
                pmp_PmpSend(mPump, EvMakeDecision, (Nat32)NULL);
            }
            break;
        case hsvdvbcins_insN_EventInstallationCompleted:
            pmp_PmpSend(mPump, EvMakeDecision, (Nat32)NULL);
            break;
        default:    
		/* ANEESH: ADD_PRINS_EVENT */
			pginsN_OnEvent(eventid, value);
            insN_OnEvent(eventid, value);
            break;
    }
}

void CHsvEuropeInstallation_m_Priv::hsvziggoins_insN_OnEvent(int eventid, int value)
{
    //TraceDebug(m,"%s %d eventid %d value %d", __FUNCTION__, __LINE__, eventid, value);
    switch(eventid)
    {
        case hsvziggoins_insN_EventInstallationStopped:
            mInstallationDone();
            break;
        case hsvziggoins_insN_EventChannelNotFound: //for DVBC Lite as to do 2nd pass i.e., DVBT
            insN_OnEvent(eventid, value);
            mInstallationDone();
            break;
        case hsvziggoins_insN_EventInstallationCompleted:
			if(value != BACKGROUND_MODE)
			{
            pmp_PmpSend(mPump, EvMakeDecision, (Nat32)NULL);
			}
			else
			{
				insN_OnEvent(eventid, value);
			}
            break;
        default:    
		/* ANEESH: ADD_PRINS_EVENT */
			pginsN_OnEvent(eventid, value);
            insN_OnEvent(eventid, value);
            break;
    }
}


void CHsvEuropeInstallation_m_Priv::hsvcanaldigitalins_insN_OnEvent(int eventid, int value)
{
    //TraceDebug(m,"%s %d eventid %d value %d", __FUNCTION__, __LINE__, eventid, value);
    switch(eventid)
    {
        case hsvcanaldigitalins_insN_EventInstallationStopped:
            mInstallationDone();
            break;
        case hsvcanaldigitalins_insN_EventChannelNotFound: //for DVBC Lite as to do 2nd pass i.e., DVBT
            insN_OnEvent(eventid, value);
            mInstallationDone();
            break;
        case hsvcanaldigitalins_insN_EventInstallationCompleted:
			if(value != BACKGROUND_MODE)
			{
            pmp_PmpSend(mPump, EvMakeDecision, (Nat32)NULL);
			}
			else
			{
				insN_OnEvent(eventid, value);
			}
            break;
        default:    
		/* ANEESH: ADD_PRINS_EVENT */
			pginsN_OnEvent(eventid, value);
            insN_OnEvent(eventid, value);
            break;
    }
}


void CHsvEuropeInstallation_m_Priv::hsvdvbtmpegins_insN_OnEvent(int eventid, int value)
{
	if((InsStatus.Mode == rins_InstallationModeBackground) && (eventid == hsvdvbtins_insN_EventInstallationCompleted))
	{		
		insN_OnEvent(eventid, value);	
	} else  {
		hsvdvbtins_insN_OnEvent(eventid, value);
	}
}

void CHsvEuropeInstallation_m_Priv::hsvdvbcamins_insN_OnEvent(int eventid, int value)
{
    //TraceNotice(m,"%s eventid %d value %d", __FUNCTION__, eventid, value);
    switch(eventid)
    {
        case hsvdvbcamins_insN_EventInstallationStopped:
		    //TraceNotice(m,"Notifying ins stopped ");
			//pgdb_LoadChannelMapsFromBackup();
			insN_OnEvent(insN_EventInstallationStopped,InsStatus.Mode);//			InsStatus.Stopped = TRUE;
			mInstallationDone();
			break;
        case hsvdvbcamins_insN_EventInstallationCompleted:
			{
				if((pins_GetNumberOfDigitalChannelsFound() == 0) && (value == OP_PROFILE_TYPE_1))
				{
					//TraceNotice(m,"Notifying Installation stopped because of 0 channels installed");
					//pgdb_LoadChannelMapsFromBackup();
					insN_OnEvent(insN_EventInstallationStopped,InsStatus.Mode);
					mInstallationDone();
					mCamProfile0Installation = TRUE;					
				}
				else if(value == OP_PROFILE_TYPE_1)
			{
			insN_OnEvent(insN_EventPhaseCompleted,  pins_InstallationInPassAnalog);
			insN_OnEvent(insN_EventChannelIterationStarted, InsStatus.Mode);
			SET_INS_STATE(StSorting);
					mCamProfile0Installation = FALSE;
			pmp_PmpSend(mPump, EvSorting, (Nat32)NULL);			
			}
			else
			{
				//TraceNotice (m, "CAM Profile 0 Installation, so notifying installation stopped");
					
				if (!InsStatus.Stopped)
				{					
					//pgdb_LoadChannelMapsFromBackup();
						mCamProfile0Installation = TRUE;
						insN_OnEvent(insN_EventInstallationStopped,InsStatus.Mode);
					}
					mInstallationDone();
				}
			}
			break;
        default:    
            insN_OnEvent(eventid, value);
            break;
    }
}
void CHsvEuropeInstallation_m_Priv::sortN_OnEvent(int eventid, int value)
{
    //TraceDebug(m,"%s %d eventid %d value %d", __FUNCTION__, __LINE__, eventid, value);
    if(InsStatus.Mode == rins_InstallationModeBackground)
    {
    	 int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
    	 if((((InsStatus.Country == cids_CountryNorway) || (InsStatus.Country == cids_CountrySweden)) && (NetworkOperator == rins_CanalDigital)) ||
        			((InsStatus.Country == cids_CountryDenmark) &&  (NetworkOperator == rins_YouSee)))
    	 {
			if(VALID_BARKERMUX_FOUND == TRUE)
			{
				mStoreBarkerMuxData();
			}
    	 	hsvcanaldigitalins_sortN_OnEvent(eventid, value);
    	 } else {
        hsvziggoins_sortN_OnEvent(eventid, value);
    	}
		
    }
    else
    {
        switch(eventid)
        {
            case sortN_EventNewPresetFound:
                insN_OnEvent(insN_EventChannelAdded,InsStatus.Mode);
                break;
            case sortN_EventChannelRemoved:
                InsStatus.DigitalChannelsRemoved++;
                insN_OnEvent(insN_EventChannelRemoved,InsStatus.Mode);
                break;
            case sortN_EventSortComplete:

                //TraceDebug(m,"SENDING EVENT SORT COMPLETE, %d InsStatus.State = %d StSorting = %d", __LINE__, InsStatus.State, StSorting);

                pmp_PmpSend(mPump, EvSortComplete, (Nat32)NULL);

                break;
            default:
                break;
        }
    }
}

int CHsvEuropeInstallation_m_Priv::mCalculateInstallationPass(void)
{
    int retval = SCAN_NONE;

    do
    {
        retval = eurdiv_GetNextScan(InsStatus.Medium, InsStatus.Mode, InsStatus.Pass);
        if(retval == SCAN_NONE)
        {
            break;
        }
        else
        {
            InsStatus.Pass = (HsvInstallationPass)retval;
        }
    }while(retval & (InsStatus.SkipInstallation));
    TraceDebug(m, "%s %d next scan = %d", __FUNCTION__, __LINE__, retval);

	if(sysset_GetPbsMode() == 1) // [HTV]
	{	
		switch(InsStatus.Pass) // HTV
		{
			case eurdiv_ScanDVBC:
				pins_SetMedium(rins_Cable);
				break;
			case eurdiv_ScanAnalog:
				if (sysset_GetDvbtSetting() && sysset_GetDvbcSetting())
					pins_SetMedium(rins_Terrestrial);
				break;
			case eurdiv_ScanDVBT:
				pins_SetMedium(rins_Terrestrial);
				break;
			default:
				break;
		}
	}
			
    return retval;    
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnSearchInProgress( tmFe_SearchState_t state )
{
	pmp_PmpSend(mPump, EvSearchInProgress, 0);
	UNUSED(state);
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnMeasReady(int ssm, Nat32 strength )
{
    hsvprins_feapiN_OnMeasReady( ssm, strength );
    hsvdvbtins_feapiN_OnMeasReady( ssm, strength );
    hsvziggoins_feapiN_OnMeasReady( ssm, strength );
	hsvcanaldigitalins_feapiN_OnMeasReady( ssm, strength );

    insN_OnEvent(insN_EventSignalStrengthChanged, ssm);
}

HsvConstellation CHsvEuropeInstallation_m_Priv::pins_GetConstellation(void)
{
    tmFe_Constellation_t PlfConst;
    Nat32 errorcode = TM_OK;

    feapi_GetActualConstellation(WINDOWID, feapi_ChanDecDvbT, &PlfConst, &errorcode);/* ANEESH:TODO Correct this */
    ASSERT(TM_OK  ==  errorcode);

    return (HsvConstellation)PlfConst; //ConvertFromPlatformConstellation(PlfConst);
}

Nat32 CHsvEuropeInstallation_m_Priv::pins_GetSymbolRate(void)
{
    Nat32 errorcode = TM_OK, retval = 0;

    feapi_GetSymbolRate(WINDOWID, &retval, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    return  retval;
}

FResult CHsvEuropeInstallation_m_Priv::pins_SkipInstallationScans(int ScanTypes)
{
    FResult retval = err_Ok;
    if((GET_INS_STATE == StIdle) || (InsStatus.Mode == rins_InstallationModeBackground))
    {
        if(DVBC_LIGHT_COUNTRY)
        {
            if(InsStatus.Mode != PRESCAN_MODE)
            {
                /* DVBCLight requirement is to scan from lowest frequency when the frequency pop-up is cancalled */
    
                hsvdvbcins_dvbset_SetAttributeMode(AUTO_MODE, rins_AttributeNetworkFreq, rins_AutomaticValue);
                hsvdvbcins_dvbset_SetAttribute(AUTO_MODE, rins_AttributeModulation, 0);
                hsvdvbcins_dvbset_SetAttribute(AUTO_MODE, rins_AttributeNetworkFreq, 0);
            }
        }
        else
        {
            InsStatus.SkipInstallation = ScanTypes;
        }
    }   
    return retval;  
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsNetworkUpdateDetected(void)
{
    Bool ret = FALSE;

    if(CABLE_MEDIUM)
    {
        int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

        if( !(((InsStatus.Country == cids_CountryNetherlands) && 
                    ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None))) 
                    || (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet)) ||
                    mIsCanalDigitalorYouSeeOperatorSupported())
        {
            ret = hsvdvbcins_ins_IsNetworkUpdateDetected();
        }
    }
    else
    {
        ret = hsvdvbtins_afitr_IsNetworkUpdateDetected();
    }
    
    return ret;
}

void CHsvEuropeInstallation_m_Priv::pins_SetFavouriteNetworkID(int mode, int attrib, int index)
{
    UNUSED(mode);
    UNUSED(attrib);
    pmp_PmpSend(mPump, EvPreSorting, (Nat32)index);
}

void CHsvEuropeInstallation_m_Priv::pins_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType)
{
    UNUSED(mode);
    pmp_PmpSend(mPump, EvPreSorting, (Nat32)(((index & 0xFFFF) << 16) | RegionType));
}

void CHsvEuropeInstallation_m_Priv::pins_UserSelectionDone(Bool UserSelection)
{
    UNUSED(UserSelection);
    
		/* ANEESH: Check this for UK CR */
//    idbookconf_AssignRegionAttributesForService ();
    pmp_PmpSend(mPump, EvPreSorting, (Nat32)USER_SELECTION_DONE);
}

Nat32 CHsvEuropeInstallation_m_Priv::pins_GetSignalQualityBer(void)
{
    Nat32 bervalue, errorcode;

    feapi_GetBer(WINDOWID, 0, &bervalue, &errorcode);  /* ANEESH: Correct this */
    ASSERT(TM_OK == errorcode);

    return bervalue;    
}

void CHsvEuropeInstallation_m_Priv::impow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE, "hsveuins_m_pmp" );

    mModuleLifeCycle = Initialised;
    InsStatus.Medium = pins_GetMedium();
	InsStatus.vbi_enabled = FALSE;
	//TraceNotice(m,"%s %d Installed Country = %d",__FUNCTION__,__LINE__,syssetx_GetInstallCountry());
	syssetx_SetSystemCountry(syssetx_GetInstallCountry());
    //TraceDebug(m,"%s %d InsStatus.Medium %d", __FUNCTION__, __LINE__, InsStatus.Medium);
}

void CHsvEuropeInstallation_m_Priv::impow_TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
    pgdb_EnableAutoCommit(TRUE);
    InsStatus.Mode = pins_InstallationModeNone;
	InsStatus.DigitalChannelsRemoved = 0;
    mInitInstallationValues(0, FALSE);
}

void CHsvEuropeInstallation_m_Priv::impow_TurnOff(void)
{
    mModuleLifeCycle = TurnedOff;
    FuncStopInstallation((Nat32)NULL);
    if(InsStatus.State != StSorting)
    {
        pgdb_CommitTable(pgdb_GetCurrentTable());
        instlaN_LastActivityPerformed();
      //  TraceDebug(m,"euins_m.c::instlaN_LastActivityPerformed in %d\r",__LINE__);
    }
}

void CHsvEuropeInstallation_m_Priv::ictrlN_OnEvent(HsvDemux dmx,int eventid,int value)  
{
    FResult retval = plferrids_Ok;
    Nat32 Decoder;
    UNUSED(dmx);
    UNUSED(value);
	Decoder = syssetx_GetInstalledMedium();

	/* ANEESH: TODO: Get the decoder here. Otherwise the background installation wont work */
    TraceDebug(m,"%s %d eventid %d Decoder %d ", __FUNCTION__, __LINE__, eventid, Decoder);
    if(TURNED_ON)
    {
        if(eventid == ictrlN_StartedCollection)
        {
            if(InsStatus.State == StIdle)
            {
                InsStatus.Mode = BACKGROUND_MODE;
                hsvdvbcins_ena_Disable();
                hsvdvbtins_ena_Disable();
                hsvdvbtmpegins_ena_Disable();
                hsvziggoins_ena_Disable();
				hsvcanaldigitalins_ena_Disable();
				pgdb_MasterEnableEvents(TRUE);
                if((Decoder == rins_Terrestrial) && (hsvdvbcamins_dvbset_IsAvailable(BACKGROUND_MODE,rins_AttributeNetworkOperator) == FALSE)) //Later this check should be replaced with sysset_getOperator(terrestrial) != CAM))
              
                {
					
                    sigstr_SetSigStrengthMeasured(TRUE);
                    if(eurdiv_GetDVBTMode() != SCAN_MPEG_ONLY)
                    {
						
                        hsvdvbtins_ena_Enable();
                    }
                    else
                    {
						
                        hsvdvbtmpegins_ena_Enable();
                    }
                }
                else if((rins_Cable == Decoder) && (hsvdvbcamins_dvbset_IsAvailable(BACKGROUND_MODE,rins_AttributeNetworkOperator) == FALSE)) //Later this check should be replaced with sysset_getOperator(terrestrial) != CAM)))
                {
                    int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
					InsStatus.Country = sysset_GetSystemCountry();
                    //TraceNotice(m,"%s %d eventid %d InsStatus.Country %d NetworkOperator %d", __FUNCTION__, __LINE__, eventid, InsStatus.Country, NetworkOperator);
                    if ( ( (InsStatus.Country == cids_CountryNetherlands)   && 
                            ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None)))   ||
                            (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) )
                    {
                        hsvziggoins_ena_Enable();
                    } else if(mIsCanalDigitalorYouSeeOperatorSupported()) 
                    {
						hsvcanaldigitalins_ena_Enable();
					}
                    else
                    {
                        hsvdvbcins_ena_Enable();
                    }
                }
                else
                {
                    //TraceDebug(m,"feapi_GetChanDec() returns Decoder Type %d",(int)Decoder);
                }
            }
        }
    }
}


inline Bool CHsvEuropeInstallation_m_Priv::mIsNextPassRequired(void)
{
    Bool retval = TRUE;
    if ( ( eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite ) && ( hsvdvbcins_ins_GetNumberOfDigitalChannelsFound() > 0 ) ) 
    {
        retval = FALSE;
    }

    return retval;
}

HsvConstellation CHsvEuropeInstallation_m_Priv::ConvertFromPlatformConstellation(tmFe_Constellation_t inval)
{
    HsvConstellation outval = (HsvConstellation)0;
    switch(inval)
    {
#define HSVCONSTELLATION(a)  case (tmFe_##a): \
        outval  =   Hsv##a;                   \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif
        default:
            break;
    }
    return outval;
}

Bool CHsvEuropeInstallation_m_Priv::pins_GetAltTSValues(Nat16* ONID, Nat16* TSID)
{
    Bool retval = FALSE;
    int NetworkOperator; 
	int medium = pgctl_GetSelectedMedium();

	if(medium == pins_Cable) {
		NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	    if ( ( (InsStatus.Country == cids_CountryNetherlands) && 
	        ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None))) || 
	        (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) )

	    {
	        retval = hsvziggoins_ins_GetAltTSValues(ONID, TSID );
	    } else if(mIsCanalDigitalorYouSeeOperatorSupported())
	    {
			retval = hsvcanaldigitalins_ins_GetAltTSValues(ONID, TSID );
	    }
	    else
	    {
	        retval = hsvdvbcins_ins_GetAltTSValues(ONID, TSID );
	    }
	}
    return retval;
}

void CHsvEuropeInstallation_m_Priv::pins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
    int NetworkOperator; 
	int medium = pgctl_GetSelectedMedium();

	if(medium == pins_Cable) {
		NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	    if ( ( (InsStatus.Country == cids_CountryNetherlands) && 
	        ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None))) || 
	        (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) )

	    {
	        //retval = hsvziggoins_ins_GetSIDetails(sivalues);
	    }
	    else
	    {
	        hsvdvbcins_ins_GetSIDetails(sivalues);
	    }
	}
    return;
}


void CHsvEuropeInstallation_m_Priv::pins_GetEpgBarkerMux(Nat16* ONID, Nat16* TSID)
{
    /* presently only ziggo supports this */
    hsvziggoins_ins_GetEpgBarkerMux(ONID, TSID);
}

Bool CHsvEuropeInstallation_m_Priv::pins_ZiggoNetworkDataSet(Bool ActionValue)
{
    return hsvziggoins_ins_ZiggoNetworkDataSet(ActionValue);
}

int CHsvEuropeInstallation_m_Priv::pins_GetTargetNitType(Nat16* NetworkId)
{
    int retval, NetworkOperator;

    NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);

    if ( ( (InsStatus.Country == cids_CountryNetherlands) && 
        ((NetworkOperator == rins_Ziggo) || (NetworkOperator == rins_None))) || (InsStatus.Country == cids_CountryBelgium && NetworkOperator == rins_Telenet) )
            
    {
        
        retval = hsvziggoins_ins_GetTargetNitType(NetworkId);
    } else if(mIsCanalDigitalorYouSeeOperatorSupported())
    {
		
        retval = hsvcanaldigitalins_ins_GetTargetNitType(NetworkId);
    }
    else
    {
        
        retval = hsvdvbcins_ins_GetTargetNitType(NetworkId);
    }

    return retval;
}
void CHsvEuropeInstallation_m_Priv::instla_PerformLastActivity( void)
{
    impow_TurnOff();
   // TraceDebug(m,"euins_m.c::instla_PerformLastActivity in %d\r",__LINE__);
}

void CHsvEuropeInstallation_m_Priv::pins_ClearPersistent( )
{
    hsvdvbcins_ins_ClearPersistent();
    hsvdvbtins_dvbset_ClearPersistent();
    hsvdvbcamins_dvbset_ClearPersistent();
    eurdiv_setForceCharacterTable(FALSE);
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsUpdateInstallationSupported( void )
{
#define INVALID_NID 0
    Bool retVal = TRUE;
    int nEntries,iter;
    HsvPgdatDigTSData tsdat;

    /* In DVBC Quickscan mode, IsUpdateInstallationSupported() returns FALSE under
       a) NID Value is INVALID or
       b) Number of TS Installed is 0 or
       c) All TS Installed are Manually Installed */

    if( CABLE_MEDIUM )
    {   
        if(rins_QuickScan == rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode) )
        {
			nEntries = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_DigitalTS );
            if( (INVALID_NID == rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkId)) && (nEntries == 0) )
            {
                retVal = FALSE;
            }
            else
            {
                if( nEntries == 0 ) 
                {
                    
                    retVal = FALSE; 
                }
                else if( nEntries > 0 )
                {
                    retVal = FALSE;

                    for(iter=0;iter<nEntries;iter++)
                    {
                        if ( pgdb_GetByIndex( (pgdb_GetCurrentTable() | pgdbconst_DigitalTS), iter, (Address )&tsdat ) )
                        {
                            if(tsdat.UserInstalled == FALSE)
                            {
                                retVal = TRUE;
                                break;
                            }           
                        }   
                    }
                }

            }   
        }
    }
    //TraceDebug(m,"hveuins: CR114958 IsUpdateInstallationSupported returned %d",retVal);
    return retVal;
}

void CHsvEuropeInstallation_m_Priv::pins_SetStreamPriority (HsvStreamPriority prio)
{
	
	hsvdvbtins_dvbt_SetStreamPriority(prio);
}

Bool CHsvEuropeInstallation_m_Priv::mUpdateBarkerInfo(HsvDestination dest, int spid)
{
	
	
	if( (HsvMain == dest) && (spid == HSVSPID(LinkageInfo, dvb, nit) || spid == HSVSPID(OtherLinkageInfo, dvb, nit) || spid == HSVSPID(CamNITLinkageInfo, dvb, camnit)) )
	{
		if (GET_INS_STATE != StIdle)
		{
			Nat16 lNetworkId = 0 ,ActualNetworkID;
            HsvNITLinkageInfo lLinkageInfo;
            int lNitType = pins_NitNone, ScanMode = 0;

            if(pins_GetMedium() == pins_Cable)
            {
                ScanMode = pins_GetAttribute(pins_InstallationModeAutomatic, pins_AttributeScanMode);
                if(ScanMode == pins_QuickScan)
                {
                    lNetworkId = pins_GetAttribute(pins_InstallationModeAutomatic, pins_AttributeNetworkId); 
                }
                else if(ScanMode == pins_FullScan)
                {
                    switch(sysset_GetSystemCountry())
                    {
                        case cids_CountrySweden:
                        case cids_CountryNorway:
                        case cids_CountryDenmark:
                            strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &lNetworkId);
                            break;
                    }
                }

                if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &ActualNetworkID))
                {
                    if((lNetworkId == ActualNetworkID ) && (HSVSPID(LinkageInfo, dvb, nit) == spid) )
                    {
                        spid = HSVSPID(LinkageInfo, dvb, nit);
                    }
                    else if(HSVSPID(OtherLinkageInfo, dvb, nit) == spid)
                    {
                        if(ScanMode != pins_FullScan)
                        {
                            spid = HSVSPID(OtherLinkageInfo, dvb, nit); 
                        }
                    }
                }
            }
			else if (pins_GetMedium() == pins_Terrestrial)
			{
				/* CR: TF515PHIALLMVL02-109. Norway Riks TV also support Barker Mux */
				if (sysset_GetSystemCountry() == cids_CountryNorway)
				{
					strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &lNetworkId);
					spid = HSVSPID(LinkageInfo, dvb, nit);
				}
			}
            
            if(spid != -1)
            {
                int index;
                int lNitSize = strapi_GetSize(HsvMain, spid) ;
                //TraceNotice(m,"CEAPPS : EPG NITSIZE = %d", lNitSize);
                for(index = 0; index < lNitSize; index++)
                {
                    strapi_GetByIndex(HsvMain, spid, index, &lLinkageInfo);
			TraceNotice (m, "LinkageNetworkID %d lNetworkID %d LinageType %d ", lLinkageInfo.NetworkId, lNetworkId, lLinkageInfo.LinkageType);
                    if( (lLinkageInfo.NetworkId == lNetworkId) && (TS_Containing_Complete_Network_Bouquet_SI == lLinkageInfo.LinkageType) )
                    {
                       // TraceNotice(m,"CEAPPS : EPG NIT PASSED INDEX = %d", index);
                        if(VALID_BARKERMUX_FOUND == FALSE)
                        {
                        	mBarkerMuxONID= lLinkageInfo.Original_NetworkId;
							mBarkerMuxTSID= lLinkageInfo.Tsid;
							break;
                        }
					}
					else
                    {
                        //TraceNotice(m,"CEAPPS : EPG NIT FAILED INDEX = %d", index);
                    }
				}
			}
            if((CAM_INSTALL) && (spid != -1))
            {
            	//TraceDebug(m,"Cam install barker mux");
                int index;
                int lNitSize = strapi_GetSize(HsvMain, spid) ;
               // TraceNotice(m,"CEAPPS : EPG NITSIZE = %d", lNitSize);
                for(index = 0; index < lNitSize; index++)
                {
                    strapi_GetByIndex(HsvMain, spid, index, &lLinkageInfo);
                    if((EPG_Service == lLinkageInfo.LinkageType) )
                    {
                        //TraceNotice(m,"CEAPPS : EPG NIT PASSED INDEX = %d", index);
                        if(VALID_BARKERMUX_FOUND == FALSE)
                        {
                        	mBarkerMuxONID= lLinkageInfo.Original_NetworkId;
							mBarkerMuxTSID= lLinkageInfo.Tsid;
							break;
                        }
					}
					else
                    {
                        //TraceNotice(m,"CEAPPS : EPG NIT FAILED INDEX = %d", index);
                    }
				}
			}

		}
        else if (InsStatus.Mode == BACKGROUND_MODE)  /* For Canal Digital background Barker Mux update is needed */
		{
			Nat16 lNetworkId = 0 ,ActualNetworkID;
            HsvNITLinkageInfo lLinkageInfo;

			if ((syssetx_GetInstalledMedium() == rins_Cable) && \ 
				(hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator) == rins_CanalDigital) && \ 
				(rins_QuickScan == hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeScanMode)) && \ 
				((InsStatus.Country == cids_CountryNorway) || (InsStatus.Country == cids_CountrySweden)))
			{
				lNetworkId = pins_GetAttribute(pins_InstallationModeAutomatic, pins_AttributeNetworkId); 
				/* Canal Digital in NIT Actual based. So no need to check for NIT Other here */
				if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &ActualNetworkID))
                {
                    if((lNetworkId == ActualNetworkID ) && (HSVSPID(LinkageInfo, dvb, nit) == spid) )
                    {
                        spid = HSVSPID(LinkageInfo, dvb, nit);
                    }
				}
				if(spid != -1)
				{
					int index;
					int lNitSize = strapi_GetSize(HsvMain, spid) ;
					TraceNotice(m,"CanalDigital Background : EPG NITSIZE = %d", lNitSize);
					for(index = 0; index < lNitSize; index++)
					{
						strapi_GetByIndex(HsvMain, spid, index, &lLinkageInfo);
						TraceNotice (m, "LinkageNetworkID %d lNetworkID %d LinageType %d ", lLinkageInfo.NetworkId, lNetworkId, lLinkageInfo.LinkageType);
						if( (lLinkageInfo.NetworkId == lNetworkId) && (TS_Containing_Complete_Network_Bouquet_SI == lLinkageInfo.LinkageType) )
						{
							TraceNotice(m,"CanalDigital Background : EPG NIT PASSED INDEX = %d", index);
							if(VALID_BARKERMUX_FOUND == FALSE)
							{
								mBarkerMuxONID= lLinkageInfo.Original_NetworkId;
								mBarkerMuxTSID= lLinkageInfo.Tsid;
								break;
							}
						}
						else
						{
							TraceNotice(m,"CanalDigital Background : EPG NIT FAILED INDEX = %d", index);
						}
					}
				}
			}
		}
	}

	return TRUE;
}

void CHsvEuropeInstallation_m_Priv::strapiN_OnCompleted( HsvDestination dest, int spid)
{
	hsvziggoins_strapiN_OnCompleted( dest, spid);
	hsvcanaldigitalins_strapiN_OnCompleted( dest, spid);
	tstrapiN_OnCompleted( dest, spid);
	cstrapiN_OnCompleted( dest, spid);
	mpegstrapiN_OnCompleted( dest, spid);
	hsvdvbcamins_strapiN_OnCompleted(dest,spid);
	/* ANEESH: For reference. */
	mUpdateBarkerInfo (dest,spid);
	
}
void CHsvEuropeInstallation_m_Priv::strapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	hsvziggoins_strapiN_OnAdded( dest, spid, key1, key2, key3);
	hsvcanaldigitalins_strapiN_OnAdded( dest, spid, key1, key2, key3);
	tstrapiN_OnAdded( dest, spid, key1, key2, key3);
	cstrapiN_OnAdded( dest, spid, key1, key2, key3);
	mpegstrapiN_OnAdded( dest, spid, key1, key2, key3);
	hsvdvbcamins_strapiN_OnAdded( dest, spid, key1, key2, key3);
	
    if( (TurnedOn) && (InsStatus.Pass == SCAN_DVBC) && (rins_FullScan == rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode)) )
    {
        if(spid == (HSVSPID(NetworkName, dvb, nit)))
        {
			if(!(strapi_GetByKey(HsvMain, HSVSPID(NetworkName, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, (void *)(FullScanNetworkName))) )
			{
				TraceErr(m,"%s: Error in getting Network name", __FUNCTION__);
			}
    	}
    }
}
void CHsvEuropeInstallation_m_Priv::strapiN_OnChanged( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
	hsvziggoins_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
	hsvcanaldigitalins_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    tstrapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    cstrapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    mpegstrapiN_OnAdded( dest, spid, key1, key2, key3);
    hsvdvbcamins_strapiN_OnAdded( dest, spid, key1, key2, key3);
	
    if( (TurnedOn) && (InsStatus.Pass == SCAN_DVBC) && (rins_FullScan == rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode)) )
    {
        if(spid == (HSVSPID(NetworkName, dvb, nit)))
        {
			if(!(strapi_GetByKey(HsvMain, HSVSPID(NetworkName, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, (void *)(FullScanNetworkName))) )
			{
				TraceErr(m,"%s: Error in getting Network name", __FUNCTION__);
			}
        }
    }
	if (InsStatus.Mode == BACKGROUND_MODE)
	{
		/* Only needed for Canal Digital */
		mUpdateBarkerInfo (dest,spid);
	}
}
void CHsvEuropeInstallation_m_Priv::strapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	hsvziggoins_strapiN_OnRemoved( dest, spid, key1, key2, key3);
	hsvcanaldigitalins_strapiN_OnRemoved( dest, spid, key1, key2, key3);
	tstrapiN_OnRemoved( dest, spid, key1, key2, key3);
	cstrapiN_OnRemoved( dest, spid, key1, key2, key3);
	mpegstrapiN_OnRemoved( dest, spid, key1, key2, key3);
	hsvdvbcamins_strapiN_OnRemoved( dest, spid, key1, key2, key3);
}




void CHsvEuropeInstallation_m_Priv::isyssetN_OnCountryChanged(int cntry)
{
	hsvdvbcins_syssetN_OnCountryChanged(cntry);
   	hsvdvbtins_syssetN_OnCountryChanged(cntry);
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnMediumChanged(int medium)
{
	hsvdvbcins_syssetN_OnMediumChanged(medium),
    hsvdvbtins_syssetN_OnMediumChanged(medium); 
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnCityChanged(int city)
{
	hsvdvbcins_syssetN_OnCityChanged(city);
}

void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredSecondaryTxtLanguageChanged(int value)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredPrimaryTxtLanguageChanged(int value)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredSecondarySubtitleLanguageChanged(int value)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredPrimarySubtitleLanguageChanged(int value)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredSecondaryAudioLanguageChanged(int value)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredPrimaryAudioLanguageChanged(int value)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnPreferredAudioFormatChanged(int format)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnHearingImpairedTypeChanged(int lang)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnInstalledCountryChanged(int country)
{
	return;	
}
void CHsvEuropeInstallation_m_Priv::isyssetN_OnLanguageChanged(int lang)
{
	if(eurdiv_MultiLingSupported())
	{
   		hsvdvbtins_bcksyssetN_OnLanguageChanged(lang);
	}
}



/*Within */



int CHsvEuropeInstallation_m_Priv::pins_GetMinFrequency( )
{
	return freqctl_GetMinFrequency( );
}
int CHsvEuropeInstallation_m_Priv::pins_GetMaxFrequency( )                                 
{   
	return freqctl_GetMaxFrequency( );
}
int CHsvEuropeInstallation_m_Priv::pins_GetTunerFrequency( )                               
{   
	return freqctl_GetTunerFrequency();
}
void CHsvEuropeInstallation_m_Priv::pins_SetTunerFrequency( int freq, Bool fineTune )                
{   
	return freqctl_SetTunerFrequency( freq, fineTune );
}
int CHsvEuropeInstallation_m_Priv::pins_GetFrequency2Channel( int chantbl, int frequency )         
{   
	return freqctl_GetFrequency2Channel( chantbl, frequency );
}
int CHsvEuropeInstallation_m_Priv::pins_GetChannel2CarrierFrequency ( int chantbl,  int channel )  
{   
	return freqctl_GetChannel2CarrierFrequency ( chantbl,  channel );
}
int CHsvEuropeInstallation_m_Priv::pins_GetChannel2CentreFrequency ( int chantbl,  int channel )   
{   
	return freqctl_GetChannel2CentreFrequency ( chantbl,  channel );
}

/* Weak Signal Installation Functions */
       
Nat32 CHsvEuropeInstallation_m_Priv::pins_GetSignalstrength(int mode)                
{   
	return sigstr_GetSignalStrength(mode); 
}

FResult CHsvEuropeInstallation_m_Priv::pins_GetSigStrengthRange(int mode,Nat32* min,Nat32* max)
{   
	return sigstr_GetSigStrengthRange(mode, min, max);
}

       

Nat16 CHsvEuropeInstallation_m_Priv::pins_GetCurrentPassType()                       
{
	return 0;
}
void CHsvEuropeInstallation_m_Priv::pins_GetUserSymbolRates(int mode, int *values, int *len )       
{ 
	hsvdvbcins_ins_GetUserSymbolRates(mode, values, len);
}
void CHsvEuropeInstallation_m_Priv::pins_SetUserSymbolRates(int mode, int *values, int len )       
{ 
	hsvdvbcins_ins_SetUserSymbolRates(mode, values, len);
}
void CHsvEuropeInstallation_m_Priv::pins_GetPredefinedSymbolRates(int mode, int *values, int *len )       
{
		hsvdvbcins_ins_GetPredefinedSymbolRates(mode, values, len);
}

void CHsvEuropeInstallation_m_Priv::pins_ResetAttributeToPersistent( int mode, int attrib )
{
	(pins_GetMedium() == pins_Terrestrial) ?hsvdvbtins_dvbset_ResetAttributeToPersistent( mode, attrib ):hsvdvbcins_ins_ResetAttributeToPersistent( mode, attrib );
}

void CHsvEuropeInstallation_m_Priv::pins_ResetAttributeToDefault( int mode, int attrib )
{
	(pins_GetMedium() == pins_Terrestrial)?hsvdvbtins_dvbset_ResetAttributeToDefault( mode, attrib ):hsvdvbcins_ins_ResetAttributeToDefault( mode, attrib );
}

int CHsvEuropeInstallation_m_Priv::pins_GetAttribute( int mode, int attrib )
{
	int retval;
	if (attrib == pins_AttributeAnalogEnabled)
	{
		retval = AnalogEnabledStatus;
	}
	else if((hsvdvbcamins_dvbset_GetAttribute(AUTO_MODE,pins_AttributeNetworkOperator) == pins_DvbCCAM) || (hsvdvbcamins_dvbset_GetAttribute(AUTO_MODE,pins_AttributeNetworkOperator) == pins_DvbTCAM ))
	{
		//TraceNotice(m,"Get from Cam component ");
		retval = hsvdvbcamins_dvbset_GetAttribute(mode,attrib);
	}
	else
	{
		//TraceNotice(m,"pins_GetAttribute %d %d %d",mode,attrib,pins_GetMedium());
		if(mIsDVBCSpecificAttribute(attrib))
		{
			retval = hsvdvbcins_ins_GetAttribute( mode, attrib );
		}
		else
		{
			retval = ((pins_GetMedium() == pins_Terrestrial)?hsvdvbtins_dvbset_GetAttribute( mode, attrib ):hsvdvbcins_ins_GetAttribute( mode, attrib ));
		}
	}
	return retval;
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsAvailable( int mode, int attrib )
{
	Bool retval;
	retval = ((pins_GetMedium() == pins_Terrestrial)?hsvdvbtins_dvbset_IsAvailable( mode, attrib ):hsvdvbcins_ins_IsAvailable( mode, attrib ));
	return retval;
}

int CHsvEuropeInstallation_m_Priv::pins_GetAttributeMode( int mode, int attrib )
{
	return hsvdvbcins_ins_GetAttributeMode( mode, attrib );
}

Bool CHsvEuropeInstallation_m_Priv::pins_SetAttributeMode(int mode, int attrib, int attribMode)  
{
	return hsvdvbcins_ins_SetAttributeMode(mode, attrib, attribMode);
}

Bool CHsvEuropeInstallation_m_Priv::pins_GetAttributeRange(int mode, int attrib, int* minVal, int* maxVal)  
{
	return hsvdvbcins_ins_GetAttributeRange(mode, attrib, minVal, maxVal);
}

void CHsvEuropeInstallation_m_Priv::pins_StartSigStrMeas( int measmode )                     
{
	 sigstr_StartSigStrMeas( measmode );
}
void CHsvEuropeInstallation_m_Priv::pins_StopSigStrMeas( int measmode )                      
{
	sigstr_StopSigStrMeas( measmode );
}
Bool CHsvEuropeInstallation_m_Priv::pins_IsSignalStrengthMeasurementValid( int measmode )    
{
	return sigstr_IsSignalStrengthMeasurementValid( measmode );
}
int CHsvEuropeInstallation_m_Priv::pins_GetNetworkIDList()                          
{
   return hsvdvbtins_digacq_GetNetworkIDList();
}
void CHsvEuropeInstallation_m_Priv::pins_GetNetworkIDName(int index, Nat16*networkname)        
{
   hsvdvbtins_digacq_GetNetworkIDName(index, networkname);
}

void CHsvEuropeInstallation_m_Priv::pins_GetChannelListIDName(int index, Nat16*ChannelistName)        
{
   hsvdvbtins_digacq_GetChannelListIDName(index, ChannelistName);
}
int CHsvEuropeInstallation_m_Priv::pins_GetNumberOfChannelListIds()        
{
   return hsvdvbtins_digacq_GetNumberOfChannelListIds();
}

int CHsvEuropeInstallation_m_Priv::pins_GetChannelListIdByIndex(int index)
{
   return hsvdvbtins_digacq_GetChannelListIdByIndex(index);
}

void CHsvEuropeInstallation_m_Priv::pins_SetFavouriteChannelListId(int mode,int attrib,int index)     
{
   //TraceDebug(m,"pins_SetFavouriteChannelListId called with index[%d]",index);
   hsvdvbtins_digacq_SetFavouriteChannelListId(AUTO_MODE,rins_AttributeFavoriteChannelId,index);
}
      
HsvHierarchyMode CHsvEuropeInstallation_m_Priv::pins_GetHierarchyMode()                      
{
	return hsvdvbtins_dvbt_GetHierarchyMode();
}
HsvStreamPriority CHsvEuropeInstallation_m_Priv::pins_GetStreamPriority()                     
{
	return hsvdvbtins_dvbt_GetStreamPriority();
}

int CHsvEuropeInstallation_m_Priv::pins_GetInstallationProgress() /*New*/
{
    Int32 ProgressStatus = 0;
	int  PlfParam1 ;
	Nat32 errorcode;

	int MaxFrequency = pins_GetMaxFrequency();
	int MinFrequency = pins_GetMinFrequency();
	int MaxNoOfPass = pins_GetNoOfPass();
	int CurrentPass = pins_GetCurrentPass();
	InstallationPassSwitchOver++;
	if ((MaxNoOfPass > 1) && (CurrentPass > 1))
	{
		/* This is pass switchover time. During this time, it is seen that TVPlayer is still giving 
			last scan's frequency. So reduce the current pass if within switchover count and frequency 
			is less than Middle frequency  of band */
		if ((InstallationPassSwitchOver < MAX_SWITCHCASE_PRGCOUNT) && (CurrentFrequency > (450*16)))
		{
			CurrentPass--;
		}
	}
    if ((MaxFrequency > MinFrequency) && (MaxNoOfPass))
    {
		if((CurrentPass == SCAN_DVBT) && ((pins_FullScan == hsvdvbtins_dvbset_GetAttribute(pins_InstallationModeAutomatic, pins_AttributeScanMode)) || 
										  ((eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite ) && (pins_Terrestrial != pins_GetMedium()))) )
		{
			 MaxNoOfPass ++;
			feapi_GetActualChanBandwidth (WINDOWID, (tmFe_ChanBandwidth_t* ) (&PlfParam1), &errorcode);
			if(PlfParam1 == tmFe_ChanBandwidth8MHz)
			{
			  CurrentPass++;

			}

		}
        ProgressStatus = ((((CurrentFrequency - MinFrequency)  * 100) / 
                    ((MaxFrequency - MinFrequency) * MaxNoOfPass)) 
                + ((CurrentPass - 1) * 100 / MaxNoOfPass));
    }

    if(InsCompleted)
    {
        ProgressStatus = 100;
    }
	/*TODO: add it after Analog is integrated*/
    /*else if(mACIPageDisplayed)
    {
        ProgressStatus = ((100/MaxNoOfPass)*CurrentPass);
    }*/

    if(ProgressStatus < LastProgressStatus)
    {
        ProgressStatus = LastProgressStatus;
    }
    else
    {
        LastProgressStatus = ProgressStatus;
    }
	//TraceNotice(m,"ProgressStatus = %d", ProgressStatus);
    return (ProgressStatus);
}

void CHsvEuropeInstallation_m_Priv::pins_SetInstallRfSetting( int value ) /*New*/
{
	TraceNotice(m, "Install RfSetting is set to %d", value);
	sysset_SetInstallRfSetting(value);
}

void CHsvEuropeInstallation_m_Priv::pins_SetPbsMode( int value ) /*New*/
{
	TraceNotice(m, "Set PBS mode is set to %d", value);
	sysset_SetPbsMode(value);
}

void CHsvEuropeInstallation_m_Priv::pins_PrepareChNameUpdate(int ChUniID, int ServID ) /*New*/
{
	TraceNotice(m, "Set ChUniID and ServID for channel name updating is set to %d, %d", ChUniID, ServID);
	sysset_SetChUniqueIDForChNameUpdate(ChUniID);
	sysset_SetServiceIDForChNameUpdate(ServID);
}

void CHsvEuropeInstallation_m_Priv::pins_GetUpdatedChannelName( Nat16* pChName)
{
	TraceNotice(m, "Get Updated channel name.");
	sysset_GetUpdatedChannelName(pChName);
}

int CHsvEuropeInstallation_m_Priv::pins_GetUpdatedONID()
{
	TraceNotice(m, "Get Updated channel original network ID.");
	return sysset_GetUpdatedONID();
}

int CHsvEuropeInstallation_m_Priv::pins_GetUpdatedTsID()
{
	TraceNotice(m, "Get Updated channel TS ID.");
	return sysset_GetUpdatedTsID();
}

void CHsvEuropeInstallation_m_Priv::pins_SetIsDVBT2Scan(int abIsTrue)
{
	sysset_SetIsDVBT2Scan(abIsTrue);
}

void CHsvEuropeInstallation_m_Priv::pins_SetFocusedPlpId(int aiPlpId)
{
	sysset_SetFocusedPlpId(aiPlpId);
}

void CHsvEuropeInstallation_m_Priv::pins_SetExtractScanResult(int abIsTrue)
{
	sysset_SetExtractScanResult(abIsTrue);
}

int CHsvEuropeInstallation_m_Priv::pins_GetUpdatedSymbolRate()
{
	return sysset_GetUpdatedSymbolRate();
}

void CHsvEuropeInstallation_m_Priv::pins_SetLCNSortingControl( int mode ) /*New*/
{
	TraceNotice(m, "%s:%d:mode %d\n", __FUNCTION__, __LINE__, mode);
	s__CurLCNControlMode = mode;
}

int CHsvEuropeInstallation_m_Priv::pins_GetLCNSortingControl() /*New*/
{
	TraceNotice(m, "%s:%d:cur mode %d\n", __FUNCTION__, __LINE__, s__CurLCNControlMode);
	return s__CurLCNControlMode;
}

void CHsvEuropeInstallation_m_Priv::pins_SetInstallCountry( int country ) /*New*/
{
	TraceNotice(m, "Install Country is set to %d", country);
	syssetx_SetInstallCountry(country);

}
void CHsvEuropeInstallation_m_Priv::pins_SetSystemCountry( int country ) /*New*/
{
	//TraceNotice(m, "System Country is set to %d", country);
	if( (country >= cids_CountryAustria) /*&& (country < icountid_CountryMax)*/ )
	{        
		syssetx_SetSystemCountry(country);
		if( country != syssetx_GetInstallCountry() )
		{   
			/*TODO: check if new this action to be done based on notification from Tvserversettings.so*/

			isyssetN_OnCountryChanged(country);
			TraceNotice(m, "System Country changed to %d", country);
		}
	}
}

void CHsvEuropeInstallation_m_Priv::pins_GetFirstIntalledDigitalChannel(int *channelno)
{
	HsvPgdatPresetData preset;
    int NoOfRecords = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_Preset);
    
	while((NoOfRecords > 0))
	{
		if(pgdb_GetByIndex((pgdb_GetCurrentTable() | pgdbconst_Preset), (NoOfRecords-1), (Address)&preset))
		{
			if(preset.Type != AppApiAnalog)
			{
				break;
			}
		}
		else
		{
			//TraceErr(m, "pgdb_GetByIndex failed");
		}
		NoOfRecords--;
	}
	if(NoOfRecords > 0)
	{
		*channelno = preset.PresetNumber;
		TraceNotice(m, "pins_GetFirstIntalledDigitalChannel %d", *channelno);
	}
	else
	{
		//TraceNotice(m, "No Digitalchannel found");
	}
}

void CHsvEuropeInstallation_m_Priv::pins_GetFirstIntalledAnalogueChannel(int *channelno)
{
	HsvPgdatPresetData preset;
    int NoOfRecords = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_Preset);
    
	while((NoOfRecords > 0))
	{
		if(pgdb_GetByIndex((pgdb_GetCurrentTable() | pgdbconst_Preset), (NoOfRecords-1), (Address)&preset))
		{
			if(preset.Type == AppApiAnalog)
			{
				break;
			}
		}
		else
		{
			TraceErr(m, "pgdb_GetByIndex failed");
		}
		NoOfRecords--;
	}
	if(NoOfRecords > 0)
	{
		*channelno = preset.PresetNumber;
		TraceNotice(m, "pins_GetFirstIntalledAnalogChannel %d", *channelno);
	}
	else
	{
		//TraceNotice(m, "No Analogchannel found");
	}
}

Bool CHsvEuropeInstallation_m_Priv::mCheckRadioservice(HsvPgdatPresetData* preset)
{
	HsvPgdatDigServiceData data;
	Bool retval = FALSE;

	ASSIGN_DIGSVC_KEYS(&data, preset);
	if(pgdb_GetByKey((pgdb_GetCurrentTable() | pgdbconst_DigitalService), (Address)&data))
	{               
		if((data.ServiceType == AppApiRadioService) || (data.ServiceType == AppApiAdvCodecRadioService))
		{
			retval = TRUE;
		}
	}
	else
	{
		//TraceErr(m, "pgdb_GetByKey failed");
	}
	return retval;
}

void CHsvEuropeInstallation_m_Priv::pins_GetFirstIntalledRadioChannel(int *channelno)
{
	HsvPgdatPresetData preset;
	*channelno = 0;
    int NoOfRecords = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_Preset);
    
	while((NoOfRecords > 0))
	{
		if(pgdb_GetByIndex((pgdb_GetCurrentTable() | pgdbconst_Preset), (NoOfRecords-1), (Address)&preset))
		{
			if((preset.Type != AppApiAnalog)&& mCheckRadioservice(&preset))
			{
				break;
			}
		}
		else
		{
			//TraceErr(m, "pgdb_GetByIndex failed");
		}
		NoOfRecords--;
	}
	if(NoOfRecords > 0)
	{
		*channelno = preset.PresetNumber;
		TraceNotice(m, "pins_GetFirstIntalledDigitalChannel %d", *channelno);
	}
	else
	{
		//TraceNotice(m, "No Digitalchannel found");
	}
	
}

Bool CHsvEuropeInstallation_m_Priv::mCheckVisibleService(HsvPgdatPresetData* preset)
{
	HsvPgdatDigServiceData data;
	Bool retval = FALSE;

	if(InsStatus.Mode == CAM_MODE){
		ASSIGN_CAM_DIGSVC_KEYS(&data, preset);
	}
	else{
		ASSIGN_DIGSVC_KEYS(&data, preset);
	}
	if(pgdb_GetByKey((pgdb_GetCurrentTable() | pgdbconst_DigitalService), (Address)&data))
	{               
		/* check if HD LCN is assigned as PresetNumber. */			
		retval = (eurdiv_IsDbookCountry() == TRUE) ?  (!data.SystemHidden) : data.VisibleService;
	}
	else
	{
		//TraceErr(m, "pgdb_GetByKey failed");
	}
	return retval;
}

void CHsvEuropeInstallation_m_Priv::pins_GetFirstInstalledChannel(int *channelno)
{
	HsvPgdatPresetData preset;
	HsvChannel channel;
	*channelno = -1;
    int NoOfRecords = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_Preset);
	
	

	if (InsStatus.Mode == MANUAL_MODE)
	{
		/* In case of manual installation switching should be done to manually installed channel only */
		channel = pins_GetInstalledWeakSignalChannel();
		*channelno = channel.Channel.Digit;
	}
	else
	{
		while(NoOfRecords > 0)
		{
			if(pgdb_GetByIndex((pgdb_GetCurrentTable() | pgdbconst_Preset), (NoOfRecords-1), (Address)&preset))
			{
				if((preset.Type == AppApiAnalog) || mCheckVisibleService(&preset))
				{
					break;
				}
			}
			else
			{
				//TraceErr(m, "pgdb_GetByIndex failed");
			}
			NoOfRecords--;
		}
		if(NoOfRecords > 0)
		{
			*channelno = preset.PresetNumber;
			TraceNotice(m, "pins_GetFirstInstalledChannel %d", *channelno);
		}
		else
		{
			//TraceNotice(m, "No Visible Service found");
		}
	}
}

void CHsvEuropeInstallation_m_Priv::pins_GetNetworkNameForNetworkID(int networkID, Nat16 *NetworkName)
{
	Bool Found = FALSE;
	Nat16 NetworkId, lSelectedNetworkID = networkID;
	int i;

	if(pins_GetMedium() == pins_Cable) {
		int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
		if((InsStatus.Country == cids_CountryBelgium) && (NetworkOperator == rins_None)) {
			return;
		}
	}
	

	if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &NetworkId))
	{
		if((lSelectedNetworkID == NetworkId) || (networkID == 0))
		{
			if(strapi_GetByKey(HsvMain, HSVSPID(NetworkName, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, (void *)(NetworkName)) )
			{
				Found = TRUE;
			}
		}
	}
	
	if(!Found)
	{
		HsvNITOtherNetworkIdInfo lOtherNIDInfo;
		if((InsStatus.Pass == SCAN_DVBC) && (rins_FullScan == rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode)) )
		{
			memcpy(NetworkName, FullScanNetworkName, MAX_NETWORK_NAME_SIZE);
		}
		else if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), lSelectedNetworkID, 0, 0, &lOtherNIDInfo))
		{
			mUnicodeCopy(NetworkName, lOtherNIDInfo.Name);
		}
	}

}

void CHsvEuropeInstallation_m_Priv::pins_GetListOfNetworkIDs (int *NumberOfEntries, int *NetworkIDList)
{
    int lSize,i;
    HsvNITOtherNetworkIdInfo lOtherNIDInfo;
	Nat16	ActualNID = 0;

	*NumberOfEntries = 0;

    if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &ActualNID))
    {
		NetworkIDList[0] = ActualNID;
		if((strapi_GetSize(HsvMain, HSVSPID(ActualCableDS, dvb, nit))) > 0)
		{
			++(*NumberOfEntries);
		}
		else
		{
			TraceNotice(m, "No CDSD available in this MUX");
		}
    }

    lSize = strapi_GetSize(HsvMain, HSVSPID(OtherNetworkIDInfo,dvb,nit));

    for(i = 0; i < lSize; i++)
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(OtherNetworkIDInfo,dvb,nit), i, &lOtherNIDInfo))
        {
			NetworkIDList[*NumberOfEntries] = lOtherNIDInfo.NetworkId;
            ++(*NumberOfEntries);

        }
    }

	return;
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsValidNetworkId (int networkID)
{
    Nat16 lSelectableNetworkID;
    Bool lFound = FALSE, lretval = FALSE;
    int lMinNetworkID, lMaxNetworkID;


    lretval = pins_GetAttributeRange(pins_InstallationModeAutomatic, pins_AttributeNetworkId, &lMinNetworkID, &lMaxNetworkID);
    if((networkID <= lMaxNetworkID) && (networkID >=lMinNetworkID))
    {

		int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
		
		if( ( (pins_GetMedium() == pins_Cable) && (sysset_GetSystemCountry() == cids_CountryNetherlands)
		&& ((NetworkOperator == pins_Ziggo) || (NetworkOperator == pins_None))) 
		|| (pins_GetMedium() == pins_Cable && sysset_GetSystemCountry() == cids_CountryBelgium && NetworkOperator == pins_Telenet)  ||
		   (pins_GetMedium() == pins_Cable && sysset_GetSystemCountry() == cids_CountryDenmark && NetworkOperator == rins_YouSee))  
		{

			lFound = TRUE;
		} else {
		if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &lSelectableNetworkID))
		{
			if(lSelectableNetworkID == networkID)
			{
				lFound = TRUE;
			}
		}
    
		if(!lFound)
		{
			int lSize = strapi_GetSize(HsvMain, HSVSPID(OtherNetworkIDInfo,dvb,nit));
			int i;
			HsvNITOtherNetworkIdInfo lOtherNIDInfo;
        
			for(i = 0; i < lSize; i++)
			{
				if(strapi_GetByIndex(HsvMain, HSVSPID(OtherNetworkIDInfo,dvb,nit), i, &lOtherNIDInfo))
				{
					if(lOtherNIDInfo.NetworkId == networkID)
					{
						lFound = TRUE;
						break;
					}
				}
			}
		}
    }
    	}
    else
    {
        TraceDebug(m,"Entered manual Network ID is not in the correct range ! Pop the NetworkID  message");

    }

	TraceNotice (m, "IsValidNetworkID returned %d  for entered ID %d ", lFound, networkID);
    return lFound;
}


void CHsvEuropeInstallation_m_Priv::pins_SetLowestNetworkId (int *networkID)
{
	int lSelectableNetworkID = 0xFFFF;

    if(pins_GetInstallationMode() == pins_InstallationModePreScan)
    {
        int i, lSize = strapi_GetSize(HsvMain, HSVSPID(OtherNetworkIDInfo,dvb,nit));
        HsvNITOtherNetworkIdInfo lOtherNIDInfo;
        Nat16 ActualNetworkID  = 0xFFFF, lSelectableNetworkID = 0xFFFF;


        for(i = 0; i < lSize; i++)
        {
            if(strapi_GetByIndex(HsvMain, HSVSPID(OtherNetworkIDInfo,dvb,nit), i, &lOtherNIDInfo))
            {
                if(lOtherNIDInfo.NetworkId < lSelectableNetworkID)
                {
                    lSelectableNetworkID = lOtherNIDInfo.NetworkId;
                }
            }
        }

        if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, &ActualNetworkID))
        {
            if(ActualNetworkID < lSelectableNetworkID)
            {
                lSelectableNetworkID = ActualNetworkID;
            }
        }
        pins_SetAttributeMode(pins_InstallationModeAutomatic, pins_AttributeNetworkId, pins_ManualValue);
        pins_SetAttribute(pins_InstallationModeAutomatic, pins_AttributeNetworkId, lSelectableNetworkID);		
    }

	*networkID = lSelectableNetworkID;

}


        /* Naresh:  for Italy */
void CHsvEuropeInstallation_m_Priv::pins_SetUserSelectConflictService(int LcnIndex, int DbIndex)    
{
	iconf_SetUserSelectConflictService(LcnIndex, DbIndex);
}
void CHsvEuropeInstallation_m_Priv::pins_ConflictsSelectionDone(Bool UserSelection)              
{
	iconf_ConflictsSelectionDone(UserSelection);
}
void CHsvEuropeInstallation_m_Priv::pins_GetConflictServices(HsvConflictServicesData *ConflictList, int *NumRecords)      
{
	iconf_GetConflictServices(ConflictList, NumRecords);   
}
        
/* Naresh: for dvbt2 */
int CHsvEuropeInstallation_m_Priv::pins_GetPLPIds(int *PLPIds)                       
{
	return hsvdvbtins_dvbt_GetPLPIds(PLPIds);
}
void CHsvEuropeInstallation_m_Priv::pins_GetRegionList(HsvNetworkRegionsData *RegionsData)              
{
	hsvdvbtins_digacq_GetRegionList(RegionsData);
}
int CHsvEuropeInstallation_m_Priv::pins_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType)    
{
   return hsvdvbtins_digacq_GetFavouriteRegion(mode, RegionType);
}
        
//divsupp_PresetNameLength                    =   div_PresetNameLength;
    
int CHsvEuropeInstallation_m_Priv::divsupp_InstallTestStreams( int mode, int medium )
{
	return div_InstallTestStreams( mode, medium );
}

Bool CHsvEuropeInstallation_m_Priv::divsupp_StaticTable()
{
	return eurdiv_StaticTable();    
}



void CHsvEuropeInstallation_m_Priv::feapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	hsvprins_feapiN_OnSearchStateChanged( state );
	hsvdvbtins_feapiN_OnSearchStateChanged( state );
    hsvdvbtmpegins_feapiN_OnSearchStateChanged( state );
    hsvdvbcins_feapiN_OnSearchStateChanged( state );
    hsvdvbcamins_feapiN_OnSearchStateChanged( state );
	return;
}

/*
void feapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}*/

void CHsvEuropeInstallation_m_Priv::feapiN_OnStationFound( void ) 
{
	hsvprins_feapiN_OnStationFound( );
 	hsvdvbtins_feapiN_OnStationFound( );
    hsvdvbtmpegins_feapiN_OnStationFound( );
    hsvdvbcins_feapiN_OnStationFound( );
    hsvziggoins_feapiN_OnStationFound( );
    hsvdvbcamins_feapiN_OnStationFound( );
	hsvcanaldigitalins_feapiN_OnStationFound( );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnStationNotFound( void ) 
{
	hsvprins_feapiN_OnStationNotFound( );
	hsvdvbtins_feapiN_OnStationNotFound( );
    hsvdvbtmpegins_feapiN_OnStationNotFound( );
    hsvdvbcins_feapiN_OnStationNotFound( );
    hsvziggoins_feapiN_OnStationNotFound( );
    hsvdvbcamins_feapiN_OnStationNotFound( );
	hsvcanaldigitalins_feapiN_OnStationNotFound();
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	hsvprins_feapiN_OnTvSystemDetected(tvSystem);
	hsvdvbtins_feapiN_OnTvSystemDetected( tvSystem );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	hsvprins_feapiN_OnAfcFreqChanged(freq);
	hsvdvbtins_feapiN_OnAfcFreqChanged( freq );
   hsvdvbtmpegins_feapiN_OnAfcFreqChanged( freq );
    hsvdvbcins_feapiN_OnAfcFreqChanged( freq );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnAfcLimitReached(Nat32 freq ) 
{
	hsvprins_feapiN_OnAfcLimitReached( freq );
	hsvdvbtins_feapiN_OnAfcLimitReached( freq );
    hsvdvbtmpegins_feapiN_OnAfcLimitReached( freq );
    hsvdvbcins_feapiN_OnAfcLimitReached( freq );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnAfcModeChanged( void ) 
{
	hsvprins_feapiN_OnAfcModeChanged( );
 	hsvdvbtins_feapiN_OnAfcModeChanged( );
    hsvdvbtmpegins_feapiN_OnAfcModeChanged( );
    hsvdvbcins_feapiN_OnAfcModeChanged( );
	return;
}

/*
void feapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	return;
}*/

void CHsvEuropeInstallation_m_Priv::feapiN_OnMeasAborted( int ssm ) 
{
	hsvprins_feapiN_OnMeasAborted( ssm );
	hsvdvbtins_feapiN_OnMeasAborted( ssm );
    hsvdvbtmpegins_feapiN_OnMeasAborted( ssm );
    hsvdvbcins_feapiN_OnMeasAborted( ssm );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	hsvprins_feapiN_OnConstellationDetected( constellation );
	hsvdvbtins_feapiN_OnConstellationDetected( constellation );
  	hsvdvbtmpegins_feapiN_OnConstellationDetected( constellation );
    hsvdvbcins_feapiN_OnConstellationDetected( constellation );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	hsvprins_feapiN_OnIqModeDetected( mode );
	hsvdvbtins_feapiN_OnIqModeDetected( mode );
    hsvdvbtmpegins_feapiN_OnIqModeDetected( mode );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	hsvprins_feapiN_OnCodeRateDetected( highPrioRate, lowPrioRate );
	hsvdvbtins_feapiN_OnCodeRateDetected( highPrioRate, lowPrioRate );
    hsvdvbtmpegins_feapiN_OnCodeRateDetected( highPrioRate, lowPrioRate );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	hsvprins_feapiN_OnHierarchyModeDetected( mode );
	hsvdvbtins_feapiN_OnHierarchyModeDetected( mode );
    hsvdvbtmpegins_feapiN_OnHierarchyModeDetected( mode );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	hsvprins_feapiN_OnGuardIntervalDetected( interval );
	hsvdvbtins_feapiN_OnGuardIntervalDetected( interval );
    hsvdvbtmpegins_feapiN_OnGuardIntervalDetected( interval );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	hsvprins_feapiN_OnTxModeDetected( mode );
	hsvdvbtins_feapiN_OnTxModeDetected( mode );
    hsvdvbtmpegins_feapiN_OnTxModeDetected( mode );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	hsvprins_feapiN_OnChanBandwidthDetected( bandwith);
	hsvdvbtins_feapiN_OnChanBandwidthDetected( bandwith );
    hsvdvbtmpegins_feapiN_OnChanBandwidthDetected( bandwith );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	hsvprins_feapiN_OnCarrierPresentChanged( carrier );
    hsvdvbtins_feapiN_OnCarrierPresentChanged( carrier );
    hsvdvbtmpegins_feapiN_OnCarrierPresentChanged( carrier );
	return;
}

void CHsvEuropeInstallation_m_Priv::feapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	hsvprins_feapiN_OnBerThresholdCrossed( ber, berThreshold );
 	hsvdvbtins_feapiN_OnBerThresholdCrossed( ber, berThreshold );
    hsvdvbtmpegins_feapiN_OnBerThresholdCrossed( ber, berThreshold );
	return;
}

void CHsvEuropeInstallation_m_Priv::ctrlN_OnEvent(HsvDemux dmx,int eventid,int value)
{
	ictrlN_OnEvent(dmx, eventid, value);
	tctrlN_OnEvent(dmx, eventid, value);
	cctrlN_OnEvent(dmx, eventid, value);
	hsvziggoins_ctrlN_OnEvent(dmx, eventid, value);
	hsvcanaldigitalins_ctrlN_OnEvent(dmx, eventid, value);
}



/*hsveuins_mSourcesetup.c*/


void CHsvEuropeInstallation_m_Priv::DetermineMedium(int* Medium, HsvInstallationPass Pass)
{
	switch(Pass)
	{
		case SCAN_ANALOG:
			*Medium = srcstp_Analog;
			break;
		case SCAN_DVBC:
			*Medium = srcstp_DVBC;
			break;
		case SCAN_DVBT:
		case SCAN_MPEG_ONLY:
			*Medium = srcstp_DVBT;
			break;
		default:
			*Medium = srcstp_NONE;
			break;
	}
}


Nat32 CHsvEuropeInstallation_m_Priv::DetermineSourceDesignator(HsvStreamType StreamType)
{
    Nat32 SourceDesignator = plfdesigid_DesignatorNone;

    if(StreamType == HsvAnalogue)
    {
        SourceDesignator = plfdesigid_DesignatorAnalog;

    }
    else if(StreamType == HsvMpegTs)
    {
        SourceDesignator = plfdesigid_DesignatorDigital;

    }
    return SourceDesignator;
}

Bool CHsvEuropeInstallation_m_Priv::mSourceSetupAndApply(HsvInstallationPass Pass)
{
    int retval = srcstp_WaitForSourceSetupApplyNotify;
	int Medium;	

    DetermineMedium(&Medium, Pass);


    retval = srcstp_SourceSetupApply(Medium);
	

	if(retval == srcstp_Success)
	{
		pmp_PmpSend(mPump, EvSourceSetupApplied, (Nat32)NULL);
	}
    else if(retval == srcstp_WaitForSourceSetupApplyNotify)
    {
    }
    

	
    return retval;
}

void CHsvEuropeInstallation_m_Priv::srcstpN_OnSourceSetupApplied(int Status)
{
    if(TURNED_ON)
    {

        pmp_PmpSend(mPump, ((Status == srcstp_Success)? EvSourceSetupApplied: EvStop), (Nat32)NULL);
    }
}


void CHsvEuropeInstallation_m_Priv::ipgaciN_OnAciInstallationCompleted ( Bool success  ) 
{
	hsvprins_pgaciN_OnAciInstallationCompleted ( success );
	return;
}

void CHsvEuropeInstallation_m_Priv::ipgaciN_aciPresetsWriteInDataStarted( void ) 
{
	hsvprins_pgaciN_aciPresetsWriteInDataStarted();
	return;
}

 Bool CHsvEuropeInstallation_m_Priv::divsupp_ParseLCN( void )
 {
 return 1;
 }
 
void CHsvEuropeInstallation_m_Priv::implins_StartImplicitInstallation( HsvChannel chan )
{
	hsvprins_implins_StartImplicitInstallation(chan);
}
void CHsvEuropeInstallation_m_Priv::implins_StopImplicitInstallation( void )
{
	hsvprins_implins_StopImplicitInstallation();
}
   
void CHsvEuropeInstallation_m_Priv::acidat_StorePreset( HsvAciSingleInfo presetInfo ,Bool clear )
{
	hsvprins_acidat_StorePreset(presetInfo, clear);
}
HsvAciLanguage CHsvEuropeInstallation_m_Priv::acidat_GetAciLanguage(int language)
{
	return hsvprins_acidat_GetAciLanguage(language);
}
	 
void CHsvEuropeInstallation_m_Priv::pins_SetManualFrequency( int frequency, int offset, Bool finetune ) 
{
	hsvprins_prins_SetManualFrequency(frequency, offset, finetune);
}

void CHsvEuropeInstallation_m_Priv::pins_GetManualFrequency ( int *frequency, int *offset, Bool *finetune ) 
{
	hsvprins_prins_GetManualFrequency(frequency, offset, finetune);
}

void CHsvEuropeInstallation_m_Priv::pins_SetManualChannel( int channel, Bool finetune ) 
{
	hsvprins_prins_SetManualChannel(channel, finetune );
}

void CHsvEuropeInstallation_m_Priv::pins_GetManualChannel( int *channel, Bool *finetune ) 
{
	hsvprins_prins_GetManualChannel(channel, finetune );
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsManualInstallationModeSupported ( int mode ) 
{
	return hsvprins_prins_IsManualInstallationModeSupported( mode );
}

void CHsvEuropeInstallation_m_Priv::pins_SetManualInstallationMode( int mode ) 
{
	hsvprins_prins_SetManualInstallationMode(mode);
}

int CHsvEuropeInstallation_m_Priv::pins_GetManualInstallationMode( void ) 
{
	return hsvprins_prins_GetManualInstallationMode();
}

void CHsvEuropeInstallation_m_Priv::pins_StoreManualInstallationValues( HsvChannel channel ) 
{
	hsvprins_prins_StoreManualInstallationValues(channel);
}
Bool CHsvEuropeInstallation_m_Priv::pins_StartFrequencySearch(void) 
{
	return hsvprins_prins_StartFrequencySearch();
}
Bool CHsvEuropeInstallation_m_Priv::pins_IsFrequencySearchDirectionSupported( Bool searchup ) 
{
	return FALSE;
}

void CHsvEuropeInstallation_m_Priv::pins_SetFrequencySearchDirection ( Bool searchup ) 
{
	return;
}

/* This function is used to determine which TVSystem needs to be searched during analog installation
	Return 	TRUE: NTSC M
			FALSE: PAL */
Bool CHsvEuropeInstallation_m_Priv::pins_GetFrequencySearchDirection ( void ) 
{
	Bool RetVal = FALSE;
	switch (sysset_GetSystemCountry())
	{
		case cids_CountryAustralia:
		case cids_CountryThailand:
		case cids_CountryNewZealand:
		case cids_CountrySingapore:
		case cids_CountryMalaysia:
		case cids_CountryTaiwan:
		case cids_CountryIndonesia:
			RetVal = TRUE;
			break;
		default:
			break;
	}
	return RetVal;
}
Bool CHsvEuropeInstallation_m_Priv::pins_IsTvSystemSupported( int tvsystem ) 
{
	return hsvprins_anaset_IsTvSystemSupported (tvsystem);
}

void CHsvEuropeInstallation_m_Priv::pins_SetTvSystem ( int tvsystem ) 
{
	hsvprins_anaset_SetTvSystem (tvsystem);
}

int CHsvEuropeInstallation_m_Priv::pins_GetTvSystem( void ) 
{
	return hsvprins_anaset_GetTvSystem();
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsColorSystemSupported( int colorsystem ) 
{
	return hsvprins_anaset_IsColorSystemSupported ( colorsystem);
}

void CHsvEuropeInstallation_m_Priv::pins_SetColorSystem ( int colorsystem ) 
{
	hsvprins_anaset_SetColorSystem (colorsystem ) ;
}

int CHsvEuropeInstallation_m_Priv::pins_GetColorSystem( void ) 
{
	return hsvprins_anaset_GetColorSystem();;
}

Bool CHsvEuropeInstallation_m_Priv::pins_IsValidPTC(int medium,int PTC) 
{
	return FALSE;
}

int CHsvEuropeInstallation_m_Priv::pins_GetMinPTC(int medium) 
{
	return 0;
}

int CHsvEuropeInstallation_m_Priv::pins_GetMaxPTC(int medium) 
{
	return 0;
}

int CHsvEuropeInstallation_m_Priv::pins_GetLastPTCFound(void) 
{
	return 0;
}

int CHsvEuropeInstallation_m_Priv::pins_GetNumberOfPTCsFound(void) 
{
	return 0;
}
void CHsvEuropeInstallation_m_Priv::pins_Initialise(void) 
{
	return;
}

void CHsvEuropeInstallation_m_Priv::iafscanN_OnAltFrequencyScanRequested(void)

{
}
	void CHsvEuropeInstallation_m_Priv::iafscanN_OnAltFrequencyScanInProgress(void)
{
}
	void CHsvEuropeInstallation_m_Priv::iafscanN_OnAltFrequencyScanCompleted(int Status)
{
}
	void CHsvEuropeInstallation_m_Priv::iafscanN_OnFrequencyListUpdateDetected(void)
{
}

void CHsvEuropeInstallation_m_Priv::pacidsN_OnMultiPackageFound ( void )
{
	hsvprins_pacidsN_OnMultiPackageFound();
}
void CHsvEuropeInstallation_m_Priv::pacidsN_OnMultiPackageToBeDisplayed(void)
{
	hsvprins_pacidsN_OnMultiPackageToBeDisplayed();	
	//TraceNotice(m, "Hsvprins: %s %d ",__FUNCTION__,__LINE__);
}
void CHsvEuropeInstallation_m_Priv::pacidsN_OnMultiPackageDisplayed ( void )
{
	hsvprins_pacidsN_OnMultiPackageDisplayed();
}
void CHsvEuropeInstallation_m_Priv::pacidsN_OnMultiPackageRemoved ( void )
{
	hsvprins_pacidsN_OnMultiPackageRemoved ();
}
	
void CHsvEuropeInstallation_m_Priv::resetN_OnResetEnd  ( void )
{
	hsvprins_resetN_OnResetEnd();
}

void CHsvEuropeInstallation_m_Priv::colN_OnColorSystemChanged( void )
{
	hsvprins_colN_OnColorSystemChanged();
}
void CHsvEuropeInstallation_m_Priv::colN_OnCombFilterActiveChanged( void )
{
	hsvprins_colN_OnCombFilterActiveChanged();     
}
void CHsvEuropeInstallation_m_Priv::hsvdvbtmpegins_digscanN_OnEvent(int event)
{
}

void CHsvEuropeInstallation_m_Priv::OnInterfaceRemoved (int interfaceID)
{
	//TraceNotice (m , "OnInterfaceRemoved ");
}

void CHsvEuropeInstallation_m_Priv::OnInterfacesUpdated (void)
{
	//TraceNotice (m , "OnInterfaceUpdated ");
}

	/*** TVPROVIDER IMPLEMENTATION START ***/
int CHsvEuropeInstallation_m_Priv::pins_GetNumberOfDatabaseRecords(int TSDataOnly)
{
	int NoOfEntries = 0;
	/* Aneesh: TODO: Once completely moved to srtdb, remove the active database setting */
	pgdb_SelectActiveChannelDatabase(pgdb_TempDatabase);
	if(!TSDataOnly)
	{
		NoOfEntries = pgdb_GetNoRecords(PRESET_TABLE);
	}
	else
	{
		NoOfEntries = pgdb_GetNoRecords(FREQMAP_TABLE);
	}
	//pgdb_SelectActiveChannelDatabase(pgdb_SqliteDatabase);

	TraceNotice (m ," Number of database records %d TSDataOnly %d",  NoOfEntries, TSDataOnly);
	return NoOfEntries;
}

void CHsvEuropeInstallation_m_Priv::mInitializeTvProviderData (HsvPgdatTvProviderBlobData	*TvProviderData)
{
#define NO
#define NAME
#define NONE
#define A(x)    [0]


#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      TvProviderData->item siz = def;
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     TvProviderData->item siz = def;
#define	TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)      TvProviderData->item siz = def;
#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)      TvProviderData->item siz = def;
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     TvProviderData->item siz = def;
#define	TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)     TvProviderData->item siz = def;
#define	TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)     TvProviderData->item siz = def;
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_ANALOG_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_COMMON_VECTOR_ITEM
#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM


#undef NO
#undef NAME
#undef NONE
#undef A

}

void CHsvEuropeInstallation_m_Priv::mCollectDigSrvProviderData (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->TextSubTitlePage = DigSrvcData->TextSubTitlePage ;
	TvProviderData->LogoURL = DigSrvcData->LogoURL ;
	TvProviderData->DecoderType = DigSrvcData->DecoderType ;
	TvProviderData->ModulationType = DigSrvcData->ModulationType ;
	TvProviderData->UserModifiedLogo = DigSrvcData->UserModifiedLogo ;
	TvProviderData->SAP = DigSrvcData->SAP ;
	TvProviderData->PreferredStereo = DigSrvcData->PreferredStereo ;
	TvProviderData->Ptc = DigSrvcData->Ptc ;
	TvProviderData->SymbolRate = DigSrvcData->SymbolRate ;
	TvProviderData->StreamPriority = DigSrvcData->StreamPriority ;
	TvProviderData->AudioPid = DigSrvcData->AudioPid ;
	TvProviderData->VideoPid = DigSrvcData->VideoPid ;
	TvProviderData->PcrPid = DigSrvcData->PcrPid ;
	TvProviderData->NetworkId = DigSrvcData->NetworkId ;
	TvProviderData->LCN = DigSrvcData->LCN ;
	TvProviderData->ServiceType = DigSrvcData->ServiceType ;
	TvProviderData->SystemHidden = DigSrvcData->SystemHidden ;
	TvProviderData->NumericSelect = DigSrvcData->NumericSelect ;
	TvProviderData->Bandwidth = DigSrvcData->Bandwidth ;
	TvProviderData->ScrambledStatus = DigSrvcData->SrcambledStatus ;
	TvProviderData->IntHbbTvOption = DigSrvcData->HbbTvOption ;
	TvProviderData->UserHidden = DigSrvcData->UserHidden ;
	TvProviderData->NewPreset = DigSrvcData->NewPreset ;
	TvProviderData->VideoStreamType = DigSrvcData->VideoStreamType ;
	TvProviderData->AudioStreamType = DigSrvcData->AudioStreamType ;

	/*Private Data*/
	TvProviderData->SignalStrength = DigSrvcData->SignalStrength ;
	TvProviderData->SignalQuality = DigSrvcData->SignalQuality ;
	TvProviderData->DateStamp = DigSrvcData->DateStamp ;
	TvProviderData->DeltaVolume = DigSrvcData->DeltaVolume ;
	TvProviderData->PmtPid = DigSrvcData->PmtPid ;
	TvProviderData->SecAudioPid = DigSrvcData->SecAudioPid ;
	TvProviderData->LowPrioLCN = DigSrvcData->LowPrioLCN ;
	TvProviderData->LowPrioVisibleService = DigSrvcData->LowPrioVisibleService ;
	TvProviderData->FreeCiMode = DigSrvcData->FreeCiMode ;
	TvProviderData->VideoDescPresent = DigSrvcData->VideoDescPresent ;
	if((eurdiv_IsDbookCountry() == TRUE) && (TvProviderData->PresetNumber == TvProviderData->LowPrioLCN)) {
		TvProviderData->VisibleService = TvProviderData->LowPrioVisibleService;
	} else {
		TvProviderData->VisibleService = DigSrvcData->VisibleService ;
	}
	TvProviderData->OUI = DigSrvcData->OUI ;
	TvProviderData->ServiceListVersion = DigSrvcData->ServiceListVersion ;
	TvProviderData->SecAudioStreamType = DigSrvcData->SecAudioStreamType ;
	TvProviderData->UserModifiedName = DigSrvcData->UserModifiedName ;
	TvProviderData->PreferredNicam = DigSrvcData->PreferredNicam ;
	TvProviderData->MatchBrandFlag = DigSrvcData->MatchBrandFlag ;
	TvProviderData->NumBrandIds = DigSrvcData->NumBrandIds ;
	//TvProviderData->SrcambledStatus = DigSrvcData->SrcambledStatus ;
	TvProviderData->RegionDepth = DigSrvcData->RegionDepth ;
	TvProviderData->PrimaryRegion = DigSrvcData->PrimaryRegion ;
	TvProviderData->SecondaryRegion = DigSrvcData->SecondaryRegion ;
	TvProviderData->TertiaryRegion = DigSrvcData->TertiaryRegion ;
	TvProviderData->CountryCode = DigSrvcData->CountryCode ;
	TvProviderData->HDSimulcastRepOnId = DigSrvcData->HDSimulcastRepOnId ;
	TvProviderData->HDSimulcastRepTsId = DigSrvcData->HDSimulcastRepTsId ;
	TvProviderData->HDSimulcastRepSvcId = DigSrvcData->HDSimulcastRepSvcId ;
	TvProviderData->FavoriteNumber = DigSrvcData->FavoriteNumber ;
			


	

	memcpy ((void*)TvProviderData->TxtPages,(void *)DigSrvcData->TxtPages, 23*sizeof(Nat16));
	memcpy ((void*)TvProviderData->ChannelName,(void *)DigSrvcData->ChannelName,(MAXSERVICENAMELEN + 1)*sizeof(Nat16));

	memcpy ((void*)TvProviderData->BrandIds,(void *)DigSrvcData->BrandIds,23*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultipleLCN,(void *)DigSrvcData->MultipleLCN,8*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultiplePreset,(void *)DigSrvcData->MultiplePreset,8*sizeof(Nat16));
	memcpy ((void*)TvProviderData->MultipleFavorite,(void *)DigSrvcData->MultipleFavorite,8*sizeof(Nat8));

       // Get the UniqueId corresponding to Preset Number
       mGetUniqueIdFromPresetNumber (DigSrvcData, TvProviderData);

}


void CHsvEuropeInstallation_m_Priv::mCollectDigTSProviderData (	HsvPgdatDigTSData	*DigTsData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->ASignalStrength = DigTsData->ASignalStrength ;
	TvProviderData->VSignalStrength = DigTsData->VSignalStrength ;
	TvProviderData->QSignalStrength = DigTsData->QSignalStrength ;
	TvProviderData->SDTVersion = DigTsData->SDTVersion ;
	TvProviderData->NITVersion = DigTsData->NITVersion ;
	TvProviderData->CDSDFrequency = DigTsData->CDSDFrequency ;
	TvProviderData->CodeRate = DigTsData->CodeRate ;
	TvProviderData->HierarchyMode = DigTsData->HierarchyMode ;
	TvProviderData->GuardInterval = DigTsData->GuardInterval ;
	TvProviderData->PtcListVersion = DigTsData->PtcListVersion ;
	TvProviderData->TSVersion = DigTsData->TSVersion ;
	TvProviderData->UserInstalled = DigTsData->UserInstalled ;
	TvProviderData->BarkerMux = DigTsData->BarkerMux ;
	TvProviderData->LanguageCode = DigTsData->LanguageCode ;
}


void CHsvEuropeInstallation_m_Priv::mCollectAnalogProviderData (HsvPgdatAnalogData  *AnalogData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->TextSubTitlePage = AnalogData->TextSubTitlePage ;
	TvProviderData->LogoURL = AnalogData->LogoURL ;
	TvProviderData->DecoderType = AnalogData->DecoderType ;
	TvProviderData->ModulationType = AnalogData->ModulationType ;
	TvProviderData->UserModifiedLogo = AnalogData->UserModifiedLogo ;
	TvProviderData->SAP = AnalogData->SAP ;
	TvProviderData->PreferredStereo = AnalogData->PreferredStereo ;
	memcpy ((void*)TvProviderData->TxtPages,(void *)AnalogData->TxtPages, 23*sizeof(Nat16));
	memcpy ((void*)TvProviderData->ChannelName,(void *)AnalogData-> ChannelName,33*sizeof(Nat16));
	TvProviderData->CniNi = AnalogData->CniNi;


	TvProviderData->FineTuneFrequency = AnalogData->FineTuneFrequency;
	TvProviderData->SignalStrength = AnalogData->SignalStrength;
	TvProviderData->FineTuneOffset = AnalogData->FineTuneOffset;
	TvProviderData->ColourSystem = AnalogData->ColourSystem;
	TvProviderData->DeltaVolume = AnalogData->DeltaVolume;
	TvProviderData->DataIndicator = AnalogData->DataIndicator;
	TvProviderData->Attenuator = AnalogData->Attenuator;
	TvProviderData->Tuned = AnalogData->Tuned;
	TvProviderData->DeTuned = AnalogData->DeTuned;
	TvProviderData->AgcInstalled = AnalogData->AgcInstalled;
	TvProviderData->UserModifiedName = AnalogData->UserModifiedName;
	TvProviderData->PreferredFavorite = AnalogData->PreferredFavorite;
	TvProviderData->PreferredNicam = AnalogData->PreferredNicam;
	TvProviderData->FavoriteNumber = AnalogData->FavoriteNumber;
    
    TvProviderData->UniqueId = AnalogData->UniqueId;
	

}

void CHsvEuropeInstallation_m_Priv::mCollectPresetProviderData(HsvPgdatPresetData *PresetData, HsvPgdatTvProviderBlobData *TvProviderData)
{
	TvProviderData->PresetNumber = PresetData->PresetNumber ;
	TvProviderData->OriginalNetworkId = PresetData->OriginalNetworkId ;
	TvProviderData->Tsid = PresetData->Tsid ;
	TvProviderData->ServiceId = PresetData->ServiceId ;
	TvProviderData->Frequency = PresetData->Frequency ;

	/*Private*/
	TvProviderData->AnalogTablePreset = PresetData->AnalogTablePreset ;
	TvProviderData->Type = PresetData->Type ;

}

void CHsvEuropeInstallation_m_Priv::mCollectFrequencyMapData (	HsvPgdatDigFreqMapData	*FreqData, HsvPgdatTvProviderBlobData *TvProviderData)
{

	HsvPgdatDigTSData			DigTsData;

    TvProviderData->OriginalNetworkId   = FreqData->OriginalNetworkId;
    TvProviderData->Tsid                = FreqData->Tsid;
    TvProviderData->Frequency           = FreqData->Frequency;
    TvProviderData->ModulationType      = FreqData->ModulationType;
    TvProviderData->SymbolRate          = FreqData->SymbolRate;
    TvProviderData->DecoderType         = FreqData->DecoderType;
    TvProviderData->Bandwidth         = FreqData->Bandwidth;
	TvProviderData->GuardInterval         = FreqData->GuardInterval;
	TvProviderData->BarkerMux			= 0;
	/*Get Barker mux status from TSTable*/
	
	DigTsData.Frequency = TvProviderData->Frequency;
	DigTsData.StreamPriority = HsvStreamPriorityHigh;
	
	if (pgdb_GetByKey(PTC_TABLE,&DigTsData) == TRUE)
	{
		TvProviderData->BarkerMux = DigTsData.BarkerMux;
	}
	else
	{
		DigTsData.Frequency = TvProviderData->Frequency;
		DigTsData.StreamPriority = HsvStreamPriorityLow;
		if (pgdb_GetByKey(PTC_TABLE,&DigTsData) == TRUE)
		{
			TvProviderData->BarkerMux = DigTsData.BarkerMux;		
		}
	}
	
}



void CHsvEuropeInstallation_m_Priv::pins_GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)
{
	HsvPgdatTvProviderBlobData		*TvProviderData = NULL;
	HsvPgdatPresetData				PresetData;
	HsvPgdatAnalogData				AnalogData;
	HsvPgdatDigServiceData			DigSrvcData;
	HsvPgdatDigTSData			DigTsData;
    HsvPgdatDigFreqMapData    Freqdat;
	
	//TraceNotice (m, " pins_GetTvProviderBlobDataByIndex for index %d ", Index);
	TvProviderData = (HsvPgdatTvProviderBlobData*)TvProviderBlobData;
	mInitializeTvProviderData(TvProviderData);

	/* Aneesh: TODO: Once completely moved to srtdb, remove the active database setting */
	pgdb_SelectActiveChannelDatabase(pgdb_TempDatabase);

	
	if(TSDataOnly)
	{
		if (TRUE == pgdb_GetByIndex(FREQMAP_TABLE,Index, (Address)&Freqdat))
		{
			mCollectFrequencyMapData(&Freqdat,TvProviderData);
		}
	}
	else if (TRUE == pgdb_GetByIndex(PRESET_TABLE,Index, (Address)&PresetData))
	{
		mCollectPresetProviderData(&PresetData,TvProviderData);
		if (IS_DIGITAL_PRESET(PresetData.Type))
		{
			//TraceNotice (m, "Digital Preset ");
			if(InsStatus.Mode == CAM_MODE){
				ASSIGN_CAM_SVC_FROM_PRESET(DigSrvcData,PresetData);
			}
			else{	
				ASSIGN_SVC_FROM_PRESET(DigSrvcData,PresetData);
			}
			if (pgdb_GetByKey(SERVICE_TABLE,&DigSrvcData) == TRUE)
			{
				mCollectDigSrvProviderData (&DigSrvcData, TvProviderData);
				DigTsData.Frequency = DigSrvcData.Frequency;
				DigTsData.StreamPriority = DigSrvcData.StreamPriority;
				if (pgdb_GetByKey(PTC_TABLE,&DigTsData) == TRUE)
				{
					mCollectDigTSProviderData(&DigTsData, TvProviderData);
				}
			}
			else
			{
				//TraceErr (m, "pgdb_GetByKey failed for Service Table ");
			}
		}
		else
		{
			//TraceNotice (m, "Analog Preset ");
			ASSIGN_ANALOG_KEYS(&AnalogData, &PresetData);
			if (pgdb_GetByKey(ANALOG_TABLE,&AnalogData) == TRUE)
			{
				mCollectAnalogProviderData (&AnalogData, TvProviderData);
			}
			else
			{
				//TraceErr (m, "pgdb_GetByKey failed for Analog Table ");
			}

		}
	}
	else 
	{
		//TraceErr (m, "pgdb_GetByIndex failed for Index %d ", Index);
	}
	
	/* Aneesh: TODO: Once completely moved to srtdb, remove the active database setting */
	//pgdb_SelectActiveChannelDatabase(pgdb_SqliteDatabase);
}

void CHsvEuropeInstallation_m_Priv::mAddPresetData(HsvPgdatTvProviderBlobData *TvpData)
{
	HsvPgdatPresetData				PresetData, tmp_preset;

#define NON_PRESET(item, type, bit, siz, def)
#define PRESET(item, type, bit, siz, def) PresetData.item = TvpData->item;

#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, preset, ana, srv, ts)      preset(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      PresetData.item = TvpData->item;
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)    
#define	TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_ANALOG_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_COMMON_VECTOR_ITEM
#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM


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

void CHsvEuropeInstallation_m_Priv::mAddAnalogData(HsvPgdatTvProviderBlobData *TvpData)
{

	HsvPgdatAnalogData		AnalogData, tmp_analog;

#define NON_ANALOG(item, type, bit, siz, def)
#define ANALOG(item, type, bit, siz, def) AnalogData.item = TvpData->item;

#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)      ana(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)      AnalogData.item = TvpData->item;
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)    
#define	TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_ANALOG_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_COMMON_VECTOR_ITEM
#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM


#undef ANALOG
#undef NON_ANALOG

	TraceNotice(m,"mAddAnalogData() Preset: %d", TvpData->AnalogTablePreset);
	/*Copy vector items*/
	memcpy ((void*)AnalogData.TxtPages,(void *)TvpData->TxtPages, 23*sizeof(Nat16));
	memcpy ((void*)AnalogData.ChannelName,(void *)TvpData->ChannelName,23*sizeof(Nat16));

	AnalogData.PresetNumber = TvpData->AnalogTablePreset;
	AnalogData.UniqueId = TvpData->UniqueId;
    AnalogData.Frequency = TvpData->Frequency;

	tmp_analog.PresetNumber = AnalogData.PresetNumber;
	if (TRUE == pgdb_GetByKey(ANALOG_TABLE,(Address)&tmp_analog))
	{
		pgdb_Update(ANALOG_TABLE,(Address)&AnalogData);
		//TraceNotice(m,"Updating the Analog Table from TVProvider data for Analog Preset :%d",AnalogData.PresetNumber);
	}
	else
	{
		pgdb_Add(ANALOG_TABLE,(Address)&AnalogData);
		//TraceNotice(m,"Adding the Analog Table from TVProvider data for Analog Preset :%d",AnalogData.PresetNumber);
	}
}


void CHsvEuropeInstallation_m_Priv::mAddDigSrvData(HsvPgdatTvProviderBlobData *TvpData)
{
	HsvPgdatDigServiceData			DigSrvcData, tmp_srvcdata;
	pgdb_Initialise(SERVICE_TABLE,&DigSrvcData);
	pgdb_Initialise(SERVICE_TABLE,&tmp_srvcdata);
	
#define NON_DIGSRVC(item, type, bit, siz, def)
#define DIGSRVC(item, type, bit, siz, def) DigSrvcData.item = TvpData->item;
	
#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)      srv(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     DigSrvcData.item = TvpData->item;
#define	TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)    
#define	TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_ANALOG_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_COMMON_VECTOR_ITEM
#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM
	
	
#undef DIGSRVC
#undef NON_DIGSRVC

	/*Copy vector items*/
	memcpy ((void*)DigSrvcData.TxtPages,(void *)TvpData->TxtPages, 23*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.ChannelName,(void *)TvpData->ChannelName,(MAXSERVICENAMELEN + 1)*sizeof(Nat16));

	memcpy ((void*)DigSrvcData.BrandIds,(void *)TvpData->BrandIds,23*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultipleLCN,(void *)TvpData->MultipleLCN,8*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultiplePreset,(void *)TvpData->MultiplePreset,8*sizeof(Nat16));
	memcpy ((void*)DigSrvcData.MultipleFavorite,(void *)TvpData->MultipleFavorite,8*sizeof(Nat8));

       //Based on Preset value, copy UniqueId to corresponding position in UniqueIds array
       mUpdateUniqueIds (&DigSrvcData, TvpData);

	DigSrvcData.HbbTvOption = TvpData->IntHbbTvOption;
	DigSrvcData.SrcambledStatus = TvpData->ScrambledStatus;
	
	/* Assign Keys */
	tmp_srvcdata.OriginalNetworkId = DigSrvcData.OriginalNetworkId;
	tmp_srvcdata.ServiceId = DigSrvcData.ServiceId;
	tmp_srvcdata.Frequency = DigSrvcData.Frequency;
	tmp_srvcdata.StreamPriority = DigSrvcData.StreamPriority;

	if (TRUE == pgdb_GetByKey(SERVICE_TABLE,(Address)&tmp_srvcdata))
	{
		pgdb_Update(SERVICE_TABLE,(Address)&DigSrvcData);
		TraceNotice(m,"Upadating the Service Table from TVProvider data [%d] [%d] [%d] [%d]",DigSrvcData.OriginalNetworkId,DigSrvcData.ServiceId,
			DigSrvcData.Frequency,DigSrvcData.StreamPriority);
		
	}
	else
	{
		pgdb_Add(SERVICE_TABLE,(Address)&DigSrvcData);
		TraceNotice(m,"Adding Service from TVProvider data [%d] [%d] [%d] [%d]",DigSrvcData.OriginalNetworkId,DigSrvcData.ServiceId,
			DigSrvcData.Frequency,DigSrvcData.StreamPriority);
	}
}


void CHsvEuropeInstallation_m_Priv::mAddDigTsData(HsvPgdatTvProviderBlobData *TvpData)
{

	HsvPgdatDigTSData			DigTsData, tmp_tsdata;

#define NON_DIGTS(item, type, bit, siz, def)
#define DIGTS(item, type, bit, siz, def) DigTsData.item = TvpData->item;
	
#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)      ts(item, type, bit, siz, def);
#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)     
#define	TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)      
#define	TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)     DigTsData.item = TvpData->item;
#define	TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)    
#define	TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)
#include "hsvpgdat_tvproviderblobdata.h"
#undef  TVPROVIDER_PRESET_ITEM
#undef  TVPROVIDER_DIGSRVC_ITEM
#undef TVPROVIDER_ANALOG_ITEM
#undef TVPROVIDER_COMMON_ITEM
#undef TVPROVIDER_DIGTS_ITEM
#undef TVPROVIDER_COMMON_VECTOR_ITEM
#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM
	
	
#undef DIGTS
#undef NON_DIGTS

	/* Assign Keys */
	tmp_tsdata.Frequency = DigTsData.Frequency;
	tmp_tsdata.StreamPriority = DigTsData.StreamPriority;

	if (TRUE == pgdb_GetByKey(PTC_TABLE,(Address)&tmp_tsdata))
	{
		pgdb_Update(PTC_TABLE,(Address)&DigTsData);
		//TraceNotice(m,"Upadating the TS Table from TVProvider data Freq: [%d] Streamprio: [%d] ",DigTsData.Frequency,DigTsData.StreamPriority);
	}
	else
	{
		pgdb_Add(PTC_TABLE,(Address)&DigTsData);
		//TraceNotice(m,"Adding the TS Table from TVProvider data Freq: [%d] Streamprio: [%d] ",DigTsData.Frequency,DigTsData.StreamPriority);
	}


}

void CHsvEuropeInstallation_m_Priv::mAddFreqMapData(HsvPgdatTvProviderBlobData *TvpData)
{
	HsvPgdatDigFreqMapData    freqdat;
    HsvPgdatDigFreqMapData    tmpfreqdat;
	int retval;

	freqdat.OriginalNetworkId	= TvpData->OriginalNetworkId;
	freqdat.Tsid				= TvpData->Tsid;
	freqdat.Frequency			= TvpData->Frequency;
	freqdat.ModulationType		= TvpData->ModulationType;
	freqdat.SymbolRate			= TvpData->SymbolRate;
	freqdat.DecoderType 		= TvpData->DecoderType;
	freqdat.Bandwidth			= TvpData->Bandwidth;
	freqdat.GuardInterval		= TvpData->GuardInterval;

    tmpfreqdat.OriginalNetworkId    = freqdat.OriginalNetworkId;
    tmpfreqdat.Tsid                 = freqdat.Tsid;

	if(pgdb_GetByKey(FREQMAP_TABLE, (Address )&tmpfreqdat))
	{
		retval = pgdb_Update(FREQMAP_TABLE, (Address )&freqdat);
		//TraceDebug(m,"Updating FreqMaptable %s %d retval %d", __FUNCTION__, __LINE__, retval);
	}
	else
	{
		retval = pgdb_Add( FREQMAP_TABLE, (Address )&freqdat);
		//TraceDebug(m,"Adding the FreqMapTable %s %d retval %d", __FUNCTION__, __LINE__, retval);
	}
}

int CHsvEuropeInstallation_m_Priv::pins_GetLastAnalogPresetNumber()
{
	int fiLastPresentNumber = 0;
	int dbindex = 0;
	int noOfAnaRecs = pgdb_GetNoRecords(ANALOG_TABLE);

	TraceNotice(m,"pins_GetLastAnalogPresetNumber(): Num of Rec.: %d", noOfAnaRecs);

	for(dbindex = 0; dbindex < noOfAnaRecs; ++dbindex)
	{
		HsvPgdatAnalogData anadat;

		if(pgdb_GetByIndex(ANALOG_TABLE, dbindex, (Address)&anadat))
		{
			//TraceNotice(m,"pins_GetLastAnalogPresetNumber(): Preset: %d", anadat.PresetNumber);
			if(anadat.PresetNumber > fiLastPresentNumber)
				fiLastPresentNumber = anadat.PresetNumber;
		}
	}

	TraceNotice(m,"pins_GetLastAnalogPresetNumber(): last Preset: %d", fiLastPresentNumber);

	return fiLastPresentNumber;
}

void CHsvEuropeInstallation_m_Priv::pins_AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear)
{
	if(Clear)
	{
		TraceNotice(m,"pins_AddTvpData clear");
		pgdb_SelectActiveChannelDatabase (pgdb_TempDatabase);
		pgdb_ClearTable(pgdb_GetCurrentTable());
		//TraceNotice(m,"RAM copy cleared");
	}
    else if((TvpData->ServiceId == 0) && (IS_DIGITAL_PRESET(TvpData->Type)))/*Service Id '0' is used to identify FreqMapTable*/
	{
		TraceNotice(m,"pins_AddTvpData Freq Map table: onid: [%d] tsid: [%d]  Freq: [%d] ",TvpData->OriginalNetworkId,TvpData->Tsid,TvpData->Frequency);
		mAddFreqMapData(TvpData);
	}
	else
	{
		TraceNotice(m,"pins_AddTvpData Preset: [%d] onid: [%d] service: [%d] Freq: [%d] Streamprio: [%d] type: [%d]",TvpData->PresetNumber,TvpData->OriginalNetworkId,TvpData->ServiceId,TvpData->Frequency,TvpData->StreamPriority,TvpData->Type);
		
		mAddPresetData(TvpData);
		if (IS_DIGITAL_PRESET(TvpData->Type))
		{
			TraceNotice(m,"Digital channel");
			mAddDigSrvData(TvpData);
			mAddDigTsData(TvpData);
		}
		else
		{
			TraceNotice(m,"Analog channel");
			mAddAnalogData(TvpData);
		}

	}

}


void CHsvEuropeInstallation_m_Priv::mGetUniqueIdFromPresetNumber (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData)
{
    int loopCount = 0;
    
    if (eurdiv_MultipleLCNSupported ())
    { 
        for (loopCount = 0; loopCount < MAX_NUM_PRESET_ENTRY; ++loopCount)
        {            
                if (TvpData->PresetNumber == TvpData->MultiplePreset[loopCount]) 
                {
                   // TraceNotice(m,"[%s] [%d] Preset : %d, MultiplePreset[%d] : %d, UniqueId %d \n", __FUNCTION__, __LINE__, TvpData->PresetNumber, 
                           //                 loopCount, TvpData->MultiplePreset[loopCount], DigSrvcData->UniqueIds[loopCount]);   
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
         //                   __FUNCTION__, __LINE__, DigSrvcData->OriginalNetworkId, DigSrvcData->ServiceId, DigSrvcData->Frequency,
        //                    DigSrvcData->StreamPriority, TvpData->PresetNumber, TvpData->UniqueId);
}


void CHsvEuropeInstallation_m_Priv::mUpdateUniqueIds (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData)
{
    int arrayIndex = 0;
    int loopCount = 0;
    HsvPgdatDigServiceData tempSvcData;

    /* Assign Keys */
    tempSvcData.OriginalNetworkId = DigSrvcData->OriginalNetworkId;
    tempSvcData.ServiceId = DigSrvcData->ServiceId;
    tempSvcData.Frequency = DigSrvcData->Frequency;
    tempSvcData.StreamPriority = DigSrvcData->StreamPriority;
    
    if (TRUE == pgdb_GetByKey (SERVICE_TABLE, (Address) &tempSvcData))
    {
        //Service already exists in SERVICE_TABLE; So find the arrayIndex for UniqueId based on preset value
        if (eurdiv_MultipleLCNSupported ())
        {
            for (loopCount = 0; loopCount < MAX_NUM_PRESET_ENTRY; ++loopCount)
            {
                if (TvpData->PresetNumber == TvpData->MultiplePreset[loopCount]) 
                {
                //    TraceNotice(m,"[%s] [%d] Preset : %d, MultiplePreset[%d] : %d\n", __FUNCTION__, __LINE__, TvpData->PresetNumber, loopCount, TvpData->MultiplePreset[loopCount]);   
                    arrayIndex = loopCount;
                    break;
                }
            }
        }
    }
    else
    {
        //No entry exists in SERVICE_TABLE. So update the UniqueId in the 0th index
        arrayIndex = 0;
    }
   // TraceNotice(m,"[%s] [%d] : Service (OnId, SvcId, Freq, StreamPriority, PresetNo) {%d %d %d %d %d}, UniqueId %d, arrayIndex %d  \n", 
              //              __FUNCTION__, __LINE__, DigSrvcData->OriginalNetworkId, DigSrvcData->ServiceId, DigSrvcData->Frequency,
              //              DigSrvcData->StreamPriority, TvpData->PresetNumber, TvpData->UniqueId, arrayIndex);

    //Copy UniqueIds array from DB to DigSrvcData; This is required for TV Bootup case.
    for (loopCount = arrayIndex - 1; loopCount >= 0; --loopCount)
    {
        DigSrvcData->UniqueIds[loopCount] = tempSvcData.UniqueIds[loopCount];
    }

    DigSrvcData->UniqueIds[arrayIndex] = TvpData->UniqueId;
}


void CHsvEuropeInstallation_m_Priv::mSyncUniqueIdToDigitalServiceTable (HsvPgdatTvProviderBlobData *tvpData)
{
    HsvPgdatDigServiceData DigSrvcData;
    pgdb_Initialise (SERVICE_TABLE, &DigSrvcData);

    //Assign Keys
    DigSrvcData.OriginalNetworkId = tvpData->OriginalNetworkId;
    DigSrvcData.ServiceId = tvpData->ServiceId;
    DigSrvcData.Frequency = tvpData->Frequency;
	if(InsStatus.Mode == CAM_MODE){
		DigSrvcData.LCN = tvpData->PresetNumber;
	}
	else{
    	DigSrvcData.StreamPriority = tvpData->StreamPriority;
	}

    if (TRUE == pgdb_GetByKey (SERVICE_TABLE, (Address) &DigSrvcData))
    {
        //Based on Preset value, copy UniqueId to corresponding position in UniqueIds array
        mUpdateUniqueIds (&DigSrvcData, tvpData);
        
        pgdb_Update(SERVICE_TABLE, (Address)&DigSrvcData);
       // TraceNotice(m,"Upadating the Service Table from TVProvider data [%d] [%d] [%d] [%d]", DigSrvcData.OriginalNetworkId,
       //                         DigSrvcData.ServiceId, DigSrvcData.Frequency, DigSrvcData.StreamPriority);

    }
    else
    {
        TraceErr (m,  "Error : Failed to find entry in SERVICE_TABLE for updating UniqueId ");
    }
}


void CHsvEuropeInstallation_m_Priv::mSyncUniqueIdToAnalogTable (HsvPgdatTvProviderBlobData *TvpData)
{
    HsvPgdatAnalogData	analogData;

    // Assign Keys
    analogData.PresetNumber = TvpData->AnalogTablePreset;

    if (TRUE == pgdb_GetByKey (ANALOG_TABLE, (Address) &analogData))
    {
        analogData.UniqueId = TvpData->UniqueId;
        pgdb_Update (ANALOG_TABLE, (Address) &analogData);
      //  TraceNotice (m, "Updating the Analog Table from TVProvider data for Analog Preset :%d", analogData.PresetNumber);
    }
    else
    {
    	TraceErr (m,  "Error : Failed to find entry in ANALOG_TABLE for updating UniqueId ");
    }
}


void CHsvEuropeInstallation_m_Priv::pins_SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData)
{
    if (IS_DIGITAL_PRESET (TvpData->Type))
    {
    	mSyncUniqueIdToDigitalServiceTable (TvpData);
    }
    else
    {
    	mSyncUniqueIdToAnalogTable (TvpData);
    }	
}

Bool CHsvEuropeInstallation_m_Priv::mIsCanalDigitalorYouSeeOperatorSupported(void)
{
	Bool retVal = FALSE;
	
	int NetworkOperator = hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeNetworkOperator);
	if(((((InsStatus.Country == cids_CountryNorway) || (InsStatus.Country == cids_CountrySweden)) && (NetworkOperator == rins_CanalDigital)) ||
        			((InsStatus.Country == cids_CountryDenmark) &&  (NetworkOperator == rins_YouSee))) && (rins_QuickScan == hsvdvbcins_ins_GetAttribute(AUTO_MODE, rins_AttributeScanMode)))
		{
			retVal = TRUE;
		}
	return retVal;
}



	/*** TVPROVIDER IMPLEMENTATION END ***/
