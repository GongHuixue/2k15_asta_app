#ifndef  _CHSVDVBSFRANSAT_MBCKGND_H
#define  _CHSVDVBSFRANSAT_MBCKGND_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvPower.h>
#include <ITvPlatformResourceNotify.h>
#include <IHsvStreamNotify.h>
#include <IProdApiSystemStateObserverNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvStream.h>
class CHsvDvbsFransat_mBckgnd_Priv;
class CHsvDvbsFransat_mBckgnd
{
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;

ProvidesInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;

ProvidesInterface<IHsvPower>	ibckgndpow;

ProvidesInterface<ITvPlatformResourceNotify>	plfresN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IProdApiSystemStateObserverNotify>	sysstateN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IProdApiSystemStateObserverExExExEx>	observer;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvStream>	strapi;
public:
CHsvDvbsFransat_mBckgnd();
virtual ~CHsvDvbsFransat_mBckgnd();
private:
CHsvDvbsFransat_mBckgnd_Priv	*m_priv;
};

#endif

