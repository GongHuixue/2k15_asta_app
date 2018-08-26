#ifndef IHSVCHANNELLIBSORTEDTABLEIDS_H
#define IHSVCHANNELLIBSORTEDTABLEIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvChannelLibSortedTableIds
{
public:
	virtual ~IHsvChannelLibSortedTableIds(){}
	virtual int UserTable(void)= 0;
	virtual int DigSrvcTable(void)= 0;
	virtual int DigTSTable(void)= 0;
	virtual int AnalogTable(void)= 0;
	virtual int SatInfoTable(void)= 0;
	virtual int CurrentDigSrvcTable(void)= 0;
	virtual int CurrentDigTSTable(void)= 0;
};


#define IHsvChannelLibSortedTableIdsImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvChannelLibSortedTableIds \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_UserTable; \
    InterfaceParam<Comp,int> m_DigSrvcTable; \
    InterfaceParam<Comp,int> m_DigTSTable; \
    InterfaceParam<Comp,int> m_AnalogTable; \
    InterfaceParam<Comp,int> m_SatInfoTable; \
    InterfaceParam<Comp,int> m_CurrentDigSrvcTable; \
    InterfaceParam<Comp,int> m_CurrentDigTSTable; \
    Comp ## _ ## intf( Comp *parent):m_UserTable(parent),m_DigSrvcTable(parent),m_DigTSTable(parent),m_AnalogTable(parent),m_SatInfoTable(parent),m_CurrentDigSrvcTable(parent),m_CurrentDigTSTable(parent) \
    {\
        m_parent = parent;\
    }\
virtual int UserTable(void){ return m_UserTable.Call();}\
virtual int DigSrvcTable(void){ return m_DigSrvcTable.Call();}\
virtual int DigTSTable(void){ return m_DigTSTable.Call();}\
virtual int AnalogTable(void){ return m_AnalogTable.Call();}\
virtual int SatInfoTable(void){ return m_SatInfoTable.Call();}\
virtual int CurrentDigSrvcTable(void){ return m_CurrentDigSrvcTable.Call();}\
virtual int CurrentDigTSTable(void){ return m_CurrentDigTSTable.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
