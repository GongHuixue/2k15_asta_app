#ifndef IHSVCHANLIBPOSIXLIGHT_H
#define IHSVCHANLIBPOSIXLIGHT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvChanlibPosixLight
{
public:
	virtual ~IHsvChanlibPosixLight(){}
	virtual void* SemCreate(char * key)= 0;
	virtual void SemRelease(void * fildes)= 0;
	virtual void SemAcquire(void * fildes)= 0;
};


#define IHsvChanlibPosixLightImpl(Comp,intf)    \
virtual void* intf ## _SemCreate(char * key);\
virtual void intf ## _SemRelease(void * fildes);\
virtual void intf ## _SemAcquire(void * fildes);\
class Comp ## _ ## intf : public IHsvChanlibPosixLight \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void* SemCreate(char * key){ return m_parent->intf ## _SemCreate(key);}\
virtual void SemRelease(void * fildes){ return m_parent->intf ## _SemRelease(fildes);}\
virtual void SemAcquire(void * fildes){ return m_parent->intf ## _SemAcquire(fildes);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
