#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define MAXMAG                   (8)

#define CONCEAL_CHAR             (0x18)

#define INVALID_PRESET           (0xff)

#define INVALID_FREQUENCY        (0)

#define PAGEWIDTH_NORMAL         (40)

#define TXTCOLUMNMAX             (81)

#define PLANE_T0                 (0)

#define INITIAL_START_PAGE       (0x1BE)

#define MAX_LANGUAGEPAGES_INSYSTEMROW      ( 06 )

#define MAX_FIXED_SINGLEPRESET_PER_PAGE    ( 42 )

#define MAX_PRESETROWS_PER_PAGE            ( 21 )

#define tspah_SCHO_minvalue                ( 8 ) 

#define TX_COLOUR_BLACK                    ( 0 )

#define TX_COLOUR_TRANSPARENT              ( 8 )

/*****************************************************************
 * local type declarations 
 *****************************************************************/

typedef enum   
{ 
    AciStateOff,
    AciStateAcquisition,
    AciStateDecodingLst,
    AciStateDecodingMtp,
    AciStateDecodeLstSuccessfull,
    AciStateDecodeLstFail,
    AciStateDecodeMtpSuccessfull,
    AciStateDecodeMtpFail,
    AciStateWait
}AciState;
typedef struct languagePageInfoStruct
{
    HsvAciLanguage language;
    PageNr pageNo;
}languagePageInfo;
#ifdef __cplusplus

#endif

/*****************************************************************
 * Power functions
 *****************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)

Nat8 presetCount;
static Nat8 s__presetCount;
HsvAciMode mode;
static HsvAciMode s__mode;
HsvAciNetwork network;
static HsvAciNetwork s__network;
HsvAciLanguage language;
static HsvAciLanguage s__language;
HsvAciBroadcaster broadcaster;
static HsvAciBroadcaster s__broadcaster;

Pump pumpDecodePage;
static Pump s__pumpDecodePage;
Pump pumpRequestPage;
static Pump s__pumpRequestPage;
Bool Initialised;
static Bool s__Initialised;
Bool PowerInitialised;
static Bool s__PowerInitialised;
Bool InterfacesConnected;
static Bool s__InterfacesConnected;
TxtPageHandle pageHandle;
static TxtPageHandle s__pageHandle;
Nat8 * dPacket;
static Nat8 * s__dPacket;
int mtpCurrentCount;
static int s__mtpCurrentCount;
Nat8 mtpCurrentRow;
static Nat8 s__mtpCurrentRow;
Bool aciDecodeOn;
static Bool s__aciDecodeOn;
PageNr extensionPageNumber;
static PageNr s__extensionPageNumber;

Nat8 multiPackageItems;
static Nat8 s__multiPackageItems;
PageNr MtpDefaultPage;
static PageNr s__MtpDefaultPage;
PageNr currentRequestedPage;
static PageNr s__currentRequestedPage;
Subcode currentReceivedPageSubcode;
static Subcode s__currentReceivedPageSubcode;
int currentState;
static int s__currentState;
HsvAciSingleInfo presetSingle[MAX_FIXED_SINGLEPRESET_PER_PAGE];
static HsvAciSingleInfo s__presetSingle[MAX_FIXED_SINGLEPRESET_PER_PAGE];
HsvAciMultiInfo mtpArray[MAX_PRESETROWS_PER_PAGE];
static HsvAciMultiInfo s__mtpArray[MAX_PRESETROWS_PER_PAGE];
Nat8 mtpRow[MAX_PRESETROWS_PER_PAGE];
static Nat8 s__mtpRow[MAX_PRESETROWS_PER_PAGE];
languagePageInfo aciLanguageArray[MAX_LANGUAGEPAGES_INSYSTEMROW];
static languagePageInfo s__aciLanguageArray[MAX_LANGUAGEPAGES_INSYSTEMROW];
TWindowId mainWindowId;
static TWindowId s__mainWindowId;
Bool txtMainWindow;
static Bool s__txtMainWindow;
Bool ConfigureOn;
static Bool s__ConfigureOn;
Bool headerDecoded;
static Bool s__headerDecoded;
Nat8 FourtySpaces[40];
static Nat8 s__FourtySpaces[40];
Nat8 pktptr[400];
static Nat8 s__pktptr[400];

#ifdef __cplusplus

#endif

/*****************************************************************
 * Power functions
 *****************************************************************/

void RequestPageHandler(int system, Nat32 key);
void DecodePageHandler(int system, Nat32 key);
void AciSingleDecode(void);
void AciMultiDecode(void);
void ResetVariables();
void resetMultiPageInfo( void );
TWindowId CreateMainWindow( Nat8 topLeftRow, Nat8 topLeftColumn, Nat8 bottomRightRow, Nat8 bottomRightColumn );
void DeleteMainWindow( TWindowId winId );
Bool DecodeMtpPage( Nat8* txtInfo, Nat8* dPacketx );
void AciDecodePreset(Nat8* txtinfo );
void FindNetworkInfo(void);
void GetModeInfo(void);
void GetLanguageInfo(void);
HsvAciLanguage ConvertLanguageCode( Nat8 code );
void SuggestPage(PageNr pn);
Nat32 DecAsciiToNat( Nat8* text, Nat8 number_of_digits, Bool *success );
Nat32 HexAsciiToNat( Nat8* text,Nat8 numberofdigits,Bool *success );
Bool IsXDigit(Nat8 x);
Bool IsDigit(Nat8 x);
Bool CheckIfReservedPage(PageNr pn);
void CopyPktString( Nat8 *src, Nat8 *dest, int count);
void module__init(void){
	pumpDecodePage	=	s__pumpDecodePage;
	pumpRequestPage	=	s__pumpRequestPage;
	Initialised	=	s__Initialised;
	PowerInitialised	=	s__PowerInitialised;
	InterfacesConnected	=	s__InterfacesConnected;
	pageHandle	=	s__pageHandle;
	dPacket	=	s__dPacket;
	memcpy((void*)pktptr,(void*)s__pktptr,sizeof(pktptr));
	mtpCurrentCount	=	s__mtpCurrentCount;
	mtpCurrentRow	=	s__mtpCurrentRow;
	aciDecodeOn	=	s__aciDecodeOn;
	mode	=	s__mode;
	network	=	s__network;
	language	=	s__language;
	broadcaster	=	s__broadcaster;
	extensionPageNumber	=	s__extensionPageNumber;
	presetCount	=	s__presetCount;
	multiPackageItems	=	s__multiPackageItems;
	MtpDefaultPage	=	s__MtpDefaultPage;
	currentRequestedPage	=	s__currentRequestedPage;
	currentReceivedPageSubcode	=	s__currentReceivedPageSubcode;
	currentState	=	s__currentState;
	memcpy((void*)presetSingle,(void*)s__presetSingle,sizeof(presetSingle));
	memcpy((void*)mtpArray,(void*)s__mtpArray,sizeof(mtpArray));
	memcpy((void*)mtpRow,(void*)s__mtpRow,sizeof(mtpRow));
	memcpy((void*)aciLanguageArray,(void*)s__aciLanguageArray,sizeof(aciLanguageArray));
	mainWindowId	=	s__mainWindowId;
	txtMainWindow	=	s__txtMainWindow;
	ConfigureOn	=	s__ConfigureOn;
	headerDecoded	=	s__headerDecoded;
	memcpy((void*)FourtySpaces,(void*)s__FourtySpaces,sizeof(FourtySpaces));
#ifdef __cplusplus

#endif

/*****************************************************************
 * Power functions
 *****************************************************************/

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MAXMAG
#undef MAXMAG
#endif //MAXMAG
#ifdef CONCEAL_CHAR
#undef CONCEAL_CHAR
#endif //CONCEAL_CHAR
#ifdef INVALID_PRESET
#undef INVALID_PRESET
#endif //INVALID_PRESET
#ifdef INVALID_FREQUENCY
#undef INVALID_FREQUENCY
#endif //INVALID_FREQUENCY
#ifdef PAGEWIDTH_NORMAL
#undef PAGEWIDTH_NORMAL
#endif //PAGEWIDTH_NORMAL
#ifdef TXTCOLUMNMAX
#undef TXTCOLUMNMAX
#endif //TXTCOLUMNMAX
#ifdef PLANE_T0
#undef PLANE_T0
#endif //PLANE_T0
#ifdef INITIAL_START_PAGE
#undef INITIAL_START_PAGE
#endif //INITIAL_START_PAGE
#ifdef MAX_LANGUAGEPAGES_INSYSTEMROW
#undef MAX_LANGUAGEPAGES_INSYSTEMROW
#endif //MAX_LANGUAGEPAGES_INSYSTEMROW
#ifdef MAX_FIXED_SINGLEPRESET_PER_PAGE
#undef MAX_FIXED_SINGLEPRESET_PER_PAGE
#endif //MAX_FIXED_SINGLEPRESET_PER_PAGE
#ifdef MAX_PRESETROWS_PER_PAGE
#undef MAX_PRESETROWS_PER_PAGE
#endif //MAX_PRESETROWS_PER_PAGE
#ifdef tspah_SCHO_minvalue
#undef tspah_SCHO_minvalue
#endif //tspah_SCHO_minvalue
#ifdef TX_COLOUR_BLACK
#undef TX_COLOUR_BLACK
#endif //TX_COLOUR_BLACK
#ifdef TX_COLOUR_TRANSPARENT
#undef TX_COLOUR_TRANSPARENT
#endif //TX_COLOUR_TRANSPARENT
#endif //LOCAL_UNDEFINES
