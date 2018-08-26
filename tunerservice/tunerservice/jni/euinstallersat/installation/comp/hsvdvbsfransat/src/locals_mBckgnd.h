#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define BACKGROUND_MODE                             (insstate_InstallationBackground)

#define BACKGROUND_INSTALL                          (IsBackgroundInstall())

#define CURRENT_TABLE                               (pgdb_GetCurrentTable())

#define SERVICE_TABLE                               (CURRENT_TABLE | pgdbconst_DigitalService)

#define	PRESET_TABLE                                (CURRENT_TABLE | pgdbconst_Preset)

#define VALID_VERSION(version)                      ((version >=0) && (version<=31))

#define MIN_VALID_LCN    						    (0)

#define	MAX_VALID_LCN    						    (2000)

#define	VALID_LCN_RANGE(x)  					    (((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))

typedef enum
{
    EvTriggerBckgndUpdateInstall,
    EvSDTAvailable,
    EvMax
} BackgroundEvents;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mPump;
static Pump s__mPump;
Bool mActive,mUpdatePending;
static Bool s__mActive,s__mUpdatePending;
Bool IsBackgroundInstall ();
void PumpHandler (int event, Nat32 param);
Bool mIsBATVersionChanged (void);
Bool mIsBackgroundUpdateInstallAllowed (void);
void mTriggerBckgndUpdateInstallation(void);
Bool UpdateServiceTable (HSVSPTYPE(ActualTSService, dvb, sdt) service);
void mCopyString(Nat16* dest, Nat16* src, int maxchars);
Bool mCompareUnicodeString(Nat16* dest, Nat16* src);
void module__init(void){
	mPump	=	s__mPump;
	mActive	=	s__mActive;
	mUpdatePending	=	s__mUpdatePending;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef VALID_VERSION(version)
#undef VALID_VERSION(version)
#endif //VALID_VERSION(version)
#ifdef MIN_VALID_LCN
#undef MIN_VALID_LCN
#endif //MIN_VALID_LCN
#ifdef MAX_VALID_LCN
#undef MAX_VALID_LCN
#endif //MAX_VALID_LCN
#ifdef VALID_LCN_RANGE(x)
#undef VALID_LCN_RANGE(x)
#endif //VALID_LCN_RANGE(x)
#endif //LOCAL_UNDEFINES
