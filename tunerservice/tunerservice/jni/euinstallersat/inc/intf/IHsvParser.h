#ifndef IHSVPARSER_H
#define IHSVPARSER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvParser
{
public:
	virtual ~IHsvParser(){}
	virtual int ParseDescriptors(Nat32 sectionid,Nat16 table_id,Address * handle,int length,int cookie)= 0;
};


#define IHsvParserImpl(Comp,intf)    \
virtual int intf ## _ParseDescriptors(Nat32 sectionid,Nat16 table_id,Address * handle,int length,int cookie);\
class Comp ## _ ## intf : public IHsvParser \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int ParseDescriptors(Nat32 sectionid,Nat16 table_id,Address * handle,int length,int cookie){ return m_parent->intf ## _ParseDescriptors(sectionid,table_id,handle,length,cookie);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
