#ifndef  _CHSVDVBCINSTALLATION_MDATAACQ_H
#define  _CHSVDVBCINSTALLATION_MDATAACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvDigitalAcquisition.h>
#include <IProdApiClockEx.h>
#include <IHsvCountryIds.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvDVBSettings.h>
#include <IHsvDigitalScan.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvDvbMplDiv.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortNotify.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbCInstallation_mDataAcq_Priv;
class CHsvDvbCInstallation_mDataAcq
{
public:
ProvidesInterface<IHsvPower>	iacqpow;

ProvidesInterface<IHsvStreamNotify>	iacqstrapiN;

ProvidesInterface<IHsvDigitalAcquisition>	idataacq;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvDigitalScan>	ifull;
RequiresInterface<IHsvDigitalScan>	igrid;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationNotify>	installN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvDigitalScan>	iquick;
RequiresInterface<IHsvDvbMplDiv>	mpldiv;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortNotify>	sortN;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbCInstallation_mDataAcq();
virtual ~CHsvDvbCInstallation_mDataAcq();
private:
CHsvDvbCInstallation_mDataAcq_Priv	*m_priv;
};

#endif

