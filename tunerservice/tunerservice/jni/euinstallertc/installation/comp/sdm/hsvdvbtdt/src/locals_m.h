#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <Tdt_ParserDef.h>

#define TDT_PID_VALUE                   (0x14)

#define HSV_INVALID_VERSION (-1)

#define MAX_SECTIONS    (2)

#define MAX_PROPERTIES  (2)

#define TDT_TABLE_ID                (0x70) 

#define TDT_INDEX (0)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)


/******************************FunctionDeclarations********************************/

/******************************Constants***************************/


/***********************Dynamics***********************************/
/*********************************
  Data for a given dmx 
 **********************************/

struct _DmxData
{            
    Nat32                        SubscrId;
    HsvDateTime                  dt;
    Nat32           SectionInfo[MAX_SECTIONS];          
};
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

struct _DmxData DmxData[HsvDmxLast];
static struct _DmxData s__DmxData[HsvDmxLast];
Bool ipop_PopulateTDT ( HsvDemux   dmx, Address pTdt_Parser, int code );
void InitDateTime(HsvDemux dmx);
Bool PopulateTimeDate ( HsvDemux dmx, TypeTdt_Parser* TimeDateTable, int Ppty, int tableid, int code);
void IncrementVersion (int *version);
Nat8 mBuffer[4*1024];
static Nat8 s__mBuffer[4*1024];
Bool Tdt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
int GetDescriptorIDOntdt( int descriptor_tag, int cookie );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxData,(void*)s__DmxData,sizeof(DmxData));
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef TDT_PID_VALUE
#undef TDT_PID_VALUE
#endif //TDT_PID_VALUE
#ifdef HSV_INVALID_VERSION
#undef HSV_INVALID_VERSION
#endif //HSV_INVALID_VERSION
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef MAX_PROPERTIES
#undef MAX_PROPERTIES
#endif //MAX_PROPERTIES
#ifdef TDT_TABLE_ID
#undef TDT_TABLE_ID
#endif //TDT_TABLE_ID
#ifdef TDT_INDEX
#undef TDT_INDEX
#endif //TDT_INDEX
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
#endif //LOCAL_UNDEFINES
