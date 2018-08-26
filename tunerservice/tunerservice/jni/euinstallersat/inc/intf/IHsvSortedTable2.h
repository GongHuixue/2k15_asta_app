#ifndef IHSVSORTEDTABLE2_H
#define IHSVSORTEDTABLE2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSortedTable2
{
public:
	virtual ~IHsvSortedTable2(){}
	#define IHsvSortedTable2_OperatorEqual		((int)0x01 )
	#define IHsvSortedTable2_OperatorSmaller		((int)0x02 )
	#define IHsvSortedTable2_OperatorGreater		((int)0x04 )
	virtual int GetNoOfRecords(int tableid)= 0;
	virtual void Init(int tableid)= 0;
	virtual Bool Insert(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data)= 0;
	virtual Bool Update(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data)= 0;
	virtual Bool Delete(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey)= 0;
	virtual Bool SearchOnPrimaryKey(int tableid,Nat32 PrimaryKey,int * from,int * to)= 0;
	virtual Bool SearchOnPrimaryAndSecondaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,int * from,int * to)= 0;
	virtual Bool SearchOnPrimarySecondaryAndTeritiaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,int * from,int * to)= 0;
	virtual Bool QueryOnKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data)= 0;
	virtual Bool QueryOnIndex(int tableid,int index,Address data)= 0;
	virtual Bool SearchOnKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,int * index)= 0;
	virtual Bool SearchOnKey2(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,int op,int * index)= 0;
};


#define IHsvSortedTable2Impl(Comp,intf)    \
virtual int intf ## _GetNoOfRecords(int tableid);\
virtual void intf ## _Init(int tableid);\
virtual Bool intf ## _Insert(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data);\
virtual Bool intf ## _Update(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data);\
virtual Bool intf ## _Delete(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey);\
virtual Bool intf ## _SearchOnPrimaryKey(int tableid,Nat32 PrimaryKey,int * from,int * to);\
virtual Bool intf ## _SearchOnPrimaryAndSecondaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,int * from,int * to);\
virtual Bool intf ## _SearchOnPrimarySecondaryAndTeritiaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,int * from,int * to);\
virtual Bool intf ## _QueryOnKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data);\
virtual Bool intf ## _QueryOnIndex(int tableid,int index,Address data);\
virtual Bool intf ## _SearchOnKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,int * index);\
virtual Bool intf ## _SearchOnKey2(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,int op,int * index);\
class Comp ## _ ## intf : public IHsvSortedTable2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetNoOfRecords(int tableid){ return m_parent->intf ## _GetNoOfRecords(tableid);}\
virtual void Init(int tableid){ return m_parent->intf ## _Init(tableid);}\
virtual Bool Insert(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data){ return m_parent->intf ## _Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data);}\
virtual Bool Update(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data){ return m_parent->intf ## _Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data);}\
virtual Bool Delete(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey){ return m_parent->intf ## _Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey);}\
virtual Bool SearchOnPrimaryKey(int tableid,Nat32 PrimaryKey,int * from,int * to){ return m_parent->intf ## _SearchOnPrimaryKey(tableid,PrimaryKey,from,to);}\
virtual Bool SearchOnPrimaryAndSecondaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,int * from,int * to){ return m_parent->intf ## _SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to);}\
virtual Bool SearchOnPrimarySecondaryAndTeritiaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,int * from,int * to){ return m_parent->intf ## _SearchOnPrimarySecondaryAndTeritiaryKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,from,to);}\
virtual Bool QueryOnKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,Address data){ return m_parent->intf ## _QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data);}\
virtual Bool QueryOnIndex(int tableid,int index,Address data){ return m_parent->intf ## _QueryOnIndex(tableid,index,data);}\
virtual Bool SearchOnKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,int * index){ return m_parent->intf ## _SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index);}\
virtual Bool SearchOnKey2(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,Nat32 QuaternaryKey,int op,int * index){ return m_parent->intf ## _SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
