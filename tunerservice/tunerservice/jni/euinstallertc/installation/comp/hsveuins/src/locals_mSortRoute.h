#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define     CABLE                               ( rins_Cable )

#define     ANTENNA                             ( rins_Terrestrial )

#define     CURRENT_MEDIUM                      ( rins_GetMedium() )

#define     CURRENT_ACTIVE_MEDIUM               ( rins_GetActiveMedium() )

#define     CURRENT_COUNTRY                     ( sysset_GetSystemCountry() )

#define     DVBC_LITE                           ( eurdiv_ScanDVBCLite )

#define     DVBT_LITE                           ( eurdiv_ScanDVBTMpegOnly )

#define     IS_DVBC_LIGHT                       ( eurdiv_GetDVBCMode() == DVBC_LITE )

#define     IS_DVBT_LIGHT                       ( eurdiv_GetDVBTMode() == DVBT_LITE )

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef CABLE
#undef CABLE
#endif //CABLE
#ifdef ANTENNA
#undef ANTENNA
#endif //ANTENNA
#ifdef CURRENT_MEDIUM
#undef CURRENT_MEDIUM
#endif //CURRENT_MEDIUM
#ifdef CURRENT_COUNTRY
#undef CURRENT_COUNTRY
#endif //CURRENT_COUNTRY
#ifdef DVBC_LITE
#undef DVBC_LITE
#endif //DVBC_LITE
#ifdef DVBT_LITE
#undef DVBT_LITE
#endif //DVBT_LITE
#ifdef IS_DVBC_LIGHT
#undef IS_DVBC_LIGHT
#endif //IS_DVBC_LIGHT
#ifdef IS_DVBT_LIGHT
#undef IS_DVBT_LIGHT
#endif //IS_DVBT_LIGHT
#endif //LOCAL_UNDEFINES
