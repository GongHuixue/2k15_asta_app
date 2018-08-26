#ifndef IAPPAPITPHOSTRTK_H
#define IAPPAPITPHOSTRTK_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiTpHostRtk
{
public:
	virtual ~IAppApiTpHostRtk(){}
	virtual int TaskPrioHighest(void)= 0;
	virtual int TaskPrioHigh(void)= 0;
	virtual int TaskPrioAboveNormal(void)= 0;
	virtual int TaskPrioNormal(void)= 0;
	virtual int TaskPrioBelowNormal(void)= 0;
	virtual int TaskPrioLow(void)= 0;
	virtual int TaskPrioLowest(void)= 0;
	virtual int SemSignaled(void)= 0;
	virtual int SemUnsignaled(void)= 0;
	virtual int TimeoutInfinite(void)= 0;
	virtual int TimeoutZero(void)= 0;
	virtual int TaskCreate(char * name,int priority,int stacksize,FunctionInt entry,int param)= 0;
	virtual void TaskDelete(int task)= 0;
	virtual Bool TaskExists(int task)= 0;
	virtual void TaskJoin(int task)= 0;
	virtual int TaskGetCurrent(void)= 0;
	virtual void TaskSetPriority(int task,int prio)= 0;
	virtual int TaskGetPriority(int task)= 0;
	virtual void TaskSleep(int timeout)= 0;
	virtual int SemCreateBinary(int initval)= 0;
	virtual int SemCreateCounting(int initcount)= 0;
	virtual void SemDelete(int sema)= 0;
	virtual void SemWait(int sema)= 0;
	virtual Bool SemTimedWait(int sema,int timeout)= 0;
	virtual Bool SemTryWait(int sema)= 0;
	virtual void SemSignal(int sema)= 0;
	virtual void* ProcessSharedSemCreate(char * key)= 0;
	virtual void ProcessSharedSemAcquire(void * semFileLck)= 0;
	virtual void ProcessSharedSemRelease(void * semFileLck)= 0;
	virtual int MutexCreate(void)= 0;
	virtual void MutexDelete(int mutex)= 0;
	virtual void MutexLock(int mutex)= 0;
	virtual void MutexUnlock(int mutex)= 0;
	virtual void EventSend(int task,Nat32 event)= 0;
	virtual Nat32 EventReceive(Nat32 eventmask,Bool waitall,int timeout)= 0;
	virtual void EventClear(Nat32 eventmask)= 0;
	virtual int MsgQCreate(int maxmsg,int maxmsglength)= 0;
	virtual void MsgQDelete(int msgq)= 0;
	virtual int MsgQGetMessageCount(int msgq)= 0;
	virtual Bool MsgQSend(int msgq,Address buffer,int length,int timeout)= 0;
	virtual int MsgQReceive(int msgq,Address buffer,int maxlength,int timeout)= 0;
	virtual Nat32 TimeGetCurrent(void)= 0;
	virtual Nat32 TimeAdd(Nat32 a,Nat32 b)= 0;
	virtual Nat32 TimeSubtract(Nat32 a,Nat32 b)= 0;
};


#define IAppApiTpHostRtkImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual int intf ## _TaskCreate(char * name,int priority,int stacksize,FunctionInt entry,int param);\
virtual void intf ## _TaskDelete(int task);\
virtual Bool intf ## _TaskExists(int task);\
virtual void intf ## _TaskJoin(int task);\
virtual int intf ## _TaskGetCurrent(void);\
virtual void intf ## _TaskSetPriority(int task,int prio);\
virtual int intf ## _TaskGetPriority(int task);\
virtual void intf ## _TaskSleep(int timeout);\
virtual int intf ## _SemCreateBinary(int initval);\
virtual int intf ## _SemCreateCounting(int initcount);\
virtual void intf ## _SemDelete(int sema);\
virtual void intf ## _SemWait(int sema);\
virtual Bool intf ## _SemTimedWait(int sema,int timeout);\
virtual Bool intf ## _SemTryWait(int sema);\
virtual void intf ## _SemSignal(int sema);\
virtual void* intf ## _ProcessSharedSemCreate(char * key);\
virtual void intf ## _ProcessSharedSemAcquire(void * semFileLck);\
virtual void intf ## _ProcessSharedSemRelease(void * semFileLck);\
virtual int intf ## _MutexCreate(void);\
virtual void intf ## _MutexDelete(int mutex);\
virtual void intf ## _MutexLock(int mutex);\
virtual void intf ## _MutexUnlock(int mutex);\
virtual void intf ## _EventSend(int task,Nat32 event);\
virtual Nat32 intf ## _EventReceive(Nat32 eventmask,Bool waitall,int timeout);\
virtual void intf ## _EventClear(Nat32 eventmask);\
virtual int intf ## _MsgQCreate(int maxmsg,int maxmsglength);\
virtual void intf ## _MsgQDelete(int msgq);\
virtual int intf ## _MsgQGetMessageCount(int msgq);\
virtual Bool intf ## _MsgQSend(int msgq,Address buffer,int length,int timeout);\
virtual int intf ## _MsgQReceive(int msgq,Address buffer,int maxlength,int timeout);\
virtual Nat32 intf ## _TimeGetCurrent(void);\
virtual Nat32 intf ## _TimeAdd(Nat32 a,Nat32 b);\
virtual Nat32 intf ## _TimeSubtract(Nat32 a,Nat32 b);\
class Comp ## _ ## intf : public IAppApiTpHostRtk \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_TaskPrioHighest; \
    InterfaceParam<Comp,int> m_TaskPrioHigh; \
    InterfaceParam<Comp,int> m_TaskPrioAboveNormal; \
    InterfaceParam<Comp,int> m_TaskPrioNormal; \
    InterfaceParam<Comp,int> m_TaskPrioBelowNormal; \
    InterfaceParam<Comp,int> m_TaskPrioLow; \
    InterfaceParam<Comp,int> m_TaskPrioLowest; \
    InterfaceParam<Comp,int> m_SemSignaled; \
    InterfaceParam<Comp,int> m_SemUnsignaled; \
    InterfaceParam<Comp,int> m_TimeoutInfinite; \
    InterfaceParam<Comp,int> m_TimeoutZero; \
    Comp ## _ ## intf( Comp *parent):m_TaskPrioHighest(parent),m_TaskPrioHigh(parent),m_TaskPrioAboveNormal(parent),m_TaskPrioNormal(parent),m_TaskPrioBelowNormal(parent),m_TaskPrioLow(parent),m_TaskPrioLowest(parent),m_SemSignaled(parent),m_SemUnsignaled(parent),m_TimeoutInfinite(parent),m_TimeoutZero(parent) \
    {\
        m_parent = parent;\
    }\
virtual int TaskPrioHighest(void){ return m_TaskPrioHighest.Call();}\
virtual int TaskPrioHigh(void){ return m_TaskPrioHigh.Call();}\
virtual int TaskPrioAboveNormal(void){ return m_TaskPrioAboveNormal.Call();}\
virtual int TaskPrioNormal(void){ return m_TaskPrioNormal.Call();}\
virtual int TaskPrioBelowNormal(void){ return m_TaskPrioBelowNormal.Call();}\
virtual int TaskPrioLow(void){ return m_TaskPrioLow.Call();}\
virtual int TaskPrioLowest(void){ return m_TaskPrioLowest.Call();}\
virtual int SemSignaled(void){ return m_SemSignaled.Call();}\
virtual int SemUnsignaled(void){ return m_SemUnsignaled.Call();}\
virtual int TimeoutInfinite(void){ return m_TimeoutInfinite.Call();}\
virtual int TimeoutZero(void){ return m_TimeoutZero.Call();}\
virtual int TaskCreate(char * name,int priority,int stacksize,FunctionInt entry,int param){ return m_parent->intf ## _TaskCreate(name,priority,stacksize,entry,param);}\
virtual void TaskDelete(int task){ return m_parent->intf ## _TaskDelete(task);}\
virtual Bool TaskExists(int task){ return m_parent->intf ## _TaskExists(task);}\
virtual void TaskJoin(int task){ return m_parent->intf ## _TaskJoin(task);}\
virtual int TaskGetCurrent(void){ return m_parent->intf ## _TaskGetCurrent();}\
virtual void TaskSetPriority(int task,int prio){ return m_parent->intf ## _TaskSetPriority(task,prio);}\
virtual int TaskGetPriority(int task){ return m_parent->intf ## _TaskGetPriority(task);}\
virtual void TaskSleep(int timeout){ return m_parent->intf ## _TaskSleep(timeout);}\
virtual int SemCreateBinary(int initval){ return m_parent->intf ## _SemCreateBinary(initval);}\
virtual int SemCreateCounting(int initcount){ return m_parent->intf ## _SemCreateCounting(initcount);}\
virtual void SemDelete(int sema){ return m_parent->intf ## _SemDelete(sema);}\
virtual void SemWait(int sema){ return m_parent->intf ## _SemWait(sema);}\
virtual Bool SemTimedWait(int sema,int timeout){ return m_parent->intf ## _SemTimedWait(sema,timeout);}\
virtual Bool SemTryWait(int sema){ return m_parent->intf ## _SemTryWait(sema);}\
virtual void SemSignal(int sema){ return m_parent->intf ## _SemSignal(sema);}\
virtual void* ProcessSharedSemCreate(char * key){ return m_parent->intf ## _ProcessSharedSemCreate(key);}\
virtual void ProcessSharedSemAcquire(void * semFileLck){ return m_parent->intf ## _ProcessSharedSemAcquire(semFileLck);}\
virtual void ProcessSharedSemRelease(void * semFileLck){ return m_parent->intf ## _ProcessSharedSemRelease(semFileLck);}\
virtual int MutexCreate(void){ return m_parent->intf ## _MutexCreate();}\
virtual void MutexDelete(int mutex){ return m_parent->intf ## _MutexDelete(mutex);}\
virtual void MutexLock(int mutex){ return m_parent->intf ## _MutexLock(mutex);}\
virtual void MutexUnlock(int mutex){ return m_parent->intf ## _MutexUnlock(mutex);}\
virtual void EventSend(int task,Nat32 event){ return m_parent->intf ## _EventSend(task,event);}\
virtual Nat32 EventReceive(Nat32 eventmask,Bool waitall,int timeout){ return m_parent->intf ## _EventReceive(eventmask,waitall,timeout);}\
virtual void EventClear(Nat32 eventmask){ return m_parent->intf ## _EventClear(eventmask);}\
virtual int MsgQCreate(int maxmsg,int maxmsglength){ return m_parent->intf ## _MsgQCreate(maxmsg,maxmsglength);}\
virtual void MsgQDelete(int msgq){ return m_parent->intf ## _MsgQDelete(msgq);}\
virtual int MsgQGetMessageCount(int msgq){ return m_parent->intf ## _MsgQGetMessageCount(msgq);}\
virtual Bool MsgQSend(int msgq,Address buffer,int length,int timeout){ return m_parent->intf ## _MsgQSend(msgq,buffer,length,timeout);}\
virtual int MsgQReceive(int msgq,Address buffer,int maxlength,int timeout){ return m_parent->intf ## _MsgQReceive(msgq,buffer,maxlength,timeout);}\
virtual Nat32 TimeGetCurrent(void){ return m_parent->intf ## _TimeGetCurrent();}\
virtual Nat32 TimeAdd(Nat32 a,Nat32 b){ return m_parent->intf ## _TimeAdd(a,b);}\
virtual Nat32 TimeSubtract(Nat32 a,Nat32 b){ return m_parent->intf ## _TimeSubtract(a,b);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
