#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define WINDOWID        (wnddest_GetWindowId(HsvMain))

#define SCAN_NONE       (eurdiv_ScanNone) 

#define SCAN_ANALOG     (eurdiv_ScanAnalog)

#define SCAN_DVBT       (eurdiv_ScanDVBT)

#define SCAN_DVBC       (eurdiv_ScanDVBC)

#define SCAN_DVBS       (eurdiv_ScanDVBS)

#define	PLATFORM_TABLE_ENTRIES	(14)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int InstallationInitialised;
static int s__InstallationInitialised;
int InstallationTurnOn;
static int s__InstallationTurnOn;
int PlatformTables [PLATFORM_TABLE_ENTRIES];
static int s__PlatformTables [PLATFORM_TABLE_ENTRIES];
void module__init(void){
	InstallationInitialised	=	s__InstallationInitialised;
	InstallationTurnOn	=	s__InstallationTurnOn;
	memcpy((void*)PlatformTables,(void*)s__PlatformTables,sizeof(PlatformTables));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef SCAN_NONE
#undef SCAN_NONE
#endif //SCAN_NONE
#ifdef SCAN_ANALOG
#undef SCAN_ANALOG
#endif //SCAN_ANALOG
#ifdef SCAN_DVBT
#undef SCAN_DVBT
#endif //SCAN_DVBT
#ifdef SCAN_DVBC
#undef SCAN_DVBC
#endif //SCAN_DVBC
#ifdef SCAN_DVBS
#undef SCAN_DVBS
#endif //SCAN_DVBS
#ifdef PLATFORM_TABLE_ENTRIES
#undef PLATFORM_TABLE_ENTRIES
#endif //PLATFORM_TABLE_ENTRIES
#endif //LOCAL_UNDEFINES
