#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include	<stdio.h>

#include	<stdlib.h>

#include	<string.h>

#define	AUTO_MODE					(insstate_InstallationServiceScan)

#define	UPDATE_MODE					(insstate_InstallationUpdate)

#define	GETSERVICETYPE(servicetype)				( (servicetype == AppApiRadioService)? HsvRadio: HsvOnePart )

#define	GETHSVSPID(prop)				(mHsvDVBPIDList[prop])

#define		IS_VALID_ONID							( (DataAcqInstance.Onid >= 0xFF00)? FALSE: TRUE )		

#define		IS_VALID_NID							( (DataAcqInstance.NetworkId >= 0xFF01)? FALSE: TRUE )

#define		IS_VALID_TSID							( TRUE ) /* Not using yet in field.. might come soon */

#define		IS_VALID_TS								( IS_VALID_ONID && IS_VALID_NID && IS_VALID_TSID )

#define		INVALID_LCN								(0xC000)

#define		INVALID_PRESET							(0XFFFF)

#define		SAT_INFO_TABLE							(pgdbconst_Satellite | pgdbconst_SatInfo)

#define		PTC_TABLE							    (pgdbconst_Satellite | pgdbconst_DigitalTS)

#define		SERVICE_TABLE							(pgdbconst_Satellite | pgdbconst_DigitalService)

#define		PRESET_TABLE							(pgdbconst_Satellite | pgdbconst_Preset)

#define     ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	 { \
														svcdat1.Tpid	= svcdat2.Tpid; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
													 }

#define		PRESET_ALLOCATED(PresetNo)				(PresetNo != INVALID_PRESET)

#define		DVBS_INVALID_FREECA_MODE				(-1)

#define MIN_VALID_LCN    (1)

#define MAX_VALID_LCN    (4000)

#define	MAX_LNBS_SUPPORTED						(4)

#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)				(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
																									((OrgFreq/1000) * 1000))

#define	IS_VALID_ROLLOFF(x)		(x<(sizeof(RollOffTable)/sizeof(RollOffTable[0])))

#define VALID_LCN_RANGE(x)  	(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))

#define IS_RADIO_SERVICE(x)     ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )

#define REVALIDATE(x)     		((x) &= 0x7FFF)  

typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
    Nat16 NetworkId;
    Nat16 NumSdsds;	
    Nat16 CurSdsd;
    Nat8	LnbNumber;
} HsvDataAqcInstance;
typedef enum
{
	EvStartAcquire = 0,
	EvAcquireTSInfo,
	EvCompleteAcquire
}AcqEvents;
typedef enum
{
    Sdsd = 0,
    SLD,
    LCD,
    SpidService,
    MAX_PROPERTY_ID
}eDVBProperties;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mDigitalChannelsFound,mDigitalTvChannelsFound,mDigitalRadioChannelsFound;
static int s__mDigitalChannelsFound,s__mDigitalTvChannelsFound,s__mDigitalRadioChannelsFound;
Nat16 NumTvServicesInMux,NumRadioServicesInMux,NumTvServicesremoved,NumRadioServicesRemoved;
static Nat16 s__NumTvServicesInMux,s__NumRadioServicesInMux,s__NumTvServicesremoved,s__NumRadioServicesRemoved;
Pump mDataAcqPump;
static Pump s__mDataAcqPump;
int removeCurTv,removeCurRadio;
static int s__removeCurTv,s__removeCurRadio;
HsvDataAqcInstance DataAcqInstance;
static HsvDataAqcInstance s__DataAcqInstance;
HsvInstallationPTC CurrentPTC;
static HsvInstallationPTC s__CurrentPTC;
HsvPgdatDigSatInfoData SatDetails[MAX_LNBS_SUPPORTED];
static HsvPgdatDigSatInfoData s__SatDetails[MAX_LNBS_SUPPORTED];
HsvLnbSettings	mLnbSettings;
static HsvLnbSettings	s__mLnbSettings;
double RollOffTable[4];
static double s__RollOffTable[4];
int mHsvDVBPIDList[MAX_PROPERTY_ID];
static int s__mHsvDVBPIDList[MAX_PROPERTY_ID];
char M7LockString[10];
static char s__M7LockString[10];

void mPumpHandler(int value, Nat32 param);
void mStartAcquisistion(int value);
void mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,fnt) Sdsd, HsvInstallationPTC *ptc);
void mAcquireTSInfo(void);
void mDeleteTSTable(HsvInstallationPTC *ptc);
void mDeleteMuxesFromCurrentFNT(void);
void mAddToTSTable(HsvInstallationPTC *ptc, Bool *KeyUpdated, int *TPIDOld);
Bool mInstallMux(HsvInstallationPTC *ptc, Bool IsKeyUpdate, int OldTPID);
void mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc);
void mDeleteAllServicesFromCarrier(int TPID);
void mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, fst)* service);
void mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat);
void mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, fst) *service, Bool IsDuplicatesvc);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, fst) *service);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
int CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner);
Bool mCheckTSForInstall(HSVSPTYPE(SatelliteDS,dvb,fnt) Sdsd);
void mGetSatelliteDetails(void);
int mConvertToPgdatServiceType(int servicetype);
Bool IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat);
Bool IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat);
void mCopyString(Nat16* dest, Nat16* src, int maxchars);
Bool mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, fst)* service);
void mCollectSdsds (void);
Bool IsManualInstall(void);
Bool IsUpdateInstall(void);
Bool mCheckChannelLock(Nat16* src);
void module__init(void){
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
	mDigitalTvChannelsFound	=	s__mDigitalTvChannelsFound;
	mDigitalRadioChannelsFound	=	s__mDigitalRadioChannelsFound;
	NumTvServicesInMux	=	s__NumTvServicesInMux;
	NumRadioServicesInMux	=	s__NumRadioServicesInMux;
	NumTvServicesremoved	=	s__NumTvServicesremoved;
	NumRadioServicesRemoved	=	s__NumRadioServicesRemoved;
	mDataAcqPump	=	s__mDataAcqPump;
	removeCurTv	=	s__removeCurTv;
	removeCurRadio	=	s__removeCurRadio;
	DataAcqInstance	=	s__DataAcqInstance;
	CurrentPTC	=	s__CurrentPTC;
	memcpy((void*)SatDetails,(void*)s__SatDetails,sizeof(SatDetails));
	memcpy((void*)RollOffTable,(void*)s__RollOffTable,sizeof(RollOffTable));
	memcpy((void*)mHsvDVBPIDList,(void*)s__mHsvDVBPIDList,sizeof(mHsvDVBPIDList));
	memcpy((void*)M7LockString,(void*)s__M7LockString,sizeof(M7LockString));
	memcpy((void*)&mLnbSettings,(void*)&s__mLnbSettings,sizeof(mLnbSettings));
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
#ifdef GETHSVSPID(prop)
#undef GETHSVSPID(prop)
#endif //GETHSVSPID(prop)
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
#ifdef PRESET_ALLOCATED(PresetNo)
#undef PRESET_ALLOCATED(PresetNo)
#endif //PRESET_ALLOCATED(PresetNo)
#ifdef DVBS_INVALID_FREECA_MODE
#undef DVBS_INVALID_FREECA_MODE
#endif //DVBS_INVALID_FREECA_MODE
#ifdef MIN_VALID_LCN
#undef MIN_VALID_LCN
#endif //MIN_VALID_LCN
#ifdef MAX_VALID_LCN
#undef MAX_VALID_LCN
#endif //MAX_VALID_LCN
#ifdef MAX_LNBS_SUPPORTED
#undef MAX_LNBS_SUPPORTED
#endif //MAX_LNBS_SUPPORTED
#ifdef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#undef ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#endif //ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)
#ifdef IS_VALID_ROLLOFF(x)
#undef IS_VALID_ROLLOFF(x)
#endif //IS_VALID_ROLLOFF(x)
#ifdef VALID_LCN_RANGE(x)
#undef VALID_LCN_RANGE(x)
#endif //VALID_LCN_RANGE(x)
#ifdef IS_RADIO_SERVICE(x)
#undef IS_RADIO_SERVICE(x)
#endif //IS_RADIO_SERVICE(x)
#ifdef REVALIDATE(x)
#undef REVALIDATE(x)
#endif //REVALIDATE(x)
#endif //LOCAL_UNDEFINES
