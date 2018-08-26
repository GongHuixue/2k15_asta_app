#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define WINDOWID  (wnddest_GetWindowId(HsvMain))

#define PRESET_ALLOCATED(PresetNo)  (PresetNo != INVALID_PRESET)

#define DVBC_INVALID_FREECA_MODE (-1)

#define INVALID_INDEX                   ( -1 )

#define CHANNELLIST_NAME_LENGTH (33)

#define INVALID_CHANNELLIST_ID (0xFFFF)

#define INVALID_TPS_ID	(-1)

#define     VALID_PRIMARY_REGIONID(region)        ( (region) <= (int)0xFF )
#define     VALID_SECONDARY_REGIONID(region)      ( (region) <= (int)0xFF )
#define     VALID_TERTIARY_REGIONID(region)       ( (region) <= (int)0xFFFF )

#define     MASK_REGION_TYPES(P, S, T)          ( ((VALID_PRIMARY_REGIONID(P))   << 2) | \
													((VALID_SECONDARY_REGIONID(S)) << 1) | \
													(VALID_TERTIARY_REGIONID(T))     )
#define 	IS_VALID_REGION(P,S,T)			( VALID_PRIMARY_REGIONID(P) || VALID_SECONDARY_REGIONID(S) || VALID_TERTIARY_REGIONID(T) )

#define		NO_TRD_MATCH		(0)
#define		SELECT_CURRENT_MUX	(1)
#define		SELECT_OTHER_MUX	(2)

#define		PRIMARY_REGION_MATCH		(4)
#define		SECONDARY_REGION_MATCH		(2)
#define		TERTIARY_REGION_MATCH		(1)


#define		FIND_MATCHING_TRD(PrimaryRegion,SecondaryRegion,TertiaryRegion,RegionCache,Count,Result)		if(VALID_PRIMARY_REGIONID(PrimaryRegion)) {\
									for (Count = 0; Count < MAX_REGIONS_PER_SERVICE; Count++) { \
										if ((RegionCache.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] != INVALID_REGION_DEPTH) &&\
											(RegionCache.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] >= 1) &&\
											(RegionCache.RegionList.RegionMap [Count][MULT_PRIMARY_INDEX] == PrimaryRegion)) {\
											Result = PRIMARY_REGION_MATCH;\
											/* Now check for Matching Secondary. Check the region depth to see if Secondary is supported */ \
											if (VALID_SECONDARY_REGIONID(SecondaryRegion)) { \
												if ((RegionCache.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] >= 2) && \
													(RegionCache.RegionList.RegionMap [Count][MULT_SECONDARY_INDEX] == SecondaryRegion)) { \
													Result |= SECONDARY_REGION_MATCH; \
													/* Now go for matching Tertiary Region ID */ \
													if (VALID_TERTIARY_REGIONID(TertiaryRegion)) {\
														if ((RegionCache.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] >= 3) && \
															(RegionCache.RegionList.RegionMap [Count][MULT_TERTIARY_INDEX] == TertiaryRegion)) {\
															Result |= TERTIARY_REGION_MATCH; \
															break; \
														}\
													} else { \
														break; \
													} \
												}\
											} else {\
												break; \
											} \
										}\
									} \
								}





#define SAME_RANK(uPST, sPST)       (!((uPST) ^ (sPST)))
#define MULT_SAME_REGION_CODE(PST)			(TRUE)
typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
    Nat16 ServiceId;    
}st_LCNInfo;
#define TYPE_SDT    0x01

#define BUFF_ADMIN_MEMORY   100
#define MAX_NUMBER_CHANNELLIST_IDS 100

typedef struct NwIDCache
{
    Nat16                   NetworkId;
    Nat16                   NetworkName[MAX_NETWORK_NAME_SIZE];
}TypeNwIDCache;

typedef struct TypeChannelID_services
{
	Nat16					ServiceId;
	Nat16					VisibiltyFlag;
	Nat16					LCN;
	Nat16					Original_NetworkId;
	Nat16					Tsid;
}ChannelID_services;
typedef struct Type_CachedChannelList
{
	Nat8					ChannelId;			
	Nat16					ChannelListName[MAX_CHANNEL_LIST_NAME_SIZE];
	Nat16					NoOfServiceInChannelList;
	TypeChannelID_services ChannelID_services[MAX_NUMBER_SERVICES];
}CachedChannelList_ts;

typedef struct Channel_list_data
{
	Type_CachedChannelList		CachedChannelList[MAX_NUMBER_CHANNELLIST_IDS];
	Nat8						TotalNumberofChannelListId;
}ChannelListData ;

typedef struct Region_data
{
	Nat16 Index;
	Nat16 RegionDataAvailable;
	Nat16 PrimryRegionMatch;
	Nat16 SecondaryRegionMatch;
	Nat16 TertiaryRegionMatch;
}RegionData;


Nat32 mInterpretCountryCode( Nat32 country );

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
st_LCNInfo mLCNInfo[MAX_NUMBER_SERVICES];
static st_LCNInfo s__mLCNInfo[MAX_NUMBER_SERVICES];
HsvNetworkRegionsData mRegionsData;
static HsvNetworkRegionsData s__mRegionsData;
int mUserPrimaryRegionIndex,mUserSecondaryRegionIndex,mUserTertiaryRegionIndex;
static int s__mUserPrimaryRegionIndex,s__mUserSecondaryRegionIndex,s__mUserTertiaryRegionIndex;
HsvTargetRegionCache * mTargetRegionCache;
static HsvTargetRegionCache * s__mTargetRegionCache;
int TargetRegionCachePoolId;
static int s__TargetRegionCachePoolId;
Bool updateBarkerMuxDvbtins;
static Bool s__updateBarkerMuxDvbtins;
int mNetworkIndex;
static int s__mNetworkIndex;
TypeNwIDCache NwIDCache[MAX_MUXES_PER_NTK];
ChannelListData ChannelListDataCache;
//static ChannelListData s_ChannelListDataCache;
static TypeNwIDCache s__NwIDCache[MAX_MUXES_PER_NTK];
void mCreateLCNList(void);
void InsertLCNList(Nat16 Onid,Nat16 Tsid,Nat16 ServiceId);
void mPumpHandler(int value, Nat32 param);
void mUpdateServiceTableRecords(int evCurrentStep);
void mDeleteServiceNotInTransmission(int evCurrentStep);
void mUpdatePtcTableRecords(int evCurrentStep);
Bool mInstallMux ( HsvInstallationPTC *ptc );
void mCopyString(Nat16 *dest, Nat16 *src, int maxchars);
Bool mGetTSMetaData(void);
int mConvertToPgDataServiceType  (int servicetype);
void mUpdateService (HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
Bool mCompareMultiplex(HsvPgdatDigTSData tsdata, HsvInstallationPTC *ptc );
Bool mCheckServiceForInstall (HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service);
Bool mDuplicateEntry(HsvPgdatDigServiceData *psvcdat1, HsvPgdatDigServiceData *psvcdat2);
void mAddToFreqMapTable(HsvInstallationPTC ptc);
void mAddToTSTable(HsvInstallationPTC ptc);
Bool mLCNParsingRequired(Nat16 OnwId);
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp);
void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat);
Bool mLcnVersion2Data(HsvPgdatDigServiceData *psvcdat);
inline int mGetInterestedChanneListId(int from, int to, int *countrycode);
void mAssignLCN(HsvPgdatDigServiceData *psvcdat);
void mDeleteServicesOfSameMux(Nat32 Frequency, Nat32 StreamPriority);
inline void mLCNOverRuling(HsvPgdatDigServiceData *svcdat);
void mAssignSvcHDSimulcastLinkageParams( HsvPgdatDigServiceData *svcdat );
void mDeleteHDSimulcastSDServices(void);
Bool mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat);
void mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat);
Bool mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
void mDbookInitialise(void);
void mDbookAcquireNetworkData(void);
void mDbookAcquireServiceData(HsvPgdatDigServiceData *psvcdat);
void mClearCache(void);
void mAddRegionInList(HsvNITTargetRegionName TargetRegionName);
void mAssignLCNForDbook(HsvPgdatDigServiceData *psvcdat);
void mApmeaChannelListData(void);
void mAddChannelListNameInList(HsvNITLCN2 ChannelListName);
int mGetPrimaryRegionIndex(Nat16 RegionCode, Nat32 Langcode, Bool *UpdateEntry);
int mGetSecondaryRegionIndex(Nat16 RegionCode, Nat32 Langcode, int PrimaryIndex, Bool *UpdateEntry);
int mGetTertiaryRegionIndex(Nat16 RegionCode, Nat32 Langcode, int PrimaryIndex, int SecondaryIndex, Bool *UpdateEntry);
void mAddinCachedRegionList ( HsvSDTTargetRegion * TargetRegion, HsvPgdatDigServiceData *psvcdat );
void mAssignLCNForFrance(HsvPgdatDigServiceData *psvcdat);
void mAssignMultipleLCN(HsvPgdatDigServiceData *psvcdat);
void mStoreNetworkName(void);
void mSortbyName(void);
int Unistrcmp(Nat16 *s1, Nat16 *s2);
void mRiksTvInitialise(void);
void mRiksTvAcquireData(void);
void mDeleteSDTActuallNotService(HsvInstallationPTC *ptc);
void mAddToCachedChannelListID(void);
void mAssignLCNforChannelList(int UserSelectedFavChannelList,HsvPgdatDigServiceData *psvcdat);
Bool mInstallCellIdService(HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) service,int *InstalledServices);
Nat32 mAdjustFrequency(Nat32 Frequency);
Bool GetSvcNameWithCurrentLanguage(HsvPgdatDigServiceData *psvcdat, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
/* Newly added functions */
Bool mCompareTSSignal(HsvPgdatDigTSData tsdata, HsvPgdatDigTSData ts2data );
int mGetPSTIndexFromCache (HsvPgdatDigServiceData *SvcDat);
Bool mCheckAndComparePSTFromStrapiForAutoInstall (HsvPgdatDigServiceData *SvcDat, int PSTIndexInCache);
int  mCheckAndComparePSTFromStrapiForUpdateInstall (HsvPgdatDigServiceData *SvcDat, int PSTIndexInCache);
int mIdentifyHighPrioServiceIndex(int from, int to, Nat16 PrimaryRegion, Nat16 SecondaryRegion, Nat32 TertiaryRegion);
int DeleteLowPrioServices(int from, int to, int HighPrioMuxIndex);

void module__init(void){
	memcpy((void*)mLCNInfo,(void*)s__mLCNInfo,sizeof(mLCNInfo));
	mRegionsData	=	s__mRegionsData;
	mUserPrimaryRegionIndex	=	s__mUserPrimaryRegionIndex;
	mUserSecondaryRegionIndex	=	s__mUserSecondaryRegionIndex;
	mUserTertiaryRegionIndex	=	s__mUserTertiaryRegionIndex;
	mTargetRegionCache	=	s__mTargetRegionCache;
	TargetRegionCachePoolId	=	s__TargetRegionCachePoolId;
	updateBarkerMuxDvbtins	=	s__updateBarkerMuxDvbtins;
	mNetworkIndex	=	s__mNetworkIndex;
	memcpy((void*)NwIDCache,(void*)s__NwIDCache,sizeof(NwIDCache));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef PRESET_ALLOCATED(PresetNo)
#undef PRESET_ALLOCATED(PresetNo)
#endif //PRESET_ALLOCATED(PresetNo)
#ifdef DVBC_INVALID_FREECA_MODE
#undef DVBC_INVALID_FREECA_MODE
#endif //DVBC_INVALID_FREECA_MODE
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef TYPE_SDT
#undef TYPE_SDT
#endif //TYPE_SDT
#ifdef BUFF_ADMIN_MEMORY
#undef BUFF_ADMIN_MEMORY
#endif //BUFF_ADMIN_MEMORY
#endif //LOCAL_UNDEFINES
