#ifndef  _CHSVDVBSFREESAT_MSETTINGS_H
#define  _CHSVDVBSFREESAT_MSETTINGS_H

#include <InfraGlobals.h>
#include <provreq.h>
#include<IHsvSatelliteSettings.h>
#include<IHsvErrorCodeEx.h>
#include<IHsvPower.h>
#include <CS2MwBase.h>

class CHsvDvbsFreesat_mSettings:public IHsvSatelliteSettings, public IHsvPower, public CS2MwBase
{
public:
	ProvidesInterface<IHsvPower>	isettingspow;
	ProvidesInterface<IHsvSatelliteSettings>	isettings;

public:
	RequiresInterface<IHsvErrorCodeEx>	err;

public:
	void Init(void);
	void TurnOn(void);
	void TurnOff(void);

	void LoadLnbParametersFromPersistent(void);
	FResult GetLnbSettings(HsvLnbSettings * LnbSettings);
	FResult SetLnbSettings(HsvLnbSettings * LnbSettings);
	FResult ResetLnbSettings(void);
	FResult GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry);
	FResult ResetToDefaultLnbSettings(void);
	Nat32 GetAttribute(int AttributeId);
	FResult SetAttribute(int AttributeId,Nat32 Value);
	FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);
	FResult GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode);
	void SaveSatelliteSettingsToPersistent(void);
	FResult CommitSatelliteSettingsToPersistent(void);
	void ReLoadLnbParametersFromPersistent(void);

	CHsvDvbsFreesat_mSettings()
	{
		isettingspow = this;
		isettings = this;
	}

	virtual ~CHsvDvbsFreesat_mSettings();

private:

	#define MAX_POSTCODE_LENGTH			(9)
	#define PRIMARY_VERSION   			(1)
	#define SECONDARY_VERSION 			(0)
	#define DEFAULT_FREESAT_HD_BID		(272)
	#define DEFAULT_FREESAT_HD_RID		(50)
	#define MAX_LINKAGE_SERVICE			(25)
	#define FREESAT_SETTING_FILE_PATH  "/data/data/org.droidtv.euinstallersat/freesatsetting.bin"
	typedef struct
	{
		Nat32 RecordSize;
		Nat32 PrimaryVersion;
		Nat32 SecondaryVersion;
		Nat16 BouquetId;
		Nat16 RegionId;
		Nat8 Postcode[MAX_POSTCODE_LENGTH];
		Nat8 PostcodeLen;
		HsvFreesatHomingServiceData HomingServiceDetails;
		Nat32 Crc;
	}HsvDvbsFreesatSettings;

	static HsvDvbsFreesatSettings s__FreesatDefaultData;
	static HsvDvbsFreesatSettings s__FreesatCurrentData;
	static HsvDvbsFreesatSettings s__FreesatPersistentData;

	Bool LoadDataFromPersistentFile (void);
	Nat32 CalculateCrc32( void* buffer, int size );

};

#endif
