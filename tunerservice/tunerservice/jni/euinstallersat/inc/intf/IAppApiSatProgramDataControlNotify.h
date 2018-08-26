#ifndef IAPPAPISATPROGRAMDATACONTROLNOTIFY_H
#define IAPPAPISATPROGRAMDATACONTROLNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataControlNotify
{
public:
	virtual ~IAppApiSatProgramDataControlNotify(){}
	virtual void OnChannelTuningStart(void)= 0;
	virtual void OnChannelTuningEnd(void)= 0;
};


#define IAppApiSatProgramDataControlNotifyImpl(Comp,intf)    \
virtual void intf ## _OnChannelTuningStart(void);\
virtual void intf ## _OnChannelTuningEnd(void);\
class Comp ## _ ## intf : public IAppApiSatProgramDataControlNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnChannelTuningStart(void){ return m_parent->intf ## _OnChannelTuningStart();}\
virtual void OnChannelTuningEnd(void){ return m_parent->intf ## _OnChannelTuningEnd();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
