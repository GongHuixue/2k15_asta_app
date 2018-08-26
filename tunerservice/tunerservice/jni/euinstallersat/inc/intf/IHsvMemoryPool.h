#ifndef IHSVMEMORYPOOL_H
#define IHSVMEMORYPOOL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMemoryPool
{
public:
	virtual ~IHsvMemoryPool(){}
	virtual void Init(int poolid)= 0;
	virtual Address Malloc(int poolid)= 0;
	virtual void Free(int poolid,Address addr)= 0;
};


#define IHsvMemoryPoolImpl(Comp,intf)    \
virtual void intf ## _Init(int poolid);\
virtual Address intf ## _Malloc(int poolid);\
virtual void intf ## _Free(int poolid,Address addr);\
class Comp ## _ ## intf : public IHsvMemoryPool \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Init(int poolid){ return m_parent->intf ## _Init(poolid);}\
virtual Address Malloc(int poolid){ return m_parent->intf ## _Malloc(poolid);}\
virtual void Free(int poolid,Address addr){ return m_parent->intf ## _Free(poolid,addr);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
