#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <Nit_ParserDef.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define div_MaxChannelsPerNetwork           (50)

#define NIT_PID_VALUE                       (0x10)

#define NIT_ACTUAL_TABLE_ID                (0x40)

#define NIT_OTHER_TABLE_ID                 (0x41)

#define NIT_ACTUAL_REQ						(0x1)

#define	NIT_OTHER_REQ						(0x2)
/* fixme: We need to debate on these values */

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define HSV_INVALID_CELLID                 (0xFFFF)

#define HSV_INVALID_TABLE_ID               (-1)

#define MAX_SECTIONS                        (2)

#define NITACTUAL_INDEX						(0)

#define NITOTHER_INDEX						(1)

#define FRANSAT_PACKAGE_ID          (31)

#define DP(x)

#define CURRENTTERRESTRIALCODINGTYPE 3

#define INVALID_REGION_CODE		0xFFFF

#define FREESAT_LINKAGE_DESCRIPTOR					(0xD2)

#define FREESAT_MAX_LINKAGE_SERVICE_COUNT 		(25)

/*According to Free Satellite Requirements for Interoperability Part 3: System Management V1.6 (Table 15)
**only 10  (0x00 to 0x08 & 0x0B) valid linkage type per service is available
**But as per descriptor syntax max value for tunnelled_type_loop_length  can be 248
**the below macro value should be modified if morethan 20 linkage type is found in field
*/
#define FREESAT_MAX_LINKAGE_TYPE_COUNT		(20)
// Nat32 *NetWkTable;
/*********************************
Data for a given dmx
**********************************/

struct _DmxROMData
{            
    Nat8                         Version           [MAX_SECTIONS];
    Nat32                        SubscrId          [MAX_SECTIONS];
    Nat32                        SectionInfo[MAX_SECTIONS];
    Nat16                        NetworkId         ;
    Nat8                         NITActualAvail;
    Nat8                         TablesReq;
    Nat8                         TablesRecvd;
    Nat8                         ActualNITVer;
    Nat16                        NetworkName       [MAX_NETWORK_NAME_SIZE];
};
#if 0

#endif

#define MAXCOUNTRY 36

#define DMX_BUFFER_SIZE (16 * 1024)

#define FILTER_DEPTH    (16)

#ifndef __cplusplus

#else

#endif

#if 0

#endif
/********************************************************************************/

#define START_FREQUENCY (45*16)

#define END_FREQUENCY   (863*16)

#define FREESAT_PDSD_VALUE 	0x46534154
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

struct _DmxROMData DmxROMData[HsvDmxLast];
static struct _DmxROMData s__DmxROMData[HsvDmxLast];
Nat8 mBuffer[16*1024];
static Nat8 s__mBuffer[16*1024];
#if 0

Nat8 mModulation[7];
static Nat8 s__mModulation[7];
#endif

static const Nat32 PrivateDataSpecifier [MAXCOUNTRY];
int mCurrentONID;
static int s__mCurrentONID;
Nat8 ModeArray[FILTER_DEPTH];
static Nat8 s__ModeArray[FILTER_DEPTH];
Nat8 MatchArray[FILTER_DEPTH];
static Nat8 s__MatchArray[FILTER_DEPTH];
Nat8 MaskArray[FILTER_DEPTH];
static Nat8 s__MaskArray[FILTER_DEPTH];
#ifndef __cplusplus

#else

#endif

Bool ipop_PopulateNIT ( HsvDemux dmx , Address pNit_Parser, int code );
void InitActualNetworkID(HsvDemux dmx);
void InitNetworkName(HsvDemux dmx);
void InitActualNITVer(HsvDemux dmx);
void InitActualNetworkLCN(HsvDemux dmx);
void InitLinkageInfo(HsvDemux dmx);
void InitActualServiceListDS(HsvDemux dmx);
void InitActualNetworkLCN2(HsvDemux dmx);
void InitActualNetworkHDSLCN(HsvDemux dmx);
void InitOtherNetworkIDInfo(HsvDemux dmx);
void InitOtherNetworkLCN(HsvDemux dmx);
void InitOtherLinkageInfo(HsvDemux dmx);
void InitOtherNetworkLCN2(HsvDemux dmx);
void InitActualNetworkLCN3(HsvDemux dmx)                 /*Cyfrowy*/;
void InitSatelliteDS(HsvDemux dmx);
void InitHeadEndFrequencyList(HsvDemux dmx);
void InitFreesatLinkageInfo(HsvDemux dmx);
Bool PopulateActualNetworkID( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code);
Bool PopulateActualNITVer( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code);
Bool PopulateNetworkName(HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code);
Bool PopulateOtherNetworkIDInfo( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateActualNetworkLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherNetworkLCN(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateLogicalChannel2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateActualNetworkLCN3( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code)						/*Cyfrowy*/;
Bool PopulateLogicalChannel3 ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code)		/*Cyfrowy*/;
Bool PopulateNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateNetworkSDSD(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateHeadEndFrequencyList(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateHDSLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateLinkageInfo ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherLinkageInfo ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateLinkageInfoPrivate ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateActualServiceListDS( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateServiceListDS ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateFreesatLinkageInfo( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
int ConvertBcdToDecimal (int bcdvalue);
int MapModulationType (Nat8 modln);
Nat8 MapFECInner (Nat8 fec);
Nat8 MapPolarization (Nat8 pol);
int MapModulationStd (Nat8 modlnstd);
Bool mPopulateSatelliteDSPrivate(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool mPopulateHeadEndFrequencyList(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Nat32 DeducePrivateDataSpecifier (int NITOnid);
Nat16 mInterpretLCNValue(int NITOnid, int privatedataspecify, Nat16 lcnvalue, Nat16 *vis_flag);
#if 0

Nat8 mInterpretModulationValue(Nat8 *mod);
Nat32 mInterpretSymbolRate(Nat32 *symrate);
#endif
/********************************************************************************/

Nat32 mInterpretCountryCode( Nat32 country );
int iutil_GetLCNValue(Nat8* ptr, int num);
Bool Nit_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxROMData,(void*)s__DmxROMData,sizeof(DmxROMData));
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
#if 0

	memcpy((void*)mModulation,(void*)s__mModulation,sizeof(mModulation));
#endif

	mCurrentONID	=	s__mCurrentONID;
	memcpy((void*)ModeArray,(void*)s__ModeArray,sizeof(ModeArray));
	memcpy((void*)MatchArray,(void*)s__MatchArray,sizeof(MatchArray));
	memcpy((void*)MaskArray,(void*)s__MaskArray,sizeof(MaskArray));
#ifndef __cplusplus

#else

#endif

#if 0

#endif
/********************************************************************************/

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
#ifdef div_MaxChannelsPerNetwork
#undef div_MaxChannelsPerNetwork
#endif //div_MaxChannelsPerNetwork
#ifdef NIT_PID_VALUE
#undef NIT_PID_VALUE
#endif //NIT_PID_VALUE
#ifdef NITT_ACTUAL_TABLE_ID
#undef NITT_ACTUAL_TABLE_ID
#endif //NITT_ACTUAL_TABLE_ID
#ifdef NITT_OTHER_TABLE_ID
#undef NITT_OTHER_TABLE_ID
#endif //NITT_OTHER_TABLE_ID
#ifdef NIT_ACTUAL_REQ
#undef NIT_ACTUAL_REQ
#endif //NIT_ACTUAL_REQ
#ifdef NIT_OTHER_REQ
#undef NIT_OTHER_REQ
#endif //NIT_OTHER_REQ
#ifdef HSV_INVALID_NETWORKID
#undef HSV_INVALID_NETWORKID
#endif //HSV_INVALID_NETWORKID
#ifdef HSV_INVALID_CELLID
#undef HSV_INVALID_CELLID
#endif //HSV_INVALID_CELLID
#ifdef HSV_INVALID_TABLE_ID
#undef HSV_INVALID_TABLE_ID
#endif //HSV_INVALID_TABLE_ID
#ifdef MAX_SECTIONS
#undef MAX_SECTIONS
#endif //MAX_SECTIONS
#ifdef NITACTUAL_INDEX
#undef NITACTUAL_INDEX
#endif //NITACTUAL_INDEX
#ifdef NITOTHER_INDEX
#undef NITOTHER_INDEX
#endif //NITOTHER_INDEX
#ifdef FRANSAT_PACKAGE_ID
#undef FRANSAT_PACKAGE_ID
#endif //FRANSAT_PACKAGE_ID
#ifdef DP(x)
#undef DP(x)
#endif //DP(x)
#ifdef CURRENTTERRESTRIALCODINGTYPE
#undef CURRENTTERRESTRIALCODINGTYPE
#endif //CURRENTTERRESTRIALCODINGTYPE
#ifdef INVALID_REGION_CODE
#undef INVALID_REGION_CODE
#endif //INVALID_REGION_CODE
#ifdef MAXCOUNTRY
#undef MAXCOUNTRY
#endif //MAXCOUNTRY
#ifdef DMX_BUFFER_SIZE
#undef DMX_BUFFER_SIZE
#endif //DMX_BUFFER_SIZE
#ifdef FILTER_DEPTH
#undef FILTER_DEPTH
#endif //FILTER_DEPTH
#ifdef START_FREQUENCY
#undef START_FREQUENCY
#endif //START_FREQUENCY
#ifdef END_FREQUENCY
#undef END_FREQUENCY
#endif //END_FREQUENCY
#endif //LOCAL_UNDEFINES
