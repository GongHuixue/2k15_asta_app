#ifndef  _CHSVDVBCINSTALLATION_MSETTINGS_H
#define  _CHSVDVBCINSTALLATION_MSETTINGS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSettings.h>
#include <IHsvPower.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvSortRoute.h>
#include <IString.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbCInstallation_msettings_Priv;
class CHsvDvbCInstallation_msettings
{
public:
ProvidesInterface<IHsvDVBSettings>	idvbset;

ProvidesInterface<IHsvPower>	isetpow;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<ICesCityIds>	cityids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvSortRoute>	sortroute;
RequiresInterface<IString>	str;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbCInstallation_msettings();
virtual ~CHsvDvbCInstallation_msettings();
private:
CHsvDvbCInstallation_msettings_Priv	*m_priv;
};

#endif

