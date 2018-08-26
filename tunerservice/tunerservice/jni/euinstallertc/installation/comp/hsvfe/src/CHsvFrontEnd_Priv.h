#ifndef  _CHSVFRONTEND_PRIV_H
#define  _CHSVFRONTEND_PRIV_H 

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
#include <CTCMwBase.h>
class CHsvFrontEnd_Priv;
#define CLASSSCOPE CHsvFrontEnd_Priv::
#include "locals_m.h"

class CHsvFrontEnd_Priv : public CTCMwBase
{
public:
virtual ~CHsvFrontEnd_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IPlfApiSigStrengthMeasNotifyImpl(CHsvFrontEnd_Priv,assmN);
IPlfApiChanDecNotifyImpl(CHsvFrontEnd_Priv,chdec2N);
IPlfApiChanDecNotifyImpl(CHsvFrontEnd_Priv,chdecN);
IHsvFrontEndApiImpl(CHsvFrontEnd_Priv,feapi);
IPlfApiTuningNotifyImpl(CHsvFrontEnd_Priv,fetunN);
IHsvPowerImpl(CHsvFrontEnd_Priv,pow);
IPlfApiSigStrengthMeasNotifyImpl(CHsvFrontEnd_Priv,qssmN);
IPlfApiSigStrengthMeasNotifyImpl(CHsvFrontEnd_Priv,vssmN);
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
CHsvFrontEnd_Priv():i__assmN(this),i__chdec2N(this),i__chdecN(this),i__feapi(this),i__fetunN(this),i__pow(this),i__qssmN(this),i__vssmN(this)
{
assmN	=	&i__assmN;
chdec2N	=	&i__chdec2N;
chdecN	=	&i__chdecN;
feapi	=	&i__feapi;
fetunN	=	&i__fetunN;
pow	=	&i__pow;
qssmN	=	&i__qssmN;
vssmN	=	&i__vssmN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define assm_iPresent() (assm.Present())
#define assm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	assm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define assm_Start(winid,Avail,retval)	assm->Start(winid,Avail,retval)
#define assm_Stop(winid,Stopped,retval)	assm->Stop(winid,Stopped,retval)
#define assm_GetMeasValid(winid,Valid,retval)	assm->GetMeasValid(winid,Valid,retval)
#define assm_GetSigStrength(winid,Strength,retval)	assm->GetSigStrength(winid,Strength,retval)
#define chdec_iPresent() (chdec.Present())
#define chdec_GetActualConstellation(winid,decoder,pConstellation,retval)	chdec->GetActualConstellation(winid,decoder,pConstellation,retval)
#define chdec_SetConstellation(winid,decoder,constellation,retval)	chdec->SetConstellation(winid,decoder,constellation,retval)
#define chdec_GetCarrierPresent(winid,Present,retval)	chdec->GetCarrierPresent(winid,Present,retval)
#define chdec_GetBer(winid,decoder,Ber)	chdec->GetBer(winid,decoder,Ber)
#define chdecC_iPresent() (chdecC.Present())
#define chdecC_GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)	chdecC->GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)
#define chdecC_SetSymbolRate(winid,rate,retval)	chdecC->SetSymbolRate(winid,rate,retval)
#define chdecC_GetSymbolRate(winid,rate,retval)	chdecC->GetSymbolRate(winid,rate,retval)
#define chdecC_SetSearchRates(winid,SearchRate,size,retval)	chdecC->SetSearchRates(winid,SearchRate,size,retval)
#define chdecC_SetFreqStep(winid,step,retval)	chdecC->SetFreqStep(winid,step,retval)
#define chdecC_GetFreqStep(winid,step,retval)	chdecC->GetFreqStep(winid,step,retval)
#define chdecT_iPresent() (chdecT.Present())
#define chdecT_SetChanBandwidth(winid,bandwidth,retval)	chdecT->SetChanBandwidth(winid,bandwidth,retval)
#define chdecT_GetActualChanBandwidth(winid,Bandwidth,retval)	chdecT->GetActualChanBandwidth(winid,Bandwidth,retval)
#define chdecT_SetStreamPriority(winid,streamPriority,retval)	chdecT->SetStreamPriority(winid,streamPriority,retval)
#define chdecT_GetStreamPriority(winid,streamPriority,retval)	chdecT->GetStreamPriority(winid,streamPriority,retval)
#define chdecT_GetHierarchyMuxPresence(winid, HierarchyMuxPresent, retval)	chdecT->GetHierarchyMuxPresence(winid, HierarchyMuxPresent, retval);
#define chdecT_GetTPSId(winid,TPSId,retval)	chdecT->GetTPSId(winid,TPSId,retval)
#define feapiN_iPresent() (feapiN.Present())
#define feapiN_OnSearchStateChanged(state)	feapiN->OnSearchStateChanged(state)
#define feapiN_OnSearchInProgress(state)	feapiN->OnSearchInProgress(state)
#define feapiN_OnStationFound()	feapiN->OnStationFound()
#define feapiN_OnStationNotFound()	feapiN->OnStationNotFound()
#define feapiN_OnTvSystemDetected(tvSystem)	feapiN->OnTvSystemDetected(tvSystem)
#define feapiN_OnAfcFreqChanged(freq)	feapiN->OnAfcFreqChanged(freq)
#define feapiN_OnAfcLimitReached(freq)	feapiN->OnAfcLimitReached(freq)
#define feapiN_OnAfcModeChanged()	feapiN->OnAfcModeChanged()
#define feapiN_OnMeasReady(ssm,strength)	feapiN->OnMeasReady(ssm,strength)
#define feapiN_OnMeasAborted(ssm)	feapiN->OnMeasAborted(ssm)
#define feapiN_OnConstellationDetected(constellation)	feapiN->OnConstellationDetected(constellation)
#define feapiN_OnIqModeDetected(mode)	feapiN->OnIqModeDetected(mode)
#define feapiN_OnCodeRateDetected(highPrioRate,lowPrioRate)	feapiN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define feapiN_OnHierarchyModeDetected(mode)	feapiN->OnHierarchyModeDetected(mode)
#define feapiN_OnGuardIntervalDetected(interval)	feapiN->OnGuardIntervalDetected(interval)
#define feapiN_OnTxModeDetected(mode)	feapiN->OnTxModeDetected(mode)
#define feapiN_OnChanBandwidthDetected(bandwith)	feapiN->OnChanBandwidthDetected(bandwith)
#define feapiN_OnCarrierPresentChanged(carrier)	feapiN->OnCarrierPresentChanged(carrier)
#define feapiN_OnBerThresholdCrossed(ber,berThreshold)	feapiN->OnBerThresholdCrossed(ber,berThreshold)
#define fetun_iPresent() (fetun.Present())
#define fetun_GetFreqRange(winid,MinFreq,MaxFreq,retval)	fetun->GetFreqRange(winid,MinFreq,MaxFreq,retval)
#define fetun_GetFreq(winid,Freq,retval)	fetun->GetFreq(winid,Freq,retval)
#define fetun_SetFreq(winid,freq,finetune,retval)	fetun->SetFreq(winid,freq,finetune,retval)
#define fetun_GetTvSystemSupp(winid,tvSystem,Supp,retval)	fetun->GetTvSystemSupp(winid,tvSystem,Supp,retval)
#define fetun_GetTvSystem(winid,TvSystem,retval)	fetun->GetTvSystem(winid,TvSystem,retval)
#define fetun_SetTvSystem(winid,TvSystem,retval)	fetun->SetTvSystem(winid,TvSystem,retval)
#define fetun_StartSearch(winid,startFreq,mode,endFreq,retval)	fetun->StartSearch(winid,startFreq,mode,endFreq,retval)
#define fetun_StopSearch(winid,retval)	fetun->StopSearch(winid,retval)
#define plferrids_iPresent() (plferrids.Present())
#define plferrids_Ok	IPlfApiErrorIds_Ok
#define plferrids_ResourceNotOwned	IPlfApiErrorIds_ResourceNotOwned
#define plferrids_InterfaceNotAvailable	IPlfApiErrorIds_InterfaceNotAvailable
#define plferrids_InterfaceNotImplemented	IPlfApiErrorIds_InterfaceNotImplemented
#define plferrids_Other	IPlfApiErrorIds_Other
#define qssm_iPresent() (qssm.Present())
#define qssm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	qssm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define qssm_Start(winid,Avail,retval)	qssm->Start(winid,Avail,retval)
#define qssm_Stop(winid,Stopped,retval)	qssm->Stop(winid,Stopped,retval)
#define qssm_GetMeasValid(winid,Valid,retval)	qssm->GetMeasValid(winid,Valid,retval)
#define qssm_GetSigStrength(winid,Strength,retval)	qssm->GetSigStrength(winid,Strength,retval)
#define vssm_iPresent() (vssm.Present())
#define vssm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	vssm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define vssm_Start(winid,Avail,retval)	vssm->Start(winid,Avail,retval)
#define vssm_Stop(winid,Stopped,retval)	vssm->Stop(winid,Stopped,retval)
#define vssm_GetMeasValid(winid,Valid,retval)	vssm->GetMeasValid(winid,Valid,retval)
#define vssm_GetSigStrength(winid,Strength,retval)	vssm->GetSigStrength(winid,Strength,retval)
#define feapi_SigAssm	IHsvFrontEndApi_SigAssm
#define feapi_SigVssm	IHsvFrontEndApi_SigVssm
#define feapi_SigQssm	IHsvFrontEndApi_SigQssm
#define feapi_SigSssm	IHsvFrontEndApi_SigSssm
#define feapi_ChanDecDvbT	IHsvFrontEndApi_ChanDecDvbT
#define feapi_ChanDecDvbC	IHsvFrontEndApi_ChanDecDvbC
#define feapi_ChanDecDvbS	IHsvFrontEndApi_ChanDecDvbS
#define feapi_ChanDecISDBT	IHsvFrontEndApi_ChanDecISDBT
#define feapi_ChanDecDvbT2	IHsvFrontEndApi_ChanDecDvbT2
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

