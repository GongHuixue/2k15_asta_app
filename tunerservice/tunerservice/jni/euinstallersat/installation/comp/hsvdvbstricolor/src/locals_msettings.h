#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>



#define TRICOLOR_REGION_NAME_STORE_FILE_PATH   "/user_setting/rw/tvserver/databases/s2channellib/tricolor_region_name.bin"									 
#define INVALID_INDEX 		-1
#define PRIMARY_VERSION   	 1
#define SECONDARY_VERSION 	 0


typedef struct
{
	Nat32 	RecordSize;
	Nat32 	PrimaryVersion;
	Nat32 	SecondaryVersion;
	HsvTricolorRegionNameData regionNameData;
	Nat32 	Crc;
}HsvTricolorRegionNameStore;

/****************************************************************************
 * Static variables
 ****************************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)

HsvTricolorRegionNameStore HsvTricolorCurrentRegionNameData,HsvTricolorPersistentRegionNameData,HsvTricolorDefaultRegionNameData;
static HsvTricolorRegionNameStore s__HsvTricolorCurrentRegionNameData,s__HsvTricolorPersistentRegionNameData,s__HsvTricolorDefaultRegionNameData;

void Loaddefaultdata (void);
Bool LoadDataFromPersistentFile (void);
Nat32 CalculateCrc32( void* buffer, int size );
void module__init(void)
{
	HsvTricolorCurrentRegionNameData	=	s__HsvTricolorCurrentRegionNameData;
	HsvTricolorPersistentRegionNameData	=	s__HsvTricolorPersistentRegionNameData;
	HsvTricolorDefaultRegionNameData	=	s__HsvTricolorDefaultRegionNameData;	
}

#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INSTALL_SETTING_FILE_PATH
#undef INSTALL_SETTING_FILE_PATH
#endif //INSTALL_SETTING_FILE_PATH
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#endif //LOCAL_UNDEFINES
