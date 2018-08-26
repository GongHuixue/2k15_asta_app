#ifndef  _CHSVDVBCINSTALLATION_MGRID_H
#define  _CHSVDVBCINSTALLATION_MGRID_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IEnable.h>
#include <IHsvDigitalScan.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
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
#include <IHsvWindowDestinationMap.h>
class CHsvDvbCInstallation_mgrid_Priv;
class CHsvDvbCInstallation_mgrid
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	igctrlN;

ProvidesInterface<IEnable>	igena;

ProvidesInterface<IHsvDigitalScan>	igrid;

ProvidesInterface<IHsvFrontEndApiNotify>	igridfeN;

ProvidesInterface<IHsvPower>	igridpow;

ProvidesInterface<IHsvStreamNotify>	igstrapiN;

//Required interfaces
public:
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvDigitalScanNotify>	igridN;
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
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbCInstallation_mgrid();
virtual ~CHsvDvbCInstallation_mgrid();
private:
CHsvDvbCInstallation_mgrid_Priv	*m_priv;
};

#endif

