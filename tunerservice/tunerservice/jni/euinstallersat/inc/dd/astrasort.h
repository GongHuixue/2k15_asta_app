/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: astrasort.h %
 *       %version:  TVG_2 %
 * %date_modified:  %
 *    %derived_by:  shivam % 
 */

#define INVALIDATE(x)     ((x) |= 0x8000)
#define 	INVALID_INDEX		(-1)
#define MAX_NUM_LCN_ENTRY			8
#define INVALID_LCN			(0xC000)
#define	INVALID_PRESET		(0XFFFF)
#define	SAT_INFO_TABLE		(pgdb_GetCurrentTable() | pgdbconst_SatInfo)
#define	SERVICE_TABLE		(pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define	PRESET_TABLE		(pgdb_GetCurrentTable() | pgdbconst_Preset)
#define STEP_SIZE (100)
/*RMCR-2423*/
#define RADIO_PRESET_OFFSET 						(4000)
#define TV_PRESET_OFFSET 							(3000)
#define ADD_ENTRY                                   ( 0 )
#define UPDATE_ENTRY                                ( 1 )
#define MAX_RADIO_PRESET							(5000)
#define MIXED_PRESET_OFFSET							(5000)
#define MAX_PRESET_NUMBER							(9999)
#define MinValidLCNValue    (1)
#define MaxValidLCNValue    (0x2000)
#define VALID_LCN_RANGE(x)  (((x) <= MaxValidLCNValue) && (MinValidLCNValue <= (x)))
#define CURRENT_PRESET_VALID(preset, svcType)       ( !mIsCurrentPresetInvalid(preset, svcType) )   
#define IS_RADIO_SERVICE(x)                                         ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )
//#define PRESET_NOT_ALLOCATED(svcdat)                ( (svcdat).PresetNumber == INVALID_PRESET )
#define PRESET_NOT_ALLOCATED(preset)                (preset == INVALID_PRESET )
#define REVALIDATE(x)     ((x) &= 0x7FFF)  
#define ASSIGN_PRESET_NUMBER(x)                                     (IS_RADIO_SERVICE(svcdat.ServiceType) ? ((x) + (MAX_LCN_VALUE)):(x))
#define MAX_LCN_VALUE                                               (MaxValidLCNValue)
#define AUTO_MODE													(insstate_InstallationServiceScan)
#define GETCURRENTINDEX(x)                                          (IS_RADIO_SERVICE(x) ? (mCurrentRadioIndex) : (mCurrentPresetIndex))
#define ASSIGN_PRESET_FROM_SVC(presetdat, svcdat)((presetdat.OriginalNetworkId = svcdat.OriginalNetworkId),\
                                                  (presetdat.ServiceId = svcdat.ServiceId),\
                                                  (presetdat.Tsid = svcdat.Tsid),\
						                          (presetdat.StreamPriority = svcdat.StreamPriority),\
                                                  (presetdat.Frequency = svcdat.Frequency))
#define ASSIGN_DEFAULTCOOKIES(svcdat)			( ((svcdat).CesvcCookie  = CESVCCOOKIE),\
												  ((svcdat).AppsCookie  = APPSCOOKIE),\
												  ((svcdat).TxtCookie   = TXTCOOKIE) )

#define		PTC_TABLE							    (pgdbconst_Satellite | pgdbconst_DigitalTS)
#define		SERVICE_TABLE							(pgdbconst_Satellite | pgdbconst_DigitalService)
#define		PRESET_TABLE							(pgdbconst_Satellite | pgdbconst_Preset)
#define 	BACKGROUND_MODE             			(rins_InstallationModeBackground) 




