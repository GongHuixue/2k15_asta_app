#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include	<stdio.h>

#include	<stdlib.h>

#include	<string.h>

#define	AUTO_MODE								(insstate_InstallationServiceScan)

#define	UPDATE_MODE							(insstate_InstallationUpdate)

#define	GETSERVICETYPE(servicetype)			( ((servicetype == AppApiRadioService) || (servicetype == AppApiAdvCodecRadioService)) ? HsvRadio: HsvOnePart )

#define	GETHSVSPID(prop, tableid)				(mHsvDVBPIDList[prop][tableid])

#define	ACTUAL_TABLE							(0)

#define	OTHER_TABLE							(1)

#define	IS_VALID_ONID							( (DataAcqInstance.Onid >= 0xFF00)? FALSE: TRUE )		

#define	IS_VALID_NID							( (DataAcqInstance.NetworkId >= 0xFF01)? FALSE: TRUE )

#define	IS_VALID_TSID							( TRUE ) /* Not using yet in field.. might come soon */

#define	IS_VALID_TS							( IS_VALID_ONID && IS_VALID_NID && IS_VALID_TSID )

#define	INVALID_PRESET							(0XFFFF)

#define	SAT_INFO_TABLE						(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	PTC_TABLE							    	(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	SERVICE_TABLE							(pgdbconst_Satellite | pgdbconst_DigitalService)

#define	PRESET_TABLE							(pgdbconst_Satellite | pgdbconst_Preset)

#define	INVALID_VERSION						(-1)

#define	VERSION1								(1)

#define	VERSION2								(2)	

#define     	LCN_VERSION2_PRESENT(NoOfRecs)		(NoOfRecs > 0)

#define 	MIN_VALID_LCN    						(0)

#define	MAX_VALID_LCN    						(1000)

#define	VALID_LCN_RANGE(x)  					(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))

#define	REVALIDATE(x)     						((x) &= 0x7FFF)  

#define 	IS_RADIO_SERVICE(x)     ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )

#define	ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	 { \
														svcdat1.Tpid	= svcdat2.Tpid; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
													 }

#define	MAX_LNBS_SUPPORTED						(4)

#define	IS_VALID_ROLLOFF(x)		(x<(sizeof(RollOffTable)/sizeof(RollOffTable[0])))

#define	MAX_SERVICES				(500)

#define	MAX_LCN_NUMBERS			(500)

#define 	MAX_SDSD					(50)

#define	ABS(freq1, freq2)			((freq1 >= freq2) ? (freq1 - freq2) : (freq2 - freq1))

#define 	FREQ_DRIFT_TOLERANCE		(4000)

#define 	BARKER_MUX_LINKAGE_TYPE	0x04

typedef enum
{
	Homing = 1,
	Fallback
}AcqMode;
typedef struct
{
	Nat16 Onid;
	Nat16 Tsid;
	Nat16 NetworkId;
	Nat16 NumSdsds;	
	Nat16 CurSdsd;
	Nat8	LnbNumber;
	Bool SDTOtherPresent;
	AcqMode Mode;
} HsvDataAcqInstance;
typedef enum
{
	EvStartAcquire = 0,
	EvAcquireTSInfo,
	EvCompleteAcquire
}AcqEvents;
typedef enum
{
	Onid = 0,
	Tsid,
	VerNo,
	SLD,
	SDSD,
	SpidService,
	LCNv1,
	LCNv2,
	MAX_PROPERTY_ID
}eDVBProperties;
typedef enum
{
	NoUpdate = 0,
	SDSDChange,
	AcqModeChange
}KeyUpdateReason;
typedef struct 
{
	Nat16 Onid;
	Nat16 Tsid;
	Nat16 ServiceId;
	Nat8  ServiceType;
	Nat16 NetworkId;
}SvcListInfo;
typedef struct
{
	Nat8 VersionNumber;
	Nat16 NumOfRecords;
	SvcListInfo mSvcListInfo[MAX_SERVICES];
}CanalServiceList;
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
}CanalLCNData;
typedef struct
{
	Nat8 NumOfSDSD;
	int CurrentSDSDIndex;
	HsvNITSatelliteDS SatDesc[MAX_SDSD];
}CanalSatDSDesc;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
CanalLCNData mLCNData;
static CanalLCNData s__mLCNData;
CanalServiceList mSvcListData;
static CanalServiceList s__mSvcListData;
CanalSatDSDesc mCanalDSDesc;
static CanalSatDSDesc s__mCanalDSDesc;
int mDigitalChannelsFound,mDigitalTvChannelsFound,mDigitalRadioChannelsFound;
static int s__mDigitalChannelsFound,s__mDigitalTvChannelsFound,s__mDigitalRadioChannelsFound;
Pump mDataAcqPump;
static Pump s__mDataAcqPump;
int removeCurTv,removeCurRadio;
static int s__removeCurTv,s__removeCurRadio;
HsvDataAcqInstance DataAcqInstance;
static HsvDataAcqInstance s__DataAcqInstance;
HsvInstallationPTC CurrentPTC;
static HsvInstallationPTC s__CurrentPTC;
HsvBarkerMuxData BarkerMuxData;
static HsvBarkerMuxData s__BarkerMuxData;
double RollOffTable[4];
static double s__RollOffTable[4];
int mHsvDVBPIDList[MAX_PROPERTY_ID][2];
static int s__mHsvDVBPIDList[MAX_PROPERTY_ID][2];
void mPumpHandler(int value, Nat32 param);
void mStartHomingAcquisition(void);
Bool mCollectBarkerMuxData(void);
void mStartFallbackAcquisition(void);
void mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc);
Bool mGetTSMetaData(void);
void mAcquireTSInfo(void);
void mDeleteTSTable(HsvInstallationPTC *ptc);
void mDeleteMuxesFromCurrentNIT(void);
Bool mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata);
void mAddToTSTable(HsvInstallationPTC *ptc, KeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData);
Bool mInstallHomingMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData);
Bool mInstallFallbackMux(HsvInstallationPTC ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData);
Bool mCheckServiceForInstall(HsvInstallationPTC *ptc, KeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData, SvcListInfo *ServiceList);
void mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc);
Bool mIsSvcPresentInServiceList(HsvPgdatDigServiceData *svcdata);
int mDeleteAllServicesFromCarrier(int Tpid);
void mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat);
void mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool IsDuplicatesvc);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
int CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner);
int mConvertToPgdatServiceType(int servicetype);
Bool IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat);
Bool IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat);
void mCopyString(Nat16* dest, Nat16* src, int maxchars);
Bool mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mCollectSdsds (void);
void mCollectServicelistData(void);
Bool mGetLCN(t_LCNInfo *LCNInfo);
Bool mAcquireLCNData(void);
Bool mLcnVersion1Data(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll);
Bool mLcnVersion2Data(int HsvPid, t_LCNInfo *LCNInfo, Bool AcquireAll);
Bool mPopulateLCN(Address data, int version);
void mGetInterestedLCNRecords(int HsvPid, int *from, int *to, int *countrycode);
int mGetInterestedChanneListId(int HsvPid, int from, int to, int *countrycode);
int mGetCorrespondingCountryForPackage(int packageid);
inline void mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int VisibleSvc, int version);
void mAssignLCN(HsvPgdatDigServiceData *psvcdat);
inline int mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId);
void mGetSDTOtherStatus(void);
void mGetSatelliteLnbNo(int SatId);
Bool IsManualInstall(void);
Bool IsUpdateInstall(void);
void module__init(void){
	mLCNData	=	s__mLCNData;
	mSvcListData	=	s__mSvcListData;
	mCanalDSDesc	=	s__mCanalDSDesc;
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
	mDigitalTvChannelsFound	=	s__mDigitalTvChannelsFound;
	mDigitalRadioChannelsFound	=	s__mDigitalRadioChannelsFound;
	mDataAcqPump	=	s__mDataAcqPump;
	removeCurTv	=	s__removeCurTv;
	removeCurRadio	=	s__removeCurRadio;
	DataAcqInstance	=	s__DataAcqInstance;
	CurrentPTC	=	s__CurrentPTC;
	BarkerMuxData	=	s__BarkerMuxData;
	memcpy((void*)RollOffTable,(void*)s__RollOffTable,sizeof(RollOffTable));
	memcpy((void*)mHsvDVBPIDList,(void*)s__mHsvDVBPIDList,sizeof(mHsvDVBPIDList));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef GETSERVICETYPE(servicetype)
#undef GETSERVICETYPE(servicetype)
#endif //GETSERVICETYPE(servicetype)
#ifdef GETHSVSPID(prop,
#undef GETHSVSPID(prop,
#endif //GETHSVSPID(prop,
#ifdef ACTUAL_TABLE
#undef ACTUAL_TABLE
#endif //ACTUAL_TABLE
#ifdef OTHER_TABLE
#undef OTHER_TABLE
#endif //OTHER_TABLE
#ifdef IS_VALID_ONID
#undef IS_VALID_ONID
#endif //IS_VALID_ONID
#ifdef IS_VALID_NID
#undef IS_VALID_NID
#endif //IS_VALID_NID
#ifdef IS_VALID_TSID
#undef IS_VALID_TSID
#endif //IS_VALID_TSID
#ifdef IS_VALID_TS
#undef IS_VALID_TS
#endif //IS_VALID_TS
#ifdef INVALID_PRESET
#undef INVALID_PRESET
#endif //INVALID_PRESET
#ifdef SAT_INFO_TABLE
#undef SAT_INFO_TABLE
#endif //SAT_INFO_TABLE
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef INVALID_VERSION
#undef INVALID_VERSION
#endif //INVALID_VERSION
#ifdef VERSION1
#undef VERSION1
#endif //VERSION1
#ifdef VERSION2
#undef VERSION2
#endif //VERSION2
#ifdef LCN_VERSION2_PRESENT(NoOfRecs)
#undef LCN_VERSION2_PRESENT(NoOfRecs)
#endif //LCN_VERSION2_PRESENT(NoOfRecs)
#ifdef MIN_VALID_LCN
#undef MIN_VALID_LCN
#endif //MIN_VALID_LCN
#ifdef MAX_VALID_LCN
#undef MAX_VALID_LCN
#endif //MAX_VALID_LCN
#ifdef VALID_LCN_RANGE(x)
#undef VALID_LCN_RANGE(x)
#endif //VALID_LCN_RANGE(x)
#ifdef REVALIDATE(x)
#undef REVALIDATE(x)
#endif //REVALIDATE(x)
#ifdef IS_RADIO_SERVICE(x)
#undef IS_RADIO_SERVICE(x)
#endif //IS_RADIO_SERVICE(x)
#ifdef ASSIGN_KEYS_OF_SVC(svcdat1,
#undef ASSIGN_KEYS_OF_SVC(svcdat1,
#endif //ASSIGN_KEYS_OF_SVC(svcdat1,
#ifdef MAX_LNBS_SUPPORTED
#undef MAX_LNBS_SUPPORTED
#endif //MAX_LNBS_SUPPORTED
#ifdef IS_VALID_ROLLOFF(x)
#undef IS_VALID_ROLLOFF(x)
#endif //IS_VALID_ROLLOFF(x)
#ifdef MAX_SERVICES
#undef MAX_SERVICES
#endif //MAX_SERVICES
#ifdef MAX_LCN_NUMBERS
#undef MAX_LCN_NUMBERS
#endif //MAX_LCN_NUMBERS
#ifdef MAX_SDSD
#undef MAX_SDSD
#endif //MAX_SDSD
#ifdef ABS(freq1,
#undef ABS(freq1,
#endif //ABS(freq1,
#ifdef FREQ_DRIFT_TOLERANCE
#undef FREQ_DRIFT_TOLERANCE
#endif //FREQ_DRIFT_TOLERANCE
#ifdef BARKER_MUX_LINKAGE_TYPE
#undef BARKER_MUX_LINKAGE_TYPE
#endif //BARKER_MUX_LINKAGE_TYPE
#endif //LOCAL_UNDEFINES
