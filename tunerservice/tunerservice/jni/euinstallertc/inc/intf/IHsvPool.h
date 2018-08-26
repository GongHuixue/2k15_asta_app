#ifndef IHSVPOOL_H
#define IHSVPOOL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPool
{
public:
	virtual ~IHsvPool(){}
	#define IHsvPool_MemLocalDma		((int)0 )
	#define IHsvPool_MemLocal		((int)0 )
	#define IHsvPool_MemShared		((int)0 )
	#define IHsvPool_MemLocalNoFatal		((int)0 )
	virtual int Create(int memtype,int buflen,char * name)= 0;
	virtual void* Malloc(int poolid,int size)= 0;
	virtual void* Realloc(int poolid,void * ptr,int size)= 0;
	virtual void Free(int poolid,void * ptr)= 0;
	virtual void Destroy(int poolid)= 0;
	virtual int GetMaxFree(int poolid)= 0;
};


#define IHsvPoolImpl(Comp,intf)    \
virtual int intf ## _Create(int memtype,int buflen,char * name);\
virtual void* intf ## _Malloc(int poolid,int size);\
virtual void* intf ## _Realloc(int poolid,void * ptr,int size);\
virtual void intf ## _Free(int poolid,void * ptr);\
virtual void intf ## _Destroy(int poolid);\
virtual int intf ## _GetMaxFree(int poolid);\
class Comp ## _ ## intf : public IHsvPool \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int Create(int memtype,int buflen,char * name){ return m_parent->intf ## _Create(memtype,buflen,name);}\
virtual void* Malloc(int poolid,int size){ return m_parent->intf ## _Malloc(poolid,size);}\
virtual void* Realloc(int poolid,void * ptr,int size){ return m_parent->intf ## _Realloc(poolid,ptr,size);}\
virtual void Free(int poolid,void * ptr){ return m_parent->intf ## _Free(poolid,ptr);}\
virtual void Destroy(int poolid){ return m_parent->intf ## _Destroy(poolid);}\
virtual int GetMaxFree(int poolid){ return m_parent->intf ## _GetMaxFree(poolid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
