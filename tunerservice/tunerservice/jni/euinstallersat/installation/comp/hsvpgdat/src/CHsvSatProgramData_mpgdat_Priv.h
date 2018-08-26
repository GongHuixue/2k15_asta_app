#ifndef  _CHSVSATPROGRAMDATA_MPGDAT_PRIV_H
#define  _CHSVSATPROGRAMDATA_MPGDAT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvProgramData.h>
#include <IHsvProgramData3.h>
#include <IHsvChannelMapOperation.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvProgramDataNotifyExEx.h>
#include <IHsvProgramDataNotifyExExEx.h>
#include <IHsvChannelLibSyncEvents.h>
#include <CS2MwBase.h>
class CHsvSatProgramData_mpgdat_Priv;
#define CLASSSCOPE CHsvSatProgramData_mpgdat_Priv::
#include "locals_mpgdat.h"

class CHsvSatProgramData_mpgdat_Priv : public CS2MwBase
{
public:
virtual ~CHsvSatProgramData_mpgdat_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpgdat.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvSatProgramData_mpgdat_Priv,ipgdatpow);
IHsvProgramDataImpl(CHsvSatProgramData_mpgdat_Priv,pgdat);
IHsvProgramData3Impl(CHsvSatProgramData_mpgdat_Priv,pgdat3);
public:
ProvidesInterface<IHsvPower>	ipgdatpow;

ProvidesInterface<IHsvProgramData>	pgdat;

ProvidesInterface<IHsvProgramData3>	pgdat3;

//Required interfaces
public:
RequiresInterface<IHsvChannelMapOperation>	chmapop;
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IHsvProgramDatabase>	ipgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	ipgdbconst;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvProgramDataNotifyExEx>	pgdatNxx;
RequiresInterface<IHsvProgramDataNotifyExExEx>	pgdatNxxx;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;

public:
CHsvSatProgramData_mpgdat_Priv():i__ipgdatpow(this),i__pgdat(this),i__pgdat3(this)
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
#define ipgdb_SaveChannelMapsToBackup()  ipgdb->SaveChannelMapsToBackup()
#define ipgdb_LoadChannelMapsFromBackup ipgdb->LoadChannelMapsFromBackup()
#define pgdb_SqliteDatabase		IHsvProgramDatabase_SqliteDatabase
#define pgdb_TempDatabase		IHsvProgramDatabase_TempDatabase
#define pgdb_SelectChannelDatabase(databaseId)		pgdb->SelectChannelDatabase(databaseId)
#define pgdb_SyncDatabase(fromDatabaseId,toDatabaseId)		pgdb->SyncDatabase(fromDatabaseId,toDatabaseId)
#define pgdb_AddInIndex(tableid,index,channeldata)	pgdb->AddInIndex(tableid,index,channeldata)
#define pgdb_BeginSqliteTransaction()		pgdb->BeginSqliteTransaction()
#define pgdb_CommitSqliteTransaction()		pgdb->CommitSqliteTransaction()
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
#define pgdat3_BoolLock	i__pgdat3.m_BoolLock
#define pgdat3_BoolFavorite	i__pgdat3.m_BoolFavorite
#define pgdat3_BoolUserHidden	i__pgdat3.m_BoolUserHidden
#define pgdat3_BoolSystemHidden	i__pgdat3.m_BoolSystemHidden
#define pgdat3_BoolNewPreset	i__pgdat3.m_BoolNewPreset
#define pgdat3_BoolFreeCiMode	i__pgdat3.m_BoolFreeCiMode
#define pgdat3_BoolUpdateName	i__pgdat3.m_BoolUpdateName
#define pgdat3_IntDeltaVolume	i__pgdat3.m_IntDeltaVolume
#define pgdat3_Nat32DateStamp	i__pgdat3.m_Nat32DateStamp
#define pgdat3_Nat32AppsCookie	i__pgdat3.m_Nat32AppsCookie
#define pgdat3_Nat32TxtCookie	i__pgdat3.m_Nat32TxtCookie
#define pgdat3_StringChannelName	i__pgdat3.m_StringChannelName
#define pgdat3_StringExtChannelName	i__pgdat3.m_StringExtChannelName
#define pgdat3_IntFrequency	i__pgdat3.m_IntFrequency
#define pgdat3_IntModulation	i__pgdat3.m_IntModulation
#define pgdat3_IntSignalStrength	i__pgdat3.m_IntSignalStrength
#define pgdat3_IntSignalQuality	i__pgdat3.m_IntSignalQuality
#define pgdat3_Nat32SymbolRate	i__pgdat3.m_Nat32SymbolRate
#define pgdat3_IntNetworkId	i__pgdat3.m_IntNetworkId
#define pgdat3_IntOriginalNwId	i__pgdat3.m_IntOriginalNwId
#define pgdat3_IntTsid	i__pgdat3.m_IntTsid
#define pgdat3_IntServiceId	i__pgdat3.m_IntServiceId
#define pgdat3_IntServiceType	i__pgdat3.m_IntServiceType
#define pgdat3_IntPmtPid	i__pgdat3.m_IntPmtPid
#define pgdat3_IntPcrPid	i__pgdat3.m_IntPcrPid
#define pgdat3_IntVideoPid	i__pgdat3.m_IntVideoPid
#define pgdat3_IntVideoStreamType	i__pgdat3.m_IntVideoStreamType
#define pgdat3_IntAudioPid	i__pgdat3.m_IntAudioPid
#define pgdat3_IntAudioStreamType	i__pgdat3.m_IntAudioStreamType
#define pgdat3_IntSecAudioPid	i__pgdat3.m_IntSecAudioPid
#define pgdat3_IntSecAudioStreamType	i__pgdat3.m_IntSecAudioStreamType
#define pgdat3_IntPresetNumber	i__pgdat3.m_IntPresetNumber
#define pgdat3_IntModulationType	i__pgdat3.m_IntModulationType
#define pgdat3_IntLCN	i__pgdat3.m_IntLCN
#define pgdat3_IntPtc	i__pgdat3.m_IntPtc
#define pgdat3_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat3_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat3_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat3_Antenna	IHsvProgramData3_Antenna
#define pgdat3_Cable	IHsvProgramData3_Cable
#define pgdat3_IntSystemHidden	i__pgdat3.m_IntSystemHidden
#define pgdat3_IntNumericSelect	i__pgdat3.m_IntNumericSelect
#define pgdat3_IntNewChannel	i__pgdat3.m_IntNewChannel
#define pgdat3_StringSatelliteName	i__pgdat3.m_StringSatelliteName
#define pgdat3_IntSrcambledStatus	i__pgdat3.m_IntSrcambledStatus
#define pgdat3_IntInstalledSatelliteNumber	i__pgdat3.m_IntInstalledSatelliteNumber
#define pgdat3_IntUserHidden	i__pgdat3.m_IntUserHidden
#define pgdat3_FavoriteNumber	i__pgdat3.m_FavoriteNumber
#define pgdat3_IntHbbTvOption	i__pgdat3.m_IntHbbTvOption
#define pgdat3_BoolChannelLock	i__pgdat3.m_BoolChannelLock
#define pgdat3_StringTxtPages	i__pgdat3.m_StringTxtPages
#define pgdat3_IntLogoURL	i__pgdat3.m_IntLogoURL
#define pgdat3_BoolMatchBrandFlag	i__pgdat3.m_BoolMatchBrandFlag
#define pgdat3_Nat32NumBrandIds	i__pgdat3.m_Nat32NumBrandIds
#define pgdat3_StringBrandIds	i__pgdat3.m_StringBrandIds
#define pgdat3_Nat64UniqueNodeId	i__pgdat3.m_Nat64UniqueNodeId
#define pgdat3_BoolUserModifiedLogo	i__pgdat3.m_BoolUserModifiedLogo
#define pgdat3_Nat32TPID	i__pgdat3.m_Nat32TPID
#define pgdat3_IntLnbNumber	i__pgdat3.m_IntLnbNumber
#define pgdat3_IntPolarization	i__pgdat3.m_IntPolarization
#define pgdat3_IntSatelliteId	i__pgdat3.m_IntSatelliteId
#define pgdat3_IntInstalledSatelliteId	i__pgdat3.m_IntInstalledSatelliteId
#define pgdat3_IntPackageGroup	i__pgdat3.m_IntPackageGroup
#define pgdat3_IntDpTsid	i__pgdat3.m_IntDpTsid
#define pgdat3_IntDpServiceId	i__pgdat3.m_IntDpServiceId
#define pgdat3_MultipleLCN	i__pgdat3.m_MultipleLCN
#define pgdat3_MultiplePreset	i__pgdat3.m_MultiplePreset
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

