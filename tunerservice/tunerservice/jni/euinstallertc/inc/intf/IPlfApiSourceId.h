#ifndef IPLFAPISOURCEID_H
#define IPLFAPISOURCEID_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiSourceId
{
public:
	virtual ~IPlfApiSourceId(){}
	#define IPlfApiSourceId_SrcInvalid		((int)-1 )
	#define IPlfApiSourceId_SrcNone		((int)0 )
	#define IPlfApiSourceId_SrcTuner		((int)1 )
	#define IPlfApiSourceId_SrcFront		((int)2 )
	#define IPlfApiSourceId_SrcAv1		((int)3 )
	#define IPlfApiSourceId_SrcAv2		((int)4 )
	#define IPlfApiSourceId_SrcAv3		((int)5 )
	#define IPlfApiSourceId_SrcAv4		((int)6 )
	#define IPlfApiSourceId_SrcAv5		((int)7 )
	#define IPlfApiSourceId_SrcAv6		((int)8 )
	#define IPlfApiSourceId_SrcAv7		((int)9 )
	#define IPlfApiSourceId_SrcAv8		((int)10 )
	#define IPlfApiSourceId_SrcAv9		((int)11 )
	#define IPlfApiSourceId_SrcAv10		((int)12 )
	#define IPlfApiSourceId_SrcHdmi1		((int)13 )
	#define IPlfApiSourceId_SrcHdmi2		((int)14 )
	#define IPlfApiSourceId_SrcHdmi3		((int)15 )
	#define IPlfApiSourceId_SrcHdmi4		((int)16 )
	#define IPlfApiSourceId_SrcHdmi5		((int)17 )
	#define IPlfApiSourceId_SrcUrl		((int)18 )
	#define IPlfApiSourceId_SrcBolton		((int)19 )
	#define IPlfApiSourceId_SrcVga		((int)20 )
	#define IPlfApiSourceId_SrcFrontHdmi		((int)21 )
	#define IPlfApiSourceId_SrcSkype		((int)22 )
	#define IPlfApiSourceId_SrcWifiDisplay		((int)23 )
	#define IPlfApiSourceId_SrcData		((int)24 )
	#define IPlfApiSourceId_SrcAudioIn		((int)25 )
};


#define IPlfApiSourceIdImpl(Comp,intf)    \
class Comp ## _ ## intf : public IPlfApiSourceId \
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
