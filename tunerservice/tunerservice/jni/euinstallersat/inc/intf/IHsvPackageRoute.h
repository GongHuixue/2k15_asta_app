#ifndef IHSVPACKAGEROUTE_H
#define IHSVPACKAGEROUTE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPackageRoute
{
public:
	virtual ~IHsvPackageRoute(){}
	#define IHsvPackageRoute_generic		((int)-1 )
	#define IHsvPackageRoute_m7		((int)1 )
	#define IHsvPackageRoute_canal		((int)2 )
	#define IHsvPackageRoute_pol		((int)3 )
	#define IHsvPackageRoute_russia		((int)4 )
	#define IHsvPackageRoute_turk		((int)5 )
	#define IHsvPackageRoute_n		((int)6 )
	#define IHsvPackageRoute_fransat		((int)7 )
	#define IHsvPackageRoute_OpProfile		((int)8 )
	#define IHsvPackageRoute_freesat		((int)9 )
	virtual int GetCurrentActivePackage(void)= 0;
};


#define IHsvPackageRouteImpl(Comp,intf)    \
virtual int intf ## _GetCurrentActivePackage(void);\
class Comp ## _ ## intf : public IHsvPackageRoute \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetCurrentActivePackage(void){ return m_parent->intf ## _GetCurrentActivePackage();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
