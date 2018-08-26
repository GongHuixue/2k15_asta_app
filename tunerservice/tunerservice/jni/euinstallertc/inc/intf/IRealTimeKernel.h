#ifndef IREALTIMEKERNEL_H
#define IREALTIMEKERNEL_H
#include <intfparam.h>
#include <provreq.h>
class IRealTimeKernel
{
public:
	virtual ~IRealTimeKernel(){}
	virtual int PrioHighest(void)= 0;
	virtual int PrioHigh(void)= 0;
	virtual int PrioAboveNormal(void)= 0;
	virtual int PrioNormal(void)= 0;
	virtual int PrioBelowNormal(void)= 0;
	virtual int PrioLow(void)= 0;
	virtual int PrioLowest(void)= 0;
	virtual Task TskCreate(TaskFunction func,int priority,int stacksize)= 0;
	virtual Task TskCreateNoWatchdog(TaskFunction func,int priority,int stacksize)= 0;
	virtual void TskDelete(Task tsk)= 0;
	virtual Task TskCurrent(void)= 0;
	virtual void TskSetPriority(Task tsk,int priority)= 0;
	virtual void TskSuspend(int msecs)= 0;
	virtual void TskResume(Task tsk)= 0;
	virtual void TskBeginCriticalSection(void)= 0;
	virtual void TskEndCriticalSection(void)= 0;
	virtual void TskFeedWatchdog(void)= 0;
	virtual Bool TskBoostWatchdog(int seconds)= 0;
	virtual int TskWatchdogPeriod(void)= 0;
	virtual void IsrBegin(void)= 0;
	virtual void IsrEnd(void)= 0;
	virtual void IsrEvtSend(Task tsk,Event evt)= 0;
	virtual void IsrMbxSend(Mailbox mbx,int msg,int param1,Nat32 param2)= 0;
	virtual Semaphore SemCreate(void)= 0;
	virtual Semaphore SemCreateWithCeiling(int ceiling)= 0;
	virtual void SemDelete(Semaphore sem)= 0;
	virtual void SemAcquire(Semaphore sem)= 0;
	virtual Bool SemAcquireNoWait(Semaphore sem)= 0;
	virtual void SemRelease(Semaphore sem)= 0;
	virtual Event EvtCreate(Task tsk)= 0;
	virtual void EvtDelete(Task tsk,Event evt)= 0;
	virtual void EvtSend(Task tsk,Event evt)= 0;
	virtual Event EvtReceive(Event mask)= 0;
	virtual Event EvtReceiveNoWait(Event mask)= 0;
	virtual Event EvtReceiveWait(Event mask,int msecs)= 0;
	virtual Event EvtGetReserved(Task tsk)= 0;
	virtual Timer TmrCreate(Task tsk,Event evt)= 0;
	virtual void TmrDelete(Timer tmr)= 0;
	virtual void TmrEvery(Timer tmr,int msecs)= 0;
	virtual void TmrOnce(Timer tmr,int msecs)= 0;
	virtual void TmrCancel(Timer tmr)= 0;
	virtual int TmrTime(void)= 0;
	virtual int TmrResolution(void)= 0;
	virtual Mailbox MbxCreate(void)= 0;
	virtual void MbxDelete(Mailbox mbx)= 0;
	virtual void MbxSend(Mailbox mbx,int msg,int param1,Nat32 param2)= 0;
	virtual void MbxReceive(Mailbox mbx,Message * msg)= 0;
	virtual Bool MbxReceiveNoWait(Mailbox mbx,Message * msg)= 0;
	virtual Talos TlsCreate(int size)= 0;
	virtual void* TlsAccess(Talos tls)= 0;
};


#define IRealTimeKernelImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Task intf ## _TskCreate(TaskFunction func,int priority,int stacksize);\
virtual Task intf ## _TskCreateNoWatchdog(TaskFunction func,int priority,int stacksize);\
virtual void intf ## _TskDelete(Task tsk);\
virtual Task intf ## _TskCurrent(void);\
virtual void intf ## _TskSetPriority(Task tsk,int priority);\
virtual void intf ## _TskSuspend(int msecs);\
virtual void intf ## _TskResume(Task tsk);\
virtual void intf ## _TskBeginCriticalSection(void);\
virtual void intf ## _TskEndCriticalSection(void);\
virtual void intf ## _TskFeedWatchdog(void);\
virtual Bool intf ## _TskBoostWatchdog(int seconds);\
virtual int intf ## _TskWatchdogPeriod(void);\
virtual void intf ## _IsrBegin(void);\
virtual void intf ## _IsrEnd(void);\
virtual void intf ## _IsrEvtSend(Task tsk,Event evt);\
virtual void intf ## _IsrMbxSend(Mailbox mbx,int msg,int param1,Nat32 param2);\
virtual Semaphore intf ## _SemCreate(void);\
virtual Semaphore intf ## _SemCreateWithCeiling(int ceiling);\
virtual void intf ## _SemDelete(Semaphore sem);\
virtual void intf ## _SemAcquire(Semaphore sem);\
virtual Bool intf ## _SemAcquireNoWait(Semaphore sem);\
virtual void intf ## _SemRelease(Semaphore sem);\
virtual Event intf ## _EvtCreate(Task tsk);\
virtual void intf ## _EvtDelete(Task tsk,Event evt);\
virtual void intf ## _EvtSend(Task tsk,Event evt);\
virtual Event intf ## _EvtReceive(Event mask);\
virtual Event intf ## _EvtReceiveNoWait(Event mask);\
virtual Event intf ## _EvtReceiveWait(Event mask,int msecs);\
virtual Event intf ## _EvtGetReserved(Task tsk);\
virtual Timer intf ## _TmrCreate(Task tsk,Event evt);\
virtual void intf ## _TmrDelete(Timer tmr);\
virtual void intf ## _TmrEvery(Timer tmr,int msecs);\
virtual void intf ## _TmrOnce(Timer tmr,int msecs);\
virtual void intf ## _TmrCancel(Timer tmr);\
virtual int intf ## _TmrTime(void);\
virtual int intf ## _TmrResolution(void);\
virtual Mailbox intf ## _MbxCreate(void);\
virtual void intf ## _MbxDelete(Mailbox mbx);\
virtual void intf ## _MbxSend(Mailbox mbx,int msg,int param1,Nat32 param2);\
virtual void intf ## _MbxReceive(Mailbox mbx,Message * msg);\
virtual Bool intf ## _MbxReceiveNoWait(Mailbox mbx,Message * msg);\
virtual Talos intf ## _TlsCreate(int size);\
virtual void* intf ## _TlsAccess(Talos tls);\
class Comp ## _ ## intf : public IRealTimeKernel \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_PrioHighest; \
    InterfaceParam<Comp,int> m_PrioHigh; \
    InterfaceParam<Comp,int> m_PrioAboveNormal; \
    InterfaceParam<Comp,int> m_PrioNormal; \
    InterfaceParam<Comp,int> m_PrioBelowNormal; \
    InterfaceParam<Comp,int> m_PrioLow; \
    InterfaceParam<Comp,int> m_PrioLowest; \
    Comp ## _ ## intf( Comp *parent):m_PrioHighest(parent),m_PrioHigh(parent),m_PrioAboveNormal(parent),m_PrioNormal(parent),m_PrioBelowNormal(parent),m_PrioLow(parent),m_PrioLowest(parent) \
    {\
        m_parent = parent;\
    }\
virtual int PrioHighest(void){ return m_PrioHighest.Call();}\
virtual int PrioHigh(void){ return m_PrioHigh.Call();}\
virtual int PrioAboveNormal(void){ return m_PrioAboveNormal.Call();}\
virtual int PrioNormal(void){ return m_PrioNormal.Call();}\
virtual int PrioBelowNormal(void){ return m_PrioBelowNormal.Call();}\
virtual int PrioLow(void){ return m_PrioLow.Call();}\
virtual int PrioLowest(void){ return m_PrioLowest.Call();}\
virtual Task TskCreate(TaskFunction func,int priority,int stacksize){ return m_parent->intf ## _TskCreate(func,priority,stacksize);}\
virtual Task TskCreateNoWatchdog(TaskFunction func,int priority,int stacksize){ return m_parent->intf ## _TskCreateNoWatchdog(func,priority,stacksize);}\
virtual void TskDelete(Task tsk){ return m_parent->intf ## _TskDelete(tsk);}\
virtual Task TskCurrent(void){ return m_parent->intf ## _TskCurrent();}\
virtual void TskSetPriority(Task tsk,int priority){ return m_parent->intf ## _TskSetPriority(tsk,priority);}\
virtual void TskSuspend(int msecs){ return m_parent->intf ## _TskSuspend(msecs);}\
virtual void TskResume(Task tsk){ return m_parent->intf ## _TskResume(tsk);}\
virtual void TskBeginCriticalSection(void){ return m_parent->intf ## _TskBeginCriticalSection();}\
virtual void TskEndCriticalSection(void){ return m_parent->intf ## _TskEndCriticalSection();}\
virtual void TskFeedWatchdog(void){ return m_parent->intf ## _TskFeedWatchdog();}\
virtual Bool TskBoostWatchdog(int seconds){ return m_parent->intf ## _TskBoostWatchdog(seconds);}\
virtual int TskWatchdogPeriod(void){ return m_parent->intf ## _TskWatchdogPeriod();}\
virtual void IsrBegin(void){ return m_parent->intf ## _IsrBegin();}\
virtual void IsrEnd(void){ return m_parent->intf ## _IsrEnd();}\
virtual void IsrEvtSend(Task tsk,Event evt){ return m_parent->intf ## _IsrEvtSend(tsk,evt);}\
virtual void IsrMbxSend(Mailbox mbx,int msg,int param1,Nat32 param2){ return m_parent->intf ## _IsrMbxSend(mbx,msg,param1,param2);}\
virtual Semaphore SemCreate(void){ return m_parent->intf ## _SemCreate();}\
virtual Semaphore SemCreateWithCeiling(int ceiling){ return m_parent->intf ## _SemCreateWithCeiling(ceiling);}\
virtual void SemDelete(Semaphore sem){ return m_parent->intf ## _SemDelete(sem);}\
virtual void SemAcquire(Semaphore sem){ return m_parent->intf ## _SemAcquire(sem);}\
virtual Bool SemAcquireNoWait(Semaphore sem){ return m_parent->intf ## _SemAcquireNoWait(sem);}\
virtual void SemRelease(Semaphore sem){ return m_parent->intf ## _SemRelease(sem);}\
virtual Event EvtCreate(Task tsk){ return m_parent->intf ## _EvtCreate(tsk);}\
virtual void EvtDelete(Task tsk,Event evt){ return m_parent->intf ## _EvtDelete(tsk,evt);}\
virtual void EvtSend(Task tsk,Event evt){ return m_parent->intf ## _EvtSend(tsk,evt);}\
virtual Event EvtReceive(Event mask){ return m_parent->intf ## _EvtReceive(mask);}\
virtual Event EvtReceiveNoWait(Event mask){ return m_parent->intf ## _EvtReceiveNoWait(mask);}\
virtual Event EvtReceiveWait(Event mask,int msecs){ return m_parent->intf ## _EvtReceiveWait(mask,msecs);}\
virtual Event EvtGetReserved(Task tsk){ return m_parent->intf ## _EvtGetReserved(tsk);}\
virtual Timer TmrCreate(Task tsk,Event evt){ return m_parent->intf ## _TmrCreate(tsk,evt);}\
virtual void TmrDelete(Timer tmr){ return m_parent->intf ## _TmrDelete(tmr);}\
virtual void TmrEvery(Timer tmr,int msecs){ return m_parent->intf ## _TmrEvery(tmr,msecs);}\
virtual void TmrOnce(Timer tmr,int msecs){ return m_parent->intf ## _TmrOnce(tmr,msecs);}\
virtual void TmrCancel(Timer tmr){ return m_parent->intf ## _TmrCancel(tmr);}\
virtual int TmrTime(void){ return m_parent->intf ## _TmrTime();}\
virtual int TmrResolution(void){ return m_parent->intf ## _TmrResolution();}\
virtual Mailbox MbxCreate(void){ return m_parent->intf ## _MbxCreate();}\
virtual void MbxDelete(Mailbox mbx){ return m_parent->intf ## _MbxDelete(mbx);}\
virtual void MbxSend(Mailbox mbx,int msg,int param1,Nat32 param2){ return m_parent->intf ## _MbxSend(mbx,msg,param1,param2);}\
virtual void MbxReceive(Mailbox mbx,Message * msg){ return m_parent->intf ## _MbxReceive(mbx,msg);}\
virtual Bool MbxReceiveNoWait(Mailbox mbx,Message * msg){ return m_parent->intf ## _MbxReceiveNoWait(mbx,msg);}\
virtual Talos TlsCreate(int size){ return m_parent->intf ## _TlsCreate(size);}\
virtual void* TlsAccess(Talos tls){ return m_parent->intf ## _TlsAccess(tls);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
