#ifndef  _CHSVDVBSOPPROFILE_H
#define  _CHSVDVBSOPPROFILE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbsOpProfile_mAcq.h>
#include <CHsvDvbsOpProfile_mScan.h>
#include <CHsvDvbsOpProfile_mSort.h>
#include <IHsvDigitalAcquisition.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSystemSettingsNotify.h>
#include <IProdApiClockEx.h>
#include <IHsvCamDataParser.h>
#include <IHsvSdmEnable.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvMediaControl.h>
#include <ICesOperatorProfile.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPrescanParser.h>
#include <IHsvSdmControlNotifyEx.h>
class CHsvDvbsOpProfile;

class CHsvDvbsOpProfile
{

private:
	//Contained Modules
	CHsvDvbsOpProfile_mAcq mAcq;
	CHsvDvbsOpProfile_mScan mScan;
	CHsvDvbsOpProfile_mSort mSort;

	Pumpdefines(CHsvDvbsOpProfile);

public:
	//Provides interfaces
	ProvidesInterface<IHsvSatellitePackageInstallation>	ins;
	ProvidesInterface<IHsvDigitalAcquisition>	dataacq;
	ProvidesInterface<ICesOperatorProfileNotify> opinsN;
	ProvidesInterface<IHsvPower>	pow;
	ProvidesInterface<IHsvStreamNotify>	strapiN;
	ProvidesInterface<IHsvSystemSettingsNotify>	syssetN;
	ProvidesInterface<IHsvSorting>	sort;	
	ProvidesInterface<IHsvSatelliteFrontEndNotify> plfApidvbsN;
	ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

	//Required interfaces
	RequiresInterface<IProdApiClockEx>	Timerclk;
	RequiresInterface<IHsvCamDataParser>	camdataparser;
	RequiresInterface<IHsvSdmEnable>	camnitena;
	RequiresInterface<IHsvCountryIds>	cids;
	RequiresInterface<IHsvSdmControl2>	ctrl;
	RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
	RequiresInterface<IHsvPrescanParser>	iprescanparser;
	RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
	RequiresInterface<IHsvErrorCodeEx>	hsverr;
	RequiresInterface<IHsvMediaControl>	mctl;
	RequiresInterface<ICesOperatorProfile>	opins;
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IHsvProgramData3>	pgdat;
	RequiresInterface<IHsvProgramDatabase>	pgdb;
	RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
	RequiresInterface<IPlfApiErrorIds>	plferrids;
	RequiresInterface<ITvPlatformResource>	plfres;
	RequiresInterface<IPumpExSub>	pmp;
	RequiresInterface<IHsvInstallationSigStrength>	sigstr;
	RequiresInterface<IHsvSortedTable2>	srtdb;
	RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
	RequiresInterface<IString>	str;
	RequiresInterface<IHsvStream>	strapi;
	RequiresInterface<IHsvStreamFilter>	strmfltr;
	RequiresInterface<IHsvWindowDestinationMap>	wnddest;	
	RequiresInterface<IAppApiSystemSettings5> apsysset;	
	RequiresInterface<IHsvSatelliteSettings>	idvbset;
	RequiresInterface<IHsvSatelliteInstallationNotify>	insN;

	//Constructor
	CHsvDvbsOpProfile()
	{
		pow		=	mScan.pow;
		ins		= 	mScan.satpkgins;
		opinsN	=	mScan.opinsN;
		strapiN	=	mScan.strapiN;
		plfApidvbsN	=	mScan.satfeN;
		ctrlN	=	mScan.ctrlN;
		mScan.pmp	=	pmp;
		mScan.pen	=	pen;
		mScan.sigstr	=	sigstr;
		mScan.ctrl	=	ctrl;
		mScan.mctl	=	mctl;
		mScan.plferrids	=	plferrids;
		mScan.idataacq	=	mAcq.idataacq;
		mScan.wnddest	=	wnddest;
		mScan.eurdiv	=	eurdiv;
		mScan.cids	=	cids;
		mScan.camnitena	=	camnitena;
		mScan.hsverr	=	hsverr;
		mScan.opins	=	opins;
		mScan.strapi	=	strapi;
		mScan.camdataparser	=	camdataparser;
		mScan.apsysset		=	apsysset;
		mScan.idvbset		= 	idvbset;		
		mScan.insN			= 	insN;
		mScan.iacqpow		= 	mAcq.iacqpow;
		mScan.isortpow		= 	mSort.isortpow;
		mScan.satfeapi		= 	satfeapi;
		dataacq	=	mAcq.idataacq;
		mAcq.strapi	=	strapi;
		mAcq.pgdbconst	=	pgdbconst;
		mAcq.pgdb	=	pgdb;
		mAcq.eurdiv	=	eurdiv;
		mAcq.pen	= 	pen;
		mAcq.pmp	= 	pmp;
		mAcq.isvcscandata	= mScan.iscandata;
		mAcq.rins		= mScan.satpkgins;
		mAcq.idataacqN	= mScan.dataacqN;
		mAcq.iprescanparser = iprescanparser;
		sort				= mSort.isort;
		mSort.pen		= pen;
		mSort.pmp		= pmp;
		mSort.pgdat		= pgdat;
		mSort.pgdb		= pgdb;
		mSort.pgdbconst	= pgdbconst;
		mSort.insN		= insN;
		mSort.rins		= mScan.satpkgins;
	}

	//Destructor
	virtual ~CHsvDvbsOpProfile() {}
};

#endif
