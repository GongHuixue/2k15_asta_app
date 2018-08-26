#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_M_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDemuxNotify.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDVBService.h>
#include <IHsvMpegSectionsNotify.h>
#include <IHsvStream.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <IHsvCountryIds.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvMpegSections.h>
#include <IHsvInstallation2.h>
#include <IPumpExSub.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvStreamFilterNotify.h>
#include <IHsvTcSystemSettings.h>
class CHsvDvbStreamingDataManager_m_Priv;
class CHsvDvbStreamingDataManager_m
{
public:
ProvidesInterface<IHsvDVBSIConfig>	conf;

ProvidesInterface<IHsvSdmControl2>	ctrl;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvDemuxNotify>	hsvdmxN;

ProvidesInterface<IHsvSdmControlNotifyEx>	hsvdvbsi_ctrlN;

ProvidesInterface<IHsvDVBService>	hsvdvbsi_dvbsvc;

ProvidesInterface<IHsvMpegSectionsNotify>	hsvmpeg_mpegsecnN;

ProvidesInterface<IHsvStream>	ilclstrapi;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvPower>	dmxpow;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvPower>	hsvdvbcamsdm_pow;
RequiresInterface<IHsvStreamFilter>	hsvdvbcamsdm_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	hsvdvbsi_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	hsvdvbsi_ena;
RequiresInterface<IHsvPower>	hsvdvbsi_pow;
RequiresInterface<IHsvStreamFilter>	hsvdvbsi_strmfltr;
RequiresInterface<IHsvSdmEnable>	hsvmpeg_enable;
RequiresInterface<IHsvMpegSections>	hsvmpeg_mpegsecn;
RequiresInterface<IHsvPower>	hsvmpeg_pow;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvStream>	istrapi;
RequiresInterface<IHsvMpegSectionsNotify>	mpegsecnN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvDemuxSectionFilter2>	secfltr;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvDvbStreamingDataManager_m();
virtual ~CHsvDvbStreamingDataManager_m();
private:
CHsvDvbStreamingDataManager_m_Priv	*m_priv;
};

#endif

