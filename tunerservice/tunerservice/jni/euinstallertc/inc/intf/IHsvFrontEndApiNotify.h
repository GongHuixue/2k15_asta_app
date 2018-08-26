#ifndef IHSVFRONTENDAPINOTIFY_H
#define IHSVFRONTENDAPINOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvFrontEndApiNotify
{
public:
	virtual ~IHsvFrontEndApiNotify(){}
	virtual void OnSearchStateChanged(tmFe_SearchState_t state)= 0;
	virtual void OnSearchInProgress(tmFe_SearchState_t state)= 0;
	virtual void OnStationFound(void)= 0;
	virtual void OnStationNotFound(void)= 0;
	virtual void OnTvSystemDetected(tmFe_TvSystem_t tvSystem)= 0;
	virtual void OnAfcFreqChanged(Nat32 freq)= 0;
	virtual void OnAfcLimitReached(Nat32 freq)= 0;
	virtual void OnAfcModeChanged(void)= 0;
	virtual void OnMeasReady(int ssm,Nat32 strength)= 0;
	virtual void OnMeasAborted(int ssm)= 0;
	virtual void OnConstellationDetected(tmFe_Constellation_t constellation)= 0;
	virtual void OnIqModeDetected(tmFe_IqMode_t mode)= 0;
	virtual void OnCodeRateDetected(tmFe_CodeRate_t highPrioRate,tmFe_CodeRate_t lowPrioRate)= 0;
	virtual void OnHierarchyModeDetected(tmFe_HierarchyMode_t mode)= 0;
	virtual void OnGuardIntervalDetected(tmFe_GuardInterval_t interval)= 0;
	virtual void OnTxModeDetected(tmFe_TxMode_t mode)= 0;
	virtual void OnChanBandwidthDetected(tmFe_ChanBandwidth_t bandwith)= 0;
	virtual void OnCarrierPresentChanged(Bool carrier)= 0;
	virtual void OnBerThresholdCrossed(Nat32 ber,Nat32 berThreshold)= 0;
};


#define IHsvFrontEndApiNotifyImpl(Comp,intf)    \
virtual void intf ## _OnSearchStateChanged(tmFe_SearchState_t state);\
virtual void intf ## _OnSearchInProgress(tmFe_SearchState_t state);\
virtual void intf ## _OnStationFound(void);\
virtual void intf ## _OnStationNotFound(void);\
virtual void intf ## _OnTvSystemDetected(tmFe_TvSystem_t tvSystem);\
virtual void intf ## _OnAfcFreqChanged(Nat32 freq);\
virtual void intf ## _OnAfcLimitReached(Nat32 freq);\
virtual void intf ## _OnAfcModeChanged(void);\
virtual void intf ## _OnMeasReady(int ssm,Nat32 strength);\
virtual void intf ## _OnMeasAborted(int ssm);\
virtual void intf ## _OnConstellationDetected(tmFe_Constellation_t constellation);\
virtual void intf ## _OnIqModeDetected(tmFe_IqMode_t mode);\
virtual void intf ## _OnCodeRateDetected(tmFe_CodeRate_t highPrioRate,tmFe_CodeRate_t lowPrioRate);\
virtual void intf ## _OnHierarchyModeDetected(tmFe_HierarchyMode_t mode);\
virtual void intf ## _OnGuardIntervalDetected(tmFe_GuardInterval_t interval);\
virtual void intf ## _OnTxModeDetected(tmFe_TxMode_t mode);\
virtual void intf ## _OnChanBandwidthDetected(tmFe_ChanBandwidth_t bandwith);\
virtual void intf ## _OnCarrierPresentChanged(Bool carrier);\
virtual void intf ## _OnBerThresholdCrossed(Nat32 ber,Nat32 berThreshold);\
class Comp ## _ ## intf : public IHsvFrontEndApiNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnSearchStateChanged(tmFe_SearchState_t state){ return m_parent->intf ## _OnSearchStateChanged(state);}\
virtual void OnSearchInProgress(tmFe_SearchState_t state){ return m_parent->intf ## _OnSearchInProgress(state);}\
virtual void OnStationFound(void){ return m_parent->intf ## _OnStationFound();}\
virtual void OnStationNotFound(void){ return m_parent->intf ## _OnStationNotFound();}\
virtual void OnTvSystemDetected(tmFe_TvSystem_t tvSystem){ return m_parent->intf ## _OnTvSystemDetected(tvSystem);}\
virtual void OnAfcFreqChanged(Nat32 freq){ return m_parent->intf ## _OnAfcFreqChanged(freq);}\
virtual void OnAfcLimitReached(Nat32 freq){ return m_parent->intf ## _OnAfcLimitReached(freq);}\
virtual void OnAfcModeChanged(void){ return m_parent->intf ## _OnAfcModeChanged();}\
virtual void OnMeasReady(int ssm,Nat32 strength){ return m_parent->intf ## _OnMeasReady(ssm,strength);}\
virtual void OnMeasAborted(int ssm){ return m_parent->intf ## _OnMeasAborted(ssm);}\
virtual void OnConstellationDetected(tmFe_Constellation_t constellation){ return m_parent->intf ## _OnConstellationDetected(constellation);}\
virtual void OnIqModeDetected(tmFe_IqMode_t mode){ return m_parent->intf ## _OnIqModeDetected(mode);}\
virtual void OnCodeRateDetected(tmFe_CodeRate_t highPrioRate,tmFe_CodeRate_t lowPrioRate){ return m_parent->intf ## _OnCodeRateDetected(highPrioRate,lowPrioRate);}\
virtual void OnHierarchyModeDetected(tmFe_HierarchyMode_t mode){ return m_parent->intf ## _OnHierarchyModeDetected(mode);}\
virtual void OnGuardIntervalDetected(tmFe_GuardInterval_t interval){ return m_parent->intf ## _OnGuardIntervalDetected(interval);}\
virtual void OnTxModeDetected(tmFe_TxMode_t mode){ return m_parent->intf ## _OnTxModeDetected(mode);}\
virtual void OnChanBandwidthDetected(tmFe_ChanBandwidth_t bandwith){ return m_parent->intf ## _OnChanBandwidthDetected(bandwith);}\
virtual void OnCarrierPresentChanged(Bool carrier){ return m_parent->intf ## _OnCarrierPresentChanged(carrier);}\
virtual void OnBerThresholdCrossed(Nat32 ber,Nat32 berThreshold){ return m_parent->intf ## _OnBerThresholdCrossed(ber,berThreshold);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
