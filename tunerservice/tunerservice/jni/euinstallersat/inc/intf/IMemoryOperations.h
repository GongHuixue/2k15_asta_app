#ifndef IMEMORYOPERATIONS_H
#define IMEMORYOPERATIONS_H
#include <intfparam.h>
#include <provreq.h>
class IMemoryOperations
{
public:
	virtual ~IMemoryOperations(){}
	virtual int memcmp(void * ptr1,void * ptr2,int num)= 0;
	virtual int memcmpRom(void * ptr1,void ROM * ptr2,int num)= 0;
	virtual void* memcpy(void * dest,void * source,int num)= 0;
	virtual void* memcpyRom(void * dest,void ROM * source,int num)= 0;
	virtual void* memmove(void * dest,void * source,int num)= 0;
	virtual void* memset(void * ptr,int val,int num)= 0;
};


#define IMemoryOperationsImpl(Comp,intf)    \
virtual int intf ## _memcmp(void * ptr1,void * ptr2,int num);\
virtual int intf ## _memcmpRom(void * ptr1,void ROM * ptr2,int num);\
virtual void* intf ## _memcpy(void * dest,void * source,int num);\
virtual void* intf ## _memcpyRom(void * dest,void ROM * source,int num);\
virtual void* intf ## _memmove(void * dest,void * source,int num);\
virtual void* intf ## _memset(void * ptr,int val,int num);\
class Comp ## _ ## intf : public IMemoryOperations \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int memcmp(void * ptr1,void * ptr2,int num){ return m_parent->intf ## _memcmp(ptr1,ptr2,num);}\
virtual int memcmpRom(void * ptr1,void ROM * ptr2,int num){ return m_parent->intf ## _memcmpRom(ptr1,ptr2,num);}\
virtual void* memcpy(void * dest,void * source,int num){ return m_parent->intf ## _memcpy(dest,source,num);}\
virtual void* memcpyRom(void * dest,void ROM * source,int num){ return m_parent->intf ## _memcpyRom(dest,source,num);}\
virtual void* memmove(void * dest,void * source,int num){ return m_parent->intf ## _memmove(dest,source,num);}\
virtual void* memset(void * ptr,int val,int num){ return m_parent->intf ## _memset(ptr,val,num);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
