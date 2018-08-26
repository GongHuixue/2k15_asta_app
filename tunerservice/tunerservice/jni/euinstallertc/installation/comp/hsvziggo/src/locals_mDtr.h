#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define     VALID_EVENT(Event)          ((Event >= EvStart) && (Event < EvMax))

#define     VALID_STATE(state)          ((state >= StIdle) && (state < StMax))

#define     SET_INS_STATE(state)        (mInsState = state)

#define     VALID_SOURCE(source)        (source == HsvMainTuner )

#define     TURNED_ON                   (mModuleLifeCycle == TurnedOn )

#define     MANUAL_MODE                 (rins_InstallationModeWeakSignal)

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
    StInProgress,
    StMax
}InsStates;
typedef enum
{
    EvStart,
    EvStop,
    EvOnMeasReady,
    EvMax
}Events;
typedef enum
{
    Initialised = 0,
    TurnedOn,
    TurnedOff
}ModuleLifeCycle;
typedef void (CLASSSCOPE *FunctionVoid)();
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

ModuleLifeCycle mModuleLifeCycle;
static ModuleLifeCycle s__mModuleLifeCycle;
int mInsState;
static int s__mInsState;
Pump mInstallPump;
static Pump s__mInstallPump;
static const FunctionVoid EventActionMatrix[][StMax];
void PumpHandler(int event, Nat32 param);
inline void FuncStartInstallation(void);
inline void FuncStopInstallation(void);
inline void FuncComplete(void);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mModuleLifeCycle	=	s__mModuleLifeCycle;
	mInsState	=	s__mInsState;
	mInstallPump	=	s__mInstallPump;
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
#ifdef VALID_SOURCE(source)
#undef VALID_SOURCE(source)
#endif //VALID_SOURCE(source)
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
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
