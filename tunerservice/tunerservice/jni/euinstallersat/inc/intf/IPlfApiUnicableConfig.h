#ifndef IPLFAPIUNICABLECONFIG_H
#define IPLFAPIUNICABLECONFIG_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiUnicableConfig
{
public:
	virtual ~IPlfApiUnicableConfig(){}
	virtual FResult Enable(int winid,Bool Active,Nat32 Lo_Low,Nat32 Lo_High,Nat8 Ub_number,Nat32 Ub_frequency)= 0;
};


#define IPlfApiUnicableConfigImpl(Comp,intf)    \
virtual FResult intf ## _Enable(int winid,Bool Active,Nat32 Lo_Low,Nat32 Lo_High,Nat8 Ub_number,Nat32 Ub_frequency);\
class Comp ## _ ## intf : public IPlfApiUnicableConfig \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult Enable(int winid,Bool Active,Nat32 Lo_Low,Nat32 Lo_High,Nat8 Ub_number,Nat32 Ub_frequency){ return m_parent->intf ## _Enable(winid,Active,Lo_Low,Lo_High,Ub_number,Ub_frequency);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
