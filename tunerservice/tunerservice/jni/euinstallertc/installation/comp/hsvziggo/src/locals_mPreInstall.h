#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define     VALID_EVENT(Event)      ((Event >= EvStart) && (Event < EvMax))

#define     VALID_STATE(state)      ((state >= StIdle) && (state < StMax))

#define     SET_INS_STATE(state)    (mInstStatus.State = state)

#define     SET_VALUE               (TRUE)

#define MAX_SEARCH_RATES    (25)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

typedef enum
{
    StIdle,
    StInit,
    StTunerWait,
    StDemuxWait,
    StMax
}InsStates;
typedef enum
{
    EvStart,
    EvStop,
    EvSdmStopped,
    EvStationFound,
    EvStationNotFound,
    EvDataAvailable,
    EvDataNotAvailable,
    EvMax
}Events;
typedef enum
{
    Initialised = 0,
    TurnedOn,
    TurnedOff
}ModuleLifeCycle;
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
}t_ZiggoCableDSDesc;
typedef void (CLASSSCOPE *FunctionVoid)();
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

InstStatus mInstStatus;
static InstStatus s__mInstStatus;
Pump mInstallPump;
static Pump s__mInstallPump;
ModuleLifeCycle mModuleLifeCycle;
static ModuleLifeCycle s__mModuleLifeCycle;
Bool mUserNetworkDataSet,mDataAvailable;
static Bool s__mUserNetworkDataSet,s__mDataAvailable;
int mConstellation[14];
static int s__mConstellation[14];
static const FunctionVoid EventActionMatrix[][StMax];
void PumpHandler(int event, Nat32 param);
inline void FuncStartInstallation(void);
inline void FuncStopInstallation(void);
inline void FuncSdmStopped(void);
inline void mSetTunerAttributes(void);
inline void FuncStationFound(void);
inline void FuncStationNotFound(void);
inline void FuncDataAvailable(void);
inline void FuncDataNotAvailable(void);
inline void mStopSdm(HsvDemux dmx);
inline void mSelectDecoder(void);
inline Bool mNitValid(void);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mInstStatus	=	s__mInstStatus;
	mInstallPump	=	s__mInstallPump;
	mModuleLifeCycle	=	s__mModuleLifeCycle;
	mUserNetworkDataSet	=	s__mUserNetworkDataSet;
	mDataAvailable	=	s__mDataAvailable;
	memcpy((void*)mConstellation,(void*)s__mConstellation,sizeof(mConstellation));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef VALID_EVENT(Event)
#undef VALID_EVENT(Event)
#endif //VALID_EVENT(Event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef SET_INS_STATE(state)
#undef SET_INS_STATE(state)
#endif //SET_INS_STATE(state)
#ifdef SET_VALUE
#undef SET_VALUE
#endif //SET_VALUE
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
