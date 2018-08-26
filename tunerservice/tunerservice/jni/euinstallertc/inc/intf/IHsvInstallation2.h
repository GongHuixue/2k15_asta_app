#ifndef IHSVINSTALLATION2_H
#define IHSVINSTALLATION2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallation2
{
public:
	virtual ~IHsvInstallation2(){}
	#define IHsvInstallation2_InvalidChannel		((int)-1 )
	#define IHsvInstallation2_InvalidFrequency		((int)-1 )
	#define IHsvInstallation2_StIdle		((int)0 )
	#define IHsvInstallation2_StSourceSetupWait		((int)1 )
	#define IHsvInstallation2_StDigital		((int)2 )
	#define IHsvInstallation2_StAnalog		((int)3 )
	#define IHsvInstallation2_StPreSorting		((int)4 )
	#define IHsvInstallation2_StSorting		((int)5 )
	#define IHsvInstallation2_Terrestrial		((int)0 )
	#define IHsvInstallation2_Cable		((int)1 )
	#define IHsvInstallation2_Satellite		((int)2 )
	#define IHsvInstallation2_InstallationInPassAnalog		((int)1 )
	#define IHsvInstallation2_InstallationInDigitalPass		((int)3 )
	#define IHsvInstallation2_InstallationStateScrambledSearch		((int)3 )
	#define IHsvInstallation2_InstallationStateIdle		((int)0 )
	#define IHsvInstallation2_InstallationStateInProgress		((int)1 )
	#define IHsvInstallation2_InstallationStatePaused		((int)2 )
	#define IHsvInstallation2_InstallationModeNone		((int)0 )
	#define IHsvInstallation2_InstallationModeManual		((int)1 )
	#define IHsvInstallation2_InstallationModeAutomatic		((int)2 )
	#define IHsvInstallation2_InstallationModeBackground		((int)3 )
	#define IHsvInstallation2_InstallationModeImplicit		((int)4 )
	#define IHsvInstallation2_InstallationModeUpdate		((int)5 )
	#define IHsvInstallation2_InstallationModeWeakSignal		((int)6 )
	#define IHsvInstallation2_InstallationModeSingleChannel		((int)7 )
	#define IHsvInstallation2_InstallationModePreScan		((int)8 )
	#define IHsvInstallation2_InstallationModeDtr		((int)9 )
	#define IHsvInstallation2_InstallationModeCam		((int)10 )
	#define IHsvInstallation2_MaxChannel		((int)14 )
	#define IHsvInstallation2_ManualInstallationModeFrequency		((int)0 )
	#define IHsvInstallation2_InsTvSystemBg		((int)0 )
	#define IHsvInstallation2_InsTvSystemDk		((int)1 )
	#define IHsvInstallation2_InsTvSystemI		((int)2 )
	#define IHsvInstallation2_InsTvSystemL		((int)3 )
	#define IHsvInstallation2_InsTvSystemN		((int)4 )
	#define IHsvInstallation2_InsTvSystemM		((int)5 )
	#define IHsvInstallation2_InsTvSystemAuto		((int)6 )
	#define IHsvInstallation2_InsTvSystemBG_A2		((int)7 )
	#define IHsvInstallation2_InsTvSystemDK_A2		((int)8 )
	#define IHsvInstallation2_InsColourSystemPal		((int)0 )
	#define IHsvInstallation2_InsColurSystemSecam		((int)1 )
	#define IHsvInstallation2_InsColurSystemNtsc358		((int)2 )
	#define IHsvInstallation2_InsColurSystemNtsc443		((int)3 )
	#define IHsvInstallation2_InsColurSystemAuto		((int)4 )
	#define IHsvInstallation2_InsColurSystemInvalid		((int)5 )
	#define IHsvInstallation2_InsColurSystemNtscUnknown		((int)6 )
	#define IHsvInstallation2_InsAssm		((int)0 )
	#define IHsvInstallation2_InsVssm		((int)1 )
	#define IHsvInstallation2_InsQssm		((int)2 )
	#define IHsvInstallation2_InsSssm		((int)3 )
	virtual FResult StartInstallation(int source,int ptc,int mode)= 0;
	virtual FResult StopInstallation(void)= 0;
	virtual int GetNumberOfAnalogChannelsFound(void)= 0;
	virtual int GetNumberOfDigitalChannelsFound(void)= 0;
	virtual int GetNumberOfDigitalChannelsRemoved(void)= 0;
	virtual int GetInstallationProgress(void)= 0;
	virtual int GetInstallationStatus(void)= 0;
	virtual int GetInstallationMode(void)= 0;
	virtual Bool IsUpdateInstallationSupported(void)= 0;
	virtual void SetInstallRfSetting(int value)= 0;
	virtual void SetLCNSortingControl(int mode)= 0;
	virtual int GetLCNSortingControl(void)= 0;
	virtual void SetPbsMode(int value)= 0;
	virtual void PrepareChNameUpdate(int ChUniID, int ServID)= 0;
	virtual void GetUpdatedChannelName(Nat16* pChName)= 0;
	virtual int GetUpdatedONID(void) = 0;
	virtual int GetUpdatedTsID(void) = 0;
	virtual void SetIsDVBT2Scan(int abIsTrue) = 0;
	virtual void SetExtractScanResult(int abIsTrue) = 0;
	virtual int GetUpdatedSymbolRate(void) = 0;
	virtual void SetFocusedPlpId(int aiPlpId) = 0;
	virtual void SetInstallCountry(int country)= 0;
	virtual void SetSystemCountry(int country)= 0;
	virtual void GetFirstIntalledDigitalChannel(int * channelno)= 0;
	virtual void GetFirstIntalledAnalogueChannel(int * channelno)= 0;
	virtual void GetFirstIntalledRadioChannel(int * channelno)= 0;
	virtual void GetFirstInstalledChannel(int * channelno)= 0;
	virtual void GetNetworkNameForNetworkID(int networkID,Nat16 * NetworkName)= 0;
	virtual void GetListOfNetworkIDs(int * NumberOfEntries,int * NetworkIDList)= 0;
	virtual Bool IsValidNetworkId(int networkID)= 0;
	virtual void SetLowestNetworkId(int * networkID)= 0;
	virtual void SetManualFrequency(int frequency,int offset,Bool finetune)= 0;
	virtual void GetManualFrequency(int * frequency,int * offset,Bool * finetune)= 0;
	virtual void SetManualChannel(int channel,Bool finetune)= 0;
	virtual void GetManualChannel(int * channel,Bool * finetune)= 0;
	virtual Bool IsManualInstallationModeSupported(int mode)= 0;
	virtual void SetManualInstallationMode(int mode)= 0;
	virtual int GetManualInstallationMode(void)= 0;
	virtual void StoreManualInstallationValues(HsvChannel channel)= 0;
	virtual Bool AutoStoreManualInstallationValues(void)= 0;
	virtual Bool StartFrequencySearch(void)= 0;
	virtual FResult GetSigStrengthRange(int measmode,Nat32 * min,Nat32 * max)= 0;
	virtual Nat32 GetSignalstrength(int measmode)= 0;
	virtual FResult StoreWeakSignalInstallationChannel(void)= 0;
	virtual HsvChannel GetInstalledWeakSignalChannel(void)= 0;
	virtual Nat32 GetSignalQualityBer(void)= 0;
	virtual Bool IsFrequencySearchDirectionSupported(Bool searchup)= 0;
	virtual void SetFrequencySearchDirection(Bool searchup)= 0;
	virtual Bool GetFrequencySearchDirection(void)= 0;
	virtual int GetMinFrequency(void)= 0;
	virtual int GetMaxFrequency(void)= 0;
	virtual int GetTunerFrequency(void)= 0;
	virtual void SetTunerFrequency(int freq,Bool fineTune)= 0;
	virtual int GetFrequency2Channel(int chantbl,int frequency)= 0;
	virtual int GetChannel2CarrierFrequency(int chantbl,int channel)= 0;
	virtual int GetChannel2CentreFrequency(int chantbl,int channel)= 0;
	virtual int GetCurrentPass(void)= 0;
	virtual int GetNoOfPass(void)= 0;
	virtual Nat16 GetCurrentPassType(void)= 0;
	virtual Bool IsMediumSupported(int medium)= 0;
	virtual int GetMedium(void)= 0;
	virtual void SetMedium(int medium)= 0;
	virtual int GetInstalledMedium(void)= 0;
	virtual void SetInstalledMedium(int medium)= 0;
	virtual Bool IsTvSystemSupported(int tvsystem)= 0;
	virtual void SetTvSystem(int tvsystem)= 0;
	virtual int GetTvSystem(void)= 0;
	virtual Bool IsColorSystemSupported(int colorsystem)= 0;
	virtual void SetColorSystem(int colorsystem)= 0;
	virtual int GetColorSystem(void)= 0;
	virtual Bool IsValidPTC(int medium,int PTC)= 0;
	virtual int GetMinPTC(int medium)= 0;
	virtual int GetMaxPTC(int medium)= 0;
	virtual int GetLastPTCFound(void)= 0;
	virtual int GetNumberOfPTCsFound(void)= 0;
	virtual void StartSigStrMeas(int measmode)= 0;
	virtual void StopSigStrMeas(int measmode)= 0;
	virtual Bool IsSignalStrengthMeasurementValid(int measmode)= 0;
    virtual int GetActiveMedium (void) = 0;
	#define IHsvInstallation2_ScanNone		((Nat16)0x0 )
	#define IHsvInstallation2_ScanAnalog		((Nat16)0x1 )
	#define IHsvInstallation2_ScanDVBT		((Nat16)0x2 )
	#define IHsvInstallation2_ScanDVBC		((Nat16)0x4 )
	#define IHsvInstallation2_ScanDVBS		((Nat16)0x8 )
	#define IHsvInstallation2_AttributeScanMode		((Nat8)0 )
	#define IHsvInstallation2_AttributeSymbolRate		((Nat8)1 )
	#define IHsvInstallation2_AttributeNetworkId		((Nat8)2 )
	#define IHsvInstallation2_AttributeNetworkFreq		((Nat8)3 )
	#define IHsvInstallation2_AttributeModulation		((Nat8)4 )
	#define IHsvInstallation2_AttributeDigitalOption		((Nat8)5 )
	#define IHsvInstallation2_AttributeFreqStepSize		((Nat8)6 )
	#define IHsvInstallation2_AttributeCity		((Nat8)7 )
	#define IHsvInstallation2_AttributePrimaryRegion		((Nat8)8 )
	#define IHsvInstallation2_AttributeSecondaryRegion		((Nat8)9 )
	#define IHsvInstallation2_AttributeTertiaryRegion		((Nat8)10 )
	#define IHsvInstallation2_AttributeScrOrFTA		((Nat8)11 )
	#define IHsvInstallation2_AttributeNetworkOperator		((Nat8)12 )
	#define IHsvInstallation2_AttributeUpdateInstall		((Nat8)13 )
	#define IHsvInstallation2_AttributeAnalogEnabled		((Nat8)14 )
	#define IHsvInstallation2_AttributePersistentFile		((Nat8)14 )
	#define IHsvInstallation2_AttributeLCNSorting		((Nat8)15 )
	#define IHsvInstallation2_Attributecamcharset		((Nat8)16 )
	#define IHsvInstallation2_AttributeOpProfilecicamId		((int)17 )
	#define IHsvInstallation2_AttributeCamNITVersion		((int)18 )
	#define IHsvInstallation2_AttributeDualAnalogPass       ((int)19)
    #define IHsvInstallation2_AttributeDTTScanOnAnalog      ((int)20)
	#define IHsvInstallation2_AttributeLCNOption      		((int)21)
	#define IHsvInstallation2_AttributeFavoriteChannelId    ((int)22)
	#define IHsvInstallation2_QuickScan		((Nat8)0 )
	#define IHsvInstallation2_FullScan		((Nat8)1 )
	#define IHsvInstallation2_GridScan		((Nat8)2 )
	#define IHsvInstallation2_AutomaticValue		((int)0 )
	#define IHsvInstallation2_ManualValue		((int)1 )
	virtual Bool GetAttributeRange(int installationmode,int attribute,int * minValue,int * maxValue)= 0;
	virtual Bool SetAttributeMode(int installationmode,int attribute,int attributeMode)= 0;
	virtual Bool SetAttribute(int installationmode,int attribute,int value)= 0;
	virtual int GetAttributeMode(int installationmode,int attribute)= 0;
	virtual int GetAttribute(int installationmode,int attribute)= 0;
	virtual Bool IsAvailable(int installationmode,int attribute)= 0;
	virtual void ResetAttributeToDefault(int installationmode,int attribute)= 0;
	virtual void ResetAttributeToPersistent(int installationmode,int attribute)= 0;
	#define IHsvInstallation2_NitNone		((Nat8)0 )
	#define IHsvInstallation2_NitActual		((Nat8)0x1 )
	#define IHsvInstallation2_NitOther		((Nat8)0x2 )
	virtual int GetTargetNitType(Nat16 * NetworkId)= 0;
	virtual Bool IsNetworkUpdateDetected(void)= 0;
	#define IHsvInstallation2_DVBCStepSize1		((Nat32)1 )
	#define IHsvInstallation2_DVBCStepSize8		((Nat32)8 )
	virtual void Initialise(void)= 0;
	virtual FResult SkipInstallationScans(int ScanTypes)= 0;
	virtual Bool GetAltTSValues(Nat16 * ONID,Nat16 * TSID)= 0;
	virtual void SetUserSymbolRates(int installationmode,int * values,int len)= 0;
	virtual void GetUserSymbolRates(int installationmode,int * values,int * len)= 0;
	virtual void GetPredefinedSymbolRates(int installationmode,int * values,int * len)= 0;
	virtual int GetNetworkIDList(void)= 0;
	virtual void GetNetworkIDName(int index,Nat16 * NetworkName)= 0;
	virtual void GetChannelListIDName(int index,Nat16 *ChannelistName)=0;
	virtual void SetFavouriteNetworkID(int mode,int attrib,int index)= 0;
	virtual void SetFavouriteRegion(int mode,int index,HsvEnmRegionType RegionType)= 0;
	#define IHsvInstallation2_DvbTCAM			((Nat8)1 )
	#define IHsvInstallation2_None				((Nat8)0 )
	#define IHsvInstallation2_Ziggo				((Nat8)1 )
	#define IHsvInstallation2_UPC				((Nat8)2 )
	#define IHsvInstallation2_UnityMedia		((Nat8)3 )
	#define IHsvInstallation2_Kdg_SD				((Nat8)4 )
	#define IHsvInstallation2_Telenet			((Nat8)5 )
	#define IHsvInstallation2_DvbCCAM			((Nat8)6 )
	#define IHsvInstallation2_RCSRDS        	((Nat8)7 )
	#define IHsvInstallation2_Blizoo        	((Nat8)8 )
	#define IHsvInstallation2_CanalDigital      ((Nat8)9 )
	#define IHsvInstallation2_YouSee        	((Nat8)10 )
	#define IHsvInstallation2_Telemach        	((Nat8)11 )
	#define IHsvInstallation2_ComHem        	((Nat8)12 )
	#define IHsvInstallation2_Kdg_HD       		((Nat8)13 )
	virtual void SetUserSelectConflictService(int LcnIndex,int SvcIndex)= 0;
	virtual void ConflictsSelectionDone(Bool UserSelection)= 0;
	virtual void GetConflictServices(HsvConflictServicesData * ConflictList,int * NumRecords)= 0;
	virtual int GetInstallationVersion(void)= 0;
	virtual int GetInstallationState(void)= 0;
	virtual int GetPLPIds(int * PLPIds)= 0;
	virtual void GetRegionList(HsvNetworkRegionsData * RegionsData)= 0;
	virtual void UserSelectionDone(Bool UserSelection)= 0;
	virtual int GetFavouriteRegion(int mode,HsvEnmRegionType RegionType)= 0;
	virtual HsvStreamPriority GetStreamPriority(void)= 0;
	virtual void SetStreamPriority(HsvStreamPriority prio)= 0;
	virtual HsvConstellation GetConstellation(void)= 0;
	virtual Nat32 GetSymbolRate(void)= 0;
	virtual HsvHierarchyMode GetHierarchyMode(void)= 0;
	virtual void GetEpgBarkerMux(Nat16 * OnId,Nat16 * TsId)= 0;
	virtual Bool ZiggoNetworkDataSet(Bool ActionValue)= 0;
	virtual void ClearPersistent(void)= 0;
	virtual int GetNumberOfDatabaseRecords(int TSDataOnly)=0;
	virtual void GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly)=0;
	virtual int GetNumberOfChannelListIds()= 0;
	virtual int GetChannelListIdByIndex(int index)= 0;
	virtual void SetFavouriteChannelListId(int mode,int attrib,int index)= 0;
	virtual void GetSIDetails(HsvSDMSIDataValues* sivalues)= 0;
	virtual void AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear) = 0;
	virtual void SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData) = 0;
	virtual int GetLastAnalogPresetNumber() = 0;
};


#define IHsvInstallation2Impl(Comp,intf)    \
virtual FResult intf ## _StartInstallation(int source,int ptc,int mode);\
virtual FResult intf ## _StopInstallation(void);\
virtual int intf ## _GetNumberOfAnalogChannelsFound(void);\
virtual int intf ## _GetNumberOfDigitalChannelsFound(void);\
virtual int intf ## _GetNumberOfDigitalChannelsRemoved(void);\
virtual int intf ## _GetInstallationProgress(void);\
virtual int intf ## _GetInstallationStatus(void);\
virtual int intf ## _GetInstallationMode(void);\
virtual Bool intf ## _IsUpdateInstallationSupported(void);\
virtual void intf ## _SetInstallRfSetting(int value);\
virtual void intf ## _SetLCNSortingControl(int mode);\
virtual int intf ## _GetLCNSortingControl(void);\
virtual void intf ## _SetPbsMode(int value);\
virtual void intf ## _PrepareChNameUpdate(int ChUniID, int ServID);\
virtual void intf ## _GetUpdatedChannelName(Nat16* pChName);\
virtual int intf ## _GetUpdatedONID(void);\
virtual int intf ## _GetUpdatedTsID(void);\
virtual void intf ## _SetIsDVBT2Scan(int abIsTrue);\
virtual void intf ## _SetExtractScanResult(int abIsTrue);\
virtual int intf ## _GetUpdatedSymbolRate(void);\
virtual void intf ## _SetFocusedPlpId(int aiPlpId);\
virtual void intf ## _SetInstallCountry(int country);\
virtual void intf ## _SetSystemCountry(int country);\
virtual void intf ## _GetFirstIntalledDigitalChannel(int * channelno);\
virtual void intf ## _GetFirstIntalledAnalogueChannel(int * channelno);\
virtual void intf ## _GetFirstIntalledRadioChannel(int * channelno);\
virtual void intf ## _GetFirstInstalledChannel(int * channelno);\
virtual void intf ## _GetNetworkNameForNetworkID(int networkID,Nat16 * NetworkName);\
virtual void intf ## _GetListOfNetworkIDs(int * NumberOfEntries,int * NetworkIDList);\
virtual Bool intf ## _IsValidNetworkId(int networkID);\
virtual void intf ## _SetLowestNetworkId(int * networkID);\
virtual void intf ## _SetManualFrequency(int frequency,int offset,Bool finetune);\
virtual void intf ## _GetManualFrequency(int * frequency,int * offset,Bool * finetune);\
virtual void intf ## _SetManualChannel(int channel,Bool finetune);\
virtual void intf ## _GetManualChannel(int * channel,Bool * finetune);\
virtual Bool intf ## _IsManualInstallationModeSupported(int mode);\
virtual void intf ## _SetManualInstallationMode(int mode);\
virtual int intf ## _GetManualInstallationMode(void);\
virtual void intf ## _StoreManualInstallationValues(HsvChannel channel);\
virtual Bool intf ## _AutoStoreManualInstallationValues(void);\
virtual Bool intf ## _StartFrequencySearch(void);\
virtual FResult intf ## _GetSigStrengthRange(int measmode,Nat32 * min,Nat32 * max);\
virtual Nat32 intf ## _GetSignalstrength(int measmode);\
virtual FResult intf ## _StoreWeakSignalInstallationChannel(void);\
virtual HsvChannel intf ## _GetInstalledWeakSignalChannel(void);\
virtual Nat32 intf ## _GetSignalQualityBer(void);\
virtual Bool intf ## _IsFrequencySearchDirectionSupported(Bool searchup);\
virtual void intf ## _SetFrequencySearchDirection(Bool searchup);\
virtual Bool intf ## _GetFrequencySearchDirection(void);\
virtual int intf ## _GetMinFrequency(void);\
virtual int intf ## _GetMaxFrequency(void);\
virtual int intf ## _GetTunerFrequency(void);\
virtual void intf ## _SetTunerFrequency(int freq,Bool fineTune);\
virtual int intf ## _GetFrequency2Channel(int chantbl,int frequency);\
virtual int intf ## _GetChannel2CarrierFrequency(int chantbl,int channel);\
virtual int intf ## _GetChannel2CentreFrequency(int chantbl,int channel);\
virtual int intf ## _GetCurrentPass(void);\
virtual int intf ## _GetNoOfPass(void);\
virtual Nat16 intf ## _GetCurrentPassType(void);\
virtual Bool intf ## _IsMediumSupported(int medium);\
virtual int intf ## _GetMedium(void);\
virtual void intf ## _SetMedium(int medium);\
virtual int intf ## _GetInstalledMedium(void);\
virtual void intf ## _SetInstalledMedium(int medium);\
virtual Bool intf ## _IsTvSystemSupported(int tvsystem);\
virtual void intf ## _SetTvSystem(int tvsystem);\
virtual int intf ## _GetTvSystem(void);\
virtual Bool intf ## _IsColorSystemSupported(int colorsystem);\
virtual void intf ## _SetColorSystem(int colorsystem);\
virtual int intf ## _GetColorSystem(void);\
virtual Bool intf ## _IsValidPTC(int medium,int PTC);\
virtual int intf ## _GetMinPTC(int medium);\
virtual int intf ## _GetMaxPTC(int medium);\
virtual int intf ## _GetLastPTCFound(void);\
virtual int intf ## _GetNumberOfPTCsFound(void);\
virtual void intf ## _StartSigStrMeas(int measmode);\
virtual void intf ## _StopSigStrMeas(int measmode);\
virtual Bool intf ## _IsSignalStrengthMeasurementValid(int measmode);\
virtual Bool intf ## _GetAttributeRange(int installationmode,int attribute,int * minValue,int * maxValue);\
virtual Bool intf ## _SetAttributeMode(int installationmode,int attribute,int attributeMode);\
virtual Bool intf ## _SetAttribute(int installationmode,int attribute,int value);\
virtual int intf ## _GetAttributeMode(int installationmode,int attribute);\
virtual int intf ## _GetAttribute(int installationmode,int attribute);\
virtual Bool intf ## _IsAvailable(int installationmode,int attribute);\
virtual void intf ## _ResetAttributeToDefault(int installationmode,int attribute);\
virtual void intf ## _ResetAttributeToPersistent(int installationmode,int attribute);\
virtual int intf ## _GetTargetNitType(Nat16 * NetworkId);\
virtual Bool intf ## _IsNetworkUpdateDetected(void);\
virtual void intf ## _Initialise(void);\
virtual FResult intf ## _SkipInstallationScans(int ScanTypes);\
virtual Bool intf ## _GetAltTSValues(Nat16 * ONID,Nat16 * TSID);\
virtual void intf ## _SetUserSymbolRates(int installationmode,int * values,int len);\
virtual void intf ## _GetUserSymbolRates(int installationmode,int * values,int * len);\
virtual void intf ## _GetPredefinedSymbolRates(int installationmode,int * values,int * len);\
virtual int intf ## _GetNetworkIDList(void);\
virtual void intf ## _GetNetworkIDName(int index,Nat16 * NetworkName);\
virtual void intf ## _GetChannelListIDName(int index,Nat16 * ChannelistName);\
virtual void intf ## _SetFavouriteNetworkID(int mode,int attrib,int index);\
virtual void intf ## _SetFavouriteRegion(int mode,int index,HsvEnmRegionType RegionType);\
virtual void intf ## _SetUserSelectConflictService(int LcnIndex,int SvcIndex);\
virtual void intf ## _ConflictsSelectionDone(Bool UserSelection);\
virtual void intf ## _GetConflictServices(HsvConflictServicesData * ConflictList,int * NumRecords);\
virtual int intf ## _GetInstallationVersion(void);\
virtual int intf ## _GetInstallationState(void);\
virtual int intf ## _GetPLPIds(int * PLPIds);\
virtual void intf ## _GetRegionList(HsvNetworkRegionsData * RegionsData);\
virtual void intf ## _UserSelectionDone(Bool UserSelection);\
virtual int intf ## _GetFavouriteRegion(int mode,HsvEnmRegionType RegionType);\
virtual HsvStreamPriority intf ## _GetStreamPriority(void);\
virtual void intf ## _SetStreamPriority(HsvStreamPriority prio);\
virtual HsvConstellation intf ## _GetConstellation(void);\
virtual Nat32 intf ## _GetSymbolRate(void);\
virtual HsvHierarchyMode intf ## _GetHierarchyMode(void);\
virtual void intf ## _GetEpgBarkerMux(Nat16 * OnId,Nat16 * TsId);\
virtual Bool intf ## _ZiggoNetworkDataSet(Bool ActionValue);\
virtual void intf ## _ClearPersistent(void);\
virtual int intf ## _GetNumberOfDatabaseRecords(int TSDataOnly);\
virtual void intf ## _GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly);\
virtual int intf ## _GetNumberOfChannelListIds();\
virtual int intf ## _GetChannelListIdByIndex(int index);\
virtual void intf ## _SetFavouriteChannelListId(int mode,int attrib,int index);\
virtual void intf ## _GetSIDetails(HsvSDMSIDataValues* sivalues);\
virtual void intf ## _AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear);\
virtual void intf ## _SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData);\
virtual int intf ## _GetLastAnalogPresetNumber();\
virtual int intf ## _GetActiveMedium(void);\
class Comp ## _ ## intf : public IHsvInstallation2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult StartInstallation(int source,int ptc,int mode){ return m_parent->intf ## _StartInstallation(source,ptc,mode);}\
virtual FResult StopInstallation(void){ return m_parent->intf ## _StopInstallation();}\
virtual int GetNumberOfAnalogChannelsFound(void){ return m_parent->intf ## _GetNumberOfAnalogChannelsFound();}\
virtual int GetNumberOfDigitalChannelsFound(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsFound();}\
virtual int GetNumberOfDigitalChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsRemoved();}\
virtual int GetInstallationProgress(void){ return m_parent->intf ## _GetInstallationProgress();}\
virtual int GetInstallationStatus(void){ return m_parent->intf ## _GetInstallationStatus();}\
virtual int GetInstallationMode(void){ return m_parent->intf ## _GetInstallationMode();}\
virtual Bool IsUpdateInstallationSupported(void){ return m_parent->intf ## _IsUpdateInstallationSupported();}\
virtual void SetInstallRfSetting(int value){ return m_parent->intf ## _SetInstallRfSetting(value);}\
virtual void SetLCNSortingControl(int mode){ return m_parent->intf ## _SetLCNSortingControl(mode);}\
virtual int GetLCNSortingControl(void){ return m_parent->intf ## _GetLCNSortingControl();}\
virtual void SetPbsMode(int value){ return m_parent->intf ## _SetPbsMode(value);}\
virtual void PrepareChNameUpdate(int ChUniID, int ServID){ return m_parent->intf ## _PrepareChNameUpdate(ChUniID,ServID);}\
virtual void GetUpdatedChannelName(Nat16* pChName){ return m_parent->intf ## _GetUpdatedChannelName(pChName);}\
virtual void SetIsDVBT2Scan(int abIsTrue){return m_parent->intf ## _SetIsDVBT2Scan(abIsTrue);}\
virtual void SetExtractScanResult(int abIsTrue){return m_parent->intf ## _SetExtractScanResult(abIsTrue);}\
virtual int GetUpdatedSymbolRate(void){return m_parent->intf ## _GetUpdatedSymbolRate();}\
virtual void SetFocusedPlpId(int aiPlpId){return m_parent->intf ## _SetFocusedPlpId(aiPlpId);}\
virtual int GetUpdatedONID(){return m_parent->intf ## _GetUpdatedONID();}\
virtual int GetUpdatedTsID(){return m_parent->intf ## _GetUpdatedTsID();}\
virtual void SetInstallCountry(int country){ return m_parent->intf ## _SetInstallCountry(country);}\
virtual void SetSystemCountry(int country){ return m_parent->intf ## _SetSystemCountry(country);}\
virtual void GetFirstIntalledDigitalChannel(int * channelno){ return m_parent->intf ## _GetFirstIntalledDigitalChannel(channelno);}\
virtual void GetFirstIntalledAnalogueChannel(int * channelno){ return m_parent->intf ## _GetFirstIntalledAnalogueChannel(channelno);}\
virtual void GetFirstIntalledRadioChannel(int * channelno){ return m_parent->intf ## _GetFirstIntalledRadioChannel(channelno);}\
virtual void GetFirstInstalledChannel(int * channelno){ return m_parent->intf ## _GetFirstInstalledChannel(channelno);}\
virtual void GetNetworkNameForNetworkID(int networkID,Nat16 * NetworkName){ return m_parent->intf ## _GetNetworkNameForNetworkID(networkID,NetworkName);}\
virtual void GetListOfNetworkIDs(int * NumberOfEntries,int * NetworkIDList){ return m_parent->intf ## _GetListOfNetworkIDs(NumberOfEntries,NetworkIDList);}\
virtual Bool IsValidNetworkId(int networkID){ return m_parent->intf ## _IsValidNetworkId(networkID);}\
virtual void SetLowestNetworkId(int * networkID){ return m_parent->intf ## _SetLowestNetworkId(networkID);}\
virtual void SetManualFrequency(int frequency,int offset,Bool finetune){ return m_parent->intf ## _SetManualFrequency(frequency,offset,finetune);}\
virtual void GetManualFrequency(int * frequency,int * offset,Bool * finetune){ return m_parent->intf ## _GetManualFrequency(frequency,offset,finetune);}\
virtual void SetManualChannel(int channel,Bool finetune){ return m_parent->intf ## _SetManualChannel(channel,finetune);}\
virtual void GetManualChannel(int * channel,Bool * finetune){ return m_parent->intf ## _GetManualChannel(channel,finetune);}\
virtual Bool IsManualInstallationModeSupported(int mode){ return m_parent->intf ## _IsManualInstallationModeSupported(mode);}\
virtual void SetManualInstallationMode(int mode){ return m_parent->intf ## _SetManualInstallationMode(mode);}\
virtual int GetManualInstallationMode(void){ return m_parent->intf ## _GetManualInstallationMode();}\
virtual void StoreManualInstallationValues(HsvChannel channel){ return m_parent->intf ## _StoreManualInstallationValues(channel);}\
virtual Bool AutoStoreManualInstallationValues(void){ return m_parent->intf ## _AutoStoreManualInstallationValues();}\
virtual Bool StartFrequencySearch(void){ return m_parent->intf ## _StartFrequencySearch();}\
virtual FResult GetSigStrengthRange(int measmode,Nat32 * min,Nat32 * max){ return m_parent->intf ## _GetSigStrengthRange(measmode,min,max);}\
virtual Nat32 GetSignalstrength(int measmode){ return m_parent->intf ## _GetSignalstrength(measmode);}\
virtual FResult StoreWeakSignalInstallationChannel(void){ return m_parent->intf ## _StoreWeakSignalInstallationChannel();}\
virtual HsvChannel GetInstalledWeakSignalChannel(void){ return m_parent->intf ## _GetInstalledWeakSignalChannel();}\
virtual Nat32 GetSignalQualityBer(void){ return m_parent->intf ## _GetSignalQualityBer();}\
virtual Bool IsFrequencySearchDirectionSupported(Bool searchup){ return m_parent->intf ## _IsFrequencySearchDirectionSupported(searchup);}\
virtual void SetFrequencySearchDirection(Bool searchup){ return m_parent->intf ## _SetFrequencySearchDirection(searchup);}\
virtual Bool GetFrequencySearchDirection(void){ return m_parent->intf ## _GetFrequencySearchDirection();}\
virtual int GetMinFrequency(void){ return m_parent->intf ## _GetMinFrequency();}\
virtual int GetMaxFrequency(void){ return m_parent->intf ## _GetMaxFrequency();}\
virtual int GetTunerFrequency(void){ return m_parent->intf ## _GetTunerFrequency();}\
virtual void SetTunerFrequency(int freq,Bool fineTune){ return m_parent->intf ## _SetTunerFrequency(freq,fineTune);}\
virtual int GetFrequency2Channel(int chantbl,int frequency){ return m_parent->intf ## _GetFrequency2Channel(chantbl,frequency);}\
virtual int GetChannel2CarrierFrequency(int chantbl,int channel){ return m_parent->intf ## _GetChannel2CarrierFrequency(chantbl,channel);}\
virtual int GetChannel2CentreFrequency(int chantbl,int channel){ return m_parent->intf ## _GetChannel2CentreFrequency(chantbl,channel);}\
virtual int GetCurrentPass(void){ return m_parent->intf ## _GetCurrentPass();}\
virtual int GetNoOfPass(void){ return m_parent->intf ## _GetNoOfPass();}\
virtual Nat16 GetCurrentPassType(void){ return m_parent->intf ## _GetCurrentPassType();}\
virtual Bool IsMediumSupported(int medium){ return m_parent->intf ## _IsMediumSupported(medium);}\
virtual int GetMedium(void){ return m_parent->intf ## _GetMedium();}\
virtual void SetMedium(int medium){ return m_parent->intf ## _SetMedium(medium);}\
virtual int GetInstalledMedium(void){ return m_parent->intf ## _GetInstalledMedium();}\
virtual void SetInstalledMedium(int medium){ return m_parent->intf ## _SetInstalledMedium(medium);}\
virtual Bool IsTvSystemSupported(int tvsystem){ return m_parent->intf ## _IsTvSystemSupported(tvsystem);}\
virtual void SetTvSystem(int tvsystem){ return m_parent->intf ## _SetTvSystem(tvsystem);}\
virtual int GetTvSystem(void){ return m_parent->intf ## _GetTvSystem();}\
virtual Bool IsColorSystemSupported(int colorsystem){ return m_parent->intf ## _IsColorSystemSupported(colorsystem);}\
virtual void SetColorSystem(int colorsystem){ return m_parent->intf ## _SetColorSystem(colorsystem);}\
virtual int GetColorSystem(void){ return m_parent->intf ## _GetColorSystem();}\
virtual Bool IsValidPTC(int medium,int PTC){ return m_parent->intf ## _IsValidPTC(medium,PTC);}\
virtual int GetMinPTC(int medium){ return m_parent->intf ## _GetMinPTC(medium);}\
virtual int GetMaxPTC(int medium){ return m_parent->intf ## _GetMaxPTC(medium);}\
virtual int GetLastPTCFound(void){ return m_parent->intf ## _GetLastPTCFound();}\
virtual int GetNumberOfPTCsFound(void){ return m_parent->intf ## _GetNumberOfPTCsFound();}\
virtual void StartSigStrMeas(int measmode){ return m_parent->intf ## _StartSigStrMeas(measmode);}\
virtual void StopSigStrMeas(int measmode){ return m_parent->intf ## _StopSigStrMeas(measmode);}\
virtual Bool IsSignalStrengthMeasurementValid(int measmode){ return m_parent->intf ## _IsSignalStrengthMeasurementValid(measmode);}\
virtual Bool GetAttributeRange(int installationmode,int attribute,int * minValue,int * maxValue){ return m_parent->intf ## _GetAttributeRange(installationmode,attribute,minValue,maxValue);}\
virtual Bool SetAttributeMode(int installationmode,int attribute,int attributeMode){ return m_parent->intf ## _SetAttributeMode(installationmode,attribute,attributeMode);}\
virtual Bool SetAttribute(int installationmode,int attribute,int value){ return m_parent->intf ## _SetAttribute(installationmode,attribute,value);}\
virtual int GetAttributeMode(int installationmode,int attribute){ return m_parent->intf ## _GetAttributeMode(installationmode,attribute);}\
virtual int GetAttribute(int installationmode,int attribute){ return m_parent->intf ## _GetAttribute(installationmode,attribute);}\
virtual Bool IsAvailable(int installationmode,int attribute){ return m_parent->intf ## _IsAvailable(installationmode,attribute);}\
virtual void ResetAttributeToDefault(int installationmode,int attribute){ return m_parent->intf ## _ResetAttributeToDefault(installationmode,attribute);}\
virtual void ResetAttributeToPersistent(int installationmode,int attribute){ return m_parent->intf ## _ResetAttributeToPersistent(installationmode,attribute);}\
virtual int GetTargetNitType(Nat16 * NetworkId){ return m_parent->intf ## _GetTargetNitType(NetworkId);}\
virtual Bool IsNetworkUpdateDetected(void){ return m_parent->intf ## _IsNetworkUpdateDetected();}\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual FResult SkipInstallationScans(int ScanTypes){ return m_parent->intf ## _SkipInstallationScans(ScanTypes);}\
virtual Bool GetAltTSValues(Nat16 * ONID,Nat16 * TSID){ return m_parent->intf ## _GetAltTSValues(ONID,TSID);}\
virtual void SetUserSymbolRates(int installationmode,int * values,int len){ return m_parent->intf ## _SetUserSymbolRates(installationmode,values,len);}\
virtual void GetUserSymbolRates(int installationmode,int * values,int * len){ return m_parent->intf ## _GetUserSymbolRates(installationmode,values,len);}\
virtual void GetPredefinedSymbolRates(int installationmode,int * values,int * len){ return m_parent->intf ## _GetPredefinedSymbolRates(installationmode,values,len);}\
virtual int GetNetworkIDList(void){ return m_parent->intf ## _GetNetworkIDList();}\
virtual void GetNetworkIDName(int index,Nat16 * NetworkName){ return m_parent->intf ## _GetNetworkIDName(index,NetworkName);}\
virtual void GetChannelListIDName(int index,Nat16 * ChannelistName){ return m_parent->intf ## _GetChannelListIDName(index,ChannelistName);}\
virtual void SetFavouriteNetworkID(int mode,int attrib,int index){ return m_parent->intf ## _SetFavouriteNetworkID(mode,attrib,index);}\
virtual void SetFavouriteRegion(int mode,int index,HsvEnmRegionType RegionType){ return m_parent->intf ## _SetFavouriteRegion(mode,index,RegionType);}\
virtual void SetUserSelectConflictService(int LcnIndex,int SvcIndex){ return m_parent->intf ## _SetUserSelectConflictService(LcnIndex,SvcIndex);}\
virtual void ConflictsSelectionDone(Bool UserSelection){ return m_parent->intf ## _ConflictsSelectionDone(UserSelection);}\
virtual void GetConflictServices(HsvConflictServicesData * ConflictList,int * NumRecords){ return m_parent->intf ## _GetConflictServices(ConflictList,NumRecords);}\
virtual int GetInstallationVersion(void){ return m_parent->intf ## _GetInstallationVersion();}\
virtual int GetInstallationState(void){ return m_parent->intf ## _GetInstallationState();}\
virtual int GetPLPIds(int * PLPIds){ return m_parent->intf ## _GetPLPIds(PLPIds);}\
virtual void GetRegionList(HsvNetworkRegionsData * RegionsData){ return m_parent->intf ## _GetRegionList(RegionsData);}\
virtual void UserSelectionDone(Bool UserSelection){ return m_parent->intf ## _UserSelectionDone(UserSelection);}\
virtual int GetFavouriteRegion(int mode,HsvEnmRegionType RegionType){ return m_parent->intf ## _GetFavouriteRegion(mode,RegionType);}\
virtual HsvStreamPriority GetStreamPriority(void){ return m_parent->intf ## _GetStreamPriority();}\
virtual void SetStreamPriority(HsvStreamPriority prio){ return m_parent->intf ## _SetStreamPriority(prio);}\
virtual HsvConstellation GetConstellation(void){ return m_parent->intf ## _GetConstellation();}\
virtual Nat32 GetSymbolRate(void){ return m_parent->intf ## _GetSymbolRate();}\
virtual HsvHierarchyMode GetHierarchyMode(void){ return m_parent->intf ## _GetHierarchyMode();}\
virtual void GetEpgBarkerMux(Nat16 * OnId,Nat16 * TsId){ return m_parent->intf ## _GetEpgBarkerMux(OnId,TsId);}\
virtual Bool ZiggoNetworkDataSet(Bool ActionValue){ return m_parent->intf ## _ZiggoNetworkDataSet(ActionValue);}\
virtual void ClearPersistent(void){ return m_parent->intf ## _ClearPersistent();}\
virtual int GetNumberOfDatabaseRecords(int TSDataOnly){ return m_parent->intf ## _GetNumberOfDatabaseRecords(TSDataOnly);}\
virtual void GetTvProviderBlobDataByIndex(int Index, Address TvProviderBlobData, Address InstallerPrivateBlobData, int TSDataOnly){ return m_parent->intf ## _GetTvProviderBlobDataByIndex(Index,TvProviderBlobData,InstallerPrivateBlobData,TSDataOnly);}\
virtual int GetNumberOfChannelListIds(){ return m_parent->intf ## _GetNumberOfChannelListIds();}\
virtual int GetChannelListIdByIndex(int index){ return m_parent->intf ## _GetChannelListIdByIndex(index);}\
virtual void SetFavouriteChannelListId(int mode,int attrib,int index){ return m_parent->intf ## _SetFavouriteChannelListId(mode,attrib,index );}\
virtual void GetSIDetails(HsvSDMSIDataValues* sivalues){return m_parent->intf ## _GetSIDetails(sivalues);}\
virtual void AddTvpData(HsvPgdatTvProviderBlobData *TvpData, int Clear){ return m_parent->intf ## _AddTvpData(TvpData,Clear);}\
virtual void SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData){ return m_parent->intf ## _SyncUniqueIdToMW(TvpData);}\
virtual int GetLastAnalogPresetNumber(void) { return m_parent->intf ## _GetLastAnalogPresetNumber();}\
virtual int GetActiveMedium(void) { return m_parent->intf ## _GetActiveMedium();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
