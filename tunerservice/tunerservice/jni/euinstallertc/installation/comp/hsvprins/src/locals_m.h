#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#ifndef mem_iPresent_CONSTANT
// TODO:#error The presence of "mem" must be statically known

#endif


#define FNADDR(f) (& CLASSSCOPE f)

#define ANALOG_TABLE     (pgdb_GetCurrentTable() | pgdbconst_Analog)

#define PRESET_TABLE     (pgdb_GetCurrentTable() | pgdbconst_Preset)        

#define SERVICE_TABLE    (pgdb_GetCurrentTable() | pgdbconst_DigitalService)

#define LEAST_COUNT_FOR_ACI_TIMEOUT (1000) /* 1 Sec */

#define TIME_OUT_TVSYSTEM           (50000)/* HACK: As requested by TVPlayer changing this value temporarily on FB3 build */

#define CHECK_SECAML_SUPPORT        ( FALSE )

#define HSVPRINS_INVALID_VALUE      (-1) 

#define HSVPRINS_INVALID_PRESET     (-1) 

#define PRESENT_NAMELENGTH_ANALOG   (5)

#define SECAM_FIRST               ((mGetAnalogInstallationSequence() == div_SecamPal) || (mGetAnalogInstallationSequence() == div_SecamOnly) )

/* ANEESH: TODO: Make this as FALSE */
#define SECOND_PASS_REQUIRED     ((mGetAnalogInstallationSequence() == div_SecamPal) || (mGetAnalogInstallationSequence() == div_PalSecam) )


#if CHECK_SECAML_SUPPORT

#define IS_SECAML_SUPPORTED         (TRUE)//IsSECAMLSupported( )

#else

#define IS_SECAML_SUPPORTED         ( TRUE )

#endif

#define STATUS_MSG_LEN              (21)

#define HSV_INSTALL_INVLAID_ANALOG  (div_SupportEmptyAnalogChannels) 

#define IS_PRESET_INRANGE(x) ( ((x) >= div_MinPresetNo) && ((x) <= div_MaxPresetNo) )

typedef enum
{
    HsvinsStateNone = 0
        ,HsvinsStateSetFrequency
        ,HsvinsStateSearching
        ,HsvinsStateAcquiringTxt
        ,HsvinsStateTxtResetWait
        ,HsvinsStateTvSystemDetectWait
        ,HsvinsStateCheckAci
        ,HsvinsStateSignalStrengthMeasurement
}HsvAnaloginstallationState;
typedef enum
{
    insEventStationFound = 0
        ,insEventStationNotFound
        ,insEventTimeout
        ,insEventTxtInfoRecvdCheck
        ,insEventVpsRecvd
        ,insEventPkt830RecvdCNI
        ,insEventPkt830RecvdNI
        ,insEventPkt830RecvdSTATUS
        ,insEventTvSystemFound
        ,insEventTxplfResetOver
        ,insEventAciSearched
        ,insEventAciStored
        ,insEventAciStoreFail
        ,insEventAciStoreTimeOut
        ,insEventTvSystemDetectTimeOut
        ,insEventClearPresets
        ,insEventStorePresets
        ,insEventSignalStrengthDetectionInProgess
        ,insEventStopAutoInstallation        
        ,insEventSkipInstallation
        ,insEventAfcFreqChanged
        ,EventfeapiNOnStationFound
        ,EventfeapiNOnStationNotFound
		,EventStartManualInstallation
		,EventDelayedTvSystemDetected
}InstallationEvent;
#if mem_iPresent_CONSTANT

#else

#ifndef __cplusplus

#else

#endif

#endif
/* pointer to the preset names list, which is dynamivally allocated */

#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

#if CHECK_SECAML_SUPPORT

#endif

#if CHECK_SECAML_SUPPORT

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef mem_iPresent_CONSTANT
// TODO:#error The presence of "mem" must be statically known

#endif

tmFe_SearchMode_t TvSystemsearch;
static tmFe_SearchMode_t s__TvSystemsearch;
int ColorSystemSearch;
static int s__ColorSystemSearch;
int mCurrentSortingIndex;
static int s__mCurrentSortingIndex;

#if CHECK_SECAML_SUPPORT

#else

#endif

#if mem_iPresent_CONSTANT

HsvPresetSortData * PresetData;
static HsvPresetSortData * s__PresetData;
char *             presetNames;
static char *             s__presetNames;
Nat8 *             PresetIndex;
static Nat8 *             s__PresetIndex;
#else

#ifndef __cplusplus

HsvPresetSortData PresetData[div_MaxAnalogPresets];
static HsvPresetSortData s__PresetData[div_MaxAnalogPresets];
char presetNames[div_MaxAnalogPresets * div_PresetNameLength];
static char s__presetNames[div_MaxAnalogPresets * div_PresetNameLength];
Nat8 PresetIndex[div_MaxAnalogPresets];
static Nat8 s__PresetIndex[div_MaxAnalogPresets];
#else

HsvPresetSortData PresetData[IHsvPresetInstallationDiv_MaxAnalogPresets];
static HsvPresetSortData s__PresetData[IHsvPresetInstallationDiv_MaxAnalogPresets];
char presetNames[IHsvPresetInstallationDiv_MaxAnalogPresets * IHsvPresetInstallationDiv_PresetNameLength];
static char s__presetNames[IHsvPresetInstallationDiv_MaxAnalogPresets * IHsvPresetInstallationDiv_PresetNameLength];
Nat8 PresetIndex[IHsvPresetInstallationDiv_MaxAnalogPresets];
static Nat8 s__PresetIndex[IHsvPresetInstallationDiv_MaxAnalogPresets];
#endif

#endif
/* pointer to the preset names list, which is dynamivally allocated */

HsvPresetSortData miPreset;
static HsvPresetSortData s__miPreset;
Nat16 currentVpsCni;
static Nat16 s__currentVpsCni;
Nat16 currentPkt830Cni;
static Nat16 s__currentPkt830Cni;
Nat16 currentPkt830Ni;
static Nat16 s__currentPkt830Ni;
#ifndef __cplusplus

char miPresetName[ div_PresetNameLength ];
static char s__miPresetName[ div_PresetNameLength ];
char tempStr[div_PresetNameLength];
static char s__tempStr[div_PresetNameLength];
char defaultName[div_PresetNameLength];
static char s__defaultName[div_PresetNameLength];
#else

char miPresetName[ IHsvPresetInstallationDiv_PresetNameLength ];
static char s__miPresetName[ IHsvPresetInstallationDiv_PresetNameLength ];
char tempStr[IHsvPresetInstallationDiv_PresetNameLength];
static char s__tempStr[IHsvPresetInstallationDiv_PresetNameLength];
char defaultName[IHsvPresetInstallationDiv_PresetNameLength];
static char s__defaultName[IHsvPresetInstallationDiv_PresetNameLength];
#endif
static CHsvPresetInstallation_m_Priv *currentinstance;
char msgString[21];
static char s__msgString[21];
int installationMode;
static int s__installationMode;
int manualInstallationMode;
static int s__manualInstallationMode;
HsvChannel currentPreset;
static HsvChannel s__currentPreset;
HsvChannel lastPresetFound;
static HsvChannel s__lastPresetFound;
int noOfPresetsFound;
static int s__noOfPresetsFound;
int noOfNewPresetsFound;
static int s__noOfNewPresetsFound;
Pump prgInstallationPump;
static Pump s__prgInstallationPump;
int nbOfStationAfterSort;
static int s__nbOfStationAfterSort;
int setChannel;
static int s__setChannel;
int setFrequency;
static int s__setFrequency;
int setOffset;
static int s__setOffset;
Bool fineTune;
static Bool s__fineTune;
int presetNumberStored;
static int s__presetNumberStored;
int noOfPresetFoundInFirstPass;
static int s__noOfPresetFoundInFirstPass;
int aciTimeOutCounter;
static int s__aciTimeOutCounter;
int country;
static int s__country;
int SPointCSearch;
static int s__SPointCSearch;
int SPointSSearch;
static int s__SPointSSearch;
int tvsystemDetectCounter ;
static int s__tvsystemDetectCounter ;
#ifndef __cplusplus

int fieldCNI;
static int s__fieldCNI;
int fieldNI;
static int s__fieldNI;
int fieldSTATUS;
static int s__fieldSTATUS;
int fieldVPS;
static int s__fieldVPS;
#else

int fieldCNI;
static int s__fieldCNI;
int fieldNI;
static int s__fieldNI;
int fieldSTATUS;
static int s__fieldSTATUS;
int fieldVPS;
static int s__fieldVPS;
#endif

UInt32 lastTunerFrequency;
static UInt32 s__lastTunerFrequency;
UInt32 ManualInstallFrequency;
static UInt32 s__ManualInstallFrequency;
Bool automaticInstallationFirstPass;
static Bool s__automaticInstallationFirstPass;
Bool manualInstallationPendingStore;
static Bool s__manualInstallationPendingStore;
Bool prgInstallationInitialised ;
static Bool s__prgInstallationInitialised ;
Bool prgInstallationTurnOn ;
static Bool s__prgInstallationTurnOn ;
Bool installationStopped ;
static Bool s__installationStopped ;
Bool setFrequencyManual ;
static Bool s__setFrequencyManual ;
Bool setChannelManual ;
static Bool s__setChannelManual ;
Bool backGroundCniUpdationOn ;
static Bool s__backGroundCniUpdationOn ;
Bool stationFoundFlag ;
static Bool s__stationFoundFlag ;
Bool tvSystemFoundFlag ;
static Bool s__tvSystemFoundFlag ;
Bool txplfResetFlag ;
static Bool s__txplfResetFlag ;
Bool aciSearchOverFlag ;
static Bool s__aciSearchOverFlag ;
Bool askAciToStorePreset ;
static Bool s__askAciToStorePreset ;
Bool currentPresetAciSearch;
static Bool s__currentPresetAciSearch;
Bool presetFoundInFirstPass;
static Bool s__presetFoundInFirstPass;
Bool statusMessageFound ;
static Bool s__statusMessageFound ;
Bool aciTimeoutStarted ;
static Bool s__aciTimeoutStarted ;
Bool tvSystemDetectFlag ;
static Bool s__tvSystemDetectFlag ;
Bool positiveModulationSearchStarted ;
static Bool s__positiveModulationSearchStarted ;
Bool installMode;
static Bool s__installMode;
Bool manualStationFoundFlag ;
static Bool s__manualStationFoundFlag ;
Bool implicitInstRequired;
static Bool s__implicitInstRequired;
Bool changePresetAttrib;
static Bool s__changePresetAttrib;
Bool updateOnlyCniInBackground;
static Bool s__updateOnlyCniInBackground;
Bool allMemoryFilled;
static Bool s__allMemoryFilled;
Bool fineTuneSorC;
static Bool s__fineTuneSorC;
Bool signalStrengthMeasurementInProgress;
static Bool s__signalStrengthMeasurementInProgress;
Bool aciPresetStorageOn;
static Bool s__aciPresetStorageOn;
Bool HndlSetTunerFreqNtf;
static Bool s__HndlSetTunerFreqNtf;
tmFe_SearchMode_t searchmode;
static tmFe_SearchMode_t s__searchmode;
UInt32 freqendpos;
static UInt32 s__freqendpos;
int WaitForColorSystemPump;
static int s__WaitForColorSystemPump;
int AnalogPassNo;
static int s__AnalogPassNo;
int NoOfPresets;
static int s__NoOfPresets;
int installationState;
static int s__installationState;
Int32 mRfaMinAmplification,mRfaMaxAmplification;
static Int32 s__mRfaMinAmplification,s__mRfaMaxAmplification;
#if CHECK_SECAML_SUPPORT

#endif
int mGetAnalogInstallationSequence(void);

void StoreManualInstallationValues( HsvChannel channel )
    /****************************************************
     * function to store a preset in the NVM during manual 
     * installation
     *****************************************************/;
void mfeapiNOnStationFound(void);
void mfeapiNOnStationNotFound(void);
int mGetTunerFrequency(void);
int mGetFrequencySearchDirection(void);
void OnReceivedVps( void );
void OnReceivedPkt830CNI( void );
void OnReceivedPkt830NI( void );
void OnReceivedPkt830STATUS( void );
void ReaddataHandler(int event, Nat32 value );
void ProgramInstallationStep( int event, Nat32 value );
void OnTvSystemDetectedHadler( tmFe_TvSystem_t tvSystem );
    /************************************************************
     * Purpose: Pump Function for program installation.
     ************************************************************/
void mStartManualInstallation(void);

void SignalStrengthMeaured(int value);
void StoreData( void )
    /****************************************************
     * function to store current preset from the preset list
     * in the program data
     *****************************************************/;
void StoreDataEx( HsvPresetSortData *presetPtr,HsvChannel preset, Bool StoreInPresetList)
    /****************************************************
     * Purpose: This function stores all the data first
     *          into the structure and then it calls
     *          platform function to write the values
     *          obtained by platform to NVM.
     ****************************************************/;
void ContinueSearch( void )
    /*****************************************************
     * Purpose: Continue's search if the current preset is
     *          less than the maximum presets.
     *****************************************************/;
void continueSearchforPreset( void );
void TimeoutCheck( int preset )
    /*****************************************************
     * Purpose: Switches to next state after a timeout
     *          occurs.
     *****************************************************/;
void StationFound( int frequency )
    /*******************************************************
     * Purpose: This function is called when tuner sends a
     *          notification for station found.
     *          If AutoStoreMode is VPSPDC, acquire VPS and
     *          Packet830 data from teletext. Otherwise
     *          store data and proceed.
     *******************************************************/;
void CheckAIStateOnStationFound( int frequency )
    /****************************************************
     * function to handle Onstationfound notification in
     * automatic installation
     *****************************************************/;
void CheckMIStateOnStationFound( int frequency )
    /****************************************************
     * function to handle Onstationfound notification in
     * manual installation
     *****************************************************/;
void StationNotFound( void )
    /********************************************************
     * Purpose: This function is called when no more stations
     *          are found by the tuner.
     *          If a second pass is required, it is done.
     *          Otherwise do sorting if required, or send
     *          a notification for installation completed.
     ********************************************************/;
void CheckAIStateOnStationNotFound( void )
    /****************************************************
     * function to handle OnstationNotfound notification in
     * automatic installation
     *****************************************************/;
void AIStationNotFoundFreqSearchState(void)
    /****************************************************
     * function to handle Onstationfound notification in
     * automatic installation
     *****************************************************/;
void StartSecondPassSearch(void)
    /****************************************************
     * function to start second pass search
     *****************************************************/;
void SecondPassSearchOver(void)
    /****************************************************
     * function to
     *****************************************************/;
void CheckMIStateOnStationNotFound( void )
    /****************************************************
     * function to handle Onstationnotfound notification in
     * manual installation
     *****************************************************/;
void OnTvSystemDetected(int value)
    /****************************************************
     * function to handle Ontvsystemdetected notification
     *****************************************************/;
void EventVpsRecvd(HsvPresetSortData *presetPtr,int preset)
    /****************************************************
     * function to get the received VPS data
     *****************************************************/;
void EventPkt830CniRecvd( HsvPresetSortData *presetPtr,int preset)
    /****************************************************
     * function to get the received Packet 830 CNI data
     *****************************************************/;
void EventPkt830NiRecvd( HsvPresetSortData *presetPtr,int preset)
    /****************************************************
     * function to get the received Packet 830 NI data
     *****************************************************/;
void TxtInfoRecvdCheck( int preset )
    /****************************************************
     * function to check CNI/NI info
     *****************************************************/;
void StoreSortedList( int presetNo )
    /*************************************************************/
    /* Stores the preset information after AutomaticInstallation */
    /* In AutoStoremodeVpsPdc & AutoStoreModeVpsPdcAci           */
    /*************************************************************/;
void StartTimeOut( int time )
    /****************************************************
     * starts the timeout
     *****************************************************/;
void InstallationCompleted( void )
    /****************************************************
     * gives installation completed notification
     *****************************************************/;
void ChannelFound( void )
    /****************************************************
     * actions to be taken after channel is found
     *****************************************************/;
void GetPkt0Name( int preset )
    /****************************************************
     * Gives the name of Preset for a given preset in preset 
     * list
     *****************************************************/;
void GetPkt0NameEx( HsvPresetSortData *presetPtr,int preset )
    /****************************************************
     * Gives the name of Preset for a given preset
     *****************************************************/;
Bool PresetSearch(int presetInList,int frequency,Bool BeforeTxt)
    /************************************************************/
    /* This function Searches the preset in Data Base           */
    /* Function Returns the TRUE if preset is found in list and */
    /* have teletext Otherwise returns FALSE                    */
    /************************************************************/;
void AciStoreFail(int value)
    /****************************************************
     * function to handle aci store fail event
     *****************************************************/;
void AciTimeout(int value)
    /****************************************************
     * function to handle aci decode timeout event
     *****************************************************/;
void ClearRemainingPresets(void);
void ClearPresets(int presetNo)
    /*****************************************************/
    /*Clears Presets After Automatic Installation in mode*/
    /*AutoSroreModeNone,AutoStoreModeAci                 */
    /*****************************************************/;
void SetPresetDataIndicator( int prNo, Nat8 mask, Bool bit)
    /****************************************************
     * Purpose: returns Booean data indicator for a given 
     preset in the preset list
     ****************************************************/;
Bool GetPresetDataIndicator( int prNo, Nat8 mask)
    /****************************************************
     * Purpose: returns Booean data indicator for a given .
     preset in the preset list
     ****************************************************/;
Bool IsVpsPkt830InfoReceived( HsvPresetSortData *ptr)
    /****************************************************
     * checks whether VPS and Packet 830 info arrived
     ****************************************************/;
void SetDataIndicator( HsvPresetSortData *ptr, Nat8 mask, Bool bit)
    /****************************************************
     * Purpose: sets Boolean data indicator for a given 
     preset
     ****************************************************/;
Bool GetDataIndicator( HsvPresetSortData *ptr, Nat8 mask )
    /****************************************************
     * Purpose: returns Boolean data indicator for a given 
     preset
     ****************************************************/;
void GetPresetName(int prNo)
    /****************************************************
     * Purpose: returns preset name for a given preset in 
     the preset list
     ****************************************************/;
void GetPresetNameEx(HsvPresetSortData * presetPtr,int preset)
    /****************************************************
     * Purpose: returns preset name for a given preset
     ****************************************************/;
void AllocateMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases any memory which has been malloced 
     and mallocs again
     ****************************************************/;
void ReleaseMemoryForPresetList(void)
    /****************************************************
     * Purpose: Releases the memory which has been malloced
     ****************************************************/;
Bool RequestVpsP830( HsvPresetSortData * presetPtr)
    /****************************************************
     * Purpose: Releases the memory which has been malloced
     ****************************************************/;
void DoSorting(void)
    /****************************************************
     * Purpose: if any presets are found during band search,
     * this function calls the sorting functions.  
     ****************************************************/;
int StartChannelSearch( tmFe_ChanTable_t cht )
    /****************************************************
     * Purpose: Starts manual installation for S or C channel
     ****************************************************/;
void UpdateCniNameInManual(HsvChannel preset)
    /****************************************************
     * Purpose: update CNI and name in manual installation
     ****************************************************/;
void UpdateCniNameInAutomatic(HsvChannel preset)
    /****************************************************
     * Purpose: update CNI and name in automatic installation
     ****************************************************/;
Bool StartBackgroundPresetUpdation(HsvChannel channel,Bool updateOnlyCni);
void UpdatePresetInBackground(HsvChannel preset)
    /****************************************************
     * Purpose: update CNI and name in implicit installation
     ****************************************************/;
void ClearCurrentPreset(void);
int GetPresetIndexAfterSorting(int index);
void SignalStrengthDetectionCompleted(int value);
void sortWithSignalStrength(Nat8 *list ,int elements)
    /*****************************************************/
    /*  Parametrs :  List of the elements passed         */
    /*               Number of members passed            */  
    /*Purpose:       Sort  within the Group              */
    /*****************************************************/;
#if CHECK_SECAML_SUPPORT

Bool IsSECAMLSupported( );
#endif

void WaitForColorSystem(int param1, Nat32 param2);
tmErrorCode_t StartSearching( tmFe_SearchMode_t mode, UInt32 endFreq );
HsvDvbTvSystem ConvertFromPlatformTvSystem(tmFe_TvSystem_t inval);
Bool UpdateCNIinPgData( HsvPresetSortData data, HsvChannel channel );
void module__init(void){
#ifndef mem_iPresent_CONSTANT
// TODO:#error The presence of "mem" must be statically known

#endif

	TvSystemsearch	=	s__TvSystemsearch;
	ColorSystemSearch	=	s__ColorSystemSearch;
	mCurrentSortingIndex = s__mCurrentSortingIndex;
#if CHECK_SECAML_SUPPORT

#else

#endif

#if mem_iPresent_CONSTANT

	PresetData	=	s__PresetData;
	presetNames	=	s__presetNames;
	PresetIndex	=	s__PresetIndex;
#else

#ifndef __cplusplus

	memcpy((void*)PresetData,(void*)s__PresetData,sizeof(PresetData));
	memcpy((void*)presetNames,(void*)s__presetNames,sizeof(presetNames));
	memcpy((void*)PresetIndex,(void*)s__PresetIndex,sizeof(PresetIndex));
#else

	memcpy((void*)PresetData,(void*)s__PresetData,sizeof(PresetData));
	memcpy((void*)presetNames,(void*)s__presetNames,sizeof(presetNames));
	memcpy((void*)PresetIndex,(void*)s__PresetIndex,sizeof(PresetIndex));
#endif

#endif
/* pointer to the preset names list, which is dynamivally allocated */

	miPreset	=	s__miPreset;
	currentVpsCni	=	s__currentVpsCni;
	currentPkt830Cni	=	s__currentPkt830Cni;
	currentPkt830Ni	=	s__currentPkt830Ni;
#ifndef __cplusplus

	memcpy((void*)miPresetName,(void*)s__miPresetName,sizeof(miPresetName));
	memcpy((void*)tempStr,(void*)s__tempStr,sizeof(tempStr));
	memcpy((void*)defaultName,(void*)s__defaultName,sizeof(defaultName));
#else

	memcpy((void*)miPresetName,(void*)s__miPresetName,sizeof(miPresetName));
	memcpy((void*)tempStr,(void*)s__tempStr,sizeof(tempStr));
	memcpy((void*)defaultName,(void*)s__defaultName,sizeof(defaultName));
#endif

	memcpy((void*)msgString,(void*)s__msgString,sizeof(msgString));
	installationMode	=	s__installationMode;
	manualInstallationMode	=	s__manualInstallationMode;
	currentPreset	=	s__currentPreset;
	lastPresetFound	=	s__lastPresetFound;
	noOfPresetsFound	=	s__noOfPresetsFound;
	noOfNewPresetsFound	=	s__noOfNewPresetsFound;
	prgInstallationPump	=	s__prgInstallationPump;
	nbOfStationAfterSort	=	s__nbOfStationAfterSort;
	setChannel	=	s__setChannel;
	setFrequency	=	s__setFrequency;
	setOffset	=	s__setOffset;
	fineTune	=	s__fineTune;
	presetNumberStored	=	s__presetNumberStored;
	noOfPresetFoundInFirstPass	=	s__noOfPresetFoundInFirstPass;
	aciTimeOutCounter	=	s__aciTimeOutCounter;
	country	=	s__country;
	SPointCSearch	=	s__SPointCSearch;
	SPointSSearch	=	s__SPointSSearch;
	tvsystemDetectCounter	=	s__tvsystemDetectCounter;
#ifndef __cplusplus

	fieldCNI	=	s__fieldCNI;
	fieldNI	=	s__fieldNI;
	fieldSTATUS	=	s__fieldSTATUS;
	fieldVPS	=	s__fieldVPS;
#else

	fieldCNI	=	s__fieldCNI;
	fieldNI	=	s__fieldNI;
	fieldSTATUS	=	s__fieldSTATUS;
	fieldVPS	=	s__fieldVPS;
#endif

	lastTunerFrequency	=	s__lastTunerFrequency;
	ManualInstallFrequency	=	s__ManualInstallFrequency;
	automaticInstallationFirstPass	=	s__automaticInstallationFirstPass;
	manualInstallationPendingStore	=	s__manualInstallationPendingStore;
	prgInstallationInitialised	=	s__prgInstallationInitialised;
	prgInstallationTurnOn	=	s__prgInstallationTurnOn;
	installationStopped	=	s__installationStopped;
	setFrequencyManual	=	s__setFrequencyManual;
	setChannelManual	=	s__setChannelManual;
	backGroundCniUpdationOn	=	s__backGroundCniUpdationOn;
	stationFoundFlag	=	s__stationFoundFlag;
	tvSystemFoundFlag	=	s__tvSystemFoundFlag;
	txplfResetFlag	=	s__txplfResetFlag;
	aciSearchOverFlag	=	s__aciSearchOverFlag;
	askAciToStorePreset	=	s__askAciToStorePreset;
	currentPresetAciSearch	=	s__currentPresetAciSearch;
	presetFoundInFirstPass	=	s__presetFoundInFirstPass;
	statusMessageFound	=	s__statusMessageFound;
	aciTimeoutStarted	=	s__aciTimeoutStarted;
	tvSystemDetectFlag	=	s__tvSystemDetectFlag;
	positiveModulationSearchStarted	=	s__positiveModulationSearchStarted;
	installMode	=	s__installMode;
	manualStationFoundFlag	=	s__manualStationFoundFlag;
	implicitInstRequired	=	s__implicitInstRequired;
	changePresetAttrib	=	s__changePresetAttrib;
	updateOnlyCniInBackground	=	s__updateOnlyCniInBackground;
	allMemoryFilled	=	s__allMemoryFilled;
	fineTuneSorC	=	s__fineTuneSorC;
	signalStrengthMeasurementInProgress	=	s__signalStrengthMeasurementInProgress;
	aciPresetStorageOn	=	s__aciPresetStorageOn;
	HndlSetTunerFreqNtf	=	s__HndlSetTunerFreqNtf;
	searchmode	=	s__searchmode;
	freqendpos	=	s__freqendpos;
	WaitForColorSystemPump	=	s__WaitForColorSystemPump;
	AnalogPassNo	=	s__AnalogPassNo;
	NoOfPresets	=	s__NoOfPresets;
	installationState	=	s__installationState;
	mRfaMinAmplification	=	s__mRfaMinAmplification;
	mRfaMaxAmplification	=	s__mRfaMaxAmplification;
#if CHECK_SECAML_SUPPORT

#endif

#if CHECK_SECAML_SUPPORT

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef ANALOG_TABLE
#undef ANALOG_TABLE
#endif //ANALOG_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef LEAST_COUNT_FOR_ACI_TIMEOUT
#undef LEAST_COUNT_FOR_ACI_TIMEOUT
#endif //LEAST_COUNT_FOR_ACI_TIMEOUT
#ifdef TIME_OUT_TVSYSTEM
#undef TIME_OUT_TVSYSTEM
#endif //TIME_OUT_TVSYSTEM
#ifdef CHECK_SECAML_SUPPORT
#undef CHECK_SECAML_SUPPORT
#endif //CHECK_SECAML_SUPPORT
#ifdef HSVPRINS_INVALID_VALUE
#undef HSVPRINS_INVALID_VALUE
#endif //HSVPRINS_INVALID_VALUE
#ifdef HSVPRINS_INVALID_PRESET
#undef HSVPRINS_INVALID_PRESET
#endif //HSVPRINS_INVALID_PRESET
#ifdef PRESENT_NAMELENGTH_ANALOG
#undef PRESENT_NAMELENGTH_ANALOG
#endif //PRESENT_NAMELENGTH_ANALOG
#ifdef SECAM_FIRST
#undef SECAM_FIRST
#endif //SECAM_FIRST
#ifdef SECOND_PASS_REQUIRED
#undef SECOND_PASS_REQUIRED
#endif //SECOND_PASS_REQUIRED
#ifdef IS_SECAML_SUPPORTED
#undef IS_SECAML_SUPPORTED
#endif //IS_SECAML_SUPPORTED
#ifdef IS_SECAML_SUPPORTED
#undef IS_SECAML_SUPPORTED
#endif //IS_SECAML_SUPPORTED
#ifdef STATUS_MSG_LEN
#undef STATUS_MSG_LEN
#endif //STATUS_MSG_LEN
#ifdef HSV_INSTALL_INVLAID_ANALOG
#undef HSV_INSTALL_INVLAID_ANALOG
#endif //HSV_INSTALL_INVLAID_ANALOG
#ifdef IS_PRESET_INRANGE(x)
#undef IS_PRESET_INRANGE(x)
#endif //IS_PRESET_INRANGE(x)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif
#endif //LOCAL_UNDEFINES
