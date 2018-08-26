#ifndef  _CHSVDVBCAMINSTALLATION_MDATAACQ_H
#define  _CHSVDVBCAMINSTALLATION_MDATAACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalAcquisition.h>
#include <IProdApiClockEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvCamScanHelper.h>
#include <IHsvDigitalScan.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvInstallation2.h>
#include <IHsvCamPresetSort.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
#include<IMultiLingualStringConversion.h>
#include <IHsvDVBSettings.h>
#include <IHsvCharSetUtility2.h>
class CHsvDvbCamInstallation_mDataAcq_Priv;
class CHsvDvbCamInstallation_mDataAcq
{
public:
ProvidesInterface<IHsvDigitalAcquisition>	idataacq;
ProvidesInterface<IHsvCamScanHelper>	pcamhelper;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvCamScanHelper>	icamhelper;
RequiresInterface<IHsvDigitalScan>	iins;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvCamPresetSort>	sort;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IMultiLingualStringConversion>	ling;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
public:
CHsvDvbCamInstallation_mDataAcq();
virtual ~CHsvDvbCamInstallation_mDataAcq();
private:
CHsvDvbCamInstallation_mDataAcq_Priv	*m_priv;
};

#endif

