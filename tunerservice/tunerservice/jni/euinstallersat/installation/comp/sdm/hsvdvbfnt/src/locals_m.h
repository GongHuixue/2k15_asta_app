#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <fnt_parser.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define FNT_INDEX			(0)

#define MAX_SECTIONS        (2)

#define FNT_REQ				(0x1)

#define FNT_TABLE_ID        (0xBC)

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define INVALID_PID         (0x1FFF)

#define  POLARIZATION_HORIZANTAL	(0)

#define  POLARIZATION_VERTICAL		(1)

#define MODULATION_STD_DVBS		(1)

#define MODULATION_STD_DVBS2	(2)

#define  MOD_TYPE_AUTO	(0)

#define  MOD_TYPE_QPSK	(1)

#define  MOD_TYPE_8PSK	(2)

#define  MOD_TYPE_16QAM	(3)

struct DmxRomDataStruct
{            
    Nat8                         Version           [MAX_SECTIONS];
    Nat32                        SubscrId          [MAX_SECTIONS];
    Nat32						 SectionInfo	   [MAX_SECTIONS];
    Nat16                        NetworkId         ;
	Nat8						 FNTAvail;
	Nat8						 TablesReq;
    Nat8                         FNTVer;
    Nat16                        NetworkName       [MAX_NETWORK_NAME_SIZE];
};
#ifndef __cplusplus

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

struct DmxRomDataStruct DmxROMData[HsvDmxLast];
static struct DmxRomDataStruct s__DmxROMData[HsvDmxLast];
Nat8 mBuffer[16*1024];
static Nat8 s__mBuffer[16*1024];
#ifndef __cplusplus

#endif

Bool ipop_PopulateFNT( HsvDemux dmx , Address fnt_parser, int code );
void InitSatelliteDS(HsvDemux dmx);
void InitActualNetworkID(HsvDemux dmx);
void InitNetworkName(HsvDemux dmx);
void InitFNTVer(HsvDemux dmx);
void InitLCN(HsvDemux dmx);
void InitServiceListDS(HsvDemux dmx);
Bool PopulateNetworkName(HsvDemux dmx, Typefnt_parser *NetWkTable,  int code);
Bool PopulateNetworkSDSD(HsvDemux dmx, Typefnt_parser *NetWkTable, int code);
Bool PopulateServiceListDS ( HsvDemux dmx, Typefnt_parser *NetWkTable,  int code);
Bool PopulateLogicalChannel ( HsvDemux dmx, Typefnt_parser *NetWkTable,  int code);
int ConvertBcdToDecimal (int bcdvalue);
int MapModulationType (Nat8 modln);
Nat8 MapPolarization (Nat8 pol);
int MapModulationStd (Nat8 modlnstd);
int M7GetLCNValue(Nat8* ptr, int num);
Bool Fnt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxROMData,(void*)s__DmxROMData,sizeof(DmxROMData));
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
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
#ifdef FNT_INDEX
#undef FNT_INDEX
#endif //FNT_INDEX
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef FNT_REQ
#undef FNT_REQ
#endif //FNT_REQ
#ifdef FNT_TABLE_ID
#undef FNT_TABLE_ID
#endif //FNT_TABLE_ID
#ifdef HSV_INVALID_NETWORKID
#undef HSV_INVALID_NETWORKID
#endif //HSV_INVALID_NETWORKID
#ifdef INVALID_PID
#undef INVALID_PID
#endif //INVALID_PID
#ifdef POLARIZATION_HORIZANTAL
#undef POLARIZATION_HORIZANTAL
#endif //POLARIZATION_HORIZANTAL
#ifdef POLARIZATION_VERTICAL
#undef POLARIZATION_VERTICAL
#endif //POLARIZATION_VERTICAL
#ifdef MODULATION_STD_DVBS
#undef MODULATION_STD_DVBS
#endif //MODULATION_STD_DVBS
#ifdef MODULATION_STD_DVBS2
#undef MODULATION_STD_DVBS2
#endif //MODULATION_STD_DVBS2
#ifdef MOD_TYPE_AUTO
#undef MOD_TYPE_AUTO
#endif //MOD_TYPE_AUTO
#ifdef MOD_TYPE_QPSK
#undef MOD_TYPE_QPSK
#endif //MOD_TYPE_QPSK
#ifdef MOD_TYPE_8PSK
#undef MOD_TYPE_8PSK
#endif //MOD_TYPE_8PSK
#ifdef MOD_TYPE_16QAM
#undef MOD_TYPE_16QAM
#endif //MOD_TYPE_16QAM
#endif //LOCAL_UNDEFINES
