#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define WINDOWID        (wnddest_GetWindowId(HsvMain))

#define AUTO_MODE       (rins_InstallationModeAutomatic)

#define UPDATE_MODE     (rins_InstallationModeUpdate)

#define MANUAL_MODE     (rins_InstallationModeWeakSignal)

#define BACKGROUND_MODE (rins_InstallationModeBackground)

#define CURRENT_MODE    (rins_GetInstallationMode())

#define CURRENT_MEDIUM  (rins_GetMedium())

#define AUTO_INSTALL        ((CURRENT_MODE) == (AUTO_MODE))

#define UPDATE_INSTALL      ((CURRENT_MODE) == (UPDATE_MODE))

#define MANUAL_INSTALL      ((CURRENT_MODE) == (MANUAL_MODE))

#define BACKGROUND_INSTALL  ((CURRENT_MODE) == (BACKGROUND_MODE))

#define SIGSTR_WAITTIME     (1000)

#define PAT_TIMEOUT         (1000)

#define ANTENNA_PRESET  (pgdb_GetCurrentTable() | pgdbconst_Preset)

#define ANTENNA_SERVICE (pgdb_GetCurrentTable() | pgdbconst_DigitalService)

#define ANTENNA_PTC     (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)




#define MAX_BANDS                   (29)

#define ANTENNA_MEDIUM              (rins_GetMedium() == rins_Terrestrial)

#define GET_ABSOLUTE_VAL(x)         (((x)>0)?(x):-(x))

#define BAND_170_50_7MHz    { 2728,             2896,             tmFe_ChanBandwidth7MHz    }   /*  177.50 / 7  */

#define BAND_170_00_8MHz    { 2720,             2912,             tmFe_ChanBandwidth8MHz    }   /*  178.00 / 8  */

#define BAND_171_00_8MHz    { 2736,             2928,             tmFe_ChanBandwidth8MHz    }   /*  179.00/ 8  */

#define BAND_177_50_7MHz    { 2840,             3008,             tmFe_ChanBandwidth7MHz    }   /*  184.50 / 7  */

#define BAND_178_00_8MHz    { 2848,             3040,             tmFe_ChanBandwidth8MHz    }   /*  186.00 / 8  */

#define BAND_179_00_7MHz    { 2864,             3032,             tmFe_ChanBandwidth7MHz    }   /*  186.00 / 7  */

#define BAND_179_00_8MHz    { 2864,             3056,             tmFe_ChanBandwidth8MHz    }   /*  187.00 / 8  */

#define BAND_184_50_7MHz    { 2952,             3120,             tmFe_ChanBandwidth7MHz    }   /*  191.50 / 7  */

#define BAND_186_00_8MHz    { 2976,             3168,             tmFe_ChanBandwidth8MHz    }   /*  194.00 / 8  */

#define BAND_187_00_8MHz    { 2992,             3184,             tmFe_ChanBandwidth8MHz    }   /*  195.00 / 8  */

#define BAND_187_50_7MHz    { 3000,             3168,             tmFe_ChanBandwidth7MHz    }   /*  194.50 / 7  */

#define BAND_191_50_7MHz    { 3064,             3232,             tmFe_ChanBandwidth7MHz    }   /*  198.50 / 7  */

#define BAND_194_00_8MHz    { 3104,             3296,             tmFe_ChanBandwidth8MHz    }   /*  202.00 / 8  */

#define BAND_195_00_8MHz    { 3120,             3312,             tmFe_ChanBandwidth8MHz    }   /*  203.00 / 8  */

#define BAND_196_50_7MHz    { 3144,             3312,             tmFe_ChanBandwidth7MHz    }   /*  203.50 / 7  */

#define BAND_198_50_7MHz    { 3176,             3344,             tmFe_ChanBandwidth7MHz    }   /*  205.50 / 7  */

#define BAND_202_00_8MHz    { 3232,             3424,             tmFe_ChanBandwidth8MHz    }   /*  210.00 / 8  */

#define BAND_203_00_8MHz    { 3248,             3440,             tmFe_ChanBandwidth8MHz    }   /*  211.00 / 8  */

#define BAND_205_50_7MHz    { 3288,             3456,             tmFe_ChanBandwidth7MHz    }   /*  212.50 / 7  */

#define BAND_210_00_8MHz    { 3360,             3552,             tmFe_ChanBandwidth8MHz    }   /*  218.00 / 8  */

#define BAND_211_00_8MHz    { 3376,             3568,             tmFe_ChanBandwidth8MHz    }   /*  219.00 / 8  */

#define BAND_212_50_7MHz    { 3400,             3568,             tmFe_ChanBandwidth7MHz    }   /*  219.50 / 7  */

#define BAND_218_00_8MHz    { 3488,             3680,             tmFe_ChanBandwidth8MHz    }   /*  226.00 / 8  */

#define BAND_219_50_7MHz    { 3512,             3680,             tmFe_ChanBandwidth7MHz    }   /*  226.50 / 7  */

#define BAND_226_00_8MHz    { 3616,             4832,             tmFe_ChanBandwidth8MHz    }   /*  234.00 -- 298.00 / 8  */

#define BAND_226_50_7MHz    { 3624,             4800,             tmFe_ChanBandwidth7MHz    }   /*  233.50 -- 296.50 / 7  */

#define BAND_298            { 4768,             7520,             tmFe_ChanBandwidth8MHz    }   /*  306.00 -- 466.00 / 8  */

#define BAND_466            { 7456,             13792,            tmFe_ChanBandwidth8MHz    }

#define BAND_170_AUS        { 2728,             3680,             tmFe_ChanBandwidth7MHz    }

#define BAND_515_AUS        { 8248,             13120,            tmFe_ChanBandwidth7MHz    }

#define BAND_DVBCLIGHT_7MHZ { 1832,             13704,            tmFe_ChanBandwidth7MHz    }

#define BAND_DVBCLIGHT_8MHZ { 1824,             13728,            tmFe_ChanBandwidth8MHz    }

#define BAND_NULL           { INVALID_FREQUENCY,INVALID_FREQUENCY,tmFe_ChanBandwidth8MHz    }

/*
    All frequencies found must be between StartFrequency and EndFrequency.  Since there is a +/- 0.5Mhz
    variation allowed for these frequencies, we need to search up to 0.5Mhz below the lowest frequency
    in the band.  This is all taken care of by the feapi_startSearch call.  Since startSearch will
    never go below StartFrequency and will search consecutive channels (in the same band) in increments 
    of the bandwidth (8Mhz steps for 8Mhz bandwidth) we need to start a full channel below the lowest
    frequency we want to install.   Remember to also allow for another half of the bandwidth from the
    lower end of the band to the first center frequency and that frequencies are specified in 1/16th of
    a MHz.
    
    If we want to install channels in the band B->T (Bottom->Top) with bandwidth W, then:
        StartFrequency = B - W
        EndFrequency   = T
        Bandwidth      = W
        first channel center frequency:  StartFrequency + 1.5*W
        second channel center frequency: StartFrequency + 2.5*W
        etc...
        last channel center frequency  <= EndFrequency - 0.5*W
        
    This will ensure the top of the highest channel is lower than T and the bottom of the lowest 
    channel is higher than B.
 */

typedef struct
{
    int     StartFrequency;
    int     EndFrequency;
    tmFe_ChanBandwidth_t Bandwidth;
} HsvInstallationSpectrum;
#define	ANTENNASPECTRUM_ENTRIES		(56)

#define	CABLESPECTRUM_ENTRIES		(3)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

typedef enum
{
    StIdle = 0,
    StFeWait,
    StDmxWait,
    StDecision,
    StMax
}States;
typedef struct DigitalInstallationStatus
{
    States                              State;
    Nat8                                ModulationType;
    Nat8                                CodeRateHigh;
    Nat8                                CodeRateLow;
    Nat8                                HierarchyMode;
    Bool                                HierarchyModeDetected;
    Nat8                                GuardInterval;
    Nat8                                TxMode;
    Nat8                                IqMode;
    Nat8                                ChannelBandwidth;
    HsvStreamPriority                   StreamPriority;
    Nat16                               ChannelInformation;
    Int32                               TimeError;
    Int32                               FrequencyError;
    Nat8                                FrequencyOffset;
    HsvDemux                            CurrentDemux;
    Nat8                                FrequencyBand;
    Bool                                PlayStarted;
    Bool                                StationFound;
    Nat32                               Frequency;
    int                                 Country;
    Bool                                Active;
}TypeDigitalInstallationStatus;
#undef  DECLARECONVERTFUNC

#define DECLARECONVERTFUNC(PlfParameter) static  Hsv##PlfParameter ConvertFromPlatform##PlfParameter (tmFe_##PlfParameter##_t in);

    /*DECLARECONVERTFUNC(Constellation)
    DECLARECONVERTFUNC(CodeRate)
    DECLARECONVERTFUNC(HierarchyMode)
    DECLARECONVERTFUNC(GuardInterval)
    DECLARECONVERTFUNC(TxMode)
    DECLARECONVERTFUNC(ChanBandwidth)
    DECLARECONVERTFUNC(FrequencyOffset)*/

    /****************************************************************************
     * State machine
     ****************************************************************************/

typedef enum
{
    evStart,
    evStop,
    evMeasNtfSigStr,
    evPgDatAvailable,
    evStationFound,
    evStationNotFound,
    evMakeDecision,             
    evPATTimeOut,
	evOnMeasReady,
    evMax
}Events;
typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#ifndef __cplusplus

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
HsvInstallationSpectrum AntennaSpectrum[ANTENNASPECTRUM_ENTRIES][MAX_BANDS];
static HsvInstallationSpectrum s__AntennaSpectrum[ANTENNASPECTRUM_ENTRIES][MAX_BANDS];
HsvInstallationSpectrum CableSpectrum[CABLESPECTRUM_ENTRIES];
static HsvInstallationSpectrum s__CableSpectrum[CABLESPECTRUM_ENTRIES];
#ifndef __cplusplus

#else

#endif

Bool InstallationInitialised;
static Bool s__InstallationInitialised;
Bool InstallationTurnOn;
static Bool s__InstallationTurnOn;
Pump mDVBTMpegPump;
static Pump s__mDVBTMpegPump;
TypeDigitalInstallationStatus mDvbtMpegStatus;
static TypeDigitalInstallationStatus s__mDvbtMpegStatus;
Bool mPATReceived;
static Bool s__mPATReceived;
#undef  DECLARECONVERTFUNC

static const FunctionNat32 mDvbtMpegMatrix[evMax][StMax];
void UpdateDigitalTunerInstallationStatus(void);
void SetChannelDecoderAttributes(void);
void mDvbtMpegHandler(int event, Nat32 param2);
void FuncStartDigitalScan(Nat32 param);
void FuncStop(Nat32 param);
void FuncDmxData(Nat32 param);
void FuncStationFound(Nat32 param);
void FuncStationNotFound(Nat32 param);
void FuncMakeDecision(Nat32 param);
void FuncSigStrMeasured(Nat32 param);
void FuncOnMeasReady(Nat32  param);
void PlayService(int serviceid);
void ArmTimerForPAT(void);
void HandlePatTimeOut(Nat32 param);
#ifndef __cplusplus

#endif

HsvConstellation ConvertFromPlatformConstellation(tmFe_Constellation_t inval);
HsvCodeRate ConvertFromPlatformCodeRate(tmFe_CodeRate_t inval);
HsvHierarchyMode ConvertFromPlatformHierarchyMode(tmFe_HierarchyMode_t inval);
HsvGuardInterval ConvertFromPlatformGuardInterval(tmFe_GuardInterval_t inval);
HsvTxMode ConvertFromPlatformTxMode(tmFe_TxMode_t inval);
HsvChanBandwidth ConvertFromPlatformChanBandwidth(tmFe_ChanBandwidth_t inval);
HsvFrequencyOffset ConvertFromPlatformFrequencyOffset(tmFe_FrequencyOffset_t inval);
HsvStreamPriority ConvertFromPlatformStreamPriority(tmFe_StreamPriority_t inval);
void SetStreamPriority(HsvStreamPriority prio);
tmFe_StreamPriority_t ConvertToPlatformStreamPriority(HsvStreamPriority inval);
int mGetMaxFrequency(HsvInstallationSpectrum *Spectrum);
int mGetCorrectedFrequency(int Frequency, int Country);
int mConvertBandwidthToValue(tmFe_ChanBandwidth_t Bandwidth);
void module__init(void){
	memcpy((void*)AntennaSpectrum,(void*)s__AntennaSpectrum,sizeof(AntennaSpectrum));
	memcpy((void*)CableSpectrum,(void*)s__CableSpectrum,sizeof(CableSpectrum));
#ifndef __cplusplus

#else

#endif

	InstallationInitialised	=	s__InstallationInitialised;
	InstallationTurnOn	=	s__InstallationTurnOn;
	mDVBTMpegPump	=	s__mDVBTMpegPump;
	mDvbtMpegStatus	=	s__mDvbtMpegStatus;
	mPATReceived	=	s__mPATReceived;
#undef  DECLARECONVERTFUNC

#ifndef __cplusplus

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef BACKGROUND_MODE
#undef BACKGROUND_MODE
#endif //BACKGROUND_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef CURRENT_MEDIUM
#undef CURRENT_MEDIUM
#endif //CURRENT_MEDIUM
#ifdef AUTO_INSTALL
#undef AUTO_INSTALL
#endif //AUTO_INSTALL
#ifdef UPDATE_INSTALL
#undef UPDATE_INSTALL
#endif //UPDATE_INSTALL
#ifdef MANUAL_INSTALL
#undef MANUAL_INSTALL
#endif //MANUAL_INSTALL
#ifdef BACKGROUND_INSTALL
#undef BACKGROUND_INSTALL
#endif //BACKGROUND_INSTALL
#ifdef SIGSTR_WAITTIME
#undef SIGSTR_WAITTIME
#endif //SIGSTR_WAITTIME
#ifdef PAT_TIMEOUT
#undef PAT_TIMEOUT
#endif //PAT_TIMEOUT
#ifdef ANTENNA_PRESET
#undef ANTENNA_PRESET
#endif //ANTENNA_PRESET
#ifdef ANTENNA_SERVICE
#undef ANTENNA_SERVICE
#endif //ANTENNA_SERVICE
#ifdef MAX_BANDS
#undef MAX_BANDS
#endif //MAX_BANDS
#ifdef ANTENNA_MEDIUM
#undef ANTENNA_MEDIUM
#endif //ANTENNA_MEDIUM
#ifdef GET_ABSOLUTE_VAL(x)
#undef GET_ABSOLUTE_VAL(x)
#endif //GET_ABSOLUTE_VAL(x)
#ifdef BAND_170_50_7MHz
#undef BAND_170_50_7MHz
#endif //BAND_170_50_7MHz
#ifdef BAND_170_00_8MHz
#undef BAND_170_00_8MHz
#endif //BAND_170_00_8MHz
#ifdef BAND_171_00_8MHz
#undef BAND_171_00_8MHz
#endif //BAND_171_00_8MHz
#ifdef BAND_177_50_7MHz
#undef BAND_177_50_7MHz
#endif //BAND_177_50_7MHz
#ifdef BAND_178_00_8MHz
#undef BAND_178_00_8MHz
#endif //BAND_178_00_8MHz
#ifdef BAND_179_00_7MHz
#undef BAND_179_00_7MHz
#endif //BAND_179_00_7MHz
#ifdef BAND_179_00_8MHz
#undef BAND_179_00_8MHz
#endif //BAND_179_00_8MHz
#ifdef BAND_184_50_7MHz
#undef BAND_184_50_7MHz
#endif //BAND_184_50_7MHz
#ifdef BAND_186_00_8MHz
#undef BAND_186_00_8MHz
#endif //BAND_186_00_8MHz
#ifdef BAND_187_00_8MHz
#undef BAND_187_00_8MHz
#endif //BAND_187_00_8MHz
#ifdef BAND_187_50_7MHz
#undef BAND_187_50_7MHz
#endif //BAND_187_50_7MHz
#ifdef BAND_191_50_7MHz
#undef BAND_191_50_7MHz
#endif //BAND_191_50_7MHz
#ifdef BAND_194_00_8MHz
#undef BAND_194_00_8MHz
#endif //BAND_194_00_8MHz
#ifdef BAND_195_00_8MHz
#undef BAND_195_00_8MHz
#endif //BAND_195_00_8MHz
#ifdef BAND_196_50_7MHz
#undef BAND_196_50_7MHz
#endif //BAND_196_50_7MHz
#ifdef BAND_198_50_7MHz
#undef BAND_198_50_7MHz
#endif //BAND_198_50_7MHz
#ifdef BAND_202_00_8MHz
#undef BAND_202_00_8MHz
#endif //BAND_202_00_8MHz
#ifdef BAND_203_00_8MHz
#undef BAND_203_00_8MHz
#endif //BAND_203_00_8MHz
#ifdef BAND_205_50_7MHz
#undef BAND_205_50_7MHz
#endif //BAND_205_50_7MHz
#ifdef BAND_210_00_8MHz
#undef BAND_210_00_8MHz
#endif //BAND_210_00_8MHz
#ifdef BAND_211_00_8MHz
#undef BAND_211_00_8MHz
#endif //BAND_211_00_8MHz
#ifdef BAND_212_50_7MHz
#undef BAND_212_50_7MHz
#endif //BAND_212_50_7MHz
#ifdef BAND_218_00_8MHz
#undef BAND_218_00_8MHz
#endif //BAND_218_00_8MHz
#ifdef BAND_219_50_7MHz
#undef BAND_219_50_7MHz
#endif //BAND_219_50_7MHz
#ifdef BAND_226_00_8MHz
#undef BAND_226_00_8MHz
#endif //BAND_226_00_8MHz
#ifdef BAND_226_50_7MHz
#undef BAND_226_50_7MHz
#endif //BAND_226_50_7MHz
#ifdef BAND_298
#undef BAND_298
#endif //BAND_298
#ifdef BAND_466
#undef BAND_466
#endif //BAND_466
#ifdef BAND_170_AUS
#undef BAND_170_AUS
#endif //BAND_170_AUS
#ifdef BAND_515_AUS
#undef BAND_515_AUS
#endif //BAND_515_AUS
#ifdef BAND_DVBCLIGHT_7MHZ
#undef BAND_DVBCLIGHT_7MHZ
#endif //BAND_DVBCLIGHT_7MHZ
#ifdef BAND_DVBCLIGHT_8MHZ
#undef BAND_DVBCLIGHT_8MHZ
#endif //BAND_DVBCLIGHT_8MHZ
#ifdef BAND_NULL
#undef BAND_NULL
#endif //BAND_NULL
#ifdef ANTENNASPECTRUM_ENTRIES
#undef ANTENNASPECTRUM_ENTRIES
#endif //ANTENNASPECTRUM_ENTRIES
#ifdef CABLESPECTRUM_ENTRIES
#undef CABLESPECTRUM_ENTRIES
#endif //CABLESPECTRUM_ENTRIES
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
#ifdef DECLARECONVERTFUNC(PlfParameter)
#undef DECLARECONVERTFUNC(PlfParameter)
#endif //DECLARECONVERTFUNC(PlfParameter)
#endif //LOCAL_UNDEFINES
