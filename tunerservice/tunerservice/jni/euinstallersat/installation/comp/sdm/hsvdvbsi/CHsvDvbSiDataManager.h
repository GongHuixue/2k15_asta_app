#ifndef  _CHSVDVBSIDATAMANAGER_H
#define  _CHSVDVBSIDATAMANAGER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbSiDataManager_m.h>
#include <CHsvDvbSiDataManager_mtab.h>
#include <CHsvDvbSiDataManager_mdt.h>
#include <CHsvDvbBAT.h>
#include <CHsvDvbFNT.h>
#include <CHsvDvbFST.h>
#include <CHsvDvbNIT.h>
#include <CHsvDvbCamNIT.h>
#include <CHsvDvbSDT.h>
#include <CHsvDvbPostcode.h>
#include <CHsvDvbSGT.h>
#include <IHsvStream.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvSDTReset.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSdmDiv.h>
#include <IHsvDVBService.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSatelliteSettings.h>
//#include <CHsvDvbTDT.h>
#include <CHsvDvbTOT.h>
#include <IHsvDateTimeConversion.h>
class CHsvDvbSiDataManager
{
public:
virtual ~CHsvDvbSiDataManager(){}

//Contained Modules
private:
CHsvDvbSiDataManager_m m;
CHsvDvbSiDataManager_mtab mtab;
CHsvDvbSiDataManager_mdt mdt;
//Contained Components
private:
CHsvDvbBAT chsvdvbbat;
CHsvDvbFNT chsvdvbfnt;
CHsvDvbFST chsvdvbfst;
CHsvDvbNIT chsvdvbnit;
CHsvDvbSDT chsvdvbsdt;
CHsvDvbCamNIT chsvdvbcamnit;
CHsvDvbPostcode chsvdvbpostcode;
CHsvDvbSGT chsvdvbsgt;
//CHsvDvbTDT chsvdvbtdt;
CHsvDvbTOT chsvdvbtot;

public:
ProvidesInterface<IHsvStream>	batstrapi;

ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvStream>	fntstrapi;

ProvidesInterface<IHsvStream>	fststrapi;

ProvidesInterface<IHsvStream>	nitstrapi;
ProvidesInterface<IHsvStream>	postcodestrapi;

//ProvidesInterface<IHsvStream>	tdtstrapi;

ProvidesInterface<IHsvStream>	totstrapi;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSDTReset>	sdtena;

ProvidesInterface<IHsvStream>	sdtstrapi;

ProvidesInterface<IHsvStream>	sgtstrapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

ProvidesInterface<IHsvCamDataParser>	camdataparser;

ProvidesInterface<IHsvStream>	camnitstrapi;

ProvidesInterface<IHsvSdmEnable>	camnitena;

ProvidesInterface<IHsvSdmEnable> sdt_Freesatena;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCharSetUtility2>	charsetutil2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControl2>	ctrl;
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
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IHsvStream>	ipmtstrapi;
RequiresInterface<IHsvSatelliteSettings>  itricolorsettings;
private:
DEMUX_DEFINES(CHsvDvbSiDataManager,sec);

public:
CHsvDvbSiDataManager()
{
pow	=	m.pow;
ena	=	m.ena;
m.chsvdvbnit_pow	=	chsvdvbnit.pow;
m.chsvdvbsdt_pow	=	chsvdvbsdt.pow;
m.chsvdvbbat_pow	=	chsvdvbbat.pow;
m.chsvdvbfnt_pow	=	chsvdvbfnt.pow;
m.chsvdvbfst_pow	=	chsvdvbfst.pow;
m.chsvdvbcamnit_pow	=	chsvdvbcamnit.pow;
m.chsvdvbpostcode_pow	=	chsvdvbpostcode.pow;
m.chsvdvbsgt_pow	=	chsvdvbsgt.pow;
m.chsvdvbtot_pow	=	chsvdvbtot.pow;
m.chsvdvbnit_ena	=	chsvdvbnit.ena;
m.chsvdvbfnt_ena	=	chsvdvbfnt.ena;
m.chsvdvbfst_ena	=	chsvdvbfst.ena;
m.chsvdvbsdt_ena	=	chsvdvbsdt.ena;
m.chsvdvbbat_ena	=	chsvdvbbat.ena;
m.chsvdvbcamnit_ena	=	chsvdvbcamnit.ena;
m.chsvdvbpostcode_ena	=	chsvdvbpostcode.ena;
m.chsvdvbsgt_ena	=	chsvdvbsgt.ena;
m.chsvdvbtot_ena	=	chsvdvbtot.ena;
dmxsecfN	=	m.dmxsecfN;
m.chsvdvbsdt_dmxsecfN	=	chsvdvbsdt.dmxsecfN;
m.chsvdvbnit_dmxsecfN	=	chsvdvbnit.dmxsecfN;
m.chsvdvbfnt_dmxsecfN	=	chsvdvbfnt.dmxsecfN;
m.chsvdvbfst_dmxsecfN	=	chsvdvbfst.dmxsecfN;
m.chsvdvbbat_dmxsecfN	=	chsvdvbbat.dmxsecfN;
m.chsvdvbpostcode_dmxsecfN	=	chsvdvbpostcode.dmxsecfN;
m.chsvdvbsgt_dmxsecfN	=	chsvdvbsgt.dmxsecfN;
m.chsvdvbtot_dmxsecfN	=	chsvdvbtot.dmxsecfN;
m.sec	=	sec;
chsvdvbnit.srtdb	=	srtdb;
chsvdvbnit.srtdbids	=	srtdbids;
chsvdvbnit.sec	=	sec;
chsvdvbnit.conf	=	conf;
chsvdvbnit.strapiN	=	strapiN;
chsvdvbnit.charsetutil	=	charsetutil2;
chsvdvbnit.ctrlN	=	ctrlN;
chsvdvbnit.pakgins	=	pakgins;
chsvdvbnit.ins	=	ins;
chsvdvbnit.sysset	=	sysset;
chsvdvbnit.eurdiv	=	eurdiv;
chsvdvbnit.cids	=	cids;
chsvdvbnit.ctrl	=	ctrl;
chsvdvbfnt.srtdb	=	srtdb;
chsvdvbfnt.srtdbids	=	srtdbids;
chsvdvbfnt.sec	=	sec;
chsvdvbfnt.conf	=	conf;
chsvdvbfnt.strapiN	=	strapiN;
chsvdvbfnt.charsetutil	=	charsetutil2;
chsvdvbfnt.ctrlN	=	ctrlN;
chsvdvbfnt.pakgins	=	pakgins;
chsvdvbfst.srtdb	=	srtdb;
chsvdvbfst.srtdbids	=	srtdbids;
chsvdvbfst.sec	=	sec;
chsvdvbfst.conf	=	conf;
chsvdvbfst.strapiN	=	strapiN;
chsvdvbfst.charsetutil	=	charsetutil2;
chsvdvbfst.ctrlN	=	ctrlN;
chsvdvbfst.eurdiv	=	eurdiv;
chsvdvbfst.pakgins	=	pakgins;
sdtena	=	chsvdvbsdt.sdtena;
chsvdvbsdt.srtdb	=	srtdb;
chsvdvbsdt.srtdbids	=	srtdbids;
chsvdvbsdt.sec	=	sec;
chsvdvbsdt.conf	=	conf;
chsvdvbsdt.div	=	div;
chsvdvbsdt.charsetutil	=	charsetutil;
chsvdvbsdt.ctrlN	=	ctrlN;
chsvdvbsdt.dvbsvc	=	dvbsvc;
chsvdvbsdt.strapiN	=	strapiN;
chsvdvbsdt.cids	=	cids;
chsvdvbsdt.ins	=	ins;
chsvdvbsdt.pakgins	=	pakgins;
chsvdvbsdt.eurdiv	=	eurdiv;
chsvdvbsgt.srtdb	=	srtdb;
chsvdvbsgt.srtdbids	=	srtdbids;
chsvdvbsgt.sec	=	sec;
chsvdvbsgt.conf	=	conf;
//chsvdvbsgt.div	=	div;
chsvdvbsgt.charsetutil	=	charsetutil2;
chsvdvbsgt.ctrlN	=	ctrlN;
//chsvdvbsgt.dvbsvc	=	dvbsvc;
chsvdvbsgt.strapiN	=	strapiN;
//chsvdvbsgt.cids	=	cids;
//chsvdvbsgt.ins	=	ins;
chsvdvbsgt.pakgins	=	pakgins;
chsvdvbsgt.eurdiv	=	eurdiv;
chsvdvbsgt.ctrlN	=	ctrlN;
//chsvdvbsgt.dvbsvc	=	dvbsvc;
chsvdvbsgt.strapiN	=	strapiN;
//chsvdvbsgt.cids	=	cids;
//chsvdvbsgt.ins	=	ins;
chsvdvbsgt.pakgins	=	pakgins;
chsvdvbsgt.eurdiv	=	eurdiv;
chsvdvbsdt.ctrl	=	ctrl;
chsvdvbbat.ctrlN	=	ctrlN;
chsvdvbbat.sec	=	sec;
chsvdvbbat.conf	=	conf;
chsvdvbbat.ins	=	ins;
chsvdvbbat.srtdb	=	srtdb;
chsvdvbbat.srtdbids	=	srtdbids;
chsvdvbbat.strapiN	=	strapiN;
chsvdvbbat.ctrl	=	ctrl;
chsvdvbbat.sysset = sysset;
chsvdvbbat.charsetutil	=	charsetutil;
chsvdvbpostcode.srtdb	=	srtdb;
chsvdvbpostcode.srtdbids	=	srtdbids;
chsvdvbpostcode.sec	=	sec;
chsvdvbpostcode.conf	=	conf;
chsvdvbpostcode.strapiN	=	strapiN;
chsvdvbpostcode.charsetutil	=	charsetutil2;
chsvdvbpostcode.ctrlN	=	ctrlN;
chsvdvbpostcode.pakgins	=	pakgins;
chsvdvbpostcode.ins	=	ins;
chsvdvbpostcode.sysset	=	sysset;
chsvdvbpostcode.eurdiv	=	eurdiv;
chsvdvbpostcode.cids	=	cids;
batstrapi	=	chsvdvbbat.strapi;
nitstrapi	=	chsvdvbnit.strapi;
fntstrapi	=	chsvdvbfnt.strapi;
fststrapi	=	chsvdvbfst.strapi;
sdtstrapi	=	chsvdvbsdt.strapi;
sgtstrapi	=	chsvdvbsgt.strapi;
camnitstrapi = 	chsvdvbcamnit.strapi;
totstrapi = chsvdvbtot.strapi;
strmfltr	=	m.strmfltr;
m.chsvdvbnit_strmfltr	=	chsvdvbnit.strmfltr;
m.chsvdvbfnt_strmfltr	=	chsvdvbfnt.strmfltr;
m.chsvdvbfst_strmfltr	=	chsvdvbfst.strmfltr;
m.chsvdvbsdt_strmfltr	=	chsvdvbsdt.strmfltr;
m.chsvdvbsgt_strmfltr	=	chsvdvbsgt.strmfltr;
m.chsvdvbcamnit_strmfltr =	chsvdvbcamnit.strmfltr;
camdataparser = chsvdvbcamnit.camdataparser;
camnitena = chsvdvbcamnit.ena;
chsvdvbcamnit.srtdb	=	srtdb;
chsvdvbcamnit.srtdbids	=	srtdbids;
chsvdvbcamnit.strapiN	=	strapiN;
chsvdvbcamnit.charsetutil =	charsetutil2;
postcodestrapi	=	chsvdvbpostcode.strapi;
m.chsvdvbpostcode_strmfltr	=	chsvdvbpostcode.strmfltr;
sdt_Freesatena = chsvdvbsdt.Freesatena;
chsvdvbsdt.ipmtstrapi = ipmtstrapi;
chsvdvbbat.itricolorsettings = itricolorsettings;
//chsvdvbtot.strapiN	=	strapiN;
chsvdvbtot.dtconv = mdt.idtconv;
chsvdvbtot.sec	=	sec;
chsvdvbtot.conf	=	conf;
chsvdvbtot.ctrlN	=	ctrlN;
chsvdvbtot.srtdb	=	srtdb;




}

};

#endif

