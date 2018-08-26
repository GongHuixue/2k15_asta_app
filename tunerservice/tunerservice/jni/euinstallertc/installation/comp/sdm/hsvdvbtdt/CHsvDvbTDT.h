#ifndef  _CHSVDVBTDT_H
#define  _CHSVDVBTDT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvComponentIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvDateTimeConversion.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallation2.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
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
RequiresInterface<IHsvComponentIds>	compids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvDateTimeConversion>	dtconv;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
public:
CHsvDvbTDT();
virtual ~CHsvDvbTDT();
private:
CHsvDvbTDT_Priv	*m_priv;
};

#endif

