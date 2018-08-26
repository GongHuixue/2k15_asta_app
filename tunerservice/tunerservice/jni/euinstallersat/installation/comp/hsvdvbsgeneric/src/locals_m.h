#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define		AUTO_MODE			(insstate_InstallationServiceScan)

#define		UPDATE_MODE			(insstate_InstallationUpdate)

#define		AUTOUPDATE_MODE		(insstate_InstallationAutomaticUpdate)

#define		MANUAL_MODE			(insstate_InstallationManual)

#define		ADDSAT_MODE			(insstate_InstallationAddSatellite)

#define		BACKGROUND_MODE     (insstate_InstallationBackground)

#define		CURRENT_MODE		(InsStatus.Mode)

#define		SET_MODE(x)			(InsStatus.Mode = x)

typedef struct InstallationStatus
{
    int		State;
    Nat8    Mode;
}TypeInstallationStatus;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
TypeInstallationStatus InsStatus;
static TypeInstallationStatus s__InsStatus;
void module__init(void){
	InsStatus	=	s__InsStatus;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef AUTOUPDATE_MODE
#undef AUTOUPDATE_MODE
#endif //AUTOUPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef ADDSAT_MODE
#undef ADDSAT_MODE
#endif //ADDSAT_MODE
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef SET_MODE(x)
#undef SET_MODE(x)
#endif //SET_MODE(x)
#endif //LOCAL_UNDEFINES
