#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
tmFe_TvSystem_t convertToPlfTvSystem(int instvsystem);
void convertToPlfColorSystem(int insCol,int *plfCol,int *plfColFreq);
int convertToPrgColorSystem(int colSys,int colFreq);
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#endif //LOCAL_UNDEFINES
