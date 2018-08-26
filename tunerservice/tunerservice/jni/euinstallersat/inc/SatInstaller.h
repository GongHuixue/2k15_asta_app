/*
 * SatInstaller.h
 *
 *  Created on: Jun 12, 2013
 *      Author: mahesh.mathada
 */




#ifndef SATINSTALLER_H_
#define SATINSTALLER_H_
#include <jni.h>
#include "CS2Installer.h"
#include <SatInstallerJNI.h>
#include "IHsvSatelliteSettings.h"
#include <IHsvSatGlobalSettings.h>


class SatInstaller;

class SatInstaller: private IPlfApiDvbsTuning, private IPlfApiTuning,private IPlfApiSigStrengthMeas,
					   private IHsvSatelliteInstallationNotify, private ICesOperatorProfile, private IHsvSatGlobalSettings, 
					   private ICesCipCAMStatusNotify, private ICesCipCAMStatus
{
public:
	SatInstaller(){}
	SatInstaller(int token,jobject thisOject);
	~SatInstaller() { }

public:
	ProvidesInterface<IPlfApiDvbsTuning>	plfdvbs;
	ProvidesInterface<IPlfApiTuning>		plftune;
	ProvidesInterface<IPlfApiSigStrengthMeas> ssm;
	ProvidesInterface<IHsvSatelliteInstallationNotify> insN;
	ProvidesInterface<ICesOperatorProfile>	opins;
	ProvidesInterface<IHsvSatGlobalSettings>	globalsettings;
	ProvidesInterface<ICesCipCAMStatus>	cipStatus;

public:
	RequiresInterface<IHsvSatelliteInstallation> ins;
	RequiresInterface<IHsvPower> pow;
	//RequiresInterface<IPlfApiDiseqcNotify2> plfapidiseqcN2;
	RequiresInterface<IPlfApiTuningNotify>	plfapidvbsN;
	RequiresInterface<IHsvSatelliteSettings> dvbset;
	RequiresInterface<ICesOperatorProfileNotify> opinsN;
	RequiresInterface<ICesCipCAMStatusNotify>	cipStatusN;


public:

	//IHsvSatelliteInstallation
	int GetCurrentInstallationState(int * mode,int * state);
	FResult StartInstallation(int Source,int Lnb,int Mode);
	FResult StopInstallation(void);
	void ResetInstallation(void);
	int GetNumberOfTvChannelsFound(int Lnb);
	int GetNumberofRadioChannelsFound(int Lnb);
	int GetNumberOfTvChannelsRemoved(int Lnb);
	int GetNumberofRadioChannelsRemoved(int Lnb);
	FResult GetSatelliteName(int Lnb,Nat16 * SatelliteName);
	int GetNumberOfDigitalChannelsAdded(void);
	int GetNumberOfDigitalChannelsRemoved(void);
	int GetNumberOfDigitalChannelsMoved(void);
	FResult IdentifyPackagesAvailable(void);
	int GetTotalNumberOfPackagesFound(void);
	FResult GetPackageByIndex(int Index,HsvPackageStructure * Package);
	FResult SetUserPackageIndex(Nat32 PackageIndex);
	FResult GetUserPackageIndex(Nat32 * PackageIndex,Bool * IsPackage);
	FResult GetInstalledSatellites(int mode,HsvInstalledSatellites * SatelliteEntries);
	FResult InstallAddedSatellites(void);
	FResult ResetAddedSatellites(void);
	FResult RemoveSatelliteEntry(int LnbNumber);
	int GetSatelliteSignalStrength(int LnbNumber);
	int GetSatelliteSignalQuality(int LnbNumber);
	FResult LoadManualInstallationDefaultValues(void);
	FResult StoreManualInstallationValues(void);
	Nat32 GetAttribute(int Mode,int AttributeId);
	FResult SetAttribute(int Mode,int AttributeId,Nat32 Value);
	int GetScanProgressStatus(int Mode);
	FResult GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID);
	FResult GetPackageName(Nat32 PackageId,Nat16 * PackageName);
	void GetSIDetails(HsvSDMSIDataValues * SiValues);
	void EnableUnicable(int LnbNumber,Bool Enable);
	void StopSignalStrengthMeas(int LnbNumber);
	int GetSignalQuality(Nat32 Param);
	void StartSignalStrengthMeas(int LnbNumber);
	int GetSignalStrength(Nat32 param);
	FResult StartPredefinedListCopy(void);

	int GetFirstInstalledChannel();

	//plfapidvbsN
	int onScanningStandardDetected(int std, int freq);
	int onScanAborted(void);
	int onScanEnded(void);
	int onTuned(int tuningresult, int freq);
	
	void UpdateConfigXmlStrings(char* prescanXml,int prescansize,char* satelliteXml, int satelliteSize);
	void assetManager_init(AAssetManager* mgr);

	int GetNumberOfDatabaseRecords(int TSDataOnly);
	void GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData,int TSDataOnly);
	void AddTvpData(HsvPgdatTvProviderBlobData* TvpData, int Clear);
	void SyncUniqueIdToMW (HsvPgdatTvProviderBlobData* TvpData);
	void setDemuxHandle(long demuxhandle);

	//IPlfApiDvbsTuning
	virtual int getParams(HsvDvbSParams * par);
	virtual int configureLNB(HsvDvbSLNBConfig lnbcfg,HsvDvbSCustomLNBConfig customlnbcfg);
	virtual int configureUnicable(HsvDvbSUnicableConfig uccfg);
	virtual int setPolarization(int polarization);
	virtual int setSymbolRate(int srdetectmode,int symbolrate);
	virtual int setPLP(Nat8 plpid);
	virtual int setBand(int band);
	virtual int setLNBConnectionType(int connectiontype);
	virtual int setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots);

	//IPlfApiTuning
	virtual int tune(int freq,Bool finetune);
	virtual int getFreq(int * freq);
	virtual int scanStart(int startfreq,int endfreq,Bool scanforward);
	virtual int scanAbort(void);
	virtual int scanNext(void);


	// IPlfApiSigStrengthMeas
	virtual FResult GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval);
	virtual FResult Start(int winid,Bool * Avail,Nat32 * retval);
	virtual FResult Stop(int winid,Bool * Stopped,Nat32 * retval);
	virtual FResult GetMeasValid(int winid,Bool * Valid,Nat32 * retval);
	virtual FResult GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval);
	//IHsvSatelliteInstallationNotify
	virtual void OnEvent(int eventid,int value);

	// IHsvSatelliteSettings
	
	void LoadLnbParametersFromPersistent(void);
	FResult GetLnbSettings(HsvLnbSettings * LnbSettings);
	FResult SetLnbSettings(HsvLnbSettings * LnbSettings);
	FResult ResetLnbSettings(void);
	FResult GetDefaultValues(LnbSettingsEntry * LnbSettingsEntry);
	FResult ResetToDefaultLnbSettings(void);
	Nat32 GetAttribute(int AttributeId);
	FResult SetAttribute(int AttributeId,Nat32 Value);
	void SaveSatelliteSettingsToPersistent(void);
	FResult CommitSatelliteSettingsToPersistent(void);
	void ReLoadLnbParametersFromPersistent(void);

	//ICesOperatorProfile
	virtual void RequestStatusInfo(void);
	virtual void RequestNit(void);
	virtual void SendOperatorSearchStart(Op_Search_Settings searchstart);
	virtual void SendOpExit(void);
	virtual void SendOpTuneStatus(Op_Tune_Status tuneStatus);
	virtual void SendOpAck(void);
	virtual void SendOpSearchCancel(void);
	virtual void CacheOperatorData(void);
	virtual Op_ProfileStatusInfo GetStoredOperatorData(void);

	//ICesOperatorProfileNotify
	virtual void OnOpSearchStatus(Op_ProfileSearchStatus opStatus);
	virtual void OnOpStatusInfo(Op_ProfileStatusInfo statusInfo);
	virtual void OnOpNIT(Op_ProfileNitData nitData);
	virtual void OnOpTune(Op_ProfileTuneData tuneData);
	
	// IHsvSatGlobalSettings
	virtual void GetValuesFromGlobalSettings(int ID, int *Value);

	//ICesCipCAMStatusNotify
	virtual void OnEvent (CIPlusStatus_e status);
	
	virtual void StartTricolorRegionParsing ();
	virtual void SetTricolorRegionIndex (int indx);
	virtual void GetTricolorRegionNames (Nat16 **names, int *len);

	//ICesCipCAMStatus
	virtual void GetCipStatus (Nat8 * status);
	virtual void setPostCode(int pCodeLen ,char *pCode);

public:
	CS2Installer *sins;
	SatInstallerJNI *njni;

};

#endif /* SATINSTALLER_H_ */
