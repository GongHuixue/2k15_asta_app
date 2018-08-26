#ifndef IHSVDVBSIPOOLIDS_H
#define IHSVDVBSIPOOLIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDvbSiPoolIds
{
public:
	virtual ~IHsvDvbSiPoolIds(){}
	virtual int StringPool(void)= 0;
	virtual int DescPool(void)= 0;
	virtual int PmtSectionPool(void)= 0;
	virtual int BufferPool(void)= 0;
};


#define IHsvDvbSiPoolIdsImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvDvbSiPoolIds \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_StringPool; \
    InterfaceParam<Comp,int> m_DescPool; \
    InterfaceParam<Comp,int> m_PmtSectionPool; \
    InterfaceParam<Comp,int> m_BufferPool; \
    Comp ## _ ## intf( Comp *parent):m_StringPool(parent),m_DescPool(parent),m_PmtSectionPool(parent),m_BufferPool(parent) \
    {\
        m_parent = parent;\
    }\
virtual int StringPool(void){ return m_StringPool.Call();}\
virtual int DescPool(void){ return m_DescPool.Call();}\
virtual int PmtSectionPool(void){ return m_PmtSectionPool.Call();}\
virtual int BufferPool(void){ return m_BufferPool.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
