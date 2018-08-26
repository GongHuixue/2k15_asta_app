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

#ifndef _libs2chanlibapp_mprov_h
#define _libs2chanlibapp_mprov_h

#ifndef PREFIX
#define PREFIX	libs2chanlibapp
#endif
#define MODIDX	1

#include "plf/plfApi/export/build/os/type/infraglobals/idl/infraglobals.dd"
#include "plf/plfApi/export/build/avg/type/DPlfApiFrontend.dd"
#include "app/appApi/export/build/type/channelLib/AppApiChannelLibTypes.dd"
#include "app/appApi/export/build/type/channelLib/AppApiSatelliteTypes.dd"

/* interface libs2chanlib__chanret : IHsvChannelLibReturnCodes */
#define libs2chanlib__chanret_BadParameter	((AppApiReturnCode)0x1)
#define libs2chanlib__chanret_ChannelNotInstalled	((AppApiReturnCode)0x9)
#define libs2chanlib__chanret_ChannelTableCrcError	((AppApiReturnCode)0x8)
#define libs2chanlib__chanret_ChannelTableEmpty	((AppApiReturnCode)0x2)
#define libs2chanlib__chanret_ChannelTableExhausted	((AppApiReturnCode)0x3)
#define libs2chanlib__chanret_ChannelTableVersionError	((AppApiReturnCode)0x7)
#define libs2chanlib__chanret_FileError	((AppApiReturnCode)0x6)
#define libs2chanlib__chanret_MinorNumbersExhausted	((AppApiReturnCode)0x4)
#define libs2chanlib__chanret_NotSupported	((AppApiReturnCode)0x5)
#define libs2chanlib__chanret_NVMError	((AppApiReturnCode)0xA)
#define libs2chanlib__chanret_Ok	((AppApiReturnCode)0x0)

/* interface libs2chanlib__esctrl : IAppApiElementaryStreamControl */
#define libs2chanlib__esctrl_DefaultPID	((int)0x1FFF)

/* interface libs2chanlib__esctrlx : IAppApiElementaryStreamControlEx */
#define libs2chanlib__esctrlx_DefaultLanguage	((int)0xFFFFFFFF)
#define libs2chanlib__esctrlx_DefaultPID	((int)0x1FFF)

/* interface libs2chanlib__esctrlxx : IAppApiElementaryStreamControlExEx */
#define libs2chanlib__esctrlxx_DefaultLanguage	((int)0xFFFFFFFF)
#define libs2chanlib__esctrlxx_DefaultPID	((int)0x1FFF)

/* interface libs2chanlib__pgctl : IHsvProgramDataControl */
#define libs2chanlib__pgctl_Cable	((int)0x1)
#define libs2chanlib__pgctl_Satellite	((int)0x2)
#define libs2chanlib__pgctl_Terrestrial	((int)0x0)

/* interface libs2chanlib__pgctl3 : IHsvProgramDataControl3 */
#define libs2chanlib__pgctl3_Cable	((int)0x1)
#define libs2chanlib__pgctl3_CcOff	((int)0x1)
#define libs2chanlib__pgctl3_CcOn	((int)0x0)
#define libs2chanlib__pgctl3_CcOnDuringMute	((int)0x2)
#define libs2chanlib__pgctl3_Satellite	((int)0x2)
#define libs2chanlib__pgctl3_SelectionTypeNonDestructive	((int)0x2)
#define libs2chanlib__pgctl3_SelectionTypeNormal	((int)0x0)
#define libs2chanlib__pgctl3_SelectionTypeQuite	((int)0x1)
#define libs2chanlib__pgctl3_SelectionTypeQuiteNonDestructive	((int)0x3)
#define libs2chanlib__pgctl3_SubtitleOff	((int)0x0)
#define libs2chanlib__pgctl3_SubtitleOn	((int)0x1)
#define libs2chanlib__pgctl3_SubtitleOnDuringMute	((int)0x2)
#define libs2chanlib__pgctl3_Terrestrial	((int)0x0)

/* interface libs2chanlib__pgctl3x : IHsvSatProgramDataControl3Ex */
#define libs2chanlib__pgctl3x_Cable	((int)0x1)
#define libs2chanlib__pgctl3x_CcOff	((int)0x1)
#define libs2chanlib__pgctl3x_CcOn	((int)0x0)
#define libs2chanlib__pgctl3x_CcOnDuringMute	((int)0x2)
#define libs2chanlib__pgctl3x_Satellite	((int)0x2)
#define libs2chanlib__pgctl3x_SelectionTypeNonDestructive	((int)0x2)
#define libs2chanlib__pgctl3x_SelectionTypeNormal	((int)0x0)
#define libs2chanlib__pgctl3x_SelectionTypeQuite	((int)0x1)
#define libs2chanlib__pgctl3x_SelectionTypeQuiteNonDestructive	((int)0x3)
#define libs2chanlib__pgctl3x_SubtitleOff	((int)0x0)
#define libs2chanlib__pgctl3x_SubtitleOn	((int)0x1)
#define libs2chanlib__pgctl3x_SubtitleOnDuringMute	((int)0x2)
#define libs2chanlib__pgctl3x_Terrestrial	((int)0x0)

/* interface libs2chanlib__pgdat : IHsvProgramData */
#define libs2chanlib__pgdat_Antenna	((int)0x0)
#define libs2chanlib__pgdat_BoolFavorite	((int)0x1)
#define libs2chanlib__pgdat_BoolFreeCiMode	((int)0x6)
#define libs2chanlib__pgdat_BoolLock	((int)0x0)
#define libs2chanlib__pgdat_BoolMatchBrandFlag	((int)0x23)
#define libs2chanlib__pgdat_BoolNewPreset	((int)0x5)
#define libs2chanlib__pgdat_BoolSystemHidden	((int)0x3)
#define libs2chanlib__pgdat_BoolUpdateName	((int)0x7)
#define libs2chanlib__pgdat_BoolUserHidden	((int)0x2)
#define libs2chanlib__pgdat_Cable	((int)0x1)
#define libs2chanlib__pgdat_DecoderExt1	((int)0x1)
#define libs2chanlib__pgdat_DecoderExt2	((int)0x2)
#define libs2chanlib__pgdat_DecoderNone	((int)0x0)
#define libs2chanlib__pgdat_IntAudioPid	((int)0x17)
#define libs2chanlib__pgdat_IntAudioStreamType	((int)0x18)
#define libs2chanlib__pgdat_IntDeltaVolume	((int)0x8)
#define libs2chanlib__pgdat_IntFrequency	((int)0x9)
#define libs2chanlib__pgdat_IntLCN	((int)0x1C)
#define libs2chanlib__pgdat_IntModulation	((int)0xB)
#define libs2chanlib__pgdat_IntModulationType	((int)0x1B)
#define libs2chanlib__pgdat_IntNetworkId	((int)0xE)
#define libs2chanlib__pgdat_IntNumericSelect	((int)0x4)
#define libs2chanlib__pgdat_IntOriginalNwId	((int)0xF)
#define libs2chanlib__pgdat_IntPcrPid	((int)0x14)
#define libs2chanlib__pgdat_IntPmtPid	((int)0x13)
#define libs2chanlib__pgdat_IntPresetNumber	((int)0xA)
#define libs2chanlib__pgdat_IntPtc	((int)0x1D)
#define libs2chanlib__pgdat_IntSecAudioPid	((int)0x19)
#define libs2chanlib__pgdat_IntSecAudioStreamType	((int)0x1A)
#define libs2chanlib__pgdat_IntServiceId	((int)0x11)
#define libs2chanlib__pgdat_IntServiceType	((int)0x12)
#define libs2chanlib__pgdat_IntSignalQuality	((int)0xD)
#define libs2chanlib__pgdat_IntSignalStrength	((int)0xC)
#define libs2chanlib__pgdat_IntTsid	((int)0x10)
#define libs2chanlib__pgdat_IntVideoPid	((int)0x15)
#define libs2chanlib__pgdat_IntVideoStreamType	((int)0x16)
#define libs2chanlib__pgdat_Nat32AppsCookie	((int)0x1F)
#define libs2chanlib__pgdat_Nat32DateStamp	((int)0x1E)
#define libs2chanlib__pgdat_Nat32NumBrandIds	((int)0x24)
#define libs2chanlib__pgdat_Nat32SymbolRate	((int)0x21)
#define libs2chanlib__pgdat_Nat32TxtCookie	((int)0x20)
#define libs2chanlib__pgdat_StringBrandIds	((int)0x25)
#define libs2chanlib__pgdat_StringChannelName	((int)0x22)
#define libs2chanlib__pgdat_StringExtChannelName	((int)0x26)

/* interface libs2chanlib__pgdat3 : IHsvProgramData3 */
#define libs2chanlib__pgdat3_Antenna	((int)0x0)
#define libs2chanlib__pgdat3_BoolChannelLock	((Bool)0x2F)
#define libs2chanlib__pgdat3_BoolFavorite	((int)0x1)
#define libs2chanlib__pgdat3_BoolFreeCiMode	((int)0x6)
#define libs2chanlib__pgdat3_BoolLock	((int)0x0)
#define libs2chanlib__pgdat3_BoolMatchBrandFlag	((int)0x23)
#define libs2chanlib__pgdat3_BoolNewPreset	((int)0x5)
#define libs2chanlib__pgdat3_BoolSystemHidden	((int)0x3)
#define libs2chanlib__pgdat3_BoolUpdateName	((int)0x7)
#define libs2chanlib__pgdat3_BoolUserHidden	((int)0x2)
#define libs2chanlib__pgdat3_BoolUserModifiedLogo	((Bool)0x32)
#define libs2chanlib__pgdat3_Cable	((int)0x1)
#define libs2chanlib__pgdat3_DecoderExt1	((int)0x1)
#define libs2chanlib__pgdat3_DecoderExt2	((int)0x2)
#define libs2chanlib__pgdat3_DecoderNone	((int)0x0)
#define libs2chanlib__pgdat3_FavoriteNumber	((int)0x2D)
#define libs2chanlib__pgdat3_IntAudioPid	((int)0x17)
#define libs2chanlib__pgdat3_IntAudioStreamType	((int)0x18)
#define libs2chanlib__pgdat3_IntDeltaVolume	((int)0x8)
#define libs2chanlib__pgdat3_IntDpServiceId	((int)0x37)
#define libs2chanlib__pgdat3_IntDpTsid	((int)0x36)
#define libs2chanlib__pgdat3_IntFrequency	((int)0x9)
#define libs2chanlib__pgdat3_IntHbbTvOption	((int)0x2E)
#define libs2chanlib__pgdat3_IntInstalledSatelliteId	((int)0x3D)
#define libs2chanlib__pgdat3_IntInstalledSatelliteNumber	((int)0x2B)
#define libs2chanlib__pgdat3_IntLCN	((int)0x1C)
#define libs2chanlib__pgdat3_IntLnbNumber	((int)0x34)
#define libs2chanlib__pgdat3_IntLogoURL	((int)0x31)
#define libs2chanlib__pgdat3_IntModulation	((int)0xB)
#define libs2chanlib__pgdat3_IntModulationType	((int)0x1B)
#define libs2chanlib__pgdat3_IntNetworkId	((int)0xE)
#define libs2chanlib__pgdat3_IntNewChannel	((int)0x28)
#define libs2chanlib__pgdat3_IntNumericSelect	((int)0x4)
#define libs2chanlib__pgdat3_IntOriginalNwId	((int)0xF)
#define libs2chanlib__pgdat3_IntPackageGroup	((int)0x38)
#define libs2chanlib__pgdat3_IntPcrPid	((int)0x14)
#define libs2chanlib__pgdat3_IntPmtPid	((int)0x13)
#define libs2chanlib__pgdat3_IntPolarization	((int)0x35)
#define libs2chanlib__pgdat3_IntPresetNumber	((int)0xA)
#define libs2chanlib__pgdat3_IntPtc	((int)0x1D)
#define libs2chanlib__pgdat3_IntSatelliteId	((int)0x3C)
#define libs2chanlib__pgdat3_IntSecAudioPid	((int)0x19)
#define libs2chanlib__pgdat3_IntSecAudioStreamType	((int)0x1A)
#define libs2chanlib__pgdat3_IntServiceId	((int)0x11)
#define libs2chanlib__pgdat3_IntServiceType	((int)0x12)
#define libs2chanlib__pgdat3_IntSignalQuality	((int)0xD)
#define libs2chanlib__pgdat3_IntSignalStrength	((int)0xC)
#define libs2chanlib__pgdat3_IntSrcambledStatus	((int)0x2A)
#define libs2chanlib__pgdat3_IntSystemHidden	((int)0x27)
#define libs2chanlib__pgdat3_IntTsid	((int)0x10)
#define libs2chanlib__pgdat3_IntUserHidden	((int)0x2C)
#define libs2chanlib__pgdat3_IntVideoPid	((int)0x15)
#define libs2chanlib__pgdat3_IntVideoStreamType	((int)0x16)
#define libs2chanlib__pgdat3_MultipleLCN	((int)0x39)
#define libs2chanlib__pgdat3_MultiplePreset	((int)0x3A)
#define libs2chanlib__pgdat3_Nat32AppsCookie	((int)0x1F)
#define libs2chanlib__pgdat3_Nat32DateStamp	((int)0x1E)
#define libs2chanlib__pgdat3_Nat32NumBrandIds	((int)0x24)
#define libs2chanlib__pgdat3_Nat32SymbolRate	((int)0x21)
#define libs2chanlib__pgdat3_Nat32TPID	((int)0x33)
#define libs2chanlib__pgdat3_Nat32TxtCookie	((int)0x20)
#define libs2chanlib__pgdat3_Nat64UniqueNodeId	((Nat64)0x3B)
#define libs2chanlib__pgdat3_StringBrandIds	((int)0x25)
#define libs2chanlib__pgdat3_StringChannelName	((int)0x22)
#define libs2chanlib__pgdat3_StringExtChannelName	((int)0x26)
#define libs2chanlib__pgdat3_StringSatelliteName	((int)0x29)
#define libs2chanlib__pgdat3_StringTxtPages	((int)0x30)

/* interface libs2chanlib__pgdb : IHsvProgramDatabase */

/* interface libs2chanlib__pgdbconst : IHsvProgramDatabaseConstants */
#define libs2chanlib__pgdbconst_CurrentDigitalService	((int)0x40)
#define libs2chanlib__pgdbconst_CurrentDigitalTS	((int)0x20)
#define libs2chanlib__pgdbconst_CurrentPreset	((int)0x80)
#define libs2chanlib__pgdbconst_CurrentSatInfo	((int)0x10)
#define libs2chanlib__pgdbconst_DigitalService	((int)0x4)
#define libs2chanlib__pgdbconst_DigitalTS	((int)0x2)
#define libs2chanlib__pgdbconst_Preset	((int)0x8)
#define libs2chanlib__pgdbconst_Satellite	((int)0x10000)
#define libs2chanlib__pgdbconst_SatInfo	((int)0x1)
#define libs2chanlib__pgdbconst_TempSatellite	((int)0x20000)

/* interface libs2chanlib__pgitr : IHsvProgramIterator */
#define libs2chanlib__pgitr_All	((int)0x0)
#define libs2chanlib__pgitr_Analog	((int)0x2)
#define libs2chanlib__pgitr_AudioOnly	((Nat32)0x1000)
#define libs2chanlib__pgitr_ChannelsInMux	((int)0x5)
#define libs2chanlib__pgitr_Digital	((int)0x1)
#define libs2chanlib__pgitr_DvbC	((Nat32)0x8000)
#define libs2chanlib__pgitr_DvbCLite	((Nat32)0x20000)
#define libs2chanlib__pgitr_DvbS2	((Nat32)0x40000)
#define libs2chanlib__pgitr_DvbT	((Nat32)0x4000)
#define libs2chanlib__pgitr_DvbTLite	((Nat32)0x10000)
#define libs2chanlib__pgitr_EpgChannel	((Nat32)0x40)
#define libs2chanlib__pgitr_Favorite	((Nat32)0x1)
#define libs2chanlib__pgitr_Favorite1	((Nat32)0x2)
#define libs2chanlib__pgitr_Favorite2	((Nat32)0x4)
#define libs2chanlib__pgitr_Favorite3	((Nat32)0x8)
#define libs2chanlib__pgitr_Locked	((Nat32)0x10)
#define libs2chanlib__pgitr_Mux	((int)0x4)
#define libs2chanlib__pgitr_NonAudioOnly	((Nat32)0x2000)
#define libs2chanlib__pgitr_None	((Nat32)0x0)
#define libs2chanlib__pgitr_NonEpgChannel	((Nat32)0x80)
#define libs2chanlib__pgitr_NonSystemHidden	((Nat32)0x200)
#define libs2chanlib__pgitr_NonUserHidden	((Nat32)0x800)
#define libs2chanlib__pgitr_PreferredFavorite	((Nat32)0x1)
#define libs2chanlib__pgitr_SystemHidden	((Nat32)0x100)
#define libs2chanlib__pgitr_UnLocked	((Nat32)0x20)
#define libs2chanlib__pgitr_UserHidden	((Nat32)0x400)

/* interface libs2chanlib__pgitrx : IHsvProgramIteratorEx */
#define libs2chanlib__pgitrx_All	((int)0x0)
#define libs2chanlib__pgitrx_Analog	((int)0x2)
#define libs2chanlib__pgitrx_AudioOnly	((Nat32)0x1000)
#define libs2chanlib__pgitrx_ChannelsInMux	((int)0x5)
#define libs2chanlib__pgitrx_DataOnly	((Nat32)0x80000)
#define libs2chanlib__pgitrx_Digital	((int)0x1)
#define libs2chanlib__pgitrx_DvbC	((Nat32)0x8000)
#define libs2chanlib__pgitrx_DvbCLite	((Nat32)0x20000)
#define libs2chanlib__pgitrx_DvbS2	((Nat32)0x40000)
#define libs2chanlib__pgitrx_DvbT	((Nat32)0x4000)
#define libs2chanlib__pgitrx_DvbTLite	((Nat32)0x10000)
#define libs2chanlib__pgitrx_EpgChannel	((Nat32)0x40)
#define libs2chanlib__pgitrx_Favorite	((Nat32)0x1)
#define libs2chanlib__pgitrx_Favorite1	((Nat32)0x2)
#define libs2chanlib__pgitrx_Favorite2	((Nat32)0x4)
#define libs2chanlib__pgitrx_Favorite3	((Nat32)0x8)
#define libs2chanlib__pgitrx_GetNoOfMajorChannels( mode, descriptor, noofchannels )	((AppApiReturnCode)0x0)
#define libs2chanlib__pgitrx_Locked	((Nat32)0x10)
#define libs2chanlib__pgitrx_Mux	((int)0x4)
#define libs2chanlib__pgitrx_NonAudioOnly	((Nat32)0x2000)
#define libs2chanlib__pgitrx_NonDataOnly	((Nat32)0x100000)
#define libs2chanlib__pgitrx_None	((Nat32)0x0)
#define libs2chanlib__pgitrx_NonEpgChannel	((Nat32)0x80)
#define libs2chanlib__pgitrx_NonSystemHidden	((Nat32)0x200)
#define libs2chanlib__pgitrx_NonUserHidden	((Nat32)0x800)
#define libs2chanlib__pgitrx_PreferredFavorite	((Nat32)0x1)
#define libs2chanlib__pgitrx_SystemHidden	((Nat32)0x100)
#define libs2chanlib__pgitrx_UnLocked	((Nat32)0x20)
#define libs2chanlib__pgitrx_UserHidden	((Nat32)0x400)

/* interface libs2chanlib__pow : IAppApiPower */

/* interface libs2chanlib__s2alive : IHsvChanLibTimer */

/* interface libs2chanlib__sendevt : IHsvSendChannelEvents */
#define libs2chanlib__sendevt_CCControl	((int)0x13)
#define libs2chanlib__sendevt_CCSetting	((int)0x15)
#define libs2chanlib__sendevt_ChannelTableChanged	((int)0x5)
#define libs2chanlib__sendevt_ChannelTableUpdateEnd	((int)0x4)
#define libs2chanlib__sendevt_ChannelTableUpdateStart	((int)0x3)
#define libs2chanlib__sendevt_CurrentAudioLanguage	((int)0x21)
#define libs2chanlib__sendevt_CurrentPmtPidChanged	((int)0x17)
#define libs2chanlib__sendevt_CurrentSubtLanguage	((int)0x22)
#define libs2chanlib__sendevt_DirectProgramTune	((int)0x27)
#define libs2chanlib__sendevt_DirectTune	((int)0x6)
#define libs2chanlib__sendevt_DirectTuneEnd	((int)0x8)
#define libs2chanlib__sendevt_DirectTuneStart	((int)0x7)
#define libs2chanlib__sendevt_EnableLocks	((int)0x16)
#define libs2chanlib__sendevt_EuContentLibCreateComplete	((int)0x25)
#define libs2chanlib__sendevt_EventS2AppAlive	((int)0x29)
#define libs2chanlib__sendevt_EventS2AppEnabled	((int)0x28)
#define libs2chanlib__sendevt_LoadChannelMapFromMedium	((int)0x24)
#define libs2chanlib__sendevt_LockStatus	((int)0xB)
#define libs2chanlib__sendevt_MaxEvents	((int)0x2C)
#define libs2chanlib__sendevt_NetworkOperator	((int)0x2A)
#define libs2chanlib__sendevt_PackageId	((int)0x26)
#define libs2chanlib__sendevt_PidChanged	((int)0x10)
#define libs2chanlib__sendevt_PidStopped	((int)0x11)
#define libs2chanlib__sendevt_PlayIPPid	((int)0xE)
#define libs2chanlib__sendevt_PlayPid	((int)0xC)
#define libs2chanlib__sendevt_SaveChannelMapToMedium	((int)0x23)
#define libs2chanlib__sendevt_SelectChannel	((int)0x0)
#define libs2chanlib__sendevt_SelectChannel2	((int)0x18)
#define libs2chanlib__sendevt_SetCC	((int)0x1A)
#define libs2chanlib__sendevt_SetFrequency	((int)0x1C)
#define libs2chanlib__sendevt_SetNodeId	((int)0x1D)
#define libs2chanlib__sendevt_SetSubtitle	((int)0x19)
#define libs2chanlib__sendevt_SetTvSystem	((int)0x1B)
#define libs2chanlib__sendevt_StopIPPid	((int)0xF)
#define libs2chanlib__sendevt_StopPid	((int)0xD)
#define libs2chanlib__sendevt_StreamRating	((int)0xA)
#define libs2chanlib__sendevt_SubtitleAvailStatus	((int)0x1E)
#define libs2chanlib__sendevt_SubtitleControl	((int)0x12)
#define libs2chanlib__sendevt_SubtitleSetting	((int)0x14)
#define libs2chanlib__sendevt_TuneChannelEnd	((int)0x2)
#define libs2chanlib__sendevt_TuneChannelStart	((int)0x1)
#define libs2chanlib__sendevt_TXTAvailStatus	((int)0x1F)
#define libs2chanlib__sendevt_TxtRatedContent	((int)0x2B)
#define libs2chanlib__sendevt_UserRating	((int)0x9)
#define libs2chanlib__sendevt_VIAvailStatus	((int)0x20)

extern int libs2chanlib__esctrl_GetAudioPid( void );
extern int libs2chanlib__esctrl_GetCCPid( void );
extern int libs2chanlib__esctrl_GetPCRPid( void );
extern int libs2chanlib__esctrl_GetSubtitlePid( void );
extern int libs2chanlib__esctrl_GetTeletextPid( void );
extern int libs2chanlib__esctrl_GetVideoPid( void );
extern AppApiReturnCode libs2chanlib__esctrl_PlayAudioPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrl_PlayCCPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrl_PlayPCRPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrl_PlaySubtitlePid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrl_PlayTeletextPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrl_PlayVideoPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrl_StopAudioPid( void );
extern AppApiReturnCode libs2chanlib__esctrl_StopCCPid( void );
extern AppApiReturnCode libs2chanlib__esctrl_StopPCRPid( void );
extern AppApiReturnCode libs2chanlib__esctrl_StopSubtitlePid( void );
extern AppApiReturnCode libs2chanlib__esctrl_StopTeletextPid( void );
extern AppApiReturnCode libs2chanlib__esctrl_StopVideoPid( void );
extern int libs2chanlib__esctrlx_GetAudioPid( void );
extern int libs2chanlib__esctrlx_GetCCPid( void );
extern int libs2chanlib__esctrlx_GetIPCCPid( void );
extern int libs2chanlib__esctrlx_GetIPSubtitlePid( void );
extern int libs2chanlib__esctrlx_GetPCRPid( void );
extern int libs2chanlib__esctrlx_GetSubtitlePid( void );
extern int libs2chanlib__esctrlx_GetTeletextPid( void );
extern int libs2chanlib__esctrlx_GetVideoPid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayAudioPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayCCPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayIPCCPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayIPSubtitlePid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayPCRPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlaySubtitlePid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayTeletextPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_PlayVideoPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlx_StopAudioPid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopCCPid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopIPCCPid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopIPSubtitlePid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopPCRPid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopSubtitlePid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopTeletextPid( void );
extern AppApiReturnCode libs2chanlib__esctrlx_StopVideoPid( void );
extern int libs2chanlib__esctrlxx_GetAudioPid( void );
extern int libs2chanlib__esctrlxx_GetCCPid( void );
extern int libs2chanlib__esctrlxx_GetIPCCPid( void );
extern int libs2chanlib__esctrlxx_GetIPSubtitlePid( void );
extern int libs2chanlib__esctrlxx_GetPCRPid( void );
extern int libs2chanlib__esctrlxx_GetSubtitlePid( void );
extern int libs2chanlib__esctrlxx_GetTeletextPid( void );
extern int libs2chanlib__esctrlxx_GetVideoPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayAudioPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayCCPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayIPCCPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayIPCCPidEx( int PIDValue, Nat8 CurrentLanguageTag );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayIPSubtitlePid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayIPSubtitlePidEx( int PIDValue, Nat16 CompositionPageId, Nat16 AncilliaryPageId );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayPCRPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlaySubtitlePid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayTeletextPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_PlayVideoPid( int PIDValue );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopAudioPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopCCPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopIPCCPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopIPSubtitlePid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopPCRPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopSubtitlePid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopTeletextPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_StopVideoPid( void );
extern AppApiReturnCode libs2chanlib__esctrlxx_TeletextRatedContentEvent( Bool RatedContent );
extern AppApiReturnCode libs2chanlib__pgctl_DirectTuning( AppApiDirectTuningParameters param );
extern AppApiReturnCode libs2chanlib__pgctl_DisableClosedCaption( void );
extern AppApiReturnCode libs2chanlib__pgctl_DisableSubtitle( void );
extern AppApiReturnCode libs2chanlib__pgctl_EnableClosedCaption( void );
extern AppApiReturnCode libs2chanlib__pgctl_EnableSubtitle( void );
extern AppApiReturnCode libs2chanlib__pgctl_GetCCSettings( int * CCSetting );
extern AppApiReturnCode libs2chanlib__pgctl_GetCurrentProgram( AppApiChannel * Channel );
extern int libs2chanlib__pgctl_GetInstalledMedium( void );
extern int libs2chanlib__pgctl_GetSelectedMedium( void );
extern AppApiReturnCode libs2chanlib__pgctl_GetStreamParentalRating( AppApiParentalRating * Rating );
extern AppApiReturnCode libs2chanlib__pgctl_GetUserParentalRating( AppApiParentalRating * Rating );
extern AppApiReturnCode libs2chanlib__pgctl_IsChannelLocked( int * Status );
extern AppApiReturnCode libs2chanlib__pgctl_SelectChannel( AppApiChannel channel );
extern void libs2chanlib__pgctl_SetInstalledMedium( int medium );
extern void libs2chanlib__pgctl_SetSelectedMedium( int medium );
extern AppApiReturnCode libs2chanlib__pgctl3_DirectTuning( AppApiDirectTuningParameters param );
extern AppApiReturnCode libs2chanlib__pgctl3_DisableClosedCaption( void );
extern AppApiReturnCode libs2chanlib__pgctl3_DisableSubtitle( void );
extern AppApiReturnCode libs2chanlib__pgctl3_EnableClosedCaption( void );
extern AppApiReturnCode libs2chanlib__pgctl3_EnableLocks( Bool enable );
extern AppApiReturnCode libs2chanlib__pgctl3_EnableSubtitle( void );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCCSettings( int * CCSetting );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentAudioLanguage( int * Language );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentAudioType( int * AudioType );
extern int libs2chanlib__pgctl3_GetCurrentPMTPID( void );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentProgram( AppApiChannel * Channel );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentSatelliteName( Nat16 * SatelliteName );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentSubtitleLanguage( int * Language );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentSubtitleStatus( AppApiSubtitleType * SubtitleType );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentSubtitleType( int * SubtitleType );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentTeletextStatus( Bool * Present );
extern AppApiReturnCode libs2chanlib__pgctl3_GetCurrentVisuallyImpairedStatus( Bool * Present );
extern int libs2chanlib__pgctl3_GetInstalledMedium( void );
extern int libs2chanlib__pgctl3_GetSelectedMedium( void );
extern AppApiReturnCode libs2chanlib__pgctl3_GetStreamParentalRating( AppApiParentalRating * Rating );
extern AppApiReturnCode libs2chanlib__pgctl3_GetSubtitleSetting( int * SubtitleSetting );
extern AppApiReturnCode libs2chanlib__pgctl3_GetUserParentalRating( AppApiParentalRating * Rating );
extern AppApiReturnCode libs2chanlib__pgctl3_IsChannelLocked( int * Status );
extern AppApiReturnCode libs2chanlib__pgctl3_LoadChannelMap( char * sourcedir, int MapType );
extern AppApiReturnCode libs2chanlib__pgctl3_SaveChannelMap( char * destdir, int MapType );
extern AppApiReturnCode libs2chanlib__pgctl3_SelectChannel( int seltype, AppApiChannel channel );
extern void libs2chanlib__pgctl3_SetChannelUniqueNodeId( AppApiChannel channel, Nat64 node_id );
extern void libs2chanlib__pgctl3_SetInstalledMedium( int medium );
extern void libs2chanlib__pgctl3_SetSelectedMedium( int medium );
extern AppApiReturnCode libs2chanlib__pgctl3x_DirectProgramTuning( AppApiDirectTuningParameters2 param );
extern AppApiReturnCode libs2chanlib__pgctl3x_DirectTuning( AppApiDirectTuningParameters param );
extern AppApiReturnCode libs2chanlib__pgctl3x_DisableClosedCaption( void );
extern AppApiReturnCode libs2chanlib__pgctl3x_DisableSubtitle( void );
extern AppApiReturnCode libs2chanlib__pgctl3x_EnableClosedCaption( void );
extern AppApiReturnCode libs2chanlib__pgctl3x_EnableLocks( Bool enable );
extern AppApiReturnCode libs2chanlib__pgctl3x_EnableSubtitle( void );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCCSettings( int * CCSetting );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentAudioLanguage( int * Language );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentAudioType( int * AudioType );
extern int libs2chanlib__pgctl3x_GetCurrentPMTPID( void );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentProgram( AppApiChannel * Channel );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentSatelliteName( Nat16 * SatelliteName );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentSubtitleLanguage( int * Language );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentSubtitleStatus( AppApiSubtitleType * SubtitleType );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentSubtitleType( int * SubtitleType );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentTeletextStatus( Bool * Present );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetCurrentVisuallyImpairedStatus( Bool * Present );
extern int libs2chanlib__pgctl3x_GetInstalledMedium( void );
extern int libs2chanlib__pgctl3x_GetSelectedMedium( void );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetStreamParentalRating( AppApiParentalRating * Rating );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetSubtitleSetting( int * SubtitleSetting );
extern AppApiReturnCode libs2chanlib__pgctl3x_GetUserParentalRating( AppApiParentalRating * Rating );
extern AppApiReturnCode libs2chanlib__pgctl3x_IsChannelLocked( int * Status );
extern AppApiReturnCode libs2chanlib__pgctl3x_LoadChannelMap( char * sourcedir, int MapType );
extern AppApiReturnCode libs2chanlib__pgctl3x_SaveChannelMap( char * destdir, int MapType );
extern AppApiReturnCode libs2chanlib__pgctl3x_SelectChannel( int seltype, AppApiChannel channel );
extern void libs2chanlib__pgctl3x_SetChannelUniqueNodeId( AppApiChannel channel, Nat64 node_id );
extern void libs2chanlib__pgctl3x_SetInstalledMedium( int medium );
extern void libs2chanlib__pgctl3x_SetSelectedMedium( int medium );
extern void libs2chanlib__pgdat_ClearAllTables( void );
extern void libs2chanlib__pgdat_ClearCurrentTable( void );
extern AppApiReturnCode libs2chanlib__pgdat_GetChannelDataBool( AppApiChannel channel, int dataid, Bool * value );
extern AppApiReturnCode libs2chanlib__pgdat_GetChannelDataInt( AppApiChannel channel, int dataid, int * value );
extern AppApiReturnCode libs2chanlib__pgdat_GetChannelDataNat32( AppApiChannel channel, int dataid, Nat32 * value );
extern AppApiReturnCode libs2chanlib__pgdat_GetChannelDataString( AppApiChannel channel, int dataid, Nat16 * value, int size );
extern AppApiReturnCode libs2chanlib__pgdat_GetDigitalChannel( AppApiChannel * channel, int OnId, int TsId, int Sid, int Ptc );
extern Bool libs2chanlib__pgdat_IsAttributeSupported( int attribute );
extern Bool libs2chanlib__pgdat_IsChannelInstalled( AppApiChannel * channel );
extern Bool libs2chanlib__pgdat_IsValidChannel( AppApiChannel channel );
extern AppApiReturnCode libs2chanlib__pgdat_LoadChannelTable( char * dir );
extern AppApiReturnCode libs2chanlib__pgdat_LoadChannelTableFromMedium( char * dir, int medium );
extern AppApiReturnCode libs2chanlib__pgdat_ReorderChannels( AppApiChannel channel1, AppApiChannel channel2, Bool Swap );
extern AppApiReturnCode libs2chanlib__pgdat_SaveChannelTable( char * dir );
extern AppApiReturnCode libs2chanlib__pgdat_SaveChannelTableToMedium( char * dir, int medium );
extern AppApiReturnCode libs2chanlib__pgdat_StoreChannelDataBool( AppApiChannel channel, int dataid, Bool value );
extern AppApiReturnCode libs2chanlib__pgdat_StoreChannelDataInt( AppApiChannel channel, int dataid, int value );
extern AppApiReturnCode libs2chanlib__pgdat_StoreChannelDataNat32( AppApiChannel channel, int dataid, Nat32 value );
extern AppApiReturnCode libs2chanlib__pgdat_StoreChannelDataString( AppApiChannel channel, int dataid, Nat16 * value, int size );
extern AppApiReturnCode libs2chanlib__pgdat_SwapChannels( AppApiChannel channel1, AppApiChannel channel2 );
extern void libs2chanlib__pgdat3_ClearAllTables( void );
extern void libs2chanlib__pgdat3_ClearCurrentTable( void );
extern AppApiReturnCode libs2chanlib__pgdat3_GetBarkerMultiplexByIndex( int index, AppApiMultiplex * muxes );
extern AppApiReturnCode libs2chanlib__pgdat3_GetBarkerMultiplexesForChannel( AppApiChannel channel, int * NoOfMuxes, AppApiMultiplex * muxes );
extern AppApiReturnCode libs2chanlib__pgdat3_GetChannelDataBool( AppApiChannel channel, int dataid, Bool * value );
extern AppApiReturnCode libs2chanlib__pgdat3_GetChannelDataInt( AppApiChannel channel, int dataid, int * value );
extern AppApiReturnCode libs2chanlib__pgdat3_GetChannelDataNat32( AppApiChannel channel, int dataid, Nat32 * value );
extern AppApiReturnCode libs2chanlib__pgdat3_GetChannelDataNat64( AppApiChannel channel, int dataid, Nat64 * value );
extern AppApiReturnCode libs2chanlib__pgdat3_GetChannelDataString( AppApiChannel channel, int dataid, Nat16 * value, int size );
extern AppApiReturnCode libs2chanlib__pgdat3_GetDigitalChannel( AppApiChannel * channel, int OnId, int TsId, int Sid, int Ptc );
extern AppApiReturnCode libs2chanlib__pgdat3_GetDigitalChannelForFreesat( int * MultiplePresetList, int OnId, int TsId, int Sid, int Ptc );
extern AppApiReturnCode libs2chanlib__pgdat3_GetMediumFromTable( char * dir, int * medium );
extern AppApiReturnCode libs2chanlib__pgdat3_GetNoOfBarkerMultiplexes( int * NoOfMuxes );
extern AppApiReturnCode libs2chanlib__pgdat3_GetOperator( AppApiOperator * OperatorId );
extern AppApiReturnCode libs2chanlib__pgdat3_GetSatelliteName( int LnbNumber, Nat16 * SatelliteName );
extern AppApiReturnCode libs2chanlib__pgdat3_GetSatellitePackage( AppApiPackageId * PackageId, AppApiPackageGroup * PackageIGroupId );
extern Bool libs2chanlib__pgdat3_IsAttributeSupported( int attribute );
extern Bool libs2chanlib__pgdat3_IsChannelInstalled( AppApiChannel * channel );
extern Bool libs2chanlib__pgdat3_IsValidChannel( AppApiChannel channel );
extern AppApiReturnCode libs2chanlib__pgdat3_LoadChannelTable( char * dir );
extern AppApiReturnCode libs2chanlib__pgdat3_LoadChannelTableFromMedium( char * dir, int medium );
extern AppApiReturnCode libs2chanlib__pgdat3_ReArrangeChannels( AppApiChannel channel1, AppApiChannel channel2 );
extern AppApiReturnCode libs2chanlib__pgdat3_ReorderChannels( AppApiChannel channel1, AppApiChannel channel2, Bool Swap );
extern AppApiReturnCode libs2chanlib__pgdat3_SaveChannelTable( char * dir );
extern AppApiReturnCode libs2chanlib__pgdat3_SaveChannelTableToMedium( char * dir, int medium );
extern AppApiReturnCode libs2chanlib__pgdat3_StoreChannelDataBool( AppApiChannel channel, int dataid, Bool value );
extern AppApiReturnCode libs2chanlib__pgdat3_StoreChannelDataInt( AppApiChannel channel, int dataid, int value );
extern AppApiReturnCode libs2chanlib__pgdat3_StoreChannelDataNat32( AppApiChannel channel, int dataid, Nat32 value );
extern AppApiReturnCode libs2chanlib__pgdat3_StoreChannelDataNat64( AppApiChannel channel, int dataid, Nat64 value );
extern AppApiReturnCode libs2chanlib__pgdat3_StoreChannelDataString( AppApiChannel channel, int dataid, Nat16 * value, int size );
extern AppApiReturnCode libs2chanlib__pgdat3_SwapChannels( AppApiChannel channel1, AppApiChannel channel2 );
extern Bool libs2chanlib__pgdb_Add( int tableid, Address channeldata );
extern void libs2chanlib__pgdb_ChannelTableChanged( void );
extern Bool libs2chanlib__pgdb_ClearTable( int tableid );
extern Bool libs2chanlib__pgdb_CommitTable( int tableid );
extern Bool libs2chanlib__pgdb_Delete( int tableid, Address channeldata );
extern void libs2chanlib__pgdb_EnableAutoCommit( Bool enable );
extern Bool libs2chanlib__pgdb_GetByIndex( int tableid, int index, Address channeldata );
extern Bool libs2chanlib__pgdb_GetByKey( int tableid, Address channeldata );
extern int libs2chanlib__pgdb_GetCurrentTable( void );
extern int libs2chanlib__pgdb_GetIndex( int tableid, int * index, Address channeldata );
extern int libs2chanlib__pgdb_GetNoRecords( int tableid );
extern Bool libs2chanlib__pgdb_GetRange( int tableid, int noofkeys, Address channeldata, int * from, int * to );
extern void libs2chanlib__pgdb_Initialise( int tableid, Address channeldata );
extern Bool libs2chanlib__pgdb_IsSupported( int tableid );
extern Bool libs2chanlib__pgdb_LoadTable( int tableid );
extern void libs2chanlib__pgdb_MasterEnableEvents( Bool Status );
extern Bool libs2chanlib__pgdb_SelectTable( int tableid );
extern Bool libs2chanlib__pgdb_Update( int tableid, Address channeldata );
extern AppApiReturnCode libs2chanlib__pgitr_GetFirstChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetFirstMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetFirstMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetFirstMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitr_GetLastChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetLastMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetLastMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetLastMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitr_GetNextChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetNextMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetNextMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetNextMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitr_GetNoOfChannels( int mode, Nat32 descriptor, int * noofchannels );
extern AppApiReturnCode libs2chanlib__pgitr_GetNoOfMinorChannelsOfMajor( Nat32 descriptor, AppApiChannel channelno, int * noofminors );
extern AppApiReturnCode libs2chanlib__pgitr_GetNoOfMultiplexes( int * noofmuxes );
extern AppApiReturnCode libs2chanlib__pgitr_GetPreviousChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetPreviousMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetPreviousMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitr_GetPreviousMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitrx_GetFirstChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetFirstMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetFirstMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetFirstMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitrx_GetLastChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetLastMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetLastMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetLastMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNextChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNextMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNextMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNextMultiplex( AppApiMultiplex * mux );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNoOfChannels( int mode, Nat32 descriptor, int * noofchannels );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNoOfMinorChannelsOfMajor( Nat32 descriptor, AppApiChannel channelno, int * noofminors );
extern AppApiReturnCode libs2chanlib__pgitrx_GetNoOfMultiplexes( int * noofmuxes );
extern AppApiReturnCode libs2chanlib__pgitrx_GetPreviousChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetPreviousMajorChannel( int mode, Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetPreviousMinorChannel( Nat32 descriptor, AppApiChannel * channelno );
extern AppApiReturnCode libs2chanlib__pgitrx_GetPreviousMultiplex( AppApiMultiplex * mux );
extern void libs2chanlib__pow_Init( void );
extern void libs2chanlib__pow_TurnOff( void );
extern void libs2chanlib__pow_TurnOn( void );
extern void libs2chanlib__s2alive_ActivateS2AliveTimer( void );
extern void libs2chanlib__sendevt_SendEvent( int EventId, Address data, Nat32 size );

extern int libs2chanlib__RegisterCallback_esctrlN_OnAudioPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnAudioPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnCCPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnCCPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnPCRPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnPCRPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnSubtitlePidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnSubtitlePidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnTeletextPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnTeletextPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnVideoPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlN_OnVideoPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnAudioPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnAudioPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnCCPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnCCPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnIPCCPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnIPCCPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnIPSubtitlePidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnIPSubtitlePidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnPCRPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnPCRPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnSubtitlePidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnSubtitlePidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnTeletextPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnTeletextPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnVideoPidChanged( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_esctrlNx_OnVideoPidStopped( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelAdded( Bool remove, void (*cb)( AppApiChannel ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelMapLoadComplete( Bool remove, void (*cb)( Bool ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelMapSaveComplete( Bool remove, void (*cb)( Bool ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelRemoved( Bool remove, void (*cb)( AppApiChannel ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelsRearranged( Bool remove, void (*cb)( AppApiChannel , AppApiChannel ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelsSwapped( Bool remove, void (*cb)( AppApiChannel , AppApiChannel ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelTableChanged( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelTableReset( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelTableUpdateEnd( Bool remove, void (*cb)( int ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelTableUpdateStart( Bool remove, void (*cb)( ) );
extern int libs2chanlib__RegisterCallback_pgdatNxxx_OnChannelUpdated( Bool remove, void (*cb)( AppApiChannel , int ) );

#endif  /* _libs2chanlibapp_mprov_h */
#ifdef __cplusplus
}
#endif
