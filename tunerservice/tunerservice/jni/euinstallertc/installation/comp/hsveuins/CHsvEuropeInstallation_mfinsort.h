#ifndef  _CHSVEUROPEINSTALLATION_MFINSORT_H
#define  _CHSVEUROPEINSTALLATION_MFINSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvPower.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvInstallationCountrySpecifics.h>
#include <IHsvAdvanceProgramIterator.h>
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
#include <IHsvAnalogInstallation.h>
class CHsvEuropeInstallation_mfinsort_Priv;
class CHsvEuropeInstallation_mfinsort
{
public:
ProvidesInterface<IHsvHybridPresetSort>	ifinsort;

ProvidesInterface<IHsvPower>	ifinsortpow;

//Required interfaces
public:
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvInstallationCountrySpecifics>	hsvdvbtins_inscountry;
RequiresInterface<IHsvAdvanceProgramIterator>	iadvpgitr;
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
RequiresInterface<IHsvAnalogInstallation>	hsvprins_prins;
public:
CHsvEuropeInstallation_mfinsort();
virtual ~CHsvEuropeInstallation_mfinsort();
private:
CHsvEuropeInstallation_mfinsort_Priv	*m_priv;
};

#endif

