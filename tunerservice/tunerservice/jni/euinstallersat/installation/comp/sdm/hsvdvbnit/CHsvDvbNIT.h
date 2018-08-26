#ifndef  _CHSVDVBNIT_H
#define  _CHSVDVBNIT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSdmControl2.h>
class CHsvDvbNIT_Priv;
class CHsvDvbNIT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitHeadEndFrequencyListconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitfreqlistconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2mainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2subconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn3mainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinkmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinksubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitntwkidconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsatellitedsdconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitFreesatLinkageconf;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IHsvSdmControl2>	ctrl;
public:
CHsvDvbNIT();
virtual ~CHsvDvbNIT();
private:
CHsvDvbNIT_Priv	*m_priv;
};

#endif

