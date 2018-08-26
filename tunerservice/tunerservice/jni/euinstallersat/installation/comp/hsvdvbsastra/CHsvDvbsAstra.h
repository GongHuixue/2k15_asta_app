#ifndef  _CHSVDVBSASTRA_H
#define  _CHSVDVBSASTRA_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsAstra_mAcq.h>
#include <CHsvDvbsAstra_mScan.h>
#include <CHsvDvbsAstra_mSort.h>
#include <CHsvDvbsAstra_mBckgnd.h>
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
#include <IHsvProgramData3.h>


class CHsvDvbsAstra
{
public:
virtual ~CHsvDvbsAstra(){}

//Contained Modules
private:
CHsvDvbsAstra_mAcq mAcq;
CHsvDvbsAstra_mScan mScan;
CHsvDvbsAstra_mSort mSort;

CHsvDvbsAstra_mBckgnd mBckgnd;

public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSorting>	sort;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IHsvSatelliteBackgroundInstallation>	bckInstall;


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
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramSelection2>	pgsel;

private:
Pumpdefines(CHsvDvbsAstra);

public:
CHsvDvbsAstra()
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
mScan.ibckgndpow	=	mBckgnd.ibckgndpow;
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
sort	=	mSort.iastrasort;
mSort.pgdb	=	pgdb;
mSort.pgdbconst	=	pgdbconst;
mSort.pen	=	pen;
mSort.pmp	=	pmp;
mSort.iinsN	=	insN;
mSort.rins	=	mScan.isvcscan;
mSort.insstate	=	insstate;
mBckgnd.err	=	err;
mBckgnd.eurdiv	=	eurdiv;
mBckgnd.iinsN	=	insN;
mBckgnd.insstate	=	insstate;
mBckgnd.pgdat	=	pgdat;
mBckgnd.pgdb	=	pgdb;
mBckgnd.pgdbconst	=	pgdbconst;
mBckgnd.strapi	=	strapi;
mBckgnd.pmp	=	pmp;
mBckgnd.pgsel = pgsel;
mBckgnd.pen = pen;
bckInstall	=	mBckgnd.ibckInstall;
strapiN	=	mBckgnd.strapiN;

}

};

#endif

