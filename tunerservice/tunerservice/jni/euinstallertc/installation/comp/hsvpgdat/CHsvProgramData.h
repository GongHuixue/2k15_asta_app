#ifndef  _CHSVPROGRAMDATA_H
#define  _CHSVPROGRAMDATA_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvProgramData_m.h>
#include <CHsvProgramData_mpgdat.h>
#include <CHsvProgramData_mpgdb.h>
#include <IHsvFlashFileSystemResources.h>
#include <IHsvProgramData.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvPower.h>
#include <IHsvProgramDataDiv.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvProgramDataNotifyExExEx.h>
#include <IAppApiChannelLibNvmIds.h>
#include <IProdApiNvmProtectedAccessExEx.h>
#include <IHsvProgramDataControl.h>
#include <IHsvProgramDataControl3.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvProgramDataNotifyExEx.h>
#include <IHsvChanlibPosixLight.h>
#include <IProdApiNvmSubIdsEx.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IRealTimeKernel.h>
#include <IHsvInstallationNotify.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvSortedTable2.h>
#include <IHsvTcSystemSettingsEx.h>

class CHsvProgramData
{
public:
virtual ~CHsvProgramData(){}

//Contained Modules
private:
CHsvProgramData_m m;
CHsvProgramData_mpgdat mpgdat;
CHsvProgramData_mpgdb mpgdb;
public:
ProvidesInterface<IHsvFlashFileSystemResources>	ffsres;

ProvidesInterface<IHsvProgramData>	pgdat;

ProvidesInterface<IHsvProgramData3>	pgdat3;

ProvidesInterface<IHsvProgramDatabase>	pgdb;

ProvidesInterface<IHsvProgramDatabaseConstants>	pgdbconst;

ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvProgramDataDiv>	div;
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvProgramDataNotifyExExEx>	ipgdatNxxx;
RequiresInterface<IAppApiChannelLibNvmIds>	nvmids;
RequiresInterface<IProdApiNvmProtectedAccessExEx>	nvmpa;
RequiresInterface<IHsvProgramDataControl>	pgctl;
RequiresInterface<IHsvProgramDataControl3>	pgctl3;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvProgramDataNotifyExEx>	pgdatNxx;
RequiresInterface<IHsvProgramDataNotifyExExEx>	pgdatNxxx;
RequiresInterface<IHsvChanlibPosixLight>	rtk;
RequiresInterface<IProdApiNvmSubIdsEx>	subid;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;
RequiresInterface<IRealTimeKernel>		corertk;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvTcSystemSettings>	sysset;

public:
CHsvProgramData()
{
pgdb	=	mpgdb.ipgdb;
pgdbconst	=	mpgdb.ipgdbconst;
pow	=	m.pow;
m.ipgdatpow	=	mpgdat.ipgdatpow;
m.ipgdbpow	=	mpgdb.ipgdbpow;
pgdat	=	mpgdat.pgdat;
pgdat3	=	mpgdat.pgdat3;
ffsres	=	mpgdb.ffsres;
mpgdb.rtk	=	rtk;
mpgdb.corertk	=	corertk;
mpgdb.pgctl3	=	pgctl3;
mpgdb.pgctl	=	pgctl;
mpgdb.div	=	div;
mpgdb.err	=	err;
mpgdb.sync	=	sync;
mpgdb.ffsdir	=	ffsdir;
mpgdb.pgdatN	=	pgdatN;
mpgdb.insN 		=insN;
mpgdb.srtdb2 = srtdb2;
mpgdb.srtdbids = srtdbids;
mpgdb.sysset	=	sysset;
mpgdat.err	=	err;
mpgdat.div	=	div;
mpgdat.ipgdbconst	=	mpgdb.ipgdbconst;
mpgdat.ipgdb	=	mpgdb.ipgdb;
mpgdat.chmapop	=	mpgdb.chmapop;
mpgdat.pgdatN	=	pgdatN;
mpgdat.pgdatNxx	=	pgdatNxx;
mpgdat.sync	=	sync;
mpgdat.pgdatNxxx	=	pgdatNxxx;
mpgdat.nvmpa	=	nvmpa;
mpgdat.nvmids	=	nvmids;
mpgdat.subid	=	subid;
}

};

#endif

