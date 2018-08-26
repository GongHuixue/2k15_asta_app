#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <pthread.h>

#include <unistd.h>

#include <fcntl.h>

#include <errno.h>

#include <pthread.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <string.h>

#include <sqlite3.h>

#define	MAX_PGDB_TABLES				(10)

#define MAX_SAT_PGDB_TABLES			(8)

#define NUM_MAIN_PGDB_TABLES		(5)

#define	SQL_TABLE_LARGE_QUERY_LENGTH		(4*1024)

#define	SQL_TABLE_MEDIUM_QUERY_LENGTH		(2*1024)

#define	SQL_TABLE_SMALL_QUERY_LENGTH		(256)

#define MAX_DIRECTORY_NAME_SIZE         (100)

#define MAX_FILE_NAME_SIZE              (100)

#define	SQL_TEMP_STRING_LENGTH			(64)

#define SEM_TAKE(sem)                   corertk_SemAcquire(mProgramMapSem)

#define SEM_GIVE(sem)                   corertk_SemRelease(mProgramMapSem)

#define TER_DB_FILENAME					"TerrestrialChannelMaps.db"

#define CAB_DB_FILENAME					"CableChannelMaps.db"

#define SAT_DB_FILENAME					"SatelliteChannelMaps.db"

#define TER_BAKDB_FILENAME					"TerrestrialChannelMapsBak.db"

#define CAB_BAKDB_FILENAME					"CableChannelMapsBak.db"

#define SAT_BAKDB_FILENAME					"SatelliteChannelMapsBak.db"


#define	CHANNELDATABASE_FILENAME		(mCurrentTable == ipgdbconst_Antenna) ? TER_DB_FILENAME : \
										((mCurrentTable == ipgdbconst_Cable) ? CAB_DB_FILENAME : SAT_DB_FILENAME)

#define GETMAJORTABLEID(id) (id & 0xffff0000)

#define GETSUBTABLEID(id)   (id & 0x0000ffff)

#define	IS_SQLITE_ERROR(x)				(x!=SQLITE_OK)

#define MAX_DIRTY_TYPES                 (3)

#define CHECK_CONFIG_ERR(a)			if(a != SQLITE_OK)		{	/*PrintfNotice ("Config Failed @ Func %s and line %d for config error %d \n", __FUNCTION__, __LINE__, a);*/ }

#define	CHECK_SQLITE_ERR(db,x)				if ( ((x) != SQLITE_OK) && ((x) != SQLITE_DONE) && ((x) != SQLITE_ROW) ) {\
												if (  ((x) == SQLITE_IOERR) || ((x) == SQLITE_CORRUPT) || ((x) == SQLITE_BUSY)){\
													usleep(50);\
												}\
											}


#define RETRY_COMMIT(db,x,retryCount)	  if( ((x) == SQLITE_LOCKED) || ((x) == SQLITE_BUSY)) {\
										  __android_log_print(ANDROID_LOG_ERROR, "PGDB","Retry Count");\
											while(((retryCount) < 50)){\
												sleep(1);\
												if((sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL)) == SQLITE_OK){\
													__android_log_print(ANDROID_LOG_ERROR, "PGDB","sqlite3_exec SUCCESS");\
													break;\
												}\
												retryCount++;\
												__android_log_print(ANDROID_LOG_ERROR, "PGDB","retryCount [%d]",retryCount);\
												if(retryCount == 50) {\
													TraceNotice(m,"Failed to insert to db");\
													break;\
												}\
											}\
								  		  }


#define SQLITE_STEP(stmnt,retryCount,RetVal)	RetVal = sqlite3_step (stmnt);\
												if(RetVal != SQLITE_ROW){\
													  __android_log_print(ANDROID_LOG_ERROR, "PGDB","sqlite3_step returned [%d]",RetVal);\
													}\
												if( ((RetVal) == SQLITE_LOCKED) || ((RetVal) == SQLITE_BUSY)) {\
													retryCount =0;\
												  __android_log_print(ANDROID_LOG_ERROR, "PGDB","Retry Count");\
												while(((retryCount) < 50)){\
													sleep(1);\
													RetVal = sqlite3_step (stmnt);\
													if(((RetVal) != SQLITE_LOCKED) && ((RetVal) != SQLITE_BUSY)){\
														__android_log_print(ANDROID_LOG_ERROR, "PGDB","sqlite3_step SUCCESS");\
														break;\
													}\
													retryCount++;\
													__android_log_print(ANDROID_LOG_ERROR, "PGDB","sqlite3_step retryCount [%d]",retryCount);\
													if(retryCount == 50) {\
														TraceNotice(m,"Failed to run query");\
														break;\
													}\
												}\
								  		  	}


#define DATABASE_DIRECTORY_PATH		"/user_setting/rw/tvserver/databases/channellib/"

											

#define MAX_ITEMS_CHANGED  2											

#define 	PERFORM_PGDB_DATABASE_SYNC(DbToSync,FromTableId,ToTableId,Index,TotalNumberOfEntries,Data) 			TotalNumberOfEntries = srtdb2_GetNoOfRecords(FromTableId);\
		TraceNotice (m, "Number of entries for %d is %d ", DbToSync, TotalNumberOfEntries);\
		if (TotalNumberOfEntries)\
		{\
			for (Index = 0; Index < TotalNumberOfEntries; Index++)\
			{\
				if (TRUE == srtdb2_QueryOnIndex(FromTableId, Index, &Data))\
				{\
					if (TRUE != srtdb2_Insert(ToTableId, mGetPrimaryKey(DbToSync, &Data), mGetSecondaryKey(DbToSync, &Data), mGetTertiaryKey(DbToSync, &Data), mGetQuaternaryKey(DbToSync, &Data), &Data))\
					{\
						TraceNotice (m, "PERFORM_PGDB_DATABASE_SYNC failed for Table %d Index %d ", DbToSync, Index);\
					}\
				}\
			}\
		}



	
/* Structure and Enums */

enum
{
    HsvAddDirtyType       =  0,
    HsvDeleteDirtyType,
    HsvUpdateDirtyType 
};
typedef struct HandleMaps
{
	int				SubTableId;
	sqlite3_stmt	*InsertHandle;
	sqlite3_stmt	*UpdateHandle;
} SqliteHandleMapEntry;

typedef struct Srtdbconfig
{
    Nat32   DbTableId;
    int     SrtDbTableId;
    int     MaxElements;
    int     ElementSize;
	int		BackupSrtDbTableId;
} Srtdbconfig;


#if 0

#endif

#ifdef	__OPTIMIZATION_CHECKS_ON__

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mCurrentTable;
static int s__mCurrentTable;
int mActiveDatabase;
static int s__mActiveDatabase;
SqliteHandleMapEntry SqliteHandleMaps[MAX_PGDB_TABLES];
static SqliteHandleMapEntry s__SqliteHandleMaps[MAX_PGDB_TABLES];
SqliteHandleMapEntry SqliteHandleSatMaps[MAX_SAT_PGDB_TABLES];
static SqliteHandleMapEntry s__SqliteHandleSatMaps[MAX_SAT_PGDB_TABLES];
Srtdbconfig	mProgramDbMap[MAX_PGDB_TABLES];
static Srtdbconfig	s__mProgramDbMap[MAX_PGDB_TABLES];
Bool mAutoCommitEnabled;
static Bool s__mAutoCommitEnabled;
Bool mFlashOperationPossible;
static Bool s__mFlashOperationPossible;
Bool mDirtyBit;
static Bool s__mDirtyBit;
char mDirectory[MAX_DIRECTORY_NAME_SIZE];
static char s__mDirectory[MAX_DIRECTORY_NAME_SIZE];
Semaphore mProgramMapSem;
static Semaphore s__mProgramMapSem;
char *SemKey;
static char *s__SemKey;
int 	mDatabaseMode;
static int s__mDatabaseMode;
sqlite3 *SqliteDbHandle;
static sqlite3 *s__SqliteDbHandle;
sqlite3 *SatDbHandle;
static sqlite3 *s__SatDbHandle;
sqlite3 *CabDbHandle;
static sqlite3 *s__CabDbHandle;
sqlite3 *TerDbHandle;
static sqlite3 *s__TerDbHandle;
char sqldbTableLargeStatementBuf[SQL_TABLE_LARGE_QUERY_LENGTH];
static char s__sqldbTableLargeStatementBuf[SQL_TABLE_LARGE_QUERY_LENGTH];
char sqldbTableInsertStatementBuf[SQL_TABLE_MEDIUM_QUERY_LENGTH];
static char s__sqldbTableInsertStatementBuf[SQL_TABLE_MEDIUM_QUERY_LENGTH];
HsvPgdatSatInfoData DefaultSatInfoValues;
static HsvPgdatSatInfoData s__DefaultSatInfoValues;
HsvPgdatPresetData DefaultPresetValues;
static HsvPgdatPresetData s__DefaultPresetValues;
HsvPgdatAnalogData DefaultAnalogValues;
static HsvPgdatAnalogData s__DefaultAnalogValues;
HsvPgdatDigServiceData DefaultDigSvcValues;
static HsvPgdatDigServiceData s__DefaultDigSvcValues;
HsvPgdatDigFreqMapData DefaultFrqMapValues;
static HsvPgdatDigFreqMapData s__DefaultFrqMapValues;
HsvPgdatDigTSData DefaultDigTSValues;
static HsvPgdatDigTSData s__DefaultDigTSValues;
void mInitialize (void);
char* mGetTableName (int ReqTableId);
void PrepareCreateElementString (int TableId,	char *sqldbTableExectureStatement, char *tempString);
int CreateAllDatabaseTables (sqlite3 *database, int medium);
int CreateDatabases(void);
int OpenSqliteDatabase (void);
void ResetSqliteStatementHandles (void);
int CloseSqliteDatabase (void);
void set_sqlite_configuration(void);
int ClearTable (int SubTableId);
int ClearAllTables (int tableid);
int ExtractNodeDataFromDatabse (char *QueryBuf, int QueryLen, int TableId, Address Data);
int GetDataFromTableByKey (int MajorTableId, int TableId, Address Data);
int GetCurrentIndexFromTable (int TableId, Address Data, Bool *Valid);
int GetDataFromTableByIndex (int TableId, int Index, Address Data);
int GetRangeOfDataByKey (int ReqTableId, int NoofKeys, Address Data, int *From, int *To);
void PrepareUpdateElementStringForSinglePrepare (int TableId,	char *statementbuf, char *tempString);
sqlite3_stmt* PrepareSqlUpdateStatement (int InsertTableId);
int FillUpdateStatement (sqlite3_stmt *InsertHandle, int TableId, Address Data);
int UpdateEntryToTableWithSinglePrepare (int InsertTableId, Address Data);
void CopyTempDataToCurrentTable (void);
int mGetDBTableIds(int PgDbTid);
int mGetPrimaryKey(int tableid, Address data);
int mGetSecondaryKey(int tableid, Address data);
int mGetTertiaryKey(int tableid, Address data);
int mGetQuaternaryKey(int tableid, Address data);
Bool Notification_enable;
int NoItemsChangedDigitalTS,NoItemsChangedAnalog;
int ItemIDs[MAX_ITEMS_CHANGED];
#if 0

#endif

int DeleteEntryFromTable (int deleteTableId, Address Data);
int GetIndexValForInsertion (int majorTableId, int InsertTableId, Address Data, Bool *Valid);
void PrepareInsertElementStringForSinglePrepare (int TableId,	char *statementbuf, char *tempString);
sqlite3_stmt* PrepareSqlInsertStatement (int InsertTableId);
void FillInsertStatement (sqlite3_stmt *InsertHandle, int TableId, Address Data);
int InsertEntryToTableWithSinglePrepare (int majorTableId, int InsertTableId, Address Data);
int InsertEntryToTableWithSinglePrepareIndex(int majorTableId, int InsertTableId, Address Data, int Index);
void LoadOrSaveChannelMaps (Bool LoadOrSave);
#ifdef	__OPTIMIZATION_CHECKS_ON__

#endif

void module__init(void){
	mCurrentTable	=	s__mCurrentTable;
	mActiveDatabase	=	s__mActiveDatabase;
	memcpy((void*)SqliteHandleMaps,(void*)s__SqliteHandleMaps,sizeof(SqliteHandleMaps));
	memcpy((void*)SqliteHandleSatMaps,(void*)s__SqliteHandleSatMaps,sizeof(SqliteHandleSatMaps));
	mAutoCommitEnabled	=	s__mAutoCommitEnabled;
	mFlashOperationPossible	=	s__mFlashOperationPossible;
	mDirtyBit	=	s__mDirtyBit;
	memcpy((void*)mDirectory,(void*)s__mDirectory,sizeof(mDirectory));
	mProgramMapSem	=	s__mProgramMapSem;
	SemKey	=	s__SemKey;
	SqliteDbHandle	=	s__SqliteDbHandle;
	SatDbHandle	=	s__SatDbHandle;
	CabDbHandle	=	s__CabDbHandle;
	TerDbHandle	=	s__TerDbHandle;
	memcpy((void*)sqldbTableLargeStatementBuf,(void*)s__sqldbTableLargeStatementBuf,sizeof(sqldbTableLargeStatementBuf));
	memcpy((void*)sqldbTableInsertStatementBuf,(void*)s__sqldbTableInsertStatementBuf,sizeof(sqldbTableInsertStatementBuf));
	DefaultSatInfoValues	=	s__DefaultSatInfoValues;
	DefaultPresetValues	=	s__DefaultPresetValues;
	DefaultAnalogValues	=	s__DefaultAnalogValues;
	DefaultDigSvcValues	=	s__DefaultDigSvcValues;
	DefaultFrqMapValues	=	s__DefaultFrqMapValues;
	DefaultDigTSValues	=	s__DefaultDigTSValues;
	memcpy((void*) mProgramDbMap, (void*) s__mProgramDbMap, sizeof(mProgramDbMap));
	mDatabaseMode 		=	s__mDatabaseMode;
#if 0

#endif

#ifdef	__OPTIMIZATION_CHECKS_ON__

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MAX_PGDB_TABLES
#undef MAX_PGDB_TABLES
#endif //MAX_PGDB_TABLES
#ifdef MAX_SAT_PGDB_TABLES
#undef MAX_SAT_PGDB_TABLES
#endif //MAX_SAT_PGDB_TABLES
#ifdef SQL_TABLE_LARGE_QUERY_LENGTH
#undef SQL_TABLE_LARGE_QUERY_LENGTH
#endif //SQL_TABLE_LARGE_QUERY_LENGTH
#ifdef SQL_TABLE_MEDIUM_QUERY_LENGTH
#undef SQL_TABLE_MEDIUM_QUERY_LENGTH
#endif //SQL_TABLE_MEDIUM_QUERY_LENGTH
#ifdef SQL_TABLE_SMALL_QUERY_LENGTH
#undef SQL_TABLE_SMALL_QUERY_LENGTH
#endif //SQL_TABLE_SMALL_QUERY_LENGTH
#ifdef MAX_DIRECTORY_NAME_SIZE
#undef MAX_DIRECTORY_NAME_SIZE
#endif //MAX_DIRECTORY_NAME_SIZE
#ifdef MAX_FILE_NAME_SIZE
#undef MAX_FILE_NAME_SIZE
#endif //MAX_FILE_NAME_SIZE
#ifdef SQL_TEMP_STRING_LENGTH
#undef SQL_TEMP_STRING_LENGTH
#endif //SQL_TEMP_STRING_LENGTH
#ifdef SEM_TAKE(sem)
#undef SEM_TAKE(sem)
#endif //SEM_TAKE(sem)
#ifdef SEM_GIVE(sem)
#undef SEM_GIVE(sem)
#endif //SEM_GIVE(sem)
#ifdef TER_DB_FILENAME
#undef TER_DB_FILENAME
#endif //TER_DB_FILENAME
#ifdef CAB_DB_FILENAME
#undef CAB_DB_FILENAME
#endif //CAB_DB_FILENAME
#ifdef SAT_DB_FILENAME
#undef SAT_DB_FILENAME
#endif //SAT_DB_FILENAME
#ifdef CHANNELDATABASE_FILENAME
#undef CHANNELDATABASE_FILENAME
#endif //CHANNELDATABASE_FILENAME
#ifdef GETMAJORTABLEID(id)
#undef GETMAJORTABLEID(id)
#endif //GETMAJORTABLEID(id)
#ifdef GETSUBTABLEID(id)
#undef GETSUBTABLEID(id)
#endif //GETSUBTABLEID(id)
#ifdef IS_SQLITE_ERROR(x)
#undef IS_SQLITE_ERROR(x)
#endif //IS_SQLITE_ERROR(x)
#ifdef MAX_DIRTY_TYPES
#undef MAX_DIRTY_TYPES
#endif //MAX_DIRTY_TYPES
#ifdef CHECK_CONFIG_ERR(a)
#undef CHECK_CONFIG_ERR(a)
#endif //CHECK_CONFIG_ERR(a)
#ifdef CHECK_SQLITE_ERR(db,x)
#undef CHECK_SQLITE_ERR(db,x)
#endif //CHECK_SQLITE_ERR(db,x)
#ifdef DATABASE_DIRECTORY_PATH
#undef DATABASE_DIRECTORY_PATH
#endif //DATABASE_DIRECTORY_PATH
#endif //LOCAL_UNDEFINES
