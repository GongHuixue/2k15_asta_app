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
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvSdmDiv.h>
#include <IHsvSystemSettings.h>
#include <IHsvSdmControlNotifyEx.h>


class CHsvDvbTOT_Priv;
class CHsvDvbTOT
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvSortedTableConfigurationEx>	totmainconf;

ProvidesInterface<IHsvSdmEnable>    Freesatena;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvDateTimeConversion>	dtconv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;


public:
CHsvDvbTOT();
virtual ~CHsvDvbTOT();
private:
CHsvDvbTOT_Priv	*m_priv;
};

#endif
