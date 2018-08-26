#ifndef  _CHSVDVBBAT_H
#define  _CHSVDVBBAT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvLanguageIds2.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSatelliteSettings.h>
class CHsvDvbBAT_Priv;
class CHsvDvbBAT
{
public:
ProvidesInterface<IHsvSortedTableConfigurationEx>	batDetailsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	batECNconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	batlcn2conf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	batlcnconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	batlinkmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	batsrvclstmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	batFreesatSrvGroupconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batFreesatInfoLocationconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batFreesatLCNconf;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;
ProvidesInterface<IHsvLanguageIds2> langids;


//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IHsvSatelliteSettings> 			itricolorsettings;
public:
CHsvDvbBAT();
virtual ~CHsvDvbBAT();
private:
CHsvDvbBAT_Priv	*m_priv;
};

#endif

