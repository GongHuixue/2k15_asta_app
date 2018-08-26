#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <fst_parser.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define FST_PID_VALUE                      (0x0011)

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define HSV_INVALID_TSID                   (0xFFFF)

#define HSV_INVALID_ONID                   (0xFFFF)

#define HSV_INVALID_SERVICE                (0xFFFF)

#define INVALID_PID         			   (0x1FFF)

#define MAX_SECTIONS	(2)

#define FST_INDEX (0)

#define MAX_PROPERTIES	(2)

#define DMX_BUFFER_SIZE						(32 * 1024)

#define FILTER_DEPTH						(16)

#define FST_REQ				(0x1)

#define FST_TABLE_ID        (0xBD)

/******************************FunctionDeclarations********************************/
/******************************Constants***************************/
//#define DP(x) 	printf x

#define DP(x)

/***********************Dynamics***********************************/
/*********************************
Data for a given dmx 
**********************************/

struct DmxRomDataStruct
{            
    Nat8                         Version           [MAX_SECTIONS];
    Nat32                        SubscrId          [MAX_SECTIONS];
    Nat32						 SectionInfo	   [MAX_SECTIONS];
    Nat16                        NetworkId;
	Nat8						 FstAvail;
    Nat8                         FstVer;
    
};
#define GETINDEX(p) (p - HsvdvbfstFirstProperty - 1)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

struct DmxRomDataStruct DmxROMData[HsvDmxLast];
static struct DmxRomDataStruct s__DmxROMData[HsvDmxLast];
Nat8 mBuffer[16*1024];
static Nat8 s__mBuffer[16*1024];
Nat8 ModeArray[FILTER_DEPTH];
static Nat8 s__ModeArray[FILTER_DEPTH];
Nat8 MatchArray[FILTER_DEPTH];
static Nat8 s__MatchArray[FILTER_DEPTH];
Nat8 MaskArray[FILTER_DEPTH];
static Nat8 s__MaskArray[FILTER_DEPTH];

void InitFst(HsvDemux dmx);
void InitFstVer(HsvDemux dmx);
void InitNetworkID(HsvDemux dmx);
Bool ipop_PopulateFST ( HsvDemux dmx , Address pFst_Parser, int code);
void InitfstSection(HsvDemux dmx);
Bool PopulatefstSection( HsvDemux dmx, Typefst_parser *ServiceTable,  int code);
Bool PopulateServiceDescriptionSection(HsvDemux dmx, Typefst_parser *ServiceTable, int Ppty, int tableid, int code);
void AssignServiceDescriptor(Typefst_parser *ServiceTable, int tsloop, int i, HsvfstSection *DbaseVersion);
Bool Fst_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxROMData,(void*)s__DmxROMData,sizeof(DmxROMData));
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
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
#ifdef FST_PID_VALUE
#undef FST_PID_VALUE
#endif //FST_PID_VALUE
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
#ifdef INVALID_PID
#undef INVALID_PID
#endif //INVALID_PID
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef FST_INDEX
#undef FST_INDEX
#endif //FST_INDEX
#ifdef MAX_PROPERTIES
#undef MAX_PROPERTIES
#endif //MAX_PROPERTIES
#ifdef DMX_BUFFER_SIZE
#undef DMX_BUFFER_SIZE
#endif //DMX_BUFFER_SIZE
#ifdef FILTER_DEPTH
#undef FILTER_DEPTH
#endif //FILTER_DEPTH
#ifdef FST_REQ
#undef FST_REQ
#endif //FST_REQ
#ifdef FST_TABLE_ID
#undef FST_TABLE_ID
#endif //FST_TABLE_ID
#ifdef DP(x)
#undef DP(x)
#endif //DP(x)
#ifdef GETINDEX(p)
#undef GETINDEX(p)
#endif //GETINDEX(p)
#endif //LOCAL_UNDEFINES
