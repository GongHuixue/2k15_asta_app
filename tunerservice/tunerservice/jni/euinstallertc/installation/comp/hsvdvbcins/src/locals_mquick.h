#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define INVALID_NETWORKID   (0xFFFF)

#define KDG_NETWORK(NetworkId)                      ((NetworkId >= 0xF001) && (NetworkId <= 0xF01F))

#define KABLEBW_NETWORK(NetworkId)                  (NetworkId == 0xA018) 
/* pavan: should be a different div */

#define VALID_NTKID(ntkid)  (((ntkid) >= (0xFF01))? (FALSE) : (TRUE))

#define TV_SERVICE                       (0x01)

#define NIT_TYPE_INVALID    0

#define NIT_ACTUAL_REQD     (eurdiv_GetNitPriority(rins_Cable) & eurdiv_NitActual)

#define NIT_OTHER_REQD      (eurdiv_GetNitPriority(rins_Cable) & eurdiv_NitOther)

/* pavan: convert this to div */

#define NIT_PREFERRED       (NIT_ACTUAL_REQD ? eurdiv_NitActual : eurdiv_NitOther)

#define MAX_CHARACTERS		(128)

#define CABLE_FREQ          (pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)

#define PRE_SCAN_SUPPORTED  (eurdiv_IsPreScanSupported(rins_Cable))

#define CURRENT_SYM_RATE    (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CableDescParam[mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex].SymbolRate)

#define CURRENT_FREQ        (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CableDescParam[mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex].Frequency)

#define CURRENT_MODULATION  (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CableDescParam[mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex].Modulation)

#define ALT_SYM_RATE    (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].AltTsParam[mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentAltTsIndex].SymbolRate)

#define ALT_FREQ        (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].AltTsParam[mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentAltTsIndex].Frequency)

#define ALT_MODULATION  (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].AltTsParam[mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentAltTsIndex].Modulation)

#define INVALID_HSVSPID     (-1)

#define INVALID_VERSION     (-1)

#define MAX_CHARACTERS				     (128)

#define MAX_SEARCH_RATES    (25)

#define SDT_OTHER_TABLE_ID                (0x46)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define PLF_TUNING_DVBC_QAM16           (1)
#define PLF_TUNING_DVBC_QAM32           (2)
#define PLF_TUNING_DVBC_QAM64           (3)
#define PLF_TUNING_DVBC_QAM128          (4)
#define PLF_TUNING_DVBC_QAM256          (5)


/*************************************************************************
  Local Structures and enums
 **************************************************************************/

typedef enum
{
    StIdle = 0,
    StInit,
    StFeWait,
    StNITWait,
    StDmxWait,
    StDecision,
    StMax
}States;
typedef enum
{
    EvStart = 0,
    EvStationFound,
    EvStationNotFound,
    EvNitFound,
    EvNitNotFound,
    EvDmxNtf,
    EvMakeDecision,
    EvStop,
    EvSdmStopped,
    EvMax
}Events;
typedef enum
{
    DvbcQuickIdle,
    DvbcQuickScanningDefaultList,
    DvbcQuickScanningNetworkFreq,
    DvbcQuickScanningCDS,
    DvbcQuickScanningAlt
}t_DVBCQuickScanStates;
typedef struct
{
    States State;
    Nat32 Frequency;
    Nat8 ModulationType;
    /* not used but to remain consistent with data structure */
    Nat8 CodeRateHigh;
    Nat8 CodeRateLow;
    Nat8 ChannelBandwidth;
    Nat8 GuardInterval;
    Nat8 FrequencyOffset;
    Nat8 TxMode;
    Nat8 IqMode;
    Nat16 ChannelInformation;
    Int32 TimeError;
    Int32 FrequencyError;
    /* till here */
    Nat32 SymbolRate;
    HsvDemux CurrentDemux;
    Bool  SDTAcquired;

    Bool  TargeNITFound;
    Nat8  TargetNITType;
    Nat8  TargetNITVersion;
    Nat32 TargetNITFreq;
    Nat16 TargetNITValue;
    Nat32 TargetNITSymRate;

    int   PreferredNit;
    int   NitMode;

    Bool  PlayStarted;
    Bool  StationFound;
    tmFe_SearchSymbolRate_t SearchRates[MAX_SEARCH_RATES];
    int SearchRateLen;
    int NumChannelsAdded;
    int NumChannelsRemoved;
    int FirstPresetNumber;
    Bool Active;
    Nat32 StartFrequency;
    Nat32 EndFrequency;
    Nat8 FrequencyMode;
    t_DVBCQuickScanStates   ScanState;
}t_DVBCQuickStatus;
typedef void (CLASSSCOPE *FunctionNat32)(int);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

Pump mQuickPump;
static Pump s__mQuickPump;
t_DVBCQuickStatus mDvbcQuickStatus;
static t_DVBCQuickStatus s__mDvbcQuickStatus;
t_CableDSDesc mCableDSDesc;
static t_CableDSDesc s__mCableDSDesc;
t_CableDSDesc mFlashCableDS;
static t_CableDSDesc s__mFlashCableDS;
char mDirName[MAX_CHARACTERS];
static char s__mDirName[MAX_CHARACTERS];
char mFileName[MAX_CHARACTERS];
static char s__mFileName[MAX_CHARACTERS];
int mConstellation[14];
static int s__mConstellation[14];
static const FunctionNat32 StateEventMatrix[][StMax];
void PumpHandler(int event, Nat32 param );
void FuncSdmStopped(int param);
void FuncStartInstall(int param);
void FuncStationFound(int param);
void FuncStationNotFound(int param);
void FuncNITFound(int param);
void FuncNITNotFound(int param);
void FuncDmxData(int param);
void FuncMakeDecision(int param);
void FuncStop(int param);
void mUpdateTunerStatus();
Bool mGetNextcableDS(void);
Bool mGetNextAltTs();
void mOnNitAvailable();
void mGetPathName(char* dirName, char* FileName , char* PathName);
void mWriteCableDSToFlash();
void mInvalidateFlash();
Bool mLoadCDSDFromStrapi(int hsvspid, int hsvaltspid);
void mResetInstallationState(void);
void mStopSdm(HsvDemux dmx);
int FindHsvValue(int plfval, int* arr, int len);
int mMapFromHsvToPlfDvbcModulation(int type);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mQuickPump	=	s__mQuickPump;
	mDvbcQuickStatus	=	s__mDvbcQuickStatus;
	mCableDSDesc	=	s__mCableDSDesc;
	mFlashCableDS	=	s__mFlashCableDS;
	memcpy((void*)mDirName,(void*)s__mDirName,sizeof(mDirName));
	memcpy((void*)mFileName,(void*)s__mFileName,sizeof(mFileName));
	memcpy((void*)mConstellation,(void*)s__mConstellation,sizeof(mConstellation));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INVALID_NETWORKID
#undef INVALID_NETWORKID
#endif //INVALID_NETWORKID
#ifdef KDG_NETWORK(NetworkId)
#undef KDG_NETWORK(NetworkId)
#endif //KDG_NETWORK(NetworkId)
#ifdef KABLEBW_NETWORK(NetworkId)
#undef KABLEBW_NETWORK(NetworkId)
#endif //KABLEBW_NETWORK(NetworkId)
#ifdef VALID_NTKID(ntkid)
#undef VALID_NTKID(ntkid)
#endif //VALID_NTKID(ntkid)
#ifdef TV_SERVICE
#undef TV_SERVICE
#endif //TV_SERVICE
#ifdef NIT_TYPE_INVALID
#undef NIT_TYPE_INVALID
#endif //NIT_TYPE_INVALID
#ifdef NIT_ACTUAL_REQD
#undef NIT_ACTUAL_REQD
#endif //NIT_ACTUAL_REQD
#ifdef NIT_OTHER_REQD
#undef NIT_OTHER_REQD
#endif //NIT_OTHER_REQD
#ifdef NIT_PREFERRED
#undef NIT_PREFERRED
#endif //NIT_PREFERRED
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef CABLE_FREQ
#undef CABLE_FREQ
#endif //CABLE_FREQ
#ifdef PRE_SCAN_SUPPORTED
#undef PRE_SCAN_SUPPORTED
#endif //PRE_SCAN_SUPPORTED
#ifdef CURRENT_SYM_RATE
#undef CURRENT_SYM_RATE
#endif //CURRENT_SYM_RATE
#ifdef CURRENT_FREQ
#undef CURRENT_FREQ
#endif //CURRENT_FREQ
#ifdef CURRENT_MODULATION
#undef CURRENT_MODULATION
#endif //CURRENT_MODULATION
#ifdef ALT_SYM_RATE
#undef ALT_SYM_RATE
#endif //ALT_SYM_RATE
#ifdef ALT_FREQ
#undef ALT_FREQ
#endif //ALT_FREQ
#ifdef ALT_MODULATION
#undef ALT_MODULATION
#endif //ALT_MODULATION
#ifdef INVALID_HSVSPID
#undef INVALID_HSVSPID
#endif //INVALID_HSVSPID
#ifdef INVALID_VERSION
#undef INVALID_VERSION
#endif //INVALID_VERSION
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef MAX_SEARCH_RATES
#undef MAX_SEARCH_RATES
#endif //MAX_SEARCH_RATES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#endif //LOCAL_UNDEFINES
