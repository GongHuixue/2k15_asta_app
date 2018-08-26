#ifndef  _CHSVEUROPEINSTALLATION_MBLIZOOSORT_H
#define  _CHSVEUROPEINSTALLATION_MBLIZOOSORT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvHybridPresetSort.h>
//#include <IAppApiChannelLibReturnCodes.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
//#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
//#include <IProdApiFlashFileSystemDirectoryExEx.h>
//#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
//#include <IHsvAdvanceProgramIterator.h>
//#include <IMemoryOperations.h>
//#include <IHsvCookieNvmInfo.h>
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
class CHsvEuropeInstallation_mblizoosort_Priv;
class CHsvEuropeInstallation_mblizoosort
{
public:
ProvidesInterface<IHsvPower>	iblizoopow;

ProvidesInterface<IHsvHybridPresetSort>	iblizoosort;

//Required interfaces
public:
//RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPresetInstallationDiv>	div;
//RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
//RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
//RequiresInterface<IHsvDigitalAcquisition>	hsvdvbcins_digacq;
RequiresInterface<IHsvDVBSettings>	hsvdvbcins_dvbset;
//RequiresInterface<IHsvAdvanceProgramIterator>	iadvpgitr;
//RequiresInterface<IMemoryOperations>	memo;
//RequiresInterface<IHsvCookieNvmInfo>	nvmapps;
//RequiresInterface<IHsvCookieNvmInfo>	nvmcesvc;
//RequiresInterface<IHsvCookieNvmInfo>	nvmtxt;
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
CHsvEuropeInstallation_mblizoosort();
virtual ~CHsvEuropeInstallation_mblizoosort();
private:
CHsvEuropeInstallation_mblizoosort_Priv	*m_priv;
};

#endif

