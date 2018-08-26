#ifndef IHSVSATELLITEINSTALLATION_H
#define IHSVSATELLITEINSTALLATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteInstallation
{
public:
	virtual ~IHsvSatelliteInstallation(){}
	#define IHsvSatelliteInstallation_InstallationNone		((int)0x00 )
	#define IHsvSatelliteInstallation_InstallationPreScan		((int)0x01 )
	#define IHsvSatelliteInstallation_InstallationServiceScan		((int)0x02 )
	#define IHsvSatelliteInstallation_InstallationUpdate		((int)0x04 )
	#define IHsvSatelliteInstallation_InstallationManual		((int)0x08 )
	#define IHsvSatelliteInstallation_InstallationAddSatellite		((int)0x10 )
	#define IHsvSatelliteInstallation_InstallationAutomaticUpdate		((int)0x20 )
	#define IHsvSatelliteInstallation_InstallationBackground		((int)0x40 )
	#define IHsvSatelliteInstallation_InstallationMiniPrecan		((int)0x80 )
	#define IHsvSatelliteInstallation_InstallationBackgroundUpdate		((int)0x100 )
	#define IHsvSatelliteInstallation_InstallationPackageParsing		((int)0x200 )
	#define IHsvSatelliteInstallation_InstallationStateRegionScan		((int)0x400)
	#define IHsvSatelliteInstallation_InstallationSSbyUpdate			((int)0x800 )
	#define IHsvSatelliteInstallation_InstallationCamNit		((int)0x1000 )
	#define IHsvSatelliteInstallation_InstallationStateIdle		((int)0 )
	#define IHsvSatelliteInstallation_InstallationStateInProgress		((int)1 )
	#define IHsvSatelliteInstallation_InstallationStateSorting		((int)2 )
	#define IHsvSatelliteInstallation_AttributePackageId		((int)0 )
	#define IHsvSatelliteInstallation_AttributePackageOnly		((int)1 )
	#define IHsvSatelliteInstallation_AttributePackageGroup		((int)2 )
	#define IHsvSatelliteInstallation_AttributeAssetManager		((int)13 )
	#define IHsvSatelliteInstallation_AttributeFrequency		((int)9 )
	#define IHsvSatelliteInstallation_AttributePolarization     ((int)10)
	#define IHsvSatelliteInstallation_AttributeSymbolRate       ((int)11)
	#define IHsvSatelliteInstallation_AttributeSymbolRateMode   ((int)12)
	#define IHsvSatelliteInstallation_AttributeRegionIndex	   ((int)14)
	#define IHsvSatelliteInstallation_AttributeTimeOffset 	((int)15)
	#define IHsvSatelliteInstallation_AttributeChangeDate		((int)16)
	#define IHsvSatelliteInstallation_AttributeNextTimeOffset	((int)17)
	#define IHsvSatelliteInstallation_ManualInstallLnb		((int)3 )
	#define IHsvSatelliteInstallation_ManualInstallFreq		((int)4 )
	#define IHsvSatelliteInstallation_ManualInstallPolaraization		((int)5 )
	#define IHsvSatelliteInstallation_ManualInstallSymRate		((int)6 )
	#define IHsvSatelliteInstallation_ManualInstallSymRateMode		((int)7 )
	#define IHsvSatelliteInstallation_ManualInstallModulation		((int)8 )
	#define IHsvSatelliteInstallation_SatLnb1		((int)0x01 )
	#define IHsvSatelliteInstallation_SatLnb2		((int)0x02 )
	#define IHsvSatelliteInstallation_SatLnb3		((int)0x04 )
	#define IHsvSatelliteInstallation_SatLnb4		((int)0x08 )
	virtual int GetCurrentInstallationState(int * mode,int * state)= 0;
	virtual FResult StartInstallation(int Source,int Lnb,int Mode)= 0;
	virtual FResult StopInstallation(void)= 0;
	virtual void ResetInstallation(void)= 0;
	virtual int GetNumberOfTvChannelsFound(int Lnb)= 0;
	virtual int GetNumberofRadioChannelsFound(int Lnb)= 0;
	virtual int GetNumberOfTvChannelsRemoved(int Lnb)= 0;
	virtual int GetNumberofRadioChannelsRemoved(int Lnb)= 0;
	virtual FResult GetSatelliteName(int Lnb,Nat16 * SatelliteName)= 0;
	virtual int GetNumberOfDigitalChannelsAdded(void)= 0;
	virtual int GetNumberOfDigitalChannelsRemoved(void)= 0;
	virtual int GetNumberOfDigitalChannelsMoved(void)= 0;
	virtual FResult IdentifyPackagesAvailable(void)= 0;
	virtual int GetTotalNumberOfPackagesFound(void)= 0;
	virtual FResult GetPackageByIndex(int Index,HsvPackageStructure * Package)= 0;
	virtual FResult SetUserPackageIndex(Nat32 PackageIndex)= 0;
	virtual FResult GetUserPackageIndex(Nat32 * PackageIndex,Bool * IsPackage)= 0;
	virtual FResult GetInstalledSatellites(int mode,HsvInstalledSatellites * SatelliteEntries)= 0;
	virtual FResult InstallAddedSatellites(void)= 0;
	virtual FResult ResetAddedSatellites(void)= 0;
	virtual FResult RemoveSatelliteEntry(int LnbNumber)= 0;
	virtual int GetSatelliteSignalStrength(int LnbNumber)= 0;
	virtual int GetSatelliteSignalQuality(int LnbNumber)= 0;
	virtual FResult LoadManualInstallationDefaultValues(void)= 0;
	virtual FResult StoreManualInstallationValues(void)= 0;
	virtual Nat32 GetAttribute(int Mode,int AttributeId)= 0;
	virtual FResult SetAttribute(int Mode,int AttributeId,Nat32 Value)= 0;
	virtual FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)= 0;
	virtual int GetScanProgressStatus(int Mode)= 0;
	virtual FResult GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID)= 0;
	virtual FResult GetPackageName(Nat32 PackageId,Nat16 * PackageName)= 0;
	virtual void GetSIDetails(HsvSDMSIDataValues * SiValues)= 0;
	virtual void EnableUnicable(int LnbNumber,Bool Enable)= 0;
	virtual void StopSignalStrengthMeas(int LnbNumber)= 0;
	virtual int GetSignalQuality(Nat32 Param)= 0;
	virtual void StartSignalStrengthMeas(int LnbNumber)= 0;
	virtual int GetSignalStrength(Nat32 param)= 0;
	virtual FResult StartPredefinedListCopy(void)= 0;
	virtual int GetFirstInstalledChannel(void)= 0;
	virtual void UpdateConfigXmlStrings(char * PrescanXmlString,int PrescanXmlStringLen,char * SatellitePackageXmlString,int SatellitePackageXmlStringLen)= 0;
	virtual int GetNumberOfDatabaseRecords(int TSDataOnly)=0;
	virtual void GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)=0;
	virtual void AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear)=0;
	virtual void SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData)=0;
	virtual FResult StartTricolorRegionParsing (void) = 0;
	virtual FResult SetTricolorRegionIndex (int index) = 0;
	virtual FResult GetTricolorRegionNames (Nat16 **regionNames, int *len) = 0;
};


#define IHsvSatelliteInstallationImpl(Comp,intf)    \
virtual int intf ## _GetCurrentInstallationState(int * mode,int * state);\
virtual FResult intf ## _StartInstallation(int Source,int Lnb,int Mode);\
virtual FResult intf ## _StopInstallation(void);\
virtual void intf ## _ResetInstallation(void);\
virtual int intf ## _GetNumberOfTvChannelsFound(int Lnb);\
virtual int intf ## _GetNumberofRadioChannelsFound(int Lnb);\
virtual int intf ## _GetNumberOfTvChannelsRemoved(int Lnb);\
virtual int intf ## _GetNumberofRadioChannelsRemoved(int Lnb);\
virtual FResult intf ## _GetSatelliteName(int Lnb,Nat16 * SatelliteName);\
virtual int intf ## _GetNumberOfDigitalChannelsAdded(void);\
virtual int intf ## _GetNumberOfDigitalChannelsRemoved(void);\
virtual int intf ## _GetNumberOfDigitalChannelsMoved(void);\
virtual FResult intf ## _IdentifyPackagesAvailable(void);\
virtual int intf ## _GetTotalNumberOfPackagesFound(void);\
virtual FResult intf ## _GetPackageByIndex(int Index,HsvPackageStructure * Package);\
virtual FResult intf ## _SetUserPackageIndex(Nat32 PackageIndex);\
virtual FResult intf ## _GetUserPackageIndex(Nat32 * PackageIndex,Bool * IsPackage);\
virtual FResult intf ## _GetInstalledSatellites(int mode,HsvInstalledSatellites * SatelliteEntries);\
virtual FResult intf ## _InstallAddedSatellites(void);\
virtual FResult intf ## _ResetAddedSatellites(void);\
virtual FResult intf ## _RemoveSatelliteEntry(int LnbNumber);\
virtual int intf ## _GetSatelliteSignalStrength(int LnbNumber);\
virtual int intf ## _GetSatelliteSignalQuality(int LnbNumber);\
virtual FResult intf ## _LoadManualInstallationDefaultValues(void);\
virtual FResult intf ## _StoreManualInstallationValues(void);\
virtual Nat32 intf ## _GetAttribute(int Mode,int AttributeId);\
virtual FResult intf ## _SetAttribute(int Mode,int AttributeId,Nat32 Value);\
virtual FResult intf##_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);\
virtual int intf ## _GetScanProgressStatus(int Mode);\
virtual FResult intf ## _GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID);\
virtual FResult intf ## _GetPackageName(Nat32 PackageId,Nat16 * PackageName);\
virtual void intf ## _GetSIDetails(HsvSDMSIDataValues * SiValues);\
virtual void intf ## _EnableUnicable(int LnbNumber,Bool Enable);\
virtual void intf ## _StopSignalStrengthMeas(int LnbNumber);\
virtual int intf ## _GetSignalQuality(Nat32 Param);\
virtual void intf ## _StartSignalStrengthMeas(int LnbNumber);\
virtual int intf ## _GetSignalStrength(Nat32 param);\
virtual FResult intf ## _StartPredefinedListCopy(void);\
virtual int intf ## _GetFirstInstalledChannel(void);\
virtual void intf ## _UpdateConfigXmlStrings(char * PrescanXmlString,int PrescanXmlStringLen,char * SatellitePackageXmlString,int SatellitePackageXmlStringLen);\
virtual int intf ## _GetNumberOfDatabaseRecords(int TSDataOnly);\
virtual void intf ## _GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly);\
virtual void intf ## _AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear);\
virtual void intf ## _SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData);\
virtual FResult intf ## _StartTricolorRegionParsing ();\
virtual FResult intf ## _SetTricolorRegionIndex (int index);\
virtual FResult intf ## _GetTricolorRegionNames (Nat16 **regionNames, int *len);\
class Comp ## _ ## intf : public IHsvSatelliteInstallation \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetCurrentInstallationState(int * mode,int * state){ return m_parent->intf ## _GetCurrentInstallationState(mode,state);}\
virtual FResult StartInstallation(int Source,int Lnb,int Mode){ return m_parent->intf ## _StartInstallation(Source,Lnb,Mode);}\
virtual FResult StopInstallation(void){ return m_parent->intf ## _StopInstallation();}\
virtual void ResetInstallation(void){ return m_parent->intf ## _ResetInstallation();}\
virtual int GetNumberOfTvChannelsFound(int Lnb){ return m_parent->intf ## _GetNumberOfTvChannelsFound(Lnb);}\
virtual int GetNumberofRadioChannelsFound(int Lnb){ return m_parent->intf ## _GetNumberofRadioChannelsFound(Lnb);}\
virtual int GetNumberOfTvChannelsRemoved(int Lnb){ return m_parent->intf ## _GetNumberOfTvChannelsRemoved(Lnb);}\
virtual int GetNumberofRadioChannelsRemoved(int Lnb){ return m_parent->intf ## _GetNumberofRadioChannelsRemoved(Lnb);}\
virtual FResult GetSatelliteName(int Lnb,Nat16 * SatelliteName){ return m_parent->intf ## _GetSatelliteName(Lnb,SatelliteName);}\
virtual int GetNumberOfDigitalChannelsAdded(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsAdded();}\
virtual int GetNumberOfDigitalChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsRemoved();}\
virtual int GetNumberOfDigitalChannelsMoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsMoved();}\
virtual FResult IdentifyPackagesAvailable(void){ return m_parent->intf ## _IdentifyPackagesAvailable();}\
virtual int GetTotalNumberOfPackagesFound(void){ return m_parent->intf ## _GetTotalNumberOfPackagesFound();}\
virtual FResult GetPackageByIndex(int Index,HsvPackageStructure * Package){ return m_parent->intf ## _GetPackageByIndex(Index,Package);}\
virtual FResult SetUserPackageIndex(Nat32 PackageIndex){ return m_parent->intf ## _SetUserPackageIndex(PackageIndex);}\
virtual FResult GetUserPackageIndex(Nat32 * PackageIndex,Bool * IsPackage){ return m_parent->intf ## _GetUserPackageIndex(PackageIndex,IsPackage);}\
virtual FResult GetInstalledSatellites(int mode,HsvInstalledSatellites * SatelliteEntries){ return m_parent->intf ## _GetInstalledSatellites(mode,SatelliteEntries);}\
virtual FResult InstallAddedSatellites(void){ return m_parent->intf ## _InstallAddedSatellites();}\
virtual FResult ResetAddedSatellites(void){ return m_parent->intf ## _ResetAddedSatellites();}\
virtual FResult RemoveSatelliteEntry(int LnbNumber){ return m_parent->intf ## _RemoveSatelliteEntry(LnbNumber);}\
virtual int GetSatelliteSignalStrength(int LnbNumber){ return m_parent->intf ## _GetSatelliteSignalStrength(LnbNumber);}\
virtual int GetSatelliteSignalQuality(int LnbNumber){ return m_parent->intf ## _GetSatelliteSignalQuality(LnbNumber);}\
virtual FResult LoadManualInstallationDefaultValues(void){ return m_parent->intf ## _LoadManualInstallationDefaultValues();}\
virtual FResult StoreManualInstallationValues(void){ return m_parent->intf ## _StoreManualInstallationValues();}\
virtual Nat32 GetAttribute(int Mode,int AttributeId){ return m_parent->intf ## _GetAttribute(Mode,AttributeId);}\
virtual FResult SetAttribute(int Mode,int AttributeId,Nat32 Value){ return m_parent->intf ## _SetAttribute(Mode,AttributeId,Value);}\
virtual FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode) { return m_parent->intf ## _SetPostcode(PostcodeLen,Postcode);}\
virtual int GetScanProgressStatus(int Mode){ return m_parent->intf ## _GetScanProgressStatus(Mode);}\
virtual FResult GetSITableIds(Nat16 * NetworkID,Nat16 * BouquetID){ return m_parent->intf ## _GetSITableIds(NetworkID,BouquetID);}\
virtual FResult GetPackageName(Nat32 PackageId,Nat16 * PackageName){ return m_parent->intf ## _GetPackageName(PackageId,PackageName);}\
virtual void GetSIDetails(HsvSDMSIDataValues * SiValues){ return m_parent->intf ## _GetSIDetails(SiValues);}\
virtual void EnableUnicable(int LnbNumber,Bool Enable){ return m_parent->intf ## _EnableUnicable(LnbNumber,Enable);}\
virtual void StopSignalStrengthMeas(int LnbNumber){ return m_parent->intf ## _StopSignalStrengthMeas(LnbNumber);}\
virtual int GetSignalQuality(Nat32 Param){ return m_parent->intf ## _GetSignalQuality(Param);}\
virtual void StartSignalStrengthMeas(int LnbNumber){ return m_parent->intf ## _StartSignalStrengthMeas(LnbNumber);}\
virtual int GetSignalStrength(Nat32 param){ return m_parent->intf ## _GetSignalStrength(param);}\
virtual FResult StartPredefinedListCopy(void){ return m_parent->intf ## _StartPredefinedListCopy();}\
virtual int GetFirstInstalledChannel(void){ return m_parent->intf ## _GetFirstInstalledChannel();}\
virtual void UpdateConfigXmlStrings(char * PrescanXmlString,int PrescanXmlStringLen,char * SatellitePackageXmlString,int SatellitePackageXmlStringLen){ return m_parent->intf ## _UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen);}\
virtual int GetNumberOfDatabaseRecords(int TSDataOnly){ return m_parent->intf ## _GetNumberOfDatabaseRecords(TSDataOnly);}\
virtual void GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly){ return m_parent->intf ## _GetTvProviderBlobDataByIndex(Index,TvProviderBlobData,InstallerPrivateBlobData,TSDataOnly);}\
virtual void AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear){ return m_parent->intf ## _AddTvpData(TvpData,Clear);}\
virtual void SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData){ return m_parent->intf ## _SyncUniqueIdToMW (TvpData);}\
virtual FResult StartTricolorRegionParsing (void) {return m_parent->intf ## _StartTricolorRegionParsing (); }\
virtual FResult SetTricolorRegionIndex (int indx) {return m_parent->intf ## _SetTricolorRegionIndex (indx); }\
virtual FResult GetTricolorRegionNames (Nat16 **regionNames, int *len) {return m_parent->intf ## _GetTricolorRegionNames (regionNames, len); }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
