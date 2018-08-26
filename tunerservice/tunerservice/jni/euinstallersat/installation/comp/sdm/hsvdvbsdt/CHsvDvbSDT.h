#ifndef  _CHSVDVBSDT_H
#define  _CHSVDVBSDT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPower.h>
#include <IHsvSDTReset.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSdmDiv.h>
#include <IHsvDVBService.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSdmControl2.h>
class CHsvDvbSDT_Priv;
class CHsvDvbSDT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	linkmainconf;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSDTReset>	sdtena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	sdtmainconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	sdtsubconf;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

ProvidesInterface<IHsvSdmEnable>    Freesatena;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvDVBService>	dvbsvc;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvStream>	ipmtstrapi;
public:
CHsvDvbSDT();
virtual ~CHsvDvbSDT();
private:
CHsvDvbSDT_Priv	*m_priv;
};

#endif

