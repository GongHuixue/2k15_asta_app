#ifndef  _CHSVDVBEIT_H
#define  _CHSVDVBEIT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvDVBService.h>
#include <IHsvMpegServices.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvStreamNotify.h>
class CHsvDvbEIT_Priv;
class CHsvDvbEIT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvDVBService>	dvbsvc;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvStreamNotify>	strapiN;
public:
CHsvDvbEIT();
virtual ~CHsvDvbEIT();
private:
CHsvDvbEIT_Priv	*m_priv;
};

#endif

