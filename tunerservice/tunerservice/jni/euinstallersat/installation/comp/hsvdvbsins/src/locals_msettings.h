#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/stat.h>

#include <unistd.h>



#define INSTALL_SETTING_FILE_PATH   "/user_setting/rw/tvserver/databases/s2channellib/installsetting.bin"									 

#define INVALID_INDEX -1

#define	VALID_LNB(x)		(x<MAX_LNB_SUPPORTED)

#define PRIMARY_VERSION   1

#define SECONDARY_VERSION 0

#define MAX_LNB_SUPPORTED   4

#define UNIVERSAL_LOW_LO_FREQ	9750000

#define UNIVERSAL_HIGH_LO_FREQ	10600000

#define	UNIVERSAL_TONE_DEFLT	LnbToneAuto	

#define	UNIVERSAL_POW_DEFLT		LnbPowerAuto

#define ISNORDIGCOUNTRY(x) ((x == cids_CountryDenmark) || (x == cids_CountrySweden) || (x == cids_CountryFinland) || (x == cids_CountryNorway))

#define AID_USER_SETTING 9997 /*Value taken from android_filesystem_config.h*/


/****************************************************************************
 * Static variables
 ****************************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int AssetManager;
static int s__AssetManager;
HsvSatInstallationSettings HsvsatInsSetCurrentData,HsvsatInsSetPersistentData,HsvsatInsSetDefaultData;
static HsvSatInstallationSettings s__HsvsatInsSetCurrentData,s__HsvsatInsSetPersistentData,s__HsvsatInsSetDefaultData;
int NordigUnicableUBF[UnicableUserBandMax];
static int s__NordigUnicableUBF[UnicableUserBandMax];
void Loaddefaultdata (void);
Bool LoadDataFromPersistentFile (void);
Nat32 CalculateCrc32( void* buffer, int size );
Bool IsPersistentFilePresent (void);
void module__init(void){
	AssetManager	=	s__AssetManager;
	HsvsatInsSetCurrentData	=	s__HsvsatInsSetCurrentData;
	HsvsatInsSetPersistentData	=	s__HsvsatInsSetPersistentData;
	HsvsatInsSetDefaultData	=	s__HsvsatInsSetDefaultData;
	memcpy((void*)NordigUnicableUBF,(void*)s__NordigUnicableUBF,sizeof(NordigUnicableUBF));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INSTALL_SETTING_FILE_PATH
#undef INSTALL_SETTING_FILE_PATH
#endif //INSTALL_SETTING_FILE_PATH
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef VALID_LNB(x)
#undef VALID_LNB(x)
#endif //VALID_LNB(x)
#ifdef PRIMARY_VERSION
#undef PRIMARY_VERSION
#endif //PRIMARY_VERSION
#ifdef SECONDARY_VERSION
#undef SECONDARY_VERSION
#endif //SECONDARY_VERSION
#ifdef MAX_LNB_SUPPORTED
#undef MAX_LNB_SUPPORTED
#endif //MAX_LNB_SUPPORTED
#ifdef UNIVERSAL_LOW_LO_FREQ
#undef UNIVERSAL_LOW_LO_FREQ
#endif //UNIVERSAL_LOW_LO_FREQ
#ifdef UNIVERSAL_HIGH_LO_FREQ
#undef UNIVERSAL_HIGH_LO_FREQ
#endif //UNIVERSAL_HIGH_LO_FREQ
#ifdef UNIVERSAL_TONE_DEFLT
#undef UNIVERSAL_TONE_DEFLT
#endif //UNIVERSAL_TONE_DEFLT
#ifdef UNIVERSAL_POW_DEFLT
#undef UNIVERSAL_POW_DEFLT
#endif //UNIVERSAL_POW_DEFLT
#ifdef ISNORDIGCOUNTRY(x)
#undef ISNORDIGCOUNTRY(x)
#endif //ISNORDIGCOUNTRY(x)
#endif //LOCAL_UNDEFINES
