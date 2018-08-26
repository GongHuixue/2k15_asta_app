/*
 *  Copyright(C) 2002 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.      
 *                                                                  
 *############################################################
 */
/*!
 *     \file          hsvziggo_mDataAcq.h
 *
 *     \brief         -
 *
 */
/*----------------------------------------------------------*
 *
 *     %version:       TVG_FusionPPV2_9 %
 *     %date_created:  Fri Jun 08 10:59:55 2012 %
 *     %date_modified: Tue Oct 28 19:17:58 2008 %
 *     %derived_by:    adarshlr %
 *
 *
 *############################################################
 */

/* include dependencies */
#include	"_hsvziggo_mDataAcq.h"

#ifndef __cplusplus
#include	"../hsvdvbcins/hsvdvbcins.h"
#else
#include	"hsvdvbcins.h"
#endif
#include	<string.h>

/* Macros */
#define		PTC_TABLE							    (pgdb_GetCurrentTable() | pgdbconst_DigitalTS)
#define		SERVICE_TABLE							(pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define		PRESET_TABLE							(pgdb_GetCurrentTable() | pgdbconst_Preset)
#define		FREQMAP_TABLE							(pgdb_GetCurrentTable() | pgdbconst_FrequencyMapTable)
#define		CURRENT_ONID							(sort_GetOriginalNetworkId(sysset_GetSystemCountry()))

#define		GETSERVICETYPE(servicetype)				( (servicetype == AppApiRadioService)? HsvRadio: HsvOnePart )

#define		CONVERT_TO_PGDAT_OUI(oui)				((oui == 0x0000903e)? (HsvOUI_Philips) : (HsvOUI_Last))
#define		MAX_PGDAT_SERVICE_TYPES					(17)
#define		INVALID_NITVERSION						(255)
#define		BACKGROUND_INSTALL						((CURRENT_MODE == BACKGROUND_MODE) || (CURRENT_MODE == rins_InstallationModeNone))
#define		PID_CACHING_ENABLED						mpldiv_PidCachingEnabled
#define		GETHSVSPID(prop, tableid)				(mHsvDVBPIDList[prop][tableid])
#define		GETDBTABLEID(prop, tableid)				(mHsvDVBSortedTableList[prop][tableid])
#define		ACTUAL_TABLE							(0)
#define		OTHER_TABLE								(1)

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
#define		IS_RADIO_SERVICE(svcType)                ((svcType == AppApiRadioService) || (svcType == AppApiAdvCodecRadioService) )
/* Local Structures and enums */

typedef enum
{
	evStep0 = 0,
	evStep1,
	evStep2,
	evStepComplete,
}SvcSteps;



typedef struct
{
    Bool EnableBackground;
    Bool SemiSbyInstallRequired;
	Bool InProgress;
}t_DVBCSemiSby;



typedef enum
{
	EvStart = 0
}t_AcqEvents;

typedef enum
{
    Onid = 0,
    Tsid,
    VerNo,
    SpidService,
	LCNv1,
	LCNv2,
	HDSLCN,
    MAX_PROPERTY_ID
}eDVBProperties;


