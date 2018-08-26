#ifndef  _CHSVDVBTOT_H
#define  _CHSVDVBTOT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IDateTime.h>
#include <IHsvDateTimeConversion.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallation2.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IAppApiSystemSettings5.h>
class CHsvDvbTOT_Priv;
class CHsvDvbTOT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvSortedTableConfigurationEx>	totmainconf;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IDateTime>	dt;
RequiresInterface<IHsvDateTimeConversion>	dtconv;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IAppApiSystemSettings5>	sysset5;
public:
CHsvDvbTOT();
virtual ~CHsvDvbTOT();
private:
CHsvDvbTOT_Priv	*m_priv;
};

#endif

