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

#define cids_CountryAlbania	((int)0x26)

#define cids_CountryAlbania_CONSTANT	0x26

#define cids_CountryArgentina	((int)0x25)

#define cids_CountryArgentina_CONSTANT	0x25

#define cids_CountryArmenia	((int)0x27)

#define cids_CountryArmenia_CONSTANT	0x27

#define cids_CountryAustralia	((int)0x1C)

#define cids_CountryAustralia_CONSTANT	0x1C

#define cids_CountryAustria	((int)0x0)

#define cids_CountryAustria_CONSTANT	0x0

#define cids_CountryAzerbaijan	((int)0x28)

#define cids_CountryAzerbaijan_CONSTANT	0x28

#define cids_CountryBelarus	((int)0x29)

#define cids_CountryBelarus_CONSTANT	0x29

#define cids_CountryBelgium	((int)0x1)

#define cids_CountryBelgium_CONSTANT	0x1

#define cids_CountryBosniaAndHerzegovina	((int)0x2A)

#define cids_CountryBosniaAndHerzegovina_CONSTANT	0x2A

#define cids_CountryBrazil	((int)0x24)

#define cids_CountryBrazil_CONSTANT	0x24

#define cids_CountryBulgaria	((int)0x21)

#define cids_CountryBulgaria_CONSTANT	0x21

#define cids_CountryChina	((int)0x22)

#define cids_CountryChina_CONSTANT	0x22

#define cids_CountryCroatia	((int)0x2)

#define cids_CountryCroatia_CONSTANT	0x2

#define cids_CountryCzechrep	((int)0x3)

#define cids_CountryCzechrep_CONSTANT	0x3

#define cids_CountryDenmark	((int)0x4)

#define cids_CountryDenmark_CONSTANT	0x4

#define cids_CountryEstonia	((int)0x1D)

#define cids_CountryEstonia_CONSTANT	0x1D

#define cids_CountryFinland	((int)0x5)

#define cids_CountryFinland_CONSTANT	0x5

#define cids_CountryFrance	((int)0x6)

#define cids_CountryFrance_CONSTANT	0x6

#define cids_CountryGeorgia	((int)0x2B)

#define cids_CountryGeorgia_CONSTANT	0x2B

#define cids_CountryGermany	((int)0x7)

#define cids_CountryGermany_CONSTANT	0x7

#define cids_CountryGreece	((int)0x8)

#define cids_CountryGreece_CONSTANT	0x8

#define cids_CountryHungary	((int)0x9)

#define cids_CountryHungary_CONSTANT	0x9

#define cids_CountryIreland	((int)0xA)

#define cids_CountryIreland_CONSTANT	0xA

#define cids_CountryIsrael	((int)0x2D)

#define cids_CountryIsrael_CONSTANT	0x2D

#define cids_CountryItaly	((int)0xB)

#define cids_CountryItaly_CONSTANT	0xB

#define cids_CountryKazakhstan	((int)0x20)

#define cids_CountryKazakhstan_CONSTANT	0x20

#define cids_CountryLatvia	((int)0x1F)

#define cids_CountryLatvia_CONSTANT	0x1F

#define cids_CountryLithuania	((int)0x1E)

#define cids_CountryLithuania_CONSTANT	0x1E

#define cids_CountryLuxembourg	((int)0xC)

#define cids_CountryLuxembourg_CONSTANT	0xC

#define cids_CountryMacedoniafyrom	((int)0x2E)

#define cids_CountryMacedoniafyrom_CONSTANT	0x2E

#define cids_CountryMax	((int)0x2F)

#define cids_CountryMax_CONSTANT	0x2F

#define cids_CountryMontenegro	((int)0x2C)

#define cids_CountryMontenegro_CONSTANT	0x2C

#define cids_CountryNetherlands	((int)0xD)

#define cids_CountryNetherlands_CONSTANT	0xD

#define cids_CountryNorway	((int)0xE)

#define cids_CountryNorway_CONSTANT	0xE

#define cids_CountryOther	((int)0x1B)

#define cids_CountryOther_CONSTANT	0x1B

#define cids_CountryPoland	((int)0xF)

#define cids_CountryPoland_CONSTANT	0xF

#define cids_CountryPortugal	((int)0x10)

#define cids_CountryPortugal_CONSTANT	0x10

#define cids_CountryRomania	((int)0x11)

#define cids_CountryRomania_CONSTANT	0x11

#define cids_CountryRussia	((int)0x12)

#define cids_CountryRussia_CONSTANT	0x12

#define cids_CountrySerbia	((int)0x13)

#define cids_CountrySerbia_CONSTANT	0x13

#define cids_CountrySlovakia	((int)0x14)

#define cids_CountrySlovakia_CONSTANT	0x14

#define cids_CountrySlovenia	((int)0x15)

#define cids_CountrySlovenia_CONSTANT	0x15

#define cids_CountrySpain	((int)0x16)

#define cids_CountrySpain_CONSTANT	0x16

#define cids_CountrySweden	((int)0x17)

#define cids_CountrySweden_CONSTANT	0x17

#define cids_CountrySwitzerland	((int)0x18)

#define cids_CountrySwitzerland_CONSTANT	0x18

#define cids_CountryTurkey	((int)0x19)

#define cids_CountryTurkey_CONSTANT	0x19

#define cids_CountryUK	((int)0x1A)

#define cids_CountryUK_CONSTANT	0x1A

#define cids_CountryUkraine	((int)0x23)

#define cids_CountryUkraine_CONSTANT	0x23


/* interface srtdbids : IHsvDvbSiSortedTableIds */

#define srtdbids_EitFollowActual	((int)0x4)

#define srtdbids_EitFollowActual_CONSTANT	0x4

#define srtdbids_EitFollowOther	((int)0xFFFFFFFF)

#define srtdbids_EitFollowOther_CONSTANT	0xFFFFFFFF

#define srtdbids_EitLinkageInfo	((int)0x36)

#define srtdbids_EitLinkageInfo_CONSTANT	0x36

#define srtdbids_EitPresentActual	((int)0x3)

#define srtdbids_EitPresentActual_CONSTANT	0x3

#define srtdbids_EitPresentOther	((int)0xFFFFFFFF)

#define srtdbids_EitPresentOther_CONSTANT	0xFFFFFFFF

#define srtdbids_EitScheduleActual	((int)0xFFFFFFFF)

#define srtdbids_EitScheduleActual_CONSTANT	0xFFFFFFFF

#define srtdbids_EitScheduleOther	((int)0xFFFFFFFF)

#define srtdbids_EitScheduleOther_CONSTANT	0xFFFFFFFF

#define srtdbids_LinkageInfoMain	((int)0x1E)

#define srtdbids_LinkageInfoMain_CONSTANT	0x1E

#define srtdbids_NitCableDSMain	((int)0x26)

#define srtdbids_NitCableDSMain_CONSTANT	0x26

#define srtdbids_NitCableDSSub	((int)0x27)

#define srtdbids_NitCableDSSub_CONSTANT	0x27

#define srtdbids_NitFreqList	((int)0x29)

#define srtdbids_NitFreqList_CONSTANT	0x29

#define srtdbids_NitHDSLcnTableMain	((int)0x2F)

#define srtdbids_NitHDSLcnTableMain_CONSTANT	0x2F

#define srtdbids_NitHDSLcnTableSub	((int)0x35)

#define srtdbids_NitHDSLcnTableSub_CONSTANT	0x35

#define srtdbids_NitLcn2TableMain	((int)0x2B)

#define srtdbids_NitLcn2TableMain_CONSTANT	0x2B

#define srtdbids_NitLcn2TableSub	((int)0x2C)

#define srtdbids_NitLcn2TableSub_CONSTANT	0x2C

#define srtdbids_NitLcnTableMain	((int)0x1F)

#define srtdbids_NitLcnTableMain_CONSTANT	0x1F

#define srtdbids_NitLcnTableSub	((int)0x23)

#define srtdbids_NitLcnTableSub_CONSTANT	0x23

#define srtdbids_NitLinkageInfoMain	((int)0x24)

#define srtdbids_NitLinkageInfoMain_CONSTANT	0x24

#define srtdbids_NitLinkageInfoSub	((int)0x25)

#define srtdbids_NitLinkageInfoSub_CONSTANT	0x25

#define srtdbids_NitOtherNetworkIdTable	((int)0x28)

#define srtdbids_NitOtherNetworkIdTable_CONSTANT	0x28

#define srtdbids_NitSrvcAtrbTableMain	((int)0x30)

#define srtdbids_NitSrvcAtrbTableMain_CONSTANT	0x30

#define srtdbids_NitSrvclstTableMain	((int)0x32)

#define srtdbids_NitSrvclstTableMain_CONSTANT	0x32

#define srtdbids_NitSrvclstTableSub	((int)0x33)

#define srtdbids_NitSrvclstTableSub_CONSTANT	0x33

#define srtdbids_NitTargetRegion	((int)0x38)

#define srtdbids_NitTargetRegion_CONSTANT	0x38

#define srtdbids_NitTargetRegionName	((int)0x39)

#define srtdbids_NitTargetRegionName_CONSTANT	0x39

#define srtdbids_NitTsRelocateTableMain	((int)0x34)

#define srtdbids_NitTsRelocateTableMain_CONSTANT	0x34

#define srtdbids_NitLCN2Favorite	((int)0x35)

#define srtdbids_NitLCN2Favorite_CONSTANT	0x35

#define srtdbids_SdtTableActual	((int)0x20)

#define srtdbids_SdtTableActual_CONSTANT	0x20

#define srtdbids_SdtTableOther	((int)0x31)

#define srtdbids_SdtTableOther_CONSTANT	0x31

#define srtdbids_SdtTargetRegion	((int)0x37)

#define srtdbids_SdtTargetRegion_CONSTANT	0x37

#define srtdbids_TotTableMain	((int)0x6)

#define srtdbids_TotTableMain_CONSTANT	0x6

#define srtdbids_SdtSvcAvailability ((int)0x72)

#define srtdbids_SdtSvcAvailability_CONSTANT   0x72

#define div_ChannelNameLength  (41)

#define SDT_PID_VALUE                      (0x0011)

#define HSV_INVALID_NETWORKID              (0xFFFF)

#define HSV_INVALID_TSID                   (0xFFFF)

#define HSV_INVALID_ONID                   (0xFFFF)

#define HSV_INVALID_SERVICE                (0xFFFF)

#define HSV_INVALID_TABLE_ID               (-1)

#define SDT_ACTUAL_TABLE_ID                (0x42)

#define SDT_OTHER_TABLE_ID                (0x46)

#define MAX_SECTIONS    (2)

#define SDT_ACTUAL_INDEX (0)

#define SDT_OTHER_INDEX  (1)

#define MAX_PROPERTIES  (2)

#define SDT_OTHER_COOKIE        (3)

#define CIP_PRIVATE_DATA_SPEC   (0x00000040)

#define SDT_ACTUAL_REQ                      (0x1)

#define SDT_OTHER_REQ                       (0x2)

#define DMX_BUFFER_SIZE                     (16 * 1024)

#define FILTER_DEPTH                        (16)

#define INVALID_REGION_DEPTH    0xFFFF

//#define ServiceNameLength 22 

/*********************************
  Data for a given dmx
 **********************************/

typedef struct
{
    int                          TableIds          [MAX_PROPERTIES];
    Nat8                         Version           [MAX_SECTIONS];
    Nat32                        SubscrId          [MAX_SECTIONS];
    Nat32                        SectionInfo[MAX_SECTIONS];
    Nat16                        TsId;
    Nat16                        OtherTsId;
    Nat16                        OtherONID;
    int                          OtherTsVersionNo;
    Nat16                        OriginalNetworkId ;
    int                          TsVersionNo   ;
    HsvLinkageInfo               LinkageInfo   ;
    HsvSDTSection                SDTOtherSection;
    Bool                         ActualSectionValid;
    Bool                         OtherSectionValid;
    Nat16                        ActualOnId;
    Nat16                        ActualSvcId;
    Nat8                         TablesReq;
    Nat8                         TablesRecvd;
}DemuxData;
#ifdef __cplusplus

#else

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
#ifdef __cplusplus

#else

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
void InitServiceAvailablityDesc(HsvDemux dmx);
void InitTargetRegionDesc( HsvDemux dmx);
void InitMultiLingSvcNameDesc( HsvDemux dmx);
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
void PopulateTargetRegionDesc( HsvDemux dmx, TypeSdt_Parser  *ServiceTable, int code);
Nat32 mInterpretCountryCode( Nat32 country );
void PopulateServiceAvailabilityDesc ( HsvDemux dmx, TypeSdt_Parser *ServiceTable,  int code);
void DeleteServicesOldVersion(HsvSDTSection *DbaseVersion, int tableid);
void PopulateMultiLingSvcNameDesc( HsvDemux dmx, TypeSdt_Parser  *ServiceTable, int code);
Nat8 GetLanguageId(Nat32 Language);
Nat8 mBuffer[4*1024];
static Nat8 s__mBuffer[4*1024];
Bool Sdt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)DmxData,(void*)s__DmxData,sizeof(DmxData));
	memcpy((void*)ModeArray,(void*)s__ModeArray,sizeof(ModeArray));
	memcpy((void*)MatchArray,(void*)s__MatchArray,sizeof(MatchArray));
	memcpy((void*)MaskArray,(void*)s__MaskArray,sizeof(MaskArray));
#ifdef __cplusplus

#else

#endif

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
#ifdef cids_CountryAlbania
#undef cids_CountryAlbania
#endif //cids_CountryAlbania
#ifdef cids_CountryAlbania_CONSTANT
#undef cids_CountryAlbania_CONSTANT
#endif //cids_CountryAlbania_CONSTANT
#ifdef cids_CountryArgentina
#undef cids_CountryArgentina
#endif //cids_CountryArgentina
#ifdef cids_CountryArgentina_CONSTANT
#undef cids_CountryArgentina_CONSTANT
#endif //cids_CountryArgentina_CONSTANT
#ifdef cids_CountryArmenia
#undef cids_CountryArmenia
#endif //cids_CountryArmenia
#ifdef cids_CountryArmenia_CONSTANT
#undef cids_CountryArmenia_CONSTANT
#endif //cids_CountryArmenia_CONSTANT
#ifdef cids_CountryAustralia
#undef cids_CountryAustralia
#endif //cids_CountryAustralia
#ifdef cids_CountryAustralia_CONSTANT
#undef cids_CountryAustralia_CONSTANT
#endif //cids_CountryAustralia_CONSTANT
#ifdef cids_CountryAustria
#undef cids_CountryAustria
#endif //cids_CountryAustria
#ifdef cids_CountryAustria_CONSTANT
#undef cids_CountryAustria_CONSTANT
#endif //cids_CountryAustria_CONSTANT
#ifdef cids_CountryAzerbaijan
#undef cids_CountryAzerbaijan
#endif //cids_CountryAzerbaijan
#ifdef cids_CountryAzerbaijan_CONSTANT
#undef cids_CountryAzerbaijan_CONSTANT
#endif //cids_CountryAzerbaijan_CONSTANT
#ifdef cids_CountryBelarus
#undef cids_CountryBelarus
#endif //cids_CountryBelarus
#ifdef cids_CountryBelarus_CONSTANT
#undef cids_CountryBelarus_CONSTANT
#endif //cids_CountryBelarus_CONSTANT
#ifdef cids_CountryBelgium
#undef cids_CountryBelgium
#endif //cids_CountryBelgium
#ifdef cids_CountryBelgium_CONSTANT
#undef cids_CountryBelgium_CONSTANT
#endif //cids_CountryBelgium_CONSTANT
#ifdef cids_CountryBosniaAndHerzegovina
#undef cids_CountryBosniaAndHerzegovina
#endif //cids_CountryBosniaAndHerzegovina
#ifdef cids_CountryBosniaAndHerzegovina_CONSTANT
#undef cids_CountryBosniaAndHerzegovina_CONSTANT
#endif //cids_CountryBosniaAndHerzegovina_CONSTANT
#ifdef cids_CountryBrazil
#undef cids_CountryBrazil
#endif //cids_CountryBrazil
#ifdef cids_CountryBrazil_CONSTANT
#undef cids_CountryBrazil_CONSTANT
#endif //cids_CountryBrazil_CONSTANT
#ifdef cids_CountryBulgaria
#undef cids_CountryBulgaria
#endif //cids_CountryBulgaria
#ifdef cids_CountryBulgaria_CONSTANT
#undef cids_CountryBulgaria_CONSTANT
#endif //cids_CountryBulgaria_CONSTANT
#ifdef cids_CountryChina
#undef cids_CountryChina
#endif //cids_CountryChina
#ifdef cids_CountryChina_CONSTANT
#undef cids_CountryChina_CONSTANT
#endif //cids_CountryChina_CONSTANT
#ifdef cids_CountryCroatia
#undef cids_CountryCroatia
#endif //cids_CountryCroatia
#ifdef cids_CountryCroatia_CONSTANT
#undef cids_CountryCroatia_CONSTANT
#endif //cids_CountryCroatia_CONSTANT
#ifdef cids_CountryCzechrep
#undef cids_CountryCzechrep
#endif //cids_CountryCzechrep
#ifdef cids_CountryCzechrep_CONSTANT
#undef cids_CountryCzechrep_CONSTANT
#endif //cids_CountryCzechrep_CONSTANT
#ifdef cids_CountryDenmark
#undef cids_CountryDenmark
#endif //cids_CountryDenmark
#ifdef cids_CountryDenmark_CONSTANT
#undef cids_CountryDenmark_CONSTANT
#endif //cids_CountryDenmark_CONSTANT
#ifdef cids_CountryEstonia
#undef cids_CountryEstonia
#endif //cids_CountryEstonia
#ifdef cids_CountryEstonia_CONSTANT
#undef cids_CountryEstonia_CONSTANT
#endif //cids_CountryEstonia_CONSTANT
#ifdef cids_CountryFinland
#undef cids_CountryFinland
#endif //cids_CountryFinland
#ifdef cids_CountryFinland_CONSTANT
#undef cids_CountryFinland_CONSTANT
#endif //cids_CountryFinland_CONSTANT
#ifdef cids_CountryFrance
#undef cids_CountryFrance
#endif //cids_CountryFrance
#ifdef cids_CountryFrance_CONSTANT
#undef cids_CountryFrance_CONSTANT
#endif //cids_CountryFrance_CONSTANT
#ifdef cids_CountryGeorgia
#undef cids_CountryGeorgia
#endif //cids_CountryGeorgia
#ifdef cids_CountryGeorgia_CONSTANT
#undef cids_CountryGeorgia_CONSTANT
#endif //cids_CountryGeorgia_CONSTANT
#ifdef cids_CountryGermany
#undef cids_CountryGermany
#endif //cids_CountryGermany
#ifdef cids_CountryGermany_CONSTANT
#undef cids_CountryGermany_CONSTANT
#endif //cids_CountryGermany_CONSTANT
#ifdef cids_CountryGreece
#undef cids_CountryGreece
#endif //cids_CountryGreece
#ifdef cids_CountryGreece_CONSTANT
#undef cids_CountryGreece_CONSTANT
#endif //cids_CountryGreece_CONSTANT
#ifdef cids_CountryHungary
#undef cids_CountryHungary
#endif //cids_CountryHungary
#ifdef cids_CountryHungary_CONSTANT
#undef cids_CountryHungary_CONSTANT
#endif //cids_CountryHungary_CONSTANT
#ifdef cids_CountryIreland
#undef cids_CountryIreland
#endif //cids_CountryIreland
#ifdef cids_CountryIreland_CONSTANT
#undef cids_CountryIreland_CONSTANT
#endif //cids_CountryIreland_CONSTANT
#ifdef cids_CountryIsrael
#undef cids_CountryIsrael
#endif //cids_CountryIsrael
#ifdef cids_CountryIsrael_CONSTANT
#undef cids_CountryIsrael_CONSTANT
#endif //cids_CountryIsrael_CONSTANT
#ifdef cids_CountryItaly
#undef cids_CountryItaly
#endif //cids_CountryItaly
#ifdef cids_CountryItaly_CONSTANT
#undef cids_CountryItaly_CONSTANT
#endif //cids_CountryItaly_CONSTANT
#ifdef cids_CountryKazakhstan
#undef cids_CountryKazakhstan
#endif //cids_CountryKazakhstan
#ifdef cids_CountryKazakhstan_CONSTANT
#undef cids_CountryKazakhstan_CONSTANT
#endif //cids_CountryKazakhstan_CONSTANT
#ifdef cids_CountryLatvia
#undef cids_CountryLatvia
#endif //cids_CountryLatvia
#ifdef cids_CountryLatvia_CONSTANT
#undef cids_CountryLatvia_CONSTANT
#endif //cids_CountryLatvia_CONSTANT
#ifdef cids_CountryLithuania
#undef cids_CountryLithuania
#endif //cids_CountryLithuania
#ifdef cids_CountryLithuania_CONSTANT
#undef cids_CountryLithuania_CONSTANT
#endif //cids_CountryLithuania_CONSTANT
#ifdef cids_CountryLuxembourg
#undef cids_CountryLuxembourg
#endif //cids_CountryLuxembourg
#ifdef cids_CountryLuxembourg_CONSTANT
#undef cids_CountryLuxembourg_CONSTANT
#endif //cids_CountryLuxembourg_CONSTANT
#ifdef cids_CountryMacedoniafyrom
#undef cids_CountryMacedoniafyrom
#endif //cids_CountryMacedoniafyrom
#ifdef cids_CountryMacedoniafyrom_CONSTANT
#undef cids_CountryMacedoniafyrom_CONSTANT
#endif //cids_CountryMacedoniafyrom_CONSTANT
#ifdef cids_CountryMax
#undef cids_CountryMax
#endif //cids_CountryMax
#ifdef cids_CountryMax_CONSTANT
#undef cids_CountryMax_CONSTANT
#endif //cids_CountryMax_CONSTANT
#ifdef cids_CountryMontenegro
#undef cids_CountryMontenegro
#endif //cids_CountryMontenegro
#ifdef cids_CountryMontenegro_CONSTANT
#undef cids_CountryMontenegro_CONSTANT
#endif //cids_CountryMontenegro_CONSTANT
#ifdef cids_CountryNetherlands
#undef cids_CountryNetherlands
#endif //cids_CountryNetherlands
#ifdef cids_CountryNetherlands_CONSTANT
#undef cids_CountryNetherlands_CONSTANT
#endif //cids_CountryNetherlands_CONSTANT
#ifdef cids_CountryNorway
#undef cids_CountryNorway
#endif //cids_CountryNorway
#ifdef cids_CountryNorway_CONSTANT
#undef cids_CountryNorway_CONSTANT
#endif //cids_CountryNorway_CONSTANT
#ifdef cids_CountryOther
#undef cids_CountryOther
#endif //cids_CountryOther
#ifdef cids_CountryOther_CONSTANT
#undef cids_CountryOther_CONSTANT
#endif //cids_CountryOther_CONSTANT
#ifdef cids_CountryPoland
#undef cids_CountryPoland
#endif //cids_CountryPoland
#ifdef cids_CountryPoland_CONSTANT
#undef cids_CountryPoland_CONSTANT
#endif //cids_CountryPoland_CONSTANT
#ifdef cids_CountryPortugal
#undef cids_CountryPortugal
#endif //cids_CountryPortugal
#ifdef cids_CountryPortugal_CONSTANT
#undef cids_CountryPortugal_CONSTANT
#endif //cids_CountryPortugal_CONSTANT
#ifdef cids_CountryRomania
#undef cids_CountryRomania
#endif //cids_CountryRomania
#ifdef cids_CountryRomania_CONSTANT
#undef cids_CountryRomania_CONSTANT
#endif //cids_CountryRomania_CONSTANT
#ifdef cids_CountryRussia
#undef cids_CountryRussia
#endif //cids_CountryRussia
#ifdef cids_CountryRussia_CONSTANT
#undef cids_CountryRussia_CONSTANT
#endif //cids_CountryRussia_CONSTANT
#ifdef cids_CountrySerbia
#undef cids_CountrySerbia
#endif //cids_CountrySerbia
#ifdef cids_CountrySerbia_CONSTANT
#undef cids_CountrySerbia_CONSTANT
#endif //cids_CountrySerbia_CONSTANT
#ifdef cids_CountrySlovakia
#undef cids_CountrySlovakia
#endif //cids_CountrySlovakia
#ifdef cids_CountrySlovakia_CONSTANT
#undef cids_CountrySlovakia_CONSTANT
#endif //cids_CountrySlovakia_CONSTANT
#ifdef cids_CountrySlovenia
#undef cids_CountrySlovenia
#endif //cids_CountrySlovenia
#ifdef cids_CountrySlovenia_CONSTANT
#undef cids_CountrySlovenia_CONSTANT
#endif //cids_CountrySlovenia_CONSTANT
#ifdef cids_CountrySpain
#undef cids_CountrySpain
#endif //cids_CountrySpain
#ifdef cids_CountrySpain_CONSTANT
#undef cids_CountrySpain_CONSTANT
#endif //cids_CountrySpain_CONSTANT
#ifdef cids_CountrySweden
#undef cids_CountrySweden
#endif //cids_CountrySweden
#ifdef cids_CountrySweden_CONSTANT
#undef cids_CountrySweden_CONSTANT
#endif //cids_CountrySweden_CONSTANT
#ifdef cids_CountrySwitzerland
#undef cids_CountrySwitzerland
#endif //cids_CountrySwitzerland
#ifdef cids_CountrySwitzerland_CONSTANT
#undef cids_CountrySwitzerland_CONSTANT
#endif //cids_CountrySwitzerland_CONSTANT
#ifdef cids_CountryTurkey
#undef cids_CountryTurkey
#endif //cids_CountryTurkey
#ifdef cids_CountryTurkey_CONSTANT
#undef cids_CountryTurkey_CONSTANT
#endif //cids_CountryTurkey_CONSTANT
#ifdef cids_CountryUK
#undef cids_CountryUK
#endif //cids_CountryUK
#ifdef cids_CountryUK_CONSTANT
#undef cids_CountryUK_CONSTANT
#endif //cids_CountryUK_CONSTANT
#ifdef cids_CountryUkraine
#undef cids_CountryUkraine
#endif //cids_CountryUkraine
#ifdef cids_CountryUkraine_CONSTANT
#undef cids_CountryUkraine_CONSTANT
#endif //cids_CountryUkraine_CONSTANT
#ifdef srtdbids_EitFollowActual
#undef srtdbids_EitFollowActual
#endif //srtdbids_EitFollowActual
#ifdef srtdbids_EitFollowActual_CONSTANT
#undef srtdbids_EitFollowActual_CONSTANT
#endif //srtdbids_EitFollowActual_CONSTANT
#ifdef srtdbids_EitFollowOther
#undef srtdbids_EitFollowOther
#endif //srtdbids_EitFollowOther
#ifdef srtdbids_EitFollowOther_CONSTANT
#undef srtdbids_EitFollowOther_CONSTANT
#endif //srtdbids_EitFollowOther_CONSTANT
#ifdef srtdbids_EitLinkageInfo
#undef srtdbids_EitLinkageInfo
#endif //srtdbids_EitLinkageInfo
#ifdef srtdbids_EitLinkageInfo_CONSTANT
#undef srtdbids_EitLinkageInfo_CONSTANT
#endif //srtdbids_EitLinkageInfo_CONSTANT
#ifdef srtdbids_EitPresentActual
#undef srtdbids_EitPresentActual
#endif //srtdbids_EitPresentActual
#ifdef srtdbids_EitPresentActual_CONSTANT
#undef srtdbids_EitPresentActual_CONSTANT
#endif //srtdbids_EitPresentActual_CONSTANT
#ifdef srtdbids_EitPresentOther
#undef srtdbids_EitPresentOther
#endif //srtdbids_EitPresentOther
#ifdef srtdbids_EitPresentOther_CONSTANT
#undef srtdbids_EitPresentOther_CONSTANT
#endif //srtdbids_EitPresentOther_CONSTANT
#ifdef srtdbids_EitScheduleActual
#undef srtdbids_EitScheduleActual
#endif //srtdbids_EitScheduleActual
#ifdef srtdbids_EitScheduleActual_CONSTANT
#undef srtdbids_EitScheduleActual_CONSTANT
#endif //srtdbids_EitScheduleActual_CONSTANT
#ifdef srtdbids_EitScheduleOther
#undef srtdbids_EitScheduleOther
#endif //srtdbids_EitScheduleOther
#ifdef srtdbids_EitScheduleOther_CONSTANT
#undef srtdbids_EitScheduleOther_CONSTANT
#endif //srtdbids_EitScheduleOther_CONSTANT
#ifdef srtdbids_LinkageInfoMain
#undef srtdbids_LinkageInfoMain
#endif //srtdbids_LinkageInfoMain
#ifdef srtdbids_LinkageInfoMain_CONSTANT
#undef srtdbids_LinkageInfoMain_CONSTANT
#endif //srtdbids_LinkageInfoMain_CONSTANT
#ifdef srtdbids_NitCableDSMain
#undef srtdbids_NitCableDSMain
#endif //srtdbids_NitCableDSMain
#ifdef srtdbids_NitCableDSMain_CONSTANT
#undef srtdbids_NitCableDSMain_CONSTANT
#endif //srtdbids_NitCableDSMain_CONSTANT
#ifdef srtdbids_NitCableDSSub
#undef srtdbids_NitCableDSSub
#endif //srtdbids_NitCableDSSub
#ifdef srtdbids_NitCableDSSub_CONSTANT
#undef srtdbids_NitCableDSSub_CONSTANT
#endif //srtdbids_NitCableDSSub_CONSTANT
#ifdef srtdbids_NitFreqList
#undef srtdbids_NitFreqList
#endif //srtdbids_NitFreqList
#ifdef srtdbids_NitFreqList_CONSTANT
#undef srtdbids_NitFreqList_CONSTANT
#endif //srtdbids_NitFreqList_CONSTANT
#ifdef srtdbids_NitHDSLcnTableMain
#undef srtdbids_NitHDSLcnTableMain
#endif //srtdbids_NitHDSLcnTableMain
#ifdef srtdbids_NitHDSLcnTableMain_CONSTANT
#undef srtdbids_NitHDSLcnTableMain_CONSTANT
#endif //srtdbids_NitHDSLcnTableMain_CONSTANT
#ifdef srtdbids_NitHDSLcnTableSub
#undef srtdbids_NitHDSLcnTableSub
#endif //srtdbids_NitHDSLcnTableSub
#ifdef srtdbids_NitHDSLcnTableSub_CONSTANT
#undef srtdbids_NitHDSLcnTableSub_CONSTANT
#endif //srtdbids_NitHDSLcnTableSub_CONSTANT
#ifdef srtdbids_NitLcn2TableMain
#undef srtdbids_NitLcn2TableMain
#endif //srtdbids_NitLcn2TableMain
#ifdef srtdbids_NitLcn2TableMain_CONSTANT
#undef srtdbids_NitLcn2TableMain_CONSTANT
#endif //srtdbids_NitLcn2TableMain_CONSTANT
#ifdef srtdbids_NitLcn2TableSub
#undef srtdbids_NitLcn2TableSub
#endif //srtdbids_NitLcn2TableSub
#ifdef srtdbids_NitLcn2TableSub_CONSTANT
#undef srtdbids_NitLcn2TableSub_CONSTANT
#endif //srtdbids_NitLcn2TableSub_CONSTANT
#ifdef srtdbids_NitLcnTableMain
#undef srtdbids_NitLcnTableMain
#endif //srtdbids_NitLcnTableMain
#ifdef srtdbids_NitLcnTableMain_CONSTANT
#undef srtdbids_NitLcnTableMain_CONSTANT
#endif //srtdbids_NitLcnTableMain_CONSTANT
#ifdef srtdbids_NitLcnTableSub
#undef srtdbids_NitLcnTableSub
#endif //srtdbids_NitLcnTableSub
#ifdef srtdbids_NitLcnTableSub_CONSTANT
#undef srtdbids_NitLcnTableSub_CONSTANT
#endif //srtdbids_NitLcnTableSub_CONSTANT
#ifdef srtdbids_NitLinkageInfoMain
#undef srtdbids_NitLinkageInfoMain
#endif //srtdbids_NitLinkageInfoMain
#ifdef srtdbids_NitLinkageInfoMain_CONSTANT
#undef srtdbids_NitLinkageInfoMain_CONSTANT
#endif //srtdbids_NitLinkageInfoMain_CONSTANT
#ifdef srtdbids_NitLinkageInfoSub
#undef srtdbids_NitLinkageInfoSub
#endif //srtdbids_NitLinkageInfoSub
#ifdef srtdbids_NitLinkageInfoSub_CONSTANT
#undef srtdbids_NitLinkageInfoSub_CONSTANT
#endif //srtdbids_NitLinkageInfoSub_CONSTANT
#ifdef srtdbids_NitOtherNetworkIdTable
#undef srtdbids_NitOtherNetworkIdTable
#endif //srtdbids_NitOtherNetworkIdTable
#ifdef srtdbids_NitOtherNetworkIdTable_CONSTANT
#undef srtdbids_NitOtherNetworkIdTable_CONSTANT
#endif //srtdbids_NitOtherNetworkIdTable_CONSTANT
#ifdef srtdbids_NitSrvcAtrbTableMain
#undef srtdbids_NitSrvcAtrbTableMain
#endif //srtdbids_NitSrvcAtrbTableMain
#ifdef srtdbids_NitSrvcAtrbTableMain_CONSTANT
#undef srtdbids_NitSrvcAtrbTableMain_CONSTANT
#endif //srtdbids_NitSrvcAtrbTableMain_CONSTANT
#ifdef srtdbids_NitSrvclstTableMain
#undef srtdbids_NitSrvclstTableMain
#endif //srtdbids_NitSrvclstTableMain
#ifdef srtdbids_NitSrvclstTableMain_CONSTANT
#undef srtdbids_NitSrvclstTableMain_CONSTANT
#endif //srtdbids_NitSrvclstTableMain_CONSTANT
#ifdef srtdbids_NitSrvclstTableSub
#undef srtdbids_NitSrvclstTableSub
#endif //srtdbids_NitSrvclstTableSub
#ifdef srtdbids_NitSrvclstTableSub_CONSTANT
#undef srtdbids_NitSrvclstTableSub_CONSTANT
#endif //srtdbids_NitSrvclstTableSub_CONSTANT
#ifdef srtdbids_NitTargetRegion
#undef srtdbids_NitTargetRegion
#endif //srtdbids_NitTargetRegion
#ifdef srtdbids_NitTargetRegion_CONSTANT
#undef srtdbids_NitTargetRegion_CONSTANT
#endif //srtdbids_NitTargetRegion_CONSTANT
#ifdef srtdbids_NitTargetRegionName
#undef srtdbids_NitTargetRegionName
#endif //srtdbids_NitTargetRegionName
#ifdef srtdbids_NitTargetRegionName_CONSTANT
#undef srtdbids_NitTargetRegionName_CONSTANT
#endif //srtdbids_NitTargetRegionName_CONSTANT
#ifdef srtdbids_NitTsRelocateTableMain
#undef srtdbids_NitTsRelocateTableMain
#endif //srtdbids_NitTsRelocateTableMain
#ifdef srtdbids_NitTsRelocateTableMain_CONSTANT
#undef srtdbids_NitTsRelocateTableMain_CONSTANT
#endif //srtdbids_NitTsRelocateTableMain_CONSTANT
#ifdef srtdbids_SdtTableActual
#undef srtdbids_SdtTableActual
#endif //srtdbids_SdtTableActual
#ifdef srtdbids_SdtTableActual_CONSTANT
#undef srtdbids_SdtTableActual_CONSTANT
#endif //srtdbids_SdtTableActual_CONSTANT
#ifdef srtdbids_SdtTableOther
#undef srtdbids_SdtTableOther
#endif //srtdbids_SdtTableOther
#ifdef srtdbids_SdtTableOther_CONSTANT
#undef srtdbids_SdtTableOther_CONSTANT
#endif //srtdbids_SdtTableOther_CONSTANT
#ifdef srtdbids_SdtTargetRegion
#undef srtdbids_SdtTargetRegion
#endif //srtdbids_SdtTargetRegion
#ifdef srtdbids_SdtTargetRegion_CONSTANT
#undef srtdbids_SdtTargetRegion_CONSTANT
#endif //srtdbids_SdtTargetRegion_CONSTANT
#ifdef srtdbids_TotTableMain
#undef srtdbids_TotTableMain
#endif //srtdbids_TotTableMain
#ifdef srtdbids_TotTableMain_CONSTANT
#undef srtdbids_TotTableMain_CONSTANT
#endif //srtdbids_TotTableMain_CONSTANT
#ifdef div_ChannelNameLength
#undef div_ChannelNameLength
#endif //div_ChannelNameLength
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
#ifdef INVALID_REGION_DEPTH
#undef INVALID_REGION_DEPTH
#endif //INVALID_REGION_DEPTH
#ifdef GETINDEX(p)
#undef GETINDEX(p)
#endif //GETINDEX(p)
#endif //LOCAL_UNDEFINES
