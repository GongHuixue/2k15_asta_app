#ifndef IHSVSTREAM_H
#define IHSVSTREAM_H
#include <intfparam.h>
#include <provreq.h>
class IHsvStream
{
public:
	virtual ~IHsvStream(){}
	virtual int GetSize(HsvDestination dest,int spid)= 0;
	virtual Bool GetIndex(HsvDestination dest,int spid,int key1,int key2,int key3,int * index)= 0;
	virtual Bool GetByKey(HsvDestination dest,int spid,int key1,int key2,int key3,void * val)= 0;
	virtual Bool GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to)= 0;
	virtual Bool GetByIndex(HsvDestination dest,int spid,int index,void * val)= 0;
};


#define IHsvStreamImpl(Comp,intf)    \
virtual int intf ## _GetSize(HsvDestination dest,int spid);\
virtual Bool intf ## _GetIndex(HsvDestination dest,int spid,int key1,int key2,int key3,int * index);\
virtual Bool intf ## _GetByKey(HsvDestination dest,int spid,int key1,int key2,int key3,void * val);\
virtual Bool intf ## _GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to);\
virtual Bool intf ## _GetByIndex(HsvDestination dest,int spid,int index,void * val);\
class Comp ## _ ## intf : public IHsvStream \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetSize(HsvDestination dest,int spid){ return m_parent->intf ## _GetSize(dest,spid);}\
virtual Bool GetIndex(HsvDestination dest,int spid,int key1,int key2,int key3,int * index){ return m_parent->intf ## _GetIndex(dest,spid,key1,key2,key3,index);}\
virtual Bool GetByKey(HsvDestination dest,int spid,int key1,int key2,int key3,void * val){ return m_parent->intf ## _GetByKey(dest,spid,key1,key2,key3,val);}\
virtual Bool GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to){ return m_parent->intf ## _GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to);}\
virtual Bool GetByIndex(HsvDestination dest,int spid,int index,void * val){ return m_parent->intf ## _GetByIndex(dest,spid,index,val);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
