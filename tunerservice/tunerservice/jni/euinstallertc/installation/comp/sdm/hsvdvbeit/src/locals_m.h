#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define EIT_SECFLTR_LIST_TIMEOUT           (100)

#define EIT_SECFLTR_LIST_LENGTH            (SECTION_FILTER_LIST_LENGTH)

#define EIT_SECTION_BUFFER_SIZE            (64 * 1024)

#define EIT_PID_VALUE                      (0x12)

#define HSV_INVALID_TABLE_ID               (-1)

#define HSV_INVALID_EVENT                  (0xFFFF)

#define INVALID_INDEX                       (-1)

#define HSV_INVALID_KEY                     (-1)

#define HSV_INVALID_FILTER_VALUE            (-1)

#define div_AcquireEITSchedule (0)

#define TABLEID_FIELD          (0)

#define MAX_EXTENDEDDESC_SIZE (4096)

#define CLEAR_DATA    {\
    DmxData[dmx].ValidTable                 = FALSE;\
    DmxData[dmx].ValidExtendedInfo          = FALSE;\
    DmxData[dmx].ValidExtendedInfoForNow    = FALSE;\
    DmxData[dmx].ValidExtendedInfoForNext   = FALSE;\
    DmxData[dmx].ValidShortDesc             = FALSE;\
    DmxData[dmx].RatingDesc.DataValid       = FALSE;\
    DmxData[dmx].ValidLinkageDesc           = FALSE;\
    LinkageInfoVersionNumber                = -1;\
}\


#define TRUE 1

#define FALSE 0

/* Add Win 32 correction for mode match mask settings to help dvptst demux */

#ifdef WIN32

#define TABLE_ID_EXTN_FIELD            (3)

#define SECTION_NUMBER_FIELD           (6)

#else

#define TABLE_ID_EXTN_FIELD            (1)

#define SECTION_NUMBER_FIELD           (4)

#endif

#define TABLEID_MASK                   (0xFF)

#define SECTION_NUMBER_MASK            (0xFF)

#define	iparconst_StartParsing  (0)

#define	iparconst_HeaderParsed (1)

#define	iparconst_DataParsed   (2)

#define	iparconst_CompletedParsing (3)


/* Cookies to identify descriptor postion */

#define LOOP0 0

#define LOOP1 1

#define	parconst_StartParsing  (0)

#define	parconst_HeaderParsed (1)

#define	parconst_DataParsed   (2)

#define	parconst_CompletedParsing (3)

#define MAX_EPG_SIZE  4097

#define EIT_8DAYS_DATA_NOTREQ(TableId) (((TableId == 0x51)||(TableId == 0x61))&& (mSubscribeEpg4to8days == FALSE))

#define EIT_OTHER_PF_DATA_NOTREQ(TableId) ((TableId == EIT_OTHER_PF_TABLEID)/*&&(sysset_GetSystemCountry() != cids_CountryChina)*/)

/***********************Dynamics***********************************/
/*Multifeed related declarations*/

#define  MULTI_FEED_LINKAGE_TYPE        0xB0

#define  EVENT_LINKAGE_TYPE             0x0D

#define  MAX_FEED_NAME                  16

#define MAX_SECTIONS (HsvdvbeitLastSection - 1)

#define MAX_PROPERTIES (HsvdvbeitLastProperty - HsvdvbeitFirstProperty - 1)

#define EIT_SCHED_ACTUAL4_INDEX (2)

#define EIT_SCHED_ACTUAL8_INDEX (5)

#define EIT_SCHED_OTHER4_INDEX (6)

#define EIT_SCHED_OTHER8_INDEX (7)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

/******************************FunctionDeclarations********************************/

struct DmxData_t
{            
    int                             TableIds          [MAX_PROPERTIES];
    Nat32                           SubscrId          [MAX_SECTIONS];
    Bool                            ValidTable;
    HsvParentalRatingDescription    RatingDesc        ;    /* Only rating for the current event stored */
    Bool                            ValidLinkageDesc;
    Bool                            ValidExtendedInfo;
    HsvExtendedEventInfo            ExtendedInfo;
    Bool                            ValidExtendedInfoForNow;
    HsvExtendedEventInfo            ExtendedInfoForNow;
    Bool                            ValidExtendedInfoForNext;
    HsvExtendedEventInfo            ExtendedInfoForNext;
    Bool                            ValidShortDesc;
    HsvEITShortDesc                 ShortDesc;
    Int8                            ShortEvtVersionNumber;
    Int8                            ExtEvtVersionNumber;
};
#define GETINDEX(p) (p - HsvdvbeitFirstProperty - 1)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifdef WIN32

#else

#endif

Nat8 EPGData[MAX_EPG_SIZE];
static Nat8 s__EPGData[MAX_EPG_SIZE];
#ifndef __cplusplus

#else

#endif

Bool mSubscribeEpg4to8days;
static Bool s__mSubscribeEpg4to8days;
Bool EitSchedParsingStarted;
static Bool s__EitSchedParsingStarted;
Bool EnableNowNextInfoReset;
static Bool s__EnableNowNextInfoReset;
int LinkageInfoVersionNumber;
static int s__LinkageInfoVersionNumber;
struct DmxData_t DmxData[HsvDmxLast];
static struct DmxData_t s__DmxData[HsvDmxLast];
Bool PopulateEIT ( HsvDemux dmx, HsvEITTable *EITTable, int code );
Bool PopulateEIT_PF ( HsvDemux   dmx, HsvEITTable *EITTable, int pptyindex, int secindex, int code);
Bool PopulateRating ( HsvDemux   dmx, HsvEITTable *EITTable, int pptyindex, int secindex, int code);
Bool PopulateLinkage ( HsvDemux   dmx, HsvEITTable *EITTable, int pptyindex, int secindex, int code);
void AssignContentDescriptor(HsvEITTable  *EITTable, int i, HsvEITSection *DbaseVersion);
void CopyEitData (Address dest, Address source);
Bool EITParser( HsvDestination   dest, Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifdef WIN32

#else

#endif

	memcpy((void*)EPGData,(void*)s__EPGData,sizeof(EPGData));
#ifndef __cplusplus

#else

#endif

	mSubscribeEpg4to8days	=	s__mSubscribeEpg4to8days;
	EitSchedParsingStarted	=	s__EitSchedParsingStarted;
	EnableNowNextInfoReset	=	s__EnableNowNextInfoReset;
	LinkageInfoVersionNumber	=	s__LinkageInfoVersionNumber;
	memcpy((void*)DmxData,(void*)s__DmxData,sizeof(DmxData));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef EIT_SECFLTR_LIST_TIMEOUT
#undef EIT_SECFLTR_LIST_TIMEOUT
#endif //EIT_SECFLTR_LIST_TIMEOUT
#ifdef EIT_SECFLTR_LIST_LENGTH
#undef EIT_SECFLTR_LIST_LENGTH
#endif //EIT_SECFLTR_LIST_LENGTH
#ifdef EIT_SECTION_BUFFER_SIZE
#undef EIT_SECTION_BUFFER_SIZE
#endif //EIT_SECTION_BUFFER_SIZE
#ifdef EIT_PID_VALUE
#undef EIT_PID_VALUE
#endif //EIT_PID_VALUE
#ifdef HSV_INVALID_TABLE_ID
#undef HSV_INVALID_TABLE_ID
#endif //HSV_INVALID_TABLE_ID
#ifdef HSV_INVALID_EVENT
#undef HSV_INVALID_EVENT
#endif //HSV_INVALID_EVENT
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef HSV_INVALID_KEY
#undef HSV_INVALID_KEY
#endif //HSV_INVALID_KEY
#ifdef HSV_INVALID_FILTER_VALUE
#undef HSV_INVALID_FILTER_VALUE
#endif //HSV_INVALID_FILTER_VALUE
#ifdef div_AcquireEITSchedule
#undef div_AcquireEITSchedule
#endif //div_AcquireEITSchedule
#ifdef TABLEID_FIELD
#undef TABLEID_FIELD
#endif //TABLEID_FIELD
#ifdef MAX_EXTENDEDDESC_SIZE
#undef MAX_EXTENDEDDESC_SIZE
#endif //MAX_EXTENDEDDESC_SIZE
#ifdef CLEAR_DATA
#undef CLEAR_DATA
#endif //CLEAR_DATA
#ifdef TRUE
#undef TRUE
#endif //TRUE
#ifdef FALSE
#undef FALSE
#endif //FALSE
#ifdef TABLE_ID_EXTN_FIELD
#undef TABLE_ID_EXTN_FIELD
#endif //TABLE_ID_EXTN_FIELD
#ifdef SECTION_NUMBER_FIELD
#undef SECTION_NUMBER_FIELD
#endif //SECTION_NUMBER_FIELD
#ifdef TABLE_ID_EXTN_FIELD
#undef TABLE_ID_EXTN_FIELD
#endif //TABLE_ID_EXTN_FIELD
#ifdef SECTION_NUMBER_FIELD
#undef SECTION_NUMBER_FIELD
#endif //SECTION_NUMBER_FIELD
#ifdef TABLEID_MASK
#undef TABLEID_MASK
#endif //TABLEID_MASK
#ifdef SECTION_NUMBER_MASK
#undef SECTION_NUMBER_MASK
#endif //SECTION_NUMBER_MASK
#ifdef iparconst_StartParsing
#undef iparconst_StartParsing
#endif //iparconst_StartParsing
#ifdef iparconst_HeaderParsed
#undef iparconst_HeaderParsed
#endif //iparconst_HeaderParsed
#ifdef iparconst_DataParsed
#undef iparconst_DataParsed
#endif //iparconst_DataParsed
#ifdef iparconst_CompletedParsing
#undef iparconst_CompletedParsing
#endif //iparconst_CompletedParsing
#ifdef LOOP0
#undef LOOP0
#endif //LOOP0
#ifdef LOOP1
#undef LOOP1
#endif //LOOP1
#ifdef parconst_StartParsing
#undef parconst_StartParsing
#endif //parconst_StartParsing
#ifdef parconst_HeaderParsed
#undef parconst_HeaderParsed
#endif //parconst_HeaderParsed
#ifdef parconst_DataParsed
#undef parconst_DataParsed
#endif //parconst_DataParsed
#ifdef parconst_CompletedParsing
#undef parconst_CompletedParsing
#endif //parconst_CompletedParsing
#ifdef MAX_EPG_SIZE
#undef MAX_EPG_SIZE
#endif //MAX_EPG_SIZE
#ifdef EIT_8DAYS_DATA_NOTREQ(TableId)
#undef EIT_8DAYS_DATA_NOTREQ(TableId)
#endif //EIT_8DAYS_DATA_NOTREQ(TableId)
#ifdef EIT_OTHER_PF_DATA_NOTREQ(TableId)
#undef EIT_OTHER_PF_DATA_NOTREQ(TableId)
#endif //EIT_OTHER_PF_DATA_NOTREQ(TableId)
#ifdef MULTI_FEED_LINKAGE_TYPE
#undef MULTI_FEED_LINKAGE_TYPE
#endif //MULTI_FEED_LINKAGE_TYPE
#ifdef EVENT_LINKAGE_TYPE
#undef EVENT_LINKAGE_TYPE
#endif //EVENT_LINKAGE_TYPE
#ifdef MAX_FEED_NAME
#undef MAX_FEED_NAME
#endif //MAX_FEED_NAME
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef MAX_PROPERTIES
#undef MAX_PROPERTIES
#endif //MAX_PROPERTIES
#ifdef EIT_SCHED_ACTUAL4_INDEX
#undef EIT_SCHED_ACTUAL4_INDEX
#endif //EIT_SCHED_ACTUAL4_INDEX
#ifdef EIT_SCHED_ACTUAL8_INDEX
#undef EIT_SCHED_ACTUAL8_INDEX
#endif //EIT_SCHED_ACTUAL8_INDEX
#ifdef EIT_SCHED_OTHER4_INDEX
#undef EIT_SCHED_OTHER4_INDEX
#endif //EIT_SCHED_OTHER4_INDEX
#ifdef EIT_SCHED_OTHER8_INDEX
#undef EIT_SCHED_OTHER8_INDEX
#endif //EIT_SCHED_OTHER8_INDEX
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#ifdef GETINDEX(p)
#undef GETINDEX(p)
#endif //GETINDEX(p)
#endif //LOCAL_UNDEFINES
