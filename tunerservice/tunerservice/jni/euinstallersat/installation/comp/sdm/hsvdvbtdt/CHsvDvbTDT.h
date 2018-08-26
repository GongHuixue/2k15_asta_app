#ifndef  _CHSVDVBTDT_H
#define  _CHSVDVBTDT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CMwBase.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvComponentIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvDateTimeConversion.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvStreamNotify.h>
#include <IHsvSdmControlNotifyEx.h>

class CHsvDvbTDT_Priv;
class CHsvDvbTDT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

//Required interfaces
public:

RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvDateTimeConversion>	dtconv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;


public:
CHsvDvbTDT();
virtual ~CHsvDvbTDT();
private:
CHsvDvbTDT_Priv	*m_priv;
};

#endif

