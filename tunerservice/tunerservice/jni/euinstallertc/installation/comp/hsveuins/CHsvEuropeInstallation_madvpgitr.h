#ifndef  _CHSVEUROPEINSTALLATION_MADVPGITR_H
#define  _CHSVEUROPEINSTALLATION_MADVPGITR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAdvanceProgramIterator.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramIterator.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
class CHsvEuropeInstallation_madvpgitr_Priv;
class CHsvEuropeInstallation_madvpgitr
{
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
CHsvEuropeInstallation_madvpgitr();
virtual ~CHsvEuropeInstallation_madvpgitr();
private:
CHsvEuropeInstallation_madvpgitr_Priv	*m_priv;
};

#endif

