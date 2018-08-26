#ifndef  _CHSVFRONTEND_H
#define  _CHSVFRONTEND_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IPlfApiSigStrengthMeasNotify.h>
#include <IPlfApiChanDecNotify.h>
#include <IHsvFrontEndApi.h>
#include <IPlfApiTuningNotify.h>
#include <IHsvPower.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IPlfApiChanDec.h>
#include <IPlfApiChanDecDvbC.h>
#include <IPlfApiChanDecDvbT.h>
#include <IHsvFrontEndApiNotify.h>
#include <IPlfApiTuning.h>
#include <IPlfApiErrorIds.h>
class CHsvFrontEnd_Priv;
class CHsvFrontEnd
{
public:
ProvidesInterface<IPlfApiSigStrengthMeasNotify>	assmN;

ProvidesInterface<IPlfApiChanDecNotify>	chdec2N;

ProvidesInterface<IPlfApiChanDecNotify>	chdecN;

ProvidesInterface<IHsvFrontEndApi>	feapi;

ProvidesInterface<IPlfApiTuningNotify>	fetunN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IPlfApiSigStrengthMeasNotify>	qssmN;

ProvidesInterface<IPlfApiSigStrengthMeasNotify>	vssmN;

//Required interfaces
public:
RequiresInterface<IPlfApiSigStrengthMeas>	assm;
RequiresInterface<IPlfApiChanDec>	chdec;
RequiresInterface<IPlfApiChanDecDvbC>	chdecC;
RequiresInterface<IPlfApiChanDecDvbT>	chdecT;
RequiresInterface<IHsvFrontEndApiNotify>	feapiN;
RequiresInterface<IPlfApiTuning>	fetun;
RequiresInterface<IPlfApiErrorIds>	plferrids;
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
public:
CHsvFrontEnd();
virtual ~CHsvFrontEnd();
private:
CHsvFrontEnd_Priv	*m_priv;
};

#endif

