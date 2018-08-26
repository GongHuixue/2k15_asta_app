#ifndef IPLFAPISIGSTRENGTHMEAS_H
#define IPLFAPISIGSTRENGTHMEAS_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiSigStrengthMeas
{
public:
	virtual ~IPlfApiSigStrengthMeas(){}
	virtual FResult GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval)= 0;
	virtual FResult Start(int winid,Bool * Avail,Nat32 * retval)= 0;
	virtual FResult Stop(int winid,Bool * Stopped,Nat32 * retval)= 0;
	virtual FResult GetMeasValid(int winid,Bool * Valid,Nat32 * retval)= 0;
	virtual FResult GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval)= 0;
};


#define IPlfApiSigStrengthMeasImpl(Comp,intf)    \
virtual FResult intf ## _GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval);\
virtual FResult intf ## _Start(int winid,Bool * Avail,Nat32 * retval);\
virtual FResult intf ## _Stop(int winid,Bool * Stopped,Nat32 * retval);\
virtual FResult intf ## _GetMeasValid(int winid,Bool * Valid,Nat32 * retval);\
virtual FResult intf ## _GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval);\
class Comp ## _ ## intf : public IPlfApiSigStrengthMeas \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetSigStrengthRange(int winid,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval){ return m_parent->intf ## _GetSigStrengthRange(winid,MinStrength,MaxStrength,retval);}\
virtual FResult Start(int winid,Bool * Avail,Nat32 * retval){ return m_parent->intf ## _Start(winid,Avail,retval);}\
virtual FResult Stop(int winid,Bool * Stopped,Nat32 * retval){ return m_parent->intf ## _Stop(winid,Stopped,retval);}\
virtual FResult GetMeasValid(int winid,Bool * Valid,Nat32 * retval){ return m_parent->intf ## _GetMeasValid(winid,Valid,retval);}\
virtual FResult GetSigStrength(int winid,Nat32 * Strength,Nat32 * retval){ return m_parent->intf ## _GetSigStrength(winid,Strength,retval);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
