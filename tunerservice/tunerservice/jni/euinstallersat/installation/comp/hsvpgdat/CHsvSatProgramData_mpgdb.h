#ifndef  _CHSVSATPROGRAMDATA_MPGDB_H
#define  _CHSVSATPROGRAMDATA_MPGDB_H 

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
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvSortedTableConfigurationEx.h>

class CHsvSatProgramData_mpgdb_Priv;
class CHsvSatProgramData_mpgdb
{
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
ProvidesInterface<IHsvSortedTableConfigurationEx>   homingsvctableconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>   interactivesvctableconf;
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
CHsvSatProgramData_mpgdb();
virtual ~CHsvSatProgramData_mpgdb();
private:
CHsvSatProgramData_mpgdb_Priv	*m_priv;
};

#endif

