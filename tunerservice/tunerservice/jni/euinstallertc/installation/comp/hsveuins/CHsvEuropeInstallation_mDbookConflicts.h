#ifndef  _CHSVEUROPEINSTALLATION_MDBOOKCONFLICTS_H
#define  _CHSVEUROPEINSTALLATION_MDBOOKCONFLICTS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvConflicts.h>
#include <IHsvPower.h>
#include <IHsvCountryIds.h>
#include <IHsvPool.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvConflictsNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
class CHsvEuropeInstallation_mDbookConflicts_Priv;
class CHsvEuropeInstallation_mDbookConflicts
{
public:
ProvidesInterface<IHsvConflicts>	idbookconf;

ProvidesInterface<IHsvPower>	idbookconpow;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbtins_digacq;
RequiresInterface<IHsvDVBSettings>	hsvdvbtins_dvbset;
RequiresInterface<IHsvConflictsNotify>	idbookconfN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvEuropeInstallation_mDbookConflicts();
virtual ~CHsvEuropeInstallation_mDbookConflicts();
private:
CHsvEuropeInstallation_mDbookConflicts_Priv	*m_priv;
};

#endif

