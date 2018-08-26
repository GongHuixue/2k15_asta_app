#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_M_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDVBService.h>
#include <IHsvStream.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDemuxNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <IHsvCountryIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IPumpExSub.h>
#include <IHsvStreamFilterNotify.h>
#include <IHsvSatSystemSettings.h>
class CHsvDvbStreamingDataManager_m_Priv;
class CHsvDvbStreamingDataManager_m
{
public:
ProvidesInterface<IHsvDVBSIConfig>	conf;

ProvidesInterface<IHsvSdmControl2>	ctrl;

ProvidesInterface<IHsvSdmControlNotifyEx>	hsvdvbsi_ctrlN;

ProvidesInterface<IHsvDVBService>	hsvdvbsi_dvbsvc;

ProvidesInterface<IHsvSdmControlNotifyEx>	hsvsimplempeg_ctrlN;

ProvidesInterface<IHsvSdmControl2>	ictrl;

ProvidesInterface<IHsvStream>	ilclstrapi;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	pdmxsecfN;

ProvidesInterface<IHsvDemuxNotify>	phsvdmxN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDemuxNotify>	hsvdmxN;
RequiresInterface<IHsvDemuxSectionFilterNotify>	hsvdvbsi_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	hsvdvbsi_ena;
RequiresInterface<IHsvPower>	hsvdvbsi_pow;
RequiresInterface<IHsvStreamFilter>	hsvdvbsi_strmfltr;
RequiresInterface<IHsvSdmEnable>	hsvsimplempeg_enable;
RequiresInterface<IHsvPower>	hsvsimplempeg_pow;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvStream>	istrapi;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IHsvSatSystemSettings>	sysset;
public:
CHsvDvbStreamingDataManager_m();
virtual ~CHsvDvbStreamingDataManager_m();
private:
CHsvDvbStreamingDataManager_m_Priv	*m_priv;
};

#endif

