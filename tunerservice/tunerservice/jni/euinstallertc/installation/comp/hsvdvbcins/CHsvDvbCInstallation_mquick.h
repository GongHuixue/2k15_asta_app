#ifndef  _CHSVDVBCINSTALLATION_MQUICK_H
#define  _CHSVDVBCINSTALLATION_MQUICK_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IEnable.h>
#include <IHsvStreamNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvInstallationNotify.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvMediaControl.h>
#include <IMemoryOperations.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbCInstallation_mquick_Priv;
class CHsvDvbCInstallation_mquick
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	iqctrlN;

ProvidesInterface<IEnable>	iqena;

ProvidesInterface<IHsvStreamNotify>	iqstrapiN;

ProvidesInterface<IHsvDigitalScan>	iquick;

ProvidesInterface<IHsvFrontEndApiNotify>	iquickfeN;

ProvidesInterface<IHsvPower>	iquickpow;

//Required interfaces
public:
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvDigitalScanNotify>	iquickN;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbCInstallation_mquick();
virtual ~CHsvDvbCInstallation_mquick();
private:
CHsvDvbCInstallation_mquick_Priv	*m_priv;
};

#endif

