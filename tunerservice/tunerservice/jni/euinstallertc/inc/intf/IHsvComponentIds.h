#ifndef IHSVCOMPONENTIDS_H
#define IHSVCOMPONENTIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvComponentIds
{
public:
	virtual ~IHsvComponentIds(){}
	#define IHsvComponentIds_hsvcc708dec		((Nat16)0 )
	#define IHsvComponentIds_hsvatscsdm		((Nat16)100 )
	#define IHsvComponentIds_hsvcc		((Nat16)200 )
	#define IHsvComponentIds_hsvccdisp		((Nat16)300 )
	#define IHsvComponentIds_hsvcm		((Nat16)400 )
	#define IHsvComponentIds_hsvdbase		((Nat16)500 )
	#define IHsvComponentIds_hsvdmx		((Nat16)600 )
	#define IHsvComponentIds_hsvins		((Nat16)700 )
	#define IHsvComponentIds_hsvlocks		((Nat16)800 )
	#define IHsvComponentIds_hsvlog		((Nat16)900 )
	#define IHsvComponentIds_hsvmempool		((Nat16)1000 )
	#define IHsvComponentIds_hsvmpeg		((Nat16)1100 )
	#define IHsvComponentIds_hsvmpl		((Nat16)1200 )
	#define IHsvComponentIds_hsvpgview		((Nat16)1300 )
	#define IHsvComponentIds_hsvpsip		((Nat16)1400 )
	#define IHsvComponentIds_hsvsel		((Nat16)1500 )
	#define IHsvComponentIds_hsvsrttable		((Nat16)1600 )
	#define IHsvComponentIds_hsvunsrttable		((Nat16)1700 )
	#define IHsvComponentIds_hsvl21dc		((Nat16)1800 )
	#define IHsvComponentIds_hsveuins		((Nat16)1900 )
	#define IHsvComponentIds_hsveursel		((Nat16)2000 )
	#define IHsvComponentIds_hsvdvbsdm		((Nat16)2100 )
	#define IHsvComponentIds_hsvprins		((Nat16)2200 )
	#define IHsvComponentIds_NumComponents		((int)23 )
};


#define IHsvComponentIdsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvComponentIds \
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
