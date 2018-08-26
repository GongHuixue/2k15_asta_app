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
 *          %name: polsort.h %
 *       %version:  TVG_4 %
 * %date_modified:  %
 *    %derived_by:  sreeds % 
 */

#define INVALIDATE(x)     ((x) |= 0x8000)
#define 	INVALID_INDEX		(-1)
#define	INVALID_PRESET		(0XFFFF)
#define	SAT_INFO_TABLE		(pgdb_GetCurrentTable() | pgdbconst_SatInfo)
#define	SERVICE_TABLE		(pgdb_GetCurrentTable() | pgdbconst_DigitalService)
#define	PRESET_TABLE		(pgdb_GetCurrentTable() | pgdbconst_Preset)
#define STEP_SIZE (100)
#define RADIO_PRESET_OFFSET 						(3000)
#define TV_PRESET_OFFSET 							(1000)
#define ADD_ENTRY                                   ( 0 )
#define UPDATE_ENTRY                                ( 1 )
#define MAX_RADIO_PRESET							(5000)
#define MIXED_PRESET_OFFSET							(5000)
#define MAX_PRESET_NUMBER							(9999)
#define MIN_VALID_LCN    (1)
#define MAX_VALID_LCN    (1000)
#define MIN_VALID_LCN_CYFRA   (0)
#define VALID_LCN_RANGE(x,package)  ((package == CYFROWY_POLSAT_PACKAGE_ID)?(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x))) : \
									(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN_CYFRA <= (x))))
#define CURRENT_PRESET_VALID(preset, svcType)       ( !mIsCurrentPresetInvalid(preset, svcType) )   
#define IS_RADIO_SERVICE(x)                                         ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )
#define PRESET_NOT_ALLOCATED(svcdat)                ( (svcdat).PresetNumber == INVALID_PRESET )
#define REVALIDATE(x)     ((x) &= 0x7FFF)  
#define ASSIGN_PRESET_NUMBER(x)                                     (IS_RADIO_SERVICE(svcdat.ServiceType) ? ((x) + (MAX_LCN_VALUE)):(x))
#define MAX_LCN_VALUE                                               (MAX_VALID_LCN)
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
													 						  


