#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define		MAX_LCN_NUMBERS							(500)

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
    Nat8 VersionNumber;
    Nat16 NumOfRecords;
    struct
    {
        Nat16 Onid;
        Nat16 Tsid;
	    Nat16 ServiceId;
		Nat8  ServiceType;
    }mSvcListInfo[MAX_SERVICES];
}t_CanalDigitalServiceList;
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
t_CanalDigitalServiceList mSvcListData;
static t_CanalDigitalServiceList s__mSvcListData;
int mDigitalChannelsFound;
static int s__mDigitalChannelsFound;
Bool updateBarkerMuxCanalDigital;
static Bool s__updateBarkerMuxCanalDigital;
void mInstallMux(void);
void mAddToTSTable(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid);
Bool mDuplicateEntry(HsvPgdatDigServiceData svcdat, int tableid);
void mCheckAndNotifyAttributeChange (HsvPgdatDigServiceData* newsvcdat, HsvPgdatDigServiceData* cursvcdat);
Bool mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void UpdateBarkerMuxInfo(Bool IsBarkerMux);
Bool mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
inline void mCopyString(Nat16* dest, Nat16* src, int maxchars);
inline int mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId);
Bool mInstallBasedOnHDSLcns(HsvPgdatDigServiceData svcdat1);
inline Bool mOperatorCanalDigitalInstallRules(HsvPgdatDigServiceData *svcdat);
void mAssignSvcHDSimulcastLinkageParams( HsvPgdatDigServiceData *svcdat);
void mDeleteHDSimulcastSDServices(void);
Bool mLcnVersion1Data(Nat16 NetworkId, int HsvPid, t_LCNInfo *LCNInfo, int ActionOnData);
Bool mHdsLcnData(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData);
Bool mLcnVersion2Data(Nat16 NetworkId, int HsvPid, int DBTableId, t_LCNInfo *LCNInfo, int ActionOnData);
Bool mPopulateLCN(Address data, int version);
void mGetInterestedLCNRecords(int HsvPid, int DBTableId, int *from, int *to, int *countrycode);
int mGetInterestedChanneListId(int HsvPid, int from, int to, int *countrycode);
inline void mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version);
Bool mGetLCNData(t_LCNInfo *LCNInfo, int ActionOnData);
void mAssignLCN(HsvPgdatDigServiceData *psvcdat);
void mAddToFreqMapTable(HsvInstallationPTC ptc, Nat16 Onid, Nat16 Tsid);
Bool mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat);
void mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat);
Nat8 mGetNITVersion(void);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
int mConvertToDVBServiceType(int servicetype);
int mConvertToPgdatServiceType(int servicetype);
void mUpdateServiceNameForCanalDigitalandYousee(HsvPgdatDigServiceData* psvcdat);
void mDeleteServiceNotInTransmission();
Bool mCanalDigitalNetwork();

void module__init(void){
	memcpy((void*)mHsvDVBPIDList,(void*)s__mHsvDVBPIDList,sizeof(mHsvDVBPIDList));
	memcpy((void*)mHsvDVBSortedTableList,(void*)s__mHsvDVBSortedTableList,sizeof(mHsvDVBSortedTableList));
	mDVBCData	=	s__mDVBCData;
	mLCNData	=	s__mLCNData;
	mSvcListData	=	s__mSvcListData;
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
	updateBarkerMuxCanalDigital	=	s__updateBarkerMuxCanalDigital;
}


TypeInstallationStatus InsStatus;
static TypeInstallationStatus s__InsStatus;
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MAX_LCN_NUMBERS
#undef MAX_LCN_NUMBERS
#endif //MAX_LCN_NUMBERS
#endif //LOCAL_UNDEFINES
