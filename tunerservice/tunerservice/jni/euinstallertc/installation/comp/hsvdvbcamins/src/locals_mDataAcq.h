#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#define		VALID_CAM_LCN_RANGE(lcn)				((lcn >=0) && (lcn <=9999))

#define         AUTO_MODE       (rins_InstallationModeAutomatic)
#define 	      MAX_TEXT_LENGTH             255
#define		MAX_NUM_OF_SERVICES						(500)

#define		PTC_TABLE							    (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)

#define		SERVICE_TABLE							(pgdb_GetCurrentTable() | pgdbconst_DigitalService)

#define		PRESET_TABLE							(pgdb_GetCurrentTable() | pgdbconst_Preset)

#define		FREQMAP_TABLE							(pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)

#define 	BACKGROUND_CAM_MODE						(2)

#define		BACKGROUND_CAM_INSTALL					(icamhelper_GetCamInstallationMode() == BACKGROUND_CAM_MODE)

#define		GETSERVICETYPE(servicetype)				( (servicetype == AppApiRadioService)? HsvRadio: HsvOnePart )

#define     ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	{ \
														svcdat1.OriginalNetworkId	= svcdat2.OriginalNetworkId; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
														svcdat1.Frequency			= svcdat2.Frequency; \
														svcdat1.StreamPriority		= svcdat2.StreamPriority; \
													}

#if eurdiv_iPresent_CONSTANT
#define DEFAULT_CHAR_SET            (eurdiv_DefaultCharacterTable)
#else
#define DEFAULT_CHAR_SET            (0) //Latin Alphabet - ISO8859-1 
#endif

typedef struct
{
    Nat8 VersionNumber;
    Nat16 NumOfRecords;
    HsvCamNITService ServiceInfo[MAX_NUM_OF_SERVICES];
}t_CamServiceList;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
t_CamServiceList mCamServiceList;
static t_CamServiceList s__mCamServiceList;
Nat8 mCamNITVersion;
static Nat8 s__mCamNITVersion;
int mDigitalChannelsFound;
static int s__mDigitalChannelsFound;
Bool updateBarkerMuxDvbCamins;
static Bool s__updateBarkerMuxDvbCamins;
void mInstallMuxs(void);
void mAssignServiceMetaDataAttributes(HsvPgdatDigServiceData *svcdat, HsvCamNITService *Service);
Nat8 mGetDvbType(int DecoderType);
void mAddToTSTable(HsvInstallationPTC *ptc, Nat16 OriginalNetworkId, Nat16 TsId, Bool isBarker);
Bool mDuplicateEntry(HsvPgdatDigServiceData svcdat, int tableid);
void mCheckAndNotifyAttributeChange (HsvPgdatDigServiceData* newsvcdat, HsvPgdatDigServiceData* cursvcdat);
Bool mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc);
Bool mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc);
void mAssignServiceBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc);
void mAssignServiceNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat);
void mCopyString(Nat16* dest, Nat16* src, int maxchars);
Bool mOperatorProfileInstallRules(HsvPgdatDigServiceData *svcdat);
void mAddToFreqMapTable(HsvInstallationPTC ptc, Nat16 OriginalNetworkId, Nat16 TsId);
Bool mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat);
void mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
Nat8 mFindTableCode(Nat8* str);
void msetCharacterCode(Nat8 charCodeFromCam,Nat8  prestoredCharCode);
void module__init(void){
	mCamServiceList	=	s__mCamServiceList;
	mCamNITVersion	=	s__mCamNITVersion;
	mDigitalChannelsFound	=	s__mDigitalChannelsFound;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef VALID_CAM_LCN_RANGE(lcn)
#undef VALID_CAM_LCN_RANGE(lcn)
#endif //VALID_CAM_LCN_RANGE(lcn)
#ifdef MAX_NUM_OF_SERVICES
#undef MAX_NUM_OF_SERVICES
#endif //MAX_NUM_OF_SERVICES
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef MAX_TEXT_LENGTH
#undef MAX_TEXT_LENGTH
#endif //MAX_NUM_OF_SERVICES
#ifdef PTC_TABLE
#undef PTC_TABLE
#endif //PTC_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef FREQMAP_TABLE
#undef FREQMAP_TABLE
#endif //FREQMAP_TABLE
#ifdef BACKGROUND_CAM_MODE
#undef BACKGROUND_CAM_MODE
#endif //BACKGROUND_CAM_MODE
#ifdef BACKGROUND_CAM_INSTALL
#undef BACKGROUND_CAM_INSTALL
#endif //BACKGROUND_CAM_INSTALL
#ifdef GETSERVICETYPE(servicetype)
#undef GETSERVICETYPE(servicetype)
#endif //GETSERVICETYPE(servicetype)
#ifdef ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)
#undef ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)
#endif //ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)
#endif //LOCAL_UNDEFINES
