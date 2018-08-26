#ifndef IPLFAPITUNINGNOTIFY_H
#define IPLFAPITUNINGNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiTuningNotify
{
public:
	virtual ~IPlfApiTuningNotify(){}
	virtual void OnSearchStateChanged(tmFe_SearchState_t state)= 0;
	virtual void OnSearchInProgress(tmFe_SearchState_t state)= 0;
	virtual void OnStationFound(void)= 0;
	virtual void OnStationNotFound(void)= 0;
	virtual void OnTvSystemDetected(tmFe_TvSystem_t tvSystem)= 0;
	virtual void OnAfcFreqChanged(Nat32 freq)= 0;
	virtual void OnAfcLimitReached(Nat32 freq)= 0;
	virtual void OnAfcModeChanged(void)= 0;
};


#define IPlfApiTuningNotifyImpl(Comp,intf)    \
virtual void intf ## _OnSearchStateChanged(tmFe_SearchState_t state);\
virtual void intf ## _OnSearchInProgress(tmFe_SearchState_t state);\
virtual void intf ## _OnStationFound(void);\
virtual void intf ## _OnStationNotFound(void);\
virtual void intf ## _OnTvSystemDetected(tmFe_TvSystem_t tvSystem);\
virtual void intf ## _OnAfcFreqChanged(Nat32 freq);\
virtual void intf ## _OnAfcLimitReached(Nat32 freq);\
virtual void intf ## _OnAfcModeChanged(void);\
class Comp ## _ ## intf : public IPlfApiTuningNotify \
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
};\
Comp ## _ ## intf i__ ## intf;


#endif
