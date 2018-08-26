#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void mCabsortHandler(int value, Nat32 param);
void mNoSorting(int evCurrentSortStep);
void mSortAnalogServices(int evCurrentSortStep);
void mSortHonouredServices(Bool CheckForRadioServices, int evCurrentSortStep, Nat32 decoderType);
void mSortNonHonouredServices(Bool CheckForRadioServices, int evCurrentSortStep, Nat32 decoderType);
void mSortNonHonouredServicesRCSRDS(int evCurrentSortStep);
void mDigitalPresetEntryforInValidLCN_Blizoo(int dbindex);
void mSortNonHonouredServicesBlizoo(int evCurrentSortStep);
void mDigitalPresetEntryforValidLCN(int dbindex);
void mDigitalPresetEntryforInValidLCN(int dbindex);
void mDigitalPresetEntryforInValidLCN_RCSRDS(int dbindex);
int mAddPresetEntryForInstalledAnalog(HsvPgdatAnalogData anadat, int PresetNumber);
Bool mAddPresetEntryForNewAnalog(HsvPgdatAnalogData *anadat, int PresetNumber);
int mCompareServices(HsvPgdatDigServiceData *svcdata, int pref_index);
int mStrCmp(Nat16 *str1, Nat16 *str2);
int mGetServicePriority(int serviceType);
void mReadCableDS(void);
void mGetFileName(char *FileName, char *FilePath);
void mDeleteTSByIndex(int index);
void mAssignPresetsFromStaticTable(Bool CheckForRadioServices, int evCurrentSortStep);
void mAddOrUpdateEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, Bool AddOrUpdate);
Bool mIsPresetReplacable(HsvPgdatPresetData presetdat, HsvPgdatDigServiceData svcdat);
Bool mIsCurrentPresetInvalid( int PresetNo, int ServiceType);
inline void mFindPresetNumberForService(int ServiceType);
void mAssignPresetNumberForService(int ServiceType);
inline int mLastLCNBasedPreset(Bool CheckForRadioServices);
int mLargestGapInForwardRange(int FromPreset, int ToPreset);
Bool mValidPresetForService(int presetnum, int svcType);
void mGetPresetRangeForService(int svcType, int *startpreset, int *endpreset);
void mReInnovateFromPreset(int ServiceType, int *FromPreset);
Bool mTSInTransmission(void);
inline int ANALOG_STARTPRESET(void);
inline int NONRADIO_STARTPRESET(void);
inline int RADIO_STARTPRESET(void);
int mGetAutomaticPlatformPresetNumber(void);
Bool mStaticSortingAvailable(Nat16 NetworkId);
Bool mGetValidRangeofPreset(int PresetNo, int ServiceType);
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#endif //LOCAL_UNDEFINES
