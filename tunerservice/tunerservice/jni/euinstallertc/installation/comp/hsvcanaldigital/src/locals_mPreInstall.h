#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define INVALID_NETWORKID   (0xFFFF)

#define ISONID_VALID(value)             (((value >= 0xFF00) && (value <= 0xFFFF))? FALSE:TRUE)
/* pavan: should be a different div */

#define VALID_NTKID(ntkid)  (((ntkid) >= (0xFF01))? (FALSE) : (TRUE))

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
    StInit,
    StFeWait,
    StDmxWait,
    StDecision,
	StWaitAbort,
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
    EvSdmStopped,
    EvMax
}Events;
typedef enum
{
    DvbcPreScanIdle,
    DvbcPreScanScanningDefaultList,
    DvbcPreScanScanningNetworkFreq
}t_DVBCPreScanScanStates;
typedef struct
{
    States State;
    Nat32 Frequency;
    Nat8 ModulationType;
    Nat32 SymbolRate;
    HsvDemux CurrentDemux;

    tmFe_SearchSymbolRate_t SearchRates[MAX_SEARCH_RATES];
    int SearchRateLen;
    Bool Active;
    Nat32 StartFrequency;
    Nat32 EndFrequency;
    Nat8 FrequencyMode;
    t_DVBCPreScanScanStates   ScanState;
}t_DVBCPreScanStatus;

typedef void (CLASSSCOPE *FunctionNat32)(int);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

t_DVBCPreScanStatus mInstStatus;
static t_DVBCPreScanStatus s__mInstStatus;
Pump mInstallPump;
static Pump s__mInstallPump;
int mConstellation[14];
static int s__mConstellation[14];
static const FunctionNat32 StateEventMatrix[][StMax];
void PumpHandler(int event, Nat32 param );
void FuncSdmStopped(int param);
void FuncStartInstall(int param);
void FuncStationFound(int param);
void FuncStationNotFound(int param);
void FuncDmxData(int param);
void FuncMakeDecision(int param);
void FuncStop(int param);
void FuncScanAborted (int param);
Bool mOnNitAvailable();
void mResetInstallationState(void);
void mStopSdm(HsvDemux dmx);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mInstStatus	=	s__mInstStatus;
	mInstallPump	=	s__mInstallPump;
	memcpy((void*)mConstellation,(void*)s__mConstellation,sizeof(mConstellation));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INVALID_NETWORKID
#undef INVALID_NETWORKID
#endif //INVALID_NETWORKID
#ifdef ISONID_VALID(value)
#undef ISONID_VALID(value)
#endif //ISONID_VALID(value)
#ifdef VALID_NTKID(ntkid)
#undef VALID_NTKID(ntkid)
#endif //VALID_NTKID(ntkid)
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
