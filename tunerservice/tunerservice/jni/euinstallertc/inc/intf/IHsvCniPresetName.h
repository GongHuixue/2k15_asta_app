#ifndef IHSVCNIPRESETNAME_H
#define IHSVCNIPRESETNAME_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCniPresetName
{
public:
	virtual ~IHsvCniPresetName(){}
	#define IHsvCniPresetName_CniNiInvalid		((int)0 )
	virtual HsvCniName GetPresetName(Nat16 vpsCni,Nat16 pkt830Cni,Nat16 pkt830Ni,Bool ard)= 0;
};


#define IHsvCniPresetNameImpl(Comp,intf)    \
virtual HsvCniName intf ## _GetPresetName(Nat16 vpsCni,Nat16 pkt830Cni,Nat16 pkt830Ni,Bool ard);\
class Comp ## _ ## intf : public IHsvCniPresetName \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual HsvCniName GetPresetName(Nat16 vpsCni,Nat16 pkt830Cni,Nat16 pkt830Ni,Bool ard){ return m_parent->intf ## _GetPresetName(vpsCni,pkt830Cni,pkt830Ni,ard);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
