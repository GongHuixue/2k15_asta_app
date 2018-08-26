#ifndef  _CHSVDVBSGENERIC_H
#define  _CHSVDVBSGENERIC_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsGeneric_m.h>
#include <CHsvDvbsGeneric_mAcq.h>
#include <CHsvDvbsGeneric_mBckgnd.h>
#include <CHsvDvbsGeneric_mScan.h>
#include <CHsvDvbsGeneric_mSort.h>
#include <CHsvDvbsGeneric_mSrt.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvSorting.h>
#include <IHsvStreamNotify.h>
#include <IProdApiClockEx.h>
#include <IAppApiChannelLibReturnCodes.h>
#include <IAppApiSystemSettings5.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvPrescanParser.h>
#include <IHsvSatelliteUtility.h>
#include <IHsvMediaControl.h>
#include <IHsvPackageParser.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvDigitalScanData.h>
#include <IRealTimeKernel.h>
#include <IHsvSatelliteDiversity.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvWindowDestinationMap.h>

class CHsvDvbsGeneric
{
public:
virtual ~CHsvDvbsGeneric(){}

//Contained Modules
private:
CHsvDvbsGeneric_m m;
CHsvDvbsGeneric_mAcq mAcq;
CHsvDvbsGeneric_mBckgnd mBckgnd;
CHsvDvbsGeneric_mScan mScan;
CHsvDvbsGeneric_mSort mSort;
CHsvDvbsGeneric_mSrt mSrt;
public:
ProvidesInterface<IHsvSatelliteBackgroundInstallation>	bckInstall;

ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	plfApidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSorting>	sort;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IAppApiChannelLibReturnCodes>	apperr;
RequiresInterface<IAppApiSystemSettings5>	apsysset;
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvSatelliteSettings>	dvbset;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IHsvPrescanParser>	iprescanparser;
RequiresInterface<IHsvSatelliteUtility>	iutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IHsvPackageParser>	packagepar;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat3;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvDigitalScanData>	prescandata;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvDigitalAcquisition>	dataacq;

private:
Pumpdefines(CHsvDvbsGeneric);

public:
CHsvDvbsGeneric()
{
sort	=	mSort.isort;
ctrlN	=	m.ctrlN;
plfApidvbsN	=	m.plfApidvbsN;
ins	=	m.ins;
pow	=	m.pow;
bckInstall	=	m.bckInstall;
m.isvcscanpow	=	mScan.isvcscanpow;
m.isrtpow	=	mSrt.isrtpow;
m.iacqpow	=	mAcq.iacqpow;
m.isortpow	=	mSort.isortpow;
m.ibckgndpow	=	mBckgnd.ibckgndpow;
m.isvcscanplfApidvbsN	=	mScan.isvcscanplfApidvbsN;
m.isvcscanctrlN	=	mScan.isvcscanctrlN;
m.isrtctrlN	=	mSrt.isrtctrlN;
m.isrtplfApidvbsN	=	mSrt.isrtplfApidvbsN;
m.isrt	=	mSrt.isrt;
m.isvcscan	=	mScan.isvcscan;
m.insstate	=	insstate;
m.err	=	err;
m.iscanAcqN	=	mScan.iscanAcqN;
m.isrtAcqN	=	mSrt.isrtAcqN;
m.ibckAcqN	=	mBckgnd.ibckAcqN;
m.ibckInstall	=	mBckgnd.ibckInstall;
mScan.isigstr	=	sigstr;
mScan.idvbset	=	dvbset;
mScan.err	=	err;
mScan.ctrl	=	ctrl;
mScan.pmp	=	pmp;
mScan.pen	=	pen;
mScan.wnddest	=	wnddest;
mScan.iinsN	=	insN;
mScan.satfeapi	=	satfeapi;
mScan.idataacq	=	mAcq.idataacq;
mScan.iacqpow	=	mAcq.iacqpow;
mScan.insstate	=	insstate;
mScan.pgdb	=	pgdb;
mScan.pgdbconst	=	pgdbconst;
mScan.strapi	=	strapi;
mScan.s2div	=	s2div;
mScan.apsysset	=	apsysset;
mScan.cids	=	cids;
mScan.iutil	=	iutil;
mAcq.dataacq	= dataacq;
mAcq.strapi	=	strapi;
mAcq.pmp	=	pmp;
mAcq.pen	=	pen;
mAcq.rtk	=	rtk;
mAcq.eurdiv	=	eurdiv;
mAcq.err	=	err;
mAcq.pgdb	=	pgdb;
mAcq.pgdbconst	=	pgdbconst;
mAcq.isvcscandata	=	mScan.isvcscandata;
mAcq.Timerclk	=	Timerclk;
mAcq.idvbset	=	dvbset;
mAcq.rins	=	mScan.isvcscan;
mAcq.isrtdata	=	mSrt.isrtdata;
mAcq.iprescanparser	=	iprescanparser;
mAcq.charsetutil	=	charsetutil;
mAcq.insstate	=	insstate;
mAcq.iacqN	=	m.iacqN;
mAcq.iutil	=	iutil;
mAcq.pgdat3	=	pgdat3;
mAcq.pgsel	=	pgsel;
mAcq.insN   =  insN;
mAcq.ipackage	=	packagepar;
mSrt.isigstr	=	sigstr;
mSrt.idvbset	=	dvbset;
mSrt.err	=	err;
mSrt.ctrl	=	ctrl;
mSrt.pmp	=	pmp;
mSrt.pen	=	pen;
mSrt.wnddest	=	wnddest;
mSrt.iinsN	=	insN;
mSrt.satfeapi	=	satfeapi;
mSrt.idataacq	=	mAcq.idataacq;
mSrt.iacqpow	=	mAcq.iacqpow;
mSrt.mctl	=	mctl;
mSrt.strmfltr	=	strmfltr;
mSrt.strapi	=	strapi;
mSrt.pgdb	=	pgdb;
mSrt.pgdbconst	=	pgdbconst;
mSrt.insstate	=	insstate;
mSrt.isort	=	mSort.isort;
mSrt.iutil	=	iutil;
mSrt.pgdat3	=	pgdat3;
mSrt.pgsel	=	pgsel;
mSort.pmp	=	pmp;
mSort.pen	=	pen;
mSort.satfeapi	=	satfeapi;
mSort.pgdbconst	=	pgdbconst;
mSort.pgdb	=	pgdb;
mSort.iinsN	=	insN;
mSort.ipackage	=	packagepar;
mSort.idvbset	=	dvbset;
bckctrlN	=	mBckgnd.bckctrlN;
//strapiN	=	mBckgnd.strapiN;
strapiN	=	m.strapiN;
m.isrtstrapiN = mSrt.isrtstrapiN;
m.ibckgndstrapiN = mBckgnd.strapiN;
mBckgnd.insstate	=	insstate;
mBckgnd.plfres	=	plfres;
mBckgnd.pmp	=	pmp;
mBckgnd.pen	=	pen;
mBckgnd.s2div	=	s2div;
mBckgnd.idataacq	=	mAcq.idataacq;
}

};

#endif

