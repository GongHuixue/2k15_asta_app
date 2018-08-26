#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include<string.h>

#include<pthread.h>
//#include<sys/msg.h>

#define MESSAGE_SEND_RECEIVE_SUPPORT 0

#define TRACE_ON		0

#define CHANNEL_NAME_SIZE           (33)

#define MIN_PTC                     ((ipgdbconst_Antenna == ipgdb_GetCurrentTable()) ? 2 :  1)

#define MAX_PTC                     ((ipgdbconst_Antenna == ipgdb_GetCurrentTable()) ? 69 : 135)

#define CURRENT_PRESET_TABLE        (ipgdb_GetCurrentTable() | ipgdbconst_Preset)

#define CURRENT_ANALOG_TABLE        (ipgdb_GetCurrentTable() | ipgdbconst_Analog)

#define CURRENT_D_SVC_TABLE         (ipgdb_GetCurrentTable() | ipgdbconst_DigitalService)

#define CURRENT_D_PTC_TABLE         (ipgdb_GetCurrentTable() | ipgdbconst_DigitalPTC)

#define CURRENT_D_FREQ_TABLE        (ipgdb_GetCurrentTable() | ipgdbconst_FrequencyMapTable)
//#define CURRENT_D_SATINFO_TABLE     (ipgdbconst_Satellite    | ipgdbconst_SatInfo)

#define PGDAT_EXT_TASK_PRIORITY		10

#define PGDAT_EXT_TASK_STACK_SIZE	8192

#define MAX_DIRECTORY_NAME_SIZE     (200)
/* Reorder of channels */

#define MOVEDOWN 0

#define MOVEUP 1

#define SHUFFLE_CHANNELS_NO_SIZE 200

#define EVALUATE(channel1,channel2, increment, oper) ((oper == MOVEDOWN)? (channel1 + increment <= channel2 ): (channel1 - increment >= channel2))

#define INCREMENT_OR_DECREMENT(data1,i,MoveupOrDown) ((MoveupOrDown == MOVEDOWN)? (data1 -= i ): (data1 += i))

#define NEXT_OR_PREVIOUS(data1,i,MoveupOrDown) ((MoveupOrDown == MOVEDOWN)? (data1 + i ): (data1 - i))

#define LOCK_MUTEX(pgdatmutex)      pthread_mutex_lock(&pgdatmutex)

#define UNLOCK_MUTEX(pgdatmutex)    pthread_mutex_unlock(&pgdatmutex)

/* Message queue */

#define PGDAT_MSG_KEY           1000 /* To identify the message queue */

#define VALID_ONID(OnId)        (OnId >= 0)

#define VALID_TSID(TsId)        (TsId >= 0)

#define VALID_SID(SId)          (SId  >= 0)

#define VALID_PTC(Ptc)          (Ptc  >  0)

typedef struct
{
    AppApiChannel RChannel1;
    AppApiChannel RChannel2;
    Bool MoveupOrDown;
    Bool DeleteFirst;
}ReorderChannelInfo;
typedef struct
{
    long type;          /* This default is requried otherwise, message send will fail */
    ReorderChannelInfo ReChanlInfo;
}PgdatReOrderChannelMsg;
typedef enum
{
	PGDAT_EXT_LOAD = 1,
	PGDAT_EXT_SAVE
} PgdatExtEvents;
typedef struct 
{
	int		medium;
	char	DirectoryPath[MAX_DIRECTORY_NAME_SIZE];
} PgdatLoadSaveMsg;
#if MESSAGE_SEND_RECEIVE_SUPPORT

#endif

#if MESSAGE_SEND_RECEIVE_SUPPORT

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#include<string.h>

#include<pthread.h>
//#include<sys/msg.h>

#if MESSAGE_SEND_RECEIVE_SUPPORT

#endif

int gmqd;
static int s__gmqd;
pthread_mutex_t pgdatmutex;
static pthread_mutex_t s__pgdatmutex;
int mPgdatExtTaskId;
static int s__mPgdatExtTaskId;
PgdatLoadSaveMsg mPgdatMsg;
static PgdatLoadSaveMsg s__mPgdatMsg;
void PgdatExternalEventHandler(int param);
AppApiReturnCode mLoadChannelTableFromMedium(char* dir, int medium);
AppApiReturnCode mSaveChannelTableToMedium(char* dir, int medium);
void GetOperator(AppApiOperator * x);
FResult mSetScalarAttributeNat64(AppApiChannel channel, int dataid, Nat64  value);
FResult mGetScalarAttributeNat64(AppApiChannel channel, int dataid, Nat64  *value);
FResult mGetScalarAttribute(AppApiChannel channel, int dataid, Nat32  *value);
FResult mSetScalarAttribute(AppApiChannel channel, int dataid, Nat32 value);
Bool mIsAttributeSupportedNat64(int attribute);
Bool mIsAttributeSupported(int attribute);
FResult ShuffleChannels(ReorderChannelInfo rchannelinfo);
#if MESSAGE_SEND_RECEIVE_SUPPORT

void mPgdatThread(void *arg);
#endif

Bool internalreorder(AppApiChannel channel1, AppApiChannel channel2, Bool DeleteFrist);
void UpdateAnalogOrDigitalTable(HsvPgdatPresetData presetdat);
void InstalledSwap(HsvPgdatPresetData Channel1Presetdat, HsvPgdatPresetData Channel2Presetdat);
void DeletePresetTables(HsvPgdatPresetData Channel1Presetdat, HsvPgdatPresetData Channel2Presetdat);
void InsertPresetTables(HsvPgdatPresetData Channel1Presetdat, HsvPgdatPresetData Channel2Presetdat);
void UpdateServiceTable(HsvPgdatDigServiceData  svcdat, int PresetNumber);
void module__init(void){
#include<string.h>

#include<pthread.h>
//#include<sys/msg.h>

#if MESSAGE_SEND_RECEIVE_SUPPORT

#endif

	gmqd	=	s__gmqd;
	pgdatmutex	=	s__pgdatmutex;
	mPgdatExtTaskId	=	s__mPgdatExtTaskId;
	mPgdatMsg	=	s__mPgdatMsg;
#if MESSAGE_SEND_RECEIVE_SUPPORT

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MESSAGE_SEND_RECEIVE_SUPPORT
#undef MESSAGE_SEND_RECEIVE_SUPPORT
#endif //MESSAGE_SEND_RECEIVE_SUPPORT
#ifdef TRACE_ON
#undef TRACE_ON
#endif //TRACE_ON
#ifdef CHANNEL_NAME_SIZE
#undef CHANNEL_NAME_SIZE
#endif //CHANNEL_NAME_SIZE
#ifdef MIN_PTC
#undef MIN_PTC
#endif //MIN_PTC
#ifdef MAX_PTC
#undef MAX_PTC
#endif //MAX_PTC
#ifdef CURRENT_PRESET_TABLE
#undef CURRENT_PRESET_TABLE
#endif //CURRENT_PRESET_TABLE
#ifdef CURRENT_ANALOG_TABLE
#undef CURRENT_ANALOG_TABLE
#endif //CURRENT_ANALOG_TABLE
#ifdef CURRENT_D_SVC_TABLE
#undef CURRENT_D_SVC_TABLE
#endif //CURRENT_D_SVC_TABLE
#ifdef CURRENT_D_PTC_TABLE
#undef CURRENT_D_PTC_TABLE
#endif //CURRENT_D_PTC_TABLE
#ifdef CURRENT_D_FREQ_TABLE
#undef CURRENT_D_FREQ_TABLE
#endif //CURRENT_D_FREQ_TABLE
#ifdef PGDAT_EXT_TASK_PRIORITY
#undef PGDAT_EXT_TASK_PRIORITY
#endif //PGDAT_EXT_TASK_PRIORITY
#ifdef PGDAT_EXT_TASK_STACK_SIZE
#undef PGDAT_EXT_TASK_STACK_SIZE
#endif //PGDAT_EXT_TASK_STACK_SIZE
#ifdef MAX_DIRECTORY_NAME_SIZE
#undef MAX_DIRECTORY_NAME_SIZE
#endif //MAX_DIRECTORY_NAME_SIZE
#ifdef MOVEDOWN
#undef MOVEDOWN
#endif //MOVEDOWN
#ifdef MOVEUP
#undef MOVEUP
#endif //MOVEUP
#ifdef SHUFFLE_CHANNELS_NO_SIZE
#undef SHUFFLE_CHANNELS_NO_SIZE
#endif //SHUFFLE_CHANNELS_NO_SIZE
#ifdef EVALUATE(channel1,channel2,
#undef EVALUATE(channel1,channel2,
#endif //EVALUATE(channel1,channel2,
#ifdef INCREMENT_OR_DECREMENT(data1,i,MoveupOrDown)
#undef INCREMENT_OR_DECREMENT(data1,i,MoveupOrDown)
#endif //INCREMENT_OR_DECREMENT(data1,i,MoveupOrDown)
#ifdef NEXT_OR_PREVIOUS(data1,i,MoveupOrDown)
#undef NEXT_OR_PREVIOUS(data1,i,MoveupOrDown)
#endif //NEXT_OR_PREVIOUS(data1,i,MoveupOrDown)
#ifdef LOCK_MUTEX(pgdatmutex)
#undef LOCK_MUTEX(pgdatmutex)
#endif //LOCK_MUTEX(pgdatmutex)
#ifdef UNLOCK_MUTEX(pgdatmutex)
#undef UNLOCK_MUTEX(pgdatmutex)
#endif //UNLOCK_MUTEX(pgdatmutex)
#ifdef PGDAT_MSG_KEY
#undef PGDAT_MSG_KEY
#endif //PGDAT_MSG_KEY
#ifdef VALID_ONID(OnId)
#undef VALID_ONID(OnId)
#endif //VALID_ONID(OnId)
#ifdef VALID_TSID(TsId)
#undef VALID_TSID(TsId)
#endif //VALID_TSID(TsId)
#ifdef VALID_SID(SId)
#undef VALID_SID(SId)
#endif //VALID_SID(SId)
#ifdef VALID_PTC(Ptc)
#undef VALID_PTC(Ptc)
#endif //VALID_PTC(Ptc)
#endif //LOCAL_UNDEFINES
