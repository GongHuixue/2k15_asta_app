#ifndef  _CHSVDVBTMPEGINSTALLATION_MDIGACQ_H
#define  _CHSVDVBTMPEGINSTALLATION_MDIGACQ_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvCountryIds.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvDigitalScan.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortedTable2.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
class CHsvDvbtMpegInstallation_mdigacq_Priv;
class CHsvDvbtMpegInstallation_mdigacq
{
public:
ProvidesInterface<IHsvDigitalAcquisition>	idigacq;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvDigitalScan>	idigscan;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvDvbtMpegInstallation_mdigacq();
virtual ~CHsvDvbtMpegInstallation_mdigacq();
private:
CHsvDvbtMpegInstallation_mdigacq_Priv	*m_priv;
};

#endif

