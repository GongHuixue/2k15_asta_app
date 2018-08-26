#ifndef IHSVTCSYSTEMSETTINGS_H
#define IHSVTCSYSTEMSETTINGS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTcSystemSettings
{
public:
	virtual ~IHsvTcSystemSettings(){}
	#define IHsvTcSystemSettings_AudioFormatStandard		((int)0 )
	#define IHsvTcSystemSettings_AudioFormatAdvanced		((int)1 )
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
	virtual void SetInstallCity(int city)= 0;
	virtual void SetSystemCity(int city)= 0;
	virtual int GetInstallCity(void)= 0;
	virtual int GetSystemCity(void)= 0;
	virtual void SetInstallRfSetting(int value)= 0;
	virtual void SetPbsMode(int value)= 0;
	virtual int GetPbsMode(void)= 0;
	virtual void SetServiceIDForChNameUpdate(int ServID)= 0;
	virtual int GetServiceIDForChNameUpdate(void)= 0;
	virtual void SetChUniqueIDForChNameUpdate(int ChUniID)= 0;
	virtual int GetChUniqueIDForChNameUpdate()= 0;
	virtual void SetUpdatedChannelName(Nat16 *pChName)= 0;
	virtual void GetUpdatedChannelName(Nat16 *pChName)= 0;
	virtual void SetUpdatedONID(int fiONID) = 0;
	virtual int GetUpdatedONID(void) = 0;
	virtual void SetUpdatedTsID(int fiTsID) = 0;
	virtual int GetUpdatedTsID(void) = 0;
	virtual int GetIsDVBT2Scan(void) = 0;
	virtual void SetIsDVBT2Scan(int abIsTrue) = 0;
	virtual int GetFocusedPlpId(void) = 0;
	virtual void SetFocusedPlpId(int aiPlpId) = 0;
	virtual void SetExtractScanResult(int abIsTrue) = 0;
	virtual int GetExtractScanResult(void) = 0;
	virtual void SetUpdatedSymbolRate(int aiSymRate) = 0;
	virtual int GetUpdatedSymbolRate(void) = 0;
	virtual int GetDvbtSetting(void) = 0;
	virtual int GetDvbcSetting(void) = 0;
};


#define IHsvTcSystemSettingsImpl(Comp,intf)    \
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
virtual void intf ## _SetInstallCity(int city);\
virtual void intf ## _SetSystemCity(int city);\
virtual int intf ## _GetInstallCity(void);\
virtual int intf ## _GetSystemCity(void);\
virtual void intf ## _SetInstallRfSetting(int value);\
virtual void intf ## _SetPbsMode(int value);\
virtual int intf ## _GetPbsMode(void);\
virtual void intf ## _SetServiceIDForChNameUpdate(int ServID);\
virtual int intf ## _GetServiceIDForChNameUpdate(void);\
virtual void intf ## _SetChUniqueIDForChNameUpdate(int ChUniID);\
virtual int intf ## _GetChUniqueIDForChNameUpdate(void);\
virtual void intf ## _SetUpdatedChannelName(Nat16* pChName);\
virtual void intf ## _GetUpdatedChannelName(Nat16* pChName);\
virtual void intf ## _SetUpdatedONID(int fiONID);\
virtual int intf ## _GetUpdatedONID(void);\
virtual void intf ## _SetUpdatedTsID(int fiTsID);\
virtual int intf ## _GetUpdatedTsID(void);\
virtual void intf ## _SetIsDVBT2Scan(int abIsTrue);\
virtual int intf ## _GetIsDVBT2Scan(void);\
virtual int intf ## _GetFocusedPlpId(void);\
virtual void intf ## _SetFocusedPlpId(int aiPlpId);\
virtual void intf ## _SetExtractScanResult(int abIsTrue);\
virtual int intf ## _GetExtractScanResult(void);\
virtual void intf ## _SetUpdatedSymbolRate(int aiSymRate);\
virtual int intf ## _GetUpdatedSymbolRate(void);\
virtual int intf ## _GetDvbtSetting(void);\
virtual int intf ## _GetDvbcSetting(void);\
class Comp ## _ ## intf : public IHsvTcSystemSettings \
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
virtual void SetInstallCity(int city){ return m_parent->intf ## _SetInstallCity(city);}\
virtual void SetSystemCity(int city){ return m_parent->intf ## _SetSystemCity(city);}\
virtual int GetInstallCity(void){ return m_parent->intf ## _GetInstallCity();}\
virtual int GetSystemCity(void){ return m_parent->intf ## _GetSystemCity();}\
virtual void SetInstallRfSetting(int value){ return m_parent->intf ## _SetInstallRfSetting(value);}\
virtual void SetPbsMode(int value){ return m_parent->intf ## _SetPbsMode(value);}\
virtual int GetPbsMode(void){ return m_parent->intf ## _GetPbsMode();}\
virtual void SetServiceIDForChNameUpdate(int ServID){ return m_parent->intf ## _SetServiceIDForChNameUpdate(ServID);}\
virtual int GetServiceIDForChNameUpdate(void){ return m_parent->intf ## _GetServiceIDForChNameUpdate();}\
virtual void SetChUniqueIDForChNameUpdate(int ChUniID){ return m_parent->intf ## _SetChUniqueIDForChNameUpdate(ChUniID);}\
virtual int GetChUniqueIDForChNameUpdate(void){ return m_parent->intf ## _GetChUniqueIDForChNameUpdate();}\
virtual void SetUpdatedChannelName(Nat16* pChName){ return m_parent->intf ## _SetUpdatedChannelName(pChName);}\
virtual void GetUpdatedChannelName(Nat16* pChName){ return m_parent->intf ## _GetUpdatedChannelName(pChName);}\
virtual void SetUpdatedONID(int fiONID){ return m_parent->intf ## _SetUpdatedONID(fiONID);}\
virtual int GetUpdatedONID(void){ return m_parent->intf ## _GetUpdatedONID();}\
virtual void SetUpdatedTsID(int fiTsID){ return m_parent->intf ## _SetUpdatedTsID(fiTsID);}\
virtual int GetUpdatedTsID(void){ return m_parent->intf ## _GetUpdatedTsID();}\
virtual void SetIsDVBT2Scan(int abIsTrue){ return m_parent->intf ## _SetIsDVBT2Scan(abIsTrue);}\
virtual int GetIsDVBT2Scan(void){ return m_parent->intf ## _GetIsDVBT2Scan();}\
virtual void SetFocusedPlpId(int aiPlpId){ return m_parent->intf ## _SetFocusedPlpId(aiPlpId);}\
virtual int GetFocusedPlpId(void){ return m_parent->intf ## _GetFocusedPlpId();}\
virtual void SetExtractScanResult(int abIsTrue){ return m_parent->intf ## _SetExtractScanResult(abIsTrue);}\
virtual int GetExtractScanResult(void){ return m_parent->intf ## _GetExtractScanResult();}\
virtual void SetUpdatedSymbolRate(int aiSymRate){ return m_parent->intf ## _SetUpdatedSymbolRate(aiSymRate);}\
virtual int GetUpdatedSymbolRate(void){ return m_parent->intf ## _GetUpdatedSymbolRate();}\
virtual int GetDvbtSetting(void){ return m_parent->intf ## _GetDvbtSetting();}\
virtual int GetDvbcSetting(void){ return m_parent->intf ## _GetDvbcSetting();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
