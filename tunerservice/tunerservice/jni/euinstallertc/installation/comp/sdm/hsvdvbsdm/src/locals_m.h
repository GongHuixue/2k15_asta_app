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

#define	SDM_ACTION_TABLE_ENTRIES	(5)

#define DVB_SI_ENABLED       (eurdiv_GetDVBTMode() != eurdiv_ScanDVBTMpegOnly) || (ins_Cable == ins_GetMedium())

/*****************************************************************************/
// contains defines for within

#define hsvdmx_dmxsecfN_iPresent( )	((int)0x1)

#define hsvdmx_dmxsecfN_iPresent_CONSTANT	0x1

//#define hsvmpeg_ctrlN_iPresent( )	((int)0x1)
//#define hsvmpeg_ctrlN_iPresent_CONSTANT	0x1

#define hsvmpeg_mpegsecnN_iPresent( )	((int)0x1)

#define hsvmpeg_mpegsecnN_iPresent_CONSTANT	0x1

#define hsvdvbsi_ctrlN_iPresent( )	((int)0x1)

#define hsvdvbsi_ctrlN_iPresent_CONSTANT	0x1

#define hsvdmx_hsvdmxN_iPresent( )	((int)0x1)

#define hsvdmx_hsvdmxN_iPresent_CONSTANT	0x1

#define hsvmpeg_std_ICONNECTED	1

#define hsvmpeg_std_StandardATSC	((int)0x0)

#define hsvmpeg_std_StandardATSC_CONSTANT	0x0

#define hsvmpeg_std_StandardDVB	((int)0x1)

#define hsvmpeg_std_StandardDVB_CONSTANT	0x1

/*****************************************************************************/

#define div_SdmWaitTime 10

#define div_DataCollectionTimeout div_SdmWaitTime

#define pen_PumpEngine 0

#define ctrlpen_PumpEngine 0

struct SdmDemux_t
{
    int Mode;               
    int Status;             
    int WorkingStatus;
};
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
}HsvSdmEvents;
struct StreamFilterValues_t {
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

struct SdmDemux_t SdmDemux[HsvDmxLast];
static struct SdmDemux_t s__SdmDemux[HsvDmxLast];
int Actions[SDM_ACTION_TABLE_ENTRIES];
static int s__Actions[SDM_ACTION_TABLE_ENTRIES];
struct StreamFilterValues_t StreamFilterValues[HsvDmxLast];
static struct StreamFilterValues_t s__StreamFilterValues[HsvDmxLast];
Pump ControlPump;
static Pump s__ControlPump;
Pump NoDataPump;
static Pump s__NoDataPump;
Pump SyncPump;
static Pump s__SyncPump;
int conf_CurrentCountry;
static int s__conf_CurrentCountry;
void SdmControlEventHandler( int dmx, Nat32 eventmask );
void SdmNoDataAvailableHandler( int dmx, Nat32 eventmask);
void SdmSyncHandler( int dmx, Nat32 eventmask);
void SyncFilter(HsvDemux dmx);
void InitializeTables( HsvDemux dmx );
int MapCountry( int cntry );
void module__init(void){
#ifdef WIN32

#else

#endif

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
#ifdef SDM_ACTION_TABLE_ENTRIES
#undef SDM_ACTION_TABLE_ENTRIES
#endif //SDM_ACTION_TABLE_ENTRIES
#ifdef DVB_SI_ENABLED
#undef DVB_SI_ENABLED
#endif //DVB_SI_ENABLED
#ifdef hsvdmx_dmxsecfN_iPresent(
#undef hsvdmx_dmxsecfN_iPresent(
#endif //hsvdmx_dmxsecfN_iPresent(
#ifdef hsvdmx_dmxsecfN_iPresent_CONSTANT
#undef hsvdmx_dmxsecfN_iPresent_CONSTANT
#endif //hsvdmx_dmxsecfN_iPresent_CONSTANT
#ifdef hsvmpeg_mpegsecnN_iPresent(
#undef hsvmpeg_mpegsecnN_iPresent(
#endif //hsvmpeg_mpegsecnN_iPresent(
#ifdef hsvmpeg_mpegsecnN_iPresent_CONSTANT
#undef hsvmpeg_mpegsecnN_iPresent_CONSTANT
#endif //hsvmpeg_mpegsecnN_iPresent_CONSTANT
#ifdef hsvdvbsi_ctrlN_iPresent(
#undef hsvdvbsi_ctrlN_iPresent(
#endif //hsvdvbsi_ctrlN_iPresent(
#ifdef hsvdvbsi_ctrlN_iPresent_CONSTANT
#undef hsvdvbsi_ctrlN_iPresent_CONSTANT
#endif //hsvdvbsi_ctrlN_iPresent_CONSTANT
#ifdef hsvdmx_hsvdmxN_iPresent(
#undef hsvdmx_hsvdmxN_iPresent(
#endif //hsvdmx_hsvdmxN_iPresent(
#ifdef hsvdmx_hsvdmxN_iPresent_CONSTANT
#undef hsvdmx_hsvdmxN_iPresent_CONSTANT
#endif //hsvdmx_hsvdmxN_iPresent_CONSTANT
#ifdef hsvmpeg_std_ICONNECTED
#undef hsvmpeg_std_ICONNECTED
#endif //hsvmpeg_std_ICONNECTED
#ifdef hsvmpeg_std_StandardATSC
#undef hsvmpeg_std_StandardATSC
#endif //hsvmpeg_std_StandardATSC
#ifdef hsvmpeg_std_StandardATSC_CONSTANT
#undef hsvmpeg_std_StandardATSC_CONSTANT
#endif //hsvmpeg_std_StandardATSC_CONSTANT
#ifdef hsvmpeg_std_StandardDVB
#undef hsvmpeg_std_StandardDVB
#endif //hsvmpeg_std_StandardDVB
#ifdef hsvmpeg_std_StandardDVB_CONSTANT
#undef hsvmpeg_std_StandardDVB_CONSTANT
#endif //hsvmpeg_std_StandardDVB_CONSTANT
#ifdef div_SdmWaitTime
#undef div_SdmWaitTime
#endif //div_SdmWaitTime
#ifdef div_DataCollectionTimeout
#undef div_DataCollectionTimeout
#endif //div_DataCollectionTimeout
#ifdef pen_PumpEngine
#undef pen_PumpEngine
#endif //pen_PumpEngine
#ifdef ctrlpen_PumpEngine
#undef ctrlpen_PumpEngine
#endif //ctrlpen_PumpEngine
#ifdef HSV_MAKE_CHAR_MASK(a,b,c)
#undef HSV_MAKE_CHAR_MASK(a,b,c)
#endif //HSV_MAKE_CHAR_MASK(a,b,c)
#endif //LOCAL_UNDEFINES
