#ifndef  _CHSVDVBSINSTALLATION_MREMOVESAT_PRIV_H
#define  _CHSVDVBSINSTALLATION_MREMOVESAT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_mremovesat_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_mremovesat_Priv::
#include "locals_mremovesat.h"

class CHsvDvbsInstallation_mremovesat_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_mremovesat_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mremovesat.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSatelliteInstallationImpl(CHsvDvbsInstallation_mremovesat_Priv,iaddremove);
IHsvPowerImpl(CHsvDvbsInstallation_mremovesat_Priv,iremovesatpow);
public:
ProvidesInterface<IHsvSatelliteInstallation>	iaddremove;

ProvidesInterface<IHsvPower>	iremovesatpow;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IPumpExSub>	pmp;
private:
Pumpdefines(CHsvDvbsInstallation_mremovesat_Priv);

public:
CHsvDvbsInstallation_mremovesat_Priv():i__iaddremove(this),i__iremovesatpow(this)
{
iaddremove	=	&i__iaddremove;
iremovesatpow	=	&i__iremovesatpow;
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
#define idvbset_iPresent() (idvbset.Present())
#define idvbset_AttributePackageId	IHsvSatelliteSettings_AttributePackageId
#define idvbset_AttributePackageOnly	IHsvSatelliteSettings_AttributePackageOnly
#define idvbset_AttributeAssetManager	IHsvSatelliteSettings_AttributeAssetManager
#define idvbset_LoadLnbParametersFromPersistent()	idvbset->LoadLnbParametersFromPersistent()
#define idvbset_GetLnbSettings(LnbSettings)	idvbset->GetLnbSettings(LnbSettings)
#define idvbset_SetLnbSettings(LnbSettings)	idvbset->SetLnbSettings(LnbSettings)
#define idvbset_ResetLnbSettings()	idvbset->ResetLnbSettings()
#define idvbset_GetDefaultValues(LnbSettingsEntry)	idvbset->GetDefaultValues(LnbSettingsEntry)
#define idvbset_ResetToDefaultLnbSettings()	idvbset->ResetToDefaultLnbSettings()
#define idvbset_GetAttribute(AttributeId)	idvbset->GetAttribute(AttributeId)
#define idvbset_SetAttribute(AttributeId,Value)	idvbset->SetAttribute(AttributeId,Value)
#define idvbset_SaveSatelliteSettingsToPersistent()	idvbset->SaveSatelliteSettingsToPersistent()
#define idvbset_CommitSatelliteSettingsToPersistent()	idvbset->CommitSatelliteSettingsToPersistent()
#define idvbset_ReLoadLnbParametersFromPersistent()	idvbset->ReLoadLnbParametersFromPersistent()
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
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
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
#define pins_iPresent() (pins.Present())
#define pins_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define pins_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define pins_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define pins_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define pins_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define pins_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define pins_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define pins_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define pins_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define pins_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define pins_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define pins_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define pins_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define pins_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define pins_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define pins_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define pins_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define pins_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define pins_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define pins_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define pins_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define pins_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define pins_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define pins_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define pins_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define pins_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define pins_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define pins_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define pins_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define pins_GetCurrentInstallationState(mode,state)	pins->GetCurrentInstallationState(mode,state)
#define pins_StartInstallation(Source,Lnb,Mode)	pins->StartInstallation(Source,Lnb,Mode)
#define pins_StopInstallation()	pins->StopInstallation()
#define pins_ResetInstallation()	pins->ResetInstallation()
#define pins_GetNumberOfTvChannelsFound(Lnb)	pins->GetNumberOfTvChannelsFound(Lnb)
#define pins_GetNumberofRadioChannelsFound(Lnb)	pins->GetNumberofRadioChannelsFound(Lnb)
#define pins_GetNumberOfTvChannelsRemoved(Lnb)	pins->GetNumberOfTvChannelsRemoved(Lnb)
#define pins_GetNumberofRadioChannelsRemoved(Lnb)	pins->GetNumberofRadioChannelsRemoved(Lnb)
#define pins_GetSatelliteName(Lnb,SatelliteName)	pins->GetSatelliteName(Lnb,SatelliteName)
#define pins_GetNumberOfDigitalChannelsAdded()	pins->GetNumberOfDigitalChannelsAdded()
#define pins_GetNumberOfDigitalChannelsRemoved()	pins->GetNumberOfDigitalChannelsRemoved()
#define pins_GetNumberOfDigitalChannelsMoved()	pins->GetNumberOfDigitalChannelsMoved()
#define pins_IdentifyPackagesAvailable()	pins->IdentifyPackagesAvailable()
#define pins_GetTotalNumberOfPackagesFound()	pins->GetTotalNumberOfPackagesFound()
#define pins_GetPackageByIndex(Index,Package)	pins->GetPackageByIndex(Index,Package)
#define pins_SetUserPackageIndex(PackageIndex)	pins->SetUserPackageIndex(PackageIndex)
#define pins_GetUserPackageIndex(PackageIndex,IsPackage)	pins->GetUserPackageIndex(PackageIndex,IsPackage)
#define pins_GetInstalledSatellites(mode,SatelliteEntries)	pins->GetInstalledSatellites(mode,SatelliteEntries)
#define pins_InstallAddedSatellites()	pins->InstallAddedSatellites()
#define pins_ResetAddedSatellites()	pins->ResetAddedSatellites()
#define pins_RemoveSatelliteEntry(LnbNumber)	pins->RemoveSatelliteEntry(LnbNumber)
#define pins_GetSatelliteSignalStrength(LnbNumber)	pins->GetSatelliteSignalStrength(LnbNumber)
#define pins_GetSatelliteSignalQuality(LnbNumber)	pins->GetSatelliteSignalQuality(LnbNumber)
#define pins_LoadManualInstallationDefaultValues()	pins->LoadManualInstallationDefaultValues()
#define pins_StoreManualInstallationValues()	pins->StoreManualInstallationValues()
#define pins_GetAttribute(Mode,AttributeId)	pins->GetAttribute(Mode,AttributeId)
#define pins_SetAttribute(Mode,AttributeId,Value)	pins->SetAttribute(Mode,AttributeId,Value)
#define pins_GetScanProgressStatus(Mode)	pins->GetScanProgressStatus(Mode)
#define pins_GetSITableIds(NetworkID,BouquetID)	pins->GetSITableIds(NetworkID,BouquetID)
#define pins_GetPackageName(PackageId,PackageName)	pins->GetPackageName(PackageId,PackageName)
#define pins_GetSIDetails(SiValues)	pins->GetSIDetails(SiValues)
#define pins_EnableUnicable(LnbNumber,Enable)	pins->EnableUnicable(LnbNumber,Enable)
#define pins_StopSignalStrengthMeas(LnbNumber)	pins->StopSignalStrengthMeas(LnbNumber)
#define pins_GetSignalQuality(Param)	pins->GetSignalQuality(Param)
#define pins_StartSignalStrengthMeas(LnbNumber)	pins->StartSignalStrengthMeas(LnbNumber)
#define pins_GetSignalStrength(param)	pins->GetSignalStrength(param)
#define pins_StartPredefinedListCopy()	pins->StartPredefinedListCopy()
#define pins_GetFirstInstalledChannel()	pins->GetFirstInstalledChannel()
#define pins_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	pins->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsInstallation_mremovesat_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define iaddremove_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define iaddremove_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define iaddremove_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define iaddremove_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define iaddremove_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define iaddremove_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define iaddremove_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define iaddremove_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define iaddremove_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define iaddremove_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define iaddremove_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define iaddremove_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define iaddremove_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define iaddremove_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define iaddremove_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define iaddremove_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define iaddremove_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define iaddremove_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define iaddremove_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define iaddremove_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define iaddremove_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define iaddremove_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define iaddremove_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define iaddremove_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define iaddremove_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define iaddremove_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define iaddremove_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define iaddremove_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define iaddremove_SatLnb4	IHsvSatelliteInstallation_SatLnb4
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
#include "locals_mremovesat.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

