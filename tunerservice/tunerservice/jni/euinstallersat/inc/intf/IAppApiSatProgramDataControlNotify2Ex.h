#ifndef IAPPAPISATPROGRAMDATACONTROLNOTIFY2EX_H
#define IAPPAPISATPROGRAMDATACONTROLNOTIFY2EX_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataControlNotify2Ex
{
public:
	virtual ~IAppApiSatProgramDataControlNotify2Ex(){}
	virtual void OnChannelChangeStart(AppApiChannel channel)= 0;
	virtual void OnChannelChangeEnd(AppApiChannel channel)= 0;
	virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param)= 0;
	virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param)= 0;
	virtual void OnLockStatusChanged(int Status)= 0;
	virtual void OnCCSettingChanged(int CCSetting)= 0;
};


#define IAppApiSatProgramDataControlNotify2ExImpl(Comp,intf)    \
virtual void intf ## _OnChannelChangeStart(AppApiChannel channel);\
virtual void intf ## _OnChannelChangeEnd(AppApiChannel channel);\
virtual void intf ## _OnDirectTuningStart(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnDirectTuningEnd(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnLockStatusChanged(int Status);\
virtual void intf ## _OnCCSettingChanged(int CCSetting);\
class Comp ## _ ## intf : public IAppApiSatProgramDataControlNotify2Ex \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnChannelChangeStart(AppApiChannel channel){ return m_parent->intf ## _OnChannelChangeStart(channel);}\
virtual void OnChannelChangeEnd(AppApiChannel channel){ return m_parent->intf ## _OnChannelChangeEnd(channel);}\
virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param){ return m_parent->intf ## _OnDirectTuningStart(Param);}\
virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param){ return m_parent->intf ## _OnDirectTuningEnd(Param);}\
virtual void OnLockStatusChanged(int Status){ return m_parent->intf ## _OnLockStatusChanged(Status);}\
virtual void OnCCSettingChanged(int CCSetting){ return m_parent->intf ## _OnCCSettingChanged(CCSetting);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
