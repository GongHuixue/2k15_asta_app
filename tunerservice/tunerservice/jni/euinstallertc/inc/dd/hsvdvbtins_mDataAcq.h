#include <stdio.h>
#include <string.h>


#define     CURRENT_MODE                             ( rins_GetInstallationMode() ) 
#define     AUTO_MODE                                ( rins_InstallationModeAutomatic )
#define     UPDATE_MODE                              ( rins_InstallationModeUpdate )
#define     MANUAL_MODE                              ( rins_InstallationModeWeakSignal )
#define     BACKGROUND_MODE                          ( rins_InstallationModeBackground )
#define     AUTO_INSTALL                             ( (CURRENT_MODE) == (AUTO_MODE) )
#define     UPDATE_INSTALL                           ( (CURRENT_MODE) == (UPDATE_MODE) )
#define     MANUAL_INSTALL                           ( (CURRENT_MODE) == (MANUAL_MODE) )
#define     BACKGROUND_INSTALL                       ( (CURRENT_MODE) == (BACKGROUND_MODE) )


#define     PTC_TABLE                                (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define     SERVICE_TABLE                            (pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define     PRESET_TABLE                             (pgdb_GetCurrentTable() | pgdbconst_Preset)
#define     ANTENNA_FREQ                             (pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)

#define     TEMP_PTC_TABLE                           (pgdb_GetCurrentTable() | pgdbconst_CurrentDigitalTS)
#define     TEMP_SERVICE_TABLE                       (pgdb_GetCurrentTable() | pgdbconst_CurrentDigitalService)                                         
#define     GETSERVICETYPE(type)                     ( ((type == AppApiRadioService)||(type ==AppApiAdvCodecRadioService ))? HsvRadio : HsvOnePart )                                                   
#define     PID_CACHING_ENABLED                      ( mpldiv_PidCachingEnabled )
#define     ZEROLCN                                  ( 0 )
#define     SERVICE_NOT_VISIBLE                      ( FALSE )
#define     SERVICE_NOT_SELECTABLE                   ( FALSE )
#define     DELTASSI                                 ( eurdiv_GetDeltaSSI() )
#define     DELTASQI                                 ( eurdiv_GetDeltaSQI() )
#define     IS_VALID_ONID                            ( (DigInsStatus.Onwid >= 0xFF00)? FALSE: TRUE )        
#define     IS_VALID_NID                             ( (DigInsStatus.NetworkId >= 0xFF01)? FALSE: TRUE )
#define     IS_VALID_TSID                            ( TRUE ) /* Not using yet in field.. might come soon */
                                                    
#define     IS_VALID_TS                              ( IS_VALID_ONID && IS_VALID_NID && IS_VALID_TSID )
#define     IS_NOT_USER_INSTALLED(tsdata)            ( (tsdata).UserInstalled == FALSE )
#define     ADD_ENTRY                                ( 0 )
#define     UPDATE_ENTRY                             ( 1 )

#define     TV_SERVICE                               ( TelevisionService )
#define     RADIO_SERVICE                            ( RadioService )
#define     TELETEXT_SERVICE                         ( TeletextService )
#define     NVOD_REFERENCE_SERVICE                   ( NVODReferenceService )
#define     NVOD_TIMESHIFTED_SERVICE                 ( NVODTimeShiftedService )
#define     MOSAIC_SERVICE                           ( MosaicService )
#define     DATABROADCAST_SERVICE                    ( DatabroadcastService )
#define     DVBMHP_SERVICE                           ( DVBMHPService )
#define     LCN_VERSION2_PRESENT(NoOfRecs)           ( eurdiv_SupportLCNVersion2(rins_GetMedium()) && (NoOfRecs > 0) )
#define     ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)     { \
                                                        svcdat1.OriginalNetworkId   = svcdat2.OriginalNetworkId; \
                                                        svcdat1.ServiceId           = svcdat2.ServiceId; \
                                                        svcdat1.Frequency           = svcdat2.Frequency; \
                                                        svcdat1.StreamPriority      = svcdat2.StreamPriority; \
                                                     }
#define     HD_SIMULCAST_LINKAGE(svcdat)             (  (svcdat.HDSimulcastRepOnId != 0xFFFF) && \
                                                        (svcdat.HDSimulcastRepTsId != 0xFFFF) && \
                                                        (svcdat.HDSimulcastRepSvcId != 0xFFFF) )?0x01:0x00


/* P, S & T population into SERVICE_TABLE */
#define VALID_PRIMARY_REGION(svcdat)    ( ((svcdat).PrimaryRegion > 0) && ((svcdat).PrimaryRegion <= 0xFF) )
#define VALID_SECONDARY_REGION(svcdat)  ( ((svcdat).SecondaryRegion > 0) && ((svcdat).SecondaryRegion <= 0xFF) )
#define VALID_TERTIARY_REGION(svcdat)   ( ((svcdat).TertiaryRegion > 0) && ((svcdat).TertiaryRegion <= 0xFFFF) )
#define VALID_REGIONS(svcdat)           ( VALID_PRIMARY_REGION(svcdat) && VALID_SECONDARY_REGION(svcdat) && VALID_TERTIARY_REGION(svcdat) )

#define NUM_PRIMARY_REGIONS             ( mRegionsData.NoOfRegions )
#define NUM_SECONDARY_REGIONS(i)        ( mRegionsData.Primary[i].NoOfRegions )
#define NUM_TERTIARY_REGIONS(i, j)      ( mRegionsData.Primary[i].Secondary[j].NoOfRegions )

#define PRIMARY_REGION_LASTINDEX        ( NUM_PRIMARY_REGIONS - 1 )
#define SECONDARY_REGION_LASTINDEX(i)   ( NUM_SECONDARY_REGIONS(i) - 1 )
#define TERTIARY_REGION_LASTINDEX(i, j) ( NUM_TERTIARY_REGIONS(i, j) - 1 )
#define PRIMARY_REGION_CODE(i)          ( mRegionsData.Primary[i].RegionCode )
#define SECONDARY_REGION_CODE(i, j)     ( mRegionsData.Primary[i].Secondary[j].RegionCode )
#define TERTIARY_REGION_CODE(i, j, k)   ( mRegionsData.Primary[i].Secondary[j].Tertiary[k].RegionCode )
#define PRIMARY_REGION_NAME(i)          ( mRegionsData.Primary[i].RegionName )
#define SECONDARY_REGION_NAME(i, j)     ( mRegionsData.Primary[i].Secondary[j].RegionName )
#define TERTIARY_REGION_NAME(i, j, k)   ( mRegionsData.Primary[i].Secondary[j].Tertiary[k].RegionName )

#define AUTO_MODE                       ( rins_InstallationModeAutomatic )
#define CURRENT_MODE                    ( rins_GetInstallationMode() ) 
#define ZEROLCN                         ( 0 )
#define SRVCNOTVISIBLE                  ( FALSE )
#define SRVCNOTSELECTABLE               ( FALSE )
#define INVALID_INDEX                   ( -1 )


/*****   static functions   *****/
static      void    mPumpHandler(int value, Nat32 param);

static      Bool    mGetTSMetaData( void );
static      Bool    mLCNParsingRequired(Nat16 OnId);
static      Bool    mInstallMux(HsvInstallationPTC *ptc);
static      void    mAddToTSTable(HsvInstallationPTC ptc);
static      int     mConvertToDVBServiceType(int servicetype);
static      void    mUpdatePtcTableRecords(int evCurrentStep);
static      void    mAddToFreqMapTable(HsvInstallationPTC ptc);
static      int     mConvertToPgDataServiceType  (int servicetype);
static      void    mUpdateServiceTableRecords(int evCurrentStep);
static inline void  mLCNOverRuling(HsvPgdatDigServiceData *svcdat);
static      void    mDeleteServiceNotInTransmission(int evCurrentStep);
static      void    mCopyString (Nat16 *dest, Nat16 *src, int maxchars);
static      void    mDeleteServicesOfSameMux(Nat16 Frequency, Nat32 StreamPriority);
static      void    mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat);
static      Bool    mCompareMultiplex(HsvPgdatDigTSData tsdata, HsvInstallationPTC *ptc);
static      Bool    mDuplicateEntry(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData *pgdat2);
static      void    mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp);
static      Bool    mCheckServiceForInstall(HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
static      void    mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp);
static      void    mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service);
static      void    mUpdateService (HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
static      void    mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
static      Bool    mLcnVersion2Data(HsvPgdatDigServiceData *psvcdat);
static      void    mAssignSvcHDSimulcastLinkageParams( HsvPgdatDigServiceData *service );
static      void    mDeleteHDSimulcastSDServices (void);
static      Bool    mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat);

/*****   static variables   *****/

typedef enum
{
    evStep0 = 0,
    evStep1,
    evStep2,
    evStepComplete,
}SvcSteps;


typedef struct DigitalInstallationStatus
{
    Nat16                   Onwid;
    Nat16                   Tsid;
    Nat16                   NetworkId;
    Nat8                    TsVersionNumber;
}TypeDigitalInstallationStatus;

static      TypeDigitalInstallationStatus    DigInsStatus;
static      Pump                             mPump;

static int mDigitalChannelsFound;
/*****   Static functions   *****/

/* Naresh: include operator specific modules */
//#include    "operators/HsvDbookOperators.c"
/*
#include    "operators/HsvDvbGeneric.c"
#include    "operators/HsvRiksTvOperator.c"*/


static int mConvertToDVBServiceType(int servicetype)
{
    int retval = servicetype;
    switch(servicetype)
    {

        case AppApiTelevisionService:     
            retval  =   TV_SERVICE;
            break;
        case AppApiRadioService:        
            retval  =   RADIO_SERVICE;
            break;
        case AppApiTeletextService:         
            retval  =   TELETEXT_SERVICE;
            break;
        case AppApiNVODReferenceService:         
            retval  =   NVOD_REFERENCE_SERVICE;
            break;
        case AppApiNVODTimeshiftedService:         
            retval  =   NVOD_TIMESHIFTED_SERVICE;
            break;
        case AppApiMosaicService:        
            retval  =   MOSAIC_SERVICE;
            break;
        case AppApiDatabroadcastService:        
            retval  =   DATABROADCAST_SERVICE;
            break;
        case AppApiDVBMHPService:        
            retval  =   DVBMHP_SERVICE;
            break;
        case AppApiMPEG2HDService:        
            retval  =   MPEG2HDService;
            break;
        case AppApiAdvCodecSDTelevisionService:        
            retval  =   AdvCodecSDTelevisionService;
            break;
        case AppApiAdvCodecSDNVODTimeShiftedService:        
            retval  =   AdvCodecSDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecSDNVODReferenceService:        
            retval  =   AdvCodecSDNVODReferenceService;
            break;
        case AppApiAdvCodecHDTelevisionService:        
            retval  =   AdvCodecHDTelevisionService;
            break;
        case AppApiAdvCodecHDNVODTimeShiftedService:        
            retval  =   AdvCodecHDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecHDNVODReferenceService:        
            retval  =   AdvCodecHDNVODReferenceService;
            break;      
		case AppApi3DHDDigitalService:
			retval  =   HD3DDigitalService;
			break;
        default:
            break;        

    }
    return retval;
}

