#ifndef  _CHSVDVBSINSTALLATION_MSATIPPRESCAN_H
#define  _CHSVDVBSINSTALLATION_MSATIPPRESCAN_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalScanData.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvPackageParser.h>
#include <IHsvPrescanParser.h>
#include <IHsvInstallationSigStrength.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbsInstallation_msatipprescan_Priv;
class CHsvDvbsInstallation_msatipprescan
{
public:
ProvidesInterface<IHsvSatelliteInstallation>	iprescan;

ProvidesInterface<IHsvSdmControlNotifyEx>	iprescanctrlN;

ProvidesInterface<IHsvDigitalScanData>	iprescandata;

ProvidesInterface<IHsvPower>	iprescanpow;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	iprescansatfrontendN;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvPackageParser>	ipackage;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbsInstallation_msatipprescan();
virtual ~CHsvDvbsInstallation_msatipprescan();
private:
CHsvDvbsInstallation_msatipprescan_Priv	*m_priv;
};

#endif

