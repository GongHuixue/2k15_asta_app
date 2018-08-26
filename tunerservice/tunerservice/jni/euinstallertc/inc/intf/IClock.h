#ifndef ICLOCK_H
#define ICLOCK_H
#include <intfparam.h>
#include <provreq.h>
class IClock
{
public:
	virtual ~IClock(){}
	virtual Nat32 SecondsSinceWakeup(void)= 0;
	virtual Bool ClockIsSet(void)= 0;
	virtual void SetClock(DateTime utc,DateTime lto)= 0;
	virtual DateTime GetUniversalTime(void)= 0;
	virtual DateTime GetLocalTimeOffset(void)= 0;
	virtual DateTime GetLocalTime(void)= 0;
	virtual void RunDuringStandby(Bool enable)= 0;
	virtual void SetAlarm(DateTime alarm)= 0;
	virtual void CancelAlarm(void)= 0;
	virtual Bool AlarmIsSet(void)= 0;
	virtual DateTime GetAlarm(void)= 0;
	virtual void SetWakeupMode(Bool enable)= 0;
	virtual Bool CausedWakeup(void)= 0;
};


#define IClockImpl(Comp,intf)    \
virtual Nat32 intf ## _SecondsSinceWakeup(void);\
virtual Bool intf ## _ClockIsSet(void);\
virtual void intf ## _SetClock(DateTime utc,DateTime lto);\
virtual DateTime intf ## _GetUniversalTime(void);\
virtual DateTime intf ## _GetLocalTimeOffset(void);\
virtual DateTime intf ## _GetLocalTime(void);\
virtual void intf ## _RunDuringStandby(Bool enable);\
virtual void intf ## _SetAlarm(DateTime alarm);\
virtual void intf ## _CancelAlarm(void);\
virtual Bool intf ## _AlarmIsSet(void);\
virtual DateTime intf ## _GetAlarm(void);\
virtual void intf ## _SetWakeupMode(Bool enable);\
virtual Bool intf ## _CausedWakeup(void);\
class Comp ## _ ## intf : public IClock \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Nat32 SecondsSinceWakeup(void){ return m_parent->intf ## _SecondsSinceWakeup();}\
virtual Bool ClockIsSet(void){ return m_parent->intf ## _ClockIsSet();}\
virtual void SetClock(DateTime utc,DateTime lto){ return m_parent->intf ## _SetClock(utc,lto);}\
virtual DateTime GetUniversalTime(void){ return m_parent->intf ## _GetUniversalTime();}\
virtual DateTime GetLocalTimeOffset(void){ return m_parent->intf ## _GetLocalTimeOffset();}\
virtual DateTime GetLocalTime(void){ return m_parent->intf ## _GetLocalTime();}\
virtual void RunDuringStandby(Bool enable){ return m_parent->intf ## _RunDuringStandby(enable);}\
virtual void SetAlarm(DateTime alarm){ return m_parent->intf ## _SetAlarm(alarm);}\
virtual void CancelAlarm(void){ return m_parent->intf ## _CancelAlarm();}\
virtual Bool AlarmIsSet(void){ return m_parent->intf ## _AlarmIsSet();}\
virtual DateTime GetAlarm(void){ return m_parent->intf ## _GetAlarm();}\
virtual void SetWakeupMode(Bool enable){ return m_parent->intf ## _SetWakeupMode(enable);}\
virtual Bool CausedWakeup(void){ return m_parent->intf ## _CausedWakeup();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
