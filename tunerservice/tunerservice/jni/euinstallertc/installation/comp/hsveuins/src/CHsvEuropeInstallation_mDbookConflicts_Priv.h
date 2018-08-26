#ifndef  _CHSVEUROPEINSTALLATION_MDBOOKCONFLICTS_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MDBOOKCONFLICTS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvConflicts.h>
#include <IHsvPower.h>
#include <IHsvCountryIds.h>
#include <IHsvPool.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvConflictsNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_mDbookConflicts_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_mDbookConflicts_Priv::
#include "locals_mDbookConflicts.h"

class CHsvEuropeInstallation_mDbookConflicts_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_mDbookConflicts_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mDbookConflicts.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvConflictsImpl(CHsvEuropeInstallation_mDbookConflicts_Priv,idbookconf);
IHsvPowerImpl(CHsvEuropeInstallation_mDbookConflicts_Priv,idbookconpow);
public:
ProvidesInterface<IHsvConflicts>	idbookconf;

ProvidesInterface<IHsvPower>	idbookconpow;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbtins_digacq;
RequiresInterface<IHsvDVBSettings>	hsvdvbtins_dvbset;
RequiresInterface<IHsvConflictsNotify>	idbookconfN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
private:
Pumpdefines(CHsvEuropeInstallation_mDbookConflicts_Priv);

public:
CHsvEuropeInstallation_mDbookConflicts_Priv():i__idbookconf(this),i__idbookconpow(this)
{
idbookconf	=	&i__idbookconf;
idbookconpow	=	&i__idbookconpow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define cids_iPresent() (cids.Present())
#define cids_CountryAustria	IHsvCountryIds_CountryAustria
#define cids_CountryBelgium	IHsvCountryIds_CountryBelgium
#define cids_CountryCroatia	IHsvCountryIds_CountryCroatia
#define cids_CountryCzechrep	IHsvCountryIds_CountryCzechrep
#define cids_CountryDenmark	IHsvCountryIds_CountryDenmark
#define cids_CountryFinland	IHsvCountryIds_CountryFinland
#define cids_CountryFrance	IHsvCountryIds_CountryFrance
#define cids_CountryGermany	IHsvCountryIds_CountryGermany
#define cids_CountryGreece	IHsvCountryIds_CountryGreece
#define cids_CountryHungary	IHsvCountryIds_CountryHungary
#define cids_CountryIreland	IHsvCountryIds_CountryIreland
#define cids_CountryItaly	IHsvCountryIds_CountryItaly
#define cids_CountryLuxembourg	IHsvCountryIds_CountryLuxembourg
#define cids_CountryNetherlands	IHsvCountryIds_CountryNetherlands
#define cids_CountryNorway	IHsvCountryIds_CountryNorway
#define cids_CountryPoland	IHsvCountryIds_CountryPoland
#define cids_CountryPortugal	IHsvCountryIds_CountryPortugal
#define cids_CountryRomania	IHsvCountryIds_CountryRomania
#define cids_CountryRussia	IHsvCountryIds_CountryRussia
#define cids_CountrySerbia	IHsvCountryIds_CountrySerbia
#define cids_CountrySlovakia	IHsvCountryIds_CountrySlovakia
#define cids_CountrySlovenia	IHsvCountryIds_CountrySlovenia
#define cids_CountrySpain	IHsvCountryIds_CountrySpain
#define cids_CountrySweden	IHsvCountryIds_CountrySweden
#define cids_CountrySwitzerland	IHsvCountryIds_CountrySwitzerland
#define cids_CountryTurkey	IHsvCountryIds_CountryTurkey
#define cids_CountryUK	IHsvCountryIds_CountryUK
#define cids_CountryOther	IHsvCountryIds_CountryOther
#define cids_CountryAustralia	IHsvCountryIds_CountryAustralia
#define cids_CountryEstonia	IHsvCountryIds_CountryEstonia
#define cids_CountryLithuania	IHsvCountryIds_CountryLithuania
#define cids_CountryLatvia	IHsvCountryIds_CountryLatvia
#define cids_CountryKazakhstan	IHsvCountryIds_CountryKazakhstan
#define cids_CountryBulgaria	IHsvCountryIds_CountryBulgaria
#define cids_CountryChina	IHsvCountryIds_CountryChina
#define cids_CountryUkraine	IHsvCountryIds_CountryUkraine
#define cids_CountryBrazil	IHsvCountryIds_CountryBrazil
#define cids_CountryArgentina	IHsvCountryIds_CountryArgentina
#define cids_CountryAlbania	IHsvCountryIds_CountryAlbania
#define cids_CountryArmenia	IHsvCountryIds_CountryArmenia
#define cids_CountryAzerbaijan	IHsvCountryIds_CountryAzerbaijan
#define cids_CountryBelarus	IHsvCountryIds_CountryBelarus
#define cids_CountryBosniaAndHerzegovina	IHsvCountryIds_CountryBosniaAndHerzegovina
#define cids_CountryGeorgia	IHsvCountryIds_CountryGeorgia
#define cids_CountryMontenegro	IHsvCountryIds_CountryMontenegro
#define cids_CountryIsrael	IHsvCountryIds_CountryIsrael
#define cids_CountryMacedoniafyrom	IHsvCountryIds_CountryMacedoniafyrom
#define cids_CountryMax	IHsvCountryIds_CountryMax
#define hpool_iPresent() (hpool.Present())
#define hpool_MemLocalDma	IHsvPool_MemLocalDma
#define hpool_MemLocal	IHsvPool_MemLocal
#define hpool_MemShared	IHsvPool_MemShared
#define hpool_MemLocalNoFatal	IHsvPool_MemLocalNoFatal
#define hpool_Create(memtype,buflen,name)	hpool->Create(memtype,buflen,name)
#define hpool_Malloc(poolid,size)	hpool->Malloc(poolid,size)
#define hpool_Realloc(poolid,ptr,size)	hpool->Realloc(poolid,ptr,size)
#define hpool_Free(poolid,ptr)	hpool->Free(poolid,ptr)
#define hpool_Destroy(poolid)	hpool->Destroy(poolid)
#define hpool_GetMaxFree(poolid)	hpool->GetMaxFree(poolid)
#define hsvdvbtins_digacq_iPresent() (hsvdvbtins_digacq.Present())
#define hsvdvbtins_digacq_Initialise()	hsvdvbtins_digacq->Initialise()
#define hsvdvbtins_digacq_InitialiseTotalChannels()	hsvdvbtins_digacq->InitialiseTotalChannels()
#define hsvdvbtins_digacq_AcquireData()	hsvdvbtins_digacq->AcquireData()
#define hsvdvbtins_digacq_GetNumberOfDigitalChannelsFound()	hsvdvbtins_digacq->GetNumberOfDigitalChannelsFound()
#define hsvdvbtins_digacq_GetNumberOfDigitalChannelsRemoved()	hsvdvbtins_digacq->GetNumberOfDigitalChannelsRemoved()
#define hsvdvbtins_digacq_GetNumberOfChannels(servicetype)	hsvdvbtins_digacq->GetNumberOfChannels(servicetype)
#define hsvdvbtins_digacq_GetNextSampleProgram()	hsvdvbtins_digacq->GetNextSampleProgram()
#define hsvdvbtins_digacq_AcquireLCNData()	hsvdvbtins_digacq->AcquireLCNData()
#define hsvdvbtins_digacq_AcquireServiceListData()	hsvdvbtins_digacq->AcquireServiceListData()
#define hsvdvbtins_digacq_StartBackgroundInstall()	hsvdvbtins_digacq->StartBackgroundInstall()
#define hsvdvbtins_digacq_ResetBackgroundInstall()	hsvdvbtins_digacq->ResetBackgroundInstall()
#define hsvdvbtins_digacq_IsNetworkUpdateDetected()	hsvdvbtins_digacq->IsNetworkUpdateDetected()
#define hsvdvbtins_digacq_DeleteServices()	hsvdvbtins_digacq->DeleteServices()
#define hsvdvbtins_digacq_GetNetworkIDList()	hsvdvbtins_digacq->GetNetworkIDList()
#define hsvdvbtins_digacq_GetNetworkIDName(index,NetworkName)	hsvdvbtins_digacq->GetNetworkIDName(index,NetworkName)
#define hsvdvbtins_digacq_SetFavouriteNetworkID(mode,attrib,index)	hsvdvbtins_digacq->SetFavouriteNetworkID(mode,attrib,index)
#define hsvdvbtins_digacq_ClearNetworkNameCache()	hsvdvbtins_digacq->ClearNetworkNameCache()
#define hsvdvbtins_digacq_IsLCNValid()	hsvdvbtins_digacq->IsLCNValid()
#define hsvdvbtins_digacq_AcquireONID()	hsvdvbtins_digacq->AcquireONID()
#define hsvdvbtins_digacq_SyncTemporaryTableRecords()	hsvdvbtins_digacq->SyncTemporaryTableRecords()
#define hsvdvbtins_digacq_ClearCache()	hsvdvbtins_digacq->ClearCache()
#define hsvdvbtins_digacq_GetRegionList(RegionsData)	hsvdvbtins_digacq->GetRegionList(RegionsData)
#define hsvdvbtins_digacq_SetFavouriteRegion(mode,index,RegionType)	hsvdvbtins_digacq->SetFavouriteRegion(mode,index,RegionType)
#define hsvdvbtins_digacq_GetFavouriteRegion(mode,RegionType)	hsvdvbtins_digacq->GetFavouriteRegion(mode,RegionType)
#define hsvdvbtins_digacq_Enable()	hsvdvbtins_digacq->Enable()
#define hsvdvbtins_digacq_Disable()	hsvdvbtins_digacq->Disable()
#define hsvdvbtins_digacq_GetCachedRegionDetails(RegionCache)	hsvdvbtins_digacq->GetCachedRegionDetails(RegionCache)
#define hsvdvbtins_digacq_UpdateBarkerMuxInfo(onid,tsid)	hsvdvbtins_digacq->UpdateBarkerMuxInfo(onid,tsid)
#define hsvdvbtins_dvbset_iPresent() (hsvdvbtins_dvbset.Present())
#define hsvdvbtins_dvbset_SetAttribute(installationmode,attribute,value)	hsvdvbtins_dvbset->SetAttribute(installationmode,attribute,value)
#define hsvdvbtins_dvbset_GetAttribute(installationmode,attribute)	hsvdvbtins_dvbset->GetAttribute(installationmode,attribute)
#define hsvdvbtins_dvbset_ResetAttributeToDefault(installationmode,attribute)	hsvdvbtins_dvbset->ResetAttributeToDefault(installationmode,attribute)
#define hsvdvbtins_dvbset_ResetAttributeToPersistent(installationmode,attribute)	hsvdvbtins_dvbset->ResetAttributeToPersistent(installationmode,attribute)
#define hsvdvbtins_dvbset_ResetAllToDefault()	hsvdvbtins_dvbset->ResetAllToDefault()
#define hsvdvbtins_dvbset_ResetAllToPersistent()	hsvdvbtins_dvbset->ResetAllToPersistent()
#define hsvdvbtins_dvbset_GetAttributeLength(installationmode,attribute)	hsvdvbtins_dvbset->GetAttributeLength(installationmode,attribute)
#define hsvdvbtins_dvbset_GetNextAttributeValue(installationmode,attribute,value)	hsvdvbtins_dvbset->GetNextAttributeValue(installationmode,attribute,value)
#define hsvdvbtins_dvbset_SetPreferred(attribute,value,preferred)	hsvdvbtins_dvbset->SetPreferred(attribute,value,preferred)
#define hsvdvbtins_dvbset_GetAttributeRange(installationmode,attribute,minValue,maxValue)	hsvdvbtins_dvbset->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define hsvdvbtins_dvbset_GetAttributeMode(installationmode,attribute)	hsvdvbtins_dvbset->GetAttributeMode(installationmode,attribute)
#define hsvdvbtins_dvbset_SetAttributeMode(installationmode,attribute,attributeMode)	hsvdvbtins_dvbset->SetAttributeMode(installationmode,attribute,attributeMode)
#define hsvdvbtins_dvbset_CopyTemporaryToPersistent()	hsvdvbtins_dvbset->CopyTemporaryToPersistent()
#define hsvdvbtins_dvbset_ClearPersistent()	hsvdvbtins_dvbset->ClearPersistent()
#define hsvdvbtins_dvbset_CommitPreferred()	hsvdvbtins_dvbset->CommitPreferred()
#define hsvdvbtins_dvbset_IsAvailable(installationmode,attribute)	hsvdvbtins_dvbset->IsAvailable(installationmode,attribute)
#define hsvdvbtins_dvbset_SetUserSymbolRates(installationmode,values,len)	hsvdvbtins_dvbset->SetUserSymbolRates(installationmode,values,len)
#define hsvdvbtins_dvbset_GetUserSymbolRates(installationmode,values,len)	hsvdvbtins_dvbset->GetUserSymbolRates(installationmode,values,len)
#define hsvdvbtins_dvbset_GetPredefinedSymbolRates(installationmode,values,len)	hsvdvbtins_dvbset->GetPredefinedSymbolRates(installationmode,values,len)
#define hsvdvbtins_dvbset_ClearUserSymbolRates()	hsvdvbtins_dvbset->ClearUserSymbolRates()
#define hsvdvbtins_dvbset_GetONIDNetworkOperator(ONID)	hsvdvbtins_dvbset->GetONIDNetworkOperator(ONID)
#define idbookconfN_iPresent() (idbookconfN.Present())
#define idbookconfN_ConflictsResolved	IHsvConflictsNotify_ConflictsResolved
#define idbookconfN_ConflictsNotResolved	IHsvConflictsNotify_ConflictsNotResolved
#define idbookconfN_OnEvent(ConflictsResolutionStatus)	idbookconfN->OnEvent(ConflictsResolutionStatus)
#define idbookconfN_OnConflictsDetected()	idbookconfN->OnConflictsDetected()
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvEuropeInstallation_mDbookConflicts_Priv::func,replace,(char *)name,this)
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
#define sysset_iPresent() (sysset.Present())
#define sysset_AudioFormatStandard	IHsvTcSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvTcSystemSettings_AudioFormatAdvanced
#define sysset_SetSystemLanguage(lang)	sysset->SetSystemLanguage(lang)
#define sysset_GetSystemLanguage()	sysset->GetSystemLanguage()
#define sysset_SetPreferredPrimaryAudioLanguage(lang)	sysset->SetPreferredPrimaryAudioLanguage(lang)
#define sysset_GetPreferredPrimaryAudioLanguage()	sysset->GetPreferredPrimaryAudioLanguage()
#define sysset_GetPreferredSecondarySubtitleLanguage()	sysset->GetPreferredSecondarySubtitleLanguage()
#define sysset_SetPreferredSecondarySubtitleLanguage(lang)	sysset->SetPreferredSecondarySubtitleLanguage(lang)
#define sysset_GetPreferredSecondaryAudioLanguage()	sysset->GetPreferredSecondaryAudioLanguage()
#define sysset_SetPreferredSecondaryAudioLanguage(lang)	sysset->SetPreferredSecondaryAudioLanguage(lang)
#define sysset_SetPreferredPrimarySubtitleLanguage(lang)	sysset->SetPreferredPrimarySubtitleLanguage(lang)
#define sysset_GetPreferredPrimarySubtitleLanguage()	sysset->GetPreferredPrimarySubtitleLanguage()
#define sysset_SetPreferredAudioFormat(format)	sysset->SetPreferredAudioFormat(format)
#define sysset_GetPreferredAudioFormat()	sysset->GetPreferredAudioFormat()
#define sysset_SetPreferredPrimaryTxtLanguage(lang)	sysset->SetPreferredPrimaryTxtLanguage(lang)
#define sysset_GetPreferredPrimaryTxtLanguage()	sysset->GetPreferredPrimaryTxtLanguage()
#define sysset_SetPreferredSecondaryTxtLanguage(lang)	sysset->SetPreferredSecondaryTxtLanguage(lang)
#define sysset_GetPreferredSecondaryTxtLanguage()	sysset->GetPreferredSecondaryTxtLanguage()
#define sysset_SetSystemCountry(country)	sysset->SetSystemCountry(country)
#define sysset_GetSystemCountry()	sysset->GetSystemCountry()
#define sysset_SetInstallCountry(country)	sysset->SetInstallCountry(country)
#define sysset_GetInstallCountry()	sysset->GetInstallCountry()
#define sysset_SetInstallCity(city)	sysset->SetInstallCity(city)
#define sysset_SetSystemCity(city)	sysset->SetSystemCity(city)
#define sysset_GetInstallCity()	sysset->GetInstallCity()
#define sysset_GetSystemCity()	sysset->GetSystemCity()
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
#include "locals_mDbookConflicts.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

