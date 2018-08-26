#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include	<stdio.h>

#include	<stdlib.h>

#include	<string.h>

#define		AUTO_MODE								(insstate_InstallationServiceScan)

#define		ADDSAT_MODE								(insstate_InstallationAddSatellite)

#define		UPDATE_MODE								(insstate_InstallationUpdate)

#define		AUTOUPDATE_MODE							(insstate_InstallationAutomaticUpdate)

#define     BACKGROUND_MODE                         (insstate_InstallationBackground)
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

#define		TEMP_SAT_INFO_TABLE						(pgdbconst_Satellite | pgdbconst_CurrentSatInfo)

#define		TEMP_PTC_TABLE							(pgdbconst_Satellite | pgdbconst_CurrentDigitalTS)

#define		TEMP_SERVICE_TABLE						(pgdbconst_Satellite | pgdbconst_CurrentDigitalService)

#define     ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	 { \
														svcdat1.Tpid	= svcdat2.Tpid; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
													 }

#define		MAX_LNBS_SUPPORTED						(4)

#define 		MAX_NUM_LCN_ENTRY							(8)

#define 	MAX_SDSD					(200)


typedef struct
{
    Nat16 Onid;
    Nat16 Tsid;
    Nat16 NetworkId;
    int   TsVersionNum;
    Nat8  SDTVersion;
} HsvDataAcqInstance;
typedef enum
{
	StartDataAcq,
	StartDataAcqOnTimeout,
	StartBackgroundDataAcq,
	StartSDSDDataAcq,
	StartSyncRecordsForPreDefinedList
} HsvDataAcqEvents;
typedef enum
{
    Onid = 0,
    Tsid,
    VerNo,
    SpidService,
    MAX_PROPERTY_ID
}eDVBProperties;

typedef struct
{
	Nat8 NumOfSDSD;
	int CurrentSDSDIndex;
	HsvNITSatelliteDS SatDesc[MAX_SDSD];
}SatDSDesc;


#if 0

#endif

/*
static void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp)
{
	tsdata->Frequency            =   tsdata_temp.Frequency;
    tsdata->ModulationType       =   tsdata_temp.ModulationType;               
    //tsdata->HierarchyMode        =   tsdata_temp.HierarchyMode;
    tsdata->IqMode               =   tsdata_temp.IqMode;
    tsdata->Bandwidth     		=   tsdata_temp.ChannelBandwidth;
    //tsdata->StreamPriority       =   tsdata_temp.StreamPriority;
    //tsdata->QSignalStrength      =   tsdata_temp.QSignalStrength;
	//tsdata->SSignalStrength      =   tsdata_temp.SSignalStrength;
    //tsdata->ChannelInformation   =   tsdata_temp.ChannelInformation; 

    tsdata->SymbolRate           =   tsdata_temp.SymbolRate; 
    tsdata->OriginalNetworkId    =   tsdata_temp.OriginalNetworkId;
    tsdata->Tsid                 =   tsdata_temp.Tsid;
    tsdata->NetworkId            =   tsdata_temp.NetworkId;
	tsdata->TSVersion            =   tsdata_temp.TSVersion;
	tsdata->PtcListVersion       =   tsdata_temp.PtcListVersion;
	tsdata->CodeRate             =   tsdata_temp.CodeRate;
	
	tsdata->UserInstalled		 =	 tsdata_temp.UserInstalled;
}
*/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mDigitalTvChannelsFoundInLnb[MAX_LNBS_SUPPORTED],mDigitalRadioChannelsFoundInLnb[MAX_LNBS_SUPPORTED];
static int s__mDigitalTvChannelsFoundInLnb[MAX_LNBS_SUPPORTED],s__mDigitalRadioChannelsFoundInLnb[MAX_LNBS_SUPPORTED];
int mDigitalTranspondersFound;
static int s__mDigitalTranspondersFound;
int mCurrentLnb,mDigitalChannelsFound,mDigitalUserDefinedChannelsFound;
static int s__mCurrentLnb,s__mDigitalChannelsFound,s__mDigitalUserDefinedChannelsFound;
Pump mDataAcqPump;
static Pump s__mDataAcqPump;
int removeCurTv,removeCurRadio;
static int s__removeCurTv,s__removeCurRadio;
HsvDataAcqInstance DataAcqInstance;
static HsvDataAcqInstance s__DataAcqInstance;
Nat16 NumTvServicesInMux,NumRadioServicesInMux,NumTvServicesremoved,NumRadioServicesRemoved;
static Nat16 s__NumTvServicesInMux,s__NumRadioServicesInMux,s__NumTvServicesremoved,s__NumRadioServicesRemoved;
Nat16 mUnicodeBuffer[11];
static Nat16 s__mUnicodeBuffer[11];
int mHsvDVBPIDList[MAX_PROPERTY_ID][2];
static int s__mHsvDVBPIDList[MAX_PROPERTY_ID][2];
SatDSDesc mSatDSDesc;
static SatDSDesc s__mSatDSDesc;
void mPumpHandler(int value, Nat32 param);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
Bool UpdateServiceTable (Nat32 TpId);
Bool mCheckAndUpdateSdtVersion (Nat32 *TpId);
Bool mUpdateBackgroundService (void);
int mConvertToPgdatServiceType(int servicetype);
Bool IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat);
Bool IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat);
Bool IsUserDefinedService (HsvPgdatDigServiceData *psvcdat);
Bool mGetTSMetaData(void);
void FillDummySdtData (HSVSPTYPE(ActualTSService, dvb, sdt) *service);
Bool mInstallMuxOnPat (HsvInstallationPTC *ptc, int TotalServices);
Bool mInstallMuxOnTimeout(HsvInstallationPTC *ptc);
Bool mInstallMux(HsvInstallationPTC *ptc);
void mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc);
void DeleteCurrentChannelEntry (HsvInstallationPTC *ptc);
void mAddToTSTable(HsvInstallationPTC *ptc);
Bool mCheckServiceForInstall(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
void mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat);
void mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void UpdateServiceTypeFromPat (HsvPgdatDigServiceData *psvcdat);
void mCollectSdsds (void);
void GetUserPackageIndex(Nat32* PackageIndex, Bool* IsPackage);

Nat16 * mAsciiToUnicode(char *ascii_str,int length);
Bool mSyncRecordsForPreDefinedList(void);
/*--------------------------------------------------------------------------------------------------------------------------*/
void mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
#if 0

void mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp);
#endif

/*
static void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp)
{
	tsdata->Frequency            =   tsdata_temp.Frequency;
    tsdata->ModulationType       =   tsdata_temp.ModulationType;               
    //tsdata->HierarchyMode        =   tsdata_temp.HierarchyMode;
    tsdata->IqMode               =   tsdata_temp.IqMode;
    tsdata->Bandwidth     		=   tsdata_temp.ChannelBandwidth;
    //tsdata->StreamPriority       =   tsdata_temp.StreamPriority;
    //tsdata->QSignalStrength      =   tsdata_temp.QSignalStrength;
	//tsdata->SSignalStrength      =   tsdata_temp.SSignalStrength;
    //tsdata->ChannelInformation   =   tsdata_temp.ChannelInformation; 

    tsdata->SymbolRate           =   tsdata_temp.SymbolRate; 
    tsdata->OriginalNetworkId    =   tsdata_temp.OriginalNetworkId;
    tsdata->Tsid                 =   tsdata_temp.Tsid;
    tsdata->NetworkId            =   tsdata_temp.NetworkId;
	tsdata->TSVersion            =   tsdata_temp.TSVersion;
	tsdata->PtcListVersion       =   tsdata_temp.PtcListVersion;
	tsdata->CodeRate             =   tsdata_temp.CodeRate;
	
	tsdata->UserInstalled		 =	 tsdata_temp.UserInstalled;
}
*/

void mCopyString(Nat16* dest, Nat16* src, int maxchars);
void mDetermineSatelliteDetails (HsvPgdatDigSatInfoData *SatInfo);
void mDetermineDuplicateSatelliteName (HsvPgdatDigSatInfoData *SatInfo);
Bool mUpdateSatelliteDetails (HsvPgdatDigSatInfoData *SatInfo);
void mAddSatInfo (HsvInstallationPTC	*ptc);
void mGetPTCInfo(HsvInstallationPTC *ptc);
Bool mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service);
Bool IsManualInstall(void);
Bool IsUpdateInstall(void);
Bool IsServiceScanInstall (void);
void mCheckAndAdjustDuplicateEntry (HsvInstallationPTC *Ptc);
void mAcquireData(void);
Bool mIsPredefinedListPackage (void);
void mAcquireDataOnTimeout(void);
Bool mIsLCNAcquistionSupported(void);

void module__init(void){
	memcpy((void*)mDigitalTvChannelsFoundInLnb,(void*)s__mDigitalTvChannelsFoundInLnb,sizeof(mDigitalTvChannelsFoundInLnb));
	memcpy((void*)mDigitalRadioChannelsFoundInLnb,(void*)s__mDigitalRadioChannelsFoundInLnb,sizeof(mDigitalRadioChannelsFoundInLnb));
	mDigitalTranspondersFound	=	s__mDigitalTranspondersFound;
	mCurrentLnb	=	s__mCurrentLnb;
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
	mDigitalUserDefinedChannelsFound	=	s__mDigitalUserDefinedChannelsFound;
	mDataAcqPump	=	s__mDataAcqPump;
	removeCurTv	=	s__removeCurTv;
	removeCurRadio	=	s__removeCurRadio;
	DataAcqInstance	=	s__DataAcqInstance;
	NumTvServicesInMux	=	s__NumTvServicesInMux;
	NumRadioServicesInMux	=	s__NumRadioServicesInMux;
	NumTvServicesremoved	=	s__NumTvServicesremoved;
	NumRadioServicesRemoved	=	s__NumRadioServicesRemoved;
	memcpy((void*)mUnicodeBuffer,(void*)s__mUnicodeBuffer,sizeof(mUnicodeBuffer));
	memcpy((void*)mHsvDVBPIDList,(void*)s__mHsvDVBPIDList,sizeof(mHsvDVBPIDList));
#if 0

#endif

/*
static void mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp)
{
	tsdata->Frequency            =   tsdata_temp.Frequency;
    tsdata->ModulationType       =   tsdata_temp.ModulationType;               
    //tsdata->HierarchyMode        =   tsdata_temp.HierarchyMode;
    tsdata->IqMode               =   tsdata_temp.IqMode;
    tsdata->Bandwidth     		=   tsdata_temp.ChannelBandwidth;
    //tsdata->StreamPriority       =   tsdata_temp.StreamPriority;
    //tsdata->QSignalStrength      =   tsdata_temp.QSignalStrength;
	//tsdata->SSignalStrength      =   tsdata_temp.SSignalStrength;
    //tsdata->ChannelInformation   =   tsdata_temp.ChannelInformation; 

    tsdata->SymbolRate           =   tsdata_temp.SymbolRate; 
    tsdata->OriginalNetworkId    =   tsdata_temp.OriginalNetworkId;
    tsdata->Tsid                 =   tsdata_temp.Tsid;
    tsdata->NetworkId            =   tsdata_temp.NetworkId;
	tsdata->TSVersion            =   tsdata_temp.TSVersion;
	tsdata->PtcListVersion       =   tsdata_temp.PtcListVersion;
	tsdata->CodeRate             =   tsdata_temp.CodeRate;
	
	tsdata->UserInstalled		 =	 tsdata_temp.UserInstalled;
}
*/

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
#ifdef TEMP_SAT_INFO_TABLE
#undef TEMP_SAT_INFO_TABLE
#endif //TEMP_SAT_INFO_TABLE
#ifdef TEMP_PTC_TABLE
#undef TEMP_PTC_TABLE
#endif //TEMP_PTC_TABLE
#ifdef TEMP_SERVICE_TABLE
#undef TEMP_SERVICE_TABLE
#endif //TEMP_SERVICE_TABLE
#ifdef ASSIGN_KEYS_OF_SVC(svcdat1,
#undef ASSIGN_KEYS_OF_SVC(svcdat1,
#endif //ASSIGN_KEYS_OF_SVC(svcdat1,
#ifdef MAX_LNBS_SUPPORTED
#undef MAX_LNBS_SUPPORTED
#endif //MAX_LNBS_SUPPORTED
#ifdef MAX_NUM_LCN_ENTRY
#undef MAX_NUM_LCN_ENTRY
#endif //MAX_NUM_LCN_ENTRY
#endif //LOCAL_UNDEFINES
