#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define     CURRENT_MODE            (rins_GetInstallationMode())

#define     AUTO_MODE               ( rins_InstallationModeAutomatic )

#define     UPDATE_MODE             ( rins_InstallationModeUpdate )

#define     MANUAL_MODE             ( rins_InstallationModeWeakSignal )

#define     BACKGROUND_MODE         ( rins_InstallationModeBackground )

#define     AUTO_INSTALL            ( (CURRENT_MODE) == (AUTO_MODE) )

#define     UPDATE_INSTALL          ( (CURRENT_MODE) == (UPDATE_MODE) )

#define     MANUAL_INSTALL          ( (CURRENT_MODE) == (MANUAL_MODE) )

#define     BACKGROUND_INSTALL      ( (CURRENT_MODE) == (BACKGROUND_MODE) )

#define     CURRENT_SCAN            ( idvbset_GetAttribute(AUTO_MODE, rins_AttributeScanMode) )

#define     SCAN_MPEG_ONLY          ( eurdiv_ScanDVBTMpegOnly )

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
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
#ifdef CURRENT_SCAN
#undef CURRENT_SCAN
#endif //CURRENT_SCAN
#ifdef SCAN_MPEG_ONLY
#undef SCAN_MPEG_ONLY
#endif //SCAN_MPEG_ONLY
#endif //LOCAL_UNDEFINES
