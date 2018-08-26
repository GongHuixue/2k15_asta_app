#ifndef IPLFAPISTORAGEDEVICE_H
#define IPLFAPISTORAGEDEVICE_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiStorageDevice
{
public:
	virtual ~IPlfApiStorageDevice(){}
	#define IPlfApiStorageDevice_ErrorOk		((int)0 )
	#define IPlfApiStorageDevice_ErrorInvalidArgument		((int)1 )
	#define IPlfApiStorageDevice_ErrorContainerListTooBig		((int)2 )
	#define IPlfApiStorageDevice_ErrorMountPathTooBig		((int)3 )
	#define IPlfApiStorageDevice_ErrorStorageNameTooBig		((int)4 )
	#define IPlfApiStorageDevice_ContTypeUnknown		((int)0 )
	#define IPlfApiStorageDevice_ContTypeMedia		((int)( 1 << 0 ) )
	#define IPlfApiStorageDevice_ContTypeRecording		((int)( 1 << 1 ) )
	#define IPlfApiStorageDevice_ContTypeTimeshift		((int)( 1 << 2 ) )
	#define IPlfApiStorageDevice_ContTypeVideostore		((int)( 1 << 3 ) )
	#define IPlfApiStorageDevice_ContTypeAll		((int)0xFFFF )
	#define IPlfApiStorageDevice_PhysIdsAll		((int)-1 )
	#define IPlfApiStorageDevice_MaxContainerListSize		((int)40 )
	#define IPlfApiStorageDevice_MaxMountPathSize		((int)128 )
	#define IPlfApiStorageDevice_MaxStorageNameSize		((int)128 )
	virtual FResult IsInitializationDone(int winid,Bool * done)= 0;
	virtual FResult IsStoragePrepared(int winid,int conttype,Bool * prepared)= 0;
	virtual FResult PrepareStorage(int winid,Nat32 id,int conttype,int * retval)= 0;
	virtual FResult GetContainerList(int winid,int conttype,Nat32 physid,Nat32 * items,Nat32 * numitems,int * retval)= 0;
	virtual FResult GetSize(int winid,Nat32 id,Nat64 * size)= 0;
	virtual FResult GetFreeSize(int winid,Nat32 id,Nat64 * size)= 0;
	virtual FResult GetWriteProtected(int winid,Nat32 contid,Bool * protect)= 0;
	virtual FResult GetPath(int winid,Nat32 contid,char * path)= 0;
	virtual FResult GetStorageName(int winid,Nat32 contid,char * name)= 0;
	virtual FResult GetUniqueID(int winid,Nat32 contid,Nat64 * uid)= 0;
	virtual FResult GetType(int winid,Nat32 contid,int * conttype)= 0;
	virtual FResult GetPhysID(int winid,Nat32 contid,Nat32 * physid)= 0;
};


#define IPlfApiStorageDeviceImpl(Comp,intf)    \
virtual FResult intf ## _IsInitializationDone(int winid,Bool * done);\
virtual FResult intf ## _IsStoragePrepared(int winid,int conttype,Bool * prepared);\
virtual FResult intf ## _PrepareStorage(int winid,Nat32 id,int conttype,int * retval);\
virtual FResult intf ## _GetContainerList(int winid,int conttype,Nat32 physid,Nat32 * items,Nat32 * numitems,int * retval);\
virtual FResult intf ## _GetSize(int winid,Nat32 id,Nat64 * size);\
virtual FResult intf ## _GetFreeSize(int winid,Nat32 id,Nat64 * size);\
virtual FResult intf ## _GetWriteProtected(int winid,Nat32 contid,Bool * protect);\
virtual FResult intf ## _GetPath(int winid,Nat32 contid,char * path);\
virtual FResult intf ## _GetStorageName(int winid,Nat32 contid,char * name);\
virtual FResult intf ## _GetUniqueID(int winid,Nat32 contid,Nat64 * uid);\
virtual FResult intf ## _GetType(int winid,Nat32 contid,int * conttype);\
virtual FResult intf ## _GetPhysID(int winid,Nat32 contid,Nat32 * physid);\
class Comp ## _ ## intf : public IPlfApiStorageDevice \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult IsInitializationDone(int winid,Bool * done){ return m_parent->intf ## _IsInitializationDone(winid,done);}\
virtual FResult IsStoragePrepared(int winid,int conttype,Bool * prepared){ return m_parent->intf ## _IsStoragePrepared(winid,conttype,prepared);}\
virtual FResult PrepareStorage(int winid,Nat32 id,int conttype,int * retval){ return m_parent->intf ## _PrepareStorage(winid,id,conttype,retval);}\
virtual FResult GetContainerList(int winid,int conttype,Nat32 physid,Nat32 * items,Nat32 * numitems,int * retval){ return m_parent->intf ## _GetContainerList(winid,conttype,physid,items,numitems,retval);}\
virtual FResult GetSize(int winid,Nat32 id,Nat64 * size){ return m_parent->intf ## _GetSize(winid,id,size);}\
virtual FResult GetFreeSize(int winid,Nat32 id,Nat64 * size){ return m_parent->intf ## _GetFreeSize(winid,id,size);}\
virtual FResult GetWriteProtected(int winid,Nat32 contid,Bool * protect){ return m_parent->intf ## _GetWriteProtected(winid,contid,protect);}\
virtual FResult GetPath(int winid,Nat32 contid,char * path){ return m_parent->intf ## _GetPath(winid,contid,path);}\
virtual FResult GetStorageName(int winid,Nat32 contid,char * name){ return m_parent->intf ## _GetStorageName(winid,contid,name);}\
virtual FResult GetUniqueID(int winid,Nat32 contid,Nat64 * uid){ return m_parent->intf ## _GetUniqueID(winid,contid,uid);}\
virtual FResult GetType(int winid,Nat32 contid,int * conttype){ return m_parent->intf ## _GetType(winid,contid,conttype);}\
virtual FResult GetPhysID(int winid,Nat32 contid,Nat32 * physid){ return m_parent->intf ## _GetPhysID(winid,contid,physid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
