#ifndef IHSVCOOKIENVMINFO_H
#define IHSVCOOKIENVMINFO_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCookieNvmInfo
{
public:
	virtual ~IHsvCookieNvmInfo(){}
	virtual HsvCookieNvmInfo* CookieNvmInfo(void)= 0;
	#define IHsvCookieNvmInfo_NumberOfEntries		((int)0 )
	#define IHsvCookieNvmInfo_InvalidNvmID		((int)-1 )
	virtual Nat32 GetDefaultCookieValue(void)= 0;
};


#define IHsvCookieNvmInfoImpl(Comp,intf)    \
friend class InterfaceParam<Comp,HsvCookieNvmInfo*>;\
virtual Nat32 intf ## _GetDefaultCookieValue(void);\
class Comp ## _ ## intf : public IHsvCookieNvmInfo \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,HsvCookieNvmInfo*> m_CookieNvmInfo; \
    Comp ## _ ## intf( Comp *parent):m_CookieNvmInfo(parent) \
    {\
        m_parent = parent;\
    }\
virtual HsvCookieNvmInfo* CookieNvmInfo(void){ return m_CookieNvmInfo.Call();}\
virtual Nat32 GetDefaultCookieValue(void){ return m_parent->intf ## _GetDefaultCookieValue();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
