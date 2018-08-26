#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define TV_SERVICE                       (0x01)

#define SIGSTR_WAITTIME                  (1000) /* Every second */
#define		PTC_TABLE					(pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define		MAX_TS_FREQUENCIES			(140)
#define		DIFFERENCE_IN_FREQUENCY(Ptc,Cache)		((Ptc > Cache) ? (Ptc - Cache) : (Cache - Ptc))
#define		ALLOWABLE_DRIFT_IN_FREQUENCY	(150)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define MAX_CHARACTERS				     (128)

#define MAX_SEARCH_RATES    (25)


/*************************************************************************
  Local Structures and enums
 **************************************************************************/

typedef enum
{
    StIdle = 0,
    StFeWait,
    StDmxWait,
    StDecision,
    StPMTWait,
    StMax
}States;
typedef enum
{
    EvStart = 0,
    EvStationFound,
    EvStationNotFound,
    EvDmxNtf,
    EvMakeDecision,
    EvStop,
    EvSigStrMeasured,
    EvPMTCollected,
    EvMax
}Events;
typedef struct
{
    States State;
    Nat32 Frequency;
    Nat8 ModulationType;
    Nat8 CodeRateHigh;
    Nat8 CodeRateLow;
    Nat8 ChannelBandwidth;
    Nat8 GuardInterval;
    Nat8 FrequencyOffset;
    Nat8 TxMode;
    Nat8 IqMode; 
    Nat16 ChannelInformation;
    Int32 TimeError;
    Int32 FrequencyError;
    Nat32 SymbolRate;
    HsvDemux CurrentDemux;
    Bool SDTAcquired;
    Bool PlayStarted;
    Bool StationFound;
    tmFe_SearchSymbolRate_t SearchRates[MAX_SEARCH_RATES];
    int SearchRateLen;
    int NumChannelsAdded;
    int NumChannelsRemoved;
    int FirstPresetNumber;
    Bool Active;
    Nat32 EndFrequency;
}t_DVBCFullStatus;
typedef void (CLASSSCOPE *FunctionNat32)(int);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

Pump mFullPump;
static Pump s__mFullPump;
t_DVBCFullStatus mDvbcFullStatus;
static t_DVBCFullStatus s__mDvbcFullStatus;
t_CableDSDesc mFlashCableDS;
static t_CableDSDesc s__mFlashCableDS;
char mDirName[MAX_CHARACTERS];
static char s__mDirName[MAX_CHARACTERS];
char mFileName[MAX_CHARACTERS];
static char s__mFileName[MAX_CHARACTERS];
Nat32 mCacheFrequency[MAX_TS_FREQUENCIES];
static Nat32 s__mCacheFrequency[MAX_TS_FREQUENCIES];
static const FunctionNat32 StateEventMatrix[][StMax];
void PumpHandler(int event, Nat32 param );
void FuncStartInstall(int param);
void FuncStationFound(int param);
void FuncStationNotFound(int param);
void FuncDmxData(int param);
void FuncMakeDecision(int param);
void FuncPMTCollected (int param);
void FuncStop(int param);
void FuncBackground(int param);
void FuncSigStrMeasured(int param);
void mUpdateTunerStatus(void);
void mPlayService(int serviceid);
int mGetSymbolRates( tmFe_SearchSymbolRate_t *SearchRates, int *SearchRateLen );
int mGetSymbolRatesNordic( int country, tmFe_SearchSymbolRate_t *SearchRates, int *SearchRateLen );
int mGetSymbolRatesOthers(tmFe_SearchSymbolRate_t *SearchRates, int *SearchRateLen);
void mResetInstallationState(void);
void mResetCableDSLen();
void mGetPathNameFull(char* dirName, char* FileName , char* PathName);
int FindHsvValue(int plfval, int* arr, int len);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mFullPump	=	s__mFullPump;
	mDvbcFullStatus	=	s__mDvbcFullStatus;
	mFlashCableDS	=	s__mFlashCableDS;
	memcpy((void*)mDirName,(void*)s__mDirName,sizeof(mDirName));
	memcpy((void*)mFileName,(void*)s__mFileName,sizeof(mFileName));
	memcpy((void*)mCacheFrequency,(void*)s__mCacheFrequency,sizeof(mCacheFrequency));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef TV_SERVICE
#undef TV_SERVICE
#endif //TV_SERVICE
#ifdef SIGSTR_WAITTIME
#undef SIGSTR_WAITTIME
#endif //SIGSTR_WAITTIME
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
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef MAX_SEARCH_RATES
#undef MAX_SEARCH_RATES
#endif //MAX_SEARCH_RATES
#endif //LOCAL_UNDEFINES
