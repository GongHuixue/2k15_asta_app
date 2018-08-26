#ifndef  _CHSVDVBSFREESAT_H
#define  _CHSVDVBSFREESAT_H

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsFreesat_mAcq.h>
#include <CHsvDvbsFreesat_mBckgnd.h>
#include <CHsvDvbsFreesat_mScan.h>
#include <CHsvDvbsFreesat_mSort.h>
#include <CHsvDvbsFreesat_mSettings.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvSorting.h>
#include <IProdApiClockEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatelliteUtility.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvSystemSettings.h>
#include <IHsvSatelliteSettings.h>

class CHsvDvbsFreesat
{
public:
virtual ~CHsvDvbsFreesat(){}

private:
	//Contained Modules
	CHsvDvbsFreesat_mAcq mAcq;
	CHsvDvbsFreesat_mBckgnd mBckgnd;
	CHsvDvbsFreesat_mScan mScan;
	CHsvDvbsFreesat_mSort mSort;
	CHsvDvbsFreesat_mSettings mSettings;

public:
	//Provides interfaces
	ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;
	ProvidesInterface<IHsvSatellitePackageInstallation>	ins;
	ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;
	ProvidesInterface<IHsvPower>	pow;
	ProvidesInterface<IHsvSorting>	sort;
	ProvidesInterface<IHsvSatelliteSettings>	settings;
	ProvidesInterface<IHsvSatelliteBackgroundInstallation>	bckInstall;
	ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;
	ProvidesInterface<IHsvStreamNotify>	strapiN;
	//ProvidesInterface<IHsvSatelliteInstallationNotify>	iinsN;

	//Required interfaces
	RequiresInterface<IProdApiClockEx>	Timerclk;
	RequiresInterface<IHsvSdmControl2>	ctrl;
	RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
	RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
	RequiresInterface<IHsvSatelliteInstallation>	insstate;
	RequiresInterface<IHsvSatelliteUtility>	iutil;
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IHsvProgramDatabase>	pgdb;
	RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
	RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
	RequiresInterface<IHsvInstallationSigStrength>	sigstr;
	RequiresInterface<IHsvStream>	strapi;
	RequiresInterface<IHsvSatSystemSettings>	sysset;
	RequiresInterface<IPumpExSub>	pmp;
	RequiresInterface<IHsvErrorCodeEx>	err;
	RequiresInterface<IHsvProgramData3>	pgdat;
	RequiresInterface<IHsvSatelliteDiversity>	s2div;

private:
Pumpdefines(CHsvDvbsFreesat);

public:
CHsvDvbsFreesat()
{
	pow	=	mScan.isvcscanpow;
	mScan.iacqpow	=	mAcq.iacqpow;
	mScan.isortpow	=	mSort.isortpow;
	mScan.ibckgndpow	=	mBckgnd.ibckgndpow;
	mScan.isettingspow	=	mSettings.isettingspow;
	mScan.isigstr	=	sigstr;
	mScan.iinsN	=	insN;
	mScan.satfeapi	=	satfeapi;
	mScan.ctrl	=	ctrl;
	mScan.pen	=	pen;
	mScan.idataacq	=	mAcq.idataacq;
	mScan.pgdb	=	pgdb;
	mScan.pgdbconst	=	pgdbconst;
	mScan.insstate	=	insstate;
	mScan.strapi	=	strapi;
	mScan.err	=	err;
	mScan.isettings = mSettings.isettings;
	plfApidvbsN	=	mScan.plfApidvbsN;
	mAcq.strapi	=	strapi;
	mAcq.pen	=	pen;
	mAcq.eurdiv	=	eurdiv;
	mAcq.pgdb	=	pgdb;
	mAcq.pgdbconst	=	pgdbconst;
	mAcq.isvcscandata	=	mScan.isvcscandata;
	mAcq.insstate	=	insstate;
	mAcq.rins	=	mScan.isvcscan;
	mAcq.idataacqN	=	mScan.idataacqN;
	mAcq.iutil	=	iutil;
	mAcq.isettings = mSettings.isettings;
	mAcq.iscansdsd = mScan.iscansdsd;
	ins	=	mScan.isvcscan;
	ctrlN	=	mScan.isvcscanctrlN;
	sort	=	mSort.ifreesatsort;
	mSort.pgdb	=	pgdb;
	mSort.pgdbconst	=	pgdbconst;
	mSort.pen	=	pen;
	mSort.iinsN	=	insN;
	mSort.rins	=	mScan.isvcscan;
	mSort.insstate	=	insstate;
	bckInstall	=	mBckgnd.ibckInstall;
	strapiN	=	mBckgnd.strapiN;
	mBckgnd.insstate	=	insstate;
	mBckgnd.pmp	=	pmp;
	mBckgnd.pen	=	pen;
	mBckgnd.eurdiv	=	eurdiv;
	mBckgnd.s2div	=	s2div;
	mBckgnd.idataacq	=	mAcq.idataacq;
	mBckgnd.pgdb	=	pgdb;
	mBckgnd.pgdbconst	=	pgdbconst;
	//mBckgnd.iinsN	=	iinsN;
	//bckctrlN	=	mBckgnd.bckctrlN;
	mBckgnd.strapi	=	strapi;
	mBckgnd.pgdat	=	pgdat;
	mBckgnd.err	=	err;
	mBckgnd.isort	=	mSort.ifreesatsort;
	mBckgnd.isettings = mSettings.isettings;
	mSettings.err = err;
	settings = mSettings.isettings;
}

};

#endif

