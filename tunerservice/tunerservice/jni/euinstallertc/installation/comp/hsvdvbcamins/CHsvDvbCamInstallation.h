#ifndef  _CHSVDVBCAMINSTALLATION_H
#define  _CHSVDVBCAMINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbCamInstallation_mDataAcq.h>
#include <CHsvDvbCamInstallation_mScan.h>
#include <CHsvDvbCamInstallation_mSettings.h>
#include <IHsvDigitalAcquisition.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSystemSettingsNotifyEx.h>
#include <IProdApiClockEx.h>
#include <IHsvCamScanHelper.h>
#include <IHsvSdmEnable.h>
#include <IPlfApiChanDecDvbT2.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IProdApiFlashFileSystemDirectoryExEx.h>
#include <IHsvPool.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <ICesOperatorProfile.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvCamPresetSort.h>
#include <IHsvSortRoute.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IString.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include<IMultiLingualStringConversion.h>
#include <IHsvCharSetUtility2.h>

class CHsvDvbCamInstallation;

class CHsvDvbCamInstallation
{
public:
virtual ~CHsvDvbCamInstallation(){}

//Contained Modules
private:
CHsvDvbCamInstallation_mDataAcq mDataAcq;
CHsvDvbCamInstallation_mScan mScan;
CHsvDvbCamInstallation_mSettings mSettings;
public:
ProvidesInterface<IHsvDigitalAcquisition>	dataacq;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	ins;
ProvidesInterface<IHsvDVBSettings>	dvbset;

ProvidesInterface<ICesOperatorProfileNotify>	opinsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

ProvidesInterface<IHsvSystemSettingsNotifyEx>	syssetN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvCamScanHelper>	camScanparser;
RequiresInterface<IHsvSdmEnable>	camena;
RequiresInterface<IPlfApiChanDecDvbT2>	chdecdvbt2;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IProdApiFlashFileSystemDirectoryExEx>	ffsdir;
RequiresInterface<IHsvPool>	hpool;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<ICesOperatorProfile>	opins;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvCamPresetSort>	sort;
RequiresInterface<IHsvSortRoute>	sortroute;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IString>	str;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IMultiLingualStringConversion>	ling;
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
private:
Pumpdefines(CHsvDvbCamInstallation);

public:
CHsvDvbCamInstallation()
{
pow	=	mScan.pow;
ena	=	mScan.ena;
ins	=	mScan.iins;
mScan.isetpow = mSettings.isetpow;
opinsN	=	mScan.opinsN;
feapiN	=	mScan.feapiN;
strapiN	=	mScan.strapiN;
mScan.pmp	=	pmp;
mScan.pen	=	pen;
mScan.rins	=	rins;
mScan.feapi	=	feapi;
mScan.sigstr	=	sigstr;
mScan.ctrl	=	ctrl;
mScan.insN	=	insN;
mScan.mctl	=	mctl;
mScan.plferrids	=	plferrids;
mScan.sysset	=	sysset;
mScan.idataacq	=	mDataAcq.idataacq;
mScan.wnddest	=	wnddest;
mScan.chdecdvbt2	=	chdecdvbt2;
mScan.eurdiv	=	eurdiv;
mScan.cids	=	cids;
mScan.camena	=	camena;
mScan.hsverr	=	hsverr;
mScan.opins	=	opins;
mScan.strapi	=	strapi;
mScan.camScanparser	=	camScanparser;
dataacq	=	mDataAcq.idataacq;
mDataAcq.Timerclk	=	Timerclk;
mDataAcq.strapi	=	strapi;
mDataAcq.pgdbconst	=	pgdbconst;
mDataAcq.pgdb	=	pgdb;
mDataAcq.rins	=	rins;
mDataAcq.pgdat	=	pgdat;
mDataAcq.iins	=	mScan.iins;
mDataAcq.icamhelper	=	mScan.icamhelper;
mDataAcq.feapi	=	feapi;
mDataAcq.srtdbids	=	srtdbids;
mDataAcq.srtdb	=	srtdb;
mDataAcq.sysset	=	sysset;
mDataAcq.eurdiv	=	eurdiv;
mDataAcq.sort	=	sort;
dvbset = mSettings.idvbset;
mScan.camacqhelper = mDataAcq.pcamhelper;
mScan.idvbset = mSettings.idvbset;
mDataAcq.idvbset = mSettings.idvbset;
mDataAcq.ling = ling;
mDataAcq.charsetutil = charsetutil;
mSettings.str	=	str;
mSettings.rins = rins;
}

};

#endif

