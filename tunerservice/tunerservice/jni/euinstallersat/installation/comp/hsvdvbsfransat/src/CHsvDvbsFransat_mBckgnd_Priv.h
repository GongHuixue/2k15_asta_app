#ifndef  _CHSVDVBSFRANSAT_MBCKGND_PRIV_H
#define  _CHSVDVBSFRANSAT_MBCKGND_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvPower.h>
#include <ITvPlatformResourceNotify.h>
#include <IHsvStreamNotify.h>
#include <IProdApiSystemStateObserverNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvStream.h>
#include <CS2MwBase.h>
class CHsvDvbsFransat_mBckgnd_Priv;
#define CLASSSCOPE CHsvDvbsFransat_mBckgnd_Priv::
#include "locals_mBckgnd.h"

class CHsvDvbsFransat_mBckgnd_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsFransat_mBckgnd_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mBckgnd.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmControlNotifyExImpl(CHsvDvbsFransat_mBckgnd_Priv,bckctrlN);
IHsvDigitalAcquisitionNotifyImpl(CHsvDvbsFransat_mBckgnd_Priv,ibckAcqN);
IHsvSatelliteBackgroundInstallationImpl(CHsvDvbsFransat_mBckgnd_Priv,ibckInstall);
IHsvPowerImpl(CHsvDvbsFransat_mBckgnd_Priv,ibckgndpow);
ITvPlatformResourceNotifyImpl(CHsvDvbsFransat_mBckgnd_Priv,plfresN);
IHsvStreamNotifyImpl(CHsvDvbsFransat_mBckgnd_Priv,strapiN);
IProdApiSystemStateObserverNotifyImpl(CHsvDvbsFransat_mBckgnd_Priv,sysstateN);
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;

ProvidesInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;

ProvidesInterface<IHsvPower>	ibckgndpow;

ProvidesInterface<ITvPlatformResourceNotify>	plfresN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IProdApiSystemStateObserverNotify>	sysstateN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IProdApiSystemStateObserverExExExEx>	observer;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvStream>	strapi;
private:
Pumpdefines(CHsvDvbsFransat_mBckgnd_Priv);

public:
CHsvDvbsFransat_mBckgnd_Priv():i__bckctrlN(this),i__ibckAcqN(this),i__ibckInstall(this),i__ibckgndpow(this),i__plfresN(this),i__strapiN(this),i__sysstateN(this)
{
bckctrlN	=	&i__bckctrlN;
ibckAcqN	=	&i__ibckAcqN;
ibckInstall	=	&i__ibckInstall;
ibckgndpow	=	&i__ibckgndpow;
plfresN	=	&i__plfresN;
strapiN	=	&i__strapiN;
sysstateN	=	&i__sysstateN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define err_iPresent() (err.Present())
#define err_Ok	IHsvErrorCodeEx_Ok
#define err_BadParameter	IHsvErrorCodeEx_BadParameter
#define err_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define err_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define err_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define err_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define err_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define err_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define err_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define err_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define err_FileError	IHsvErrorCodeEx_FileError
#define err_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define err_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define err_NotSupported	IHsvErrorCodeEx_NotSupported
#define err_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define err_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define err_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define err_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define err_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define err_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define err_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define err_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define err_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define err_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define err_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define err_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define err_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define err_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define err_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define err_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define err_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define err_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define err_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define err_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define err_DiseqcError	IHsvErrorCodeEx_DiseqcError
#define err_TunerError	IHsvErrorCodeEx_TunerError
#define err_UsbPathNotFound	IHsvErrorCodeEx_UsbPathNotFound
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
#define eurdiv_AnalogOnly	eurdiv->AnalogOnly()
#define eurdiv_InstallTestStreams(installationmode,medium)	eurdiv->InstallTestStreams(installationmode,medium)
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_NoOfVirtualChannelsSupported(medium)	eurdiv->NoOfVirtualChannelsSupported(medium)
#define eurdiv_ForceLCNSyntax(medium)	eurdiv->ForceLCNSyntax(medium)
#define eurdiv_DefaultStreamPriority(medium)	eurdiv->DefaultStreamPriority(medium)
#define eurdiv_IsServiceInstallable(medium,ServiceType)	eurdiv->IsServiceInstallable(medium,ServiceType)
#define eurdiv_IsServiceHidden(medium,ServiceType)	eurdiv->IsServiceHidden(medium,ServiceType)
#define eurdiv_AcceptedStreamType(medium,StreamType)	eurdiv->AcceptedStreamType(medium,StreamType)
#define eurdiv_UpdateChannelName(medium)	eurdiv->UpdateChannelName(medium)
#define eurdiv_IsDbookCountry()	eurdiv->IsDbookCountry()
#define eurdiv_SkipInstallationPass	eurdiv->SkipInstallationPass()
#define eurdiv_FirstInstallationPass	eurdiv->FirstInstallationPass()
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_TxtInfoTimeout	eurdiv->TxtInfoTimeout()
#define eurdiv_VideoMuteColor	eurdiv->VideoMuteColor()
#define eurdiv_VideoMuteColorForLocks	eurdiv->VideoMuteColorForLocks()
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	eurdiv->DecoderSupported()
#define eurdiv_BreakInSupported	eurdiv->BreakInSupported()
#define eurdiv_ScartRuleSupported	eurdiv->ScartRuleSupported()
#define eurdiv_HsvAntennaDigSrvcTable	eurdiv->HsvAntennaDigSrvcTable()
#define eurdiv_HsvAntennaDigPtcTable	eurdiv->HsvAntennaDigPtcTable()
#define eurdiv_HsvAntennaFreqMapTable	eurdiv->HsvAntennaFreqMapTable()
#define eurdiv_PersistentMemUpdateTimeout	eurdiv->PersistentMemUpdateTimeout()
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	eurdiv->MaxNoOfChannelsToStoreAntennaUserTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigPtcTable()
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreAntennaFreqMapTable()
#define eurdiv_IsHDSubtitleSupported()	eurdiv->IsHDSubtitleSupported()
#define eurdiv_AvSignalDetectionTimeOut	eurdiv->AvSignalDetectionTimeOut()
#define eurdiv_HearingImpairedOn	eurdiv->HearingImpairedOn()
#define eurdiv_VisuallyImpairedOn	eurdiv->VisuallyImpairedOn()
#define eurdiv_IsQaaSupported	eurdiv->IsQaaSupported()
#define eurdiv_IsPremixedVISupported	eurdiv->IsPremixedVISupported()
#define eurdiv_EPGSecondaryDirName	eurdiv->EPGSecondaryDirName()
#define eurdiv_DefaultCharacterTable	eurdiv->DefaultCharacterTable()
#define eurdiv_ShortInfoCacheForCountry	eurdiv->ShortInfoCacheForCountry()
#define eurdiv_OUI	eurdiv->OUI()
#define eurdiv_HardwareModel	eurdiv->HardwareModel()
#define eurdiv_HardwareVersion	eurdiv->HardwareVersion()
#define eurdiv_GetNoOfBackBuffers(clientId)	eurdiv->GetNoOfBackBuffers(clientId)
#define eurdiv_SubtitleTimeOut	eurdiv->SubtitleTimeOut()
#define eurdiv_IsMpeg4STBoltOnSupported()	eurdiv->IsMpeg4STBoltOnSupported()
#define eurdiv_ForceCharacterTable	eurdiv->ForceCharacterTable()
#define eurdiv_RegionalCharacterTable	eurdiv->RegionalCharacterTable()
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
#define eurdiv_HsvCableDigSrvcTable	eurdiv->HsvCableDigSrvcTable()
#define eurdiv_HsvCableDigPtcTable	eurdiv->HsvCableDigPtcTable()
#define eurdiv_HsvCableSvcListDescTable	eurdiv->HsvCableSvcListDescTable()
#define eurdiv_HsvCableFreqMapTable	eurdiv->HsvCableFreqMapTable()
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	eurdiv->MaxNoOfChannelsToStoreCableUserTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreCableDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	eurdiv->MaxNoOfChannelsToStoreCableDigPtcTable()
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreCableFreqMapTable()
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_GetDefaultScanMode(medium)	eurdiv->GetDefaultScanMode(medium)
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_GetNextScan(medium,installationmode,ScanPreference)	eurdiv->GetNextScan(medium,installationmode,ScanPreference)
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_GetAudioPreference()	eurdiv->GetAudioPreference()
#define eurdiv_GetSubtitlePreference()	eurdiv->GetSubtitlePreference()
#define eurdiv_UserPreferredAudioFormat()	eurdiv->UserPreferredAudioFormat()
#define eurdiv_HsvDVBCSettingsFilePath	eurdiv->HsvDVBCSettingsFilePath()
#define eurdiv_HsvCableDelSysDescFilePath	eurdiv->HsvCableDelSysDescFilePath()
#define eurdiv_HsvServiceListDescFilePath	eurdiv->HsvServiceListDescFilePath()
#define eurdiv_MaxLCNValue	eurdiv->MaxLCNValue()
#define eurdiv_IsBackgroundInstallRequired(medium)	eurdiv->IsBackgroundInstallRequired(medium)
#define eurdiv_SupportLCNVersion2(medium)	eurdiv->SupportLCNVersion2(medium)
#define eurdiv_ParseLCN(medium,installationmode)	eurdiv->ParseLCN(medium,installationmode)
#define eurdiv_IsPreScanSupported(medium)	eurdiv->IsPreScanSupported(medium)
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
#define eurdiv_IsAc3AudioSupported()	eurdiv->IsAc3AudioSupported()
#define eurdiv_StaticTable()	eurdiv->StaticTable()
#define eurdiv_GetDefaultDigitalInstallStatus(country)	eurdiv->GetDefaultDigitalInstallStatus(country)
#define eurdiv_IsMultifeedSupported()	eurdiv->IsMultifeedSupported()
#define eurdiv_GetViterbiBER()	eurdiv->GetViterbiBER()
#define eurdiv_DeltaViterbiBER()	eurdiv->DeltaViterbiBER()
#define eurdiv_GetShortInfoCacheSize()	eurdiv->GetShortInfoCacheSize()
#define eurdiv_GetDeltaSQI()	eurdiv->GetDeltaSQI()
#define eurdiv_GetDeltaSSI()	eurdiv->GetDeltaSSI()
#define eurdiv_AutomaticDigitalPresetAllocation	eurdiv->AutomaticDigitalPresetAllocation()
#define eurdiv_NonRadioStartPreset(country,medium,numRecords)	eurdiv->NonRadioStartPreset(country,medium,numRecords)
#define eurdiv_NonRadioEndPreset(country,medium)	eurdiv->NonRadioEndPreset(country,medium)
#define eurdiv_RadioStartPreset(country,medium,numRecords)	eurdiv->RadioStartPreset(country,medium,numRecords)
#define eurdiv_RadioEndPreset(country,medium)	eurdiv->RadioEndPreset(country,medium)
#define eurdiv_IsHDSimulcastSupported()	eurdiv->IsHDSimulcastSupported()
#define eurdiv_FirstLCNOnlySupported()	eurdiv->FirstLCNOnlySupported()
#define eurdiv_IsDigiturkPackage()	eurdiv->IsDigiturkPackage()
#define idataacq_iPresent() (idataacq.Present())
#define idataacq_Homing	IHsvDigitalAcquisition_Homing
#define idataacq_Fallback	IHsvDigitalAcquisition_Fallback
#define idataacq_Normal	IHsvDigitalAcquisition_Normal
#define idataacq_Background	IHsvDigitalAcquisition_Background
#define idataacq_Initialise(LnbNumber)	idataacq->Initialise(LnbNumber)
#define idataacq_AcquireData(Mode)	idataacq->AcquireData(Mode)
#define idataacq_AcquireDataOnTimeout()	idataacq->AcquireDataOnTimeout()
#define idataacq_GetNumberOfDigitalChannelsFound()	idataacq->GetNumberOfDigitalChannelsFound()
#define idataacq_GetNumberOfDigitalChannelsRemoved()	idataacq->GetNumberOfDigitalChannelsRemoved()
#define idataacq_GetNumberOfTvChannelsFound()	idataacq->GetNumberOfTvChannelsFound()
#define idataacq_GetNumberOfRadioChannelsFound()	idataacq->GetNumberOfRadioChannelsFound()
#define idataacq_GetNumberOfTvChannelsRemoved()	idataacq->GetNumberOfTvChannelsRemoved()
#define idataacq_GetNumberofRadioChannelsRemoved()	idataacq->GetNumberofRadioChannelsRemoved()
#define idataacq_StoreBarkerMuxDetails()	idataacq->StoreBarkerMuxDetails()
#define idataacq_SyncTemporaryTableRecords()	idataacq->SyncTemporaryTableRecords()
#define idataacq_GetNumberOfSdsds()	idataacq->GetNumberOfSdsds()
#define idataacq_GetSdsdByIndex(count,SdSdEntry)	idataacq->GetSdsdByIndex(count,SdSdEntry)
#define idataacq_GetNumberOfTvChannelsInLnb(Lnb)	idataacq->GetNumberOfTvChannelsInLnb(Lnb)
#define idataacq_GetNumberOfRadioChannelsInLnb(Lnb)	idataacq->GetNumberOfRadioChannelsInLnb(Lnb)
#define iinsN_iPresent() (iinsN.Present())
#define iinsN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define iinsN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define iinsN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
#define iinsN_EventInsFailed	IHsvSatelliteInstallationNotify_EventInsFailed
#define iinsN_EventSatelliteFound	IHsvSatelliteInstallationNotify_EventSatelliteFound
#define iinsN_EventSatelliteNotFound	IHsvSatelliteInstallationNotify_EventSatelliteNotFound
#define iinsN_EventSortingStarted	IHsvSatelliteInstallationNotify_EventSortingStarted
#define iinsN_EventSortStopped	IHsvSatelliteInstallationNotify_EventSortStopped
#define iinsN_EventSortCompleted	IHsvSatelliteInstallationNotify_EventSortCompleted
#define iinsN_EventSortInProgress	IHsvSatelliteInstallationNotify_EventSortInProgress
#define iinsN_EventChannelFound	IHsvSatelliteInstallationNotify_EventChannelFound
#define iinsN_EventChannelNotFound	IHsvSatelliteInstallationNotify_EventChannelNotFound
#define iinsN_EventInsProgress	IHsvSatelliteInstallationNotify_EventInsProgress
#define iinsN_EventInsCompletedForLnb	IHsvSatelliteInstallationNotify_EventInsCompletedForLnb
#define iinsN_EventSatLnbRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted
#define iinsN_EventContentLibRead	IHsvSatelliteInstallationNotify_EventContentLibRead
#define iinsN_EventPkgInstallStart	IHsvSatelliteInstallationNotify_EventPkgInstallStart
#define iinsN_EventPkgInstallEnd	IHsvSatelliteInstallationNotify_EventPkgInstallEnd
#define iinsN_EventRegionScanEnd	IHsvSatelliteInstallationNotify_EventRegionScanEnd
#define iinsN_EventLNBStart	IHsvSatelliteInstallationNotify_EventLNBStart
#define iinsN_EventLNBEnd	IHsvSatelliteInstallationNotify_EventLNBEnd
#define iinsN_EventSatLnbRemovalStarted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted
#define iinsN_EventSatRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatRemovalCompleted
#define iinsN_EventPackageInstallFailed	IHsvSatelliteInstallationNotify_EventPackageInstallFailed
#define iinsN_EventPackageId	IHsvSatelliteInstallationNotify_EventPackageId
#define iinsN_EventPredefinedListCopySuccesful	IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful
#define iinsN_EventPredefinedListCopyGenericError	IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError
#define iinsN_EventPredefinedListCopyOlderVersion	IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion
#define iinsN_EventDifferentSatelliteFound	IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound
#define iinsN_EventPkgParsingStarted	IHsvSatelliteInstallationNotify_EventPkgParsingStarted
#define iinsN_EventPkgParsingCompleted	IHsvSatelliteInstallationNotify_EventPkgParsingCompleted
#define iinsN_EventTriggerBckgndUpdateInstall	IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall
#define iinsN_OnEvent(eventid,value)	iinsN->OnEvent(eventid,value)
#define insstate_iPresent() (insstate.Present())
#define insstate_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define insstate_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define insstate_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define insstate_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define insstate_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define insstate_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define insstate_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define insstate_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define insstate_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define insstate_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define insstate_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define insstate_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define insstate_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define insstate_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define insstate_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define insstate_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define insstate_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define insstate_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define insstate_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define insstate_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define insstate_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define insstate_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define insstate_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define insstate_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define insstate_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define insstate_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define insstate_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define insstate_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define insstate_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define insstate_GetCurrentInstallationState(mode,state)	insstate->GetCurrentInstallationState(mode,state)
#define insstate_StartInstallation(Source,Lnb,Mode)	insstate->StartInstallation(Source,Lnb,Mode)
#define insstate_StopInstallation()	insstate->StopInstallation()
#define insstate_ResetInstallation()	insstate->ResetInstallation()
#define insstate_GetNumberOfTvChannelsFound(Lnb)	insstate->GetNumberOfTvChannelsFound(Lnb)
#define insstate_GetNumberofRadioChannelsFound(Lnb)	insstate->GetNumberofRadioChannelsFound(Lnb)
#define insstate_GetNumberOfTvChannelsRemoved(Lnb)	insstate->GetNumberOfTvChannelsRemoved(Lnb)
#define insstate_GetNumberofRadioChannelsRemoved(Lnb)	insstate->GetNumberofRadioChannelsRemoved(Lnb)
#define insstate_GetSatelliteName(Lnb,SatelliteName)	insstate->GetSatelliteName(Lnb,SatelliteName)
#define insstate_GetNumberOfDigitalChannelsAdded()	insstate->GetNumberOfDigitalChannelsAdded()
#define insstate_GetNumberOfDigitalChannelsRemoved()	insstate->GetNumberOfDigitalChannelsRemoved()
#define insstate_GetNumberOfDigitalChannelsMoved()	insstate->GetNumberOfDigitalChannelsMoved()
#define insstate_IdentifyPackagesAvailable()	insstate->IdentifyPackagesAvailable()
#define insstate_GetTotalNumberOfPackagesFound()	insstate->GetTotalNumberOfPackagesFound()
#define insstate_GetPackageByIndex(Index,Package)	insstate->GetPackageByIndex(Index,Package)
#define insstate_SetUserPackageIndex(PackageIndex)	insstate->SetUserPackageIndex(PackageIndex)
#define insstate_GetUserPackageIndex(PackageIndex,IsPackage)	insstate->GetUserPackageIndex(PackageIndex,IsPackage)
#define insstate_GetInstalledSatellites(mode,SatelliteEntries)	insstate->GetInstalledSatellites(mode,SatelliteEntries)
#define insstate_InstallAddedSatellites()	insstate->InstallAddedSatellites()
#define insstate_ResetAddedSatellites()	insstate->ResetAddedSatellites()
#define insstate_RemoveSatelliteEntry(LnbNumber)	insstate->RemoveSatelliteEntry(LnbNumber)
#define insstate_GetSatelliteSignalStrength(LnbNumber)	insstate->GetSatelliteSignalStrength(LnbNumber)
#define insstate_GetSatelliteSignalQuality(LnbNumber)	insstate->GetSatelliteSignalQuality(LnbNumber)
#define insstate_LoadManualInstallationDefaultValues()	insstate->LoadManualInstallationDefaultValues()
#define insstate_StoreManualInstallationValues()	insstate->StoreManualInstallationValues()
#define insstate_GetAttribute(Mode,AttributeId)	insstate->GetAttribute(Mode,AttributeId)
#define insstate_SetAttribute(Mode,AttributeId,Value)	insstate->SetAttribute(Mode,AttributeId,Value)
#define insstate_GetScanProgressStatus(Mode)	insstate->GetScanProgressStatus(Mode)
#define insstate_GetSITableIds(NetworkID,BouquetID)	insstate->GetSITableIds(NetworkID,BouquetID)
#define insstate_GetPackageName(PackageId,PackageName)	insstate->GetPackageName(PackageId,PackageName)
#define insstate_GetSIDetails(SiValues)	insstate->GetSIDetails(SiValues)
#define insstate_EnableUnicable(LnbNumber,Enable)	insstate->EnableUnicable(LnbNumber,Enable)
#define insstate_StopSignalStrengthMeas(LnbNumber)	insstate->StopSignalStrengthMeas(LnbNumber)
#define insstate_GetSignalQuality(Param)	insstate->GetSignalQuality(Param)
#define insstate_StartSignalStrengthMeas(LnbNumber)	insstate->StartSignalStrengthMeas(LnbNumber)
#define insstate_GetSignalStrength(param)	insstate->GetSignalStrength(param)
#define insstate_StartPredefinedListCopy()	insstate->StartPredefinedListCopy()
#define insstate_GetFirstInstalledChannel()	insstate->GetFirstInstalledChannel()
#define insstate_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	insstate->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define observer_iPresent() (observer.Present())
#define observer_IsRecordingOngoing()	observer->IsRecordingOngoing()
#define observer_GetMultiviewState(ena)	observer->GetMultiviewState(ena)
#define observer_GetSystemDisabledEvents()	observer->GetSystemDisabledEvents()
#define observer_IsTimeShiftActive()	observer->IsTimeShiftActive()
#define observer_IsSkypeActive()	observer->IsSkypeActive()
#define observer_IsTopmenubarActive()	observer->IsTopmenubarActive()
#define observer_IsDmsPlaybackOngoing()	observer->IsDmsPlaybackOngoing()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgdat_iPresent() (pgdat.Present())
#define pgdat_BoolLock	pgdat->BoolLock()
#define pgdat_BoolFavorite	pgdat->BoolFavorite()
#define pgdat_BoolUserHidden	pgdat->BoolUserHidden()
#define pgdat_BoolSystemHidden	pgdat->BoolSystemHidden()
#define pgdat_BoolNewPreset	pgdat->BoolNewPreset()
#define pgdat_BoolFreeCiMode	pgdat->BoolFreeCiMode()
#define pgdat_BoolUpdateName	pgdat->BoolUpdateName()
#define pgdat_IntDeltaVolume	pgdat->IntDeltaVolume()
#define pgdat_Nat32DateStamp	pgdat->Nat32DateStamp()
#define pgdat_Nat32AppsCookie	pgdat->Nat32AppsCookie()
#define pgdat_Nat32TxtCookie	pgdat->Nat32TxtCookie()
#define pgdat_StringChannelName	pgdat->StringChannelName()
#define pgdat_StringExtChannelName	pgdat->StringExtChannelName()
#define pgdat_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat_IntModulation	pgdat->IntModulation()
#define pgdat_IntSignalStrength	pgdat->IntSignalStrength()
#define pgdat_IntSignalQuality	pgdat->IntSignalQuality()
#define pgdat_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat_IntNetworkId	pgdat->IntNetworkId()
#define pgdat_IntOriginalNwId	pgdat->IntOriginalNwId()
#define pgdat_IntTsid	pgdat->IntTsid()
#define pgdat_IntServiceId	pgdat->IntServiceId()
#define pgdat_IntServiceType	pgdat->IntServiceType()
#define pgdat_IntPmtPid	pgdat->IntPmtPid()
#define pgdat_IntPcrPid	pgdat->IntPcrPid()
#define pgdat_IntVideoPid	pgdat->IntVideoPid()
#define pgdat_IntVideoStreamType	pgdat->IntVideoStreamType()
#define pgdat_IntAudioPid	pgdat->IntAudioPid()
#define pgdat_IntAudioStreamType	pgdat->IntAudioStreamType()
#define pgdat_IntSecAudioPid	pgdat->IntSecAudioPid()
#define pgdat_IntSecAudioStreamType	pgdat->IntSecAudioStreamType()
#define pgdat_IntPresetNumber	pgdat->IntPresetNumber()
#define pgdat_IntModulationType	pgdat->IntModulationType()
#define pgdat_IntLCN	pgdat->IntLCN()
#define pgdat_IntPtc	pgdat->IntPtc()
#define pgdat_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat_Antenna	IHsvProgramData3_Antenna
#define pgdat_Cable	IHsvProgramData3_Cable
#define pgdat_IntSystemHidden	pgdat->IntSystemHidden()
#define pgdat_IntNumericSelect	pgdat->IntNumericSelect()
#define pgdat_IntNewChannel	pgdat->IntNewChannel()
#define pgdat_StringSatelliteName	pgdat->StringSatelliteName()
#define pgdat_IntSrcambledStatus	pgdat->IntSrcambledStatus()
#define pgdat_IntInstalledSatelliteNumber	pgdat->IntInstalledSatelliteNumber()
#define pgdat_IntUserHidden	pgdat->IntUserHidden()
#define pgdat_FavoriteNumber	pgdat->FavoriteNumber()
#define pgdat_IntHbbTvOption	pgdat->IntHbbTvOption()
#define pgdat_BoolChannelLock	pgdat->BoolChannelLock()
#define pgdat_StringTxtPages	pgdat->StringTxtPages()
#define pgdat_IntLogoURL	pgdat->IntLogoURL()
#define pgdat_BoolMatchBrandFlag	pgdat->BoolMatchBrandFlag()
#define pgdat_Nat32NumBrandIds	pgdat->Nat32NumBrandIds()
#define pgdat_StringBrandIds	pgdat->StringBrandIds()
#define pgdat_Nat64UniqueNodeId	pgdat->Nat64UniqueNodeId()
#define pgdat_BoolUserModifiedLogo	pgdat->BoolUserModifiedLogo()
#define pgdat_Nat32TPID	pgdat->Nat32TPID()
#define pgdat_IntLnbNumber	IHsvProgramData3_IntLnbNumber
#define pgdat_IntPolarization	IHsvProgramData3_IntPolarization
#define pgdat_IntSatelliteId	pgdat->IntSatelliteId()
#define pgdat_IntInstalledSatelliteId	pgdat->IntInstalledSatelliteId()
#define pgdat_IntPackageGroup	pgdat->IntPackageGroup()
#define pgdat_IntDpTsid	pgdat->IntDpTsid()
#define pgdat_IntDpServiceId	pgdat->IntDpServiceId()
#define pgdat_MultipleLCN	pgdat->MultipleLCN()
#define pgdat_MultiplePreset	pgdat->MultiplePreset()
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
#define pgdat_GetSatelliteName(LnbNumber,SatelliteName)	pgdat->GetSatelliteName(LnbNumber,SatelliteName)
#define pgdat_GetSatellitePackage(PackageId,PackageIGroupId)	pgdat->GetSatellitePackage(PackageId,PackageIGroupId)
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
#define pgdb_SaveChannelMapsToBackup()  pgdb->SaveChannelMapsToBackup()
#define pgdb_LoadChannelMapsFromBackup pgdb->LoadChannelMapsFromBackup()
#define pgdb_SqliteDatabase		IHsvProgramDatabase_SqliteDatabase
#define pgdb_TempDatabase		IHsvProgramDatabase_TempDatabase
#define pgdb_SelectChannelDatabase(databaseId)		pgdb->SelectChannelDatabase(databaseId)
#define pgdb_SyncDatabase(fromDatabaseId,toDatabaseId)		pgdb->SyncDatabase(fromDatabaseId,toDatabaseId)
#define pgdb_AddInIndex(tableid,index,channeldata)	pgdb->AddInIndex(tableid,index,channeldata)
#define pgdb_BeginSqliteTransaction()		pgdb->BeginSqliteTransaction()
#define pgdb_CommitSqliteTransaction()		pgdb->CommitSqliteTransaction()
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
#define plfres_ConvertStateToResourceid(State)	plfres->ConvertStateToResourceid(State)
#define plfres_RequestResource(resid)	plfres->RequestResource(resid)
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsFransat_mBckgnd_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define s2div_iPresent() (s2div.Present())
#define s2div_iVersion	s2div->iVersion()
#define s2div_IsHomingMuxTuningRequired(SatelliteId,CountryId)	s2div->IsHomingMuxTuningRequired(SatelliteId,CountryId)
#define s2div_LoadDefaultConnectionType(CountryId,ConnectionType)	s2div->LoadDefaultConnectionType(CountryId,ConnectionType)
#define s2div_LoadDefaultLnbType(CountryId,LnbType)	s2div->LoadDefaultLnbType(CountryId,LnbType)
#define s2div_IsBackgroundInstallRequired()	s2div->IsBackgroundInstallRequired()
#define s2div_PerformReinstallInSemiStandby()	s2div->PerformReinstallInSemiStandby()
#define strapi_iPresent() (strapi.Present())
#define strapi_GetSize(dest,spid)	strapi->GetSize(dest,spid)
#define strapi_GetIndex(dest,spid,key1,key2,key3,index)	strapi->GetIndex(dest,spid,key1,key2,key3,index)
#define strapi_GetByKey(dest,spid,key1,key2,key3,val)	strapi->GetByKey(dest,spid,key1,key2,key3,val)
#define strapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	strapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define strapi_GetByIndex(dest,spid,index,val)	strapi->GetByIndex(dest,spid,index,val)
#define bckctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define bckctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define bckctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define bckctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define bckctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define bckctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define bckctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define bckctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define bckctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define bckctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define bckctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define bckctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define bckctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define bckctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define bckctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define bckctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define bckctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define bckctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define bckctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define bckctrlN_FST	IHsvSdmControlNotifyEx_FST
#define sysstateN_RecordingStateChanged	IProdApiSystemStateObserverNotify_RecordingStateChanged
#define sysstateN_MultiviewStateChanged	IProdApiSystemStateObserverNotify_MultiviewStateChanged
#define sysstateN_DisabledEventsStateChanged	IProdApiSystemStateObserverNotify_DisabledEventsStateChanged
#define sysstateN_TimeshiftStateChanged	IProdApiSystemStateObserverNotify_TimeshiftStateChanged
#define sysstateN_SkypeStateChanged	IProdApiSystemStateObserverNotify_SkypeStateChanged
#define sysstateN_TopmenubarStateChanged	IProdApiSystemStateObserverNotify_TopmenubarStateChanged
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
#include "locals_mBckgnd.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

