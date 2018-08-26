#ifndef  _CHSVDVBCINSTALLATION_MFULL_H
#define  _CHSVDVBCINSTALLATION_MFULL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IEnable.h>
#include <IHsvStreamNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvProgramDatabaseConstants.h>
class CHsvDvbCInstallation_mfull_Priv;
class CHsvDvbCInstallation_mfull
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ifctrlN;

ProvidesInterface<IEnable>	ifena;

ProvidesInterface<IHsvStreamNotify>	ifstrapiN;

ProvidesInterface<IHsvDigitalScan>	ifull;

ProvidesInterface<IHsvFrontEndApiNotify>	ifullfeN;

ProvidesInterface<IHsvPower>	ifullpow;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvDigitalScanNotify>	ifullN;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
public:
CHsvDvbCInstallation_mfull();
virtual ~CHsvDvbCInstallation_mfull();
private:
CHsvDvbCInstallation_mfull_Priv	*m_priv;
};

#endif

