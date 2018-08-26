#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvStreamNotify.h>
#include <IHsvStream.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSdmEnable.h>
class CHsvDvbStreamingDataManager_mstrapi_Priv;
class CHsvDvbStreamingDataManager_mstrapi
{
public:
ProvidesInterface<IHsvStreamNotify>	hsvdvbsi_strapiN;

ProvidesInterface<IHsvStreamNotify>	hsvsimplempeg_strapiN;

ProvidesInterface<IHsvStream>	istrapi;

//Required interfaces
public:
RequiresInterface<IHsvStream>	ibatstrapi;
RequiresInterface<IHsvStream>	ifntstrapi;
RequiresInterface<IHsvStream>	ifststrapi;
RequiresInterface<IHsvStream>	ilclstrapi;
RequiresInterface<IHsvStream>	initstrapi;
RequiresInterface<IHsvStream>	isdtstrapi;
RequiresInterface<IHsvStream>	ipostcodestrapi;
RequiresInterface<IHsvStream>	isimplepatstrapi;
RequiresInterface<IHsvStream>	isimplepmtstrapi;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvStream>	icamnitstrapi;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvSdmEnable>  chsvdvbsdt_Freesatena;
RequiresInterface<IHsvStream>	isgtstrapi;
RequiresInterface<IHsvStream>	itotstrapi;
public:
CHsvDvbStreamingDataManager_mstrapi();
virtual ~CHsvDvbStreamingDataManager_mstrapi();
private:
CHsvDvbStreamingDataManager_mstrapi_Priv	*m_priv;
};

#endif

