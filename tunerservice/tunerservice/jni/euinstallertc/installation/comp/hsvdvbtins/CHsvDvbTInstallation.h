#ifndef  _CHSVDVBTINSTALLATION_H
#define  _CHSVDVBTINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbTInstallation_mBackground.h>
#include <CHsvDvbTInstallation_mDataAcq.h>
#include <CHsvDvbTInstallation_mDtr.h>
#include <CHsvDvbTInstallation_mFull.h>
#include <CHsvDvbTInstallation_mQuick.h>
#include <CHsvDvbTInstallation_mRoute.h>
#include <CHsvDvbTInstallation_mcountry.h>
#include <CHsvDvbTInstallation_msettings.h>
#include <IHsvAltFrequencyIterator.h>
#include <IHsvInstallationNotify.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDVBSettings.h>
#include <IHsvDigitalScan.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvInstallationCountrySpecifics.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IProdApiClockEx.h>
#include <IHsvAltFrequencyScannerNotify.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvPool.h>
#include <IHsvInstallationUtility.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
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
#include <IHsvProgramSelection2.h>

class CHsvDvbTInstallation
{
public:
virtual ~CHsvDvbTInstallation(){}

//Contained Modules
private:
CHsvDvbTInstallation_mBackground mBackground;
CHsvDvbTInstallation_mDataAcq mDataAcq;
CHsvDvbTInstallation_mDtr mDtr;
CHsvDvbTInstallation_mFull mFull;
CHsvDvbTInstallation_mQuick mQuick;
CHsvDvbTInstallation_mRoute mRoute;
CHsvDvbTInstallation_mcountry mcountry;
CHsvDvbTInstallation_msettings msettings;
public:
ProvidesInterface<IHsvAltFrequencyIterator>	afitr;

ProvidesInterface<IHsvInstallationNotify>	cntryinsN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvDigitalAcquisition>	digacq;

ProvidesInterface<IHsvDVBSettings>	dvbset;

ProvidesInterface<IHsvDigitalScan>	dvbt;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvSortedTableConfigurationEx>	freqlistconf;

ProvidesInterface<IHsvInstallationCountrySpecifics>	inscountry;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	bcksyssetN;


//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvAltFrequencyScannerNotify>	afscanN;
RequiresInterface<IHsvDVBSettings>	cdvbset;
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationNotify>	installN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<ITvPlatformResource>	plfres;
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
RequiresInterface<IHsvProgramSelection2>	pgsel;
private:
Pumpdefines(CHsvDvbTInstallation);

public:
CHsvDvbTInstallation()
{
pow	=	mRoute.pow;
feapiN	=	mRoute.feapiN;
ctrlN	=	mRoute.ctrlN;
mRoute.rins	=	rins;
mRoute.idvbset	=	msettings.idvbset;
mRoute.iquickpow	=	mQuick.iquickpow;
mRoute.iquickfeN	=	mQuick.iquickfeN;
mRoute.iqctrlN	=	mQuick.iqctrlN;
mRoute.ifullpow	=	mFull.ifullpow;
mRoute.ifullfeN	=	mFull.ifullfeN;
mRoute.ifctrlN	=	mFull.ifctrlN;
mRoute.idtrpow	=	mDtr.idtrpow;
mRoute.idtrfeN	=	mDtr.idtrfeN;
mRoute.idctrlN	=	mDtr.idctrlN;
mRoute.idatapow	=	mDataAcq.idatapow;
mRoute.icntrypow	=	mcountry.icntrypow;
mRoute.icctrlN	=	mcountry.icctrlN;
mRoute.ibctrlN	=	mBackground.ibctrlN;
mRoute.ibpow	=	mBackground.ibpow;
mRoute.isetpow	=	msettings.isetpow;
strapiN	=	mRoute.strapiN;
mRoute.ibstrapiN	=	mBackground.ibstrapiN;
mRoute.icntrystrapiN	=	mcountry.icntrystrapiN;
mRoute.idstrapiN	=	mDtr.idstrapiN;
mRoute.eurdiv	=	eurdiv;
mRoute.iquick	=	mQuick.iquick;
mRoute.ifull	=	mFull.ifull;
mRoute.idtr	=	mDtr.idtr;
dvbt	=	mRoute.idvbt;
digacq	=	mDataAcq.idataacq;
mQuick.pmp	=	pmp;
mQuick.pen	=	pen;
mQuick.feapi	=	feapi;
mQuick.sigstr	=	sigstr;
mQuick.ctrl	=	ctrl;
mQuick.rins	=	rins;
mQuick.insN	=	insN;
mQuick.mctl	=	mctl;
mQuick.plferrids	=	plferrids;
mQuick.sysset	=	sysset;
mQuick.idataacq	=	mDataAcq.idataacq;
mQuick.wnddest	=	wnddest;
mQuick.chdecdvbt2	=	chdecdvbt2;
mQuick.digscanN	=	mDataAcq.digscanN;
mQuick.eurdiv	=	eurdiv;
mQuick.idvbtqctrlN	=	mDataAcq.idvbtqctrlN;
mQuick.istub	=	mRoute.istub;
mQuick.err	=	err;
mQuick.idvbset	=	msettings.idvbset;
mQuick.cids	=	cids;
mQuick.strapi 	= strapi;
mFull.pmp	=	pmp;
mFull.pen	=	pen;
mFull.feapi	=	feapi;
mFull.sigstr	=	sigstr;
mFull.ctrl	=	ctrl;
mFull.rins	=	rins;
mFull.insN	=	insN;
mFull.mctl	=	mctl;
mFull.plferrids	=	plferrids;
mFull.sysset	=	sysset;
mFull.idataacq	=	mDataAcq.idataacq;
mFull.wnddest	=	wnddest;
mFull.chdecdvbt2	=	chdecdvbt2;
mFull.digscanN	=	mDataAcq.digscanN;
mFull.eurdiv	=	eurdiv;
mFull.idvbtqctrlN	=	mDataAcq.idvbtqctrlN;
mFull.istub	=	mRoute.istub;
mFull.err	=	err;
mFull.idvbset	=	msettings.idvbset;
mFull.cids	=	cids;
mFull.strapi 	= strapi;
mDtr.pmp	=	pmp;
mDtr.pen	=	pen;
mDtr.feapi	=	feapi;
mDtr.sigstr	=	sigstr;
mDtr.ctrl	=	ctrl;
mDtr.rins	=	rins;
mDtr.insN	=	insN;
mDtr.mctl	=	mctl;
mDtr.plferrids	=	plferrids;
mDtr.sysset	=	sysset;
mDtr.idataacq	=	mDataAcq.idataacq;
mDtr.wnddest	=	wnddest;
mDtr.chdecdvbt2	=	chdecdvbt2;
mDtr.strmfltr	=	strmfltr;
mDtr.digscanN	=	mDataAcq.digscanN;
mDtr.idvbtqctrlN	=	mDataAcq.idvbtqctrlN;
mDtr.eurdiv	=	eurdiv;
mDtr.pgdb	=	pgdb;
mDtr.istub	=	mRoute.istub;
mDtr.strapi	=	strapi;
mDtr.err	=	err;
mDtr.cids	=	cids;
mDataAcq.idvbt	=	mRoute.idvbt;
mDataAcq.pmp	=	pmp;
mDataAcq.pen	=	pen;
mDataAcq.feapi	=	feapi;
mDataAcq.pgdb	=	pgdb;
mDataAcq.pgdbconst	=	pgdbconst;
mDataAcq.cids	=	cids;
mDataAcq.sysset	=	sysset;
mDataAcq.rins	=	rins;
mDataAcq.idvbset	=	msettings.idvbset;
mDataAcq.sort	=	sort;
mDataAcq.sortN	=	sortN;
mDataAcq.srtdbids	=	srtdbids;
mDataAcq.wnddest	=	wnddest;
mDataAcq.strapi	=	strapi;
mDataAcq.srtdb	=	srtdb;
mDataAcq.eurdiv	=	eurdiv;
mDataAcq.Timerclk	=	Timerclk;
mDataAcq.chdecdvbt2	=	chdecdvbt2;
mDataAcq.hpool	=	hpool;
mDataAcq.instutil	=	instutil;
mDataAcq.pgdat	=	pgdat;
mDataAcq.langids	=	mcountry.langids;
freqlistconf	=	mcountry.freqlistconf;
inscountry	=	mcountry.inscountry;
cntryinsN	=	mcountry.cntryinsN;
afitr	=	mcountry.afitr;
mcountry.ffsdir	=	ffsdir;
mcountry.insN	=	insN;
mcountry.str	=	str;
mcountry.afscanN	=	afscanN;
mcountry.cdvbset	=	cdvbset;
mcountry.cids	=	cids;
mcountry.strapi	=	strapi;
mcountry.srtdbids	=	srtdbids;
mcountry.srtdb	=	srtdb;
mcountry.rins	=	rins;
mcountry.eurdiv	=	eurdiv;
mcountry.sysset	=	sysset;
ena	=	mBackground.ena;
mBackground.pen	=	pen;
mBackground.pmp	=	pmp;
mBackground.idataacq	=	mDataAcq.idataacq;
mBackground.eurdiv	=	eurdiv;
mBackground.rins	=	rins;
mBackground.plfres	=	plfres;
mBackground.pgsel   = pgsel;
mBackground.pgdbconst = pgdbconst;
mBackground.pgdb 	= pgdb;
mBackground.strapi 	= strapi;
mBackground.sysset 	= sysset;
mBackground.idvbset	=	msettings.idvbset;
mBackground.installN	= 	installN;
mBackground.cids	= 	cids;
mBackground.sort	=	sort;
mBackground.instutil	=	instutil;
mBackground.pgdat	=	pgdat;
dvbset	=	msettings.idvbset;
syssetN	=	msettings.syssetN;
bcksyssetN = mBackground.syssetN;
msettings.rins	=	rins;
msettings.ffsdir	=	ffsdir;
msettings.str	=	str;
msettings.eurdiv	=	eurdiv;
msettings.plferrids	=	plferrids;
msettings.feapi	=	feapi;
msettings.wnddest	=	wnddest;
msettings.sortroute	=	sortroute;
}

};

#endif

