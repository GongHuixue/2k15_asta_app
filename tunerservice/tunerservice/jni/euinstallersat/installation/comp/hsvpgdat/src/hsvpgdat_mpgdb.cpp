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
#include "hsvpgdat_mpgdb.h"

#include "semaphore.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "_hsvpgdat_mpgdb.h"


TRACESYMBOL(m, "euinstallersat/hsvpgdat/hsvpgdat_mpgdb")

int CHsvSatProgramData_mpgdb_Priv::s__mCurrentTable = ipgdbconst_Satellite;


SqliteHandleMapEntry CHsvSatProgramData_mpgdb_Priv::s__SqliteHandleMaps[MAX_PGDB_TABLES] =
{
	{ipgdbconst_FrequencyMapTable,		NULL,	NULL	 },
	{ipgdbconst_DigitalTS,				NULL,	NULL	 },
	{ipgdbconst_DigitalService,			NULL,	NULL	 },
	{ipgdbconst_Analog,					NULL,	NULL	 },
	{ipgdbconst_Preset,					NULL,	NULL	 },
	{ipgdbconst_CurrentFrequencyMapTable,	NULL,	NULL },
	{ipgdbconst_CurrentDigitalTS,		NULL,	NULL	 },
	{ipgdbconst_CurrentDigitalService,	NULL,	NULL	 },
	{ipgdbconst_CurrentAnalog,			NULL,	NULL	 },
	{ipgdbconst_CurrentPreset,			NULL,	NULL	 },
	{IHsvProgramDatabaseConstants_HomingService,NULL,NULL},
	{IHsvProgramDatabaseConstants_InteractiveService,NULL,NULL}
};


SqliteHandleMapEntry CHsvSatProgramData_mpgdb_Priv::s__SqliteHandleSatMaps[MAX_SAT_PGDB_TABLES] =
{
	{ipgdbconst_SatInfo,				NULL,	NULL},
	{ipgdbconst_DigitalTS,				NULL,	NULL},
	{ipgdbconst_DigitalService,			NULL,	NULL},
	{ipgdbconst_Preset,					NULL,	NULL},
	{ipgdbconst_CurrentSatInfo,			NULL,	NULL},
	{ipgdbconst_CurrentDigitalTS,		NULL,	NULL},
	{ipgdbconst_CurrentDigitalService,	NULL,	NULL},
	{ipgdbconst_CurrentPreset,			NULL,	NULL},
	{IHsvProgramDatabaseConstants_HomingService,NULL,NULL},
	{IHsvProgramDatabaseConstants_InteractiveService,NULL,NULL}
};

Srtdbconfig	CHsvSatProgramData_mpgdb_Priv::s__mProgramDbMap[NUM_PGDB_SUBTABLES] = { 	
													{ipgdbconst_Preset, 		0/*srtdbids_PresetTable*/, 	5000, 	sizeof(HsvPgdatPresetData) ,0},
													{ipgdbconst_DigitalService,	0/*srtdbids_DigSrvcTable*/, 	5000, 	sizeof(HsvPgdatDigServiceData),0 },
													{ipgdbconst_SatInfo, 		0/*srtdbids_SatInfoTable*/, 	4, 		sizeof(HsvPgdatDigSatInfoData),0 },
													{ipgdbconst_DigitalTS, 		0/*srtdbids_DigTSTable*/, 	500, 	sizeof(HsvPgdatDigTSData),0 },
													{IHsvProgramDatabaseConstants_HomingService,0,20,sizeof(HsvPgdatHomServiceData), 0},
													{IHsvProgramDatabaseConstants_InteractiveService,0,20,sizeof(HsvPgdatIntrServiceData), 0}};

int	CHsvSatProgramData_mpgdb_Priv::s__mActiveDatabase = ipgdb_TempDatabase;


/* Static variables  */
Bool CHsvSatProgramData_mpgdb_Priv::s__mAutoCommitEnabled = FALSE;

Bool CHsvSatProgramData_mpgdb_Priv::s__mFlashOperationPossible = FALSE;

Bool CHsvSatProgramData_mpgdb_Priv::s__mDirtyBit = FALSE;


char CHsvSatProgramData_mpgdb_Priv::s__mDirectory[MAX_DIRECTORY_NAME_SIZE];

void *CHsvSatProgramData_mpgdb_Priv::s__mProgramMapSem = NULL;

char *CHsvSatProgramData_mpgdb_Priv::s__SemKey = "/hsvpgdat_mflash";
  /* TODO: how to make sure that key is unique? */
sqlite3 *CHsvSatProgramData_mpgdb_Priv::s__SqliteDbHandle = NULL;

sqlite3 *CHsvSatProgramData_mpgdb_Priv::s__SatDbHandle = NULL;

sqlite3 *CHsvSatProgramData_mpgdb_Priv::s__CabDbHandle = NULL;

sqlite3 *CHsvSatProgramData_mpgdb_Priv::s__TerDbHandle = NULL;

char CHsvSatProgramData_mpgdb_Priv::s__sqldbTableLargeStatementBuf[SQL_TABLE_LARGE_QUERY_LENGTH];
	/* This buffer is used mainly in create table query */
char CHsvSatProgramData_mpgdb_Priv::s__sqldbTableInsertStatementBuf[SQL_TABLE_MEDIUM_QUERY_LENGTH];



HsvPgdatDigSatInfoData CHsvSatProgramData_mpgdb_Priv::s__DefaultSatInfoValues;

HsvPgdatPresetData CHsvSatProgramData_mpgdb_Priv::s__DefaultPresetValues;

HsvPgdatAnalogData CHsvSatProgramData_mpgdb_Priv::s__DefaultAnalogValues;

HsvPgdatDigServiceData CHsvSatProgramData_mpgdb_Priv::s__DefaultDigSvcValues;

HsvPgdatDigFreqMapData CHsvSatProgramData_mpgdb_Priv::s__DefaultFrqMapValues;

HsvPgdatDigTSData CHsvSatProgramData_mpgdb_Priv::s__DefaultDigTSValues;

HsvPgdatHomServiceData CHsvSatProgramData_mpgdb_Priv::s__DefaultHomingSvcValues;
HsvPgdatIntrServiceData CHsvSatProgramData_mpgdb_Priv::s__DefaultInteractiveSvcValues;

HSVCOMPAREKEY(presettableconf, Primary, HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(presettableconf, Secondary, HsvPgdatPresetData, Tpid)
HSVCOMPAREKEY(presettableconf, Teritiary, HsvPgdatPresetData, Frequency)
HSVCOMPAREKEY(presettableconf, Quaternary, HsvPgdatPresetData, Frequency)

HSVCOMPAREKEY(digsrvctableconf, Primary, HsvPgdatDigServiceData, Tpid)
HSVCOMPAREKEY(digsrvctableconf, Secondary, HsvPgdatDigServiceData, ServiceId)
HSVCOMPAREKEY(digsrvctableconf, Teritiary, HsvPgdatDigServiceData, ServiceId)                         
HSVCOMPAREKEY(digsrvctableconf, Quaternary, HsvPgdatDigServiceData, ServiceId)

HSVCOMPAREKEY(satinfotableconf, Primary, HsvPgdatDigSatInfoData, LnbNumber)
HSVCOMPAREKEY(satinfotableconf, Secondary, HsvPgdatDigSatInfoData, LnbNumber)
HSVCOMPAREKEY(satinfotableconf, Teritiary, HsvPgdatDigSatInfoData, LnbNumber)
HSVCOMPAREKEY(satinfotableconf, Quaternary, HsvPgdatDigSatInfoData, LnbNumber)

HSVCOMPAREKEY(digtstableconf, Primary,		HsvPgdatDigTSData, LnbNumber)
HSVCOMPAREKEY(digtstableconf, Secondary,	HsvPgdatDigTSData, Frequency)
HSVCOMPAREKEY(digtstableconf, Teritiary,	HsvPgdatDigTSData, Polarization)
HSVCOMPAREKEY(digtstableconf, Quaternary,	HsvPgdatDigTSData, Polarization)

HSVCOMPAREKEY(homingsvctableconf, Primary,		HsvPgdatHomServiceData, HomingServiceType)
HSVCOMPAREKEY(homingsvctableconf, Secondary,	HsvPgdatHomServiceData, OriginalNetworkId)
HSVCOMPAREKEY(homingsvctableconf, Teritiary,	HsvPgdatHomServiceData, ServiceId)
HSVCOMPAREKEY(homingsvctableconf, Quaternary,	HsvPgdatHomServiceData, ServiceId)

HSVCOMPAREKEY(interactivesvctableconf, Primary,		HsvPgdatIntrServiceData, FreesatServiceIdentifier)
HSVCOMPAREKEY(interactivesvctableconf, Secondary,	HsvPgdatIntrServiceData, FreesatGroupID)
HSVCOMPAREKEY(interactivesvctableconf, Teritiary,	HsvPgdatIntrServiceData, FreesatGroupID)
HSVCOMPAREKEY(interactivesvctableconf, Quaternary,	HsvPgdatIntrServiceData, FreesatGroupID)

HSVCOMPAREKEY(temppresettableconf, Primary, HsvPgdatPresetData, PresetNumber)
HSVCOMPAREKEY(temppresettableconf, Secondary, HsvPgdatPresetData, Tpid)
HSVCOMPAREKEY(temppresettableconf, Teritiary, HsvPgdatPresetData, Frequency)
HSVCOMPAREKEY(temppresettableconf, Quaternary, HsvPgdatPresetData, Frequency)

HSVCOMPAREKEY(tempdigsrvctableconf, Primary, HsvPgdatDigServiceData, Tpid)
HSVCOMPAREKEY(tempdigsrvctableconf, Secondary, HsvPgdatDigServiceData, ServiceId)
HSVCOMPAREKEY(tempdigsrvctableconf, Teritiary, HsvPgdatDigServiceData, ServiceId)                         
HSVCOMPAREKEY(tempdigsrvctableconf, Quaternary, HsvPgdatDigServiceData, ServiceId)

HSVCOMPAREKEY(tempsatinfotableconf, Primary, HsvPgdatDigSatInfoData, LnbNumber)
HSVCOMPAREKEY(tempsatinfotableconf, Secondary, HsvPgdatDigSatInfoData, LnbNumber)
HSVCOMPAREKEY(tempsatinfotableconf, Teritiary, HsvPgdatDigSatInfoData, LnbNumber)
HSVCOMPAREKEY(tempsatinfotableconf, Quaternary, HsvPgdatDigSatInfoData, LnbNumber)

HSVCOMPAREKEY(tempdigtstableconf, Primary,		HsvPgdatDigTSData, LnbNumber)
HSVCOMPAREKEY(tempdigtstableconf, Secondary,	HsvPgdatDigTSData, Frequency)
HSVCOMPAREKEY(tempdigtstableconf, Teritiary,	HsvPgdatDigTSData, Polarization)
HSVCOMPAREKEY(tempdigtstableconf, Quaternary,	HsvPgdatDigTSData, Polarization)



/* Internal Functions */
















































int CHsvSatProgramData_mpgdb_Priv::mGetDBTableIds(int PgDbTid)
{
    int ret = -1;
    int i;
    
    for(i=0; i<NUM_PGDB_SUBTABLES; i++)
    {
        if(PgDbTid == mProgramDbMap[i].DbTableId)
        {
            ret = mProgramDbMap[i].SrtDbTableId;
            break;
        }
    }
    return ret;
}

inline int CHsvSatProgramData_mpgdb_Priv::mGetPrimaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
		retval = ((HsvPgdatPresetData*)(data))->PresetNumber;
		break;
	case ipgdbconst_SatInfo:	
		retval = ((HsvPgdatDigSatInfoData*)(data))->LnbNumber;
		break;
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
		retval = ((HsvPgdatDigServiceData*)(data))-> Tpid;
		break;
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
		retval = ((HsvPgdatDigTSData*)(data))->LnbNumber;
		break;
	case IHsvProgramDatabaseConstants_HomingService:
	case IHsvProgramDatabaseConstants_CurrentHomingService:
		retval = ((HsvPgdatHomServiceData *)(data))->HomingServiceType;
		break;
	case IHsvProgramDatabaseConstants_InteractiveService:
	case IHsvProgramDatabaseConstants_CurrentInteractiveService:
		retval = ((HsvPgdatIntrServiceData *)(data))->FreesatServiceIdentifier;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

inline int CHsvSatProgramData_mpgdb_Priv::mGetSecondaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_SatInfo:	
		break;
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
		retval = ((HsvPgdatDigServiceData*)(data))->ServiceId;
		break;
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
		retval = ((HsvPgdatDigTSData*)(data))->Frequency;
		break;
	case IHsvProgramDatabaseConstants_HomingService:
	case IHsvProgramDatabaseConstants_CurrentHomingService:
		retval = ((HsvPgdatHomServiceData *)(data))->OriginalNetworkId;
		break;
	case IHsvProgramDatabaseConstants_InteractiveService:
	case IHsvProgramDatabaseConstants_CurrentInteractiveService:
		retval = ((HsvPgdatIntrServiceData *)(data))->FreesatGroupID;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

inline int CHsvSatProgramData_mpgdb_Priv::mGetTertiaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_SatInfo:	
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
	case IHsvProgramDatabaseConstants_InteractiveService:
	case IHsvProgramDatabaseConstants_CurrentInteractiveService:
		break;
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
		retval = ((HsvPgdatDigTSData*)(data))->Polarization;
		break;
	case IHsvProgramDatabaseConstants_HomingService:
	case IHsvProgramDatabaseConstants_CurrentHomingService:
		retval = ((HsvPgdatHomServiceData *)(data))->ServiceId;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

inline int CHsvSatProgramData_mpgdb_Priv::mGetQuaternaryKey(int tableid, Address data)
{
	int retval = 0;
	switch(tableid)
	{
	case ipgdbconst_Preset:
	case ipgdbconst_SatInfo:	
	case ipgdbconst_DigitalTS:
	case ipgdbconst_CurrentDigitalTS:
	case ipgdbconst_DigitalService:
	case ipgdbconst_CurrentDigitalService:
	case IHsvProgramDatabaseConstants_HomingService:
	case IHsvProgramDatabaseConstants_CurrentHomingService:
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return retval;
}

void CHsvSatProgramData_mpgdb_Priv::mInitialize (void)
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

#define	HOMSRVC_ITEM(item, type, bit, siz, def)	   DefaultHomingSvcValues.item siz = def;
#ifndef __cplusplus
#include "data/hsvpgdat_homsrvcitems.h"
#else
#include "hsvpgdat_homsrvcitems.h"
#endif
#undef	HOMSRVC_ITEM

#define	INTSRVC_ITEM(item, type, bit, siz, def)	   DefaultInteractiveSvcValues.item siz = def;
#ifndef __cplusplus
#include "data/hsvpgdat_intrsrvcitems.h"
#else
#include "hsvpgdat_intrsrvcitems.h"
#endif
#undef	INTSRVC_ITEM

#undef NO
#undef NAME
#undef NONE
#undef A
    
	/* Starting the flash updat thread, and creating the semaphore to protect channel map */
    mProgramMapSem = rtk_SemCreate( SemKey );

	mProgramDbMap[0].SrtDbTableId = srtdbids_PresetTable;
	mProgramDbMap[1].SrtDbTableId = srtdbids_DigSrvcTable;
	mProgramDbMap[2].SrtDbTableId = srtdbids_SatInfoTable;
	mProgramDbMap[3].SrtDbTableId = srtdbids_DigTSTable;
	mProgramDbMap[4].SrtDbTableId = srtdbids_HomingSvcTable;
	mProgramDbMap[5].SrtDbTableId = srtdbids_InteractiveSvcTable;
    mAutoCommitEnabled = FALSE;

	for(i=0; i<NUM_PGDB_SUBTABLES; i++)
	{
		srtdb2_Init(mProgramDbMap[i].SrtDbTableId);
	}

	
	mProgramDbMap[0].TempSrtDbTableId = srtdbids_TempPresetTable;
	mProgramDbMap[1].TempSrtDbTableId = srtdbids_TempDigSrvcTable;
	mProgramDbMap[2].TempSrtDbTableId = srtdbids_TempSatInfoTable;
	mProgramDbMap[3].TempSrtDbTableId = srtdbids_TempDigTSTable;

	for(i=0; i<NUM_PGDB_SUBTABLES; i++)
	{
		srtdb2_Init(mProgramDbMap[i].TempSrtDbTableId);
	}

	
	set_sqlite_configuration ();
	/* Initializing the SQLite. Table creation happens at a later point of time */
	RetVal = sqlite3_initialize ();
}

char* CHsvSatProgramData_mpgdb_Priv::mGetTableName (int ReqTableId)	
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

void CHsvSatProgramData_mpgdb_Priv::PrepareCreateElementString (int TableId,	char *sqldbTableExectureStatement, char *tempString)
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

int CHsvSatProgramData_mpgdb_Priv::CreateAllDatabaseTables (sqlite3 *database, int medium)
{
	Nat32	RetVal = 0;
	char 	tempString[SQL_TEMP_STRING_LENGTH];

	/* This statement is a longer one. Use the long buffer
		Check the table info. Create tables for each of the entries in database */
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


int CHsvSatProgramData_mpgdb_Priv::CreateDatabases(void)
{
	int RetVal = 0;
	char db_FileName[100] = {0};
	
	strcpy(db_FileName, DATABASE_DIRECTORY_PATH);
	strcat(db_FileName, TER_DB_FILENAME);	
	RetVal = sqlite3_open (db_FileName, &TerDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;
		return RetVal;
	}
	else
	{
		CreateAllDatabaseTables(TerDbHandle, ipgdbconst_Antenna);
	}
	
	strcpy(db_FileName, DATABASE_DIRECTORY_PATH);
	strcat(db_FileName, CAB_DB_FILENAME);	
	RetVal = sqlite3_open (db_FileName, &CabDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;
		return RetVal;
	}
	else
	{
		CreateAllDatabaseTables(CabDbHandle, ipgdbconst_Cable);
	}
	
	strcpy(db_FileName, DATABASE_DIRECTORY_PATH);
	strcat(db_FileName, CAB_DB_FILENAME);	
	RetVal = sqlite3_open (db_FileName, &SatDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;
		return RetVal;
	}
	else
	{
		CreateAllDatabaseTables(SatDbHandle, ipgdbconst_Satellite);
	}
	
	return TRUE;
}

int CHsvSatProgramData_mpgdb_Priv::OpenSqliteDatabase (void)
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
		default:
			return RetVal;
	}
	
	fp = fopen (fileName,"r");
	if (fp)
	{
		fclose(fp);
	}
	else
	{
		return RetVal;
	}

	RetVal = sqlite3_open (fileName, &SqliteDbHandle);
	if (IS_SQLITE_ERROR(RetVal))
	{
		ASSERT("EuChannelLib: Open SQLITE memory db failed \n");
	}
	else
	{
	}
	/* This API returns TRUE or FALSE only */
	RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;

	return RetVal;
}


void CHsvSatProgramData_mpgdb_Priv::ipgdbpow_Init (void)
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

void CHsvSatProgramData_mpgdb_Priv::ipgdb_BeginSqliteTransaction(void)
{	
	int RetVal = 0;
	
	/*  DBOPTIMIZATION - Doing this begin commit explicitly only */
	RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_CommitSqliteTransaction(void)
{
	int RetVal = 0, retryCount = 0;
	
	RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
	if(RetVal == SQLITE_BUSY) 
	{
		RETRY_COMMIT(SqliteDbHandle,RetVal,retryCount)
	}
}


void CHsvSatProgramData_mpgdb_Priv::ipgdbpow_TurnOn (void)
{
	/* TODO */
}

void CHsvSatProgramData_mpgdb_Priv::ResetSqliteStatementHandles (void)
{
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
			err_code = sqlite3_reset (handle[count].InsertHandle);
			err_code = sqlite3_finalize (handle[count].InsertHandle);
			handle[count].InsertHandle = NULL;
		}

		if (handle[count].UpdateHandle)
		{
			err_code = sqlite3_reset (handle[count].UpdateHandle);
			err_code = sqlite3_finalize (handle[count].UpdateHandle);
			handle[count].UpdateHandle = NULL;
		}
	}
}

int CHsvSatProgramData_mpgdb_Priv::CloseSqliteDatabase (void)
{
	int		RetVal = FALSE;

	RetVal = sqlite3_close (SqliteDbHandle);
	
	if (IS_SQLITE_ERROR(RetVal))
	{
		CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);
		ASSERT("EuChannelLib: Close SQLITE memory db failed \n");
	}

	/* This API returns TRUE or FALSE only */
	RetVal = (RetVal == SQLITE_OK) ? TRUE : FALSE;


	return RetVal;
}

void CHsvSatProgramData_mpgdb_Priv::ipgdbpow_TurnOff (void)
{
	int	RetVal = 0;
	/* TODO: Reset Statements */
	ResetSqliteStatementHandles ();
	RetVal = CloseSqliteDatabase ();
}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_SelectTable       ( int tableid )
{
	Bool	RetVal = FALSE;

	SEM_TAKE(mProgramMapSem);
	
	if (tableid != mCurrentTable)
	{
		switch (mCurrentTable)
		{
		case	ipgdbconst_Satellite:
		case	ipgdbconst_TempSatellite:
			if (SatDbHandle)
			{
				RetVal = sqlite3_close (SatDbHandle);
				if (IS_SQLITE_ERROR(RetVal))
				{
					CHECK_SQLITE_ERR(TerDbHandle, RetVal);
					ASSERT("EuChannelLib: Close SQLITE memory db failed \n");
				}
			}
			break;
		default:
			break;
		}


		/* Set Current table */
		switch (tableid)
		{
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
	else if(SqliteDbHandle == NULL)
	{
		/* Set Current table */
		switch (tableid)
		{
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

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_LoadTable        ( int tableid )
{
	mCurrentTable = tableid;

	return TRUE;
}

/* SQLITE based general internal functions */
void CHsvSatProgramData_mpgdb_Priv::set_sqlite_configuration(void)
{
	int err;
	static void *pScatchBuf = NULL;
	
	pScatchBuf = malloc(4 * 10 * 1024);
	if(pScatchBuf==NULL)
	{
		exit(0);
	}
	err = sqlite3_config(SQLITE_CONFIG_SCRATCH,pScatchBuf, 10*1024, 4);
	CHECK_CONFIG_ERR(err);
	err = sqlite3_config(SQLITE_CONFIG_LOOKASIDE, 100, 500);
	CHECK_CONFIG_ERR(err);
	err = sqlite3_config(SQLITE_CONFIG_SERIALIZED);
	CHECK_CONFIG_ERR(err);
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_MasterEnableEvents(Bool enable)
{
	TraceDebug (m, "%s %d Notification_enable %d\n", __FUNCTION__, __LINE__, enable);
    Notification_enable=enable;
    sync_MasterEnableEvents(enable);
}

int CHsvSatProgramData_mpgdb_Priv::ipgdb_GetCurrentTable   ( void )
{
	return mCurrentTable;
}

int CHsvSatProgramData_mpgdb_Priv::ClearTable (int SubTableId)
{
	int	RetVal = -1;
	char	sqlDeleteBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

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
	if(RetVal == SQLITE_BUSY) 
		RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	

	return RetVal;
}

int CHsvSatProgramData_mpgdb_Priv::ClearAllTables (int tableid)
{
	int	RetVal = -1;
	char	sqlDeleteBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);


	/* Clear all the subtables of the MajorTable */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
	if (MajorTableId == tableid) {\
		sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlDeleteBuf, "DELETE FROM %s ", TableName);\
		RetVal = sqlite3_exec (SqliteDbHandle, sqlDeleteBuf, NULL, NULL, NULL);\
		RetVal = (RetVal == SQLITE_DONE) ? err_Ok: err_FileError;\
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
	}
#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

	RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);

	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
	if(RetVal == SQLITE_BUSY) 
		RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	

	return RetVal;
}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_ClearTable        ( int tableid )
{
	Bool	RetVal = FALSE;
	int		subtableid, i;

	SEM_TAKE(mProgramMapSem);
	
	subtableid = GETSUBTABLEID(tableid);

	switch (GETMAJORTABLEID(tableid))
	{
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
			for(i=0; i<NUM_PGDB_SUBTABLES; i++)
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

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_IsSupported( int tableid )
{
    Bool retval = FALSE;
    switch(tableid)
    {
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

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_CommitTable      ( int tableid )
{
	int	RetVal = 0;

	SEM_TAKE(mProgramMapSem);
	ResetSqliteStatementHandles ();
	//RetVal = CloseSqliteDatabase ();
	SEM_GIVE(mProgramMapSem);
	return TRUE;
}

int CHsvSatProgramData_mpgdb_Priv::ipgdb_GetNoRecords(int tableid )
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


int CHsvSatProgramData_mpgdb_Priv::ExtractNodeDataFromDatabse (char *QueryBuf, int QueryLen, int TableId, Address Data)
{
	int			RetVal = FALSE, Ret;
	int			index = 0;
	int			temp, NumColumns = 0;
	Bool		proceed = TRUE;
	void		*returnString = NULL;
	sqlite3_stmt	*statement = NULL;

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
	
	RetVal = sqlite3_prepare_v2 (SqliteDbHandle, QueryBuf, QueryLen, &statement, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	/* Only single step is required. And now parse each columns */
	RetVal = sqlite3_step (statement);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	NumColumns = (RetVal == SQLITE_ROW) ? sqlite3_column_count(statement) : 0;
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
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt,HsvPgdatDigSatInfoData,statement,temp,returnString)
#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef	SATINFO_ITEM
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

		case	IHsvProgramDatabaseConstants_HomingService:
#define	HOMSRVC_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt ,HsvPgdatHomServiceData,statement,temp,returnString)

#ifndef __cplusplus
#include "data/hsvpgdat_homsrvcitems.h"
#else
#include "hsvpgdat_homsrvcitems.h"
#endif

#undef	HOMSRVC_ITEM
			RetVal = TRUE;
			break;
		case	IHsvProgramDatabaseConstants_InteractiveService:
#define	INTSRVC_ITEM(element, type, bitdec, bitdef, deflt)	\
	EXTRACT_ELEMENTS_FROM_TABLE(element, type, bitdec, bitdef,deflt ,HsvPgdatIntrServiceData,statement,temp,returnString)

#ifndef __cplusplus
#include "data/hsvpgdat_intrsrvcitems.h"
#else
#include "hsvpgdat_intrsrvcitems.h"
#endif

#undef	INTSRVC_ITEM
			RetVal = TRUE;
			break;
		default:
			RetVal = FALSE;
			break;
		}
	}
	else
	{
		RetVal = FALSE;
	}

	/* Now reset and finalize the statements */
	Ret = sqlite3_reset (statement);
	CHECK_SQLITE_ERR(SqliteDbHandle,Ret);
	Ret = sqlite3_finalize (statement);
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


int CHsvSatProgramData_mpgdb_Priv::GetDataFromTableByKey (int MajorTableId, int TableId, Address Data)
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
				"SELECT * FROM %s WHERE LnbNumber = %d ", mGetTableName(TableId), ((HsvPgdatDigSatInfoData*)Data)->LnbNumber);
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
				"SELECT * FROM %s WHERE Tpid = %d AND ServiceId = %d", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->Tpid, ((HsvPgdatDigServiceData*)Data)->ServiceId);
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE PresetNumber = %d ", mGetTableName(TableId), ((HsvPgdatPresetData*)Data)->PresetNumber);
			break;

		case    IHsvProgramDatabaseConstants_HomingService:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM  %s WHERE HomingServiceType = %d AND OriginalNetworkId = %d AND ServiceId = %d", mGetTableName(TableId), ((HsvPgdatHomServiceData*)Data)->HomingServiceType,((HsvPgdatHomServiceData*)Data)->OriginalNetworkId,((HsvPgdatHomServiceData*)Data)->ServiceId);
			break;
		case    IHsvProgramDatabaseConstants_InteractiveService:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM  %s WHERE FreesatServiceIdentifier = %d AND FreesatGroupID = %d ", mGetTableName(TableId), ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier,((HsvPgdatIntrServiceData*)Data)->FreesatGroupID);
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
		TraceNotice (m, "GetDataFromTableByKey pointing to wrong database ");
	}
	
	return RetVal;
}


Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_GetByKey       ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
	
	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
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
int CHsvSatProgramData_mpgdb_Priv::GetDataFromTableByKeyForFreesat (int MajorTableId, int TableId, Address Data)
{
	int		RetVal = -1;
	char	*TempString = NULL;
	char	sqlQueryBuf [SQL_TABLE_SMALL_QUERY_LENGTH];


	if (MajorTableId == ipgdbconst_Satellite)
	{
		/* For the SELECT query based on the set of keys */
		switch (TableId)
		{
		case	ipgdbconst_DigitalService:
		case	ipgdbconst_CurrentDigitalService:
			TempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT * FROM %s WHERE FreesatServiceIdentifier = %d ", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->FreesatServiceIdentifier);
			break;

        case    ipgdbconst_SatInfo:
        case    ipgdbconst_CurrentSatInfo:
		case	ipgdbconst_DigitalTS:
		case	ipgdbconst_CurrentDigitalTS:
		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
		case    IHsvProgramDatabaseConstants_HomingService:
		case 	IHsvProgramDatabaseConstants_CurrentHomingService:
		case    IHsvProgramDatabaseConstants_InteractiveService:
		case 	IHsvProgramDatabaseConstants_CurrentInteractiveService:
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

	return RetVal;
}

#if 1
//Customized GetByKey for Freesat as for freesat services, FreesatServiceIdentifier is the unique key
Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_GetByKeyForFreesat (int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid),index;
	HsvPgdatDigServiceData svcData;


    switch(GETMAJORTABLEID(tableid))
    {

	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:

		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			RetVal = GetDataFromTableByKeyForFreesat(GETMAJORTABLEID(tableid), SubTableId, channeldata);
		}
		else
		{
			RetVal = FALSE;
			for(index=0;index<srtdb2_GetNoOfRecords(mGetDBTableIds(SubTableId));index++)
			{
				if(srtdb2_QueryOnIndex(mGetDBTableIds(SubTableId),index,(Address)&svcData))
				{
					if(svcData.FreesatServiceIdentifier == ((HsvPgdatDigServiceData*)(channeldata))->FreesatServiceIdentifier)
					{
						memcpy(channeldata,&svcData,sizeof(HsvPgdatDigServiceData));
						RetVal = TRUE;
						break;
					}
				}
			}	
		}
		break;
	default:
		RetVal = FALSE;
		break;
	}

	return RetVal;
}
#endif


int CHsvSatProgramData_mpgdb_Priv::GetCurrentIndexFromTable (int TableId, Address Data, Bool *Valid)
{
	int		RetVal = -1;
	int		Index = 0;
	char	*tempString = NULL;
	sqlite3_stmt	*Statement = NULL;
	char	sqlQueryBuf[SQL_TABLE_SMALL_QUERY_LENGTH * 2];

	*Valid = FALSE;

	if(mCurrentTable == ipgdbconst_Satellite)
	{
		/* Make the Query to get Index based on the fixed keys */
		switch (TableId)
		{
		case	ipgdbconst_SatInfo:
		case	ipgdbconst_CurrentSatInfo:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM %s WHERE LnbNumber = %d ", mGetTableName(TableId), (int)((HsvPgdatDigSatInfoData*)Data)->LnbNumber);
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
				"SELECT DbIndex FROM %s WHERE Tpid = %d AND ServiceId = %d", mGetTableName(TableId),
				((HsvPgdatDigServiceData*)Data)->Tpid, ((HsvPgdatDigServiceData*)Data)->ServiceId);
			break;

		case	ipgdbconst_Preset:
		case	ipgdbconst_CurrentPreset:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM  %s WHERE PresetNumber = %d ", mGetTableName(TableId), ((HsvPgdatPresetData*)Data)->PresetNumber);
			break;
		case    IHsvProgramDatabaseConstants_HomingService:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM  %s WHERE HomingServiceType = %d AND OriginalNetworkId = %d AND ServiceId = %d", mGetTableName(TableId), ((HsvPgdatHomServiceData*)Data)->HomingServiceType,((HsvPgdatHomServiceData*)Data)->OriginalNetworkId,((HsvPgdatHomServiceData*)Data)->ServiceId);
			break;
		case    IHsvProgramDatabaseConstants_InteractiveService:
			tempString = sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf,\
				"SELECT DbIndex FROM  %s WHERE FreesatServiceIdentifier = %d AND FreesatGroupID = %d ", mGetTableName(TableId), ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier,((HsvPgdatIntrServiceData*)Data)->FreesatGroupID);
			break;
		default:
			break;
		}
	}
	else
	{
	}

	
	if (tempString != NULL) 
	{
		/* Now extract the Index value */
		RetVal = sqlite3_prepare_v2 (SqliteDbHandle, sqlQueryBuf, (SQL_TABLE_SMALL_QUERY_LENGTH*2), &Statement, NULL);
		
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		if(RetVal == SQLITE_OK)
		{
			RetVal = sqlite3_step (Statement);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
			if (RetVal == SQLITE_ROW)
			{
				*Valid = TRUE;
				Index = sqlite3_column_int (Statement, 0);
			}
			RetVal = sqlite3_finalize (Statement);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		}
	}
	return Index;
}


int CHsvSatProgramData_mpgdb_Priv::ipgdb_GetIndex       ( int tableid, int *index, Address channeldata)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

   
	SEM_TAKE(mProgramMapSem);
	*index = 0;
    switch(GETMAJORTABLEID(tableid))
    {
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

int CHsvSatProgramData_mpgdb_Priv::GetDataFromTableByIndex (int TableId, int Index, Address Data)
{
	int		RetVal = FALSE;
	char	sqlQueryBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	switch (TableId)
	{
	case	ipgdbconst_DigitalTS:
	case	ipgdbconst_CurrentDigitalTS:
	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
	case	ipgdbconst_SatInfo:
	case 	IHsvProgramDatabaseConstants_HomingService:
	case 	IHsvProgramDatabaseConstants_InteractiveService:
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

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_GetByIndex     ( int tableid, int index, Address channeldata)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
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

int CHsvSatProgramData_mpgdb_Priv::GetRangeOfDataByKey (int ReqTableId, int NoofKeys, Address Data, int *From, int *To)
{
	int		RetVal = -1;
	sqlite3_stmt	*statement = NULL;
	char	queryStatmentBuf[SQL_TABLE_SMALL_QUERY_LENGTH*2];

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
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigSatInfoData*)Data)->LnbNumber);\
					RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					if (RetVal == SQLITE_OK) \
					{\
						RetVal = sqlite3_step (statement);\
						if(RetVal==SQLITE_ROW)\
						{\
							*From = *To = sqlite3_column_int (statement, 0);\
							sqlite3_finalize (statement);\
						}\
						else\
						{\
						sqlite3_reset(statement);\
						sqlite3_finalize (statement);\
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
			/*during insertion records are not sorted by frequency*/\	
			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber):\
/*			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE LnbNumber = %d ORDER BY Frequency DESC LIMIT 1 ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber):*/\
			((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE LnbNumber = %d AND Frequency = %d ORDER BY Frequency DESC LIMIT 1", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency):\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE LnbNumber = %d AND Frequency = %d AND Polarization = %d ORDER BY Frequency DESC LIMIT 1", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->Polarization));\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				if (RetVal == SQLITE_OK) \
				{\
					/* Get the MAX and MIN Index values for given condition and assign to From and To */\
					RetVal = sqlite3_step (statement);\
					if(RetVal==SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber):\
/*						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE LnbNumber = %d ORDER BY Frequency ASC LIMIT 1 ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber):*/\
							((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE LnbNumber = %d AND Frequency = %d ORDER BY Frequency ASC LIMIT 1 ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency):\
											   sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE LnbNumber = %d AND Frequency = %d AND Polarization = %d ORDER BY Frequency ASC LIMIT 1 ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber, ((HsvPgdatDigTSData*)Data)->Frequency, ((HsvPgdatDigTSData*)Data)->Polarization));\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						if (RetVal == SQLITE_OK) \
						{\
							RetVal = sqlite3_step (statement);\
							if(RetVal==SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
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
				(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MAX(DbIndex) FROM %s WHERE Tpid = %d", TableName, ((HsvPgdatDigServiceData*)Data)->Tpid): \
								  sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE Tpid = %d AND ServiceId = %d ORDER BY ServiceId DESC LIMIT 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->Tpid, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				if (RetVal == SQLITE_OK) \
				{\
					RetVal = sqlite3_step (statement);\
					if(RetVal == SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT MIN(DbIndex) FROM %s WHERE Tpid = %d", TableName, ((HsvPgdatDigServiceData*)Data)->Tpid): \
									  sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE Tpid = %d AND ServiceId = %d ORDER BY ServiceId ASC LIMIT 1 ", TableName, ((HsvPgdatDigServiceData*)Data)->Tpid, ((HsvPgdatDigServiceData*)Data)->ServiceId);\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						if (RetVal == SQLITE_OK) \
						{\
							RetVal = sqlite3_step (statement);\
							if(RetVal == SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
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
					if (RetVal == SQLITE_OK) \
					{\
						RetVal = sqlite3_step (statement);\
						if(RetVal==SQLITE_ROW)\
						{\
							*From = *To = sqlite3_column_int (statement, 0);\
							sqlite3_finalize (statement);\
						}\
						else\
						{\
						sqlite3_reset(statement);\
						sqlite3_finalize (statement);\
						}\
					}\
				}

	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			}
			break;
		case	IHsvProgramDatabaseConstants_HomingService:
			/* Here totally 3 keys are present Primary - HomingServiceType | Onid | SerivceId  . So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
			(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d ORDER BY DbIndex DESC LIMIT 1 ", TableName, ((HsvPgdatHomServiceData*)Data)->HomingServiceType):\
			((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d AND OriginalNetworkId = %d ORDER BY DbIndex DESC LIMIT 1", TableName, ((HsvPgdatHomServiceData*)Data)->HomingServiceType, ((HsvPgdatHomServiceData*)Data)->OriginalNetworkId):\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d AND OriginalNetworkId = %d AND  ServiceId = %d ORDER BY DbIndex DESC LIMIT 1", TableName, ((HsvPgdatHomServiceData*)Data)->HomingServiceType,((HsvPgdatHomServiceData*)Data)->OriginalNetworkId, ((HsvPgdatHomServiceData*)Data)->ServiceId));\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				if (RetVal == SQLITE_OK) \
				{\
					/* Get the MAX and MIN Index values for given condition and assign to From and To */\
					RetVal = sqlite3_step (statement);\
					if(RetVal==SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d ORDER BY DbIndex ASC LIMIT 1 ", TableName, ((HsvPgdatHomServiceData*)Data)->HomingServiceType):\
							((NoofKeys == 2) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d AND OriginalNetworkId = %d ORDER BY DbIndex ASC LIMIT 1 ", TableName, ((HsvPgdatHomServiceData*)Data)->HomingServiceType,((HsvPgdatHomServiceData*)Data)->OriginalNetworkId):\
											   sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d AND OriginalNetworkId = %d AND  ServiceId = %d ORDER BY DbIndex ASC LIMIT 1 ", TableName, ((HsvPgdatHomServiceData*)Data)->HomingServiceType,((HsvPgdatHomServiceData*)Data)->OriginalNetworkId,((HsvPgdatHomServiceData*)Data)->ServiceId));\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						if (RetVal == SQLITE_OK) \
						{\
							RetVal = sqlite3_step (statement);\
							if(RetVal==SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					}\
				}\
			}
	#include "hsvpgdat_tableinfo.h"
	#undef	TABLE_ITEM
			break;
	case	IHsvProgramDatabaseConstants_InteractiveService:
			/* Here totally 3 keys are present. So based on the noofkeys preparing the relevant SQL statement  */
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == ReqTableId)) {\
				(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE FreesatServiceIdentifier = %d ORDER BY DbIndex DESC LIMIT 1", TableName, ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier): \
								  sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE FreesatServiceIdentifier = %d AND FreesatGroupID = %d ORDER BY DbIndex DESC LIMIT 1 ", TableName, ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier, ((HsvPgdatIntrServiceData*)Data)->FreesatGroupID);\
				RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
				if (RetVal == SQLITE_OK) \
				{\
					RetVal = sqlite3_step (statement);\
					if(RetVal == SQLITE_ROW)\
					{\
						*To = sqlite3_column_int (statement, 0);\
						sqlite3_finalize (statement);\
						statement = NULL;\
						(NoofKeys == 1) ? sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE FreesatServiceIdentifier = %d ORDER BY DbIndex ASC LIMIT 1 ", TableName, ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier): \
									  sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, queryStatmentBuf, "SELECT DbIndex FROM %s WHERE FreesatServiceIdentifier = %d AND FreesatGroupID = %d ORDER BY DbIndex ASC LIMIT 1 ", TableName, ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier, ((HsvPgdatIntrServiceData*)Data)->FreesatGroupID);\
						RetVal = sqlite3_prepare_v2 (SqliteDbHandle, queryStatmentBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
						if (RetVal == SQLITE_OK) \
						{\
							RetVal = sqlite3_step (statement);\
							if(RetVal == SQLITE_ROW)\
							{\
								*From = sqlite3_column_int (statement, 0);\
								sqlite3_finalize (statement);\
							}\
							else\
							{\
							sqlite3_reset(statement);\
							sqlite3_finalize (statement);\
							}\
						}\
					}\
					else\
					{\
					sqlite3_reset(statement);\
					sqlite3_finalize (statement);\
					}\
				}\
			}

	#include "hsvpgdat_tableinfo.h"
	#undef	TABLE_ITEM
			break;
		default:
			 break;
		}
	}
	else
	{
		TraceNotice (m ,"Error..Wrong database pointed in GetRangeOfDataByKey ");
	}


	return RetVal;
}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_GetRange       ( int tableid, int noofkeys, Address channeldata, int *from, int *to)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
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


void CHsvSatProgramData_mpgdb_Priv::PrepareUpdateElementStringForSinglePrepare (int TableId,	char *statementbuf, char *tempString)
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

	case	IHsvProgramDatabaseConstants_HomingService:
#define	HOMSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_homsrvcitems.h"
#else
#include "hsvpgdat_homsrvcitems.h"
#endif

#undef	HOMSRVC_ITEM

		break;
	case	IHsvProgramDatabaseConstants_InteractiveService:
#define	INTSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_intrsrvcitems.h"
#else
#include "hsvpgdat_intrsrvcitems.h"
#endif

#undef	INTSRVC_ITEM

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

sqlite3_stmt* CHsvSatProgramData_mpgdb_Priv::PrepareSqlUpdateStatement (int InsertTableId)
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
	RetVal = sqlite3_prepare_v2 (SqliteDbHandle, sqldbTableInsertStatementBuf, SQL_TABLE_MEDIUM_QUERY_LENGTH, &statement, NULL);
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	if (RetVal != SQLITE_OK)
	{
		statement = NULL;
	}
	return statement;
}

int CHsvSatProgramData_mpgdb_Priv::FillUpdateStatement (sqlite3_stmt *InsertHandle, int TableId, Address Data)
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
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigSatInfoData,InsertHandle,tempVar,tempBuff,count)

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

		case	IHsvProgramDatabaseConstants_HomingService:

#define HOMSRVC_ITEM(element, type, bitdec, bitdef, deflt ) \
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatHomServiceData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_homsrvcitems.h"
#else
#include "hsvpgdat_homsrvcitems.h"
#endif
#undef	HOMSRVC_ITEM
		break;
		case	IHsvProgramDatabaseConstants_InteractiveService:

#define INTSRVC_ITEM(element, type, bitdec, bitdef, deflt ) \
	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatIntrServiceData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_intrsrvcitems.h"
#else
#include "hsvpgdat_intrsrvcitems.h"
#endif
#undef	INTSRVC_ITEM
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
	return count;
}

Bool CHsvSatProgramData_mpgdb_Priv::mCheckForUpdates (void *Data, int Index, int *NoItemsChanged, int *ItemIDs)
{
			HsvPgdatDigServiceData               	 DbData;
			*NoItemsChanged = 0;
			int count =0;
			int count1=0;
			int comparenamesize=0;
			if(TRUE == GetDataFromTableByIndex (ipgdbconst_DigitalService, Index, &DbData ))
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
				if (memcmp(DbData.ChannelName,((HsvPgdatDigServiceData*)Data)->ChannelName, comparenamesize*sizeof(Nat16)))
				{
				             ItemIDs[*NoItemsChanged] = 12;
				             (*NoItemsChanged)++;
							 TraceNotice(m," 1 NoItemsChanged= %d ",*(NoItemsChanged));
				}
				TraceNotice(m," 3 NoItemsChanged= %d ",*(NoItemsChanged));
			}
	return TRUE ;			   
}
int CHsvSatProgramData_mpgdb_Priv::UpdateEntryToTableWithSinglePrepare (int InsertTableId, Address Data)
{
	int		RetVal = -1;
	int		Index = 0, count = 0, LastIndex = 0;
	Bool	Valid = FALSE;
	int  ret = 0;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;

	/* Get the index of the table based on keys provided by user */
	Index = GetCurrentIndexFromTable (InsertTableId, Data, &Valid);
	if (Valid == TRUE)
	{
		if (mCurrentTable == ipgdbconst_Satellite)
		{
			handle = SqliteHandleSatMaps;
			num_tbl = MAX_SAT_PGDB_TABLES;
		}
		else
		{
			TraceNotice (m, " Error.. pointing to wrong database ");
		}

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
			NoItemsChanged = 0;
			if (InsertTableId == ipgdbconst_DigitalService)
			{
				RetVal = mCheckForUpdates (Data, Index, &NoItemsChanged, ItemIDs);
			}						
			RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);


		/* Now update entries to this Index */
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
				sqlite3_bind_int(handle[count].UpdateHandle,1,Index);\
				LastIndex = FillUpdateStatement(handle[count].UpdateHandle,InsertTableId,Data);\
				ret = sqlite3_bind_int(handle[count].UpdateHandle,LastIndex,Index);\
				RetVal = sqlite3_step (handle[count].UpdateHandle);\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				RetVal = sqlite3_reset (handle[count].UpdateHandle);\
			}

#include "hsvpgdat_tableinfo.h"

		RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
		if(RetVal == SQLITE_BUSY)
				RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
		

#undef	TABLE_ITEM
		}
		if(TRUE==Notification_enable)
		{
			if (NoItemsChanged)
			{
				for (int i=0;i<NoItemsChanged;i++)
				{
				TraceDebug (m, "%s %d Update channel Preset number=%d",__FUNCTION__, __LINE__,((HsvPgdatDigServiceData*)Data)->PresetNumber);
				insN->OnEvent(IHsvSatelliteInstallationNotify_EventUpdated, ((((HsvPgdatDigServiceData*)Data)->PresetNumber << 16) | ItemIDs[i]));
				}
			}
		}
	}
	return RetVal;
}


Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_Update     ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Satellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_DONE != UpdateEntryToTableWithSinglePrepare (SubTableId, channeldata))
			{
				RetVal = FALSE;
			}
		}
		else
		{
			RetVal = srtdb2_Update(mGetDBTableIds(SubTableId), mGetPrimaryKey(SubTableId, channeldata), mGetSecondaryKey(SubTableId, channeldata), mGetTertiaryKey(SubTableId, channeldata), mGetQuaternaryKey(SubTableId, channeldata), channeldata);
		}
            		
		break;
	default:
		RetVal = FALSE;
	}

	SEM_GIVE(mProgramMapSem);
	return RetVal;
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_EnableAutoCommit(Bool enable)
{
	/* Set the variables to start the autocommit */
	mAutoCommitEnabled = enable;
//	mSetDirty(FALSE);
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_ChannelTableChanged(void)
{
	pgdatN_OnChannelTableChanged();
}

/* Initialize with Default values */
void CHsvSatProgramData_mpgdb_Priv::ipgdb_Initialise(int tableid, Address channeldata )
{
	switch(tableid)
    {
	case	ipgdbconst_SatInfo:		
	case	ipgdbconst_CurrentSatInfo:
		*(HsvPgdatDigSatInfoData*)channeldata = DefaultSatInfoValues;
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
	case    IHsvProgramDatabaseConstants_HomingService:
	case 	IHsvProgramDatabaseConstants_CurrentHomingService:
		*(HsvPgdatHomServiceData*)channeldata = DefaultHomingSvcValues;
		break;
	case    IHsvProgramDatabaseConstants_InteractiveService:
	case 	IHsvProgramDatabaseConstants_CurrentInteractiveService:
		*(HsvPgdatIntrServiceData*)channeldata = DefaultInteractiveSvcValues;
		break;
	}
}

void CHsvSatProgramData_mpgdb_Priv::CopyTempDataToCurrentTable (void)
{
	int	RetVal = 0;
	char 	*TempString = NULL;
	char	CopyStatementBuf[SQL_TABLE_SMALL_QUERY_LENGTH];

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

void CHsvSatProgramData_mpgdb_Priv::ipgdb_UpdateChannelMapFromTemp (void)
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


void CHsvSatProgramData_mpgdb_Priv::chmapop_Lock(void)
{
    SEM_TAKE(mProgramMapSem);
}

void CHsvSatProgramData_mpgdb_Priv::chmapop_UnLock(void)
{
    SEM_GIVE(mProgramMapSem);
} 

FResult CHsvSatProgramData_mpgdb_Priv::chmapop_ReloadFromFlash(int tableid)
{
	FResult		Err = err_Ok;
	return TRUE;
}
   
FResult CHsvSatProgramData_mpgdb_Priv::chmapop_CommitToFlash(int tableid)
{
	FResult		Err = err_Ok;
	pgdatN_OnChannelTableChanged();
	return Err;
}
    
FResult CHsvSatProgramData_mpgdb_Priv::chmapop_LoadChannelTable(int tableid, char* dir)
{
	FResult		Err = err_Ok;
	return Err;
}
    
FResult CHsvSatProgramData_mpgdb_Priv::chmapop_SaveChannelTable(int tableid, char* dir)
{
	FResult		Err = err_Ok;

	return Err;
}
   
void CHsvSatProgramData_mpgdb_Priv::chmapop_SetDirtyBit(void)
{
}
   
void CHsvSatProgramData_mpgdb_Priv::chmapop_EnableAutoCommit(Bool enable)
{
	mAutoCommitEnabled = enable;
//	mSetDirty(FALSE);
}
    
void CHsvSatProgramData_mpgdb_Priv::chmapop_ChannelTableChanged(void)
{
	pgdatN_OnChannelTableChanged();
}
	
FResult CHsvSatProgramData_mpgdb_Priv::chmapop_LoadChannelExternal(char* dir)
{
	FResult	Err = err_NotSupported;
	UNUSED(dir);
	/*TODO: */
	return Err;
}
    
FResult CHsvSatProgramData_mpgdb_Priv::chmapop_SaveChannelExternal(char* dir)
{
	FResult	Err = err_NotSupported;
	UNUSED(dir);
	/*TODO: */
	return Err;
}
	
FResult CHsvSatProgramData_mpgdb_Priv::chmapop_GetMediumFromTable(char *dir, int *medium)
{
	FResult	Err = err_NotSupported;
	UNUSED(dir);
	UNUSED(medium);
	/*TODO: */
	return Err;
}

/* SQLITE DELETE Functionality */
int CHsvSatProgramData_mpgdb_Priv::DeleteEntryFromTable (int deleteTableId, Address Data)
{
	int		RetVal = -1, Ret = -1;
	int		Index = 0;
	Bool	Valid = FALSE;
	char	sqlDeleteBuf [SQL_TABLE_SMALL_QUERY_LENGTH];

	/* Get index corresponding to given keys */
	Index = GetCurrentIndexFromTable (deleteTableId, Data, &Valid);

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
		if(RetVal == SQLITE_BUSY) 
			RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	

#ifdef	ENABLE_TIME_TRACE
		t2 = errlib__GetMicrosSinceInit ();
		PRINT_TIMING_INFO("DeleteEntryFromTable",t1,t2);
#endif

	}

	return RetVal;
}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_Delete     ( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_OK != DeleteEntryFromTable (SubTableId, channeldata))
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
			TraceDebug (m, "%s %d PresetNumber deleted %d \n", __FUNCTION__, __LINE__,(int)preset->PresetNumber);
			insN->OnEvent(IHsvSatelliteInstallationNotify_EventPresetDeleted,(int)preset->PresetNumber);
		}
	}
	return RetVal;
}

/* SQLITE INSERT Functionality */
int CHsvSatProgramData_mpgdb_Priv::GetIndexValForInsertion (int majorTableId, int InsertTableId, Address Data, Bool *Valid)
{
	int		RetVal;
	int		Index = 0;
	sqlite3_stmt *statement;
	char	sqlQueryBuf[SQL_TABLE_SMALL_QUERY_LENGTH];
	int		MatchingEntryExist = 0;

	*Valid = FALSE;
	/* Main intention of this function is to have a sort based on primary key alone. 
	Also the index value will literally indicate the index in particular table */

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
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						RetVal = sqlite3_step (statement);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							sqlite3_reset(statement);\
							sqlite3_finalize(statement);\
							if (MatchingEntryExist) \
							{\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE LnbNumber = %d ", TableName, ((HsvPgdatDigTSData*)Data)->LnbNumber);\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									RetVal = sqlite3_step (statement);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										sqlite3_finalize(statement);\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex > %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										if(RetVal == SQLITE_BUSY) \
											RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	\
									}\
									else\
									{\
										sqlite3_reset(statement);\
										sqlite3_finalize(statement);\
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
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE Tpid = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->Tpid);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						RetVal = sqlite3_step (statement);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							sqlite3_finalize(statement);\
							if (MatchingEntryExist)\
							{\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE Tpid = %d ", TableName, ((HsvPgdatDigServiceData*)Data)->Tpid);\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									RetVal = sqlite3_step (statement);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										sqlite3_finalize(statement);\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										if(RetVal == SQLITE_BUSY) \
											RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	\
									}\
									else\
									{\
										sqlite3_reset(statement);\
										sqlite3_finalize(statement);\
										GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
										Index++;\
									}\
								}\
							}\
						}\
						else\
						{\
							sqlite3_reset(statement);\
							sqlite3_finalize(statement);\
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
		if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)){\
		PrintfNotice (" MajorTableId %d TableId %d \n",MajorTableId,TableId);\
		GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
		PrintfNotice (" TableName is %s Index %d \n",TableName,Index);\
		if(Index>0) {\
			Index = 0;\
			sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE PresetNumber < %d order by PresetNumber  DESC limit 1 ", TableName, ((HsvPgdatPresetData*)Data)->PresetNumber); \
			RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
			if (RetVal == SQLITE_OK) {\
				RetVal = sqlite3_step (statement);\
				if(RetVal==SQLITE_ROW)\
				{\
					Index = sqlite3_column_int (statement, 0);\
					PrintfNotice (" Index is %d \n",Index);\
					sqlite3_reset(statement);\
					sqlite3_finalize(statement);\
				}\
				else\
				{\
					sqlite3_reset(statement);\
					sqlite3_finalize(statement);\
					GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				}\
			}\
			RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
			CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\							
			sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
			RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
			CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
			RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
			CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
			if(RetVal == SQLITE_BUSY)  \
				RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	\
		}\
		*Valid = TRUE;\
	}
	#include "hsvpgdat_tableinfo.h"

	#undef	TABLE_ITEM
			
			break;


		case  IHsvProgramDatabaseConstants_HomingService:   /* key is combination of HomingSvc Type : serviceid : onid */

			#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)\
				if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)){\
					GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
					if (Index > 0)\
					{\
						if(((HsvPgdatHomServiceData*)Data)->HomingServiceType == LD_HOMINGSERVICES)\
						{\
							Index = 0;\
							sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT DbIndex FROM %s WHERE HomingServiceType = %d ORDER BY DbIndex DESC limit 1", TableName,((HsvPgdatHomServiceData*)Data)->HomingServiceType);\
							RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
							CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
							if (RetVal == SQLITE_OK)\
							{\
								RetVal = sqlite3_step (statement);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if(RetVal==SQLITE_ROW)\
								{\
									Index = sqlite3_column_int (statement, 0);\
									Index++;\
								}\
								sqlite3_reset(statement);\
								sqlite3_finalize(statement);\
								/* Below UPDATE Query is to push the ILD services one index below to insert LD service */\
								RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE HomingServiceType = 1",TableName);\
								RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
							}\
						}\
						else\
						{\
							Index++;\
						}\
					}\
				*Valid = TRUE;\
			}
			#include "hsvpgdat_tableinfo.h"
			#undef	TABLE_ITEM
			break;
		case	IHsvProgramDatabaseConstants_InteractiveService:
			/* Here the request can be done for TpId alone	*/
	#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
			if (TableId == InsertTableId) {\
				GET_NUM_ROW_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
				if (Index > 0) \
				{\
					MatchingEntryExist = 0;\
					sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT COUNT(*) FROM %s WHERE FreesatServiceIdentifier = %d ", TableName, ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier);\
					RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
					CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
					if (RetVal == SQLITE_OK) {\
						RetVal = sqlite3_step (statement);\
						CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
						if(RetVal==SQLITE_ROW)\
						{\
							MatchingEntryExist = sqlite3_column_int (statement, 0);\
							if (MatchingEntryExist)\
							{\
								sqlite3_finalize(statement);\
								sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "SELECT MAX(DbIndex) FROM %s WHERE FreesatServiceIdentifier = %d ", TableName, ((HsvPgdatIntrServiceData*)Data)->FreesatServiceIdentifier);\
								/*PrintfNotice ("S2ChannelLib: ANEESH: DbgPrint Query is %s \n",sqlQueryBuf);*/\
								RetVal = sqlite3_prepare_v2(SqliteDbHandle, sqlQueryBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &statement, NULL);\
								CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
								if (RetVal == SQLITE_OK) {\
									RetVal = sqlite3_step (statement);\
									CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
									if(RetVal==SQLITE_ROW)\
									{\
										Index = sqlite3_column_int (statement, 0);\
										Index++;\
										/*PrintfNotice ("S2ChannelLib: Got Row Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
										sqlite3_finalize(statement);\
										/* The new entry will sit in next Index'. So increment the value of Index for all higer Index value */\
										RetVal = sqlite3_exec (SqliteDbHandle, "BEGIN", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, sqlQueryBuf, "UPDATE %s SET DbIndex=DbIndex+1 WHERE DbIndex >= %d ", TableName, Index);\
										RetVal = sqlite3_exec (SqliteDbHandle, sqlQueryBuf, NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);\
										CHECK_SQLITE_ERR(SqliteDbHandle, RetVal);\
										if(RetVal == SQLITE_BUSY) \
											RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	\
									}\
									else\
									{\
										sqlite3_reset(statement);\
										sqlite3_finalize(statement);\
										GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
										Index++;\
										/*PrintfNotice ("S2ChannelLib: Func %s and line %d index value is %d \n",__FUNCTION__, __LINE__, Index);*/\
									}\
								}\
							}\
							else\
							{\
								/*no matching found addt the end of the list*/\
								sqlite3_reset(statement);\
								sqlite3_finalize(statement);\
								GET_MAX_VALUE_FROM_TABLE(TableId, InsertTableId, TableName,SqliteDbHandle,sqlQueryBuf,statement,Index)\
								Index++;\
							}\
						}\
						else\
						{\
							sqlite3_reset(statement);\
							sqlite3_finalize(statement);\
						}\
					}\
				}\
				*Valid = TRUE;\
			}

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
		TraceNotice (m, "Error.. GetIndexValForInsertion pointing to wrong database ");
	}
	return Index;
}

void CHsvSatProgramData_mpgdb_Priv::PrepareInsertElementStringForSinglePrepare (int TableId,	char *statementbuf, char *tempString)
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
#include "data/hsvpgdat_sat_digtsitems.h"
#else
#include "hsvpgdat_sat_digtsitems.h"
#endif
#undef	DIGTS_ITEM
		break;

	case	ipgdbconst_DigitalService:
	case	ipgdbconst_CurrentDigitalService:
#define	DIGSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_sat_digsrvcitems.h"
#else
#include "hsvpgdat_sat_digsrvcitems.h"
#endif
#undef	DIGSRVC_ITEM
		break;

	case	ipgdbconst_Preset:
	case	ipgdbconst_CurrentPreset:
#define	PRESET_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_sat_presetitems.h"
#else
#include "hsvpgdat_sat_presetitems.h"
#endif
#undef	PRESET_ITEM
		break;

	case IHsvProgramDatabaseConstants_HomingService:
	case IHsvProgramDatabaseConstants_CurrentHomingService:

#define	HOMSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_homsrvcitems.h"
#else
#include "hsvpgdat_homsrvcitems.h"
#endif
#undef	HOMSRVC_ITEM
		break;
	case IHsvProgramDatabaseConstants_InteractiveService:
	case IHsvProgramDatabaseConstants_CurrentInteractiveService:

#define	INTSRVC_ITEM(element, type, bitdec, bitdef, deflt )	\
	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)

#ifndef __cplusplus
#include "data/hsvpgdat_intrsrvcitems.h"
#else
#include "hsvpgdat_intrsrvcitems.h"
#endif
#undef	INTSRVC_ITEM
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

sqlite3_stmt* CHsvSatProgramData_mpgdb_Priv::PrepareSqlInsertStatement (int InsertTableId)
{
	Nat32	RetVal = err_Ok;
	char 	tempString[SQL_TEMP_STRING_LENGTH];
	sqlite3_stmt	*statement = NULL;
	
#define	TABLE_ITEM(MajorTableId,TableId, TableName, Type)	\
		if ((mCurrentTable == MajorTableId) && (TableId == InsertTableId)) {\
			sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, sqldbTableInsertStatementBuf, "INSERT INTO %s ", TableName);\
			if (strcmp(TableName, "PresetTable")==0) \
			{ \
				sqlite3_snprintf (SQL_TABLE_MEDIUM_QUERY_LENGTH, tempString, "(DbIndex,Frequency,PresetNumber,Tpid,LnbNumber,Polarization,OriginalNetworkId,Tsid,ServiceId,FavoriteNumber,EmmChannel,SystemHidden,NumericSelect,VisibleService,dummy) " );\
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
	CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);

	if (RetVal != SQLITE_OK)
	{
		statement = NULL;
	}

	return statement;
}

void CHsvSatProgramData_mpgdb_Priv::FillInsertStatement (sqlite3_stmt *InsertHandle, int TableId, Address Data)
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
		
	case	ipgdbconst_SatInfo: 		/* Key is LnbNumber */
	case	ipgdbconst_CurrentSatInfo:
			
#define SATINFO_ITEM(element, type, bitdec, bitdef, deflt ) \
		BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatDigSatInfoData,InsertHandle,tempVar,tempBuff,count)
			
#ifndef __cplusplus
#include "data/hsvpgdat_satinfoitems.h"
#else
#include "hsvpgdat_satinfoitems.h"
#endif
#undef	SATINFO_ITEM
		break;

		case	IHsvProgramDatabaseConstants_HomingService:

#define HOMSRVC_ITEM(element, type, bitdec, bitdef, deflt ) \
		BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatHomServiceData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_homsrvcitems.h"
#else
#include "hsvpgdat_homsrvcitems.h"
#endif
#undef	HOMSRVC_ITEM
		break;
		case	IHsvProgramDatabaseConstants_InteractiveService:

#define INTSRVC_ITEM(element, type, bitdec, bitdef, deflt ) \
		BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,HsvPgdatIntrServiceData,InsertHandle,tempVar,tempBuff,count)

#ifndef __cplusplus
#include "data/hsvpgdat_intrsrvcitems.h"
#else
#include "hsvpgdat_intrsrvcitems.h"
#endif
#undef	INTSRVC_ITEM
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

int CHsvSatProgramData_mpgdb_Priv::InsertEntryToTableWithSinglePrepare (int majorTableId, int InsertTableId, Address Data)
{
	Bool	Valid = FALSE;
	Nat32	RetVal = err_Ok;
	int		Index;
	Nat8	count = 0;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;

	/*Identify the Index which should be inserted now */
	Index = GetIndexValForInsertion (majorTableId, InsertTableId, Data, &Valid);

	if (mCurrentTable == ipgdbconst_Satellite)
	{
		handle = SqliteHandleSatMaps;
		num_tbl = MAX_SAT_PGDB_TABLES;
		Valid = TRUE;
	}
	else
	{
		TraceNotice(m," Error... Insert pointing to wrong channel maps ");\
	}
	
	if( Valid == TRUE)
	{
		for (count = 0; count < num_tbl; count++)
		{
			if (InsertTableId == handle[count].SubTableId)
			{
				if (handle[count].InsertHandle == NULL)
				{
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
				RetVal = sqlite3_step (handle[count].InsertHandle);\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				RetVal = sqlite3_reset (handle[count].InsertHandle);\
			}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

			RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);
			CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);
			if(RetVal == SQLITE_BUSY) 
				RetVal = sqlite3_exec (SqliteDbHandle, "COMMIT", NULL, NULL, NULL);	
			

		}
	}

	return RetVal;
}


int CHsvSatProgramData_mpgdb_Priv::InsertEntryToTableWithSinglePrepareIndex (int majorTableId, int InsertTableId, Address Data, int Index)
{
	Bool	Valid = FALSE;
	Nat32	RetVal = err_Ok;
	Nat8	count = 0;
	SqliteHandleMapEntry *handle = NULL;
	int num_tbl = 0;

	if (mCurrentTable == ipgdbconst_Satellite)
	{
		handle = SqliteHandleSatMaps;
		num_tbl = MAX_SAT_PGDB_TABLES;
		Valid = TRUE;
	}
	else
	{
		TraceNotice(m," Error... Insert pointing to wrong channel maps ");\
	}
	
	if( Valid == TRUE)
	{
		for (count = 0; count < num_tbl; count++)
		{
			if (InsertTableId == handle[count].SubTableId)
			{
				if (handle[count].InsertHandle == NULL)
				{
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
				RetVal = sqlite3_step (handle[count].InsertHandle);\
				CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
				RetVal = sqlite3_reset (handle[count].InsertHandle);\
			}

#include "hsvpgdat_tableinfo.h"

#undef	TABLE_ITEM

			

		}
	}

	return RetVal;
}


Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_Add( int tableid, Address channeldata )
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);
#ifdef	ENABLE_TIME_TRACE
	Nat64	t1, t2;
#endif

	
	SEM_TAKE(mProgramMapSem);

	
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_OK != InsertEntryToTableWithSinglePrepare (GETMAJORTABLEID(tableid), SubTableId, channeldata))
			{
				TraceNotice(m," InsertEntryToTableWithSinglePrepare is FAILED");
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
			TraceDebug (m, "%s %d PresetNumber added %d \n", __FUNCTION__, __LINE__,(int)preset->PresetNumber);
			insN->OnEvent(IHsvSatelliteInstallationNotify_EventPresetAdded,(int)preset->PresetNumber);
		}
	}
	return RetVal;
}


/* Function to load or Save database.
	TRUE: Load the database from backup to actual 
	FALSE: Save the database to backup from actual */
void CHsvSatProgramData_mpgdb_Priv::LoadOrSaveChannelMaps (Bool LoadOrSave)
{
	int TableIndex = 0, i = 0;
	int TotalNumberOfEntries =0, count = 0, Index = 0;

	HsvPgdatDigTSData		digTsData;
	HsvPgdatDigServiceData	digSrvData;
	HsvPgdatPresetData		presetData;
	HsvPgdatDigSatInfoData	satInfoData;



	/*Clear To Database*/
	
	for(i=0; i<NUM_PGDB_SUBTABLES; i++)
	{
		srtdb2_Init((LoadOrSave) ? (mProgramDbMap[i].SrtDbTableId) : (mProgramDbMap[i].TempSrtDbTableId));
	}

	
	if (LoadOrSave == TRUE)
	{
		/*Load ChanelMaps from backup*/
		TraceNotice (m, "Load ChannelMaps from backup");
		PERFORM_DATABASE_SYNC(mProgramDbMap[0].DbTableId, mProgramDbMap[0].TempSrtDbTableId,mProgramDbMap[0].SrtDbTableId,Index, TotalNumberOfEntries,presetData)
		PERFORM_DATABASE_SYNC(mProgramDbMap[1].DbTableId, mProgramDbMap[1].TempSrtDbTableId,mProgramDbMap[1].SrtDbTableId,Index, TotalNumberOfEntries,digSrvData)
		PERFORM_DATABASE_SYNC(mProgramDbMap[2].DbTableId, mProgramDbMap[2].TempSrtDbTableId,mProgramDbMap[2].SrtDbTableId,Index, TotalNumberOfEntries,satInfoData)
		PERFORM_DATABASE_SYNC(mProgramDbMap[3].DbTableId, mProgramDbMap[3].TempSrtDbTableId,mProgramDbMap[3].SrtDbTableId,Index, TotalNumberOfEntries,digTsData)
		
	}
	else
	{
		/*Save ChannelMaps to backup*/
		TraceNotice (m, "Save ChannelMaps to backup");
		PERFORM_DATABASE_SYNC(mProgramDbMap[0].DbTableId, mProgramDbMap[0].SrtDbTableId,mProgramDbMap[0].TempSrtDbTableId,Index, TotalNumberOfEntries,presetData)
		PERFORM_DATABASE_SYNC(mProgramDbMap[1].DbTableId, mProgramDbMap[1].SrtDbTableId,mProgramDbMap[1].TempSrtDbTableId,Index, TotalNumberOfEntries,digSrvData)
		PERFORM_DATABASE_SYNC(mProgramDbMap[2].DbTableId, mProgramDbMap[2].SrtDbTableId,mProgramDbMap[2].TempSrtDbTableId,Index, TotalNumberOfEntries,satInfoData)
		PERFORM_DATABASE_SYNC(mProgramDbMap[3].DbTableId, mProgramDbMap[3].SrtDbTableId,mProgramDbMap[3].TempSrtDbTableId,Index, TotalNumberOfEntries,digTsData)
	}


} 


void CHsvSatProgramData_mpgdb_Priv::ipgdb_SaveChannelMapsToBackup (void)
{
	LoadOrSaveChannelMaps (FALSE);
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_LoadChannelMapsFromBackup (void)
{
	LoadOrSaveChannelMaps (TRUE);
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_SelectChannelDatabase (int databaseId)
{
	mActiveDatabase = databaseId;
}

void CHsvSatProgramData_mpgdb_Priv::ipgdb_SyncDatabase (int fromDatabaseId, int toDatabaseId)
{

}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_AddInIndex (int tableid, int index, Address channeldata)
{
	Bool	RetVal = TRUE;
	int		SubTableId = GETSUBTABLEID(tableid);

	
	SEM_TAKE(mProgramMapSem);
    switch(GETMAJORTABLEID(tableid))
    {
	case	ipgdbconst_Satellite:
	case	ipgdbconst_TempSatellite:
		if (mActiveDatabase == ipgdb_SqliteDatabase)
		{
			if (SQLITE_OK != InsertEntryToTableWithSinglePrepareIndex (GETMAJORTABLEID(tableid), SubTableId, channeldata,index))
			{
				TraceNotice(m," InsertEntryToTableWithSinglePrepareIndex is FAILED");
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
			TraceDebug (m, "%s %d PresetNumber added %d \n", __FUNCTION__, __LINE__,(int)preset->PresetNumber);
			insN->OnEvent(IHsvSatelliteInstallationNotify_EventPresetAdded,(int)preset->PresetNumber);
		}
	}
	return RetVal;
}

#ifdef	__OPTIMIZATION_CHECKS_ON__

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_CheckDuplicateTpid (int TpId)
{

}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_GetSortDetailsFromDigSrvTable (int *Index, Address Data)
{

}

Bool CHsvSatProgramData_mpgdb_Priv::ipgdb_UpdatePresetInDigSrvTable (int Index, int PresetNumber)
{

}

#endif



