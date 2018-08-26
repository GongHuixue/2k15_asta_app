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
#include <IHsvInstallation2.h>
#include <IHsvMpegServices.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvTcSystemSettings.h>
class CHsvDvbNIT_Priv;
class CHsvDvbNIT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitcablemainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitcablesubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitfreqlistconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nithdslcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2mainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2subconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcnsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinkmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlinksubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitntwkidconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvcatrbmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitsrvclstsubconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nittargetregionconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nittargetregionnameconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nittsrelocatemainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitlcn2favoriteconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	nitactualtsidconf;


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
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvDvbNIT();
virtual ~CHsvDvbNIT();
private:
CHsvDvbNIT_Priv	*m_priv;
};

#endif

