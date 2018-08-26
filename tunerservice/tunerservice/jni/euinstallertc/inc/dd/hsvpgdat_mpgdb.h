
/* SQLITE: CREATE TABLE <TABLE_NAME> (ELMENT_NAME, ELEMENT_TYPE, ...) */
#define	IDENTIFY_CREATE_STATEMENT(element,type,bitdef,tempString,sqldbTableExectureStatement)	\
			sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, " %s %s", #element, type); \
			if (bitdef != 0) \
			{\
				/*  TODO: Check if smallint array works. Otherwise go for text */\
				sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, " %s text", #element);\
				/* After testing moving to text instead of smallint array */\
				/*sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "%s(%d)", tempString,  bitdef);*/\
			}\
			strcat (sqldbTableExectureStatement, tempString);\
			strcat (sqldbTableExectureStatement, ",");

#define	GET_NUM_ROW_FROM_TABLE(TableId, MinorTableId, TableName,SqliteDbHandle, StatementBuf,StatementHandle,Index)	\
	if (TableId == MinorTableId) {\
		/*PrintfNotice ("EuChannelLib : DbgPrint %s line %d \n",__FUNCTION__, __LINE__); */\
		sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, StatementBuf, "SELECT COUNT(*) FROM %s ", TableName);\
		RetVal = sqlite3_prepare_v2(SqliteDbHandle, StatementBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &StatementHandle, NULL);\
		++Preparecount;\
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
		if (RetVal == SQLITE_OK) {\
			RetVal = sqlite3_step (StatementHandle);\
			if(RetVal==SQLITE_ROW)\
			{\
				Index = sqlite3_column_int (StatementHandle, 0);\
				/*PrintfNotice (" Index is %d \n",Index);*/\
			}\
			sqlite3_reset(StatementHandle);\
			sqlite3_finalize(StatementHandle);\
			--Preparecount;\
		}\
	}
			
/* SQLITE: SELECT * FROM TABLE <TABLE_NAME> WHERE <CONDTION(optional)> */
#define	EXTRACT_ELEMENTS_FROM_TABLE(element,type,bitdec,bitdef,defval,structtype,statement,temp,returnString)  \
	if (proceed == TRUE) \
	{\
		if (RetVal == SQLITE_ROW) \
		{\
			switch (type) \
			{\
				case	1:\
				case	2:\
					temp = sqlite3_column_int (statement, index);\
					index++;\
					bitdec((structtype*)Data)->element = temp;\
					break;\
				case	3:\
				case	4:\
					if (bitdef == 0)\
					{\
						temp = sqlite3_column_int (statement, index);\
						index++;\
						bitdec((structtype*)Data)->element = temp;\
					}\
					else\
					{\
						temp = sqlite3_column_bytes16(statement, index);\
						if (temp) {\
							returnString = (void *)sqlite3_column_text16 (statement, index);\
							if (returnString)\
							{\
								memcpy ((void*)((int)((structtype*)Data)->element), returnString, (sizeof(unsigned short) * bitdef));\
							}\
						}\
						else {\
							memset ((void*)((int)((structtype*)Data)->element), 0x00, (sizeof(unsigned short) * bitdef));\
						}\
						index++;\
					}\
					break;\
				case	5:\
					temp = sqlite3_column_int(statement, index);\
					bitdec((structtype*)Data)->element = temp;\
					index++;\
					break;\
				case	6:\
				{\
					long long int temp64 = 0;\
					temp64 = sqlite3_column_int64(statement, index);\
					bitdec((structtype*)Data)->element = temp64;\
					index++;\
					break;\
				}\
			}\
		}\
		else if (RetVal == SQLITE_DONE) \
		{\
			TraceNotice(m," COLUMN READ Complete \n");\
			sqlite3_reset (statement);\
			sqlite3_finalize (statement);\
			--Preparecount;\
			proceed = FALSE;\
		}\
		else \
		{\
			TraceNotice(m," COLUMN READ ERROR Happened \n");\
			sqlite3_reset (statement);\
			sqlite3_finalize (statement);\
			--Preparecount;\
			proceed = FALSE;\
		} \
	}

	#define	CREATE_UPDATE_STATEMENT_FOR_SINGLE_PREPARE(element,type,statementbuf,tempString)		\
		switch (type) \
		{\
			case	1:\
			case	2:\
			case	3:\
			case	4:\
			case	5:\
				sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "%s=? ,",#element); \
				break;\
			case	6:\
				sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "%s=? ,",#element); \
				/*PrintfNotice("Rohit: Create Update Statement: %s = %s", #element, tempString);*/ \
				break;\
		}\
		strcat (statementbuf, tempString); \

#define	BIND_INSERT_VALUES_FOR_SINGLE_PREPARE(element, type, bitdec, bitdef,datatype,statementHandle,tempVar,tempBuff,Index)	\
		switch (type) \
		{\
			case	1:\
			case	2:\
				sqlite3_bind_int (statementHandle,Index,(int)((datatype*)Data)->element); \
				break;\
			case	3:\
			case	4:\
				if (bitdef == 0) \
				{\
					tempVar = (int)((datatype*)Data)->element;\
					sqlite3_bind_int (statementHandle,Index,tempVar); \
				}\
				else \
				{\
					sqlite3_bind_text16(statementHandle, Index, (void*)((int)((datatype*)Data)->element),(-1),NULL);\
				}\
				break;\
			case	5:\
				tempVar = (int)((datatype*)Data)->element;\
				sqlite3_bind_int (statementHandle,Index,(int)(tempVar & 0xFF)); \
				break;\
			case	6:\
				{\
				/*PrintfNotice("Rohit: bind insert values for single prepare: %s = %x, index = %d\n", #element, ((datatype*)Data)->element, Index);*/\
				/*PrintfNotice("Rohit: 64bit insert returns - %d",sqlite3_bind_int64(statementHandle, Index,((datatype*)Data)->element));*/\
				break;\
				}\
		}\
		++Index;

/* SQLITE: SELECT MAX(<val>) FROM TABLE <TABLE_NAME)	*/
#define	GET_MAX_VALUE_FROM_TABLE(TableId, MinorTableId, TableName,SqliteDbHandle, StatementBuf,StatementHandle,Index)	\
	if (TableId == MinorTableId) {\
		/*PrintfNotice ("EuChannelLib : DbgPrint %s line %d \n",__FUNCTION__, __LINE__); */\
		sqlite3_snprintf (SQL_TABLE_SMALL_QUERY_LENGTH, StatementBuf, "SELECT MAX(DbIndex) FROM %s ", TableName);\
		RetVal = sqlite3_prepare_v2(SqliteDbHandle, StatementBuf, SQL_TABLE_SMALL_QUERY_LENGTH, &StatementHandle, NULL);\
		++Preparecount;\
		CHECK_SQLITE_ERR(SqliteDbHandle,RetVal);\
		if (RetVal == SQLITE_OK) {\
			RetVal = sqlite3_step (StatementHandle);\
			if(RetVal==SQLITE_ROW)\
			{\
				Index = sqlite3_column_int (StatementHandle, 0);\
				/*PrintfNotice (" Index is 0 \n");*/\
			}\
			else \
			{\
				Index = -1;\
				/*PrintfNotice (" Index is -1 \n");*/\
			}\
			sqlite3_reset(StatementHandle);\
			sqlite3_finalize(StatementHandle);\
			--Preparecount;\
		}\
	}

#define	CREATE_INSERT_STATEMENT_FOR_SINGLE_PREPARE(type,statementbuf,tempString)		\
		switch (type) \
		{\
			case	1:\
			case	2:\
			case	3:\
			case	4:\
			case	5:\
				sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "? ,"); \
				break;\
			case	6:\
				sqlite3_snprintf (SQL_TEMP_STRING_LENGTH, tempString, "? ,"); \
				/*PrintfNotice("Rohit: Create Insert Statement for single prepare: %s", tempString);*/ \
				break;\
		}\
		strcat (statementbuf, tempString); \
