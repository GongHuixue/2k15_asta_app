#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define PRESET_TABLE  (pgdb_GetCurrentTable() | pgdbconst_Preset)

#define IS_ANALOG(Channel)  (Channel->Type == HsvAnalog)

#define IS_DIGITAL(Channel)  (Channel->Type == HsvOnePart)

/*  Functions of Interface IHsvAdvanceIterator */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef IS_ANALOG(Channel)
#undef IS_ANALOG(Channel)
#endif //IS_ANALOG(Channel)
#ifdef IS_DIGITAL(Channel)
#undef IS_DIGITAL(Channel)
#endif //IS_DIGITAL(Channel)
#endif //LOCAL_UNDEFINES
