#ifndef IHSVDIGITALSCANROUTE_H
#define IHSVDIGITALSCANROUTE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalScanRoute
{
public:
	virtual ~IHsvDigitalScanRoute(){}
	#define IHsvDigitalScanRoute_quickscan		((int)0 )
	#define IHsvDigitalScanRoute_fullscan		((int)1 )
	#define IHsvDigitalScanRoute_userentryscan		((int)2 )
	#define IHsvDigitalScanRoute_stubscan		((int)3 )
	virtual int GetActiveScanInterface(void)= 0;
};


#define IHsvDigitalScanRouteImpl(Comp,intf)    \
virtual int intf ## _GetActiveScanInterface(void);\
class Comp ## _ ## intf : public IHsvDigitalScanRoute \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetActiveScanInterface(void){ return m_parent->intf ## _GetActiveScanInterface();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
