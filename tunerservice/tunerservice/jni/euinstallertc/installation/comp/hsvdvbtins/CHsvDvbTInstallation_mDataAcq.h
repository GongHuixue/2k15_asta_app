#ifndef  _CHSVDVBTINSTALLATION_MDATAACQ_H
#define  _CHSVDVBTINSTALLATION_MDATAACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvPower.h>
#include <IHsvSdmControlNotify.h>
#include <IProdApiClockEx.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvCountryIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvPool.h>
#include <IHsvDVBSettings.h>
#include <IHsvDigitalScan.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLanguageIds.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortNotify.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbTInstallation_mDataAcq_Priv;
class CHsvDvbTInstallation_mDataAcq
{
public:
ProvidesInterface<IHsvDigitalScanNotify>	digscanN;

ProvidesInterface<IHsvDigitalAcquisition>	idataacq;

ProvidesInterface<IHsvPower>	idatapow;

ProvidesInterface<IHsvSdmControlNotify>	idvbtqctrlN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvDigitalScan>	idvbt;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLanguageIds>	langids;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortNotify>	sortN;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbTInstallation_mDataAcq();
virtual ~CHsvDvbTInstallation_mDataAcq();
private:
CHsvDvbTInstallation_mDataAcq_Priv	*m_priv;
};

#endif

