#ifndef IPLFAPIDESIGNATORID_H
#define IPLFAPIDESIGNATORID_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiDesignatorId
{
public:
	virtual ~IPlfApiDesignatorId(){}
	#define IPlfApiDesignatorId_DesignatorNone		((Nat32)0x00000000 )
	#define IPlfApiDesignatorId_DesignatorAll		((Nat32)0xFFFFFFFF )
	#define IPlfApiDesignatorId_DesignatorAnalog		((Nat32)0x00000001 )
	#define IPlfApiDesignatorId_DesignatorDigital		((Nat32)0x00000002 )
	#define IPlfApiDesignatorId_DesignatorMpeg2		((Nat32)0x00000004 )
	#define IPlfApiDesignatorId_DesignatorMpeg4		((Nat32)0x00000008 )
	#define IPlfApiDesignatorId_DesignatorJpg		((Nat32)0x00000010 )
	#define IPlfApiDesignatorId_DesignatorMp3		((Nat32)0x00000020 )
	#define IPlfApiDesignatorId_DesignatorWm		((Nat32)0x00000040 )
	#define IPlfApiDesignatorId_DesignatorDivX		((Nat32)0x00000080 )
	#define IPlfApiDesignatorId_DesignatorMpegTs		((Nat32)0x00000100 )
	#define IPlfApiDesignatorId_DesignatorRm		((Nat32)0x00000200 )
	#define IPlfApiDesignatorId_DesignatorMkv		((Nat32)0x00000400 )
	#define IPlfApiDesignatorId_DesignatorMpegTsDmx		((Nat32)0x00000800 )
	#define IPlfApiDesignatorId_DesignatorData		((Nat32)0x00001000 )
	#define IPlfApiDesignatorId_DesignatorHls		((Nat32)0x00002000 )
	#define IPlfApiDesignatorId_DesignatorWidevine		((Nat32)0x00004000 )
	#define IPlfApiDesignatorId_DesignatorMss		((Nat32)0x00008000 )
	#define IPlfApiDesignatorId_DesignatorMhegTsDmx		((Nat32)0x00010000 )
	#define IPlfApiDesignatorId_DesignatorMpegDash_Fmp4		((Nat32)0x00020000 )
	#define IPlfApiDesignatorId_DesignatorMpegDash_TS		((Nat32)0x00040000 )
	#define IPlfApiDesignatorId_DesignatorYtlb_Fmp4		((Nat32)0x00080000 )
	#define IPlfApiDesignatorId_DesignatorNetFlix		((Nat32)0x00100000 )
};


#define IPlfApiDesignatorIdImpl(Comp,intf)    \
class Comp ## _ ## intf : public IPlfApiDesignatorId \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
