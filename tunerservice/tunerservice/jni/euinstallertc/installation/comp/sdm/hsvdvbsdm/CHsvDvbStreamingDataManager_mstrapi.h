#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvStreamNotify.h>
#include <IHsvStream.h>
class CHsvDvbStreamingDataManager_mstrapi_Priv;
class CHsvDvbStreamingDataManager_mstrapi
{
public:
ProvidesInterface<IHsvStreamNotify>	hsvdvbcamsdm_strapiN;
ProvidesInterface<IHsvStreamNotify>	hsvdvbsi_strapiN;

ProvidesInterface<IHsvStreamNotify>	hsvmpeg_strapiN;

ProvidesInterface<IHsvStream>	istrapi;

//Required interfaces
public:
RequiresInterface<IHsvStream>	icamnitstrapi;
RequiresInterface<IHsvStream>	ieitstrapi;
RequiresInterface<IHsvStream>	ilclstrapi;
RequiresInterface<IHsvStream>	initstrapi;
RequiresInterface<IHsvStream>	ipatstrapi;
RequiresInterface<IHsvStream>	ipmtstrapi;
RequiresInterface<IHsvStream>	isdtstrapi;
RequiresInterface<IHsvStream>	itdtstrapi;
RequiresInterface<IHsvStream>	itotstrapi;
RequiresInterface<IHsvStreamNotify>	strapiN;
public:
CHsvDvbStreamingDataManager_mstrapi();
virtual ~CHsvDvbStreamingDataManager_mstrapi();
private:
CHsvDvbStreamingDataManager_mstrapi_Priv	*m_priv;
};

#endif

