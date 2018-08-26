#ifndef  _CHSVDVBTINSTALLATION_MSETTINGS_H
#define  _CHSVDVBTINSTALLATION_MSETTINGS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSettings.h>
#include <IHsvPower.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IPlfApiErrorIds.h>
#include <IHsvInstallation2.h>
#include <IHsvSortRoute.h>
#include <IString.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbTInstallation_msettings_Priv;
class CHsvDvbTInstallation_msettings
{
public:
ProvidesInterface<IHsvDVBSettings>	idvbset;

ProvidesInterface<IHsvPower>	isetpow;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvSortRoute>	sortroute;
RequiresInterface<IString>	str;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbTInstallation_msettings();
virtual ~CHsvDvbTInstallation_msettings();
private:
CHsvDvbTInstallation_msettings_Priv	*m_priv;
};

#endif

