#ifndef  _CHSVZIGGOINSTALLATION_MDATAACQ_H
#define  _CHSVZIGGOINSTALLATION_MDATAACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalAcquisition.h>
#include <IProdApiClockEx.h>
#include <IHsvDVBSettings.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvDigitalScan.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvInstallation2.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvStreamFilter.h>
#include <IHsvStreamNotify.h>
class CHsvZiggoInstallation_mDataAcq_Priv;
class CHsvZiggoInstallation_mDataAcq
{
public:
ProvidesInterface<IHsvDigitalAcquisition>	idataacq;
ProvidesInterface<IHsvStreamNotify>	strapiN;
//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvDVBSettings>	dvbset;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvDigitalScan>	ibckg;
RequiresInterface<IHsvDigitalScan>	iins;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvStreamFilter>	strmfltr;
public:
CHsvZiggoInstallation_mDataAcq();
virtual ~CHsvZiggoInstallation_mDataAcq();
private:
CHsvZiggoInstallation_mDataAcq_Priv	*m_priv;
};

#endif

