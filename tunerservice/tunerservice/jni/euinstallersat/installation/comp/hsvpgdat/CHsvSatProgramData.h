#ifndef  _CHSVSATPROGRAMDATA_H
#define  _CHSVSATPROGRAMDATA_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvSatProgramData_m.h>
#include <CHsvSatProgramData_mpgdat.h>
#include <CHsvSatProgramData_mpgdb.h>
#include <IHsvFlashFileSystemResources.h>
#include <IHsvProgramData.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvPower.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvProgramDataNotify.h>
#include <IHsvProgramDataNotifyExEx.h>
#include <IHsvProgramDataNotifyExExEx.h>
#include <IHsvChanlibPosixLight.h>
#include <IHsvChannelLibSyncEvents.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>

class CHsvSatProgramData
{
public:
virtual ~CHsvSatProgramData(){}

//Contained Modules
private:
CHsvSatProgramData_m m;
CHsvSatProgramData_mpgdat mpgdat;
CHsvSatProgramData_mpgdb mpgdb;
public:
ProvidesInterface<IHsvFlashFileSystemResources>	ffsres;

ProvidesInterface<IHsvProgramData>	pgdat;

ProvidesInterface<IHsvProgramData3>	pgdat3;

ProvidesInterface<IHsvProgramDatabase>	pgdb;

ProvidesInterface<IHsvProgramDatabaseConstants>	pgdbconst;

ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvChannelLibReturnCodes>	err;
RequiresInterface<IHsvProgramDataNotify>	pgdatN;
RequiresInterface<IHsvProgramDataNotifyExEx>	pgdatNxx;
RequiresInterface<IHsvProgramDataNotifyExExEx>	pgdatNxxx;
RequiresInterface<IHsvChanlibPosixLight>	rtk;
RequiresInterface<IHsvChannelLibSyncEvents>	sync;
RequiresInterface<IHsvSatelliteInstallationNotify> insN;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;


public:
CHsvSatProgramData()
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
mpgdb.err	=	err;
mpgdb.sync	=	sync;
mpgdb.pgdatN	=	pgdatN;
mpgdat.err	=	err;
mpgdat.ipgdbconst	=	mpgdb.ipgdbconst;
mpgdat.ipgdb	=	mpgdb.ipgdb;
mpgdat.chmapop	=	mpgdb.chmapop;
mpgdat.pgdatN	=	pgdatN;
mpgdat.pgdatNxx	=	pgdatNxx;
mpgdat.sync	=	sync;
mpgdat.pgdatNxxx	=	pgdatNxxx;
mpgdb.insN=insN;
mpgdb.srtdb2 = srtdb2;
mpgdb.srtdbids = srtdbids;
}

};

#endif

