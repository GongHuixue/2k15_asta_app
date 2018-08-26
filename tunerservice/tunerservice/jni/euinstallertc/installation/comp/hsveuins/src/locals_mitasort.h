#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void mItaSortHandler(int value, Nat32 param);
void mNoSorting(int evCurrentSortStep);
void mSortHonouredServices(int evCurrentSortStep);
void mDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
void mSortNonHonouredServices(int evCurrentSortStep);
void mDigitalPresetEntryforInValidLCN(int dbindex);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp( Nat16 * str1, Nat16 * str2 );
int mGetServicePriority(int serviceType);
void mSortAnalogServices(int evCurrentSortStep);
void mAutonomousSortingHonouredServices(void);
void mAutonomousDigitalPresetEntryforValidLCN(HsvPgdatDigServiceData *svcdat);
void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);
Bool mIsPresetOccupied(int PresetNumber);
int mPlaceNonHonouredOrAnalogServices(void);
int mFirstGapInForwardRange(int FromPreset, int ToPreset);
int mFirstGapInReverseRange(int FromPreset, int ToPreset);
void mConflictDetection(HsvPgdatDigServiceData *svcdat);
inline void mFindPresetNumberForService(int AnalogOrDigital);
int mGetAutomaticPlatformPresetNumber(void);
Bool mServiceIsOfPreviousPass(HsvPgdatPresetData presetdat);
Bool mCanServiceBeHonoured(HsvPgdatDigServiceData *currsvcdat);
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#endif //LOCAL_UNDEFINES
