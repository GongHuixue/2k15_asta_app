#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include<string.h>

#define     DP(str)         //printf str

#define     ViterbiBER      (98)

#define     DEFAULT_SYM_RATE (1)            

#define     ABS(x)          (((x)>0)?(x):-(x))

#define     AUTO_MODE       (rins_InstallationModeAutomatic)

#define     UPDATE_MODE     (rins_InstallationModeUpdate)

#define     MANUAL_MODE     (rins_InstallationModeWeakSignal)

#define     BACKGROUND_MODE (rins_InstallationModeBackground)

#define     CURRENT_MODE    (rins_GetInstallationMode()) 

#define     AUTO_INSTALL    ((CURRENT_MODE) == (AUTO_MODE))

#define     UPDATE_INSTALL  ((CURRENT_MODE) == (UPDATE_MODE))

#define     MANUAL_INSTALL  ((CURRENT_MODE) == (MANUAL_MODE))

#define     BACKGROUND_INSTALL  ((CURRENT_MODE) == (BACKGROUND_MODE))

#define     ANTENNA_PTC     (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)

#define     DIGITAL_SERVICE (pgdb_GetCurrentTable() | pgdbconst_DigitalService)

/* medium */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#include<string.h>

int mInsMedium;
static int s__mInsMedium;
Nat16 mCurrentPresetIndex;
static Nat16 s__mCurrentPresetIndex;
TypeInstallationStatus InsStatus;
static TypeInstallationStatus s__InsStatus;
Bool mIsChannelListUpdated;
static Bool s__mIsChannelListUpdated;

Bool AddServices ( HsvInstallationPTC *ptc );
Bool AddService (HsvInstallationPTC *ptc, HSVSPTYPE(Program, mpeg, pat) *service);
void AddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(Program, mpeg, pat) *service);
Bool DuplicateEntry(HsvPgdatDigServiceData *psvcdat1, HsvPgdatDigServiceData *psvcdat2);
inline void mCopyString(Nat16* dest, Nat16* src, int maxchars);
void module__init(void){
#include<string.h>

	mInsMedium	=	s__mInsMedium;
	mCurrentPresetIndex	=	s__mCurrentPresetIndex;
	InsStatus	=	s__InsStatus;
	mIsChannelListUpdated = s__mIsChannelListUpdated;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef DP(str)
#undef DP(str)
#endif //DP(str)
#ifdef ViterbiBER
#undef ViterbiBER
#endif //ViterbiBER
#ifdef DEFAULT_SYM_RATE
#undef DEFAULT_SYM_RATE
#endif //DEFAULT_SYM_RATE
#ifdef ABS(x)
#undef ABS(x)
#endif //ABS(x)
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef AUTO_INSTALL
#undef AUTO_INSTALL
#endif //AUTO_INSTALL
#ifdef UPDATE_INSTALL
#undef UPDATE_INSTALL
#endif //UPDATE_INSTALL
#ifdef MANUAL_INSTALL
#undef MANUAL_INSTALL
#endif //MANUAL_INSTALL
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#ifdef ANTENNA_PTC
#undef ANTENNA_PTC
#endif //ANTENNA_PTC
#ifdef DIGITAL_SERVICE
#undef DIGITAL_SERVICE
#endif //DIGITAL_SERVICE
#endif //LOCAL_UNDEFINES
