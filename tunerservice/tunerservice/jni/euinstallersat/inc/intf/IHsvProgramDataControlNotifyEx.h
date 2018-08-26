#ifndef IHSVPROGRAMDATACONTROLNOTIFYEX_H
#define IHSVPROGRAMDATACONTROLNOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataControlNotifyEx
{
public:
	virtual ~IHsvProgramDataControlNotifyEx(){}
	#define IHsvProgramDataControlNotifyEx_SelectedMediumChanged		((int)0 )
	#define IHsvProgramDataControlNotifyEx_InstalledMediumChanged		((int)1 )
	virtual void OnEvent(int event)= 0;
	virtual void OnChannelChangeStart(AppApiChannel channel)= 0;
	virtual void OnChannelChangeEnd(AppApiChannel channel)= 0;
	virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param)= 0;
	virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param)= 0;
	virtual void OnLockStatusChanged(int Status)= 0;
	virtual void OnCCSettingChanged(int CCSetting)= 0;
};


#define IHsvProgramDataControlNotifyExImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int event);\
virtual void intf ## _OnChannelChangeStart(AppApiChannel channel);\
virtual void intf ## _OnChannelChangeEnd(AppApiChannel channel);\
virtual void intf ## _OnDirectTuningStart(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnDirectTuningEnd(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnLockStatusChanged(int Status);\
virtual void intf ## _OnCCSettingChanged(int CCSetting);\
class Comp ## _ ## intf : public IHsvProgramDataControlNotifyEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int event){ return m_parent->intf ## _OnEvent(event);}\
virtual void OnChannelChangeStart(AppApiChannel channel){ return m_parent->intf ## _OnChannelChangeStart(channel);}\
virtual void OnChannelChangeEnd(AppApiChannel channel){ return m_parent->intf ## _OnChannelChangeEnd(channel);}\
virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param){ return m_parent->intf ## _OnDirectTuningStart(Param);}\
virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param){ return m_parent->intf ## _OnDirectTuningEnd(Param);}\
virtual void OnLockStatusChanged(int Status){ return m_parent->intf ## _OnLockStatusChanged(Status);}\
virtual void OnCCSettingChanged(int CCSetting){ return m_parent->intf ## _OnCCSettingChanged(CCSetting);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
