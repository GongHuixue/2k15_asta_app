#ifndef IHSVCHARSETUTILITYEX_H
#define IHSVCHARSETUTILITYEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCharSetUtilityEx
{
public:
	virtual ~IHsvCharSetUtilityEx(){}
	virtual FResult MbToWcEx(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,Bool ExtractShortName)= 0;
	virtual FResult MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,Bool ExtractShortName)= 0;
};


#define IHsvCharSetUtilityExImpl(Comp,intf)    \
virtual FResult intf ## _MbToWcEx(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,Bool ExtractShortName);\
virtual FResult intf ## _MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,Bool ExtractShortName);\
class Comp ## _ ## intf : public IHsvCharSetUtilityEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult MbToWcEx(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,Bool ExtractShortName){ return m_parent->intf ## _MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName);}\
virtual FResult MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,Bool ExtractShortName){ return m_parent->intf ## _MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
