#ifndef IMEMORYMANAGEMENT_H
#define IMEMORYMANAGEMENT_H
#include <intfparam.h>
#include <provreq.h>
class IMemoryManagement
{
public:
	virtual ~IMemoryManagement(){}
	virtual void* malloc(int size)= 0;
	virtual void free(void * ptr)= 0;
	virtual void* realloc(void * ptr,int newsize)= 0;
	virtual void* remalloc(void * ptr,int newsize)= 0;
	virtual void* palloc(int size)= 0;
};


#define IMemoryManagementImpl(Comp,intf)    \
virtual void* intf ## _malloc(int size);\
virtual void intf ## _free(void * ptr);\
virtual void* intf ## _realloc(void * ptr,int newsize);\
virtual void* intf ## _remalloc(void * ptr,int newsize);\
virtual void* intf ## _palloc(int size);\
class Comp ## _ ## intf : public IMemoryManagement \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void* malloc(int size){ return m_parent->intf ## _malloc(size);}\
virtual void free(void * ptr){ return m_parent->intf ## _free(ptr);}\
virtual void* realloc(void * ptr,int newsize){ return m_parent->intf ## _realloc(ptr,newsize);}\
virtual void* remalloc(void * ptr,int newsize){ return m_parent->intf ## _remalloc(ptr,newsize);}\
virtual void* palloc(int size){ return m_parent->intf ## _palloc(size);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
