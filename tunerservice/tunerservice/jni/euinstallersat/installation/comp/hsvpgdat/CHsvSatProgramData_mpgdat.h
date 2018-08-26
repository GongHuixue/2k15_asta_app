#ifndef  _CHSVSATPROGRAMDATA_MPGDAT_H
#define  _CHSVSATPROGRAMDATA_MPGDAT_H 

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
class CHsvSatProgramData_mpgdat_Priv;
class CHsvSatProgramData_mpgdat
{
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
CHsvSatProgramData_mpgdat();
virtual ~CHsvSatProgramData_mpgdat();
private:
CHsvSatProgramData_mpgdat_Priv	*m_priv;
};

#endif

