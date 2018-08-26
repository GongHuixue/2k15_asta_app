#ifndef  _CHSVCANALDIGITALINSTALLATION_MBACKGROUND_PRIV_H
#define  _CHSVCANALDIGITALINSTALLATION_MBACKGROUND_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IEnable.h>
#include <IHsvDigitalScan.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvPower.h>
#include <IHsvSortNotify.h>
#include <IHsvStreamNotify.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvDVBSettings.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IRealTimeKernel.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
#include <CTCMwBase.h>
class CHsvCanalDigitalInstallation_mBackground_Priv;
#define CLASSSCOPE CHsvCanalDigitalInstallation_mBackground_Priv::
#include "locals_mBackground.h"

class CHsvCanalDigitalInstallation_mBackground_Priv : public CTCMwBase
{
public:
virtual ~CHsvCanalDigitalInstallation_mBackground_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mBackground.h"
#undef MEMBERVARS
//Provided interfaces
private:
IEnableImpl(CHsvCanalDigitalInstallation_mBackground_Priv,ena);
IHsvDigitalScanImpl(CHsvCanalDigitalInstallation_mBackground_Priv,ibckg);
IHsvSdmControlNotifyExImpl(CHsvCanalDigitalInstallation_mBackground_Priv,ibckgctrlN);
IHsvPowerImpl(CHsvCanalDigitalInstallation_mBackground_Priv,ibckgpow);
IHsvSortNotifyImpl(CHsvCanalDigitalInstallation_mBackground_Priv,sortN);
IHsvStreamNotifyImpl(CHsvCanalDigitalInstallation_mBackground_Priv,strapiN);
public:
ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvDigitalScan>	ibckg;

ProvidesInterface<IHsvSdmControlNotifyEx>	ibckgctrlN;

ProvidesInterface<IHsvPower>	ibckgpow;

ProvidesInterface<IHsvSortNotify>	sortN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvChannelLibReturnCodes>	chanret;
RequiresInterface<IHsvDVBSettings>	dvbset;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvStreamNotify>	idatastrapiN;
private:
Pumpdefines(CHsvCanalDigitalInstallation_mBackground_Priv);

public:
CHsvCanalDigitalInstallation_mBackground_Priv():i__ena(this),i__ibckg(this),i__ibckgctrlN(this),i__ibckgpow(this),i__sortN(this),i__strapiN(this)
{
ena	=	&i__ena;
ibckg	=	&i__ibckg;
ibckgctrlN	=	&i__ibckgctrlN;
ibckgpow	=	&i__ibckgpow;
sortN	=	&i__sortN;
strapiN	=	&i__strapiN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define chanret_iPresent() (chanret.Present())
#define chanret_Ok	IHsvChannelLibReturnCodes_Ok
#define chanret_BadParameter	IHsvChannelLibReturnCodes_BadParameter
#define chanret_ChannelTableEmpty	IHsvChannelLibReturnCodes_ChannelTableEmpty
#define chanret_ChannelTableExhausted	IHsvChannelLibReturnCodes_ChannelTableExhausted
#define chanret_MinorNumbersExhausted	IHsvChannelLibReturnCodes_MinorNumbersExhausted
#define chanret_NotSupported	IHsvChannelLibReturnCodes_NotSupported
#define chanret_FileError	IHsvChannelLibReturnCodes_FileError
#define chanret_ChannelTableVersionError	IHsvChannelLibReturnCodes_ChannelTableVersionError
#define chanret_ChannelTableCrcError	IHsvChannelLibReturnCodes_ChannelTableCrcError
#define chanret_ChannelNotInstalled	IHsvChannelLibReturnCodes_ChannelNotInstalled
#define chanret_NVMError	IHsvChannelLibReturnCodes_NVMError
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
#define eurdiv_DeleteServiceOnFly()	eurdiv->DeleteServiceOnFly()
#define eurdiv_SupportSDTOtherInBackgroundInstallation()	eurdiv->SupportSDTOtherInBackgroundInstallation()
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
#define insN_EventTelenetNameUpdate	IHsvInstallationNotify_EventTelenetNameUpdate
#define insN_EventTelenetMajorVersionUpdate	IHsvInstallationNotify_EventTelenetMajorVersionUpdate
#define insN_OnEvent(eventid,value)	insN->OnEvent(eventid,value)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgdat_iPresent() (pgdat.Present())
#define pgdat_BoolLock	IHsvProgramData3_BoolLock
#define pgdat_BoolFavorite	IHsvProgramData3_BoolFavorite
#define pgdat_BoolFavorite1	IHsvProgramData3_BoolFavorite1
#define pgdat_BoolFavorite2	IHsvProgramData3_BoolFavorite2
#define pgdat_BoolFavorite3	IHsvProgramData3_BoolFavorite3
#define pgdat_BoolPreferredFavorite	IHsvProgramData3_BoolPreferredFavorite
#define pgdat_BoolPreferredNicam	IHsvProgramData3_BoolPreferredNicam
#define pgdat_BoolPreferredStereo	IHsvProgramData3_BoolPreferredStereo
#define pgdat_BoolSAP	IHsvProgramData3_BoolSAP
#define pgdat_BoolHMProtectedChannel	IHsvProgramData3_BoolHMProtectedChannel
#define pgdat_BoolHMBlanked	IHsvProgramData3_BoolHMBlanked
#define pgdat_BoolUserHidden	IHsvProgramData3_BoolUserHidden
#define pgdat_BoolSystemHidden	IHsvProgramData3_BoolSystemHidden
#define pgdat_BoolNumericSelect	IHsvProgramData3_BoolNumericSelect
#define pgdat_BoolEpgChannel	IHsvProgramData3_BoolEpgChannel
#define pgdat_BoolEPGShortInfoEnabled	IHsvProgramData3_BoolEPGShortInfoEnabled
#define pgdat_BoolNewPreset	IHsvProgramData3_BoolNewPreset
#define pgdat_BoolFreeCiMode	IHsvProgramData3_BoolFreeCiMode
#define pgdat_BoolTuned	IHsvProgramData3_BoolTuned
#define pgdat_BoolDeTuned	IHsvProgramData3_BoolDeTuned
#define pgdat_BoolAttenuator	IHsvProgramData3_BoolAttenuator
#define pgdat_BoolAgcInstalled	IHsvProgramData3_BoolAgcInstalled
#define pgdat_BoolChannelVirgin	IHsvProgramData3_BoolChannelVirgin
#define pgdat_BoolUpdateName	IHsvProgramData3_BoolUpdateName
#define pgdat_IntDeltaVolume	IHsvProgramData3_IntDeltaVolume
#define pgdat_Nat32DateStamp	IHsvProgramData3_Nat32DateStamp
#define pgdat_Nat32AppsCookie	IHsvProgramData3_Nat32AppsCookie
#define pgdat_Nat32TxtCookie	IHsvProgramData3_Nat32TxtCookie
#define pgdat_Nat32CesvcCookie	IHsvProgramData3_Nat32CesvcCookie
#define pgdat_Nat32DvbType	IHsvProgramData3_Nat32DvbType
#define pgdat_StringChannelName	IHsvProgramData3_StringChannelName
#define pgdat_StringExtChannelName	IHsvProgramData3_StringExtChannelName
#define pgdat_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat_IntTvSystem	IHsvProgramData3_IntTvSystem
#define pgdat_IntModulation	IHsvProgramData3_IntModulation
#define pgdat_IntNewChannelMap	IHsvProgramData3_IntNewChannelMap
#define pgdat_IntSignalStrength	IHsvProgramData3_IntSignalStrength
#define pgdat_IntSignalQuality	IHsvProgramData3_IntSignalQuality
#define pgdat_IntColoursystem	IHsvProgramData3_IntColoursystem
#define pgdat_IntDecoderType	IHsvProgramData3_IntDecoderType
#define pgdat_IntFineTuneOffset	IHsvProgramData3_IntFineTuneOffset
#define pgdat_IntFineTuneFrequency	IHsvProgramData3_IntFineTuneFrequency
#define pgdat_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat_IntNetworkId	IHsvProgramData3_IntNetworkId
#define pgdat_IntOriginalNwId	IHsvProgramData3_IntOriginalNwId
#define pgdat_IntTsid	IHsvProgramData3_IntTsid
#define pgdat_IntServiceId	IHsvProgramData3_IntServiceId
#define pgdat_IntServiceType	IHsvProgramData3_IntServiceType
#define pgdat_IntPmtPid	IHsvProgramData3_IntPmtPid
#define pgdat_IntPcrPid	IHsvProgramData3_IntPcrPid
#define pgdat_IntVideoPid	IHsvProgramData3_IntVideoPid
#define pgdat_IntVideoStreamType	IHsvProgramData3_IntVideoStreamType
#define pgdat_IntAudioPid	IHsvProgramData3_IntAudioPid
#define pgdat_IntAudioStreamType	IHsvProgramData3_IntAudioStreamType
#define pgdat_IntSecAudioPid	IHsvProgramData3_IntSecAudioPid
#define pgdat_IntSecAudioStreamType	IHsvProgramData3_IntSecAudioStreamType
#define pgdat_IntInstallMode	IHsvProgramData3_IntInstallMode
#define pgdat_IntCniNi	IHsvProgramData3_IntCniNi
#define pgdat_IntDataIndicator	IHsvProgramData3_IntDataIndicator
#define pgdat_IntPresetNumber	IHsvProgramData3_IntPresetNumber
#define pgdat_IntModulationType	IHsvProgramData3_IntModulationType
#define pgdat_IntLCN	IHsvProgramData3_IntLCN
#define pgdat_IntStreamPriority	IHsvProgramData3_IntStreamPriority
#define pgdat_IntHMMapChannelNo	IHsvProgramData3_IntHMMapChannelNo
#define pgdat_IntPtc	IHsvProgramData3_IntPtc
#define pgdat_IntAssociatedDecoder	IHsvProgramData3_IntAssociatedDecoder
#define pgdat_IntChannelBandwidth	IHsvProgramData3_IntChannelBandwidth
#define pgdat_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat_Antenna	IHsvProgramData3_Antenna
#define pgdat_Cable	IHsvProgramData3_Cable
#define pgdat_IntSystemHidden	IHsvProgramData3_IntSystemHidden
#define pgdat_IntNumericSelect	IHsvProgramData3_IntNumericSelect
#define pgdat_IntNewChannel	IHsvProgramData3_IntNewChannel
#define pgdat_StringSatelliteName	IHsvProgramData3_StringSatelliteName
#define pgdat_IntSrcambledStatus	IHsvProgramData3_IntSrcambledStatus
#define pgdat_IntInstalledSatelliteNumber	IHsvProgramData3_IntInstalledSatelliteNumber
#define pgdat_IntUserHidden	IHsvProgramData3_IntUserHidden
#define pgdat_FavoriteNumber	IHsvProgramData3_FavoriteNumber
#define pgdat_FavoriteNumber1	IHsvProgramData3_FavoriteNumber1
#define pgdat_FavoriteNumber2	IHsvProgramData3_FavoriteNumber2
#define pgdat_FavoriteNumber3	IHsvProgramData3_FavoriteNumber3
#define pgdat_IntEPGEnabled	IHsvProgramData3_IntEPGEnabled
#define pgdat_IntHbbTvOption	IHsvProgramData3_IntHbbTvOption
#define pgdat_BoolChannelLock	IHsvProgramData3_BoolChannelLock
#define pgdat_StringTxtPages	IHsvProgramData3_StringTxtPages
#define pgdat_IntLogoURL	IHsvProgramData3_IntLogoURL
#define pgdat_BoolMatchBrandFlag	IHsvProgramData3_BoolMatchBrandFlag
#define pgdat_Nat32NumBrandIds	IHsvProgramData3_Nat32NumBrandIds
#define pgdat_StringBrandIds	IHsvProgramData3_StringBrandIds
#define pgdat_Nat16PrimaryRegion	IHsvProgramData3_Nat16PrimaryRegion
#define pgdat_Nat16SecondaryRegion	IHsvProgramData3_Nat16SecondaryRegion
#define pgdat_IntTertiaryRegion	IHsvProgramData3_IntTertiaryRegion
#define pgdat_Nat32CountryCode	IHsvProgramData3_Nat32CountryCode
#define pgdat_Nat64UniqueNodeId	IHsvProgramData3_Nat64UniqueNodeId
#define pgdat_BoolUserModifiedLogo	IHsvProgramData3_BoolUserModifiedLogo
#define pgdat_MultipleLCN	IHsvProgramData3_MultipleLCN
#define pgdat_MultiplePreset	IHsvProgramData3_MultiplePreset
#define pgdat_IsValidChannel(channel)	pgdat->IsValidChannel(channel)
#define pgdat_IsChannelInstalled(channel)	pgdat->IsChannelInstalled(channel)
#define pgdat_IsAttributeSupported(attribute)	pgdat->IsAttributeSupported(attribute)
#define pgdat_ClearCurrentTable()	pgdat->ClearCurrentTable()
#define pgdat_ClearAllTables()	pgdat->ClearAllTables()
#define pgdat_GetChannelDataBool(channel,dataid,value)	pgdat->GetChannelDataBool(channel,dataid,value)
#define pgdat_GetChannelDataInt(channel,dataid,value)	pgdat->GetChannelDataInt(channel,dataid,value)
#define pgdat_GetChannelDataNat32(channel,dataid,value)	pgdat->GetChannelDataNat32(channel,dataid,value)
#define pgdat_GetChannelDataString(channel,dataid,value,size)	pgdat->GetChannelDataString(channel,dataid,value,size)
#define pgdat_StoreChannelDataBool(channel,dataid,value)	pgdat->StoreChannelDataBool(channel,dataid,value)
#define pgdat_StoreChannelDataInt(channel,dataid,value)	pgdat->StoreChannelDataInt(channel,dataid,value)
#define pgdat_StoreChannelDataNat32(channel,dataid,value)	pgdat->StoreChannelDataNat32(channel,dataid,value)
#define pgdat_StoreChannelDataString(channel,dataid,value,size)	pgdat->StoreChannelDataString(channel,dataid,value,size)
#define pgdat_GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)	pgdat->GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)
#define pgdat_SwapChannels(channel1,channel2)	pgdat->SwapChannels(channel1,channel2)
#define pgdat_LoadChannelTable(dir)	pgdat->LoadChannelTable(dir)
#define pgdat_SaveChannelTable(dir)	pgdat->SaveChannelTable(dir)
#define pgdat_ReorderChannels(channel1,channel2,Swap)	pgdat->ReorderChannels(channel1,channel2,Swap)
#define pgdat_LoadChannelTableFromMedium(dir,medium)	pgdat->LoadChannelTableFromMedium(dir,medium)
#define pgdat_SaveChannelTableToMedium(dir,medium)	pgdat->SaveChannelTableToMedium(dir,medium)
#define pgdat_GetMediumFromTable(dir,medium)	pgdat->GetMediumFromTable(dir,medium)
#define pgdat_GetNoOfBarkerMultiplexes(NoOfMuxes)	pgdat->GetNoOfBarkerMultiplexes(NoOfMuxes)
#define pgdat_GetBarkerMultiplexByIndex(index,muxes)	pgdat->GetBarkerMultiplexByIndex(index,muxes)
#define pgdat_ReArrangeChannels(channel1,channel2)	pgdat->ReArrangeChannels(channel1,channel2)
#define pgdat_GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)	pgdat->GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)
#define pgdat_GetOperator(OperatorId)	pgdat->GetOperator(OperatorId)
#define pgdat_StoreChannelDataNat64(channel,dataid,value)	pgdat->StoreChannelDataNat64(channel,dataid,value)
#define pgdat_GetChannelDataNat64(channel,dataid,value)	pgdat->GetChannelDataNat64(channel,dataid,value)
#define pgdb_iPresent() (pgdb.Present())
#define pgdb_GetCurrentTable()	pgdb->GetCurrentTable()
#define pgdb_SelectTable(tableid)	pgdb->SelectTable(tableid)
#define pgdb_ClearTable(tableid)	pgdb->ClearTable(tableid)
#define pgdb_IsSupported(tableid)	pgdb->IsSupported(tableid)
#define pgdb_CommitTable(tableid)	pgdb->CommitTable(tableid)
#define pgdb_LoadTable(tableid)	pgdb->LoadTable(tableid)
#define pgdb_GetNoRecords(tableid)	pgdb->GetNoRecords(tableid)
#define pgdb_GetByKey(tableid,channeldata)	pgdb->GetByKey(tableid,channeldata)
#define pgdb_GetIndex(tableid,index,channeldata)	pgdb->GetIndex(tableid,index,channeldata)
#define pgdb_GetByIndex(tableid,index,channeldata)	pgdb->GetByIndex(tableid,index,channeldata)
#define pgdb_GetRange(tableid,noofkeys,channeldata,from,to)	pgdb->GetRange(tableid,noofkeys,channeldata,from,to)
#define pgdb_Add(tableid,channeldata)	pgdb->Add(tableid,channeldata)
#define pgdb_Update(tableid,channeldata)	pgdb->Update(tableid,channeldata)
#define pgdb_Delete(tableid,channeldata)	pgdb->Delete(tableid,channeldata)
#define pgdb_EnableAutoCommit(enable)	pgdb->EnableAutoCommit(enable)
#define pgdb_ChannelTableChanged()	pgdb->ChannelTableChanged()
#define pgdb_Initialise(tableid,channeldata)	pgdb->Initialise(tableid,channeldata)
#define pgdb_MasterEnableEvents(Status)	pgdb->MasterEnableEvents(Status)
#define pgdb_SaveChannelMapsToBackup()	pgdb->SaveChannelMapsToBackup()
#define pgdb_LoadChannelMapsFromBackup()	pgdb->LoadChannelMapsFromBackup()
#define	pgdb_SqliteDatabase 	IHsvProgramDatabase_SqliteDatabase
#define	pgdb_TempDatabase 		IHsvProgramDatabase_TempDatabase
#define	pgdb_SelectActiveChannelDatabase(ActiveDb) 		pgdb->SelectActiveChannelDatabase(ActiveDb)
#define	pgdb_AddInIndex(tableid,index,channeldata)		pgdb->AddInIndex(tableid,index,channeldata)
#define	pgdb_BeginSqliteTransaction()					pgdb->BeginSqliteTransaction()
#define	pgdb_CommitSqliteTransaction()					pgdb->CommitSqliteTransaction()
#define pgdbconst_iPresent() (pgdbconst.Present())
#define pgdbconst_Antenna	IHsvProgramDatabaseConstants_Antenna
#define pgdbconst_Cable	IHsvProgramDatabaseConstants_Cable
#define pgdbconst_TempAntenna	IHsvProgramDatabaseConstants_TempAntenna
#define pgdbconst_TempCable	IHsvProgramDatabaseConstants_TempCable
#define pgdbconst_Satellite	IHsvProgramDatabaseConstants_Satellite
#define pgdbconst_TempSatellite	IHsvProgramDatabaseConstants_TempSatellite
#define pgdbconst_Analog	IHsvProgramDatabaseConstants_Analog
#define pgdbconst_DigitalTS	IHsvProgramDatabaseConstants_DigitalTS
#define pgdbconst_DigitalService	IHsvProgramDatabaseConstants_DigitalService
#define pgdbconst_Preset	IHsvProgramDatabaseConstants_Preset
#define pgdbconst_FrequencyMapTable	IHsvProgramDatabaseConstants_FrequencyMapTable
#define pgdbconst_CurrentDigitalService	IHsvProgramDatabaseConstants_CurrentDigitalService
#define pgdbconst_CurrentDigitalTS	IHsvProgramDatabaseConstants_CurrentDigitalTS
#define pgdbconst_CurrentAnalog	IHsvProgramDatabaseConstants_CurrentAnalog
#define pgdbconst_CurrentPreset	IHsvProgramDatabaseConstants_CurrentPreset
#define pgdbconst_CurrentFrequencyMapTable	IHsvProgramDatabaseConstants_CurrentFrequencyMapTable
#define pgdbconst_SatInfo	IHsvProgramDatabaseConstants_SatInfo
#define pgdbconst_CurrentSatInfo	IHsvProgramDatabaseConstants_CurrentSatInfo
#define pgsel_iPresent() (pgsel.Present())
#define pgsel_DefaultSelection	IHsvProgramSelection2_DefaultSelection
#define pgsel_SilentSelection	IHsvProgramSelection2_SilentSelection
#define pgsel_ControlledSelection	IHsvProgramSelection2_ControlledSelection
#define pgsel_ReplacementSelection	IHsvProgramSelection2_ReplacementSelection
#define pgsel_BreakIn	IHsvProgramSelection2_BreakIn
#define pgsel_DecoderBreakIn	IHsvProgramSelection2_DecoderBreakIn
#define pgsel_MultifeedSelection	IHsvProgramSelection2_MultifeedSelection
#define pgsel_NDTSelection	IHsvProgramSelection2_NDTSelection
#define pgsel_PriorityHigh	IHsvProgramSelection2_PriorityHigh
#define pgsel_PriorityMed	IHsvProgramSelection2_PriorityMed
#define pgsel_PriorityLow	IHsvProgramSelection2_PriorityLow
#define pgsel_Frequency	IHsvProgramSelection2_Frequency
#define pgsel_ModulationType	IHsvProgramSelection2_ModulationType
#define pgsel_TvSystem	IHsvProgramSelection2_TvSystem
#define pgsel_AudioPid	IHsvProgramSelection2_AudioPid
#define pgsel_VideoPid	IHsvProgramSelection2_VideoPid
#define pgsel_PcrPid	IHsvProgramSelection2_PcrPid
#define pgsel_ProgramNumber	IHsvProgramSelection2_ProgramNumber
#define pgsel_SymbolRate	IHsvProgramSelection2_SymbolRate
#define pgsel_DecoderType	IHsvProgramSelection2_DecoderType
#define pgsel_InvalidAttribute	IHsvProgramSelection2_InvalidAttribute
#define pgsel_SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority)	pgsel->SelectProgram(Source,ChannelNo,Dest,TypeOfSelection,Priority)
#define pgsel_GetCurrentProgram(Dest,Source,ChannelNo)	pgsel->GetCurrentProgram(Dest,Source,ChannelNo)
#define pgsel_GetActualCurrentProgram(Dest,Source,ChannelNo)	pgsel->GetActualCurrentProgram(Dest,Source,ChannelNo)
#define pgsel_IsSelectionAllowed(Source,ChannelNo,Dest)	pgsel->IsSelectionAllowed(Source,ChannelNo,Dest)
#define pgsel_IsSelectionInProgress()	pgsel->IsSelectionInProgress()
#define pgsel_GetLastRequestedProgram(Dest,Source,ChannelNo)	pgsel->GetLastRequestedProgram(Dest,Source,ChannelNo)
#define pgsel_GetLastActualRequestedProgram(Dest,Source,ChannelNo)	pgsel->GetLastActualRequestedProgram(Dest,Source,ChannelNo)
#define pgsel_IsAssociationAllowed(Source,AssociationSource)	pgsel->IsAssociationAllowed(Source,AssociationSource)
#define pgsel_SetAssociation(Source,AssociationSource)	pgsel->SetAssociation(Source,AssociationSource)
#define pgsel_GetAssociation(Source)	pgsel->GetAssociation(Source)
#define pgsel_EnableAllExtensionBreakIn(enable)	pgsel->EnableAllExtensionBreakIn(enable)
#define pgsel_IsAllExtensionBreakInEnabled()	pgsel->IsAllExtensionBreakInEnabled()
#define pgsel_EnableExtensionBreakIn(ext,enable)	pgsel->EnableExtensionBreakIn(ext,enable)
#define pgsel_IsExtensionBreakInEnabled(ext)	pgsel->IsExtensionBreakInEnabled(ext)
#define pgsel_EnableBreakInHistory(enable)	pgsel->EnableBreakInHistory(enable)
#define pgsel_IsBreakInHistoryEnabled()	pgsel->IsBreakInHistoryEnabled()
#define pgsel_ClearBreakInStack()	pgsel->ClearBreakInStack()
#define pgsel_IsBreakInStackEmpty()	pgsel->IsBreakInStackEmpty()
#define pgsel_GetBreakInSourceByIndex(index,BreakInSource)	pgsel->GetBreakInSourceByIndex(index,BreakInSource)
#define pgsel_GetNumberOfBreakInSources()	pgsel->GetNumberOfBreakInSources()
#define pgsel_GetRuningStatusForService()	pgsel->GetRuningStatusForService()
#define pgsel_IsDualWindowCombinationAllowed(MainSource,MainChannel,AuxSource,AuxChannel)	pgsel->IsDualWindowCombinationAllowed(MainSource,MainChannel,AuxSource,AuxChannel)
#define pgsel_SetAttribute(attribute,value)	pgsel->SetAttribute(attribute,value)
#define pgsel_GetAttribute(attribute,value)	pgsel->GetAttribute(attribute,value)
#define pgsel_IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection)	pgsel->IsTuningRequired(Source,ChannelNo,Dest,TypeOfSelection)
#define pgsel_GetActualTypeOfSelection(Dest)	pgsel->GetActualTypeOfSelection(Dest)
#define pgsel_IsProgramSelectionRequired(Channel)	pgsel->IsProgramSelectionRequired(Channel)
#define pgsel_SetVirginBitOn()	pgsel->SetVirginBitOn()
#define plfres_iPresent() (plfres.Present())
#define plfres_IsResourceOwned(resid)	plfres->IsResourceOwned(resid)
#define plfres_GetOwnedResources()	plfres->GetOwnedResources()
#define plfres_AudioFeaturing	ITvPlatformResource_AudioFeaturing
#define plfres_Connectivity	ITvPlatformResource_Connectivity
#define plfres_Frontend	ITvPlatformResource_Frontend
#define plfres_General	ITvPlatformResource_General
#define plfres_Infrastructure	ITvPlatformResource_Infrastructure
#define plfres_Source	ITvPlatformResource_Source
#define plfres_VideoFeaturing	ITvPlatformResource_VideoFeaturing
#define plfres_Xray	ITvPlatformResource_Xray
#define plfres_Scale	ITvPlatformResource_Scale
#define plfres_Gfx	ITvPlatformResource_Gfx
#define plfres_Mute	ITvPlatformResource_Mute
#define plfres_GetResourceState()	plfres->GetResourceState()
#define plfres_RequestResourceState(State)	plfres->RequestResourceState(State)
#define plfres_RestorePreviousState()	plfres->RestorePreviousState()
#define plfres_FullState	ITvPlatformResource_FullState
#define plfres_SubState	ITvPlatformResource_SubState
#define plfres_IdleState	ITvPlatformResource_IdleState
#define plfres_FullStateWithVideoScale	ITvPlatformResource_FullStateWithVideoScale
#define plfres_Invalid	ITvPlatformResource_Invalid
#define plfres_FullWithScaleState	ITvPlatformResource_FullWithScaleState
#define plfres_IdleWithMuteState	ITvPlatformResource_IdleWithMuteState
#define plfres_FullStateWithOutMute	ITvPlatformResource_FullStateWithOutMute
#define plfres_FrontEndState	ITvPlatformResource_FrontEndState
#define plfres_ScaleState	ITvPlatformResource_ScaleState
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvCanalDigitalInstallation_mBackground_Priv::func,replace,(char *)name,this)
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
#define rins_CanalDigital	IHsvInstallation2_CanalDigital
#define rins_YouSee	IHsvInstallation2_YouSee
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
#define rins_CanalDigitalNetworkDataSet(ActionValue)	rins->CanalDigitalNetworkDataSet(ActionValue)
#define rins_ClearPersistent()	rins->ClearPersistent()
#define rtk_iPresent() (rtk.Present())
#define rtk_PrioHighest	rtk->PrioHighest()
#define rtk_PrioHigh	rtk->PrioHigh()
#define rtk_PrioAboveNormal	rtk->PrioAboveNormal()
#define rtk_PrioNormal	rtk->PrioNormal()
#define rtk_PrioBelowNormal	rtk->PrioBelowNormal()
#define rtk_PrioLow	rtk->PrioLow()
#define rtk_PrioLowest	rtk->PrioLowest()
#define rtk_TskCreate(func,priority,stacksize)	rtk->TskCreate(func,priority,stacksize)
#define rtk_TskCreateNoWatchdog(func,priority,stacksize)	rtk->TskCreateNoWatchdog(func,priority,stacksize)
#define rtk_TskDelete(tsk)	rtk->TskDelete(tsk)
#define rtk_TskCurrent()	rtk->TskCurrent()
#define rtk_TskSetPriority(tsk,priority)	rtk->TskSetPriority(tsk,priority)
#define rtk_TskSuspend(msecs)	rtk->TskSuspend(msecs)
#define rtk_TskResume(tsk)	rtk->TskResume(tsk)
#define rtk_TskBeginCriticalSection()	rtk->TskBeginCriticalSection()
#define rtk_TskEndCriticalSection()	rtk->TskEndCriticalSection()
#define rtk_TskFeedWatchdog()	rtk->TskFeedWatchdog()
#define rtk_TskBoostWatchdog(seconds)	rtk->TskBoostWatchdog(seconds)
#define rtk_TskWatchdogPeriod()	rtk->TskWatchdogPeriod()
#define rtk_IsrBegin()	rtk->IsrBegin()
#define rtk_IsrEnd()	rtk->IsrEnd()
#define rtk_IsrEvtSend(tsk,evt)	rtk->IsrEvtSend(tsk,evt)
#define rtk_IsrMbxSend(mbx,msg,param1,param2)	rtk->IsrMbxSend(mbx,msg,param1,param2)
#define rtk_SemCreate()	rtk->SemCreate()
#define rtk_SemCreateWithCeiling(ceiling)	rtk->SemCreateWithCeiling(ceiling)
#define rtk_SemDelete(sem)	rtk->SemDelete(sem)
#define rtk_SemAcquire(sem)	rtk->SemAcquire(sem)
#define rtk_SemAcquireNoWait(sem)	rtk->SemAcquireNoWait(sem)
#define rtk_SemRelease(sem)	rtk->SemRelease(sem)
#define rtk_EvtCreate(tsk)	rtk->EvtCreate(tsk)
#define rtk_EvtDelete(tsk,evt)	rtk->EvtDelete(tsk,evt)
#define rtk_EvtSend(tsk,evt)	rtk->EvtSend(tsk,evt)
#define rtk_EvtReceive(mask)	rtk->EvtReceive(mask)
#define rtk_EvtReceiveNoWait(mask)	rtk->EvtReceiveNoWait(mask)
#define rtk_EvtReceiveWait(mask,msecs)	rtk->EvtReceiveWait(mask,msecs)
#define rtk_EvtGetReserved(tsk)	rtk->EvtGetReserved(tsk)
#define rtk_TmrCreate(tsk,evt)	rtk->TmrCreate(tsk,evt)
#define rtk_TmrDelete(tmr)	rtk->TmrDelete(tmr)
#define rtk_TmrEvery(tmr,msecs)	rtk->TmrEvery(tmr,msecs)
#define rtk_TmrOnce(tmr,msecs)	rtk->TmrOnce(tmr,msecs)
#define rtk_TmrCancel(tmr)	rtk->TmrCancel(tmr)
#define rtk_TmrTime()	rtk->TmrTime()
#define rtk_TmrResolution()	rtk->TmrResolution()
#define rtk_MbxCreate()	rtk->MbxCreate()
#define rtk_MbxDelete(mbx)	rtk->MbxDelete(mbx)
#define rtk_MbxSend(mbx,msg,param1,param2)	rtk->MbxSend(mbx,msg,param1,param2)
#define rtk_MbxReceive(mbx,msg)	rtk->MbxReceive(mbx,msg)
#define rtk_MbxReceiveNoWait(mbx,msg)	rtk->MbxReceiveNoWait(mbx,msg)
#define rtk_TlsCreate(size)	rtk->TlsCreate(size)
#define rtk_TlsAccess(tls)	rtk->TlsAccess(tls)
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
#define sort_iPresent() (sort.Present())
#define sort_Initialise()	sort->Initialise()
#define sort_AddAnalogPreset(adata)	sort->AddAnalogPreset(adata)
#define sort_AnalogPresetEntry()	sort->AnalogPresetEntry()
#define sort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	sort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define sort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	sort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define sort_AssignPresetsOfOtherCountries()	sort->AssignPresetsOfOtherCountries()
#define sort_AddDigitalPreset(svcdat)	sort->AddDigitalPreset(svcdat)
#define sort_AutoStoreManualInstallationValues()	sort->AutoStoreManualInstallationValues()
#define sort_RemoveDigitalPresets()	sort->RemoveDigitalPresets()
#define sort_GetNumberOfAnalogChannelsFound()	sort->GetNumberOfAnalogChannelsFound()
#define sort_UpdateDigitalPreset(svcdat)	sort->UpdateDigitalPreset(svcdat)
#define sort_DeleteAllDigitalChannels()	sort->DeleteAllDigitalChannels()
#define sort_UpdatingLCNDuringUpdateInstallation()	sort->UpdatingLCNDuringUpdateInstallation()
#define sort_DeleteInvalidPTCTable()	sort->DeleteInvalidPTCTable()
#define sort_GetOriginalNetworkId(CurrentCountry)	sort->GetOriginalNetworkId(CurrentCountry)
#define sort_IsPresetInstalled(frequency)	sort->IsPresetInstalled(frequency)
#define sort_AssignPresetsForCountry(ONID)	sort->AssignPresetsForCountry(ONID)
#define sort_SortAll()	sort->SortAll()
#define sort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	sort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define sort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	sort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define sort_GetInstalledWeakSignalChannel()	sort->GetInstalledWeakSignalChannel()
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
#define ibckg_stidle	IHsvDigitalScan_stidle
#define ibckg_stfewait	IHsvDigitalScan_stfewait
#define ibckg_stdmxwait	IHsvDigitalScan_stdmxwait
#define ibckg_stdecision	IHsvDigitalScan_stdecision
#define ibckgctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ibckgctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ibckgctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ibckgctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ibckgctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ibckgctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ibckgctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ibckgctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ibckgctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ibckgctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ibckgctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ibckgctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ibckgctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ibckgctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ibckgctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define sortN_EventNewPresetFound	IHsvSortNotify_EventNewPresetFound
#define sortN_EventChannelRemoved	IHsvSortNotify_EventChannelRemoved
#define sortN_EventSortComplete	IHsvSortNotify_EventSortComplete
#define idatastrapiN_iPresent() (idatastrapiN.Present())
#define idatastrapiN_OnCompleted(dest,spid)	idatastrapiN->OnCompleted(dest,spid)
#define idatastrapiN_OnAdded(dest,spid,key1,key2,key3)	idatastrapiN->OnAdded(dest,spid,key1,key2,key3)
#define idatastrapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	idatastrapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define idatastrapiN_OnRemoved(dest,spid,key1,key2,key3)	idatastrapiN->OnRemoved(dest,spid,key1,key2,key3)
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
#include "locals_mBackground.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

