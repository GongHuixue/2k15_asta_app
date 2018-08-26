#ifndef IHSVSYSTEMSETTINGSNOTIFYEX_H
#define IHSVSYSTEMSETTINGSNOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSystemSettingsNotifyEx
{
public:
	virtual ~IHsvSystemSettingsNotifyEx(){}
	virtual void OnLanguageChanged(int lang)= 0;
	virtual void OnCountryChanged(int country)= 0;
	virtual void OnMediumChanged(int medium)= 0;
	virtual void OnInstalledCountryChanged(int country)= 0;
	virtual void OnHearingImpairedTypeChanged(int lang)= 0;
	virtual void OnPreferredAudioFormatChanged(int format)= 0;
	virtual void OnPreferredPrimaryAudioLanguageChanged(int value)= 0;
	virtual void OnPreferredSecondaryAudioLanguageChanged(int value)= 0;
	virtual void OnPreferredPrimarySubtitleLanguageChanged(int value)= 0;
	virtual void OnPreferredSecondarySubtitleLanguageChanged(int value)= 0;
	virtual void OnPreferredPrimaryTxtLanguageChanged(int value)= 0;
	virtual void OnPreferredSecondaryTxtLanguageChanged(int value)= 0;
	virtual void OnCityChanged(int city)= 0;
};


#define IHsvSystemSettingsNotifyExImpl(Comp,intf)    \
virtual void intf ## _OnLanguageChanged(int lang);\
virtual void intf ## _OnCountryChanged(int country);\
virtual void intf ## _OnMediumChanged(int medium);\
virtual void intf ## _OnInstalledCountryChanged(int country);\
virtual void intf ## _OnHearingImpairedTypeChanged(int lang);\
virtual void intf ## _OnPreferredAudioFormatChanged(int format);\
virtual void intf ## _OnPreferredPrimaryAudioLanguageChanged(int value);\
virtual void intf ## _OnPreferredSecondaryAudioLanguageChanged(int value);\
virtual void intf ## _OnPreferredPrimarySubtitleLanguageChanged(int value);\
virtual void intf ## _OnPreferredSecondarySubtitleLanguageChanged(int value);\
virtual void intf ## _OnPreferredPrimaryTxtLanguageChanged(int value);\
virtual void intf ## _OnPreferredSecondaryTxtLanguageChanged(int value);\
virtual void intf ## _OnCityChanged(int city);\
class Comp ## _ ## intf : public IHsvSystemSettingsNotifyEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnLanguageChanged(int lang){ return m_parent->intf ## _OnLanguageChanged(lang);}\
virtual void OnCountryChanged(int country){ return m_parent->intf ## _OnCountryChanged(country);}\
virtual void OnMediumChanged(int medium){ return m_parent->intf ## _OnMediumChanged(medium);}\
virtual void OnInstalledCountryChanged(int country){ return m_parent->intf ## _OnInstalledCountryChanged(country);}\
virtual void OnHearingImpairedTypeChanged(int lang){ return m_parent->intf ## _OnHearingImpairedTypeChanged(lang);}\
virtual void OnPreferredAudioFormatChanged(int format){ return m_parent->intf ## _OnPreferredAudioFormatChanged(format);}\
virtual void OnPreferredPrimaryAudioLanguageChanged(int value){ return m_parent->intf ## _OnPreferredPrimaryAudioLanguageChanged(value);}\
virtual void OnPreferredSecondaryAudioLanguageChanged(int value){ return m_parent->intf ## _OnPreferredSecondaryAudioLanguageChanged(value);}\
virtual void OnPreferredPrimarySubtitleLanguageChanged(int value){ return m_parent->intf ## _OnPreferredPrimarySubtitleLanguageChanged(value);}\
virtual void OnPreferredSecondarySubtitleLanguageChanged(int value){ return m_parent->intf ## _OnPreferredSecondarySubtitleLanguageChanged(value);}\
virtual void OnPreferredPrimaryTxtLanguageChanged(int value){ return m_parent->intf ## _OnPreferredPrimaryTxtLanguageChanged(value);}\
virtual void OnPreferredSecondaryTxtLanguageChanged(int value){ return m_parent->intf ## _OnPreferredSecondaryTxtLanguageChanged(value);}\
virtual void OnCityChanged(int city){ return m_parent->intf ## _OnCityChanged(city);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
