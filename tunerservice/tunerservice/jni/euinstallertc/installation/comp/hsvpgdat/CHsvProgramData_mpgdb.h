#ifndef  _CHSVPROGRAMDATA_MPGDB_H
#define  _CHSVPROGRAMDATA_MPGDB_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvChannelMapOperation.h>
#include <IHsvFlashFileSystemResources.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvPower.h>
#include <IHsvProgramDataDiv.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvProgramDataControl.h>
#include <IHsvProgramDataControl3.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IRealTimeKernel.h>
#include <IHsvInstallationNotify.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvSortedTable2.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvTcSystemSettings.h>

class CHsvProgramData_mpgdb_Priv;
class CHsvProgramData_mpgdb
{
public:
ProvidesInterface<IHsvChannelMapOperation>	chmapop;

ProvidesInterface<IHsvFlashFileSystemResources>	ffsres;

ProvidesInterface<IHsvProgramDatabase>	ipgdb;

ProvidesInterface<IHsvProgramDatabaseConstants>	ipgdbconst;

ProvidesInterface<IHsvPower>	ipgdbpow;
ProvidesInterface<IHsvSortedTableConfigurationEx>	freqmaptableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tstableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	digsrvtableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	analogtableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	presettableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tempfreqmaptableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	temptstableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tempdigsrvtableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	tempanalogtableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	temppresettableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	backupfreqmaptableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	backuptstableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	backupdigsrvtableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	backupanalogtableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	backuppresettableconf;

//Required interfaces
public:
RequiresInterface<IHsvProgramDataDiv>	div;
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvProgramDataControl>	pgctl;
RequiresInterface<IHsvProgramDataControl3>	pgctl3;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvChanlibPosixLight>	rtk;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;
RequiresInterface<IRealTimeKernel>		corertk;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvProgramData_mpgdb();
virtual ~CHsvProgramData_mpgdb();
private:
CHsvProgramData_mpgdb_Priv	*m_priv;
};

#endif

