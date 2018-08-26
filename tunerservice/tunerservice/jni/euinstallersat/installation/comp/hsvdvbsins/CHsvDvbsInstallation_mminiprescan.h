#ifndef  _CHSVDVBSINSTALLATION_MMINIPRESCAN_H
#define  _CHSVDVBSINSTALLATION_MMINIPRESCAN_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvMiniPrescan.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvMiniPrescanNotify.h>
#include <IHsvPackageParser.h>
#include <IHsvPrescanParser.h>
#include <IHsvInstallationSigStrength.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvSatelliteInstallation.h>
#include <IPumpExSub.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbsInstallation_mminiprescan_Priv;
class CHsvDvbsInstallation_mminiprescan
{
public:
ProvidesInterface<IHsvMiniPrescan>	iminiprescan;

ProvidesInterface<IHsvSdmControlNotifyEx>	iminiprescanctrlN;

ProvidesInterface<IHsvPower>	iminiprescanpow;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	iminiprescansatfrontendN;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvMiniPrescanNotify>	iminiprescanN;
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
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbsInstallation_mminiprescan();
virtual ~CHsvDvbsInstallation_mminiprescan();
private:
CHsvDvbsInstallation_mminiprescan_Priv	*m_priv;
};

#endif

