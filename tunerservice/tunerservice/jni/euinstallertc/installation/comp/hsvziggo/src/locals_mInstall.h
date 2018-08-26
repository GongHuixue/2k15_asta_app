#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define     VALID_EVENT(Event)      ((Event >= EvStart) && (Event < EvMax))

#define     VALID_STATE(state)      ((state >= StIdle) && (state < StMax))

#define     SET_INS_STATE(state)    (mInstStatus.State = state)

#define VALID_BARKERMUX_FOUND       ( (mBarkerMuxONID != 0xFFFF) && (mBarkerMuxTSID != 0xFFFF) )

#define MAX_SEARCH_RATES    (25)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define PLF_TUNING_DVBC_QAM16       	(1)
#define PLF_TUNING_DVBC_QAM32       	(2)
#define PLF_TUNING_DVBC_QAM64 		(3)
#define PLF_TUNING_DVBC_QAM128 		(4)
#define PLF_TUNING_DVBC_QAM256 		(5)

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
t_ZiggoCableDSDesc mCableDSDesc;
static t_ZiggoCableDSDesc s__mCableDSDesc;
Nat16 mBarkerMuxONID,mBarkerMuxTSID;
static Nat16 s__mBarkerMuxONID,s__mBarkerMuxTSID;
int mConstellation[14];
static int s__mConstellation[14];
static const FunctionVoid EventActionMatrix[][StMax];
void PumpHandler(int event, Nat32 param);
inline void FuncStartInstallation(void);
inline void FuncStopInstallation(void);
inline void FuncSdmStopped(void);
inline void FuncStationFound(void);
inline void FuncStationNotFound(void);
inline void FuncDataAvailable(void);
inline void FuncDataNotAvailable(void);
inline void mSetTunerAttributes(void);
inline void mStopSdm(HsvDemux dmx);
inline void mSelectDecoder(void);
inline Bool mAcquireValidNit(void);
inline void mInitialise(void);
inline int mGetSDTType(Nat16 Frequency);
inline void mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid);
inline Bool mLoadCDSDFromStrapi(int hsvspid);
inline Bool mGetAltTSValues(Nat16* ONID, Nat16* TSID);
inline void mGetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID);
inline int mMapFromHsvToPlfDvbcModulation(int type);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mInstStatus	=	s__mInstStatus;
	mInstallPump	=	s__mInstallPump;
	mModuleLifeCycle	=	s__mModuleLifeCycle;
	mCableDSDesc	=	s__mCableDSDesc;
	mBarkerMuxONID	=	s__mBarkerMuxONID;
	mBarkerMuxTSID	=	s__mBarkerMuxTSID;
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
#ifdef VALID_BARKERMUX_FOUND
#undef VALID_BARKERMUX_FOUND
#endif //VALID_BARKERMUX_FOUND
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
