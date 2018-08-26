/*
 *  Copyright(C) 2002 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.      
 *                                                                  
 *############################################################
 */
/*!
 *     \file          hsvcanaldigital_mBackground.c
 *
 *     \brief         -
 *
 */
/*----------------------------------------------------------*
 *
 *     %version:       TVG_FusionPPV2_7.1.2 %
 *     %date_created:  Fri Nov 30 17:18:42 2012 %
 *     %date_modified: Tue Oct 28 19:17:58 2008 %
 *     %derived_by:    mahesh  %
 *
 *
 *############################################################
 */
#include "_hsvcanaldigital_mBackground.h"

TRACESYMBOL(m, "dvb/installation/hsvcanaldigital_mBackground")

#include "hsvcanaldigital.h"
//#include "hsvcanaldigital_mCommonData.c"



#ifndef __cplusplus

#else

#endif









InstStatus CHsvCanalDigitalInstallation_mBackground_Priv::s__mInstStatus;





t_CanalDigitalCableDSDesc CHsvCanalDigitalInstallation_mBackground_Priv::s__mCableDSDesc;

Nat16 CHsvCanalDigitalInstallation_mBackground_Priv::s__mBarkerMuxONID = 0xFFFF,CHsvCanalDigitalInstallation_mBackground_Priv::s__mBarkerMuxTSID = 0xFFFF;



/* static functions */







Bool CHsvCanalDigitalInstallation_mBackground_Priv::s__VersionUpdateNeeded = FALSE;


Nat16 CHsvCanalDigitalInstallation_mBackground_Priv:: s__OnId = 0xFFFF;
Nat16 CHsvCanalDigitalInstallation_mBackground_Priv:: s__SrvId = 0xFFFF;
Nat16 CHsvCanalDigitalInstallation_mBackground_Priv:: s__TsId = 0xFFFF;
Nat16 CHsvCanalDigitalInstallation_mBackground_Priv:: s__CachedPresetnumber = 0xFFFF;
Nat32 CHsvCanalDigitalInstallation_mBackground_Priv:: s__CachedFrequency = 0;

Bool CHsvCanalDigitalInstallation_mBackground_Priv:: s__mServiceUpdateInProgress = FALSE;
Bool CHsvCanalDigitalInstallation_mBackground_Priv:: s__mBackgroundUpdateInProgress = FALSE;

Bool CHsvCanalDigitalInstallation_mBackground_Priv::s__mServiceNameUpdated = FALSE;
Bool CHsvCanalDigitalInstallation_mBackground_Priv::s__mNitUpdatedAlsoHappened = FALSE;





const FunctionVoid CHsvCanalDigitalInstallation_mBackground_Priv::EventActionMatrix[][StMax] =
{
	/* 								StIdle,                		StNITAcquistion,      			StSorting     */
    /* EvDataAvailable */     {  FNADDR(FuncStartInstallation),	NULL,                 			NULL          },
    /* EvStop */              {  NULL,                  		FNADDR(FuncStopInstallation), 	FNADDR(FuncStopInstallation)	},
    /* EvComplete */          {  FNADDR(FuncComplete),       	NULL,                 			FNADDR(FuncComplete) },
	/* EvSdtOtherTimeout */	  {  FNADDR(FuncSdtOtherComplete),	NULL,							NULL		}
};


/* static variables */
Bool CHsvCanalDigitalInstallation_mBackground_Priv::s__mActive,CHsvCanalDigitalInstallation_mBackground_Priv::s__mDirtyBit,CHsvCanalDigitalInstallation_mBackground_Priv::s__mDataAcquistion;
Bool CHsvCanalDigitalInstallation_mBackground_Priv::s__mPresetChanged,CHsvCanalDigitalInstallation_mBackground_Priv::s__mLowestPreset;


Pump CHsvCanalDigitalInstallation_mBackground_Priv::s__mInstallPump;


void CHsvCanalDigitalInstallation_mBackground_Priv::mPumpHandler(int event, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"@ %d event %d state %d - %s\n", __LINE__, event, mInstStatus.State, (EventActionMatrix[event][mInstStatus.State] == NULL)?"Ignored":"Handled");
    if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State) && BACKGROUND_INSTALL)
    {
        TraceDebug(m,"@ %d event %d state %d - %s\n", __LINE__, event, mInstStatus.State, (EventActionMatrix[event][mInstStatus.State] == NULL)?"Ignored":"Handled");
        if(EventActionMatrix[event][mInstStatus.State] != NULL)
        {
            FPCALL(EventActionMatrix[event][mInstStatus.State])();
        }
    }
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::FuncStartInstallation(void)
{
    HsvPgdatDigTSData tsdata;
    HsvSource  Src;
    HsvChannel Channel;
   
	HsvPgdatPresetData	PresetData,temp_PresetData;
	
	HsvPgdatDigServiceData  svcdat_temp;

	
	/* Issue reported : "Scrambled channel message on 9.32.46". Root cause for this issue is SDT Other version check. Sometimes if SDT Other is not present (when tried installation)
		this further leads to unnecessary background updates. To overcome this issue, not checking for SDT version change. (As installation is fully based on SLD in NIT) */
    int /*CurrentSDTVersion = 0, */CurrentNITVersion = 0;
	HsvChannel channel;
	
    int NoOfRecords = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_Preset);

	
	
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    
    mInitialise();

    SET_BACKGROUND_STATE(StNITAcquistion);
    mInstStatus.TargeNITFound = mAcquireValidNit();
    
    pgsel_GetActualCurrentProgram(HsvMain,&Src, &Channel);
	PresetData.PresetNumber = Channel.Channel.Digit;
	CachedPresetnumber = Channel.Channel.Digit;
	
	if (pgdb_GetByKey(PRESETTABLE, &PresetData) == TRUE)
	{ 
    	CachedFrequency = PresetData.Frequency;
		OnId = PresetData.OriginalNetworkId;
		SrvId = PresetData.ServiceId;
		TsId = PresetData.Tsid;
		TraceNotice (m,"Frequency %d ", CachedFrequency);
	}

	/* Instead of initializing with 0, initializing with current values. This will avoid 
		any unwanted background trigger just in case the SQLITE queries fail */
	CurrentNITVersion = mGetVersion(NIT_DATA);

    tsdata.Frequency = CachedFrequency;
    tsdata.StreamPriority = HsvStreamPriorityHigh;
    if(pgdb_GetByKey( PTC_TABLE, (Address )&tsdata) == TRUE)
    {
        CurrentNITVersion = tsdata.NITVersion;
    }
	else
	{
		TraceNotice (m, "TSData query failed for Frequency %d", CachedFrequency);
	}

    TraceDebug(m,"%s %d CurrentFreq %lu CurrentNITVersionInDb %d NITVersionFromDmx %d\n", __FUNCTION__, __LINE__, CachedFrequency, CurrentNITVersion, mGetVersion(NIT_DATA));
    if( VersionUpdateNeeded || ((mGetVersion(NIT_DATA) != 0xFF) && (mGetVersion(NIT_DATA) != CurrentNITVersion)) )
    {
		mBackgroundUpdateInProgress = TRUE;
	    VersionUpdateNeeded = FALSE;
		 TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
        if(mInstStatus.TargeNITFound == FALSE)
        {
            /* No proper data available, need not proceed further, so no updates done here */
            TraceDebug(m,"%s %d No proper data available\n", __FUNCTION__, __LINE__);
            mInitialise();
        }
        
        else
        {
            rtk_TskBoostWatchdog(60);
            /* Target NIT available, so proceed with updation of network on fly */
			insN_OnEvent(insN_EventInstallationStarted, CURRENT_MODE);
			pgdb_EnableAutoCommit(FALSE);
			pgdb_MasterEnableEvents(TRUE);
			/* ANEESH: Clear TempDatabase
				Do sync from SQLITE to TempDatabase. */
			//mClearAndSyncDatabase ();			
            idataacq_AcquireData();
            idataacq_DeleteServices();
			SET_BACKGROUND_STATE(StSorting);
			/* finished with data acquistion go to sorting */
			sort_SortAll();
			
        }
    }
    else
    {
        TraceDebug(m,"%s %d no version change\n", __FUNCTION__, __LINE__);
            mInitialise();
    }
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::FuncStopInstallation(void)
{
    mInitialise();
	pgdb_EnableAutoCommit(TRUE);
	pgdb_MasterEnableEvents(FALSE);
    insN_OnEvent(insN_EventNetworkUpdateNotDetected, CURRENT_MODE);
	insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::FuncComplete(void)
{
	/*If sorting was triggered in previous zap then still sort compelted event need to be handled*/
	if((mInstStatus.State == StSorting) || ((mInstStatus.State == StIdle) && (mActive == TRUE)))
	{
		/* ANEESH: Do database sync back to SQLITE here */
		//mDeleteServicesRemoved ();
		//mAddOrUpdateServiceRecords ();
		tuneToLowestPreset();
	    mInitialise();
		mNitUpdatedAlsoHappened = TRUE; /* NIT Update already happenend. So no need to update the major version for Name Update */
		
		pgdb_CommitTable(pgdb_GetCurrentTable());
		pgdb_EnableAutoCommit(TRUE);
		pgdb_MasterEnableEvents(FALSE);
	    insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
		mBackgroundUpdateInProgress = FALSE;
		/* Enabling the SDT other filter */
	}
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::FuncSdtOtherComplete(void)
{
	/* Cross check any change happened in Service Names. If yes, trigger major version update */
	if (BACKGROUND_INSTALL && eurdiv_SupportSDTOtherInBackgroundInstallation() && (mServiceNameUpdated == TRUE))
	{
		if (mNitUpdatedAlsoHappened == FALSE)
		{
			insN_OnEvent(insN_EventTelenetMajorVersionUpdate, TRUE);
		TraceNotice (m, " Service Name update happened for Telenet. Sending notification to increment major version ");
		}
		else
		{
			TraceNotice (m, " Service Name update happened for Telenet. But a network update also happened. Hence ignoring it.. ");
		}
		mServiceNameUpdated = FALSE;
		mNitUpdatedAlsoHappened = FALSE;
	}
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::mInitialise(void)
{
    SET_BACKGROUND_STATE(StIdle);
    mInstStatus.TargeNITFound = mInstStatus.SDTOtherScan = FALSE;
    mInstStatus.TargetNITType = rins_NitNone; 
    mInstStatus.TargetNITValue = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkId);
    mDirtyBit = FALSE;
	mPresetChanged = FALSE;
	mLowestPreset = FALSE;
    mDataAcquistion = NO_DATA;

    idataacq_Initialise();
    memset((Address)(&mCableDSDesc), 0, sizeof(mCableDSDesc));

    TraceDebug(m,"%s %d TargetNITValue %d\n", __FUNCTION__, __LINE__, mInstStatus.TargetNITValue);
}

inline Bool CHsvCanalDigitalInstallation_mBackground_Priv::mAcquireValidNit(void)
{
    int hsvspid = 0;
    Bool retval = FALSE;
    Nat16 NetworkId = 0xFFFF;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit)  NitOtherData;

	mInstStatus.TargetNITType = rins_NitNone;
    if( strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkId) )
    {
        TraceDebug(m,"%s %d Actual NetworkId %d mInstStatus.TargetNITValue %d\n", __FUNCTION__, __LINE__, NetworkId,mInstStatus.TargetNITValue);

        if(mInstStatus.TargetNITValue == NetworkId)
        {
            hsvspid = HSVSPID(ActualCableDS, dvb, nit);
            mInstStatus.TargetNITType = rins_NitActual;
        }
    }

    if(mInstStatus.TargetNITType == rins_NitNone)   /* means NIT Actual is not of entered value */
    {
        if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), mInstStatus.TargetNITValue, 0, 0, &NitOtherData))
        {
            TraceDebug(m,"%s %d NIT other present for entered NID %d\n", __FUNCTION__, __LINE__, NitOtherData.NetworkId);

            hsvspid = HSVSPID(OtherCableDS, dvb, nit);
            mInstStatus.TargetNITType = rins_NitOther;
        }
    }

    retval = (mInstStatus.TargetNITType == rins_NitNone)? FALSE: TRUE;

    if(retval == TRUE)
    {
        mDirtyBit = TRUE;
        retval = mLoadCDSDFromStrapi(hsvspid);
        if(retval)
        {
            /* Acquire Service List Data before it goes away */
            idataacq_AcquireLCNData();

            idataacq_AcquireServiceListData();
        }
    }

    TraceDebug(m,"%s %d retval %d\n",__FUNCTION__, __LINE__, retval);
    return retval;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::mClearAndSyncDatabase (void)
{	
	int FromDatabaseId = pgdb_SqliteDatabase,  ToDatabaseId = pgdb_TempDatabase;
	int DatabaseToBeSynced [MAX_DATABASE_SYNC] = {PTC_TABLE,SERVICE_TABLE, PRESETTABLE,FREQMAP_TABLE, ANALOG_TABLE};
	int TotalNumberOfEntries =0, count = 0, Index = 0;
	int RetryCount = 0;
	HsvPgdatDigTSData		digTsData;
	HsvPgdatDigServiceData	digSrvData;
	HsvPgdatPresetData		presetData;
	HsvPgdatDigFreqMapData	freqMapData;
	HsvPgdatAnalogData		analogData;

	pgdb_SelectActiveChannelDatabase (ToDatabaseId);
	pgdb_ClearTable(pgdb_GetCurrentTable());
	pgdb_SelectActiveChannelDatabase(FromDatabaseId);
	
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[0]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,digTsData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[1]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,digSrvData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[2]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,presetData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[3]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,freqMapData)
	PERFORM_DATABASE_SYNC((DatabaseToBeSynced[4]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,analogData)

	pgdb_SelectActiveChannelDatabase (ToDatabaseId);
}

void CHsvCanalDigitalInstallation_mBackground_Priv::mDeleteServicesRemoved (void)
{
	/* This function will iterate through the SQLITE database and check if same keys are there
		in TempDatabase. If not found, they got deleted during background installation. So remove those
		entries from SQLITE */
	int DatabaseToBeSynced [MAX_DATABASE_SYNC] = {PTC_TABLE,SERVICE_TABLE, PRESETTABLE,FREQMAP_TABLE, ANALOG_TABLE};
	int		NumRecords = 0, count = 0;
	HsvPgdatDigTSData		digTsData, tempDigTsData;
	HsvPgdatDigServiceData	digSrvData, tempDigSrvData;
	HsvPgdatPresetData		presetData, tempPresetData;
	HsvPgdatDigFreqMapData	freqMapData, tempFreqMapData;
	HsvPgdatAnalogData		analogData, tempAnalogData;

	
	PERFORM_REMOVEDSVCDELETION(DatabaseToBeSynced[0],pgdb_SqliteDatabase,pgdb_TempDatabase,count,NumRecords,digTsData,tempDigTsData)
	PERFORM_REMOVEDSVCDELETION(DatabaseToBeSynced[1],pgdb_SqliteDatabase,pgdb_TempDatabase,count,NumRecords,digSrvData,tempDigSrvData)
	PERFORM_REMOVEDSVCDELETION(DatabaseToBeSynced[2],pgdb_SqliteDatabase,pgdb_TempDatabase,count,NumRecords,presetData,tempPresetData)
	PERFORM_REMOVEDSVCDELETION(DatabaseToBeSynced[3],pgdb_SqliteDatabase,pgdb_TempDatabase,count,NumRecords,freqMapData,tempFreqMapData)
	PERFORM_REMOVEDSVCDELETION(DatabaseToBeSynced[4],pgdb_SqliteDatabase,pgdb_TempDatabase,count,NumRecords,analogData,tempAnalogData)
	
}

void CHsvCanalDigitalInstallation_mBackground_Priv::mAddOrUpdateServiceRecords (void)
{
	int FromDatabaseId = pgdb_TempDatabase,  ToDatabaseId = pgdb_SqliteDatabase;
	int DatabaseToBeSynced [MAX_DATABASE_SYNC] = {PTC_TABLE,SERVICE_TABLE, PRESETTABLE,FREQMAP_TABLE, ANALOG_TABLE};
	int TotalNumberOfEntries =0, count = 0, Index = 0;
	HsvPgdatDigTSData		digTsData, tempDigTsData;
	HsvPgdatDigServiceData	digSrvData, tempDigSrvData;
	HsvPgdatPresetData		presetData, tempPresetData;
	HsvPgdatDigFreqMapData	freqMapData, tempFreqMapData;
	HsvPgdatAnalogData		analogData, tempAnalogData;

/*
	pgdb_SelectActiveChannelDatabase (ToDatabaseId);
	pgdb_ClearTable(pgdb_GetCurrentTable());
	pgdb_SelectActiveChannelDatabase(FromDatabaseId);
*/
	
	PERFORM_DATABASE_ADDUPDATE((DatabaseToBeSynced[0]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,digTsData, tempDigTsData)
	PERFORM_DATABASE_ADDUPDATE((DatabaseToBeSynced[1]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,digSrvData, tempDigSrvData)
	PERFORM_DATABASE_ADDUPDATE((DatabaseToBeSynced[2]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,presetData, tempPresetData)
	PERFORM_DATABASE_ADDUPDATE((DatabaseToBeSynced[3]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,freqMapData, tempFreqMapData)
	PERFORM_DATABASE_ADDUPDATE((DatabaseToBeSynced[4]), FromDatabaseId,ToDatabaseId,Index, TotalNumberOfEntries,analogData, tempAnalogData)
	pgdb_SelectActiveChannelDatabase (ToDatabaseId);
}




void CHsvCanalDigitalInstallation_mBackground_Priv::mAssignPgdbKeys (int TableId, Address Data, Address TempData)
{
	if(TableId == PTC_TABLE)
	{
		((HsvPgdatDigTSData*)Data)->Frequency = ((HsvPgdatDigTSData*)TempData)->Frequency;
		((HsvPgdatDigTSData*)Data)->StreamPriority = ((HsvPgdatDigTSData*)TempData)->StreamPriority;
	}
	else if (TableId == SERVICE_TABLE)
	{
		((HsvPgdatDigServiceData*)Data)->OriginalNetworkId = ((HsvPgdatDigServiceData*)TempData)->OriginalNetworkId;
		((HsvPgdatDigServiceData*)Data)->ServiceId = ((HsvPgdatDigServiceData*)TempData)->ServiceId;
		((HsvPgdatDigServiceData*)Data)->Frequency = ((HsvPgdatDigServiceData*)TempData)->Frequency;
		((HsvPgdatDigServiceData*)Data)->StreamPriority = ((HsvPgdatDigServiceData*)TempData)->StreamPriority;
	}
	else if (TableId == PRESETTABLE)
	{
		((HsvPgdatPresetData*)Data)->PresetNumber = ((HsvPgdatPresetData*)TempData)->PresetNumber;
	}
	else if (TableId == FREQMAP_TABLE)
	{
		((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId = ((HsvPgdatDigFreqMapData*)TempData)->OriginalNetworkId;
		((HsvPgdatDigFreqMapData*)Data)->Tsid = ((HsvPgdatDigFreqMapData*)TempData)->Tsid;
	}
	else if (TableId == ANALOG_TABLE)
	{
		((HsvPgdatAnalogData*)Data)->PresetNumber = ((HsvPgdatAnalogData*)TempData)->PresetNumber;
	}
}

Nat8 CHsvCanalDigitalInstallation_mBackground_Priv::mGetVersion(int TableData)
{
    Nat8 retval = 0xFF;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) NIDInfo;

    if(TableData == NIT_DATA)
    {
        if(mInstStatus.TargetNITType == rins_NitOther)
        {
            if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), mInstStatus.TargetNITValue, 0, 0, (void*) (&NIDInfo)))
            {
                retval = NIDInfo.VersionNumber;
            }
        }
        else 
        {
            strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (Address)(&retval));
        }
    }
    else
    {
        strapi_GetByKey(HsvMain, HSVSPID(ActualTsVersionNo, dvb, sdt), 0, 0, 0, &retval);
    }
    
    TraceDebug(m,"%s %d NetworkId %d VersionNumber : %d \n",__FUNCTION__,__LINE__, mInstStatus.TargetNITValue, retval);
    return retval;
}
void CHsvCanalDigitalInstallation_mBackground_Priv::ena_Enable(void)
{
    TraceDebug(m,"%s %d mActive %d\n", __FUNCTION__, __LINE__, mActive);
    mActive = TRUE;
	mInstStatus.TargetNITValue = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkId);
	mServiceUpdateInProgress = FALSE;
	idataacq_Enable();
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ena_Disable(void)
{
    TraceDebug(m,"%s %d mActive %d\n", __FUNCTION__, __LINE__, mActive);
    mActive = FALSE;
	if(mServiceUpdateInProgress == TRUE)
	{
		mServiceUpdateInProgress = FALSE;
		insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);	
	}
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ibckgpow_Init(void)
{
    mInstallPump = pmp_PmpCreateEx(pen_PumpEngine, mPumpHandler, TRUE, "hsvcanaldigital_mBackground");
    VersionUpdateNeeded = FALSE;
    mInitialise();
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ibckgctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(dmx);
    TraceDebug(m,"%s %d mActive %d BACKGROUND_INSTALL %d eventid %d value %d mDirtyBit %d\n", __FUNCTION__, __LINE__, mActive, BACKGROUND_INSTALL, eventid, value, mDirtyBit);
    if(mActive && BACKGROUND_INSTALL)
    {
        if( (eventid == ibckgctrlN_StoppedCollection) && (mDirtyBit == FALSE) )
        {
            mInitialise();
        }
    }
}

int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_ZiggoGetSDTType(Nat16 Frequency)
{
    return mGetSDTType(Frequency);
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    mGetPTCInfo(ptc, Onid, Tsid);
}

void CHsvCanalDigitalInstallation_mBackground_Priv::sortN_OnEvent(int eventid, int value)
{
    UNUSED(value);
    TraceDebug(m,"%s %d eventid %d\n", __FUNCTION__, __LINE__, eventid);
    if(eventid == sortN_EventSortComplete)
    {
        pmp_PmpSend(mInstallPump, EvComplete, (Nat32)NULL);
    }
}

#ifndef __cplusplus

void CHsvCanalDigitalInstallation_mBackground_Priv::plfresN_OnResourceLost( Nat32 resources )
{
    TraceDebug(m,"%s %d resources %ld\n", __FUNCTION__, __LINE__, resources);
    if(resources & plfres_Frontend)
    {
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
}
#endif


void CHsvCanalDigitalInstallation_mBackground_Priv::strapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    Bool UpdateInstallReq = FALSE;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) NIDInfo;
	HsvChannel svcChannel;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	Nat16	ChannelName[33] = {0};
	int Size = (eurdiv_ChannelNameLength - 1);
	//TraceNotice(m,"[%s] [%d]",__FUNCTION__,__LINE__);
    if(mActive && BACKGROUND_INSTALL)
    {
    	
        switch(spid)
        {
        	
            case HSVSPID(ActualCableDS, dvb, nit):
                if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, (void*) (&NIDInfo)))
            {
            	
                if(mInstStatus.TargetNITValue == NIDInfo.NetworkId)
                {
                	
                    UpdateInstallReq = TRUE;
                }
            }
                break;
            case HSVSPID(OtherCableDS, dvb, nit):
               	if(mInstStatus.TargetNITValue == key3)
            {
            	
                UpdateInstallReq = TRUE;
            }
                break;
            case HSVSPID(ActualTSService, dvb, sdt):
				{
						
					if(TRUE == strapi_GetByKey(dest, spid, key1, key2, key3, &service))
					{
						
						int ret = pgdat_GetDigitalChannel(&svcChannel,key1,key3, key2, 0);
						if(chanret_Ok == ret)
						{
						
							ret = pgdat_GetChannelDataString(svcChannel, pgdat_StringChannelName, ChannelName, Size);
							if ( (chanret_Ok == ret) && (mCompareUnicodeString(service.ServiceName, ChannelName) == FALSE) )
							{
								if(mServiceUpdateInProgress == FALSE)
								{
									mServiceUpdateInProgress = TRUE;
									insN_OnEvent(insN_EventInstallationStarted, CURRENT_MODE);
									TraceNotice(m,"%s: %d: Service Name Update Started", __FUNCTION__,__LINE__);
								}
								ret = pgdat_StoreChannelDataString(svcChannel, pgdat_StringChannelName, service.ServiceName, eurdiv_ChannelNameLength);
							}
						}
						
					}
				}
                break;
			case HSVSPID(OtherTSService, dvb, sdt):
				if (mActive && (mBackgroundUpdateInProgress == FALSE))
				{
					HandleTelenetSdtOtherNameUpdate (dest, spid, key1, key2, key3, 0);
				}
				break;
            default:
                break;
        }
        if(UpdateInstallReq)
        {
        	//TraceNotice(m,"[%s] [%d]",__FUNCTION__,__LINE__);
            pmp_PmpSendAfter(mInstallPump, EvDataAvailable, (Nat32)NULL, DATA_TIMEOUT);
        }
    }
    UNUSED(dest);
    UNUSED(key2);
    UNUSED(key1);
}

Bool CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetAltTSValues(Nat16* ONID, Nat16* TSID)
{
    UNUSED(ONID);
    UNUSED(TSID);
    return FALSE;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetTargetNitType(Nat16* NetworkId)
{
    *NetworkId = mInstStatus.TargetNITValue;

    TraceDebug(m,"%s %d TargetNITValue %d TargetNITType %d\n", __FUNCTION__, __LINE__, mInstStatus.TargetNITValue, mInstStatus.TargetNITType);
    return mInstStatus.TargetNITType;
}

FResult CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_StopInstallation(void)
{ 
    TraceDebug(m,"%s %d mInstStatus.State %d\n", __FUNCTION__, __LINE__, mInstStatus.State);
    pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);

    return 0;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ibckgpow_TurnOn(void)
{ }
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckgpow_TurnOff(void)
{ }
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_Initialise()
{ }
FResult CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_StartInstallation(int source, int ptc, int mode)
{ 
    UNUSED(source);
    UNUSED(ptc);
    UNUSED(mode);
    return 0; 
}
FResult CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_StartDigitalScan(void)
{ return 0; }
FResult CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_StopDigitalScan (void)
{ return 0; }
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetNoOfPass(void)
{ return 0; }
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetCurrentPass ( void )
{ return 0; }
FResult CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetCurrentState()
{ return 0; }
Bool CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ 
    UNUSED(ONID);
    UNUSED(TSID);
    return 0; 
}    
HsvStreamPriority CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_SetStreamPriority (HsvStreamPriority prio)
{
    UNUSED(prio);
}
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_SyncComplete(void)
{ }
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_ClearCache(void)
{ }
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetPLPIds(int *PLPIds)
{ 
    UNUSED(PLPIds);
    return 0; 
}
int CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetSDTType()
{ return 0; }
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetPTCInfo(HsvInstallationPTC *ptc)
{ UNUSED(ptc); }
void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{
    UNUSED(ONID);
    UNUSED(TSID);
}

Bool CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_ZiggoNetworkDataSet(Bool ActionValue)
{
    UNUSED(ActionValue);
    return FALSE;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::ibckg_ClearPersistent()
{
    
}
Bool CHsvCanalDigitalInstallation_mBackground_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;
    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}
	return retval;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::strapiN_OnCompleted         ( HsvDestination dest, int spid)
{

    if(mActive && BACKGROUND_INSTALL)
    {
        switch(spid)
        {
		case HSVSPID(ActualTSService, dvb, sdt):
			{
				if(mServiceUpdateInProgress == TRUE)
				{
					mServiceUpdateInProgress = FALSE;
					insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
					TraceNotice(m,"%s: %d: Service Name Update Completed", __FUNCTION__,__LINE__);
				}
			}
			break;
		default:
			break;

        }
    }
	return;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::HandleTelenetSdtOtherNameUpdate(HsvDestination dest, int spid, int Onid, int ServiceId, int Tsid, int eventid)
{
	HSVSPTYPE(OtherTSService, dvb, sdt) other_service;
    HsvChannel svcChannel;
    Nat16	ChannelName[33] = {0};
	int Size = (eurdiv_ChannelNameLength - 1);
    if( BACKGROUND_INSTALL && (spid == HSVSPID(OtherTSService, dvb, sdt)) && eurdiv_SupportSDTOtherInBackgroundInstallation() )
    {
        if(TRUE == strapi_GetByKey(dest, HSVSPID(OtherSDTSection, dvb, sdt), Onid, Tsid, ServiceId, &other_service))
        {
            int ret = pgdat_GetDigitalChannel(&svcChannel,Onid,Tsid, ServiceId, 0);
            if(0 == ret)
            {            	
				ret = pgdat_GetChannelDataString(svcChannel, pgdat_StringExtChannelName, ChannelName, Size);
				if ( (0 == ret) && (mCompareUnicodeString(other_service.ServiceName, ChannelName) == FALSE) )
				{
					TraceNotice(m,"Telenet : [%s] [%d] \n",__FUNCTION__,__LINE__);
					ret = pgdat_StoreChannelDataString(svcChannel, pgdat_StringExtChannelName, other_service.ServiceName, (eurdiv_ChannelNameLength-1));
					TraceNotice(m,"Telenet : Updated channel name in background inst : %d %s \n", __LINE__, __FUNCTION__);
					insN_OnEvent(insN_EventTelenetNameUpdate,svcChannel.Channel.Digit);
					if (mServiceNameUpdated == FALSE) {
						pmp_PmpSendAfter(mInstallPump, EvSdtOtherTimeout, (Nat32)NULL,(Nat32)BACKGROUND_SDT_OTHER_TIMEOUT);
						mServiceNameUpdated = TRUE;
						mNitUpdatedAlsoHappened = FALSE; /* This flag is used to identify within 30seconds a network update is performed or not */
					}
				}
            }
        }         
     }
    UNUSED(eventid);
}
void CHsvCanalDigitalInstallation_mBackground_Priv::strapiN_OnChanged           ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
	strapiN_OnAdded(dest,spid,key1,key2,key3);
	if (mActive && (mBackgroundUpdateInProgress == FALSE))
	{
		HandleTelenetSdtOtherNameUpdate (dest, spid, key1, key2, key3, eventid);
	}
	return;
}
void CHsvCanalDigitalInstallation_mBackground_Priv::strapiN_OnRemoved           ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	return;
}
int CHsvCanalDigitalInstallation_mBackground_Priv::mMapFromHsvToPlfDvbcModulation(int InputModulation)
{

	int 	OutputModulation = InputModulation;
	switch (InputModulation)
	{
	   case HsvQam16:
			   OutputModulation = PLF_TUNING_DVBC_QAM16;
			   break;
	   case HsvQam32:
			   OutputModulation = PLF_TUNING_DVBC_QAM32;
			   break;
	   case HsvQam64:
			   OutputModulation = PLF_TUNING_DVBC_QAM64;
			   break;
	   case HsvQam128:
			   OutputModulation = PLF_TUNING_DVBC_QAM128;
			   break;
	   case HsvQam256:
			   OutputModulation = PLF_TUNING_DVBC_QAM256;
			   break;
	   default:
			   break;
	}
	return OutputModulation;


}



/*hsvcanaldigital_mCommonData.c*/

inline int CHsvCanalDigitalInstallation_mBackground_Priv::mGetSDTType(Nat16 Frequency)
{
    return ((BACKGROUND_INSTALL)? eurdiv_SDTActual : ((Frequency == dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq))? eurdiv_SDTActual : eurdiv_SDTOther));
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    int i = 0;

    for(i = 0; i < mCableDSDesc.NumOfTs; i++ )
    {
        if( (mCableDSDesc.TsLoop[i].ONID == Onid) && (mCableDSDesc.TsLoop[i].Tsid == Tsid) )
        {
	    ptc->Frequency      = (mCableDSDesc.TsLoop[i].CableDesc[0].Frequency * 1000) / 16;	
            ptc->SymbolRate     = mCableDSDesc.TsLoop[i].CableDesc[0].SymbolRate;
            ptc->ModulationType = mCableDSDesc.TsLoop[i].CableDesc[0].Modulation;
			ptc->ModulationType = mMapFromHsvToPlfDvbcModulation (ptc->ModulationType);
            break;
        }
    }
    ptc->CodeRateHigh       =   ptc->CodeRateLow = HsvCodeRateAuto;
    ptc->ChannelInformation =   ptc->TimeError   = ptc->FrequencyError = ptc->FrequencyOffset = 0;
    ptc->DecoderType        =   feapi_ChanDecDvbC; 
    ptc->HierarchyMode      =   HsvHierarchyNone;
    ptc->GuardInterval      =   HsvGuardIntervalAuto;
    ptc->TxMode             =   HsvTxModeAuto;           
    ptc->IqMode             =   HsvIqModeNormal;
    ptc->ChannelBandwidth   =   HsvChanBandwidth8MHz;
    ptc->StreamPriority     =   HsvStreamPriorityHigh;
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);

    TraceDebug(m,"%s %d mInstStatus.TargetNITType %d <Freq SymRate ModRate> = <%ld %ld %d>\n", __FUNCTION__, __LINE__, mInstStatus.TargetNITType, ptc->Frequency, ptc->SymbolRate, ptc->ModulationType);
}

inline Bool CHsvCanalDigitalInstallation_mBackground_Priv::mLoadCDSDFromStrapi(int hsvspid)
{
    int i, j;
    HSVSPTYPE(ActualCableDS, dvb, nit)    CableDSDesc;
    Nat32 Frequency = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);

    mCableDSDesc.NumOfTs = strapi_GetSize(HsvMain, hsvspid);
    mBarkerMuxONID = 0xFFFF; mBarkerMuxTSID = 0xFFFF;

    TraceDebug(m,"%s %d NumofCDSD %d Frequency %ld\n", __FUNCTION__, __LINE__, mCableDSDesc.NumOfTs, Frequency);

    if(mCableDSDesc.NumOfTs > MAX_MUXES_PER_NTK)
    {
        TraceDebug(m,"%s %d NumofCDSD > MAX_MUXES_PER_NTK => (%d > %d)\n", __FUNCTION__, __LINE__, mCableDSDesc.NumOfTs, MAX_MUXES_PER_NTK);
        mCableDSDesc.NumOfTs = MAX_MUXES_PER_NTK;
    }

    for(i = 0; i < mCableDSDesc.NumOfTs; i++ )
    {
        if(strapi_GetByIndex(HsvMain, hsvspid, i, (void*)(&CableDSDesc)))
        {
            mCableDSDesc.TsLoop[i].ONID = CableDSDesc.Original_NetworkId;
            mCableDSDesc.TsLoop[i].Tsid = CableDSDesc.Tsid;
            mCableDSDesc.TsLoop[i].NumOfCDSD = CableDSDesc.NumOfCDSD;

            TraceDebug(m,"%s %d NumofCDSD %d\n", __FUNCTION__, __LINE__, CableDSDesc.NumOfCDSD);
            for(j = 0; j < CableDSDesc.NumOfCDSD; j++)
            {
                mCableDSDesc.TsLoop[i].CableDesc[j].Frequency  = CableDSDesc.CDSD[j].Frequency;
                mCableDSDesc.TsLoop[i].CableDesc[j].Modulation = CableDSDesc.CDSD[j].Modulation;
                mCableDSDesc.TsLoop[i].CableDesc[j].SymbolRate = CableDSDesc.CDSD[j].SymbolRate;

                if( (VALID_BARKERMUX_FOUND == FALSE) && (Frequency == mCableDSDesc.TsLoop[i].CableDesc[j].Frequency) )
                {
                    mBarkerMuxONID = mCableDSDesc.TsLoop[i].ONID; mBarkerMuxTSID = mCableDSDesc.TsLoop[i].Tsid;
                }
                TraceDebug(m,"CDS:: Frequency %d\nModulation %d\nSymbolRate %d\n", (CableDSDesc.CDSD[j].Frequency>>4), CableDSDesc.CDSD[j].Modulation, CableDSDesc.CDSD[j].SymbolRate);
            }
        }
        else
        {
            TraceDebug(m,"%s %d strapi_GetByIndex failed for pid %d index %d\n", __FUNCTION__, __LINE__, hsvspid, i);
        }
    }

    return ((mCableDSDesc.NumOfTs == 0)? FALSE: TRUE);
}

inline Bool CHsvCanalDigitalInstallation_mBackground_Priv::mGetAltTSValues(Nat16* ONID, Nat16* TSID)
{
    UNUSED(ONID);
    UNUSED(TSID);
    return TRUE;
}

inline void CHsvCanalDigitalInstallation_mBackground_Priv::mGetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{
    *ONID = mBarkerMuxONID; *TSID = mBarkerMuxTSID;
}

Bool CHsvCanalDigitalInstallation_mBackground_Priv::mCheckVisibleService(HsvPgdatPresetData* preset)
{
	HsvPgdatDigServiceData data;
	Bool retval = FALSE;

	ASSIGN_DIGSVC_KEYS(&data, preset);
	if(pgdb_GetByKey((pgdb_GetCurrentTable() | pgdbconst_DigitalService), (Address)&data))
	{               
		if (data.VisibleService)
		{
			retval = TRUE;
		}
	}
	else
	{
		TraceErr(m, "pgdb_GetByKey failed");
	}
	return retval;
}

void CHsvCanalDigitalInstallation_mBackground_Priv::tuneToLowestPreset()
{
	HsvPgdatDigServiceData  svcdat_temp;
	int from = -1, to = -1,srvindex = -1;
	int presetNumber = 0;	
	HsvPgdatPresetData	PresetData,temp_PresetData;
	svcdat_temp.OriginalNetworkId = OnId;
	svcdat_temp.ServiceId = SrvId;
	if(pgdb_GetRange(SERVICE_TABLE,2,(Address)&svcdat_temp,&from,&to)) {
		ASSERT(from<=to);
		for (srvindex = from; srvindex <= to ; srvindex++)
		{
			if(pgdb_GetByIndex(SERVICE_TABLE, srvindex, (Address)&svcdat_temp)) {
				if(svcdat_temp.Tsid == TsId) {
					temp_PresetData.PresetNumber = svcdat_temp.PresetNumber;
					if (pgdb_GetByKey(PRESETTABLE, &temp_PresetData) == TRUE)
					{
						if(temp_PresetData.PresetNumber != CachedPresetnumber) {
							presetNumber = temp_PresetData.PresetNumber;
							mPresetChanged = TRUE;
						} else {
						}
					}
					break;	
				}
			}
		}
		if(srvindex > to) {
			mLowestPreset = TRUE;
		}
   } else {
		mLowestPreset = TRUE;
   }
	if(mLowestPreset) {
		int NoOfRecords = pgdb_GetNoRecords(pgdb_GetCurrentTable() | pgdbconst_Preset);
		while(NoOfRecords > 0)
		{
			if(pgdb_GetByIndex((pgdb_GetCurrentTable() | pgdbconst_Preset), (NoOfRecords-1), (Address)&PresetData))
			{
				if((mCheckVisibleService(&PresetData)))
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
			presetNumber = PresetData.PresetNumber;
			TraceNotice(m, "Lowest preset Number %d", presetNumber);
		}
		else
		{
			TraceNotice(m, "No Visible Service found");
		}
		mLowestPreset = FALSE;
		mPresetChanged = TRUE;
	}
	TraceNotice(m ,"%s %d mPresetChanged[%d] presetNumber[%d] \n",__FUNCTION__,__LINE__,mPresetChanged,presetNumber);
	if(mPresetChanged == TRUE) {
		insN_OnEvent(insN_EventNewPresetNumber,presetNumber);
		mPresetChanged = FALSE;
	}
	mDirtyBit = FALSE;
}
