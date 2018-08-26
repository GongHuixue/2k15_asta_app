#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define     CURRENT_MODE            ( rins_GetInstallationMode() )

#define     AUTO_MODE               ( rins_InstallationModeAutomatic )

#define     BACKGROUND_MODE         ( rins_InstallationModeBackground )

#define     PRESCAN_MODE            ( rins_InstallationModePreScan )

#define     PRE_INSTALL             ( (CURRENT_MODE) == (PRESCAN_MODE) )

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
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef PRESCAN_MODE
#undef PRESCAN_MODE
#endif //PRESCAN_MODE
#ifdef PRE_INSTALL
#undef PRE_INSTALL
#endif //PRE_INSTALL
#endif //LOCAL_UNDEFINES
