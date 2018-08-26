#ifndef IHSVSOURCESETUP_H
#define IHSVSOURCESETUP_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSourceSetup
{
public:
	virtual ~IHsvSourceSetup(){}
	virtual int SourceSetupApply(int Medium)= 0;
	#define IHsvSourceSetup_Success		((int)0 )
	#define IHsvSourceSetup_SourceSetupNotAllowed		((int)1 )
	#define IHsvSourceSetup_SourceSetupNotApplied		((int)2 )
	#define IHsvSourceSetup_WaitForSourceSetupApplyNotify		((int)3 )
	#define IHsvSourceSetup_ResourceNotAvailable		((int)5 )
	#define IHsvSourceSetup_WndDesignatorNone		((Nat32)0x00000000 )
	#define IHsvSourceSetup_WndDesignatorProcessed		((Nat32)0x00000001 )
	#define IHsvSourceSetup_WndDesignatorUnProcessed		((Nat32)0x00000002 )
	#define IHsvSourceSetup_Analog 	((Nat16)0x1 )
	#define IHsvSourceSetup_DVBT		((Nat16)0x2 )
	#define IHsvSourceSetup_DVBC		((Nat16)0x4 )
	#define IHsvSourceSetup_DVBS		((Nat16)0x8 )
	#define IHsvSourceSetup_NONE		((Nat16)0x0 )
};


#define IHsvSourceSetupImpl(Comp,intf)    \
virtual int intf ## _SourceSetupApply(int Medium);\
class Comp ## _ ## intf : public IHsvSourceSetup \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int SourceSetupApply(int Medium){ return m_parent->intf ## _SourceSetupApply(Medium);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
