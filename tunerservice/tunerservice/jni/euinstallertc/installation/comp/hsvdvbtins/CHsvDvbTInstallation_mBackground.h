#ifndef  _CHSVDVBTINSTALLATION_MBACKGROUND_H
#define  _CHSVDVBTINSTALLATION_MBACKGROUND_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IEnable.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisition.h>
#include <IPumpEngine.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvProgramSelection2.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvStream.h>
#include <IHsvInstallationNotify.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvDVBSettings.h>
#include <IHsvCountryIds.h>
#include <IHsvProgramData3.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IHsvInstallationUtility.h>
#include <IHsvHybridPresetSort.h>
class CHsvDvbTInstallation_mBackground_Priv;
class CHsvDvbTInstallation_mBackground
{
public:
ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvSdmControlNotifyEx>	ibctrlN;

ProvidesInterface<IHsvPower>	ibpow;

ProvidesInterface<IHsvStreamNotify>	ibstrapiN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;


//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationNotify>	installN;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvDVBSettings>	idvbset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvProgramData3>	pgdat;
public:
CHsvDvbTInstallation_mBackground();
virtual ~CHsvDvbTInstallation_mBackground();
private:
CHsvDvbTInstallation_mBackground_Priv	*m_priv;
};

#endif

