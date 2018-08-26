
#include <string.h>

#define MODE_NONE       (rins_InstallationModeNone)
#define AUTO_MODE       (rins_InstallationModeAutomatic)
#define UPDATE_MODE     (rins_InstallationModeUpdate)
#define MANUAL_MODE     (rins_InstallationModeWeakSignal)
#define PRESCAN_MODE    (rins_InstallationModePreScan) 
#define CURRENT_MODE    (rins_GetInstallationMode()) 
#define ANALOG_MANUAL_MODE  (rins_InstallationModeManual) 
#define CAM_MODE    	(rins_InstallationModeCam)

#define AUTO_INSTALL    ((CURRENT_MODE) == (AUTO_MODE))
#define UPDATE_INSTALL  ((CURRENT_MODE) == (UPDATE_MODE))
#define MANUAL_INSTALL  ((CURRENT_MODE) == (MANUAL_MODE))
#define PRE_INSTALL     ((CURRENT_MODE) == (PRESCAN_MODE))
#define CAM_INSTALL     ((CURRENT_MODE) == (CAM_MODE))

#define SCAN_NONE       (eurdiv_ScanNone) 
#define SCAN_ANALOG     (eurdiv_ScanAnalog)
#define SCAN_DVBT       (eurdiv_ScanDVBT)
#define SCAN_DVBC       (eurdiv_ScanDVBC)
#define SCAN_DVBS       (eurdiv_ScanDVBS)
#define SCAN_MPEG_ONLY  (eurdiv_ScanDVBTMpegOnly)
#define CABLE           (rins_Cable)
#define ANTENNA         (rins_Terrestrial)
#define CABLE_MEDIUM    (InsStatus.Medium == rins_Cable)
#define ANTENNA_MEDIUM  (InsStatus.Medium == rins_Terrestrial)
#define DIGITAL_PASS    (((InsStatus.Pass) == SCAN_DVBT) || ((InsStatus.Pass) == SCAN_DVBC) || ((InsStatus.Pass) == SCAN_MPEG_ONLY))
#define IS_DIGITAL_PRESET(presetType)               ( presetType == HsvOnePart)
#define WINDOWID        (wnddest_GetWindowId(HsvMain))

#define MAIN_VIDEO_WINDOW_TYPE      0
#define MAIN_AUDIO_WINDOW_TYPE      1
#define MONITOR_WINDOW_TYPE         2
#define MAX_NO_OF_SOURCE_SETUPS     3

#define MAX_DATABASE_SYNC	    5
#define	PTC_TABLE                                (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define	SERVICE_TABLE                            (pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define	PRESET_TABLE                             (pgdb_GetCurrentTable() | pgdbconst_Preset)
#define	FREQMAP_TABLE                            (pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)
#define ANALOG_TABLE				 (pgdb_GetCurrentTable() | pgdbconst_AnalogTable)
#define GETUSECASE(pass)            ((pass == SCAN_ANALOG)? HsvAnalogue: HsvMpegTs)
#define TEMP_PTC_TABLE              (pgdb_GetCurrentTable() | pgdbconst_CurrentDigitalTS)
#define TEMP_SERVICE_TABLE          (pgdb_GetCurrentTable() | pgdbconst_CurrentDigitalService)
#define ANALOG_TABLE				(pgdb_GetCurrentTable() | pgdbconst_Analog)
#define VALID_SOURCE(src)           (src == HsvMainTuner)
#define SET_INS_STATE(state);        (InsStatus.State = state); \
												__android_log_print(ANDROID_LOG_DEBUG, "hsveuins_m"," setting ins state %d  ", state);

#define GET_INS_STATE               (InsStatus.State)
#define TURNED_ON                   (mModuleLifeCycle == TurnedOn)
#define DVBC_LIGHT_COUNTRY          (CABLE_MEDIUM && (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite))



static void FuncSearchInProgress(Nat32 param);
static void FuncSortComplete(Nat32 param);
static inline void FuncSorting(Nat32 param);
static inline void FuncPreSorting(Nat32 param);
static inline void  FuncStopInstallation(Nat32 param);
static inline void FuncSourceSetupApplied(Nat32 param);
static inline Bool mValidInstallMode(int mode);
static inline Bool mIsNextPassRequired(void);
static void mStartDigitalInstall(void);
static inline void mInstallationDone(void);
static int mWaitForUserSelection(void);
static int mCalculateInstallationPass(void);
static void mPumpHandler(int event, Nat32 param);
static inline void mInitInstallationValues(Nat32 param, Bool InstallStart);
static inline void mInitInstallationPass(Bool BlockDestionationFlag);
static  HsvConstellation ConvertFromPlatformConstellation(tmFe_Constellation_t inval);
