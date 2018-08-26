#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#define     VALID_PRIMARY_REGION(region)        ( (region) <= (int)0xFF )	
#define     VALID_SECONDARY_REGION(region)      ( (region) <= (int)0xFF )
#define     VALID_TERTIARY_REGION(region)       ( (region) <= (int)0xFFFF )
Bool mIsHdSdFromUserSelectedRegion(HsvPgdatDigServiceData *HdService, HsvPgdatDigServiceData *SdService);
void mNoSorting(int evCurrentSortStep);
void mDvbtSortHandler(int value, Nat32 param);
void mSortHonouredServices(int evCurrentSortStep, Bool CheckForHDLCN);
Bool mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN);
void mSortNonHonouredServices(int evCurrentSortStep);
void mDigitalPresetEntryforInValidLCN(int dbindex);
int mGetCurrentInstallationVersion(void);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp( Nat16 * str1, Nat16 * str2 );
int mGetServicePriority(int serviceType);
void mSortAnalogServices(int evCurrentSortStep);
void mSortHDAndSDConflictServices(int evCurrentSortStep);
void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);
inline Bool mIsPresetOccupied(int PresetNumber);
inline void mFindPresetNumberForService(int AnalogOrDigital);
int mGetAutomaticPlatformPresetNumber(void);
Bool mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat);
Bool mCanServiceBeHonoured(HsvPgdatDigServiceData *currsvcdat, Bool CheckForHDLCN);
Bool mConflictDetection(HsvPgdatDigServiceData *svcdat, Bool CheckForHDLCN);
int mFindFirstGapInRange(int FromPreset, int ToPreset);

void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#endif //LOCAL_UNDEFINES
