#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <svpat.h>

#define            MAX_MAIN_SORT (56)

#define            MAX_THIRD_PROGRAM_SORT (10)

#define            MAX_THIRD_PROGRAM_SORT_UK (19)

#define            MAX_THIRD_PROGRAM_SORT_POLAND (13)

/* Preset name length is fixed as per standard so should not depend on diversity */
/* This should change only when there is a change in the standards               */

#define            PRESET_NAME_LENTH    (5) 

#define            MALLOC   (mem_iPresent_CONSTANT)

#define            EMPTY (0)

#define            validSortTable(t)        ( (t) != NULL )

#define            PdcTableSelect  (0)

#define            VpsTableSelect  (1)

#define            NiTableSelect   (2)
/* Reserved positions for channels w.r.t Country */

#define            AustriaReservedLocations (2)

#define            BelgiumReservedLocations (2) 

#define            CzechReservedLocations   (2) 

#define            DenmarkReservedLocations (2) 

#define            FinlandReservedLocations (2) 

#define            FranceReservedLocations  (6) 

#define            GermanyReservedLocations (2) 

#define            GreeceReservedLocations  (3) 

#define            HungaryReservedLocations (2) 

#define            IrelandReservedLocations (4)

#define            ItalyReservedLocations   (6)

#define            LuxembourgReservedLocations (2)

#define            NetherlandsReservedLocations (3)

#define            NorwayReservedLocations (2)

#define            PolandReservedLocations (2)

#define            PortugalReservedLocations (2)

#define            SlovakiaReservedLocations (2)

#define            SloveniaReservedLocations (3)

#define            SpainReservedLocations (2)

#define            SwedenReservedLocations (2)

#define            SwitzerlandReservedLocations (2)

#define            TurkeyReservedLocations (2)

#define            UKReservedLocations (5)

typedef enum
{ 
    programTypePdcVpsMainsort = 0 
        ,programTypePdcVpsThirdProgarmSort
        ,programTypeKnownPdcVpsStation
        ,programTypeUknownPdcVpsStation
        ,programTypeNonPdcVpsStation
        ,programTypeDoubleStation
} programType;
#if MALLOC

#else

#ifndef __cplusplus

#else

#endif

#endif

#ifndef __cplusplus

#else

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int maxPreset;
static int s__maxPreset;
Nat8 presetname[PRESET_NAME_LENTH];
static Nat8 s__presetname[PRESET_NAME_LENTH];
Nat8 cniName[PRESET_NAME_LENTH];
static Nat8 s__cniName[PRESET_NAME_LENTH];
Nat8 nrKnownPdcVpsStation ;
static Nat8 s__nrKnownPdcVpsStation ;
Nat8 nrUnknownPdcVpsStation;
static Nat8 s__nrUnknownPdcVpsStation;
Nat8 nrNonPdcVpsStation ;
static Nat8 s__nrNonPdcVpsStation ;
Nat8 nrDoubleStation ;
static Nat8 s__nrDoubleStation ;
Nat8 doubleStation ;
static Nat8 s__doubleStation ;
Nat8 otherProgarm ;
static Nat8 s__otherProgarm ;
Nat8 firstThirdProgram;
static Nat8 s__firstThirdProgram;
Nat8 currentThirdProgarmPosition;
static Nat8 s__currentThirdProgarmPosition;
#if MALLOC

Nat8 *           mallocedMemory;
static Nat8 *           s__mallocedMemory;
Nat8 *           mainSortList;
static Nat8 *           s__mainSortList;
Nat8 *           thirdProgramList;
static Nat8 *           s__thirdProgramList;
Nat8 *           knownPdcVpsStationList;
static Nat8 *           s__knownPdcVpsStationList;
Nat8 *           unKnownPdcVpsStationList;
static Nat8 *           s__unKnownPdcVpsStationList;
Nat8 *           nonPdcVpsStationList;
static Nat8 *           s__nonPdcVpsStationList;
Nat8 *           doubleStationList;
static Nat8 *           s__doubleStationList;
int *            presetNameAttrib;
static int *            s__presetNameAttrib;
#else

Nat8 mainSortList[ MAX_MAIN_SORT ];
static Nat8 s__mainSortList[ MAX_MAIN_SORT ];
Nat8 thirdProgramList[ MAX_THIRD_PROGRAM_SORT_UK ];
static Nat8 s__thirdProgramList[ MAX_THIRD_PROGRAM_SORT_UK ];
#ifndef __cplusplus

Nat8 knownPdcVpsStationList[div_MaxPresets  ];
static Nat8 s__knownPdcVpsStationList[div_MaxPresets  ];
Nat8 unKnownPdcVpsStationList[div_MaxPresets ];
static Nat8 s__unKnownPdcVpsStationList[div_MaxPresets ];
Nat8 nonPdcVpsStationList[div_MaxPresets  ];
static Nat8 s__nonPdcVpsStationList[div_MaxPresets  ];
Nat8 doubleStationList[div_MaxPresets ];
static Nat8 s__doubleStationList[div_MaxPresets ];
int presetNameAttrib[div_MaxPresets];
static int s__presetNameAttrib[div_MaxPresets];
#else

Nat8 knownPdcVpsStationList[ICesPatsDiv_MaxPresets  ];
static Nat8 s__knownPdcVpsStationList[ICesPatsDiv_MaxPresets  ];
Nat8 unKnownPdcVpsStationList[ICesPatsDiv_MaxPresets ];
static Nat8 s__unKnownPdcVpsStationList[ICesPatsDiv_MaxPresets ];
Nat8 nonPdcVpsStationList[ICesPatsDiv_MaxPresets  ];
static Nat8 s__nonPdcVpsStationList[ICesPatsDiv_MaxPresets  ];
Nat8 doubleStationList[ICesPatsDiv_MaxPresets ];
static Nat8 s__doubleStationList[ICesPatsDiv_MaxPresets ];
int presetNameAttrib[ICesPatsDiv_MaxPresets];
static int s__presetNameAttrib[ICesPatsDiv_MaxPresets];
#endif

#endif

Bool mainOrThirdPresent;
static Bool s__mainOrThirdPresent;
Nat8 nbOfReservedLocation;
static Nat8 s__nbOfReservedLocation;
Bool nonVpsPdcSpecialSort;
static Bool s__nonVpsPdcSpecialSort;
Nat8 NUMBER_OF_THIRD_PROGRAMS;
static Nat8 s__NUMBER_OF_THIRD_PROGRAMS;
PresetName currentNameAttrib;
static PresetName s__currentNameAttrib;
#ifndef __cplusplus

Nat8 PresetIndex[div_MaxPresets];
static Nat8 s__PresetIndex[div_MaxPresets];
#else

Nat8 PresetIndex[ICesPatsDiv_MaxPresets];
static Nat8 s__PresetIndex[ICesPatsDiv_MaxPresets];
#endif

HsvPresetSortData *   PresetData;
static HsvPresetSortData *   s__PresetData;
Bool validateData( Nat16 cni,Bool ardBit,
        PresetName *presetnameattrib,
        char  *presetnamestring,
        int   Local_tableSelection,
        int   sizeOfTable);
void storeNameAttrib(void)
    /**************************************
      Stores the  Preset Name and Preset 
      attrib to the temporaray memory
     **************************************/;
Nat8 entryPosition(   PresetName pn
        ,  PresetName ROM *tbl
        ,  Nat8   maxSort
        );
void updateOtherListCheckDouble(  Nat8      *nr
        , Nat8       pi
        , Nat8      *list
        , Nat8      *preset
        , programType        *pt
        , Nat8       maxSort
        );
void updateSortListCheckDouble(  Nat8      pr
        , Nat8      pi
        , Nat8      *list
        , Nat8      *opreset
        , Nat8      *dpreset
        , programType        *pt
        , Nat8      maxSort
        );
void conCatListToList( Nat8    nrFromList
        , Nat8   *nrToList
        , Nat8   *fromList
        , Nat8   *toList
        , Nat8    startPoint 
        );
Bool topOfList(   Nat8  *list
        , Nat8   listLen
        , Nat8  *first
        , Nat8  *currentPosition
        );
void calculateEntryPosType(   PresetName          prname
        , PresetName ROM     *tbl
        , PresetName ROM     *thirdtbl
        , Nat8               *pos
        , Nat8               *thirdpos
        , programType        *pt
        , Bool                IsCniNumber
        );
void sortWithInGroup(Nat8 *list ,Nat8 elements)
    /*****************************************************/
    /*  Parametrs :  List of the elements passed         */
    /*               Number of members passed            */  
    /*Purpose:       Sort  within the Group              */
    /*****************************************************/;
PresetName ROM * tableSelection(void)
    /********************************************
      Returns the Priority Table
     *********************************************/;
void sortInitialisation(void)
    /*****************************/
    /* Initialisation of lists   */
    /*****************************/;
void sortAndList( int maxpreset )
    /********************************************************/
    /* Parameters :   Maxpreset                             */
    /* Purpose    : sorts the  preset list                  */
    /*                                                      */
    /********************************************************/;
Nat8 sortMergeList(int maxpreset)
    /*******************************************/
    /*    Sorting & Merging                    */
    /*******************************************/;
Nat8 * presetNameString( PresetName p )
    /*******************************************************
     * copies name from table in ROM
     *******************************************************/;
Bool GetPresetDataIndicator( int prNo, Nat8 mask )
    /****************************************************/
    /*  Gets bits in the indicator byte                 */ 
    /****************************************************/;
void AllocateMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases any memory which has been malloced 
     and mallocs again
     ****************************************************/;
void ReleaseMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases the memory which has been malloced
     ****************************************************/;
void module__init(void){
	maxPreset	=	s__maxPreset;
	memcpy((void*)presetname,(void*)s__presetname,sizeof(presetname));
	memcpy((void*)cniName,(void*)s__cniName,sizeof(cniName));
	nrKnownPdcVpsStation	=	s__nrKnownPdcVpsStation;
	nrUnknownPdcVpsStation	=	s__nrUnknownPdcVpsStation;
	nrNonPdcVpsStation	=	s__nrNonPdcVpsStation;
	nrDoubleStation	=	s__nrDoubleStation;
	doubleStation	=	s__doubleStation;
	otherProgarm	=	s__otherProgarm;
	firstThirdProgram	=	s__firstThirdProgram;
	currentThirdProgarmPosition	=	s__currentThirdProgarmPosition;
#if MALLOC

	mallocedMemory	=	s__mallocedMemory;
	mainSortList	=	s__mainSortList;
	thirdProgramList	=	s__thirdProgramList;
	knownPdcVpsStationList	=	s__knownPdcVpsStationList;
	unKnownPdcVpsStationList	=	s__unKnownPdcVpsStationList;
	nonPdcVpsStationList	=	s__nonPdcVpsStationList;
	doubleStationList	=	s__doubleStationList;
	presetNameAttrib	=	s__presetNameAttrib;
#else

	memcpy((void*)mainSortList,(void*)s__mainSortList,sizeof(mainSortList));
	memcpy((void*)thirdProgramList,(void*)s__thirdProgramList,sizeof(thirdProgramList));
#ifndef __cplusplus

	memcpy((void*)knownPdcVpsStationList,(void*)s__knownPdcVpsStationList,sizeof(knownPdcVpsStationList));
	memcpy((void*)unKnownPdcVpsStationList,(void*)s__unKnownPdcVpsStationList,sizeof(unKnownPdcVpsStationList));
	memcpy((void*)nonPdcVpsStationList,(void*)s__nonPdcVpsStationList,sizeof(nonPdcVpsStationList));
	memcpy((void*)doubleStationList,(void*)s__doubleStationList,sizeof(doubleStationList));
	memcpy((void*)presetNameAttrib,(void*)s__presetNameAttrib,sizeof(presetNameAttrib));
#else

	memcpy((void*)knownPdcVpsStationList,(void*)s__knownPdcVpsStationList,sizeof(knownPdcVpsStationList));
	memcpy((void*)unKnownPdcVpsStationList,(void*)s__unKnownPdcVpsStationList,sizeof(unKnownPdcVpsStationList));
	memcpy((void*)nonPdcVpsStationList,(void*)s__nonPdcVpsStationList,sizeof(nonPdcVpsStationList));
	memcpy((void*)doubleStationList,(void*)s__doubleStationList,sizeof(doubleStationList));
	memcpy((void*)presetNameAttrib,(void*)s__presetNameAttrib,sizeof(presetNameAttrib));
#endif

#endif

	mainOrThirdPresent	=	s__mainOrThirdPresent;
	nbOfReservedLocation	=	s__nbOfReservedLocation;
	nonVpsPdcSpecialSort	=	s__nonVpsPdcSpecialSort;
	NUMBER_OF_THIRD_PROGRAMS	=	s__NUMBER_OF_THIRD_PROGRAMS;
	currentNameAttrib	=	s__currentNameAttrib;
#ifndef __cplusplus

	memcpy((void*)PresetIndex,(void*)s__PresetIndex,sizeof(PresetIndex));
#else

	memcpy((void*)PresetIndex,(void*)s__PresetIndex,sizeof(PresetIndex));
#endif

	PresetData	=	s__PresetData;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MAX_MAIN_SORT
#undef MAX_MAIN_SORT
#endif //MAX_MAIN_SORT
#ifdef MAX_THIRD_PROGRAM_SORT
#undef MAX_THIRD_PROGRAM_SORT
#endif //MAX_THIRD_PROGRAM_SORT
#ifdef MAX_THIRD_PROGRAM_SORT_UK
#undef MAX_THIRD_PROGRAM_SORT_UK
#endif //MAX_THIRD_PROGRAM_SORT_UK
#ifdef MAX_THIRD_PROGRAM_SORT_POLAND
#undef MAX_THIRD_PROGRAM_SORT_POLAND
#endif //MAX_THIRD_PROGRAM_SORT_POLAND
#ifdef PRESET_NAME_LENTH
#undef PRESET_NAME_LENTH
#endif //PRESET_NAME_LENTH
#ifdef MALLOC
#undef MALLOC
#endif //MALLOC
#ifdef EMPTY
#undef EMPTY
#endif //EMPTY
#ifdef validSortTable(t)
#undef validSortTable(t)
#endif //validSortTable(t)
#ifdef PdcTableSelect
#undef PdcTableSelect
#endif //PdcTableSelect
#ifdef VpsTableSelect
#undef VpsTableSelect
#endif //VpsTableSelect
#ifdef NiTableSelect
#undef NiTableSelect
#endif //NiTableSelect
#ifdef AustriaReservedLocations
#undef AustriaReservedLocations
#endif //AustriaReservedLocations
#ifdef BelgiumReservedLocations
#undef BelgiumReservedLocations
#endif //BelgiumReservedLocations
#ifdef CzechReservedLocations
#undef CzechReservedLocations
#endif //CzechReservedLocations
#ifdef DenmarkReservedLocations
#undef DenmarkReservedLocations
#endif //DenmarkReservedLocations
#ifdef FinlandReservedLocations
#undef FinlandReservedLocations
#endif //FinlandReservedLocations
#ifdef FranceReservedLocations
#undef FranceReservedLocations
#endif //FranceReservedLocations
#ifdef GermanyReservedLocations
#undef GermanyReservedLocations
#endif //GermanyReservedLocations
#ifdef GreeceReservedLocations
#undef GreeceReservedLocations
#endif //GreeceReservedLocations
#ifdef HungaryReservedLocations
#undef HungaryReservedLocations
#endif //HungaryReservedLocations
#ifdef IrelandReservedLocations
#undef IrelandReservedLocations
#endif //IrelandReservedLocations
#ifdef ItalyReservedLocations
#undef ItalyReservedLocations
#endif //ItalyReservedLocations
#ifdef LuxembourgReservedLocations
#undef LuxembourgReservedLocations
#endif //LuxembourgReservedLocations
#ifdef NetherlandsReservedLocations
#undef NetherlandsReservedLocations
#endif //NetherlandsReservedLocations
#ifdef NorwayReservedLocations
#undef NorwayReservedLocations
#endif //NorwayReservedLocations
#ifdef PolandReservedLocations
#undef PolandReservedLocations
#endif //PolandReservedLocations
#ifdef PortugalReservedLocations
#undef PortugalReservedLocations
#endif //PortugalReservedLocations
#ifdef SlovakiaReservedLocations
#undef SlovakiaReservedLocations
#endif //SlovakiaReservedLocations
#ifdef SloveniaReservedLocations
#undef SloveniaReservedLocations
#endif //SloveniaReservedLocations
#ifdef SpainReservedLocations
#undef SpainReservedLocations
#endif //SpainReservedLocations
#ifdef SwedenReservedLocations
#undef SwedenReservedLocations
#endif //SwedenReservedLocations
#ifdef SwitzerlandReservedLocations
#undef SwitzerlandReservedLocations
#endif //SwitzerlandReservedLocations
#ifdef TurkeyReservedLocations
#undef TurkeyReservedLocations
#endif //TurkeyReservedLocations
#ifdef UKReservedLocations
#undef UKReservedLocations
#endif //UKReservedLocations
#endif //LOCAL_UNDEFINES
