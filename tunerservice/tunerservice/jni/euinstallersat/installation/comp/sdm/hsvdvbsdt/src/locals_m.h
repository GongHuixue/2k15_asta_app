#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <Sdt_ParserDef.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define	INVALID_REGION_DEPTH				(0xFFFF)

#define SDT_PID_VALUE                      (0x0011)

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define HSV_INVALID_TSID                   (0xFFFF)

#define HSV_INVALID_ONID                   (0xFFFF)

#define HSV_INVALID_SERVICE                (0xFFFF)

#define HSV_INVALID_TABLE_ID               (-1)

#define SDT_ACTUAL_TABLE_ID                (0x42) 

#define SDT_OTHER_TABLE_ID                (0x46) 

#define MAX_SECTIONS	(2)

#define SDT_ACTUAL_INDEX (0)

#define SDT_OTHER_INDEX  (1)

#define MAX_PROPERTIES	(2)

#define SDT_OTHER_COOKIE        (3)

#define CIP_PRIVATE_DATA_SPEC	(0x00000040)

#define SDT_ACTUAL_REQ						(0x1)

#define	SDT_OTHER_REQ						(0x2)

#define DMX_BUFFER_SIZE						(16 * 1024)

#define FILTER_DEPTH						(16)

#define INVALID_TABLEID	(-1)

#define MAX_DIGITURK_SERVICE_LEN			(21)

#define FREESAT_TUNNELLED_PID_INVALID      (0xFFFF)

#define FREESAT_PACKAGE_ID				(33)

/******************************FunctionDeclarations********************************/
/******************************Constants***************************/
//#define DP(x) 	printf x

#define DP(x)

/***********************Dynamics***********************************/
/*********************************
Data for a given dmx 
**********************************/

typedef struct _DemuxData
{            
    int                          TableIds          [MAX_PROPERTIES];
    Nat8                         Version           [MAX_SECTIONS];
    Nat32                        SubscrId          [MAX_SECTIONS];
    Nat32			            SectionInfo[MAX_SECTIONS];	
    Nat16                        TsId;
    Nat16                        OtherTsId;
    Nat16                        OtherONID;
    int                        OtherTsVersionNo;
    Nat16                        OriginalNetworkId ; 
    int                        TsVersionNo   ;
    HsvLinkageInfo               LinkageInfo   ;
    HsvSDTSection                SDTOtherSection;   
    Bool                         ActualSectionValid;
    Bool                         OtherSectionValid;
    Nat16                        ActualOnId;
    Nat16                        ActualSvcId;
	Nat8						 TablesReq;
	Nat8						 TablesRecvd;
	Bool 						 enabled;
}DemuxData;
#if 0

#endif

#ifndef __cplusplus

#endif

#define GETINDEX(p) (p - HsvdvbsdtFirstProperty - 1)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

DemuxData DmxData[HsvDmxLast];
static DemuxData s__DmxData[HsvDmxLast];
Nat8 ModeArray[FILTER_DEPTH];
static Nat8 s__ModeArray[FILTER_DEPTH];
Nat8 MatchArray[FILTER_DEPTH];
static Nat8 s__MatchArray[FILTER_DEPTH];
Nat8 MaskArray[FILTER_DEPTH];
static Nat8 s__MaskArray[FILTER_DEPTH];
Nat8 mBuffer[16*1024];
static Nat8 s__mBuffer[16*1024];
#if 0

#endif

Bool mIsSDTClearNeeded ();
#ifndef __cplusplus

#endif

Bool ipop_PopulateSDT ( HsvDemux dmx , Address pSdt_Parser, int code, Nat32 cookie );
void InitTSID(HsvDemux dmx);
void InitONID(HsvDemux dmx);
void InitTSVersionNumber(HsvDemux dmx);
void InitSDTSection(HsvDemux dmx);
void InitOtherSDTSection(HsvDemux dmx);
void InitLinkageInfo(HsvDemux dmx);
void InitOtherTSID(HsvDemux dmx);
void InitOtherONID(HsvDemux dmx);
void InitOtherTSVersionNumber(HsvDemux dmx);
void InitOtherSDTSectionServices(HsvDemux dmx);
Bool PopulateTSID(HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
Bool PopulateONID( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
Bool PopulateTSVersionNumber( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
Bool PopulateSDTSection( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
Bool PopulateOtherSDTSection( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
Bool PopulateServiceDescriptionSection(HsvDemux dmx, TypeSdt_Parser *ServiceTable, int Ppty, int tableid, int code);
Bool PopulateOtherServiceDescriptionSection(HsvDemux dmx, TypeSdt_Parser *ServiceTable, int Ppty, int tableid, int code);
void AssignServiceDescriptor(TypeSdt_Parser *ServiceTable, int tsloop, int i, HsvSDTSection *DbaseVersion);
inline void AssignCipDesc(TypeSdt_Parser* ServiceTable,int tsloop, int i, HsvSDTSection *DbaseVersion);
Bool PopulateLinkageInfo ( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
void mQuickPopulateOtherSDTSectionServices(HsvDemux dmx, TypeSdt_Parser* ServiceTable,  int code);
Bool PopulateLinkageInfoPrivate (HsvDemux dmx, TypeSdt_Parser *ServiceTable, int Ppty, int tableid, int code);
Nat32 mInterpretCountryCode( Nat32 country );
Bool Sdt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxData,(void*)s__DmxData,sizeof(DmxData));
	memcpy((void*)ModeArray,(void*)s__ModeArray,sizeof(ModeArray));
	memcpy((void*)MatchArray,(void*)s__MatchArray,sizeof(MatchArray));
	memcpy((void*)MaskArray,(void*)s__MaskArray,sizeof(MaskArray));
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
#if 0

#endif

#ifndef __cplusplus

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
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
#ifdef INVALID_REGION_DEPTH
#undef INVALID_REGION_DEPTH
#endif //INVALID_REGION_DEPTH
#ifdef SDT_PID_VALUE
#undef SDT_PID_VALUE
#endif //SDT_PID_VALUE
#ifdef HSV_INVALID_NETWORKID
#undef HSV_INVALID_NETWORKID
#endif //HSV_INVALID_NETWORKID
#ifdef HSV_INVALID_TSID
#undef HSV_INVALID_TSID
#endif //HSV_INVALID_TSID
#ifdef HSV_INVALID_ONID
#undef HSV_INVALID_ONID
#endif //HSV_INVALID_ONID
#ifdef HSV_INVALID_SERVICE
#undef HSV_INVALID_SERVICE
#endif //HSV_INVALID_SERVICE
#ifdef HSV_INVALID_TABLE_ID
#undef HSV_INVALID_TABLE_ID
#endif //HSV_INVALID_TABLE_ID
#ifdef SDT_ACTUAL_TABLE_ID
#undef SDT_ACTUAL_TABLE_ID
#endif //SDT_ACTUAL_TABLE_ID
#ifdef SDT_OTHER_TABLE_ID
#undef SDT_OTHER_TABLE_ID
#endif //SDT_OTHER_TABLE_ID
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef SDT_ACTUAL_INDEX
#undef SDT_ACTUAL_INDEX
#endif //SDT_ACTUAL_INDEX
#ifdef SDT_OTHER_INDEX
#undef SDT_OTHER_INDEX
#endif //SDT_OTHER_INDEX
#ifdef MAX_PROPERTIES
#undef MAX_PROPERTIES
#endif //MAX_PROPERTIES
#ifdef SDT_OTHER_COOKIE
#undef SDT_OTHER_COOKIE
#endif //SDT_OTHER_COOKIE
#ifdef CIP_PRIVATE_DATA_SPEC
#undef CIP_PRIVATE_DATA_SPEC
#endif //CIP_PRIVATE_DATA_SPEC
#ifdef SDT_ACTUAL_REQ
#undef SDT_ACTUAL_REQ
#endif //SDT_ACTUAL_REQ
#ifdef SDT_OTHER_REQ
#undef SDT_OTHER_REQ
#endif //SDT_OTHER_REQ
#ifdef DMX_BUFFER_SIZE
#undef DMX_BUFFER_SIZE
#endif //DMX_BUFFER_SIZE
#ifdef FILTER_DEPTH
#undef FILTER_DEPTH
#endif //FILTER_DEPTH
#ifdef INVALID_TABLEID
#undef INVALID_TABLEID
#endif //INVALID_TABLEID
#ifdef MAX_DIGITURK_SERVICE_LEN
#undef MAX_DIGITURK_SERVICE_LEN
#endif //MAX_DIGITURK_SERVICE_LEN
#ifdef DP(x)
#undef DP(x)
#endif //DP(x)
#ifdef GETINDEX(p)
#undef GETINDEX(p)
#endif //GETINDEX(p)
#endif //LOCAL_UNDEFINES
