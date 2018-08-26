/*
 *  Copyright(C) 2009 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *    %name: hsvpgdat_mpgdb.c %
 *    %version: TVG_5 %
 *    %date_modified: Fri Apr 10 15:30:44 2009 %
 *    %derived_by: aneeshc %
 */



#include "semaphore.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "_hsvpgdat_mpgdb.h"

TRACESYMBOL(m, "euinstalltc/hsvpgdat/hsvpgdat_mpgdb")

#include "hsvpgdat_mpgdb.h"
















int CHsvProgramData_mpgdb_Priv::s__mCurrentTable = ipgdbconst_Antenna;
int CHsvProgramData_mpgdb_Priv::s__mActiveDatabase = ipgdb_TempDatabase;
int CHsvProgramData_mpgdb_Priv::s__mDatabaseMode = ipgdb_DatabaseModeNormal;
int CHsvProgramData_mpgdb_Priv::Preparecount = 0;

SqliteHandleMapEntry CHsvProgramData_mpgdb_Priv::s__SqliteHandleMaps[MAX_PGDB_TABLES] =
{
	{ipgdbconst_FrequencyMapTable,		NULL,	NULL},
	{ipgdbconst_DigitalTS,				NULL,	NULL},
	{ipgdbconst_DigitalService,			NULL,	NULL},
	{ipgdbconst_Analog,					NULL,	NULL},
	{ipgdbconst_Preset,					NULL,	NULL},
	{ipgdbconst_CurrentFrequencyMapTable,	NULL,	NULL},
	{ipgdbconst_CurrentDigitalTS,		NULL,	NULL},
	{ipgdbconst_CurrentDigitalService,	NULL,	NULL},
	{ipgdbconst_CurrentAnalog,			NULL,	NULL},
	{ipgdbconst_CurrentPreset,			NULL,	NULL}
};


SqliteHandleMapEntry CHsvProgramData_mpgdb_Priv::s__SqliteHandleSatMaps[MAX_SAT_PGDB_TABLES] =
{
	{ipgdbconst_SatInfo,				NULL,	NULL},
	{ipgdbconst_DigitalTS,				NULL,	NULL},
	{ipgdbconst_DigitalService,			NULL,	NULL},
	{ipgdbconst_Preset,					NULL,	NULL},
	{ipgdbconst_CurrentSatInfo,			NULL,	NULL},
	{ipgdbconst_CurrentDigitalTS,		NULL,	NULL},
	{ipgdbconst_CurrentDigitalService,	NULL,	NULL},
	{ipgdbconst_CurrentPreset,			NULL,	NULL}
};

Srtdbconfig	CHsvProgramData_mpgdb_Priv::s__mProgramDbMap[MAX_PGDB_TABLES] = { 	
													{ipgdbconst_FrequencyMapTable, 		0/*srtdbids_PresetTable*/, 		50, 	sizeof(HsvPgdatDigFreqMapData) },
													{ipgdbconst_DigitalTS,				0/*srtdbids_DigSrvcTable*/, 	50, 	sizeof(HsvPgdatDigTSData) },
													{ipgdbconst_DigitalService,			0/*srtdbids_DigSrvcTable*/, 	500, 	sizeof(HsvPgdatDigServiceData) },
													{ipgdbconst_Analog,					0/*srtdbids_DigSrvcTable*/, 	100, 	sizeof(HsvPgdatAnalogData) },
													{ipgdbconst_Preset,					0/*srtdbids_DigSrvcTable*/, 	500, 	sizeof(HsvPgdatPresetData) },
													{ipgdbconst_CurrentFrequencyMapTable,0/*srtdbids_DigSrvcTable*/, 	50, 	sizeof(HsvPgdatDigFreqMapData) },
													{ipgdbconst_CurrentDigitalTS,		0/*srtdbids_DigSrvcTable*/, 	50, 	sizeof(HsvPgdatDigTSData) },
													{ipgdbconst_CurrentDigitalService,	0/*srtdbids_DigSrvcTable*/, 	500, 	sizeof(HsvPgdatDigServiceData) },
													{ipgdbconst_CurrentAnalog, 			0/*srtdbids_SatInfoTable*/, 	100, 	sizeof(HsvPgdatAnalogData) },
													{ipgdbconst_CurrentPreset, 			0/*srtdbids_DigTSTable*/, 		500, 	sizeof(HsvPgdatPresetData) }};


/* Static variables  */
Bool CHsvProgramData_mpgdb_Priv::s__mAutoCommitEnabled = FALSE;

Bool CHsvProgramData_mpgdb_Priv::s__mFlashOperationPossible = FALSE;

Bool CHsvProgramData_mpgdb_Priv::s__mDirtyBit = FALSE;


char CHsvProgramData_mpgdb_Priv::s__mDirectory[MAX_DIRECTORY_NAME_SIZE];

Semaphore CHsvProgramData_mpgdb_Priv::s__mProgramMapSem = NULL;

char *CHsvProgramData_mpgdb_Priv::s__SemKey = "/hsvpgdat_mflash";
  /* TODO: how to make sure that key is unique? */
sqlite3 *CHsvProgramData_mpgdb_Priv::s__SqliteDbHandle = NULL;

sqlite3 *CHsvProgramData_mpgdb_Priv::s__SatDbHandle = NULL;

sqlite3 *CHsvProgramData_mpgdb_Priv::s__CabDbHandle = NULL;

sqlite3 *CHsvProgramData_mpgdb_Priv::s__TerDbHandle = NULL;

char CHsvProgramData_mpgdb_Priv::s__sqldbTableLargeStatementBuf[SQL_TABLE_LARGE_QUERY_LENGTH];
	/* This buffer is used mainly in create table query */
char CHsvProgramData_mpgdb_Priv::s__sqldbTableInsertStatementBuf[SQL_TABLE_MEDIUM_QUERY_LENGTH];



HsvPgdatSatInfoData CHsvProgramData_mpgdb_Priv::s__DefaultSatInfoValues;

HsvPgdatPresetData CHsvProgramData_mpgdb_Priv::s__DefaultPresetValues;

HsvPgdatAnalogData CHsvProgramData_mpgdb_Priv::s__DefaultAnalogValues;

HsvPgdatDigServiceData CHsvProgramData_mpgdb_Priv::s__DefaultDigSvcValues;

HsvPgdatDigFreqMapData CHsvProgramData_mpgdb_Priv::s__DefaultFrqMapValues;

HsvPgdatDigTSData CHsvProgramData_mpgdb_Priv::s__DefaultDigTSValues;


HSVCOMPAREKEY(freqmaptableconf, Primary, HsvPgdatDigFreqMapData, OriginalNetworkId)
HSVCOMPAREKEY(freqmaptableconf, Secondary, HsvPgdatDigFreqMapData, Tsid)
HSVCOMPAREKEY(freqmaptableconf, Teritiary, HsvPgdatDigFreqMapData, Frequency)
HSVCOMPAREKEY(freqmaptableconf, Quaternary, HsvPgdatDigFreqMapData, Frequency)

HSVCOMPAREKEY(tstableconf, Primary, HsvPgdatDigTSData, Frequency)
HSVCOMPAREKEY(tstableconf, Secondary, HsvPgdatDigTSData, StreamPriority)
HSVCOMPAREKEY(tstableconf, Teritiary, HsvPgdatDigTSData, StreamPriority)                         
HSVCOMPAREKEY(tstableconf, Quaternary, HsvPgdatDigTSData, StreamPriority)

HSVCOMPAREKEY(digsrvtableconf, Primary, HsvPgdatDigServiceData, OriginalNetworkId)
HSVCOMPAREKEY(digsrvtableconf, Secondary, HsvPgdatDigServiceData, ServiceId)
HSVCOMPAREKEY(digsrvtableconf, Teritiary, HsvPgdatDigServiceData, Frequency)
//HSVCOMPAREKEY(digsrvtableconf, Quaternary, HsvPgdatDigServiceData, StreamPriority)
Nat8 CHsvProgramData_mpgdb_Priv::digsrvtableconf_CompareQuaternaryKey(Nat32 key, Address data)
{
     HsvPgdatDigServiceData * Section   = (HsvPgdatDigServiceData *)data;                                    
     Nat8            RetValue     = digsrvtableconf_BiggerKey;                                                                                                               
     if( NULL == data )                                                          
	     {                                                                           
                ASSERT( "NULL pointer passed to extract and compare key ");             
         }                                                                           
         else                                                                        
         {                                   
            if (mDatabaseMode == ipgdb_DatabaseModeCam)
            {
                  if ( key < (Nat32) Section->LCN )                                           
                  {                                                                       
                       RetValue = digsrvtableconf_SmallerKey;                                       
                  }                                                                       
                  else                                                                    
                  {                                                                       
                      if (key == (Nat32) Section->LCN )                                       
                      {
                          RetValue = digsrvtableconf_Equal;                                        
                      }                                                                   
                  }
            }
            else
			{
                 if ( key < (Nat32) Section->StreamPriority )                                           
                 {                                                                       
                     RetValue = digsrvtableconf_SmallerKey;                                       
                 }                                                                       
                 else                                                                    
                 {                                                                       
                      if (key == (Nat32) Section->StreamPriority )                                       
                        {                                                                   
                            RetValue = digsrvtableconf_Equal;                                        
                        }                                                                   
                 }
            }
            } 
            return RetValue;                                                            
}

HSVCOMPAREKEY(analogtableconf, Primary,		HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(analogtableconf, Secondary,	HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(analogtableconf, Teritiary,	HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(analogtableconf, Quaternary,	HsvPgdatAnalogData, PresetNumber)


HSVCOMPAREKEY(presettableconf, Primary,		HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(presettableconf, Secondary,	HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(presettableconf, Teritiary,	HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(presettableconf, Quaternary,	HsvPgdatPresetData, PresetNumber)

HSVCOMPAREKEY(tempfreqmaptableconf, Primary, HsvPgdatDigFreqMapData, OriginalNetworkId)
HSVCOMPAREKEY(tempfreqmaptableconf, Secondary, HsvPgdatDigFreqMapData, Tsid)
HSVCOMPAREKEY(tempfreqmaptableconf, Teritiary, HsvPgdatDigFreqMapData, Frequency)
HSVCOMPAREKEY(tempfreqmaptableconf, Quaternary, HsvPgdatDigFreqMapData, Frequency)

HSVCOMPAREKEY(temptstableconf, Primary, HsvPgdatDigTSData, Frequency)
HSVCOMPAREKEY(temptstableconf, Secondary, HsvPgdatDigTSData, StreamPriority)
HSVCOMPAREKEY(temptstableconf, Teritiary, HsvPgdatDigTSData, StreamPriority)                         
HSVCOMPAREKEY(temptstableconf, Quaternary, HsvPgdatDigTSData, StreamPriority)

HSVCOMPAREKEY(tempdigsrvtableconf, Primary, HsvPgdatDigServiceData, OriginalNetworkId)
HSVCOMPAREKEY(tempdigsrvtableconf, Secondary, HsvPgdatDigServiceData, ServiceId)
HSVCOMPAREKEY(tempdigsrvtableconf, Teritiary, HsvPgdatDigServiceData, Frequency)
HSVCOMPAREKEY(tempdigsrvtableconf, Quaternary, HsvPgdatDigServiceData, StreamPriority)

HSVCOMPAREKEY(tempanalogtableconf, Primary,		HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(tempanalogtableconf, Secondary,	HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(tempanalogtableconf, Teritiary,	HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(tempanalogtableconf, Quaternary,	HsvPgdatAnalogData, PresetNumber)


HSVCOMPAREKEY(temppresettableconf, Primary,		HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(temppresettableconf, Secondary,	HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(temppresettableconf, Teritiary,	HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(temppresettableconf, Quaternary,	HsvPgdatPresetData, PresetNumber)

HSVCOMPAREKEY(backupfreqmaptableconf, Primary, HsvPgdatDigFreqMapData, OriginalNetworkId)
HSVCOMPAREKEY(backupfreqmaptableconf, Secondary, HsvPgdatDigFreqMapData, Tsid)
HSVCOMPAREKEY(backupfreqmaptableconf, Teritiary, HsvPgdatDigFreqMapData, Frequency)
HSVCOMPAREKEY(backupfreqmaptableconf, Quaternary, HsvPgdatDigFreqMapData, Frequency)

HSVCOMPAREKEY(backuptstableconf, Primary, HsvPgdatDigTSData, Frequency)
HSVCOMPAREKEY(backuptstableconf, Secondary, HsvPgdatDigTSData, StreamPriority)
HSVCOMPAREKEY(backuptstableconf, Teritiary, HsvPgdatDigTSData, StreamPriority)                         
HSVCOMPAREKEY(backuptstableconf, Quaternary, HsvPgdatDigTSData, StreamPriority)

HSVCOMPAREKEY(backupdigsrvtableconf, Primary, HsvPgdatDigServiceData, OriginalNetworkId)
HSVCOMPAREKEY(backupdigsrvtableconf, Secondary, HsvPgdatDigServiceData, ServiceId)
HSVCOMPAREKEY(backupdigsrvtableconf, Teritiary, HsvPgdatDigServiceData, Frequency)
HSVCOMPAREKEY(backupdigsrvtableconf, Quaternary, HsvPgdatDigServiceData, StreamPriority)

HSVCOMPAREKEY(backupanalogtableconf, Primary,		HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(backupanalogtableconf, Secondary,	HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(backupanalogtableconf, Teritiary,	HsvPgdatAnalogData, PresetNumber)
HSVCOMPAREKEY(backupanalogtableconf, Quaternary,	HsvPgdatAnalogData, PresetNumber)


HSVCOMPAREKEY(backuppresettableconf, Primary,		HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(backuppresettableconf, Secondary,	HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(backuppresettableconf, Teritiary,	HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(backuppresettableconf, Quaternary,	HsvPgdatPresetData, PresetNumber)


/* Internal Functions */


















































void CHsvProgramData_mpgdb_Priv::mInitialize (void)
{

	pthread_t	Futhread;
	int			RetValth,RetVal,i;		
 
	/* Getting the default values for each of the pgdb structures */
#define NO
#define NAME
#define NONE
#define A(x)    [0]

#define SATINFO_ITEM(item, type, bit, siz, def)     DefaultSatInfoValues.item siz = def;
#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef SATINFO_ITEM

#define PRESET_ITEM(item, type, bit, siz, def)      DefaultPresetValues.item siz = def;
if (mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_presetitems.h"
#else
#include "hsvpgdat_sat_presetitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_presetitems.h"
#else
#include "hsvpgdat_presetitems.h"
#endif
}
#undef PRESET_ITEM

#define ANALOG_ITEM(item, type, bit, siz, def)      DefaultAnalogValues.item siz = def;
#ifndef __cplusplus
#include "data/hsvpgdat_analogitems.h"
#else
#include "hsvpgdat_analogitems.h"
#endif

#undef ANALOG_ITEM

#define DIGSRVC_ITEM(item, type, bit, siz, def)     DefaultDigSvcValues.item siz = def;
if (mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digsrvcitems.h"
#else
#include "hsvpgdat_sat_digsrvcitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digsrvcitems.h"
#else
#include "hsvpgdat_digsrvcitems.h"
#endif
}
#undef DIGSRVC_ITEM

#define FREQMAP_ITEM(item, type, bit, siz, def)     DefaultFrqMapValues.item siz = def;
#ifndef __cplusplus
#include "data/hsvpgdat_freqmapitems.h"
#else
#include "hsvpgdat_freqmapitems.h"
#endif
#undef FREQMAP_ITEM

#define DIGTS_ITEM(item, type, bit, siz, def)         DefaultDigTSValues.item siz = def;
if(mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digtsitems.h"
#else
#include "hsvpgdat_sat_digtsitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digtsitems.h"
#else
#include "hsvpgdat_digtsitems.h"
#endif
}
#undef DIGTS_ITEM

#undef NO
#undef NAME
#undef NONE
#undef A
    
	/* Starting the flash updat thread, and creating the semaphore to protect channel map */
//	RetValth = pthread_create(&Futhread, NULL, (void*)mUpdateFlashMemory, NULL);
    
    //mProgramMapSem = rtk_SemCreate( SemKey );
    mProgramMapSem = corertk_SemCreate();

	/* Update the channel map directory. Disable auto commit by default */
//    mGetDirectoryPath(mDirectory);    
    
//    mSetDirty(FALSE);

    mAutoCommitEnabled = FALSE;

	mProgramDbMap[0].SrtDbTableId = srtdbids_FreqMapTable;
	mProgramDbMap[1].SrtDbTableId = srtdbids_DigTsTable;
	mProgramDbMap[2].SrtDbTableId = srtdbids_DigSrvTable;
	mProgramDbMap[3].SrtDbTableId = srtdbids_AnalogTable;
	mProgramDbMap[4].SrtDbTableId = srtdbids_PresetTable;
	mProgramDbMap[5].SrtDbTableId = srtdbids_TempFreqMapTable;
	mProgramDbMap[6].SrtDbTableId = srtdbids_TempDigTsTable;
	mProgramDbMap[7].SrtDbTableId = srtdbids_TempDigSrvTable;
	mProgramDbMap[8].SrtDbTableId = srtdbids_TempAnalogTable;
	mProgramDbMap[9].SrtDbTableId = srtdbids_TempPresetTable;
	
	for(i=0; i<MAX_PGDB_TABLES; i++)
	{
		srtdb2_Init(mProgramDbMap[i].SrtDbTableId);
	}

	/* Backup DB exists only for Main tables. Initialize them */
	mProgramDbMap[0].BackupSrtDbTableId = srtdbids_BackupFreqMapTable;
	mProgramDbMap[1].BackupSrtDbTableId = srtdbids_BackupDigTsTable;
	mProgramDbMap[2].BackupSrtDbTableId = srtdbids_BackupDigSrvTable;
	mProgramDbMap[3].BackupSrtDbTableId = srtdbids_BackupAnalogTable;
	mProgramDbMap[4].BackupSrtDbTableId = srtdbids_BackupPresetTable;
	for(i=0; i<5; i++)
	{
		srtdb2_Init(mProgramDbMap[i].BackupSrtDbTableId);
	}
	
	set_sqlite_configuration ();
	/* Initializing the SQLite. Table creation happens at a later point of time */
	RetVal = sqlite3_initialize ();
	//PrintfNotice ("SQLITE_Init Return value %d \n", RetVal);

}

char* CHsvProgramData_mpgdb_Priv::mGetTableName (int ReqTableId)	
{
	char		*Name = NULL;

	/* Check for matching Subtable ID for getting the name */
#define	TABLE_ITEM(MajorTableId, TableId,TableName,DataType)	\
	if((mCurrentTable==MajorTableId) && (ReqTableId==TableId)) \
	{\
		Name = TableName;\
	}

#include "hsvpgdat_tableinfo.h"

#undef TABLE_ITEM

	return Name;
}

void CHsvProgramData_mpgdb_Priv::PrepareCreateElementString (int TableId,	char *sqldbTableExectureStatement, char *tempString)
{
	int medium_sat = FALSE;

	switch (TableId)
	{
	case	ipgdbconst_SatInfo:
	case	ipgdbconst_CurrentSatInfo:
#define	SATINFO_ITEM(element, type, bitdec, bitdef, defaultval )	\
	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)
#ifndef __cplusplus
#include "data/hsvpgdat_sqlite_items.h"
#else
#include "hsvpgdat_sqlite_items.h"
#endif
#undef	SATINFO_ITEM

		break;

	case	ipgdbconst_Analog:
	case	ipgdbconst_CurrentAnalog:
#define	ANALOG_ITEM(element, type, bitdec, bitdef, defaultval )	\
	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)
#ifndef __cplusplus
#include "data/hsvpgdat_sqlite_items.h"
#else
#include "hsvpgdat_sqlite_items.h"
#endif
#undef	ANALOG_ITEM

		break;

	case	ipgdbconst_FrequencyMapTable:
	case	ipgdbconst_CurrentFrequencyMapTable:

#define	FREQMAP_ITEM(element, type, bitdec, bitdef, defaultval )	\
	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)
#ifndef __cplusplus
#include "data/hsvpgdat_sqlite_items.h"
#else
#include "hsvpgdat_sqlite_items.h"
#endif
#undef	FREQMAP_ITEM

		break;

		
	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:

#define	DIGTS_ITEM(element, type, bitdec, bitdef, defaultval )	\
	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)
#ifndef __cplusplus
#include "data/hsvpgdat_sqlite_items.h"
#else
#include "hsvpgdat_sqlite_items.h"
#endif
#undef	DIGTS_ITEM

		break;

		
	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:

#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, defaultval )	\
	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)
#ifndef __cplusplus
#include "data/hsvpgdat_sqlite_items.h"
#else
#include "hsvpgdat_sqlite_items.h"
#endif
#undef	DIGSRVC_ITEM

		break;

	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:

#define	PRESET_ITEM(element, type, bitdec, bitdef, defaultval )	\
	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)

#ifndef __cplusplus
#include "data/hsvpgdat_sqlite_items.h"
#else
#include "hsvpgdat_sqlite_items.h"
#endif
#undef	PRESET_ITEM

		break;
	}
	
	sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, " %s int", "dummy" );\
	strcat (sqldbTableExectureStatement, tempString);

}

int CHsvProgramData_mpgdb_Priv::CreateAllDatabaseTables (sqlite3 *database, int medium)
{
	Nat32	RetVal = 0;
	char 	tempString[SQL_TEMP_STRING_LENGTH];

	/* This statement is a longer one. Use the long buffer */
	//PrintfNotice (" S2Channellib: %s @ %d \n", __FUNCTION__,__LINE__);

	/* Check the table info. Create tables for each of the entries in database */
#define	TABLE_ITEM(MajorTableId,TableId, TableName,Type)	\
	if (medium == MajorTableId) { \	
		sqlite3_snprintf (SQL_TABLE_LARGE_QUERY_LENGTH, sqldbTableLargeStatementBuf, "CREATE TABLE IF NOT EXISTS %s (", TableName);\
		sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "DbIndex integer , ");\
		strcat (sqldbTableLargeStatementBuf, tempString);\
		PrepareCreateElementString (TableId,sqldbTableLargeStatementBuf,tempString);\
		sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, ");");\
		strcat (sqldbTableLargeStatementBuf, tempString);\
		RetVal = sqlite3_exec (database, sqldbTableLargeStatementBuf, NULL, NULL, NULL);\
		CHECK_SQLITE_ERR (database, RetVal);\
	}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

	return RetVal;
}


int CHsvProgramData_mpgdb_Priv::CreateDatabases(void)
{
	int RetVal = 0;
	char db_FileName[100] = {0};
	
	strcpy(db_FileName, DATABASE_DIRECTORY_PATH);
	strcat(db_FileName, TER_DB_FILENAME);	
	RetVal = sqlite3_open (db_FileName, &TerDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		//PrintfNotice ("ChannelLib: Open SQLITE db %s failed with error value %d \n", TER_DB_FILENAME, RetVal);
		RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;
		return RetVal;
	}
	else
	{
		CreateAllDatabaseTables(TerDbHandle, ipgdbconst_Antenna);
	}
	if(sysset_GetPbsMode() == 0)
	{
//#if (0)	// Jemy Chao - Using Antenna table only for HTV.
	strcpy(db_FileName, DATABASE_DIRECTORY_PATH);
	strcat(db_FileName, CAB_DB_FILENAME);	
	RetVal = sqlite3_open (db_FileName, &CabDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		//PrintfNotice ("ChannelLib: Open SQLITE db %s failed with error value %d \n", CAB_DB_FILENAME, RetVal);
		RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;
		return RetVal;
	}
	else
	{
		CreateAllDatabaseTables(CabDbHandle, ipgdbconst_Cable);
	}
//#endif
	}
	
	strcpy(db_FileName, DATABASE_DIRECTORY_PATH);
	strcat(db_FileName, CAB_DB_FILENAME);	
	RetVal = sqlite3_open (db_FileName, &SatDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		//PrintfNotice ("ChannelLib: Open SQLITE db %s failed with error value %d \n", SAT_DB_FILENAME, RetVal);
		RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;
		return RetVal;
	}
	else
	{
		CreateAllDatabaseTables(SatDbHandle, ipgdbconst_Satellite);
	}
	
	return TRUE;
}

int CHsvProgramData_mpgdb_Priv::OpenSqliteDatabase (void)
{
	int		RetVal = FALSE;
	FILE	*fp = NULL;
	char	fileName[200];
	
	strcpy(fileName, DATABASE_DIRECTORY_PATH);
	switch (mCurrentTable)
	{
		case ipgdbconst_Satellite:
			strcat(fileName, SAT_DB_FILENAME);
			break;
		case ipgdbconst_Cable:
			if(sysset_GetPbsMode() == 0)
			{
//#if (0)	// Jemy Chao - Using Antenna table only for HTV.
				strcat(fileName, CAB_DB_FILENAME);
				break;
//#endif			
			}
		case ipgdbconst_Antenna:
			strcat(fileName, TER_DB_FILENAME);
			break;
		default:
			return RetVal;
	}
	
	fp = fopen (fileName,"r");
	if (fp)
	{
		//PrintfNotice ("EuChannelLib: DBFile Created..\n");
		fclose(fp);
	}
	else
	{
		return RetVal;
	}

	RetVal = sqlite3_open (fileName, &SqliteDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		//TraceNotice(m," EuChannelLib: Open SQLITE memory db failed with error value %d \n", RetVal);
		ASSERT("EuChannelLib: Open SQLITE memory db failed \n");
	}
	else
	{
		TraceNotice(m,"EuChannelLib: DBGPrint sqlite open succesful for file %s with dbHandle 0x%x\n", fileName, (unsigned int)SqliteDbHandle );
	}
	/* This API returns TRUE or FALSE only */
	RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;

	return RetVal;
}


void CHsvProgramData_mpgdb_Priv::ipgdbpow_Init (void)
{
	int RetVal = 0;

	/* Initialize the default params and creation of flash update thread */
	mInitialize ();

	/* Create the sqlite Databse file. Tables are created later only*/
	RetVal = OpenSqliteDatabase ();

	if (RetVal != TRUE)
	{
		ASSERT("Error Seen during pgdbpow_Init \n");
	}

}

/* Function to load or Save database.
	TRUE: Load the database from backup to actual 
	FALSE: Save the database to backup from actual */
void CHsvProgramData_mpgdb_Priv::LoadOrSaveChannelMaps (Bool LoadOrSave)
{
		int TableIndex = 0, i = 0;
	int TotalNumberOfEntries =0, count = 0, Index = 0;

	HsvPgdatDigTSData		digTsData;
	HsvPgdatDigServiceData	digSrvData;
	HsvPgdatPresetData		presetData;
	HsvPgdatDigFreqMapData	freqMapData;
	HsvPgdatAnalogData		analogData;



	/*Clear To Database*/
	
	for(i=0; i<NUM_MAIN_PGDB_TABLES; i++)
	{
		srtdb2_Init((LoadOrSave) ? (mProgramDbMap[i].SrtDbTableId) : (mProgramDbMap[i].BackupSrtDbTableId));
	}
	
	if (LoadOrSave == TRUE)
	{
		/*Load ChanelMaps from backup*/
		TraceNotice (m, "Load ChannelMaps from backup");
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[0].DbTableId, mProgramDbMap[0].BackupSrtDbTableId,mProgramDbMap[0].SrtDbTableId,Index, TotalNumberOfEntries,freqMapData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[1].DbTableId, mProgramDbMap[1].BackupSrtDbTableId,mProgramDbMap[1].SrtDbTableId,Index, TotalNumberOfEntries,digTsData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[2].DbTableId, mProgramDbMap[2].BackupSrtDbTableId,mProgramDbMap[2].SrtDbTableId,Index, TotalNumberOfEntries,digSrvData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[3].DbTableId, mProgramDbMap[3].BackupSrtDbTableId,mProgramDbMap[3].SrtDbTableId,Index, TotalNumberOfEntries,analogData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[4].DbTableId, mProgramDbMap[4].BackupSrtDbTableId,mProgramDbMap[4].SrtDbTableId,Index, TotalNumberOfEntries,presetData)
		
	}
	else
	{
		/*Save ChannelMaps to backup*/
		TraceNotice (m, "Save ChannelMaps to backup");
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[0].DbTableId, mProgramDbMap[0].SrtDbTableId,mProgramDbMap[0].BackupSrtDbTableId,Index, TotalNumberOfEntries,freqMapData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[1].DbTableId, mProgramDbMap[1].SrtDbTableId,mProgramDbMap[1].BackupSrtDbTableId,Index, TotalNumberOfEntries,digTsData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[2].DbTableId, mProgramDbMap[2].SrtDbTableId,mProgramDbMap[2].BackupSrtDbTableId,Index, TotalNumberOfEntries,digSrvData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[3].DbTableId, mProgramDbMap[3].SrtDbTableId,mProgramDbMap[3].BackupSrtDbTableId,Index, TotalNumberOfEntries,analogData)
		PERFORM_PGDB_DATABASE_SYNC(mProgramDbMap[4].DbTableId, mProgramDbMap[4].SrtDbTableId,mProgramDbMap[4].BackupSrtDbTableId,Index, TotalNumberOfEntries,presetData)
	}
	TraceNotice (m, "Backup copy completed ");

} 
	
void CHsvProgramData_mpgdb_Priv::ipgdb_SaveChannelMapsToBackup(void)
{
	LoadOrSaveChannelMaps (FALSE);
}

void CHsvProgramData_mpgdb_Priv::ipgdb_LoadChannelMapsFromBackup(void)
{
	LoadOrSaveChannelMaps (TRUE);
}

void CHsvProgramData_mpgdb_Priv::ipgdbpow_TurnOn (void)
{
	/* TODO */
}

void CHsvProgramData_mpgdb_Priv::ResetSqliteStatementHandles (void)
{
	TraceNotice(m,"ResetSqliteStatementHandles" );
	int err_code;
	int count;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;
	
	if (mCurrentTable == ipgdbconst_Satellite)
	{
		handle = SqliteHandleSatMaps;
		num_tbl = MAX_SAT_PGDB_TABLES;
	}
	else
	{
		handle = SqliteHandleMaps;
		num_tbl = MAX_PGDB_TABLES;
	}
	
	for (count = 0; count < num_tbl; count++)
	{
		if (handle[count].InsertHandle)
		{
			//TraceNotice (m,"Reset Insert %d ", handle[count].InsertHandle);
			err_code = sqlite3_reset (handle[count].InsertHandle);
			//TraceNotice(m,"err_code [%d], line [%d]",err_code, __LINE__);
			err_code = sqlite3_finalize (handle[count].InsertHandle);
			--Preparecount;
			//TraceNotice(m,"err_code [%d], line [%d]",err_code, __LINE__);
			handle[count].InsertHandle = NULL;

		}

		if (handle[count].UpdateHandle)
		{
			err_code = sqlite3_reset (handle[count].UpdateHandle);
			//TraceNotice(m,"err_code [%d], line [%d]",err_code, __LINE__);			
			err_code = sqlite3_finalize (handle[count].UpdateHandle);
			--Preparecount;
			//TraceNotice(m,"err_code [%d], line [%d]",err_code, __LINE__);			
			handle[count].UpdateHandle = NULL;	
		}
	}
}

int CHsvProgramData_mpgdb_Priv::CloseSqliteDatabase (void)
{
	int		RetVal = FALSE;

	RetVal = sqlite3_close (SqliteDbHandle);
	TraceNotice(m,"ClosedSqliteDbHandle [%d]",RetVal);
	if (IS_SQLITE_ERROR(RetVal))
	{
		CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);
		//PrintfNotice ("EuChannelLib: Close SQLITE memory db failed \n");
		ASSERT("EuChannelLib: Close SQLITE memory db failed \n");
	}
	TraceNotice(m,"ClosedSqliteHandleMaps" );

	/* This API returns TRUE or FALSE only */
	RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;

	TraceNotice(m,"Database closed with retval [%d]",RetVal);

	return RetVal;
}

void CHsvProgramData_mpgdb_Priv::ipgdbpow_TurnOff (void)
{
	int	RetVal = 0;
	/* TODO: Reset Statements */
	ResetSqliteStatementHandles ();
	RetVal = CloseSqliteDatabase ();
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_SelectTable       ( int tableid )
{
	Bool	RetVal = FALSE;

	SEM_TAKE(mProgramMapSem);
	
	if (tableid != mCurrentTable)
	{
		
		if (SqliteDbHandle != NULL)
		{
			//TraceNotice (m,"Pgdb: CurrentTable %d NewSelectedTable %d, Closing Db ", mCurrentTable, tableid);
			ResetSqliteStatementHandles ();
			RetVal = CloseSqliteDatabase ();
		}

		/* Set Current table */
		switch (tableid)
		{
		case	ipgdbconst_Cable:
		case	ipgdbconst_TempCable:
		case	ipgdbconst_Antenna:
		case	ipgdbconst_TempAntenna:
		case	ipgdbconst_Satellite:
		case	ipgdbconst_TempSatellite:
			mCurrentTable = tableid;
			OpenSqliteDatabase ();
			RetVal = TRUE;
			break;
		default:
			break;
		}
	}
	else
	{
		RetVal = TRUE;
	}

	SEM_GIVE(mProgramMapSem);
	
	return RetVal;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_LoadTable        ( int tableid )
{
	mCurrentTable = tableid;
//	mGetDirectoryPath(mDirectory);

	return TRUE;
}

void CHsvProgramData_mpgdb_Priv::ipgdb_SetDatabaseOperationMode (int mode)
{
	TraceNotice(m, "%s %d : mode = %d", __FUNCTION__, __LINE__, mode);
	mDatabaseMode = mode;
}
/* SQLITE based general internal functions */
void CHsvProgramData_mpgdb_Priv::set_sqlite_configuration(void)
{
}

void CHsvProgramData_mpgdb_Priv::ipgdb_MasterEnableEvents(Bool enable)
{
	SEM_TAKE(mProgramMapSem);
    sync_MasterEnableEvents(enable);
	SEM_GIVE(mProgramMapSem);
	Notification_enable=enable;
}

int CHsvProgramData_mpgdb_Priv::ipgdb_GetCurrentTable   ( void )
{
	return mCurrentTable;
}

int CHsvProgramData_mpgdb_Priv::ClearTable (int SubTableId)
{
	int	RetVal = -1, retryCount = 0;
	char	sqlDeleteBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	//PrintfNotice (" EuChannelLib : DbgPrint ClearTable \n");
	RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);


	/* Clear the particular subtable */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
	if ((mCurrentTable == MajorTableId) && (TableId == SubTableId)) {\
		sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlDeleteBuf, "DELETE FROM %s ", TableName);\
		RetVal = sqlite3_exec (SqliteDbHandle, sqlDeleteBuf, NULL, NULL, NULL);\
		RetVal = (RetVal == SQLITE_DONE) ? err_Ok: err_FileError;\
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
	}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

	RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
	if(RetVal == SQLITE_BUSY) 	{
		RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount);
	}


	return RetVal;
}

int CHsvProgramData_mpgdb_Priv::ClearAllTables (int tableid)
{
	int	RetVal = -1, retryCount = 0;
	char	sqlDeleteBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	//PrintfNotice (" EuChannelLib : DbgPrint ClearTable \n");
	RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);


	/* Clear all the subtables of the MajorTable */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
	if (MajorTableId == tableid) {\
		sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlDeleteBuf, "DELETE FROM %s ", TableName);\
		RetVal = sqlite3_exec (SqliteDbHandle, sqlDeleteBuf, NULL, NULL, NULL);\
		RetVal = (RetVal == SQLITE_OK) ? err_Ok: err_FileError;\
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
	}
#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

	RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
	if(RetVal == SQLITE_BUSY) 	
	{
		RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount);
	}

	return RetVal;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_ClearTable        ( int tableid )
{
	Bool	RetVal = FALSE;
	int		subtableid,i;

	SEM_TAKE(mProgramMapSem);
	
	subtableid = GETSUBTABLEID(tableid);

	switch (GETMAJORTABLEID(tableid))
	{
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{

			if (subtableid)
			{
				/* If subtable present, clear that alone */
				RetVal = (ClearTable (subtableid) == err_Ok) ? TRUE : FALSE;
			}
			else
			{
				/* No subtable, then clear all */
				RetVal = (ClearAllTables (GETMAJORTABLEID(tableid)) == err_Ok) ? TRUE : FALSE;
			}
		}
		else
		{
			for(i=0; i<MAX_PGDB_TABLES; i++)
			{
			    if(subtableid)
                {
                    if(subtableid & mProgramDbMap[i].DbTableId)
                    {
                        srtdb2_Init(mProgramDbMap[i].SrtDbTableId);
                    }
                }
                else
                {
					{
						srtdb2_Init(mProgramDbMap[i].SrtDbTableId);
					}
                }
			}
		}
		break;
	default:
		break;
	}

	SEM_GIVE(mProgramMapSem);
	return RetVal;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_IsSupported( int tableid )
{
    Bool retval = FALSE;
    switch(tableid)
    {
        case ipgdbconst_Antenna: 
		case ipgdbconst_TempAntenna:
		case ipgdbconst_Cable:
		case ipgdbconst_TempCable:
		case ipgdbconst_Satellite:
		case ipgdbconst_TempSatellite:
            retval = TRUE;
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_CommitTable      ( int tableid )
{
	int	RetVal = 0;

	SEM_TAKE(mProgramMapSem);
	
	ResetSqliteStatementHandles ();
	if (Preparecount)
	{
		TraceNotice (m, " ALERT!! : There are some prepared SQLITE statements which are not finalized. This will impact LOGO association. FIX IT ");
	}
	//RetVal = CloseSqliteDatabase ();/* ANEESH: Closing of DB happens only on TurnOff */
	

//	mGetDirectoryPath(mDirectory);

	SEM_GIVE(mProgramMapSem);

	return TRUE;//mCommitTable (tableid, mDirectory);
}

int CHsvProgramData_mpgdb_Priv::ipgdb_GetNoRecords(int tableid )
{
	int		RetVal = TRUE;
	int		MinorTableId = GETSUBTABLEID(tableid);
	int		Index = 0;
	sqlite3_stmt *statement;
	char	StatementBuf[SQL_TABLE_SMALL_QUERY_LENGTH];

	SEM_TAKE(mProgramMapSem);
	
	/* Last index value will be equal the number of records present */
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		if (mCurrentTable == MajorTableId) \
		GET_NUM_ROW_FROM_TABLE(TableId, MinorTableId, TableName,SqliteDbHandle, StatementBuf,statement,Index)

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM
		}
		else
		{
			RetVal = srtdb2_GetNoOfRecords(mGetDBTableIds(MinorTableId));
			Index = RetVal;
		}
		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	
	return Index;
}

int CHsvProgramData_mpgdb_Priv::mGetDBTableIds(int PgDbTid)
{
    int ret = -1;
    int i;
    
    for(i=0; i<MAX_PGDB_TABLES; i++)
    {
        if(PgDbTid == mProgramDbMap[i].DbTableId)
        {	
            ret = mProgramDbMap[i].SrtDbTableId;
            break;
        }
    }
    return ret;
}

inline int CHsvProgramData_mpgdb_Priv::mGetPrimaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_CurrentPreset:
		retval = ((HsvPgdatPresetData*)(data))->PresetNumber;
		break;
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
		retval = ((HsvPgdatDigTSData*)(data))->Frequency;
		break;
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
		retval = ((HsvPgdatDigServiceData*)(data))-> OriginalNetworkId;
		break;
	case ipgdbconst_FrequencyMapTable:
	case ipgdbconst_CurrentFrequencyMapTable:
		retval = ((HsvPgdatDigFreqMapData*)(data))->OriginalNetworkId;
		break;
	case ipgdbconst_Analog:
	case ipgdbconst_CurrentAnalog:
		retval = ((HsvPgdatAnalogData*)(data))->PresetNumber;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

inline int CHsvProgramData_mpgdb_Priv::mGetSecondaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_CurrentPreset:
	case ipgdbconst_Analog:
	case ipgdbconst_CurrentAnalog:
		break;
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
		retval = ((HsvPgdatDigTSData*)(data))->StreamPriority;
		break;
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
		retval = ((HsvPgdatDigServiceData*)(data))-> ServiceId;
		break;
	case ipgdbconst_FrequencyMapTable:
	case ipgdbconst_CurrentFrequencyMapTable:
		retval = ((HsvPgdatDigFreqMapData*)(data))->Tsid;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

inline int CHsvProgramData_mpgdb_Priv::mGetTertiaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_CurrentPreset:
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
	case ipgdbconst_Analog:
	case ipgdbconst_CurrentAnalog:
		break;
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
		retval = ((HsvPgdatDigServiceData*)(data))-> Frequency;
		break;
	case ipgdbconst_FrequencyMapTable:
	case ipgdbconst_CurrentFrequencyMapTable:
		//retval = ((HsvPgdatDigFreqMapData*)(data))->Frequency;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

inline int CHsvProgramData_mpgdb_Priv::mGetQuaternaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_CurrentPreset:
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
	case ipgdbconst_FrequencyMapTable:
	case ipgdbconst_CurrentFrequencyMapTable:
	case ipgdbconst_Analog:
	case ipgdbconst_CurrentAnalog:
		break;
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
		if(mDatabaseMode == ipgdb_DatabaseModeCam){
			retval = ((HsvPgdatDigServiceData*)(data))->LCN;
		}
		else{
			retval = ((HsvPgdatDigServiceData*)(data))->StreamPriority;
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}




int CHsvProgramData_mpgdb_Priv::ExtractNodeDataFromDatabse (char *QueryBuf, int QueryLen, int TableId, Address Data)
{
	int			RetVal = FALSE, Ret;
	int			index = 0;
	int			temp, NumColumns = 0;
	Bool		proceed = TRUE;
//	Nat16		*returnString = NULL;
	void		*returnString = NULL;
	sqlite3_stmt	*statement = NULL;
	int			retryCount = 0;

	/* TODO: For optimisations: From Top Layer check whether pre-compilaiton of statements can be done.
		This will need changes in multiple functions */
	/* TODO: Cleanup the return values */
	/* DO the extraction after the SELECT executiion */
#define		Nat32	1
#define		Int32	2
#define		Nat16	3
#define		Int16	4
#define		Nat8	5
#define		Nat64	6
#define		NONE	0
#define		NO
#define		NAME	*
#define		A(x)	x
	
	//PrintfNotice ("EuChannelLib: In Func %s Query Statement %s \n", __FUNCTION__, QueryBuf);
	RetVal = sqlite3_prepare_v2 (SqliteDbHandle, QueryBuf, QueryLen, &statement, NULL);
	++Preparecount;
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	/* Only single step is required. And now parse each columns */
	SQLITE_STEP(statement,retryCount,RetVal);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	NumColumns = (RetVal == SQLITE_ROW) ? sqlite3_column_count(statement) : 0;
	//PrintfNotice (" EuChannelLib:  DbgPrint Number of columns in %s @ %d is %d \n", __FUNCTION__,__LINE__, NumColumns);
	if (NumColumns)
	{
		/* Index should be 1 not 0. Because 0 is element DbIndex'. */
		sqlite3_column_int(statement,0);
		index = 1;

		switch (TableId)
		{
		case	ipgdbconst_SatInfo:
		case	ipgdbconst_CurrentSatInfo:
#define	SATINFO_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt,HsvPgdatSatInfoData,statement,temp,returnString)
#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef	SATINFO_ITEM
			RetVal = TRUE;
			break;

		case	ipgdbconst_FrequencyMapTable:
		case	ipgdbconst_CurrentFrequencyMapTable:
#define	FREQMAP_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt,HsvPgdatDigFreqMapData,statement,temp,returnString)
#ifndef __cplusplus
#include "data/hsvpgdat_freqmapitems.h"
#else
#include "hsvpgdat_freqmapitems.h"
#endif
#undef	FREQMAP_ITEM
			RetVal = TRUE;
			break;

		case	ipgdbconst_Analog:
		case	ipgdbconst_CurrentAnalog:
#define	ANALOG_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt,HsvPgdatAnalogData,statement,temp,returnString)
#ifndef __cplusplus
#include "data/hsvpgdat_analogitems.h"
#else
#include "hsvpgdat_analogitems.h"
#endif
#undef	ANALOG_ITEM
			RetVal = TRUE;
			break;

		case	ipgdbconst_DigitalTS:
		case	ipgdbconst_CurrentDigitalTS:
#define	DIGTS_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt ,HsvPgdatDigTSData,statement,temp,returnString)

if (mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digtsitems.h"
#else
#include "hsvpgdat_sat_digtsitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digtsitems.h"
#else
#include "hsvpgdat_digtsitems.h"
#endif
}
#undef	DIGTS_ITEM
			RetVal = TRUE;
			break;

		case	ipgdbconst_DigitalService:
		case	ipgdbconst_CurrentDigitalService:
#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt ,HsvPgdatDigServiceData,statement,temp,returnString)

if (mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digsrvcitems.h"
#else
#include "hsvpgdat_sat_digsrvcitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digsrvcitems.h"
#else
#include "hsvpgdat_digsrvcitems.h"
#endif
}
#undef	DIGSRVC_ITEM
			RetVal = TRUE;
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
#define	PRESET_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt ,HsvPgdatPresetData,statement,temp,returnString)

if (mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_presetitems.h"
#else
#include "hsvpgdat_sat_presetitems.h"
#endif
}
else {
	
#ifndef __cplusplus
#include "data/hsvpgdat_presetitems.h"
#else
#include "hsvpgdat_presetitems.h"
#endif

}
#undef	PRESET_ITEM
			RetVal = TRUE;
			break;

		default:
			RetVal = FALSE;
			break;
		}
	}
	else
	{
		//PrintfNotice ("EuChannelLib: Count is Zero \n");
		RetVal = FALSE;
	}

	/* Now reset and finalize the statements */
	Ret = sqlite3_reset (statement);
	CHECK_SQLITE_ERR(SqliteDbHandle,Ret);
	Ret = sqlite3_finalize (statement);
	--Preparecount;
	CHECK_SQLITE_ERR(SqliteDbHandle,Ret);

#undef	Nat64
#undef	Nat32
#undef	Int32
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	NO
#undef	NAME
#undef	A

	return RetVal;
}


int CHsvProgramData_mpgdb_Priv::GetDataFromTableByKey (int MajorTableId, int TableId, Address Data)
{
	int		RetVal = -1;
	char	*TempString = NULL;
	char	sqlQueryBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	if (MajorTableId == ipgdbconst_Satellite)
	{
		/* For the SELECT query based on the set of keys */
		switch (TableId)
		{
		case	ipgdbconst_SatInfo:
		case	ipgdbconst_CurrentSatInfo:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE LnbNumber = %d ", mGetTableName(TableId), ((HsvPgdatSatInfoData*)Data)->LnbNumber);
			break;

		case	ipgdbconst_DigitalTS:
		case	ipgdbconst_CurrentDigitalTS:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE LnbNumber = %d AND Frequency = %d AND Polarization = %d  ", mGetTableName(TableId), \
				((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->Polarization);
			break;

		case	ipgdbconst_DigitalService:
		case	ipgdbconst_CurrentDigitalService:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE TPID = %d AND ServiceId = %d", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->TPID, ((HsvPgdatDigServiceData*)Data)->ServiceId);
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE PresetNumber = %d ", mGetTableName(TableId), ((HsvPgdatPresetData*)Data)->PresetNumber);
			break;
		default:
			break;
		}
	#ifdef	ENABLE_TIME_TRACE
		t1 = errlib__GetMicrosSinceInit ();
	#endif
		if (TempString != NULL) 
		{
			/* Now execute the query and extract the elements */
			RetVal = ExtractNodeDataFromDatabse (sqlQueryBuf,SQL_TABLE_SMALL_QUERY_LENGTH, TableId, Data);
		}
	}
	else
	{
		/* For the SELECT query based on the set of keys */
		switch (TableId)
		{
		case	ipgdbconst_FrequencyMapTable:
		case	ipgdbconst_CurrentFrequencyMapTable:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d ", mGetTableName(TableId), (int)((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, (int)((HsvPgdatDigFreqMapData*)Data)->Tsid);
			break;

		case	ipgdbconst_Analog:
		case	ipgdbconst_CurrentAnalog:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE PresetNumber = %d  ", mGetTableName(TableId), (int)((HsvPgdatAnalogData*)Data)->PresetNumber);
			break;

		case	ipgdbconst_DigitalTS:
		case	ipgdbconst_CurrentDigitalTS:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE Frequency = %d AND StreamPriority = %d ", mGetTableName(TableId), \
				((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->StreamPriority);
			break;

		case	ipgdbconst_DigitalService:
		case	ipgdbconst_CurrentDigitalService:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency = %d AND StreamPriority = %d", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency, ((HsvPgdatDigServiceData*)Data)->StreamPriority);
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE PresetNumber = %d ", mGetTableName(TableId), ((HsvPgdatPresetData*)Data)->PresetNumber);
			break;
		default:
			break;
		}

		if (TempString != NULL) 
		{
			/* Now execute the query and extract the elements */
			RetVal = ExtractNodeDataFromDatabse (sqlQueryBuf,SQL_TABLE_SMALL_QUERY_LENGTH, TableId, Data);
		}
	}
	
	return RetVal;
}


Bool CHsvProgramData_mpgdb_Priv::ipgdb_GetByKey       ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	SEM_TAKE(mProgramMapSem);
    //PrintfNotice (" EuChannelLib: Calling %s from 0x%x \n", __FUNCTION__, (unsigned int)__builtin_return_address(0));
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			RetVal = GetDataFromTableByKey (GETMAJORTABLEID(tableid), SubTableId, channeldata);
		}
		else
		{
			RetVal = srtdb2_QueryOnKey(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata), channeldata);
		}
		break;
	default:
		RetVal = FALSE;
		break;
	}

	SEM_GIVE(mProgramMapSem);
	return RetVal;
}

int CHsvProgramData_mpgdb_Priv::GetCurrentIndexFromTable (int TableId, Address Data, Bool *Valid)
{
	int		RetVal = -1;
	int		Index = 0;
	char	*tempString = NULL;
	sqlite3_stmt	*Statement = NULL;
	char	sqlQueryBuf[SQL_TABLE_SMALL_QUERY_LENGTH * 2];
	int		retryCount = 0;

	*Valid = FALSE;

	if(mCurrentTable == ipgdbconst_Satellite)
	{
		/* Make the Query to get Index based on the fixed keys */
		switch (TableId)
		{
		case	ipgdbconst_SatInfo:
		case	ipgdbconst_CurrentSatInfo:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE LnbNumber = %d ", mGetTableName(TableId), (int)((HsvPgdatSatInfoData*)Data)->LnbNumber);
			break;

		case	ipgdbconst_DigitalTS:
		case	ipgdbconst_CurrentDigitalTS:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE LnbNumber = %d AND Frequency = %d AND Polarization = %d  ", mGetTableName(TableId), \
				(int)((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->Polarization);
			break;

		case	ipgdbconst_DigitalService:
		case	ipgdbconst_CurrentDigitalService:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE TPID = %d AND ServiceId = %d", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->TPID, ((HsvPgdatDigServiceData*)Data)->ServiceId);
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM  %s WHERE PresetNumber = %d ", mGetTableName(TableId), ((HsvPgdatPresetData*)Data)->PresetNumber);
			break;
		default:
			break;
		}
	}
	else
	{
		/* Make the Query to get Index based on the fixed keys */
		switch (TableId)
		{
		case	ipgdbconst_FrequencyMapTable:
		case	ipgdbconst_CurrentFrequencyMapTable:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d", mGetTableName(TableId), (int)((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, (int)((HsvPgdatDigFreqMapData*)Data)->Tsid);
			break;

		case	ipgdbconst_Analog:
		case	ipgdbconst_CurrentAnalog:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE PresetNumber = %d ", mGetTableName(TableId), (int)((HsvPgdatAnalogData*)Data)->PresetNumber);
			break;

		case	ipgdbconst_DigitalTS:
		case	ipgdbconst_CurrentDigitalTS:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE Frequency = %d AND StreamPriority = %d ", mGetTableName(TableId), \
				((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->StreamPriority);
			break;

		case	ipgdbconst_DigitalService:
		case	ipgdbconst_CurrentDigitalService:
			tempString = sqlite3_snprintf ((SQL_TABLE_SMALL_QUERY_LENGTH * 2), sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency = %d AND StreamPriority = %d", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency, ((HsvPgdatDigServiceData*)Data)->StreamPriority);
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM  %s WHERE PresetNumber = %d ", mGetTableName(TableId), ((HsvPgdatPresetData*)Data)->PresetNumber);
			break;
		default:
			break;
		}
	}

	
	if (tempString != NULL) 
	{
		//PrintfNotice ("EuChannelLib: DbgPrint sqlQueryStatement in Func %s and line %d is %s \n", __FUNCTION__,__LINE__,sqlQueryBuf);

		/* Now extract the Index value */
		RetVal = sqlite3_prepare_v2 (SqliteDbHandle, sqlQueryBuf, (SQL_TABLE_SMALL_QUERY_LENGTH*2), &Statement, NULL);
		++Preparecount;
		
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		if(RetVal == SQLITE_OK)
		{
			SQLITE_STEP(Statement,retryCount,RetVal);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
			if (RetVal == SQLITE_ROW)
			{
				*Valid = TRUE;
				Index = sqlite3_column_int (Statement, 0);
				//PrintfNotice ("EuChannelLib: DbgPrint, Found Index value is %d \n", Index);
			}
			RetVal = sqlite3_finalize (Statement);
			--Preparecount;
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		}
	}
	
	return Index;
}


int CHsvProgramData_mpgdb_Priv::ipgdb_GetIndex       ( int tableid, int *index, Address channeldata)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
    //PrintfNotice (" EuChannelLib: Calling %s from 0x%x \n", __FUNCTION__, (unsigned int)__builtin_return_address(0));

	SEM_TAKE(mProgramMapSem);

	*index = 0;
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			*index  = GetCurrentIndexFromTable (SubTableId, channeldata, &RetVal);
		}
		else
		{
			if(FALSE == srtdb2_SearchOnKey(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata), index))
            {
                RetVal = -1;
            }
		}
		break;
	default:
		RetVal = FALSE;
		break;
	}

	SEM_GIVE(mProgramMapSem);
	
	return RetVal;

}

int CHsvProgramData_mpgdb_Priv::GetDataFromTableByIndex (int TableId, int Index, Address Data)
{
	int		RetVal = FALSE;
	char	sqlQueryBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	switch (TableId)
	{
	case	ipgdbconst_FrequencyMapTable:
	case	ipgdbconst_CurrentFrequencyMapTable:
	case	ipgdbconst_Analog:
	case	ipgdbconst_CurrentAnalog:
	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
		/* Form SELECT query for particular Index from the given table. Execute and 
			extract the elements */
		sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
			"SELECT * FROM %s WHERE DbIndex = %d ", mGetTableName(TableId), Index);
		RetVal = ExtractNodeDataFromDatabse (sqlQueryBuf,SQL_TABLE_SMALL_QUERY_LENGTH, TableId, Data);

		break;

	default:
		break;
	}
	
	return RetVal;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_GetByIndex     ( int tableid, int index, Address channeldata)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	SEM_TAKE(mProgramMapSem);
	//PrintfNotice (" EuChannelLib: Calling %s from 0x%x \n", __FUNCTION__, (unsigned int)__builtin_return_address(0));
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			RetVal = GetDataFromTableByIndex (SubTableId, index, channeldata);
		}
		else
		{
			RetVal = srtdb2_QueryOnIndex(mGetDBTableIds(SubTableId), index, channeldata);
		}
		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	return RetVal;

}

int CHsvProgramData_mpgdb_Priv::GetRangeOfDataByKey (int ReqTableId, int NoofKeys, Address Data, int *From, int *To)
{
	int		RetVal = -1;
	sqlite3_stmt	*statement = NULL;
	char	queryStatmentBuf[SQL_TABLE_SMALL_QUERY_LENGTH*2];
	int		retryCount = 0;

	//PrintfNotice (" EuChannelLib : DbgPrint GetRange \n");
	*From = *To = 0;

	if (mCurrentTable == ipgdbconst_Satellite)
	{
		switch (ReqTableId)
		{
		case	ipgdbconst_SatInfo:			/* Key is LnbNumber */
		case	ipgdbconst_CurrentSatInfo:
			if (NoofKeys == 1)
			{
			/* Here only one key is present. So the *From and *To has to be same */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
				if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatSatInfoData*)Data)->LnbNumber);\
					RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					if (RetVal == SQLITE_OK) \
					{\
						SQLITE_STEP(statement,retryCount,RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							*From = *To = sqlite3_column_int (statement, 0);\
							sqlite3_finalize (statement);\
							--Preparecount;\
						}\
						else\
						{\
						sqlite3_reset(statement);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						}\
					}\
				}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			}
			break;

		case	ipgdbconst_DigitalTS:		/* Keys - LnbNumber: Frequency: Polarization */
		case	ipgdbconst_CurrentDigitalTS:
			/* Here totally 3 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber):\
			((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(Db) FROM %s WHERE LnbNumber = %d AND Frequency = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency):\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(Index) FROM %s WHERE LnbNumber = %d AND Frequency = %d AND Polarization = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->Polarization));\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				++Preparecount;\
				if (RetVal == SQLITE_OK) \
				{\
					/* Get the MAX and MIN Index values for given condition and assign to From and To */\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal==SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber):\
							((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE LnbNumber = %d AND Frequency = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency):\
											   sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE LnbNumber = %d AND Frequency = %d AND Polarization = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->Polarization));\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						++Preparecount;\
						if (RetVal == SQLITE_OK) \
						{\
							SQLITE_STEP(statement,retryCount,RetVal);\
							if(RetVal==SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
								--Preparecount;\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							--Preparecount;\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					--Preparecount;\
					}\
				}\
			}	

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_DigitalService:	/* Keys - TpId:	SvcId	*/
		case	ipgdbconst_CurrentDigitalService:
			/* Here totally 3 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
				(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->TPID): \
								  sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d AND ServiceId = %d  ", TableName, ((HsvPgdatDigServiceData*)Data)->TPID, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				++Preparecount;\
				if (RetVal == SQLITE_OK) \
				{\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal == SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->TPID): \
									  sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE LnbNumber = %d AND ServiceId = %d  ", TableName, ((HsvPgdatDigServiceData*)Data)->TPID, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						++Preparecount;\
						if (RetVal == SQLITE_OK) \
						{\
							SQLITE_STEP(statement,retryCount,RetVal);\
							if(RetVal == SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
								--Preparecount;\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							--Preparecount;\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					--Preparecount;\
					}\
				}\
			}	

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM

			break;
		case	ipgdbconst_Preset:			/* Key is - PresetNumber */
		case	ipgdbconst_CurrentPreset:
			if (NoofKeys == 1)
			{
			/* Here only one key is present. So the *From and *To has to be same */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
				if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE PresetNumber = %d ", TableName, ((HsvPgdatPresetData*)Data)->PresetNumber);\
					RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					if (RetVal == SQLITE_OK) \
					{\
						SQLITE_STEP(statement,retryCount,RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							*From = *To = sqlite3_column_int (statement, 0);\
							sqlite3_finalize (statement);\
							--Preparecount;\
						}\
						else\
						{\
						sqlite3_reset(statement);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						}\
					}\
				}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			}
			break;
		default:
			 break;
		}
	}
	else
	{
		switch (ReqTableId)
		{
		case	ipgdbconst_FrequencyMapTable:			
		case	ipgdbconst_CurrentFrequencyMapTable:
			/* Here totally 3 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE OriginalNetworkId = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId):\
			((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(Db) FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, ((HsvPgdatDigFreqMapData*)Data)->Tsid):\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(Index) FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d AND Frequency = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, ((HsvPgdatDigFreqMapData*)Data)->Tsid, ((HsvPgdatDigFreqMapData*)Data)->Frequency));\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				++Preparecount;\
				if (RetVal == SQLITE_OK) \
				{\
					/* Get the MAX and MIN Index values for given condition and assign to From and To */\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal==SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE OriginalNetworkId = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId):\
							((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, ((HsvPgdatDigFreqMapData*)Data)->Tsid):\
											   sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d AND Frequency = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, ((HsvPgdatDigFreqMapData*)Data)->Tsid, ((HsvPgdatDigFreqMapData*)Data)->Frequency));\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						++Preparecount;\
						if (RetVal == SQLITE_OK) \
						{\
							SQLITE_STEP(statement,retryCount,RetVal);\
							if(RetVal==SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
								--Preparecount;\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							--Preparecount;\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					--Preparecount;\
					}\
				}\
			}	

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_Analog:			
		case	ipgdbconst_CurrentAnalog:
			/* Here totally 2 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE PresetNumber = %d ", TableName, ((HsvPgdatAnalogData*)Data)->PresetNumber):\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(Db) FROM %s WHERE PresetNumber = %d AND Frequency = %d ", TableName, ((HsvPgdatAnalogData*)Data)->PresetNumber, ((HsvPgdatAnalogData*)Data)->Frequency);\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				++Preparecount;\
				if (RetVal == SQLITE_OK) \
				{\
					/* Get the MAX and MIN Index values for given condition and assign to From and To */\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal==SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE PresetNumber = %d ", TableName, ((HsvPgdatAnalogData*)Data)->PresetNumber):\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE PresetNumber = %d AND Frequency = %d ", TableName, ((HsvPgdatAnalogData*)Data)->PresetNumber, ((HsvPgdatAnalogData*)Data)->Frequency);\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						++Preparecount;\
						if (RetVal == SQLITE_OK) \
						{\
							SQLITE_STEP(statement,retryCount,RetVal);\
							if(RetVal==SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
								--Preparecount;\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							--Preparecount;\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					--Preparecount;\
					}\
				}\
			}	

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_DigitalTS:		
		case	ipgdbconst_CurrentDigitalTS:
			/* Here totally 2 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE Frequency = %d ORDER BY Frequency DESC LIMIT 1", TableName, ((HsvPgdatDigTSData*)Data)->Frequency):\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE Frequency = %d AND StreamPriority = %d ORDER BY Frequency DESC LIMIT 1", TableName, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->StreamPriority);\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				++Preparecount;\
				if (RetVal == SQLITE_OK) \
				{\
					/* Get the MAX and MIN Index values for given condition and assign to From and To */\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal==SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE Frequency = %d ORDER BY Frequency ASC LIMIT 1", TableName, ((HsvPgdatDigTSData*)Data)->Frequency):\
											sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE Frequency = %d AND StreamPriority = %d ORDER BY Frequency ASC LIMIT 1 ", TableName, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->StreamPriority);\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						++Preparecount;\
						if (RetVal == SQLITE_OK) \
						{\
							SQLITE_STEP(statement,retryCount,RetVal);\
							if(RetVal==SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
								--Preparecount;\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							--Preparecount;\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					--Preparecount;\
					}\
				}\
			}	

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_DigitalService:	
		case	ipgdbconst_CurrentDigitalService:
			/* Here totally 4 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
				(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d ORDER BY ServiceId DESC LIMIT 1", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId): \
				((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d ORDER BY ServiceId DESC LIMIT 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId): \
				((NoofKeys == 3) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency = %d ORDER BY ServiceId DESC LIMIT 1", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency): \
									sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency = %d AND StreamPriority = %d ORDER BY ServiceId DESC LIMIT 1", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency, ((HsvPgdatDigServiceData*)Data)->StreamPriority))); \
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH*2, &statement, NULL);\
				++Preparecount;\
				if (RetVal == SQLITE_OK) \
				{\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal == SQLITE_ROW)\
					{\
						*From = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						--Preparecount;\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d ORDER BY ServiceId ASC LIMIT 1", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId): \
						((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d ORDER BY ServiceId ASC LIMIT 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId): \
						((NoofKeys == 3) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency = %d ORDER BY ServiceId ASC LIMIT 1", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency): \
											sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH*2, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency = %d AND StreamPriority = %d ORDER BY ServiceId ASC LIMIT 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency, ((HsvPgdatDigServiceData*)Data)->StreamPriority))); \
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH*2, &statement, NULL);\
						++Preparecount;\
						if (RetVal == SQLITE_OK) \
						{\
							SQLITE_STEP(statement,retryCount,RetVal);\
							if(RetVal == SQLITE_ROW)\
							{\
								*To = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
								--Preparecount;\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							--Preparecount;\
							}\
						}\
					}\
					else \
					{\
						sqlite3_reset(statement);\
						sqlite3_finalize (statement);\
						--Preparecount;\
					}\
				}\
			}	

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;
		case	ipgdbconst_Preset:			/* Key is - PresetNumber */
		case	ipgdbconst_CurrentPreset:
			if (NoofKeys == 1)
			{
			/* Here only one key is present. So the *From and *To has to be same */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
				if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE PresetNumber = %d ", TableName, ((HsvPgdatPresetData*)Data)->PresetNumber);\
					RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					if (RetVal == SQLITE_OK) \
					{\
						SQLITE_STEP(statement,retryCount,RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							*From = *To = sqlite3_column_int (statement, 0);\
							sqlite3_finalize (statement);\
							--Preparecount;\
						}\
						else\
						{\
							sqlite3_reset(statement);\
							sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			}
			break;
		default:
			 break;
		}
	}

	return RetVal;
}


Bool CHsvProgramData_mpgdb_Priv::ipgdb_GetRange       ( int tableid, int noofkeys, Address channeldata, int *from, int *to)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
	//PrintfNotice (" EuChannelLib: Calling %s from 0x%x \n", __FUNCTION__, (unsigned int)__builtin_return_address(0));

	SEM_TAKE(mProgramMapSem);
	
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_ROW != GetRangeOfDataByKey (SubTableId, noofkeys, channeldata, from, to))
			{
				RetVal = FALSE;
			}
		}
		else
		{

			switch (noofkeys)
			{
			case 1:
				RetVal = srtdb2_SearchOnPrimaryKey(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), from, to);
				break;
			case 2:
				RetVal = srtdb2_SearchOnPrimaryAndSecondaryKey(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), from, to);
				break;
			case 3:
				/* Not supported yet */
				ASSERT(FALSE);
				break;
			default:
				ASSERT(FALSE);
				break;
			}
		}

		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	return RetVal;
}

void CHsvProgramData_mpgdb_Priv::PrepareUpdateElementStringForSinglePrepare (int TableId,	char *statementbuf, char *tempString)
{

/* Based on the macro type fill in the string */
#define		Nat32	1
#define		Int32	2
#define		Nat16	3
#define		Int16	4
#define		Nat8	5
#define		Nat64	6
#define		NONE	0
#define		A(x)	x

	/* Based on type, fill the values for insertion */
	switch (TableId)
	{
	case	ipgdbconst_SatInfo:
	case	ipgdbconst_CurrentSatInfo:
#define	SATINFO_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef	SATINFO_ITEM
		break;

	case	ipgdbconst_FrequencyMapTable:
	case	ipgdbconst_CurrentFrequencyMapTable:
#define	FREQMAP_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_freqmapitems.h"
#else
#include "hsvpgdat_freqmapitems.h"
#endif
#undef	FREQMAP_ITEM
		break;

	case	ipgdbconst_Analog:
	case	ipgdbconst_CurrentAnalog:
#define	ANALOG_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_analogitems.h"
#else
#include "hsvpgdat_analogitems.h"
#endif
#undef	ANALOG_ITEM
		break;

	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
#define	DIGTS_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

if (mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digtsitems.h"
#else
#include "hsvpgdat_sat_digtsitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digtsitems.h"
#else
#include "hsvpgdat_digtsitems.h"
#endif
}
#undef	DIGTS_ITEM
		break;

	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

if(mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digsrvcitems.h"
#else
#include "hsvpgdat_sat_digsrvcitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digsrvcitems.h"
#else
#include "hsvpgdat_digsrvcitems.h"
#endif
}
#undef	DIGSRVC_ITEM
		break;

	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
#define	PRESET_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

if(mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_presetitems.h"
#else
#include "hsvpgdat_sat_presetitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_presetitems.h"
#else
#include "hsvpgdat_presetitems.h"
#endif
}
#undef	PRESET_ITEM

		break;

	default:
		break;
	}

#undef	Nat64
#undef	Nat32
#undef	Int32
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A

	sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "dummy=?");
	strcat (statementbuf, tempString);

}

sqlite3_stmt* CHsvProgramData_mpgdb_Priv::PrepareSqlUpdateStatement (int InsertTableId)
{
	Nat32	RetVal = err_Ok;
	char 	tempString[SQL_TEMP_STRING_LENGTH];
	sqlite3_stmt	*statement = NULL;
	
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
			sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, sqldbTableInsertStatementBuf, "UPDATE %s SET ", TableName);\
			sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "DbIndex=?, ");\
			strcat (sqldbTableInsertStatementBuf, tempString);\
			PrepareUpdateElementStringForSinglePrepare(InsertTableId,sqldbTableInsertStatementBuf,tempString);\
			sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, " WHERE DbIndex=?;");\
			strcat (sqldbTableInsertStatementBuf, tempString);\
		}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM
//PrintfNotice("Rohit: PrepareSqlUpdateStatement: Update statement = %s", sqldbTableInsertStatementBuf);
	RetVal = sqlite3_prepare_v2 (SqliteDbHandle, sqldbTableInsertStatementBuf, SQL_TABLE_MEDIUM_QUERY_LENGTH, &statement, NULL);
	++Preparecount;
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	if (RetVal != SQLITE_OK)
	{
		statement = NULL;
	}
//PrintfNotice("Rohit: PrepareSqlUpdateStatement: statement = %d", statement);
	return statement;
}

int CHsvProgramData_mpgdb_Priv::FillUpdateStatement (sqlite3_stmt *InsertHandle, int TableId, Address Data)
{
	int			count = 2;
	//char		tempBuff[66];
	Nat16		tempBuff[33];
	int			tempVar;

	/* Update is SAME filling mechanism as INSERT */
/* Based on the macro type fill in the string */
#define		Nat32	1
#define		Int32	2
#define		Nat16	3
#define		Int16	4
#define		Nat8	5
#define 	Nat64	6
#define		NONE	0
#define		A(x)	x

	/* Based on type, fill the values for insertion */
	switch (TableId)
	{
	case	ipgdbconst_SatInfo:
	case	ipgdbconst_CurrentSatInfo:
#define	SATINFO_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatSatInfoData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef	SATINFO_ITEM
		break;

	case	ipgdbconst_FrequencyMapTable:
	case	ipgdbconst_CurrentFrequencyMapTable:
#define	FREQMAP_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigFreqMapData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_freqmapitems.h"
#else
#include "hsvpgdat_freqmapitems.h"
#endif
#undef	FREQMAP_ITEM
		break;

	case	ipgdbconst_Analog:
	case	ipgdbconst_CurrentAnalog:
#define	ANALOG_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatAnalogData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_analogitems.h"
#else
#include "hsvpgdat_analogitems.h"
#endif
#undef	ANALOG_ITEM
		break;

	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
#define	DIGTS_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigTSData,InsertHandle,tempVar,tempBuff,count)

if(mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digtsitems.h"
#else
#include "hsvpgdat_sat_digtsitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digtsitems.h"
#else
#include "hsvpgdat_digtsitems.h"
#endif
}
#undef	DIGTS_ITEM
		break;

	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigServiceData,InsertHandle,tempVar,tempBuff,count)

if(mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_digsrvcitems.h"
#else
#include "hsvpgdat_sat_digsrvcitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_digsrvcitems.h"
#else
#include "hsvpgdat_digsrvcitems.h"
#endif
}
#undef	DIGSRVC_ITEM
		break;

	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
#define	PRESET_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatPresetData,InsertHandle,tempVar,tempBuff,count)

if(mCurrentTable == ipgdbconst_Satellite) {
#ifndef __cplusplus
#include "data/hsvpgdat_sat_presetitems.h"
#else
#include "hsvpgdat_sat_presetitems.h"
#endif
}
else {
#ifndef __cplusplus
#include "data/hsvpgdat_presetitems.h"
#else
#include "hsvpgdat_presetitems.h"
#endif
}
#undef	PRESET_ITEM
		break;

	default:
		break;
	}

#undef	Nat64
#undef	Nat32
#undef	Int32
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A

	sqlite3_bind_int(InsertHandle,count,0);
	count++;
//PrintfNotice("Rohit: FillUpdateStatement: Count = %d", count);
	return count;
}
Bool CHsvProgramData_mpgdb_Priv::mCheckForUpdatesDigitalTS (void *Data, int Index, int *NoItemsChangedDigitalTS, int *ItemIDs)
{
	*NoItemsChangedDigitalTS = 0;
	return FALSE;
}
Bool CHsvProgramData_mpgdb_Priv::mCheckForUpdatesDigitalTSInTempDb (int SubTableId, void *Data, int *NoItemsChangedDigitalTS, int *ItemIDs)
{
//			TraceDebug (m, "%s %d  \n", __FUNCTION__, __LINE__);
			HsvPgdatDigServiceData               	 DbData;
			*NoItemsChangedDigitalTS = 0;
			int count =0;
			int count1=0;
			int comparenamesize=0;

			DbData.OriginalNetworkId = ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId;
			DbData.ServiceId = ((HsvPgdatDigServiceData*)Data)->ServiceId;
			DbData.Frequency = ((HsvPgdatDigServiceData*)Data)->Frequency;
			DbData.StreamPriority = ((HsvPgdatDigServiceData*)Data)->StreamPriority;
			
			if(TRUE == srtdb2_QueryOnKey(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, &DbData), mGetSecondaryKey(SubTableId, &DbData), mGetTertiaryKey(SubTableId, &DbData), mGetQuaternaryKey(SubTableId, &DbData), &DbData))
			{
				for (count = 0; count < 33; count++)
				{
					if (DbData.ChannelName[count] == 0x00)
						break;
				}
				for (count1 = 0; count1 < 33; count1++)
				{
					if (((HsvPgdatDigServiceData*)Data)->ChannelName[count1] == 0x00)
						break;
				}
				if(count1>count){
				comparenamesize=count1;
				}
				else if(count>count1){	
				comparenamesize=count;
				}
				else if(count==count1){
				comparenamesize=count1=count;
				}
				//TraceNotice (m,"Num Characters in ChannelName %d ", count);
				if (memcmp(DbData.ChannelName,((HsvPgdatDigServiceData*)Data)->ChannelName, comparenamesize*sizeof(Nat16)))
				{
				             ItemIDs[*NoItemsChangedDigitalTS] = 12;
				             (*NoItemsChangedDigitalTS)++;
							  TraceNotice(m," ChannelName Change NoItemsChangedDigitalTS= %d ",*(NoItemsChangedDigitalTS));
				}
			}
	return TRUE ;			   
}
int CHsvProgramData_mpgdb_Priv::UpdateEntryToTableWithSinglePrepare (int InsertTableId, Address Data)
{
	int		RetVal = -1;
	int		Index = 0, count = 0, LastIndex = 0;
	Bool	Valid = FALSE;
	int  ret = 0, retryCount = 0;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;

	/* Get the index of the table based on keys provided by user */
	Index = GetCurrentIndexFromTable (InsertTableId, Data, &Valid);
//PrintfNotice("Rohit: UpdateEntryToTableWithSinglePrepare: Index found = %d", Index);
	if (Valid == TRUE)
	{
		if (mCurrentTable == ipgdbconst_Satellite)
		{
			handle = SqliteHandleSatMaps;
			num_tbl = MAX_SAT_PGDB_TABLES;
		}
		else
		{
			handle = SqliteHandleMaps;
			num_tbl = MAX_PGDB_TABLES;
		}

//		PrintfNotice("Before for loop\n");
		for (count = 0; count < num_tbl; count++)
		{
			if (InsertTableId == handle[count].SubTableId)
			{
				if (handle[count].UpdateHandle == NULL)
				{
					handle[count].UpdateHandle = PrepareSqlUpdateStatement (InsertTableId);
			
				}
				break;
			}
		}

		if ((count >= num_tbl) || (handle[count].UpdateHandle == NULL))
		{
			RetVal = FALSE;
		}
		else
		{
	 			NoItemsChangedDigitalTS = 0;
			if (InsertTableId == ipgdbconst_DigitalService)
				{
				RetVal = mCheckForUpdatesDigitalTS (Data, Index, &NoItemsChangedDigitalTS, ItemIDs);
				}
			RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		/* Now update entries to this Index */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
				sqlite3_bind_int(handle[count].UpdateHandle,1,Index);\
				LastIndex = FillUpdateStatement(handle[count].UpdateHandle,InsertTableId,Data);\
				ret = sqlite3_bind_int(handle[count].UpdateHandle,LastIndex,Index);\
				SQLITE_STEP(handle[count].UpdateHandle,retryCount,RetVal);\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				RetVal = sqlite3_reset (handle[count].UpdateHandle);\
			}

#include "hsvpgdat_tableinfo.h"

		RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		if(RetVal == SQLITE_BUSY) 	{		
			RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount);
		}

#undef	TABLE_ITEM
		}
	if(TRUE==Notification_enable)
	{
		if (NoItemsChangedDigitalTS)
			{
				for (int i=0;i<NoItemsChangedDigitalTS;i++){
				TraceDebug (m, "%s %d Update channel Preset number=%d",__FUNCTION__, __LINE__,((HsvPgdatDigServiceData*)Data)->PresetNumber);
				insN->OnEvent(IHsvInstallationNotify_EventUpdated, ((((HsvPgdatDigServiceData*)Data)->PresetNumber << 16) | ItemIDs[i]));
				}
			}
	}
	}
	return RetVal;
}


Bool CHsvProgramData_mpgdb_Priv::ipgdb_Update     ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
	NoItemsChangedDigitalTS = 0;
	//PrintfNotice (" EuChannelLib: Calling %s from 0x%x \n", __FUNCTION__, (unsigned int)__builtin_return_address(0));

	SEM_TAKE(mProgramMapSem);
	
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			//PrintfNotice ("EuChannelLib: DbgPrint : Updating the entry for Maj: %d Min : %d \n", GETMAJORTABLEID(tableid), SubTableId);
			
			if (SQLITE_DONE != UpdateEntryToTableWithSinglePrepare (SubTableId, channeldata))
			//if (SQLITE_DONE != UpdateEntryToTable (SubTableId, channeldata))
			{
				RetVal = FALSE;
			}
		}
		else
		{
			if (SubTableId == ipgdbconst_DigitalService)
			{
				//TraceDebug (m, "%s %d \n", __FUNCTION__, __LINE__);
				RetVal = mCheckForUpdatesDigitalTSInTempDb (SubTableId, channeldata, &NoItemsChangedDigitalTS, ItemIDs);
				//TraceDebug (m, "%s %d NoItemsChangedDigitalTS %d\n", __FUNCTION__, __LINE__,NoItemsChangedDigitalTS);
			}
			
			RetVal = srtdb2_Update(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata), channeldata);
	
			if(TRUE==Notification_enable)
			{
				//TraceDebug (m, "%s %d \n", __FUNCTION__, __LINE__);
				if (NoItemsChangedDigitalTS)
				{
                    TraceDebug (m, "%s %d Update channel Preset number=%d, NoItemsChangedDigitalTS=%d",__FUNCTION__, __LINE__,((HsvPgdatDigServiceData*)channeldata)->PresetNumber, NoItemsChangedDigitalTS);
					for (int i=0;i<NoItemsChangedDigitalTS;i++){
						insN->OnEvent(IHsvInstallationNotify_EventUpdated, ((((HsvPgdatDigServiceData*)channeldata)->PresetNumber << 16) | ItemIDs[i]));
					}
				}
			}
		}
		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	return RetVal;
}

void CHsvProgramData_mpgdb_Priv::ipgdb_EnableAutoCommit(Bool enable)
{
	/* Set the variables to start the autocommit */
	mAutoCommitEnabled = enable;
//	mSetDirty(FALSE);
}

void CHsvProgramData_mpgdb_Priv::ipgdb_ChannelTableChanged(void)
{
	pgdatN_OnChannelTableChanged();
}

/* Initialize with Default values */
void CHsvProgramData_mpgdb_Priv::ipgdb_Initialise(int tableid, Address channeldata )
{
	switch(tableid)
    {
	case	ipgdbconst_SatInfo:		
	case	ipgdbconst_CurrentSatInfo:
		*(HsvPgdatSatInfoData*)channeldata = DefaultSatInfoValues;
		break;
	case	ipgdbconst_FrequencyMapTable:		
	case	ipgdbconst_CurrentFrequencyMapTable:
		*(HsvPgdatDigFreqMapData*)channeldata = DefaultFrqMapValues;
		break;
	case	ipgdbconst_Analog:		
	case	ipgdbconst_CurrentAnalog:
		*(HsvPgdatAnalogData*)channeldata = DefaultAnalogValues;
		break;
	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
		*(HsvPgdatDigTSData*)channeldata = DefaultDigTSValues;
		break;
	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
		*(HsvPgdatDigServiceData*)channeldata = DefaultDigSvcValues;
		break;
	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
		*(HsvPgdatPresetData*)channeldata = DefaultPresetValues;
		break;
	}
}

void CHsvProgramData_mpgdb_Priv::CopyTempDataToCurrentTable (void)
{
	int	RetVal = 0;
	char 	*TempString = NULL;
	char	CopyStatementBuf[SQL_TABLE_SMALL_QUERY_LENGTH];

	//PrintfNotice ("EuChannelLib Copying..\n");

	if (mCurrentTable == ipgdbconst_Satellite)
	{
		TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, CopyStatementBuf,\
				"INSERT INTO %s SELECT * FROM %s ;", mGetTableName(ipgdbconst_SatInfo),mGetTableName(ipgdbconst_CurrentSatInfo));
		RetVal = sqlite3_exec (SqliteDbHandle, CopyStatementBuf, NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);
	}
	else
	{	
		TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, CopyStatementBuf,\
				"INSERT INTO %s SELECT * FROM %s ;", mGetTableName(ipgdbconst_FrequencyMapTable),mGetTableName(ipgdbconst_CurrentFrequencyMapTable));
		RetVal = sqlite3_exec (SqliteDbHandle, CopyStatementBuf, NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);

		TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, CopyStatementBuf,\
				"INSERT INTO %s SELECT * FROM %s ;", mGetTableName(ipgdbconst_Analog),mGetTableName(ipgdbconst_CurrentAnalog));
		RetVal = sqlite3_exec (SqliteDbHandle, CopyStatementBuf, NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);
	}
	
	TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, CopyStatementBuf,\
			"INSERT INTO %s SELECT * FROM %s ;", mGetTableName(ipgdbconst_DigitalTS),mGetTableName(ipgdbconst_CurrentDigitalTS));
	RetVal = sqlite3_exec (SqliteDbHandle, CopyStatementBuf, NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);

	TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, CopyStatementBuf,\
			"INSERT INTO %s SELECT * FROM %s ;", mGetTableName(ipgdbconst_DigitalService),mGetTableName(ipgdbconst_CurrentDigitalService));
	RetVal = sqlite3_exec (SqliteDbHandle, CopyStatementBuf, NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);

	TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, CopyStatementBuf,\
			"INSERT INTO %s SELECT * FROM %s ;", mGetTableName(ipgdbconst_Preset),mGetTableName(ipgdbconst_CurrentPreset));
	RetVal = sqlite3_exec (SqliteDbHandle, CopyStatementBuf, NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);

}

#if 0

void CHsvProgramData_mpgdb_Priv::ipgdb_UpdateChannelMapFromTemp (void)
{
	/* TODO */
	/* Delete the entries from the current table here */

	SEM_TAKE(mProgramMapSem);

	if (mCurrentTable == ipgdbconst_Cable) {
		ClearAllTables (ipgdbconst_Cable);
	}
	else if (mCurrentTable == ipgdbconst_Antenna) {
		ClearAllTables (ipgdbconst_Antenna);
	}
	else {
		ClearAllTables (ipgdbconst_Satellite);
	}

	/* Copy the data from the temp tables to the current table here */
	CopyTempDataToCurrentTable ();
	
	SEM_GIVE(mProgramMapSem);
}
#endif


void CHsvProgramData_mpgdb_Priv::chmapop_Lock(void)
{
    SEM_TAKE(mProgramMapSem);
}

void CHsvProgramData_mpgdb_Priv::chmapop_UnLock(void)
{
    SEM_GIVE(mProgramMapSem);
} 

FResult CHsvProgramData_mpgdb_Priv::chmapop_ReloadFromFlash(int tableid)
{
	FResult		Err = err_Ok;
//	mGetDirectoryPath(mDirectory);

	/* Load table from mDirectory */
//	Err = (mLoadTable (tableid, mDirectory) == TRUE) ? err_Ok: err_FileError;

	return TRUE;
}
   
FResult CHsvProgramData_mpgdb_Priv::chmapop_CommitToFlash(int tableid)
{
	FResult		Err = err_Ok;

//	mGetDirectoryPath(mDirectory);
	/* Write table to mDirectory */
//	Err = (mCommitTable (tableid, mDirectory) == TRUE) ? err_Ok: err_FileError;

	pgdatN_OnChannelTableChanged();

	return Err;
}
    
FResult CHsvProgramData_mpgdb_Priv::chmapop_LoadChannelTable(int tableid, char* dir)
{
	FResult		Err = err_Ok;

	/* Load table from requested directory */
//	Err = (mLoadTable (tableid, dir) == TRUE) ? err_Ok: err_FileError;

	return Err;
}
    
FResult CHsvProgramData_mpgdb_Priv::chmapop_SaveChannelTable(int tableid, char* dir)
{
	FResult		Err = err_Ok;

	/* Save table to requested dirctory */
//	Err = (mCommitTable (tableid, dir) == TRUE) ? err_Ok: err_FileError;

	return Err;
}
   
void CHsvProgramData_mpgdb_Priv::chmapop_SetDirtyBit(void)
{
//	mSetDirty(TRUE);
}
   
void CHsvProgramData_mpgdb_Priv::chmapop_EnableAutoCommit(Bool enable)
{
	mAutoCommitEnabled = enable;
//	mSetDirty(FALSE);
}
    
void CHsvProgramData_mpgdb_Priv::chmapop_ChannelTableChanged(void)
{
	pgdatN_OnChannelTableChanged();
}
	
FResult CHsvProgramData_mpgdb_Priv::chmapop_LoadChannelExternal(char* dir)
{
	FResult	Err = err_NotSupported;
	UNUSED(dir);
	/*TODO: */
	return Err;
}
    
FResult CHsvProgramData_mpgdb_Priv::chmapop_SaveChannelExternal(char* dir)
{
	FResult	Err = err_NotSupported;
	UNUSED(dir);
	/*TODO: */
	return Err;
}
	
FResult CHsvProgramData_mpgdb_Priv::chmapop_GetMediumFromTable(char *dir, int *medium)
{
	FResult	Err = err_NotSupported;
	UNUSED(dir);
	UNUSED(medium);
	/*TODO: */
	return Err;
}

/* SQLITE DELETE Functionality */
int CHsvProgramData_mpgdb_Priv::DeleteEntryFromTable (int deleteTableId, Address Data)
{
	int		RetVal = -1, Ret = -1;
	int		Index = 0,retryCount = 0;
	Bool	Valid = FALSE;
	char	sqlDeleteBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	/* Get index corresponding to given keys */
	Index = GetCurrentIndexFromTable (deleteTableId, Data, &Valid);
	//PrintfNotice ("EuChannelLib: In Func %s @ %d Index for deletion %d validity %d \n",__FUNCTION__, __LINE__, Index, Valid);

	if (Valid == TRUE)
	{

		RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

		/* Delete the entire row from table. Also decrement the Index of all higher Index; values */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		if ((mCurrentTable == MajorTableId) && (TableId == deleteTableId)) {\
			sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlDeleteBuf, "DELETE FROM %s WHERE DbIndex = %d", TableName, Index);\
			RetVal = sqlite3_exec (SqliteDbHandle, sqlDeleteBuf, NULL, NULL, NULL);\
			if (RetVal == SQLITE_OK)\
			{\
				sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlDeleteBuf, "UPDATE %s SET DbIndex=DbIndex-1 WHERE DbIndex > %d ", TableName, Index);\
				RetVal = sqlite3_exec (SqliteDbHandle, sqlDeleteBuf, NULL, NULL, NULL);\
			}\
		}
#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

		Ret = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle,Ret);
		if(Ret == SQLITE_BUSY) 	
		{
			RETRY_COMMIT(SqliteDbHandle,Ret,retryCount);
		}

#ifdef	ENABLE_TIME_TRACE
		t2 = errlib__GetMicrosSinceInit ();
		PRINT_TIMING_INFO("DeleteEntryFromTable",t1,t2);
#endif

	}

	return RetVal;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_Delete     ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
	//PrintfNotice (" EuChannelLib: Calling %s from 0x%x \n", __FUNCTION__, (unsigned int)__builtin_return_address(0));

	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		//PrintfNotice ("EuChannelLib: DbgPrint : Deleting the entry for Maj: %d Min : %d \n", GETMAJORTABLEID(tableid), SubTableId);
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_DONE != DeleteEntryFromTable (SubTableId, channeldata))
			{
				RetVal = FALSE;
			}
		}
		else
		{
			RetVal = srtdb2_Delete(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata));
		}

		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	if (TRUE==Notification_enable)
		{
			if(SubTableId==ipgdbconst_Preset)
			{
				HsvPgdatPresetData	*preset;
				preset = (HsvPgdatPresetData*) channeldata;
				insN->OnEvent(IHsvInstallationNotify_EventPresetDeleted,(int)preset->PresetNumber);
			}
		}
	return RetVal;
}

/* SQLITE INSERT Functionality */
int CHsvProgramData_mpgdb_Priv::GetIndexValForInsertion (int majorTableId, int InsertTableId, Address Data, Bool *Valid)
{
	int		RetVal;
	int		Index = 0;
	sqlite3_stmt *statement;
	char	sqlQueryBuf[SQL_TABLE_SMALL_QUERY_LENGTH];
	int		MatchingEntryExist = 0;
	int retryCount = 0;

	*Valid = FALSE;
	/* Main intention of this function is to have a sort based on primary key alone. 
	Also the index value will literally indicate the index in particular table */
	//PrintfNotice("%s %d InsertTableId %d\n", __FUNCTION__, __LINE__, InsertTableId);

	if (majorTableId == ipgdbconst_Satellite)
	{
		switch (InsertTableId)
		{
		case	ipgdbconst_SatInfo:			/* Key is LnbNumber */
		case	ipgdbconst_CurrentSatInfo:
			/* Here only one key is present. So highest index will be of last element. So increment 
				by 1 to get the free index value*/
	#define	TABLE_ITEM(MajorTableId,TableId, TableName,Type)	\
		GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)

	#include "hsvpgdat_tableinfo.h"
		
	#undef	TABLE_ITEM
			*Valid = TRUE;
			break;

		case	ipgdbconst_DigitalTS:		/* Keys - LnbNumber: Frequency: Polarization */
		case	ipgdbconst_CurrentDigitalTS:
			/* Here the request can be done for LnbNumber Alone */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName,Type)	\
			if (TableId == InsertTableId) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						SQLITE_STEP(statement,retryCount,RetVal);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							if (MatchingEntryExist) \
							{\
								sqlite3_reset(statement);\
								sqlite3_finalize(statement);\
								--Preparecount;\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber);\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								++Preparecount;\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									SQLITE_STEP(statement,retryCount,RetVal);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										sqlite3_finalize(statement);\
										--Preparecount;\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
										if(RetVal == SQLITE_BUSY) 	{\
										RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
										}\
									}\
									else\
									{\
										sqlite3_reset(statement);\
										sqlite3_finalize(statement);\
										--Preparecount;\
										GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
										Index++;\
									}\
								}\
							}\
						}\
						else \
						{\
							sqlite3_reset(statement);\
							sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}\
				*Valid = TRUE;\
			}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_DigitalService:	/* Keys - TpId:	SvcId	*/
		case	ipgdbconst_CurrentDigitalService:
			/* Here the request can be done for TpId alone	*/
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if (TableId == InsertTableId) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE TPID = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->TPID);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						SQLITE_STEP(statement,retryCount,RetVal);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							if (MatchingEntryExist)\
							{\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE TPID = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->TPID);\
								/*PrintfNotice ("S2ChannelLib: ANEESH: DbgPrint Query is %s \n",sqlQueryBuf);*/\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								++Preparecount;\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									SQLITE_STEP(statement,retryCount,RetVal);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										/*PrintfNotice ("S2ChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
										sqlite3_finalize(statement);\
										--Preparecount;\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
										if(RetVal == SQLITE_BUSY) 	{\
										RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
										}\
									}\
									else\
									{\
										sqlite3_reset(statement);\
										sqlite3_finalize(statement);\
										--Preparecount;\
										GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
										Index++;\
										/*PrintfNotice ("S2ChannelLib: Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
									}\
								}\
							}\
						}\
						else\
						{\
							sqlite3_reset(statement);\
							sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}\
				*Valid = TRUE;\
			}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_Preset:			/* Key is - PresetNumber */
		case	ipgdbconst_CurrentPreset:
			/* Here only one key is present. So index will be the highest index of the table */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			*Valid = TRUE;
			break;

		default:
			 break;
		}
	}
	else
	{
		switch (InsertTableId)
		{
		case	ipgdbconst_Analog:
		case	ipgdbconst_CurrentAnalog:
		/* Key is preset number */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE PresetNumber = %d ", TableName, ((HsvPgdatAnalogData*)Data)->PresetNumber);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						SQLITE_STEP(statement,retryCount,RetVal);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							RetVal = sqlite3_finalize(statement);\
							--Preparecount;\
							if (MatchingEntryExist)\
							{\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE PresetNumber = %d ", TableName, ((HsvPgdatAnalogData*)Data)->PresetNumber);\
								/*PrintfNotice ("EuChannelLib: ANEESH: DbgPrint Query is %s \n",sqlQueryBuf);*/\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								++Preparecount;\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									SQLITE_STEP(statement,retryCount,RetVal);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
										sqlite3_finalize(statement);\
										--Preparecount;\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
										if(RetVal == SQLITE_BUSY) 	{\
										RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \	
										}\
									}\
									else\
									{\
										sqlite3_reset(statement);\
										sqlite3_finalize(statement);\
										--Preparecount;\
										GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
										Index++;\
										/*PrintfNotice ("EuChannelLib: Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
									}\
								}\
							}\
						}\
						else\
						{\
							RetVal = sqlite3_reset(statement);\
							RetVal = sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}\
				*Valid = TRUE;\
			}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			*Valid = TRUE;
			break;

		case	ipgdbconst_FrequencyMapTable:
		case	ipgdbconst_CurrentFrequencyMapTable:
		/* Key is preset number */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE OriginalNetworkId = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						++Preparecount;\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						SQLITE_STEP(statement,retryCount,RetVal);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							sqlite3_finalize(statement);\
							--Preparecount;\
							if (MatchingEntryExist)\
							{\
								MatchingEntryExist = 0;\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, ((HsvPgdatDigFreqMapData*)Data)->Tsid);\
								/*PrintfNotice ("EuChannelLib: ANEESH: DbgPrint Query is %s \n",sqlQueryBuf);*/\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								++Preparecount;\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									SQLITE_STEP(statement,retryCount,RetVal);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										MatchingEntryExist = sqlite3_column_int (statement, 0);\
										sqlite3_finalize(statement);\
										--Preparecount;\
										if (MatchingEntryExist)\
										{\
											sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE OriginalNetworkId = %d AND Tsid = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId, ((HsvPgdatDigFreqMapData*)Data)->Tsid);\
											RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
											++Preparecount;\
											CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
											if (RetVal == SQLITE_OK) {\
												SQLITE_STEP(statement,retryCount,RetVal);\
												CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
												if(RetVal==SQLITE_ROW)\
												{\
													Index = sqlite3_column_int (statement, 0);\
													Index++;\
													/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
													sqlite3_finalize(statement);\
													--Preparecount;\
													/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
													RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
													RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
													if(RetVal == SQLITE_BUSY)	{\
													RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \	
													}\
												}\
												else\
												{\
													RetVal = sqlite3_reset(statement);\
													RetVal = sqlite3_finalize(statement);\
													--Preparecount;\
													GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
													Index++;\
													/*PrintfNotice ("EuChannelLib: Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
												}\
											}\
										}\
									}\
									else\
									{\
										RetVal = sqlite3_finalize(statement);\
										--Preparecount;\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE OriginalNetworkId = %d ", TableName, ((HsvPgdatDigFreqMapData*)Data)->OriginalNetworkId);\
										RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
										++Preparecount;\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										if (RetVal == SQLITE_OK) {\
											SQLITE_STEP(statement,retryCount,RetVal);\
											CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
											if(RetVal==SQLITE_ROW)\
											{\
												Index = sqlite3_column_int (statement, 0);\
												Index++;\
												/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
												sqlite3_finalize(statement);\
												--Preparecount;\
												/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
												RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
												CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
												sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
												RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
												CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
												RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
												CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
												if(RetVal == SQLITE_BUSY) 	{\
												RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
												}\
											}\
											else\
											{\
												RetVal = sqlite3_reset(statement);\
												RetVal = sqlite3_finalize(statement);\
												--Preparecount;\
												GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
												Index++;\
												/*PrintfNotice ("EuChannelLib: Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
											}\
										}\
									}\
								}\
							}\
						}\
						else\
						{\
							RetVal = sqlite3_reset(statement);\
							RetVal = sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}\
				*Valid = TRUE;\
			}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			*Valid = TRUE;
			break;


		case	ipgdbconst_DigitalTS:		/* Keys - LnbNumber: Frequency: Polarization */
		case	ipgdbconst_CurrentDigitalTS:
			/* Here the request can be done for Frequency Alone */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName,Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE Frequency = %d ", TableName, ((HsvPgdatDigTSData*)Data)->Frequency);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						SQLITE_STEP(statement,retryCount,RetVal);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							sqlite3_reset(statement);\
							RetVal = sqlite3_finalize(statement);\
							--Preparecount;\
							if (MatchingEntryExist) \
							{\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE Frequency = %d ", TableName, ((HsvPgdatDigTSData*)Data)->Frequency);\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								++Preparecount;\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									SQLITE_STEP(statement,retryCount,RetVal);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										sqlite3_finalize(statement);\
										--Preparecount;\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
										if(RetVal == SQLITE_BUSY) 	{\
										RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
										}\
									}\
									else\
									{\
										RetVal = sqlite3_reset(statement);\
										RetVal = sqlite3_finalize(statement);\
										--Preparecount;\
										GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
										Index++;\
									}\
								}\
							}\
						}\
						else \
						{\
							RetVal = sqlite3_reset(statement);\
							RetVal = sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}\
				*Valid = TRUE;\
			}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			break;

		case	ipgdbconst_DigitalService:	/* Keys - Onid:	SvcId	*/
		case	ipgdbconst_CurrentDigitalService:
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE OriginalNetworkId = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					++Preparecount;\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						SQLITE_STEP(statement,retryCount,RetVal);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							sqlite3_finalize(statement);\
							--Preparecount;\
							if (MatchingEntryExist)\
							{\
								MatchingEntryExist = 0;\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
								/*PrintfNotice ("EuChannelLib: ANEESH: DbgPrint Query is %s \n",sqlQueryBuf);*/\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								++Preparecount;\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									SQLITE_STEP(statement,retryCount,RetVal);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										MatchingEntryExist = sqlite3_column_int (statement, 0);\
										sqlite3_finalize(statement);\
										--Preparecount;\
										if (MatchingEntryExist)\
										{\
											sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency < %d order by Frequency DESC limit 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency);\
											RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
											++Preparecount;\
											CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
											if (RetVal == SQLITE_OK) {\
												SQLITE_STEP(statement,retryCount,RetVal);\
												CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
												if(RetVal==SQLITE_ROW)\
												{\
													Index = sqlite3_column_int (statement, 0);\
													/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
													sqlite3_finalize(statement);\
													--Preparecount;\
													/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
													RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
													RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
													if(RetVal == SQLITE_BUSY) 	{\
													RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \	
													}\
												}\
												else\
												{\
													RetVal = sqlite3_finalize(statement);\
													--Preparecount;\
													sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId = %d AND Frequency > %d order by Frequency ASC limit 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId, ((HsvPgdatDigServiceData*)Data)->Frequency);\
													RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
													++Preparecount;\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													if (RetVal == SQLITE_OK) {\
														SQLITE_STEP(statement,retryCount,RetVal);\
														CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
														if(RetVal==SQLITE_ROW)\
														{\
															Index = sqlite3_column_int (statement, 0);\
															Index++;\
															/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
															sqlite3_finalize(statement);\
															--Preparecount;\
															/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
															RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
															CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
															sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
															RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
															CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
															RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
															CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
															if(RetVal == SQLITE_BUSY) 	{\
															RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
															}\
														}\
														else\
														{\
															sqlite3_finalize(statement);\
															--Preparecount;\
														}\
													}\
												}\
											}\										
										}\
										else\
										{\
											sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId < %d order by ServiceId DESC limit 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
											RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
											++Preparecount;\
											CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
											if (RetVal == SQLITE_OK) {\
												SQLITE_STEP(statement,retryCount,RetVal);\
												CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
												if(RetVal==SQLITE_ROW)\
												{\
													Index = sqlite3_column_int (statement, 0);\
													/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
													sqlite3_finalize(statement);\
													--Preparecount;\
													/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
													RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
													RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
													CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
													if(RetVal == SQLITE_BUSY) 	{\
													RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
													}\
												}\
												else\
												{\
													RetVal = sqlite3_finalize(statement);\
													--Preparecount;\
													sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE OriginalNetworkId = %d AND ServiceId > %d order by ServiceId ASC limit 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->OriginalNetworkId, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
													RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
													++Preparecount;\
													CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
													if (RetVal == SQLITE_OK) {\
														SQLITE_STEP(statement,retryCount,RetVal);\
														CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
														if(RetVal==SQLITE_ROW)\
														{\
															Index = sqlite3_column_int (statement, 0);\
															Index++;\
															/*PrintfNotice ("EuChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
															sqlite3_finalize(statement);\
															--Preparecount;\
															/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
															RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
															CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
															sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
															RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
															CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
															RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
															CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
															if(RetVal == SQLITE_BUSY) 	{\
															RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
															}\
														}\
														else\
														{\
															sqlite3_finalize(statement);\
															--Preparecount;\
														}\
													}\
												}\
											}\
										}\
									}\
									else\
									{\
										sqlite3_finalize(statement);\
										--Preparecount;\
									}\
								}\
							}\
						}\
						else\
						{\
							RetVal = sqlite3_reset(statement);\
							RetVal = sqlite3_finalize(statement);\
							--Preparecount;\
						}\
					}\
				}\
				else\
				{\
				}\
				*Valid = TRUE;\
			}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			*Valid = TRUE;
			break;

		case	ipgdbconst_Preset:			/* Key is - PresetNumber */
		case	ipgdbconst_CurrentPreset:
			/* Here only one key is present. So index will be the highest index of the table */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)){\
		GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
			if(Index>0) {\
				Index = 0;\
				sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE PresetNumber < %d order by PresetNumber DESC limit 1 ", TableName, ((HsvPgdatPresetData*)Data)->PresetNumber); \
				RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				++Preparecount;\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				if (RetVal == SQLITE_OK) {\
					SQLITE_STEP(statement,retryCount,RetVal);\
					if(RetVal==SQLITE_ROW)\
					{\
						Index = sqlite3_column_int (statement, 0);\
						PrintfNotice (" Index is %d \n",Index);\
						sqlite3_reset(statement);\
						sqlite3_finalize(statement);\
						--Preparecount;\
					}\
					else\
					{\
						sqlite3_reset(statement);\
						sqlite3_finalize(statement);\
						--Preparecount;\
						GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
					}\
				}\
				RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
				CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
				sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
				RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
				CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
				RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);	\
				if(RetVal == SQLITE_BUSY) 	{\
				RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); \
				}\
			}\
	}
		

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			*Valid = TRUE;


			break;

		default:
			 break;
		}
	}
	return Index;
}

void CHsvProgramData_mpgdb_Priv::PrepareInsertElementStringForSinglePrepare (int TableId,	char *statementbuf, char *tempString)
{
/* Based on the macro type fill in the string */
#define		Nat32	1
#define		Int32	2
#define		Nat16	3
#define		Int16	4
#define		Nat8	5
#define 	Nat64	6
#define		NONE	0
#define		A(x)	x

	/* Based on type, fill the values for insertion */
	switch (TableId)
	{
	case	ipgdbconst_FrequencyMapTable:
	case	ipgdbconst_CurrentFrequencyMapTable:
#define	FREQMAP_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_freqmapitems.h"
#else
#include "hsvpgdat_freqmapitems.h"
#endif
#undef	FREQMAP_ITEM
		break;

	case	ipgdbconst_SatInfo:
	case	ipgdbconst_CurrentSatInfo:
#define	SATINFO_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef	SATINFO_ITEM
		break;

	case	ipgdbconst_Analog:
	case	ipgdbconst_CurrentAnalog:
#define	ANALOG_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_analogitems.h"
#else
#include "hsvpgdat_analogitems.h"
#endif
#undef	ANALOG_ITEM
		break;

	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
#define	DIGTS_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_digtsitems.h"
#else
#include "hsvpgdat_digtsitems.h"
#endif
#undef	DIGTS_ITEM
		break;

	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_digsrvcitems.h"
#else
#include "hsvpgdat_digsrvcitems.h"
#endif
#undef	DIGSRVC_ITEM
		break;

	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
#define	PRESET_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_presetitems.h"
#else
#include "hsvpgdat_presetitems.h"
#endif
#undef	PRESET_ITEM
		break;

	default:
		break;
	}

	sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "?");
	strcat (statementbuf, tempString);

#undef	Nat64
#undef	Nat32
#undef	Int32
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A

}

sqlite3_stmt* CHsvProgramData_mpgdb_Priv::PrepareSqlInsertStatement (int InsertTableId)
{
	Nat32	RetVal = err_Ok;
	char 	tempString[SQL_TABLE_SMALL_QUERY_LENGTH];
	sqlite3_stmt	*statement = NULL;
	
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
			sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, sqldbTableInsertStatementBuf, "INSERT INTO %s ", TableName);\
			if ((strcmp(TableName, "PresetTable")==0) || (strcmp(TableName, "TempPresetTable")==0)) \
			{ \
				sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, tempString, "(DbIndex,Frequency,PresetNumber,AnalogTablePreset,Type,OriginalNetworkId,Tsid,ServiceId,StreamPriority,FavoriteNumber,EmmChannel,dummy) " );\
				strcat (sqldbTableInsertStatementBuf, tempString);\
			} \
			sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, tempString, "VALUES ( ?, ");\
			strcat (sqldbTableInsertStatementBuf, tempString);\
			PrepareInsertElementStringForSinglePrepare(InsertTableId,sqldbTableInsertStatementBuf,tempString);\
			sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, tempString, ");");\
			strcat (sqldbTableInsertStatementBuf, tempString);\
		}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

	RetVal = sqlite3_prepare_v2 (SqliteDbHandle, sqldbTableInsertStatementBuf, SQL_TABLE_MEDIUM_QUERY_LENGTH, &statement, NULL);
	++Preparecount;
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	if (RetVal != SQLITE_OK)
	{
		statement = NULL;
	}

	return statement;
}

void CHsvProgramData_mpgdb_Priv::FillInsertStatement (sqlite3_stmt *InsertHandle, int TableId, Address Data)
{
	int			count = 2;
	//char		tempBuff[66];
	Nat16		tempBuff[33];
	int			tempVar;

/* Based on the macro type fill in the string */
#define		Nat32	1
#define		Int32	2
#define		Nat16	3
#define		Int16	4
#define		Nat8	5
#define		Nat64	6
#define		NONE	0
#define		A(x)	x

	/* Based on type, fill the values for insertion */
	switch (TableId)
	{
	case	ipgdbconst_FrequencyMapTable:
	case	ipgdbconst_CurrentFrequencyMapTable:
#define	FREQMAP_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigFreqMapData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_freqmapitems.h"
#else
#include "hsvpgdat_freqmapitems.h"
#endif
#undef	FREQMAP_ITEM
		break;

	case	ipgdbconst_Analog:
	case	ipgdbconst_CurrentAnalog:
#define	ANALOG_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatAnalogData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_analogitems.h"
#else
#include "hsvpgdat_analogitems.h"
#endif
#undef	ANALOG_ITEM
		break;

	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
#define	DIGTS_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigTSData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_digtsitems.h"
#else
#include "hsvpgdat_digtsitems.h"
#endif
#undef	DIGTS_ITEM
		break;

	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigServiceData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_digsrvcitems.h"
#else
#include "hsvpgdat_digsrvcitems.h"
#endif
#undef	DIGSRVC_ITEM
		break;

	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
#define	PRESET_ITEM(element, type, bitdec, bitdef, deflt )	\
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatPresetData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_presetitems.h"
#else
#include "hsvpgdat_presetitems.h"
#endif
#undef	PRESET_ITEM
		break;

	default:
		break;
	}

#undef	Nat64
#undef	Nat32
#undef	Int32
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A

	sqlite3_bind_int(InsertHandle,count,0);
}

int CHsvProgramData_mpgdb_Priv::InsertEntryToTableWithSinglePrepareIndex(int majorTableId, int InsertTableId, Address Data, int Index)
{
	Bool	Valid = FALSE;
	Nat32	RetVal = err_Ok;
	Nat8	count = 0;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;
	int retryCount = 0;

	if (mCurrentTable == ipgdbconst_Satellite)
	{
		handle = SqliteHandleSatMaps;
		num_tbl = MAX_SAT_PGDB_TABLES;
	}
	else
	{
		handle = SqliteHandleMaps;
		num_tbl = MAX_PGDB_TABLES;
		Valid = TRUE;
	}
	
	if( Valid == TRUE)
	{
		for (count = 0; count < num_tbl; count++)
		{
			if (InsertTableId == handle[count].SubTableId)
			{
				if (handle[count].InsertHandle == NULL)
				{
					//PrintfNotice (" NULL Handle Found for TableIndex %d \n", count);
					handle[count].InsertHandle = PrepareSqlInsertStatement (InsertTableId);
				}
				break;
			}
		}

		if ((count >= num_tbl) || (handle[count].InsertHandle == NULL))
		{
			RetVal = SQLITE_ERROR;
		}
		else
		{

			/* Insert the entry now */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) &&  (TableId == InsertTableId)) {\
				sqlite3_bind_int(handle[count].InsertHandle,1,Index);\
				FillInsertStatement(handle[count].InsertHandle,InsertTableId,Data);\
				SQLITE_STEP(handle[count].InsertHandle,retryCount,RetVal);\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				RetVal = sqlite3_reset (handle[count].InsertHandle);\
			}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM


		}
	}

	return RetVal;

}


int CHsvProgramData_mpgdb_Priv::InsertEntryToTableWithSinglePrepare (int majorTableId, int InsertTableId, Address Data)
{
	Bool	Valid = FALSE;
	Nat32	RetVal = err_Ok;
	int		Index;
	Nat8	count = 0;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;
	int retryCount = 0;

	/*Identify the Index which should be inserted now */
	Index = GetIndexValForInsertion (majorTableId, InsertTableId, Data, &Valid);
	//PrintfNotice("S2ChannelLib: %s %d Valid %d and Index %d \n", __FUNCTION__, __LINE__, Valid, Index);

	if (mCurrentTable == ipgdbconst_Satellite)
	{
		handle = SqliteHandleSatMaps;
		num_tbl = MAX_SAT_PGDB_TABLES;
	}
	else
	{
		handle = SqliteHandleMaps;
		num_tbl = MAX_PGDB_TABLES;
	}
	
	if( Valid == TRUE)
	{
		for (count = 0; count < num_tbl; count++)
		{
			if (InsertTableId == handle[count].SubTableId)
			{
				if (handle[count].InsertHandle == NULL)
				{
					//PrintfNotice (" NULL Handle Found for TableIndex %d \n", count);
					handle[count].InsertHandle = PrepareSqlInsertStatement (InsertTableId);
				}
				break;
			}
		}

		if ((count >= num_tbl) || (handle[count].InsertHandle == NULL))
		{
			RetVal = SQLITE_ERROR;
		}
		else
		{
			RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

			/* Insert the entry now */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) &&  (TableId == InsertTableId)) {\
				sqlite3_bind_int(handle[count].InsertHandle,1,Index);\
				FillInsertStatement(handle[count].InsertHandle,InsertTableId,Data);\
				SQLITE_STEP(handle[count].InsertHandle,retryCount,RetVal);\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				RetVal = sqlite3_reset (handle[count].InsertHandle);\
			}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

			RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
			if(RetVal == SQLITE_BUSY) {
 				RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount); 
			}

		}
	}

	return RetVal;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_Add        ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
#ifdef	ENABLE_TIME_TRACE
	Nat64	t1, t2;
#endif

	SEM_TAKE(mProgramMapSem);

	
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		//PrintfNotice ("EuChannelLib: DbgPrint : Adding the entry for Maj: %d Min : %d \n", GETMAJORTABLEID(tableid), SubTableId);
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			//if (SQLITE_OK != InsertEntryToTable (SubTableId, channeldata))
			if (SQLITE_OK != InsertEntryToTableWithSinglePrepare (GETMAJORTABLEID(tableid), SubTableId, channeldata))
			{
				RetVal = FALSE;
			}
			else
			{
			}
		}
		else
		{
			RetVal = srtdb2_Insert(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata), channeldata);
		}

		break;
	default:
		//PrintfNotice ("EuChannelLib: DbgPrint.... SERIOUS WRONG TABLE..\n");
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	if (TRUE==Notification_enable)
		{	
		if(SubTableId==ipgdbconst_Preset)
			{
			HsvPgdatPresetData	*preset;
			preset = (HsvPgdatPresetData*) channeldata;
			insN->OnEvent(IHsvInstallationNotify_EventPresetAdded,(int)preset->PresetNumber);
			}
		}
	return RetVal;
}

void CHsvProgramData_mpgdb_Priv::ipgdb_SelectActiveChannelDatabase(int ActiveDb)
{
	mActiveDatabase = ActiveDb;
}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_AddInIndex (int tableid, int index, Address channeldata)
{

	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Cable:
	case	ipgdbconst_TempCable:
	case	ipgdbconst_Antenna:
	case	ipgdbconst_TempAntenna:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_OK != InsertEntryToTableWithSinglePrepareIndex (GETMAJORTABLEID(tableid), SubTableId, channeldata,index))
			{
				RetVal = FALSE;
			}
			else
			{
			}
		}
		else
		{
			RetVal = srtdb2_Insert(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata), channeldata);
		}
		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	if (TRUE==Notification_enable)
	{	
		if(SubTableId==ipgdbconst_Preset)
		{
			HsvPgdatPresetData	*preset;
			preset = (HsvPgdatPresetData*) channeldata;
			insN->OnEvent(IHsvInstallationNotify_EventPresetAdded,(int)preset->PresetNumber);
		}
	}
	return RetVal;
}

void CHsvProgramData_mpgdb_Priv::ipgdb_BeginSqliteTransaction(void)
{
	int RetVal = 0;
	
	/*  DBOPTIMIZATION - Doing this begin commit explicitly only */
	RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
}

void CHsvProgramData_mpgdb_Priv::ipgdb_CommitSqliteTransaction(void)
{
	int RetVal = 0, retryCount = 0;
	
	RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
	if(RetVal == SQLITE_BUSY) 
	{
		RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount)
	}
}


#ifdef	__OPTIMIZATION_CHECKS_ON__

Bool CHsvProgramData_mpgdb_Priv::ipgdb_CheckDuplicateTpid (int TpId)
{

}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_GetSortDetailsFromDigSrvTable (int *Index, Address Data)
{

}

Bool CHsvProgramData_mpgdb_Priv::ipgdb_UpdatePresetInDigSrvTable (int Index, int PresetNumber)
{

}

#endif



