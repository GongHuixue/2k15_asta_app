#ifndef IHSVSDMPOOLIDS_H
#define IHSVSDMPOOLIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmPoolIds
{
public:
	virtual ~IHsvSdmPoolIds(){}
	virtual int StringPool(void)= 0;
	virtual int DescPool(void)= 0;
	virtual int PmtSectionPool(void)= 0;
	virtual int BufferPool(void)= 0;
	virtual int StringPoolVc(void)= 0;
	virtual int SectionBufferPool(void)= 0;
	virtual int PesBufferPool(void)= 0;
	virtual int MsgPoolId(void)= 0;
};


#define IHsvSdmPoolIdsImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvSdmPoolIds \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_StringPool; \
    InterfaceParam<Comp,int> m_DescPool; \
    InterfaceParam<Comp,int> m_PmtSectionPool; \
    InterfaceParam<Comp,int> m_BufferPool; \
    InterfaceParam<Comp,int> m_StringPoolVc; \
    InterfaceParam<Comp,int> m_SectionBufferPool; \
    InterfaceParam<Comp,int> m_PesBufferPool; \
    InterfaceParam<Comp,int> m_MsgPoolId; \
    Comp ## _ ## intf( Comp *parent):m_StringPool(parent),m_DescPool(parent),m_PmtSectionPool(parent),m_BufferPool(parent),m_StringPoolVc(parent),m_SectionBufferPool(parent),m_PesBufferPool(parent),m_MsgPoolId(parent) \
    {\
        m_parent = parent;\
    }\
virtual int StringPool(void){ return m_StringPool.Call();}\
virtual int DescPool(void){ return m_DescPool.Call();}\
virtual int PmtSectionPool(void){ return m_PmtSectionPool.Call();}\
virtual int BufferPool(void){ return m_BufferPool.Call();}\
virtual int StringPoolVc(void){ return m_StringPoolVc.Call();}\
virtual int SectionBufferPool(void){ return m_SectionBufferPool.Call();}\
virtual int PesBufferPool(void){ return m_PesBufferPool.Call();}\
virtual int MsgPoolId(void){ return m_MsgPoolId.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
