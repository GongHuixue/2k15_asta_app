#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define ACI_INITIAL_PAGENUMBER              (0x1BE)

#define MAX_PRESETROWS_PER_PAGE             (21)

#define INVALID_FREQUENCY                   (0)

#define MAX_ACILANGUAGES_INPAGE             (6)

#define INVALID_PRESETNO                    (0xff)

#define MAXMAG                              (8)

#define RESTOREPAGEACQTIMEOUTVALUE 		(120 * 1000)
#define ACIACQUISITIONTIMEOUTVALUE		(120 * 1000)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)


/*****************************************************************
 * local type declarations 
 *****************************************************************/

typedef enum   { stIdle = 0
    , stStart
        , stExtensionPage
        , stEvaluateLanguage
        , stEvaluateMtp
        , stHeaderMatchSuccessful
        , stWaitForUser
        , stMtpSelectedPage
        , stDefaultPage
        , stMaxPriorityPage
        , stRestoreMtp
        , stCompleted
        , stStorePresets
        , stWaitForContinueDisplay
} aciState;
typedef enum   { aciTimeoutStartAci = 0
    , aciTimeoutTuner
        , aciTimeoutServiceLabel
        , aciTimeoutInvalid
} aciTimeOut;
#ifndef __cplusplus

#else

#endif

typedef enum   { eStationFoundTxtReset = 0
    , eStationNotFound
        , eHeaderDecoded
        , ePageDecodeSuccessful
        , ePageDecodeFailure
        , eAciPageTimerExpired
        , eSelectIndex
        , eDisplayTimerExpired
        , eTeletextReset
        , eTunerTimeout
        , eStartAciTimeout
        , eServiceLabelTimeout
        , eStorePresets
} aciEvent;
typedef void (CLASSSCOPE *EVENT_HANDLER)(void);
#ifdef __cplusplus

#endif


/****************************************************
 * Purpose : Intialises ACI component
 ****************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

Bool powerInitialised;
static Bool s__powerInitialised;
Bool initialised;
static Bool s__initialised;
aciState currentAciState;
static aciState s__currentAciState;
aciTimeOut currentAciTimeOut;
static aciTimeOut s__currentAciTimeOut;
Pump aciPump,TimerPump;
static Pump s__aciPump,s__TimerPump;
PageNr restoreMtpPage;
static PageNr s__restoreMtpPage;
Nat32 restoreMtpFrequency;
static Nat32 s__restoreMtpFrequency;
Nat32 startFrequency;
static Nat32 s__startFrequency;
PageNr currentAciPage;
static PageNr s__currentAciPage;
int currentDecodedTotalPresets;
static int s__currentDecodedTotalPresets;
Bool frequencyDetuned;
static Bool s__frequencyDetuned;
HsvAciBroadcaster currentAciBroadcaster;
static HsvAciBroadcaster s__currentAciBroadcaster;
HsvAciNetwork currentAciNetwork;
static HsvAciNetwork s__currentAciNetwork;
HsvAciMode currentAciMode;
static HsvAciMode s__currentAciMode;
HsvAciLanguage currentAciLanguage;
static HsvAciLanguage s__currentAciLanguage;
HsvAciPriority currentAciPriority;
static HsvAciPriority s__currentAciPriority;
HsvAciPriority currentMaxAciPriority;
static HsvAciPriority s__currentMaxAciPriority;
PageNr currentMaxPriorityPage;
static PageNr s__currentMaxPriorityPage;
Nat32 currentMaxPriorityFrequency;
static Nat32 s__currentMaxPriorityFrequency;
HsvAciMultiInfo currentMtpInfo;
static HsvAciMultiInfo s__currentMtpInfo;
Bool TimerHandlingNeeded;
static Bool s__TimerHandlingNeeded;

#ifndef __cplusplus

HsvAciSingleInfo decodedPresets[adiv_MaxPresets];
static HsvAciSingleInfo s__decodedPresets[adiv_MaxPresets];
#else

HsvAciSingleInfo decodedPresets[ICesPaciDiv_MaxPresets];
static HsvAciSingleInfo s__decodedPresets[ICesPaciDiv_MaxPresets];
#endif

Nat8 currentMtpIndex;
static Nat8 s__currentMtpIndex;
Nat8 currentMtpCount;
static Nat8 s__currentMtpCount;
STimer pageTimerHandle;
static STimer s__pageTimerHandle;
STimer displayTimerHandle;
static STimer s__displayTimerHandle;
int selectedIndex;
static int s__selectedIndex;
Bool completedStatus;
static Bool s__completedStatus;
Bool writeIndataInProgress;
static Bool s__writeIndataInProgress;
Bool waitForStationFoundTxtReset;
static Bool s__waitForStationFoundTxtReset;
Bool receivedTxtReset;
static Bool s__receivedTxtReset;
Bool receivedOnStationFound;
static Bool s__receivedOnStationFound;
Bool receivedOnStationNotFound;
static Bool s__receivedOnStationNotFound;
Nat8 currentPresetToStore;
static Nat8 s__currentPresetToStore;
int tryHeader;
static int s__tryHeader;
EVENT_HANDLER ce_eventHandlerTable[13];
static EVENT_HANDLER s__ce_eventHandlerTable[13];
#ifdef __cplusplus

#endif


/****************************************************
 * Purpose : Intialises ACI component
 ****************************************************/

void OnStationFound( void );
void OnStationNotFound( void );
void AciHandler(int event, Nat32 key);
void EventHandlerHeaderDecoded(void );
void EventHandlerOnPageDecodeSuccessful(void );
void processAciPage( void );
void EventHandlerStationFoundTxtReset(void );
void EventHandlerStationNotFound(void );
void EventHandlerPageTimerExpired(void );
void EventHandlerTeletextReset(void );
void EventHandlerTunerTimeout(void );
void EventHandlerStartAciTimeout(void );
void EventHandlerServiceLabelTimeout(void );
Bool ServiceLabelMatchPossible(Nat8 mag);
Bool IsTxtAvailable(void);
void EventHandlerSelectIndex(void );
void EventHandlerStorePresets(void );
void OnAciPageTimerExpired( void );
void EventHandlerDisplayTimerExpired(void );
void OnDisplayTimerExpired( void );
void OnPumpTimerExpired(int system, Nat32 timeoutId );
Bool StartCurrentMtpItemDecoding();
void CopyPresets();
void StoreInData();
HsvAciPriority CalculatePriority(HsvAciBroadcaster broadcaster, HsvAciNetwork network);
Bool CheckHeaderMatch();
void TuneFrequency(Nat32 frequency);
void CallDecodeStart(PageNr page);
void WriteIndataAndSendCompletedNotification( void );
void SendCompletedNotification(Bool success);
void ResetVariables();
void module__init(void){
#ifndef __cplusplus

#else

#endif

	powerInitialised	=	s__powerInitialised;
	initialised	=	s__initialised;
	currentAciState	=	s__currentAciState;
	currentAciTimeOut	=	s__currentAciTimeOut;
	aciPump	=	s__aciPump;
	TimerPump	=	s__TimerPump;
	restoreMtpPage	=	s__restoreMtpPage;
	restoreMtpFrequency	=	s__restoreMtpFrequency;
	startFrequency	=	s__startFrequency;
	currentAciPage	=	s__currentAciPage;
	currentDecodedTotalPresets	=	s__currentDecodedTotalPresets;
	frequencyDetuned	=	s__frequencyDetuned;
	currentAciBroadcaster	=	s__currentAciBroadcaster;
	currentAciNetwork	=	s__currentAciNetwork;
	currentAciMode	=	s__currentAciMode;
	currentAciLanguage	=	s__currentAciLanguage;
	currentAciPriority	=	s__currentAciPriority;
	currentMaxAciPriority	=	s__currentMaxAciPriority;
	currentMaxPriorityPage	=	s__currentMaxPriorityPage;
	currentMaxPriorityFrequency	=	s__currentMaxPriorityFrequency;
	currentMtpInfo	=	s__currentMtpInfo;
#ifndef __cplusplus

	memcpy((void*)decodedPresets,(void*)s__decodedPresets,sizeof(decodedPresets));
#else

	memcpy((void*)decodedPresets,(void*)s__decodedPresets,sizeof(decodedPresets));
#endif

	currentMtpIndex	=	s__currentMtpIndex;
	currentMtpCount	=	s__currentMtpCount;
	pageTimerHandle	=	s__pageTimerHandle;
	displayTimerHandle	=	s__displayTimerHandle;
	selectedIndex	=	s__selectedIndex;
	completedStatus	=	s__completedStatus;
	writeIndataInProgress	=	s__writeIndataInProgress;
	waitForStationFoundTxtReset	=	s__waitForStationFoundTxtReset;
	receivedTxtReset	=	s__receivedTxtReset;
	receivedOnStationFound	=	s__receivedOnStationFound;
	receivedOnStationNotFound	=	s__receivedOnStationNotFound;
	currentPresetToStore	=	s__currentPresetToStore;
	tryHeader	=	s__tryHeader;
	TimerHandlingNeeded = s__TimerHandlingNeeded;
	memcpy((void*)ce_eventHandlerTable,(void*)s__ce_eventHandlerTable,sizeof(ce_eventHandlerTable));
#ifdef __cplusplus

#endif


/****************************************************
 * Purpose : Intialises ACI component
 ****************************************************/

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef ACI_INITIAL_PAGENUMBER
#undef ACI_INITIAL_PAGENUMBER
#endif //ACI_INITIAL_PAGENUMBER
#ifdef MAX_PRESETROWS_PER_PAGE
#undef MAX_PRESETROWS_PER_PAGE
#endif //MAX_PRESETROWS_PER_PAGE
#ifdef INVALID_FREQUENCY
#undef INVALID_FREQUENCY
#endif //INVALID_FREQUENCY
#ifdef MAX_ACILANGUAGES_INPAGE
#undef MAX_ACILANGUAGES_INPAGE
#endif //MAX_ACILANGUAGES_INPAGE
#ifdef INVALID_PRESETNO
#undef INVALID_PRESETNO
#endif //INVALID_PRESETNO
#ifdef MAXMAG
#undef MAXMAG
#endif //MAXMAG
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
