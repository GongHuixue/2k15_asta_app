#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define NO_DATA                     (0x0)

#define SDT                         (0x1)

#define NIT                         (0x2)

#define EvDataAvaiable              (0x256)

#define BACKGROUND_MODE             (rins_InstallationModeBackground) 

#define CURRENT_MODE                (rins_GetInstallationMode()) 

#define BACKGROUND_INSTALL          (CURRENT_MODE == BACKGROUND_MODE)

#define INVALID_NIT_VERSION			(-1)

#define MIN_VALID_LCN    						(1)

#define	MAX_VALID_LCN    						(999)
#define	VALID_LCN_RANGE(x)  					(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))
#define	PTC_TABLE             		(pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define	PRESET_TABLE           		(pgdb_GetCurrentTable() | pgdbconst_Preset)
#define	SERVICE_TABLE				(pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define	GETSERVICETYPE(servicetype)				( (servicetype == AppApiRadioService)? HsvRadio: HsvOnePart )


#define REVALIDATE(x)                   ((x) &= 0x7FFF)  

/* static variables */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mPump;
static Pump s__mPump;
Bool mActive,mAcquistionInProgress,mPresetChanged,mLowestPreset;
static Bool s__mActive,s__mAcquistionInProgress,s__mPresetChanged,s__mLowestPreset;
static Nat16 s__OnIdCached,s__SrvIdCached,s__TsIdCached,s_PresetNumberCached;
static Nat32 s__FrequencyCached, s__StreamPriorityCached;
int mCurrentSessionCookie;
static int s__mCurrentSessionCookie;
void PumpHandler(int event, Nat32 param);
inline void FuncDataAvailable(void);
Bool mIsSdtVersionUpdate(void);
Bool mIsNitVersionUpdate(void);
Nat16 OnId,SrvId,TsId;
Nat16 OnIdCached,SrvIdCached,TsIdCached,PresetNumberCached;
Nat8 mGetVersion(int TableData);
Nat32 FrequencyCached, StreamPriorityCached;
void mUpdateLCN();
Bool mCachedServiceDetail();
void mTunedLowestPreset();
Bool mCheckVisibleService(HsvPgdatPresetData* preset);
Bool UpdateServiceNames(HsvPgdatDigTSData *tsdata);
Bool UpdateChannelName(int *pPreset);
Bool mIsMenuLanguageChanged(HsvPgdatDigTSData *tsdata, int *preset);
Bool GetSvcNameWithCurrentLanguage(HsvPgdatDigServiceData *psvcdat, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
void mCopyString(Nat16 *dest, Nat16 *src, int maxchars);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);

void module__init(void){
	mPump	=	s__mPump;
	mActive	=	s__mActive;
	OnIdCached = s__OnIdCached;
	SrvIdCached = s__SrvIdCached;
	TsIdCached = s__TsIdCached;
	PresetNumberCached=s_PresetNumberCached;
	mAcquistionInProgress	=	s__mAcquistionInProgress;
	mCurrentSessionCookie   = 	s__mCurrentSessionCookie;
	FrequencyCached = s__FrequencyCached;
	StreamPriorityCached = s__StreamPriorityCached;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef NO_DATA
#undef NO_DATA
#endif //NO_DATA
#ifdef SDT
#undef SDT
#endif //SDT
#ifdef NIT
#undef NIT
#endif //NIT
#ifdef EvDataAvaiable
#undef EvDataAvaiable
#endif //EvDataAvaiable
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#endif //LOCAL_UNDEFINES
