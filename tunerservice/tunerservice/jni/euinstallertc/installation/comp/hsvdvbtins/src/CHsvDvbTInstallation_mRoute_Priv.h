#ifndef  _CHSVDVBTINSTALLATION_MROUTE_PRIV_H
#define  _CHSVDVBTINSTALLATION_MROUTE_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvDigitalScanRoute.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDVBSettings.h>
#include <IHsvInstallation2.h>
#include <CTCMwBase.h>
class CHsvDvbTInstallation_mRoute_Priv;
#define CLASSSCOPE CHsvDvbTInstallation_mRoute_Priv::
#include "locals_mRoute.h"

class CHsvDvbTInstallation_mRoute_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbTInstallation_mRoute_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mRoute.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmControlNotifyExImpl(CHsvDvbTInstallation_mRoute_Priv,ctrlN);
IHsvFrontEndApiNotifyImpl(CHsvDvbTInstallation_mRoute_Priv,feapiN);
IHsvDigitalScanImpl(CHsvDvbTInstallation_mRoute_Priv,idvbt);
IHsvDigitalScanRouteImpl(CHsvDvbTInstallation_mRoute_Priv,iroute);
IHsvDigitalScanImpl(CHsvDvbTInstallation_mRoute_Priv,istub);
IHsvPowerImpl(CHsvDvbTInstallation_mRoute_Priv,pow);
IHsvStreamNotifyImpl(CHsvDvbTInstallation_mRoute_Priv,strapiN);
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	idvbt;

ProvidesInterface<IHsvDigitalScanRoute>	iroute;

ProvidesInterface<IHsvDigitalScan>	istub;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSdmControlNotifyEx>	ibctrlN;
RequiresInterface<IHsvPower>	ibpow;
RequiresInterface<IHsvStreamNotify>	ibstrapiN;
RequiresInterface<IHsvSdmControlNotifyEx>	icctrlN;
RequiresInterface<IHsvPower>	icntrypow;
RequiresInterface<IHsvStreamNotify>	icntrystrapiN;
RequiresInterface<IHsvPower>	idatapow;
RequiresInterface<IHsvSdmControlNotifyEx>	idctrlN;
RequiresInterface<IHsvDigitalScan>	idtr;
RequiresInterface<IHsvFrontEndApiNotify>	idtrfeN;
RequiresInterface<IHsvPower>	idtrpow;
RequiresInterface<IHsvStreamNotify>	idstrapiN;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvSdmControlNotifyEx>	ifctrlN;
RequiresInterface<IHsvDigitalScan>	ifull;
RequiresInterface<IHsvFrontEndApiNotify>	ifullfeN;
RequiresInterface<IHsvPower>	ifullpow;
RequiresInterface<IHsvSdmControlNotifyEx>	iqctrlN;
RequiresInterface<IHsvDigitalScan>	iquick;
RequiresInterface<IHsvFrontEndApiNotify>	iquickfeN;
RequiresInterface<IHsvPower>	iquickpow;
RequiresInterface<IHsvPower>	isetpow;
RequiresInterface<IHsvInstallation2>	rins;

public:
CHsvDvbTInstallation_mRoute_Priv():i__ctrlN(this),i__feapiN(this),i__idvbt(this),i__iroute(this),i__istub(this),i__pow(this),i__strapiN(this)
{
ctrlN	=	&i__ctrlN;
feapiN	=	&i__feapiN;
idvbt	=	&i__idvbt;
iroute	=	&i__iroute;
istub	=	&i__istub;
pow	=	&i__pow;
strapiN	=	&i__strapiN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define eurdiv_iPresent() (eurdiv.Present())
#define eurdiv_iVersion	eurdiv->iVersion()
#define eurdiv_NITTimeoutTime	eurdiv->NITTimeoutTime()
#define eurdiv_AttenuatorDetectionInInstall	eurdiv->AttenuatorDetectionInInstall()
#define eurdiv_SupportNameExtractionInManIns	eurdiv->SupportNameExtractionInManIns()
#define eurdiv_WeakSignalStrengthThreshold	eurdiv->WeakSignalStrengthThreshold()
#define eurdiv_SignalStrengthSorting	eurdiv->SignalStrengthSorting()
#define eurdiv_SearchForColorSystemInInstallation	eurdiv->SearchForColorSystemInInstallation()
#define eurdiv_SearchForTvSystemInInstallation	eurdiv->SearchForTvSystemInInstallation()
#define eurdiv_ManualSearchWithWrapAround	eurdiv->ManualSearchWithWrapAround()
#define eurdiv_SortPresetsInAutoStoreModeNone	eurdiv->SortPresetsInAutoStoreModeNone()
#define eurdiv_SignalStrengthTimeoutTime	eurdiv->SignalStrengthTimeoutTime()
#define eurdiv_DefaultTunerPresetFrequency	eurdiv->DefaultTunerPresetFrequency()
#define eurdiv_PgctrlMuteColor	eurdiv->PgctrlMuteColor()
#define eurdiv_ChannelNameLength	eurdiv->ChannelNameLength()
#define eurdiv_PresetNameLength	eurdiv->PresetNameLength()
#define eurdiv_MuteRequiredOnInstallation	eurdiv->MuteRequiredOnInstallation()
#define eurdiv_ClearDataOnAutoInstallation	eurdiv->ClearDataOnAutoInstallation()
#define eurdiv_AnalogOnly()	eurdiv->AnalogOnly()
#define eurdiv_InstallTestStreams(installationmode,medium)	eurdiv->InstallTestStreams(installationmode,medium)
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_NoOfVirtualChannelsSupported(medium)	eurdiv->NoOfVirtualChannelsSupported(medium)
#define eurdiv_SupportMultipleOriginalNetworkId(medium)	eurdiv->SupportMultipleOriginalNetworkId(medium)
#define eurdiv_ForceLCNSyntax(medium)	eurdiv->ForceLCNSyntax(medium)
#define eurdiv_InstallDuplicateTsids(medium)	eurdiv->InstallDuplicateTsids(medium)
#define eurdiv_DefaultStreamPriority(medium)	eurdiv->DefaultStreamPriority(medium)
#define eurdiv_IsServiceInstallable(medium,ServiceType)	eurdiv->IsServiceInstallable(medium,ServiceType)
#define eurdiv_IsServiceSortable(medium,ServiceType)	eurdiv->IsServiceSortable(medium,ServiceType)
#define eurdiv_IsServiceHidden(medium,ServiceType)	eurdiv->IsServiceHidden(medium,ServiceType)
#define eurdiv_AcceptedStreamType(medium,StreamType)	eurdiv->AcceptedStreamType(medium,StreamType)
#define eurdiv_UpdateChannelName(medium)	eurdiv->UpdateChannelName(medium)
#define eurdiv_IsApmeaChannelListCountry()	eurdiv->IsApmeaChannelListCountry()
#define eurdiv_IsApmeaNetworkUpdateCountry()	eurdiv->IsApmeaNetworkUpdateCountry()
#define eurdiv_IsDbookCountry()	eurdiv->IsDbookCountry()
#define eurdiv_SkipInstallationPass	eurdiv->SkipInstallationPass()
#define eurdiv_FirstInstallationPass	eurdiv->FirstInstallationPass()
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_UpdateLCN(medium)	eurdiv->UpdateLCN(medium)
#define eurdiv_TxtInfoTimeout	eurdiv->TxtInfoTimeout()
#define eurdiv_VideoMuteColor	eurdiv->VideoMuteColor()
#define eurdiv_VideoMuteColorForLocks	eurdiv->VideoMuteColorForLocks()
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	eurdiv->DecoderSupported()
#define eurdiv_BreakInSupported	eurdiv->BreakInSupported()
#define eurdiv_ScartRuleSupported	eurdiv->ScartRuleSupported()
#define eurdiv_HsvAntennaAnalogTable	eurdiv->HsvAntennaAnalogTable()
#define eurdiv_HsvAntennaDigSrvcTable	eurdiv->HsvAntennaDigSrvcTable()
#define eurdiv_HsvAntennaDigPtcTable	eurdiv->HsvAntennaDigPtcTable()
#define eurdiv_HsvAntennaFreqMapTable	eurdiv->HsvAntennaFreqMapTable()
#define eurdiv_PersistentMemUpdateTimeout	eurdiv->PersistentMemUpdateTimeout()
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	eurdiv->MaxNoOfChannelsToStoreAntennaUserTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigPtcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaAnalogTable	eurdiv->MaxNoOfChannelsToStoreAntennaAnalogTable()
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreAntennaFreqMapTable()
#define eurdiv_IsHDSubtitleSupported()	eurdiv->IsHDSubtitleSupported()
#define eurdiv_AvSignalDetectionTimeOut	eurdiv->AvSignalDetectionTimeOut()
#define eurdiv_HearingImpairedOn	eurdiv->HearingImpairedOn()
#define eurdiv_VisuallyImpairedOn()	eurdiv->VisuallyImpairedOn()
#define eurdiv_IsQaaSupported()	eurdiv->IsQaaSupported()
#define eurdiv_IsPremixedVISupported()	eurdiv->IsPremixedVISupported()
#define eurdiv_EPGSecondaryDirName	eurdiv->EPGSecondaryDirName()
#define eurdiv_DefaultCharacterTable	eurdiv->DefaultCharacterTable()
#define eurdiv_ShortInfoCacheForCountry	eurdiv->ShortInfoCacheForCountry()
#define eurdiv_OUI	eurdiv->OUI()
#define eurdiv_HardwareModel	eurdiv->HardwareModel()
#define eurdiv_HardwareVersion	eurdiv->HardwareVersion()
#define eurdiv_GetNoOfBackBuffers(clientId)	eurdiv->GetNoOfBackBuffers(clientId)
#define eurdiv_SubtitleTimeOut	eurdiv->SubtitleTimeOut()
#define eurdiv_IsMpeg4STBoltOnSupported()	eurdiv->IsMpeg4STBoltOnSupported()
#define eurdiv_IsAVCDescriptorSupported()	eurdiv->IsAVCDescriptorSupported()
#define eurdiv_ForceCharacterTable()	eurdiv->ForceCharacterTable()
#define eurdiv_RegionalCharacterTable()	eurdiv->RegionalCharacterTable()
#define eurdiv_CurrentCountryInvalidLCNSortKey1	eurdiv->CurrentCountryInvalidLCNSortKey1()
#define eurdiv_CurrentCountryInvalidLCNSortKey2	eurdiv->CurrentCountryInvalidLCNSortKey2()
#define eurdiv_CurrentCountryInvalidLCNSortKey3	eurdiv->CurrentCountryInvalidLCNSortKey3()
#define eurdiv_CurrentCountryInvalidLCNSortKey4	eurdiv->CurrentCountryInvalidLCNSortKey4()
#define eurdiv_CurrentCountryInvalidLCNSortKey5	eurdiv->CurrentCountryInvalidLCNSortKey5()
#define eurdiv_OtherCountrySortKey1	eurdiv->OtherCountrySortKey1()
#define eurdiv_OtherCountrySortKey2	eurdiv->OtherCountrySortKey2()
#define eurdiv_OtherCountrySortKey3	eurdiv->OtherCountrySortKey3()
#define eurdiv_OtherCountrySortKey4	eurdiv->OtherCountrySortKey4()
#define eurdiv_OtherCountrySortKey5	eurdiv->OtherCountrySortKey5()
#define eurdiv_KeyInvalid	IHsvEuropeDiversity2_KeyInvalid
#define eurdiv_KeyOriginalNetworkId	IHsvEuropeDiversity2_KeyOriginalNetworkId
#define eurdiv_KeyServiceType	IHsvEuropeDiversity2_KeyServiceType
#define eurdiv_KeyLCN	IHsvEuropeDiversity2_KeyLCN
#define eurdiv_KeyServiceName	IHsvEuropeDiversity2_KeyServiceName
#define eurdiv_KeyServiceId	IHsvEuropeDiversity2_KeyServiceId
#define eurdiv_TripletKey(medium)	eurdiv->TripletKey(medium)
#define eurdiv_InstallDuplicateServices(medium)	eurdiv->InstallDuplicateServices(medium)
#define eurdiv_MeasureSignalStrengthWhilePlaying	eurdiv->MeasureSignalStrengthWhilePlaying()
#define eurdiv_AnalogInstallationSequence	eurdiv->AnalogInstallationSequence()
#define eurdiv_Automatic	IHsvEuropeDiversity2_Automatic
#define eurdiv_PalOnly	IHsvEuropeDiversity2_PalOnly
#define eurdiv_PalSecam	IHsvEuropeDiversity2_PalSecam
#define eurdiv_SecamPal	IHsvEuropeDiversity2_SecamPal
#define eurdiv_SecamOnly	IHsvEuropeDiversity2_SecamOnly
#define eurdiv_ChannelListVariant	eurdiv->ChannelListVariant()
#define eurdiv_DefaultChannelList	IHsvEuropeDiversity2_DefaultChannelList
#define eurdiv_DualChannelList	IHsvEuropeDiversity2_DualChannelList
#define eurdiv_TripleChannelList	IHsvEuropeDiversity2_TripleChannelList
#define eurdiv_EnableCountryFallbackForLCNSyntax(medium)	eurdiv->EnableCountryFallbackForLCNSyntax(medium)
#define eurdiv_EnableONIDFallbackForLCNSyntax(medium)	eurdiv->EnableONIDFallbackForLCNSyntax(medium)
#define eurdiv_HsvCableAnalogTable	eurdiv->HsvCableAnalogTable()
#define eurdiv_HsvCableDigSrvcTable	eurdiv->HsvCableDigSrvcTable()
#define eurdiv_HsvCableDigPtcTable	eurdiv->HsvCableDigPtcTable()
#define eurdiv_HsvCableSvcListDescTable	eurdiv->HsvCableSvcListDescTable()
#define eurdiv_HsvCableFreqMapTable	eurdiv->HsvCableFreqMapTable()
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	eurdiv->MaxNoOfChannelsToStoreCableUserTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreCableDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	eurdiv->MaxNoOfChannelsToStoreCableDigPtcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableAnalogTable	eurdiv->MaxNoOfChannelsToStoreCableAnalogTable()
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreCableFreqMapTable()
#define eurdiv_IsDVBCSupported()	eurdiv->IsDVBCSupported()
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_GetDefaultScanMode(medium)	eurdiv->GetDefaultScanMode(medium)
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanAnalog	IHsvEuropeDiversity2_ScanAnalog
#define eurdiv_ScanDVBT	IHsvEuropeDiversity2_ScanDVBT
#define eurdiv_ScanDVBC	IHsvEuropeDiversity2_ScanDVBC
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_ScanDVBTMpegOnly	IHsvEuropeDiversity2_ScanDVBTMpegOnly
#define eurdiv_ScanDVBCLite	IHsvEuropeDiversity2_ScanDVBCLite
#define eurdiv_GetScanPreference(medium,installationmode)	eurdiv->GetScanPreference(medium,installationmode)
#define eurdiv_GetNextScan(medium,installationmode,ScanPreference)	eurdiv->GetNextScan(medium,installationmode,ScanPreference)
#define eurdiv_GetDVBTMode()	eurdiv->GetDVBTMode()
#define eurdiv_GetDVBCMode()	eurdiv->GetDVBCMode()
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_GetNitPriority(medium)	eurdiv->GetNitPriority(medium)
#define eurdiv_IsServiceListDescriptorMandatory(medium)	eurdiv->IsServiceListDescriptorMandatory(medium)
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_GetAudioPreference()	eurdiv->GetAudioPreference()
#define eurdiv_GetSubtitlePreference()	eurdiv->GetSubtitlePreference()
#define eurdiv_UserPreferredAudioFormat()	eurdiv->UserPreferredAudioFormat()
#define eurdiv_IsFrequencyListStorageRequired()	eurdiv->IsFrequencyListStorageRequired()
#define eurdiv_GetDefaultAttributeValues(attrib,country,mode,length,values)	eurdiv->GetDefaultAttributeValues(attrib,country,mode,length,values)
#define eurdiv_HsvDVBCSettingsFilePath	eurdiv->HsvDVBCSettingsFilePath()
#define eurdiv_HsvCableDelSysDescFilePath	eurdiv->HsvCableDelSysDescFilePath()
#define eurdiv_HsvServiceListDescFilePath	eurdiv->HsvServiceListDescFilePath()
#define eurdiv_MaxLCNValue	eurdiv->MaxLCNValue()
#define eurdiv_IsBackgroundInstallRequired(medium)	eurdiv->IsBackgroundInstallRequired(medium)
#define eurdiv_SupportLCNVersion2(medium)	eurdiv->SupportLCNVersion2(medium)
#define eurdiv_ParseLCN(medium,installationmode)	eurdiv->ParseLCN(medium,installationmode)
#define eurdiv_IsPreScanSupported(medium)	eurdiv->IsPreScanSupported(medium)
#define eurdiv_SortNonLCNs(medium)	eurdiv->SortNonLCNs(medium)
#define eurdiv_SupportHDSLCN(medium)	eurdiv->SupportHDSLCN(medium)
#define eurdiv_IsServiceAttrbDescSupported(medium)	eurdiv->IsServiceAttrbDescSupported(medium)
#define eurdiv_IsTSRelocatedDescSupported(medium)	eurdiv->IsTSRelocatedDescSupported(medium)
#define eurdiv_SDTActual	IHsvEuropeDiversity2_SDTActual
#define eurdiv_SDTOther	IHsvEuropeDiversity2_SDTOther
#define eurdiv_SDTNone	IHsvEuropeDiversity2_SDTNone
#define eurdiv_GetAltSDTType(medium)	eurdiv->GetAltSDTType(medium)
#define eurdiv_AltHomingFrequency	IHsvEuropeDiversity2_AltHomingFrequency
#define eurdiv_AltTSRelocatedDesc	IHsvEuropeDiversity2_AltTSRelocatedDesc
#define eurdiv_AltNone	IHsvEuropeDiversity2_AltNone
#define eurdiv_GetAlternateTSLocation(medium)	eurdiv->GetAlternateTSLocation(medium)
#define eurdiv_GetAltFreqScanSupported(country)	eurdiv->GetAltFreqScanSupported(country)
#define eurdiv_FreqListDescriptorSupported(medium)	eurdiv->FreqListDescriptorSupported(medium)
#define eurdiv_IsAc3AudioSupported()	eurdiv->IsAc3AudioSupported()
#define eurdiv_GetDefaultAnalogInstallStatus(country)	eurdiv->GetDefaultAnalogInstallStatus(country)
#define eurdiv_StaticTable()	eurdiv->StaticTable()
#define eurdiv_GetDefaultDigitalInstallStatus(country)	eurdiv->GetDefaultDigitalInstallStatus(country)
#define eurdiv_IsMultifeedSupported()	eurdiv->IsMultifeedSupported()
#define eurdiv_IsZeroLCNHidden()	eurdiv->IsZeroLCNHidden()
#define eurdiv_GetViterbiBER()	eurdiv->GetViterbiBER()
#define eurdiv_DeltaViterbiBER()	eurdiv->DeltaViterbiBER()
#define eurdiv_GetShortInfoCacheSize()	eurdiv->GetShortInfoCacheSize()
#define eurdiv_GetDeltaSQI()	eurdiv->GetDeltaSQI()
#define eurdiv_GetDeltaSSI()	eurdiv->GetDeltaSSI()
#define eurdiv_AutomaticAnalogPresetAllocation()	eurdiv->AutomaticAnalogPresetAllocation()
#define eurdiv_AutomaticDigitalPresetAllocation()	eurdiv->AutomaticDigitalPresetAllocation()
#define eurdiv_AnalogStartPreset(country,medium,numRecords)	eurdiv->AnalogStartPreset(country,medium,numRecords)
#define eurdiv_AnalogEndPreset(country,medium)	eurdiv->AnalogEndPreset(country,medium)
#define eurdiv_NonRadioStartPreset(country,medium,numRecords)	eurdiv->NonRadioStartPreset(country,medium,numRecords)
#define eurdiv_NonRadioEndPreset(country,medium)	eurdiv->NonRadioEndPreset(country,medium)
#define eurdiv_RadioStartPreset(country,medium,numRecords)	eurdiv->RadioStartPreset(country,medium,numRecords)
#define eurdiv_RadioEndPreset(country,medium)	eurdiv->RadioEndPreset(country,medium)
#define eurdiv_IsHDSimulcastSupported()	eurdiv->IsHDSimulcastSupported()
#define eurdiv_IsDVBT2Supported()	eurdiv->IsDVBT2Supported()
#define eurdiv_MultipleLCNSupported()	eurdiv->MultipleLCNSupported()
#define eurdiv_SubtitlePidFallbackFirstPMT()	eurdiv->SubtitlePidFallbackFirstPMT()
#define eurdiv_DeleteTSNotIntransmission()	eurdiv->DeleteTSNotIntransmission()
#define eurdiv_ReapplyChildLockOnEventChange()	eurdiv->ReapplyChildLockOnEventChange()
#define eurdiv_DeleteServiceOnFly()	eurdiv->DeleteServiceOnFly()
#define ibctrlN_iPresent() (ibctrlN.Present())
#define ibctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ibctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ibctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ibctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ibctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ibctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ibctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ibctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ibctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ibctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ibctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ibctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ibctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ibctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ibctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ibctrlN_OnEvent(dmx,eventid,value)	ibctrlN->OnEvent(dmx,eventid,value)
#define ibpow_iPresent() (ibpow.Present())
#define ibpow_Init()	ibpow->Init()
#define ibpow_TurnOn()	ibpow->TurnOn()
#define ibpow_TurnOff()	ibpow->TurnOff()
#define ibstrapiN_iPresent() (ibstrapiN.Present())
#define ibstrapiN_OnCompleted(dest,spid)	ibstrapiN->OnCompleted(dest,spid)
#define ibstrapiN_OnAdded(dest,spid,key1,key2,key3)	ibstrapiN->OnAdded(dest,spid,key1,key2,key3)
#define ibstrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	ibstrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define ibstrapiN_OnRemoved(dest,spid,key1,key2,key3)	ibstrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define idstrapiN_iPresent() (idstrapiN.Present())
#define idstrapiN_OnCompleted(dest,spid)	idstrapiN->OnCompleted(dest,spid)
#define idstrapiN_OnAdded(dest,spid,key1,key2,key3)	idstrapiN->OnAdded(dest,spid,key1,key2,key3)
#define idstrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	idstrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define idstrapiN_OnRemoved(dest,spid,key1,key2,key3)	idstrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define icctrlN_iPresent() (icctrlN.Present())
#define icctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define icctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define icctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define icctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define icctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define icctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define icctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define icctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define icctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define icctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define icctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define icctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define icctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define icctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define icctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define icctrlN_OnEvent(dmx,eventid,value)	icctrlN->OnEvent(dmx,eventid,value)
#define icntrypow_iPresent() (icntrypow.Present())
#define icntrypow_Init()	icntrypow->Init()
#define icntrypow_TurnOn()	icntrypow->TurnOn()
#define icntrypow_TurnOff()	icntrypow->TurnOff()
#define icntrystrapiN_iPresent() (icntrystrapiN.Present())
#define icntrystrapiN_OnCompleted(dest,spid)	icntrystrapiN->OnCompleted(dest,spid)
#define icntrystrapiN_OnAdded(dest,spid,key1,key2,key3)	icntrystrapiN->OnAdded(dest,spid,key1,key2,key3)
#define icntrystrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	icntrystrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define icntrystrapiN_OnRemoved(dest,spid,key1,key2,key3)	icntrystrapiN->OnRemoved(dest,spid,key1,key2,key3)
#define idatapow_iPresent() (idatapow.Present())
#define idatapow_Init()	idatapow->Init()
#define idatapow_TurnOn()	idatapow->TurnOn()
#define idatapow_TurnOff()	idatapow->TurnOff()
#define idctrlN_iPresent() (idctrlN.Present())
#define idctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define idctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define idctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define idctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define idctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define idctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define idctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define idctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define idctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define idctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define idctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define idctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define idctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define idctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define idctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define idctrlN_OnEvent(dmx,eventid,value)	idctrlN->OnEvent(dmx,eventid,value)
#define idtr_iPresent() (idtr.Present())
#define idtr_stidle	IHsvDigitalScan_stidle
#define idtr_stfewait	IHsvDigitalScan_stfewait
#define idtr_stdmxwait	IHsvDigitalScan_stdmxwait
#define idtr_stdecision	IHsvDigitalScan_stdecision
#define idtr_Initialise()	idtr->Initialise()
#define idtr_StartInstallation(source,ptc,mode)	idtr->StartInstallation(source,ptc,mode)
#define idtr_StopInstallation()	idtr->StopInstallation()
#define idtr_StartDigitalScan()	idtr->StartDigitalScan()
#define idtr_StartDigitalTuning(frequency)	idtr->StartDigitalTuning(frequency)
#define idtr_StopDigitalScan()	idtr->StopDigitalScan()
#define idtr_GetNoOfPass()	idtr->GetNoOfPass()
#define idtr_GetCurrentPass()	idtr->GetCurrentPass()
#define idtr_GetPTCInfo(ptc)	idtr->GetPTCInfo(ptc)
#define idtr_StoreWeakSignalInstallationChannel()	idtr->StoreWeakSignalInstallationChannel()
#define idtr_GetNumberOfDigitalChannelsFound()	idtr->GetNumberOfDigitalChannelsFound()
#define idtr_GetNumberOfDigitalChannelsRemoved()	idtr->GetNumberOfDigitalChannelsRemoved()
#define idtr_GetTargetNitType(NetworkId)	idtr->GetTargetNitType(NetworkId)
#define idtr_GetCurrentState()	idtr->GetCurrentState()
#define idtr_GetSDTType()	idtr->GetSDTType()
#define idtr_GetAltTSValues(ONID,TSID)	idtr->GetAltTSValues(ONID,TSID)
#define idtr_GetCurTSValues(ONID,TSID)	idtr->GetCurTSValues(ONID,TSID)
#define idtr_GetStreamPriority()	idtr->GetStreamPriority()
#define idtr_SetStreamPriority(prio)	idtr->SetStreamPriority(prio)
#define idtr_SyncComplete()	idtr->SyncComplete()
#define idtr_ClearCache()	idtr->ClearCache()
#define idtr_GetPLPIds(PLPIds)	idtr->GetPLPIds(PLPIds)
#define idtr_GetHierarchyMode()	idtr->GetHierarchyMode()
#define idtr_ZiggoGetPTCInfo(ptc,Onid,Tsid)	idtr->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define idtr_ZiggoGetSDTType(Frequency)	idtr->ZiggoGetSDTType(Frequency)
#define idtr_GetEpgBarkerMux(ONID,TSID)	idtr->GetEpgBarkerMux(ONID,TSID)
#define idtr_ZiggoNetworkDataSet(ActionValue)	idtr->ZiggoNetworkDataSet(ActionValue)
#define idtr_ClearPersistent()	idtr->ClearPersistent()
#define idtrfeN_iPresent() (idtrfeN.Present())
#define idtrfeN_OnSearchStateChanged(state)	idtrfeN->OnSearchStateChanged(state)
#define idtrfeN_OnSearchInProgress(state)	idtrfeN->OnSearchInProgress(state)
#define idtrfeN_OnStationFound()	idtrfeN->OnStationFound()
#define idtrfeN_OnStationNotFound()	idtrfeN->OnStationNotFound()
#define idtrfeN_OnTvSystemDetected(tvSystem)	idtrfeN->OnTvSystemDetected(tvSystem)
#define idtrfeN_OnAfcFreqChanged(freq)	idtrfeN->OnAfcFreqChanged(freq)
#define idtrfeN_OnAfcLimitReached(freq)	idtrfeN->OnAfcLimitReached(freq)
#define idtrfeN_OnAfcModeChanged()	idtrfeN->OnAfcModeChanged()
#define idtrfeN_OnMeasReady(ssm,strength)	idtrfeN->OnMeasReady(ssm,strength)
#define idtrfeN_OnMeasAborted(ssm)	idtrfeN->OnMeasAborted(ssm)
#define idtrfeN_OnConstellationDetected(constellation)	idtrfeN->OnConstellationDetected(constellation)
#define idtrfeN_OnIqModeDetected(mode)	idtrfeN->OnIqModeDetected(mode)
#define idtrfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	idtrfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define idtrfeN_OnHierarchyModeDetected(mode)	idtrfeN->OnHierarchyModeDetected(mode)
#define idtrfeN_OnGuardIntervalDetected(interval)	idtrfeN->OnGuardIntervalDetected(interval)
#define idtrfeN_OnTxModeDetected(mode)	idtrfeN->OnTxModeDetected(mode)
#define idtrfeN_OnChanBandwidthDetected(bandwith)	idtrfeN->OnChanBandwidthDetected(bandwith)
#define idtrfeN_OnCarrierPresentChanged(carrier)	idtrfeN->OnCarrierPresentChanged(carrier)
#define idtrfeN_OnBerThresholdCrossed(ber,berThreshold)	idtrfeN->OnBerThresholdCrossed(ber,berThreshold)
#define idtrpow_iPresent() (idtrpow.Present())
#define idtrpow_Init()	idtrpow->Init()
#define idtrpow_TurnOn()	idtrpow->TurnOn()
#define idtrpow_TurnOff()	idtrpow->TurnOff()
#define idvbset_iPresent() (idvbset.Present())
#define idvbset_SetAttribute(installationmode,attribute,value)	idvbset->SetAttribute(installationmode,attribute,value)
#define idvbset_GetAttribute(installationmode,attribute)	idvbset->GetAttribute(installationmode,attribute)
#define idvbset_ResetAttributeToDefault(installationmode,attribute)	idvbset->ResetAttributeToDefault(installationmode,attribute)
#define idvbset_ResetAttributeToPersistent(installationmode,attribute)	idvbset->ResetAttributeToPersistent(installationmode,attribute)
#define idvbset_ResetAllToDefault()	idvbset->ResetAllToDefault()
#define idvbset_ResetAllToPersistent()	idvbset->ResetAllToPersistent()
#define idvbset_GetAttributeLength(installationmode,attribute)	idvbset->GetAttributeLength(installationmode,attribute)
#define idvbset_GetNextAttributeValue(installationmode,attribute,value)	idvbset->GetNextAttributeValue(installationmode,attribute,value)
#define idvbset_SetPreferred(attribute,value,preferred)	idvbset->SetPreferred(attribute,value,preferred)
#define idvbset_GetAttributeRange(installationmode,attribute,minValue,maxValue)	idvbset->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define idvbset_GetAttributeMode(installationmode,attribute)	idvbset->GetAttributeMode(installationmode,attribute)
#define idvbset_SetAttributeMode(installationmode,attribute,attributeMode)	idvbset->SetAttributeMode(installationmode,attribute,attributeMode)
#define idvbset_CopyTemporaryToPersistent()	idvbset->CopyTemporaryToPersistent()
#define idvbset_ClearPersistent()	idvbset->ClearPersistent()
#define idvbset_CommitPreferred()	idvbset->CommitPreferred()
#define idvbset_IsAvailable(installationmode,attribute)	idvbset->IsAvailable(installationmode,attribute)
#define idvbset_SetUserSymbolRates(installationmode,values,len)	idvbset->SetUserSymbolRates(installationmode,values,len)
#define idvbset_GetUserSymbolRates(installationmode,values,len)	idvbset->GetUserSymbolRates(installationmode,values,len)
#define idvbset_GetPredefinedSymbolRates(installationmode,values,len)	idvbset->GetPredefinedSymbolRates(installationmode,values,len)
#define idvbset_ClearUserSymbolRates()	idvbset->ClearUserSymbolRates()
#define idvbset_GetONIDNetworkOperator(ONID)	idvbset->GetONIDNetworkOperator(ONID)
#define ifctrlN_iPresent() (ifctrlN.Present())
#define ifctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ifctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ifctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ifctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ifctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ifctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ifctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ifctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ifctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ifctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ifctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ifctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ifctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ifctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ifctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ifctrlN_OnEvent(dmx,eventid,value)	ifctrlN->OnEvent(dmx,eventid,value)
#define ifull_iPresent() (ifull.Present())
#define ifull_stidle	IHsvDigitalScan_stidle
#define ifull_stfewait	IHsvDigitalScan_stfewait
#define ifull_stdmxwait	IHsvDigitalScan_stdmxwait
#define ifull_stdecision	IHsvDigitalScan_stdecision
#define ifull_Initialise()	ifull->Initialise()
#define ifull_StartInstallation(source,ptc,mode)	ifull->StartInstallation(source,ptc,mode)
#define ifull_StopInstallation()	ifull->StopInstallation()
#define ifull_StartDigitalScan()	ifull->StartDigitalScan()
#define ifull_StartDigitalTuning(frequency)	ifull->StartDigitalTuning(frequency)
#define ifull_StopDigitalScan()	ifull->StopDigitalScan()
#define ifull_GetNoOfPass()	ifull->GetNoOfPass()
#define ifull_GetCurrentPass()	ifull->GetCurrentPass()
#define ifull_GetPTCInfo(ptc)	ifull->GetPTCInfo(ptc)
#define ifull_StoreWeakSignalInstallationChannel()	ifull->StoreWeakSignalInstallationChannel()
#define ifull_GetNumberOfDigitalChannelsFound()	ifull->GetNumberOfDigitalChannelsFound()
#define ifull_GetNumberOfDigitalChannelsRemoved()	ifull->GetNumberOfDigitalChannelsRemoved()
#define ifull_GetTargetNitType(NetworkId)	ifull->GetTargetNitType(NetworkId)
#define ifull_GetCurrentState()	ifull->GetCurrentState()
#define ifull_GetSDTType()	ifull->GetSDTType()
#define ifull_GetAltTSValues(ONID,TSID)	ifull->GetAltTSValues(ONID,TSID)
#define ifull_GetCurTSValues(ONID,TSID)	ifull->GetCurTSValues(ONID,TSID)
#define ifull_GetStreamPriority()	ifull->GetStreamPriority()
#define ifull_SetStreamPriority(prio)	ifull->SetStreamPriority(prio)
#define ifull_SyncComplete()	ifull->SyncComplete()
#define ifull_ClearCache()	ifull->ClearCache()
#define ifull_GetPLPIds(PLPIds)	ifull->GetPLPIds(PLPIds)
#define ifull_GetHierarchyMode()	ifull->GetHierarchyMode()
#define ifull_ZiggoGetPTCInfo(ptc,Onid,Tsid)	ifull->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define ifull_ZiggoGetSDTType(Frequency)	ifull->ZiggoGetSDTType(Frequency)
#define ifull_GetEpgBarkerMux(ONID,TSID)	ifull->GetEpgBarkerMux(ONID,TSID)
#define ifull_ZiggoNetworkDataSet(ActionValue)	ifull->ZiggoNetworkDataSet(ActionValue)
#define ifull_ClearPersistent()	ifull->ClearPersistent()
#define ifull_GetNumberOfChannelListIds()	ifull->GetNumberOfChannelListIds()
#define ifull_GetChannelListIdByIndex(index)	ifull->GetChannelListIdByIndex(index)
#define ifull_GetNumberOfDigitalChannelsFound()	ifull->GetNumberOfDigitalChannelsFound()
#define ifull_SetFavouriteChannelListId(mode,attrib,index)	ifull->SetFavouriteChannelListId(mode,attrib,index)
#define ifull_GetChannelListIDName(index,ChannelistName)	ifull->GetChannelListIDName(index,ChannelistName)
#define ifullfeN_iPresent() (ifullfeN.Present())
#define ifullfeN_OnSearchStateChanged(state)	ifullfeN->OnSearchStateChanged(state)
#define ifullfeN_OnSearchInProgress(state)	ifullfeN->OnSearchInProgress(state)
#define ifullfeN_OnStationFound()	ifullfeN->OnStationFound()
#define ifullfeN_OnStationNotFound()	ifullfeN->OnStationNotFound()
#define ifullfeN_OnTvSystemDetected(tvSystem)	ifullfeN->OnTvSystemDetected(tvSystem)
#define ifullfeN_OnAfcFreqChanged(freq)	ifullfeN->OnAfcFreqChanged(freq)
#define ifullfeN_OnAfcLimitReached(freq)	ifullfeN->OnAfcLimitReached(freq)
#define ifullfeN_OnAfcModeChanged()	ifullfeN->OnAfcModeChanged()
#define ifullfeN_OnMeasReady(ssm,strength)	ifullfeN->OnMeasReady(ssm,strength)
#define ifullfeN_OnMeasAborted(ssm)	ifullfeN->OnMeasAborted(ssm)
#define ifullfeN_OnConstellationDetected(constellation)	ifullfeN->OnConstellationDetected(constellation)
#define ifullfeN_OnIqModeDetected(mode)	ifullfeN->OnIqModeDetected(mode)
#define ifullfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	ifullfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define ifullfeN_OnHierarchyModeDetected(mode)	ifullfeN->OnHierarchyModeDetected(mode)
#define ifullfeN_OnGuardIntervalDetected(interval)	ifullfeN->OnGuardIntervalDetected(interval)
#define ifullfeN_OnTxModeDetected(mode)	ifullfeN->OnTxModeDetected(mode)
#define ifullfeN_OnChanBandwidthDetected(bandwith)	ifullfeN->OnChanBandwidthDetected(bandwith)
#define ifullfeN_OnCarrierPresentChanged(carrier)	ifullfeN->OnCarrierPresentChanged(carrier)
#define ifullfeN_OnBerThresholdCrossed(ber,berThreshold)	ifullfeN->OnBerThresholdCrossed(ber,berThreshold)
#define ifullpow_iPresent() (ifullpow.Present())
#define ifullpow_Init()	ifullpow->Init()
#define ifullpow_TurnOn()	ifullpow->TurnOn()
#define ifullpow_TurnOff()	ifullpow->TurnOff()
#define iqctrlN_iPresent() (iqctrlN.Present())
#define iqctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iqctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iqctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iqctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iqctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iqctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iqctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iqctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iqctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iqctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iqctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iqctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iqctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iqctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iqctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iqctrlN_OnEvent(dmx,eventid,value)	iqctrlN->OnEvent(dmx,eventid,value)
#define iquick_iPresent() (iquick.Present())
#define iquick_stidle	IHsvDigitalScan_stidle
#define iquick_stfewait	IHsvDigitalScan_stfewait
#define iquick_stdmxwait	IHsvDigitalScan_stdmxwait
#define iquick_stdecision	IHsvDigitalScan_stdecision
#define iquick_Initialise()	iquick->Initialise()
#define iquick_StartInstallation(source,ptc,mode)	iquick->StartInstallation(source,ptc,mode)
#define iquick_StopInstallation()	iquick->StopInstallation()
#define iquick_StartDigitalScan()	iquick->StartDigitalScan()
#define iquick_StartDigitalTuning(frequency)	iquick->StartDigitalTuning(frequency)
#define iquick_StopDigitalScan()	iquick->StopDigitalScan()
#define iquick_GetNoOfPass()	iquick->GetNoOfPass()
#define iquick_GetCurrentPass()	iquick->GetCurrentPass()
#define iquick_GetPTCInfo(ptc)	iquick->GetPTCInfo(ptc)
#define iquick_StoreWeakSignalInstallationChannel()	iquick->StoreWeakSignalInstallationChannel()
#define iquick_GetNumberOfDigitalChannelsFound()	iquick->GetNumberOfDigitalChannelsFound()
#define iquick_GetNumberOfDigitalChannelsRemoved()	iquick->GetNumberOfDigitalChannelsRemoved()
#define iquick_GetTargetNitType(NetworkId)	iquick->GetTargetNitType(NetworkId)
#define iquick_GetCurrentState()	iquick->GetCurrentState()
#define iquick_GetSDTType()	iquick->GetSDTType()
#define iquick_GetAltTSValues(ONID,TSID)	iquick->GetAltTSValues(ONID,TSID)
#define iquick_GetCurTSValues(ONID,TSID)	iquick->GetCurTSValues(ONID,TSID)
#define iquick_GetStreamPriority()	iquick->GetStreamPriority()
#define iquick_SetStreamPriority(prio)	iquick->SetStreamPriority(prio)
#define iquick_SyncComplete()	iquick->SyncComplete()
#define iquick_ClearCache()	iquick->ClearCache()
#define iquick_GetPLPIds(PLPIds)	iquick->GetPLPIds(PLPIds)
#define iquick_GetHierarchyMode()	iquick->GetHierarchyMode()
#define iquick_ZiggoGetPTCInfo(ptc,Onid,Tsid)	iquick->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define iquick_ZiggoGetSDTType(Frequency)	iquick->ZiggoGetSDTType(Frequency)
#define iquick_GetEpgBarkerMux(ONID,TSID)	iquick->GetEpgBarkerMux(ONID,TSID)
#define iquick_ZiggoNetworkDataSet(ActionValue)	iquick->ZiggoNetworkDataSet(ActionValue)
#define iquick_ClearPersistent()	iquick->ClearPersistent()
#define iquick_GetNumberOfChannelListIds()	iquick->GetNumberOfChannelListIds()
#define iquick_GetChannelListIdByIndex(index)	iquick->GetChannelListIdByIndex(index)
#define iquick_GetNumberOfDigitalChannelsFound()	iquick->GetNumberOfDigitalChannelsFound()
#define iquick_SetFavouriteChannelListId(mode,attrib,index)	iquick->SetFavouriteChannelListId(mode,attrib,index)
#define iquick_GetChannelListIDName(index,ChannelistName)	iquick->GetChannelListIDName(index,ChannelistName
#define iquickfeN_iPresent() (iquickfeN.Present())
#define iquickfeN_OnSearchStateChanged(state)	iquickfeN->OnSearchStateChanged(state)
#define iquickfeN_OnSearchInProgress(state)	iquickfeN->OnSearchInProgress(state)
#define iquickfeN_OnStationFound()	iquickfeN->OnStationFound()
#define iquickfeN_OnStationNotFound()	iquickfeN->OnStationNotFound()
#define iquickfeN_OnTvSystemDetected(tvSystem)	iquickfeN->OnTvSystemDetected(tvSystem)
#define iquickfeN_OnAfcFreqChanged(freq)	iquickfeN->OnAfcFreqChanged(freq)
#define iquickfeN_OnAfcLimitReached(freq)	iquickfeN->OnAfcLimitReached(freq)
#define iquickfeN_OnAfcModeChanged()	iquickfeN->OnAfcModeChanged()
#define iquickfeN_OnMeasReady(ssm,strength)	iquickfeN->OnMeasReady(ssm,strength)
#define iquickfeN_OnMeasAborted(ssm)	iquickfeN->OnMeasAborted(ssm)
#define iquickfeN_OnConstellationDetected(constellation)	iquickfeN->OnConstellationDetected(constellation)
#define iquickfeN_OnIqModeDetected(mode)	iquickfeN->OnIqModeDetected(mode)
#define iquickfeN_OnCodeRateDetected(highPrioRate,lowPrioRate)	iquickfeN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define iquickfeN_OnHierarchyModeDetected(mode)	iquickfeN->OnHierarchyModeDetected(mode)
#define iquickfeN_OnGuardIntervalDetected(interval)	iquickfeN->OnGuardIntervalDetected(interval)
#define iquickfeN_OnTxModeDetected(mode)	iquickfeN->OnTxModeDetected(mode)
#define iquickfeN_OnChanBandwidthDetected(bandwith)	iquickfeN->OnChanBandwidthDetected(bandwith)
#define iquickfeN_OnCarrierPresentChanged(carrier)	iquickfeN->OnCarrierPresentChanged(carrier)
#define iquickfeN_OnBerThresholdCrossed(ber,berThreshold)	iquickfeN->OnBerThresholdCrossed(ber,berThreshold)
#define iquickpow_iPresent() (iquickpow.Present())
#define iquickpow_Init()	iquickpow->Init()
#define iquickpow_TurnOn()	iquickpow->TurnOn()
#define iquickpow_TurnOff()	iquickpow->TurnOff()
#define isetpow_iPresent() (isetpow.Present())
#define isetpow_Init()	isetpow->Init()
#define isetpow_TurnOn()	isetpow->TurnOn()
#define isetpow_TurnOff()	isetpow->TurnOff()
#define rins_iPresent() (rins.Present())
#define rins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define rins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define rins_StIdle	IHsvInstallation2_StIdle
#define rins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define rins_StDigital	IHsvInstallation2_StDigital
#define rins_StAnalog	IHsvInstallation2_StAnalog
#define rins_StPreSorting	IHsvInstallation2_StPreSorting
#define rins_StSorting	IHsvInstallation2_StSorting
#define rins_Terrestrial	IHsvInstallation2_Terrestrial
#define rins_Cable	IHsvInstallation2_Cable
#define rins_Satellite	IHsvInstallation2_Satellite
#define rins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define rins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define rins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define rins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define rins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define rins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define rins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define rins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define rins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define rins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define rins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define rins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define rins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define rins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define rins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define rins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define rins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define rins_MaxChannel	IHsvInstallation2_MaxChannel
#define rins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define rins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define rins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define rins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define rins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define rins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define rins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define rins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define rins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define rins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define rins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define rins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define rins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define rins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define rins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define rins_InsAssm	IHsvInstallation2_InsAssm
#define rins_InsVssm	IHsvInstallation2_InsVssm
#define rins_InsQssm	IHsvInstallation2_InsQssm
#define rins_InsSssm	IHsvInstallation2_InsSssm
#define rins_StartInstallation(source,ptc,mode)	rins->StartInstallation(source,ptc,mode)
#define rins_StopInstallation()	rins->StopInstallation()
#define rins_GetNumberOfAnalogChannelsFound()	rins->GetNumberOfAnalogChannelsFound()
#define rins_GetNumberOfDigitalChannelsFound()	rins->GetNumberOfDigitalChannelsFound()
#define rins_GetNumberOfDigitalChannelsRemoved()	rins->GetNumberOfDigitalChannelsRemoved()
#define rins_GetInstallationProgress()	rins->GetInstallationProgress()
#define rins_GetInstallationStatus()	rins->GetInstallationStatus()
#define rins_GetInstallationMode()	rins->GetInstallationMode()
#define rins_IsUpdateInstallationSupported()	rins->IsUpdateInstallationSupported()
#define rins_SetInstallCountry(country)	rins->SetInstallCountry(country)
#define rins_SetSystemCountry(country)	rins->SetSystemCountry(country)
#define rins_GetFirstIntalledDigitalChannel(channelno)	rins->GetFirstIntalledDigitalChannel(channelno)
#define rins_GetFirstIntalledAnalogueChannel(channelno)	rins->GetFirstIntalledAnalogueChannel(channelno)
#define rins_GetFirstIntalledRadioChannel(channelno)	rins->GetFirstIntalledRadioChannel(channelno)
#define rins_GetFirstInstalledChannel(channelno)	rins->GetFirstInstalledChannel(channelno)
#define rins_GetNetworkNameForNetworkID(networkID,NetworkName)	rins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define rins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	rins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define rins_IsValidNetworkId(networkID)	rins->IsValidNetworkId(networkID)
#define rins_SetLowestNetworkId(networkID)	rins->SetLowestNetworkId(networkID)
#define rins_SetManualFrequency(frequency,offset,finetune)	rins->SetManualFrequency(frequency,offset,finetune)
#define rins_GetManualFrequency(frequency,offset,finetune)	rins->GetManualFrequency(frequency,offset,finetune)
#define rins_SetManualChannel(channel,finetune)	rins->SetManualChannel(channel,finetune)
#define rins_GetManualChannel(channel,finetune)	rins->GetManualChannel(channel,finetune)
#define rins_IsManualInstallationModeSupported(mode)	rins->IsManualInstallationModeSupported(mode)
#define rins_SetManualInstallationMode(mode)	rins->SetManualInstallationMode(mode)
#define rins_GetManualInstallationMode()	rins->GetManualInstallationMode()
#define rins_StoreManualInstallationValues(channel)	rins->StoreManualInstallationValues(channel)
#define rins_AutoStoreManualInstallationValues()	rins->AutoStoreManualInstallationValues()
#define rins_StartFrequencySearch()	rins->StartFrequencySearch()
#define rins_GetSigStrengthRange(measmode,min,max)	rins->GetSigStrengthRange(measmode,min,max)
#define rins_GetSignalstrength(measmode)	rins->GetSignalstrength(measmode)
#define rins_StoreWeakSignalInstallationChannel()	rins->StoreWeakSignalInstallationChannel()
#define rins_GetInstalledWeakSignalChannel()	rins->GetInstalledWeakSignalChannel()
#define rins_GetSignalQualityBer()	rins->GetSignalQualityBer()
#define rins_IsFrequencySearchDirectionSupported(searchup)	rins->IsFrequencySearchDirectionSupported(searchup)
#define rins_SetFrequencySearchDirection(searchup)	rins->SetFrequencySearchDirection(searchup)
#define rins_GetFrequencySearchDirection()	rins->GetFrequencySearchDirection()
#define rins_GetMinFrequency()	rins->GetMinFrequency()
#define rins_GetMaxFrequency()	rins->GetMaxFrequency()
#define rins_GetTunerFrequency()	rins->GetTunerFrequency()
#define rins_SetTunerFrequency(freq,fineTune)	rins->SetTunerFrequency(freq,fineTune)
#define rins_GetFrequency2Channel(chantbl,frequency)	rins->GetFrequency2Channel(chantbl,frequency)
#define rins_GetChannel2CarrierFrequency(chantbl,channel)	rins->GetChannel2CarrierFrequency(chantbl,channel)
#define rins_GetChannel2CentreFrequency(chantbl,channel)	rins->GetChannel2CentreFrequency(chantbl,channel)
#define rins_GetCurrentPass()	rins->GetCurrentPass()
#define rins_GetNoOfPass()	rins->GetNoOfPass()
#define rins_GetCurrentPassType()	rins->GetCurrentPassType()
#define rins_IsMediumSupported(medium)	rins->IsMediumSupported(medium)
#define rins_GetMedium()	rins->GetMedium()
#define rins_SetMedium(medium)	rins->SetMedium(medium)
#define rins_GetInstalledMedium()	rins->GetInstalledMedium()
#define rins_SetInstalledMedium(medium)	rins->SetInstalledMedium(medium)
#define rins_IsTvSystemSupported(tvsystem)	rins->IsTvSystemSupported(tvsystem)
#define rins_SetTvSystem(tvsystem)	rins->SetTvSystem(tvsystem)
#define rins_GetTvSystem()	rins->GetTvSystem()
#define rins_IsColorSystemSupported(colorsystem)	rins->IsColorSystemSupported(colorsystem)
#define rins_SetColorSystem(colorsystem)	rins->SetColorSystem(colorsystem)
#define rins_GetColorSystem()	rins->GetColorSystem()
#define rins_IsValidPTC(medium,PTC)	rins->IsValidPTC(medium,PTC)
#define rins_GetMinPTC(medium)	rins->GetMinPTC(medium)
#define rins_GetMaxPTC(medium)	rins->GetMaxPTC(medium)
#define rins_GetLastPTCFound()	rins->GetLastPTCFound()
#define rins_GetNumberOfPTCsFound()	rins->GetNumberOfPTCsFound()
#define rins_StartSigStrMeas(measmode)	rins->StartSigStrMeas(measmode)
#define rins_StopSigStrMeas(measmode)	rins->StopSigStrMeas(measmode)
#define rins_IsSignalStrengthMeasurementValid(measmode)	rins->IsSignalStrengthMeasurementValid(measmode)
#define rins_ScanNone	IHsvInstallation2_ScanNone
#define rins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define rins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define rins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define rins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define rins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define rins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define rins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define rins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define rins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define rins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define rins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define rins_AttributeCity	IHsvInstallation2_AttributeCity
#define rins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define rins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define rins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define rins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define rins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define rins_AttributeDualAnalogPass  IHsvInstallation2_AttributeDualAnalogPass
#define rins_AttributeDTTScanOnAnalog  IHsvInstallation2_AttributeDTTScanOnAnalog
#define rins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define rins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define rins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define rins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define rins_AttributeFavoriteChannelId	IHsvInstallation2_AttributeFavoriteChannelId
#define rins_QuickScan	IHsvInstallation2_QuickScan
#define rins_FullScan	IHsvInstallation2_FullScan
#define rins_GridScan	IHsvInstallation2_GridScan
#define rins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define rins_ManualValue	IHsvInstallation2_ManualValue
#define rins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	rins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define rins_SetAttributeMode(installationmode,attribute,attributeMode)	rins->SetAttributeMode(installationmode,attribute,attributeMode)
#define rins_SetAttribute(installationmode,attribute,value)	rins->SetAttribute(installationmode,attribute,value)
#define rins_GetAttributeMode(installationmode,attribute)	rins->GetAttributeMode(installationmode,attribute)
#define rins_GetAttribute(installationmode,attribute)	rins->GetAttribute(installationmode,attribute)
#define rins_IsAvailable(installationmode,attribute)	rins->IsAvailable(installationmode,attribute)
#define rins_ResetAttributeToDefault(installationmode,attribute)	rins->ResetAttributeToDefault(installationmode,attribute)
#define rins_ResetAttributeToPersistent(installationmode,attribute)	rins->ResetAttributeToPersistent(installationmode,attribute)
#define rins_NitNone	IHsvInstallation2_NitNone
#define rins_NitActual	IHsvInstallation2_NitActual
#define rins_NitOther	IHsvInstallation2_NitOther
#define rins_GetTargetNitType(NetworkId)	rins->GetTargetNitType(NetworkId)
#define rins_IsNetworkUpdateDetected()	rins->IsNetworkUpdateDetected()
#define rins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define rins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define rins_Initialise()	rins->Initialise()
#define rins_SkipInstallationScans(ScanTypes)	rins->SkipInstallationScans(ScanTypes)
#define rins_GetAltTSValues(ONID,TSID)	rins->GetAltTSValues(ONID,TSID)
#define rins_SetUserSymbolRates(installationmode,values,len)	rins->SetUserSymbolRates(installationmode,values,len)
#define rins_GetUserSymbolRates(installationmode,values,len)	rins->GetUserSymbolRates(installationmode,values,len)
#define rins_GetPredefinedSymbolRates(installationmode,values,len)	rins->GetPredefinedSymbolRates(installationmode,values,len)
#define rins_GetNetworkIDList()	rins->GetNetworkIDList()
#define rins_GetNetworkIDName(index,NetworkName)	rins->GetNetworkIDName(index,NetworkName)
#define rins_GetChannelListIDName(index,ChannelistName)	rins->GetChannelListIDName(index,ChannelistName)
#define rins_SetFavouriteNetworkID(mode,attrib,index)	rins->SetFavouriteNetworkID(mode,attrib,index)
#define rins_GetNumberOfChannelListIds()	rins->GetNumberOfChannelListIds(index)
#define rins_GetChannelListIdByIndex(index)	rins->GetChannelListIdByIndex()
#define rins_SetFavouriteChannelListId(mode,attrib,index)	rins->SetFavouriteChannelListId(mode,attrib,index)
#define rins_SetFavouriteRegion(mode,index,RegionType)	rins->SetFavouriteRegion(mode,index,RegionType)
#define rins_None	IHsvInstallation2_None
#define rins_Ziggo	IHsvInstallation2_Ziggo
#define rins_UPC	IHsvInstallation2_UPC
#define rins_UnityMedia	IHsvInstallation2_UnityMedia
#define rins_Kdg	IHsvInstallation2_Kdg
#define rins_Telenet	IHsvInstallation2_Telenet
#define rins_RCSRDS	IHsvInstallation2_RCSRDS
#define rins_SetUserSelectConflictService(LcnIndex,SvcIndex)	rins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define rins_ConflictsSelectionDone(UserSelection)	rins->ConflictsSelectionDone(UserSelection)
#define rins_GetConflictServices(ConflictList,NumRecords)	rins->GetConflictServices(ConflictList,NumRecords)
#define rins_GetInstallationVersion()	rins->GetInstallationVersion()
#define rins_GetInstallationState()	rins->GetInstallationState()
#define rins_GetPLPIds(PLPIds)	rins->GetPLPIds(PLPIds)
#define rins_GetRegionList(RegionsData)	rins->GetRegionList(RegionsData)
#define rins_UserSelectionDone(UserSelection)	rins->UserSelectionDone(UserSelection)
#define rins_GetFavouriteRegion(mode,RegionType)	rins->GetFavouriteRegion(mode,RegionType)
#define rins_GetStreamPriority()	rins->GetStreamPriority()
#define rins_SetStreamPriority(prio)	rins->SetStreamPriority(prio)
#define rins_GetConstellation()	rins->GetConstellation()
#define rins_GetSymbolRate()	rins->GetSymbolRate()
#define rins_GetHierarchyMode()	rins->GetHierarchyMode()
#define rins_GetEpgBarkerMux(OnId,TsId)	rins->GetEpgBarkerMux(OnId,TsId)
#define rins_ZiggoNetworkDataSet(ActionValue)	rins->ZiggoNetworkDataSet(ActionValue)
#define rins_ClearPersistent()	rins->ClearPersistent()
#define ctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define idvbt_stidle	IHsvDigitalScan_stidle
#define idvbt_stfewait	IHsvDigitalScan_stfewait
#define idvbt_stdmxwait	IHsvDigitalScan_stdmxwait
#define idvbt_stdecision	IHsvDigitalScan_stdecision
#define iroute_quickscan	IHsvDigitalScanRoute_quickscan
#define iroute_fullscan	IHsvDigitalScanRoute_fullscan
#define iroute_userentryscan	IHsvDigitalScanRoute_userentryscan
#define iroute_stubscan	IHsvDigitalScanRoute_stubscan
#define istub_stidle	IHsvDigitalScan_stidle
#define istub_stfewait	IHsvDigitalScan_stfewait
#define istub_stdmxwait	IHsvDigitalScan_stdmxwait
#define istub_stdecision	IHsvDigitalScan_stdecision
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mRoute.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

