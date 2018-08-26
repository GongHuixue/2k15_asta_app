#ifndef IPLFAPISTORAGEDEVICENOTIFY_H
#define IPLFAPISTORAGEDEVICENOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiStorageDeviceNotify
{
public:
	virtual ~IPlfApiStorageDeviceNotify(){}
	#define IPlfApiStorageDeviceNotify_ErrorUnknown		((int)0 )
	#define IPlfApiStorageDeviceNotify_ErrorMaxStorages		((int)1 )
	#define IPlfApiStorageDeviceNotify_ErrorUnmountStorage		((int)2 )
	#define IPlfApiStorageDeviceNotify_StatusOk		((int)0 )
	#define IPlfApiStorageDeviceNotify_StatusPartitionFailed		((int)1 )
	#define IPlfApiStorageDeviceNotify_StatusFormatFailed		((int)2 )
	#define IPlfApiStorageDeviceNotify_StatusSpeedtestFailed		((int)3 )
	#define IPlfApiStorageDeviceNotify_StepFormat		((int)1 )
	#define IPlfApiStorageDeviceNotify_StepSpeedtest		((int)2 )
	virtual void OnInitializationDone(void)= 0;
	virtual void OnStorageAdded(Nat32 contid)= 0;
	virtual void OnStorageRemoved(Nat32 contid)= 0;
	virtual void OnStorageError(Nat32 contid,int errortype)= 0;
	virtual void OnPrepareProgress(Nat32 id,int step,int maxstep,int progress)= 0;
	virtual void OnPrepareDone(Nat32 id,int status)= 0;
};


#define IPlfApiStorageDeviceNotifyImpl(Comp,intf)    \
virtual void intf ## _OnInitializationDone(void);\
virtual void intf ## _OnStorageAdded(Nat32 contid);\
virtual void intf ## _OnStorageRemoved(Nat32 contid);\
virtual void intf ## _OnStorageError(Nat32 contid,int errortype);\
virtual void intf ## _OnPrepareProgress(Nat32 id,int step,int maxstep,int progress);\
virtual void intf ## _OnPrepareDone(Nat32 id,int status);\
class Comp ## _ ## intf : public IPlfApiStorageDeviceNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnInitializationDone(void){ return m_parent->intf ## _OnInitializationDone();}\
virtual void OnStorageAdded(Nat32 contid){ return m_parent->intf ## _OnStorageAdded(contid);}\
virtual void OnStorageRemoved(Nat32 contid){ return m_parent->intf ## _OnStorageRemoved(contid);}\
virtual void OnStorageError(Nat32 contid,int errortype){ return m_parent->intf ## _OnStorageError(contid,errortype);}\
virtual void OnPrepareProgress(Nat32 id,int step,int maxstep,int progress){ return m_parent->intf ## _OnPrepareProgress(id,step,maxstep,progress);}\
virtual void OnPrepareDone(Nat32 id,int status){ return m_parent->intf ## _OnPrepareDone(id,status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
