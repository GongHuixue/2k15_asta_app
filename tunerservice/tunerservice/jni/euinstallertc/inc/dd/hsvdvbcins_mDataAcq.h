
/* include dependencies */
#include	"_hsvdvbcins_mDataAcq.h"

#include	"hsvdvbcins.h"

/* Macros */
#define		PTC_TABLE							    (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define		SERVICE_TABLE							(pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define		PRESET_TABLE							(pgdb_GetCurrentTable() | pgdbconst_Preset)
#define		FREQMAP_TABLE							(pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)

#define		TEMP_PTC_TABLE							(pgdb_GetCurrentTable() | pgdbconst_CurrentDigitalTS)
#define		TEMP_SERVICE_TABLE						(pgdb_GetCurrentTable() | pgdbconst_CurrentDigitalService)
													
#define		BACKGROUND_TIMEOUT						(30000)
#define		CURRENT_ONID							(sort_GetOriginalNetworkId(sysset_GetSystemCountry()))

#define		GETSERVICETYPE(servicetype)				( ((servicetype == AppApiRadioService) || (servicetype == AppApiAdvCodecRadioService)) ? HsvRadio: HsvOnePart )

#define		CONVERT_TO_PGDAT_OUI(oui)				((oui == 0x0000903e)? (HsvOUI_Philips) : (HsvOUI_Last))
#define		MAX_PGDAT_SERVICE_TYPES					(17)
#define		INVALID_NITVERSION						(255)
#define		BACKGROUND_INSTALL						((CURRENT_MODE == BACKGROUND_MODE) || (CURRENT_MODE == rins_InstallationModeNone))
#define		PID_CACHING_ENABLED						mpldiv_PidCachingEnabled
#define		GETHSVSPID(prop, tableid)				(mHsvDVBPIDList[prop][tableid])
#define		GETDBTABLEID(prop, tableid)				(mHsvDVBSortedTableList[prop][tableid])
#define		ACTUAL_TABLE							(0)
#define		OTHER_TABLE								(1)

#define 	IS_SYSTEM_NETWORKOPERATOR_RCSRDS		((sysset_GetSystemCountry() == cids_CountryRomania)&&(rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkOperator) == rins_RCSRDS)? true : false)
#define 	RCSRDS_MinValidLCNValue    				(1)
#define 	RCSRDS_MaxValidLCNValue    				(1999)
#define 	VALID_LCN_RANGE_RCSRDS(x)				(((x) <= RCSRDS_MaxValidLCNValue) && ( RCSRDS_MinValidLCNValue <= (x)))

#define		ZEROLCN									0
#define     TV_SERVICE								(TelevisionService)
#define     RADIO_SERVICE							(RadioService)
#define     TELETEXT_SERVICE						(TeletextService)
#define     NVOD_REFERENCE_SERVICE					(NVODReferenceService)
#define     NVOD_TIMESHIFTED_SERVICE				(NVODTimeShiftedService)
#define     MOSAIC_SERVICE							(MosaicService)
#define     DATABROADCAST_SERVICE					(DatabroadcastService)
#define     DVBMHP_SERVICE							(DVBMHPService)

#define     INVALID_VERSION							(-1)
#define     INVALID_TS_VERSION						(0xFF)
#define     VERSION1								(1)
#define     VERSION2								(2)	
#define     HDSLCNVERSION							(3)
#define     LCN_VERSION2_PRESENT(NoOfRecs)			( eurdiv_SupportLCNVersion2(rins_GetMedium()) && (NoOfRecs > 0) )

#define		IS_VALID_ONID							 ( (mDVBCData.Onid >= 0xFF00)? FALSE: TRUE )		
#define		IS_VALID_NID							 ( (mDVBCData.NetworkId >= 0xFF01)? FALSE: TRUE )
#define		IS_VALID_TSID							 ( TRUE ) /* Not using yet in field.. might come soon */
													
#define		IS_VALID_TS								 ( IS_VALID_ONID && IS_VALID_NID && IS_VALID_TSID )
#define		LCNS_REQUIRED							 (eurdiv_ParseLCN(rins_GetMedium(), rins_GetInstallationMode()))
#define		GET_LCN									 (1)
#define		ACQUIRE_LCNS							 (2)

#define     ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	 { \
														svcdat1.OriginalNetworkId	= svcdat2.OriginalNetworkId; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
														svcdat1.Frequency			= svcdat2.Frequency; \
														svcdat1.StreamPriority		= svcdat2.StreamPriority; \
													 }
#define		IS_NOT_USER_INSTALLED(tsdata)			 ( (tsdata).UserInstalled == FALSE )
#define     HD_SIMULCAST_LINKAGE(svcdat)             (  (svcdat.HDSimulcastRepOnId != 0xFFFF) && \
                                                        (svcdat.HDSimulcastRepTsId != 0xFFFF) && \
                                                        (svcdat.HDSimulcastRepSvcId != 0xFFFF) )?0x01:0x00
/* Local Structures and enums */


