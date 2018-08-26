#ifndef  _CHSVDVBSCANAL_H
#define  _CHSVDVBSCANAL_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsCanal_mAcq.h>
#include <CHsvDvbsCanal_mScan.h>
#include <CHsvDvbsCanal_mSort.h>
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
#include <IHsvSatSystemSettings.h>

class CHsvDvbsCanal
{
public:
virtual ~CHsvDvbsCanal(){}

//Contained Modules
private:
CHsvDvbsCanal_mAcq mAcq;
CHsvDvbsCanal_mScan mScan;
CHsvDvbsCanal_mSort mSort;
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSorting>	sort;

ProvidesInterface<IHsvDigitalAcquisition>	dataacq;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvCountryIds>	cids;
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
Pumpdefines(CHsvDvbsCanal);

public:
CHsvDvbsCanal()
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
mScan.strapi	=	strapi;
plfApidvbsN	=	mScan.plfApidvbsN;
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
mAcq.sysset	=	sysset;
mAcq.iutil	=	iutil;
mAcq.cids	=	cids;
mAcq.Timerclk	=	Timerclk;
ins	=	mScan.isvcscan;
ctrlN	=	mScan.isvcscanctrlN;
sort	=	mSort.icanalsort;
mSort.pgdb	=	pgdb;
mSort.pgdbconst	=	pgdbconst;
mSort.pen	=	pen;
mSort.pmp	=	pmp;
mSort.iinsN	=	insN;
mSort.rins	=	mScan.isvcscan;
mSort.insstate	=	insstate;
dataacq	= mAcq.idataacq;

}

};

#endif

