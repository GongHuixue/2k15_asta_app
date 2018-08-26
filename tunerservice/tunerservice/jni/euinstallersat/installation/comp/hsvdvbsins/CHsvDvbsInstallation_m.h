#ifndef  _CHSVDVBSINSTALLATION_M_H
#define  _CHSVDVBSINSTALLATION_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvMiniPrescanNotify.h>
#include <IHsvSatelliteInstallationConstants.h>
#include <IHsvPower.h>
#include <IHsvSystemSettingsNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvStreamNotify.h>
#include <ISvcAudioControl4ExEx.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvMiniPrescan.h>
#include <IHsvPackageParser.h>
#include <IHsvSorting.h>
#include <IHsvPredefinedListCopy.h>
#include <IHsvPrescanParser.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvSatSystemSettings.h>
#include <ISvcVideoControl3.h>
#include <IHsvWindowDestinationMap.h>
#include <ICesOperatorProfileNotify.h>
#include <ICesCipCAMStatusNotify.h>

class CHsvDvbsInstallation_m_Priv;
class CHsvDvbsInstallation_m
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatelliteInstallationNotify>	iinsN;

ProvidesInterface<IHsvMiniPrescanNotify>	iminiprescanN;

ProvidesInterface<IHsvSatelliteInstallationConstants>	insconst;

ProvidesInterface<IHsvPower>	ipow;

ProvidesInterface<IHsvSystemSettingsNotify>	isyssetN;

ProvidesInterface<IHsvSatelliteInstallation>	pins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	satfeapiN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<ICesCipCAMStatusNotify>	cipStatusN;

//Required interfaces
public:
RequiresInterface<ISvcAudioControl4ExEx>	actl3;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsgeneric_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsgeneric_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsgeneric_plfApidvbsN;
RequiresInterface<IHsvSatelliteInstallation>	iaddremove;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;
RequiresInterface<IHsvSdmControlNotifyEx>	ibckctrlN;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvMiniPrescan>	iminiprescan;
RequiresInterface<IHsvSdmControlNotifyEx>	iminiprescanctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	iminiprescansatfrontendN;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvPackageParser>	ipackage;
RequiresInterface<IHsvSdmControlNotifyEx>	ipackagectrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	ipackageins;
RequiresInterface<IHsvSdmControlNotifyEx>	ipackageparserctrlN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	ipackageparsersatfrontendN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	ipackageplfApidvbsN;
RequiresInterface<IHsvSorting>	ipackagesort;
RequiresInterface<IHsvPredefinedListCopy>	ipredefcopy;
RequiresInterface<IHsvSatelliteInstallation>	iprescan;
RequiresInterface<IHsvSdmControlNotifyEx>	iprescanctrlN;
RequiresInterface<IHsvSdmControlNotifyEx>	isatipprescanctrlN;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvSatelliteFrontEndNotify>	iprescansatfrontendN;
RequiresInterface<IHsvSatelliteFrontEndNotify>	isatipprescansatfrontendN;
RequiresInterface<IHsvInstallationSigStrength>	isigstr;
RequiresInterface<IHsvStreamNotify>	istrapiN;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<ISvcVideoControl3>	vctl;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ICesOperatorProfileNotify>	ipackageopinsN;
RequiresInterface<ICesOperatorProfileNotify>	ipackageparseropinsN;
RequiresInterface<ICesCipCAMStatusNotify>	ipackageparsercipStatusN;
RequiresInterface<IHsvSatelliteInstallation>	isatipprescan;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbstricolor_plfApidvbsN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbstricolor_ctrlN;

public:
CHsvDvbsInstallation_m();
virtual ~CHsvDvbsInstallation_m();
private:
CHsvDvbsInstallation_m_Priv	*m_priv;
};

#endif

