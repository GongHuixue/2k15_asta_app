#ifndef  _CHSVCANALDIGITALINSTALLATION_MBACKGROUND_H
#define  _CHSVCANALDIGITALINSTALLATION_MBACKGROUND_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IEnable.h>
#include <IHsvDigitalScan.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvPower.h>
#include <IHsvSortNotify.h>
#include <IHsvStreamNotify.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvDVBSettings.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvInstallationNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IRealTimeKernel.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
class CHsvCanalDigitalInstallation_mBackground_Priv;
class CHsvCanalDigitalInstallation_mBackground
{
public:
ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvDigitalScan>	ibckg;

ProvidesInterface<IHsvSdmControlNotifyEx>	ibckgctrlN;

ProvidesInterface<IHsvPower>	ibckgpow;

ProvidesInterface<IHsvSortNotify>	sortN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvChannelLibReturnCodes>	chanret;
RequiresInterface<IHsvDVBSettings>	dvbset;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvStreamNotify>	idatastrapiN;
public:
CHsvCanalDigitalInstallation_mBackground();
virtual ~CHsvCanalDigitalInstallation_mBackground();
private:
CHsvCanalDigitalInstallation_mBackground_Priv	*m_priv;
};

#endif

