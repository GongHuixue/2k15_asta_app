#ifndef  _CHSVSATPROGRAMDATA_MPGDB_PRIV_H
#define  _CHSVSATPROGRAMDATA_MPGDB_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvChannelMapOperation.h>
#include <IHsvFlashFileSystemResources.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvPower.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <CS2MwBase.h>

class CHsvSatProgramData_mpgdb_Priv;
#define CLASSSCOPE CHsvSatProgramData_mpgdb_Priv::
#include "locals_mpgdb.h"

class CHsvSatProgramData_mpgdb_Priv : public CS2MwBase
{
public:
virtual ~CHsvSatProgramData_mpgdb_Priv();

private:
void params__init(void);
Bool  mCheckForUpdates (void *Data, int Index, int *NoItemsChanged, int *ItemIDs);
private:
#define MEMBERVARS
#include "locals_mpgdb.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvChannelMapOperationImpl(CHsvSatProgramData_mpgdb_Priv,chmapop);
IHsvFlashFileSystemResourcesImpl(CHsvSatProgramData_mpgdb_Priv,ffsres);
IHsvProgramDatabaseImpl(CHsvSatProgramData_mpgdb_Priv,ipgdb);
IHsvProgramDatabaseConstantsImpl(CHsvSatProgramData_mpgdb_Priv,ipgdbconst);
IHsvPowerImpl(CHsvSatProgramData_mpgdb_Priv,ipgdbpow);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,presettableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,digsrvctableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,satinfotableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,digtstableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,homingsvctableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,interactivesvctableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,temppresettableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,tempdigsrvctableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,tempsatinfotableconf);
IHsvSortedTableConfigurationExImpl(CHsvSatProgramData_mpgdb_Priv,tempdigtstableconf);
public:
ProvidesInterface<IHsvChannelMapOperation>	chmapop;

ProvidesInterface<IHsvFlashFileSystemResources>	ffsres;

ProvidesInterface<IHsvProgramDatabase>	ipgdb;

ProvidesInterface<IHsvProgramDatabaseConstants>	ipgdbconst;

ProvidesInterface<IHsvPower>	ipgdbpow;
ProvidesInterface<IHsvSortedTableConfigurationEx>	presettableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	digsrvctableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	satinfotableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	digtstableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx> 	homingsvctableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx> 	interactivesvctableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	temppresettableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tempdigsrvctableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tempsatinfotableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tempdigtstableconf;

//Required interfaces
public:
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvChanlibPosixLight>	rtk;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;
RequiresInterface<IHsvSatelliteInstallationNotify> insN;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;

public:
CHsvSatProgramData_mpgdb_Priv():i__chmapop(this),i__ffsres(this),i__ipgdb(this),i__ipgdbconst(this),i__ipgdbpow(this), i__presettableconf(this), i__digsrvctableconf(this), i__satinfotableconf(this), i__digtstableconf(this),i__homingsvctableconf(this),i__interactivesvctableconf(this), i__temppresettableconf(this), i__tempdigsrvctableconf(this), i__tempsatinfotableconf(this), i__tempdigtstableconf(this)
{
chmapop	=	&i__chmapop;
ffsres	=	&i__ffsres;
ipgdb	=	&i__ipgdb;
ipgdbconst	=	&i__ipgdbconst;
ipgdbpow	=	&i__ipgdbpow;
presettableconf = &i__presettableconf;
digsrvctableconf = &i__digsrvctableconf;
satinfotableconf = &i__satinfotableconf;
digtstableconf = &i__digtstableconf;
homingsvctableconf = &i__homingsvctableconf;
interactivesvctableconf = &i__interactivesvctableconf;
temppresettableconf = &i__temppresettableconf;
tempdigsrvctableconf = &i__tempdigsrvctableconf;
tempsatinfotableconf = &i__tempsatinfotableconf;
tempdigtstableconf = &i__tempdigtstableconf;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define ipgdb_SqliteDatabase	IHsvProgramDatabase_SqliteDatabase
#define ipgdb_TempDatabase	IHsvProgramDatabase_TempDatabase
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
#define rtk_iPresent() (rtk.Present())
#define rtk_SemCreate(key)	rtk->SemCreate(key)
#define rtk_SemRelease(fildes)	rtk->SemRelease(fildes)
#define rtk_SemAcquire(fildes)	rtk->SemAcquire(fildes)
#define sync_iPresent() (sync.Present())
#define sync_EnableEvents(Status)	sync->EnableEvents(Status)
#define sync_MasterEnableEvents(Status)	sync->MasterEnableEvents(Status)
#define sync_OnInsert(tableid,data)	sync->OnInsert(tableid,data)
#define sync_OnUpdate(tableid,data)	sync->OnUpdate(tableid,data)
#define sync_OnDelete(tableid,data)	sync->OnDelete(tableid,data)
#define ffsres_Directories	i__ffsres.m_Directories
#define ffsres_Files	i__ffsres.m_Files
#define ffsres_Size	i__ffsres.m_Size
#define ffsres_FilesOpen	i__ffsres.m_FilesOpen
#define ffsres_WriteRate	i__ffsres.m_WriteRate
#define ffsres_ReadRate	i__ffsres.m_ReadRate
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
#define srtdb2_iPresent() (srtdb2.Present())
#define srtdb2_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb2_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb2_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdb2_GetNoOfRecords(tableid)	srtdb2->GetNoOfRecords(tableid)
#define srtdb2_Init(tableid)	srtdb2->Init(tableid)
#define srtdb2_Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb2->Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb2_Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb2->Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb2_Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)	srtdb2->Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)
#define srtdb2_SearchOnPrimaryKey(tableid,PrimaryKey,from,to)	srtdb2->SearchOnPrimaryKey(tableid,PrimaryKey,from,to)
#define srtdb2_SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)	srtdb2->SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)
#define srtdb2_QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb2->QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb2_QueryOnIndex(tableid,index,data)	srtdb2->QueryOnIndex(tableid,index,data)
#define srtdb2_SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)	srtdb2->SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)
#define srtdb2_SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)	srtdb2->SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)
#define srtdbids_PresetTable	 		 reinterpret_cast<int>(&i__presettableconf)
#define srtdbids_DigSrvcTable	 		 reinterpret_cast<int>(&i__digsrvctableconf)
#define srtdbids_SatInfoTable	 		 reinterpret_cast<int>(&i__satinfotableconf)
#define srtdbids_DigTSTable	 	 		 reinterpret_cast<int>(&i__digtstableconf)
#define srtdbids_HomingSvcTable  		 reinterpret_cast<int>(&i__homingsvctableconf)
#define srtdbids_InteractiveSvcTable     reinterpret_cast<int>(&i__interactivesvctableconf)
#define presettableconf_MaxElements	i__presettableconf.m_MaxElements
#define presettableconf_ElementSize	i__presettableconf.m_ElementSize
#define presettableconf_ThreadSafe	i__presettableconf.m_ThreadSafe
#define presettableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define presettableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define presettableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define presettableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define presettableconf_SortCriteria	i__presettableconf.m_SortCriteria
#define presettableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define presettableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define presettableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define digsrvctableconf_MaxElements	i__digsrvctableconf.m_MaxElements
#define digsrvctableconf_ElementSize	i__digsrvctableconf.m_ElementSize
#define digsrvctableconf_ThreadSafe	i__digsrvctableconf.m_ThreadSafe
#define digsrvctableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define digsrvctableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define digsrvctableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define digsrvctableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define digsrvctableconf_SortCriteria	i__digsrvctableconf.m_SortCriteria
#define digsrvctableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define digsrvctableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define digsrvctableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define satinfotableconf_MaxElements	i__satinfotableconf.m_MaxElements
#define satinfotableconf_ElementSize	i__satinfotableconf.m_ElementSize
#define satinfotableconf_ThreadSafe	i__satinfotableconf.m_ThreadSafe
#define satinfotableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define satinfotableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define satinfotableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define satinfotableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define satinfotableconf_SortCriteria	i__satinfotableconf.m_SortCriteria
#define satinfotableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define satinfotableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define satinfotableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define digtstableconf_MaxElements	i__digtstableconf.m_MaxElements
#define digtstableconf_ElementSize	i__digtstableconf.m_ElementSize
#define digtstableconf_ThreadSafe	i__digtstableconf.m_ThreadSafe
#define digtstableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define digtstableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define digtstableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define digtstableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define digtstableconf_SortCriteria	i__digtstableconf.m_SortCriteria
#define digtstableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define digtstableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define digtstableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define srtdbids_TempPresetTable	 reinterpret_cast<int>(&i__temppresettableconf)
#define srtdbids_TempDigSrvcTable	 reinterpret_cast<int>(&i__tempdigsrvctableconf)
#define srtdbids_TempSatInfoTable	 reinterpret_cast<int>(&i__tempsatinfotableconf)
#define srtdbids_TempDigTSTable	 	reinterpret_cast<int>(&i__tempdigtstableconf)
#define temppresettableconf_MaxElements	i__temppresettableconf.m_MaxElements
#define temppresettableconf_ElementSize	i__temppresettableconf.m_ElementSize
#define temppresettableconf_ThreadSafe	i__temppresettableconf.m_ThreadSafe
#define temppresettableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define temppresettableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define temppresettableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define temppresettableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define temppresettableconf_SortCriteria	i__temppresettableconf.m_SortCriteria
#define temppresettableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define temppresettableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define temppresettableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define tempdigsrvctableconf_MaxElements	i__tempdigsrvctableconf.m_MaxElements
#define tempdigsrvctableconf_ElementSize	i__tempdigsrvctableconf.m_ElementSize
#define tempdigsrvctableconf_ThreadSafe	i__tempdigsrvctableconf.m_ThreadSafe
#define tempdigsrvctableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define tempdigsrvctableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define tempdigsrvctableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define tempdigsrvctableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define tempdigsrvctableconf_SortCriteria	i__tempdigsrvctableconf.m_SortCriteria
#define tempdigsrvctableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define tempdigsrvctableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define tempdigsrvctableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define tempsatinfotableconf_MaxElements	i__tempsatinfotableconf.m_MaxElements
#define tempsatinfotableconf_ElementSize	i__tempsatinfotableconf.m_ElementSize
#define tempsatinfotableconf_ThreadSafe	i__tempsatinfotableconf.m_ThreadSafe
#define tempsatinfotableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define tempsatinfotableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define tempsatinfotableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define tempsatinfotableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define tempsatinfotableconf_SortCriteria	i__tempsatinfotableconf.m_SortCriteria
#define tempsatinfotableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define tempsatinfotableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define tempsatinfotableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define tempdigtstableconf_MaxElements	i__tempdigtstableconf.m_MaxElements
#define tempdigtstableconf_ElementSize	i__tempdigtstableconf.m_ElementSize
#define tempdigtstableconf_ThreadSafe	i__tempdigtstableconf.m_ThreadSafe
#define tempdigtstableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define tempdigtstableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define tempdigtstableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define tempdigtstableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define tempdigtstableconf_SortCriteria	i__tempdigtstableconf.m_SortCriteria
#define tempdigtstableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define tempdigtstableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define tempdigtstableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey


#define homingsvctableconf_MaxElements	i__homingsvctableconf.m_MaxElements
#define homingsvctableconf_ElementSize	i__homingsvctableconf.m_ElementSize
#define homingsvctableconf_ThreadSafe	i__homingsvctableconf.m_ThreadSafe
#define homingsvctableconf_Primary		IHsvSortedTableConfigurationEx_Primary
#define homingsvctableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define homingsvctableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define homingsvctableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define homingsvctableconf_SortCriteria	i__homingsvctableconf.m_SortCriteria
#define homingsvctableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define homingsvctableconf_Equal		IHsvSortedTableConfigurationEx_Equal
#define homingsvctableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define interactivesvctableconf_MaxElements	i__interactivesvctableconf.m_MaxElements
#define interactivesvctableconf_ElementSize	i__interactivesvctableconf.m_ElementSize
#define interactivesvctableconf_ThreadSafe	i__interactivesvctableconf.m_ThreadSafe
#define interactivesvctableconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define interactivesvctableconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define interactivesvctableconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define interactivesvctableconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define interactivesvctableconf_SortCriteria	i__interactivesvctableconf.m_SortCriteria
#define interactivesvctableconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define interactivesvctableconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define interactivesvctableconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

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
#include "locals_mpgdb.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

