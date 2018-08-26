#ifndef  _CHSVDVBTMPEGINSTALLATION_H
#define  _CHSVDVBTMPEGINSTALLATION_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvDvbtMpegInstallation_m.h>
#include <CHsvDvbtMpegInstallation_mdigacq.h>
#include <IHsvSdmControlNotify.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvDigitalScan.h>
#include <IEnable.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvDigitalScanNotify.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvInstallationDivSupport.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvInstallationNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvMediaControl.h>
#include <IPumpEngine.h>
#include <IHsvProgramData3.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortedTable2.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvWindowDestinationMap.h>

class CHsvDvbtMpegInstallation
{
public:
virtual ~CHsvDvbtMpegInstallation(){}

//Contained Modules
private:
CHsvDvbtMpegInstallation_m m;
CHsvDvbtMpegInstallation_mdigacq mdigacq;
public:
ProvidesInterface<IHsvSdmControlNotify>	ctrlN;

ProvidesInterface<IHsvDigitalAcquisition>	digacq;

ProvidesInterface<IHsvDigitalScan>	digscan;

ProvidesInterface<IEnable>	ena;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvSdmControl2>	ctrl;
RequiresInterface<IHsvDigitalScanNotify>	digscanN;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvInstallationDivSupport>	divsupp;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvInstallationNotify>	insN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMediaControl>	mctl;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvStream>	strapi;
RequiresInterface<IHsvStreamFilter>	strmfltr;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvDvbtMpegInstallation);

public:
CHsvDvbtMpegInstallation()
{
ena	=	m.ena;
feapiN	=	m.feapiN;
pow	=	m.pow;
digscan	=	m.idigscan;
strapiN	=	m.strapiN;
ctrlN	=	m.ctrlN;
digacq	=	mdigacq.idigacq;
m.pmp	=	pmp;
m.pen	=	pen;
m.feapi	=	feapi;
m.instutil	=	instutil;
m.rins	=	rins;
m.sigstr	=	sigstr;
m.ctrl	=	ctrl;
m.strapi	=	strapi;
m.log	=	log;
m.idigacq	=	mdigacq.idigacq;
m.div	=	div;
m.err	=	err;
m.mctl	=	mctl;
m.strmfltr	=	strmfltr;
m.insN	=	insN;
m.digscanN	=	digscanN;
m.pgdb	=	pgdb;
m.wnddest	=	wnddest;
m.plferrids	=	plferrids;
m.sysset	=	sysset;
m.freqctl	=	freqctl;
m.sort	=	sort;
m.eurdiv	=	eurdiv;
mdigacq.idigscan	=	m.idigscan;
mdigacq.strapi	=	strapi;
mdigacq.pgdb	=	pgdb;
mdigacq.pgdbconst	=	pgdbconst;
mdigacq.pgdat	=	pgdat;
mdigacq.divsupp	=	divsupp;
mdigacq.div	=	div;
mdigacq.sigstr	=	sigstr;
mdigacq.rins	=	rins;
mdigacq.log	=	log;
mdigacq.instutil	=	instutil;
mdigacq.sort	=	sort;
mdigacq.sysset	=	sysset;
mdigacq.cids	=	cids;
mdigacq.feapi	=	feapi;
mdigacq.eurdiv	=	eurdiv;
mdigacq.srtdb	=	srtdb;
}

};

#endif

