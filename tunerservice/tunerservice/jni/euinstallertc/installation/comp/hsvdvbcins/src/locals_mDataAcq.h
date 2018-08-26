#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define     PRESET_ALLOCATED(PresetNo)  (PresetNo != INVALID_PRESET)

#define     DVBC_INVALID_FREECA_MODE    (-1)

#define		MAX_CHARACTERS							(128)

#define		MAX_LCN_NUMBERS						(1000)

#define		MAX_TS							(100)

typedef enum
{
	evStep0 = 0,
	evStep1,
	evStep2,
	evStepComplete,
}SvcSteps;
typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
    Nat16 NetworkId;
    int   TsVersionNum;
    Nat8  SDTVersion;
	Nat8  NITVersion;
	Nat16 HomingONID;
}t_DVBCData;
typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
	Nat16 ServiceId;
	Nat16 LogicalChannelNum;
	Bool  VisibleService;
	int	  LCNType;
}t_LCNInfo;
typedef struct
{
	Nat32 VersionNumber;
    Nat16 NumOfLCNRecords;
	t_LCNInfo mLCNInfo[MAX_LCN_NUMBERS];
}t_LCNsData;
typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
	Nat32 VersionNumber;
}t_SDTVersioData;
typedef struct
{
	Nat16 NumOfRecords;
	t_SDTVersioData Version[MAX_TS];
}t_SDTOtherData;

typedef struct
{
    Bool EnableBackground;
    Bool SemiSbyInstallRequired;
	Bool InProgress;
}t_DVBCSemiSby;
typedef enum
{
	EvStart = 0
}t_AcqEvents;
typedef enum
{
    Onid = 0,
    Tsid,
    VerNo,
    SpidService,
	LCNv1,
	LCNv2,
	HDSLCN,
    MAX_PROPERTY_ID
}eDVBProperties;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mHsvDVBPIDList[7][7];
static int s__mHsvDVBPIDList[7][7];
int mHsvDVBSortedTableList[2][2];
static int s__mHsvDVBSortedTableList[2][2];
t_DVBCData mDVBCData;
static t_DVBCData s__mDVBCData;
t_LCNsData mLCNData;
static t_LCNsData s__mLCNData;
Pump mAcqPump,mBackgroundPump;
static Pump s__mAcqPump,s__mBackgroundPump;
t_CableDSDesc mCurrCableDS,mFlashCableDS;
static t_CableDSDesc s__mCurrCableDS,s__mFlashCableDS;
t_ServiceList mSvcListData,mFlashSvcListData;
static t_ServiceList s__mSvcListData,s__mFlashSvcListData;
int mDigitalChannelsFound;
static int s__mDigitalChannelsFound;
char mDirName[MAX_CHARACTERS],mFileName[MAX_CHARACTERS];
static char s__mDirName[MAX_CHARACTERS],s__mFileName[MAX_CHARACTERS];
Bool mActive,mAcquistionInProgress,mSemiSbyInstallRequired,mVersionUpdateNeeded;
int BackGroundCount;
static int s__BackGroundCount;
static Bool s__mActive,s__mAcquistionInProgress,s__mSemiSbyInstallRequired,s__mVersionUpdateNeeded;
Bool updateBarkerMuxDvbcins;
static Bool s__updateBarkerMuxDvbcins;
t_SDTOtherData mSDTOtherVersion;
static t_SDTOtherData s__mSDTOtherVersion;
Bool ServiceNameUpdated;
static Bool s__ServiceNameUpdated;
static int	s__BackGroundCountInAcq;
int BackGroundCountInAcq;

void mPumpHandler(int value, Nat32 param);
Nat8 mGetNITVersion(void);
Bool mGetTSMetaData(void);
Nat8 mGetSdtOtherVersion(int OnId,int TsId);
void mStoreSdtOtherVersion();
void mCheckAllPTCForBackgroundInstall(); 
void mCheckSDTOtherForBackgroundInstall(int Onid, int Tsid);
void mCheckSDTOtherServiceForInstall(HsvInstallationPTC* ptc,HSVSPTYPE(ActualCableDS, dvb, nit)	*CDSD,HSVSPTYPE(ActualTSService, dvb, sdt)* service);
Bool mIsSDTOtherServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(OtherTSService, dvb, sdt)* service);
Bool IsTSversionStored(int Onid,int Tsid);
Bool mInstallMux(HsvInstallationPTC *ptc);
void mAddToTSTable(HsvInstallationPTC *ptc);
Bool mDuplicateEntry(HsvPgdatDigServiceData svcdat, int tableid);
Bool mCheckServiceForInstall(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
void mUpdateServiceTableRecords(int evCurrentStep);
void mDeleteServiceNotInTransmission(int evCurrentStep);
void mUpdatePtcTableRecords(int evCurrentStep);
void mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp);
void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp);
void mCopyString(Nat16* dest, Nat16* src, int maxchars);
int mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId);
Bool mOperatorUPCInstallRules(HsvPgdatDigServiceData svcdat);
Bool mOperatorRCSRDSInstallRules(HsvPgdatDigServiceData svcdat);
Bool mOperatorBlizooInstallRules(HsvPgdatDigServiceData svcdat);
int mConvertToDVBServiceType(int servicetype);
int mConvertToPgdatServiceType(int servicetype);
void mAcquireServiceListData(void);
Bool mLcnVersion1Data(Nat16 NetworkId, int HsvPid, t_LCNInfo *LCNInfo, int ActionOnData);
Bool mHdsLcnData(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData);
Bool mLcnVersion2Data(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData);
Bool mPopulateLCN(Address data, int version);
void mGetInterestedLCNRecords(int HsvPid, int DBTableId, int *from, int *to, int *countrycode);
int mGetInterestedChanneListId(int HsvPid, int from, int to, int *countrycode);
inline void mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version);
Bool mGetLCNData(t_LCNInfo *LCNInfo, int ActionOnData);
void mAssignLCN(HsvPgdatDigServiceData *psvcdat);
void mGetPTCInfo(HsvInstallationPTC *ptc);
void mAddToFreqMapTable(HsvInstallationPTC ptc);
Bool mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat);
Bool mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mBackgroundPumpHandler(int event, Nat32 param );
void mBackgroundOnInit(void);
void mBackgroundInitialise(void);
void mStartBackgroundInstall(void);
void mGetPathName(char* dirName, char* FileName , char* PathName);
void mLoadCableDS(void);
void mLoadSLD(void);
void mCheckPTCForBackgroundInstall(HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) Service, int TotalServices);
void mBackgroundUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mBackgroundNewService(HsvPgdatDigServiceData* svcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mUpdateServiceName(HsvPgdatDigServiceData* psvcdat, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
Bool mCheckForLCNUpdate(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mCheckNITForBackgroundInstall(HsvInstallationPTC ptc);
void mUpdateTsBackgroundInstall(void);
Bool mCompareCDSDFromStrapi(int hsvspid);
Bool mCompareCableDS(void);
Bool mCompareSLD(void);
Bool mCompareLCN(void);
void mWriteSLDToFlash(void);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
Bool mCheckForHDSimulcastLinkageUpdate(HsvPgdatDigServiceData *svcdat);
Bool mIgnoreUPCBackgroundNetworkUpdate (void);
void module__init(void){
	memcpy((void*)mHsvDVBPIDList,(void*)s__mHsvDVBPIDList,sizeof(mHsvDVBPIDList));
	memcpy((void*)mHsvDVBSortedTableList,(void*)s__mHsvDVBSortedTableList,sizeof(mHsvDVBSortedTableList));
	mDVBCData	=	s__mDVBCData;
	mLCNData	=	s__mLCNData;
	mAcqPump	=	s__mAcqPump;
	mBackgroundPump	=	s__mBackgroundPump;
	mCurrCableDS	=	s__mCurrCableDS;
	mFlashCableDS	=	s__mFlashCableDS;
	mSvcListData	=	s__mSvcListData;
	mFlashSvcListData	=	s__mFlashSvcListData;
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
	memcpy((void*)mDirName,(void*)s__mDirName,sizeof(mDirName));
	memcpy((void*)mFileName,(void*)s__mFileName,sizeof(mFileName));
	mActive	=	s__mActive;
	mAcquistionInProgress	=	s__mAcquistionInProgress;
	mSemiSbyInstallRequired	=	s__mSemiSbyInstallRequired;
	mVersionUpdateNeeded	=	s__mVersionUpdateNeeded;
	updateBarkerMuxDvbcins	=	s__updateBarkerMuxDvbcins;
	BackGroundCount	=	s__BackGroundCount;
	mSDTOtherVersion	=	s__mSDTOtherVersion;
	BackGroundCountInAcq = s__BackGroundCountInAcq;
}
void mDeleteHDSimulcastSDServices(void);
void mAssignSvcHDSimulcastLinkageParams( HsvPgdatDigServiceData *svcdat );
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef PRESET_ALLOCATED(PresetNo)
#undef PRESET_ALLOCATED(PresetNo)
#endif //PRESET_ALLOCATED(PresetNo)
#ifdef DVBC_INVALID_FREECA_MODE
#undef DVBC_INVALID_FREECA_MODE
#endif //DVBC_INVALID_FREECA_MODE
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef MAX_LCN_NUMBERS
#undef MAX_LCN_NUMBERS
#endif //MAX_LCN_NUMBERS
#endif //LOCAL_UNDEFINES
