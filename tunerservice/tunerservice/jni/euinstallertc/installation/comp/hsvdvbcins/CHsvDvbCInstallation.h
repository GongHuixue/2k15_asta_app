#ifndef  _CHSVDVBCINSTALLATION_H
#define  _CHSVDVBCINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbCInstallation_m.h>
#include <CHsvDvbCInstallation_mDataAcq.h>
#include <CHsvDvbCInstallation_mfull.h>
#include <CHsvDvbCInstallation_mgrid.h>
#include <CHsvDvbCInstallation_mprescan.h>
#include <CHsvDvbCInstallation_mquick.h>
#include <CHsvDvbCInstallation_msettings.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvInstallation2.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IProdApiClockEx.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCountryIds.h>
#include <ICesCityIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvMediaControl.h>
#include <IMemoryOperations.h>
#include <IHsvDvbMplDiv.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortNotify.h>
#include <IHsvSortRoute.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>

class CHsvDvbCInstallation
{
public:
virtual ~CHsvDvbCInstallation(){}

//Contained Modules
private:
CHsvDvbCInstallation_m m;
CHsvDvbCInstallation_mDataAcq mDataAcq;
CHsvDvbCInstallation_mfull mfull;
CHsvDvbCInstallation_mgrid mgrid;
CHsvDvbCInstallation_mprescan mprescan;
CHsvDvbCInstallation_mquick mquick;
CHsvDvbCInstallation_msettings msettings;
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvDigitalAcquisition>	digacq;

ProvidesInterface<IHsvDVBSettings>	dvbset;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvInstallation2>	ins;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<ICesCityIds>	cityids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationNotify>	installN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvDvbMplDiv>	mpldiv;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortNotify>	sortN;
RequiresInterface<IHsvSortRoute>	sortroute;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvDvbCInstallation);

public:
CHsvDvbCInstallation()
{
pow	=	m.pow;
ena	=	m.ena;
m.pmp	=	pmp;
m.pen	=	pen;
m.iquick	=	mquick.iquick;
m.ifull	=	mfull.ifull;
m.igrid	=	mgrid.igrid;
m.iprescan	=	mprescan.iprescan;
m.iprescanpow	=	mprescan.iprescanpow;
m.iquickpow	=	mquick.iquickpow;
m.ifullpow	=	mfull.ifullpow;
m.igridpow	=	mgrid.igridpow;
m.iacqpow	=	mDataAcq.iacqpow;
m.isetpow	=	msettings.isetpow;
m.rins	=	rins;
m.hsverr	=	hsverr;
m.idvbset	=	msettings.idvbset;
m.insN	=	insN;
m.idataacq	=	mDataAcq.idataacq;
m.iprescanfeN	=	mprescan.iprescanfeN;
m.ifullfeN	=	mfull.ifullfeN;
m.igridfeN	=	mgrid.igridfeN;
m.iquickfeN	=	mquick.iquickfeN;
m.iqstrapiN	=	mquick.iqstrapiN;
m.ifstrapiN	=	mfull.ifstrapiN;
m.igstrapiN	=	mgrid.igstrapiN;
m.iacqstrapiN	=	mDataAcq.iacqstrapiN;
m.ipctrlN	=	mprescan.ipctrlN;
m.iqctrlN	=	mquick.iqctrlN;
m.ifctrlN	=	mfull.ifctrlN;
m.igctrlN	=	mgrid.igctrlN;
m.ifena	=	mfull.ifena;
m.igena	=	mgrid.igena;
m.iqena	=	mquick.iqena;
m.ipena	=	mprescan.ipena;
m.eurdiv	=	eurdiv;
feapiN	=	m.feapiN;
ins	=	m.ins;
strapiN	=	m.strapiN;
ctrlN	=	m.ctrlN;
dvbset	=	msettings.idvbset;
digacq	=	mDataAcq.idataacq;
mprescan.pmp	=	pmp;
mprescan.pen	=	pen;
mprescan.idataacq	=	mDataAcq.idataacq;
mprescan.idvbset	=	msettings.idvbset;
mprescan.iprescanN	=	m.iprescanN;
mprescan.ctrl	=	ctrl;
mprescan.rins	=	rins;
mprescan.insN	=	insN;
mprescan.sigstr	=	sigstr;
mprescan.strapi	=	strapi;
mprescan.feapi	=	feapi;
mprescan.eurdiv	=	eurdiv;
mprescan.wnddest	=	wnddest;
mprescan.hsverr	=	hsverr;
mprescan.plferrids	=	plferrids;
mquick.pmp	=	pmp;
mquick.pen	=	pen;
mquick.idataacq	=	mDataAcq.idataacq;
mquick.idvbset	=	msettings.idvbset;
mquick.iquickN	=	m.iquickN;
mquick.ctrl	=	ctrl;
mquick.rins	=	rins;
mquick.insN	=	insN;
mquick.sigstr	=	sigstr;
mquick.strapi	=	strapi;
mquick.pgdb	=	pgdb;
mquick.mctl	=	mctl;
mquick.feapi	=	feapi;
mquick.strmfltr	=	strmfltr;
mquick.eurdiv	=	eurdiv;
mquick.hsverr	=	hsverr;
mquick.wnddest	=	wnddest;
mquick.plferrids	=	plferrids;
mquick.ffsdir	=	ffsdir;
mquick.str	=	str;
mquick.pgdbconst	=	pgdbconst;
mquick.memo	=	memo;
mquick.apsysset	=	apsysset;
mfull.pmp	=	pmp;
mfull.pen	=	pen;
mfull.idataacq	=	mDataAcq.idataacq;
mfull.idvbset	=	msettings.idvbset;
mfull.ifullN	=	m.ifullN;
mfull.rins	=	rins;
mfull.insN	=	insN;
mfull.ctrl	=	ctrl;
mfull.hsverr	=	hsverr;
mfull.mctl	=	mctl;
mfull.strmfltr	=	strmfltr;
mfull.strapi	=	strapi;
mfull.sigstr	=	sigstr;
mfull.feapi	=	feapi;
mfull.pgdb	=	pgdb;
mfull.wnddest	=	wnddest;
mfull.plferrids	=	plferrids;
mfull.eurdiv	=	eurdiv;
mfull.ffsdir	=	ffsdir;
mfull.str	=	str;
mfull.sysset	=	sysset;
mfull.cids	=	cids;
mfull.pgdbconst = pgdbconst;
mgrid.pmp	=	pmp;
mgrid.pen	=	pen;
mgrid.idataacq	=	mDataAcq.idataacq;
mgrid.idvbset	=	msettings.idvbset;
mgrid.igridN	=	m.igridN;
mgrid.rins	=	rins;
mgrid.insN	=	insN;
mgrid.ctrl	=	ctrl;
mgrid.hsverr	=	hsverr;
mgrid.mctl	=	mctl;
mgrid.strmfltr	=	strmfltr;
mgrid.strapi	=	strapi;
mgrid.sigstr	=	sigstr;
mgrid.feapi	=	feapi;
mgrid.pgdb	=	pgdb;
mgrid.wnddest	=	wnddest;
mgrid.plferrids	=	plferrids;
mgrid.eurdiv	=	eurdiv;
mgrid.ffsdir	=	ffsdir;
mgrid.str	=	str;
mDataAcq.pmp	=	pmp;
mDataAcq.pen	=	pen;
mDataAcq.Timerclk	=	Timerclk;
mDataAcq.strapi	=	strapi;
mDataAcq.pgdbconst	=	pgdbconst;
mDataAcq.pgdb	=	pgdb;
mDataAcq.rins	=	rins;
mDataAcq.sort	=	sort;
mDataAcq.pgdat	=	pgdat;
mDataAcq.sysset	=	sysset;
mDataAcq.eurdiv	=	eurdiv;
mDataAcq.mpldiv	=	mpldiv;
mDataAcq.divsupp	=	divsupp;
mDataAcq.iquick	=	mquick.iquick;
mDataAcq.ifull	=	mfull.ifull;
mDataAcq.igrid	=	mgrid.igrid;
mDataAcq.ffsdir	=	ffsdir;
mDataAcq.str	=	str;
mDataAcq.feapi	=	feapi;
mDataAcq.idvbset	=	msettings.idvbset;
mDataAcq.srtdbids	=	srtdbids;
mDataAcq.srtdb	=	srtdb;
mDataAcq.insN	=	insN;
mDataAcq.installN	=	installN;
mDataAcq.cids	=	cids;
mDataAcq.wnddest	=	wnddest;
mDataAcq.plferrids	=	plferrids;
mDataAcq.sortN	=	sortN;
mDataAcq.instutil	=	instutil;
msettings.pmp	=	pmp;
msettings.pen	=	pen;
msettings.rins	=	rins;
msettings.eurdiv	=	eurdiv;
msettings.sysset	=	sysset;
msettings.plferrids	=	plferrids;
msettings.wnddest	=	wnddest;
msettings.feapi	=	feapi;
msettings.ffsdir	=	ffsdir;
msettings.str	=	str;
msettings.cityids	=	cityids;
msettings.apsysset	=	apsysset;
msettings.cids	=	cids;
msettings.sortroute	=	sortroute;
msettings.insN	=	insN;
syssetN	=	msettings.syssetN;
}

};

#endif

