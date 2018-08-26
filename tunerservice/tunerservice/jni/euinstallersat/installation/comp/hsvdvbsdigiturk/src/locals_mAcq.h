#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include	<stdio.h>

#include	<stdlib.h>

#include	<string.h>

#include	<math.h>

#define		AUTO_MODE								(insstate_InstallationServiceScan)

#define		ADDSAT_MODE								(insstate_InstallationAddSatellite)

#define		UPDATE_MODE								(insstate_InstallationUpdate)

#define		AUTOUPDATE_MODE							(insstate_InstallationAutomaticUpdate)

#define		GETSERVICETYPE(servicetype)				( (servicetype == AppApiRadioService)? HsvRadio: HsvOnePart )

#define		GETHSVSPID(prop, tableid)				(mHsvDVBPIDList[prop][tableid])

#define		ACTUAL_TABLE							(0)

#define		OTHER_TABLE								(1)

#define		IS_NOT_USER_INSTALLED(tsdata)			( (tsdata).UserInstalled == FALSE )

#define		INVALID_LCN								(0xC000)

#define		INVALID_PRESET							(0xFFFF)

#define		SAT_INFO_TABLE							(pgdbconst_Satellite | pgdbconst_SatInfo)

#define		PTC_TABLE							    (pgdbconst_Satellite | pgdbconst_DigitalTS)

#define		SERVICE_TABLE							(pgdbconst_Satellite | pgdbconst_DigitalService)

#define		PRESET_TABLE							(pgdbconst_Satellite | pgdbconst_Preset)

#define     ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	 { \
														svcdat1.Tpid	= svcdat2.Tpid; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
													 }

#define		MAX_LNBS_SUPPORTED						(4)

#define		MAX_LCN_NUMBERS							(1500)

#define		GET_LCN									(1)

#define		ACQUIRE_LCNS							(2)

#define		VALID_LCN_RANGE(LCN)					( (LCN > 0) && (LCN < 1000) )

#define		MAX_SERVICES_IN_SINGLE_STEP				(300)

#define		MAX_NUM_SDSD							(500)

#define		FREQ_DRIFT_TOLERANCE					(4000)

#define 	BARKER_MUX_LINKAGE_TYPE					(0x04)

typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
    Nat16 NetworkId;
    int   TsVersionNum;
    Nat8  SDTVersion;
} HsvDataAcqInstance;
typedef struct
{
    Nat16 BouquetId;
    Nat16 Original_NetworkId;
    Nat16 Tsid;
    Nat16 ServiceId;
    Nat16 LogicalChannelNum;
	Nat16 Frequency;
	Nat8  Polarization;
    Nat16 DpTsid;	
    Nat16 DpServiceId;
}t_LCNInfo;
typedef struct
{
	Nat32 VersionNumber;
    Nat16 NumOfLCNRecords;
	t_LCNInfo mLCNInfo[MAX_LCN_NUMBERS];
}t_LCNsData;
typedef enum
{
	EvStartAcquistion = 0,
	EvSyncRecords
}AcqEvents;
typedef enum
{
    Onid = 0,
    Tsid,
    VerNo,
    SpidService,
    MAX_PROPERTY_ID
}eDVBProperties;
typedef struct SDSDList
{
	int	Lnb;
	int NumofSDSDs;
	HSVSPTYPE(SatelliteDS, dvb, nit) SDSD[MAX_NUM_SDSD];
} SDSDList;
typedef struct HomingMuxData 
{
	Nat32	Frequency;
	Nat8	Polarization;
	Nat16	SatelliteId;
} HomingMuxData;
typedef struct PackageDetails
{
	Nat32 BouquetIndex;
	const HomingMuxData* HomingMuxDetails;
} PackageDetails;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mDataAcqPump;
static Pump s__mDataAcqPump;
int mDigitalTvChannelsFoundInLnb[MAX_LNBS_SUPPORTED],mDigitalRadioChannelsFoundInLnb[MAX_LNBS_SUPPORTED];
static int s__mDigitalTvChannelsFoundInLnb[MAX_LNBS_SUPPORTED],s__mDigitalRadioChannelsFoundInLnb[MAX_LNBS_SUPPORTED];
int mDigitalTranspondersFound;
static int s__mDigitalTranspondersFound;
int mCurrentLnb,mDigitalChannelsFound;
static int s__mCurrentLnb,s__mDigitalChannelsFound;
int mDigitalTVChannelsRemoved,mDigitalRadioChannelsRemoved;
static int s__mDigitalTVChannelsRemoved,s__mDigitalRadioChannelsRemoved;
HsvDataAcqInstance DataAcqInstance;
static HsvDataAcqInstance s__DataAcqInstance;
t_LCNsData mLCNData;
static t_LCNsData s__mLCNData;
HsvBarkerMuxData BarkerMuxData;
static HsvBarkerMuxData s__BarkerMuxData;
Nat16 mUnicodeBuffer[11];
static Nat16 s__mUnicodeBuffer[11];
int mHsvDVBPIDList[MAX_PROPERTY_ID][2];
static int s__mHsvDVBPIDList[MAX_PROPERTY_ID][2];
Nat16 mMapBouquetIdtoPackageId(Nat32 PackageId);
void mPumpHandler(int value, Nat32 param);
Bool mIsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat);
Bool mIsDigitalRadioService (HsvPgdatDigServiceData *psvcdat);
Bool mGetTSMetaData(void);
Bool mInstallMux(HsvInstallationPTC *ptc);
void mAcquireData(void);
void mAddToTSTable(HsvInstallationPTC *ptc);
Bool mCheckServiceForInstall(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service, int DuplicateIndex);
void mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat);
void mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service);
Nat16 * mAsciiToUnicode(char *ascii_str,int length)
/*--------------------------------------------------------------------------------------------------------------------------*/;
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
void mCopyString(Nat16* dest, Nat16* src, int maxchars);
Bool mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
Bool mIsManualInstall(void);
Bool mIsUpdateInstall(void);
Bool mIsServiceScanInstall (void);
Bool mGetLCNData(Nat16 BouquetId, t_LCNInfo *LCNInfo, int ActionOnData);
inline void mCopyLCNInfo(t_LCNInfo *LCNInfo, int OnId, int TsId, int SvcId, int Lcn, int DpServiceId, int DpTsid);
Bool mPopulateLCN(Address data);
int mGetLCNIndex(Nat16 Onid, Nat16 Tsid, Nat16 ServiceId);
void mAssignLCN(HsvPgdatDigServiceData *psvcdat);
void mSyncServiceRecords(int EvCurrentRecordIndex);
void mSyncPtcRecords(void);
Bool mDuplicateEntry(HsvPgdatDigServiceData svcdat, int *DuplicateIndex);
Bool mPresentInSDSD(HsvPgdatDigTSData *tsdata);
void mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat);
int  mGetSatelliteLnbNo(int SatId);
Bool mCollectEutelSatBarkerMuxData(void);
Bool mCollectTurkSatBarkerMuxData(void);
void module__init(void){
	mDataAcqPump	=	s__mDataAcqPump;
	memcpy((void*)mDigitalTvChannelsFoundInLnb,(void*)s__mDigitalTvChannelsFoundInLnb,sizeof(mDigitalTvChannelsFoundInLnb));
	memcpy((void*)mDigitalRadioChannelsFoundInLnb,(void*)s__mDigitalRadioChannelsFoundInLnb,sizeof(mDigitalRadioChannelsFoundInLnb));
	mDigitalTranspondersFound	=	s__mDigitalTranspondersFound;
	mCurrentLnb	=	s__mCurrentLnb;
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
	mDigitalTVChannelsRemoved	=	s__mDigitalTVChannelsRemoved;
	mDigitalRadioChannelsRemoved	=	s__mDigitalRadioChannelsRemoved;
	DataAcqInstance	=	s__DataAcqInstance;
	mLCNData	=	s__mLCNData;
	BarkerMuxData	=	s__BarkerMuxData;
	memcpy((void*)mUnicodeBuffer,(void*)s__mUnicodeBuffer,sizeof(mUnicodeBuffer));
	memcpy((void*)mHsvDVBPIDList,(void*)s__mHsvDVBPIDList,sizeof(mHsvDVBPIDList));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef ADDSAT_MODE
#undef ADDSAT_MODE
#endif //ADDSAT_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef AUTOUPDATE_MODE
#undef AUTOUPDATE_MODE
#endif //AUTOUPDATE_MODE
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
#ifdef IS_NOT_USER_INSTALLED(tsdata)
#undef IS_NOT_USER_INSTALLED(tsdata)
#endif //IS_NOT_USER_INSTALLED(tsdata)
#ifdef INVALID_LCN
#undef INVALID_LCN
#endif //INVALID_LCN
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
#ifdef ASSIGN_KEYS_OF_SVC(svcdat1,
#undef ASSIGN_KEYS_OF_SVC(svcdat1,
#endif //ASSIGN_KEYS_OF_SVC(svcdat1,
#ifdef MAX_LNBS_SUPPORTED
#undef MAX_LNBS_SUPPORTED
#endif //MAX_LNBS_SUPPORTED
#ifdef MAX_LCN_NUMBERS
#undef MAX_LCN_NUMBERS
#endif //MAX_LCN_NUMBERS
#ifdef GET_LCN
#undef GET_LCN
#endif //GET_LCN
#ifdef ACQUIRE_LCNS
#undef ACQUIRE_LCNS
#endif //ACQUIRE_LCNS
#ifdef VALID_LCN_RANGE(LCN)
#undef VALID_LCN_RANGE(LCN)
#endif //VALID_LCN_RANGE(LCN)
#ifdef MAX_SERVICES_IN_SINGLE_STEP
#undef MAX_SERVICES_IN_SINGLE_STEP
#endif //MAX_SERVICES_IN_SINGLE_STEP
#ifdef MAX_NUM_SDSD
#undef MAX_NUM_SDSD
#endif //MAX_NUM_SDSD
#ifdef FREQ_DRIFT_TOLERANCE
#undef FREQ_DRIFT_TOLERANCE
#endif //FREQ_DRIFT_TOLERANCE
#ifdef BARKER_MUX_LINKAGE_TYPE
#undef BARKER_MUX_LINKAGE_TYPE
#endif //BARKER_MUX_LINKAGE_TYPE
#endif //LOCAL_UNDEFINES
