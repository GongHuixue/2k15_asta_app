#ifndef  _CHSVZIGGOINSTALLATION_H
#define  _CHSVZIGGOINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvZiggoInstallation_mBackground.h>
#include <CHsvZiggoInstallation_mDataAcq.h>
#include <CHsvZiggoInstallation_mDtr.h>
#include <CHsvZiggoInstallation_mInstall.h>
#include <CHsvZiggoInstallation_mPreInstall.h>
#include <CHsvZiggoInstallation_mRoute.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvPower.h>
#include <IHsvSortNotify.h>
#include <IHsvStreamNotify.h>
#include <IProdApiClockEx.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvSdmControl2.h>
#include <IHsvDVBSettings.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IHsvProgramSelection2.h>
#include <IPlfApiErrorIds.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IRealTimeKernel.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortRoute.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStream.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvSdmControl2.h>
class CHsvZiggoInstallation
{
public:
virtual ~CHsvZiggoInstallation(){}

//Contained Modules
private:
CHsvZiggoInstallation_mBackground mBackground;
CHsvZiggoInstallation_mDataAcq mDataAcq;
CHsvZiggoInstallation_mDtr mDtr;
CHsvZiggoInstallation_mInstall mInstall;
CHsvZiggoInstallation_mPreInstall mPreInstall;
CHsvZiggoInstallation_mRoute mRoute;
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvDigitalAcquisition>	dataacq;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	ins;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSortNotify>	sortN;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IProdApiClockEx>	Timerclk;
RequiresInterface<IHsvChannelLibReturnCodes>	chanret;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvDVBSettings>	dvbset;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvErrorCodeEx>	hsverr;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IHsvProgramSelection2>	pgsel;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IRealTimeKernel>	rtk;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortRoute>	sortroute;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<IHsvStreamFilter>strmfltr;
private:
Pumpdefines(CHsvZiggoInstallation);

public:
CHsvZiggoInstallation()
{
mRoute.ipreinspow	=	mPreInstall.ipreinspow;
mRoute.iinspow	=	mInstall.iinspow;
mRoute.ibckgpow	=	mBackground.ibckgpow;
mRoute.idtrpow	=	mDtr.idtrpow;
mRoute.rins	=	rins;
mRoute.ipreinsfeapiN	=	mPreInstall.ipreinsfeapiN;
mRoute.iinsfeapiN	=	mInstall.iinsfeapiN;
mRoute.idtrfeapiN	=	mDtr.idtrfeapiN;
mRoute.ipreinsctrlN	=	mPreInstall.ipreinsctrlN;
mRoute.iinsctrlN	=	mInstall.iinsctrlN;
mRoute.ibckgctrlN	=	mBackground.ibckgctrlN;
pow	=	mRoute.pow;
feapiN	=	mRoute.feapiN;
ctrlN	=	mRoute.ctrlN;
mPreInstall.pmp	=	pmp;
mPreInstall.pen	=	pen;
mPreInstall.idataacq	=	mDataAcq.idataacq;
mPreInstall.ctrl	=	ctrl;
mPreInstall.rins	=	rins;
mPreInstall.insN	=	insN;
mPreInstall.strapi	=	strapi;
mPreInstall.feapi	=	feapi;
mPreInstall.eurdiv	=	eurdiv;
mPreInstall.wnddest	=	wnddest;
mPreInstall.plferrids	=	plferrids;
mPreInstall.hsverr	=	hsverr;
mPreInstall.dvbset	=	dvbset;
mPreInstall.sigstr	=	sigstr;
mPreInstall.mctl	=	mctl;
mPreInstall.ibckg	=	mBackground.ibckg;
mInstall.pmp	=	pmp;
mInstall.pen	=	pen;
mInstall.idataacq	=	mDataAcq.idataacq;
mInstall.ctrl	=	ctrl;
mInstall.rins	=	rins;
mInstall.insN	=	insN;
mInstall.strapi	=	strapi;
mInstall.feapi	=	feapi;
mInstall.eurdiv	=	eurdiv;
mInstall.wnddest	=	wnddest;
mInstall.plferrids	=	plferrids;
mInstall.hsverr	=	hsverr;
mInstall.sigstr	=	sigstr;
mInstall.dvbset	=	dvbset;
mInstall.mctl	=	mctl;
mInstall.ibckg	=	mBackground.ibckg;
mBackground.pmp	=	pmp;
mBackground.pen	=	pen;
mBackground.idataacq	=	mDataAcq.idataacq;
mBackground.rins	=	rins;
mBackground.strapi	=	strapi;
mBackground.feapi	=	feapi;
mBackground.eurdiv	=	eurdiv;
mBackground.wnddest	=	wnddest;
mBackground.sort	=	sort;
mBackground.plfres	=	plfres;
mBackground.pgdb	=	pgdb;
mBackground.sigstr	=	sigstr;
mBackground.dvbset	=	dvbset;
mBackground.insN	=	insN;
mBackground.pgdat	=	pgdat;
mBackground.pgdbconst	=	pgdbconst;
mBackground.pgsel	=	pgsel;
mBackground.rtk	=	rtk;
mBackground.chanret	=	chanret;
ena	=	mBackground.ena;
strapiN	=	mBackground.strapiN;
mBackground.idatastrapiN = mDataAcq.strapiN;
sortN	=	mBackground.sortN;
mDataAcq.Timerclk	=	Timerclk;
mDataAcq.strapi	=	strapi;
mDataAcq.pgdbconst	=	pgdbconst;
mDataAcq.pgdb	=	pgdb;
mDataAcq.rins	=	rins;
mDataAcq.pgdat	=	pgdat;
mDataAcq.eurdiv	=	eurdiv;
mDataAcq.strmfltr = strmfltr;
mDataAcq.iins	=	mInstall.iins;
mDataAcq.feapi	=	feapi;
mDataAcq.insN	=	insN;
mDataAcq.wnddest	=	wnddest;
mDataAcq.srtdbids	=	srtdbids;
mDataAcq.srtdb	=	srtdb;
mDataAcq.ibckg	=	mBackground.ibckg;
mDataAcq.dvbset	=	dvbset;
mDataAcq.sysset	=	sysset;
mDataAcq.instutil	=	instutil;
mDataAcq.sort	=	sort;
dataacq	=	mDataAcq.idataacq;
mDtr.pmp	=	pmp;
mDtr.pen	=	pen;
mDtr.rins	=	rins;
mDtr.sigstr	=	sigstr;
mDtr.insN	=	insN;
mDtr.hsverr	=	hsverr;
mDtr.ctrl	=	ctrl;
mRoute.ipreins	=	mPreInstall.ipreins;
mRoute.iins	=	mInstall.iins;
mRoute.ibckg	=	mBackground.ibckg;
mRoute.idtr	=	mDtr.idtr;
ins	=	mRoute.ins;
}

};

#endif

