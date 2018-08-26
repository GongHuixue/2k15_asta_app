#ifndef  _CHSVEUROPEINSTALLATION_MDBOOKSORT_H
#define  _CHSVEUROPEINSTALLATION_MDBOOKSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvConflictsNotify.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvPower.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvInstallationCountrySpecifics.h>
#include <IHsvAdvanceProgramIterator.h>
#include <IHsvConflicts.h>
#include <IHsvInstallationUtility.h>
#include <IMemoryOperations.h>
#include <IHsvCookieNvmInfo.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvSortNotify.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvAnalogInstallation.h>
#include <IHsvDVBSettings.h>
class CHsvEuropeInstallation_mDbookSort_Priv;
class CHsvEuropeInstallation_mDbookSort
{
public:
ProvidesInterface<IHsvConflictsNotify>	idbookconfN;

ProvidesInterface<IHsvHybridPresetSort>	idbooksort;

ProvidesInterface<IHsvPower>	idbooksortpow;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvInstallationCountrySpecifics>	hsvdvbtins_inscountry;
RequiresInterface<IHsvAdvanceProgramIterator>	iadvpgitr;
RequiresInterface<IHsvConflicts>	idbookconf;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvSortNotify>	sortN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvAnalogInstallation>	hsvprins_prins;
RequiresInterface<IHsvDVBSettings>	hsvdvbtins_dvbset;
public:
CHsvEuropeInstallation_mDbookSort();
virtual ~CHsvEuropeInstallation_mDbookSort();
private:
CHsvEuropeInstallation_mDbookSort_Priv	*m_priv;
};

#endif

