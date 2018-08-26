#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define ANALOGUE_TABLE  (pgdb_GetCurrentTable() | pgdbconst_Analog)

#define PRESENT_NAMELENGTH_ANALOG (5)

#define PRESETNAMELENGTH (6)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void ConvertAcisystemToTvsystem( HsvAciSystem acisys ,tmFe_TvSystem_t *tvsystem, Nat8 *colsystem);
void Store(Nat16 tableid , HsvPgdatAnalogData* pstruct);
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef ANALOGUE_TABLE
#undef ANALOGUE_TABLE
#endif //ANALOGUE_TABLE
#ifdef PRESENT_NAMELENGTH_ANALOG
#undef PRESENT_NAMELENGTH_ANALOG
#endif //PRESENT_NAMELENGTH_ANALOG
#ifdef PRESETNAMELENGTH
#undef PRESETNAMELENGTH
#endif //PRESETNAMELENGTH
#endif //LOCAL_UNDEFINES
