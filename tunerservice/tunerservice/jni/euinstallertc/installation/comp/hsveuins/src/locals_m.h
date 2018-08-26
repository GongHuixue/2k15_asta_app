#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define BACKGROUND_MODE             (rins_InstallationModeBackground) 

#define VALID_EVENT(event)          ((event >= EvStart) && (event < EvMax))

#define VALID_STATE(state)          ((state >= StIdle) && (state < StMax))

#define USER_SELECTION_DONE         (0xFFFFFFFF)            /* high value given just to differentiate b/w other values sent */

#define VALID_BARKERMUX_FOUND ( (mBarkerMuxONID != 0xFFFF) && (mBarkerMuxTSID != 0xFFFF) )

#define	MAX_SWITCHCASE_PRGCOUNT		(10)

#define MAX_NUM_LCN_ENTRY			8

#define MAX_NUM_PRESET_ENTRY		MAX_NUM_LCN_ENTRY

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define 	PERFORM_DATABASE_SYNC(DbToSync,FromDatabaseId,ToDatabaseId,Index,TotalNumberOfEntries,Data) 	pgdb_SelectActiveChannelDatabase(FromDatabaseId);\
		TotalNumberOfEntries = pgdb_GetNoRecords(DbToSync);\
		TraceNotice (m, "Number of entries for %d is %d ", count, TotalNumberOfEntries);\
		if (TotalNumberOfEntries)\
		{\
			for (Index = 0; Index < TotalNumberOfEntries; Index++)\
			{\
				pgdb_SelectActiveChannelDatabase(FromDatabaseId);\
				if (TRUE == pgdb_GetByIndex(DbToSync, Index, (Address) &Data))\
				{\
					pgdb_SelectActiveChannelDatabase(ToDatabaseId);\
					if (TRUE != pgdb_AddInIndex (DbToSync, Index, &Data))\
					{\
						TraceNotice (m, "Eu pgdbAddIndex failed for Table %d Index %d ", count, Index);\
					}\ 
				}\
				else \
				{\
					TraceNotice (m, "S2 SyncDatabase failed for count %d Index %d . Retrying.. From %d To %d  ", count, Index, FromDatabaseId, ToDatabaseId);\
					usleep (50000);\
					Index--;\
				}\
			}\
		}


typedef enum
{
    StIdle,
    StSourceSetupWait,
    StDigital,
    StAnalog,
    StPreSorting,
    StSorting,
    StMax
}States;
typedef enum 
{
    EvStart,
    EvStop,
    EvSourceSetupApplied,
    EvMakeDecision,
    EvPreSorting,
    EvSorting,
    EvRemovePresets,
    EvSortComplete,         
    EvSearchInProgress,
    EvMax
}Events;
typedef enum
{
    Initialised = 0,
    TurnedOn,
    TurnedOff
}ModuleLifeCycle;
typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

ModuleLifeCycle mModuleLifeCycle;
static ModuleLifeCycle s__mModuleLifeCycle;
Nat16 mBarkerMuxONID,mBarkerMuxTSID;
static Nat16 s__mBarkerMuxONID,s__mBarkerMuxTSID;
Pump mPump;
static Pump s__mPump;
TypeInstallationStatus InsStatus;
static TypeInstallationStatus s__InsStatus;
Bool InsCompleted;
static Bool s__InsCompleted;
int CurrentFrequency;
static int s__CurrentFrequency;
int LastProgressStatus;
static int s__LastProgressStatus;
int InstallationPassSwitchOver;
static int s__InstallationPassSwitchOver;
Nat16	FullScanNetworkName[MAX_NETWORK_NAME_SIZE];
static const FunctionNat32 EventActionMatrix[][10];
Bool mCamProfile0Installation;
static Bool s__mCamProfile0Installation;
static int s__CurLCNControlMode;

inline void mPumpHandler(int event, Nat32 param);
inline void FuncStartInstallation(Nat32 param);
inline void FuncSourceSetupApplied(Nat32 param);
inline void FuncStopInstallation(Nat32 param);
void FuncMakeDecision(Nat32 param);
inline void FuncPreSorting(Nat32 param);
inline void FuncSorting(Nat32 param);
void FuncSearchInProgress(Nat32 param);
void FuncSortComplete(Nat32 param);
inline void mInitInstallationValues(Nat32 param, Bool InstallStart);
inline Bool mValidInstallMode(int mode);
inline void mUnicodeCopy(Nat16* dest, Nat16* source);
inline void mInstallationDone(void);
int mWaitForUserSelection(void);
inline void mInitInstallationPass(Bool BlockDestionationFlag);
void mStartDigitalInstall(void);
Bool mIsCanalDigitalorYouSeeOperatorSupported(void);
int mCalculateInstallationPass(void);
inline Bool mIsNextPassRequired(void);
HsvConstellation ConvertFromPlatformConstellation(tmFe_Constellation_t inval);
Bool mUpdateBarkerInfo(HsvDestination dest, int spid);
Bool mCheckRadioservice(HsvPgdatPresetData* preset);
Bool mCheckVisibleService(HsvPgdatPresetData* preset);
void DetermineMedium(int *Medium, HsvInstallationPass Pass);
Nat32 DetermineSourceDesignator(HsvStreamType StreamType);
Bool mSourceSetupAndApply(HsvInstallationPass Pass);
void mStoreBarkerMuxData(void);
void mPerformDatabaseSync (int FromDatabaseId, int ToDatabaseId);
void mInitializeTvProviderData (HsvPgdatTvProviderBlobData	*TvProviderData);
void mCollectDigSrvProviderData (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectAnalogProviderData (HsvPgdatAnalogData  *AnalogData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectPresetProviderData(HsvPgdatPresetData *PresetData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectDigTSProviderData (HsvPgdatDigTSData	*DigTsData, HsvPgdatTvProviderBlobData *TvProviderData);
void mCollectFrequencyMapData (	HsvPgdatDigFreqMapData	*FreqData, HsvPgdatTvProviderBlobData *TvProviderData);
void mAddPresetData(HsvPgdatTvProviderBlobData *TvpData);
void mAddAnalogData(HsvPgdatTvProviderBlobData *TvpData);
void mAddDigSrvData(HsvPgdatTvProviderBlobData *TvpData);
void mAddDigTsData(HsvPgdatTvProviderBlobData *TvpData);
void mAddFreqMapData(HsvPgdatTvProviderBlobData *TvpData);
void mGetUniqueIdFromPresetNumber (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData);
void mUpdateUniqueIds (HsvPgdatDigServiceData *DigSrvcData, HsvPgdatTvProviderBlobData *TvpData);
void mSyncUniqueIdToDigitalServiceTable (HsvPgdatTvProviderBlobData *TvpData);
void mSyncUniqueIdToAnalogTable (HsvPgdatTvProviderBlobData *TvpData);
Bool mIsDVBCSpecificAttribute(int attribute);  



void module__init(void){
#ifndef __cplusplus

#else

#endif

	mModuleLifeCycle	=	s__mModuleLifeCycle;
	mBarkerMuxONID	=	s__mBarkerMuxONID;
	mBarkerMuxTSID	=	s__mBarkerMuxTSID;
	mPump	=	s__mPump;
	InsStatus	=	s__InsStatus;
	InsCompleted	=	s__InsCompleted;
	CurrentFrequency	=	s__CurrentFrequency;
	LastProgressStatus	=	s__LastProgressStatus;
	mCamProfile0Installation = s__mCamProfile0Installation;
	FullScanNetworkName[0] = '\0';
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef VALID_EVENT(event)
#undef VALID_EVENT(event)
#endif //VALID_EVENT(event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef USER_SELECTION_DONE
#undef USER_SELECTION_DONE
#endif //USER_SELECTION_DONE
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
