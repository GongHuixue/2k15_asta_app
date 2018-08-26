#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define COMPARE_INVALID_NETWORKID(NetworkId)        (NetworkId >= 0xFF01)

/*************************************************************************
  Local Structures and enums
 **************************************************************************/

typedef enum
{
    StIdle = 0,
    StPreScan,
    StQuick,
    StFull,
    StGrid,
    StScansDone,
    StMax
}States;
typedef enum
{
    EvStart = 0,
    EvPreScanDone,    
    EvQuickDone,
    EvFullDone,
    EvGridDone,
    EvScansDone,
    EvStop,
    EvMax
}Events;
typedef struct
{
    States State;
    Nat8 ScanMode;/* quick/full/grid */
}t_DVBCStatus;
typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

Pump mInstallPump;
static Pump s__mInstallPump;
t_DVBCStatus mDvbcStatus;
static t_DVBCStatus s__mDvbcStatus;
static const FunctionNat32 StateEventMatrix[][StMax];
void PumpHandler(int event, Nat32 param );
void FuncStart(Nat32 param);
void FuncPreScanDone(Nat32 param);
void FuncQuickDone(Nat32 param);
void FuncFullDone(Nat32 param);
void FuncGridDone(Nat32 param);
void FuncScansDone(Nat32 param);
void FuncPreScanStop(Nat32 param);
void FuncQuickStop(Nat32 param);
void FuncFullStop(Nat32 param);
void FuncGridStop(Nat32 param);
#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

void module__init(void){
#ifndef __cplusplus

#else

#endif

	mInstallPump	=	s__mInstallPump;
	mDvbcStatus	=	s__mDvbcStatus;
#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
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
#ifdef COMPARE_INVALID_NETWORKID(NetworkId)
#undef COMPARE_INVALID_NETWORKID(NetworkId)
#endif //COMPARE_INVALID_NETWORKID(NetworkId)
#endif //LOCAL_UNDEFINES
