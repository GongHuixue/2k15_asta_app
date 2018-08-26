#ifndef IPLFAPIPHYSDEVICE_H
#define IPLFAPIPHYSDEVICE_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiPhysDevice
{
public:
	virtual ~IPlfApiPhysDevice(){}
	#define IPlfApiPhysDevice_ErrorOk		((int)0 )
	#define IPlfApiPhysDevice_ErrorDeviceListTooBig		((int)1 )
	#define IPlfApiPhysDevice_ErrorDeviceNameTooBig		((int)2 )
	#define IPlfApiPhysDevice_PhysTypeUnknown		((int)0 )
	#define IPlfApiPhysDevice_PhysTypeUsbMs		((int)( 1 << 0 ) )
	#define IPlfApiPhysDevice_PhysTypeUsbImage		((int)( 1 << 1 ) )
	#define IPlfApiPhysDevice_PhysTypeUsbHid		((int)( 1 << 2 ) )
	#define IPlfApiPhysDevice_PhysTypeUsbNet		((int)( 1 << 3 ) )
	#define IPlfApiPhysDevice_PhysTypeSD		((int)( 1 << 4 ) )
	#define IPlfApiPhysDevice_PhysTypeEmmc		((int)( 1 << 5 ) )
	#define IPlfApiPhysDevice_PhysTypeNetSmb		((int)( 1 << 6 ) )
	#define IPlfApiPhysDevice_PhysTypeNetNfs		((int)( 1 << 7 ) )
	#define IPlfApiPhysDevice_PhysTypeSkypeCam		((int)( 1 << 8 ) )
	#define IPlfApiPhysDevice_PhysTypeUsbWifi		((int)( 1 << 9 ) )
	#define IPlfApiPhysDevice_PhysTypeAll		((int)0xFFFF )
	#define IPlfApiPhysDevice_MaxDeviceListSize		((int)20 )
	#define IPlfApiPhysDevice_MaxDeviceNameSize		((int)128 )
	virtual FResult IsInitializationDone(int winid,Bool * done)= 0;
	virtual FResult GetDeviceList(int winid,int phystype,Nat32 * items,Nat32 * numitems,int * retval)= 0;
	virtual FResult GetDeviceName(int winid,Nat32 physid,char * name)= 0;
	virtual FResult GetType(int winid,Nat32 physid,int * phystype)= 0;
};


#define IPlfApiPhysDeviceImpl(Comp,intf)    \
virtual FResult intf ## _IsInitializationDone(int winid,Bool * done);\
virtual FResult intf ## _GetDeviceList(int winid,int phystype,Nat32 * items,Nat32 * numitems,int * retval);\
virtual FResult intf ## _GetDeviceName(int winid,Nat32 physid,char * name);\
virtual FResult intf ## _GetType(int winid,Nat32 physid,int * phystype);\
class Comp ## _ ## intf : public IPlfApiPhysDevice \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult IsInitializationDone(int winid,Bool * done){ return m_parent->intf ## _IsInitializationDone(winid,done);}\
virtual FResult GetDeviceList(int winid,int phystype,Nat32 * items,Nat32 * numitems,int * retval){ return m_parent->intf ## _GetDeviceList(winid,phystype,items,numitems,retval);}\
virtual FResult GetDeviceName(int winid,Nat32 physid,char * name){ return m_parent->intf ## _GetDeviceName(winid,physid,name);}\
virtual FResult GetType(int winid,Nat32 physid,int * phystype){ return m_parent->intf ## _GetType(winid,physid,phystype);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
