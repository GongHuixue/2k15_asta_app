#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define TV_SERVICE                       (0x01)

#define SIGSTR_WAITTIME                  (1000) /* Every second */

#define MAX_MODULATION_VALS              5

#define MAX_CHARACTERS				     (128)

#define MAX_SEARCH_RATES    (25)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)



/*************************************************************************
  Local Structures and enums
 **************************************************************************/

typedef enum
{
    StIdle = 0,
    StFeWait,
    StDmxWait,
    StDecision,
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
}t_DVBCGridStatus;
typedef struct 
{
    Nat32 StartFrequency;
    Nat32 EndFrequency;
} t_DVBCFreqTable;
typedef void (CLASSSCOPE *FunctionNat32)(int);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

t_DVBCFreqTable ChinaFreqTable[110];
static t_DVBCFreqTable s__ChinaFreqTable[110];
Nat32 FreqTableIndex;
static Nat32 s__FreqTableIndex;
Pump mGridPump;
static Pump s__mGridPump;
t_DVBCGridStatus mDvbcGridStatus;
static t_DVBCGridStatus s__mDvbcGridStatus;
int ModulationVals[MAX_MODULATION_VALS];
static int s__ModulationVals[MAX_MODULATION_VALS];
int mConstellation[14];
static int s__mConstellation[14];
static const FunctionNat32 StateEventMatrix[][StMax];
void PumpHandler(int event, Nat32 param );
void FuncStartInstall(int param);
void FuncStationFound(int param);
void FuncStationNotFound(int param);
void FuncDmxData(int param);
void FuncMakeDecision(int param);
void FuncStop(int param);
void FuncBackground(int param);
void FuncSigStrMeasured(int param);
void mUpdateTunerStatus(void);
void mPlayService(int serviceid);
void mResetInstallationState(void);
int FindHsvValue(int plfval, int* arr, int len);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)ChinaFreqTable,(void*)s__ChinaFreqTable,sizeof(ChinaFreqTable));
	FreqTableIndex	=	s__FreqTableIndex;
	mGridPump	=	s__mGridPump;
	mDvbcGridStatus	=	s__mDvbcGridStatus;
	memcpy((void*)ModulationVals,(void*)s__ModulationVals,sizeof(ModulationVals));
	memcpy((void*)mConstellation,(void*)s__mConstellation,sizeof(mConstellation));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef TV_SERVICE
#undef TV_SERVICE
#endif //TV_SERVICE
#ifdef SIGSTR_WAITTIME
#undef SIGSTR_WAITTIME
#endif //SIGSTR_WAITTIME
#ifdef MAX_MODULATION_VALS
#undef MAX_MODULATION_VALS
#endif //MAX_MODULATION_VALS
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef MAX_SEARCH_RATES
#undef MAX_SEARCH_RATES
#endif //MAX_SEARCH_RATES
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
