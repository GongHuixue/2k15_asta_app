#ifndef  _CHSVEUROPEINSTALLATION_MADVPGITR_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MADVPGITR_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAdvanceProgramIterator.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramIterator.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_madvpgitr_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_madvpgitr_Priv::
#include "locals_madvpgitr.h"

class CHsvEuropeInstallation_madvpgitr_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_madvpgitr_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_madvpgitr.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvAdvanceProgramIteratorImpl(CHsvEuropeInstallation_madvpgitr_Priv,iadvpgitr);
public:
ProvidesInterface<IHsvAdvanceProgramIterator>	iadvpgitr;

//Required interfaces
public:
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramIterator>	pgitr;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;

public:
CHsvEuropeInstallation_madvpgitr_Priv():i__iadvpgitr(this)
{
iadvpgitr	=	&i__iadvpgitr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define apperr_iPresent() (apperr.Present())
#define apperr_Ok	IAppApiChannelLibReturnCodes_Ok
#define apperr_BadParameter	IAppApiChannelLibReturnCodes_BadParameter
#define apperr_ChannelTableEmpty	IAppApiChannelLibReturnCodes_ChannelTableEmpty
#define apperr_ChannelTableExhausted	IAppApiChannelLibReturnCodes_ChannelTableExhausted
#define apperr_MinorNumbersExhausted	IAppApiChannelLibReturnCodes_MinorNumbersExhausted
#define apperr_NotSupported	IAppApiChannelLibReturnCodes_NotSupported
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
#define pgitr_iPresent() (pgitr.Present())
#define pgitr_All	IHsvProgramIterator_All
#define pgitr_Digital	IHsvProgramIterator_Digital
#define pgitr_Analog	IHsvProgramIterator_Analog
#define pgitr_Mux	IHsvProgramIterator_Mux
#define pgitr_ChannelsInMux	IHsvProgramIterator_ChannelsInMux
#define pgitr_None	IHsvProgramIterator_None
#define pgitr_Favorite	IHsvProgramIterator_Favorite
#define pgitr_Favorite1	IHsvProgramIterator_Favorite1
#define pgitr_Favorite2	IHsvProgramIterator_Favorite2
#define pgitr_Favorite3	IHsvProgramIterator_Favorite3
#define pgitr_Locked	IHsvProgramIterator_Locked
#define pgitr_UnLocked	IHsvProgramIterator_UnLocked
#define pgitr_EpgChannel	IHsvProgramIterator_EpgChannel
#define pgitr_NonEpgChannel	IHsvProgramIterator_NonEpgChannel
#define pgitr_SystemHidden	IHsvProgramIterator_SystemHidden
#define pgitr_NonSystemHidden	IHsvProgramIterator_NonSystemHidden
#define pgitr_UserHidden	IHsvProgramIterator_UserHidden
#define pgitr_NonUserHidden	IHsvProgramIterator_NonUserHidden
#define pgitr_AudioOnly	IHsvProgramIterator_AudioOnly
#define pgitr_NonAudioOnly	IHsvProgramIterator_NonAudioOnly
#define pgitr_DvbT	IHsvProgramIterator_DvbT
#define pgitr_DvbC	IHsvProgramIterator_DvbC
#define pgitr_DvbTLite	IHsvProgramIterator_DvbTLite
#define pgitr_DvbCLite	IHsvProgramIterator_DvbCLite
#define pgitr_DvbS2	IHsvProgramIterator_DvbS2
#define pgitr_PreferredFavorite	IHsvProgramIterator_PreferredFavorite
#define pgitr_GetNoOfChannels(mode,descriptor,noofchannels)	pgitr->GetNoOfChannels(mode,descriptor,noofchannels)
#define pgitr_GetFirstChannel(mode,descriptor,channelno)	pgitr->GetFirstChannel(mode,descriptor,channelno)
#define pgitr_GetLastChannel(mode,descriptor,channelno)	pgitr->GetLastChannel(mode,descriptor,channelno)
#define pgitr_GetNextChannel(mode,descriptor,channelno)	pgitr->GetNextChannel(mode,descriptor,channelno)
#define pgitr_GetPreviousChannel(mode,descriptor,channelno)	pgitr->GetPreviousChannel(mode,descriptor,channelno)
#define pgitr_GetFirstMajorChannel(mode,descriptor,channelno)	pgitr->GetFirstMajorChannel(mode,descriptor,channelno)
#define pgitr_GetLastMajorChannel(mode,descriptor,channelno)	pgitr->GetLastMajorChannel(mode,descriptor,channelno)
#define pgitr_GetNextMajorChannel(mode,descriptor,channelno)	pgitr->GetNextMajorChannel(mode,descriptor,channelno)
#define pgitr_GetPreviousMajorChannel(mode,descriptor,channelno)	pgitr->GetPreviousMajorChannel(mode,descriptor,channelno)
#define pgitr_GetNoOfMinorChannelsOfMajor(descriptor,channelno,noofminors)	pgitr->GetNoOfMinorChannelsOfMajor(descriptor,channelno,noofminors)
#define pgitr_GetFirstMinorChannel(descriptor,channelno)	pgitr->GetFirstMinorChannel(descriptor,channelno)
#define pgitr_GetLastMinorChannel(descriptor,channelno)	pgitr->GetLastMinorChannel(descriptor,channelno)
#define pgitr_GetNextMinorChannel(descriptor,channelno)	pgitr->GetNextMinorChannel(descriptor,channelno)
#define pgitr_GetPreviousMinorChannel(descriptor,channelno)	pgitr->GetPreviousMinorChannel(descriptor,channelno)
#define pgitr_GetNoOfMultiplexes(noofmuxes)	pgitr->GetNoOfMultiplexes(noofmuxes)
#define pgitr_GetFirstMultiplex(mux)	pgitr->GetFirstMultiplex(mux)
#define pgitr_GetNextMultiplex(mux)	pgitr->GetNextMultiplex(mux)
#define pgitr_GetPreviousMultiplex(mux)	pgitr->GetPreviousMultiplex(mux)
#define pgitr_GetLastMultiplex(mux)	pgitr->GetLastMultiplex(mux)
#define srtdb_iPresent() (srtdb.Present())
#define srtdb_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdb_GetNoOfRecords(tableid)	srtdb->GetNoOfRecords(tableid)
#define srtdb_Init(tableid)	srtdb->Init(tableid)
#define srtdb_Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)	srtdb->Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)
#define srtdb_SearchOnPrimaryKey(tableid,PrimaryKey,from,to)	srtdb->SearchOnPrimaryKey(tableid,PrimaryKey,from,to)
#define srtdb_SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)	srtdb->SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)
#define srtdb_QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_QueryOnIndex(tableid,index,data)	srtdb->QueryOnIndex(tableid,index,data)
#define srtdb_SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)	srtdb->SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)
#define srtdb_SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)	srtdb->SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)
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
#include "locals_madvpgitr.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

