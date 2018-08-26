#ifndef IHSVEUROPEDIVERSITY2_H
#define IHSVEUROPEDIVERSITY2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvEuropeDiversity2
{
public:
	virtual ~IHsvEuropeDiversity2(){}
	virtual int iVersion(void)= 0;
	virtual int NITTimeoutTime(void)= 0;
	virtual Bool AttenuatorDetectionInInstall(void)= 0;
	virtual Bool SupportNameExtractionInManIns(void)= 0;
	virtual int WeakSignalStrengthThreshold(void)= 0;
	virtual Bool SignalStrengthSorting(void)= 0;
	virtual Bool SearchForColorSystemInInstallation(void)= 0;
	virtual Bool SearchForTvSystemInInstallation(void)= 0;
	virtual Bool ManualSearchWithWrapAround(void)= 0;
	virtual Bool SortPresetsInAutoStoreModeNone(void)= 0;
	virtual int SignalStrengthTimeoutTime(void)= 0;
	virtual int DefaultTunerPresetFrequency(void)= 0;
	virtual int PgctrlMuteColor(void)= 0;
	virtual int ChannelNameLength(void)= 0;
	virtual int PresetNameLength(void)= 0;
	virtual Bool MuteRequiredOnInstallation(void)= 0;
	virtual Bool ClearDataOnAutoInstallation(void)= 0;
	virtual Bool AnalogOnly(void)= 0;
	virtual int InstallTestStreams(int installationmode,int medium)= 0;
	#define IHsvEuropeDiversity2_NotInstall		((int)0 )
	#define IHsvEuropeDiversity2_Install		((int)1 )
	#define IHsvEuropeDiversity2_Hide		((int)2 )
	virtual int NoOfVirtualChannelsSupported(int medium)= 0;
	virtual Bool SupportMultipleOriginalNetworkId(int medium)= 0;
	virtual Bool ForceLCNSyntax(int medium)= 0;
	virtual Bool InstallDuplicateTsids(int medium)= 0;
	virtual int DefaultStreamPriority(int medium)= 0;
	virtual Bool IsServiceInstallable(int medium,int ServiceType)= 0;
	virtual Bool IsServiceSortable(int medium,int ServiceType)= 0;
	virtual Bool IsServiceHidden(int medium,int ServiceType)= 0;
	virtual Bool AcceptedStreamType(int medium,HsvAVStreamType StreamType)= 0;
	virtual Bool UpdateChannelName(int medium)= 0;
	virtual Bool IsDbookCountry(void)= 0;	
	virtual Bool IsApmeaChannelListCountry(void)= 0;	
	virtual Bool IsApmeaNetworkUpdateCountry(void)= 0;
	virtual int SkipInstallationPass(void)= 0;
	virtual int FirstInstallationPass(void)= 0;
	#define IHsvEuropeDiversity2_SkipAnalog		((int)0 )
	#define IHsvEuropeDiversity2_SkipDigital		((int)1 )
	#define IHsvEuropeDiversity2_SkipNone		((int)2 )
	virtual Bool UpdateLCN(int medium)= 0;
	virtual int TxtInfoTimeout(void)= 0;
	virtual int VideoMuteColor(void)= 0;
	virtual int VideoMuteColorForLocks(void)= 0;
	#define IHsvEuropeDiversity2_VideoMuteBlack		((int)0 )
	#define IHsvEuropeDiversity2_VideoMuteBlue		((int)1 )
	#define IHsvEuropeDiversity2_VideoMuteGrey		((int)2 )
	virtual Bool DecoderSupported(void)= 0;
	virtual Bool BreakInSupported(void)= 0;
	virtual Bool ScartRuleSupported(void)= 0;
	virtual String HsvAntennaAnalogTable(void)= 0;
	virtual String HsvAntennaDigSrvcTable(void)= 0;
	virtual String HsvAntennaDigPtcTable(void)= 0;
	virtual String HsvAntennaFreqMapTable(void)= 0;
	virtual int PersistentMemUpdateTimeout(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaUserTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaDigSrvcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaDigPtcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaAnalogTable(void)= 0;
	virtual int MaxNoOfMultiplexsToStoreAntennaFreqMapTable(void)= 0;
	virtual Bool IsHDSubtitleSupported(void)= 0;
	virtual int AvSignalDetectionTimeOut(void)= 0;
	virtual Bool HearingImpairedOn(void)= 0;
	virtual Bool VisuallyImpairedOn(void)= 0;
	virtual Bool IsQaaSupported(void)= 0;
	virtual Bool IsPremixedVISupported(void)= 0;
	virtual char* EPGSecondaryDirName(void)= 0;
	virtual int DefaultCharacterTable(void)= 0;
	virtual int ShortInfoCacheForCountry(void)= 0;
	virtual int OUI(void)= 0;
	virtual int HardwareModel(void)= 0;
	virtual int HardwareVersion(void)= 0;
	virtual int GetNoOfBackBuffers(int clientId)= 0;
	virtual int SubtitleTimeOut(void)= 0;
	virtual Bool IsMpeg4STBoltOnSupported(void)= 0;
	virtual Bool IsAVCDescriptorSupported(void)= 0;
	virtual Bool ForceCharacterTable(void)= 0;
	virtual int RegionalCharacterTable(void)= 0;
	virtual int CurrentCountryInvalidLCNSortKey1(void)= 0;
	virtual int CurrentCountryInvalidLCNSortKey2(void)= 0;
	virtual int CurrentCountryInvalidLCNSortKey3(void)= 0;
	virtual int CurrentCountryInvalidLCNSortKey4(void)= 0;
	virtual int CurrentCountryInvalidLCNSortKey5(void)= 0;
	virtual int OtherCountrySortKey1(void)= 0;
	virtual int OtherCountrySortKey2(void)= 0;
	virtual int OtherCountrySortKey3(void)= 0;
	virtual int OtherCountrySortKey4(void)= 0;
	virtual int OtherCountrySortKey5(void)= 0;
	#define IHsvEuropeDiversity2_KeyInvalid		((int)0 )
	#define IHsvEuropeDiversity2_KeyOriginalNetworkId		((int)1 )
	#define IHsvEuropeDiversity2_KeyServiceType		((int)2 )
	#define IHsvEuropeDiversity2_KeyLCN		((int)3 )
	#define IHsvEuropeDiversity2_KeyServiceName		((int)4 )
	#define IHsvEuropeDiversity2_KeyServiceId		((int)5 )
	virtual Bool TripletKey(int medium)= 0;
	virtual Bool InstallDuplicateServices(int medium)= 0;
	virtual Bool MeasureSignalStrengthWhilePlaying(void)= 0;
	virtual int AnalogInstallationSequence(void)= 0;
	#define IHsvEuropeDiversity2_Automatic		((int)0 )
	#define IHsvEuropeDiversity2_PalOnly		((int)1 )
	#define IHsvEuropeDiversity2_PalSecam		((int)2 )
	#define IHsvEuropeDiversity2_SecamPal		((int)3 )
	#define IHsvEuropeDiversity2_SecamOnly		((int)4 )
	virtual int ChannelListVariant(void)= 0;
	#define IHsvEuropeDiversity2_DefaultChannelList		((int)0 )
	#define IHsvEuropeDiversity2_DualChannelList		((int)1 )
	#define IHsvEuropeDiversity2_TripleChannelList		((int)2 )
	virtual Bool EnableCountryFallbackForLCNSyntax(int medium)= 0;
	virtual Bool EnableONIDFallbackForLCNSyntax(int medium)= 0;
	virtual String HsvCableAnalogTable(void)= 0;
	virtual String HsvCableDigSrvcTable(void)= 0;
	virtual String HsvCableDigPtcTable(void)= 0;
	virtual String HsvCableSvcListDescTable(void)= 0;
	virtual String HsvCableFreqMapTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableUserTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableDigSrvcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableDigPtcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableAnalogTable(void)= 0;
	virtual int MaxNoOfMultiplexsToStoreCableFreqMapTable(void)= 0;
	virtual Bool IsDVBCSupported(void)= 0;
	#define IHsvEuropeDiversity2_QuickScan		((int)0 )
	#define IHsvEuropeDiversity2_FullScan		((int)1 )
	virtual int GetDefaultScanMode(int medium)= 0;
	#define IHsvEuropeDiversity2_ScanNone		((Nat16)0x0 )
	#define IHsvEuropeDiversity2_ScanAnalog		((Nat16)0x1 )
	#define IHsvEuropeDiversity2_ScanDVBT		((Nat16)0x2 )
	#define IHsvEuropeDiversity2_ScanDVBC		((Nat16)0x4 )
	#define IHsvEuropeDiversity2_ScanDVBS		((Nat16)0x8 )
	#define IHsvEuropeDiversity2_ScanDVBTMpegOnly		((Nat16)0x10 )
	#define IHsvEuropeDiversity2_ScanDVBCLite		((Nat16)0x20 )
	virtual Nat16 GetScanPreference(int medium,int installationmode)= 0;
	virtual Nat16 GetNextScan(int medium,int installationmode,Nat16 ScanPreference)= 0;
	virtual Nat16 GetDVBTMode(void)= 0;
	virtual Nat16 GetDVBCMode(void)= 0;
	#define IHsvEuropeDiversity2_NitNone		((Nat8)0 )
	#define IHsvEuropeDiversity2_NitActual		((Nat8)0x1 )
	#define IHsvEuropeDiversity2_NitOther		((Nat8)0x2 )
	virtual Nat8 GetNitPriority(int medium)= 0;
	virtual Bool IsServiceListDescriptorMandatory(int medium)= 0;
	#define IHsvEuropeDiversity2_PrimaryPreference		((Nat8)0x1 )
	#define IHsvEuropeDiversity2_SecondaryPreference		((Nat8)0x2 )
	virtual Nat8 GetAudioPreference(void)= 0;
	virtual Nat8 GetSubtitlePreference(void)= 0;
	virtual Bool UserPreferredAudioFormat(void)= 0;
	virtual Bool IsFrequencyListStorageRequired(void)= 0;
	virtual Bool GetDefaultAttributeValues(Nat8 attrib,int country,Nat8 * mode,int * length,int * values)= 0;
	virtual String HsvDVBCSettingsFilePath(void)= 0;
	virtual String HsvCableDelSysDescFilePath(void)= 0;
	virtual String HsvServiceListDescFilePath(void)= 0;
	virtual int MaxLCNValue(void)= 0;
	virtual Bool IsBackgroundInstallRequired(int medium)= 0;
	virtual Bool SupportLCNVersion2(int medium)= 0;
	virtual Bool ParseLCN(int medium,int installationmode)= 0;
	virtual Bool IsPreScanSupported(int medium)= 0;
	virtual Bool SortNonLCNs(int medium)= 0;
	virtual Bool SupportHDSLCN(int medium)= 0;
	virtual Bool IsServiceAttrbDescSupported(int medium)= 0;
	virtual Bool IsTSRelocatedDescSupported(int medium)= 0;
	#define IHsvEuropeDiversity2_SDTActual		((Nat8)0x1 )
	#define IHsvEuropeDiversity2_SDTOther		((Nat8)0x2 )
	#define IHsvEuropeDiversity2_SDTNone		((Nat8)0x0 )
	virtual int GetAltSDTType(int medium)= 0;
	#define IHsvEuropeDiversity2_AltHomingFrequency		((Nat8)1 )
	#define IHsvEuropeDiversity2_AltTSRelocatedDesc		((Nat8)2 )
	#define IHsvEuropeDiversity2_AltNone		((Nat8)0 )
	virtual Nat8 GetAlternateTSLocation(int medium)= 0;
	virtual Bool GetAltFreqScanSupported(int country)= 0;
	virtual Bool FreqListDescriptorSupported(int medium)= 0;
	virtual Bool IsAc3AudioSupported(void)= 0;
	virtual Bool GetDefaultAnalogInstallStatus(int country)= 0;
	virtual Bool StaticTable(void)= 0;
	virtual Bool GetDefaultDigitalInstallStatus(int country)= 0;
	virtual Bool IsMultifeedSupported(void)= 0;
	virtual Bool IsZeroLCNHidden(void)= 0;
	virtual int GetViterbiBER(void)= 0;
	virtual int DeltaViterbiBER(void)= 0;
	virtual Nat32 GetShortInfoCacheSize(void)= 0;
	virtual int GetDeltaSQI(void)= 0;
	virtual int GetDeltaSSI(void)= 0;
	virtual Bool AutomaticAnalogPresetAllocation(void)= 0;
	virtual Bool GetDualAnalogPassStatus(void)= 0;
	virtual Bool GetDTTScanOnCableStatus(void)= 0;
	virtual Bool GetLCNOptionStatus(void)= 0;
	virtual Bool AutomaticDigitalPresetAllocation(void)= 0;
	virtual int AnalogStartPreset(int country,int medium,int numRecords)= 0;
	virtual int AnalogEndPreset(int country,int medium)= 0;
	virtual int NonRadioStartPreset(int country,int medium,int numRecords)= 0;
	virtual int NonRadioEndPreset(int country,int medium)= 0;
	virtual int RadioStartPreset(int country,int medium,int numRecords)= 0;
	virtual int RadioEndPreset(int country,int medium)= 0;
	virtual Bool IsHDSimulcastSupported(void)= 0;
	virtual Bool IsDVBT2Supported(void)= 0;
	virtual Bool MultipleLCNSupported(void)= 0;
	virtual Bool MultiLingSupported(void)= 0;
	virtual Bool SubtitlePidFallbackFirstPMT(void)= 0;
	virtual Bool DeleteTSNotIntransmission(void)= 0;
	virtual Bool ReapplyChildLockOnEventChange(void)= 0;
	virtual Bool DeleteServiceOnFly(void)=0;
	virtual int setForceCharacterTable(Bool isSet) = 0;
	virtual Bool SupportSDTOtherInBackgroundInstallation(void)=0;
	virtual int sdmWaitTime(void) = 0;
	virtual Bool UpdateLCNOnFly(void)= 0;	
};


#define IHsvEuropeDiversity2Impl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
virtual Bool intf ## _AnalogOnly(void);\
virtual int intf ## _InstallTestStreams(int installationmode,int medium);\
virtual int intf ## _NoOfVirtualChannelsSupported(int medium);\
virtual Bool intf ## _SupportMultipleOriginalNetworkId(int medium);\
virtual Bool intf ## _ForceLCNSyntax(int medium);\
virtual Bool intf ## _InstallDuplicateTsids(int medium);\
virtual int intf ## _DefaultStreamPriority(int medium);\
virtual Bool intf ## _IsServiceInstallable(int medium,int ServiceType);\
virtual Bool intf ## _IsServiceSortable(int medium,int ServiceType);\
virtual Bool intf ## _IsServiceHidden(int medium,int ServiceType);\
virtual Bool intf ## _AcceptedStreamType(int medium,HsvAVStreamType StreamType);\
virtual Bool intf ## _UpdateChannelName(int medium);\
virtual Bool intf ## _IsDbookCountry(void);\
virtual Bool intf ## _IsApmeaChannelListCountry(void);\
virtual Bool intf ## _IsApmeaNetworkUpdateCountry(void);\
virtual Bool intf ## _UpdateLCNOnFly(void);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _UpdateLCN(int medium);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsHDSubtitleSupported(void);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
virtual Bool intf ## _VisuallyImpairedOn(void);\
virtual Bool intf ## _IsQaaSupported(void);\
virtual Bool intf ## _IsPremixedVISupported(void);\
friend class InterfaceParam<Comp,char*>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual int intf ## _GetNoOfBackBuffers(int clientId);\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsMpeg4STBoltOnSupported(void);\
virtual Bool intf ## _IsAVCDescriptorSupported(void);\
virtual Bool intf ## _ForceCharacterTable(void);\
virtual int intf ## _RegionalCharacterTable(void);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _TripletKey(int medium);\
virtual Bool intf ## _InstallDuplicateServices(int medium);\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _EnableCountryFallbackForLCNSyntax(int medium);\
virtual Bool intf ## _EnableONIDFallbackForLCNSyntax(int medium);\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsDVBCSupported(void);\
virtual int intf ## _GetDefaultScanMode(int medium);\
virtual Nat16 intf ## _GetScanPreference(int medium,int installationmode);\
virtual Nat16 intf ## _GetNextScan(int medium,int installationmode,Nat16 ScanPreference);\
virtual Nat16 intf ## _GetDVBTMode(void);\
virtual Nat16 intf ## _GetDVBCMode(void);\
virtual Nat8 intf ## _GetNitPriority(int medium);\
virtual Bool intf ## _IsServiceListDescriptorMandatory(int medium);\
virtual Nat8 intf ## _GetAudioPreference(void);\
virtual Nat8 intf ## _GetSubtitlePreference(void);\
virtual Bool intf ## _UserPreferredAudioFormat(void);\
virtual Bool intf ## _IsFrequencyListStorageRequired(void);\
virtual Bool intf ## _GetDefaultAttributeValues(Nat8 attrib,int country,Nat8 * mode,int * length,int * values);\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsBackgroundInstallRequired(int medium);\
virtual Bool intf ## _SupportLCNVersion2(int medium);\
virtual Bool intf ## _ParseLCN(int medium,int installationmode);\
virtual Bool intf ## _IsPreScanSupported(int medium);\
virtual Bool intf ## _SortNonLCNs(int medium);\
virtual Bool intf ## _SupportHDSLCN(int medium);\
virtual Bool intf ## _IsServiceAttrbDescSupported(int medium);\
virtual Bool intf ## _IsTSRelocatedDescSupported(int medium);\
virtual int intf ## _GetAltSDTType(int medium);\
virtual Nat8 intf ## _GetAlternateTSLocation(int medium);\
virtual Bool intf ## _GetAltFreqScanSupported(int country);\
virtual Bool intf ## _FreqListDescriptorSupported(int medium);\
virtual Bool intf ## _IsAc3AudioSupported(void);\
virtual Bool intf ## _GetDefaultAnalogInstallStatus(int country);\
virtual Bool intf ## _StaticTable(void);\
virtual Bool intf ## _GetDefaultDigitalInstallStatus(int country);\
virtual Bool intf ## _IsMultifeedSupported(void);\
virtual Bool intf ## _IsZeroLCNHidden(void);\
virtual int intf ## _GetViterbiBER(void);\
virtual int intf ## _DeltaViterbiBER(void);\
virtual Nat32 intf ## _GetShortInfoCacheSize(void);\
virtual int intf ## _GetDeltaSQI(void);\
virtual int intf ## _GetDeltaSSI(void);\
virtual Bool intf ## _AutomaticAnalogPresetAllocation(void);\
virtual Bool intf ## _AutomaticDigitalPresetAllocation(void);\
virtual int intf ## _AnalogStartPreset(int country,int medium,int numRecords);\
virtual int intf ## _GetDualAnalogPassStatus(void);\
virtual int intf ## _GetDTTScanOnCableStatus(void);\
virtual int intf ## _GetLCNOptionStatus(void);\
virtual int intf ## _AnalogEndPreset(int country,int medium);\
virtual int intf ## _NonRadioStartPreset(int country,int medium,int numRecords);\
virtual int intf ## _NonRadioEndPreset(int country,int medium);\
virtual int intf ## _RadioStartPreset(int country,int medium,int numRecords);\
virtual int intf ## _RadioEndPreset(int country,int medium);\
virtual Bool intf ## _IsHDSimulcastSupported(void);\
virtual Bool intf ## _IsDVBT2Supported(void);\
virtual Bool intf ## _MultipleLCNSupported(void);\
virtual Bool intf ## _MultiLingSupported(void);\
virtual Bool intf ## _SubtitlePidFallbackFirstPMT(void);\
virtual Bool intf ## _DeleteTSNotIntransmission(void);\
virtual Bool intf ## _ReapplyChildLockOnEventChange(void);\
virtual Bool intf ## _DeleteServiceOnFly(void);\
virtual int intf ## _setForceCharacterTable(Bool isSet);\
virtual Bool intf ## _SupportSDTOtherInBackgroundInstallation(void);\
virtual int intf ## _sdmWaitTime(void);\
class Comp ## _ ## intf : public IHsvEuropeDiversity2 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_iVersion; \
    InterfaceParam<Comp,int> m_NITTimeoutTime; \
    InterfaceParam<Comp,Bool> m_AttenuatorDetectionInInstall; \
    InterfaceParam<Comp,Bool> m_SupportNameExtractionInManIns; \
    InterfaceParam<Comp,int> m_WeakSignalStrengthThreshold; \
    InterfaceParam<Comp,Bool> m_SignalStrengthSorting; \
    InterfaceParam<Comp,Bool> m_SearchForColorSystemInInstallation; \
    InterfaceParam<Comp,Bool> m_SearchForTvSystemInInstallation; \
    InterfaceParam<Comp,Bool> m_ManualSearchWithWrapAround; \
    InterfaceParam<Comp,Bool> m_SortPresetsInAutoStoreModeNone; \
    InterfaceParam<Comp,int> m_SignalStrengthTimeoutTime; \
    InterfaceParam<Comp,int> m_DefaultTunerPresetFrequency; \
    InterfaceParam<Comp,int> m_PgctrlMuteColor; \
    InterfaceParam<Comp,int> m_ChannelNameLength; \
    InterfaceParam<Comp,int> m_PresetNameLength; \
    InterfaceParam<Comp,Bool> m_MuteRequiredOnInstallation; \
    InterfaceParam<Comp,Bool> m_ClearDataOnAutoInstallation; \
    InterfaceParam<Comp,int> m_SkipInstallationPass; \
    InterfaceParam<Comp,int> m_FirstInstallationPass; \
    InterfaceParam<Comp,int> m_TxtInfoTimeout; \
    InterfaceParam<Comp,int> m_VideoMuteColor; \
    InterfaceParam<Comp,int> m_VideoMuteColorForLocks; \
    InterfaceParam<Comp,Bool> m_DecoderSupported; \
    InterfaceParam<Comp,Bool> m_BreakInSupported; \
    InterfaceParam<Comp,Bool> m_ScartRuleSupported; \
    InterfaceParam<Comp,String> m_HsvAntennaAnalogTable; \
    InterfaceParam<Comp,String> m_HsvAntennaDigSrvcTable; \
    InterfaceParam<Comp,String> m_HsvAntennaDigPtcTable; \
    InterfaceParam<Comp,String> m_HsvAntennaFreqMapTable; \
    InterfaceParam<Comp,int> m_PersistentMemUpdateTimeout; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaUserTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaDigSrvcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaDigPtcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaAnalogTable; \
    InterfaceParam<Comp,int> m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable; \
    InterfaceParam<Comp,int> m_AvSignalDetectionTimeOut; \
    InterfaceParam<Comp,Bool> m_HearingImpairedOn; \
    InterfaceParam<Comp,char*> m_EPGSecondaryDirName; \
    InterfaceParam<Comp,int> m_DefaultCharacterTable; \
    InterfaceParam<Comp,int> m_ShortInfoCacheForCountry; \
    InterfaceParam<Comp,int> m_OUI; \
    InterfaceParam<Comp,int> m_HardwareModel; \
    InterfaceParam<Comp,int> m_HardwareVersion; \
    InterfaceParam<Comp,int> m_SubtitleTimeOut; \
    InterfaceParam<Comp,int> m_CurrentCountryInvalidLCNSortKey1; \
    InterfaceParam<Comp,int> m_CurrentCountryInvalidLCNSortKey2; \
    InterfaceParam<Comp,int> m_CurrentCountryInvalidLCNSortKey3; \
    InterfaceParam<Comp,int> m_CurrentCountryInvalidLCNSortKey4; \
    InterfaceParam<Comp,int> m_CurrentCountryInvalidLCNSortKey5; \
    InterfaceParam<Comp,int> m_OtherCountrySortKey1; \
    InterfaceParam<Comp,int> m_OtherCountrySortKey2; \
    InterfaceParam<Comp,int> m_OtherCountrySortKey3; \
    InterfaceParam<Comp,int> m_OtherCountrySortKey4; \
    InterfaceParam<Comp,int> m_OtherCountrySortKey5; \
    InterfaceParam<Comp,Bool> m_MeasureSignalStrengthWhilePlaying; \
    InterfaceParam<Comp,int> m_AnalogInstallationSequence; \
    InterfaceParam<Comp,int> m_ChannelListVariant; \
    InterfaceParam<Comp,String> m_HsvCableAnalogTable; \
    InterfaceParam<Comp,String> m_HsvCableDigSrvcTable; \
    InterfaceParam<Comp,String> m_HsvCableDigPtcTable; \
    InterfaceParam<Comp,String> m_HsvCableSvcListDescTable; \
    InterfaceParam<Comp,String> m_HsvCableFreqMapTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableUserTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableDigSrvcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableDigPtcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableAnalogTable; \
    InterfaceParam<Comp,int> m_MaxNoOfMultiplexsToStoreCableFreqMapTable; \
    InterfaceParam<Comp,String> m_HsvDVBCSettingsFilePath; \
    InterfaceParam<Comp,String> m_HsvCableDelSysDescFilePath; \
    InterfaceParam<Comp,String> m_HsvServiceListDescFilePath; \
    InterfaceParam<Comp,int> m_MaxLCNValue; \
    Comp ## _ ## intf( Comp *parent):m_iVersion(parent),m_NITTimeoutTime(parent),m_AttenuatorDetectionInInstall(parent),m_SupportNameExtractionInManIns(parent),m_WeakSignalStrengthThreshold(parent),m_SignalStrengthSorting(parent),m_SearchForColorSystemInInstallation(parent),m_SearchForTvSystemInInstallation(parent),m_ManualSearchWithWrapAround(parent),m_SortPresetsInAutoStoreModeNone(parent),m_SignalStrengthTimeoutTime(parent),m_DefaultTunerPresetFrequency(parent),m_PgctrlMuteColor(parent),m_ChannelNameLength(parent),m_PresetNameLength(parent),m_MuteRequiredOnInstallation(parent),m_ClearDataOnAutoInstallation(parent),m_SkipInstallationPass(parent),m_FirstInstallationPass(parent),m_TxtInfoTimeout(parent),m_VideoMuteColor(parent),m_VideoMuteColorForLocks(parent),m_DecoderSupported(parent),m_BreakInSupported(parent),m_ScartRuleSupported(parent),m_HsvAntennaAnalogTable(parent),m_HsvAntennaDigSrvcTable(parent),m_HsvAntennaDigPtcTable(parent),m_HsvAntennaFreqMapTable(parent),m_PersistentMemUpdateTimeout(parent),m_MaxNoOfChannelsToStoreAntennaUserTable(parent),m_MaxNoOfChannelsToStoreAntennaDigSrvcTable(parent),m_MaxNoOfChannelsToStoreAntennaDigPtcTable(parent),m_MaxNoOfChannelsToStoreAntennaAnalogTable(parent),m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable(parent),m_AvSignalDetectionTimeOut(parent),m_HearingImpairedOn(parent),m_EPGSecondaryDirName(parent),m_DefaultCharacterTable(parent),m_ShortInfoCacheForCountry(parent),m_OUI(parent),m_HardwareModel(parent),m_HardwareVersion(parent),m_SubtitleTimeOut(parent),m_CurrentCountryInvalidLCNSortKey1(parent),m_CurrentCountryInvalidLCNSortKey2(parent),m_CurrentCountryInvalidLCNSortKey3(parent),m_CurrentCountryInvalidLCNSortKey4(parent),m_CurrentCountryInvalidLCNSortKey5(parent),m_OtherCountrySortKey1(parent),m_OtherCountrySortKey2(parent),m_OtherCountrySortKey3(parent),m_OtherCountrySortKey4(parent),m_OtherCountrySortKey5(parent),m_MeasureSignalStrengthWhilePlaying(parent),m_AnalogInstallationSequence(parent),m_ChannelListVariant(parent),m_HsvCableAnalogTable(parent),m_HsvCableDigSrvcTable(parent),m_HsvCableDigPtcTable(parent),m_HsvCableSvcListDescTable(parent),m_HsvCableFreqMapTable(parent),m_MaxNoOfChannelsToStoreCableUserTable(parent),m_MaxNoOfChannelsToStoreCableDigSrvcTable(parent),m_MaxNoOfChannelsToStoreCableDigPtcTable(parent),m_MaxNoOfChannelsToStoreCableAnalogTable(parent),m_MaxNoOfMultiplexsToStoreCableFreqMapTable(parent),m_HsvDVBCSettingsFilePath(parent),m_HsvCableDelSysDescFilePath(parent),m_HsvServiceListDescFilePath(parent),m_MaxLCNValue(parent) \
    {\
        m_parent = parent;\
    }\
virtual int iVersion(void){ return m_iVersion.Call();}\
virtual int NITTimeoutTime(void){ return m_NITTimeoutTime.Call();}\
virtual Bool AttenuatorDetectionInInstall(void){ return m_AttenuatorDetectionInInstall.Call();}\
virtual Bool SupportNameExtractionInManIns(void){ return m_SupportNameExtractionInManIns.Call();}\
virtual int WeakSignalStrengthThreshold(void){ return m_WeakSignalStrengthThreshold.Call();}\
virtual Bool SignalStrengthSorting(void){ return m_SignalStrengthSorting.Call();}\
virtual Bool SearchForColorSystemInInstallation(void){ return m_SearchForColorSystemInInstallation.Call();}\
virtual Bool SearchForTvSystemInInstallation(void){ return m_SearchForTvSystemInInstallation.Call();}\
virtual Bool ManualSearchWithWrapAround(void){ return m_ManualSearchWithWrapAround.Call();}\
virtual Bool SortPresetsInAutoStoreModeNone(void){ return m_SortPresetsInAutoStoreModeNone.Call();}\
virtual int SignalStrengthTimeoutTime(void){ return m_SignalStrengthTimeoutTime.Call();}\
virtual int DefaultTunerPresetFrequency(void){ return m_DefaultTunerPresetFrequency.Call();}\
virtual int PgctrlMuteColor(void){ return m_PgctrlMuteColor.Call();}\
virtual int ChannelNameLength(void){ return m_ChannelNameLength.Call();}\
virtual int PresetNameLength(void){ return m_PresetNameLength.Call();}\
virtual Bool MuteRequiredOnInstallation(void){ return m_MuteRequiredOnInstallation.Call();}\
virtual Bool ClearDataOnAutoInstallation(void){ return m_ClearDataOnAutoInstallation.Call();}\
virtual Bool AnalogOnly(void){ return m_parent->intf ## _AnalogOnly();}\
virtual int InstallTestStreams(int installationmode,int medium){ return m_parent->intf ## _InstallTestStreams(installationmode,medium);}\
virtual int NoOfVirtualChannelsSupported(int medium){ return m_parent->intf ## _NoOfVirtualChannelsSupported(medium);}\
virtual Bool SupportMultipleOriginalNetworkId(int medium){ return m_parent->intf ## _SupportMultipleOriginalNetworkId(medium);}\
virtual Bool ForceLCNSyntax(int medium){ return m_parent->intf ## _ForceLCNSyntax(medium);}\
virtual Bool InstallDuplicateTsids(int medium){ return m_parent->intf ## _InstallDuplicateTsids(medium);}\
virtual int DefaultStreamPriority(int medium){ return m_parent->intf ## _DefaultStreamPriority(medium);}\
virtual Bool IsServiceInstallable(int medium,int ServiceType){ return m_parent->intf ## _IsServiceInstallable(medium,ServiceType);}\
virtual Bool IsServiceSortable(int medium,int ServiceType){ return m_parent->intf ## _IsServiceSortable(medium,ServiceType);}\
virtual Bool IsServiceHidden(int medium,int ServiceType){ return m_parent->intf ## _IsServiceHidden(medium,ServiceType);}\
virtual Bool AcceptedStreamType(int medium,HsvAVStreamType StreamType){ return m_parent->intf ## _AcceptedStreamType(medium,StreamType);}\
virtual Bool UpdateChannelName(int medium){ return m_parent->intf ## _UpdateChannelName(medium);}\
virtual Bool IsDbookCountry(void){ return m_parent->intf ## _IsDbookCountry();}\
virtual Bool IsApmeaChannelListCountry(void){ return m_parent->intf ## _IsApmeaChannelListCountry();}\
virtual Bool UpdateLCNOnFly(){ return m_parent->intf ## _UpdateLCNOnFly();}\
virtual Bool IsApmeaNetworkUpdateCountry(void){ return m_parent->intf ## _IsApmeaNetworkUpdateCountry();}\
virtual int SkipInstallationPass(void){ return m_SkipInstallationPass.Call();}\
virtual int FirstInstallationPass(void){ return m_FirstInstallationPass.Call();}\
virtual Bool UpdateLCN(int medium){ return m_parent->intf ## _UpdateLCN(medium);}\
virtual int TxtInfoTimeout(void){ return m_TxtInfoTimeout.Call();}\
virtual int VideoMuteColor(void){ return m_VideoMuteColor.Call();}\
virtual int VideoMuteColorForLocks(void){ return m_VideoMuteColorForLocks.Call();}\
virtual Bool DecoderSupported(void){ return m_DecoderSupported.Call();}\
virtual Bool BreakInSupported(void){ return m_BreakInSupported.Call();}\
virtual Bool ScartRuleSupported(void){ return m_ScartRuleSupported.Call();}\
virtual String HsvAntennaAnalogTable(void){ return m_HsvAntennaAnalogTable.Call();}\
virtual String HsvAntennaDigSrvcTable(void){ return m_HsvAntennaDigSrvcTable.Call();}\
virtual String HsvAntennaDigPtcTable(void){ return m_HsvAntennaDigPtcTable.Call();}\
virtual String HsvAntennaFreqMapTable(void){ return m_HsvAntennaFreqMapTable.Call();}\
virtual int PersistentMemUpdateTimeout(void){ return m_PersistentMemUpdateTimeout.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaUserTable(void){ return m_MaxNoOfChannelsToStoreAntennaUserTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaDigSrvcTable(void){ return m_MaxNoOfChannelsToStoreAntennaDigSrvcTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaDigPtcTable(void){ return m_MaxNoOfChannelsToStoreAntennaDigPtcTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaAnalogTable(void){ return m_MaxNoOfChannelsToStoreAntennaAnalogTable.Call();}\
virtual int MaxNoOfMultiplexsToStoreAntennaFreqMapTable(void){ return m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable.Call();}\
virtual Bool IsHDSubtitleSupported(void){ return m_parent->intf ## _IsHDSubtitleSupported();}\
virtual int AvSignalDetectionTimeOut(void){ return m_AvSignalDetectionTimeOut.Call();}\
virtual Bool HearingImpairedOn(void){ return m_HearingImpairedOn.Call();}\
virtual Bool VisuallyImpairedOn(void){ return m_parent->intf ## _VisuallyImpairedOn();}\
virtual Bool IsQaaSupported(void){ return m_parent->intf ## _IsQaaSupported();}\
virtual Bool IsPremixedVISupported(void){ return m_parent->intf ## _IsPremixedVISupported();}\
virtual char* EPGSecondaryDirName(void){ return m_EPGSecondaryDirName.Call();}\
virtual int DefaultCharacterTable(void){ return m_DefaultCharacterTable.Call();}\
virtual int ShortInfoCacheForCountry(void){ return m_ShortInfoCacheForCountry.Call();}\
virtual int OUI(void){ return m_OUI.Call();}\
virtual int HardwareModel(void){ return m_HardwareModel.Call();}\
virtual int HardwareVersion(void){ return m_HardwareVersion.Call();}\
virtual int GetNoOfBackBuffers(int clientId){ return m_parent->intf ## _GetNoOfBackBuffers(clientId);}\
virtual int SubtitleTimeOut(void){ return m_SubtitleTimeOut.Call();}\
virtual Bool IsMpeg4STBoltOnSupported(void){ return m_parent->intf ## _IsMpeg4STBoltOnSupported();}\
virtual Bool IsAVCDescriptorSupported(void){ return m_parent->intf ## _IsAVCDescriptorSupported();}\
virtual Bool ForceCharacterTable(void){ return m_parent->intf ## _ForceCharacterTable();}\
virtual int RegionalCharacterTable(void){ return m_parent->intf ## _RegionalCharacterTable();}\
virtual int CurrentCountryInvalidLCNSortKey1(void){ return m_CurrentCountryInvalidLCNSortKey1.Call();}\
virtual int CurrentCountryInvalidLCNSortKey2(void){ return m_CurrentCountryInvalidLCNSortKey2.Call();}\
virtual int CurrentCountryInvalidLCNSortKey3(void){ return m_CurrentCountryInvalidLCNSortKey3.Call();}\
virtual int CurrentCountryInvalidLCNSortKey4(void){ return m_CurrentCountryInvalidLCNSortKey4.Call();}\
virtual int CurrentCountryInvalidLCNSortKey5(void){ return m_CurrentCountryInvalidLCNSortKey5.Call();}\
virtual int OtherCountrySortKey1(void){ return m_OtherCountrySortKey1.Call();}\
virtual int OtherCountrySortKey2(void){ return m_OtherCountrySortKey2.Call();}\
virtual int OtherCountrySortKey3(void){ return m_OtherCountrySortKey3.Call();}\
virtual int OtherCountrySortKey4(void){ return m_OtherCountrySortKey4.Call();}\
virtual int OtherCountrySortKey5(void){ return m_OtherCountrySortKey5.Call();}\
virtual Bool TripletKey(int medium){ return m_parent->intf ## _TripletKey(medium);}\
virtual Bool InstallDuplicateServices(int medium){ return m_parent->intf ## _InstallDuplicateServices(medium);}\
virtual Bool MeasureSignalStrengthWhilePlaying(void){ return m_MeasureSignalStrengthWhilePlaying.Call();}\
virtual int AnalogInstallationSequence(void){ return m_AnalogInstallationSequence.Call();}\
virtual int ChannelListVariant(void){ return m_ChannelListVariant.Call();}\
virtual Bool EnableCountryFallbackForLCNSyntax(int medium){ return m_parent->intf ## _EnableCountryFallbackForLCNSyntax(medium);}\
virtual Bool EnableONIDFallbackForLCNSyntax(int medium){ return m_parent->intf ## _EnableONIDFallbackForLCNSyntax(medium);}\
virtual String HsvCableAnalogTable(void){ return m_HsvCableAnalogTable.Call();}\
virtual String HsvCableDigSrvcTable(void){ return m_HsvCableDigSrvcTable.Call();}\
virtual String HsvCableDigPtcTable(void){ return m_HsvCableDigPtcTable.Call();}\
virtual String HsvCableSvcListDescTable(void){ return m_HsvCableSvcListDescTable.Call();}\
virtual String HsvCableFreqMapTable(void){ return m_HsvCableFreqMapTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableUserTable(void){ return m_MaxNoOfChannelsToStoreCableUserTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableDigSrvcTable(void){ return m_MaxNoOfChannelsToStoreCableDigSrvcTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableDigPtcTable(void){ return m_MaxNoOfChannelsToStoreCableDigPtcTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableAnalogTable(void){ return m_MaxNoOfChannelsToStoreCableAnalogTable.Call();}\
virtual int MaxNoOfMultiplexsToStoreCableFreqMapTable(void){ return m_MaxNoOfMultiplexsToStoreCableFreqMapTable.Call();}\
virtual Bool IsDVBCSupported(void){ return m_parent->intf ## _IsDVBCSupported();}\
virtual int GetDefaultScanMode(int medium){ return m_parent->intf ## _GetDefaultScanMode(medium);}\
virtual Nat16 GetScanPreference(int medium,int installationmode){ return m_parent->intf ## _GetScanPreference(medium,installationmode);}\
virtual Nat16 GetNextScan(int medium,int installationmode,Nat16 ScanPreference){ return m_parent->intf ## _GetNextScan(medium,installationmode,ScanPreference);}\
virtual Nat16 GetDVBTMode(void){ return m_parent->intf ## _GetDVBTMode();}\
virtual Nat16 GetDVBCMode(void){ return m_parent->intf ## _GetDVBCMode();}\
virtual Nat8 GetNitPriority(int medium){ return m_parent->intf ## _GetNitPriority(medium);}\
virtual Bool IsServiceListDescriptorMandatory(int medium){ return m_parent->intf ## _IsServiceListDescriptorMandatory(medium);}\
virtual Nat8 GetAudioPreference(void){ return m_parent->intf ## _GetAudioPreference();}\
virtual Nat8 GetSubtitlePreference(void){ return m_parent->intf ## _GetSubtitlePreference();}\
virtual Bool UserPreferredAudioFormat(void){ return m_parent->intf ## _UserPreferredAudioFormat();}\
virtual Bool IsFrequencyListStorageRequired(void){ return m_parent->intf ## _IsFrequencyListStorageRequired();}\
virtual Bool GetDefaultAttributeValues(Nat8 attrib,int country,Nat8 * mode,int * length,int * values){ return m_parent->intf ## _GetDefaultAttributeValues(attrib,country,mode,length,values);}\
virtual String HsvDVBCSettingsFilePath(void){ return m_HsvDVBCSettingsFilePath.Call();}\
virtual String HsvCableDelSysDescFilePath(void){ return m_HsvCableDelSysDescFilePath.Call();}\
virtual String HsvServiceListDescFilePath(void){ return m_HsvServiceListDescFilePath.Call();}\
virtual int MaxLCNValue(void){ return m_MaxLCNValue.Call();}\
virtual Bool IsBackgroundInstallRequired(int medium){ return m_parent->intf ## _IsBackgroundInstallRequired(medium);}\
virtual Bool SupportLCNVersion2(int medium){ return m_parent->intf ## _SupportLCNVersion2(medium);}\
virtual Bool ParseLCN(int medium,int installationmode){ return m_parent->intf ## _ParseLCN(medium,installationmode);}\
virtual Bool IsPreScanSupported(int medium){ return m_parent->intf ## _IsPreScanSupported(medium);}\
virtual Bool SortNonLCNs(int medium){ return m_parent->intf ## _SortNonLCNs(medium);}\
virtual Bool SupportHDSLCN(int medium){ return m_parent->intf ## _SupportHDSLCN(medium);}\
virtual Bool IsServiceAttrbDescSupported(int medium){ return m_parent->intf ## _IsServiceAttrbDescSupported(medium);}\
virtual Bool IsTSRelocatedDescSupported(int medium){ return m_parent->intf ## _IsTSRelocatedDescSupported(medium);}\
virtual int GetAltSDTType(int medium){ return m_parent->intf ## _GetAltSDTType(medium);}\
virtual Nat8 GetAlternateTSLocation(int medium){ return m_parent->intf ## _GetAlternateTSLocation(medium);}\
virtual Bool GetAltFreqScanSupported(int country){ return m_parent->intf ## _GetAltFreqScanSupported(country);}\
virtual Bool FreqListDescriptorSupported(int medium){ return m_parent->intf ## _FreqListDescriptorSupported(medium);}\
virtual Bool IsAc3AudioSupported(void){ return m_parent->intf ## _IsAc3AudioSupported();}\
virtual Bool GetDefaultAnalogInstallStatus(int country){ return m_parent->intf ## _GetDefaultAnalogInstallStatus(country);}\
virtual Bool StaticTable(void){ return m_parent->intf ## _StaticTable();}\
virtual Bool GetDefaultDigitalInstallStatus(int country){ return m_parent->intf ## _GetDefaultDigitalInstallStatus(country);}\
virtual Bool IsMultifeedSupported(void){ return m_parent->intf ## _IsMultifeedSupported();}\
virtual Bool IsZeroLCNHidden(void){ return m_parent->intf ## _IsZeroLCNHidden();}\
virtual int GetViterbiBER(void){ return m_parent->intf ## _GetViterbiBER();}\
virtual int DeltaViterbiBER(void){ return m_parent->intf ## _DeltaViterbiBER();}\
virtual Nat32 GetShortInfoCacheSize(void){ return m_parent->intf ## _GetShortInfoCacheSize();}\
virtual int GetDeltaSQI(void){ return m_parent->intf ## _GetDeltaSQI();}\
virtual int GetDeltaSSI(void){ return m_parent->intf ## _GetDeltaSSI();}\
virtual Bool AutomaticAnalogPresetAllocation(void){ return m_parent->intf ## _AutomaticAnalogPresetAllocation();}\
virtual Bool AutomaticDigitalPresetAllocation(void){ return m_parent->intf ## _AutomaticDigitalPresetAllocation();}\
virtual Bool GetDualAnalogPassStatus(void){ return m_parent->intf ## _GetDualAnalogPassStatus();}\
virtual Bool GetDTTScanOnCableStatus(void){ return m_parent->intf ## _GetDTTScanOnCableStatus();}\
virtual Bool GetLCNOptionStatus(void){ return m_parent->intf ## _GetLCNOptionStatus();}\
virtual int AnalogStartPreset(int country,int medium,int numRecords){ return m_parent->intf ## _AnalogStartPreset(country,medium,numRecords);}\
virtual int AnalogEndPreset(int country,int medium){ return m_parent->intf ## _AnalogEndPreset(country,medium);}\
virtual int NonRadioStartPreset(int country,int medium,int numRecords){ return m_parent->intf ## _NonRadioStartPreset(country,medium,numRecords);}\
virtual int NonRadioEndPreset(int country,int medium){ return m_parent->intf ## _NonRadioEndPreset(country,medium);}\
virtual int RadioStartPreset(int country,int medium,int numRecords){ return m_parent->intf ## _RadioStartPreset(country,medium,numRecords);}\
virtual int RadioEndPreset(int country,int medium){ return m_parent->intf ## _RadioEndPreset(country,medium);}\
virtual Bool IsHDSimulcastSupported(void){ return m_parent->intf ## _IsHDSimulcastSupported();}\
virtual Bool IsDVBT2Supported(void){ return m_parent->intf ## _IsDVBT2Supported();}\
virtual Bool MultipleLCNSupported(void){ return m_parent->intf ## _MultipleLCNSupported();}\
virtual Bool MultiLingSupported(void){ return m_parent->intf ## _MultiLingSupported();}\
virtual Bool SubtitlePidFallbackFirstPMT(void){ return m_parent->intf ## _SubtitlePidFallbackFirstPMT();}\
virtual Bool DeleteTSNotIntransmission(void){ return m_parent->intf ## _DeleteTSNotIntransmission();}\
virtual Bool ReapplyChildLockOnEventChange(void){ return m_parent->intf ## _ReapplyChildLockOnEventChange();}\
virtual Bool DeleteServiceOnFly(void){ return m_parent->intf ## _DeleteServiceOnFly();}\
virtual int setForceCharacterTable(Bool isSet){ return m_parent->intf ## _setForceCharacterTable(isSet);}\
virtual Bool SupportSDTOtherInBackgroundInstallation(void){  return m_parent->intf ## _SupportSDTOtherInBackgroundInstallation();}\
virtual Bool sdmWaitTime(void){  return m_parent->intf ## _sdmWaitTime();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
