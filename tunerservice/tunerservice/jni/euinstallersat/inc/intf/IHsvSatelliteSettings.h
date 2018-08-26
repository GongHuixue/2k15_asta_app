#ifndef IHSVSATELLITESETTINGS_H
#define IHSVSATELLITESETTINGS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteSettings
{
public:
	virtual ~IHsvSatelliteSettings(){}
	#define IHsvSatelliteSettings_AttributePackageId		((int)0 )
	#define IHsvSatelliteSettings_AttributePackageOnly		((int)1 )
	#define IHsvSatelliteSettings_AttributeAssetManager		((int)2 )
	#define IHsvSatelliteSettings_AttributeFrequency		((int)3 )
	#define IHsvSatelliteSettings_AttributePolarization		((int)4 )
	#define IHsvSatelliteSettings_AttributeSymbolRate		((int)5 )
	#define IHsvSatelliteSettings_AttributeSymbolRateMode	((int)6 )
	#define IHsvSatelliteSettings_AttributeCamCharSet		  ((int)7 )
	#define IHsvSatelliteSettings_AttributeOpProfileCICamId ((int)8)
	#define IHsvSatelliteSettings_AttributeCamNITVersion	  ((int)9 )
	#define IHsvSatelliteSettings_AttributeBouquetId		((int)10 )
	#define IHsvSatelliteSettings_AttributeRegionId			((int)11 )
	#define IHsvSatelliteSettings_AttributeTricolorRegionNameData		((int)12 )
	#define IHsvSatelliteSettings_AttributeFreesatHomingServiceData ((int)13)
	
	virtual void LoadLnbParametersFromPersistent(void)= 0;
	virtual FResult GetLnbSettings(HsvLnbSettings * LnbSettings)= 0;
	virtual FResult SetLnbSettings(HsvLnbSettings * LnbSettings)= 0;
	virtual FResult ResetLnbSettings(void)= 0;
	virtual FResult GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry)= 0;
	virtual FResult ResetToDefaultLnbSettings(void)= 0;
	virtual Nat32 GetAttribute(int AttributeId)= 0;
	virtual FResult SetAttribute(int AttributeId,Nat32 Value)= 0;
	virtual FResult SetPostcode(Nat8 PostcodeLen,Nat8 *Postcode)= 0;
	virtual FResult GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode) = 0;
	virtual void SaveSatelliteSettingsToPersistent(void)= 0;
	virtual FResult CommitSatelliteSettingsToPersistent(void)= 0;
	virtual void ReLoadLnbParametersFromPersistent(void)= 0;
};


#define IHsvSatelliteSettingsImpl(Comp,intf)    \
virtual void intf ## _LoadLnbParametersFromPersistent(void);\
virtual FResult intf ## _GetLnbSettings(HsvLnbSettings * LnbSettings);\
virtual FResult intf ## _SetLnbSettings(HsvLnbSettings * LnbSettings);\
virtual FResult intf ## _ResetLnbSettings(void);\
virtual FResult intf ## _GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry);\
virtual FResult intf ## _ResetToDefaultLnbSettings(void);\
virtual Nat32 intf ## _GetAttribute(int AttributeId);\
virtual FResult intf ## _SetAttribute(int AttributeId,Nat32 Value);\
virtual FResult intf##_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);\
virtual FResult intf##_GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode);\
virtual void intf ## _SaveSatelliteSettingsToPersistent(void);\
virtual FResult intf ## _CommitSatelliteSettingsToPersistent(void);\
virtual void intf ## _ReLoadLnbParametersFromPersistent(void);\
class Comp ## _ ## intf : public IHsvSatelliteSettings \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void LoadLnbParametersFromPersistent(void){ return m_parent->intf ## _LoadLnbParametersFromPersistent();}\
virtual FResult GetLnbSettings(HsvLnbSettings * LnbSettings){ return m_parent->intf ## _GetLnbSettings(LnbSettings);}\
virtual FResult SetLnbSettings(HsvLnbSettings * LnbSettings){ return m_parent->intf ## _SetLnbSettings(LnbSettings);}\
virtual FResult ResetLnbSettings(void){ return m_parent->intf ## _ResetLnbSettings();}\
virtual FResult GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry){ return m_parent->intf ## _GetDefaultValues(LnbSettingsEntry);}\
virtual FResult ResetToDefaultLnbSettings(void){ return m_parent->intf ## _ResetToDefaultLnbSettings();}\
virtual Nat32 GetAttribute(int AttributeId){ return m_parent->intf ## _GetAttribute(AttributeId);}\
virtual FResult SetAttribute(int AttributeId,Nat32 Value){ return m_parent->intf ## _SetAttribute(AttributeId,Value);}\
virtual FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode) { return m_parent->intf ## _SetPostcode(PostcodeLen,Postcode);}\
virtual FResult GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode) { return m_parent->intf ## _GetPostcode(PostcodeLen,Postcode);}\
virtual void SaveSatelliteSettingsToPersistent(void){ return m_parent->intf ## _SaveSatelliteSettingsToPersistent();}\
virtual FResult CommitSatelliteSettingsToPersistent(void){ return m_parent->intf ## _CommitSatelliteSettingsToPersistent();}\
virtual void ReLoadLnbParametersFromPersistent(void){ return m_parent->intf ## _ReLoadLnbParametersFromPersistent();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
