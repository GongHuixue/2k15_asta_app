#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <errno.h>

#include <sys/types.h>

#include <unistd.h> 
/**************************************************************************
 * Macros and types
 **************************************************************************/

#define MAX_CHARACTERS        (128)

#define DEFAULT_FILE_PATH     "nandffs0/HsvCamSettingsFile"

#define BOOT_FILE_NAME        "HsvCamSettingsFile"

#define AUTO_MODE             (rins_InstallationModeAutomatic)

#define UPDATE_MODE           (rins_InstallationModeUpdate)


/*************************************************************************
 * Local Structures and enums
 **************************************************************************/

typedef struct
{
    int      charTableId;                        /* for storing character code */
    int      OperatorProfileInstalled;           /* To store whether operator profile installed */                 
    int      cicamId;                            /* CiCamId of Cam used for storing operator profile */
	int		 camNitVersion;						 /* NIT version of profile*/
}HsvDVBCamSettings;

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
char mFileName[MAX_CHARACTERS];
static char s__mFileName[MAX_CHARACTERS];
HsvDVBCamSettings mCurrentData;
static HsvDVBCamSettings s__mCurrentData;
HsvDVBCamSettings mDefaultData;
static HsvDVBCamSettings s__mDefaultData;
HsvDVBCamSettings mPersistentData;
static HsvDVBCamSettings s__mPersistentData;
inline void mAttributeCopy(HsvDVBCamSettings* dest, HsvDVBCamSettings* src, int attribute);
inline Bool mAttributeValueCopy(HsvDVBCamSettings* tmp, int attribute, int value);
inline int mGetAttrValue(HsvDVBCamSettings tmp, int attribute);
void mLoadDefaults(void);
Bool mIsPersistentFileAvailable(void);
void mGetFilePath(void);

void module__init(void){
	mCurrentData	=	s__mCurrentData;
	mDefaultData	=	s__mDefaultData;
	mPersistentData	=	s__mPersistentData;
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
#endif //LOCAL_UNDEFINES
