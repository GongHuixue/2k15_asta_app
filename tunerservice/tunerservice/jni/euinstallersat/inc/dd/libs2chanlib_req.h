#ifdef __cplusplus
extern "C" {
#endif
/*
 * Copyright (c) 2010 Philips Consumer Lifestyle N.V., All rights reserved.
 * 
 * This  source code and any compilation or derivative thereof is the
 * proprietary information of Philips Consumer Lifestyle N.V. and is confidential 
 * in nature.
 * Under no circumstances is this software to be exposed to or placed
 * under an Open Source License of any type without the expressed
 * written permission of Philips Consumer Lifestyle N.V..
 */

#ifndef _libs2chanlibapp_mreq_h
#define _libs2chanlibapp_mreq_h

#ifndef PREFIX
#define PREFIX	libs2chanlibapp
#endif
#define MODIDX	1

#include "directfb.h"
#include "fusiondale.h"

#include "plf/plfApi/export/build/os/type/infraglobals/idl/infraglobals.dd"
#include "plf/plfApi/export/build/avg/type/DPlfApiFrontend.dd"
#include "app/appApi/export/build/type/channelLib/AppApiChannelLibTypes.dd"
#include "plf/plfApi/export/build/os/type/infranvm.dd"

extern NvmId libs2chanlib__nvmids_LastPresetOnePartNo( void );
extern void libs2chanlib__pgdatNxxx_OnChannelsRearranged( AppApiChannel channel1, AppApiChannel channel2 );
extern void libs2chanlib__esctrlNx_OnTeletextPidChanged( int Pid );
extern void libs2chanlib__pgdatNxxx_OnChannelMapSaveComplete( Bool Status );
extern int libs2chanlib__pgdatNxx_iPresent( void );
extern void libs2chanlib__ipgdatNxxx_OnChannelRemoved( AppApiChannel channel );
extern void libs2chanlib__pgdatNxxx_OnChannelAdded( AppApiChannel channel );
extern FResult libs2chanlib__nvmpa_LastError( void );
extern void libs2chanlib__nvmpa_SetBool( NvmId nvmid, Bool val, int subid );
extern int libs2chanlib__nvmpa_GetInt( NvmId nvmid, int subid );
extern NvmId libs2chanlib__nvmids_InstSettingsClosedCaptions( void );
extern NvmId libs2chanlib__nvmids_LstStatParentalRatingSex( void );
extern void libs2chanlib__nvmpa_SetInt32Ix( NvmId nvmid, int ix, Int32 val, int subid );
extern void libs2chanlib__pgdatNxx_OnChannelsSwapped( AppApiChannel channel1, AppApiChannel channel2 );
extern char libs2chanlib__nvmpa_GetChar( NvmId nvmid, int subid );
extern void libs2chanlib__ipgdatNxxx_OnChannelTableUpdateEnd( int Reset );
extern void libs2chanlib__esctrlNx_OnPCRPidStopped( void );
extern NvmId libs2chanlib__nvmids_LstStatDVBParentalRating( void );
extern void libs2chanlib__pgdatNxxx_OnChannelUpdated( AppApiChannel channel, int attribute );
extern void libs2chanlib__nvmpa_SetInt( NvmId nvmid, int val, int subid );
extern void libs2chanlib__pgdatNxx_OnChannelUpdated( AppApiChannel channel, int attribute );
extern NvmId libs2chanlib__nvmids_LastPresetType( void );
extern void libs2chanlib__pgdatN_OnChannelTableChanged( void );
extern void libs2chanlib__esctrlNx_OnPCRPidChanged( int Pid );
extern void libs2chanlib__pgctl3N_OnSubtitleSettingChanged( int SubtitleSetting );
extern void libs2chanlib__nvmpa_SetNat16( NvmId nvmid, int subid, Nat16 * value );
extern void libs2chanlib__pgctlN_OnDirectTuningStart( AppApiDirectTuningParameters Param );
extern void libs2chanlib__pgdatN_OnChannelUpdated( AppApiChannel channel, int attribute );
extern void libs2chanlib__esctrlNx_OnVideoPidChanged( int Pid );
extern NvmId libs2chanlib__nvmids_LastPresetTwoPartMajorNo( void );
extern void libs2chanlib__esctrlN_OnVideoPidChanged( int Pid );
extern void libs2chanlib__nvmpa_SetChar( NvmId nvmid, char val, int subid );
extern void libs2chanlib__pgctl3N_OnEvent( int event );
extern void libs2chanlib__nvmpa_SetIntIxIx( NvmId nvmid, int ix1, int ix2, int val, int subid );
extern NvmId libs2chanlib__nvmids_LstStatParentalRatingViolence( void );
extern void libs2chanlib__esctrlN_OnSubtitlePidStopped( void );
extern void libs2chanlib__pgdatNxxx_OnChannelTableReset( void );
extern int libs2chanlib__nvmpa_iPresent( void );
extern void libs2chanlib__pgctlN_OnDirectTuningEnd( AppApiDirectTuningParameters Param );
extern Int32 libs2chanlib__nvmpa_GetInt32Ix( NvmId nvmid, int ix, int subid );
extern NvmId libs2chanlib__nvmids_InstSettingsInstallMode( void );
extern void libs2chanlib__ipgdatNxxx_OnChannelsSwapped( AppApiChannel channel1, AppApiChannel channel2 );
extern void libs2chanlib__esctrlNx_OnVideoPidStopped( void );
extern NvmId libs2chanlib__nvmids_LstStatParentalRatingAge( void );
extern void libs2chanlib__pgdatNxxx_OnChannelMapLoadComplete( Bool Status );
extern void libs2chanlib__nvmpa_SetBoolIxIx( NvmId nvmid, int ix1, int ix2, Bool val, int subid );
extern void libs2chanlib__pgdatNxx_OnChannelTableChanged( void );
extern void libs2chanlib__esctrlNx_OnIPCCPidStopped( void );
extern void libs2chanlib__pgctl3N_OnCurrentPmtPidChanged( int PmtPid );
extern int libs2chanlib__nvmpa_GetIntIx( NvmId nvmid, int ix, int subid );
extern Int32 libs2chanlib__nvmpa_GetInt32( NvmId nvmid, int subid );
extern void libs2chanlib__ipgdatNxxx_OnChannelUpdated( AppApiChannel channel, int attribute );
extern void libs2chanlib__nvmpa_SetBoolIx( NvmId nvmid, int ix, Bool val, int subid );
extern int libs2chanlib__ipgdatNxxx_iPresent( void );
extern void libs2chanlib__pgdatNxxx_OnChannelTableChanged( void );
extern void libs2chanlib__esctrlNx_OnAudioPidStopped( void );
extern void libs2chanlib__nvmpa_SetIntIx( NvmId nvmid, int ix, int val, int subid );
extern void libs2chanlib__pgctl3N_OnDirectTuningEnd( AppApiDirectTuningParameters Param );
extern void libs2chanlib__esctrlNx_OnIPCCPidChanged( int Pid );
extern void libs2chanlib__esctrlN_OnCCPidStopped( void );
extern NvmId libs2chanlib__nvmids_LstStatParentalRatingDrugs( void );
extern void libs2chanlib__pgctlN_OnChannelChangeStart( AppApiChannel channel );
extern void libs2chanlib__esctrlN_OnPCRPidStopped( void );
extern void libs2chanlib__pgdatNxx_OnChannelRemoved( AppApiChannel channel );
extern void libs2chanlib__pgdatN_OnChannelAdded( AppApiChannel channel );
extern void libs2chanlib__esctrlNx_OnTeletextPidStopped( void );
extern void libs2chanlib__pgctlN_OnEvent( int event );
extern void libs2chanlib__pgdatN_OnChannelTableUpdateEnd( int Reset );
extern int libs2chanlib__nvmpa_GetIntIxIx( NvmId nvmid, int ix1, int ix2, int subid );
extern Bool libs2chanlib__nvmpa_GetBoolIxIx( NvmId nvmid, int ix1, int ix2, int subid );
extern void libs2chanlib__pgdatN_OnChannelTableUpdateStart( void );
extern Bool libs2chanlib__nvmpa_GetBoolIx( NvmId nvmid, int ix, int subid );
extern void libs2chanlib__esctrlN_OnCCPidChanged( int Pid );
extern void libs2chanlib__nvmpa_SetCharIx( NvmId nvmid, int ix, char val, int subid );
extern void libs2chanlib__esctrlN_OnPCRPidChanged( int Pid );
extern void libs2chanlib__pgctl3N_OnStreamParentalRatingChanged( AppApiParentalRating Rating );
extern void libs2chanlib__pgdatN_OnChannelsSwapped( AppApiChannel channel1, AppApiChannel channel2 );
extern int libs2chanlib__esctrlNx_iPresent( void );
extern void libs2chanlib__ipgdatNxxx_OnChannelTableChanged( void );
extern int libs2chanlib__pgdatN_iPresent( void );
extern void libs2chanlib__pgctl3N_OnDirectTuningStart( AppApiDirectTuningParameters Param );
extern void libs2chanlib__pgdatNxxx_OnChannelTableUpdateStart( void );
extern void libs2chanlib__pgdatN_OnChannelTableReset( void );
extern int libs2chanlib__nvmids_iPresent( void );
extern void libs2chanlib__nvmpa_SetInt32( NvmId nvmid, Int32 val, int subid );
extern void libs2chanlib__esctrlN_OnTeletextPidStopped( void );
extern int libs2chanlib__esctrlN_iPresent( void );
extern void libs2chanlib__pgdatNxx_OnChannelAdded( AppApiChannel channel );
extern NvmId libs2chanlib__nvmids_LastPresetTwoPartMinorNo( void );
extern void libs2chanlib__pgctl3N_OnCCSettingChanged( int CCSetting );
extern void libs2chanlib__esctrlN_OnAudioPidStopped( void );
extern void libs2chanlib__pgdatN_OnChannelRemoved( AppApiChannel channel );
extern void libs2chanlib__nvmpa_GetNat16( NvmId nvmid, int subid, Nat16 * value );
extern char libs2chanlib__nvmpa_GetCharIx( NvmId nvmid, int ix, int subid );
extern void libs2chanlib__nvmpa_InvalidateCache( void );
extern void libs2chanlib__pgdatNxxx_OnChannelTableUpdateEnd( int Reset );
extern void libs2chanlib__esctrlN_OnTeletextPidChanged( int Pid );
extern void libs2chanlib__esctrlNx_OnIPSubtitlePidStopped( void );
extern char libs2chanlib__nvmpa_GetCharIxIx( NvmId nvmid, int ix1, int ix2, int subid );
extern void libs2chanlib__pgdatNxx_OnChannelTableUpdateEnd( int Reset );
extern void libs2chanlib__esctrlN_OnAudioPidChanged( int Pid );
extern void libs2chanlib__ipgdatNxxx_OnChannelTableReset( void );
extern void libs2chanlib__ipgdatNxxx_OnChannelMapSaveComplete( Bool Status );
extern Int32 libs2chanlib__nvmpa_GetInt32IxIx( NvmId nvmid, int ix1, int ix2, int subid );
extern void libs2chanlib__ipgdatNxxx_OnChannelTableUpdateStart( void );
extern void libs2chanlib__ipgdatNxxx_OnChannelMapLoadComplete( Bool Status );
extern void libs2chanlib__esctrlNx_OnSubtitlePidChanged( int Pid );
extern void libs2chanlib__esctrlN_OnSubtitlePidChanged( int Pid );
extern void libs2chanlib__nvmpa_SetInt32IxIx( NvmId nvmid, int ix1, int ix2, Int32 val, int subid );
extern void libs2chanlib__esctrlNx_OnIPSubtitlePidChanged( int Pid );
extern int libs2chanlib__pgdatNxxx_iPresent( void );
extern void libs2chanlib__esctrlNx_OnSubtitlePidStopped( void );
extern void libs2chanlib__nvmpa_SetCharIxIx( NvmId nvmid, int ix1, int ix2, char val, int subid );
extern NvmId libs2chanlib__nvmids_LastPresetAnalogNo( void );
extern void libs2chanlib__pgctl3N_OnUserParentalRatingChanged( AppApiParentalRating Rating );
extern NvmId libs2chanlib__nvmids_LastPresetDigit( void );
extern NvmId libs2chanlib__nvmids_InstSettingsSubtitle( void );
extern void libs2chanlib__esctrlNx_OnCCPidStopped( void );
extern void libs2chanlib__pgdatNxx_OnChannelTableReset( void );
extern void libs2chanlib__pgctl3N_OnChannelChangeEnd( int seltype, AppApiChannel channel );
extern void libs2chanlib__esctrlNx_OnCCPidChanged( int Pid );
extern void libs2chanlib__pgctl3N_OnTeletextRatingContentChanged( Bool Status );
extern void libs2chanlib__pgctl3N_OnLockStatusChanged( int Status );
extern void libs2chanlib__ipgdatNxxx_OnChannelAdded( AppApiChannel channel );
extern void libs2chanlib__pgdatNxxx_OnChannelsSwapped( AppApiChannel channel1, AppApiChannel channel2 );
extern NvmId libs2chanlib__nvmids_LastSource( void );
extern int libs2chanlib__pgctl3N_iPresent( void );
extern void libs2chanlib__pgctl3N_OnChannelChangeStart( int seltype, AppApiChannel channel );
extern void libs2chanlib__esctrlNx_OnAudioPidChanged( int Pid );
extern void libs2chanlib__pgdatNxx_OnChannelTableUpdateStart( void );
extern void libs2chanlib__ipgdatNxxx_OnChannelsRearranged( AppApiChannel channel1, AppApiChannel channel2 );
extern void libs2chanlib__pgctlN_OnChannelChangeEnd( AppApiChannel channel );
extern Bool libs2chanlib__nvmpa_GetBool( NvmId nvmid, int subid );
extern void libs2chanlib__pgctlN_OnCCSettingChanged( int CCSetting );
extern void libs2chanlib__pgctlN_OnLockStatusChanged( int Status );
extern int libs2chanlib__subid_iPresent( void );
extern int libs2chanlib__pgctlN_iPresent( void );
extern void libs2chanlib__pgdatNxx_OnChannelsRearranged( AppApiChannel channel1, AppApiChannel channel2 );
extern void libs2chanlib__esctrlN_OnVideoPidStopped( void );
extern void libs2chanlib__pgdatN_OnChannelsRearranged( AppApiChannel channel1, AppApiChannel channel2 );
extern NvmId libs2chanlib__nvmids_LastPresetlPtc( void );
extern void libs2chanlib__pgdatNxxx_OnChannelRemoved( AppApiChannel channel );

/* interface libs2chanlib__dale : fusiondale.h */
/*   No functions found. */

/* interface libs2chanlib__dfb : directfb.h */
/*   No functions found. */

/* interface libs2chanlib__esctrlN : IAppApiElementaryStreamControlNotify */

/* interface libs2chanlib__esctrlNx : IAppApiElementaryStreamControlNotifyEx */

/* interface libs2chanlib__ipgdatNxxx : IHsvProgramDataNotifyExExEx */

/* interface libs2chanlib__nvmids : IAppApiChannelLibNvmIds */

/* interface libs2chanlib__nvmpa : IProdApiNvmProtectedAccessExEx */
#define libs2chanlib__nvmpa_optFalse	((int)0x0)
#define libs2chanlib__nvmpa_optInvalid	((int)0xFFFFFFFF)
#define libs2chanlib__nvmpa_optTrue	((int)0x1)

/* interface libs2chanlib__pgctl3N : IHsvProgramDataControlNotify3 */
#define libs2chanlib__pgctl3N_InstalledMediumChanged	((int)0x1)
#define libs2chanlib__pgctl3N_SelectedMediumChanged	((int)0x0)

/* interface libs2chanlib__pgctlN : IHsvProgramDataControlNotifyEx */
#define libs2chanlib__pgctlN_InstalledMediumChanged	((int)0x1)
#define libs2chanlib__pgctlN_SelectedMediumChanged	((int)0x0)

/* interface libs2chanlib__pgdatN : IHsvProgramDataNotify */

/* interface libs2chanlib__pgdatNxx : IHsvProgramDataNotifyExEx */
#define libs2chanlib__pgdatNxx_MajorChannel	((int)0x0)
#define libs2chanlib__pgdatNxx_MinorChannel	((int)0x1)
#define libs2chanlib__pgdatNxx_PIDs	((int)0x2)

/* interface libs2chanlib__pgdatNxxx : IHsvProgramDataNotifyExExEx */

/* interface libs2chanlib__subid : IProdApiNvmSubIdsEx */
#define libs2chanlib__subid_Apps	((int)0x1)
#define libs2chanlib__subid_Bra	((int)0x10000)
#define libs2chanlib__subid_Cbmhg	((int)0x400)
#define libs2chanlib__subid_Ceinfra	((int)0x100)
#define libs2chanlib__subid_Cetv	((int)0x80)
#define libs2chanlib__subid_Deasvc	((int)0x2)
#define libs2chanlib__subid_Demo	((int)0x40000)
#define libs2chanlib__subid_Dlna	((int)0x10)
#define libs2chanlib__subid_Dvbs2	((int)0x4000)
#define libs2chanlib__subid_Ecd	((int)0x20)
#define libs2chanlib__subid_Epg	((int)0x4)
#define libs2chanlib__subid_Eu	((int)0x8000)
#define libs2chanlib__subid_Fac	((int)0x10)
#define libs2chanlib__subid_Home	((int)0x20000)
#define libs2chanlib__subid_Media	((int)0x2000)
#define libs2chanlib__subid_NetTv	((int)0x1000)
#define libs2chanlib__subid_NotAllowed	((int)0xFFFF)
#define libs2chanlib__subid_Ols	((int)0x1000)
#define libs2chanlib__subid_Play	((int)0x2000)
#define libs2chanlib__subid_Prod	((int)0x200)
#define libs2chanlib__subid_Skype	((int)0x40)
#define libs2chanlib__subid_Svpsc	((int)0x40)
#define libs2chanlib__subid_Tv	((int)0x100000)
#define libs2chanlib__subid_Tvint	((int)0x800)
#define libs2chanlib__subid_Tvsvc	((int)0x20)
#define libs2chanlib__subid_Txsvc	((int)0x8)
#define libs2chanlib__subid_Txt	((int)0x2)
#define libs2chanlib__subid_Upg	((int)0x80000)
#define libs2chanlib__subid_Zap	((int)0x8)

#endif  /* _libs2chanlibapp_mreq_h */
#ifdef __cplusplus
}
#endif


