#ifndef IHSVTXTPAGEREQUEST_H
#define IHSVTXTPAGEREQUEST_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPageRequest
{
public:
	virtual ~IHsvTxtPageRequest(){}
	virtual int RequestPage(PageNr page,Subcode subcode,FncReceived fnc,int tag)= 0;
	virtual void UnRequestPage(PageNr page,Subcode subcode,FncReceived fnc)= 0;
	virtual void SuggestPage(PageNr page)= 0;
	virtual void UnSuggestPage(PageNr page)= 0;
	virtual Bool SetType(PageNr page,PageType ptype,Bool priority,FncCallBack func)= 0;
};


#define IHsvTxtPageRequestImpl(Comp,intf)    \
virtual int intf ## _RequestPage(PageNr page,Subcode subcode,FncReceived fnc,int tag);\
virtual void intf ## _UnRequestPage(PageNr page,Subcode subcode,FncReceived fnc);\
virtual void intf ## _SuggestPage(PageNr page);\
virtual void intf ## _UnSuggestPage(PageNr page);\
virtual Bool intf ## _SetType(PageNr page,PageType ptype,Bool priority,FncCallBack func);\
class Comp ## _ ## intf : public IHsvTxtPageRequest \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int RequestPage(PageNr page,Subcode subcode,FncReceived fnc,int tag){ return m_parent->intf ## _RequestPage(page,subcode,fnc,tag);}\
virtual void UnRequestPage(PageNr page,Subcode subcode,FncReceived fnc){ return m_parent->intf ## _UnRequestPage(page,subcode,fnc);}\
virtual void SuggestPage(PageNr page){ return m_parent->intf ## _SuggestPage(page);}\
virtual void UnSuggestPage(PageNr page){ return m_parent->intf ## _UnSuggestPage(page);}\
virtual Bool SetType(PageNr page,PageType ptype,Bool priority,FncCallBack func){ return m_parent->intf ## _SetType(page,ptype,priority,func);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
