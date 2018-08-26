#ifndef  _CHSVEUROPEINSTALLATION_MCABSORT_H
#define  _CHSVEUROPEINSTALLATION_MCABSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvHybridPresetSort.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvAdvanceProgramIterator.h>
#include <IMemoryOperations.h>
#include <IHsvCookieNvmInfo.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IRealTimeKernel.h>
#include <IHsvSortNotify.h>
#include <IString.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvAnalogInstallation.h>
class CHsvEuropeInstallation_mcabsort_Priv;
class CHsvEuropeInstallation_mcabsort
{
public:
ProvidesInterface<IHsvPower>	icabpow;

ProvidesInterface<IHsvHybridPresetSort>	idvbcsort;

//Required interfaces
public:
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvDigitalAcquisition>	hsvdvbcins_digacq;
RequiresInterface<IHsvDVBSettings>	hsvdvbcins_dvbset;
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
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSortNotify>	sortN;
RequiresInterface<IString>	str;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvAnalogInstallation>	hsvprins_prins;
public:
CHsvEuropeInstallation_mcabsort();
virtual ~CHsvEuropeInstallation_mcabsort();
private:
CHsvEuropeInstallation_mcabsort_Priv	*m_priv;
};

#endif

