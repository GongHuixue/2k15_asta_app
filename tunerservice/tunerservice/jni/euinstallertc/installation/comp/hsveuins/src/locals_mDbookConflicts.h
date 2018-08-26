#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define     BUFFER_ADMIN_MEM                   (100)

#define     REGION_NONE                         0x00           

#define     REGION_P                            0x04

#define     REGION_PS                           0x06

#define     REGION_PST                          0x07

#define     DIGITAL                             ( HsvOnePart )

#define     ANALOG                              ( HsvAnalog )

#define     DIGITAL_PRESET(presetdat)           ( (presetdat).Type == DIGITAL )

#define     SAME(x, y)                          ( !(x ^ y) )

#define     CURRENT_SERVICE_INDEX               ( 0 )

#define     VALID_PRIMARY_REGION(region)        ( (region) <= (int)0xFF )

#define     VALID_SECONDARY_REGION(region)      ( (region) <= (int)0xFF )

#define     VALID_TERTIARY_REGION(region)       ( (region) <= (int)0xFFFF )

#define     PRIORITY_NOT_ASSIGNED(priority)     ( (priority) == 0 )

#define     GET_LCN(svcdat)                     ( (mConflictResolutionPass == FIRST_PASS)? (svcdat).LCN : (svcdat).LowPrioLCN )

#define     TOTAL_NUM_OF_CONFLICTS              ( mNumOfLCNsInConflict )

#define     CONFLICT_LCN(Indx)                  ( mConflictList[Indx].LCN )

#define     IS_VALID_CONFLICT(svcdat)           ( PRESET_NOT_ALLOCATED(svcdat) || (svcdat.PresetNumber == GET_LCN(svcdat)) )

#define     VALID_SERVICE_INDEX(i, MaxIndex)    ( (i >= 0) && (i <= MaxIndex) )

#define     CALCULATE_DISTANCE(UserPST)         ( (UserPST == REGION_NONE)? (UserPST | 0x10): ((UserPST == REGION_P)? (UserPST | 0x1): (UserPST)) )

#define     CONFLICT_SERVICE_DBINDEX(i, j)      ( mConflictList[i].ServiceInfo[j].DbIndex )

#define     IGNORE_NONE                         ( 0 )

#define     IGNORE_TERTIARY                     ( 16 )

#define     IGNORE_SECONDARYTERTIARY            ( 24 )

#define     SHIFT_BITS                          ( (CurrentLevelFromMiddlelevel == 0)? IGNORE_NONE : \
        ((CurrentLevelFromMiddlelevel == 1)? IGNORE_TERTIARY  : IGNORE_SECONDARYTERTIARY) )

#define     MASK_REGION_TYPES(P, S, T)          ( ((VALID_PRIMARY_REGION(P))   << 2) | \
        ((VALID_SECONDARY_REGION(S)) << 1) | \
        (VALID_TERTIARY_REGION(T))     )

#define     MASK_REGION_CODE(P, S, T, Type)     ( (((Type >= REGION_P)?   P : 0) << 24) |   \
        (((Type >= REGION_PS)?  S : 0) << 16) |   \
        ((Type >= REGION_PST)? T : 0) )

#define     NO_PASS                             ( 0 )

#define     FIRST_PASS                          ( 1 )

#define     CURRENT_TABLE                       ( pgdb_GetCurrentTable() )

#define     SERVICE_TABLE                       ( CURRENT_TABLE | pgdbconst_DigitalService )

#define     PRESET_TABLE                        ( CURRENT_TABLE | pgdbconst_Preset )

#define     PTC_TABLE                           ( CURRENT_TABLE | pgdbconst_DigitalTS )

#define     MAX_SERVICE_TYPES                   ( 8 )

#define     CURRENT_MODE                        ( rins_GetInstallationMode() ) 

#define     AUTO_MODE                           ( rins_InstallationModeAutomatic )

#define     TV_SERVICE                          ( TelevisionService )

#define     RADIO_SERVICE                       ( RadioService )

#define     TELETEXT_SERVICE                    ( TeletextService )

#define     NVOD_REFERENCE_SERVICE              ( NVODReferenceService )

#define     NVOD_TIMESHIFTED_SERVICE            ( NVODTimeShiftedService )

#define     MOSAIC_SERVICE                      ( MosaicService )

#define     DATABROADCAST_SERVICE               ( DatabroadcastService )

#define     DVBMHP_SERVICE                      ( DVBMHPService )

#define     PRESET_NOT_ALLOCATED(svcdat)        ( (svcdat).PresetNumber == INVALID_PRESET )

/**Prio determination specific macros **/

#define INVALID         -1

#define NO_REGION_CODE              (0xFFFF)    //In TRD descriptor Primary & Secondry Region code is of unsigned 8 bits

#define NO_TERTIARY_REGION_CODE     (0x1FFFF)   //In TRD descriptor Tertiary Region code is of unsigned 16 bits

#define SAME_RANK(uPST, sPST)       (!((uPST) ^ (sPST)))

#define SAME_REGION_CODE_B4UK(index)     ((index == 0x7)?   ((svcdat.TertiaryRegion == TertiaryRegion) &&   \
            (svcdat.SecondaryRegion == SecondaryRegion) &&  \
            (svcdat.PrimaryRegion == PrimaryRegion)) :      \
        ((index == 0x6) ?      ((svcdat.TertiaryRegion == NO_TERTIARY_REGION_CODE) &&  \
            (svcdat.SecondaryRegion == SecondaryRegion) &&  \
            (svcdat.PrimaryRegion == PrimaryRegion)) :      \
         ((index == 0x4) ?     ((svcdat.TertiaryRegion == NO_TERTIARY_REGION_CODE) &&\
             (svcdat.SecondaryRegion == NO_REGION_CODE) &&   \
             (svcdat.PrimaryRegion == PrimaryRegion)) : FALSE )))

#define SAME_REGION_CODE_AFTERUK7(index)  ((index == 0x7)?  ((svcdat.TertiaryRegion != TertiaryRegion) &&   \
            (svcdat.SecondaryRegion == SecondaryRegion) &&  \
            (svcdat.PrimaryRegion == PrimaryRegion)) :      \
        ((index == 0x6) ?   ((svcdat.SecondaryRegion != SecondaryRegion) && \
            (svcdat.PrimaryRegion == PrimaryRegion)) :      \
         ((index == 0x4) ?  ((svcdat.PrimaryRegion != PrimaryRegion)) : 0 )))

#define SAME_REGION_CODE_AFTERUK6(index)    ((index == 0x7)? ((svcdat.TertiaryRegion != NO_TERTIARY_REGION_CODE) && \
            (svcdat.SecondaryRegion == SecondaryRegion) && \
            (svcdat.PrimaryRegion == PrimaryRegion)) :     \
        ((index == 0x6) ? ((svcdat.SecondaryRegion != SecondaryRegion) &&   \
            (svcdat.PrimaryRegion == PrimaryRegion)) :        \
         ((index == 0x4) ? ((svcdat.PrimaryRegion != PrimaryRegion)) : 0 )))

#define SAME_REGION_CODE_AFTERUK4(index)    ((index == 0x7) ?  ((svcdat.TertiaryRegion == NO_TERTIARY_REGION_CODE) &&   \
            (svcdat.SecondaryRegion != NO_REGION_CODE) &&    \
            (svcdat.PrimaryRegion == PrimaryRegion)) :       \
        ((index == 0x6) ?  ((svcdat.TertiaryRegion != NO_TERTIARY_REGION_CODE) &&   \
            (svcdat.SecondaryRegion != NO_REGION_CODE) &&    \
            (svcdat.PrimaryRegion == PrimaryRegion)) :       \
         ((index == 0x4) ?  ((svcdat.PrimaryRegion != PrimaryRegion)) : 0 )))

#define SAME_REGION_CODE_AFTERUK0(index)    ((index == 0x0) ?  ((svcdat.TertiaryRegion == NO_TERTIARY_REGION_CODE) &&   \
            (svcdat.SecondaryRegion == NO_REGION_CODE) &&    \
            (svcdat.PrimaryRegion == NO_REGION_CODE)) :  0)

#define SAME_REGION_CODE_AFTERUK(UserPST, index)             ((UserPST == 0x7)? SAME_REGION_CODE_AFTERUK7(index) : \
        ((UserPST == 0x6)? SAME_REGION_CODE_AFTERUK6(index) : \
         ((UserPST == 0x4)? SAME_REGION_CODE_AFTERUK4(index) :  \
          ((UserPST == 0x0)? SAME_REGION_CODE_AFTERUK0(index) : INVALID))))






                                                         /*********************** static functions  ************************/

typedef enum
{
    evStep0 = 0,
    evStep1,
    evStep2,
    evStep3,
    evStep4,
    evStepComplete,
}SortSteps;
typedef struct
{
    Nat16 LCN;
    int   NoOfServices;
    struct
    {
        Nat8  Priority;
        int   DbIndex;
        Nat8  ServicePST;
    }ServiceInfo[MAX_CONFLICT_SERVICES];
    Bool Resolved;
}HsvDbookConflictsData;
#define MULT_SAME_REGION_CODE_B4UK(index)    ((index == 0x7) ?          ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX]  == TertiaryRegion)                  && \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX]  == SecondaryRegion)                 && \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) :                   \
        ((index == 0x6) ?          ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX]  == NO_TERTIARY_REGION_CODE)         && \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX]  == SecondaryRegion)                 && \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) :                    \
         ((index == 0x4) ?          ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX]  == NO_TERTIARY_REGION_CODE)          && \
             (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX]  == NO_REGION_CODE)                   && \
             (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) : FALSE )))

#define MULT_SAME_REGION_CODE_AFTERUK7(index)    ((index == 0x7)?           ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX]  != TertiaryRegion)            && \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX]  == SecondaryRegion)           && \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) :            \
        ((index == 0x6) ?          ((mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX] != SecondaryRegion)            &&   \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) :            \
         ((index == 0x4) ?          ((mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]   != PrimaryRegion)) : 0 )))

#define MULT_SAME_REGION_CODE_AFTERUK6(index)       ((index == 0x7)?        ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX]  != NO_TERTIARY_REGION_CODE)    &&   \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX]  == SecondaryRegion)           &&    \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) :                \
        ((index == 0x6) ?       ((mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX] != SecondaryRegion)           &&    \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]    == PrimaryRegion)) :                \
         ((index == 0x4) ?       ((mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]   != PrimaryRegion)) : 0 )))

#define MULT_SAME_REGION_CODE_AFTERUK4(index)       ((index == 0x7) ?       ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX] == NO_TERTIARY_REGION_CODE)      &&  \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX] != NO_REGION_CODE)               &&  \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]   == PrimaryRegion)) :             \
        ((index == 0x6) ?       ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX] != NO_TERTIARY_REGION_CODE)      &&  \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX] != NO_REGION_CODE)               &&  \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]   == PrimaryRegion)) :              \
         ((index == 0x4) ?       ((mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]  != PrimaryRegion)) : 0 )))

#define MULT_SAME_REGION_CODE_AFTERUK0(index)       ((index == 0x0) ?       ((mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX] == NO_TERTIARY_REGION_CODE)    &&    \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX] == NO_REGION_CODE)             &&    \
            (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX]   == NO_REGION_CODE)) :    0)

#define MULT_SAME_REGION_CODE_AFTERUK(UserPST, index)                       ((UserPST == 0x7)? MULT_SAME_REGION_CODE_AFTERUK7(index) :                      \
        ((UserPST == 0x6)? MULT_SAME_REGION_CODE_AFTERUK6(index) :                      \
         ((UserPST == 0x4)? MULT_SAME_REGION_CODE_AFTERUK4(index) :                      \
          ((UserPST == 0x0)? MULT_SAME_REGION_CODE_AFTERUK0(index) : INVALID))))

#define INVALID_REGION_DEPTH						0xFFFF

                                                                                                    /**************************************************************************************************************************/
/**************************************************************************************************************************/

/************************** MULTIPLE TARGET REGION DESCRIPTOR SPECIFIC MACROS END *****************************************/

/**************************************************************************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mServicePriority[MAX_SERVICE_TYPES];
static int s__mServicePriority[MAX_SERVICE_TYPES];
int RegionCachePoolId;
static int s__RegionCachePoolId;
Pump mDbookConflictsPmp;
static Pump s__mDbookConflictsPmp;
HsvDbookConflictsData mConflictList[ MAX_SERVICES ];
static HsvDbookConflictsData s__mConflictList[ MAX_SERVICES ];
int TOTAL_NUM_OF_CONFLICTS,mConflictResolutionPass;
static int s__TOTAL_NUM_OF_CONFLICTS,s__mConflictResolutionPass;
void mPopulateListOfConflicts(int evCurrentSortStep);
void mResolveConflicts(int evCurrentSortStep);
void mAssignPriorityForServices(void);
void mSelectPriorityService(void);
void mInvalidateLessPrioHDLCNServices (int i, int PrefServiceIndex);
inline int mDBookCompareServices(int LCNConflictIndex, int ServiceIndex, int PrefServiceIndex);
int mGetServicePriority(int serviceType);
void InitConflictList(void);
void mDvbTConflictsHandler(int value, Nat32 param);
void mCopyDataToList(HsvPgdatDigServiceData *svcdat, int ServiceInfoIndex, int ConflictLCN);
inline Bool mIsPresentInConflictList(HsvPgdatDigServiceData svcdat);
inline void mGetUserPSTSettings(Nat16 *PrimaryRegion, Nat16 *SecondaryRegion, Nat32 *TertiaryRegion, Nat8 *UserPST);
void mUpdateConflictPresets(int PrefDbIndex);
int mConvertToDVBServiceType(int servicetype);
void module__init(void){
	memcpy((void*)mServicePriority,(void*)s__mServicePriority,sizeof(mServicePriority));
	RegionCachePoolId	=	s__RegionCachePoolId;
	mDbookConflictsPmp	=	s__mDbookConflictsPmp;
	memcpy((void*)mConflictList,(void*)s__mConflictList,sizeof(mConflictList));
	TOTAL_NUM_OF_CONFLICTS	=	s__TOTAL_NUM_OF_CONFLICTS;
	mConflictResolutionPass	=	s__mConflictResolutionPass;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef BUFFER_ADMIN_MEM
#undef BUFFER_ADMIN_MEM
#endif //BUFFER_ADMIN_MEM
#ifdef REGION_NONE
#undef REGION_NONE
#endif //REGION_NONE
#ifdef REGION_P
#undef REGION_P
#endif //REGION_P
#ifdef REGION_PS
#undef REGION_PS
#endif //REGION_PS
#ifdef REGION_PST
#undef REGION_PST
#endif //REGION_PST
#ifdef DIGITAL
#undef DIGITAL
#endif //DIGITAL
#ifdef ANALOG
#undef ANALOG
#endif //ANALOG
#ifdef DIGITAL_PRESET(presetdat)
#undef DIGITAL_PRESET(presetdat)
#endif //DIGITAL_PRESET(presetdat)
#ifdef SAME(x,
#undef SAME(x,
#endif //SAME(x,
#ifdef CURRENT_SERVICE_INDEX
#undef CURRENT_SERVICE_INDEX
#endif //CURRENT_SERVICE_INDEX
#ifdef VALID_PRIMARY_REGION(region)
#undef VALID_PRIMARY_REGION(region)
#endif //VALID_PRIMARY_REGION(region)
#ifdef VALID_SECONDARY_REGION(region)
#undef VALID_SECONDARY_REGION(region)
#endif //VALID_SECONDARY_REGION(region)
#ifdef VALID_TERTIARY_REGION(region)
#undef VALID_TERTIARY_REGION(region)
#endif //VALID_TERTIARY_REGION(region)
#ifdef PRIORITY_NOT_ASSIGNED(priority)
#undef PRIORITY_NOT_ASSIGNED(priority)
#endif //PRIORITY_NOT_ASSIGNED(priority)
#ifdef GET_LCN(svcdat)
#undef GET_LCN(svcdat)
#endif //GET_LCN(svcdat)
#ifdef TOTAL_NUM_OF_CONFLICTS
#undef TOTAL_NUM_OF_CONFLICTS
#endif //TOTAL_NUM_OF_CONFLICTS
#ifdef CONFLICT_LCN(Indx)
#undef CONFLICT_LCN(Indx)
#endif //CONFLICT_LCN(Indx)
#ifdef IS_VALID_CONFLICT(svcdat)
#undef IS_VALID_CONFLICT(svcdat)
#endif //IS_VALID_CONFLICT(svcdat)
#ifdef VALID_SERVICE_INDEX(i,
#undef VALID_SERVICE_INDEX(i,
#endif //VALID_SERVICE_INDEX(i,
#ifdef CALCULATE_DISTANCE(UserPST)
#undef CALCULATE_DISTANCE(UserPST)
#endif //CALCULATE_DISTANCE(UserPST)
#ifdef CONFLICT_SERVICE_DBINDEX(i,
#undef CONFLICT_SERVICE_DBINDEX(i,
#endif //CONFLICT_SERVICE_DBINDEX(i,
#ifdef IGNORE_NONE
#undef IGNORE_NONE
#endif //IGNORE_NONE
#ifdef IGNORE_TERTIARY
#undef IGNORE_TERTIARY
#endif //IGNORE_TERTIARY
#ifdef IGNORE_SECONDARYTERTIARY
#undef IGNORE_SECONDARYTERTIARY
#endif //IGNORE_SECONDARYTERTIARY
#ifdef SHIFT_BITS
#undef SHIFT_BITS
#endif //SHIFT_BITS
#ifdef MASK_REGION_TYPES(P,
#undef MASK_REGION_TYPES(P,
#endif //MASK_REGION_TYPES(P,
#ifdef MASK_REGION_CODE(P,
#undef MASK_REGION_CODE(P,
#endif //MASK_REGION_CODE(P,
#ifdef NO_PASS
#undef NO_PASS
#endif //NO_PASS
#ifdef FIRST_PASS
#undef FIRST_PASS
#endif //FIRST_PASS
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef MAX_SERVICE_TYPES
#undef MAX_SERVICE_TYPES
#endif //MAX_SERVICE_TYPES
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef TV_SERVICE
#undef TV_SERVICE
#endif //TV_SERVICE
#ifdef RADIO_SERVICE
#undef RADIO_SERVICE
#endif //RADIO_SERVICE
#ifdef TELETEXT_SERVICE
#undef TELETEXT_SERVICE
#endif //TELETEXT_SERVICE
#ifdef NVOD_REFERENCE_SERVICE
#undef NVOD_REFERENCE_SERVICE
#endif //NVOD_REFERENCE_SERVICE
#ifdef NVOD_TIMESHIFTED_SERVICE
#undef NVOD_TIMESHIFTED_SERVICE
#endif //NVOD_TIMESHIFTED_SERVICE
#ifdef MOSAIC_SERVICE
#undef MOSAIC_SERVICE
#endif //MOSAIC_SERVICE
#ifdef DATABROADCAST_SERVICE
#undef DATABROADCAST_SERVICE
#endif //DATABROADCAST_SERVICE
#ifdef DVBMHP_SERVICE
#undef DVBMHP_SERVICE
#endif //DVBMHP_SERVICE
#ifdef PRESET_NOT_ALLOCATED(svcdat)
#undef PRESET_NOT_ALLOCATED(svcdat)
#endif //PRESET_NOT_ALLOCATED(svcdat)
#ifdef INVALID
#undef INVALID
#endif //INVALID
#ifdef NO_REGION_CODE
#undef NO_REGION_CODE
#endif //NO_REGION_CODE
#ifdef NO_TERTIARY_REGION_CODE
#undef NO_TERTIARY_REGION_CODE
#endif //NO_TERTIARY_REGION_CODE
#ifdef SAME_RANK(uPST,
#undef SAME_RANK(uPST,
#endif //SAME_RANK(uPST,
#ifdef SAME_REGION_CODE_B4UK(index)
#undef SAME_REGION_CODE_B4UK(index)
#endif //SAME_REGION_CODE_B4UK(index)
#ifdef SAME_REGION_CODE_AFTERUK7(index)
#undef SAME_REGION_CODE_AFTERUK7(index)
#endif //SAME_REGION_CODE_AFTERUK7(index)
#ifdef SAME_REGION_CODE_AFTERUK6(index)
#undef SAME_REGION_CODE_AFTERUK6(index)
#endif //SAME_REGION_CODE_AFTERUK6(index)
#ifdef SAME_REGION_CODE_AFTERUK4(index)
#undef SAME_REGION_CODE_AFTERUK4(index)
#endif //SAME_REGION_CODE_AFTERUK4(index)
#ifdef SAME_REGION_CODE_AFTERUK0(index)
#undef SAME_REGION_CODE_AFTERUK0(index)
#endif //SAME_REGION_CODE_AFTERUK0(index)
#ifdef SAME_REGION_CODE_AFTERUK(UserPST,
#undef SAME_REGION_CODE_AFTERUK(UserPST,
#endif //SAME_REGION_CODE_AFTERUK(UserPST,
#ifdef MULT_SAME_REGION_CODE_B4UK(index)
#undef MULT_SAME_REGION_CODE_B4UK(index)
#endif //MULT_SAME_REGION_CODE_B4UK(index)
#ifdef MULT_SAME_REGION_CODE_AFTERUK7(index)
#undef MULT_SAME_REGION_CODE_AFTERUK7(index)
#endif //MULT_SAME_REGION_CODE_AFTERUK7(index)
#ifdef MULT_SAME_REGION_CODE_AFTERUK6(index)
#undef MULT_SAME_REGION_CODE_AFTERUK6(index)
#endif //MULT_SAME_REGION_CODE_AFTERUK6(index)
#ifdef MULT_SAME_REGION_CODE_AFTERUK4(index)
#undef MULT_SAME_REGION_CODE_AFTERUK4(index)
#endif //MULT_SAME_REGION_CODE_AFTERUK4(index)
#ifdef MULT_SAME_REGION_CODE_AFTERUK0(index)
#undef MULT_SAME_REGION_CODE_AFTERUK0(index)
#endif //MULT_SAME_REGION_CODE_AFTERUK0(index)
#ifdef MULT_SAME_REGION_CODE_AFTERUK(UserPST,
#undef MULT_SAME_REGION_CODE_AFTERUK(UserPST,
#endif //MULT_SAME_REGION_CODE_AFTERUK(UserPST,
#ifdef INVALID_REGION_DEPTH
#undef INVALID_REGION_DEPTH
#endif //INVALID_REGION_DEPTH
#endif //LOCAL_UNDEFINES
