#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define     DATA_TIMEOUT                    (20000)

#define     SET_BACKGROUND_STATE(state)     (mInstStatus.State = state)

#define     SDT_OTHER_TABLE_ID              (0x46)

#define     VALID_EVENT(Event)              ((Event >= EvDataAvailable) && (Event < EvMax))

#define     VALID_STATE(state)              ((state >= StIdle) && (state < StMax))

#define     NO_DATA                         (0x0)

#define     NIT_DATA                        (0x1)

#define     SDT_DATA                        (0x2)

#define		MAX_RETRYIN_SYNC				(10)

#define 	MAX_DATABASE_SYNC	    		5
#define     PTC_TABLE                       (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define		PRESETTABLE						(pgdb_GetCurrentTable() | pgdbconst_Preset)
#define		SERVICE_TABLE					(pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define		FREQMAP_TABLE					(pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)
#define 	ANALOG_TABLE					(pgdb_GetCurrentTable() | pgdbconst_Analog)
#define		BACKGROUND_SDT_OTHER_TIMEOUT	(20*1000)

#define VALID_BARKERMUX_FOUND       ( (mBarkerMuxONID != 0xFFFF) && (mBarkerMuxTSID != 0xFFFF) )

#define 	PERFORM_DATABASE_SYNC(DbToSync,FromDatabaseId,ToDatabaseId,Index,TotalNumberOfEntries,Data) 	pgdb_SelectActiveChannelDatabase(FromDatabaseId);\
		TotalNumberOfEntries = pgdb_GetNoRecords(DbToSync);\
		TraceNotice (m, "Number of entries for %d is %d ", DbToSync, TotalNumberOfEntries);\
		if (TotalNumberOfEntries)\
		{\
			RetryCount = 0;\
			for (Index = 0; Index < TotalNumberOfEntries; Index++, RetryCount++)\
			{\
				pgdb_SelectActiveChannelDatabase(FromDatabaseId);\
				if (TRUE == pgdb_GetByIndex(DbToSync, Index, (Address) &Data))\
				{\
					pgdb_SelectActiveChannelDatabase(ToDatabaseId);\
					if (TRUE != pgdb_AddInIndex (DbToSync, Index, &Data))\
					{\
						TraceNotice (m, "Ziggo/Telenet pgdbAddIndex failed for Table %d Index %d ", DbToSync, Index);\
					}\
				}\
				else \
				{\
					TraceNotice (m, "Ziggo/Telenet SyncDatabase failed for count %d Index %d . Retrying.. From %d To %d  ", DbToSync, Index, FromDatabaseId, ToDatabaseId);\
					usleep (50000);\
					if (RetryCount < MAX_RETRYIN_SYNC) \
						Index--;\
				}\
			}\
		}

#define	PERFORM_REMOVEDSVCDELETION(Table,SqliteId,TempId,Index,TotalEntries,Data,TempData) 	\
	pgdb_SelectActiveChannelDatabase(SqliteId);\
	TotalEntries = pgdb_GetNoRecords(Table);\
	for (Index = TotalEntries - 1; Index >=0; Index--)\
	{\
		pgdb_SelectActiveChannelDatabase(SqliteId);\
		if (TRUE == pgdb_GetByIndex (Table,Index,(Address)&TempData))\
		{\
			mAssignPgdbKeys(Table,(Address)&Data, (Address)&TempData);\
			pgdb_SelectActiveChannelDatabase(TempId);\
			if(FALSE == pgdb_GetByKey(Table,(Address)&Data))\
			{\
				pgdb_SelectActiveChannelDatabase(SqliteId);\
				pgdb_Delete(Table,(Address)&TempData);\
			}\
		}\
	}

#define 	PERFORM_DATABASE_ADDUPDATE(DbToSync,FromDatabaseId,ToDatabaseId,Index,TotalNumberOfEntries,Data,TempData) 	\
	pgdb_SelectActiveChannelDatabase(FromDatabaseId);\
	TotalNumberOfEntries = pgdb_GetNoRecords(DbToSync);\
	TraceNotice (m, "Ziggo/Telenet Number of entries for %d is %d ", count, TotalNumberOfEntries);\
	if (TotalNumberOfEntries)\
	{\
		for (Index = 0; Index < TotalNumberOfEntries; Index++)\
		{\
			pgdb_SelectActiveChannelDatabase(FromDatabaseId);\
			if (TRUE == pgdb_GetByIndex(DbToSync, Index, (Address) &TempData))\
			{\
				pgdb_SelectActiveChannelDatabase(ToDatabaseId);\
				mAssignPgdbKeys(DbToSync,(Address)&Data, (Address)&TempData);\
				if(FALSE == pgdb_GetByKey(DbToSync,(Address)&Data))\
				{\
					if (TRUE != pgdb_Add (DbToSync, (Address)&TempData))\
					{\
						TraceNotice (m, "Ziggo/Telenet pgdbAdd failed for DbToSync %d Index %d ", DbToSync, Index);\
					}\
				}\
				else\
				{\
					pgdb_Update (DbToSync, (Address)&TempData);\
				}\
			}\
			else \
			{\
				TraceNotice (m, "Ziggo/Telenet SyncDatabase failed for count %d Index %d . Retrying.. From %d To %d  ", count, Index, FromDatabaseId, ToDatabaseId);\
				usleep (50000);\
				Index--;\
			}\
		}\
	}

	
	
#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define PLF_TUNING_DVBC_QAM16           (1)
#define PLF_TUNING_DVBC_QAM32           (2)
#define PLF_TUNING_DVBC_QAM64           (3)
#define PLF_TUNING_DVBC_QAM128          (4)
#define PLF_TUNING_DVBC_QAM256          (5)

typedef enum
{
    StIdle,
    StNITAcquistion,
    StSorting,
    StMax
}BackgroundStates;
typedef enum
{
    EvDataAvailable,
    EvStop,
    EvComplete,
	EvSdtOtherTimeout,
    EvMax
}BackgroundEvents;
typedef struct 
{
    int         State;
    Bool        TargeNITFound;
    int         TargetNITType;
    Nat16       TargetNITValue;
    Bool        SDTOtherScan;
}InstStatus;
typedef struct
{
    Nat8 TargetNITType;
    Nat16 TargetNITValue;
    Nat8 NumOfTs;
    int CurrentTsIndex; 
    struct 
    {
        Nat16 ONID;
        Nat16 Tsid;
        Bool Installed;
        Nat8 NumOfCDSD;
        int CurrentCDSDIndex;
        struct
        {
            Nat32 SymbolRate;
            Nat32 Frequency;
            Nat8 Modulation;
        }CableDesc[MAX_CDSD_PER_TS];
    }TsLoop[MAX_MUXES_PER_NTK];
}t_CanalDigitalCableDSDesc;
typedef void (CLASSSCOPE *FunctionVoid)();
#ifndef __cplusplus

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

InstStatus mInstStatus;
static InstStatus s__mInstStatus;
t_CanalDigitalCableDSDesc mCableDSDesc;
static t_CanalDigitalCableDSDesc s__mCableDSDesc;
Nat16 mBarkerMuxONID,mBarkerMuxTSID;
static Nat16 s__mBarkerMuxONID,s__mBarkerMuxTSID;
Bool VersionUpdateNeeded;
static Bool s__VersionUpdateNeeded;
static const FunctionVoid EventActionMatrix[][StMax];
Bool mActive,mDirtyBit,mDataAcquistion,mPresetChanged,mLowestPreset;
static Bool s__mActive,s__mDirtyBit,s__mDataAcquistion,s__mPresetChanged,s__mLowestPreset;
Pump mInstallPump;
static Pump s__mInstallPump;
Bool mServiceUpdateInProgress;
Bool mBackgroundUpdateInProgress;
static Bool s__mBackgroundUpdateInProgress;
static Bool s__mServiceUpdateInProgress;
void mPumpHandler(int event, Nat32 param);
inline void FuncStartInstallation(void);
inline void FuncStopInstallation(void);
inline void FuncComplete(void);
inline void FuncSdtOtherComplete(void);
inline void mInitialise(void);
inline Bool mAcquireValidNit(void);
Nat8 mGetVersion(int TableData);
Nat16 OnId,SrvId,TsId,CachedPresetnumber;
static Nat16 s__OnId,s__SrvId,s__TsId,s__CachedPresetnumber;
Nat32 CachedFrequency;
static Nat32 s__CachedFrequency;
Bool mServiceNameUpdated;
static Bool s__mServiceNameUpdated;
Bool mNitUpdatedAlsoHappened;
static Bool s__mNitUpdatedAlsoHappened;
#ifndef __cplusplus

#endif

Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
inline int mGetSDTType(Nat16 Frequency);
inline void mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid);
inline Bool mLoadCDSDFromStrapi(int hsvspid);
inline Bool mGetAltTSValues(Nat16* ONID, Nat16* TSID);
inline void mGetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID);
Bool mCheckVisibleService(HsvPgdatPresetData* preset);
void mClearAndSyncDatabase(void);
void mAddOrUpdateServiceRecords(void);
void mDeleteServicesRemoved (void);
void mAssignPgdbKeys (int TableId, Address Data, Address TempData);
void HandleTelenetSdtOtherNameUpdate(HsvDestination dest, int spid, int Onid, int ServiceId, int Tsid, int eventid);
void tuneToLowestPreset();
int mMapFromHsvToPlfDvbcModulation(int type);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mInstStatus	=	s__mInstStatus;
	mCableDSDesc	=	s__mCableDSDesc;
	mBarkerMuxONID	=	s__mBarkerMuxONID;
	mBarkerMuxTSID	=	s__mBarkerMuxTSID;
	VersionUpdateNeeded	=	s__VersionUpdateNeeded;
	OnId = s__OnId;
	SrvId = s__SrvId;
	TsId = s__TsId;
	mActive	=	s__mActive;
	mDirtyBit	=	s__mDirtyBit;
	mDataAcquistion	=	s__mDataAcquistion;
	mInstallPump	=	s__mInstallPump;
	mPresetChanged = s__mPresetChanged;
	mLowestPreset = s__mLowestPreset;
	mServiceUpdateInProgress = s__mServiceUpdateInProgress;
	CachedPresetnumber = s__CachedPresetnumber;
	CachedFrequency  = s__CachedFrequency;
	mBackgroundUpdateInProgress = s__mBackgroundUpdateInProgress;
	mServiceNameUpdated = s__mServiceNameUpdated;
	mNitUpdatedAlsoHappened = s__mNitUpdatedAlsoHappened;
#ifndef __cplusplus

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef DATA_TIMEOUT
#undef DATA_TIMEOUT
#endif //DATA_TIMEOUT
#ifdef SET_BACKGROUND_STATE(state)
#undef SET_BACKGROUND_STATE(state)
#endif //SET_BACKGROUND_STATE(state)
#ifdef SDT_OTHER_TABLE_ID
#undef SDT_OTHER_TABLE_ID
#endif //SDT_OTHER_TABLE_ID
#ifdef VALID_EVENT(Event)
#undef VALID_EVENT(Event)
#endif //VALID_EVENT(Event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef NO_DATA
#undef NO_DATA
#endif //NO_DATA
#ifdef NIT_DATA
#undef NIT_DATA
#endif //NIT_DATA
#ifdef SDT_DATA
#undef SDT_DATA
#endif //SDT_DATA
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef VALID_BARKERMUX_FOUND
#undef VALID_BARKERMUX_FOUND
#endif //VALID_BARKERMUX_FOUND
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#endif //LOCAL_UNDEFINES
