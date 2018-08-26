#ifndef ICESCITYIDS_H
#define ICESCITYIDS_H
#include <intfparam.h>
#include <provreq.h>
class ICesCityIds
{
public:
	virtual ~ICesCityIds(){}
	#define ICesCityIds_CityBeijing		((int)0 )
	#define ICesCityIds_CityGuangdong		((int)1 )
	#define ICesCityIds_CityGuangzhou		((int)2 )
	#define ICesCityIds_CityOthers		((int)3 )
	#define ICesCityIds_CityInvalid		((int)-1 )
};


#define ICesCityIdsImpl(Comp,intf)    \
class Comp ## _ ## intf : public ICesCityIds \
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
