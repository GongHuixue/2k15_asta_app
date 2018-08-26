#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <errno.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <unistd.h> 
/**************************************************************************
 * Macros and types
 **************************************************************************/

#define MAX_CHARACTERS        (128)

#define DEFAULT_FILE_PATH     "nandffs0/HsvDVBTSettingsFile"

#define BOOT_FILE_NAME        "HsvDVBTSettingsFile"

#define AUTO_MODE             (rins_InstallationModeAutomatic)

#define UPDATE_MODE           (rins_InstallationModeUpdate)

#define MANUAL_MODE           (rins_InstallationModeWeakSignal)

#define WINDOWID                (wnddest_GetWindowId(HsvMain))

#define AID_USER_SETTING 9997 /*Value taken from android_filesystem_config.h*/


/*************************************************************************
 * Local Structures and enums
 **************************************************************************/

typedef struct
{
    Nat8    ScanMode;                               /* Quick/Full Scan */
    Nat16   NetworkID;                              /* Can be any valid networkId */
    Nat32   PrimaryRegion;
    Nat32   SecondaryRegion;
    Nat32   TertiaryRegion;
    Nat32   ScrambledState;
    Bool    DualAnalogPass;
    Bool    DTTScanonAnalog;
	Nat16   FavoriteChannelListId;
}HsvDVBTSettings;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
HsvDVBTSettings mCurrentData;
static HsvDVBTSettings s__mCurrentData;
HsvDVBTSettings mDefaultData;
static HsvDVBTSettings s__mDefaultData;
HsvDVBTSettings mPersistentData;
static HsvDVBTSettings s__mPersistentData;
char mDirName[MAX_CHARACTERS];
static char s__mDirName[MAX_CHARACTERS];
char mFileName[MAX_CHARACTERS];
static char s__mFileName[MAX_CHARACTERS];
inline void mAttributeCopy(HsvDVBTSettings* dest, HsvDVBTSettings* src, int attribute);
inline Bool mAttributeValueCopy(HsvDVBTSettings* tmp, int attribute, int value);
inline int mGetAttrValue(HsvDVBTSettings tmp, int attribute);
void mLoadDefaults(void);
Bool mIsPersistentFileAvailable(void);
void mGetFilePath(void);
void module__init(void){
	mCurrentData	=	s__mCurrentData;
	mDefaultData	=	s__mDefaultData;
	mPersistentData	=	s__mPersistentData;
	memcpy((void*)mDirName,(void*)s__mDirName,sizeof(mDirName));
	memcpy((void*)mFileName,(void*)s__mFileName,sizeof(mFileName));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef DEFAULT_FILE_PATH
#undef DEFAULT_FILE_PATH
#endif //DEFAULT_FILE_PATH
#ifdef BOOT_FILE_NAME
#undef BOOT_FILE_NAME
#endif //BOOT_FILE_NAME
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#endif //LOCAL_UNDEFINES
