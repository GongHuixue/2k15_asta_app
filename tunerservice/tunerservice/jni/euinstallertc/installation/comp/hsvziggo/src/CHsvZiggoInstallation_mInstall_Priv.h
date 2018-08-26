#ifndef  _CHSVZIGGOINSTALLATION_MINSTALL_PRIV_H
#define  _CHSVZIGGOINSTALLATION_MINSTALL_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalScan.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvSdmControl2.h>
#include <IHsvDVBSettings.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
#include <CTCMwBase.h>
class CHsvZiggoInstallation_mInstall_Priv;
#define CLASSSCOPE CHsvZiggoInstallation_mInstall_Priv::
#include "locals_mInstall.h"

class CHsvZiggoInstallation_mInstall_Priv : public CTCMwBase
{
public:
virtual ~CHsvZiggoInstallation_mInstall_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mInstall.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDigitalScanImpl(CHsvZiggoInstallation_mInstall_Priv,iins);
IHsvSdmControlNotifyExImpl(CHsvZiggoInstallation_mInstall_Priv,iinsctrlN);
IHsvFrontEndApiNotifyImpl(CHsvZiggoInstallation_mInstall_Priv,iinsfeapiN);
IHsvPowerImpl(CHsvZiggoInstallation_mInstall_Priv,iinspow);
public:
ProvidesInterface<IHsvDigitalScan>	iins;

ProvidesInterface<IHsvSdmControlNotifyEx>	iinsctrlN;

ProvidesInterface<IHsvFrontEndApiNotify>	iinsfeapiN;

ProvidesInterface<IHsvPower>	iinspow;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvDVBSettings>	dvbset;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalScan>	ibckg;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvZiggoInstallation_mInstall_Priv);

public:
CHsvZiggoInstallation_mInstall_Priv():i__iins(this),i__iinsctrlN(this),i__iinsfeapiN(this),i__iinspow(this)
{
iins	=	&i__iins;
iinsctrlN	=	&i__iinsctrlN;
iinsfeapiN	=	&i__iinsfeapiN;
iinspow	=	&i__iinspow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define ctrl_iPresent() (ctrl.Present())
#define ctrl_Idle	IHsvSdmControl2_Idle
#define ctrl_Minimal	IHsvSdmControl2_Minimal
#define ctrl_Normal	IHsvSdmControl2_Normal
#define ctrl_External	IHsvSdmControl2_External
#define ctrl_CrossCarraige	IHsvSdmControl2_CrossCarraige
#define ctrl_Invalid	IHsvSdmControl2_Invalid
#define ctrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ctrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ctrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ctrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ctrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
#define ctrl_GetMode(dmx)	ctrl->GetMode(dmx)
#define ctrl_GetStatus(dmx)	ctrl->GetStatus(dmx)
#define ctrl_StartCollection(dmx,mode)	ctrl->StartCollection(dmx,mode)
#define ctrl_StopCollection(dmx)	ctrl->StopCollection(dmx)
#define dvbset_iPresent() (dvbset.Present())
#define dvbset_SetAttribute(installationmode,attribute,value)	dvbset->SetAttribute(installationmode,attribute,value)
#define dvbset_GetAttribute(installationmode,attribute)	dvbset->GetAttribute(installationmode,attribute)
#define dvbset_ResetAttributeToDefault(installationmode,attribute)	dvbset->ResetAttributeToDefault(installationmode,attribute)
#define dvbset_ResetAttributeToPersistent(installationmode,attribute)	dvbset->ResetAttributeToPersistent(installationmode,attribute)
#define dvbset_ResetAllToDefault()	dvbset->ResetAllToDefault()
#define dvbset_ResetAllToPersistent()	dvbset->ResetAllToPersistent()
#define dvbset_GetAttributeLength(installationmode,attribute)	dvbset->GetAttributeLength(installationmode,attribute)
#define dvbset_GetNextAttributeValue(installationmode,attribute,value)	dvbset->GetNextAttributeValue(installationmode,attribute,value)
#define dvbset_SetPreferred(attribute,value,preferred)	dvbset->SetPreferred(attribute,value,preferred)
#define dvbset_GetAttributeRange(installationmode,attribute,minValue,maxValue)	dvbset->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define dvbset_GetAttributeMode(installationmode,attribute)	dvbset->GetAttributeMode(installationmode,attribute)
#define dvbset_SetAttributeMode(installationmode,attribute,attributeMode)	dvbset->SetAttributeMode(installationmode,attribute,attributeMode)
#define dvbset_CopyTemporaryToPersistent()	dvbset->CopyTemporaryToPersistent()
#define dvbset_ClearPersistent()	dvbset->ClearPersistent()
#define dvbset_CommitPreferred()	dvbset->CommitPreferred()
#define dvbset_IsAvailable(installationmode,attribute)	dvbset->IsAvailable(installationmode,attribute)
#define dvbset_SetUserSymbolRates(installationmode,values,len)	dvbset->SetUserSymbolRates(installationmode,values,len)
#define dvbset_GetUserSymbolRates(installationmode,values,len)	dvbset->GetUserSymbolRates(installationmode,values,len)
#define dvbset_GetPredefinedSymbolRates(installationmode,values,len)	dvbset->GetPredefinedSymbolRates(installationmode,values,len)
#define dvbset_ClearUserSymbolRates()	dvbset->ClearUserSymbolRates()
#define dvbset_GetONIDNetworkOperator(ONID)	dvbset->GetONIDNetworkOperator(ONID)
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
#define feapi_iPresent() (feapi.Present())
#define feapi_GetFreqRange(winid,MinFreq,MaxFreq,retval)	feapi->GetFreqRange(winid,MinFreq,MaxFreq,retval)
#define feapi_GetFreq(winid,Freq,retval)	feapi->GetFreq(winid,Freq,retval)
#define feapi_SetFreq(winid,freq,finetune,retval)	feapi->SetFreq(winid,freq,finetune,retval)
#define feapi_GetTvSystemSupp(winid,tvSystem,Supp,retval)	feapi->GetTvSystemSupp(winid,tvSystem,Supp,retval)
#define feapi_GetTvSystem(winid,TvSystem,retval)	feapi->GetTvSystem(winid,TvSystem,retval)
#define feapi_SetTvSystem(winid,TvSystem,retval)	feapi->SetTvSystem(winid,TvSystem,retval)
#define feapi_StartSearch(winid,startFreq,mode,endFreq,retval)	feapi->StartSearch(winid,startFreq,mode,endFreq,retval)
#define feapi_StopSearch(winid,retval)	feapi->StopSearch(winid,retval)
#define feapi_Freq2Chan(winid,freq,table,Chan,retval)	feapi->Freq2Chan(winid,freq,table,Chan,retval)
#define feapi_GetCarrierFreq(winid,chan,table,Freq,retval)	feapi->GetCarrierFreq(winid,chan,table,Freq,retval)
#define feapi_SigAssm	IHsvFrontEndApi_SigAssm
#define feapi_SigVssm	IHsvFrontEndApi_SigVssm
#define feapi_SigQssm	IHsvFrontEndApi_SigQssm
#define feapi_SigSssm	IHsvFrontEndApi_SigSssm
#define feapi_GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval)	feapi->GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval)
#define feapi_Start(winid,ssm,Avail,retval)	feapi->Start(winid,ssm,Avail,retval)
#define feapi_Stop(winid,ssm,Stopped,retval)	feapi->Stop(winid,ssm,Stopped,retval)
#define feapi_GetMeasValid(winid,ssm,Valid,retval)	feapi->GetMeasValid(winid,ssm,Valid,retval)
#define feapi_GetSigStrength(winid,ssm,Strength,retval)	feapi->GetSigStrength(winid,ssm,Strength,retval)
#define feapi_GetActualConstellation(winid,decoder,pConstellation,retval)	feapi->GetActualConstellation(winid,decoder,pConstellation,retval)
#define feapi_SetConstellation(winid,decoder,constellation,retval)	feapi->SetConstellation(winid,decoder,constellation,retval)
#define feapi_GetBer(winid,decoder,Ber,retval)	feapi->GetBer(winid,decoder,Ber,retval)
#define feapi_GetCarrierPresent(winid,Present,retval)	feapi->GetCarrierPresent(winid,Present,retval)
#define feapi_SetChanBandwidth(winid,bandwidth,retval)	feapi->SetChanBandwidth(winid,bandwidth,retval)
#define feapi_GetActualChanBandwidth(winid,Bandwidth,retval)	feapi->GetActualChanBandwidth(winid,Bandwidth,retval)
#define feapi_SetStreamPriority(winid,streamPriority,retval)	feapi->SetStreamPriority(winid,streamPriority,retval)
#define feapi_GetStreamPriority(winid,streamPriority,retval)	feapi->GetStreamPriority(winid,streamPriority,retval)
#define feapi_GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)	feapi->GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)
#define feapi_SetSymbolRate(winid,rate,retval)	feapi->SetSymbolRate(winid,rate,retval)
#define feapi_GetSymbolRate(winid,rate,retval)	feapi->GetSymbolRate(winid,rate,retval)
#define feapi_SetSearchRates(winid,SearchRate,size,retval)	feapi->SetSearchRates(winid,SearchRate,size,retval)
#define feapi_GetActualCodeRate(winid,rate,retval)	feapi->GetActualCodeRate(winid,rate,retval)
#define feapi_SetFreqStep(winid,step,retval)	feapi->SetFreqStep(winid,step,retval)
#define feapi_GetFreqStep(winid,step,retval)	feapi->GetFreqStep(winid,step,retval)
#define feapi_GetTPSId(winid,TPSId,retval)	feapi->GetTPSId(winid,TPSId,retval)
#define feapi_ChanDecDvbT	IHsvFrontEndApi_ChanDecDvbT
#define feapi_ChanDecDvbC	IHsvFrontEndApi_ChanDecDvbC
#define feapi_ChanDecDvbS	IHsvFrontEndApi_ChanDecDvbS
#define feapi_ChanDecISDBT	IHsvFrontEndApi_ChanDecISDBT
#define feapi_ChanDecDvbT2	IHsvFrontEndApi_ChanDecDvbT2
#define hsverr_iPresent() (hsverr.Present())
#define hsverr_Ok	IHsvErrorCodeEx_Ok
#define hsverr_BadParameter	IHsvErrorCodeEx_BadParameter
#define hsverr_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define hsverr_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define hsverr_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define hsverr_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define hsverr_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define hsverr_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define hsverr_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define hsverr_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define hsverr_FileError	IHsvErrorCodeEx_FileError
#define hsverr_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define hsverr_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define hsverr_NotSupported	IHsvErrorCodeEx_NotSupported
#define hsverr_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define hsverr_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define hsverr_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define hsverr_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define hsverr_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define hsverr_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define hsverr_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define hsverr_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define hsverr_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define hsverr_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define hsverr_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define hsverr_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define hsverr_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define hsverr_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define hsverr_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define hsverr_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define hsverr_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define hsverr_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define hsverr_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define hsverr_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define ibckg_iPresent() (ibckg.Present())
#define ibckg_stidle	IHsvDigitalScan_stidle
#define ibckg_stfewait	IHsvDigitalScan_stfewait
#define ibckg_stdmxwait	IHsvDigitalScan_stdmxwait
#define ibckg_stdecision	IHsvDigitalScan_stdecision
#define ibckg_Initialise()	ibckg->Initialise()
#define ibckg_StartInstallation(source,ptc,mode)	ibckg->StartInstallation(source,ptc,mode)
#define ibckg_StopInstallation()	ibckg->StopInstallation()
#define ibckg_StartDigitalScan()	ibckg->StartDigitalScan()
#define ibckg_StartDigitalTuning(frequency)	ibckg->StartDigitalTuning(frequency)
#define ibckg_StopDigitalScan()	ibckg->StopDigitalScan()
#define ibckg_GetNoOfPass()	ibckg->GetNoOfPass()
#define ibckg_GetCurrentPass()	ibckg->GetCurrentPass()
#define ibckg_GetPTCInfo(ptc)	ibckg->GetPTCInfo(ptc)
#define ibckg_StoreWeakSignalInstallationChannel()	ibckg->StoreWeakSignalInstallationChannel()
#define ibckg_GetNumberOfDigitalChannelsFound()	ibckg->GetNumberOfDigitalChannelsFound()
#define ibckg_GetNumberOfDigitalChannelsRemoved()	ibckg->GetNumberOfDigitalChannelsRemoved()
#define ibckg_GetTargetNitType(NetworkId)	ibckg->GetTargetNitType(NetworkId)
#define ibckg_GetCurrentState()	ibckg->GetCurrentState()
#define ibckg_GetSDTType()	ibckg->GetSDTType()
#define ibckg_GetAltTSValues(ONID,TSID)	ibckg->GetAltTSValues(ONID,TSID)
#define ibckg_GetCurTSValues(ONID,TSID)	ibckg->GetCurTSValues(ONID,TSID)
#define ibckg_GetStreamPriority()	ibckg->GetStreamPriority()
#define ibckg_SetStreamPriority(prio)	ibckg->SetStreamPriority(prio)
#define ibckg_SyncComplete()	ibckg->SyncComplete()
#define ibckg_ClearCache()	ibckg->ClearCache()
#define ibckg_GetPLPIds(PLPIds)	ibckg->GetPLPIds(PLPIds)
#define ibckg_GetHierarchyMode()	ibckg->GetHierarchyMode()
#define ibckg_ZiggoGetPTCInfo(ptc,Onid,Tsid)	ibckg->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define ibckg_ZiggoGetSDTType(Frequency)	ibckg->ZiggoGetSDTType(Frequency)
#define ibckg_GetEpgBarkerMux(ONID,TSID)	ibckg->GetEpgBarkerMux(ONID,TSID)
#define ibckg_ZiggoNetworkDataSet(ActionValue)	ibckg->ZiggoNetworkDataSet(ActionValue)
#define ibckg_ClearPersistent()	ibckg->ClearPersistent()
#define idataacq_iPresent() (idataacq.Present())
#define idataacq_Initialise()	idataacq->Initialise()
#define idataacq_InitialiseTotalChannels()	idataacq->InitialiseTotalChannels()
#define idataacq_AcquireData()	idataacq->AcquireData()
#define idataacq_GetNumberOfDigitalChannelsFound()	idataacq->GetNumberOfDigitalChannelsFound()
#define idataacq_GetNumberOfDigitalChannelsRemoved()	idataacq->GetNumberOfDigitalChannelsRemoved()
#define idataacq_GetNumberOfChannels(servicetype)	idataacq->GetNumberOfChannels(servicetype)
#define idataacq_GetNextSampleProgram()	idataacq->GetNextSampleProgram()
#define idataacq_AcquireLCNData()	idataacq->AcquireLCNData()
#define idataacq_AcquireServiceListData()	idataacq->AcquireServiceListData()
#define idataacq_StartBackgroundInstall()	idataacq->StartBackgroundInstall()
#define idataacq_ResetBackgroundInstall()	idataacq->ResetBackgroundInstall()
#define idataacq_IsNetworkUpdateDetected()	idataacq->IsNetworkUpdateDetected()
#define idataacq_DeleteServices()	idataacq->DeleteServices()
#define idataacq_GetNetworkIDList()	idataacq->GetNetworkIDList()
#define idataacq_GetNetworkIDName(index,NetworkName)	idataacq->GetNetworkIDName(index,NetworkName)
#define idataacq_SetFavouriteNetworkID(mode,attrib,index)	idataacq->SetFavouriteNetworkID(mode,attrib,index)
#define idataacq_ClearNetworkNameCache()	idataacq->ClearNetworkNameCache()
#define idataacq_IsLCNValid()	idataacq->IsLCNValid()
#define idataacq_AcquireONID()	idataacq->AcquireONID()
#define idataacq_SyncTemporaryTableRecords()	idataacq->SyncTemporaryTableRecords()
#define idataacq_ClearCache()	idataacq->ClearCache()
#define idataacq_GetRegionList(RegionsData)	idataacq->GetRegionList(RegionsData)
#define idataacq_SetFavouriteRegion(mode,index,RegionType)	idataacq->SetFavouriteRegion(mode,index,RegionType)
#define idataacq_GetFavouriteRegion(mode,RegionType)	idataacq->GetFavouriteRegion(mode,RegionType)
#define idataacq_Enable()	idataacq->Enable()
#define idataacq_Disable()	idataacq->Disable()
#define idataacq_GetCachedRegionDetails(RegionCache)	idataacq->GetCachedRegionDetails(RegionCache)
#define idataacq_UpdateBarkerMuxInfo(IsBarkerMux)	idataacq->UpdateBarkerMuxInfo(IsBarkerMux)
#define insN_iPresent() (insN.Present())
#define insN_EventInstallationCompleted	IHsvInstallationNotify_EventInstallationCompleted
#define insN_EventInstallationStarted	IHsvInstallationNotify_EventInstallationStarted
#define insN_EventInstallationStopped	IHsvInstallationNotify_EventInstallationStopped
#define insN_EventInstallationPaused	IHsvInstallationNotify_EventInstallationPaused
#define insN_EventInstallationContinued	IHsvInstallationNotify_EventInstallationContinued
#define insN_EventChannelFound	IHsvInstallationNotify_EventChannelFound
#define insN_EventChannelNotFound	IHsvInstallationNotify_EventChannelNotFound
#define insN_EventSearchInProgress	IHsvInstallationNotify_EventSearchInProgress
#define insN_EventTuningStarted	IHsvInstallationNotify_EventTuningStarted
#define insN_EventTuningStationFound	IHsvInstallationNotify_EventTuningStationFound
#define insN_EventTuningStationNotFound	IHsvInstallationNotify_EventTuningStationNotFound
#define insN_EventManualInstallationCniExtractionStarted	IHsvInstallationNotify_EventManualInstallationCniExtractionStarted
#define insN_EventManualInstallationCniExtractionEnded	IHsvInstallationNotify_EventManualInstallationCniExtractionEnded
#define insN_EventATSSortingStarted	IHsvInstallationNotify_EventATSSortingStarted
#define insN_EventAciStoreStarted	IHsvInstallationNotify_EventAciStoreStarted
#define insN_EventTvSystemChanged	IHsvInstallationNotify_EventTvSystemChanged
#define insN_EventMediumChanged	IHsvInstallationNotify_EventMediumChanged
#define insN_EventSignalStrengthChanged	IHsvInstallationNotify_EventSignalStrengthChanged
#define insN_EventBackGroundCNIUpdated	IHsvInstallationNotify_EventBackGroundCNIUpdated
#define insN_EventPresetStored	IHsvInstallationNotify_EventPresetStored
#define insN_EventPhaseStarted	IHsvInstallationNotify_EventPhaseStarted
#define insN_EventPhaseCompleted	IHsvInstallationNotify_EventPhaseCompleted
#define insN_EventChannelIterationStarted	IHsvInstallationNotify_EventChannelIterationStarted
#define insN_EventHeirarchyModeDetected	IHsvInstallationNotify_EventHeirarchyModeDetected
#define insN_EventChannelAdded	IHsvInstallationNotify_EventChannelAdded
#define insN_EventChannelRemoved	IHsvInstallationNotify_EventChannelRemoved
#define insN_EventNetworkUpdateDetected	IHsvInstallationNotify_EventNetworkUpdateDetected
#define insN_EventDisplayNetworkNames	IHsvInstallationNotify_EventDisplayNetworkNames
#define insN_EventNIDInvalid	IHsvInstallationNotify_EventNIDInvalid
#define insN_EventNetworkUpdateNotDetected	IHsvInstallationNotify_EventNetworkUpdateNotDetected
#define insN_EventOnConflictsDetected	IHsvInstallationNotify_EventOnConflictsDetected
#define insN_EventDisplayRegionNames	IHsvInstallationNotify_EventDisplayRegionNames
#define insN_EventPLPsDetected	IHsvInstallationNotify_EventPLPsDetected
#define insN_NetworkOperator	IHsvInstallationNotify_NetworkOperator
#define insN_EventPresetAdded	IHsvInstallationNotify_EventPresetAdded
#define insN_EventPresetDeleted IHsvInstallationNotify_EventPresetDeleted	
#define insN_EventUpdated	 IHsvInstallationNotify_EventUpdated
#define insN_EventMultiPackageFound 	IHsvInstallationNotify_EventMultiPackageFound
#define	insN_EventMultiPackageToBeDisplayed 	IHsvInstallationNotify_EventMultiPackageToBeDisplayed
#define	insN_EventMultiPackageRemoved	 IHsvInstallationNotify_EventMultiPackageRemoved
#define insN_EventNewPresetNumber IHsvInstallationNotify_EventNewPresetNumber
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define mctl_iPresent() (mctl.Present())
#define mctl_InvalidMedia	IHsvMediaControl_InvalidMedia
#define mctl_Video	IHsvMediaControl_Video
#define mctl_Audio	IHsvMediaControl_Audio
#define mctl_Pcr	IHsvMediaControl_Pcr
#define mctl_Subtitle	IHsvMediaControl_Subtitle
#define mctl_ClosedCaption	IHsvMediaControl_ClosedCaption
#define mctl_Teletext	IHsvMediaControl_Teletext
#define mctl_IPSubtitle	IHsvMediaControl_IPSubtitle
#define mctl_IPClosedCaption	IHsvMediaControl_IPClosedCaption
#define mctl_InvalidSelector	IHsvMediaControl_InvalidSelector
#define mctl_Language	IHsvMediaControl_Language
#define mctl_Type	IHsvMediaControl_Type
#define mctl_Pid	IHsvMediaControl_Pid
#define mctl_VIAssociation	IHsvMediaControl_VIAssociation
#define mctl_VIPrimaryAssociation	IHsvMediaControl_VIPrimaryAssociation
#define mctl_StreamType	IHsvMediaControl_StreamType
#define mctl_GetMediaSize(dest,media)	mctl->GetMediaSize(dest,media)
#define mctl_GetMediaByKey(dest,media,selector1,selector2,value)	mctl->GetMediaByKey(dest,media,selector1,selector2,value)
#define mctl_GetMediaIndex(dest,media,selector1,selecto2,index)	mctl->GetMediaIndex(dest,media,selector1,selecto2,index)
#define mctl_GetMediaByIndex(dest,media,index,value)	mctl->GetMediaByIndex(dest,media,index,value)
#define mctl_SetMedia(dest,media,selector,value)	mctl->SetMedia(dest,media,selector,value)
#define mctl_SetMediaWithProgram(dest,program,media,selector,value)	mctl->SetMediaWithProgram(dest,program,media,selector,value)
#define mctl_Play(dest)	mctl->Play(dest)
#define mctl_PlayMedia(dest,media)	mctl->PlayMedia(dest,media)
#define mctl_Stop(dest)	mctl->Stop(dest)
#define mctl_StopMedia(dest,media)	mctl->StopMedia(dest,media)
#define mctl_Flush(dest)	mctl->Flush(dest)
#define mctl_EnableMedia(dest,media)	mctl->EnableMedia(dest,media)
#define mctl_DisableMedia(dest,media)	mctl->DisableMedia(dest,media)
#define mctl_GetCurrentSelection(dest,media,selector)	mctl->GetCurrentSelection(dest,media,selector)
#define mctl_IsMediaPlaying(dest,media)	mctl->IsMediaPlaying(dest,media)
#define mctl_IsMediaEnabled(dest,media)	mctl->IsMediaEnabled(dest,media)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define plferrids_iPresent() (plferrids.Present())
#define plferrids_Ok	IPlfApiErrorIds_Ok
#define plferrids_ResourceNotOwned	IPlfApiErrorIds_ResourceNotOwned
#define plferrids_InterfaceNotAvailable	IPlfApiErrorIds_InterfaceNotAvailable
#define plferrids_InterfaceNotImplemented	IPlfApiErrorIds_InterfaceNotImplemented
#define plferrids_Other	IPlfApiErrorIds_Other
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvZiggoInstallation_mInstall_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
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
#define rins_SetFavouriteNetworkID(mode,attrib,index)	rins->SetFavouriteNetworkID(mode,attrib,index)
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
#define sigstr_iPresent() (sigstr.Present())
#define sigstr_Initialise()	sigstr->Initialise()
#define sigstr_GetSigStrengthRange(mode,min,max)	sigstr->GetSigStrengthRange(mode,min,max)
#define sigstr_GetSignalStrength(mode)	sigstr->GetSignalStrength(mode)
#define sigstr_GetMinSignalStrength(mode)	sigstr->GetMinSignalStrength(mode)
#define sigstr_GetMaxSignalStrength(mode)	sigstr->GetMaxSignalStrength(mode)
#define sigstr_GetActualSignalStrength(mode,cookie)	sigstr->GetActualSignalStrength(mode,cookie)
#define sigstr_StartSigStrMeasAll()	sigstr->StartSigStrMeasAll()
#define sigstr_StopSigStrMeasAll()	sigstr->StopSigStrMeasAll()
#define sigstr_UpdateSigStrRange()	sigstr->UpdateSigStrRange()
#define sigstr_GetSigStrengthMeasured()	sigstr->GetSigStrengthMeasured()
#define sigstr_SetSigStrengthMeasured(flag)	sigstr->SetSigStrengthMeasured(flag)
#define sigstr_StartSigStrMeas(measmode)	sigstr->StartSigStrMeas(measmode)
#define sigstr_StopSigStrMeas(measmode)	sigstr->StopSigStrMeas(measmode)
#define sigstr_IsSignalStrengthMeasurementValid(measmode)	sigstr->IsSignalStrengthMeasurementValid(measmode)
#define strapi_iPresent() (strapi.Present())
#define strapi_GetSize(dest,spid)	strapi->GetSize(dest,spid)
#define strapi_GetIndex(dest,spid,key1,key2,key3,index)	strapi->GetIndex(dest,spid,key1,key2,key3,index)
#define strapi_GetByKey(dest,spid,key1,key2,key3,val)	strapi->GetByKey(dest,spid,key1,key2,key3,val)
#define strapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	strapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define strapi_GetByIndex(dest,spid,index,val)	strapi->GetByIndex(dest,spid,index,val)
#define wnddest_iPresent() (wnddest.Present())
#define wnddest_InvalidWindowId	wnddest->InvalidWindowId()
#define wnddest_GetWindowId(dest)	wnddest->GetWindowId(dest)
#define wnddest_GetAudioNodeId(dest)	wnddest->GetAudioNodeId(dest)
#define wnddest_GetMonitorWindow()	wnddest->GetMonitorWindow()
#define wnddest_WndTypeInvalid	IHsvWindowDestinationMap_WndTypeInvalid
#define wnddest_WndTypeMainVideo	IHsvWindowDestinationMap_WndTypeMainVideo
#define wnddest_WndTypeMainAudio	IHsvWindowDestinationMap_WndTypeMainAudio
#define wnddest_WndTypeMonitor	IHsvWindowDestinationMap_WndTypeMonitor
#define wnddest_WndTypeAuxVideo	IHsvWindowDestinationMap_WndTypeAuxVideo
#define wnddest_GetWindowType(winid)	wnddest->GetWindowType(winid)
#define wnddest_GetDestinationForWindow(windowid)	wnddest->GetDestinationForWindow(windowid)
#define iins_stidle	IHsvDigitalScan_stidle
#define iins_stfewait	IHsvDigitalScan_stfewait
#define iins_stdmxwait	IHsvDigitalScan_stdmxwait
#define iins_stdecision	IHsvDigitalScan_stdecision
#define iinsctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iinsctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iinsctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iinsctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iinsctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iinsctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iinsctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iinsctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iinsctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iinsctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iinsctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iinsctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iinsctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iinsctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iinsctrlN_UNT	IHsvSdmControlNotifyEx_UNT
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
#include "locals_mInstall.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

