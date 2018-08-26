#ifndef  _CHSVDVBSDIGITURK_H
#define  _CHSVDVBSDIGITURK_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsDigiTurk_mAcq.h>
#include <CHsvDvbsDigiTurk_mPow.h>
#include <CHsvDvbsDigiTurk_mScan.h>
#include <CHsvDvbsDigiTurk_mSort.h>
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
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvSatelliteUtility.h>

class CHsvDvbsDigiTurk
{
public:
virtual ~CHsvDvbsDigiTurk(){}

//Contained Modules
private:
CHsvDvbsDigiTurk_mAcq mAcq;
CHsvDvbsDigiTurk_mPow mPow;
CHsvDvbsDigiTurk_mScan mScan;
CHsvDvbsDigiTurk_mSort mSort;
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
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvSatelliteUtility>	util;
private:
Pumpdefines(CHsvDvbsDigiTurk);

public:
CHsvDvbsDigiTurk()
{
pow	=	mPow.pow;
mPow.iscanpow	=	mScan.iscanpow;
mPow.iacqpow	=	mAcq.iacqpow;
mPow.isortpow	=	mSort.isortpow;
mScan.isigstr	=	sigstr;
mScan.iinsN	=	insN;
mScan.satfeapi	=	satfeapi;
mScan.ctrl	=	ctrl;
mScan.pmp	=	pmp;
mScan.pen	=	pen;
mScan.err	=	err;
mScan.idataacq	=	mAcq.idataacq;
mScan.iacqpow	=	mAcq.iacqpow;
mScan.pgdb	=	pgdb;
mScan.pgdbconst	=	pgdbconst;
mScan.insstate	=	insstate;
mScan.strapi	=	strapi;
mScan.util	=	util;
plfApidvbsN	=	mScan.plfApidvbsN;
mAcq.strapi	=	strapi;
mAcq.pmp	=	pmp;
mAcq.pen	=	pen;
mAcq.eurdiv	=	eurdiv;
mAcq.err	=	err;
mAcq.pgdb	=	pgdb;
mAcq.pgdbconst	=	pgdbconst;
mAcq.iscandata	=	mScan.iscandata;
mAcq.isdsddata	=	mScan.isdsddata;
mAcq.insstate	=	insstate;
mAcq.rins	=	mScan.iscan;
mAcq.idataacqN	=	mScan.idataacqN;
mAcq.util	=	util;
mAcq.Timerclk	=	Timerclk;
ins	=	mScan.iscan;
ctrlN	=	mScan.iscanctrlN;
sort	=	mSort.isort;
mSort.pgdb	=	pgdb;
mSort.pgdbconst	=	pgdbconst;
mSort.pen	=	pen;
mSort.pmp	=	pmp;
mSort.iinsN	=	insN;
mSort.rins	=	mScan.iscan;
mSort.insstate	=	insstate;
mSort.iscandata	=	mScan.iscandata;
}

};

#endif

