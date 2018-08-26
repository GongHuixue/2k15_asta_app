#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <Bat_ParserDef.h>

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define BAT_PID_VALUE                       (0x0011)

#define	BAT_TABLE_ID						(0x4A)	

#define	INVALID_BOUQUET_ID					(0x0FFFF)

#define INVALID_BAT_ECN				(0xC000)

#define INVALID_BAT_LCN				(0xC000) // have to check on what is correct invalid LCN for tricolor

#define DMX_BUFFER_SIZE (16 * 1024)

#define FILTER_DEPTH    (16)

#define FRANSAT_PDSD_VALUE  0x55F

#define FREESAT_PDSD_VALUE 	0x46534154
#define EUTELSAT_CHANNEL_NUMBER_DESCRIPTOR	0x83

#define PRIVATE_DATA_SPECIFIER_DESCRIPTOR 		0x5F
#define FREESAT_INFO_LOCATION_DESCRIPTOR			(0xD7)
#define FREESAT_MAX_INFO_LOCATION_DESC_COUNT			(42)

#define IS_NTVPLUS_BAT(id) 		((id >= 0x0001) && (id <=0x2000)) /*RMCR-768*/
#define FREESAT_SERVICEGROUP_DESCRIPTOR			(0xD5)
#define FREESAT_SERVICEGROUP_DESC_COUNT		(500)

#define FREESAT_INTERACTIVE_STORAGE_DESCRIPTOR (0xD6)
#define FREESAT_INTERACTIVE_STORAGE_DESC_COUNT  (340)

#define FREESAT_INTERACTIVE_RESTRICTION_DESCRIPTOR (0xDB)
#define FREESAT_INTERACTIVE_RESTRICTION_DESC_COUNT	(128)

#define FREESAT_REGIONALISED_LCN_DESCRIPTOR		 (0xD3)
#define FREESAT_REGIONALISED_LCN_DESC_COUNT 		(250)

#define FREESAT_INVALID_LCN				(0x1000)

#define TRICOLOR_LOGICAL_REGION_NAME_DESCRIPTOR_TAG		(0x88)	/* Tricolor logical Region name descriptor tag */
#define TRICOLOR_LCNV2_DESCRIPTOR_TAG					(0x87)	/* Tricolor LcnV2 descriptor tag */
#define IS_TRICOLOR_VALID_BID(x)							((x == 0x01)||(x == 0x02))?TRUE:FALSE

#define HSV_MAKE_CHAR_MASK(a,b,c)           ( ((((Nat32)(a))<<16) ) | (((Nat32)(b))<<8) | (((Nat32)(c))) )

struct DmxRomDataStruct
{            
    Nat8                         Version;
    Nat32                        SubscrId;
    Nat32						 SectionInfo;
	int 						 BouquetId;
};
#ifndef __cplusplus

#endif
/*****   Module functions   *****/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

Nat8 mBuffer[16*1024*8];
static Nat8 s__mBuffer[16*1024*8];
Nat8 ModeArray[FILTER_DEPTH];
static Nat8 s__ModeArray[FILTER_DEPTH];
Nat8 MatchArray[FILTER_DEPTH];
static Nat8 s__MatchArray[FILTER_DEPTH];
Nat8 MaskArray[FILTER_DEPTH];
static Nat8 s__MaskArray[FILTER_DEPTH];
struct DmxRomDataStruct DmxROMData[HsvDmxLast];
static struct DmxRomDataStruct s__DmxROMData[HsvDmxLast];
#ifndef __cplusplus

#endif
/*****   Module functions   *****/

void mInitBatLCN(HsvDemux dmx);
void InitActualServiceListDS(HsvDemux dmx);
void InitLinkageInfo(HsvDemux dmx);
void InitActualBouquetId(HsvDemux dmx);
Bool PopulateActualBouquetId( HsvDemux dmx, TypeBat_Parser *BatTable,  int code);
void mPopulateNetworkLCN( HsvDemux dmx , TypeBat_Parser *BatTable, int code);
void mInitBatLCN2(HsvDemux dmx)						/*cyfra*/;
void mInitBatLCNV2(HsvDemux dmx)						/*NTV+*/;
void mInitBatMulLCNV2(HsvDemux dmx)						/*Tricolor*/;
void mInitBatECN(HsvDemux dmx)					/*FRANSAT-ECD-> Eutelsat Channel Descriptor*/;
void mInitBatDetails(HsvDemux dmx)					/*FRANSAT-BatInfo - Contains overall Bouquet Information*/;

void	mInitBatFreesatSrvGroupTable(HsvDemux dmx);
void	mInitBatFreesatInfoLocationTable(HsvDemux dmx);
void	mInitBatFreesatLCNTable(HsvDemux dmx);

Bool mPopulateFreesatServiceGroupInfo( HsvDemux dmx, TypeBat_Parser *BatTable,  int code);
Bool mPopulateFreesatInteractiveStorageInfo( HsvDemux dmx, TypeBat_Parser *BatTable,  int code);
Bool mPopulateFreesatInteractiveRestrictionInfo( HsvDemux dmx, TypeBat_Parser *BatTable,  int code);
Bool mPopulateFreesatInfoLocationInfo( HsvDemux dmx, TypeBat_Parser *BatTable,  int code);
Bool mPopulateFreesatLCN( HsvDemux dmx, TypeBat_Parser *BatTable,  int code);

void mInitBatTricolorLRNDetails(HsvDemux dmx);
void mPopulateTricolorLRNDetails( HsvDemux dmx , TypeBat_Parser *BatTable, int code);
int mGetLanguageId(char byte1, char byte2, char byte3);
int iutil_GetLCNValue(Nat8* ptr, int num);
void mPopulateTricolorLCNV2( HsvDemux dmx , TypeBat_Parser *BatTable, int code);

void mPopulateNetworkLCN2( HsvDemux dmx , TypeBat_Parser *BatTable, int code);
void mPopulateNetworkLCNV2( HsvDemux dmx , TypeBat_Parser *BatTable, int code);
void mPopulateBouquetDetails( HsvDemux dmx , TypeBat_Parser *BatTable, int code);
void mPopulateEutelsatChannelList( HsvDemux dmx , TypeBat_Parser *BatTable, int code);
Bool PopulateLinkageInfo ( HsvDemux dmx, TypeBat_Parser *BatTable, int code);
Bool PopulateLinkageInfoPrivate ( HsvDemux dmx, TypeBat_Parser *BatTable, int Ppty, int tableid, int code);
Bool PopulateActualServiceListDS( HsvDemux dmx, TypeBat_Parser *BatTable, int code);
Bool PopulateServiceListDS ( HsvDemux dmx, TypeBat_Parser *BatTable, int Ppty, int tableid, int code);
Bool ipop_PopulateBAT ( HsvDemux dmx , Address pBat_Parser, int code );
Bool Bat_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
	memcpy((void*)ModeArray,(void*)s__ModeArray,sizeof(ModeArray));
	memcpy((void*)MatchArray,(void*)s__MatchArray,sizeof(MatchArray));
	memcpy((void*)MaskArray,(void*)s__MaskArray,sizeof(MaskArray));
	memcpy((void*)DmxROMData,(void*)s__DmxROMData,sizeof(DmxROMData));

#ifndef __cplusplus

#endif
/*****   Module functions   *****/

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
#ifdef BAT_PID_VALUE
#undef BAT_PID_VALUE
#endif //BAT_PID_VALUE
#ifdef BAT_TABLE_ID
#undef BAT_TABLE_ID
#endif //BAT_TABLE_ID
#ifdef INVALID_BOUQUET_ID
#undef INVALID_BOUQUET_ID
#endif //INVALID_BOUQUET_ID
#ifdef INVALID_BAT_ECN
#undef INVALID_BAT_ECN
#endif //INVALID_BAT_ECN
#ifdef DMX_BUFFER_SIZE
#undef DMX_BUFFER_SIZE
#endif //DMX_BUFFER_SIZE
#ifdef FILTER_DEPTH
#undef FILTER_DEPTH
#endif //FILTER_DEPTH
#ifdef FRANSAT_PDSD_VALUE
#undef FRANSAT_PDSD_VALUE
#endif //FRANSAT_PDSD_VALUE
#ifdef EUTELSAT_CHANNEL_NUMBER_DESCRIPTOR
#undef EUTELSAT_CHANNEL_NUMBER_DESCRIPTOR
#endif //EUTELSAT_CHANNEL_NUMBER_DESCRIPTOR
#ifdef PRIVATE_DATA_SPECIFIER_DESCRIPTOR
#undef PRIVATE_DATA_SPECIFIER_DESCRIPTOR
#endif //PRIVATE_DATA_SPECIFIER_DESCRIPTOR
#endif //LOCAL_UNDEFINES
