#ifndef  _CHSVSATELLITEFRONTEND_H
#define  _CHSVSATELLITEFRONTEND_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CHsvSatelliteFrontEnd_msilabs.h>
#include <IPlfApiTuningNotify.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteSettings.h>
#include <IPumpEngine.h>
#include <IPlfApiDvbsTuning.h>
#include <IPlfApiTuning.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <ICeIsTpHostRtk2.h>
#include <IHsvWindowDestinationMap.h>

class CHsvSatelliteFrontEnd
{
public:
virtual ~CHsvSatelliteFrontEnd(){}

//Contained Modules
private:
CHsvSatelliteFrontEnd_msilabs msilabs;
public:
ProvidesInterface<IPlfApiTuningNotify>	plfapidvbsN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvSatelliteFrontEnd>	satfrontend;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteSettings>	hsvsatsettings;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiDvbsTuning>	plfdvbs;
RequiresInterface<IPlfApiTuning>	plftune;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEndNotify>	satfrontendNotify;
RequiresInterface<ICeIsTpHostRtk2>	tprtk;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvSatelliteFrontEnd);
TpRtkDefines(CHsvSatelliteFrontEnd);

public:
CHsvSatelliteFrontEnd()
{
satfrontend	=	msilabs.sisatfrontend;
plfapidvbsN	=	msilabs.plfapidvbsN;
pow	=	msilabs.sipow;
msilabs.plfdvbs	=	plfdvbs;
msilabs.plftune	=	plftune;
msilabs.err	=	err;
msilabs.wnddest	=	wnddest;
msilabs.hsvsatsettings	=	hsvsatsettings;
msilabs.pmp	=	pmp;
msilabs.pen	=	pen;
msilabs.tprtk	=	tprtk;
msilabs.satfrontendNotify	=	satfrontendNotify;
}

};

#endif

