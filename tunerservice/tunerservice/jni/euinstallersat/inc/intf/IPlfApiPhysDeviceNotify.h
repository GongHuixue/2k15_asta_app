#ifndef IPLFAPIPHYSDEVICENOTIFY_H
#define IPLFAPIPHYSDEVICENOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiPhysDeviceNotify
{
public:
	virtual ~IPlfApiPhysDeviceNotify(){}
	#define IPlfApiPhysDeviceNotify_ErrorUnknown		((int)0 )
	#define IPlfApiPhysDeviceNotify_ErrorMaxDevices		((int)1 )
	#define IPlfApiPhysDeviceNotify_ErrorMountDevice		((int)2 )
	#define IPlfApiPhysDeviceNotify_ErrorUnmountDevice		((int)3 )
	virtual void OnInitializationDone(void)= 0;
	virtual void OnDeviceConnected(Nat32 physid)= 0;
	virtual void OnDeviceDisconnected(Nat32 physid)= 0;
	virtual void OnDeviceError(Nat32 physid,int errortype)= 0;
};


#define IPlfApiPhysDeviceNotifyImpl(Comp,intf)    \
virtual void intf ## _OnInitializationDone(void);\
virtual void intf ## _OnDeviceConnected(Nat32 physid);\
virtual void intf ## _OnDeviceDisconnected(Nat32 physid);\
virtual void intf ## _OnDeviceError(Nat32 physid,int errortype);\
class Comp ## _ ## intf : public IPlfApiPhysDeviceNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnInitializationDone(void){ return m_parent->intf ## _OnInitializationDone();}\
virtual void OnDeviceConnected(Nat32 physid){ return m_parent->intf ## _OnDeviceConnected(physid);}\
virtual void OnDeviceDisconnected(Nat32 physid){ return m_parent->intf ## _OnDeviceDisconnected(physid);}\
virtual void OnDeviceError(Nat32 physid,int errortype){ return m_parent->intf ## _OnDeviceError(physid,errortype);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
