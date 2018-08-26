#ifndef IPLFAPIERRORIDS_H
#define IPLFAPIERRORIDS_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiErrorIds
{
public:
	virtual ~IPlfApiErrorIds(){}
	#define IPlfApiErrorIds_Ok		((FResult)0 )
	#define IPlfApiErrorIds_ResourceNotOwned		((FResult)1 )
	#define IPlfApiErrorIds_InterfaceNotAvailable		((FResult)2 )
	#define IPlfApiErrorIds_InterfaceNotImplemented		((FResult)100 )
	#define IPlfApiErrorIds_Other		((FResult)-1 )
};


#define IPlfApiErrorIdsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IPlfApiErrorIds \
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
