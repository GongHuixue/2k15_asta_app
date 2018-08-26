#ifndef  _CHSVDVBCAMNIT_H
#define  _CHSVDVBCAMNIT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCamDataParser.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
class CHsvDvbCamNIT_Priv;
class CHsvDvbCamNIT
{
public:
ProvidesInterface<IHsvCamDataParser>	camdataparser;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitsatellitedsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	optunesatellitedsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitcontentlabelconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitlinkageinfoconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitserviceconf;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
public:
CHsvDvbCamNIT();
virtual ~CHsvDvbCamNIT();
private:
CHsvDvbCamNIT_Priv	*m_priv;
};

#endif

