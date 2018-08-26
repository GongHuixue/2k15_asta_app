#ifndef  _CHSVPROGRAMDATA_MPGDAT_PRIV_H
#define  _CHSVPROGRAMDATA_MPGDAT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvProgramData.h>
#include <IHsvProgramData3.h>
#include <IHsvChannelMapOperation.h>
#include <IHsvProgramDataDiv.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IAppApiChannelLibNvmIds.h>
#include <IProdApiNvmProtectedAccessExEx.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvProgramDataNotifyExEx.h>
#include <IHsvProgramDataNotifyExExEx.h>
#include <IProdApiNvmSubIdsEx.h>
#include <IHsvChannelLibSyncEvents.h>
#include <CTCMwBase.h>
class CHsvProgramData_mpgdat_Priv;
#define CLASSSCOPE CHsvProgramData_mpgdat_Priv::
#include "locals_mpgdat.h"

class CHsvProgramData_mpgdat_Priv : public CTCMwBase
{
public:
virtual ~CHsvProgramData_mpgdat_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpgdat.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvProgramData_mpgdat_Priv,ipgdatpow);
IHsvProgramDataImpl(CHsvProgramData_mpgdat_Priv,pgdat);
IHsvProgramData3Impl(CHsvProgramData_mpgdat_Priv,pgdat3);
public:
ProvidesInterface<IHsvPower>	ipgdatpow;

ProvidesInterface<IHsvProgramData>	pgdat;

ProvidesInterface<IHsvProgramData3>	pgdat3;

//Required interfaces
public:
RequiresInterface<IHsvChannelMapOperation>	chmapop;
RequiresInterface<IHsvProgramDataDiv>	div;
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IHsvProgramDatabase>	ipgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	ipgdbconst;
RequiresInterface<IAppApiChannelLibNvmIds>	nvmids;
RequiresInterface<IProdApiNvmProtectedAccessExEx>	nvmpa;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvProgramDataNotifyExEx>	pgdatNxx;
RequiresInterface<IHsvProgramDataNotifyExExEx>	pgdatNxxx;
RequiresInterface<IProdApiNvmSubIdsEx>	subid;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;

public:
CHsvProgramData_mpgdat_Priv():i__ipgdatpow(this),i__pgdat(this),i__pgdat3(this)
{
ipgdatpow	=	&i__ipgdatpow;
pgdat	=	&i__pgdat;
pgdat3	=	&i__pgdat3;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define chmapop_iPresent() (chmapop.Present())
#define chmapop_Lock()	chmapop->Lock()
#define chmapop_UnLock()	chmapop->UnLock()
#define chmapop_ReloadFromFlash(tableid)	chmapop->ReloadFromFlash(tableid)
#define chmapop_CommitToFlash(tableid)	chmapop->CommitToFlash(tableid)
#define chmapop_LoadChannelTable(tableid,dir)	chmapop->LoadChannelTable(tableid,dir)
#define chmapop_SaveChannelTable(tableid,dir)	chmapop->SaveChannelTable(tableid,dir)
#define chmapop_SetDirtyBit()	chmapop->SetDirtyBit()
#define chmapop_EnableAutoCommit(enable)	chmapop->EnableAutoCommit(enable)
#define chmapop_ChannelTableChanged()	chmapop->ChannelTableChanged()
#define chmapop_LoadChannelExternal(dir)	chmapop->LoadChannelExternal(dir)
#define chmapop_SaveChannelExternal(dir)	chmapop->SaveChannelExternal(dir)
#define chmapop_GetMediumFromTable(dir,medium)	chmapop->GetMediumFromTable(dir,medium)
#define div_iPresent() (div.Present())
#define div_DefaultSystemLanguage	div->DefaultSystemLanguage()
#define div_OobSupported	div->OobSupported()
#define div_NoOfMinorChannelsToStoreAntenna	div->NoOfMinorChannelsToStoreAntenna()
#define div_NoOfMinorChannelsToStoreCable	div->NoOfMinorChannelsToStoreCable()
#define div_MaxNoOfChannelsToStoreAntenna	div->MaxNoOfChannelsToStoreAntenna()
#define div_MaxNoOfChannelsToStoreCable	div->MaxNoOfChannelsToStoreCable()
#define div_MaxNoOfPrograms	div->MaxNoOfPrograms()
#define div_PersistentMemoryFileVersion	div->PersistentMemoryFileVersion()
#define div_DefaultTunerPresetFrequency	div->DefaultTunerPresetFrequency()
#define div_HsvAntennaMajorTable	div->HsvAntennaMajorTable()
#define div_HsvAntennaPtcTable	div->HsvAntennaPtcTable()
#define div_HsvCableMajorTable	div->HsvCableMajorTable()
#define div_HsvCablePtcTable	div->HsvCablePtcTable()
#define div_HsvOobMajorTable	div->HsvOobMajorTable()
#define div_HsvOobPtcTable	div->HsvOobPtcTable()
#define div_PersistentMemUpdateTimeout	div->PersistentMemUpdateTimeout()
#define div_CookieDefaultValue	div->CookieDefaultValue()
#define div_EpgCookieDefaultValue	div->EpgCookieDefaultValue()
#define div_TxtCookieDefaultValue	div->TxtCookieDefaultValue()
#define div_AppsCookieDefaultValue	div->AppsCookieDefaultValue()
#define div_ProgramViewForUS	div->ProgramViewForUS()
#define div_ChannelNameLength	div->ChannelNameLength()
#define div_HsvAntennaAnalogTable	div->HsvAntennaAnalogTable()
#define div_HsvAntennaDigSrvcTable	div->HsvAntennaDigSrvcTable()
#define div_HsvAntennaDigPtcTable	div->HsvAntennaDigPtcTable()
#define div_HsvAntennaFreqMapTable	div->HsvAntennaFreqMapTable()
#define div_HsvCableAnalogTable	div->HsvCableAnalogTable()
#define div_HsvCableDigSrvcTable	div->HsvCableDigSrvcTable()
#define div_HsvCableDigPtcTable	div->HsvCableDigPtcTable()
#define div_HsvCableFreqMapTable	div->HsvCableFreqMapTable()
#define div_MaxNoOfChannelsToStoreAntennaUserTable	div->MaxNoOfChannelsToStoreAntennaUserTable()
#define div_MaxNoOfChannelsToStoreAntennaDigSrvcTable	div->MaxNoOfChannelsToStoreAntennaDigSrvcTable()
#define div_MaxNoOfChannelsToStoreAntennaDigTSTable	div->MaxNoOfChannelsToStoreAntennaDigTSTable()
#define div_MaxNoOfChannelsToStoreAntennaDigPtcTable	div->MaxNoOfChannelsToStoreAntennaDigPtcTable()
#define div_MaxNoOfChannelsToStoreAntennaAnalogTable	div->MaxNoOfChannelsToStoreAntennaAnalogTable()
#define div_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	div->MaxNoOfMultiplexsToStoreAntennaFreqMapTable()
#define div_MaxNoOfChannelsToStoreCableUserTable	div->MaxNoOfChannelsToStoreCableUserTable()
#define div_MaxNoOfChannelsToStoreCableDigSrvcTable	div->MaxNoOfChannelsToStoreCableDigSrvcTable()
#define div_MaxNoOfChannelsToStoreCableDigTSTable	div->MaxNoOfChannelsToStoreCableDigTSTable()
#define div_MaxNoOfChannelsToStoreCableDigPtcTable	div->MaxNoOfChannelsToStoreCableDigPtcTable()
#define div_MaxNoOfChannelsToStoreCableAnalogTable	div->MaxNoOfChannelsToStoreCableAnalogTable()
#define div_MaxNoOfMultiplexsToStoreCableFreqMapTable	div->MaxNoOfMultiplexsToStoreCableFreqMapTable()
#define div_AnalogOnly	div->AnalogOnly()
#define div_InstallDuplicateTsids(medium)	div->InstallDuplicateTsids(medium)
#define div_PrimaryFileVersion	div->PrimaryFileVersion()
#define div_SecondaryFileVersion	div->SecondaryFileVersion()
#define div_ChannelListVariant	div->ChannelListVariant()
#define div_DefaultChannelList	IHsvProgramDataDiv_DefaultChannelList
#define div_DualChannelList	IHsvProgramDataDiv_DualChannelList
#define div_TripleChannelList	IHsvProgramDataDiv_TripleChannelList
#define div_ChannelNameSource	div->ChannelNameSource()
#define div_TripletKey(medium)	div->TripletKey(medium)
#define div_ExtendedName	IHsvProgramDataDiv_ExtendedName
#define div_ShortName	IHsvProgramDataDiv_ShortName
#define div_Default	IHsvProgramDataDiv_Default
#define div_UpdateChannelName(medium)	div->UpdateChannelName(medium)
#define err_iPresent() (err.Present())
#define err_Ok	IHsvChannelLibReturnCodes_Ok
#define err_BadParameter	IHsvChannelLibReturnCodes_BadParameter
#define err_ChannelTableEmpty	IHsvChannelLibReturnCodes_ChannelTableEmpty
#define err_ChannelTableExhausted	IHsvChannelLibReturnCodes_ChannelTableExhausted
#define err_MinorNumbersExhausted	IHsvChannelLibReturnCodes_MinorNumbersExhausted
#define err_NotSupported	IHsvChannelLibReturnCodes_NotSupported
#define err_FileError	IHsvChannelLibReturnCodes_FileError
#define err_ChannelTableVersionError	IHsvChannelLibReturnCodes_ChannelTableVersionError
#define err_ChannelTableCrcError	IHsvChannelLibReturnCodes_ChannelTableCrcError
#define err_ChannelNotInstalled	IHsvChannelLibReturnCodes_ChannelNotInstalled
#define err_NVMError	IHsvChannelLibReturnCodes_NVMError
#define ipgdb_iPresent() (ipgdb.Present())
#define ipgdb_GetCurrentTable()	ipgdb->GetCurrentTable()
#define ipgdb_SelectTable(tableid)	ipgdb->SelectTable(tableid)
#define ipgdb_ClearTable(tableid)	ipgdb->ClearTable(tableid)
#define ipgdb_IsSupported(tableid)	ipgdb->IsSupported(tableid)
#define ipgdb_CommitTable(tableid)	ipgdb->CommitTable(tableid)
#define ipgdb_LoadTable(tableid)	ipgdb->LoadTable(tableid)
#define ipgdb_GetNoRecords(tableid)	ipgdb->GetNoRecords(tableid)
#define ipgdb_GetByKey(tableid,channeldata)	ipgdb->GetByKey(tableid,channeldata)
#define ipgdb_GetIndex(tableid,index,channeldata)	ipgdb->GetIndex(tableid,index,channeldata)
#define ipgdb_GetByIndex(tableid,index,channeldata)	ipgdb->GetByIndex(tableid,index,channeldata)
#define ipgdb_GetRange(tableid,noofkeys,channeldata,from,to)	ipgdb->GetRange(tableid,noofkeys,channeldata,from,to)
#define ipgdb_Add(tableid,channeldata)	ipgdb->Add(tableid,channeldata)
#define ipgdb_Update(tableid,channeldata)	ipgdb->Update(tableid,channeldata)
#define ipgdb_Delete(tableid,channeldata)	ipgdb->Delete(tableid,channeldata)
#define ipgdb_EnableAutoCommit(enable)	ipgdb->EnableAutoCommit(enable)
#define ipgdb_ChannelTableChanged()	ipgdb->ChannelTableChanged()
#define ipgdb_Initialise(tableid,channeldata)	ipgdb->Initialise(tableid,channeldata)
#define ipgdb_MasterEnableEvents(Status)	ipgdb->MasterEnableEvents(Status)
#define ipgdb_SaveChannelMapsToBackup()	ipgdb->SaveChannelMapsToBackup()
#define ipgdb_LoadChannelMapsFromBackup()	ipgdb->LoadChannelMapsFromBackup()
#define	pgdb_SqliteDatabase 	IHsvProgramDatabase_SqliteDatabase
#define	pgdb_TempDatabase 		IHsvProgramDatabase_TempDatabase
#define	pgdb_SelectActiveChannelDatabase(ActiveDb) 		pgdb->SelectActiveChannelDatabase(ActiveDb)
#define	pgdb_AddInIndex(tableid,index,channeldata)		pgdb->AddInIndex(tableid,index,channeldata)
#define	pgdb_BeginSqliteTransaction()					pgdb->BeginSqliteTransaction()
#define	pgdb_CommitSqliteTransaction()					pgdb->CommitSqliteTransaction()
#define ipgdbconst_iPresent() (ipgdbconst.Present())
#define ipgdbconst_Antenna	IHsvProgramDatabaseConstants_Antenna
#define ipgdbconst_Cable	IHsvProgramDatabaseConstants_Cable
#define ipgdbconst_TempAntenna	IHsvProgramDatabaseConstants_TempAntenna
#define ipgdbconst_TempCable	IHsvProgramDatabaseConstants_TempCable
#define ipgdbconst_Satellite	IHsvProgramDatabaseConstants_Satellite
#define ipgdbconst_TempSatellite	IHsvProgramDatabaseConstants_TempSatellite
#define ipgdbconst_Analog	IHsvProgramDatabaseConstants_Analog
#define ipgdbconst_DigitalTS	IHsvProgramDatabaseConstants_DigitalTS
#define ipgdbconst_DigitalService	IHsvProgramDatabaseConstants_DigitalService
#define ipgdbconst_Preset	IHsvProgramDatabaseConstants_Preset
#define ipgdbconst_FrequencyMapTable	IHsvProgramDatabaseConstants_FrequencyMapTable
#define ipgdbconst_CurrentDigitalService	IHsvProgramDatabaseConstants_CurrentDigitalService
#define ipgdbconst_CurrentDigitalTS	IHsvProgramDatabaseConstants_CurrentDigitalTS
#define ipgdbconst_CurrentAnalog	IHsvProgramDatabaseConstants_CurrentAnalog
#define ipgdbconst_CurrentPreset	IHsvProgramDatabaseConstants_CurrentPreset
#define ipgdbconst_CurrentFrequencyMapTable	IHsvProgramDatabaseConstants_CurrentFrequencyMapTable
#define ipgdbconst_SatInfo	IHsvProgramDatabaseConstants_SatInfo
#define ipgdbconst_CurrentSatInfo	IHsvProgramDatabaseConstants_CurrentSatInfo
#define nvmids_iPresent() (nvmids.Present())
#define nvmids_InstSettingsInstallMode	nvmids->InstSettingsInstallMode()
#define nvmids_LastPresetType	nvmids->LastPresetType()
#define nvmids_LastPresetlPtc	nvmids->LastPresetlPtc()
#define nvmids_LastPresetOnePartNo	nvmids->LastPresetOnePartNo()
#define nvmids_LastPresetAnalogNo	nvmids->LastPresetAnalogNo()
#define nvmids_LastPresetDigit	nvmids->LastPresetDigit()
#define nvmids_LastPresetTwoPartMajorNo	nvmids->LastPresetTwoPartMajorNo()
#define nvmids_LastPresetTwoPartMinorNo	nvmids->LastPresetTwoPartMinorNo()
#define nvmids_LastSource	nvmids->LastSource()
#define nvmids_LstStatParentalRatingAge	nvmids->LstStatParentalRatingAge()
#define nvmids_LstStatParentalRatingDrugs	nvmids->LstStatParentalRatingDrugs()
#define nvmids_LstStatParentalRatingViolence	nvmids->LstStatParentalRatingViolence()
#define nvmids_LstStatParentalRatingSex	nvmids->LstStatParentalRatingSex()
#define nvmids_InstSettingsClosedCaptions	nvmids->InstSettingsClosedCaptions()
#define nvmids_InstSettingsSubtitle	nvmids->InstSettingsSubtitle()
#define nvmids_LstStatDVBParentalRating	nvmids->LstStatDVBParentalRating()
#define nvmpa_iPresent() (nvmpa.Present())
#define nvmpa_optTrue	IProdApiNvmProtectedAccessExEx_optTrue
#define nvmpa_optFalse	IProdApiNvmProtectedAccessExEx_optFalse
#define nvmpa_optInvalid	IProdApiNvmProtectedAccessExEx_optInvalid
#define nvmpa_GetBool(nvmid,subid)	nvmpa->GetBool(nvmid,subid)
#define nvmpa_SetBool(nvmid,val,subid)	nvmpa->SetBool(nvmid,val,subid)
#define nvmpa_GetBoolIx(nvmid,ix,subid)	nvmpa->GetBoolIx(nvmid,ix,subid)
#define nvmpa_SetBoolIx(nvmid,ix,val,subid)	nvmpa->SetBoolIx(nvmid,ix,val,subid)
#define nvmpa_GetBoolIxIx(nvmid,ix1,ix2,subid)	nvmpa->GetBoolIxIx(nvmid,ix1,ix2,subid)
#define nvmpa_SetBoolIxIx(nvmid,ix1,ix2,val,subid)	nvmpa->SetBoolIxIx(nvmid,ix1,ix2,val,subid)
#define nvmpa_GetChar(nvmid,subid)	nvmpa->GetChar(nvmid,subid)
#define nvmpa_SetChar(nvmid,val,subid)	nvmpa->SetChar(nvmid,val,subid)
#define nvmpa_GetCharIx(nvmid,ix,subid)	nvmpa->GetCharIx(nvmid,ix,subid)
#define nvmpa_SetCharIx(nvmid,ix,val,subid)	nvmpa->SetCharIx(nvmid,ix,val,subid)
#define nvmpa_GetCharIxIx(nvmid,ix1,ix2,subid)	nvmpa->GetCharIxIx(nvmid,ix1,ix2,subid)
#define nvmpa_SetCharIxIx(nvmid,ix1,ix2,val,subid)	nvmpa->SetCharIxIx(nvmid,ix1,ix2,val,subid)
#define nvmpa_GetInt(nvmid,subid)	nvmpa->GetInt(nvmid,subid)
#define nvmpa_SetInt(nvmid,val,subid)	nvmpa->SetInt(nvmid,val,subid)
#define nvmpa_GetIntIx(nvmid,ix,subid)	nvmpa->GetIntIx(nvmid,ix,subid)
#define nvmpa_SetIntIx(nvmid,ix,val,subid)	nvmpa->SetIntIx(nvmid,ix,val,subid)
#define nvmpa_GetIntIxIx(nvmid,ix1,ix2,subid)	nvmpa->GetIntIxIx(nvmid,ix1,ix2,subid)
#define nvmpa_SetIntIxIx(nvmid,ix1,ix2,val,subid)	nvmpa->SetIntIxIx(nvmid,ix1,ix2,val,subid)
#define nvmpa_GetInt32(nvmid,subid)	nvmpa->GetInt32(nvmid,subid)
#define nvmpa_SetInt32(nvmid,val,subid)	nvmpa->SetInt32(nvmid,val,subid)
#define nvmpa_GetInt32Ix(nvmid,ix,subid)	nvmpa->GetInt32Ix(nvmid,ix,subid)
#define nvmpa_SetInt32Ix(nvmid,ix,val,subid)	nvmpa->SetInt32Ix(nvmid,ix,val,subid)
#define nvmpa_GetInt32IxIx(nvmid,ix1,ix2,subid)	nvmpa->GetInt32IxIx(nvmid,ix1,ix2,subid)
#define nvmpa_SetInt32IxIx(nvmid,ix1,ix2,val,subid)	nvmpa->SetInt32IxIx(nvmid,ix1,ix2,val,subid)
#define nvmpa_LastError()	nvmpa->LastError()
#define nvmpa_GetNat16(nvmid,subid,value)	nvmpa->GetNat16(nvmid,subid,value)
#define nvmpa_SetNat16(nvmid,subid,value)	nvmpa->SetNat16(nvmid,subid,value)
#define nvmpa_InvalidateCache()	nvmpa->InvalidateCache()
#define pgdatN_iPresent() (pgdatN.Present())
#define pgdatN_OnChannelAdded(channel)	pgdatN->OnChannelAdded(channel)
#define pgdatN_OnChannelRemoved(channel)	pgdatN->OnChannelRemoved(channel)
#define pgdatN_OnChannelUpdated(channel,attribute)	pgdatN->OnChannelUpdated(channel,attribute)
#define pgdatN_OnChannelTableReset()	pgdatN->OnChannelTableReset()
#define pgdatN_OnChannelTableChanged()	pgdatN->OnChannelTableChanged()
#define pgdatN_OnChannelsRearranged(channel1,channel2)	pgdatN->OnChannelsRearranged(channel1,channel2)
#define pgdatN_OnChannelTableUpdateStart()	pgdatN->OnChannelTableUpdateStart()
#define pgdatN_OnChannelTableUpdateEnd(Reset)	pgdatN->OnChannelTableUpdateEnd(Reset)
#define pgdatN_OnChannelsSwapped(channel1,channel2)	pgdatN->OnChannelsSwapped(channel1,channel2)
#define pgdatNxx_iPresent() (pgdatNxx.Present())
#define pgdatNxx_MajorChannel	IHsvProgramDataNotifyExEx_MajorChannel
#define pgdatNxx_MinorChannel	IHsvProgramDataNotifyExEx_MinorChannel
#define pgdatNxx_PIDs	IHsvProgramDataNotifyExEx_PIDs
#define pgdatNxx_OnChannelAdded(channel)	pgdatNxx->OnChannelAdded(channel)
#define pgdatNxx_OnChannelRemoved(channel)	pgdatNxx->OnChannelRemoved(channel)
#define pgdatNxx_OnChannelUpdated(channel,attribute)	pgdatNxx->OnChannelUpdated(channel,attribute)
#define pgdatNxx_OnChannelTableReset()	pgdatNxx->OnChannelTableReset()
#define pgdatNxx_OnChannelTableChanged()	pgdatNxx->OnChannelTableChanged()
#define pgdatNxx_OnChannelsRearranged(channel1,channel2)	pgdatNxx->OnChannelsRearranged(channel1,channel2)
#define pgdatNxx_OnChannelTableUpdateStart()	pgdatNxx->OnChannelTableUpdateStart()
#define pgdatNxx_OnChannelTableUpdateEnd(Reset)	pgdatNxx->OnChannelTableUpdateEnd(Reset)
#define pgdatNxx_OnChannelsSwapped(channel1,channel2)	pgdatNxx->OnChannelsSwapped(channel1,channel2)
#define pgdatNxxx_iPresent() (pgdatNxxx.Present())
#define pgdatNxxx_OnChannelAdded(channel)	pgdatNxxx->OnChannelAdded(channel)
#define pgdatNxxx_OnChannelRemoved(channel)	pgdatNxxx->OnChannelRemoved(channel)
#define pgdatNxxx_OnChannelUpdated(channel,attribute)	pgdatNxxx->OnChannelUpdated(channel,attribute)
#define pgdatNxxx_OnChannelTableReset()	pgdatNxxx->OnChannelTableReset()
#define pgdatNxxx_OnChannelTableChanged()	pgdatNxxx->OnChannelTableChanged()
#define pgdatNxxx_OnChannelsRearranged(channel1,channel2)	pgdatNxxx->OnChannelsRearranged(channel1,channel2)
#define pgdatNxxx_OnChannelTableUpdateStart()	pgdatNxxx->OnChannelTableUpdateStart()
#define pgdatNxxx_OnChannelTableUpdateEnd(Reset)	pgdatNxxx->OnChannelTableUpdateEnd(Reset)
#define pgdatNxxx_OnChannelsSwapped(channel1,channel2)	pgdatNxxx->OnChannelsSwapped(channel1,channel2)
#define pgdatNxxx_OnChannelMapLoadComplete(Status)	pgdatNxxx->OnChannelMapLoadComplete(Status)
#define pgdatNxxx_OnChannelMapSaveComplete(Status)	pgdatNxxx->OnChannelMapSaveComplete(Status)
#define subid_iPresent() (subid.Present())
#define subid_Apps	IProdApiNvmSubIdsEx_Apps
#define subid_Txt	IProdApiNvmSubIdsEx_Txt
#define subid_Epg	IProdApiNvmSubIdsEx_Epg
#define subid_Zap	IProdApiNvmSubIdsEx_Zap
#define subid_Dlna	IProdApiNvmSubIdsEx_Dlna
#define subid_Ecd	IProdApiNvmSubIdsEx_Ecd
#define subid_Skype	IProdApiNvmSubIdsEx_Skype
#define subid_Cetv	IProdApiNvmSubIdsEx_Cetv
#define subid_Prod	IProdApiNvmSubIdsEx_Prod
#define subid_Cbmhg	IProdApiNvmSubIdsEx_Cbmhg
#define subid_NetTv	IProdApiNvmSubIdsEx_NetTv
#define subid_Play	IProdApiNvmSubIdsEx_Play
#define subid_Dvbs2	IProdApiNvmSubIdsEx_Dvbs2
#define subid_Eu	IProdApiNvmSubIdsEx_Eu
#define subid_Bra	IProdApiNvmSubIdsEx_Bra
#define subid_Home	IProdApiNvmSubIdsEx_Home
#define subid_Demo	IProdApiNvmSubIdsEx_Demo
#define subid_Upg	IProdApiNvmSubIdsEx_Upg
#define subid_Tv	IProdApiNvmSubIdsEx_Tv
#define subid_Deasvc	IProdApiNvmSubIdsEx_Deasvc
#define subid_Txsvc	IProdApiNvmSubIdsEx_Txsvc
#define subid_Fac	IProdApiNvmSubIdsEx_Fac
#define subid_Tvsvc	IProdApiNvmSubIdsEx_Tvsvc
#define subid_Svpsc	IProdApiNvmSubIdsEx_Svpsc
#define subid_Ceinfra	IProdApiNvmSubIdsEx_Ceinfra
#define subid_Tvint	IProdApiNvmSubIdsEx_Tvint
#define subid_Ols	IProdApiNvmSubIdsEx_Ols
#define subid_Media	IProdApiNvmSubIdsEx_Media
#define subid_NotAllowed	IProdApiNvmSubIdsEx_NotAllowed
#define sync_iPresent() (sync.Present())
#define sync_EnableEvents(Status)	sync->EnableEvents(Status)
#define sync_MasterEnableEvents(Status)	sync->MasterEnableEvents(Status)
#define sync_OnInsert(tableid,data)	sync->OnInsert(tableid,data)
#define sync_OnUpdate(tableid,data)	sync->OnUpdate(tableid,data)
#define sync_OnDelete(tableid,data)	sync->OnDelete(tableid,data)
#define pgdat_BoolLock	i__pgdat.m_BoolLock
#define pgdat_BoolFavorite	i__pgdat.m_BoolFavorite
#define pgdat_BoolFavorite1	i__pgdat.m_BoolFavorite1
#define pgdat_BoolFavorite2	i__pgdat.m_BoolFavorite2
#define pgdat_BoolFavorite3	i__pgdat.m_BoolFavorite3
#define pgdat_BoolPreferredFavorite	i__pgdat.m_BoolPreferredFavorite
#define pgdat_BoolPreferredNicam	i__pgdat.m_BoolPreferredNicam
#define pgdat_BoolPreferredStereo	i__pgdat.m_BoolPreferredStereo
#define pgdat_BoolSAP	i__pgdat.m_BoolSAP
#define pgdat_BoolHMProtectedChannel	i__pgdat.m_BoolHMProtectedChannel
#define pgdat_BoolHMBlanked	i__pgdat.m_BoolHMBlanked
#define pgdat_BoolUserHidden	i__pgdat.m_BoolUserHidden
#define pgdat_BoolSystemHidden	i__pgdat.m_BoolSystemHidden
#define pgdat_BoolNumericSelect	i__pgdat.m_BoolNumericSelect
#define pgdat_BoolEpgChannel	i__pgdat.m_BoolEpgChannel
#define pgdat_BoolEPGShortInfoEnabled	i__pgdat.m_BoolEPGShortInfoEnabled
#define pgdat_BoolNewPreset	i__pgdat.m_BoolNewPreset
#define pgdat_BoolFreeCiMode	i__pgdat.m_BoolFreeCiMode
#define pgdat_BoolTuned	i__pgdat.m_BoolTuned
#define pgdat_BoolDeTuned	i__pgdat.m_BoolDeTuned
#define pgdat_BoolAttenuator	i__pgdat.m_BoolAttenuator
#define pgdat_BoolAgcInstalled	i__pgdat.m_BoolAgcInstalled
#define pgdat_BoolChannelVirgin	i__pgdat.m_BoolChannelVirgin
#define pgdat_BoolUpdateName	i__pgdat.m_BoolUpdateName
#define pgdat_IntDeltaVolume	i__pgdat.m_IntDeltaVolume
#define pgdat_Nat32DateStamp	i__pgdat.m_Nat32DateStamp
#define pgdat_Nat32AppsCookie	i__pgdat.m_Nat32AppsCookie
#define pgdat_Nat32TxtCookie	i__pgdat.m_Nat32TxtCookie
#define pgdat_Nat32CesvcCookie	i__pgdat.m_Nat32CesvcCookie
#define pgdat_Nat32DvbType	i__pgdat.m_Nat32DvbType
#define pgdat_StringChannelName	i__pgdat.m_StringChannelName
#define pgdat_StringExtChannelName	i__pgdat.m_StringExtChannelName
#define pgdat_IntFrequency	i__pgdat.m_IntFrequency
#define pgdat_IntTvSystem	i__pgdat.m_IntTvSystem
#define pgdat_IntModulation	i__pgdat.m_IntModulation
#define pgdat_IntNewChannelMap	i__pgdat.m_IntNewChannelMap
#define pgdat_IntSignalStrength	i__pgdat.m_IntSignalStrength
#define pgdat_IntSignalQuality	i__pgdat.m_IntSignalQuality
#define pgdat_IntColoursystem	i__pgdat.m_IntColoursystem
#define pgdat_IntDecoderType	i__pgdat.m_IntDecoderType
#define pgdat_IntFineTuneOffset	i__pgdat.m_IntFineTuneOffset
#define pgdat_IntFineTuneFrequency	i__pgdat.m_IntFineTuneFrequency
#define pgdat_Nat32SymbolRate	i__pgdat.m_Nat32SymbolRate
#define pgdat_IntNetworkId	i__pgdat.m_IntNetworkId
#define pgdat_IntOriginalNwId	i__pgdat.m_IntOriginalNwId
#define pgdat_IntTsid	i__pgdat.m_IntTsid
#define pgdat_IntServiceId	i__pgdat.m_IntServiceId
#define pgdat_IntServiceType	i__pgdat.m_IntServiceType
#define pgdat_IntPmtPid	i__pgdat.m_IntPmtPid
#define pgdat_IntPcrPid	i__pgdat.m_IntPcrPid
#define pgdat_IntVideoPid	i__pgdat.m_IntVideoPid
#define pgdat_IntVideoStreamType	i__pgdat.m_IntVideoStreamType
#define pgdat_IntAudioPid	i__pgdat.m_IntAudioPid
#define pgdat_IntAudioStreamType	i__pgdat.m_IntAudioStreamType
#define pgdat_IntSecAudioPid	i__pgdat.m_IntSecAudioPid
#define pgdat_IntSecAudioStreamType	i__pgdat.m_IntSecAudioStreamType
#define pgdat_IntInstallMode	i__pgdat.m_IntInstallMode
#define pgdat_IntCniNi	i__pgdat.m_IntCniNi
#define pgdat_IntDataIndicator	i__pgdat.m_IntDataIndicator
#define pgdat_IntPresetNumber	i__pgdat.m_IntPresetNumber
#define pgdat_IntModulationType	i__pgdat.m_IntModulationType
#define pgdat_IntLCN	i__pgdat.m_IntLCN
#define pgdat_IntStreamPriority	i__pgdat.m_IntStreamPriority
#define pgdat_IntHMMapChannelNo	i__pgdat.m_IntHMMapChannelNo
#define pgdat_IntPtc	i__pgdat.m_IntPtc
#define pgdat_IntAssociatedDecoder	i__pgdat.m_IntAssociatedDecoder
#define pgdat_IntChannelBandwidth	i__pgdat.m_IntChannelBandwidth
#define pgdat_DecoderNone	IHsvProgramData_DecoderNone
#define pgdat_DecoderExt1	IHsvProgramData_DecoderExt1
#define pgdat_DecoderExt2	IHsvProgramData_DecoderExt2
#define pgdat_Antenna	IHsvProgramData_Antenna
#define pgdat_Cable	IHsvProgramData_Cable
#define pgdat_BoolMatchBrandFlag	i__pgdat.m_BoolMatchBrandFlag
#define pgdat_Nat32NumBrandIds	i__pgdat.m_Nat32NumBrandIds
#define pgdat_StringBrandIds	i__pgdat.m_StringBrandIds
#define pgdat3_BoolLock	IHsvProgramData3_BoolLock
#define pgdat3_BoolFavorite	IHsvProgramData3_BoolFavorite
#define pgdat3_BoolFavorite1	IHsvProgramData3_BoolFavorite1
#define pgdat3_BoolFavorite2	IHsvProgramData3_BoolFavorite2
#define pgdat3_BoolFavorite3	IHsvProgramData3_BoolFavorite3
#define pgdat3_BoolPreferredFavorite	IHsvProgramData3_BoolPreferredFavorite
#define pgdat3_BoolPreferredNicam	IHsvProgramData3_BoolPreferredNicam
#define pgdat3_BoolPreferredStereo	IHsvProgramData3_BoolPreferredStereo
#define pgdat3_BoolSAP	IHsvProgramData3_BoolSAP
#define pgdat3_BoolHMProtectedChannel	IHsvProgramData3_BoolHMProtectedChannel
#define pgdat3_BoolHMBlanked	IHsvProgramData3_BoolHMBlanked
#define pgdat3_BoolUserHidden	IHsvProgramData3_BoolUserHidden
#define pgdat3_BoolSystemHidden	IHsvProgramData3_BoolSystemHidden
#define pgdat3_BoolNumericSelect	IHsvProgramData3_BoolNumericSelect
#define pgdat3_BoolEpgChannel	IHsvProgramData3_BoolEpgChannel
#define pgdat3_BoolEPGShortInfoEnabled	IHsvProgramData3_BoolEPGShortInfoEnabled
#define pgdat3_BoolNewPreset	IHsvProgramData3_BoolNewPreset
#define pgdat3_BoolFreeCiMode	IHsvProgramData3_BoolFreeCiMode
#define pgdat3_BoolTuned	IHsvProgramData3_BoolTuned
#define pgdat3_BoolDeTuned	IHsvProgramData3_BoolDeTuned
#define pgdat3_BoolAttenuator	IHsvProgramData3_BoolAttenuator
#define pgdat3_BoolAgcInstalled	IHsvProgramData3_BoolAgcInstalled
#define pgdat3_BoolChannelVirgin	IHsvProgramData3_BoolChannelVirgin
#define pgdat3_BoolUpdateName	IHsvProgramData3_BoolUpdateName
#define pgdat3_IntDeltaVolume	IHsvProgramData3_IntDeltaVolume
#define pgdat3_Nat32DateStamp	IHsvProgramData3_Nat32DateStamp
#define pgdat3_Nat32AppsCookie	IHsvProgramData3_Nat32AppsCookie
#define pgdat3_Nat32TxtCookie	IHsvProgramData3_Nat32TxtCookie
#define pgdat3_Nat32CesvcCookie	IHsvProgramData3_Nat32CesvcCookie
#define pgdat3_Nat32DvbType	IHsvProgramData3_Nat32DvbType
#define pgdat3_StringChannelName	IHsvProgramData3_StringChannelName
#define pgdat3_StringExtChannelName	IHsvProgramData3_StringExtChannelName
#define pgdat3_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat3_IntTvSystem	IHsvProgramData3_IntTvSystem
#define pgdat3_IntModulation	IHsvProgramData3_IntModulation
#define pgdat3_IntNewChannelMap	IHsvProgramData3_IntNewChannelMap
#define pgdat3_IntSignalStrength	IHsvProgramData3_IntSignalStrength
#define pgdat3_IntSignalQuality	IHsvProgramData3_IntSignalQuality
#define pgdat3_IntColoursystem	IHsvProgramData3_IntColoursystem
#define pgdat3_IntDecoderType	IHsvProgramData3_IntDecoderType
#define pgdat3_IntFineTuneOffset	IHsvProgramData3_IntFineTuneOffset
#define pgdat3_IntFineTuneFrequency	IHsvProgramData3_IntFineTuneFrequency
#define pgdat3_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat3_IntNetworkId	IHsvProgramData3_IntNetworkId
#define pgdat3_IntOriginalNwId	IHsvProgramData3_IntOriginalNwId
#define pgdat3_IntTsid	IHsvProgramData3_IntTsid
#define pgdat3_IntServiceId	IHsvProgramData3_IntServiceId
#define pgdat3_IntServiceType	IHsvProgramData3_IntServiceType
#define pgdat3_IntPmtPid	IHsvProgramData3_IntPmtPid
#define pgdat3_IntPcrPid	IHsvProgramData3_IntPcrPid
#define pgdat3_IntVideoPid	IHsvProgramData3_IntVideoPid
#define pgdat3_IntVideoStreamType	IHsvProgramData3_IntVideoStreamType
#define pgdat3_IntAudioPid	IHsvProgramData3_IntAudioPid
#define pgdat3_IntAudioStreamType	IHsvProgramData3_IntAudioStreamType
#define pgdat3_IntSecAudioPid	IHsvProgramData3_IntSecAudioPid
#define pgdat3_IntSecAudioStreamType	IHsvProgramData3_IntSecAudioStreamType
#define pgdat3_IntInstallMode	IHsvProgramData3_IntInstallMode
#define pgdat3_IntCniNi	IHsvProgramData3_IntCniNi
#define pgdat3_IntDataIndicator	IHsvProgramData3_IntDataIndicator
#define pgdat3_IntPresetNumber	IHsvProgramData3_IntPresetNumber
#define pgdat3_IntModulationType	IHsvProgramData3_IntModulationType
#define pgdat3_IntLCN	IHsvProgramData3_IntLCN
#define pgdat3_IntStreamPriority	IHsvProgramData3_IntStreamPriority
#define pgdat3_IntHMMapChannelNo	IHsvProgramData3_IntHMMapChannelNo
#define pgdat3_IntPtc	IHsvProgramData3_IntPtc
#define pgdat3_IntAssociatedDecoder	IHsvProgramData3_IntAssociatedDecoder
#define pgdat3_IntChannelBandwidth	IHsvProgramData3_IntChannelBandwidth
#define pgdat3_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat3_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat3_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat3_Antenna	IHsvProgramData3_Antenna
#define pgdat3_Cable	IHsvProgramData3_Cable
#define pgdat3_IntSystemHidden	IHsvProgramData3_IntSystemHidden
#define pgdat3_IntNumericSelect	IHsvProgramData3_IntNumericSelect
#define pgdat3_IntNewChannel	IHsvProgramData3_IntNewChannel
#define pgdat3_StringSatelliteName	IHsvProgramData3_StringSatelliteName
#define pgdat3_IntSrcambledStatus	IHsvProgramData3_IntSrcambledStatus
#define pgdat3_IntInstalledSatelliteNumber	IHsvProgramData3_IntInstalledSatelliteNumber
#define pgdat3_IntUserHidden	IHsvProgramData3_IntUserHidden
#define pgdat3_FavoriteNumber	IHsvProgramData3_FavoriteNumber
#define pgdat3_FavoriteNumber1	IHsvProgramData3_FavoriteNumber1
#define pgdat3_FavoriteNumber2	IHsvProgramData3_FavoriteNumber2
#define pgdat3_FavoriteNumber3	IHsvProgramData3_FavoriteNumber3
#define pgdat3_IntEPGEnabled	IHsvProgramData3_IntEPGEnabled
#define pgdat3_IntHbbTvOption	IHsvProgramData3_IntHbbTvOption
#define pgdat3_BoolChannelLock	IHsvProgramData3_BoolChannelLock
#define pgdat3_StringTxtPages	IHsvProgramData3_StringTxtPages
#define pgdat3_IntLogoURL	IHsvProgramData3_IntLogoURL
#define pgdat3_BoolMatchBrandFlag	IHsvProgramData3_BoolMatchBrandFlag
#define pgdat3_Nat32NumBrandIds	IHsvProgramData3_Nat32NumBrandIds
#define pgdat3_StringBrandIds	IHsvProgramData3_StringBrandIds
#define pgdat3_Nat16PrimaryRegion	IHsvProgramData3_Nat16PrimaryRegion
#define pgdat3_Nat16SecondaryRegion	IHsvProgramData3_Nat16SecondaryRegion
#define pgdat3_IntTertiaryRegion	IHsvProgramData3_IntTertiaryRegion
#define pgdat3_Nat32CountryCode	IHsvProgramData3_Nat32CountryCode
#define pgdat3_Nat64UniqueNodeId	IHsvProgramData3_Nat64UniqueNodeId
#define pgdat3_BoolUserModifiedLogo	IHsvProgramData3_BoolUserModifiedLogo
#define pgdat3_MultipleLCN	IHsvProgramData3_MultipleLCN
#define pgdat3_MultiplePreset	IHsvProgramData3_MultiplePreset
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
#include "locals_mpgdat.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

