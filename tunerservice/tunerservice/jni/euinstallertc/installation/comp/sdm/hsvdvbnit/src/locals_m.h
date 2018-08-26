#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#include <Nit_ParserDef.h>

#define srtdbids_NitLcnTableMain 1

#define srtdbids_NitLinkageInfoMain 1

#define srtdbids_NitCableDSMain 1

#define srtdbids_NitTsRelocateTableMain 1

#define srtdbids_NitSrvclstTableMain 1

#define srtdbids_NitLcn2TableMain 1

#define srtdbids_NitHDSLcnTableMain 1

#define srtdbids_NitOtherNetworkIdTable 1

#define srtdbids_NitLcnTableSub 1

#define srtdbids_NitLinkageInfoSub 1

#define srtdbids_NitCableDSSub 1

#define srtdbids_NitLcn2TableSub 1

#define srtdbids_NitSrvclstTableSub 1

#define srtdbids_NitSrvcAtrbTableMain 1

#define srtdbids_NitFreqList 1

#define srtdbids_NitHDSLcnTableSub 1

#define srtdbids_NitTargetRegion 1

#define srtdbids_NitTargetRegionName 1

#define srtdbids_NitLCN2Favorite 1

#define srtdbids_NitActualTsId 1
#define srtdb_Init(a) 1

#define srtdb_Insert(inst, pK, sK, tK, qK, data) 1

#define srtdb_GetNoOfRecords(inst) 1

#define srtdb_SearchOnPrimaryKey(inst, pK, frm, to) 1

#define srtdb_SearchOnKey(inst, pK, sK, tK, qK, index) 1

#define srtdb_QueryOnKey(inst, pK, sK, tK, qK, data) 1

#define srtdb_QueryOnIndex(inst, index, data) 1

#define srtdb_Update(inst, pK, sK, tK, qK, data) 1

#define srtdb_Delete(inst, pK, sK, tK, qK) 1

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define div_MaxChannelsPerNetwork           (50)

#define NIT_PID_VALUE                       (0x10)

#define NITT_ACTUAL_TABLE_ID                (0x40)

#define NITT_OTHER_TABLE_ID                 (0x41)

#define NIT_ACTUAL_REQ                      (0x1)

#define NIT_OTHER_REQ                       (0x2)
/* fixme: We need to debate on these values */

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define HSV_INVALID_CELLID                 (0xFFFF)

#define HSV_INVALID_TABLE_ID               (-1)

#define MAX_SECTIONS                        (2)

#define NITACTUAL_INDEX                     (0)

#define NITOTHER_INDEX                      (1)

#define MULTIPLE_LCN_SUPPORTED				 eurdiv_MultipleLCNSupported()

#define CURRENTTERRESTRIALCODINGTYPE  3

#define INVALID_REGION_CODE           0xFFFF

#define	LCN_TYPE_V1						(1)
#define	LCN_TYPE_V2						(2)
#define	LCN_TYPE_HDS					(3)


#define 	IS_SYSTEM_NETWORKOPERATOR_RCSRDS	((sysset_GetSystemCountry() == cids_CountryRomania)&&(ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator) == ins_RCSRDS)? true : false)

#define 	RCS_RDS_PDSD_VALUE					(0x01A0)

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
#define DMX_BUFFER_SIZE (16 * 1024)

#define FILTER_DEPTH    (16)

#ifdef __cplusplus

#else

#endif

#define START_FREQUENCY (45*16)

#define END_FREQUENCY   (863*16)

#if 0

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

struct _DmxROMData DmxROMData[HsvDmxLast];
static struct _DmxROMData s__DmxROMData[HsvDmxLast];
Nat8 mModulation[7];
static Nat8 s__mModulation[7];
static const Nat32 PrivateDataSpecifier [];
int mCurrentONID;
static int s__mCurrentONID;
Nat16 ActualNetworkId;
static Nat16 s__ActualNetworkId;
Nat8 ModeArray[FILTER_DEPTH];
static Nat8 s__ModeArray[FILTER_DEPTH];
Nat8 MatchArray[FILTER_DEPTH];
static Nat8 s__MatchArray[FILTER_DEPTH];
Nat8 MaskArray[FILTER_DEPTH];
static Nat8 s__MaskArray[FILTER_DEPTH];
#ifdef __cplusplus

#else

#endif

Bool ipop_PopulateNIT ( HsvDemux dmx , Address pNit_Parser, int code );
void InitActualNetworkID(HsvDemux dmx);
void InitNetworkName(HsvDemux dmx);
void InitActualNITVer(HsvDemux dmx);
void InitActualNetworkLCN(HsvDemux dmx);
void InitLinkageInfo(HsvDemux dmx);
void InitActualCableDS(HsvDemux dmx);
void InitActualTSRelocateDS(HsvDemux dmx);
void InitActualServiceListDS(HsvDemux dmx);
void InitActualNetworkLCN2(HsvDemux dmx);
void InitActualNetworkHDSLCN(HsvDemux dmx);
void InitOtherNetworkIDInfo(HsvDemux dmx);
void InitOtherNetworkLCN(HsvDemux dmx);
void InitOtherLinkageInfo(HsvDemux dmx);
void InitOtherCableDS(HsvDemux dmx);
void InitOtherNetworkLCN2(HsvDemux dmx);
void InitOtherServiceListDS(HsvDemux dmx);
void InitNetworkSRVCATRB ( HsvDemux dmx);
void InitNetworkFreqList ( HsvDemux dmx);
void InitOtherNetworkHDSLCN(HsvDemux dmx);
void InitTargetRegionDesc( HsvDemux dmx);
void InitTargetRegionNameDesc( HsvDemux dmx);
void InitActualNetworkLCN2FavoriteList(HsvDemux dmx);
void InitActualTsID(HsvDemux dmx);
Bool PopulateActualNetworkID( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code);
Bool PopulateActualNITVer( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code);
Bool PopulateNetworkName(HsvDemux dmx, TypeNit_Parser *NetWkTable,  int code);
Bool PopulateActualTSRelocateDS(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateActualTsId(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateNITTsId(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateTSRelocateDS(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateOtherNetworkIDInfo( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateActualNetworkLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherNetworkLCN(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateActualCableDS(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateChannelListId(HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateNetworkLogicalChannelV2 ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateOtherCableDS( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateCableDSPrivate(HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherNetworkLCN2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateLogicalChannel2( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherNetworkHDSLCN( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateHDSLogicalChannel ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateLinkageInfo ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherLinkageInfo ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateLinkageInfoPrivate ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateNetworkSRVCATRB ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateServiceAttribute ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Bool PopulateActualServiceListDS( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Bool PopulateOtherServiceListDS(HsvDemux dmx, TypeNit_Parser * NetWkTable, int code);
Bool PopulateServiceListDS ( HsvDemux dmx, TypeNit_Parser *NetWkTable, int Ppty, int tableid, int code);
Nat32 DeducePrivateDataSpecifier (int NITOnid);
Nat16 mInterpretLCNValue(int NITOnid, int privatedataspecify, Nat16 lcnvalue, Nat16 *vis_flag, int LcnType);
Nat32 mInterpretFrequencyValue(Nat32 *freq);
Nat8 mInterpretModulationValue(Nat8 *mod);
Nat32 mInterpretSymbolRate(Nat32 *symrate);
Nat32 mInterpretCountryCode( Nat32 country );
Bool mValidateCDS(HsvNITCableDS *pCds, int index);
int iutil_GetLCNValue(Nat8* ptr, int num);
Bool PopulateFreqList(HsvDemux dmx, TypeNit_Parser * NetWkTable, int code);
Bool PopulateFreqListPrivate( HsvDemux dmx, TypeNit_Parser *NetWkTable,  int Ppty, int tableid, int code);
void PopulateTargetRegionDesc( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
void PopulateTargetRegionNameDesc( HsvDemux dmx, TypeNit_Parser *NetWkTable, int code);
Nat8 GetLanguageId(Nat32 Language);
Nat8 mBuffer[4*1024];
static Nat8 s__mBuffer[4*1024];
Bool Nit_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
#if 0

#endif

void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxROMData,(void*)s__DmxROMData,sizeof(DmxROMData));
	memcpy((void*)mModulation,(void*)s__mModulation,sizeof(mModulation));
	mCurrentONID	=	s__mCurrentONID;
	ActualNetworkId	=	s__ActualNetworkId;
	memcpy((void*)ModeArray,(void*)s__ModeArray,sizeof(ModeArray));
	memcpy((void*)MatchArray,(void*)s__MatchArray,sizeof(MatchArray));
	memcpy((void*)MaskArray,(void*)s__MaskArray,sizeof(MaskArray));
#ifdef __cplusplus

#else

#endif

	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
#if 0

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef TraceNotice(m,
#undef TraceNotice(m,
#endif //TraceNotice(m,
#ifdef TraceInfo(m,
#undef TraceInfo(m,
#endif //TraceInfo(m,
#ifdef TraceDebug(m,
#undef TraceDebug(m,
#endif //TraceDebug(m,
#ifdef srtdbids_NitLcnTableMain
#undef srtdbids_NitLcnTableMain
#endif //srtdbids_NitLcnTableMain
#ifdef srtdbids_NitLinkageInfoMain
#undef srtdbids_NitLinkageInfoMain
#endif //srtdbids_NitLinkageInfoMain
#ifdef srtdbids_NitCableDSMain
#undef srtdbids_NitCableDSMain
#endif //srtdbids_NitCableDSMain
#ifdef srtdbids_NitTsRelocateTableMain
#undef srtdbids_NitTsRelocateTableMain
#endif //srtdbids_NitTsRelocateTableMain
#ifdef srtdbids_NitSrvclstTableMain
#undef srtdbids_NitSrvclstTableMain
#endif //srtdbids_NitSrvclstTableMain
#ifdef srtdbids_NitLcn2TableMain
#undef srtdbids_NitLcn2TableMain
#endif //srtdbids_NitLcn2TableMain
#ifdef srtdbids_NitHDSLcnTableMain
#undef srtdbids_NitHDSLcnTableMain
#endif //srtdbids_NitHDSLcnTableMain
#ifdef srtdbids_NitOtherNetworkIdTable
#undef srtdbids_NitOtherNetworkIdTable
#endif //srtdbids_NitOtherNetworkIdTable
#ifdef srtdbids_NitLcnTableSub
#undef srtdbids_NitLcnTableSub
#endif //srtdbids_NitLcnTableSub
#ifdef srtdbids_NitLinkageInfoSub
#undef srtdbids_NitLinkageInfoSub
#endif //srtdbids_NitLinkageInfoSub
#ifdef srtdbids_NitCableDSSub
#undef srtdbids_NitCableDSSub
#endif //srtdbids_NitCableDSSub
#ifdef srtdbids_NitLcn2TableSub
#undef srtdbids_NitLcn2TableSub
#endif //srtdbids_NitLcn2TableSub
#ifdef srtdbids_NitSrvclstTableSub
#undef srtdbids_NitSrvclstTableSub
#endif //srtdbids_NitSrvclstTableSub
#ifdef srtdbids_NitSrvcAtrbTableMain
#undef srtdbids_NitSrvcAtrbTableMain
#endif //srtdbids_NitSrvcAtrbTableMain
#ifdef srtdbids_NitFreqList
#undef srtdbids_NitFreqList
#endif //srtdbids_NitFreqList
#ifdef srtdbids_NitHDSLcnTableSub
#undef srtdbids_NitHDSLcnTableSub
#endif //srtdbids_NitHDSLcnTableSub
#ifdef srtdbids_NitTargetRegion
#undef srtdbids_NitTargetRegion
#endif //srtdbids_NitTargetRegion
#ifdef srtdbids_NitTargetRegionName
#undef srtdbids_NitTargetRegionName
#endif //srtdbids_NitTargetRegionName
#ifdef srtdbids_NitLCN2Favorite
#undef srtdbids_NitLCN2Favorite
#endif //srtdbids_NitLCN2Favorite
#ifdef srtdbids_NitActualTsId
#undef srtdbids_NitActualTsId
#endif //srtdbids_NitActualTsId
#ifdef srtdb_Init(a)
#undef srtdb_Init(a)
#endif //srtdb_Init(a)
#ifdef srtdb_Insert(inst,
#undef srtdb_Insert(inst,
#endif //srtdb_Insert(inst,
#ifdef srtdb_GetNoOfRecords(inst)
#undef srtdb_GetNoOfRecords(inst)
#endif //srtdb_GetNoOfRecords(inst)
#ifdef srtdb_SearchOnPrimaryKey(inst,
#undef srtdb_SearchOnPrimaryKey(inst,
#endif //srtdb_SearchOnPrimaryKey(inst,
#ifdef srtdb_SearchOnKey(inst,
#undef srtdb_SearchOnKey(inst,
#endif //srtdb_SearchOnKey(inst,
#ifdef srtdb_QueryOnKey(inst,
#undef srtdb_QueryOnKey(inst,
#endif //srtdb_QueryOnKey(inst,
#ifdef srtdb_QueryOnIndex(inst,
#undef srtdb_QueryOnIndex(inst,
#endif //srtdb_QueryOnIndex(inst,
#ifdef srtdb_Update(inst,
#undef srtdb_Update(inst,
#endif //srtdb_Update(inst,
#ifdef srtdb_Delete(inst,
#undef srtdb_Delete(inst,
#endif //srtdb_Delete(inst,
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
#ifdef MULTIPLE_LCN_SUPPORTED
#undef MULTIPLE_LCN_SUPPORTED
#endif //MULTIPLE_LCN_SUPPORTED
#ifdef CURRENTTERRESTRIALCODINGTYPE
#undef CURRENTTERRESTRIALCODINGTYPE
#endif //CURRENTTERRESTRIALCODINGTYPE
#ifdef INVALID_REGION_CODE
#undef INVALID_REGION_CODE
#endif //INVALID_REGION_CODE
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
