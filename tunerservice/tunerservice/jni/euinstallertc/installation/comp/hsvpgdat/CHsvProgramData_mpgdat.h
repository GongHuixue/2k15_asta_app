#ifndef  _CHSVPROGRAMDATA_MPGDAT_H
#define  _CHSVPROGRAMDATA_MPGDAT_H 

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
class CHsvProgramData_mpgdat_Priv;
class CHsvProgramData_mpgdat
{
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
CHsvProgramData_mpgdat();
virtual ~CHsvProgramData_mpgdat();
private:
CHsvProgramData_mpgdat_Priv	*m_priv;
};

#endif

