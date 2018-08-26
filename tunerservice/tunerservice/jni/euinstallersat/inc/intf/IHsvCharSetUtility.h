#ifndef IHSVCHARSETUTILITY_H
#define IHSVCHARSETUTILITY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCharSetUtility
{
public:
	virtual ~IHsvCharSetUtility(){}
	virtual FResult MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,Bool ExtractShortName)= 0;
};


#define IHsvCharSetUtilityImpl(Comp,intf)    \
virtual FResult intf ## _MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,Bool ExtractShortName);\
class Comp ## _ ## intf : public IHsvCharSetUtility \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,Bool ExtractShortName){ return m_parent->intf ## _MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
