#ifndef  _CHSVSATELLITEFRONTEND_MSILABS_H
#define  _CHSVSATELLITEFRONTEND_MSILABS_H 

#include <InfraGlobals.h>
#include <provreq.h>
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
#include <tprtkdefines.h>
#include <IHsvWindowDestinationMap.h>
class CHsvSatelliteFrontEnd_msilabs_Priv;
class CHsvSatelliteFrontEnd_msilabs
{
public:
ProvidesInterface<IPlfApiTuningNotify>	plfapidvbsN;

ProvidesInterface<IHsvPower>	sipow;

ProvidesInterface<IHsvSatelliteFrontEnd>	sisatfrontend;

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
public:
CHsvSatelliteFrontEnd_msilabs();
virtual ~CHsvSatelliteFrontEnd_msilabs();
private:
CHsvSatelliteFrontEnd_msilabs_Priv	*m_priv;
};

#endif

