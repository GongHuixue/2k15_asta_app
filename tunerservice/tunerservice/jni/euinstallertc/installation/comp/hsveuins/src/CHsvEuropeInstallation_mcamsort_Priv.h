#ifndef  _CHSVEUROPEINSTALLATION_MCAMSORT_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MCAMSORT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCamPresetSort.h>
#include <IHsvPower.h>
#include <IHsvCookieNvmInfo.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSortNotify.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_mcamsort_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_mcamsort_Priv::
#include "locals_mcamsort.h"

class CHsvEuropeInstallation_mcamsort_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_mcamsort_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mcamsort.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvCamPresetSortImpl(CHsvEuropeInstallation_mcamsort_Priv,icamsort);
IHsvPowerImpl(CHsvEuropeInstallation_mcamsort_Priv,icamsortpow);
public:
ProvidesInterface<IHsvCamPresetSort>	icamsort;

ProvidesInterface<IHsvPower>	icamsortpow;

//Required interfaces
public:
RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSortNotify>	sortN;
private:
Pumpdefines(CHsvEuropeInstallation_mcamsort_Priv);

public:
CHsvEuropeInstallation_mcamsort_Priv():i__icamsort(this),i__icamsortpow(this)
{
icamsort	=	&i__icamsort;
icamsortpow	=	&i__icamsortpow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define nvmapps_iPresent() (nvmapps.Present())
#define nvmapps_CookieNvmInfo	nvmapps->CookieNvmInfo()
#define nvmapps_NumberOfEntries	IHsvCookieNvmInfo_NumberOfEntries
#define nvmapps_InvalidNvmID	IHsvCookieNvmInfo_InvalidNvmID
#define nvmapps_GetDefaultCookieValue()	nvmapps->GetDefaultCookieValue()
#define nvmcesvc_iPresent() (nvmcesvc.Present())
#define nvmcesvc_CookieNvmInfo	nvmcesvc->CookieNvmInfo()
#define nvmcesvc_NumberOfEntries	IHsvCookieNvmInfo_NumberOfEntries
#define nvmcesvc_InvalidNvmID	IHsvCookieNvmInfo_InvalidNvmID
#define nvmcesvc_GetDefaultCookieValue()	nvmcesvc->GetDefaultCookieValue()
#define nvmtxt_iPresent() (nvmtxt.Present())
#define nvmtxt_CookieNvmInfo	nvmtxt->CookieNvmInfo()
#define nvmtxt_NumberOfEntries	IHsvCookieNvmInfo_NumberOfEntries
#define nvmtxt_InvalidNvmID	IHsvCookieNvmInfo_InvalidNvmID
#define nvmtxt_GetDefaultCookieValue()	nvmtxt->GetDefaultCookieValue()
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
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvEuropeInstallation_mcamsort_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define sortN_iPresent() (sortN.Present())
#define sortN_EventNewPresetFound	IHsvSortNotify_EventNewPresetFound
#define sortN_EventChannelRemoved	IHsvSortNotify_EventChannelRemoved
#define sortN_EventSortComplete	IHsvSortNotify_EventSortComplete
#define sortN_OnEvent(eventid,value)	sortN->OnEvent(eventid,value)
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
#include "locals_mcamsort.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

