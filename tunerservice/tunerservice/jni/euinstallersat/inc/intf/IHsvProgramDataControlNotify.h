#ifndef IHSVPROGRAMDATACONTROLNOTIFY_H
#define IHSVPROGRAMDATACONTROLNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataControlNotify
{
public:
	virtual ~IHsvProgramDataControlNotify(){}
	#define IHsvProgramDataControlNotify_SelectedMediumChanged		((int)0 )
	#define IHsvProgramDataControlNotify_InstalledMediumChanged		((int)1 )
	virtual void OnEvent(int event)= 0;
	virtual void OnChannelChangeStart(AppApiChannel channel)= 0;
	virtual void OnChannelChangeEnd(AppApiChannel channel)= 0;
	virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param)= 0;
	virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param)= 0;
	virtual void OnLockStatusChanged(int Status)= 0;
};


#define IHsvProgramDataControlNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int event);\
virtual void intf ## _OnChannelChangeStart(AppApiChannel channel);\
virtual void intf ## _OnChannelChangeEnd(AppApiChannel channel);\
virtual void intf ## _OnDirectTuningStart(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnDirectTuningEnd(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnLockStatusChanged(int Status);\
class Comp ## _ ## intf : public IHsvProgramDataControlNotify \
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
};\
Comp ## _ ## intf i__ ## intf;


#endif
