#ifndef  _CHSVDVBSIDATAMANAGER_H
#define  _CHSVDVBSIDATAMANAGER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbSiDataManager_m.h>
#include <CHsvDvbSiDataManager_mdt.h>
#include <CHsvDvbSiDataManager_mtab.h>
#include <CHsvDvbEIT.h>
#include <CHsvDvbNIT.h>
#include <CHsvDvbSDT.h>
#include <CHsvDvbTDT.h>
#include <CHsvDvbTOT.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvDateTimeConversion.h>
#include <IHsvStream.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IPumpExSub.h>
#include <IPumpEngine.h>
#include <IHsvSDTReset.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IDateTime.h>
#include <IHsvDVBService.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallation2.h>
#include <IHsvMpegServices.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramSelection2.h>
#include <IHsvDemuxSectionFilter2.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvTcSystemSettings.h>
#include <IAppApiSystemSettings5.h>

class CHsvDvbSiDataManager
{
public:
virtual ~CHsvDvbSiDataManager(){}

//Contained Modules
private:
CHsvDvbSiDataManager_m m;
CHsvDvbSiDataManager_mdt mdt;
CHsvDvbSiDataManager_mtab mtab;
//Contained Components
private:
CHsvDvbEIT chsvdvbeit;
CHsvDvbNIT chsvdvbnit;
CHsvDvbSDT chsvdvbsdt;
CHsvDvbTDT chsvdvbtdt;
CHsvDvbTOT chsvdvbtot;
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvDateTimeConversion>	dtconv;

ProvidesInterface<IHsvStream>	eitstrapi;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvStream>	nitstrapi;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSDTReset>	sdtena;

ProvidesInterface<IHsvStream>	sdtstrapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

ProvidesInterface<IHsvStream>	tdtstrapi;

ProvidesInterface<IHsvStream>	totstrapi;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCharSetUtility2>	charsetutil2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IDateTime>	dt;
RequiresInterface<IHsvDVBService>	dvbsvc;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvInstallation2>	ins;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IHsvDemuxSectionFilter2>	secf;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IAppApiSystemSettings5>	sysset5;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPumpEngine>	pen;
private:
DEMUX_DEFINES(CHsvDvbSiDataManager,secf);

public:
CHsvDvbSiDataManager()
{
pow	=	m.pow;
ena	=	m.ena;
dmxsecfN	=	m.dmxsecfN;
m.chsvdvbnit_pow	=	chsvdvbnit.pow;
m.chsvdvbsdt_pow	=	chsvdvbsdt.pow;
m.chsvdvbeit_pow	=	chsvdvbeit.pow;
m.chsvdvbtdt_pow	=	chsvdvbtdt.pow;
m.chsvdvbtot_pow	=	chsvdvbtot.pow;
m.chsvdvbeit_ena	=	chsvdvbeit.ena;
m.chsvdvbeit_dmxsecfN	=	chsvdvbeit.dmxsecfN;
m.chsvdvbtot_dmxsecfN	=	chsvdvbtot.dmxsecfN;
m.chsvdvbtdt_dmxsecfN	=	chsvdvbtdt.dmxsecfN;
m.chsvdvbsdt_dmxsecfN	=	chsvdvbsdt.dmxsecfN;
m.chsvdvbnit_dmxsecfN	=	chsvdvbnit.dmxsecfN;
m.chsvdvbtdt_ena	=	chsvdvbtdt.ena;
m.chsvdvbtot_ena	=	chsvdvbtot.ena;
m.chsvdvbnit_ena	=	chsvdvbnit.ena;
m.chsvdvbsdt_ena	=	chsvdvbsdt.ena;
chsvdvbnit.sec	=	secf;
chsvdvbnit.mpegserv	=	mpegserv;
chsvdvbnit.conf	=	conf;
chsvdvbnit.strapiN	=	strapiN;
chsvdvbnit.ctrlN	=	ctrlN;
chsvdvbnit.ins	=	ins;
chsvdvbnit.sysset	=	sysset;
chsvdvbnit.eurdiv	=	eurdiv;
chsvdvbnit.cids	=	cids;
chsvdvbnit.charsetutil	=	charsetutil2;
chsvdvbnit.srtdb	=	srtdb;
chsvdvbnit.srtdbids	=	srtdbids;
sdtena	=	chsvdvbsdt.sdtena;
chsvdvbsdt.sec	=	secf;
chsvdvbsdt.conf	=	conf;
chsvdvbsdt.charsetutil	=	charsetutil;
chsvdvbsdt.ctrlN	=	ctrlN;
chsvdvbsdt.dvbsvc	=	dvbsvc;
chsvdvbsdt.strapiN	=	strapiN;
chsvdvbsdt.cids	=	cids;
chsvdvbsdt.ins	=	ins;
chsvdvbsdt.sysset	=	sysset;
chsvdvbsdt.srtdb	=	srtdb;
chsvdvbsdt.srtdbids	=	srtdbids;
chsvdvbsdt.eurdiv   = eurdiv;
chsvdvbsdt.mpegserv	=	mpegserv;
chsvdvbeit.sec	=	secf;
chsvdvbeit.conf	=	conf;
chsvdvbeit.dvbsvc	=	dvbsvc;
chsvdvbeit.strapiN	=	strapiN;
chsvdvbeit.mpegserv	=	mpegserv;
chsvdvbtdt.sec	=	secf;
chsvdvbtdt.dtconv	=	mdt.idtconv;
chsvdvbtdt.conf	=	conf;
chsvdvbtdt.eurdiv	=	eurdiv;
chsvdvbtdt.ins	=	ins;
chsvdvbtot.srtdb	=	srtdb;
chsvdvbtot.srtdbids	=	srtdbids;
chsvdvbtot.sec	=	secf;
chsvdvbtot.dtconv	=	mdt.idtconv;
chsvdvbtot.dt	=	dt;
chsvdvbtot.conf	=	conf;
chsvdvbtot.strapiN	=	strapiN;
chsvdvbtot.eurdiv	=	eurdiv;
chsvdvbtot.ins	=	ins;
chsvdvbtot.cids	=	cids;
chsvdvbtot.sysset5	=	sysset5;
mdt.dt	=	dt;
nitstrapi	=	chsvdvbnit.strapi;
sdtstrapi	=	chsvdvbsdt.strapi;
eitstrapi	=	chsvdvbeit.strapi;
tdtstrapi	=	chsvdvbtdt.strapi;
totstrapi	=	chsvdvbtot.strapi;
strmfltr	=	m.strmfltr;
m.chsvdvbeit_strmfltr	=	chsvdvbeit.strmfltr;
m.chsvdvbnit_strmfltr	=	chsvdvbnit.strmfltr;
m.chsvdvbsdt_strmfltr	=	chsvdvbsdt.strmfltr;
dtconv	=	mdt.idtconv;
}

};

#endif

