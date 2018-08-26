#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define CURRENT_TABLE                       (pgdb_GetCurrentTable())

#define PTC_TABLE                           (CURRENT_TABLE | pgdbconst_DigitalTS)

#define SERVICE_TABLE                       (CURRENT_TABLE | pgdbconst_DigitalService)

#define PRESET_TABLE                        (CURRENT_TABLE | pgdbconst_Preset)      

#define PRESET_NOT_ALLOCATED(presetno)      (presetno == INVALID_PRESET)

#define MAX_PRESETS_SORT_PER_STEP			(100)

#ifndef __cplusplus

#define CLASSSCOPE

#endif

#define FNADDR(f) (& CLASSSCOPE f)


/*************************************************************************
  Local Structures and enums
 **************************************************************************/

typedef enum
{
	EvSortStart		= 0,
    EvSortContinue,
    EvSortComplete
}SortSteps;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#endif

Pump mCamSortPmp;
static Pump s__mCamSortPmp;
char TempString[50];
static char s__TempString[50];
void mCamSortPumpHandler(int Event, Nat32 Param);
void mSortPresets(int RunningRecordIndex);
void mAddEntryToPresetTable(HsvPgdatDigServiceData *SvcData);
Bool mGetServiceName(HsvPgdatDigServiceData *SvcData);
void module__init(void){
#ifndef __cplusplus

#endif

	mCamSortPmp	=	s__mCamSortPmp;
	memcpy((void*)TempString,(void*)s__TempString,sizeof(TempString));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef PRESET_NOT_ALLOCATED(presetno)
#undef PRESET_NOT_ALLOCATED(presetno)
#endif //PRESET_NOT_ALLOCATED(presetno)
#ifdef MAX_PRESETS_SORT_PER_STEP
#undef MAX_PRESETS_SORT_PER_STEP
#endif //MAX_PRESETS_SORT_PER_STEP
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#endif //LOCAL_UNDEFINES
