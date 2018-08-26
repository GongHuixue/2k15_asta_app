#ifndef  _CHSVMPEGDATAMANAGER_H
#define  _CHSVMPEGDATAMANAGER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmEnable.h>
#include <IInit.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMpegSections.h>
#include <IHsvMpegServices.h>
#include <IHsvStream.h>
#include <IHsvPower.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvMpegControlNotify.h>
#include <IHsvMpegSectionsNotify.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IRealTimeKernel.h>
#include <IHsvSdmDiv.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvStreamNotify.h>
class CHsvMpegDataManager_Priv;
class CHsvMpegDataManager
{
public:
ProvidesInterface<IHsvSortedTableConfigurationEx>	audioinfoconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	audioinfoconfmain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	basicpidinfoconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	basicpidinfoconfmain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	componenttaginfoaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	componenttaginfomain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	databroadcastinfoaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	databroadcastinfomain;

ProvidesInterface<IHsvSdmEnable>	enable;

ProvidesInterface<IInit>	init;

ProvidesInterface<IHsvLanguageIds2>	langids;

ProvidesInterface<IHsvMpegSections>	mpegsecn;

ProvidesInterface<IHsvMpegServices>	mpegserv;

ProvidesInterface<IHsvStream>	patstrapi;

ProvidesInterface<IHsvStream>	pmtstrapi;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSortedTableConfigurationEx>	subtitleconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	subtitleconfmain;

ProvidesInterface<IHsvSortedTableConfigurationEx>	teletextconfaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	teletextconfmain;

//Required interfaces
public:
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvMpegControlNotify>	mpegN;
RequiresInterface<IHsvMpegSectionsNotify>	mpegsecnN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSdmDiv>	sdmdiv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
public:
CHsvMpegDataManager();
virtual ~CHsvMpegDataManager();
private:
CHsvMpegDataManager_Priv	*m_priv;
};

#endif

