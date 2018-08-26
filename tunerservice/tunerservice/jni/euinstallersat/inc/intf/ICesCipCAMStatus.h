#ifndef ICESCIPCAMSTATUS_H
#define ICESCIPCAMSTATUS_H
#include <intfparam.h>
#include <provreq.h>
class ICesCipCAMStatus
{
public:
	virtual ~ICesCipCAMStatus(){}
	#define ICesCipCAMStatus_Status_Inactive				((Nat8)0 )
	#define ICesCipCAMStatus_Status_Initialising			((Nat8)1 )
	#define ICesCipCAMStatus_Status_Initialsed			((Nat8)2 )
	#define ICesCipCAMStatus_Status_Authorised			((Nat8)3 )
	#define ICesCipCAMStatus_Status_NOT_Authorised		((Nat8)4 )
	#define ICesCipCAMStatus_Status_V1					((Nat8)5 )
	virtual void GetCipStatus(Nat8 * status)= 0;
};


#define ICesCipCAMStatusImpl(Comp,intf)    \
virtual void intf ## _GetCipStatus(Nat8 * status);\
class Comp ## _ ## intf : public ICesCipCAMStatus \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void GetCipStatus(Nat8 * status){ return m_parent->intf ## _GetCipStatus(status);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
