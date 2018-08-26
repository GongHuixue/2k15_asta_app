#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <stdio.h>

#include <errno.h>

#include <unistd.h>

#include <string.h>

#include <pthread.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <string.h>

#include <sys/stat.h>

#include <unistd.h>

#include <sys/stat.h>

#define	PREDEF_LIST_PATH_IN_USB		"predefinedlist"

#define	BIN_FILE_PATH	"/mnt/jffs1/data/dvbs2/configdata/predefinedrankinglist"

#define MAX_CACHE_SIZE 5

#define MAX_URI_LENGTH 256 //cbdiv_MaximumURISize

#define PREDEF_COPY_TASK_PRIORITY		10

#define PREDEF_COPY_TASK_STACK_SIZE		8192

#define	MAX_DIRECTORY_NAME_SIZE			256

#define	PREDEF_LIST_PATHLEN_IN_USB	(sizeof(PREDEF_LIST_PATH_IN_USB) + 1)

typedef enum
{
	USB_INSERT_NTF,
	USB_REMOVE_NTF
} USB_Events;
typedef enum
{
	TRIGGER_PREDEF_COPY = 1,
} PredefCopyEvents;
typedef enum
{
	Initialised,
	TurnedOn,
	TurnedOff
} ModuleState;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mModuleLifeCycle;
static int s__mModuleLifeCycle;
Pump UsbPump;
static Pump s__UsbPump;
char UsbUriCache[MAX_CACHE_SIZE][MAX_URI_LENGTH];
static char s__UsbUriCache[MAX_CACHE_SIZE][MAX_URI_LENGTH];
int mPgdatExtTaskId;
static int s__mPgdatExtTaskId;
void USBPumpHandler(int param1, Nat32 param2);
char * mGetFirstUsbUri(void);
int RunApp( char* program, char** arglist, Bool wait);
Bool mUntarAndCopyPredefinedBinaryFiles (char *PredefinedBinaryPath);
void PredefindListCopyHandler (int param);
void module__init(void){
	mModuleLifeCycle	=	s__mModuleLifeCycle;
	UsbPump	=	s__UsbPump;
	memcpy((void*)UsbUriCache,(void*)s__UsbUriCache,sizeof(UsbUriCache));
	mPgdatExtTaskId	=	s__mPgdatExtTaskId;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef PREDEF_LIST_PATH_IN_USB
#undef PREDEF_LIST_PATH_IN_USB
#endif //PREDEF_LIST_PATH_IN_USB
#ifdef BIN_FILE_PATH
#undef BIN_FILE_PATH
#endif //BIN_FILE_PATH
#ifdef MAX_CACHE_SIZE
#undef MAX_CACHE_SIZE
#endif //MAX_CACHE_SIZE
#ifdef MAX_URI_LENGTH
#undef MAX_URI_LENGTH
#endif //MAX_URI_LENGTH
#ifdef PREDEF_COPY_TASK_PRIORITY
#undef PREDEF_COPY_TASK_PRIORITY
#endif //PREDEF_COPY_TASK_PRIORITY
#ifdef PREDEF_COPY_TASK_STACK_SIZE
#undef PREDEF_COPY_TASK_STACK_SIZE
#endif //PREDEF_COPY_TASK_STACK_SIZE
#ifdef MAX_DIRECTORY_NAME_SIZE
#undef MAX_DIRECTORY_NAME_SIZE
#endif //MAX_DIRECTORY_NAME_SIZE
#ifdef PREDEF_LIST_PATHLEN_IN_USB
#undef PREDEF_LIST_PATHLEN_IN_USB
#endif //PREDEF_LIST_PATHLEN_IN_USB
#endif //LOCAL_UNDEFINES
