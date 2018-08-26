
#define WINDOWID					(wnddest_GetWindowId(HsvMain))

#define TURNED_ON					(mConstModuleLifeCycle == ConstTurnedOn)
#define MODE_NONE					(rins_InstallationModeNone)
#define AUTO_MODE					(rins_InstallationModeAutomatic)
#define UPDATE_MODE					(rins_InstallationModeUpdate)
#define MANUAL_MODE					(rins_InstallationModeWeakSignal)
#define BACKGROUND_MODE				(rins_InstallationModeBackground)
#define CURRENT_MODE				(rins_GetInstallationMode()) 
#define AUTO_INSTALL				((CURRENT_MODE) == (AUTO_MODE))
#define UPDATE_INSTALL				((CURRENT_MODE) == (UPDATE_MODE))
#define MANUAL_INSTALL				((CURRENT_MODE) == (MANUAL_MODE))
#define BACKGROUND_INSTALL			((CURRENT_MODE) == (BACKGROUND_MODE))
#define VALID_EVENT(event)			((event >= ConstEvStart) && (event < ConstEvMax))
#define VALID_STATE(state)			(/*(state >= ConstStIdle) && */(state < ConstStMax))
#define VALID_SOURCE(source)		(source == HsvMainTuner)
#define VALID_INSTALL_MODE(mode)	((mode == AUTO_MODE) || (mode == UPDATE_MODE) || (mode == MANUAL_MODE))
#define COUNTRY						(sysset_GetSystemCountry())
#define SET_INS_STATE(state)		(mInstStatus.State = state)
#define ANTENNA_MEDIUM				(rins_GetMedium() == rins_Terrestrial)
#define CABLE_MEDIUM				(rins_GetMedium() == rins_Cable)
#define NO_DATA						(0)
#define ACQUISITION_COMPLETED		(1)
#define SIGNALSTRENGTH_POLLTIME		(1000)	//every second
#define TV_SERVICE                  (0x01)


typedef enum
{
	ConstStIdle,
	ConstStScanProgress,
	ConstStTunerWait,
	ConstStDemuxWait,
	ConstStPMTWait,
	ConstStMax
}ConstInsStates;


typedef enum
{
	ConstEvStart,
	ConstEvStop,
	ConstEvSdmStopped,
	ConstEvDataAvailable,
    ConstEvStationFound,
    ConstEvStationNotFound,
	ConstEvMakeDecision,
	ConstEvMeasureSignalStr,
    ConstEvHierarchyModeDetected,
	ConstEvOnMeasReady,
	ConstEvPMTCollected,
	ConstEvMax
}ConstEvents;

typedef struct 
{
	ConstInsStates   State;
	int			SdmData;
	Nat32		Frequency;
	int			FrequencyBand;
	Bool		HierarchyMode;
	Bool		StationFound;
}InstStatus;
static InstStatus mInstStatus;

typedef enum
{
    ConstInitialised = 0,
    ConstTurnedOn,
    ConstTurnedOff
}ConstModuleLifeCycle;
static ConstModuleLifeCycle mConstModuleLifeCycle = ConstTurnedOff;

static Pump mPump;

static void PumpHandler(int event, Nat32 param);
static void mInitialise(Nat32 freq);
static void mStopSdm(HsvDemux dmx);
static void mSetChannelDecoderAttributes(void);
static void mSetTunerAttributes(void);
static void mSetHeirarchyMux(int HeirarchyValue);
static int  mWaitForData(void);
static inline Nat16 mGetChannelDecoder(void);

