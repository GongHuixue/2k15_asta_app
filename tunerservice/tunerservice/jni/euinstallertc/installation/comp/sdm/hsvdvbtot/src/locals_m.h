#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <Tot_ParserDef.h>
//#include "Parser.h"

#define TOT_PID_VALUE                   (0x14)

#define HSV_INVALID_TABLE_ID (-1)

#define HSV_INVALID_VERSION (-1)

#define MAX_SECTIONS    (2)

#define MAX_PROPERTIES  (2)

#define TOT_TABLE_ID                (0x73) 

#define TOT_INDEX (0)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

/******************************FunctionDeclarations********************************/
//#define DP(x)     printf x
//#define DP(x)     printf x

#define DP(x)

/******************************Constants***************************/
/***********************Dynamics***********************************/
/*********************************
  Data for a given dmx 
 **********************************/

struct _DmxData
{            
    int                          TableIds          [MAX_PROPERTIES];
    Nat32                        SubscrId;
    Nat32           SectionInfo[MAX_SECTIONS];      
    HsvDateTime                  dt;
};
#ifdef __cplusplus

#else

#endif

#define GETINDEX(p) (p - HsvdvbtotFirstProperty - 1)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

struct _DmxData DmxData[HsvDmxLast];
static struct _DmxData s__DmxData[HsvDmxLast];
#ifdef __cplusplus

#else

#endif

Bool ipop_PopulateTOT ( HsvDemux dmx , Address pTot_Parser, int code );
void InitTimeDate(HsvDemux dmx);
void InitTimeOffset(HsvDemux dmx);
Bool PopulateDateTime (HsvDemux dmx, TypeTot_Parser* TimeOffsetTable,  int code);
Bool PopulateTimeOffset (HsvDemux dmx, TypeTot_Parser* TimeOffsetTable,  int code);
Bool PopulateTimeOffsetprivate ( HsvDemux dmx, TypeTot_Parser* TimeOffsetTable, int Ppty, int tableid, int code);
Nat32 mInterpretCountryCode( Nat32 country );
void IncrementVersion (int *version);
Nat8 mBuffer[4*1024];
static Nat8 s__mBuffer[4*1024];
Bool Tot_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
int GetDescriptorIDOntot( int descriptor_tag, int cookie );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxData,(void*)s__DmxData,sizeof(DmxData));
#ifdef __cplusplus

#else

#endif

	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef TOT_PID_VALUE
#undef TOT_PID_VALUE
#endif //TOT_PID_VALUE
#ifdef HSV_INVALID_TABLE_ID
#undef HSV_INVALID_TABLE_ID
#endif //HSV_INVALID_TABLE_ID
#ifdef HSV_INVALID_VERSION
#undef HSV_INVALID_VERSION
#endif //HSV_INVALID_VERSION
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef MAX_PROPERTIES
#undef MAX_PROPERTIES
#endif //MAX_PROPERTIES
#ifdef TOT_TABLE_ID
#undef TOT_TABLE_ID
#endif //TOT_TABLE_ID
#ifdef TOT_INDEX
#undef TOT_INDEX
#endif //TOT_INDEX
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
#ifdef DP(x)
#undef DP(x)
#endif //DP(x)
#ifdef GETINDEX(p)
#undef GETINDEX(p)
#endif //GETINDEX(p)
#endif //LOCAL_UNDEFINES
