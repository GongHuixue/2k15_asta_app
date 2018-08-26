#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <stdlib.h>

#include <sys/stat.h>

#define 	INVALID_INDEX		(-1)

#define	INVALID_PRESET		(0xFFFF)

#define	SAT_INFO_TABLE		(pgdb_GetCurrentTable() | pgdbconst_SatInfo)

#define	SERVICE_TABLE		(pgdb_GetCurrentTable() | pgdbconst_DigitalService)

#define	PRESET_TABLE		(pgdb_GetCurrentTable() | pgdbconst_Preset)

#define 	INVALID_PACKAGE_ID	(-1)

#define 	NO_SORTING_PACKAGE_ID (0) /*TODO: initialize with the interface value once it is available.*/

#define	RANKING_LIST_STATIC (0) /*TODO: Remove the code under this macro for dynamic ranking lists*/

#define	BIN_FILE_NAME_LENGTH	100

#define	BIN_FILE_PATH	"mnt/jffs1/data/dvbs2/configdata/predefinedrankinglist"

#define FREQUENCY_TOLERANCE	(2000)

/* This is needed since there is constant difference between Fusion and Marvell 2k14 */
#define	MAP_PREDEFINEDLIST_POLARIZATION(Polarization)	((Polarization==1)?0:1)

typedef enum
{
	SORTING_START = 0,
	SORTING_PROCESS,
	SORTING_END
}SORTING_HANDLER_ENUM;
typedef struct  staticlist
{
	int    Rank;
	Nat32  Frequency;
	int    Polarisation;
	Nat16  ServiceId;
	Nat16  OriginalNetworkId;
	Nat16  Tsid;
	int   OrbitalPostion;
}RANKING_LIST_NODE;
typedef struct  header
{
	int    NoOfNodes; /*No. of entries*/
}RANKING_LIST_HEADER;
typedef struct currentlist
{
	Nat32 PackageIndex;
	Nat32 NoofServices;
	RANKING_LIST_NODE *StartNode;
}RANKING_LIST_DATA;
typedef enum
{
	FAILURE = 0,
	SUCCESS
}RESULT;
#define CHECK_IF_TURKEY_PREDEFINEDLIST(PackageIndex) ((PackageIndex == DSMART_TURKSAT_HOTBIRD_PACKAGE_ID) || (PackageIndex == DSMART_TURKSAT_PACKAGE_ID) || (PackageIndex == TURKEY_FTA_PACKAGE_ID))

#if RANKING_LIST_STATIC

#define RANK_ITEM(Rank,Frequency,Polarisation,ServiceId,OriginalNetworkId,Tsid,OrbitalPostion )   {Rank,Frequency,Polarisation,ServiceId,OriginalNetworkId,Tsid,OrbitalPostion}

#define GET_NO_OF_SERVICES(List) sizeof(List)/sizeof(RANKING_LIST_NODE) 

/* Aneesh: Filling with dummy values. This is not needed any longer */

typedef struct ranklistdetails
{
	int NoofServices;
	RANKING_LIST_NODE *Data; /*points to the corresponding array contains ranking list data*/
}RANKING_LIST_DETAILS;
#define NO_OF_RANKING_LISTS 12

#endif

/****************************************************************************
 * Static functions
 ****************************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump Sortingpmp;
static Pump s__Sortingpmp;
int SortingCount;
static int s__SortingCount;
int EndOfDummyPreset;
static int s__EndOfDummyPreset;
RANKING_LIST_DATA CurrentRankingList;
static RANKING_LIST_DATA s__CurrentRankingList;
#if RANKING_LIST_STATIC

RANKING_LIST_NODE GermanHDPlusList[500];
static RANKING_LIST_NODE s__GermanHDPlusList[500];
RANKING_LIST_NODE GermanFTAList[500];
static RANKING_LIST_NODE s__GermanFTAList[500];
RANKING_LIST_NODE AustriaList[500];
static RANKING_LIST_NODE s__AustriaList[500];
RANKING_LIST_NODE SwissFrenchList[500];
static RANKING_LIST_NODE s__SwissFrenchList[500];
RANKING_LIST_NODE SwissGermanList[500];
static RANKING_LIST_NODE s__SwissGermanList[500];
RANKING_LIST_NODE NITINeoVisionList[500];
static RANKING_LIST_NODE s__NITINeoVisionList[500];
RANKING_LIST_NODE CyfraPlusList[500];
static RANKING_LIST_NODE s__CyfraPlusList[500];
RANKING_LIST_NODE CyfrowyPolsatList[500];
static RANKING_LIST_NODE s__CyfrowyPolsatList[500];
RANKING_LIST_NODE DigiturkEutelsatList[500];
static RANKING_LIST_NODE s__DigiturkEutelsatList[500];
RANKING_LIST_NODE DigiturkTurkSatList[500];
static RANKING_LIST_NODE s__DigiturkTurkSatList[500];
RANKING_LIST_NODE DSmartTurkSatHotbirdList[500];
static RANKING_LIST_NODE s__DSmartTurkSatHotbirdList[500];
RANKING_LIST_NODE DSmartTurkSatList[500];
static RANKING_LIST_NODE s__DSmartTurkSatList[500];
RANKING_LIST_DETAILS RankingListsDetails[NO_OF_RANKING_LISTS];
static RANKING_LIST_DETAILS s__RankingListsDetails[NO_OF_RANKING_LISTS];
#endif

/****************************************************************************
 * Static functions
 ****************************************************************************/

void SortingHandler( int event, Nat32 Param2 );
Bool mStartAssignStaticRank(void);
Bool CheckGivenServiceMatchedSortingList ( HsvPgdatDigServiceData *svcdat );
void AddPresetwithDigitalServiceData ( HsvPgdatDigServiceData *svcdat );
Bool CheckServiceMatchedWithRanking( HsvPgdatDigServiceData *ptempsvcdat,RANKING_LIST_NODE   *TempRankList );
Bool LoadRankingList (Nat32 PackageIndex );
RESULT FileRead(int Start, int Bytes, void *Buff, char *file);
int GetLargestPresetInList(void);
void module__init(void){
	Sortingpmp	=	s__Sortingpmp;
	SortingCount	=	s__SortingCount;
	EndOfDummyPreset	=	s__EndOfDummyPreset;
	CurrentRankingList	=	s__CurrentRankingList;
#if RANKING_LIST_STATIC

	memcpy((void*)GermanHDPlusList,(void*)s__GermanHDPlusList,sizeof(GermanHDPlusList));
	memcpy((void*)GermanFTAList,(void*)s__GermanFTAList,sizeof(GermanFTAList));
	memcpy((void*)AustriaList,(void*)s__AustriaList,sizeof(AustriaList));
	memcpy((void*)SwissFrenchList,(void*)s__SwissFrenchList,sizeof(SwissFrenchList));
	memcpy((void*)SwissGermanList,(void*)s__SwissGermanList,sizeof(SwissGermanList));
	memcpy((void*)NITINeoVisionList,(void*)s__NITINeoVisionList,sizeof(NITINeoVisionList));
	memcpy((void*)CyfraPlusList,(void*)s__CyfraPlusList,sizeof(CyfraPlusList));
	memcpy((void*)CyfrowyPolsatList,(void*)s__CyfrowyPolsatList,sizeof(CyfrowyPolsatList));
	memcpy((void*)DigiturkEutelsatList,(void*)s__DigiturkEutelsatList,sizeof(DigiturkEutelsatList));
	memcpy((void*)DigiturkTurkSatList,(void*)s__DigiturkTurkSatList,sizeof(DigiturkTurkSatList));
	memcpy((void*)DSmartTurkSatHotbirdList,(void*)s__DSmartTurkSatHotbirdList,sizeof(DSmartTurkSatHotbirdList));
	memcpy((void*)DSmartTurkSatList,(void*)s__DSmartTurkSatList,sizeof(DSmartTurkSatList));
	memcpy((void*)RankingListsDetails,(void*)s__RankingListsDetails,sizeof(RankingListsDetails));
#endif

/****************************************************************************
 * Static functions
 ****************************************************************************/

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef INVALID_PRESET
#undef INVALID_PRESET
#endif //INVALID_PRESET
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef INVALID_PACKAGE_ID
#undef INVALID_PACKAGE_ID
#endif //INVALID_PACKAGE_ID
#ifdef NO_SORTING_PACKAGE_ID
#undef NO_SORTING_PACKAGE_ID
#endif //NO_SORTING_PACKAGE_ID
#ifdef RANKING_LIST_STATIC
#undef RANKING_LIST_STATIC
#endif //RANKING_LIST_STATIC
#ifdef BIN_FILE_NAME_LENGTH
#undef BIN_FILE_NAME_LENGTH
#endif //BIN_FILE_NAME_LENGTH
#ifdef BIN_FILE_PATH
#undef BIN_FILE_PATH
#endif //BIN_FILE_PATH
#ifdef FREQUENCY_TOLERANCE
#undef FREQUENCY_TOLERANCE
#endif //FREQUENCY_TOLERANCE
#ifdef CHECK_IF_TURKEY_PREDEFINEDLIST(PackageIndex)
#undef CHECK_IF_TURKEY_PREDEFINEDLIST(PackageIndex)
#endif //CHECK_IF_TURKEY_PREDEFINEDLIST(PackageIndex)
#ifdef RANK_ITEM(Rank,Frequency,Polarisation,ServiceId,OriginalNetworkId,Tsid,OrbitalPostion
#undef RANK_ITEM(Rank,Frequency,Polarisation,ServiceId,OriginalNetworkId,Tsid,OrbitalPostion
#endif //RANK_ITEM(Rank,Frequency,Polarisation,ServiceId,OriginalNetworkId,Tsid,OrbitalPostion
#ifdef GET_NO_OF_SERVICES(List)
#undef GET_NO_OF_SERVICES(List)
#endif //GET_NO_OF_SERVICES(List)
#ifdef NO_OF_RANKING_LISTS
#undef NO_OF_RANKING_LISTS
#endif //NO_OF_RANKING_LISTS
#endif //LOCAL_UNDEFINES
