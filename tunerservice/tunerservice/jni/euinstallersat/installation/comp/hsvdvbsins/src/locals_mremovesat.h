#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define	INVALID_LNB			(0xFFFF)

#define	PUMP_LIMIT			40  /*Limit of iterations for the Pump to avoid conflict with WatchDog */

#define	SAT_INFO_TABLE		(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	PTC_TABLE			(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	SERVICE_TABLE		(pgdbconst_Satellite | pgdbconst_DigitalService)

#define	PRESET_TABLE		(pgdbconst_Satellite | pgdbconst_Preset)

#define	STATUS_OK			(1U)

#define	STATUS_NOT_OK		(0U)

typedef enum _Events
{
    EvStart,
    EvSatInfoDelStart,
    EvSatInfoDelComplete,
    EvTSInfoDelStart,
    EvPumpLimitReached,
    EvLnbRemoved,
    EvMax
}Events;
typedef enum __State
{
	ConstInitialized,
	ConstTurnedOn,
	ConstTurnedOff
} State;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mPump;
static Pump s__mPump;
int mConstModuleLifeCycle;
static int s__mConstModuleLifeCycle;
int ts_from_index;
static int s__ts_from_index;
int ts_to_index;
static int s__ts_to_index;
int LnbsToRemove;
static int s__LnbsToRemove;
void mPumpHandler(int value, Nat32 param);
void FuncInitialise(Nat32 Param);
void FuncRemoveTSSatInfo(Nat32 Param);
void FuncRemoveSatInfo(Nat32 Param );
void FuncParamReset(Nat32 num);
Nat32 GetNextLnbToRemove (Nat32 CurrentLnb);
void RemoveSatInfo(Nat32 Param);
void module__init(void){
	mPump	=	s__mPump;
	mConstModuleLifeCycle	=	s__mConstModuleLifeCycle;
	ts_from_index	=	s__ts_from_index;
	ts_to_index	=	s__ts_to_index;
	LnbsToRemove	=	s__LnbsToRemove;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INVALID_LNB
#undef INVALID_LNB
#endif //INVALID_LNB
#ifdef PUMP_LIMIT
#undef PUMP_LIMIT
#endif //PUMP_LIMIT
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef STATUS_OK
#undef STATUS_OK
#endif //STATUS_OK
#ifdef STATUS_NOT_OK
#undef STATUS_NOT_OK
#endif //STATUS_NOT_OK
#endif //LOCAL_UNDEFINES
