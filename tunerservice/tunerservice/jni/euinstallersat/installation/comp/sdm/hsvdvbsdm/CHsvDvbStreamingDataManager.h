#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbStreamingDataManager_m.h>
#include <CHsvDvbStreamingDataManager_mstrapi.h>
#include <CHsvDvbCamNIT.h>
#include <CHsvDvbSiDataManager.h>
#include <CHsvSimpleMpegDataManager.h>
#include <IHsvSdmControl2.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDemuxNotify.h>
#include <IHsvPower.h>
#include <IHsvSDTReset.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IPumpEngine.h>
#include <IHsvSdmDiv.h>
#include <IHsvSdmEnable.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IPumpExSub.h>
#include <IRealTimeKernel.h>
#include <IHsvDemuxSectionFilter2.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvStreamFilterNotify.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSatelliteSettings.h>

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
CHsvDvbSiDataManager hsvdvbsi;
CHsvSimpleMpegDataManager hsvsimplempeg;
public:
ProvidesInterface<IHsvSdmControl2>	ctrl;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	pdmxsecfN;

ProvidesInterface<IHsvDemuxNotify>	phsvdmxN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSDTReset>	sdtena;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

ProvidesInterface<IHsvCamDataParser>	camdataparser;

ProvidesInterface<IHsvSdmEnable>	camnitena;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCharSetUtility2>	charsetutil2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	ctrlpen;
RequiresInterface<IHsvSdmDiv>	div;
RequiresInterface<IHsvSdmEnable>	dmxena;
RequiresInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;
RequiresInterface<IHsvDvbSiSortedTableIds>	dvbsrtdbids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvDemuxNotify>	hsvdmxN;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvDemuxSectionFilter2>	secf;
RequiresInterface<IHsvSortedTable2>	srtdb2;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvStreamFilterNotify>	strmfltrN;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IHsvSatelliteSettings>  itricolorsettings;

private:
Pumpdefines(CHsvDvbStreamingDataManager);
DEMUX_DEFINES(CHsvDvbStreamingDataManager,secf);

public:
CHsvDvbStreamingDataManager()
{
m.hsvdvbsi_pow	=	hsvdvbsi.pow;
m.hsvdvbsi_ena	=	hsvdvbsi.ena;
sdtena	=	hsvdvbsi.sdtena;
hsvdvbsi.ins	=	ins;
hsvdvbsi.pakgins	=	pakgins;
hsvdvbsi.div	=	div;
hsvdvbsi.sysset	=	sysset;
hsvdvbsi.srtdbids	=	dvbsrtdbids;
hsvdvbsi.srtdb	=	srtdb2;
hsvdvbsi.conf	=	m.conf;
hsvdvbsi.cids	=	cids;
hsvdvbsi.charsetutil	=	charsetutil;
hsvdvbsi.charsetutil2	=	charsetutil2;
hsvdvbsi.ctrlN	=	m.hsvdvbsi_ctrlN;
hsvdvbsi.dvbsvc	=	m.hsvdvbsi_dvbsvc;
hsvdvbsi.eurdiv	=	eurdiv;
hsvdvbsi.ctrl	=	m.ictrl;
m.cids	=	cids;
m.hsvsimplempeg_pow	=	hsvsimplempeg.pow;
m.hsvsimplempeg_enable	=	hsvsimplempeg.enable;
hsvsimplempeg.srtdbids	=	srtdbids;
hsvsimplempeg.srtdb	=	srtdb2;
hsvsimplempeg.sdmdiv	=	div;
hsvsimplempeg.ctrlN	=	m.hsvsimplempeg_ctrlN;
hsvsimplempeg.pmp	=	pmp;
hsvsimplempeg.pen	=	pen;
hsvsimplempeg.strapiN	=	mstrapi.hsvsimplempeg_strapiN;
hsvsimplempeg.ins = ins;
m.dmxsecfN	=	dmxsecfN;
m.hsvdvbsi_dmxsecfN	=	hsvdvbsi.dmxsecfN;
m.div	=	div;
m.ctrlN	=	ctrlN;
m.pen	=	pen;
m.ctrlpen	=	ctrlpen;
m.pmp	=	pmp;
m.hsvdmxN	=	hsvdmxN;
m.sysset	=	sysset;
m.pakgins	=	pakgins;
ctrl	=	m.ctrl;
pow	=	m.pow;
strapi	=	mstrapi.istrapi;
hsvdvbsi.strapiN	=	mstrapi.hsvdvbsi_strapiN;
mstrapi.strapiN	=	strapiN;
mstrapi.initstrapi	=	hsvdvbsi.nitstrapi;
mstrapi.isdtstrapi	=	hsvdvbsi.sdtstrapi;
mstrapi.ifntstrapi	=	hsvdvbsi.fntstrapi;
mstrapi.ifststrapi	=	hsvdvbsi.fststrapi;
mstrapi.itotstrapi	=	hsvdvbsi.totstrapi;
mstrapi.ilclstrapi	=	m.ilclstrapi;
mstrapi.ibatstrapi	=	hsvdvbsi.batstrapi;
mstrapi.ipostcodestrapi 	=	hsvdvbsi.postcodestrapi;
mstrapi.isimplepatstrapi	=	hsvsimplempeg.simplepatstrapi;
mstrapi.isimplepmtstrapi	=	hsvsimplempeg.simplepmtstrapi;
mstrapi.icamnitstrapi	=	hsvdvbsi.camnitstrapi;
mstrapi.isgtstrapi	=	hsvdvbsi.sgtstrapi;
strmfltr	=	m.strmfltr;
m.strmfltrN	=	strmfltrN;
m.hsvdvbsi_strmfltr	=	hsvdvbsi.strmfltr;
m.eurdiv	=	eurdiv;
m.ins	=	ins;
m.istrapi	=	mstrapi.istrapi;
phsvdmxN	=	m.phsvdmxN;
pdmxsecfN	=	m.pdmxsecfN;
hsvdvbsi.sec	=	secf;
hsvsimplempeg.sec	=	secf;
m.dmxena	=	dmxena;
mstrapi.ins = ins;
mstrapi.chsvdvbsdt_Freesatena = hsvdvbsi.sdt_Freesatena;
hsvdvbsi.ipmtstrapi = hsvsimplempeg.simplepmtstrapi;
camdataparser = hsvdvbsi.camdataparser;
camnitena = hsvdvbsi.camnitena;
hsvdvbsi.itricolorsettings = itricolorsettings;
}

};

#endif

