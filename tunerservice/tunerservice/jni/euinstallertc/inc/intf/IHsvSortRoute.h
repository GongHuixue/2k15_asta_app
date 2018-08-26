#ifndef IHSVSORTROUTE_H
#define IHSVSORTROUTE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSortRoute
{
public:
	virtual ~IHsvSortRoute(){}
	#define IHsvSortRoute_stubsort		((int)-1 )
	#define IHsvSortRoute_dvbtsort		((int)0 )
	#define IHsvSortRoute_dvbcsort		((int)1 )
	#define IHsvSortRoute_norsort		((int)2 )
	#define IHsvSortRoute_dvbclitesort	((int)3 )
	#define IHsvSortRoute_dvbtlitesort	((int)4 )
	#define IHsvSortRoute_italysort		((int)5 )
	#define IHsvSortRoute_dvbt2sort		((int)6 )
	#define IHsvSortRoute_finsort		((int)7 )
	#define IHsvSortRoute_apmeasort		((int)8 )
	#define IHsvSortRoute_hungarysort	((int)9 )
	#define IHsvSortRoute_blizoosort	((int)10 )
	
	virtual void Enable(void)= 0;
	virtual int GetCurrentActiveSortInterface(void)= 0;
};


#define IHsvSortRouteImpl(Comp,intf)    \
virtual void intf ## _Enable(void);\
virtual int intf ## _GetCurrentActiveSortInterface(void);\
class Comp ## _ ## intf : public IHsvSortRoute \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Enable(void){ return m_parent->intf ## _Enable();}\
virtual int GetCurrentActiveSortInterface(void){ return m_parent->intf ## _GetCurrentActiveSortInterface();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
