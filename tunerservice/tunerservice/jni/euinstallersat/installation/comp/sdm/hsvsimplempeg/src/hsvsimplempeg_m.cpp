#include "_hsvsimplempeg_m.h"

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "s2/sdm/hsvsimplempeg")


#ifndef __cplusplus

#else

#endif




























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvSimpleMpegDataManager_Priv::MpegAcqEventNames[EvMax+1][32] = 
{	
	"EvStart",
	"EvPatCollected",
	"EvPatNotCollected",
	"EvPmtCollected",
	"EvPmtTimeout",
	"EvStop",
	"EvMax"
};


Pump CHsvSimpleMpegDataManager_Priv::s__mPump;

Pump CHsvSimpleMpegDataManager_Priv::s__NoDataPump;



/* Data structures used for storing the information */
PatTableData CHsvSimpleMpegDataManager_Priv::s__ProgramTables[HsvDmxLast];

PmtTableData CHsvSimpleMpegDataManager_Priv::s__PmtTables [HsvDmxLast][MAX_PMT_FILTERS_SUPPORTED];

MpegAcqStatus CHsvSimpleMpegDataManager_Priv::s__mStatus;

Nat8 CHsvSimpleMpegDataManager_Priv::s__mBuffer[16*1024];

int CHsvSimpleMpegDataManager_Priv::s__mFreesatServiceId = 0;

/****************************************************************************
 * Static functions
 ****************************************************************************/























FunctionNat32 CHsvSimpleMpegDataManager_Priv::s__EventActionMatrix[EvMax][StMax] = 
{								/*StIdle						StWaitPat					StWaitPmt			*/
/* EvStart*/				{	FNADDR(FuncStartPatCollection),	NULL,						NULL				},
/* EvPatCollected*/			{	NULL,							FNADDR(FuncProcessPat),		NULL				},	
/* EvPatNotCollected*/		{	NULL,							FNADDR(FuncPatTimeout),		NULL				},
/* EvPmtCollected */		{	NULL,							NULL,						FNADDR(FuncProcessPmt)		},
/* EvPmtTimeout */			{	NULL,							NULL,						FNADDR(FuncPmtTimeout)		},
/* EvStop		*/			{	FNADDR(FuncStopCollection),		FNADDR(FuncStopCollection),	FNADDR(FuncStopCollection)	}
};


HSVCOMPAREKEY(simplepmtinfomain,	Primary,	HsvSimplePMTPidInfo,	ServiceId)
/* Not used */

HSVCOMPAREKEY(simplepmtinfomain,	Secondary,	HsvSimplePMTPidInfo,	ServiceId)

HSVCOMPAREKEY(simplepmtinfomain,	Teritiary,	HsvSimplePMTPidInfo,	ServiceId)

HSVCOMPAREKEY(simplepmtinfomain,	Quaternary,	HsvSimplePMTPidInfo,	ServiceId)


HSVCOMPAREKEY(simplepmtFreesatTunnelledInfo,	Primary,	HsvFreesatTunnelledDataInfo,	ServiceId)
/* Not used */
HSVCOMPAREKEY(simplepmtFreesatTunnelledInfo,	Secondary,	HsvFreesatTunnelledDataInfo,	ServiceId)
HSVCOMPAREKEY(simplepmtFreesatTunnelledInfo,	Teritiary,	HsvFreesatTunnelledDataInfo,	ServiceId)
HSVCOMPAREKEY(simplepmtFreesatTunnelledInfo,	Quaternary,	HsvFreesatTunnelledDataInfo,	ServiceId)
#ifdef __cplusplus

HSVCOMPAREKEY(simplepmtinfoaux,	Primary,	HsvSimplePMTPidInfo,	ServiceId)

HSVCOMPAREKEY(simplepmtinfoaux,	Secondary,	HsvSimplePMTPidInfo,	ServiceId)

HSVCOMPAREKEY(simplepmtinfoaux,	Teritiary,	HsvSimplePMTPidInfo,	ServiceId)

HSVCOMPAREKEY(simplepmtinfoaux,	Quaternary,	HsvSimplePMTPidInfo,	ServiceId)

#endif


void CHsvSimpleMpegDataManager_Priv::PumpHandler(int event, Nat32 param)
{	
	int		State = mStatus.CurState;

	if(VALID_EVENT(event) && VALID_STATE(State))
	{
		if(EventActionMatrix[event][State] != NULL)
		{
			TraceNotice (m, " SimpleMpeg: %s %d event %d [%s] State %d \n", __FUNCTION__, __LINE__, event,MpegAcqEventNames[event],  State);
			FPCALL(EventActionMatrix[event][State])(param);
		}
	}
}

void CHsvSimpleMpegDataManager_Priv::FuncStartPatCollection (Nat32 Param)
{
	/* This will just collect the PAT table */
	mInitialize (Param);
	InitSimplePmtInfo (Param);
	InitFreesatTunnelledInfo(Param);
	mStatus.CurrentPmtRequestIndex = 0;
	mStatus.NumCollectedPmts = 0;

	mCollectPat (Param);
}

void CHsvSimpleMpegDataManager_Priv::FuncProcessPat (Nat32 Param)
{
	int	count = 0;

	/* PAT arrived and data stored. Now stop PAT filter. Start maximum PMT filters
		possible (MAX_PMT_FILTERS_SUPPORTED)	*/
	ProgramTables[CUR_DMX].TablesInitialized = TRUE;

	mStopPat (CUR_DMX);

	SET_STATE(StWaitPmt);

	strapiN_OnCompleted (HSV_MAP_DMX_TO_DEST(CUR_DMX), HSVSPID(Program, mpeg, simplepat));
	if( ctrlN_iPresent())
    {
		/* Notify PAT information is ready */
        ctrlN_OnEvent( CUR_DMX, ctrlN_DataAvailable, ctrlN_SIMPLEPAT);
    }

	for (count = 0; count < MIN(MAX_PMT_FILTERS_SUPPORTED, ProgramTables[CUR_DMX].patsec.NumPrograms) ;count++)
	{
		mCollectPmt (count, ProgramTables[CUR_DMX].patsec.ProgramNumber[count], ProgramTables[CUR_DMX].patsec.ProgramMapPid[count]);
		mStatus.CurrentPmtRequestIndex++;
	}
	UNUSED (Param);
}

void CHsvSimpleMpegDataManager_Priv::FuncPatTimeout (Nat32 Param)
{
	UNUSED (Param);
}

void CHsvSimpleMpegDataManager_Priv::FuncProcessPmt (Nat32 Param)
{
	/* Param contains the filter index */
	Nat16   strapiCookie = 0;
	Nat32   ActlParam = Param;


	strapiCookie = ActlParam & 0x00FF;
	Param        = (ActlParam >>16)&0x00FF;
	

	/* stop filter */
	mStopPmt (CUR_DMX, (int)Param);
	mStatus.NumCollectedPmts++;

	if (IGNORE_STRAPI != strapiCookie)
	{
		/* Update the values in strapi */
		mUpdateStrapiWithSimplePmt ((int)Param);
	}
	if(Param < MAX_PMT_FILTERS_SUPPORTED)
	{
		PmtTables [CUR_DMX][Param].TablesInitialized = FALSE;
	}

	/* Trigger next PMT if needed */
	if (mStatus.CurrentPmtRequestIndex < ProgramTables[CUR_DMX].patsec.NumPrograms)
	{
		mCollectPmt (Param, ProgramTables[CUR_DMX].patsec.ProgramNumber[mStatus.CurrentPmtRequestIndex], \
							ProgramTables[CUR_DMX].patsec.ProgramMapPid[mStatus.CurrentPmtRequestIndex]);
		mStatus.CurrentPmtRequestIndex++;
	}
	else 
	{
		/* If all collected give the notification */
		if (mStatus.NumCollectedPmts >= ProgramTables[CUR_DMX].patsec.NumPrograms)
		{
			strapiN_OnCompleted (HSV_MAP_DMX_TO_DEST(CUR_DMX), HSVSPID(PidInfo, mpeg,simplepmt));
			SET_STATE(StIdle);
			/* Completed the PAT & PMT collection */
			if( ctrlN_iPresent())
			{
				/* Notify PAT information is ready */
				ctrlN_OnEvent( CUR_DMX, ctrlN_DataAvailable, ctrlN_SIMPLEPMT);
			}
		}
	}
}

void CHsvSimpleMpegDataManager_Priv::FuncPmtTimeout (Nat32 Param)
{
	UNUSED (Param);
}

void CHsvSimpleMpegDataManager_Priv::FuncStopCollection (Nat32 Param)
{
	int count = 0;
		
	if (ProgramTables[Param].PatSubscriptionStarted == TRUE)
	{
		mStopPat(Param);
	}

	for (count = 0 ; count < MAX_PMT_FILTERS_SUPPORTED; count++)
	{
		if (PmtTables [Param][count].PmtSubscriptionStarted == TRUE)
		{
			mStopPmt (Param, count);
		}
	}

	ctrlN_OnEvent( CUR_DMX, ctrlN_StoppedCollection, 0);
}

/*********************************************************************/
void CHsvSimpleMpegDataManager_Priv::NoDataAvailableHandler( int dmx, Nat32 eventmask)
{
	int count = 0;

	PrintfNotice ("TRACE_TIME_OUT\n");

	for (count = 0; count < MIN(MAX_PMT_FILTERS_SUPPORTED, ProgramTables[CUR_DMX].patsec.NumPrograms) ;count++)
	{
		if (PmtTables [CUR_DMX][count].PmtSubscriptionStarted == TRUE)
		{
			pmp_PmpSend (mPump, EvPmtCollected, ((count<<16)|IGNORE_STRAPI));
		}
	}
	
	
}

void CHsvSimpleMpegDataManager_Priv::mInitialize (Nat32 Param)
{
	memset (&ProgramTables[Param], 0x00, sizeof(PatTableData));
	memset (PmtTables[Param], 0x00, ((sizeof(PmtTableData)) * MAX_PMT_FILTERS_SUPPORTED));

	ProgramTables[Param].PatSubscriptionId = HSV_INVALID_SCT_REQUEST;
	ProgramTables[Param].TablesInitialized = FALSE;
	SET_STATE(StIdle);

	SET_CUR_DMX((HsvDemux)Param);
}

void CHsvSimpleMpegDataManager_Priv::mCollectPat (Nat32 Param)
{
	if (1 /*sec_IsRequestAllowed(HSV_MAP_DMX_TO_DEST(Param))*/)
	{
		SET_STATE(StWaitPat);
		#ifndef __cplusplus
		ProgramTables[Param].PatSubscriptionId  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(Param), (int)PAT_PID_VALUE, PAT_TABLE_ID,PAT_TABLE_ID, (HsvSectionCallback)Pat_Parser_Parser);	
		#else
		ProgramTables[Param].PatSubscriptionId  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(Param), (int)PAT_PID_VALUE, PAT_TABLE_ID,PAT_TABLE_ID, FNADDR(Pat_Parser_Parser));	
		#endif
		//ProgramTables[Param].TablesInitialized = TRUE;
		ProgramTables[Param].PatSubscriptionStarted = TRUE;
		pmp_PmpSendAfter (mPump, EvPatNotCollected, (Nat32)NULL, PAT_COLLECTION_TIMEOUT);
	}
	else
	{
		PrintfNotice (" SimpleMpeg: Request Not allowed for the current Demux \n");
	}
}

void CHsvSimpleMpegDataManager_Priv::mStopPat (int Dmx)
{
	/* Stop filter and reset the subscription details */
	sec_CancelSection (HSV_MAP_DMX_TO_DEST(Dmx), ProgramTables[Dmx].PatSubscriptionId);
	ProgramTables[Dmx].PatSubscriptionId = HSV_INVALID_SCT_REQUEST;
	ProgramTables[Dmx].PatSubscriptionStarted = FALSE;
}

void CHsvSimpleMpegDataManager_Priv::mCollectPmt (int FilterIndex, Nat16 ServiceId, Nat16 PmtPid)
{
    TraceNotice(m,"%s() PmtPid %d\n", __FUNCTION__, PmtPid);
	if (PmtTables [CUR_DMX][FilterIndex].TablesInitialized == FALSE)
	{
		/* Service ID is passed as the Cookie here */
		#ifndef __cplusplus
		PmtTables[CUR_DMX][FilterIndex].PmtSubscriptionId = sec_RequestSection2 (HSV_MAP_DMX_TO_DEST(CUR_DMX), (int)PmtPid, PMT_TABLE_ID, ServiceId, ServiceId, (HsvSectionCallback)Pmt_Parser_Parser);
		#else
		PmtTables[CUR_DMX][FilterIndex].PmtSubscriptionId = sec_RequestSection2 (HSV_MAP_DMX_TO_DEST(CUR_DMX), (int)PmtPid, PMT_TABLE_ID, ServiceId, ServiceId, FNADDR(Pmt_Parser_Parser));
		#endif
		PmtTables[CUR_DMX][FilterIndex].TablesInitialized = TRUE;
		PmtTables[CUR_DMX][FilterIndex].PmtSubscriptionStarted = TRUE;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.ServiceId = ServiceId;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.VideoPid = INVALID_PID;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.AudioPid = INVALID_PID;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.PcrPid = INVALID_PID;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.SgtPid = INVALID_PID;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.VideoStreamType= INVALID_PID;
		PmtTables[CUR_DMX][FilterIndex].pmtsec.AudioStreamType= INVALID_PID;
		pmp_PmpSendAfter(NoDataPump, 0, 0,3000);
	}
	else
	{
		PrintfNotice (" SimpleMpeg : Error. FilterIndex already in use %d \n", FilterIndex);
	}
}

void CHsvSimpleMpegDataManager_Priv::mStopPmt (int Dmx, int FilterIndex)
{
	/* Stop PMT filter and reset subscription variables */
	if(FilterIndex < MAX_PMT_FILTERS_SUPPORTED)
	{
		sec_CancelSection (HSV_MAP_DMX_TO_DEST(Dmx), PmtTables [Dmx][FilterIndex].PmtSubscriptionId);
		PmtTables [Dmx][FilterIndex].PmtSubscriptionId = HSV_INVALID_SCT_REQUEST;
		PmtTables [Dmx][FilterIndex].PmtSubscriptionStarted = FALSE;
	}
}

Bool CHsvSimpleMpegDataManager_Priv::mPopulateSimplePat (HsvDemux dmx , Address Ptr, int code )
{
	Bool	RetVal = TRUE;
	int	count = 0;
	int	ProgramNumber, PmtPid;
	TypePat_Parser	*ProgramAssociationTable = (TypePat_Parser*)Ptr;

	TraceNotice(m,"mPopulateSimplePat");
	/* Simple PAT information is not stored in strapi. Rather this is stored on
		local data structure only */
	if ((code & 0xFFFF) & sec_SctArrived)
	{
		for (count =0; count < ProgramAssociationTable->TsLoopDataNum; count++)
		{
			ProgramNumber = ProgramAssociationTable->TsLoopData[count].ProgramNumber;
			PmtPid = ProgramAssociationTable->TsLoopData[count].PID;

			/* TODO: Check whether repetition can happen here */
			if (ProgramTables[dmx].patsec.NumPrograms < MAX_POSSIBLE_PROGRAMS)
			{
				/* Program Number 0 indicates NIT PID. So ignore this */
				if (ProgramNumber != 0)
				{
					ProgramTables[dmx].patsec.ProgramNumber[ProgramTables[dmx].patsec.NumPrograms] = ProgramNumber;
					ProgramTables[dmx].patsec.ProgramMapPid[ProgramTables[dmx].patsec.NumPrograms] = PmtPid;
					ProgramTables[dmx].patsec.NumPrograms++;
				}
			}
			else
			{
				PrintfNotice (" SimpleMpeg: Warning: PAT Database is FULL...\n");
				RetVal = FALSE;
				break;
			}
		}
	}	
	if ((code & 0xFFFF) & sec_TableCompleted)
	{
		/* Trigger to stop PAT and start PMT collection */
		TraceNotice(m,"Sending EvPatCollected");
		pmp_PmpSend (mPump, EvPatCollected, (Nat32)NULL);
	}
	

	return RetVal;
}

Bool CHsvSimpleMpegDataManager_Priv::mPopulateSimplePmt ( HsvDemux dmx , Address Ptr, int code )
{
	Bool	RetVal = FALSE;
	Nat16	CollectedServiceId = 0;
	int		count = 0, innercount = 0;
	TypePmt_Parser	*ProgramMapTable = (TypePmt_Parser *)Ptr;

	CollectedServiceId = (code & (0xFFFF<<16)) >> 16;
	/* Cookie coming from platform contains the ServiceID. Check for 
		matching service ID. And then store the A/V/PCR pid details to 
		local data structure. Once complete PMT information is received
		(for a particular service, it should be added to strapi */
	for (count = 0; count < MAX_PMT_FILTERS_SUPPORTED; count++)
	{
		if (PmtTables[dmx][count].pmtsec.ServiceId == CollectedServiceId)
		{
			RetVal = TRUE;
			break;
		}
	}

	if (RetVal == TRUE)
	{
		if (((code & 0xFFFF) & sec_SctArrived ) && (count < MAX_PMT_FILTERS_SUPPORTED))
		{

			/* count contains the current filter index */
			for (innercount = 0; innercount < ProgramMapTable->TsLoopDataNum; innercount++)
			{

				if ( (IsInvalidPid(PmtTables[dmx][count].pmtsec.PcrPid)) && (IsValidPid(ProgramMapTable->PCR_PID)) )
				{
					PmtTables[dmx][count].pmtsec.PcrPid = ProgramMapTable->PCR_PID;
				}

				if ( (IsInvalidPid(PmtTables[dmx][count].pmtsec.VideoPid)) &&  (IsValidVideoStreamType (ProgramMapTable->TsLoopData[innercount].StreamType)) )
				{
					PmtTables[dmx][count].pmtsec.VideoPid = ProgramMapTable->TsLoopData[innercount].BasicPID;
					PmtTables[dmx][count].pmtsec.VideoStreamType= ProgramMapTable->TsLoopData[innercount].StreamType;
				}
				else if ( (IsInvalidPid(PmtTables[dmx][count].pmtsec.AudioPid)) &&  (IsValidAudioStreamType (ProgramMapTable->TsLoopData[innercount].StreamType)) )
				{
					PmtTables[dmx][count].pmtsec.AudioPid = ProgramMapTable->TsLoopData[innercount].BasicPID;
					PmtTables[dmx][count].pmtsec.AudioStreamType = ProgramMapTable->TsLoopData[innercount].StreamType;
				}
				else if ( (IsInvalidPid(PmtTables[dmx][count].pmtsec.SgtPid)) &&  (ProgramMapTable->TsLoopData[innercount].StreamType == SGT_REF_STREAM_TYPE) )
				{
					PmtTables[dmx][count].pmtsec.SgtPid = ProgramMapTable->TsLoopData[innercount].BasicPID;
					TraceNotice(m,"SGT pid collected: %d",PmtTables[dmx][count].pmtsec.SgtPid);
				}
			}
		}
        
		if ((code & 0xFFFF) & sec_TableCompleted)
		{		    
			/* Triggering to start the update of PMT data to strapi */
			pmp_PmpSend (mPump, EvPmtCollected, (count<<16));
		}
	}
	else
	{
		PrintfNotice ("Invalid PMT Collected ServiceId %d ", CollectedServiceId);
	}

	return RetVal;
}

Bool CHsvSimpleMpegDataManager_Priv::mPopulateFreesatTunnelledInfo ( HsvDemux dmx , Address Ptr, int code )
{
	TypePmt_Parser	*ProgramMapTable = (TypePmt_Parser *)Ptr;
	HsvFreesatTunnelledDataInfo DbaseVersion, CurrentVersion;
	Nat16 LoopCount = 0;
	Nat16 EsLoop = 0;
	Nat16 StreamIdentifierLoop = 0;
	Nat8 TunnelledType = 0;
	Nat8 ComponentTag = 0;
	Bool ComponentFound = FALSE;
	if ((code & 0xFFFF) & sec_SctArrived)
	{
		LoopCount = 0;
		while(LoopCount < ProgramMapTable->FreesatTunnelledDataDescNum)
		{
			if(FREESAT_PDSD_VALUE == ProgramMapTable->FreesatTunnelledData_Descriptor[LoopCount].PrivateDataSpecifier)
			{
				/*consider only valid tunnelled types for population
				**Refer Table 8 Free Satellite Requirements for Interoperability Part 3: System Management Ver 1.6
				*/
				TunnelledType = ProgramMapTable->FreesatTunnelledData_Descriptor[LoopCount].TunnelledDataType;
				if(((0x00 <= TunnelledType) && (TunnelledType <= 0x07)) || ((0x09 <= TunnelledType) && (TunnelledType <= 0x0C)))
				{
					CurrentVersion.VersionNumber = ProgramMapTable->VersionNumber;
					CurrentVersion.ServiceId = ProgramMapTable->FreesatTunnelledData_Descriptor[LoopCount].ServiceId;
					ComponentTag = ProgramMapTable->FreesatTunnelledData_Descriptor[LoopCount].ComponentTag;
					CurrentVersion.TunnelledDataTypeBitMap = 0;
					EsLoop = 0;
					ComponentFound = FALSE;
					while((FALSE == ComponentFound) && (EsLoop < ProgramMapTable->TsLoopDataNum))
					{
						StreamIdentifierLoop = 0;
						while(StreamIdentifierLoop < ProgramMapTable->TsLoopData[EsLoop].StreamIdentifierDescNum)
						{
							if(ComponentTag == ProgramMapTable->TsLoopData[EsLoop].StreamIdentifierDescriptor[StreamIdentifierLoop].ComponentTag)
							{
								ComponentFound = TRUE;
								CurrentVersion.TunnelledDataTypeBitMap = (1 << TunnelledType);
								CurrentVersion.PID[TunnelledType] = ProgramMapTable->TsLoopData[EsLoop].StreamIdentifierDescriptor[StreamIdentifierLoop].BasicPID;
								break;
							}
							StreamIdentifierLoop++;
						}

						EsLoop++;
					}

					if(ComponentFound)
					{
						if (srtdb_QueryOnKey( srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0 , 0, (Address)(&DbaseVersion) ) )
						{
							if(CurrentVersion.VersionNumber == DbaseVersion.VersionNumber)
							{
								DbaseVersion.TunnelledDataTypeBitMap |= CurrentVersion.TunnelledDataTypeBitMap;
								DbaseVersion.PID[TunnelledType] = CurrentVersion.PID[TunnelledType];
								TraceNotice(m,"TMP_DEBUG Line %d Tunelled data Database update TunnelledType 0x%x SID %d PID %d TunnelledDataTypeBitMap 0x%x",__LINE__,
												TunnelledType,DbaseVersion.ServiceId ,DbaseVersion.PID[TunnelledType], DbaseVersion.TunnelledDataTypeBitMap);
								srtdb_Update(srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0,(Address)(&DbaseVersion));
							}
							else
							{
								TraceNotice(m,"TMP_DEBUG Line %d Tunelled data Current update TunnelledType 0x%x SID %d PID %d TunnelledDataTypeBitMap 0x%x",__LINE__,
												TunnelledType,CurrentVersion.ServiceId ,CurrentVersion.PID[TunnelledType], CurrentVersion.TunnelledDataTypeBitMap);
								srtdb_Update(srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0,(Address)(&CurrentVersion));
							}
							strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt), CurrentVersion.ServiceId, 0,0, 0);
						}
						else
						{
							TraceNotice(m,"TMP_DEBUG Line %d Tunelled data Insert TunnelledType 0x%x SID %d PID %d TunnelledDataTypeBitMap 0x%x",__LINE__,
												TunnelledType,CurrentVersion.ServiceId ,CurrentVersion.PID[TunnelledType], CurrentVersion.TunnelledDataTypeBitMap);
							srtdb_Insert( srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0, (Address)(&CurrentVersion));
							strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt), CurrentVersion.ServiceId, 0,0);
						}
					}
				}
			}
			//Caching service id for collecting tunnelled during Background Update.
			
			mFreesatServiceId = CurrentVersion.ServiceId;
			
			LoopCount++;
		}

		

		/*Populate  if free satellite tunnelled  data descriptor is available then ignore free satellite alternate tunnelled data
		**Refre section 3.1. PID tunnelling Free Satellite Requirements for Interoperability Part 3: System Management Ver 1.6
		*/
		if(0 == ProgramMapTable->FreesatTunnelledDataDescNum)
		{
			EsLoop = 0;
			while(EsLoop < ProgramMapTable->TsLoopDataNum)
			{
				LoopCount = 0;
				TraceNotice(m,"TMP_DEBUG FreesatAltTunnelledDataDescNum %d ", ProgramMapTable->TsLoopData[EsLoop].FreesatAltTunnelledDataDescNum);
				while(LoopCount < ProgramMapTable->TsLoopData[EsLoop].FreesatAltTunnelledDataDescNum)
				{
					if(FREESAT_PDSD_VALUE == ProgramMapTable->TsLoopData[EsLoop].FreesatAltTunnelledData_Descriptor[LoopCount].PrivateDataSpecifier)
					{
						TunnelledType = ProgramMapTable->TsLoopData[EsLoop].FreesatAltTunnelledData_Descriptor[LoopCount].TunnelledDataType;
						if(((0x00 <= TunnelledType) && (TunnelledType <= 0x07)) || ((0x09 <= TunnelledType) && (TunnelledType <= 0x0C)))
						{
							CurrentVersion.VersionNumber = ProgramMapTable->VersionNumber;
							CurrentVersion.ServiceId = ProgramMapTable->TsLoopData[EsLoop].FreesatAltTunnelledData_Descriptor[LoopCount].ServiceId;
							CurrentVersion.TunnelledDataTypeBitMap = (1 << TunnelledType);
							CurrentVersion.PID[TunnelledType] = ProgramMapTable->TsLoopData[EsLoop].FreesatAltTunnelledData_Descriptor[LoopCount].BasicPID;
							if (srtdb_QueryOnKey( srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0, (Address)(&DbaseVersion) ) )
							{
								if(CurrentVersion.VersionNumber == DbaseVersion.VersionNumber)
								{
									DbaseVersion.TunnelledDataTypeBitMap |= CurrentVersion.TunnelledDataTypeBitMap;
									DbaseVersion.PID[TunnelledType] = CurrentVersion.PID[TunnelledType];
									srtdb_Update(srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0,(Address)(&DbaseVersion));
									TraceNotice(m,"TMP_DEBUG Line %d Alt Tunelled data Database update TunnelledType 0x%x SID %d PID %d TunnelledDataTypeBitMap 0x%x",__LINE__,
												TunnelledType,DbaseVersion.ServiceId ,DbaseVersion.PID[TunnelledType], DbaseVersion.TunnelledDataTypeBitMap);
								}
								else
								{
									TraceNotice(m,"TMP_DEBUG Line %d Alt Tunelled data Current update TunnelledType 0x%x SID %d PID %d TunnelledDataTypeBitMap 0x%x",__LINE__,
											TunnelledType,CurrentVersion.ServiceId ,CurrentVersion.PID[TunnelledType], CurrentVersion.TunnelledDataTypeBitMap);
									srtdb_Update(srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0,(Address)(&CurrentVersion));
								}
								strapiN_OnChanged(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt), CurrentVersion.ServiceId, 0,0, 0);
							}
							else
							{
								TraceNotice(m,"TMP_DEBUG Line %d Alt Tunelled data Insert TunnelledType 0x%x SID %d PID %d TunnelledDataTypeBitMap 0x%x",__LINE__,
												TunnelledType,CurrentVersion.ServiceId ,CurrentVersion.PID[TunnelledType], CurrentVersion.TunnelledDataTypeBitMap);
								srtdb_Insert( srtdbids_SimplepmtFreesatTunnelledInfo, CurrentVersion.ServiceId, 0,0,0, (Address)(&CurrentVersion));
								strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt), CurrentVersion.ServiceId, 0,0);
							}
						}
					}
					mFreesatServiceId = CurrentVersion.ServiceId;
					LoopCount++;
				}
				EsLoop++;
			}
		}
	}
	
	if ((code & 0xFFFF) & sec_TableCompleted)
	{
		LoopCount = srtdb_GetNoOfRecords(srtdbids_SimplepmtFreesatTunnelledInfo);

		while(LoopCount > 0)
		{
			LoopCount--;
			if(srtdb_QueryOnIndex(srtdbids_SimplepmtFreesatTunnelledInfo,LoopCount,(Address )(&DbaseVersion)))
			{
				if(DbaseVersion.VersionNumber != ProgramMapTable->VersionNumber)
				{
					strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt), DbaseVersion.ServiceId, 0, 0);
				}
			}
		}
		TraceNotice(m,"Cached Freesat Service Id %d",mFreesatServiceId);
		strapiN_OnCompleted(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt));
		
	}
	return TRUE;
}
void CHsvSimpleMpegDataManager_Priv::InitSimplePmtInfo (int Dmx)
{
	srtdb_Init (SIMPLE_PMT_SORTEDTABLE_ID(Dmx));
}

void CHsvSimpleMpegDataManager_Priv::InitFreesatTunnelledInfo(int Dmx)
{
	srtdb_Init(srtdbids_SimplepmtFreesatTunnelledInfo);
}

void CHsvSimpleMpegDataManager_Priv::mUpdateStrapiWithSimplePmt (int FilterIndex)
{    
	HsvSimplePMTPidInfo		SimplePmtInfo;

	if(FilterIndex < MAX_PMT_FILTERS_SUPPORTED)
	{
		if (srtdb_QueryOnKey (SIMPLE_PMT_SORTEDTABLE_ID(CUR_DMX), PmtTables[CUR_DMX][FilterIndex].pmtsec.ServiceId, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY, (Address)&SimplePmtInfo))
		{		    
			/* Highly unusual case */
			SimplePmtInfo.ServiceId = PmtTables[CUR_DMX][FilterIndex].pmtsec.ServiceId;
			SimplePmtInfo.VideoPid = IsValidPid(SimplePmtInfo.VideoPid) ? SimplePmtInfo.VideoPid : PmtTables[CUR_DMX][FilterIndex].pmtsec.VideoPid;
			SimplePmtInfo.AudioPid = IsValidPid(SimplePmtInfo.AudioPid) ? SimplePmtInfo.AudioPid : PmtTables[CUR_DMX][FilterIndex].pmtsec.AudioPid;
			SimplePmtInfo.PcrPid = IsValidPid(SimplePmtInfo.PcrPid) ? SimplePmtInfo.PcrPid : PmtTables[CUR_DMX][FilterIndex].pmtsec.PcrPid;
			SimplePmtInfo.SgtPid = IsValidPid(SimplePmtInfo.SgtPid) ? SimplePmtInfo.SgtPid : PmtTables[CUR_DMX][FilterIndex].pmtsec.SgtPid;
			SimplePmtInfo.VideoStreamType= IsValidPid(SimplePmtInfo.VideoStreamType) ? SimplePmtInfo.VideoStreamType: PmtTables[CUR_DMX][FilterIndex].pmtsec.VideoStreamType;
			SimplePmtInfo.AudioStreamType= IsValidPid(SimplePmtInfo.AudioStreamType) ? SimplePmtInfo.AudioStreamType: PmtTables[CUR_DMX][FilterIndex].pmtsec.AudioStreamType;

			srtdb_Update ( SIMPLE_PMT_SORTEDTABLE_ID(CUR_DMX) , PmtTables[CUR_DMX][FilterIndex].pmtsec.ServiceId, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY, (Address)&SimplePmtInfo);
			strapiN_OnChanged (HSV_MAP_DMX_TO_DEST(CUR_DMX), HSVSPID(PidInfo, mpeg,simplepmt), SimplePmtInfo.ServiceId, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY,0);
		}
		else
		{		    
			SimplePmtInfo.ServiceId = PmtTables[CUR_DMX][FilterIndex].pmtsec.ServiceId;
			SimplePmtInfo.VideoPid = PmtTables[CUR_DMX][FilterIndex].pmtsec.VideoPid;
			SimplePmtInfo.AudioPid = PmtTables[CUR_DMX][FilterIndex].pmtsec.AudioPid;
			SimplePmtInfo.PcrPid = PmtTables[CUR_DMX][FilterIndex].pmtsec.PcrPid;
			SimplePmtInfo.SgtPid = PmtTables[CUR_DMX][FilterIndex].pmtsec.SgtPid;
			SimplePmtInfo.VideoStreamType= PmtTables[CUR_DMX][FilterIndex].pmtsec.VideoStreamType;
			SimplePmtInfo.AudioStreamType= PmtTables[CUR_DMX][FilterIndex].pmtsec.AudioStreamType;

			if(srtdb_Insert (SIMPLE_PMT_SORTEDTABLE_ID(CUR_DMX) , PmtTables[CUR_DMX][FilterIndex].pmtsec.ServiceId, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY, (Address)&SimplePmtInfo))
			{			    
				strapiN_OnAdded (HSV_MAP_DMX_TO_DEST(CUR_DMX), HSVSPID(PidInfo, mpeg,simplepmt), SimplePmtInfo.ServiceId, INVALID_SRTDB_KEY, INVALID_SRTDB_KEY);
                //TraceNotice(m,"%s() : %d strapiN_OnAdded for Svc %d spid %d", __FUNCTION__, __LINE__, SimplePmtInfo.ServiceId, HSVSPID(PidInfo, mpeg,simplepmt));
			}
			else
			{
				PrintfNotice (" SimpleMpeg: Warning : Error in inserting ServiceID %d \n",SimplePmtInfo.ServiceId);
			}
		}
	}
}

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower	pow */
void CHsvSimpleMpegDataManager_Priv::pow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbsins_mpegacq" );
    NoDataPump      = pmp_PmpCreateEx( pen_PumpEngine, NoDataAvailableHandler,TRUE, "oDataPump");   /* Replacing pump*/
    ASSERT( NoDataPump );    /* Failed to create the required number of pumps. Is the infra diversity set to a sufficiently high value ?*/
}

void CHsvSimpleMpegDataManager_Priv::pow_TurnOn  ( void )
{	
}

void CHsvSimpleMpegDataManager_Priv::pow_TurnOff ( void )
{
}

/* provides IHsvPopulate	ipop	*/

Bool CHsvSimpleMpegDataManager_Priv::ipop_PopulatePAT ( HsvDemux dmx , Address ProgramAssocationTable, int code )
{
	return mPopulateSimplePat (dmx,ProgramAssocationTable,code);
}

Bool CHsvSimpleMpegDataManager_Priv::ipop_PopulatePMT ( HsvDemux dmx , Address ProgramMapTable, int code )
{
	
	int installedPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);

	if(installedPackageId == FREESAT_PACKAGE_ID) 
	{
	mPopulateFreesatTunnelledInfo(dmx,ProgramMapTable,code);
	}
	mPopulateSimplePmt (dmx,ProgramMapTable,code);
	return TRUE;
}


/* provides IHsvSdmEnable	enable	*/

void CHsvSimpleMpegDataManager_Priv::enable_Enable (HsvDemux dmx)
{
	if (mStatus.CurState == StIdle)
	{
		if (IsValidDemux(dmx))
		{
			pmp_PmpSend (mPump, EvStart, (Nat32)dmx);
		}
		else
		{
			PrintfNotice (" SimpleMpeg: Wrong Dmx Value..\n");
		}
	}
	else
	{
		PrintfNotice (" SimpleMpeg: Not in Idle Mode. Not Starting the Filters again.. \n");
	}
}
    
void CHsvSimpleMpegDataManager_Priv::enable_Disable(HsvDemux dmx)
{
	SET_STATE(StIdle);
	pmp_PmpSend (mPump, EvStop, (Nat32)dmx);
}
    
void CHsvSimpleMpegDataManager_Priv::enable_Sync   (HsvDemux dmx)
{
	UNUSED (dmx);
}

/* provides IHsvStream	simplepatstrapi */

int CHsvSimpleMpegDataManager_Priv::simplepatstrapi_GetSize   ( HsvDestination inst, int prop )
{
    int         retval  = 0;
    HsvDemux    dmx;

    dmx = HSV_MAP_DEST_TO_DMX(inst);

    if(ProgramTables[dmx].TablesInitialized == TRUE)
    {
        switch(prop)
        {
        case HSVSPID(Program, mpeg, simplepat):
            retval = ProgramTables[dmx].patsec.NumPrograms;
            break;
        default:
            ASSERT(! "Invalid Property called with this function");
            break;
        }
    }
    else
    {
        /* Clients blindly query even when SDM is not started ! */
        //LogError( log_SoftErr, MPEG_INVALID_QUERY );
    }
    
    return retval;
}


Bool CHsvSimpleMpegDataManager_Priv::simplepatstrapi_GetIndex  ( HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool        retval = FALSE;
    HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(inst);


    UNUSED(key2);
    UNUSED(key3);
    if(ProgramTables[dmx].TablesInitialized == TRUE)
    {
        switch(prop)
        {
        case HSVSPID(Program, mpeg, simplepat):
            {
                int i = -1;
                for(i = 0; i < ProgramTables[dmx].patsec.NumPrograms; i++)
                {
                    if( key1 == (int )ProgramTables[dmx].patsec.ProgramNumber[i] )
                    {
                        retval = TRUE;
                        *index = i;
                        break;
                    }
                }
            break;
            }
        default:
            ASSERT(! "Invalid Property called with this function");
            break;
        }
    }
    else
    {
        /* Clients blindly query even when SDM is not started ! */
        //LogError( log_SoftErr, MPEG_INVALID_QUERY );
    }

    return retval;
}

Bool CHsvSimpleMpegDataManager_Priv::simplepatstrapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	return FALSE;
}


Bool CHsvSimpleMpegDataManager_Priv::simplepatstrapi_GetByKey  ( HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool        retval = FALSE;
    HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(inst);
    
    UNUSED(key2);
    UNUSED(key3);
    if(ProgramTables[dmx].TablesInitialized == TRUE)
    {
        switch(prop)
        {
        case HSVSPID(Program, mpeg, simplepat):
            {
                int i = -1;
                for(i = 0; i < ProgramTables[dmx].patsec.NumPrograms; i++)
                {
                    if( key1 == (int )ProgramTables[dmx].patsec.ProgramNumber [i] )
                    {
                        HsvPATProgramPIDInfo *pval = (HsvPATProgramPIDInfo *)val;
                        pval->ProgramNumber =   ProgramTables[dmx].patsec.ProgramNumber [i];
                        pval->Pid           =   ProgramTables[dmx].patsec.ProgramMapPid [i];
                        retval = TRUE;
                        break;
                    }
                }
            break;
            }

        default:
            ASSERT(! "Invalid Property called with this function");
            break;
        }
    }
    else
    {
        /* Clients blindly query even when SDM is not started ! */
        //LogError( log_SoftErr, MPEG_INVALID_QUERY );
    }
    return retval;
}


Bool CHsvSimpleMpegDataManager_Priv::simplepatstrapi_GetByIndex( HsvDestination inst, int prop , int index, void *val)
{
    Bool        retval = FALSE;
    HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(inst);

    if(ProgramTables[dmx].TablesInitialized == TRUE)
    {
        switch(prop)
        {
        case HSVSPID(Program, mpeg, simplepat):
            {
                if( index < ProgramTables[dmx].patsec.NumPrograms )
                {
                    HsvPATProgramPIDInfo *pval = (HsvPATProgramPIDInfo *)val;
                    pval->ProgramNumber =   ProgramTables[dmx].patsec.ProgramNumber [index];
                    pval->Pid           =   ProgramTables[dmx].patsec.ProgramMapPid [index];
                    retval = TRUE;
                }                
            break;
            }
        default:
            ASSERT(! "Invalid Property called with this function");
            break;
        }
    }
    else
    {
        /* Clients blindly query even when SDM is not started ! */
        //LogError( log_SoftErr, MPEG_INVALID_QUERY );
    }
    
    return retval;
}


/* provided interface simplepmtstrapi */

int CHsvSimpleMpegDataManager_Priv::simplepmtstrapi_GetSize        ( HsvDestination dest, int spid )
{
	int		retval = 0;

	switch (spid)
	{
	case	HSVSPID(PidInfo, mpeg,simplepmt):
		retval = srtdb_GetNoOfRecords(SIMPLE_PMT_SORTEDTABLE_ID((HSV_MAP_DEST_TO_DMX(dest)))); 
		break;
	case HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt):
		retval = srtdb_GetNoOfRecords(srtdbids_SimplepmtFreesatTunnelledInfo);
		break;
	default:
		ASSERT(! "Invalid Property called with this function");
		break;
	}

	return retval;
}

/* provides IHsvStream	simplepmtstrapi */
   
Bool CHsvSimpleMpegDataManager_Priv::simplepmtstrapi_GetIndex       ( HsvDestination dest, int spid, int key1, int key2, int key3, int *index)
{
	Bool		retval = FALSE;

	switch (spid)
	{
	case	HSVSPID(PidInfo, mpeg,simplepmt):
		retval = srtdb_SearchOnKey(SIMPLE_PMT_SORTEDTABLE_ID((HSV_MAP_DEST_TO_DMX(dest))), key1, key2, key3,0, (int *)&index); 
		break;
	case HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt):
		srtdb_SearchOnKey(srtdbids_SimplepmtFreesatTunnelledInfo, key1, 0, 0,0, (int *)&index);
		break;
	default:
		ASSERT(! "Invalid Property called with this function");
		break;
	}

	return retval;
}
    
Bool CHsvSimpleMpegDataManager_Priv::simplepmtstrapi_GetByKey ( HsvDestination dest, int spid, int key1, int key2, int key3, void *val)
{
	Bool		retval = FALSE;

	switch (spid)
	{
	case HSVSPID(PidInfo, mpeg,simplepmt):
		retval = srtdb_QueryOnKey(SIMPLE_PMT_SORTEDTABLE_ID((HSV_MAP_DEST_TO_DMX(dest))), key1, key2, key3, 0,(Address)val);
		break;
	case HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt):
		if(key1)
		{
			retval = srtdb_QueryOnKey(srtdbids_SimplepmtFreesatTunnelledInfo, key1, 0, 0, 0,(Address)val);
		}
		else if(key1 == 0)
		{
			retval = srtdb_QueryOnKey(srtdbids_SimplepmtFreesatTunnelledInfo,mFreesatServiceId,0, 0, 0,(Address)val);
		}
		break;
	default:
		ASSERT(! "Invalid Property called with this function");
		break;
	}

	return retval;
}
    
Bool CHsvSimpleMpegDataManager_Priv::simplepmtstrapi_GetRangeByKey  ( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
	Bool	retval = FALSE;
	UNUSED (dest);
	UNUSED (spid);
	UNUSED (noofkeys);
	UNUSED (key1);
	UNUSED (key2);
	UNUSED (key3);
	UNUSED (from);
	UNUSED (to);
	return retval;
}
    
Bool CHsvSimpleMpegDataManager_Priv::simplepmtstrapi_GetByIndex     ( HsvDestination dest, int spid, int index, void *val)
{
	Bool		retval = 0;

	switch (spid)
	{
	case	HSVSPID(PidInfo, mpeg,simplepmt):
		retval = srtdb_QueryOnIndex(SIMPLE_PMT_SORTEDTABLE_ID((HSV_MAP_DEST_TO_DMX(dest))), index, (Address)val);
		break;
	case HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt):
		retval = srtdb_QueryOnIndex(srtdbids_SimplepmtFreesatTunnelledInfo, index,(Address)val);
		break;
	default:
		ASSERT(! "Invalid Property called with this function");
		break;
	}

	return retval;
}




Bool CHsvSimpleMpegDataManager_Priv::Pat_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    TypePat_Parser  Pat_Parser;
    Bool retval = TRUE;
    int dummy , tsloopIndex = 0, tableLen = 0;
	int temp_code;

	memset (&Pat_Parser, 0x00, sizeof(Pat_Parser));
	if( sec_SctArrived & code )
	{

		if (secondarySectionSize > 0)
		{  
			memcpy(ptr, PrimarySectionStartAddress, primarySectionSize); 
			memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
		}  
		else
		{
			ptr = PrimarySectionStartAddress;
		}

		v32 = GET32(0);
		tableLen = HSV_GETSECTION_LENGTH(ptr);

		Pat_Parser.TsLoopDataNum=0;
		Pat_Parser.TableId = GETNBITS(v32,0,8);
		dummy = GETNBITS(v32,8,1);
		dummy = GETNBITS(v32,9,1);
		dummy = GETNBITS(v32,10,2);
		Pat_Parser.SectionLength = GETNBITS(v32,12,12);

		v32 = GET32( 3);
		Pat_Parser.TSID = GETNBITS(v32,0,16);

		dummy = GETNBITS(v32,16,2);
		Pat_Parser.version_number = GETNBITS(v32,18,5);

		dummy = GETNBITS(v32,23,1);
		dummy = GETNBITS(v32,24,8);
		v32 = GET32( 7);
		dummy = GETNBITS(v32,0,8);
		ptr += 8;
		tableLen = tableLen - 8;

		v32 = GET32( 0);

		while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
		{
			Pat_Parser.TsLoopData[tsloopIndex].ProgramNumber = GETNBITS(v32, 0,16);
			dummy = GETNBITS(v32,16,3);
			Pat_Parser.TsLoopData[tsloopIndex].PID = GETNBITS(v32, 19,13);
			ptr += 4;
			tableLen -= 4;
			v32 = GET32( 0);
			tsloopIndex++;
			Pat_Parser.TsLoopDataNum++;
			
			temp_code = sec_SctArrived;
			temp_code |= (cookie << 16);
			retval = retval && ipop_PopulatePAT(demux, (Address)&Pat_Parser , temp_code);
			tsloopIndex = 0;
			Pat_Parser.TsLoopDataNum = 0;
		}
		dummy = GETNBITS(v32,0,32);
	}
	if ((code & 0xFFFF) & sec_TableCompleted)
	{
		temp_code = sec_TableCompleted;
		temp_code |= (cookie << 16);
		retval = retval && ipop_PopulatePAT(demux, (Address) &Pat_Parser , temp_code);
	}

	UNUSED (crc);
	return TRUE;
}

Bool CHsvSimpleMpegDataManager_Priv::Pmt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
	
	register Nat8 *ptr = mBuffer;
	register int v32=0;
	HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
	TypePmt_Parser  Pmt_Parser;
	Bool retval = TRUE;
	int dummy, loopcount = 0;
	int tsloopIndex = 0, tableLen = 0;
	int temp_code;
	Nat8 descTag = 0;
	Nat8 descLen = 0;
	Nat16 descLoopLen = 0;
	Nat32 ParsedPDSD = 0;
	int installedPackageId = 0;

	if( sec_SctArrived & code )
	{
		if (secondarySectionSize > 0)
		{  
			memcpy(ptr, PrimarySectionStartAddress, primarySectionSize); 
			memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);
		}  
		else
		{
			ptr = PrimarySectionStartAddress;
		}

		v32 = GET32(0);
		tableLen = HSV_GETSECTION_LENGTH(ptr);
		Pmt_Parser.TsLoopDataNum=0;
		Pmt_Parser.TableId = GETNBITS(v32,0,8);
		dummy = GETNBITS(v32,8,1);
		dummy = GETNBITS(v32,9,1);
		dummy = GETNBITS(v32,10,2);
		Pmt_Parser.SectionLength = GETNBITS(v32,12,12);
		v32 = GET32( 3);
		Pmt_Parser.ProgramNumber = GETNBITS(v32,0,16);
        TraceNotice(m,"ProgramNumber %d\n", Pmt_Parser.ProgramNumber);
		dummy = GETNBITS(v32,16,2);
		Pmt_Parser.VersionNumber = GETNBITS(v32,18,5);
		dummy = GETNBITS(v32,23,1);
		dummy = GETNBITS(v32,24,8);
		v32 = GET32( 7);
		dummy = GETNBITS(v32,0,8);
		dummy = GETNBITS(v32,8,3);
		Pmt_Parser.PCR_PID = GETNBITS(v32,11,13);
		dummy = GETNBITS(v32,24,4);
		v32 = GET32( 10);
		Pmt_Parser.ProgramInfoLen = GETNBITS(v32,4,12);
		ptr += 12;
		tableLen = tableLen - 12;

		/* Skipping program Info */
		//ptr += Pmt_Parser.ProgramInfoLen;
		Pmt_Parser.FreesatTunnelledDataDescNum = 0;

		installedPackageId = ins_GetAttribute(ins_InstallationServiceScan, ins_AttributePackageId);
		
		
		v32 = GET32(0);
		
		//TraceNotice(m,"%s Pmt_Parser.ProgramInfoLen %d & loop count %d",__FUNCTION__,Pmt_Parser.ProgramInfoLen,loopcount);
		while(loopcount < Pmt_Parser.ProgramInfoLen)
		{
			descTag = GETNBITS(v32,0,8);
			descLen = GETNBITS(v32,8,8);
			//TraceNotice(m,"LINE %d Desc Tag %d Desc Len %d",__LINE__,descTag,descLen);
			switch(descTag)
			{
				case FREESAT_TUNNELLED_DATA_DESCRIPTOR:
					if(installedPackageId == FREESAT_PACKAGE_ID) 
					{	
					ptr += 2;
					descLoopLen = 0;

					while((Pmt_Parser.FreesatTunnelledDataDescNum < FREESAT_MAX_TUNNELLED_DATA_DESC_COUNT) && (descLoopLen < descLen))
					{
						v32 = GET32(descLoopLen);
						Pmt_Parser.FreesatTunnelledData_Descriptor[Pmt_Parser.FreesatTunnelledDataDescNum].DescriptorTag = descTag;
						Pmt_Parser.FreesatTunnelledData_Descriptor[Pmt_Parser.FreesatTunnelledDataDescNum].DescriptorLen = descLen;
						Pmt_Parser.FreesatTunnelledData_Descriptor[Pmt_Parser.FreesatTunnelledDataDescNum].PrivateDataSpecifier = ParsedPDSD;
						Pmt_Parser.FreesatTunnelledData_Descriptor[Pmt_Parser.FreesatTunnelledDataDescNum].ServiceId = Pmt_Parser.ProgramNumber;
						Pmt_Parser.FreesatTunnelledData_Descriptor[Pmt_Parser.FreesatTunnelledDataDescNum].TunnelledDataType = GETNBITS(v32,0,8);
						Pmt_Parser.FreesatTunnelledData_Descriptor[Pmt_Parser.FreesatTunnelledDataDescNum].ComponentTag = GETNBITS(v32,8,8);
						Pmt_Parser.FreesatTunnelledDataDescNum ++;
						descLoopLen += 2;
					}
						
					}else {
						ptr += 2;
					}
					loopcount += 2+descLen;
					ptr += descLen;
					v32 = GET32(0);
					//TraceNotice(m,"Parsing of FREESAT_TUNNELLED_DATA_DESCRIPTOR done: %d",Pmt_Parser.FreesatTunnelledDataDescNum);
					break;
				case PRIVATE_DATA_SPECIFIER_DESCRIPTOR:
					ParsedPDSD = GET32( 2);
					ptr += 2 + descLen;
					loopcount += 2 + descLen;
					v32 = GET32( 0);
					//TraceNotice(m,"PDSD parsed: %d",ParsedPDSD);
					break;
				case PRIVATE_DATA_INDICATOR_DESCRIPTOR:/*Private data indicator descriptor*/
					/*If private data indicator descriptor is found then reset the PDSD valuse, since the scope ends there
					**reference Section 4.1.1- Free Satellite Requirements for Interoperability Part 3: System Management V1.6
					*/
					ParsedPDSD = 0;
					loopcount += 2 + descLen;
					ptr +=2 + descLen;
					v32 = GET32(0);
					break;
				default:
					ptr +=  2 + descLen;
					loopcount += 2+descLen;
					v32 = GET32(0);
					break;
			}
		}
		tableLen = tableLen - Pmt_Parser.ProgramInfoLen;
		v32 = GET32( 0);
		//TraceNotice(m,"tableLen %d & tsloopIndex %d",tableLen,tsloopIndex);
		while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < MAX_ES_PER_SERVICE))
		{
			Bool Ac3Avail = FALSE;
			v32 = GET32( 0);
			Pmt_Parser.TsLoopData[tsloopIndex].StreamType = GETNBITS(v32, 0,8);
			dummy = GETNBITS(v32,8,3);
			Pmt_Parser.TsLoopData[tsloopIndex].BasicPID = GETNBITS(v32, 11,13);
			dummy = GETNBITS(v32,24,4);
			v32 = GET32( 3);
			Pmt_Parser.TsLoopData[tsloopIndex].TsDescLoopLen = GETNBITS(v32, 4,12);
			ptr += 5;
			tableLen = tableLen - 5;
			//TraceNotice(m,"tableLen %d TsDescLoopLen %d Stream Type %d Basic PID %d",tableLen,Pmt_Parser.TsLoopData[tsloopIndex].TsDescLoopLen,Pmt_Parser.TsLoopData[tsloopIndex].StreamType,Pmt_Parser.TsLoopData[tsloopIndex].BasicPID);
			loopcount = 0;
			Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum = 0;
			Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum = 0;
			v32 = GET32(0);
			//TraceNotice(m,"TsDescLoopLen %d",Pmt_Parser.TsLoopData[tsloopIndex].TsDescLoopLen);
			
			while(loopcount < Pmt_Parser.TsLoopData[tsloopIndex].TsDescLoopLen)
			{
				
				
				descTag = GETNBITS(v32,0, 8); 
				descLen = GETNBITS(v32,8, 8); 
				//TraceNotice(m,"LINE %d Desc Tag %d Desc Len %d",__LINE__,descTag,descLen);
				switch(descTag) 
				{
		            	
	       			case STREAM_IDENTIFIER_DESCRIPTOR: /*Stream identifier descriptor*/
						/*Parse stream identifier descriptor only if stream type is 0.x05
						**This descri[tor is required only by free satellite tunnelled data descriptor
						**to identify tunnelled PID
						*/
						if((0x05 == Pmt_Parser.TsLoopData[tsloopIndex].StreamType) && (Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum < MAX_STREAM_IDENTIFIER_DESCRIPTOR_PER_LOOP))
						{
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescriptor[Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum].DescriptorTag = descTag;
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescriptor[Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum].DescriptorLen = descLen;
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescriptor[Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum].ServiceId = Pmt_Parser.ProgramNumber;
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescriptor[Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum].StreamType = Pmt_Parser.TsLoopData[tsloopIndex].StreamType;
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescriptor[Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum].BasicPID = Pmt_Parser.TsLoopData[tsloopIndex].BasicPID;
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescriptor[Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum].ComponentTag = GETNBITS(v32,16, 8);
							Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum++;
						}
						loopcount += 2 + descLen;
						ptr += 2 + descLen;
						v32 = GET32(0);
						//TraceNotice(m,"Parsing of STREAM_IDENTIFIER_DESCRIPTOR done: %d",Pmt_Parser.TsLoopData[tsloopIndex].StreamIdentifierDescNum);
					break;
					
					case FREESAT_ALT_TUNNELLED_DATA_DESCRIPTOR: /*free satellite alt tunnelled data descriptor*/
						if(installedPackageId == FREESAT_PACKAGE_ID) 
						{
						descLoopLen = 0;
						ptr += 2;
						if(0x05 == Pmt_Parser.TsLoopData[tsloopIndex].StreamType)
						{
							while((Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum < FREESAT_MAX_ALT_TUNNELLED_DATA_DESC_COUNT) && (descLoopLen < descLen))
							{
								v32 = GET32(descLoopLen);
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].PrivateDataSpecifier = ParsedPDSD;
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].DescriptorTag = descTag;
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].DescriptorLen = descLen;
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].ServiceId = Pmt_Parser.ProgramNumber;
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].StreamType = Pmt_Parser.TsLoopData[tsloopIndex].StreamType;
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].BasicPID = Pmt_Parser.TsLoopData[tsloopIndex].BasicPID;
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledData_Descriptor[Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum].TunnelledDataType = GETNBITS(v32,0, 8);
								Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum++;
								descLoopLen ++;
							}
							}
						} else {
							ptr += 2;
						}
						loopcount += 2 + descLen;
						ptr += descLen;
						v32 = GET32(0);
						//TraceNotice(m,"Parsing of FREESAT_ALT_TUNNELLED_DATA_DESCRIPTOR done: %d",Pmt_Parser.TsLoopData[tsloopIndex].FreesatAltTunnelledDataDescNum);
						break; 
						
					case AC3_DESCRIPTOR: /*AC-3 descriptor*/
						if(0x06 == Pmt_Parser.TsLoopData[tsloopIndex].StreamType)
						{
							Ac3Avail = TRUE;
						}
						ptr += 2 + descLen;
						loopcount += 2 + descLen;
						v32 = GET32( 0);
						break;
					
					case PRIVATE_DATA_SPECIFIER_DESCRIPTOR:
						ptr += 2;
						ParsedPDSD = GET32(0);
						loopcount +=  2+descLen;
						ptr += descLen;
						v32 = GET32(0);
					break;
					
					case PRIVATE_DATA_INDICATOR_DESCRIPTOR:/*Private data indicator descriptor*/
						/*If private data indicator descriptor is found then reset the PDSD valuse, since the scope ends there
						**reference Section 4.1.1- Free Satellite Requirements for Interoperability Part 3: System Management V1.6
						*/
						ParsedPDSD = 0;
						loopcount += 2 + descLen;
						ptr += 2 + descLen;
						v32 = GET32(0);
					break;
					
		            default:
						loopcount += 2 + descLen;
						ptr += 2 + descLen;
						v32 = GET32( 0);
						break;
		            }//endswitch
	        }

			if((0x06 == Pmt_Parser.TsLoopData[tsloopIndex].StreamType) && (!Ac3Avail))
			{
				TraceDebug (m,"JENI_SKIPPING_TELETEXT" );
				Pmt_Parser.TsLoopData[tsloopIndex].StreamType = 0;
			}

			tableLen = tableLen - Pmt_Parser.TsLoopData[tsloopIndex].TsDescLoopLen;
			tsloopIndex++;
		}

		Pmt_Parser.TsLoopDataNum = tsloopIndex;
			
		temp_code = sec_SctArrived;
		temp_code |= (cookie << 16);
		retval = retval && ipop_PopulatePMT(demux,(Address) &Pmt_Parser,temp_code );
		//tsloopIndex = 0;
		//Pmt_Parser.TsLoopDataNum = 0;
		
	}
	if ((code & 0xFFFF) & sec_TableCompleted)
	{
		temp_code = sec_TableCompleted;
		temp_code |= (cookie << 16);
		retval = retval && ipop_PopulatePMT(demux,(Address) &Pmt_Parser,temp_code );
	}

	UNUSED (crc);
	return TRUE;
}
