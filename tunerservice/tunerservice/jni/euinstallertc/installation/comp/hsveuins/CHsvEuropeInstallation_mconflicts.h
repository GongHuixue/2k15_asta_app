#ifndef  _CHSVEUROPEINSTALLATION_MCONFLICTS_H
#define  _CHSVEUROPEINSTALLATION_MCONFLICTS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvConflicts.h>
#include <IHsvPower.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvConflictsNotify.h>
#include <IHsvInstallationNotify.h>
#include <IMemoryOperations.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
class CHsvEuropeInstallation_mconflicts_Priv;
class CHsvEuropeInstallation_mconflicts
{
public:
ProvidesInterface<IHsvConflicts>	iconf;

ProvidesInterface<IHsvPower>	iconpow;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvConflictsNotify>	iconfN;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvEuropeInstallation_mconflicts();
virtual ~CHsvEuropeInstallation_mconflicts();
private:
CHsvEuropeInstallation_mconflicts_Priv	*m_priv;
};

#endif

