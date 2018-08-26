#ifndef IHSVPRESETINSTALLATIONDIV_H
#define IHSVPRESETINSTALLATIONDIV_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPresetInstallationDiv
{
public:
	virtual ~IHsvPresetInstallationDiv(){}
	virtual int iVersion(void)= 0;
	#define IHsvPresetInstallationDiv_MaxPresets		((int)500 )
	#define IHsvPresetInstallationDiv_PresetNameLength		((Nat8)23 )
	virtual int TxtResetTimeoutTime(void)= 0;
	virtual int SorCChannelSupported(void)= 0;
	virtual int TxtInfoTimeoutTime(void)= 0;
	virtual int AciOverallTimeoutTime(void)= 0;
	virtual int NITTimeoutTime(void)= 0;
	virtual Bool SecondPassSearchSupported(int country)= 0;
	virtual Bool SignalStrengthSorting(void)= 0;
	virtual int WeakSignalStrengthThreshold(void)= 0;
	virtual Bool AttenuatorDetectionInInstall(void)= 0;
	virtual Bool SupportNameExtractionInManIns(void)= 0;
	virtual char* GetDefaultPresetName(void)= 0;
	virtual Bool SearchForTvSystemInInstallation(void)= 0;
	virtual Bool SearchForColorSystemInInstallation(void)= 0;
	virtual Bool SortPresetsInAutoStoreModeNone(void)= 0;
	virtual int SignalStrengthTimeoutTime(void)= 0;
	virtual Bool ManualSearchWithWrapAround(void)= 0;
	virtual Bool ImmediateStoreInAutoInstall(void)= 0;
	virtual Bool AudioMuteDuringInstall(void)= 0;
	virtual Bool NameExtractionDuringImplicitManInstall(void)= 0;
	virtual Bool HandleSorCStationNotFoundinManInstall(void)= 0;
	virtual int DefaultSystemLanguage(void)= 0;
	virtual Nat32 CookieDefaultValue(void)= 0;
	virtual int MpegSectionsAcquisitionTimeout(void)= 0;
	virtual Bool BlankVideo(void)= 0;
	virtual int SigStrengthThresholdValue(void)= 0;
	virtual int FirstInstallationPass(void)= 0;
	virtual int PgctrlMuteColor(void)= 0;
	virtual int MaxPresetNo(void)= 0;
	virtual int MinPresetNo(void)= 0;
	virtual int AnalogOnly(void)= 0;
	virtual int InstallTestStreams(int installationmode,int medium)= 0;
	virtual int NotInstall(void)= 0;
	virtual int Install(void)= 0;
	virtual int Hide(void)= 0;
	virtual Bool SupportMultipleOriginalNetworkId(int medium)= 0;
	virtual Bool InstallDuplicateTsids(int medium)= 0;
	virtual int StreamPriorityToBeUsed(int medium)= 0;
	virtual Bool IsServiceInstallable(int medium,int ServiceType)= 0;
	virtual Bool IsServiceSortable(int medium,int ServiceType)= 0;
	virtual Bool IsServiceHidden(int medium,int ServiceType)= 0;
	virtual Bool UpdateChannelName(int medium)= 0;
	virtual Bool UpdateLCN(int medium)= 0;
	virtual int ChannelListVariant(void)= 0;
	virtual int DefaultChannelList(void)= 0;
	virtual int DualChannelList(void)= 0;
	virtual int TripleChannelList(void)= 0;
	virtual int SkipInstallationPass(void)= 0;
	virtual Bool AutoCommitOnInstallation(void)= 0;
	virtual Bool TripletKey(int medium)= 0;
	virtual Bool InstallDuplicateServices(int medium)= 0;
	#define IHsvPresetInstallationDiv_SkipAnalog		((int)0 )
	#define IHsvPresetInstallationDiv_SkipDigital		((int)1 )
	#define IHsvPresetInstallationDiv_SkipNone		((int)2 )
	virtual Bool ClearDataOnAutoInstallation(void)= 0;
	virtual int AnalogInstallationSequence(void)= 0;
	#define IHsvPresetInstallationDiv_PalOnly		((int)1 )
	#define IHsvPresetInstallationDiv_PalSecam		((int)2 )
	#define IHsvPresetInstallationDiv_SecamPal		((int)3 )
	#define IHsvPresetInstallationDiv_SecamOnly		((int)4 )
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
	#define IHsvPresetInstallationDiv_KeyInvalid		((int)0 )
	#define IHsvPresetInstallationDiv_KeyOriginalNetworkId		((int)1 )
	#define IHsvPresetInstallationDiv_KeyServiceType		((int)2 )
	#define IHsvPresetInstallationDiv_KeyLCN		((int)3 )
	#define IHsvPresetInstallationDiv_KeyServiceName		((int)4 )
	#define IHsvPresetInstallationDiv_KeyServiceId		((int)5 )
	#define IHsvPresetInstallationDiv_MaxAnalogPresets		((int)100 )
	virtual Bool SupportEmptyAnalogChannels(void)= 0;
	virtual Bool StorePresetsOnStopInstallation(void)= 0;
	virtual int DefaultTunerPresetFrequency(void)= 0;
	virtual int MaxLCNValue(void)= 0;
	virtual int FreqListSortedTableId(void)= 0;
	virtual int GetViterbiBER(void)= 0;
	virtual int DeltaViterbiBER(void)= 0;
};


#define IHsvPresetInstallationDivImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _SecondPassSearchSupported(int country);\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
virtual char* intf ## _GetDefaultPresetName(void);\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual int intf ## _InstallTestStreams(int installationmode,int medium);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _SupportMultipleOriginalNetworkId(int medium);\
virtual Bool intf ## _InstallDuplicateTsids(int medium);\
virtual int intf ## _StreamPriorityToBeUsed(int medium);\
virtual Bool intf ## _IsServiceInstallable(int medium,int ServiceType);\
virtual Bool intf ## _IsServiceSortable(int medium,int ServiceType);\
virtual Bool intf ## _IsServiceHidden(int medium,int ServiceType);\
virtual Bool intf ## _UpdateChannelName(int medium);\
virtual Bool intf ## _UpdateLCN(int medium);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
virtual Bool intf ## _TripletKey(int medium);\
virtual Bool intf ## _InstallDuplicateServices(int medium);\
friend class InterfaceParam<Comp,Bool>;\
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
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual int intf ## _GetViterbiBER(void);\
virtual int intf ## _DeltaViterbiBER(void);\
class Comp ## _ ## intf : public IHsvPresetInstallationDiv \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_iVersion; \
    InterfaceParam<Comp,int> m_TxtResetTimeoutTime; \
    InterfaceParam<Comp,int> m_SorCChannelSupported; \
    InterfaceParam<Comp,int> m_TxtInfoTimeoutTime; \
    InterfaceParam<Comp,int> m_AciOverallTimeoutTime; \
    InterfaceParam<Comp,int> m_NITTimeoutTime; \
    InterfaceParam<Comp,Bool> m_SignalStrengthSorting; \
    InterfaceParam<Comp,int> m_WeakSignalStrengthThreshold; \
    InterfaceParam<Comp,Bool> m_AttenuatorDetectionInInstall; \
    InterfaceParam<Comp,Bool> m_SupportNameExtractionInManIns; \
    InterfaceParam<Comp,Bool> m_SearchForTvSystemInInstallation; \
    InterfaceParam<Comp,Bool> m_SearchForColorSystemInInstallation; \
    InterfaceParam<Comp,Bool> m_SortPresetsInAutoStoreModeNone; \
    InterfaceParam<Comp,int> m_SignalStrengthTimeoutTime; \
    InterfaceParam<Comp,Bool> m_ManualSearchWithWrapAround; \
    InterfaceParam<Comp,Bool> m_ImmediateStoreInAutoInstall; \
    InterfaceParam<Comp,Bool> m_AudioMuteDuringInstall; \
    InterfaceParam<Comp,Bool> m_NameExtractionDuringImplicitManInstall; \
    InterfaceParam<Comp,Bool> m_HandleSorCStationNotFoundinManInstall; \
    InterfaceParam<Comp,int> m_DefaultSystemLanguage; \
    InterfaceParam<Comp,Nat32> m_CookieDefaultValue; \
    InterfaceParam<Comp,int> m_MpegSectionsAcquisitionTimeout; \
    InterfaceParam<Comp,Bool> m_BlankVideo; \
    InterfaceParam<Comp,int> m_SigStrengthThresholdValue; \
    InterfaceParam<Comp,int> m_FirstInstallationPass; \
    InterfaceParam<Comp,int> m_PgctrlMuteColor; \
    InterfaceParam<Comp,int> m_MaxPresetNo; \
    InterfaceParam<Comp,int> m_MinPresetNo; \
    InterfaceParam<Comp,int> m_AnalogOnly; \
    InterfaceParam<Comp,int> m_NotInstall; \
    InterfaceParam<Comp,int> m_Install; \
    InterfaceParam<Comp,int> m_Hide; \
    InterfaceParam<Comp,int> m_ChannelListVariant; \
    InterfaceParam<Comp,int> m_DefaultChannelList; \
    InterfaceParam<Comp,int> m_DualChannelList; \
    InterfaceParam<Comp,int> m_TripleChannelList; \
    InterfaceParam<Comp,int> m_SkipInstallationPass; \
    InterfaceParam<Comp,Bool> m_AutoCommitOnInstallation; \
    InterfaceParam<Comp,Bool> m_ClearDataOnAutoInstallation; \
    InterfaceParam<Comp,int> m_AnalogInstallationSequence; \
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
    InterfaceParam<Comp,Bool> m_SupportEmptyAnalogChannels; \
    InterfaceParam<Comp,Bool> m_StorePresetsOnStopInstallation; \
    InterfaceParam<Comp,int> m_DefaultTunerPresetFrequency; \
    InterfaceParam<Comp,int> m_MaxLCNValue; \
    InterfaceParam<Comp,int> m_FreqListSortedTableId; \
    Comp ## _ ## intf( Comp *parent):m_iVersion(parent),m_TxtResetTimeoutTime(parent),m_SorCChannelSupported(parent),m_TxtInfoTimeoutTime(parent),m_AciOverallTimeoutTime(parent),m_NITTimeoutTime(parent),m_SignalStrengthSorting(parent),m_WeakSignalStrengthThreshold(parent),m_AttenuatorDetectionInInstall(parent),m_SupportNameExtractionInManIns(parent),m_SearchForTvSystemInInstallation(parent),m_SearchForColorSystemInInstallation(parent),m_SortPresetsInAutoStoreModeNone(parent),m_SignalStrengthTimeoutTime(parent),m_ManualSearchWithWrapAround(parent),m_ImmediateStoreInAutoInstall(parent),m_AudioMuteDuringInstall(parent),m_NameExtractionDuringImplicitManInstall(parent),m_HandleSorCStationNotFoundinManInstall(parent),m_DefaultSystemLanguage(parent),m_CookieDefaultValue(parent),m_MpegSectionsAcquisitionTimeout(parent),m_BlankVideo(parent),m_SigStrengthThresholdValue(parent),m_FirstInstallationPass(parent),m_PgctrlMuteColor(parent),m_MaxPresetNo(parent),m_MinPresetNo(parent),m_AnalogOnly(parent),m_NotInstall(parent),m_Install(parent),m_Hide(parent),m_ChannelListVariant(parent),m_DefaultChannelList(parent),m_DualChannelList(parent),m_TripleChannelList(parent),m_SkipInstallationPass(parent),m_AutoCommitOnInstallation(parent),m_ClearDataOnAutoInstallation(parent),m_AnalogInstallationSequence(parent),m_CurrentCountryInvalidLCNSortKey1(parent),m_CurrentCountryInvalidLCNSortKey2(parent),m_CurrentCountryInvalidLCNSortKey3(parent),m_CurrentCountryInvalidLCNSortKey4(parent),m_CurrentCountryInvalidLCNSortKey5(parent),m_OtherCountrySortKey1(parent),m_OtherCountrySortKey2(parent),m_OtherCountrySortKey3(parent),m_OtherCountrySortKey4(parent),m_OtherCountrySortKey5(parent),m_SupportEmptyAnalogChannels(parent),m_StorePresetsOnStopInstallation(parent),m_DefaultTunerPresetFrequency(parent),m_MaxLCNValue(parent),m_FreqListSortedTableId(parent) \
    {\
        m_parent = parent;\
    }\
virtual int iVersion(void){ return m_iVersion.Call();}\
virtual int TxtResetTimeoutTime(void){ return m_TxtResetTimeoutTime.Call();}\
virtual int SorCChannelSupported(void){ return m_SorCChannelSupported.Call();}\
virtual int TxtInfoTimeoutTime(void){ return m_TxtInfoTimeoutTime.Call();}\
virtual int AciOverallTimeoutTime(void){ return m_AciOverallTimeoutTime.Call();}\
virtual int NITTimeoutTime(void){ return m_NITTimeoutTime.Call();}\
virtual Bool SecondPassSearchSupported(int country){ return m_parent->intf ## _SecondPassSearchSupported(country);}\
virtual Bool SignalStrengthSorting(void){ return m_SignalStrengthSorting.Call();}\
virtual int WeakSignalStrengthThreshold(void){ return m_WeakSignalStrengthThreshold.Call();}\
virtual Bool AttenuatorDetectionInInstall(void){ return m_AttenuatorDetectionInInstall.Call();}\
virtual Bool SupportNameExtractionInManIns(void){ return m_SupportNameExtractionInManIns.Call();}\
virtual char* GetDefaultPresetName(void){ return m_parent->intf ## _GetDefaultPresetName();}\
virtual Bool SearchForTvSystemInInstallation(void){ return m_SearchForTvSystemInInstallation.Call();}\
virtual Bool SearchForColorSystemInInstallation(void){ return m_SearchForColorSystemInInstallation.Call();}\
virtual Bool SortPresetsInAutoStoreModeNone(void){ return m_SortPresetsInAutoStoreModeNone.Call();}\
virtual int SignalStrengthTimeoutTime(void){ return m_SignalStrengthTimeoutTime.Call();}\
virtual Bool ManualSearchWithWrapAround(void){ return m_ManualSearchWithWrapAround.Call();}\
virtual Bool ImmediateStoreInAutoInstall(void){ return m_ImmediateStoreInAutoInstall.Call();}\
virtual Bool AudioMuteDuringInstall(void){ return m_AudioMuteDuringInstall.Call();}\
virtual Bool NameExtractionDuringImplicitManInstall(void){ return m_NameExtractionDuringImplicitManInstall.Call();}\
virtual Bool HandleSorCStationNotFoundinManInstall(void){ return m_HandleSorCStationNotFoundinManInstall.Call();}\
virtual int DefaultSystemLanguage(void){ return m_DefaultSystemLanguage.Call();}\
virtual Nat32 CookieDefaultValue(void){ return m_CookieDefaultValue.Call();}\
virtual int MpegSectionsAcquisitionTimeout(void){ return m_MpegSectionsAcquisitionTimeout.Call();}\
virtual Bool BlankVideo(void){ return m_BlankVideo.Call();}\
virtual int SigStrengthThresholdValue(void){ return m_SigStrengthThresholdValue.Call();}\
virtual int FirstInstallationPass(void){ return m_FirstInstallationPass.Call();}\
virtual int PgctrlMuteColor(void){ return m_PgctrlMuteColor.Call();}\
virtual int MaxPresetNo(void){ return m_MaxPresetNo.Call();}\
virtual int MinPresetNo(void){ return m_MinPresetNo.Call();}\
virtual int AnalogOnly(void){ return m_AnalogOnly.Call();}\
virtual int InstallTestStreams(int installationmode,int medium){ return m_parent->intf ## _InstallTestStreams(installationmode,medium);}\
virtual int NotInstall(void){ return m_NotInstall.Call();}\
virtual int Install(void){ return m_Install.Call();}\
virtual int Hide(void){ return m_Hide.Call();}\
virtual Bool SupportMultipleOriginalNetworkId(int medium){ return m_parent->intf ## _SupportMultipleOriginalNetworkId(medium);}\
virtual Bool InstallDuplicateTsids(int medium){ return m_parent->intf ## _InstallDuplicateTsids(medium);}\
virtual int StreamPriorityToBeUsed(int medium){ return m_parent->intf ## _StreamPriorityToBeUsed(medium);}\
virtual Bool IsServiceInstallable(int medium,int ServiceType){ return m_parent->intf ## _IsServiceInstallable(medium,ServiceType);}\
virtual Bool IsServiceSortable(int medium,int ServiceType){ return m_parent->intf ## _IsServiceSortable(medium,ServiceType);}\
virtual Bool IsServiceHidden(int medium,int ServiceType){ return m_parent->intf ## _IsServiceHidden(medium,ServiceType);}\
virtual Bool UpdateChannelName(int medium){ return m_parent->intf ## _UpdateChannelName(medium);}\
virtual Bool UpdateLCN(int medium){ return m_parent->intf ## _UpdateLCN(medium);}\
virtual int ChannelListVariant(void){ return m_ChannelListVariant.Call();}\
virtual int DefaultChannelList(void){ return m_DefaultChannelList.Call();}\
virtual int DualChannelList(void){ return m_DualChannelList.Call();}\
virtual int TripleChannelList(void){ return m_TripleChannelList.Call();}\
virtual int SkipInstallationPass(void){ return m_SkipInstallationPass.Call();}\
virtual Bool AutoCommitOnInstallation(void){ return m_AutoCommitOnInstallation.Call();}\
virtual Bool TripletKey(int medium){ return m_parent->intf ## _TripletKey(medium);}\
virtual Bool InstallDuplicateServices(int medium){ return m_parent->intf ## _InstallDuplicateServices(medium);}\
virtual Bool ClearDataOnAutoInstallation(void){ return m_ClearDataOnAutoInstallation.Call();}\
virtual int AnalogInstallationSequence(void){ return m_AnalogInstallationSequence.Call();}\
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
virtual Bool SupportEmptyAnalogChannels(void){ return m_SupportEmptyAnalogChannels.Call();}\
virtual Bool StorePresetsOnStopInstallation(void){ return m_StorePresetsOnStopInstallation.Call();}\
virtual int DefaultTunerPresetFrequency(void){ return m_DefaultTunerPresetFrequency.Call();}\
virtual int MaxLCNValue(void){ return m_MaxLCNValue.Call();}\
virtual int FreqListSortedTableId(void){ return m_FreqListSortedTableId.Call();}\
virtual int GetViterbiBER(void){ return m_parent->intf ## _GetViterbiBER();}\
virtual int DeltaViterbiBER(void){ return m_parent->intf ## _DeltaViterbiBER();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
