#ifndef IHSVSORTEDTABLECONFIGURATIONEX_H
#define IHSVSORTEDTABLECONFIGURATIONEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSortedTableConfigurationEx
{
public:
	virtual ~IHsvSortedTableConfigurationEx(){}
	virtual int MaxElements(void)= 0;
	virtual int ElementSize(void)= 0;
	virtual Bool ThreadSafe(void)= 0;
	#define IHsvSortedTableConfigurationEx_Primary		((Nat8)0x01 )
	#define IHsvSortedTableConfigurationEx_Secondary		((Nat8)0x02 )
	#define IHsvSortedTableConfigurationEx_Teritiary		((Nat8)0x04 )
	#define IHsvSortedTableConfigurationEx_Quaternary		((Nat8)0x08 )
	virtual Nat8 SortCriteria(void)= 0;
	#define IHsvSortedTableConfigurationEx_SmallerKey		((Nat8)0 )
	#define IHsvSortedTableConfigurationEx_Equal		((Nat8)1 )
	#define IHsvSortedTableConfigurationEx_BiggerKey		((Nat8)2 )
	virtual Nat8 ComparePrimaryKey(Nat32 Key,Address data)= 0;
	virtual Nat8 CompareSecondaryKey(Nat32 Key,Address data)= 0;
	virtual Nat8 CompareTeritiaryKey(Nat32 Key,Address data)= 0;
	virtual Nat8 CompareQuaternaryKey(Nat32 Key,Address data)= 0;
};


#define IHsvSortedTableConfigurationExImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Nat8>;\
virtual Nat8 intf ## _ComparePrimaryKey(Nat32 Key,Address data);\
virtual Nat8 intf ## _CompareSecondaryKey(Nat32 Key,Address data);\
virtual Nat8 intf ## _CompareTeritiaryKey(Nat32 Key,Address data);\
virtual Nat8 intf ## _CompareQuaternaryKey(Nat32 Key,Address data);\
class Comp ## _ ## intf : public IHsvSortedTableConfigurationEx \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_MaxElements; \
    InterfaceParam<Comp,int> m_ElementSize; \
    InterfaceParam<Comp,Bool> m_ThreadSafe; \
    InterfaceParam<Comp,Nat8> m_SortCriteria; \
    Comp ## _ ## intf( Comp *parent):m_MaxElements(parent),m_ElementSize(parent),m_ThreadSafe(parent),m_SortCriteria(parent) \
    {\
        m_parent = parent;\
    }\
virtual int MaxElements(void){ return m_MaxElements.Call();}\
virtual int ElementSize(void){ return m_ElementSize.Call();}\
virtual Bool ThreadSafe(void){ return m_ThreadSafe.Call();}\
virtual Nat8 SortCriteria(void){ return m_SortCriteria.Call();}\
virtual Nat8 ComparePrimaryKey(Nat32 Key,Address data){ return m_parent->intf ## _ComparePrimaryKey(Key,data);}\
virtual Nat8 CompareSecondaryKey(Nat32 Key,Address data){ return m_parent->intf ## _CompareSecondaryKey(Key,data);}\
virtual Nat8 CompareTeritiaryKey(Nat32 Key,Address data){ return m_parent->intf ## _CompareTeritiaryKey(Key,data);}\
virtual Nat8 CompareQuaternaryKey(Nat32 Key,Address data){ return m_parent->intf ## _CompareQuaternaryKey(Key,data);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
