#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbStreamingDataManager_m.h>
#include <CHsvDvbStreamingDataManager_mstrapi.h>
#include <CHsvDvbCamSdm.h>
#include <CHsvDvbSiDataManager.h>
#include <CHsvMpegDataManager.h>
#include <IHsvSdmEnable.h>
#include <IHsvSdmControl2.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDateTimeConversion.h>
#include <IHsvDemuxNotify.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMpegSections.h>
#include <IHsvMpegServices.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IDateTime.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallation2.h>
#include <IHsvMpegControlNotify.h>
#include <IHsvMpegSectionsNotify.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramSelection2.h>
#include <IPumpExSub.h>
#include <IRealTimeKernel.h>
#include <IHsvDemuxSectionFilter2.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvStreamFilterNotify.h>
#include <IHsvTcSystemSettings.h>
#include <IAppApiSystemSettings5.h>

class CHsvDvbStreamingDataManager
{
public:
virtual ~CHsvDvbStreamingDataManager(){}

//Contained Modules
private:
CHsvDvbStreamingDataManager_m m;
CHsvDvbStreamingDataManager_mstrapi mstrapi;
//Contained Components
private:
CHsvDvbCamSdm hsvdvbcamsdm;
CHsvDvbSiDataManager hsvdvbsi;
CHsvMpegDataManager hsvmpeg;
public:
ProvidesInterface<IHsvSdmEnable>	camena;
ProvidesInterface<IHsvSdmControl2>	ctrl;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvDateTimeConversion>	dtconv;

ProvidesInterface<IHsvDemuxNotify>	hsvdmxN;

ProvidesInterface<IHsvLanguageIds2>	lngids;

ProvidesInterface<IHsvMpegSections>	mpegsecn;

ProvidesInterface<IHsvMpegServices>	mpegserv;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

ProvidesInterface<IHsvCamScanHelper>	camScanparser;
//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCharSetUtility2>	charsetutil2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvPower>	dmxpow;
RequiresInterface<IDateTime>	dt;
RequiresInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvMpegControlNotify>	mpegN;
RequiresInterface<IHsvMpegSectionsNotify>	mpegsecnN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvDemuxSectionFilter2>	secfltr;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IAppApiSystemSettings5>	sysset5;
private:
Pumpdefines(CHsvDvbStreamingDataManager);
DEMUX_DEFINES(CHsvDvbStreamingDataManager,secfltr);

public:
CHsvDvbStreamingDataManager()
{
m.hsvdvbsi_pow	=	hsvdvbsi.pow;
m.hsvdvbsi_ena	=	hsvdvbsi.ena;
dtconv	=	hsvdvbsi.dtconv;
hsvdvbsi.ins	=	ins;
hsvdvbsi.dt	=	dt;
hsvdvbsi.sysset5	=	sysset5;
hsvdvbsi.sysset	=	sysset;
hsvdvbsi.srtdbids	=	dvbsrtdbids;
hsvdvbsi.srtdb	=	srtdb2;
hsvdvbsi.secf	=	secfltr;
hsvdvbsi.mpegserv	=	hsvmpeg.mpegserv;
hsvdvbsi.conf	=	m.conf;
hsvdvbsi.cids	=	cids;
hsvdvbsi.charsetutil	=	charsetutil;
hsvdvbsi.charsetutil2	=	charsetutil2;
hsvdvbsi.ctrlN	=	m.hsvdvbsi_ctrlN;
hsvdvbsi.dvbsvc	=	m.hsvdvbsi_dvbsvc;
hsvdvbsi.eurdiv	=	eurdiv;
m.hsvmpeg_mpegsecn	=	hsvmpeg.mpegsecn;
mpegsecn	=	hsvmpeg.mpegsecn;
lngids	=	hsvmpeg.langids;
mpegserv	=	hsvmpeg.mpegserv;
m.hsvmpeg_enable	=	hsvmpeg.enable;
m.hsvmpeg_pow	=	hsvmpeg.pow;
m.cids	=	cids;
m.sysset	=	sysset;
hsvmpeg.srtdbids	=	srtdbids;
hsvmpeg.srtdb	=	srtdb2;
hsvmpeg.sec	=	secfltr;
hsvmpeg.sdmdiv	=	div;
hsvmpeg.mpegsecnN	=	m.hsvmpeg_mpegsecnN;
hsvmpeg.mpegN	=	mpegN;
hsvmpeg.rtk	=	rtk;
hsvmpeg.pgdat	=	pgdat;
hsvmpeg.pgsel	=	pgsel;
hsvdvbsi.pgdat	=	pgdat;
hsvdvbsi.pgsel	=	pgsel;
hsvmpeg.eurdiv	=	eurdiv;
hsvmpeg.pmp	=	pmp;
hsvmpeg.pen	=	pen;
hsvdvbsi.pmp	=	pmp;
hsvdvbsi.pen	=	pen;
m.secfltr	=	secfltr;
m.dmxena	=	dmxena;
m.dmxpow	=	dmxpow;
hsvdmxN	=	m.hsvdmxN;
dmxsecfN	=	m.dmxsecfN;
m.hsvdvbsi_dmxsecfN	=	hsvdvbsi.dmxsecfN;
m.div	=	div;
m.ctrlN	=	ctrlN;
m.mpegsecnN	=	mpegsecnN;
m.pen	=	pen;
m.ctrlpen	=	ctrlpen;
m.pmp	=	pmp;
ctrl	=	m.ctrl;
pow	=	m.pow;
strapi	=	mstrapi.istrapi;
m.istrapi	=	mstrapi.istrapi;
mstrapi.strapiN	=	strapiN;
hsvmpeg.strapiN	=	mstrapi.hsvmpeg_strapiN;
hsvdvbsi.strapiN	=	mstrapi.hsvdvbsi_strapiN;
mstrapi.initstrapi	=	hsvdvbsi.nitstrapi;
mstrapi.isdtstrapi	=	hsvdvbsi.sdtstrapi;
mstrapi.ieitstrapi	=	hsvdvbsi.eitstrapi;
mstrapi.itdtstrapi	=	hsvdvbsi.tdtstrapi;
mstrapi.itotstrapi	=	hsvdvbsi.totstrapi;
mstrapi.ipmtstrapi	=	hsvmpeg.pmtstrapi;
mstrapi.ipatstrapi	=	hsvmpeg.patstrapi;
mstrapi.ilclstrapi	=	m.ilclstrapi;
strmfltr	=	m.strmfltr;
m.strmfltrN	=	strmfltrN;
m.hsvdvbsi_strmfltr	=	hsvdvbsi.strmfltr;
m.eurdiv	=	eurdiv;
m.ins	=	ins;
camena	=	hsvdvbcamsdm.ena;
mstrapi.icamnitstrapi	=	hsvdvbcamsdm.strapi;
m.hsvdvbcamsdm_pow	=	hsvdvbcamsdm.pow;
m.hsvdvbcamsdm_strmfltr	=	hsvdvbcamsdm.strmfltr;
hsvdvbcamsdm.strapiN	=	mstrapi.hsvdvbcamsdm_strapiN;
hsvdvbcamsdm.srtdbids	=	dvbsrtdbids;
hsvdvbcamsdm.srtdb	=	srtdb2;
hsvdvbcamsdm.mpegserv	=	hsvmpeg.mpegserv;
hsvdvbcamsdm.charsetutil	=	charsetutil2;
camScanparser				=	hsvdvbcamsdm.camScanparser;
}

};

#endif

