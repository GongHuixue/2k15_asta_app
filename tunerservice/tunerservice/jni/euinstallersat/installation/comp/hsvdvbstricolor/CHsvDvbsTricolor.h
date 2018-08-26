#ifndef  _CHSVDVBSTRICOLOR_H
#define  _CHSVDVBSTRICOLOR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsTricolor_mAcq.h>
#include <CHsvDvbsTricolor_mScan.h>
#include <CHsvDvbsTricolor_mSort.h>
#include <CHsvDvbsTricolor_msettings.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <ITvPlatformResourceNotify.h>
#include <IHsvPower.h>
#include <IHsvSorting.h>
#include <IHsvStreamNotify.h>
#include <IProdApiSystemStateObserverNotify.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteUtility.h>
#include <IProdApiSystemStateObserverExExExEx.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvSatelliteSettings.h>


class CHsvDvbsTricolor
{
public:
virtual ~CHsvDvbsTricolor(){}

//Contained Modules
private:
CHsvDvbsTricolor_mAcq mAcq;
CHsvDvbsTricolor_mScan mScan;
CHsvDvbsTricolor_mSort mSort;
CHsvDvbsTricolor_msettings msettings;

public:
ProvidesInterface<IHsvSatelliteBackgroundInstallation>	bckInstall;

ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<ITvPlatformResourceNotify>	plfresN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSorting>	sort;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IProdApiSystemStateObserverNotify>	sysstateN;


//Required interfaces
public:

RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IProdApiSystemStateObserverExExExEx>	observer;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
RequiresInterface<IHsvSatelliteUtility>	util;
RequiresInterface<IHsvSatelliteSettings>	idvbset;
RequiresInterface<IHsvSatelliteSettings>	itricolorsettings;



private:
Pumpdefines(CHsvDvbsTricolor);

public:
CHsvDvbsTricolor()
{
pow	=	mScan.isvcscanpow;
mScan.iacqpow	=	mAcq.iacqpow;
mScan.isortpow	=	mSort.isortpow;
mScan.isigstr	=	sigstr;
mScan.iinsN	=	insN;
mScan.satfeapi	=	satfeapi;
mScan.ctrl	=	ctrl;
mScan.pmp	=	pmp;
mScan.pen	=	pen;
mScan.err	=	err;
mScan.idataacq	=	mAcq.idataacq;
mScan.pgdb	=	pgdb;
mScan.pgdbconst	=	pgdbconst;
mScan.insstate	=	insstate;
mScan.util	=	util;
mScan.idvbset = idvbset;
mScan.strapi = strapi;
mScan.itricolorsettings = msettings.idvbset;

plfApidvbsN	=	mScan.plfApidvbsN;
mAcq.Timerclk = Timerclk;
mAcq.strapi	=	strapi;
mAcq.pmp	=	pmp;
mAcq.pen	=	pen;
mAcq.eurdiv	=	eurdiv;
mAcq.err	=	err;
mAcq.pgdb	=	pgdb;
mAcq.pgdbconst	=	pgdbconst;
mAcq.isvcscandata	=	mScan.isvcscandata;
mAcq.insstate	=	insstate;
mAcq.rins	=	mScan.isvcscan;
mAcq.idataacqN	=	mScan.idataacqN;
mAcq.iutil	=	iutil;
ins	=	mScan.isvcscan;
ctrlN	=	mScan.isvcscanctrlN;
sort	=	mSort.itricolorsort;
mSort.pgdb	=	pgdb;
mSort.pgdbconst	=	pgdbconst;
mSort.pen	=	pen;
mSort.pmp	=	pmp;
mSort.iinsN	=	insN;
mSort.rins	=	mScan.isvcscan;
mSort.insstate	=	insstate;


itricolorsettings = msettings.idvbset;


}

};

#endif

