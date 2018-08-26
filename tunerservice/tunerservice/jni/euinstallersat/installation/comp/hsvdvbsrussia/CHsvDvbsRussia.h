#ifndef  _CHSVDVBSRUSSIA_H
#define  _CHSVDVBSRUSSIA_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsRussia_mAcq.h>
#include <CHsvDvbsRussia_mScan.h>
#include <CHsvDvbsRussia_mSort.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvSorting.h>
#include <IProdApiClockEx.h>
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
#include <IHsvSatSystemSettings.h>

class CHsvDvbsRussia
{
public:
virtual ~CHsvDvbsRussia(){}

//Contained Modules
private:
CHsvDvbsRussia_mAcq mAcq;
CHsvDvbsRussia_mScan mScan;
CHsvDvbsRussia_mSort mSort;
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSorting>	sort;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatSystemSettings>	sysset;
private:
Pumpdefines(CHsvDvbsRussia);

public:
CHsvDvbsRussia()
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
plfApidvbsN	=	mScan.plfApidvbsN;
mAcq.strapi	=	strapi;
mAcq.pmp	=	pmp;
mAcq.pen	=	pen;
mAcq.eurdiv	=	eurdiv;
mAcq.err	=	err;
mAcq.pgdb	=	pgdb;
mAcq.pgdbconst	=	pgdbconst;
mAcq.isvcscandata	=	mScan.isvcscandata;
mAcq.Timerclk	=	Timerclk;
mAcq.insstate	=	insstate;
mAcq.rins	=	mScan.isvcscan;
mAcq.idataacqN	=	mScan.idataacqN;
mAcq.sysset	=	sysset;
mAcq.iutil	=	iutil;
ins	=	mScan.isvcscan;
ctrlN	=	mScan.isvcscanctrlN;
sort	=	mSort.irussiasort;
mSort.pgdb	=	pgdb;
mSort.pgdbconst	=	pgdbconst;
mSort.pen	=	pen;
mSort.pmp	=	pmp;
mSort.iinsN	=	insN;
mSort.rins	=	mScan.isvcscan;
mSort.insstate	=	insstate;
}

};

#endif

