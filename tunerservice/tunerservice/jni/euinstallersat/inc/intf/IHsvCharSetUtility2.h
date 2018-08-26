#ifndef IHSVCHARSETUTILITY2_H
#define IHSVCHARSETUTILITY2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCharSetUtility2
{
public:
	virtual ~IHsvCharSetUtility2(){}
	#define IHsvCharSetUtility2_ExtractNone		((int)0 )
	#define IHsvCharSetUtility2_ExtractShortName		((int)1 )
	#define IHsvCharSetUtility2_ExtractEITShortEvent		((int)2 )
	#define IHsvCharSetUtility2_ExtractEITExtendedEvent		((int)3 )
	#define IHsvCharSetUtility2_ExtractBATLrnChannelListName			((int)4)
	#define IHsvCharSetUtility2_ExtractBATLrnChannelListTranslation			((int)5)
	virtual FResult MbToWcEx(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,int exinfo)= 0;
	virtual FResult MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,int exinfo)= 0;
};


#define IHsvCharSetUtility2Impl(Comp,intf)    \
virtual FResult intf ## _MbToWcEx(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,int exinfo);\
virtual FResult intf ## _MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,int exinfo);\
class Comp ## _ ## intf : public IHsvCharSetUtility2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult MbToWcEx(Nat8 * mbstr,int mblen,Nat16 * wcstr,int * wclen,int exinfo){ return m_parent->intf ## _MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo);}\
virtual FResult MbToWc(Nat8 * mbstr,int mblen,Nat16 * wcstr,int wclen,int exinfo){ return m_parent->intf ## _MbToWc(mbstr,mblen,wcstr,wclen,exinfo);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
