#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define AUTO_MODE       (ins_InstallationModeAutomatic)

#define UPDATE_MODE     (ins_InstallationModeUpdate)

#define MANUAL_MODE     (ins_InstallationModeWeakSignal)

#define PRESCAN_MODE    (ins_InstallationModePreScan)

#define FINLAND_MAX_SYM_VALS       (4)

#define NETHERLANDS_MAX_SYM_VALS   (2)

#define NETHERLANDS_ZIGGO_MAX_SYM_VALS   (2)

#define AUSTRIA_SWTZ_MAX_SYM_VALS  (3)

#define GERMANY_MAX_SYM_VALS       (3)

#define SWEDEN_MAX_SYM_VALS        (4)

#define NORWAY_MAX_SYM_VALS        (4)

#define DENMARK_MAX_SYM_VALS       (4)

#define CHINA_MAX_SYM_VALS         (3)      

#define DVBC_LIGHT_MAX_SYM_VALS    (3)

#define HPR_MAX_SYM_VALS           (3)

#define IRELAND_MAX_SYM_VALS       (4)

#define UKRAINE_MAX_SYM_VALS       (2)

#define FINLAND_MAX_FREQ_VALS      (3)

#define ROMANIA_MAX_FREQ_VALS		(4)

#define GERMANY_MAX_FREQ_VALS      (16)

#define SWEDEN_MAX_FREQ_VALS       (5)

#define NORWAY_MAX_FREQ_VALS       (3)

#define DENMARK_MAX_FREQ_VALS      (4)

#define CHINA_MAX_FREQ_VALS        (3)

#define UKRAINE_MAX_FREQ_VALS      (1)

#define BULGARIA_BLIZOO_FREQ_VALS  (10)

#define MAX_MOD_VALS               (3)

#define NETHERLANDS_MAX_MOD_VALS   (5)

#define AUSTRIA_SWTZ_MAX_MOD_VALS  (5)

#define GERMANY_MAX_MOD_VALS       (2)

#define DVBC_LIGHT_MAX_MOD_VALS    (5)

#define HPRI_MAX_MOD_VALS          (5)

#define SHARED_WIDGET_DIR_PATH_SIZE  (17)

#define SHARED_DIR_PATH_SIZE       (9)

#define SWEDEN_FULLSCAN_MAX_SYM_VALS   (7) // brg36mgr#112856 Add 4 more PreDef Values for full scan only

#define NORWAY_FULLSCAN_MAX_SYM_VALS   (6) // brg36mgr#112856 Add 3 more PreDef Values for full scan only

#define DENMARK_FULLSCAN_MAX_SYM_VALS  (6) // brg36mgr#112856 Add 3 more PreDef Values for full scan only

#define FINLAND_FULLSCAN_MAX_SYM_VALS  (2)

#define BELGIUM_MAX_SYM_VALS       (3)

#define BELGIUM_TELENET_MAX_SYM_VALS     (2)

#define BELGIUM_MAX_MOD_VALS       (5)

#define ROMANIA_AUTO_MOD_VALS	   (2)

#define DENMARKYOUSEE_MAX_FREQ_VALS (4)

#define CANALDIGITAL_MAX_FREQ_VALS	 (4)

#define SLOVENIATELEMACH_MAX_FREQ_VALS (1)


#define INVALID_PID				   (0x1FFF)


typedef enum
{
    divDVBTFullBitPos,
    divDVBTLightBitPos,
    divDVBCFullBitPos,
    divDVBCLightBitPos,
    divAnalogOnlyBitPos,
    divDvbT2BitPos
} divBitPos;
#ifndef __cplusplus

#endif


/*intf: eurdiv*/

/*intf: eurdiv*/

/* retval is a bit vector with bit positions according to enum divBitPos */

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif
//#define nvmapps_NumberOfEntries 0

/*intf: IPlfApiTuning*/

#ifndef __cplusplus

#endif


/* Interfaces from IHsvChanlibPosixLight.id */

#ifndef __cplusplus 

#endif

#ifndef __cplusplus    

#endif	

#ifndef __cplusplus 

#endif
/* Interfaces from IHsvProgramDataControl3.id */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int FinlandSymVals[FINLAND_MAX_SYM_VALS];
static int s__FinlandSymVals[FINLAND_MAX_SYM_VALS];
int FinlandFullScanSymVals[FINLAND_FULLSCAN_MAX_SYM_VALS];
static int s__FinlandFullScanSymVals[FINLAND_FULLSCAN_MAX_SYM_VALS];
int NetherlandsSymVals[NETHERLANDS_MAX_SYM_VALS];
static int s__NetherlandsSymVals[NETHERLANDS_MAX_SYM_VALS];
int NetherlandsZiggoSymVals[NETHERLANDS_MAX_SYM_VALS];
static int s__NetherlandsZiggoSymVals[NETHERLANDS_MAX_SYM_VALS];
int GermanySymVals[GERMANY_MAX_SYM_VALS];
static int s__GermanySymVals[GERMANY_MAX_SYM_VALS];
int AustriaSwtzSymVals[AUSTRIA_SWTZ_MAX_SYM_VALS];
static int s__AustriaSwtzSymVals[AUSTRIA_SWTZ_MAX_SYM_VALS];
int SwedenSymVals[SWEDEN_MAX_SYM_VALS];
static int s__SwedenSymVals[SWEDEN_MAX_SYM_VALS];
int SwedenFullScanSymVals[SWEDEN_FULLSCAN_MAX_SYM_VALS];
static int s__SwedenFullScanSymVals[SWEDEN_FULLSCAN_MAX_SYM_VALS];
int NorwaySymVals[NORWAY_MAX_SYM_VALS];
static int s__NorwaySymVals[NORWAY_MAX_SYM_VALS];
int NorwayFullScanSymVals[NORWAY_FULLSCAN_MAX_SYM_VALS];
static int s__NorwayFullScanSymVals[NORWAY_FULLSCAN_MAX_SYM_VALS];
int DenmarkSymVals[DENMARK_MAX_SYM_VALS];
static int s__DenmarkSymVals[DENMARK_MAX_SYM_VALS];
int DenmarkFullScanSymVals[DENMARK_FULLSCAN_MAX_SYM_VALS];
static int s__DenmarkFullScanSymVals[DENMARK_FULLSCAN_MAX_SYM_VALS];
int ChinaSymVals[CHINA_MAX_SYM_VALS];
static int s__ChinaSymVals[CHINA_MAX_SYM_VALS];
int DvbcLightSymVals[DVBC_LIGHT_MAX_SYM_VALS];
static int s__DvbcLightSymVals[DVBC_LIGHT_MAX_SYM_VALS];
int HPRSymVals[HPR_MAX_SYM_VALS];
static int s__HPRSymVals[HPR_MAX_SYM_VALS];
int IrelandSymVals[IRELAND_MAX_SYM_VALS];
static int s__IrelandSymVals[IRELAND_MAX_SYM_VALS];
int UkraineSymVals[UKRAINE_MAX_SYM_VALS];
static int s__UkraineSymVals[UKRAINE_MAX_SYM_VALS];
int FinlandFreqVals[FINLAND_MAX_FREQ_VALS];
static int s__FinlandFreqVals[FINLAND_MAX_FREQ_VALS];
int RomaniaFreqVals[ROMANIA_MAX_FREQ_VALS];
static int s__RomaniaFreqVals[ROMANIA_MAX_FREQ_VALS];
int GermanyFreqVals[GERMANY_MAX_FREQ_VALS];
static int s__GermanyFreqVals[GERMANY_MAX_FREQ_VALS];
int BulgariaBlizooFreqVals[BULGARIA_BLIZOO_FREQ_VALS];
static int s__BulgariaBlizooFreqVals[BULGARIA_BLIZOO_FREQ_VALS];
int SwedenFreqVals[SWEDEN_MAX_FREQ_VALS];
static int s__SwedenFreqVals[SWEDEN_MAX_FREQ_VALS];
int NorwayFreqVals[NORWAY_MAX_FREQ_VALS];
static int s__NorwayFreqVals[NORWAY_MAX_FREQ_VALS];
int DenmarkFreqVals[DENMARK_MAX_FREQ_VALS];
static int s__DenmarkFreqVals[DENMARK_MAX_FREQ_VALS];
int ChinaFreqVals[CHINA_MAX_FREQ_VALS];
static int s__ChinaFreqVals[CHINA_MAX_FREQ_VALS];
int UkraineFreqVals[UKRAINE_MAX_FREQ_VALS];
static int s__UkraineFreqVals[UKRAINE_MAX_FREQ_VALS];
int FinlandModVals[MAX_MOD_VALS];
static int s__FinlandModVals[MAX_MOD_VALS];
int NetherlandsModVals[NETHERLANDS_MAX_MOD_VALS];
static int s__NetherlandsModVals[NETHERLANDS_MAX_MOD_VALS];
int GermanyModVals[GERMANY_MAX_MOD_VALS];
static int s__GermanyModVals[GERMANY_MAX_MOD_VALS];
int AustriaSwtzModVals[AUSTRIA_SWTZ_MAX_MOD_VALS];
static int s__AustriaSwtzModVals[AUSTRIA_SWTZ_MAX_MOD_VALS];
int SwedenModVals[MAX_MOD_VALS];
static int s__SwedenModVals[MAX_MOD_VALS];
int NorwayModVals[MAX_MOD_VALS];
static int s__NorwayModVals[MAX_MOD_VALS];
int DenmarkModVals[MAX_MOD_VALS];
static int s__DenmarkModVals[MAX_MOD_VALS];
int DvbcLightModVals[DVBC_LIGHT_MAX_MOD_VALS];
static int s__DvbcLightModVals[DVBC_LIGHT_MAX_MOD_VALS];
int HPRIModVals[HPRI_MAX_MOD_VALS];
static int s__HPRIModVals[HPRI_MAX_MOD_VALS];
int BelgiumTelenetSymVals[BELGIUM_TELENET_MAX_SYM_VALS];
static int s__BelgiumTelenetSymVals[BELGIUM_TELENET_MAX_SYM_VALS];
int BelgiumSymVals[BELGIUM_MAX_SYM_VALS];
static int s__BelgiumSymVals[BELGIUM_MAX_SYM_VALS];
int BelgiumModVals[BELGIUM_MAX_MOD_VALS];
static int s__BelgiumModVals[BELGIUM_MAX_MOD_VALS];
int RomaniaAutomaticFreqModVals[ROMANIA_AUTO_MOD_VALS];
static int s__RomaniaAutomaticFreqModVals[ROMANIA_AUTO_MOD_VALS];
int DenMarkYouSeeFreqVals[DENMARKYOUSEE_MAX_FREQ_VALS];
static int s__DenMarkYouSeeFreqVals[DENMARKYOUSEE_MAX_FREQ_VALS];
int CanalDigitalFreqVals[CANALDIGITAL_MAX_FREQ_VALS];
static int s__CanalDigitalFreqVals[CANALDIGITAL_MAX_FREQ_VALS];
int SloveniaTelemachFreqVals[SLOVENIATELEMACH_MAX_FREQ_VALS];
static int s__SloveniaTelemachFreqVals[SLOVENIATELEMACH_MAX_FREQ_VALS];
int InsMedium;
static int s__InsMedium;
int InsInstallMedium;
static int s__InsInstallMedium;
int InsCountry;
static int s__InsCountry;
int InsRfSetting;
static int s__InsRfSetting;
int PbsMode;
static int s__PbsMode;
int ChServIDForUpdate;
int ChUniIDForUpdate;
Nat16 UpdatedChannelName[41];
int UpdatedONID;
int UpdatedTsID;
int IsDVBT2Scan;
int FocusedPlpId;
int IsExtractScanResult;
int UpdatedSymbolRate;
int InsInstallCountry;
static int s__InsInstallCountry;
Nat16 AudioPid;
static Nat16 s__AudioPid;
Nat16 VideoPid;
static Nat16 s__VideoPid;
Nat16 PcrPid;
static Nat16 s__PcrPid;
Nat16 AudioStreamType;
static Nat16 s__AudioStreamType;
Nat16 VideoStreamType;
static Nat16 s__VideoStreamType;
int itvdiv_On;
static int s__itvdiv_On;
int itvdiv_CountryDependent;
static int s__itvdiv_CountryDependent;
int itvdiv_Off;
static int s__itvdiv_Off;
int itvdiv_AtscDvbSupported;
static int s__itvdiv_AtscDvbSupported;
int itvdiv_DVBTInstallationSupported;
static int s__itvdiv_DVBTInstallationSupported;
Bool itvdiv_DvbtLightSupported;
static Bool s__itvdiv_DvbtLightSupported;
Bool IsForceCharacterCode;
static Bool s__IsForceCharacterCode;
int itvdiv_DVBCInstallationSupported;
static int s__itvdiv_DVBCInstallationSupported;
Bool itvdiv_DvbcLightSupported;
static Bool s__itvdiv_DvbcLightSupported;
int itvdiv_EnableDolbyFeaturing;
static int s__itvdiv_EnableDolbyFeaturing;
int itvdiv_ProdRegion;
static int s__itvdiv_ProdRegion;
int itvdiv_Australia;
static int s__itvdiv_Australia;
int amdivlib_brdcstdiv2_Off;
static int s__amdivlib_brdcstdiv2_Off;
int amdivlib_brdcstdiv_Off;
static int s__amdivlib_brdcstdiv_Off;
int amdivlib_brdcstdiv2_On;
static int s__amdivlib_brdcstdiv2_On;
int amdivlib_brdcstdiv2_DvbTandCSupported;
static int s__amdivlib_brdcstdiv2_DvbTandCSupported;
int amdivlib_brdcstdiv_DvbT2InstallationSupported;
static int s__amdivlib_brdcstdiv_DvbT2InstallationSupported;

Bool InsEnableDVBC;
Bool InsEnableDVBT;
Bool InsEnableAnalog;
#ifndef __cplusplus

volatile unsigned int *errlib__TraceGlobalRulesAge;
static volatile unsigned int *s__errlib__TraceGlobalRulesAge;
TraceSymbol *errlib__TraceSymbolLegacyPrintf;
static TraceSymbol *s__errlib__TraceSymbolLegacyPrintf;
int nopapi;
static int s__nopapi;
#endif


/*intf: eurdiv*/

/*intf: eurdiv*/

/* retval is a bit vector with bit positions according to enum divBitPos */

Bool m_CheckDVBDiversities(int country, int bitpos);
Bool IsDVBCSupported( void );
Bool IsDVBCLightSupported( void );
Bool IsDVBTSupported(void);
Bool IsMpeg4Supported(void);
Bool IsDVBTLightSupported(void);
Bool IsDVBTSupportedInSystemCountry(void);
Bool IsAnalogSupported(void);
Nat16 ScanModeA(int medium, int installationmode, Nat16 ScanPreference);
Nat16 ScanModeB(int medium, int installationmode, Nat16 ScanPreference);
Nat16 ScanModeC(int medium, int installationmode, Nat16 ScanPreference);

int GiveDefaultCharacterTable(void);
int ConvertToSTAudioType(int stmType);
int ConvertToSTVideoType(int stmType);
#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif
//#define nvmapps_NumberOfEntries 0

/*intf: IPlfApiTuning*/

#ifndef __cplusplus

#endif


/* Interfaces from IHsvChanlibPosixLight.id */

#ifndef __cplusplus 

#endif

#ifndef __cplusplus    

#endif	

#ifndef __cplusplus 

#endif
/* Interfaces from IHsvProgramDataControl3.id */

void module__init(void){
	memcpy((void*)FinlandSymVals,(void*)s__FinlandSymVals,sizeof(FinlandSymVals));
	memcpy((void*)FinlandFullScanSymVals,(void*)s__FinlandFullScanSymVals,sizeof(FinlandFullScanSymVals));
	memcpy((void*)NetherlandsSymVals,(void*)s__NetherlandsSymVals,sizeof(NetherlandsSymVals));
	memcpy((void*)NetherlandsZiggoSymVals,(void*)s__NetherlandsZiggoSymVals,sizeof(NetherlandsZiggoSymVals));
	memcpy((void*)GermanySymVals,(void*)s__GermanySymVals,sizeof(GermanySymVals));
	memcpy((void*)AustriaSwtzSymVals,(void*)s__AustriaSwtzSymVals,sizeof(AustriaSwtzSymVals));
	memcpy((void*)SwedenSymVals,(void*)s__SwedenSymVals,sizeof(SwedenSymVals));
	memcpy((void*)SwedenFullScanSymVals,(void*)s__SwedenFullScanSymVals,sizeof(SwedenFullScanSymVals));
	memcpy((void*)NorwaySymVals,(void*)s__NorwaySymVals,sizeof(NorwaySymVals));
	memcpy((void*)NorwayFullScanSymVals,(void*)s__NorwayFullScanSymVals,sizeof(NorwayFullScanSymVals));
	memcpy((void*)DenmarkSymVals,(void*)s__DenmarkSymVals,sizeof(DenmarkSymVals));
	memcpy((void*)DenmarkFullScanSymVals,(void*)s__DenmarkFullScanSymVals,sizeof(DenmarkFullScanSymVals));
	memcpy((void*)ChinaSymVals,(void*)s__ChinaSymVals,sizeof(ChinaSymVals));
	memcpy((void*)DvbcLightSymVals,(void*)s__DvbcLightSymVals,sizeof(DvbcLightSymVals));
	memcpy((void*)HPRSymVals,(void*)s__HPRSymVals,sizeof(HPRSymVals));
	memcpy((void*)IrelandSymVals,(void*)s__IrelandSymVals,sizeof(IrelandSymVals));
	memcpy((void*)UkraineSymVals,(void*)s__UkraineSymVals,sizeof(UkraineSymVals));
	memcpy((void*)FinlandFreqVals,(void*)s__FinlandFreqVals,sizeof(FinlandFreqVals));
	memcpy((void*)RomaniaFreqVals,(void*)s__RomaniaFreqVals,sizeof(RomaniaFreqVals));
	memcpy((void*)GermanyFreqVals,(void*)s__GermanyFreqVals,sizeof(GermanyFreqVals));
	memcpy((void*)BulgariaBlizooFreqVals,(void*)s__BulgariaBlizooFreqVals,sizeof(BulgariaBlizooFreqVals));
	memcpy((void*)SwedenFreqVals,(void*)s__SwedenFreqVals,sizeof(SwedenFreqVals));
	memcpy((void*)NorwayFreqVals,(void*)s__NorwayFreqVals,sizeof(NorwayFreqVals));
	memcpy((void*)DenmarkFreqVals,(void*)s__DenmarkFreqVals,sizeof(DenmarkFreqVals));
	memcpy((void*)ChinaFreqVals,(void*)s__ChinaFreqVals,sizeof(ChinaFreqVals));
	memcpy((void*)UkraineFreqVals,(void*)s__UkraineFreqVals,sizeof(UkraineFreqVals));
	memcpy((void*)FinlandModVals,(void*)s__FinlandModVals,sizeof(FinlandModVals));
	memcpy((void*)NetherlandsModVals,(void*)s__NetherlandsModVals,sizeof(NetherlandsModVals));
	memcpy((void*)GermanyModVals,(void*)s__GermanyModVals,sizeof(GermanyModVals));
	memcpy((void*)AustriaSwtzModVals,(void*)s__AustriaSwtzModVals,sizeof(AustriaSwtzModVals));
	memcpy((void*)SwedenModVals,(void*)s__SwedenModVals,sizeof(SwedenModVals));
	memcpy((void*)NorwayModVals,(void*)s__NorwayModVals,sizeof(NorwayModVals));
	memcpy((void*)DenmarkModVals,(void*)s__DenmarkModVals,sizeof(DenmarkModVals));
	memcpy((void*)DvbcLightModVals,(void*)s__DvbcLightModVals,sizeof(DvbcLightModVals));
	memcpy((void*)HPRIModVals,(void*)s__HPRIModVals,sizeof(HPRIModVals));
	memcpy((void*)BelgiumSymVals,(void*)s__BelgiumSymVals,sizeof(BelgiumSymVals));
	memcpy((void*)BelgiumTelenetSymVals,(void*)s__BelgiumTelenetSymVals,sizeof(BelgiumTelenetSymVals));
	memcpy((void*)BelgiumModVals,(void*)s__BelgiumModVals,sizeof(BelgiumModVals));
	memcpy((void*)RomaniaAutomaticFreqModVals,(void*)s__RomaniaAutomaticFreqModVals,sizeof(RomaniaAutomaticFreqModVals));
	memcpy((void*)DenMarkYouSeeFreqVals,(void*)s__DenMarkYouSeeFreqVals,sizeof(DenMarkYouSeeFreqVals));
	memcpy((void*)CanalDigitalFreqVals,(void*)s__CanalDigitalFreqVals,sizeof(CanalDigitalFreqVals));
	memcpy((void*)SloveniaTelemachFreqVals,(void*)s__SloveniaTelemachFreqVals,sizeof(SloveniaTelemachFreqVals));
	
	InsMedium	=	s__InsMedium;
	InsInstallMedium	=	s__InsInstallMedium;
	InsCountry	=	s__InsCountry;
	InsInstallCountry	=	s__InsInstallCountry;
	InsRfSetting	=	s__InsRfSetting;
	PbsMode	=	s__PbsMode;
	ChServIDForUpdate = 0;
	ChUniIDForUpdate = 0;
	UpdatedChannelName[0] = 0;
	UpdatedONID = 0;
	UpdatedTsID = 0;
	IsDVBT2Scan = 0;
	FocusedPlpId = -1;
	IsExtractScanResult = 0;
	UpdatedSymbolRate = 0;
	AudioPid = s__AudioPid;
	VideoPid= s__VideoPid;
	PcrPid= s__PcrPid;
	AudioStreamType = s__AudioStreamType;
	VideoStreamType = s__VideoStreamType;
	itvdiv_On	=	s__itvdiv_On;
	itvdiv_CountryDependent	=	s__itvdiv_CountryDependent;
	itvdiv_Off	=	s__itvdiv_Off;
	itvdiv_AtscDvbSupported	=	s__itvdiv_AtscDvbSupported;
	itvdiv_DVBTInstallationSupported	=	s__itvdiv_DVBTInstallationSupported;
	itvdiv_DvbtLightSupported	=	s__itvdiv_DvbtLightSupported;
	IsForceCharacterCode              = s__IsForceCharacterCode;
	itvdiv_DVBCInstallationSupported	=	s__itvdiv_DVBCInstallationSupported;
	itvdiv_DvbcLightSupported	=	s__itvdiv_DvbcLightSupported;
	itvdiv_EnableDolbyFeaturing	=	s__itvdiv_EnableDolbyFeaturing;
	itvdiv_ProdRegion	=	s__itvdiv_ProdRegion;
	itvdiv_Australia	=	s__itvdiv_Australia;
	amdivlib_brdcstdiv2_Off	=	s__amdivlib_brdcstdiv2_Off;
	amdivlib_brdcstdiv_Off	=	s__amdivlib_brdcstdiv_Off;
	amdivlib_brdcstdiv2_On	=	s__amdivlib_brdcstdiv2_On;
	amdivlib_brdcstdiv2_DvbTandCSupported	=	s__amdivlib_brdcstdiv2_DvbTandCSupported;
	amdivlib_brdcstdiv_DvbT2InstallationSupported	=	s__amdivlib_brdcstdiv_DvbT2InstallationSupported;
	InsEnableDVBC = true;
	InsEnableDVBT = true;
	InsEnableAnalog = true;

#ifndef __cplusplus

	errlib__TraceGlobalRulesAge	=	s__errlib__TraceGlobalRulesAge;
	errlib__TraceSymbolLegacyPrintf	=	s__errlib__TraceSymbolLegacyPrintf;
	nopapi	=	s__nopapi;
#endif


/*intf: eurdiv*/

/*intf: eurdiv*/

/* retval is a bit vector with bit positions according to enum divBitPos */

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif

#ifndef __cplusplus

#endif
//#define nvmapps_NumberOfEntries 0

/*intf: IPlfApiTuning*/

#ifndef __cplusplus

#endif


/* Interfaces from IHsvChanlibPosixLight.id */

#ifndef __cplusplus 

#endif

#ifndef __cplusplus    

#endif	

#ifndef __cplusplus 

#endif
/* Interfaces from IHsvProgramDataControl3.id */

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef PRESCAN_MODE
#undef PRESCAN_MODE
#endif //PRESCAN_MODE
#ifdef FINLAND_MAX_SYM_VALS
#undef FINLAND_MAX_SYM_VALS
#endif //FINLAND_MAX_SYM_VALS
#ifdef NETHERLANDS_MAX_SYM_VALS
#undef NETHERLANDS_MAX_SYM_VALS
#endif //NETHERLANDS_MAX_SYM_VALS
#ifdef NETHERLANDS_ZIGGO_MAX_SYM_VALS
#undef NETHERLANDS_ZIGGO_MAX_SYM_VALS
#endif //NETHERLANDS_ZIGGO_MAX_SYM_VALS
#ifdef AUSTRIA_SWTZ_MAX_SYM_VALS
#undef AUSTRIA_SWTZ_MAX_SYM_VALS
#endif //AUSTRIA_SWTZ_MAX_SYM_VALS
#ifdef GERMANY_MAX_SYM_VALS
#undef GERMANY_MAX_SYM_VALS
#endif //GERMANY_MAX_SYM_VALS
#ifdef SWEDEN_MAX_SYM_VALS
#undef SWEDEN_MAX_SYM_VALS
#endif //SWEDEN_MAX_SYM_VALS
#ifdef NORWAY_MAX_SYM_VALS
#undef NORWAY_MAX_SYM_VALS
#endif //NORWAY_MAX_SYM_VALS
#ifdef DENMARK_MAX_SYM_VALS
#undef DENMARK_MAX_SYM_VALS
#endif //DENMARK_MAX_SYM_VALS
#ifdef CHINA_MAX_SYM_VALS
#undef CHINA_MAX_SYM_VALS
#endif //CHINA_MAX_SYM_VALS
#ifdef DVBC_LIGHT_MAX_SYM_VALS
#undef DVBC_LIGHT_MAX_SYM_VALS
#endif //DVBC_LIGHT_MAX_SYM_VALS
#ifdef HPR_MAX_SYM_VALS
#undef HPR_MAX_SYM_VALS
#endif //HPR_MAX_SYM_VALS
#ifdef IRELAND_MAX_SYM_VALS
#undef IRELAND_MAX_SYM_VALS
#endif //IRELAND_MAX_SYM_VALS
#ifdef UKRAINE_MAX_SYM_VALS
#undef UKRAINE_MAX_SYM_VALS
#endif //UKRAINE_MAX_SYM_VALS
#ifdef FINLAND_MAX_FREQ_VALS
#undef FINLAND_MAX_FREQ_VALS
#endif //FINLAND_MAX_FREQ_VALS
#ifdef GERMANY_MAX_FREQ_VALS
#undef GERMANY_MAX_FREQ_VALS
#endif //GERMANY_MAX_FREQ_VALS
#ifdef BULGARIA_BLIZOO_FREQ_VALS
#undef BULGARIA_BLIZOO_FREQ_VALS
#endif //BULGARIA_BLIZOO_FREQ_VALS
#ifdef SWEDEN_MAX_FREQ_VALS
#undef SWEDEN_MAX_FREQ_VALS
#endif //SWEDEN_MAX_FREQ_VALS
#ifdef NORWAY_MAX_FREQ_VALS
#undef NORWAY_MAX_FREQ_VALS
#endif //NORWAY_MAX_FREQ_VALS
#ifdef DENMARK_MAX_FREQ_VALS
#undef DENMARK_MAX_FREQ_VALS
#endif //DENMARK_MAX_FREQ_VALS
#ifdef CHINA_MAX_FREQ_VALS
#undef CHINA_MAX_FREQ_VALS
#endif //CHINA_MAX_FREQ_VALS
#ifdef UKRAINE_MAX_FREQ_VALS
#undef UKRAINE_MAX_FREQ_VALS
#endif //UKRAINE_MAX_FREQ_VALS
#ifdef MAX_MOD_VALS
#undef MAX_MOD_VALS
#endif //MAX_MOD_VALS
#ifdef NETHERLANDS_MAX_MOD_VALS
#undef NETHERLANDS_MAX_MOD_VALS
#endif //NETHERLANDS_MAX_MOD_VALS
#ifdef AUSTRIA_SWTZ_MAX_MOD_VALS
#undef AUSTRIA_SWTZ_MAX_MOD_VALS
#endif //AUSTRIA_SWTZ_MAX_MOD_VALS
#ifdef GERMANY_MAX_MOD_VALS
#undef GERMANY_MAX_MOD_VALS
#endif //GERMANY_MAX_MOD_VALS
#ifdef DVBC_LIGHT_MAX_MOD_VALS
#undef DVBC_LIGHT_MAX_MOD_VALS
#endif //DVBC_LIGHT_MAX_MOD_VALS
#ifdef HPRI_MAX_MOD_VALS
#undef HPRI_MAX_MOD_VALS
#endif //HPRI_MAX_MOD_VALS
#ifdef SHARED_WIDGET_DIR_PATH_SIZE
#undef SHARED_WIDGET_DIR_PATH_SIZE
#endif //SHARED_WIDGET_DIR_PATH_SIZE
#ifdef SHARED_DIR_PATH_SIZE
#undef SHARED_DIR_PATH_SIZE
#endif //SHARED_DIR_PATH_SIZE
#ifdef SWEDEN_FULLSCAN_MAX_SYM_VALS
#undef SWEDEN_FULLSCAN_MAX_SYM_VALS
#endif //SWEDEN_FULLSCAN_MAX_SYM_VALS
#ifdef NORWAY_FULLSCAN_MAX_SYM_VALS
#undef NORWAY_FULLSCAN_MAX_SYM_VALS
#endif //NORWAY_FULLSCAN_MAX_SYM_VALS
#ifdef DENMARK_FULLSCAN_MAX_SYM_VALS
#undef DENMARK_FULLSCAN_MAX_SYM_VALS
#endif //DENMARK_FULLSCAN_MAX_SYM_VALS
#ifdef FINLAND_FULLSCAN_MAX_SYM_VALS
#undef FINLAND_FULLSCAN_MAX_SYM_VALS
#endif //FINLAND_FULLSCAN_MAX_SYM_VALS
#endif //LOCAL_UNDEFINES
