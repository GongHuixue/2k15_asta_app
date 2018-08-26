#ifndef  _CHSVSIMPLEMPEGDATAMANAGER_H
#define  _CHSVSIMPLEMPEGDATAMANAGER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
#include <IHsvSdmDiv.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatelliteInstallation.h>

class CHsvSimpleMpegDataManager_Priv;
class CHsvSimpleMpegDataManager
{
public:
ProvidesInterface<IHsvSdmEnable>	enable;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	simplepatstrapi;

ProvidesInterface<IHsvSortedTableConfigurationEx>	simplepmtinfoaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	simplepmtinfomain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	simplepmtFreesatTunnelledInfo;
ProvidesInterface<IHsvStream>	simplepmtstrapi;

//Required interfaces
public:
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSdmDiv>	sdmdiv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSatelliteInstallation>	ins;

public:
CHsvSimpleMpegDataManager();
virtual ~CHsvSimpleMpegDataManager();
private:
CHsvSimpleMpegDataManager_Priv	*m_priv;
};

#endif

