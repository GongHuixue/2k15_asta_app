#ifndef IHSVTCSYSTEMSETTINGSEX_H
#define IHSVTCSYSTEMSETTINGSEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTcSystemSettingsEx
{
public:
	virtual ~IHsvTcSystemSettingsEx(){}
	#define IHsvTcSystemSettingsEx_AudioFormatStandard		((int)0 )
	#define IHsvTcSystemSettingsEx_AudioFormatAdvanced		((int)1 )
	virtual void SetSystemLanguage(int lang)= 0;
	virtual int GetSystemLanguage(void)= 0;
	virtual void SetPreferredPrimaryAudioLanguage(int lang)= 0;
	virtual int GetPreferredPrimaryAudioLanguage(void)= 0;
	virtual int GetPreferredSecondarySubtitleLanguage(void)= 0;
	virtual void SetPreferredSecondarySubtitleLanguage(int lang)= 0;
	virtual int GetPreferredSecondaryAudioLanguage(void)= 0;
	virtual void SetPreferredSecondaryAudioLanguage(int lang)= 0;
	virtual void SetPreferredPrimarySubtitleLanguage(int lang)= 0;
	virtual int GetPreferredPrimarySubtitleLanguage(void)= 0;
	virtual void SetPreferredAudioFormat(int format)= 0;
	virtual int GetPreferredAudioFormat(void)= 0;
	virtual void SetPreferredPrimaryTxtLanguage(int lang)= 0;
	virtual int GetPreferredPrimaryTxtLanguage(void)= 0;
	virtual void SetPreferredSecondaryTxtLanguage(int lang)= 0;
	virtual int GetPreferredSecondaryTxtLanguage(void)= 0;
	virtual void SetSystemCountry(int country)= 0;
	virtual int GetSystemCountry(void)= 0;
	virtual void SetInstallCountry(int country)= 0;
	virtual int GetInstallCountry(void)= 0;
	virtual void SetSelectedMedium(int medium)= 0;
	virtual int GetSelectedMedium(void)= 0;
	virtual void SetInstalledMedium(int medium)= 0;
	virtual int GetInstalledMedium(void)= 0;
};


#define IHsvTcSystemSettingsExImpl(Comp,intf)    \
virtual void intf ## _SetSystemLanguage(int lang);\
virtual int intf ## _GetSystemLanguage(void);\
virtual void intf ## _SetPreferredPrimaryAudioLanguage(int lang);\
virtual int intf ## _GetPreferredPrimaryAudioLanguage(void);\
virtual int intf ## _GetPreferredSecondarySubtitleLanguage(void);\
virtual void intf ## _SetPreferredSecondarySubtitleLanguage(int lang);\
virtual int intf ## _GetPreferredSecondaryAudioLanguage(void);\
virtual void intf ## _SetPreferredSecondaryAudioLanguage(int lang);\
virtual void intf ## _SetPreferredPrimarySubtitleLanguage(int lang);\
virtual int intf ## _GetPreferredPrimarySubtitleLanguage(void);\
virtual void intf ## _SetPreferredAudioFormat(int format);\
virtual int intf ## _GetPreferredAudioFormat(void);\
virtual void intf ## _SetPreferredPrimaryTxtLanguage(int lang);\
virtual int intf ## _GetPreferredPrimaryTxtLanguage(void);\
virtual void intf ## _SetPreferredSecondaryTxtLanguage(int lang);\
virtual int intf ## _GetPreferredSecondaryTxtLanguage(void);\
virtual void intf ## _SetSystemCountry(int country);\
virtual int intf ## _GetSystemCountry(void);\
virtual void intf ## _SetInstallCountry(int country);\
virtual int intf ## _GetInstallCountry(void);\
virtual void intf ## _SetSelectedMedium(int medium);\
virtual int intf ## _GetSelectedMedium(void);\
virtual void intf ## _SetInstalledMedium(int medium);\
virtual int intf ## _GetInstalledMedium(void);\
class Comp ## _ ## intf : public IHsvTcSystemSettingsEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetSystemLanguage(int lang){ return m_parent->intf ## _SetSystemLanguage(lang);}\
virtual int GetSystemLanguage(void){ return m_parent->intf ## _GetSystemLanguage();}\
virtual void SetPreferredPrimaryAudioLanguage(int lang){ return m_parent->intf ## _SetPreferredPrimaryAudioLanguage(lang);}\
virtual int GetPreferredPrimaryAudioLanguage(void){ return m_parent->intf ## _GetPreferredPrimaryAudioLanguage();}\
virtual int GetPreferredSecondarySubtitleLanguage(void){ return m_parent->intf ## _GetPreferredSecondarySubtitleLanguage();}\
virtual void SetPreferredSecondarySubtitleLanguage(int lang){ return m_parent->intf ## _SetPreferredSecondarySubtitleLanguage(lang);}\
virtual int GetPreferredSecondaryAudioLanguage(void){ return m_parent->intf ## _GetPreferredSecondaryAudioLanguage();}\
virtual void SetPreferredSecondaryAudioLanguage(int lang){ return m_parent->intf ## _SetPreferredSecondaryAudioLanguage(lang);}\
virtual void SetPreferredPrimarySubtitleLanguage(int lang){ return m_parent->intf ## _SetPreferredPrimarySubtitleLanguage(lang);}\
virtual int GetPreferredPrimarySubtitleLanguage(void){ return m_parent->intf ## _GetPreferredPrimarySubtitleLanguage();}\
virtual void SetPreferredAudioFormat(int format){ return m_parent->intf ## _SetPreferredAudioFormat(format);}\
virtual int GetPreferredAudioFormat(void){ return m_parent->intf ## _GetPreferredAudioFormat();}\
virtual void SetPreferredPrimaryTxtLanguage(int lang){ return m_parent->intf ## _SetPreferredPrimaryTxtLanguage(lang);}\
virtual int GetPreferredPrimaryTxtLanguage(void){ return m_parent->intf ## _GetPreferredPrimaryTxtLanguage();}\
virtual void SetPreferredSecondaryTxtLanguage(int lang){ return m_parent->intf ## _SetPreferredSecondaryTxtLanguage(lang);}\
virtual int GetPreferredSecondaryTxtLanguage(void){ return m_parent->intf ## _GetPreferredSecondaryTxtLanguage();}\
virtual void SetSystemCountry(int country){ return m_parent->intf ## _SetSystemCountry(country);}\
virtual int GetSystemCountry(void){ return m_parent->intf ## _GetSystemCountry();}\
virtual void SetInstallCountry(int country){ return m_parent->intf ## _SetInstallCountry(country);}\
virtual int GetInstallCountry(void){ return m_parent->intf ## _GetInstallCountry();}\
virtual void SetSelectedMedium(int medium){ return m_parent->intf ## _SetSelectedMedium(medium);}\
virtual int GetSelectedMedium(void){ return m_parent->intf ## _GetSelectedMedium();}\
virtual void SetInstalledMedium(int medium){ return m_parent->intf ## _SetInstalledMedium(medium);}\
virtual int GetInstalledMedium(void){ return m_parent->intf ## _GetInstalledMedium();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
