/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: svpats_m.c %
 *       %version: TVG_tv550r4dev1 %
 * %date_modified: Thu Feb 08 17:58:20 2007 %
 *    %derived_by: vijayan %
 */




#include "_svpats_m.h"

TRACESYMBOL(m, "analog/installation/svpats_m")








/* Local Declarations */
int CSvcPats_Priv::s__maxPreset;

Nat8 CSvcPats_Priv::s__presetname[PRESET_NAME_LENTH];

Nat8 CSvcPats_Priv::s__cniName[PRESET_NAME_LENTH];

Nat8 CSvcPats_Priv::s__nrKnownPdcVpsStation ;

Nat8 CSvcPats_Priv::s__nrUnknownPdcVpsStation;

Nat8 CSvcPats_Priv::s__nrNonPdcVpsStation ;

Nat8 CSvcPats_Priv::s__nrDoubleStation ;

Nat8 CSvcPats_Priv::s__doubleStation ;

Nat8 CSvcPats_Priv::s__otherProgarm ;

Nat8 CSvcPats_Priv::s__firstThirdProgram;

Nat8 CSvcPats_Priv::s__currentThirdProgarmPosition;





#if MALLOC

Nat8 *           CSvcPats_Priv::s__mallocedMemory = NULL;

Nat8 *           CSvcPats_Priv::s__mainSortList = NULL;

Nat8 *           CSvcPats_Priv::s__thirdProgramList = NULL;

Nat8 *           CSvcPats_Priv::s__knownPdcVpsStationList = NULL;

Nat8 *           CSvcPats_Priv::s__unKnownPdcVpsStationList = NULL;

Nat8 *           CSvcPats_Priv::s__nonPdcVpsStationList = NULL;

Nat8 *           CSvcPats_Priv::s__doubleStationList = NULL;

int *            CSvcPats_Priv::s__presetNameAttrib;

#else

Nat8 CSvcPats_Priv::s__mainSortList[ MAX_MAIN_SORT ];

Nat8 CSvcPats_Priv::s__thirdProgramList[ MAX_THIRD_PROGRAM_SORT_UK ];

#ifndef __cplusplus

Nat8 CSvcPats_Priv::s__knownPdcVpsStationList[div_MaxPresets  ];

Nat8 CSvcPats_Priv::s__unKnownPdcVpsStationList[div_MaxPresets ];

Nat8 CSvcPats_Priv::s__nonPdcVpsStationList[div_MaxPresets  ];

Nat8 CSvcPats_Priv::s__doubleStationList[div_MaxPresets ];

int CSvcPats_Priv::s__presetNameAttrib[div_MaxPresets];

#else

Nat8 CSvcPats_Priv::s__knownPdcVpsStationList[ICesPatsDiv_MaxPresets  ];

Nat8 CSvcPats_Priv::s__unKnownPdcVpsStationList[ICesPatsDiv_MaxPresets ];

Nat8 CSvcPats_Priv::s__nonPdcVpsStationList[ICesPatsDiv_MaxPresets  ];

Nat8 CSvcPats_Priv::s__doubleStationList[ICesPatsDiv_MaxPresets ];

int CSvcPats_Priv::s__presetNameAttrib[ICesPatsDiv_MaxPresets];

#endif

#endif


static PresetName ROM  *currentTable;

static PresetName ROM  *thirdProgramTable;

Bool CSvcPats_Priv::s__mainOrThirdPresent;

Nat8 CSvcPats_Priv::s__nbOfReservedLocation;

Bool CSvcPats_Priv::s__nonVpsPdcSpecialSort;

Nat8 CSvcPats_Priv::s__NUMBER_OF_THIRD_PROGRAMS;

PresetName CSvcPats_Priv::s__currentNameAttrib;


#ifndef __cplusplus

Nat8 CSvcPats_Priv::s__PresetIndex[div_MaxPresets];

#else

Nat8 CSvcPats_Priv::s__PresetIndex[ICesPatsDiv_MaxPresets];

#endif

HsvPresetSortData *   CSvcPats_Priv::s__PresetData;



/***********************************************/
/*    Local Function Declaration               */
/***********************************************/














/*static void SetPresetDataIndicator( int prNo, Nat8 mask, Bool bit);*/





/* -------------------------------------------------------------------------- *
   interface functions 
 * -------------------------------------------------------------------------- */
/***************************************************************
 * sorts the preset list
 ***************************************************************/
int CSvcPats_Priv::prsort_Sort (HsvPresetSortData *listOfPresetData, int sizeOfList, int numPresets)
{
    int returnVal;
    UNUSED(sizeOfList);

    PresetData = listOfPresetData;
    AllocateMemoryForPresetList();
    returnVal = sortMergeList(numPresets+1);        /*the preset data starts from preset 1 , so +1 */
    ReleaseMemoryForPresetList();
    return(returnVal);
}

/***************************************************************
 * gets the preset index
 ***************************************************************/
int CSvcPats_Priv::prsort_GetPresetIndex ( int presetNo)
{
    return(PresetIndex[presetNo]);
}

/***************************************************************
 * gets the preset index list
 ***************************************************************/
Nat8 * CSvcPats_Priv::prsort_GetPresetIndexList (int *sizeOfList)
{
    *sizeOfList = (sizeof(PresetIndex)/sizeof(PresetIndex[0]));
    return (PresetIndex);
}

/***************************************************************
Parameters : cni :  CNI or NI number on 16 bits and ard bit.
ard_bit from teletext for Vps only
Table : Pdc,Vps, Ni Table
sizeOfTable : Pdc,Vps,Ni size 
Purpose    : Validates the CNI or NI  number from the vps data
and to store the PresetNameAttrib & Name
 ***************************************************************/
Bool CSvcPats_Priv::validateData( Nat16 cni,Bool ardBit,
        PresetName *presetnameattrib,
        char  *presetnamestring,
        int   Local_tableSelection,
        int   sizeOfTable)

{
    Bool       found= FALSE;
    Nat16      count;
    Nat16      i;
    Nat16      countryNetwork;
    Nat16      nbOfNetwork;
    Nat16 ROM *ptr;


    count = 0;
    *presetnameattrib = presetNameOther;
    countryNetwork = (cni & 0xffff);
    switch(Local_tableSelection)
    {
        case PdcTableSelect:
            ptr =  &PdcCniTable[0];
            break;
        case VpsTableSelect:
            ptr =  &VpsCniTable[0];
            break;
        case NiTableSelect:
            ptr =  &NiTable[0];
            break;
        default:
            countryNetwork = 0;
            ptr = NULL;
            break;
    }
    if(countryNetwork != 0 )
    {
        while( (!found) && (count<sizeOfTable) )
        {
            nbOfNetwork = *ptr;
            ptr++;
            for( i=0; (!found )&& (i<nbOfNetwork); i++ )
            {
                found = ( countryNetwork == ptr[i] );
            }
            ptr += nbOfNetwork;
            if( found )
            {
                if( countryNetwork == 0x0DC3)      /* ARD/ZDF morning-programme */
                {
                    if( ardBit )         /* modified snehal */
                    {
                        *presetnameattrib = presetNameArd;
                    }
                    else
                    {
                        *presetnameattrib = presetNameZdf;
                    }
                }
                else
                {
                    *presetnameattrib = (PresetName)(*ptr);

                }
                str_strncpy( (char*)presetnamestring
                        , (char*)presetNameString( *presetnameattrib )
                        , PRESET_NAME_LENTH);

            }
            else
            {
                ptr++;
            }
            count += (1 + nbOfNetwork + 1);/* As per Table */ 
        }
    }
    return( found );
}

void CSvcPats_Priv::storeNameAttrib(void)
    /**************************************
      Stores the  Preset Name and Preset 
      attrib to the temporaray memory
     **************************************/  
{
    int     i;
    Bool    ard;
    Nat16   CniNi;
    Nat16   vpsCni;
    Nat16   pkt830Cni;
    Nat16   pkt830Ni;
    /*HsvCniName cniName;*/

    for( i=1;i<maxPreset;i++)
    {
        vpsCni = 0;
        pkt830Cni = 0;
        pkt830Ni = 0;
        ard = GetPresetDataIndicator(i,MASK_ARD);

        CniNi = PresetData[i].CniNi;

        /* only one indicator should be set at this time  */

        /* Poorna - Harmless assert hit because of transmission. Therefore commented*/
        /*
           ASSERT( !((GetPresetDataIndicator(i,MASK_VPS) && GetPresetDataIndicator(i,MASK_PKT830CNI))       ||
           (GetPresetDataIndicator(i,MASK_PKT830NI) && GetPresetDataIndicator(i,MASK_PKT830CNI))  ||
           (GetPresetDataIndicator(i,MASK_VPS) && GetPresetDataIndicator(i,MASK_PKT830NI))) );
           */

        if(GetPresetDataIndicator(i,MASK_VPS))
        {
            vpsCni = CniNi;
        }
        if(GetPresetDataIndicator(i,MASK_PKT830CNI))
        {
            pkt830Cni = CniNi;
        }
        if(GetPresetDataIndicator(i,MASK_PKT830NI))
        {
            pkt830Ni = CniNi;
        }
        cniname_GetPresetName (vpsCni,pkt830Cni,pkt830Ni,ard);      /* get the name attrib in currentNameAttrib */
        presetNameAttrib[i] = currentNameAttrib;
    }
}

/********************************************************/
/* Parameters : pn the presetname to be found           */
/*              tbl the table to be used                */
/*              maxSort max entry in the tbl           */
/* Purpose    : returns the defined position of preset  */
/*              name pn in table tbl. If no position    */
/*              available then 0 is returned.           */
/********************************************************/
Nat8 CSvcPats_Priv::entryPosition(   PresetName pn
        ,  PresetName ROM *tbl
        ,  Nat8   maxSort
        )

{
    Nat8          rval = 0;
    Nat8          j;
    PresetName    ln;

    if (tbl == NULL)
    {
        return (rval);
    }
    for ( j = 0; ( j < maxSort ) && ( *tbl != presetNameOther ) ; j ++ )
    {
        ln = *tbl;
        if ( ln == pn )
        {
            rval = j + 1;    /* 0 is used as stop position */
            break;    /* stop loop */
        }

        tbl++;
    }

    return( rval );
}

/********************************************************
 * Parameters : nr      number of element in the list
 *              pi      preset to store
 *              list    sorted list of preset
 *              preset  if double then preset = double preset
 *              pt      program type is double when its cni matches
 *                      another in the list
 *              maxSort max number of elements in the list.
 * Purpose    : concatenates an element to the list and check
 *              for double preset.
 ********************************************************/
void CSvcPats_Priv::updateOtherListCheckDouble(  Nat8      *nr
        , Nat8       pi
        , Nat8      *list
        , Nat8      *preset
        , programType        *pt
        , Nat8       maxSort
        )

{
    Nat8 k;

    if ((*nr <= maxSort) && (pi < div_MaxPresets ))
    {
        for ( k = 1; ( ( k < (*nr) ) && ( *pt != programTypeDoubleStation ) ); k++ )
        {
            if ( ( PresetData[ list[ k ] ].CniNi == PresetData[pi].CniNi ) &&
                    ( presetNameAttrib[ list[ k ] ] == presetNameAttrib[pi]) )
            {
                *pt = programTypeDoubleStation;

                if ( PresetData[ list[ k ] ].SignalStrength  < PresetData[ pi ].SignalStrength  )
                {
                    *preset = list[ k ];
                    list[ k ] = pi;
                }
                else if( PresetData[ list[ k ] ].SignalStrength == PresetData[ pi ].SignalStrength )
                {
                    if( PresetData[ list[k] ].Frequency < PresetData[ pi ].Frequency )
                    {
                        *preset = list[ k ];
                        list[ k ] = pi;
                    }

                }    
                else
                {
                    *preset = pi;
                }
            }
        }

        if ( ! ( (*pt) == programTypeDoubleStation ) )
        {
            list[ *nr ] = pi;
            (*nr)++;
        }
    }
}

/********************************************************
 * Parameters : pr       sort priority =sort list index+1
 *              pi       preset list index
 *              list     sorted list of preset
 *              opreset  if pi has the same presetname index, but
 *                       different cni, then opreset = second preset
 *              dpreset  if pi is a double preset, then preset = double
 *                       preset.
 *              maxSort max number of sorting entries.
 * Purpose    : updates the sort list and check for double or other preset.
 ********************************************************/
void CSvcPats_Priv::updateSortListCheckDouble(  Nat8      pr
        , Nat8      pi
        , Nat8      *list
        , Nat8      *opreset
        , Nat8      *dpreset
        , programType        *pt
        , Nat8      maxSort
        )

{
    if ( (pi < div_MaxPresets ) && (pr < maxSort ))
    {
        if ( list[ pr ] == EMPTY )
        {
            list[ pr ] =  pi ;
        }
        else
        {
            if ( (  PresetData[ list[ pr] ].CniNi == PresetData[ pi ].CniNi ) &&
                    (  presetNameAttrib[ list[ pr] ] == presetNameAttrib[pi]) )
            {
                *pt = programTypeDoubleStation;

                if (PresetData[ list[ pr ] ].SignalStrength < PresetData[  pi  ].SignalStrength )
                {
                    *dpreset = list[ pr ];
                    list[ pr ] =  pi ;
                }
                else if( PresetData[ list[ pr ] ].SignalStrength == PresetData[ pi ].SignalStrength )
                {
                    if( PresetData[ list[pr] ].Frequency < PresetData[ pi ].Frequency )
                    {
                        *dpreset = list[ pr];
                        list[ pr ] = pi;
                    }

                }

                else
                {
                    *dpreset =  pi ;
                }
            }
            else
                /* stations with the same presetname, but different cni numbers, *
                 * so different stations                                         */
            {
                *pt = programTypeKnownPdcVpsStation;
                mainOrThirdPresent= TRUE;
                if ( PresetData[  list[ pr ] ].SignalStrength < PresetData[ pi ].SignalStrength )
                {
                    *opreset = list[ pr ];
                    list[ pr ] = pi ;
                }
                else if( PresetData[ list[ pr ] ].SignalStrength == PresetData[ pi ].SignalStrength )
                {
                    if( PresetData[ list[pr] ].Frequency < PresetData[ pi ].Frequency )
                    {
                        *opreset = list[ pr ];
                        list[ pr ] = pi;
                    }

                }

                else
                {
                    *opreset =  pi ;
                }
            }
        }
    }

}

/********************************************************
 * Parameters : nrFromList  number of elements in source list
 *              nrToList    number of elements in destination list
 *              fromList     source list
 *              toList       destination list
 * Purpose    : Concatenates 1 list to the end of another list.
 ********************************************************/
void CSvcPats_Priv::conCatListToList( Nat8    nrFromList
        , Nat8   *nrToList
        , Nat8   *fromList
        , Nat8   *toList
        , Nat8    startPoint 
        )

{
    Nat8 i;
    for(i= startPoint;i<nrFromList;i++)
    {
        toList[*nrToList]=fromList[i];
        (*nrToList)++;
    }
    /*str_strncat(toList,fromList,nrFromList);
      (*nrToList) +=(nrFromList);*/
}

/********************************************************
 * Parameters : list      list
 *              listLen  max number of elements in list
 *              first     first non-empty element in list
 * Purpose    : Searches for the first item in the list.
 *              Returns true if available else false.
 ********************************************************/
Bool CSvcPats_Priv::topOfList(   Nat8  *list
        , Nat8   listLen
        , Nat8  *first
        , Nat8  *currentPosition
        )

{
    Bool found = FALSE;
    int i;

    for ( i = 1; (i < listLen) && (! found); i++ )
    {
        if ( list[ i ] != EMPTY )
        {
            found = TRUE;
            *first = list[ i ];
            *currentPosition = i+1;
        }
    }

    return ( found );

}


/********************************************************
 * Parameters : prname   presetname index
 *              tbl      main sort table
 *              thirdtbl third program sort table
 *              pos      position of presetname index
 *                       in main sort table. 0 if not found.
 *              thirdpos position of presetname index in third
 *                       program sort table. 0 if not found.
 *              st       type of program
 * Purpose    : Computes the entry position of the presetname
 *              in the main sort and third program sort table.
 ********************************************************/
void CSvcPats_Priv::calculateEntryPosType(   PresetName          prname
        , PresetName ROM     *tbl
        , PresetName ROM     *thirdtbl
        , Nat8               *pos
        , Nat8               *thirdpos
        , programType        *pt
        , Bool                IsCniNumber
        )

{
    if ( prname != presetNameOther )
    {
        *pos = entryPosition( prname
                , &tbl[0]
                , MAX_MAIN_SORT
                );

        if ( validSortTable( thirdtbl ) )
        {
            *thirdpos = entryPosition( prname
                    , &thirdtbl[0]
                    , NUMBER_OF_THIRD_PROGRAMS
                    );
        }
        else
        {
            *thirdpos = 0;
        }
    }
    else
    {
        *pos = 0;
        *thirdpos = 0;
    }

    if ( *pos > 0 )
    {
        /* PDC/VPS stations with DEFINE name index which are IN the sort list */

        (*pt) = programTypePdcVpsMainsort;
    }
    else if ( ( *pos == 0 ) && ( prname != presetNameOther ) )
    {
        /* PDC/VPS stations with DEFINE name index which are NOT in the main *
         * sort list.                                                        */
        if ( *thirdpos > 0 )
        {
            /* PDC/VPS stations with DEFINE name index which are NOT in the main *
             * sort list, but in the third program sort list. Third Program      */

            (*pt) =programTypePdcVpsThirdProgarmSort;
        }
        else
        {
            /* PDC/VPS stations with DEFINE name index which are NOT in the main *
             * sort list and the third program sort list.                        */

            (*pt) = programTypeKnownPdcVpsStation;
        }
    }
    else if ( ( *pos == 0 )
            &&( prname == presetNameOther )
            &&( IsCniNumber )
            )
    {
        /* PDC/VPS stations with UNDEFINE name index */

        (*pt) = programTypeUknownPdcVpsStation;
    }
    else 
    {
        /* NON-PDC/VPS stations with UNDEFINE name index */

        (*pt) = programTypeNonPdcVpsStation;
    }

}

void CSvcPats_Priv::sortWithInGroup(Nat8 *list ,Nat8 elements)
    /*****************************************************/
    /*  Parametrs :  List of the elements passed         */
    /*               Number of members passed            */  
    /*Purpose:       Sort  within the Group              */
    /*****************************************************/
{
    Nat8 temp;
    Nat8 i;
    Nat8 j;
    for (i=elements-1;i>1;i--)
    {
        for(j=1;j<i;j++)
        {
            if(PresetData[ list[j] ].SignalStrength<PresetData[ list[j+1] ].SignalStrength)
            {
                temp = list[j+1];
                list[j+1] = list[j];
                list[j] = temp;
            }
            if(PresetData[ list[j] ].SignalStrength == PresetData[ list[j+1] ].SignalStrength)
            {
                if(PresetData[ list[j] ].Frequency > PresetData[ list[j+1] ].Frequency)
                {
                    temp = list[j+1];
                    list[j+1] = list[j];
                    list[j] = temp;
                }
            }
        }
    }

}

PresetName ROM * CSvcPats_Priv::tableSelection(void)
    /********************************************
      Returns the Priority Table
     *********************************************/
{ 
    PresetName ROM * priorityTable; 
    switch(sysset_GetSystemCountry())
    {
        case countid_CountryAustria:
            nbOfReservedLocation = AustriaReservedLocations;
            priorityTable =  (&austriaSortTable[0]);
            break;
        case countid_CountryBelgium:
            if(sysset_GetSystemLanguage() == langid_LangFrench)
            { 
                nbOfReservedLocation = BelgiumReservedLocations;   
                priorityTable =  (&belgiumSortTableFrench[0]);
            } 
            else
            {
                nbOfReservedLocation = BelgiumReservedLocations ;
                priorityTable =  (&belgiumSortTableDutch[0]);
            }    
            break;    
        case countid_CountryCzechrep: 
            nbOfReservedLocation = CzechReservedLocations;
            priorityTable =  (&czechSortTable[0]);
            break;
        case countid_CountryDenmark:
            nbOfReservedLocation = DenmarkReservedLocations; 
            priorityTable =  (&denmarkSortTable[0]);
            break;
        case countid_CountryFinland:
            nbOfReservedLocation = FinlandReservedLocations;
            priorityTable =  (&finlandSortTable[0]);
            break;
        case countid_CountryFrance: 
            nonVpsPdcSpecialSort = TRUE;
            nbOfReservedLocation = FranceReservedLocations;
            priorityTable =  (&franceSortTable[0]);
            break;
        case countid_CountryGermany:
            nbOfReservedLocation = GermanyReservedLocations;
            priorityTable =  (&germanSortTable[0]);
            break;
        case countid_CountryGreece:
            nbOfReservedLocation = GreeceReservedLocations; 
            priorityTable =  (&greeceSortTable[0]);
            break;
        case countid_CountryHungary:
            nbOfReservedLocation = HungaryReservedLocations;
            priorityTable =  (&hungarySortTable[0]);
            break;
        case countid_CountryIreland:
            nonVpsPdcSpecialSort = TRUE;
            nbOfReservedLocation = IrelandReservedLocations; 
            priorityTable =  (&irelandSortTable[0]);
            break;
        case countid_CountryItaly: 
            nonVpsPdcSpecialSort = TRUE;
            nbOfReservedLocation = ItalyReservedLocations;
            priorityTable =  (&italySortTable[0]);
            break;
        case countid_CountryLuxembourg:
            nbOfReservedLocation = LuxembourgReservedLocations;
            priorityTable =  (&luxemburgSortTable[0]);
            break;
        case countid_CountryNetherlands:
            nbOfReservedLocation = NetherlandsReservedLocations;
            priorityTable =  (&netherlandSortTable[0]);
            break;
        case countid_CountryNorway:
            nbOfReservedLocation = NorwayReservedLocations;
            priorityTable =  (&norwaySortTable[0]);
            break;
        case countid_CountryPoland:
            nonVpsPdcSpecialSort = TRUE;
            nbOfReservedLocation = PolandReservedLocations;
            priorityTable =  (&polandSortTable[0]);
            break;
        case countid_CountryPortugal:
            nbOfReservedLocation = PortugalReservedLocations;
            priorityTable =  (&portugalSortTable[0]);
            break;
        case countid_CountrySlovakia:
            nbOfReservedLocation = SlovakiaReservedLocations;
            priorityTable = (&slovakiaSortTable[0]);
            break;
        case countid_CountrySlovenia :
            nbOfReservedLocation = SloveniaReservedLocations;
            priorityTable = (&sloveniaSortTable[0]);
            break;
        case countid_CountrySpain:
            nonVpsPdcSpecialSort = TRUE;
            nbOfReservedLocation = SpainReservedLocations;
            priorityTable =  (&spainSortTable[0]);
            break;
        case countid_CountrySweden:
            nbOfReservedLocation = SwedenReservedLocations;
            priorityTable =  (&swedenSortTable[0]);
            break;
        case  countid_CountrySwitzerland:
            nbOfReservedLocation = SwitzerlandReservedLocations;
            priorityTable =  (&switzerlandSortTable[0]);
            break;
        case countid_CountryTurkey:
            nbOfReservedLocation = TurkeyReservedLocations;
            priorityTable =  (&turkeySortTable[0]);
            break;
        case countid_CountryUK:
            nonVpsPdcSpecialSort = TRUE;
            nbOfReservedLocation = UKReservedLocations;
            priorityTable =  (&ukSortTable[0]);
            break;
        default :
            nbOfReservedLocation = 0;
            priorityTable =  (NULL);
            break;
    }
    return(priorityTable ); 
} 

void CSvcPats_Priv::sortInitialisation(void)
    /*****************************/
    /* Initialisation of lists   */
    /*****************************/
{
    Nat8 i;
    nrKnownPdcVpsStation = 1 ;
    nrUnknownPdcVpsStation = 1;
    nrNonPdcVpsStation = 1;
    nrDoubleStation = 1;
    doubleStation = 0;
    otherProgarm = 0;
    firstThirdProgram = 0;
    currentThirdProgarmPosition =1;
    nbOfReservedLocation = 0;
    nonVpsPdcSpecialSort = FALSE;
    currentTable = tableSelection();
    switch(sysset_GetSystemCountry())
    {
        case countid_CountryGermany :
            thirdProgramTable = &germanThirdSortTable[0];
            NUMBER_OF_THIRD_PROGRAMS = MAX_THIRD_PROGRAM_SORT;
            break;
        case countid_CountryUK :
            thirdProgramTable =  &ukThirdSortTable[0];
            NUMBER_OF_THIRD_PROGRAMS = MAX_THIRD_PROGRAM_SORT_UK;
            break;
        case countid_CountryPoland :
            thirdProgramTable =  &polandThirdSortTable[0];
            NUMBER_OF_THIRD_PROGRAMS = MAX_THIRD_PROGRAM_SORT_POLAND;
            break;
        default : 
            thirdProgramTable= NULL;
            break;
    }
    if ( validSortTable( currentTable )  )
    {

        /*******************************
         * Initialisation of sort list *
         *******************************/

        for ( i = 1; i < MAX_MAIN_SORT; i++ )
        {
            mainSortList[ i ] = EMPTY;

        }
        for(i=1; i < NUMBER_OF_THIRD_PROGRAMS ;i++ )
        {
            thirdProgramList[ i ] = EMPTY;
        }
    }  
    storeNameAttrib();
}
/********************************************************/
void CSvcPats_Priv::sortAndList( int maxpreset )
    /********************************************************/
    /* Parameters :   Maxpreset                             */
    /* Purpose    : sorts the  preset list                  */
    /*                                                      */
    /********************************************************/
{

    int                i ;
    Nat8               priorityMainSort= 0;
    Nat8               priorityThirdSort= 0;
    programType        prgmType;


    /************
     * Sorting  *
     ************/

    for ( i = 1; i < maxpreset; i++ )
    {
        mainOrThirdPresent = FALSE; 
        calculateEntryPosType( (PresetName)presetNameAttrib[i]
                , currentTable
                , thirdProgramTable
                , &priorityMainSort
                , &priorityThirdSort
                , &prgmType
                , ((GetPresetDataIndicator(i,MASK_VPS) )   /* the == TRUE was removed */ 
                    ||(GetPresetDataIndicator(i,MASK_PKT830CNI)) /* the == TRUE was removed */
                    ||(GetPresetDataIndicator(i,MASK_PKT830NI) )) /* the == TRUE was removed */ 
                );

        if ( prgmType == programTypePdcVpsMainsort )
        {
            /* PDC/VPS stations with DEFINE name index which are IN the sort list */

            updateSortListCheckDouble(  priorityMainSort
                    , (Nat8)i
                    , mainSortList
                    , &otherProgarm
                    , &doubleStation
                    , &prgmType
                    , MAX_MAIN_SORT
                    );
        }
        if ( prgmType ==programTypePdcVpsThirdProgarmSort )
        {
            /* PDC/VPS stations with DEFINE name index which are NOT in the main *
             * sort list, but IN the third program sort list. Third Program      */

            updateSortListCheckDouble( priorityThirdSort
                    , (Nat8)i
                    , thirdProgramList
                    , &otherProgarm
                    , &doubleStation
                    , &prgmType
                    , NUMBER_OF_THIRD_PROGRAMS
                    );
        }

        if ( prgmType == programTypeKnownPdcVpsStation )
            /* PDC/VPS stations with DEFINE name index which are NOT in the main *
             * sort list and the third program sort list.                        */

        {
            if(mainOrThirdPresent)
            {
                updateOtherListCheckDouble( &nrKnownPdcVpsStation
                        , otherProgarm
                        , knownPdcVpsStationList
                        , &doubleStation
                        , &prgmType
                        , div_MaxPresets
                        );
            }
            else
            {
                updateOtherListCheckDouble( &nrKnownPdcVpsStation
                        , (Nat8)i
                        , knownPdcVpsStationList
                        , &doubleStation
                        , &prgmType
                        , div_MaxPresets
                        );
            }

        }
        if ( prgmType == programTypeUknownPdcVpsStation )
        {
            /* PDC/VPS stations with UNDEFINE name index */

            updateOtherListCheckDouble( &nrUnknownPdcVpsStation
                    ,(Nat8) i 
                    , unKnownPdcVpsStationList
                    , &doubleStation
                    , &prgmType
                    , div_MaxPresets
                    );
        }
        if ( prgmType == programTypeNonPdcVpsStation )
        {
            /* NON-PDC/VPS stations with UNDEFINE name index */
            if(GetPresetDataIndicator(i,MASK_RECEIVED) )  /* the == TRUE was removed */ 
                /*if(PresetData[i].received == TRUE)*/
            {
                nonPdcVpsStationList[nrNonPdcVpsStation] =  (Nat8)i ;
                nrNonPdcVpsStation++;
            }
        }

        if ( prgmType == programTypeDoubleStation )
        {
            /* Double stations */

            doubleStationList[nrDoubleStation] = doubleStation;
            nrDoubleStation++;
        }

    }
    sortWithInGroup(unKnownPdcVpsStationList,nrUnknownPdcVpsStation);
    sortWithInGroup(knownPdcVpsStationList,nrKnownPdcVpsStation);
    sortWithInGroup(nonPdcVpsStationList,nrNonPdcVpsStation);
    sortWithInGroup(doubleStationList,nrDoubleStation);
    if(sysset_GetSystemCountry() == countid_CountryUK )
    {
        sortWithInGroup(thirdProgramList,NUMBER_OF_THIRD_PROGRAMS);
    } 
    if(sysset_GetSystemCountry() == countid_CountryPoland)
    {
        sortWithInGroup(thirdProgramList,NUMBER_OF_THIRD_PROGRAMS);
    }
}

Nat8 CSvcPats_Priv::sortMergeList(int maxpreset)
    /*******************************************/
    /*    Sorting & Merging                    */
    /*******************************************/
{
    Nat8 indexCount;
    Nat8 presetNumber;
    Nat8 i;
    Nat8 mergedNbofVpsPdc = 1;

    maxPreset = maxpreset;
    sortInitialisation();
    sortAndList(maxPreset);
    indexCount=1; 
    for ( i = 1; i < MAX_MAIN_SORT; i++ )
    {
        presetNumber = mainSortList[ i ];

        if ( i == 3 ) /* Third Program i.e. frist porgarm  from the thirdProgramList
                         To the main sort list */
        {
            if ( validSortTable( thirdProgramTable ) )
            {
                if ( topOfList( thirdProgramList,NUMBER_OF_THIRD_PROGRAMS,
                            &firstThirdProgram,&currentThirdProgarmPosition)
                   )
                {
                    /* putting the first third program in the list  */
                    PresetIndex[ indexCount ] = firstThirdProgram;
                    if(sysset_GetSystemCountry() == countid_CountryUK)/* Special Case for UK third Program*/
                    {
                        str_strncpy(PresetData[PresetIndex[indexCount]].Name,
                                (char * )presetNameString (presetNameItvnetwork),
                                PRESET_NAME_LENTH);
                    }
                    indexCount++;
                }
                else if(sysset_GetSystemCountry() == countid_CountryUK)
                {
                    PresetIndex[ indexCount ] = nonPdcVpsStationList[mergedNbofVpsPdc];
                    mergedNbofVpsPdc++;
                    indexCount++;
                }
                else
                {
                    /*Do Nothing*/
                }
            }
        }
        if( (sysset_GetSystemCountry() == countid_CountryFrance )
                && (i == 5) && (presetNumber == EMPTY) && (mainSortList[7] != EMPTY) )
        {
            presetNumber = mainSortList[7];
            mainSortList[7] = EMPTY;
            PresetIndex[ indexCount ] = presetNumber;
            indexCount++;
            i++;
            presetNumber = mainSortList[ i ]; 
        }

        if (( presetNumber != EMPTY ) && (indexCount>nbOfReservedLocation))
        {
            PresetIndex[ indexCount ] = presetNumber;
            indexCount++;
        }
        if((nonVpsPdcSpecialSort == FALSE)&&(indexCount<=nbOfReservedLocation))
        {
            PresetIndex[ indexCount ] = presetNumber;
            indexCount++;
        }
        if((nonVpsPdcSpecialSort )&&(indexCount<=nbOfReservedLocation) /* the == TRUE was removed */
                &&(presetNumber == EMPTY))
        {
            PresetIndex[ indexCount ] = nonPdcVpsStationList[mergedNbofVpsPdc];
            mergedNbofVpsPdc++;
            indexCount++;
        }
        if((nonVpsPdcSpecialSort )&&(indexCount<=nbOfReservedLocation) /* the == TRUE was removed */
                &&(presetNumber != EMPTY))
        {
            PresetIndex[ indexCount ] = presetNumber;
            indexCount++;
        }

    }

    /* second step:
       adding known pdcvps station list
       */
    conCatListToList( nrKnownPdcVpsStation , &indexCount , knownPdcVpsStationList, PresetIndex,1
            );

    /* third step:
       adding the unknown pdcvps station list
       */
    conCatListToList( nrUnknownPdcVpsStation , &indexCount , unKnownPdcVpsStationList , PresetIndex,1
            );

    /* fourth step:
       adding the remaining third programs
       */

    for ( i = currentThirdProgarmPosition; i < NUMBER_OF_THIRD_PROGRAMS; i++ )
    {
        presetNumber = thirdProgramList[ i ];
        if ( presetNumber != EMPTY )
        {
            PresetIndex[ indexCount ] = presetNumber;
            indexCount++;
        }
    }

    /* fifth step:
       adding the non pdcvps station list
       */
    conCatListToList( nrNonPdcVpsStation, &indexCount , nonPdcVpsStationList, PresetIndex,mergedNbofVpsPdc
            );

    /* sixth step:
       adding the double station list
       */
    conCatListToList( nrDoubleStation , &indexCount , doubleStationList, PresetIndex,1);
    return(indexCount);
}

/*******************************************************/
Nat8 * CSvcPats_Priv::presetNameString( PresetName p )
    /*******************************************************
     * copies name from table in ROM
     *******************************************************/
{

    str_strncpy((char *)presetname,(char *)&presetnames[PRESET_NAME_LENTH*p],PRESET_NAME_LENTH); 
    return ( presetname );

}

HsvCniName CSvcPats_Priv::cniname_GetPresetName (Nat16 vpsCni,Nat16 pkt830Cni, Nat16 pkt830Ni, Bool ardBit)
    /****************************************************/
    /*  Gets the  Preset Name and Preset                */ 
    /*  attrib to the database                          */
    /****************************************************/  
{
    int         sizeOfPdcCniTable;
    int         sizeOfVpsCniTable;
    int         sizeOfNiTable;
    HsvCniName  returnVal;    



    sizeOfPdcCniTable = sizeof(PdcCniTable)/sizeof(PdcCniTable[0]);
    sizeOfVpsCniTable = sizeof(VpsCniTable)/sizeof(VpsCniTable[0]);
    sizeOfNiTable = sizeof(NiTable)/sizeof(NiTable[0]);
    str_strncpy((char *)cniName,div_GetDefaultPresetName,PRESET_NAME_LENTH);
	TraceDebug(m,"Hsvprins: channelName %s",(char *)cniName);

    /*for(i = 0; i<PRESET_NAME_LENTH; i++)
      {
      cniName[i] = 0x20;
      }*/

    /*VPS*/
    if( (vpsCni != cniname_CniNiInvalid) && (validateData(vpsCni,ardBit,&currentNameAttrib,(char *)cniName,VpsTableSelect,sizeOfVpsCniTable)) )
    {
        returnVal.cniNi = vpsCni;
    }
    /*Format2*/
    else if( (pkt830Cni != cniname_CniNiInvalid) && (validateData(pkt830Cni,FALSE,&currentNameAttrib,(char *)cniName,PdcTableSelect,sizeOfPdcCniTable)) )
    {
        returnVal.cniNi = pkt830Cni;
    }
    /*Format1*/
    else if( (pkt830Ni != cniname_CniNiInvalid) && (validateData(pkt830Ni,FALSE,&currentNameAttrib,(char *)cniName,NiTableSelect, sizeOfNiTable)) )
    {
        returnVal.cniNi = pkt830Ni;
    }
    else
    {
        returnVal.cniNi = cniname_CniNiInvalid;
        currentNameAttrib = presetNameOther;
    }

    returnVal.name = (char *)cniName;
    return (returnVal);
}

/****************************************************/
/*  Sets bits in the indicator byte                 */ 
/****************************************************/  
/* commented as the function is not used
   static void SetPresetDataIndicator( int prNo, Nat8 mask, Bool bit)
   {
   Nat8 bitmask = 0;
   ASSERT( (mask == MASK_RECEIVED) ||
   (mask == MASK_ARD) ||
   (mask == MASK_VPS) ||
   (mask == MASK_PKT830CNI) ||
   (mask == MASK_PKT830NI) );

   if(bit)
   {
   PresetData[prNo].DataIndicator |= mask;
   }
   else
   {
   PresetData[prNo].DataIndicator &= (~mask);
   }
   }
   */
Bool CSvcPats_Priv::GetPresetDataIndicator( int prNo, Nat8 mask )
    /****************************************************/
    /*  Gets bits in the indicator byte                 */ 
    /****************************************************/  
{
    Bool returnVal = FALSE;

    ASSERT( (mask == MASK_RECEIVED) ||
            (mask == MASK_ARD) ||
            (mask == MASK_VPS) ||
            (mask == MASK_PKT830CNI) ||
            (mask == MASK_PKT830NI) ||
            (mask == MASK_TXTTRNAVLBL) );
    if(PresetData[prNo].DataIndicator & mask )
    {
        returnVal = TRUE;
    }
    return(returnVal);
}

/****************************************************/
void CSvcPats_Priv::AllocateMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases any memory which has been malloced 
     and mallocs again
     ****************************************************/
{
#if MALLOC
    int sizeOfMalloc ;    

    ReleaseMemoryForPresetList();

    sizeOfMalloc =    (div_MaxPresets * (sizeof(int)))                /* for presetNameAttrib         */
        +  (MAX_MAIN_SORT * (sizeof(Nat8)))                /* for mainSortList             */
        +  (MAX_THIRD_PROGRAM_SORT_UK * (sizeof(Nat8)))    /* for thirdProgramList         */
        +  (div_MaxPresets * (sizeof(Nat8)))               /* for knownPdcVpsStationList   */
        +  (div_MaxPresets * (sizeof(Nat8)))               /* for unKnownPdcVpsStationList */
        +  (div_MaxPresets * (sizeof(Nat8)))               /* for nonPdcVpsStationList     */
        +  (div_MaxPresets * (sizeof(Nat8)));              /* for doubleStationList        */

    mallocedMemory = mem_Malloc( sizeOfMalloc );
    memo_memset((void *)mallocedMemory,0,sizeOfMalloc);

    presetNameAttrib = (int *)(mallocedMemory);
    mainSortList = mallocedMemory + (div_MaxPresets * (sizeof(int)));
    thirdProgramList = mainSortList + (MAX_MAIN_SORT * (sizeof(Nat8)));
    knownPdcVpsStationList = thirdProgramList + (MAX_THIRD_PROGRAM_SORT_UK * (sizeof(Nat8)));
    unKnownPdcVpsStationList = knownPdcVpsStationList + (div_MaxPresets * (sizeof(Nat8)));
    nonPdcVpsStationList = unKnownPdcVpsStationList + (div_MaxPresets * (sizeof(Nat8)));
    doubleStationList = nonPdcVpsStationList + (div_MaxPresets * (sizeof(Nat8)));
#else
    int i;
    for (i = 0; i<div_MaxPresets; i++)
    {
        presetNameAttrib[i] = 0;
    }
#endif
    /*
       sizeOfMalloc = div_MaxPresets * (sizeof(int));
       presetNameAttrib = (int * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)presetNameAttrib,0,sizeOfMalloc);

       sizeOfMalloc = MAX_MAIN_SORT * (sizeof(Nat8));
       mainSortList = (Nat8 * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)mainSortList,0,sizeOfMalloc);

       sizeOfMalloc = MAX_THIRD_PROGRAM_SORT_UK * (sizeof(Nat8));
       thirdProgramList = (Nat8 * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)thirdProgramList,0,sizeOfMalloc);

       sizeOfMalloc = div_MaxPresets * (sizeof(Nat8));
       knownPdcVpsStationList = (Nat8 * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)knownPdcVpsStationList,0,sizeOfMalloc);

       sizeOfMalloc = div_MaxPresets * (sizeof(Nat8));
       unKnownPdcVpsStationList = (Nat8 * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)unKnownPdcVpsStationList,0,sizeOfMalloc);

       sizeOfMalloc = div_MaxPresets * (sizeof(Nat8));
       nonPdcVpsStationList = (Nat8 * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)nonPdcVpsStationList,0,sizeOfMalloc);

       sizeOfMalloc = div_MaxPresets * (sizeof(Nat8));
       doubleStationList = (Nat8 * )mem_malloc( sizeOfMalloc );
       memo_memset((void *)doubleStationList,0,sizeOfMalloc);
       */
    /*
       for (i = 0; i<div_MaxPresets; i++)
       {
       presetNameAttrib[i] = 0;
       }
       */
}

/****************************************************/
void CSvcPats_Priv::ReleaseMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases the memory which has been malloced
     ****************************************************/
{
#if MALLOC

    if(mallocedMemory != NULL)
    {
        mem_Free(0,mallocedMemory);

        mallocedMemory = NULL;
        presetNameAttrib = NULL;
        mainSortList = NULL;
        thirdProgramList = NULL;
        knownPdcVpsStationList = NULL;
        unKnownPdcVpsStationList = NULL;
        nonPdcVpsStationList = NULL;
        doubleStationList = NULL;
    }
#endif
    /*
       if(presetNameAttrib != NULL)
       {
       mem_free(0, presetNameAttrib);
       presetNameAttrib = NULL;
       }
       if(mainSortList != NULL)
       {
       mem_free(0, mainSortList);
       mainSortList = NULL;
       }
       if(thirdProgramList != NULL)
       {
       mem_free(0, thirdProgramList);
       thirdProgramList = NULL;
       }
       if(knownPdcVpsStationList != NULL)
       {
       mem_free(0, knownPdcVpsStationList);
       knownPdcVpsStationList = NULL;
       }
       if(unKnownPdcVpsStationList != NULL)
       {
       mem_free(0, unKnownPdcVpsStationList);
       unKnownPdcVpsStationList = NULL;
       }
       if(nonPdcVpsStationList != NULL)
       {
       mem_free(0, nonPdcVpsStationList);
       nonPdcVpsStationList = NULL;
       }
       if(doubleStationList != NULL)
       {
       mem_free(0, doubleStationList);
       doubleStationList = NULL;
       }
       */
}

