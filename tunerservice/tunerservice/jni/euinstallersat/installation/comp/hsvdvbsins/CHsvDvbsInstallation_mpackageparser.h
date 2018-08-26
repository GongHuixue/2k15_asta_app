#ifndef  _CHSVDVBSINSTALLATION_MPACKAGEPARSER_H
#define  _CHSVDVBSINSTALLATION_MPACKAGEPARSER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvPackageParser.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvPrescanParser.h>
#include <IHsvLanguageIds2.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvSatSystemSettings.h>
#include <ICesOperatorProfile.h>
#include <ICesOperatorProfileNotify.h>
#include <ICesCipCAMStatusNotify.h>
#include <ICesCipCAMStatus.h>
#include <IHsvSatelliteSettings.h>

class CHsvDvbsInstallation_mpackageparser_Priv;
class CHsvDvbsInstallation_mpackageparser
{
public:
ProvidesInterface<IHsvPower>	impackagepow;

ProvidesInterface<IHsvPackageParser>	ipackage;

ProvidesInterface<IHsvSdmControlNotifyEx>	ipackageparserctrlN;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	ipackageparsersatfrontendN;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<ICesCipCAMStatusNotify>	cipStatusN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvLanguageIds2>	lngids;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<ICesCipCAMStatus>	cipStatus;
RequiresInterface<IHsvSatelliteSettings>	dvbset;
public:
CHsvDvbsInstallation_mpackageparser();
virtual ~CHsvDvbsInstallation_mpackageparser();
private:
CHsvDvbsInstallation_mpackageparser_Priv	*m_priv;
};

#endif

