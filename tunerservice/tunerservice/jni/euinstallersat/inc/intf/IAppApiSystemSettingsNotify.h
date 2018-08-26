#ifndef IAPPAPISYSTEMSETTINGSNOTIFY_H
#define IAPPAPISYSTEMSETTINGSNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSystemSettingsNotify
{
public:
	virtual ~IAppApiSystemSettingsNotify(){}
	#define IAppApiSystemSettingsNotify_ViriginBitChanged		((int)0 )
	#define IAppApiSystemSettingsNotify_MenuLanguageChanged		((int)1 )
	#define IAppApiSystemSettingsNotify_InstalledCountryChanged		((int)2 )
	#define IAppApiSystemSettingsNotify_RCLockStatusChanged		((int)3 )
	#define IAppApiSystemSettingsNotify_LKBLockStatusChanged		((int)4 )
	#define IAppApiSystemSettingsNotify_BDSModeChanged		((int)5 )
	#define IAppApiSystemSettingsNotify_HMApplicatonControlStatusChanged		((int)6 )
	#define IAppApiSystemSettingsNotify_OsdDisplayStateChanged		((int)7 )
	#define IAppApiSystemSettingsNotify_EpgTypeChanged		((int)8 )
	#define IAppApiSystemSettingsNotify_FactoryModeChanged		((int)9 )
	#define IAppApiSystemSettingsNotify_ShopHomeLocationChanged		((int)10 )
	#define IAppApiSystemSettingsNotify_ServiceModeChanged		((int)11 )
	#define IAppApiSystemSettingsNotify_ClockModeChanged		((int)12 )
	#define IAppApiSystemSettingsNotify_DSTChanged		((int)13 )
	#define IAppApiSystemSettingsNotify_AudioFormatChanged		((int)14 )
	#define IAppApiSystemSettingsNotify_OsdSizeChanged		((int)15 )
	#define IAppApiSystemSettingsNotify_TimeZoneChanged		((int)16 )
	#define IAppApiSystemSettingsNotify_ClockCalibrated		((int)17 )
	#define IAppApiSystemSettingsNotify_ClockSrcCalibrated		((int)18 )
	#define IAppApiSystemSettingsNotify_FactoryReset		((int)19 )
	#define IAppApiSystemSettingsNotify_USBBreakInSupportChanged		((int)20 )
	#define IAppApiSystemSettingsNotify_AutoPowerDownModeChanged		((int)21 )
	#define IAppApiSystemSettingsNotify_HBBStatusChanged		((int)22 )
	#define IAppApiSystemSettingsNotify_SourceChanged		((int)23 )
	#define IAppApiSystemSettingsNotify_PrimaryAudioLanguageChanged		((int)24 )
	#define IAppApiSystemSettingsNotify_SecondaryAudioLanguageChanged		((int)25 )
	#define IAppApiSystemSettingsNotify_PrimarySubtitleLangaugeChanged		((int)26 )
	#define IAppApiSystemSettingsNotify_SecondarySubtitleLanguageChanged		((int)27 )
	#define IAppApiSystemSettingsNotify_PrimaryTxtLangaugeChanged		((int)28 )
	#define IAppApiSystemSettingsNotify_SecondaryTxtLanguageChanged		((int)29 )
	#define IAppApiSystemSettingsNotify_HearingImpairedChanged		((int)30 )
	#define IAppApiSystemSettingsNotify_ActiveChannelListChanged		((int)31 )
	#define IAppApiSystemSettingsNotify_MediumChanged		((int)32 )
	#define IAppApiSystemSettingsNotify_VisuallyImpairedStatusChanged		((int)33 )
	#define IAppApiSystemSettingsNotify_SubtitlePreferenceChanged		((int)34 )
	#define IAppApiSystemSettingsNotify_PinCodeChanged		((int)35 )
	#define IAppApiSystemSettingsNotify_TvFriendlyNameChanged		((int)36 )
	#define IAppApiSystemSettingsNotify_NextTimeOfChange		((int)37 )
	#define IAppApiSystemSettingsNotify_DMRInfoChanged		((int)41 )
	virtual void Notify(int value)= 0;
};


#define IAppApiSystemSettingsNotifyImpl(Comp,intf)    \
virtual void intf ## _Notify(int value);\
class Comp ## _ ## intf : public IAppApiSystemSettingsNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Notify(int value){ return m_parent->intf ## _Notify(value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
