#ifndef IPLFAPITUNINGNOTIFY_H
#define IPLFAPITUNINGNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiTuningNotify
{
public:
	virtual ~IPlfApiTuningNotify(){}
	virtual int onScanningStandardDetected(int std,int freq)= 0;
	virtual int onScanAborted(void)= 0;
	virtual int onScanEnded(void)= 0;
	virtual int onTuned(int tuningresult,int freq)= 0;
};


#define IPlfApiTuningNotifyImpl(Comp,intf)    \
virtual int intf ## _onScanningStandardDetected(int std,int freq);\
virtual int intf ## _onScanAborted(void);\
virtual int intf ## _onScanEnded(void);\
virtual int intf ## _onTuned(int tuningresult,int freq);\
class Comp ## _ ## intf : public IPlfApiTuningNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int onScanningStandardDetected(int std,int freq){ return m_parent->intf ## _onScanningStandardDetected(std,freq);}\
virtual int onScanAborted(void){ return m_parent->intf ## _onScanAborted();}\
virtual int onScanEnded(void){ return m_parent->intf ## _onScanEnded();}\
virtual int onTuned(int tuningresult,int freq){ return m_parent->intf ## _onTuned(tuningresult,freq);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
