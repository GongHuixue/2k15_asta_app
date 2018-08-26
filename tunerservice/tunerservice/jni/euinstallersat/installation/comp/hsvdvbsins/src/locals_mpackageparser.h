#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

//#define SATELLITE_PACKAGE_LIST_FILE     "/data/data/tvserver/databases/SatellitePackageList.xml"

#define TURNED_ON                   (mModuleLifeCycle == TurnedOn)

#define	MAX_PACKAGE_GROUP_SUPPORTED		11

#define	MAX_PACKAGEID_PER_GROUP			10

#define CURRENT_SUPPORTED_PACKAGE_GROUP	9
#define CURRENT_SUPPORTED_PREDEF_PACKAGES	8
#define CURRENT_SUPPORTED_HOMING_PACKAGES	31

/* For fransat  since bouquet ids 0x550 to 0x55E, 0x070 to 0x07E, 0x130 to 0x13E have to be shown dynamically. 0x55F & 0x7F should not show to user */
/*in case a new package is added for France (which requires Dynamic package name collection) then max dynamic package should be MAX_FRANSAT_PACKAGE + new package
**New package offeset should be MAX_FRANSAT_PACKAGES, because index 0 to 44 is reserved for fransat.
**if a new package is not added for france, then offest can be maintained as FRANSAT_OFFSET
*/

#define MAX_FRANSAT_PACKAGES			45

#define MAX_DYNAMIC_PACKAGES			MAX_FRANSAT_PACKAGES

#define FRANSAT_OFFSET					0

#define MAX_PACKAGE_SUPPORTED           50  + MAX_DYNAMIC_PACKAGES

#define MAX_COUNTRIES_SUPPORTED         100

#define MAX_SATELLITES_SUPPORTED        4

#define MAX_PACKAGE_NAME_LEN            64

#define MAX_PACKAGELIST_NAME_LEN		100

#define	MAX_PACKAGE_GROUP_NAME_LEN		20

#define	INVALID_PACKAGE_ID				(65536)

#define INVALID_SAT_INDEX               0xFFFF

#define NO_SORTING_PACKAGE_ID           0 /* TODO: Correct with proper interface */

#define MAX_PREDEFBINFILE_NAME_LEN      32

#define	MANDATORY_SATELLITE				1

#define	OPTIONAL_SATELLITE				0

#define	SET_MANDATORY_SAT(Val,SatNum)		(((Val) & 0x0F) << ((SatNum) * 4))

#define	IS_MANDATORY_SAT(StoredVal,SatNum)	(((StoredVal) >> (SatNum * 4)) & 0x0F)


#define NO_SORTING_STRING               "No Sorting"

#define DEFAULT_OPERATOR_PROFILE        "CI+CAMPROFILE"

#define MIN(x,y)                        ((x > y) ? y : x)

#define SAT_INFO_TABLE                  (pgdbconst_Satellite | pgdbconst_SatInfo)

#define     SET_PKG_BLD_INS_STATE(state)        (PkgInsStatus.State = state)

#define     GET_PKG_BLD_INS_STATE               (PkgInsStatus.State)

#define     PKG_BLD_VALID_EVENT(event)      ((event >= EvPkgParseStart) && (event < EvPkgParseMax))

#define     PKG_BLD_VALID_STATE(state)          ((state >= StPkgParseIdle) && (state < StPkgMax))


#define CHK_PACKAGE_SAT_IN_FOUND_LIST(Var)          SatFound = 0;\
        for (InnerLoop = 0; InnerLoop < FoundSatelliteList.NumSatellites; InnerLoop++)\
        {\
            if (Var == FoundSatelliteList.SatelliteIndex[InnerLoop])\
            {\
                SatFound = 1;\
                break;\
            }\
        }


/* Array {0-44 : 0x70 to 0x55E}
 * => {0 : 0x71, 1 : 0x70}, {2 to 14 : 0x72 to 0x7E}
 * {15 to 29 : 0x550 to 0x55E}
 * {30 to 44 : 0x130 to 0x13E} */

#define GET_INDEX_FOR_BOUQUET_ID(BouquetId) (( BouquetId >= 0x70 && BouquetId <= 0x7E ) ? \
											(( BouquetId > 0x71) ? ( BouquetId - 0x70) : !( BouquetId - 0x70 )) : \
											(( BouquetId >= 0x550 && BouquetId <= 0x55E ) ? \
											(( BouquetId - 0x550 ) + 15) : (( BouquetId >= 0x130 && BouquetId <= 0x13E ) ?\
											(( BouquetId - 0x130 ) + 30) : MAX_DYNAMIC_PACKAGES)))

#define FIND_FRANSAT_PACKAGE(PackageId)  ( FRANSAT_PACKAGE_ID == ( PackageId&0xFFFF )  )

#define CREATE_DYNAMIC_PACKAGE_ID(PackageId,BouquetId)	( ( ( BouquetId & 0xFFFF ) << 16 ) | ( PackageId & 0xFFFF ) );
/*CR:RMCR:2884
	:Remove Legagcy Fransat Installation
	:No Need of Dynamic package Building: returning Invalid Package Id.
*/
#define GET_PACKAGE_ID(SatelliteId,CountryId,PackageId) \
	{\
		TraceDebug(m," Sat ID %d Country %d", SatelliteId, CountryId);\
		if( (EUTELSAT_5_W == SatelliteId) && (cids_CountryFrance == CountryId) )\
		{\
			PackageId = INVALID_PACKAGE_ID;\
		}\
	}\


#define ADD_PACKAGE_TO_FOUND_LIST            if(SatFound ==1)\
        {\
if(FRANSAT_PACKAGE_ID == DefaultPackageList[Count].PackageIndex)\
    		{\
    				TraceDebug(m," Fransat Faxkage detected Dynamic package count %d", NumDynamicPackagesFound);\
				if( NumDynamicPackagesFound )\
				{\
					for (InnerLoop = FRANSAT_OFFSET; InnerLoop < MAX_FRANSAT_PACKAGES; InnerLoop++)\
					{\
						TraceDebug(m," Loop index %d Dynamic package availablity %d",InnerLoop, DynamicPackageList[InnerLoop].Index);\
						if( DynamicPackageList[InnerLoop].Index )\
						{\
							FoundPackageList[NumPackagesFound].Index = NumPackagesFound;\
							FoundPackageList[NumPackagesFound].PackageId = DynamicPackageList[InnerLoop].PackageId;\
							memcpy((char*)FoundPackageList[NumPackagesFound].PackageName,DynamicPackageList[InnerLoop].PackageName, MAX_PACKAGE_NAME_LEN * sizeof(Nat16) );\
							memcpy (FoundPackageList[NumPackagesFound].PackageListName, DynamicPackageList[InnerLoop].PackageName, (MAX_PACKAGELIST_NAME_LEN * sizeof(Nat16)));\
							memcpy (FoundPackageList[NumPackagesFound].PredefinedListBinFile, DefaultPackageList[Count].PredefinedListBinFile, MAX_PREDEFBINFILE_NAME_LEN);\
							NumPackagesFound++;\
							TraceDebug(m,"Dynamic package added Number of Packages found %d",NumPackagesFound);\
						}\
					}\
				}\
    		}\
			else\
			{\
			for (tempCount=0;tempCount<NumPackagesFound;tempCount++)\
			{\
				if (FoundPackageList[tempCount].PackageId == DefaultPackageList[Count].PackageIndex)\
				{\
					break;\
				}\
			}\
			if (tempCount == NumPackagesFound) \
			{\
            FoundPackageList[NumPackagesFound].Index = NumPackagesFound;\
            FoundPackageList[NumPackagesFound].PackageId = DefaultPackageList[Count].PackageIndex;\
            memcpy (FoundPackageList[NumPackagesFound].PackageName, DefaultPackageList[Count].PackageName, (MAX_PACKAGE_NAME_LEN * sizeof(Nat16)));\
			memcpy (FoundPackageList[NumPackagesFound].PackageListName, DefaultPackageList[Count].PackageListName, (MAX_PACKAGELIST_NAME_LEN * sizeof(Nat16)));\
            memcpy (FoundPackageList[NumPackagesFound].PredefinedListBinFile, DefaultPackageList[Count].PredefinedListBinFile, MAX_PREDEFBINFILE_NAME_LEN);\
            NumPackagesFound++;\
			}\
			}\
        }

#define OP_PROFILE_PACKAGE_ID           					32
#define OP_PROFILE_ENABLED								1
#define IS_OPERATOR_PROFILE(pkgGroupId)				(pkgGroupId == OP_PROFILE_PACKAGE_ID)


typedef enum
{
    StPkgParseIdle,
    StPkgParseStart,
    StPkgParseTune,
    StPkgParseDemuxWait,
    StPkgParsePopulatePkg,
    StPkgMax
}PkgBuildStates;
typedef enum
{
    EvPkgParseStart,
    EvPkgParseTune,
    EvPkgParseLockChange,
    EvPkgParseDataAcquire,
    EvPkgParseDataAcqComplete,
    EvPkgParsePopulatePkg,
    EvPkgParseComplete,
    EvPkgParseMax
}PkgBuildEvents;
typedef enum
{
    Initialised = 0,
    TurnedOn,
    TurnedOff
}ModuleLifeCycle;
typedef	struct	PackageGroupMapping
{
	Nat16	PackageGroupId;
	Nat16	PackageId[MAX_PACKAGEID_PER_GROUP];
	Nat16	PackageGroupName[MAX_PACKAGE_GROUP_NAME_LEN];
} PackageGroupMapping;
typedef struct PackageSatelliteList 
{
    Nat16   PackageIndex;
    int     CountryIndex;
    Nat32   Satellite1;
    Nat32   Satellite2;
    Nat32   Satellite3;
    Nat32   Satellite4;
	Nat32	MandatorySatellites;		/* Each Nibble gives Mandatory/optional setting of each satellite. Eg: <Sat4>:<Sat3>:<Sat2>:<Sat1> */
    Nat16   PackageName[MAX_PACKAGE_NAME_LEN];
	Nat16   PackageListName[MAX_PACKAGELIST_NAME_LEN];
    Nat8    PredefinedListBinFile[MAX_PREDEFBINFILE_NAME_LEN];
	Nat8	SatIP;
} PackageSatelliteList;

typedef struct PackageSatelliteListTemp 
{
    Nat16   PackageIndex;
    int     CountryIndex;
	int 	IsPredefinedList;
    Nat32   Satellite1;
	Nat32	Satellite1Mandatory;
    Nat32   Satellite2;
	Nat32	Satellite2Mandatory;
    Nat32   Satellite3;
	Nat32	Satellite3Mandatory;
    Nat32   Satellite4;
	Nat32	Satellite4Mandatory;
    const char   *PackageName/*[MAX_PACKAGE_NAME_LEN]*/;
	const char   *PackageListName/*[MAX_PACKAGELIST_NAME_LEN]*/;
    const char   *PredefinedListBinFile/*[MAX_PREDEFBINFILE_NAME_LEN]*/;
} PackageSatelliteListTemp;
typedef struct FoundSatList 
{
    Nat8    NumSatellites;
    Nat32   SatelliteIndex[MAX_SATELLITES_SUPPORTED];
} FoundSatList;
typedef struct PackageParsingStatus
{
    int     State;
    Nat32    Mode;
    Nat32 CurrentLNBNumber;
    Nat32 CurrentPrescanIndex;
}TypePackageParsingStatus;
#define	SUPPORTED_COUNTRIES_IN_PACKAGE		18

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

PackageSatelliteList DefaultPackageList [MAX_PACKAGE_SUPPORTED];
static PackageSatelliteList s__DefaultPackageList [MAX_PACKAGE_SUPPORTED];
PackageGroupMapping DefaultPackageGroup [MAX_PACKAGE_GROUP_SUPPORTED];
static PackageGroupMapping s__DefaultPackageGroup [MAX_PACKAGE_GROUP_SUPPORTED];
HsvPackageStructure FoundPackageList[MAX_PACKAGE_SUPPORTED];
static HsvPackageStructure s__FoundPackageList[MAX_PACKAGE_SUPPORTED];
HsvPackageStructure DynamicPackageList[MAX_DYNAMIC_PACKAGES];
static HsvPackageStructure s__DynamicPackageList[MAX_DYNAMIC_PACKAGES];
FoundSatList FoundSatelliteList;
static FoundSatList s__FoundSatelliteList;
int NumPackagesFound;
static int s__NumPackagesFound;
int NumDynamicPackagesFound;
static int s__NumDynamicPackagesFound;
Nat32 TotalPackages,TotalPackageGroups;
static Nat32 s__TotalPackages,s__TotalPackageGroups;
Bool PackageListFound;
static Bool s__PackageListFound;
Pump mPkgBldPump;
static Pump s__mPkgBldPump;
TypePackageParsingStatus PkgInsStatus;
static TypePackageParsingStatus s__PkgInsStatus;
ModuleLifeCycle mModuleLifeCycle;
static ModuleLifeCycle s__mModuleLifeCycle;
Op_ProfileStatusInfo mOpProfileStatusInfo;
static Op_ProfileStatusInfo s__mOpProfileStatusInfo;
CIPlusStatus_e mDynamicCIPlusStatus;
static CIPlusStatus_e s__mDynamicCIPlusStatus;
int SortedCountryIds [SUPPORTED_COUNTRIES_IN_PACKAGE];
static int s__SortedCountryIds [SUPPORTED_COUNTRIES_IN_PACKAGE];
FunctionNat32 PackageBuildingActionMatrix[EvPkgParseMax][StPkgMax];
static FunctionNat32 s__PackageBuildingActionMatrix[EvPkgParseMax][StPkgMax];
void mPkgBuildPumpHandler(int event, Nat32 param);
unsigned int extractSatelliteContentValue (char *String, char HexOn, int *MandatoryFlag);
unsigned int extractContentValue (char *String, char HexOn);
void extractContentString (char *String,  char *OutputString, unsigned char MaxLen);
void mBuildPackageSatelliteList (void);
void mBuildFoundSatelliteList (void);
void mBuildDynamicPackageList(int CountryId);
void mFindNationalPackages (int CountryId, Bool IsSatIP);
void mAddNoSorting (void);
void mAddOpProfileName (void);
void mFindForeignPackages (int CountryId, Bool IsSatIP);
void mReorderOnMenuLanguage (int CountryId);
void DetermineCanalDigitalPackage (int CountryId, Bool *IsNordigCountry, Bool *IsThorDetected);
void DetermineDigiturkMduDetected (Bool *MduDetected);
void mFindCanalDigitalPackage (int CountryId);
Bool IsForeignPackageAvailable(int PackageId);
void mStopPackageParsing( void );
void FuncPkgParseStart( Nat32 param );
void FuncPkgParseCheckLockStatus(Nat32 param);
void FuncPkgParseStartTuning(Nat32 param);
void FuncPkgParseStartCollection(Nat32 param);
void FuncPkgParseStopCollection(Nat32 param);
void FuncPkgParsePopulatePackage(Nat32 param);
void FuncPkgParseComplete(Nat32 param);
void mInitOpProfileStatusInfo (void);
Bool mIsCAMInserted (void);
void module__init(void){
#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

	memcpy((void*)DefaultPackageList,(void*)s__DefaultPackageList,sizeof(DefaultPackageList));
	memcpy((void*)DefaultPackageGroup,(void*)s__DefaultPackageGroup,sizeof(DefaultPackageGroup));
	memcpy((void*)FoundPackageList,(void*)s__FoundPackageList,sizeof(FoundPackageList));
	memcpy((void*)DynamicPackageList,(void*)s__DynamicPackageList,sizeof(DynamicPackageList));
	FoundSatelliteList	=	s__FoundSatelliteList;
	NumPackagesFound	=	s__NumPackagesFound;
	NumDynamicPackagesFound	=	s__NumDynamicPackagesFound;
	TotalPackages	=	s__TotalPackages;
	TotalPackageGroups	=	s__TotalPackageGroups;
	PackageListFound	=	s__PackageListFound;
	mPkgBldPump	=	s__mPkgBldPump;
	PkgInsStatus	=	s__PkgInsStatus;
	mModuleLifeCycle	=	s__mModuleLifeCycle;
	mOpProfileStatusInfo	=	s__mOpProfileStatusInfo;
	mDynamicCIPlusStatus	=	s__mDynamicCIPlusStatus;
	memcpy((void*)SortedCountryIds,(void*)s__SortedCountryIds,sizeof(SortedCountryIds));
	memcpy((void*)PackageBuildingActionMatrix,(void*)s__PackageBuildingActionMatrix,sizeof(PackageBuildingActionMatrix));
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
#ifdef SATELLITE_PACKAGE_LIST_FILE
#undef SATELLITE_PACKAGE_LIST_FILE
#endif //SATELLITE_PACKAGE_LIST_FILE
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef MAX_PACKAGE_GROUP_SUPPORTED
#undef MAX_PACKAGE_GROUP_SUPPORTED
#endif //MAX_PACKAGE_GROUP_SUPPORTED
#ifdef MAX_PACKAGEID_PER_GROUP
#undef MAX_PACKAGEID_PER_GROUP
#endif //MAX_PACKAGEID_PER_GROUP
#ifdef MAX_FRANSAT_PACKAGES
#undef MAX_FRANSAT_PACKAGES
#endif //MAX_FRANSAT_PACKAGES
#ifdef MAX_DYNAMIC_PACKAGES
#undef MAX_DYNAMIC_PACKAGES
#endif //MAX_DYNAMIC_PACKAGES
#ifdef FRANSAT_OFFSET
#undef FRANSAT_OFFSET
#endif //FRANSAT_OFFSET
#ifdef MAX_PACKAGE_SUPPORTED
#undef MAX_PACKAGE_SUPPORTED
#endif //MAX_PACKAGE_SUPPORTED
#ifdef MAX_COUNTRIES_SUPPORTED
#undef MAX_COUNTRIES_SUPPORTED
#endif //MAX_COUNTRIES_SUPPORTED
#ifdef MAX_SATELLITES_SUPPORTED
#undef MAX_SATELLITES_SUPPORTED
#endif //MAX_SATELLITES_SUPPORTED
#ifdef MAX_PACKAGE_NAME_LEN
#undef MAX_PACKAGE_NAME_LEN
#endif //MAX_PACKAGE_NAME_LEN
#ifdef MAX_PACKAGELIST_NAME_LEN
#undef MAX_PACKAGELIST_NAME_LEN
#endif //MAX_PACKAGELIST_NAME_LEN
#ifdef MAX_PACKAGE_GROUP_NAME_LEN
#undef MAX_PACKAGE_GROUP_NAME_LEN
#endif //MAX_PACKAGE_GROUP_NAME_LEN
#ifdef INVALID_PACKAGE_ID
#undef INVALID_PACKAGE_ID
#endif //INVALID_PACKAGE_ID
#ifdef INVALID_SAT_INDEX
#undef INVALID_SAT_INDEX
#endif //INVALID_SAT_INDEX
#ifdef NO_SORTING_PACKAGE_ID
#undef NO_SORTING_PACKAGE_ID
#endif //NO_SORTING_PACKAGE_ID
#ifdef MAX_PREDEFBINFILE_NAME_LEN
#undef MAX_PREDEFBINFILE_NAME_LEN
#endif //MAX_PREDEFBINFILE_NAME_LEN
#ifdef MANDATORY_SATELLITE
#undef MANDATORY_SATELLITE
#endif //MANDATORY_SATELLITE
#ifdef OPTIONAL_SATELLITE
#undef OPTIONAL_SATELLITE
#endif //OPTIONAL_SATELLITE
#ifdef SET_MANDATORY_SAT(Val,SatNum)
#undef SET_MANDATORY_SAT(Val,SatNum)
#endif //SET_MANDATORY_SAT(Val,SatNum)
#ifdef IS_MANDATORY_SAT(StoredVal,SatNum)
#undef IS_MANDATORY_SAT(StoredVal,SatNum)
#endif //IS_MANDATORY_SAT(StoredVal,SatNum)
#ifdef NO_SORTING_STRING
#undef NO_SORTING_STRING
#endif //NO_SORTING_STRING
#ifdef MIN(x,y)
#undef MIN(x,y)
#endif //MIN(x,y)
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef SET_PKG_BLD_INS_STATE(state)
#undef SET_PKG_BLD_INS_STATE(state)
#endif //SET_PKG_BLD_INS_STATE(state)
#ifdef GET_PKG_BLD_INS_STATE
#undef GET_PKG_BLD_INS_STATE
#endif //GET_PKG_BLD_INS_STATE
#ifdef PKG_BLD_VALID_EVENT(event)
#undef PKG_BLD_VALID_EVENT(event)
#endif //PKG_BLD_VALID_EVENT(event)
#ifdef PKG_BLD_VALID_STATE(state)
#undef PKG_BLD_VALID_STATE(state)
#endif //PKG_BLD_VALID_STATE(state)
#ifdef CHK_PACKAGE_SAT_IN_FOUND_LIST(Var)
#undef CHK_PACKAGE_SAT_IN_FOUND_LIST(Var)
#endif //CHK_PACKAGE_SAT_IN_FOUND_LIST(Var)
#ifdef GET_INDEX_FOR_BOUQUET_ID(BouquetId)
#undef GET_INDEX_FOR_BOUQUET_ID(BouquetId)
#endif //GET_INDEX_FOR_BOUQUET_ID(BouquetId)
#ifdef FIND_FRANSAT_PACKAGE(PackageId)
#undef FIND_FRANSAT_PACKAGE(PackageId)
#endif //FIND_FRANSAT_PACKAGE(PackageId)
#ifdef CREATE_DYNAMIC_PACKAGE_ID(PackageId,BouquetId)
#undef CREATE_DYNAMIC_PACKAGE_ID(PackageId,BouquetId)
#endif //CREATE_DYNAMIC_PACKAGE_ID(PackageId,BouquetId)
#ifdef GET_PACKAGE_ID(SatelliteId,CountryId,PackageId)
#undef GET_PACKAGE_ID(SatelliteId,CountryId,PackageId)
#endif //GET_PACKAGE_ID(SatelliteId,CountryId,PackageId)
#ifdef ADD_PACKAGE_TO_FOUND_LIST
#undef ADD_PACKAGE_TO_FOUND_LIST
#endif //ADD_PACKAGE_TO_FOUND_LIST
#ifdef SUPPORTED_COUNTRIES_IN_PACKAGE
#undef SUPPORTED_COUNTRIES_IN_PACKAGE
#endif //SUPPORTED_COUNTRIES_IN_PACKAGE
#endif //LOCAL_UNDEFINES
