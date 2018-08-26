#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define EvDataAvaiable              (0x01)

#define BACKGROUND_MODE             (insstate_InstallationBackground)

#define BACKGROUND_INSTALL          (IsBackgroundInstall())


/* static variables */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mPump;
static Pump s__mPump;
Bool mActive,mAcquistionInProgress;
static Bool s__mActive,s__mAcquistionInProgress;
Bool IsBackgroundInstall (void);
void PumpHandler(int event, Nat32 param);
inline void FuncDataAvailable(void);
void module__init(void){
	mPump	=	s__mPump;
	mActive	=	s__mActive;
	mAcquistionInProgress	=	s__mAcquistionInProgress;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef EvDataAvaiable
#undef EvDataAvaiable
#endif //EvDataAvaiable
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#endif //LOCAL_UNDEFINES
