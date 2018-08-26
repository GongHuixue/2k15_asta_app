#ifndef IAPPAPISYSTEMSETTINGS3_H
#define IAPPAPISYSTEMSETTINGS3_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSystemSettings3
{
public:
	virtual ~IAppApiSystemSettings3(){}
	#define IAppApiSystemSettings3_Success		((int)0 )
	#define IAppApiSystemSettings3_NVMFailure		((int)1 )
	#define IAppApiSystemSettings3_CertificateDetectionNotDone		((int)2 )
	#define IAppApiSystemSettings3_InitFailure		((int)3 )
	#define IAppApiSystemSettings3_AutoEpg		((int)0 )
	#define IAppApiSystemSettings3_DVBEpg		((int)1 )
	#define IAppApiSystemSettings3_IPEpg		((int)2 )
	#define IAppApiSystemSettings3_Shop		((int)0 )
	#define IAppApiSystemSettings3_Home		((int)1 )
	#define IAppApiSystemSettings3_clkSrcNone		((int)0 )
	#define IAppApiSystemSettings3_clkSrcMainTuner		((int)1 )
	#define IAppApiSystemSettings3_clkSrcSatelliteTuner		((int)2 )
	#define IAppApiSystemSettings3_clkSrcManualClock		((int)3 )
	#define IAppApiSystemSettings3_avSrcNone		((int)0 )
	#define IAppApiSystemSettings3_avSrcMainTuner		((int)1 )
	#define IAppApiSystemSettings3_avSrcSatellite		((int)2 )
	#define IAppApiSystemSettings3_avSrcAvIn0		((int)3 )
	#define IAppApiSystemSettings3_avSrcAvIn1		((int)4 )
	#define IAppApiSystemSettings3_avSrcAvIn2		((int)5 )
	#define IAppApiSystemSettings3_avSrcAvIn3		((int)6 )
	#define IAppApiSystemSettings3_avSrcAvIn4		((int)7 )
	#define IAppApiSystemSettings3_avSrcAvIn5		((int)8 )
	#define IAppApiSystemSettings3_avSrcAvIn6		((int)9 )
	#define IAppApiSystemSettings3_avSrcAvIn7		((int)10 )
	#define IAppApiSystemSettings3_avSrcAvIn8		((int)11 )
	#define IAppApiSystemSettings3_avSrcAvIn9		((int)12 )
	#define IAppApiSystemSettings3_avSrcAvIn10		((int)13 )
	#define IAppApiSystemSettings3_svcModeNone		((int)0 )
	#define IAppApiSystemSettings3_svcModeCSM		((int)1 )
	#define IAppApiSystemSettings3_svcModeSAM		((int)2 )
	#define IAppApiSystemSettings3_svcModeSDM		((int)3 )
	#define IAppApiSystemSettings3_svcModeCompair		((int)4 )
	#define IAppApiSystemSettings3_svcModeFac		((int)5 )
	#define IAppApiSystemSettings3_svcModeDigSDM		((int)6 )
	#define IAppApiSystemSettings3_svcModeBDS		((int)7 )
	#define IAppApiSystemSettings3_BdsPowStateOn		((int)0 )
	#define IAppApiSystemSettings3_BdsPowStateStandby		((int)1 )
	#define IAppApiSystemSettings3_AudioFormatStandard		((int)0 )
	#define IAppApiSystemSettings3_AudioFormatAdvanced		((int)1 )
	#define IAppApiSystemSettings3_OsdSizeInvalid		((int)-1 )
	#define IAppApiSystemSettings3_OsdSizeSmall		((int)0 )
	#define IAppApiSystemSettings3_OsdSizeLarge		((int)1 )
	#define IAppApiSystemSettings3_SpainBaleares		((int)1 )
	#define IAppApiSystemSettings3_SpainCanaryIsland		((int)2 )
	#define IAppApiSystemSettings3_TimeZoneContinental		((int)9 )
	#define IAppApiSystemSettings3_TimeZoneAzores		((int)10 )
	#define IAppApiSystemSettings3_TimeZoneKalingrad		((int)11 )
	#define IAppApiSystemSettings3_TimeZoneMoscow		((int)12 )
	#define IAppApiSystemSettings3_TimeZoneSamara		((int)13 )
	#define IAppApiSystemSettings3_TimeZoneYekaterinburg		((int)14 )
	#define IAppApiSystemSettings3_TimeZoneOmsk		((int)15 )
	#define IAppApiSystemSettings3_TimeZoneKrasnoyarsk		((int)16 )
	#define IAppApiSystemSettings3_TimeZoneIrkutsk		((int)17 )
	#define IAppApiSystemSettings3_TimeZoneYakutsk		((int)18 )
	#define IAppApiSystemSettings3_TimeZoneVladivostok		((int)19 )
	#define IAppApiSystemSettings3_TimeZoneMagadan		((int)20 )
	#define IAppApiSystemSettings3_TimeZoneKamchatka		((int)21 )
	#define IAppApiSystemSettings3_TimeZoneLatamMinus2		((int)0 )
	#define IAppApiSystemSettings3_TimeZoneLatamMinus1		((int)1 )
	#define IAppApiSystemSettings3_TimeZoneLatamZero		((int)2 )
	#define IAppApiSystemSettings3_TimeZoneLatamPlus1		((int)3 )
	#define IAppApiSystemSettings3_TimeZoneLatamPlus2		((int)4 )
	#define IAppApiSystemSettings3_NewSouthWales		((int)2 )
	#define IAppApiSystemSettings3_Victoria		((int)3 )
	#define IAppApiSystemSettings3_Queensland		((int)4 )
	#define IAppApiSystemSettings3_SouthAustralia		((int)5 )
	#define IAppApiSystemSettings3_WestAustralia		((int)6 )
	#define IAppApiSystemSettings3_Tasmania		((int)7 )
	#define IAppApiSystemSettings3_NorthernTerritory		((int)8 )
	#define IAppApiSystemSettings3_ManualClkMode		((int)0 )
	#define IAppApiSystemSettings3_AutoClkMode		((int)1 )
	#define IAppApiSystemSettings3_CountryDepClkMode		((int)2 )
	#define IAppApiSystemSettings3_DstOff		((Bool)0 )
	#define IAppApiSystemSettings3_DstOn		((Bool)1 )
	#define IAppApiSystemSettings3_CalStateNotStarted		((int)0 )
	#define IAppApiSystemSettings3_CalStateInProgress		((int)1 )
	#define IAppApiSystemSettings3_CalStateSuccessfull		((int)2 )
	#define IAppApiSystemSettings3_CalStateFailed		((int)3 )
	#define IAppApiSystemSettings3_CalStateForced		((int)4 )
	#define IAppApiSystemSettings3_AutoPowerDownModeOff		((Bool)0 )
	#define IAppApiSystemSettings3_AutoPowerDownModeOn		((Bool)1 )
	#define IAppApiSystemSettings3_ChannelListAll		((int)0 )
	#define IAppApiSystemSettings3_ChannelListTV		((int)1 )
	#define IAppApiSystemSettings3_ChannelListRadio		((int)2 )
	#define IAppApiSystemSettings3_ChannelListFavorite		((int)3 )
	#define IAppApiSystemSettings3_ChannelListAnalog		((int)4 )
	#define IAppApiSystemSettings3_MediumNone		((int)-1 )
	#define IAppApiSystemSettings3_MediumTerrestrial		((int)0 )
	#define IAppApiSystemSettings3_MediumCable		((int)1 )
	virtual int GetClockMode(void)= 0;
	virtual void SetClockMode(int mode)= 0;
	virtual Bool IsDstSettingControllable(void)= 0;
	virtual int GetDst(void)= 0;
	virtual void SetDst(Bool dst)= 0;
	virtual Bool IsManualClockSettingControllable(void)= 0;
	virtual Bool GetAutoPowerDownMode(void)= 0;
	virtual void SetAutoPowerDownMode(Bool mode)= 0;
	virtual FResult SetMenuLanguage(int language)= 0;
	virtual int GetMenuLanguage(void)= 0;
	virtual FResult SetInstallCountry(int country)= 0;
	virtual int GetInstallCountry(void)= 0;
	virtual Bool IsDateSet(void)= 0;
	virtual Bool IsClockDefined(void)= 0;
	virtual Bool IsLTOSet(void)= 0;
	virtual FResult SetRCLock(Bool OnOff)= 0;
	virtual Bool GetRCLockStatus(void)= 0;
	virtual void OverrideRCLock(Bool Override)= 0;
	virtual FResult SetKeyboardLock(Bool OnOff)= 0;
	virtual Bool GetKeyboardLock(void)= 0;
	virtual FResult SetBDSMode(Bool mode)= 0;
	virtual FResult GetBDSMode(Bool * mode)= 0;
	virtual FResult SetSXApplicationControl(Bool onoff)= 0;
	virtual Bool GetSXApplicationControl(void)= 0;
	virtual FResult SetBDSFeatureEnabled(Bool onoff)= 0;
	virtual Bool GetBDSFeatureEnabled(void)= 0;
	virtual FResult SetBDSPowerOnState(int state)= 0;
	virtual int GetBDSPowerOnState(void)= 0;
	virtual FResult SetOSDDisplay(Bool on_off)= 0;
	virtual Bool GetOSDDisplay(void)= 0;
	virtual FResult SetBdsWakeupSource(int src)= 0;
	virtual int GetBdsWakeupSource(void)= 0;
	virtual FResult SetHotelModeUsbBreakInAllowed(Bool onOff)= 0;
	virtual Bool GetHotelModeUsbBreakInAllowed(void)= 0;
	virtual FResult SetMaxAllowedVolume(int MaxVol)= 0;
	virtual int GetMaxAllowedVolume(void)= 0;
	virtual FResult SetEpgType(int epgType)= 0;
	virtual int GetEpgType(void)= 0;
	virtual FResult SetFactoryMode(Bool onoff)= 0;
	virtual Bool GetFactoryMode(void)= 0;
	virtual FResult SetShopHomeMode(int mode)= 0;
	virtual int GetShopHomeMode(void)= 0;
	virtual FResult SetVirginBit(Bool virginBit)= 0;
	virtual Bool GetVirginBit(void)= 0;
	virtual FResult SetClockCalibSource(int src)= 0;
	virtual int GetClockCalibSource(void)= 0;
	virtual FResult SetCurrentAVSource(int src)= 0;
	virtual int GetCurrentAVSource(void)= 0;
	virtual FResult SetPreferredAudioFormat(int format)= 0;
	virtual int GetPreferredAudioFormat(void)= 0;
	virtual FResult SetServiceMode(int mode)= 0;
	virtual int GetServiceMode(void)= 0;
	virtual void SetTimeZone(int timezone)= 0;
	virtual int GetTimeZone(void)= 0;
	virtual Bool IsTimeZoneSettingControllable(void)= 0;
	virtual Bool IsTimeZoneAvailable(int timezone)= 0;
	virtual Nat32 GetSystemVersionNumber(void)= 0;
	virtual FResult SetOsdSize(int size)= 0;
	virtual int GetOsdSize(void)= 0;
	virtual void SetClockCaliberated(int state)= 0;
	virtual FResult SetHotelModeUsbBrowseAllowed(Bool OnOff)= 0;
	virtual Bool GetHotelModeUsbBrowseAllowed(void)= 0;
	virtual void SetFactoryReset(void)= 0;
	virtual FResult SetPrimaryAudioLanguage(int language)= 0;
	virtual int GetPrimaryAudioLanguage(void)= 0;
	virtual FResult SetSecondaryAudioLanguage(int language)= 0;
	virtual int GetSecondaryAudioLanguage(void)= 0;
	virtual FResult SetPrimarySubtitleLanguage(int language)= 0;
	virtual int GetPrimarySubtitleLanguage(void)= 0;
	virtual FResult SetSecondarySubtitleLanguage(int language)= 0;
	virtual int GetSecondarySubtitleLanguage(void)= 0;
	virtual FResult SetPrimaryTxtLanguage(int language)= 0;
	virtual int GetPrimaryTxtLanguage(void)= 0;
	virtual FResult SetSecondaryTxtLanguage(int language)= 0;
	virtual int GetSecondaryTxtLanguage(void)= 0;
	virtual FResult SetHearingImpaired(Bool OnOff)= 0;
	virtual Bool GetHearingImpaired(void)= 0;
	virtual void SetHbbTv(Bool OnOff)= 0;
	virtual Bool GetHbbTv(void)= 0;
	virtual void AllowLastSourceUpdateInNVM(Bool enable)= 0;
	virtual void SetActiveChannelList(int ChannelList)= 0;
	virtual int GetActiveChannelList(void)= 0;
	virtual void SetMedium(int Medium)= 0;
	virtual int GetMedium(void)= 0;
	virtual void SetUserPinEntryStatus(Bool Status)= 0;
	virtual Bool GetUserPinEntryStatus(void)= 0;
};


#define IAppApiSystemSettings3Impl(Comp,intf)    \
virtual int intf ## _GetClockMode(void);\
virtual void intf ## _SetClockMode(int mode);\
virtual Bool intf ## _IsDstSettingControllable(void);\
virtual int intf ## _GetDst(void);\
virtual void intf ## _SetDst(Bool dst);\
virtual Bool intf ## _IsManualClockSettingControllable(void);\
virtual Bool intf ## _GetAutoPowerDownMode(void);\
virtual void intf ## _SetAutoPowerDownMode(Bool mode);\
virtual FResult intf ## _SetMenuLanguage(int language);\
virtual int intf ## _GetMenuLanguage(void);\
virtual FResult intf ## _SetInstallCountry(int country);\
virtual int intf ## _GetInstallCountry(void);\
virtual Bool intf ## _IsDateSet(void);\
virtual Bool intf ## _IsClockDefined(void);\
virtual Bool intf ## _IsLTOSet(void);\
virtual FResult intf ## _SetRCLock(Bool OnOff);\
virtual Bool intf ## _GetRCLockStatus(void);\
virtual void intf ## _OverrideRCLock(Bool Override);\
virtual FResult intf ## _SetKeyboardLock(Bool OnOff);\
virtual Bool intf ## _GetKeyboardLock(void);\
virtual FResult intf ## _SetBDSMode(Bool mode);\
virtual FResult intf ## _GetBDSMode(Bool * mode);\
virtual FResult intf ## _SetSXApplicationControl(Bool onoff);\
virtual Bool intf ## _GetSXApplicationControl(void);\
virtual FResult intf ## _SetBDSFeatureEnabled(Bool onoff);\
virtual Bool intf ## _GetBDSFeatureEnabled(void);\
virtual FResult intf ## _SetBDSPowerOnState(int state);\
virtual int intf ## _GetBDSPowerOnState(void);\
virtual FResult intf ## _SetOSDDisplay(Bool on_off);\
virtual Bool intf ## _GetOSDDisplay(void);\
virtual FResult intf ## _SetBdsWakeupSource(int src);\
virtual int intf ## _GetBdsWakeupSource(void);\
virtual FResult intf ## _SetHotelModeUsbBreakInAllowed(Bool onOff);\
virtual Bool intf ## _GetHotelModeUsbBreakInAllowed(void);\
virtual FResult intf ## _SetMaxAllowedVolume(int MaxVol);\
virtual int intf ## _GetMaxAllowedVolume(void);\
virtual FResult intf ## _SetEpgType(int epgType);\
virtual int intf ## _GetEpgType(void);\
virtual FResult intf ## _SetFactoryMode(Bool onoff);\
virtual Bool intf ## _GetFactoryMode(void);\
virtual FResult intf ## _SetShopHomeMode(int mode);\
virtual int intf ## _GetShopHomeMode(void);\
virtual FResult intf ## _SetVirginBit(Bool virginBit);\
virtual Bool intf ## _GetVirginBit(void);\
virtual FResult intf ## _SetClockCalibSource(int src);\
virtual int intf ## _GetClockCalibSource(void);\
virtual FResult intf ## _SetCurrentAVSource(int src);\
virtual int intf ## _GetCurrentAVSource(void);\
virtual FResult intf ## _SetPreferredAudioFormat(int format);\
virtual int intf ## _GetPreferredAudioFormat(void);\
virtual FResult intf ## _SetServiceMode(int mode);\
virtual int intf ## _GetServiceMode(void);\
virtual void intf ## _SetTimeZone(int timezone);\
virtual int intf ## _GetTimeZone(void);\
virtual Bool intf ## _IsTimeZoneSettingControllable(void);\
virtual Bool intf ## _IsTimeZoneAvailable(int timezone);\
virtual Nat32 intf ## _GetSystemVersionNumber(void);\
virtual FResult intf ## _SetOsdSize(int size);\
virtual int intf ## _GetOsdSize(void);\
virtual void intf ## _SetClockCaliberated(int state);\
virtual FResult intf ## _SetHotelModeUsbBrowseAllowed(Bool OnOff);\
virtual Bool intf ## _GetHotelModeUsbBrowseAllowed(void);\
virtual void intf ## _SetFactoryReset(void);\
virtual FResult intf ## _SetPrimaryAudioLanguage(int language);\
virtual int intf ## _GetPrimaryAudioLanguage(void);\
virtual FResult intf ## _SetSecondaryAudioLanguage(int language);\
virtual int intf ## _GetSecondaryAudioLanguage(void);\
virtual FResult intf ## _SetPrimarySubtitleLanguage(int language);\
virtual int intf ## _GetPrimarySubtitleLanguage(void);\
virtual FResult intf ## _SetSecondarySubtitleLanguage(int language);\
virtual int intf ## _GetSecondarySubtitleLanguage(void);\
virtual FResult intf ## _SetPrimaryTxtLanguage(int language);\
virtual int intf ## _GetPrimaryTxtLanguage(void);\
virtual FResult intf ## _SetSecondaryTxtLanguage(int language);\
virtual int intf ## _GetSecondaryTxtLanguage(void);\
virtual FResult intf ## _SetHearingImpaired(Bool OnOff);\
virtual Bool intf ## _GetHearingImpaired(void);\
virtual void intf ## _SetHbbTv(Bool OnOff);\
virtual Bool intf ## _GetHbbTv(void);\
virtual void intf ## _AllowLastSourceUpdateInNVM(Bool enable);\
virtual void intf ## _SetActiveChannelList(int ChannelList);\
virtual int intf ## _GetActiveChannelList(void);\
virtual void intf ## _SetMedium(int Medium);\
virtual int intf ## _GetMedium(void);\
virtual void intf ## _SetUserPinEntryStatus(Bool Status);\
virtual Bool intf ## _GetUserPinEntryStatus(void);\
class Comp ## _ ## intf : public IAppApiSystemSettings3 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetClockMode(void){ return m_parent->intf ## _GetClockMode();}\
virtual void SetClockMode(int mode){ return m_parent->intf ## _SetClockMode(mode);}\
virtual Bool IsDstSettingControllable(void){ return m_parent->intf ## _IsDstSettingControllable();}\
virtual int GetDst(void){ return m_parent->intf ## _GetDst();}\
virtual void SetDst(Bool dst){ return m_parent->intf ## _SetDst(dst);}\
virtual Bool IsManualClockSettingControllable(void){ return m_parent->intf ## _IsManualClockSettingControllable();}\
virtual Bool GetAutoPowerDownMode(void){ return m_parent->intf ## _GetAutoPowerDownMode();}\
virtual void SetAutoPowerDownMode(Bool mode){ return m_parent->intf ## _SetAutoPowerDownMode(mode);}\
virtual FResult SetMenuLanguage(int language){ return m_parent->intf ## _SetMenuLanguage(language);}\
virtual int GetMenuLanguage(void){ return m_parent->intf ## _GetMenuLanguage();}\
virtual FResult SetInstallCountry(int country){ return m_parent->intf ## _SetInstallCountry(country);}\
virtual int GetInstallCountry(void){ return m_parent->intf ## _GetInstallCountry();}\
virtual Bool IsDateSet(void){ return m_parent->intf ## _IsDateSet();}\
virtual Bool IsClockDefined(void){ return m_parent->intf ## _IsClockDefined();}\
virtual Bool IsLTOSet(void){ return m_parent->intf ## _IsLTOSet();}\
virtual FResult SetRCLock(Bool OnOff){ return m_parent->intf ## _SetRCLock(OnOff);}\
virtual Bool GetRCLockStatus(void){ return m_parent->intf ## _GetRCLockStatus();}\
virtual void OverrideRCLock(Bool Override){ return m_parent->intf ## _OverrideRCLock(Override);}\
virtual FResult SetKeyboardLock(Bool OnOff){ return m_parent->intf ## _SetKeyboardLock(OnOff);}\
virtual Bool GetKeyboardLock(void){ return m_parent->intf ## _GetKeyboardLock();}\
virtual FResult SetBDSMode(Bool mode){ return m_parent->intf ## _SetBDSMode(mode);}\
virtual FResult GetBDSMode(Bool * mode){ return m_parent->intf ## _GetBDSMode(mode);}\
virtual FResult SetSXApplicationControl(Bool onoff){ return m_parent->intf ## _SetSXApplicationControl(onoff);}\
virtual Bool GetSXApplicationControl(void){ return m_parent->intf ## _GetSXApplicationControl();}\
virtual FResult SetBDSFeatureEnabled(Bool onoff){ return m_parent->intf ## _SetBDSFeatureEnabled(onoff);}\
virtual Bool GetBDSFeatureEnabled(void){ return m_parent->intf ## _GetBDSFeatureEnabled();}\
virtual FResult SetBDSPowerOnState(int state){ return m_parent->intf ## _SetBDSPowerOnState(state);}\
virtual int GetBDSPowerOnState(void){ return m_parent->intf ## _GetBDSPowerOnState();}\
virtual FResult SetOSDDisplay(Bool on_off){ return m_parent->intf ## _SetOSDDisplay(on_off);}\
virtual Bool GetOSDDisplay(void){ return m_parent->intf ## _GetOSDDisplay();}\
virtual FResult SetBdsWakeupSource(int src){ return m_parent->intf ## _SetBdsWakeupSource(src);}\
virtual int GetBdsWakeupSource(void){ return m_parent->intf ## _GetBdsWakeupSource();}\
virtual FResult SetHotelModeUsbBreakInAllowed(Bool onOff){ return m_parent->intf ## _SetHotelModeUsbBreakInAllowed(onOff);}\
virtual Bool GetHotelModeUsbBreakInAllowed(void){ return m_parent->intf ## _GetHotelModeUsbBreakInAllowed();}\
virtual FResult SetMaxAllowedVolume(int MaxVol){ return m_parent->intf ## _SetMaxAllowedVolume(MaxVol);}\
virtual int GetMaxAllowedVolume(void){ return m_parent->intf ## _GetMaxAllowedVolume();}\
virtual FResult SetEpgType(int epgType){ return m_parent->intf ## _SetEpgType(epgType);}\
virtual int GetEpgType(void){ return m_parent->intf ## _GetEpgType();}\
virtual FResult SetFactoryMode(Bool onoff){ return m_parent->intf ## _SetFactoryMode(onoff);}\
virtual Bool GetFactoryMode(void){ return m_parent->intf ## _GetFactoryMode();}\
virtual FResult SetShopHomeMode(int mode){ return m_parent->intf ## _SetShopHomeMode(mode);}\
virtual int GetShopHomeMode(void){ return m_parent->intf ## _GetShopHomeMode();}\
virtual FResult SetVirginBit(Bool virginBit){ return m_parent->intf ## _SetVirginBit(virginBit);}\
virtual Bool GetVirginBit(void){ return m_parent->intf ## _GetVirginBit();}\
virtual FResult SetClockCalibSource(int src){ return m_parent->intf ## _SetClockCalibSource(src);}\
virtual int GetClockCalibSource(void){ return m_parent->intf ## _GetClockCalibSource();}\
virtual FResult SetCurrentAVSource(int src){ return m_parent->intf ## _SetCurrentAVSource(src);}\
virtual int GetCurrentAVSource(void){ return m_parent->intf ## _GetCurrentAVSource();}\
virtual FResult SetPreferredAudioFormat(int format){ return m_parent->intf ## _SetPreferredAudioFormat(format);}\
virtual int GetPreferredAudioFormat(void){ return m_parent->intf ## _GetPreferredAudioFormat();}\
virtual FResult SetServiceMode(int mode){ return m_parent->intf ## _SetServiceMode(mode);}\
virtual int GetServiceMode(void){ return m_parent->intf ## _GetServiceMode();}\
virtual void SetTimeZone(int timezone){ return m_parent->intf ## _SetTimeZone(timezone);}\
virtual int GetTimeZone(void){ return m_parent->intf ## _GetTimeZone();}\
virtual Bool IsTimeZoneSettingControllable(void){ return m_parent->intf ## _IsTimeZoneSettingControllable();}\
virtual Bool IsTimeZoneAvailable(int timezone){ return m_parent->intf ## _IsTimeZoneAvailable(timezone);}\
virtual Nat32 GetSystemVersionNumber(void){ return m_parent->intf ## _GetSystemVersionNumber();}\
virtual FResult SetOsdSize(int size){ return m_parent->intf ## _SetOsdSize(size);}\
virtual int GetOsdSize(void){ return m_parent->intf ## _GetOsdSize();}\
virtual void SetClockCaliberated(int state){ return m_parent->intf ## _SetClockCaliberated(state);}\
virtual FResult SetHotelModeUsbBrowseAllowed(Bool OnOff){ return m_parent->intf ## _SetHotelModeUsbBrowseAllowed(OnOff);}\
virtual Bool GetHotelModeUsbBrowseAllowed(void){ return m_parent->intf ## _GetHotelModeUsbBrowseAllowed();}\
virtual void SetFactoryReset(void){ return m_parent->intf ## _SetFactoryReset();}\
virtual FResult SetPrimaryAudioLanguage(int language){ return m_parent->intf ## _SetPrimaryAudioLanguage(language);}\
virtual int GetPrimaryAudioLanguage(void){ return m_parent->intf ## _GetPrimaryAudioLanguage();}\
virtual FResult SetSecondaryAudioLanguage(int language){ return m_parent->intf ## _SetSecondaryAudioLanguage(language);}\
virtual int GetSecondaryAudioLanguage(void){ return m_parent->intf ## _GetSecondaryAudioLanguage();}\
virtual FResult SetPrimarySubtitleLanguage(int language){ return m_parent->intf ## _SetPrimarySubtitleLanguage(language);}\
virtual int GetPrimarySubtitleLanguage(void){ return m_parent->intf ## _GetPrimarySubtitleLanguage();}\
virtual FResult SetSecondarySubtitleLanguage(int language){ return m_parent->intf ## _SetSecondarySubtitleLanguage(language);}\
virtual int GetSecondarySubtitleLanguage(void){ return m_parent->intf ## _GetSecondarySubtitleLanguage();}\
virtual FResult SetPrimaryTxtLanguage(int language){ return m_parent->intf ## _SetPrimaryTxtLanguage(language);}\
virtual int GetPrimaryTxtLanguage(void){ return m_parent->intf ## _GetPrimaryTxtLanguage();}\
virtual FResult SetSecondaryTxtLanguage(int language){ return m_parent->intf ## _SetSecondaryTxtLanguage(language);}\
virtual int GetSecondaryTxtLanguage(void){ return m_parent->intf ## _GetSecondaryTxtLanguage();}\
virtual FResult SetHearingImpaired(Bool OnOff){ return m_parent->intf ## _SetHearingImpaired(OnOff);}\
virtual Bool GetHearingImpaired(void){ return m_parent->intf ## _GetHearingImpaired();}\
virtual void SetHbbTv(Bool OnOff){ return m_parent->intf ## _SetHbbTv(OnOff);}\
virtual Bool GetHbbTv(void){ return m_parent->intf ## _GetHbbTv();}\
virtual void AllowLastSourceUpdateInNVM(Bool enable){ return m_parent->intf ## _AllowLastSourceUpdateInNVM(enable);}\
virtual void SetActiveChannelList(int ChannelList){ return m_parent->intf ## _SetActiveChannelList(ChannelList);}\
virtual int GetActiveChannelList(void){ return m_parent->intf ## _GetActiveChannelList();}\
virtual void SetMedium(int Medium){ return m_parent->intf ## _SetMedium(Medium);}\
virtual int GetMedium(void){ return m_parent->intf ## _GetMedium();}\
virtual void SetUserPinEntryStatus(Bool Status){ return m_parent->intf ## _SetUserPinEntryStatus(Status);}\
virtual Bool GetUserPinEntryStatus(void){ return m_parent->intf ## _GetUserPinEntryStatus();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
