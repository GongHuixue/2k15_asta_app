#ifndef  _CHSVDVBSINSTALLATION_MUTIL_PRIV_H
#define  _CHSVDVBSINSTALLATION_MUTIL_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_mutil_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_mutil_Priv::
#include "locals_mutil.h"

class CHsvDvbsInstallation_mutil_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_mutil_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mutil.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSatelliteUtilityImpl(CHsvDvbsInstallation_mutil_Priv,iutil);
public:
ProvidesInterface<IHsvSatelliteUtility>	iutil;

//Required interfaces
public:
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;

public:
CHsvDvbsInstallation_mutil_Priv():i__iutil(this)
{
iutil	=	&i__iutil;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#include "locals_mutil.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

