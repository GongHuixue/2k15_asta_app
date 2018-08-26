#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define HSV_CREATE_EVENT_MASK( event, mode )     ( ((event)<<16) | ((mode) & 0xFFFF) )

#define HSV_GET_EVENT( eventmask )               ( ((eventmask) >> 16 ) & (0xFFFF) )

#define HSV_INVALID_FILTER_VALUE                 (-1)

#define RESET_BIT(a) (~SET_BIT(a))

#define SET_BIT(a)   (0x1 << (a))

#define PROCESS_MESSAGE  (0)

#define IGNORE_MESSAGE   (1)

#ifdef WIN32

#define TARGET_CORRECTION (1)

#else

#define TARGET_CORRECTION (1)

#endif

#define INVALID_TABLEID		(-1)

#define DVB_SI_ENABLED		1

#define M7_TIMEOUT			(15000)		//msec

#define CANAL_SDTOTHER_TIMEOUT			(10000)		//msec

#define NTVPLUS_SDTOTHER_TIMEOUT (30000)

#define N_SDTOTHER_TIMEOUT             (30000) //msec

#define SDT_OTHER_TABLE_ID                (0x46) 

#define FRANSAT_SDTOTHER_TIMEOUT	30000

#define FRANSAT_DATA_ACQ_TIMEOUT			(20000)		//msec

#define SGT_TIMEOUT		(15000)

#define FREESAT_NORMAL_TIMEOUT			(30000)		//msec
#define FREESAT_NORMAL_PLUS_PMT_TIMEOUT			(30000)//(20000)		//msec
#define FREESAT_POSTCODE_TIMEOUT			(70000)		//msec
#define CHECK_ALL_TABLE(x) ((x&(SDT_AVAILABLE|NIT_AVAILABLE|BAT_AVAILABLE)) == (SDT_AVAILABLE|NIT_AVAILABLE|BAT_AVAILABLE))

#define IS_FRANSAT_PACKAGE(x) (((x & 0xFFFF) == FRANSAT_PACKAGE_ID) ? TRUE : FALSE)

typedef enum
{
	SDT_AVAILABLE = 0x1,
	NIT_AVAILABLE = 0x2,
	BAT_AVAILABLE = 0x4,
	SIMPLEPAT_AVAILABLE = 0x8,
	SIMPLEPMT_AVAILABLE = 0x10
}TableStatus;
struct SdmDemuxStruct
{
    int Mode;               /* Denotes the mode in which the demux was started */
    int Status;             /* Denotes the status of data collection           */
	int WorkingStatus;
	int	PmtCollectedStatus;	/* Denotes the status of PMT Collection				*/
	int TablesCollectionStatus ; /* SDT + NIT + BAT table status */
};

#define		NUM_SDM_COLLECTION_MODES	21


/* This array is required to determine if a particular action is allowed, as requested by the
   function in the IHsvDVBSIConfig interface. The order in which the elements are defined in this 
   array is closely coupled with the values of the constants in IHsvDVBSIConfig*/

typedef enum 
{
    evHsvSdmStart,
    evHsvSdmNoDataAvailable,    
    evHsvSdmDemuxSyncLock,
    evHsvSdmSyncComponents,
    evHsvSdmSDTAvailable,
    evHsvSdmNITAvailable,
    evHsvSdmStop,
    evHsvSdmDmxStarted,
    evHsvSdmDmxStopped,
	evHsvSdmSIMPLEPATAvailable,
	evHsvSdmSIMPLEPMTAvailable,
	evHsvSdmBatAvailable,
	evHsvSdmFNTAvailable,
	evHsvSdmFSTAvailable,
	evHsvSdmSGTAvailable,
	evHsvSdmMPEGStopped,
	evHsvSdmPostcodeAvailable,
	evHsvSdmTOTAvailable
}HsvSdmEvents;
struct StreamFilterTypesStruct{
    int StartMode;       
    int CurrentCountry;  
    int CurrentLanguage; 
    int CurrentProgram;  
    int ExtraProgram;    
    int OtherSDTOnwidId; 
    int OtherSDTServiceId;
    int WaitingFor;
    int ExtraProgram0;
    int ExtraProgram1;
    int ExtraProgram2;
    int ExtraProgram3;
    int ExtraProgram4;
    int ExtraProgram5;
    int ActualEitScheduleService;
    int OtherEitScheduleService;
    int ExtendedInfoEventId;
    int ExtendedInfoONId;
	int ExtendedInfoTsId;
    int ExtendedInfoSerId;
    int ShortDescEventId;
    int ShortDescONId;
	int ShortDescTsId;
    int ShortDescSerId;
};
#define HSV_MAKE_CHAR_MASK(a,b,c)           ( ((((Nat32)(a))<<16) ) | (((Nat32)(b))<<8) | (((Nat32)(c))) )

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifdef WIN32

#else

#endif

int mPackageSelected;
static int s__mPackageSelected;
struct SdmDemuxStruct SdmDemux[HsvDmxLast];
static struct SdmDemuxStruct s__SdmDemux[HsvDmxLast];
int Actions[NUM_SDM_COLLECTION_MODES];
static int s__Actions[NUM_SDM_COLLECTION_MODES];
struct StreamFilterTypesStruct StreamFilterValues [HsvDmxLast];
static struct StreamFilterTypesStruct s__StreamFilterValues [HsvDmxLast];
Pump ControlPump;
static Pump s__ControlPump;
Pump NoDataPump;
static Pump s__NoDataPump;
Pump SyncPump;
static Pump s__SyncPump;
int conf_CurrentCountry;
static int s__conf_CurrentCountry;
void SdmControlEventHandler( int dmxval, Nat32 eventmask );
void SdmNoDataAvailableHandler( int dmx, Nat32 eventmask);
void SdmSyncHandler( int dmx, Nat32 eventmask);
void SyncFilter(HsvDemux dmx);
void InitializeTables( HsvDemux dmx );
int MapCountry( int cntry );
int getTimeOut(void);
void module__init(void){
#ifdef WIN32

#else

#endif

	mPackageSelected	=	s__mPackageSelected;
	memcpy((void*)SdmDemux,(void*)s__SdmDemux,sizeof(SdmDemux));
	memcpy((void*)Actions,(void*)s__Actions,sizeof(Actions));
	memcpy((void*)StreamFilterValues,(void*)s__StreamFilterValues,sizeof(StreamFilterValues));
	ControlPump	=	s__ControlPump;
	NoDataPump	=	s__NoDataPump;
	SyncPump	=	s__SyncPump;
	conf_CurrentCountry	=	s__conf_CurrentCountry;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef HSV_CREATE_EVENT_MASK(
#undef HSV_CREATE_EVENT_MASK(
#endif //HSV_CREATE_EVENT_MASK(
#ifdef HSV_GET_EVENT(
#undef HSV_GET_EVENT(
#endif //HSV_GET_EVENT(
#ifdef HSV_INVALID_FILTER_VALUE
#undef HSV_INVALID_FILTER_VALUE
#endif //HSV_INVALID_FILTER_VALUE
#ifdef RESET_BIT(a)
#undef RESET_BIT(a)
#endif //RESET_BIT(a)
#ifdef SET_BIT(a)
#undef SET_BIT(a)
#endif //SET_BIT(a)
#ifdef PROCESS_MESSAGE
#undef PROCESS_MESSAGE
#endif //PROCESS_MESSAGE
#ifdef IGNORE_MESSAGE
#undef IGNORE_MESSAGE
#endif //IGNORE_MESSAGE
#ifdef TARGET_CORRECTION
#undef TARGET_CORRECTION
#endif //TARGET_CORRECTION
#ifdef TARGET_CORRECTION
#undef TARGET_CORRECTION
#endif //TARGET_CORRECTION
#ifdef INVALID_TABLEID
#undef INVALID_TABLEID
#endif //INVALID_TABLEID
#ifdef DVB_SI_ENABLED
#undef DVB_SI_ENABLED
#endif //DVB_SI_ENABLED
#ifdef M7_TIMEOUT
#undef M7_TIMEOUT
#endif //M7_TIMEOUT
#ifdef CANAL_SDTOTHER_TIMEOUT
#undef CANAL_SDTOTHER_TIMEOUT
#endif //CANAL_SDTOTHER_TIMEOUT
#ifdef NTVPLUS_SDTOTHER_TIMEOUT
#undef NTVPLUS_SDTOTHER_TIMEOUT
#endif //NTVPLUS_SDTOTHER_TIMEOUT
#ifdef N_SDTOTHER_TIMEOUT
#undef N_SDTOTHER_TIMEOUT
#endif //N_SDTOTHER_TIMEOUT
#ifdef SDT_OTHER_TABLE_ID
#undef SDT_OTHER_TABLE_ID
#endif //SDT_OTHER_TABLE_ID
#ifdef FRANSAT_SDTOTHER_TIMEOUT
#undef FRANSAT_SDTOTHER_TIMEOUT
#endif //FRANSAT_SDTOTHER_TIMEOUT
#ifdef FRANSAT_DATA_ACQ_TIMEOUT
#undef FRANSAT_DATA_ACQ_TIMEOUT
#endif //FRANSAT_DATA_ACQ_TIMEOUT
#ifdef CHECK_ALL_TABLE(x)
#undef CHECK_ALL_TABLE(x)
#endif //CHECK_ALL_TABLE(x)
#ifdef IS_FRANSAT_PACKAGE(x)
#undef IS_FRANSAT_PACKAGE(x)
#endif //IS_FRANSAT_PACKAGE(x)
#ifdef NUM_SDM_COLLECTION_MODES
#undef NUM_SDM_COLLECTION_MODES
#endif //NUM_SDM_COLLECTION_MODES
#ifdef HSV_MAKE_CHAR_MASK(a,b,c)
#undef HSV_MAKE_CHAR_MASK(a,b,c)
#endif //HSV_MAKE_CHAR_MASK(a,b,c)
#endif //LOCAL_UNDEFINES
