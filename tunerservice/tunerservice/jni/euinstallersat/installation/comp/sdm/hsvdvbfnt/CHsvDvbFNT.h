#ifndef  _CHSVDVBFNT_H
#define  _CHSVDVBFNT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
class CHsvDvbFNT_Priv;
class CHsvDvbFNT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	fntlcnconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	fntsatellitedsdconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	fntsrvclstconf;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
public:
CHsvDvbFNT();
virtual ~CHsvDvbFNT();
private:
CHsvDvbFNT_Priv	*m_priv;
};

#endif

